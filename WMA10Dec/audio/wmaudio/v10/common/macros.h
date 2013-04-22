//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 2006

Module Name:

    Macros.h

Abstract:

    Processor-specific macros, defines, and data types.

Author:

    Raymond Cheng (raych)       Jul 29, 1999

Revision History:


*************************************************************************/

#ifndef __COMMON_MACROS_H
#define __COMMON_MACROS_H

//#define PRINT_STATS
//#define MCLT_MASK // compute mask using MCLT
// UES ===================================================================
// when BUILD_UES is defined, the UES related functions will be built in all places
#ifndef DISABLE_UES
#define BUILD_UES
//#define UES_DEBUG_CORE_BITS
#endif
//#define WMA_DEBUG_DUMP // dump frame based results

//#define WMA_TEST_ADJUST_NMR_DRANGE

// Freqex ================================================================

// write freqex data into reserved data in subframe header, else writes to
// private files, useful for seeing how many bits it takes for fex
//#define WRITE_PLUS_TO_FILE
#if defined(WRITE_PLUS_TO_FILE)
#define COUNT_FREQEX_BITS
#endif

#if defined(WRITE_PLUS_TO_FILE)
#include <windows.h>
extern const TCHAR *g_pCmpName;
#endif

// ***********************************************************************
// Arithmetic coding, and testing
// **********************************************************************

//#define DEFINE_ARITH_CODER

// ***********************************************************************

// #define WMA_COMPRESSION_TOOL
#ifdef WMA_COMPRESSION_TOOL
    #define WMA_COMPTOOL_NODUMPING
    //#define WMA_DEBUG_COMPRESSION_TOOL
#endif //WMA_COMPRESSION_TOOL

#define DISABLE_FOURTHFILTER

// #define AVS_TEST_MODES
#ifdef AVS_TEST_MODES
    //#define TRANSIENT_DETECT_FOURFILTERS_LOG
    // #define AVS_TEST_MODES_PRINTFRMBITS // rely on WMA_COMPRESSION_TOOL.
    #if defined(AVS_TEST_MODES_PRINTFRMBITS) && !defined(WMA_COMPRESSION_TOOL)
        #define WMA_COMPRESSION_TOOL
    #endif //AVS_TEST_MODES_PRINTFRMBITS && !WMA_COMPRESSION_TOOL
    extern g_fForceV7RateCtrlAVS;
#endif

#if defined(SCRAMBLE_GLOBAL_SYMBOL_NAMES) || defined(UNDER_CE)
#include "scramble.h"
#endif

#include "wmatypes.h"
#include "catchflops.h"

// If BUILD_INTEGER or BUILD_INT_FLOAT is not defined by project set default state

#if defined(BUILD_INTEGER) && defined(BUILD_INT_FLOAT)
#error both BUILD_INTEGER and BUILD_INT_FLOAT are defined.
#endif

//#if !defined(BUILD_INTEGER) && !defined(BUILD_INT_FLOAT)
//#error neither BUILD_INTEGER nor BUILD_INT_FLOAT are defined.
//#endif

#include "constants.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <float.h>

// always use 32 bit integer decoding
#if !defined(DISABLE_COEF64BIT)
#define DISABLE_COEF64BIT
#endif

// =====================================================================
// For PK's

#if defined(WMA_DECPK_BUILD)

#include "pkconfig.h"

#if (BUILDCFG_STD == 1)
#define BUILD_WMASTD
#elif (BUILDCFG_STDPROSTEREOLBRV1 == 1)
#define BUILD_WMASTD
#define BUILD_WMAPROLBRV1
#define BUILD_WMAPROSTEREOONLY
#elif (BUILDCFG_STDPROSTEREOLBR == 1)
#define BUILD_WMASTD
#define BUILD_WMAPROLBRV3
#define BUILD_WMAPROSTEREOONLY
#elif (BUILDCFG_STDPROLBR == 1)
#define BUILD_WMASTD
#define BUILD_WMAPROLBRV3
#elif (BUILDCFG_LSL == 1)
#define BUILD_WMALSL
#elif (BUILDCFG_ALL == 1)
#if !defined(BUILD_WMASTD)
#define BUILD_WMASTD
#endif
#if !defined(BUILD_WMAPROLBRV3)
#define BUILD_WMAPROLBRV3
#endif
#if !defined(BUILD_WMALSL)
#define BUILD_WMALSL
#endif
#else
#error "At least one build configuration must be defined (see pkconfig.h)"
#endif

// always use low power cx decoding
#if !defined(CX_LOW_POWER)
#define CX_LOW_POWER
#endif

#endif // defined(WMA_DECPK_BUILD)


// =====================================================================
// set BUILD_WMA definitions - if no specific build flags are set,
// then this section turns on all versions of WMA (std,lsl,pro,lbr)
// =====================================================================

// Note there are many combinations here for builds
// STD: Off/On (2)
// PRO: Off/PRO/LBRV1/LBRV2/LBRV3 (5)
// LSL: Off/On (2)
// This results in (2)(5)(5)-1 = 49 comb. (-1 since not all can be off).
// However, not all need to verified for builds.
#if !defined(BUILD_WMASTD) &&      \
    !defined(BUILD_WMAPRO) &&      \
    !defined(BUILD_WMAPROLBRV1) && \
    !defined(BUILD_WMAPROLBRV2) && \
    !defined(BUILD_WMAPROLBRV3) && \
    !defined(BUILD_WMALSL)      

// We must build for everything :)

// wma std
#define BUILD_WMASTD
// wma pro - max LBR version
#define BUILD_WMAPROLBRV3
// wma lsl
#define BUILD_WMALSL

// modes within pro
#define BUILD_WMAPRO_PLLM
#define BUILD_WMAPRO_RTSPDIF

#endif // !BUILD_WMASTD && !BUILD_WMAPRO && !BUILD_WMAPROLBRV1 && !BUILD_WMALSL

// LBR v3 requires LBR v2
#if defined(BUILD_WMAPROLBRV3) && !defined(BUILD_WMAPROLBRV2)
#define BUILD_WMAPROLBRV2
#endif

// LBR v2 requires LBR v1
#if defined(BUILD_WMAPROLBRV2) && !defined(BUILD_WMAPROLBRV1)
#define BUILD_WMAPROLBRV1
#endif

// LBR v1 requires PRO
#if defined(BUILD_WMAPROLBRV1) && !defined(BUILD_WMAPRO)
#define BUILD_WMAPRO
#endif

// CE does use V3 yet
#ifdef UNDER_CE
#undef BUILD_WMAPROLBRV3
#endif

// =====================================================================

// LBR v2 and above requires v4 entropy coding
#if defined (BUILD_WMAPROLBRV2)
#define USE_V4ENTCODING
#endif

#ifdef USE_V4ENTCODING
#define MAX_V4ENTTBLS (16)
#endif

// =====================================================================
// CX_LOW_POWER enables low complexity functions for "chex". This is
// the default execution path for the fixed-point implementation.
// there are 3 compile-time options used by CX_LOW_POWER: 
//
//   CX_SMALL_REVERB - this uses a smaller memory footprint
//      for the "chex" reverb filter. the larger memory footprint
//      (default) is organized in stripes, for use by SSE1 code.
//
//   CX_DCT_ONLY - this is a performance optimization, which
//      ignores the imaginary (DST) portion of the signal, and
//      uses only the DCT portion for "chex" reconstruction.
//
//   CX_DECODE_MONO - this is a memory optimization (12K), which  
//      assumes that the 2nd channel of the base-band encoding is
//      empty. this is used to remove an entire 2nd set of buffers.
//
// =====================================================================

#if (defined(BUILD_INTEGER) || defined(UNDER_CE)) && !defined(CX_LOW_POWER)
#define CX_LOW_POWER
#endif

#if defined(CX_LOW_POWER)
#define CX_SMALL_REVERB 1   // use 'smaller' reverb (little footprint)
#define CX_DCT_ONLY     1   // use only DCT signal in chex recon
#define CX_DECODE_MONO  1   // use mono base-band (saves memory)
#else
#define CX_SMALL_REVERB 0   // use 'faster' reverb (bigger footprint)
#define CX_DCT_ONLY     0   // use DST and DCT signals in chex recon
#define CX_DECODE_MONO  0   // use stereo base-band (more accurate)
#endif

// =====================================================================
// set the target
// =====================================================================

#if !defined(DISABLE_OPT) && !defined(WMA_TARGET_ANSI)
// only define a platform specific target if we are optimizing for it.

#ifdef _M_IX86
#define WMA_TARGET_X86
#endif //_M_IX86

#ifdef _MIPS_
#define WMA_TARGET_MIPS
#endif

#if defined(_SH3_) && !defined(_SH4_)
#define WMA_TARGET_SH3
#endif

#ifdef _SH4_
#define WMA_TARGET_SH4
#endif

#ifdef _Embedded_x86
#define WMA_TARGET_Embedded_x86
#endif

#ifdef S_SUNOS5
#define WMA_TARGET_S_SUNOS5
#endif

#if defined(_ARM_) || defined(__arm)
#define WMA_TARGET_ARM
#endif

#endif // !DISABLE_OPT && !WMA_TARGET_ANSI

// =====================================================================

#undef  LITTLE_ENDIAN
#undef  BIG_ENDIAN

//first disable Intel FFT for everyone; whoever 
// needs to undef in their platform specific secion
#if !defined (DISABLE_INTELFFT)
#define DISABLE_INTELFFT
#endif

//off by default; whoever needs to undef in their platform specific secion
#define WMA_DISABLE_MMX
#define WMA_DISABLE_SSE1
#undef USE_SIN_COS_TABLES //don't use it for now

#if defined(__arm)
#define EMBEDDED_ARM
#else
#undef EMBEDDED_ARM
#endif

//Satisfy ARMulator ROPI (Read-Only Position-Independent) requirement
#ifndef __arm
#   define ROPI_CONST const
#else
#   define ROPI_CONST
#endif


// ======================================================
// Intel x86 Platform
// ======================================================
#if defined(WMA_TARGET_X86) && !defined (DISABLE_OPT)
#define LITTLE_ENDIAN
// Override the macros below
#define PLATFORM_SPECIFIC_ROUND
#define PLATFORM_SPECIFIC_DIVI64BYU32
#define PLATFORM_SPECIFIC_CEILOFLOG2
#define PLATFORM_SPECIFIC_FNPTR //mmx, katmai

#if !defined(BUILD_INTEGER)
//turn on INTELFFT for X86
#ifdef DISABLE_INTELFFT //remove redef error if specified in the build cmd line
#undef DISABLE_INTELFFT
#endif
#undef WMA_DISABLE_MMX
#undef WMA_DISABLE_SSE1
// Turn On/Off MMX/SSE1/SSE2 optimizations
#ifdef UNDER_CE
// Macallan (CE 500) compiler support MMX/SSE1. Version lower than 500 doesn't support SSE1/SSE2.
#if UNDER_CE<500
#define WMA_DISABLE_SSE1
#define DISABLE_INTELFFT
#endif //UNDER_CE<500
#endif //UNDER_CE
#endif //!(BUILD_INTEGER)

#if defined (WMA_ANSI_COMPATIBILITY_MODE)
#undef PLATFORM_SPECIFIC_ROUND
#undef PLATFORM_SPECIFIC_DIVI64BYU32
#undef PLATFORM_SPECIFIC_CEILOFLOG2
#endif // WMA_ANSI_COMPATIBILITY_MODE

// ======================================================
// Win64 Platform (potentially we need to spilt IA64/AMD64)
// ======================================================
#elif defined(WMA_TARGET_WIN64) && !defined (DISABLE_OPT)
#define LITTLE_ENDIAN
//turn on INTELFFT 
#ifdef DISABLE_INTELFFT //remove redef error if specified in the build cmd line
#undef DISABLE_INTELFFT
#endif
#undef WMA_DISABLE_SSE1
#if defined(BUILD_INTEGER)
#define DISABLE_INTELFFT // integer build is not compatible with intelFFT.
#endif 

// ======================================================
// Solaris
// ======================================================
#elif defined(WMA_TARGET_S_SUNOS5) && !defined (DISABLE_OPT)
#define BIG_ENDIAN

// ======================================================
//MacOS Platform
// ======================================================
#elif defined(WMA_TARGET_MACOS) && !defined (DISABLE_OPT)
#define BIG_ENDIAN
#include <stdint.h>

// ======================================================
// XBOX2 - Xenon Platform
// ======================================================
#elif defined(_XBOX)
#define BIG_ENDIAN

#elif defined(WMA_TARGET_SH4)
#define LITTLE_ENDIAN
// ======================================================
// ANSI-C version (no platform-specific details
// ======================================================
#else // assume little-endian ANSI platform
#define LITTLE_ENDIAN
#ifndef DISABLE_OPT
#define DISABLE_OPT
#endif
#endif // Platform-specific #ifdefs

#if defined(WMA_TARGET_ANSI)
#if !defined (DISABLE_INTELFFT)
#define DISABLE_INTELFFT
#endif
#endif//WMA_TARGET_ANSI


