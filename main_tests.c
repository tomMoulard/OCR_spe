# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>

# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>


# include "types/pixel.h"
# include "image_op/binarize.h"
# include "matrix_op/rlsa.h"
# include "SDL/pixel_operations.h"
# include "matrix_op/rectangle.h"
//# include "matrix_op/matrix_op.h"
# include "types/matrix.h"

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
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
 printf("\n");
}

int main(void) {
  SDL_Surface *img = load_image("SDL/test.bmp");
  size_t w = 1024;
  size_t h = 768;


  int coefh = 700;
  int coefv = 200;
  UnsignedMatrix *mat = frompictomatbin(img,w,h);
  UnsignedMatrix *math = horizontal(mat,coefh);
  img = frommatbintopict(math);
  display_image(img);
  UnsignedMatrix *matv = vertical(mat,coefv);
  img = frommatbintopict(matv);
  display_image(img);
  UnsignedMatrix *matrlsa = rlsa(mat,coefh,coefv);
  img = frommatbintopict(matrlsa);
  display_image(img);
  /*
  size_t len = 0;

  displayrect(mat,4,5);
  img = frommatbintopict(mat);
  display_image(img);

  UnsignedMatrix **matmat = getrect(mat,4,5,&len);
  for (size_t i = 0; i < len / 10; i++) {
      img = frommatbintopict(matmat[i]);
      display_image(img);
  }
  */

/*
img = frommatbintopict(rlsa(mat,w,h,1000,1000),w,h);
display_image(img);
*/

  free_unsigned_matrix(mat);
  //free(matest);


return 0;
}
