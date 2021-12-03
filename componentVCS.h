/**************************************************************
 *
 *                     componenetVCS.h
 *
 *     Assignment: Arith
 *     Authors:  Wade Perry (gperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *
 *     summary
 *
 *     componentVCS.h is the interface for decompressing the component_ DCT 
 *     UArray into a CVCS UArray and compressing a UArray of CVCS structs into a
 *     UArray of component_DCT structs.
 *    

 **************************************************************/



#include <pnm.h>
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"

/*
* Purpose: A struct representing a component VCS form.
*/
typedef struct component_vcs{
    float y;
    float pb;
    float pr;
} *component_vcs;

/*
* Purpose: Compress a Pnm_ppm Array
*     into a Component Video Color Space Array
* Arguments: The Pnm_ppm
* Returns: a DCT array
* Effects: 
* Error Cases: a NULL argument
*/
A2Methods_UArray2 compressPPM(Pnm_ppm ppm);

/*
* Purpose: Decompress the Component Video Color Space Array
*        into a Pnm_ppm
* Arguments: The CVS Array to be compressed and methods
* Returns: a Pnm_ppm
* Effects: 
* Error Cases: a NULL argument
*/
Pnm_ppm decompressCVCS(A2Methods_UArray2 cvcs, A2Methods_T methods);