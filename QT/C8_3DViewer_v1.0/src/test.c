#include <check.h>
#include <math.h>
#include <stdio.h>

#include "parser.h"
#include "s21_matrix.h"
#include "stack.h"
#include "stack_i.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void print_test(char *name);
void fill_matrix(matrix_t *A);
double test_determ(double *f, int n);
void test_inverse_matr(double *arr, double *res, int n);
void test_rotation(matrix_t (*f)(double));
void test_rotation_2(matrix_t (*f)(double), double arg, double *arr_res);
void test_shift_scale(matrix_t (*f)(double, double, double), double arg1,
                      double arg2, double arg3, double *arr_res);
void test_matrix_all(double *arg, double *arr_res);

START_TEST(test_create_matrix) {
  print_test("#TEST1: s21_create_matrix, s21_eq_matrix, s21_remove_matrix");
  matrix_t A = s21_create_matrix(5, 7);
  matrix_t B = s21_create_matrix(7, 5);
  matrix_t C = s21_create_matrix(5, 7);
  matrix_t D = s21_create_matrix(-5, 7);
  matrix_t E = s21_create_matrix(1, 1);

  ck_assert_int_eq(A.matrix_type, ZERO_MATRIX);
  ck_assert_int_eq(B.matrix_type, ZERO_MATRIX);
  ck_assert_int_eq(C.matrix_type, ZERO_MATRIX);
  ck_assert_int_eq(D.matrix_type, INCORRECT_MATRIX);
  fill_matrix(&A);
  fill_matrix(&B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);
  fill_matrix(&C);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), SUCCESS);
  A.matrix[2][2] = 8.000005;
  ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&E, &E), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  s21_remove_matrix(&E);

  ck_assert_int_eq(A.matrix_type, INCORRECT_MATRIX);
  ck_assert_ptr_eq(A.matrix, NULL);
  ck_assert_int_eq(B.matrix_type, INCORRECT_MATRIX);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  ck_assert_int_eq(D.matrix_type, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_sum_sub) {
  print_test("#TEST2: s21_sum_matrix, s21_sub_matrix");
  matrix_t A = s21_create_matrix(5, 7);
  matrix_t B = s21_create_matrix(7, 5);
  matrix_t C = s21_create_matrix(5, 7);

  fill_matrix(&A);
  fill_matrix(&B);
  fill_matrix(&C);

  matrix_t AB = s21_sub_matrix(&A, &B);
  ck_assert_int_eq(AB.matrix_type, INCORRECT_MATRIX);
  matrix_t AC = s21_sum_matrix(&A, &C);
  ck_assert_int_eq(AC.matrix_type, CORRECT_MATRIX);
  matrix_t CA = s21_sub_matrix(&AC, &C);
  ck_assert_int_eq(s21_eq_matrix(&CA, &A), SUCCESS);
  matrix_t CB = s21_sub_matrix(&AC, &A);
  ck_assert_int_eq(s21_eq_matrix(&CA, &C), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&AC);
  s21_remove_matrix(&CA);
  s21_remove_matrix(&CB);
}
END_TEST

