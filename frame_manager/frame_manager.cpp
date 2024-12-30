#include "frame_manager.h"

#include "../util/util.h"

#include <X11/X.h>

void frame_manager::storeFrameAndChild(Window frame, Window child)
{
  m_frames.emplace(child,frame);
}

bool frame_manager::wasFramedByWM(Window w)
{
  return m_frames.contains(w);
}

Window frame_manager::getFrame(Window w)
{
  return wasFramedByWM(w) ? m_frames[w] : g_root;
}


void frame_manager::removeFrameAndChildFromStorage(Window reframedWindow)
{
  m_frames.erase(reframedWindow);
}
