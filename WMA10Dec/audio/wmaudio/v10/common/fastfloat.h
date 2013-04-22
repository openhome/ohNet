//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 2006

Module Name:

    fastfloat.h

Abstract:

    "fast" floating-point emulation for integer implementations.

    under BUILD_INTEGER, FastFloat is an exponent & mantissa stored in
    two int32 members of a structure. The macros defined are for use in
    fixed-point implementation.

    under BUILD_INT_FLOAT, FastFloat is simply a 'float' type, and all
    macros map to floating-point operations.

Author:

Revision History:


*************************************************************************/

#if defined(BUILD_INTEGER)
    // FastFloat
    // FastFloat is a quick way of handling values that exceed I32 range without incurring
    // the expense of floating point emulation on integer only platforms.
    // real value = iFraction * pow( 2, -iFracBits )
    // In debugger, iFraction*1.0F/(1<<iFracBits) works if 0<=iFracBits<31

    // Normalize a FastFloat
#if !defined(WMA_OPT_NORM_ARM) || !WMA_OPT_NORM_ARM
INLINE void Norm4FastFloat( FastFloat* pfflt )
    {   // use the faster Norm4FastFloatU when you know the value is positive
        register UInt uiF = abs(pfflt->iFraction);
        register Int iFB = 0;

        if ( uiF == 0 )
        {
            pfflt->iFracBits = 0;
            return;
        }
        while ( uiF < 0x20000000 )
        {
            uiF <<= 2;
            iFB +=  2;
        }
        if ( uiF < 0x40000000 )
        {
            iFB +=  1;
        }
        pfflt->iFraction <<= iFB;
        pfflt->iFracBits  += iFB;
    }

INLINE void Norm4FastFloatU( FastFloat* pfflt )
    {   // same as above when we know value is positive (which we often do)
        register UInt uiF = pfflt->iFraction;
        register Int iFB = 0;
        assert( uiF > 0 );
        while ( uiF < 0x20000000 )
        {
            uiF  <<= 2;
            iFB +=  2;
        }
        if ( uiF < 0x40000000 )
        {
            uiF  <<= 1;
            iFB +=  1;
        }
        pfflt->iFraction = uiF;
        pfflt->iFracBits += iFB;
    }
#else
#define Norm4FastFloatU Norm4FastFloat
void Norm4FastFloat( FastFloat* pfflt );
#endif  // WMA_OPT_NORM_ARM

INLINE FastFloat ffltMultiply( FastFloat ffltA, FastFloat ffltB )
{
    FastFloat ffltP;
    ffltP.iFraction = MULT_HI( ffltA.iFraction, ffltB.iFraction );
    ffltP.iFracBits = (ffltA.iFracBits + ffltB.iFracBits - 31);
    Norm4FastFloat( &ffltP );
    return ffltP;
}
#   define FASTFLOAT_MULT(a,b) ffltMultiply((a),(b))

INLINE I32 I32FromFFLT(FastFloat fflt, Int bits)
{
    if (bits >= fflt.iFracBits)
        return (fflt.iFraction << (bits-fflt.iFracBits));
    else
        return (fflt.iFraction >> min((fflt.iFracBits-bits), 31));
}

INLINE FastFloat FFLTFromI32(Int i32, Int bits)
{
    FastFloat ffltP;
    ffltP.iFraction = i32;
    ffltP.iFracBits = bits;
    Norm4FastFloat(&ffltP);
    return ffltP;
}

INLINE FastFloat ffltNegate(FastFloat fflt)
{
    fflt.iFraction = -fflt.iFraction;
    return fflt;
}

INLINE FastFloat ffltAbs(FastFloat fflt)
{
    fflt.iFraction = ABS(fflt.iFraction);
    return fflt;
}

