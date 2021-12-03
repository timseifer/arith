#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitpack.h"

int
main(int argc, char *argv[])
{
(void) argc;
(void) argv;
//  printf("Bitpack_getu(0x3f4, 6, 2) == %li\n", Bitpack_getu(0x3f4, 6, 2));

//  printf("Bitpack_gets(0x3f4, 6, 2) == %li\n", Bitpack_gets(0x3f4, 6, 2));

// printf("Bitpack_getu(Bitpack_newu(0x3f4, 6, 2, 3), 6, 2) == %li\n", Bitpack_getu(Bitpack_newu(0x3f4, 6, 2, 3), 6, 2));

// printf("Bitpack_gets(Bitpack_news(0x3f4, 6, 2, -32), 6, 2) == %li\n", Bitpack_gets(Bitpack_news(0x3f4, 6, 2, -32), 6, 2));

// printf("org bit = %lx \nnew bit = %lx \n\n",  0x123456789,  Bitpack_newu(0x123456789, 16, 4, 0xabcd));

// printf("org bit = %lx \nnew bit = %lx \n\n",  0x123456789,  Bitpack_news(0x123456789, 16, 4, (int64_t)-21555));
// printf("org bit = %lx \nnew bit = %lx \n\n",  0x123456789,  Bitpack_newu(0x123456789, 16, 4, 0xabcd));


// printf("org bit = %lx \nnew bit = %lx \n\n",  0x123456789,  Bitpack_news(0x123456789, 16, 4, (int16_t)0xabcd));

// // uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value)
// printf("Bitpack_getu(Bitpack_newu(0xfd213f4, 10, 2, 300), 10, 2) == 300 == %li\n", Bitpack_getu(Bitpack_newu(0xfd213f4, 10, 2, 300), 10, 2));

// printf("Bitpack_gets(Bitpack_news(0xfd213f4, 10, 2, -312), 10, 2) == -312 == %li\n", Bitpack_gets(Bitpack_news(0xfd213f4, 10, 2, -312), 10, 2));


printf("1234 == %lx\n", Bitpack_newu(0x1234567890abcdef, 16, 0, 0x1234));
printf("1234 == %lx\n", Bitpack_news(0x1234567890abcdef, 16, 0, 0x1234));

printf("1234 == %lx\n", Bitpack_newu(0x1234567890abcdef, 16, 48, 0x1234));
printf("1234 == %lx\n", Bitpack_news(0x1234567890abcdef, 16, 48, 0x1234));
// printf("1234 == %lx\n", Bitpack_news(0x00000000, 16, 0, 0x1234));

// printf("12340 == %lx\n", Bitpack_newu(0x00000000, 16, 1, 0x1234));

// printf("12340 == %lx\n", Bitpack_news(0x00000000, 16, 1 , 0x1234));

// printf("6789 == %lx\n", Bitpack_getu(0x123456789, 16, 0));

// printf("6789 == %lx\n", Bitpack_gets(0x123456789, 16, 0));


} 