# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>
# include <err.h>

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "types/pixel.h"
# include "types/matrix.h"
# include "image_op/binarize.h"
# include "image_op/sdl_fct.h"

int main()
{
    SDL_Surface *surf;
    SDL_Surface *img;
    size_t lines = 1024;
    size_t cols = 768;
    PixelMatrix *image = new_pixel_matrix(lines, cols);
    init_sdl();
    printf("Display image : %s\n", "images/test.bmp");
    surf = load_image("images/test.bmp");
    img = display_image(surf);
    save_image(img, image);
    UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
    binarize(image, mat);
    surf = unsignedMatrix_to_pict(mat);
    img = display_image(surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(img);
    free_unsigned_matrix(mat);
    return 0;
}
