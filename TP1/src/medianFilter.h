#include "pgm.h"

#ifndef MEDIANFILTER
#define MEDIANFILTER

void getHistogram(unsigned char** im, int i, int j, int filterSize, int* h, int* sizeHisto);
void updateHistogram(unsigned char** im, int i, int j, int filterSize, int* h, int* sizeHisto);
void getMedian(int* h, int* sizeHisto, int sizeFilter, int* k);

#endif
