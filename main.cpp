#include "display/display.hpp"
#include "window/window.hpp"


#include <X11/X.h>
#include <X11/Xlib.h>

#include <iostream>

void event_dispatch()
{
    auto Xdisplay { strike::display::get().dpy() };
    XEvent ev;
    while(!XNextEvent(Xdisplay, &ev))
    {
        switch (ev.type) 
        {
            case ButtonPress:
                return;
        }
    }
}

int main()
{
    auto Xdisplay { strike::display::get().dpy() };

    auto screen { DefaultScreen(Xdisplay) };
    strike::window root { XRootWindow(Xdisplay, screen) };

    strike::window square { strike::window::create_window(0, 0, 500, 500)};


    square.map();

    event_dispatch();
    

    square.unMap();

    return 0; 


}