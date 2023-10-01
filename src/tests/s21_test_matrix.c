#include <check.h>

#include "../s21_matrix.h"

matrix_t A = {
    .matrix = (double *[]){(double[]){1.0, 2.0}, (double[]){3.0, 4.0}},
    .rows = 2,
    .columns = 2};

matrix_t a_A = {
    .matrix = (double *[]){(double[]){1.0, 2.0}, (double[]){3.0, 4.0}},
    .rows = 2,
    .columns = 2};

matrix_t Error_matrix = {
    .matrix = (double *[]){(double[]){1.0, 2.0}, (double[]){3.0, 4.0}},
    .rows = -2,
    .columns = -2};

matrix_t B = {.matrix = (double *[]){(double[]){-1.0, 0.0, 2.0},
                                     (double[]){4.0, -2.0, 3.0},
                                     (double[]){1.0, 5.0, 7.0}},
              .rows = 3,
              .columns = 3};

matrix_t C = {.matrix = (double *[]){(double[]){6.0, 3.0, 8.0, 2.0},
                                     (double[]){1.0, 9.0, 4.0, 7.0},
                                     (double[]){5.0, 0.0, 2.0, 1.0},
                                     (double[]){-3.0, 4.0, 7.0, 2.0}},
              .rows = 4,
              .columns = 4};

matrix_t D = {.matrix = (double *[]){(double[]){1.0, 2.0, 3.0, 4.0, 5.0},
                                     (double[]){6.0, -1.0, 7.0, 8.0, 0.0},
                                     (double[]){-2.0, 3.0, 1.0, 0.0, -4.0},
                                     (double[]){7.0, 8.0, -5.0, 1.0, 2.0},
                                     (double[]){0.0, -3.0, 4.0, -2.0, 1.0}},
              .rows = 5,
              .columns = 5};

matrix_t D_d = {
    .matrix = (double *[]){(double[]){2.0, 3.0, 3.0, 100.0, 33.0},
                           (double[]){10.0, -100.0, 7.0, 5.0, 3.0},
                           (double[]){-30.0, 13.0, 31.0, 40.0, -48.0},
                           (double[]){27.0, 38.0, -15.0, 11.0, 21.0},
                           (double[]){110.0, -13.0, 34.0, -12.0, 31.0}},
    .rows = 5,
    .columns = 5};

matrix_t E = {
    .matrix = (double *[]){(double[]){10.0}}, .rows = 1, .columns = 1};

matrix_t F = {
    .matrix =
        (double *[]){(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0},
                     (double[]){7.0, 8.0, 9.0}, (double[]){10.0, 11.0, 12.0}},
    .rows = 4,
    .columns = 3};

matrix_t G = {.matrix = (double *[]){(double[]){2.0, 3.0}, (double[]){4.0, 5.0},
                                     (double[]){6.0, 7.0}},
              .rows = 3,
              .columns = 2};

matrix_t H = {
    .matrix = (double *[]){(double[]){-1.0, -2.0}, (double[]){3.0, 4.0},
                           (double[]){5.0, -1.0}, (double[]){0.0, 2.0}},
    .rows = 4,
    .columns = 2};

