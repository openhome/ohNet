//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
//+-------------------------------------------------------------------------
//
//  Microsoft Windows Media
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       fft.c
//
//  The FFT used for the DctIV and DctIV
//
//--------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "msaudio.h"
#include "AutoProfile.h"


#if defined(BUILD_WMASTD) || defined(BUILD_WMAPRO)

#ifdef RECALC
#   define RECALC_FFT
#endif

#   if defined(_SH4_)
#       pragma warning(push)
#       pragma warning(disable:4719)
#   endif

// Define to get Split Radix FFt algorithm - which is expected to be 30% faster than Radix 2
//#define SPLIT_RADIX_FFT

#if ( defined(WMA_TARGET_SH3) || defined(WMA_TARGET_SH4) ) && defined(BUILD_INTEGER)

// Now separately build each processor
//#    include "../sh3/transform_sh3.c"

//#elif defined(WMA_TARGET_SH4) && defined(BUILD_INT_FLOAT)

// Now separately build each processor
//#    include "../sh4/transform_sh4_stub.c"

#else

// Some Algorithm Counters to match to journal article operation counts
#if defined(_DEBUG) && 0

    static int cButterfly0 = 0;         // R2 butterfly with no multiplies
    static int cButterfly1 = 0;         // R4 butterfly with no multiplies
    static int cButterfly2 = 0;         // R2 or R4 butterfly with a complex multiply
    static int cTrig  = 0;              // number of sin/cos recursions
    static int cAdditions = 0;          // number of Data additions (float or I32)
    static int cMultiplications = 0;    // number of Data mutliplications (float or I32)
    static int cIndexing = 0;           // count array indexing/incrementing
    static int cLoops = 0;              // count loops
    static int cLoopIndexing = 0;       // count extra loop indexing operations
    static int cTrigAdditions = 0;      // Additions for trig recursions
    static int cTrigMultiplications = 0; // multiplications for trig recursions

#   define DEBUG_COUNT_BTFLY0(a,m,i) cButterfly0++; cAdditions += a; cMultiplications += m; cIndexing += i;
#   define DEBUG_COUNT_BTFLY1(a,m,i) cButterfly1++; cAdditions += a; cMultiplications += m; cIndexing += i;
#   define DEBUG_COUNT_BTFLY2(a,m,i) cButterfly2++; cAdditions += a; cMultiplications += m; cIndexing += i;
#   define DEBUG_COUNT_TRIG(a,m)     cTrig++;  cTrigAdditions += a;  cTrigMultiplications += m;
#   define DEBUG_COUNT_LOOP(i)       cLoops++; cLoopIndexing += i;

#else // _DEBUG

#   define DEBUG_COUNT_BTFLY0(a,m,i)
#   define DEBUG_COUNT_BTFLY1(a,m,i)
#   define DEBUG_COUNT_BTFLY2(a,m,i)
#   define DEBUG_COUNT_TRIG(a,m)
#   define DEBUG_COUNT_LOOP(i)

#endif // _DEBUG

AVRT_DATA static const double dPI = PI;       // 3.1415926535897932384626433832795;

// the following defines do most of the computational work of the FFT, so they should be done efficently
// note need ur and ui to be defined unless assembly routines which should not need them
// note pointers will be incremented as a side effect of these macros
// define these in assembly for any processor whose compiler needs further optimization

#if !defined(SPLIT_RADIX_FFT)


#define FFTBUTTERFLY0(pxk,pxi) \
/* Butterfly at angle == 0 */ \
    ur = *pxk - *pxi;               /* ur = px[k] - px[i];      */ \
    *pxk++ += *pxi;                 /* px[k]   += px[i];        */ \
    *pxi++ = ur;                    /* px[i]   = ur;            */ \
    ui = *pxk - *pxi;               /* ui = px[k+1] - px[i+1];  */ \
    *pxk++ += *pxi;                 /* px[k+1] += px[i+1];      */ \
    *pxi++ = ui;                    /* px[i+1] = ui;            */
// leave pxi and pxk incremented by 2
// The SH-3 compiler generates very good code for fftbutterfly0

#define FFTBUTTERFLY(pxk,pxi,CR,SI)     \
/* Butterfly at a non-zero angle */     \
    ur = *pxk - *pxi;           /* ur = px[k] - px[i];    */ \
    *pxk++ += *pxi++;           /* px[k]   += px[i];      */ \
    ui = *pxk - *pxi;           /* ui = px[k+1] - px[i+1];*/ \
    *pxk++ += *pxi--;           /* px[k+1] += px[i+1];    */ \
    *pxi++ = MULT_ADD2_CBP2(CR,ur, -SI,ui);  /* px[i]   = cr * ur - (si) * ui; */ \
    *pxi++ = MULT_ADD2_CBP2(CR,ui,  SI,ur);  /* px[i+1] = cr * ui + (si) * ur; */ \
// leave pxi and pxk incremented by 2

// *************************************************************************************
// Spilt radix inverse FFT which scales by 2/N in a step-wise fashion
// *************************************************************************************

#ifdef FFT_DUAL_MPY_ARM
// This macro is defined to make C-code match asm
#define DUAL_MULT_BP2(a,b,c,d) ((((I64)a * (I64)b)+((I64)c * (I64)d)) >> 30) 
#endif 

#if defined(BUILD_INTEGER)

#ifdef FFT_NO_SCALING
    #define SCALING 0
#else
    #define SCALING 1
#endif

#define FFTBUTTERFLY0_N(pxk,pxi) \
/* Butterfly at angle == 0 with inputs divided by 2*/ \
    ur = (tk = *pxk>>SCALING) - (ti = *pxi>>SCALING);   /* ur = px[k] - px[i];      */ \
    *pxk++ = tk + ti;                       /* px[k]   += px[i];        */ \
    *pxi++ = ur;                            /* px[i]   = ur;            */ \
    ui = (tk = *pxk>>SCALING) - (ti = *pxi>>SCALING);   /* ui = px[k+1] - px[i+1];  */ \
    *pxk++ = tk + ti;                       /* px[k+1] += px[i+1];      */ \
    *pxi++ = ui;                    /* px[i+1] = ui;            */
// leave pxi and pxk incremented by 2
// The SH-3 compiler generates very good code for fftbutterfly0

#ifndef FFT_DUAL_MPY_ARM
#define FFTBUTTERFLY_N(pxk,pxi,CR,SI)       \
/* Butterfly at a non-zero angle with inputs divided by 2*/     \
    ur = (tk = *pxk>>SCALING) - (ti = *pxi++>>SCALING); /* ur = px[k] - px[i];    */ \
    *pxk++ = tk + ti;                       /* px[k]   += px[i];      */ \
    ui = (tk = *pxk>>SCALING) - (ti = *pxi-->>SCALING); /* ui = px[k+1] - px[i+1];*/ \
    *pxk++ = tk + ti;                       /* px[k+1] += px[i+1];    */ \
    *pxi++ = MULT_ADD2_CBP2(CR,ur, -SI,ui);  /* px[i]   = cr * ur - (si) * ui; */ \
    *pxi++ = MULT_ADD2_CBP2(CR,ui,  SI,ur);  /* px[i+1] = cr * ui + (si) * ur; */ \
// leave pxi and pxk incremented by 2
#else
#define FFTBUTTERFLY_N(pxk,pxi,CR,SI)       \
/* Butterfly at a non-zero angle with inputs divided by 2*/     \
    ur = (tk = *pxk>>SCALING) - (ti = *pxi++>>SCALING); /* ur = px[k] - px[i];    */ \
    *pxk++ = tk + ti;                       /* px[k]   += px[i];      */ \
    ui = (tk = *pxk>>SCALING) - (ti = *pxi-->>SCALING); /* ui = px[k+1] - px[i+1];*/ \
    *pxk++ = tk + ti;                       /* px[k+1] += px[i+1];    */ \
    *pxi++ = DUAL_MULT_BP2(CR,ur,-SI,ui);  \
    *pxi++ = DUAL_MULT_BP2(CR,ui,SI,ur); 
#endif
    // leave pxi and pxk incremented by 2


#else // must be BUILD_INT_FLOAT

#define FFTBUTTERFLY0_N(pxk,pxi) FFTBUTTERFLY0(pxk,pxi)

#define FFTBUTTERFLY_N(pxk,pxi,CR,SI) FFTBUTTERFLY(pxk,pxi,CR,SI)

#endif

#if 1 //!defined (WMA_TARGET_X86) || defined (DISABLE_OPT)
// the following tables save floating point conversions and trig function calls
// compiler is unwilling to evaluate a constant expression of the form cos(PI/4) as a constant
ROPI_CONST BP1Type icosPIbynp[16] = { 
        BP1_FROM_FLOAT(-0.999999999999996),   // cos(dPI/1)
        BP1_FROM_FLOAT(-0.000000043711390),   // cos(dPI/2)
        BP1_FROM_FLOAT(0.707106765732237),    // cos(dPI/4)
        BP1_FROM_FLOAT(0.923879528329380),    // cos(dPI/8)
        BP1_FROM_FLOAT(0.980785279337272),    // cos(dPI/16)
        BP1_FROM_FLOAT(0.995184726404418),    // cos(dPI/32)
        BP1_FROM_FLOAT(0.998795456138147),    // cos(dPI/64)
        BP1_FROM_FLOAT(0.999698818679443),    // cos(dPI/128)
        BP1_FROM_FLOAT(0.999924701834954),    // cos(dPI/256)
        BP1_FROM_FLOAT(0.999981175281554),    // cos(dPI/512)
        BP1_FROM_FLOAT(0.999995293809314),    // cos(dPI/1024)
        BP1_FROM_FLOAT(0.999998823451636),    // cos(dPI/2048)
        BP1_FROM_FLOAT(0.999999705862866),    // cos(dPI/4096)
        BP1_FROM_FLOAT(0.999999926465714),    // cos(dPI/8192)
        BP1_FROM_FLOAT(0.999999981616428),    // cos(dPI/16384)
        BP1_FROM_FLOAT(0.999999995404107) };  // cos(dPI/32768)
ROPI_CONST BP1Type isinPIbynp[16] = { 
        BP1_FROM_FLOAT(0.000000087422780),    // sin(-dPI/1)
        BP1_FROM_FLOAT(-0.999999999999999),   // sin(-dPI/2)
        BP1_FROM_FLOAT(-0.707106796640858),   // sin(-dPI/4)
        BP1_FROM_FLOAT(-0.382683442461104),   // sin(-dPI/8)
        BP1_FROM_FLOAT(-0.195090327375064),   // sin(-dPI/16)
        BP1_FROM_FLOAT(-0.098017143048367),   // sin(-dPI/32)
        BP1_FROM_FLOAT(-0.049067675691754),   // sin(-dPI/64)
        BP1_FROM_FLOAT(-0.024541229205697),   // sin(-dPI/128)
        BP1_FROM_FLOAT(-0.012271538627189),   // sin(-dPI/256)
        BP1_FROM_FLOAT(-0.006135884819899),   // sin(-dPI/512)
        BP1_FROM_FLOAT(-0.003067956848339),   // sin(-dPI/1024)
        BP1_FROM_FLOAT(-0.001533980228972),   // sin(-dPI/2048)
        BP1_FROM_FLOAT(-0.000766990340086),   // sin(-dPI/4096)
        BP1_FROM_FLOAT(-0.000383495198243),   // sin(-dPI/8192)
        BP1_FROM_FLOAT(-0.000191747602647),   // sin(-dPI/16384)
        BP1_FROM_FLOAT(-0.000095873801764) }; // sin(-dPI/32768)
#endif // !WMA_TARGET_X86 || DISABLE_OPT

#ifdef FFT_STATISTICS
extern Int g_FFTNP[13];
#endif

#if defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL
BP2Type g_W128_i[128] = {0}; // real, imaginary part of Wnp_i, i = 0, 1, 2, ..., np/2 - 1
#endif  // defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL

#if defined(DCT_LOOKUPTBL) && DCT_LOOKUPTBL
extern ROPI_CONST SinCosTable g_sct256;
I32 g_nFacExponent_scale1;
I32 g_nFacExponent_scale2_256;
BP1Type g_pre128FFTTbl_scale1[256] = {0};           // pre 128FFT lookup table for scale factor = 1.0f
BP1Type g_pre128FFTTbl_scale2_256[256] = {0};       // pre 128FFT lookup table for scale factor = 2.0f/256
BP1Type g_post128FFTTbl[256] = {0};             // post 128FFT lookup table (real, imaginary part of e^(-j*n*PI/256), n = 0, 1, 2, 3, ..., 127
#endif  // defined(DCT_LOOKUPTBL) && DCT_LOOKUPTBL

#if BITREVERSAL_FFTDCT_LOOKUPTBL
//I32 g_BR128[64] = {0};        // bit reverse table for 128 point complex FFT (only first 64 mapping needed) 
//void conBitReversal128Tbl();
#define BR128TWIDDLETBL_ENTRY           28      // 28 actual entries
#define BR128TWIDDLETBL_SPECIAL_ENTRY   8       // 8 actual entries

#if !SMALL_BR128TWIDDLE_LOOKUPTBL
// large bit reversal lookup table
#define BR128TWIDDLETbl_INC             4       // g_BR128TwiddleTbl: each entry has 4 elements: top, top_br, bot, bot_br
#define BR128TWIDDLETbl_SPECIAL_INC     2       // g_BR128TwiddleTbl_special: each entry has 2 elements: top, bot

I32 g_BR128TwiddleTbl[(BR128TWIDDLETBL_ENTRY+1)*BR128TWIDDLETbl_INC] = {
    64, 1,  63, 126,    // top, top_br, bot, bot_br
    96, 3,  31, 124,
    80, 5,  47, 122,
    112,7,  15, 120, 
    72, 9,  55, 118,
    104,11, 23, 116,
    88, 13, 39, 114,
    68, 17, 59, 110,
    100,19, 27, 108,
    84, 21, 43, 106,
    76, 25, 51, 102,
    92, 29, 35, 98,
    66, 33, 61, 94,
    82, 37, 45, 90,
    74, 41, 53, 86,
    70, 49, 57, 78,
    32, 2,  95, 125,
    97, 67, 30, 60,
    16, 4,  111,123,
    81, 69, 46, 58,
    48, 6,  79, 121,
    113,71, 14, 56,
    40, 10, 87, 117,
    105,75, 22, 52,
    24, 12, 103,115,
    89, 77, 38, 50,
    36, 18, 91, 109,
    101,83, 26, 44,     // top, top_br, bot, bot_br - end of table
    0,0,0,0             // dummy padding entry for ARM preload w/o buf overrun
};

I32 g_BR128TwiddleTbl_special[BR128TWIDDLETBL_SPECIAL_ENTRY*BR128TWIDDLETbl_SPECIAL_INC] = {
    0,  127,    // top, bot
    8,  119,
    20, 107,
    28, 99,
    34, 93,
    42, 85,
    54, 73,
    62, 65
};
#else   // SMALL_BR128TWIDDLE_LOOKUPTBL
// SMALL_BR128TWIDDLE_LOOKUPTBL
// small bit reversal lookup table
#define BR128TWIDDLETbl_INC             2       // g_BR128TwiddleTbl: each entry has 2 elements: top, top_br
#define BR128TWIDDLETbl_SPECIAL_INC     1       // g_BR128TwiddleTbl_special: each entry has 1 element: top

I32 g_BR128TwiddleTbl[(BR128TWIDDLETBL_ENTRY+1)*BR128TWIDDLETbl_INC] = {
    64, 1,     // top, top_br
    96, 3,  
    80, 5,  
    112,7,  
    72, 9,  
    104,11, 
    88, 13, 
    68, 17, 
    100,19, 
    84, 21, 
    76, 25, 
    92, 29, 
    66, 33, 
    82, 37, 
    74, 41, 
    70, 49, 
    32, 2,  
    97, 67, 
    16, 4,  
    81, 69, 
    48, 6,  
    113,71, 
    40, 10, 
    105,75, 
    24, 12, 
    89, 77, 
    36, 18, 
    101,83,     // top, top_br - end of table
    0,0         // dummy padding entry for ARM preload w/o buf overrun
};

I32 g_BR128TwiddleTbl_special[BR128TWIDDLETBL_SPECIAL_ENTRY*BR128TWIDDLETbl_SPECIAL_INC] = {
    0,      // top
    8,  
    20, 
    28, 
    34, 
    42, 
    54, 
    62
};
#endif  // SMALL_BR128TWIDDLE_LOOKUPTBL
#endif  // BITREVERSAL_FFTDCT_LOOKUPTBL

#if defined(CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL) && CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL
//void conWinRefPre128FFTbl(BP1Type* PreCookedTab);
#if !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)
//void WindowRefPre128FFT(CoefType* rgiCoef);
//void FFTPost128FFTTwiddle(CoefType* rgiCoef,
//                  const Int cSubbandAdjusted,
//                  PFNFFT pfnFFT, Void *pFFTInfo, U32 iMagnitude); 
#endif	// !WMA_OPT_FFT_ARM
#endif  // CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL

// *************************************************************************************
//  Radix 2 FFT
//  when BUILD_INTEGER, does a scale by 2/N FFT
//  when BUILD_INT_FLOAT, does a regular FFT
// *************************************************************************************

#if !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)    
#if !((defined(WMA_TARGET_MIPS) || defined(WMA_TARGET_SH4)) && defined(PLATFORM_SPECIFIC_FFT))

