/*
 * noise.c
 *
 *  Created on: Apr 28, 2017
 *      Author: bouteloj
 */

#include "noise.h"

double** initmask(){
	double** res=alloue_image_double(3,3);

	res[0][0]=0;
	res[0][1]=-1;
	res[0][2]=0;
	res[1][0]=-1;
	res[1][1]=5;
	res[1][2]=-1;
	res[2][0]=0;
	res[2][1]=-1;
	res[2][2]=0;

	return res;
}



double** convolve(double ** im, double ** mask, int nl, int nc){
	double ** res=alloue_image_double(nl,nc);

	for(int i=0;i<nl;i++){
			for (int j=0;j<nc;j++){

				for (int x=0; x<3;x++){
					for (int y=0;y<3;y++){
						res[i][j]+=im[(i-x+1+nl)%nl][(j-y+1+nc)%nc]*mask[x][y];
					}
				}
			}
		}
	return res;
}

int localvar(double** imd, int nl, int nc, int i, int j, int t) {
	int res = 0;
	double mean = 0;
	double mean2 = 0;

	for (int k = -t; k < t+1; k++) {
		for (int l = -t; l < t+1; l++) {
			mean += imd[(i + k+nl) % nl][(j + l+nc) % nc];
			mean2+=imd[(i + k+nl) % nl][(j + l+nc) % nc]*imd[(i + k+nl) % nl][(j + l+nc) % nc];
		}
	}

	mean=mean/((2*t+1)*(2*t+1));
	mean2=mean2/((2*t+1)*(2*t+1));

	res=mean2-mean*mean;


	return res;

}


double doFindNoise(unsigned char** im, int nl, int nc, int tailleBlocs,
		double percentile) {
	if (percentile > 1) {
		exit(1);
	}
	int temp;
	double** imd = alloue_image_double(nl, nc);
	double** imd2 = alloue_image_double(nl, nc);

	imd = imuchar2double(im, nl, nc);
	double hist[65536];
	double** mask = initmask();
	imd2 = convolve(imd, mask, nl, nc);
	for (int i = 0; i << 65536; i++) {
		hist[i] = 0;
	}

	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++) {
			temp = localvar(imd, nl, nc, i, j, tailleBlocs);
			hist[temp] += 1;
		}
	}

	double test = percentile * nl * nc;
	for (int i = 1; i < 65536; i++) {
		hist[i] += hist[i - 1];
		if (hist[i] > test) {
			temp = i;
			break;

		}
	}

	libere_image(imd);
	libere_image(imd2);
	libere_image(mask);

	return 1.13 * temp;
}
