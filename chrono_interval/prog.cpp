#include <iostream>
#include "interval.h"
#include "so.h"

int main() {

  Base<SomeType> b(2,2.5);
  Derived d(1, 1.5);
  Derived db(b);

  std::cout << d.member1 << d.member2 << std::endl;
  std::cout << db.member1 << db.member2 << std::endl;
  d.Base = b;
  std::cout << d.member1 << d.member2 << std::endl;

  using clock = std::chrono::steady_clock;

  chrono_ival<clock> i(clock::now(), clock::now());
  Event e( i );

  std::cout << "Base: " << sizeof(b) << std::endl;
  std::cout << "Derived: " << sizeof(d) << std::endl;
  std::cout << "timepoint: " << sizeof(clock::now()) << std::endl;
  std::cout << "ival: " << sizeof(i) << std::endl;
  std::cout << "Event: " << sizeof(e) << std::endl;

  return 0;
}

