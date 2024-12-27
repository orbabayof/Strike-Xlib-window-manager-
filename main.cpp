#include "display/display.hpp"
#include "window/window.hpp"
#include "handler/handler.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>


#include <iostream>

int main()
{

    std::cout << "couting to check\n";
    XEvent ev;
    auto Xdisplay { strike::display::get().dpy() };
    auto scrn { DefaultScreen(Xdisplay) };

    //actually start the window manager
    XSelectInput(Xdisplay, RootWindow(Xdisplay, scrn), SubstructureRedirectMask);
    XSync(Xdisplay, scrn);

    while(true)
    {
        while(!XNextEvent(Xdisplay, &ev))
        {

            std::cout << "got request! " << ev.type << '\n' ;

            if(strike::handler[ev.type])
                strike::handler[ev.type](ev);
        }
    } 
}