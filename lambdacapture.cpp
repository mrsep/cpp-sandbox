#include <iostream>
#include <functional> // header for functional programming

// compile with $ cl /EHsc file.cpp

// define the type (signature) of a function
using callback_type = std::function<void (int,double)>;

// define a function pointer, or: callback is the name of a function with signature callback_type
callback_type callback;

// a global variable
int global;

// an ordinary function
void f(int x, double y) { 
  std::cout << "Hello Space! " << x+y-global << std::endl; 
}


int main() {
  int local = 1;
  global = local; // set the value of the global variable

  // define a named lambda function which takes two arguments and captures the variable local
  auto fun = [local] (int x, double y) { std::cout << "Hello World! " << x+y-local << std::endl; };

  // call the lambda function directly
  fun(0,0.0);

  // let the function callback be the lambda fun
  callback = fun;

  // call the lambda function through the function pointer
  callback(0,0.0);

  // let the function be the ordinary function f
  callback = f;

  // call the ordinary function through the function pointer
  callback(0,0.0);

  return 0;
}
