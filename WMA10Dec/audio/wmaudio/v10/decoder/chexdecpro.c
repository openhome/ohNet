//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "msaudiodec.h"

#if defined(BUILD_WMAPROLBRV2)

#include "huffdec.h"
#include "chexpro.h"
#include "fex.h"
#include "chexdectblspro.h"

// =========================================================================
// CHEX routines

INLINE
WMARESULT chexGetSymbol(CAudioObjectDecoder *paudec, U32 *puVal,
                        QuantFlt *pqf, CxPredType predType)
{
    switch (predType)
    {
    case CxNoPred:
        return plusGetIndexH(paudec, puVal, pqf->m_phi);
        break;
    case CxPredF:
        return plusGetIndexH(paudec, puVal, pqf->m_phiPredF);
        break;
    case CxPredT:
        return plusGetIndexH(paudec, puVal, pqf->m_phiPredT);
        break;
    }
    assert(WMAB_FALSE);
    return WMA_E_FAIL;
}

WMARESULT chexQuantDecode(CAudioObjectDecoder *paudec,
                          ChexType *pfParam,
                          CxPredType predType, Int *piPred,
                          QuantFlt *pqf)
{
    WMARESULT wmaResult = WMA_OK;
    U32 uVal;
    Int iIndex;

    TRACEWMA_EXIT(wmaResult, chexGetSymbol(paudec, &uVal, pqf, predType));
    iIndex = (Int)uVal;

    if (predType != CxNoPred)
        *pfParam = qfInvQuantPred(pqf, iIndex, piPred);
    else
        *pfParam = qfInvQuant(pqf, iIndex, piPred);

exit:
    return wmaResult;
}

WMARESULT chexQuantDecodeRndSign(CAudioObjectDecoder *paudec,
                                 ChexType *pfParam,
                                 CxPredType predType, Int *piPred,
                                 QuantFlt *pqf)
{
    WMARESULT wmaResult = WMA_OK;
    U32 uVal;
    Int iIndex, iSign, iIndexCode, iSignCode;
    Int iBand = paudec->pau->m_pcx->m_iBand;

    TRACEWMA_EXIT(wmaResult, chexGetSymbol(paudec, &uVal, pqf, predType));
    iIndexCode = (Int)uVal;
    //printf("%d %d DEC-INDEX: %d\n", count, iBand, uVal);
    //printf("PTYPE=%d\n", predType);
    //printf("%d\n", *piPred);

    iSignCode = 1;
    if (iIndexCode != 0)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iSignCode = (uVal==1) ? 1 : -1;
        //printf("DEC-SIGN2: %d\n", iSignCode);
    }

    if (predType != CxNoPred)
    {
        iIndex = iIndexCode*iSignCode + (*piPred);
        iSign = (iIndex >= 0 ? 1 : -1);
        iIndex = ABS(iIndex);
    }
    else
    {
        iIndex = iIndexCode;
        iSign = iSignCode;
    }

    *pfParam = qfInvQuantRnd(pqf, iIndex)*iSign;
    *piPred = iIndex*iSign;

    //printf("%d\n", *piPred);

exit:
    return wmaResult;
}

WMARESULT chexQuantDecodeRndSignPhase(CAudioObjectDecoder *paudec,
                                      ChexType *pfParam,
                                      CxPredType predType, Int *piPred,
                                      QuantFlt *pqf)
{
    WMARESULT wmaResult = WMA_OK;
    U32 uVal;
    Int iIndex, iSign, iIndexCode, iSignCode, iVal0, iVal1;
    Int iBand = paudec->pau->m_pcx->m_iBand;

    assert(predType != CxNoPred);

    TRACEWMA_EXIT(wmaResult, chexGetSymbol(paudec, &uVal, pqf, predType));
    iIndexCode = (Int)uVal;
    //printf("%d %d DEC-INDEX: %d\n", count, iBand, uVal);
    //printf("PTYPE=%d\n", predType);
    //printf("%d\n", *piPred);
    
    iVal0 = ABS(*piPred) + iIndexCode;
    iVal1 = ABS(*piPred) - iIndexCode;

    if (iVal0 >= 0 && iVal0 < pqf->m_iBins &&
        iVal1 >= 0 && iVal1 < pqf->m_iBins)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iSignCode = (uVal==1) ? 1 : -1;
        //printf("DEC-SIGN: %d\n", iSignCode);
    }
    else if (iVal0 >= 0 && iVal0 < pqf->m_iBins)
    {
        iSignCode = 1;
    }
    else if (iVal1 >= 0 && iVal1 < pqf->m_iBins)
    {
        iSignCode = -1;
    }
    else
    {
        iSignCode = 1;
        assert(WMAB_FALSE);
    }

    iIndex = iIndexCode*iSignCode + ABS(*piPred);
    assert(iIndex >= 0 && iIndex < pqf->m_iBins);
    iSign = 1;
    if (iIndex != 0 && iIndex != pqf->m_iBins-1)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iSign = (uVal==1) ? 1 : -1;
        //printf("DEC-SIGN2: %d\n", iSign);
    }

    *pfParam = qfInvQuantRnd(pqf, iIndex)*iSign;
    *piPred = iIndex*iSign;

    //printf("%d\n", *piPred);

exit:
    return wmaResult;
}

#define CXQUANTDEC(type, fParam, predType, iPred) \
    chexQuantDecode(paudec, &(fParam), predType, &(iPred), &pcx->m_qf##type)

INLINE
WMARESULT chexGetIndex(CAudioObjectDecoder *paudec, Int *piSymbol,
                       Int *piIndex, Int *piSign,
                       QuantFlt *pqf, Int iPred, CxPredType predType)
{
    WMARESULT wmaResult = WMA_OK;
    Int iSign, iSymbol;
    U32 uVal;

    TRACEWMA_EXIT(wmaResult, chexGetSymbol(paudec, &uVal, pqf, predType));
    iSymbol = (Int)uVal;
    iSign = 1;
    if (0 != iSymbol)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iSign = (uVal==1) ? 1 : -1;
    }
    iSymbol = iSign*iSymbol;
    if (predType != CxNoPred)
        iSymbol += iPred;

    *piSymbol = iSymbol;
    *piSign = (iSymbol >= 0) ? 1 : -1;
    *piIndex = ABS(iSymbol);

exit:
    return wmaResult;
}

INLINE
WMARESULT chexDecodeClosePts(CAudioObjectDecoder *paudec, Int *piVal,
                             Int iMin, Int iMax)
{
    WMARESULT wmaResult = WMA_OK;
    Int iSign, iAbsVal, iNumOnes;
    Int iRange = max(ABS(iMin), ABS(iMax));
    Int iStart;
    U32 uVal;

    if (0 >= iMin && 0 <= iMax)
        iStart = 0;
    else
        iStart = min(ABS(iMin), ABS(iMax));

    iNumOnes = 0;
    while (1)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        if (uVal==1)
            iNumOnes++;
        if (uVal==0 || iNumOnes==iRange-iStart)
            break;
    }

    iAbsVal = iNumOnes + iStart;

    if (iAbsVal < iMin || iAbsVal > iMax)
        iSign = -1;
    else if (-iAbsVal < iMin || -iAbsVal > iMax || iAbsVal == 0)
        iSign = 1;
    else
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iSign = (uVal==1) ? 1 : -1;
    }

    *piVal = iAbsVal*iSign;

    assert(*piVal >= iMin && *piVal <= iMax);

exit:
    return wmaResult;
}

INLINE
WMARESULT chexGetCloseIndex(CAudioObjectDecoder *paudec, Int iMin, Int iMax,
                            Int *piSymbol, Int *piIndex, Int *piSign,
                            Int iPred, CxPredType predType)
{
    WMARESULT wmaResult = WMA_OK;
    Int iSymbol;

    if (iMin != iMax)
    {
        TRACEWMA_EXIT(wmaResult,
                      chexDecodeClosePts(paudec, &iSymbol, iMin, iMax));
    }
    else
        iSymbol = iMin;

    if (predType != CxNoPred)
        iSymbol += iPred;

    *piSymbol = iSymbol;
    *piSign = (iSymbol >= 0) ? 1 : -1;
    *piIndex = ABS(iSymbol);

exit:
    return wmaResult;
}

WMARESULT chexQuantDecodeCloseIndex(CAudioObjectDecoder *paudec,
                                    ChexType *pfParam, CxPredType predType,
                                    Int *piPrev, QuantFlt *pqf,
                                    Bool bSign)
{
    WMARESULT wmaResult = WMA_OK;
    Int iVal=0, iIndex=0, iSign=0, iMin, iMax;

    if (predType != CxNoPred)
    {
        if (bSign)
            iMin = -pqf->m_iMax - (*piPrev);
        else
            iMin = pqf->m_iMin - (*piPrev);
        iMax = pqf->m_iMax - (*piPrev);
    }
    else
    {
        if (bSign)
            iMin = -pqf->m_iMax;
        else
            iMin = pqf->m_iMin;
        iMax = pqf->m_iMax;
    }

    TRACEWMA_EXIT(wmaResult,
                  chexGetCloseIndex(paudec, iMin, iMax, &iVal, &iIndex,
                                    &iSign, *piPrev, predType));

    *piPrev = iVal;
    *pfParam = qfInvQuantRnd(pqf, iIndex)*iSign;

exit:
    return wmaResult;
}

