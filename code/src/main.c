#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
int main()
{
	int rank, nproc;
	int nx, ny;
	int i,j;
	int nx_min, nx_max;
	int start_time, finish_time;
	char filename[256] = "../input_files/edge192x128.pgm";
	float **buf;
	
	MPI_Init(NULL, NULL);
	start_time = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	if(rank == 0)
	{
		printf("\nCode Starting...\n\n");
		pgmsize(filename, &nx, &ny);
		printf("rank=%d\nnproc=%d\n", rank, nproc);
		printf("nx=%d\nny=%d\n", nx, ny);
		buf = (float **) malloc (ny * sizeof(float *));
		for(i=0; i<ny;i++)
		{
			buf[i] = (float *)malloc(nx*sizeof(float));
		}
		for(j=0;j<nx;j++)
		{
			for(i=0;i<ny;i++)
			{
				buf[i][j] = 0.0;
			}
		}
		printf("last digit should be ~= %d\n", ny*nx);
		printf("mallocs done\nabout to read\n");
		pgmread(filename, buf, nx, ny);
		printf("file read\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	nx_min = ceil((double)rank/(double)nproc)*nx;
	nx_max = ceil((double)(rank+1)/(double)nproc)*nx;
	if(nx_max > nx) nx_max = nx;
	if(rank == 1)
	{
		printf("nx=%d\nny=%d\n", nx, ny);
	}
	p_reconstruct(buf, nx_min, nx_max, ny, 10);	
	finish_time = MPI_Wtime();
	if(rank == 0)
	{
		sprintf(filename, "../output_files/reconstruct_%dx%d_%d-iterations.pgm", nx, ny, 10);
		pgmwrite(filename, buf, nx, ny);
	}
	printf("\nCode Completed!\nTook %d second(s)\n\n", finish_time - start_time);
	MPI_Finalize();
	return 0;
}
