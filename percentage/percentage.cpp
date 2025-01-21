#include <percentage.h>

percentage::percentage(unsigned long long partOfHole): m_partOfHole { roundIfNeeded(partOfHole)  } {}

percentage::percentage(int partOfHole): percentage(static_cast<unsigned long long>(partOfHole)) {}

int operator*(int XwidthOrHeight, percentage p)
{
  return (p * XwidthOrHeight)/100;
}
int operator*(percentage p, int XwidthOrHeight)
{
  return operator*(XwidthOrHeight, p);
}

percentage operator""_p (unsigned long long partOfHole)
{
  return {partOfHole};
}