#include "wmatyps.h"
#include "wmaerror.h"
#include "wmaassert.h"
#include "wmaresults.h"

#ifndef WMAB_TRUE 
#define WMAB_TRUE 1
#endif //WMAB_TRUE 
#ifndef WMAB_FALSE 
#define WMAB_FALSE 0
#endif //WMAB_FALSE 

#define own // used as "reserved word" to indicate ownership or transfer to distinguish from const


//***************************************************************************
// 24-bit Encoding
//***************************************************************************

#define PCMSAMPLE_MAX(iValidBits)   ((1 << ((iValidBits) - 1)) - 1)
#define PCMSAMPLE_MIN(iValidBits)   (~((1 << ((iValidBits) - 1)) - 1))

typedef I32 PCMSAMPLE;
#define PCMSAMPLE_BITS  32

#define I24_MIN     ((I32)0xFF800000)
#define I24_MAX     ((I32)0x007FFFFF)
#define I2024_MIN   ((I32)0xFFF80000)
#define I2024_MAX   ((I32)0x0007FFFF)
#define I25_MIN     ((I32)0xFF000000)
#define I25_MAX     ((I32)0x00FFFFFF)
#define I2025_MIN   ((I32)0xFFF00000)
#define I2025_MAX   ((I32)0x000FFFFF)

#define I32_MIN ((I32)0x80000000)

// **************************************************************************
// Overridable Compiler Directives
// **************************************************************************

#ifndef PLATFORM_SPECIFIC_COMPILER_MESSAGE
#define COMPILER_MESSAGE(x)         message(x)
#endif

#ifndef PLATFORM_SPECIFIC_COMPILER_PACKALIGN
#define COMPILER_PACKALIGN(x)       pack(x)
#endif

#ifndef PLATFORM_SPECIFIC_COMPILER_PACKALIGN_DEFAULT
#define COMPILER_PACKALIGN_DEFAULT  pack()
#endif

#ifdef _MSC_VER
#define MSVC_DISABLE_WARNING(x)     warning(disable:x)
#define MSVC_RESTORE_WARNING(x)     warning(default:x)
#define MSVC_CDECL                  __cdecl
#else   // _MSC_VER
// I'm hoping that compilers can take an empty #pragma (VC can)
#define MSVC_DISABLE_WARNING(x)
#define MSVC_RESTORE_WARNING(x)
#define MSVC_CDECL
#endif  // _MSC_VER

// **************************************************************************
// Macros Common to All Platforms
// **************************************************************************
// If you need to override the following for just one platform, #define a
// switch to override as in the case for ROUNDF/ROUNDD above in the
// platform-specific #ifdefs so that it is plain to see.

#define INT_ABS( f ) ((*(const U32*)&(f))&0x7fffffff)

#define MULT_HI(a,b) (MULT_HI_DWORD(a,b)<<1)

#ifndef BUILD_INTEGER
    // these macros are not used by integer decoder. 
    // Where/when needed, provide cpu depended optimized versions as well as these generic ones.
#   define UMASR(a,b,c) (U32)((((U64)(a)*((U64)(b)))>>(c))
#   define MASR(a,b,c)  (I32)((((I64)(a)*((I64)(b)))>>(c))
#   define DASR(a,b,c)  (I32)((((I64)(a)*((I64)(b)))>>(c))
#   define DASL(a,b,c)  (I32)((((I64)(a)*((I64)(b)))<<(c))

    // The following macro has no perf-enhanced equivalents, although one can
    // easily be written a la x86 MULT_HI_DWORD:
    // I32HI,LOW = a*b; if (I32LOW & 0x80000000) I32HI += 1; return I32HI;
    // NOTE that it only rounds UP, and does not consider negative numbers.
#   define MULT_HI_DWORD_ROUND(a,b)    (I32)((((I64)(a))*((I64)(b)) + ((I64)1 << 31))>>32)
#endif

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define checkRange(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))
#define DELETE_ARRAY(ptr) if (ptr!=NULL) { auFree (ptr); ptr = NULL;}
#define DELETE_PTR(ptr) if (ptr!=NULL) {auFree (ptr); ptr = NULL;}
#define ARRAY_SIZE(ar) (sizeof(ar)/sizeof((ar)[0]))
#define CHECK_POWER_OF_TWO(x) ((((x)-1) & (x)) == 0)

#  ifdef DEBUG_ONLY
// WCE already has this macro defined in the same way, avoid warning messages
#  undef DEBUG_ONLY
#  endif
#ifdef _DEBUG
#define DEBUG_ONLY(x)   x
#else   // _DEBUG
#define DEBUG_ONLY(x)
#endif  // _DEBUG

#if defined(LITTLE_ENDIAN)
#define DEFAULTENDIAN_TO_BIGENDIAN(i)   ByteSwap(i)
#define BIGENDIAN_TO_DEFAULTENDIAN(i)   ByteSwap(i)
#elif defined(BIG_ENDIAN)
#define DEFAULTENDIAN_TO_BIGENDIAN(i)   (i)
#define BIGENDIAN_TO_DEFAULTENDIAN(i)   (i)
#else
#error Must define the endian of the target platform
#endif // ENDIAN

#define SWAP_WORD( w )      (w) = ((w) << 8) | ((w) >> 8)

#define SWAP_DWORD( dw )    (dw) = ((dw) << 24) | ( ((dw) & 0xFF00) << 8 ) | ( ((dw) & 0xFF0000) >> 8 ) | ( ((dw) & 0xFF000000) >> 24);

// WMARESULT macros (stolen from winerror.h)
#ifndef WMA_SUCCEEDED
#define WMA_SUCCEEDED(Status) ((WMARESULT)(Status) >= 0)
#endif //WMA_SUCCEEDED
#ifndef WMA_FAILED
#define WMA_FAILED(Status) ((WMARESULT)(Status)<0)
#endif //WMA_FAILED

// Use 64-bit buffers in integer build to get better match in int vs. intfloat
//
// When building desktop reference decoders COEF64BIT is defined.  This alone can cause 
// significant enough differences between the platform decoders and the reference decoders
// that the platform decoders can appear to not pass QL1.  --  a-dutchm

#if defined(BUILD_INTEGER) && defined(BUILD_WMAPRO) && !defined(UNDER_CE) && !defined(__arm) && !defined(DISABLE_COEF64BIT)
#define COEF64BIT
#define RECALC_SINCOS
#else
#undef COEF64BIT
#endif

// Use integer calculations when calculating inverse channel transform matrix
#define FLOAT_INT_CHXFORM

#ifdef COEF64BIT
//#define HIGHBIT_CH
//#define HIGHBIT_IQ
#define HIGHBIT_FFT
#else
#undef HIGHBIT_CH
#undef HIGHBIT_IQ
#undef HIGHBIT_FFT
#endif

#if defined(BUILD_WMAPROLBRV1)
#   if defined(BUILD_INTEGER)
        typedef I32 FexType;
#       define FEXT_BITS 27
#       define FEXT_FROM_FLOAT( x ) (FexType)((x)*(1<<FEXT_BITS))
#       define FLOAT_FROM_FEXT( x ) ((Float)(x)/(1<<FEXT_BITS))
#   else
        typedef Float FexType;
#       define FEXT_BITS 0
#       define FEXT_FROM_FLOAT( x ) (FexType)(x)
#       define FLOAT_FROM_FEXT( x ) (Float)(x)
#   endif
#endif

#if defined(BUILD_INTEGER) // already integer calcs
#undef FLOAT_INT_CHXFORM
#elif defined(BUILD_INT_FLOAT) // float cannont support 64 bit buffers
#undef COEF64BIT
#else // assume it is floating build, unless otherwise specified.
#undef COEF64BIT
#error "At least one of BUILD_INTEGER or BUILD_INT_FLOAT must be defined."
#endif

#ifdef COEF64BIT
typedef I64 CBT;
#else
typedef Int CBT;
#endif

#ifdef COEF64BIT
// a is guaranteed to be less than 40 bits.
INLINE I64 multHi64(I64 a, I32 b, Int bits)
{
  if (bits <= 32) {
    if (a > 0)
      return ((((a & 0xffffffff)*b)>>bits) + (((a>>32)*b)<<(32-bits)));
    else {
      a = -a;
      return -((((a & 0xffffffff)*b)>>bits) + (((a>>32)*b)<<(32-bits)));
    }
  } else {
    if (a > 0)
      return ((((a & 0xffffffff)*b)>>bits) + (((a>>32)*b)>>(bits-32)));
    else {
      a = -a;
      return -((((a & 0xffffffff)*b)>>bits) + (((a>>32)*b)>>(bits-32)));
    }
  }
}
INLINE I64 multHi64B31(I64 a, I32 b)
{
#if 0 // non-branching versions of the above for 30, 31 bits
  U64 r;
  U64 s = a >> 63;
  a = (a^s)-s;
  r = ((((a & 0xffffffff)*b)>>31) + (((a>>32)*b)<<1));
  return (r^s)-s;
#else
  if (a > 0)
    return ((((a & 0xffffffff)*b)>>31) + (((a>>32)*b)<<1));
  else {
    a = -a;
    return -((((a & 0xffffffff)*b)>>31) + (((a>>32)*b)<<1));
  }
#endif
}
INLINE I64 multHi64B30(I64 a, I32 b)
{
#if 0
  U64 r;
  U64 s = a >> 63;
  a = (a^s)-s;
  r = ((((a & 0xffffffff)*b)>>30) + (((a>>32)*b)<<2));
  return (r^s)-s;
#else
  if (a > 0)
    return ((((a & 0xffffffff)*b)>>30) + (((a>>32)*b)<<2));
  else {
    a = -a;
    return -((((a & 0xffffffff)*b)>>30) + (((a>>32)*b)<<2));
  }
#endif
}
#endif

INLINE I32 wmaiiround2toN(const I32 x, const I32 N) {
  return x >= 0 ? (x+(1<<N>>1)) & ~((1<<N)-1) : (x-1+(1<<N>>1)) & ~((1<<N)-1);
}

#define IFLOOR(x, N) (((x)>=0) ? (x)/(N)            : ((x)-(N)+1)/(N)   )
#define  ICEIL(x, N) (((x)>=0) ? ((x)+(N)-1)/(N)    : (x)/(N)           )
#define IROUND(x, N) (((x)>=0) ? ((x)+((N)>>1))/(N) : ((x)-((N)>>1))/(N))

#define IPFLOOR(x, N) ((x)/(N))
#define  IPCEIL(x, N) (((x)+(N)-1)/(N))
#define IPROUND(x, N) (((x)+((N)>>1))/(N))

// Create types which are change implementation between BUILD_INTEGER and BUILD_INT_FLOAT
// Some platforms, like the X86 and the SH4, can implement either build efficently.
// Other platforms, with only emulated floating point support, are typically only build with BUILD_INTEGER
//  
// Each type defined below is either a float (BUILD_INT_FLOAT) and an I32 with some number of fractional bits (BUILD_INTEGER)
// Use float or and I32 with five fractional bits
// And create a type for trig functions (Float or I32 with 30 fractional bits)

#define FLOAT_FROM_FRAC(a, bits) ((a)/((Float)(((I64)1<<(bits)))))
#define FRAC_FROM_FLOAT(a, bits) ((I32)((a)*(Float)(((I64)1<<(bits)))))

#define MULT_HI32_SHIFT(a, b, bits) ((I32)(((I64)(a)*(I64)(b))>>bits))

#if defined(BUILD_INTEGER)

// Coefficents type (output of inverse quantization, transformed by DCT and overlapped/added)
// Range is +/- 2^26 with five fractional bits
#ifdef COEF64BIT
    typedef I64 CoefType;
#   define ABS_COEF(a) (((a)<0)?-(a):(a))
#else
    typedef I32 CoefType;
#   define ABS_COEF(a) abs(a)
#endif
#   define COEF_FRAC_BITS TRANSFORM_FRACT_BITS // == 5
#   define COEF_FRAC_SCALE (1<<COEF_FRAC_BITS)
#   define COEF_FROM_FLOAT(flt) ((CoefType)((flt)*COEF_FRAC_SCALE))//; assert( I32_MAX > (flt)*COEF_FRAC_SCALE )
#   define FLOAT_FROM_COEF(coef) (((Float)(coef))/COEF_FRAC_SCALE)
#   define COEF_FROM_INT(i) (CoefType)((i)<<pau->m_cLeftShiftBitsFixedPre)
#   define INT_FROM_COEF(cf) ((cf)>>pau->m_cLeftShiftBitsFixedPost)
#   define PCMSAMPLE_TO_COEFTYPE(pcm) ((pcm)<<TRANSFORM_FRACT_BITS)

#   define SINSTEP_SCALE(a) (a)

#   define FRAC_FROM_RATIO(a, b, bits) (DIVI64BYU32((I64)(a)<<(bits), (b)))

// bits-per-sample type
    typedef U32 BPSType;
#   define WBPS_BITS 27
#   define WBPS(x) (U32)((x)*(1<<WBPS_BITS))
#   define FLOAT_FROM_WBPS(x) ((Float)(x)/(1<<WBPS_BITS))

