#pragma once

#include <frame_manager.h>

class window_manager : public frame_manager
{
public:

  friend window_manager& wm();

private:
  window_manager() = default;
};

window_manager& wm();

