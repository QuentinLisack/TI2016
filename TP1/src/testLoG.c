#include "pgm.h"
#include "libFT.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
    int nl, nc;
    unsigned char **im=NULL;
    double **res;
    double sigma = 3; 
    
    im = lectureimagepgm(av[1], &nl, &nc);

	res = applyLoG(im, &nl, &nc, sigma);

    ecritureimagepgm(av[2], imdouble2uchar(res, nl, nc), nl, nc);
    
    libere_image(res);
    libere_image(im);
}