START_TEST(test_s21create_matrix) {
  matrix_t test1 = {0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &test1), OK);
  s21_remove_matrix(&test1);

  matrix_t test2 = {0};
  ck_assert_int_eq(s21_create_matrix(10, 10, &test2), OK);
  s21_remove_matrix(&test2);

  matrix_t test3 = {0};
  ck_assert_int_eq(s21_create_matrix(1, 10, &test3), OK);
  s21_remove_matrix(&test3);

  matrix_t test4 = {0};
  ck_assert_int_eq(s21_create_matrix(10, 1, &test4), OK);
  s21_remove_matrix(&test4);

  matrix_t test6 = {0};
  ck_assert_int_eq(s21_create_matrix(1, -11, &test6), Calculation_error);
  s21_remove_matrix(&test6);

  matrix_t test7 = {0};
  ck_assert_int_eq(s21_create_matrix(1, 0, &test7), Calculation_error);
  s21_remove_matrix(&test7);

  matrix_t test8 = {0};
  ck_assert_int_eq(s21_create_matrix(7, 8, &test8), OK);
  s21_remove_matrix(&test8);

  matrix_t test10 = {0};
  ck_assert_int_eq(s21_create_matrix(-11, 1, &test10), Calculation_error);
  s21_remove_matrix(&test10);

  matrix_t *test9 = NULL;
  ck_assert_int_eq(s21_create_matrix(10, 5, test9), Calculation_error);
  s21_remove_matrix(test9);

  ck_assert_int_eq(s21_create_matrix(10, 10, NULL), Calculation_error);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  ck_assert_int_eq(s21_eq_matrix(&A, &a_A), SUCCESS);

  ck_assert_int_eq(s21_eq_matrix(&A, &H), FAILURE);

  ck_assert_int_eq(s21_eq_matrix(&G, &H), FAILURE);

  ck_assert_int_eq(s21_eq_matrix(&A, &A), SUCCESS);

  matrix_t test6 = {0};
  ck_assert_int_eq(s21_eq_matrix(&test6, &A), FAILURE);
  s21_remove_matrix(&test6);

  ck_assert_int_eq(s21_eq_matrix(&H, &H), SUCCESS);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t test_1 = {
      .matrix = (double *[]){(double[]){2.0, 4.0}, (double[]){6.0, 8.0}},
      .rows = 2,
      .columns = 2};
  matrix_t Z = {0};
  s21_sum_matrix(&A, &a_A, &Z);
  int res = s21_eq_matrix(&test_1, &Z);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&Z);

  matrix_t D_sum = {
      .matrix = (double *[]){(double[]){3.0, 5.0, 6.0, 104.0, 38.0},
                             (double[]){16.0, -101.0, 14.0, 13.0, 3.0},
                             (double[]){-32.0, 16.0, 32.0, 40.0, -52.0},
                             (double[]){34.0, 46.0, -20.0, 12.0, 23.0},
                             (double[]){110.0, -16.0, 38.0, -14.0, 32.0}},
      .rows = 5,
      .columns = 5};
  matrix_t X = {0};
  s21_sum_matrix(&D, &D_d, &X);
  int res_2 = s21_eq_matrix(&X, &D_sum);
  s21_remove_matrix(&X);
  ck_assert_int_eq(res_2, SUCCESS);

  matrix_t V = {0};
  int res_3 = s21_sum_matrix(&G, &D, &V);
  ck_assert_int_eq(res_3, incorrect_matrix);
  s21_remove_matrix(&V);

  matrix_t N = {0};
  int res_4 = s21_sum_matrix(&F, &E, &N);
  ck_assert_int_eq(res_4, incorrect_matrix);
  s21_remove_matrix(&N);

  matrix_t M = {0};
  int res_5 = s21_sum_matrix(&A, &Error_matrix, &M);
  ck_assert_int_eq(res_5, Calculation_error);
  s21_remove_matrix(&M);

  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);
  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;
  R2.matrix[0][0] = 3.5;
  s21_sum_matrix(&A, &B, &R);
  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < eps);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);

  matrix_t *AA = NULL;
  matrix_t *BB = NULL;
  matrix_t *RR = NULL;
  int res8 = s21_sum_matrix(AA, BB, RR);
  ck_assert_int_eq(res8, Calculation_error);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t Z = {0};
  matrix_t Z_res = {0};
  s21_create_matrix(2, 2, &Z_res);
  s21_sub_matrix(&A, &a_A, &Z);
  int test_1 = s21_eq_matrix(&Z_res, &Z);
  ck_assert_int_eq(test_1, SUCCESS);
  s21_remove_matrix(&Z_res);
  s21_remove_matrix(&Z);

  matrix_t X = {0};
  matrix_t X_res = {0};
  s21_create_matrix(5, 5, &X_res);
  s21_sub_matrix(&D, &D_d, &X);
  int test_2 = s21_eq_matrix(&X_res, &X);
  ck_assert_int_eq(test_2, FAILURE);
  s21_remove_matrix(&X_res);
  s21_remove_matrix(&X);

  matrix_t V = {0};
  int test_3 = s21_sub_matrix(&B, &E, &V);
  ck_assert_int_eq(test_3, incorrect_matrix);
  s21_remove_matrix(&V);

  matrix_t N = {0};
  int test_4 = s21_sub_matrix(&Error_matrix, &A, &N);
  ck_assert_int_eq(test_4, Calculation_error);
  s21_remove_matrix(&N);

  matrix_t M = {0};
  int test_5 = s21_sub_matrix(&B, &E, &M);
  ck_assert_int_eq(test_5, incorrect_matrix);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(test_s21_mult_number) {
  double number_1 = 1;
  matrix_t Z = {0};
  s21_mult_number(&A, number_1, &Z);
  int test_1 = s21_eq_matrix(&A, &Z);
  ck_assert_int_eq(test_1, SUCCESS);
  s21_remove_matrix(&Z);

  double number_2 = 2;
  matrix_t X = {0};
  s21_mult_number(&A, number_2, &X);
  int test_2 = s21_eq_matrix(&A, &X);
  ck_assert_int_eq(test_2, FAILURE);
  s21_remove_matrix(&X);

  double number_3 = 3;
  matrix_t V = {
      .matrix = (double *[]){(double[]){3.0, 6.0}, (double[]){9.0, 12.0}},
      .rows = 2,
      .columns = 2};
  matrix_t V_v = {0};
  s21_mult_number(&A, number_3, &V_v);
  int test_3 = s21_eq_matrix(&V_v, &V);
  ck_assert_int_eq(test_3, SUCCESS);
  s21_remove_matrix(&V_v);

  double number_4 = 10;
  matrix_t N = {.matrix = (double *[]){(double[]){-10.0, 00.0, 20.0},
                                       (double[]){40.0, -20.0, 30.0},
                                       (double[]){10.0, 50.0, 70.0}},
                .rows = 3,
                .columns = 3};
  matrix_t N_n = {0};
  s21_mult_number(&B, number_4, &N_n);
  int test_4 = s21_eq_matrix(&N_n, &N);
  ck_assert_int_eq(test_4, SUCCESS);
  s21_remove_matrix(&N_n);

  double number_5 = 1;
  matrix_t M = {0};
  s21_mult_number(&Error_matrix, number_5, &M);
  int test_5 = s21_eq_matrix(&Error_matrix, &M);
  ck_assert_int_eq(test_5, FAILURE);
  s21_remove_matrix(&M);
}

