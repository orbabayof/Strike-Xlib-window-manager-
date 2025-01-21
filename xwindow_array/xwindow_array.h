#include <X11/X.h>

class xwindow_array {
public:
  xwindow_array(Window* firstWin, unsigned int n);
  xwindow_array(xwindow_array &&);
  xwindow_array &operator=(xwindow_array &&);

  ~xwindow_array();
  
  Window& operator[](unsigned int idx);

  Window* begin();
  Window* end();

  //lets just make sure we don't get double dealocc for the same address
  xwindow_array(const xwindow_array &) = delete;
  xwindow_array &operator=(const xwindow_array &) = delete;

private:
  Window* m_data;
  unsigned int m_length;
};