INLINE
WMARESULT chexDecodeSamePtWrap(CAudioObjectDecoder *paudec, Int *piVal,
                               Int iMax)
{
    WMARESULT wmaResult = WMA_OK;
    U32 uVal;
    Int iSignOffset;

    PLUS_GETBITS(wmaResult, 1, &uVal);
    if (0 != uVal)
    {
        TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, 2*iMax-1, &uVal));
        *piVal = uVal/2;
        iSignOffset = uVal - (*piVal)*2;
        *piVal = (iSignOffset==0) ? (*piVal+1) : -(*piVal+1);
    }
    else
        *piVal = 0;

exit:
    return wmaResult;
}

WMARESULT chexQuantDecodeSamePtWrap(CAudioObjectDecoder *paudec,
                                    ChexType *pfParam, CxPredType predType,
                                    Int *piPrev, QuantFlt *pqf)
{
    WMARESULT wmaResult = WMA_OK;
    Int iVal;

    TRACEWMA_EXIT(wmaResult,
                  chexDecodeSamePtWrap(paudec, &iVal, pqf->m_iBins-1));

    if (predType != CxNoPred)
    {
        iVal += *piPrev;
    }
    iVal = qfWrapParam(pqf, iVal);

    *piPrev = iVal;
    *pfParam = qfInvQuantRnd(pqf, iVal);

exit:
    return wmaResult;
}

WMARESULT chexDecodeBandLMRM(CAudioObjectDecoder *paudec,
                             CxAnchorReconTileInfo *pcxarti,
                             Int iCh0, Int iCh1)
{
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = paudec->pau->m_pcx;
    ChexType lmScale, rmScale;
    const Int iBand = pcx->m_iBand;
    Int iPrev;

#ifdef JOINT_CODE_LMRM
    Int iPrevRM;

    iPrev = (pcxarti->m_predTypeLMScale==CxPredT ?
             pcx->m_rgiPrevLMScale[iBand] : pcx->m_iPrevLMScale);
    iPrevRM = (pcxarti->m_predTypeRMScale==CxPredT ?
               pcx->m_rgiPrevRMScale[iBand] : pcx->m_iPrevRMScale);
    TRACEWMA_EXIT(wmaResult,
                  chexQuantDecodeLMRM(paudec, pcxarti, &lmScale, &rmScale,
                                      pcxarti->m_predTypeLMScale,
                                      pcxarti->m_predTypeRMScale,
                                      &iPrev, &iPrevRM,
                                      &pcx->m_qfScale));
    pcx->m_iPrevLMScale = iPrev;
    pcx->m_rgiPrevLMScale[iBand] = iPrev;
    pcx->m_iPrevRMScale = iPrevRM;
    pcx->m_rgiPrevRMScale[iBand] = iPrevRM;
#else
    // LM Scale
    iPrev = (pcxarti->m_predTypeLMScale==CxPredT ?
             pcx->m_rgiPrevLMScale[iBand] : pcx->m_iPrevLMScale);
    TRACEWMA_EXIT(wmaResult,
                  chexQuantDecodeRndSign(paudec, &lmScale,
                                         pcxarti->m_predTypeLMScale,
                                         &iPrev, &pcx->m_qfScale));
    pcx->m_iPrevLMScale = iPrev;
    pcx->m_rgiPrevLMScale[iBand] = iPrev;
    // RM Scale
    iPrev = (pcxarti->m_predTypeRMScale==CxPredT ?
             pcx->m_rgiPrevRMScale[iBand] : pcx->m_iPrevRMScale);
    TRACEWMA_EXIT(wmaResult,
                  chexQuantDecodeRndSign(paudec, &rmScale,
                                         pcxarti->m_predTypeRMScale,
                                         &iPrev, &pcx->m_qfScale));
    pcx->m_iPrevRMScale = iPrev;
    pcx->m_rgiPrevRMScale[iBand] = iPrev;
#endif

    lmScale = qstCalcQuantStepInterp( lmScale );
    rmScale = qstCalcQuantStepInterp( rmScale );

    lmScale = checkRange( lmScale, CX_MINM4, CX_MAXM4 );
    rmScale = checkRange( rmScale, CX_MINM4, CX_MAXM4 );

    // if lmScale+rmScale==2, no need to code sign

    if (!pcx->m_bNoPhase)
    {
        iPrev = (pcxarti->m_predTypeLRAng==CxPredT ?
                 pcx->m_rgiPrevLRAng[iBand] : pcx->m_iPrevLRAng);

        TRACEWMA_EXIT(wmaResult,
                      chexQuantDecodeCloseIndex(paudec, 
                                                &pcxarti->m_lrScAng[iBand],
                                                pcxarti->m_predTypeLRAng,
                                                &iPrev, &pcx->m_qfLRAng,
                                                WMAB_TRUE));
    }
    else
    {
        iPrev = 0;
        pcxarti->m_lrScAng[iBand] = 0;
    }
    pcx->m_rgiPrevLRAng[iBand] = iPrev;
    pcx->m_iPrevLRAng = iPrev;

    pcxarti->m_lmSc[iBand] = lmScale;
    pcxarti->m_rmSc[iBand] = rmScale;

exit:
    return wmaResult;
}

#define CHEX_QUANT_SCALE_LUT

#if defined( CHEX_QUANT_SCALE_LUT )

const ChexType g_chexScaleLUT_33[] =
{
    // x = pow( 10, i*5.0f/33 ) for i in [-17:+17]. why 17? because then x < 512 prevents overflow.

 CX_FROM_FLOAT( 2.656088e-003f ), CX_FROM_FLOAT( 3.764936e-003f ), CX_FROM_FLOAT( 5.336699e-003f ), CX_FROM_FLOAT( 7.564633e-003f ),
 CX_FROM_FLOAT( 1.072267e-002f ), CX_FROM_FLOAT( 1.519911e-002f ), CX_FROM_FLOAT( 2.154435e-002f ), CX_FROM_FLOAT( 3.053856e-002f ),
 CX_FROM_FLOAT( 4.328761e-002f ), CX_FROM_FLOAT( 6.135907e-002f ), CX_FROM_FLOAT( 8.697490e-002f ), CX_FROM_FLOAT( 1.232847e-001f ),
 CX_FROM_FLOAT( 1.747528e-001f ), CX_FROM_FLOAT( 2.477076e-001f ), CX_FROM_FLOAT( 3.511192e-001f ), CX_FROM_FLOAT( 4.977024e-001f ),
 CX_FROM_FLOAT( 7.054802e-001f ),

 CX_FROM_FLOAT( 1.000000e+000f ),

 CX_FROM_FLOAT( 1.417474e+000f ), CX_FROM_FLOAT( 2.009233e+000f ), CX_FROM_FLOAT( 2.848036e+000f ), CX_FROM_FLOAT( 4.037017e+000f ),
 CX_FROM_FLOAT( 5.722368e+000f ), CX_FROM_FLOAT( 8.111308e+000f ), CX_FROM_FLOAT( 1.149757e+001f ), CX_FROM_FLOAT( 1.629751e+001f ),
 CX_FROM_FLOAT( 2.310130e+001f ), CX_FROM_FLOAT( 3.274549e+001f ), CX_FROM_FLOAT( 4.641589e+001f ), CX_FROM_FLOAT( 6.579332e+001f ),
 CX_FROM_FLOAT( 9.326033e+001f ), CX_FROM_FLOAT( 1.321941e+002f ), CX_FROM_FLOAT( 1.873817e+002f ), CX_FROM_FLOAT( 2.656088e+002f ),
 CX_FROM_FLOAT( 3.764936e+002f ),
};

