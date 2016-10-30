# include <stdlib.h>
# include <SDL/SDL.h>

# include "matrix.h"
# include "matbintree.h"

MatBinTree* new_matbintree(UnsignedMatrix* mat){
    MatBinTree *mbt = malloc(sizeof(MatBinTree));
    mbt->key = mat;
    mbt->left = NULL;
    mbt->right = NULL;
    return mbt;
  }

void free_matbintree(MatBinTree* mbt){
  if(mbt){
    free_unsigned_matrix(mbt->key);
    free_matbintree(mbt->left);
    free_matbintree(mbt->right);
  }
  else{
    free(mbt);
  }
}
