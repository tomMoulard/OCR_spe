//made by moular_b
#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

int xor(int a, int b)
{
	return (a*(b ? 0 : 1) || (a ? 0 : 1)*b) ? 1 : 0;
}

//ulitity
double sigmoid(double z)
{
	return 1.0 / (1.0 + exp(z));
}

/*
	Making a function to create a new neural network in a list(Array)
	Array[0] = biasesDeb
	Array[1] = weightDeb
	Array[2] = input aka array (no uppercase)
*/
int **makeNetWork(int len, int *array)
{
	int **Array = malloc(5);
	int *biasesDeb = malloc(len); 
	int *tmp = biasesDeb;
	//random :
	srand(time(NULL));
	for(; tmp < biasesDeb + len; ++tmp)
	{
		*tmp = rand()%2; // init biase value
	}
	//free(tmp);
	int *weightDeb = malloc(len);
	tmp = weightDeb;
	for(; tmp < weightDeb + len; ++tmp)
	{
		*tmp = rand()%2; // init biase value
	}
	*(Array+0) = biasesDeb; //biasesFin = biasesDeb + len;
	*(Array+1) = weightDeb; //weightFin = weightDeb + len;
	*(Array+2) = array;	
	return Array;	
}

int **dot(int *a, int *b, int leni, int lenj)
{
	int *resj = malloc(lenj * sizeof(int));
	int **res = malloc(leni * sizeof(resj));
	for (int i = 0; i < leni; ++i)
	{
		for (int j = 0; j < lenj; ++j)
		{
			
		}
	}
	return res;
}

//convert A char to int : A = strtoul(A, NULL, 10);
int main(int argc, char *argv[])
{
	if (argc < 2)
		errx(1, "Please input a valid input :\n	- number of pixel in width\n 	- list of pixels\n");
	int *net = malloc(3 * sizeof (int));
	//nb neurons for each layers
	*net     = 1; //first layer
	*(net+1) = 1; //second layer
	*(net+2) = 1; //third layer
	int len = 3;
	int **test = makeNetWork(len, net);
	int a;
	for (int b = 0, w = 0; b < len; ++b)
	{
		/* code */
	}
	argv[0]++;
	return 0;
}