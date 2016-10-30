//made by moular_b
#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "nr.h"

int xor(int a, int b)
{  //explicit content
	return (a*(b ? 0 : 1) || (a ? 0 : 1)*b) ? 1 : 0;
}
int nand(int a, int b)
{  //explicit content
	return a * b ? 0 : 1;
}

//ulitity
double sigmoid(double z)
{  //explicit content
	return 1.0 / (1.0 + exp(z));
}
double *sigmoidStar(double *z, int len)
{  //explicit content
	double *res = malloc(sizeof(double) * len);
	for (int i = 0; i < len; ++i)
	{
		res[i] = sigmoid(z[i]);
	}
	return res;
}
double sigmoidPrime(double z)
{  //explicit content
	return sigmoid(z) * (1 - sigmoid(z));
}
double dotdouble(double coeff, double *a, int len)
{  //do a dot mathematical function :3 
	double res = 0;
	for (int i = 0; i < len; ++i)
	{
		res += a[i] * coeff;
	}
	return res;
}
double *append(double *a, double *b, int lenA, int lenB)
{  //To append two list a and b.
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
{  //explicit content
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void printArrayIntEnd(int *beg, int *end)
{  //explicit content
	for(; beg < end; ++beg)
		printf("%d\n", *beg);
}
void printNetwork(Network net)
{  //explicit content
	int i, j;
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
	int pos = 0;
	for(i = 0; i < net.lenlayers; ++i)
	{
		for (j = 0; j < net.numLayers[i]; ++j){
			printf("| %f", net.biases[pos]);
			pos += 1;	
		}
		printf("|\n");
	}
	printf("\nweight     :\n");	
	for (int k = 0; k < net.lenWeight; ++k)
	{
		printf("| %f |\n", net.weight[k]);
	}
	printf("\n");
}
Network makeNetWork(int len, int *sizes)
{ //To create a brand (and shiny) new NeuralNetwork 
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
	//lenweight
	//len first  = [0] * [1]
	//len second = [1] * [2]
	net.lenWeight = 0;
	for (int i = 0; i < net.lenlayers - 1; ++i)
	{
		net.lenWeight += net.numLayers[i] * net.numLayers[i + 1];
	}
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
{  //explicit content
	free(net.sizes);
	free(net.numLayers);
	//free(net.weight);
	//free(net.biases);
}

void printBashint(Bashint b)
{ //explicit content
	printf("Bashint : %f\nInput :", b.res);
	for (int i = 0; i < 2; ++i)
	{
		printf("%f ", b.input[i]);
	}
	printf("\n");
}
void freeBashint(Bashint b)
{ //explicit content
	free(b.input);
}
Bashint *makeBAshXor(int len, Network net)
{   //create a bash of randomely generated XOR int *inputlist and int res;
	//reusable ti create random things ;)
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
Bashint *suffleBashint(Bashint *bash, int len, time_t seed)
{ //to shuffle all elts in the BashintArray
	srand(seed);
	int pos;
	Bashint tmp;
	for (int i = 0; i < len; ++i)
	{
		pos = rand() % (len - i);
		tmp = bash[len - i];
		bash[len - i] = bash[pos];
		bash[pos] = tmp;
	}
	return bash;
}
void printdoublearray(double *array)
{
	while(*array)
	{
		printf("%f ", *array);
		array = array + 1;
	}
}
double *cutarray(double *array, int posmin, int posmax)
{
	printf("%d, %d\n", posmin, posmax);
	printdoublearray(array);
	int len = posmax - posmin;
	double *res = malloc(sizeof(double) * len);
	for (int i = 0; i < len; ++i)
	{
		res[i] = array[i + posmin];
	}
	return res;
}
double **backprop(Network *network, double *x, double y) //may be done .....
{
	double **res = malloc(sizeof(double *) * 2);
	Network net = *network;
	//init:
	double *nabla_b = malloc(sizeof(double) * net.lenBiases);
	int i;
	for(i = 0; i < net.lenBiases; ++i)
	{
		nabla_b[i] = 0;
	}
	double *nabla_w = malloc(sizeof(double) * net.lenWeight);
	for(i = 0; i <net.lenWeight; ++i)
	{
		nabla_w[i] = 0;
	}
	//feedforward
	double *activation = x;
	int min_len = (net.lenBiases > net.lenWeight ? net.lenWeight : net.lenBiases);
	double **activations = malloc(sizeof(double *) * min_len);
	double *zs = malloc(sizeof(double) * min_len);
	double z;
	int thisLayerWieght = 0;
	int nbneuronsleft = net.numLayers[0];
	int posmininweight = 0;
	for(i = 0; i < min_len - 1; ++i)
	{
		if(nbneuronsleft) // ==0
		{
			thisLayerWieght += 1;
			nbneuronsleft = net.numLayers[thisLayerWieght];
		}
		posmininweight += 1;
		printdoublearray(net.weight);
		printf("test\n");
		printNetwork(net);
		z = dotdouble(activation[i], 
			cutarray(net.weight, posmininweight, posmininweight + net.numLayers[thisLayerWieght]), 
			net.numLayers[thisLayerWieght]) + net.biases[i];
		printf("test\n");
		nbneuronsleft -= 1;
		zs[i] = z;
		activation[i] = sigmoid(z);
		activations[i] = activation;
	}
	double delta = (activations[0][min_len - 1] - y ) * sigmoidPrime(zs[min_len - 1]);
	double sp;
	for (int l = 2; l < net.lenlayers; ++l)
	{
		z = zs[min_len - l];
		sp = sigmoidPrime(z);
		//no transposition : useless....
		delta = dotdouble(delta, net.weight, net.lenWeight - l - 1) * sp;
		nabla_b[min_len - l] = delta;
		nabla_w[min_len - l] = dotdouble(delta, activations[l], min_len - l - 1) * sp;
	}
	//building result
	res[0] = nabla_b;
	res[1] = nabla_w;
	//free
	*network = net;
	free(activation);
	free(zs);
	free(nabla_b);
	free(nabla_w);
	freeNetwork(net);
	//I'm freeeee, from my worries
	return res;
}
Bashint *update_mini_bash(Bashint *mini_bash, size_t len_mini_bash, double eta, Network *network) //done
{	
	Network net = *network;
	//initialization:
	double *nabla_b = malloc(sizeof(double) * net.lenBiases);
	int i;
	for (i = 0; i < net.lenBiases; ++i)
	{
		net.biases[i] = 0;
	}
	double *nabla_w = malloc(sizeof(double) * net.lenWeight);
	for (i = 0; i < net.lenWeight; ++i)
	{
		net.weight[i] = 0;
	}
	//loop
	Bashint b;
	double *x;
	double y;
	double **deltas = malloc(sizeof(double *) * 2);
	int j;
	size_t w;
	for (w = 0; w < len_mini_bash; ++w)
	{
		b = mini_bash[w];
		x = b.input;
		y = b.res;
		deltas = backprop(network, x, y); //deltas[0] == delta_nabla_b and deltas[1] == delta_nabla_w
		for(j = 0; j < net.lenBiases; ++j)
		{
			nabla_b[j] += deltas[0][j]; 
		}
		for(j = 0; j < net.lenWeight; ++j)
		{
			nabla_w[j] += deltas[1][j];
		}

	}
	int k;
	for (k = 0; k < net.lenWeight; ++k)
	{
		net.weight[k] = net.weight[k] - (eta / len_mini_bash) * nabla_w[k];
	}
	for(k = 0; k < net.lenBiases; ++k)
	{
		net.biases[k] = net.biases[k] - (eta / len_mini_bash) * nabla_b[k];
	}
	//free
	*network = net;
	free(nabla_b);
	free(nabla_w);
	freeNetwork(net);
	return mini_bash;
}
double *feedforward(Network net, int *x)
{
	int min_len = (net.lenBiases > net.lenWeight ? net.lenWeight : net.lenBiases);
	for (int i = 0; i < min_len; ++i)
	{
		x[i] = sigmoid(dotdouble(net.weight[i], (double*)x, min_len) + net.biases[i]);
	}
	return (double *)x;
}
int argmax(double *array, int len)
{
	int res = 0;
	for (int i = 1; i < len; ++i)
	{
		if(array[i] > array[res])
			res = i;
	}
	return res;
}
double evaluate(Bashint *test_data, int len_test_data, Network net)
{
	double res = 0;
	double **test_result = malloc(sizeof(double *) * len_test_data);
	//building test_result
	for (int i = 0; i < len_test_data; ++i)
	{
		test_result[i] = malloc(sizeof(double) * 2);
		test_result[i][0] = (double)argmax(feedforward(net, (int *)test_data[i].input), (net.lenBiases > net.lenWeight ? net.lenWeight : net.lenBiases));
		//change test_result[i][1] is not neccesary :/
	}
	//compute test_result
	for (int i = 0; i < len_test_data; ++i)
	{
		if (test_result[0] == test_result[1])
			res += 1;
	}
	return res;
}
Network SGDV1(Network net, Bashint *training_data, size_t len_training_data, 
	int epoch, int mini_bash_size, double eta, Bashint *test_data, 
	size_t len_test_data)//V1
{
	/*
	printf("training_data : \n");
	for (size_t m = 0; m < len_training_data; ++m)
	{
		printBashint(training_data[m]);
		printf("training_data : %zu\n\n", m);
	}*/
	size_t n_test = len_test_data;
	size_t n = len_training_data;
	for (int j = 0; j < epoch; j += mini_bash_size)
	{
		training_data = suffleBashint(training_data, len_training_data, net.seed);
		Bashint *mini_batches = malloc(sizeof(Bashint) * mini_bash_size * n);
		for (size_t k = 0; k < n; ++k)
		{
			for (size_t i = k; i < k + mini_bash_size; ++i)
			{
				printBashint(mini_batches[k + i]);  
				mini_batches[k + i] = training_data[i];
			}
		}
		for (size_t l = 0; l < n; ++l)
		{
			mini_batches = update_mini_bash(mini_batches, mini_bash_size, eta, &net);
		}
		if(test_data)
		{
			printf("%d: %f / %zu\n", j, evaluate(test_data, len_test_data, net) , n_test);
		}
		else
			printf("Epoch %d complete.\n", j);
	}
	return net;
}
Bashint *cutarrayBashint(Bashint *b, int posmin, int posmax)
{
	int len = posmax - posmin;
	Bashint *res = malloc(sizeof(Bashint) * len);
	for (int i = 0; i < len; ++i)
	{
		res[i] = b[i + posmin];
	}
	return res;
}
Network SGD(Network net, Bashint *training_data, size_t len_training_data, 
	int epoch, int mini_bash_size, double eta, Bashint *test_data, 
	size_t len_test_data)//V2
{
	size_t n_test = len_test_data; 
	size_t n = len_training_data;
	Bashint **mini_batches = malloc(sizeof(Bashint) * n / mini_bash_size);
	size_t k;
	size_t l;
	for (int j = 0; j < epoch; ++j)
	{
		training_data = suffleBashint(training_data, len_training_data, net.seed);
		for (k = 0; k < n; k += mini_bash_size)
		{
			mini_batches[j + k] = cutarrayBashint(training_data, k, k + mini_bash_size);
		}
		for (l = 0; l < n / mini_bash_size; ++l)
		{
			mini_batches[l] = update_mini_bash(training_data, mini_bash_size, eta, &net);
		}
		if(test_data)
		{
			printf("%d: %f / %zu\n", j, evaluate(test_data, len_test_data, net) , n_test);
		}
		else
			printf("Epoch %d complete.\n", j);
	}	
	return net;
}
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
	argv[0]++; // warning removers
	int len = 3;// set number of layers
	int nbPixels = 900; // set number of input neurons
	size_t lenTest = 1000; //set number of test to occure
	int epoch = 30; //see tuto
	int mini_bash_size = 10; //see tuto
	double eta = 3.0;
	Network net = openNr(); // to open the previously saved Network
	if (net.len == -1) //no previously saved network
	{
		int type = 1; //see setNetwork funct to see why
		net = makeNetWork(len, setNetwork(type, nbPixels)); //create network
	}
	printNetwork(net);
	Bashint *testBash = makeBAshXor(lenTest, net); // create a Bashint List to improve the network
	net = SGD(net, testBash, lenTest, epoch, mini_bash_size, eta, testBash, mini_bash_size); // update network
	//saveNr(net);
	freeNetwork(net);
	return 0;
}