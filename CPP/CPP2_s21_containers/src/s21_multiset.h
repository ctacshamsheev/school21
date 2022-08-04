#pragma once

#include "s21_set.h"

namespace s21 {

template <typename T>
class multiset : public s21::set<T> {
 public:
  // ___________________ Member type ___________________
  using value_type = T;         // Key value type (the value itself is a key)
  using key_type = value_type;  // Key the first template parameter (Key)
  using size_type = size_t;     // size_t defines the type of the container size
                                // (standard type is size_t)
  using reference =
      value_type &;  // defines the type of the reference to an element
  using const_reference =
      const value_type &;  // defines the type of the constant  reference
  using iterator = typename set<
      value_type>::SetIterator;  // internal class MultisetIterator<T> or
                                 // BinaryTree::iterator as internal
  using const_iterator = typename set<value_type>::
      SetConstIterator;  // internal class MultisetConstIterator<T>
                         // or  BinaryTree::const_iterator as internal const
                         // iterator of tree subclass; defines the constant type
                         // for iterating through the container

 public:
  // ___________________ Member functions ____________________

  // default constructor, creates empty set
  multiset();
  // initializer list constructor, creates the set initizialized using
  // std::initializer_list
  explicit multiset(std::initializer_list<value_type> const &items);
  // copy constructor
  explicit multiset(const multiset<value_type> &copy);
  // move constructor
  explicit multiset(multiset &&copy);
  // assignment operator overload for moving object operator=
  multiset<value_type> &operator=(const multiset &m);
  // assignment operator overload for moving object
  multiset<value_type> &operator=(multiset &&ms);

  // ___________________ Modifiers ___________________

  // inserts node and returns iterator to where the element is in the container
  iterator insert(const value_type &data);

  //  ____________________ Bonus Task ____________________
  // inserts new elements into the container
  template <typename... Args>
  iterator emplace(Args &&...args);

  // ___________________ Multiset Lookup ____________________

  // returns range of elements matching a specific key
  std::pair<iterator, iterator> equal_range(const key_type &key);
  // returns an iterator to the first element not less than the given key
  iterator lower_bound(const key_type &key);
  // returns an iterator to the first element greater than the given key
  iterator upper_bound(const key_type &key);

 protected:
  // key_type get_key(value_type data) override;
  bool is_not_eq(value_type a, value_type b) override;
};

#include "s21_multiset.tpp"

}  // namespace s21
