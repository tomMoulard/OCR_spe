# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>

# include <SDL/SDL.h>

//# include "types/pixel.h"
//# include "image_op/binarize.h"

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
 printf("\n");
}

int main(void) {
    return 0;
}
