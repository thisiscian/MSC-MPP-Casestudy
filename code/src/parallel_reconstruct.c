#include "parallel_reconstruct.h"

void p_reconstruct(void *buf_in, int nx_min, int nx_max, int ny, int iterations)
{
	int i,j;
	int nx = nx_max-nx_min;
	float segment[nx+2][ny+2];
	float *buf = (float *) buf_in;

	initialise_reconstruct(segment, nx, ny);
	for(i=0; i<iterations;i++)
	{
		reconstruct_image_segment(segment, buf, nx_min, nx_max, ny); 
	}
	for(j=0;j<ny;j++)
	{
		for(i=nx_min;i<nx_max;i++)
		{
			buf[i * ny+j] = segment[i-nx_min+1][j+1];
		}
	}	
	
}

void reconstruct_image_segment(void *segment, void *edge_in, int nx_min, int nx_max, int ny)
{
	int i,j;
	int nx = nx_max-nx_min;
	float *old = (float *) segment;
	float new[(nx+2)*(ny+2)];
	float *edge = (float *) edge_in;
	for(j=1;j<ny+1;j++)
	{
		for(i=1;i<nx+1;i++)
		{
			new[i*(ny+2)+j] = reconstruct_point(old[(i-1)*(ny+2)+j], old[(i+1)*(ny+2)+j], old[i*(ny+2)+(j-1)],old[i*(ny+2)+(j+1)], edge[(i+nx_min)*ny+j]);
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
