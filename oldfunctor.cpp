#include <iostream>
#include <string>

typedef void (*callback_type)(int val);

void fun(int val) {
  std::cout << val << std::endl;
}

int main() {

  std::cout << _MSC_VER << std::endl;

  callback_type callback = fun;

  callback(5);

  return 0;
}
