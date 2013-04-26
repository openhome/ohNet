//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "msaudiodec.h"
#include "huffdec.h"
#include "fex.h"
#include "fexdectbls.h"
#include "wmatypes.h"

#if defined(BUILD_WMAPROLBRV1)

// ========================================================================

//#define mprintf(x) printf x
#define mprintf(x)

// ========================================================================

#ifdef BUILD_WMAPROLBRV2
#include "fexdec_lowrate.c"
#endif

#if defined(WRITE_PLUS_TO_FILE)

#include <strsafe.h>
const TCHAR *g_pCmpName;

static FILE *g_fex = NULL;
#define FEXFOPEN { \
  if (g_fex==NULL) { \
    TCHAR cmpFexName[100]; \
    HRESULT hr; \
    hr = StringCchPrintf(cmpFexName, 100, "%s.fex", g_pCmpName); \
    assert(hr == S_OK); \
    g_fex = fopen(cmpFexName, "rb"); \
  } \
}

WMARESULT plusGetMoreData(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int ret;
    Fex *pfx = &(pau->m_fex);

    if (NULL==paudec->m_pibsPlus) return WMA_E_FAIL;

    FEXFOPEN;
    ret = FREAD(pau->m_rgiPlusBsBuf, sizeof(U8), PLUS_BUFSIZE, g_fex);
    wmaResult = ibstrmAttach(paudec->m_pibsPlus, (U8*)pau->m_rgiPlusBsBuf, ret,
                         WMAB_FALSE, WMAB_FALSE, WMAB_FALSE, pau->m_iVersion);

    return wmaResult;
}

#endif // WRITE_PLUS_TO_FILE

WMARESULT plusGetIndex( const CAudioObjectDecoder *paudec,
                          const U16 *pDecTable   , UInt numBits, U32 *puVal,
                          const Int iMinSym    , const Int iMaxSym,
                          const Int cMinSymBits, const Int cMaxSymBits,
                          const Int iExtraBits )
{
    WMARESULT wmaResult = WMA_OK;
    U32 uBitCnt;
    Int cOffset;
    U32 uRes;

#ifdef FEX_WRITEINDEX
    if (g_fWriteIndex)
    {
        PLUS_GETDATA(wmaResult, ibstrmLookForBits(paudec->m_pibsPlus, numBits));
        ASSERTWMA_EXIT(wmaResult, ibstrmGetBits(paudec->m_pibsPlus, numBits,
                                                puVal));
    }
    else
#endif
    {
        cOffset = max(0, iMinSym-1);
        PLUS_GETDATA(wmaResult, huffDecGet(pDecTable, paudec->m_pibsPlus,
                                          &uBitCnt, puVal, NULL));
        ASSERTWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, uBitCnt));
        if (*puVal == 0 && cMinSymBits != 0)
        {
            PLUS_GETBITS(wmaResult, (Int)cMinSymBits, puVal);
        }
        else if (*puVal == (U32)(iMaxSym+1-cOffset) && cMaxSymBits != 0)
        {
            PLUS_GETBITS(wmaResult, (Int)cMaxSymBits, puVal);
            *puVal += (U32)iMaxSym + 1;
        }
        else
        {
            *puVal += (U32)cOffset;
        }
        
        if (iExtraBits != 0)
        {
            PLUS_GETBITS(wmaResult, (Int)iExtraBits, &uRes);
            *puVal = (*puVal << iExtraBits) | uRes;
        }
    }

exit:
    return wmaResult;
}

WMARESULT freqexGet1ofN(const CAudioObjectDecoder *paudec,
                        const Int iVals, const Int iCeilLog2Vals,
                        const Int iShortVals,
                        U32 *puVal)
{
    WMARESULT wmaResult = WMA_OK;

    PLUS_PEEKBITS(wmaResult, (UInt)iCeilLog2Vals, puVal);
    if ((*puVal>>1) < (U32)iShortVals)
    {
        *puVal >>= 1;
        PLUS_FLUSHBITS(wmaResult, (UInt)(iCeilLog2Vals-1));
    }
    else
    {
        *puVal -= (UInt)iShortVals;
        PLUS_FLUSHBITS(wmaResult, (UInt)iCeilLog2Vals);
    }

exit:
    return wmaResult;
}

WMARESULT freqexGet1ofNVals(const CAudioObjectDecoder *paudec,
                            const Int iVals, U32 *puVal)
{
    if (iVals <= 1)
    {
        assert(1 == iVals);

        *puVal = 0;

        return WMA_OK;
    }
    else
    {
        const Int iCeilLog2Vals = CEILLOG2((U32)iVals);
        const Int iShortVals = (1<<iCeilLog2Vals) - iVals;

        return freqexGet1ofN(paudec, iVals, iCeilLog2Vals, iShortVals, puVal);
    }
}

WMARESULT plusGetIndex2( const CAudioObjectDecoder *paudec,
                           const U16 *pDecTable   , UInt numBits, U32 *puVal,
                           const Int iMinSym    , const Int iMaxSym,
                           const Int iNSyms,
                           const Int iExtraBits )
{
    WMARESULT wmaResult = WMA_OK;
    U32 uBitCnt;
    Int cOffset;
    U32 uRes;

#ifdef FEX_WRITEINDEX
    if (g_fWriteIndex)
    {
        PLUS_GETDATA(wmaResult, ibstrmLookForBits(paudec->m_pibsPlus, numBits));
        ASSERTWMA_EXIT(wmaResult, ibstrmGetBits(paudec->m_pibsPlus, numBits,
                                                puVal));
    }
    else
#endif
    {
        cOffset = max(0, iMinSym-1);
        PLUS_GETDATA(wmaResult, huffDecGet(pDecTable, paudec->m_pibsPlus,
                                          &uBitCnt, puVal, NULL));
        ASSERTWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, uBitCnt));
        if (*puVal == 0 && iMinSym != 0)
        {
            ASSERTWMA_EXIT(wmaResult,
                           freqexGet1ofNVals(paudec, iMinSym, puVal));
        }
        else if (*puVal == (U32)(iMaxSym+1-cOffset) && iMaxSym != iNSyms-1)
        {
            ASSERTWMA_EXIT(wmaResult,
                           freqexGet1ofNVals(paudec, iNSyms-iMaxSym-1, puVal));
            *puVal += (U32)iMaxSym + 1;
        }
        else
        {
            *puVal += (U32)cOffset;
        }
        
        if (iExtraBits != 0)
        {
            PLUS_GETBITS(wmaResult, (Int)iExtraBits, &uRes);
            *puVal = (*puVal << iExtraBits) | uRes;
        }
    }

exit:
    return wmaResult;
}

WMARESULT plusGetIndexH(const CAudioObjectDecoder *paudec,
                          U32 *puVal, HuffInfo *phi)
{
    return plusGetIndex2(paudec, phi->m_uDecTable, (UInt)phi->m_iBits,
                           puVal, phi->m_iMinSym, phi->m_iMaxSym,
                           phi->m_iBins,
                           phi->m_iExtraBits);
}

// ========================================================================

WMARESULT freqexDecInit(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    Int iCh;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iCh;
        freqexInitPcInfo(pau, ppcinfo, iCh);
    }

    // allocated memory is freed in fex.c
    pfx->m_rgGlobalParam =
        (FexGlobalParam*)auMalloc(2*sizeof(FexGlobalParam));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgGlobalParam);
    memset(pfx->m_rgGlobalParam, 0, 2*sizeof(FexGlobalParam));

    pfx->m_rgiBandSizeMGlobalParam =
        (Int*)auCalloc(2*pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiBandSizeMGlobalParam);
    memset(pfx->m_rgiBandSizeMGlobalParam, 0, 2*pfx->m_cMaxBands*sizeof(Int));

    pfx->m_rgGlobalParam[FexCodingGlobalParamFrame].m_piBandSizeM = pfx->m_rgiBandSizeMGlobalParam;
    pfx->m_rgGlobalParam[FexReconGlobalParamFrame].m_piBandSizeM  = pfx->m_rgiBandSizeMGlobalParam + pfx->m_cMaxBands;