void prvFFT4DCT(Void *ptrNotUsed, CoefType data[], Int nLog2np, FftDirection fftDirection)
{
    I32 np = (1<<nLog2np);
    CoefType *px = data;
    I32 i, j, k, l, m, n;
    CoefType *pxk, *pxi;
    CoefType ur, ui;
#if defined(BUILD_INTEGER)
    CoefType tk, ti;
#endif

    // defining the following COSSIN structure allows us to pass a pointer to a set of values in asm code
    // but WinCE/SH-3 compiler seems to do a particularly bad job of optimizing access to structure members!
    // struct COSSIN { I32 CR2,SI2,CR1,SI1,STEP,CR,SI;  } cs;
    TR2_TYPE CR2,SI2,CR1,SI1,STEP,CR,SI;
    FUNCTION_PROFILE(fp);
    FUNCTION_PROFILE_START(&fp,FFT_PROFILE);

#if defined (WMA_TARGET_X86) && !defined (DISABLE_OPT) && !defined(BUILD_INTEGER)
    // Pentium sin/cos are fast
    CR = TR2_FROM_FLOAT(cos(dPI/np));
    STEP = TR2_FROM_FLOAT(2*sin(-dPI/np));
#else // WMA_TARGET_X86
    // other platforms' sin/cos unlikely to be that optimized, so do lookup
    {
        if ( nLog2np < 16 )
        {
            CR = TR2_FROM_BP1(icosPIbynp[nLog2np]);         // CR = (I32)(cos(PI/np) * NF2BP2)
#ifdef BUILD_INTEGER 
            STEP = TR2_FROM_BP2((isinPIbynp[nLog2np]));                     // STEP = (I32)(2*sin(-PI/np) * NF2BP2)
#else // BUILD_INT_FLOAT
            STEP = TR2_FROM_FLOAT(2*isinPIbynp[nLog2np]);   // STEP = (I32)(2*sin(-PI/np) * NF2BP2)
#endif
        }
        else
        {
            CR = TR2_FROM_FLOAT(cos(dPI/np));
            STEP = TR2_FROM_FLOAT(2*sin(-dPI/np));
        }
    }
#endif // WMA_TARGET_X86 && !DISABLE_OPT
    
    if (fftDirection == FFT_INVERSE) STEP *= -1;
    
    SI = DIV2(STEP);                                    // SI = (I32)(sin(-PI/np) * NF2BP2)

    ///  comments with three /// show example indexing sequences for np=1024 and times the loop is executed [1x]

    n = 2 * np;                             /// n: 2048
    m = n;

    while (m > 4) {                         /// m: {2048, ... 16, 8} [9x]
        l = m >> 1;
        CR2 = TR2_FROM_FLOAT(1);                                // cos(0)
        SI2 = 0;                                                // sin(0)
        CR1 = TR2_FROM_FLOAT(1) - MULT_TR2(STEP,SI);    // cos(2*2*PI/m)
        SI = SI1 = MULT_TR2(STEP,CR);                   // sin(2*2*PI/m)
        CR = CR1;
        STEP = MUL2(SI1);

#ifdef RECALC_FFT
        if (DORECALC_FFT(m, n)) {
          //BP2Type CR1Save = CR1;
          //BP2Type SI1Save = SI1;
          //BP2Type d1, d2;
          CR1 = TR2_FROM_FLOAT(cos(-4*PI/m));
          SI1 = TR2_FROM_FLOAT(sin(-4*PI/m));
          //d1 = BPX_ABS(CR1-CR1Save);
          //d2 = BPX_ABS(SI1-SI1Save);
          //assert(d1 <= 32000);
          //assert(d2 <= 32000);
        }
#endif

        // Trivial butterflies (angle = 0) 
        for (k = 0; k < n; k += m) {        /// k: {0} {0,1024} ... {0,8,16...2044} [512x]
            i = k + l;                      /// i: {1024} {1024,2048} ... {4,12,20...2040}
            pxk = &px[k];
            pxi = &px[i];
            // +1/-1 butterfly 
            FFTBUTTERFLY0_N(pxk,pxi);                   // update px[i], px[i+1] and px[k], px[k+1], leave pointers +2
             // +1/-1/W_k butterfly 
            FFTBUTTERFLY_N(pxk,pxi,BP2_FROM_TR2(CR1),BP2_FROM_TR2(SI1));    // update px[i+2], px[i+2+1] and px[k+2], px[k+2+1], leave pointers +2
            /* Butterfly at a non-zero angle */ 
#if 0
              ur = *pxk - *pxi;           /* ur = px[k] - px[i];    */ \
              *pxk++ += *pxi++;           /* px[k]   += px[i];      */ \
              ui = *pxk - *pxi;           /* ui = px[k+1] - px[i+1];*/ \
              *pxk++ += *pxi--;           /* px[k+1] += px[i+1];    */ \
              *pxi++ = MULT_BP2(CR,ur) - MULT_BP2(SI,ui);  /* px[i]   = cr * ur - (si) * ui; */ \
              *pxi++ = MULT_BP2(CR,ui) + MULT_BP2(SI,ur);  /* px[i+1] = cr * ui + (si) * ur; */
#endif
              // leave pxi and pxk incremented by 2
            DEBUG_COUNT_BTFLY0(4,0,4);
            DEBUG_COUNT_BTFLY1(6,4,6);
        }
        // Nontrivial butterflies 
        for (j = 4; j < l; j += 4) {        /// j: {4,8...1020} {4,8,...510} ... {4} {} [~510x]

            // recursion to next sin and cosine values where Theta = 2*PI/m;
            // CR2 = cos(-j*Theta);  SI2 = sin(-j*Theta); CR1 = cos((-j-2)*Theta); SI1 = sin((-j-2)*Theta);
            // recursion: cos(a-2b) = cos(a) - 2*sin(b)*cos(a-b)
            // and:       sin(a-2b) = sin(a) + 2*sin(b)*sin(a-b)
            TR2_RECURR_DEC2X(CR1,SI1,CR2,SI2,STEP);
            /*
            CR2 -= MULT_BP2(STEP,SI1);
            SI2 += MULT_BP2(STEP,CR1);
            CR1 -= MULT_BP2(STEP,SI2);
            SI1 += MULT_BP2(STEP,CR2);
            */

#ifdef RECALC_FFT
            if (DORECALC_FFT(j, n)) {
              //BP2Type CR1Save = CR1;
              //BP2Type SI1Save = SI1;
              //BP2Type CR2Save = CR2;
              //BP2Type SI2Save = SI2;
              //BP2Type d1, d2, d3, d4;
              CR2 = TR2_FROM_FLOAT(cos(-j*2*PI/m));
              SI2 = TR2_FROM_FLOAT(sin(-j*2*PI/m));
              CR1 = TR2_FROM_FLOAT(cos((-j-2)*2*PI/m));
              SI1 = TR2_FROM_FLOAT(sin((-j-2)*2*PI/m));
              //d1 = BPX_ABS(CR1-CR1Save);
              //d2 = BPX_ABS(SI1-SI1Save);
              //d3 = BPX_ABS(CR2-CR2Save);
              //d4 = BPX_ABS(SI2-SI2Save);
              //assert(d1 <= 32000);
              //assert(d2 <= 32000);
              //assert(d3 <= 32000);
              //assert(d4 <= 32000);
            }
#endif

            // do main butterflies
            for (k = j; k <= n; k += m) {   /// k: {{4}{8}...{1020}} {{4,1028}{8,1032}...{508,1020}} ... {{4,20...2044}} [2048x]
                pxk = &px[k];
                pxi = &px[k + l];
                // +1/-1/W_k butterfly 
                FFTBUTTERFLY_N(pxk,pxi,BP2_FROM_TR2(CR2),BP2_FROM_TR2(SI2));        // update px[i], px[i+1] and px[k], px[k+1], leave pointers at +2
                // +1/-1/W_k butterfly 
                FFTBUTTERFLY_N(pxk,pxi,BP2_FROM_TR2(CR1),BP2_FROM_TR2(SI1));        // update px[i+2], px[i+2+1] and px[k+2], px[k+2+1], leave pointers at +2
                /* Butterfly at a non-zero angle */
#if 0
                  ur = *pxk - *pxi;           /* ur = px[k] - px[i];    */ \
                  *pxk++ += *pxi++;           /* px[k]   += px[i];      */ \
                  ui = *pxk - *pxi;           /* ui = px[k+1] - px[i+1];*/ \
                  *pxk++ += *pxi--;           /* px[k+1] += px[i+1];    */ \
                  *pxi++ = MULT_BP2(CR,ur) - MULT_BP2(SI,ui);  /* px[i]   = cr * ur - (si) * ui; */ \
                  *pxi++ = MULT_BP2(CR,ui) + MULT_BP2(SI,ur);  /* px[i+1] = cr * ui + (si) * ur; */
#endif
                  // leave pxi and pxk incremented by 2
                DEBUG_COUNT_BTFLY1(6,4,6);
                DEBUG_COUNT_BTFLY1(6,4,6);
                DEBUG_COUNT_LOOP(2);
            }
            DEBUG_COUNT_TRIG(2,2);
            DEBUG_COUNT_TRIG(2,2);
            DEBUG_COUNT_LOOP(2);
        }
        m  = l;
        DEBUG_COUNT_TRIG(2,2);
        DEBUG_COUNT_LOOP(2);
    }
    if (m > 2) {
        // m normally exits the loop above == 4, so normally do this except when called with np = 1 or 2
        for (j = 0; j < n; j += 4) {        /// j: {0,4...2044}  [512x]
            pxi = (pxk = px+j) + 2;
            
            // +1/-1 butterfly 
            FFTBUTTERFLY0(pxk,pxi);
            DEBUG_COUNT_BTFLY0(4,0,4);
            DEBUG_COUNT_LOOP(2);
        }
    }
    if (n > 4) {
        I32 n2, n21;
        CoefType tmp;

        n2 = np / 2;                        /// n2: 512
        n21 = np + 1;                       /// n21: 1025
        j = 0;                              
        for (i = 0; i < np; i += 4) {       /// i,j: 0,0; 4,1024; 8,512; 12,1536; ... 2044,??? [255x]

            if (i < j) {
                // swap 4 pairs of values (2 complex pairs with 2 others)
                // px[i] <-> px[j]; px[i+1] <-> px[j+1]
                // px[i+1+n21] <-> px[j+1+n21];  px[i+1+n21+1] <-> px[j+1+n21+1]
                pxi = &px[i];
                pxk = &px[j];
                tmp = *pxi; 
                *pxi++ = *pxk;
                *pxk++ = tmp;
                tmp = *pxi;
                *pxi = *pxk;
                *pxk = tmp;
                pxi  += n21;
                pxk  += n21;
                tmp = *pxi;
                *pxi++ = *pxk;
                *pxk++ = tmp;
                tmp = *pxi;
                *pxi = *pxk;
                *pxk = tmp;
            }

            // swap 2 pairs of values (1 complex pair with another)
            // px[i+2] <-> px[j+np];  px[i+3] <-> px[j+np+1]
            pxi = &px[i+2];
            pxk = &px[j+np];
            tmp = *pxi; 
            *pxi++ = *pxk;
            *pxk++ = tmp;
            tmp = *pxi;
            *pxi = *pxk;
            *pxk = tmp;

            k = n2;                         
            while (k <= j) {                /// k: {1024} {1024,512} {1024} {1024,512,256} ...
                j -= k;
                k = k / 2;
            }
            j += k;                         /// j: {1024} {512} {1536} {256} ...
        }
    }
#ifndef FFT_NO_SCALING
    if (fftDirection == FFT_INVERSE) // Normalization to match Intel library
        for (i = 0; i < 2 * np; i++) data[i] /= np;
#endif

    FUNCTION_PROFILE_STOP(&fp);
}
#endif //WMA_OPT_FFT_ARM
#endif //!(((WMA_TARGET_MIPS) || (WMA_TARGET_SH4)) && PLATFORM_SPECIFIC_FFT)

#else // so must be SPLIT_RADIX_FFT

//****************************************************************************************************************
//
// A Split Radix FFT for the DCT -
// See WMAConcepts.xls - Sheet SRFFT32 for how this works.
// See also Sorensen & Heldeman, IEEE Trans ASSP, Vol ASSP-34, #1, 2/86, pp152-156.
// And also G. M. Blair, Electronics & Comm Engr Journal, August 1995, pp169-177.
//
//****************************************************************************************************************

#define BP2Const6(a,b,c,d,e,f) BP2_FROM_FLOAT(a),BP2_FROM_FLOAT(b),BP2_FROM_FLOAT(c), \
                               BP2_FROM_FLOAT(d),BP2_FROM_FLOAT(e),BP2_FROM_FLOAT(f)

AVRT_DATA static const BP2Type rgcbp2SrFFTTrig[] = {
//        STEP1             STEP3       
//        2sin(2pi/2^k) Cos(2pi/2^k)  Sin(2pi/2^k)  2sin(6pi/2^k)  Cos(6pi/2^k)  Sin(6pi/2^k)
BP2Const6(1.41421356237,0.70710678119,0.70710678119,1.41421356237,-0.70710678119,0.70710678119),    // K=3
BP2Const6(0.76536686473,0.92387953251,0.38268343237,1.84775906502, 0.38268343237,0.92387953251),    // K=4
BP2Const6(0.39018064403,0.98078528040,0.19509032202,1.11114046604, 0.83146961230,0.55557023302),    // K=5
BP2Const6(0.19603428066,0.99518472667,0.09801714033,0.58056935451, 0.95694033573,0.29028467725),    // K=6
BP2Const6(0.09813534865,0.99879545621,0.04906767433,0.29346094891, 0.98917650996,0.14673047446),    // k=7
BP2Const6(0.04908245705,0.99969881870,0.02454122852,0.14712912720, 0.99729045668,0.07356456360),    // k=8
BP2Const6(0.02454307657,0.99992470184,0.01227153829,0.07361444588, 0.99932238459,0.03680722294),    // k=9
BP2Const6(0.01227176930,0.99998117528,0.00613588465,0.03681345981, 0.99983058180,0.01840672991),    // k=10
BP2Const6(0.00613591353,0.99999529381,0.00306795676,0.01840750956, 0.99995764455,0.00920375478),    // k=11
BP2Const6(0.00306796037,0.99999882345,0.00153398019,0.00920385224, 0.99998941108,0.00460192612),    // k=12
BP2Const6(0.00153398064,0.99999970586,0.00076699032,0.00460193830, 0.99999735277,0.00230096915),    // k=13
BP2Const6(0.00076699038,0.99999992647,0.00038349519,0.00230097067, 0.99999933819,0.00115048534),    // k=14
BP2Const6(0.00038349519,0.99999998162,0.00019174760,0.00115048553, 0.99999983455,0.00057524276),    // k=15
BP2Const6(0.00019174760,0.99999999540,0.00009587380,0.00057524279, 0.99999995864,0.00028762139),    // k=16
0,0,0,0,0,0 };


#if defined(_DEBUG) && 0
// some code to show looping 
FILE* fileFFTDump = NULL;
Int* pFFTIndex = NULL;
#define DUMP_FFT_OPEN(msg,np)                          \
    if (fileFFTDump == NULL )                          \
        fileFFTDump = FOPEN("DUMP_FFT.TXT","wt");      \
    if (fileFFTDump != NULL )                          \
        WMAFprintf( fileFFTDump, msg, np );               \
    pFFTIndex = realloc(pFFTIndex,2*np*sizeof(Int));   \
    memset( pFFTIndex,0,2*np*sizeof(Int));
#define DUMP_FFT_SET(i,v) pFFTIndex[i] = v;
#define DUMP_FFT_SHOW(msg,k,np)                         \
    {   int i;                                          \
        if (fileFFTDump != NULL ) {                     \
            WMAFprintf( fileFFTDump, msg, k, np );         \
            for( i=0; i<2*np; i += 2 ) {                \
                WMAFprintf( fileFFTDump, "%d,  %d,\n",     \
                    i, pFFTIndex[i] );                  \
            }                                           \
        }                                               \
        memset( pFFTIndex, 0, 2*np*sizeof(Int) );       \
    }
#else
#define DUMP_FFT_OPEN(msg,np)
#define DUMP_FFT_SET(i,v)
#define DUMP_FFT_SHOW(msg,k,np)
#endif

#ifdef BUILD_INTEGER
#   define INTDIV2(a) ((a)>>1)
#else
#   define INTDIV2(a) (a)
#endif

#if !((defined(WMA_TARGET_MIPS) || defined(WMA_TARGET_SH4)) && defined(PLATFORM_SPECIFIC_FFT))
void prvFFT4DCT(Void *ptrNotUsed, CoefType data[], Int nLog2np, FftDirection fftDirection)
{
    Int np = (1<<nLog2np);
    Int np2 = np<<1;
    Int np2m7 = np2-7;
    CoefType *pxk, *pxi, *px0, *px1, *px2, *px3;
    CoefType *px = data;
    I32 i, j, k, iOffset, iStride, iStridem1;
    Int n2k, n2km1, n2km2, n2kp2, idx;
    CoefType tmp, ur0, ui0, ur1, ui1;
    TR2_TYPE bp2Step1, bp2Cos1, bp2Sin1, bp2Step3, bp2Cos3, bp2Sin3;
    TR2_TYPE bp2Cos1p, bp2Sin1p, bp2Cos3p, bp2Sin3p;
    TR2_TYPE bp2Cos1T, bp2Sin1T, bp2Cos3T, bp2Sin3T;
    CoefType ur2, ui2, ur3, ui3, urp, uip, urm, uim;
    const BP2Type* pbp2Trig = rgcbp2SrFFTTrig;
    INTEGER_ONLY( Int n2kp1; )

    FUNCTION_PROFILE(fp);
    FUNCTION_PROFILE_START(&fp,FFT_PROFILE);
    DUMP_FFT_OPEN("//FFT np = %d\n", np );

    
    assert(fftDirection == FFT_FORWARD); // not implemented inverse yet.
    
    // bit reverse (same code as Radix 2)
    if (np > 2) {
        I32 n2, n21;

        n2 = np / 2;                        /// n2: 512
        n21 = np + 1;                       /// n21: 1025
        j = 0;                              
        for (i = 0; i < np; i += 4) {       /// i,j: 0,0; 4,1024; 8,512; 12,1536; ... 2044,??? [255x]

            if (i < j) {
                // swap 4 pairs of values (2 complex pairs with 2 others)
                // px[i] <-> px[j]; px[i+1] <-> px[j+1]
                // px[i+1+n21] <-> px[j+1+n21];  px[i+1+n21+1] <-> px[j+1+n21+1]
                pxi = &px[i];
                pxk = &px[j];
                tmp = *pxi; 
                *pxi++ = *pxk;
                *pxk++ = tmp;
                tmp = *pxi;
                *pxi = *pxk;
                *pxk = tmp;
                pxi  += n21;
                pxk  += n21;
                tmp = *pxi;
                *pxi++ = *pxk;
                *pxk++ = tmp;
                tmp = *pxi;
                *pxi = *pxk;
                *pxk = tmp;
            }

            // swap 2 pairs of values (1 complex pair with another)
            // px[i+2] <-> px[j+np];  px[i+3] <-> px[j+np+1]
            pxi = &px[i+2];
            pxk = &px[j+np];
            tmp = *pxi; 
            *pxi++ = *pxk;
            *pxk++ = tmp;
            tmp = *pxi;
            *pxi = *pxk;
            *pxk = tmp;

            k = n2;                         
            while (k <= j) {                /// k: {1024} {1024,512} {1024} {1024,512,256} ...
                j -= k;
                k = k / 2;
            }
            j += k;                         /// j: {1024} {512} {1536} {256} ...
        }
    }
 
    // Length 2 butterflies
    for( iOffset = 0, iStride = 8; 
            iOffset < np2; 
                iOffset = (iStride<<1) - 4, iStride <<= 2 )
    {
        iStridem1 = iStride-1;
        for( idx = iOffset, px1 = (px0 = px+iOffset) + 2;
                idx < np2; 
                    idx += iStride, px0 += iStridem1, px1 += iStridem1 )
        {
            ur0 = *px0;
            ur1 = *px1; 
            *px0++ = ur0 + ur1;
            *px1++ = ur0 - ur1;
            ui0 = *px0;
            ui1 = *px1; 
            *px0 = ui0 + ui1;
            *px1 = ui0 - ui1;
            DUMP_FFT_SET(idx,2);
            DUMP_FFT_SET(idx+2,1);
            DEBUG_COUNT_BTFLY0(4,0,4);
            DEBUG_COUNT_LOOP(2);
        }
        DEBUG_COUNT_LOOP(6);
    }
    DUMP_FFT_SHOW("k = %d.\n", 1, np );

    // Radix 4 like Butterflies - either with ot without multiplies
    n2k = 2;
    for( k=2; k<=nLog2np; k++ )
    {
        n2k <<= 1;
        n2km1 = n2k>>1;
        n2km2 = n2k>>2;
        n2kp2 = n2k<<2;
#ifdef BUILD_INTEGER
        n2kp1 = n2k<<1;
        // we must scale all the px's by 2 that will not be accessed in the remainder of this main loop
        for( iOffset = n2kp1, iStride = n2k<<3; 
                iOffset < np2; 
                    iOffset = (iStride<<1) - n2kp1, iStride <<= 2 )
        {
            for( idx = iOffset; idx < np2; idx += iStride )
            {
                for( i = 0, px0 = px+idx; i < n2kp1; i++ )
                    *px0++ >>= 1;
            }
        }
#endif 
        // Trivial Butterflies - j==0 - no multiplies since Cos==1 and Sin==0
        for( iOffset = 0, iStride = n2kp2; 
                iOffset < np2; 
                    iOffset = (iStride - n2k)<<1, iStride <<= 2 )
        {
            px3 = (px2 = (px1 = (px0 = px+iOffset) + n2km1) + n2km1) + n2km1;
            iStridem1 = iStride-1;
            for( idx = iOffset; 
                    idx < np2m7; 
                        idx += iStride, px0 += iStridem1, px1 += iStridem1, px2 += iStridem1, px3 += iStridem1 )
            {
                urp = (ur0=INTDIV2(*px2++)) + (ur1=INTDIV2(*px3++));
                urm = ur0 - ur1;
                uip = (ui0=INTDIV2(*px2--)) + (ui1=INTDIV2(*px3--));
                uim = ui0 - ui1;
                *px2++  = (ur0 = INTDIV2(*px0)) - urp;
                *px0++  = ur0 + urp;
                *px3++  = (ur1 = INTDIV2(*px1)) - uim;
                *px1++  = ur1 + uim;
                *px2    = (ui0 = INTDIV2(*px0)) - uip;
                *px0    = ui0 + uip;
                *px3    = (ui1 = INTDIV2(*px1)) + urm;
                *px1    = ui1 - urm;
                DUMP_FFT_SET(idx,3);
                DUMP_FFT_SET(idx+n2km1,1);
                DUMP_FFT_SET(idx+2*n2km1,1);
                DUMP_FFT_SET(idx+3*n2km1,1);
                DEBUG_COUNT_BTFLY1(12,0,12);
                DEBUG_COUNT_LOOP(2);
            }
            DEBUG_COUNT_LOOP(9);
        }
        // Now the non-trivial butterflies
        if ( n2km2 > 1 )
        {
            if ( *pbp2Trig != 0 )
            {   // normal case with k <= 16
                bp2Step1 = TR2_FROM_BP2(*pbp2Trig++);     // 2*sin(2*pi/2^k)
                bp2Cos1  = TR2_FROM_BP2(*pbp2Trig++);     // cos(2*pi/2^k) 
                bp2Sin1  = TR2_FROM_BP2(*pbp2Trig++);     // sin(2*pi/2^k)
                bp2Step3 = TR2_FROM_BP2(*pbp2Trig++);     // 2*sin(6*pi/2^k)
                bp2Cos3  = TR2_FROM_BP2(*pbp2Trig++);     // cos(6*pi/2^k) 
                bp2Sin3  = TR2_FROM_BP2(*pbp2Trig++);     // sin(6*pi/2^k)
            }
            else
            {   // k > 16 is not normal - but cleaniness before smallness
                bp2Step1 = TR2_FROM_FLOAT( 2*sin(2*PI/n2k) );
                bp2Cos1  = TR2_FROM_FLOAT( cos(2*PI/n2k) );
                bp2Sin1  = TR2_FROM_FLOAT( sin(2*PI/n2k) );
                bp2Step3 = TR2_FROM_FLOAT( 2*sin(6*PI/n2k) );
                bp2Cos3  = TR2_FROM_FLOAT( cos(6*PI/n2k)  );
                bp2Sin3  = TR2_FROM_FLOAT( sin(6*PI/n2k) );
            }
            bp2Cos1p = bp2Cos3p = TR2_FROM_FLOAT(1.0);
            bp2Sin1p = bp2Sin3p = TR2_FROM_FLOAT(0.0);
            for( j = 1; j<n2km2;  j++ )
            {
                //assert( fabs(FLOAT_FROM_BP2(bp2Sin1) - sin((2*PI*j)/n2k)) < 0.0001 );
                //assert( fabs(FLOAT_FROM_BP2(bp2Sin3) - sin((6*PI*j)/n2k)) < 0.0001 );
                for( iOffset = j<<1, iStride = n2kp2; 
                        iOffset < np2; 
                            iOffset = (iStride - n2k + j)<<1, iStride <<= 2 )
                {
                    px3 = (px2 = (px1 = (px0 = px+iOffset) + n2km1) + n2km1) + n2km1;
                    iStridem1 = iStride-1;
                    for( idx = iOffset; 
                            idx < np2m7; 
                        idx += iStride, px0 += iStridem1, px1 += iStridem1, px2 += iStridem1, px3 += iStridem1 )
                    {
#if !defined(WMA_TARGET_SH4)
                        // The pentium prefers this way, but still does not generate wonderful code
                        ur0 = INTDIV2(*px2++);  ui0 = INTDIV2(*px2--);
                        ur2 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos1),ur0,  BP2_FROM_TR2(bp2Sin1),ui0);
                        ui2 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos1),ui0, BP2_FROM_TR2(-bp2Sin1),ur0);
                        ur1 = INTDIV2(*px3++);  ui1 = INTDIV2(*px3--);
                        ur3 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos3),ur1,  BP2_FROM_TR2(bp2Sin3),ui1);
                        ui3 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos3),ui1, BP2_FROM_TR2(-bp2Sin3),ur1);
                        urp     = ur2 + ur3;
                        *px2++  = (ur0 = INTDIV2(*px0)) - urp;
                        *px0++  = ur0 + urp;
                        uim     = ui2 - ui3;
                        *px3++  = (ur1 = INTDIV2(*px1)) - uim;
                        *px1++  = ur1 + uim;
                        uip     = ui2 + ui3;
                        *px2    = (ui0 = INTDIV2(*px0)) - uip;
                        *px0    = ui0 + uip;
                        urm     = ur2 - ur3;
                        *px3    = (ui1 = INTDIV2(*px1)) + urm;
                        *px1    = ui1 - urm;
