#pragma once

#include "s21_set.h"

namespace s21 {

template <class T>
class multiset : public set<T> {
 private:
 public:
  // class Iterator : public set<T>::Iterator {
  //  public:
  //   Iterator(set<T>::node *p) : set<T>::Iterator(p){};
  // };

  class Key;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using key_type = value_type;
  using size_type = size_t;
  // using iterator = T *;
  // using const_iterator = const T *;
  // using iterator = Iterator;
  virtual void say() {
    s21::set<T>::say();
    std::cout << "!!!!!!!MultisetSet:say" << std::endl;
  }

 public:
  multiset() : set<value_type>(){};
  multiset(std::initializer_list<value_type> const &items)
      : set<value_type>(items){};

  class MKey : public set<value_type>::Key {
   private:
    key_type _key;

   public:
    MKey(key_type key) : set<value_type>::Key(key) {}

    // virtual bool is_insert(key_type other) {
    //   std::cout << "multiset:is_insert" << std::endl;
    //   return true;
    // }
  };

  // node *_head;
  bool insert(value_type data) {
    this->insert_recurrentsiv(MKey(data), data, &this->_head, nullptr);
    std::cout << "multiset:insert" << std::endl;
    return true;
  }

 protected:
  virtual bool is_not_eq(value_type a, value_type b) { return true; }

  // bool insert(value_type data) { return set<value_type>::insert(data); }
  //  bool is_not_eq(T a, T b) {
  //    return true;
  //  }  // почему не подменилось, как подменить?

 private:
};

}  // namespace s21
