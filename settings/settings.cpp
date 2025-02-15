
#include "layout.h"
#include "tiler.h"
#include "util.h"
#include <algorithm>
#include <atomUtil.h>
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
#include <string>
#include <string_view>
#include <unistd.h>

#include <boost/process.hpp>

#include <X11/Xutil.h>
#include <vector>

inline std::function<void(XKeyEvent &)> spawn(std::string_view program_name)
{
	return {[=](XKeyEvent &) {
		namespace bp = boost::process;
		std::cout << "running spawn cmd\n";

		bp::spawn(bp::search_path(program_name));
	}};
}

inline std::function<void(XKeyEvent &)> moveToWorkspace(std::size_t workspace_idx)
{
	return {[=](XKeyEvent &) { screenManager().currScreen().moveTo(workspace_idx); }};
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

void doNothing(XKeyEvent &keyEv)
{
}

inline void killWindow(XKeyEvent &keyEv)
{
	auto wm_supported_protocols{getSupportedProtocols(keyEv.window)};

	if (std::ranges::contains(wm_supported_protocols, wm_delete_win))
	{
		XEvent message;
		memset(&message, 0, sizeof(message));
		message.xclient.type = ClientMessage;
		message.xclient.message_type = wm_protocols;
		message.xclient.window = keyEv.window;
		message.xclient.format = 32;
		message.xclient.data.l[0] = wm_delete_win;
	}
	else
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

inline void generate_workspace_nav_keybinds()
{
	using enum window_t;
	static std::vector<keybind<wm>> kbs{};
	kbs.reserve(settings::defualt_num_of_workspaces);

	for (std::size_t workspace_idx{1}; workspace_idx < settings::defualt_num_of_workspaces; ++workspace_idx)
		kbs.emplace_back(std::to_string(workspace_idx), Mod1Mask, moveToWorkspace(workspace_idx));
}

void settings::initKeyBinds()
{
	using enum window_t;

	static keybind<wm> st_term{"k", AnyModifier, spawn("st")};
	static keybind<wm> vs_code{"c", AnyModifier, spawn("code")};
	static keybind<wm> second{"w", AnyModifier, spawn("google-chrome-stable")};

	static keybind<allWindows> hide_window{"h", AnyModifier, hideWin};
	static keybind<allWindows> show_window{"s", AnyModifier, showWin};

  


	generate_workspace_nav_keybinds();
	flexibility_example(true);
}
