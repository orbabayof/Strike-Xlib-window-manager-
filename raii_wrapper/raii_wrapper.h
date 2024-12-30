#ifndef RAII_WRAPPER_H
#define RAII_WRAPPER_H

#include <functional>

//wrappes an object with a destractor
template<typename T, typename U>
class raii_wrapper
{

public:

  using struct_t = T;
  using function_t = U;

  raii_wrapper(const struct_t& Xstruct, const function_t& destractor): m_Xstruct { Xstruct }, m_destractor { destractor } 
  {}

  ~raii_wrapper()
  {
    m_destractor(m_Xstruct);  
  }

  struct_t   m_Xstruct;

private:

  function_t m_destractor   ;
};


#endif // !RAII_WRAPPER_H
