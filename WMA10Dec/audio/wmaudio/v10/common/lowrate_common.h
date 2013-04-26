//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    lowrate_common.h

Abstract:

    Macros from lowrate_common.c, placed here so that the macros may be
    used by encoder-only parts of the code.

Author:

    Raymond Cheng (raych)       Jan 18, 2001

*************************************************************************/

#ifndef __LOWRATE_COMMON_H
#define __LOWRATE_COMMON_H


//***************************************************************************
// Encoder/Decoder Separation
//***************************************************************************

// From lowrate_common.c

#ifdef ENABLE_ALL_ENCOPT
//******************************************************************************************
// Support routines for Resampling indexes to those used when the MaskQ's were last updated
//******************************************************************************************
#define MASKQ_RESAMPLE_OFFSET 6
typedef struct MaskResampleInfo
{
	Int iMaskResampleRatio;
	Int iMaskResampleRatioPow;
	Int cValidBarkBandLatestUpdate;
} MaskResampleInfo;


#ifdef HITACHI
#pragma inline(iResampleIndex)
static Int iResampleIndex( Int iRecon, const MaskResampleInfo MRI )
#else
STATIC_INLINE Int iResampleIndex( Int iRecon, const MaskResampleInfo MRI )
#endif
{	// return resampled linear index suitable for frame that was last updated with MaskQ
	// equvilent to iRecon shifted left or right by (MRI.iMaskResampleRatioPow-MASKQ_RESAMPLE_OFFSET)
	return ( (((iRecon) << MRI.iMaskResampleRatioPow) >> MASKQ_RESAMPLE_OFFSET) );
}

#ifdef HITACHI
#pragma inline(iUnResampleIndex)
static Int iUnResampleIndex( Int iResampled, const MaskResampleInfo MRI )
#else
STATIC_INLINE Int iUnResampleIndex( Int iResampled, const MaskResampleInfo MRI )
#endif
{	// return the reverse of iResampleIndex()
	// that is, convert from resampled indexes of MaskQ or WeightFactor to natural index for the current frame
    if (MRI.iMaskResampleRatioPow > MASKQ_RESAMPLE_OFFSET){
		// Rounding for down shift 
		// Although V4 did not round when resampling, this inverse funtion needs to round ???
        return (iResampled + (1<<(MRI.iMaskResampleRatioPow-(MASKQ_RESAMPLE_OFFSET+1)))) >> (MRI.iMaskResampleRatioPow-MASKQ_RESAMPLE_OFFSET);
        // return iResampled >> (MRI.iMaskResampleRatioPow-MASKQ_RESAMPLE_OFFSET);
    } else {
        return iResampled << (MASKQ_RESAMPLE_OFFSET-MRI.iMaskResampleRatioPow);
    }
}


//*****************************************************************************************
// Look up (10^(1/16)) ^ iMaskQ
//*****************************************************************************************
#ifdef HITACHI
#pragma inline(ffltMaskPower10)
static FastFloat ffltMaskPower10( Int iMaskQ )
#else
STATIC_INLINE FastFloat ffltMaskPower10( Int iMaskQ )
#endif
{	// (10^(1/16)) ^ iMaskQ
	FastFloat fflt;

    // There is, unfortunately, no easy way to keep this assert with our new
    // combined decoder/encoder build.
//#if !defined (ENCODER)
//  assert( -MASK_MINUS_POWER_TABLE_SIZE < iMaskQ && iMaskQ <= MASK_PLUS_POWER_TABLE_SIZE );
//#endif

    if ( iMaskQ <= 0 )
	{
		if (iMaskQ <= -MASK_MINUS_POWER_TABLE_SIZE)
			iMaskQ = -(MASK_MINUS_POWER_TABLE_SIZE-1);
#if defined(BUILD_INTEGER)
		fflt.iFraction = rgiMaskMinusPower10[ -iMaskQ ];	// with MASK_POWER_FRAC_BITS==28 fractional bits
		fflt.iFracBits = MASK_POWER_FRAC_BITS+(-iMaskQ>>2);
#else
		fflt = rgiMaskMinusPower10[ -iMaskQ ] / (Float)(1<<(-iMaskQ>>2));
#endif
	}
	else
	{
		if (iMaskQ >= MASK_PLUS_POWER_TABLE_SIZE)
			iMaskQ = MASK_PLUS_POWER_TABLE_SIZE;
#if defined(BUILD_INTEGER)
		fflt.iFraction = rgiMaskPlusPower10[ iMaskQ-1 ];	// with MASK_POWER_FRAC_BITS==28 fractional bits
		fflt.iFracBits = MASK_POWER_FRAC_BITS-(iMaskQ>>2);
#else
		fflt = rgiMaskPlusPower10[ iMaskQ-1 ] * (Float)(1<<(iMaskQ>>2));
#endif
	}
	return fflt;
}
#endif  // ENABLE_ALL_ENCOPT


