#pragma once
#include <string>
#include <iostream>
#include "namespaces_val.h"

namespace space {

  void print() {
    cout << val << endl;
  }
}

int main() {
  
  space::print();

  return 0;
}
