namespace s21 {

template <typename T>
Queue<T>::Queue() : _inception(nullptr), _finish(nullptr), _size(0){};

template <typename T>
Queue<T>::Queue(std::initializer_list<T> const& items) : Queue() {
  for (const auto& it : items) this->push(it);
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) : Queue() {
  *this = other;
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other) : Queue() {
  this->swap(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
  if (this != &other) {
    try {
      while (_inception) {
        pop();
      }
      _size = 0;
      _finish = nullptr;
      Node* tmp = other._inception;
      for (size_type i = 0; i < other._size; i++) {
        push(tmp->_data);
        tmp = tmp->_next;
      }
    } catch (...) {
      throw;
    }
  }
  return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) {
  this->swap(other);
  return *this;
}

template <typename T>
Queue<T>::~Queue() {
  size_t tmp = _size;
  for (size_t i = 0; i < tmp; i++) {
    pop();
  }
}

template <typename T>
void Queue<T>::push(const_reference value) {
  Node* tmp = new Node;
  tmp->_data = value;
  if (_inception == nullptr) {
    tmp->_next = nullptr;
    _inception = tmp;
    _finish = tmp;
  } else {
    tmp->_next = nullptr;
    _finish->_next = tmp;
    _finish = tmp;
  }
  ++_size;
}

template <typename T>
void Queue<T>::pop() {
  if (_inception == nullptr) return;
  Node* tmp = _inception;
  _inception = _inception->_next;
  delete tmp;
  --_size;
}

template <typename T>
void Queue<T>::swap(Queue<T>& other) {
  size_type tmp_size = _size;
  Node* tmp_inception = _inception;
  Node* tmp_finish = _finish;
  _size = other._size;
  _inception = other._inception;
  _finish = other._finish;
  other._size = tmp_size;
  other._inception = tmp_inception;
  other._finish = tmp_finish;
}

template <typename T>
template <class... Args>
void Queue<T>::emplace_back(Args... args) {
  try {
    push(T(args...));
  } catch (...) {
    throw;
  }
}

}  // namespace s21
