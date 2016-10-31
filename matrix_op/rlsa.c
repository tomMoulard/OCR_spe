# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "rlsa.h"
# include "../types/matrix.h"
# include "../types/rectangle.h"

int isokh(UnsignedMatrix *mat, size_t pos, int coef){
  size_t max = mat->lines * mat->cols;
  while (pos < max && mat->data[pos] == 0 && coef > 0) {
    coef--;
    pos += mat->cols;
  }
  if(mat->data[pos] == 1){
    return 1;
  }
  else{
    return 0;
  }
  return 0;
}

UnsignedMatrix* horizontal(UnsignedMatrix *matrix, int coef){

  UnsignedMatrix *mat = copy_mat(matrix);
  int isblack;

  for (size_t j = 0; j < mat->cols; j++) {
    isblack = 0;
    for (size_t i = 0; i < mat->lines; i++) {

      if (matrix->data[i * matrix->cols + j] == 1) {
        isblack = isokh(matrix,(i + 1) * matrix->cols + j,coef);
        mat->data[i * mat->cols + j] = 1;
      }
      else{
        if (isblack > 0) {
          mat->data[i * mat->cols + j] = 1;
        }
      }
    }
  }
  return mat;
}


int isokv(UnsignedMatrix *mat, size_t pos, int coef){
  size_t max = ((pos / mat->cols) + 1) * mat->cols;
  while (pos < max && mat->data[pos] == 0 && coef > 0) {
    coef--;
    pos++;
  }
  if(pos >= max || mat->data[pos] == 1){
    return 1;
  }
  else{
    return 0;
  }
  return 0;
}

UnsignedMatrix* vertical(UnsignedMatrix *matrix, int coef){

  UnsignedMatrix *mat = copy_mat(matrix);

  int isblack;

  for (size_t i = 0; i < mat->lines; i++) {
  isblack = 0;
  for (size_t j = 0; j < mat->cols; j++) {
      if (matrix->data[i * matrix->cols + j] == 1) {
        isblack = isokv(matrix,i * matrix->cols + j + 1,coef);
        mat->data[i * mat->cols + j] = 1;
      }
      else{
        if (isblack > 0) {
          mat->data[i * mat->cols + j] = 1;
        }
      }
    }
  }
  return mat;
}

  UnsignedMatrix* rlsa(UnsignedMatrix *matrix,int coefh,int coefv){
  UnsignedMatrix *math = horizontal(matrix,coefh);
  UnsignedMatrix *matv = vertical(matrix,coefv);
  UnsignedMatrix *mat = new_unsigned_matrix(matrix->lines,matrix->cols);

  size_t x = mat->lines;
  size_t y = mat->cols;
  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {
      if (math->data[i * y + j] && matv->data[i * y + j]) {
        mat->data[i * y + j] = math->data[i * y + j];
      }
      else{
        mat->data[i * y + j] = 0;
      }
    }
  }

  free_unsigned_matrix(math);
  free_unsigned_matrix(matv);
  return mat;

}

unsigned value_pix(unsigned *data,size_t len){
  unsigned min = data[0];

  for (size_t i = 0; i < len; i++) {
    if (data[i] > 1) {
        min = min < data[i]?min:data[i];
    }
  }
  return min;
}

void eight_connexe_forth(UnsignedMatrix *mat,size_t x,size_t y,int *isok){
  unsigned data[5];
  data[0] = mat->data[x * mat->cols + y];
  data[1] = x > 0 ? mat->data[(x - 1) * mat->cols +y]:0;
  data[2] = y > 0 ? mat->data[x * mat->cols + y -1]:0;
  data[3] = (x > 0) && (y > 0)?mat->data[(x - 1) * mat->cols + y - 1]:0;
  data[4] = (x < mat->lines)&&(y > 0)?mat->data[(x + 1) * mat->cols+y-1]:0;

  unsigned temp = value_pix(data,5);
  if (temp == data[0]) {
    *isok = *isok || 0;
  }
  else{
    mat->data[x * mat->cols + y] = temp;
    *isok = 1;
  }

 }


void eight_connexe_back(UnsignedMatrix *mat,size_t x,size_t y,int *isok){
  unsigned data[5];

  data[0] = mat->data[x * mat->cols + y];
  data[1] = x < mat->lines?mat->data[(x + 1) * mat->cols +y]:0;
  data[2] = y < mat->cols?mat->data[x * mat->cols + y + 1]:0;
  data[3]=(x < mat->cols)&&(y < mat->cols)?mat->data[(x+1)* mat->cols+y+1]:0;
  data[4] = (x > 0)&&(y < mat->cols)?mat->data[(x - 1) * mat->cols+y+1]:0;


  unsigned temp = value_pix(data,5);
  if (temp == data[0]) {
    *isok = *isok || 0;
  }
  else{
    mat->data[x * mat->cols + y] = temp;
    *isok = 1;
  }
}