#else
                        // some platforms might prefer this expression
                        ur0 = INTDIV2(*px2++);  ui0 = INTDIV2(*px2--);
                        ur2 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos1),ur0,  BP2_FROM_TR2(bp2Sin1),ui0);
                        ui2 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos1),ui0, BP2_FROM_TR2(-bp2Sin1),ur0);
                        ur1 = INTDIV2(*px3++); ui1 = INTDIV2(*px3--);
                        ur3 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos3),ur1,  BP2_FROM_TR2(bp2Sin3),ui1);
                        ui3 = MULT_ADD2_CBP2(BP2_FROM_TR2(bp2Cos3),ui1, BP2_FROM_TR2(-bp2Sin3),ur1);
                        urp = ur2 + ur3;
                        urm = ur2 - ur3;
                        uip = ui2 + ui3;
                        uim = ui2 - ui3;
                        *px2++  = (ur0 = INTDIV2(*px0)) - urp;
                        *px0++  = ur0 + urp;
                        *px3++  = (ur1 = INTDIV2(*px1)) - uim;
                        *px1++  = ur1 + uim;
                        *px2    = (ui0 = INTDIV2(*px0)) - uip;
                        *px0    = ui0 + uip;
                        *px3    = (ui1 = INTDIV2(*px1)) + urm;
                        *px1    = ui1 - urm;
#endif
                        DUMP_FFT_SET(idx,4);
                        DUMP_FFT_SET(idx+n2km1,1);
                        DUMP_FFT_SET(idx+2*n2km1,1);
                        DUMP_FFT_SET(idx+3*n2km1,1);
                        DEBUG_COUNT_BTFLY2(16,8,12);
                        DEBUG_COUNT_LOOP(2);
                    }
                    DEBUG_COUNT_LOOP(10);
                }
                if ( (j+1) < n2km2 )
                {   // Trig Recurrsion for both 2*pi/2^k and 6*pi/2^k
                    // sin(a+b) = sin(a-b) + 2*sin(b)*cos(a)
                    // cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
                    // Lay these out like this as ahint to optimizer to overlap operations
                    bp2Sin1T = bp2Sin1p + MULT_TR2(bp2Step1,bp2Cos1);
                    bp2Cos1T = bp2Cos1p - MULT_TR2(bp2Step1,bp2Sin1);
                    bp2Sin3T = bp2Sin3p + MULT_TR2(bp2Step3,bp2Cos3);
                    bp2Cos3T = bp2Cos3p - MULT_TR2(bp2Step3,bp2Sin3);
                    bp2Sin1p = bp2Sin1;  bp2Sin1 = bp2Sin1T;
                    bp2Cos1p = bp2Cos1;  bp2Cos1 = bp2Cos1T;
                    bp2Sin3p = bp2Sin3;  bp2Sin3 = bp2Sin3T;
                    bp2Cos3p = bp2Cos3;  bp2Cos3 = bp2Cos3T;
                    DEBUG_COUNT_TRIG(2,2);
                    DEBUG_COUNT_TRIG(2,2);
                }
                DEBUG_COUNT_LOOP(2);
            }
        }
        DEBUG_COUNT_LOOP(7);
        DUMP_FFT_SHOW("k = %d.\n", k, np );
    }
    FUNCTION_PROFILE_STOP(&fp);
}
#endif //((WMA_TARGET_MIPS) || (WMA_TARGET_SH4)) && PLATFORM_SPECIFIC_FFT

#endif  // both !SPLIT_RADIX_FFT and SPLIT_RADIX_FFT


///----------------- 128 point FFT (lookup table based) -----------------------
#if defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL   
#if !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)

void prvFFT4DCT_128Tbl(Void *ptrNotUsed, CoefType data[], Int nLog2np, FftDirection fftDirection)
{
    I32 np = (1<<nLog2np);
    CoefType *px = data;
    I32 i, j, k, l, m, n;
    CoefType *pxk, *pxi;
    CoefType ur, ui;
#if defined(BUILD_INTEGER)
    CoefType tk, ti;
#endif
    I32 stage = 0;              // stage of butterflies
    I32 tblIndex = 0;

    // defining the following COSSIN structure allows us to pass a pointer to a set of values in asm code
    // but WinCE/SH-3 compiler seems to do a particularly bad job of optimizing access to structure members!
    // struct COSSIN { I32 CR2,SI2,CR1,SI1,STEP,CR,SI;  } cs;
    BP2Type CR2,SI2,CR1,SI1;
    FUNCTION_PROFILE(fp);
    FUNCTION_PROFILE_START(&fp,FFT_PROFILE);

    ///  comments with three /// show example indexing sequences for np=1024 and times the loop is executed [1x]

    n = 2 * np;                             /// n: 2048
    m = n;

    while (m > 4) {                         /// m: {2048, ... 16, 8} [9x]
        l = m >> 1;

#ifdef RECALC_FFT
        if (DORECALC_FFT(m, n)) {
          //BP2Type CR1Save = CR1;
          //BP2Type SI1Save = SI1;
          //BP2Type d1, d2;
          CR1 = BP2_FROM_FLOAT(cos(-4*PI/m));
          SI1 = BP2_FROM_FLOAT(sin(-4*PI/m));
          //d1 = BPX_ABS(CR1-CR1Save);
          //d2 = BPX_ABS(SI1-SI1Save);
          //assert(d1 <= 32000);
          //assert(d2 <= 32000);
        }
#endif

        // Trivial butterflies (angle = 0) 
        //CR1 = g_W128_i[(1<<stage)<<1];            // real(Wnp/k_1), k = 1, 2, 4, 8, ...
        //SI1 = g_W128_i[((1<<stage)<<1) + 1];      // imag(Wnp/k_1)    
        ///CR1 = g_W128_i[(2<<stage)];            // real(Wnp/k_1), k = 1, 2, 4, 8, ...
        ///SI1 = g_W128_i[(2<<stage) + 1];      // imag(Wnp/k_1)  
        tblIndex = 2<<stage;
        CR1 = g_W128_i[tblIndex];            // real(Wnp/k_1), k = 1, 2, 4, 8, ...
        SI1 = g_W128_i[tblIndex + 1];      // imag(Wnp/k_1)    
        for (k = 0; k < n; k += m) {        /// k: {0} {0,1024} ... {0,8,16...2044} [512x]
            i = k + l;                      /// i: {1024} {1024,2048} ... {4,12,20...2040}
            pxk = &px[k];
            pxi = &px[i];
            // +1/-1 butterfly 
            FFTBUTTERFLY0_N(pxk,pxi);                   // update px[i], px[i+1] and px[k], px[k+1], leave pointers +2
             // +1/-1/W_k butterfly 
            FFTBUTTERFLY_N(pxk,pxi,CR1,SI1);    // update px[i+2], px[i+2+1] and px[k+2], px[k+2+1], leave pointers +2
            /* Butterfly at a non-zero angle */ 
#if 0
              ur = *pxk - *pxi;           /* ur = px[k] - px[i];    */ \
              *pxk++ += *pxi++;           /* px[k]   += px[i];      */ \
              ui = *pxk - *pxi;           /* ui = px[k+1] - px[i+1];*/ \
              *pxk++ += *pxi--;           /* px[k+1] += px[i+1];    */ \
              *pxi++ = MULT_BP2(CR,ur) - MULT_BP2(SI,ui);  /* px[i]   = cr * ur - (si) * ui; */ \
              *pxi++ = MULT_BP2(CR,ui) + MULT_BP2(SI,ur);  /* px[i+1] = cr * ui + (si) * ur; */
#endif
              // leave pxi and pxk incremented by 2
            DEBUG_COUNT_BTFLY0(4,0,4);
            DEBUG_COUNT_BTFLY1(6,4,6);
        }
        // Nontrivial butterflies 
        for (j = 4; j < l; j += 4) {        /// j: {4,8...1020} {4,8,...510} ... {4} {} [~510x]

            //CR2 = g_W128_i[(1<<stage)*j];             // real(Wnp/k_i) = real(Wnp_k*i), k = 1, 2, 4, 8, ... (k = 2^stage)
            //SI2 = g_W128_i[(1<<stage)*j + 1];         // imag(Wnp/k_i) = imag(Wnp_k*i), i = j/2, (i = 2, 4, 6, ...)
            //CR1 = g_W128_i[(1<<stage)*(j + 2)];       // real(Wnp/k_i+1) = real(Wnp_k*(i+1))
            //SI1 = g_W128_i[(1<<stage)*(j + 2) + 1];   // imag(Wnp/k_i+1) = imag(Wnp_k*(i+1))
            ///CR2 = g_W128_i[(j<<stage)];             // real(Wnp/k_i) = real(Wnp_k*i), k = 1, 2, 4, 8, ... (k = 2^stage)
            ///SI2 = g_W128_i[(j<<stage) + 1];         // imag(Wnp/k_i) = imag(Wnp_k*i), i = j/2, (i = 2, 4, 6, ...)
            ///CR1 = g_W128_i[(j<<stage) + (2<<stage)];       // real(Wnp/k_i+1) = real(Wnp_k*(i+1))
            ///SI1 = g_W128_i[(j<<stage) + (2<<stage) + 1];   // imag(Wnp/k_i+1) = imag(Wnp_k*(i+1))
            tblIndex += (2<<stage);
            CR2 = g_W128_i[tblIndex];             // real(Wnp/k_i) = real(Wnp_k*i), k = 1, 2, 4, 8, ... (k = 2^stage)
            SI2 = g_W128_i[tblIndex + 1];         // imag(Wnp/k_i) = imag(Wnp_k*i), i = j/2, (i = 2, 4, 6, ...)
            tblIndex += (2<<stage);
            CR1 = g_W128_i[tblIndex];       // real(Wnp/k_i+1) = real(Wnp_k*(i+1))
            SI1 = g_W128_i[tblIndex + 1];   // imag(Wnp/k_i+1) = imag(Wnp_k*(i+1))


#ifdef RECALC_FFT
            if (DORECALC_FFT(j, n)) {
              //BP2Type CR1Save = CR1;
              //BP2Type SI1Save = SI1;
              //BP2Type CR2Save = CR2;
              //BP2Type SI2Save = SI2;
              //BP2Type d1, d2, d3, d4;
              CR2 = BP2_FROM_FLOAT(cos(-j*2*PI/m));
              SI2 = BP2_FROM_FLOAT(sin(-j*2*PI/m));
              CR1 = BP2_FROM_FLOAT(cos((-j-2)*2*PI/m));
              SI1 = BP2_FROM_FLOAT(sin((-j-2)*2*PI/m));
              //d1 = BPX_ABS(CR1-CR1Save);
              //d2 = BPX_ABS(SI1-SI1Save);
              //d3 = BPX_ABS(CR2-CR2Save);
              //d4 = BPX_ABS(SI2-SI2Save);
              //assert(d1 <= 32000);
              //assert(d2 <= 32000);
              //assert(d3 <= 32000);
              //assert(d4 <= 32000);
            }
#endif

            // do main butterflies
            for (k = j; k <= n; k += m) {   /// k: {{4}{8}...{1020}} {{4,1028}{8,1032}...{508,1020}} ... {{4,20...2044}} [2048x]
                pxk = &px[k];
                pxi = &px[k + l];
                // +1/-1/W_k butterfly 
                FFTBUTTERFLY_N(pxk,pxi,CR2,SI2);        // update px[i], px[i+1] and px[k], px[k+1], leave pointers at +2
                // +1/-1/W_k butterfly 
                FFTBUTTERFLY_N(pxk,pxi,CR1,SI1);        // update px[i+2], px[i+2+1] and px[k+2], px[k+2+1], leave pointers at +2
#if 0
                /* Butterfly at a non-zero angle */
                  ur = *pxk - *pxi;           /* ur = px[k] - px[i];    */ \
                  *pxk++ += *pxi++;           /* px[k]   += px[i];      */ \
                  ui = *pxk - *pxi;           /* ui = px[k+1] - px[i+1];*/ \
                  *pxk++ += *pxi--;           /* px[k+1] += px[i+1];    */ \
                  *pxi++ = MULT_BP2(CR,ur) - MULT_BP2(SI,ui);  /* px[i]   = cr * ur - (si) * ui; */ \
                  *pxi++ = MULT_BP2(CR,ui) + MULT_BP2(SI,ur);  /* px[i+1] = cr * ui + (si) * ur; */
#endif
                // leave pxi and pxk incremented by 2
                DEBUG_COUNT_BTFLY1(6,4,6);
                DEBUG_COUNT_BTFLY1(6,4,6);
                DEBUG_COUNT_LOOP(2);
            }
            DEBUG_COUNT_TRIG(2,2);
            DEBUG_COUNT_TRIG(2,2);
            DEBUG_COUNT_LOOP(2);
        }
        m  = l;
        stage++;    //proceed to next stage of butterflies
        DEBUG_COUNT_TRIG(2,2);
        DEBUG_COUNT_LOOP(2);
    }
    if (m > 2) {
        // m normally exits the loop above == 4, so normally do this except when called with np = 1 or 2
        for (j = 0; j < n; j += 4) {        /// j: {0,4...2044}  [512x]
            pxi = (pxk = px+j) + 2;
            
            // +1/-1 butterfly 
            FFTBUTTERFLY0(pxk,pxi);
            DEBUG_COUNT_BTFLY0(4,0,4);
            DEBUG_COUNT_LOOP(2);
        }
    }
#if !BITREVERSAL_FFTDCT_LOOKUPTBL   // combine bit reversal into post FFT twiddle if BITREVERSAL_FFTDCT_LOOKUPTBL is on
    if (n > 4) {
        I32 n2, n21;
        CoefType tmp;

        n2 = np / 2;                        /// n2: 512
        n21 = np + 1;                       /// n21: 1025
        j = 0;                              
        for (i = 0; i < np; i += 4) {       /// i,j: 0,0; 4,1024; 8,512; 12,1536; ... 2044,??? [255x]

            if (i < j) {
                // swap 4 pairs of values (2 complex pairs with 2 others)
                // px[i] <-> px[j]; px[i+1] <-> px[j+1]
                // px[i+1+n21] <-> px[j+1+n21];  px[i+1+n21+1] <-> px[j+1+n21+1]
                pxi = &px[i];
                pxk = &px[j];
                tmp = *pxi; 
                *pxi++ = *pxk;
                *pxk++ = tmp;
                tmp = *pxi;
                *pxi = *pxk;
                *pxk = tmp;
                pxi  += n21;
                pxk  += n21;
                tmp = *pxi;
                *pxi++ = *pxk;
                *pxk++ = tmp;
                tmp = *pxi;
                *pxi = *pxk;
                *pxk = tmp;
            }

            // swap 2 pairs of values (1 complex pair with another)
            // px[i+2] <-> px[j+np];  px[i+3] <-> px[j+np+1]
            pxi = &px[i+2];
            pxk = &px[j+np];
            tmp = *pxi; 
            *pxi++ = *pxk;
            *pxk++ = tmp;
            tmp = *pxi;
            *pxi = *pxk;
            *pxk = tmp;

            k = n2;                         
            while (k <= j) {                /// k: {1024} {1024,512} {1024} {1024,512,256} ...
                j -= k;
                k = k / 2;
            }
            j += k;                         /// j: {1024} {512} {1536} {256} ...
        }
    }
#endif // BITREVERSAL_FFTDCT_LOOKUPTBL
#ifndef FFT_NO_SCALING
    if (fftDirection == FFT_INVERSE) // Normalization to match Intel library
        for (i = 0; i < 2 * np; i++) data[i] /= np;
#endif
    FUNCTION_PROFILE_STOP(&fp);
}
#endif // !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)

