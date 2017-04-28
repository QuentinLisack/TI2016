#include "pgm.h"
#include <math.h>

#ifndef NLMEANSFILTER
#define NLMEANSFILTER

double calculatePatchDistance(int X, int Y, int x, int y, int r, double **im, int nl, int nc);
void applyNlMeansFilter(double** im, double** res, double s, int r, int t, int nl, int nc);

#endif
