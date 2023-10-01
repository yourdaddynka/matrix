#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int create_status = Calculation_error;
  if (result && rows > 0 && columns > 0 &&
      (result->matrix = (double **)calloc((rows), sizeof(double *)))) {
    result->columns = columns, result->rows = rows;
    create_status = OK;
    for (int i = 0; i < result->rows; i++) {
      if (!(result->matrix[i] = (double *)calloc((columns), sizeof(double)))) {
        for (int free_matrix = 0; free_matrix < i; free_matrix++) {
          free(result->matrix[free_matrix]);
        }
        free(result->matrix);
        create_status = Calculation_error;
        return create_status;
      }
    }
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0.0;
      }
    }
  }
  return create_status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int free_matrix = 0; free_matrix < A->rows; free_matrix++) {
      free(A->matrix[free_matrix]);
    }
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (A && B && A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((fabs(A->matrix[i][j] - B->matrix[i][j])) >= eps) {
          status = FAILURE;
          break;
        }
      }
    }
  } else
    status = FAILURE;
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = Calculation_error;
  if (A && B && result && A->rows > 0 && A->columns > 0 && B->columns > 0 &&
      B->rows > 0) {
    res = incorrect_matrix;
    if (A->rows == B->rows && B->columns == A->columns &&
        (s21_create_matrix(A->rows, A->columns, result) == OK)) {
      res = OK;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = Calculation_error;
  if (A && B && result && A->rows > 0 && A->columns > 0 && B->columns > 0 &&
      B->rows > 0) {
    res = incorrect_matrix;
    if (A->rows == B->rows && B->columns == A->columns &&
        (s21_create_matrix(A->rows, A->columns, result) == OK)) {
      res = OK;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = Calculation_error;
  if (A && B && result && A->columns == B->rows && A->rows > 0 && B->rows > 0 &&
      B->columns > 0 && A->columns > 0 &&
      (s21_create_matrix(A->rows, B->columns, result) == OK)) {
    res = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int s = 0; s < A->columns; s++) {
          result->matrix[i][j] += A->matrix[i][s] * B->matrix[s][j];
        }
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = Calculation_error;
  if (A && result && A->rows > 0 && A->columns > 0) {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      res = OK;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = Calculation_error;
  if (A && result && A->rows > 0 && A->columns > 0) {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      res = OK;
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = Calculation_error;
  if (A && A->columns > 0 && A->rows > 0) {
    res = incorrect_matrix;
    matrix_t minor_matrix = {0};
    if (A->rows == A->columns && A &&
        (s21_create_matrix(A->rows, A->columns, result) == OK) &&
        (s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix) == OK)) {
      res = OK;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          double minor = 0.0;
          int n_columns = 0, n_rows = 0;
          minor_matrix.rows = A->rows - 1;
          minor_matrix.columns = A->rows - 1;
          s21_minor_calc_complements(A, i, j, n_rows, n_columns, minor_matrix);
          s21_determinant(&minor_matrix, &minor);
          result->matrix[i][j] = pow((-1), (i + j)) * minor;
        }
      }
      s21_remove_matrix(&minor_matrix);
    }
  }
  return res;
}

void s21_minor_calc_complements(matrix_t *A, int i, int j, int n_rows,
                                int n_columns, matrix_t minor_matrix) {
  for (int min_rows = 0; min_rows < A->rows; min_rows++) {
    if (min_rows == i) n_rows = 1;
    n_columns = 0;
    for (int min_columns = 0; min_columns < A->columns; min_columns++) {
      if (min_columns == j) n_columns = 1;
      if (min_rows != i && min_columns != j) {
        minor_matrix.matrix[min_rows - n_rows][min_columns - n_columns] =
            A->matrix[min_rows][min_columns];
      }
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int res = Calculation_error;
  if (A && A->rows > 0 && A->columns > 0) res = incorrect_matrix;
  matrix_t temp = {0};
  if (A->rows == A->columns &&
      (s21_create_matrix(A->rows, A->columns, &temp) == OK)) {
    res = OK;
    for (int i = 0; i < A->rows; i++) {  //копирование матрицы в созданную
      for (int j = 0; j < A->columns; j++) {
        temp.matrix[i][j] = A->matrix[i][j];
      }
    }
    *result = 1.0;
    s21_det_calc(temp, A, result);
    for (int i = 0; i < A->rows; i++) {
      *result = *result * (double)temp.matrix[i][i];
    }
    s21_remove_matrix(&temp);
  }
  return res;
}

void s21_det_calc(matrix_t temp, matrix_t *A, double *result) {
  for (int i = 0; i < A->rows - 1;
       i++) {  // до элемента -1 в связи с "лестницей" метода Гаусса
    if (temp.matrix[i][i] == 0.0) {  //если встречаем 0 на главной диагонали
      for (int j = i + 1; j < A->columns; j++) {
        if (temp.matrix[j][i] != 0.0) {
          double *temp_o = temp.matrix[i];
          temp.matrix[i] = temp.matrix[j];
          temp.matrix[j] = temp_o;
          *result *= -1.0;
          break;
        }
      }
    }
    if (temp.matrix[i][i] != 0.0) {
      for (int j = i + 1; j < A->rows; j++) {
        double coeff = temp.matrix[j][i] / temp.matrix[i][i];
        for (int z = i; z < A->columns; z++) {
          temp.matrix[j][z] -= coeff * (double)temp.matrix[i][z];
        }
      }
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = Calculation_error;
  if (A->rows > 0 && A->columns > 0) res = incorrect_matrix;
  if (A->columns == A->rows) {
    res = OK;
    double det = 0.0;
    s21_determinant(A, &det);
    if (det != 0.0) {
      matrix_t minor = {0};
      s21_calc_complements(A, &minor);
      double dop_mat = (1.0 / det);
      matrix_t trans = {0};
      s21_transpose(&minor, &trans);
      s21_mult_number(&trans, dop_mat, result);
      s21_remove_matrix(&minor);
      s21_remove_matrix(&trans);
    } else
      res = Calculation_error;
  }
  return res;
}
