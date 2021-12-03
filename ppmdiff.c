#include "ppmdiff.h"
#include <pnm.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void check(Pnm_ppm ppmOne, Pnm_ppm ppmTwo){
        
    assert(ppmOne != NULL);
    assert(ppmTwo != NULL);

    int heightOne = ppmOne->height;
    int heightTwo = ppmTwo->height;
        

        int widthOne = ppmOne->width;
        int widthTwo = ppmTwo->width;

        if(abs(widthOne - widthTwo) > 1 || abs(heightOne - heightTwo) > 1){
        fprintf(stderr, "The difference of width and height is greater than 1\n");
        printf("%f", 1.0);
        //exit(EXIT_FAILURE);
        exit(1);
    }
}

double compute_diff(Pnm_ppm ppmOne, Pnm_ppm ppmTwo){

    double summation = 0;

    int smallHeight = ppmOne->height;
    int heightTwo = ppmTwo->height;
    if(smallHeight > heightTwo) {
        smallHeight = heightTwo;
    }

    int smallWidth = ppmOne->width;
    int widthTwo = ppmTwo->width;
    if(smallWidth > widthTwo) {
        smallWidth = widthTwo;
    }

    double ppmOne_denom = ppmOne->denominator;
    double ppmTwo_denom = ppmTwo->denominator;
    for(int i = 0; i < smallWidth; i++){
        for(int j = 0; j < smallHeight; j++){
            Pnm_rgb rgbOne = ppmOne->methods->at(ppmOne->pixels, i, j);   
            double rOne = rgbOne->red / ppmOne_denom;
            double gOne = rgbOne->green / ppmOne_denom;
            double bOne = rgbOne->blue / ppmOne_denom;
            Pnm_rgb rgbTwo = ppmTwo->methods->at(ppmTwo->pixels, i, j);   
            double rTwo = rgbTwo->red / ppmTwo_denom;
            double gTwo = rgbTwo->green / ppmTwo_denom;
            double bTwo = rgbTwo->blue / ppmTwo_denom;
            double rDiffSq = (rOne - rTwo) * (rOne - rTwo);
            double gDiffSq = (gOne - gTwo) * (gOne - gTwo);
            double bDiffSq = (bOne - bTwo) * (bOne - bTwo);
            summation += (rDiffSq + gDiffSq + bDiffSq);
        }
    }
    double output = sqrt(((double) summation / (double)(3 * smallWidth * smallHeight)));
    if(output > 1){

    }
    return output;
}