#include <algorithm>
class percentage {
public:

  percentage(int partOfHole);
  percentage(unsigned long long partOfHole);
  friend int operator*(int XwidthOrHeight, percentage p); 
  friend int operator*(percentage p, int XwidthOrHeight);


private:
  int m_partOfHole {};
  
  template<typename T>
  int roundIfNeeded(T input);
};

percentage operator""_p (unsigned long long partOfHole);


template<typename T>
int percentage::roundIfNeeded(T input)
{
  input = std::min<T>(100, input);
  input = std::max<T>(0,   input);

  return static_cast<int>(input);
}
