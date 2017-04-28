#include "bilateralFilter.h"

double calculateWeightsBilateral(int x, int y, int i, int j, double s1, double s2, double** im, int nl, int nc){
	double res = exp(- (i*i + j*j)/(2*s1*s1));
	res *= exp(- pow(im[(x+i+nl)%nl][(y+j+nc)%nc] - im[x][y], 2)/(2*s2*s2));
	return res;
}

void applyBilateralFilter(double** ims, double** imd, double s1, double s2, int nl, int nc){
	copieimagedouble(ims, imd, nl, nc);
	int t = floor(3*s1)+1;
	double newPix;
	double w;
	double temp;
	for(int x = 0; x < nl; x++){
		for(int y = 0; y < nc; y++){
			newPix = 0;
			w = 0;
			for(int i = -t; i < t+1; i++){
				for(int j = -t; j < t+1; j++){
					temp = calculateWeightsBilateral(x, y, i, j, s1, s2, ims, nl, nc);
					newPix += temp * ims[(x+i+nl)%nl][(y+j+nc)%nc];
					w += temp;
				}
			}
			imd[x][y] = newPix/w;
		}
	}
}
