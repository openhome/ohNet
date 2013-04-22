//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Pro. Not needed for WMA Std or Lossless.
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    MsAudio.cpp

Abstract:

    Implementation of public member functions for CAudioObject.

Author:

    Wei-ge Chen (wchen) 11-March-1998

Revision History:


*************************************************************************/

// Print out the target we're building for
#define COMMONMACROS_OUTPUT_TARGET

#if !defined (_WIN32_WCE) && !defined (HITACHI)
#include <time.h>
#endif  // _WIN32_WCE

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include "msaudio.h"
#include "AutoProfile.h"
#include "macros.h"
#include "float.h"
#include "wavfileexio.h"
#include "drccommon.h"

#if defined (BUILD_WMAPRO)

Void prvDeleteBarkResampleMatrix(CAudioObject* pau)
{
    if (pau->m_rgrgrgnBarkResampleMatrix) {
        Int iWin0, iWin1;
        for (iWin0 = 0; iWin0 < pau->m_cPossibleWinSize; iWin0++) {
            if (pau->m_rgrgrgnBarkResampleMatrix[iWin0]) {
                for (iWin1 = 0; iWin1 < pau->m_cPossibleWinSize; iWin1++) {
                    DELETE_ARRAY (pau->m_rgrgrgnBarkResampleMatrix [iWin0][iWin1]);
                }
                DELETE_ARRAY (pau->m_rgrgrgnBarkResampleMatrix [iWin0]);
            }
        }
        DELETE_ARRAY (pau->m_rgrgrgnBarkResampleMatrix);
    }
}

// Allocate mask resample matrices.
WMARESULT prvAllocateBarkResampleMatrix(CAudioObject* pau)
{
    WMARESULT wmaResult = WMA_OK;

#if !defined (DEBUG_PRINT_BARK_NMR)
    if (pau->m_iVersion > 2)
#endif
    {
        pau->m_rgrgrgnBarkResampleMatrix = (U8***) auMalloc (sizeof (U8**) * pau->m_cPossibleWinSize);
        if (pau->m_rgrgrgnBarkResampleMatrix == NULL) {
            wmaResult = TraceResult (WMA_E_OUTOFMEMORY);
            goto exit;
        } else {
            Int iWin0, iWin1;
            memset(pau->m_rgrgrgnBarkResampleMatrix, 0, sizeof (U8**) * pau->m_cPossibleWinSize);

            for (iWin0 = 0; iWin0 < pau->m_cPossibleWinSize; iWin0++) {
                pau->m_rgrgrgnBarkResampleMatrix[iWin0] = (U8**) auMalloc (sizeof (U8*) * pau->m_cPossibleWinSize);
                if (pau->m_rgrgrgnBarkResampleMatrix[iWin0] == NULL) {
                    wmaResult = TraceResult (WMA_E_OUTOFMEMORY);
                    goto exit;
                }
                memset(pau->m_rgrgrgnBarkResampleMatrix[iWin0], 0, sizeof (U8*) * pau->m_cPossibleWinSize);

                for (iWin1 = 0; iWin1 < pau->m_cPossibleWinSize; iWin1++) {
                    pau->m_rgrgrgnBarkResampleMatrix[iWin0][iWin1] = (U8*) auMalloc (sizeof (U8) * NUM_BARK_BAND);
                    if (pau->m_rgrgrgnBarkResampleMatrix[iWin0][iWin1] == NULL) {
                        wmaResult = TraceResult (WMA_E_OUTOFMEMORY);
                        goto exit;
                    }
                    memset(pau->m_rgrgrgnBarkResampleMatrix[iWin0][iWin1], 0, sizeof (U8) * NUM_BARK_BAND);
                }
            }
        }
    }
exit:
    return wmaResult;
}

Void prvSetSubWooferCutOffs (CAudioObject* pau)
{
    Int iWin;
    const Float fltSubWooferCutOffHz = 220.0F;
    const Float fltSamplingPeriod = 1.0F / pau->m_iSamplingRate;
    Int iIndex;

    // Should it be aligned to Bark boundaries? To be determined

    for (iWin = 0; iWin < pau->m_cPossibleWinSize; iWin++)    {
        Int cFrameSample = pau->m_cFrameSample / (1 << iWin);
        iIndex = (Int) ceil((fltSubWooferCutOffHz * cFrameSample * fltSamplingPeriod) + 0.5F); // Should they be multiple of 2, or 4 or such?
        iIndex = max(4, iIndex); // Minimum of 4 coeffs
        pau->m_rgcSubWooferCutOffIndex [iWin] = min(iIndex, cFrameSample/2);
        //WMAFprintf(stdout, "Cuttoff[%d] = %d\n", iWin, pau->m_rgcSubWooferCutOffIndex [iWin]);
    }
    pau->m_cSubWooferCutOffIndex = pau->m_rgcSubWooferCutOffIndex[0];
} // prvSetSubWooferCutOffs


#ifdef BUILD_INTEGER
Int qstCalcLog2QuantStepModifier(Int iQSS) 
{
#if 0 // if want to save table size, can simply use this
    return Log2FromFastFloat(qstCalcQuantStep(iQSS, 0));
#else
    //assert(iQSS < INTEGER_DBPOWER_TABLE_SIZEV3);
    if (iQSS >= INTEGER_DBPOWER_TABLE_SIZEV3) {
        return 30;
    }
    if (iQSS >= 0 &&
        iQSS < DBPOWER_TABLE_SIZEV3) {
        return g_rgiLog2DBPower10V3[iQSS];
    }
    else { // unusual cases
        return Log2FromFastFloat(qstCalcQuantStep(iQSS, 0));
    }
#endif // 0
}
#endif // BUILD_INTEGER


//*****************************************************************************************
//
// prvWeightedModifiedQuantization
// calculate 10^( (MaskQ-MaxMaskQ)* iMaskQuantMultiplier / 20 ) * 10^( QuantStepSize/20 ) * 10^(QuantStepModifier/20)
//         = (10^(iMaskQuantMultiplier/20))^( MaskQ-MaxMaskQ )     * (10^(1/20)^QuantStepSize * (10^(1/20)^QuantStepModifier 
//*****************************************************************************************
QuantFloat prvWeightedModifiedQuantizationV3(CAudioObject *pau, PerChannelInfo *ppcinfo, Int iBark, U8 fMaskUpdate)
{
    Int iIndex = 0;
    QuantFloat qfltRMS;

    if (fMaskUpdate) {
        iIndex = (ppcinfo->m_iMaxMaskQ - ppcinfo->m_rgiMaskQ[iBark]) * ppcinfo->m_iMaskQuantMultiplier;
    } else {
        iIndex = (ppcinfo->m_iMaxMaskQ - ppcinfo->m_rgiMaskQResampled[iBark]) * ppcinfo->m_iMaskQuantMultiplier;
    }
    // disable the assert,
    // since the mask values created by base peak coding may violate the assumption
//    assert( 0 <= iIndex );
    assert(ppcinfo->m_iMaskQuantMultiplier < 5);
    assert(ppcinfo->m_iMaskQuantMultiplier > 0);
    // m_ucQuantStepModifierIndex: 0..32, 
    // m_iQuantStepSize: 1..255
    // iIndex : 0..(60 dpcmerr/bark * 28 barks * 4 multiplier * 2 mask quant): 0..13440
    // Reasonble range: -x..286?
    qfltRMS = qstCalcQuantStep( ((Int)ppcinfo->m_ucQuantStepModifierIndex) + pau->m_iQuantStepSize -iIndex, ppcinfo->m_cLeftShiftBitsQuant );

    MONITOR_RANGE(gMR_WeightRatio,qfltRMS);

    return qfltRMS;
}


INLINE I32 LOG2_64(I64 i)
{   // returns n where n = log2(2^n) = log2(2^(n+1)-1)
    I32 iLog2 = 0;
    assert (i != 0);

    while ((i >> iLog2) > 1)
        iLog2++;

    return iLog2;
}

INLINE I32 LOG2CEIL_64(I64 i)
{   
    I32 iLog2 = 0;
    assert (i != 0);

    while (((I64)1 << iLog2) < i)
        iLog2++;

    return iLog2;
}

Void auCheckForOverflowSamp(CoefType rgiCoef,
                            CoefType iMaxOutputAllowed)
{
    if (rgiCoef > iMaxOutputAllowed ||
        rgiCoef < -iMaxOutputAllowed)
    {
        assert(WMAB_FALSE);
    }
}

Void auCheckForOverflowCh(CoefType *rgiCoef, Int cSubbandAdjusted,
                          CoefType iMaxOutputAllowed,
                          CoefType iLog2MaxOutputAllowed)
{
    I32 i;

    for (i=0; i < cSubbandAdjusted; i++)
    {
        if (rgiCoef[i] > iMaxOutputAllowed ||
            rgiCoef[i] < -iMaxOutputAllowed)
        {
            assert(WMAB_FALSE);
        }
    }
}

Void auCheckForOverflow(CAudioObject *pau,
                        CoefType iMaxOutputAllowed,
                        CoefType iLog2MaxOutputAllowed)
{
    I32 iCh;
    PerChannelInfo *ppcinfo;

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        ppcinfo = &pau->m_rgpcinfo[pau->m_rgiChInTile[iCh]];
        auCheckForOverflowCh((CoefType*)ppcinfo->m_rgiCoefRecon,
                             ppcinfo->m_cSubFrameSampleHalf,
                             iMaxOutputAllowed, iLog2MaxOutputAllowed);
    }
}

#ifdef BUILD_WMAPROLBRV2

WMARESULT auPreScaleCoeffsLBR ( CAudioObject  * const pau,
                          const ReconTileInfo * const prti )
{
#if defined( BUILD_INTEGER )

    CoefType * const pBuf = pau->m_rgCoefXFormMCLT;

    const Int cSize = prti->m_iSizeCurr;

    Int i, shift = 0;
    CoefType maxCoef = 0;

    //if( !pau->m_bUseDynamicIntegerPrec ) return WMA_OK;

    for( i=0; i < 2*cSize; ++i )
        maxCoef |= COEF_ABS( pBuf[i] );

    if( 0 < maxCoef ) shift = (Int)( LOG2MAX32BITVAL - LOG2((U32)maxCoef) - LOG2(cSize) );

    pau->m_cLeftShiftBitsMCLT = shift;

    if( shift > 0 ) for( i=0; i < 2*cSize; ++i ) pBuf[i] <<=  shift;
    if( shift < 0 ) for( i=0; i < 2*cSize; ++i ) pBuf[i] >>= -shift;

#endif
    return WMA_OK;
}

WMARESULT auPostScaleCoeffsLBR( CAudioObject  * const pau,
                          const ReconTileInfo * const prti )
{
#if defined( BUILD_INTEGER )

    CoefType * const pBuf = pau->m_rgCoefXFormMCLT;

    const Int shift = pau->m_cLeftShiftBitsMCLT;
    const Int cSize = prti->m_iSizeCurr;

    Int i;

    pau->m_cLeftShiftBitsMCLT = 0;

    //if( !pau->m_bUseDynamicIntegerPrec ) return WMA_OK;

    if( shift > 0 ) for( i=0; i< cSize; ++i ) pBuf[i] >>=  shift;
    if( shift < 0 ) for( i=0; i< cSize; ++i ) pBuf[i] <<= -shift;

#endif
    return WMA_OK;
}

#endif

#if !(defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_SCALE_COEFFS_V3))
// Prescale coefficients before a block, iMaxInputAllowed is maximum block
// can take without overflowing.


#if !WMA_OPT_SCALE_COEFFS_V3_ARM

WMARESULT auPreScaleCoeffsV3(CAudioObject *pau,
                             CoefType iLog2MaxOutputAllowed,
                             Bool fUseQuantStep,
                             Bool fUseGlobalScale, char c )
{
#if defined(BUILD_INTEGER)
    I32 iCh, iHi, iRecon;
    PerChannelInfo *ppcinfo;
    CoefType *rgiCoefRecon;
    I32 cLeftShiftBits, cLeftShiftBitsMin;

    //static int count = 0;

    // prescale occurs in frequency domain always
    iHi = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;

    cLeftShiftBitsMin = 64;
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        I64 ctMaxVal = 0;
        ppcinfo = &pau->m_rgpcinfo[pau->m_rgiChInTile[iCh]];
        rgiCoefRecon = ppcinfo->m_rgiCoefRecon;

        if (ppcinfo->m_bNoDecodeForCx)
            continue;

        // find max value
        for (iRecon=0; iRecon < iHi; iRecon++)
            ctMaxVal |= COEF_ABS( rgiCoefRecon[iRecon] );

        if (fUseQuantStep == WMAB_TRUE) 
        {
            const QuantFloat maxQuantStep = ppcinfo->m_qfltMaxQuantStep;

            // ctMaxVal = ceil((a*b)/c)  = (a*b + (c-1))/c
            ctMaxVal  *=     maxQuantStep.iFraction;
            ctMaxVal  += (1<<maxQuantStep.iFracBits)-1;
            ctMaxVal >>=     maxQuantStep.iFracBits;
        }

        if (ctMaxVal == 0)
            cLeftShiftBits = 0;
        else    
            cLeftShiftBits = (I32)(iLog2MaxOutputAllowed - LOG2CEIL_64(ctMaxVal));

        // if cLeftShiftBits is positive and small, avoid doing some work.
        // disabled due to QL1 failure on 6 channel 24bits cases. Hui Gao. 
//        if( 0 < cLeftShiftBits && 3 > cLeftShiftBits )
//            cLeftShiftBits = 0;

        if (cLeftShiftBits<cLeftShiftBitsMin && ctMaxVal!=0)
            cLeftShiftBitsMin = cLeftShiftBits;

        if (!fUseGlobalScale) {
            ppcinfo->m_cLeftShiftBitsTotal += cLeftShiftBits;

            if (cLeftShiftBits > 0)
              for (iRecon=0; iRecon < iHi; iRecon++)
                rgiCoefRecon[iRecon] <<= cLeftShiftBits;
            else if (cLeftShiftBits < 0)
              for (iRecon=0; iRecon < iHi; iRecon++) {
                // rounding makes no real diff.
                //rgiCoefRecon[iRecon] += 1<<(-cLeftShiftBits-1);
                rgiCoefRecon[iRecon] >>= -cLeftShiftBits;
              }
        }
        //count++;
    }
    if (fUseGlobalScale) {
        cLeftShiftBits = cLeftShiftBitsMin;
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            const Int iChSrc = pau->m_rgiChInTile[iCh];
            ppcinfo = &pau->m_rgpcinfo[iChSrc];
            iHi = pau->m_rgpcinfo[iChSrc].m_cSubbandAdjusted;
            rgiCoefRecon = ppcinfo->m_rgiCoefRecon;

            // m_rgiCoefRecon can be NULL ( under CX_DECODE_MONO )
            // if this is the case, skip the shift adjustment for
            // un-allocated CoefRecon buffers.

            if( NULL == rgiCoefRecon ) continue;

            ppcinfo->m_cLeftShiftBitsTotal += cLeftShiftBits;

            if (cLeftShiftBits > 0)
                for (iRecon=0; iRecon < iHi; iRecon++)
                    rgiCoefRecon[iRecon] <<= cLeftShiftBits;
            else if (cLeftShiftBits < 0)
                for (iRecon=0; iRecon < iHi; iRecon++) {
                    //rgiCoefRecon[iRecon] += 1<<(-cLeftShiftBits-1);
                    rgiCoefRecon[iRecon] >>= -cLeftShiftBits;
                }
        }
    }

    //printf( "%c %i\n", c, cLeftShiftBits );

    return WMA_OK;
