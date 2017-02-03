/*
 * convolution.c
 *
 *  Created on: Feb 3, 2017
 *      Author: bouteloj
 */

#include "convolution.h"



double* initmask(int i, double sigma){
	double * res;
	res=malloc((2*i+1)*sizeof(double));


	for(int k=0; k<i+1; k++){
		res[i+k]=exp(-(k*k)/(2*sigma*sigma));
		res[i-k]=res[i+k];
	}

	return res;

}

int n_f_de_sigma(double sigma){
	return 1;
}


double** doConvolve(unsigned char** img, int nl, int nc, double sigma){

	int(masksize)=n_f_de_sigma(sigma);


	double* mask=initmasque(masksize, sigma);

	double** imgd=alloue_image_double(nl,nc);
	imgd=imuchar2double(img, nl, nc);
	double** res=alloue_image_double(nl,nc);

	for (int i=0; i<nl;i++){
		for(int j=0; j<nc; j++){
			res[i][j]=0;
			for (int k=-masksize; k<masksize+1; k++){
				res[i][j]+=mask[k]*imgd[i][(j+nc+k)%nc];
			}
		}
	}
	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++) {
			res[i][j] = 0;
			for (int k = -masksize; k < masksize + 1; k++) {
				res[i][j] += mask[k] * imgd[(i+ nl + k) % nl][j];
			}
		}
	}


	libere_image(imgd);
	free(mask);
	return res;

}
