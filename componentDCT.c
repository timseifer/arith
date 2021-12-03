/*
 *     componentDCT.c
 *     by Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *     assignment: Arith
 *
 *     summary: implementation for componentDCT.h
*/ 
#include "componentDCT.h"
#include "arith40.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "assert.h"

/*
 * Purpose: Checks to see if Y is in range
 *          If not makes it in range (0-1)
 */
float validateY(float y){
    if (y < 0) {
        return 0;
    } else if (y > 1) {
        return 1;
    }
    return y;
}

/*
 * Purpose: Checks to see if b c and d are in range
 *          If not makes it in range (-15-15)
 */
int validateBCD(int bcd) {
    if (bcd > 15) {
        bcd = 15;
    } else if (bcd < -15) {
        bcd = -15;
    }
    return bcd;
}

/*
 * Purpose: Helper function of compressCVCS
 *          Compresses a CVCS and populates a DCT Array 
 */
void populate_dct(A2Methods_UArray2 dctArray, 
     A2Methods_UArray2 cvcs, A2Methods_T methods)
{
    assert(methods != NULL && dctArray != NULL && cvcs != NULL);
    /*Itterates through each pixel in the new dct array*/
    for(int col = 0; col < methods->width(cvcs); col = col + 2){
        for(int row = 0; row < methods->height(cvcs); row = row + 2){
            /*Creates one DCT pixel for each 4  VCS pixels*/
            component_dct pixelDCT = malloc(sizeof(struct component_dct));
            /*Get the 4 VSC pixels*/
            component_vcs vscOne = methods->at(cvcs, col, row);
            component_vcs vscTwo = methods->at(cvcs, col + 1, row);
            component_vcs vscThree = methods->at(cvcs, col, row + 1);
            component_vcs vscFour = methods->at(cvcs, col + 1, row + 1);
            /*Quantize the average Pb and Pr from the four VSC pixels*/
            pixelDCT->avPb = Arith40_index_of_chroma((float)(vscOne->pb + 
                            vscTwo->pb + vscThree->pb + vscFour->pb) / 4.0);
            pixelDCT->avPr = Arith40_index_of_chroma((float)(vscOne->pr +
                             vscTwo->pr + vscThree->pr + vscFour->pr) / 4.0);
            /*Get the four VSC pixels Y values and check to see if in range*/
            float Y1 = validateY(vscOne->y);
            float Y2 = validateY(vscTwo->y);    
            float Y3 = validateY(vscThree->y);
            float Y4 = validateY(vscFour->y);
            /*Set a, b, c, and d*/
            float a = ((Y4 + Y3 + Y2 + Y1) / 4.0);
            float b = ((Y4 + Y3 - Y2 - Y1) / 4.0);
            float c = ((Y4 - Y3 + Y2 - Y1) / 4.0);
            float d = ((Y4 - Y3 - Y2 + Y1) / 4.0);
            /*Quantize and set a, b, c, and d*/
            pixelDCT->a = a * 63;
            pixelDCT->b = validateBCD(b * 50);
            pixelDCT->d = validateBCD(d * 50);
            pixelDCT->c = validateBCD(c * 50);
            /*put the DCT pixel DCT Array*/
            *(component_dct)(methods->at(dctArray, col/2, row/2)) = *pixelDCT;
            free(pixelDCT);
        }
    }
  
}
/*
 * Purpose: Helper function of decompressDCT
 *          Decompresses a DCT and populates a CVCS Array
 */
void populate_CVCS(A2Methods_UArray2 cvcs, 
    A2Methods_UArray2 dctArray, A2Methods_T methods)
{
    assert(methods != NULL && cvcs != NULL && dctArray != NULL);
    /*Itterates through each pixel in the old dct array*/
    for(int col = 0; col < methods->width(cvcs); col = col + 2){
      for(int row = 0; row < methods->height(cvcs); row = row + 2){
        /*Creates 4 new VCS pixels for each pixel of DCT*/
        component_vcs pixelOne = malloc(sizeof(struct component_vcs));
        component_vcs pixelTwo = malloc(sizeof(struct component_vcs));
        component_vcs pixelThree = malloc(sizeof(struct component_vcs));
        component_vcs pixelFour = malloc(sizeof(struct component_vcs));
        /*Get the dct pixel that corresponds to the four new  VCS pixels*/
        component_dct pixelDCT = methods->at(dctArray, col / 2, row / 2);
        /*Get the un-quantized a,b,c, and d values */
        float a = pixelDCT->a / 63.0;
        float b = pixelDCT->b / 50.0;
        float c = pixelDCT->c / 50.0;
        float d = pixelDCT->d / 50.0;
        /*Get the un-quantized Pb and Pr values*/
        float newPb = Arith40_chroma_of_index(pixelDCT->avPb);
        float newPr = Arith40_chroma_of_index(pixelDCT->avPr);
        /*set pb for the four VCS pixels*/
        pixelOne->pb = newPb;
        pixelTwo->pb = newPb;
        pixelThree->pb = newPb;
        pixelFour->pb = newPb;
        /*set pr for the four VCS pixels*/
        pixelOne->pr = newPr;
        pixelTwo->pr = newPr;
        pixelThree->pr = newPr;
        pixelFour->pr = newPr;
        /*set y for the four VCS pixels and check to see if in range*/
        pixelOne->y = validateY(a - b - c + d);
        pixelTwo->y = validateY(a - b + c - d); 
        pixelThree->y = validateY(a + b - c - d);
        pixelFour->y = validateY(a + b + c + d);
        /*put the pixels in the correct place in the CVCS Array*/
        *(component_vcs)(methods->at(cvcs, col, row)) = *pixelOne;
        *(component_vcs)(methods->at(cvcs, col + 1, row)) = *pixelTwo;
        *(component_vcs)(methods->at(cvcs, col, row +1)) = *pixelThree;
        *(component_vcs)(methods->at(cvcs, col + 1, row + 1)) = *pixelFour;
        free(pixelOne);
        free(pixelTwo);
        free(pixelThree);
        free(pixelFour);
      }
    }
}



/*
 * Purpose: Cmpresses a 2D array of component_vcs into
 *          a 2D array of component_dct
 * Notes: The CVCSArray will be half as large as the CVCS
 */
A2Methods_UArray2 compressCVCS(A2Methods_UArray2 cvcs, A2Methods_T methods)
{
    A2Methods_UArray2 DCTArray =  methods->new(methods->width(cvcs)/2, 
                                  methods->height(cvcs)/2,
    sizeof(struct component_dct));
    populate_dct(DCTArray, cvcs, methods);
    return DCTArray;
}

/*
 * Purpose: Decompresses a 2D array of component_dct into
 *          a 2D array of component_vcs
 * Notes: The CVCSArray will be twice as large as the DCT
 */
A2Methods_UArray2 decompressDCT(A2Methods_UArray2 dct, A2Methods_T methods)
{
    A2Methods_UArray2 CVCSArray = methods->new(methods->width(dct)*2, 
                                  methods->height(dct)*2,
    sizeof(struct component_vcs));
    populate_CVCS(CVCSArray, dct, methods);
    return CVCSArray;
}