#else
    return WMA_OK;
#endif
}
#endif //WMA_OPT_SCALE_COEFFS_V3_ARM
#endif //WMA_TARGET_MIPS && PLATFORM_SPECIFIC_SCALE_COEFFS_V3

WMARESULT auPreScaleQuantV3(CAudioObject *pau,
                            Bool fUseGlobalQuantScale)
{
#ifdef BUILD_INTEGER
    Int iCh, iBark, iIndex;
    PerChannelInfo *ppcinfo;
    CoefType *rgiCoefRecon;
    const Int *rgiBarkIndex;
    U8 fMaskUpdate;
    Int iMinIndex, iMaxIndex, iMaxIndexTile;
    Int cLeftShiftBitsQuantMin;

    rgiBarkIndex = pau->m_rgiBarkIndex;

    iMaxIndexTile = -100000;
    cLeftShiftBitsQuantMin = 100;
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        ppcinfo = &pau->m_rgpcinfo[pau->m_rgiChInTile[iCh]];
        rgiCoefRecon = ppcinfo->m_rgiCoefRecon;
        fMaskUpdate = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0];

        iMinIndex = 100000;
        iMaxIndex = -100000;
        for (iBark = 0; iBark < pau->m_cValidBarkBand; iBark++)
        {
            if (fMaskUpdate)
                iIndex = (ppcinfo->m_iMaxMaskQ - ppcinfo->m_rgiMaskQ[iBark]) * ppcinfo->m_iMaskQuantMultiplier;
            else
                iIndex = (ppcinfo->m_iMaxMaskQ - ppcinfo->m_rgiMaskQResampled[iBark]) * ppcinfo->m_iMaskQuantMultiplier;
            if (((Int)ppcinfo->m_ucQuantStepModifierIndex - iIndex + pau->m_iQuantStepSize) < iMinIndex)
                iMinIndex = pau->m_iQuantStepSize + ppcinfo->m_ucQuantStepModifierIndex - iIndex;
            if (((Int)ppcinfo->m_ucQuantStepModifierIndex - iIndex + pau->m_iQuantStepSize) > iMaxIndex)
                iMaxIndex = pau->m_iQuantStepSize + ppcinfo->m_ucQuantStepModifierIndex - iIndex;
        }

        iMinIndex = max(0, iMinIndex);
        ppcinfo->m_cLeftShiftBitsQuant = qstCalcLog2QuantStepModifier(iMinIndex);
        assert(ppcinfo->m_cLeftShiftBitsQuant >= 0);

#if 0 // don't remove common scale factor -- may work for 16 bits, but not 24
        ppcinfo->m_cLeftShiftBitsQuant = 0;
#endif

        if (ppcinfo->m_cLeftShiftBitsQuant < cLeftShiftBitsQuantMin)
            cLeftShiftBitsQuantMin = ppcinfo->m_cLeftShiftBitsQuant;
        if (iMaxIndex > iMaxIndexTile)
            iMaxIndexTile = iMaxIndex;

        ppcinfo->m_qfltMaxQuantStep =
          qstCalcQuantStep(iMaxIndex, ppcinfo->m_cLeftShiftBitsQuant);
    }

    if (fUseGlobalQuantScale) {
        QuantStepType qfltMaxQuantStep =
          qstCalcQuantStep(iMaxIndexTile, cLeftShiftBitsQuantMin);
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
            ppcinfo = &pau->m_rgpcinfo[pau->m_rgiChInTile[iCh]];
            ppcinfo->m_cLeftShiftBitsQuant = cLeftShiftBitsQuantMin;
            ppcinfo->m_qfltMaxQuantStep = qfltMaxQuantStep;
        }
    }
#endif

    return WMA_OK;
}

#if !WMA_OPT_SCALE_COEFFS_V3_ARM
WMARESULT auPostScaleCoeffsV3(CAudioObject *pau)
{
#ifdef BUILD_INTEGER
    Int iCh, iRecon;
    PerChannelInfo *ppcinfo;
    CoefType *rgiCoefRecon;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        ppcinfo = &pau->m_rgpcinfo[pau->m_rgiChInTile[iCh]];
        rgiCoefRecon = ppcinfo->m_rgiCoefRecon;

        if (ppcinfo->m_bNoDecodeForCx)
            continue;

        ppcinfo->m_cLeftShiftBitsTotal -= ppcinfo->m_cLeftShiftBitsQuant;
        ppcinfo->m_cLeftShiftBitsTotal -= pau->m_cLeftShiftBitsFixedPost;
        if (ppcinfo->m_cLeftShiftBitsTotal > 0)
        {
            for (iRecon = 0; iRecon < ppcinfo->m_cSubbandAdjusted; iRecon++)
            {
                //rgiCoefRecon[iRecon] += 1<<(ppcinfo->m_cLeftShiftBitsTotal-1);
                rgiCoefRecon[iRecon] >>= ppcinfo->m_cLeftShiftBitsTotal;
            }
        }
        else if (ppcinfo->m_cLeftShiftBitsTotal < 0)
        {
            for (iRecon = 0; iRecon < ppcinfo->m_cSubbandAdjusted; iRecon++)
                rgiCoefRecon[iRecon] <<= -ppcinfo->m_cLeftShiftBitsTotal;
        }

        //printf( "P %i\n", ppcinfo->m_cLeftShiftBitsTotal );

        ppcinfo->m_cLeftShiftBitsTotal = 0;
        ppcinfo->m_cLeftShiftBitsQuant = 0;
    }

    return WMA_OK;
#else
   return WMA_OK;
#endif
}

///*****************************************************************************************
//
// auInvWeightSpectrumV3  - Integer or IntFloat Version (Untested on Integer)
//
//*****************************************************************************************
// This method multiplies with modified step size, resampled mask, quantstepsize. 
// This method can be moved to msaudiodec.c, but all the integerization macros are not available 
// there :-(
// pass in fMaskUpdate so that enc/dec can both call it; but will be unnecessary when
// make move the func to dec as suggested above. --wchen 5/14/2002
WMARESULT auInvWeightSpectrumV3 (CAudioObject* pau, 
                                 PerChannelInfo* ppcinfo,
                                 U8 fMaskUpdate)
{
    WMARESULT   wmaResult = WMA_OK;

    CoefType* rgiCoefRecon   = (CoefType*) ppcinfo->m_rgiCoefRecon;
    Int cValidBarkBand;
    Int iBark = 0;
    I32 iRecon = 0;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    const Int *rgiBarkIndex;
    I32 iHighCutOff = 0;
    I32 iLo, iHi;
    QuantFloat qfltQuantizer;   // eithe a FastFloat or a Float, as appropriate to the build.
    Bool fPrint = WMAB_FALSE;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif

    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);
    assert (0 != ppcinfo->m_cSubFrameSampleHalf);
    DEBUG_BREAK_AT_FRAME_DECODE;

    if (ppcinfo->m_cSubFrameSampleHalfWithUpdate <= 0 || 
        ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    // Assume new mask always available (either resampled or freshly decoded)
    rgiBarkIndex = pau->m_rgiBarkIndex;

    cValidBarkBand = pau->m_cValidBarkBand;

    //// DEBUG NOTES below are preceeded by four slashes and typically allow cut and paste so you can view scaled integers as floats
    //// They are on the line below where the calculation occurs - of course, with BUILD_INT_FLOAT, they are unnecessary

#if defined(BUILD_WMAPROLBRV1)

    if (pau->m_bFreqex && pau->m_bDoFexOnCodedChannels)
        iHighCutOff = ppcinfo->m_cSubbandAdjusted;
    else

#endif  // BUILD_WMAPROLBRV1

    iHighCutOff = min(ppcinfo->m_cSubFrameSampleHalf, pau->m_cLastCodedIndex);

    for (iBark = 0; iBark < cValidBarkBand; iBark++)
    {
        iLo = rgiBarkIndex [iBark];
        iHi = min(iHighCutOff, (rgiBarkIndex [iBark + 1]));

        qfltQuantizer = prvWeightedModifiedQuantizationV3(pau,ppcinfo,iBark,fMaskUpdate);

        //// Float Quantizer = qfltQuantizer.iFraction/(1024.0F*(1<<(qfltQuantizer-10)))
        //MAKE_MASK_FOR_SCALING(qfltQuantizer.iFracBits);
        //WMAPrintf("%f %d\n", FloatFromFastFloat(qfltQuantizer), (1<<ppcinfo->m_cLeftShiftBitsQuant));
        //assert(FloatFromFastFloat(qfltQuantizer) > 1.0f);

#if defined(BUILD_INTEGER)
        if ((0 > qfltQuantizer.iFracBits) || (64 <= qfltQuantizer.iFracBits))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
#endif
        CHECK_COEF_MUL_FFLT( qfltQuantizer );
        for (iRecon = iLo; iRecon < iHi; iRecon++)
        {
            rgiCoefRecon [iRecon] = MULT_QUANT_AND_SCALE(rgiCoefRecon [iRecon],qfltQuantizer);
		
            VERIFY_DECODED_COEFFICENT(iBark);

            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[iRecon]));
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[iRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
        }
    }
    assert (iRecon <= ppcinfo->m_cSubFrameSampleHalf); 

exit:
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // auInvWeightSpectrumV3
#endif // WMA_OPT_SCALE_COEFFS_V3_ARM

#undef SCALE_COEFFICENT 
#undef MAKE_MASK_FOR_SCALING
#undef MULT_QUANT


//***************************************************************************
// Function: prvNextSeekPoint
//
// Purpose:
//   This function calculates the number of samples in the next frame
// which cannot be reconstructed without the current frame. For instance,
// this situation arises when seeking to a packet which starts with the next
// frame. The result of this function, added with the "aligned PCM" for the
// current frame, is used to compute the "seek" timestamp of the next
// packet (ie, the sample # of the first PCM sample generated after a seek).
//
// In version 2 the time stamp for one packet is the time output for continously
// decoding. Version 3 above this changes to seek time so the time stamp in
// the encoder should be adjusted to accommodate this change.
//
// Arguments:
//   CAudioObject *pau [in] - used for subframe config, etc.
//
// Returns:
//   Number of samples in next frame which require current frame to reconstruct.
// Note that if this is a v2 stream, this function just returns zero.
//***************************************************************************
I32 prvNextSeekPoint(const CAudioObject *pau)
{
    Int iCh;
    I32 iSizeCurr, iSizeNext, iSkipSize;
    I32 iMaxSizeCurr = 0, iMaxSizeNext = 0;

    if (pau->m_iVersion <= 2 || pau->m_bPureLosslessMode)
        return 0;

    // ---- We are at the first frame of a packet ----
    // first we try to find the max first subframe size for all the channel
    for ( iCh = 0; iCh < pau->m_cChannel; iCh++ ) {
        Int iSubframeNum;

        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;

        iSubframeNum = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame;
        iSizeCurr = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[iSubframeNum-1];
        iSizeNext = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[iSubframeNum];

        if( iSizeCurr > iMaxSizeCurr )
            iMaxSizeCurr = iSizeCurr;

        if( iSizeNext > iMaxSizeNext )
            iMaxSizeNext = iSizeNext;
    }

    iSkipSize = (iMaxSizeCurr + iMaxSizeNext) / 2;

    return (iSkipSize);

} // prvNextSeekPoint

//***************************************************************************
// Function: prvContinuousDecodeAdjustment
//
// Purpose:
//  See notes for prvNextSeekPoint
//  This function is for decoder to adjust time stamp
//  At decoder, the first frame of a packet does not know prev subframe size
//  This function is used for continously decoding scenario, so prev subframe
//  size is available.
//
// Arguments:
//   CAudioObject *pau [in] - used for subframe config, etc.
//
// Returns:
//   Number of samples in curr frame which require previous frame to reconstruct.
// Note that if this is a v2 stream, this function just returns zero.
//***************************************************************************
I32 prvContinuousDecodeAdjustment(const CAudioObject *pau)
{

    Int iCh;
    I32 iSizeCurr, iSizePrev, iSkipSize;
    I32 iMaxSizeCurr = 0, iMaxSizePrev = 0;

    if (pau->m_iVersion <= 2 || pau->m_bPureLosslessMode)
        return 0;

    // ---- We are at the first frame of a packet ----
    // first we try to find the max first subframe size for all the channel
    for ( iCh = 0; iCh < pau->m_cChannel; iCh++ ) {

        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;

        iSizePrev = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[-1]; // -1 is valid
        iSizeCurr = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[0];

        if (pau->m_fHalfTransform) {
            iSizeCurr >>= pau->m_iAdjustSizeShiftFactor;
            iSizePrev >>= pau->m_iAdjustSizeShiftFactor;
        }else if (pau->m_fPad2XTransform) {
            iSizeCurr <<= pau->m_iAdjustSizeShiftFactor;
            iSizePrev <<= pau->m_iAdjustSizeShiftFactor;
        }

        if( iSizePrev > iMaxSizePrev )
            iMaxSizePrev = iSizePrev;

        if( iSizeCurr > iMaxSizeCurr )
            iMaxSizeCurr = iSizeCurr;
    }

    iSkipSize = (iMaxSizeCurr + iMaxSizePrev) / 2;
    return (iSkipSize);

} // prvContinuousDecodeAdjustment

#if defined(_DEBUG) && 0

void prvPrintChMatrix(CAudioObject *pau)
{
  int iChGrp;
  CChannelGroupInfo *pcgi;
  Int cChannelsInGrp, iChSrc, iChDst;
  ChXFormType *rgfltMultiXGrpInverse;
  static FILE *fp = NULL;

  if (fp == NULL) {
#ifdef BUILD_INTEGER
    fp = FOPEN("chmatrix.int", "wt");
#else
    fp = FOPEN("chmatrix.flt", "wt");
#endif
  }

  for (iChGrp = 0; iChGrp < pau->m_cChannelGroup; iChGrp++) {
    WMAFprintf(fp, "\n");
    // Position src correctly for this channel group
    pcgi = pau->m_rgChannelGrpInfo + iChGrp;
    cChannelsInGrp = pcgi->m_cChannelsInGrp;
    for (iChDst=0; iChDst < cChannelsInGrp; iChDst++) {
      rgfltMultiXGrpInverse = pcgi->m_rgfltMultiXInverse + iChDst*cChannelsInGrp;
      WMAFprintf(fp, "\n");
      for (iChSrc=0; iChSrc < cChannelsInGrp; iChSrc++) {
#ifdef BUILD_INTEGER
        WMAFprintf(fp, "%6.4f %f",
                (float)rgfltMultiXGrpInverse[iChSrc]/(1<<CH_FRAC_BITS),
                (float)rgfltMultiXGrpInverse[iChSrc]/(1<<CH_FRAC_BITS)*256.0f);
#else
        WMAFprintf(fp, "%6.4f %f", 
                (float)rgfltMultiXGrpInverse[iChSrc],
                (float)rgfltMultiXGrpInverse[iChSrc]*256.0f);
#endif
#if 1
        WMAFprintf(fp, "\n");
#endif
      }
    }
  } 
} // prvPrintChMatrix
#endif // _DEBUG && 0


