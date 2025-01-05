#pragma once

#include <X11/X.h>
#include <keybind.h>
#include <X11/Xlib.h>


namespace settings
{
// in pixels right now (TODO in precentage)
constexpr unsigned int border_width{3};

// can change that to a Color class
constexpr unsigned int border_color{0xff0000};
constexpr unsigned int bg_color{0x0000ff};

void initKeyBinds();

} // namespace settings