END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t Z = {0};
  int test_1 = s21_mult_matrix(&A, &a_A, &Z);
  ck_assert_int_eq(test_1, OK);
  s21_remove_matrix(&Z);

  matrix_t X = {0};
  int test_2 = s21_mult_matrix(&A, &B, &X);
  ck_assert_int_eq(test_2, Calculation_error);

  matrix_t V = {0};
  int test_3 = s21_mult_matrix(&D, &D_d, &V);
  ck_assert_int_eq(test_3, OK);
  s21_remove_matrix(&V);

  matrix_t N = {0};
  int test_4 = s21_mult_matrix(&Error_matrix, &B, &N);
  ck_assert_int_eq(test_4, Calculation_error);
  s21_remove_matrix(&N);

  matrix_t M = {0};
  int test_5 = s21_mult_matrix(&C, &F, &M);
  ck_assert_int_eq(test_5, OK);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t G_test = {.matrix = (double *[]){(double[]){2.0, 4.0, 6, 0},
                                            (double[]){3.0, 5.0, 7.0}},
                     .rows = 2,
                     .columns = 3};
  matrix_t Z = {0};
  s21_transpose(&G, &Z);
  int test_1 = s21_eq_matrix(&Z, &G_test);
  ck_assert_int_eq(test_1, SUCCESS);
  s21_remove_matrix(&Z);

  matrix_t H_test = {.matrix = (double *[]){(double[]){-1.0, 3.0, 5.0, 0.0},
                                            (double[]){-2.0, 4.0, -1.0, 2.0}},
                     .rows = 2,
                     .columns = 4};
  matrix_t X = {0};
  s21_transpose(&H, &X);
  int test_2 = s21_eq_matrix(&X, &H_test);
  ck_assert_int_eq(test_2, SUCCESS);
  s21_remove_matrix(&X);

  matrix_t V = {0};
  int test_3 = s21_transpose(&Error_matrix, &V);
  ck_assert_int_eq(test_3, Calculation_error);
  s21_remove_matrix(&V);

  matrix_t N = {0};
  int test_4t = s21_transpose(&F, &N);
  int test_4 = s21_eq_matrix(&N, &F);
  ck_assert_int_eq(test_4t, OK);
  ck_assert_int_eq(test_4, FAILURE);
  s21_remove_matrix(&N);

  matrix_t M = {0};
  int test_5t = s21_transpose(&D, &M);
  int test_5 = s21_eq_matrix(&D, &F);
  ck_assert_int_eq(test_5t, OK);
  ck_assert_int_eq(test_5, FAILURE);
  s21_remove_matrix(&M);
}
END_TEST
START_TEST(test_s21_calc_complements) {
  int res = 0;
  matrix_t AAaa = {0};
  matrix_t Z = {0};
  matrix_t XXxx = {0};

  s21_create_matrix(4, 4, &AAaa);
  AAaa.matrix[0][0] = 112.0;
  AAaa.matrix[0][1] = 243.0;
  AAaa.matrix[0][2] = 3.0;
  AAaa.matrix[0][3] = -8.0;
  AAaa.matrix[1][0] = 47.0;
  AAaa.matrix[1][1] = 51.0;
  AAaa.matrix[1][2] = -66.0;
  AAaa.matrix[1][3] = 99.0;
  AAaa.matrix[2][0] = -74.0;
  AAaa.matrix[2][1] = 85.0;
  AAaa.matrix[2][2] = 97.0;
  AAaa.matrix[2][3] = 63.0;
  AAaa.matrix[3][0] = -13.0;
  AAaa.matrix[3][1] = 79.0;
  AAaa.matrix[3][2] = -99.0;
  AAaa.matrix[3][3] = -121.0;

  s21_calc_complements(&AAaa, &Z);

  s21_create_matrix(4, 4, &XXxx);

  XXxx.matrix[0][0] = -2879514.0;
  XXxx.matrix[0][1] = -1236631.0;
  XXxx.matrix[0][2] = -1685096.0;
  XXxx.matrix[0][3] = 880697.0;
  XXxx.matrix[1][0] = 1162090.0;
  XXxx.matrix[1][1] = -714015.0;
  XXxx.matrix[1][2] = 4046255.0;
  XXxx.matrix[1][3] = -3901600.0;
  XXxx.matrix[2][0] = 4362897.0;
  XXxx.matrix[2][1] = -2049432.0;
  XXxx.matrix[2][2] = -532912.0;
  XXxx.matrix[2][3] = -1370781.0;
  XXxx.matrix[3][0] = 3412773.0;
  XXxx.matrix[3][1] = -1569493.0;
  XXxx.matrix[3][2] = 3144517.0;
  XXxx.matrix[3][3] = 1284666.0;

  res = s21_eq_matrix(&XXxx, &Z);
  s21_remove_matrix(&AAaa);
  s21_remove_matrix(&XXxx);
  s21_remove_matrix(&Z);
  ck_assert_int_eq(res, SUCCESS);

  matrix_t A_test = {
      .matrix = (double *[]){(double[]){4.0, -3.0}, (double[]){-2.0, 1.0}},
      .rows = 2,
      .columns = 2};
  matrix_t A_test_res = {0};
  s21_calc_complements(&A, &A_test_res);
  int test_1 = s21_eq_matrix(&A_test, &A_test_res);
  ck_assert_int_eq(test_1, SUCCESS);
  s21_remove_matrix(&A_test_res);

  matrix_t C_test = {
      .matrix = (double *[]){(double[]){-67.0, -232.0, 19.0, 297.0},
                             (double[]){-7.0, -40.0, 23.0, -11.0},
                             (double[]){51.0, 392.0, -67.0, -473.0},
                             (double[]){66.0, 176.0, -66.0, -198.0}},
      .rows = 4,
      .columns = 4};
  matrix_t C_test_res = {0};
  s21_calc_complements(&C, &C_test_res);
  int test_2 = s21_eq_matrix(&C_test, &C_test_res);
  ck_assert_int_eq(test_2, SUCCESS);
  s21_remove_matrix(&C_test_res);

  matrix_t D_test = {
      .matrix =
          (double *[]){(double[]){-1418.0, 1180.0, 728.0, 574.0, 1776.0},
                       (double[]){878.0, -539.0, 225.0, 865.0, -787.0},
                       (double[]){-816.0, 2081.0, 1599.0, -527.0, -1207.0},
                       (double[]){1260.0, 888.0, 160.0, -974.0, 76.0},
                       (double[]){1306.0, 648.0, 2436.0, -3030.0, 442.0}},
      .rows = 5,
      .columns = 5};
  matrix_t D_test_res = {0};
  s21_calc_complements(&D, &D_test_res);
  int test_3 = s21_eq_matrix(&D_test, &D_test_res);
  ck_assert_int_eq(test_3, SUCCESS);
  s21_remove_matrix(&D_test_res);

  matrix_t err = {0};
  int test_4 = s21_calc_complements(&Error_matrix, &err);
  ck_assert_int_eq(test_4, Calculation_error);
  s21_remove_matrix(&err);

  matrix_t E_test = {
      .matrix = (double *[]){(double[]){-10.0}}, .rows = 1, .columns = 1};
  matrix_t err_1 = {0};
  s21_calc_complements(&E, &err_1);
  int test_5 = s21_eq_matrix(&E_test, &E);

  ck_assert_int_eq(test_5, OK);
  s21_remove_matrix(&err_1);
}
END_TEST

