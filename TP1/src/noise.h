/*
 * noise.h
 *
 *  Created on: Apr 28, 2017
 *      Author: bouteloj
 */

#include "pgm.h"
#include <math.h>
#include <stdlib.h>

#ifndef SRC_NOISE_H_
#define SRC_NOISE_H_


double** initmask();
double** convolve(double ** im, double ** mask, int nl, int nc);
double doFindNoise(unsigned char** im,int nl, int nc, int tailleBlocs, double percentile);
int localvar(double** imd, int nl, int nc, int i, int j, int t);
#endif /* SRC_NOISE_H_ */
