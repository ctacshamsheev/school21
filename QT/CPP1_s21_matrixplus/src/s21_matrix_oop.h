#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <iostream>
#include <stdexcept>

#define EPS 1e-8  // точность сравнения метода eq_matrix

// сообщения исключений

/* out_of_range: исключение, которое возникает при попытке доступа к элементам
 * вне допустимого диапазона */
#define EXCP_INDX "Incorrect input, index is out of range"
/* invalid_argument: исключение, которое возникает при передаче в функцию
 * некорректного аргумента */
#define EXCP_EQ "Incorrect input, different dimensions of matrices."
#define EXCP_MUL "Invalid input, the number of columns is not equal of rows"
#define EXCP_SQ "Incorrect input, matrix is not square."
#define EXCP_DET "Incorrect input, matrix determinant is zero."

class S21Matrix {
 private:                  // атрибуты класса
  int _rows{0};            // число строк
  int _cols{0};            // число столбцов
  double** _matrix{NULL};  // указатель на двумерный массив элементов матрицы

 public:  // публичные методы класса
  /* конструкторы и деструкторы */
  explicit S21Matrix(
      int rows = 3);  // конструктор квадратной матрицы, без параметров
                      // S21Matrix() сгерерирует квадратную матрицу 3х3
  S21Matrix(int rows, int cols);  //  Параметризированный конструктор с
                                  //  количеством строк и столбцов
  S21Matrix(const S21Matrix& other);  //  Конструктор копирования
  S21Matrix(S21Matrix&& other);  // Конструктор переноса
  ~S21Matrix();                  // Деструктор

  /* accessor и mutator */
  void set_rows(int _rows);  // установка количества строк
  void set_cols(int _cols);  // установка количества столбцов
  void set_matrix(const double* arr);  // заполнение матрицы
  void set_matrix(int row, int col, double f);
  int get_rows();
  int get_cols();
  double** get_matrix();
  double get_matrix(int row, int col);

  /* операций над матрицами */
  bool eq_matrix(
      const S21Matrix& other);  // Проверяет матрицы на равенство между собой
  void sum_matrix(
      const S21Matrix& other);  // Прибавляет вторую матрицы к текущей
  void sub_matrix(
      const S21Matrix& other);  // Вычитает из текущей матрицы другую
  void mul_number(const double num);  // Умножает текущую матрицу на число
  void mul_matrix(
      const S21Matrix& other);  //  Умножает текущую матрицу на вторую
  S21Matrix transpose();  //  Создает новую транспонированную матрицу из текущей
                          //  и возвращает ее
  S21Matrix calc_complements();  // Вычисляет матрицу алгебраических дополнений
                                 // текущей матрицы и возвращает ее
  double determinant();  // Вычисляет и возвращает определитель текущей матрицы
  S21Matrix inverse_matrix();  // Вычисляет и возвращает обратную матрицу

  /* перегрузка операторов.*/
  S21Matrix operator+(const S21Matrix& other);  // Сложение двух матриц
  S21Matrix operator-(
      const S21Matrix& other);  // Вычитание одной матрицы из другой
  S21Matrix operator*(const S21Matrix& other);  //  Умножение матриц
  S21Matrix operator*(const double other);  // Умножение матрицы на число
  bool operator==(
      const S21Matrix& other);  // Проверка на равенство матриц (eq_matrix)
  S21Matrix& operator=(
      const S21Matrix& other);  // Присвоение матрице значений другой матрицы

  S21Matrix& operator+=(
      const S21Matrix& other);  // Присвоение сложения (sum_matrix)
  S21Matrix& operator-=(
      const S21Matrix& right);  // Присвоение разности (sub_matrix)
  S21Matrix& operator*=(
      const S21Matrix& right);  // Присвоение умножения (mul_matrix)
  S21Matrix& operator*=(
      const double& right);  // Присвоение умножения (mul_number)

  double& operator()(
      int row, int col);  // Индексация по элементам матрицы (строка, колонка)

  // friend S21Matrix operator*(const double left, S21Matrix& right);
  // Присвоение умножения (mul_number) double * S21Matrix

  friend std::ostream& operator<<(
      std::ostream& out,
      const S21Matrix& matrix);  // функция вывода матрицы

 private:  // приватные методы класса
  /* проверка на корректность */
  bool is_correct_eq(const S21Matrix& other);  // проверка на равные размеры
  bool is_correct_mul(const S21Matrix& other);  // проверка на соответствие для
                                                // матричного умножения
  bool is_correct_square();  // проверка на квадратную матрицу
  bool is_correct_index(int row, int col);  // проверка индекса

  /* функции работы с памятью */
  void create_matrix(int rows, int cols);  // выделение памяти
  void remove_matrix();                    // очистка памяти
  void resize_matrix(int rows, int cols);  // изменение размера

  /* операций над матрицами */
  S21Matrix get_minor(const S21Matrix& other, int n, int m);  // поиск минора
};

#endif  // SRC_S21_MATRIX_OOP_H_
