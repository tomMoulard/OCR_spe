# include <math.h>
# include "binarize.h"

PixelMatrix *to_grey_scale(PixelMatrix *image)
{
    PixelMatrix *dest = new_pixel_matrix(image->lines, image->cols);
    for(size_t i = 0; i < image->lines; i++)
        for(size_t j =0; j < image->cols; j++)
        {
            Pixel p = image->data[i * image->cols + j];
            Uint8 r = p.r;
            Uint8 g = p.g;
            Uint8 b = p.b;
            Uint8 f = sqrt((r * r + g * g + b * b) / 3);
            dest->data[i * dest->cols + j] = new_pixel(f, f, f);
        }
    return dest;
}

unsigned long *get_histogram(PixelMatrix *grey_mat, unsigned long *array)
{
    for(size_t i = 0; i < grey_mat->lines; i++)
        for(size_t j = 0; j < grey_mat->cols; j++)
        {
            Uint8 n = grey_mat->data[i * grey_mat->cols + j].r;
            if(array[n] < 4294967295)
                array[n] += 1;
        }
    return array;
}

Uint8 get_threshold(unsigned long *histogram, int total)
{
    unsigned long sum = 0, wf = 0, sumb = 0;
    unsigned long mb, mf;
    float between = 0, max = 0;
    Uint8 threshold1 = 0, threshold2 =0;
    for(int i = 0; i < 256; i++)
        sum += i * histogram[i];
    unsigned long wb = 0;
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
    Uint8 threshold = ((threshold1 + threshold2) / 2);
    //printf("threshold = %u\n", threshold);
    return threshold;
}

void array_print(unsigned long array[], size_t len)
{
  int line = 0;
  for (size_t i = 0; i < len; ++i) {
    if (line > 72) {
      printf("|`|\n");
      line = 0;
    }
    line += printf("| %lu", array[i]);
  }
  printf("|\n");
}

void binarize(PixelMatrix *image, UnsignedMatrix *mat)
{
    PixelMatrix *grey_mat = to_grey_scale(image);
    unsigned long *hist = malloc(256 * sizeof(unsigned long));
    for(int i = 0; i < 256; i++)
        hist[i] = 0;
    hist = get_histogram(grey_mat, hist);
    //array_print(hist, 256);
    Uint8 threshold = get_threshold(hist, image->lines*image->cols);
    for(size_t i = 0; i < mat->lines; i++)
    {
        for(size_t j = 0; j < mat->cols; j++)
        {
            Uint8 g = grey_mat->data[i * grey_mat->cols + j].r;
            if(g > threshold)
                mat->data[i * mat->cols + j] = 0;
            else
                mat->data[i * mat->cols + j] = 1;
        }
    }
    free(hist);
    free_pixel_matrix(grey_mat);
}
