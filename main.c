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
# include "images/database.h"

const char usage[] =
  "<image path> <op>\n"
  "Take only a bmp image\n"
  "\tOperators :\n"
  "\t\t1 : Just binarization\n"
  "\t\t2 : Display rectangles\n"
  "\t\t_ : all\n";



int main(int argc, char *argv[]) {
  if(argc != 3)
    errx(1, "%s", usage);
  unsigned op = strtoul(argv[2], NULL, 10);
  size_t lines = bmpWidth(argv[1]);
  size_t cols = bmpHeight(argv[1]);
  SDL_Surface *surf;
  init_sdl();
  SDL_Surface *img;
  PixelMatrix *image = new_pixel_matrix(lines, cols);
  printf("Display image : %s\n", argv[1]);
  surf = load_image(argv[1]);
  img = display_image(surf);
  save_image(img, image);
  UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
  binarize(image, mat);
  free_pixel_matrix(image);
  if(op == 1)
  {
    surf = unsignedMatrix_to_pict(mat, 1);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
  }
  MatBinTree *mbt = new_matbintree(mat);
  mbt->pos = new_rect(0,0,mat->lines,mat->cols);
  xycut(mbt,1,1,0);
  //mbt_print(mbt,0);
  int coef = get_all_rect(mbt,mat,0);
  if(op == 2)
  {
    surf = unsignedMatrix_to_pict(mat, coef);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
  }
  //UnsignedMatrix* matrix = cut(mat,0,1126,500,1570);


  //UnsignedMatrix* matecc = ecc(matrix,&coef);

  free_matbintree(mbt);
  SDL_FreeSurface(surf);
  SDL_FreeSurface(img);
  //free_unsigned_matrix(mat);
  free_pixel_matrix(image);

  return 0;

}
