#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <queue>


struct task {
  using clock = std::chrono::system_clock;
  using action_type = std::function<void(void)>;
  clock::time_point timepoint;
  action_type action;

  bool operator>(const task& other) const {
    return timepoint > other.timepoint;
  }
};

using task_queue = std::priority_queue<task, std::vector<task>, std::greater<task>>;

int main() {
  task_queue schedule{};
  
  task t1{task::clock::now() + std::chrono::seconds{2}, [](){std::cout << "action t1" << std::endl;}};
  std::this_thread::sleep_for(std::chrono::milliseconds{999});
  task t2{task::clock::now() + std::chrono::seconds{1}, [](){std::cout << "action t2" << std::endl;}};
  std::this_thread::sleep_for(std::chrono::milliseconds{200});
  task t3{task::clock::now() + std::chrono::seconds{3}, [](){std::cout << "action t3" << std::endl;}};

  schedule.push(t1);
  schedule.push(t3);
  schedule.push(t2);

  while (! schedule.empty()) {
    auto t = schedule.top();
    if (task::clock::now() > t.timepoint) {
      schedule.pop();
      t.action();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds{100});
  }
  return 0;
}