const ChexType g_chexScaleLUT_200[] =
{
    // x = pow(10,i*5./200) for i in [-108:+108]. why 108? because then x < 512 prevents overflow.

 CX_FROM_FLOAT( 1.995262e-003f ), CX_FROM_FLOAT( 2.113489e-003f ), CX_FROM_FLOAT( 2.238721e-003f ), CX_FROM_FLOAT( 2.371374e-003f ),
 CX_FROM_FLOAT( 2.511886e-003f ), CX_FROM_FLOAT( 2.660725e-003f ), CX_FROM_FLOAT( 2.818383e-003f ), CX_FROM_FLOAT( 2.985383e-003f ),
 CX_FROM_FLOAT( 3.162278e-003f ), CX_FROM_FLOAT( 3.349654e-003f ), CX_FROM_FLOAT( 3.548134e-003f ), CX_FROM_FLOAT( 3.758374e-003f ),
 CX_FROM_FLOAT( 3.981072e-003f ), CX_FROM_FLOAT( 4.216965e-003f ), CX_FROM_FLOAT( 4.466836e-003f ), CX_FROM_FLOAT( 4.731513e-003f ),
 CX_FROM_FLOAT( 5.011872e-003f ), CX_FROM_FLOAT( 5.308844e-003f ), CX_FROM_FLOAT( 5.623413e-003f ), CX_FROM_FLOAT( 5.956621e-003f ),
 CX_FROM_FLOAT( 6.309573e-003f ), CX_FROM_FLOAT( 6.683439e-003f ), CX_FROM_FLOAT( 7.079458e-003f ), CX_FROM_FLOAT( 7.498942e-003f ),
 CX_FROM_FLOAT( 7.943282e-003f ), CX_FROM_FLOAT( 8.413951e-003f ), CX_FROM_FLOAT( 8.912509e-003f ), CX_FROM_FLOAT( 9.440609e-003f ),
 CX_FROM_FLOAT( 1.000000e-002f ), CX_FROM_FLOAT( 1.059254e-002f ), CX_FROM_FLOAT( 1.122018e-002f ), CX_FROM_FLOAT( 1.188502e-002f ),
 CX_FROM_FLOAT( 1.258925e-002f ), CX_FROM_FLOAT( 1.333521e-002f ), CX_FROM_FLOAT( 1.412538e-002f ), CX_FROM_FLOAT( 1.496236e-002f ),
 CX_FROM_FLOAT( 1.584893e-002f ), CX_FROM_FLOAT( 1.678804e-002f ), CX_FROM_FLOAT( 1.778279e-002f ), CX_FROM_FLOAT( 1.883649e-002f ),
 CX_FROM_FLOAT( 1.995262e-002f ), CX_FROM_FLOAT( 2.113489e-002f ), CX_FROM_FLOAT( 2.238721e-002f ), CX_FROM_FLOAT( 2.371374e-002f ),
 CX_FROM_FLOAT( 2.511886e-002f ), CX_FROM_FLOAT( 2.660725e-002f ), CX_FROM_FLOAT( 2.818383e-002f ), CX_FROM_FLOAT( 2.985383e-002f ),
 CX_FROM_FLOAT( 3.162278e-002f ), CX_FROM_FLOAT( 3.349654e-002f ), CX_FROM_FLOAT( 3.548134e-002f ), CX_FROM_FLOAT( 3.758374e-002f ),
 CX_FROM_FLOAT( 3.981072e-002f ), CX_FROM_FLOAT( 4.216965e-002f ), CX_FROM_FLOAT( 4.466836e-002f ), CX_FROM_FLOAT( 4.731513e-002f ),
 CX_FROM_FLOAT( 5.011872e-002f ), CX_FROM_FLOAT( 5.308844e-002f ), CX_FROM_FLOAT( 5.623413e-002f ), CX_FROM_FLOAT( 5.956621e-002f ),
 CX_FROM_FLOAT( 6.309573e-002f ), CX_FROM_FLOAT( 6.683439e-002f ), CX_FROM_FLOAT( 7.079458e-002f ), CX_FROM_FLOAT( 7.498942e-002f ),
 CX_FROM_FLOAT( 7.943282e-002f ), CX_FROM_FLOAT( 8.413951e-002f ), CX_FROM_FLOAT( 8.912509e-002f ), CX_FROM_FLOAT( 9.440609e-002f ),
 CX_FROM_FLOAT( 1.000000e-001f ), CX_FROM_FLOAT( 1.059254e-001f ), CX_FROM_FLOAT( 1.122018e-001f ), CX_FROM_FLOAT( 1.188502e-001f ),
 CX_FROM_FLOAT( 1.258925e-001f ), CX_FROM_FLOAT( 1.333521e-001f ), CX_FROM_FLOAT( 1.412538e-001f ), CX_FROM_FLOAT( 1.496236e-001f ),
 CX_FROM_FLOAT( 1.584893e-001f ), CX_FROM_FLOAT( 1.678804e-001f ), CX_FROM_FLOAT( 1.778279e-001f ), CX_FROM_FLOAT( 1.883649e-001f ),
 CX_FROM_FLOAT( 1.995262e-001f ), CX_FROM_FLOAT( 2.113489e-001f ), CX_FROM_FLOAT( 2.238721e-001f ), CX_FROM_FLOAT( 2.371374e-001f ),
 CX_FROM_FLOAT( 2.511886e-001f ), CX_FROM_FLOAT( 2.660725e-001f ), CX_FROM_FLOAT( 2.818383e-001f ), CX_FROM_FLOAT( 2.985383e-001f ),
 CX_FROM_FLOAT( 3.162278e-001f ), CX_FROM_FLOAT( 3.349654e-001f ), CX_FROM_FLOAT( 3.548134e-001f ), CX_FROM_FLOAT( 3.758374e-001f ),
 CX_FROM_FLOAT( 3.981072e-001f ), CX_FROM_FLOAT( 4.216965e-001f ), CX_FROM_FLOAT( 4.466836e-001f ), CX_FROM_FLOAT( 4.731513e-001f ),
 CX_FROM_FLOAT( 5.011872e-001f ), CX_FROM_FLOAT( 5.308844e-001f ), CX_FROM_FLOAT( 5.623413e-001f ), CX_FROM_FLOAT( 5.956621e-001f ),
 CX_FROM_FLOAT( 6.309573e-001f ), CX_FROM_FLOAT( 6.683439e-001f ), CX_FROM_FLOAT( 7.079458e-001f ), CX_FROM_FLOAT( 7.498942e-001f ),
 CX_FROM_FLOAT( 7.943282e-001f ), CX_FROM_FLOAT( 8.413951e-001f ), CX_FROM_FLOAT( 8.912509e-001f ), CX_FROM_FLOAT( 9.440609e-001f ),

 CX_FROM_FLOAT( 1.000000e+000f ),

 CX_FROM_FLOAT( 1.059254e+000f ), CX_FROM_FLOAT( 1.122018e+000f ), CX_FROM_FLOAT( 1.188502e+000f ), CX_FROM_FLOAT( 1.258925e+000f ),
 CX_FROM_FLOAT( 1.333521e+000f ), CX_FROM_FLOAT( 1.412538e+000f ), CX_FROM_FLOAT( 1.496236e+000f ), CX_FROM_FLOAT( 1.584893e+000f ),
 CX_FROM_FLOAT( 1.678804e+000f ), CX_FROM_FLOAT( 1.778279e+000f ), CX_FROM_FLOAT( 1.883649e+000f ), CX_FROM_FLOAT( 1.995262e+000f ),
 CX_FROM_FLOAT( 2.113489e+000f ), CX_FROM_FLOAT( 2.238721e+000f ), CX_FROM_FLOAT( 2.371374e+000f ), CX_FROM_FLOAT( 2.511886e+000f ),
 CX_FROM_FLOAT( 2.660725e+000f ), CX_FROM_FLOAT( 2.818383e+000f ), CX_FROM_FLOAT( 2.985383e+000f ), CX_FROM_FLOAT( 3.162278e+000f ),
 CX_FROM_FLOAT( 3.349654e+000f ), CX_FROM_FLOAT( 3.548134e+000f ), CX_FROM_FLOAT( 3.758374e+000f ), CX_FROM_FLOAT( 3.981072e+000f ),
 CX_FROM_FLOAT( 4.216965e+000f ), CX_FROM_FLOAT( 4.466836e+000f ), CX_FROM_FLOAT( 4.731513e+000f ), CX_FROM_FLOAT( 5.011872e+000f ),
 CX_FROM_FLOAT( 5.308844e+000f ), CX_FROM_FLOAT( 5.623413e+000f ), CX_FROM_FLOAT( 5.956621e+000f ), CX_FROM_FLOAT( 6.309573e+000f ),
 CX_FROM_FLOAT( 6.683439e+000f ), CX_FROM_FLOAT( 7.079458e+000f ), CX_FROM_FLOAT( 7.498942e+000f ), CX_FROM_FLOAT( 7.943282e+000f ),
 CX_FROM_FLOAT( 8.413951e+000f ), CX_FROM_FLOAT( 8.912509e+000f ), CX_FROM_FLOAT( 9.440609e+000f ), CX_FROM_FLOAT( 1.000000e+001f ),
 CX_FROM_FLOAT( 1.059254e+001f ), CX_FROM_FLOAT( 1.122018e+001f ), CX_FROM_FLOAT( 1.188502e+001f ), CX_FROM_FLOAT( 1.258925e+001f ),
 CX_FROM_FLOAT( 1.333521e+001f ), CX_FROM_FLOAT( 1.412538e+001f ), CX_FROM_FLOAT( 1.496236e+001f ), CX_FROM_FLOAT( 1.584893e+001f ),
 CX_FROM_FLOAT( 1.678804e+001f ), CX_FROM_FLOAT( 1.778279e+001f ), CX_FROM_FLOAT( 1.883649e+001f ), CX_FROM_FLOAT( 1.995262e+001f ),
 CX_FROM_FLOAT( 2.113489e+001f ), CX_FROM_FLOAT( 2.238721e+001f ), CX_FROM_FLOAT( 2.371374e+001f ), CX_FROM_FLOAT( 2.511886e+001f ),
 CX_FROM_FLOAT( 2.660725e+001f ), CX_FROM_FLOAT( 2.818383e+001f ), CX_FROM_FLOAT( 2.985383e+001f ), CX_FROM_FLOAT( 3.162278e+001f ),
 CX_FROM_FLOAT( 3.349654e+001f ), CX_FROM_FLOAT( 3.548134e+001f ), CX_FROM_FLOAT( 3.758374e+001f ), CX_FROM_FLOAT( 3.981072e+001f ),
 CX_FROM_FLOAT( 4.216965e+001f ), CX_FROM_FLOAT( 4.466836e+001f ), CX_FROM_FLOAT( 4.731513e+001f ), CX_FROM_FLOAT( 5.011872e+001f ),
 CX_FROM_FLOAT( 5.308844e+001f ), CX_FROM_FLOAT( 5.623413e+001f ), CX_FROM_FLOAT( 5.956621e+001f ), CX_FROM_FLOAT( 6.309573e+001f ),
 CX_FROM_FLOAT( 6.683439e+001f ), CX_FROM_FLOAT( 7.079458e+001f ), CX_FROM_FLOAT( 7.498942e+001f ), CX_FROM_FLOAT( 7.943282e+001f ),
 CX_FROM_FLOAT( 8.413951e+001f ), CX_FROM_FLOAT( 8.912509e+001f ), CX_FROM_FLOAT( 9.440609e+001f ), CX_FROM_FLOAT( 1.000000e+002f ),
 CX_FROM_FLOAT( 1.059254e+002f ), CX_FROM_FLOAT( 1.122018e+002f ), CX_FROM_FLOAT( 1.188502e+002f ), CX_FROM_FLOAT( 1.258925e+002f ),
 CX_FROM_FLOAT( 1.333521e+002f ), CX_FROM_FLOAT( 1.412538e+002f ), CX_FROM_FLOAT( 1.496236e+002f ), CX_FROM_FLOAT( 1.584893e+002f ),
 CX_FROM_FLOAT( 1.678804e+002f ), CX_FROM_FLOAT( 1.778279e+002f ), CX_FROM_FLOAT( 1.883649e+002f ), CX_FROM_FLOAT( 1.995262e+002f ),
 CX_FROM_FLOAT( 2.113489e+002f ), CX_FROM_FLOAT( 2.238721e+002f ), CX_FROM_FLOAT( 2.371374e+002f ), CX_FROM_FLOAT( 2.511886e+002f ),
 CX_FROM_FLOAT( 2.660725e+002f ), CX_FROM_FLOAT( 2.818383e+002f ), CX_FROM_FLOAT( 2.985383e+002f ), CX_FROM_FLOAT( 3.162278e+002f ),
 CX_FROM_FLOAT( 3.349654e+002f ), CX_FROM_FLOAT( 3.548134e+002f ), CX_FROM_FLOAT( 3.758374e+002f ), CX_FROM_FLOAT( 3.981072e+002f ),
 CX_FROM_FLOAT( 4.216965e+002f ), CX_FROM_FLOAT( 4.466836e+002f ), CX_FROM_FLOAT( 4.731513e+002f ), CX_FROM_FLOAT( 5.011872e+002f ),
 
 // above i = 108, x >= 512 which causes an overflow - so table entries beyond this point are not needed.
};

