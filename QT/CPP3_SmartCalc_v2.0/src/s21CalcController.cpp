#include "s21CalcController.h"

namespace s21 {

CalcController::CalcController() : model_(new CalcModel()) {}

CalcController::CalcController(CalcModel *model) : model_(model) {}

CalcController::CalcController(CalcController &other) {
  model_ = new s21::CalcModel(*(other.model_));
}

CalcController &CalcController::operator=(const CalcController &other) {
  if (this != &other) {
    delete model_;
    model_ = new s21::CalcModel(*(other.model_));
  }
  return *this;
}

// CalcModel *CalcController::getModel() const { return model_; }

CalcController::~CalcController() {
  if (model_ != nullptr) {
    delete model_;
    model_ = nullptr;
  }
}

void CalcController::putNumber(std::string str) {
  inputNumber += str;

  int count = std::count_if(inputNumber.begin(), inputNumber.end(),
                            [](auto p) { return p == '.'; });
  if (count > 1) throw std::invalid_argument("more then one dot in number");

  if (str.back() == '.') {
    isDotPreview = true;
  } else {
    isDotPreview = false;
  }
  if (!isNumberPreview) {
    model_->pushBackArithmetic(new Number(std::stof(inputNumber)));
  } else {
    model_->editBackArithmetic(new Number(std::stof(inputNumber)));
  }
  isNumberPreview = true;
}

void CalcController::putUnknown(std::string) {
  model_->pushBackArithmetic(new Unknown());
}

void CalcController::putOperations(std::string str) {
  char ch = str.at(0);
  if (model_->isUnary()) {
    model_->pushBackArithmetic(new UnaryOperations(ch));
  } else {
    model_->pushBackArithmetic(new Operations(ch));
  }
  setNotNumber();
}

void CalcController::putFunctions(std::string str) {
  model_->pushBackArithmetic(new Functions(str));
  setNotNumber();
}

void CalcController::putBracket(std::string str) {
  char ch = str.at(0);
  model_->pushBackArithmetic(new Bracket(ch));
  setNotNumber();
}

void CalcController::clearBack() {
  if (isNumberPreview && (inputNumber.length() > 1)) {
    inputNumber.pop_back();
    if (inputNumber.back() == '.') {
      isDotPreview = true;
    } else {
      isDotPreview = false;
    }

    model_->editBackArithmetic(new Number(std::stof(inputNumber)));

  } else {
    setNotNumber();
    model_->clearBackArithmetic();
    if (model_->isNumber()) {
      inputNumber = model_->toStringLast();
      isNumberPreview = true;
    }
  }
}

void CalcController::clear() {
  model_->clear();
  setNotNumber();
}

std::string CalcController::toString() {
  return model_->toString() + ((isDotPreview) ? "." : "");
}

// std::ostream &operator<<(std::ostream &out, const CalcController &value) {
//   out << "CalcController(" << *(value.model_) << ")";
//   return out;
// }

void CalcController::setNotNumber() {
  isNumberPreview = false;
  isDotPreview = false;
  inputNumber = "";
}

double CalcController::getResult(double x) {
  model_->getCheck();
  model_->getPolish();
  return model_->getResult(x);
}

double CalcController::getY(double x) { return model_->getResult(x); }

}  // namespace s21
