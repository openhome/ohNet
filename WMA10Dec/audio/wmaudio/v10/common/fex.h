//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __FEX_H_
#define __FEX_H_

#if defined(BUILD_WMAPROLBRV1)

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define TEST_RECONFEX
//#define TEST_RECONFEX2

//#define FEX_DBG_PRINT
//#define FEX_DBG_RECON_PRINT
//#define FEX_DBG_RECON_DUMP

#ifdef FEX_DBG_PRINT
extern Bool g_fxdbgprint;
#define fxprintf(x) if (g_fxdbgprint) printf x
#endif

// Max MLT value is given by: max_input*max_subframe_size/2.44 (approx).
// Max gain of forward xform = max_subframe_size/2.44
// Max gain of inverse xform = 1.27

// 0 to 6 produces good results

#define FEX_SCBINSHUFF (234)
#define FEX_SCBINSPREDHUFF (234)

// using a quantization step size of 9/256 makes integerization
// of the step size easy, and doesn't deviate very far from the
// original step size of 0.0352564.  

#define FEX_BASE_QUANT FEXT_FROM_FLOAT( 9.0f / 256 )

#define MAX_FEXLOGSCALE (FEX_SCBINSHUFF * FEX_BASE_QUANT)

#define FEX_STARTPOSBINS (128)
#define FEX_STARTPOSSMALL (8)
#define FEX_STARTPOSSMALLBITS (3) // log2(8)
#define FEX_MINMAXBW (4000)
#define FEX_BWRES (1000)

#define FEX_NUMNOISETRY (256) // search 256 noise vectors
// entropy coding of scale factors provides approximately 18% savings
//#define FEX_WRITEINDEX // allow direct writing of index (needed for training)
#ifdef FEX_WRITEINDEX
extern Bool g_fWriteIndex;
extern char *g_exargfile;
WMARESULT freqexInitExArgs();
#endif // FEX_WRITEINDEX

// need to increase PLUS_BUFSIZE for FEX_MAXBANDS=4096, or write more frequently

#ifdef BUILD_WMAPROLBRV3
// common
#define FEX_GLOBALPARAM_MASK_MVBINS         0x00000001
#define FEX_GLOBALPARAM_MASK_MVCBSET        0x00000002
#define FEX_GLOBALPARAM_MASK_MVCB           0x00000004
#define FEX_GLOBALPARAM_MASK_USERNDNS       0x00000008
#define FEX_GLOBALPARAM_MASK_NFTHR          0x00000010
#define FEX_GLOBALPARAM_MASK_MVRANGE        0x00000020
#define FEX_GLOBALPARAM_MASK_MVRES          0x00000040
#define FEX_GLOBALPARAM_MASK_RECCB          0x00000080
#define FEX_GLOBALPARAM_MASK_SINGLEMV       0x00000100
#define FEX_GLOBALPARAM_MASK_SCALESS        0x00000200
#define FEX_GLOBALPARAM_MASK_SCSPLIT        0x00000400
#define FEX_GLOBALPARAM_MASK_SCMVBANDS      0x00000800
#define FEX_GLOBALPARAM_MASK_MINFREQ        0x00001000
#define FEX_GLOBALPARAM_MASK_MAXFREQ        0x00002000
#define FEX_GLOBALPARAM_MASK_USECB3         0x00004000
// cfex/rfex specific
#define FEX_GLOBALPARAM_MASK_IMPLCT_BSSPLIT 0x00008000
#define FEX_GLOBALPARAM_MASK_MNZERO_BSBANDS 0x00010000
#define FEX_GLOBALPARAM_MASK_MXZERO_BSMXFRQ 0x00020000
#define FEX_GLOBALPARAM_MASK_OVRLY_BSSS     0x00040000
#define FEX_GLOBALPARAM_MASK_HFEND          0x00080000
#define FEX_GLOBALPARAM_MASK_V1COMP         0x00100000
// update list
#define FEX_GLOBALPARAM_MASK_LISTFRAME      0x00200000
#define FEX_GLOBALPARAM_MASK_LISTTILE       0x00400000
#endif

//#define FEX_DEBUGSTARTPOS
#if defined(BUILD_WMAPROLBRV2)
#include "chexpro.h"
#endif

// =========================================================================

extern const CoefType g_rgfFexNoise[1024];
extern const Int g_iFexNoiseLen;
extern const Int g_iFexMaxNoiseBandSize;

// =========================================================================

Void freqexSetCurChannelZeroMask(CAudioObject *pau);

Void freqexProcessValidMask(CAudioObject *pau, Int iGrp);

Void freqexIsValidPointInit(Fex *pfx, const CoefType *pfRecon,
                            Int iCurPos, Bool bFirst);

#define IS_VALID_FEXPT() \
  (pfx->m_bOverwriteBase || pfRecon==NULL || !pfx->m_bOverlayUsedForBand || \
   freqexGetNonzeroMask(pfx->m_pau, i+pfx->m_cStartIndex))

#define IS_VALID_FEXPT_MASK() \
  (IS_VALID_FEXPT() && (pucMask==NULL || pucMask[i]==1))

Void freqexSetNonzeroMaskFromCoef(CAudioObject *pau, CoefType *pf, Int iLen,
                                  Bool bForceCalc);

INLINE
Void freqexSetGroupGrp(CAudioObject *pau, Int iGroup, Bool bSplit)
{
    pau->m_iChGroup = iGroup;

    if (bSplit)
        pau->m_pucNonzeroMask =
            pau->m_ucNonzeroCoeffMask + 
            pau->m_iNonzeroMaskCh*pau->m_cFrameSampleHalf/8 +
            iGroup*pau->m_cFrameSampleHalf/16;
    else
        pau->m_pucNonzeroMask =
            pau->m_ucNonzeroCoeffMask + iGroup*pau->m_cFrameSampleHalf/8;
}

INLINE
Void freqexSetGroup(CAudioObject *pau, Int iChSrc, Bool bIndependent,
                    Bool bSplit)
{
    Int iGroup;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + iChSrc;

    if (pau->m_bPlusV1)
    {
        if (WMAB_TRUE==bIndependent)
            iGroup = 0;
        else
            iGroup = pcis->m_iFxChannelDependencyGroup + 1;
    }
    else if (pau->m_bPlusV2)
    {
        iGroup = iChSrc;
#if defined(BUILD_WMAPROLBRV2)
        if (pau->m_bCx && !pau->m_bFirstPlusFrameAfterReset)
            iGroup = chexGetFexChannel(pau, iChSrc);
#endif
    }

    freqexSetGroupGrp(pau, iGroup, bSplit);
}

INLINE
Void freqexSetNonzeroMask(const CAudioObject *pau, const Int iCoeff)
{
    Int iOffset = (iCoeff>>3);
    Int iRem = (iCoeff & 0x7);
    pau->m_pucNonzeroMask[iOffset] |= (1<<iRem);
}

INLINE
Void freqexUnsetNonzeroMask(const CAudioObject *pau, const Int iCoeff)
{
    Int iOffset = (iCoeff>>3);
    Int iRem = (iCoeff & 0x7);
    pau->m_pucNonzeroMask[iOffset] &= ~(1<<iRem);
}

