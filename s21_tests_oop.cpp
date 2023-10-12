#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(ConstructorDefault, Test1Success) {
  S21Matrix matrix_A;
  S21Matrix res(3, 3);
  ASSERT_TRUE(matrix_A == res);
}

TEST(ConstructorCopy, Test1Success) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  S21Matrix res(matrix_A);
  ASSERT_TRUE(matrix_A == res);
}

TEST(ConstructorCopyInvalid, Test1Success) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;
  S21Matrix temp(std::move(matrix_A));
  S21Matrix res(matrix_A);
  ASSERT_ANY_THROW(matrix_A(0, 0));
}

TEST(ConstructorMove, Test1Success) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  S21Matrix matrix_B(2, 2);
  matrix_B(0, 0) = -69.420;
  matrix_B(0, 1) = 15;
  matrix_B(1, 0) = 25.005;
  matrix_B(1, 1) = 13;

  S21Matrix res(std::move(matrix_A));
  ASSERT_TRUE(matrix_B == res);
  ASSERT_TRUE(matrix_A.GetCols() == 0);
  ASSERT_TRUE(matrix_A.GetRows() == 0);
}

TEST(OperatorCopy, Test1Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);
  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  res = matrix_A;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorCopyInvalid, Test1Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);
  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;
  S21Matrix temp(std::move(matrix_A));
  res = matrix_A;
  ASSERT_ANY_THROW(matrix_A(0, 0));
}

TEST(OperatorMove, Test1Success) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  S21Matrix matrix_B(2, 2);
  matrix_B(0, 0) = -69.420;
  matrix_B(0, 1) = 15;
  matrix_B(1, 0) = 25.005;
  matrix_B(1, 1) = 13;

  S21Matrix res = std::move(matrix_A);
  ASSERT_TRUE(matrix_B == res);
  ASSERT_TRUE(matrix_A.GetCols() == 0);
  ASSERT_TRUE(matrix_A.GetRows() == 0);
}

TEST(EqMatrix, Test1NotEq) {
  S21Matrix matrix_A(1, 2);
  S21Matrix matrix_B(2, 1);
  ASSERT_FALSE(matrix_A.EqMatrix(matrix_B));
}

TEST(EqMatrix, Test2Eq) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  matrix_A(0, 0) = 100;
  matrix_A(0, 1) = 100;
  matrix_A(1, 0) = 100;
  matrix_A(1, 1) = 100;
  matrix_B(0, 0) = 100;
  matrix_B(0, 1) = 100;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = 100;
  ASSERT_TRUE(matrix_A.EqMatrix(matrix_B));
}

TEST(EqMatrix, Test3Eq) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  matrix_A(0, 0) = -100;
  matrix_A(0, 1) = -100;
  matrix_A(1, 0) = -100;
  matrix_A(1, 1) = -100;

  matrix_B(0, 0) = -100;
  matrix_B(0, 1) = -100;
  matrix_B(1, 0) = -100;
  matrix_B(1, 1) = -100;
  ASSERT_TRUE(matrix_A.EqMatrix(matrix_B));
}

TEST(EqMatrix, Test4NotEq) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  matrix_A(0, 0) = -100;
  matrix_A(0, 1) = -100;
  matrix_A(1, 0) = -100;
  matrix_A(1, 1) = -100;

  matrix_B(0, 0) = -100;
  matrix_B(0, 1) = -100;
  matrix_B(1, 0) = -100;
  matrix_B(1, 1) = 100;
  ASSERT_FALSE(matrix_A.EqMatrix(matrix_B));
}

TEST(SumMatrix, Test1Throw) {
  S21Matrix matrix_A(1, 2);
  S21Matrix matrix_B(2, 2);

  ASSERT_ANY_THROW(matrix_A.SumMatrix(matrix_B));
}

TEST(SumMatrix, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = 0;
  res(0, 1) = 30.5;
  res(1, 0) = 125.005;
  res(1, 1) = -987.01;
  matrix_A.SumMatrix(matrix_B);
  ASSERT_TRUE(matrix_A == res);
}

