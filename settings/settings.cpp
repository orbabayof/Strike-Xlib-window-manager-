
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



inline std::function<void()> spawn(std::string_view program_name)
{
	return {[=]() {

    namespace bp = boost::process;
		std::cout << "running spawn cmd\n";
    
    bp::spawn(bp::search_path(program_name));
	}};
}

void doNothing()
{
}

void settings::initKeyBinds()
{
	using enum window_t;

	static keybind<wm> first{"w", Mod1Mask, spawn("google-chrome-stable")};
  static keybind<wm> second{"a", AnyModifier, spawn("arduino")};
  /*std::cout << first.keycode() << " : " << first.modifiers() << '\n';*/
}
