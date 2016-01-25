#include <iostream>

namespace space {

  enum class color : int {
    red, blue, green, NUMBER_OF_COLORS 
  };
}

using namespace space;

int main() {
  color c = color::blue;

  std::cout << int(c) << std::endl;
  return 0;
}

