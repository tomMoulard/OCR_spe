# define _XOPEN_SOURCE 500

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "split.h"

# define MAXVAL 100
# define STEP 10


void array_random_fill(unsigned array[], size_t len)
{
  for (size_t i = 0; i < len; ++i){
    array[i] = random() % 2;
  }
}

void array_print(unsigned array[], size_t len)
{
  int line = 0;
  for (size_t i = 0; i < len; ++i) {
    if (line > 72) {
      printf("|`|\n");
      line = 0;
    }
    line += printf("| %4d ", array[i]);
  }
  printf("|\n");
}

void matrix_print(unsigned **matrix, size_t x,size_t y)
{

 for (size_t i = 0; i < x; ++i) {
   array_print(matrix[i], y);
 }
 printf("|\n");
}

/*
 * main
 */

int main()
{

  srandom(time(NULL));

  size_t x = 10;
  size_t y = 10;
  unsigned **matrix = calloc(x,sizeof(unsigned[y]));
  for (size_t i = 0; i < x; i++) {
    *(matrix + i) = calloc(y,sizeof(unsigned));
    array_random_fill(*(matrix + i),y);
  }
  matrix_print(matrix,x,y);

  struct Matrix_double mats;
  mats =  split_x(matrix , x, y, 5);


  struct Triplet mat1 = mats.matrix1;
  struct Triplet mat2 = mats.matrix2;

  printf("%zu\n", mat1.x);
  printf("%zu\n", mat1.y);
  matrix_print(mat1.matrix,mat1.x -1,mat1.y -1);
  matrix_print(mat2.matrix,mat2.x -1,mat2.y -1);


  //free(array);
  return 0;

}