// prvMultiXIDCT*: Initializes IDCT-Type-2 values used by the
//                   inverse channel transform in V3. Values are quantized to 1.3bits.
//  
WMARESULT prvMultiXIDCTAllocate(CAudioObject *pau)
{
    WMARESULT wmaResult;
    Int cChannel = pau->m_cChannel;
    Int iGrpSize;

    wmaResult = WMA_OK;

    if (pau->m_iVersion < 3) {
        pau->m_rgrgrgfltMultiXIDCT = NULL;
        return WMA_OK;
    }

    pau->m_rgrgrgfltMultiXIDCT = (ChXFormType***) auMalloc(sizeof(ChXFormType**) * (cChannel + 1));
    if (pau->m_rgrgrgfltMultiXIDCT == NULL) 
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pau->m_rgrgrgfltMultiXIDCT, 0, sizeof(ChXFormType**) * (cChannel + 1));

    pau->m_rgrgrgfltMultiXIDCT[0] = NULL;
    for (iGrpSize = 1; iGrpSize <= cChannel; iGrpSize++)
    {
        pau->m_rgrgrgfltMultiXIDCT[iGrpSize] = (ChXFormType**) auMalloc(sizeof(ChXFormType*) * iGrpSize);
        if (pau->m_rgrgrgfltMultiXIDCT[iGrpSize] == NULL) 
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(pau->m_rgrgrgfltMultiXIDCT[iGrpSize], 0, sizeof(ChXFormType*) * iGrpSize);

        if (iGrpSize > MAX_PREDEF_MATRIX_CHANNELS) {
            // Static pre-defined tables go only upto 6 channels. 
            // Allocate memory for table entrees
            Int iCh;
            for (iCh = 0; iCh < iGrpSize; iCh++) {
                pau->m_rgrgrgfltMultiXIDCT[iGrpSize][iCh] = (ChXFormType*) auMalloc(sizeof(ChXFormType) * iGrpSize);
                if (pau->m_rgrgrgfltMultiXIDCT[iGrpSize][iCh] == NULL) {
                    wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
                    goto exit;
                }
                memset(pau->m_rgrgrgfltMultiXIDCT[iGrpSize][iCh], 0, sizeof(ChXFormType) * iGrpSize);
            }
        }
    }
    
exit:
    return wmaResult;
} // prvMultiXIDCTAllocate


WMARESULT prvMultiXIDCTInit(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    Int iGrpSize;

    if (pau->m_iVersion < 3)
        goto exit;

    if (MAX_PREDEF_MATRIX_CHANNELS != 6)
    {
        // Need to follow-up and fix pointer assignments below
        assert(0);
    }

    for (iGrpSize = 1; iGrpSize <= pau->m_cChannel; iGrpSize++)
    {
        switch (iGrpSize)
        {
          case 0:
            // Should not happen
              assert(0);
              break;
          case 1:
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][0] = g_rgfltMultiXIDCT + 0;
              break;
          case 2:
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][0] = g_rgfltMultiXIDCT + 1;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][1] = g_rgfltMultiXIDCT + 3;
              break;
          case 3:
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][0] = g_rgfltMultiXIDCT + 5;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][1] = g_rgfltMultiXIDCT + 8;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][2] = g_rgfltMultiXIDCT + 11;
              break;
          case 4:
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][0] = g_rgfltMultiXIDCT + 14;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][1] = g_rgfltMultiXIDCT + 18;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][2] = g_rgfltMultiXIDCT + 22;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][3] = g_rgfltMultiXIDCT + 26;
              break;
          case 5:
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][0] = g_rgfltMultiXIDCT + 30;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][1] = g_rgfltMultiXIDCT + 35;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][2] = g_rgfltMultiXIDCT + 40;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][3] = g_rgfltMultiXIDCT + 45;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][4] = g_rgfltMultiXIDCT + 50;
              break;
          case 6:
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][0] = g_rgfltMultiXIDCT + 55;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][1] = g_rgfltMultiXIDCT + 61;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][2] = g_rgfltMultiXIDCT + 67;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][3] = g_rgfltMultiXIDCT + 73;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][4] = g_rgfltMultiXIDCT + 79;
              pau->m_rgrgrgfltMultiXIDCT[iGrpSize][5] = g_rgfltMultiXIDCT + 85;
              break;
          default:
              {
                  // DCT-II matrix from Discrete Cosine Transform: Algorithms,
                  // Advantages, Applications: KR Rao, P Yip.pp 11
                  Int m, n;
                  ChXFormType **rgrgfltMultiXIDCT = pau->m_rgrgrgfltMultiXIDCT[iGrpSize];
                  Float fltPi = 4.0F * (Float) atan(1.0f);
                  for (m = 0; m < iGrpSize; m++) {
                      Float fltKm = (m == 0) ? 1.0F/(Float)sqrt(2.0f) : 1.0F;
                      fltKm *= (Float) sqrt(2.0F / iGrpSize);
                      for (n = 0; n < iGrpSize; n++) {
                          Float tmp;
                          tmp = fltKm * (Float) cos((m * (n + 0.5F) * fltPi)/iGrpSize);
                          // Quantize to fixed point 1.3:
                          tmp = (tmp < 0) ? tmp - 0.0625F : tmp + 0.0625F;
                          tmp *= 8.0F;
                          tmp = (Float) ((Int) tmp);
                          tmp /= 8.0F;
                          assert(tmp != -1.0F);
                          rgrgfltMultiXIDCT[n][m] = CH_FROM_FLOAT(tmp);
                      }
                  }
              }
              break;
        }
    }

exit:
    return wmaResult;
} // prvMultiXIDCTInit



Void prvMultiXIDCTDelete  (CAudioObject *pau)
{
  Int cChannel = pau->m_cChannel;
  Int iGrpSize;
  
  if (pau->m_rgrgrgfltMultiXIDCT != NULL) {
    for (iGrpSize = 1; iGrpSize <= cChannel; iGrpSize++) {
        if (iGrpSize > MAX_PREDEF_MATRIX_CHANNELS) {
            // Allocated additional memory
            Int iCh;
            for (iCh = 0; iCh < iGrpSize; iCh++) {
                DELETE_ARRAY (pau->m_rgrgrgfltMultiXIDCT[iGrpSize][iCh]);
            }
        }
        DELETE_ARRAY (pau->m_rgrgrgfltMultiXIDCT[iGrpSize]);
    }
    DELETE_ARRAY (pau->m_rgrgrgfltMultiXIDCT);
  }
  return;
} // prvMultiXIDCTDelete

// Sets -1 if not found
Void prvGetChannelNumAtSpeakerPosition (U32 nChannelMask,
                                        U32 nSpeakerPosition,
                                        I16 *pnChannelNum)
{
    *pnChannelNum = -1;
    if (nChannelMask & nSpeakerPosition) {
      // Determine the exact position: count 1's from LSB to required speaker position
        U32 nTmp = 0x1;
        Int iCh;
        for (iCh = 0; iCh < 32; iCh++) {
            if (nTmp & nChannelMask) 
                *pnChannelNum = *pnChannelNum + 1;
            if (nTmp & nSpeakerPosition)
                break;
            nTmp <<= 1;
        } 
    }
} // prvGetChannelNumAtSpeakerPosition

Void auInitBarkResampleMatrix (CAudioObject* pau)
{
    Int iWin0, iWin1, iBark0, iBark1;
    Int* rgiBarkIndex0 = NULL;
    Int* rgiBarkIndex1 = NULL;
    Int  iFreq0, iFreq1; 
    // Frequency in Hz = iFreq * iSamplingRate / (2 * framesampleHalf)
    // But here, we do not need the true freq in Hz.

    // unnecessary loops
    if (pau->m_rgrgrgnBarkResampleMatrix == NULL)
    {
        // not allocated => not needed.
        return;
    }
    for (iWin0 = 0; iWin0 < pau->m_cPossibleWinSize; iWin0++)
    {
        for (iWin1 = 0; iWin1 < pau->m_cPossibleWinSize; iWin1++)
        {
            memset(pau->m_rgrgrgnBarkResampleMatrix[iWin0][iWin1], 0,
                sizeof (U8) * NUM_BARK_BAND);
        }
    }
    
    for (iWin0 = 0; iWin0 < pau->m_cPossibleWinSize; iWin0++) {
        rgiBarkIndex0 = pau->m_rgiBarkIndexOrig + iWin0 * (NUM_BARK_BAND + 1);
        for (iBark0 = 0; iBark0 < pau->m_rgcValidBarkBand[iWin0]; iBark0++) {
            // Representative freq (Hz) for iBark0 in subframe size iWin0
            iFreq0 = (rgiBarkIndex0[iBark0] + rgiBarkIndex0[iBark0+1] -1) * (1 << iWin0)/ 2;
            for (iWin1 = 0; iWin1 < pau->m_cPossibleWinSize; iWin1++) {
                rgiBarkIndex1 = pau->m_rgiBarkIndexOrig + iWin1 * (NUM_BARK_BAND + 1);
                // Locate the first iBark1 in subframe size iWin1 that includes iFreq0
                iBark1 = 0;
                while ((iFreq1 = rgiBarkIndex1[iBark1+1] * (1 << iWin1)) < iFreq0) {
                    iBark1++;
                }
                assert(iBark1 < pau->m_rgcValidBarkBand[iWin1]);
                pau->m_rgrgrgnBarkResampleMatrix[iWin0][iWin1][iBark0] = (U8)iBark1;
            }
        }
    }
} // auInitBarkResampleMatrix


WMARESULT auResampleMaskV3 (CAudioObject* pau, 
                          Int* rgiMaskQIn, Int cSubbandIn, Int cValidBarksIn, 
                          Int* rgiMaskQOut, Int cSubbandOut, Int cValidBarksOut)
{
  WMARESULT wmaResult = WMA_OK;
  Int iBandIn, iBandOut;
  Int iWinIn, iWinOut;


  assert(pau->m_iVersion > 2);
  assert(cValidBarksIn > 0);
  assert(cValidBarksOut > 0);
  assert(cSubbandIn > 0);
  assert(cSubbandOut > 0);
  assert (pau->m_rgrgrgnBarkResampleMatrix != NULL);

  iWinIn  = LOG2(pau->m_cFrameSampleHalf / cSubbandIn);
  iWinOut = LOG2(pau->m_cFrameSampleHalf / cSubbandOut);

  for (iBandOut = 0; iBandOut < cValidBarksOut; iBandOut++) {
      iBandIn = pau->m_rgrgrgnBarkResampleMatrix[iWinOut][iWinIn][iBandOut];
      rgiMaskQOut[iBandOut] = rgiMaskQIn[iBandIn];
  }

  return wmaResult;
} // auResampleMaskV3

