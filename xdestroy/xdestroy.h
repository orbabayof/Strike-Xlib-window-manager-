#include <X11/Xlib.h>
#include <cstdlib>

template <typename T>
class xdestroy
{
public:
  constexpr xdestroy() noexcept = default;

  constexpr void operator() (T* ptr) const
  {
    XFree(ptr);
  }
};
