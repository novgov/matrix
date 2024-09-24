#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!s21_is_empty(A) && !s21_is_empty(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      ret = s21_create_matrix(A->rows, A->columns, result);
      if (ret != OK) return ret;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      ret = INCORRECT_MATRIX;
    }
  } else {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!s21_is_empty(A) && !s21_is_empty(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      ret = s21_create_matrix(A->rows, A->columns, result);
      if (ret != OK) return ret;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      ret = INCORRECT_MATRIX;
    }
  } else {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = 0;
  if (!s21_is_empty(A)) {
    ret = s21_create_matrix(A->rows, A->columns, result);
    if (ret != OK) return ret;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!s21_is_empty(A) && !s21_is_empty(B)) {
    if (A->columns == B->rows) {
      ret = s21_create_matrix(A->rows, B->columns, result);
      if (ret != OK) return ret;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      ret = INCORRECT_MATRIX;
    }
  } else {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}
