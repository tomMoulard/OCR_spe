# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>
# include <err.h>

# include "types/pixel.h"
# include "image_op/binarize.h"
# include "matrix_op/rlsa.h"
# include "types/rectangle.h"
# include "types/matrix.h"
# include "types/matbintree.h"
# include "matrix_op/xycut.h"
# include "image_op/sdl_fct.h"



int main(void) {

  SDL_Surface *surf;
  SDL_Surface *img;
  size_t lines = 1024;
  size_t cols = 768;
  PixelMatrix *image = new_pixel_matrix(lines, cols);
  init_sdl();
  printf("Display image : %s\n", "images/test.bmp");
  surf = load_image("images/test.bmp");
  img = display_image(surf);
  save_image(img, image);
  UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
  binarize(image, mat);

  MatBinTree *mbt = new_matbintree(mat);
  mbt->pos = new_rect(0,0,mat->lines,mat->cols);
  xycut(mbt,1,1,0);

  //mbt_print(mbt,0);

  int coef = get_all_rect(mbt,mat,0);
  printf("ok\n");


  surf = unsignedMatrix_to_pict(mat, coef);
  img = display_image(surf);
  //UnsignedMatrix* matrix = cut(mat,0,1126,500,1570);


  //UnsignedMatrix* matecc = ecc(matrix,&coef);

  free_matbintree(mbt);
  SDL_FreeSurface(surf);
  SDL_FreeSurface(img);
  //free_unsigned_matrix(mat);
  free_pixel_matrix(image);

  return 0;

}
