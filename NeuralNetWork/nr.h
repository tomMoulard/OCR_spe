#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

typedef struct Network Network;
struct Network{
  int    *numLayers;  //number of neurons by layers
  int     lenlayers;  //len of numLayers
  time_t  seed;       //seed to initiate random
  int    *sizes;      //list of bite of the letter
  int     len;        //len of size
  double *biases;     //list of biases for neurons
  int     lenBiases;  //nb neurons
  double *weight;     //list of weights for neurons
  int     lenWeight;  //nb neurons //useless len biases == lenweights
};

typedef struct Bashint Bashint;
struct Bashint{
	double *input;
	double  res;
};