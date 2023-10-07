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

void S21Matrix::SumMatrix(const S21Matrix &other) {}