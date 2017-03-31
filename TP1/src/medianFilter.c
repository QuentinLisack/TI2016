#include "medianFilter.h"

// (i, j) est le centre du noyau
void getHistogram(unsigned char** im, int i, int j, int filterSize, int* h, int* sizeHisto){
    h = mallocOrDie(sizeof(unsigned int), "allocation histogram");
    *sizeHisto = 1;
    for(int p = i-filterSize; p < i+filterSize+1; p++){
        for(int k = j-filterSize; k < j+filterSize+1; k++){
            if(*sizeHisto <= im[p][k]){
                reallocOrDie(h, im[p][k]+1, "realloc histogram");
                for(int m = *sizeHisto; m < im[p][k]+1; m++){
                    h[m] = 0;
                }
                *sizeHisto = im[p][k]
            }
            h[im[p][k]]++;
        }
    }
}

// ici (i, j) est le nouveau centre du noyau
void updateHistogram(unsigned char** im, int i, int j, int filterSize, int* h, int* sizeHisto){
    for(int p = i-filterSize; p<i+filterSize+1; p++){
        h[im[p][j-n-1]]--;
        if(*sizeHisto <= im[p][j-n-1]){
            reallocOrDie(h, im[p][j-n-1]+1, "realloc histogram");
            for(int m = *sizeHisto; m < im[p][j-n-1]+1; m++){
                h[m] = 0;
            }
            *sizeHisto = im[p][j-n-1]
        }
        h[im[p][j+n]]++;
    }
}

void getMedian(int* h, int* sizeHisto, int sizeFilter, int* k){
    int sum = 0;
    *k = 0;
    while(sum < 2*sizeFilter*(sizeFilter+1)){
        sum += h[*k];
        (*k)++;
    }
    (*k)--;
}
