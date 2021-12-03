/*
 *     bitpack.c
 *     by Wade Perry (jperry04), Tim Seifert(tseife01)
 *     Date:     03/21/2021
 *     assignment: Arith
 *
 *     summary: implementation for bitpack.h
*/ 
#include "bitpack.h"
#include "math.h"
#include "assert.h"
#include <stdio.h>
#include <stdbool.h>

Except_T Bitpack_Overflow = { "Overflow packing bits" };


/*
 * Purpose: Checks to see if unsigned int n
 *          will fit in width bits
 */
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
    if( n > (((uint64_t)1 << width) - 1)){
        return false;
    }
    return true;
}

/*
 * Purpose: Checks to see if signed int n
 *          will fit in width bits
 */
bool Bitpack_fitss( int64_t n, unsigned width)
{
    if ( n < (0 - (((int64_t)1 << width) - ((int64_t)1 << width)/2)) || n > ((
        (int64_t)1 << width) - (((int64_t)1 << width)/2) - 1 )) {
        return false;
    }
    return true;
}

/*
 * Purpose: Get the unsigned int at lsb that is width long
 * Notes: Bits to the left will be zero
 */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width <= 64);
    assert((width+lsb) <= 64);
    word = word << (64 - (width + lsb));
    word = word >> (64 - width);
    return word;
}

/*
 * Purpose: Get the signed int at lsb that is width long
 */
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
    /*Checks to see if the Value is negative*/
    /*If negative the left will be one*/
    if((word >> (lsb + width - 1) ) & 1){
        assert(width <= 64);
        assert((width+lsb) <= 64);
        uint64_t mask = ~0;
        mask = mask << width;
        word = word >> lsb;
        word = word | mask;
        return word;
    }
    /*If not treat as unsigned (Bits to the left will be zero)*/
    return (int64_t)Bitpack_getu(word, width, lsb);
}

/*
 * Purpose: Pack width amount of nits value into word at lsb
 */
uint64_t Universal_new(uint64_t word, unsigned width, unsigned lsb, uint64_t
 value)
{
    assert(width <= 64);
    assert((width+lsb) <= 64);
    /*Create Mask*/
    uint64_t maskLeft = ~0;
    maskLeft = maskLeft << (width + lsb);
    uint64_t mask = ~0;
    mask = mask >> (64 - (lsb));
    /*shifting bits by 64 does nothing so much manually set it to 0*/
    if(lsb == 0){
        mask = 0;
    }
    mask = maskLeft | mask;
    /*Zero bits where value will go*/
    word = word & mask;
    /*Shift value to correct place*/
    value = value << lsb;
    value = value & ~mask;
    /*Add value to word in correct place and return*/
    return word | value;
}

uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t
 value)
{
    if(! Bitpack_fitsu(value, width)){
         RAISE(Bitpack_Overflow);
    }
    return Universal_new(word, width, lsb, value);
}

uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  int64_t 
value)
{
    if(! Bitpack_fitss(value, width)){
        RAISE(Bitpack_Overflow);
    }
    return Universal_new(word, width, lsb, value);
}