exit:
    return wmaResult;
}
 
Void freqexDecFree(CAudioObjectDecoder *paudec)
{
    CAudioObject *pau = paudec->pau;
    Fex *pfx = (pau ? &pau->m_fex : NULL);
    
    if (pfx)
    {
        DELETE_ARRAY(pfx->m_rgGlobalParam);
        DELETE_ARRAY(pfx->m_rgiBandSizeMGlobalParam);
    }
}

WMARESULT freqexDecodeScaleBand( const CAudioObjectDecoder *paudec,
                                 FastFloat *pfScale, I32 *piLogScaleIndex)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau=paudec->pau;
    Fex *pfx = &(pau->m_fex);
    FastFloat fScale = FFLT_ZERO;
    U32 uVal=0;

    if (pfx->m_bUseScalePred)
    {
        TRACEWMA_EXIT(wmaResult, plusGetIndex(paudec, g_fexHuffScaleDecPred,
                        (UInt)pfx->m_cScaleBitsPred, &uVal,
                        g_fexHuffScalePredMinSym, g_fexHuffScalePredMaxSym,
                        g_fexHuffScalePredMinBits, g_fexHuffScalePredMaxBits,
                        pfx->m_cScaleIndexExtraBits));
        fScale = freqexInvQuantScalePred( pfx, uVal,
                                          pfx->m_iPrevLogScaleIndex,
                                         &pfx->m_iPrevLogScaleIndex );
    }
    else
    {
        TRACEWMA_EXIT(wmaResult, plusGetIndex(paudec, g_fexHuffScaleDec,
                               (UInt)pfx->m_cScaleBits, &uVal,
                               g_fexHuffScaleMinSym, g_fexHuffScaleMaxSym,
                               g_fexHuffScaleMinBits, g_fexHuffScaleMaxBits,
                               pfx->m_cScaleIndexExtraBits));
        fScale = freqexInvQuantScale( pfx, uVal,
                                      &pfx->m_iPrevLogScaleIndex );
    }
    *piLogScaleIndex = pfx->m_iPrevLogScaleIndex;

exit:
    *pfScale = fScale;
    return wmaResult;
}

WMARESULT freqexDecodePeakToNoiseScale( const CAudioObjectDecoder *paudec,
                                        const PerChannelInfo *ppcinfo,
                                        const Int iBand,
                                       FastFloat *pfScale)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    FastFloat fScale = FFLT_ZERO;
    U32 uVal = 0;
    I32 iLogScale;

    iLogScale = ppcinfo->m_piFexLogScaleFacIndex[iBand];

    pfx->m_bUseScalePred = WMAB_TRUE;

    TRACEWMA_EXIT(wmaResult, plusGetIndex(paudec, g_fexHuffScaleDecPred,
                        (UInt)pfx->m_cScaleBitsPred, &uVal,
                        g_fexHuffScalePredMinSym, g_fexHuffScalePredMaxSym,
                        g_fexHuffScalePredMinBits, g_fexHuffScalePredMaxBits,
                        pfx->m_cScaleIndexExtraBits));
    fScale = freqexInvQuantScalePred(pfx, uVal, iLogScale, &iLogScale);

exit:
    *pfScale = fScale;
    return wmaResult;
}

WMARESULT freqexDecodeScale(CAudioObjectDecoder *paudec,
                            PerChannelInfo *ppcinfo, Int iChCode,
                            Int iBand, Int iActLen)
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(paudec->pau->m_fex);

    if (iActLen == 0)
    {
        ppcinfo->m_piFexLogScaleFacIndex[iBand] = 0;
        ppcinfo->m_pffltFexScaleFac[iBand] = FFLT_ZERO;
        //printf("Skipped Scale factor\n");
        goto exit;
    }

    if (pfx->m_bFirstScaleFacCh && pfx->m_bFirstScaleFacBand)
    {
        pfx->m_bUseScalePred = WMAB_FALSE;
    }
    else
    {
        if (pfx->m_bFirstScaleFacBand)
            pfx->m_iPrevLogScaleIndex = pfx->m_iFirstChLogScaleIndex;
        pfx->m_bUseScalePred = WMAB_TRUE;
    }
    
    TRACEWMA_EXIT(wmaResult,
        freqexDecodeScaleBand( paudec, &ppcinfo->m_pffltFexScaleFac[iBand],
                               &ppcinfo->m_piFexLogScaleFacIndex[iBand]));

    if (pfx->m_bFirstScaleFacCh && pfx->m_bFirstScaleFacBand)
        pfx->m_iFirstChLogScaleIndex = pfx->m_iPrevLogScaleIndex;
    pfx->m_bFirstScaleFacBand = WMAB_FALSE;
    pfx->m_bFirstScaleFacCh = WMAB_FALSE;

exit:
    return wmaResult;
}

WMARESULT freqexDecodeMvBand(CAudioObjectDecoder *paudec,
                             PerChannelInfo *ppcinfo,
                             Int *piMv, Int iCb, Int iBand)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau=paudec->pau;
    Fex *pfx = &(pau->m_fex);
    Int iMv=0, iMvIndex;
    U32 uVal=0;
    Int cMvBits;
    Int iLeftClose, iRightClose, iPredMv;
    Bool bUseMvPred;

    freqexSetMvConfig(pau, pfx, ppcinfo,
                      pfx->m_cBandSize, iCb, WMAB_FALSE);
    
    if (pfx->m_iMaxStartPos < pfx->m_iMinStartPos)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult)
    }
    
    cMvBits = freqexMvBits(pfx);

    bUseMvPred = freqexUseMvPred(pfx, iCb);

    if (bUseMvPred)
    {
        iPredMv = freqexGetMvPred(pfx, iCb);
        if (iPredMv > pfx->m_iMaxStartPos || iPredMv < pfx->m_iMinStartPos)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        pfx->m_iPredMvIndex = freqexQuantMv(pfx, iPredMv);

        PLUS_GETBITS(wmaResult, 1, &uVal);
        if (uVal == 0)
        {
            iMvIndex = pfx->m_iPredMvIndex;
        }
        else
        {
            freqexGetPredMvClosePts(pfx, &iLeftClose, &iRightClose);
            PLUS_GETBITS(wmaResult, (UInt)pfx->m_iPredMvCloseBits, &uVal);
            if (uVal == (U32)pfx->m_iPredMvClose)
            {
                TRACEWMA_EXIT(wmaResult, 
                              freqexGet1ofN(paudec, pfx->m_iPredMvRemVals,
                                            pfx->m_iPredMvRemValsBits,
                                            pfx->m_iPredMvRemShortVals,
                                            &uVal));
                iMvIndex = uVal;
                if (iMvIndex >= iLeftClose)
                    iMvIndex += iRightClose-iLeftClose+1;
            }
            else
            {
                iMvIndex = uVal + iLeftClose;
                if (iMvIndex >= pfx->m_iPredMvIndex)
                    iMvIndex++;
            }
        }
    }
    else
    {
        if (cMvBits != 0)
            PLUS_GETBITS(wmaResult, (UInt)cMvBits, &uVal);
        iMvIndex = uVal;
    }
    iMv = freqexInvQuantMv(pfx, iMvIndex, iCb);
    CHECK_MV(iMv);