//*****************************************************************************************
//
// prvAllocChannelGrpInfo
//   Allocates an array of CChannelGroupInfo (of size cChannel), with channel mask in each entry of size cChannel
//   Does not allocate memory for forward/inverse matrices.
//
//*****************************************************************************************
WMARESULT prvAllocChannelGrpInfo(CChannelGroupInfo **prgChannelGrpInfo, 
                                 Int cChannel)
{
    WMARESULT wmaResult = WMA_OK;
    Int iCh;

    assert (prgChannelGrpInfo != NULL);
    *prgChannelGrpInfo = NULL;

    *prgChannelGrpInfo = (CChannelGroupInfo*) auMalloc(sizeof(CChannelGroupInfo) * cChannel);
    if (*prgChannelGrpInfo == NULL) {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(*prgChannelGrpInfo, 0, sizeof(CChannelGroupInfo) * cChannel);
    for (iCh = 0; iCh < cChannel; iCh++) {
        CChannelGroupInfo* pcgi = (*prgChannelGrpInfo) + iCh;
        pcgi->m_rgfChannelMask = (Bool*) auMalloc(sizeof(Bool) * cChannel);
        if (pcgi->m_rgfChannelMask == NULL) {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        if (cChannel > 1) {
            pcgi->m_rgbRotationAngle = (I8*) auMalloc(sizeof(I8) * (cChannel * (cChannel -1)/2));
            if (pcgi->m_rgbRotationAngle == NULL) {
                wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
                goto exit;
            }
            memset(pcgi->m_rgbRotationAngle, 0, sizeof(I8) * (cChannel * (cChannel - 1)) / 2);
        }
        pcgi->m_rgbRotationSign = (I8*) auMalloc(sizeof(I8) * cChannel);
        if (pcgi->m_rgbRotationSign == NULL) {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(pcgi->m_rgbRotationSign, 0, sizeof(I8) * cChannel);
    }
exit:
    return wmaResult;
} // prvAllocChannelGrpInfo

//*****************************************************************************************
//
// prvDeleteChannelGrpInfo
//   Deletes an array of CChannelGroupInfo (of size cChannel), with channel mask in each entry of size cChannel
//
//*****************************************************************************************
Void prvDeleteChannelGrpInfo(CChannelGroupInfo **prgChannelGrpInfo, Int cChannel)
{
    Int k;
    if (prgChannelGrpInfo && *prgChannelGrpInfo)
    {
        for (k = 0; k < cChannel; k++) {
            CChannelGroupInfo* pcgi = (*prgChannelGrpInfo) + k;
            DELETE_ARRAY(pcgi->m_rgfChannelMask);
            DELETE_ARRAY(pcgi->m_rgbRotationAngle);
            DELETE_ARRAY(pcgi->m_rgbRotationSign);
            DELETE_ARRAY(pcgi->m_rgfltMultiXForward);
            DELETE_ARRAY(pcgi->m_rgfltMultiXInverse);
        }
        DELETE_ARRAY((*prgChannelGrpInfo));
    }
} // prvDeleteChannelGrpInfo

// Performs Givens rotations to take a unitary transform of 
// size cSize-1 to cSize.
// Angles are assumed to be quantized. 
// The input transformation, and the output transformation,
// both have a size of cMatrixSize X cMatrixSizex.
WMARESULT prvGivensMultiplyFactors(I8*    rgbRotationAngle,
                                   ChXFormMType* rgfltMultiXInverse,
                                   Int    cSize,
                                   Int    cMatrixSize,
                                   ChXFormMType* rgfltTmpCurr,
                                   ChXFormMType* rgfltTmpFinal)
{
    WMARESULT wmaResult = WMA_OK;
    Int i, j;
    ChXFormMType fltCosTheta, fltSinTheta;
    const Float fltPiDivTwo = (Float) (PI/2.0F);

    // No rotations to be performed.
    if (cSize <=1 )
        return wmaResult;
    
    for (i = 0; i < cSize-1; i++)
    {

#if defined(BUILD_INTEGER) || defined(FLOAT_INT_CHXFORM) // use tables
        assert(rgbRotationAngle[i] + MAX_ROTATION_ANGLE_INDEX >= 0);
        assert(rgbRotationAngle[i] + MAX_ROTATION_ANGLE_INDEX < MAX_ROTATION_ANGLES);
        fltCosTheta = (I32) g_fltRotationCos[rgbRotationAngle[i] + MAX_ROTATION_ANGLE_INDEX];
        fltSinTheta = (I32) g_fltRotationSin[rgbRotationAngle[i] + MAX_ROTATION_ANGLE_INDEX];
#else
        Float fltTheta = rgbRotationAngle[i] * fltPiDivTwo / MAX_ROTATION_ANGLE_INDEX; // currently 3 decimal bits 
        fltCosTheta = CHM_FROM_FLOAT((Float) cos(fltTheta));
        fltSinTheta = CHM_FROM_FLOAT((Float) sin(fltTheta));
#endif
        // Copy over the rows we are going to change
        memcpy(rgfltTmpCurr, rgfltMultiXInverse + cMatrixSize * i, sizeof(ChXFormMType) * cSize);
        memcpy(rgfltTmpFinal, rgfltMultiXInverse + cMatrixSize * (cSize-1), sizeof(ChXFormMType) * cSize);

        // Do the rotation
        for (j = 0; j < cSize; j++) {
            rgfltMultiXInverse[cMatrixSize * i + j] =
              MULT_CH_MATRIX(fltCosTheta, rgfltTmpCurr[j]) + MULT_CH_MATRIX(fltSinTheta, rgfltTmpFinal[j]);
            rgfltMultiXInverse[cMatrixSize * (cSize-1) + j] =
              MULT_CH_MATRIX(-fltSinTheta, rgfltTmpCurr[j]) + MULT_CH_MATRIX(fltCosTheta, rgfltTmpFinal[j]);
        }
    }
    return wmaResult;
} // prvGivensMultiplyFactors

// Based on quantized Givens rotation angles and signs, this 
// procedure recreates the unitary transform. 
// See Section 14.6.1 in "Multirate Systems and Filter Banks,"
// by P.P. Vaidyanathan, 1993, Prentice Hall.
WMARESULT auGetTransformFromGivensFactors(I8* rgbRotationAngle, 
                                          I8* rgbRotationSign, 
                                          Int cSize, 
                                          Int cMaxChannel,  // only for security
                                          ChXFormType* rgfltMultiXInverse,
                                          ChXFormType* rgfltTmpCurr,
                                          ChXFormType* rgfltTmpFinal)
{
    WMARESULT wmaResult = WMA_OK;
    Int i, iStage, cCur;
    ChXFormMType* rgfltMultiXInverseM = (ChXFormMType*)rgfltMultiXInverse;

    if (rgbRotationAngle == NULL || rgbRotationSign == NULL ||
        rgfltMultiXInverseM == NULL || cSize < 1 || cSize > cMaxChannel)
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
    
    // First fill with the sign info.
    memset(rgfltMultiXInverseM, 0, sizeof(ChXFormMType) * cSize * cSize);
    for (i = 0; i < cSize; i++)
        rgfltMultiXInverseM[i * cSize + i] = (rgbRotationSign[i] == 0) ? CHM_FROM_FLOAT(-1.0F) : CHM_FROM_FLOAT(1.0F);
    
    cCur = 0;
    for (iStage = 0; iStage < cSize; iStage++)
    {
        TRACEWMA_EXIT(wmaResult, prvGivensMultiplyFactors(rgbRotationAngle + cCur, 
            (ChXFormMType*)rgfltMultiXInverse,
            iStage+1,
            cSize,
            (ChXFormMType*)rgfltTmpCurr,
            (ChXFormMType*)rgfltTmpFinal));
        cCur += iStage;
    }

    // Limit the precision needed to perform inverse channel transform. 8 decimal bits.
    for (i = 0; i < cSize * cSize; i++) {
        rgfltMultiXInverseM[i] = ROUND_CH_TO_2TON(rgfltMultiXInverseM[i], 8);
    }

#if defined(FLOAT_INT_CHXFORM)
    for (i = 0; i < cSize * cSize; i++) {
        rgfltMultiXInverse[i] =  FLOAT_FROM_CHM(rgfltMultiXInverseM[i]);
    }
#endif

exit:
    return wmaResult;
} // auGetTransformFromGivensFactors

#if !defined(BUILD_INTEGER)
// moved here from processes.c since decoder need MatrixMultiply in LLMB.
/* 
    Matrix multiplication. 
    rgMatrixOutput = rgMatrixInput1 * rgMatrixInput2;
    rgMatrixInput1: cSize1 X cSize2    
    rgMatrixInput2: cSize2 X cSize3    
    rgMatrixOutput: cSize1 X cSize3    
*/
WMARESULT prvMatrixMultiply(Float * rgMatrixInput1, Float * rgMatrixInput2, Float * rgMatrixOutput, 
                            const Int cSize1, const Int cSize2, const Int cSize3)
{
    Int i, j, k;
    WMARESULT hr = WMA_OK;

    assert(rgMatrixInput1 != NULL);        
    assert(rgMatrixInput2 != NULL);        
    assert(rgMatrixOutput != NULL);        

    assert(cSize1 > 0);
    assert(cSize2 > 0);
    assert(cSize3 > 0);


    for (i = 0; i < cSize1; i ++)
        for (k = 0; k < cSize3; k++) {
            rgMatrixOutput[i * cSize3 + k] = 0;
            for (j = 0; j < cSize2; j++) {
                rgMatrixOutput[i * cSize3 + k] += rgMatrixInput1[i * cSize2 + j] * rgMatrixInput2[j * cSize3 + k];
            }
        }


    return (hr);
}
#endif

WMARESULT prvLLMVerBResetAllCom_MLLM(CAudioObject * pau, PerChannelInfo * ppcInfoComms)
{
    WMARESULT     hr = WMA_OK;
    I16 iCh;
    // reset for seekable.
    assert(pau->m_bSeekable == WMAB_TRUE);

    // Not in bitstream.
    pau->m_bSendCDLMS = WMAB_FALSE; // for prvResetLMSPredictor call.
    pau->m_iACFilterOrder = 1;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        I16 k;
        PerChannelInfo * ppcInfoComm = ppcInfoComms + iChSrc;
        // reset LPC prevsamples.
        memset(ppcInfoComm->m_rgiLPCPrevSamples, 0, LLM_LPC_ORDER * sizeof(I32));
        // Step 1
        memset(ppcInfoComm->m_iLastSamples, 0, LLM_VERB_ACFILTER_ORDER_MAX * sizeof(I32));
        // Step 2
        {
            for (k = 0; k < ppcInfoComm->m_cLMSPredictors; k++) {
                // MLLMUsePLLM doesn't send filter coefficients. And rgiFilterBackup are all zero.
                prvResetLMSPredictor(pau, &ppcInfoComm->m_rgLMSPredictors[k]);            
            }
        }
        // Step 3
        // we use block Colomb coding in MLLMUsePLLM
        ppcInfoComm->m_iSum = 0;
        // prvResetColombKinLLMB(pau, ppcInfoComm);
    }
    return(hr);
}

// ======================================================================
#ifdef OVERLAPADDV3DCT_C_OPT

INLINE WMARESULT auOverlapAddV3DCTFlip_LUT(CAudioObject *pau, CoefType *pctCoefOut,
                         CoefType *pctCoefHist, CoefType *pctCoefNew,
                         CoefType *pctCoefHistDST, CoefType *pctCoefNewDST,
                         Int iSizePrev, Int iSizeCurr, Bool fBase)
{
    WMARESULT wmaResult = WMA_OK;
    Int iOverlap, iCoeff, iLoopEnd;
    TR2_TYPE bp2Sin, bp2Cos;
    TR2_TYPE bp2Sin1, bp2Cos1;
    TR2_TYPE bp2Step;
    CoefType ctPrevData;
    CoefType ctCurrData;
    CoefType *pctOut, *pctOutBottom, *pctHist, *pctNew;
    const SinCosTable *pSinCosTable;
    const BP2Type* pbp2Sin;
    const BP2Type* pbp2Cos;
    I16 iQ1, iQ2;

    // flip all the new coefficients
    auFlipCoeff(pctCoefNew, iSizeCurr);

    if (fBase)
    {
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr,
                         &iQ1, &iQ2);

        iOverlap = (iQ2 - iQ1)/2;
    }
    else
    {
        iOverlap = min(iSizePrev, iSizeCurr) >> 1;
    }

    // flat part of 2nd half of prev
    pctHist = pctCoefHist;
    pctOut = pctCoefOut;
    iLoopEnd = (iSizePrev >> 1) - iOverlap;
    for (iCoeff = 0; iCoeff < iLoopEnd; iCoeff++)
    {
        *pctOut++ = *pctHist++;
    }

    assert(((iOverlap >= 32 && iOverlap <= 1024) || iOverlap == 0) &&
           CHECK_POWER_OF_TWO(iOverlap));

    // move history pointers to start of overlap region
    // move current pointers to end of overlap region
    // move destination pointers to start of overlap region for output
    pctHist = pctCoefHist + (iSizePrev >> 1) - iOverlap;
    pctNew = pctCoefNew + iOverlap - 1;
    pctOut = pctCoefOut + (iSizePrev >> 1) - iOverlap;
    pctOutBottom = pctOut + (iOverlap << 1) - 1;

    // Same as (iOverlap == 64 || iOverlap == 128) since iOverlap is power of 2
    if (iOverlap & ( 64 | 128))
    {
        pbp2Sin = (iOverlap == 64) ? g_bp2SinLUT128 : g_bp2SinLUT256;
        pbp2Cos = (iOverlap == 64) ? (pbp2Sin + 127): (pbp2Sin + 255);
#if !defined(WMA_OPT_OVERLAPADDV3DCT_ARM) || !WMA_OPT_OVERLAPADDV3DCT_ARM
        for (iCoeff = 0; iCoeff < iOverlap; iCoeff++)
        {
            bp2Sin = TR2_FROM_BP2(*pbp2Sin++);
            bp2Cos = TR2_FROM_BP2(*pbp2Cos--);
    #if defined(RECALC_R) || defined(RECALC)
            if (DORECALC_R(iCoeff))
            {
                bp2Sin = TR2_FROM_FLOAT(sin(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
                bp2Cos = TR2_FROM_FLOAT(cos(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
            }
    #endif
            ctPrevData = *pctHist++;
            ctCurrData = *pctNew--;
    #if defined(BUILD_INTEGER)
            assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
            assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
    #endif
            *pctOut++ = MAC2_BP2(-bp2Sin, ctCurrData, bp2Cos, ctPrevData);
            *pctOutBottom-- = MAC2_BP2(bp2Sin, ctPrevData, bp2Cos, ctCurrData);
        }
#else
        auOverlapAddV3DCTLoop_LUT_Flip(pctHist, pctNew, pctOut, pbp2Sin, iOverlap);
#endif
    }
    else
    {
        pSinCosTable = rgSinCosTables[iOverlap >> 6];
        // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
        bp2Sin = TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
        bp2Cos = TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
        // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
        bp2Sin1 = -bp2Sin;
        bp2Cos1 = bp2Cos;
        // STEP = 2*sin(PI/2/iSizeCurr)
        bp2Step = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));
        // Recursion Formulas:
        // sin(a + b) = sin(a - b) + 2 * sin(b) * cos(a)
        // cos(a + b) = cos(a - b) - 2 * sin(b) * sin(a)
        for (iCoeff = 0; iCoeff < iOverlap; iCoeff += 2)
        {
    #if defined(RECALC_R) || defined(RECALC)
            if (DORECALC_R(iCoeff))
            {
                bp2Sin = TR2_FROM_FLOAT(sin(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
                bp2Cos = TR2_FROM_FLOAT(cos(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
            }
    #endif
            ctPrevData = *pctHist++;
            ctCurrData = *pctNew--;
    #if defined(BUILD_INTEGER)
            assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
            assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
    #endif
            *pctOut++ = MAC2_BP2(BP2_FROM_TR2(-bp2Sin), ctCurrData, BP2_FROM_TR2(bp2Cos), ctPrevData);
            *pctOutBottom-- = MAC2_BP2(BP2_FROM_TR2(bp2Sin), ctPrevData, BP2_FROM_TR2(bp2Cos), ctCurrData);
            bp2Sin1 = bp2Sin1 + MULT_TR2(bp2Step, bp2Cos);
            bp2Cos1 = bp2Cos1 - MULT_TR2(bp2Step, bp2Sin);

    #if defined(RECALC_R) || defined(RECALC)
            if (DORECALC_R(iCoeff))
            {
                bp2Sin = BP2_FROM_FLOAT(sin(PI * (2 * iCoeff + 3) / (8 * iOverlap)));
                bp2Cos = BP2_FROM_FLOAT(cos(PI * (2 * iCoeff + 3) / (8 * iOverlap)));
            }
    #endif
            ctPrevData = *pctHist++;
            ctCurrData = *pctNew--;
    #if defined(BUILD_INTEGER)
            assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
            assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
    #endif
            *pctOut++ = MAC2_BP2(BP2_FROM_TR2(-bp2Sin1), ctCurrData, BP2_FROM_TR2(bp2Cos1), ctPrevData);
            *pctOutBottom-- = MAC2_BP2(BP2_FROM_TR2(bp2Sin1), ctPrevData, BP2_FROM_TR2(bp2Cos1), ctCurrData);
            TR2_RECURR_INC(bp2Cos,bp2Sin,bp2Cos1,bp2Sin1,bp2Step)
            /*
            bp2Sin = bp2Sin + MULT_TR2(bp2Step, bp2Cos1);
            bp2Cos = bp2Cos - MULT_TR2(bp2Step, bp2Sin1);
            */
        }
    }

    // flat part of first half of cur
    pctNew = pctCoefNew + iOverlap;
    pctOut = pctCoefOut + (iSizePrev >> 1) + iOverlap;
    iLoopEnd = iSizeCurr >> 1;
    for (iCoeff = iOverlap; iCoeff < iLoopEnd; iCoeff++)
    {
        *pctOut++ = *pctNew++;
    }
    return wmaResult;
}

INLINE WMARESULT auOverlapAddV3DCTNoFlip_LUT(CAudioObject *pau, CoefType *pctCoefOut,
                         CoefType *pctCoefHist, CoefType *pctCoefNew,
                         CoefType *pctCoefHistDST, CoefType *pctCoefNewDST,
                         Int iSizePrev, Int iSizeCurr, Bool fBase)
{
    WMARESULT wmaResult = WMA_OK;
    Int iOverlap, iCoeff, iLoopEnd;
    TR2_TYPE bp2Sin, bp2Cos;
    TR2_TYPE bp2Sin1, bp2Cos1;
    TR2_TYPE bp2Step;
    CoefType ctPrevData;
    CoefType ctCurrData;
    CoefType *pctOut, *pctOutBottom, *pctHist, *pctNew;
    const SinCosTable *pSinCosTable;
    const BP2Type* pbp2Sin;
    const BP2Type* pbp2Cos;
    I16 iQ1, iQ2;

    if (fBase)
    {
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr,
                         &iQ1, &iQ2);

        iOverlap = (iQ2 - iQ1) >> 1;
    }
    else
    {
        iOverlap = min(iSizePrev, iSizeCurr) >> 1;
    }

    // flat part of 2nd half of prev
    pctHist = pctCoefHist + (iSizePrev >> 1) - 1;
    pctOut = pctCoefOut;
    iLoopEnd = (iSizePrev >> 1) - iOverlap;
    for (iCoeff = 0; iCoeff < iLoopEnd; iCoeff++)
    {
        *pctOut++ = *pctHist--;
    }

    assert(((iOverlap >= 32 && iOverlap <= 1024) || iOverlap == 0) &&
           CHECK_POWER_OF_TWO(iOverlap));

    // move history pointers to start of overlap region
    // move current pointers to end of overlap region
    // move destination pointers to start of overlap region for output
    pctHist = pctCoefHist + iOverlap - 1;
    pctNew = pctCoefNew + iSizeCurr - iOverlap;
    pctOut = pctCoefOut + (iSizePrev >> 1) - iOverlap;
    pctOutBottom = pctOut + (iOverlap << 1) - 1;

    // Same as (iOverlap == 64 || iOverlap == 128) since iOverlap is power of 2
    if (iOverlap & ( 64 | 128))
    {
        pbp2Sin = (iOverlap == 64) ? g_bp2SinLUT128 : g_bp2SinLUT256;
        pbp2Cos = (iOverlap == 64) ? (pbp2Sin + 127): (pbp2Sin + 255);
#if !defined(WMA_OPT_OVERLAPADDV3DCT_ARM) || !WMA_OPT_OVERLAPADDV3DCT_ARM
        for (iCoeff = 0; iCoeff < iOverlap; iCoeff++)
        {
            bp2Sin = TR2_FROM_BP2(*pbp2Sin++);
            bp2Cos = TR2_FROM_BP2(*pbp2Cos--);

#if defined(RECALC_R) || defined(RECALC)
            if (DORECALC_R(iCoeff))
            {
                bp2Sin = TR2_FROM_FLOAT(sin(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
                bp2Cos = TR2_FROM_FLOAT(cos(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
            }
#endif
            ctPrevData = *pctHist--;
            ctCurrData = *pctNew++;
#if defined(BUILD_INTEGER)
            assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
            assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
#endif
            *pctOut++ = MAC2_BP2(BP2_FROM_TR2(-bp2Sin), ctCurrData, BP2_FROM_TR2(bp2Cos), ctPrevData);
            *pctOutBottom-- = MAC2_BP2(BP2_FROM_TR2(bp2Sin), ctPrevData, BP2_FROM_TR2(bp2Cos), ctCurrData);
        }
#else
        auOverlapAddV3DCTLoop_LUT_NoFlip(pctHist, pctNew, pctOut, pbp2Sin, iOverlap);
#endif
    }
    else
    {
        pSinCosTable = rgSinCosTables[iOverlap >> 6];
        // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
        bp2Sin = TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
        bp2Cos = TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
        // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
        bp2Sin1 = -bp2Sin;
        bp2Cos1 = bp2Cos;
        // STEP = 2*sin(PI/2/iSizeCurr)
        bp2Step = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));
        // Recursion Formulas:
        // sin(a + b) = sin(a - b) + 2 * sin(b) * cos(a)
        // cos(a + b) = cos(a - b) - 2 * sin(b) * sin(a)
        for (iCoeff = 0; iCoeff < iOverlap; iCoeff += 2)
        {
#if defined(RECALC_R) || defined(RECALC)
            if (DORECALC_R(iCoeff))
            {
                bp2Sin = TR2_FROM_FLOAT(sin(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
                bp2Cos = TR2_FROM_FLOAT(cos(PI * (2 * iCoeff + 1) / (8 * iOverlap)));
            }
#endif
            ctPrevData = *pctHist--;
            ctCurrData = *pctNew++;
#if defined(BUILD_INTEGER)
            assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
            assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
#endif
            *pctOut++ = MAC2_BP2(BP2_FROM_TR2(-bp2Sin), ctCurrData, BP2_FROM_TR2(bp2Cos), ctPrevData);
            *pctOutBottom-- = MAC2_BP2(BP2_FROM_TR2(bp2Sin), ctPrevData, BP2_FROM_TR2(bp2Cos), ctCurrData);
            
            TR2_RECURR_INC(bp2Cos1,bp2Sin1,bp2Cos,bp2Sin,bp2Step)
            /*
            bp2Sin1 = bp2Sin1 + MULT_TR2(bp2Step, bp2Cos);
            bp2Cos1 = bp2Cos1 - MULT_TR2(bp2Step, bp2Sin);
            */

#if defined(RECALC_R) || defined(RECALC)
            if (DORECALC_R(iCoeff))
            {
                bp2Sin = TR2_FROM_FLOAT(sin(PI * (2 * iCoeff + 3) / (8 * iOverlap)));
                bp2Cos = TR2_FROM_FLOAT(cos(PI * (2 * iCoeff + 3) / (8 * iOverlap)));
            }
#endif
            ctPrevData = *pctHist--;
            ctCurrData = *pctNew++;
#if defined(BUILD_INTEGER)
            assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
            assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
#endif
            *pctOut++ = MAC2_BP2(BP2_FROM_TR2(-bp2Sin1), ctCurrData,BP2_FROM_TR2(bp2Cos1), ctPrevData);
            *pctOutBottom-- = MAC2_BP2(BP2_FROM_TR2(bp2Sin1), ctPrevData, BP2_FROM_TR2(bp2Cos1), ctCurrData);
            TR2_RECURR_INC(bp2Cos,bp2Sin,bp2Cos1,bp2Sin1,bp2Step)
            /*
            bp2Sin = bp2Sin + MULT_TR2(bp2Step, bp2Cos1);
            bp2Cos = bp2Cos - MULT_TR2(bp2Step, bp2Sin1);
            */
        }
    }
    // flat part of first half of cur
    pctNew = pctCoefNew + iSizeCurr - 1 - iOverlap;
    pctOut = pctCoefOut + (iSizePrev >> 1) + iOverlap;
    iLoopEnd = iSizeCurr >> 1;
    for (iCoeff = iOverlap; iCoeff < iLoopEnd; iCoeff++)
    {
        *pctOut++ = *pctNew--;
    }
    return wmaResult;
}
#endif
          
#undef TEMPLATE_INCLUDE_INDX
#define TEMPLATE_INCLUDE_INDX 1
#include "msaudiotemplatedef.h"
#undef TEMPLATE_INCLUDE_INDX

WMARESULT auOverlapAddV3(CAudioObject *pau,
                         CoefType *pctCoefOut,
                         CoefType *pctCoefHist,
                         CoefType *pctCoefNew,
                         CoefType *pctCoefHistDST,
                         CoefType *pctCoefNewDST,
                         Int iSizePrev, Int iSizeCurr,
                         Bool bUseDCT,
                         Bool bUseMCLT,
                         Bool bFlip,
                         Bool fBase)
{
#ifdef OVERLAPADDV3DCT_C_OPT
    if ((1==bUseDCT) && (0==bUseMCLT) && (1==bFlip))
    {
        return auOverlapAddV3DCTFlip_LUT(pau, pctCoefOut, pctCoefHist, pctCoefNew,
                                     pctCoefHistDST, pctCoefNewDST, iSizePrev,
                                     iSizeCurr, fBase);
    }
    else if ((1==bUseDCT) && (0==bUseMCLT) && (0==bFlip))
    {
        return auOverlapAddV3DCTNoFlip_LUT(pau, pctCoefOut, pctCoefHist, pctCoefNew,
                                       pctCoefHistDST, pctCoefNewDST,
                                       iSizePrev, iSizeCurr,
                                       fBase);
    }
#else
    if ((1==bUseDCT) && (0==bUseMCLT) && (1==bFlip))
    {
        return auOverlapAddV3DCTFlip(pau, pctCoefOut, pctCoefHist, pctCoefNew,
                                     pctCoefHistDST, pctCoefNewDST, iSizePrev,
                                     iSizeCurr, fBase);
    }
    else if ((1==bUseDCT) && (0==bUseMCLT) && (0==bFlip))
    {
        return auOverlapAddV3DCTNoFlip(pau, pctCoefOut, pctCoefHist, pctCoefNew,
                                       pctCoefHistDST, pctCoefNewDST,
                                       iSizePrev, iSizeCurr,
                                       fBase);
    }
#endif
    else if ((0==bUseDCT) && (1==bUseMCLT) && (0==bFlip))
        return auOverlapAddV3MCLTNoFlip(pau, pctCoefOut, pctCoefHist, pctCoefNew,
                                        pctCoefHistDST, pctCoefNewDST,
                                        iSizePrev, iSizeCurr,
                                        fBase);
    else if ((1==bUseDCT) && (1==bUseMCLT) && (0==bFlip))
        return auOverlapAddV3MCLTHistDirectMCLT(
                                        pau,
                                        pctCoefOut,
                                        pctCoefHist,
                                        pctCoefNew,
                                        NULL,
                                        pctCoefNewDST,
                                        iSizePrev,
                                        iSizeCurr,
                                        fBase);
    else
    {
        assert(!"Invalid argument");
        return WMA_E_FAIL;
    }
}

WMARESULT auOverlapAddV3DirectMCLTHistDCTDSTWrap(CAudioObject *pau, CoefType *pctCoefOut,
                         CoefType *pctCoefHist, CoefType *pctCoefNew,
                         CoefType *pctCoefHistDST, CoefType *pctCoefNewDST,
                         Int iSizePrev, Int iSizeCurr, Bool fBase)
{
    return auOverlapAddV3DirectMCLTHistDCTDST(pau, pctCoefOut, pctCoefHist, pctCoefNew,
                                              pctCoefHistDST, pctCoefNewDST,
                                              iSizePrev, iSizeCurr, fBase);
}


WMARESULT auOverlapAddV3DirectMCLT(CoefType *pctCoefOut,
                                  CoefType *pctCoefHist,
                                  CoefType *pctCoefNew,
                                  Int iSizeCurr)
{
    WMARESULT wmaResult = WMA_OK;
    Int iCoeff;
    CoefType *pctOut, *pctHist, *pctNew;

    pctHist = pctCoefHist;
    pctOut = pctCoefOut;
    pctNew = pctCoefNew;
    for (iCoeff=0; iCoeff < iSizeCurr; iCoeff++)
    {
        *pctOut = ( *pctNew + *pctHist ) / 2;
        pctHist++;
        pctNew++;
        pctOut++;
    }

    return wmaResult;
}


#if 0
#if defined(WMA_TARGET_X86) && defined(BUILD_INT_FLOAT) && !defined(WMA_DISABLE_SSE1)

#include <xmmintrin.h>

WMARESULT auOverlapAddV3_SSE1(CAudioObject *pau,
                              CoefType *pctCoefOut,
                              CoefType *pctCoefHist,
                              CoefType *pctCoefNew,
                              Int iSizePrev, Int iSizeCurr,
                              Bool bUseDCT,
                              Bool bUseMCLT,
                              Bool fBase)
{
    WMARESULT wmaResult = WMA_OK;
    Int iOverlap;
    I16 iQ1, iQ2;

    // flip all the new coefficients
    auFlipCoeff(pctCoefNew, iSizeCurr);

    if (fBase)
    {
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr,
                         &iQ1, &iQ2);

        iOverlap = (iQ2 - iQ1)/2;
    }
    else
    {
        iOverlap = min(iSizePrev, iSizeCurr) / 2;
    }

    // flat part of 2nd half of prev
    {
        if (bUseMCLT)
        {
            Int iCoeff;
            CoefType *pctOut, *pctHist;
            pctHist = pctCoefHist;
            pctOut = pctCoefOut;
            for (iCoeff=-iSizePrev/2/4; iCoeff < -iOverlap/4; iCoeff++)
            {
                _mm_store_ps(pctOut, _mm_mul_ps(_mm_load_ps(pctHist), _mm_set1_ps(0.5f)));
                pctHist += 4;
                pctOut += 4;
            }
        }
        else
        {
            memcpy(pctCoefOut, pctCoefHist, (-iOverlap - (-iSizePrev/2)) * sizeof(CoefType));
        }
    }

    assert(((iOverlap >= 32 && iOverlap <= 1024) || iOverlap==0) &&
           CHECK_POWER_OF_TWO(iOverlap));

    {
        __m128 sincur, coscur, sinprev, cosprev, step;
        {
            const SinCosTable *pSinCosTable;
            BP2Type bp2SinCur0, bp2SinCur1, bp2SinCur2, bp2SinCur3,
                    bp2CosCur0, bp2CosCur1, bp2CosCur2, bp2CosCur3;
            BP2Type bp2SinPrev0, bp2SinPrev1, bp2SinPrev2, bp2SinPrev3,
                    bp2CosPrev0, bp2CosPrev1, bp2CosPrev2, bp2CosPrev3;
            BP2Type bp2SinTemp0, bp2SinTemp1, bp2SinTemp2, bp2SinTemp3,
                    bp2CosTemp0, bp2CosTemp1, bp2CosTemp2, bp2CosTemp3;
            BP2Type bp2Step;
            
            pSinCosTable = rgSinCosTables[iOverlap>>6];
        
            // Notation: "1" is PI/cSB
        
#define SINQ  (pSinCosTable->sin_PIby4cSB)
#define COSQ  (pSinCosTable->cos_PIby4cSB)
#define SINH  (pSinCosTable->sin_PIby2cSB) // H means "half" - not "hyperbolic"
#define COSH  (pSinCosTable->cos_PIby2cSB)
#define SIN3Q (pSinCosTable->sin_3PIby4cSB)
#define COS3Q (pSinCosTable->cos_3PIby4cSB)
#define SIN1  (pSinCosTable->sin_PIbycSB)
#define COS1  (pSinCosTable->cos_PIbycSB)
#define SIN2  (pSinCosTable->sin_2PIbycSB)
#define COS2  (pSinCosTable->cos_2PIbycSB)
            
            // Q: the vectorized recursion phases require unusual initial "previous" angles not present in standard tables
            // Options:
            //  (1) Use sin(a+b) = sin(a)*cos(b) + cos(a)*sin(b), cos(a+b) = cos(a)*cos(b) - sin(a)*sin(b)
            //  (2) Use sin(a+b) = sin(a-b) + 2*sin(b)*cos(a),    cos(a+b) = cos(a-b) - 2*sin(b)*sin(a)
            //  (3) Try to find suitable values in a table intended for a different cSB
            // Currently doing (1), not sure what is best.
        
            // trig(7/4) = trig(1+3/4)   (better than trig(2-1/4) ?)
            // trig(5/4) = trig(1/2+3/4) (better than trig(1+1/4) ?)
            // sin(a+b) = sin(a)cos(b) + cos(b)sin(a)
            // cos(a+b) = cos(a)cos(b) - sin(a)sin(b)
            
            // Phase3: START = trig(7/4), PRIOR = trig(-1/4)
            bp2SinCur3 = BP2_FROM_BP1(MULT_ADD2_BP1(SIN3Q,COS1,  COS3Q,SIN1));
            bp2CosCur3 = BP2_FROM_BP1(MULT_ADD2_BP1(COS3Q,COS1, -SIN3Q,SIN1));
            bp2SinPrev3 = -BP2_FROM_BP1(SINQ);
            bp2CosPrev3 = BP2_FROM_BP1(COSQ);
        
            // Phase2: START = trig(5/4), PRIOR = trig(-3/4)
            bp2SinCur2 = BP2_FROM_BP1(MULT_ADD2_BP1(SIN3Q,COSH,  COS3Q,SINH));
            bp2CosCur2 = BP2_FROM_BP1(MULT_ADD2_BP1(COS3Q,COSH, -SIN3Q,SINH));
            bp2SinPrev2 = -BP2_FROM_BP1(SIN3Q);
            bp2CosPrev2 = BP2_FROM_BP1(COS3Q);
        
            // Phase1: START = trig(3/4), PRIOR = trig(-5/4)
            bp2SinCur1 = BP2_FROM_BP1(SIN3Q);
            bp2CosCur1 = BP2_FROM_BP1(COS3Q);
            bp2SinPrev1 = -bp2SinCur2;
            bp2CosPrev1 = bp2CosCur2;
        
            // Phase0: START = trig(1/4), PRIOR = trig(-7/4)
            bp2SinCur0 = BP2_FROM_BP1(SINQ);
            bp2CosCur0 = BP2_FROM_BP1(COSQ);
            bp2SinPrev0 = -bp2SinCur3;
            bp2CosPrev0 = bp2CosCur3;
        
            // STEP = 2*sin(1/2 * 4)
            bp2Step = SINSTEP_SCALE(SIN2);
            step = _mm_set1_ps(bp2Step);
    
            sincur = _mm_set_ps(bp2SinCur3, bp2SinCur2, bp2SinCur1, bp2SinCur0);
            coscur = _mm_set_ps(bp2CosCur3, bp2CosCur2, bp2CosCur1, bp2CosCur0);
            sinprev = _mm_set_ps(bp2SinPrev3, bp2SinPrev2, bp2SinPrev1, bp2SinPrev0);
            cosprev = _mm_set_ps(bp2CosPrev3, bp2CosPrev2, bp2CosPrev1, bp2CosPrev0);
        }

        {
            CoefType *pctOut, *pctOut2, *pctHist, *pctNew;
            // move history pointers to start of overlap region
            // move current pointers to end of overlap region
            // move destination pointers to start of overlap region for output
            pctHist = pctCoefHist + iSizePrev/2 - iOverlap;
            pctNew = pctCoefNew + iOverlap - 4;
            pctOut = pctCoefOut + iSizePrev/2 - iOverlap;
            pctOut2 = pctOut + 2*iOverlap - 4;
            while (pctOut < pctOut2)
            {
                {
                    __m128 sum1, sum2;
                    {
                        __m128 sin_times_curr,
                               sin_times_prev,
                               cos_times_curr,
                               cos_times_prev;
                        {
                            __m128 ctPrevData,
                                   ctCurrData;
                            ctPrevData = _mm_load_ps(pctHist);
                            ctCurrData = _mm_load_ps(pctNew); 
                            ctCurrData = _mm_shuffle_ps(ctCurrData, ctCurrData, _MM_SHUFFLE(0,1,2,3));
                            sin_times_curr = _mm_mul_ps(sincur, ctCurrData);
                            sin_times_prev = _mm_mul_ps(sincur, ctPrevData);
                            cos_times_curr = _mm_mul_ps(coscur, ctCurrData);
                            cos_times_prev = _mm_mul_ps(coscur, ctPrevData);
                        }
                        if (bUseDCT)
                        {
                            sum1 = _mm_sub_ps(cos_times_prev, sin_times_curr);
                            sum2 = _mm_add_ps(cos_times_curr, sin_times_prev);
                        }
                        else
                        {
                            sum1 = _mm_add_ps(cos_times_prev, sin_times_curr);
                            sum2 = _mm_sub_ps(cos_times_curr, sin_times_prev);
                        }
                    }
                    sum2 = _mm_shuffle_ps(sum2, sum2, _MM_SHUFFLE(0,1,2,3));
            
                    if (bUseMCLT)
                    {
                        _mm_store_ps(pctOut,  _mm_add_ps(_mm_load_ps(pctOut ), sum1));
                        _mm_store_ps(pctOut2, _mm_add_ps(_mm_load_ps(pctOut2), sum2));
                    }
                    else
                    {
                        _mm_store_ps(pctOut, sum1);
                        _mm_store_ps(pctOut2, sum2);
                    }
                }
        
                pctHist += 4;
                pctNew -= 4;
                pctOut += 4;
                pctOut2 -= 4;
        
                {
                    __m128 sinnext = _mm_add_ps(sinprev, _mm_mul_ps(step, coscur)),
                           cosnext = _mm_sub_ps(cosprev, _mm_mul_ps(step, sincur));
                    sinprev = sincur; sincur = sinnext;
                    cosprev = coscur; coscur = cosnext;
                }
            }
        }
        
    }

    // flat part of first half of cur
    {
        CoefType *pctOut, *pctNew;
        pctNew = pctCoefNew + iOverlap;
        pctOut = pctCoefOut + iSizePrev/2 + iOverlap;
        if (bUseMCLT)
        {
            Int iCoeff;
            for (iCoeff=iOverlap/4; iCoeff < iSizeCurr/2/4; iCoeff++)
            {
                _mm_store_ps(pctOut, _mm_mul_ps(_mm_load_ps(pctNew), _mm_set1_ps(0.5f)));
                pctOut += 4;
                pctNew += 4;
            }
        }
        else
        {
            memcpy(pctOut, pctNew, (iSizeCurr/2 - iOverlap) * sizeof(CoefType));
        }
    }

    return wmaResult;
}
#endif // WMA_TARGET_X86 && BUILD_INT_FLOAT && !WMA_DISABLE_SSE1
#endif

#if defined(BUILD_WMAPROLBRV2)

// obtain dst from idct for (prev, curr, next)
Void auDSTFromDCTV3(CAudioObject *pau,
                    CoefType *pctDST,
                    const CoefType *pctIDCTPrev,
                    const CoefType *pctIDCTCurr,
                    const CoefType *pctIDCTNext,
                    Int iSizePrev, Int iSizeCurr, Int iSizeNext)
{
    const CoefType *pctP2;
    const CoefType *pctC0;
    const CoefType *pctC2;
    const CoefType *pctN0;
    CoefType *pDST;
    Int i, iPrevOverlap, iNextOverlap;
    TR2_TYPE bp2Sin, bp2Cos, bp2SinPrev, bp2CosPrev, bp2Step;
    const SinCosTable *pSinCosTable;

    iPrevOverlap = min(iSizePrev, iSizeCurr)/2;
    iNextOverlap = min(iSizeNext, iSizeCurr)/2;

    // DCT unfolding from [A B] is [-B BF AF A]
    // DST folding from [1 2 3 4] is [3F-4 2F+1]

    //pctPrev2 = pctIDCTPrev + iSizePrev/2 - 1; // AF, go backward
    //pctPrev3 = pctIDCTPrev; // A, go forward

    //pctCurr0 = pctIDCTCurr + iSizeCurr/2; // B, go forward, negate
    //pctCurr1 = pctIDCTCurr + iSizeCurr - 1; // BF, go backward
    //pctCurr2 = pctIDCTCurr + iSizeCurr/2 - 1; // AF, go backward
    //pctCurr3 = pctIDCTCurr; // A, go forward

    //pctNext0 = pctIDCTNext + iSizeNext/2; // B, go forward, negate
    //pctNext1 = pctIDCTNext + iSizeNext - 1; // BF, go backward

    // First quadrant of curr - apply rising window w0P
    // zeros
    // - (iSizeCurr/2)-iPrevOverlap
    // overlap with prev, take
    // - last  iPrevOverlap coeffs from pctPrev2 (falling window - w2P)
    // - last  iPrevOverlap coeffs from pctCurr0 (rising  window - w0P)
    //
    // Second quadrant of curr - apply rising window w1P
    // overlap with prev, take
    // - first iPrevOverlap coeffs from pctPrev3 (falling window - w3P)
    // - first iPrevOverlap coeffs from pctCurr1 (rising  window - w1P)
    // flat portion
    // - last  (iSizeCurr/2)-iPrevOverlap coeffs from pctCurr1
    //
    // Third quadrant of curr - apply falling window w2N
    // flat portion
    // - first (iSizeCurr/2)-iNextOverlap coeffs from pctCurr2
    // overlap with next, take
    // - last  iNextOverlap coeffs from pctCurr2 (falling window - w2N)
    // - last  iNextOverlap coeffs from pctNext0 (rising  window - w0N)
    //
    // Fourth quadrant of curr - apply falling window w3N
    // overlap with next, take
    // - first iNextOverlap coeffs from pctCurr3 (falling window - w3N)
    // - first iNextOverlap coeffs from pctNext1 (rising  wingow - w1N)
    // zeros
    // - (iSizeCurr/2)-iNextOverlap

    assert (SINCOSTABLE_ENTRIES > (iNextOverlap>>6));
    pSinCosTable = rgSinCosTables[iNextOverlap>>6];
    // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
    bp2Sin  =  TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB); // rising
    bp2Cos  =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB); // falling
    // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
    bp2SinPrev = -TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2CosPrev =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    // STEP = 2*sin(PI/2/iSizeCurr)
    bp2Step = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));

    // 3F-4
    // Windows generated are going to be w0-sin & w2-cos (or w1F-cos & w3F-sin)
    // For 3F, need w2NF & w0NF & w2NF
    // For  4, need w1N  & w3N  & w3N
    // Do 3F-4 backwards, i.e. do 3-4F and store backwards

    // Pointers for 3
    // go backwards, falling window w2N -- apply window w2N
    //pctC2 = pctCurr2;
    // go forward, negate, rising window w0N -- apply window w2N
    // move pointer so that we get last iNextOverlap coeffs
    //pctN0 = pctNext0 + iSizeNext/2 - iNextOverlap;
    pctC2 = pctIDCTCurr + iSizeCurr/2 - 1;
    pctN0 = pctIDCTNext + iSizeNext - iNextOverlap;

    // Pointers for 4F
    // go backwards - rising window w3NF -- apply window w3NF
    //pctC3F = pctCurr3 + iSizeCurr/2 - 1;
    // go forward - falling window w1NF -- apply window w3NF
    //pctN1F = pctNext1 - iNextOverlap + 1;

    // Note pctC2 == pctC3F && pctN1F == pctN0 always

    pDST = pctDST + iSizeCurr/2;
    for (i=0; i < iSizeCurr/2-iNextOverlap; i++)
    {
        *pDST = *pctC2;
        
        pDST++;
        pctC2--;
    }
    for (; i < iSizeCurr/2; i++)
    {
        // windows being generated are w0-sin & w2-cos (or w1F-cos & w3F-sin)
        // 3F term
        *pDST  = MULT_BP2(BP2_FROM_TR2(bp2Cos), MULT_ADD2_BP2( *pctC2, BP2_FROM_TR2(bp2Cos),  -*pctN0, BP2_FROM_TR2(bp2Sin) ) );
        // -4 term
        *pDST -= MULT_BP2(BP2_FROM_TR2(bp2Sin), MULT_ADD2_BP2( *pctC2, BP2_FROM_TR2(bp2Sin),   *pctN0, BP2_FROM_TR2(bp2Cos) ) );

        TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2CosPrev, bp2SinPrev, bp2Step);
        /*
        bp2SinTemp = bp2SinPrev + MULT_TR2(bp2Step, bp2Cos);
        bp2CosTemp = bp2CosPrev - MULT_TR2(bp2Step, bp2Sin);
        bp2SinPrev = bp2Sin;  bp2Sin = bp2SinTemp;
        bp2CosPrev = bp2Cos;  bp2Cos = bp2CosTemp;
        */

        pDST++;
        pctC2--;
        pctN0++;
    }

    assert (SINCOSTABLE_ENTRIES > (iPrevOverlap>>6));
    pSinCosTable = rgSinCosTables[iPrevOverlap>>6];
    bp2Sin  =  TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB); // rising
    bp2Cos  =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB); // falling
    bp2SinPrev = -TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2CosPrev =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    bp2Step = TR2_FROM_BP1(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));

    // 2F+1
    // Windows generated are going to be w0-sin & w2-cos (or w1F-cos & w3F-sin)
    // For 2F, need w1PF & w3PF & w1PF
    // For  1, need w0P  & w2P  & w0P

    // Pointers for 2F
    // go backward - rising window w3PF, apply window w1PF
    //pctP3F = pctPrev3 + iPrevOverlap - 1;
    // go forward - falling window w1PF, apply window w1PF
    //pctC1F = pctCurr1 - iSizeCurr/2 + 1;

    // Pointers for 1
    // go backwards - falling window w2P, apply window w0P
    //pctP2  = pctPrev2 - iSizePrev/2 + iPrevOverlap;
    // go forward - negate - rising window w0P, apply window w0P
    //pctC0  = pctCurr0;
    pctC0 = pctIDCTCurr + iSizeCurr/2;
    pctP2 = pctIDCTPrev + iPrevOverlap - 1;

    // Note pctP2 == pctP3F && pctC0 == pctC1F

    pDST = pctDST + iSizeCurr/2 - 1;
    for (i=0; i < iSizeCurr/2-iPrevOverlap; i++)
    {
        *pDST = *pctC0;

        pDST--;
        pctC0++;
    }
    for (; i < iSizeCurr/2; i++)
    {
        // windows being generated are w0-sin & w2-cos (or w1F-cos & w3F-sin)
        // 2F term
        *pDST  = MULT_BP2(BP2_FROM_TR2(bp2Cos), MULT_ADD2_BP2( *pctP2, BP2_FROM_TR2(bp2Sin),  *pctC0, BP2_FROM_TR2(bp2Cos) ) );
        // 1 term
        *pDST += MULT_BP2(BP2_FROM_TR2(bp2Sin), MULT_ADD2_BP2( *pctP2, BP2_FROM_TR2(bp2Cos), -*pctC0, BP2_FROM_TR2(bp2Sin) ) );

        TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2CosPrev, bp2SinPrev, bp2Step)
        /*
        bp2SinTemp = bp2SinPrev + MULT_TR2(bp2Step, bp2Cos);
        bp2CosTemp = bp2CosPrev - MULT_TR2(bp2Step, bp2Sin);
        bp2SinPrev = bp2Sin;  bp2Sin = bp2SinTemp;
        bp2CosPrev = bp2Cos;  bp2Cos = bp2CosTemp;
        */

        pDST--;
        pctC0++;
        pctP2--;
    }

    catchFP();
    // forward DST-IV
    chexDstHelperNoFlip(pau, NULL, pctDST, BP2_FROM_FLOAT(1.0f), iSizeCurr);
    initFP();
}

