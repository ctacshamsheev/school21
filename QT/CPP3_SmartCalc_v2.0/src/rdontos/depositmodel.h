#ifndef DEPOSITMODEL_H
#define DEPOSITMODEL_H

#include <QStandardItemModel>

#include "qdatetime.h"

namespace s21 {

class DepositModel {
 public:
  struct depos_t {
    QDate payDate;
    double payment;
  };

  DepositModel();
  ~DepositModel();
  DepositModel(const DepositModel &other);

  QStandardItemModel *getDepositModel(double amount, int term, double rate,
                                      QDate begin_date, bool isCapital);
  QStandardItemModel *getItem();

  void setItemList(QDate pay_date, double payment);
  void setClearList();

  double getTmp_amount() const;

  double getSumAll() const;

 private:
  void addItemModel(QStandardItemModel *model, struct depos_t it, int i);
  void addTable(double d, QStandardItemModel *model, int i, int j);

 private:
  QList<depos_t> payList_;
  QStandardItemModel *model_ = nullptr;
  QStandardItemModel *item_ = nullptr;
  double sumAll_;     // общая сумма выплат
  double curAmount_;  // текущий депозит
};

}  // namespace s21
#endif  // DEPOSITMODEL_H
