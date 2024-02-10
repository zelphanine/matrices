#include "matrix.h"

int main(void) {
	Matrix m1 = init_matrix(3, 2);
	get_element(m1, 2, 1) = 54;
	get_element(m1, 2, 2) = -2.718;
	print_matrix(m1);
	free_matrix(m1);
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
    printf("┘\n");
}
