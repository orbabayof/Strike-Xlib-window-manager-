#include <util.h>

#include <raii_wrapper.h>

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
