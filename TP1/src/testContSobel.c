/*
 * testContGrad.c
 *
 *  Created on: Mar 3, 2017
 *      Author: bouteloj
 */

#include "contourGradient.h"
#include <time.h>

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
  int nb,nl,nc, oldnl,oldnc;
  unsigned char **im1=NULL;
  double ** im2=NULL;
  double** im4,** im5, ** im6, ** im7, **im8, **im9,**im10;
  clock_t debut, fin;

  if (ac < 2) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
	/* Lecture d'une image pgm dont le nom est passe sur la ligne de commande */
  im1=lectureimagepgm(av[1],&nl,&nc);
  if (im1==NULL)  { puts("Lecture image impossible"); exit(1); }
	/* Calcul la convolution par un filtre gaussien*/
  //im4=imuchar2double(im1,nl,nc);

  debut = clock();
  im2=doAll(im1,nl,nc,2,1.7);
  fin = clock();
  printf("%f   Sobel : %s\n", ((double)(fin - debut))/CLOCKS_PER_SEC, av[1]);
  //im2=doFindContours(im4, nl, nc,1);
	/* Sauvegarde dans un fichier dont le nom est passe sur la ligne de commande */
  ecritureimagepgm(av[2],imdouble2uchar(im2,nl,nc),nl,nc);
}
