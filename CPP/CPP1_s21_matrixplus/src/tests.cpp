#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

void fill_matrix(S21Matrix *matr);

/* конструкторы и деструкторы */

TEST(create, create_a1) {
  S21Matrix a(3, 4);
  fill_matrix(&a);
  EXPECT_EQ(a(2, 3), 3 * 4);
  EXPECT_EQ(a(1, 1), 6);
  EXPECT_EQ(a.get_rows(), 3);
  EXPECT_EQ(a.get_cols(), 4);
}

TEST(create, create_a2) {
  S21Matrix a(3);
  fill_matrix(&a);
  EXPECT_EQ(a(2, 2), 9);
}

TEST(create, create_a3) {
  S21Matrix a;
  fill_matrix(&a);
  EXPECT_EQ(a(2, 2), 9);
}

TEST(create, create_copy1) {
  S21Matrix a(3);
  fill_matrix(&a);
  S21Matrix b(a);
  EXPECT_TRUE(a == b);
}

TEST(create, create_copy2) {
  S21Matrix a(2, 3);
  fill_matrix(&a);
  S21Matrix b(a);
  EXPECT_TRUE(a == b);
}

TEST(create, create_move1) {
  S21Matrix a(2, 3);
  fill_matrix(&a);
  S21Matrix b(std::move(a));
  EXPECT_EQ(a.get_rows(), 0);
  EXPECT_EQ(a.get_cols(), 0);
  EXPECT_TRUE(a.get_matrix() == NULL);
  EXPECT_EQ(b.get_rows(), 2);
  EXPECT_EQ(b.get_cols(), 3);
  EXPECT_EQ(b(1, 2), 6);
}

/* accessor и mutator */

TEST(get_set, set_rows1) {
  S21Matrix a(3, 3);
  fill_matrix(&a);
  a.set_rows(2);
  S21Matrix b(2, 3);
  double f[]{1, 2, 3, 4, 5, 6};
  b.set_matrix(f);
  EXPECT_TRUE(a == b);
}

TEST(get_set, set_rows2) {
  S21Matrix a(3, 3);
  fill_matrix(&a);
  a.set_rows(4);
  S21Matrix b(4, 3);
  double f[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0};
  b.set_matrix(f);
  EXPECT_TRUE(a == b);
}

TEST(get_set, set_cols1) {
  S21Matrix a(3, 3);
  fill_matrix(&a);
  a.set_cols(2);
  S21Matrix b(3, 2);
  double f[]{1, 2, 4, 5, 7, 8};
  b.set_matrix(f);
  EXPECT_TRUE(a == b);
}

TEST(get_set, set_cols2) {
  S21Matrix a(3, 3);
  fill_matrix(&a);
  a.set_cols(4);
  S21Matrix b(3, 4);
  double f[]{1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0};
  b.set_matrix(f);
  EXPECT_TRUE(a == b);
}

TEST(get_set, set_matrix) {
  S21Matrix a(2, 3);
  fill_matrix(&a);
  // std::cout << "a" << a << std::endl;
  S21Matrix b(2, 3);
  double f[]{1, 2, 3, 4, 5, 6};
  b.set_matrix(f);
  // std::cout << "b" << b << std::endl;
  EXPECT_TRUE(a == b);
  b.set_matrix(1, 1, 0);
  EXPECT_EQ(b.get_matrix(1, 1), 0);
  EXPECT_FALSE(a == b);
}

TEST(get_set, get_matrix) {
  S21Matrix a(2, 3);
  fill_matrix(&a);
  EXPECT_EQ(a.get_rows(), 2);
  EXPECT_EQ(a.get_cols(), 3);
  EXPECT_EQ(a(1, 1), 5);
  EXPECT_EQ(a.get_matrix(1, 1), 5);
  EXPECT_EQ(a(1, 2), 6);
  EXPECT_EQ(a.get_matrix(1, 2), 6);
}

/* операций над матрицами */

