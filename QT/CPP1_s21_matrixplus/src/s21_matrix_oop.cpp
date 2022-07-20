#include "s21_matrix_oop.h"

// публичные методы класса

/* конструкторы и деструкторы */

S21Matrix::S21Matrix(int rows) : S21Matrix(rows, rows) {}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range(EXCP_INDX);
  } else {
    create_matrix(rows, cols);
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other._rows, other._cols) {
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      this->_matrix[i][j] = other._matrix[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : _rows(other._rows), _cols(other._cols) {
  if (this->_matrix != NULL) {
    remove_matrix();
  }
  this->_matrix = other._matrix;
  other._matrix = NULL;
  other._rows = other._cols = 0;
}

S21Matrix::~S21Matrix() {
  if (this->_matrix != NULL) {
    remove_matrix();
  }
  _rows = 0;
  _cols = 0;
}

/* accessor и mutator */

void S21Matrix::set_rows(int _rows) { resize_matrix(_rows, this->_cols); }

void S21Matrix::set_cols(int _cols) { resize_matrix(this->_rows, _cols); }

int S21Matrix::get_rows() { return this->_rows; }

int S21Matrix::get_cols() { return this->_cols; }

double **S21Matrix::get_matrix() { return this->_matrix; }

double S21Matrix::get_matrix(int row, int col) {
  return this->operator()(row, col);
}

void S21Matrix::set_matrix(const double *arr) {
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      this->_matrix[i][j] = arr[i * this->_cols + j];
    }
  }
}

void S21Matrix::set_matrix(int row, int col, double f) {
  this->operator()(row, col) = f;
}

/* операций над матрицами */

bool S21Matrix::eq_matrix(const S21Matrix &other) {
  bool result = false;
  if (this->is_correct_eq(other) == true) {
    result = true;
    for (int i = 0; i < this->_rows && result; i++) {
      for (int j = 0; j < this->_cols && result; j++) {
        if (fabs(this->_matrix[i][j] - other._matrix[i][j]) > EPS) {
          result = false;
        }
      }
    }
  }
  return result;
}

void S21Matrix::sum_matrix(const S21Matrix &other) {
  if (this->is_correct_eq(other) != true) {
    throw std::invalid_argument(EXCP_EQ);
  }
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      this->_matrix[i][j] += other._matrix[i][j];
    }
  }
}

void S21Matrix::sub_matrix(const S21Matrix &other) {
  if (this->is_correct_eq(other) != true) {
    throw std::invalid_argument(EXCP_EQ);
  }
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      this->_matrix[i][j] -= other._matrix[i][j];
    }
  }
}

void S21Matrix::mul_number(const double num) {
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      this->_matrix[i][j] *= num;
    }
  }
}

void S21Matrix::mul_matrix(const S21Matrix &other) {
  if (this->is_correct_mul(other) != true) {
    throw std::invalid_argument(EXCP_MUL);
  }
  S21Matrix result(this->_rows, other._cols);
  for (int i = 0; i < result._rows; i++) {
    for (int j = 0; j < result._cols; j++) {
      result._matrix[i][j] = 0;
      for (int k = 0; k < this->_cols; k++) {
        result._matrix[i][j] += this->_matrix[i][k] * other._matrix[k][j];
      }
    }
  }
  // this->std::move(result);   TODO move?
  remove_matrix();
  this->_matrix = result._matrix;
  this->_rows = result._rows;
  this->_cols = result._cols;
  result._matrix = NULL;
}

