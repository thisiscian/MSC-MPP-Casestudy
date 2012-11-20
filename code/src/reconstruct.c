#include "reconstruct.h"

void reconstruct(char *infilename, int nx, int ny, int iterations)
{
	int i;
	float buf[nx][ny];
	float edge[nx+2][ny+2];
	float reconst[nx+2][ny+2];
	char outfilename[256];

	pgmread(infilename, buf, nx, ny);
	addhalo(buf, edge, nx, ny);

	initialise_reconstruct(reconst, nx, ny);
	for(i=0; i<iterations;i++)
	{
		reconstruct_image(reconst, edge, nx, ny); 
	}
	removehalo(reconst, buf, nx, ny);
	sprintf(outfilename, "../output_files/reconstruct_%dx%d_%d-iterations.pgm", nx, ny, iterations);
	pgmwrite(outfilename, buf, nx, ny);
	
}

void initialise_reconstruct(void *reconstruct_in, int nx, int ny)
{
	int i,j;
	float *reconst = (float *) reconstruct_in;
	for(j=0;j<ny+2;j++)
	{
		for(i=0;i<nx+2;i++)
		{
			reconst[i*(ny+2)+j] = 255.0;
		}
	}	
}

void reconstruct_image(void *reconst, void *edge_in, int nx, int ny)
{
	int i,j;
	float *old = (float *) reconst;
	float new[(nx+2)*(ny+2)];
	float *edge = (float *) edge_in;
	for(j=1;j<ny+1;j++)
	{
		for(i=1;i<nx+1;i++)
		{
			new[i*(ny+2)+j] = reconstruct_point(old[(i-1)*(ny+2)+j], old[(i+1)*(ny+2)+j], old[i*(ny+2)+(j-1)],old[i*(ny+2)+(j+1)], edge[i*(ny+2)+j]);
		}
	}	
	for(j=1;j<ny+1;j++)
	{
		for(i=1;i<nx+1;i++)
		{
			old[i*(ny+2)+j] = new[i*(ny+2)+j];
		}
	}	
	
}

float reconstruct_point(float old_left, float old_right, float old_up, float old_down, float edge)
{
	return 0.25*(old_left+old_right+old_up+old_down-edge);
}

void removehalo(void *image_in, void *buf_out, int nx, int ny)
{
	int i,j;
	float *buf = (float *) buf_out;
	float *image = (float *) image_in;
	for(j=0;j<ny;j++)
	{
		for(i=0;i<nx;i++)
		{
			buf[i*ny+j] = image[(i+1)*(ny+2)+(j+1)];
		}
	}	
}

void addhalo(void *buf_in, void *image_out, int nx, int ny)
{
	int i,j;
	float *buf = (float *) buf_in;
	float *image = (float *) image_out;
	for(j=0;j<ny+2;j++)
	{
		for(i=0;i<nx+2;i++)
		{
			if(i==0 || i==nx+1 || j==0 || j==ny+1)
			{
				image[i*(ny+2)+j] = 255.0;
			}
			else
			{
				image[i*(ny+2)+j] = buf[(i-1)*ny+(j-1)];
			}
		}
	}	
}
