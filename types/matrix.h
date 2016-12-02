# ifndef MATRIX_H_
# define MATRIX_H_

# include <stdlib.h>
# include "../NeuralNetWork/nr.h"

typedef struct _UnsignedMatrix{
    size_t lines;
    size_t cols;
    unsigned *data;
}UnsignedMatrix;

UnsignedMatrix *new_unsigned_matrix(size_t lines, size_t cols);
UnsignedMatrix* copy_mat(UnsignedMatrix *matrix);
void free_unsigned_matrix(UnsignedMatrix *matrix);

UnsignedMatrix* cut(UnsignedMatrix *matrix,
                    size_t x1, 
                    size_t x2,
                    size_t y1,
                    size_t y2);

UnsignedMatrix* expand_mat(UnsignedMatrix *matrix,
                           size_t xdest,
                           size_t ydest);

Bashint unsignedmatToBashint(UnsignedMatrix *matrix);
# endif
