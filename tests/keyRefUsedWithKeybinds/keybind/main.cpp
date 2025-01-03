#include "keybind.h"
#include <iostream>

int main(int argc, char *argv[])
{

	auto printHello{[]() {
  
    std::cout << "Hello!";
	}};

  keybind kb {2,2, printHello };

  key samek {2,2};

  keybind::runBindedFuncIfExists(samek);

	return 0;
}
