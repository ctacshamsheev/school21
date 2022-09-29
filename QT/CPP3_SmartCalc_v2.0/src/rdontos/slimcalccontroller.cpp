#include "slimcalccontroller.h"

namespace s21 {

SlimCalcController::SlimCalcController() {
  calcController_ = new s21::CalcController(new s21::CalcModel());
}

SlimCalcController::SlimCalcController(SlimCalcController &other) {
  calcController_ = new s21::CalcController(*(other.calcController_));
}

s21::SlimCalcController::~SlimCalcController() { delete calcController_; }

SlimCalcController &SlimCalcController::operator=(
    const SlimCalcController &other) {
  if (this != &other) {
    delete calcController_;
    calcController_ = new s21::CalcController(*(other.calcController_));
  }
  return *this;
}

void s21::SlimCalcController::putNumber(QString str) {
  calcController_->putNumber(str.toStdString());
}

void s21::SlimCalcController::putUnknown(QString str) {
  calcController_->putUnknown(str.toStdString());
}

void s21::SlimCalcController::putOperations(QString str) {
  calcController_->putOperations(str.toStdString());
}

void s21::SlimCalcController::putFunctions(QString str) {
  calcController_->putFunctions(str.toStdString());
}

void s21::SlimCalcController::putBracket(QString str) {
  calcController_->putBracket(str.toStdString());
}

void s21::SlimCalcController::clearBack() { calcController_->clearBack(); }

void s21::SlimCalcController::clear() { calcController_->clear(); }

double s21::SlimCalcController::getResult(double x) {
  return calcController_->getResult(x);
}

double s21::SlimCalcController::getY(double x) {
  return calcController_->getY(x);
}

QString s21::SlimCalcController::toString() {
  return QString::fromStdString(calcController_->toString());
}

}  // namespace s21