// Fractional Type with range -2.0 <= x < 2.0 used by FFT Trig Recurrsion 
    typedef I32 BP2Type;
#   define BP2_FRAC_BITS 30
#   define BP2_FRAC_SCALE NF2BP2
#   define BP2_FROM_FLOAT(flt) ((BP2Type)((flt)*BP2_FRAC_SCALE))
#   define BP2_FROM_FLOAT_R(flt) ((BP2Type)((flt >= 0)?((flt) * 0x40000000 + 0.5) : ((flt) * 0x40000000 - 0.5)))
#   define FLOAT_FROM_BP2(bp2) ((bp2)/((Float)BP2_FRAC_SCALE))
#   define BP2_FROM_BP1(bp1) ((bp1)>>1)
#ifdef COEF64BIT
#   define MULT_BP2(a,b) ((I32) (((a) * (I64) (b)) >> BP2_FRAC_BITS))
#else
    // some 32-bit implementations of MULT_HI_DWORD_DOWN implement (((I32)(a*(I64)b))>>32)<<2 for performance but it is inaccurate
#   define MULT_BP2(a,b) MULT_HI_DWORD_DOWN((a),(b))
#endif
#   define MULT_BP2_I32(a,b) ((I32) (((a) * (I64) (b)) >> BP2_FRAC_BITS))
#   ifdef FUSED_MUL_ADD
#       define MULT_ADD2_BP2(a,b,c,d) ((I32)((((a) * (I64)(b)) + ((c) * (I64)(d))) >> BP2_FRAC_BITS))
#       define MULT_ADD4_BP1(a,b,c,d,e,f,g,h) ((I32)((((a) * (I64)(b)) + ((c) * (I64)(d)) + (((e) * (I64)(f)) + ((g) * (I64)(h))) >> BP1_FRAC_BITS))
#   else // FUSED_MUL_ADD
#       define MULT_ADD2_BP2(a,b,c,d) (MULT_BP2(a,b) + MULT_BP2(c,d))
#       define MULT_ADD4_BP1(a,b,c,d,e,f,g,h) (MULT_BP1(a,b) + MULT_BP1(c,d) + MULT_BP1(e,f) + MULT_BP1(g,h))
#   endif // FUSED_MUL_ADD

#	define MAC2_BP2(a, b, c, d) \
		((I32)(((I64)(a)*(I64)(b) + (I64)(c)*(I64)(d)) >> BP2_FRAC_BITS))

// Fractional Type with range -2.0 <= x < 2.0 used by FFT Trig Recurrsion using I64 values and addition but 32*32=>64 multiplication
    typedef I64 XBP2Type;
#   define XBP2_FRAC_BITS 62
#   define XBP2_FRAC_SCALE 0x4000000000000000i64
#   define BP2_XBP2_CONVFACT  (XBP2_FRAC_SCALE/(I64)(NF2BP2)) // 0x100000000
#   define XBP2_FROM_FLOAT(flt) ((XBP2Type)((flt)*XBP2_FRAC_SCALE))
#   define FLOAT_FROM_XBP2(bp2) ((bp2)/((double)XBP2_FRAC_SCALE))
#   define BP2_FROM_XBP2(xbp2) ((BP2Type)((xbp2)>>32))
#   define XBP2_FROM_BP2(bp2) ((XBP2Type)(bp2 * BP2_XBP2_CONVFACT))
#   define XBP2_FROM_BP1(bp1) ((XBP2Type)(BP2_FROM_BP1(bp1) * BP2_XBP2_CONVFACT))
// some 32-bit implementations of MULT_HI_DWORD_DOWN implement (((I32)(a*(I64)b))>>32)<<2 for performance but it is inaccurate
//#   define MULT_XBP2(a,b) ((((XBP2Type)BP2_FROM_XBP2(a)) * ((XBP2Type)BP2_FROM_XBP2(b)))<<2)	// 1.8 eps max error
//#   define MULT_XBP2(a,b) ( ((XBP2Type)((a)>>31)) * ((XBP2Type)((b)>>31)) )  // very good for fft recursion, 0.61 eps max error.
// this is the fastest 64-bit versions to implement on a 32-bit RISC machine such as ARM.
#   define MULT_XBP2(a,b) ( ((XBP2Type)(((a)>>32))<<1) * (((XBP2Type)((b)>>32))<<1) )	// less good for the FFT, 1.44 eps max error


// Fractional type with range -1.0 <= x < 1.0 used by DCT Trig Recurrsion
    typedef I32 BP1Type;
#   define BP1_FRAC_BITS 31
#   define BP1_FRAC_SCALE NF2BP1
#   define BP1_FROM_FLOAT(flt) ((BP1Type)(flt*BP1_FRAC_SCALE))
#   define FLOAT_FROM_BP1(bp1) (bp1/((Float)BP1_FRAC_SCALE))
#   define MULT_BP1(a,b) MULT_HI((a),(b))
#   ifdef FUSED_MUL_ADD
#       define MULT_ADD2_BP1(a,b,c,d) ((I32)((((a) * (I64)(b)) + ((c) * (I64)(d))) >> BP1_FRAC_BITS))
#   else // FUSED_MUL_ADD
#       define MULT_ADD2_BP1(a,b,c,d) (MULT_BP1(a,b) + MULT_BP1(c,d))
#   endif // FUSED_MUL_ADD
    
// Fractional Type with range -1.0 <= x < 1.0 used by DCT Trig Recurrsion using I64 values and addition but 32*32=>64 multiplication
    typedef I64 XBP1Type;
#   define XBP1_FRAC_BITS 63
#   define XBP1_FRAC_SCALE (((1i64<<DBL_MANT_DIG)-1)<<(63-DBL_MANT_DIG))  // 0x7FFFFFFFFFFFFFFFi64
#   define XBP1_FROM_FLOAT(flt) ((XBP1Type)((flt)*XBP1_FRAC_SCALE))
#   define FLOAT_FROM_XBP1(xbp1) ((xbp1)/((double)XBP1_FRAC_SCALE))
#   define BP1_FROM_XBP1(xbp1) ((BP1Type)((xbp1)>>32))
#   define XBP1_FROM_BP1(bp1) (((XBP1Type)(bp1))<<32)
// some 32-bit implementations of MULT_HI_DWORD_DOWN implement (((I32)(a*(I64)b))>>32)<<2 for performance but it is inaccurate
//#   define MULT_XBP1(a,b) ((((XBP1Type)BP1_FROM_XBP1(a)) * ((XBP1Type)BP1_FROM_XBP1(b)))<<1)	
//#   define MULT_XBP1(a,b) ( ((XBP1Type)(((a)>>31))) * ((XBP1Type)((b)>>32)) )
// this is the fastest 64-bit versions to implement on a 32-bit RISC machine such as ARM.
#   define MULT_XBP1(a,b) ( ((XBP1Type)(((a)>>32))<<1) * ((XBP1Type)((b)>>32)) )

#   define MAX40BITVAL ((I64)0xfffffffff0)
#   define LOG2MAX40BITVAL (39)
#   define MAX32BITVAL ((I32)0x7ffffff0)
#   define LOG2MAX32BITVAL (30)

#ifdef HIGHBIT_FFT
#   define MAXINTVAL_FFT MAX40BITVAL
#   define MAXINTVAL_FFT_LOG2 (LOG2MAX40BITVAL)  //LOG2_64(MAXINTVAL_FFT)
#   define MULT_CBP2(a,b) (multHi64B30((b), (a)))
#   define MULT_CBP1(a,b) (multHi64B31((b), (a)))
#   define MULT_ADD2_CBP2(a,b,c,d) (MULT_CBP2(a,b) + MULT_CBP2(c,d))
#   define MULT_ADD2_CBP1(a,b,c,d) (MULT_CBP1(a,b) + MULT_CBP1(c,d))
#   define MULT_ADD4_CBP1(a,b,c,d,e,f,g,h) (MULT_CBP1(a,b) + MULT_CBP1(c,d) + MULT_CBP1(e,f) + MULT_CBP1(g,h))
#else
#   define MAXINTVAL_FFT MAX32BITVAL
#   define MAXINTVAL_FFT_LOG2 (LOG2MAX32BITVAL)  //LOG2(MAXINTVAL_FFT)
#   define MULT_CBP2(a,b) MULT_BP2(a,b)
#   define MULT_CBP1(a,b) MULT_BP1(a,b)
#   ifdef FUSED_MUL_ADD
#       define MULT_ADD2_CBP2(a,b,c,d) MULT_ADD2_BP2(a,b,c,d)
#       define MULT_ADD2_CBP1(a,b,c,d) MULT_ADD2_BP1(a,b,c,d)
#       define MULT_ADD4_CBP1(a,b,c,d,e,f,g,h) MULT_ADD4_BP1(a,b,c,d,e,f,g,h)
#   else
#       define MULT_ADD2_CBP2(a,b,c,d) (MULT_CBP2(a,b) + MULT_CBP2(c,d))
#       define MULT_ADD2_CBP1(a,b,c,d) (MULT_CBP1(a,b) + MULT_CBP1(c,d))
#       define MULT_ADD4_CBP1(a,b,c,d,e,f,g,h) (MULT_CBP1(a,b) + MULT_CBP1(c,d) + MULT_CBP1(e,f) + MULT_CBP1(g,h))
#   endif
#endif

// Channel transform
    typedef I32 ChXFormType;
#   define CH_FRAC_BITS (30)
#ifdef HIGHBIT_CH
#   define MAXINTVAL_CH MAX40BITVAL
#   define MAXINTVAL_CH_LOG2 (LOG2MAX40BITVAL)   //LOG2_64(MAXINTVAL_CH)
#   define MULT_CH(a,b) (multHi64(b, a, CH_FRAC_BITS))
#   define MULT_CH_SQRT2(a) (multHi64((a), INT_SQRT2, INT_SQRT2_BITS))
#else
#   define MAXINTVAL_CH MAX32BITVAL
#   define MAXINTVAL_CH_LOG2 (LOG2MAX32BITVAL)   //LOG2(MAXINTVAL_CH)
#   define MULT_CH(a,b) MULT_HI32_SHIFT(b, a, CH_FRAC_BITS)
#   define MULT_CH_SQRT2(a) MULT_HI32_SHIFT(a, INT_SQRT2, INT_SQRT2_BITS)
#endif
#   define MULT_CH_MATRIX(a,b) MULT_HI32_SHIFT(a, b, CH_FRAC_BITS)
#   define CH_FROM_FLOAT(flt) FRAC_FROM_FLOAT(flt, CH_FRAC_BITS)
#   define FLOAT_FROM_CH(ch) FLOAT_FROM_FRAC(ch, CH_FRAC_BITS)
#   define ROUND_CH_TO_2TON(x, N) (((N) >= CH_FRAC_BITS) ? (x) : wmaiiround2toN(x, CH_FRAC_BITS-N))

    typedef ChXFormType ChXFormMType;
#   define CHM_FROM_FLOAT(flt) CH_FROM_FLOAT(flt)
#   define FLOAT_FORM_CHM(ch) FLOAT_FROM_CH(ch)

    typedef I32 ChPPXFormType;
#   define CHPP_FRAC_BITS (30)
#   define MULT_CHPP(a,b) MULT_HI32_SHIFT(a, b, CHPP_FRAC_BITS)
#   define CHPP_FROM_FLOAT(flt) FRAC_FROM_FLOAT(flt, CHPP_FRAC_BITS)

    typedef I32 ChPPXFormType2;
#   define CHPP2_FRAC_BITS (5)
#   define CHPP2_FROM_INT(i) (i<<CHPP2_FRAC_BITS)
#   define INT_FROM_CHPP2(i) (i>>CHPP2_FRAC_BITS)

// Downmix transform
    typedef I32 ChDnMixType;
#   define CHDN_FRAC_BITS (23)
#   define MULT_CHDN(a,b) MULT_HI32_SHIFT(a, b, CHDN_FRAC_BITS)
#   define CHDN_FROM_FLOAT(flt) FRAC_FROM_FLOAT(flt, CHDN_FRAC_BITS)

// Half transform for mllm
    typedef I32 HTFilterType;
#   define HTFT_FRAC_BITS (28)
#   define MULT_HTFT(a,b) MULT_HI32_SHIFT(a, b, HTFT_FRAC_BITS)
#   define HTFT_FROM_FLOAT(flt) FRAC_FROM_FLOAT(flt, HTFT_FRAC_BITS)


// fix-point binary points conversion factors
// convert float or double to BP1 integer ( -1.0 <= x < +1.0 )
#define NF2BP1 0x7FFFFFFF
// convert float or double to BP2 integer ( -2.0 <= x < +2.0 )
#define NF2BP2 0x40000000

// Fraction is stored at 2^32 (BP0)
#define UBP0_FROM_FLOAT(x) ((U32)(x*4294967296.0F))

    typedef I32 FracBitsType;
    typedef struct {
    //I8 exponent;  Old exponent was shift from binary point at 24th position
        FracBitsType iFracBits;
        I32 iFraction;
    } FastFloat;

