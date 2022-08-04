#pragma once

#include "s21_map.h"

using namespace s21;

// public:
// ___________________  Map Member functions ___________________

template <typename K, typename T>
map<K, T>::map() : set<std::pair<K, T>>() {}

template <typename K, typename T>
map<K, T>::map(std::initializer_list<std::pair<K, T>> const& items) : map() {
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
    this->balance_all();
  }
}

template <typename K, typename T>
map<K, T>::map(const map& copy) : map() {
  this->copy_recurrentsiv(copy._head);
}

template <typename K, typename T>
map<K, T>::map(map&& copy) {
  this->_head = copy._head;
  copy._head = nullptr;
}

template <typename K, typename T>
map<K, T>& map<K, T>::operator=(map&& m) {
  if (this != &m) {
    swap(m);
  }
  return *this;
}

template <typename K, typename T>
map<K, T>& map<K, T>::operator=(const map& m) {
  if (this != &m) {
    this->clear();
    if (m._head != nullptr) {
      this->copy_recurrentsiv(m._head);
    }
  }
  return *this;
}

// ___________________  Map Lookup  ___________________

template <typename K, typename T>
bool map<K, T>::contains(const key_type& key) {
  return find(key).is_not_nullptr();
};

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::find(const key_type& key) {
  node* ptr = this->_head;
  while (ptr != nullptr) {
    if (get_key(ptr->data) == key) {
      return iterator(ptr);
    }
    if (get_key(ptr->data) > key) {
      ptr = ptr->left;
    } else {
      ptr = ptr->right;
    }
  }
  return iterator(nullptr);
};

template <typename K, typename T>
T& map<K, T>::at(const K& key) {
  auto it = find(key);
  if (!it.is_not_nullptr())
    throw std::out_of_range(
        "map: k does not match the key of any element in the container");
  return it->second;
}

// ___________________  Modifiers  ___________________

template <typename K, typename T>
T& map<K, T>::operator[](const K& key) {
  return at(key);
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const key_type& key, const T& obj) {
  auto it = find(key);
  if (it.is_not_nullptr()) {
    it->second = obj;
    return std::pair<iterator, bool>(it, false);
  } else {
    return this->insert(std::pair<K, T>(key, obj));
  }
}

//  protected:
template <typename K, typename T>
bool map<K, T>::is_not_eq(std::pair<K, T> a, std::pair<K, T> b) {
  return (a.first != b.first);
}