S21Matrix S21Matrix::transpose() {
  S21Matrix result(this->_cols, this->_rows);
  for (int i = 0; i < result._rows; i++) {
    for (int j = 0; j < result._cols; j++) {
      result._matrix[i][j] = this->_matrix[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::calc_complements() {
  if (this->is_correct_square() != true) {
    throw std::invalid_argument(EXCP_SQ);
  }
  S21Matrix result(this->_rows, this->_rows);

  if (this->_cols == 1) {
    result._matrix[0][0] = 1;
  } else {
    for (int i = 0; i < result._rows; i++) {
      for (int j = 0; j < result._cols; j++) {
        S21Matrix t = get_minor(*this, i, j);
        int z = (((i + j) % 2) == 0 ? 1 : -1);

        result._matrix[i][j] = z * t.determinant();
      }
    }
  }
  return result;
}

double S21Matrix::determinant() {
  if (this->is_correct_square() != true) {
    throw std::invalid_argument(EXCP_SQ);
  }
  double result = 0.0;
  if (this->_cols == 1) {
    result = this->_matrix[0][0];
  } else {
    for (int i = 0; i < this->_cols; i++) {
      S21Matrix t = get_minor(*this, 0, i);
      int z = (((i % 2) == 0) ? 1 : -1);
      result += z * this->_matrix[0][i] * t.determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::inverse_matrix() {
  if (this->is_correct_square() != true) {
    throw std::invalid_argument(EXCP_SQ);
  }
  double det = this->determinant();
  if (det == 0) {
    throw std::invalid_argument(EXCP_DET);
  }
  S21Matrix calc = this->calc_complements();
  S21Matrix result = calc.transpose();
  result.mul_number(1.0 / det);
  return result;
}

/* перегрузка операторов.*/

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.sum_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.sub_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.mul_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double other) {
  S21Matrix result(*this);
  result.mul_number(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->eq_matrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->sum_matrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->sub_matrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->mul_matrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &other) {
  this->mul_number(other);
  return *this;
}

// S21Matrix operator*(const double left, S21Matrix &right) {
//   S21Matrix result(right);
//   result.mul_number(left);
//   return result;
// }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    if (this->_matrix != NULL) {
      remove_matrix();
    }
    this->_rows = other._rows;
    this->_cols = other._cols;
    create_matrix(this->_rows, this->_cols);
    for (int i = 0; i < this->_rows; i++) {
      for (int j = 0; j < this->_cols; j++) {
        this->_matrix[i][j] = other._matrix[i][j];
      }
    }
  }
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (is_correct_index(row, col) != true) {
    throw std::out_of_range(EXCP_INDX);
  }
  return this->_matrix[row][col];
}

std::ostream &operator<<(std::ostream &out, const S21Matrix &matrix) {
  out << "[" << matrix._rows << "," << matrix._cols << "]" << std::endl;
  for (int i = 0; i < matrix._rows; i++) {
    for (int j = 0; j < matrix._cols; j++) {
      if (j != 0) out << "\t";
      out << matrix._matrix[i][j];
    }
    out << std::endl;
  }
  return out;
}

// приватные методы класса

/* проверка на корректность */

bool S21Matrix::is_correct_eq(const S21Matrix &other) {
  bool result = false;
  if (this->_matrix != NULL && other._matrix != NULL) {
    if (this->_rows > 0 && this->_cols > 0 && other._rows > 0 &&
        other._cols > 0 && this->_rows == other._rows &&
        this->_cols == other._cols) {
      result = true;
    }
  }
  return result;
}

bool S21Matrix::is_correct_mul(const S21Matrix &other) {
  bool result = false;
  if (this->_matrix != NULL && other._matrix != NULL) {
    if (this->_rows > 0 && this->_cols > 0 && other._rows > 0 &&
        other._cols > 0 && this->_cols == other._rows) {
      result = true;
    }
  }
  return result;
}

bool S21Matrix::is_correct_square() {
  bool result = false;
  if (this->_matrix != NULL) {
    if (this->_rows > 0 && this->_cols > 0 && this->_rows == this->_cols) {
      result = true;
    }
  }
  return result;
}

bool S21Matrix::is_correct_index(int row, int col) {
  return (row < 0 || col < 0 || row >= this->_rows || col >= this->_cols)
             ? false
             : true;
}

/* операций над матрицами */

S21Matrix S21Matrix::get_minor(const S21Matrix &other, int n, int m) {
  S21Matrix result = S21Matrix(other._rows - 1);
  for (int i = 0; i < result._rows; i++) {
    int ii = (i >= n) ? i + 1 : i;
    for (int j = 0; j < result._cols; j++) {
      int jj = (j >= m) ? j + 1 : j;
      result._matrix[i][j] = other._matrix[ii][jj];
    }
  }
  return result;
}

/* функции работы с памятью */

void S21Matrix::create_matrix(int rows, int cols) {
  this->_rows = rows;
  this->_cols = cols;
  this->_matrix = new double *[this->_rows]();
  for (int i = 0; i < this->_rows; i++)
    this->_matrix[i] = new double[this->_cols]();
}

void S21Matrix::remove_matrix() {
  for (int i = 0; i < _rows; i++) delete[] this->_matrix[i];
  delete[] this->_matrix;
  this->_matrix = NULL;
}

void S21Matrix::resize_matrix(int rows, int cols) {
  if (rows != this->_rows || cols != this->_cols) {
    if (rows <= 0 || cols <= 0) {
      throw std::out_of_range(EXCP_INDX);
    }
    S21Matrix tmp = *this;
    remove_matrix();
    create_matrix(rows, cols);
    for (int i = 0; i < std::min(rows, tmp.get_rows()); i++) {
      for (int j = 0; j < std::min(cols, tmp.get_cols()); j++) {
        this->_matrix[i][j] = tmp._matrix[i][j];
      }
    }
  }
}
