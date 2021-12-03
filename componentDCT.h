/**************************************************************
 *
 *                     componenetDCT.h
 *
 *     Assignment: Arith
 *     Authors:  Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *
 *     summary
 *
 *     componentDCT.h is the interface for a compressed PPM's 
 *     rgb values in discrete cosine transform. This is where the 
 *
 **************************************************************/


#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "componentVCS.h"

/*
* Purpose: A struct that reprsent the values necessary for a DCT representation.
*/
typedef struct component_dct { 
    unsigned avPb;
    unsigned avPr;
    unsigned a;
    int b;
    int c;
    int d;
} *component_dct;


/*
* Purpose: Compress the Component Video Color Space Array
*      into a Discrete Cosine Transform Array
* Arguments: The CVS Array to be compressed and methods
* Returns: a DCT array
* Effects: the DCT array will be a quarter the size of CVCQuantization in range 
* loses a very small amount of accuracy.
* Error Cases: a NULL argument
*/
A2Methods_UArray2 compressCVCS(A2Methods_UArray2 cvcs, A2Methods_T methods);

/*
* Purpose: decompress a Discrete Cosine Transform UArray into a Component Video
*          form UArray.
* Arguments: A Uarray that stores DCT structs and an A2Methods_T instance.
* Returns: A Uarray of Component Video structs
* Effects: Creates a UArray of CVCS structs. Quantization in range loses a very
* small amount of accuracy.
* Error Cases: a NULL argument
*/
A2Methods_UArray2 decompressDCT(A2Methods_UArray2 dct, A2Methods_T methods);
