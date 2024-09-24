#include "s21_matrix.h"

// Creates a matrix with given rows and columns, initializing all elements to 0
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = OK;
  if (rows < 1 || columns < 1) {
    ret = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      ret = MALLOC_FAILED;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          s21_clear_shit(rows, result->matrix);
          free(result->matrix);
          result->matrix = NULL;
          ret = MALLOC_FAILED;
          break;
        }
      }
    }
  }
  return ret;
}

// Removes a matrix, freeing allocated memory
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
    }
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

void s21_clear_shit(int rows, double **matrix) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < i; j++) {
      free(matrix[j]);
    }
  }
  free(matrix);
}