U32 isqrt( U32 x );
//INLINE Float FloatFromFastFloat( FastFloat fflt );
//double  __cdecl sqrt(double);
INLINE FastFloat ffltSqrt(FastFloat fflt)
{
    //Float a = (Float)sqrt(max(0, FloatFromFastFloat(fflt)));

    if (fflt.iFracBits & 1)
    {
        if (fflt.iFraction > 0x3FFFFFFF)
        {
            fflt.iFraction >>= 1;
            fflt.iFracBits--;
        }
        else
        {
            fflt.iFraction <<= 1;
            fflt.iFracBits++;
        }
    }

    // zero-check: sqrt(0) == 0.

    if (0 == fflt.iFraction)
        return fflt;

#define ONE      (1<<28)

    while( fflt.iFraction >= 4*ONE )
    {
        fflt.iFraction >>= 2;
        fflt.iFracBits  -= 2;
    }
    while( fflt.iFraction < ONE )
    {
        fflt.iFraction <<= 2;
        fflt.iFracBits  += 2;
    }
#undef ONE

    fflt.iFraction = isqrt(max(fflt.iFraction, 0));
    fflt.iFracBits -= 28;
    fflt.iFracBits /= 2;
    fflt.iFracBits += 28;

    Norm4FastFloat(&fflt);

    //{
    //    Float b = FloatFromFastFloat(fflt);
    //    assert(ABS(a - b)/a < 0.001f ||  ABS(a-b)<0.001f);
    //}

    return fflt;
}

#define FASTFLOAT_SQRT( fflt ) ffltSqrt( fflt )

INLINE FastFloat ffltfltMultiply( FastFloat ffltA, Int B , Int bits)
{

    FastFloat ffltP;
    ffltP.iFracBits = ffltA.iFracBits;

    assert( I32_MAX >= (( ffltA.iFraction * (I64)B) >> bits ));
    assert( I32_MIN <= (( ffltA.iFraction * (I64)B) >> bits ));

    ffltP.iFraction = MULT_HI32_SHIFT(ffltA.iFraction, B, bits);
    Norm4FastFloat(&ffltP);

    return ffltP;
}
#   define FASTFLOAT_FLOAT_MULT(a,b,bits) ffltfltMultiply((a), (b), (bits))

INLINE FastFloat ffltAdd( FastFloat ffltA, FastFloat ffltB )
{
    FastFloat ffltP;
    Int iShift;

    if (ABS(ffltA.iFraction) > 0x3FFFFFFF)
    {
        ffltA.iFraction >>= 1;
        ffltA.iFracBits--;
    }
    if (ABS(ffltB.iFraction) > 0x3FFFFFFF)
    {
        ffltB.iFraction >>= 1;
        ffltB.iFracBits--;
    }

    if ((ffltA.iFracBits >= ffltB.iFracBits && ffltB.iFraction != 0) ||
        ffltA.iFraction == 0)
    {
        iShift = ffltA.iFracBits-ffltB.iFracBits;
        iShift = min(iShift, 31);
        ffltP.iFracBits = ffltB.iFracBits;
        ffltP.iFraction = ffltB.iFraction + (ffltA.iFraction>>iShift);
    }
    else
    {
        iShift = ffltB.iFracBits-ffltA.iFracBits;
        iShift = min(iShift, 31);
        ffltP.iFracBits = ffltA.iFracBits;
        ffltP.iFraction = ffltA.iFraction + (ffltB.iFraction>>iShift);
    }

    Norm4FastFloat(&ffltP);

    return ffltP;
}

#   define FASTFLOAT_ADD(a,b) ffltAdd((a),(b))