#   define CX_SCALE_CHCK_QUANT( i, n ) (checkRange(i,-n,n)+n)
#   define CX_SCALE_FROM_QUANT( i, n ) g_chexScaleLUT_##n[ i ]
#else // so !CHEX_QUANT_SCALE_LUT
#   define CX_SCALE_CHCK_QUANT( i, n ) checkRange(i,-n,n)
#   define CX_SCALE_FROM_QUANT( i, n ) CX_FROM_FLOAT((Float)pow( 10.0f, (Float)i/n ))
#endif

INLINE ChexType cxScaleFromQuant( const Int iQuantStepIndex, Int iIndex )
{
    if( 0 == iQuantStepIndex )
    {
        // 0 == 'iQuantStepIndex' implies 33 bins,
        // so compute pow( 10, 'iIndex' / 33 )

        iIndex = CX_SCALE_CHCK_QUANT( iIndex, 17 );
        return   CX_SCALE_FROM_QUANT( iIndex, 33 );
    }
    else
    {
        // 1,2,3 == 'iQuantStepIndex' implies  50, 100,
        // 200 bins. in this case, scale 'iIndex' so
        // that we can just use the 200-bin LUT for all
        // 3 cases. then compute pow( 10, 'iIndex' / 200 )

        iIndex <<= 3 - iQuantStepIndex;
        iIndex = CX_SCALE_CHCK_QUANT( iIndex, 108 );
        return   CX_SCALE_FROM_QUANT( iIndex, 200 );
    }
}

WMARESULT chexDecodePowMat(CAudioObjectDecoder *paudec,
                           CxAnchorReconTileInfo *pcxarti, Int iCh0, Int iCh1)
{
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = paudec->pau->m_pcx;
    ChexType lScale;
    const Int iBand = pcx->m_iBand;
    Int iPrev, iIndex;
    
    //printf("B=%d %d\n", pcxarti->m_iStartPt, iBand);

    // Decode L scale
    iPrev = (pcxarti->m_predTypeLScale==CxPredT ?
             pcx->m_rgiPrevLScale[iBand] : pcx->m_iPrevLScale);

    TRACEWMA_EXIT( wmaResult,
        chexQuantDecodeRndSign(paudec, &lScale,
                     pcxarti->m_predTypeLScale,
                     &iPrev, &pcx->m_qfScale ));

    iIndex = iPrev;
    
    pcxarti->m_lScNorm[ iBand ] = cxScaleFromQuant( pcx->m_iQuantStepIndex, iIndex );
    pcx->m_rgiPrevLScale[iBand] = iPrev;
    pcx->m_iPrevLScale = iPrev;
    
    pcxarti->m_lScNorm[iBand] = checkRange( pcxarti->m_lScNorm[iBand], CX_MINM4, CX_MAXM4 );

    //printf("L=%f\n", pcxarti->m_lScNorm[iBand]);

    // Decode LR scale
    if (pcx->m_rgiPrevLScale[iBand] == -pcx->m_qfScale.m_iMax ||
        pcx->m_rgiPrevLScale[iBand] == pcx->m_qfScale.m_iMax)
    {
        iPrev = pcx->m_qfLRScale.m_iMax;
        pcxarti->m_lrScNorm[iBand] = CX_FROM_FLOAT(1.0f);
    }
    else
    {
        iPrev = (pcxarti->m_predTypeLRScale==CxPredT ?
                 pcx->m_rgiPrevLRScale[iBand] : pcx->m_iPrevLRScale);
        TRACEWMA_EXIT(wmaResult,
                      chexQuantDecodeCloseIndex(paudec,
                                                &pcxarti->m_lrScNorm[iBand],
                                                pcxarti->m_predTypeLRScale,
                                                &iPrev, &pcx->m_qfLRScale,
                                                WMAB_FALSE));
    }
    pcx->m_rgiPrevLRScale[iBand] = iPrev;
    pcx->m_iPrevLRScale = iPrev;
    //printf("LR=%f\n", pcxarti->m_lrScNorm[iBand]);

    // Decode LR Ang
    if (0 == pcx->m_rgiPrevLRScale[iBand] ||
        pcx->m_rgiPrevLScale[iBand] == -pcx->m_qfScale.m_iMax ||
        pcx->m_rgiPrevLScale[iBand] == pcx->m_qfScale.m_iMax ||
        pcx->m_bNoPhase)
    {
        iPrev = 0;
        pcxarti->m_lrScAng[iBand] = CX_FROM_FLOAT(0.0f);
    }
    else
    {
        iPrev = (pcxarti->m_predTypeLRAng==CxPredT ?
                 pcx->m_rgiPrevLRAng[iBand] : pcx->m_iPrevLRAng);
        TRACEWMA_EXIT(wmaResult,
                      chexQuantDecodeSamePtWrap(paudec,
                                                &pcxarti->m_lrScAng[iBand],
                                                pcxarti->m_predTypeLRAng,
                                                &iPrev, &pcx->m_qfLRAng));
    }
    pcx->m_rgiPrevLRAng[iBand] = iPrev;
    pcx->m_iPrevLRAng = iPrev;
    //printf("%d LRA=%f\n", count, pcxarti->m_lrScAng[iBand]);

exit:
    return wmaResult;
}