INLINE
Int freqexGetNonzeroMask(const CAudioObject *pau, const Int iCoeff)
{
    Int iOffset = (iCoeff>>3);
    Int iRem = (iCoeff & 0x7);
    return (pau->m_pucNonzeroMask[iOffset] & (1<<iRem));
}

// =========================================================================

// generic quantization of an integer
INLINE
Int freqexQuant( Int iVal, const Int iBins, 
             const Int iMin, const Int iMax )
{
    const Int iVals = iMax-iMin+1;

    Int iIndex;

    assert(iVal >= iMin);
    assert(iVal <= iMax);

    iVal -= iMin;
    if (iBins < iVals)
        iIndex = iVal*iBins/iVals;
    else
        iIndex = iVal;

    assert(iIndex >= 0);
    assert(iIndex < iBins);
    iIndex = checkRange(iIndex, 0, iBins-1);

    return iIndex;
}

// inverse quantize an integer to approximate center of bin
// reconstruction is round(i*nVals/nBins + nVals/(2*nBins))
// which is round(2*i*nVals+nVals/(2*nBins))
// = (2*i*nVals+nVals+nBins)/(2*nBins)
INLINE
Int freqexInvQuantCenter( const Int iIndex, const Int iBins, 
                            const Int iMin  , const Int iMax )
{
    const Int iVals = iMax-iMin+1;

    Int iVal;

    assert(iIndex >= 0);
    assert(iIndex < iBins);

    if (iBins < iVals)
        iVal = (2*iIndex*iVals+iVals+iBins)/(2*iBins);
    else
        iVal = iIndex;
    iVal += iMin;

    assert(iVal >= iMin);
    if (iVal > iMax)
    {
        NO_ERROR_REPORT_BITSTREAM_CORRUPTION_AND_EXIT;
    }
    iVal = checkRange(iVal, iMin, iMax); // not necessary
exit:
    return iVal;
}

// inverse quantize an integer to minimum of bin
// recon is given by ceil(i*nVals/nBins)
// = (i*nVals+nBins-1)/nBins
INLINE
Int freqexInvQuantMin( const Int iIndex, const Int iBins, 
                         const Int iMin  , const Int iMax )
{
    const Int iVals = iMax-iMin+1;
    Int iVal;

    assert(iIndex >= 0);
    assert(iIndex < iBins);

    if (iBins < iVals)
        iVal = (iIndex*iVals + iBins - 1)/iBins;
    else
        iVal = iIndex;
    iVal += iMin;

    assert(iVal >= iMin);
    assert(iVal <= iMax);
    iVal = checkRange(iVal, iMin, iMax); // not necessary

    return iVal;
}

// inverse quantize an integer to maximum of bin
// use: floor(x-eps) = ceil(x-1) for positive 'x'
// recon is given by floor((i+1)*nVals/nBins-eps)
// = ceil((i+1)*nVals/nBins-1)
// = ceil(((i+1)*nVals-nBins)/nBins)
// = ((i+1)*nVals-nBins+nBins-1)/nBins
// = ((i+1)*nVals-1)/nBins
INLINE
Int freqexInvQuantMax( const Int iIndex, const Int iBins, 
                       const Int iMin  , const Int iMax )
{
    const Int iVals = iMax-iMin+1;

    Int iVal;

    assert(iIndex >= 0);
    assert(iIndex < iBins);

    if (iBins < iVals)
        iVal = ((iIndex+1)*iVals-1)/iBins;
    else
        iVal = iIndex;
    iVal += iMin;

    assert(iVal >= iMin);
    assert(iVal <= iMax);
    iVal = checkRange(iVal, iMin, iMax); // not necessary

    return iVal;
}

// inverse quantize so that defVal is a quantization point
INLINE
Int freqexInvQuantVal( const Int iIndex, const Int iBins,
                       const Int iMin  , const Int iMax,
                       const Int iDefVal )
{
    const Int iVals = iMax-iMin+1;
    Int iVal;

    assert(iIndex >= 0);
    assert(iIndex < iBins);

    if (iBins < iVals)
    {
        Int iDefValMin = iDefVal - iMin;

        Int iDefValIndex = freqexQuant(iDefValMin, iBins, 0, iVals-1);

        if (freqexInvQuantMin(iDefValIndex, iBins, 0, iVals-1)==
            iDefValMin)
            iVal = freqexInvQuantMin(iIndex, iBins, 0, iVals-1);
        else if (freqexInvQuantMax(iDefValIndex, iBins, 0, iVals-1)==
                 iDefValMin)
            iVal = freqexInvQuantMax(iIndex, iBins, 0, iVals-1);
        else
            iVal = (2*iVals*(iIndex-iDefValIndex)+2*iDefValMin*iBins+iBins)/
                (2*iBins);
    }
    else
    {
        iVal = iIndex;
    }
    iVal += iMin;

    assert(iVal >= iMin);
    if (iVal > iMax)
    {
        NO_ERROR_REPORT_BITSTREAM_CORRUPTION_AND_EXIT;
    }
    iVal = checkRange(iVal, iMin, iMax); // not necessary
exit:
    return iVal;
}

#ifdef BUILD_INTEGER
INLINE Int freqexBitScale( const CAudioObject *pau )
{
    return pau->m_nValidBitsPerSample-16;
}
#else
INLINE Float freqexBitScale( const CAudioObject *pau )
{
    // adjust to 16-bits of precision
    if (pau->m_nValidBitsPerSample <= 16)
        return (Float)(1<<(16-pau->m_nValidBitsPerSample));
    else
        return 1.0f / (1<<(pau->m_nValidBitsPerSample-16));
}
#endif


#ifndef BUILD_INTEGER

// quant scale
INLINE
Int freqexQuantScale( const Fex *pfx, Float fScale )
{
    Int iIndex;

    fScale *= pfx->m_fBitScale;
    if (fScale > 0.0f)
        fScale = (Float)log10(fScale); // in log domain
    else
        fScale = 0.0;
    fScale = checkRange(fScale, 0.0f, (Float)(MAX_FEXLOGSCALE-0.001f));

#ifndef PLATFORM_SPECIFIC_ROUND
    iIndex = (Int)(fScale/pfx->m_fltScaleQuantStep);
#else
    // this is faster than ftol
    iIndex = (Int)ROUNDF(fScale/pfx->m_fltScaleQuantStep - 0.5f);
#endif

    return iIndex;
}

// quant scale with prediction
INLINE
Int freqexQuantScalePred( const Fex *pfx, Float fScale,
                            I32 iLogScalePredQuantIndex )
{
    Int iIndex;
    Float fLogScalePredQuant;

    assert(iLogScalePredQuantIndex >= 0 &&
           iLogScalePredQuantIndex <= 2*(I32)pfx->m_cScaleBins);
    fLogScalePredQuant =
        iLogScalePredQuantIndex*(pfx->m_fltScaleQuantStep*0.5f);

    fScale *= pfx->m_fBitScale;
    if (fScale > 0.0f)
        fScale = (Float)log10(fScale);
    else
        fScale = 0.0;
    fScale = checkRange(fScale, 0.0f, (Float)(MAX_FEXLOGSCALE-0.001f));
    fScale -= fLogScalePredQuant-MAX_FEXLOGSCALE;
#ifndef PLATFORM_SPECIFIC_ROUND
    iIndex = (Int)(fScale/pfx->m_fltScaleQuantStepPred);
#else
    // faster than ftol
    iIndex = (Int)ROUNDF(fScale/pfx->m_fltScaleQuantStepPred - 0.5f);
#endif

    return iIndex;
}

