#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


typedef struct Network Network;
struct Network{
  int       num_layers;
  time_t    seed;
  int       len;
  int      *sizes;
  double  **biases;
  int       lenBiases;
  double ***weight;
  int       lenWeight;
};