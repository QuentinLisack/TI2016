#include "pgm.h"
#include "libFT.h"
#include "contourExtract.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
    int nl, nc;
    unsigned char **im=NULL;
    double **res;
    double sigma = 10; 
    
    im = lectureimagepgm(av[1], &nl, &nc);

	res = applyLoG(im, nl, nc, sigma);

    //ecritureimagepgm(av[2], imdouble2uchar(res, nl, nc), nl, nc);
    
    double** contours = extract(res, nl, nc);
    
    ecritureimagepgm(av[2], imdouble2uchar(contours, nl, nc), nl, nc); //normalement le crop se fait tout seul à l'écriture comme nl et nc n'ont pas été modifiés
    
    libere_image(res);
    libere_image(im);
    libere_image(contours);
}
