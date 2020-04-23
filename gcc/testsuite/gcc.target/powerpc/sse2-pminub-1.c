/* { dg-do run } */
/* { dg-options "-O3 -mpower8-vector -Wno-psabi" } */
/* { dg-require-effective-target p8vector_hw } */

#ifndef CHECK_H
#define CHECK_H "sse2-check.h"
#endif

#include CHECK_H

#ifndef TEST
#define TEST sse2_test_pminub_1
#endif

#include <emmintrin.h>

static __m128i
__attribute__((noinline, unused))
test (__m128i s1, __m128i s2)
{
  return _mm_min_epu8 (s1, s2); 
}

static void
TEST (void)
{
  union128i_ub u, s1, s2;
  unsigned char e[16];
  int i;
   
  s1.x = _mm_set_epi8 (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
  s2.x = _mm_set_epi8 (16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1);
  u.x = test (s1.x, s2.x);

  for (i=0; i<16; i++)
    e[i] = s1.a[i]<s2.a[i]?s1.a[i]:s2.a[i]; 

  if (check_union128i_ub (u, e))
    abort ();
}