TEST(SubMatrix, Test1Throw) {
  S21Matrix matrix_A(1, 2);
  S21Matrix matrix_B(2, 2);

  ASSERT_ANY_THROW(matrix_A.SubMatrix(matrix_B));
}

TEST(SubMatrix, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = -138.84;
  res(0, 1) = -0.5;
  res(1, 0) = -74.995;
  res(1, 1) = 1013.01;
  matrix_A.SubMatrix(matrix_B);
  ASSERT_TRUE(matrix_A == res);
}

TEST(MulNumber, Test1Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  res(0, 0) = -347.1;
  res(0, 1) = 75;
  res(1, 0) = 125.025;
  res(1, 1) = 65;

  matrix_A.MulNumber(5);

  ASSERT_TRUE(matrix_A == res);
}

TEST(MulMatrix, Test1Throw) {
  S21Matrix matrix_A(2, 1);
  S21Matrix matrix_B(2, 2);

  ASSERT_ANY_THROW(matrix_A.MulMatrix(matrix_B));
}

TEST(MulMatrix, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = -3319.1364;
  res(0, 1) = -16076.16;
  res(1, 0) = 3035.8471;
  res(1, 1) = -12612.5525;

  matrix_A.MulMatrix(matrix_B);
  ASSERT_TRUE(matrix_A == res);
}

TEST(Transpose, Test1Success) {
  S21Matrix matrix_A(3, 2);
  S21Matrix res(2, 3);

  matrix_A(0, 0) = 1.0001;
  matrix_A(0, 1) = -4;
  matrix_A(1, 0) = 2.99;
  matrix_A(1, 1) = 5;
  matrix_A(2, 0) = 300;
  matrix_A(2, 1) = 69.420;

  res(0, 0) = 1.0001;
  res(0, 1) = 2.99;
  res(0, 2) = 300;
  res(1, 0) = -4;
  res(1, 1) = 5;
  res(1, 2) = 69.420;
  S21Matrix transposed = matrix_A.Transpose();
  ASSERT_TRUE(transposed == res);
}

TEST(Determinant, Test1Throw) {
  S21Matrix matrix_A(3, 2);

  ASSERT_ANY_THROW(matrix_A.Determinant());
}

TEST(Determinant, Test2Zero) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = 0;
  matrix_A(0, 1) = 100;
  matrix_A(1, 0) = 0;
  matrix_A(1, 1) = 200;

  ASSERT_TRUE(std::fabs(matrix_A.Determinant()) < s21_ACCURACY);
}

TEST(Determinant, Test3Zero) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = 0;
  matrix_A(0, 1) = 0;
  matrix_A(1, 0) = 100;
  matrix_A(1, 1) = 200;

  ASSERT_TRUE(std::fabs(matrix_A.Determinant()) < s21_ACCURACY);
}

TEST(Determinant, Test4Success) {
  S21Matrix matrix_A(1, 1);
  matrix_A(0, 0) = -123.456789;

  ASSERT_TRUE(matrix_A.Determinant() == -123.456789);
}

TEST(Determinant, Test5Success) {
  S21Matrix matrix_A(2, 2);
  matrix_A(0, 0) = -100;
  matrix_A(0, 1) = 69;
  matrix_A(1, 0) = 420.69;
  matrix_A(1, 1) = 15;
  ASSERT_TRUE(matrix_A.Determinant() == -30527.61);
}

TEST(Determinant, Test6Success) {
  S21Matrix matrix_A(4, 4);
  matrix_A(0, 0) = -100;
  matrix_A(0, 1) = 69;
  matrix_A(0, 2) = 420.69;
  matrix_A(0, 3) = 1337;
  matrix_A(1, 0) = 1;
  matrix_A(1, 1) = 2;
  matrix_A(1, 2) = 3;
  matrix_A(1, 3) = 4;
  matrix_A(2, 0) = 5;
  matrix_A(2, 1) = 69;
  matrix_A(2, 2) = 7;
  matrix_A(2, 3) = 8;
  matrix_A(3, 0) = 9;
  matrix_A(3, 1) = 10;
  matrix_A(3, 2) = 11;
  matrix_A(3, 3) = 12;

  ASSERT_TRUE(matrix_A.Determinant() == 661212.72);
}

