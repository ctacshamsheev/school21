#include "arithmetic.h"

namespace s21 {

std::ostream &operator<<(std::ostream &str, I_Arithmetic const &data) {
  data.print(str);
  return str;
}

// ______________________________ Number ______________________________

Number::Number(double number) { number_ = number; }

Arithmetic_type Number::get_type() const { return numbers; }

double Number::get_number() { return number_; }

void Number::print(std::ostream &os) const { os << number_; };

int Number::get_priority() const {
  throw std::invalid_argument("Number::get_priority");
}

// ______________________________ Unknown ______________________________

Number Unknown::get_number(double num) { return Number(num); }

Arithmetic_type Unknown::get_type() const { return unknowns; }

void Unknown::print(std::ostream &os) const { os << "x"; };

int Unknown::get_priority() const {
  throw std::invalid_argument("Unknown::get_priority");
}

// ______________________________ Operations ______________________________

Operations::Operations(char operations) { operations_ = operations; }

Number Operations::get_result(Number &operand1, Number &operand2) {
  double result;
  double a = operand1.get_number();
  double b = operand2.get_number();

  switch (operations_) {
    case '+':
      result = a + b;
      break;
    case '-':
      result = a - b;
      break;
    case '*':
      result = a * b;
      break;
    case '/':
      result = a / b;
      break;
    case '^':
      result = pow(a, b);
      break;
    case 'm':
      result = fmod(a, b);
      break;
    default:
      throw std::invalid_argument("unknown operations :");
      // + operations_);
      break;
  }
  return Number(result);
}

void Operations::print(std::ostream &os) const {
  if (operations_ == 'm')
    os << "mod";
  else
    os << operations_;
}

Arithmetic_type Operations::get_type() const { return operations; }

int Operations::get_priority() const {
  int result = 0;
  switch (operations_) {
    case '+':
    case '-':
      result = 1;
      break;
    case '*':
    case '/':
      result = 2;
      break;
    case '^':
    case 'm':
      result = 3;
      break;
    default:
      throw std::invalid_argument("unknown operations :");
      break;
  }
  return result;
}

// ______________________________ UnaryOperations ______________________________

UnaryOperations::UnaryOperations(char operations) { operations_ = operations; }

Number UnaryOperations::get_result(Number &operand) {
  double result;
  double a = operand.get_number();
  switch (operations_) {
    case '+':
      result = a;
      break;
    case '-':
      result = -1 * a;
      break;
    default:
      throw std::invalid_argument("unknown functions :");
      break;
  }
  return Number(result);
}

void UnaryOperations::print(std::ostream &os) const { os << operations_; }

Arithmetic_type UnaryOperations::get_type() const { return unary; }

int UnaryOperations::get_priority() const { return 6; }

// ______________________________ Functions ______________________________

Functions::Functions(const std::string &str) { function_ = getFunction(str); }

Functions::Function Functions::getFunction(const std::string &str) {
  std::map<std::string, Function> mapStringToFunction = {
      {"cos", cos_},   {"sin", sin_},   {"tan", tan_},
      {"acos", acos_}, {"asin", asin_}, {"atan", atan_},
      {"sqrt", sqrt_}, {"ln", ln_},     {"log", log_}};
  return mapStringToFunction[str];
}

std::string Functions::getString(Function functions) {
  std::map<Function, std::string> mapFunctionToString = {
      {cos_, "cos"},   {sin_, "sin"},   {tan_, "tan"},
      {acos_, "acos"}, {asin_, "asin"}, {atan_, "atan"},
      {sqrt_, "sqrt"}, {ln_, "ln"},     {log_, "log"}};
  if (functions == 0) {
    throw std::invalid_argument("unknown functions");
  }
  return mapFunctionToString[functions];
}

Number Functions::get_result(Number &operand) {
  double result;
  double x = operand.get_number();

  switch (function_) {
    case cos_:
      result = cos(x);
      break;
    case sin_:
      result = sin(x);
      break;
    case tan_:
      result = tan(x);
      break;
    case acos_:
      result = acos(x);
      break;
    case asin_:
      result = asin(x);
      break;
    case atan_:
      result = atan(x);
      break;
    case sqrt_:
      result = sqrt(x);
      break;
    case ln_:
      result = log(x);
      break;
    case log_:
      result = log10(x);
      break;
    default:
      throw std::invalid_argument("unknown functions");
      break;
  }
  return Number(result);
}

Arithmetic_type Functions::get_type() const { return functions; }

void Functions::print(std::ostream &os) const { os << getString(function_); }

int Functions::get_priority() const { return 4; }

// ______________________________ Bracket ______________________________

void Bracket::print(std::ostream &os) const { os << bracket_; };

Bracket::Bracket(char bracket) { bracket_ = bracket; }

Arithmetic_type Bracket::get_type() const { return brackets; }

char Bracket::get_bracket() { return bracket_; }

int Bracket::get_priority() const { return -1; }

}  // namespace s21