WMARESULT chexDecodeBand(CAudioObjectDecoder *paudec,
                         CxAnchorReconTileInfo *pcxarti, Int iCh0, Int iCh1)
{
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = paudec->pau->m_pcx;
    const Int iBand = pcx->m_iBand;
    U32 uVal;

    if (ChexChCodingPerBand == pcxarti->m_eCxChCoding)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcxarti->m_iCodeMono[iBand] = (Int)uVal;
    }
    else
    {
        assert(pcxarti->m_eCxChCoding == ChexMono ||
               pcxarti->m_eCxChCoding == ChexDiff);
        pcxarti->m_iCodeMono[iBand] =
            (ChexMono == pcxarti->m_eCxChCoding) ? 1 : 0;
    }

    if (IS_SET_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIXLMRM))
    {
        TRACEWMA_EXIT(wmaResult,
                      chexDecodeBandLMRM(paudec, pcxarti, iCh0, iCh1));
    }
    else if (IS_SET_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIX))
    {
        TRACEWMA_EXIT(wmaResult,
                      chexDecodePowMat(paudec, pcxarti, iCh0, iCh1));
    }

exit:
    return wmaResult;
}

WMARESULT chexDecodeTileParamUpdate(CAudioObjectDecoder *paudec,
                                    CxAnchorReconTileInfo *pcxarti)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Chex *pcx = pcx = pau->m_pcx;
    U32 uVal;
    Bool bBandConfigSame=WMAB_TRUE, bStartBandSame=WMAB_TRUE;

    if (pcx->m_bStartBandPerTile && pcx->m_bBandConfigPerTile)
    {
        PLUS_PEEKBITS(wmaResult, 3, &uVal);
        if ((uVal & 0x4)>>2 == 0)
        {
            PLUS_FLUSHBITS(wmaResult, 1); // 0xx -- no update
        }
        else if ((uVal & 0x6)>>1 == 2)
        {
            PLUS_FLUSHBITS(wmaResult, 2); // 10x -- update start band only
            bStartBandSame = WMAB_FALSE;
        }
        else if (uVal == 6)
        {
            PLUS_FLUSHBITS(wmaResult, 3); // 100 -- update band config only
            bBandConfigSame = WMAB_FALSE;
        }
        else
        {
            PLUS_FLUSHBITS(wmaResult, 3); // 111
            bStartBandSame = WMAB_FALSE;
            bBandConfigSame = WMAB_FALSE;
        }
    }
    else if (pcx->m_bBandConfigPerTile)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        bBandConfigSame = (1==uVal) ? WMAB_FALSE : WMAB_TRUE;
    }
    else if (pcx->m_bStartBandPerTile)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        bStartBandSame = (1==uVal) ? WMAB_FALSE : WMAB_TRUE;
    }

    // decode new band config
    if (pcx->m_bBandConfigPerTile && !bBandConfigSame)
    {
        PLUS_GETBITS(wmaResult, pcx->m_iNumBandIndexBits, &uVal);
        pcxarti->m_iNumBandIndex = (Int)uVal;
        pcxarti->m_cBands = pcx->m_piCxBands[pcxarti->m_iNumBandIndex];
        if (pcxarti->m_cBands >= g_iMinCxBandsForTwoConfigs)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            pcxarti->m_iBandMultIndex = (Int)uVal;
        }
        else
        {
            pcxarti->m_iBandMultIndex = 0;
        }
    }

    // decode new start band
    if (pcx->m_bStartBandPerTile && !bStartBandSame)
    {
        TRACEWMA_EXIT(wmaResult,
                      freqexGet1ofNVals(paudec, pcxarti->m_cBands, &uVal));
        pcxarti->m_iStartBand = (Int)uVal;
    }

    pcxarti->m_iStartBand = min(pcxarti->m_iStartBand,
                                pcx->m_piCxBands[pcxarti->m_iNumBandIndex]-1);

    // udpate global band config
    if (pcx->m_bBandConfigPerTile)
    {
        pcx->m_iNumBandIndex  = pcxarti->m_iNumBandIndex;
        pcx->m_cBands         = pcxarti->m_cBands;
        pcx->m_iBandMultIndex = pcxarti->m_iBandMultIndex;
    }
    if (pcx->m_bStartBandPerTile)
        pcx->m_iStartBand     = pcxarti->m_iStartBand;

    // adjust scale
    if (ChexAutoAdjustPerTile == pcx->m_eAutoAdjustScale)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcxarti->m_eAutoAdjustScale =
            (1==uVal) ? ChexAdjustScaleExact : ChexAdjustScaleApprox;
    }

    // filter tap output
    if (ChexFilterOutputPerTile == pcx->m_eFilterTapOutput)
    {
        PLUS_GETBITS(wmaResult, 2, &uVal);
        pcxarti->m_eFilterTapOutput = (ChexFilterOutput)uVal;
    }

    // channel coding
    if (ChexChCodingPerTile == pcx->m_eCxChCoding)
    {
        TRACEWMA_EXIT(wmaResult,
                   freqexGet1ofNVals(paudec, pcx->m_iCxChCodingVals-1, &uVal));
        pcxarti->m_eCxChCoding = (ChexChCoding)uVal;
    }

exit:
    return wmaResult;
}

WMARESULT chexDecodeChexTile(CAudioObjectDecoder *paudec, ReconTileInfo *prti,
                             ReconTileInfo *prtiPrev)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    Int iBand;
    U32 uVal;
    Int iGrp, iCh0, iCh1, nChInGrp;
    CxAnchorReconTileInfo *pcxarti;
    Bool bUseNewAnchor;

#ifdef CHEXTILE_SYNCBITS_DEBUG
    PLUS_GETBITS(wmaResult, 8, *uVal);
    assert(0xFF == uVal);
#endif //CHEXTILE_SYNCBITS_DEBUG
    PLUS_GETBITS(wmaResult, 1, &uVal);
    prti->m_bParamsCoded = (Bool)uVal;

    if (WMAB_FALSE == prti->m_bParamsCoded)
    {
        chexCopyParams(pcx, prti, prtiPrev);
        goto exit;
    }

    pcx->m_bNoInterpFromPrev = WMAB_FALSE;

    if (0 != prp->m_rgcxarti[prp->m_icxarti].m_iRefCount)
    {
        // Prevent assert in the call to chexGetNewAnchor below...
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    pcxarti = chexGetNewAnchor(prp);
    bUseNewAnchor = chexSetCodeAnchor(prti, pcxarti);
    if ((prti->m_pcxartiSeg != pcxarti) && (NULL != prti->m_pcxartiSeg))
    {
        // Prevent assert in the call to chexSetSegAnchor below...
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    chexSetSegAnchor(prti, pcxarti);
    if (bUseNewAnchor)
        chexUpdateNextAnchorPos(prp);

    prti->m_iTilesInCoding = 1;

    pcxarti->m_bCxInterpolate = WMAB_TRUE;

    PLUS_GETBITS(wmaResult, 1, &uVal);
    pcxarti->m_bEvenLengthCxSegment = (Bool)uVal;

    // set to global, overwrite as needed, init tile configuration
    chexSetTileParamsFromGlobalParam(pcx, pcxarti);
    TRACEWMA_EXIT(wmaResult, chexDecodeTileParamUpdate(paudec, pcxarti));
    pcxarti->m_bCodeLMRM = pcx->m_bCodeLMRM;
    TRACEWMA_EXIT(wmaResult, chexInitTileConfig(pcx, prti, WMAB_TRUE, 0));

    cxUpdateFrameMaxStartBand(pcx, pcxarti);

    if (IS_SET_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIXLMRM))
    {
        TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, 3, &uVal));
        pcxarti->m_predTypeLMScale = 2-(CxPredType)uVal;
        TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, 3, &uVal));
        pcxarti->m_predTypeRMScale = 2-(CxPredType)uVal;
        if (!pcx->m_bNoPhase)
        {
            TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, 3, &uVal));
            pcxarti->m_predTypeLRAng = 2-(CxPredType)uVal;
        }

        if (pcx->m_bNeedIntra)
        {
            // otherwise bitstream corruption
            if (CxPredT == pcxarti->m_predTypeLMScale ||
                CxPredT == pcxarti->m_predTypeRMScale  ||
                (CxPredT == pcxarti->m_predTypeLRAng && !pcx->m_bNoPhase))
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }
    }
    else if (IS_SET_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIX))
    {
        TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, 3, &uVal));
        pcxarti->m_predTypeLScale = 2-(CxPredType)uVal;
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcxarti->m_predTypeLRScale = (uVal==1) ? CxPredF : CxPredT;
        if (!pcx->m_bNoPhase)
        {
            TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, 3, &uVal));
            pcxarti->m_predTypeLRAng = 2-(CxPredType)uVal;
        }

        if (pcx->m_bNeedIntra)
        {
            // otherwise bitstream corruption
            if (CxPredT == pcxarti->m_predTypeLScale ||
                CxPredT == pcxarti->m_predTypeLRScale  ||
                (CxPredT == pcxarti->m_predTypeLRAng && !pcx->m_bNoPhase))
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }
    }

    for (iGrp=0; iGrp < prti->m_iNChGroups; iGrp++)
    {
        nChInGrp = chexChannelsInGroup(pau, prti, iGrp, &iCh0, &iCh1);
        assert(1 == nChInGrp || 2 == nChInGrp);

        if (1 == nChInGrp)
            continue;

        pcx->m_cStartIndex = 0;
        pcx->m_iPrevLRScale = pcx->m_qfLRScale.m_iMax;
        pcx->m_iPrevLScale = 0;
        pcx->m_iPrevLRAng = 0;
        pcx->m_iPrevLRReal = 0;
        pcx->m_iPrevLRImag = 0;
        pcx->m_iPrevLMScale = 0;
        pcx->m_iPrevRMScale = 0;
        // cx params sent for all bands, even if not used
        for (iBand=0; iBand < pcxarti->m_cBands; iBand++)
        {
            pcx->m_iBand = iBand;
            TRACEWMA_EXIT(wmaResult,
                          chexDecodeBand(paudec, pcxarti, iCh0, iCh1));
            pcx->m_cStartIndex += (Int)pcx->m_rgiBandSizes[iBand];
        }
        assert(pcx->m_cStartIndex == pcx->m_cEnd);
    }

    //chexDumpCodedParams(pau, prti, NULL);

    // copy segment specific parameters for all tiles in this segment
    TRACEWMA_EXIT(wmaResult, chexSetTileSegmentParameters(pau, prti));

    pcx->m_bNeedIntra = WMAB_FALSE;

