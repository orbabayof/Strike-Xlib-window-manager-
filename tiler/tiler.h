#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>

#include <functional>
#include <list>

class layout;

class tiler
{

  public:
	void add(Window w);
	void extract(Window w);

	tiler(Screen *scr);
	tiler(int screen);
	tiler();

	~tiler() = default;

	friend class layout;

  private:
	std::list<Window> m_win_stack{};
	Screen *m_screen{};
	std::reference_wrapper<const layout> m_layout;
};

inline tiler t{};
