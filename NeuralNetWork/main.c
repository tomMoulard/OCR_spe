#include "nr2.h"

int main(int argc, char *argv[])
{
	if(argc == 2){
		size_t lines        = bmpWidth(argv[1]);
		size_t cols         = bmpHeight(argv[1]);
		SDL_Surface *surf;
		init_sdl();
		//SDL_Surface *img;
		PixelMatrix *image  = new_pixel_matrix(lines, cols);
		//printf("Display image : %s\n", argv[1]);
		surf                = load_image(argv[1]);
		//img                 = display_image(surf);
		save_image(surf, image);
		UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
		binarize(image, mat);
		free_pixel_matrix(image);
		
		UnsignedMatrix *matrix   = copy_mat(mat);
		//UnsignedMatrix *matrix = eraseimage(mat);
		MatBinTree *mbt          = new_matbintree(matrix);
		//SDL_Surface *img;

		xycut_test(mbt,1,1,10);
		printf("getting the network from file\n");
		Network *net = OpenNr("network.nr");
		printf("let's train the network\n");
		//trainNetFinal(net);
		char *str = get_string(mbt, net);
		printf("\n \n %s\n", str);
		free(str);
		SDL_FreeSurface(surf);
		//SDL_FreeSurface(img);
		free_unsigned_matrix(mat);
	}
	return 0;
}