#endif // BUILD_WMAPROLBRV2

#if 0
// test DST from DCT function

Void prvObtainSamplesFromFile(CAudioObject *pau,
                              const TCHAR *szFile, Int iStart, Int iLen,
                              Int iCh, CoefType *pCoeff);

Void auTestDSTFromDCT(CAudioObject *pau)
{
    Int iSizePrev = 512;
    Int iSizeCurr = 512;
    Int iSizeNext = 512;
    Int iSizeTotal = iSizePrev+iSizeCurr+iSizeNext+iSizePrev/2+iSizeNext/2;
    Int i;
    __declspec(align(32)) CoefType rgBuf[4096], rg0[4096], rg1[4096], rg2[4096], rg3[4096];

#if 0
    srand(1234);

    for (i=0; i < iSizeTotal; i++)
        rgBuf[i] = (rand()/RAND_MAX - 0.5f)*20000;
#else
    prvObtainSamplesFromFile(pau, "d:/sanjeevm/progs/misc/test/bbb.wav",
                             400000, iSizeTotal, 0, rgBuf);
#endif

    for (i=0; i < 2*iSizePrev; i++)
        rg0[i] = rgBuf[i];

    for (i=0; i < 2*iSizeCurr; i++)
        rg1[i] = rgBuf[i+iSizePrev/2+iSizePrev-iSizeCurr/2];

    for (i=0; i < 2*iSizeNext; i++)
        rg2[i] = rgBuf[i+iSizePrev/2+iSizePrev+iSizeCurr-iSizeNext/2];

    pau->m_pfnApplyWindow(pau, rg0, iSizePrev, iSizePrev, iSizeCurr, WMAB_FALSE);
    auApplyReflectionV3(rg0, iSizePrev);
    chexDctHelper(pau, NULL, rg0, 1.0f, iSizePrev);

    pau->m_pfnApplyWindow(pau, rg1, iSizePrev, iSizeCurr, iSizeNext, WMAB_FALSE);
    auApplyReflectionV3(rg1, iSizeCurr);
    chexDctHelper(pau, NULL, rg1, 1.0f, iSizeCurr);
    chexDstHelper(pau, NULL, rg1+iSizeCurr, 1.0f, iSizeCurr);

    pau->m_pfnApplyWindow(pau, rg2, iSizeCurr, iSizeNext, iSizeNext, WMAB_FALSE);
    auApplyReflectionV3(rg2, iSizeNext);
    chexDctHelper(pau, NULL, rg2, 1.0f, iSizeNext);

    chexDctHelper(pau, NULL, rg0, 2.0f/iSizePrev, iSizePrev);
    chexDctHelper(pau, NULL, rg1, 2.0f/iSizeCurr, iSizeCurr);
    chexDctHelper(pau, NULL, rg2, 2.0f/iSizeNext, iSizeNext);

    auDstFromDctV3(pau, rg3, rg0, rg1, rg2,
                   iSizePrev, iSizeCurr, iSizeNext);

    printf("");
}

