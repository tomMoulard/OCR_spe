# ifndef RLSA_H
# define RLSA_H

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

struct Rect{
  size_t x1;
  size_t y1;
  size_t x2;
  size_t y2;
};

unsigned** horizontal(unsigned **matrix,size_t x,size_t y,int coef);

unsigned** vertical(unsigned **matrix,size_t x,size_t y,int coef);

unsigned** rlsa(unsigned **matrix, size_t x, size_t y ,int coefh,int coefv);

size_t* blockdetect(unsigned **matrix,size_t x ,size_t y);

# endif