TEST(CalcComplements, Test1Throw) {
  S21Matrix matrix_A(3, 2);

  ASSERT_ANY_THROW(matrix_A.CalcComplements());
}

TEST(CalcComplements, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(1, 0) = 3;
  matrix_A(1, 1) = 4;

  res(0, 0) = 4;
  res(0, 1) = -3;
  res(1, 0) = -2;
  res(1, 1) = 1;

  ASSERT_TRUE(matrix_A.CalcComplements() == res);
}

TEST(CalcComplements, Test3Success) {
  S21Matrix matrix_A(3, 3);
  S21Matrix res(3, 3);

  matrix_A(0, 0) = 1;
  matrix_A(0, 1) = 2;
  matrix_A(0, 2) = 3;
  matrix_A(1, 0) = 0;
  matrix_A(1, 1) = 4;
  matrix_A(1, 2) = 2;
  matrix_A(2, 0) = 5;
  matrix_A(2, 1) = 2;
  matrix_A(2, 2) = 69.42;

  res(0, 0) = 273.68;
  res(0, 1) = 10;
  res(0, 2) = -20;
  res(1, 0) = -132.84;
  res(1, 1) = 54.42;
  res(1, 2) = 8;
  res(2, 0) = -8;
  res(2, 1) = -2;
  res(2, 2) = 4;

  ASSERT_TRUE(matrix_A.CalcComplements() == res);
}

TEST(CalcComplements, Test4Success) {
  S21Matrix matrix_A(1, 1);
  S21Matrix res(1, 1);

  matrix_A(0, 0) = 1;
  res(0, 0) = 1;

  ASSERT_TRUE(matrix_A.CalcComplements() == res);
}

TEST(Inverse, Test1Throw) {
  S21Matrix matrix_A(4, 4);

  matrix_A(0, 0) = -100;
  matrix_A(0, 1) = 0;
  matrix_A(0, 2) = 420.69;
  matrix_A(0, 3) = 1337;
  matrix_A(1, 0) = 1;
  matrix_A(1, 1) = 0;
  matrix_A(1, 2) = 3;
  matrix_A(1, 3) = 4;
  matrix_A(2, 0) = 5;
  matrix_A(2, 1) = 0;
  matrix_A(2, 2) = 7;
  matrix_A(2, 3) = 8;
  matrix_A(3, 0) = 9;
  matrix_A(3, 1) = 0;
  matrix_A(3, 2) = 11;
  matrix_A(3, 3) = 12;
  ASSERT_ANY_THROW(matrix_A.InverseMatrix());
}

TEST(Inverse, Test2Throw) {
  S21Matrix matrix_A(4, 3);

  ASSERT_ANY_THROW(matrix_A.InverseMatrix());
}

TEST(Inverse, Test3Success) {
  S21Matrix matrix_A(3, 3);
  S21Matrix res(3, 3);

  matrix_A(0, 0) = 2;
  matrix_A(0, 1) = 5;
  matrix_A(0, 2) = 7;
  matrix_A(1, 0) = 6;
  matrix_A(1, 1) = 3;
  matrix_A(1, 2) = 4;
  matrix_A(2, 0) = 5;
  matrix_A(2, 1) = -2;
  matrix_A(2, 2) = -3;

  res(0, 0) = 1;
  res(0, 1) = -1;
  res(0, 2) = 1;
  res(1, 0) = -38;
  res(1, 1) = 41;
  res(1, 2) = -34;
  res(2, 0) = 27;
  res(2, 1) = -29;
  res(2, 2) = 24;

  ASSERT_TRUE(matrix_A.InverseMatrix().EqMatrix(res));
}

TEST(OperatorPlus, Test1Throw) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 1);

  ASSERT_ANY_THROW(matrix_A + matrix_B);
}

TEST(OperatorPlus, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = 0;
  res(0, 1) = 30.5;
  res(1, 0) = 125.005;
  res(1, 1) = -987.01;

  ASSERT_TRUE((matrix_A + matrix_B) == res);
}

