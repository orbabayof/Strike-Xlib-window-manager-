// constexpr support

#pragma once

#include <functional>

#include <boost/functional/hash_fwd.hpp>
#include <X11/X.h>

class key
{
  public:
	constexpr key(KeySym keycode, int modifiers) : m_keycode{keycode}, m_modifiers{modifiers}
	{
	}

	constexpr virtual ~key() = default;

	// a workaround over dynamic_cast for the keybind class
	void constexpr virtual execBindedActionIfExists()
	{
	}

	friend class std::hash<key>;

	friend bool operator==(const key &k1, const key &k2)
	{
		return k1.m_keycode == k2.m_keycode && k1.m_modifiers == k2.m_modifiers;
	}

  private:
	KeySym m_keycode;
	int m_modifiers;
};

// hashhing function for key class
namespace std
{

template <> class hash<key>
{
  public:
	size_t operator()(const key &k) const
	{
    size_t seed {};
    boost::hash_combine(seed, k.m_keycode);
    boost::hash_combine(seed, k.m_modifiers);

    return seed;
	}
};

} // namespace std