exit:
    return wmaResult;
}

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
Void prvReplaceSamplesFromMonoBuf(CAudioObject *pau, ReconTileInfo *prti,
                                  Int iCh, CoefType *pBuf)
{
}
#endif

WMARESULT chexDecodeTile(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Chex *pcx = pau->m_pcx;
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti, *prtiPrev;
    Int iTile, iBufSubframePos, iBufPrevPos;

    if (1 == pau->m_cChannel)
        goto exit;

    pcx->m_rgiMaxStartBandForFrame[pcx->m_iMaxStartBandIndex] = 0;

    iBufSubframePos = prp->m_iBufCodePos;
    iBufPrevPos = chexOffsetBuf(prp, prp->m_iBufCodePos, -1);
    for (iTile=0; iTile < prp->m_iTilesInSubframeCode; iTile++)
    {
        prti = prp->m_rgchextiBuf + iBufSubframePos;
        prtiPrev = prp->m_rgchextiBuf + iBufPrevPos;
        TRACEWMA_EXIT(wmaResult, chexDecodeChexTile(paudec, prti, prtiPrev));
        iBufPrevPos = iBufSubframePos;
        iBufSubframePos = chexOffsetBuf(prp, iBufSubframePos, 1);
        chexSetInfoStatCode(&prti->m_uInfoStat);
    }

    cxUpdateMaxStartBandIndex(pcx);

exit:
    return wmaResult;
}

// =========================================================

WMARESULT chexEndDecodeData(CAudioObjectDecoder *paudec, U16 *pcSampleReady)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int cSamples;

    if (audecStateGetPCM == paudec->m_externalState)
    {
        assert(*pcSampleReady >= 0);
        TRACEWMA_EXIT(wmaResult,
                    chexAuGetPCM(pau, paudec->m_fSPDIFStyleGetPCM, &cSamples));
        assert(cSamples == *pcSampleReady);
        *pcSampleReady = (U16)chexGetSamplesReady(pau);
        if (*pcSampleReady > 0)
        {
            paudec->m_externalState = audecStateGetPCM;
            //audecLog((paudec, "...%d PS samples ready", paudec->m_cSamplesReady));
        }
        else
        {
            paudec->m_externalState = audecStateDecode;
            //audecLog((paudec, "...PS state back to decode"));
        }
    }

exit:
    return wmaResult;
}

// =======================================================================

WMARESULT chexClearFexParamsBasic(Fex *pfx, ReconTileInfo *prti)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject    *pau = pfx->m_pau;
    PerChannelRecon *ppcr;
    Int iCh, iBand = 0;
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;

    prfxrti->m_cFexScaleBands = 0;
    prfxrti->m_cFexMvBands = 0;
    prfxrti->m_cFexBaseBands = 0;
    prfxrti->m_cFexStart = 0;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        if (!(prti->m_uChannelMask & (1<<iCh)))
            continue;

        if (!pau->m_rgpcinfo[iCh].m_bFex)
            continue;

        if (pau->m_bCx && iCh != 0 && pau->m_rgpcinfo[iCh].m_bFex)
        {
            // Only the 1st channel should have Fex enabled
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        
        ppcr = prfxrti->m_rgpcr + iCh;
        ppcr->m_iFexScaleFacPred = FexScaleFacNo;
#if defined(BUILD_WMAPROLBRV2)
        ppcr->m_rgiFexLogScaleFacIndex = NULL;
#endif
    }
exit:
    return wmaResult;
}

WMARESULT chexDecodeHeaderReconFex(CAudioObjectDecoder *paudec)
{
    CAudioObject    *pau = paudec->pau;    
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &pau->m_fex;
    ReconTileInfo   *prti;
    Bool            fAll, fSwitchOnce, fRFx, fOn;
    Int             i, iStart, iEnd, iBufPos;
    U32             uVal;
    WMARESULT       wmaResult = WMA_OK;

    fAll = fOn = fSwitchOnce = fRFx = WMAB_FALSE;
    iStart = 0;
    iEnd = prp->m_iTilesInSubframeCodeFx;

    pfx->m_bRFxTilesProc = WMAB_FALSE;

    if (!pau->m_bTileReconFex)
    {
        fAll = WMAB_TRUE; // no recon fex
        pau->m_bAlignFexBoundary = WMAB_FALSE;
    }
    else
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        if (uVal == 0)
        {
            pau->m_bAlignFexBoundary = WMAB_TRUE;
        }
        else
        {
            pau->m_bAlignFexBoundary = WMAB_FALSE;
            if (!pau->m_bRFxIsLast)
            {
                PLUS_GETBITS(wmaResult, 2, &uVal);
                if (uVal == 0)
                {
                    fAll = WMAB_TRUE; // no recon fex
                }
                else if (uVal == 1)
                {
                    fAll = WMAB_TRUE; // all recon fex
                    fOn = WMAB_TRUE;
                    iEnd = 0;
                }
                else if (uVal == 2)
                {
                    fSwitchOnce = WMAB_TRUE; // switch once
                }
            }
            else
            {
                PLUS_GETBITS(wmaResult, 1, &uVal);
                if (uVal == 0)
                {
                    fAll = WMAB_TRUE; // all recon fex
                    fOn = WMAB_TRUE;
                    iEnd = 0;
                }
                else
                {
                    PLUS_GETBITS(wmaResult, 1, &uVal);
                    if (uVal == 0)
                        fSwitchOnce = WMAB_TRUE; // switch once
                }
            }
        }
    }

    if (pau->m_bAlignFexBoundary || (fAll && fOn) || fSwitchOnce)
        pfx->m_bRFxTilesProc = WMAB_TRUE;

    if (pau->m_bAlignFexBoundary == WMAB_TRUE)
    {
        // count # of recon fex tiles
        prp->m_iTilesInSubframeProcFx = 0;
        iBufPos = prp->m_iBufCodeFxPos;
        for (i = 0; i < prp->m_iTilesInSubframeCodeFx; i++)
        {
            prti = prp->m_rgchextiBuf + iBufPos;
            if (prti->m_bCodingFex)
                chexSetInfoStatNoFx(&prti->m_uInfoStat);
            else
                prp->m_iTilesInSubframeProcFx++;
            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        }
        goto exit;
    }

    if (fSwitchOnce)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        fRFx = (uVal == 0) ? WMAB_FALSE : WMAB_TRUE;
        PLUS_GETBITS(wmaResult, (UInt)CEILLOG2(prp->m_iNTilesPerFrameBasic), &uVal);
        uVal = uVal + 1;

        if (fRFx)
            iStart = uVal;
        else
            iEnd = uVal;
    }

    if (fAll || fSwitchOnce)
    {
        // set no fex
        iBufPos = chexOffsetBuf(prp, prp->m_iBufCodeFxPos, iStart);
        if (!pau->m_bFirstPlusFrameAfterSuperframe)
        {
            for (i = iStart; i < iEnd; i++)
            {
                prti = prp->m_rgchextiBuf + iBufPos;
                chexSetInfoStatNoFx(&prti->m_uInfoStat);
                iBufPos = chexOffsetBuf(prp, iBufPos, 1);
            }
        }
        prp->m_iTilesInSubframeProcFx = iStart + (prp->m_iTilesInSubframeCodeFx - iEnd);
    }
    else
    {
        // individual decoding
        prp->m_iTilesInSubframeProcFx = 0;
        if (pau->m_bFirstPlusFrameAfterSuperframe &&
            pau->m_bFirstFrameAfterReset)
        {
            pau->m_bSkipPlusDueToRFx = WMAB_TRUE; // stays true until next sf
            goto exit;
        }
        iBufPos = prp->m_iBufCodeFxPos;
        for (i = 0; i < prp->m_iTilesInSubframeCodeFx; i++)
        {
            prti = prp->m_rgchextiBuf + iBufPos;
            PLUS_GETBITS(wmaResult, 1, &uVal);
            if (uVal == 0)
                chexSetInfoStatNoFx(&prti->m_uInfoStat);
            else
                prp->m_iTilesInSubframeProcFx++;
            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        }
        pfx->m_bRFxTilesProc = WMAB_TRUE;
    }

