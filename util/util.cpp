#include <X11/X.h>
#include <algorithm>
#include <util.h>

#include <raii_wrapper.h>
#include <keybind.h>

#include <X11/Xlib.h>
#include <functional>

Display* dpy()
{
	static raii_wrapper display_wrapper{XOpenDisplay(nullptr), std::function{XCloseDisplay}};

	// return display
	return display_wrapper.m_Xstruct;
}

extern const Window g_root{XDefaultRootWindow(dpy())};

int listenWindowEvents(Window w)
{
  return XSelectInput(dpy(), w, SubstructureRedirectMask | SubstructureNotifyMask);
}

void grabKeybinds(Window w)
{
  auto grabKey 
  {
    [w](const key& k)
      {
        XGrabKey(dpy(), k.keycode(), k.modifiers(), w, true, GrabModeAsync, GrabModeAsync);
      }
  };

  std::ranges::for_each(keybind::allDeclared(), grabKey);
}
