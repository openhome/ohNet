/*
   Double Precision FFT, with scaling
 */
#include <assert.h>
#include "dsp_fft32x32s.h"
#include "intrinsics.h"

#include "typedef.h"
#include "basic_op.h"
#include "oper_32b.h"
#include "count.h"

#include <string.h>

static const Word16 __sineTable8_16 [8] =
{
  -0x0000, -0x18f9, -0x30fc, -0x471d,
  -0x5a82, -0x6a6e, -0x7642, -0x7d8a,
} ;


static void
butterfly32a_16( Word32 ro, Word32 io, Word16 rwh, Word16 iwh, Word32 *rx, Word32 *ix )
{
  Word16 roh, rol, ioh, iol;
  Word32 acc;

  splitWord32(ro, &rol, &roh);
  splitWord32(io, &iol, &ioh);

  acc = L_mult(roh, rwh);
  acc = L_msu(acc, ioh, iwh);
  acc = L_mac(acc, mult(rol, rwh), 1);
  acc = L_msu(acc, mult(iol, iwh), 1);
  *rx = acc;                                            move32();
  acc = L_mult(roh, iwh);
  acc = L_mac(acc, ioh, rwh);
  acc = L_mac(acc, mult(rol, iwh), 1);
  acc = L_mac(acc, mult(iol, rwh), 1);
  *ix = acc;                                            move32();
}

static void
butterfly32b_16( Word32 ro, Word32 io, Word16 ch, Word16 sh, Word32 *rx, Word32 *ix )
{
  Word16 roh, rol, ioh, iol;
  Word32 acc;

  splitWord32(ro, &rol, &roh);
  splitWord32(io, &iol, &ioh);

  acc = L_mult(roh, ch);
  acc = L_mac(acc, ioh, sh);
  acc = L_mac(acc, mult(rol, ch), 1);
  acc = L_mac(acc, mult(iol, sh), 1);
  *rx = acc;                                            move32();
  acc = L_mult(ioh, ch);
  acc = L_msu(acc, roh, sh);
  acc = L_mac(acc, mult(iol, ch), 1);
  acc = L_msu(acc, mult(rol, sh), 1);
  *ix = acc;                                            move32();
}

