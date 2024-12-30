#include "event_dispatcher.h"

#include "../settings/settings.h"
#include "../util/util.h"
#include "../window_manager/window_manager.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>
#include <vector>

void frame(Window w)
{
	XWindowAttributes wa;
	XGetWindowAttributes(dpy(), w, &wa);

  //triggers CreateNotify
	const Window frame{XCreateSimpleWindow(dpy(), g_root, wa.x, wa.y, wa.width, wa.height, settings::border_width,
										   settings::border_color, settings::bg_color)};

	// frame is not a direct child of root at this point
	listenWindowEvents(frame);

  // for crashes and cleanup
	XAddToSaveSet(dpy(), w);

  // offset within the frame, triggers ReperentNotify
  XReparentWindow(dpy(), w, frame, 0, 0);

  XMapWindow(dpy(), frame);
  
  wm().storeFrameAndChild(frame, w);

  //TODO grub key events
}

void unframe(Window framedWindow)
{
    const Window frame { wm().getFrame(framedWindow) };

    XUnmapWindow(dpy(), frame);

    //offset window back to the root 
    XReparentWindow(dpy(), framedWindow, g_root, 0, 0);

    XRemoveFromSaveSet(dpy(), framedWindow);

    XDestroyWindow(dpy(), frame);


    wm().removeFrameAndChildFromStorage(framedWindow);
}

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
  
  //we need to reconfigure the frame if exists
  if(wm().wasFramedByWM(e.window))
  {
    XConfigureWindow(dpy(), wm().getFrame(e.window) , e.value_mask, &change);
  }
	// creates configure notify
	XConfigureWindow(dpy(), g_root, e.value_mask, &change);
}

void mapRequest(XEvent &ev)
{

	XMapRequestEvent e{ev.xmaprequest};

  frame(e.window);

	// creates map notify
	XMapWindow(dpy(), e.window);
}

void unMapNotify(XEvent& ev)
{
  XUnmapEvent e { ev.xunmap };

  //reverse mapRequest
  if(wm().wasFramedByWM(e.window))
  {
    std::cerr << "widnow was framed \n";
    unframe(e.window);
  }
}

} // namespace event

std::vector<void (*)(XEvent &)> initEventHand()
{
	std::vector<void (*)(XEvent &)> v(LASTEvent);

	v[ConfigureRequest] = event::configureRequest;
	v[MapRequest] = event::mapRequest;
  v[UnmapNotify] = event::unMapNotify;

	return v;
}

extern const std::vector<void (*)(XEvent &)> event_hand{initEventHand()};
