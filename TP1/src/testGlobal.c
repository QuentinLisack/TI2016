#include "pgm.h"
#include "libFT.h"
#include "contourExtract.h"
#include <dirent.h> 

main (int ac, char **av) {  /* av[1] contient le nom du répertoire avec les images, av[2] celui du répertoire où stocker les résultats . */
    
    //récupération de tous les noms de fichiers
    
    DIR *d;
    struct dirent *dir;
    d = opendir(av[1]);
    char** filenames;
    unsigned int filenumber = 0;
    if (d){
        while ((dir = readdir(d)) != NULL){
            filenames = realloc(filenames, (filenumber + 1)*sizeof(char*));
            filenames[filenumber] = dir->d_name;
            filenumber++;
        }
        filenames[filenumber] = 0;
        closedir(d);
    }
    printf("nombre de fichiers %d\n", filenumber);
    for(int j = 0; j < filenumber; j++){
        printf("%s\n", filenames[j]);
    }
    
    
    for(int i = 2; i < filenumber; i++){
        int nl, nc;
        unsigned char **im=NULL;
        double **res, **contours;
        double sigma, coeff, r1, r2; 
        char* prefixe;
        
        printf("\n");
        printf("\n");
        char* readname = (char*) malloc(strlen(av[1]) + strlen(filenames[i]));
        strcpy(readname, av[1]);
        char* temp = (char*) malloc(strlen(filenames[i]));
        strcpy(temp, filenames[i]);
        strcat(readname, temp);
        im = lectureimagepgm(readname, &nl, &nc);
        
        printf("temp : %s\n", temp);
        printf("readname : %s\n", readname);
        printf("\n");
        
        //lissage par gaussienne fft
        sigma = 3.0;
        prefixe = "lissage_";
        char* savename = malloc(strlen(av[2]) + strlen(prefixe) + strlen(filenames[i]));
        strcpy(savename, av[2]);
        strcat(savename, prefixe);
        strcat(savename, temp);

        printf("foldername : %s\n", av[2]);
        printf("prefixe : %s\n", prefixe);
        printf("temp : %s\n", temp);
        printf("savename : %s\n", savename);
        printf("\n");

	    res = applyGaussian(im, nl, nc, sigma);
        ecritureimagepgm(savename, imdouble2uchar(res, nl, nc), nl, nc);
        free(savename);
        
        //DOG
        sigma = 10.0;
        coeff = 1.6;
        prefixe = "DOG_";
        savename = malloc(strlen(av[2]) + strlen(prefixe) + strlen(filenames[i]));

        strcpy(savename, av[2]);
        strcat(savename, prefixe);
        strcat(savename, temp);
        
        printf("foldername : %s\n", av[2]);
        printf("prefixe : %s\n", prefixe);
        printf("temp : %s\n", temp);
        printf("savename : %s\n", savename);
        printf("\n");
        
        res = applyDOG(im, nl, nc, sigma, coeff);
        ecritureimagepgm(savename, imdouble2uchar(res, nl, nc), nl, nc);
        free(savename);
        
        //LoG
        sigma = 10.0;
        prefixe = "LoG_";
        savename = malloc(strlen(av[2]) + strlen(prefixe) + strlen(filenames[i]));

        strcpy(savename, av[2]);
        strcat(savename, prefixe);
        strcat(savename, temp);
        
        printf("foldername : %s\n", av[2]);
        printf("prefixe : %s\n", prefixe);
        printf("temp : %s\n", temp);
        printf("savename : %s\n", savename);
        printf("\n");
        
        res = applyLoG(im, nl, nc, sigma);
        contours = extract(res, nl, nc);
        ecritureimagepgm(savename, imdouble2uchar(contours, nl, nc), nl, nc);
        free(savename);
        
        //Ideal Filter
        r1 = 1.0/256.0; 
        r2 = 45.0/256.0;
        prefixe = "idealFilter_";
        savename = malloc(strlen(av[2]) + strlen(prefixe) + strlen(filenames[i]));

        strcpy(savename, av[2]);
        strcat(savename, prefixe);
        strcat(savename, temp);
        
        printf("foldername : %s\n", av[2]);
        printf("prefixe : %s\n", prefixe);
        printf("temp : %s\n", temp);
        printf("savename : %s\n", savename);
        printf("\n");
        
        res = applyIdealFilter(im, nl, nc, r1, r2);
        contours = extract(res, nl, nc);
        ecritureimagepgm(savename, imdouble2uchar(contours, nl, nc), nl, nc);
        free(savename);
        
        libere_image(res);
        libere_image(im);
        libere_image(contours);
    }
    
    
}
