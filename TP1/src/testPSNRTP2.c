#include "pgm.h"
#include <time.h>
#include "adaptativeRecursiveFilter.h"
#include "bilateralFilter.h"
#include "medianFilter.h"
#include "NlMeansFilter.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom de l'image 2*/
    int nl, nc;
    unsigned char **im=NULL, **resu;
    double **res, **im1;
    clock_t debut, fin;

    
    im = lectureimagepgm(av[1], &nl, &nc);
    im1 = alloue_image_double(nl, nc);
    im1 = imuchar2double(im, nl, nc);
	res = alloue_image_double(nl, nc);
	resu = alloue_image(nl, nc);

    //test pour adaptatif recursif
    double TOL = 0.0001;
    double filterParam = 10.0;

    debut = clock();
	applyAdaptativeRecursiveFilter(im1, res, filterParam, nl, nc, TOL);
    fin = clock();
    
    printf("%f   Adaptative Recursive filter : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
	
	resu = imdouble2uchar(res, nl, nc);
	double PSNR = psnr(im, resu, nl, nc);
	printf("Original VS Adaptative Recursive    : %f\n", PSNR);
	
	//test bilateral
	
	double s1 = 10.0;
    double s2 = 20.0;
    
	debut = clock();
	applyBilateralFilter(im1, res, s1, s2, nl, nc);
    
    fin = clock();
    printf("%f   Bilateral filter : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
    
    resu = imdouble2uchar(res, nl, nc);
    
    PSNR = psnr(im, resu, nl, nc);
	printf("Original VS Adaptative Recursive    : %f\n", PSNR);
	
	//test median filter
	
	int filterSize = 3.0;
	
    debut = clock();
	applyMedianFilter(im, resu, nl, nc, filterSize);
    
    fin = clock();
    printf("%f   Median filter : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
    
    PSNR = psnr(im, resu, nl, nc);
	printf("Original VS Median    : %f\n", PSNR);
	
	//test Nl Means
	
	double s = 250.0;
    int r = 2;
    int t = 10;
	
    debut = clock();
	applyNlMeansFilter(im1, res, s, r, t, nl, nc);
    
    fin = clock();
    printf("%f   Nl-Means filter : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
    
    resu = imdouble2uchar(res, nl, nc);
    
    PSNR = psnr(im, resu, nl, nc);
	printf("Original VS Nl Means    : %f\n", PSNR);
    
    libere_image(res);
    libere_image(im);
    libere_image(im1);
    libere_image(resu);
}
