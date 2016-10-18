# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct Rect Rect;
struct Rect{
  size_t x1;
  size_t y1;
  size_t x2;
  size_t y2;
};

Rect* allrect(unsigned **matrix,
              size_t x,size_t y, size_t coef,size_t *len);