// Type for holding quantization magnitide returned by prvWeightedQuantization
    typedef FastFloat QuantFloat;

    // Some utility functions with obvious meaning
#   define DIV2(a) ((a)>>1)
#   define MUL2(a) ((a)<<1)
#   define DIV4(a) ((a)>>2)
#   define MUL4(a) ((a)<<2)
#   define MUL8(a) ((a)<<3)

#   define INTEGER_ONLY(a) a
#   define INTEGER_OR_INT_FLOAT(a,b) a

#define MULT_SQRT2(a) (I32)(((I64)(a) * INT_SQRT2) >> INT_SQRT2_BITS)

#else // ************ so must be BUILD_INT_FLOAT *****************

// transient detection type

// Coefficents type (output of inverse quantization, transformed by DCT and overlapped/added)
    typedef Float CoefType;
#   define COEF_FRAC_BITS 0
#   define COEF_FRAC_SCALE 1
#   define COEF_FROM_FLOAT(flt)  (CoefType)(flt)
#   define FLOAT_FROM_COEF(coef) (Float)(coef)
#   define COEF_FROM_INT(i) (CoefType)(i)
#   define INT_FROM_COEF(cf) (cf)

#   define PCMSAMPLE_TO_COEFTYPE(pcm) (pcm)
#   define ABS_COEF(a) (Float)fabs(a)
#   define SINSTEP_SCALE(a) (2.0F * (a))

INLINE void FLOATS_FROM_COEFS( void *p, int n ){}
INLINE void COEFS_FROM_FLOATS( void *p, int n ){}

#   define FRAC_FROM_RATIO(a, b, bits) ((a)/(b))

// bit-per-sample type
    typedef Float BPSType;
#   define WBPS(x) (x)
#   define FLOAT_FROM_WBPS(x) (x)

// Fractional Type used by FFT Trig Recurrsion 
    typedef Float BP2Type;
#   define BP2_FRAC_BITS 0
#   define BP2_FRAC_SCALE 1
#   define BP2_FROM_FLOAT(flt) ((BP2Type)(flt))
#   define BP2_FROM_FLOAT_R(flt) ((BP2Type)(flt))
#   define FLOAT_FROM_BP2(bp2) ((Float)(bp2))
#   define BP2_FROM_BP1(bp1) (bp1)
#   define MULT_BP2(a,b) ((a)*(b))
#   define MULT_BP2_I32(a,b) ((a) * (b))
#   define MULT_ADD2_BP2(a,b,c,d) (MULT_BP2(a,b) + MULT_BP2(c,d))

// Fractional Type used by FFT Trig Recurrsion with 64 bit precision
    typedef Double XBP2Type;
#   define XBP2_FRAC_BITS 0
#   define XBP2_FRAC_SCALE 1
#   define XBP2_FROM_FLOAT(flt) ((XBP2Type)(flt))
#   define FLOAT_FROM_XBP2(xbp2) ((double)(xbp2))
#   define BP2_FROM_XBP2(xbp2) ((BP2Type)(xbp2))
#   define XBP2_FROM_BP2(bp2)((XBP2Type)(bp2))
#   define XBP2_FROM_BP1(bp1) (XBP2_FROM_BP2(BP2_FROM_BP1(bp1)))
#   define MULT_XBP2(a,b) ((a)*(b))

// Fractional type used by DCT Trig Recurrsion
    typedef Float BP1Type;
#   define BP1_FRAC_BITS 0
#   define BP1_FRAC_SCALE 1
#   define BP1_FROM_FLOAT(flt) ((BP1Type)(flt))
#   define FLOAT_FROM_BP1(bp1) ((Float)(bp1))
#   define MULT_BP1(a,b) ((a)*(b))
#   define MULT_ADD2_BP1(a,b,c,d) (MULT_BP1(a,b) + MULT_BP1(c,d))
#   define MULT_ADD2_CBP2(a,b,c,d) (MULT_CBP2(a,b) + MULT_CBP2(c,d))
#   define MULT_ADD2_CBP1(a,b,c,d) (MULT_CBP1(a,b) + MULT_CBP1(c,d))
#   define MULT_ADD4_CBP1(a,b,c,d,e,f,g,h) (MULT_CBP1(a,b) + MULT_CBP1(c,d) + MULT_CBP1(e,f) + MULT_CBP1(g,h))

    typedef Double XBP1Type;
#   define XBP1_FRAC_BITS 0
#   define XBP1_FRAC_SCALE 1
#   define XBP1_FROM_FLOAT(flt) ((XBP1Type)(flt))
#   define FLOAT_FROM_XBP1(xbp1) ((double)(xbp1))
#   define BP1_FROM_XBP1(xbp1) ((BP1Type)(xbp1))
#   define XBP1_FROM_BP1(bp1) ((XBP1Type)(bp1))
#   define MULT_XBP1(a,b) ((a)*(b))
#   define MULT_XBP1_BP1(bp1,xbp1) ((XBP1_FROM_BP1(bp1) * xbp1))
     
// Calculation of output of channel transform
#define CH_FRAC_BITS (30)
    typedef Float ChXFormType;
#   define MULT_CH(a,b) ((a)*(b))
#   define MULT_CH_SQRT2(a) ((a) * (FLT_SQRT2))
#   define CH_FROM_FLOAT(flt) (flt)
#   define FLOAT_FROM_CH(ch) (ch)

// Channel transform
#ifdef FLOAT_INT_CHXFORM
    typedef I32 ChXFormMType;
#   define MULT_CH_MATRIX(a,b) MULT_HI32_SHIFT(a, b, CH_FRAC_BITS)
#   define ROUND_CH_TO_2TON(x, N) (((N) >= CH_FRAC_BITS) ? (x) : wmaiiround2toN(x, CH_FRAC_BITS-N))
#   define CHM_FROM_FLOAT(flt) FRAC_FROM_FLOAT(flt, CH_FRAC_BITS)
#   define FLOAT_FROM_CHM(ch) FLOAT_FROM_FRAC(ch, CH_FRAC_BITS)
#else
    typedef ChXFormType ChXFormMType;
#   define MULT_CH_MATRIX(a,b) ((a)*(b))
#   define ROUND_CH_TO_2TON(x, N) (ROUNDF((x)*(Float)(1<<(N))) / (Float)(1<<(N)))
#   define CHM_FROM_FLOAT(flt) (flt)
#   define FLOAT_FROM_CHM(ch) (ch)
#endif

    typedef Float ChPPXFormType;
#   define MULT_CHPP(a,b) ((a)*(b))
#   define CHPP_FROM_FLOAT(flt) (flt)

    typedef I32 ChPPXFormType2;
#   define CHPP2_FRAC_BITS (5)
#   define CHPP2_FROM_INT(i) (i)
#   define INT_FROM_CHPP2(i) (i)

// Downmix transform
    typedef Float ChDnMixType;
#   define MULT_CHDN(a,b) ((a)*(b))
#   define CHDN_FROM_FLOAT(flt) (flt)

// Half transform for mllm
    typedef Float HTFilterType;
#   define MULT_HTFT(a,b) ((a)*(b))
#   define HTFT_FROM_FLOAT(flt) (flt)

#   define MULT_CBP1(a,b) MULT_BP1(a,b)
#   define MULT_CBP2(a,b) MULT_BP2(a,b)

// fix-point binary points conversion factors
// convert float or double to BP1 integer ( -1.0 <= x < +1.0 )
#define NF2BP1 2
// convert float or double to BP2 integer ( -2.0 <= x < +2.0 )
#define NF2BP2 1

// Another form of floating point 
    typedef Float FastFloat;

// Type for holding quantization magnitide returned by prvWeightedQuantization
    typedef Float QuantFloat;

// Some utility functions with obvious meaning
#   define DIV2(a) ((a)*0.5f)
#   define MUL2(a) ((a)*2.0f)
#   define DIV4(a) ((a)*0.25f)
#   define MUL4(a) ((a)*4.0f)
#   define MUL8(a) ((a)*8.0f)

#   define INTEGER_ONLY(a)
#   define INTEGER_OR_INT_FLOAT(a,b) b

#define MULT_SQRT2(a) ((a) * (FLT_SQRT2))

#endif  // either BUILD_INTEGER or BUILD_INT_FLOAT


//Trig Recursion Type
#if !defined(REF_64_TRIG) && !defined(REF_EXACT_TRIG)//32 bit trig recursion
#      define TR1_TYPE BP1Type
#      define MULT_TR1  MULT_BP1
#      define COEFF_FROM_TR1(tr1) (tr1)
#      define TR1_FROM_FLOAT(flt) (BP1_FROM_FLOAT(flt))
#      define TR1_FROM_COEFF(tr1) (tr1)
#      if defined(BUILD_INTEGER)
#           define TR1_SCALE     NF2BP1
#      else
#           define TR1_SCALE     1.0F
#      endif
#      define TR1_FROM_BP1(bp1) (bp1)
#      define BP1_FROM_TR1(tr1) (tr1)

#      define TR2_TYPE BP2Type
#      define MULT_TR2  MULT_BP2
#      define TR2_FROM_FLOAT(flt) (BP2_FROM_FLOAT(flt))
#      if defined(BUILD_INTEGER)
#           define TR2_SCALE     NF2BP2
#      else
#           define TR2_SCALE     1.0F
#      endif
#      define TR2_FROM_BP1(bp1) (BP2_FROM_BP1(bp1))
#      define TR2_FROM_BP2(bp2) (bp2)
#      define BP2_FROM_TR2(tr2) (tr2)
#else//FOR 64 bit trig recursion
#      define TR1_TYPE XBP1Type
#      define MULT_TR1  MULT_XBP1
#      define COEFF_FROM_TR1(tr1) XBP1_FROM_BP1(tr1)
#      define TR1_FROM_FLOAT(flt) XBP1_FROM_FLOAT(flt)
#      define TR1_FROM_COEFF(tr1) XBP1_FROM_BP1(tr1)
#      if defined(BUILD_INTEGER)
#           define TR1_SCALE     XBP1_FRAC_SCALE
#      else
#           define TR1_SCALE     1.0F
#      endif
#      define TR1_FROM_BP1(bp1) (XBP1_FROM_BP1(bp1))
#      define BP1_FROM_TR1(tr1) (BP1_FROM_XBP1(tr1))

#      define TR2_TYPE XBP2Type
#      define MULT_TR2  MULT_XBP2
#      define TR2_FROM_FLOAT(flt) XBP2_FROM_FLOAT(flt)
#      if defined(BUILD_INTEGER)
#           define TR2_SCALE     XBP2_FRAC_SCALE
#      else
#           define TR2_SCALE     1.0F
#      endif
#      define TR2_FROM_BP1(bp1) (XBP2_FROM_BP1(bp1))
#      define TR2_FROM_BP2(bp2) (XBP2_FROM_BP2(bp2))
#      define BP2_FROM_TR2(tr2) (BP2_FROM_XBP2(tr2))
#endif
// recursion: cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
// and:       sin(a+b) = sin(a-b) + 2*sin(b)*cos(a)
#define TR1_RECURR_INC_UPDATE_PREV(ThisCos,ThisSin,PriorCos,PriorSin,Step)          \
{                                                                   \
    TR1_TYPE xbp1TempCos = (PriorCos) - MULT_TR1(Step,ThisSin);     \
    TR1_TYPE xbp1TempSin = (PriorSin) + MULT_TR1(Step,ThisCos);     \
    PriorCos = ThisCos;  ThisCos = xbp1TempCos;                     \
    PriorSin = ThisSin;  ThisSin = xbp1TempSin;                     \
}

// recursion: cos(a-2b) = cos(a) - 2*sin(b)*cos(a-b)
// and:       sin(a-2b) = sin(a) + 2*sin(b)*sin(a-b)
#define TR2_RECURR_DEC2X(Cos1,Sin1,Cos2,Sin2,Step)                  \
{                                                                   \
    Cos2 -= MULT_TR2(Step,Sin1);                                    \
    Sin2 += MULT_TR2(Step,Cos1);                                    \
    Cos1 -= MULT_TR2(Step,Sin2);                                    \
    Sin1 += MULT_TR2(Step,Cos2);                                    \
}

/* sin(a+b) = sin(a-b) + 2*sin(b)*cos(a) */
/* cos(a+b) = cos(a-b) - 2*sin(b)*sin(a) */
#define TR2_RECURR_INC(ThisCos,ThisSin,Cos1,Sin1,Step)  \
{                                                                   \
    ThisCos = (ThisCos) - MULT_TR2(Step,Sin1);         \
    ThisSin = (ThisSin) + MULT_TR2(Step,Cos1);         \
}

/* sin(a+b) = sin(a-b) + 2*sin(b)*cos(a) */
/* cos(a+b) = cos(a-b) - 2*sin(b)*sin(a) */
#define TR2_RECURR_INC_UPDATE_PREV(ThisCos,ThisSin,PriorCos,PriorSin,Step)      \
{                                                                   \
    TR2_TYPE xbp1TempCos = (PriorCos) - MULT_TR2(Step,ThisSin);     \
    TR2_TYPE xbp1TempSin = (PriorSin) + MULT_TR2(Step,ThisCos);     \
    PriorCos = ThisCos;  ThisCos = xbp1TempCos;                     \
    PriorSin = ThisSin;  ThisSin = xbp1TempSin;                     \
} 
                                                                                    
