#include "creditcontroller.h"

namespace s21 {

CreditController::CreditController(double amount, int term, double rate,
                                   bool isAnnuity) {
  creditModel_ = new CreditModel(amount, term, rate, isAnnuity);
}

CreditController::CreditController(const CreditController &other) {
  creditModel_ = new CreditModel(*(other.creditModel_));
}

CreditController::~CreditController() { delete creditModel_; }

CreditController &CreditController::operator=(const CreditController &other) {
  if (this != &other) {
    delete creditModel_;
    creditModel_ = new CreditModel(*(other.creditModel_));
  }
  return *this;
}

double CreditController::getSumOverPayment() const {
  return creditModel_->getSumOverPayment();
}

double CreditController::getSumAll() const { return creditModel_->getSumAll(); }

QStandardItemModel *CreditController::getCreditModel() const {
  return creditModel_->getCreditModel();
}

}  // namespace s21
