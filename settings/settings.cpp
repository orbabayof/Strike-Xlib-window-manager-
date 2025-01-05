#include "keybind.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <settings.h>

void doNothing()
{}

void settings::initKeyBinds()
{
  using enum window_t;

  static keybind<wm> first {"a", AnyModifier, doNothing };


}
