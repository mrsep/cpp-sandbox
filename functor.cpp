#include <iostream>
#include <functional>
#include <array>

template <int N>
using func = std::function<std::array<int,N>(bool)>;

func<1> one_ret;
func<2> two_ret;
func<3> three_ret;

std::array<int,1> one_fun(bool val) {
  std::array<int,1> res{42};
  return res;
}

struct A {
  std::array<int,3> three_fun(bool val) {
    std::array<int,3> res{7,23,42};
    return res;
  }
};

int main() {
  
  // assign free functions
  one_ret = one_fun;
  two_ret = [](bool val) { return std::array<int,2>{1,2}; };

  // assign member function
  A a;
  three_ret = std::bind(&A::three_fun, &a, std::placeholders::_1); // redirect the arguments

  std::array<int,1> one_result = one_ret(true);
  std::array<int,2> two_result = two_ret(true);
  std::array<int,3> three_result = three_ret(true);

  std::cout << one_result[0] << std::endl;
  std::cout << two_result[0] << two_result[1] << std::endl;
  std::cout << three_result[0] << three_result[1] << three_result[2] << std::endl;

}
