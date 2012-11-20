#include "edgeview.h"

int main()
{
	printf("\n\tRunning 'edgeview':\n\t");
	edgeview("../input_files/edge192x128.pgm", 192, 128);
	printf("\n\tRunning 'reconstruct':\n\t");
	reconstruct("../input_files/edge192x128.pgm", 192, 128);
	printf("\n\tCode Completed!\n\n");
	return 0;
}
