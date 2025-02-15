#include <atomUtil.h>
#include <functional>
#include <util.h>

#include <X11/X.h>
#include <X11/Xlib.h>

auto getAtom { std::bind(XInternAtom, dpy(), _1, false) }; 

//used atoms

const Atom wm_protocols  { getAtom("WM_PROTOCOLS")     };
const Atom wm_delete_win { getAtom("WM_DELETE_WINDOW") };

xarray<Atom> getSupportedProtocols(Window w)
{
  Atom* arr;
  int n;

  XGetWMProtocols(dpy(), w, &arr, &n);
  
  if(arr)
    return {arr, static_cast<unsigned int>(n)};

  return {};
}