//******************************************************************************************
//******************************************************************************************
#if defined(_DEBUG) && defined(INVERSE_QUANTIZE_AT_FRAME)
// these help match where we are with V4 which does not have a m_iFrameCount
#	define DEBUG_BREAK_AT_FRAME_INV_QUANT										\
		{ 																		\
			if ( pau->m_iCurrSubFrame == 0 && ppcinfo == pau->m_rgpcinfo )		\
			{	iInvQuantFrameCount++;	iInvQuantSubFrameCount = 0; }			\
			else if ( ppcinfo == pau->m_rgpcinfo ) iInvQuantSubFrameCount++;	\
			if ( iInvQuantFrameCount==INVERSE_QUANTIZE_AT_FRAME )				\
				DEBUG_BREAK();													\
		}
#elif defined(_DEBUG) && ( defined(PRINT_INVERSE_QUANTIZE_AT_FRAME) || defined(PRINT_INVERSE_QUANTIZE_AT_FRAME_FIRST) )
// these help match where we are with V4 which does not have a m_iFrameCount
#	define DEBUG_BREAK_AT_FRAME_INV_QUANT										\
		{ 																		\
			if ( pau->m_iCurrSubFrame == 0 && ppcinfo == pau->m_rgpcinfo )		\
			{	iInvQuantFrameCount++;	iInvQuantSubFrameCount = 0; }			\
			else if ( ppcinfo == pau->m_rgpcinfo ) iInvQuantSubFrameCount++;	\
		}
#else	// defined(_DEBUG) && defined(PRINT_INVERSE_QUANTIZE_AT_FRAME_FIRST) 
#	define DEBUG_BREAK_AT_FRAME_INV_QUANT
#endif	// ...

#if defined (ENABLE_ALL_ENCOPT)
//******************************************************************************************
//******************************************************************************************
// prvScanForNextBarkIndex scans for the next resampled bark index and then returns its unresampled linear index
//   iRecon and iHighLimit are linear indexes in the current frames natural scale.
//   iBarkResampled is the bark index in the resampled bark scale (appropriate for the frame when the MaskQ's were last updated)
//   rgiBarkIndex is the resampled bark index scale from that last updated MaskQ subframe
#ifdef HITACHI
#pragma inline(prvScanForNextBarkIndex)
static Int prvScanForNextBarkIndex( const Int iRecon, Int* piBarkResampled, const int iHighLimit, 
										  const Int* const rgiBarkIndexResampled, const MaskResampleInfo MRI )
#else
STATIC_INLINE Int prvScanForNextBarkIndex( const Int iRecon, Int* piBarkResampled, const int iHighLimit,
										  const Int* const rgiBarkIndexResampled, const MaskResampleInfo MRI )
#endif
{   //Scan for the next resampled bark index
	Int iNextBarkIndex, iBarkResampled, iReconResampled;
	iReconResampled = iResampleIndex(iRecon, MRI);
    while ( iReconResampled >= rgiBarkIndexResampled [*piBarkResampled+1]) 
		++(*piBarkResampled);
	iBarkResampled = *piBarkResampled;
	if ( iBarkResampled >= MRI.cValidBarkBandLatestUpdate )
	{
		assert( iBarkResampled < MRI.cValidBarkBandLatestUpdate );
		return( MRI.cValidBarkBandLatestUpdate );
	}
	iNextBarkIndex = iUnResampleIndex( rgiBarkIndexResampled [iBarkResampled + 1], MRI );
    if (iNextBarkIndex > iHighLimit) 
		iNextBarkIndex = iHighLimit;
	return iNextBarkIndex;
}
#endif // ENABLE_ALL_ENCOPT

