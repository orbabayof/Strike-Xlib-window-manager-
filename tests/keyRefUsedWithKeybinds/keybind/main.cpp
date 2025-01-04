#include "keybind.h"
#include <iostream>

int main(int argc, char *argv[])
{

	auto printHello{[]() {
  
    std::cout << "Hello!";
	}};

  keybind<wm> kb {2,2, printHello };

  key samek {2,2};

  keybind<bar>::runBindedFuncIfExists(samek);

	return 0;
}
