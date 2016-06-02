#pragma once
#include <tuple>

// type list
template <typename ... Args>
struct type_list
{
  // the type of the underlying tuple 
  using tuple_type = std::tuple<Args ...>;

  // obtain the N-th type in the type list
  template <std::size_t N>
  using type = typename std::tuple_element<N, tuple_type>::type;

  // number of elements in the type list
  static const std::size_t size = std::tuple_size<tuple_type>::value;
};

// example Functor, matching the interface of the example classes
template <typename T, typename ... Arg>
struct Print_F {
  void operator()(Arg ... args) {
    T::Print(args ... );
  }
};

// implementation of for each taking a type list, a Functor and arguments for the functor
// general case
// L .. type list
// F .. functor as template template parameter
// N .. current element of the type_list to process
// Arg .. variable number of parameters of the functor
template <typename L, template <typename, typename ...> class F, std::size_t N, typename ... Arg>
struct for_each_type_impl {
  void operator()(Arg ... args) {
    using ele_type = typename L::template type<N>;

    for_each_type_impl<L,F,N-1,Arg ...>()(args ...);
    
    F<ele_type, Arg ...>()(args ...);
  }
};

// break case
template <typename L, template <typename, typename ...> class F, typename ... Arg>
struct for_each_type_impl<L,F,0,Arg ...> {
  using ele_type = typename L::template type<0>;

  void operator()(Arg ... args) {
    F<ele_type, Arg ...>()(args ...);
  }
};

// function taking a type_list, a functor, argument types and their values
// and executes the functor for each type in the list using the arugments
// requires that each type in the type list satisfies the requirements of the functor
template <typename L, template <typename, typename ...> class F, typename ... Arg>
void for_each_type(Arg ... args) {
  for_each_type_impl<L,F,L::size-1,Arg ...>()(args ...);
}

