#include "frame_manager.h"
#include <X11/X.h>

void frame_manager::storeFrameChildWindow(Window w)
{
  m_reframedWindows.emplace(w);
}

bool frame_manager::wasFramedByWM(Window w)
{
  return m_reframedWindows.contains(w);
}

