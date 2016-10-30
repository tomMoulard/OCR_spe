# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "../types/matbintree.h"
# include "../types/matrix.h"
# include "xycut.h"

int iswhitestripeshor(UnsignedMatrix *mat,size_t y){
  size_t max = mat->lines * mat->cols;
  while (y < max && mat->data[y] == 0) {
    y += mat->cols;
  }
  return y >= max;
}

void hor_cut_pos(UnsignedMatrix *mat,size_t *y1,size_t *y2){
  size_t t1,t2;
  for (size_t i = 0; i < mat->cols; i++) {
    if (i < mat->cols && iswhitestripeshor(mat,i)) {
      t1 = i;
      t2 = i;

      while (i < mat->cols && iswhitestripeshor(mat,i)) {
        t2++;
        i++;
      }


      if (t2 - t1 > *y2 - *y1) {
        *y1 = t1;
        *y2 = t2;
      }
    }
  }
}

int hor_cut(MatBinTree *mbt,size_t coef){
  size_t y1 = 0;
  size_t y2 = coef;
  hor_cut_pos(mbt->key,&y1,&y2);

  if (y2 == coef){
    UnsignedMatrix *mat = copy_mat(mbt->key);
    mbt->left = new_matbintree(mat);
    return 0;
  }
  if (y1 == 0) {
    UnsignedMatrix *mat = cut(mbt->key,0,mbt->key->lines,y2,mbt->key->cols);
    mbt->left = new_matbintree(mat);
    return 1;
  }
  if (y2 == mbt->key->lines) {
    UnsignedMatrix *mat = cut(mbt->key,0,mbt->key->lines,0,y1);
    mbt->left = new_matbintree(mat);
    return 1;
  }

  UnsignedMatrix *matl = cut(mbt->key,0,mbt->key->lines,0,y1);
  UnsignedMatrix *matr = cut(mbt->key,0,mbt->key->lines,y2,mbt->key->cols);
  mbt->left = new_matbintree(matl);
  mbt->right = new_matbintree(matr);
  return 1;
}

int iswhitestripesver(UnsignedMatrix *mat,size_t x){
  size_t max = x + mat->cols;
  while (x < max && mat->data[x] == 0) {
    x++;
  }
  return x >= max;
}

void ver_cut_pos(UnsignedMatrix *mat,size_t *x1,size_t *x2){
  size_t t1,t2;
  for (size_t i = 0; i < mat->lines; i++) {
    if (i < mat->lines && iswhitestripesver(mat,i * mat->cols)) {
      t1 = i;
      t2 = i;

      while (i < mat->lines && iswhitestripesver(mat,i*mat->cols)) {
        t2++;
        i++;
      }

      if (t2 - t1 > *x2 - *x1) {
        *x1 = t1;
        *x2 = t2;
      }
    }
  }
}

int ver_cut(MatBinTree *mbt,size_t coef){
  size_t x1 = 0;
  size_t x2 = coef;
  ver_cut_pos(mbt->key,&x1,&x2);


  if (x2 == coef){
    UnsignedMatrix *mat = copy_mat(mbt->key);
    mbt->left = new_matbintree(mat);
    return 0;
  }
  if (x1 == 0) {
    UnsignedMatrix *mat = cut(mbt->key,x2,mbt->key->lines,0,mbt->key->cols);
    mbt->left = new_matbintree(mat);
    return 1;
  }
  if (x2 == mbt->key->lines) {
    UnsignedMatrix *mat = cut(mbt->key,0,x1,0,mbt->key->cols);
    mbt->left = new_matbintree(mat);
    return 1;
  }



  UnsignedMatrix *matl = cut(mbt->key,0,x1,0,mbt->key->cols);
  UnsignedMatrix *matr = cut(mbt->key,x2,mbt->key->lines,0,mbt->key->cols);
  mbt->left = new_matbintree(matl);
  mbt->right = new_matbintree(matr);
  return 1;
}

UnsignedMatrix* supprbord(UnsignedMatrix *mat){
  size_t x1 = 0;
  while (iswhitestripesver(mat,x1 * mat->cols)) {
    x1++;
  }
  size_t x2 = mat->lines;
  while (iswhitestripesver(mat,x2 * mat->cols)) {
    x2--;
  }
  size_t y1 = 0;

  while (iswhitestripeshor(mat,y1)) {
    y1++;
  }
  size_t y2 =mat->cols;
  while (iswhitestripeshor(mat,y2)) {
    y2--;
  }
  return cut(mat,x1,x2,y1,y2);
}

void xycut(MatBinTree * mbt, int hor,int ver,size_t h){
  if (mbt && (hor || ver)) {
    if (h % 2 == 0) {
      int a = hor_cut(mbt,0);
      xycut(mbt->left,a,ver,h + 1);
      xycut(mbt->right,a,ver,h + 1);
    }
    else{
      int a = ver_cut(mbt,0);
      xycut(mbt->left,hor,a,h + 1);
      xycut(mbt->right,hor,a,h + 1);
    }
  }
}