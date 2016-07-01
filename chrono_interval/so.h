#pragma once

struct SomeType {
  using type1 = int;
  using type2 = float;
};

template <typename T>
struct Base {
  using value_t1 = typename T::type1;
  using value_t2 = typename T::type2;

  value_t1 member1;
  value_t2 member2;

  Base() : member1(), member2() {}
  Base(value_t1 m1, value_t2 m2) : member1(m1), member2(m2) {}
  virtual ~Base() = default;
};

struct Derived : public Base<SomeType> {

  Derived(value_t1 m1, value_t2 m2) : Base(m1,m2) {}
  Derived(Base<SomeType> b) : Base(b) {}

  void reset(value_t1 m1, value_t2 m2) {
    Base(m1,m2);
  }
};
