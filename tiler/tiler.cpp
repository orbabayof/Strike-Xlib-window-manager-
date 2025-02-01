#include "util.h"
#include <X11/Xlib.h>
#include <layout.h>
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

	auto ordering{[&]() { m_layout.get().order(*this); }};

	dontShowClientWhileExec(ordering, w);
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
