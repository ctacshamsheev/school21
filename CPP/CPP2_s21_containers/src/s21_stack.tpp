namespace s21 {

template <typename T>
Stack<T>::Stack() : _roof(nullptr), _size(0){};

template <typename T>
Stack<T>::Stack(std::initializer_list<T> const& items) : Stack() {
  for (const auto& it : items) this->push(it);
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : Stack() {
  *this = other;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& other) : Stack() {
  this->swap(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
  if (this != &other) {
    try {
      while (_roof) {
        pop();
      }
      _size = 0;
      Node* tmp = other._roof;
      value_type arr[other._size];
      for (size_type i = 0; i < other._size; i++) {
        arr[i] = tmp->_data;
        tmp = tmp->_next;
      }
      for (size_type i = 0; i < other._size; i++) {
        this->push(arr[other._size - 1 - i]);
      }
    } catch (...) {
      throw;
    }
  }
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) {
  this->swap(other);
  return *this;
}

template <typename T>
Stack<T>::~Stack() {
  size_t tmp = _size;
  for (size_t i = 0; i < tmp; i++) {
    pop();
  }
}

template <typename T>
void Stack<T>::push(const_reference value) {
  Node* tmp = new Node;
  tmp->_next = _roof;
  tmp->_data = value;
  _roof = tmp;
  ++_size;
}

template <typename T>
void Stack<T>::pop() {
  if (_roof == nullptr) return;
  Node* tmp = _roof;
  _roof = _roof->_next;
  delete tmp;
  --_size;
}

template <typename T>
void Stack<T>::swap(Stack<T>& other) {
  size_type tmp_size = _size;
  Node* tmp_roof = _roof;
  _size = other._size;
  _roof = other._roof;
  other._size = tmp_size;
  other._roof = tmp_roof;
}

template <typename T>
template <class... Args>
void Stack<T>::emplace_front(Args... args) {
  try {
    push(T(args...));
  } catch (...) {
    throw;
  }
}

}  // namespace s21