#define WTTYPE
#if defined(BUILD_INTEGER) && defined(WTTYPE)

    typedef U32 WtType;
#   define WT_FRAC_BITS 31
#   define WT_SCALE ((U32)1<<WT_FRAC_BITS)
#   define WT_FROM_FLOAT(flt) ((WtType)((flt)*WT_SCALE+0.5))
#   define FLOAT_FROM_WT(wt) ((Float)(wt)/WT_SCALE)
#   define MUL_WT_F( c, x, y ) (c)((x)*FLOAT_FROM_WT(y))

#   define COEF_MUL_WT( x, y ) (CoefType)((I64)(x)*(y)>>WT_FRAC_BITS)
#   define COEF_DIV_WT( x, y ) (CoefType)(((I64)(x)<<WT_FRAC_BITS)/(y))


#else // WTTYPE

    typedef Float WtType;
#   define WT_FROM_FLOAT(flt) ((WtType)(flt))
#   define FLOAT_FROM_WT(wt) ((Float)(wt))
#   define COEF_MUL_WT( x, y ) ((x)*(y))
#   define COEF_DIV_WT( x, y ) ((x)/(y))

#endif // !WTTYPE

#define RVRBTYPE

// RvrbType, used by cxReverbFilter()

#if defined(BUILD_INTEGER) && defined(RVRBTYPE)
    typedef I32 RvrbType;
#   define RVRB_FROM_FLOAT( flt ) (RvrbType)((flt)*(1<<30))
#   ifdef COEF64BIT
#       define COEF_MUL_RVRB( x, y ) (CoefType)(((x)*(I64)(y))>>30)
#   else
#       define COEF_MUL_RVRB( x, y ) (CoefType)(MULT_HI_DWORD_DOWN(x,y))
#   endif
#else
    typedef Float RvrbType;
#   define RVRB_FROM_FLOAT( flt ) (flt)
#   define COEF_MUL_RVRB( x, y ) ( (x) * (y) )
#endif

// ChexType, used by chex-scaling function ReconMonoDiff() & friends.

#define CHEXTYPE

#   define CX_BITS 22
#   define CX_MAX ((1<<(32-CX_BITS-1))-1)
// something less than log10(CX_MAXM4)
#   define CX_MAXLOG (CX_FROM_FLOAT( 2.7f))
#   define CX_MINLOG (-CX_MAXLOG)
// something less than sqrt(CX_MAXM4)
#   define CXM_MAXSQ (CX_FROM_FLOAT(22.0f))

#if defined(BUILD_INTEGER)
    typedef I32 ChexType;
#   define CX_SCALE ((I32)1<<CX_BITS)

#   define CX_FROM_FLOAT( flt  ) (ChexType)((flt)*(1<<CX_BITS))
#   define FLOAT_FROM_CX( cxsc ) (((float)(cxsc))/(1<<CX_BITS))
#   define CX_MUL( x, y ) (MULT_HI_DWORDM(x,y,10))
#   define CX_MUL64(x, y) ((((x)*(I64)(y))>>CX_BITS))
#   if defined(COEF64BIT)
#       define COEF_MUL_CXSC(x, y) (CoefType)CX_MUL64(x, y)
#   else
#       define COEF_MUL_CXSC(x, y) (CoefType)CX_MUL(x, y)
#   endif
#   define ASSERT_CX( flt ) assert( (((I64)1<<31)-1) >= ABS(flt) );
#   define CX_ROUND(a,b) IPROUND(a,b)
#   define CX_FLOOR(a,b) IPFLOOR(a,b)
#   define CX_FROM_IDIV(a,b) ((a)*CX_SCALE/(b))
#   define CX_DIV(a, b) (ChexType)(((I64)(a)<<CX_BITS)/(b))
#   define CX_DIV64(a, b) (((I64)(a)<<CX_BITS)/(b))
#   define CX_SQRT(a)   (isqrt32(max(a,0))<<(CX_BITS/2))
#   define CX_SQRT64(a) (isqrt64(max(a,0))<<(CX_BITS/2))
#else
    typedef Float ChexType;
#   define CX_FROM_FLOAT( flt ) (flt)
#   define FLOAT_FROM_CX( flt ) (flt)
#   define CX_MUL(x, y) ((x)*(y))
#   define CX_MUL64(x, y) CX_MUL(x, y)
#   define CX_MUL_FFLT( x, y ) (ChexType)( (x) * (y) )
#   define COEF_MUL_CXSC( x, y ) (CoefType)( (x) * (y) )
#   define ASSERT_CX( flt ) assert( CX_MAX >= ABS(flt) );
#   ifndef PLATFORM_SPECIFIC_ROUND
#       define CX_FLOOR(a,b) ((Int)((a)/(b)))
#   else
#       define CX_FLOOR(a,b) ((Int)ROUNDF((a)/(b) - 0.5f))
#   endif
#   define CX_ROUND(a,b) (ROUNDF((a)/(b)))
#   define CX_FROM_IDIV(a,b) ((ChexType)(a)/(b))
#   define CX_MUL(a, b) ((a)*(b))
#   define CX_DIV(a, b) ((a)/(b))
#   define CX_DIV64(a, b) ((a)/(b))
#   define CX_SQRT(a) ((ChexType)sqrt(a))
#   define CX_SQRT64(a) CX_SQRT(a)
#endif

#   define CX_MAXM4 CX_FROM_FLOAT((CX_MAX-4))
#   define CX_MINM4 CX_FROM_FLOAT(1.0f/(CX_MAX-4))

#define CX_ABS(a) (ABS(a))

#define CX_ZERO  0
#define CX_ONE   CX_FROM_FLOAT(1.0f)
#define CX_SQRT2 CX_FROM_FLOAT(1.41421356237310f)

#ifdef BUILD_INTEGER
#define BUILD_INTEGER_LPC
#endif
// always build integer lpc as long as not using PLATFORM_LPC_DIRECT
#ifndef PLATFORM_LPC_DIRECT
#ifndef WMA_TARGET_SH4
#define BUILD_INTEGER_LPC
#endif
#endif // PLATFORM_LPC_DIRECT

#ifdef BUILD_INTEGER_LPC

//****************************************************************************
//         Types, constants related to LPC.
//         Lot of these could be moved to constants.h or lpcConst.h for cleanliness
//****************************************************************************

//  LSP (aka LSF), used for inverse quantized LSF.
    typedef Int LspType;
#   define FRACT_BITS_LSP 30
#   define LSP_SCALE (1<<FRACT_BITS_LSP)
#   define LSP_FROM_FLOAT(a) ((LpType)((a)*LSP_SCALE))
#   define MULT_LSP(a,b) (I32)((((I64)(a))*((I64)(b)))>>FRACT_BITS_LSP)
// MULT_LSP may be redefined by processor specific code in macros_cpu.h

//  LP, used for P, Q, and LPC values
    typedef Int LpType;
#   ifndef MATCH_ARM_WAY
#       define FRACT_BITS_LP 27
#   else
#       define FRACT_BITS_LP 26        
#   endif
#   define LP_SCALE (1<<FRACT_BITS_LP)
#if defined(LPC_COMPARE)          //only used for LPC debug
#   define FLOAT_FROM_LP(a) ((Float)((a)*(1.0f/LP_SCALE)))
#endif
#   define LP_FROM_FLOAT(a) ((LpType)((a)*LP_SCALE))

//  LP Spectrum: used during FFT of LPC values
//  LP Spectrum power: sum-squares of FFT output
    typedef Int LpSpecType;
//                Uses 64-bit intermediates
#   ifndef MATCH_ARM_WAY
#       define FRACT_BITS_LP_SPEC 25
#   else
        //  ARM's use of 26 instead of 25 produces BIG relative errors compared to LPC_COMPARE
        //  at least when using the old version of the Lpc code.
//#       define FRACT_BITS_LP_SPEC 26
#       define FRACT_BITS_LP_SPEC 25
#   endif
    typedef U64 LpSpecPowerType;
#   define BITS_LP_SPEC_POWER 64
#   define FRACT_BITS_LP_SPEC_POWER 30 
#   define QR_FRACTION_FRAC_BITS 24
#   define QR_EXPONENT_FRAC_BITS 29

#   define LP_SPEC_SCALE (1<<FRACT_BITS_LP_SPEC)
#   define LP_SPEC_POWER_SCALE ((float)(1L<<FRACT_BITS_LP_SPEC_POWER))
#   define LP_SPEC_FROM_FLOAT(a) ((LpSpecType)((a)*LP_SPEC_SCALE))
#   define LP_SPEC_POWER_FROM_FLOAT(a) ((LpSpecType)((a)*LP_SPEC_POWER_SCALE))
#   define FLOAT_FROM_LP_SPEC(a) ((Float)((a)*(1.0f/LP_SPEC_SCALE)))
#   define LP_SPEC_FROM_LP(a) ((LpSpecType)((a)>>(FRACT_BITS_LP-FRACT_BITS_LP_SPEC)))

//  Weights, computed from LPC (and Bark?).
    typedef UInt WeightType;
#ifdef BUILD_INTEGER
    typedef UInt FinalWeightType;
#   define FINALWEIGHT_FROM_FLOAT(flt) WEIGHT_FROM_FLOAT(flt)
#   define FINALWEIGHT_FROM_WEIGHT(wt) (wt)
#else
    typedef Float FinalWeightType;
#   define FINALWEIGHT_FROM_FLOAT(flt) (flt)
#   define FINALWEIGHT_FROM_WEIGHT(wt) FLOAT_FROM_WEIGHT(wt)
#endif
//               We see weight factor values upto 64.53440857: 7 bits enough to cover integer part, 
//               leaving upto 25 bits for fraction. However, only 21 bits of fraction are generated 
//               upstream, making other 4 bits zero, even if used.
#   ifndef MATCH_ARM_WAY
#       define WEIGHTFACTOR_FRACT_BITS     21
#   else
#       define WEIGHTFACTOR_FRACT_BITS     25
#   endif
#   define WEIGHT_FROM_FLOAT(a) ((WeightType)((a)*(1<<WEIGHTFACTOR_FRACT_BITS)))
#   define FLOAT_FROM_WEIGHT(a) ((Float)((a)*(1.0f/(1<<WEIGHTFACTOR_FRACT_BITS))))

// convert float or double to BP2 integer ( -2.0 <= x < +2.0 )
#define NF2BP2LPC 0x40000000

// Fractional Type with range -2.0 <= x < 2.0 used by FFT Trig Recurrsion 
    typedef I32 BP2LPCType;
#   define BP2LPC_FRAC_BITS 30
#   define BP2LPC_FRAC_SCALE NF2BP2LPC
#   define BP2LPC_FROM_FLOAT(flt) ((BP2LPCType)((flt)*BP2LPC_FRAC_SCALE))
#   define FLOAT_FROM_BP2LPC(bp2) ((bp2)/((Float)BP2LPC_FRAC_SCALE))
#if defined(BUILD_INTEGER)
#   define BP2LPC_FROM_BP1(bp1) ((bp1)>>1)
#   define BP2LPC_FROM_BP2(bp2) (bp2)
#else
#   define BP2LPC_FROM_BP1(bp1) BP2LPC_FROM_FLOAT(bp1)
#   define BP2LPC_FROM_BP2(bp2) BP2LPC_FROM_FLOAT(bp2)
#endif
#   define MULT_BP2LPC(a,b) MULT_HI_DWORD_DOWN((a),(b))
#   define MULT_BP2LPC_I32(a,b) ((I32) (((a) * (I64) (b)) >> BP2LPC_FRAC_BITS))

// Fractional Type with range -2.0 <= x < 2.0 used by FFT Trig Recurrsion 
    typedef I64 XBP2LPCType;
#   define XBP2LPC_FRAC_BITS 62
#   define XBP2LPC_FRAC_SCALE 0x4000000000000000i64
#   define XBP2LPC_FROM_FLOAT(flt) ((XBP2LPCType)((flt)*XBP2LPC_FRAC_SCALE))
#   define FLOAT_FROM_XBP2LPC(xbp2) ((xbp2)/((Float)XBP2LPC_FRAC_SCALE))
#   define BP2LPC_XBP2LPC_CONVFACT  (XBP2LPC_FRAC_SCALE/(I64)(NF2BP2LPC)) // 0x100000000
#   define BP2LPC_FROM_XBP2LPC(xbp2) ((BP2LPCType)((xbp2)>>32))
#   define XBP2LPC_FROM_BP2LPC(bp2) ((XBP2LPCType)(bp2 * BP2LPC_XBP2LPC_CONVFACT))
#if defined(BUILD_INTEGER)
#   define XBP2LPC_FROM_BP2(bp2) XBP2LPC_FROM_BP2LPC(bp2)
#   define XBP2LPC_FROM_BP1(bp1) (XBP2LPC_FROM_BP2LPC((bp1)>>1))
#else
#   define XBP2LPC_FROM_BP1(bp1) XBP2LPC_FROM_FLOAT(bp1)
#   define XBP2LPC_FROM_BP2(bp2) XBP2LPC_FROM_FLOAT(bp2)
#endif
#   define MULT_XBP2LPC(a,b) ( ((XBP2LPCType)(((a)>>32))<<1) * (((XBP2LPCType)((b)>>32))<<1) )	// less good for the FFT, 1.44 eps max error

