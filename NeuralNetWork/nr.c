//made by moular_b
#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "nr.h"

int xor(int a, int b)
{
	return (a*(b ? 0 : 1) || (a ? 0 : 1)*b) ? 1 : 0;
}

//ulitity
double sigmoid(double z)
{
	return 1.0 / (1.0 + exp(z));
}
double *sigmoidStar(double *z, int len)
{
	double *res = malloc(sizeof(double) * len);
	for (int i = 0; i < len; ++i)
	{
		res[i] = sigmoid(z[i]);
	}
	return res;
}
double sigmoidPrime(double z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}
double **transpose(double ***toTranspose)
{
	return *toTranspose;
}
double *dotdouble(double coeff, double *a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		*a *= coeff;
	}
	return a;
}
double *append(double *a, double *b, int lenA, int lenB)
{
	double *res = malloc(sizeof(a) * lenA + sizeof(b) * lenB);
	res = a;
	for (int i = lenA; i < lenB; ++i)
	{
		res[i] = *b;
	}
	return res;
}
//prints
void printArrayIntLen(int *array, int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void printArrayIntEnd(int *beg, int *end)
{
	for(; beg < end; ++beg)
		printf("%d\n", *beg);
}
void printNetwork(Network net)
{
	int i;
	printf("lenLayers  : %d\n", net.lenlayers);
	printf("numLayers  :\n");
	for(i = 0; i < net.lenlayers; ++i)
	{
		printf("%d ", net.numLayers[i]);
	}
	printf("\nseed     : %ld\n", net.seed);
	printf("len        : %d\n", net.len);
	printf("lenBiases  : %d\n", net.lenBiases);
	printf("lenWeight  : %d\n", net.lenWeight);
	printf("size       :\n");
	printArrayIntLen(net.sizes, net.len);
	printf("biases     :\n");	
	int thisLayer = 0;
	for (i = 0; i < net.lenBiases; ++i)
	{
		printf("| %f ", net.biases[i]);
		if(xor(i != 0,  i % net.numLayers[thisLayer] == 0))
		{
			thisLayer += 1;
			printf("|\n");
		}
	}
	thisLayer = 0;
	printf("\nweight     :\n");	
	for (i = 0; i < net.lenWeight; ++i)
	{
		printf("| %f ", net.weight[i]);
		if(xor(i != 0, i % net.numLayers[thisLayer] == 0))
		{
			thisLayer += 1;
			printf("|\n");
		}
	}
	printf("\n");
}
/*
	Making a function to create a new neural network in a Network : net 
*/
Network makeNetWork(int len, int *sizes)
{
	Network net;
	//lenLayers
	net.lenlayers = 3;
	//numlayers
	net.numLayers = malloc(sizeof(int) * net.lenlayers);
	for (int i = 0; i < net.lenlayers; ++i)
	{
		net.numLayers[i] = sizes[i];
	}
	//lenbiases
	net.lenBiases = *sizes;
	for (int i = 1; i < len; ++i)
	{
		net.lenBiases += sizes[i];
	}
	//lenwieghts
	net.lenWeight = net.lenBiases;
	//len
	net.len = len;
	//sizes
	net.sizes = sizes;
	//seed
	net.seed = time(NULL);
	srand(net.seed);
	//*biases
	double *tmpBiases = malloc(sizeof(double) * net.lenBiases);
	for (int i = 0; i < net.lenBiases; ++i)
	{
		tmpBiases[i] = ((double)rand()/(double)RAND_MAX);
	}
	net.biases = tmpBiases;
	srand(net.seed + 42);
	//*weight
	double *tmpWeights = malloc(sizeof(double) * net.lenWeight);
	for (int j = 0; j < net.lenWeight; ++j)
	{
		tmpWeights[j] = ((double)rand()/(double)RAND_MAX);
	}
	net.weight = tmpWeights;
	free(tmpWeights);
	free(tmpBiases);
	//lenWeight
	return net;
}

void freeNetwork(Network net)
{
	free(net.sizes);
	free(net.numLayers);
	//free(net.weight);
	//free(net.biases);
}

Bashint *makeBAshXor(int len, Network net){
	Bashint *res = malloc(sizeof(Bashint) * len);
	//initiate random
	srand(net.seed);
	for (int i = 0; i < len; ++i)
 	{
 		Bashint b;
 		double *tmp = malloc(sizeof(double) * 2);
 		*tmp = rand()%2;
 		*(tmp + 1) = rand()%2;
 		b.res = xor(*tmp, *(tmp + 1));
 		b.input = tmp;
 		res[i] = b;
 	} 	
 	return res;

}
/*
Network update_mini_bash(Network net, double eta, Bashint *mini_bash)
{
	return net;
}
*/
/*
void saveNr(Network net)
{
	FILE *nr;
	nr = fopen("REMOVEME!neuralNetwork.nr", "r");
	net.len++;
	fclose(nr);
}
*/
//open a .nr file to get a previouly saved network : WORK IN PROGRESS
Network openNr()
{
	FILE *nr;
	nr = fopen("REMOVEME!neuralNetwork.nr", "r"); 
    Network net;
  	if (nr == NULL) {
    	printf("Fail to retrive neural network from file, creating a new one : \n");  
    	net.len = -1;
    	return net;
    }
    fclose(nr);
    return net;
}

int *setNetwork(int type, int nbPixels)
{
	if (type == 1) //xor -> set len to 3
	{
		int *res   = malloc(3 * sizeof(int));
		*res       = 2 ; //input neurons
		*(res + 1) = 3 ;
		*(res + 2) = 1 ; //output neurons
		return res;
	}
	if (type == 2)//picture recognition [0-9]
	{
		int *res   = malloc(3 * sizeof (int));
		*res       = nbPixels;
		*(res + 1) = 100;//fixme
		*(res + 2) = 10;
		return res;
	}
	if (type == 3)//picture recognition [0-9a-zA-Z]
	{
		int *res   = malloc(3 * sizeof (int));
		*res       = nbPixels;
		*(res + 1) = 100;//fixme
		*(res + 2) = 62;
		return res;
	}
	if (type == 4)//picture recognition [0-9]
	{ 
		int *res   = malloc(3 * sizeof (int));
		*res       = nbPixels;
		*(res + 1) = 100; //fixme
		*(res + 2) = 185;
		return res;
	}
	//fail : no layer schema
	errx(2, "Please, input a valid input : input a network scheme.");
}

//convert A char to int : A = strtoul(A, NULL, 10);
int main(int argc, char *argv[])
{
	if (argc < 2)
		errx(1, "Please input a valid input :\n	- number of pixel in width\n 	- list of pixels\n");
	argv[0]++;
	int len = 3;
	int nbPixels = 900;
	//int **test = makeNetWorkOld(len, net);
	Network net = openNr();
	if (net.len == -1)
	{
		int type = 1;
		net = makeNetWork(len, setNetwork(type, nbPixels));
	}
	//Bashint *testBash = makeBAshXor(1000, net);
	//net = update_mini_bash(net, 0.3, testBash);
	printNetwork(net);
	//saveNr(net);
	freeNetwork(net);
	return 0;
}