# ifndef ROTATION_H_
# define ROTATION_H_

# define PI (3.141592653589793)

# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# include "../types/matrix.h"
# include "../matrix_op/xycut.h"

UnsignedMatrix *rotation(UnsignedMatrix *mat, double angle);

# endif
