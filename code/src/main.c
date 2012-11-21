#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main()
{
	int iterations = 1000;
	char infilename[256] = "../input_files/edge192x128.pgm";
	
	p_reconstruct(infilename, iterations);
	//reconstruct(infilename, iterations);
	return 0;
}
