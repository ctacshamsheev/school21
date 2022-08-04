#pragma once

#include "s21_set.h"

namespace s21 {

template <typename K, typename T>
class map : public s21::set<std::pair<K, T>> {
 public:
  // ___________________ Member type ___________________
  using key_type = K;     // Key the first template parameter (Key)
  using mapped_type = T;  // T the second template parameter (T)
  using value_type = std::pair<key_type, mapped_type>;  //  Key-value pair
  using size_type = size_t;  // size_t defines the type of the container size

  using iterator = typename set<
      value_type>::SetIterator;  // internal class MultisetIterator<T> or
                                 // BinaryTree::iterator as internal iterator of
                                 // tree subclass; defines the type for
                                 // iterating through the container
  using node = typename set<value_type>::node;

  using reference = value_type&;  // defines the type of the reference to an
                                  // element
  using const_reference = const value_type&;  // defines the type of the
                                              // constant reference
  using const_iterator = typename set<value_type>::
      SetConstIterator;  // as internal const iterator
                         // of tree subclass; defines the constant type for
                         // iterating through the  container

 public:
  // ___________________  Map Member functions ___________________

  // default constructor, creates empty map
  map();
  //  initializer list constructor,  creates the map initizialized using
  //  std::initializer_list
  explicit map(std::initializer_list<value_type> const& items);
  // copy constructor
  map(const map& copy);
  // move constructor
  map(map&& copy);
  // assignment operator overload for moving object operator=
  map<K, T>& operator=(const map& m);
  // assignment operator overload for moving object
  map<K, T>& operator=(map&& m);

  // ___________________  Map Lookup  ___________________

  // finds element with specific key
  iterator find(const key_type& key);
  // checks if there is an element with key equivalent to key in the container
  bool contains(const key_type& key);

  // ___________________  Map Element access  ___________________

  //  access specified element with bounds checking
  T& at(const key_type& key);
  //  access or insert specified element
  T& operator[](const key_type& key);

  // ___________________  Modifiers  ___________________

  //  inserts an element or assigns to the current element
  //  if the key already exists
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);

  //  ____________________ Bonus Task ____________________
  // inserts new elements into the container
  // std::pair<iterator, bool> emplace(Args&&... args);  // унаследована

 protected:
  bool is_not_eq(value_type a, value_type b) override;
  key_type get_key(value_type data) { return data.first; }
};

}  // namespace s21

#include "s21_map.tpp"
