#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(EqMatrix, Test1NotEq) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 1);
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(EqMatrix, Test2Eq) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 100;
  matrix_a(0, 1) = 100;
  matrix_a(1, 0) = 100;
  matrix_a(1, 1) = 100;
  matrix_b(0, 0) = 100;
  matrix_b(0, 1) = 100;
  matrix_b(1, 0) = 100;
  matrix_b(1, 1) = 100;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, Test3Sucess) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = -100;
  matrix_a(0, 1) = -100;
  matrix_a(1, 0) = -100;
  matrix_a(1, 1) = -100;
  matrix_b(0, 0) = -100;
  matrix_b(0, 1) = -100;
  matrix_b(1, 0) = -100;
  matrix_b(1, 1) = -100;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(SumMatrix, Test1Throw) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  ASSERT_ANY_THROW(matrix_a.SumMatrix(matrix_b));
}

TEST(SumMatrix, Test2Success) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix res(2, 2);

  matrix_a(0, 0) = -69.420;
  matrix_a(0, 1) = 15;
  matrix_a(1, 0) = 25.005;
  matrix_a(1, 1) = 13;

  matrix_b(0, 0) = 69.420;
  matrix_b(0, 1) = 15.5;
  matrix_b(1, 0) = 100;
  matrix_b(1, 1) = -1000.01;

  res(0, 0) = 0;
  res(0, 1) = 30.5;
  res(1, 0) = 125.005;
  res(1, 1) = -987.01;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == res);
}

TEST(SubMatrix, Test1Throw) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  ASSERT_ANY_THROW(matrix_a.SubMatrix(matrix_b));
}

TEST(SubMatrix, Test2Success) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix res(2, 2);

  matrix_a(0, 0) = -69.420;
  matrix_a(0, 1) = 15;
  matrix_a(1, 0) = 25.005;
  matrix_a(1, 1) = 13;

  matrix_b(0, 0) = 69.420;
  matrix_b(0, 1) = 15.5;
  matrix_b(1, 0) = 100;
  matrix_b(1, 1) = -1000.01;

  res(0, 0) = -138.84;
  res(0, 1) = -0.5;
  res(1, 0) = -74.995;
  res(1, 1) = 1013.01;
  matrix_a.SubMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == res);
}

TEST(MulNumber, Test1Success) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -69.420;
  matrix_a(0, 1) = 15;
  matrix_a(1, 0) = 25.005;
  matrix_a(1, 1) = 13;

  result(0, 0) = -347.1;
  result(0, 1) = 75;
  result(1, 0) = 125.025;
  result(1, 1) = 65;

  matrix_a.MulNumber(5);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, Test1Throw) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  ASSERT_ANY_THROW(matrix_a.MulMatrix(matrix_b));
}

TEST(MulMatrix, Test2Success) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -69.420;
  matrix_a(0, 1) = 15;
  matrix_a(1, 0) = 25.005;
  matrix_a(1, 1) = 13;

  matrix_b(0, 0) = 69.420;
  matrix_b(0, 1) = 15.5;
  matrix_b(1, 0) = 100;
  matrix_b(1, 1) = -1000.01;

  result(0, 0) = -3319.1364;
  result(0, 1) = -16076.16;
  result(1, 0) = 3035.8471;
  result(1, 1) = -12612.5525;

  matrix_a.MulMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(Transpose, Test1Success) {
  S21Matrix matrix_a(3, 2);
  S21Matrix result(2, 3);

  matrix_a(0, 0) = 1.0001;
  matrix_a(0, 1) = -4;
  matrix_a(1, 0) = 2.99;
  matrix_a(1, 1) = 5;
  matrix_a(2, 0) = 300;
  matrix_a(2, 1) = 69.420;

  result(0, 0) = 1.0001;
  result(0, 1) = 2.99;
  result(0, 2) = 300;
  result(1, 0) = -4;
  result(1, 1) = 5;
  result(1, 2) = 69.420;
  S21Matrix res = matrix_a.Transpose();
  ASSERT_TRUE(res == result);
}

