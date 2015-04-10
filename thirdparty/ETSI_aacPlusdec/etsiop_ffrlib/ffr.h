/*
   fractional arithmetric
 */
#ifndef __FFR_H
#define __FFR_H


#include <stdarg.h>
#include "intrinsics.h"
#include "typedef.h"

#define LOG_DUALIS_TABLE_SIZE   65   /*!< Number of entries for ld(x) lookup table used by ffr_logDualisDiv8(x) */
#define INV_TABLE_SIZE         256   /*!< Number of entries for 0.5/x lookup table. */
#define SQRT_TABLE_SIZE        256   /*!< Number of entries for sqrt(x) lookup table. */

#define POW2_TABLE_BITS 8
#define POW2_TABLE_SIZE (1<<POW2_TABLE_BITS)

Word16 ffr_iLog4(Word32 value);
Word32 ffr_pow2_xy(Word32 x, Word32 y);
Word32 ffr_div32_32(Word32 x, Word32 y);
Word16 ffr_Short_Mult(Word16 x, Word16 y);
Word16 ffr_Short_Div(Word16 x, Word16 y);
Word32 ffr_Integer_Mult(Word32 x, Word32 y);
Word32 ffr_Integer_Mult16x16(Word32 x, Word32 y);
Word32 ffr_Integer_Div(Word32 x, Word32 y);

Word32 ffr_divideWord32(Word32 a, Word32 b);
Word16 ffr_logDualisDiv8(Word32 a);
Word16 ffr_getNumOctavesDiv8(Word32 a, Word32 b);
Word32 ffr_sqrt(Word32 op, Word32 accuracy);
void   ffr_add_MantExp(Word16 a_m, Word16 a_e,  Word16 b_m, Word16 b_e,  Word16 *ptrSum_m, Word16 *ptrSum_e);
void   ffr_divide_MantExp(Word16 a_m, Word16 a_e,  Word16 b_m, Word16 b_e,  Word16 *ptrResult_m, Word16 *ptrResult_e);
void   ffr_sqrt_MantExp(Word16 *mant, Word16 *exp);
Word32 ffr_divide16(Word32 divident, Word32 divisor);

Word16 ffr_getScalefactorOfShortVector(const Word16 *vector, Word16 len);
Word16 ffr_getScalefactorOfShortVectorStride(const Word16 *vector, Word16 len, Word16 stride);
Word16 ffr_getScalefactorOfWord32Vector(const Word32 *vector, Word16 len);
void   ffr_scaleWord32Vector(Word32 *vector,Word32 len,Word16 scalefactor);
void   ffr_scaleShortVector(Word16 *vector,Word32 len,Word16 scalefactor);

Word16 ffr_norm32(Word32 x);
#endif
