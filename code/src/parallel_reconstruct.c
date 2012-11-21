#include "parallel_reconstruct.h"

void p_reconstruct(char *infilename, int iterations)
{
	int i,j;
	int nx, ny;
	int nx_min, nx_max, nx_range;
	int rank, nproc;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);

	pgmsize(infilename, &nx, &ny);
	nx_min = (int)((double)rank/(double)nproc*nx);
	nx_max = (int)((double)(rank+1)/(double)nproc*nx);
	if(nx_max > nx) nx_max = nx;
	nx_range = nx_max-nx_min;

	float buf[nx][ny];
	float edge[nx_range][ny];
	float out[nx_range][ny];
	float segment[nx_range+2][ny+2];
	if(rank == 0)
	{	
		pgmread(infilename, buf, nx, ny);
	}
	MPI_Scatter(buf, ny*nx_range, MPI_FLOAT, edge, ny*nx_range, MPI_FLOAT, 0, MPI_COMM_WORLD);
	initialise_segment(segment, nx_range+2, ny+2);
	for(i=0; i<iterations;i++)
	{
		reconstruct_image_segment(segment, edge, nx_min, nx_max, ny); 
	}
	removehalo(segment, out, nx_range, ny);
	MPI_Gather(out, ny*nx_range, MPI_FLOAT, buf, ny*nx_range, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if(rank == 0)
	{
		char outfilename[256];
		sprintf(outfilename, "../output_files/p%d_reconstruct_%di.pgm", nproc, iterations);
		pgmwrite(outfilename, buf, nx, ny);
	}
	MPI_Finalize();
}
