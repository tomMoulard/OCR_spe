# ifndef NR2_H_
# define NR2_H_

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "../types/matrix.h"
#include "../image_op/sdl_fct.h"
#include "../types/matbintree.h"
#include "../image_op/binarize.h"
#include "../images/database.h"
#include "../matrix_op/xycut.h"
#include "../types/pixel.h"

typedef struct Network Network;
struct Network{
	float Error;
	int Numpattern;
	int NumHidden;
	int NumInput;
	int NumOutput;
	int is7;

	double *ranpat;
	double *deltaO;
	double *deltaH;
	double *SumDow;

	double **deltaWeightLH;
	double **deltaWeightHO;
	double **WeightLH;
	double **WeightHO;
	double **SumO;
	double **SumH;
	double **Hidden;
	double **Output;

};

//################################Functions###############################

int useNr(Network *net, double **input);

void trainNetFinal(Network *net);

Network *OpenNr(char *filePath);

void saveNr(Network *net, char *filePath);

void freeNetwork(Network *net); //called in SaveNr

char *get_string(MatBinTree *mbt, Network *net);

void printNr(Network *net);

# endif