TEST(Determinant, Test1Throw) {
  S21Matrix matrix_a(3, 2);

  ASSERT_ANY_THROW(matrix_a.Determinant());
}

TEST(Determinant, Test2Zero) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 0;
  matrix_a(0, 1) = 100;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 200;

  ASSERT_TRUE(std::fabs(matrix_a.Determinant()) < s21_ACCURACY);
}

TEST(Determinant, Test3Zero) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 0;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = 100;
  matrix_a(1, 1) = 200;

  ASSERT_TRUE(std::fabs(matrix_a.Determinant()) < s21_ACCURACY);
}

TEST(Determinant, Test4Success) {
  S21Matrix matrix_a(1, 1);
  matrix_a(0, 0) = -123.456789;

  ASSERT_TRUE(matrix_a.Determinant() == -123.456789);
}

TEST(Determinant, Test5Success) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = -100;
  matrix_a(0, 1) = 69;
  matrix_a(1, 0) = 420.69;
  matrix_a(1, 1) = 15;
  std::cout << "\n" << matrix_a.Determinant() << '\n';
  ASSERT_TRUE(matrix_a.Determinant() == -30527.61);
}

TEST(Determinant, Test6Success) {
  S21Matrix matrix_a(4, 4);
  matrix_a(0, 0) = -100;
  matrix_a(0, 1) = 69;
  matrix_a(0, 2) = 420.69;
  matrix_a(0, 3) = 1337;
  matrix_a(1, 0) = 1;
  matrix_a(1, 1) = 2;
  matrix_a(1, 2) = 3;
  matrix_a(1, 3) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 69;
  matrix_a(2, 2) = 7;
  matrix_a(2, 3) = 8;
  matrix_a(3, 0) = 9;
  matrix_a(3, 1) = 10;
  matrix_a(3, 2) = 11;
  matrix_a(3, 3) = 12;

  std::cout << "\n" << matrix_a.Determinant() << '\n';
  ASSERT_TRUE(matrix_a.Determinant() == 661212.72);
}

TEST(CalcComplements, Test1Throw) {
  S21Matrix matrix_a(3, 2);

  ASSERT_ANY_THROW(matrix_a.CalcComplements());
}

TEST(CalcComplements, Test2Success) {
  S21Matrix matrix_a(2, 2);
  S21Matrix res(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 3;
  matrix_a(1, 1) = 4;

  res(0, 0) = 4;
  res(0, 1) = -3;
  res(1, 0) = -2;
  res(1, 1) = 1;

  ASSERT_TRUE(matrix_a.CalcComplements() == res);
}

TEST(CalcComplements, Test3Success) {
  S21Matrix matrix_a(3, 3);
  S21Matrix res(3, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 69.42;

  res(0, 0) = 273.68;
  res(0, 1) = 10;
  res(0, 2) = -20;
  res(1, 0) = -132.84;
  res(1, 1) = 54.42;
  res(1, 2) = 8;
  res(2, 0) = -8;
  res(2, 1) = -2;
  res(2, 2) = 4;

  ASSERT_TRUE(matrix_a.CalcComplements() == res);
}

TEST(Inverse, Test1Throw) {
  S21Matrix matrix_a(4, 4);

  matrix_a(0, 0) = -100;
  matrix_a(0, 1) = 0;
  matrix_a(0, 2) = 420.69;
  matrix_a(0, 3) = 1337;
  matrix_a(1, 0) = 1;
  matrix_a(1, 1) = 0;
  matrix_a(1, 2) = 3;
  matrix_a(1, 3) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 0;
  matrix_a(2, 2) = 7;
  matrix_a(2, 3) = 8;
  matrix_a(3, 0) = 9;
  matrix_a(3, 1) = 0;
  matrix_a(3, 2) = 11;
  matrix_a(3, 3) = 12;
  ASSERT_ANY_THROW(matrix_a.InverseMatrix());
}

TEST(Inverse, Test2Throw) {
  S21Matrix matrix_a(4, 3);

  ASSERT_ANY_THROW(matrix_a.InverseMatrix());
}

TEST(Inverse, Test3Success) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));

  S21Matrix matrix_c(1, 1);
  S21Matrix matrix_c_res(1, 1);
  matrix_c_res(0, 0) = 1;
  matrix_c(0, 0) = 1;
  ASSERT_TRUE(matrix_c.InverseMatrix().EqMatrix(matrix_c_res));
}

