#include "pgm.h"
#include <math.h>

#ifndef BILATERALFILTER
#define BILATERALFILTER

double calculateWeightsBilateral(int x, int y, int i, int j, double s1, double s2, double** im);
void applyBilateralFilter(double** ims, double** imd, double s1, double s2, int nl, int nc);

#endif
