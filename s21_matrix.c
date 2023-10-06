#include "s21_matrix.h"

#include <math.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;

  if (!result) return ERROR_INCORRECT_MATRIX;

  if (rows <= 0 || columns <= 0) res = 1;

  if (!res) {
    result->matrix = NULL;
    result->rows = rows;
    result->columns = columns;
  }

  if (!res) {
    if ((result->matrix = calloc(rows, sizeof(double *))) == NULL) {
      res = 1;
    } else {
      for (int i = 0; i < rows; ++i) {
        if ((result->matrix[i] = calloc(columns, sizeof(double))) == NULL) {
          res = 1;
          result->rows = i;
          s21_remove_matrix(result);
        }
      }
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; ++i) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!is_matrix_valid(A) || !is_matrix_valid(B)) return FAILURE;
  if (A->rows != B->rows || A->columns != B->columns) return FAILURE;

  int is_equal = SUCCESS;

  if (is_equal) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > ACCURACY)
          is_equal = FAILURE;
      }
    }
  }
  return is_equal;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!is_matrix_valid(A) || !is_matrix_valid(B) || result == NULL)
    return ERROR_INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALCUALTION_ERROR;

  int res = OK;

  if (s21_create_matrix(A->rows, A->columns, result))
    res = ERROR_INCORRECT_MATRIX;

  if (!res) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!is_matrix_valid(A) || !is_matrix_valid(B) || result == NULL)
    return ERROR_INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALCUALTION_ERROR;

  int res = OK;

  if (s21_create_matrix(A->rows, A->columns, result))
    res = ERROR_INCORRECT_MATRIX;

  if (!res) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!is_matrix_valid(A) || result == NULL) return ERROR_INCORRECT_MATRIX;

  int res = OK;

  if (s21_create_matrix(A->rows, A->columns, result))
    res = ERROR_INCORRECT_MATRIX;

  if (!res) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!is_matrix_valid(A) || !is_matrix_valid(B) || result == NULL)
    return ERROR_INCORRECT_MATRIX;
  if (A->columns != B->rows) return CALCUALTION_ERROR;

  int res = OK;

  if (s21_create_matrix(A->rows, B->columns, result))
    res = ERROR_INCORRECT_MATRIX;

  if (!res) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < B->columns; ++j) {
        for (int k = 0; k < B->rows; ++k) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!is_matrix_valid(A) || result == NULL) return ERROR_INCORRECT_MATRIX;

  int res = OK;

  if (s21_create_matrix(A->columns, A->rows, result))
    res = ERROR_INCORRECT_MATRIX;

  if (!res) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  if (!is_matrix_valid(A) || result == NULL) return ERROR_INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCUALTION_ERROR;

  matrix_t temp = {0};
  if (s21_create_matrix(A->rows, A->columns, &temp))
    return ERROR_INCORRECT_MATRIX;
  copy_matrix(A, &temp);

  *result = 1.0;
  int swaps = 0, is_column_zero = 0;

  for (int i = 0; i < temp.rows - 1; ++i) {
    if (fabs(temp.matrix[i][i]) < ACCURACY) {
      int j = i + 1;
      for (; j < temp.rows && fabs(temp.matrix[j][i]) < ACCURACY; ++j)
        ;
      if (j == temp.rows) {
        *result = 0.0;
        is_column_zero = 1;
        break;
      }
      swaps++;
      swap_rows(&temp, i, j);
    }

    for (int j = i + 1; j < temp.rows; ++j) {
      double div = temp.matrix[j][i] / temp.matrix[i][i];
      for (int k = 0; k < temp.rows; ++k) {
        temp.matrix[j][k] -= div * temp.matrix[i][k];
      }
    }
  }

  if (!is_column_zero) {
    for (int i = 0; i < temp.rows; ++i) {
      *result *= temp.matrix[i][i];
    }
    if (swaps % 2 != 0) *result *= -1.0;
  }

  s21_remove_matrix(&temp);
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!is_matrix_valid(A) || result == NULL) return ERROR_INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCUALTION_ERROR;

  int res = OK;

  matrix_t minor = {0};
  if (s21_create_matrix(A->rows, A->columns, result) ||
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor))
    res = ERROR_INCORRECT_MATRIX;

  double minor_res = 0;
  if (!res) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->rows; ++j) {
        create_minor(&minor, A, i, j);
        s21_determinant(&minor, &minor_res);
        result->matrix[i][j] = minor_res * pow(-1, i + j);
      }
    }
  }
  s21_remove_matrix(&minor);
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!is_matrix_valid(A) || result == NULL) return ERROR_INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCUALTION_ERROR;

  int res = OK;

  matrix_t temp = {0}, Acpy = {0};

  if (!res) {
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det) < ACCURACY) {
      res = CALCUALTION_ERROR;
    }

    if (!res) {
      s21_calc_complements(A, &Acpy);
      s21_transpose(&Acpy, &temp);
      s21_mult_number(&temp, 1.0 / det, result);
    }
  }
  s21_remove_matrix(&temp);
  s21_remove_matrix(&Acpy);
  return res;
}

void copy_matrix(matrix_t *A, matrix_t *temp) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      temp->matrix[i][j] = A->matrix[i][j];
    }
  }
}

void create_minor(matrix_t *minor, matrix_t *A, int i, int j) {
  int minorx = 0, minory;
  for (int x = 0; x < A->rows; ++x) {
    minory = 0;
    for (int y = 0; y < A->rows; ++y) {
      if (x != i && y != j) {
        minor->matrix[minorx][minory] = A->matrix[x][y];
        ++minory;
      }
    }
    if (x != i) ++minorx;
  }
}

void swap_rows(matrix_t *A, int i, int j) {
  for (int k = 0; k < A->rows; ++k) {
    double temp = A->matrix[i][k];
    A->matrix[i][k] = A->matrix[j][k];
    A->matrix[j][k] = temp;
  }
}

int is_matrix_valid(matrix_t *A) {
  return (A && A->rows > 0 && A->columns > 0);
}
