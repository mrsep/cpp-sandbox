#include <iostream>
#include <string>

struct P {
 P() {
  std::cout << "constructor" << std::endl;
 }

 P(std::string str) {
  std::cout << "constructor" << str << std::endl;
 }

 ~P() {
  std::cout << "Deconstructor" << std::endl;	 
 }
};


int main() {

  //P p1;    // 1:1
  //P p2();  // 0:0
  //P p3{};  // 1:1
  //P p4 = P();  // 1:1
  P p5 = P(" haha"); // 1:2 + one copy constructor call
  // explenation of p5:
  // after the first instance got created and assigned/copy constructed to p5, it gets destructed!!!

  std::cout << "almost out of scope" << std::endl;
  return 0;
}

