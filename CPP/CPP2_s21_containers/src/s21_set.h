// #ifndef S21_SET_H
// #define S21_SET_H

#pragma once

#include <stdlib.h>

#include <initializer_list>
#include <iostream>
#include <utility>

#include "s21_multiset.h"

namespace s21 {

template <typename T>
class set {
 public:
  class SetIterator;
  class Key;

  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using key_type = value_type;
  using size_type = size_t;
  using iterator = SetIterator;
  // TODO using const_iterator = SetConstIterator;
  // TODO https://en.cppreference.com/w/cpp/container/set

  // iterator internal class SetIterator<T> or
  // BinaryTree::iterator as the internal iterator of tree subclass; defines
  // the type for iterating through the container
  // const_iterator
  // internal class SetConstIterator<T> or BinaryTree::const_iterator as the
  // internal const iterator of tree subclass; defines the constant type for
  // iterating through the container
  // using iterator = T *;
  // using const_iterator = const T *;
  // template <typename key_type>
  // friend class Multiset<value_type>;
  // class Key;

 protected:
  struct node;
  node *_head;

 public:
  // ___________________ Member functions ____________________

  // default constructor, creates empty set
  set();
  // initializer list constructor, creates the set
  set(std::initializer_list<value_type> const &items);
  // copy constructor
  explicit set(const set &copy);
  // move constructor
  explicit set(set &&copy);
  // destructor
  ~set();
  // assignment operator overload for moving object operator=
  set<value_type> &operator=(const set &m);
  set<value_type> &operator=(set &&m);

  // ___________________ Capacity __________________

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();
  // returns the maximum possible number of elements
  size_type max_size();

  // ___________________ Modifiers ___________________

  // clears the contents
  void clear();

  // inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &data);

  // TODO AVL https://habr.com/ru/post/150732/

  // erases element = key
  size_type erase(const key_type &key);
  // erases element at pos
  void erase(iterator pos);

  // swaps the contents
  void swap(set &other);
  // splices nodes from another  container
  void merge(set &other);  // TODO!!!!!!!!!!!!!

  // ____________________ Lookup ___________________________
  // finds element with specific key
  iterator find(const key_type &key);
  // checks if the container contains
  bool contains(const key_type &key);
  // count element = key
  size_type count(const key_type &key);

  // ____________________ Iterators _________________________
  iterator begin();
  iterator end();

  //  ____________________ Bonus Task ____________________ //
  // template <typename... Args>
  //  std::pair<iterator, bool> emplace(
  //      Args &&...args);  // inserts new elements into the container

  // My type
  class SetIterator
      : public std::iterator<std::input_iterator_tag,  // iterator_category
                             value_type> {
   public:
    node *_current;  // private?
                     // friend class set<value_type>;  // ?? нужно ли

    SetIterator(node *p = nullptr);
    value_type operator*();
    SetIterator &operator++();
    // SetIterator &operator--()
    bool operator!=(SetIterator const &other) const;
    bool operator==(const SetIterator &other) {
      return _current == other._current;
    }
    bool is_not_nullptr() { return this->_current != nullptr; }
  };
  class Key {
   private:
    key_type _key;

   public:
    Key(key_type key) : _key(key) {}
    bool is_less(key_type other) { return _key <= other; }
    // bool is_less(Key other) { return _key < other._key; }
    // bool is_more(Key other) { return _key > other._key; }
    virtual bool is_insert(key_type other) {
      // std::cout << "set:is_insert" << std::endl;
      return _key != other;
    }

    virtual key_type get_key(value_type data) { return data; }
  };
  typedef struct node {
    value_type data;
    node *left;
    node *right;
    node *parent;
  } node;

  // _______________________ protected func ___________________________
 protected:
  node **get_head() { return &_head; }
  virtual bool is_not_eq(value_type a, value_type b);

  iterator insert_recurrentsiv(Key key, const value_type &data, node **ptr,
                               node *parent);
  iterator find_recurrentsiv(const key_type &key, node *ptr);
  void copy_recurrentsiv(node *ptr);
  size_type count_recurrentsiv(const key_type &key, const node *ptr);
  size_type size_recurrentsiv(node *ptr) const;

  void remove_recurrentsiv(node *ptr);
  node *minimum(node *ptr);
  node *erase_recurrentsiv(node *ptr, key_t key);

  int height(node *ptr) const;
  int bfactor(const node *p) const;
  node *rotateright(node *p);
  node *rotateleft(node *q);
  node *balance(node *p);
  void balance_recurrentsiv(node **ptr);
  void set_parent(node **ptr, node *parent);

  // _______________________ print ___________________________

  template <T>
  friend std::ostream &operator<<(std::ostream &out, const set<T> &set);

  void print_line(std::ostream &out) const;
  void print_recurrentsiv(const node *ptr, int lvl_current, int lvl,
                          std::ostream &out, bool &flag) const;
  void print_sort(const node *ptr, std::ostream &out) const;

 public:
  void print(std::ostream &out) const;
};

}  // namespace s21

#include "s21_set.tpp"

// template <class T>
// class Multiset;  // ?????
// friend class s21::Multiset<T>;