#ifndef DEPOSITCONTROLLER_H
#define DEPOSITCONTROLLER_H

#include "depositmodel.h"

namespace s21 {

class DepositController {
 public:
  DepositController();
  DepositController(const DepositController &other);
  ~DepositController();

  DepositController &operator=(const DepositController &other);
  // set
  QStandardItemModel *getDepositModel(double amount, int term, double rate,
                                      QDate begin_date, bool isCapital);
  QStandardItemModel *getItem(QDate pay_date, double payment);

  QStandardItemModel *getClear();

  double getAmount() const;
  double getSumAll() const;

 private:
  DepositModel *depositModel_ = nullptr;
};

}  // namespace s21

#endif  // DEPOSITCONTROLLER_H