#endif // !BUILD_INTEGER


#define FEX_POW10_OPT
#ifdef BUILD_INTEGER
#ifdef FEX_POW10_OPT

#define FEX_P2LUT_BITS 10
#define FEX_P2LUT_SIZE (1<<FEX_P2LUT_BITS)

extern U32 g_pow2LUT[ FEX_P2LUT_SIZE ];
extern U32 g_p2lut_init;

INLINE FastFloat fexPow10( U32 iScale )    // argument has FEXT_BITS of 
{
    if( 0 == iScale ) return FASTFLOAT_FROM_FLOAT(1.0f);

    if( !g_p2lut_init ) 
    {
        I32 i;
        for( i=0; i< FEX_P2LUT_SIZE; ++i )
        {
            g_pow2LUT[i] = (U32)(pow( 2, (float)i/FEX_P2LUT_SIZE )*(1<<30));
        }

        g_p2lut_init = 1;
    }

    {
        FastFloat fflt;

#define B FEX_P2LUT_BITS
#define N FEX_P2LUT_SIZE
#define S (FEXT_BITS-2)

        const U32 ilog2 = 0xD49A784C;   // 1.0/log(2) * 2^30
        const U32 ln2   = 0xB17217F8;   // ln(2) * 2^32

        const I32 exp_s = (I32)MULT_HI_UDWORD( iScale, ilog2 );         // 32x32 -> keep hi 32
        const U32 exp_i =  ( exp_s + (1<<(S-B-1)) ) >>  S;              // integer exponent
        const U32 exp_t = (( exp_s + (1<<(S-B-1)) ) >> (S-B)) & (N-1);  // 10 frac bits
        const I32 exp_d = exp_s - (exp_i<<S) - (exp_t<<(S-B));          // remainder

        U32 frac = g_pow2LUT[ exp_t ];      // 2.30 format

        I32 rem = (I32)(((I64)exp_d * ln2 ) >> (S-B));          // >> 15
        rem    += (I32)(((I64)rem   * rem ) >> (32+B+1));       // >> 43
        frac   += (I32)(((I64)frac  * rem ) >> (32+B));         // >> 42

        fflt.iFracBits = 30 - exp_i;
        fflt.iFraction = frac;

        assert( 0 <= exp_s );

        return fflt;

#undef S
#undef N
#undef B
    }
}

#else // so not FEX_POW10_OPT

INLINE FastFloat fexPow10( U32 iScale )
{
    Float fScale = (Float)iScale / (1<<FEXT_BITS);
    fScale = (Float)pow( 10.0f, fScale );
    return FASTFLOAT_FROM_FLOAT( fScale );
}
#endif // !FEX_POW10_OPT
#endif // BUILD_INTEGER

// unquant scale
INLINE
FastFloat freqexInvQuantScale( const Fex *pfx, const Int iIndex,
                                 I32 *piLogScalePred )
{
    I32 iLogScaleIndex;
#ifndef BUILD_INTEGER
    Float fScale;
#else
    FastFloat fScale;
    I32 iScale;
#endif

    // iLogScaleIndex represents reconstruction point as multiple of (step/2)
    // iLogScaleIndex will be odd and go from 1 to 2*numbins-1
    iLogScaleIndex = 2*(I32)iIndex + 1;
    *piLogScalePred = iLogScaleIndex;
    assert(iLogScaleIndex >= 0 && iLogScaleIndex <= 2*(I32)pfx->m_cScaleBins);

#ifndef BUILD_INTEGER

    fScale = iLogScaleIndex*(pfx->m_fltScaleQuantStep*0.5f);
    fScale = (Float)pow( 10.0f, fScale ) / pfx->m_fBitScale;
    return fScale;

#else // !BUILD_INTEGER

    iScale   = iLogScaleIndex * 9;
    iScale <<= FEXT_BITS - 9 - pfx->m_cScaleIndexExtraBits;

    assert( 0 <= iScale );  // iScale is assumed to be non-negative

    fScale = fexPow10( iScale );
    fScale.iFracBits -= pfx->m_iBitScale;
    return fScale;

#endif // BUILD_INTEGER
}

// unquant scale with predicition
INLINE
FastFloat freqexInvQuantScalePred( const Fex *pfx, const Int iIndex,
                                   const I32 iLogScalePredQuant,
                                   I32 *piLogScalePred )
{
    I32 iLogScaleIndex;
#ifndef BUILD_INTEGER
    Float fScale;
#else
    FastFloat fScale;
    I32 iScale;
#endif

    // use fact that steppred = 2*step to represent
    // reconstruction point as multiple of (step/2)
    // since iLogScalePredQuant is odd, iLogScaleIndex will be odd
    iLogScaleIndex =
        (I32)(4*iIndex + 2 - 2*pfx->m_cScaleBins + iLogScalePredQuant);
    // iLogScaleIndex will be odd point between 0 & 2*numbins, or
    // 0 or 2*numbins
    iLogScaleIndex = checkRange(iLogScaleIndex, 0, 2*(I32)pfx->m_cScaleBins);
    *piLogScalePred = iLogScaleIndex;

#ifndef BUILD_INTEGER

    fScale = iLogScaleIndex*(pfx->m_fltScaleQuantStep*0.5f);
    fScale = (Float)pow( 10.0f, fScale ) / pfx->m_fBitScale;
    return fScale;

#else // !BUILD_INTEGER

    iScale   = iLogScaleIndex * 9;
    iScale <<= FEXT_BITS - 9 - pfx->m_cScaleIndexExtraBits;
    fScale = fexPow10( iScale );
    fScale.iFracBits -= pfx->m_iBitScale;
    return fScale;

#endif // BUILD_INTEGER
}

INLINE
Int freqexMvBins( const Fex * const pfx )
{
    const Int nPts = pfx->m_iMaxStartPos - pfx->m_iMinStartPos + 1;
    return min(nPts, pfx->m_cMvBins);
}

INLINE
Int freqexMvBits( const Fex *pfx )
{
    const Int nPts = pfx->m_iMaxStartPos - pfx->m_iMinStartPos + 1;

    if (nPts < pfx->m_cMvBins)
        return CEILLOG2((UInt)nPts);
    else
        return pfx->m_cMvBits;
}

