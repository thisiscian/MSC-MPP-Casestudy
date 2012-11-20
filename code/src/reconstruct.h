#ifndef __RECONSTRUCT_H__
#define __RECONSTRUCT_H__
#include "pgmio.h"
#include "stdio.h"

void reconstruct(char *filename, int M, int N, int iterations);
void addhalo(void *buf, void *image, int M, int N);
void removehalo(void *image, void *buf, int M, int N);
float reconstruct_point(float old_left, float old_right, float old_up, float old_down, float edge);
void initialise_reconstruct(void *reconstruct_in, int M, int N);
void reconstruct_image(void *reconstruct_in, void *edge, int M, int N);
float reconstruct_point(float old_left, float old_right, float old_up, float old_down, float edge);
#endif
