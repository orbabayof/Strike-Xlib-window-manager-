#include "layout.h"
#include "tiler.h"
#include "util.h"
#include <algorithm>
#include <atomUtil.h>
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


#include <X11/Xutil.h>
#include <filesystem>

template <typename... Arg>
void execBin(std::string_view binName, Arg... arg)
{
  std::filesystem::path binary { "/usr/bin/" };
  binary /= binName;

  if(fork() == 0)
  {
    execl(binary.c_str(), binary.c_str(), std::forward<Arg>(arg)... ,nullptr);
    std::_Exit(EXIT_SUCCESS);
  }
} 

inline std::function<void(XKeyEvent &)> spawn(std::string_view program_name)
{
	return {[=](XKeyEvent &) {
		std::cout << "running spawn cmd\n";

    execBin(program_name);
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
