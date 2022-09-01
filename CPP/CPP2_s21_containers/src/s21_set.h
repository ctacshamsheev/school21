#pragma once

#include <limits>

namespace s21 {
template <typename T>
class set {
 public:
  // ___________________ Member type ___________________
  class SetIterator;
  class SetConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using key_type = value_type;
  using size_type = size_t;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

 protected:
  struct node;
  node *_head;

 public:
  // ___________________ Member functions ____________________

  // default constructor, creates empty set
  set();
  // initializer list constructor, creates the set
  explicit set(const std::initializer_list<value_type> &items);
  // copy constructor
  explicit set(const set &copy);
  // move constructor
  explicit set(set &&copy);
  // destructor
  ~set();
  // assignment operator overload for moving object operator=
  set<value_type> &operator=(const set &m);
  // assignment operator overload for moving object operator=
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
  // inserts node and returns iterator to where the element is in the
  // container and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &data);
  // erases element = key
  size_type erase(const key_type &key);
  // erases element at pos
  void erase(iterator pos);
  // swaps the contents
  void swap(set &other);
  // splices nodes from another  container
  void merge(set &other);

  // ____________________ Lookup ___________________________

  // finds element with specific key
  iterator find(const key_type &key);
  // checks if the container contains
  bool contains(const key_type &key);
  // count element = key
  size_type count(const key_type &key);

  // ____________________ Iterators _________________________

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();

  //  ____________________ Bonus Task ____________________
  // inserts new elements into the container
  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  // My type

  class SetIterator {
   private:
    node *_current;

   public:
    explicit SetIterator(node *p = nullptr);
    value_type operator*();
    value_type *operator->();
    SetIterator &operator++();
    bool operator!=(SetIterator const &other) const;
    bool operator==(const SetIterator &other) const;
    bool is_not_nullptr() const;
  };

  class SetConstIterator : public SetIterator {
   public:
    SetConstIterator();
    const value_type operator*();
    const value_type *operator->();
    const SetConstIterator &operator++();
  };

  typedef struct node {
    value_type data;
    node *left;
    node *right;
    node *parent;
  } node;
  // _______________________ protected func ___________________________
 protected:
  key_type get_key(value_type data);
  virtual bool is_not_eq(value_type a, value_type b);
  iterator find_upper(const key_type &key, node *ptr);  // >
  iterator find_lower(const key_type &key, node *ptr);  // >=
  node *minimum(node *ptr);
  iterator insert_recurrentsiv(key_type key, const value_type &data, node **ptr,
                               node *parent);
  iterator find_recurrentsiv(const key_type &key, node *ptr);
  virtual void copy_recurrentsiv(node *ptr);
  size_type count_recurrentsiv(const key_type &key, const node *ptr);
  size_type size_recurrentsiv(node *ptr) const;
  void remove_recurrentsiv(node *ptr);
  node *erase_recurrentsiv(node *ptr, key_type key);

  // _______________________ balance ___________________________
  void balance_all();
  int height(node *ptr) const;
  int bfactor(const node *p) const;
  node *rotateright(node *p);
  node *rotateleft(node *q);
  node *balance(node *p);
  void balance_recurrentsiv(node **ptr);
  void set_parent(node **ptr, node *parent);

  // _______________________ print ___________________________
  // template <T>
  // friend std::ostream &operator<<(std::ostream &out, const set<T> &set);
  //   void print_line(std::ostream &out) const;
  //   void print_recurrentsiv(const node *ptr, int lvl_current, int lvl,
  //                           std::ostream &out, bool *flag) const;
  //   void print_sort(const node *ptr, std::ostream &out) const;
  //  public:
  //   void print(std::ostream &out) const;
};

}  // namespace s21

#include "s21_set.tpp"
