# include "pixel.h"

Pixel new_pixel(Uint8 r, Uint8 g, Uint8 b){
    Pixel pixel;
    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    return pixel;
}

PixelMatrix *new_pixel_matrix(size_t lines, size_t cols){
    PixelMatrix *matrix;
    matrix = malloc(sizeof(PixelMatrix));
    matrix->lines = lines;
    matrix->cols = cols;
    matrix->data = malloc(lines * cols * sizeof(Pixel));
    return matrix;
}

void free_pixel_matrix(PixelMatrix *matrix){
    free(matrix->data);
    free(matrix);
}