START_TEST(test_s21_determinant) {
  double test_1 = 0.0;
  s21_determinant(&A, &test_1);
  ck_assert_double_eq(test_1, -2.0);

  double test_2 = 0.0;
  s21_determinant(&B, &test_2);
  ck_assert_double_eq(test_1, -2.0);

  double test_3 = 0.0;
  s21_determinant(&C, &test_3);
  ck_assert_float_eq(test_3, -352.0);

  double test_4 = 0.0;
  int test_4_det = s21_determinant(&Error_matrix, &test_4);
  ck_assert_int_eq(test_4_det, Calculation_error);

  double test_5 = 0.0;
  int test_5_det = s21_determinant(&F, &test_5);
  ck_assert_int_eq(test_5_det, incorrect_matrix);

  double test_6 = 0.0;
  int test_6_det = s21_determinant(&H, &test_6);
  ck_assert_int_eq(test_6_det, incorrect_matrix);

  double test_7 = 0.0;
  int test_7_det = s21_determinant(&G, &test_7);
  ck_assert_int_eq(test_7_det, incorrect_matrix);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  matrix_t inv_task = {.matrix = (double *[]){(double[]){2.0, 5.0, 7.0},
                                              (double[]){6.0, 3.0, 4.0},
                                              (double[]){5.0, -2.0, -3.0}},
                       .rows = 3,
                       .columns = 3};
  matrix_t inv_B_test = {0};
  int resBB = s21_inverse_matrix(&inv_task, &inv_B_test);
  ck_assert_int_eq(resBB, OK);
  s21_remove_matrix(&inv_B_test);

  matrix_t inv_A = {
      .matrix = (double *[]){(double[]){-2.0, 1.0}, (double[]){1.5, -0.5}},
      .rows = 2,
      .columns = 2};
  matrix_t test2 = {0};
  s21_inverse_matrix(&A, &test2);
  int test_2 = s21_eq_matrix(&test2, &inv_A);
  ck_assert_int_eq(test_2, SUCCESS);
  s21_remove_matrix(&test2);

  matrix_t matrix_B = {.matrix = (double *[]){(double[]){1.0, 1.0, 1.0},
                                              (double[]){1.0, 1.0, 1.0},
                                              (double[]){1.0, 1.0, 1.0}},
                       .rows = 3,
                       .columns = 3};

  matrix_t test3 = {0};
  int test_33 = s21_inverse_matrix(&matrix_B, &test3);
  ck_assert_int_eq(test_33, Calculation_error);

  matrix_t matrix_c = {.matrix = (double *[]){(double[]){1.0, -1.0, 2.0},
                                              (double[]){0.0, 2.0, -1.0},
                                              (double[]){1.0, 0.0, 1.0}},
                       .rows = 3,
                       .columns = 3};
  matrix_t inv_c = {.matrix = (double *[]){(double[]){-2.0, -1.0, 3.0},
                                           (double[]){1.0, 1.0, -1.0},
                                           (double[]){2.0, 1.0, -2.0}},
                    .rows = 3,
                    .columns = 3};
  matrix_t test4 = {0};
  s21_inverse_matrix(&matrix_c, &test4);
  int test_4 = s21_eq_matrix(&test4, &inv_c);
  ck_assert_int_eq(test_4, SUCCESS);
  s21_remove_matrix(&test4);

  matrix_t matrix_d = {.matrix = (double *[]){(double[]){1.0, 5.0, 1.0},
                                              (double[]){3.0, 2.0, 1.0},
                                              (double[]){6.0, -2.0, 1.0}},
                       .rows = 3,
                       .columns = 3};
  matrix_t inv_d = {.matrix = (double *[]){(double[]){4.0, -7.0, 3.0},
                                           (double[]){3.0, -5.0, 2.0},
                                           (double[]){-18.0, 32.0, -13.0}},
                    .rows = 3,
                    .columns = 3};
  matrix_t test5 = {0};
  s21_inverse_matrix(&matrix_d, &test5);
  int test_5 = s21_eq_matrix(&test5, &inv_d);
  ck_assert_int_eq(test_5, SUCCESS);
  s21_remove_matrix(&test5);

  matrix_t matrix_e = {
      .matrix = (double *[]){(double[]){1.0, 4.0, 2.0, 3.0},
                             (double[]){1.0, -2.0, 1.0, -2.0},
                             (double[]){1.0, -1.0, 1.0, 1.0},
                             (double[]){0.0, -10.0, -2.0, -5.0}},
      .rows = 4,
      .columns = 4};
  matrix_t inv_e = {.matrix = (double *[]){(double[]){33.0, -6.0, -26.0, 17.0},
                                           (double[]){6.0, -1.0, -5.0, 3.0},
                                           (double[]){-25.0, 5.0, 20.0, -13.0},
                                           (double[]){-2.0, 0.0, 2.0, -1.0}},
                    .rows = 4,
                    .columns = 4};
  matrix_t test6 = {0};
  s21_inverse_matrix(&matrix_e, &test6);
  int test_6 = s21_eq_matrix(&test6, &inv_e);
  ck_assert_int_eq(test_6, SUCCESS);
  s21_remove_matrix(&test6);
}
END_TEST