///------------------------- end of 128 point FFT -------------------------

// 128 point FFT lookup table construction
void conFFT128Tbl() 
{
    BP2Type CR2,SI2,CR1,SI1,STEP,CR,SI;
    I32 nLog2np = 7, np = 128, i;

    // Start table building for 128 point complex FFT
    // set initial values
    CR = BP2_FROM_BP1(icosPIbynp[nLog2np]);         // CR = (I32)(cos(PI/np) * NF2BP2)
    STEP = isinPIbynp[nLog2np];                     // STEP = (I32)(2*sin(-PI/np) * NF2BP2)
   
    SI = DIV2(STEP);                                // SI = (I32)(sin(-PI/np) * NF2BP2)

    // start trig recurrsion for table building
    // Wnp_0
    CR2 = BP2_FROM_FLOAT(1);                        // cos(0)
    SI2 = 0;                                        // sin(0)
    g_W128_i[0] = CR2;
    g_W128_i[1] = SI2;
    //Wnp_1
    CR1 = BP2_FROM_FLOAT(1) - MULT_BP2(STEP,SI);    // cos(-2*PI/np)
    SI = SI1 = MULT_BP2(STEP,CR);                   // sin(-2*PI/np)
    g_W128_i[2] = CR1;
    g_W128_i[3] = SI;
    CR = CR1;
    STEP = MUL2(SI1);

    //Wnp_i, Wnp_i+1, i = 2, 4, 6, ..., np/2 - 2 
    for (i = 2; i < np/2; i+=2) {
        // Wnp_i
        CR2 -= MULT_BP2(STEP,SI1);
        SI2 += MULT_BP2(STEP,CR1);
        g_W128_i[i*2] = CR2;
        g_W128_i[i*2 + 1] = SI2;
        //Wnp_i+1
        CR1 -= MULT_BP2(STEP,SI2);
        SI1 += MULT_BP2(STEP,CR2);
        g_W128_i[i*2 + 2] = CR1;
        g_W128_i[i*2 + 3] = SI1;
    }
}
#endif // defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL   

//*****************************************************************************************
//
// DCT code and related functions
//
//*****************************************************************************************

#if defined(_DEBUG)
//*****************************************************************************************
//
// auDctIV
// DCT type IV transform
//
//*****************************************************************************************
//
// define DCT_SIN_PRINT to print sin values as they are used
//#define DCT_SIN_PRINT -1
// define DCT_IN_PRINT to prinf DCT input coefs (positive value to do so for just one frame)
//#define DCT_IN_PRINT 10100
// define DCT_PRE_PRINT to print DCT coefs prior to calling FFT
//#define DCT_PRE_PRINT -1
// define DCT_POST_PRINT to print DCT coefs after calling FFT
//#define DCT_POST_PRINT -1
// define DCT_OUT_PRINT to print DCT output coefs
//#define DCT_OUT_PRINT 10100
// define this to be smaller than 2048 is you only want a sample
#define DCT_MOD_COEF_TO_PRINT 128
#   if defined(DCT_IN_PRINT) || defined(DCT_PRE_PRINT)  || defined(DCT_POST_PRINT) || defined(DCT_OUT_PRINT)
#       pragma COMPILER_MESSAGE(__FILE__ "(725) : Warning - DCT Debug Code Enabled.")
        int bPrintDctAtFrame = 0;       // used by main program to control the printing
        extern int g_ulOutputSamples;   // main must create and update
        void DebugDctPrintCoefs(CAudioObject* pau, int def, int id, float fac, CoefType* pfCoef)
        {   int dcti; float fmax = 0;                                                     
            if ( ((int)pau->m_iFrameNumber==def) || (def < 0) || (bPrintDctAtFrame&(1<<id)) )          
            {   /* MyOutputDbgStr(0, "DCT %4s %4d\n",id,n); matlab does not like */  
                static char* szID[]= { "DCT in  ", "DCT pre ", "DCT post", "DCT out ", "Wgt Fact", "WF down ", "WF up  ", "WF same" };
                for( dcti = 0; dcti < pau->m_cSubbandAdjusted; dcti++ ) {    
                    float f = id<4 ? FLOAT_FROM_COEF(pfCoef[dcti])/((Float)fac) :
                                     FLOAT_FROM_WEIGHT(pfCoef[dcti]);
                    if ( fmax < fabs(f) )       
                        fmax = (float)fabs(f);
                    if ( dcti < DCT_MOD_COEF_TO_PRINT || (dcti%DCT_MOD_COEF_TO_PRINT)==0 ) 
#                       ifdef UNDER_CE
                            MyOutputDbgStr(0, 
#                       else
                            WMAPrintf(
#                       endif
                        "%4d.%1d   %4d  %+15.7f\n",          
                            pau->m_iFrameNumber, pau->m_iCurrSubFrame, dcti, f );
                }
#               ifdef UNDER_CE
                    MyOutputDbgStr(0, szID[id]);
                    MyOutputDbgStr(0, 
#               else
                    WMAPrintf(szID[id]);
                    WMAPrintf(
#               endif
                    " %4d  %+15.7f  %7d\n", pau->m_cSubbandAdjusted, fmax, g_ulOutputSamples );
#               ifndef UNDER_CE
                    FFLUSH(stdout); 
#               endif
            }
        }
#       define DCT_PRINT(def,id,fac,pfCoef)  DebugDctPrintCoefs(pau,def,id,fac,pfCoef)
#   else
#       define DCT_PRINT(def,id,fac,pfCoef)
#   endif
#   if defined(DCT_IN_PRINT)
#       define DCT_DOPRINT_IN(fac,pfCoef) DCT_PRINT(DCT_IN_PRINT,0,fac,pfCoef)
#   else
#       define DCT_DOPRINT_IN(fac,pfCoef)
#   endif
#   if defined(DCT_PRE_PRINT)
#       define DCT_DOPRINT_PRE(fac,pfCoef) DCT_PRINT(DCT_PRE_PRINT,1,n,fac,pfCoef)
#   else
#       define DCT_DOPRINT_PRE(fac,pfCoef)
#   endif
#   if defined(DCT_POST_PRINT)
#       define DCT_DOPRINT_POST(fac,pfCoef) DCT_PRINT(DCT_POST_PRINT,2,n,fac,pfCoef)
#   else
#       define DCT_DOPRINT_POST(fac,pfCoef)
#   endif
#   if defined(DCT_OUT_PRINT)
#       define DCT_DOPRINT_OUT(fac,pfCoef) DCT_PRINT(DCT_OUT_PRINT,3,n,fac,pfCoef)
#   else
#       define DCT_DOPRINT_OUT(fac,pfCoef)
#   endif
#   if defined(DCT_SIN_PRINT)
#       pragma COMPILER_MESSAGE(__FILE__ "(774) : Warning - DCT Debug Code Enabled.")
#       define DEBUG_DCT_SIN(id,i,fac,sinv)                                     \
            if ( (pau->m_iFrameNumber==DCT_SIN_PRINT) || (DCT_SIN_PRINT < 0) )  \
            {   WMAPrintf("%2d  %4d  %+15.8f\n", id, i, sinv/fac );                \
                FFLUSH(stdout);                                                 \
            }
#   else
#       define DEBUG_DCT_SIN(id,i,fac,sinv)
#   endif
#else
#       define DCT_DOPRINT_IN(fac,pfCoef)
#       define DCT_DOPRINT_PRE(fac,pfCoef)
#       define DCT_DOPRINT_POST(fac,pfCoef)
#       define DCT_DOPRINT_OUT(fac,pfCoef)
#       define DEBUG_DCT_SIN(id,i,fac,sinv)
#endif

#if !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)

#if !((defined(WMA_TARGET_MIPS) || defined(WMA_TARGET_SH4)) && defined(PLATFORM_SPECIFIC_DCTIV))
#ifdef FFT_DUAL_MPY_ARM
// This macro is defined so we can verify bitexactness with asm version, by defining the above flag
#define DUAL_MULT_BP1(a,b,c,d) (((((I64)a * (I64)b)+((I64)c * (I64)d)) >> 32) << 1) 
#endif 

WMARESULT auDctIV(CoefType* rgiCoef,
                  BP2Type fltAfterScaleFactor,
                  U32 *piMagnitude,
                  const Int cSubbandAdjusted,
                  PFNFFT pfnFFT, Void *pFFTInfo,
                  const Int iFrameNumber,
                  const Int iCurrSubFrame,
                  const Int cFrameSampleAdjusted,
                  const Int cSubFrameSampleAdjusted)
{
    CoefType *piCoefTop, *piCoefBottom;
    CoefType iTr, iTi, iBr, iBi;
    TR1_TYPE CR, CI, STEP, CR1, CI1, CR2, CI2, CR_, CI_, CR1_, CI1_;
    Int iFFTSize, i, cSB, nLog2SB;
    TR1_TYPE  iFac;
    Bool fPowerOfTwo;
    const SinCosTable* pSinCosTable;
    double fac;
    const double dPI3Q = 3*PI/4;                        // PI (-1/4 + 1)
    const double dPIby4 = PI/4;
    const double d1p0   = 1.0 * TR1_SCALE;
    const double d2p0   = 2.0 * TR1_SCALE;
    const double d1Hp0  = 0.5 * TR1_SCALE;
    const double d1Qp0  = 0.25* TR1_SCALE;
#if defined(BUILD_INTEGER)
    Int nFacExponent;
    U32 iMagnitude = 0;
#endif

    FUNCTION_PROFILE(fp);
    FUNCTION_PROFILE_START(&fp,DCTIV_PROFILE);

#if defined(DCT_LOOKUPTBL) && DCT_LOOKUPTBL
    if (cSubbandAdjusted == 256 && 
        (FLOAT_FROM_BP2(fltAfterScaleFactor) == 1.0f || 
         FLOAT_FROM_BP2(fltAfterScaleFactor) == 2.0f/256))
    {
        auDctIV256Tbl(rgiCoef, fltAfterScaleFactor, piMagnitude, cSubbandAdjusted,
                  pfnFFT, pFFTInfo, iFrameNumber, iCurrSubFrame, cFrameSampleAdjusted,
                  cSubFrameSampleAdjusted);
        goto exit;
    }
#endif 
#ifdef FFTDCT_VAR_LOOKUPTBL
    if (cSubbandAdjusted >= MIN_FFT_LUT_SIZE && cSubbandAdjusted <= MAX_FFT_LUT_SIZE)
    {
        auVarTblDCT(rgiCoef, fltAfterScaleFactor, piMagnitude, cSubbandAdjusted,
                    pfnFFT, pFFTInfo, iFrameNumber, iCurrSubFrame, cFrameSampleAdjusted,
                    cSubFrameSampleAdjusted);
        goto exit;
    }
#endif // FFTDCT_VAR_LOOKUPTBL

    // m_cSubbandAdjusted below deals with the need to scale transform results to compensate the fact 
    // that we're inv transforming coefficients from a transform that was twice or half our size

    cSB = cSubbandAdjusted;
    iFFTSize = cSB/2;
    nLog2SB = LOG2( cSB );
    fPowerOfTwo = CHECK_POWER_OF_TWO(iFFTSize);

    piCoefTop    = rgiCoef;
    piCoefBottom = rgiCoef + cSB - 2;

#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
    prvWmaShowFrames(iFrameNumber, iCurrSubFrame, cFrameSampleAdjusted,
        cSubFrameSampleAdjusted, cSubbandAdjusted, "DCT",
        " %4d 0x%08x 0x%08x", cSB, piCoefTop, piCoefBottom);
#endif

    // fltAfterScaleFactor:  V2: 2/cSB == 1/iFFTSize and V1: sqrt(2/cSB)
#if defined(BUILD_INTEGER)
    fac = FLOAT_FROM_BP2(fltAfterScaleFactor) * cSB * d1Qp0;
    for( nFacExponent = 0; fabs(fac) > d1p0; nFacExponent++ )
        fac /= 2.0f;        // SH warning CBE4717 here is ignorable
#else   // must be BUILD_INT_FLOAT
    fac = fltAfterScaleFactor;
#endif

    // initialize sin/cos recursion
    // note this style of recursion is more accurate than Numerical Recipies 5.5.6
    if ( 64 <= cSB && cSB <= 2048 && fPowerOfTwo )
    {
        pSinCosTable = rgSinCosTables[cSB>>7];
#       if defined(BUILD_INTEGER)&& !defined(REF_64_TRIG)
            iFac = (I32)ROUNDD( fac );
#       elif defined(BUILD_INTEGER) && defined(REF_64_TRIG)
            iFac = (I64)(fac+0.5);
#       else // BUILD_INT_FLOAT
            iFac = (TR1_TYPE)fac;
#       endif //BUILD_INTEGER
        // initial cosine/sine values
        CR =  MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->cos_PIby4cSB));        // CR = (I32)(fac*cos(-PI/(4*m_cSubband)) * NF2BP1)
        CI = -MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->sin_PIby4cSB));        // CI = (I32)(fac*sin(-PI/(4*m_cSubband)) * NF2BP1)
        CR_ = MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->sin_3PIby4cSB)); // cos(3/4*pi/cSB - pi/2) = sin(3/4*pi/cSB)
        CI_ = -MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->cos_3PIby4cSB)); // sin(3/4*pi/cSB - pi/2) = -cos(3/4*pi/cSB)
        // prior cosine/sine values to init Pre-FFT recursion trig( -PI/(4*M) - (-PI/M ) = trig( 3*PI/(4*M) )
        CR1 =  MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->cos_3PIby4cSB));  // CR = (I32)(fac*cos(+3*PI/(4*m_cSubband)) * NF2BP1)
        CI1 =  MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->sin_3PIby4cSB));  // CI = (I32)(fac*sin(+3*PI/(4*m_cSubband)) * NF2BP1)
        CR1_ = -MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->sin_PIby4cSB)); // cos(-pi/4cSB - pi/2) = sin(-pi/4cSB) = -sin(-pi/4cSB)
        CI1_ = -MULT_TR1(iFac,TR1_FROM_BP1(pSinCosTable->cos_PIby4cSB)); // sin(-pi/4cSB - pi/2) = -cos(-pi/4cSB) = -cos(pi/4cSB)
        // rotation step for both recursions
        STEP = TR1_FROM_BP1(-pSinCosTable->two_sin_PIbycSB);              // STEP = 2*sin(-PI/m_cSubband) 
        // prior cosine/sine values to init Post-FFT recursion
        CR2 =  TR1_FROM_BP1(pSinCosTable->cos_PIbycSB);                   // CR = (I32)(cos( PI/m_cSubband) * NF2BP1)
        CI2 =  TR1_FROM_BP1(pSinCosTable->sin_PIbycSB);                   // CI = (I32)(sin( PI/m_cSubband) * NF2BP1)
    }
    else
    {   // not normally needed in decoder, here for generality
        double dA, dSB;

        dA = -dPIby4 / (dSB=cSB);
        CR = (TR1_TYPE)( fac * cos( dA ) );
        CI = (TR1_TYPE)( fac * sin( dA ) );
        CR1_ = (TR1_TYPE)(fac * sin( dA ) );
        CI1_ = -(TR1_TYPE)(fac * cos( dA ));
        dA = dPI3Q / dSB;
        CR1 = (TR1_TYPE)( fac * cos( dA ) );
        CI1 = (TR1_TYPE)( fac * sin( dA ) );
        CR_ = (TR1_TYPE)(fac * sin( dA ) );
        CI_ = -(TR1_TYPE)(fac * cos( dA ) );
        dA = -dPI / dSB;
        STEP = (TR1_TYPE)( d2p0 * sin( dA ) );
        CR2  = (TR1_TYPE)( d1p0 * cos( dA ) );
        CI2  = -STEP/2;  
    }

    // Include the next code-block to verify changes to the lookup-table
#if 0
    {
#       if defined(BUILD_INTEGER)
            const BP1Type Theshold = 1;
#       else
            const BP1Type Theshold = BP1_FROM_FLOAT(0.001F*fac);
#       endif
        assert(BPX_ABS(BP1_FROM_TR1(CR) - (BP1Type)( fac * cos(-dPIby4 / cSB) )) <= Theshold);
        assert(BPX_ABS(BP1_FROM_TR1(CI) - (BP1Type)( fac * sin(-dPIby4 / cSB) )) <= Theshold);
        assert(BPX_ABS(BP1_FROM_TR1(CR1) - (BP1Type)( fac * cos(dPI3Q / cSB) )) <= Theshold);
        assert(BPX_ABS(BP1_FROM_TR1(CI1) - (BP1Type)( fac * sin(dPI3Q / cSB) )) <= Theshold);
        assert(BPX_ABS(BP1_FROM_TR1(STEP) - (BP1Type)( d2p0 * sin(-dPI / cSB) )) <= Theshold);
        assert(BPX_ABS(BP1_FROM_TR1(CR2)  - (BP1Type)( d1p0 * cos(-dPI / cSB) )) <= Theshold);
        assert(BPX_ABS(BP1_FROM_TR1(CI2)  - DIV2((-(BP1Type)( d2p0 * sin(-dPI / cSB) )))) <= Theshold);
    }
