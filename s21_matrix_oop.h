#ifndef S21_MATRIX_OOP  // this needs to be the full path to header file
#define S21_MATRIX_OPP

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

#define s21_ACCURACY 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix operator*(const double &x) const noexcept;
  S21Matrix &operator*=(const double &x) noexcept;
  bool operator==(const S21Matrix &other) const;
  double &operator()(const int &i, const int &j);
  const double &operator()(const int &i, const int &j) const;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void EditRows(const int rows);
  void EditCols(const int cols);

  void CreateMinor(const S21Matrix &other, const int i, const int j);
};

#endif