namespace s21 {
#pragma once

TEMPLATE_ARRAY
Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  try {
    if (items.size() > size_)
      throw std::out_of_range("initializer_list size is too large");
    std::copy(items.begin(), items.end(), data_);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    exit(1);
  }
}

TEMPLATE_ARRAY
Array<T, N>::Array(const Array &other) {
  try {
    if (size_ != other.size_) {
      throw std::out_of_range("container size is not equal");
    }
    std::copy(other.data_, other.data_ + size_, data_);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    exit(1);
  }
}

TEMPLATE_ARRAY
Array<T, N>::Array(Array &&other) {
  try {
    if (size_ != other.size_) {
      throw std::out_of_range("container size is not equal");
    }
    std::move(other.data_, other.data_ + size_, data_);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    exit(1);
  }
}

TEMPLATE_ARRAY
Array<T, N> &Array<T, N>::operator=(Array &&other) {
  if (size_ != other.size_) {
    throw std::out_of_range("container size is not equal");
  }
  std::move(other.data_, other.data_ + size_, data_);
  return *this;
}

TEMPLATE_ARRAY
Array<T, N> &Array<T, N>::operator=(const Array &other) {
  if (size_ != other.size_) {
    throw std::out_of_range("containers size is not equal");
  }
  std::copy(other.data_, other.data_ + size_, data_);
  return *this;
}

TEMPLATE_ARRAY
typename Array<T, N>::reference Array<T, N>::at(size_type position_) {
  if (position_ >= size_)
    throw std::out_of_range("index is out of array range");
  return data_[position_];
}

TEMPLATE_ARRAY
void Array<T, N>::swap(Array &other) {
  // if (size_ != other.size_) {
  //   throw std::out_of_range("containers size is not equal");
  // }
  for (size_t i = 0; i < size_; i++) {
    std::swap(data_[i], other.data_[i]);
  }
}

TEMPLATE_ARRAY
void Array<T, N>::fill(const_reference value) {
  for (auto &element : data_) {
    element = value;
  }
}

}  // namespace s21
