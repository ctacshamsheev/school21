namespace s21 {

//! === Member functions ===

TEMPLATE_VECTOR
Vector<T, Alloc>::Vector() : size_(0), capacity_(0), data_(nullptr) {}

TEMPLATE_VECTOR
Vector<T, Alloc>::Vector(size_type n) : size_(n), capacity_(n) {
  data_ = AllocTraits::allocate(allocator_, n);
  for (size_t i = 0; i < size_; i++) {
    AllocTraits::construct(allocator_, data_ + i, T());
  }
}

TEMPLATE_VECTOR
Vector<T, Alloc>::Vector(std::initializer_list<value_type> const &items) {
  capacity_ = size_ = items.size();
  data_ = AllocTraits::allocate(allocator_, size_);
  const value_type *ptr_ = items.begin();
  for (size_t i = 0; i < size_; i++) {
    AllocTraits::construct(allocator_, data_ + i, *(ptr_ + i));
  }
}

TEMPLATE_VECTOR
Vector<T, Alloc>::Vector(const Vector &other)
    : allocator_(other.allocator_),
      size_(other.size_),
      capacity_(other.capacity_) {
  data_ = AllocTraits::allocate(allocator_, capacity_);
  for (size_t i = 0; i < size_; i++) {
    AllocTraits::construct(allocator_, data_ + i, other[i]);
  }
}

TEMPLATE_VECTOR
Vector<T, Alloc>::Vector(Vector &&other)
    : allocator_(other.allocator_),
      size_(other.size_),
      capacity_(other.capacity_),
      data_(nullptr) {
  std::swap(data_, other.data_);
}

TEMPLATE_VECTOR Vector<T, Alloc>::~Vector() {
  for (size_t i = 0; i < size_; i++) {
    AllocTraits::destroy(allocator_, data_ + i);
  }
  AllocTraits::deallocate(allocator_, data_, capacity_);
}

TEMPLATE_VECTOR
Vector<T, Alloc> &Vector<T, Alloc>::operator=(Vector &&other) {
  try {
    data_ = realloc_memory(this, other.capacity_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    for (size_t i = 0; i < size_; i++) {
      AllocTraits::construct(allocator_, data_ + i, *(other.data_ + i));
    }
    other.capacity_ = 0;
    other.size_ = 0;
    return *this;
  } catch (...) {
    throw;
  }
}

TEMPLATE_VECTOR
Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector &other) {
  if (this != &other) {
    try {
      data_ = realloc_memory(this, other.capacity_);
      capacity_ = other.capacity_;
      size_ = other.size_;
      for (size_t i = 0; i < size_; i++) {
        AllocTraits::construct(allocator_, data_ + i, *(other.data_ + i));
      }
    } catch (...) {
      throw;
    }
  }
  return *this;
}

//! === Element access ===

TEMPLATE_VECTOR
typename Vector<T, Alloc>::reference Vector<T, Alloc>::at(size_type position) {
  if (position >= size_)
    throw std::out_of_range("index is out of vector range");
  return data_[position];
}

TEMPLATE_VECTOR
typename Vector<T, Alloc>::reference Vector<T, Alloc>::operator[](
    size_type position) {
  return data_[position];
}

TEMPLATE_VECTOR
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::operator[](
    size_type position) const {
  return data_[position];
}

TEMPLATE_VECTOR
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::front() {
  return *(begin());
}

TEMPLATE_VECTOR
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::back() {
  return *(--end());
}

TEMPLATE_VECTOR
typename Vector<T, Alloc>::VectorIterator Vector<T, Alloc>::data() {
  return begin();
}

//! === Capacity functions ===

TEMPLATE_VECTOR
T *Vector<T, Alloc>::realloc_memory(Vector<T, Alloc> *v, size_t n) {
  // выделяем новую память
  T *new_data = AllocTraits::allocate(v->allocator_, n);
  for (size_t i = 0; i < v->size_; i++) {
    try {
      // вызываем конструкторы новых объектов
      AllocTraits::construct(v->allocator_, new_data + i, v->data_[i]);
      // вызываем деструкторы старых объектов
      AllocTraits::destroy(v->allocator_, v->data_ + i);
    } catch (...) {
      // возвращаем вектор в исходное состояние
      for (size_t j = 0; j < i; j++) {
        AllocTraits::destroy(v->allocator_, new_data + j);
      }
      AllocTraits::deallocate(v->allocator_, new_data, n);
      throw;
    }
  }
  // очищаем старую память
  AllocTraits::deallocate(v->allocator_, v->data_, v->capacity_);
  return new_data;
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::reserve(size_type new_capacity) {
  if (new_capacity <= capacity_) return;
  try {
    data_ = realloc_memory(this, new_capacity);
    capacity_ = new_capacity;
  } catch (...) {
    throw;
  }
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::shrink_to_fit() {
  if (capacity_ <= size_) return;
  try {
    data_ = realloc_memory(this, size_);
    capacity_ = size_;
  } catch (...) {
    throw;
  }
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::resize(size_type new_size) {
  if (new_size > capacity_) {
    try {
      reserve(new_size);
    } catch (...) {
      throw;
    }
    for (size_t i = size_; i < new_size; i++) {
      AllocTraits::construct(allocator_, data_ + i, T());
    }
  } else {
    if (new_size > size_) {
      for (size_t i = size_; i < new_size; i++) {
        AllocTraits::construct(allocator_, data_ + i, T());
      }
    } else {
      for (size_t i = size_ - 1; i > new_size - 1; i--) {
        AllocTraits::destroy(allocator_, data_ + i);
      }
    }
  }
  size_ = new_size;
}

//! === Modifiers functions ===

TEMPLATE_VECTOR
typename Vector<T, Alloc>::VectorIterator Vector<T, Alloc>::insert(
    VectorIterator position, const_reference value) {
  try {
    if (empty() && position == begin()) {  // Если вектор пустой
      push_back(value);
      return begin();
    }
    VectorIterator it = --end();
    value_type tmp = *it;  // сохранение последнего эл-а
    size_t index = size_ - 1;
    // Перемещение эл-в
    while (it != position) {
      --it;
      data_[index--] = std::move(*it);
    }
    data_[index] = value;
    push_back(tmp);
    return (begin() + index);
  } catch (...) {
    throw;
  }
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::erase(VectorIterator position) {
  if (!empty()) {
    VectorIterator it_ = position + 1;
    while (it_ != end()) {
      *position = std::move(*it_);
      ++position;
      ++it_;
    }
    AllocTraits::destroy(allocator_, (data_ + (--size_)));
  }
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::push_back(const_reference value) {
  try {
    if (capacity_ == 0) {
      reserve(1);
    } else if (size_ >= capacity_) {
      reserve(capacity_ << 1);
    }
    AllocTraits::construct(allocator_, data_ + size_, value);
    ++size_;
  } catch (...) {
    throw;
  }
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::pop_back() {
  if (size_ > 0) {
    AllocTraits::destroy(allocator_, data_ + (--size_));
  }
}

TEMPLATE_VECTOR
void Vector<T, Alloc>::swap(Vector &other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(data_, other.data_);
}

//! === Bonus ===

template <class T, class Alloc>
template <class... Args>
void Vector<T, Alloc>::emplace_back(Args &&...args) {
  try {
    push_back(T(args...));
  } catch (...) {
    throw;
  }
}

template <class T, class Alloc>
template <class... Args>
typename Vector<T, Alloc>::VectorIterator Vector<T, Alloc>::emplace(
    const VectorIterator position, Args &&...args) {
  try {
    auto it = insert(position, T(args...));
    return it;
  } catch (...) {
    throw;
  }
}
}  // namespace s21
