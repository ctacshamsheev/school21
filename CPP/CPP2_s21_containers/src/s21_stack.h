#pragma once

namespace s21 {
template <typename T>
class Stack {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  struct Node {
    value_type _data;
    Node* _next;
  };

 private:
  Node* _roof;
  size_type _size;

 public:
  // constructors & destructor
  Stack();
  explicit Stack(std::initializer_list<value_type> const& items);
  Stack(const Stack& other);
  Stack(Stack&& other);
  ~Stack();

  // operators
  Stack& operator=(Stack&& other);
  Stack& operator=(const Stack& other);

  // Element access
  const_reference top() const { return _roof->_data; }

  // Capacity
  bool empty() { return !_roof; }
  size_type size() { return _size; }

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Stack& other);

  // Bonus functions
  template <class... Args>
  void emplace_front(Args... args);
};

}  // namespace s21

#include "s21_stack.tpp"
