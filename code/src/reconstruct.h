#ifndef __RECONSTRUCT_H__
#define __RECONSTRUCT_H__
#include "pgmio.h"
#include "stdio.h"

void reconstruct(char *filename, int M, int N);
void addhalo(void *buf, void *image, int M, int N);
#endif
