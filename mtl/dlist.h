#pragma once

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
  inline bool is_head() { return prev == nullptr; }
  inline bool is_tail() { return next == nullptr; }

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
    //std::cout << "dlist ctor called" << std::endl;
  }

  virtual ~dlist() {
    if (is_head()) { head = next; }
    else { prev->next = next; }
    if (is_tail()) { tail = prev; }
    else { next->prev = prev; }
    //std::cout << "dlist dtor called" << std::endl;
  }

// public interface
public:
  inline T* Next() { return next; }
  inline T* Prev() { return prev; }
  static inline T* Head() { return head; }
  static inline T* Tail() { return tail; }
  static inline bool is_empty() { return head == nullptr && tail == nullptr; }

  // iterator

  // what about other constructors, operators?
};


// example type
struct A : public dlist<A> {

  int x,y;

  A() : A(0,0) {}
  A(int x, int y) : x(x), y(y) {}
};

// init static data members
template <typename T> T* dlist<T>::head = static_cast<T*>(nullptr);
template <typename T> T* dlist<T>::tail = static_cast<T*>(nullptr);

