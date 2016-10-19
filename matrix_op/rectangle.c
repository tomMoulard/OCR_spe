# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rectangle.h"
# include "cut.h"



void printrect(Rect rect){
  printf("x1 : %zu y1 : %zu x2 : %zu : y2 : %zu\n", rect.a1.x,rect.a1.y,rect.a2.x,rect.a2.y);

}

Coordinates neighbor(unsigned **matrix,
              size_t x,size_t y, size_t posx,size_t posy,size_t coef){


Coordinates coord;

size_t maxx = (posx + coef < x)? posx + coef: x;
size_t maxy = (posy + coef < y)? posy + coef: y;
size_t minx = (posx > coef)? posx - coef: 0;
size_t miny = (posy > coef)? posy - coef: 0;


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
              size_t x,size_t y, size_t posx,size_t posy,size_t coef){


matrix[posx][posy] = 0;
Coordinates coord;
size_t i,j;

Rect rect;
rect.a1.x = posx;
rect.a1.y = posy;
rect.a2.x = posx;
rect.a2.y = posy;
Rect rect2;
coord = neighbor(matrix,x,y,posx,posy,coef);
while(coord.x != 0 || coord.y != 0) {


  i = coord.x;
  j = coord.y;
  matrix[i][j] = 0;


  rect2 = posrect(matrix,x,y,i,j,coef);
  //printrect(rect2);
  rect.a1.x = (rect.a1.x > rect2.a1.x)?rect.a1.x:rect2.a1.x;
  rect.a1.y = (rect.a1.y > rect2.a1.y)?rect.a1.y:rect2.a1.y;
  rect.a2.x = (rect.a2.x < rect2.a2.x)?rect.a2.x:rect2.a2.x;
  rect.a2.y = (rect.a2.y < rect2.a2.y)?rect.a2.y:rect2.a2.y;


  coord = neighbor(matrix,x,y,posx,posy,coef);
}
return rect;
}


Rect* allrect(unsigned **matrix,
              size_t x,size_t y, size_t coef,size_t len,size_t *max){

Rect *rects = malloc(sizeof(Rect) * len);
  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {

      if (matrix[i][j] == 1) {
        rects[*max] = posrect(matrix,x,y,i,j,coef);
        (*max)++;
      }
    }
  }

return rects;
}

void displayrect(unsigned **matrix,size_t x,size_t y,size_t coef)
{
  size_t max = 0;
  size_t len = 10000;

  unsigned **mat = copy_mat(matrix,x,y);
  Rect *rect;
  rect = allrect(mat,x,y,coef,len,&max);



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

free(rect);


}
