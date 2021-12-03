/*
 *     compress40.c
 *     by Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *     assignment: Arith
 *
 *     summary: implementation for compress40.h
*/ 

#include "compress40.h"
#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include <stdbool.h>
#include "componentPacking.h"
#include <stdio.h>
#include <stdlib.h>

void freeHelper(void* ptr, void* cl){
    (void)cl;
    free(ptr);
}

void populate(int col, int row, A2Methods_UArray2 array2,
             void *ptr, void *cl)
{
    (void)ptr;
    struct Pnm_ppm *ppm = cl;
    Pnm_rgb pixel = (ppm)->methods->at(ppm->pixels, col, row);
    Pnm_rgb pixel2 = (ppm)->methods->at(array2, col, row);
    *pixel2 = *pixel;
}

A2Methods_UArray2 populate_new(Pnm_ppm pnm, A2Methods_T methods)
{
    A2Methods_UArray2 myArray = methods->new(pnm->width, 
                    pnm->height, sizeof(struct Pnm_rgb));
    methods->map_row_major(myArray, populate, pnm);
    return myArray;
}


extern void compress40  (FILE *input){
    A2Methods_T methods = uarray2_methods_plain;
    Pnm_ppm pnm = Pnm_ppmread(input, methods);
    /*Test to see if odd height or width*/
    int newWidth = pnm->width;
    int newHeight = pnm->height;
    bool flag = false;
    if (!(newWidth % 2 == 0)) {
        newWidth--;
        flag = true;
    }
    if (!(newHeight % 2 == 0)) {
        newHeight--;
        flag = true;
    } 
    /*If odd correct*/
    if (flag) {
        pnm->width = newWidth;
        pnm->height = newHeight;
        A2Methods_UArray2 myArray = populate_new(pnm, methods);
        methods->free(&(pnm->pixels));
        pnm->pixels = myArray;
    }
    /*Begin Compression*/
    A2Methods_UArray2 cvcs = compressPPM(pnm);
    A2Methods_UArray2 dct = compressCVCS(cvcs, methods);
    compressDCT(dct, methods);
    /*free data structures*/
    methods->free(&cvcs);
    methods->free(&dct);
    Pnm_ppmfree(&pnm);  
}

extern void decompress40(FILE *input){
    assert(input != NULL);
    A2Methods_T methods = uarray2_methods_plain;
    /*Begin Decompression*/
    A2Methods_UArray2 dct = decompressWords(input, methods);
    A2Methods_UArray2 cvcs = decompressDCT(dct, methods); 
    Pnm_ppm pnm = decompressCVCS(cvcs, methods);
    Pnm_ppmwrite(stdout, pnm);
    /*free data structures*/
    methods->free(&cvcs);
    methods->free(&dct);
    Pnm_ppmfree(&pnm);
}