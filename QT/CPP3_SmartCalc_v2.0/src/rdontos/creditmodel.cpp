#include "creditmodel.h"

namespace s21 {

//    double amount  // сумма кредита
//    int term   // срок кредита
//    double rate  // процентная ставка
CreditModel::CreditModel(double amount, int term, double rate, bool isAnnuity) {
  model_ = new QStandardItemModel();
  sumOverPayment_ = 0.0;  // сумма переплаты
  sumAll_ = 0.0;          // общая сумма выплат

  double monthly_rate = (rate / 12) / 100;  // процентная ставка в месяц
  double tmp_amount = amount;  // остаток долга

  if (isAnnuity) {  // ануитетный
    double sum_payment =
        roundf(amount * (monthly_rate / (1 - pow(1 + monthly_rate, -term))) *
               100) /
        100;
    sumOverPayment_ = sum_payment * term - amount;
    for (int i = 0; i < term; i++) {
      double overpayment = tmp_amount * monthly_rate;
      double payment = roundf((sum_payment - overpayment) * 100) / 100;
      tmp_amount -= payment;
      addLine(i, sum_payment, payment, overpayment, tmp_amount);
    }
  } else {  // дифференцированный
    double payment = amount / term;
    for (int i = 0; i < term; i++) {
      double overpayment = tmp_amount * monthly_rate;
      tmp_amount = tmp_amount - payment;
      sumOverPayment_ += overpayment;
      double sum_payment = payment + overpayment;
      addLine(i, sum_payment, payment, overpayment, tmp_amount);
    }
  }

  sumAll_ = sumOverPayment_ + amount;
}

CreditModel::CreditModel(const CreditModel &other) {
  model_ = new QStandardItemModel(other.model_);
  sumOverPayment_ = other.sumOverPayment_;
  sumAll_ = other.sumAll_;
}

CreditModel::~CreditModel() { delete model_; }

QStandardItemModel *CreditModel::getCreditModel() { return this->model_; }

CreditModel &CreditModel::operator=(const CreditModel &other) {
  if (this != &other) {
    delete model_;
    model_ = new QStandardItemModel(other.model_);
    sumOverPayment_ = other.sumOverPayment_;
    sumAll_ = other.sumAll_;
  }
  return *this;
}

double CreditModel::getSumOverPayment() const { return sumOverPayment_; }

double CreditModel::getSumAll() const { return sumAll_; }

void CreditModel::addTable(double d, int i, int j) {
  QStandardItem *item = new QStandardItem(QString::number(d, 'f', 2));
  model_->setItem(i, j, item);
}

void CreditModel::addLine(int i, double a, double b, double c, double d) {
  addTable(a, i, 0);
  addTable(b, i, 1);
  addTable(c, i, 2);
  addTable(d, i, 3);
}

}  // namespace s21