INLINE FastFloat ffltSub( FastFloat ffltA, FastFloat ffltB )
{
    FastFloat ffltP;
    Int iShift;

    if (ABS(ffltA.iFraction) > 0x3FFFFFFF)
    {
        ffltA.iFraction >>= 1;
        ffltA.iFracBits--;
    }
    if (ABS(ffltB.iFraction) > 0x3FFFFFFF)
    {
        ffltB.iFraction >>= 1;
        ffltB.iFracBits--;
    }

    if ((ffltA.iFracBits >= ffltB.iFracBits && ffltB.iFraction != 0) ||
        ffltA.iFraction == 0)
    {
        iShift = ffltA.iFracBits-ffltB.iFracBits;
        iShift = min(iShift, 31);
        ffltP.iFracBits = ffltB.iFracBits;
        ffltP.iFraction = -ffltB.iFraction + (ffltA.iFraction>>iShift);
    }
    else
    {
        iShift = ffltB.iFracBits-ffltA.iFracBits;
        iShift = min(iShift, 31);
        ffltP.iFracBits = ffltA.iFracBits;
        ffltP.iFraction = ffltA.iFraction - (ffltB.iFraction>>iShift);
    }
    Norm4FastFloat(&ffltP);
    return ffltP;
}

#define FASTFLOAT_SUB(a,b) ffltSub((a),(b))

INLINE FastFloat ffltDivide( FastFloat ffltA, const FastFloat ffltB )
{
    assert( 0 != ffltB.iFraction );

    if( ( 0 == ffltA.iFraction ) || ( ( 0 <= ffltB.iFracBits )
          && ( ffltB.iFraction   ==   ( 1 << ffltB.iFracBits ) )))
    {
        // a == 0 or b == 1.

        return ffltA;
    }
    else
    {
        I64 i64 = ( (I64)ffltA.iFraction << 32 ) / ffltB.iFraction;
        U32 u32 = ( 0 > i64 ) ? (U32)(-i64>>31) : (U32)(i64>>31);

        if( 0xffff < u32 ){ u32 >>= 16; i64 >>= 16; ffltA.iFracBits -= 16; }
        if( 0x00ff < u32 ){ u32 >>=  8; i64 >>=  8; ffltA.iFracBits -=  8; }
        if(   0    < u32 ){ u32 >>=  8; i64 >>=  8; ffltA.iFracBits -=  8; }

        assert( I32_MAX >= i64 && I32_MIN <= i64 );

        ffltA.iFraction  = (I32)i64;
        ffltA.iFracBits += 32 - ffltB.iFracBits;

        // Norm4FastFloat(&ffltA);

        return ffltA;
    }
}

#   define FASTFLOAT_DIV(a,b) ffltDivide((a),(b))

INLINE FastFloat ffltfltDivide( FastFloat ffltA, const Int B, const Int bits )
{
    assert( 0 != B );

    if( 0 == ffltA.iFraction )
    {
        // a == 0.
        return ffltA;
    }
    else
    {
        // assume that ffltA is normalized, so that ffltA.iFraction
        // is "full" ( max range used ). Then shifting up by 32 and
        // dividing by B will result in ( minimally ) the original
        // number of bits of precision, but will actually be more
        // since B < (1<<31). So, shift down until the number fits
        // within 32 bits. This guarantees max precision, and the
        // resulting FastFloat will already be normalized.

        I64 i64 = ( (I64)ffltA.iFraction << 32 ) / B;
        U32 u32 = ( 0 > i64 ) ? (U32)(-i64>>31) : (U32)(i64>>31);

        if( 0xffff < u32 ){ u32 >>= 16; i64 >>= 16; ffltA.iFracBits -= 16; }
        if( 0x00ff < u32 ){ u32 >>=  8; i64 >>=  8; ffltA.iFracBits -=  8; }
        if(   0    < u32 ){ u32 >>=  8; i64 >>=  8; ffltA.iFracBits -=  8; }

        assert( I32_MAX >= i64 && I32_MIN <= i64 );

        ffltA.iFraction  = (I32)i64;
        ffltA.iFracBits += 32 - bits;

        //Norm4FastFloat(&ffltA); // not needed.
    
        return ffltA;
    }
}

#   define FASTFLOAT_FLOAT_DIV(a,b,bits) ffltfltDivide((a),(b),(bits))

