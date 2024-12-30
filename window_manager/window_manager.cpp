#include "window_manager.h"

window_manager& wm()
{
  static window_manager win_manager {};

  return win_manager;
}
