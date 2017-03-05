#include "contourExtract.h"

double** extract(double **im, int nl, int nc){
	double** res = alloue_image_double(nl, nc);
	for(int i = 0; i < nl; i++){
		for(int j = 0; j < nc; j++){
			if(i < nl-1 && im[i][j] * im[i+1][j] <= 0){
				res[i][j] = 255.0;
			}
			if(j < nc-1 && im[i][j] * im[i][j+1] <= 0){
				res[i][j] = 255.0;
			}
		}
	}
	return res;
}
