# ifndef PIXEL_H_
# define PIXEL_H_

# include <stdlib.h>
# include <SDL.h>

Pixel *new_pixel(Uint8 r, Uint8 g, Uint8 b);
Unint8 rgb_average(Pixel pixel);

# endif
