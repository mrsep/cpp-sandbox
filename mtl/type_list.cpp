#include "type_list.h"
#include <iostream>

// example types
struct A{ static void Print(int v) {std::cout << " A" << v;}};
struct B{ static void Print(int v) {std::cout << " B" << v;}};
struct C{ static void Print(int v) {std::cout << " C" << v;}};
struct D{ static void Print(int v) {std::cout << " D" << v;}};

int main()
{
  using EP_list = type_list<A, B, C, D>;

  Print_F<A,int>()(1);
  EP_list::type<1>::Print(2);
  std::cout << '\n' << "list size = " << EP_list::size << std::endl;

  for_each_type_impl<EP_list,Print_F,3,int>()(3); 
  for_each_type<EP_list,Print_F,int>(4);

  return 0;
}
