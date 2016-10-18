// pixel_operations.h

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_

# include <stdlib.h>
# include <SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

unsigned** frompictomatbin(SDL_Surface *surface,int x, int y);
SDL_Surface* frommatbintopict(unsigned** mat,int x,int y);

# endif
