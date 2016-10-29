# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "../types/matrix.h"

typedef struct Coordinates Coordinates;
struct Coordinates{
  size_t x;
  size_t y;
};

typedef struct Rect Rect;
struct Rect{
  Coordinates a1;
  Coordinates a2;
};


Rect* allrect(UnsignedMatrix *matrix, size_t coefh,size_t coefv
              ,size_t len,size_t *max);

void displayrect(UnsignedMatrix *matrix,size_t coefh,size_t coefv);

UnsignedMatrix** getrect(UnsignedMatrix *matrix,
  size_t coefh,size_t coefv,size_t *len);

typedef struct _RecBinTree{
    Rect    *key;
    struct _RecBinTree *left;
    struct _RecBinTree *right;
  }RecBinTree;

  RecBinTree* new_mecbintree(Rect* rect);

  void free_recbintree(RecBinTree* rbt);
