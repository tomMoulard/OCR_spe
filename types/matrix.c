# include "matrix.h"

UnsignedMatrix *new_unsigned_matrix(size_t lines, size_t cols){
    UnsignedMatrix *matrix;
    matrix = malloc(sizeof(UnsignedMatrix));
    matrix->lines = lines;
    matrix->cols = cols;
    matrix->data = malloc(lines * cols * sizeof(unsigned));
    return matrix;
}

UnsignedMatrix* cut(UnsignedMatrix *matrix,
  size_t x1, size_t x2,size_t y1,size_t y2){

  UnsignedMatrix *mat = new_unsigned_matrix(x2 - x1,y2 - y1);
  for (size_t i = 0; i < x2 - x1; i++) {
    for (size_t j = 0; j < y2 - y1; j++) {
      mat->data[i * mat->cols + j] = matrix->data[(i + x1)* matrix->cols +(j + y1)];
    }
  }

  return mat;
}

UnsignedMatrix* copy_mat(UnsignedMatrix *matrix){
UnsignedMatrix *mat = new_unsigned_matrix(matrix->lines,matrix->cols);
for (size_t i = 0; i < matrix->lines; i++) {
  for (size_t j = 0; j < matrix->cols; j++) {
    mat->data[i * mat->cols + j] = matrix->data[i * matrix->cols + j];
  }
}
return mat;
}

UnsignedMatrix* expand_mat(UnsignedMatrix *matrix,
size_t xdest,size_t ydest){

  UnsignedMatrix *mat = new_unsigned_matrix(xdest,ydest);
  for (size_t i = 0; i < matrix->lines; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {
      mat->data[i * mat->cols + j] = matrix->data[i * matrix->cols + j];
    }
  }

  for (size_t i = matrix->lines; i < xdest; i++) {
    for (size_t j = matrix->cols; j < ydest; j++) {
      mat->data[i * mat->cols + j] = 0;
    }
  }

  return mat;
}

void free_unsigned_matrix(UnsignedMatrix *matrix)
{
    free(matrix->data);
    free(matrix);
}
