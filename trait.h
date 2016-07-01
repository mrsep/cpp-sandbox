
enum class source {
  hand,
  face 
};

template <source S>
struct Type;

template <source S>
struct selectS{
  using ele = bool;
  using type = bool;
};

template <>
struct selectS<source::hand> {
  using ele = int;
  using type = Type<source::hand>;
};

template <>
struct selectS<source::face> {
  using ele = float;
  using type = Type<source::face>;
};

// any other type A
template <source S>
struct A : public selectS<S> {
  ele* p;
};

// the Type type
template <source S>
struct Type : selectS<S> {

  int a;
};

struct Ahand : public A<source::hand> {

};
