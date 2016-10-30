// pixel_operations.c

// Simple get/put pixel for SDL
// Inspired by code from SDL documentation
// (http://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html)

# include "pixel_operations.h"
# include "../types/matrix.h"

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
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

 UnsignedMatrix* frompictomatbin(SDL_Surface *surface,int x, int y){
  Uint8 r,g,b;
  Uint32 pixel;
  UnsignedMatrix *mat = new_unsigned_matrix(x,y);
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      pixel = getpixel(surface,i,j);
      r = (pixel & 0x0000ff00) >> 8;
      g = (pixel & 0x00ff0000) >> 16;
      b = (pixel & 0xff000000) >> 24;
      if ((r + g + b) / 3 < 127) {
        mat->data[i * y + j] = 1;
      }
      else{
        mat->data[i * y + j] = 0;
      }
    }
  }
  return mat;
}


SDL_Surface* frommatbintopict(UnsignedMatrix* mat){
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
        if (mat->data[i * mat->cols + j] == 0) {
          putpixel(pict,i,j,black);
        }
        else{
          putpixel(pict,i,j,yolo);
        }

      }
    }
  }
  return pict;
}

SDL_Surface* frommattopict(UnsignedMatrix* mat,unsigned coef){
  Uint32 white = 0x00000000;
  Uint32 black = 0xffffffff;
  Uint32 color = 0xffffffff / coef;

  SDL_Surface *pict = SDL_CreateRGBSurface(0,mat->lines,mat->cols,32,0,0,0,0);
  for (size_t i = 0; i < mat->lines; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      if (mat->data[i * mat->cols + j] == 1) {
        putpixel(pict,i,j,white);
      }
      else{
        if (mat->data[i * mat->cols + j] == 0) {
          putpixel(pict,i,j,black);
        }
        else{
          putpixel(pict,i,j,color * mat->data[i * mat->cols + j]);
      }
    }
   }
  }
  return pict;
}
