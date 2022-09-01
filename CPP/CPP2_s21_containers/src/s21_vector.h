#pragma once

#include <initializer_list>
#include <iostream>

#define TEMPLATE_VECTOR template <class T, class Alloc>
namespace s21 {
template <class T, class Alloc = std::allocator<T>>
class Vector {
 public:
  //* === Member type ===
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using AllocTraits = std::allocator_traits<Alloc>;

  //* === Class iterator ===
  class VectorIterator {
    using difference_type = std::ptrdiff_t;

   public:
    VectorIterator() : ptr_(nullptr) {}
    explicit VectorIterator(T *data_ptr) : ptr_(data_ptr) {}
    VectorIterator(const VectorIterator &other) : ptr_(other.ptr_) {}
    ~VectorIterator() {}

    VectorIterator &operator=(const VectorIterator &other) {
      ptr_ = other.ptr_;
      return *this;
    }
    VectorIterator &operator++() {
      ++ptr_;
      return *this;
    }
    VectorIterator &operator--() {
      --ptr_;
      return *this;
    }
    VectorIterator &operator+=(int n) {
      ptr_ += n;
      return *this;
    }
    VectorIterator &operator-=(int n) {
      ptr_ -= n;
      return *this;
    }
    VectorIterator operator+(int n) {
      VectorIterator it = *this;
      return it += n;
    }
    VectorIterator operator-(int n) {
      VectorIterator it = *this;
      return it -= n;
    }
    bool operator==(const VectorIterator &other) { return ptr_ == other.ptr_; }
    bool operator!=(const VectorIterator &other) {
      return !(ptr_ == other.ptr_);
    }
    bool operator>(const VectorIterator &other) { return ptr_ > other.ptr_; }
    bool operator<(const VectorIterator &other) { return ptr_ < other.ptr_; }
    bool operator>=(const VectorIterator &other) {
      return !(ptr_ < other.ptr_);
    }
    bool operator<=(const VectorIterator &other) {
      return !(ptr_ > other.ptr_);
    }
    reference operator*() { return *ptr_; }
    const_reference operator*() const { return *ptr_; }
    reference operator[](size_type n) { return *(ptr_ + n); }

   private:
    T *ptr_;
  };
  class ConstVectorIterator : public VectorIterator {
   public:
    ConstVectorIterator() : ptr_(nullptr) {}
    const_reference operator*() { return *ptr_; }
    const_reference operator[](size_type n) { return *(ptr_ + n); }

   private:
    T *ptr_;
  };

  //* === Member functions ===
  Vector();
  explicit Vector(size_type n);
  explicit Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &other);
  Vector(Vector &&other);
  ~Vector();
  Vector &operator=(Vector &&other);
  Vector &operator=(const Vector &other);

  //* === Member functions ===
  reference at(size_type position_);
  reference operator[](size_type position_);
  const_reference operator[](size_type position_) const;
  const_reference front();
  const_reference back();
  VectorIterator data();

  //* === Iterators functions ===
  VectorIterator begin() { return VectorIterator(data_); }
  VectorIterator end() { return VectorIterator(data_ + size()); }

  //* === Capacity functions ===
  bool empty() { return size_ == 0; }
  size_type size() const { return size_; }
  size_type capacity() const { return capacity_; }
  size_type max_size() { return allocator_.max_size(); }
  void reserve(size_type new_capacity);
  void shrink_to_fit();
  void resize(size_type new_size);

  //* === Modifiers functions ===
  void clear() { resize(0); }
  VectorIterator insert(VectorIterator position, const_reference value);
  void erase(VectorIterator position);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  //* === Bonus ===
  template <class... Args>
  VectorIterator emplace(const VectorIterator position, Args &&...args);
  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  T *realloc_memory(Vector<T, Alloc> *v, size_t n);
  Alloc allocator_;
  size_type size_;
  size_type capacity_;
  T *data_;
};

}  // namespace s21

#include "s21_vector.tpp"
