#include "NlMeansFilter.h"

double calculatePatchDistance(int X, int Y, int x, int y, int r, double **im, int nl, int nc){
    double res = 0;
    for(int i = -r; i < r+1; i++){
        for(int j = -r; j < r+1; j++){
            res += pow(im[(x+i+nl)%nl][(y+j+nc)%nc] - im[(X+i+nl)%nl][(Y+j+nc)%nc], 2);
        }
    }
    return res;
}

void applyNlMeansFilter(double** im, double** res, double s, int r, int t, int nl, int nc){
    double d = 0;
    double w = 0;
    //parcours de l'image
    for(int X = 0; X < nl; X++){
        for(int Y = 0; Y < nc; Y++){
            double newPix = 0;
            double wSum = 0;
            //parcours de la region
            for(int x = X - t; x < X+t+1; x++){
                for(int y = Y - t; y < Y+t+1; y++){
                    //calcul de la distance entre les patchs autour des deux pixels
                    d = calculatePatchDistance(X, Y, x, y, r, im, nl, nc);
                    w = exp(-d/(2*s*s));
                    newPix += w*im[(x+nl)%nl][(y+nc)%nc];
                    wSum += w;
                }
            }
            res[X][Y] = newPix/wSum;
        }
    }
}
