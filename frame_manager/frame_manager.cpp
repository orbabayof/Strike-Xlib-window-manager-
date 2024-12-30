#include "frame_manager.h"
#include <X11/X.h>

void frame_manager::storeFrameAndChild(Window frame, Window child)
{
  m_frames.emplace(frame,child);
}

bool frame_manager::wasFramedByWM(Window w)
{
  return m_frames.contains(w);
}

