#include <iostream>

bool predicate() {
  std::cout << "predicate called" << std::endl;
  return true;
}

int main() {

  bool x = false;
  x &= predicate();

}
