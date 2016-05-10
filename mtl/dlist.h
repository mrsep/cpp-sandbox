#pragma once
#include <iostream>

template <typename T>
class dlist {

private:
  // data members
  T* prev = nullptr;
  T* next = nullptr;
  static T* head;
  static T* tail;

private:
  // helper functions
  bool inline is_head() { return prev == nullptr; }
  bool inline is_tail() { return next == nullptr; }
  bool inline is_empty() { return head == nullptr && tail == nullptr; }

public:
  // ctor & dtor
  dlist() {
    T* T_this = static_cast<T*>(this);

    if (is_empty()) {
      head = T_this;
      tail = T_this;
    }
    else {
      tail->next = T_this;
      prev = tail;
      tail = T_this;
    }
  }

  virtual ~dlist() {
    if (is_head()) { head = next; }
    else { prev->next = next; }
    if (is_tail()) { tail = prev; }
    else { next->prev = prev; }
  }

// public interface
public:
  T& Next() { return *next; }
  T& Prev() { return *prev; }
  T& Head() { return *head; }
  T& Tail() { return *tail; }

  // iterator
};

struct A : public dlist<A> {

  int x,y;

  A() : A(0,0) {}
  A(int x, int y) : x(x), y(y) {}
};

// init static data members
template <typename T> T* dlist<T>::head = static_cast<T*>(nullptr);
template <typename T> T* dlist<T>::tail = static_cast<T*>(nullptr);

