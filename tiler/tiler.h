#pragma once


#include <X11/X.h>
#include <X11/Xlib.h>

#include <list>

class tiler 
{

public:


  void add(Window w);
  Window extract(Window w);

  tiler(int screen);
  tiler();

  ~tiler() = default;

  tiler(tiler &&)                 = delete;
  tiler(const tiler &)            = delete;
  tiler &operator=(tiler &&)      = delete;
  tiler &operator=(const tiler &) = delete;

  friend class layout;
private:

  std::list<Window> m_win_stack {};
  Screen* m_screen {};
  

};
