/*
 * contourGradient.c
 *
 *  Created on: Mar 3, 2017
 *      Author: bouteloj
 */

#include "contourGradient.h"

double** initPrewitt1(){
	double** res;
	res=alloue_image_double(3,3);
	for (int i=0;i<3;i++){
		res[i][0]=-1.0;
		res[i][2]=1.0;
	}
	return res;
}
double** initPrewitt2() {
	double** res;
	res = alloue_image_double(3, 3);

	for (int i = 0; i < 3; i++) {
		res[0][i] = -1;
		res[2][i] = 1;
	}
	return res;
}
double** initSobel1() {
	double** res;
	res = alloue_image_double(3, 3);
	res[0][0] = -1;
	res[1][0] = -2;
	res[2][0] = -1;
	res[0][1] = 0;
	res[1][1] = 0;
	res[2][1] = 0;
	res[0][2] = 1;
	res[1][2] = 2;
	res[2][2] = 1;
	return res;
}
double** initSobel2() {
	double** res;
	res = alloue_image_double(3, 3);
	res[0][0] = -1;
	res[0][1] = -2;
	res[0][2] = -1;
	res[2][0] = 1;
	res[2][1] = 2;
	res[2][2] = 1;
	return res;
}

//method=1 pour prewitt, 2 pour sobel
double** calculateGrad(double** img,int nl,int nc,int method){
	double** grad;
	grad=alloue_image_double(nl,nc);
	double temp1=0, temp2=0;
	double** mask1, **mask2;


	if (method==1){
		mask1=initPrewitt1();
		mask2=initPrewitt2();
	}else{
		mask1=initSobel1();
		mask2=initSobel2();
	}

	for(int i=1;i<nl-1;i++){
		for (int j=1;j<nc-1;j++){
			temp1=0;
			temp2=0;
			for (int x=0; x<3;x++){
				for (int y=0;y<3;y++){
					temp1+=img[i-x+1][j-y+1]*mask1[x][y];
					temp2+=img[i-x+1][j-y+1]*mask2[x][y];
				}
			}
			grad[i][j]=sqrt(temp1*temp1+temp2*temp2);
		}
	}

	libere_image(mask1);
	libere_image(mask2);

	return grad;

}

double calculSeuil(double**grad,int nl, int nc){
	return 30;
}


double** threshold(double** grad, int nl, int nc) {
	double** contours;
	contours = alloue_image_double(nl, nc);
	double seuil=calculSeuil(grad,nl,nc);

	for (int i = 1; i < nl - 1; i++) {
		for (int j = 1; j < nc - 1; j++) {
			if (grad[i][j]>seuil){
				contours[i][j]=254;
			}else{
				contours[i][j]=0;
			}
		}
	}

	libere_image(grad);
	return contours;
}

double** doFindContours(double** im,int nl, int nc, int method){
	double** grad;
	double** contours;
	grad=calculateGrad(im,nl,nc,method);
	contours=threshold(grad,nl,nc);
	return contours;
}

double** doAll(unsigned char** im,int nl, int nc, int method,double sigma, int m){

	unsigned char** im2;
	double **res;


	im2=doConvolve(im,nl,nc,sigma, m);
	res=doFindContours(imuchar2double(im2,nl,nc),nl,nc,method);
	libere_image(im2);
	return res;
}
