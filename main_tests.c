# define _XOPEN_SOURCE 500

# include <stdio.h>
# include <stdlib.h>
# include <err.h>

# include "types/pixel.h"
# include "image_op/binarize.h"
# include "matrix_op/rlsa.h"
# include "types/rectangle.h"
# include "types/matrix.h"
# include "types/matbintree.h"
# include "matrix_op/xycut.h"
# include "image_op/sdl_fct.h"


unsigned get_all_rect(MatBinTree* mbt,UnsignedMatrix *mat,unsigned h){
  if (!mbt) {
    return h;
  }
  else{
    displayrect(mat,mbt->pos,h);
    unsigned l = get_all_rect(mbt->left,mat,h + 1);
    unsigned r = get_all_rect(mbt->right,mat,h + 1);
    return (h > l) && (h > r)? h :(l > r? l : r);
  }
}


int main(void) {
  SDL_Surface *img = load_image("images/level2.jpg");
  size_t w = 1126;
  size_t h = 1570;

  UnsignedMatrix* mat = cut(frompictomatbin(img,w,h),0,1126,500,1570);
  unsigned coef;
  UnsignedMatrix* matecc = ecc(mat,&coef);
  display_image(frommattopict(matecc,coef));

  free_unsigned_matrix(mat);
  free_unsigned_matrix(matecc);

return 0;
}
