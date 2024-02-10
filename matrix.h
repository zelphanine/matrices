#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define PI 3.141592654
#define e 2.7182818459045

typedef struct {
	size_t rows;
	size_t columns;
	float *elements;
} *Matrix;

#define get_element(M, row, column) *((M->elements) + (row-1)*M->columns + (column-1))

Matrix init_matrix(size_t rows, size_t columns);
void free_matrix(Matrix m);

void fill_matrix(Matrix m, float x);
void scale_matrix(Matrix m, float x);
void randomize_matrix(Matrix m, float lower_bound, float upper_bound);
Matrix diag_matrix(size_t n, ...);

void print_matrix(Matrix m);

Matrix get_row(Matrix m, size_t row);
Matrix get_column(Matrix m, size_t column);

Matrix add_matrix(Matrix a, Matrix b);
Matrix multiply_matrix(Matrix a, Matrix b);
