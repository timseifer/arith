/*
 *     componentPacking.c
 *     by Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *     assignment: Arith
 *
 *     summary: implementation for componentPacking.h
*/ 

#include "componentPacking.h"
#include <stdlib.h>
#include <assert.h>

void DCTtoWords (void *ptr, void *cl)
{
    (void)cl;
    uint64_t word = 0;
    component_dct pixelDCT = ptr;
    /*Pack Word*/
    word = Bitpack_newu(word, 6, 26, pixelDCT->a);
    word = Bitpack_news(word, 6, 20, pixelDCT->b);
    word = Bitpack_news(word, 6, 14, pixelDCT->c);
    word = Bitpack_news(word, 6, 8, pixelDCT->d);
    word = Bitpack_newu(word, 4, 4, pixelDCT->avPb);
    word = Bitpack_newu(word, 4, 0, pixelDCT->avPr);
    /*Print out the code word in Big-Endian*/
    for (int i = 3; i >= 0; i--) {
        putchar(Bitpack_getu(word, 8, i * 8));
    }
}

void WordstoDCT (void *ptr, void *cl)
{
    unsigned word = 0;
    /*read the charcters into the word*/
    for (int i = 3; i >= 0; i--) {
        int c = getc(cl);
        assert(c != EOF);
        word = Bitpack_newu(word, 8, i * 8, c);
    }
    /*Create a new DCT pixel*/
    component_dct pixelDCT = malloc(sizeof(struct component_dct));
    /*Unpack word*/
    pixelDCT->a = Bitpack_getu(word, 6, 26);
    pixelDCT->b = Bitpack_gets(word, 6, 20);
    pixelDCT->c = Bitpack_gets(word, 6, 14);
    pixelDCT->d = Bitpack_gets(word, 6, 8);
    pixelDCT->avPb = Bitpack_getu(word, 4, 4);
    pixelDCT->avPr = Bitpack_getu(word, 4, 0);
    /*put the DCT pixel DCT Array*/
    *(component_dct)ptr = *pixelDCT;
    free(pixelDCT);
}

void compressDCT(A2Methods_UArray2 dct, A2Methods_T methods)
{
    printf("COMP40 Compressed image format 2\n%u %u\n", 
            methods->width(dct) * 2, methods->height(dct) * 2);
    methods->small_map_row_major(dct, DCTtoWords, NULL);
}

A2Methods_UArray2 decompressWords(FILE *input, A2Methods_T methods)
{
    unsigned height, width;
    int read = fscanf(input, "COMP40 Compressed image format 2\n%u %u",
                         &width, &height);
    assert(read == 2);
    int c = getc(input);
    assert(c == '\n');
    A2Methods_UArray2 DCTArray =  methods->new(width / 2, height / 2,
    sizeof(struct component_dct));
    methods->small_map_row_major(DCTArray, WordstoDCT, input);
    return DCTArray;
}