
#include "layout.h"
#include "tiler.h"
#include "util.h"
#include <boost/process/v1/detail/child_decl.hpp>
#include <boost/process/v1/search_path.hpp>
#include <keybind.h>
#include <settings.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string_view>
#include <unistd.h>

#include <boost/process.hpp>

inline std::function<void(XKeyEvent &)> spawn(std::string_view program_name)
{
	return {[=](XKeyEvent &) {
		namespace bp = boost::process;
		std::cout << "running spawn cmd\n";

		bp::spawn(bp::search_path(program_name));
	}};
}

void hideWin(XKeyEvent &keyEv)
{
	std::cout << "hiding \n";
	hide(keyEv.subwindow);
}

void showWin(XKeyEvent &keyEv)
{
	show(keyEv.subwindow);
}

void orderSelectedScr(XKeyEvent &keyEv)
{
	defualt{}.order(t);
}

void doNothing(XKeyEvent &keyEv)
{
}

inline void killWindow(XKeyEvent &keyEv)
{
	XKillClient(dpy(), keyEv.window);
}

inline void flexibility_example(bool wantKeyBind)
{
	using enum window_t;

	if (wantKeyBind)
	{
		static keybind<allWindows> del{"d", Mod1Mask, killWindow};
	}
	else
	{
		static keybind<allWindows> del{"d", Mod1Mask, doNothing};
	}
}

void settings::initKeyBinds()
{
	using enum window_t;

	static keybind<wm> st_term{"k", AnyModifier, spawn("st")};
	static keybind<wm> vs_code{"c", AnyModifier, spawn("code")};
	static keybind<wm> second{"w", AnyModifier, spawn("google-chrome-stable")};

	static keybind<wm> hide_window{"h", AnyModifier, hideWin};
	static keybind<wm> show_window{"s", AnyModifier, showWin};

	static keybind<wm> ord{"o", AnyModifier, orderSelectedScr};

	flexibility_example(true);
}
