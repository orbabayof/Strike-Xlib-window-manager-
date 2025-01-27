#pragma once

#include <X11/X.h>
#include <memory>
#include "../xdestroy/xdestroy.h"

template <typename T>
class xarray {
public:

  xarray();
  xarray(T* firstWin, unsigned int n);
  xarray(xarray &&);
  xarray &operator=(xarray &&);

  ~xarray();
  
  T& operator[](unsigned int idx);

  T* begin();
  T* end();

  [[nodiscard]] T* data(){ return m_data.get(); }
  [[nodiscard]] unsigned int& length() { return m_length; }

  //lets just make sure we don't get double dealocc for the same address
  xarray(const xarray &) = delete;
  xarray &operator=(const xarray &) = delete;

private:

  std::unique_ptr<T,xdestroy<T>> m_data;
  unsigned int m_length;
};


template <typename T>
xarray<T>::xarray(T* firstWin, unsigned int n)
  :m_data   { firstWin }
  ,m_length { n }
{}


template <typename T>
xarray<T>::xarray()
  :m_data   { nullptr }
  ,m_length { 0       }
{}

template <typename T>
xarray<T>::~xarray()
{}


template <typename T>
T* xarray<T>::begin()
{
  return m_data.get();
}

template <typename T>
T* xarray<T>::end()
{
  return begin() + m_length;
}

template <typename T>
T& xarray<T>::operator[](unsigned int idx)
{
  return m_data.get()[idx];
}


template <typename T>
xarray<T>::xarray(xarray && otherArr)
  : xarray(std::move(otherArr.m_data).get(), otherArr.m_length)
{}

template <typename T>
xarray<T>& xarray<T>::operator=(xarray && otherArr)
{
  m_data = std::move(otherArr.m_data);
  m_length = otherArr.m_length;

  return *this;
}


