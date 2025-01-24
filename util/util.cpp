#include <X11/X.h>
#include <algorithm>
#include <iostream>
#include <util.h>

#include <raii_wrapper.h>
#include <event_dispatcher.h>

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
  return XSelectInput(dpy(), w, SubstructureRedirectMask | SubstructureNotifyMask );
}


xwindow_array getChildWindows(Window w)
{
  //dummy variables are marked with _nu
  Window root_nu  ;
  Window perent_nu; 
  
  Window* arr; 
  unsigned int n; 
  XQueryTree(dpy(), w, &root_nu, &perent_nu, &arr, &n );

  if(arr)
    return {arr, n};
  
  return {};

}

void frameAllClients()
{
  auto childs { getChildWindows(g_root) };

  auto frameIfNeeded 
  { 
    [](Window w)
    {
      XWindowAttributes wa;
      XGetWindowAttributes(dpy(), w, &wa);
      if(!wa.override_redirect && wa.map_state == IsViewable)
      {
        std::cout << "framing" << '\n';
        XUnmapWindow(dpy(), w);
        frame(w);
        XMapWindow(dpy(), w);
      }
    }
  };

  std::ranges::for_each(childs, frameIfNeeded);
}
