#include "util.h"
#include "window_manager.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <algorithm>
#include <iostream>
#include <layout.h>
#include <util.h>
#include <tiler.h>

tiler::tiler(Screen *screen) : m_screen{screen}, m_win_stack{}, m_layout{defualtLayout()}
{
}

tiler::tiler(int screen) : tiler{XScreenOfDisplay(dpy(), screen)}
{
}

tiler::tiler() : tiler{0}
{
}

void tiler::add(Window w)
{
	m_win_stack.emplace_back(w);
  m_layout.get().order(*this);

}

void tiler::extract(Window w)
{
	m_win_stack.remove(w);
	m_layout.get().order(*this);
}

bool tiler::empty()
{
  return m_win_stack.empty();
}

void tiler::map()
{
  auto map_and_rep { [&](Window w){
    std::cout << "mapping window: " << w << '\n';
    ::map(wm().getFrame(w));
  }};
  std::ranges::for_each(m_win_stack, map_and_rep);
}

void tiler::unmap()
{
  auto ummap_and_rep { [&](Window w){
    std::cout << "mapping window: " << w << '\n';
    ::unmap(wm().getFrame(w));
  }};
  std::ranges::for_each(m_win_stack, ummap_and_rep);

}
