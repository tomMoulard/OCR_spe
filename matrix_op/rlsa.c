# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rlsa.h"
# include "../types/matrix.h"

int isokh(UnsignedMatrix *mat, size_t pos, int coef){
  size_t max = mat->lines * mat->cols;
  while (pos < max && mat->data[pos] == 0 && coef > 0) {
    coef--;
    pos += mat->cols;
  }
  if(pos >= max || mat->data[pos] == 1){
    return 1;
  }
  else{
    return 0;
  }
  return 0;
}

UnsignedMatrix* horizontal(UnsignedMatrix *matrix, int coef){

  UnsignedMatrix *mat = copy_mat(matrix);
  int isblack;

    for (size_t j = 0; j < mat->cols; j++) {
      isblack = isokh(matrix,mat->cols + j,coef);
      for (size_t i = 0; i < mat->lines; i++) {

      if (matrix->data[i * matrix->cols + j] == 1) {
        isblack = isokh(matrix,(i + 1) * matrix->cols + j,coef);
        mat->data[i * mat->cols + j] = 1;
      }
      else{
        if (isblack > 0) {
          mat->data[i * mat->cols + j] = 1;
        }
        else{
          mat->data[i * mat->cols + j] = 0;
        }
      }
    }
  }
  return mat;
}


int isokv(UnsignedMatrix *mat, size_t pos, int coef){
  size_t max = ((pos / mat->cols) + 1) * mat->cols;
  while (pos < max && mat->data[pos] == 0 && coef > 0) {
    coef--;
    pos++;
  }
  if(pos >= max || mat->data[pos] == 1){
    return 1;
  }
  else{
    return 0;
  }
  return 0;
}

UnsignedMatrix* vertical(UnsignedMatrix *matrix, int coef){

  UnsignedMatrix *mat = copy_mat(matrix);

  int isblack;

  for (size_t i = 0; i < mat->lines; i++) {

  isblack = isokv(matrix,i * mat->cols,coef);

  for (size_t j = 0; j < mat->cols; j++) {

      if (matrix->data[i * matrix->cols + j] == 1) {
        isblack = isokv(matrix,(i + 1) * matrix->cols + j,coef);
        mat->data[i * mat->cols + j] = 1;
      }
      else{
        if (isblack > 0) {
          mat->data[i * mat->cols + j] = 1;
        }
        else{
          mat->data[i * mat->cols + j] = 0;
        }
      }
    }
  }
  return mat;
}

UnsignedMatrix* rlsa(UnsignedMatrix *matrix,int coefh,int coefv){
  UnsignedMatrix *math = horizontal(matrix,coefh);
  UnsignedMatrix *matv = vertical(matrix,coefv);
  UnsignedMatrix *mat = new_unsigned_matrix(matrix->lines,matrix->cols);

  size_t x = mat->lines;
  size_t y = mat->cols;
  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {
      mat->data[i * y + j] = math->data[i * y + j] && matv->data[i * y + j];
    }
  }

  free_unsigned_matrix(math);
  free_unsigned_matrix(matv);
  return mat;

}
