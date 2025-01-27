#include <X11/X.h>
#include <X11/Xlib.h>
#include "xarray.h"

xarray::xarray(Window* firstWin, unsigned int n)
  :m_data   { firstWin }
  ,m_length { n }
{}

xarray::xarray()
  :m_data   { nullptr }
  ,m_length { 0       }
{}

xarray::~xarray()
{}

Window* xarray::begin()
{
  return m_data.get();
}

Window* xarray::end()
{
  return begin() + m_length;
}

Window& xarray::operator[](unsigned int idx)
{
  return m_data.get()[idx];
}


xarray::xarray(xarray && windows)
  : xarray(std::move(windows.m_data).get(), windows.m_length)
{}

xarray& xarray::operator=(xarray && windows)
{
  m_data = std::move(windows.m_data);
  m_length = windows.m_length;

  return *this;
}