UnsignedMatrix* ecc(UnsignedMatrix *matrix,unsigned *coef){
 *coef = 2;
 int isok = 1;
 UnsignedMatrix *mat = copy_mat(matrix);

  for (size_t j = 0; j < mat->cols; j++) {
    for (size_t i = 0; i < mat->lines; i++) {

      if (mat->data[i * mat->cols +j] > 0){
        mat->data[i * mat->cols +j] = *coef;
        eight_connexe_forth(mat,i,j,&isok);
      if (isok) {
          (*coef)++;
       }
     }
   }
 }
 while(isok){
   *coef = 0;
   isok = 0;
   for (size_t j = 0; j < mat->cols; j++) {
     for (size_t i = 0; i < mat->lines; i++) {
       if (mat->data[i * mat->cols +j] > 0){
         eight_connexe_forth(mat,i,j,&isok);
         if (mat->data[i * mat->cols +j] > *coef) {
           *coef = mat->data[i * mat->cols +j] ;
         }
      }
    }
  }
  for (size_t j = mat->cols; j > 0; j--) {
    for (size_t i = mat->lines; i > 0; i--) {
      if (mat->data[i * mat->cols +j] > 0) {
        eight_connexe_back(mat,i,j,&isok);
      }
      if (mat->data[i * mat->cols +j] > *coef) {
        *coef = mat->data[i * mat->cols +j] ;
      }
    }
  }
}

  *coef = 0;
for (size_t j = 0; j < mat->cols; j++) {
  for (size_t i = 0; i < mat->lines; i++) {
      if (mat->data[i * mat->cols +j] > *coef) {
        *coef = mat->data[i * mat->cols +j] ;

   }
 }
}
  return mat;
}

unsigned* get_all_areas(UnsignedMatrix *mat,size_t len){
  unsigned *values = malloc(len * sizeof(unsigned));
  for (size_t i = 0; i < len; i++) {
    values[i] = 0;
  }
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      values[mat->data[i * mat->cols +j]]++;
    }
  }
  return values;
}

Rect* get_all_rects(UnsignedMatrix *mat,unsigned *values,size_t len){
  Rect* rects = malloc(len * sizeof(Rect));
  for (size_t i = 0; i < len; i++) {
    rects[i].a1.x = mat->lines;
    rects[i].a2.x = 0;
    rects[i].a1.y = mat->cols;
    rects[i].a2.y = 0;
  }
  unsigned n;

  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
        n = mat->data[i * mat->cols + j];
        rects[n].a1.x = rects[n].a1.x  < i?rects[n].a1.x :i;
        rects[n].a2.x = rects[n].a2.x  > i?rects[n].a2.x :i;
        rects[n].a1.y = rects[n].a1.y < j?rects[n].a1.y:j;
        rects[n].a2.y = rects[n].a2.y > j?rects[n].a2.y:j;

    }
  }
  free(values);
  return rects;
}

unsigned* original_black(UnsignedMatrix *mat,
  UnsignedMatrix *matecc,Rect* rects, size_t len){
  unsigned *values = malloc(len * sizeof(unsigned));

  for (size_t n = 0; n < len; n++) {
    for (size_t i = rects[n].a1.x; i < rects[n].a2.x; i++) {
      for (size_t j = rects[n].a1.y; j < rects[n].a2.y; j++) {
        values[matecc->data[i * mat->cols + j]] += mat->data[i * mat->cols+j];
      }
    }
  }
  return values;
}

void eraserect(UnsignedMatrix *mat,Rect rect)
{
  for (size_t i = rect.a1.x; i < rect.a2.x; i++) {
    for (size_t j = rect.a1.y; j < rect.a2.y; j++) {
      mat->data[i * mat->cols + j] = 0;
    }
  }
}
void get_items_height(UnsignedMatrix* mat,unsigned coef,
  size_t thval1,size_t thval2){


  Coordinates coord[coef];
  for (size_t i = 0; i < coef; i++) {
    coord[i].x = 5000;
    coord[i].y = 0;
  }

  unsigned curpix;
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      curpix = mat->data[i * mat->cols + j];
      if (j < coord[curpix].x) {
        coord[curpix].x = j;
      }
      if (j > coord[curpix].y) {
        coord[curpix].y = j;
      }
    }
  }

  size_t *heights = malloc(coef * sizeof(size_t));
  for (size_t i = 0; i < coef; i++) {
    heights[i] = coord[i].y - coord[i].x;
  }
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      curpix = mat->data[i * mat->cols + j];
      if (curpix != 0) {

      if (heights[curpix] < thval1) {
        mat->data[i * mat->cols + j] = 1;
      }
      else{
        if (heights[curpix] >= thval2) {
          mat->data[i * mat->cols + j] = 3;
        }
        else{
          mat->data[i * mat->cols + j] = 2;
        }
     }
   }
   }
 }
 free(heights);
}

UnsignedMatrix* eraseimage(UnsignedMatrix *matrix,unsigned maxpixel){


  int coefh = 200;
  int coefv = 200;

  UnsignedMatrix *mat = copy_mat(matrix);
  unsigned coef = 0;
  UnsignedMatrix* matrlsa = rlsa(mat,coefh,coefv);
  UnsignedMatrix* matecc = ecc(matrlsa,&coef);

  unsigned* areas = get_all_areas(matecc,coef);
  Rect* rects = get_all_rects(matecc,areas,coef);
  //unsigned* origin = original_black(mat,matecc,rects,coef);



  for (size_t i = 2; i < coef; i++) {
    if(areas[i] > maxpixel){
      eraserect(mat,rects[i]);
    }
  }



  //free(areas);
  free(rects);
  free_unsigned_matrix(matrlsa);
  free_unsigned_matrix(matecc);

  return mat;
}
