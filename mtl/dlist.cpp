#include "dlist.h"
#include <iostream>
#include <list>
#include <vector>
#include <memory>

void test_next(const std::unique_ptr<A>& a) {
  A* i = a.get();
  while (i != nullptr) {
    std::cout << i->x << "\t";
    i = i->Next();
  }
  std::cout << std::endl;
}

void test_prev(const std::unique_ptr<A>& a) {
  A* i = a.get();
  while (i != nullptr) {
    std::cout << i->x << "\t";
    i = i->Prev();
  }
  std::cout << std::endl;
}

void test_dlist(const std::list<std::unique_ptr<A>>& v) {
  if (!v.empty()) {
    auto& f = v.front();
    test_next(f);
    auto& b = v.back();
    test_prev(b);
  }
}

int main() {

  A* a = new A(0,0);
  std::cout << sizeof(a) << std::endl;
  std::list<std::unique_ptr<A>> v;

  v.push_back(std::unique_ptr<A>(new A{1,1}));
  v.push_back(std::unique_ptr<A>(new A{2,2}));
  v.push_back(std::unique_ptr<A>(new A{3,3}));
  v.push_back(std::unique_ptr<A>(new A{4,4}));
  A* b = new A(10,10);
  test_dlist(v);

  std::cout << "cleanup" << std::endl;
  v.pop_front();
  v.pop_back();
  //v.pop_back();
  v.pop_front();

  std::cout << "dlist cleanup" << std::endl;
  //delete a; delete b;
  
  delete a->Next();
  //delete A::Head();
  delete A::Tail();


  test_dlist(v);

  std::cout << "automatic cleanup" << std::endl;
  return 0;
}