INLINE
Void freqexGetPredMvClosePts( const Fex *pfx,
                              Int *piLeftClose, 
                              Int *piRightClose )
{
    if (pfx->m_iPredMvIndex + pfx->m_iPredMvRightClose + 1 >=
        pfx->m_cMvBins)
    {
        *piRightClose = pfx->m_cMvBins - 1;
        *piLeftClose  = pfx->m_cMvBins - pfx->m_iPredMvClose - 1;
    }
    else if (pfx->m_iPredMvIndex - pfx->m_iPredMvLeftClose <= 0)
    {
        *piLeftClose  = 0;
        *piRightClose = pfx->m_iPredMvClose;
    }
    else
    {
        *piLeftClose  = pfx->m_iPredMvIndex - pfx->m_iPredMvLeftClose;
        *piRightClose = pfx->m_iPredMvIndex + pfx->m_iPredMvRightClose;
    }
}

// quant mv
INLINE
Int freqexQuantMv(const Fex *pfx, const Int iMv)
{
    return freqexQuant(iMv, pfx->m_cMvBins,
                       pfx->m_iMinStartPos, pfx->m_iMaxStartPos);
}

INLINE
Int freqexGetMvPred(const Fex *pfx, const Int iCb)
{
#if defined(BUILD_WMAPROLBRV2)
    if (WMAB_TRUE == pfx->m_bReconDomain)
    {
        ReconTileInfo *prtiPrev = chexPrevTile(pfx->m_pau->m_prp,
                                               pfx->m_prtiCurr);
        if (prtiPrev && prtiPrev->m_prfxrti)
        {
            PerChannelRecon *ppcr = prtiPrev->m_prfxrti->m_rgpcr + pfx->m_iChSrc;
            return ppcr->m_rgiFexMv[pfx->m_iBand];
        }
        else
        {
            assert(WMAB_FALSE);
            return 0;
        }
    }
    else
#endif
    {
        switch (iCb)
        {
        case 0:
        case 2:
            // no wrapping
            if (pfx->m_cStartIndex < pfx->m_iMaxLastCodedIndex &&
                WMAB_TRUE==pfx->m_bMvRangeFull)
                return pfx->m_cStartIndex;
            else
                return checkRange(pfx->m_iPredMvLowband,
                                  pfx->m_iMinStartPos, pfx->m_iMaxStartPos);
            break;
        case 1:
            // allow wrapping around the noise codebook
            assert(pfx->m_iMinStartPos == 0);
            return pfx->m_iPredMvNoise % (pfx->m_iMaxStartPos+1);
            break;
        case 3:
            assert(pfx->m_iMinStartPos == 0);
            return pfx->m_iPredMvNoiseFloor % (pfx->m_iMaxStartPos+1);
            break;
        }
        assert(WMAB_FALSE);
        return 0;
    }
}

INLINE
Void freqexSetPredMvIndex(Fex *pfx, const Int iCb)
{
    Int iPredMv = freqexGetMvPred(pfx, iCb);
    pfx->m_iPredMvIndex = freqexQuantMv(pfx, iPredMv);
}

INLINE
Bool freqexUseMvPred(const Fex *pfx, const Int iCb)
{
    if (pfx->m_iVersion == 1 ||
        (pfx->m_iVersion > 1 && WMAB_FALSE == pfx->m_bReconDomain && pfx->m_bV1Compatible))
    {
        if ((pfx->m_cStartIndex < pfx->m_iMaxLastCodedIndex) &&
            (iCb==0 || iCb==2)
            && WMAB_TRUE==pfx->m_bMvRangeFull)
            return WMAB_TRUE;

        if (WMAB_TRUE==pfx->m_bFirstLowbandAfterMaxCodedIndex &&
            (iCb==0 || iCb==2))
            return WMAB_FALSE;

        return
            (iCb==0 || iCb==2) ?
            pfx->m_bUseMvPredLowband : pfx->m_bUseMvPredNoise;
    }

    return WMAB_FALSE;
}

INLINE
Void freqexInitMvPred(Fex *pfx)
{
    pfx->m_iPredMvLowband = 0;
    pfx->m_iPredMvNoise = 0;
    pfx->m_iPredMvNoiseFloor = 0;
    pfx->m_bFirstLowbandAfterMaxCodedIndex = WMAB_TRUE;
}

INLINE
Void freqexUpdateFirstLowbandInfo(Fex *pfx, const Int iCb)
{
    Bool bUpdateLow = (pfx->m_cStartIndex >= pfx->m_iMaxLastCodedIndex ||
                       WMAB_FALSE==pfx->m_bMvRangeFull);

    if (WMAB_TRUE==bUpdateLow && (0==iCb || 2==iCb) &&
        WMAB_TRUE==pfx->m_bNeedMvCoding)
    {
        pfx->m_bFirstLowbandAfterMaxCodedIndex = WMAB_FALSE;
    }
}

INLINE
Void freqexUpdateMvPred(Fex *pfx, const Int iCb, const Int iMv)
{
    Bool bUpdateLow = (pfx->m_cStartIndex >= pfx->m_iMaxLastCodedIndex ||
                       WMAB_FALSE==pfx->m_bMvRangeFull);

    switch (iCb)
    {
    case 0:
        if (bUpdateLow)
            pfx->m_iPredMvLowband = iMv + pfx->m_cBandSize;
        break;
    case 1:
        if (bUpdateLow)
            pfx->m_iPredMvLowband += pfx->m_cBandSize;
        pfx->m_iPredMvNoise = iMv + pfx->m_cBandSize;
        break;
    case 2:
        if (bUpdateLow)
            pfx->m_iPredMvLowband = iMv + pfx->m_cBandSize;
        break;
    case 3:
        pfx->m_iPredMvNoiseFloor = iMv + pfx->m_cBandSize;
        break;
    case 4:
        // band is skipped completely
        if (bUpdateLow)
            pfx->m_iPredMvLowband += pfx->m_cBandSize;
        break;
    default:
        assert(WMAB_FALSE);
    }
}

// inverse quant mv
INLINE
Int freqexInvQuantMv( const Fex *pfx, const Int iMvIndex, const Int iCb)
{
    Int iMv, iPredMv;
    Bool bUseMvPred;

    // bUseNoise not referenced in the function
//    Bool bUseNoise, bUseMvPred;
//    bUseNoise = ((iCb % 2)==1 ? WMAB_TRUE : WMAB_FALSE); // iCb==1 || iCb==3

    bUseMvPred = freqexUseMvPred(pfx, iCb);

    if (bUseMvPred)
    {
        iPredMv = freqexGetMvPred(pfx, iCb);
        iMv = freqexInvQuantVal(iMvIndex, pfx->m_cMvBins,
                                pfx->m_iMinStartPos, pfx->m_iMaxStartPos,
                                iPredMv);
    }
    else
    {
        iMv = freqexInvQuantCenter(iMvIndex, pfx->m_cMvBins,
                                   pfx->m_iMinStartPos, pfx->m_iMaxStartPos);
    }

    return iMv;
}

#define CHECK_VAR(wr, val, min, max) \
if ((val) < (min) || (val) > (max)) /* we know it will be >= 0 */ \
{ \
    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wr); \
    val = max; \
}
#define CHECK_VAR_ENC(val, min, max) assert((val) >= (min) && (val) <= (max))

#define CHECK_VAR0(wr, val) \
if ((val) < 0) \
{ \
    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wr); \
    val = 0; \
}

