#include "edgeview.h"

int main()
{
	printf("\nRunning 'edgeview':\n");
	edgeview("../input_files/edge192x128.pgm", 192, 128);
	printf("\nRunning 'reconstruct':\n");
	reconstruct("../input_files/edge192x128.pgm", 192, 128, 0);
	reconstruct("../input_files/edge192x128.pgm", 192, 128, 1);
	reconstruct("../input_files/edge192x128.pgm", 192, 128, 10);
	reconstruct("../input_files/edge192x128.pgm", 192, 128, 100);
	reconstruct("../input_files/edge192x128.pgm", 192, 128, 1000);
	printf("\nCode Completed!\n\n");
	return 0;
}
