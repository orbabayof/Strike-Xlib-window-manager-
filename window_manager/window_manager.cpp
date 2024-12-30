#include "window_manager.h"
#include <X11/X.h>

void window_manager::addFrame(Window frame)
{
	m_frames.emplace(frame);
}

bool window_manager::wasMadeByWm(Window w)
{
	return m_frames.contains(w);
}

window_manager& wm()
{
  static window_manager wm {};
	return wm;
}