#endif

    DCT_DOPRINT_IN(1.0,rgiCoef);
    
    for (i = iFFTSize/2; i > 0; i--) {
#ifdef RECALC_FFT
        if (DORECALC_FFT(i, cSB)) {
          int j = iFFTSize/2 - i;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR_ = (TR1_TYPE)(fac*cos((-dPIby4 - j*PI) / cSB));
          CI_ = (TR1_TYPE)(fac*sin((-dPIby4 - j*PI) / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        
          j = iFFTSize/2 + i - 1;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR_ = (TR1_TYPE)(fac*cos((-dPIby4 - j*PI) / cSB));
          CI_ = (TR1_TYPE)(fac*sin((-dPIby4 - j*PI) / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        }
#endif
        iBi = piCoefBottom[1];
        piCoefBottom[1] = piCoefTop[1];

        iTr = piCoefTop[0];
#ifndef FFT_DUAL_MPY_ARM
        piCoefTop[0] = MULT_ADD2_CBP1(BP1_FROM_TR1(CR),iTr, BP1_FROM_TR1(-CI),iBi);
        piCoefTop[1] = MULT_ADD2_CBP1(BP1_FROM_TR1(CR),iBi,  BP1_FROM_TR1(CI),iTr);
#else
        piCoefTop[0] = DUAL_MULT_BP1(BP1_FROM_TR1(CR),iTr,BP1_FROM_TR1(-CI),iBi);
        piCoefTop[1] = DUAL_MULT_BP1(BP1_FROM_TR1(CR),iBi,BP1_FROM_TR1(CI),iTr);
#endif 

        DEBUG_DCT_SIN(0,i,fac,CI);
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[1]));
        
        iTr = piCoefBottom[0];
        iTi = piCoefBottom[1];
        piCoefBottom[0] = MULT_ADD2_CBP1(BP1_FROM_TR1(CR_),iTr, BP1_FROM_TR1(-CI_),iTi);
        piCoefBottom[1] = MULT_ADD2_CBP1(BP1_FROM_TR1(CR_),iTi, BP1_FROM_TR1(CI_),iTr);
        DEBUG_DCT_SIN(1,i,fac,CI_);
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefBottom[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefBottom[1]));
        
        // rotate angle by b = -pi/cSubband
        // recursion: cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
        // and:       sin(a+b) = sin(a-b) + 2*sin(b)*cos(a)
        TR1_RECURR_INC_UPDATE_PREV(CR,CI,CR1,CI1,STEP) 
        /*
        UR = CR1 - MULT_BP1(STEP,CI);
        UI = CI1 + MULT_BP1(STEP,CR);
        CR1 = CR;  CR = UR;
        CI1 = CI;  CI = UI;
        */

        // rotate angle by -b = pi/cSubband
        // recursion: cos(a-b) = cos(a+b) + 2*sin(b)*sin(a)
        // and:       sin(a-b) = sin(a+b) - 2*sin(b)*cos(a)
        TR1_RECURR_INC_UPDATE_PREV(CI_,CR_,CI1_,CR1_,STEP)
        //Gives different results from TR1_RECURR_INC(CR,CI,CR1,CI1,-STEP) 
        //The current way gives no differences after before and after addition of TR1_RECURR_INC
        /*
        UR = CR1_ + MULT_BP1(STEP,CI_);
        UI = CI1_ - MULT_BP1(STEP,CR_);
        CR1_ = CR_;  CR_ = UR;
        CI1_ = CI_;  CI_ = UI;
        */
        
        piCoefTop += 2;
        piCoefBottom -= 2;
    }

    DCT_DOPRINT_PRE((fac/d1Hp0),rgiCoef);

#ifdef FFT_STATISTICS
    { 
        int np = fPowerOfTwo ? nLog2SB - 1 : iFFTSize;
        if (np < 12) {
            g_FFTNP[np]++;
        } else {
            g_FFTNP[12]++;
        }
        g_FFTNP[0]++;    // total number of FFT calls
    }
#endif

#if defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL
    if (nLog2SB - 1 == 7)
        prvFFT4DCT_128Tbl(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);
    else
#endif   
        pfnFFT(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);

    DCT_DOPRINT_POST(1.0,rgiCoef);

    // post FFT demodulation 
    // using R[i], I[i] as real and imaginary parts of complex point i
    // and C(i), S(i) are cos(i*pi/cSubband) and sin(i*pi/cSubband), and N = cSubband/2
    // R[0] = C(0) R[0] - S(0) I[0]
    // I[0] = -S(-(N-1)) R[N-1] - C(-(N-1)) I[N-1]
    // R[1] = C(1) R[1] - S(-1) I[N-1]
    // I[1] = -S(-(N-2)) R[N-2] - C(-(N-2)) I[N-2]
    // ...
    // R[N-2] = C(-(N-2)) R[N-2] - S(-(N-2)) I[N-2]
    // I[N-2] = -S(-1) R[1] - C(-1) I[1]
    // R[N-1] = C(-(N-1)) R[N-1] - S(-(N-1)) I[N-1]
    // R[N-1] = -S(0) R[0] - C(0) I[0]
    // and where 90 - angle trig formulas reveal:
    // C(-(N-i)) == -S(-i) and S(-(N-i)) = -C(-i)

    piCoefTop      = rgiCoef;           //reuse this pointer; start from head;
    piCoefBottom   = rgiCoef + cSB - 2; //reuse this pointer; start from tail;
    CR = TR1_FROM_FLOAT(1);             //one
    CI = 0;                             //zero

    for (i = iFFTSize/2; i > 0; i--) {
        iTr = piCoefTop[0];
        iTi = piCoefTop[1];
        iBr = piCoefBottom[0];
        iBi = piCoefBottom[1];

#ifdef RECALC_FFT
        if (DORECALC_FFT(i, cSB)) {
          int j = iFFTSize/2 - i;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR = TR1_FROM_FLOAT(cos(-j*PI / cSB));
          CI = TR1_FROM_FLOAT(sin(-j*PI / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        }
#endif
#ifndef FFT_DUAL_MPY_ARM
        piCoefTop[0]    =   MULT_ADD2_CBP1( BP1_FROM_TR1(CR),iTr, BP1_FROM_TR1(-CI),iTi);
        piCoefBottom[1] =  -MULT_ADD2_CBP1( BP1_FROM_TR1(CI),iTr, BP1_FROM_TR1(CR),iTi);
#else
        piCoefTop[0] =  DUAL_MULT_BP1(BP1_FROM_TR1(CR),iTr,BP1_FROM_TR1(-CI),iTi);
        piCoefBottom[1] =  DUAL_MULT_BP1(BP1_FROM_TR1(-CI),iTr,BP1_FROM_TR1(-CR),iTi);
#endif
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefTop[0]) );
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefBottom[1]) );

        DEBUG_DCT_SIN(2,i,d1p0,CI);
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefBottom[1]));
        // rotate angle by b = -pi/cSubband
        // recursion: cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
        // and:       sin(a+b) = sin(a-b) + 2*sin(b)*cos(a)
        TR1_RECURR_INC_UPDATE_PREV(CR,CI,CR2,CI2,STEP) 
        /*
        UR = CR2 - MULT_BP1(STEP,CI);
        UI = CI2 + MULT_BP1(STEP,CR);
        CR2 = CR;  CR = UR;
        CI2 = CI;  CI = UI;
        */

        // note that cos(-(cSubband/2 - i)*pi/cSubband ) = -sin( -i*pi/cSubband )
#ifndef FFT_DUAL_MPY_ARM
        piCoefTop[1]    = MULT_ADD2_CBP1( BP1_FROM_TR1(CR),iBr,  BP1_FROM_TR1(CI),iBi);
        piCoefBottom[0] = MULT_ADD2_CBP1(BP1_FROM_TR1(-CI),iBr,  BP1_FROM_TR1(CR),iBi);
#else
        piCoefTop[1] = DUAL_MULT_BP1(BP1_FROM_TR1(CR),iBr,BP1_FROM_TR1(CI),iBi);
        piCoefBottom[0] = DUAL_MULT_BP1(BP1_FROM_TR1(-CI),iBr,BP1_FROM_TR1(CR),iBi);
#endif 
        
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefTop[1]) );
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefBottom[0]) );

        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefTop[1]));
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefBottom[0]));

        piCoefTop += 2;
        piCoefBottom -= 2;
    }
#if defined(BUILD_INTEGER)
    if ( nFacExponent > 0 )
    {   // This scaling needed in v1 bit-streams
        piCoefTop      = rgiCoef; 
        iMagnitude <<= nFacExponent;
        for( i = cSB; i > 0; i-- )
        {
            *piCoefTop++ <<= nFacExponent;
        }
    }
#endif


    if (NULL != piMagnitude)
        *piMagnitude = INTEGER_OR_INT_FLOAT( iMagnitude, 0 );
#ifdef COEF64BIT
    assert(piMagnitude == NULL);
    if (NULL != piMagnitude) return WMA_E_NOTSUPPORTED;
#endif

#if (defined(DCT_LOOKUPTBL) && DCT_LOOKUPTBL) || (defined(FFTDCT_VAR_LOOKUPTBL))
exit:
#endif

    DCT_DOPRINT_OUT(1.0,rgiCoef);
#if defined(DCT_OUT_PRINT) && defined(_DEBUG)
    if (iFrameNumber == DCT_OUT_PRINT)
    { DEBUG_BREAK(); }
#endif
    FUNCTION_PROFILE_STOP(&fp);

    return WMA_OK;
}
#endif //!((WMA_TARGET_MIPS || WMA_TARGET_SH4) && PLATFORM_SPECIFIC_DCTIV)
#endif // !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM) 

#if defined(BUILD_INT_FLOAT) && !defined(WMA_DISABLE_SSE1)

#include <xmmintrin.h>

WMARESULT auDctIV_SSE1(Float* rgiCoef, 
                  Float fltAfterScaleFactor,
                  U32 *piMagnitude,
                  const Int cSubbandAdjusted,
                  PFNFFT pfnFFT, Void *pFFTInfo,
                  const Int iFrameNumber,
                  const Int iCurrSubFrame,
                  const Int cFrameSampleAdjusted,
                  const Int cSubFrameSampleAdjusted)
{
    Float *piCoefTop;
    Float *piCoefBottom;
    Float STEP, iFac;
    Int iFFTSize, i, cSB, nLog2SB;
    Bool fPowerOfTwo;
    const SinCosTable* pSinCosTable;
    double fac;
    const double dPI3Q  = 3*PI/4;                        // PI (-1/4 + 1)
    const double dPIby4 = PI/4;
    const double d1p0   = 1.0;
    const double d2p0   = 2.0;
    const double d1Hp0  = 0.5;
    const double d1Qp0  = 0.25;

    __m128 vCRb, vCIb, vCR2b, vCI2b;
    __m128 vCR, vCI, vCR1, vCI1, vCR2, vCI2, vSTEP, vSTEP2;
    __m128 vURnext, vUInext, vCR1next, vCI1next, vCRnext, vCInext;

#define Z_NEG 0x80000000

    const unsigned __int32 izerosnodd [4] = { 0, Z_NEG, 0, Z_NEG };
    const unsigned __int32 izerosneven[4] = { Z_NEG, 0, Z_NEG, 0 };

    const __m128 vzerosnodd  = _mm_loadu_ps( (const float*)&izerosnodd  );
    const __m128 vzerosneven = _mm_loadu_ps( (const float*)&izerosneven );

    // m_cSubbandAdjusted below deals with the need to scale transform results to compensate the fact 
    // that we're inv transforming coefficients from a transform that was twice or half our size

    cSB = cSubbandAdjusted;
    iFFTSize = cSB/2;
    nLog2SB = LOG2( cSB );
    fPowerOfTwo = CHECK_POWER_OF_TWO(iFFTSize);

    // fltAfterScaleFactor:  V2: 2/cSB == 1/iFFTSize and V1: sqrt(2/cSB)

    fac = fltAfterScaleFactor;

    // initialize sin/cos recursion
    // note this style of recursion is more accurate than Numerical Recipies 5.5.6
    
    if ( 64 <= cSB && cSB <= 2048 && fPowerOfTwo )
    {
        pSinCosTable = rgSinCosTables[cSB>>7];
        iFac = (Float)fac;

        // initial cosine/sine values
        vCR   = _mm_set1_ps(  iFac * pSinCosTable->cos_PIby4cSB );
        vCI   = _mm_set1_ps( -iFac * pSinCosTable->sin_PIby4cSB );

        // prior cosine/sine values to init Pre-FFT recursion
        // trig( -PI/(4*M) - (-PI/M ) = trig( 3*PI/(4*M) )
        vCR1  = _mm_set1_ps( iFac * pSinCosTable->cos_3PIby4cSB );
        vCI1  = _mm_set1_ps( iFac * pSinCosTable->sin_3PIby4cSB );

        // rotation step for both recursions
        vSTEP = _mm_set1_ps( -pSinCosTable->two_sin_PIbycSB );
        vSTEP2 = _mm_set1_ps( -2*pSinCosTable->sin_2PIbycSB );

        // prior cosine/sine values to init Post-FFT recursion
        vCR2  = _mm_set1_ps( pSinCosTable->cos_PIbycSB );
        vCI2  = _mm_set1_ps( pSinCosTable->sin_PIbycSB );
    }
    else
    {   // not normally needed in decoder, here for generality
        double dA, dSB;

        dA     = -dPIby4 / (dSB=cSB);
        vCR    = _mm_set1_ps( (Float)(fac * cos( dA )) );
        vCI    = _mm_set1_ps( (Float)(fac * sin( dA )) );

        dA     = dPI3Q / dSB;
        vCR1   = _mm_set1_ps( (Float)(fac * cos( dA )) );
        vCI1   = _mm_set1_ps( (Float)(fac * sin( dA )) );

        dA     = -dPI / dSB;
        vSTEP  = _mm_set1_ps( STEP = (Float)(d2p0 * sin( dA )) );
        vSTEP2 = _mm_set1_ps( (Float)(d2p0 * sin( 2*dA )) );
        vCR2   = _mm_set1_ps( (Float)(d1p0 * cos( dA )) );
        vCI2   = _mm_set1_ps( -STEP/2 ); 
    }

    vURnext  = _mm_sub_ps( vCR1, _mm_mul_ps( vSTEP, vCI ) );
    vUInext  = _mm_add_ps( vCI1, _mm_mul_ps( vSTEP, vCR ) );
    vCR1next = vCR; vCRnext = vURnext;
    vCI1next = vCI; vCInext = vUInext;

    vCR  = _mm_movelh_ps( vCR , vCRnext  );
    vCI  = _mm_movelh_ps( vCI , vCInext  );
    vCR1 = _mm_movelh_ps( vCR1, vCR1next );
    vCI1 = _mm_movelh_ps( vCI1, vCI1next );

    // step CR1, CI1 backwards 1 more increment, because
    // we will be stepping forward 2x in the loop using
    // vSTEP2 = 2*sin(2b) instead of vSTEP = 2*sin(b)

    vURnext = _mm_add_ps( vCR, _mm_mul_ps( vSTEP, vCI1 ) );
    vUInext = _mm_sub_ps( vCI, _mm_mul_ps( vSTEP, vCR1 ) );
    vCR1 = vURnext;
    vCI1 = vUInext;

    piCoefTop    = rgiCoef; 
    piCoefBottom = rgiCoef + cSB - 4;

    // 1st pass - just reorg data so
    // that it is easier to vectorize.

    for( i = 0; i < iFFTSize; i += 4 )
    {
        __m128 vTop, vBot;

        vTop = _mm_load_ps( piCoefTop    + i );
        vBot = _mm_load_ps( piCoefBottom - i );

        vTop = _mm_shuffle_ps( vTop, vTop, _MM_SHUFFLE( 1,3,2,0 ) );
        vBot = _mm_shuffle_ps( vBot, vBot, _MM_SHUFFLE( 2,0,1,3 ) );

        _mm_store_ps( piCoefTop    + i, _mm_unpacklo_ps( vTop, vBot ) );
        _mm_store_ps( piCoefBottom - i, _mm_unpackhi_ps( vBot, vTop ) );
    }

    piCoefTop = rgiCoef;

    for( i = 0; i < 2*iFFTSize; i += 4 )
    {
        __m128 vUR, vUI;
        __m128 vMulCR, vMulCI;

        vMulCR = _mm_load_ps( piCoefTop + i );
        vMulCI = _mm_shuffle_ps( vMulCR, vMulCR,
                        _MM_SHUFFLE( 2,3,0,1 ) );

        vMulCI = _mm_xor_ps( vMulCI, vzerosneven );
        vMulCR = _mm_add_ps( _mm_mul_ps( vCR, vMulCR ),
                             _mm_mul_ps( vCI, vMulCI ) );

        _mm_store_ps( piCoefTop + i, vMulCR );

        // rotate angle by b = -2*pi/cSubband
        // recursion: cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
        // and:       sin(a+b) = sin(a-b) + 2*sin(b)*cos(a)

        // notice that this is stepping forward 2 steps with vSTEP2!

        vUR  = _mm_sub_ps( vCR1, _mm_mul_ps( vSTEP2, vCI ) );
        vUI  = _mm_add_ps( vCI1, _mm_mul_ps( vSTEP2, vCR ) );
        vCR1 = vCR;  vCR = vUR;
        vCI1 = vCI;  vCI = vUI;
    }

    //Call the integer FFT explicitly
#ifdef FFT_STATISTICS
    { 
        int np = fPowerOfTwo ? nLog2SB - 1 : iFFTSize;
        if (np < 12) {
            g_FFTNP[np]++;
        } else {
            g_FFTNP[12]++;
        }
        g_FFTNP[0]++;    // total number of FFT calls
    }
#endif

    pfnFFT(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);

    // post FFT demodulation 
    vCR = _mm_set1_ps( 1 );           //one
    vCI = _mm_set1_ps( 0 );           //zero

    vURnext  = _mm_sub_ps( vCR2, _mm_mul_ps( vSTEP, vCI ) );
    vUInext  = _mm_add_ps( vCI2, _mm_mul_ps( vSTEP, vCR ) );
    vCR1next = vCR;  vCRnext = vURnext;
    vCI1next = vCI;  vCInext = vUInext;

    vCR  = _mm_movelh_ps( vCR , vCRnext  );
    vCI  = _mm_movelh_ps( vCI , vCInext  );
    vCR2 = _mm_movelh_ps( vCR2, vCR1next );
    vCI2 = _mm_movelh_ps( vCI2, vCI1next );

    vCRb = _mm_sub_ps( vCR2, _mm_mul_ps( vSTEP, vCI ) );
    vCIb = _mm_add_ps( vCI2, _mm_mul_ps( vSTEP, vCR ) );
    vCR2b = vCR2;
    vCI2b = vCI2;

    vURnext  = _mm_add_ps( vCR, _mm_mul_ps( vSTEP, vCI2 ) );
    vUInext  = _mm_sub_ps( vCI, _mm_mul_ps( vSTEP, vCR2 ) );
    vCR2 = vURnext;
    vCI2 = vUInext;

    piCoefTop    = rgiCoef;           //reuse this pointer; start from head;
    piCoefBottom = rgiCoef + cSB - 4; //reuse this pointer; start from tail;

    for( i = 0; i < iFFTSize; i += 4 )
    {
        __m128 vUR, vUI, vURb, vUIb;
        __m128 vMulCR, vMulCI, vMulCRb, vMulCIb;

        vMulCR  = _mm_load_ps ( piCoefTop    + i );
        vMulCIb = _mm_loadr_ps( piCoefBottom - i );

        vMulCI  = _mm_shuffle_ps( vMulCR , vMulCR , _MM_SHUFFLE( 2,3,0,1 ) );
        vMulCRb = _mm_shuffle_ps( vMulCIb, vMulCIb, _MM_SHUFFLE( 2,3,0,1 ) );

        vMulCR  = _mm_xor_ps( vMulCR , vzerosnodd );
        vMulCIb = _mm_xor_ps( vMulCIb, vzerosnodd );

        vMulCR  = _mm_sub_ps( _mm_mul_ps( vCR , vMulCR  ),
                              _mm_mul_ps( vCI , vMulCI  ) );

        vMulCIb = _mm_add_ps( _mm_mul_ps( vCRb, vMulCRb ),
                              _mm_mul_ps( vCIb, vMulCIb ) );

        vMulCR  = _mm_shuffle_ps( vMulCR , vMulCR , _MM_SHUFFLE( 1,3,2,0 ) );
        vMulCIb = _mm_shuffle_ps( vMulCIb, vMulCIb, _MM_SHUFFLE( 1,3,2,0 ) );

        _mm_store_ps( piCoefTop    + i, _mm_unpacklo_ps( vMulCR , vMulCIb ) );
        _mm_store_ps( piCoefBottom - i, _mm_unpackhi_ps( vMulCIb, vMulCR  ) );

        // rotate angle by b = -2*pi/cSubband
        // recursion: cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
        // and:       sin(a+b) = sin(a-b) + 2*sin(b)*cos(a)
        
        // notice that this is stepping forward 2 steps with vSTEP2!
        
        vUR   = _mm_sub_ps( vCR2 , _mm_mul_ps( vSTEP2, vCI ) );
        vUI   = _mm_add_ps( vCI2 , _mm_mul_ps( vSTEP2, vCR ) );
        vCR2  = vCR;  vCR = vUR;
        vCI2  = vCI;  vCI = vUI;

        vURb  = _mm_sub_ps( vCR2b, _mm_mul_ps( vSTEP2, vCIb ) );
        vUIb  = _mm_add_ps( vCI2b, _mm_mul_ps( vSTEP2, vCRb ) );
        vCR2b = vCRb;  vCRb = vURb;
        vCI2b = vCIb;  vCIb = vUIb;
    }

    if (NULL != piMagnitude)
        *piMagnitude = INTEGER_OR_INT_FLOAT( iMagnitude, 0 );

    return WMA_OK;
}

#endif // BUILD_INT_FLOAT && !WMA_DISABLE_SSE1

#   if defined(_SH4_)
#       pragma warning(pop)
#   endif


