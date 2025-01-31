// full constexpr support for initialization, m_action constains Xlib non-constexpr functions so no support for that

#pragma once

#include "key.h"

#include <X11/Xlib.h>
#include <functional>
#include <iostream>
#include <string_view>
#include <unordered_set>

enum class window_t
{
  allWindows,
  wm,
  bar,

  max_types
};

template<window_t N>
class keybind : public key
{
  public:

	constexpr keybind(std::string_view keyName, unsigned int modifiers, std::function<void(XKeyEvent&)> action)
		: key(keyName, modifiers), m_action{action}
	{
		m_all.emplace(*this);
	}

	static void runBindedFuncIfExists(XKeyEvent& keyEv)
	{
      
	  key k {static_cast<KeyCode>(keyEv.keycode), keyEv.state};
    std::cout << m_all.size() << '\n';
		if (wasDeclared(k))
		{
      std::reference_wrapper<key> kb { *m_all.find(k) }; 
      std::cout << "got here! \n";
      kb.get().execBindedActionIfExists(keyEv);
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
	std::function<void(XKeyEvent&)> m_action{};
	static inline std::unordered_set<std::reference_wrapper<key>> m_all;


	void constexpr execBindedActionIfExists(XKeyEvent& keyEv) const override
	{
		m_action(keyEv);
	}
};
