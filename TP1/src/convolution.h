/*
 * convolution.h
 *
 *  Created on: Feb 3, 2017
 *      Author: bouteloj
 */

#ifndef SRC_CONVOLUTION_H_
#define SRC_CONVOLUTION_H_

#include "pgm.h"
#include <stdio.h>
#include <math.h>

double* initmask(int i,double sigma);
int n_f_de_sigma(double sigma);
unsigned char** doConvolve(unsigned char** img,int nl, int nc, double sigma, int m);

#endif /* SRC_CONVOLUTION_H_ */
