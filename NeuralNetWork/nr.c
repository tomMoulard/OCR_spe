//made by moular_b
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
{  //do a dot mathematical function :3 coucou
	double res = 0;
	if (coeff == 0 || len == 0)
		return 0;
	//printf("dot : %f * (", coeff);
	for (int i = 0; i < len; ++i)
	{
		//printf("%f , ", a[i]);
		res += a[i] * coeff;
	}
	//printf(" ) = %f\n", res);
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
//########################prints#################################
void printArrayIntLen(int *array, int len)
{  //explicit content
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", array[i]);
	}
}

void printArrayIntEnd(int *beg, int *end)
{  //explicit content
	for(; beg < end; ++beg)
		printf("%d\n", *beg);
}
void printNetwork(Network net)
{  //explicit content
	int i, j;
	printf("#~~~~~~~~~~~ NETWORK ~~~~~~~~~~~#\n");
	printf("|lenLayers  : %d                 |\n", net.lenlayers);
	printf("|numLayers  :                   |\n|");
	for(i = 0; i < net.lenlayers; ++i)
	{
		printf("%d ", net.numLayers[i]);
	}
	printf("                         |\n|seed       : %ld        |\n", net.seed);
	printf("|len        : %d                 |\n", net.len);
	printf("|lenBiases  : %d                 |\n", net.lenBiases);
	printf("|lenWeight  : %d                 |\n", net.lenWeight);
	printf("|size       :                   |\n|");
	printArrayIntLen(net.sizes, net.len);
	printf("                         |\n|biases     :                   |\n");
	int pos = 0;
	for(i = 0; i < net.lenlayers; ++i)
	{
		for (j = 0; j < net.numLayers[i]; ++j){
			printf("| %f", net.biases[pos]);
			pos += 1;	
		}
		printf("|\n");
	}
	printf("|                               |\n|weight     :                   |\n");	
	for (int k = 0; k < net.lenWeight; ++k)
	{
		printf("| %d :  %f |               |\n", net.lenWeight, net.weight[k]);
	}
	printf("#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#\n");
}
void printNetworkArray(Network *a)
{
	while(a)
	{
		printNetwork(*a);
		a += 1;
	}
}
void printBashint(Bashint b)
{ //explicit content
	printf("#~~~~~~~~~ Bashint ~~~~~~~~#\n");
	printf("|res : %f            |\n|Input : ", b.res);
	for (int i = 0; i < 2; ++i)	
	{
		printf("%f ", b.input[i]);
	}
	printf("|\n#~~~~~~~~~~~~~~~~~~~~~~~~~~#\n");
}
void printBashintArray(Bashint *a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf(" Bashint n° %d\n", i);
		printBashint(a[i]);
	}
}
void printdoublearray(double *array)
{
	while(*array)
	{
		printf("%f ", *array);
		array = array + 1;
	}
}
Network makeNetWork(int len, int *sizes)
{ //To create a brand (and shiny) new NeuralNetwork 
	Network net;
	//lenLayers
	net.lenlayers = 3;
	//numlayers
	net.numLayers = sizes;
	//lenbiases
	net.lenBiases = sizes[0];
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
	net.biases = malloc(sizeof(double) * net.lenBiases);
	for (int i = 0; i < net.lenBiases; ++i)
	{
		net.biases[i] = ((double)rand()/(double)RAND_MAX);
	}
	//lenweight
	//len first  = [0] * [1]
	//len second = [1] * [2]
	net.lenWeight = 0;
	for (int i = 0; i < net.lenlayers - 1; ++i)
	{
		net.lenWeight += net.numLayers[i] * net.numLayers[i + 1];
	}
	//*weight
	net.weight = malloc(sizeof(double) * net.lenWeight);
	for (int j = 0; j < net.lenWeight; ++j)
	{
		net.weight[j] = ((double)rand()/(double)RAND_MAX);
	}
	//lenWeight
	return net;
}
void freeNetwork(Network net)
{  //explicit content
	free(net.sizes);
	free(net.weight);
	free(net.biases);
}
void freeBashint(Bashint b)
{ //explicit content
	free(b.input);
}
void freedouble2star(double **a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		free(a[i]);
	}
	free(a);
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
 	//printBashintArray(res, len);
 	return res;
}
Bashint *suffleBashint(Bashint *bash, int len, time_t seed)
{ //to shuffle all elts in the BashintArray
	srand(seed);
	int pos;
	Bashint tmp;
	for (int i = 0; i < len - 1; ++i)
	{
		pos = rand() % (len - i - 1);
		tmp = bash[len - i - 1];
		bash[len - i - 1] = bash[pos];
		bash[pos] = tmp;
	}
	return bash;
}
double *cutarray(double *array, int posmin, int posmax)
{
	//printf("cut : %d, %d\n", posmin, posmax);
	//printdoublearray(array);
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
	double *resT;	
	for(i = 0; i < min_len - 1; ++i)
	{
		if(nbneuronsleft) // ==0
		{
			thisLayerWieght += 1;
			nbneuronsleft = net.numLayers[thisLayerWieght];
		}
		posmininweight += 1;
		resT = cutarray(net.weight, posmininweight, posmininweight + net.numLayers[thisLayerWieght]);
		z = dotdouble(activation[i], resT, net.numLayers[thisLayerWieght]);
		z +=+ net.biases[i];
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
	free(activations);
	free(zs);
	free(nabla_b);
	free(nabla_w);
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
		nabla_b[i] = 0;
	}
	double *nabla_w = malloc(sizeof(double) * net.lenWeight);
	for (i = 0; i < net.lenWeight; ++i)
	{
		nabla_w[i] = 0;
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
	*network = net;
	//free
	free(nabla_b);
	free(nabla_w);
	//freeNetwork(net);
	return mini_bash;
}
double *feedforward(Network net, double *x)
{
	int min_len = (net.lenBiases > net.lenWeight ? net.lenWeight : net.lenBiases);
	for (int i = 0; i < min_len; ++i)
	{
		x[i] = sigmoid(dotdouble(net.weight[i], x, min_len) + net.biases[i]);
	}
	return x;
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
	int min_len = (net.lenBiases > net.lenWeight ? net.lenWeight : net.lenBiases);
	//building test_result
	for (int i = 0; i < len_test_data; ++i)
	{
		test_result[i] = malloc(sizeof(double) * 2);
		test_result[i][0] = (double)argmax(feedforward(net, test_data[i].input), min_len);
		test_result[i][1] = test_data[i].res;
	}
	//compute test_result
	for (int i = 0; i < len_test_data; ++i)
	{
		//printf("evaluate : x = %f et y = %f\n", test_result[i][0], test_result[i][1]);
		if (test_result[i][0] == test_result[i][1])
			res += 1;
	}
	freedouble2star(test_result, len_test_data);
	return res;
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
	Bashint **mini_batches = malloc(sizeof(Bashint) * epoch * n);
	size_t k;
	size_t l;
	for (int j = 0; j < epoch; ++j)
	{
		training_data = suffleBashint(training_data, len_training_data, net.seed);
		//printBashintArray(training_data, len_training_data);
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
			printf("%2d: %f / %zu\n", j, evaluate(test_data, len_test_data, net) , n_test);
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
	int *res = malloc(sizeof(int) * 3);
	if (type == 1) //xor -> set len to 3
	{
		*res       = 2 ; //input neurons
		*(res + 1) = 3 ;
		*(res + 2) = 1 ; //output neurons
	}
	if (type == 2)//picture recognition [0-9]
	{
		*res       = nbPixels;
		*(res + 1) = 100;//fixme
		*(res + 2) = 10;
	}
	if (type == 3)//picture recognition [0-9a-zA-Z]
	{
		*res       = nbPixels;
		*(res + 1) = 100;//fixme
		*(res + 2) = 62;
	}
	if (type == 4)//picture recognition [0-9]
	{ 
		*res       = nbPixels;
		*(res + 1) = 100; //fixme
		*(res + 2) = 185;
	}
	return res;
}

//convert A char to int : A = strtoul(A, NULL, 10);
int main(int argc, char *argv[])
{
	//if (argc < 2)
	//	errx(1, "Please input a valid input :\n	- number of pixel in width\n 	- list of pixels\n");
	argv[0]++; // warning removers
	argc++;
	int len = 3;// set number of layers
	int nbPixels = 900; // set number of input neurons
	size_t lenTest = 1000; //set number of test to occure
	int epoch = 1000; //see tuto
	int mini_bash_size = 100; //see tuto
	double eta = 3.0;
	Network net = openNr(); // to open the previously saved Network
	if (net.len == -1) //no previously saved network
	{
		int type = 1; //see setNetwork funct to see why
		net = makeNetWork(len, setNetwork(type, nbPixels)); //create network
	}
	printNetwork(net);
	Bashint *testBash = makeBAshXor(lenTest, net); // create a Bashint List to improve the network
	net = SGD(net, testBash, lenTest, 
			epoch, mini_bash_size, 
			eta, testBash, mini_bash_size); // update network
	printNetwork(net);
	//saveNr(net);
	freeNetwork(net);
	return 0; 
}