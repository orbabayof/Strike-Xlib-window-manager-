#include <error_hundle.h>
#include <event_dispatcher.h>
#include <keybind.h>
#include <keybindUtil.h>
#include <settings.h>
#include <thread>
#include <unistd.h>
#include <util/util.h>
#include <workspace.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "we're testinggggg\n";
	if (!dpy())
	{
		std::cerr << "can't connnect with the X server! \n";
		return 1;
	}

	XSetErrorHandler(errorHandler);
	// might want to add more redirect masks
	frameAllClients();

	listenWindowEvents(g_root);

	XSync(dpy(), false);

	settings::initKeyBinds();

	grabKeybinds<window_t::wm>(g_root);

	/*workspace w{ScreenOfDisplay(dpy(), 0)};*/
	/*Window wind2{*/
	/*	XCreateSimpleWindow(dpy(), g_root, 500, 500, 50, 50, settings::border_width, settings::border_color,
	 * 0x808080)};*/
	/*Window wind3{*/
	/*	XCreateSimpleWindow(dpy(), g_root, 500, 500, 50, 50, settings::border_width, settings::border_color,
	 * 0x808080)};*/
	/*Window wind4{*/
	/*	XCreateSimpleWindow(dpy(), g_root, 500, 500, 50, 50, settings::border_width, settings::border_color,
	 * 0x808080)};*/
	/*Window wind5{*/
	/*	XCreateSimpleWindow(dpy(), g_root, 500, 500, 50, 50, settings::border_width, settings::border_color,
	 * 0x808080)};*/
	/**/
	/*w.show();*/
	/**/
	/*w.add(wind2);*/
	/*w.add(wind3);*/
	/*w.add(wind4);*/
	/*w.add(wind5);*/
	/*XMapWindow(dpy(), wind2);*/
	/*XMapWindow(dpy(), wind3);*/
	/*XMapWindow(dpy(), wind4);*/
	/*XMapWindow(dpy(), wind5);*/
	getWorkSpace(0);
	/*XSync(dpy(), false);*/
	std::cout << "child window count: " << getChildWindows(g_root).length() << '\n';

	/*event loop */
	while (true)
	{
		XEvent ev;

		while (!XNextEvent(dpy(), &ev))
		{

			std::cout << "got event: " << ev.type << '\n';
			if (event_hand[ev.type])
				event_hand[ev.type](ev);
		}
	}

	return 0;
}
