# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "cut.h"

  void array_copy(unsigned *source,unsigned *dest, size_t len){
    for (size_t i = 0; i < len; i++) {
      dest[i] = source[i];
    }
  }

  void array_cut(unsigned *source,unsigned *dest, size_t y1,size_t y2){
    for (size_t i = 0; i < y2 - y1; i++) {
      dest[i] = source[i + y1];
    }
  }

  unsigned** cut_x(unsigned **matrix,size_t y,size_t x1,size_t x2){
    unsigned **mat = calloc(x2 - x1,sizeof(unsigned[y]));
    for (size_t i = x1; i < x2; i++) {
      mat[i] = calloc(y,sizeof(unsigned));
      array_copy(matrix[i],mat[i],y);
    }
    return mat;
  }

  unsigned** cut_y(unsigned **matrix,size_t x, size_t y1,size_t y2){
    unsigned **mat = calloc(x,sizeof(unsigned[y2 - y1]));
    for (size_t i = 0; i < x; i++) {
      mat[i] = calloc(y2 - y1,sizeof(unsigned));
      array_cut(matrix[i],mat[i],y1,y2);
    }
    return mat;
  }

unsigned** copy_mat(unsigned **matrix, size_t x,size_t y){
  unsigned **mat = calloc(x,sizeof(unsigned[y]));
  for (size_t i = 0; i < x; i++) {
    mat[i] = calloc(y,sizeof(unsigned));
    for (size_t j = 0; j < y; j++) {
      mat[i][j] = matrix[i][j];
    }
  }
  return mat;
}
