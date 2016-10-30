#ifndef _MATBINTREE_H_
#define _MATBINTREE_H_

# include <stdlib.h>

# include "matrix.h"

typedef struct _MatBinTree{
  UnsignedMatrix     *key;
  struct _MatBinTree *left;
  struct _MatBinTree *right;
}MatBinTree;

MatBinTree* new_matbintree(UnsignedMatrix* mat);

void free_matbintree(MatBinTree* mbt);

#endif
