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
double sigmoidPrime(double z)
{
	return sigmoid(z) * (1 - sigmoid(z));
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

void printBiases(Network net)
{
	printf("%p\n", &net.biases);
}
void printWeight(Network net)
{
	printf("%p\n", &net.weight);
}

void printNetwork(Network net)
{
	printf("num_layers : %d\n", net.num_layers);
	printf("seed       : %ld\n", net.seed);
	printf("len        : %d\n", net.len);
	printf("lenBiases  : %d\n", net.lenBiases);
	printf("lenWeight  : %d\n", net.lenWeight);
	printf("size       :\n");
	printArrayIntLen(net.sizes, net.len);
	printf("bias       :\n");	
	printBiases(net);
	printf("weight     :\n");
	printWeight(net);
	printf("\n");
}
/*
	Making a function to create a new neural network in a Network : net 
*/
int **makeNetWorkOld(int len, int *array)
{
	int **Array = malloc(5);
	int nbNeurons = *array;
	for (int i = 1; i < len; ++i)
	{
		nbNeurons += array[i];
	}
	int *biasesDeb = malloc(nbNeurons * sizeof ( int )); 
	int *tmp = biasesDeb;
	//random :
	srand(time(NULL));

	for(; tmp < nbNeurons + biasesDeb; ++tmp)
	{
		*tmp = rand()%2; // init biase value
	}
	//free(tmp);
	printArrayIntEnd(biasesDeb, (biasesDeb + nbNeurons) );
	int *weightDeb = malloc(len);
	tmp = weightDeb;
	for(; tmp < weightDeb + nbNeurons; ++tmp)
	{
		*tmp = rand()%2; // init biase value	
	}
	printArrayIntEnd(biasesDeb, biasesDeb + len);
	*(Array+0) = biasesDeb; //biasesFin = biasesDeb + nbNeurons;
	*(Array+1) = weightDeb; //weightFin = weightDeb + nbNeurons;
	*(Array+2) = array;	
	return Array;	
}

double **randnFile(time_t seed, int a, int b)
{
	srand(seed);
	double **res = malloc(sizeof(double) * a * b);
	for (int i = 0; i < a; ++i)
	{
		double *tmp = malloc(b * sizeof(double));
		res[i] = tmp;
		for (int j = 0; j < b; ++j)
		{
			tmp[j] = rand()%2;
		}
	}
	return res;
}

Network makeNetWork(int len, int *sizes)
{
	Network net;
	//num_layers
	net.num_layers = *sizes;
	for (int i = 0; i < len; ++i)
	{
		net.num_layers = sizes[i];
	}
	//len
	net.len = len;
	//sizes
	net.sizes = sizes;
	//seed
	net.seed = time(NULL);
	srand(net.seed);
	//**biases
	double **tmpBiases = malloc(len * sizeof(double *) * net.num_layers);
	net.biases = tmpBiases;
	for (int i = 1; i < len; ++i)
	{
		double *tmp = malloc(sizeof(double *) * sizes[i]);
		*tmpBiases = tmp;
		for (int j = 0; j < sizes[i]; ++j)
		{
			*tmp = rand()%2;
			++tmp;
		}
		++tmpBiases;
	}
	//lenBiases
	net.lenBiases = net.len - 1;
	//**weight
	int x = 0, y = sizes[1];
	double ***res = malloc(sizeof(double) * net.num_layers);
	net.weight = res;
	for (int q = 0; q < net.num_layers - 1; ++q)
	{
		res[q] = randnFile(net.seed, sizes[x], sizes[y]);
		x = x + 1;
		y = y + 1;
	}
	//lenWeight
	return net;
}

void freeNetwork(Network net)
{
	free(net.sizes);
	for (int i = 0; i < net.len; ++i)
	{
		free(net.biases[i]);
	}
	free(net.biases);
	int x = 0;
	for (int j = 0; j < net.num_layers - 1; ++j)
	{
		for (int w = 0; w < net.sizes[x]; ++w)
		{
			printf("yolo1\n");
			free(net.weight[j][w]);
		}
		printf("yolo2\n");
		x = x + 1;
		//free(net.weight[j]);

	}
	free(net.weight);
}

Network update_mini_bash(Network net, double eta)
{
	double **nabla_b = malloc(sizeof(double *) * net.len);
	for (double i = 0; i < net.len; ++i)
	{
		double *tmp = malloc(sizeof(double) * net.sises[i])
		for (int j = 0; j < net.sizes[i]; ++j)
		{
			tmp[j] =0;
		}
	}
	double ***nabla_w = malloc(sizeof(double **) * net.num_layers);
	double x = 0;
	double y = 1;
	for (double i = 0; i < net.num_layers - 1; ++i)
	{
		double **tmpi = malloc(sizeof(double *) * net.sizes[x]);
		for (int j = 0; j < net.sizes[x]; ++j)
		{
			double *tmpj = malloc(sizeof(double) * net.size[y]);
			for (int k = 0; k < net.sizes[y]; ++k)
			{
				tmpj[k] = 0;
			}
		}
		x = 1 + x;
		y = 1 + y;
	}

	return net;
}

void saveNr(Network, net)
{
	FILE *nr;
	nr = fopen("REMOVEME!neuralNetwork.nr", "r");
	fclose(nr);
}

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
	printNetwork(net);
	saveNr(net);
	freeNetwork(net);
	return 0;
}