# include "pixel.h"

Pixel new_pixel(Uint8 r, Uint8 g, Uint8 b){
    //Pixel pixel = malloc(sizeof(Pixel));
    Pixel pixel;
    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    return pixel;
}

Pixel **new_pixel_matrix(int dimx, int dimy){ 
    Pixel **mat;
    mat = malloc(dimx * sizeof(Pixel*));
    for(int i =0; i < dimx; i++)
        mat[i] = malloc(dimy * sizeof(Pixel));
    return mat;
}

void free_pixel_matrix(Pixel **mat, int dimx)//, int dimy)
{
    for(int i = 0; i < dimx; i++)
    {   
        //for(int j = 0; j < dimy; i++)
            //free((mat[i] + j));
        free(mat[i]);
    }
    free(mat);
}
