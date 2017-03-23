#include "pgm.h"
#include "libFT.h"
#include "convolution.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] la valeur de sigma et av[3] la taille du masque */
    int nl, nc;
    unsigned char **im1;
    double **resG;
    unsigned char **resC;
    double sigma = atof(av[2]);
    int masksize = (int) atof(av[3]);
    
    im1 = lectureimagepgm(av[1], &nl, &nc);

	resG = applyGaussian(im1, nl, nc, sigma);
	resC = doConvolve(im1, nl, nc, sigma, masksize);
	
	printf("%s ; sigma = %f ; masksize = %d\n", av[1], sigma, masksize);
	double res = psnr(resC, imdouble2uchar(resG, nl, nc), nl, nc);
	printf("%f\n", res);
    
    libere_image(resG);
    libere_image(resC);
    libere_image(im1);
}
