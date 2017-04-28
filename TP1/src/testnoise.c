/*
 * testnoise.c
 *
 *  Created on: Apr 28, 2017
 *      Author: bouteloj
 */

#include "noise.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat et av[3] la valeur de sigma. */
    int nl, nc;
    unsigned char **im=NULL;


    im = lectureimagepgm(av[1], &nl, &nc);
    double var=doFindNoise(im,nl, nc,10,0.5);

   printf("variance du bruit:%f\n",var);


    libere_image(im);
}
