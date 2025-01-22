#include <X11/X.h>
#include <X11/Xlib.h>
#include <xwindow_array.h>

xwindow_array::xwindow_array(Window* firstWin, unsigned int n)
  :m_data   { firstWin }
  ,m_length { n }
{}

xwindow_array::xwindow_array()
  :m_data   { nullptr }
  ,m_length { 0       }
{}

xwindow_array::~xwindow_array()
{}

Window* xwindow_array::begin()
{
  return m_data.get();
}

Window* xwindow_array::end()
{
  return begin() + m_length;
}

Window& xwindow_array::operator[](unsigned int idx)
{
  return m_data.get()[idx];
}


xwindow_array::xwindow_array(xwindow_array && windows)
  : xwindow_array(std::move(windows.m_data).get(), windows.m_length)
{}

xwindow_array& xwindow_array::operator=(xwindow_array && windows)
{
  m_data = std::move(windows.m_data);
  m_length = windows.m_length;

  return *this;
}


