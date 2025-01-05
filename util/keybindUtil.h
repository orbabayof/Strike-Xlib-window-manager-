#include <util.h>
#include <keybind.h>

#include <iostream>
#include <algorithm>

template<window_t N>
void grabKeybinds(Window w)
{
  auto grabKey 
  {
    [w](const key& k)
      {
        std::cout << "grabbed " << k.keycode() << '\n';
        XGrabKey(dpy(), k.keycode(), k.modifiers(), w, true, GrabModeAsync, GrabModeAsync);
      }
  };

  std::ranges::for_each(keybind<N>::allDeclared(), grabKey);
}
