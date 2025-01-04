#include <keybind.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#include <algorithm>

Display* dpy();
extern const Window g_root;

//listens on substructure and notify 
int listenWindowEvents(Window w);

template<window_t N>
void grabKeybinds(Window w)
{
  auto grabKey 
  {
    [w](const key& k)
      {
        XGrabKey(dpy(), k.keycode(), k.modifiers(), w, true, GrabModeAsync, GrabModeAsync);
      }
  };

  std::ranges::for_each(keybind<N>::allDeclared(), grabKey);
}
