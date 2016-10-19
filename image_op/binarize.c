# include <math.h>
# include "binarize.h"

void to_grey_scale(Pixel **image, Pixel **dest, int dimx, int dimy)
{
    for(int i = 0; i < dimx; i++)
        for(int j =0; j < dimy; j++)
        {
            Pixel p = image[i][j];
            Uint8 r = p.r;
            Uint8 g = p.g;
            Uint8 b = p.b;
            Uint8 f = sqrt((r * r + g * g + b * b) / 3);
            dest[i][j] = new_pixel(f, f, f);
        }
}

void get_histogram(Pixel **grey_mat, int *array, int dimx, int dimy)
{
    for(int i = 0; i < dimx; i++)
        for(int j = 0; j < dimy; j++)
            *(array + grey_mat[i][j].r) += 1;

}

Uint8 get_threshold(int *histogram, int total)
{
    int sum = 0, wf = 0, sumb = 0;
    int mb, mf;
    float between = 0, max = 0;
    Uint8 threshold1 = 0, threshold2 =0;
    for(int i = 0; i < 256; i++)
        sum += i * histogram[i];
    Uint8 wb = 0;
    for(int i = 0; i < 256; i++)
    {
        wb += histogram[i];
        if(wb == 0)
            continue;
        wf = total - wb;
        if( wf == 0)
            break;

        sumb += i * histogram[i];
        mb = sumb / wb;
        mf = (sum - sumb) / wf;
        between = wb * wf * (mb - mf) * (mb - mf);
        if(between >= max)
        {
            threshold1 = i;
            if(between > max)
                threshold2 = i;
            max = between;
        }
    }
    return((threshold1 +threshold2) / 2);
}

void binarize(Pixel **image, unsigned **mat, int dimx, int dimy)
{
    Pixel **grey_mat = new_pixel_matrix(dimx, dimy);
    to_grey_scale(image, grey_mat, dimx, dimy);
    int *histogram = malloc(256 * sizeof(int));
    Uint8 threshold = get_threshold(histogram, dimx*dimy);
    for(int i = 0; i < dimx; i++)
    {
        for(int j = 0; j < dimy; j++)
        {
            Uint8 g = grey_mat[i][j].r;
            if(g > threshold)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
    free_pixel_matrix(grey_mat, dimx);//, dimy);
}