#ifdef FEX_DBG_PRINT
    fxprintf(("CODE %d: CB=%d MVPRED=%d MIN=%d MAX=%d PREDMVINDEX=%d MV=%d MVINDEX=%d\n",
              iBand, iCb, freqexGetMvPred(pfx, iCb), pfx->m_iMinStartPos,
              pfx->m_iMaxStartPos, pfx->m_iPredMvIndex, iMv, iMvIndex));
#endif

    freqexUpdateMvPred(pfx, iCb, iMv);

exit:
    *piMv = iMv;
    return wmaResult;
} // freqexDecodeMvBand

WMARESULT freqexDecodeCb(CAudioObjectDecoder *paudec,
                         PerChannelInfo *ppcinfo,
                         PerChannelInfo *ppcinfoFirst,
                         Int iChCode, Int iBand)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    Int iCb, iCh;
    U32 uVal;
    PerChannelInfoShr *pcis = ppcinfo->m_ppcinfoShr;

    if (WMAB_TRUE==pfx->m_bUseSingleMv && 0==iChCode)
        pfx->m_pbMvCoded[iBand] = WMAB_FALSE;

    if (WMAB_FALSE==pfx->m_bNeedMvCoding)
    {
        // use random noise, set during recon
        goto exit;
    }
    else if (WMAB_TRUE==pfx->m_bUseSingleMv &&
             WMAB_TRUE==pfx->m_pbMvCoded[iBand])
    {
        iCb = ppcinfoFirst->m_piFexCb[iBand];
    }
    else
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iCb = uVal;
        // read if noise floor being used
        if (pcis->m_bFxUseNoiseFloor && iCb==0)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            if (uVal == 1)
                iCb = 2; // use low + noise modelling
        }
        if (iCb==0 || iCb==2)
        {
            if (!pfx->m_bMvResTypeCoded)
            {
                PLUS_GETBITS(wmaResult, 2, &uVal);
                for (iCh=0; iCh < pau->m_cChannel; iCh++)
                    pau->m_rgpcinfoShr[iCh].m_iFxMvResType = uVal;
                pfx->m_bMvResTypeCoded = WMAB_TRUE;
            }
        }
        if (WMAB_TRUE==pfx->m_bUseSingleMv)
        {
            // coded for first time
            ppcinfoFirst->m_piFexCb[iBand] = (I32)iCb;
        }
    }
    ppcinfo->m_piFexCb[iBand] = (I32)iCb;

exit:
    return wmaResult;
}

WMARESULT freqexDecodeMv(CAudioObjectDecoder *paudec,
                         PerChannelInfo *ppcinfo,
                         PerChannelInfo *ppcinfoFirst,
                         Int iChCode, Int iBand)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    U32 uVal;
    Int iMv=0, iMv2=0, iCb=0;
    FexType fExp = 0;
    Bool bSkip;
    Int iSign;
    PerChannelInfoShr *pcis = ppcinfo->m_ppcinfoShr;

    if (WMAB_FALSE==pfx->m_bNeedMvCoding)
    {
        // scale factor too low
        if (WMAB_TRUE==pfx->m_bUseSingleMv &&
            WMAB_TRUE==pfx->m_pbMvCoded[iBand])
            // already coded in previous channel in single mv mode
            freqexUpdateMvPred(pfx, ppcinfoFirst->m_piFexCb[iBand],
                               ppcinfoFirst->m_piFexMv[iBand]);
        else
            freqexUpdateMvPred(pfx, 4, 0);
        goto exit;
    }

    bSkip = WMAB_FALSE;

    if (WMAB_TRUE==pfx->m_bUseSingleMv &&
        WMAB_TRUE==pfx->m_pbMvCoded[iBand])
    {
        // already coded in previous channel in single mv mode
        freqexUpdateMvPred(pfx, ppcinfoFirst->m_piFexCb[iBand],
                           ppcinfoFirst->m_piFexMv[iBand]);
        freqexCopyMvState(ppcinfo, ppcinfoFirst, iBand);
        bSkip = WMAB_TRUE;
    }

    iCb = ppcinfo->m_piFexCb[iBand]; // already decoded

    if (WMAB_FALSE==pfx->m_bHasPower && iCb!=1 && !bSkip)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    if ((pfx->m_bMergeNoiseVecAdj || pfx->m_bMergeNoiseVecAll) &&
         pfx->m_bNoiseMvDecoded && iCb==1 && !bSkip &&
        (pfx->m_cMergeBandSize+pfx->m_cBandSize <= g_iFexMaxNoiseBandSize))
    {
        iMv   = pfx->m_iMergeMv;
        iMv2  = pfx->m_iMergeMv2;
        fExp  = ppcinfo->m_pFexExp  [pfx->m_iMergeBand];
        iSign = ppcinfo->m_piFexSign[pfx->m_iMergeBand];

        pfx->m_cMergeBandSize += pfx->m_cBandSize;
        pfx->m_iMergeMv       += pfx->m_cBandSize;
        pfx->m_iMergeMv2      += pfx->m_cBandSize;

        bSkip = WMAB_TRUE;
    }

    if (!bSkip)
    {
        // read exponent provided noise floor not used
        fExp = FEXT_FROM_FLOAT( 1.0f );
        if (pcis->m_bFxUseExponent && iCb!=2)
        {
            PLUS_PEEKBITS(wmaResult, 2, &uVal);
            if (((uVal & 2)>>1) == 0) // 0
            {
                fExp = FEXT_FROM_FLOAT( 0.5f );
                PLUS_FLUSHBITS(wmaResult, 1);
            }
            else if (uVal == 2) // 10
            {
                fExp = FEXT_FROM_FLOAT( 1.0f );
                PLUS_FLUSHBITS(wmaResult, 2);
            }
            else if (uVal == 3) // 11
            {
                fExp = FEXT_FROM_FLOAT( 2.0f );
                PLUS_FLUSHBITS(wmaResult, 2);
            }
        }
        // read sign if needed
        iSign = 1;
        if (pcis->m_bFxUseSign)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            iSign = (uVal == 0 ? 1 : -1);
        }
        // read motion vector
        if (!pfx->m_bUseRandomNoise || iCb==0)
            TRACEWMA_EXIT(wmaResult, freqexDecodeMvBand(paudec, ppcinfo,
                                                        &iMv, iCb, iBand));
        if (2 == iCb && !pcis->m_bFxUseRandomMv2)
        {
            TRACEWMA_EXIT(wmaResult, freqexDecodeMvBand(paudec, ppcinfo,
                                                        &iMv2, 3, iBand));
        }

        ppcinfo->m_piFexMv  [iBand] = (I32)iMv;
        ppcinfo->m_piFexMv2 [iBand] = (I32)iMv2;
        ppcinfo->m_pFexExp  [iBand] = fExp;
        ppcinfo->m_piFexSign[iBand] = (I32)iSign;
        ppcinfo->m_pbFexRev [iBand] = WMAB_FALSE;

        if (WMAB_TRUE==pfx->m_bUseSingleMv)
        {
            freqexCopyMvState(ppcinfoFirst, ppcinfo, iBand);
            pfx->m_pbMvCoded[iBand] = WMAB_TRUE; // set this to true
        }
    }

    if (2 == iCb)
    {
        // read peak to noise floor scale ratio
        TRACEWMA_EXIT(wmaResult,
                      freqexDecodePeakToNoiseScale(paudec, ppcinfo, iBand,
                                    &ppcinfo->m_pffltFexScaleFacNoise[iBand]));
    }

    if ((WMAB_TRUE==pfx->m_bMergeNoiseVecAdj && 0==iCb) ||
        (pfx->m_cMergeBandSize+pfx->m_cBandSize >
         g_iFexMaxNoiseBandSize))
        pfx->m_bNoiseMvDecoded = WMAB_FALSE;
    if ((WMAB_TRUE==pfx->m_bMergeNoiseVecAdj ||
         WMAB_TRUE==pfx->m_bMergeNoiseVecAll) && 1==iCb &&
        WMAB_FALSE==pfx->m_bNoiseMvDecoded)
    {
        pfx->m_cMergeBandSize = pfx->m_cBandSize;
        pfx->m_iMergeBand = iBand;
        pfx->m_iMergeMv = iMv+pfx->m_cBandSize;
        pfx->m_iMergeMv2 = iMv2+pfx->m_cBandSize;
        pfx->m_bNoiseMvDecoded = WMAB_TRUE;
    }

    if (!pfx->m_bUseRandomNoise && 1==iCb)
    {
        if (iMv+pfx->m_cBandSize > g_iFexNoiseLen)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
    }
    if (2==iCb && iMv2+pfx->m_cBandSize > g_iFexNoiseLen)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

