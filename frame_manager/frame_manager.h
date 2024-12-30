#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>


class frame_manager
{
public:

  void storeFrameAndChild(Window frame, Window child);

  bool wasFramedByWM(Window w);


protected:

  frame_manager() = default;

private:

  //maps window to his frame
  std::unordered_map<Window,Window> m_frames {};
};


