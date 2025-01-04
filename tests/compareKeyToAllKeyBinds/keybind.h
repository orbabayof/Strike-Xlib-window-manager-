//full constexpr support for initialization, m_action constains Xlib non-constexpr functions so no support for that

#pragma once

#include "key.h"

#include <functional>
#include <unordered_set>

enum windowType
{
  wm,
  bar,

  max_types,
};

template <windowType N>
class keybind : public key {
public:
   
   constexpr keybind( unsigned long keycode, int modifiers, std::function<void()> action)
   :key(keycode, modifiers)
   ,m_action { action }
   {
      m_all.emplace(*this); 
   }


   void constexpr execBindedActionIfExists() override { m_action(); }
    
   static bool wasDeclared(key k) { return m_all.contains(k); }

  //avoid dangaling references
  ~keybind() override
  {
    m_all.erase(*this);
  }

private:

  std::function<void()> m_action {};
  static inline std::unordered_set<std::reference_wrapper<key>> m_all;
};
