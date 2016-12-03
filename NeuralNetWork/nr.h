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
  double *biases;     //list of biases for neurons
  int     lenbiases;  //nb neurons
  double *weight;     //list of weights for neurons
  int     lenweight;  //nb neurons //useless len biases == lenweights
};

typedef struct Bashint Bashint;
struct Bashint{
  double *input;
  double  res;
};

//########################################################
//Usefull fonctions:
int xor(int a, int b);

int nand(int a, int b);

double sigmoid(double z);

double *sigmoidStar(double *z, int len);

double sigmoidPrime(double z);

double dotdouble(double coeff, double *a, int len);

double *append(double *a, double *b, int lenA, int lenB);

//########################prints#################################
void printArrayIntLen(int *array, int len);


void printArrayIntEnd(int *beg, int *end);

void printNetwork(Network net);

void printNetworkArray(Network *a);

void printBashint(Bashint b);

void printBashintArray(Bashint *a, int len);

void printdoublearray(double *array);

Network makeNetWork(int len, int *sizes);

void freeNetwork(Network net);

void freeBashint(Bashint b);

void freedouble2star(double **a, int len);

Bashint *makeBAshXor(int len, Network net);

void suffleBashint(Bashint *bash, int len, time_t seed);

double *cutarray(double *array, int posmin, int posmax);;

double **backprop(Network *network, double *x, double y);

Bashint *update_mini_bash(Bashint *mini_bash, size_t len_mini_bash,
  double eta, Network *network);

double *feedforward(Network net, double *x);

int argmax(double *array, int len);

double evaluate(Bashint *test_data, int len_test_data, Network net);

Bashint *cutarrayBashint(Bashint *b, int posmin, int posmax);

Network SGD(Network net, Bashint *training_data, size_t len_training_data,
  int epoch, int mini_bash_size, double eta, Bashint *test_data,
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

Network getNetwork();

UnsignedMatrix **from_img_to_letters(char *filepath,size_t *len);

char *get_string(MatBinTree *mbt, Network net);

# endif
