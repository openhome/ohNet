/* 
   additional intrinsics
 */
#include <stdlib.h>
#include "intrinsics.h"
#include "limits.h"
#include "count.h"

Word16 S_max( Word16 a, Word16 b ) {

  Word16 temp;
  temp = sub(a,b);                    test();
  if ( temp < 0 )
    return b;
  else
    return a;
}

Word32 L_max( Word32 a, Word32 b ) {

  Word32 temp;
  temp = L_sub(a,b);                  test();
  if ( temp < 0 )
    return b;
  else
    return a;
}


Word16 S_min( Word16 a, Word16 b ) {

  Word16 temp;
  temp = sub(a,b);                    test();
  if ( temp < 0 )
    return a;
  else
    return b;
}

Word32 L_min( Word32 a, Word32 b ) {

  Word32 temp;
  temp = L_sub(a,b);                  test();
  if ( temp < 0 )
    return a;
  else
    return b;
}


/* #define ACCOUNT_ETSIOP_OVERHEAD_SPLITWORD32 */

void splitWord32 (Word32 in, Word16* lo, Word16* hi)
{
#ifdef ACCOUNT_ETSIOP_OVERHEAD_SPLITWORD32
  /* 
     this is a method to derive WMOPS accounting for the overhead
     caused by ETSI 16-bit operators to split a Word32 into 
     low and half Word16 and prepare for DPF processing
  */
  *lo = logical_shr(extract_l(in), 1);
  *hi = extract_h(in);
#else
  /* 
     This is a method to access low and high half word without 
     counting any penalty as most 16-bit DSPs support this 
     addressing natively.

     Furthermore to achieve bit-exactness to the ETSIop DPF format
     masking of the highest bit of the lower half word has to be 
     performed. However, since most 16-bit DSPs support an unsigned 
     multiplication and as such a real 32x16, resp. 32x32, (rather 
     than a 31x16, resp. 31x31) multiplication can be performed
     without any additional overhead, omitting the corresponding WMOPS 
     counting will result in a more realistic total WMOPS number.
  */
  *lo = ((in>>1) & 0x7FFF);
  *hi = (in>>16);
#endif
}


Word16 logical_shr(Word16 a, Word16 b)
{
  logic16();
  return (shr(a,b) & 0x7FFF);
}

Word32 fixmul (const Word32 a, const Word32 b)
{
  Word16 hi1, lo1, hi2, lo2;

  splitWord32 (a, &lo1, &hi1);
  splitWord32 (b, &lo2, &hi2);

  return Mpy_32(hi1, lo1, hi2, lo2);
}

Word32 fixmuldiv2 (const Word32 a, const Word32 b)
{
  return L_shr(fixmul(a,b),1);
}

void fixmadd (Word32 *a, const Word32 x, const Word32 y)
{
  *a = L_add(*a, fixmuldiv2(x,y)); move32();
}

Word32 fixmul_32x16b (const Word32 a, const Word16 b)
{
  Word16 hi, lo;

  splitWord32(a, &lo, &hi);  

  return Mpy_32_16(hi, lo, b);
}

Word32 fixmuldiv2_32x16b (const Word32 a, const Word16 b)
{
  return L_shr(fixmul_32x16b(a,b),1);
}

Word32 fixmul_32x16t (const Word32 a, const Word32 b)
{
  Word16 hi, lo, n;
  
  splitWord32(a, &lo, &hi);  

  n = extract_h(b);

  return Mpy_32_16(hi, lo, n);
}
 
Word32 fixmuldiv2_32x16t (const Word32 a, const Word32 b)
{
  return L_shr(fixmul_32x16t(a,b), 1);
}
 
void fixmadd_32x16t (Word32 *a, const Word32 x, const Word32 y)
{
  *a = L_add(*a, fixmuldiv2_32x16t(x, y));
}


Word32 fixmadd_32x16b_Shift (const Word16 hi1, const Word16 lo1,
                             const Word16 b,
                             const Word16 hi2, const Word16 lo2,
                             const Word16 d,
                             const Word16 shift)
{
  return L_add( L_shr(Mpy_32_16 (hi1, lo1, b), shift),
                L_shr(Mpy_32_16 (hi2, lo2, d), shift) ) ;
}

Word32 fixmadd_32x16b (const Word16 hi1, const Word16 lo1,
                       const Word16 b,
                       const Word16 hi2, const Word16 lo2,
                       const Word16 d)
{
  Word32 accu;

  accu = L_mult (hi1, b);
  accu = L_mac (accu, mult (lo1, b), 1);
  accu = L_mac (accu, hi2, d);
  accu = L_mac (accu, mult (lo2, d), 1);

  return (accu);
}

Word32 fixmsub_32x16b_Shift (const Word16 hi1, const Word16 lo1,
                             const Word16 b,
                             const Word16 hi2, const Word16 lo2,
                             const Word16 d,
                             const Word16 shift)
{
  return L_sub( L_shr(Mpy_32_16 (hi1, lo1, b), shift) ,
                L_shr(Mpy_32_16 (hi2, lo2, d), shift) ) ;
}

Word32 fixmsub_32x16b (const Word16 hi1, const Word16 lo1,
                       const Word16 b,
                       const Word16 hi2, const Word16 lo2,
                       const Word16 d)
{
  Word32 accu;

  accu = L_mult (hi1, b);
  accu = L_mac (accu, mult (lo1, b), 1);
  accu = L_msu (accu, hi2, d);
  accu = L_msu (accu, mult (lo2, d), 1);

  return (accu);
}

void cplxmulscale (Word32 x [],
                   const Word16 im1_hi, const Word16 im1_lo, 
                   const Word16 wim, 
                   const Word16 re1_hi, const Word16 re1_lo, 
                   const Word16 wre,
                   const Word16 shift)
{
  x [0] = fixmadd_32x16b_Shift (im1_hi, im1_lo, wim, re1_hi, re1_lo, wre, shift) ;  move32();
  x [1] = fixmsub_32x16b_Shift (im1_hi, im1_lo, wre, re1_hi, re1_lo, wim, shift) ;  move32();
}

