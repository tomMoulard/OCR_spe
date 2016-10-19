# ifndef BINARIZE_H_
# define BINARIZE_H_

# include <SDL/SDL.h>
# include <stdlib.h>
# include <math.h>

# include "../types/pixel.h"

void to_grey_scale(Pixel **image, Pixel **dest, int dmx, int dmy);
void get_histogram(Pixel **grey_mat, int* array, int dmx, int dmy);
Uint8 get_threshold(int *histogram, int total);
void binarize(Pixel **image, unsigned **mat, int dimx, int dimy);

# endif
