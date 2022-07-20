#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_calc.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

START_TEST(test_1) {
  char input_str[STR_MAX] = {"2/(3+2)*5"};
  double x = 1.0;
  double ans = 2.0 / (3.0 + 2.0) * 5.0;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_2) {
  char input_str[STR_MAX] = {"9.99999+9.999999*9.999"};
  double x = 1.0;
  double ans = 9.99999 + 9.999999 * 9.999;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_3) {
  char input_str[STR_MAX] = {"((1)-2-((-3)-(4)))-5-(-6)"};
  double x = 1.0;
  double ans = ((1) - 2 - ((-3) - (4))) - 5 - (-6);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_4) {
  char input_str[STR_MAX] = {"+5-(+4)-x+((+x)-x-(-x))"};
  double x = 12345.0;
  double ans = +5 - (+4) - x + ((+x) - x - (-x));
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_5) {
  char input_str[STR_MAX] = {"-x-(-x)"};
  double x = -123456.0;
  double ans = -x - (-x);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_6) {
  char input_str[STR_MAX] = {"-5mod-3"};
  double x = 1.0;
  double ans = fmod(-5, -3);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_7) {
  char input_str[STR_MAX] = {"2^3^4"};
  double x = 1.0;
  double ans = 4096;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_8) {
  char input_str[STR_MAX] = {"1.0/2.0*(2.0-1.0)"};
  double x = 1.0;
  double ans = 1.0 / 2.0 * (2.0 - 1.0);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_9) {
  char input_str[STR_MAX] = {"(1+2)*((3-4)+1+(5-6+7))"};
  double x = 1.0;
  double ans = (1 + 2) * ((3 - 4) + 1 + (5 - 6 + 7));
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_10) {
  char input_str[STR_MAX] = {"1.1+2.0+(3*4.0)+(5+6.78)"};
  double x = 1.0;
  double ans = 1.1 + 2.0 + (3 * 4.0) + (5 + 6.78);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_11) {
  char input_str[STR_MAX] = {"8^(1/(-x))"};
  double x = -3.0;
  double ans = 2.0;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_12) {
  char input_str[STR_MAX] = {"asin(-x+1.5)+acos(-x)-atan(x+1)"};
  double x = 1.0;
  double ans = asin(-x + 1.5) + acos(-x) - atan(x + 1);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_13) {
  char input_str[STR_MAX] = {"log(x)+ln(-2.0+4.0)"};
  double x = 100.0;
  double ans = log10(x) + log(-2.0 + 4.0);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_14) {
  char input_str[STR_MAX] = {"cos(x)^2+sin(x)^2"};
  double x = M_PI / 2.0;
  double ans = 1.0;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_15) {
  char input_str[STR_MAX] = {"-1*sin(cos(tan(-x^2)^3)^4)"};
  double x = M_PI / 2.0;
  double ans = -1 * sin(pow(cos(pow(tan(pow(-x, 2)), 3)), 4));
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_16) {
  char input_str[STR_MAX] = {"+x"};
  double x = M_PI;
  double ans = +x;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_17) {
  char input_str[STR_MAX] = {"-x"};
  double x = M_PI;
  double ans = -x;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_18) {
  char input_str[STR_MAX] = {"xmod(x+1.0)"};
  double x = M_PI;
  double ans = fmod(x, x + 1.0);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_19) {
  char input_str[STR_MAX] = {"1.2345678+2.3456789-3"};
  double x = M_PI;
  double ans = 1.2345678 + 2.3456789 - 3;
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_20) {
  char input_str[STR_MAX] = {"(-1 + (-1 - (1 + 1)) - (-1 + 1) - (-1 + (-1)))"};
  double x = M_PI;
  double ans = (-1 + (-1 - (1 + 1)) - (-1 + 1) - (-1 + (-1)));
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

START_TEST(test_21) {
  char input_str[STR_MAX] = {"sqrt(x)*ctg(x)"};
  double x = M_PI;
  double ans = sqrt(x) / tan(x);
  double res = get_result(input_str, x);
  ck_assert_double_eq(ans, res);
}
END_TEST

int test_rdontos() {
  Suite *s = suite_create("All Part");
  TCase *tc = tcase_create("Test1");
  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);

  srunner_run_all(sr, CK_ENV);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf;
}

int main(void) {
  int nf = 0;
  nf += test_rdontos();
  return nf;
}
