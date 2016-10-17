# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>

# include "types/pixel.h"
//# include "image_op/binarize.h"

int main()
{
    Pixel **mat = new_pixel_matrix(10, 10);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            mat[i][j] = new_pixel(0, 0, 0);
    unsigned **m = binarize(mat, 10, 10); 
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; i++)
            printf("%u\n", m[i][j]);
    free(m);
    free(mat);
    return 0;
}
