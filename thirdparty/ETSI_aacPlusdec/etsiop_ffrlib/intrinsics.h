/*  
   additional intrinsics
 */
#ifndef INTRINSIC_LIB_H
#define INTRINSIC_LIB_H


#include "basic_op.h"
#include "oper_32b.h"

#define SHORT_BITS 16
#define INT_BITS   32
#define OVL_BITS    8

#define memop32(x)   { Word32 i; for(i=0;i<((Word32)(x));i++) { move32(); } }
#define memop16(x)   { Word32 i; for(i=0;i<((Word32)(x));i++) { move16(); } }

Word16 S_max( Word16 a, Word16 b );
Word32 L_max( Word32 a, Word32 b );

Word16 S_min( Word16 a, Word16 b );
Word32 L_min( Word32 a, Word32 b );

void splitWord32 (Word32 in, Word16* lo, Word16* hi);
Word16 logical_shr(Word16 a, Word16 b);


/*
  min max macros
*/
#ifndef min
#define min(a,b) ( a < b ? a : b)
#endif

#ifndef max
#define max(a,b) ( a > b ? a : b)
#endif

//#define aacopt

#ifdef aacopt
#define fixmul_32x16b(a,b) ((Word32)(((Word64)a*(Word64)b >> 15)))
#endif

Word32 fixmul(const Word32 a, const Word32 b);
Word32 fixmuldiv2 (const Word32 a, const Word32 b);
void fixmadd (Word32 *a, const Word32 x, const Word32 y);

#ifndef fixmul_32x16b
Word32 fixmul_32x16b (const Word32 a, const Word16 b);
#endif
Word32 fixmuldiv2_32x16b (const Word32 a, const Word16 b);
Word32 fixmul_32x16t (const Word32 a, const Word32 b);
Word32 fixmuldiv2_32x16t (const Word32 a, const Word32 b);
void fixmadd_32x16t (Word32 *a, const Word32 x, const Word32 y);

#ifndef aacopt
Word32 fixmadd_32x16b_Shift (const Word16 hi1, const Word16 lo1,
                             const Word16 b,
                             const Word16 hi2, const Word16 lo2,
                             const Word16 d,
                             const Word16 shift);
Word32 fixmadd_32x16b (const Word16 hi1, const Word16 lo1,
                       const Word16 b,
                       const Word16 hi2, const Word16 lo2,
                       const Word16 d);
Word32 fixmsub_32x16b_Shift (const Word16 hi1, const Word16 lo1,
                             const Word16 b,
                             const Word16 hi2, const Word16 lo2,
                             const Word16 d,
                             const Word16 shift);
Word32 fixmsub_32x16b (const Word16 hi1, const Word16 lo1,
                       const Word16 b,
                       const Word16 hi2, const Word16 lo2,
                       const Word16 d);
void cplxmulscale (Word32 x [],
                   const Word16 im1_hi, const Word16 im1_lo, 
                   const Word16 wim, 
                   const Word16 re1_hi, const Word16 re1_lo, 
                   const Word16 wre,
                   const Word16 shift);
#endif
#endif
