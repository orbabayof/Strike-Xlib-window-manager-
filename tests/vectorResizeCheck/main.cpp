#include <iostream>
#include <vector>
struct dummy 
{
  int a;

  dummy() = delete;
  dummy(int b): a { b } {}
  
};

std::ostream& operator<<(std::ostream& out, dummy d)
{
  return (out << d.a);
}


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
    out << "{ ";
    bool comma { false };

    for (auto e : v)
    {
        if (comma)
            out << ", ";
        else
            comma = true;

        out << e;

    }

    return out << " }";
}

int main (int argc, char *argv[]) 
{
  using std::vector;
  vector<dummy> v;
  for(int i { 6 }; i > 0; --i)
    v.emplace_back(1);

  std::cout << v;
  return 0;
}