#endif // #if 0

// Apply 2N->N point reflection prior to dct/dst
//
// apply reflection transformation so that first half becomes for DCT
// 2nd half becomes for DST
//
// given four quadrants of (2*iSizeCurr) window label as [1 2 3 4]
// reflection transformation becomes (where F=flip)
// DCT: [3F+4 2F-1]
// DST: [3F-4 2F+1]
#if 1

#define REFL_HALF (REFL_SIZE / 2)
#define REFL_THREEHALVES (3 * REFL_SIZE / 2)

#define pct1Begin (pct0Begin + REFL_HALF)
#define pct1End (pct0End + REFL_HALF)
#define pct2Begin (pct0Begin + REFL_SIZE)
#define pct2End (pct0End + REFL_SIZE)
#define pct3Begin (pct0Begin + REFL_THREEHALVES)
#define pct3End (pct0End + REFL_THREEHALVES)

#define REFL_SIZE 64
Void auApplyReflectionV3_64(CoefType *pctCoef)
#include "applyreflectionv3.h"
#undef REFL_SIZE

#define REFL_SIZE 128
Void auApplyReflectionV3_128(CoefType *pctCoef)
#include "applyreflectionv3.h"
#undef REFL_SIZE

#define REFL_SIZE 256
Void auApplyReflectionV3_256(CoefType *pctCoef)
#include "applyreflectionv3.h"
#undef REFL_SIZE

