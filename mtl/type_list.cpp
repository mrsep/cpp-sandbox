#include "type_list.h"
#include <typeinfo>

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
