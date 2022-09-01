namespace s21 {

template <typename T>
list<T>::list() : _inception(nullptr), _finish(nullptr), _size(0) {
  _base_node = new Node;
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) this->push_back(0);
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto &it : items) this->push_back(it);
}

template <typename T>
list<T>::list(const list &other) : list() {
  *this = other;
}

template <typename T>
list<T>::list(list &&other) : list() {
  this->swap(other);
}

template <typename T>
list<T>::~list() {
  size_t tmp = _size;
  for (size_t i = 0; i < tmp; ++i) {
    pop_back();
  }
  delete _base_node;
}

template <typename T>
list<T> &list<T>::operator=(const list &other) {
  this->clear();
  _size = 0;
  iterator it(other);
  for (size_type i = 0; i < other._size; ++i) {
    push_back(it.n_current->_data);
    ++it;
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&other) {
  this->swap(other);
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (!_size) {
    throw std::out_of_range("'Front' called on empty list");
  }
  return _inception->_data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (!_size) {
    throw std::out_of_range("'Back' called on empty list");
  }
  return _finish->_data;
}

template <typename T>
bool list<T>::empty() const {
  bool result = false;
  if (_inception == nullptr) result = true;
  return result;
}

template <typename T>
size_t list<T>::size() const {
  return _size;
}

template <typename T>
size_t list<T>::max_size() const {
  return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
}

template <typename T>
void list<T>::clear() {
  size_t tmp = _size;
  for (size_t i = 0; i < tmp; ++i) {
    pop_back();
  }
  _finish = nullptr;
  _inception = nullptr;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T &value) {
  Node *tmp = pos.n_current;
  if (tmp == _inception) {
    push_front(value);
    return iterator(_inception);
  } else if (tmp == _base_node) {
    push_back(value);
    return iterator(_finish);
  } else {
    Node *newNode = new Node;
    newNode->_data = value;
    newNode->_next = tmp;
    newNode->_previous = tmp->_previous;
    tmp->_previous->_next = newNode;
    tmp->_previous = newNode;
    ++_size;
    _base_node->_data = (int)_size;
    return iterator(newNode);
  }
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node *tmp = pos.n_current;
  Node *del;
  if (tmp == nullptr || tmp == _base_node)
    throw std::out_of_range("insert : iterator point to null");
  if (tmp == _inception) _inception = tmp->_next;
  if (tmp == _finish) _finish = tmp->_previous;
  del = tmp;
  tmp->_previous->_next = tmp->_next;
  tmp->_next->_previous = tmp->_previous;
  --_size;
  _base_node->_data = (int)_size;
  delete del;
}

template <typename T>
void list<T>::push_back(const T &value) {
  Node *tmp = new Node;
  tmp->_data = value;
  if (_finish == nullptr) {
    tmp->_previous = _base_node;
  } else
    tmp->_previous = _finish;
  tmp->_next = _base_node;
  if (_finish != nullptr) {
    _finish->_next = tmp;
  }
  _finish = tmp;
  if (_inception == nullptr) {
    _inception = tmp;
  }
  ++_size;
  _base_node->_previous = _finish;
  _base_node->_next = _inception;
  _base_node->_data = (int)_size;
}

template <typename T>
void list<T>::push_front(const T &value) {
  Node *tmp = new Node;
  tmp->_data = value;
  if (_inception == nullptr) {
    tmp->_next = _base_node;
  } else {
    tmp->_next = _inception;
  }
  tmp->_previous = _base_node;
  if (_inception != nullptr) {
    _inception->_previous = tmp;
  }
  _inception = tmp;
  if (_finish == nullptr) {
    _finish = tmp;
  }
  ++_size;
  _base_node->_previous = _finish;
  _base_node->_next = _inception;
  _base_node->_data = (int)_size;
}

template <typename T>
void list<T>::pop_back() {
  if (_size == 0) throw std::out_of_range("List is empty");
  Node *tmp = _finish->_previous;
  tmp->_next = _base_node;
  _finish->_previous->_next = _base_node;
  _base_node->_previous = tmp;
  delete _finish;
  --_size;
  if (_size)
    _finish = tmp;
  else
    _finish = nullptr;
  _base_node->_data = (int)_size;
}

template <typename T>
void list<T>::pop_front() {
  if (_size == 0) throw std::out_of_range("List is empty");
  Node *tmp = _inception->_next;
  tmp->_previous = _base_node;
  _inception->_next->_previous = _base_node;
  _base_node->_next = tmp;
  delete _inception;
  --_size;
  if (_size)
    _inception = tmp;
  else
    _inception = nullptr;
  _base_node->_data = (int)_size;
}

template <typename T>
void list<T>::merge(list &other) {
  iterator it = this->begin();
  iterator it_other = other.begin();
  while (*it_other >= *it) ++it;
  this->splice(it, other);
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  iterator tmp = pos;
  iterator it = other.begin();
  for (size_t i = 0; i < other.size(); ++i) {
    tmp = insert(tmp, *it);
    ++tmp;
    ++it;
  }
  other.clear();
}

template <typename T>
void list<T>::swap(list &other) {
  Node *swap_inc = _inception, *swap_fin = _finish, *swap_tay = _base_node;
  size_type swap_size = _size;
  _inception = other._inception;
  _finish = other._finish;
  _size = other._size;
  _base_node = other._base_node;
  other._inception = swap_inc;
  other._finish = swap_fin;
  other._size = swap_size;
  other._base_node = swap_tay;
}

template <typename T>
void list<T>::reverse() {
  if (_size > 1) {
    for (auto it = this->begin(); it != this->end();) {
      Node *tmp = it.n_current;
      ++it;
      std::swap(tmp->_next, tmp->_previous);
    }
    std::swap(this->_inception, this->_finish);
    _base_node->_previous = _finish;
    _base_node->_next = _inception;
  }
}

template <typename T>
void list<T>::unique() {
  if (_size > 1) {
    for (auto it = this->begin(); it != --this->end();) {
      iterator it_tmp = it;
      ++it;
      if (*it_tmp == *it) {
        this->erase(it);
        it = it_tmp;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (_size < 2) return;
  list new_list;
  size_t tmp_size = this->size();
  for (size_t i = 0; i < tmp_size; ++i) {
    value_type min = this->_inception->_data;
    iterator it_min(_inception);
    for (iterator it = this->begin(); it != this->end(); ++it) {
      value_type tmp = *it;
      if (min > tmp) {
        min = tmp;
        it_min.n_current = it.n_current;
      }
    }
    this->erase(it_min);
    new_list.push_back(min);
  }
  this->swap(new_list);
}

template <typename T>
template <class... Args>
typename list<T>::ListIterator list<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  return insert(pos, T(args...));
}

template <typename T>
template <class... Args>
void list<T>::emplace_back(Args &&...args) {
  push_back(T(args...));
}

template <typename T>
template <class... Args>
void list<T>::emplace_front(Args &&...args) {
  push_front(T(args...));
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(_inception);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  iterator tmp(_base_node);
  return tmp;
}

// ------------ move from head

template <typename T>
list<T>::ListIterator::ListIterator() {
  n_current = nullptr;
}

template <typename T>
list<T>::ListIterator::ListIterator(const list<T> &other)
    : n_current(other._inception) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node *_n_current) : n_current(_n_current) {}

template <typename T>
T &list<T>::ListIterator::operator*() {
  return n_current->_data;
}

template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator++() {
  if (n_current) n_current = n_current->_next;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator++(int) {
  ListIterator tmp(*this);
  n_current = n_current->_next;
  return tmp;
}

template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator--() {
  n_current = n_current->_previous;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator--(int) {
  ListIterator tmp(*this);
  n_current = n_current->_previous;
  return tmp;
}

template <typename T>
bool list<T>::ListIterator::operator==(
    const ListIterator &other) {
  return this->n_current == other.n_current;
}

template <typename T>
bool list<T>::ListIterator::operator!=(
    const ListIterator &other) {
  return this->n_current != other.n_current;
}

}  // namespace s21
