# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rlsa.h"
# include "../types/matrix.h"
# include "../types/rectangle.h"

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

void eight_conn(UnsignedMatrix *mat,size_t x,size_t y){
  size_t imin = x > 0? x - 1 : 0;
  size_t imax = x < mat->lines?x + 1: mat->lines;
  size_t jmin = y > 0? y - 1 : 0;
  size_t jmax = x < mat->cols?y + 1: mat->cols;
  unsigned coef = mat->data[x * mat->cols + y];
  unsigned data;
  for (size_t i = imin; i < imax + 1; i++) {
    for (size_t j = jmin; j < jmax + 1;j++) {

      data = mat->data[i * mat->cols + j];
      coef = (data > 1 && data < coef)?data:coef;
    }
  }
  mat->data[x * mat->cols + y] = coef;
}

UnsignedMatrix* ecc(UnsignedMatrix *matrix,unsigned *coef){
  UnsignedMatrix *mat = copy_mat(matrix);
  *coef = 1;
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      if (mat->data[i * mat->cols +j] > 0){
        mat->data[i * mat->cols +j] = *coef;
        eight_conn(mat,i,j);
        if (mat->data[i * mat->cols +j] == *coef) {
          (*coef)++;
        }
      }
    }
  }
  for (size_t i = mat->lines; i > 0; i--) {
    for (size_t j = mat->cols; j > 0; j--) {
      if (mat->data[i * mat->cols +j] > 0) {
        eight_conn(mat,i,j);
      }
    }
  }

  return mat;
}

unsigned getmaxarea(UnsignedMatrix *mat,size_t len){
  unsigned *values = malloc(len * sizeof(unsigned));
  for (size_t i = 0; i < len; i++) {
    values[i] = 0;
  }
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      values[mat->data[i * mat->cols +j]]++;
    }
  }
  unsigned max = 1;
  for (size_t i = 2; i < len; i++) {
    max = values[max] > values[i]?max:i;
  }
  return max;
}

Rect getmaxrect(UnsignedMatrix *mat,size_t len){
  unsigned maxarea = getmaxarea(mat,len);
  size_t x1 = mat->lines;
  size_t x2 = 0;
  size_t y1 = mat->cols;
  size_t y2 = 0;
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      if (mat->data[i * mat->cols + j] == maxarea) {
        x1 = x1 < i?x1:i;
        x2 = x2 > i?x2:i;
        y1 = y1 < j?y1:j;
        y2 = y2 > j?y2:j;
      }
    }
  }
  Rect rect;
  rect.a1.x = x1;
  rect.a1.y = y1;
  rect.a2.x = x2 + 1;
  rect.a2.y = y2 + 1;
  return rect;
}

void eraseimage(UnsignedMatrix *mat,int coefh,int coefv){
  unsigned coef = 0;

  UnsignedMatrix* matecc = ecc(horizontal(rlsa(mat,coefh,coefv),2),&coef);

  Rect rect = getmaxrect(matecc,coef);
  for (size_t i = rect.a1.x; i < rect.a2.x; i++) {
    for (size_t j = rect.a1.y; j < rect.a2.y; j++) {
      mat->data[i * mat->cols + j] = 0;
    }
  }
  free_unsigned_matrix(matecc);

}
