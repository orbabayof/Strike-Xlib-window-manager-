#include "util.h"
#include <tiler.h>

tiler::tiler(int screen): m_screen { ScreenOfDisplay(dpy(), screen) }, m_win_stack {}
{}

tiler::tiler(): tiler { 0 } {}

void tiler::add(Window w)
{
  m_win_stack.emplace_back(w);
}

Window tiler::extract(Window w)
{
  return m_win_stack.remove(w);
}


