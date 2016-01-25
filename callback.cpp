#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <future>
#include <chrono>

using callback_type = std::function<void(std::string)>;

void print_callback(std::string str) {
  std::cout << str << std::endl;
}

void threadProc(callback_type callback) {
  
  // perform some calculation

  // report to the caller
  callback("This is my message to you!"); 
}

int main() {
  // please use this callback function
  callback_type my_callback = print_callback;

  // starts a thread at threadProc with the callback my_callback
  std::thread t {threadProc,my_callback};
  
  // asynchronously start a thread at threadProc
  {
    auto f = std::async(threadProc,my_callback);
  }

  // sleep
  std::this_thread::sleep_for(std::chrono::seconds{1});
  
  // wait for the threads end
  t.join();

  return 0;
}