#define CHECK_MV(iMv) CHECK_VAR(wmaResult, iMv, pfx->m_iMinStartPos, \
                                pfx->m_iMaxStartPos);
#define CHECK_MVENC(iMv) CHECK_VAR_ENC(iMv, pfx->m_iMinStartPos, \
                                       pfx->m_iMaxStartPos);

#define STARTPOS_MINMAX \
    /* find default starting position */ \
    Int minPos = 0; \
    /* Int maxPos = pfx->m_iMaxLastCodedIndex-1; */ \
    Int maxPos = pau->m_cHighCutOff-1;

INLINE
Int freqexStartPosBins(CAudioObject *pau, Fex *pfx)
{
    STARTPOS_MINMAX;

    if (maxPos-minPos+1 >= pfx->m_cStartPosBins)
        return pfx->m_cStartPosBins;
    else
        return maxPos-minPos+1;
}

INLINE
Int freqexStartPosBits(CAudioObject *pau, Fex *pfx)
{
    STARTPOS_MINMAX;

    if (maxPos-minPos+1 >= pfx->m_cStartPosBins)
        return pfx->m_cStartPosBits;

    if (maxPos <= minPos)
        return 0;

    return LOG2((U32)(maxPos-minPos))+1;
}

// quant start position
INLINE
Int freqexQuantStartPos(CAudioObject *pau, Fex *pfx, Int startPos)
{
    STARTPOS_MINMAX;

    startPos = checkRange(startPos, minPos, maxPos);

    return freqexQuant(startPos, pfx->m_cStartPosBins, minPos, maxPos);
}

INLINE
Int freqexInvQuantStartPos(CAudioObject *pau, Fex *pfx, Int startPos)
{
    STARTPOS_MINMAX;

    if (startPos > maxPos-minPos)
    {
        assert(minPos >= 0);
        return -1;
    }
    return freqexInvQuantMin(startPos, pfx->m_cStartPosBins, minPos, maxPos);
}

#define CHECK_START_POS(startPos) CHECK_VAR0(wmaResult, startPos);

INLINE
Int freqexEndPosBits(CAudioObject *pau, Fex *pfx)
{
    Int minPos = pfx->m_cStart+1;
    Int maxPos = pau->m_cHighCutOff-1;

    if (maxPos-minPos+1 >= pfx->m_cEndPosBins)
        return pfx->m_cEndPosBits;

    if (maxPos <= minPos)
        return 0;

    return LOG2((U32)(maxPos-minPos))+1;
}

// quant end position
INLINE
Int freqexQuantEndPos(CAudioObject *pau, Fex *pfx, Int endPos)
{
    // find default ending position
    Int minPos = pfx->m_cStart+1;
    Int maxPos = pau->m_cHighCutOff-1;

    endPos = checkRange(endPos, minPos, maxPos);

    return freqexQuant(endPos, pfx->m_cEndPosBins, minPos, maxPos);
}

INLINE
Int freqexInvQuantEndPos(CAudioObject *pau, Fex *pfx, Int endPos)
{
    Int minPos = pfx->m_cStart+1;
    Int maxPos = pau->m_cHighCutOff-1;

    if (endPos > maxPos-minPos)
    {
        assert(minPos >= 0);
        return -1;
    }
    return freqexInvQuantMin(endPos, pfx->m_cEndPosBins, minPos, maxPos);
}

INLINE
Int freqexQuantBw(CAudioObject *pau, Fex *pfx, Int iBandwidth)
{
    Int iMinBw = FEX_MINMAXBW;
    Int iMaxBw = pau->m_iSamplingRate / 2;

    return freqexQuant(iBandwidth, pfx->m_cEndPosBins, iMinBw, iMaxBw);
}

INLINE
Int freqexInvQuantBw(CAudioObject *pau, Fex *pfx, Int iIndex)
{
    Int iMinBw = FEX_MINMAXBW;
    Int iMaxBw = pau->m_iSamplingRate / 2;

    return freqexInvQuantCenter(iIndex, pfx->m_cEndPosBins, iMinBw, iMaxBw);
}

INLINE
FexType freqexInvQuantNoiseFloorThresh(Int iIndex)
{
    switch (iIndex)
    {
    case 0: return FEXT_FROM_FLOAT( 0.500f-0.01f ); //   6 dB down
    case 1: return FEXT_FROM_FLOAT( 0.250f-0.01f ); //  12 dB down
    case 2: return FEXT_FROM_FLOAT( 0.125f-0.01f ); //  18 dB down
    case 3: return FEXT_FROM_FLOAT( 0.0f );         // Inf dB down -- any nonzero value is peak
    }

    assert(0);
    return 0;
}

INLINE
Int freqexIndexToMinRunOfZerosForOverlay(const CAudioObject *pau,
                                           const Fex *pfx,
                                           const Int iIndex)
{
    Int iMinRun;

    // minimum run in Hz
    switch (iIndex)
    {
    case 0: iMinRun = 0;    break;
    case 1: iMinRun = 150;  break;
    case 2: iMinRun = 300;  break;
    case 3: iMinRun = 450;  break;
    default: assert(WMAB_FALSE);  iMinRun = 0;
    }

    if (iIndex == 0)
      return 1;

    // convert to # of coeffs using fex tile size & sampling rate
    return max(2, (iMinRun*pfx->m_cTileSize)/(pau->m_iSamplingRate/2));
}
#ifdef BUILD_WMAPROLBRV3
INLINE
Int freqexIndexToMinRunOfZerosForOverlayV3(const CAudioObject *pau,
                                           const Fex *pfx,
                                           const Int iIndex)
{
    Int iMinRun;

    assert( iIndex < 8 );

    // minimum run in Hz
    iMinRun = (iIndex + 1) * 150;
    // convert to # of coeffs using fex tile size & sampling rate
    return max(2, (iMinRun*pfx->m_cTileSize)/(pau->m_iSamplingRate/2));
}

INLINE
Int freqexIndexToMaxRunOfZerosPerBandForOverlayV3(const CAudioObject *pau,
                                                  const Fex *pfx,
                                                  const Int iIndex)
{
    return freqexIndexToMinRunOfZerosForOverlayV3(pau, pfx, iIndex);
}
#endif


#define CHECK_END_POS(endPos) CHECK_VAR0(wmaResult, endPos)

Void freqexSetChannelDependencies(CAudioObject *pau,
                                  CChannelGroupInfo *rgcgi,
                                  Int cChannelGroup,
                                  Int iChSrc);
Void freqexSetStart(CAudioObject *pau, Int iFexStartPos);
Void freqexSetEnd(CAudioObject *pau, Int cSubFrameSampleHalf);
Int freqexSetBandConfig(CAudioObject *pau, Int cBands,
                          Bool bGetMax, Bool bMvBands);
Void freqexSetStartPosChannel(CAudioObject *pau, Int iChCode, Int iChSrc);
Void freqexSetBandConfigChannel(CAudioObject *pau, Int iChCode, Int iChSrc);
Int freqexFindStartPosForOverlay(CAudioObject *pau,
                                 Int iChSrc);

