# ifndef BINARIZE_H_
# define BINARIZE_H_

# include <SDL/SDL.h>
# include <stdlib.h>

# include "../types/pixel.h"

unsigned **binarize(Pixel **image, int dimx, int dimy);

# endif
