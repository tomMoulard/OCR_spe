# include "matbintree.h"
# include "../matrix_op/xycut.h"

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

void mbt_print(MatBinTree *mbt,size_t h){
  if (mbt) {
      display_image(unsignedMatrix_to_pict(mbt->key, 1));
      mbt_print(mbt->left,h + 1);
      mbt_print(mbt->right, h + 1);
  }
}

void display_leaves(MatBinTree* mbt){
  if (mbt) {
    if(!mbt->left){
      if(!mbt->right)
        display_image(unsignedMatrix_to_pict(mbt->key, 1));
      else
        display_leaves(mbt->right);
    }
    else{
      display_leaves(mbt->left);
      if(mbt->right)
        display_leaves(mbt->right);
    }
  }
}

void get_leaves(MatBinTree* mbt,UnsignedMatrix *mat,unsigned h){
  if (mbt) {
    if(!mbt->left){
      if(!mbt->right)
        displayrect(mat,mbt->pos,255);
      else
        get_leaves(mbt->right,mat,h+1);
    }
    else{
      get_leaves(mbt->left,mat,h+1);
      if(mbt->right)
        get_leaves(mbt->right,mat,h+1);
    }
  }
}
unsigned get_all_rect(MatBinTree* mbt,UnsignedMatrix *mat,unsigned h){
  if (!mbt) {
    return h;
  }
  else{
    displayrect(mat,mbt->pos,h);
    unsigned l = get_all_rect(mbt->left,mat,h + 1);
    unsigned r = get_all_rect(mbt->right,mat,h + 1);
    return (h > l) && (h > r)? h :(l > r? l : r);
  }
}

void get_lets(MatBinTree *mbt,UnsignedMatrix **mats,size_t *len){
  if (mbt) {
    if(!mbt->left){
      if(!mbt->right){
        mats[*len] = mbt->key;
        *len += 1;
      }
      else{
        get_lets(mbt->right,mats,len);
      }
    }
    else{
      get_lets(mbt->left,mats,len);
      if(mbt->right){
        get_lets(mbt->right,mats,len);
      }
    }
  }
}

UnsignedMatrix** get_letters(MatBinTree *mbt,size_t *len){
  UnsignedMatrix **mats = malloc(10000 * sizeof(UnsignedMatrix));
  get_lets(mbt,mats,len);
  
  UnsignedMatrix **matrix = malloc(*len * sizeof(UnsignedMatrix));

  for (size_t i = 0; i < *len; i++) {
    matrix[i] = expand_mat(mats[i],30,30);

  }

  free(mats);
  return matrix;
}
