#include "pgm.h"
#include <math.h>

#ifndef ADAPTATIVERECURSIVEFILTER
#define ADAPTATIVERECURSIVEFILTER

double calculateWeightsAdaptative(int x, int y, double k, double** im, int nl, int nc);
void applyAdaptativeRecursiveFilter(double** ims, double** imd, double k, int nl, int nc, double TOL);

#endif
