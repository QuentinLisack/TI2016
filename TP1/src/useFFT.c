#include "pgm.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
  int nb,nl,nc, oldnl,oldnc;
  unsigned char **im2=NULL,** im1=NULL;
  double **im_r, **im_i, **im_r_tf, **im_i_tf;
  
  if (ac < 2) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
	/* Lecture d'une image pgm dont le nom est passe sur la ligne de commande */
  im1=lectureimagepgm(av[1],&nl,&nc);
  if (im1==NULL)  { puts("Lecture image impossible"); exit(1); }
  //calcul de la fft
  im_r = padimucforfft(im1, &nl, &nc);
  im_i = alloue_image_double(nl, nc);
  im_r_tf = alloue_image_double(nl, nd);
  im_i_tf = alloue_image_double(nl, nc);
  int res = fft(im_r, im_i, im_r_tf, im_i_tf, nl, nc);
  if(res != 1){
    printf("FFT failed");
  }
  im_i_shift = alloue_image_double(nl, nc);
  im_r_shift = alloue_image_double(nl, nc);
  fftshift(im_r_tf, im_i_tf, im_r_shift, im_i_shift, nl, nc);
  
}
