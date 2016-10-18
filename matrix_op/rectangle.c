# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rectangle.h"


void neighborhood(unsigned **matrix,
              size_t x,size_t y, size_t posx,size_t posy,size_t coef,
              size_t *coord,size_t *len){

size_t maxx = (posx + coef < x)? posx + coef: x;
size_t maxy = (posy + coef < y)? posy + coef: y;
size_t minx = (posx - coef > 0)? posx - coef: 0;
size_t miny = (posy - coef > 0)? posy - coef: 0;

for (size_t i = minx; i < maxx; i++) {
  for (size_t j = miny; j < maxy; j++) {
    if (matrix[i][j] == 1) {
      coord[*len] = i;
      (*len)++;
      coord[*len] = j;
      (*len)++;
      }
    }
  }
}

Rect posrect(unsigned **matrix,
              size_t x,size_t y, size_t posx,size_t posy,size_t coef){

Rect rect;
rect.x1 = x;
rect.y1 = y;
rect.x2 = x;
rect.y2 = y;

Rect rect2;
size_t *coord = malloc(sizeof(size_t));
size_t len = 0;
neighborhood(matrix,x,y,posx,posy,coef,coord,&len);

while (len != 0) {
  matrix[coord[0]][coord[1]] = 0;
  rect2 = posrect(matrix,x,y,coord[0],coord[1],coef);
  rect.x1 = (rect.x1 > rect2.x1)?rect.x1:rect2.x1;
  rect.y1 = (rect.y1 > rect2.y1)?rect.y1:rect2.y1;
  rect.x2 = (rect.x2 < rect2.x2)?rect.x2:rect2.x2;
  rect.y2 = (rect.y2 < rect2.y2)?rect.y2:rect2.y2;
  neighborhood(matrix,x,y,posx,posy,coef,coord,&len);
}
return rect;

}

Rect* allrect(unsigned **matrix,
              size_t x,size_t y, size_t coef,size_t *len){

Rect *pos = malloc(sizeof(Rect));


  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {
      if (matrix[i][j] == 1) {
        pos[*len] = posrect(matrix,x,y,i,j,coef);
        (*len)++;
      }
    }
  }
return pos;
}
