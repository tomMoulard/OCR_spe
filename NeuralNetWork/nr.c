//made by moular_b
#include <stdio.h>
#include <math.h>
#include <err.h>
#include <assert.h>
#include <stdlib.h>

int xor(int a, int b)
{
	return (a*(b ? 0 : 1) || (a ? 0 : 1)*b) ? 1 : 0;
}

//ulitity
double sigmoid(double z)
{
	return 1 / (1 + exp(z));
}

/*
	Making a function to create a new neural network in a list(Array)
	Array[0] = nb layers
	Array[1] = size
	Array[2] = biases
*/
/*
int makeNetWork(int len, int *array)
{

}
*/


//convert A char to int : A = strtoul(A, NULL, 10);
int main(int argc, char *argv[])
{
	if (argc < 2)
		errx(1, "Please input a valid input :\n	- number of pixel in width\n 	- list of pixels\n");
	printf("%f\n", sigmoid(0.5));;
	argv[0]++;
	return 0;
}