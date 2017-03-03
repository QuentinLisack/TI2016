/*
 * contourGradient.h
 *
 *  Created on: Mar 3, 2017
 *      Author: bouteloj
 */

#ifndef SRC_CONTOURGRADIENT_H_
#define SRC_CONTOURGRADIENT_H_

#include "pgm.h"
#include <stdio.h>
#include <math.h>
#include "convolution.h"

double** initPrewitt1();
double** initPrewitt2();
double** initSobel1();
double** initSobel2();

//method=1 pour prewitt, 2 pour sobel
double** calculateGrad(double** img,int nl,int nc,int method);

double calculSeuil(double**grad,int nl, int nc);

double** threshold(double** grad,int nl,int nc);

double** doFindContours(double** im,int nl, int nc, int method);

double** doAll(unsigned char** im,int nl, int nc, int method,double sigma);

#endif /* SRC_CONTOURGRADIENT_H_ */
