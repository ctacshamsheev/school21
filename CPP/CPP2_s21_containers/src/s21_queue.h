#pragma once

namespace s21 {
template <typename T>
class Queue {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  struct Node {
    value_type _data;
    Node* _next;
  };

 private:
  Node* _inception;
  Node* _finish;
  size_type _size;

 public:
  // constructors & destructor
  Queue();
  explicit Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& other);
  Queue(Queue&& other);
  ~Queue();

  // operators
  Queue& operator=(Queue&& other);
  Queue& operator=(const Queue& other);

  // Element access
  const_reference front() const { return _inception->_data; }
  const_reference back() const { return _finish->_data; }

  // Capacity
  bool empty() { return !_inception; }
  size_type size() { return _size; }

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Queue& other);

  // Bonus functions
  template <class... Args>
  void emplace_back(Args... args);
};

}  // namespace s21

#include "s21_queue.tpp"
