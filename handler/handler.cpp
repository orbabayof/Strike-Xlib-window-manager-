#include "handler.hpp"

#include "../display/display.hpp"
#include "../window/window.hpp"

#include <X11/Xlib.h>
#include <cstdlib>
#include <iostream>


void strike::event_dispatch::mapRequest(XEvent& e)
{
    XMapRequestEvent& mapEvent { e.xmaprequest } ;
    XWindowAttributes attr;
    auto Xdisplay { display::get().dpy() };
    strike::window winToBeMapped { mapEvent.window };

    bool gotAttr { static_cast<bool>(XGetWindowAttributes(Xdisplay, winToBeMapped ,&attr)) };
    if(!gotAttr || attr.override_redirect)
         return;
    else
    {
        //for now we will just map the window
        std::cout << "we mapped a window!!!!!\n"; 
        winToBeMapped.map();
    }
}