Void freqexGetExpectedMultipliers(const Int  *piFexBandSizesM,
                                  const Int  iMinRatioBandSizeM,
                                  const Bool bUseUniformBands,
                                  UInt *puiExpBandSizeMIndex,
                                  Int  *piExpBandSizeM,
                                  Int  *rgiBandBreakPts);

Void freqexUpdateExpectedBandSizeM( const  Int *rgiBandBreakPts,
                                    const  Int  iActBandSizeM,
                                    const UInt  cMaxBands,
                                          UInt *piExpBandSizeMIndex,
                                           Int *piExpBandSizeM);

Void freqexSetCommonTilePtrs(CAudioObject *pau, ReconTileInfo *prti);
Void freqexSaveCommonTileParams(CAudioObject *pau, ReconTileInfo *prti);
Void freqexRestoreCommonTileParams(CAudioObject *pau, ReconTileInfo *prti);
Void freqexSetPerChTilePtrs(CAudioObject *pau, ReconTileInfo *prti,
                            PerChannelInfo *ppcinfo, 
                            const Int iChSrc);
Void freqexSavePerChTileParams(CAudioObject *pau, ReconTileInfo *prti,
                               PerChannelInfo *ppcinfo, 
                               const Int iChSrc);
Void freqexRestorePerChTileParams(CAudioObject *pau, ReconTileInfo *prti,
                                  PerChannelInfo *ppcinfo,
                                  const Int iChSrc);
Void freqexResetCommonTileParams(CAudioObject *pau, ReconTileInfo *prti);

#ifdef BUILD_WMAPROLBRV2
Void freqexSetBandConfigForMergedMv( CAudioObject *pau,
                                     Int cScaleBands,
                                     Int cMvBands );
Int freqexQuantScaleV2( const Fex *pfx, const Int iStepSize, FastFloat fScale );
FastFloat freqexInvQuantScaleV2( const Fex *pfx, const Int iStepSize, const FastFloat fIndex );
WMARESULT freqexSetLocalParamsFromGlobalParam( CAudioObject *pau, FexGlobalParam *pfxgp );
Int freqexComputeScaleRefV2( Fex *pfx,
                               const CoefType *pfRecon, 
                               const Int cLeftShiftBits );

WMARESULT freqexReconScaleBands( CAudioObject    *pau,
                                 PerChannelInfo  *ppcinfo,
                                 Int             iChSrc );
WMARESULT freqexReconBaseScaleBand( CAudioObject   *pau,
                                    PerChannelInfo *ppcinfo,
                                    Int          iBand,
                                    CoefType       *pfRecon );
WMARESULT freqexSetScaleFacPtrChannel( CAudioObject *pau, PerChannelInfo *ppcinfo, Int iChSrc );
Int freqexSetBaseBandConfig(CAudioObject *pau, Int cBands, Bool bGetMax);

INLINE
Int freqexQuantBwV2(CAudioObject *pau, Int iBandwidth)
{
    return (Int)((pau->m_iSamplingRate / 2 - iBandwidth - FEX_BWRES / 2 + 1) / FEX_BWRES);
}
INLINE
Int freqexInvQuantBwV2(CAudioObject *pau, Int iIndex)
{
    return freqexInvQuantCenter( 0, 1, pau->m_iSamplingRate / 2 - (iIndex + 1) * FEX_BWRES,
                                       pau->m_iSamplingRate / 2 - iIndex * FEX_BWRES );
}
#ifdef BUILD_WMAPROLBRV3
WMARESULT freqexBaseScaleAndAddToRecon( CAudioObject *pau,
                                        PerChannelInfo * ppcinfo,
                                        Int iBand,
                                        CoefType *pfBase,
                                        CoefType *pfRecon );
#endif
#endif // BUILD_WMAPROLBRV2

extern const Int g_rgiFexBandSizesM[];
extern const Int g_rgiFexBandSizesMLinearSlope[];
INLINE
const Int* freqexSetBandSizeM( Bool bScaleBandSplitV2 )
{
#ifdef BUILD_WMAPROLBRV2
    return bScaleBandSplitV2 ? g_rgiFexBandSizesMLinearSlope : g_rgiFexBandSizesM;
#else
    return g_rgiFexBandSizesM;
#endif
}

#define MAX_MV_SHIFT (2)

WMARESULT freqexOffsetPcInfo( CAudioObject *pau, PerChannelInfo *ppcinfo,
                              const Int iSubtile);

Void freqexSetMvConfig( const CAudioObject   * const pau, Fex * const pfx,
                        const PerChannelInfo * const ppcinfo,
                        const Int cBandSize, 
                        const Int bUseNoise,
                        const Int bGetMax);

Bool freqexNeedChCode(CAudioObject *pau, PerChannelInfo *ppcinfo,
                      Int iChSrc);

INLINE
Bool freqexIsChannelIndependent(Fex *pfx, Int iChSrc)
{
    return (((U32)1<<iChSrc) == 
            pfx->m_pau->m_rgpcinfoShr[iChSrc].m_uFxChannelDependencyMask);
}

INLINE
Bool freqexCheckLastCodedIndex( const CoefType *rgctCoef, 
                                const Int iLastCodedIndex,
                                const Int cSubframeSize )
{
    Int i;

    if (iLastCodedIndex <= 1)
        return WMAB_TRUE;

    if (iLastCodedIndex >= 1)
        if( rgctCoef[iLastCodedIndex-1] == 0 )
            return WMAB_FALSE;
    for (i=iLastCodedIndex; i < cSubframeSize; i++)
        if( rgctCoef[i] != 0 )
            return WMAB_FALSE;
    return WMAB_TRUE;
}

INLINE
Bool freqexCheckLastCodedIndexI32( const I32 *rgiCoef, 
                                   const Int iLastCodedIndex,
                                   const Int cSubframeSize )
{
    Int i;

    if (iLastCodedIndex <= 1)
        return WMAB_TRUE;

    if (iLastCodedIndex >= 1)
        if (rgiCoef[iLastCodedIndex-1] == 0)
            return WMAB_FALSE;
    for (i=iLastCodedIndex; i < cSubframeSize; i++)
        if (rgiCoef[i] != 0)
            return WMAB_FALSE;
    return WMAB_TRUE;
}

Void freqexInvSplitRecon( const Fex *pfx, CoefType *pfRecon,
                          const PerChannelInfo *ppcinfo );

Void freqexDumpConfig(CAudioObject *pau, Fex *pfx, Int iSubframe);
Void freqexDumpBandConfigCfg(Fex *pfx, Int iConfig, PerChannelInfoShr *pcis);
Void freqexDumpBandConfig(Fex *pfx);

Void freqexExpVec(CoefType *pfCb, const CoefType *pfSrc, const Int iLen,
                                  const FexType fExp   , const Int iSign
#ifdef BUILD_INTEGER
                                , const I32 lshift     , const Bool bNoise 
#endif
                            );


WMARESULT freqexReconBand( CAudioObject *pau,
                           PerChannelInfo *ppcinfo,
                     const Int iBand,
                           CoefType *pfRecon,
                     const CoefType *pfLowband,
                     const QuantStepType fGlobalQ );