// Fraction is stored at 2^32 (BP0)
#define UBP0_FROM_FLOAT_LPC(x) ((U32)(x*4294967296.0F))

#   define DIV2LPC(a) ((a)>>1)
#   define MUL2LPC(a) ((a)<<1)

#   define INTEGER_ONLY_LPC(a) a
#   define INTEGER_OR_INT_FLOAT_LPC(a,b) a

#else // BUILD_INTEGER_LPC

//****************************************************************************
//         Types, constants related to LPC.
//****************************************************************************

//  LSP (aka LSF), used for inverse quantized LSF.
    typedef Float LspType;
#   define LSP_FROM_FLOAT(a) ((LspType)(a))
#   define MULT_LSP(x,y) ((x)*(y))

// LP, used for P, Q, and LPC values
    typedef Float LpType;
#   define LP_FROM_FLOAT(a) ((LpType)(a))
#   define FLOAT_FROM_LP(a) ((Float)(a))

// LP Spectrum: used during FFT of LPC values
// LP Spectrum power: sum-squares of FFT output
    typedef Float LpSpecType;
    typedef Float LpSpecPowerType;
#   define LP_SPEC_FROM_FLOAT(a) ((LpSpecType)(a))
#   define FLOAT_FROM_LP_SPEC(a) ((Float)(a))
#   define LP_SPEC_FROM_LP(a)    ((LpSpecType)(a))

//  Weights, computed from LPC   (and Bark?).
    typedef Float WeightType;
    typedef Float FinalWeightType;
#   define FINALWEIGHT_FROM_FLOAT(flt) (flt)
#   define FINALWEIGHT_FROM_WEIGHT(wt) (wt)
#   define WEIGHT_FROM_FLOAT(a) ((WeightType)(a))
#   define FLOAT_FROM_WEIGHT(a) ((Float)(a))

// Fractional Type used by FFT Trig Recurrsion 
    typedef Float BP2LPCType;
#   define BP2LPC_FRAC_BITS 0
#   define BP2LPC_FRAC_SCALE 1
#   define BP2LPC_FROM_FLOAT(flt) ((BP2LPCType)(flt))
#   define FLOAT_FROM_BP2LPC(bp2) ((Float)(bp2))
#   define BP2LPC_FROM_BP1(bp1) (bp1)
#   define BP2LPC_FROM_BP2(bp2) (bp2)
#   define MULT_BP2LPC(a,b) ((a)*(b))
#   define MULT_BP2LPC_I32(a,b) ((a) * (b))

// Fractional Type used by FFT Trig Recurrsion 
    typedef Double XBP2LPCType;
#   define XBP2LPC_FRAC_BITS 0
#   define XBP2LPC_FRAC_SCALE 1
#   define XBP2LPC_FROM_FLOAT(flt) ((XBP2LPCType)(flt))
#   define FLOAT_FROM_XBP2LPC(bp2) ((Float)(bp2))
#   define BP2LPC_XBP2LPC_CONVFACT  (1) // 0x100000000
#   define BP2LPC_FROM_XBP2LPC(xbp2) (BP2LPCType(xbp2))
#   define XBP2LPC_FROM_BP2LPC(bp2) (XBP2LPCType(bp2))
#   define XBP2LPC_FROM_BP1(bp1) ((XBP2LPCType)(bp1))
#   define XBP2LPC_FROM_BP2(bp2) ((XBP2LPCType)(bp2))
#   define MULT_XBP2LPC(a,b) ((a)*(b))

#   define DIV2LPC(a) ((a)*0.5f)
#   define MUL2LPC(a) ((a)*2.0f)

#   define INTEGER_ONLY_LPC(a)
#   define INTEGER_OR_INT_FLOAT_LPC(a,b) b

#endif // BUILD_INTEGER_LPC

//Trig Recursion Type
#if !defined(REF_64_TRIGLPC) && !defined(REF_EXACT_TRIGLPC)//32 bit trig recursion
#      define TR2LPC_TYPE BP2LPCType
#      define MULT_TR2LPCX  MULT_BP2LPCX
#      define TR2LPC_FROM_FLOAT(flt) (BP2LPC_FROM_FLOAT(flt))
#      define FLOAT_FROM_TR2LPC(flt) (FLOAT_FROM_BP2LPC(flt))
#      define TR2LPC_FROM_BP2(bp2) (BP2LPC_FROM_BP2(bp2))
#      define TR2LPC_FROM_BP1(bp1) (BP2LPC_FROM_BP1(bp1))
#      define BP2LPC_FROM_TR2LPC(tr2) (tr2)
#else//FOR 64 bit trig recursion
#      define TR2LPC_TYPE XBP2LPCType
#      define MULT_TR2LPCX MULT_XBP2LPCX
#      define TR2LPC_FROM_FLOAT(flt) (XBP2LPC_FROM_FLOAT(flt))
#      define FLOAT_FROM_TR2LPC(flt) (FLOAT_FROM_XBP2LPC(flt))
#      define TR2LPC_FROM_BP2(bp2) (XBP2LPC_FROM_BP2(bp2))
#      define TR2LPC_FROM_BP1(bp1) (XBP2LPC_FROM_BP1(bp1))
#      define BP2LPC_FROM_TR2LPC(tr2) (BP2LPC_FROM_XBP2LPC(tr2))
#endif


INLINE Float FloatFromCoeff(const CoefType c, int ls)
{
  int rs = ls + COEF_FRAC_BITS;
  Float s = (rs > 0) ? (1.0f/((I64)1<<rs)) : (Float)((I64)1<<-rs);
  return (Float)c*s;
}

INLINE Double DoubleFromCoeff(const CoefType c, int ls)
{
  int rs = ls + COEF_FRAC_BITS;
  Double s = (rs > 0) ? (1.0/((I64)1<<rs)) : (Double)((I64)1<<-rs);
  return (Double)c*s;
}

INLINE I32 CoeffFromDouble(const Double c, int ls)
{
  int rs = ls + COEF_FRAC_BITS;
  Double s = (rs > 0) ? (1.0/((I64)1<<rs)) : (Double)((I64)1<<-rs);
  return (I32)((Double)c/s);
}

INLINE I32 CoeffFromFloat(const Float c, int ls)
{
  int rs = ls + COEF_FRAC_BITS;
  Double s = (rs > 0) ? (1.0/((I64)1<<rs)) : (Double)((I64)1<<-rs);
  return (I32)((Double)c/s);
}

#define CH_FFC(c) (c)

#ifdef BUILD_INTEGER
#define WMACFF(c) CoeffFromFloat(c, ppcinfo->m_cLeftShiftBitsTotal)
#define WMADFC(c) DoubleFromCoeff(c, ppcinfo->m_cLeftShiftBitsTotal)
#define WMACFD(c) CoeffFromDouble(c, ppcinfo->m_cLeftShiftBitsTotal)
#define WMAFFC(c) FloatFromCoeff(c, ppcinfo->m_cLeftShiftBitsTotal)
#define WMACFFPQ(c) CoeffFromFloat(c, ppcinfo->m_cLeftShiftBitsTotal-ppcinfo->m_cLeftShiftBitsQuant)
#define WMADFCPQ(c) DoubleFromCoeff(c, ppcinfo->m_cLeftShiftBitsTotal-ppcinfo->m_cLeftShiftBitsQuant)
#define WMAFFCPQ(c) FloatFromCoeff(c, ppcinfo->m_cLeftShiftBitsTotal-ppcinfo->m_cLeftShiftBitsQuant)
#endif

// some utility macros that are type specific to avoid the compiler's type conversion rules.
#define COEF_ABS(a) (((a)<0) ? -(a) : (a))
#define BPX_ABS(a) (((a)<0) ? -(a) : (a))

#define ABS(x) ((x) > 0 ? (x) : -(x))


#if !(defined(REFERENCE_RAND_24) || defined(REFERENCE_RAND_16))

    //****************************************************************************
    // quick and dirty rand generator, assuming low word multiply, only works for 
    // 32-bit machines see Numerical Recipes p.284.  
    // Note this is the referenced generator but the 24-bit or 16-bit versions can
    // be used for compliance comparisions with 24-bit or 16-bit implementations.
    //****************************************************************************

    typedef struct tagRandState {
        I32 iPrior;         // prior value
        U32 uiRand;         // current value
    } tRandState;

    INLINE I32 quickRand(tRandState* ptRandState)
    {
        const U32 a = 1664525;
        const U32 c = 1013904223;
        I32 iTemp, iTemp1;
        //a*x + c has to be done with unsigned 32 bit
        ptRandState->uiRand =  a * ptRandState->uiRand + c;

        // uiRand values starting from a 0 seed are: 0x3c6ef35f, 0x47502932, 0xd1ccf6e9, 0xaaf95334, 0x6252e503, 0x9f2ec686, 0x57fe6c2d, ...

        // do not change the above - this reference generator has been extensively tested and has excellent randomness properties
        // a truism in the world of random number generator theory and practice is:
        // "any change, no matter how small, can and will change the properties of the generator and must be fully tested"
        // In case you don't know, it can easily take a person-month to fully test a generator.
    
        // Notwithstanding the above, it is fair to take a function of a random number to shape its range or distribution.
        // This we do below to give it a triangular distrbution between -2.5 and 2.5 to roughly approximate a Guassian distribution.

        // cast and shift to make the range (-1, 1) with Binary Point 3.
        iTemp = ((I32)(ptRandState->uiRand)) >> 2; 

        // *1.25 to make the range (-1.25, 1.25) 
        iTemp += (iTemp>>2);
    
        // Difference of two random numbers gives a triangle distribution and a range of (-2.5, 2.5)
        // it also gives a serial correlation of -0.5 at lag 1.  But all the other lags have normally small correlations.
        iTemp1 = iTemp - ptRandState->iPrior;

        // Save first term of this difference for next time.
        ptRandState->iPrior = iTemp;

        //return -2.5 to 2.5 with Binary Point = 3 with a triangle distribution
        return iTemp1;
    }

    INLINE void RandStateClear(tRandState* ptRandState) {
        ptRandState->iPrior = 0;
        ptRandState->uiRand = 0;
    }

    // protect encoder from having these defined by mistake
#   ifdef REFERENCE_RAND_24
#       undef REFERENCE_RAND_24
#   endif
#   ifdef REFERENCE_RAND_16
#       undef REFERENCE_RAND_16
#   endif

#elif defined(REFERENCE_RAND_24)

    //****************************************************************************
    // Quick and dirty 24-bit rand generator.
    // Simulates 24-bits on a 32-bit reference machine.
    // Note this is the 24-bit referenced generator which can be used for compliance 
    // comparisions with 24-bit implementations by defining REFERENCE_RAN_24
    //****************************************************************************
    typedef struct tagRandState {
        I32 iPrior;         // prior value   (only top 24-bits used)
        U32 uiRand;         // current value (only top 24-bits used)
    } tRandState;

    INLINE I32 quickRand(tRandState* ptRandState)
    {
        // OK to 512 lags, then ChiSquare is suspect at 1024 and rejects at 2048 (length 1024000)
        const U32 uLCa = 69857;         // 0x000110E1
        const U32 uLCc = 3546581;       // 0x00361DD5

        I32 iTemp, iTemp1;
        //a*x + c has to be done with unsigned 32 bit - but we similate a 24x24
        ptRandState->uiRand =  (uLCa * ((ptRandState->uiRand)>>8) + uLCc)<<8;

        // uiRand values starting from a 0 seed are: 0x361dd500, 0x78a60a00, 0xaaac9f00, 0xa0c59400, 0x7104e900, 0xc2fe9e00, 0x1fc6b300

        // do not change the above - see comment in 32-bit generator

        // cast and shift to make the range (-1, 1) with Binary Point 3.
        iTemp = (((I32)(ptRandState->uiRand)) >> 2) & 0xFFFFFF00; 

        // *1.25 to make the range (-1.25, 1.25) 
        iTemp += ((iTemp>>2) & 0xFFFFFF00);
    
        // Difference of two random numbers gives a triangle distribution and a range of (-2.5, 2.5)
        // it also gives a serial correlation of -0.5 at lag 1.  But all the other lags have normally small correlations.
        iTemp1 = iTemp - ptRandState->iPrior;

        // Save first term of this difference for next time.
        ptRandState->iPrior = iTemp;

        //return -2.5 to 2.5 with Binary Point = 3 with a triangle distribution
        return iTemp1;
    }

    INLINE void RandStateClear(tRandState* ptRandState) {
        ptRandState->iPrior = 0;
        ptRandState->uiRand = 0;
    }