TEST(method, eq1) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 2);
  EXPECT_FALSE(a == b);
  EXPECT_FALSE(a.eq_matrix(b));
}

TEST(method, eq2) {
  S21Matrix a(3, 2);
  S21Matrix b(3, 2);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(a.eq_matrix(b));
}

TEST(method, eq3) {
  S21Matrix a(2, 3);
  fill_matrix(&a);
  S21Matrix b(2, 3);
  fill_matrix(&b);
  EXPECT_TRUE(a == b);
  b(0, 0) += 2 * EPS;
  EXPECT_FALSE(a == b);
  a(0, 0) += 2 * EPS;
  EXPECT_TRUE(a == b);
}

TEST(method, sum_sub1) {
  // нулевые не изменятся, но утечки памяти проверить удобно
  S21Matrix a(2, 3);
  S21Matrix b(2, 3);
  a.sum_matrix(b);
  b.sub_matrix(a);
  EXPECT_TRUE(a == b);
  S21Matrix c = (a + b);
  EXPECT_TRUE(c == a);
  c = a + b;
  EXPECT_TRUE(c == a);
  c -= a + b;
  EXPECT_TRUE(c == a);
  c += a - b;
  EXPECT_TRUE(c == a);
  c = a - b;
  EXPECT_TRUE(c == a);
}

