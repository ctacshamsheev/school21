#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

#define TEMPLATE_VECTOR template <class T, class Alloc>
namespace s21 {
template <class T, class Alloc = std::allocator<T>>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using AllocTraits = std::allocator_traits<Alloc>;
  class Iterator {
    using difference_type = std::ptrdiff_t;

   public:
    Iterator() : ptr_(nullptr) {}
    Iterator(T *data_ptr) : ptr_(data_ptr) {}
    Iterator(const Iterator &other) { *this = other; }
    ~Iterator() {}

    Iterator &operator=(const Iterator &other) {
      ptr_ = other.ptr_;
      return *this;
    }
    Iterator &operator++() {
      ptr_++;
      return *this;
    }
    Iterator &operator--() {
      ptr_--;
      return *this;
    }
    Iterator &operator+=(int n) {
      ptr_ += n;
      return *this;
    }
    Iterator &operator-=(int n) {
      ptr_ -= n;
      return *this;
    }
    Iterator operator+(int n) {
      Iterator it = *this;
      return it += n;
    }
    Iterator operator-(int n) {
      Iterator it = *this;
      return it -= n;
    }
    bool operator==(const Iterator &other) { return ptr_ == other.ptr_; }
    bool operator!=(const Iterator &other) { return !(ptr_ == other.ptr_); }
    bool operator>(const Iterator &other) { return ptr_ > other.ptr_; }
    bool operator<(const Iterator &other) { return ptr_ < other.ptr_; }
    bool operator>=(const Iterator &other) { return !(ptr_ < other.ptr_); }
    bool operator<=(const Iterator &other) { return !(ptr_ > other.ptr_); }
    reference operator*() { return *ptr_; }
    const_reference operator*() const { return *ptr_; }
    reference operator[](size_type n) { return *(ptr_ + n); }

   private:
    T *ptr_;
  };
  using IterTraits = std::iterator_traits<Iterator>;

  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &other);
  Vector(Vector &&other);
  ~Vector();

  Vector &operator=(Vector &&other);
  Vector &operator=(const Vector &other);
  reference at(size_type position_);
  reference operator[](size_type position_);
  const_reference operator[](size_type position_) const;
  const_reference front();
  const_reference back();
  Iterator data();

  Iterator begin();
  Iterator end();

  bool empty() { return size_ == 0; }
  size_type size() const { return size_; };
  size_type capacity() const { return capacity_; };
  size_type max_size();
  void reserve(size_type new_capacity);
  void resize(size_type new_size);
  void shrink_to_fit();

  void clear();
  Iterator insert(Iterator position, const_reference value);
  void erase(Iterator position);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  template <class... Args>
  Iterator emplace(const Iterator position, Args &&...args);
  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  T *realloc_memory(Vector<T, Alloc> &v, size_t n);
  Alloc allocator_;
  size_type size_;
  size_type capacity_;
  T *data_;
};

}  // namespace s21

#include "s21_vector.tpp"
