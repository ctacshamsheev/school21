#pragma once

#include <initializer_list>
#include <iostream>

#define TEMPLATE_ARRAY template <class T, std::size_t N>
namespace s21 {
template <class T, std::size_t N>
class Array {
 public:
  //* === Member type ===
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

  //* === Member functions ===
  Array() : size_(N) {}
  explicit Array(std::initializer_list<value_type> const &items);
  Array(const Array &other);
  Array(Array &&other);
  ~Array() {}
  Array &operator=(Array &&other);
  Array &operator=(const Array &other);

  //* === Element functions ===
  reference at(size_type position_);
  reference operator[](size_type position_) { return data_[position_]; }
  const_reference front() { return data_[0]; }
  const_reference back() { return data_[size_ - 1]; }
  iterator data() { return data_; }

  //* === Iterators functions ===
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }

  //* === Capacity functions ===
  bool empty() { return bool(!size_); }
  size_type size() { return size_; }
  size_type max_size() { return size_; }

  //* === Modifiers functions ===
  void swap(Array &other);
  void fill(const_reference value);

 private:
  size_t size_ = N;
  T data_[N]{};
};

}  // namespace s21

#include "s21_array.tpp"
