#pragma once

#include <math.h>

#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

namespace s21 {

enum Arithmetic_type {
  numbers,
  operations,
  functions,
  brackets,
  unknowns,
  unary
};

// ______________________________ I_Arithmetic ______________________________
class I_Arithmetic {
 protected:
  virtual void print(std::ostream &os) const = 0;

 public:
  friend std::ostream &operator<<(std::ostream &str, I_Arithmetic const &data);
  virtual Arithmetic_type get_type() const = 0;
  virtual ~I_Arithmetic() {}
  virtual int get_priority() const = 0;
};

// ______________________________ Number ______________________________
class Number : public I_Arithmetic {
 private:
  double number_ = 0;

 public:
  explicit Number(double number);
  double get_number();
  virtual Arithmetic_type get_type() const override;
  virtual int get_priority() const override;

 protected:
  virtual void print(std::ostream &os) const override;
};

// ______________________________ Unknown ______________________________
class Unknown : public I_Arithmetic {
 public:
  Number get_number(double num);
  virtual Arithmetic_type get_type() const override;
  virtual int get_priority() const override;

 protected:
  virtual void print(std::ostream &os) const override;
};

// ______________________________ Operations ______________________________
class Operations : public I_Arithmetic {
 private:
  char operations_ = '\0';

 public:
  explicit Operations(char operations);
  Number get_result(Number &operand1, Number &operand2);
  virtual int get_priority() const override;

 protected:
  virtual void print(std::ostream &os) const override;
  virtual Arithmetic_type get_type() const override;
};

// ______________________________ Unary Operations______________________________
class UnaryOperations : public I_Arithmetic {
 private:
  char operations_ = '\0';

 public:
  explicit UnaryOperations(char operations);
  Number get_result(Number &operand);
  virtual int get_priority() const override;

 protected:
  virtual void print(std::ostream &os) const override;
  virtual Arithmetic_type get_type() const override;
};

// ______________________________ Functions ______________________________
class Functions : public I_Arithmetic {
 public:
  enum Function { cos_ = 1, sin_, tan_, acos_, asin_, atan_, sqrt_, ln_, log_ };

 private:
  Function function_;

 public:
  // Functions(Function functions);
  explicit Functions(const std::string &str);
  static Function getFunction(const std::string &str);
  static std::string getString(Function functions);
  Number get_result(Number &operand);
  virtual Arithmetic_type get_type() const override;
  virtual int get_priority() const override;

 protected:
  virtual void print(std::ostream &os) const override;
};

// ______________________________ Bracket ______________________________
class Bracket : public I_Arithmetic {
 private:
  char bracket_ = '\0';

 public:
  explicit Bracket(char bracket);

  virtual Arithmetic_type get_type() const override;
  char get_bracket();
  virtual int get_priority() const override;

 protected:
  virtual void print(std::ostream &os) const override;
};

}  // namespace s21