WMARESULT freqexRecon( CAudioObject   *pau,
                       PerChannelInfo *ppcinfo,
                       Int            iChSrc,
                 const QuantStepType   fGlobalQ );

INLINE
Void freqexSetNeedMvCoding(Fex *pfx,
                           const PerChannelInfo *ppcinfo,
                           const Int iBand,
                           const Int iActLen)
{
    if (pfx->m_iVersion == 1 || pfx->m_bV1Compatible)
    {
        assert(pfx->m_cScaleBands == pfx->m_cMvBands);
        pfx->m_bNeedMvCoding =
            (2*ppcinfo->m_piFexLogScaleFacIndex[iBand] >= 2*pfx->m_iMvThreshold+1);
    }
    else if (pfx->m_bReconDomain || (iActLen > 0 && !pfx->m_bScFacIntraPredNoRef))
    {
        pfx->m_bNeedMvCoding = WMAB_TRUE;
    }
    else if (pfx->m_cScaleBands == pfx->m_cMvBands)
    {
        pfx->m_bNeedMvCoding =
            (2*ppcinfo->m_piFexLogScaleFacIndex[iBand]
                *pfx->m_rgGlobalParam[FexCodingGlobalParamFrame].m_iScFacStepSize >= 2*pfx->m_iMvThreshold+1);
    }
    else
    {
        Int i, iScBandStart;
        for (i = iScBandStart = 0; i < iBand ; i++)
            iScBandStart += pfx->m_rgcScaleBandsPerMvBand[i];
        pfx->m_bNeedMvCoding = WMAB_FALSE;
        for (i = 0; i < pfx->m_rgcScaleBandsPerMvBand[iBand]; i++)
        {
            pfx->m_bNeedMvCoding |=
                (2*ppcinfo->m_piFexLogScaleFacIndex[iBand]
                  *pfx->m_rgGlobalParam[FexCodingGlobalParamFrame].m_iScFacStepSize >= 2*pfx->m_iMvThreshold+1);
        }
    }
}

typedef enum {
    ClearBuf = 0,
    CopyBuf,
    AddToBuf,
    AvgBuf
} FexBufOp;

Void freqexBufOps(CAudioObject *pau, const FexBufOp bufOp, const Int nVals,
                  CoefType *dst, CoefType *src, const Int iLen);

Int freqexKeepPeaks(Fex *pfx, 
                      const CoefType *pVec, 
                      const CoefType *pfRecon,
                      U8 *pMask, const Int iLen,
                      const Bool bRev,
                      const Int iRecLen,
                      Int *piCbStart,
                      const I32 cLeftShiftBits,
                      Int *piActLen);

FastFloat freqexGetMvBandScale( Fex      *pfx,
                          const CoefType *pVec, 
                          const CoefType *pfRecon,
                          const Int       iLen,
                          const FexType   fExp,
                          const Bool      fRev,
                          const Int       iRecLen,
                                Int      *piCbStart,
                                Int       lshift );

FastFloat freqexGetMvBandScaleWithMask( Fex *pfx,
                                    const CoefType *pVec, 
                                    const CoefType *pfRecon,
                                    const U8 *pucMask, 
                                    const Int iLen,
                                    const Bool bRev,
                                    const Int iRecLen,
                                          Int *piCbStart,
                                          Int lshift );

#ifdef FEX_GET_MV_SCALE_C_OPT
void freqexGetMvBandScaleLoop(const CoefType *pVec, const Int iLen, Int j0, Int i0, 
	I32 rshift, I64 *pfScale, const FexType fExp, Bool bRev);

CoefType computeMaxCoef(const CoefType *pVec, const Int iLen);
#endif

#ifdef FEX_SCALE_BAND_C_OPT
#if WMA_OPT_FEX_SCL_BAND_OPT_ARM
void freqexScaleBandUpdateFlags(const U8 *pucMask, Bool *bFlags,
                                       const Int iLen);
#endif
void freqexScaleBandLoop(const CoefType *pVec, CoefType *pfRecon, const U8 *pucMask,   
	const Int iCwSign, const FexType fExp, FastFloat *pfBandScale1, Int * piAccumRshift,          
	const Bool bNoise, Int * plshift, 
	const Int iStart, const Int iEnd, Int k, const Int iStep);
#endif	// FEX_SCALE_BAND_C_OPT

INLINE
Int freqexGetValidLength(Fex *pfx, const CoefType *pfRecon, const Int iLen)
{
    Int iLenAct = 0;
    Int i;

    for (i=0; i < iLen; i++)
    {
        if (IS_VALID_FEXPT())
        {
            iLenAct++;
        }
    }

    return iLenAct;
}

Int freqexComplementMask(U8 *pMask, Int iLen);
Void freqexRemovePeaksFromNoise(CoefType *pVec, const U8* pMask, Int iLen);

// ====================================================================

// insert elem into array of size curSize, sort ascending
INLINE
Void freqexInsertSort( CoefType *pf, const CoefType fElem, const Int iCurSize )
{
    Int i, j;

    for (i=0; i <= iCurSize; i++)
    {
        if (i==iCurSize || fElem<=pf[i]) // found place to insert
        {
            // shift everything to the right, start from end
            for (j=iCurSize-1; j >= i; j--)
            {
                pf[j+1] = pf[j];
            }
            pf[i] = fElem; // insert new
            break;
        }
    }
}

INLINE
Void freqexInsertSort4( CoefType *pf, const CoefType fElem )
{
    if (fElem<pf[0])
    {
        pf[4] = pf[3];
        pf[3] = pf[2];
        pf[2] = pf[1];
        pf[1] = pf[0];
        pf[0] = fElem;
        return;
    }
    if (fElem<pf[1])
    {
        pf[4] = pf[3];
        pf[3] = pf[2];
        pf[2] = pf[1];
        pf[1] = fElem;
        return;
    }
    if (fElem<pf[2])
    {
        pf[4] = pf[3];
        pf[3] = pf[2];
        pf[2] = fElem;
        return;
    }
    if (fElem<pf[3])
    {
        pf[4] = pf[3];
        pf[3] = fElem;
        return;
    }
    pf[4] = fElem;
}

INLINE
WMARESULT freqexRemoveSort( CoefType *pf, const CoefType fElem, const Int iCurSize )
{
    Int i, j;

    for (i=0; i < iCurSize; i++)
    {
        if (pf[i] == fElem)
        {
            for (j=i; j < iCurSize; j++)
            {
                pf[j] = pf[j+1];
            }
            return WMA_OK;
        }
    }
    assert(WMAB_FALSE);
    return WMA_E_FAIL;
}

INLINE
WMARESULT freqexRemoveSort5( CoefType *pf, const CoefType fElem )
{
    if (pf[0] == fElem)
    {
        pf[0] = pf[1];
        pf[1] = pf[2];
        pf[2] = pf[3];
        pf[3] = pf[4];
        return WMA_OK;
    }
    if (pf[1] == fElem)
    {
        pf[1] = pf[2];
        pf[2] = pf[3];
        pf[3] = pf[4];
        return WMA_OK;
    }
    if (pf[2] == fElem)
    {
        pf[2] = pf[3];
        pf[3] = pf[4];
        return WMA_OK;
    }
    if (pf[3] == fElem)
    {
        pf[3] = pf[4];
        return WMA_OK;
    }
    return WMA_OK;
}