#elif defined(REFERENCE_RAND_16)
    //****************************************************************************
    // Quick and dirty 16-bit rand generator.
    // Simulates 16-bits on a 32-bit reference machine.
    // Note this is the 16-bit referenced generator for compliance comparisions 
    // with 16-bit implementations by defining REFERENCE_RAN_16.
    // The function actually returns 21 random bits at the top of the 32 
    // so is not a pure 16-bit generator, but does limit itself to a 16x16=>32 multiply
    //****************************************************************************

    // Background
    // A pure 16-bit Linear Congruent generator has limited sequence length.  
    // Use 13 A's and 3 C's choosen from good values in the middle of the range.
    // Tested OK up to lag 1024 (length 32768) and pretty good at 2048 and 2049.
    // Sequence length quite long.

    // these two arrays are defined once in dectables.c
#   define LCA_SET 13
#   define LCC_SET 3
    extern const unsigned int g_uWMALCA[LCA_SET];   // {1637,1033,1825,1621, 1657,1861,1229,1549, 2017,941,1409,1777, 1153};
    extern const unsigned int g_uWMALCC[LCC_SET];   // {13849,13841,13859};

    typedef struct tagRandState {
        I32 iPrior;         // prior value
        U16 uiRand;         // current value
        char bIdxLCA;       // index for uLCA
        char bIdxLCC;       // index for uLCC
    } tRandState;

    INLINE I32 quickRand(tRandState* ptRandState)
    {
        // This 16-bit implementation returns a 32-bit result with the top 21 bits random.
        // But it base implementation is 16x16=>32, e.g. it requires only a single precision 16-bit multiply.

        I32 iTemp, iTemp1;
        U32 uTemp;

        //a*x + c is with unsigned 32 bit - but we similate a 16x16+16 =32
        uTemp =  (g_uWMALCA[ptRandState->bIdxLCA++] * (ptRandState->uiRand)) + g_uWMALCC[ptRandState->bIdxLCC++];

        // save bottom 16 bits
        ptRandState->uiRand  = (unsigned short)uTemp;

        // uiRand values starting from a 0 seed are: 0x3623, 0x259c, 0x5add, 0x5698, 0xb511, 0x78ae, 0x6af9, 0x09f2, 0xc49b, 0x4f3e, 0x4377, 0x1108

        // wrap indexes
        if (ptRandState->bIdxLCA>=LCA_SET) 
            ptRandState->bIdxLCA = 0;
        if (ptRandState->bIdxLCC>=LCC_SET)
            ptRandState->bIdxLCC = 0;

        // get best 19 bits into top
        uTemp <<= 13;           

        // do not change the above - see comment in 32-bit generator

        // cast and shift to make the range (-1, 1) with Binary Point 3.
        iTemp = (((I32)(uTemp)) >> 2); 

        // *1.25 to make the range (-1.25, 1.25) 
        iTemp += (iTemp>>2);
    
        // Difference of two random numbers gives a triangle distribution and a range of (-2.5, 2.5)
        // it also gives a serial correlation of -0.5 at lag 1.  But all the other lags have normally small correlations.
        iTemp1 = iTemp - ptRandState->iPrior;

        // Save first term of this difference for next time.
        ptRandState->iPrior = iTemp;

        //return -2.5 to 2.5 with Binary Point = 3 with a triangle distribution
        return iTemp1;
    }

    INLINE void RandStateClear(tRandState* ptRandState) {
        ptRandState->iPrior = 0;
        ptRandState->uiRand = 0;
        ptRandState->bIdxLCA = 1;
        ptRandState->bIdxLCC = 2;
    }

#endif

//****************************************************************************
// floor of log base 2 of a number which is a power of 2 
//****************************************************************************

INLINE I32 LOG2(U32 i)
{   // returns n where n = log2(2^n) = log2(2^(n+1)-1)
    U32 iLog2 = 0;
    assert (i != 0);

    while ((i >> iLog2) > 1)
        iLog2++;

    return iLog2;
}

#define CEILLOG2(i) ((i)<=1 ? 0 : (LOG2((i)-1)+1))
#define FLOORLOG2(i) ((i)<=1 ? 0 : LOG2(i))

//#ifndef macintosh
//#define log2 LOG2
//#endif

//****************************************************************************
// Normalize a dynamically scaled unsigned int 
//****************************************************************************
INLINE void NormUInt( UInt* puiValue, Int* pcFracBits, const UInt uiTarget ){
    const UInt uiTarget2 = uiTarget>>1;
    register UInt uiV = *puiValue;
    register Int cFB = *pcFracBits;
    assert( uiV > 0 );    
    if (uiV == 0) return; // useful if asserts are disabled

    while ( uiV < uiTarget2 )
    {
        uiV <<= 2;        
        cFB += 2;
    }
    if ( uiV < uiTarget )
    {
        uiV <<= 1;        
        cFB += 1;
    }
    *puiValue = uiV;
    *pcFracBits = cFB;
}

//****************************************************************************
// Align a dynamically scaled int to a particular binary point position
//****************************************************************************
INLINE Int Align2FracBits( const Int iValue, const Int cFracBits, const Int cAlignFracBits )
{
    const Int iShift = cFracBits-cAlignFracBits;

    if (iShift < 0) {
        return (iValue << -iShift);
    } else if (iShift < 32) { 
        return (iValue >> iShift);
    } else {
        return 0;
    }
}


// V4 Compatibility Mode: This mode allows us to compare V5 encoder with V4 encoder
#ifdef V4V5_COMPARE_MODE
#define V4V5COMPARE_SNAPTOZERO(x)   if (fabs(x) <= 1.0e-15) {(x) = 0;}
#define ROUNDF_V4V5COMPARE(x)  ROUNDD(x)
typedef double V4V5COMPARE;
#else   // V4V5_COMPARE_MODE
#define V4V5COMPARE_SNAPTOZERO(x)
#define ROUNDF_V4V5COMPARE(x)  ROUNDF(x)
typedef float  V4V5COMPARE;
#endif  // V4V5_COMPARE_MODE
/*
#ifdef BUILD_INTEGER
#define FLOATORU32_CONST(flop,fb)           ((U32)((flop)*(1 << (fb))))
#define FLOATORINT_TOFLOAT(x,fb)            ((Float)(x)/(Float)(1 << (fb)))
#define FLOATORINT_SELECTTOFLOAT(f,i,fb)    ((Float)(i)/(Float)(1 << (fb)))
#define FLOATORINT_ASSERT(x)                assert(x)
#define FLOATORINT_AB(a,b)                  (a)

// The following is used to allow non-integerized code to convert a FLOP
// result to a bit-discarded integer result
#define FLOATORU32_DISCARDBITSFROMFLT(x,fb) ((U32)((x)/(float)(1 << (fb))))
#define FLOATORU32_DISCARDBITSFROMU32(x,fb) ((U32)(x) >> (fb))
#define FLOATORU32_DISCARDBITSFROMI64(x,fb) ((I64)(x) >> (fb))
#define FLOATORU32_ADDFRACTBITS(i,fb)       ((i) << (fb))
#define FLOATORI32_DISCARDBITSFROMI32(x,fb) ((I32)(x) >> (fb))

#else   // BUILD_INTEGER

#define FLOATORU32_CONST(flop,fb)           (flop)
#define FLOATORINT_TOFLOAT(x,fb)            (x)
#define FLOATORINT_SELECTTOFLOAT(f,i,fb)    (f)
#define FLOATORINT_ASSERT(x)
#define FLOATORINT_AB(a,b)                  (b)

#define FLOATORU32_DISCARDBITSFROMFLT(x,fb) (x) // FLOP-to-FLOP, no conversion required
#define FLOATORU32_DISCARDBITSFROMU32(x,fb) ((Float)x)
#define FLOATORU32_DISCARDBITSFROMI64(x,fb) (x)
#define FLOATORU32_ADDFRACTBITS(i,fb)       (i) // FLOP, no fract bits required
#define FLOATORI32_DISCARDBITSFROMI32(x,fb) (x)
#endif  // BUILD_INTEGER
*/

// **************************************************************************
// Bring in platform-specific macros
// **************************************************************************
// Include them here because some of them use the global macros above

#if defined (_WINDOWS) && !defined (DISABLE_OPT)
    // This is a window build.
    #include "windows.h"
#endif

#include "wmartmacros.h"

//#pragma AVRT_CODE_BEGIN

#include "wmaOS.h"
#if defined(WMA_TARGET_X86) && !defined (DISABLE_OPT)

// Output target
#ifdef COMMONMACROS_OUTPUT_TARGET
#pragma COMPILER_MESSAGE("-----MACROS.H: Compiling for Intel x86 Target")
#endif  // COMMONMACROS_OUTPUT_TARGET

#include "../x86/macros.h"

//---------------------------------------------------------------------------
#elif defined(WMA_TARGET_MIPS) && !defined (DISABLE_OPT)

// Output target
#ifdef BUILD_INTEGER
#ifdef COMMONMACROS_OUTPUT_TARGET
#pragma COMPILER_MESSAGE("-----MACROS.H: Compiling for MIPS integer Target")
#endif // COMMONMACROS_OUTPUT_TARGET
#else
#ifdef COMMONMACROS_OUTPUT_TARGET
#pragma COMPILER_MESSAGE("-----MACROS.H: Compiling for MIPS floating point  Target")
#endif // COMMONMACROS_OUTPUT_TARGET

#endif // BUILD_INTEGER

#include "..\mips\macros_mips.h"

#elif defined(WMA_TARGET_SH3) && !defined (DISABLE_OPT)

// Output target
#ifdef COMMONMACROS_OUTPUT_TARGET
//#pragma COMPILER_MESSAGE("-----MACROS.H: Compiling for SH3 (Hitachi & HP WinCE) Target")
#endif // COMMONMACROS_OUTPUT_TARGET

#include "..\sh3\macros_sh3.h"

#elif defined(WMA_TARGET_SH4) && !defined (DISABLE_OPT)

// Output target
#ifdef COMMONMACROS_OUTPUT_TARGET
//#pragma COMPILER_MESSAGE("-----MACROS.H: Compiling for SH4 (Hitachi WinCE) Target")
#endif // COMMONMACROS_OUTPUT_TARGET

STATIC_INLINE U32 ByteSwap(U32 i){
    U8 *p = (U8 *)&i;
    return (p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3];
}

#include "..\sh4\macros_SH4.h"

//---------------------------------------------------------------------------
#else

// Output target
#   ifdef COMMONMACROS_OUTPUT_TARGET
//#       pragma COMPILER_MESSAGE("-----MACROS.H: Compiling for ANSI-C Target")
#   endif // COMMONMACROS_OUTPUT_TARGET

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

#ifndef WMA_TARGET_MIPS
STATIC_INLINE U32 ByteSwap(U32 i){
    U8 *p = (U8 *)&i;
    return (p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3];
}
#endif

#endif // Platform-specific #ifdefs

// Bring in platform-independent macros
#ifndef MULT_HI_DWORD_DOWN
#define MULT_HI_DWORD_DOWN(a,b) (I32)((((I64)(a))*((I64)(b)))>>30)
#endif
#ifndef MULT_HI_DWORD
#define MULT_HI_DWORD(a,b) (I32)((((I64)(a))*((I64)(b)))>>32)
#endif
#ifndef MULT_HI_DWORD7
#define MULT_HI_DWORD7(a,b) (I32)((((I64)(a))*((I64)(b)))>>25)
#endif
#ifndef MULT_HI_DWORDN
#define MULT_HI_DWORDN(a,b,N) (I32)((((I64)(a))*((I64)(b)))>>(32-(N)))
#endif
#ifndef MULT_HI_DWORDM
#define MULT_HI_DWORDM(a,b,M) MULT_HI_DWORDN(a,b,M)
#endif

// **************************************************************************
// Overridable Macros (optimized for some platforms, but not all)
// **************************************************************************
// The following can be overridden within a particular platform macro file
#ifndef PLATFORM_SPECIFIC_DIVI64BYU32
STATIC_INLINE I32 DIVI64BYU32(I64 a, U32 b) {
    return (I32)((a)/(b));
}
#endif

#ifndef PLATFORM_SPECIFIC_CEILOFLOG2
#define CEILOFLOG2(iDivPow2, iMean) {for (iDivPow2 = 0; ((U32)1 << iDivPow2) < iMean; iDivPow2++);} 
#endif //PLATFORM_SPECIFIC_CEILOFLOG2

#ifndef PLATFORM_SPECIFIC_ROUND
STATIC_INLINE I32   ROUNDF(float f)
{
    if (f < 0.0f)
        return (I32) (f - 0.5f);
    else
        return (I32) (f + 0.5f);
}

//---------------------------------------------------------------------------
STATIC_INLINE I32   ROUNDD(double f)
{
// The following definition is added to suppress SH4 build warnings on SH4
// when -Qfast is used.
#   if defined(SH4)
    if ((float) f < 0.0f)
        return (I32) ((float) f - 0.5f);
    else
        return (I32) ((float) f + 0.5f);
#   else
    if (f < 0.0f)
        return (I32) (f - 0.5f);
    else
        return (I32) (f + 0.5f);
#   endif
}
#endif // #ifndef PLATFORM_SPECIFIC_ROUND


