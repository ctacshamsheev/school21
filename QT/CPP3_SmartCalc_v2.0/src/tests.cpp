#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <string>

#include "arithmetic.h"
#include "s21CalcController.h"
#include "s21CalcModel.h"

using namespace s21;

// ------------------------- polish --------------------------

TEST(polish, s21_CalcController_test_polish_1) {
  CalcController a;
  a.putOperations("-");
  a.putNumber("1.23");
  EXPECT_EQ(a.toString(), "- 1.23");
  EXPECT_FLOAT_EQ(a.getResult(0), -1.23);
}

TEST(polish, s21_CalcController_test_polish_2_1) {
  CalcController a;
  a.putOperations("-");
  a.putUnknown("x");
  EXPECT_EQ(a.toString(), "- x");
  EXPECT_FLOAT_EQ(a.getResult(1.23), -1.23);
}

TEST(polish, s21_CalcController_test_polish_2_2) {
  CalcController a;
  a.putOperations("+");
  a.putUnknown("x");
  EXPECT_EQ(a.toString(), "+ x");
  EXPECT_FLOAT_EQ(a.getResult(1.23), 1.23);
}

TEST(polish, s21_CalcController_test_polish_3) {
  CalcController a;
  a.putOperations("-");
  a.putUnknown("x");
  a.putOperations("^");
  a.putUnknown("x");
  EXPECT_EQ(a.toString(), "- x ^ x");
  EXPECT_FLOAT_EQ(a.getResult(2), 4);
}

TEST(polish, s21_CalcController_test_polish_4) {
  CalcController a;
  a.putNumber("2");
  a.putOperations("+");
  a.putNumber("2");
  a.putOperations("*");
  a.putNumber("2");
  EXPECT_EQ(a.toString(), "2 + 2 * 2");
  EXPECT_FLOAT_EQ(a.getResult(2), 6);
}

TEST(polish, s21_CalcController_test_polish_5) {
  CalcController a;
  a.putBracket("(");
  a.putNumber("2");
  a.putOperations("+");
  a.putNumber("2");
  a.putBracket(")");
  a.putOperations("*");
  a.putNumber("2");
  EXPECT_EQ(a.toString(), "( 2 + 2 ) * 2");
  EXPECT_FLOAT_EQ(a.getResult(2), 8);
}

TEST(polish, s21_CalcController_test_polish_6) {
  CalcController a;
  a.putNumber("5.5");
  a.putOperations("m");
  a.putNumber("2.5");
  EXPECT_EQ(a.toString(), "5.5 mod 2.5");
  EXPECT_FLOAT_EQ(a.getResult(0), 0.5);
}

TEST(polish, s21_CalcController_test_polish_7) {
  // sin(3.14 * cos(3.14 * asin(acos(sqrt(atan(tan(x)))))))
  CalcController b;
  b.putFunctions("sin");
  b.putBracket("(");
  b.putNumber("3.14");
  b.putOperations("*");
  b.putFunctions("cos");
  b.putBracket("(");
  b.putNumber("3.14");
  b.putOperations("*");
  b.putFunctions("asin");
  b.putBracket("(");
  b.putFunctions("acos");
  b.putBracket("(");
  b.putFunctions("sqrt");
  b.putBracket("(");
  b.putFunctions("atan");
  b.putBracket("(");
  b.putFunctions("tan");
  b.putBracket("(");
  b.putUnknown("x");
  b.putBracket(")");
  b.putBracket(")");
  b.putBracket(")");
  b.putBracket(")");
  b.putBracket(")");
  b.putBracket(")");
  b.putBracket(")");

  EXPECT_EQ(b.toString(),
            "sin ( 3.14 * cos ( 3.14 * asin ( acos ( sqrt ( atan "
            "( tan ( x ) ) ) ) ) ) )");
  EXPECT_FLOAT_EQ(b.getResult(0.5), -0.14609);
  CalcController a;
  a = b;
  EXPECT_EQ(a.toString(),
            "sin ( 3.14 * cos ( 3.14 * asin ( acos ( sqrt ( atan "
            "( tan ( x ) ) ) ) ) ) )");
  EXPECT_FLOAT_EQ(a.getResult(0.5), -0.14609);
}

TEST(polish, s21_CalcController_test_polish_8) {
  CalcController b;
  b.putFunctions("ln");
  b.putBracket("(");
  b.putUnknown("x");
  b.putBracket(")");
  b.putOperations("*");
  b.putFunctions("log");
  b.putBracket("(");
  b.putUnknown("x");
  b.putBracket(")");
  EXPECT_EQ(b.toString(), "ln ( x ) * log ( x )");
  EXPECT_NEAR(b.getResult(0.5), 0.20865809275, 1e-6);
}

