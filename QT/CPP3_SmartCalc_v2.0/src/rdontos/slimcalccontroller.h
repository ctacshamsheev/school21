#ifndef SLIMCALCCONTROLLER_H
#define SLIMCALCCONTROLLER_H

#include <QString>

#include "../s21CalcController.h"
#include "../s21CalcModel.h"

namespace s21 {

class SlimCalcController {
 public:
  SlimCalcController();
  SlimCalcController(SlimCalcController &other);
  ~SlimCalcController();

  SlimCalcController &operator=(const SlimCalcController &other);

  void putNumber(QString str);

  void putUnknown(QString str);
  void putOperations(QString str);
  void putFunctions(QString str);
  void putBracket(QString str);
  void clearBack();
  void clear();

  double getResult(double x);
  double getY(double x);

  QString toString();

 private:
  s21::CalcController *calcController_ = nullptr;
};

}  // namespace s21

#endif  // SLIMCALCCONTROLLER_H
