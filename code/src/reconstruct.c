#include "reconstruct.h"

void reconstruct(char *infilename, int M, int N)
{
	float buf[M][N];
	float image[M+2][N+2];
	char outfilename[256];
	pgmread(infilename, buf, M, N);
	sprintf(outfilename, "../output_files/reconstruct_initial_%dx%d.pgm", M, N);
	pgmwrite(outfilename, buf, M, N);
	addhalo(buf, image, M, N);
	sprintf(outfilename, "../output_files/reconstruct_halo_%dx%d.pgm", M, N);
	pgmwrite(outfilename, image, M+2, N+2);
}

void addhalo(void *buf_in, void *image_in, int M, int N)
{
	int i,j;
	float *buf = (float *) buf_in;
	float *image = (float *) image_in;
	for(j=N-1;j>=0;j--)
	{
		for(i=0;i<M+2;i++)
		{
			if(i==0 || i==M+1 || j==0 || j==N+1)
			{
				image[i*N+j] = 255.0;
			}
			else
			{
				image[i*N+j] = buf[(i-1)*N+(j-1)];
			}
		}
	}	
}