//******************************************************************************************
//******************************************************************************************
#if defined(BUILD_INTEGER)
// SCALE_COEF_RECON shifts CoefRecon to give it TRANSFORM_FRACT_BITS==5 fractional bits
#if defined(PLATFORM_OPTIMIZE_MINIMIZE_BRANCHING)
	// This SCALE_COEF_RECON macro requires 6 ops and no branches
	// This SETUP_FOR_SCALE_COEF_RECON requires 5 ops plus 1 branch.
	// SCALE_COEFFICENT gets executed 25x as often as SETUP_FOR_SCALE_COEF_RECON, 
	// so this method requires 6.2 ops plus 0.04 branches per SCALE_COEFFICENT
#	define SCALE_COEF_RECON(iCR) ((((iCR)>>-iShift) & iMask2) | (((iCR)<<iShift) & iMask1))
#if 0
#	define SETUP_FOR_SCALE_COEF_RECON(iFB) iShift = iFB-TRANSFORM_FRACT_BITS;  \
								      iMask2 = 0xFFFFFFFF ^ (iMask1 = (iShift>=0) ? 0xFFFFFFFF : 0)
#endif
// See comment below
#	define SETUP_FOR_SCALE_COEF_RECON(fftQ) iShift = fftQ.iFracBits-TRANSFORM_FRACT_BITS;  \
								      iMask2 = 0xFFFFFFFF ^ (iMask1 = (iShift>=0) ? 0xFFFFFFFF : 0)

#else   // PLATFORM_OPTIMIZE_MINIMIZE_BRANCHING
	// When branching is not a high penaty activity, do it the simplier way
	//   iCoefRecon = (t=iFracBits-5)<0 ? iCoefRecon>>-t : iCoefRecon<<t
	// This SCALE_COEF_RECON requires 3 ops plus 1 branch or 2 ops plus 1 branch.  
	// This SETUP_FOR_SCALE_COEF_RECON requires 2 ops
	// SCALE_COEFFICENT gets executed 25x as often as SETUP_FOR_SCALE_COEF_RECON, 
	// so this method requires 2.58 ops plus 0.04 branches per SCALE_COEFFICENT
	// On one test on a 500 MHz Pentium 686, this way saves 1% execution time over masking.
#	define SCALE_COEF_RECON(iCR) (iShift<0) ? (iCR)<<-iShift : (iCR)>>iShift
//#	define SETUP_FOR_SCALE_COEF_RECON(iFB) iShift=iFB-TRANSFORM_FRACT_BITS
// This more complex setup (with pre-normalization) is required to deal with 56_WMAv2.wma which ends
// with 1.5 seconds of DC bias at -890.  This results in a single large coef at 0 and the rest 0.
// Then in the noise band, iShift tries to be == 33...
#	define SETUP_FOR_SCALE_COEF_RECON(fftQ) \
    while( fftQ.iFracBits > (30+TRANSFORM_FRACT_BITS) ) { fftQ.iFracBits--; fftQ.iFraction>>=1; } \
    iShift=fftQ.iFracBits-TRANSFORM_FRACT_BITS;
#endif  // PLATFORM_OPTIMIZE_MINIMIZE_BRANCHING

#define UNNORMED_MULT(fflt,c,shift) \
	fflt.iFraction = MULT_HI( fflt.iFraction, c );	\
	fflt.iFracBits += shift;

static const I32 cDitherFactorMR = 0x28F5C28F;		// BARK 0.02 * 2^35 (but I am not sure how to derive the 35)

#else   // defined(BUILD_INTEGER)

#define SCALE_COEF_RECON(iCR) (iCR)
#define SETUP_FOR_SCALE_COEF_RECON(ffltQ)
#define UNNORMED_MULT(flt,c,shift) flt *= c
static const Float cDitherFactorMR = 0.02F;		            // BARK_MODE: 0.02

#endif  // defined(BUILD_INTEGER)


#endif  // __LOWRATE_COMMON_H
