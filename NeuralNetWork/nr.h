# ifndef NR_H_
# define NR_H_

#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../types/matrix.h"
#include "../image_op/sdl_fct.h"
#include "../types/matbintree.h"
#include "../image_op/binarize.h"
#include "../images/database.h"
#include "../matrix_op/xycut.h"


typedef struct Network Network;
struct Network{
  int    *numLayers;  //number of neurons by layers
  int     lenlayers;  //len of numLayers
  time_t  seed;       //seed to initiate random
  int    *sizes;      //list of bite of the letter
  int     len;        //len of size
  float *biases;     //list of biases for neurons
  int     lenbiases;  //nb neurons
  float *weight;     //list of weights for neurons
  int     lenweight;  //nb neurons //useless len biases == lenweights
};

typedef struct Bashint Bashint;
struct Bashint{
  float *input;
  float  res;
};

//########################################################
//Usefull fonctions:
int xor(int a, int b);

int nand(int a, int b);

float sigmoid(float z);

float *sigmoidStar(float *z, int len);

float sigmoidPrime(float z);

float dotfloat(float coeff, float *a, int len);

float *append(float *a, float *b, int lenA, int lenB);

//########################prints#################################
void printArrayIntLen(int *array, int len);


void printArrayIntEnd(int *beg, int *end);

void printNetwork(Network net);

void printNetworkArray(Network *a);

void printBashint(Bashint b);

void printBashintArray(Bashint *a, int len);

void printfloatarray(float *array);

Network makeNetWork(int len, int *sizes);

void freeNetwork(Network net);

void freeBashint(Bashint b);

void freefloat2star(float **a, int len);

Bashint *makeBAshXor(int len, Network net);

void suffleBashint(Bashint *bash, int len, time_t seed);

float *cutarray(float *array, int posmin, int posmax);;

float **backprop(Network *network, float *x, float y);

Bashint *update_mini_bash(Bashint *mini_bash, size_t len_mini_bash,
  float eta, Network *network);

float *feedforward(Network net, float *x);

int argmax(float *array, int len);

float evaluate(Bashint *test_data, int len_test_data, Network net);

Bashint *cutarrayBashint(Bashint *b, int posmin, int posmax);

Network SGD(Network net, Bashint *training_data, size_t len_training_data,
  int epoch, int mini_bash_size, float eta, Bashint *test_data,
  size_t len_test_data);

void fprintArrayIntLen(FILE *nr, int *array, int len);

void saveNr(Network net, char *fileName);

Network openNr(char *fileName);

int *setNetwork(int type, int nbPixels);

char *appendChar(char *a, char *b);

Bashint unsignedmatToBashint(UnsignedMatrix *matrix);

//Personized Main :3

int mainNetwork(char *filePath, int argc, Bashint *input, size_t lenInpout, int noMessinfWithNetworks);

//to use network:
char *useNetwork(Network net, Bashint input);

Network trainNet(Network net);

Network getNetwork(char *filename);

UnsignedMatrix **from_img_to_letters(char *filepath,size_t *len);

char *get_string(MatBinTree *mbt, Network net);

# endif
