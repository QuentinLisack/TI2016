/*
 * convolution.c
 *
 *  Created on: Feb 3, 2017
 *      Author: bouteloj
 */

#include "convolution.h"


double* initmask(int i, double sigma){
	double * res;
	double sum=0;
	res=malloc((2*i+1)*sizeof(double));


	for(int k=0; k<i+1; k++){
		res[i+k]=exp(-(k*k)/(2*sigma*sigma));
		res[i-k]=res[i+k];

	}

	for(int k=0; k<2*i+1; k++){
			sum+=res[k];
		}

	for(int k=0; k<2*i+1; k++){
		res[k]=res[k]/sum;
	}
	printf("\n %f \n",sum);
	return res;

}
//brutal
int n_f_de_sigma(double sigma){
	int i=1;
	while (i<3*sigma){i++;}
	return i;
}


unsigned char** doConvolve(unsigned char** img, int nl, int nc, double sigma){

	int masksize =n_f_de_sigma(sigma);


	double* mask=initmask(masksize, sigma);

	double** imgd=alloue_image_double(nl,nc);
	imgd=imuchar2double(img, nl, nc);
	double** res=alloue_image_double(nl,nc);
	unsigned char ** resc=alloue_image(nl,nc);


	for (int i=0; i<nl;i++){
		for(int j=0; j<nc; j++){
			res[i][j]=0;
			for (int k=-masksize; k<masksize+1; k++){
				res[i][j]+=mask[masksize+k]*imgd[i][(j+nc+k)%nc];
			}
		}
	}
	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++) {
			res[i][j] = 0;
			for (int k = -masksize; k < masksize + 1; k++) {
				res[i][j] += mask[masksize+k] * imgd[(i+ nl + k) % nl][j];
			}
		}
	}

	double sum=0;
	for (int i=0;i<2*masksize+1;i++){
		sum+=mask[i];
		printf("%f ",mask[i]);
	}
	printf("\n %i %f \n",masksize,sum);

	resc=imdouble2uchar(res,nl,nc);
	libere_image(res);
	libere_image(imgd);
	free(mask);
	return resc;

}
