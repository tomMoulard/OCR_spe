# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rectangle.h"
# include "matrix_op.h"


Coordinates neighbor(unsigned **matrix,
              size_t x,size_t y, size_t posx,size_t posy,
              size_t coefh,size_t coefv){


Coordinates coord;

size_t maxx = (posx + coefh < x)? posx + coefh: x;
size_t maxy = (posy + coefv < y)? posy + coefv: y;
size_t minx = (posx > coefh)? posx - coefh: 0;
size_t miny = (posy > coefv)? posy - coefv: 0;


  for (size_t i = minx; i < maxx; i++) {
    for (size_t j = miny; j < maxy; j++) {
      if (matrix[i][j] == 1) {
        matrix[i][j] = 0;
        coord.x = i;
        coord.y = j;
        return coord;
        }
    }
  }
return coord;

}

Rect posrect(unsigned **matrix,
              size_t x,size_t y, size_t posx,size_t posy,
              size_t coefh, size_t coefv){


matrix[posx][posy] = 0;
Coordinates coord;
size_t i,j;

Rect rect;
rect.a1.x = posx;
rect.a1.y = posy;
rect.a2.x = posx;
rect.a2.y = posy;
Rect rect2;
coord = neighbor(matrix,x,y,posx,posy,coefh,coefv);
while(coord.x != 0 || coord.y != 0) {


  i = coord.x;
  j = coord.y;
  matrix[i][j] = 0;


  rect2 = posrect(matrix,x,y,i,j,coefh,coefv);
  //printrect(rect2);
  rect.a1.x = (rect.a1.x > rect2.a1.x)?rect.a1.x:rect2.a1.x;
  rect.a1.y = (rect.a1.y > rect2.a1.y)?rect.a1.y:rect2.a1.y;
  rect.a2.x = (rect.a2.x < rect2.a2.x)?rect.a2.x:rect2.a2.x;
  rect.a2.y = (rect.a2.y < rect2.a2.y)?rect.a2.y:rect2.a2.y;


  coord = neighbor(matrix,x,y,posx,posy,coefh,coefv);
}

return rect;
}


Rect* allrect(unsigned **matrix,
              size_t x,size_t y, size_t coefh,size_t coefv
              ,size_t len,size_t *max){

Rect *rects = malloc(sizeof(Rect) * len);
  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {

      if (matrix[i][j] == 1) {
        rects[*max] = posrect(matrix,x,y,i,j,coefh,coefv);
        (*max)++;
      }
    }
  }

return rects;
}

void displayrect(unsigned **matrix,size_t x,size_t y,size_t coefh,size_t coefv)
{
  size_t max = 0;
  size_t len = 10000;

  unsigned **mat = copy_mat(matrix,x,y);
  Rect *rect;
  rect = allrect(mat,x,y,coefh,coefv,len,&max);



  for (size_t n = 0; n < max; n++) {
    Rect currect = rect[n];
    for (size_t i = currect.a2.x; i < currect.a1.x; i++) {
      matrix[i][currect.a1.y] = 2;
      matrix[i][currect.a2.y] = 2;

    }
    for (size_t i = currect.a2.y; i < currect.a1.y; i++) {
      matrix[currect.a1.x][i] = 2;
      matrix[currect.a2.x][i] = 2;

    }
  }

  size_t maxl = 0;
  size_t maxL = 0;
  for (size_t i = 0; i < max; i++) {
    Rect cur = rect[i];
    maxl = (maxl > cur.a1.x - cur.a2.x)?maxl:cur.a1.x - cur.a2.x;
    maxL = (maxl > cur.a1.y - cur.a2.y)?maxl:cur.a1.y - cur.a2.y;
  }
  printf("Maxl: %zu, MaxL: %zu\n",maxl,maxL);

free(rect);


}


unsigned ***getrect(unsigned **matrix,size_t x,size_t y,
  size_t coefh,size_t coefv,size_t *len){



    unsigned **mat = copy_mat(matrix,x,y);
    Rect *rects = allrect(mat,x,y,coefh,coefv,10000,len);

    unsigned ***matmat = calloc(*len,sizeof(unsigned[30][30]));
    size_t x1,x2,y1,y2;
    for (size_t i = 0; i < *len; i++) {
      x1 = rects[i].a1.x;
      x2 = rects[i].a2.x;
      y1 = rects[i].a1.y;
      y2 = rects[i].a2.y;
      unsigned **tempmat = cut(matrix,x2,x1,y2,y1);

      matmat[i] = expand_mat(tempmat,x1 - x2,y1 - y2,30,30);

      free(tempmat);

    }


    free(mat);
    free(rects);
    return matmat;
}
