//the second
#include "nr2.h"

double sigmoid(double input){
	return 1.0 / (1.0 + exp(- input));
}
double sigmoidPrime(double input){
	double tmp = sigmoid(input);
	return tmp *( 1.0 - tmp);
}
double rando(){
	return (double)rand()/((double)RAND_MAX+1);
}
void shuffle(double *input, int len){
	srand(time(NULL));
	double tmp;
	int pos = 0;
	for(int i = 0; i < len; i++){
		pos                = rand() % (len - i - 1);
		tmp                = input[pos];
		input[pos]         = input[len - i - 1];
		input[len - i - 1] = tmp;
	}
}

UnsignedMatrix **from_img_to_letters(char *filepath, size_t *len){
  size_t lines = bmpWidth(filepath);
  size_t cols = bmpHeight(filepath);
  SDL_Surface *surf;
  init_sdl();
  PixelMatrix *image = new_pixel_matrix(lines, cols);
  //printf("Display image : %s\n", filepath);
  surf = load_image(filepath);
  save_image(surf, image);
  UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
  binarize(image, mat);
  free_pixel_matrix(image);

  UnsignedMatrix *matrix = copy_mat(mat);

  MatBinTree *mbt = new_matbintree(matrix);
  xycut_test(mbt,1,1,10);
  UnsignedMatrix **mats = get_letters(mbt,len);

  free_matbintree(mbt);
  SDL_FreeSurface(surf);
  free_unsigned_matrix(mat);
  return mats;
}

Network *initNet(){
    srand(time(NULL));
	Network *net = malloc(sizeof(Network));
	net->NumInput      = 900;
	net->NumOutput     = 2;
	net->NumHidden     = 150;
	
	double smallWeight = 0.5;

	net->deltaWeightLH = malloc(sizeof(double *) * (net->NumInput + 1));
	net->WeightLH      = malloc(sizeof(double *) * (net->NumInput + 1));
	for(int i = 0; i < net->NumInput  + 1; i++){
		net->deltaWeightLH[i] = malloc(sizeof(double) * net->NumHidden);
		net->WeightLH[i]      = malloc(sizeof(double) * net->NumHidden);
		for(int j = 0; j < net->NumHidden;j++){
			net->deltaWeightLH[i][j] = 0.0;
			net->WeightLH[i][j] = 2.0 * (rando() - 0.5) * smallWeight;
		}
	}
	net->deltaWeightHO = malloc(sizeof(double *) * (net->NumHidden + 1));
	net->WeightHO      = malloc(sizeof(double *) * (net->NumHidden + 1));
	for(int k = 0; k < net->NumHidden + 1; k++){
		net->deltaWeightHO[k] = malloc(sizeof(double) * net->NumOutput);
		net->WeightHO[k]      = malloc(sizeof(double) * net->NumOutput);
	}
	for (int k = 0; k < net->NumOutput; k++)
	{
		for(int j = 0; j < net->NumHidden + 1; j++){
				net->deltaWeightHO[j][k] = 0.0;
				net->WeightHO[j][k] = 2.0 * (rando() - 0.5) * smallWeight;
			}
	}

	net->SumO = malloc(sizeof(double *) * net->NumOutput);
	for(int l = 0; l < net->NumOutput; l++){

	}
	net->SumDow    = malloc(sizeof(double) * net->NumHidden);
	net->deltaH    = malloc(sizeof(double) * net->NumHidden);
	net->deltaO    = malloc(sizeof(double) * net->NumOutput);

	return net;
}

