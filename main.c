# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>
# include <err.h>

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "types/pixel.h"
# include "types/matrix.h"
# include "image_op/binarize.h"

void wait_for_keypressed(void) {
  SDL_Event             event;
  for (;;) {
    SDL_PollEvent( &event );
    switch (event.type) {
    case SDL_KEYDOWN: return;
    default: break;
    }
  }
}

void init_sdl(void) {
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  wait_for_keypressed();
  return screen;
}

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}

SDL_Surface* frommatbintopict(UnsignedMatrix *mat){
  Uint32 white = 0x00000000;
  Uint32 black = 0xffffffff;
  Uint32 yolo = 0xffff0000;
  SDL_Surface *pict = SDL_CreateRGBSurface(0,mat->lines,mat->cols,32,0,0,0,0);
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      if (mat->data[i * mat->cols + j] == 1) {
        putpixel(pict,i,j,white);
      }
      else{
        if (mat->data[i * mat->cols + j] == 2) {
          putpixel(pict,i,j,yolo);
        }
        else{
          putpixel(pict,i,j,black);
        }

      }
    }
  }
  return pict;
}

void save_image(SDL_Surface *img, Pixel **image, int dimx, int dimy)
{
    Uint8 r, g, b;
    Uint32 pixel;
    for(int i = 0; i < dimx; i++)
        for(int j = 0; j < dimy; j++)
        {
            pixel = getpixel(img, i, j);
            r = (pixel & 0x0000ff00) >> 8;
            g = (pixel & 0x00ff0000) >> 16;
            b = (pixel & 0xff000000) >> 24;
            image[i][j] = new_pixel(r, g, b);
        }
}

int main() 
{
    SDL_Surface *surf;
    SDL_Surface *img;
    int dimx = 1024;
    int dimy = 768;
    size_t lines = 1024;
    size_t cols = 768;
    Pixel **image = new_pixel_matrix(dimx, dimy);
    init_sdl();
    printf("Display image : %s\n", "test.jpg");
    surf = load_image("test.bmp");
    img = display_image(surf);
    save_image(img, image, dimx, dimy);
    UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
    binarize(image, mat, dimx, dimy);
    surf = frommatbintopict(mat);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
}
