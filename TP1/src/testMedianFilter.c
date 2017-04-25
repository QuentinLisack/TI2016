#include "pgm.h"
#include "medianFilter.h"
#include <time.h>

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat et av[3] la taille du filtre. */
    int nl, nc;
    unsigned char **im=NULL, **res=NULL;
    clock_t debut, fin;
    
    
    int filterSize = (int) atof(av[3]);
    
    im = lectureimagepgm(av[1], &nl, &nc);
	res = alloue_image(nl, nc);
	
    debut = clock();
	applyMedianFilter(im, res, nl, nc, filterSize);
    
    fin = clock();
    printf("%f   Median filter : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
    
    ecritureimagepgm(av[2], res, nl, nc);
    
    libere_image(res);
    libere_image(im);
}


