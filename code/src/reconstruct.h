#ifndef __RECOnySTRUCT_H__
#define __RECOnySTRUCT_H__
#include "pgmio.h"
#include "stdio.h"

void reconstruct(char *filename, int nx, int ny, int iterations);
void addhalo(void *buf, void *image, int nx, int ny);
void removehalo(void *image, void *buf, int nx, int ny);
float reconstruct_point(float old_left, float old_right, float old_up, float old_down, float edge);
void initialise_reconstruct(void *reconstruct_in, int nx, int ny);
void reconstruct_image(void *reconstruct_in, void *edge, int nx, int ny);
float reconstruct_point(float old_left, float old_right, float old_up, float old_down, float edge);
#endif
