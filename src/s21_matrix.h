#ifndef s21_MATRIX_H
#define s21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define incorrect_matrix 1
#define Calculation_error 2
#define eps 0.0000001
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
// typedef enum { OK = 0, INCORRECT = 1,incorrect_matrix = 1, CALC_ERROR =
// 2,Calculation_error = 2, SEGFAULT = 3 } matrix; typedef enum { FAILURE = 0,
// SUCCESS = 1 } equally;
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
void s21_minor_calc_complements(matrix_t *A, int i, int j, int n_rows,
                                int n_columns, matrix_t minor_matrix);

int s21_determinant(matrix_t *A, double *result);
void s21_det_calc(matrix_t temp, matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#endif