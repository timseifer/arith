
#include <string.h>
#include <a2plain.h>
#include "uarray2.h"
#include <assert.h>

/************************************************/
/* Define a private version of each function in */
/* A2Methods_T that we implement.               */
/************************************************/
typedef A2Methods_UArray2 A2;   

/* create a new UArray2 based on a width height and size */
static A2Methods_UArray2 new(int width, int height, int size)
{
  return UArray2_new(width, height, size);
}
/* create a new UArray2 without a blocksize */
static A2Methods_UArray2 new_with_blocksize(int width, int height,
                                  int size, int blocksize)
{
  (void) blocksize;
  return  UArray2_new(width, height, size);
}
/* frees the uarray2 */
static void a2free(A2Methods_UArray2* uarray2)
{
        UArray2_free((UArray2_T *) uarray2);
}
/* get the width of our UArray2 */
static int width(A2 uarray2)
{
        return UArray2_width(uarray2);
}
/* get the height of our UArray2 */
static int height(A2 uarray2)
{
        return UArray2_height(uarray2);
}
/* get the size of our UArray2 */
static int size(A2 uarray2)
{
        return UArray2_size(uarray2);
}
/* get the blocksize of our UArray2 */
static int blocksize(A2 uarray2)
{
  assert(uarray2 != NULL);
        return 1;
}
/* get the an element out of the array specifiying an index */
static A2Methods_Object *at(A2 array2, int i, int j){
        return UArray2_at(array2, i, j);
}

/* various mapping functions are listed below */
static void map_row_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
  UArray2_map_row_major(uarray2, (UArray2_applyfun*)apply, cl);
}

static void map_col_major(A2Methods_UArray2 uarray2,
                          A2Methods_applyfun apply,
                          void *cl)
{
  UArray2_map_col_major(uarray2, (UArray2_applyfun*)apply, cl);
}

/* Already implemented small_closure struct by the spec */
struct small_closure {
  A2Methods_smallapplyfun *apply; 
  void                    *cl;
};

static void apply_small(int i, int j, UArray2_T uarray2,
                        void *elem, void *vcl)
{
  struct small_closure *cl = vcl;
  (void)i;
  (void)j;
  (void)uarray2;
  cl->apply(elem, cl->cl);
}

static void small_map_row_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
  struct small_closure mycl = { apply, cl };
  UArray2_map_row_major(a2, apply_small, &mycl);
}

static void small_map_col_major(A2Methods_UArray2        a2,
                                A2Methods_smallapplyfun  apply,
                                void *cl)
{
  struct small_closure mycl = { apply, cl };
  UArray2_map_col_major(a2, apply_small, &mycl);
}

/* A2Methods function pointers are properly set */
static struct A2Methods_T uarray2_methods_plain_struct = {
  new,
  new_with_blocksize,
  a2free,
  width,
  height,
  size,
  blocksize,
  at,
  map_row_major,
  map_col_major,
  NULL, //map-block
  map_row_major, //map default
  small_map_row_major,
  small_map_col_major,
  NULL, //small block
  small_map_row_major, //small block
};

// finally the payoff: here is the exported pointer to the struct

A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;
