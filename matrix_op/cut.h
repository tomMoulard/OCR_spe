  # ifndef CUT_H_
  # define CUT_H_

  # include <stdio.h>
  # include <stdlib.h>


  struct Matrix{
    unsigned **mat;
    size_t    x;
    size_t    y;
  };

  unsigned** cut_x(unsigned **mat,size_t y,size_t x1,size_t x2);

  unsigned** cut_y(unsigned **mat,size_t x, size_t y1,size_t y2);

  # endif
