#include "event_dispatcher.h"
#include "keybind.h"
#include <keybindUtil.h>
#include <workspace.h>

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
  //will be used for floating windows later
  
	/*XConfigureRequestEvent e{ev.xconfigurerequest};*/
	/**/
	/*XWindowChanges change{.x = e.x,*/
	/*					  .y = e.y,*/
	/*					  .width = e.width,*/
	/*					  .height = e.height,*/
	/*					  .border_width = e.border_width,*/
	/*					  .sibling = e.above,*/
	/*					  .stack_mode = e.detail};*/
	/**/
	/*// we need to reconfigure the frame if exists*/
	/*if (wm().wasFramedByWM(e.window))*/
	/*{*/
	/*	XConfigureWindow(dpy(), wm().getFrame(e.window), e.value_mask, &change);*/
	/*}*/
	/*// creates configure notify*/
	/*XConfigureWindow(dpy(), g_root, e.value_mask, &change);*/
}

void mapRequest(XEvent &ev)
{

	XMapRequestEvent e{ev.xmaprequest};

	if (wm().wasFramedByWM(e.window))
	{
		XMapWindow(dpy(), wm().getFrame(e.window));
	}
	else
	{
		wm().frame(e.window);
	}

	/*t.add(e.window);*/
	/*defualtLayout().order(t);*/
	getWorkSpace(0).add(e.window);

	XMapWindow(dpy(), e.window);
}

void unMapNotify(XEvent &ev)
{
	std::cerr << "got unMap notify\n";
	XUnmapEvent e{ev.xunmap};

	// reverse mapRequest
	if (wm().wasFramedByWM(e.window))
	{
		XUnmapWindow(dpy(), wm().getFrame(e.window));
	}

  getWorkSpace(0).remove(e.window);
}

void keyPressEvent(XEvent &ev)
{
	std::cout << "running keyPress ev" << '\n';
	XKeyEvent e{ev.xkey};
	/*std::cout << e.keycode << " : " << e.state << " <- keycode \n";*/
	keybind<window_t::wm>::runBindedFuncIfExists(e);
	keybind<window_t::allWindows>::runBindedFuncIfExists(e);
}

void destroyNotifyEvent(XEvent &ev)
{
	XDestroyWindowEvent e{ev.xdestroywindow};

	if (wm().wasFramedByWM(e.window))
		wm().unframe(e.window);
}

} // namespace event

std::vector<void (*)(XEvent &)> initEventHand()
{
	std::vector<void (*)(XEvent &)> v(LASTEvent);

	v[ConfigureRequest] = event::configureRequest;
	v[MapRequest] = event::mapRequest;
	v[UnmapNotify] = event::unMapNotify;
	v[KeyPress] = event::keyPressEvent;
	v[DestroyNotify] = event::destroyNotifyEvent;

	return v;
}

extern const std::vector<void (*)(XEvent &)> event_hand{initEventHand()};
