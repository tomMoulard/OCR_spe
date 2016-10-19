# ifndef PIXEL_H_
# define PIXEL_H_

# include <stdlib.h>
# include <SDL/SDL.h>

typedef struct _Pixel{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}Pixel;

Pixel new_pixel(Uint8 r, Uint8 g, Uint8 b);
Pixel **new_pixel_matrix(int dimx, int dimy);
void free_pixel_matrix(Pixel **mat, int dmx);//, int dmy);

# endif
