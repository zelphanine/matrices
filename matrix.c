#include "matrix.h"

int main(void) {
	Matrix m1 = diag_matrix(3, 1, 2, 3);
	Matrix m2 = init_matrix(3, 3);	
	fill_matrix(m2, 2);
	Matrix m3 = multiply_matrix(m1, m2);

	print_matrix(m1);
	print_matrix(m2);
	print_matrix(m3);
	return 0;
}

Matrix init_matrix(size_t rows, size_t columns) {
    Matrix m = malloc(sizeof(Matrix));
    if (m == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    m->rows = rows;
    m->columns = columns;
    m->elements = malloc(rows * columns * sizeof(float));
    if (m->elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return m;
}

void free_matrix(Matrix m) {
    free(m->elements);
    free(m);
}

void fill_matrix(Matrix m, float x) {
	for(size_t row = 1; row <= m->rows; row++) {
		for(size_t column = 1; column <= m->columns; column++) {
			get_element(m, row, column) = x;
		}
	}
}

void randomize_matrix(Matrix m, float lower_bound, float upper_bound) {
    srand(time(NULL));
    for (size_t row = 1; row <= m->rows; row++) {
        for (size_t column = 1; column <= m->columns; column++) {
            float random_value = ((float)rand() / (float)RAND_MAX) * (upper_bound - lower_bound) + lower_bound;
            get_element(m, row, column) = random_value;
        }
    }
}

Matrix diag_matrix(size_t n, ...) {
	Matrix result = init_matrix(n, n);

    va_list args;
    va_start(args, n);

    for (size_t i = 1; i <= n; i++) {
        float value = va_arg(args, float);
        get_element(result, i, i) = value;
    }

    va_end(args);

    return result;
}

void scale_matrix(Matrix m, float x) {
	for(size_t row = 1; row <= m->rows; row++) { 	
		for(size_t column = 1; column <= m->columns; column++) { 	
			get_element(m, row, column) *= x;
		}
	}
}

void print_matrix(Matrix m) {
    printf("┌");
    printf("%*c", (int)m->columns*12+1, ' ');
    printf("┐\n");

    for (size_t row = 1; row <= m->rows; row++) {
        printf("│ ");
        for (size_t column = 1; column <= m->columns; column++) {
			float x = get_element(m, row, column);
			int ix = abs((int)x);
			int ix_digits = ix < 1 ? 1 : (int)log10(ix)+1;
			if(x < 0) { ix_digits++; }; 
            printf("%.*f ", 10-ix_digits, x);
        }
        printf("│\n");
    }

    printf("└");
    printf("%*c", (int)m->columns*12+1, ' ');
    printf("┘%zux%zu\n", m->rows, m->columns);
}

Matrix get_row(Matrix m, size_t row) {
	Matrix row_matrix = init_matrix(1, m->columns);
	for(size_t column = 1; column <= m->columns; column++) {
		get_element(row_matrix, 1, column) = get_element(m, row, column);
	}
	return row_matrix;
}

Matrix get_column(Matrix m, size_t column) {
	Matrix column_matrix = init_matrix(m->rows, 1);
	for(size_t row = 1; row <= m->rows; row++) {
		get_element(column_matrix, row, 1) = get_element(m, row, column);
	}
	return column_matrix;
}

Matrix add_matrix(Matrix a, Matrix b) {
    assert((a->columns == b->columns) && (a->rows == b->rows));

    Matrix result = init_matrix(a->rows, a->columns);

    for(size_t row = 1; row <= result->rows; row++) {
        for(size_t column = 1; column <= result->columns; column++) {
            get_element(result, row, column) = get_element(a, row, column) + get_element(b, row, column);
        }
    }

    return result;
}

Matrix multiply_matrix(Matrix a, Matrix b) {
    assert(a->columns == b->rows);

    Matrix result = init_matrix(a->rows, b->columns);

    for (size_t row = 1; row <= result->rows; row++) {
        for (size_t column = 1; column <= result->columns; column++) {
            float sum = 0;
            for (size_t index = 1; index <= a->columns; index++) {
                sum += get_element(a, row, index) * get_element(b, index, column);
            }
            get_element(result, row, column) = sum;
        }
    }

    return result;
}