exit:
    pau->m_bTileReconBs = WMAB_FALSE;
    prp->m_iTilesInSubframeProcBs = 0;

    return wmaResult;
}

#ifdef BUILD_WMAPROLBRV3
WMARESULT chexDecodeHeaderReconFexV3(CAudioObjectDecoder *paudec)
{
    CAudioObject    *pau = paudec->pau;    
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &pau->m_fex;
    ReconTileInfo   *prti;
    Bool            fAll, fSwitchOnce, fRFx, fOn;
    Int             i, iStart, iEnd, iBufPos, cNumTilesCoded;
    U32             uVal;
    WMARESULT       wmaResult = WMA_OK;

    fAll = fOn = fSwitchOnce = fRFx = WMAB_FALSE;
    iStart = cNumTilesCoded = 0;
    iEnd = prp->m_iTilesInSubframeCodeFx;

    pfx->m_bRFxTilesProc = WMAB_FALSE;

    if (pau->m_bTileReconFex && !pau->m_bRFxIsLast)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pau->m_bTileReconFex = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }

    if (!pau->m_bTileReconFex)
    {
        fAll = WMAB_TRUE; // no recon fex
        pau->m_bAlignFexBoundary = WMAB_FALSE;
    }
    else
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        if (uVal == 0)
        {
            pau->m_bAlignFexBoundary = WMAB_TRUE;
        }
        else
        {
            pau->m_bAlignFexBoundary = WMAB_FALSE;
            PLUS_GETBITS(wmaResult, 2, &uVal);
            if (uVal == 0)
            {
                fAll = WMAB_TRUE; // no recon fex
            }
            else if (uVal == 1)
            {
                fAll = WMAB_TRUE; // all recon fex
                fOn = WMAB_TRUE;
                iEnd = 0;
            }
            else if (uVal == 2)
            {
                fSwitchOnce = WMAB_TRUE; // switch once
            }
        }
    }

    if (pau->m_bAlignFexBoundary || (fAll && fOn) || fSwitchOnce)
        pfx->m_bRFxTilesProc = WMAB_TRUE;

    if (pau->m_bAlignFexBoundary == WMAB_TRUE)
    {
        // count # of recon fex tiles
        prp->m_iTilesInSubframeProcFx = 0;
        iBufPos = prp->m_iBufCodeFxPos;
        for (i = 0; i < prp->m_iTilesInSubframeCodeFx; i++)
        {
            prti = prp->m_rgchextiBuf + iBufPos;
            if (prti->m_bCodingFex)
                chexSetInfoStatNoFx(&prti->m_uInfoStat);
            else
                prp->m_iTilesInSubframeProcFx++;
            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        }
        goto base_scaling;
    }

    if (fSwitchOnce)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        fRFx = (uVal == 0) ? WMAB_FALSE : WMAB_TRUE;
        PLUS_GETBITS(wmaResult, (UInt)CEILLOG2(prp->m_iNTilesPerFrameBasic), &uVal);
        uVal = uVal + 1;

        if (fRFx)
            iStart = uVal;
        else
            iEnd = uVal;
    }

    if (fAll || fSwitchOnce)
    {
        // set no fex
        iBufPos = chexOffsetBuf(prp, prp->m_iBufCodeFxPos, iStart);
        if (!pau->m_bFirstPlusFrameAfterSuperframe)
        {
            for (i = iStart; i < iEnd; i++)
            {
                prti = prp->m_rgchextiBuf + iBufPos;
                chexSetInfoStatNoFx(&prti->m_uInfoStat);
                iBufPos = chexOffsetBuf(prp, iBufPos, 1);
            }
        }
        prp->m_iTilesInSubframeProcFx = iStart + (prp->m_iTilesInSubframeCodeFx - iEnd);
    }
    else
    {
        // individual decoding
        prp->m_iTilesInSubframeProcFx = 0;
        iEnd = prp->m_iTilesInSubframeCodeFx;
        if (pau->m_bPlusSuperframe)
        {
            // get # of tiles to know how many bits should be decoded,
            // which avoid skipping plus decoding until next superframe (v2 syntax skips in this case)
            PLUS_GETBITS(wmaResult, (UInt)CEILLOG2(prp->m_iMaxTilesPerFrame), &uVal);
            cNumTilesCoded = (Int)uVal + 1;

            // in no reset, cNumTilesCoded should match with prp->m_iTilesInSubframeCodeFx
            if (!(pau->m_bFirstPlusFrameAfterSuperframe && pau->m_bFirstFrameAfterReset) &&
                cNumTilesCoded != prp->m_iTilesInSubframeCodeFx)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
            iEnd = cNumTilesCoded;
        }
        iBufPos = prp->m_iBufCodeFxPos;
        for (i = 0; i < iEnd; i++)
        {
            prti = prp->m_rgchextiBuf + iBufPos;
            PLUS_GETBITS(wmaResult, 1, &uVal);
            if (uVal == 0)
                chexSetInfoStatNoFx(&prti->m_uInfoStat);
            else
                prp->m_iTilesInSubframeProcFx++;
            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        }
        pfx->m_bRFxTilesProc = WMAB_TRUE;
    }

base_scaling:
    pau->m_bTileReconBs = WMAB_FALSE;
    prp->m_iTilesInSubframeProcBs = 0;
    iBufPos = prp->m_iBufCodeFxPos;
    for (i = 0; i < prp->m_iTilesInSubframeCodeFx; i++)
    {
        prti = prp->m_rgchextiBuf + iBufPos;
        chexUnsetInfoStatCodeBs(&prti->m_uInfoStat);
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }
    if (pau->m_fex.m_iVersion > 2 && pau->m_bTileReconFex)
    {
        // decode base scaling flag
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pau->m_bTileReconBs = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

        if (pau->m_bTileReconBs)
        {
            PLUS_GETBITS(wmaResult, 2, &uVal);
            iBufPos = prp->m_iBufCodeFxPos;
            if (uVal == 0)
            {
                // make all tiles base-scaling
                for (i = 0; i < prp->m_iTilesInSubframeCodeFx; i++)
                {
                    prti = prp->m_rgchextiBuf + iBufPos;
                    chexSetInfoStatCodeBs(&prti->m_uInfoStat);
                    prp->m_iTilesInSubframeProcBs++;
                    iBufPos = chexOffsetBuf(prp, iBufPos, 1);
                }
            }
            else if (uVal == 1)
            {
                // make base-scaling aligned with rfx
                for (i = 0; i < prp->m_iTilesInSubframeCodeFx; i++)
                {
                    prti = prp->m_rgchextiBuf + iBufPos;
                    if (!chexInfoStatNoFx(prti->m_uInfoStat))
                    {
                        chexSetInfoStatCodeBs(&prti->m_uInfoStat);
                        prp->m_iTilesInSubframeProcBs++;
                    }
                    iBufPos = chexOffsetBuf(prp, iBufPos, 1);
                }
            }
            else if (uVal == 2)
            {
                // switch once
                PLUS_GETBITS(wmaResult, 1, &uVal);
                fRFx = (uVal == 0) ? WMAB_FALSE : WMAB_TRUE;
                PLUS_GETBITS(wmaResult, (UInt)CEILLOG2(prp->m_iNTilesPerFrameBasic), &uVal);
                uVal = uVal + 1;
                for (i = 0; i < (Int)uVal; i++)
                {
                    prti = prp->m_rgchextiBuf + iBufPos;
                    if (fRFx)
                    {
                        chexSetInfoStatCodeBs(&prti->m_uInfoStat);
                        prp->m_iTilesInSubframeProcBs++;
                    }
                    iBufPos = chexOffsetBuf(prp, iBufPos, 1);
                }
                fRFx = !fRFx;
                for (; i < prp->m_iTilesInSubframeCodeFx; i++)
                {
                    prti = prp->m_rgchextiBuf + iBufPos;
                    if (fRFx)
                    {
                        chexSetInfoStatCodeBs(&prti->m_uInfoStat);
                        prp->m_iTilesInSubframeProcBs++;
                    }
                    iBufPos = chexOffsetBuf(prp, iBufPos, 1);
                }
            }
            else
            {
                iEnd = prp->m_iTilesInSubframeCodeFx;
                if (pau->m_bPlusSuperframe && cNumTilesCoded == 0)
                {
                    // get # of tiles to know how many bits should be decoded,
                    // which avoid skipping plus decoding until next superframe (v2 syntax skips in this case)
                    PLUS_GETBITS(wmaResult, (UInt)CEILLOG2(prp->m_iMaxTilesPerFrame), &uVal);
                    cNumTilesCoded = (Int)uVal + 1;
                    // in no reset, cNumTilesCoded should match with prp->m_iTilesInSubframeCodeFx
                    if (!(pau->m_bFirstPlusFrameAfterSuperframe && pau->m_bFirstFrameAfterReset) &&
                        cNumTilesCoded != prp->m_iTilesInSubframeCodeFx)
                    {
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    }
                    iEnd = cNumTilesCoded;
                }
                // individual
                for (i = 0; i < iEnd; i++)
                {
                    prti = prp->m_rgchextiBuf + iBufPos;
                    PLUS_GETBITS(wmaResult, 1, &uVal);
                    if (uVal == 1)
                    {
                        chexSetInfoStatCodeBs(&prti->m_uInfoStat);
                        prp->m_iTilesInSubframeProcBs++;
                    }
                    iBufPos = chexOffsetBuf(prp, iBufPos, 1);
                }
            }
        }
    }