#if defined(DCT_LOOKUPTBL) && DCT_LOOKUPTBL
WMARESULT auDctIV256Tbl(CoefType* rgiCoef,
                  BP2Type fltAfterScaleFactor,  // Used to be float type. Extra conversion needed to convert BP2Type back to float. Could hurt perf due to division. Changed to BP2Type to match v10 in anyway. 
                  U32 *piMagnitude,
                  const Int cSubbandAdjusted,
                  PFNFFT pfnFFT, Void *pFFTInfo,
                  const Int iFrameNumber,
                  const Int iCurrSubFrame,
                  const Int cFrameSampleAdjusted,
                  const Int cSubFrameSampleAdjusted)
{
    CoefType *piCoefTop, *piCoefBottom;
    CoefType iTr, iTi, iBr, iBi;
    BP1Type CR, CI;
#ifndef TWO_STAGE_PREFFT_TWIDDLE
    BP1Type CR1, CI1;       // one stage pre FFT twiddle
    CoefType iBr1, iTi1;    // one stage pre FFT twiddle
#endif
    Int iFFTSize, i, cSB, nLog2SB;
    Bool fPowerOfTwo;
#if defined(BUILD_INTEGER)
    const double d1p0   = 1.0 * NF2BP1;
    const double d1Hp0  = 0.5 * NF2BP1;
    Int nFacExponent;
    U32 iMagnitude = 0;
#else  // must be BUILD_INT_FLOAT
    const double d1p0   = 1.0;
    const double d1Hp0  = 0.5;
#endif  // BUILD_INTEGER or BUILD_INT_FLOAT
    BP1Type *pre128FFTTbl = NULL, *post128FFTTbl = NULL;

#if BITREVERSAL_FFTDCT_LOOKUPTBL
    Int iIdxTop, iIdxBot;   // bit reversal index to top and bottom coeffs
    Int iIdxTopBR, iIdxBotBR;
    Int j;
    BP1Type CRBR, CIBR;
    CoefType iTrBR, iTiBR, iBrBR, iBiBR;
#endif
    FUNCTION_PROFILE(fp);
    FUNCTION_PROFILE_START(&fp,DCTIV_PROFILE);

    // m_cSubbandAdjusted below deals with the need to scale transform results to compensate the fact 
    // that we're inv transforming coefficients from a transform that was twice or half our size

    cSB = cSubbandAdjusted;
    iFFTSize = cSB/2;
    nLog2SB = LOG2( cSB );
    fPowerOfTwo = CHECK_POWER_OF_TWO(iFFTSize);
    
    if (FLOAT_FROM_BP2(fltAfterScaleFactor) == 1.0f) {  // extra conversion step from BP2Type back to float. could hurt perf due to division
#if defined(BUILD_INTEGER)
        nFacExponent = g_nFacExponent_scale1;   // 6
#endif
        pre128FFTTbl = g_pre128FFTTbl_scale1;
    } else { 
        //fltAfterScaleFactor = 2.0f/256
        assert(FLOAT_FROM_BP2(fltAfterScaleFactor) == 2.0f/256);

#if defined(BUILD_INTEGER)
        nFacExponent = g_nFacExponent_scale2_256;   // 0
#endif
        pre128FFTTbl = g_pre128FFTTbl_scale2_256;
    }
    post128FFTTbl = g_post128FFTTbl;

    piCoefTop    = rgiCoef;               
    piCoefBottom = rgiCoef + cSB - 1;

#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
    prvWmaShowFrames(iFrameNumber, iCurrSubFrame, cFrameSampleAdjusted,
        cSubFrameSampleAdjusted, cSubbandAdjusted, "DCT",
        " %4d 0x%08x 0x%08x", cSB, piCoefTop, piCoefBottom);
#endif

#ifdef TWO_STAGE_PREFFT_TWIDDLE
    // two-stage pre FFT twiddle (one stage processing is preferred. TWO_STAGE_PREFFT_TWIDDLE is therefore off by default)
    // stage 1 (1st half)
    for (i = iFFTSize; i > 0; i-=2) {
#ifdef RECALC_FFT
        if (DORECALC_FFT(i, cSB)) {
          int j = (iFFTSize - i)/2;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR = (BP1Type)(fac*cos((-dPIby4 - j*PI) / cSB));
          CI = (BP1Type)(fac*sin((-dPIby4 - j*PI) / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        }
#endif
        CR = pre128FFTTbl[iFFTSize - i];        // cos(-j(n+1/4)PI/256), n = 0, 1, 2, 3, ..., 63
        CI = pre128FFTTbl[iFFTSize - i + 1];    // sin(-j(n+1/4)PI/256), n = 0, 1, 2, 3, ..., 63
        iBi = piCoefBottom[0];
        piCoefBottom[0] = piCoefTop[1];

        iTr = piCoefTop[0];
        piCoefTop[0] = MULT_CBP1(CR,iTr) - MULT_CBP1(CI,iBi);   // real 
        piCoefTop[1] = MULT_CBP1(CR,iBi) + MULT_CBP1(CI,iTr);   // imag

        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[1]));

        piCoefTop += 2;
        piCoefBottom -= 2;
    }

    // stage 2 (2nd half)
    for (i = iFFTSize; i > 0; i-=2) {
#ifdef RECALC_FFT
        if (DORECALC_FFT(i, cSB)) {
          int j = iFFTSize - i/2;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR = (BP1Type)(fac*cos((-dPIby4 - j*PI) / cSB));
          CI = (BP1Type)(fac*sin((-dPIby4 - j*PI) / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        }
#endif
        CR = pre128FFTTbl[iFFTSize*2 - i];      // cos(-j(n+1/4)PI/256), n = 64, 65, 66, ..., 127
        CI = pre128FFTTbl[iFFTSize*2 - i + 1];  // sin(-j(n+1/4)PI/256), n = 64, 65, 66, ..., 127
        iTr = piCoefTop[0];
        iTi = piCoefTop[1];
        piCoefTop[0] = MULT_CBP1(CR,iTr) - MULT_CBP1(CI,iTi);   // real
        piCoefTop[1] = MULT_CBP1(CR,iTi) + MULT_CBP1(CI,iTr);   // imag

        DEBUG_DCT_SIN(1,i,fac,CI);
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[1]));

        piCoefTop += 2;
    }
#else
    // consolidate two stages pre FFT twiddle processing into one stage twiddle (preferred)
    // one stage pre FFT twiddle
    for (i = iFFTSize; i > 0; i-=2) {
        CR = pre128FFTTbl[iFFTSize - i];        // cos(-j(n+1/4)PI/256), n = 0, 1, 2, 3, ..., 63
        CI = pre128FFTTbl[iFFTSize - i + 1];    // sin(-j(n+1/4)PI/256), n = 0, 1, 2, 3, ..., 63
        CI1 = pre128FFTTbl[iFFTSize-1+i];       // sin(-j((127-n)+1/4)PI/256), n = 0, 1, 2, 3, ..., 63
        CR1 = pre128FFTTbl[iFFTSize-1+i-1];     // cos(-j((127-n)+1/4)PI/256), n = 0, 1, 2, 3, ..., 63

        iBi = piCoefBottom[0];
        iBr1 = piCoefBottom[-1];

        iTr = piCoefTop[0];
        iTi1 = piCoefTop[1];

        piCoefTop[0] = MULT_CBP1(CR,iTr) - MULT_CBP1(CI,iBi);           // real
        piCoefTop[1] = MULT_CBP1(CR,iBi) + MULT_CBP1(CI,iTr);           // imag

        piCoefBottom[-1] = MULT_CBP1(CR1,iBr1) - MULT_CBP1(CI1,iTi1);   // real
        piCoefBottom[0] = MULT_CBP1(CR1,iTi1) + MULT_CBP1(CI1,iBr1);    // imag

        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(piCoefTop[1]));

        piCoefTop += 2;
        piCoefBottom -= 2;
    }
#endif  

    DCT_DOPRINT_PRE((fac/d1Hp0),rgiCoef);

#ifdef FFT_STATISTICS
    { 
        int np = fPowerOfTwo ? nLog2SB - 1 : iFFTSize;
        if (np < 12) {
            g_FFTNP[np]++;
        } else {
            g_FFTNP[12]++;
        }
        g_FFTNP[0]++;    // total number of FFT calls
    }
#endif
    //Call the integer FFT explicitly
#if defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL
    if (nLog2SB - 1 == 7)
        prvFFT4DCT_128Tbl(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);
    else
#endif  
        pfnFFT(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);

    DCT_DOPRINT_POST(1.0,rgiCoef);

#if !BITREVERSAL_FFTDCT_LOOKUPTBL
    // post FFT demodulation 
    // using R[i], I[i] as real and imaginary parts of complex point i
    // and C(i), S(i) are cos(i*pi/cSubband) and sin(i*pi/cSubband), and N = cSubband/2
    // R[0] = C(0) R[0] - S(0) I[0]
    // I[0] = -S(-(N-1)) R[N-1] - C(-(N-1)) I[N-1]
    // R[1] = C(1) R[1] - S(-1) I[N-1]
    // I[1] = -S(-(N-2)) R[N-2] - C(-(N-2)) I[N-2]
    // ...
    // R[N-2] = C(-(N-2)) R[N-2] - S(-(N-2)) I[N-2]
    // I[N-2] = -S(-1) R[1] - C(-1) I[1]
    // R[N-1] = C(-(N-1)) R[N-1] - S(-(N-1)) I[N-1]
    // R[N-1] = -S(0) R[0] - C(0) I[0]
    // and where 90 - angle trig formulas reveal:
    // C(-(N-i)) == -S(-i) and S(-(N-i)) = -C(-i)

    piCoefTop      = rgiCoef;           //reuse this pointer; start from head;
    piCoefBottom   = rgiCoef + cSB - 2; //reuse this pointer; start from tail;
    CR = post128FFTTbl[0];
    CI = post128FFTTbl[1];

    for (i = iFFTSize/2; i > 0; i--) {
        iTr = piCoefTop[0];
        iTi = piCoefTop[1];
        iBr = piCoefBottom[0];
        iBi = piCoefBottom[1];

#ifdef RECALC_FFT
        if (DORECALC_FFT(i, cSB)) {
          int j = iFFTSize/2 - i;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR = BP1_FROM_FLOAT(cos(-j*PI / cSB));
          CI = BP1_FROM_FLOAT(sin(-j*PI / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        }
#endif
        piCoefTop[0] =  MULT_CBP1(CR,iTr) -  MULT_CBP1(CI,iTi);     // real
        piCoefBottom[1] =  MULT_CBP1(-CI,iTr) - MULT_CBP1(CR,iTi);  // -imag
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefTop[0]) );
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefBottom[1]) );

        DEBUG_DCT_SIN(2,i,d1p0,CI);
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefBottom[1]));

        CR = post128FFTTbl[iFFTSize - 2*(i-1)];     // cos(-j*(i+1)*PI/256), i = 0, 1, 2, 3, ..., 63
        CI = post128FFTTbl[iFFTSize - 2*(i-1) +1];  // sin(-j*(i+1)*PI/256), i = 0, 1, 2, 3, ..., 63
        // note that cos(-(cSubband/2 - i)*pi/cSubband ) = -sin( -i*pi/cSubband )
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines.
        #if 0
        piCoefTop[1] = MULT_CBP1(CR,iBr) + MULT_CBP1(CI,iBi);       // -imag
        piCoefBottom[0] = MULT_CBP1(-CI,iBr) +  MULT_CBP1(CR,iBi);  // real
        #else
        // to match and achieve bitexactness with combined bitreversal/post FFT twiddle processing
        piCoefTop[1] = MULT_CBP1(CR,iBr) - MULT_CBP1(-CI,iBi);      // -imag
        piCoefBottom[0] = MULT_CBP1(-CI,iBr) -  MULT_CBP1(-CR,iBi); // real
        #endif
       
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefTop[1]) );
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefBottom[0]) );

        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefTop[1]));
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefBottom[0]));

        piCoefTop += 2;
        piCoefBottom -= 2;
    }
#else   // BITREVERSAL_FFTDCT_LOOKUPTBL
    // Combine bit reversal for 128 point complex FFT into post FFT twiddle
    // WARNING: 
    // Due to the truncation inside MULT_CBP1, there is numeric difference 
    // between d - (a*b)>>c and d + (-a*b)>>c 
    // the max diff seems to be +/-4 after bit reversal with post FFT twiddle.
    // there is therefore no way to achieve bit-exactness with the previous code 
    // unless correct rounding is implemented inside MULT_CBP1 in the future.

    piCoefTop      = rgiCoef;           //reuse this pointer; start from head;

    // pass 1: take care of cases other than (0-0,127-127) (8-8,119-119) (20-20,107-107) (28-28,99-99) (34-34,93-93) (42-42,85-85) (54-54,73-73) (62-62,65-65) 
    for (i = BR128TWIDDLETBL_ENTRY, j = 0; i > 0; i--, j+=BR128TWIDDLETbl_INC) {
        iIdxTop = g_BR128TwiddleTbl[j];        // location to get bit reversed data pre post FFT twiddle
        iIdxTopBR = g_BR128TwiddleTbl[j+1];        // location to get post FFT twiddle coeffs and to write post FFT twiddle modulation
        #if !SMALL_BR128TWIDDLE_LOOKUPTBL
        iIdxBot = g_BR128TwiddleTbl[j+2];
        iIdxBotBR = g_BR128TwiddleTbl[j+3];
        #else
        iIdxBot = 127 - iIdxTop;
        iIdxBotBR = 127 - iIdxTopBR;
        #endif

        CR = post128FFTTbl[iIdxTopBR*2];    // location to get post FFT twiddle coeffs for data from top
        CI = post128FFTTbl[iIdxTopBR*2+1];

        iTr = piCoefTop[iIdxTop*2];         // top real for post FFT twiddle
        iTi = piCoefTop[iIdxTop*2+1];       // top imag for post FFT twiddle
        iBr = piCoefTop[iIdxBot*2];         // bottom real for post FFT twiddle
        iBi = piCoefTop[iIdxBot*2+1];       // bottom imag for post FFT twiddle

        CRBR = post128FFTTbl[iIdxTop*2];    // location to get mirrored post FFT twiddle coeffs
        CIBR = post128FFTTbl[iIdxTop*2+1];

        iTrBR = piCoefTop[iIdxTopBR*2];     // mirrored data for iTr
        iTiBR = piCoefTop[iIdxTopBR*2+1];   // mirrored data for iTi
        iBrBR = piCoefTop[iIdxBotBR*2];     // mirrored data for iBr
        iBiBR = piCoefTop[iIdxBotBR*2+1];   // mirrored data for iBi

        // write demodulated post FFT twiddled data for the data from top
        piCoefTop[iIdxTopBR*2] =  MULT_CBP1(CR,iTr) -  MULT_CBP1(CI,iTi);       // real
        piCoefTop[iIdxBotBR*2+1] =  MULT_CBP1(-CI,iTr) - MULT_CBP1(CR,iTi);     // -imag

        // write demodulated post FFT twiddled data for the mirrored data from top 
        piCoefTop[iIdxTop*2] =  MULT_CBP1(CRBR,iTrBR) -  MULT_CBP1(CIBR,iTiBR);     // real
        piCoefTop[iIdxBot*2+1] =  MULT_CBP1(-CIBR,iTrBR) - MULT_CBP1(CRBR,iTiBR);   // -imag

        // post FFT twiddle and demodulation for the data from bottom
        CR = post128FFTTbl[iIdxBotBR*2];    // location to get post FFT twiddle coeffs for data from bottom
        CI = post128FFTTbl[iIdxBotBR*2+1];

        // write demodulated post FFT twiddled data for the data from bottom
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines
        #if 1
        piCoefTop[iIdxBotBR*2] =  MULT_CBP1(CR,iBr) -  MULT_CBP1(CI,iBi);     // real
        piCoefTop[iIdxTopBR*2+1] =  MULT_CBP1(-CI,iBr) - MULT_CBP1(CR,iBi);   // -imag
        #else
        piCoefTop[iIdxBotBR*2] =  MULT_CBP1(CR,iBr) +  MULT_CBP1(-CI,iBi);      // real
        piCoefTop[iIdxTopBR*2+1] =  MULT_CBP1(-CI,iBr) + MULT_CBP1(-CR,iBi);    // -imag
        #endif

        CRBR = post128FFTTbl[iIdxBot*2];    // location to get mirrored post FFT twiddle coeffs for data from bottom
        CIBR = post128FFTTbl[iIdxBot*2+1];
       
        // write demodulated post FFT twiddled data for the mirrored data from bottom
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines
        #if 1
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CRBR,iBrBR) -  MULT_CBP1(CIBR,iBiBR);     // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CIBR,iBrBR) - MULT_CBP1(CRBR,iBiBR);   // -imag
        #else
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CRBR,iBrBR) +  MULT_CBP1(-CIBR,iBiBR);    // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CIBR,iBrBR) + MULT_CBP1(-CRBR,iBiBR);  // -imag
        #endif
    }

    // pass 2: take care of special cases - (0-0,127-127) (20-20,107-107) (34-34,93-93) (42-42,85-85), (8-8,119-119) (28-28,99-99) (54-54,73-73) (62-62,65-65) 
    for (i = BR128TWIDDLETBL_SPECIAL_ENTRY, j = 0; i > 0; i--, j+=BR128TWIDDLETbl_SPECIAL_INC) {
        iIdxTop = g_BR128TwiddleTbl_special[j];        // location to get bit reversed data pre post FFT twiddle
        #if !SMALL_BR128TWIDDLE_LOOKUPTBL
        iIdxBot = g_BR128TwiddleTbl_special[j+1];
        #else
        iIdxBot = 127 - iIdxTop;
        #endif

        CR = post128FFTTbl[iIdxTop*2];  
        CI = post128FFTTbl[iIdxTop*2+1];

        iTr = piCoefTop[iIdxTop*2];         // top real for post FFT twiddle
        iTi = piCoefTop[iIdxTop*2+1];       // top imag for post FFT twiddle
        iBr = piCoefTop[iIdxBot*2];         // bottom real for post FFT twiddle
        iBi = piCoefTop[iIdxBot*2+1];       // bottom imag for post FFT twiddle

        // write demodulated post FFT twiddled data for the data from top
        piCoefTop[iIdxTop*2] =  MULT_CBP1(CR,iTr) -  MULT_CBP1(CI,iTi);         // real
        piCoefTop[iIdxBot*2+1] =  MULT_CBP1(-CI,iTr) - MULT_CBP1(CR,iTi);       // -imag

        // post FFT twiddle and demodulation for the data from bottom
        CR = post128FFTTbl[iIdxBot*2];  // location to get post FFT twiddle coeffs for data from bottom
        CI = post128FFTTbl[iIdxBot*2+1];

        // write demodulated post FFT twiddled data for the data from bottom
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines
        #if 1
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CR,iBr) -  MULT_CBP1(CI,iBi);       // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CI,iBr) - MULT_CBP1(CR,iBi);     // -imag
        #else
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CR,iBr) +  MULT_CBP1(-CI,iBi);        // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CI,iBr) + MULT_CBP1(-CR,iBi);      // -imag
        #endif
    }
#endif  // BITREVERSAL_FFTDCT_LOOKUPTBL

#if defined(BUILD_INTEGER)
    if ( nFacExponent > 0 )
    {   // This scaling needed in v1 bit-streams
        piCoefTop      = rgiCoef; 
        iMagnitude <<= nFacExponent;
        for( i = cSB; i > 0; i-- )
        {
            *piCoefTop++ <<= nFacExponent;
        }
    }
#endif

    if (NULL != piMagnitude)
        *piMagnitude = INTEGER_OR_INT_FLOAT( iMagnitude, 0 );
#ifdef COEF64BIT
    assert(piMagnitude == NULL);
    if (NULL != piMagnitude) return WMA_E_NOTSUPPORTED;
