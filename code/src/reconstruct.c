#include "reconstruct.h"

void reconstruct(char *infilename, int M, int N, int iterations)
{
	int i;
	float buf[M][N];
	float edge[M+2][N+2];
	float reconst[M+2][N+2];
	char outfilename[256];

	pgmread(infilename, buf, M, N);
	addhalo(buf, edge, M, N);

	initialise_reconstruct(reconst, M, N);
	for(i=0; i<iterations;i++)
	{
		reconstruct_image(reconst, edge, M, N); 
	}
	removehalo(reconst, buf, M, N);
	sprintf(outfilename, "../output_files/reconstruct_%dx%d_%d-iterations.pgm", M, N, iterations);
	pgmwrite(outfilename, buf, M, N);
	
}

void initialise_reconstruct(void *reconstruct_in, int M, int N)
{
	int i,j;
	float *reconst = (float *) reconstruct_in;
	for(j=0;j<N+2;j++)
	{
		for(i=0;i<M+2;i++)
		{
			reconst[i*(N+2)+j] = 255.0;
		}
	}	
}

void reconstruct_image(void *reconst, void *edge_in, int M, int N)
{
	int i,j;
	float *old = (float *) reconst;
	float new[(M+2)*(N+2)];
	float *edge = (float *) edge_in;
	for(j=1;j<N+1;j++)
	{
		for(i=1;i<M+1;i++)
		{
			new[i*(N+2)+j] = reconstruct_point(old[(i-1)*(N+2)+j], old[(i+1)*(N+2)+j], old[i*(N+2)+(j-1)],old[i*(N+2)+(j+1)], edge[i*(N+2)+j]);
		}
	}	
	for(j=1;j<N+1;j++)
	{
		for(i=1;i<M+1;i++)
		{
			old[i*(N+2)+j] = new[i*(N+2)+j];
		}
	}	
	
}

float reconstruct_point(float old_left, float old_right, float old_up, float old_down, float edge)
{
	return 0.25*(old_left+old_right+old_up+old_down-edge);
}

void removehalo(void *image_in, void *buf_out, int M, int N)
{
	int i,j;
	float *buf = (float *) buf_out;
	float *image = (float *) image_in;
	for(j=0;j<N;j++)
	{
		for(i=0;i<M;i++)
		{
			buf[i*N+j] = image[(i+1)*(N+2)+(j+1)];
		}
	}	
}

void addhalo(void *buf_in, void *image_out, int M, int N)
{
	int i,j;
	float *buf = (float *) buf_in;
	float *image = (float *) image_out;
	for(j=0;j<N+2;j++)
	{
		for(i=0;i<M+2;i++)
		{
			if(i==0 || i==M+1 || j==0 || j==N+1)
			{
				image[i*(N+2)+j] = 255.0;
			}
			else
			{
				image[i*(N+2)+j] = buf[(i-1)*N+(j-1)];
			}
		}
	}	
}
