#include "pgm.h"
#include "libFT.h"
#include "contourExtract.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
    int nl, nc;
    unsigned char **im=NULL;
    double **res;
    double r1 = 1.0/256.0, r2 = 45.0/256.0;
    
    im = lectureimagepgm(av[1], &nl, &nc);

	res = applyIdealFilter(im, nl, nc, r1, r2);

    //ecritureimagepgm(av[2], imdouble2uchar(res, nl, nc), nl, nc);
    
    double** contours = extract(res, nl, nc);
    
    ecritureimagepgm(av[2], imdouble2uchar(contours, nl, nc), nl, nc); //normalement le crop se fait tout seul à l'écriture comme nl et nc n'ont pas été modifiés
    
    libere_image(res);
    libere_image(im);
    libere_image(contours);
}
