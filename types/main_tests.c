# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>

# include "pixel.h"

int main()
{
    Pixel *p = new_pixel(100, 50, 25);
    printf("%u\n", rgb_average(p));
    free(p);
    return 0;
}
