# include "pixel.h"

typedef struct _Pixel{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}Pixel;

Pixel *new_pixel(Uint8 r, Uint8 g, Uint8 b){
    Pixel *pixel = malloc(sizeof(Pixel));
    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
    return pixel;
}

Pixel **new_pixel_matrix(int dimx, int dimy){ 
    Pixel **mat = calloc(dimx, sizeof(Pixel[dimy]));
    for(int i =0; i < dimx; i++)
        mat[i] = calloc(dimy, sizeof(Pixel));
    return mat;
}

Uint8 rgb_average(Pixel *pixel){
    Uint8 average = (pixel->r + pixel->g + pixel->b) / 3;
    return average;
}
