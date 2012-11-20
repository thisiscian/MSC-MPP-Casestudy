#ifndef __PARALLEL_RECONSTRUCT_H__
#define __PARALLEL_RECONSTRUCT_H__
#include "pgmio.h"
#include "stdio.h"
#include "reconstruct.h"
#include <mpi.h>

void p_reconstruct(void *buf, int nx_min, int nx_max, int ny, int iterations);
void reconstruct_image_segment(void *segment, void *edge, int nx_min, int nx_max, int ny);
#endif
