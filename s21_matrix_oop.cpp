#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) {
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[cols_];
  }
}

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; ++i) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (this->rows_ < 1 || this->cols_ < 1) {
    throw std::invalid_argument("Invalid matrix dimensions");
  }
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (other.matrix_ == nullptr) {
    this->matrix_ = nullptr;
  } else {
    this->matrix_ = new double *[other.rows_];
    for (int i = 0; i < other.rows_; ++i) {
      this->matrix_[i] = new double[other.cols_];
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    for (int i = 0; i < this->rows_; ++i) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;

    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    if (other.matrix_ == nullptr) {
      this->matrix_ = nullptr;
    } else {
      this->matrix_ = new double *[this->rows_];
      for (int i = 0; i < this->rows_; ++i) {
        this->matrix_[i] = new double[this->cols_];
        for (int j = 0; j < this->cols_; ++j) {
          this->matrix_[i][j] = other.matrix_[i][j];
        }
      }
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    for (int i = 0; i < this->rows_; ++i) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;

    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;
  bool is_equal = true;

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j] > s21_ACCURACY)) {
        is_equal = false;
      }
    }
  }
  return is_equal;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimension");
  }

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimension");
  }

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrixes cannot be multiplied due to dimension differences");
  }

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        this->matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix transposed(this->cols_, this->rows_);

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      transposed.matrix_[j][i] = this->matrix_[i][j];
    }
  }

  return transposed;
}

double S21Matrix::Determinant() const {
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  double result = 1.0;
  int swaps = 0, is_column_zero = 0;
  S21Matrix temp(this->rows_, this->cols_);

  for (int i = 0; i < temp.rows_ - 1 && !is_column_zero; ++i) {
    if (std::fabs(temp.matrix_[i][i]) < s21_ACCURACY) {
      int j = i + 1;
      for (; j < temp.rows_ && std::fabs(temp.matrix_[j][i]) < s21_ACCURACY;
           ++j)
        ;
      if (j == temp.rows_) {
        result = 0;
        is_column_zero = 1;
      }
      ++swaps;
      std::swap(temp.matrix_[i], temp.matrix_[j]);
    }

    for (int j = i + 1; j < temp.rows_ && !is_column_zero; ++j) {
      double div = temp.matrix_[j][i] / temp.matrix_[i][i];
      for (int k = 0; k < temp.rows_; ++k) {
        temp.matrix_[j][k] -= div * temp.matrix_[i][k];
      }
    }
  }

  if (!is_column_zero) {
    for (int i = 0; i < temp.rows_; ++i) {
      result *= temp.matrix_[i][i];
    }
    if (swaps % 2 != 0) result *= -1;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  S21Matrix complements(this->rows_, this->cols_);
  S21Matrix minor(this->rows_ - 1, this->cols_ - 1);

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      minor.CreateMinor(*this, i, j);
      double minor_res = minor.Determinant();
      complements.matrix_[i][j] = minor_res * std::pow(-1, i + j);
    }
  }

  return complements;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (this->Determinant() == 0) {
    throw std::invalid_argument("Determinant is 0");
  }

  S21Matrix complements = this->CalcComplements();
  S21Matrix inverse = complements.Transpose();
  inverse.MulNumber(1.0 / this->Determinant());
  return inverse;
}

void S21Matrix::CreateMinor(const S21Matrix &other, const int i, const int j) {
  int minorx = 0;
  for (int x = 0; x < other.rows_; ++x) {
    int minory = 0;
    for (int y = 0; y < other.rows_; ++y) {
      if (x != i && y != j) {
        this->matrix_[minorx][minory] = other.matrix_[x][y];
        ++minory;
      }
    }
    if (x != i) ++minorx;
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double &x) const noexcept {
  S21Matrix res(*this);
  res.MulNumber(x);
  return res;
}

S21Matrix &S21Matrix::operator*=(const double &x) noexcept {
  this->MulNumber(x);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return this->EqMatrix(other);
}

double &S21Matrix::operator()(const int &i, const int &j) const {
  if (this->matrix_ == nullptr) {
    throw std::invalid_argument("invalid matrix");
  }
  if (i < 0 || i > this->rows_ || j < 0 || j > cols_) {
    throw std::invalid_argument("index is outside the matrix");
  }
  return this->matrix_[i][j];
}

int S21Matrix::GetRows() const noexcept { return this->rows_; }

int S21Matrix::GetCols() const noexcept { return this->cols_; }

void S21Matrix::EditRows(const int rows) {}

void S21Matrix::EditCols(const int cols) {}