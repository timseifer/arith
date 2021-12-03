#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppmdiff.h"
#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

int
main(int argc, char *argv[])
{
    if(argc != 3){
        fprintf(stderr, "ppmdiff takes 2 arguments\n");
        exit(EXIT_FAILURE);
    }
    A2Methods_T methods = uarray2_methods_plain; 
    FILE* fp1 = fopen(argv[1], "r");
    FILE* fp2 = NULL;
    Pnm_ppm ppmOne = Pnm_ppmread(fp1, methods);
    Pnm_ppm ppmTwo;
                if(strcmp(argv[2],"-") == 0) {
                        ppmTwo = Pnm_ppmread(stdin, methods);
                } else { 
            fp2 = fopen(argv[2], "r");
            ppmTwo = Pnm_ppmread(fp2, methods);
                }
    assert(ppmOne != NULL && ppmTwo != NULL);
    check(ppmOne, ppmTwo);
    printf("%f\n", compute_diff(ppmOne, ppmTwo));
}