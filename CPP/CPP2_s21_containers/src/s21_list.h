#pragma once

#include <cmath>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;
  class ConstListIterator;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  struct Node {
    value_type _data;
    Node* _previous;
    Node* _next;
  };

 private:
  Node* _inception;
  Node* _finish;
  Node* _base_node;
  size_type _size;

 public:
  class ListIterator {
   public:
    Node* n_current;
    // constructors & destructor
    ListIterator();
    explicit ListIterator(const list<T>& other);
    explicit ListIterator(Node* _n_current);

    // overload operators
    reference operator*();
    ListIterator& operator++();
    ListIterator operator++(int);
    ListIterator& operator--();
    ListIterator operator--(int);
    bool operator==(const ListIterator& other);
    bool operator!=(const ListIterator& other);
  };

  class ConstListIterator : public ListIterator {
   public:
    ConstListIterator() : ConstListIterator::n_current(nullptr) {}
    const_reference operator*() { return this->n_current->_data; }
  };  // namespace s21

  // iterator
  iterator begin();
  iterator end();

 public:
  // constructors & destructor
  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const& items);
  list(const list& other);
  list(list&& other);
  ~list();

  // operators
  list& operator=(list&& other);
  list& operator=(const list& other);

  // Element access
  const_reference front();
  const_reference back();

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // Bonus functions
  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args);

  template <class... Args>
  void emplace_back(Args&&... args);

  template <class... Args>
  void emplace_front(Args&&... args);
};
}  // namespace s21

#include "s21_list.tpp"
