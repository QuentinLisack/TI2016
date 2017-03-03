#include "libFT.h"

double** GaussienneFT(int dimx, int dimy, double sigma){
	double ** res;
	double sum=0;
	res = alloue_image_double(dimx, dimy);

    if(!ispowerof2(dimx)){
        printf("dimx n'est pas une puissande de 2\n");
        printf("ici, dimx = %i\n", dimx);
    }

    if(!ispowerof2(dimy)){
        printf("dimy n'est pas une puissande de 2\n");
        printf("ici, dimy = %i\n", dimy);
    }

    for(int x = -dimx/2; x < dimx/2; x++){
        for(int y = -dimy/2; y < dimy/2; y++){
            res[x + dimx/2][y + dimy/2] = exp(- 2 * sigma * sigma * M_PI * M_PI * (((double) (x*x))/(dimx*dimx) + ((double) (y*y))/(dimy*dimy)));
        }
    }
	return res;
}

void applyFilter(double **im_r, double **im_i, double **filter_r, double **filter_i, int dimx, int dimy){
    double i, r;
    for(int n = 0; n < dimx; n++){
        for(int p = 0; p < dimy; p++){
            r = im_r[n][p];
            i = im_i[n][p];
            im_r[n][p] = r*filter_r[n][p] - i*filter_i[n][p];
            im_i[n][p] = r*filter_i[n][p] + i*filter_r[n][p];
        }
    }
}

void getModule(double **im_r, double **im_i, double **mod, int dimx, int dimy){
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            mod[i][j] = sqrt(im_r[i][j]*im_r[i][j] + im_i[i][j]*im_i[i][j]);
        }
    }
}


