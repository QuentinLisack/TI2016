/*
 * testconv.c
 *
 *  Created on: Feb 8, 2017
 *      Author: bouteloj
 */
#include "convolution.h"


main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
  int nb,nl,nc, oldnl,oldnc;
  unsigned char **im1=NULL;
  double ** im2=NULL;
  double** im4,** im5, ** im6, ** im7, **im8, **im9,**im10;

  if (ac < 2) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
	/* Lecture d'une image pgm dont le nom est passe sur la ligne de commande */
  im1=lectureimagepgm(av[1],&nl,&nc);
  if (im1==NULL)  { puts("Lecture image impossible"); exit(1); }
	/* Calcul la convolution par un filtre gaussien*/
  im2=doConvolve(im1,nl,nc,3);

	/* Sauvegarde dans un fichier dont le nom est passe sur la ligne de commande */
  ecritureimagepgm(av[2],im2,nl,nc);
}


