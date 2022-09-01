#pragma once

#include "s21_set.h"

using namespace s21;

// public:
// ___________________ Member functions ____________________

template <typename T>
set<T>::set() : _head(nullptr) {}

template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) : _head(nullptr) {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
    balance_all();
  }
}

template <typename T>
set<T>::set(const set<value_type> &copy) : set() {
  copy_recurrentsiv(copy._head);
}

template <typename T>
set<T>::set(set<value_type> &&copy) {  // ? const
  _head = copy._head;
  copy._head = nullptr;
}

template <typename T>
set<T>::~set() {
  remove_recurrentsiv(_head);
}

template <typename T>
set<T> &set<T>::operator=(const set &m) {
  if (this != &m) {
    this->clear();
    if (m._head != nullptr) {
      this->copy_recurrentsiv(m._head);
    }
  }
  return *this;
}

template <typename T>
set<T> &set<T>::operator=(set &&m) {
  if (this != &m) {
    swap(m);
  }
  return *this;
}

// ____________________ Lookup ___________________________

template <typename T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  return find_recurrentsiv(key, _head);
}

template <typename T>
bool set<T>::contains(const key_type &key) {
  return this->find(key).is_not_nullptr();
}

// простые методы
template <typename T>
typename set<T>::size_type set<T>::count(const key_type &key) {
  return count_recurrentsiv(key, _head);
}

// ___________________ Capacity __________________

template <typename T>
bool set<T>::empty() {
  return _head == nullptr;
}

template <typename T>
typename set<T>::size_type set<T>::size() {
  return size_recurrentsiv(_head);
}

template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(node);
}

// ___________________ Modifiers ___________________

template <typename T>
void set<T>::clear() {
  remove_recurrentsiv(_head);
  _head = nullptr;
};

template <typename T>
std::pair<typename set<T>::SetIterator, bool> set<T>::insert(const T &data) {
  SetIterator result =
      insert_recurrentsiv(key_type(data), data, &_head, nullptr);
  return std::pair<set<T>::SetIterator, bool>(result, result.is_not_nullptr());
}

template <typename T>
void set<T>::swap(set &other) {
  if (this == &other) {
    throw std::invalid_argument("ERROR: trying swap to itself");
  } else {
    std::swap(_head, other._head);
  }
}

template <typename T>
void set<T>::merge(set &other) {
  auto iter = other.begin();
  while (iter != other.end()) {
    if (insert(*iter).second) {
      auto tmp = iter;
      ++iter;
      other.erase(tmp);
    } else
      ++iter;
  }
}

// ____________________ Iterators _________________________

template <typename T>
typename set<T>::SetIterator set<T>::begin() {  // node or &T ?????  *?
  node *ptr = minimum(_head);
  return SetIterator(ptr);
}

template <typename T>
typename set<T>::SetIterator set<T>::end() {  // *?
  return SetIterator();
}

// класс итератор
template <typename T>
set<T>::SetIterator::SetIterator(node *p) : _current(p) {}

template <typename T>
typename set<T>::value_type set<T>::SetIterator::operator*() {
  if (_current != nullptr) return _current->data;
  throw std::out_of_range("Iterator::operator*(nullptr)");
}

template <typename T>
typename set<T>::value_type *set<T>::SetIterator::operator->() {
  if (_current != nullptr) return &(_current->data);
  throw std::out_of_range("Iterator::operator*(nullptr)");
};

template <typename T>
bool set<T>::SetIterator::operator!=(SetIterator const &other) const {
  return _current != other._current;
}

template <typename T>
bool set<T>::SetIterator::operator==(const SetIterator &other) const {
  return _current == other._current;
}

template <typename T>
bool set<T>::SetIterator::is_not_nullptr() const {
  return this->_current != nullptr;
}

template <typename T>
typename set<T>::SetIterator &set<T>::SetIterator::operator++() {
  if (_current != nullptr) {
    if (_current->right != nullptr) {
      _current = (_current->right);
      while (_current->left != nullptr) {
        _current = _current->left;
      }
    } else {
      while (_current->parent != nullptr &&
             _current->data >= _current->parent->data) {
        _current = (_current->parent);
      }
      _current = (_current->parent);
    }
  }
  return *this;
}

template <typename T>
set<T>::SetConstIterator::SetConstIterator() : SetIterator() {}

template <typename T>
const typename set<T>::value_type set<T>::SetConstIterator::operator*() {
  return SetIterator::operator*();
}

template <typename T>
const typename set<T>::value_type *set<T>::SetConstIterator::operator->() {
  return SetIterator::operator->();
};

template <typename T>
const typename set<T>::SetConstIterator &
set<T>::SetConstIterator::operator++() {
  return SetIterator::operator++();
};

//  ____________________ Bonus Task ____________________

