#pragma once

#include <math.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "s21CalcModel.h"

namespace s21 {

class CalcController {
 private:
  CalcModel *model_;
  std::string inputNumber = "";
  bool isNumberPreview = false;
  bool isDotPreview = false;

 public:
  // constructor
  CalcController();
  explicit CalcController(CalcModel *model);

  CalcController(CalcController &other);
  CalcController &operator=(const CalcController &other);

  ~CalcController();

  // geters
  // CalcModel *getModel() const;

  // seters
  void putNumber(std::string str);
  void putUnknown(std::string str);
  void putOperations(std::string str);
  void putFunctions(std::string str);
  void putBracket(std::string str);
  void clearBack();
  void clear();

  void getPolish() { model_->getPolish(); };
  double getResult(double x);
  double getY(double x);

  // print
  std::string toString();

  // friend std::ostream &operator<<
  // (std::ostream &out, const CalcController &value);

 private:
  void setNotNumber();
};

}  // namespace s21
