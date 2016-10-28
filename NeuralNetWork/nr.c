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
double dotstar(double *a, double *b, int len)
{
	double res;
	for (int i = 0; i < len; ++i)
	{
		printf("dotstar\n");
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
	printf("numLayers : %d\n", net.numLayers);
	printf("seed       : %ld\n", net.seed);
	printf("len        : %d\n", net.len);
	printf("lenBiases  : %d\n", net.lenBiases);
	printf("lenWeight  : %d\n", net.lenWeight);
	printf("size       :\n");
	printArrayIntLen(net.sizes, net.len);
	printf("biases     :\n");	
	for (int i = 0; i < net.lenBiases; ++i)
	{
		printf("%f ; ", net.biases[i]);
		if(i % net.numLayers == 0)
			printf("\n");
	}
	printf("weight     :\n");	
	for (int i = 0; i < net.lenWeight; ++i)
	{
		printf("%f ; ", net.weight[i]);
		if(i % net.numLayers == 0)
			printf("\n");
	}
	printf("\n");
}
/*
	Making a function to create a new neural network in a Network : net 
*/
Network makeNetWork(int len, int *sizes)
{
	Network net;
	//numLayers
	net.numLayers = 3;
	//lenbiases
	net.lenBiases = *sizes;
	for (int i = 0; i < len; ++i)
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
	//**biases
	double *tmpBiases = malloc(len * sizeof(double) * net.numLayers);
	for (int i = 0; i < net.lenBiases; ++i)
	{
		tmpBiases[i] = rand()%2;
	}
	net.biases = tmpBiases;
	free(tmpBiases);
	//lenBiases
	net.lenBiases = net.len - 1;
	//**weight
	double *tmpWeights = malloc(sizeof(double) * lenWeight);
	for (int j = 0; j < net.lenWeight; ++j)
	{
		tmpWeights[j] = rand()%2;
	}
	net.weight = tmpWeights;
	free(tmpWeights);
	//lenWeight
	return net;
}

void freeNetwork(Network net)
{
	free(net.sizes);
	free(net.biases);
	free(net.weight);
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

double **backProp(Network net,int x ,int y)
{
	//initiate nabla_b et nabla_w
	double ***nabla_b = malloc(sizeof(double **));
	double **nabla_bTmp = malloc(sizeof(double *) * net.len);
	for (int i = 0; i < net.len; ++i)
	{
		double *tmp = malloc(sizeof(double) * net.sizes[i]);
		for (int j = 0; j < net.sizes[i]; ++j)
		{
			tmp[j] =0;
		}
	}
	*nabla_b = nabla_bTmp;
	double ***nabla_w = malloc(sizeof(double **) * net.numLayers);
	int xTmp = 0;
	int yTmp = 1;
	for (int i = 0; i < net.numLayers - 1; ++i)
	{
		double **tmpi = malloc(sizeof(double *) * net.sizes[xTmp]);
		for (int j = 0; j < net.sizes[xTmp]; ++j)
		{
			double *tmpj = malloc(sizeof(double) * net.sizes[yTmp]);
			for (int k = 0; k < net.sizes[yTmp]; ++k)
			{
				tmpj[k] = 0;
			}
			tmpi[j] = tmpj;
		}
		xTmp = 1 + xTmp;
		yTmp = 1 + yTmp;
	}
	//feedforward
	double activation = x;
	double *activations = malloc(sizeof(double) * net.len);
	*activations = x;
	double **zs = malloc(sizeof(double *) * net.len);
	for (int i = 0; i < net.len; ++i)
	{
		double *z = append(dotdouble(net.weight[i], activation, net.numLayers), net.biases[i] net.len, net.len);
		zs[i] = z;
		activation = sigmoid(z);
		activations[i] = activation;
	}
	//backwardpass
	double delta = 
		(activations[net.len - 1] - y) * sigmoidPrime(zs[net.len - 1]);
	nabla_b[net.len - 1]        = delta;
	nabla_w[net.numLayers - 1] = dotdouble(delta, activations, net.len);

	return nabla_bTmp;
}

Network update_mini_bash(Network net, double eta, Bashint *mini_bash)
{
	double **nabla_b = malloc(sizeof(double *) * net.len);
	for (int i = 0; i < net.len; ++i)
	{
		double *tmp = malloc(sizeof(double) * net.sizes[i]);
		for (int j = 0; j < net.sizes[i]; ++j)
		{
			tmp[j] =0;
		}
	}
	double ***nabla_w = malloc(sizeof(double **) * net.numLayers);
	int x = 0;
	int y = 1;
	for (double i = 0; i < net.numLayers - 1; ++i)
	{
		double **tmpi = malloc(sizeof(double *) * net.sizes[x]);
		for (int j = 0; j < net.sizes[x]; ++j)
		{
			double *tmpj = malloc(sizeof(double) * net.sizes[y]);
			for (int k = 0; k < net.sizes[y]; ++k)
			{
				tmpj[k] = 0;
			}
			tmpi[j] = tmpj;
		}
		x = 1 + x;
		y = 1 + y;
	}
	//remove me!
	(*mini_bash).res  = 2;
	eta++;

	return net;
}

void saveNr(Network net)
{
	FILE *nr;
	nr = fopen("REMOVEME!neuralNetwork.nr", "r");
	net.len++;
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
	//Bashint *testBash = makeBAshXor(1000, net);
	//net = update_mini_bash(net, 0.3, testBash);
	printNetwork(net);
	saveNr(net);
	freeNetwork(net);
	return 0;
}