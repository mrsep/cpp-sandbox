#include <iostream>


int main() {
  const int size = 8;
  double floating[size];
  
  std::cout.precision(8);

  floating[0] = 0.1;
  floating[1] = 0.4;
  floating[2] = 0.5;
  floating[3] = 0.6;
  floating[4] = 0.9;
  floating[5] = 0.999999;
  floating[6] = 0.9999999;
  floating[7] = 0.99999999;

  for (int i = 0; i < size; i++) {
    std::cout << i << ": double= " << floating[i] << " float= " << (float)floating[i] << " int-cast= " << (int)((float)floating[i]) << std::endl;
  }

  return 0;
}

