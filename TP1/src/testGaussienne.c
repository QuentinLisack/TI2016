#include "pgm.h"
#include "libFT.h"

main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
    int nl, nc, oldnl, oldnc;
    unsigned char **im2=NULL, **im1=NULL;
    double **im_r, **im_i, **im_r_tf, **im_i_tf, **g_r, **g_i, **im_r_s, **im_i_s, **im_r_tf_b, **im_i_tf_b;
    double sigma = 3;
    
    im1 = lectureimagepgm(av[1], &nl, &nc);
    oldnl = nl;
    oldnc = nc;
    
    im_r = padimucforfft(im1, &nl, &nc);
    im_i = alloue_image_double(nl, nc);
    im_r_tf = alloue_image_double(nl, nc);
    im_i_tf = alloue_image_double(nl, nc);
    im_r_tf_b = alloue_image_double(nl, nc);
    im_i_tf_b = alloue_image_double(nl, nc);
    im_r_s = alloue_image_double(nl, nc);
    im_i_s = alloue_image_double(nl, nc);
    g_r = GaussienneFT(nl, nc, sigma);
    g_i = alloue_image_double(nl, nc);
    
    int res = fft(im_r, im_i, im_r_tf, im_i_tf, nl, nc);
    if(res != 1)
        printf("probleme avec la fft\n");

    fftshift(im_r_tf, im_i_tf, im_r_s, im_i_s, nl, nc);
    
    ecritureimagepgm("gaussienne.pgm", imdouble2uchar(g_r, nl, nc), nl, nc);
    //ecritureimagepgm("imr.pgm", imdouble2uchar(im_r_s, nl, nc), nl, nc);
    //ecritureimagepgm("imi.pgm", imdouble2uchar(im_i_s, nl, nc), nl, nc);
    applyFilter(im_r_s, im_i_s, g_r, g_i, nl, nc);
    //ecritureimagepgm("imrg.pgm", imdouble2uchar(im_r_s, nl, nc), nl, nc);
    //ecritureimagepgm("imig.pgm", imdouble2uchar(im_i_s, nl, nc), nl, nc);
    fftshift(im_r_s, im_i_s, im_r_tf_b, im_i_tf_b, nl, nc);
    
    res = ifft(im_r_tf_b, im_i_tf_b, im_r, im_i, nl, nc);
    if(res != 1)
        printf("probleme avec la ifft\n");
    
    im2 = alloue_image(nl, nc);
    //im2 = imdouble2uchar(crop(im_r, 0, 0, oldnl, oldnc));
    im2 = imdouble2uchar(im_r, nl, nc);
    ecritureimagepgm(av[2], im2, nl, nc);
    
    libere_image(im1);
    libere_image(im2);
    libere_image(im_r);
    libere_image(im_i);
    libere_image(im_r_tf);
    libere_image(im_i_tf);
    libere_image(im_r_tf_b);
    libere_image(im_i_tf_b);
    libere_image(im_r_s);
    libere_image(im_i_s);
    libere_image(g_r);
    libere_image(g_i);
}
