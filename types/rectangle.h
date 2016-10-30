# ifndef _RECTANGLE_H_
# define _RECTANGLE_H_

# include <stdio.h>
# include <stdlib.h>

# include "../types/matrix.h"

typedef struct Coordinates Coordinates;
struct Coordinates{
  size_t x;
  size_t y;
};

typedef struct Rect Rect;
struct Rect{
  Coordinates a1;
  Coordinates a2;
};

Coordinates new_coords(size_t x,size_t y);

Rect new_rect(size_t x1,size_t y1,size_t x2,size_t y2);

Rect* allrect(UnsignedMatrix *matrix, size_t coefh,size_t coefv
              ,size_t len,size_t *max);

void printrect(Rect rect);

//display one rec in a mat
void displayrect(UnsignedMatrix *matrix,Rect currect, unsigned col);

//displays all rects from a list in a mat
void displayrects(UnsignedMatrix *matrix,Rect* rect,size_t max);

UnsignedMatrix** getrect(UnsignedMatrix *matrix,
  size_t coefh,size_t coefv,size_t *len);

# endif
