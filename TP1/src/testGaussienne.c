#include "pgm.h"
#include "libFT.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
  int nb,nl,nc, oldnl,oldnc;
  unsigned char **im2=NULL,** im1=NULL;
  double **im_r, **im_i, **im_r_tf, **im_i_tf;
  
  int dimx = 256;
  int dimy = 256;
  double sigma = 1;
  
    im_r = GaussienneFT(dimx, dimy, sigma);
    im2 = alloue_image(dimx, dimy);
    im2 = imdouble2uchar(im_r, dimx, dimy);
    ecritureimagepgm("testGaussienneFT.pgm",im2,dimx,dimy);
  
}
