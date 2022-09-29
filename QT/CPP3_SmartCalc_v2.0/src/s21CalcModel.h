#pragma once

#include <math.h>

#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>

#include "arithmetic.h"

namespace s21 {

class CalcModel {
 private:
  std::list<I_Arithmetic *> data_;    // input
  std::list<I_Arithmetic *> polish_;  // polish

 public:
  // constructor
  CalcModel();
  ~CalcModel();
  CalcModel(const CalcModel &other);
  CalcModel &operator=(const CalcModel &other);

  // modify
  void pushBackArithmetic(I_Arithmetic *data);
  void editBackArithmetic(I_Arithmetic *data);
  void clearBackArithmetic();
  void clear();

  // get
  bool getCheck();
  void getPolish();
  double getResult(double x);
  bool isNumber();
  bool isUnary();

  // print
  std::string toString();
  std::string toStringLast();

  // friend std::ostream &operator<<(std::ostream &out, const CalcModel &value);
 private:
  //   std::ostream &printList(std::ostream &out) const;
  void del();
  void copy(const CalcModel &other);
};

}  // namespace s21
