# ifndef BINARIZE_H_
# define BINARIZE_H_

# include <SDL/SDL.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../types/pixel.h"

void binarize(Pixel **image, unsigned **mat, int dimx, int dimy);

# endif
