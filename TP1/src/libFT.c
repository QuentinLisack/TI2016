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
            res[x + dimx/2][y + dimy/2] = 255.0 * exp(- 2 * sigma * sigma * M_PI * M_PI * (((double) (x*x))/(dimx*dimx) + ((double) (y*y))/(dimy*dimy)));
        }
    }
	return res;
}


