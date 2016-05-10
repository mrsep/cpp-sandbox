#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int compute(float val) {
  std::this_thread::sleep_for(std::chrono::seconds{1});

  return (int)val;
}


int main() {
  std::future<int> handle = std::async(compute, 5.0f);

  int res = handle.get();

  std::cout << "result:" << res << std::endl;
  std::cout << "result:" << res << std::endl;
  return 0;
}

