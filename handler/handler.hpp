#include <X11/X.h>
#include <X11/Xlib.h>

#include <array>


namespace strike 
{
    constexpr std::array<void(*)(XEvent&), LASTEvent> initHandler()
    {
        std::array<void(*)(XEvent&), LASTEvent> handler {};

        handler[ButtonPress     ]  = nullptr;
	    handler[ClientMessage   ]  = nullptr;
	    handler[ConfigureRequest]  = nullptr;
	    handler[ConfigureNotify ]  = nullptr;
	    handler[DestroyNotify   ]  = nullptr;
	    handler[EnterNotify     ]  = nullptr;
	    handler[Expose          ]  = nullptr;
	    handler[FocusIn         ]  = nullptr;
	    handler[KeyPress        ]  = nullptr;
	    handler[MappingNotify   ]  = nullptr;
	    handler[MapRequest      ]  = nullptr;
	    handler[MotionNotify    ]  = nullptr;
	    handler[PropertyNotify  ]  = nullptr;
	    handler[UnmapNotify     ]  = nullptr;

        return handler;
    }

    constexpr std::array<void(*)(XEvent&), LASTEvent> handler { initHandler() };

    namespace event_dispatch
    {

    }

}