INLINE CoefType freqexMedian( const CoefType *pVec, const Int iLen )
{
    if (iLen % 2 == 0) // even length
        return ( (pVec[iLen/2-1]+pVec[iLen/2]) / 2 );   // Fixed wrong operator association. Should be ave of the two. Hui Gao. 
    else
        return ( pVec[(iLen-1)/2] );
}

// =======================================================================

// IMPORTANT: Don't call these functions twice within loop, i.e., don't do
// for (iCh=...) { set(...) for (iCh2=...) { set(...) } }
// since this will overwrite variables
INLINE
Void freqexSetChannelConfigCfg( Fex *pfx, const Int iCfg )
{
    PerChannelInfoShr *pcis = pfx->m_pau->m_rgpcinfoShr + pfx->m_iChSrc;

    pfx->m_cScaleBands = pcis->m_iFxScaleBands;
    pfx->m_cMvBands    = pcis->m_iFxMvBands;
    pfx->m_piBandSizeM = pfx->m_rgiBandSizeM + pfx->m_cMaxBands*iCfg;
}

Void freqexSetLastCodedIndex(CAudioObject *pau, Int iChCodeSrc);

INLINE
Void freqexSetChannelConfig(CAudioObject *pau, PerChannelInfo *ppcinfo,
                            const Int iChCode, const Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    PerChannelInfoShr *pcis = ppcinfo->m_ppcinfoShr;

    pfx->m_iChCode = iChCode;
    pfx->m_iChSrc = iChSrc;
    pfx->m_iChCfg = pcis->m_iFxBandConfig;
    if (pfx->m_iIteration != 0)
        freqexSetLastCodedIndex(pau, iChSrc);
    freqexSetChannelConfigCfg( pfx, pcis->m_iFxBandConfig );
    freqexSetBandConfigChannel(pau, iChCode, iChSrc);
}

Void freqexSetBandParams( CAudioObject   * const pau,
                    const PerChannelInfo * const ppcinfo,
                    const Int iChCode    , const Int iBand );

// ======================================================================

INLINE
Void freqexCopyMvState( PerChannelInfo *ppcinfoDst, 
                  const PerChannelInfo *ppcinfoSrc,
                  const Int iBand )
{
    ppcinfoDst->m_piFexCb  [iBand] = ppcinfoSrc->m_piFexCb  [iBand];
    ppcinfoDst->m_pFexExp  [iBand] = ppcinfoSrc->m_pFexExp  [iBand];
    ppcinfoDst->m_piFexMv  [iBand] = ppcinfoSrc->m_piFexMv  [iBand];
    ppcinfoDst->m_piFexMv2 [iBand] = ppcinfoSrc->m_piFexMv2 [iBand];
    ppcinfoDst->m_piFexSign[iBand] = ppcinfoSrc->m_piFexSign[iBand];
    ppcinfoDst->m_pbFexRev [iBand] = ppcinfoSrc->m_pbFexRev [iBand];
}

// ====================================================================

INLINE
Void freqexSetMvType(Fex *pfx)
{
    PerChannelInfoShr *pcis = pfx->m_pau->m_rgpcinfoShr + 0;

    if (pcis->m_eFxMvRangeType == MvRangeFullNoOverwriteBase ||
        pcis->m_eFxMvRangeType == MvRangeFullOverwriteBase)
        pfx->m_bMvRangeFull = WMAB_TRUE;
    else
        pfx->m_bMvRangeFull = WMAB_FALSE;

    if (pcis->m_eFxMvRangeType == MvRangeFullOverwriteBase)
        pfx->m_bOverwriteBase = WMAB_TRUE;
    else
        pfx->m_bOverwriteBase = WMAB_FALSE;
}

// ======================================================================

INLINE
PerChannelInfoShr* freqexGetNextAvailChannel(CAudioObject *pau,
                                             Int *piMinCh, U32 uMask)
{
    while ((uMask & (1<<*piMinCh)) == 1)
        *piMinCh = *piMinCh + 1;

    return pau->m_rgpcinfoShr + pau->m_fex.m_rgiChCode[*piMinCh];
}
 
// ======================================================================

INLINE
Void freqexCopyBandConfig(PerChannelInfoShr *pcisDst,
                          PerChannelInfoShr *pcisSrc)
{
    pcisDst->m_iFxBandConfig = pcisSrc->m_iFxBandConfig;

    pcisDst->m_bFxUseUniformBands = pcisSrc->m_bFxUseUniformBands;
    pcisDst->m_bFxArbitraryBandConfig = pcisSrc->m_bFxArbitraryBandConfig;

    pcisDst->m_iFxScaleBands = pcisSrc->m_iFxScaleBands;
    pcisDst->m_iFxMvBands = pcisSrc->m_iFxMvBands;
}

INLINE
Float freqexGetBestSignError(const Int iLen, const Float err,
                             Int *piBestSign)
{
    // rearranged to simplify the calculation
    if (piBestSign == NULL) return (iLen - err);

    if (err >= 0.0f)
    {
        *piBestSign = 1;
        return (iLen - err);
    }
    else
    {
        *piBestSign = -1;
        return (iLen + err);
    }
 }

// ======================================================================

Void freqexSetScBins(Fex *pfx);
Void freqexSetMvBins(Fex *pfx);
Bool freqexSetBandSizes(Int *cBandSizes, Int iCoeffs, Int iTotal,
                        Int iMinBandSize, Int iMaxBandSize,
                        Int cBands, Int *pcBands, Bool bSort,
                        Bool bAllowZeroBandSizes);
Int freqexSetBandConfigLoop(Int cBands, Bool bGetMax, Int cStart, Int cEnd,
                              Int *piBandSizes, Int iMinBandSize, Int iMaxBandSize,
                              Bool bArbitraryBandConfig, Bool bUseUniformBands,
                              const Int *piBandSizeM,
                              Int cNumBandsBelowLastCodedIndex,
                              Int *piFirstBandStartPosAfterLastCodedIdx);

#define ABSSQRT(x) ((CoefType)((x) >= 0 ? sqrt(x) : -sqrt(-(x))))
#define ABSSQR(x)  ((CoefType)((x) >= 0 ? (x)*(x) : -((x)*(x))))
#define ABSPOW(v, x) ((CoefType)((x) >= 0 ? pow(v, (x)) : -pow(v, -(x))))

Float freqexGetPhase(const CoefType *pVecDCT,
                     const CoefType *pVecDST,
                     const Int      iLen,
                     const Bool     bRev,
                     const Int      iRecLen,
                     Int            *piCbStart,
                     Float          *pfTotalDCT,
                     Float          *pfTotalDST);

#ifdef __cplusplus
}
#endif

#endif // BUILD_WMAPROLBRV1

#endif // __FEX_H_
