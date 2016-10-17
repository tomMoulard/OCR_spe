# include <stdlib.h>
# include <SDL.h>

typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}Pixel;

Pixel *new_pixel(Uint8 r, Uint8 g, Uint8 b)
{
    Pixel *pixel = malloc(sizeof(Pixel));
    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
    return pixel;
}

Unint8 rgb_average(Pixel pixel)
{
    Uint8 average = (pixel.r + pixel.g + pixel.b) / 3;
    retrun average;
}
