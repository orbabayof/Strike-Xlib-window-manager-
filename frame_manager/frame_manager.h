#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <unordered_map>


class frame_manager
{
public:

  void frame(Window w);

  void unframe(Window framedWindow);

  bool wasFramedByWM(Window w);

  Window getFrame(Window w);
  //returns root window if w isn't framed

protected:

  frame_manager() = default;

private:

  //maps window to his frame
  std::unordered_map<Window,Window> m_frames {};


  void storeFrameAndChild(Window frame, Window child);


  void removeFrameAndChildFromStorage(Window reframedWindow);
};


