#include "pgm.h"
#include "libFT.h"
#include "contourExtract.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
    int nl, nc;
    unsigned char **im=NULL;
    double **res;
    double r1 = 10, r2 = 50;
    
    im = lectureimagepgm(av[1], &nl, &nc);

	res = applyIdealFilter(im, &nl, &nc, r1, r2);

    //ecritureimagepgm(av[2], imdouble2uchar(res, nl, nc), nl, nc);
    
    double** contours = extract(res, nl, nc);
    
    ecritureimagepgm(av[2], imdouble2uchar(contours, nl, nc), nl, nc);
    
    libere_image(res);
    libere_image(im);
    libere_image(contours);
}
