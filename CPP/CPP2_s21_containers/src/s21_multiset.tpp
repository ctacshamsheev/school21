#pragma once

#include "s21_multiset.h"

using namespace s21;

// public:
// ___________________ Member functions ____________________
template <typename T>
multiset<T>::multiset() : set<value_type>() {}

template <typename T>
multiset<T>::multiset(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
  }
}

template <typename T>
multiset<T>::multiset(const multiset<value_type> &copy) : multiset() {
  this->copy_recurrentsiv(copy._head);
}

template <typename T>
multiset<T>::multiset(multiset &&copy) {
  this->_head = copy._head;
  copy._head = nullptr;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::insert(const value_type &data) {
  return this->insert_recurrentsiv(this->get_key(data), data, &this->_head,
                                   nullptr);
}

// перегруженные операторы не наследуются, можно вызывать родителя и делать каст
template <typename T>
multiset<T> &multiset<T>::operator=(const multiset &m) {
  if (this != &m) {
    this->clear();
    if (m._head != nullptr) {
      this->copy_recurrentsiv(m._head);
    }
  }
  return *this;
}

template <typename T>
multiset<T> &multiset<T>::operator=(multiset &&ms) {
  std::cout << "copy = " << std::endl;
  if (this != &ms) {
    swap(ms);
  }
  return *this;
}

// ___________________ Multiset Lookup ____________________
template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const key_type &key) {
  return this->find_lower(key, this->_head);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const key_type &key) {
  return this->find_upper(key, this->_head);
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const key_type &key) {
  return std::pair<iterator, iterator>(this->lower_bound(key),
                                       this->upper_bound(key));
}

//  ____________________ Bonus Task ____________________

template <typename T>
template <typename... Args>
typename multiset<T>::iterator multiset<T>::emplace(Args &&...args) {
  std::initializer_list<value_type> items{args...};
  return insert(*(items.begin()));
}

//  protected:
template <typename T>
bool multiset<T>::is_not_eq(value_type a, value_type b) {
  if (a != b) {  // cppcheck unused if true
    return true;
  }
  return true;
}
