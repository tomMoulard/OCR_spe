# include "binarize.h"

unsigned **binarize(Pixel **image, int dimx, int dimy)
{
    unsigned **mat = calloc(dimx, sizeof(unsigned[dimy]));
    for(int x = 0; x < dimx; x++)
    {
        mat[x] = calloc(dimy, sizeof(unsigned));
        for(int y = 0; y < dimy; y++)
        {
            Uint8 average = rgb_average(p);
            if(average > 127)
                mat[x][y] = 1;
            else
                mat[x][y] = 0;
        }
    }
    return mat;
}
