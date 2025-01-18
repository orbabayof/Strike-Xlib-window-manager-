#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <keybind.h>
#include <settings.h>
#include <string_view>
#include <unistd.h>

template <std::size_t N>
int execvp(const char* file, const char* const (&argv)[N])
{
  return execvp(file, const_cast<char* const*>(argv));
}


inline std::function<void()> spawn(std::string_view program_name)
{
	return {[=]() {
		std::cout << "running spawn cmd\n";

		const char* argument_list[] = {nullptr};

  	pid_t pid { fork() };

  	if(pid)
    {
	  	execvp(program_name.data(), argument_list);
      std::exit(0);
    }

	}};
}

void doNothing()
{
}

void settings::initKeyBinds()
{
	using enum window_t;

	static keybind<wm> first{"w", Mod1Mask, spawn("google-chrome-stable")};
  /*static keybind<wm> second{"a", AnyModifier, spawn("arduino")};*/
  /*std::cout << first.keycode() << " : " << first.modifiers() << '\n';*/
}
