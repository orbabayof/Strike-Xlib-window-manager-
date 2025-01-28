#include <frame_manager.h>
#include <util.h>
#include <settings.h>
#include <keybindUtil.h>
#include <window_manager.h>

#include <X11/X.h>

#include <iostream>

void frame_manager::storeFrameAndChild(Window frame, Window child)
{
  m_frames.emplace(child,frame);
}

bool frame_manager::wasFramedByWM(Window w)
{
  return m_frames.contains(w);
}

Window frame_manager::getFrame(Window w)
{
  return wasFramedByWM(w) ? m_frames[w] : g_root;
}


void frame_manager::removeFrameAndChildFromStorage(Window reframedWindow)
{
  m_frames.erase(reframedWindow);
}

void frame_manager::frame(Window w)
{
	XWindowAttributes wa;
	XGetWindowAttributes(dpy(), w, &wa);

	// triggers CreateNotify
	const Window frame{XCreateSimpleWindow(dpy(), g_root, wa.x, wa.y, wa.width, wa.height, settings::border_width,
										   settings::border_color, settings::bg_color)};

	// frame is not a direct child of root at this point
	listenWindowEvents(frame);

	std::cout << "got to the place of the grab" << '\n';
	grabKeybinds<window_t::wm>(w);
  grabKeybinds<window_t::allWindows>(w);

	// for crashes and cleanup
	XAddToSaveSet(dpy(), w);

	XSync(dpy(), false);

	// offset within the frame, triggers ReperentNotify
	XReparentWindow(dpy(), w, frame, 0, 0);

	XMapWindow(dpy(), frame);

	storeFrameAndChild(frame, w);

	// TODO grub key events
}

void frame_manager::unframe(Window framedWindow)
{
	const Window frame{getFrame(framedWindow)};

	XUnmapWindow(dpy(), frame);

	// offset window back to the root
	XReparentWindow(dpy(), framedWindow, DefaultRootWindow(dpy()), 0, 0);

	XRemoveFromSaveSet(dpy(), framedWindow);

	XDestroyWindow(dpy(), frame);

	removeFrameAndChildFromStorage(framedWindow);
}