void trainNetwork(Network *net, size_t _epoch, double eta,\
	double alpha, double **input, double **target){
	net->ranpat = malloc(sizeof(double) * net->Numpattern);
	int np;
	double op;
	net->SumH          = malloc(sizeof(double *) * net->Numpattern);
	net->SumO          = malloc(sizeof(double *) * net->Numpattern);
	net->Hidden        = malloc(sizeof(double *) * net->Numpattern);
	net->Output        = malloc(sizeof(double *) * net->Numpattern);
	for(int i = 0; i < net->Numpattern; i++){
		net->Output[i] = malloc(sizeof(double) * net->NumOutput);
		net->SumO[i]   = malloc(sizeof(double) * net->NumOutput);
		net->SumH[i]   = malloc(sizeof(double) * net->NumHidden);
		net->Hidden[i] = malloc(sizeof(double) * net->NumHidden);
	}
	for(size_t epoch = 0; epoch < _epoch; epoch++){
		for(int p = 0; p < net->Numpattern; p++){
			net->ranpat[p] = p;
		}
		for(int q = 0; q < net->Numpattern; q++){
			np              = q + rando() * (net->Numpattern + 1 - q);
			op              = net->ranpat[q];
			net->ranpat[q]  = net->ranpat[np];
			net->ranpat[np] = op;
		}
		net->Error = 0.0;
		for(int np = 0; np < net->Numpattern; np++){
			int p = net->ranpat[np];
			for(int j = 0; j < net->NumHidden;j++){
				net->SumH[p][j] = net->WeightLH[net->NumHidden][j];
				for(int i = 0; i < net->NumInput; i++){
					net->SumH[p][j] += input[p][i] * net->WeightLH[i][j];
				}
				net->Hidden[p][j] = sigmoid(net->SumH[p][j]);
			}
			for(int k = 0; k < net->NumOutput;k++){
				net->SumO[p][k] = net->WeightHO[net->NumHidden][k];
				for(int l = 0; l < net->NumHidden; l++){
					net->SumO[p][k] += net->Hidden[p][l] * net->WeightHO[l][k];
				}
				net->Output[p][k] = sigmoid(net->SumO[p][k]);
				net->Error        += 0.5 * (target[p][k] - net->Output[p][k]) * (target[p][k] - net->Output[p][k]);/* SSE */
				net->deltaO[k]    = (target[p][k] - net->Output[p][k]) * net->Output[p][k] * (1.0 - net->Output[p][k]);
			}
			for(int j = 0; j < net->NumHidden;j++){
				net->SumDow[j] = 0.0;
				for(int m = 0; m < net->NumOutput; m++){
					net->SumDow[j] += net->WeightHO[j][m] * net->deltaO[m];
				}
				net->deltaH[j] = net->SumDow[j] * net->Hidden[p][j]\
											    * (1.0 - net->Hidden[p][j]);
			}
			for(int j = 0; j < net->NumHidden;j++){
				net->deltaWeightLH[net->NumHidden][j] = eta * net->deltaH[j] + alpha *\
							 net->deltaWeightLH[net->NumHidden][j];
				net->WeightLH[net->NumHidden][j]      += net->deltaWeightLH[net->NumHidden][j];
				for(int n = 0; n < net->NumInput; n++){
					net->deltaWeightLH[n][j] = eta * input[p][n] *\
							 net->deltaH[j] + alpha * net->deltaWeightLH[n][j];
					net->WeightLH[n][j]      += net->deltaWeightLH[n][j] ;
				}
			}
			for(int k = 0; k < net->NumOutput; k++){
				net->deltaWeightHO[net->NumHidden][k] = eta * net->deltaO[k] + alpha *\
									 net->deltaWeightHO[net->NumHidden][k] ;
				net->WeightHO[net->NumHidden][k]      += net->deltaWeightHO[net->NumHidden][k];
				for(int o = 0; o < net->NumHidden ;o++){
                    net->deltaWeightHO[o][k] = eta * net->Hidden[p][o] *\
                    		 net->deltaO[k] + alpha * net->deltaWeightHO[o][k] ;
                    net->WeightHO[o][k] += net->deltaWeightHO[o][k] ;
				}
			}
		}
		printf("epoch : %zu -> Error : %f\n", epoch, net->Error);
	}
	for(int i = 0; i < net->NumOutput; i++){
		printf("input :\n");
		for(int j = 0; j < 900; j++){
			printf("%c ", input[i][j]? '#' : ' ');
			if(j % 30 == 29){
				printf("\n");
			}
		}
		printf("\noutput : ");
		printf("%f\n", net->Output[i][0]);
	}

}

/*
int useNetwork(Network net, double *input){
	int res = 0;

	return res;
}*/
/*
int main()//int argc, char const *argv[])
{
	Network *net = initNet();
	net->Numpattern    = 4;
	double **input  = malloc(sizeof(double *) * net->Numpattern);
	input[0] = malloc(sizeof(double) * 2);
	input[0][0] = 0;
	input[0][1] = 1;
	input[1] = malloc(sizeof(double) * 2);
	input[1][0] = 1;
	input[1][1] = 1;
	input[2] = malloc(sizeof(double) * 2);
	input[2][0] = 1;
	input[2][1] = 0;
	input[3] = malloc(sizeof(double) * 2);
	input[3][0] = 0;
	input[3][1] = 0;
	double **target = malloc(sizeof(double *) * net->Numpattern);
	target[0] = malloc(sizeof(double) * 1);
	target[0][0] = 1;
	target[1] = malloc(sizeof(double) * 1);
	target[1][0] = 0;
	target[2] = malloc(sizeof(double) * 1);
	target[2][0] = 1;
	target[3] = malloc(sizeof(double) * 1);
	target[3][0] = 0;
	trainNetwork(net, 100000, 0.1, 0.9, input, target);
	return 0;
}
*/
void trainNetFinal(Network *net){
	char *res  = malloc(sizeof(char) * 500);
    FILE *file = fopen("trainingData/3.txt", "r");
    char tmp = '0';
    size_t i = 0;
    int rep = 0;
    while(tmp != '\n'){
        rep += fscanf(file, "%c", &tmp);
        res[i] = tmp;
        i++;
    }
    fclose(file);

    res[i + 1] = '\0';
    size_t len2 = 0;
    char *filePath        = "trainingData/3.bmp";
    UnsignedMatrix **mats = from_img_to_letters(filePath,&len2);
    len2 --;
	net->Numpattern    = len2;
	double **input  = malloc(sizeof(double *) * net->Numpattern);
	double **target = malloc(sizeof(double *) * net->Numpattern);
    for(i = 0; i < len2; ++i){
		input[i]  = malloc(sizeof(double) * 900);
		for(int j = 0; j < 900; ++j){
			input[i][j] = (double)mats[i]->data[j];
		}
    }
    for(size_t j = 0 ; j < len2; ++j){
		target[j] = calloc(sizeof(double), 1);
		target[j][0] = j;

    }
	trainNetwork(net, 100, 0.1, 0.9, input, target);
}
int main()//int argc, char const *argv[])
{
	Network *net = initNet();
	trainNetFinal(net);
	return 0;
}
