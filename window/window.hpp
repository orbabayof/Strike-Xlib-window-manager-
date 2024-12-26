#ifndef strike_WINDOW_H
#define strike_WINDOW_H 

#include <X11/X.h>
#include <X11/Xlib.h>

#include "../display/display.hpp"


namespace strike
{

    enum
    {
        noDeleteOnDest = 0,
        deleteOnDest = 1,
    };
    class window
    {
    public:

        window(Window win);

        window(Window win, bool deleteOnDest);

        ~window();

        operator Window();

        void map();
        void unMap();

        static window create_window(int x, int y, unsigned int width, unsigned int hight)
        {
            auto display { display::get().dpy() };
            int scr { XDefaultScreen(display)};
            XSetWindowAttributes wa;
            wa.background_pixel = BlackPixel(display, scr);
            wa.event_mask = ButtonPressMask;

            return XCreateWindow(display, XRootWindow(display, scr), x, y, width, hight, 0, XDefaultDepth(display, scr), InputOutput, XDefaultVisual(display, scr), CWBackingPixel | CWEventMask, &wa);
        }


    private:

        Window m_window {};
        bool m_deleteOnDest {};
    };

}

#endif