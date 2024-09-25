#include "s21_test_matrix.h"

START_TEST(mult_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t check = {0};
  matrix_t res = {0};

  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), OK);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &mtx), OK);
  ck_assert_int_eq(s21_create_matrix(m.rows, mtx.columns, &check), OK);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < mtx.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < m.columns; k++) {
        check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
      }
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(simple_mult) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t check = {0};
  matrix_t res = {0};

  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), OK);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &mtx), OK);
  ck_assert_int_eq(s21_create_matrix(m.rows, mtx.columns, &check), OK);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t check = {0};
  matrix_t res = {0};

  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &mtx), INCORRECT_MATRIX);

  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), INCORRECT_MATRIX);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("suite_mult_matrix");
  TCase *tc = tcase_create("case_mult_matrix");

  tcase_add_loop_test(tc, mult_matrix, 0, 100);
  tcase_add_loop_test(tc, mult_matrix2, 0, 100);
  tcase_add_test(tc, simple_mult);

  suite_add_tcase(s, tc);
  return s;
}
