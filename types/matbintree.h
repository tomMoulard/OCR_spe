#ifndef _MATBINTREE_H_
#define _MATBINTREE_H_

# include <stdlib.h>

# include "../image_op/sdl_fct.h"
# include "matrix.h"
# include "rectangle.h"
//# include "../NeuralNetWork/nr.h"


typedef struct _MatBinTree{
  UnsignedMatrix     *key;
  Rect               pos;
  int                 hor;
  int                 ver;
  char               *txt;
  struct _MatBinTree *left;
  struct _MatBinTree *right;
}MatBinTree;

MatBinTree* new_matbintree(UnsignedMatrix* mat);
void free_matbintree(MatBinTree* mbt);
void mbt_print(MatBinTree *mbt, size_t h);
void display_leaves(MatBinTree* mbt);
unsigned get_all_rect(MatBinTree* mbt, UnsignedMatrix *mat, unsigned h);
void get_leaves(MatBinTree* mbt,UnsignedMatrix *mat,unsigned h);
UnsignedMatrix** get_letters(MatBinTree *mbt,size_t *len);
#endif
