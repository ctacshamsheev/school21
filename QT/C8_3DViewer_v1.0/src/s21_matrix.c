#include "s21_matrix.h"

// служебные функции
int is_correct(matrix_t* A, matrix_t* B);  // проверка совпадения размерности
int is_correct_one(matrix_t* A);  // проверка на корректность
matrix_t get_minor(matrix_t* A, int n, int m);  // генерация матрицы минора
int get_type(matrix_t* A);  // проверка типа матрицы

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t result;
  result.columns = columns;
  result.rows = rows;
  if (rows > 0 && columns > 0) {
    result.matrix = (double**)calloc(rows, sizeof(double*));
    for (int i = 0; i < result.rows; i++) {
      result.matrix[i] = (double*)calloc(result.columns, sizeof(double));
    }
    result.matrix_type = ZERO_MATRIX;
  } else {
    result.matrix_type = INCORRECT_MATRIX;
    result.columns = 0;
    result.rows = 0;
    result.matrix = NULL;
  }
  return result;
}

void s21_remove_matrix(matrix_t* A) {
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
      A->columns = 0;
      A->rows = 0;
      A->matrix_type = INCORRECT_MATRIX;
    }
  }
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int result = FAILURE;
  if (is_correct(A, B) == SUCCESS) {
    result = SUCCESS;
    for (int i = 0; i < A->rows && result == SUCCESS; i++) {
      for (int j = 0; j < A->columns && result == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

matrix_t s21_sum_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (is_correct(A, B) == SUCCESS) {
    result = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_sub_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (is_correct(A, B) == SUCCESS) {
    result = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_mult_number(matrix_t* A, double number) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS) {
    result = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && is_correct_one(B) == SUCCESS &&
      A->columns == B->rows) {
    result = s21_create_matrix(A->rows, B->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_transpose(matrix_t* A) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS) {
    result = s21_create_matrix(A->columns, A->rows);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[j][i];
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

double s21_determinant(matrix_t* A) {
  double result = 0.0;
  if (is_correct_one(A) == SUCCESS && A->columns == A->rows) {
    if (A->columns == 1) {
      result = A->matrix[0][0];
    } else {
      for (int i = 0; i < A->columns; i++) {
        matrix_t t = get_minor(A, 0, i);
        int z = (i % 2) == 0 ? 1 : -1;
        result += z * A->matrix[0][i] * s21_determinant(&t);
        s21_remove_matrix(&t);
      }
    }
  } else {
    result = NAN;
  }
  return result;
}

matrix_t s21_calc_complements(matrix_t* A) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && A->columns == A->rows) {
    result = s21_create_matrix(A->columns, A->rows);
    if (A->columns == 1) {
      result.matrix[0][0] = 1;
    } else {
      for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.columns; j++) {
          matrix_t t = get_minor(A, i, j);
          int z = ((i + j) % 2) == 0 ? 1 : -1;
          result.matrix[i][j] = z * s21_determinant(&t);
          s21_remove_matrix(&t);
        }
      }
      result.matrix_type = get_type(&result);
    }
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_inverse_matrix(matrix_t* A) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && A->columns == A->rows) {
    double det = s21_determinant(A);
    if (det != 0) {
      matrix_t B = s21_calc_complements(A);
      matrix_t C = s21_transpose(&B);
      result = s21_mult_number(&C, (1.0 / det));
      s21_remove_matrix(&B);
      s21_remove_matrix(&C);
    } else {
      result = s21_create_matrix(0, 0);
    }
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

int get_type(matrix_t* A) {
  int result = INCORRECT_MATRIX;
  if (is_correct_one(A)) {
    if (A->columns == 1 && A->rows != 1) {
      result = VECTOR_MATRIX;
    } else {
      int is_zero_diagonal = 1;
      int is_zero = 1;
      int is_idenity = 1;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (i == j) {
            if (fabs(A->matrix[i][j] - 1.0) > EPS) is_idenity = 0;
            if (fabs(A->matrix[i][j]) > EPS) is_zero_diagonal = 0;
          } else {
            if (fabs(A->matrix[i][j]) > EPS) is_zero = 0;
          }
        }
      }
      if (is_zero && is_zero_diagonal)
        result = ZERO_MATRIX;
      else if (is_zero && is_idenity)
        result = IDENTITY_MATRIX;
      else
        result = CORRECT_MATRIX;
    }
  }
  return result;
}

int is_correct(matrix_t* A, matrix_t* B) {
  int result = FAILURE;
  if (A != NULL && B != NULL) {
    if ((A->rows > 0 && A->columns > 0 && A->matrix_type != INCORRECT_MATRIX) &&
        (B->rows > 0 && B->columns > 0 && B->matrix_type != INCORRECT_MATRIX) &&
        (A->rows == B->rows && A->columns == B->columns)) {
      result = SUCCESS;
    }
  }
  return result;
}

int is_correct_one(matrix_t* A) {
  int result = FAILURE;
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0 && A->matrix_type != INCORRECT_MATRIX) {
      result = SUCCESS;
    }
  }
  return result;
}