#ifndef PLATFORM_SPECIFIC_FNPTR
#define PLATFORM_SPECIFIC_FNPTR     //nothing for non-x86
#endif // PLATFORM_SPECIFIC_FNPTR

#include "fastfloat.h"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// Define Macros to switch auReconMono and auSaveHistoryMono between Integer and Float

#if defined(BUILD_INTEGER)

#define ROUND_SATURATE_STORE16(piDst,cf,mn,mx,iTmp)      \
    assert(pau->m_nBytePerSample == 2);                  \
    *((I16*)piDst) = (I16) checkRange (cf, mn, mx);      \
    iTmp = cf;

#define ROUND_SATURATE_STORE24(piDst,cf,mn,mx,iTmp)      \
    assert(pau->m_nBytePerSample == 3);                  \
    prvSetSample24INLINE(checkRange (cf, mn, mx), piDst, pau, 0);   \
    iTmp = cf;

#define ROUND_SATURATE_STORE2024(piDst,cf,mn,mx,iTmp)    \
    assert(pau->m_nBytePerSample == 3);                  \
    prvSetSample2024INLINE(checkRange (cf, mn, mx), piDst, pau, 0); \
    iTmp = cf;

#define ROUND_SATURATE_STORE(piDst,cf,mn,mx,iTmp)      \
    pau->m_pfnSetSample((PCMSAMPLE) checkRange (cf, mn, mx), piDst, pau, 0);    \
    iTmp = cf;

#define ROUND_AND_CHECK_RANGE(it,flt,mn,mx) \
    if (flt < mn) \
        it = mn; \
    else if (flt > mx) \
        it = mx; \
    else \
        it = flt;

#else  // BUILD_INT_FLOAT

#ifdef PLATFORM_SPECIFIC_ROUND

// Combined Round and Saturate is faster in floating point
// But if the platform has special Round function, we must use it.
#define ROUND_AND_CHECK_RANGE(it,flt,mn,mx)            \
    it = (I32)ROUNDF_V4V5COMPARE(flt);                 \
    it = checkRange(it,mn,mx);
#else

// Combined Round and Saturate is faster in floating point
#define ROUND_AND_CHECK_RANGE(it,flt,mn,mx)            \
    if ( flt < (V4V5COMPARE)0.0 ) {                    \
        it = (I32)( flt - ((V4V5COMPARE)0.5) );       \
        if ( it < mn ) it = mn;                        \
    } else {                                           \
        it = (I32)( flt + ((V4V5COMPARE)0.5) );       \
        if ( it > mx ) it = mx;                        \
    }
#endif

#define ROUND_SATURATE_STORE16(piDst,cf,mn,mx,iTmp)      \
    assert(pau->m_nBytePerSample == 2);                  \
    ROUND_AND_CHECK_RANGE( iTmp, cf, mn, mx );           \
    *((I16*)piDst) = (I16)iTmp;

#define ROUND_SATURATE_STORE24(piDst,cf,mn,mx,iTmp)      \
    assert(pau->m_nBytePerSample == 3);                  \
    ROUND_AND_CHECK_RANGE( iTmp, cf, mn, mx );           \
    prvSetSample24INLINE(iTmp, piDst, pau, 0);

#define ROUND_SATURATE_STORE2024(piDst,cf,mn,mx,iTmp)    \
    assert(pau->m_nBytePerSample == 3);                  \
    ROUND_AND_CHECK_RANGE( iTmp, cf, mn, mx );           \
    prvSetSample2024INLINE(iTmp, piDst, pau, 0);

#define ROUND_SATURATE_STORE(piDst,cf,mn,mx,iTmp)      \
    ROUND_AND_CHECK_RANGE( iTmp, cf, mn, mx );         \
    pau->m_pfnSetSample((PCMSAMPLE)iTmp, piDst, pau, 0);
    
#endif // Both BUILD_INTEGER and BUILD_INT_FLOAT

// For lossless mode. reconstructed values are I32.
#define ROUND_SATURATE_STORE16_LLM(piDst,iResult,mn,mx)           \
    assert(pau->m_nBytePerSample == 2);                           \
    iResult = checkRange(iResult,mn,mx);                          \
    *((I16*)piDst) = (I16)iResult;

#define ROUND_SATURATE_STORE24_LLM(piDst,iResult,mn,mx)           \
    assert(pau->m_nBytePerSample == 3);                           \
    iResult = checkRange(iResult,mn,mx);                          \
    prvSetSample24INLINE(iResult, piDst, pau, 0);

#define ROUND_SATURATE_STORE2024_LLM(piDst,iResult,mn,mx)         \
    assert(pau->m_nBytePerSample == 3);                           \
    iResult = checkRange(iResult,mn,mx);                          \
    prvSetSample2024INLINE(iResult, piDst, pau, 0);

#define ROUND_SATURATE_STORE_LLM(piDst,iResult,mn,mx)             \
    iResult = checkRange(iResult,mn,mx);                          \
    pau->m_pfnSetSample((PCMSAMPLE)iResult, piDst, pau, 0);

//V3 LLM
// Dump data (float or int) to a file. If file exists, attach the data to the end.
#if (!defined (UNDER_CE) && defined(DEBUG))
#define DEBUGDUMPDATA
#endif

#if defined DEBUGDUMPDATA
    #define DUMPFLOATDATATOFILE(Data, Len, FileName)    \
    {                                                   \
        Int i;                                          \
        FILE * fp;                                      \
        fp = FOPEN(FileName, "a");                      \
        for (i = 0; i < Len; i++) {                     \
            WMAFprintf(fp, "%20.10f\n",Data[i]);        \
        }                                               \
        FCLOSE(fp);                                     \
    }                                       

    #define DUMPINTDATATOFILE(Data, Len, FileName)      \
    {                                                   \
        Int i;                                          \
        FILE * fp;                                      \
        fp = FOPEN(FileName, "a");                      \
        for (i = 0; i < Len; i++) {                     \
            WMAFprintf(fp, "%10d\n",Data[i]);           \
        }                                               \
        FCLOSE(fp);                                     \
    }                         
    #define DUMPDATA(Data, Len, FileName, Mode)         \
    {                                                   \
        FILE * fp = NULL;                               \
        fp = fopen(FileName, Mode);                     \
        fwrite(Data, 1, Len, fp);                       \
        fclose(fp);                                     \
    }                         
    #define DUMPDATACOND(Cond, Data, Len, FileName, Mode) \
    {                                                   \
        FILE * fp = NULL;                               \
        if (!(Cond)) {                                  \
            fp = fopen(FileName, Mode);                 \
            fwrite(Data, 1, Len, fp);                   \
            fclose(fp);                                 \
        }                                               \
    }                         

#else
    #define DUMPFLOATDATATOFILE(Data, Len, FileName)
    #define DUMPINTDATATOFILE(Data, Len, FileName)
    #define DUMPDATA(Data, Len, FileName, Mode)
    #define DUMPDATACOND(Cond, Data, Len, FileName, Mode)
#endif //DEBUGDUMPDAATA

//  Examples:
//
//  DUMPFLOATDATATOFILE(rgfltInput0,    iLen, "c:\\temp\\input2.dat");
//  DUMPFLOATDATATOFILE(rgfltInput1,    iLen, "c:\\temp\\input3.dat");
//

#define SDE_WANTS_AV

#if defined(WIN32) && !defined(SDE_WANTS_AV)
#define WMA_TRY_AND_EXCEPT_AV(fn) { \
  __try { \
    return fn; \
  } \
  __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? \
            EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) { \
    return WMA_E_FAIL; \
  } \
}
#else // WIN32 && SDE_WANTS_AV
#define WMA_TRY_AND_EXCEPT_AV(fn) return fn;
#endif // WIN32 && SDE_WANTS_AV


#if defined (PRINT_STATS) && defined (_DEBUG)
#define DEBUG_PRINT_VECTOR
#endif // PRINT_STATS && _DEBUG

//#define FFT_TONALITY_TEST

#if defined (DEBUG_PRINT_VECTOR)

#define DEBUG_PRINT_I32_VECTOR(fPrint, szText, iArray, cSize) \
    if (fPrint) {\
      Int index;\
      WMAFprintf(stdout,"\n%s:\n", szText);\
      for (index = 0; index < cSize; index++)\
          WMAFprintf(stdout, "%d ", iArray[index]);\
      WMAFprintf(stdout,"\n");\
    }

#define DEBUG_PRINT_FLT_VECTOR(fPrint, szText, iArray, cSize) \
    if (fPrint) {\
      Int index;\
      WMAFprintf(stdout,"\n%s:\n", szText);\
      for (index = 0; index < cSize; index++)\
          WMAFprintf(stdout, "%f ", iArray[index]);\
      WMAFprintf(stdout,"\n");\
    }

#else
// so !DEBUG_PRINT_VECTOR
#define DEBUG_PRINT_I32_VECTOR(fPrint, szText, iArray, cSize)
#define DEBUG_PRINT_FLT_VECTOR(fPrint, szText, iArray, cSize)
#endif // DEBUG_PRINT_VECTOR


//#define WRITE_TIME_TO_FILE

//#define COMPLEX_STREAM3
//#define COMPLEX_STREAM2
//#define COMPLEX_STREAM1
// Complex1: Maximum subframes, one channel group for non-lfe
// Complex2: Maximum subframes, two channel groups for non-lfe (one each at a hierarchical level)
// Complex3: Post-processing transform, NxN.


//#define ENCODE_FOR_XBOX
//#if defined (_DEBUG)
//#define PRINT_STATS
//#endif

//#define SDE_WANTS_PRINTFIO
/*
#ifdef FORCEINLINE
#undef FORCEINLINE
#endif

#if defined(UNDER_CE) && !defined(DEBUG) && !defined(__arm)
#   define FORCEINLINE __forceinline
#else
#   define FORCEINLINE __inline
#   define __forceinline __inline
#endif
*/
#ifdef NOINLINE
#undef NOINLINE
#endif

#if defined(UNDER_CE)
#   define NOINLINE
#else
#   define NOINLINE __declspec(noinline)
#endif

FORCEINLINE int WMAPrintf(const char* pszFmt, ... )
{
#if !defined (UNDER_CE) || defined (SDE_WANTS_PRINTFIO)
    int ret;
    va_list vargs;
    va_start(vargs, pszFmt);
    ret = vprintf(pszFmt, vargs);
    va_end(vargs);
    return ret;
#else
    return 0;
#endif
}

FORCEINLINE int WMAFprintf(FILE *stream, const char* pszFmt, ... )
{
#if (!defined(UNDER_CE) && !defined(_XBOX)) || defined (SDE_WANTS_PRINTFIO)
    int ret;
    va_list vargs;
    va_start(vargs, pszFmt);
    ret = vfprintf(stream, pszFmt, vargs);
    va_end(vargs);
    return ret;
#else
    return 0;
#endif
}

/*FORCEINLINE int WMASprintf(char *buffer, const char* pszFmt, ... )
{
#if !defined (UNDER_CE) || defined (SDE_WANTS_PRINTFIO)
    int ret;
    va_list vargs;
    va_start(vargs, pszFmt);
    ret = vsprintf(buffer, pszFmt, vargs);
    va_end(vargs);
    return ret;
#else
    return 0;
#endif
}*/

#if !defined (UNDER_CE) || defined (SDE_WANTS_PRINTFIO)
    #ifdef _XBOX
        #include <tchar.h>
        #define XFILE void
        #define STDOUT (void *)                
        extern XFILE * _XFOPEN( const TCHAR *filename, const TCHAR *mode);
        extern int  _XFSEEK(XFILE *strmnum, long offset, int origin);
        extern int  _XFWRITE(const void *buffer, int size, int count, XFILE *strmnum);
        extern long  _XFTELL(XFILE *strmnum);
        extern int  _XFCLOSE(XFILE *strmnum);
        extern int  _XFFLUSH();
        extern int  _XFPRINTF(XFILE *strmnum, const char *format, ...);
        #define FOPEN _XFOPEN
        #define FSEEK _XFSEEK
        #define FTELL _XFTELL
        #define FCLOSE _XFCLOSE
        #define FWRITE _XFWRITE
        #define FFLUSH _XFFLUSH
        #define FPRINTF _XFPRINTF
    #else
        #define FOPEN   fopen
        #define FSEEK   fseek
        #define FTELL   ftell
        #define FCLOSE  fclose
        #define FWRITE  fwrite
        #define FREAD   fread
        #define FFLUSH  fflush
    #endif //_XBOX
#else
    #define FOPEN(a, b)        NULL
    #define FSEEK(a, b, c)     -1
    #define FTELL(a)           -1
    #define FCLOSE(a)          EOF
    #define FWRITE(a, b, c, d) 0
    #define FREAD(a, b, c, d)  0
    #define FFLUSH(a)          EOF
#endif //!defined (UNDER_CE) || defined (SDE_WANTS_PRINTFIO)
//#define DEBUG_ENCODE_FOR_XBOX

#include "wmspecstring.h"

#endif  // __COMMON_MACROS_H

