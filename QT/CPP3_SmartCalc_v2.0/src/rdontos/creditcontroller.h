#ifndef CREDITCONTROLLER_H
#define CREDITCONTROLLER_H

#include "creditmodel.h"

namespace s21 {

class CreditController {
 public:
  CreditController(double amount, int term, double rate, bool isAnnuity);
  CreditController(const CreditController &other);
  ~CreditController();

  CreditController &operator=(const CreditController &other);

  double getSumOverPayment() const;
  double getSumAll() const;
  QStandardItemModel *getCreditModel() const;

 private:
  CreditModel *creditModel_ = nullptr;
};

}  // namespace s21

#endif  // CREDITCONTROLLER_H
