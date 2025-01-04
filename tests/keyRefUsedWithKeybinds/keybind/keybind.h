// full constexpr support for initialization, m_action constains Xlib non-constexpr functions so no support for that

#pragma once

#include "key.h"

#include <functional>
#include <unordered_set>

enum window_t
{
  wm,
  bar,

  max_types
};

template<window_t N>
class keybind : public key
{
  public:

	constexpr keybind(unsigned long keycode, int modifiers, std::function<void()> action)
		: key(keycode, modifiers), m_action{action}
	{
		m_all.emplace(*this);
	}

	static void runBindedFuncIfExists(key &k)
	{
		if (wasDeclared(k))
		{
      std::reference_wrapper<key> kb { *m_all.find(k) }; 
      kb.get().execBindedActionIfExists();
		}
	}

	static bool wasDeclared(key &k)
	{
		return m_all.contains(k);
	}

	static const std::unordered_set<std::reference_wrapper<key>> &allDeclared()
	{
		return m_all;
	}


	// avoid dangaling references
	~keybind() override
	{
		m_all.erase(*this);
	}

  private:
	std::function<void()> m_action{};
	static inline std::unordered_set<std::reference_wrapper<key>> m_all;

	void constexpr execBindedActionIfExists() const override
	{
		m_action();
	}
};