matrix_t get_minor(matrix_t* A, int n, int m) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && A->columns > 1 && A->rows > 1) {
    result = s21_create_matrix(A->rows - 1, A->columns - 1);
    for (int i = 0; i < result.rows; i++) {
      int ii = (i >= n) ? i + 1 : i;
      for (int j = 0; j < result.columns; j++) {
        int jj = (j >= m) ? j + 1 : j;
        result.matrix[i][j] = A->matrix[ii][jj];
      }
    }
    result.matrix_type = CORRECT_MATRIX;
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

void matrix_fill_array(matrix_t* A, const double* arr) {
  if (is_correct_one(A) == SUCCESS) {
    int it = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = arr[it];
        it++;
      }
    }
    A->matrix_type = get_type(A);
  }
}

void matrix_print(matrix_t* A) {
  if (is_correct_one(A) == SUCCESS) {
    if (A->matrix_type == VECTOR_MATRIX) {
      printf("[");
      for (int j = 0; j < A->rows; j++) {
        if (j != 0) printf(",\t");
        printf("%.2f", A->matrix[j][0]);
      }
      printf("]\n");
    } else {
      printf("\n");
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (j != 0) printf("\t");
          printf("%.2f", A->matrix[i][j]);
        }
        printf("\n");
      }
    }
  } else {
    fprintf(stderr, "matrix_print:[NULL]\n");
  }
}

matrix_t matrix_get_rotation_x(double a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[0][0] = result.matrix[3][3] = 1.0;
  result.matrix[1][1] = result.matrix[2][2] = cos(a);
  result.matrix[2][1] = sin(a);
  result.matrix[1][2] = -sin(a);
  result.matrix_type = CORRECT_MATRIX;
  return result;
}
matrix_t matrix_get_rotation_y(double a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[1][1] = result.matrix[3][3] = 1.0;
  result.matrix[2][2] = result.matrix[0][0] = cos(a);
  result.matrix[0][2] = sin(a);
  result.matrix[2][0] = -sin(a);
  result.matrix_type = CORRECT_MATRIX;
  return result;
}
matrix_t matrix_get_rotation_z(double a) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[2][2] = result.matrix[3][3] = 1.0;
  result.matrix[1][1] = result.matrix[0][0] = cos(a);
  result.matrix[1][0] = sin(a);
  result.matrix[0][1] = -sin(a);
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t matrix_get_rotation(double ax, double ay, double az) {
  matrix_t x = matrix_get_rotation_x(ax);
  matrix_t y = matrix_get_rotation_y(ay);
  matrix_t z = matrix_get_rotation_z(az);
  matrix_t xy = s21_mult_matrix(&x, &y);
  matrix_t result = s21_mult_matrix(&xy, &z);

  s21_remove_matrix(&x);
  s21_remove_matrix(&y);
  s21_remove_matrix(&z);
  s21_remove_matrix(&xy);

  return result;
}

matrix_t matrix_get_shift(double a, double b, double c) {
  matrix_t result = s21_create_matrix(4, 4);
  for (int i = 0; i < result.rows; i++) {
    result.matrix[i][i] = 1.0;
  }
  result.matrix[0][3] = a;
  result.matrix[1][3] = b;
  result.matrix[2][3] = c;
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t matrix_get_scaling(double a, double b, double c) {
  matrix_t result = s21_create_matrix(4, 4);
  result.matrix[0][0] = a;
  result.matrix[1][1] = b;
  result.matrix[2][2] = c;
  result.matrix[3][3] = 1.0;
  result.matrix_type = CORRECT_MATRIX;
  return result;
}

matrix_t matrix_get_all(double ax, double ay, double az, double da, double db,
                        double dc, double ka, double kb, double kc) {
  matrix_t rotation = matrix_get_rotation(ax, ay, az);
  matrix_t shift = matrix_get_shift(da, db, dc);
  matrix_t scaling = matrix_get_scaling(ka, kb, kc);

  matrix_t rs = s21_mult_matrix(&rotation, &shift);
  matrix_t result = s21_mult_matrix(&rs, &scaling);

  s21_remove_matrix(&rotation);
  s21_remove_matrix(&shift);
  s21_remove_matrix(&scaling);
  s21_remove_matrix(&rs);

  return result;
}
