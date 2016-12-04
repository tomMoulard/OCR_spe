# ifndef SDL_FCT_H_
# define SDL_FCT_H_

# include <stdlib.h>
# include <err.h>

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "../types/pixel.h"
# include "../types/matrix.h"

void init_sdl(void);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void save_image(SDL_Surface *img, PixelMatrix *image);
void save_bin(SDL_Surface *img, UnsignedMatrix *image);
SDL_Surface* unsignedMatrix_to_pict(UnsignedMatrix *mat, unsigned coef);

# endif
