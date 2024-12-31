#include "key.h"
#include "keybind.h"
#include <cassert>
#include <ios>
#include <iostream>
#include <unordered_set>

void lam(){}
int main (int argc, char *argv[]) {
  

  assert((keybind {10,10,lam} == key {10,10}));
  keybind kb {10,10,lam};
  key k {10,10};

  assert(keybind::wasDeclared(k));

  
  return 0;
}
