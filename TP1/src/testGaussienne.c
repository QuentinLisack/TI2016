#include "pgm.h"
#include "libFT.h"
#include <time.h>

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat et av[3] la valeur de sigma. */
    int nl, nc;
    unsigned char **im=NULL;
    double **res;
    double sigma = atof(av[3]);
    clock_t debut, fin;
    
    im = lectureimagepgm(av[1], &nl, &nc);

    debut = clock();
	res = applyGaussian(im, nl, nc, sigma);
	fin = clock();
    printf("%f   Gaussian FFT : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
	
    ecritureimagepgm(av[2], imdouble2uchar(res, nl, nc), nl, nc); //decommenter pour sauvegarder l'image
    
    libere_image(res);
    libere_image(im);
}
