#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) {
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[cols_];
  }
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < this->rows_) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
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
  this->matrix_ = new double *[other.rows_];
  for (int i = 0; i < other.rows_; ++i) {
    this->matrix_[i] = new double[other.cols_];
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {}