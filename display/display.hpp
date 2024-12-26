#ifndef strike_DISPLAY_H
#define strike_DISPLAY_H

#include <X11/Xlib.h>

namespace strike 
{
    class display
    {

    public:

        static display& get();
        
        ~display();

        operator _XDisplay*();

        Display* dpy();

    private:
        display();
        Display* m_display {};
    };
}

#endif