#ifdef FEX_DBG_PRINT
    fxprintf(("EXP: %f SIGN: %d SCALE: %f SCALEN: %f\n",
              FLOAT_FROM_FEXT( ppcinfo->m_pFexExp[iBand] ),
              ppcinfo->m_piFexSign[iBand],
              FLOAT_FROM_FASTFLOAT( ppcinfo->m_pffltFexScaleFac[iBand] ),
              FLOAT_FROM_FASTFLOAT( ppcinfo->m_pffltFexScaleFacNoise[iBand])));

#endif

exit:
    return wmaResult;
} // freqexDecodeMv

INLINE
WMARESULT freqexDecodeMinRatioBandSizeM(const CAudioObjectDecoder *paudec,
                                        Int *piMinRatioBandSizeM)
{
    WMARESULT wmaResult = WMA_OK;
    U32 uVal;

    PLUS_PEEKBITS(wmaResult, 3, &uVal);
    if (((uVal & 0x4) >> 2) == 0)
    {
        *piMinRatioBandSizeM = 1;
        ASSERTWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, 1));
    }
    else if (((uVal & 0x6) >> 1) == 2)
    {
        *piMinRatioBandSizeM = 2;
        ASSERTWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, 2));
    }
    else
    {
        assert(uVal==6 || uVal==7);
        *piMinRatioBandSizeM = uVal-3;
        ASSERTWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, 3));
    }

exit:
    return wmaResult;
}

INLINE
WMARESULT freqexDecodeBandSizeM(const CAudioObjectDecoder *paudec,
                                const Int *piFexBandSizesM,
                                Int  iMinRatioBandSizeM,
                                Int  *piBandSizeM,
                                Int  bUseUniformBands,
                                UInt  *puiExpBandSizeMIndex,
                                Int  *piExpBandSizeM,
                                Int  *piExpBandSizeMTmp,
                                Int  *piMaxBandsTemp,
                                Int  cMaxBands,
                                const Int cBands,
                                Bool *pbArbitraryBandConfig)
{
    WMARESULT wmaResult = WMA_OK;
    Int i, iOffset, iAddtlBits, iLog2Offset;
    Int iMinOffset;
    U32 uVal;

    *pbArbitraryBandConfig = WMAB_FALSE;

    // get expected multipliers
    freqexGetExpectedMultipliers(piFexBandSizesM,
                                 iMinRatioBandSizeM,
                                 bUseUniformBands,
                                 puiExpBandSizeMIndex,
                                 piExpBandSizeM,
                                 piMaxBandsTemp);

    for (i=0; i < cBands; i++)
    {
        iMinOffset = 1-*piExpBandSizeM;
        iMinOffset = max(iMinOffset, -8);
        PLUS_GETBITS(wmaResult, 1, &uVal);
        iOffset = (uVal==0) ? 0 : 1;
        if (iOffset != 0)
        {
            PLUS_GETBITS(wmaResult, 4, &uVal); // 0 to 15
            iOffset = uVal + iMinOffset; // iMinOffset to iMinOffset+15
            if (iOffset >= 0)
                iOffset++;
        }
        if (iOffset == (16+iMinOffset))
        {
            iLog2Offset = 0;
            while (1)
            {
                PLUS_GETBITS(wmaResult, 1, &uVal);
                if (uVal == 1)
                    break;
                iLog2Offset++;
            }
            iAddtlBits = (iLog2Offset == 0 ? 1 : iLog2Offset);
            PLUS_GETBITS(wmaResult, (UInt)iAddtlBits, &uVal);
            iOffset += uVal;
            if (iLog2Offset != 0)
                iOffset += (1<<iLog2Offset);
        }
        if (iOffset != 0)
            *pbArbitraryBandConfig = WMAB_TRUE;
        piBandSizeM[i] = iOffset + *piExpBandSizeM;
        piExpBandSizeMTmp[i] = *piExpBandSizeM; // strictly for debugging, no need to save
        freqexUpdateExpectedBandSizeM(piMaxBandsTemp,
                                      piBandSizeM[i],
                                      cMaxBands,
                                      puiExpBandSizeMIndex,
                                      piExpBandSizeM);
    }

exit:
    return wmaResult;
}

WMARESULT freqexDecodeBandConfig(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    Int iConfig, iChannelsRem, iChannelsRemOrig, cBands, i, iAvailCh;
    U32 uChannelMask, uMask, uVal;
    Bool bApplyToAllRemChannels;
    PerChannelInfoShr *pcis, *pcisCh;

    iConfig = 0;
    iChannelsRem = pfx->m_iNumMvChannels;
    uChannelMask = 0;
    iAvailCh = 0;
    pfx->m_piBandSizeM = pfx->m_rgiBandSizeM;
    while (1)
    {
        if (iConfig >= pfx->m_iAllocCh)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        pcis = freqexGetNextAvailChannel(pau, &iAvailCh, uChannelMask);

        pfx->m_iChCfg = iConfig;
        pcis->m_iFxBandConfig = iConfig;

        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis->m_bFxUseUniformBands = (uVal==1 ? WMAB_TRUE : WMAB_FALSE);

        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis->m_bFxArbitraryBandConfig = (uVal==1 ? WMAB_TRUE : WMAB_FALSE);

        if (pcis->m_bFxUseUniformBands || pcis->m_bFxArbitraryBandConfig)
        {
            PLUS_GETBITS(wmaResult, (UInt)pfx->m_cBandsBits+1, &uVal);
        }
        else
        {
            PLUS_GETBITS(wmaResult, (UInt)pfx->m_cBandsBits, &uVal);
        }
        cBands =  uVal + 1;

        if (pcis->m_bFxArbitraryBandConfig)
        {
            TRACEWMA_EXIT(wmaResult, freqexDecodeMinRatioBandSizeM(paudec, &pfx->m_iMinRatioBandSizeM));
            TRACEWMA_EXIT(wmaResult, freqexDecodeBandSizeM(paudec,
                                                           pfx->m_piFexBandSizesM,
                                                           pfx->m_iMinRatioBandSizeM,
                                                           pfx->m_piBandSizeM,
                                                           pcis->m_bFxUseUniformBands,
                                                           &pfx->m_uiExpBandSizeMIndex,
                                                           &pfx->m_iExpBandSizeM,
                                                           pfx->m_rgiExpBandSizeM,
                                                           pfx->m_rgiMaxBandsTemp,
                                                           pfx->m_cMaxBands,
                                                           cBands,
                                                           &pcis->m_bFxArbitraryBandConfig));
            if (WMAB_FALSE == pcis->m_bFxArbitraryBandConfig)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }

        pcis->m_iFxScaleBands = cBands;
        pcis->m_iFxMvBands = cBands;

        // see which channels to apply this to
        if (iChannelsRem==1)
        {
            bApplyToAllRemChannels = 1;
        }
        else
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            bApplyToAllRemChannels = (Bool)uVal;
        }

        iChannelsRemOrig = iChannelsRem;
        uMask = 1;
        for (i=0; i < pfx->m_iNumMvChannels; i++)
        {
            if ((uChannelMask & uMask) == 0) // not yet coded
            {
                if (WMAB_FALSE==bApplyToAllRemChannels)
                {
                    PLUS_GETBITS(wmaResult, 1, &uVal);
                }
                if (bApplyToAllRemChannels || uVal==1)
                {
                    pcisCh = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];
                    freqexCopyBandConfig(pcisCh, pcis);
                    uChannelMask |= uMask;
                    iChannelsRem--;
                }
            }
            uMask <<= 1;
        }
        if (iChannelsRem==iChannelsRemOrig || iChannelsRem < 0)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        freqexDumpBandConfigCfg(pfx, iConfig, pcis);
        if (iChannelsRem==0)
            break;
        iConfig++;
        pfx->m_piBandSizeM += pfx->m_cMaxBands;
    }

    if (pfx->m_bUseSingleMv)
    {
        for (i=0; i < pfx->m_nChCode; i++)
        {
            pcisCh = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];
            freqexCopyBandConfig(pcisCh, pcis);
        }
    }

