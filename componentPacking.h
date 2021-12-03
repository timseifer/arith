/**************************************************************
 *
 *                     componenetPacking.h
 *
 *     Assignment: Arith
 *     Authors:  Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *
 *     summary
 *
 *     componentPacking.h is the interface for packing a DCT pixel
 *     representation to a compressed bit character representation.
 *     Values are printed to standard output.
 **************************************************************/



#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "bitpack.h"
#include "componentDCT.h"
#include <stdio.h>

/*
* Purpose: Compress DCT is the last stage of compression and utilizes
*          the bitpacking interface to output our DCT pixels in a predefined 
*          bit characters representations to standarad output.
* Arguments: A Uarray of component_DCT structs and an instance of A2Methods_T
* Returns: N/A
* Effects: Gives the compressed character representation of the image
* Error Cases: a NULL argument. Since compressDCT utilizes bitpack it is
* possible to get a Hanson bit overflow checked run-time error on invalid bits.
*/
void compressDCT(A2Methods_UArray2 dct, A2Methods_T methods);

/*
* Purpose: 
* Arguments: A File* reprsenting standard input, and an instance of A2Methods_T
* Returns: a UArray which stores component_DCT structs.
* Effects: the DCT array will be larger than the fully compressed format but 
* still relatively small (on the magnitude of bits).
* Error Cases: a NULL argument. Invalid format from standard input (not right 
* number of pixels, last element is invalid).
*/
A2Methods_UArray2 decompressWords(FILE *input, A2Methods_T methods);