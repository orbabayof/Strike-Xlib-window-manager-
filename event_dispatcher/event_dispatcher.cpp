#include "event_dispatcher.h"
#include "keybind.h"
#include <keybindUtil.h>

#include <settings.h>
#include <util.h>
#include <window_manager.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>

namespace event
{
void configureRequest(XEvent &ev)
{
	XConfigureRequestEvent e{ev.xconfigurerequest};

	XWindowChanges change{.x = e.x,
						  .y = e.y,
						  .width = e.width,
						  .height = e.height,
						  .border_width = e.border_width,
						  .sibling = e.above,
						  .stack_mode = e.detail};

	// we need to reconfigure the frame if exists
	if (wm().wasFramedByWM(e.window))
	{
		XConfigureWindow(dpy(), wm().getFrame(e.window), e.value_mask, &change);
	}
	// creates configure notify
	XConfigureWindow(dpy(), g_root, e.value_mask, &change);
}

void mapRequest(XEvent &ev)
{

	XMapRequestEvent e{ev.xmaprequest};

	wm().frame(e.window);

	// creates map notify
	XMapWindow(dpy(), e.window);
}

void unMapNotify(XEvent &ev)
{
	std::cerr << "got unMap notify\n";
	XUnmapEvent e{ev.xunmap};

	// reverse mapRequest
	if (wm().wasFramedByWM(e.window))
	{

		std::cerr << "widnow was framed \n";
    wm().unframe(e.window);
	}
}

void keyPressEvent(XEvent &ev)
{
	std::cout << "running keyPress ev" << '\n';
	XKeyEvent e{ev.xkey};
  /*std::cout << e.keycode << " : " << e.state << " <- keycode \n";*/
	keybind<window_t::wm>::runBindedFuncIfExists(e);
  keybind<window_t::allWindows>::runBindedFuncIfExists(e);
}

} // namespace event

std::vector<void (*)(XEvent &)> initEventHand()
{
	std::vector<void (*)(XEvent &)> v(LASTEvent);

	v[ConfigureRequest] = event::configureRequest;
	v[MapRequest] = event::mapRequest;
	v[UnmapNotify] = event::unMapNotify;
	v[KeyPress] = event::keyPressEvent;

	return v;
}

extern const std::vector<void (*)(XEvent &)> event_hand{initEventHand()};
