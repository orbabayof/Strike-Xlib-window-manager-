#include "event_dispatcher/event_dispatcher.h"
#include "util/util.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "we're testinggggg\n";
	if (!dpy())
		std::cerr << "can't connnect with the X server! \n";

	// might want to add more redirect masks
	listenWindowEvents(g_root);

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
