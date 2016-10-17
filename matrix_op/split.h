  # ifndef SPLIT_H_
  # define SPLIT_H_

  # include <stdio.h>
  # include <stdlib.h>


  struct Triplet{
    unsigned **matrix;
    size_t    x;
    size_t    y;
  };

  struct Matrix_double{
    struct Triplet matrix1;
    struct Triplet matrix2;
  };

  //Split_y
//  struct Triplet split_y(unsigned *matrix, size_t x, size_t y, size_t pos);

  struct Matrix_double split_x(
    unsigned **matrix,size_t x,size_t y,size_t pos);

  # endif
