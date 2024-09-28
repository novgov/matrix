#include "s21_test_matrix.h"

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  int ret = s21_create_matrix(rows, cols, &m);
  ck_assert_int_eq(ret, OK);
  if (ret == OK) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = 0;
        ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
      }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
  }
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_2) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_3) {
  const int rows = 10;
  const int cols = 0;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_large_matrix) {
  const int rows = 1000;
  const int cols = 1000;
  matrix_t m = {0};
  int ret = s21_create_matrix(rows, cols, &m);
  ck_assert_int_eq(ret, OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_negative_rows) {
  const int rows = -1;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m); // Free even if not allocated
}
END_TEST

START_TEST(create_negative_cols) {
  const int rows = 10;
  const int cols = -1;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_s21_clear_shit) {
  int rows = 3;
  int columns = 4;
  double **matrix = (double **)calloc(rows, sizeof(double *));

  for (int i = 0; i < rows; i++) {
    matrix[i] = (double *)calloc(columns, sizeof(double));
  }

  ck_assert_ptr_nonnull(matrix);
  for (int i = 0; i < rows; i++) {
    ck_assert_ptr_nonnull(matrix[i]);
  }

  s21_clear_shit(rows, matrix);
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc = tcase_create("case_create_matrix");

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, create_large_matrix);
  tcase_add_test(tc, create_negative_rows);
  tcase_add_test(tc, create_negative_cols);
  tcase_add_test(tc, test_s21_clear_shit);
  suite_add_tcase(s, tc);
  return s;
}
