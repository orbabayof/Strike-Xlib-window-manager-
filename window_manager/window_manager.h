#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <unordered_map>
#include <unordered_set>

class window_manager
{
public:

  void addFrame(Window frame);

  bool wasMadeByWm(Window w);

  friend window_manager& wm();

private:

  window_manager() = default;

  std::unordered_set<Window> m_frames {};
};

window_manager& wm();