template <typename T>
template <typename... Args>
std::pair<typename set<T>::SetIterator, bool> set<T>::emplace(Args &&...args) {
  std::initializer_list<value_type> items{args...};
  std::pair<iterator, bool> result = insert(*(items.begin()));
  balance_all();
  return result;
}

// _______________________ protected func ___________________________

template <typename T>
typename set<T>::key_type set<T>::get_key(value_type data) {
  return data;
};

template <typename T>
bool set<T>::is_not_eq(value_type a, value_type b) {
  return a != b;
}

template <typename T>
typename set<T>::SetIterator set<T>::insert_recurrentsiv(key_type key,
                                                         const value_type &data,
                                                         node **ptr,
                                                         node *parent) {
  if (*ptr == nullptr) {
    *ptr = new node;
    (*ptr)->data = data;
    (*ptr)->left = (*ptr)->right = nullptr;
    (*ptr)->parent = parent;
    return SetIterator(*ptr);
  } else {
    if (is_not_eq(data, (*ptr)->data)) {
      if (data < (*ptr)->data) {
        return insert_recurrentsiv(key, data, &((*ptr)->left), (*ptr));
      } else {
        return insert_recurrentsiv(key, data, &((*ptr)->right), (*ptr));
      }
    }
  }
  return SetIterator();
}

template <typename T>
typename set<T>::SetIterator set<T>::find_recurrentsiv(const key_type &key,
                                                       node *ptr) {
  if (ptr == nullptr) return SetIterator();
  if (get_key(ptr->data) == key) return SetIterator(ptr);
  if (get_key(ptr->data) > key) return find_recurrentsiv(key, ptr->left);
  return find_recurrentsiv(key, ptr->right);
}

template <typename T>
typename set<T>::SetIterator set<T>::find_upper(const key_type &key,
                                                node *ptr) {
  while (ptr != nullptr) {
    if ((get_key(ptr->data) > key)) {
      if (ptr->left != nullptr)
        ptr = ptr->left;
      else
        break;
    }
    if ((get_key(ptr->data) <= key)) {
      if (ptr->right != nullptr)
        ptr = ptr->right;
      else
        break;
    }
  }
  while (ptr != nullptr && get_key(ptr->data) <= key) {
    ptr = ptr->parent;
  }
  return SetIterator(ptr);
}

template <typename T>
typename set<T>::SetIterator set<T>::find_lower(const key_type &key,
                                                node *ptr) {
  while (ptr != nullptr) {
    if ((get_key(ptr->data) >= key)) {
      if (ptr->left != nullptr)
        ptr = ptr->left;
      else
        break;
    }
    if ((get_key(ptr->data) < key)) {
      if (ptr->right != nullptr)
        ptr = ptr->right;
      else
        break;
    }
  }
  while (ptr != nullptr && get_key(ptr->data) < key) {
    ptr = ptr->parent;
  }
  return SetIterator(ptr);
}

template <typename T>
void set<T>::copy_recurrentsiv(node *ptr) {
  if (ptr != nullptr) {
    insert(ptr->data);
    copy_recurrentsiv(ptr->left);
    copy_recurrentsiv(ptr->right);
  }
}

template <typename T>
typename set<T>::node *set<T>::minimum(node *ptr) {
  if (ptr == nullptr) return nullptr;
  while (ptr->left != nullptr) {
    ptr = ptr->left;
  }
  return ptr;
}

template <typename T>
typename set<T>::size_type set<T>::erase(const key_type &key) {
  size_type count = 0;
  while (contains(key)) {
    _head = erase_recurrentsiv(_head, key);
    count += 1;
  }
  return count;
}

template <typename T>
void set<T>::erase(iterator pos) {
  if (pos.is_not_nullptr()) {
    _head = erase_recurrentsiv(_head, *pos);
  }
}

template <typename T>
typename set<T>::node *set<T>::erase_recurrentsiv(node *ptr, key_type key) {
  node *tmp = nullptr;
  if (ptr == nullptr) return ptr;
  if (key < get_key(ptr->data))
    ptr->left = erase_recurrentsiv(ptr->left, key);
  else if (key > get_key(ptr->data))
    ptr->right = erase_recurrentsiv(ptr->right, key);
  else if (ptr->left != nullptr and ptr->right != nullptr) {
    ptr->data = minimum(ptr->right)->data;
    ptr->right = erase_recurrentsiv(ptr->right, ptr->data);
  } else if (ptr->left != nullptr) {
    tmp = ptr;
    ptr = ptr->left;
    ptr->parent = tmp->parent;
  } else if (ptr->right != nullptr) {
    tmp = ptr;
    ptr = ptr->right;
    ptr->parent = tmp->parent;
  } else {
    tmp = ptr;
    ptr = nullptr;
  }
  if (tmp != nullptr) {
    delete (tmp);
  }
  return ptr;
}

