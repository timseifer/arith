
/*
 *     componentVCS.c
 *     by Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *     assignment: Arith
 *
 *     summary: implementation for componentVCS.h
 */ 


#include "componentVCS.h"
#include <stdio.h>
#include <stdlib.h>


void populate_cvcs(int col, int row, A2Methods_UArray2 array2,
             void *ptr, void *cl)
{
    (void)ptr;
    /*Get the PPM and VCS pixels*/
    struct Pnm_ppm *ppm = cl;
    Pnm_rgb pixelRGB = (ppm)->methods->at(ppm->pixels, col, row);
    component_vcs pixelCVCS = (ppm)->methods->at(array2, col, row);
    float red = (float) pixelRGB->red / ppm->denominator;
    float green = (float) pixelRGB->green / ppm->denominator;
    float blue = (float) pixelRGB->blue / ppm->denominator;
    /*Change image representation from rgb to ypbpr*/
    pixelCVCS->y = (.299 * red) + (.587 * green) + (.114 * blue);
    pixelCVCS->pb = (-0.168736 * red) - (0.331264 * green) + (0.5 * blue);
    pixelCVCS->pr = (.5 * red) - (0.418688 * green) - (0.081312 * blue);
    /*Check to see if the values are in bounds*/
    /*if not set to a valid value*/
    if (pixelCVCS->y > 1 ) {
        pixelCVCS->y = 0;
    } else if (pixelCVCS->y < 0) {
        pixelCVCS->y = 0;
    }
    if (pixelCVCS->pb > .5) {
        pixelCVCS->pb = .5;
    } else if (pixelCVCS->pb < -.5) {
        pixelCVCS->pb = -.5;
    }
    if (pixelCVCS->pr > .5) {
        pixelCVCS->pr = .5;
    } else if (pixelCVCS->pr < -.5) {
        pixelCVCS->pr = -.5;
    }
}

/*
 * Purpose: Checks to see if the Red Green or Blue value
 *          is valid (in correct range) If not change to
 *          a valid value
 */
unsigned validateRGB(float rgb, unsigned denominator){
   if(rgb > (int) denominator){
        rgb = denominator;
    }else if (rgb < 0 ){
        rgb = 0;
    }
    return (unsigned)rgb;
 }

void populate_RGB(int col, int row, A2Methods_UArray2 array2,
             void *ptr, void *cl)
{
    (void)ptr;
    /*Get the VCS pixel*/
    struct Pnm_ppm *ppm = cl;
    component_vcs pixelCVCS = (ppm)->methods->at(array2, col, row);
    /*Create a new PPM pixel*/
    Pnm_rgb pixelRGB = malloc(sizeof(struct Pnm_rgb));
    float y = pixelCVCS->y;
    float pb = pixelCVCS->pb;
    float pr = pixelCVCS->pr;
    /*Populate the RGB values of the new pixel*/
    /*making sure they are valid*/
    float red = ((1.0 * y + 0.0 * pb + 1.402 * pr) * ppm->denominator);
    pixelRGB->red = validateRGB(red, ppm->denominator); 
    float green = ((1.0 * y - 0.344136 * pb - 0.714136 * pr) * 
                   ppm->denominator);
    pixelRGB->green = validateRGB(green, ppm->denominator); 
    float blue = ((1.0 * y + 1.7720 * pb + 0.0 * pr) * ppm->denominator);
    pixelRGB->blue = validateRGB(blue, ppm->denominator);
    /*put the pixel in the ppm*/
    *(Pnm_rgb)((ppm)->methods->at(ppm->pixels, col, row)) = *pixelRGB;
    free(pixelRGB);
}


A2Methods_UArray2 compressPPM(Pnm_ppm ppm)
{
    /*Creates a UArray of CVC pixels*/
    A2Methods_UArray2 cvcsArray = ppm->methods->new(ppm->width, ppm->height, 
    sizeof(struct component_vcs));
    /*Map through the cvcsArray and populate it with data from the ppm*/
    ppm->methods->map_row_major(cvcsArray, populate_cvcs, ppm);
    return cvcsArray;
}

Pnm_ppm decompressCVCS(A2Methods_UArray2 cvcs, A2Methods_T methods)
{
    /*Creates a new Pnm_ppm*/
    Pnm_ppm new_pixmap = malloc(sizeof(struct Pnm_ppm));
    if (!new_pixmap){ /* makes sure allocation succeeded */
      fprintf(stderr, "failed to allocate %ld bytes",
              sizeof(struct Pnm_ppm));
      exit(EXIT_FAILURE);
    }
    /*set the data inside the ppm*/
    new_pixmap->denominator = 255;
    new_pixmap->methods = methods;
    new_pixmap->width = methods->width(cvcs);
    new_pixmap->height = methods->height(cvcs);
    /*Creates a new array to hold the pixels*/
    A2Methods_UArray2 new_pixels = methods->new(new_pixmap->width, 
    new_pixmap->height, sizeof(struct Pnm_rgb));
    new_pixmap->pixels = new_pixels;
    /*Map through the cvcsArray and populate the ppm sent in as cl*/
    methods->map_row_major(cvcs, populate_RGB, new_pixmap);
    return new_pixmap;
}