TEST(OperatorAdditionAss, Test1Throw) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 1);

  ASSERT_ANY_THROW(matrix_A += matrix_B);
}

TEST(OperatorAdditionAss, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = 0;
  res(0, 1) = 30.5;
  res(1, 0) = 125.005;
  res(1, 1) = -987.01;

  matrix_A += matrix_B;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorMinus, Test1Throw) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 1);

  ASSERT_ANY_THROW(matrix_A - matrix_B);
}

TEST(OperatorMinus, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = -138.84;
  res(0, 1) = -0.5;
  res(1, 0) = -74.995;
  res(1, 1) = 1013.01;

  ASSERT_TRUE((matrix_A - matrix_B) == res);
}

TEST(OperatorDifferenceAss, Test1Throw) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 1);

  ASSERT_ANY_THROW(matrix_A -= matrix_B);
}

TEST(OperatorDifferenceAss, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = -138.84;
  res(0, 1) = -0.5;
  res(1, 0) = -74.995;
  res(1, 1) = 1013.01;

  matrix_A -= matrix_B;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorMulMatrix, Test1Throw) {
  S21Matrix matrix_A(2, 1);
  S21Matrix matrix_B(2, 2);

  ASSERT_ANY_THROW(matrix_A * matrix_B);
}

TEST(OperatorMulMatrix, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = -3319.1364;
  res(0, 1) = -16076.16;
  res(1, 0) = 3035.8471;
  res(1, 1) = -12612.5525;

  ASSERT_TRUE((matrix_A * matrix_B) == res);
}

TEST(OperatorMultMatrixAss, Test1Throw) {
  S21Matrix matrix_A(2, 1);
  S21Matrix matrix_B(2, 2);

  ASSERT_ANY_THROW(matrix_A *= matrix_B);
}

