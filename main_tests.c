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
  char path[] = "images/test.bmp";
  printf("Display image : %s\n", path);
  surf = load_image(path);
  img = display_image(surf);
  save_image(img, image);
  UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
  binarize(image, mat);


    surf = unsignedMatrix_to_pict(mat, 0xffffffff);
    img = display_image(surf);

  MatBinTree *mbt = new_matbintree(mat);
  mbt->pos = new_rect(0,0,mat->lines,mat->cols);
  //xycut(mbt,1,1,0,5);
  size_t len = 0;
  UnsignedMatrix* matrix = copy_mat(mat);
  Rect* rects = allrect(matrix,4,5,10000,&len);
  displayrects(mat,rects,len,255);

  //get_leaves(mbt,mat,0);

  surf = unsignedMatrix_to_pict(mat, 0xffffffff);
  img = display_image(surf);
  /*
  UnsignedMatrix* matrix = cut(mat,0,lines,500,1570);

  unsigned coef;


  UnsignedMatrix* matrlsa = rlsa(matrix,200,200);
  surf = unsignedMatrix_to_pict(matrlsa, 5);
  img = display_image(surf);

  UnsignedMatrix *matecc = ecc(matrlsa,&coef);
  surf = unsignedMatrix_to_pict(matecc, coef);
  img = display_image(surf);



  free_unsigned_matrix(matecc);
*/
  free_matbintree(mbt);
  SDL_FreeSurface(surf);
  SDL_FreeSurface(img);
  //free_unsigned_matrix(mat);
  free_pixel_matrix(image);

  return 0;

}
