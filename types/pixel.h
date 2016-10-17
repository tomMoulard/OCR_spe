# ifndef PIXEL_H_
# define PIXEL_H_

# include <stdlib.h>
# include <SDL/SDL.h>

typedef struct _Pixel Pixel;
Pixel *new_pixel(Uint8 r, Uint8 g, Uint8 b);
Pixel **new_pixel_matrix(int dimx, int dimy);
Uint8 rgb_average(Pixel *pixel);

# endif
