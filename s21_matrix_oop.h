#ifndef S21_MATRIX_OOP  // this needs to be the full path to header file
#define S21_MATRIX_OPP

#include <cmath>
#include <iostream>
#include <stdexcept>

#define s21_ACCURACY 1e-7

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();   // Default constructor
  ~S21Matrix();  // Destructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix &operator*=(const S21Matrix &other) const;
  S21Matrix operator*(const double &x) const;
  S21Matrix &operator*=(const double &x) const;
  bool operator==(const S21Matrix &other) const;
  double &operator()(const int &i, const int &j) const;

  int GetRows() const;
  int GetCols() const;
  void EditRows(const int rows);
  void EditCols(const int cols);

  void CreateMinor(const S21Matrix &other, const int i, const int j);
};

#endif