# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

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


Rect* allrect(unsigned **matrix,
              size_t x,size_t y, size_t coefh,size_t coefv,
              size_t len,size_t *max);

void displayrect(unsigned **matrix,size_t x,size_t y,size_t coefh,size_t coefv);

unsigned ***getrect(unsigned **matrix,size_t x,size_t y,
  size_t coefh,size_t coefv,size_t *len);
