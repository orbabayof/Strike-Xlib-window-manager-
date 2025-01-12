#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <keybind.h>
#include <settings.h>
#include <sstream>
#include <string>
#include <string_view>

inline std::function<void()> spawn(std::string_view program_name)
{
	return {[=]() {
		std::cout << "running spawn cmd\n";
		std::string command{(std::ostringstream{} << "/bin/sh -c " << program_name).str()};
		system(command.c_str());
	}};
}

void doNothing()
{
}

void settings::initKeyBinds()
{
	using enum window_t;

	static keybind<wm> first{"w", Mod1Mask, spawn("google-chrome-stable")};
  std::cout << first.keycode() << " : " << first.modifiers() << '\n';
}
