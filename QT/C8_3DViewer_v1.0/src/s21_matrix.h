#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-8 // точность сравнения
#define SUCCESS 1 // матрицы совпадают
#define FAILURE 0 // матрицы не совпадают

// Тип матрицы
typedef enum
{
  CORRECT_MATRIX = 0,   // корректная матрица
  INCORRECT_MATRIX = 1, // при ошибках в действиях с матрицами
  IDENTITY_MATRIX = 2,  // единичная матрица
  ZERO_MATRIX = 3,      // нулевая матрица
  VECTOR_MATRIX = 4     // вектор
} matrix_type_t;

// Структура матрицы
typedef struct matrix_struct
{
  double **matrix;
  int rows;
  int columns;
  matrix_type_t matrix_type;
} matrix_t;

// функции из проекта C6_s21_matrix
matrix_t s21_create_matrix(int rows, int columns);    // Создание матриц [rows х columns]
void s21_remove_matrix(matrix_t *A);                  // Очистка матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);          // Сравнение матриц
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);    // Сложение матриц
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);    // вычитание матриц
matrix_t s21_mult_number(matrix_t *A, double number); // Умножение матрицы на число
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);   // Умножение матрицы на матрицу
matrix_t s21_transpose(matrix_t *A);                  // Транспонирование матрицы
matrix_t s21_calc_complements(matrix_t *A);           // Минор матрицы и матрица алгебраических дополнений
double s21_determinant(matrix_t *A);                  // Определитель матрицы
matrix_t s21_inverse_matrix(matrix_t *A);             // Обратная матрица

void matrix_fill_array(matrix_t *A, const double *arr); // заполнение матрицы из массива arr

// Генерация матриц, для аффинных преобразований (перемещение, поворот, масштабирование) для матриц размерности [4x4]
matrix_t matrix_get_rotation_x(double ax);                     // Вращение вокруг оси OX в трёхмерном пространстве, где aх - угол поворота
matrix_t matrix_get_rotation_y(double ay);                     // Вращение вокруг оси OY в трёхмерном пространстве, где ay - угол поворота
matrix_t matrix_get_rotation_z(double az);                     // Вращение вокруг оси OZ в трёхмерном пространстве, где az - угол поворота
matrix_t matrix_get_rotation(double ax, double ay, double az); // Вращение вокруг произвольной оси XYZ в трёхмерном пространстве

matrix_t matrix_get_shift(double a, double b, double c);   // Перемещение, где a, b и с - величины по x, y и z, на которые необходимо переместить исходную точку
matrix_t matrix_get_scaling(double a, double b, double c); // масштабирование, где  a, b и с - коэффициенты масштабирования соответственно по осям OX, OY и OZ.

matrix_t matrix_get_all(double rotation_x, double rotation_y, double rotation_z,
                        double shift_a, double shift_b, double shift_c,
                        double scaling_a, double scaling_b, double scaling_c); // композиция всех возможных преобразований

// функции вывода, используются только с консолью, не требуют тестов
void matrix_print(matrix_t *A); // вывод матрицы в консоль

#endif // SRC_S21_MATRIX_H_
