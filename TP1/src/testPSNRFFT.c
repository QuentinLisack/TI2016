#include "pgm.h"
#include "libFT.h"
#include "convolution.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom de l'image 2, av[3] la valeur de sigma */
    int nl, nc;
    unsigned char **im=NULL, **im1;
    double **resG;
    double sigma = atof(av[3]);
    int masksize = 0;
    
    im1 = lectureimagepgm(av[1], &nl, &nc);
    im = lectureimagepgm(av[2], &nl, &nc);

	resG = applyGaussian(im1, nl, nc, sigma);
	
	printf("%s ; sigma = %f\n", av[1], sigma);
	double res = psnr(im, imdouble2uchar(resG, nl, nc), nl, nc);
	printf("Original VS FFT    : %f\n", res);
    
    libere_image(resG);
    libere_image(im);
}
