# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rlsa.h"

int isokh(unsigned *array,size_t len, size_t pos, int coef){
  while (pos < len && array[pos] == 0 && coef > 0) {
    coef--;
    pos++;
  }
  if(pos == len || array[pos] == 1){
    return 1;
  }
  else{
    return 0;
  }
}

void _array_hor(unsigned *source,unsigned *dest,size_t len,int coef){
    int isblack = isokh(source,len,0,coef);
    for (size_t j = 0; j < len; j++) {
      if (source[j] == 1) {
        isblack = isokh(source,len,j + 1,coef);
        dest[j] = 1;
      }
      else{
      if (isblack > 0) {
        dest[j] = 1;
      }
      else{
        dest[j] = 0;
      }
    }
  }
}

unsigned** vertical(unsigned **matrix,size_t x, size_t y, int coef){
  unsigned **mat = calloc(x,sizeof(unsigned[y]));
  for (size_t i = 0; i < x; i++) {
    mat[i] = calloc(y,sizeof(unsigned));
    _array_hor(matrix[i],mat[i], y , coef);
  }
    return mat;
}

int isokv(unsigned **matrix,size_t y,size_t len,size_t pos,int coef){
  while (pos < len && matrix[pos][y] == 0 && coef > 0) {
    coef--;
    pos++;
  }
  if(pos == len || matrix[pos][y] == 1){
    return 1;
  }
  else{
    return 0;
  }
}

unsigned** horizontal(unsigned **matrix,size_t x,size_t y,int coef){
  unsigned **mat = calloc(x,sizeof(unsigned[y]));
  for (size_t i = 0; i < x; i++) {
    mat[i] = calloc(y,sizeof(unsigned));
  }

  for (size_t j = 0; j < y; j++) {
    int isblack = isokv(matrix,j,x,0,coef);

    for (size_t i = 0; i < x; i++) {
      if (matrix[i][j] == 1) {
        isblack = isokv(matrix,j,x,i + 1,coef);
        mat[i][j] = 1;
      }
      else{
      if (isblack > 0) {
        mat[i][j] = 1;
      }
      else{
        mat[i][j] = 0;
      }
     }
    }
  }
  return mat;
}

unsigned** rlsa(unsigned **matrix, size_t x, size_t y ,int coefh,int coefv){
  unsigned **math = horizontal(matrix, x, y,coefh);
  unsigned **matv = vertical(matrix,x,y,coefv);
  unsigned **mat = calloc(x,sizeof(unsigned[y]));

  for (size_t i = 0; i < x; i++) {
    mat[i] = calloc(y,sizeof(unsigned));
    for (size_t j = 0; j < y; j++) {
      mat[i][j] = math[i][j] && matv[i][j];
    }
  }

  return mat;

}

/*
size_t* neighboroud(unsigned **matrix,size_t x,size_t y, size_t posx,size_t posy,
size_t coef, size_t *len){
  size_t *neigh = malloc(sizeof(size_t));

  for (size_t i = (posx > coef)?posx - coef:0;
  i < (posx < x - coef)?posx + coef: x; i++) {
    for (size_t j = (posy > coef)? posy - coef : 0;
     j < (posy < x - coef)? posy + coef: y; j++) {
      if (matrix[i][j] == 1) {
        *(neigh + len) = i;
        (*len)++;
        *(neigh + len) = j
        (*len)++;
      }
    }
  }
}

struct Rect blockpos(unsigned **matrix,size_t *pos,size_t x, size_t y,){

}


size_t* blockdetect(unsigned **matrix,size_t x ,size_t y,size_t coef){
  coord = malloc(sizeof(size_t));
  size_t len = 0;
  size_t *neighbor = neighboroud(matrix,x,y,)
}
*/
