#include <event_dispatcher.h>
#include <error_hundle.h>
#include <keybind.h>
#include <settings.h>
#include <util/util.h>
#include <keybindUtil.h>

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
	listenWindowEvents(g_root);

  XSync(dpy(), false);

  settings::initKeyBinds();
  
  grabKeybinds<window_t::wm>(g_root);

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