INLINE FastFloat FastFloatFromFloat(Float flt) {
        FastFloat fflt;
        Float fltScale = (Float)(1<<(31-24));
        fflt.iFracBits = 24;

        // perform a bounds-check on the
        // incoming floating-point value.

        if( FLT_MAX < flt ) flt = FLT_MAX;
        if( FLT_MIN > flt ) flt = FLT_MIN;

        while( flt <= -fltScale || fltScale <= flt )
        {
            fflt.iFracBits -= 1;
            fltScale *= 2;
        }

        assert( 31 > abs(fflt.iFracBits) );

        if( 0 > fflt.iFracBits )
            fflt.iFraction = (I32)(flt/(1<<-fflt.iFracBits));
        else
            fflt.iFraction = (I32)(flt*(1<<fflt.iFracBits));

        // sign check!

        assert(( 0 >  fflt.iFraction && 0 > flt ) ||
               ( 0 <  fflt.iFraction && 0 < flt ) ||
                 0 == fflt.iFraction );

        Norm4FastFloat( &fflt );
        return fflt;
    }   

    // floor of log2(flt)
INLINE Int Log2FromFloat(Float flt) {
        Int i = 0;
        Float fltScale = 2.0;
        assert(flt >= 0.0);
        while (fltScale <= flt) {
            i++;
            fltScale *= 2;
        }
        return i;
    }

    // floor of log2(fflt.iFraction*2^-fflt.iFracBits)
    //  = floor(log2(fflt.iFraction)) - fflt.iFracBits
INLINE Int Log2FromFastFloat(FastFloat fflt) {
        return LOG2(fflt.iFraction) - fflt.iFracBits;
    }
    
INLINE Float FloatFromFastFloat( FastFloat fflt )
    {
        // this assert is for catching some tiny numbers.
        // assert( 0<= fflt.iFracBits && fflt.iFracBits <= 70 );

        if ( fflt.iFracBits > 70)
            return 0.0f;
        else if ( fflt.iFracBits > 50 )
            return fflt.iFraction/(1099511627776.0f*(1<<(fflt.iFracBits-40)));
        else if ( fflt.iFracBits > 30 )
            return fflt.iFraction/(1048576.0F*(1<<(fflt.iFracBits-20)));
        else if ( fflt.iFracBits > 0 )
            return fflt.iFraction/((Float)(1<<fflt.iFracBits));
        else if ( fflt.iFracBits == 0 )
            return (Float)fflt.iFraction;
        else if ( fflt.iFracBits > -30 )
            return (Float)fflt.iFraction*(1<<-fflt.iFracBits);
        
        assert( !"number is too big!" );
            return 0;
    }

INLINE FastFloat FastFloatFromInt( Int flt )
    {
        FastFloat fflt;

        fflt.iFraction = flt;
        fflt.iFracBits = 0;

        Norm4FastFloat(&fflt);

        return fflt;
    }

#   define FASTFLOAT_FROM_INT(flt) FastFloatFromInt(flt)
#   define FASTFLOAT_FROM_FLOAT(flt) FastFloatFromFloat(flt)
#   define FLOAT_FROM_FASTFLOAT(fflt) FloatFromFastFloat(fflt)
#   define DOUBLE_FROM_FASTFLOAT(fflt) ((double)fflt.iFraction/(1<<fflt.iFracBits))

static const FastFloat FFLT_ZERO = {0};
static const FastFloat FFLT_ONE  = {30,(1<<30)};
static const FastFloat FFLT_INV_SQRT2 = { 30, (U32)((1<<30)*(FLT_INV_SQRT2)+.5) };

