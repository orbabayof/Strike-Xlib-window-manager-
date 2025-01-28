#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <vector>

extern const std::vector<void (*)(XEvent &)> event_hand;

