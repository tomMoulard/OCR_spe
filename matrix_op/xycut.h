# ifndef _XYCUT_H_
# define _XYCUT_H_

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "../types/matbintree.h"
# include "../types/matrix.h"

int hor_cut(MatBinTree *mbt,size_t coef);

int ver_cut(MatBinTree *mbt,size_t coef);

void xycut(MatBinTree * mbt, int hor,int ver,size_t h,size_t coef);

UnsignedMatrix* supprbord(UnsignedMatrix *mat);

# endif
