#include "dlist.h"
#include <iostream>

int main() {

  A a(1,1);
  A b(2,2);
  A c(3,3);
  A d(4,4);

  std::cout << a.x << std::endl;
  std::cout << a.Next().Next().x << std::endl;
  b.~A();
  std::cout << a.Next().Next().x << std::endl;
  std::cout << a.Next().Prev().x << std::endl;

  return 0;
}

