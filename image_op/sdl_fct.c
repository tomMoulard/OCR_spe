# include "sdl_fct.h"

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

SDL_Surface* unsignedMatrix_to_pict(UnsignedMatrix *mat, unsigned coef){
  Uint32 white = 0x00000000;
  Uint32 black = 0xffffffff;
  Uint32 color = 0xffffffff / coef;
  SDL_Surface *pict = SDL_CreateRGBSurface(0,mat->lines,mat->cols,32,0,0,0,0);
  for (size_t i = 0; i < mat->lines; i++)
    for (size_t j = 0; j < mat->cols; j++)
    {
      if (mat->data[i * mat->cols + j] == 1)
        putpixel(pict,i,j,white);
      else
      {
        if (mat->data[i * mat->cols + j] == 0)
          putpixel(pict,i,j,black);
        else
          putpixel(pict,i,j,color * mat->data[i * mat->cols + j]);
      }
    }
  return pict;
}

void save_image(SDL_Surface *img, PixelMatrix *image)
{
    Uint8 r, g, b;
    Uint32 pixel;
    for(size_t i = 0; i < image->lines; i++)
        for(size_t j = 0; j < image->cols; j++)
        {
            pixel = getpixel(img, i, j);
            r = (pixel & 0x0000ff00) >> 8;
            g = (pixel & 0x00ff0000) >> 16;
            b = (pixel & 0xff000000) >> 24;
            image->data[i * image->cols + j] = new_pixel(r, g, b);
        }
}
