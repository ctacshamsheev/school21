#include "depositmodel.h"

namespace s21 {

DepositModel::DepositModel() : sumAll_(0.0), curAmount_(0.0) {}

DepositModel::~DepositModel() {
  payList_.clear();
  if (item_ != nullptr) delete item_;
  if (model_ != nullptr) delete model_;
}

DepositModel::DepositModel(const DepositModel &other)
    : payList_(other.payList_),
      sumAll_(other.sumAll_),
      curAmount_(other.curAmount_) {
  model_ = nullptr;
  item_ = nullptr;
}

QStandardItemModel *DepositModel::getDepositModel(double amount, int term,
                                                  double rate, QDate begin_date,
                                                  bool isCapital) {
  if (model_ != nullptr) delete model_;
  model_ = new QStandardItemModel();
  this->sumAll_ = 0.0;        // общая сумма выплат
  this->curAmount_ = amount;  // текущий депозит

  double replenishment_deposit = 0.0;  // пополнение
  QDate current_date = begin_date;
  QDate end_date = current_date.addMonths(term);
  // QStandardItem *item = 0;
  struct depos_t t;
  t.payment = amount;
  t.payDate = begin_date;

  for (int i = 0; i < payList_.count(); i++) {
    if (payList_[i].payDate < begin_date || payList_[i].payDate > end_date)
      throw std::invalid_argument("date error");
  }
  addItemModel(model_, t, 0);  // первое пополнение
  int i = 1;
  while (term > 0) {               // цикл по месяцам
    double accrued_deposit = 0.0;  // начисленные проценты
    current_date = current_date.addMonths(1);
    term--;
    accrued_deposit = roundf(curAmount_ * (rate / 100.0) *
                             ((double)begin_date.daysTo(current_date) /
                              (double)current_date.daysInYear()) *
                             100.0) /
                      100.0;

    for (int j = 0; j < payList_.count(); j++) {
      if (payList_[j].payDate < current_date &&
          payList_[j].payDate >= begin_date) {
        addItemModel(model_, payList_[j], i);
        i++;
        accrued_deposit +=
            roundf(payList_[j].payment * (rate / 100.0) *
                   ((double)payList_[j].payDate.daysTo(current_date) /
                    (double)current_date.daysInYear()) *
                   100.0) /
            100.0;
        curAmount_ += payList_[j].payment;
      }
    }

    if (curAmount_ < 0) throw std::invalid_argument("summ error");

    sumAll_ += accrued_deposit;

    // дата
    QStandardItem *item =
        new QStandardItem(current_date.toString("dd MMM yyyy"));
    model_->setItem(i, 0, item);
    // начислено процентов
    addTable(accrued_deposit, model_, i, 1);
    if (isCapital) {
      replenishment_deposit = accrued_deposit;
      curAmount_ += accrued_deposit;
    }
    // пополнение
    addTable(replenishment_deposit, model_, i, 2);
    // остаток
    addTable(curAmount_, model_, i, 3);
    begin_date = current_date;
    i++;
  }
  return model_;
}

QStandardItemModel *DepositModel::getItem() {
  if (item_ != nullptr) delete item_;
  QStandardItemModel *item = new QStandardItemModel();
  for (int i = 0; i < payList_.count(); i++) {
    for (int j = 0; j < payList_.count(); j++) {
      if (payList_[i].payDate < payList_[j].payDate) {
        payList_.swapItemsAt(i, j);
      }
    }
  }
  for (int i = 0; i < payList_.count(); i++) {
    struct depos_t it = payList_[i];
    addItemModel(item, it, i);
  }
  return item;
}

void DepositModel::setItemList(QDate pay_date, double payment) {
  struct depos_t t;
  t.payDate = pay_date;
  t.payment = payment;
  payList_.append(t);
}

void DepositModel::setClearList() { payList_.clear(); }

void DepositModel::addItemModel(QStandardItemModel *model, struct depos_t it,
                                int i) {
  QStandardItem *item = new QStandardItem(it.payDate.toString("dd MMM yyyy"));
  model->setItem(i, 0, item);
  QStandardItem *item2 = new QStandardItem(QString::number(it.payment, 'f', 2));
  model->setItem(i, 2, item2);
}

void DepositModel::addTable(double d, QStandardItemModel *model, int i, int j) {
  QStandardItem *item = new QStandardItem(QString::number(d, 'f', 2));
  model->setItem(i, j, item);
}

double DepositModel::getSumAll() const { return sumAll_; }

double DepositModel::getTmp_amount() const { return curAmount_; }

}  // namespace s21
