#pragma once
#include <thread>
#include <chrono>
#include <queue>
#include <functional>
#include <iostream>

namespace ec_impl {

  // the type of a task

  template <typename C>
  struct task {
    // the type of a function representing an action
    using action_type = std::function<void(C)>;
    using clock = std::chrono::system_clock;

    // task data
    clock::time_point timepoint; // the earliest timepoint for calling the action
    action_type action;          // the action to perform

    // comparison of tasks is delegated to the comparison of their timepoints
    bool operator>(const task& other) const {
      return timepoint > other.timepoint;
    }
  };

  // the type of a task queue
  
  template <typename C>
  class task_queue {
  private:
    using task_queue_t = std::priority_queue<task<C>, std::vector<task<C>>, std::greater<task<C>>>;
    task_queue_t _queue;
    const C& _c;

  public:
    // ctor
    task_queue(C& c) : _c(c) {}

    // add a new task to the queue
    void schedule_task(task<C> t) { _queue.push(t); }
    void schedule_task(typename task<C>::clock::time_point t, typename task<C>::action_type a) {
      schedule_task({t,a});
    }

    // run all tasks which are due to the given timepoint
    void run_tasks(task<C>::clock::time_point tp) {
      while ((!_queue.empty()) && (tp > _queue.top().timepoint)) {
        auto t = _queue.top();  // get the most due task
        _queue.pop();           // remove it from the queue
        t.action(_c);           // execute the tasks action
      }
    }

    bool empty() { return _queue.empty(); }
  };

}

struct Behaviour {
  int data;

  ec_impl::task_queue<Behaviour> tq;

  Behaviour() : tq(*this) {}
  void printA() { std::cout << "A: " << data << std::endl;}
  void printB() { std::cout << "B: " << data << std::endl;}
  void printC() { std::cout << "C: " << data << std::endl;}
};

int main() {

  using clock = ec_impl::task<Behaviour>::clock;

  // construct Behaviour and task_queue
  Behaviour c; c.data = 42;

  // schedule tasks
  c.tq.schedule_task(clock::now() + std::chrono::seconds{10}, &Behaviour::printA);
  c.tq.schedule_task(clock::now() + std::chrono::seconds{2}, &Behaviour::printB);
  c.tq.schedule_task(clock::now() + std::chrono::seconds{5}, &Behaviour::printC);

  // process
  while (!c.tq.empty()) {
    clock::time_point t = clock::now();

    c.tq.run_tasks(t);

    std::this_thread::sleep_for(std::chrono::milliseconds{500});
  }
}