exit:
    return wmaResult;
}

WMARESULT freqexDecodeStartPos(CAudioObjectDecoder *paudec, Int *piStartPos)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    U32 uVal;
    //Int cBins = freqexStartPosBins(pau, pfx);
    Int cBins = pfx->m_cStartPosBins;
    Int iRem, nRem, iLogNRem, iNShortVals, a;

    PLUS_GETBITS(wmaResult, FEX_STARTPOSSMALLBITS, &uVal);

    if (uVal != FEX_STARTPOSSMALL-1)
    {
        *piStartPos =
            freqexInvQuantMin(uVal,FEX_STARTPOSSMALL, 0, cBins-1);
    }
    else
    {
        nRem = cBins - (FEX_STARTPOSSMALL-1);
        iLogNRem = CEILLOG2((U32)nRem);
        iNShortVals = (1<<iLogNRem) - nRem;
        TRACEWMA_EXIT(wmaResult, freqexGet1ofN(paudec, nRem, iLogNRem,
                                               iNShortVals, &uVal));
        iRem = uVal;
        a = iRem/(cBins/FEX_STARTPOSSMALL - 1);
        if (a < FEX_STARTPOSSMALL-1)
            *piStartPos = iRem + a + 1;
        else
            *piStartPos = iRem + FEX_STARTPOSSMALL - 1;
    }

exit:
    return wmaResult;
}

WMARESULT freqexDecodeAndGetTileConfig(CAudioObjectDecoder *paudec,
                                       Int cSubFrameSampleHalf)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    Int iFexStartPos=-1, i, iFexStartPosIndex;
    U32 uVal;
    //Int cStartPosBits;
    Bool bAnyUseNoiseFloor, bAnyUseExplicitStartPos;
    PerChannelInfoShr *pcis, *pcis0;

    pcis0 = pau->m_rgpcinfoShr + pfx->m_rgiChCode[0];

    if (pfx->m_bFirstTile)
    {
        // decode max bw
        PLUS_GETBITS(wmaResult, (UInt)pfx->m_cEndPosBits, &uVal);
        pfx->m_iMaxFreq = freqexInvQuantBw(pau, pfx, uVal);
        // decode single mv or not
        if (pfx->m_nChCode > 1)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            pfx->m_bUseSingleMv = (Bool)uVal;
        }
        else
        {
            pfx->m_bUseSingleMv = WMAB_FALSE;
        }
        // decode sc bins
        pfx->m_iScBinsMultiplier = 1;
        while (1)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            if (uVal == 0)
                break;
            pfx->m_iScBinsMultiplier <<= 1;
        }
        if (pfx->m_iScBinsMultiplier >= (1 << 20))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        freqexSetScBins(pfx);
        // decode mv bins
        pfx->m_iMvBinsMultiplier = 1;
        while (1)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            if (uVal == 0)
                break;
            pfx->m_iMvBinsMultiplier <<= 1;
        }
        if (pfx->m_iMvBinsMultiplier >= (1 << 20))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        freqexSetMvBins(pfx);
        // set overlay params coded & noise floor params coded to false
        pfx->m_bOverlayCoded = WMAB_FALSE;
        pfx->m_bNoiseFloorParamsCoded = WMAB_FALSE;
        pfx->m_bMinRunOfZerosForOverlayCoded = WMAB_FALSE;
        // set first tile to false
        pfx->m_bFirstTile = WMAB_FALSE;
    }

    if (pfx->m_bUseSingleMv)
        pfx->m_iNumMvChannels = 1;
    else
        pfx->m_iNumMvChannels = pfx->m_nChCode;

    // decode Rico split or not
    PLUS_GETBITS(wmaResult, 1, &uVal);
    pfx->m_bSplitTileIntoSubtiles = (Bool)uVal;

    // decode whether exponent, noise floor, or sign is being used
    bAnyUseNoiseFloor = WMAB_FALSE;
    for (i=0; i < pfx->m_iNumMvChannels; i++)
    {
        pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis->m_bFxUseExponent = (Bool)uVal;
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis->m_bFxUseNoiseFloor = (Bool)uVal;
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis->m_bFxUseSign = (Bool)uVal;
        bAnyUseNoiseFloor |= pcis->m_bFxUseNoiseFloor;
    }
    if (pfx->m_bUseSingleMv)
    {
        for (i=1; i < pfx->m_nChCode; i++)
        {
            pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

            pcis->m_bFxUseExponent = pcis0->m_bFxUseExponent;
            pcis->m_bFxUseSign = pcis0->m_bFxUseSign;
            pcis->m_bFxUseNoiseFloor = pcis0->m_bFxUseNoiseFloor;
        }
    }
    // decode random noise floor mv or not & noise floor thresh
    uVal = 0;
    if (bAnyUseNoiseFloor && WMAB_FALSE==pfx->m_bNoiseFloorParamsCoded)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis0->m_bFxUseRandomMv2 = (Bool)uVal;
        PLUS_GETBITS(wmaResult, 2, &uVal);
        pcis0->m_iFxNoiseFloorThresh = uVal;
        pfx->m_bNoiseFloorParamsCoded = WMAB_TRUE;
    }

    // decode motion res/mv search range, only do once for whole tile
    PLUS_GETBITS(wmaResult, 2, &uVal);
    pcis0->m_eFxMvRangeType = (FexMvRangeType)uVal;
    PLUS_GETBITS(wmaResult, 1, &uVal);
    pfx->m_bUseMvPredLowband = (Bool)uVal;
    PLUS_GETBITS(wmaResult, 1, &uVal);
    pfx->m_bUseMvPredNoise = (Bool)uVal;
    for (i=1; i < pfx->m_nChCode; i++)
    {
        pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

        pcis->m_bFxUseRandomMv2 = pcis0->m_bFxUseRandomMv2;
        pcis->m_iFxNoiseFloorThresh = pcis0->m_iFxNoiseFloorThresh;
        pcis->m_eFxMvRangeType = pcis0->m_eFxMvRangeType;
        pcis->m_iFxMvResType = pcis0->m_iFxMvResType;
    }
    freqexSetMvType(pfx);

    // decode start pos
    bAnyUseExplicitStartPos = WMAB_FALSE;
    for (i=0; i < pfx->m_iNumMvChannels; i++)
    {
        pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcis->m_bFxUseImplicitStartPos = (uVal==1) ? WMAB_TRUE : WMAB_FALSE;
        if (WMAB_FALSE==pcis->m_bFxUseImplicitStartPos)
            bAnyUseExplicitStartPos = WMAB_TRUE;
        if (WMAB_TRUE == pcis->m_bFxUseImplicitStartPos &&
            WMAB_FALSE == pfx->m_bMvRangeFull &&
            WMAB_FALSE == pfx->m_bOverlayCoded)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            pfx->m_bOverlay = (Bool)uVal;
            pfx->m_bOverlayCoded = WMAB_TRUE;
        }
    }
    if (pfx->m_bUseSingleMv)
    {
        for (i=1; i < pfx->m_nChCode; i++)
        {
            pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

            pcis->m_bFxUseImplicitStartPos = pcis0->m_bFxUseImplicitStartPos;
        }
    }
    if (WMAB_TRUE==bAnyUseExplicitStartPos)
    {
#if 0
        cStartPosBits = freqexStartPosBits(pau, pfx);
        PLUS_GETBITS(wmaResult, (UInt)cStartPosBits, &uVal);
        iFexStartPosIndex = uVal;
#else
        TRACEWMA_EXIT(wmaResult,
                      freqexDecodeStartPos(paudec, &iFexStartPosIndex));
#endif
        iFexStartPos =
            freqexInvQuantStartPos(paudec->pau, pfx, iFexStartPosIndex);
        CHECK_START_POS(iFexStartPos);
        pfx->m_iExplicitStartPos = iFexStartPos;
    }
    // set the end position
    freqexSetEnd(pau, cSubFrameSampleHalf);

    if ((WMAB_TRUE==bAnyUseExplicitStartPos ||
         (WMAB_TRUE==pfx->m_bOverlay && WMAB_TRUE==pfx->m_bOverlayCoded) ||
         MvRangeFullNoOverwriteBase==pcis0->m_eFxMvRangeType) &&
        WMAB_FALSE==pfx->m_bMinRunOfZerosForOverlayCoded)
    {
        // get min # of zeros for overlay
        PLUS_GETBITS(wmaResult, 2, &uVal);
        pfx->m_cMinRunOfZerosForOverlayIndex = uVal;
        pfx->m_bMinRunOfZerosForOverlayCoded = WMAB_TRUE;
    }

    // modify start/end pos for Rico split
    pfx->m_cSubtiles = 1;
    pfx->m_cSubFrameSampleHalf = cSubFrameSampleHalf;
    pfx->m_cTileSize = pfx->m_cSubFrameSampleHalf;
    pfx->m_cOrigEnd = pfx->m_cEnd;
    if (pfx->m_bSplitTileIntoSubtiles)
    {
        pfx->m_cSubtiles *= 2;
        pfx->m_cTileSize /= 2;
        pfx->m_cEnd = (pfx->m_cEnd+1)/2;
    }

    pfx->m_cMinRunOfZerosForOverlay =
        freqexIndexToMinRunOfZerosForOverlay(pau, pfx,
                                     pfx->m_cMinRunOfZerosForOverlayIndex);

    freqexDumpConfig(pau, pfx, paudec->m_iCurrTile);

    // decode band configuration
    TRACEWMA_EXIT(wmaResult, freqexDecodeBandConfig(paudec));

    pfx->m_bOverlayOnly = WMAB_FALSE;
    pfx->m_bScaleBandSplitV2 = WMAB_FALSE;
    pfx->m_piFexBandSizesM = freqexSetBandSizeM(pfx->m_bScaleBandSplitV2);

