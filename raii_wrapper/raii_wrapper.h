#ifndef RAII_WRAPPER_H
#define RAII_WRAPPER_H

//wrappes an object with a destractor
template<typename T, typename U>
class raii_wrapper
{

public:

  using struct_t = T;
  using function_t = U;

  raii_wrapper(const struct_t& Xstruct, const function_t& destractor): m_Xstruct { Xstruct }, m_destractor { destractor }, isMoved { false }
  {}

  ~raii_wrapper()
  {
    if(!isMoved)
      m_destractor(m_Xstruct);  
  }

  struct_t   m_Xstruct;

    
  raii_wrapper(raii_wrapper && another_wrapper) noexcept
  {
    m_Xstruct = another_wrapper.m_Xstruct;
    another_wrapper.isMoved = true;
  };
  raii_wrapper(const raii_wrapper &) = delete;

  operator struct_t()
  {
    return m_Xstruct;
  }

private:

  function_t m_destractor ;
  bool       isMoved      ; 
};


#endif // !RAII_WRAPPER_H
