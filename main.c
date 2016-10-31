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
  "\t\t2 : Show letters\n"
  "\t\t3 : XY-cut\n"
  "\t\t4 : Run Length Smoothing"
  "\t\t5 : Related component\n"
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
  if(op == 2)
  {
    UnsignedMatrix* matrix = copy_mat(mat);
    size_t len = 0;
    Rect* rects = allrect(matrix,4,5,10000,&len);
    displayrects(mat,rects,len,255);
    surf = unsignedMatrix_to_pict(mat, 0xffffffff);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(matrix);
    free_unsigned_matrix(mat);
    return 0;
  }
  if(op == 3)
  {
    UnsignedMatrix* matrix = cut(mat,0,1024,0,95);
    surf = unsignedMatrix_to_pict(matrix, 5);
    img = display_image(surf);

    MatBinTree *mbt = new_matbintree(matrix);
    xycut(mbt,1,1,0);
    //get_all_rect(mbt,matrix,0);
    surf = unsignedMatrix_to_pict(matrix, 0xffffffff);
    img = display_image(surf);

    display_leaves(mbt);
    free_matbintree(mbt);

    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);

    return 0;

  }
  if(op == 4)
  {
    UnsignedMatrix *math = horizontal(mat,200);
    UnsignedMatrix *matv = vertical(mat,200);
    UnsignedMatrix *matrlsa = rlsa(mat,200,200);

    surf = unsignedMatrix_to_pict(math, 1);
    img = display_image(surf);
    surf = unsignedMatrix_to_pict(matv, 1);
    img = display_image(surf);
    surf = unsignedMatrix_to_pict(matrlsa, 1);
    img = display_image(surf);

    free_unsigned_matrix(math);
    free_unsigned_matrix(matv);
    free_unsigned_matrix(matrlsa);

    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);

    return 0;
  }
  if(op == 5)
  {
    UnsignedMatrix *matrlsa = rlsa(mat,200,200);
    unsigned coef = 0;
    UnsignedMatrix *matecc = ecc(matrlsa,&coef);

    surf = unsignedMatrix_to_pict(matrlsa, 1);
    img = display_image(surf);
    surf = unsignedMatrix_to_pict(matecc, coef);
    img = display_image(surf);

    free_unsigned_matrix(matrlsa);
    free_unsigned_matrix(matecc);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);

    return 0;
  }
  //UnsignedMatrix* matrix = cut(mat,0,1126,500,1570);


  //UnsignedMatrix* matecc = ecc(matrix,&coef);

  SDL_FreeSurface(surf);
  SDL_FreeSurface(img);
  free_unsigned_matrix(mat);
  free_pixel_matrix(image);

  return 0;

}