template <typename T>
typename set<T>::size_type set<T>::count_recurrentsiv(const key_type &key,
                                                      const node *ptr) {
  if (ptr != nullptr) {
    return count_recurrentsiv(key, ptr->left) +
           count_recurrentsiv(key, ptr->right) +
           ((get_key(ptr->data) == key) ? 1 : 0);
  } else
    return 0;
}

template <typename T>
typename set<T>::size_type set<T>::size_recurrentsiv(node *ptr) const {
  if (ptr != nullptr) {
    return size_recurrentsiv(ptr->left) + size_recurrentsiv(ptr->right) + 1;
  }
  return 0;
}

template <typename T>
void set<T>::remove_recurrentsiv(node *ptr) {
  if (ptr != nullptr) {
    remove_recurrentsiv(ptr->left);
    remove_recurrentsiv(ptr->right);
    delete (ptr);
  }
}
// _______________________ balance ___________________________

template <typename T>
int set<T>::height(node *ptr) const {
  if (ptr == nullptr) return 0;
  return std::max(height(ptr->left), height(ptr->right)) + 1;
}

template <typename T>
int set<T>::bfactor(const node *p) const {
  return height(p->right) - height(p->left);
}

template <typename T>
typename set<T>::node *set<T>::rotateright(node *p)  // правый поворот вокруг p
{
  node *q = p->left;
  p->left = q->right;
  q->right = p;
  return q;
}

template <typename T>
typename set<T>::node *set<T>::rotateleft(node *q)  // левый поворот вокруг q
{
  node *p = q->right;
  q->right = p->left;
  p->left = q;
  return p;
}

template <typename T>
typename set<T>::node *set<T>::balance(node *p)  // балансировка узла p
{
  if (bfactor(p) >= 2) {
    if (bfactor(p->right) < 0) p->right = rotateright(p->right);
    return rotateleft(p);
  }
  if (bfactor(p) <= -2) {
    if (bfactor(p->left) > 0) p->left = rotateleft(p->left);
    return rotateright(p);
  }
  return p;  // балансировка не нужна
}

template <typename T>
void set<T>::balance_recurrentsiv(node **ptr) {
  if (*ptr != nullptr) {
    balance_recurrentsiv(&(*ptr)->left);
    balance_recurrentsiv(&(*ptr)->right);
    *ptr = balance(*ptr);
  }
}

template <typename T>
void set<T>::set_parent(node **ptr, node *parent) {
  if (*ptr != nullptr) {
    (*ptr)->parent = parent;
    set_parent(&(*ptr)->left, *ptr);
    set_parent(&(*ptr)->right, *ptr);
  }
}

template <typename T>
void set<T>::balance_all() {
  balance_recurrentsiv(&_head);
  set_parent(&_head, nullptr);
}

// _______________________ print ___________________________

// template <typename T>
// void set<T>::print_line(std::ostream &out) const {
//   int lvl = 0;
//   bool flag = true;
//   while (lvl < 10 && flag) {
//     flag = false;
//     out << lvl << ": ";
//     for (int i = 0; i < 10 - lvl; i++) out << "  ";
//     print_recurrentsiv(_head, 0, lvl, out, &flag);
//     out << std::endl;
//     lvl++;
//   }
// }

// template <typename T>
// void set<T>::print_recurrentsiv(const node *ptr, int lvl_current, int lvl,
//                                 std::ostream &out, bool *flag) const {
//   if (lvl_current <= lvl) {
//     if (ptr != nullptr) {
//       if (lvl_current == lvl) {
//         *flag = true;
//         //корень
//         value_type t = ((ptr->parent != nullptr) ? ptr->parent->data : -1);
//         out << ptr->data << "(" << t << ") ";
//         // элемент
//         //  out << ptr->data << " ";
//         // баланс
//         // int t = bfactor(ptr);
//         // out << ptr->data << "(" << t << ") ";
//       }
//       print_recurrentsiv(ptr->left, lvl_current + 1, lvl, out, flag);
//       print_recurrentsiv(ptr->right, lvl_current + 1, lvl, out, flag);
//     } else {
//       out << "    ";
//     }
//   }
// }

// template <typename T>
// void set<T>::print_sort(const node *ptr, std::ostream &out) const {
//   if (ptr != nullptr) {
//     print_sort(ptr->left, out);
//     out << ptr->data << " ";
//     print_sort(ptr->right, out);
//   }
// }

// template <typename T>
// void set<T>::print(std::ostream &out) const {
//   out << "set:[ ";
//   print_sort(this->_head, out);
//   out << "]" << std::endl;
//   print_line(out);
// }

// template <typename T>
// std::ostream &operator<<(std::ostream &out, const set<T> &set) {
//   set.print(out);
//   return out;
// }
