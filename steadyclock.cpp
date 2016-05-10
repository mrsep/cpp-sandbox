#include <chrono>
#include <iostream>
#include <thread>


int main() {
  using clock = std::chrono::steady_clock;

  while (true) {
    clock::time_point t1 = clock::now();
    std::this_thread::sleep_for(std::chrono::nanoseconds{1});

    clock::time_point t2 = clock::now();

    clock::duration d = t2-t1;
    if (d.count() == 0) {
      std::cout << "no time passed!" << std::endl;
    }

  };
  return 0;
}

