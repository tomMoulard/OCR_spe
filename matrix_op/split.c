# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "split.h"

/*  struct Triplet split_y(unsigned *matrix, size_t x, size_t y, size_t pos){
    struct Triplet yolo;
    return yolo;
  }*/

  void array_copy(unsigned *source,unsigned *dest, size_t len){
    for (size_t i = 0; i < len; i++) {
      dest[i] = source[i];
    }
  }

  struct Matrix_double split_x(
    unsigned **matrix, size_t x, size_t y,size_t pos){

    unsigned **matrix1 = calloc(x - pos,sizeof(unsigned[y]));
    unsigned **matrix2 = calloc(pos,sizeof(unsigned[y]));

    for (size_t i = 0; i < x - pos; i++) {
      matrix1[i] = calloc(y,sizeof(unsigned));
      array_copy(matrix[i],matrix1[i],y);

    }

    for (size_t i = pos; i < x; i++) {
      *(matrix2 + i) = calloc(y,sizeof(unsigned));
      array_copy(matrix[i],matrix2[i],y);
    }

    struct Triplet mat1;
    mat1.matrix = matrix1;
    mat1.x = x - pos;
    mat1.y = y;
    printf("%zu\n", mat1.x);
    printf("%zu\n", mat1.y);

    struct Triplet mat2;
    mat2.matrix = matrix2;
    mat2.x = pos;
    mat2.y = y;

    struct  Matrix_double res;
    res.matrix2 = mat1;
    res.matrix2 = mat2;

    return res;
  }