TEST(polish, s21_CalcController_test_polish) {
  CalcController b(new CalcModel());
  b.putOperations("-");
  b.clearBack();
  b.putFunctions("sin");
  b.putBracket("(");
  b.putOperations("-");
  b.putNumber("3.14");
  b.putOperations("-");
  b.putUnknown("x");  // x
  b.putBracket(")");
  b.putOperations("/");
  b.putNumber("5");
  b.putOperations("*");
  b.putNumber("6");
  EXPECT_EQ(b.toString(), "sin ( - 3.14 - x ) / 5 * 6");
  EXPECT_NEAR(b.getResult(0), -0.00191118349, 1e-6);
  EXPECT_NEAR(b.getY(-3.14), 0, 1e-6);
  b.clear();
  b.putOperations("-");
  EXPECT_EQ(b.toString(), "-");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

// // ------------------------- number --------------------------

TEST(create_number, s21_CalcController_putNumber_1) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.clearBack();
  b.putNumber("4");
  b.putNumber("5");
  b.clearBack();
  b.putNumber("9");
  EXPECT_EQ(b.toString(), "12.49");
  EXPECT_FLOAT_EQ(b.getResult(0), 12.49);
}

TEST(create_number, s21_CalcController_putNumber_2) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.clearBack();
  b.clearBack();
  b.clearBack();
  EXPECT_EQ(b.toString(), "1");
  EXPECT_FLOAT_EQ(b.getResult(0), 1);
}

TEST(create_number, s21_CalcController_putNumber_3) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.clearBack();
  b.clearBack();
  b.clearBack();
  b.clearBack();
  b.clearBack();
  EXPECT_EQ(b.toString(), "");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(create_number, s21_CalcController_putNumber_4) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.putNumber("4");
  b.clear();
  b.clearBack();
  b.clearBack();
  EXPECT_EQ(b.toString(), "");

#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(create_number, s21_CalcController_putNumber_5) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.clearBack();
  b.clearBack();
  b.putNumber("4");
  EXPECT_EQ(b.toString(), "124");
  EXPECT_FLOAT_EQ(b.getResult(0), 124);
}

TEST(create_number, s21_CalcController_putNumber_6) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.putOperations("-");
  b.clearBack();
  b.clearBack();
  b.putNumber("4");
  EXPECT_EQ(b.toString(), "12.4");
  EXPECT_FLOAT_EQ(b.getResult(0), 12.4);
}

TEST(create_number, s21_CalcController_putNumber_7) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putNumber("2");
  b.putNumber(".");
  b.putNumber("3");
  b.putOperations("-");
  b.clearBack();
  b.clearBack();
  b.clearBack();
  b.putNumber("4");
  EXPECT_EQ(b.toString(), "124");
  EXPECT_FLOAT_EQ(b.getResult(0), 124);
}

// ------------------------- error polish --------------------------

TEST(polish_err, s21_CalcController_test_polish_err_1) {
  CalcController b(new CalcModel());
  b.putOperations("-");
  b.putOperations("-");
  b.putNumber("1");
  EXPECT_EQ(b.toString(), "- - 1");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_2) {
  CalcController b(new CalcModel());
  b.putBracket(")");
  b.putNumber("1");
  b.putBracket("(");
  EXPECT_EQ(b.toString(), ") 1 (");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_3) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putBracket("(");
  EXPECT_EQ(b.toString(), "1 (");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_4) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putOperations("-");
  b.putOperations("-");
  b.putNumber("1");
  EXPECT_EQ(b.toString(), "1 - - 1");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_5) {
  CalcController b(new CalcModel());
  b.putNumber("1");
  b.putOperations("-");
  b.putNumber("1");
  b.putOperations("-");
  EXPECT_EQ(b.toString(), "1 - 1 -");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_6) {
  CalcController b(new CalcModel());
  b.putFunctions("sin");
  b.putFunctions("cos");
  b.putNumber("1");
  EXPECT_EQ(b.toString(), "sin cos 1");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_7) {
  CalcController b(new CalcModel());
  b.putFunctions("log");
  b.putBracket("(");
  b.putBracket(")");
  EXPECT_EQ(b.toString(), "log ( )");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_8) {
  CalcController b(new CalcModel());
  b.putFunctions("atan");
  EXPECT_EQ(b.toString(), "atan");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

TEST(polish_err, s21_CalcController_test_polish_err_9) {
  CalcController b(new CalcModel());
  b.putFunctions("asin");
  b.putFunctions("acos");
  b.putBracket("(");
  b.putNumber("1");
  b.putBracket(")");
  EXPECT_EQ(b.toString(), "asin acos ( 1 )");
#ifndef __APPLE__
  EXPECT_ANY_THROW(b.getResult(0));
#endif
}

// ------------------------- copy --------------------------

TEST(polish_err, s21_CalcController_test_copy) {
  CalcController a(new CalcModel());
  a.putOperations("-");
  a.putNumber("2");
  a.putOperations("+");
  a.putNumber("2");
  a.putOperations("*");
  a.putNumber("2");
  EXPECT_EQ(a.toString(), "- 2 + 2 * 2");

  EXPECT_FLOAT_EQ(a.getResult(0), 2);
  CalcController b(a);
  EXPECT_EQ(b.toString(), "- 2 + 2 * 2");
  EXPECT_FLOAT_EQ(b.getResult(0), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
