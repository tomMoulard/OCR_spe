// pixel_operations.h

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_

# include <stdlib.h>

# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "../types/matrix.h"

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

UnsignedMatrix* frompictomatbin(SDL_Surface *surface,int x, int y);

SDL_Surface* frommatbintopict(UnsignedMatrix* mat);

SDL_Surface* frommattopict(UnsignedMatrix* mat,unsigned coef);

# endif
