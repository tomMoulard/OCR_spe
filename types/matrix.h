# ifndef MATRIX_H_
# define MATRIX_H_

# include <stdlib.h>

typedef struct _UnsignedMatrix{
    size_t lines;
    size_t cols;
    unsigned *data;
}UnsignedMatrix;

UnsignedMatrix *new_unsigned_matrix(size_t lines, size_t cols);
void free_unsigned_matrix(UnsignedMatrix *matrix);

# endif
