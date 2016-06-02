#pragma once
#include <iostream>
#include <tuple>
#include <functional>

// example types
struct A{ static void Print(int v) {std::cout << " A" << v;}};
struct B{ static void Print(int v) {std::cout << " B" << v;}};
struct C{ static void Print(int v) {std::cout << " C" << v;}};
struct D{ static void Print(int v) {std::cout << " D" << v;}};

// type list
template <typename ... Args>
struct type_list
{
  // the type of the underlying tuple 
  using tuple_type = std::tuple<Args ...>;

  // obtain the N-th type in the type list
  template <std::size_t N>
  using type = typename std::tuple_element<N, tuple_type>::type;

  // size of elements in the type list
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
template <typename L, template <typename, typename ...> class F, std::size_t N, typename ... Arg>
struct for_each_type_impl {

  void operator()(Arg ... args) {
    for_each_type_impl<L,F,N-1,Arg ...>()(args ...);
    
    F<L::type<N>, Arg ...>()(args ...);
  }
};

template <typename L, template <typename, typename ...> class F, typename ... Arg>
struct for_each_type_impl<L,F,0,Arg ...> {

  void operator()(Arg ... args) {
    F<L::type<0>, Arg ...>()(args ...);
  }
};

template <typename L, template <typename, typename ...> class F, typename ... Arg>
void for_each_type(Arg ... args) {
  for_each_type_impl<L,F,L::size-1,Arg ...>()(args ...);
}