exit:
    return wmaResult;
}

WMARESULT freqexDecodeTile(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &(pau->m_fex);
    Int iCh, iChSrc, iChFirst=0, iChCode;
    PerChannelInfo *ppcinfo, *ppcinfoFirst=0;
    QuantStepType fGlobalQ = FFLT_ZERO;
    Int curFirstCh = pau->m_rgiChInTile[0];
    Int cSubFrameSampleHalf =
        pau->m_rgpcinfo[curFirstCh].m_cSubFrameSampleHalf;
    Int iOffset, iSubtile, iBand;
    FexGlobalParam *pfxgp;
    PerChannelRecon *ppcr, *ppcrFirst = NULL;
    Bool bMvUpdate = WMAB_TRUE;
    PerChannelInfoShr *pcis;

    pfx->m_iFirstChLogScaleIndex = 0;
    pfx->m_iIteration = 3;

    if (pfx->m_bReconDomain)
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    if (WMAB_FALSE==pfx->m_bHasPower)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

#ifdef FEXTILE_SYNCBITS_DEBUG
    {
        Int uVal;
        PLUS_GETBITS(wmaResult, 8, &uVal);
        assert(0xFF == uVal);    
    }
#endif //FEXTILE_SYNCBITS_DEBUG

#if defined(FEX_DEBUGSTARTPOS)
    {
        PLUS_GETBITS(wmaResult, 16, &uVal);
        assert(uVal == pau->m_cLastCodedIndex);
    }
#endif // FEX_DEBUGSTARTPOS

    if (pau->m_bDoFexOnCodedChannels && pau->m_iVersion >= 3)
    {
        // get global quant factor which will be applied later on
        fGlobalQ = qstCalcQuantStep( pau->m_iQuantStepSize, 0 );
    }

#if 0
    {
        static Bool fexDecPrt = 0;
        if (!fexDecPrt)
        {
            printf("Fex detected\n");
            fexDecPrt = 1;
        }
    }
#endif

    if (pfx->m_iVersion == 1)
    {
        TRACEWMA_EXIT(wmaResult,
            freqexDecodeAndGetTileConfig(paudec, cSubFrameSampleHalf));
    }
#ifdef BUILD_WMAPROLBRV2
    else if(pfx->m_bReconDomain)
    {
        freqexSetCommonTilePtrs(pau, pfx->m_prtiCurr);
        freqexGetReconTileConfigV2(paudec, cSubFrameSampleHalf);
    }
    else
    {
        if (pfx->m_iVersion == 2)
        {
            TRACEWMA_EXIT(wmaResult,
                freqexDecodeAndGetCodingTileConfigV2(paudec, cSubFrameSampleHalf));
        }
#ifdef BUILD_WMAPROLBRV3
        else if (pfx->m_iVersion > 2)
        {
            TRACEWMA_EXIT(wmaResult,
                freqexDecodeAndGetCodingTileConfigV3(paudec, cSubFrameSampleHalf));
        }
#endif
    }
    freqexDumpConfig(pau, pfx, paudec->m_iCurrTile);

    if (pfx->m_iVersion > 1 && (pfx->m_bReconDomain || !pfx->m_bV1Compatible))
    {
        // set param from subframe-level GlobalParam
        TRACEWMA_EXIT(wmaResult,
            freqexSetLocalParamsFromGlobalParam(pau, pfxgp));
    }
#endif

    if (pfx->m_iVersion > 1 && pfx->m_bSplitTileIntoSubtiles)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    
    pfx->m_uChGroupProcessed = 0;
    iChCode = 0;
    pfx->m_bMvResTypeCoded = WMAB_FALSE;
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        if (!ppcinfo->m_bFex)
            continue;

        if (iCh >= pfx->m_iAllocCh)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        pcis = ppcinfo->m_ppcinfoShr;

        freqexSetGroup(pau, iChSrc, WMAB_TRUE, WMAB_FALSE);
        if (1 == pfx->m_iVersion)
        {
            freqexSetNonzeroMaskFromCoef(pau, ppcinfo->m_rgCoefRecon,
                                         ppcinfo->m_cSubFrameSampleHalf,
                                         WMAB_FALSE);
            pfx->m_uChGroupProcessed &= ~1;
        }
        else if (2 < pfx->m_iVersion)
        {
            // to get processed mask
            freqexFindStartPosForOverlay(pau, iChSrc);
        }

        pfx->m_wmaResult = WMA_OK;
        freqexSetChannelConfig(pau, ppcinfo, iChCode, iChSrc);

        // Check for errors in the call above...
        if (WMA_FAILED(pfx->m_wmaResult))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        freqexDumpBandConfig(pfx);

        if (iChCode==0)
        {
            iChFirst = iChSrc;
            ppcinfoFirst = ppcinfo;
        }

        if (pfx->m_bSplitTileIntoSubtiles && !pau->m_bIgnoreFreqex)
        {
            assert(!pfx->m_bReconDomain);
            freqexBufOps(pau, CopyBuf, 0, ppcinfo->m_rgCoefRecon,
                      ppcinfo->m_rgCoefRecon, ppcinfo->m_cSubFrameSampleHalf);
        }
        pfx->m_pfRecon = ppcinfo->m_rgCoefRecon; // direct recon

        for (iSubtile = 0; iSubtile < pfx->m_cSubtiles; iSubtile++)
        {
            CoefType *pfRecon;
            iOffset = iSubtile*pfx->m_cTileSize;

            // needed only to store the mv's in single mv case
            freqexInitPcInfo(pau, ppcinfo, iChSrc);
            TRACEWMA_EXIT(wmaResult, freqexOffsetPcInfo(pau, ppcinfo, iSubtile));
            if (WMAB_TRUE==pfx->m_bUseSingleMv)
            {
                freqexInitPcInfo(pau, ppcinfoFirst, iChFirst);
                TRACEWMA_EXIT(wmaResult, freqexOffsetPcInfo(pau, ppcinfoFirst, iSubtile));
            }
#ifdef BUILD_WMAPROLBRV2
            TRACEWMA_EXIT(wmaResult,
                freqexSetScaleFacPtrChannel( pau, ppcinfo, iChSrc ));

            if (pfx->m_bReconDomain)
                freqexSetPerChTilePtrs(pau, pfx->m_prtiCurr, ppcinfo, iChSrc);
#endif
            pfx->m_pfLowband = ppcinfo->m_rgCoefRecon + iOffset;

#ifdef BUILD_WMAPROLBRV2
            if (pfx->m_iVersion > 1 && !pfx->m_bReconDomain)
                *(ppcinfo->m_piFexLogScaleFacIndexRef) = 
                freqexComputeScaleRefV2( pfx, pfx->m_pfLowband,
                  ppcinfo->m_cLeftShiftBitsTotal
                - ppcinfo->m_cLeftShiftBitsQuant );
#endif
            if (0==iChCode && 0==iSubtile)
                pfx->m_bFirstScaleFacCh = WMAB_TRUE;

            // entropy decode scale factors & motion vectors
            if (pfx->m_iVersion == 1 || (!pfx->m_bReconDomain && pfx->m_bV1Compatible))
            {
                pfx->m_rgiBandStart[pfx->m_cHoleBands] = pfx->m_cStart;
                pfx->m_bNoiseMvDecoded = WMAB_FALSE;
                pfx->m_iScaleBand = 0;
                pfx->m_iCoeffScaleFacBand = 0;
                freqexInitMvPred(pfx);
                for (iBand=0; iBand < pfx->m_cMvBands; iBand++)
                {
                    Int iActLen = 1; // initialize to any non-0 value

                    pfx->m_cBandSize = pfx->m_piMvBandSizes[iBand];
                    if (iBand <= pfx->m_cHoleBands)
                        pfx->m_cStartIndex = pfx->m_rgiBandStart[iBand];
                    pfRecon = pfx->m_pfRecon + pfx->m_cStartIndex;
                    freqexSetBandParams(pau, ppcinfo, iChCode, iBand);
                    if (0==iBand)
                        pfx->m_bFirstScaleFacBand = WMAB_TRUE;
                    if (WMAB_TRUE == pfx->m_bOverlayUsedForBand)
                        iActLen = freqexGetValidLength(pfx, pfRecon,
                                                       pfx->m_cBandSize);

                    TRACEWMA_EXIT(wmaResult,
                                  freqexDecodeScale(paudec, ppcinfo, iChCode, iBand, iActLen));
                    freqexSetNeedMvCoding(pfx, ppcinfo, iBand, iActLen);
                    TRACEWMA_EXIT(wmaResult,
                                  freqexDecodeCb(paudec, ppcinfo, ppcinfoFirst, iChCode, iBand));
                    TRACEWMA_EXIT(wmaResult,
                                  freqexDecodeMv(paudec, ppcinfo, ppcinfoFirst, iChCode, iBand));
                    TRACEWMA_EXIT(wmaResult,
                                  freqexReconBand(pau, ppcinfo, iBand, pfRecon,
                                                  pfx->m_pfLowband, fGlobalQ));
                    freqexUpdateFirstLowbandInfo(pfx, ppcinfo->m_piFexCb[iBand]);
                    
#ifdef BUILD_WMAPROLBRV2
                    freqexDumpV1BandInfoDec(pfx, ppcinfo, iChCode, iBand);
#endif

                    if (iBand >= pfx->m_cHoleBands)
                        pfx->m_cStartIndex += pfx->m_cBandSize;
                }
            }
#ifdef BUILD_WMAPROLBRV2
            else
            {
                if (pfx->m_bOverlayOnly &&
                    !(pfx->m_iVersion > 1 && !pfx->m_bReconDomain &&
                     (!pcis->m_bFxUseImplicitStartPos || pfx->m_bOverlay)))
                {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                }
                    
                pfx->m_cScaleBandsOverlayOnly = pfx->m_cScaleBands;
                pfx->m_cMvBandsOverlayOnly = pfx->m_cMvBands;
                if (pfx->m_bReconDomain)
                {
                    if (pfx->m_bFirstTileV2Recon)
                        pfx->m_rgiScFacResidualBufOffset[iChCode] = 0;

                    // base scale
                    TRACEWMA_EXIT(wmaResult,
                                  freqexDecodeScaleFacBaseFrameV2(paudec, ppcinfo, iChCode));
                    // fex scale
                    TRACEWMA_EXIT(wmaResult,
                                  freqexDecodeScaleFacFrameV2(paudec, ppcinfo, ppcinfoFirst, iChCode));

                    if (pfx->m_iVersion > 2 && 
                        chexInfoStatNoFx(pfx->m_prtiCurr->m_uInfoStat))
                        goto next_ch;

                    // mv merged
                    TRACEWMA_EXIT(wmaResult, 
                                  freqexDecodeMvMergedV2(paudec, ppcinfo, ppcinfoFirst, iChCode, &bMvUpdate));
                    ppcr = NULL;
                    if( !bMvUpdate )
                    {
                        if (pfx->m_rgprtiMvAnchor[iChCode] == NULL)
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                        if (!chexInfoStatCodeFx(pfx->m_rgprtiMvAnchor[iChCode]->m_uInfoStat))
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                        // recon params of anchor tile
                        ppcr = pfx->m_rgprtiMvAnchor[iChCode]->m_prfxrti->m_rgpcr + iChSrc;
                    }
                    if (iChCode == 0)
                        ppcrFirst = pfx->m_rgprtiMvAnchor[iChCode]->m_prfxrti->m_rgpcr + iChSrc;;
                }
                else
                {
                    Int   cScaleBandsSave;

                    cScaleBandsSave = pfx->m_cScaleBands;
                    if (pfx->m_bOverlayOnly)
                    {
                        pfx->m_cStartIndex = pfx->m_cStart;
                        for (iBand = 0; iBand < pfx->m_cMvBands; iBand++)
                        {
                            if (pfx->m_cStartIndex >= pfx->m_iMaxLastCodedIndex)
                            {
                                pfx->m_cMvBandsOverlayOnly = iBand;
                                break;
                            }
                            pfx->m_cStartIndex += pfx->m_piMvBandSizes[iBand];
                        }
                        pfx->m_cStartIndex = pfx->m_cStart;
                        for (iBand = 0; iBand < pfx->m_cScaleBands; iBand++)
                        {
                            if (pfx->m_cStartIndex >= pfx->m_iMaxLastCodedIndex)
                            {
                                pfx->m_cScaleBandsOverlayOnly = iBand;
                                break;
                            }
                            pfx->m_cStartIndex += pfx->m_piScaleBandSizes[iBand];
                        }
                        pfx->m_cScaleBands = pfx->m_cScaleBandsOverlayOnly;
                    }

                    if( pfx->m_cScaleBands > 0 ) // cScaleBand=0 may happen with m_bOverlayOnly=1
                    {
                        TRACEWMA_EXIT(wmaResult,
                                      freqexDecodeScaleFacFrameV2(paudec, ppcinfo, ppcinfoFirst, iChCode));
                    }

                    pfx->m_cScaleBands = cScaleBandsSave;
                }

                pfx->m_rgiBandStart[pfx->m_cHoleBands] = pfx->m_cStart;
                pfx->m_bNoiseMvDecoded = WMAB_FALSE;
                pfx->m_iScaleBand = 0;
                pfx->m_iCoeffScaleFacBand = 0;
                freqexInitMvPred(pfx);
                for (iBand = 0; iBand < min(pfx->m_cMvBands, pfx->m_cMvBandsOverlayOnly); iBand++)
                {
                    Int iActLen = 1; // initialize to any non-0 value
                    Int iScBandStart, i;

                    pfx->m_cBandSize = pfx->m_piMvBandSizes[iBand];
                    if (iBand <= pfx->m_cHoleBands)
                        pfx->m_cStartIndex = pfx->m_rgiBandStart[iBand];
                    pfRecon = pfx->m_pfRecon+pfx->m_cStartIndex;
                    freqexSetBandParams(pau, ppcinfo, iChCode, iBand);

                    if (WMAB_TRUE == pfx->m_bOverlayUsedForBand)
                    {
                        iActLen = freqexGetValidLength(pfx, pfRecon,
                                                       pfx->m_cBandSize);
                        if( iActLen == 0 )
                        {
                            for (i = iScBandStart = 0; i < iBand ; i++)
                                iScBandStart += pfx->m_rgcScaleBandsPerMvBand[i];
                            for (i = 0; i < pfx->m_rgcScaleBandsPerMvBand[iBand]; i++)
                                ppcinfo->m_piFexLogScaleFacIndex[iScBandStart+i] = 0; // this will set bNeedMvCoding FALSE
                        }
                    }

                    freqexSetNeedMvCoding(pfx, ppcinfo, iBand, iActLen);

                    if (bMvUpdate == WMAB_TRUE)
                    {
                        // decode Cb
                        TRACEWMA_EXIT(wmaResult,
                                      freqexDecodeCbV2(paudec, ppcinfo, ppcinfoFirst, ppcrFirst, iChCode, iBand));
                        // decode Mv
                        TRACEWMA_EXIT(wmaResult,
                                      freqexDecodeMvV2(paudec, ppcinfo, ppcinfoFirst, ppcrFirst, iChCode, iBand));
                        // set initial value of noise codebook offset
                        if (pfx->m_bReconDomain)
                        {
                            if (ppcinfo->m_piFexCb[iBand] == 1)
                                ppcinfo->m_piFexMvOffsetNoiseCB[iBand] = 0;
                            else
                                ppcinfo->m_piFexMvOffsetNoiseCB[iBand] = -1;
                        }
                    }
#ifdef BUILD_WMAPROLBRV3
                    if (pfx->m_iVersion > 2 && pfx->m_bReconDomain )
                    {
                        catchFP();

                        TRACEWMA_EXIT(wmaResult,
                                      freqexDecodeBandBaseScaleV3(paudec, ppcinfo, iBand, 
                                                    &ppcinfo->m_pffltFexScaleFacNoise[iBand]));
                    }
#endif
                    // reconstruction
                    if(!pfx->m_bReconDomain)
                    {
                        TRACEWMA_EXIT(wmaResult,
                                    freqexReconBand(pau, ppcinfo, iBand, pfRecon,
                                                    pfx->m_pfLowband, fGlobalQ));
                    }
                    freqexUpdateFirstLowbandInfo(pfx, ppcinfo->m_piFexCb[iBand]);

                    if (iBand >= pfx->m_cHoleBands)
                        pfx->m_cStartIndex += pfx->m_cBandSize;
                }
            }
#else
            else assert( WMAB_FALSE );
#endif

            if(!pfx->m_bReconDomain)
                pfx->m_pfRecon += pfx->m_cTileSize;
#ifdef BUILD_WMAPROLBRV2
            else
                freqexSavePerChTileParams(pau, pfx->m_prtiCurr, ppcinfo, iChSrc);
#endif
        }

        if (pfx->m_bSplitTileIntoSubtiles && !pau->m_bIgnoreFreqex)
        {
            assert(!pfx->m_bReconDomain);
            freqexInvSplitRecon(pfx, ppcinfo->m_rgCoefRecon, ppcinfo);
        }

#if defined(BUILD_WMAPROLBRV2)
        if (WMAB_TRUE == pau->m_bCxPresent && !pfx->m_bReconDomain)
        {
            TRACEWMA_EXIT(wmaResult, chexCopyFex(pau, (Int)iChSrc));
        }
#endif

#if defined(FEX_DBG_RECON_DUMP)
        {
            static FILE *fprecon = NULL;
            if (NULL == fprecon)
                fprecon = fopen("decrecon.rec", "wb");
            fwrite(ppcinfo->m_rgCoefRecon, sizeof(CoefType),
                   ppcinfo->m_cSubFrameSampleHalf, fprecon);
        }
#endif
#if defined(FEX_DBG_RECON_PRINT)
        {
            Int i;
            printf("================\n");
            for (i=0; i < pfx->m_cSubFrameSampleHalf; i++)
                printf("RECON=%d %d %f\n",
                       iChCode, i, ppcinfo->m_rgCoefRecon[i]);
        }
#endif
        if (pfx->m_bReconDomain)
            *(ppcinfo->m_pcFexSubframesMvMerged) -= 1;
next_ch:
        iChCode++;
    }

#ifdef BUILD_WMAPROLBRV2
    if (pfx->m_bReconDomain)
    {
        freqexSaveCommonTileParams(pau, pfx->m_prtiCurr);
        freqexResetCommonTileParams(pau, pfx->m_prtiCurr);
    }
#endif

exit:

    return wmaResult;
}

#endif // BUILD_WMAPROLBRV1
