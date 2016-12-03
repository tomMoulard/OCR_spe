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
# include "image_op/rotation.h"

//neural NetWork
# include "NeuralNetWork/nr.h"

const char usage[] =
  "<image path> <op>\n"
  "Take only a bmp image\n"
  "\tOperators :\n"
  "\t\t1 : Just binarization\n"
  "\t\t2 : Show letters\n"
  "\t\t3 : XY-cut\n"
  "\t\t4 : Run Length Smoothing\n"
  "\t\t5 : Related component\n"
  "\t\t6 : Erase image (with experimental value)\n"
  "\t\t7 : tests\n"
  "For Network :\n"
  "\t <filePath>\n"
  "\t\tif <filePath> contain a Neural Network : use it.\n"
  "\t\telse : create one, train it and then save it.\n";;;

UnsignedMatrix **from_img_to_letters(char *filepath,size_t *len){
  size_t lines = bmpWidth(filepath);
  size_t cols = bmpHeight(filepath);
  SDL_Surface *surf;
  init_sdl();
  SDL_Surface *img;
  PixelMatrix *image = new_pixel_matrix(lines, cols);
  //printf("Display image : %s\n", filepath);
  surf = load_image(filepath);
  img = display_image(surf);
  save_image(img, image);
  UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
  binarize(image, mat);
  free_pixel_matrix(image);

  UnsignedMatrix *matrix = copy_mat(mat);

  MatBinTree *mbt = new_matbintree(matrix);
  xycut_test(mbt,1,1,10);
  UnsignedMatrix **mats = get_letters(mbt,len);

  free_matbintree(mbt);
  SDL_FreeSurface(img);
  SDL_FreeSurface(surf);
  free_unsigned_matrix(mat);
  return mats;
}

int main(int argc, char *argv[]) {
  //neural Network
  if(argc == 2){
    //give a filePath, if it does not contain one neuralNetwork : create one
    char *filePath = argv[1];
    size_t len =0;
    UnsignedMatrix **mats = from_img_to_letters(filePath,&len);
    Bashint *input = malloc(sizeof(Bashint) * len);
    for(size_t i = 0; i < len; ++i){
      input[i] = unsignedmatToBashint(mats[i]);
    }
    char *res = "";
    for(size_t i = 0; i < len; ++i){
      printf("i : %zu\n",i);
      mainNetwork(res, argc, &input[i], 1, 1);
    }
    printf("%s\n", res);
    free(mats);
    return 0;

  }
  if(argc != 3)
    errx(1, "%s", usage);
  unsigned op = strtoul(argv[2], NULL, 10);
  if(op == 0 || op > 7)
    errx(1, "%s", usage);
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
  //mat = rotation(mat, 90);
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
  if(op == 6){
    UnsignedMatrix *mattexte = eraseimage(mat);
    surf = unsignedMatrix_to_pict(mattexte, 1);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
  }

  if (op == 7) {
    UnsignedMatrix *matrix = copy_mat(mat);
    //UnsignedMatrix *matrix = eraseimage(mat);
    surf = unsignedMatrix_to_pict(matrix, 1);
    img = display_image(surf);

    MatBinTree *mbt = new_matbintree(matrix);

    xycut_test(mbt,1,1,10);
    //mbt_print(mbt,0);

    surf = unsignedMatrix_to_pict(matrix, 0xffffffff);
    img = display_image(surf);
    size_t len = 0;
    UnsignedMatrix **mats = get_letters(mbt,&len);

    for (size_t i = 0; i < len; i++) {
      surf = unsignedMatrix_to_pict(mats[i], 0xffffffff);
      img = display_image(surf);
    }

    for (size_t i = 0; i < len; i++) {
      free_unsigned_matrix(mats[i]);
    }


    free(mats);

    //free_unsigned_matrix(matrix);
    free_matbintree(mbt);

    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
  }
}
