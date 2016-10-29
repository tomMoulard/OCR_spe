# ifndef PIXEL_H_
# define PIXEL_H_

# include <stdlib.h>
# include <SDL/SDL.h>

typedef struct _Pixel{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}Pixel;

typedef struct _PixelMatrix{
    size_t lines;
    size_t cols;
    Pixel *data;
}PixelMatrix;

Pixel new_pixel(Uint8 r, Uint8 g, Uint8 b);
PixelMatrix *new_pixel_matrix(size_t lines, size_t cols);
void free_pixel_matrix(PixelMatrix *matrix);

# endif