#define REFL_SIZE 512
Void auApplyReflectionV3_512(CoefType *pctCoef)
#include "applyreflectionv3.h"
#undef REFL_SIZE

#define REFL_SIZE 1024
Void auApplyReflectionV3_1024(CoefType *pctCoef)
#include "applyreflectionv3.h"
#undef REFL_SIZE

#define REFL_SIZE 2048
Void auApplyReflectionV3_2048(CoefType *pctCoef)
#include "applyreflectionv3.h"
#undef REFL_SIZE

// optimized version
Void auApplyReflectionV3(CoefType *pctCoef, Int iSizeCurr)
{
    switch(iSizeCurr){
    case 256: auApplyReflectionV3_256(pctCoef); break;
    case 128: auApplyReflectionV3_128(pctCoef); break;
    case 2048: auApplyReflectionV3_2048(pctCoef); break;
    case 1024: auApplyReflectionV3_1024(pctCoef); break;
    case 512: auApplyReflectionV3_512(pctCoef); break;
    case 64: auApplyReflectionV3_64(pctCoef); break;
    default: assert(0);
    }
}
#else
// original reference code
Void auApplyReflectionV3(CoefType *pctCoef, Int iSizeCurr)
{
    Int i;
    CoefType ct0, ct1, ct3;
    CoefType *pctTop, *pctBottom, *pct0, *pct1, *pct2, *pct3;

    // Implement [2F-1 2F+1] transform
    pctTop = pctCoef; // 1
    pctBottom = pctCoef + iSizeCurr - 1; // 2F
    for (i=0; i < iSizeCurr/2; i++)
    {
        ct0 = *pctBottom - *pctTop; // 2F-1
        ct1 = *pctBottom + *pctTop; // 2F+1
        *pctTop = ct0; // (2F-1) --> goes into 1st quadrant
        *pctBottom = ct1; // (2F+1)F --> goes into 2nd quadrant flipped
        pctTop++;
        pctBottom--;
    }

    // Implement [3F-4 3F+4] transform
    pctTop = pctCoef + (3*iSizeCurr/2); // 4
    pctBottom = pctTop - 1; // 3F
    for (i=0; i < iSizeCurr/2; i++)
    {
        ct0 = *pctBottom - *pctTop; // 3F-4
        ct1 = *pctBottom + *pctTop; // 3F+4
        *pctTop = ct1; // (3F+4) --> goes into 4th quadrant
        *pctBottom = ct0; // (3F-4)F --> goes into 3rd qudrant flipped
        pctTop++;
        pctBottom--;
    }

    // now we have the following [(2F-1) (2F+1)F (3F-4)F (3F+4)]
    // want                      [(3F+4) (2F-1)  (3F-4)  (2F+1)]
    // the 4 quadrants
    pct0 = pctCoef;
    pct1 = pctCoef + iSizeCurr/2;
    pct2 = pctCoef + iSizeCurr;
    pct3 = pctCoef + 3*iSizeCurr/2;
    // flip 2nd & 3rd quadrants
    auFlipCoeff(pct1, iSizeCurr/2);
    auFlipCoeff(pct2, iSizeCurr/2);
    // swap quadrants
    for (i=0; i < iSizeCurr/2; i++)
    {
        ct0 = *pct0;
        ct1 = *pct1;
        ct3 = *pct3;
        *pct0 = ct3;
        *pct1 = ct0;
        *pct3 = ct1;
        pct0++;
        pct1++;
        pct3++;
    }
}
#endif

// applies partial reflection needed for dct/dst
// DCT reflection can be written as [3F 2F] + [4 -1]
// DST reflection can be written as [3F 2F] - [4 -1]
// this function does the reflection [3F 2F 4 -1]
// DCT can be written as DCT([3F 2F]) + DCT([4 -1])
// DST can be written as DST([3F 2F]) - DST([4 -1])
Void auApplyReflectionPartialV3(CoefType *pctCoef, Int iSizeCurr)
{
    CoefType ct0, ct1, ct2, ct3;
    CoefType *pct0, *pct1, *pct2, *pct3;
    Int i;

    pct0 = pctCoef;
    pct1 = pctCoef + iSizeCurr/2;
    pct2 = pctCoef + iSizeCurr;
    pct3 = pctCoef + 3*iSizeCurr/2;
    // flip 2nd & 3rd quadrants to obtain [1 2F 3F 4]
    auFlipCoeff(pct1, iSizeCurr/2);
    auFlipCoeff(pct2, iSizeCurr/2);
    // swap coefficients to get [3F 2F 4 -1]
    for (i=0; i < iSizeCurr/2; i++)
    {
        ct0 = *pct0;
        ct1 = *pct1;
        ct2 = *pct2;
        ct3 = *pct3;
        *pct0 = ct2;
        *pct1 = ct1;
        *pct2 = ct3;
        *pct3 = -ct0;
        pct0++;
        pct1++;
        pct2++;
        pct3++;
    }
}

Void auShiftHistoryV3(CoefType *pctCoefHist,
                      CoefType *pctCoefNew,
                      Int iSizeCurr,
                      Bool bFlip)
{
    // implement: buf(1:sf/2) = buf(curLen+1:curLen+sf/2); (matlab)
    //
    // the last cur/2 samples from coef new need to be stored
    // in the last cur/2 samples in history
    if (bFlip)
        memcpy(pctCoefHist,
               pctCoefNew+iSizeCurr/2,
               iSizeCurr/2*sizeof(CoefType));
    else
        memcpy(pctCoefHist,
               pctCoefNew,
               iSizeCurr/2*sizeof(CoefType));
}

#if defined BUILD_WMAPROLBRV1

// =========================================================================

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON

Void prvObtainSamplesFromFile(CAudioObject *pau,
                              const TCHAR *szFile, Int iStart, Int iLen,
                              Int iCh, CoefType *pCoeff)
{
#define BUF_SIZE (500)
    WavFileIO *pwfio = NULL;
    WAVEFORMATEXTENSIBLE wfx;
    U8 pBuf[BUF_SIZE];
    Int iAmt, iAmtRead, iBufSize, iLenRead, i;
    PCMSAMPLE *p;

    pwfio = wfioNew();
    if (!pwfio)
        goto exit;

    if (wfioOpen(pwfio, szFile, &wfx, 0, wfioModeRead) < 0)
        goto exit;

    iStart *= wfx.Format.nBlockAlign;

    iBufSize = BUF_SIZE/wfx.Format.nBlockAlign*wfx.Format.nBlockAlign;

    if (wfioSeekNoBoundary(pwfio, iStart) < 0)
        goto exit;

    while (1)
    {
        iAmt = min(iBufSize, iLen*wfx.Format.nBlockAlign);
        iAmtRead = wfioReadNoBoundary(pwfio, pBuf, iAmt);
        iLenRead = iAmtRead / wfx.Format.nBlockAlign;

        p = PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pBuf, iCh);
        for (i=0; i < iLenRead; i++)
        {
            pCoeff[i] = (CoefType)PAUPFNGETSAMPLE0(p);
            p = PAUPRVADVANCEPCMPTR(p, pau->m_cChannel);
        }

        iLen -= iLenRead;
        pCoeff += iLenRead;
        if (iLen <= 0 || iAmtRead <= 0)
            break;
    }

exit:
    if (pwfio)
        wfioDelete(pwfio);
#undef BUF_SIZE
}

Void prvMclt(CAudioObject *pau, PerChannelInfo *ppcinfo,
             CoefType *pCoef, Int iSizePrev, Int iSizeCurr, Int iSizeNext,
             Bool bMLTOnly)
{
    pau->m_pfnApplyWindow(pau, pCoef, iSizePrev, iSizeCurr, iSizeNext, WMAB_FALSE);
    auApplyReflectionV3(pCoef, iSizeCurr);
#if defined(BUILD_WMAPROLBRV2)
    catchFP();
    chexDctHelper(pau, ppcinfo, pCoef, 1.0f, iSizeCurr);
    if (!bMLTOnly)
        chexDstHelper(pau, ppcinfo, pCoef+iSizeCurr, 1.0f, iSizeCurr);
    initFP();
#endif
}

CoefType *g_pReplBuf[MAX_CHANNEL];

Void prvReplaceSamplesFromFileCh(CAudioObject *pau, const TCHAR *szFile,
                                 PerChannelInfo *ppcinfo, Int iCh,
                                 Int iStart, Int iEnd)
{
    Int iStartPt = ppcinfo->m_iStartPtInFile-ppcinfo->m_cSubFrameSampleHalf/2;

    if (NULL == g_pReplBuf[iCh])
    {
        // mem leak in debugging code
        g_pReplBuf[iCh] =
            (CoefType*)mallocAligned(pau->m_cFrameSampleHalf*2*
                                     sizeof(CoefType), 32);
        if (!g_pReplBuf[iCh])
            return;
    }

    prvObtainSamplesFromFile(pau, szFile, iStartPt,
                             ppcinfo->m_cSubFrameSampleHalf*2,
                             iCh, g_pReplBuf[iCh]);

    prvMclt(pau, ppcinfo, g_pReplBuf[iCh],
            ppcinfo->m_iSizePrev, ppcinfo->m_iSizeCurr, ppcinfo->m_iSizeNext,
            WMAB_TRUE);

    iStart = max(iStart, 0);
    if (iEnd >= 0)
        iEnd = min(iEnd, ppcinfo->m_cSubFrameSampleHalf);
    else
        iEnd = ppcinfo->m_cSubFrameSampleHalf;

    if (iEnd-iStart > 0)
        memcpy(ppcinfo->m_rgCoefRecon+iStart, g_pReplBuf[iCh]+iStart,
               (iEnd-iStart)*sizeof(CoefType));
}

Void prvReplaceSamplesExtBufCh(CAudioObject *pau,
                               PerChannelInfo *ppcinfo,
                               Int iStart, Int iEnd)
{
    Int iCh = (Int)(ppcinfo - pau->m_rgpcinfo);

    if (iEnd-iStart > 0)
        memcpy(ppcinfo->m_rgCoefRecon+iStart, g_pReplBuf[iCh]+iStart,
               (iEnd-iStart)*sizeof(CoefType));
}

