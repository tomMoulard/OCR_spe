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
    mbt->left->pos = mbt->pos;
    return 0;
  }
  if (y1 == 0) {
    UnsignedMatrix *mat = cut(mbt->key,0,mbt->key->lines,y2,mbt->key->cols);
    mbt->left = new_matbintree(mat);
    mbt->left->pos = new_rect(mbt->pos.a1.x,mbt->pos.a1.y + y2,
      mbt->pos.a2.x,mbt->pos.a2.y);
    return 1;
  }
  if (y2 == mbt->key->lines) {
    UnsignedMatrix *mat = cut(mbt->key,0,mbt->key->lines,0,y1);
    mbt->left = new_matbintree(mat);
    mbt->left->pos = new_rect(mbt->pos.a1.x,mbt->pos.a1.y,
      mbt->pos.a2.x,mbt->pos.a2.y - y1);
    return 1;
  }

  UnsignedMatrix *matl = cut(mbt->key,0,mbt->key->lines,0,y1);
  UnsignedMatrix *matr = cut(mbt->key,0,mbt->key->lines,y2,mbt->key->cols);
  mbt->left = new_matbintree(matl);
  mbt->left->pos = new_rect(mbt->pos.a1.x,mbt->pos.a1.y,
    mbt->pos.a2.x,mbt->pos.a1.y + y1);
  mbt->right = new_matbintree(matr);
  mbt->right->pos = new_rect(mbt->pos.a1.x,mbt->pos.a1.y + y2,
    mbt->pos.a2.x,mbt->pos.a2.y);
  return (int)(y2 - y1);
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
    mbt->left->pos = mbt->pos;
    return 0;
  }
  if (x1 == 0) {
    UnsignedMatrix *mat = cut(mbt->key,x2,mbt->key->lines,0,mbt->key->cols);
    mbt->left = new_matbintree(mat);
    mbt->left->pos = new_rect(mbt->pos.a1.x + x2,mbt->pos.a1.y,
      mbt->pos.a2.x,mbt->pos.a2.y);
    return 1;
  }
  if (x2 == mbt->key->lines) {
    UnsignedMatrix *mat = cut(mbt->key,0,x1,0,mbt->key->cols);
    mbt->left = new_matbintree(mat);
    mbt->left->pos = new_rect(mbt->pos.a1.x,mbt->pos.a1.y,
      mbt->pos.a2.x - (x2 - x1),mbt->pos.a2.y);
    return 1;
  }

  UnsignedMatrix *matl = cut(mbt->key,0,x1,0,mbt->key->cols);
  UnsignedMatrix *matr = cut(mbt->key,x2,mbt->key->lines,0,mbt->key->cols);
  mbt->left = new_matbintree(matl);
  mbt->left->pos = new_rect(mbt->pos.a1.x,mbt->pos.a1.y,
    mbt->pos.a1.x + x1,mbt->pos.a2.y);
  mbt->right = new_matbintree(matr);
  mbt->right->pos = new_rect(mbt->pos.a1.x + x2,mbt->pos.a1.y,
    mbt->pos.a2.x,mbt->pos.a2.y);
  return (int)(x2 - x1);
}

UnsignedMatrix* supprbord(UnsignedMatrix *mat){
  size_t x1 = 0;
  while (iswhitestripesver(mat,x1 * mat->cols) && x1 < mat->lines) {
    x1++;
  }
  size_t x2 = mat->lines;
  while (iswhitestripesver(mat,x2 * mat->cols) && x2 > 0) {
    x2--;
  }
  size_t y1 = 0;

  while (iswhitestripeshor(mat,y1) && y1 < mat->cols) {
    y1++;
  }
  size_t y2 = mat->cols;
  while (iswhitestripeshor(mat,y2) && y2 > 0) {
    y2--;
  }
  if (x1 >= mat->lines || x2 <= 0 || y1 >= mat->cols || y2 <= 0) {
    return new_unsigned_matrix(1,1);
  }

  if (y2 - y1 > 30) {
      y2 = y1 + 30;
    }

  return cut(mat,x1,x2,y1,y2);

}

void xycut(MatBinTree * mbt, int hor,int ver,size_t h){
  if (mbt && (hor || ver)) {
    if (h % 2 == 0) {
      int a = hor_cut(mbt,10);
      xycut(mbt->left,a,ver,h + 1);
      xycut(mbt->right,a,ver,h + 1);
    }
    else{
      int a = ver_cut(mbt,10);
      xycut(mbt->left,hor,a,h + 1);
      xycut(mbt->right,hor,a,h + 1);
    }
  }
}

void split_column(MatBinTree *mbt) {
  if (mbt) {
    mbt->ver = ver_cut(mbt,0);
    if (mbt->ver) {
      split_column(mbt->left);
      split_column(mbt->right);
    }
  }
}

void split_lines(MatBinTree *mbt) {
  if (mbt) {
    mbt->hor = hor_cut(mbt,0);
    if (mbt->hor) {
      split_lines(mbt->left);
      split_lines(mbt->right);
    }
    else{
      split_column(mbt);
    }
  }
}

void xycut_test(MatBinTree *mbt, int hor,int ver,size_t coef){
  if (mbt && (hor || ver)) {
    if (hor) {
      mbt->hor = hor_cut(mbt,coef);
      if (mbt->hor) {
        xycut_test(mbt->left,mbt->hor,ver,coef);
        xycut_test(mbt->right,mbt->hor,ver,coef);
      }
      else{
          mbt->ver = ver_cut(mbt,coef);
          xycut_test(mbt->left,0,mbt->ver,coef);
          xycut_test(mbt->right,0,mbt->ver,coef);
      }

    }
    else{
      if (ver) {
        mbt->ver = ver_cut(mbt,coef);
        if (mbt->ver) {
          xycut_test(mbt->left,hor,mbt->ver,coef);
          xycut_test(mbt->right,hor,mbt->ver,coef);
        }
        else{
            mbt->hor = hor_cut(mbt,coef);
            xycut_test(mbt->left,mbt->hor,0,coef);
            xycut_test(mbt->right,mbt->hor,0,coef);
        }
      }
    }
  }
  split_lines(mbt);
}