INLINE FastFloat FastFloatFromU64(U64 u64, Int cExp)
    {
        FastFloat fflt;
        U32 uiMSF = (U32)(u64>>32);
        Int iExp = 0;
        if ( uiMSF==0 ) {
            iExp = 32;
            uiMSF = (U32)u64;
        }
        if (uiMSF==0) {
            fflt.iFracBits = 0;
            fflt.iFraction = 0;
            return fflt;
        }
        // normalize the most significant fractional part
        while( (uiMSF & 0xF0000000)==0 ) {
            iExp += 3;
            uiMSF <<= 3;
        }
        while( (uiMSF & 0xC0000000)==0 ) {
            iExp++;
            uiMSF <<= 1;
        }
        // number of fractional bits
        fflt.iFracBits = iExp+cExp-32;
#if defined(PLATFORM_OPTIMIZE_MINIMIZE_BRANCHING)
        fflt.iFraction = (U32)((u64<<iExp)>>32);
#else
        fflt.iFraction = (iExp>32) ? (U32)(u64<<(iExp-32)) : (U32)(u64>>(32-iExp));
#endif
        return fflt;
    }   
#define FASTFLOAT_FROM_U64(u64,exp) FastFloatFromU64(u64,exp)


typedef FastFloat QuantStepType;
#define DOUBLE_FROM_QUANTSTEPTYPE(qst) DOUBLE_FROM_FASTFLOAT(qst)
#define  FLOAT_FROM_QUANTSTEPTYPE(qst) FLOAT_FROM_FASTFLOAT(qst)
#define FASTFLOAT_FROM_QUANTSTEPTYPE(qst) (qst)

#if defined(COEF64BIT)

#    define CHECK_COEF_MUL_FFLT( f )       \
     assert( 0 <= f.iFracBits );           \
     assert( 64 > f.iFracBits );

#    define COEF_MUL_FFLT(x, f) \
     (CoefType)((((I64)(x))*((I64)(f.iFraction))) >> (f.iFracBits))
#else
#    define CHECK_COEF_MUL_FFLT( f )       \
     assert( 0 <= f.iFracBits );           \
     assert( 64 > f.iFracBits );           \
     if( 32 < f.iFracBits ) {              \
         f.iFraction >>= (f.iFracBits-32); \
         f.iFracBits   = 32; }

#    define COEF_MUL_FFLT(x, f) \
     (CoefType)MULT_HI_DWORDN(x, f.iFraction, (U8)(32-f.iFracBits))
#endif

#else   // must be BUILD_INT_FLOAT

#   define FFLT_ZERO 0.0f
#   define FFLT_ONE  1.0f
#   define FFLT_INV_SQRT2 FLT_INV_SQRT2

#   define FASTFLOAT_FROM_INT(flt)   (Float)(flt)
#   define FASTFLOAT_FROM_FLOAT(flt) (flt)
#   define FLOAT_FROM_FASTFLOAT(fflt) (fflt)
#   define FASTFLOAT_MULT(a,b) ((a)*(b))
#   define FASTFLOAT_DIV(a,b) ((a)/(b))
#   define FASTFLOAT_SQRT(a) (Float)(sqrt(a))
#   define FASTFLOAT_FLOAT_MULT(a,b,bits) ((a)*(b))
#   define FASTFLOAT_FLOAT_DIV(a,b,bits) ((a)/(b))
#   define FASTFLOAT_ADD(a,b) ((a)+(b))
#   define FASTFLOAT_SUB(a,b) ((a)-(b))
#   define DOUBLE_FROM_FASTFLOAT(fflt) ((double)fflt)

#   define FASTFLOAT_FROM_U64(u64,exp) (((Float)(u64))/(((U64)1)<<exp))

typedef Float QuantStepType;
#define DOUBLE_FROM_QUANTSTEPTYPE(qst) ((Double)(qst))
#define  FLOAT_FROM_QUANTSTEPTYPE(qst) (qst)
#define FASTFLOAT_FROM_QUANTSTEPTYPE(qst) ((FastFloat)(qst))

#define CHECK_COEF_MUL_FFLT( f )

#define COEF_MUL_FFLT(x, f) ((x)*(f))

#endif
