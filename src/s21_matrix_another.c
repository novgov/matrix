#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (s21_is_empty(A) == 0) {
    ret = s21_create_matrix(A->columns, A->rows, result);
    if (ret == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      s21_remove_matrix(A);
      s21_remove_matrix(result);
    }
  } else {
    s21_remove_matrix(A);
    s21_remove_matrix(result);
    ret = 1;
  }
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      ret = s21_create_matrix(A->columns, A->rows, result);
      if (ret == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor = {0};
            double determinant = 0;
            s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
            s21_get_matrix(i, j, A, &minor);
            s21_determinant(&minor, &determinant);
            result->matrix[i][j] = pow(-1, (i + j)) * determinant;
            s21_remove_matrix(&minor);
          }
        }
      } else {
        s21_remove_matrix(A);
        s21_remove_matrix(result);
      }
    } else {
      s21_remove_matrix(A);
      s21_remove_matrix(result);
      ret = 2;
    }
  } else {
    s21_remove_matrix(A);
    s21_remove_matrix(result);
    ret = 1;
  }
  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  *result = 0.0;
  int ret = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      ret = 2;
    }
  } else {
    ret = 1;
  }
  return ret;
}

double s21_get_determinant(matrix_t *A) {
  double ret = 0.0;
  if (A->rows == 1) {
    ret = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_matrix(0, i, A, &tmp);
      if (i % 2) {
        ret -= A->matrix[0][i] * s21_get_determinant(&tmp);
      } else {
        ret += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 1;
  if (s21_is_empty(A) == 0) {
    ret = 2;
    if (A->rows == 1) {
      ret = s21_create_matrix(A->rows, A->rows, result);
      if (ret == 0) result->matrix[0][0] = 1.0 / A->matrix[0][0];
    }
    double det = 0.0;
    s21_determinant(A, &det);
    if (det != 0) {
      matrix_t tmp_calc = {0};
      ret = s21_calc_complements(A, &tmp_calc);
      if (ret == 0) {
        matrix_t tmp_trans = {0};
        ret = s21_transpose(&tmp_calc, &tmp_trans);
        if (ret == 0) {
          s21_mult_number(&tmp_trans, 1 / det, result);
        }
        s21_remove_matrix(&tmp_trans);
      }
      s21_remove_matrix(&tmp_calc);
    }
  }
  return ret;
}