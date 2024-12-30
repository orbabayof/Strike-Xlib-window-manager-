#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <unordered_map>
#include <unordered_set>

class frame_manager
{
public:

  void storeFrameChildWindow(Window frame);

  bool wasFramedByWM(Window w);


protected:

  frame_manager() = default;

private:

  std::unordered_set<Window> m_reframedWindows {};
};


