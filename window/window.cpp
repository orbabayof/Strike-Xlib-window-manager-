#include "window.hpp"
#include "../display/display.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>

strike::window::window(Window window, bool deleteOnDest)
    : m_window(window), m_deleteOnDest(deleteOnDest) {}

strike::window::window(Window win) : window{win, noDeleteOnDest} {}

strike::window::~window() {
  if (m_deleteOnDest)
    XDestroyWindow(display::get(), m_window);
}

strike::window::operator Window() { return m_window; }

void strike::window::map() { XMapWindow(display::get(), m_window); }

void strike::window::unMap() { XUnmapWindow(display::get(), m_window); }

static strike::window create_window(int x, int y, unsigned int width,
                                    unsigned int hight) {
  auto display{ strike::display::get().dpy()};
  int scr{XDefaultScreen(display)};
  XSetWindowAttributes wa;
  wa.background_pixel = WhitePixel(display, scr);
  wa.backing_pixel = WhitePixel(display, scr);
  wa.event_mask = ButtonPressMask;
  wa.border_pixel = WhitePixel(display, scr);

  return {XCreateWindow(display, XRootWindow(display, scr), x, y, width, hight,
                       0, XDefaultDepth(display, scr), InputOutput,
                       XDefaultVisual(display, scr),
                       CWBackingPixel | CWEventMask | CWBorderPixel , &wa), strike::deleteOnDest};
}
