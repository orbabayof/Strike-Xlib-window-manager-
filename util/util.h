#pragma once

#include "../xarray/xarray.h"
#include "layout.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <functional>

Display *dpy();
extern const Window g_root;

// listens on substructure and notify
int listenWindowEvents(Window w);

xarray<Window> getChildWindows(Window w);

void frameAllClients();

void show(Window client);
void hide(Window client);

void resize(int x, int y, pixel_size s, Window w);

bool isWindowModifieble(Window w);

using namespace std::placeholders; 

inline const auto map { std::bind(XMapWindow, dpy(), _1) }; 
inline const auto unmap { std::bind(XUnmapWindow, dpy(), _1) }; 