TEST(OperatorParentheses, True) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_EQ(matrix_a(0, 1), 2);
  const S21Matrix matrix_b(2, 2);
  ASSERT_EQ(matrix_b(0, 0), 0);
  ASSERT_ANY_THROW(matrix_b(15, 15));
}
TEST(OperatorParentheses, False) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_NE(matrix_a(0, 1), 10);
}
// TEST(OperatorShavronnes, True) {
//   S21Matrix matrix_a(2, 2);
//   std::stringstream input_date;
//   input_date << "2 2 3 3";
//   input_date >> matrix_a;
//   std::cout << matrix_a;
// }
TEST(OperatorPlus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a + matrix_b) == result);
}
TEST(OperatorMinus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a - matrix_b) == result);
}
TEST(OperatorMultiplyMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a * matrix_b) == result);
}

TEST(OperatorBrac, True) {
  S21Matrix matrix_a(2, 2);
  ASSERT_ANY_THROW(matrix_a(-1, -1));
  ASSERT_ANY_THROW(matrix_a(10, 10));
}

TEST(OperatorMultiplyNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
  ASSERT_TRUE((10 * matrix_a) == result);
}
TEST(OperatorMultiplyNum, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
}
TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(1, 3);
  matrix_a = matrix_b;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a += matrix_b;
  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorSumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  ASSERT_ANY_THROW(matrix_a += matrix_b);
}

TEST(OperatorSubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  matrix_a -= matrix_b;
  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorSubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  ASSERT_ANY_THROW(matrix_a -= matrix_b);
}
TEST(OperatorMulNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a *= 10) == result);
}
TEST(OperatorMulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  matrix_a *= matrix_b;
  ASSERT_TRUE(matrix_a == result);
}
TEST(OperatorMulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  ASSERT_ANY_THROW(matrix_a *= matrix_b);
}

TEST(Constructorsrest, True) {
  ASSERT_ANY_THROW(S21Matrix matrix_a(0, 5));
  S21Matrix matrix_b;
  matrix_b = matrix_b;
}

TEST(Get, True) {
  S21Matrix matrix_a(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  ASSERT_EQ(matrix_a.GetRows(), 3);
  ASSERT_EQ(matrix_a.GetCols(), 3);
}
TEST(Set, True) {
  S21Matrix check;
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);
  S21Matrix result_c(4, 4);
  S21Matrix matrix_c(1, 1);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 2;
  result(0, 1) = 5;

  result(1, 0) = 6;
  result(1, 1) = 3;

  result(2, 0) = 5;
  result(2, 1) = -2;
  matrix_a.EditCols(2);
//   std::cout << "matrix" << matrix_a << std::endl;
//   std::cout << "res" << result << std::endl;
  ASSERT_TRUE(matrix_a == result);
  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);

  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;
  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;
  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;

  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;
  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;

  matrix_b.EditRows(2);
//   std::cout << "matrix" << matrix_b << std::endl;
//   std::cout << "res" << result_b << std::endl;
  ASSERT_TRUE(matrix_b == result_b);

  matrix_c.EditCols(4);
  matrix_c.EditRows(4);
  ASSERT_TRUE(matrix_c == result_c);

  ASSERT_ANY_THROW(matrix_c.EditRows(-5));

  ASSERT_ANY_THROW(matrix_c.EditCols(0));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}