TEST(method, sum_sub_mul_numb1) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);
  S21Matrix c(4, 3);
  S21Matrix res(4, 3);
  double f[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double res_f[]{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
  a.set_matrix(f);
  b.set_matrix(f);
  b *= -1.0;
  EXPECT_FALSE(a == b);
  a.sum_matrix(b);
  EXPECT_TRUE(a == res);
  a.set_matrix(f);
  a.sub_matrix(b);
  res.set_matrix(res_f);
  EXPECT_TRUE(a == res);
  a += b;
  a.mul_number(-1.0);
  EXPECT_TRUE(a == b);
  b -= a * 3.0;
  EXPECT_TRUE(b == res);
  b = b * 0.5;
  EXPECT_TRUE(b == a + res);
}

TEST(method, mul_matr1) {
  S21Matrix a(3, 4);
  S21Matrix a1(3, 4);
  S21Matrix b(4, 2);
  S21Matrix c(3, 2);

  double f1[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double f2[]{0, 2, 4, 6, 8, 10, 12, 14};
  double res_f[]{80, 100, 176, 228, 272, 356};

  a.set_matrix(f1);
  a1.set_matrix(f1);
  b.set_matrix(f2);
  c.set_matrix(res_f);

  EXPECT_TRUE(a * b == c);
  a.mul_matrix(b);
  EXPECT_TRUE(a == c);
  a1 *= b;
  EXPECT_TRUE(a1 == c);
}

TEST(method, transpose) {
  S21Matrix a(3, 4);
  S21Matrix a_res(4, 3);
  S21Matrix b(2, 2);
  S21Matrix b_res(2, 2);

  double f1[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double f1_res[]{1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12};

  double f2[]{0, 2, 4, 6};
  double f2_res[]{0, 4, 2, 6};

  a.set_matrix(f1);
  a_res.set_matrix(f1_res);
  b.set_matrix(f2);
  b_res.set_matrix(f2_res);

  EXPECT_TRUE(a.transpose() == a_res);
  EXPECT_TRUE(b.transpose() == b_res);
}

TEST(method, determinant_calc_complements_inverse_matrix) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  S21Matrix c(1, 1);
  double f[]{4, 5, -6, 7, 8, 9, -10, 11, 12};
  a.set_matrix(f);
  b.set_matrix(f);
  c.set_matrix(f);
  EXPECT_EQ(a.determinant(), -1824);
  EXPECT_EQ(b.determinant(), 58);
  EXPECT_EQ(c.determinant(), 4);
  S21Matrix a_r(3, 3);
  S21Matrix b_r(2, 2);
  S21Matrix c_r(1, 1);
  double a_res1[]{-3, -174, 157, -126, -12, -94, 93, -78, -3};
  double b_res1[]{7, 6, -5, 4};
  double c_res1[]{1};
  a_r.set_matrix(a_res1);
  b_r.set_matrix(b_res1);
  c_r.set_matrix(c_res1);
  EXPECT_TRUE(a.calc_complements() == a_r);
  EXPECT_TRUE(b.calc_complements() == b_r);
  EXPECT_TRUE(c.calc_complements() == c_r);

  S21Matrix a_i(3, 3);
  S21Matrix b_i(2, 2);
  S21Matrix c_i(1, 1);

  double f_a_i[]{1, 0, 0, 0, 1, 0, 0, 0, 1};
  double f_b_i[]{1, 0, 0, 1};
  a_i.set_matrix(f_a_i);
  b_i.set_matrix(f_b_i);
  c_i.set_matrix(f_b_i);
  EXPECT_TRUE(a.inverse_matrix() * a == a_i);
  EXPECT_TRUE(b.inverse_matrix() * b == b_i);
  EXPECT_TRUE(c.inverse_matrix() * c == c_i);
}
/* exception */

TEST(create, create_err1) {  // DISABLED_ ошибочная утечка на мак, на ubuntu ok
  EXPECT_THROW(S21Matrix a(-1, 5), std::out_of_range);
}

TEST(get_set,
     get_set_matrix_err1) {  // DISABLED_ ошибочная утечка на мак, на ubuntu ok
  S21Matrix a(2, 3);
  fill_matrix(&a);
  EXPECT_THROW(a(0, 5), std::out_of_range);
  EXPECT_THROW(a(0, -5) = 1.0, std::out_of_range);
  EXPECT_THROW(a.get_matrix(0, -5), std::out_of_range);
  EXPECT_THROW(a.set_matrix(0, -5, 1.0), std::out_of_range);
}

TEST(method,
     mul_matr_err1) {  // DISABLED_ ошибочная утечка на мак, на ubuntu ok
  S21Matrix a(3, 3);
  S21Matrix b(4, 2);
  S21Matrix c(4, 3);
  // проверка совместимости размеров
  EXPECT_THROW(a * b, std::invalid_argument);
  EXPECT_THROW(a.mul_matrix(b), std::invalid_argument);
  EXPECT_THROW(c = a * b, std::invalid_argument);
  EXPECT_THROW(a *= b, std::invalid_argument);
}

TEST(method, det_calc_comp_invers_err1) {
  S21Matrix a(3, 4);
  // проверка квадратная
  EXPECT_THROW(a.calc_complements(), std::invalid_argument);
  EXPECT_THROW(a.determinant(), std::invalid_argument);
  EXPECT_THROW(a.inverse_matrix(), std::invalid_argument);
}

TEST(method, det_calc_comp_invers_err2) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  S21Matrix c(1, 1);
  double f[]{0, 1, 2, 3, 4, 5, 6, 7, 8};
  double f2[]{1, 2, 4, 8};
  a.set_matrix(f);
  b.set_matrix(f2);
  c.set_matrix(f);
  // определитель = 0
  EXPECT_EQ(a.determinant(), 0);
  EXPECT_EQ(b.determinant(), 0);
  EXPECT_EQ(c.determinant(), 0);
  EXPECT_THROW(a.inverse_matrix(), std::invalid_argument);
  EXPECT_THROW(b.inverse_matrix(), std::invalid_argument);
  EXPECT_THROW(c.inverse_matrix(), std::invalid_argument);
}

/* other */

TEST(other, print_test) {
  S21Matrix a(3, 3);
  double f[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(f);
  std::cout << "a" << a << std::endl;
}

/* main */

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void fill_matrix(S21Matrix *matr) {
  for (int i = 0; i < matr->get_rows(); i++) {
    for (int j = 0; j < matr->get_cols(); j++) {
      (*matr)(i, j) = i * matr->get_cols() + j + 1;
    }
  }
}
