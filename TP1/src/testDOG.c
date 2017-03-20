#include "pgm.h"
#include "libFT.h"
#include <time.h>

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
    int nl, nc;
    unsigned char **im=NULL;
    double **res;
    double sigma = 3; 
    double coeff = 1.6;
    clock_t debut, fin; 
    
    im = lectureimagepgm(av[1], &nl, &nc);

    debut = clock();
	res = applyDOG(im, nl, nc, sigma, coeff);
    fin = clock();
    printf("%f   DoG : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
    
    ecritureimagepgm(av[2], imdouble2uchar(res, nl, nc), nl, nc); //normalement le crop se fait tout seul à l'écriture comme nl et nc n'ont pas été modifiés
    
    libere_image(res);
    libere_image(im);
}
