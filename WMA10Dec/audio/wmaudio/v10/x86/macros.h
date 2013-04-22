#ifndef __X86_MACROS_H
#define __X86_MACROS_H

// Bring in platform-independent macros
#   define MULT_HI_DWORD_DOWN(a,b) (I32)((((I64)(a))*((I64)(b)))>>30)
#   define MULT_HI_DWORD(a,b) (I32)((((I64)(a))*((I64)(b)))>>32)
#   define MULT_HI_DWORDN(a,b,N) (I32)((((I64)(a))*((I64)(b)))>>(32-(N)))
#   define MULT_HI_DWORDM(a,b,M) MULT_HI_DWORDN(a,b,M)

// Unsigned version of multiply
#   define MULT_HI_UDWORD(a,b) (U32)((((U64)(a))*((U64)(b)))>>32)

#ifdef FUSED_MUL_ADD
//  provide a more accurate reference path for implementations that have fused multiply-accumulate
#   define MULT_ADD2_HI_DWORD_DOWN(a,b,c,d) (I32)(( (((I64)(a))*((I64)(b))) + (((I64)(c))*((I64)(d))) )>>30)
#   define MULT_ADD2_HI_DWORD(a,b,c,d) (I32)(( (((I64)(a))*((I64)(b))) + (((I64)(c))*((I64)(d))) )>>32)
#   define MULT_ADD2_HI_DWORDN(a,b,c,d,N) (I32)(( (((I64)(a))*((I64)(b))) + (((I64)(c))*((I64)(d))) )>>(32-(N)))
#   define MULT_ADD2_HI_UDWORD(a,b,c,d) (U32)(( (((U64)(a))*((U64)(b))) + (((U64)(c))*((U64)(d))) )>>32)
#else //FUSED_MUL_ADD
//  otherwise, truncate to 32-bits between each multiply.
#   define MULT_ADD2_HI_DWORD_DOWN(a,b,c,d) (MULT_HI_DWORD_DOWN(a,b) + MULT_HI_DWORD_DOWN(c,d))
#   define MULT_ADD2_HI_DWORD(a,b,c,d) (MULT_HI_DWORD(a,b) + MULT_HI_DWORD(c,d))
#   define MULT_ADD2_HI_DWORDN(a,b,c,d,N) ((MULT_HI_DWORDN(a,b,N) + MULT_HI_DWORDN(c,d,N))
#   define MULT_ADD2_HI_UDWORD(a,b,c,d) (MULT_HI_UDWORD(a,b) + MULT_HI_UDWORD(c,d))
#endif //FUSED_MUL_ADD

#define PLATFORM_SPECIFIC_ROUND
STATIC_INLINE I32   ROUNDF(float f)
{
    if (f < 0.0f)
        return (I32) (f - 0.5f);
    else
        return (I32) (f + 0.5f);
}

STATIC_INLINE I32   ROUNDD(double f)
{
    if (f < 0.0f)
        return (I32) (f - 0.5f);
    else
        return (I32) (f + 0.5f);
} // PLATFORM_SPECIFIC_ROUND

#define PLATFORM_SPECIFIC_DIVI64BYU32
STATIC_INLINE I32 DIVI64BYU32(I64 a, U32 b) {
    return (I32)((a)/(b));
}

#define PLATFORM_SPECIFIC_CEILOFLOG2
#define CEILOFLOG2(iDivPow2, iMean) {for (iDivPow2 = 0; ((U32)1 << iDivPow2) < iMean; iDivPow2++);}

#endif  // __X86_MACROS_H