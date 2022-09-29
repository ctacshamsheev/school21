#include "depositcontroller.h"

namespace s21 {

DepositController::DepositController() { depositModel_ = new DepositModel(); }

DepositController::~DepositController() { delete depositModel_; }

DepositController::DepositController(const DepositController &other) {
  depositModel_ = new DepositModel(*(other.depositModel_));
}

DepositController &DepositController::operator=(
    const DepositController &other) {
  if (this != &other) {
    delete depositModel_;
    depositModel_ = new DepositModel(*(other.depositModel_));
  }
  return *this;
}

// void DepositController::setClearList() { depositModel_->setClearList(); }

QStandardItemModel *DepositController::getDepositModel(double amount, int term,
                                                       double rate,
                                                       QDate begin_date,
                                                       bool isCapital) {
  return depositModel_->getDepositModel(amount, term, rate, begin_date,
                                        isCapital);
}

QStandardItemModel *DepositController::getItem(QDate pay_date, double payment) {
  depositModel_->setItemList(pay_date, payment);
  return depositModel_->getItem();
}

QStandardItemModel *DepositController::getClear() {
  depositModel_->setClearList();
  return depositModel_->getItem();
}

double DepositController::getAmount() const {
  return depositModel_->getTmp_amount();
}

double DepositController::getSumAll() const {
  return depositModel_->getSumAll();
}

}  // namespace s21
