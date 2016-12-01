# ifndef RLSA_H
# define RLSA_H

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "../types/matrix.h"


UnsignedMatrix* horizontal(UnsignedMatrix *matrix, int coef);

UnsignedMatrix* vertical(UnsignedMatrix *matrix, int coef);

UnsignedMatrix* rlsa(UnsignedMatrix *matrix,int coefh,int coefv);

UnsignedMatrix* ecc(UnsignedMatrix *matrix,unsigned *coef);

UnsignedMatrix* eraseimage(UnsignedMatrix *mat);
//size_t* blockdetect(unsigned **matrix,size_t x ,size_t y);

void get_items_height(UnsignedMatrix* mat,unsigned coef,
  size_t thval1,size_t thval2);

# endif
