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
  "For Network :\n"
  "\t <filePath>\n"
  "\t\tif <filePath> contain a Neural Network : use it.\n"
  "\t\telse : create one, train it and then save it.\n";

int main(int argc, char *argv[]) {
  //neural Network
  if(argc == 2){
    //give a filePath, if it does not contain one neuralNetwork : create one
    char *filePath = argv[1];
    Network net = openNr(filePath);
    if (net.len == -1) //no previously saved network fail :/
    {
      int len = 3;// set number of layers
      int nbPixels = 900; // set number of input neurons
      int type = 2; //see setNetwork funct to see why


      net = makeNetWork(len, setNetwork(type, nbPixels)); //create network
      printf("Created network :\n");
      printNetwork(net);
      //improving it :

      //storing it:
      printf("Improved Network :\n");
      printNetwork(net);
      saveNr(net, filePath);
      printf("Network saved.\n");
      freeNetwork(net);
    }
    printf("This network was already stored :\n");
    printNetwork(net);
  }
  if(argc != 3)
    errx(1, "%s", usage);
  unsigned op = strtoul(argv[2], NULL, 10);
  if(op == 0 || op > 6)
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
    UnsignedMatrix *mattexte = eraseimage(mat,10000);
    surf = unsignedMatrix_to_pict(mattexte, 1);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
  }
  SDL_FreeSurface(surf);
  SDL_FreeSurface(img);
  free_unsigned_matrix(mat);
  return 0;
}