static void __fft16 (Word32 x [])
{
  Word32 a0, a1, a2, a3, a00, a10, a20, a30 ;
  Word32 tr, ti, vr, vi ;
  Word32 temp [32] ;

  a00 = L_add(x[0], x[16]) ;
  a0  = L_sub(x[0], x[16]) ;

  a10 = L_add(x[8], x[24]) ;
  a2  = L_sub(x[8], x[24]) ;

  a20 = L_add(x[1], x[17]) ;
  a3  = L_sub(x[1], x[17]) ;

  a30 = L_add(x[9], x[25]) ;
  a1  = L_sub(x[9], x[25]) ;

  temp [0] = L_add(a00, a10) ;        move32();
  temp [4] = L_sub(a00, a10) ;        move32();
  temp [1] = L_add(a20, a30) ;        move32();
  temp [5] = L_sub(a20, a30) ;        move32();
  temp [2] = L_add(a1, a0) ;          move32();
  temp [6] = L_sub(a0, a1) ;          move32();
  temp [3] = L_sub(a3, a2) ;          move32();
  temp [7] = L_add(a2, a3) ;          move32();

  a00 = L_add(x[ 4], x[20]) ;
  a0  = L_sub(x[ 4], x[20]) ;

  a10 = L_add(x[12], x[28]) ;
  a2  = L_sub(x[12], x[28]) ;

  a20 = L_add(x[ 5], x[21]) ;
  a3  = L_sub(x[ 5], x[21]) ;

  a30 = L_add(x[13], x[29]) ;
  a1  = L_sub(x[13], x[29]) ;

  temp [8]  = L_add(a00, a10) ;       move32();
  temp [12] = L_sub(a00, a10) ;       move32();
  temp [9]  = L_add(a20, a30) ;       move32();
  temp [13] = L_sub(a20, a30) ;       move32();
  temp [10] = L_add(a1, a0) ;         move32();
  temp [14] = L_sub(a1, a0) ;         move32();
  temp [11] = L_sub(a3, a2) ;         move32();
  temp [15] = L_add(a2, a3) ;         move32();

  a00 = L_add(x[ 2], x[18]) ;
  a0  = L_sub(x[ 2], x[18]) ;

  a10 = L_add(x[10], x[26]) ;
  a2  = L_sub(x[10], x[26]) ;

  a20 = L_add(x[ 3], x[19]) ;
  a3  = L_sub(x[ 3], x[19]) ;

  a30 = L_add(x[11], x[27]) ;
  a1  = L_sub(x[11], x[27]) ;

  temp [16] = L_add(a00, a10) ;       move32();
  temp [20] = L_sub(a00, a10) ;       move32();
  temp [17] = L_add(a20, a30) ;       move32();
  temp [21] = L_sub(a20, a30) ;       move32();
  temp [18] = L_add(a1, a0) ;         move32();
  temp [22] = L_sub(a0, a1) ;         move32();
  temp [19] = L_sub(a3, a2) ;         move32();
  temp [23] = L_add(a2, a3) ;         move32();

  a00 = L_add(x[ 6], x[22]) ;
  a0  = L_sub(x[ 6], x[22]) ;

  a10 = L_add(x[14], x[30]) ;
  a2  = L_sub(x[14], x[30]) ;

  a20 = L_add(x[ 7], x[23]) ;
  a3  = L_sub(x[ 7], x[23]) ;

  a30 = L_add(x[15], x[31]) ;
  a1  = L_sub(x[15], x[31]) ;

  temp [24] = L_add(a00, a10) ;       move32();
  temp [28] = L_sub(a00, a10) ;       move32();
  temp [25] = L_add(a20, a30) ;       move32();
  temp [29] = L_sub(a20, a30) ;       move32();
  temp [26] = L_add(a1, a0) ;         move32();
  temp [30] = L_sub(a1, a0) ;         move32();
  temp [27] = L_sub(a3, a2) ;         move32();
  temp [31] = L_add(a2, a3) ;         move32();



  a0  = L_add(temp[ 0], temp[ 8]);
  a2  = L_sub(temp[ 0], temp[ 8]);

  a1  = L_add(temp[ 1], temp[ 9]);
  a3  = L_sub(temp[ 1], temp[ 9]);

  a00 = L_add(temp[16], temp[24]);
  a20 = L_sub(temp[16], temp[24]);

  a10 = L_add(temp[17], temp[25]);
  a30 = L_sub(temp[17], temp[25]);

  x [0]  = L_add(a0, a00) ;           move32();
  x [16] = L_sub(a0, a00) ;           move32();

  x [1]  = L_add(a1, a10) ;           move32();
  x [17] = L_sub(a1, a10) ;           move32();

  x [8]  = L_add(a2, a30) ;           move32();
  x [24] = L_sub(a2, a30) ;           move32();

  x [9]  = L_sub(a3, a20) ;           move32();
  x [25] = L_add(a3, a20) ;           move32();



  tr = fixmul_32x16b(temp [10], -__sineTable8_16[4]);
  ti = fixmul_32x16b(temp [11], -__sineTable8_16[4]);
  vr = L_add(ti, tr) ;
  vi = L_sub(ti, tr) ;

  a0 = L_add(temp [2], vr) ;
  a2 = L_sub(temp [2], vr) ;

  a1 = L_add(temp [3], vi) ;
  a3 = L_sub(temp [3], vi) ;

  tr = fixmul_32x16b(temp [26], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(temp [27], -__sineTable8_16[4]) ;

  vr = L_add(ti, tr) ;

  a00 = L_add(vr, temp [18]) ;
  a20 = L_sub(vr, temp [18]) ;

  vi = L_sub(ti, tr) ;

  a10 = L_add(temp [19], vi) ;
  a30 = L_sub(temp [19], vi) ;

  butterfly32b_16(a00, a10, -__sineTable8_16[6], -__sineTable8_16[2], &vr, &vi);
  x [2]  = L_add(a0, vr) ;                    move32();
  x [18] = L_sub(a0, vr) ;                    move32();
  x [3]  = L_add(a1, vi) ;                    move32();
  x [19] = L_sub(a1, vi) ;                    move32();

  butterfly32b_16(a30, a20, -__sineTable8_16[6], -__sineTable8_16[2], &vr, &vi);
  x [10] = L_add(a2, vr) ;                    move32();
  x [26] = L_sub(a2, vr) ;                    move32();
  x [11] = L_add(a3, vi) ;                    move32();
  x [27] = L_sub(a3, vi) ;                    move32();



  a0 = L_add(temp[4], temp[13]);
  a2 = L_sub(temp[4], temp[13]);

  a1 = L_sub(temp[5], temp[12]);
  a3 = L_add(temp[5], temp[12]);

  a00 = L_add(temp [29], temp [20]) ;
  a20 = L_sub(temp [29], temp [20]) ;

  a10 = L_sub(temp [21], temp [28]) ;
  a30 = L_add(temp [21], temp [28]) ;

  tr = fixmul_32x16b(a00, -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(a10, -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(ti, tr) ;

  x [4]  = L_add(a0, vr) ;                    move32();
  x [20] = L_sub(a0, vr) ;                    move32();

  x [5]  = L_add(a1, vi) ;                    move32();
  x [21] = L_sub(a1, vi) ;                    move32();

  tr = fixmul_32x16b(a20, -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(a30, -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(tr, ti) ;

  x [12] = L_add(a2, vr) ;                    move32();
  x [28] = L_sub(a2, vr) ;                    move32();

  x [13] = L_add(a3, vi) ;                    move32();
  x [29] = L_sub(a3, vi) ;                    move32();



  tr = fixmul_32x16b(temp [14], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(temp [15], -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(tr, ti) ;

  a0 = L_add(temp [6], vr) ;
  a2 = L_sub(temp [6], vr) ;

  a1 = L_add(temp [7], vi) ;
  a3 = L_sub(temp [7], vi) ;

  tr = fixmul_32x16b(temp [30], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(temp [31], -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;

  a00 = L_add(vr, temp [22]) ;
  a20 = L_sub(vr, temp [22]) ;

  vi = L_sub(tr, ti) ;

  a10 = L_add(temp [23], vi) ;
  a30 = L_sub(temp [23], vi) ;

  butterfly32b_16(a00, a10, -__sineTable8_16[2], -__sineTable8_16[6], &vr, &vi);
  x [6]  = L_add(a0, vr) ;                    move32();
  x [22] = L_sub(a0, vr) ;                    move32();
  x [7]  = L_add(a1, vi) ;                    move32();
  x [23] = L_sub(a1, vi) ;                    move32();

  butterfly32b_16(a30, a20, -__sineTable8_16[2], -__sineTable8_16[6], &vr, &vi);
  x [14] = L_add(a2, vr) ;                    move32();
  x [30] = L_sub(a2, vr) ;                    move32();
  x [15] = L_add(a3, vi) ;                    move32();
  x [31] = L_sub(a3, vi) ;                    move32();
}

static void __fft2x16 (Word32 x [])
{
  Word32 a0, a1, a2, a3, a00, a10, a20, a30 ;
  Word32 tr, ti, vr, vi ;

  Word32 even [32], odd [32] ;

  a00 = L_add(x[4*0], x[4*8]);
  a0  = L_sub(x[4*0], x[4*8]);
  a10 = L_add(x[4*4], x[4*12]);
  a2  = L_sub(x[4*4], x[4*12]);
  a20 = L_add(x[4*0+1], x[4*8+1]);
  a3  = L_sub(x[4*0+1], x[4*8+1]);
  a30 = L_add(x[4*4+1], x[4*12+1]);
  a1  = L_sub(x[4*4+1], x[4*12+1]);
  even[0] = L_add(a00, a10) ;                 move32();
  even[4] = L_sub(a00, a10) ;                 move32();
  even[1] = L_add(a20, a30) ;                 move32();
  even[5] = L_sub(a20, a30) ;                 move32();
  even[2] = L_add(a1, a0) ;                   move32();
  even[6] = L_sub(a0, a1) ;                   move32();
  even[3] = L_sub(a3, a2) ;                   move32();
  even[7] = L_add(a2, a3) ;                   move32();

  a00 = L_add(x[4*0+2], x[4*8+2]);
  a0  = L_sub(x[4*0+2], x[4*8+2]);
  a10 = L_add(x[4*4+2], x[4*12+2]);
  a2  = L_sub(x[4*4+2], x[4*12+2]);
  a20 = L_add(x[4*0+3], x[4*8+3]);
  a3  = L_sub(x[4*0+3], x[4*8+3]);
  a30 = L_add(x[4*4+3], x[4*12+3]);
  a1  = L_sub(x[4*4+3], x[4*12+3]);
  odd[0] = L_add(a00, a10) ;                  move32();
  odd[4] = L_sub(a00, a10) ;                  move32();
  odd[1] = L_add(a20, a30) ;                  move32();
  odd[5] = L_sub(a20, a30) ;                  move32();
  odd[2] = L_add(a1, a0) ;                    move32();
  odd[6] = L_sub(a0, a1) ;                    move32();
  odd[3] = L_sub(a3, a2) ;                    move32();
  odd[7] = L_add(a2, a3) ;                    move32();

  a00 = L_add(x[4*2], x[4*10]);
  a0  = L_sub(x[4*2], x[4*10]);
  a10 = L_add(x[4*6], x[4*14]);
  a2  = L_sub(x[4*6], x[4*14]);
  a20 = L_add(x[4*2+1], x[4*10+1]);
  a3  = L_sub(x[4*2+1], x[4*10+1]);
  a30 = L_add(x[4*6+1], x[4*14+1]);
  a1  = L_sub(x[4*6+1], x[4*14+1]);
  even[8]  = L_add(a00, a10) ;                move32();
  even[12] = L_sub(a00, a10) ;                move32();
  even[9]  = L_add(a20, a30) ;                move32();
  even[13] = L_sub(a20, a30) ;                move32();
  even[10] = L_add(a1, a0) ;                  move32();
  even[14] = L_sub(a1, a0) ;                  move32();
  even[11] = L_sub(a3, a2) ;                  move32();
  even[15] = L_add(a2, a3) ;                  move32();

  a00 = L_add(x[4*2+2], x[4*10+2]);
  a0  = L_sub(x[4*2+2], x[4*10+2]);
  a10 = L_add(x[4*6+2], x[4*14+2]);
  a2  = L_sub(x[4*6+2], x[4*14+2]);
  a20 = L_add(x[4*2+3], x[4*10+3]);
  a3  = L_sub(x[4*2+3], x[4*10+3]);
  a30 = L_add(x[4*6+3], x[4*14+3]);
  a1  = L_sub(x[4*6+3], x[4*14+3]);
  odd[8]  = L_add(a00, a10) ;                 move32();
  odd[12] = L_sub(a00, a10) ;                 move32();
  odd[9]  = L_add(a20, a30) ;                 move32();
  odd[13] = L_sub(a20, a30) ;                 move32();
  odd[10] = L_add(a1, a0) ;                   move32();
  odd[14] = L_sub(a1, a0) ;                   move32();
  odd[11] = L_sub(a3, a2) ;                   move32();
  odd[15] = L_add(a2, a3) ;                   move32();

  a00 = L_add(x[4*1], x[4*9]);
  a0  = L_sub(x[4*1], x[4*9]);
  a10 = L_add(x[4*5], x[4*13]);
  a2  = L_sub(x[4*5], x[4*13]);
  a20 = L_add(x[4*1+1], x[4*9+1]);
  a3  = L_sub(x[4*1+1], x[4*9+1]);
  a30 = L_add(x[4*5+1], x[4*13+1]);
  a1  = L_sub(x[4*5+1], x[4*13+1]);
  even[16] = L_add(a00, a10) ;                move32();
  even[20] = L_sub(a00, a10) ;                move32();
  even[17] = L_add(a20, a30) ;                move32();
  even[21] = L_sub(a20, a30) ;                move32();
  even[18] = L_add(a1, a0) ;                  move32();
  even[22] = L_sub(a0, a1) ;                  move32();
  even[19] = L_sub(a3, a2) ;                  move32();
  even[23] = L_add(a2, a3) ;                  move32();

  a00 = L_add(x[4*1+2], x[4*9+2]);
  a0  = L_sub(x[4*1+2], x[4*9+2]);
  a10 = L_add(x[4*5+2], x[4*13+2]);
  a2  = L_sub(x[4*5+2], x[4*13+2]);
  a20 = L_add(x[4*1+3], x[4*9+3]);
  a3  = L_sub(x[4*1+3], x[4*9+3]);
  a30 = L_add(x[4*5+3], x[4*13+3]);
  a1  = L_sub(x[4*5+3], x[4*13+3]);
  odd[16] = L_add(a00, a10) ;                 move32();
  odd[20] = L_sub(a00, a10) ;                 move32();
  odd[17] = L_add(a20, a30) ;                 move32();
  odd[21] = L_sub(a20, a30) ;                 move32();
  odd[18] = L_add(a1, a0) ;                   move32();
  odd[22] = L_sub(a0, a1) ;                   move32();
  odd[19] = L_sub(a3, a2) ;                   move32();
  odd[23] = L_add(a2, a3) ;                   move32();

  a00 = L_add(x[4*3], x[4*11]);
  a0  = L_sub(x[4*3], x[4*11]);
  a10 = L_add(x[4*7], x[4*15]);
  a2  = L_sub(x[4*7], x[4*15]);
  a20 = L_add(x[4*3+1], x[4*11+1]);
  a3  = L_sub(x[4*3+1], x[4*11+1]);
  a30 = L_add(x[4*7+1], x[4*15+1]);
  a1  = L_sub(x[4*7+1], x[4*15+1]);
  even[24] = L_add(a00, a10) ;                move32();
  even[28] = L_sub(a00, a10) ;                move32();
  even[25] = L_add(a20, a30) ;                move32();
  even[29] = L_sub(a20, a30) ;                move32();
  even[26] = L_add(a1, a0) ;                  move32();
  even[30] = L_sub(a1, a0) ;                  move32();
  even[27] = L_sub(a3, a2) ;                  move32();
  even[31] = L_add(a2, a3) ;                  move32();

  a00 = L_add(x[4*3+2], x[4*11+2]);
  a0  = L_sub(x[4*3+2], x[4*11+2]);
  a10 = L_add(x[4*7+2], x[4*15+2]);
  a2  = L_sub(x[4*7+2], x[4*15+2]);
  a20 = L_add(x[4*3+3], x[4*11+3]);
  a3  = L_sub(x[4*3+3], x[4*11+3]);
  a30 = L_add(x[4*7+3], x[4*15+3]);
  a1  = L_sub(x[4*7+3], x[4*15+3]);
  odd[24] = L_add(a00, a10) ;                 move32();
  odd[28] = L_sub(a00, a10) ;                 move32();
  odd[25] = L_add(a20, a30) ;                 move32();
  odd[29] = L_sub(a20, a30) ;                 move32();
  odd[26] = L_add(a1, a0) ;                   move32();
  odd[30] = L_sub(a1, a0) ;                   move32();
  odd[27] = L_sub(a3, a2) ;                   move32();
  odd[31] = L_add(a2, a3) ;                   move32();



  a0  = L_add(even [ 0], even [ 8]) ;
  a2  = L_sub(even [ 0], even [ 8]) ;

  a1  = L_add(even [ 1], even [ 9]) ;
  a3  = L_sub(even [ 1], even [ 9]) ;

  a00 = L_add(even [16], even [24]) ;
  a20 = L_sub(even [16], even [24]) ;

  a10 = L_add(even [17], even [25]) ;
  a30 = L_sub(even [17], even [25]) ;

  x [0]  = L_add(a0, a00) ;                   move32();
  x [16] = L_sub(a0, a00) ;                   move32();

  x [1]  = L_add(a1, a10) ;                   move32();
  x [17] = L_sub(a1, a10) ;                   move32();

  x [8]  = L_add(a2, a30) ;                   move32();
  x [24] = L_sub(a2, a30) ;                   move32();

  x [9]  = L_sub(a3, a20) ;                   move32();
  x [25] = L_add(a3, a20) ;                   move32();



  tr = fixmul_32x16b(even[10], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(even[11], -__sineTable8_16[4]) ;

  vr = L_add(ti, tr) ;
  vi = L_sub(ti, tr) ;

  a0 = L_add(even [2], vr) ;
  a2 = L_sub(even [2], vr) ;

  a1 = L_add(even [3], vi) ;
  a3 = L_sub(even [3], vi) ;

  tr = fixmul_32x16b(even[26], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(even[27], -__sineTable8_16[4]) ;

  vr = L_add(ti, tr) ;

  a00 = L_add(vr, even [18]) ;
  a20 = L_sub(vr, even [18]) ;

  vi = L_sub(ti, tr) ;

  a10 = L_add(even [19], vi) ;
  a30 = L_sub(even [19], vi) ;

  butterfly32b_16(a00, a10, -__sineTable8_16[6], -__sineTable8_16[2], &vr, &vi);
  x [2]  = L_add(a0, vr) ;                    move32();
  x [18] = L_sub(a0, vr) ;                    move32();
  x [3]  = L_add(a1, vi) ;                    move32();
  x [19] = L_sub(a1, vi) ;                    move32();

  butterfly32b_16(a30, a20, -__sineTable8_16[6], -__sineTable8_16[2], &vr, &vi);
  x [10] = L_add(a2, vr) ;                    move32();
  x [26] = L_sub(a2, vr) ;                    move32();
  x [11] = L_add(a3, vi) ;                    move32();
  x [27] = L_sub(a3, vi) ;                    move32();



  a0 = L_add(even [4], even [13]) ;
  a2 = L_sub(even [4], even [13]) ;

  a1 = L_sub(even [5], even [12]) ;
  a3 = L_add(even [5], even [12]) ;

  a00 = L_add(even [29], even [20]) ;
  a20 = L_sub(even [29], even [20]) ;

  a10 = L_sub(even [21], even [28]) ;
  a30 = L_add(even [21], even [28]) ;

  tr = fixmul_32x16b(a00, -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(a10, -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(ti, tr) ;

  x [4]  = L_add(a0, vr) ;                    move32();
  x [20] = L_sub(a0, vr) ;                    move32();

  x [5]  = L_add(a1, vi) ;                    move32();
  x [21] = L_sub(a1, vi) ;                    move32();

  tr = fixmul_32x16b(a20, -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(a30, -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(tr, ti) ;

  x [12] = L_add(a2, vr) ;                    move32();
  x [28] = L_sub(a2, vr) ;                    move32();

  x [13] = L_add(a3, vi) ;                    move32();
  x [29] = L_sub(a3, vi) ;                    move32();



  tr = fixmul_32x16b(even[14], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(even[15], -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(tr, ti) ;

  a0 = L_add(even [6], vr) ;
  a2 = L_sub(even [6], vr) ;

  a1 = L_add(even [7], vi) ;
  a3 = L_sub(even [7], vi) ;

  tr = fixmul_32x16b(even[30], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(even[31], -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;

  a00 = L_add(vr, even [22]) ;
  a20 = L_sub(vr, even [22]) ;

  vi = L_sub(tr, ti) ;

  a10 = L_add(even [23], vi) ;
  a30 = L_sub(even [23], vi) ;

  butterfly32b_16(a00, a10, -__sineTable8_16[2], -__sineTable8_16[6], &vr, &vi);
  x [6]  = L_add(a0, vr) ;                    move32();
  x [22] = L_sub(a0, vr) ;                    move32();
  x [7]  = L_add(a1, vi) ;                    move32();
  x [23] = L_sub(a1, vi) ;                    move32();

  butterfly32b_16(a30, a20, -__sineTable8_16[2], -__sineTable8_16[6], &vr, &vi);
  x [14] = L_add(a2, vr) ;                    move32();
  x [30] = L_sub(a2, vr) ;                    move32();
  x [15] = L_add(a3, vi) ;                    move32();
  x [31] = L_sub(a3, vi) ;                    move32();



  a0  = L_add(odd [ 0], odd [ 8]) ;
  a2  = L_sub(odd [ 0], odd [ 8]) ;

  a1  = L_add(odd [ 1], odd [ 9]) ;
  a3  = L_sub(odd [ 1], odd [ 9]) ;

  a00 = L_add(odd [16], odd [24]) ;
  a20 = L_sub(odd [16], odd [24]) ;

  a10 = L_add(odd [17], odd [25]) ;
  a30 = L_sub(odd [17], odd [25]) ;

  x [32+0]  = L_add(a0, a00) ;                move32();
  x [32+16] = L_sub(a0, a00) ;                move32();

  x [32+1]  = L_add(a1, a10) ;                move32();
  x [32+17] = L_sub(a1, a10) ;                move32();

  x [32+8]  = L_add(a2, a30) ;                move32();
  x [32+24] = L_sub(a2, a30) ;                move32();

  x [32+9]  = L_sub(a3, a20) ;                move32();
  x [32+25] = L_add(a3, a20) ;                move32();



  tr = fixmul_32x16b(odd[10], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(odd[11], -__sineTable8_16[4]) ;

  vr = L_add(ti, tr) ;
  vi = L_sub(ti, tr) ;

  a0 = L_add(odd [2], vr) ;
  a2 = L_sub(odd [2], vr) ;

  a1 = L_add(odd [3], vi) ;
  a3 = L_sub(odd [3], vi) ;

  tr = fixmul_32x16b(odd[26], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(odd[27], -__sineTable8_16[4]) ;

  vr = L_add(ti, tr) ;

  a00 = L_add(vr, odd [18]) ;
  a20 = L_sub(vr, odd [18]) ;

  vi = L_sub(ti, tr) ;

  a10 = L_add(odd [19], vi) ;
  a30 = L_sub(odd [19], vi) ;

  butterfly32b_16(a00, a10, -__sineTable8_16[6], -__sineTable8_16[2], &vr, &vi);
  x [32+2]  = L_add(a0, vr) ;                 move32();
  x [32+18] = L_sub(a0, vr) ;                 move32();
  x [32+3]  = L_add(a1, vi) ;                 move32();
  x [32+19] = L_sub(a1, vi) ;                 move32();

  butterfly32b_16(a30, a20, -__sineTable8_16[6], -__sineTable8_16[2], &vr, &vi);
  x [32+10] = L_add(a2, vr) ;                 move32();
  x [32+26] = L_sub(a2, vr) ;                 move32();
  x [32+11] = L_add(a3, vi) ;                 move32();
  x [32+27] = L_sub(a3, vi) ;                 move32();



  a0 = L_add(odd [4], odd [13]) ;
  a2 = L_sub(odd [4], odd [13]) ;

  a1 = L_sub(odd [5], odd [12]) ;
  a3 = L_add(odd [5], odd [12]) ;

  a00 = L_add(odd [29], odd [20]) ;
  a20 = L_sub(odd [29], odd [20]) ;

  a10 = L_sub(odd [21], odd [28]) ;
  a30 = L_add(odd [21], odd [28]) ;

  tr = fixmul_32x16b(a00, -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(a10, -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(ti, tr) ;

  x [32+4]  = L_add(a0, vr) ;                 move32();
  x [32+20] = L_sub(a0, vr) ;                 move32();

  x [32+5]  = L_add(a1, vi) ;                 move32();
  x [32+21] = L_sub(a1, vi) ;                 move32();

  tr = fixmul_32x16b(a20, -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(a30, -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(tr, ti) ;

  x [32+12] = L_add(a2, vr) ;                 move32();
  x [32+28] = L_sub(a2, vr) ;                 move32();

  x [32+13] = L_add(a3, vi) ;                 move32();
  x [32+29] = L_sub(a3, vi) ;                 move32();



  tr = fixmul_32x16b(odd[14], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(odd[15], -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;
  vi = L_sub(tr, ti) ;

  a0 = L_add(odd [6], vr) ;
  a2 = L_sub(odd [6], vr) ;

  a1 = L_add(odd [7], vi) ;
  a3 = L_sub(odd [7], vi) ;

  tr = fixmul_32x16b(odd[30], -__sineTable8_16[4]) ;
  ti = fixmul_32x16b(odd[31], -__sineTable8_16[4]) ;

  vr = L_add(tr, ti) ;

  a00 = L_add(vr, odd [22]) ;
  a20 = L_sub(vr, odd [22]) ;

  vi = L_sub(tr, ti) ;

  a10 = L_add(odd [23], vi) ;
  a30 = L_sub(odd [23], vi) ;

  butterfly32b_16(a00, a10, -__sineTable8_16[2], -__sineTable8_16[6], &vr, &vi);
  x [32+6]  = L_add(a0, vr) ;                 move32();
  x [32+22] = L_sub(a0, vr) ;                 move32();
  x [32+7]  = L_add(a1, vi) ;                 move32();
  x [32+23] = L_sub(a1, vi) ;                 move32();

  butterfly32b_16(a30, a20, -__sineTable8_16[2], -__sineTable8_16[6], &vr, &vi);
  x [32+14] = L_add(a2, vr) ;                 move32();
  x [32+30] = L_sub(a2, vr) ;                 move32();
  x [32+15] = L_add(a3, vi) ;                 move32();
  x [32+31] = L_sub(a3, vi) ;                 move32();
}

static void __fft32 (Word32 x [])
{
  Word16 m;
  Word32 re, ie, ro, io, rx, ix ;
  Word32 *x1m, *x2m, *x1mm, *x2mm;

  __fft2x16 (x) ;

  /* merge */

  re = x[ 0] ;                                move32();
  ie = x[ 1] ;                                move32();

  x[0]  = L_add(re, x[32]) ;                  move32();
  x[32] = L_sub(re, x[32]) ;                  move32();
  x[1]  = L_add(ie, x[33]) ;                  move32();
  x[33] = L_sub(ie, x[33]) ;                  move32();



  re = x[16] ;                                move32();
  ie = x[17] ;                                move32();

  ro = x[48] ;                                move32();
  io = x[49] ;                                move32();

  x[16] = L_add(re, io) ;                     move32();
  x[48] = L_sub(re, io) ;                     move32();
  x[17] = L_sub(ie, ro) ;                     move32();
  x[49] = L_add(ie, ro) ;                     move32();



  x1m = &x[2 + 0];                            move16();
  x2m = &x[2 + 32];                           move16();
  x1mm = &x[31];                              move16();
  x2mm = &x[63];                              move16();
  for (m = 1 ; m < 8 ; m++)
  {
    Word16 rw;
    rw = negate(__sineTable8_16 [8 - m]) ;

    re = *x1m++ ;                                 move32();
    ie = *x1m-- ;                                 move32();

    butterfly32a_16(x2m[0], x2m[1], rw, __sineTable8_16 [m], &rx, &ix);
    *x1m++ = L_add(re, rx) ;                      move32();
    *x1m++ = L_add(ie, ix) ;                      move32();
    *x2m++ = L_sub(re, rx) ;                      move32();
    *x2m++ = L_sub(ie, ix) ;                      move32();



    ie = *x1mm-- ;                                move32();
    re = *x1mm++ ;                                move32();

    io = *x2mm-- ;                                move32();
    ro = *x2mm++ ;                                move32();

    butterfly32a_16(ro, io, __sineTable8_16 [8-m], __sineTable8_16 [m], &rx, &ix);

    *x1mm-- = L_add(ie, ix) ;                     move32();
    *x1mm-- = L_add(re, rx) ;                     move32();
    *x2mm-- = L_sub(ie, ix) ;                     move32();
    *x2mm-- = L_sub(re, rx) ;                     move32();
  }
}


void DSP_fft32x32s(Word32 npoints, Word32 * ptr_x)
{
  assert( (npoints ==16) || (npoints==32) );

  test(); sub(0,0);
  if(npoints == 16){
    __fft16(ptr_x);
  } else {
    __fft32(ptr_x);
  }
}


void inv_dit_fft_8pt(Word32 *y,   /*!< Pointer to input vector */
                     Word32 *real,
                     Word32 *imag)
{
  Word32 a0, a1, a2, a3, a00, a10, a20, a30;
  Word32 vr, vi;

  Word32 x[16];

  a00 = L_add(y[0], y[8]);		/* Re A + Re B */
  a0  = L_sub(y[0], y[8]);		/* Re A - Re B */

  a20 = L_add(y[1], y[9]);		/* Im A + Im B */
  a3  = L_sub(y[1], y[9]);		/* Im A - Im B */

  a10 = L_add(y[4], y[12]);		/* Re C + Re D */
  a2  = L_sub(y[4], y[12]);		/* Re C - Re D */

  a30 = L_add(y[5], y[13]);		/* Im C + Im D */
  a1  = L_sub(y[5], y[13]);		/* Im C - Im D */

  x[0] = L_add(a00, a10);		move32();	/* Re A '= ReA + ReB +ReC + ReD */
  x[4] = L_sub(a00, a10);		move32();	/* Re C' = -(ReC+ReD) + (ReA+ReB) */
  x[1] = L_add(a20, a30);		move32();	/* Im A' = sum of imag values */
  x[5] = L_sub(a20, a30);		move32();	/* Im C' = -Im C -Im D +Im A +Im B */

  x[2] = L_sub(a0, a1);			move32();	/* Re B' = Im C - Im D  + Re A - Re B */
  x[6] = L_add(a0, a1);			move32();	/* Re D' = -Im C + Im D + Re A - Re B */
  x[3] = L_add(a3, a2);			move32();	/* Im B' = -Re C + Re D + Im A - Im B */
  x[7] = L_sub(a3, a2);			move32();	/* Im D' = Re C - Re D + Im A - Im B */

  a00 = L_add(y[2], y[10]);		/* Re A + Re B */
  a0  = L_sub(y[2], y[10]);		/* Re A - Re B */

  a20 = L_add(y[3], y[11]);		/* Im A + Im B */
  a3  = L_sub(y[3], y[11]);		/* Im A - Im B */

  a10 = L_add(y[6], y[14]);		/* Re C + Re D */
  a2  = L_sub(y[6], y[14]);		/* Re C - Re D */

  a30 = L_add(y[7], y[15]);		/* Im C + Im D */
  a1  = L_sub(y[7], y[15]);		/* Im C - Im D */

  x[8]  = L_add(a00, a10);		move32();	/* Re A '= ReA + ReB +ReC + ReD */
  x[12] = L_sub(a00, a10);		move32();	/* Re C' = -(ReC+ReD) + (ReA+ReB) */
  x[9]  = L_add(a20, a30);		move32();	/* Im A' = sum of imag values */
  x[13] = L_sub(a20, a30);		move32();	/* Im C' = -Im C -Im D +Im A +Im B */

  x[10] = L_sub(a0, a1);		move32();	/* Re B' = Im C - Im D  + Re A - Re B */
  x[14] = L_add(a0, a1);		move32();	/* Re D' = -Im C + Im D + Re A - Re B */
  x[11] = L_add(a3, a2);		move32();	/* Im B' = -Re C + Re D + Im A - Im B */
  x[15] = L_sub(a3, a2);		move32();	/* Im D' = Re C - Re D + Im A - Im B */

  real[0] = L_add(x[0], x[8]);	move32();	/* x[0] */
  imag[0] = L_add(x[1], x[9]);	move32();	/* x[1] */
  real[4] = L_sub(x[0], x[8]);	move32();	/* x[8] */
  imag[4] = L_sub(x[1], x[9]);	move32();	/* x[9] */

  real[2] = L_sub(x[4], x[13]);	move32();	/* x[4] */
  imag[2] = L_add(x[5], x[12]);	move32();	/* x[5] */
  real[6] = L_add(x[4], x[13]);	move32();	/* x[12] */
  imag[6] = L_sub(x[5], x[12]);	move32();	/* x[13] */

  vr = fixmul_32x16b(L_sub(x[10], x[11]), 0x5A82);
  vi = fixmul_32x16b(L_add(x[10], x[11]), 0x5A82);

  real[1] = L_add(x[2], vr);	move32();	/* x[2] */
  imag[1] = L_add(x[3], vi);	move32();	/* x[3] */
  real[5] = L_sub(x[2], vr);	move32();	/* x[10] */
  imag[5] = L_sub(x[3], vi);	move32();	/* x[11] */

  vr = fixmul_32x16b(L_add(x[14], x[15]), 0x5A82);
  vi = fixmul_32x16b(L_sub(x[14], x[15]), 0x5A82);

  real[3] = L_sub(x[6], vr);	move32();	/* x[6] */
  imag[3] = L_add(x[7], vi);	move32();	/* x[7] */
  real[7] = L_add(x[6], vr);	move32();	/* x[14] */
  imag[7] = L_sub(x[7], vi);	move32();	/* x[15] */
}

