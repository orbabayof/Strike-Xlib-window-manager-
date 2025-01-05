// constexpr support

#pragma once


#include <X11/Xlib.h>
#include <functional>
#include <util.h>

#include <X11/X.h>
#include <boost/container_hash/hash.hpp>
#include <string_view>

class key
{
  public:
	constexpr key(KeyCode keycode, int modifiers) : m_keycode{keycode}, m_modifiers{modifiers}
	{
	}

	constexpr key(std::string_view keyName, int modifiers) : key(XKeysymToKeycode(dpy(), XStringToKeysym(keyName.data())), modifiers)
	{
	}

	constexpr virtual ~key() = default;


  constexpr auto keycode() const { return m_keycode; }
  constexpr int modifiers() const { return m_modifiers; }

	friend class std::hash<key>;

	friend bool operator==(const key &k1, const key &k2)
	{
		return k1.m_keycode == k2.m_keycode && k1.m_modifiers == k2.m_modifiers;
	}

  private:
	KeyCode m_keycode;
	int m_modifiers;


public: 

	// a workaround over dynamic_cast for the keybind class
	void constexpr virtual execBindedActionIfExists() const 
	{
	}
};

// hashhing function for key class
namespace std
{

template <> class hash<key>
{
  public:
	size_t operator()(const key &k) const
	{
		size_t seed{};
		boost::hash_combine(seed, k.m_keycode);
		boost::hash_combine(seed, k.m_modifiers);

		return seed;
	}
};


template <> class hash<reference_wrapper<key>>
{
  public:
	size_t operator()(const key &k) const
	{
    return hash<key>{}(k);
	}
};

} // namespace std