START_TEST(test_mult_number) {
  print_test("#TEST3: s21_mult_number");
  matrix_t A = s21_create_matrix(2, 3);
  matrix_t B = s21_create_matrix(2, 3);

  A.matrix_type = CORRECT_MATRIX;
  B.matrix_type = CORRECT_MATRIX;

  double arr[] = {0, 0.5, 1.0, 1.5, 2, 2.5, 3};

  matrix_fill_array(&A, arr);

  fill_matrix(&B);

  matrix_t C = s21_mult_number(&A, 2.0);

  ck_assert_int_eq(s21_eq_matrix(&C, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix) {
  print_test("#TEST4: s21_mult_matrix");
  matrix_t A = s21_create_matrix(4, 3);
  matrix_t B = s21_create_matrix(3, 4);
  matrix_t C = s21_create_matrix(2, 4);
  fill_matrix(&A);
  fill_matrix(&B);
  double arrC[] = {1, 2, -1, -2, 3, -3, 4, -4};
  matrix_fill_array(&C, arrC);

  matrix_t AB = s21_mult_matrix(&A, &B);
  matrix_t AC = s21_mult_matrix(&A, &C);
  matrix_t CA = s21_mult_matrix(&C, &A);
  matrix_t CB = s21_mult_matrix(&C, &B);

  ck_assert_int_eq(AC.matrix_type, INCORRECT_MATRIX);
  ck_assert_int_eq(CB.matrix_type, INCORRECT_MATRIX);

  matrix_t AB_res = s21_create_matrix(4, 4);
  matrix_t CA_res = s21_create_matrix(2, 3);

  double arrAB_res[] = {20, 23,  26,  29,  56,  68,  80,  92,
                        92, 113, 134, 155, 128, 158, 188, 218};
  matrix_fill_array(&AB_res, arrAB_res);
  double arrCA_res[] = {-18, -18, -18, -21, -21, -21};
  matrix_fill_array(&CA_res, arrCA_res);

  ck_assert_int_eq(s21_eq_matrix(&AB, &AB_res), SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&CA, &CA_res), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  s21_remove_matrix(&AB_res);
  s21_remove_matrix(&CA_res);

  s21_remove_matrix(&AB);
  s21_remove_matrix(&AC);
  s21_remove_matrix(&CA);
  s21_remove_matrix(&CB);
}
END_TEST

START_TEST(test_transpose) {
  print_test("#TEST5: s21_transpose");
  matrix_t A = s21_create_matrix(2, 3);
  fill_matrix(&A);
  matrix_t B = s21_transpose(&A);
  matrix_t C = s21_transpose(&B);
  matrix_t D = s21_create_matrix(-4, 3);
  matrix_t F = s21_transpose(&D);

  ck_assert_int_eq(F.matrix_type, INCORRECT_MATRIX);

  ck_assert_int_eq(s21_eq_matrix(&A, &C), SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  s21_remove_matrix(&F);
}
END_TEST

START_TEST(test_determinant) {
  print_test("#TEST6: s21_determinant");

  double f1[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  ck_assert_double_eq(test_determ(f1, 3), -40.0);

  double f2[] = {15.0};
  ck_assert_double_eq(test_determ(f2, 1), 15.0);

  double f3[] = {4, 2, 2, 1};
  ck_assert_double_eq(test_determ(f3, 2), 0.0);

  double f4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ck_assert_double_eq(test_determ(f4, 3), 0.0);

  double f5[] = {1, 5, 6, 3, 4, 2, -1, 3, -2, 3, 4, 5, -1, 6, 9, 8};
  ck_assert_double_eq(test_determ(f5, 4), 181.0);

  ck_assert_int_eq(isnan(test_determ(f5, 0)), 1);
}
END_TEST

START_TEST(test_calc_complements) {
  print_test("#TEST7: s21_calc_complements");
  matrix_t A = s21_create_matrix(3, 3);
  double arr[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  matrix_fill_array(&A, arr);
  matrix_t B = s21_calc_complements(&A);
  matrix_t B_res = s21_create_matrix(3, 3);
  double f[] = {0.00, 10.00, -20.00, 4.00, -14.00, 8.00, -8.00, -2.00, 4.00};
  matrix_fill_array(&B_res, f);

  ck_assert_int_eq(s21_eq_matrix(&B, &B_res), SUCCESS);

  matrix_t C = s21_create_matrix(-3, 3);
  matrix_t D = s21_calc_complements(&C);
  ck_assert_int_eq(D.matrix_type, INCORRECT_MATRIX);

  matrix_t E = s21_create_matrix(1, 1);
  double e[] = {10.00};
  matrix_fill_array(&E, e);

  matrix_t F = s21_calc_complements(&E);
  ck_assert_float_eq(F.matrix[0][0], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&B_res);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  s21_remove_matrix(&E);
  s21_remove_matrix(&F);
}
END_TEST

START_TEST(test_inverse_matrix) {
  print_test("#TEST8: s21_inverse_matrix");
  double arr[] = {1, -2, 3, 0, 4, -1, 5, 0, 0};
  double f[] = {0.00, 0.00, 0.20, 0.10, 0.30, -0.02, 0.40, 0.20, -0.08};
  test_inverse_matr(arr, f, 3);

  double arr1[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double f1[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  test_inverse_matr(arr1, f1, 3);

  double arr2[] = {157};
  double f2[] = {1.0 / arr2[0]};
  test_inverse_matr(arr2, f2, 1);
}
END_TEST

START_TEST(test_get_rotation_x) {
  print_test("#TEST9: matrix_get_rotation_x");
  test_rotation(matrix_get_rotation_x);
  test_rotation_2(matrix_get_rotation_x, M_PI,
                  (double[]){1.0, -1.0, -1.0, 1.0});
}
END_TEST

START_TEST(test_get_rotation_y) {
  print_test("#TEST10: matrix_get_rotation_y");
  test_rotation(matrix_get_rotation_y);
  test_rotation_2(matrix_get_rotation_y, M_PI,
                  (double[]){-1.0, 1.0, -1.0, 1.0});
}
END_TEST

START_TEST(test_get_rotation_z) {
  print_test("#TEST11: matrix_get_rotation_x");
  test_rotation(matrix_get_rotation_z);
  test_rotation_2(matrix_get_rotation_z, M_PI,
                  (double[]){-1.0, -1.0, 1.0, 1.0});
}

START_TEST(test_get_shift) {
  print_test("#TEST12: matrix_get_shift");
  test_shift_scale(matrix_get_shift, 1.0, 0.0, 0.0,
                   (double[]){2.0, 1.0, 1.0, 1.0});
  test_shift_scale(matrix_get_shift, -1.0, 1.0, -3.0,
                   (double[]){0.0, 2.0, -2.0, 1.0});
  test_shift_scale(matrix_get_shift, -1.0, 1.0, -3.0,
                   (double[]){0.0, 2.0, -2.0, 1.0});
}

START_TEST(test_get_scale) {
  print_test("#TEST13: matrix_get_scale");
  test_shift_scale(matrix_get_scaling, 1.0, 2.0, 0.0,
                   (double[]){1.0, 2.0, 0.0, 1.0});
  test_shift_scale(matrix_get_scaling, -1.5, -2.0, -0.5,
                   (double[]){-1.5, -2.0, -0.5, 1.0});
  test_shift_scale(matrix_get_scaling, 1.1, 1.1, 1.1,
                   (double[]){1.1, 1.1, 1.1, 1.0});
}

START_TEST(test_get_all) {
  print_test("#TEST14: matrix_get_all");
  test_matrix_all((double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0},
                  (double[]){1.0, 1.0, 1.0, 1.0});

  test_matrix_all((double[]){2.0 * M_PI, 2.0 * M_PI, 2.0 * M_PI, 1.0, 1.0, 1.0,
                             2.0, 2.0, 2.0},
                  (double[]){3.0, 3.0, 3.0, 1.0});

  test_matrix_all((double[]){M_PI, M_PI, M_PI, -2.0, -2.0, -2.0, 2.0, 2.0, 2.0},
                  (double[]){0.0, 0.0, 0.0, 1.0});
}

END_TEST
START_TEST(test_parser) {
  print_test("#TEST15: parser test;");
  stack_v *head_v = NULL;
  stack_i *head_f = NULL;
  FILE *f = is_file_exist("obj/parsertest.obj");
  double max = 0;
  if (f != NULL) {
    read_file(f, &head_v, &head_f, &max);
    fclose(f);
  }
  stack_matrix_mult(&head_v, matrix_get_all(0, 0, 0, 0, 0, 0, 1, 1, 1));
  printf("v=%d\n", stack_get_count(head_v));
  stack_output(head_v);
  printf("f=%d\n", stack_i_get_count(head_f));
  stack_i_output(head_f);
  stack_i_multiset(head_f, head_v);
  stack_destroy(&head_v);
  stack_i_destroy(&head_f);
}

int test_rdontos() {
  Suite *s = suite_create("All Part");
  TCase *tc = tcase_create("Test1");
  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_create_matrix);
  tcase_add_test(tc, test_sum_sub);
  tcase_add_test(tc, test_mult_number);
  tcase_add_test(tc, test_mult_matrix);
  tcase_add_test(tc, test_transpose);
  tcase_add_test(tc, test_determinant);
  tcase_add_test(tc, test_calc_complements);
  tcase_add_test(tc, test_inverse_matrix);

  tcase_add_test(tc, test_get_rotation_x);
  tcase_add_test(tc, test_get_rotation_y);
  tcase_add_test(tc, test_get_rotation_z);
  tcase_add_test(tc, test_get_shift);
  tcase_add_test(tc, test_get_scale);
  tcase_add_test(tc, test_get_all);
  tcase_add_test(tc, test_parser);

  srunner_run_all(sr, CK_ENV);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf;
}

int main(void) {
  int nf = 0;
  nf += test_rdontos();
  return nf == 0 ? 0 : 1;
}

void print_test(char *name) { printf("%s:\n", name); }

void fill_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0) {
    double f = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = f;
        f++;
      }
    }
    A->matrix_type = CORRECT_MATRIX;
  }
}

double test_determ(double *f, int n) {
  matrix_t A = s21_create_matrix(n, n);
  matrix_fill_array(&A, f);
  double d = s21_determinant(&A);
  s21_remove_matrix(&A);
  return d;
}

void test_inverse_matr(double *arr, double *res, int n) {
  matrix_t A = s21_create_matrix(n, n);
  matrix_fill_array(&A, arr);
  matrix_t B = s21_inverse_matrix(&A);
  matrix_t A_res = s21_create_matrix(n, n);
  matrix_fill_array(&A_res, res);
  ck_assert_int_eq(s21_eq_matrix(&B, &A_res), SUCCESS);

  matrix_t C = s21_mult_matrix(&A, &B);
  ck_assert_int_eq(C.matrix_type, IDENTITY_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&A_res);
  s21_remove_matrix(&C);
}

void test_rotation(matrix_t (*f)(double)) {
  matrix_t A = f(0.0);
  matrix_t B = f(2.0 * M_PI);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  matrix_t v = s21_create_matrix(4, 1);
  double arr[] = {4.0, -5.0, 13.0, 1.0};
  matrix_fill_array(&v, arr);
  matrix_t C = f((2.0 * M_PI) / 15.0);
  for (int i = 0; i < 15; i++) {
    matrix_t t = s21_mult_matrix(&C, &v);
    s21_remove_matrix(&v);
    v = t;
  }
  matrix_t v_res = s21_create_matrix(4, 1);
  matrix_fill_array(&v_res, arr);
  ck_assert_int_eq(s21_eq_matrix(&v, &v_res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&v);
  s21_remove_matrix(&v_res);
}

void test_rotation_2(matrix_t (*f)(double), double arg, double *arr_res) {
  matrix_t A = f(arg);
  matrix_t v = s21_create_matrix(4, 1);
  double arr[] = {1.0, 1.0, 1.0, 1.0};
  matrix_fill_array(&v, arr);
  matrix_t t = s21_mult_matrix(&A, &v);
  matrix_t v_res = s21_create_matrix(4, 1);
  matrix_fill_array(&v_res, arr_res);
  ck_assert_int_eq(s21_eq_matrix(&t, &v_res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&v);
  s21_remove_matrix(&t);
  s21_remove_matrix(&v_res);
}

void test_shift_scale(matrix_t (*f)(double, double, double), double arg1,
                      double arg2, double arg3, double *arr_res) {
  matrix_t A = f(arg1, arg2, arg3);
  matrix_t v = s21_create_matrix(4, 1);
  double arr[] = {1.0, 1.0, 1.0, 1.0};
  matrix_fill_array(&v, arr);
  matrix_t t = s21_mult_matrix(&A, &v);
  matrix_t v_res = s21_create_matrix(4, 1);
  matrix_fill_array(&v_res, arr_res);
  // matrix_print(&t);
  ck_assert_int_eq(s21_eq_matrix(&t, &v_res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&v);
  s21_remove_matrix(&t);
  s21_remove_matrix(&v_res);
}

void test_matrix_all(double *arg, double *arr_res) {
  matrix_t A = matrix_get_all(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5],
                              arg[6], arg[7], arg[8]);
  matrix_t v = s21_create_matrix(4, 1);
  double arr[] = {1.0, 1.0, 1.0, 1.0};
  matrix_fill_array(&v, arr);
  matrix_t t = s21_mult_matrix(&A, &v);
  matrix_t v_res = s21_create_matrix(4, 1);
  matrix_fill_array(&v_res, arr_res);
  // matrix_print(&t);
  ck_assert_int_eq(s21_eq_matrix(&t, &v_res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&v);
  s21_remove_matrix(&t);
  s21_remove_matrix(&v_res);
}