#endif

    DCT_DOPRINT_OUT(1.0,rgiCoef);
#if defined(DCT_OUT_PRINT) && defined(_DEBUG)
    if (iFrameNumber == DCT_OUT_PRINT)
    { DEBUG_BREAK(); }
#endif
    FUNCTION_PROFILE_STOP(&fp);

    return WMA_OK;
}

void conpre128FFTbl(BP1Type *preFFTTbl, I32 *pg_nFacExponent, float fltAfterScaleFactor)
{
    int i, j, nFacExponent;
    double fac;
    int iFac;

    const double d1p0   = 1.0 * NF2BP1;
    const double d1Qp0  = 0.25* NF2BP1;

    int cSB = 256;
    int iFFTSize = cSB/2;

    fac = fltAfterScaleFactor * cSB * d1Qp0;
    for( nFacExponent = 0; fabs(fac) > d1p0; nFacExponent++ )
        fac /= 2.0f;        // SH warning CBE4717 here is ignorable

    iFac = (I32)ROUNDD(fac);
    *pg_nFacExponent = nFacExponent;
#if 0
    for (i = 0, j =0; j < iFFTSize*2; i++, j+=2) 
    {
        preFFTTbl[j] = MULT_BP1(iFac, cos((-PI/4 -i*PI)/cSB)*NF2BP1);   // cos(-(i+1/4)PI/M)
        preFFTTbl[j+1] = MULT_BP1(iFac, sin((-PI/4-i*PI)/cSB)*NF2BP1);  // sin(-(i+1/4)PI/M)
    }
#else
    // recursion
    { 
        TR1_TYPE CR, CI, STEP, CR1, CI1;
        const SinCosTable* pSinCosTable = &g_sct256;

        // initial cosine/sine values
        CR =  MULT_TR1(TR1_FROM_BP1(iFac),TR1_FROM_BP1(pSinCosTable->cos_PIby4cSB));        // CR = (I32)(fac*cos(-PI/(4*m_cSubband)) * NF2BP1)
        CI = -MULT_TR1(TR1_FROM_BP1(iFac),TR1_FROM_BP1(pSinCosTable->sin_PIby4cSB));        // CI = (I32)(fac*sin(-PI/(4*m_cSubband)) * NF2BP1)
        // prior cosine/sine values to init Pre-FFT recursion trig( -PI/(4*M) - (-PI/M ) = trig( 3*PI/(4*M) )
        CR1 =  MULT_TR1(TR1_FROM_BP1(iFac),TR1_FROM_BP1(pSinCosTable->cos_3PIby4cSB));  // CR = (I32)(fac*cos(+3*PI/(4*m_cSubband)) * NF2BP1)
        CI1 =  MULT_TR1(TR1_FROM_BP1(iFac),TR1_FROM_BP1(pSinCosTable->sin_3PIby4cSB));  // CI = (I32)(fac*sin(+3*PI/(4*m_cSubband)) * NF2BP1)
        // rotation step for both recursions
        STEP = TR1_FROM_BP1(-pSinCosTable->two_sin_PIbycSB);              // STEP = 2*sin(-PI/m_cSubband) 

        for (i = iFFTSize, j =0; i > 0; i--) {
            // rotate angle by -b = -pi/cSubband
            // recursion: cos(a-b) = cos(a+b) - 2*sin(b)*sin(a)
            // and:       sin(a-b) = sin(a+b) + 2*sin(b)*cos(a)
            preFFTTbl[j++] = BP1_FROM_TR1(CR);
            preFFTTbl[j++] = BP1_FROM_TR1(CI);

            TR1_RECURR_INC_UPDATE_PREV(CR,CI,CR1,CI1,STEP)
            /*
            UR = CR1 - MULT_BP1(STEP,CI);
            UI = CI1 + MULT_BP1(STEP,CR);
            CR1 = CR;  CR = UR;
            CI1 = CI;  CI = UI;
            */
        }
    }
#endif
}

void conpost128FFTbl(BP1Type *postFFTTbl)
{
    int i, j;
    int cSB = 256;
    int iFFTSize = cSB/2;

#if 0
    for (i = 0, j =0; j < iFFTSize*2; i++, j+=2) 
    {
        postFFTTbl[j] = BP1_FROM_FLOAT(cos(-i*PI/cSB));     // cos(-i*PI/M)
        postFFTTbl[j+1] = BP1_FROM_FLOAT(sin(-i*PI/cSB));   // sin(-i*PI/M)
    }
#else
    {
        // recursion
        TR1_TYPE CR, CI, CR2, CI2, STEP;
        const SinCosTable* pSinCosTable = &g_sct256;

        // initial cos, sin value
        CR = TR1_FROM_FLOAT(1);             //one
        CI = 0;                             //zero
        STEP = TR1_FROM_BP1(-pSinCosTable->two_sin_PIbycSB);              // STEP = 2*sin(-PI/m_cSubband) 
        // prior cosine/sine values to init Post-FFT recursion
        CR2 =  TR1_FROM_BP1(pSinCosTable->cos_PIbycSB);                   // CR = (I32)(cos( PI/m_cSubband) * NF2BP1)
        CI2 =  TR1_FROM_BP1(pSinCosTable->sin_PIbycSB);                   // CI = (I32)(sin( PI/m_cSubband) * NF2BP1)

        for (i = iFFTSize/2, j = 0; i > 0; i--, j+=2) {
            // rotate angle by -b = -pi/cSubband
            // recursion: cos(a-b) = cos(a+b) - 2*sin(b)*sin(a)
            // and:       sin(a-b) = sin(a+b) + 2*sin(b)*cos(a)

            postFFTTbl[j] = BP1_FROM_TR1(CR);         // cos(-i*PI/M), i = 0, 1, 2, 3, ..., 63
            postFFTTbl[j+1] = BP1_FROM_TR1(CI);       // sin(-i*PI/M), i = 0, 1, 2, 3, ..., 63

            TR1_RECURR_INC_UPDATE_PREV(CR,CI,CR2,CI2,STEP)
            /*
            UR = CR2 - MULT_BP1(STEP,CI);
            UI = CI2 + MULT_BP1(STEP,CR);
            CR2 = CR;  CR = UR;
            CI2 = CI;  CI = UI;
            */

#if BITREVERSAL_FFTDCT_LOOKUPTBL
            // construct cos(-i*PI/M), sin(-i*PI/M) for i = 127, 126, ..., 64 
            postFFTTbl[(iFFTSize-1)*2 -j] = BP1_FROM_TR1(-CI);      // cos(-(M/2-n-1)*PI/M) = -sin(-(n+1)*PI/M)
            postFFTTbl[(iFFTSize-1)*2 -j + 1] = BP1_FROM_TR1(-CR);  // sin(-(M/2-n-1)*PI/M) = -cos(-(n+1)*PI/M)
#endif
        }
#if !BITREVERSAL_FFTDCT_LOOKUPTBL
        postFFTTbl[j] = BP1_FROM_TR1(CR);     // cos(-i*PI/M), i = 64
        postFFTTbl[j+1] = BP1_FROM_TR1(CI);   // sin(-i*PI/M), i =64
#endif
    }
#endif
}

#endif  //DCT_LOOKUPTBL

#if BITREVERSAL_FFTDCT_LOOKUPTBL
#if 0
void conBitReversal128Tbl()
{
    int i, tmp;

    // only need construct first 64 bit-reversal mapping
    for (i = 0; i < 64; i++) {
        // bitreverse128(i)
        tmp = (i << 6) & 0x40;      // bit 0 -> bit 6
        tmp |= ((i << 4) & 0x20);   // bit 1 -> bit 5
        tmp |= ((i << 2) & 0x10);   // bit 2 -> bit 4
        tmp |= i & 0x8;             // bit 3
        tmp |= ((i >> 2) & 0x4);    // bit 4 -> bit 2
        tmp |= ((i >> 4) & 0x2);    // bit 5 -> bit 1
        tmp |= (i >> 6);

        g_BR128[i] = tmp;
    }

}
#endif  // 0
#endif  // BITREVERSAL_FFTDCT_LOOKUPTBL

//*****************************************************************************************
//
// Combination of windowing, DCT and reflection functions
//
//*****************************************************************************************

#if defined(CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL) && CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL
#if !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)
WMARESULT auWindowReflectionAndDctIV256(CoefType* rgiCoef,
                  BP2Type fltAfterScaleFactor,
                  U32 *piMagnitude,
                  const Int cSubbandAdjusted,
                  PFNFFT pfnFFT, Void *pFFTInfo,
                  const Int iFrameNumber,
                  const Int iCurrSubFrame,
                  const Int cFrameSampleAdjusted,
                  const Int cSubFrameSampleAdjusted)
{
    Int iFFTSize, i, cSB, nLog2SB;
    Bool fPowerOfTwo;
    double fac;
#if defined(BUILD_INTEGER)
    const double d1p0   = 1.0 * NF2BP1;
    const double d1Hp0  = 0.5 * NF2BP1;
    const double d1Qp0  = 0.25* NF2BP1;
    Int nFacExponent;
    U32 iMagnitude = 0;
#else  // must be BUILD_INT_FLOAT
    const double d1p0   = 1.0;
    const double d1Hp0  = 0.5;
    const double d1Qp0  = 0.25;
#endif  // BUILD_INTEGER or BUILD_INT_FLOAT
    CoefType *piCoefTop;


    FUNCTION_PROFILE(fp);
    FUNCTION_PROFILE_START(&fp,DCTIV_PROFILE);

    // m_cSubbandAdjusted below deals with the need to scale transform results to compensate the fact 
    // that we're inv transforming coefficients from a transform that was twice or half our size

    cSB = cSubbandAdjusted;
    iFFTSize = cSB/2;
    nLog2SB = LOG2( cSB );
    fPowerOfTwo = CHECK_POWER_OF_TWO(iFFTSize);

#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
    prvWmaShowFrames(iFrameNumber, iCurrSubFrame, cFrameSampleAdjusted,
        cSubFrameSampleAdjusted, cSubbandAdjusted, "DCT",
        " %4d 0x%08x 0x%08x", cSB, piCoefTop, piCoefBottom);
#endif

    // fltAfterScaleFactor:  V2: 2/cSB == 1/iFFTSize and V1: sqrt(2/cSB)
#if defined(BUILD_INTEGER)
    fac = FLOAT_FROM_BP2(fltAfterScaleFactor) * cSB * d1Qp0;
    for( nFacExponent = 0; fabs(fac) > d1p0; nFacExponent++ )
        fac /= 2.0f;        // SH warning CBE4717 here is ignorable
#else   // must be BUILD_INT_FLOAT
    fac = fltAfterScaleFactor;
#endif

    DCT_DOPRINT_IN(1.0,rgiCoef);

    WindowRefPre128FFT(rgiCoef);

    DCT_DOPRINT_PRE((fac/d1Hp0),rgiCoef);

#ifdef FFT_STATISTICS
    { 
        int np = fPowerOfTwo ? nLog2SB - 1 : iFFTSize;
        if (np < 12) {
             g_FFTNP[np]++;
        } else {
            g_FFTNP[12]++;
        }
        g_FFTNP[0]++;    // total number of FFT calls
    }
#endif

    FFTPost128FFTTwiddle(rgiCoef, cSubbandAdjusted, pfnFFT, pFFTInfo, iMagnitude); 

#if defined(BUILD_INTEGER)
        if ( nFacExponent > 0 )
        {   // This scaling needed in v1 bit-streams
            piCoefTop      = rgiCoef; 
            iMagnitude <<= nFacExponent;
            for( i = cSB; i > 0; i-- )
            {
                *piCoefTop++ <<= nFacExponent;
            }
        }
#endif

    if (NULL != piMagnitude)
        *piMagnitude = INTEGER_OR_INT_FLOAT( iMagnitude, 0 );
#ifdef COEF64BIT
    assert(piMagnitude == NULL);
    if (NULL != piMagnitude) return WMA_E_NOTSUPPORTED;
#endif

    DCT_DOPRINT_OUT(1.0,rgiCoef);
#if defined(DCT_OUT_PRINT) && defined(_DEBUG)
    if (iFrameNumber == DCT_OUT_PRINT)
    { DEBUG_BREAK(); }
#endif
    FUNCTION_PROFILE_STOP(&fp);

    return WMA_OK;
}
#endif  // WMA_OPT_FFT_ARM

void conWinRefPre128FFTbl(BP1Type* PreCookedTab)
{
    int i;
    int iFFTSize = 128;

    BP1Type *preFFTTbl = g_pre128FFTTbl_scale1;

  
    for (i = 0; i < iFFTSize/4; i++)
    {
        BP1Type CR, CI, CR_, CI_, CRP, CIP, CRP_, CIP_;
        int j;
        
        j = i;
        CR = preFFTTbl[2*j];   // (BP1Type)(fac*cos((-dPIby4 - j*PI) / cSB));
        CI = preFFTTbl[2*j+1]; // (BP1Type)(fac*sin((-dPIby4 - j*PI) / cSB));
        
        j = iFFTSize/2 - i - 1;
        CRP = preFFTTbl[2*j];   // (BP1Type)(fac*cos((-dPIby4 - j*PI) / cSB));
        CIP = preFFTTbl[2*j+1]; // (BP1Type)(fac*sin((-dPIby4 - j*PI) / cSB));

        j = iFFTSize - i - 1;
        CR_ = preFFTTbl[2*j];   // (BP1Type)(fac*cos((-dPIby4 - j*PI) / cSB));
        CI_ = preFFTTbl[2*j+1]; // (BP1Type)(fac*sin((-dPIby4 - j*PI) / cSB));
        
        j = iFFTSize/2 + i;
        CRP_ = preFFTTbl[2*j];   // (BP1Type)(fac*cos((-dPIby4 - j*PI) / cSB));
        CIP_ = preFFTTbl[2*j+1]; // (BP1Type)(fac*sin((-dPIby4 - j*PI) / cSB));
        
#ifdef COEF64BIT // different tab layout to make tab ptr stride match coef ptr stride
        PreCookedTab[    4*i+0] = MULT_BP1(CR, CRP_);
        PreCookedTab[    4*i+1] = MULT_BP1(CR, CIP_);
        PreCookedTab[    4*i+2] = MULT_BP1(CI, CIP_);
        PreCookedTab[    4*i+3] = MULT_BP1(CI, CRP_);
        PreCookedTab[128+4*i+0] = MULT_BP1(CR_, CRP);
        PreCookedTab[128+4*i+1] = MULT_BP1(CR_, CIP);
        PreCookedTab[128+4*i+2] = MULT_BP1(CI_, CIP);
        PreCookedTab[128+4*i+3] = MULT_BP1(CI_, CRP);
#else
        PreCookedTab[    2*i+0] = MULT_BP1(CR, CRP_);
        PreCookedTab[    2*i+1] = MULT_BP1(CR, CIP_);
        PreCookedTab[ 64+2*i+0] = MULT_BP1(CI, CIP_);
        PreCookedTab[ 64+2*i+1] = MULT_BP1(CI, CRP_);
        PreCookedTab[128+2*i+0] = MULT_BP1(CR_, CRP);
        PreCookedTab[128+2*i+1] = MULT_BP1(CR_, CIP);
        PreCookedTab[192+2*i+0] = MULT_BP1(CI_, CIP);
        PreCookedTab[192+2*i+1] = MULT_BP1(CI_, CRP);
#endif
    }
}

#if !(defined(WMA_OPT_FFT_ARM) && WMA_OPT_FFT_ARM)    
#ifndef WMA_TARGET_ARM
void WindowRefPre128FFT(CoefType* rgiCoef)
{   //  64  64  64  64  64  64  64  64
    //  pb0 pe0 pb1 pe1 pb2 pe2 pb3 pe3
    //  ->- -<- ->- -<- ->- -<- ->- -<-
    CoefType *pb0 = rgiCoef,
             *pe0 = rgiCoef + 128 - 2;
#define pb1 (pb0 + 128)
#define pe1 (pe0 + 128)
#define pb2 (pb0 + 256)
#define pe2 (pe0 + 256)
#define pb3 (pb0 + 384)
#define pe3 (pe0 + 384)

#ifdef COEF64BIT
#define t0 t[0]
#define t1 t[1]
#define t2 t[2]
#define t3 t[3]
#define t4 t[128]
#define t5 t[129]
#define t6 t[130]
#define t7 t[131]
#else
#define t0 t[0]
#define t1 t[1]
#define t2 t[64]
#define t3 t[65]
#define t4 t[128]
#define t5 t[129]
#define t6 t[192]
#define t7 t[193]
#endif
#define t (((BP1Type*)(pb0)) - 256)
    
    while (pb0 < pe0) {
#define MUL MULT_CBP1
        {
            BP1Type c0, c1, c2, c3;
            CoefType sav0, sav1;
            CoefType b0, b1, e0, e1;

            c0=t0; c1=t1; c2=t2; c3=t3;
                
            b0=pb1[0]; b1=pb3[0]; e0=pe0[1]; e1=pe2[1];
            sav0 = pb0[0];
            sav1 = pb0[1];
            pb0[0] = MUL(c0,b1) - MUL(c1,e1) + MUL(c2,b0) + MUL(c3,e0);
            pb0[1] = -MUL( c0,e0) - MUL( c1,b0) - MUL( c2,e1) + MUL( c3,b1);
                 
            b1=pb2[0]; e0=pe1[1]; e1=pe3[1]; b0 = pb1[1];
            pb1[0] = MUL(c0,e0) - MUL(c1,b1) + MUL(c2,e1) + MUL(c3,sav0);
            pb1[1] = MUL(c0,b1) + MUL(c1,e0) + MUL(c2,sav0) - MUL(c3,e1);
                
            c0=t4; c1=t5; c2=t6; c3=t7;
                
            b1=pb2[1]; e0=pe1[0]; e1=pe3[0];
            sav0 = pe0[0];
            pe0[0] = MUL(c0,e1) + MUL(c1,sav1) + MUL(c2,e0) - MUL(c3,b1);
            pe0[1] = -MUL(c0,sav1)+ MUL(c1,e1) - MUL(c2,b1) - MUL(c3,e0);
                
            e1=pe2[0]; b1=pb3[1]; // sav0 is pe0[0], b0 is pb1[1];
            pe1[0] = MUL(c0,b0) + MUL(c1,sav0) + MUL(c2,b1) - MUL(c3,e1);
            pe1[1] = MUL(c0,e1) - MUL(c1,b1) + MUL(c2,sav0) + MUL(c3,b0);
                
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb0[0]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb0[1]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe1[0]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe1[1]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe0[0]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe0[1]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb1[0]));
            MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb1[1]));
        }
            
        pb0 += 2;
        pe0 -= 2;
    }
