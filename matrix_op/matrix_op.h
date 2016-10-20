  # ifndef MATRIX_OP_H_
  # define MATRIX_OP_H_

  # include <stdio.h>
  # include <stdlib.h>


  struct Matrix{
    unsigned **mat;
    size_t    x;
    size_t    y;
  };

  unsigned** cut_x(unsigned **mat,size_t y,size_t x1,size_t x2);

  unsigned** cut_y(unsigned **mat,size_t x, size_t y1,size_t y2);

  unsigned** cut(unsigned **matrix,size_t x1, size_t x2,size_t y1,size_t y2);

  unsigned** copy_mat(unsigned **matrix, size_t x,size_t y);

  unsigned** expand_mat(unsigned **matrix,size_t x,size_t y,
    size_t xdest,size_t ydest);


  # endif
