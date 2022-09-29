#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <QStandardItemModel>

namespace s21 {

class CreditModel {
 public:
  CreditModel(double amount, int term, double rate, bool isAnnuity);
  CreditModel(const CreditModel &other);
  ~CreditModel();

  QStandardItemModel *getCreditModel();
  CreditModel &operator=(const CreditModel &other);

  double getSumOverPayment() const;
  double getSumAll() const;

 private:
  void addTable(double d, int i, int j);
  void addLine(int i, double a, double b, double c, double d);

 private:
  QStandardItemModel *model_;
  double sumOverPayment_;
  double sumAll_;
};

}  // namespace s21

#endif  // CREDITMODEL_H
