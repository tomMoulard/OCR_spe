# include "matrix.h"

UnsignedMatrix *new_unsigned_matrix(size_t lines, size_t cols){ 
    UnsignedMatrix *matrix;
    matrix = malloc(sizeof(UnsignedMatrix));
    matrix->lines = lines;
    matrix->cols = cols;
    matrix->data = malloc(lines * cols * sizeof(unsigned));
    return matrix;
}

void free_unsigned_matrix(UnsignedMatrix *matrix)
{
    free(matrix->data);
    free(matrix);
}
