# ifndef BINARIZE_H_
# define BINARIZE_H_

# include <SDL/SDL.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../types/pixel.h"
# include "../types/matrix.h"

void binarize(PixelMatrix *image, UnsignedMatrix *mat);

# endif