TEST(OperatorMulMatrixAss, Test2Success) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  matrix_B(0, 0) = 69.420;
  matrix_B(0, 1) = 15.5;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = -1000.01;

  res(0, 0) = -3319.1364;
  res(0, 1) = -16076.16;
  res(1, 0) = 3035.8471;
  res(1, 1) = -12612.5525;

  matrix_A *= matrix_B;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorMulNumber, Test1SuccessL) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  res(0, 0) = -347.1;
  res(0, 1) = 75;
  res(1, 0) = 125.025;
  res(1, 1) = 65;

  matrix_A = matrix_A * 5;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorMulNumber, Test2SuccessR) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  res(0, 0) = -347.1;
  res(0, 1) = 75;
  res(1, 0) = 125.025;
  res(1, 1) = 65;

  matrix_A = 5 * matrix_A;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorMulNumberAss, True) {
  S21Matrix matrix_A(2, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = -69.420;
  matrix_A(0, 1) = 15;
  matrix_A(1, 0) = 25.005;
  matrix_A(1, 1) = 13;

  res(0, 0) = -347.1;
  res(0, 1) = 75;
  res(1, 0) = 125.025;
  res(1, 1) = 65;

  matrix_A *= 5;
  ASSERT_TRUE(matrix_A == res);
}

TEST(OperatorEqMatrix, Test1NotEq) {
  S21Matrix matrix_A(1, 2);
  S21Matrix matrix_B(2, 1);
  ASSERT_FALSE(matrix_A == matrix_B);
}

TEST(OperatorEqMatrix, Test2Eq) {
  S21Matrix matrix_A(2, 2);
  S21Matrix matrix_B(2, 2);
  matrix_A(0, 0) = 100;
  matrix_A(0, 1) = 100;
  matrix_A(1, 0) = 100;
  matrix_A(1, 1) = 100;
  matrix_B(0, 0) = 100;
  matrix_B(0, 1) = 100;
  matrix_B(1, 0) = 100;
  matrix_B(1, 1) = 100;
  ASSERT_TRUE(matrix_A == matrix_B);
}

TEST(OperatorIndex, Test1Throw) {
  S21Matrix matrix_A(2, 2);
  ASSERT_ANY_THROW(matrix_A(-1, -1));
  ASSERT_ANY_THROW(matrix_A(69, 420));
  S21Matrix temp(std::move(matrix_A));
  ASSERT_ANY_THROW(matrix_A(0, 0));
}

TEST(OperatorIndex, Test2SuccessChange) {
  S21Matrix matrix_A(1, 1);
  ASSERT_TRUE(matrix_A(0, 0) == 0);
  matrix_A(0, 0) = 69.420;
  ASSERT_TRUE(matrix_A(0, 0) == 69.420);
}

TEST(OperatorIndex, Test3SuccessJustVal) {
  S21Matrix matrix_A(1, 1);
  matrix_A(0, 0) = 69.420;
  double test = matrix_A(0, 0);
  ASSERT_TRUE(test == 69.420);
}

TEST(Accessor, Test1Success) {
  S21Matrix matrix_A(3, 4);

  ASSERT_TRUE(matrix_A.GetRows() == 3);
  ASSERT_TRUE(matrix_A.GetCols() == 4);
}

TEST(Mutator, Test1Throw) {
  S21Matrix matrix_A(1, 1);

  ASSERT_ANY_THROW(matrix_A.EditRows(-1));
  ASSERT_ANY_THROW(matrix_A.EditRows(0));
  ASSERT_ANY_THROW(matrix_A.EditCols(-1));
  ASSERT_ANY_THROW(matrix_A.EditCols(0));
}

TEST(Mutator, Test2SuccessEditRowsShrink) {
  S21Matrix matrix_A(3, 2);
  S21Matrix res(2, 2);

  matrix_A(0, 0) = 1.0001;
  matrix_A(0, 1) = -4;
  matrix_A(1, 0) = 2.99;
  matrix_A(1, 1) = 5;
  matrix_A(2, 0) = 300;
  matrix_A(2, 1) = 69.420;

  res(0, 0) = 1.0001;
  res(0, 1) = -4;
  res(1, 0) = 2.99;
  res(1, 1) = 5;
  matrix_A.EditRows(2);
  ASSERT_TRUE(matrix_A == res);
}

TEST(Mutator, Test3SuccessEditColsShrink) {
  S21Matrix matrix_A(3, 2);
  S21Matrix res(3, 1);

  matrix_A(0, 0) = 1.0001;
  matrix_A(0, 1) = -4;
  matrix_A(1, 0) = 2.99;
  matrix_A(1, 1) = 5;
  matrix_A(2, 0) = 300;
  matrix_A(2, 1) = 69.420;

  res(0, 0) = 1.0001;
  res(1, 0) = 2.99;
  res(2, 0) = 300;
  matrix_A.EditCols(1);
  ASSERT_TRUE(matrix_A == res);
}

TEST(Mutator, Test4SuccessEditRowsGrow) {
  S21Matrix matrix_A(3, 2);
  S21Matrix res(4, 2);

  matrix_A(0, 0) = 1.0001;
  matrix_A(0, 1) = -4;
  matrix_A(1, 0) = 2.99;
  matrix_A(1, 1) = 5;
  matrix_A(2, 0) = 300;
  matrix_A(2, 1) = 69.420;

  res(0, 0) = 1.0001;
  res(0, 1) = -4;
  res(1, 0) = 2.99;
  res(1, 1) = 5;
  res(2, 0) = 300;
  res(2, 1) = 69.420;
  matrix_A.EditRows(4);
  ASSERT_TRUE(matrix_A == res);
}

TEST(Mutator, Test5SuccessEditColsGrow) {
  S21Matrix matrix_A(3, 2);
  S21Matrix res(3, 3);

  matrix_A(0, 0) = 1.0001;
  matrix_A(0, 1) = -4;
  matrix_A(1, 0) = 2.99;
  matrix_A(1, 1) = 5;
  matrix_A(2, 0) = 300;
  matrix_A(2, 1) = 69.420;

  res(0, 0) = 1.0001;
  res(0, 1) = -4;
  res(1, 0) = 2.99;
  res(1, 1) = 5;
  res(2, 0) = 300;
  res(2, 1) = 69.420;
  matrix_A.EditCols(3);
  ASSERT_TRUE(matrix_A == res);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}