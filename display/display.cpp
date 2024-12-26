#include "display.hpp"

#include <X11/Xlib.h>

strike::display::display(): m_display { XOpenDisplay(nullptr) } {}

strike::display::~display() { XCloseDisplay(m_display); }

strike::display& strike::display::get() 
{
    static display dis {};
    return dis;
}

strike::display::operator Display*() { return m_display; }

Display* strike::display::dpy()
{
    return operator Display*();
}


