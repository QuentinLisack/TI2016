#include "adaptativeRecursiveFilter.h"

double calculateWeightsAdaptative(int x, int y, double k, double** im){
	return exp(-(pow(im[x+1][y] - im[x-1][y], 2) + pow(im[x][y+1] - im[x][y-1], 2))/(2*k*k));
}

void applyAdaptativeRecursiveFilter(double** ims, double** imd, double k, int nl, int nc, double TOL){
	unsigned int isChanged = 1;
	double** tempImage1 = alloue_image_double(nl, nc);
	double** tempImage2 = alloue_image_double(nl, nc);
	double** tempPointer;
	double** weights = alloue_image_double(nl, nc);
	copieimagedouble(ims, tempImage1, nl, nc);
	copieimagedouble(ims, tempImage2, nl, nc);
	
	int numIter = 1;
	
	while(isChanged){
		printf("nombre d'iterations : %d \n", numIter);
		numIter++;
		
		isChanged = 0;
		//on remplit le tableau des poids
		for(int i = 1; i < nl-1; i++){
			for(int j = 1; j < nc-1; j++){
				weights[i][j] = calculateWeightsAdaptative(i, j, k, tempImage1);
			}
		}
		
		for(int i = 2; i < nl - 2; i ++){
			for(int j = 2; j < nc - 2; j++){
				double newPix = 0.0;
				double w = 0.0;
				for(int p = -1; p <= 1; p++){
					for(int k = -1;k <= 1; k++){
						newPix += weights[i + p][j + k] * tempImage1[i + p][j + k];
						w += weights[i + p][j + k];
					}
				}
				tempImage2[i][j] = newPix / w;
				
				if(abs(tempImage2[i][j] - tempImage1[i][j]) > TOL){
					isChanged = 1;
				}
			}
		}
		tempPointer = tempImage2;
		tempImage2 = tempImage1;
		tempImage1 = tempPointer;
	}
	copieimagedouble(tempImage2, imd, nl, nc);
}
