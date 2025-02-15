#include <xarray/xarray.h>

#include <X11/Xutil.h>


extern const Atom wm_protocols;
extern const Atom wm_delete_win;

xarray<Atom> getSupportedProtocols(Window w);