exit:
    return wmaResult;
}
#endif

WMARESULT chexDecodeReconFexTile(CAudioObject *pau, ReconTileInfo *prti,
                                 Int iChCode)
{
    CAudioObjectDecoder *paudec = (CAudioObjectDecoder*)pau->m_hParent;
    PerChannelInfo  *ppcinfo;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    Int             iCh, iChSrc, iCurrTileSave;
    WMARESULT       wmaResult = WMA_OK;

    if (0 != iChCode)
        goto exit;

    pfx->m_prtiCurr = prti;
  
    if (!chexInfoStatNoFx(prti->m_uInfoStat) ||
        chexInfoStatCodeBs(prti->m_uInfoStat))
    {
        iCurrTileSave = pau->m_iCurrTile;
        pau->m_iCurrTile = prp->m_iDecodeRFxTileInFrame;

        // set decoding params
        for (iCh=0; iCh < pau->m_cChInTile; iCh++)
        {
            iChSrc = pau->m_rgiChInTile[iCh];
            ppcinfo = pau->m_rgpcinfo + iCh;

            // save original
            ppcinfo->m_cSubFrameSampleHalfSave = ppcinfo->m_cSubFrameSampleHalf;
            ppcinfo->m_iPowerSave = ppcinfo->m_iPower;

            ppcinfo->m_cSubFrameSampleHalf = (I16)prti->m_iSizeCurr;
            ppcinfo->m_cLastCodedIndex = 0;
            pau->m_cLastCodedIndex = 0;
            pfx->m_cStart = 0;
            ppcinfo->m_iPower = 1;
        }

        // call fex decoder
        TRACEWMA_EXIT(wmaResult, freqexDecodeTile(paudec));
        pfx->m_bFirstTileV2Recon = WMAB_FALSE;

        for (iCh=0; iCh < pau->m_cChInTile; iCh++)
        {
            iChSrc = pau->m_rgiChInTile[iCh];
            ppcinfo = pau->m_rgpcinfo + iCh;

            // retrieve params
            ppcinfo->m_cSubFrameSampleHalf = ppcinfo->m_cSubFrameSampleHalfSave;
            ppcinfo->m_iPower = ppcinfo->m_iPowerSave;
        }
        pau->m_iCurrTile = iCurrTileSave;
    }
    else
    {
        TRACEWMA_EXIT(wmaResult, chexClearFexParamsBasic(pfx, prti));
    }

exit:
    return wmaResult;
}

WMARESULT chexDecodeReconFex(CAudioObjectDecoder *paudec)
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    ReconTileInfo   *prti;
    Int             i, iBufPos;
    WMARESULT       wmaResult = WMA_OK;

    if (WMAB_FALSE == pau->m_bReconFex)
        goto exit;

    if (pfx->m_iVersion == 2)
    {
        TRACEWMA_EXIT(wmaResult, chexDecodeHeaderReconFex(paudec));

        if (WMAB_FALSE == pau->m_bSkipPlusDueToRFx &&
            (prp->m_iTilesInSubframeProcFx > 0 ||
            (pau->m_bFirstPlusFrameAfterSuperframe && pfx->m_bRFxTilesProc)))
        {
            TRACEWMA_EXIT(wmaResult,
                freqexDecodeReconTileConfigV2(paudec));
        }
    }
#ifdef BUILD_WMAPROLBRV3
    else if (pfx->m_iVersion > 2)
    {
        TRACEWMA_EXIT(wmaResult, chexDecodeHeaderReconFexV3(paudec));
        // pau->m_bSkipPlusDueToRFx and pfx->m_bRFxTilesProc are always true
        if (prp->m_iTilesInSubframeProcFx > 0 || pau->m_bTileReconBs)
        {
            TRACEWMA_EXIT(wmaResult, freqexDecodeReconTileConfigV3(paudec));
        }
    }
#endif

    pau->m_bTileReconAnyBsOnly = WMAB_FALSE;
    iBufPos = prp->m_iBufCodeFxPos;
    for (i=0; i <  prp->m_iTilesInSubframeCodeFx; i++)
    {
        prti = prp->m_rgchextiBuf + iBufPos;

        prp->m_iDecodeRFxTileInFrame = i;

        if (chexInfoStatCodeBs(prti->m_uInfoStat) &&
            !pau->m_bFirstPlusFrameAfterSuperframe)
        {
            if (chexInfoStatNoFx(prti->m_uInfoStat))
                pau->m_bTileReconAnyBsOnly = WMAB_TRUE;
        }
        else
        {
            chexUnsetInfoStatCodeBs(&prti->m_uInfoStat);
        }

        if (!chexInfoStatNoFx(prti->m_uInfoStat) &&
            !pau->m_bFirstPlusFrameAfterSuperframe &&
            !pau->m_bSkipPlusDueToRFx)
        {
            chexSetInfoStatCodeFx(&prti->m_uInfoStat);
        }
        else
        {
            TRACEWMA_EXIT(wmaResult, chexClearFexParamsBasic(pfx, prti));
        }

        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }

#ifdef BUILD_WMAPROLBRV3
    if (pfx->m_iVersion > 2 && pau->m_bTileReconBs)
    {
        FexGlobalParam *pfxgp = &pfx->m_rgGlobalParam[FexReconGlobalParamFrame];
        Int cBands;

        // set #BaseBands
        iBufPos = prp->m_iBufCodeFxPos;
        for (i=0; i < prp->m_iTilesInSubframeCodeFx; i++)
        {
            prti = prp->m_rgchextiBuf + iBufPos;
            if (chexInfoStatCodeBs(prti->m_uInfoStat))
            {
                pfx->m_cSubFrameSampleHalf = prti->m_iSizeCurr;
                pfx->m_iMaxBaseFreq = pfxgp->m_iMaxBaseFreq;
                pfx->m_cStart = (2 * pfxgp->m_iMinFreq * pfx->m_cSubFrameSampleHalf / 
                                    pau->m_iSamplingRate);
                pfx->m_piBaseBandSizesM = freqexSetBandSizeM( pfxgp->m_bBaseBandSplitV2 );

                pfx->m_bBaseScaleOnly = WMAB_FALSE;
                pfx->m_bShrinkBaseBand = WMAB_FALSE;
                if (pau->m_bTileReconAnyBsOnly)
                {
                    if (chexInfoStatNoFx(prti->m_uInfoStat))
                        pfx->m_bBaseScaleOnly = WMAB_TRUE;
                    else
                        pfx->m_bShrinkBaseBand = WMAB_TRUE;
                }

                cBands = freqexSetBaseBandConfig(pau, pfxgp->m_cBaseBands, WMAB_FALSE);
                prti->m_prfxrti->m_cFexBaseBands = cBands;
            }

            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        }
    }
#endif
exit: 
    return wmaResult;
}

#endif // BUILD_WMAPROLBRV2

