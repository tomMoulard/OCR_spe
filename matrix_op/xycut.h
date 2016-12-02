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

void xycut(MatBinTree * mbt, int hor,int ver,size_t h);

UnsignedMatrix* supprbord(UnsignedMatrix *mat);

void xycut_test(MatBinTree * mbt, int hor,int ver,size_t h);

void split_blocks(MatBinTree *mbt);
# endif
