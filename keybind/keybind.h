//full constexpr support for initialization, m_action constains Xlib non-constexpr functions so no support for that

#include <key.h>

#include <functional>

class keybind : public key {
public:
   
   constexpr keybind( int keycode, int modifiers, std::function<void()> action)
   :key(keycode, modifiers)
   ,m_action { action }
   {}


   void constexpr execBindedActionIfExists() override { m_action(); }

  ~keybind() override = default;

private:
  std::function<void()> m_action {};
};
