/*
 * convolution.h
 *
 *  Created on: Feb 3, 2017
 *      Author: bouteloj
 */

#ifndef SRC_CONVOLUTION_H_
#define SRC_CONVOLUTION_H_

#include "pgm.h"


double* initmask(int i);
int n_f_de_sigma(double sigma);
void doConvolve(unsigned char** img);

#endif /* SRC_CONVOLUTION_H_ */
