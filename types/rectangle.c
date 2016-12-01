# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rectangle.h"
# include "../types/matrix.h"

Coordinates new_coords(size_t x,size_t y){
  Coordinates coord;
  coord.x = x;
  coord.y = y;
  return coord;
}

Rect new_rect(size_t x1,size_t y1,size_t x2,size_t y2){
  Rect rect;
  rect.a1 = new_coords(x1,y1);
  rect.a2 = new_coords(x2,y2);
  return rect;

}

Coordinates neighbor(UnsignedMatrix *matrix, size_t posx,size_t posy,
              size_t coefh,size_t coefv){


Coordinates coord;

size_t maxx = (posx + coefh < matrix->lines)? posx + coefh: matrix->lines;
size_t maxy = (posy + coefv < matrix->cols)? posy + coefv: matrix->cols;
size_t minx = (posx > coefh)? posx - coefh: 0;
size_t miny = (posy > coefv)? posy - coefv: 0;


  for (size_t i = minx; i < maxx; i++) {
    for (size_t j = miny; j < maxy; j++) {
      if (matrix->data[i * matrix->cols + j] == 1) {
        matrix->data[i *matrix->cols + j] = 0;
        coord.x = i;
        coord.y = j;
        return coord;
        }
    }
  }
return coord;

}

Rect posrect(UnsignedMatrix *matrix, size_t posx,size_t posy,
              size_t coefh, size_t coefv){


matrix->data[posx * matrix->cols + posy] = 0;
Coordinates coord;
size_t i,j;

Rect rect;
rect.a1.x = posx;
rect.a1.y = posy;
rect.a2.x = posx;
rect.a2.y = posy;
Rect rect2;
coord = neighbor(matrix,posx,posy,coefh,coefv);
while(coord.x != 0 || coord.y != 0) {


  i = coord.x;
  j = coord.y;
  matrix->data[i * matrix->cols + j] = 0;


  rect2 = posrect(matrix,i,j,coefh,coefv);
  //printrect(rect2);
  rect.a1.x = (rect.a1.x < rect2.a1.x)?rect.a1.x:rect2.a1.x;
  rect.a1.y = (rect.a1.y < rect2.a1.y)?rect.a1.y:rect2.a1.y;
  rect.a2.x = (rect.a2.x > rect2.a2.x)?rect.a2.x:rect2.a2.x;
  rect.a2.y = (rect.a2.y > rect2.a2.y)?rect.a2.y:rect2.a2.y;

  coord = neighbor(matrix,posx,posy,coefh,coefv);
}

return rect;
}


Rect* allrect(UnsignedMatrix *matrix, size_t coefh,size_t coefv
              ,size_t len,size_t *max){

Rect *rects = malloc(sizeof(Rect) * len);
  for (size_t i = 0; i < matrix->lines; i++) {
    for (size_t j = 0; j < matrix->cols; j++) {

      if (matrix->data[i * matrix->cols + j] == 1) {

        rects[*max] = posrect(matrix,i,j,coefh,coefv);

        rects[*max].a2.x++;
        rects[*max].a2.y++;
        (*max)++;
      }
    }
  }

return rects;
}

void displayrect(UnsignedMatrix *matrix,Rect currect, unsigned col){
  for (size_t i = currect.a1.x; i < currect.a2.x; i++) {
    matrix->data[i * matrix->cols + currect.a2.y] = col;
    matrix->data[i * matrix->cols + currect.a1.y] = col;

  }
  for (size_t i = currect.a1.y; i < currect.a2.y; i++) {
    matrix->data[currect.a2.x * matrix->cols + i] = col;
    matrix->data[currect.a1.x * matrix->cols + i] = col;

  }
}

void displayrects(UnsignedMatrix *matrix,Rect* rect,size_t max,unsigned col)
{
  for (size_t n = 0; n < max; n++) {
    displayrect(matrix,rect[n],col);

  }

  size_t maxl = 0;
  size_t maxL = 0;
  for (size_t i = 0; i < max; i++) {
    Rect cur = rect[i];
    maxl = (maxl > cur.a1.x - cur.a2.x)?maxl:cur.a1.x - cur.a2.x;
    maxL = (maxL > cur.a1.y - cur.a2.y)?maxL:cur.a1.y - cur.a2.y;
  }

free(rect);
}


UnsignedMatrix** getrect(UnsignedMatrix *matrix,
  size_t coefh,size_t coefv,size_t *len){

    UnsignedMatrix *mat = copy_mat(matrix);
    Rect *rects = allrect(mat,coefh,coefv,10000,len);

    UnsignedMatrix** matmat = malloc(*len * sizeof(UnsignedMatrix));
    size_t x1,x2,y1,y2;
    for (size_t i = 0; i < *len; i++) {
      x1 = rects[i].a1.x;
      x2 = rects[i].a2.x;
      y1 = rects[i].a1.y;
      y2 = rects[i].a2.y;
      UnsignedMatrix *tempmat = cut(matrix,x1,x2,y1,y2);

      matmat[i] = expand_mat(tempmat,30,30);

      free_unsigned_matrix(tempmat);

    }


    free_unsigned_matrix(mat);
    free(rects);
    return matmat;
}
