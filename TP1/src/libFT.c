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

double** idealFilter(int dimx, int dimy, double r1, double r2){
	double **res;
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
        	if(sqrt((((double) (x*x))/(dimx*dimx) + ((double) (y*y))/(dimy*dimy))) <= r2 && sqrt((((double) (x*x))/(dimx*dimx) + ((double) (y*y))/(dimy*dimy))) >= r1){
        		res[x + dimx/2][y + dimy/2] = 1;
        	}else{
            	res[x + dimx/2][y + dimy/2] = 0;
        	}
        }
    }
    return res;
}

double** LoG(int dimx, int dimy, double sigma){
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
            res[x + dimx/2][y + dimy/2] = -4 * M_PI * M_PI * (((double) (x*x))/(dimx*dimx) + ((double) (y*y))/(dimy*dimy)) * exp(-2 * M_PI * M_PI * sigma * sigma * (double) (((double) (x*x))/(dimx*dimx) + ((double) (y*y))/(dimy*dimy)));
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

double** applyGaussian(unsigned char** image, int nl, int nc, double sigma){
	int oldnl, oldnc;
    double **im_r, **im_i, **im_r_tf, **im_i_tf, **g_r, **g_i, **im_r_s, **im_i_s, **im_r_tf_b, **im_i_tf_b, **imRes;
    
    oldnl = nl;
    oldnc = nc;
    
    im_r = padimucforfft(image, &nl, &nc);
    im_i = alloue_image_double(nl, nc);
    im_r_tf = alloue_image_double(nl, nc);
    im_i_tf = alloue_image_double(nl, nc);
    im_r_tf_b = alloue_image_double(nl, nc);
    im_i_tf_b = alloue_image_double(nl, nc);
    im_r_s = alloue_image_double(nl, nc);
    im_i_s = alloue_image_double(nl, nc);
    g_r = GaussienneFT(nl, nc, sigma);
    g_i = alloue_image_double(nl, nc);
    imRes = alloue_image_double(nl, nc);
    
    int res = fft(im_r, im_i, im_r_tf, im_i_tf, nl, nc);
    if(res != 1)
        printf("probleme avec la fft\n");

    fftshift(im_r_tf, im_i_tf, im_r_s, im_i_s, nl, nc);
    
    applyFilter(im_r_s, im_i_s, g_r, g_i, nl, nc);
    fftshift(im_r_s, im_i_s, im_r_tf_b, im_i_tf_b, nl, nc);
    
    res = ifft(im_r_tf_b, im_i_tf_b, im_r, im_i, nl, nc);
    if(res != 1)
        printf("probleme avec la ifft\n");
    
    //TODO vérifier que la ligne ci dessous ne pose pas de problème.
    //imRes = crop(im_r, 0, 0, oldnl, oldnc);
    copieimagedouble(im_r, imRes, nl, nc);
    
    libere_image(im_r);
    libere_image(im_i);
    libere_image(im_r_tf);
    libere_image(im_i_tf);
    libere_image(im_r_tf_b);
    libere_image(im_i_tf_b);
    libere_image(im_r_s);
    libere_image(im_i_s);
    libere_image(g_r);
    libere_image(g_i);
    
    return imRes;
}

double** applyDOG(unsigned char** image, int nl, int nc, double sigma, double coeff){
	double **imRes1, **imRes2, **res;
	imRes1 = applyGaussian(image, nl, nc, sigma);
	imRes2 = applyGaussian(image, nl, nc, sigma/coeff);
	res = alloue_image_double(nl, nc);
	differenceimagesdouble(imRes1, imRes2, res, nl, nc);
    return res;
}

double** applyLoG(unsigned char** image, int nl, int nc, double sigma){
	int oldnl, oldnc;
    double **im_r, **im_i, **im_r_tf, **im_i_tf, **LoG_r, **LoG_i, **im_r_s, **im_i_s, **im_r_tf_b, **im_i_tf_b, **imRes;
    
    oldnl = nl;
    oldnc = nc;
    
    im_r = padimucforfft(image, &nl, &nc);
    im_i = alloue_image_double(nl, nc);
    im_r_tf = alloue_image_double(nl, nc);
    im_i_tf = alloue_image_double(nl, nc);
    im_r_tf_b = alloue_image_double(nl, nc);
    im_i_tf_b = alloue_image_double(nl, nc);
    im_r_s = alloue_image_double(nl, nc);
    im_i_s = alloue_image_double(nl, nc);
    LoG_r = LoG(nl, nc, sigma);
    LoG_i = alloue_image_double(nl, nc);
    imRes = alloue_image_double(nl, nc);
    
    int res = fft(im_r, im_i, im_r_tf, im_i_tf, nl, nc);
    if(res != 1)
        printf("probleme avec la fft\n");

    fftshift(im_r_tf, im_i_tf, im_r_s, im_i_s, nl, nc);
    
    applyFilter(im_r_s, im_i_s, LoG_r, LoG_i, nl, nc);
    fftshift(im_r_s, im_i_s, im_r_tf_b, im_i_tf_b, nl, nc);
    
    res = ifft(im_r_tf_b, im_i_tf_b, im_r, im_i, nl, nc);
    if(res != 1)
        printf("probleme avec la ifft\n");
    
    //TODO vérifier que la ligne ci dessous ne pose pas de problème.
    //imRes = crop(im_r, 0, 0, oldnl, oldnc);
    copieimagedouble(im_r, imRes, nl, nc);
    
    libere_image(im_r);
    libere_image(im_i);
    libere_image(im_r_tf);
    libere_image(im_i_tf);
    libere_image(im_r_tf_b);
    libere_image(im_i_tf_b);
    libere_image(im_r_s);
    libere_image(im_i_s);
    libere_image(LoG_r);
    libere_image(LoG_i);
    
    return imRes;
}

double** applyIdealFilter(unsigned char** image, int nl, int nc, double r1, double r2){
	int oldnl, oldnc;
    double **im_r, **im_i, **im_r_tf, **im_i_tf, **if_r, **if_i, **im_r_s, **im_i_s, **im_r_tf_b, **im_i_tf_b, **imRes;
    
    oldnl = nl;
    oldnc = nc;
    
    im_r = padimucforfft(image, &nl, &nc);
    im_i = alloue_image_double(nl, nc);
    im_r_tf = alloue_image_double(nl, nc);
    im_i_tf = alloue_image_double(nl, nc);
    im_r_tf_b = alloue_image_double(nl, nc);
    im_i_tf_b = alloue_image_double(nl, nc);
    im_r_s = alloue_image_double(nl, nc);
    im_i_s = alloue_image_double(nl, nc);
    if_r = idealFilter(nl, nc, r1, r2);
    if_i = alloue_image_double(nl, nc);
    imRes = alloue_image_double(nl, nc);
    
    int res = fft(im_r, im_i, im_r_tf, im_i_tf, nl, nc);
    if(res != 1)
        printf("probleme avec la fft\n");

    fftshift(im_r_tf, im_i_tf, im_r_s, im_i_s, nl, nc);
    
    applyFilter(im_r_s, im_i_s, if_r, if_i, nl, nc);
    fftshift(im_r_s, im_i_s, im_r_tf_b, im_i_tf_b, nl, nc);
    
    res = ifft(im_r_tf_b, im_i_tf_b, im_r, im_i, nl, nc);
    if(res != 1)
        printf("probleme avec la ifft\n");
    
    //TODO vérifier que la ligne ci dessous ne pose pas de problème.
    //imRes = crop(im_r, 0, 0, oldnl, oldnc);
    copieimagedouble(im_r, imRes, nl, nc);
    
    libere_image(im_r);
    libere_image(im_i);
    libere_image(im_r_tf);
    libere_image(im_i_tf);
    libere_image(im_r_tf_b);
    libere_image(im_i_tf_b);
    libere_image(im_r_s);
    libere_image(im_i_s);
    libere_image(if_r);
    libere_image(if_i);
    
    return imRes;
}