Bool g_bReplaceForFex = 0;
Bool g_bReplaceForChex = 0;
Bool g_bReplaceCFx = 0;
TCHAR g_szReplaceFile[256];
Bool g_bVerify = 0;
Int g_iNTilesPerFrame = -1;
Int g_iCodingMethod = -1;
Int g_iCodeAll = -1;
Int g_iPowerForAllBands = -1;
Int g_iPreservePower = -1;
Int g_iPredScale = -1;
Int g_iPredPhase = -1;
Int g_iScBins = -1;
Int g_iPhBins = -1;
Int g_iPowerBins = -1;
Int g_iScPredBins = -1;
Int g_iPhPredBins = -1;
Int g_iPowerPredBins = -1;

#include "strsafe.h"
Void initReplArgs()
{
    FILE *fp = fopen("replargs.txt", "rt");

    if (NULL!=fp)
    {
        char argval[100]; // how to know what is max size when reading string?
        while (fscanf(fp, "%s", argval) != EOF)
        {
            if (!strcmpi(argval, "-replfex"))
            {
                fscanf(fp, "%d", &g_bReplaceForFex);
                printf("ReplaceForFex = %d\n", g_bReplaceForFex);
            }
            else if (!strcmpi(argval, "-replchex"))
            {
                fscanf(fp, "%d", &g_bReplaceForChex);
                printf("ReplaceForChex = %d\n", g_bReplaceForChex);
            }
            else if (!strcmpi(argval, "-replcfx"))
            {
                fscanf(fp, "%d", &g_bReplaceCFx);
                printf("ReplaceCFx = %d\n", g_bReplaceCFx);
            }
            else if (!strcmpi(argval, "-replfile"))
            {
                fscanf(fp, "%s", argval);
                StringCchCopy(g_szReplaceFile, 256, argval);
                printf("ReplacementFile = %s\n", g_szReplaceFile);
            }
            else if (!strcmpi(argval, "-verify"))
            {
                fscanf(fp, "%d", &g_bVerify);
                printf("Verify = %d\n", g_bVerify);
            }
            else if (!strcmpi(argval, "-ntileperframe"))
            {
                fscanf(fp, "%d", &g_iNTilesPerFrame);
                printf("NTilesPerFrame = %d\n", g_iNTilesPerFrame);
            }
            else if (!strcmpi(argval, "-codemethod"))
            {
                fscanf(fp, "%d", &g_iCodingMethod);
                printf("CodingMethod = %d\n", g_iCodingMethod);
            }
            else if (!strcmpi(argval, "-codeall"))
            {
                fscanf(fp, "%d", &g_iCodeAll);
                printf("CodeAll = %d\n", g_iCodeAll);
            }
            else if (!strcmpi(argval, "-powerall"))
            {
                fscanf(fp, "%d", &g_iPowerForAllBands);
                printf("PowerForAllBands = %d\n", g_iPowerForAllBands);
            }
            else if (!strcmpi(argval, "-ppower"))
            {
                fscanf(fp, "%d", &g_iPreservePower);
                printf("PreservePower = %d\n", g_iPreservePower);
            }
            else if (!strcmpi(argval, "-predsc"))
            {
                fscanf(fp, "%d", &g_iPredScale);
                printf("PredScale = %d\n", g_iPredScale);
            }
            else if (!strcmpi(argval, "-predph"))
            {
                fscanf(fp, "%d", &g_iPredPhase);
                printf("PredPhase = %d\n", g_iPredPhase);
            }
            else if (!strcmpi(argval, "-scbins"))
            {
                fscanf(fp, "%d", &g_iScBins);
                printf("ScBins = %d\n", g_iScBins);
            }
            else if (!strcmpi(argval, "-phbins"))
            {
                fscanf(fp, "%d", &g_iPhBins);
                printf("PhBins = %d\n", g_iPhBins);
            }
            else if (!strcmpi(argval, "-powerbins"))
            {
                fscanf(fp, "%d", &g_iPowerBins);
                printf("PowerBins = %d\n", g_iPowerBins);
            }
            else if (!strcmpi(argval, "-scpredbins"))
            {
                fscanf(fp, "%d", &g_iScPredBins);
                printf("ScPredBins = %d\n", g_iScPredBins);
            }
            else if (!strcmpi(argval, "-phpredbins"))
            {
                fscanf(fp, "%d", &g_iPhPredBins);
                printf("PhPredBins = %d\n", g_iPhPredBins);
            }
            else if (!strcmpi(argval, "-powerpredbins"))
            {
                fscanf(fp, "%d", &g_iPowerPredBins);
                printf("PowerPredBins = %d\n", g_iPowerPredBins);
            }
        }

        fclose(fp);
    }
}

Void prvObtainReplStartEndFromFreq(CAudioObject *pau, Int iSize,
                                   Float fStart, Float fEnd,
                                   Int *piStart, Int *piEnd)
{
    Float fMaxFreq = pau->m_iSamplingRate/2.0f;

    if (fStart < 0)
        *piStart = 0;
    else
        *piStart = ROUNDF(fStart*iSize/fMaxFreq);
    *piStart = checkRange(*piStart, 0, iSize);

    if (fEnd < 0 || fEnd >= fMaxFreq)
        *piEnd = iSize;
    else
        *piEnd = ROUNDF(fEnd*iSize/fMaxFreq);
    *piEnd = checkRange(*piEnd, 0, iSize);
}

Void prvReplaceSamplesFromFile(CAudioObject *pau, Float fStart, Float fEnd)
{
    Int iCh, iChSrc;
    PerChannelInfo *ppcinfo;
    Int iStart, iEnd;

    ppcinfo = pau->m_rgpcinfo + pau->m_rgiChInTile[0];

    prvObtainReplStartEndFromFreq(pau, ppcinfo->m_cSubFrameSampleHalf,
                                  fStart, fEnd, &iStart, &iEnd);

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        //one in the tile
        iChSrc  = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;
        prvReplaceSamplesFromFileCh(pau, g_szReplaceFile, ppcinfo, iChSrc,
                                    iStart, iEnd);
    }
}

Void prvReplaceSamplesFromMonoBuf(CAudioObject *pau, ReconTileInfo *prti,
                                  Int iCh, CoefType *pBuf);

Void prvReplaceSamplesFromFileReconProc(CAudioObject *pau,
                                        ReconTileInfo *prti,
                                        Int iChCode, CoefType *pDest,
                                        Float fStart, Float fEnd)
{
    Int iCh, iStartPt, i, nCh, iStart, iEnd;
    static CoefType *pBuf=NULL;
    static CoefType *pBufMono=NULL;

    if (pau->m_bEncoder && !strcmp(g_szReplaceFile, ""))
    {
        prvReplaceSamplesFromMonoBuf(pau, prti, iChCode, pDest);
        return;
    }

    prvObtainReplStartEndFromFreq(pau, prti->m_iSizeCurr,
                                  fStart, fEnd, &iStart, &iEnd);

    if (0 == iChCode || !pau->m_bCx)
    {
        if (pBuf)
        {
            freeAligned(pBuf);
            pBuf = NULL;
        }
        if (pBufMono)
        {
            freeAligned(pBufMono);
            pBufMono = NULL;
        }
        pBuf = (CoefType*)mallocAligned(pau->m_cFrameSampleHalf*2*
                                        sizeof(CoefType), 32);
        if (!pBuf)
            return;
        pBufMono = (CoefType*)mallocAligned(pau->m_cFrameSampleHalf*2*
                                            sizeof(CoefType), 32);
        if (!pBufMono)
            return;
    }

    iStartPt = prti->m_iStartPtInFile-prti->m_iSizeCurr/2;

    if (pau->m_bCx)
    {
        if (0 == iChCode)
        {
            nCh=0;
            memset(pBufMono, 0, 2*prti->m_iSizeCurr*sizeof(CoefType));
            for (iCh=0; iCh < pau->m_cChannel; iCh++)
            {
                if (!(prti->m_uChannelMask & (1<<iCh)))
                    continue;
            
                prvObtainSamplesFromFile(pau, g_szReplaceFile, iStartPt,
                                         prti->m_iSizeCurr*2, iCh, pBuf);
                prvMclt(pau, NULL, pBuf,
                       prti->m_iSizePrev, prti->m_iSizeCurr, prti->m_iSizeNext,
                       WMAB_FALSE);

                for (i=0; i < 2*prti->m_iSizeCurr; i++)
                    pBufMono[i] += pBuf[i];

                nCh++;
            }
            for (i=0; i < 2*prti->m_iSizeCurr; i++)
                pBufMono[i] /= nCh;
        }
    }
    else
    {
        prvObtainSamplesFromFile(pau, g_szReplaceFile, iStartPt,
                                 prti->m_iSizeCurr*2, iChCode, pBufMono);
        prvMclt(pau, NULL, pBufMono,
                prti->m_iSizePrev, prti->m_iSizeCurr, prti->m_iSizeNext,
                WMAB_FALSE);
    }
    if (iEnd-iStart > 0)
    {
        // DCT
        memcpy(pDest+iStart,
               pBufMono+iStart,
               (iEnd-iStart)*sizeof(CoefType));
        // DST
        memcpy(pDest+prti->m_iSizeCurr+iStart,
               pBufMono+prti->m_iSizeCurr+iStart,
               (iEnd-iStart)*sizeof(CoefType));
    }

    if (pau->m_cChannel-1 == iChCode || !pau->m_bCx)
    {
        freeAligned(pBuf);
        freeAligned(pBufMono);
        pBuf = NULL;
        pBufMono = NULL;
    }
}

#if defined(ALLOW_EXTERNAL_FILE_FOR_RECON)
Void prvReplaceSamplesFromFilePostXForm(CAudioObject *pau)
{
    Int iCh, iChSrc, iStart;
    PerChannelInfo *ppcinfo;
    CoefType *pBuf=NULL;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        //one in the tile
        iChSrc  = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        if (0 == iCh)
        {
            pBuf = (CoefType*)mallocAligned(ppcinfo->m_cSubFrameSampleHalf*2*
                                            sizeof(CoefType), 32);
            if (!pBuf)
                return;
        }

        iStart = ppcinfo->m_iStartPtInFile-ppcinfo->m_cSubFrameSampleHalf/2;

        prvObtainSamplesFromFile(pau, g_szReplaceFile, iStart,
                                 ppcinfo->m_cSubFrameSampleHalf*2,
                                 iCh, pBuf);
        pau->m_pfnApplyWindow(pau, pBuf, ppcinfo->m_iSizePrev, ppcinfo->m_iSizeCurr,
                      ppcinfo->m_iSizeNext,
                      WMAB_FALSE);
        auApplyReflectionV3(pBuf, ppcinfo->m_iSizeCurr);

        memcpy(ppcinfo->m_rgCoefRecon, pBuf,
               ppcinfo->m_cSubFrameSampleHalf*sizeof(CoefType));
    }

    freeAligned(pBuf);
}
#endif

Void prvCreateMono(CAudioObject *pau)
{
    PerChannelInfo *ppcinfo0, *ppcinfo1;
    Int i;
    CoefType avg;

    assert(2 == pau->m_cChInTile);

    ppcinfo0 = pau->m_rgpcinfo + 0;
    ppcinfo1 = pau->m_rgpcinfo + 1;

    for (i=0; i < ppcinfo0->m_cSubFrameSampleHalf; i++)
    {
        avg = (ppcinfo0->m_rgCoefRecon[i] + ppcinfo1->m_rgCoefRecon[i])/2;
        ppcinfo0->m_rgCoefRecon[i] = avg;
        ppcinfo1->m_rgCoefRecon[i] = avg;
    }
}
 
#endif // ALLOW_EXTERNAL_FILE_FOR_RECON

#if (!defined(UNDER_CE) && defined(DEBUG))
Void prvDumpQuantStepSizesV3(CAudioObject *pau, FILE *fp)
{
    Int iCh, iChSrc, iBark, iIndex, iMaskQ;
    Double dGlobal, dCh, dBark;
    PerChannelInfo *ppcinfo;
    Bool bSkip;
    static Int count = 0;
    FILE_DUMP_INIT(quant);

#define QS(x) (pow(10.0f, (x)/20.0f))

    auConvertSubframeConfigToTileConfig(pau, CONFIG_CURRFRM);

    bSkip = WMAB_TRUE;
    for (iCh=0; iCh < pau->m_cChannel; iCh++)
        if (pau->m_rgpcinfo[pau->m_rgiChInTile[iCh]].m_iPower != 0)
            bSkip = WMAB_FALSE;

    if (bSkip)
        goto exit;

    dGlobal = QS(pau->m_iQuantStepSize);
    fprintf(fp, "FRAMENUM=%d TILE=%d SIZE=%d\n",
            pau->m_iFrameNumber, pau->m_iCurrTile,
            pau->m_rgtci[pau->m_iCurrTile].m_iSubFrameSize);
    fprintf(fp, "QUANTSTEP=%d %f\n", pau->m_iQuantStepSize, dGlobal);
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        dCh = QS(ppcinfo->m_ucQuantStepModifierIndex);
        fprintf(fp, "  CH=%d\n", iCh);
        fprintf(fp, "  CHMOD=%d %f\n", ppcinfo->m_ucQuantStepModifierIndex,
                dCh);
        for (iBark=0; iBark < pau->m_cValidBarkBand; iBark++)
        {
            Bool fMaskUpdate =
                ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0];
            if (fMaskUpdate || pau->m_bEncoder) {
                iMaskQ = ppcinfo->m_rgiMaskQ[iBark];
                iIndex = (ppcinfo->m_iMaxMaskQ -
                          ppcinfo->m_rgiMaskQ[iBark]) *
                    ppcinfo->m_iMaskQuantMultiplier;
            } else {
                iMaskQ = ppcinfo->m_rgiMaskQResampled[iBark];
                iIndex = (ppcinfo->m_iMaxMaskQ -
                          ppcinfo->m_rgiMaskQResampled[iBark]) *
                    ppcinfo->m_iMaskQuantMultiplier;
            }
            iIndex = -iIndex;

            dBark = QS(iIndex);
            fprintf(fp, "    BARK=%d %d\n", iBark, count);
            fprintf(fp, "    BARKMOD=%d %f\n", iIndex, dBark);
            fprintf(fp, "    QUANT=%f\n", dGlobal*dCh*dBark);
            fprintf(fp, "    MAXMASKQ=%d MASKQ=%d MULT=%d UPDATE=%d\n",
                    ppcinfo->m_iMaxMaskQ,
                    (fMaskUpdate || pau->m_bEncoder) ?
                    ppcinfo->m_rgiMaskQ[iBark] :
                    ppcinfo->m_rgiMaskQResampled[iBark],
                    ppcinfo->m_iMaskQuantMultiplier, fMaskUpdate);
            count++;
        }
    }

 exit:;
#undef QS
}
#endif

#endif // BUILD_WMAPROLBRV1

#endif // BUILD_WMAPRO

