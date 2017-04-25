#include "medianFilter.h"

// (i, j) est le centre du noyau
// Fonction pour obtenir le premier histogramme 
void getHistogram(unsigned char** im, int i, int j, int filterSize, int* h, int* sizeHisto){
    *sizeHisto = 256;
    for(int n = 0; n < *sizeHisto; n++){
    	h[n] = 0;
    }
    for(int p = i-filterSize; p < i+filterSize+1; p++){
        for(int k = j-filterSize; k < j+filterSize+1; k++){
            h[im[p][k]]++;
        }
    }
}

// ici (i, j) est le nouveau centre du noyau
void updateHistogram(unsigned char** im, int i, int j, int filterSize, int* h, int* sizeHisto){
    for(int p = i-filterSize; p<i+filterSize+1; p++){
        h[im[p][j-filterSize-1]]--;
        h[im[p][j+filterSize]]++;
    }
}

//renvoie la medianne dans k, et prend en argument l'histogramme h
void getMedian(int* h, int* sizeHisto, int filterSize, int* k){
    int sum = 0;
    *k = 0;
    while(sum < 2*filterSize*(filterSize+1) && (*k) < (*sizeHisto)){
        sum += h[*k];
        (*k)++;
    }
    (*k)--;
}

void applyMedianFilter(unsigned char** im, unsigned char** ims, int dimx, int dimy, int filterSize){
	copieimageuchar(im, ims, dimx, dimy);
	for(int i = filterSize; i < dimx - filterSize; i++){
		int histo[256];
		int j = filterSize;
		int sizeHisto = 0;
		int med = 0;
		getHistogram(im, i, j, filterSize, histo, &sizeHisto);
		getMedian(histo, &sizeHisto, filterSize, &med);
		ims[i][j] = med;
		for(j = filterSize + 1; j < dimy - filterSize; j++){
			updateHistogram(im, i, j, filterSize, histo, &sizeHisto);
			getMedian(histo, &sizeHisto, filterSize, &med);
			ims[i][j] = med;
		}
	}
}
