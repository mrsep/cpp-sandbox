#include "Singleton.h"

struct A_config {
  A_config() : A_config(0) {}
  A_config(int v) : val(v) {}
  int val;

  friend bool operator!=(const A_config& lhs, const A_config& rhs) {
    return lhs.val != rhs.val;
  }
};

struct A : public Singleton<A,A_config> {
  const int data;
  void Do() {std::cout << "Do = " << data << std::endl;}

  private:
  // singleton necessities
  friend struct Singleton<A,A_config>;
  A(const A_config& config) : data(config.val) {
    std::cout << "A::ctor " << config.val << std::endl;}
};

int f() {

  A_config c;
  A_config c1(1);
  A_config c2(2);

  //A::Instance(c);
  //A::Instance().Do();
  //A::Instance().Do();
  //A::Instance().Do();
  //A::Instance(c1).Do();
  //A::Instance(c2).Do();
  //A::Instance(c2).Do();
  std::cout << "do something else" << std::endl;

  A::Instance().Do();
  return 0;
}

