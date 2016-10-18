# include "binarize.h"
# include "../types/pixel.h"

unsigned **binarize(Pixel **image, int dimx, int dimy)
{
    unsigned **mat = malloc(dimx * sizeof(unsigned*));
    for(int x = 0; x < dimx; x++)
    {
        mat[x] = malloc(dimy * sizeof(unsigned));
        for(int y = 0; y < dimy; y++)
        {
            Pixel *p = *(image + x + y);
            Uint8 average = rgb_average(p);
            if(average > 127)
                mat[x][y] = 1;
            else
                mat[x][y] = 0;
        }
    }
    return mat;
}
