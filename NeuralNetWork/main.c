#include "nr2.h"

int main(int argc, char *argv[])
{
	if(argc == 2){
		Network *net = OpenNr(argv[1]);
		trainNetFinal(net);
		saveNr(net, argv[1]);
	}
	return 0;
}