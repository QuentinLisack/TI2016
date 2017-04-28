#include "pgm.h"
#include "bilateralFilter.h"
#include <time.h>

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat. */
    int nl, nc;
    unsigned char **im=NULL, **resu;
    double **res, **im1;
    clock_t debut, fin;
    
    double s1 = 10.0;
    double s2 = 20.0;
    
    im = lectureimagepgm(av[1], &nl, &nc);
    im1 = alloue_image_double(nl, nc);
    im1 = imuchar2double(im, nl, nc);
	res = alloue_image_double(nl, nc);
	resu = alloue_image(nl, nc);
	
    debut = clock();
	applyBilateralFilter(im1, res, s1, s2, nl, nc);
    
    fin = clock();
    printf("%f   Bilateral filter : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
    
    resu = imdouble2uchar(res, nl, nc);
    ecritureimagepgm(av[2], resu, nl, nc);
    
    libere_image(res);
    libere_image(resu);
    libere_image(im);
    libere_image(im1);
}
