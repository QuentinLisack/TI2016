#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "pgm.h"

#ifndef LIBFT
#define LIBFT

double** GaussienneFT(int dimx, int dimy, double sigma);
void applyFilter(double **im_r, double **im_i, double **filter_r, double **filter_i, int dimx, int dimy);
void getModule(double **im_r, double **im_i, double **mod, int dimx, int dimy);

#endif