Suite *s21_matrix_tests_create() {
  Suite *s21_matrix = suite_create("s21_matrix");
  TCase *s21_matrix_tests = tcase_create("S21_MATRIX");
  tcase_add_test(s21_matrix_tests, test_s21create_matrix);
  tcase_add_test(s21_matrix_tests, test_s21_eq_matrix);
  tcase_add_test(s21_matrix_tests, test_s21_sum_matrix);
  tcase_add_test(s21_matrix_tests, test_s21_sub_matrix);
  tcase_add_test(s21_matrix_tests, test_s21_mult_number);
  tcase_add_test(s21_matrix_tests, test_s21_mult_matrix);
  tcase_add_test(s21_matrix_tests, test_s21_transpose);
  tcase_add_test(s21_matrix_tests, test_s21_calc_complements);
  tcase_add_test(s21_matrix_tests, test_s21_determinant);
  tcase_add_test(s21_matrix_tests, test_s21_inverse_matrix);

  suite_add_tcase(s21_matrix, s21_matrix_tests);
  return s21_matrix;
}

int main() {
  Suite *s21_matrix = s21_matrix_tests_create();
  SRunner *s21_matrix_runner = srunner_create(s21_matrix);
  int number_failed;
  srunner_run_all(s21_matrix_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_matrix_runner);
  srunner_free(s21_matrix_runner);
  return number_failed == 0 ? 0 : 1;
}