#undef t
}
#else   //WMA_TARGET_ARM
void WindowRefPre128FFT(CoefType* rgiCoef)
{   //  64  64  64  64  64  64  64  64
    //  pb0 pe0 pb1 pe1 pb2 pe2 pb3 pe3
    //  ->- -<- ->- -<- ->- -<- ->- -<-
    CoefType *pb0 = rgiCoef,
             *pe0 = rgiCoef + 128 - 2;

#define t (((BP1Type*)(pb0)) - 256) // WinRefPre128FFT lookup table has 256 int entries and is allocated immediatly before rgiCoef
    
    while (pb0 < pe0) {
        BP1Type c0, c1, c2, c3;
        CoefType sav0, sav1;
        CoefType b0, b1, e0, e1;

        c0 = t[0]; 
        c1 = t[1]; 
        c2 = t[64]; 
        c3 = t[65];
                
        b0 = pb0[128]; 
        b1 = pb0[384]; 
        e0 = pe0[1]; 
        e1 = pe0[256+1];
        sav0 = pb0[0];
        sav1 = pb0[1];
        pb0[0] = MULT_CBP1(c0,b1) - MULT_CBP1(c1,e1) + MULT_CBP1(c2,b0) + MULT_CBP1(c3,e0);
        pb0[1] = -MULT_CBP1( c0,e0) - MULT_CBP1( c1,b0) - MULT_CBP1( c2,e1) + MULT_CBP1( c3,b1);

        b0 = pb0[128+1];
        b1 = pb0[256]; 
        e0 = pe0[128+1]; 
        e1 = pe0[384+1]; 
        pb0[128] = MULT_CBP1(c0,e0) - MULT_CBP1(c1,b1) + MULT_CBP1(c2,e1) + MULT_CBP1(c3,sav0);
        pb0[128+1] = MULT_CBP1(c0,b1) + MULT_CBP1(c1,e0) + MULT_CBP1(c2,sav0) - MULT_CBP1(c3,e1);
                

        c0 = t[128]; 
        c1 = t[129]; 
        c2 = t[192]; 
        c3 = t[193];
                
        b1 = pb0[256+1]; 
        e0 = pe0[128]; 
        e1 = pe0[384];
        sav0 = pe0[0];  // sav1 = pb0[1]
        pe0[0] = MULT_CBP1(c0,e1) + MULT_CBP1(c1,sav1) + MULT_CBP1(c2,e0) - MULT_CBP1(c3,b1);
        pe0[1] = -MULT_CBP1(c0,sav1)+ MULT_CBP1(c1,e1) - MULT_CBP1(c2,b1) - MULT_CBP1(c3,e0);
                
        e1 = pe0[256]; 
        b1 = pb0[384+1]; // sav0 = pe0[0], b0 = pb0[128+1]
        pe0[128] = MULT_CBP1(c0,b0) + MULT_CBP1(c1,sav0) + MULT_CBP1(c2,b1) - MULT_CBP1(c3,e1);
        pe0[128+1] = MULT_CBP1(c0,e1) - MULT_CBP1(c1,b1) + MULT_CBP1(c2,sav0) + MULT_CBP1(c3,b0);
                
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb0[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb0[1]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe0[128]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe0[128+1]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe0[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pe0[1]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb1[0]));
        MONITOR_RANGE(gMR_DCTCoefIntoFFT,FLOAT_FROM_COEF(pb1[1]));
            
        pb0 += 2;
        pe0 -= 2;
    }
#undef t
}
#endif  //WMA_TARGET_ARM

void FFTPost128FFTTwiddle(CoefType* rgiCoef,
                  const Int cSubbandAdjusted,
                  PFNFFT pfnFFT, Void *pFFTInfo, U32 iMagnitude) 
{
    Int iFFTSize, i, cSB, nLog2SB;
    Bool fPowerOfTwo;

    CoefType *piCoefTop;
    CoefType iTr, iTi, iBr, iBi;
    BP1Type CR, CI;

#if BITREVERSAL_FFTDCT_LOOKUPTBL
    Int iIdxTop, iIdxBot;   // bit reversal index to top and bottom coeffs
    Int iIdxTopBR, iIdxBotBR;
    Int j;
    BP1Type CRBR, CIBR;
    CoefType iTrBR, iTiBR, iBrBR, iBiBR;
#else
    CoefType *piCoefBottom;
#endif

    BP1Type *post128FFTTbl = g_post128FFTTbl;

    cSB = cSubbandAdjusted;
    iFFTSize = cSB/2;
    nLog2SB = LOG2( cSB );
    fPowerOfTwo = CHECK_POWER_OF_TWO(iFFTSize);

    //Call the integer FFT explicitly
#if defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL
    if (nLog2SB - 1 == 7)
        prvFFT4DCT_128Tbl(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);
    else
#endif 
        pfnFFT(pFFTInfo, rgiCoef, (fPowerOfTwo ? nLog2SB - 1 : iFFTSize), FFT_FORWARD);

    DCT_DOPRINT_POST(1.0,rgiCoef);

#if !BITREVERSAL_FFTDCT_LOOKUPTBL
    // post FFT demodulation 
    // using R[i], I[i] as real and imaginary parts of complex point i
    // and C(i), S(i) are cos(i*pi/cSubband) and sin(i*pi/cSubband), and N = cSubband/2
    // R[0] = C(0) R[0] - S(0) I[0]
    // I[0] = -S(-(N-1)) R[N-1] - C(-(N-1)) I[N-1]
    // R[1] = C(1) R[1] - S(-1) I[N-1]
    // I[1] = -S(-(N-2)) R[N-2] - C(-(N-2)) I[N-2]
    // ...
    // R[N-2] = C(-(N-2)) R[N-2] - S(-(N-2)) I[N-2]
    // I[N-2] = -S(-1) R[1] - C(-1) I[1]
    // R[N-1] = C(-(N-1)) R[N-1] - S(-(N-1)) I[N-1]
    // R[N-1] = -S(0) R[0] - C(0) I[0]
    // and where 90 - angle trig formulas reveal:
    // C(-(N-i)) == -S(-i) and S(-(N-i)) = -C(-i)

    piCoefTop      = rgiCoef;           //reuse this pointer; start from head;
    piCoefBottom   = rgiCoef + cSB - 2; //reuse this pointer; start from tail;
    CR = post128FFTTbl[0];
    CI = post128FFTTbl[1];

    for (i = iFFTSize/2; i > 0; i--) {
        iTr = piCoefTop[0];
        iTi = piCoefTop[1];
        iBr = piCoefBottom[0];
        iBi = piCoefBottom[1];

#ifdef RECALC_FFT
        if (DORECALC_FFT(i, cSB)) {
          int j = iFFTSize/2 - i;
          //BP1Type CRSave = CR;
          //BP1Type CISave = CI;
          //BP1Type d1, d2;
          CR = BP1_FROM_FLOAT(cos(-j*PI / cSB));
          CI = BP1_FROM_FLOAT(sin(-j*PI / cSB));
          //d1 = BPX_ABS(CR-CRSave);
          //d2 = BPX_ABS(CI-CISave);
          //assert(d1 <= 4);
          //assert(d2 <= 4);
        }
#endif
        piCoefTop[0] =  MULT_CBP1(CR,iTr) -  MULT_CBP1(CI,iTi);     // real
        piCoefBottom[1] =  MULT_CBP1(-CI,iTr) - MULT_CBP1(CR,iTi);  // -imag
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefTop[0]) );
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefBottom[1]) );

        DEBUG_DCT_SIN(2,i,d1p0,CI);
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefTop[0]));
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefBottom[1]));

        CR = post128FFTTbl[iFFTSize - 2*(i-1)];     // cos(-j*(i+1)*PI/256), i = 0, 1, 2, 3, ..., 63
        CI = post128FFTTbl[iFFTSize - 2*(i-1) +1];  // sin(-j*(i+1)*PI/256), i = 0, 1, 2, 3, ..., 63
        // note that cos(-(cSubband/2 - i)*pi/cSubband ) = -sin( -i*pi/cSubband )
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines.
        #if 0   
        piCoefTop[1] = MULT_CBP1(CR,iBr) + MULT_CBP1(CI,iBi);       // -imag
        piCoefBottom[0] = MULT_CBP1(-CI,iBr) +  MULT_CBP1(CR,iBi);  // real
        #else
        // to match and achieve bitexactness with combined bitreversal/post FFT twiddle processing
        piCoefTop[1] = MULT_CBP1(CR,iBr) - MULT_CBP1(-CI,iBi);      // -imag
        piCoefBottom[0] = MULT_CBP1(-CI,iBr) -  MULT_CBP1(-CR,iBi); // real
        #endif
       
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefTop[1]) );
        INTEGER_ONLY( iMagnitude |= abs((I32)piCoefBottom[0]) );

        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefTop[1]));
        MONITOR_RANGE(gMR_DCTCoefOut,FLOAT_FROM_COEF(piCoefBottom[0]));

        piCoefTop += 2;
        piCoefBottom -= 2;
    }
#else   // BITREVERSAL_FFTDCT_LOOKUPTBL
    // Combine bit reversal for 128 point complex FFT into post FFT twiddle
    // WARNING: 
    // Due to the truncation inside MULT_CBP1, there is numeric difference 
    // between d - (a*b)>>c and d + (-a*b)>>c 
    // the max diff seems to be +/-4 after bit reversal with post FFT twiddle.
    // there is therefore no way to achieve bit-exactness with the previous code 
    // unless correct rounding is implemented inside MULT_CBP1 in the future.

    piCoefTop      = rgiCoef;           //reuse this pointer; start from head;

    // pass 1: take care of cases other than (0-0,127-127) (8-8,119-119) (20-20,107-107) (28-28,99-99) (34-34,93-93) (42-42,85-85) (54-54,73-73) (62-62,65-65) 
    for (i = BR128TWIDDLETBL_ENTRY, j = 0; i > 0; i--, j+=BR128TWIDDLETbl_INC) {
        iIdxTop = g_BR128TwiddleTbl[j];        // location to get bit reversed data pre post FFT twiddle
        iIdxTopBR = g_BR128TwiddleTbl[j+1];        // location to get post FFT twiddle coeffs and to write post FFT twiddle modulation
        #if !SMALL_BR128TWIDDLE_LOOKUPTBL
        iIdxBot = g_BR128TwiddleTbl[j+2];
        iIdxBotBR = g_BR128TwiddleTbl[j+3];
        #else
        iIdxBot = 127 - iIdxTop;
        iIdxBotBR = 127 - iIdxTopBR;
        #endif

        CR = post128FFTTbl[iIdxTopBR*2];    // location to get post FFT twiddle coeffs for data from top
        CI = post128FFTTbl[iIdxTopBR*2+1];

        iTr = piCoefTop[iIdxTop*2];         // top real for post FFT twiddle
        iTi = piCoefTop[iIdxTop*2+1];       // top imag for post FFT twiddle
        iBr = piCoefTop[iIdxBot*2];         // bottom real for post FFT twiddle
        iBi = piCoefTop[iIdxBot*2+1];       // bottom imag for post FFT twiddle

        CRBR = post128FFTTbl[iIdxTop*2];    // location to get mirrored post FFT twiddle coeffs
        CIBR = post128FFTTbl[iIdxTop*2+1];

        iTrBR = piCoefTop[iIdxTopBR*2];     // mirrored data for iTr
        iTiBR = piCoefTop[iIdxTopBR*2+1];   // mirrored data for iTi
        iBrBR = piCoefTop[iIdxBotBR*2];     // mirrored data for iBr
        iBiBR = piCoefTop[iIdxBotBR*2+1];   // mirrored data for iBi

        // write demodulated post FFT twiddled data for the data from top
        piCoefTop[iIdxTopBR*2] =  MULT_CBP1(CR,iTr) -  MULT_CBP1(CI,iTi);       // real
        piCoefTop[iIdxBotBR*2+1] =  MULT_CBP1(-CI,iTr) - MULT_CBP1(CR,iTi);     // -imag

        // write demodulated post FFT twiddled data for the mirrored data from top 
        piCoefTop[iIdxTop*2] =  MULT_CBP1(CRBR,iTrBR) -  MULT_CBP1(CIBR,iTiBR);     // real
        piCoefTop[iIdxBot*2+1] =  MULT_CBP1(-CIBR,iTrBR) - MULT_CBP1(CRBR,iTiBR);   // -imag

        // post FFT twiddle and demodulation for the data from bottom
        CR = post128FFTTbl[iIdxBotBR*2];    // location to get post FFT twiddle coeffs for data from bottom
        CI = post128FFTTbl[iIdxBotBR*2+1];

        // write demodulated post FFT twiddled data for the data from bottom
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines
        #if 1
        piCoefTop[iIdxBotBR*2] =  MULT_CBP1(CR,iBr) -  MULT_CBP1(CI,iBi);     // real
        piCoefTop[iIdxTopBR*2+1] =  MULT_CBP1(-CI,iBr) - MULT_CBP1(CR,iBi);   // -imag
        #else
        piCoefTop[iIdxBotBR*2] =  MULT_CBP1(CR,iBr) +  MULT_CBP1(-CI,iBi);      // real
        piCoefTop[iIdxTopBR*2+1] =  MULT_CBP1(-CI,iBr) + MULT_CBP1(-CR,iBi);    // -imag
        #endif

        CRBR = post128FFTTbl[iIdxBot*2];    // location to get mirrored post FFT twiddle coeffs for data from bottom
        CIBR = post128FFTTbl[iIdxBot*2+1];
       
        // write demodulated post FFT twiddled data for the mirrored data from bottom
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines
        #if 1
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CRBR,iBrBR) -  MULT_CBP1(CIBR,iBiBR);     // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CIBR,iBrBR) - MULT_CBP1(CRBR,iBiBR);   // -imag
        #else
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CRBR,iBrBR) +  MULT_CBP1(-CIBR,iBiBR);    // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CIBR,iBrBR) + MULT_CBP1(-CRBR,iBiBR);  // -imag
        #endif
    }

    // pass 2: take care of special cases - (0-0,127-127) (20-20,107-107) (34-34,93-93) (42-42,85-85), (8-8,119-119) (28-28,99-99) (54-54,73-73) (62-62,65-65) 
    for (i = BR128TWIDDLETBL_SPECIAL_ENTRY, j = 0; i > 0; i--, j+=BR128TWIDDLETbl_SPECIAL_INC) {
        iIdxTop = g_BR128TwiddleTbl_special[j];        // location to get bit reversed data pre post FFT twiddle
        #if !SMALL_BR128TWIDDLE_LOOKUPTBL
        iIdxBot = g_BR128TwiddleTbl_special[j+1];
        #else
        iIdxBot = 127 - iIdxTop;
        #endif

        CR = post128FFTTbl[iIdxTop*2];  
        CI = post128FFTTbl[iIdxTop*2+1];

        iTr = piCoefTop[iIdxTop*2];         // top real for post FFT twiddle
        iTi = piCoefTop[iIdxTop*2+1];       // top imag for post FFT twiddle
        iBr = piCoefTop[iIdxBot*2];         // bottom real for post FFT twiddle
        iBi = piCoefTop[iIdxBot*2+1];       // bottom imag for post FFT twiddle

        // write demodulated post FFT twiddled data for the data from top
        piCoefTop[iIdxTop*2] =  MULT_CBP1(CR,iTr) -  MULT_CBP1(CI,iTi);         // real
        piCoefTop[iIdxBot*2+1] =  MULT_CBP1(-CI,iTr) - MULT_CBP1(CR,iTi);       // -imag

        // post FFT twiddle and demodulation for the data from bottom
        CR = post128FFTTbl[iIdxBot*2];  // location to get post FFT twiddle coeffs for data from bottom
        CI = post128FFTTbl[iIdxBot*2+1];

        // write demodulated post FFT twiddled data for the data from bottom
        // due to the truncation inside MULT_CBP1, there is numeric difference between d - (a*b)>>c and d + (-a*b)>>c 
        // thus the commented out 2 lines below produce different results than uncommented out 2 lines
        #if 1
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CR,iBr) -  MULT_CBP1(CI,iBi);       // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CI,iBr) - MULT_CBP1(CR,iBi);     // -imag
        #else
        piCoefTop[iIdxBot*2] =  MULT_CBP1(CR,iBr) +  MULT_CBP1(-CI,iBi);        // real
        piCoefTop[iIdxTop*2+1] =  MULT_CBP1(-CI,iBr) + MULT_CBP1(-CR,iBi);      // -imag
        #endif
    }
#endif  // BITREVERSAL_FFTDCT_LOOKUPTBL
}
#endif  //WMA_OPT_FFT_ARM
#endif  // CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL

#endif // ( defined(WMA_TARGET_SH3) || defined(WMA_TARGET_SH4) ) && defined(BUILD_INTEGER)

//*****************************************************************************************
//
// Miscellaneous functions
//
//*****************************************************************************************

// Implements flip on iSize array
Void auFlipCoeff(CoefType *pctCoeff, Int iSize)
{
    Int i;
    CoefType *pctTop, *pctBottom, ctTemp;

    pctTop = pctCoeff;
    pctBottom = pctCoeff + iSize - 1;
    for (i=0; i < iSize/2; i++)
    {
        ctTemp = *pctTop;
        *pctTop = *pctBottom;
        *pctBottom = ctTemp;
        pctTop++;
        pctBottom--;
    }
}

// Implement DST-IV using a DCT-IV
// If M is the length of the sequence, then we can calculate dst using
// following matlab code (x=input, y=output=dstiv(x))
//   x = flipud(x);
//   y = dctiv(x);
//   M = length(x);
//   y(2:2:M) = -y(2:2:M);
WMARESULT auDstIV(CoefType* rgiCoef, BP2Type fltAfterScaleFactor,
                  U32 *piMagnitude,
                  const Int cSubbandAdjusted, FNDCTIV *pfnDctIV, 
                  PFNFFT pfnFFT, Void *pFFTInfo,
                  const Int iFrameNumber,
                  const Int iCurrSubFrame, const Int cFrameSampleAdjusted,
                  const Int cSubFrameSampleAdjusted,
                  Bool fFlip)
{
    WMARESULT wmaResult = WMA_OK;
    Int i;

    if (fFlip)
    {   // flip the sequence
        auFlipCoeff(rgiCoef, cSubbandAdjusted);
    }

    TRACEWMA_EXIT(wmaResult,
               (pfnDctIV)(rgiCoef, fltAfterScaleFactor, piMagnitude,
                          cSubbandAdjusted, pfnFFT, pFFTInfo, iFrameNumber,
                          iCurrSubFrame, cFrameSampleAdjusted,
                          cSubFrameSampleAdjusted));

    // negate all the odd indexed elements
    for (i=1; i < cSubbandAdjusted; i+=2)
    {
        rgiCoef[i] = -rgiCoef[i];
    }

exit:
    return wmaResult;
}

//***************************************************************************
// Encoder/Decoder Separation
//***************************************************************************


// Start BLOCK A
// Originally from fft.c, moved to here because this is an encoder-only function

// Input shall be in complex flot format(real followed by imag). rgfltData should have size = N + 2 floats.
// On the input, (N/2 + 1) complex numbers should be filled in. On the output, only the first N outputs 
// are valid, and all of them should be considered real values. nOrder = log2(N).
// Inputs are mirror-imaged (&conjugated) internally before ifft. Never tested
// with complex inputs.
// cSizeTmp is size of rgfltTmp in Floats.
WMARESULT prvInvFftComplexConjugate(Void *ptrNotUsed, CoefType *rgfltData, Int nOrder, 
                                    CoefType *rgfltTmp,  U32 cSizeTmp)
{
    Int N = 1 << nOrder;
    Int i;
    Int iSrc2, iDst2;
        WMARESULT wmaResult = WMA_OK;

    if ((cSizeTmp < (U32)(2 * N)) ||
        (rgfltTmp == NULL || rgfltData == NULL)) 
    {
        assert( !"someone is is not using prvInvFftComplexConjugate properly." );
        wmaResult = TraceResult (WMA_E_INVALIDARG);
        goto exit;
    }
    assert(nOrder < 12);
    
    memset (rgfltTmp, 0, cSizeTmp * sizeof(Float)); 
    memcpy (rgfltTmp, rgfltData, (N + 2) * sizeof(Float));
    
    // Perform mirroring (in complex domain)
    iSrc2 = 2 * 2;
    iDst2 = N * 2;
    for (i = 0; i < (N/2)-1; i++) {
        rgfltTmp[iDst2 -2] =  rgfltTmp[iSrc2 -2]; // real
        rgfltTmp[iDst2 -1] = -rgfltTmp[iSrc2 -1]; // imag
        iSrc2 += 2;
        iDst2 -= 2;
    }
    prvFFT4DCT(ptrNotUsed, rgfltTmp, nOrder, FFT_INVERSE);
    
    // Copy back real part of the result
    for (i = 0; i < N; i++) {
        rgfltData[i] = rgfltTmp[2 * i];
    }
exit:
    return wmaResult;
}

#endif // BUILD_WMASTD || BUILD_WMAPRO
