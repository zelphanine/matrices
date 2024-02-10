#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void print_matrix(Matrix m);
