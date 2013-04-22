//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "msaudio.h"

#if defined(BUILD_WMAPROLBRV2)

#include "fex.h"
#include "fexdectbls.h"
#include "chexpro.h"
#include "chexdectblspro.h"
#include <limits.h>

#ifdef BUILD_WMAPROLBRV2

WMARESULT auPreScaleCoeffsLBR ( CAudioObject  * const pau, 
                          const ReconTileInfo * const prti );

WMARESULT auPostScaleCoeffsLBR( CAudioObject  * const pau,
                          const ReconTileInfo * const prti );

#endif

// ======================================================================

#if (CX_DCT_ONLY==0)
#define RECONPROC_HIST_SIZE (prp->m_cFrameSampleHalfChex)
#else
#define RECONPROC_HIST_SIZE (prp->m_cFrameSampleHalfChex/2)
#endif

// ======================================================================

WMARESULT chexIMCLTTile(CAudioObject *pau,
                        PerChannelInfo *ppcinfo,
                        ReconTileInfo *prti,
                        Bool bMCLT,
                        CoefType *pBuf,
                        CoefType *pOut,
                        CoefType *pHist);

// declare variables for debugging CX stages
#include "dbgmacros.h"
DBG_CX_DECL
#include "dbgmacrosimpl.h"

// ======================================================================

ChexType qstCalcQuantStepInterp( const ChexType fScale )
{
    // !! need to build lookups for this function. it is best if this is
    // !! done using the decoded iIndex from the bitstream and the cBins
    // !! value to select the table, stride, and offset for the lookup.

    return CX_FROM_FLOAT( (Float)pow( 10.0f, FLOAT_FROM_CX( fScale ) ) );
}

// step vs. min quant step should be integer multiple
WMARESULT qfInit(QuantFlt *pqf, ChexType fMin, ChexType fMax,
                 Int iBins, Int iBinsPred, Bool bRndSign)
{
    WMARESULT wmaResult = WMA_OK;
    ChexType fPredRange;
    Int iMinBins, iMaxBins;

    pqf->m_fMin = fMin;
    pqf->m_fMax = fMax;
    pqf->m_iBins = iBins;
    pqf->m_iBinsPred = iBinsPred;
    pqf->m_fStep = (fMax-fMin)/iBins;
    pqf->m_iMin = 0;
    pqf->m_iMax = 0;

    pqf->m_iBits = CEILLOG2(pqf->m_iBins);

    pqf->m_bRndSign = bRndSign;

    if (bRndSign)
    {
        pqf->m_fMax -= pqf->m_fStep;
        assert(iBinsPred==2*iBins-1 || iBinsPred==iBins);
        pqf->m_iMin = qfQuantRnd(pqf, pqf->m_fMin);
        pqf->m_iMax = qfQuantRnd(pqf, pqf->m_fMax);
    }
    else
    {
        // = 2*(fMax-fMin)
        pqf->m_fMinPred = fMin - fMax;
        fPredRange = (fMax-fMin) - (fMin-fMax);
        pqf->m_fStepPred = fPredRange/iBinsPred;

        pqf->m_iBitsPred = CEILLOG2(pqf->m_iBinsPred);

        // make sure iBinsPred & iBins are related by integer mutiple
        iMinBins = min(iBins, iBinsPred);
        iMaxBins = max(iBins, iBinsPred);
        assert(iMaxBins/iMinBins*iMinBins == iMaxBins);

        pqf->m_fMinStepHalf = min(pqf->m_fStep, pqf->m_fStepPred) / 2;

        pqf->m_iMinStepHalfBins = CX_ROUND(fMax-fMin, pqf->m_fMinStepHalf);
        assert(fabs(pqf->m_iMinStepHalfBins*pqf->m_fMinStepHalf -
                    (fMax-fMin))<0.00001f);

        pqf->m_iStep = CX_ROUND(pqf->m_fStep, pqf->m_fMinStepHalf);
        assert(fabs(pqf->m_fStep-pqf->m_iStep*pqf->m_fMinStepHalf<0.00001f));
        assert(pqf->m_iStep/2*2 == pqf->m_iStep);
        pqf->m_iStep /= 2;

        pqf->m_iStepPred = CX_ROUND(pqf->m_fStepPred, pqf->m_fMinStepHalf);
        assert(ABS(pqf->m_fStepPred-pqf->m_iStepPred*pqf->m_fMinStepHalf)
               < CX_FROM_FLOAT(0.00001f));
        assert(pqf->m_iStepPred/2*2 == pqf->m_iStepPred);
        pqf->m_iStepPred /= 2;
    }

    return wmaResult;
}

// ======================================================================

WMARESULT initReconTileInfo(CAudioObject *pau,
                            ReconProc *prp, ReconTileInfo *prti)
{
    WMARESULT wmaResult = WMA_OK;

    prti->m_rgiPower = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, prti->m_rgiPower);

exit:
    return wmaResult;
}

WMARESULT chexInitAnchorReconTileInfo(CAudioObject *pau, Chex *pcx,
                                      CxAnchorReconTileInfo *pcxarti)
{
    WMARESULT wmaResult = WMA_OK;
    Int dims[2], size[2];
    
    dims[0] = pcx->m_iMaxPairs;
    dims[1] = pcx->m_cMaxBands;

    size[0] = sizeof(ChexType*);
    size[1] = sizeof(ChexType);
    TRACEWMA_EXIT(wmaResult,
                 prvAllocateNDimArr((U8***)&pcxarti->m_param0, 2, dims, size));

    size[1] = sizeof(ChexType);
    TRACEWMA_EXIT(wmaResult,
                 prvAllocateNDimArr((U8***)&pcxarti->m_param1, 2, dims, size));
    TRACEWMA_EXIT(wmaResult,
                 prvAllocateNDimArr((U8***)&pcxarti->m_param2, 2, dims, size));

    // scale / phase
    pcxarti->m_lScNorm  = (ChexType*)pcxarti->m_param0[0];
    pcxarti->m_lrScNorm = pcxarti->m_param1[0];
    pcxarti->m_lrScAng  = pcxarti->m_param2[0];

    pcxarti->m_lmSc = pcxarti->m_param0[0];
    pcxarti->m_rmSc = pcxarti->m_param1[0];

    pcxarti->m_iCodeMono = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcxarti->m_iCodeMono);

exit:
    return wmaResult;
}

WMARESULT chexInitReconTileInfo(CAudioObject *pau,
                                Chex *pcx, ReconTileInfo *prti)
{
    WMARESULT wmaResult = WMA_OK;

    prti->m_rguGroupCh = (U32*)auCalloc(pau->m_cChannel*sizeof(U32));
    CHECKWMA_ALLOC(wmaResult, prti->m_rguGroupCh);

    //prti->m_rgbGroupCx = (Bool*)auCalloc(pau->m_cChannel*sizeof(U32));
    //CHECKWMA_ALLOC(wmaResult, prti->m_rgbGroupCx);

exit:
    return wmaResult;
}

WMARESULT fexInitPerChannelRecon(CAudioObject *pau, Fex *pfx,
                                 PerChannelRecon *ppcr, Int iCh, Int iPos)
{
    WMARESULT wmaResult = WMA_OK;

    if (pfx->m_cMaxBands >= 16384)
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);

    if (pau->m_bEncoder)
    {
        ppcr->m_rgiFexLogScaleFacIndex =
            (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgiFexLogScaleFacIndex);
        ppcr->m_rgiFexLogScaleFacBaseIndex =
            (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgiFexLogScaleFacBaseIndex);
    }

    if (pau->m_bEncoder || 0==iPos)
    {
        ppcr->m_rgfFexScaleFac =
            (FastFloat*)auCalloc(pfx->m_cMaxBands*sizeof(FastFloat));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgfFexScaleFac);
        ppcr->m_rgfFexScaleFacNoise =
            (FastFloat*)auCalloc(pfx->m_cMaxBands*sizeof(FastFloat));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgfFexScaleFacNoise);
        ppcr->m_rgfFexScaleFacBase =
            (FastFloat*)auCalloc(pfx->m_cMaxBands*sizeof(FastFloat));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgfFexScaleFacBase);

        ppcr->m_rgiFexCb = (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgiFexCb);
        ppcr->m_rgiFexMv = (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgiFexMv);
        ppcr->m_rgiFexMv2 = (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgiFexMv2);
        ppcr->m_rgFexExp = (FexType*)auCalloc(pfx->m_cMaxBands*sizeof(FexType));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgFexExp);
        ppcr->m_rgiFexSign = (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgiFexSign);
        ppcr->m_rgbFexRev = (Bool*)auCalloc(pfx->m_cMaxBands*sizeof(Bool));
        CHECKWMA_ALLOC(wmaResult, ppcr->m_rgbFexRev);
    }
    else
    {
        ReconProc *prp = pau->m_prp;
        RFxReconTileInfo *prfxrtiFirst = prp->m_rgrfxrti;
        PerChannelRecon *ppcrFirst = prfxrtiFirst->m_rgpcr + iCh;

        ppcr->m_rgfFexScaleFac = ppcrFirst->m_rgfFexScaleFac;
        ppcr->m_rgfFexScaleFacNoise = ppcrFirst->m_rgfFexScaleFacNoise;
        ppcr->m_rgfFexScaleFacBase = ppcrFirst->m_rgfFexScaleFacBase;

        ppcr->m_rgiFexCb = ppcrFirst->m_rgiFexCb;
        ppcr->m_rgiFexMv = ppcrFirst->m_rgiFexMv;
        ppcr->m_rgiFexMv2 = ppcrFirst->m_rgiFexMv2;
        ppcr->m_rgFexExp = ppcrFirst->m_rgFexExp;
        ppcr->m_rgiFexSign = ppcrFirst->m_rgiFexSign;
        ppcr->m_rgbFexRev = ppcrFirst->m_rgbFexRev;
    }

exit:
    return wmaResult;
}

WMARESULT fexInitReconTileInfo(CAudioObject *pau,
                               Fex *pfx, RFxReconTileInfo *prfxrti, Int iPos)
{
    WMARESULT wmaResult = WMA_OK;
    Int iCh;

    if (pau->m_bEncoder || 0==iPos)
    {
        prfxrti->m_rgiFexScaleBandSizes =
            (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, prfxrti->m_rgiFexScaleBandSizes);
        prfxrti->m_rgiFexMvBandSizes = 
            (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, prfxrti->m_rgiFexMvBandSizes);
        prfxrti->m_rgiFexBaseBandSizes =
            (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, prfxrti->m_rgiFexBaseBandSizes);
    }
    else
    {
        ReconProc *prp = pau->m_prp;
        RFxReconTileInfo *prfxrtiFirst = prp->m_rgrfxrti;

        prfxrti->m_rgiFexScaleBandSizes = prfxrtiFirst->m_rgiFexScaleBandSizes;
        prfxrti->m_rgiFexMvBandSizes = prfxrtiFirst->m_rgiFexMvBandSizes;
        prfxrti->m_rgiFexBaseBandSizes = prfxrtiFirst->m_rgiFexBaseBandSizes;
    }

    prfxrti->m_rgpcr =
        (PerChannelRecon*)auCalloc(pfx->m_iAllocCh*sizeof(PerChannelRecon));
    CHECKWMA_ALLOC(wmaResult, prfxrti->m_rgpcr);
    for (iCh=0; iCh < pfx->m_iAllocCh; iCh++)
    {
        TRACEWMA_EXIT(wmaResult,
           fexInitPerChannelRecon(pau, pfx, prfxrti->m_rgpcr + iCh, iCh, iPos));
    }

exit:
    return wmaResult;
}

Void huffInfoInit(CAudioObject *pau,
                  HuffInfo *phi, Int cBits,
                  const Int iMinSym, const Int iMaxSym,
                  const Int iMinSymBits, const Int iMaxSymBits,
                  const Int iBins, const Int iExtraBits,
                  const U32 *uEncTable, const U16 *uDecTable)
{
    phi->m_iBits = cBits;
    phi->m_iBins = iBins;

    phi->m_iMinSym = iMinSym;
    phi->m_iMaxSym = iMaxSym;

    phi->m_iMinSymBits = iMinSymBits;
    phi->m_iMaxSymBits = iMaxSymBits;

    if (uEncTable != NULL)
        phi->m_uEncTable = uEncTable;
    phi->m_uDecTable = uDecTable;

    phi->m_iExtraBits = iExtraBits;

    phi->m_iResMask = (1<<phi->m_iExtraBits)-1;
    phi->m_iIndexMask = (~(Int)0 & ~(phi->m_iResMask));
}

// =========================================================================
// Band configurations for given number of cx bands
// - for greater than 20, split largest band until desired number of bands
//   reached.
// - for greater or equal to 16 bands, have two configurations

AVRT_DATA const I16 g_iChexBandSizesM1_1[1] =
{256};

AVRT_DATA const I16* g_iChexBandSizesM1[1] =
{g_iChexBandSizesM1_1};

AVRT_DATA const I16 g_iChexBandSizesM4_1[4] =
{4,12,48,192};

AVRT_DATA const I16* g_iChexBandSizesM4[1] =
{g_iChexBandSizesM4_1};

AVRT_DATA const I16 g_iChexBandSizesM8_1[8] =
{2,2,4,8,16,32,64,128};

AVRT_DATA const I16* g_iChexBandSizesM8[1] =
{g_iChexBandSizesM8_1};

AVRT_DATA const I16 g_iChexBandSizesM10_1[10] =
{2,2,4,4,4,8,8,32,64,128};

AVRT_DATA const I16* g_iChexBandSizesM10[1] =
{g_iChexBandSizesM10_1};

AVRT_DATA const I16 g_iChexBandSizesM12_1[12] =
{2,2,4,4,4,4,4,8,16,32,48,128};

AVRT_DATA const I16* g_iChexBandSizesM12[1] =
{g_iChexBandSizesM12_1};

AVRT_DATA const I16 g_iChexBandSizesM16_1[16] =
{2,2,4,4,4,4,4,4,4,4,8,12,16,20,48,116};

AVRT_DATA const I16 g_iChexBandSizesM16_2[16] =
{2,2,2,4,4,4,8,8,10,16,16,16,32,32,34,66};

AVRT_DATA const I16* g_iChexBandSizesM16[2] =
{g_iChexBandSizesM16_1, g_iChexBandSizesM16_2};

AVRT_DATA const I16 g_iChexBandSizesM20_1[20] =
{1,1,1,1,2,2,2,2,4,4,4,4,4,4,8,12,16,20,48,116};

AVRT_DATA const I16 g_iChexBandSizesM20_2[20] =
{2,2,2,2,4,4,4,4,8,8,8,8,16,16,16,16,32,32,32,40};

AVRT_DATA const I16* g_iChexBandSizesM20[2] =
{g_iChexBandSizesM20_1, g_iChexBandSizesM20_2};

AVRT_DATA const Int g_iMinCxBandsForTwoConfigs = 16;

#ifdef CHEX_EXP
AVRT_DATA I16 g_iChexBandSizesMTryN[2048]={0};
#endif // CHEX_EXP

AVRT_DATA const Int g_iCxBandsV2[8] = {
    4, 8, 10, 16, 20, 32, 40, 64
};

AVRT_DATA const Int g_iChexBandMultMSizeV2[8] =
{4, 8, 10, 16, 20, 20, 20, 20};

AVRT_DATA const I16** g_iChexBandSizesMV2[8] =
{g_iChexBandSizesM4,  g_iChexBandSizesM8,
 g_iChexBandSizesM10, g_iChexBandSizesM16,
 g_iChexBandSizesM20, g_iChexBandSizesM20,
 g_iChexBandSizesM20, g_iChexBandSizesM20};

AVRT_DATA const Int g_iCxBandsV3[8] = {
    1, 4, 8, 10, 12, 16, 20, 32
};

AVRT_DATA const Int g_iChexBandMultMSizeV3[8] =
{1, 4, 8, 10, 12, 16, 20, 20};

AVRT_DATA const I16** g_iChexBandSizesMV3[8] =
{g_iChexBandSizesM1,  g_iChexBandSizesM4,
 g_iChexBandSizesM8,  g_iChexBandSizesM10,
 g_iChexBandSizesM12, g_iChexBandSizesM16,
 g_iChexBandSizesM20, g_iChexBandSizesM20};

// =========================================================================

AVRT_DATA const ChexType g_fCxAdjustScaleThreshSq[4] = {
    CX_FROM_FLOAT( 1.0f*1.0f ),
    CX_FROM_FLOAT( 1.25f*1.25f ),
    CX_FROM_FLOAT( 1.5f*1.5f ),
    CX_FROM_FLOAT( 1.75f*1.75f )
};

AVRT_DATA const Float g_fMaxMatrixScale[4] = {
    3.0f, 5.0f, 7.0f, 9.0f
};

// ==========================================================================

WMARESULT chexInitConfig(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = pau->m_pcx;
    ReconProc *prp = pau->m_prp;
    Int cBins = 0, iExtraBits=0;
    U32 uPrevCodingMethod;

    assert(pcx);

    pcx->m_cBands = pcx->m_piCxBands[pcx->m_iNumBandIndex];
    if (pcx->m_cBands > pcx->m_cMaxBands)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

#ifdef CXTEST_NOQUANT
    pcx->m_cBands = pcx->m_cMaxBands;
#endif

    if (pau->m_bPlusSuperframe)
    {
        pcx->m_bNeedIntra = WMAB_TRUE;
        // reset seg start
        pcx->m_prtiSegStart = prp->m_rgchextiBuf + prp->m_iBufCodePos;
        if (0 != pcx->m_iTilesRemInSegment)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
    }

    catchFP();
    pcx->m_adjustScaleThreshSq =
        g_fCxAdjustScaleThreshSq[pcx->m_iAdjustScaleThreshIndex];

    pcx->m_maxMatrixScale =
        CX_FROM_FLOAT(g_fMaxMatrixScale[pcx->m_iMaxMatrixScaleIndex]);
    initFP();
    // pcx->m_maxMatrixScaleThreshApprox =
    //     2.0f / (pcx->m_maxMatrixScale*pcx->m_maxMatrixScale)
    pcx->m_maxMatrixScaleThreshApprox =
        CX_DIV( 2 * CX_ONE,
                CX_MUL(pcx->m_maxMatrixScale, pcx->m_maxMatrixScale));
    pcx->m_maxMatrixScaleThreshExact = 2 * pcx->m_maxMatrixScaleThreshApprox;

    uPrevCodingMethod = pcx->m_uCodingMethod;

    pcx->m_uCodingMethod = 0;
    if (pcx->m_bCodeLMRM)
        SET_CODING_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIXLMRM);
    else
        SET_CODING_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIX);

#define HUFFINFOINIT(num, type) \
    huffInfoInit(pau, &pcx->m_hiParam##num, 0, \
                 g_chexHuff##type##MinSym, g_chexHuff##type##MaxSym, \
                 g_chexHuff##type##MinBits, g_chexHuff##type##MaxBits, \
                 pcx->m_qf##type.m_iBins, \
                 iExtraBits, \
                 NULL, g_chexHuff##type##Dec); \
    huffInfoInit(pau, &pcx->m_hiParam##num##PredT, 0, \
                 g_chexHuff##type##PredTMinSym, \
                 g_chexHuff##type##PredTMaxSym, \
                 g_chexHuff##type##PredTMinBits, \
                 g_chexHuff##type##PredTMaxBits, \
                 pcx->m_qf##type##.m_iBinsPred, \
                 iExtraBits, \
                 NULL, g_chexHuff##type##PredTDec); \
    huffInfoInit(pau, &pcx->m_hiParam##num##PredF, 0, \
                 g_chexHuff##type##PredFMinSym, \
                 g_chexHuff##type##PredFMaxSym, \
                 g_chexHuff##type##PredFMinBits, \
                 g_chexHuff##type##PredFMaxBits, \
                 pcx->m_qf##type##.m_iBinsPred, \
                 iExtraBits, \
                 NULL, g_chexHuff##type##PredFDec);

#define HUFFINFOINIT_ONEPRED(num, type) \
    huffInfoInit(pau, &pcx->m_hiParam##num, 0, \
                 g_chexHuff##type##MinSym, g_chexHuff##type##MaxSym, \
                 g_chexHuff##type##MinBits, g_chexHuff##type##MaxBits, \
                 pcx->m_qf##type.m_iBins, \
                 iExtraBits, \
                 NULL, g_chexHuff##type##Dec); \
    huffInfoInit(pau, &pcx->m_hiParam##num##PredF, 0, \
                 g_chexHuff##type##PredMinSym, \
                 g_chexHuff##type##PredMaxSym, \
                 g_chexHuff##type##PredMinBits, \
                 g_chexHuff##type##PredMaxBits, \
                 pcx->m_qfScale.m_iBinsPred, \
                 iExtraBits, \
                 NULL, g_chexHuff##type##PredDec); \
    huffInfoInit(pau, &pcx->m_hiParam##num##PredT, 0, \
                 g_chexHuff##type##PredMinSym, \
                 g_chexHuff##type##PredMaxSym, \
                 g_chexHuff##type##PredMinBits, \
                 g_chexHuff##type##PredMaxBits, \
                 pcx->m_qfScale.m_iBinsPred, \
                 iExtraBits, \
                 NULL, g_chexHuff##type##PredDec);

    // lr
    //cBins = 50*(1<<pcx->m_iQuantStepIndex);
    // iExtraBits = pcx->m_iQuantStepIndex;
    // cBins = 20*5.0f / (quant step size in dB) = 100/stepsize
    switch (pcx->m_iQuantStepIndex)
    {
    case 0: cBins = 33;   iExtraBits = 0;  break; // 3 dB
    case 1: cBins = 50;   iExtraBits = 0;  break; // 2 dB
    case 2: cBins = 100;  iExtraBits = 1;  break; // 1 dB
    case 3: cBins = 200;  iExtraBits = 2;  break; // 0.5 dB
    default: assert(!"Invalid quant step index");  break;
    }
#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
    REPL_PARAM(cBins, g_iScBins);
#endif
    if (cBins != pcx->m_qfScale.m_iBins)
    {
        catchFP();
        TRACEWMA_EXIT(wmaResult, qfInit(&pcx->m_qfScale,
                                        CX_FROM_FLOAT(0.0f),
                                        CX_FROM_FLOAT(5.0f),
                                        cBins, 2*cBins-1, WMAB_TRUE));
        initFP();
#ifndef CHEX_HUFFTRAIN
        HUFFINFOINIT_ONEPRED(1, Scale);
#endif
    }

    // lrlr scale
    cBins = 5*(1<<pcx->m_iQuantStepIndexLR)+1;
    if (cBins != pcx->m_qfLRScale.m_iBins)
    {
        catchFP();
        TRACEWMA_EXIT(wmaResult, qfInit(&pcx->m_qfLRScale,
                                       CX_FROM_FLOAT(0.0f),
                                       CX_FROM_FLOAT(1.0f+1.0f/(cBins-1)),
                                       cBins, cBins, WMAB_TRUE));
        initFP();
    }

    // phase
    if (IS_SET_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIX))
    {
        //cBins = 4*(1<<pcx->m_iQuantStepIndexPhase)+1;
        switch (pcx->m_iQuantStepIndexPhase)
        {
        case 0: cBins =  4+1;  break; // pi/4
        case 1: cBins =  6+1;  break; // pi/6
        case 2: cBins =  8+1;  break; // pi/8
        case 3: cBins = 16+1;  break; // pi/16
        default: assert(!"Invalid quant step index for phase");  break;
        }
#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
        REPL_PARAM(cBins, g_iPhBins);
#endif
        if (cBins != pcx->m_qfLRAng.m_iBins ||
            pcx->m_uCodingMethod != uPrevCodingMethod)
        {
            catchFP();
            TRACEWMA_EXIT(wmaResult, qfInit(&pcx->m_qfLRAng,
                                  CX_FROM_FLOAT(0.0f),
                                  CX_FROM_FLOAT((Float)(PI+PI/(cBins-1))),
                                  cBins, cBins, WMAB_TRUE));
            initFP();
        }
    }
    else if (IS_SET_FLAG(pcx->m_uCodingMethod, USE_LRPOWERMATRIXLMRM))
    {
        cBins = 5*(1<<pcx->m_iQuantStepIndexPhase)+1;
        // not really an angle, but just r*sin(angle)
        if (cBins != pcx->m_qfLRAng.m_iBins ||
            pcx->m_uCodingMethod != uPrevCodingMethod)
        {
            catchFP();
            TRACEWMA_EXIT(wmaResult, qfInit(&pcx->m_qfLRAng,
                                       CX_FROM_FLOAT(0.0f),
                                       CX_FROM_FLOAT(1.0f+1.0f/(cBins-1)),
                                       cBins, cBins, WMAB_TRUE));
            initFP();
        }
    }

exit:
    return wmaResult;
}

Int chexMaxBandsToIndex(Int iMaxBands, Int iPlusVersion)
{
    Int i;
    const Int *piCxBands = (2 == iPlusVersion) ? g_iCxBandsV2 : g_iCxBandsV3;

    for (i=0; i < 8; i++)
    {
        if (iMaxBands <= piCxBands[i])
            break;
    }

    assert(i < 8);

    return i;
}

INLINE
Int cxGetMaxBands(CAudioObject *pau)
{
    Int iIndex;
    Chex *pcx = pau->m_pcx;

    iIndex = (pau->m_uAdvancedEncodeOpt2 & ENCOPT4_PLUSV2_CXMAXBANDS) >>
        ENCOPT4_PLUSV2_CXMAXBANDS_BITSOFFSET;

    if (2 == pau->m_iPlusVersion)
    {
        if (0 == iIndex)
            return 20;
        else if (iIndex <= 4)
            return pcx->m_piCxBands[iIndex-1];
        else
            return pcx->m_piCxBands[iIndex];
    }
    else
    {
        return pcx->m_piCxBands[iIndex];
    }
}

WMARESULT chexInit(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = pau->m_pcx;
    Fex  *pfx = &(pau->m_fex);
    Int dims[2], size[2];

    assert(FLOAT_FROM_CX(CX_MINLOG) >= (Float)log10(FLOAT_FROM_CX(CX_MINM4)));
    assert(FLOAT_FROM_CX(CX_MAXLOG) <= (Float)log10(FLOAT_FROM_CX(CX_MAXM4)));
    assert(FLOAT_FROM_CX(CXM_MAXSQ) <= (Float)sqrt(CX_MAXM4));

    if (NULL == pcx)
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);

    pcx->m_pau = pau;

    if (2 == pau->m_iPlusVersion)
    {
        pcx->m_piCxBands = g_iCxBandsV2;
        pcx->m_piChexBandMultMSize = g_iChexBandMultMSizeV2;
        pcx->m_iChexBandSizesM = g_iChexBandSizesMV2;
    }
    else
    {
        pcx->m_piCxBands = g_iCxBandsV3;
        pcx->m_piChexBandMultMSize = g_iChexBandMultMSizeV3;
        pcx->m_iChexBandSizesM = g_iChexBandSizesMV3;
    }

    pcx->m_rguFexChannel = (U32*)auCalloc(pau->m_cChannel*sizeof(U32));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rguFexChannel);

    pcx->m_rguGroupCh = (U32*)auCalloc(pau->m_cChannel*sizeof(U32));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rguGroupCh);

    pcx->m_iMaxPairs = pau->m_cChannel/2;

    pcx->m_cMaxBands = cxGetMaxBands(pau);

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
    REPL_PARAM(pcx->m_bPowerForAllBands, g_iPowerForAllBands);
#endif

    // experimental code to change band configuration, etc ...
#ifdef CHEX_EXP
    //pcx->m_iNumBandsInConfig = 10;
    //pcx->m_cMaxBands = 10;
    //pcx->m_piBandConfig = g_iChexBandSizesMTry10;
    //pcx->m_piBandConfig = g_iChexBandSizesMTry20;

    // following is for testing perfect recovery from chex parameters
    //pcx->m_iNumBandsInConfig = 1;
    //pcx->m_cMaxBands = 512;

    pcx->m_bUseNTilesPerFrame = WMAB_TRUE;
    pcx->m_iNTilesPerFrame = 2048/256;
    //pcx->m_iNTilesPerFrame = 2048/2048;
    //pcx->m_cMaxBands = pau->m_cFrameSampleHalf/pcx->m_iNTilesPerFrame;
    pcx->m_iNumBandsInConfig = 20;
    pcx->m_cMaxBands = 20;
    pcx->m_piBandConfig = g_iChexBandSizesMTry20;

    REPL_PARAM(pcx->m_iNTilesPerFrame, g_iNTilesPerFrame);

    if (1 == pcx->m_iNTilesPerFrame)
    {
        Int j=0;
        Int iSample = 2048/128;

        pcx->m_iNumBandsInConfig *= 2048/128;
        pcx->m_cMaxBands = pcx->m_iNumBandsInConfig;
        pcx->m_piBandConfig = g_iChexBandSizesMTryN;
        for (i=0; i < pcx->m_iNumBandsInConfig; i++)
        {
            g_iChexBandSizesMTryN[i] = g_iChexBandSizesMTry3[j];
            if ((i+1)%iSample == 0)
                j++;
        }
    }

    pcx->m_bPowerForAllBands = WMAB_TRUE;

    REPL_PARAM(pcx->m_bPowerForAllBands, g_iPowerForAllBands);
#endif // CHEX_EXP

    pcx->m_rgiBandSizes = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgiBandSizes);
    pcx->m_rgiBandSizesInterp = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgiBandSizesInterp);
    pcx->m_rgiBandStart = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgiBandStart);

    pcx->m_rgiPrevParam0 = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgiPrevParam0);
    pcx->m_rgiPrevParam1 = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgiPrevParam1);
    pcx->m_rgiPrevParam2 = (Int*)auCalloc(pcx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgiPrevParam2);

    pcx->m_rgiPrevLScale  = pcx->m_rgiPrevParam0;
    pcx->m_rgiPrevLRScale = pcx->m_rgiPrevParam1;
    pcx->m_rgiPrevLRAng   = pcx->m_rgiPrevParam2;

    pcx->m_rgiPrevLMScale = pcx->m_rgiPrevParam0;
    pcx->m_rgiPrevRMScale = pcx->m_rgiPrevParam1;

#ifndef BUILD_INTEGER
    pcx->m_rgMonoSc = (ChexType*)auCalloc(pcx->m_cMaxBands*sizeof(ChexType));
#else
    pcx->m_rgMonoSc = (I64*)auCalloc(pcx->m_cMaxBands*sizeof(I64));
#endif
    CHECKWMA_ALLOC(wmaResult, pcx->m_rgMonoSc);

    // initialize huffdec structs
    // associate a huffman code with the quantizer, currently just use
    // the pred F huffman table for all, just need one huffman table, can
    // delete the others
    pcx->m_qfScale.m_phi      = &pcx->m_hiParam1;
    pcx->m_qfScale.m_phiPredT = &pcx->m_hiParam1PredT;
    pcx->m_qfScale.m_phiPredF = &pcx->m_hiParam1PredF;

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
    REPL_PARAM(pcx->m_uCodingMethod, g_iCodingMethod);
#endif

    pcx->m_iNumBandIndexBits = 3;
    pcx->m_iQuantStepIndexBits = 2;
    pcx->m_iBandMultIndexBits = 1;
    pcx->m_iAdjustScaleThreshBits = 2;
    pcx->m_iMaxMatrixScaleBits = 2;
    pcx->m_iAutoAdjustScaleVals = NUM_CXAUTOADJUSTVALS;
    pcx->m_iCxChCodingVals = NUM_CXCHCODINGVALS;
    pcx->m_iFilterTapOutputVals = NUM_CXFILTEROUTPUTVALS;

    pcx->m_bDoReverbAsPostProcess = WMAB_TRUE;

    pcx->m_pcxrf = (CxReverbFilter*)auCalloc(sizeof(CxReverbFilter));
    CHECKWMA_ALLOC(wmaResult, pcx->m_pcxrf);

    size[0] = sizeof(ChexType*);
    size[1] = sizeof(ChexType);

    dims[0] = pcx->m_cMaxBands;
    dims[1] = NUM_CXMATELEMS;

    TRACEWMA_EXIT(wmaResult,
                prvAllocateNDimArr((U8***)&pcx->m_rgrgScMat, 2, dims, size));

exit:
    return wmaResult;
}

Void freeReconTileInfo(CAudioObject *pau,
                       ReconProc *prp, ReconTileInfo *prti)
{
    DELETE_ARRAY(prti->m_rgiPower);
}

Void chexFreeAnchorReconTileInfo(CAudioObject *pau,
                                 Chex *pcx, CxAnchorReconTileInfo *pcxarti)
{
    Int dims[2];

    dims[0] = pcx->m_iMaxPairs;
    dims[1] = pcx->m_cMaxBands;

    prvDeleteNDimArr((U8**)pcxarti->m_param0, 2, dims);
    prvDeleteNDimArr((U8**)pcxarti->m_param1, 2, dims);
    prvDeleteNDimArr((U8**)pcxarti->m_param2, 2, dims);

    DELETE_ARRAY(pcxarti->m_iCodeMono);
}

Void chexFreeReconTileInfo(CAudioObject *pau,
                           Chex *pcx, ReconTileInfo *prti)
{
    DELETE_ARRAY(prti->m_rguGroupCh);
    //DELETE_ARRAY(prti->m_rgbGroupCx);
}

Void fexFreePerChannelRecon(CAudioObject *pau,
                            Fex *pfx, PerChannelRecon *ppcr, Int iPos)
{
    if (pau->m_bEncoder)
    {
        DELETE_ARRAY(ppcr->m_rgiFexLogScaleFacIndex);
        DELETE_ARRAY(ppcr->m_rgiFexLogScaleFacBaseIndex);
    }

    if (pau->m_bEncoder || 0==iPos)
    {
        DELETE_ARRAY(ppcr->m_rgfFexScaleFac);
        DELETE_ARRAY(ppcr->m_rgfFexScaleFacNoise);
        DELETE_ARRAY(ppcr->m_rgfFexScaleFacBase);

        DELETE_ARRAY(ppcr->m_rgiFexCb);
        DELETE_ARRAY(ppcr->m_rgiFexMv);
        DELETE_ARRAY(ppcr->m_rgiFexMv2);
        DELETE_ARRAY(ppcr->m_rgFexExp);
        DELETE_ARRAY(ppcr->m_rgiFexSign);
        DELETE_ARRAY(ppcr->m_rgbFexRev);
    }
}

Void fexFreeReconTileInfo(CAudioObject *pau,
                          Fex *pfx, RFxReconTileInfo *prfxrti, Int iPos)
{
    Int iCh;

    if (pau->m_bEncoder || 0==iPos)
    {
        DELETE_ARRAY(prfxrti->m_rgiFexScaleBandSizes);
        DELETE_ARRAY(prfxrti->m_rgiFexMvBandSizes);
        DELETE_ARRAY(prfxrti->m_rgiFexBaseBandSizes);
    }

    for (iCh=0; iCh < pfx->m_iAllocCh; iCh++)
        fexFreePerChannelRecon(pau, pfx, prfxrti->m_rgpcr + iCh, iPos);

    DELETE_ARRAY(prfxrti->m_rgpcr);
}

Void chexFree(CAudioObject *pau)
{
    Chex *pcx = pau->m_pcx;
    Int dims[2];

    if (NULL == pcx)
        return;

    DELETE_ARRAY(pcx->m_rgiBandSizes);
    DELETE_ARRAY(pcx->m_rgiBandSizesInterp);
    DELETE_ARRAY(pcx->m_rgiBandStart);

    DELETE_ARRAY(pcx->m_rguFexChannel);

    DELETE_ARRAY(pcx->m_rguGroupCh);

    DELETE_ARRAY(pcx->m_rgiPrevParam0);
    DELETE_ARRAY(pcx->m_rgiPrevParam1);
    DELETE_ARRAY(pcx->m_rgiPrevParam2);

    cxReverbFree(pcx->m_pcxrf);
    DELETE_PTR(pcx->m_pcxrf);

    dims[0] = pcx->m_cMaxBands;
    dims[1] = NUM_CXMATELEMS;
    prvDeleteNDimArr((U8**)pcx->m_rgrgScMat, 2, dims);

    DELETE_ARRAY(pcx->m_rgMonoSc);
    freeAligned(pcx->m_rgReconBandScales);
}

// ======================================================================
// CHEX routines

#if ( 1 == CX_DCT_ONLY ) && ( 0 == CX_SMALL_REVERB )
#error CX_DCT_ONLY can only be used with CX_SMALL_REVERB.
#endif

// Any power matrix can be characterized by the following
// [A  B
//  B* C]
// Normalize the whole matrix by following sqrt(A*C)
// Therefore we have
// [A /sqrt(A*C) B/sqrt(A*C)
//  B*/sqrt(A*C) C/sqrt(A*C)]
// Now code (A/sqrt(A*C)) and (B/sqrt(A*C))
// (C/sqrt(A*C)) = 1 / (A/sqrt(A*C))
// If lrScAng < 0, assume signal coded as diff
//
// This function essentially computes the complex KLT of a correlation matrix

INLINE
Void computeScaleFactorMtx(const ChexType lSc,
                           const ChexType rSc,
                           const ChexType lrSc,
                           ChexType *pMonoL, ChexType *pDiffL,
                           ChexType *pMonoR, ChexType *pDiffR)
{
    *pMonoL = lSc + lrSc;
    *pMonoR = rSc + lrSc;
    *pDiffL = CX_SQRT( CX_ONE - CX_MUL(lrSc, lrSc) );
    *pDiffR = -(*pDiffL);
}

// since we only care about the sin & cos of the
// phase angles ( and don't need to compute the
// angles themselves ), we can use trig identities
// to avoid atan2.
INLINE
Void computePhaseMtx(
        ChexType lScNorm, ChexType lrScNorm,
        const ChexType sinA, const ChexType cosA,
        Bool      bMono, 
        ChexType *pcosLP, ChexType *psinLP , 
        ChexType *pcosRP, ChexType *psinRP )
{
    // const ChexType y = lrScNorm*sinA*(bMono?1:-1);
    const ChexType y = CX_MUL(lrScNorm, sinA) * (bMono?1:-1);
    // const ChexType x = lrScNorm*cosA*(bMono?1:-1) + lScNorm;
    const ChexType x = CX_MUL(lrScNorm, cosA) * (bMono?1:-1) + lScNorm;
    const ChexType x2 = CX_MUL(x, x);
    const ChexType y2 = CX_MUL(y, y);
    const Bool bXLarge = ( CXM_MAXSQ <= x );

    ChexType N, cosLP, sinLP, cosRP, sinRP, den;

    den = x2 + y2;

#define CXM_MINDEN CX_FROM_FLOAT(1.0f / (CX_MAX*CX_MAX))

    if ( ( 0 == y ) ||
        (!bXLarge && ( CXM_MINDEN >= den )))
    {
        // y = 0, so den = abs(x), 1/den = 1/abs(x)
        cosLP = ( 0 <= x ) ? CX_ONE : -CX_ONE;
        sinLP = CX_ZERO;
    }
    else if ( 0 == x )
    {
        // x = 0, so den = abs(y), 1/den = 1/abs(y)
        cosLP = CX_ZERO;
        sinLP = ( 0 <= y) ? CX_ONE : -CX_ONE;
    }
    else
    {
        // first order approximation sqrt(x*x+y*y), if x/y>>1 is given by
        // sqrt(x*x+y*y) = abs(x + (y*y)/(2*x))
        if (bXLarge)
            den = CX_ABS( x + CX_DIV( y2, 2*x ));
        else
            // den = (Float)sqrt(x*x+y*y);
            den = CX_SQRT(den);

        // const Float N = 1.0f/den;
        N = CX_DIV( CX_ONE, den);

        // Float cosLP = x*N;
        cosLP = CX_MUL(x, N);
        // Float sinLP = y*N;
        sinLP = CX_MUL(y, N);
    }

    // Float cosRP = cosA*cosLP + sinA*sinLP;
    cosRP = CX_MUL(cosA, cosLP) + CX_MUL(sinA, sinLP);
    // Float sinRP = cosA*sinLP - sinA*cosLP;
    sinRP = CX_MUL(cosA, sinLP) - CX_MUL(sinA, cosLP);

    *pcosLP = cosLP;
    *psinLP = sinLP;
    *pcosRP = cosRP;
    *psinRP = sinRP;
}


#if 0
FILE *g_file_cxm = NULL;
#ifndef BUILD_INTEGER
#define DBG_LOG_CHEX_MATRIX() { Int i;                                      \
        if( NULL == g_file_cxm ) g_file_cxm = fopen( "cxm.flt", "w" );      \
        for (i=0; i < NUM_CXMATELEMS; ++i ) {                               \
            fprintf( g_file_cxm, "%f\t", FLOAT_FROM_CX( pfParams[i] ) );  \
        }   fprintf( g_file_cxm, "\n" ); }
#else
#define DBG_LOG_CHEX_MATRIX() { Int i;                                       \
        if( NULL == g_file_cxm ) g_file_cxm = fopen( "cxm.int", "w" );      \
        for( i=0; i < NUM_CXMATELEMS; ++i ) {                               \
            fprintf( g_file_cxm, "%f\t", FLOAT_FROM_CX( pfParams[i] ) );  \
        }   fprintf( g_file_cxm, "\n" ); }
#endif
#else
#define DBG_LOG_CHEX_MATRIX()
#endif


Void computeLRParamsFromPowerMatrix(const Chex *pcx,
                                    const ReconTileInfo *prti,
                                    ChexType lScNorm,
                                    ChexType lrScNorm,
                                    ChexType lrScAng,
                                    ChexType *pfParams)
{
    Bool bCodeMono, bAngIsZero;
    const Int iBand = pcx->m_iBand;
    ChexType matrixSc=0;
    ChexType scMonoL, scMonoR, scDiffL, scDiffR;
    ChexType sinA, cosA;
    ChexType cosLPhase, sinLPhase, cosRPhase, sinRPhase;
    ChexType dSq;

    const CxAnchorReconTileInfo *pcxarti = prti->m_pcxartiSeg;

          ChexType lScNormF  = lScNorm;
    const ChexType lrScNormF = lrScNorm;
    const ChexType lrScAngF  = lrScAng;

    ChexType rScNormF;

    ASSERT_CX( lScNormF );

#if 0
    {
        static int cnt=0, cnt1=0, cntT=0;
        if (1==lScNorm && 0==lrScAng)
            cnt++;
        if (1==lScNorm)
            cnt1++;
        cntT++;
        printf("CC=%d %d %d\n", cnt, cnt1, cntT);
    }
#endif

    assert(WMAB_TRUE == pcx->m_bDoReverbAsPostProcess);

    //printf("M=%d PARAM=%f %f %f\n", prti->m_iStartPt, lScNorm, lrScNorm, lrScAng);
    //printf("%f %f %f %i\n", lScNorm, lrScNorm, lrScAng, prti->m_iStartPt );

    bCodeMono = pcxarti->m_iCodeMono[iBand];

    // if (1.0f == lScNormF && 0.0f == lrScAng && ...)
    if ( ( CX_ONE  == lScNormF ) &&
         ( CX_ZERO == lrScAngF ) &&
        bCodeMono &&
        ChexAdjustScaleExact == pcxarti->m_eAutoAdjustScale)
    {
        // fltDiffMonoL = sqrt(1 - lrScNorm*lrScNorm)/(1+lrScNorm)
        ChexType fltDiffMonoL = CX_ONE - CX_MUL(lrScNormF, lrScNormF);

        fltDiffMonoL = CX_SQRT(fltDiffMonoL);

        assert( 0 != CX_ONE + lrScNormF );
        fltDiffMonoL = CX_DIV(fltDiffMonoL, CX_ONE + lrScNormF );

        // in order for sqrt(1-lrScNorm*lrScNorm) to
        // be valid, abs( lrScNorm ) must be <= 1.0f.
        // also, lrScNorm is expected to be non-neg.

        assert( CX_ONE  >= lrScNormF );
        assert( CX_ZERO <= lrScNormF );

        // sqrt( 1-x*x ) / (1+x ) has range 1 to 0 on the
        // domain 0 to 1, so fltDiffMonoL is between 0 & 1.

        assert( CX_ONE  >= fltDiffMonoL );
        assert( CX_ZERO <= fltDiffMonoL );

        pfParams[e_CxScMonoRealL] = CX_ONE;
        pfParams[e_CxScMonoImagL] = CX_ZERO;
        pfParams[e_CxScMonoRealR] = CX_ONE;
        pfParams[e_CxScMonoImagR] = CX_ZERO;

        pfParams[e_CxScDiffMonoL] =  fltDiffMonoL;
        pfParams[e_CxScDiffMonoR] = -fltDiffMonoL;

        pfParams[e_CxScMonoAbsLSq] = CX_ONE;
        pfParams[e_CxScMonoAbsRSq] = CX_ONE;
        
        goto exit;
    }

    assert( 0 != lScNormF );

    rScNormF = CX_DIV( CX_ONE, lScNormF );

    assert( 0 < rScNormF );
    ASSERT_CX( rScNormF );
    ASSERT_CX( lScNormF );

    computeScaleFactorMtx(lScNormF, rScNormF, lrScNormF,
                          &scMonoL, &scDiffL,
                          &scMonoR, &scDiffR);

    if (lrScAng)
    {

#ifndef BUILD_INTEGER
        sinA = CX_FROM_FLOAT((Float)sin(FLOAT_FROM_CX(lrScAngF)));
        cosA = CX_FROM_FLOAT((Float)cos(FLOAT_FROM_CX(lrScAngF)));
#else

#define LUT_BITS 6
#define LUT_MAX (1<<LUT_BITS)

#define FRAC_BITS (CX_BITS-LUT_BITS)
#define FRAC_ONE  (1<<FRAC_BITS)
#define FRAC_MASK (FRAC_ONE-1)

        // sine / cosine lookup table. entries are U16 of the form:
        // LUT[i] = ( sin( x * pi/2 ) * (2^15) + 0.5 ) // for 0 <= x <= 1.

        const U16 g_sincos_LUT[ LUT_MAX+1 ] =
        {
            0x0000, 0x0324, 0x0648, 0x096b, 0x0c8c, 0x0fab, 0x12c8, 0x15e2,
            0x18f9, 0x1c0c, 0x1f1a, 0x2224, 0x2528, 0x2827, 0x2b1f, 0x2e11,
            0x30fc, 0x33df, 0x36ba, 0x398d, 0x3c57, 0x3f17, 0x41ce, 0x447b,
            0x471d, 0x49b4, 0x4c40, 0x4ec0, 0x5134, 0x539b, 0x55f6, 0x5843,
            0x5a82, 0x5cb4, 0x5ed7, 0x60ec, 0x62f2, 0x64e9, 0x66d0, 0x68a7,
            0x6a6e, 0x6c24, 0x6dca, 0x6f5f, 0x70e3, 0x7255, 0x73b6, 0x7505,
            0x7642, 0x776c, 0x7885, 0x798a, 0x7a7d, 0x7b5d, 0x7c2a, 0x7ce4,
            0x7d8a, 0x7e1e, 0x7e9d, 0x7f0a, 0x7f62, 0x7fa7, 0x7fd9, 0x7ff6,
            0x8000
        };

        const U32 iInvPi2 = 0x0000517d; // 2/pi * 2^15
        const I32 i2Pi    = 0x01921fb5; // 2*pi * 2^22


        Int angle  = lrScAngF % i2Pi;
        Int sign_s = 1;
        Int sign_c = 1;

        I32 sinA0;
        I32 cosA0;

        Int iIndex;
        Int iFrac;

        while( (i2Pi/2) <  angle ) angle -= i2Pi;
        while( (i2Pi/2) < -angle ) angle += i2Pi;

        // this should have (FRAC_BITS + LUT_BITS) resolution

        iIndex   = angle;                // start with CX ( 1.22 format )
        iIndex  += 1<<(CX_BITS+14-30);   // round
        iIndex >>=     CX_BITS+15-30;    // shift down    ( 1.15 format )
        iIndex  *= iInvPi2;              // mult. by 2/pi ( 1.30 format )
        iIndex >>= 30-CX_BITS;           // shift down    ( 1.22 format )

        if( 0 > iIndex )
        {
            iIndex = -iIndex;
            sign_s = -1;
        }

        if( (1<<CX_BITS) < iIndex )
        {
            iIndex = (2<<CX_BITS)-iIndex;
            sign_c = -1;
        }

        // mask off fractional bits,
        // and then shift them off.

        iFrac    = FRAC_MASK & iIndex;
        iIndex >>= FRAC_BITS;

        // look up sine & cosine values ( 1.15 format )

        sinA = g_sincos_LUT[        iIndex];
        cosA = g_sincos_LUT[LUT_MAX-iIndex];

        if( iFrac )
        {
            assert( LUT_MAX > iIndex );

            // if there is a fractional part,
            // interpolate between LUT entries

            sinA0 = g_sincos_LUT[        iIndex+1];
            cosA0 = g_sincos_LUT[LUT_MAX-iIndex-1];

            sinA *= FRAC_ONE - iFrac;
            cosA *= FRAC_ONE - iFrac;
            sinA +=  sinA0   * iFrac;
            cosA +=  cosA0   * iFrac;
        
            // currently in s.1.25 format, convert to CX

            sinA >>= 15 - LUT_BITS;
            cosA >>= 15 - LUT_BITS;
        }
        else
        {
            // currently in 1.15, convert to CX

            sinA <<= CX_BITS - 15;
            cosA <<= CX_BITS - 15;
        }

        // fix signs to place in correct quadrant

        sinA0 = sinA *= sign_s;
        cosA0 = cosA *= sign_c;

        //catchFP();
        //sinA0 = CX_FROM_FLOAT((Float)sin(FLOAT_FROM_CX(lrScAngF)));
        //cosA0 = CX_FROM_FLOAT((Float)cos(FLOAT_FROM_CX(lrScAngF)));
        //initFP();

        //printf( "%i\t%i\t%i\t%i\t%i\n", lrScAngF, sinA, sinA0, cosA, cosA0 );

#endif
        bAngIsZero = WMAB_FALSE;
    }
    else
    {
        sinA = CX_ZERO;
        cosA = CX_ONE;
        bAngIsZero = WMAB_TRUE;
    }

    dSq = lScNormF + rScNormF + 2*lrScNormF;
    // max = max(lScNorm) + 1 + 2

    assert( 0 < dSq );
    if (ChexAdjustScaleExact == pcxarti->m_eAutoAdjustScale)
    {
        // matrixSc = lScNormF + rScNormF + 2*(bCodeMono?1:-1)*lrScNormF*cosA;
        matrixSc = lScNormF + rScNormF;
        if (bCodeMono)
            matrixSc += 2 * CX_MUL(lrScNormF, cosA);
        else
            matrixSc -= 2 * CX_MUL(lrScNormF, cosA);

        if( matrixSc <= pcx->m_maxMatrixScaleThreshExact )
        {
            assert( CX_SQRT(dSq) );
            //matrixSc = pcx->m_maxMatrixScale/(Float)sqrt(dSq);
            matrixSc = CX_DIV(pcx->m_maxMatrixScale, CX_SQRT(dSq));
        }
        else
        {
            assert( CX_SQRT64(CX_MUL64(matrixSc, dSq)) );
            //matrixSc = 2.0f/(Float)sqrt(matrixSc*dSq);
            matrixSc = CX_DIV( 2 * CX_ONE,
                               CX_SQRT64(CX_MUL64(matrixSc, dSq)));
        }
    }
    else if (ChexAdjustScaleApprox == pcxarti->m_eAutoAdjustScale)
    {
        // matrixSc = eigVal[0] + eigVal[1];
        matrixSc = lScNormF + rScNormF;

        assert( dSq );

        // this requires encoder to do scaling to maintain proper power
        if( matrixSc <= pcx->m_maxMatrixScaleThreshApprox )
        {
            assert( CX_SQRT(dSq) );
            //matrixSc = pcx->m_maxMatrixScale/(Float)sqrt(dSq);
            matrixSc = CX_DIV(pcx->m_maxMatrixScale, CX_SQRT(dSq));
        }
        else if( 50*CX_ONE <= matrixSc )
        {
            assert( matrixSc + lrScNormF );
            // matrixSc = (Float)sqrt(2.0f)/(matrixSc
            matrixSc = CX_DIV( CX_SQRT2, matrixSc + lrScNormF );
        }
        else
        {
            assert( CX_MUL64(matrixSc, dSq) );
            //matrixSc = (Float)sqrt(2.0f/(matrixSc*dSq));
            matrixSc = CX_SQRT64(CX_DIV64( 2 * CX_ONE,
                                  CX_MUL64(matrixSc, dSq)));
        }
    }

    // Only real params
    // since the largest value for scDiffL = 1, and smallest for
    // scMonoL = 1/max, scDiffL/scMonoL is capped by max, so there
    // is no chance of overflow
    // fltL = checkRange(fltL, -CX_MAX, CX_MAX);
    // fltR = checkRange(fltR, -CX_MAX, CX_MAX);

    assert( scMonoL );
    assert( scMonoR );

    ASSERT_CX(CX_DIV64(scDiffL, scMonoL));
    ASSERT_CX(CX_DIV64(scDiffR, scMonoR));

    pfParams[e_CxScDiffMonoL] = CX_DIV( scDiffL, scMonoL );
    pfParams[e_CxScDiffMonoR] = CX_DIV( scDiffR, scMonoR );

    if (ChexAdjustScaleExact == pcxarti->m_eAutoAdjustScale ||
        ChexAdjustScaleApprox == pcxarti->m_eAutoAdjustScale)
    {
        // scMonoL *= matrixSc;
        scMonoL = CX_MUL(scMonoL, matrixSc);
        // scMonoR *= matrixSc;
        scMonoR = CX_MUL(scMonoR, matrixSc);
    }

#if (CX_DCT_ONLY==1)
    bAngIsZero = WMAB_TRUE; // set it after scaling, so scaling is correct
#endif

    if (bAngIsZero)
    {
        // Have not seen scMonoL/scMonoR go negative.  Do they ever ? -- no

        ASSERT_CX( CX_MUL64(scMonoL, scMonoL) );
        ASSERT_CX( CX_MUL64(scMonoR, scMonoR) );

        pfParams[e_CxScMonoAbsLSq] = CX_MUL( scMonoL, scMonoL );
        pfParams[e_CxScMonoAbsRSq] = CX_MUL( scMonoR, scMonoR );
        
        if( 0 <= lScNormF + ( bCodeMono ? lrScNormF : -lrScNormF ) )
        {
            pfParams[e_CxScMonoRealL] = scMonoL;
            pfParams[e_CxScMonoRealR] = scMonoR;
        }
        else // Have not seen this get hit.  Does it ever? Yes, if bCodeMono=0
        {
            pfParams[e_CxScMonoRealL] = -scMonoL;
            pfParams[e_CxScMonoRealR] = -scMonoR;
        }

        pfParams[e_CxScMonoImagL] = CX_ZERO;
        pfParams[e_CxScMonoImagR] = CX_ZERO;
    }
    else
    {
        ChexType scMonoRealL, scMonoImagL;
        ChexType scMonoRealR, scMonoImagR;

        computePhaseMtx( lScNormF, lrScNormF,
                         sinA, cosA, bCodeMono,
                         &cosLPhase, &sinLPhase, &cosRPhase, &sinRPhase );

        scMonoRealL = CX_MUL(scMonoL, cosLPhase);
        scMonoImagL = CX_MUL(scMonoL, sinLPhase);
        scMonoRealR = CX_MUL(scMonoR, cosRPhase);
        scMonoImagR = CX_MUL(scMonoR, sinRPhase);

        ASSERT_CX( CX_MUL64(scMonoRealL, scMonoRealL) +
                    CX_MUL64(scMonoImagL, scMonoImagL) );
        ASSERT_CX( CX_MUL64(scMonoRealR, scMonoRealR) +
                    CX_MUL64(scMonoImagR, scMonoImagR) );

        pfParams[e_CxScMonoRealL]  = scMonoRealL;
        pfParams[e_CxScMonoImagL]  = scMonoImagL;
        pfParams[e_CxScMonoRealR]  = scMonoRealR;
        pfParams[e_CxScMonoImagR]  = scMonoImagR;

        pfParams[e_CxScMonoAbsLSq] = 
                CX_MUL(scMonoRealL, scMonoRealL) +
                CX_MUL(scMonoImagL, scMonoImagL);

        pfParams[e_CxScMonoAbsRSq] =
                CX_MUL(scMonoRealR, scMonoRealR) +
                CX_MUL(scMonoImagR, scMonoImagR);
    }

    // Bug #13320. diffs in chex. scale matrix rgrgScMat has extremely small values in 
    // float bits, which correspond to 0 in int bits. threshold the value at the minimum 
    // int precision of ChexType (1 << CX_BITS). Hui Gao. 10/13/2006
#ifndef BUILD_INTEGER
    {
        Int i;
        for (i = e_CxScMonoRealL; i <= e_CxScMonoAbsRSq; i++)
        {
            Float fParamAbs = ABS(pfParams[i]);
            if (fParamAbs != 0.0f && fParamAbs*(1<<CX_BITS) <= 1)
            {
                pfParams[i] = 0.0f;
            }
        }
    }
#endif // BUILD_INTEGER

exit:

    DBG_LOG_CHEX_MATRIX();

    return;
}

//#define TEST_LRPARAM

#if defined(TEST_LRPARAM)
// code to test function computeLRParamsFromPowerMatrix -- useful for making
// sure everything is working correctly
Void chexTestLRParamsFromPowerMatrix(CAudioObject *pau, FILE *fp)
{
#define LSCMAX    (3.0)
#define LSCINCR   (0.1)
#define LRSCINCR  (0.1)
#define LRANGINCR (PI/8.0)

    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    Double lSc, lScLog, lrSc, lrAng;
    ChexType lScF, lrScF, lrAngF;
    Bool bCodeMono, bScale;
    ReconTileInfo *prti = prp->m_rgchextiBuf + prp->m_iBufReconPos;
    Int i;
    Int iLSc, iLRSc, iLRAng;
    ChexType rgfParams[NUM_CXMATELEMS];
    const Int iBand = pcx->m_iBand;
    Int cnt=0;
    FILE_DUMP_INIT(lrparams);

    for (lScLog=-LSCMAX, iLSc=0;
         lScLog <= LSCMAX+0.0000001f;
         lScLog += LSCINCR, iLSc++)
    {
        lSc = pow(10.0, lScLog);
        for (lrSc = 1.0f, iLRSc=0;
             lrSc >= 0.0f-0.0000001f;
             lrSc -= LRSCINCR, iLRSc++)
        {
            for (lrAng = -PI, iLRAng=0;
                 lrAng <= PI;
                 lrAng += LRANGINCR, iLRAng++)
            {
                for (bCodeMono=0; bCodeMono <= 1; bCodeMono++)
                {
                    for (bScale=0; bScale <= 1; bScale++)
                    {
                        printf("%d\r", cnt++);
                        if (cnt == 749)
                            printf("");
                        if (iLSc==3 && iLRSc==9 && iLRAng==4 &&
                            bCodeMono==1 && bScale==1)
                            printf("");
                        prti->m_pcxartiSeg->m_iCodeMono[iBand] = bCodeMono;
                        prti->m_pcxartiSeg->m_eAutoAdjustScale =
                            (bScale ?
                             ChexAdjustScaleExact : ChexAdjustScaleApprox);
#if defined(BUILD_INTEGER)
                        lSc = checkRange(lSc,
                                         FLOAT_FROM_CX(CX_MINM4), 
                                         FLOAT_FROM_CX(CX_MAXM4));
#endif
                        lScF   = CX_FROM_FLOAT((Float)lSc);
                        lrScF  = CX_FROM_FLOAT((Float)lrSc);
                        lrAngF = CX_FROM_FLOAT((Float)lrAng);
                        computeLRParamsFromPowerMatrix(pcx, prti,
                                                       lScF, lrScF, lrAngF,
                                                       rgfParams);
                        rgfParams[e_CxScDiffRealL] =
                            (ChexType)CX_MUL(rgfParams[e_CxScMonoRealL],
                                              rgfParams[e_CxScDiffMonoL]);
                        rgfParams[e_CxScDiffImagL] =
                            (ChexType)CX_MUL(rgfParams[e_CxScMonoImagL],
                                              rgfParams[e_CxScDiffMonoL]);
                        rgfParams[e_CxScDiffRealR] =
                            (ChexType)CX_MUL(rgfParams[e_CxScMonoRealR],
                                              rgfParams[e_CxScDiffMonoR]);
                        rgfParams[e_CxScDiffImagR] =
                            (ChexType)CX_MUL(rgfParams[e_CxScMonoImagR],
                                              rgfParams[e_CxScDiffMonoR]);
                        fprintf(fp, "%f %f %f %d %d\n",
                                lSc, lrSc, lrAng, bCodeMono, bScale);
                        fprintf(fp, "%d %d %d %d %d\n",
                                iLSc, iLRSc, iLRAng, bCodeMono, bScale);
                        for (i=0; i < 8; i++)
                            fprintf(fp, "%f\n", FLOAT_FROM_CX(rgfParams[i]));
                        fprintf(fp, "\n");
                    }
                }
            }
        }
    }

    exit(0);

#undef LSCMAX
#undef LSCINCR
#undef LRSCINCR
#undef LRANGINCR
}
#endif // #if (0)

Void computeLRParamsFromPowerMatrixLMRM(const Chex *pcx,
                                        const ReconTileInfo *prti,
                                        ChexType lmScale,
                                        ChexType rmScale,
                                        ChexType lrRIRatio,
                                        ChexType *pfParams)
{
    ChexType lScNorm;
    Float lrScReal, lrScImag;
    Float lrScNorm, lrScAng;
    Int bCodeMono = prti->m_pcxartiSeg->m_iCodeMono[pcx->m_iBand];
    
    if (rmScale != 0)
        lScNorm =
          CX_FROM_FLOAT(checkRange(FLOAT_FROM_CX(lmScale)/
                                      FLOAT_FROM_CX(rmScale),
                                      FLOAT_FROM_CX(CX_MINM4),
                                      FLOAT_FROM_CX(CX_MAXM4)));
    else
        lScNorm = CX_FROM_FLOAT(1.0f);

    // (1-(lm^2)/4-(rm^2)/4)/(lm*rm/2)
    // = (4-lm*lm-rm*rm)/(2*lm*rm)
    if (lmScale != 0 && rmScale != 0)
        lrScReal = (4-
                    FLOAT_FROM_CX(lmScale)*FLOAT_FROM_CX(lmScale)-
                    FLOAT_FROM_CX(rmScale)*FLOAT_FROM_CX(rmScale))/
                 (2*FLOAT_FROM_CX(lmScale)*FLOAT_FROM_CX(rmScale));
    else
        lrScReal = 1.0;
    if (WMAB_FALSE == bCodeMono)
        lrScReal = -lrScReal;
    lrScImag = FLOAT_FROM_CX(lrRIRatio);

    lrScNorm = (Float)sqrt(lrScReal*lrScReal + lrScImag*lrScImag);
    //printf("LL=%f\n", lrScNorm);
    lrScNorm = min(lrScNorm, 1.0f);
    lrScAng = (Float)atan2(lrScImag, lrScReal);

    computeLRParamsFromPowerMatrix(pcx, prti,
                                   lScNorm,
                                   CX_FROM_FLOAT(lrScNorm),
                                   CX_FROM_FLOAT(lrScAng),
                                   pfParams);
}

// =======================================================================

// starting with nBands, get to nBandsFinal (starting with sorted array)
Int chexIncreaseBands(Int *piBandSizes, Int nBands, Int nBandsFinal)
{
    Int iNewLoc, iNewSize1, iNewSize2, i;

    while (nBands < nBandsFinal)
    {
        iNewSize1 = (Int)piBandSizes[nBands-1]/2;
        iNewSize2 = ((Int)piBandSizes[nBands-1]+1)/2;
        iNewLoc = nBands-2;
        while (iNewLoc >= 0 &&
               iNewSize2 <= piBandSizes[iNewLoc])
            iNewLoc--;
        assert(-1 == iNewLoc || piBandSizes[iNewLoc] <= iNewSize1);
        // new sizes go at iNewLoc+1 & iNewLoc+2, so shift
        // everything from iNewLoc+1 to nBands-2 by 2 to the right
        nBands++;
        for (i=nBands-3; i >= iNewLoc+1; i--)
            piBandSizes[i+2] = piBandSizes[i];
        piBandSizes[iNewLoc+1] = iNewSize1;
        piBandSizes[iNewLoc+2] = iNewSize2;
    }

    return nBands;
}

// starting with nBands, get to nBandsFinal (starting with sorted array)
Int chexReduceBands(Int *piBandSizes, Int nBands, Int nBandsFinal)
{
    Int iNewLoc, iNewSize, i;

    while (nBands > nBandsFinal)
    {
        iNewSize = (Int)piBandSizes[0]+(Int)piBandSizes[1]; // add two smallest
        iNewLoc = 0;
        nBands--;
        while (iNewLoc+2 < nBands &&
               iNewSize >= piBandSizes[iNewLoc+2])
            iNewLoc++;
        for (i=0; i < iNewLoc-1; i++)
            piBandSizes[i] = piBandSizes[i+2];
        piBandSizes[i] = iNewSize;
        i++;
        for (; i < nBands; i++)
            piBandSizes[i] = piBandSizes[i+1];
    }

    return nBands;
}

Int chexSetBands(Int *piBandSizes, Int nBands, Int nBandsFinal)
{
    if (nBands < nBandsFinal)
        nBands = chexIncreaseBands(piBandSizes, nBands, nBandsFinal);
    else
        nBands = chexReduceBands(piBandSizes, nBands, nBandsFinal);

    assert(nBands == nBandsFinal);

    return nBands;
}

Void chexSetBandSizes(Int *rgiBandSizes, Int cBands,
                      Int iSizeCurr, Int iTotal)
{
    Int i, iStart, iEnd, iNewTotal;

    iStart = 0;
    iEnd = 0;
    iNewTotal = 0;
    for (i=0; i < cBands; i++)
    {
        iEnd += rgiBandSizes[i];
        rgiBandSizes[i] = (iEnd-iStart)*iSizeCurr/iTotal;
        iNewTotal += rgiBandSizes[i];
        iStart += rgiBandSizes[i]*iTotal/iSizeCurr;
    }
    assert(iNewTotal == iSizeCurr);
}

Void chexSetTileParamsFromGlobalParam(Chex *pcx,
                                      CxAnchorReconTileInfo *pcxarti)
{
    pcxarti->m_iStartBand = pcx->m_iStartBand;
    pcxarti->m_cBands = pcx->m_cBands;
    pcxarti->m_iNumBandIndex  = pcx->m_iNumBandIndex;
    pcxarti->m_iBandMultIndex = pcx->m_iBandMultIndex;

    pcxarti->m_eAutoAdjustScale = pcx->m_eAutoAdjustScale;
    pcxarti->m_eFilterTapOutput = pcx->m_eFilterTapOutput;
    pcxarti->m_eCxChCoding      = pcx->m_eCxChCoding;

    pcxarti->m_iStartBand = min(pcxarti->m_iStartBand,
                                pcx->m_piCxBands[pcxarti->m_iNumBandIndex]-1);
}

WMARESULT chexInitTileConfig(Chex *pcx, ReconTileInfo *prti, Bool bUseSeg,
                             Int iSizeCurr)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = pcx->m_pau;
    ReconProc *prp = pau->m_prp;
    Int i, iTotal;
    Int iStart, cBands, iNumBandIndex, iBandMultIndex;
    CxAnchorReconTileInfo *pcxarti = NULL;
    CxAnchorReconTileInfo *pcxartiSeg = NULL;

    if (prti)
    {
        if (bUseSeg)
            pcxarti = prti->m_pcxartiSeg;
        else
            pcxarti = prti->m_pcxartiCode;
        if (iSizeCurr <= 0)
            iSizeCurr = prti->m_iSizeCurr;
        pcxartiSeg = prti->m_pcxartiSeg;
    }
    else
    {
        if (iSizeCurr <= 0)
            iSizeCurr = pau->m_cFrameSampleHalf / prp->m_iNTilesPerFrameBasic;
    }

    if (pcxarti)
    {
        pcxarti->m_cBands = pcx->m_piCxBands[pcxarti->m_iNumBandIndex];
        cBands = pcxarti->m_cBands;
        iBandMultIndex = pcxarti->m_iBandMultIndex;
        iNumBandIndex = pcxarti->m_iNumBandIndex;
    }
    else
    {
        pcx->m_cBands = pcx->m_piCxBands[pcx->m_iNumBandIndex];
        cBands = pcx->m_cBands;
        iBandMultIndex = pcx->m_iBandMultIndex;
        iNumBandIndex = pcx->m_iNumBandIndex;
    }

    if (cBands > pcx->m_cMaxBands)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    
    pcx->m_piBandConfig =
        pcx->m_iChexBandSizesM[iNumBandIndex][iBandMultIndex];
    pcx->m_iNumBandsInConfig = pcx->m_piChexBandMultMSize[iNumBandIndex];

    // set bands to band multipliers
    iTotal = 0;
    for (i=0; i < pcx->m_iNumBandsInConfig; i++)
    {
        pcx->m_rgiBandSizes[i] = pcx->m_piBandConfig[i];
        iTotal += (Int)pcx->m_rgiBandSizes[i];
    }

    // adjust to correct number of bands by combining/splitting
    chexSetBands(pcx->m_rgiBandSizes, pcx->m_iNumBandsInConfig, cBands);

    // adjust band configuration for current tile size
    if (iSizeCurr != iTotal)
        chexSetBandSizes(pcx->m_rgiBandSizes, cBands, iSizeCurr, (Int)iTotal);

    iStart = 0;
    for (i=0; i < cBands; i++)
    {
        pcx->m_rgiBandStart[i] = iStart;
        iStart += (Int)pcx->m_rgiBandSizes[i];
    }

    if (pcxartiSeg)
        pcx->m_cStart = pcx->m_rgiBandStart[pcxartiSeg->m_iStartBand];
    else
        pcx->m_cStart = pcx->m_rgiBandStart[pcx->m_iStartBand];

    pcx->m_cEnd = iSizeCurr;

exit:
    return wmaResult;
}

ChexType chexComputeInterpRatio(Chex *pcx,
                                   ReconTileInfo *prti,
                                   ReconTileInfo *prtiNext)
{
    Int iNum, iDen;
    CxAnchorReconTileInfo *pcxarti = prti->m_pcxartiCode;
    CxAnchorReconTileInfo *pcxartiNext = prtiNext->m_pcxartiCode;

    if (NULL == pcxarti)
    {
        pcxarti = prti->m_pcxartiSeg;
        assert(pcxarti == pcxartiNext);
    }

    iNum = 2*(prti->m_iTilesInCoding-1);
    if (pcxarti->m_bEvenLengthCxSegment)
        iNum++;
    iDen = 2*pcx->m_prtiLastCodedTileInSeg->m_iTilesInCoding;
    if (pcxarti->m_bEvenLengthCxSegment)
        iDen++;
    if (pcxartiNext->m_bEvenLengthCxSegment)
        iDen--;

    assert( 0 != iDen );
    return CX_FROM_IDIV(iNum, iDen);
}


#if 0
FILE *g_file_cxp = NULL;
#ifndef BUILD_INTEGER
#define DBG_LOG_CHEX_PARAMS() {                                             \
        if( NULL == g_file_cxp ) g_file_cxp= fopen( "cxp.flt", "w" );       \
        fprintf( g_file_cxp, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n",                \
            scaleL, scaleLNext, scaleLR, scaleLRNext, angLR, angLRNext, ratio ); }
#else
#define DBG_LOG_CHEX_PARAMS() { float f0, f1, f2, f3, f4, f5, f6;           \
        if( NULL == g_file_cxp ) g_file_cxp = fopen( "cxp.flt", "r" );      \
        fscanf( g_file_cxp, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n",                 \
        &f0, &f1, &f2, &f3, &f4, &f5, &f6 ); }
/*                           \
        scaleL      =   CX_FROM_FLOAT( f0 );                             \
        scaleLNext  =   CX_FROM_FLOAT( f1 );                             \
        scaleLR     = CX_FROM_FLOAT( f2 );                             \
        scaleLRNext = CX_FROM_FLOAT( f3 );                             \
        angLR       = CX_FROM_FLOAT( f4 );                             \    
        angLRNext   = CX_FROM_FLOAT( f5 );                             \
        ratio       = CX_FROM_FLOAT( f6 ); }
*/
#endif
#else
#define DBG_LOG_CHEX_PARAMS()
#endif



Void chexComputeLRScMat(CAudioObject *pau, ReconTileInfo *prti,
                        ChexType ratio, Int iBandPrev, Int iBandNext)
{
    Chex *pcx = pau->m_pcx;
    Int iBand = pcx->m_iBand;
    ReconTileInfo *prtiNext;
    ChexType scaleL, scaleLNext;
    ChexType scaleLR, angLR, scaleLRNext, angLRNext;
    CxAnchorReconTileInfo *pcxartiCode = prti->m_pcxartiCode;
    CxAnchorReconTileInfo *pcxartiCodeNext;

    prtiNext = pcx->m_prtiNextCodedTile;
    pcxartiCodeNext = prtiNext->m_pcxartiCode;

    if (NULL == pcxartiCode)
    {
        scaleL  = pcxartiCodeNext->m_lScNorm[iBandNext];
        scaleLR = pcxartiCodeNext->m_lrScNorm[iBandNext];
        angLR   = pcxartiCodeNext->m_lrScAng[iBandNext];
    }
    else
    {
        scaleL  = pcxartiCode->m_lScNorm[iBandPrev];
        scaleLR = pcxartiCode->m_lrScNorm[iBandPrev];
        angLR   = pcxartiCode->m_lrScAng[iBandPrev];
    }
    scaleLNext  = pcxartiCodeNext->m_lScNorm[iBandNext];
    scaleLRNext = pcxartiCodeNext->m_lrScNorm[iBandNext];
    angLRNext   = pcxartiCodeNext->m_lrScAng[iBandNext];

    // unwrap the phase for interpolation

    assert(ABS(angLRNext-angLR) < CX_FROM_FLOAT(2*(Float)PI));
    if (angLRNext-angLR > CX_FROM_FLOAT((Float)PI))
        angLR += CX_FROM_FLOAT(2*(Float)PI);
    if (angLR-angLRNext > CX_FROM_FLOAT((Float)PI))
        angLRNext += CX_FROM_FLOAT(2*(Float)PI);
    assert(ABS(angLRNext-angLR) <= CX_FROM_FLOAT((Float)PI+0.0001f));

    //printf("M=PREV=%f %f %f ", scaleL, scaleLR, angLR);

    DBG_LOG_CHEX_PARAMS();

    scaleL  += CX_MUL( ratio, scaleLNext  - scaleL  );
    scaleLR += CX_MUL( ratio, scaleLRNext - scaleLR );
    angLR   += CX_MUL( ratio, angLRNext   - angLR   );

    //printf("%d %d %d CURR=%f %f %f\n", prti->m_iStartPt, iBand, prti->m_iSizeCurr, scaleL, scaleLR, angLR);
    //printf("NEXT=%f %f %f\n", scaleLNext, scaleLRNext, angLRNext);

    computeLRParamsFromPowerMatrix(pcx, prti, scaleL, scaleLR, angLR,
                                   pcx->m_rgrgScMat[iBand]);

#if defined(TEST_LRPARAM)
    chexTestLRParamsFromPowerMatrix(pau, NULL);
#endif
}

Void chexComputeLRScMatLMRM(CAudioObject *pau, ReconTileInfo *prti,
                            ChexType ratio, Int iBandPrev, Int iBandNext)
{
    Chex *pcx = pau->m_pcx;
    Int iBand = pcx->m_iBand;
    ReconTileInfo *prtiNext;
    ChexType scLM, scRM, lrRI, scLMNext, scRMNext, lrRINext;
    CxAnchorReconTileInfo *pcxartiCode = prti->m_pcxartiCode;
    CxAnchorReconTileInfo *pcxartiCodeNext;

    prtiNext = pcx->m_prtiNextCodedTile;
    pcxartiCodeNext = prtiNext->m_pcxartiCode;

    if (NULL == pcxartiCode)
    {
        scLM = pcxartiCodeNext->m_lmSc[iBandNext];
        scRM = pcxartiCodeNext->m_rmSc[iBandNext];
        lrRI = pcxartiCodeNext->m_lrScAng[iBandNext];
    }
    else
    {
        scLM = pcxartiCode->m_lmSc[iBandPrev];
        scRM = pcxartiCode->m_rmSc[iBandPrev];
        lrRI = pcxartiCode->m_lrScAng[iBandPrev];
    }
    scLMNext = pcxartiCodeNext->m_lmSc[iBandNext];
    scRMNext = pcxartiCodeNext->m_rmSc[iBandNext];
    lrRINext = pcxartiCodeNext->m_lrScAng[iBandNext];

    //printf("M=PREV=%f %f %f ", scLM, scRM, lrRI);

    scLM += CX_MUL( ratio, scLMNext - scLM );
    scRM += CX_MUL( ratio, scRMNext - scRM );
    lrRI += CX_MUL( ratio, lrRINext - lrRI );

    //printf("CURR=%f %f %f NEXT=%f %f %f\n",
    //       scLM, scRM, lrRI, scLMNext, scRMNext, lrRINext);

    computeLRParamsFromPowerMatrixLMRM(pcx, prti, scLM, scRM, lrRI,
                                       pcx->m_rgrgScMat[iBand]);
}

#ifndef BUILD_INTEGER
Float
#else
I64
#endif
chexComputeBandSc( const CoefType *pCoef, Int iLen, Int iSizeCurr )
{
    const CoefType *pMDCT = pCoef;
    const CoefType *pMDST = pCoef + iSizeCurr;
    Int i = 0;

#ifndef BUILD_INTEGER

    Float fScale = 0;

#if (CX_DCT_ONLY==1)
    for (i=0; i < iLen; i++)
        fScale += pMDCT[i]*(Float)pMDCT[i];
#else
    for (i=0; i < iLen; i++)
        fScale += pMDCT[i]*(Float)pMDCT[i] 
               +  pMDST[i]*(Float)pMDST[i];
#endif

    assert( 0 <= fScale );

    return fScale;

#else // BUILD_INTEGER

    I64 accum = 0;
    const U8 shift = (U8)( iLen ? (LOG2(iLen)) : 0 );

    if( 0 == iLen ) return 0;


#if 1 //!defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM 
    for( i = 0; i < iLen; ++i )
    {
        ChexType coef;
        
        coef = (ChexType)( pMDCT[i] );
        accum += ( coef * (I64)coef );
#if (CX_DCT_ONLY!=1)
        coef = (ChexType)( pMDST[i] );
        accum += ( coef * (I64)coef );
#endif
        assert( 0 <= accum );
    }
#else   // !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM 
    chexComputeBandSc_loop(pMDCT, iLen, &accum);
#if (CX_DCT_ONLY!=1)
    accum <<= 1;
#endif
#endif  // !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM 

    return accum;

#endif
}


// set DBG_ADJ_SCALE_FAC to zero for debugging.
// this forces the floating-point and fixed-point
// code to use a scale factor of 1.0f instead of
// rescaling the reverb filter output.

#define DBG_ADJ_SCALE_FAC 1


INLINE ChexType chexComputeAdjustFactor(CAudioObject *pau,
                                 const CoefType *pCoef,
                                 Int iLen, Int iSizeCurr,
                                 ChexType matrixMonoScaleSq )
{
    const Chex *pcx = pau->m_pcx;
    const Int iBand = pcx->m_iBand;

#ifndef BUILD_INTEGER
    Float revRMS, scale;
#else
    I64 revRMS, scale;
#endif

    ChexType scaleAdjustment;

    revRMS = chexComputeBandSc(pCoef, iLen, iSizeCurr );
    scale  = pcx->m_rgMonoSc[iBand];

    assert( 0 <= revRMS );
    assert( 0 <=  scale );

    assert( 0 <= matrixMonoScaleSq );
    assert( 0 <= pcx->m_adjustScaleThreshSq );

#ifndef BUILD_INTEGER

    scale = (ChexType)CX_MUL( (ChexType)scale, pcx->m_adjustScaleThreshSq );
    scale = (ChexType)CX_MUL( (ChexType)scale, matrixMonoScaleSq );

#else

    while( (((I64)1)<<32) < scale )
    {
        scale  >>= 4;
        revRMS >>= 4;
    }

    scale *= pcx->m_adjustScaleThreshSq; scale >>= CX_BITS;
    scale *= matrixMonoScaleSq;          scale >>= CX_BITS;

    assert( scale >= 0 );

    while( I32_MAX < scale || I32_MAX < revRMS )
    {
        scale  >>= 4;
        revRMS >>= 4;
    }
#endif

    if( DBG_ADJ_SCALE_FAC &&    // use scale factor adjustment ( skip for debug )
        revRMS >  scale   &&    // if revRMS <= scale, no contraction is needed
        revRMS >  0       &&    // if revRMS is <= 0, the reverb is too small.
        scale  >= 0 )           // scales may be < 0 for corrupt bitstreams
    {
        scaleAdjustment = CX_DIV ( (ChexType)scale, (ChexType)revRMS );
        scaleAdjustment = CX_SQRT( scaleAdjustment );
    }
    else
    {
        scaleAdjustment = CX_ONE;
    }

    return scaleAdjustment;
}

#ifndef CX_DECODE_MONO
#   error  CX_DECODE_MONO is undefined! Define it to be either 0 or 1.
#elif  (CX_DECODE_MONO==0)
#   define CHEX_RECON_STARTBAND(prti) prti->m_pcxartiSeg->m_iStartBand
#   define CHEX_RECON_START(pcx) pcx->m_cStart
#else
#   define CHEX_RECON_STARTBAND(prti) 0
#   define CHEX_RECON_START(pcx) 0
#endif

Void chexReconMonoDiffScales( CAudioObject *pau,
                           ReconTileInfo *prti,
                           Int iCh,
                           const CoefType *pCoefSrc,
                           Bool bMono )
{
    Chex *pcx = pau->m_pcx;
    const Int iSizeCurr = prti->m_iSizeCurr;
    const Int cBands = prti->m_pcxartiSeg->m_cBands;
    const Int iStartBand = CHEX_RECON_STARTBAND(prti);

    ChexType scaleR, scaleI;

    ChexType *pScaleR = pcx->m_rgReconBandScales;
    ChexType *pScaleI = pScaleR + iSizeCurr;

    CxScale cxscA, cxscB;

    Int iBand, j;

    if (0 == iCh)
    {
        if (bMono)
        {
            cxscA = e_CxScMonoRealL;
            cxscB = e_CxScMonoImagL;
        }
        else if (WMAB_FALSE == pcx->m_bDoReverbAsPostProcess)
        {
            cxscA = e_CxScDiffRealL;
            cxscB = e_CxScDiffImagL;
        }
        else // diff and reverb as post process
        {
            cxscA = e_CxScDiffMonoL;
            cxscB = e_CxScMonoAbsLSq;
        }
    }
    else
    {
        if (bMono)
        {
            cxscA = e_CxScMonoRealR;
            cxscB = e_CxScMonoImagR;
        }
        else if (WMAB_FALSE == pcx->m_bDoReverbAsPostProcess)
        {
            cxscA = e_CxScDiffRealR;
            cxscB = e_CxScDiffImagR;
        }
        else // diff and reverb as post process
        {
            cxscA = e_CxScDiffMonoR;
            cxscB = e_CxScMonoAbsRSq;
        }
    }

    if( bMono || !pcx->m_bDoReverbAsPostProcess )
    {
        for( iBand = iStartBand; iBand < cBands; ++iBand )
        {
            scaleR = pcx->m_rgrgScMat[ iBand ][ cxscA ];
            scaleI = pcx->m_rgrgScMat[ iBand ][ cxscB ];

            for( j = pcx->m_rgiBandSizes[ iBand ]; j-- > 0; )
            {
                *(pScaleR++) = scaleR;
                *(pScaleI++) = scaleI;
            }
        }
    }
    else // diff and reverb as post process
    {
        for( iBand = iStartBand; iBand < cBands; ++iBand )
        {
            ChexType ctAdjust;
            Int iBandSize = (Int)pcx->m_rgiBandSizes[ iBand ];
            pcx->m_iBand = (Int)iBand;

            ctAdjust = chexComputeAdjustFactor(pau, pCoefSrc, iBandSize,
                         iSizeCurr, pcx->m_rgrgScMat[ iBand ][ cxscB ]);

            scaleR = (ChexType)CX_MUL( pcx->m_rgrgScMat[ iBand ][ cxscA ], ctAdjust );

            for( j = iBandSize; j-- > 0; )
                *(pScaleR++) = scaleR;

            pCoefSrc += iBandSize;
        }
    }
}

Void chexReconMonoDiff(CAudioObject *pau,
                        ReconTileInfo *prti,
                        Int iCh,
                        const CoefType *pCoefSrc,
                        CoefType *pCoefDst,
                        Bool bMono )
{
    const Chex *pcx = pau->m_pcx;
    const Int iSizeCurr = prti->m_iSizeCurr;

    const CoefType *pMDCTSrc = pCoefSrc;
    const CoefType *pMDSTSrc = pCoefSrc + iSizeCurr;
          CoefType *pMDCTDst = pCoefDst;
          CoefType *pMDSTDst = pCoefDst + iSizeCurr;

    ChexType *pScaleR = pcx->m_rgReconBandScales;
    ChexType *pScaleI = pScaleR + iSizeCurr;

    const Int cBands = prti->m_pcxartiSeg->m_cBands;
    const Int iStartBand = CHEX_RECON_STARTBAND(prti);

#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
    Int i;
#endif
    Int nFreqs = 0, iBand;

    chexReconMonoDiffScales( pau, prti, iCh, pCoefSrc, bMono );

    for( iBand = iStartBand; iBand < cBands; ++iBand )
    {
        nFreqs += (Int)pcx->m_rgiBandSizes[ iBand ];
    }

    // (a+jb)*(c+jd) = (ac-bd) + j*(bc+ad)
    if (bMono)
    { 
#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
        for( i = 0; i < nFreqs; ++i )
        {
            // !! need to integerize.
            const CoefType dct = pMDCTSrc[i];
            const CoefType dst = pMDSTSrc[i];
            const ChexType scR = pScaleR [i];
            const ChexType scI = pScaleI [i];
 
            pMDCTDst[i] = COEF_MUL_CXSC( dct, scR )
                        - COEF_MUL_CXSC( dst, scI );
            pMDSTDst[i] = COEF_MUL_CXSC( dst, scR )
                        + COEF_MUL_CXSC( dct, scI );
        }
#else   // WMA_OPT_CHEXPRO_ARM
        chexReconMonoDiff_loop1(pScaleR, pScaleI, pMDCTSrc, pMDSTSrc, iSizeCurr, nFreqs);
#endif  // WMA_OPT_CHEXPRO_ARM
    }
    else if (WMAB_FALSE == pcx->m_bDoReverbAsPostProcess)
    {
#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
        for( i = 0; i < nFreqs; ++i )
        {
            // !! need to integerize.
            const CoefType dct = pMDCTSrc[i];
            const CoefType dst = pMDSTSrc[i];
            const ChexType scR = pScaleR [i];
            const ChexType scI = pScaleI [i];

            pMDCTDst[i] += COEF_MUL_CXSC( dct, scR )
                         - COEF_MUL_CXSC( dst, scI );
            pMDSTDst[i] += COEF_MUL_CXSC( dst, scR )
                         + COEF_MUL_CXSC( dct, scI );
        }
#else   // WMA_OPT_CHEXPRO_ARM
        chexReconMonoDiff_loop2(pScaleR, pScaleI, pMDCTSrc, pMDSTSrc, iSizeCurr, nFreqs);
#endif  // WMA_OPT_CHEXPRO_ARM
    }
    else
    {
#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
        for( i = 0; i < nFreqs; ++i )
        {
            // !! need to integerize.
            const CoefType dct = pMDCTSrc[i];
            const CoefType dst = pMDSTSrc[i];
            const ChexType scR = pScaleR [i];

            pMDCTDst[i] += COEF_MUL_CXSC( dct, scR );
            pMDSTDst[i] += COEF_MUL_CXSC( dst, scR );
        }
#else   // WMA_OPT_CHEXPRO_ARM
        chexReconMonoDiff_loop3(pScaleR, pMDCTSrc, pMDSTSrc, iSizeCurr, nFreqs);
#endif  // WMA_OPT_CHEXPRO_ARM
    }
}

Void chexReconMonoDiffDCTOnly(CAudioObject *pau,
                              ReconTileInfo *prti,
                              Int iCh,
                              const CoefType * pMDCTSrc,
                                    CoefType * pMDCTDst,
                              Bool bMono)
{
    Chex *pcx = pau->m_pcx;
    Int iBand, i, j, iOffset, cxsc;
    const Int cBands = prti->m_pcxartiSeg->m_cBands;
    const Int iStartBand = CHEX_RECON_STARTBAND(prti);
    ChexType scale;

    assert(WMAB_TRUE == pcx->m_bDoReverbAsPostProcess);

    if (0 == iCh)
        cxsc = bMono ? e_CxScMonoRealL : e_CxScDiffMonoL;
    else
        cxsc = bMono ? e_CxScMonoRealR : e_CxScDiffMonoR;

    if (bMono)
    {
        i = 0;
        for (iBand=iStartBand; iBand < cBands; iBand++)
        {       
            scale = pcx->m_rgrgScMat[iBand][cxsc];
#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
            for (j=0; j < pcx->m_rgiBandSizes[iBand]; j++, i++) 
                pMDCTDst[i] = COEF_MUL_CXSC(pMDCTSrc[i], scale);
#else
            if (pcx->m_rgiBandSizes[iBand] < 16) {
                for (j=0; j < pcx->m_rgiBandSizes[iBand]; j++, i++) 
                    pMDCTDst[i] = COEF_MUL_CXSC(pMDCTSrc[i], scale);
            } else {
                CoefMulCxscArray(&pMDCTSrc[i], &pMDCTDst[i], scale, pcx->m_rgiBandSizes[iBand]);
                i += pcx->m_rgiBandSizes[iBand];
            }
#endif
        }
    }
    else
    {
        Int cxCh = (0==iCh) ? e_CxScMonoAbsLSq : e_CxScMonoAbsRSq;

        i = 0;
        iOffset = 0;
        for (iBand=iStartBand; iBand < cBands; iBand++)
        {
            ChexType ctAdjust;
            pcx->m_iBand = iBand;
            ctAdjust =
                chexComputeAdjustFactor(pau, pMDCTSrc + iOffset,
                                        pcx->m_rgiBandSizes[iBand],
                                        prti->m_iSizeCurr,
                                        pcx->m_rgrgScMat[iBand][cxCh]);

            scale = (ChexType)CX_MUL( pcx->m_rgrgScMat[iBand][cxsc], ctAdjust );

#if !defined(WMA_OPT_CHEXPRO_ARM) || !WMA_OPT_CHEXPRO_ARM
            for (j=0; j < pcx->m_rgiBandSizes[iBand]; j++, i++) 
                pMDCTDst[i] += COEF_MUL_CXSC(pMDCTSrc[i], scale);
#else
            if (pcx->m_rgiBandSizes[iBand] < 16) {
                for (j=0; j < pcx->m_rgiBandSizes[iBand]; j++, i++) 
                    pMDCTDst[i] += COEF_MUL_CXSC(pMDCTSrc[i], scale);
            } else {
                CoefMulAddCxscArray(&pMDCTSrc[i], &pMDCTDst[i], scale, pcx->m_rgiBandSizes[iBand]);
                i += pcx->m_rgiBandSizes[iBand];
            }
#endif
            iOffset += pcx->m_rgiBandSizes[iBand];
        }
    }
}

#if defined(BUILD_INT_FLOAT) && !defined(WMA_DISABLE_SSE1)

#include <xmmintrin.h>

Void chexReconMonoDiff_SSE1(CAudioObject *pau,
                           ReconTileInfo *prti,
                           Int iCh,
                           const CoefType * pCoefSrc,
                                 CoefType * pCoefDst,
                           Bool bMono )
{
    const Chex *pcx = pau->m_pcx;
    const Int iSizeCurr = prti->m_iSizeCurr;

    const Float * const pMDCTSrc = pCoefSrc;
    const Float * const pMDSTSrc = pCoefSrc + iSizeCurr;
          Float * const pMDCTDst = pCoefDst;
          Float * const pMDSTDst = pCoefDst + iSizeCurr;

    const Int cBands = prti->m_pcxartiSeg->m_cBands;
    const Int iStartBand = CHEX_RECON_STARTBAND(prti);

    Float * const pScaleR = pcx->m_rgReconBandScales;
    Float * const pScaleI = pScaleR + iSizeCurr;

    Int i, nFreqs = 0, iBand;

    chexReconMonoDiffScales( pau, prti, iCh, pCoefSrc, bMono );

    for( iBand = iStartBand; iBand < cBands; ++iBand )
    {
        nFreqs += pcx->m_rgiBandSizes[ iBand ];
    }

    // check pointer alignment

    assert( 0 == (size_t)pScaleR  % 16 );
    assert( 0 == (size_t)pScaleI  % 16 );
    assert( 0 == (size_t)pMDCTSrc % 16 );
    assert( 0 == (size_t)pMDSTSrc % 16 );
    assert( 0 == (size_t)pMDCTDst % 16 );
    assert( 0 == (size_t)pMDSTDst % 16 );

    // make sure we are doing a multiple of 4 freqencies.

    assert( 0 == nFreqs % 4 );

    // (a+jb)*(c+jd) = (ac-bd) + j*(bc+ad)
    if (bMono)
    {
        for( i = 0; i < nFreqs; i += 4 )
        {
            const __m128 dct  = _mm_load_ps( pMDCTSrc + i );
            const __m128 dst  = _mm_load_ps( pMDSTSrc + i );
            const __m128 scR  = _mm_load_ps( pScaleR  + i );
            const __m128 scI  = _mm_load_ps( pScaleI  + i );

            const __m128 outR = _mm_sub_ps(
                                _mm_mul_ps( scR, dct ),
                                _mm_mul_ps( scI, dst ) );

            const __m128 outI = _mm_add_ps(
                                _mm_mul_ps( scR, dst ),
                                _mm_mul_ps( scI, dct ) );

            _mm_store_ps( pMDCTDst + i, outR );
            _mm_store_ps( pMDSTDst + i, outI );
        }
    }
    else if (WMAB_FALSE == pcx->m_bDoReverbAsPostProcess)
    {
        for( i = 0; i < nFreqs; i += 4 )
        {
            const __m128 dct  = _mm_load_ps( pMDCTSrc + i );
            const __m128 dst  = _mm_load_ps( pMDSTSrc + i );
            const __m128 scR  = _mm_load_ps( pScaleR  + i );
            const __m128 scI  = _mm_load_ps( pScaleI  + i );

            __m128 outR = _mm_load_ps( pMDCTDst + i );
            __m128 outI = _mm_load_ps( pMDSTDst + i );
            
            outR = _mm_add_ps( outR, _mm_mul_ps( scR, dct ) );
            outR = _mm_sub_ps( outR, _mm_mul_ps( scI, dst ) );

            outI = _mm_add_ps( outI, _mm_mul_ps( scR, dst ) );
            outI = _mm_add_ps( outI, _mm_mul_ps( scI, dct ) );

            _mm_store_ps( pMDCTDst + i, outR );
            _mm_store_ps( pMDSTDst + i, outI );
        }
    }
    else
    {
        for( i = 0; i < nFreqs; i += 4 )
        {
            const __m128 dct  = _mm_load_ps( pMDCTSrc + i );
            const __m128 dst  = _mm_load_ps( pMDSTSrc + i );
            const __m128 scR  = _mm_load_ps( pScaleR  + i );

            __m128 outR = _mm_load_ps( pMDCTDst + i );
            __m128 outI = _mm_load_ps( pMDSTDst + i );

            outR = _mm_add_ps( outR, _mm_mul_ps( scR, dct ) );
            outI = _mm_add_ps( outI, _mm_mul_ps( scR, dst ) );

            _mm_store_ps( pMDCTDst + i, outR );
            _mm_store_ps( pMDSTDst + i, outI );
        }
    } 
}

#endif // BUILD_INT_FLOAT && !WMA_DISABLE_SSE1

// prti is coded tile, set the current tile segment
WMARESULT chexSetTileSegmentParameters(CAudioObject *pau, ReconTileInfo *prtiOrig)
{
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = pau->m_pcx;
    ReconProc *prp = pau->m_prp;
    Int iTilesBefore, iTilesAfter, iTile, iTiles, iTileLast;
    Int iPos;
    ReconTileInfo *prti;
    CxAnchorReconTileInfo *pcxartiSegOrig = prtiOrig->m_pcxartiSeg;

    // find the beginning of the parameter segment
    iTilesBefore = prtiOrig->m_iTileCnt - pcx->m_prtiSegStart->m_iTileCnt;
    iTilesAfter = iTilesBefore;
    if (pcxartiSegOrig->m_bEvenLengthCxSegment)
        iTilesAfter--;
    iTiles = iTilesBefore+iTilesAfter+1;

    iPos = reconProcBufPos(prp, pcx->m_prtiSegStart, 0);
    prti = prp->m_rgchextiBuf + iPos;
    for (iTile=0, iTileLast=0; iTile < iTiles; iTile++)
    {
        if (prti && chexInfoStatAdd(prti->m_uInfoStat))
        {
            if (prti != prtiOrig)
            {
                if ((prti->m_pcxartiSeg != pcxartiSegOrig) && (NULL != prti->m_pcxartiSeg))
                {
                    // Prevent assert in the call to chexSetSegAnchor below...
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                }
                chexSetSegAnchor(prti, pcxartiSegOrig);
            }
            if (iTile < iTilesBefore && pcx->m_bNoInterpFromPrev)
                chexReleaseCxCodeAnchor(prti);

            iTileLast++;
        }

        if (prti)
            prti = chexNextTile(prp, prti);
        iPos = chexOffsetBuf(prp, iPos, 1);
    }
    pcx->m_iTilesRemInSegment = iTiles-iTileLast;

    // iPos now points to next available tile
    //pcx->m_prtiSegStart = chexOffsetTile(prp, pcx->m_prtiSegStart, iTiles);
    pcx->m_prtiSegStart = prp->m_rgchextiBuf + iPos;
exit:
    return wmaResult;
}

#if defined(CHEX_VERIFY) || 0
#define DUMP_CHEXBUFS
#endif

#ifdef DUMP_CHEXBUFS
Void chexDumpBuf(CoefType *pBuf, Int iSize, FILE **fp, LPCSTR pName)
{
    if (NULL == *fp)
        *fp = fopen(pName, "wb");
    fwrite(pBuf, iSize, sizeof(CoefType), *fp);
}

Void prvDumpVals(LPCSTR pName, LPCSTR type, I32 iSize, F32 *rgVal)
{
    FILE *fp = fopen(pName, type);

    fwrite(&iSize, sizeof(I32), 1, fp);
    fwrite(rgVal, sizeof(F32), iSize, fp);
    fflush(fp);

    fclose(fp);
}
#else // DUMP_CHEXBUFS
#define chexDumpBuf(a,b,c,d)
#define prvDumpVals(a,b,c,d)
#endif

Void cxReverbDumpOutput(CxReverbFilter *pcxrf, CoefType *pData, Int iSize,
                        FILE *fp);

INLINE
Bool chexIsSameBandConfig(CxAnchorReconTileInfo *pcxarti0,
                          CxAnchorReconTileInfo *pcxarti1)
{
    return (pcxarti0->m_iNumBandIndex == pcxarti1->m_iNumBandIndex &&
            pcxarti0->m_iBandMultIndex == pcxarti1->m_iBandMultIndex);
}

// find band in src closest to 'iBand' band in dest
INLINE
Void chexMapBandConfig(const Int iMidFreq,
                       Int *rgSrcBands, Int cSrcBands,
                       Int *piTotal, Int *piBandMap)
{
    while (*piTotal <= iMidFreq && *piBandMap < (cSrcBands-1))
    {
        *piBandMap += 1;
        *piTotal += rgSrcBands[*piBandMap];
    }
}

WMARESULT chexReconCh(CAudioObject *pau,
                      ReconTileInfo *prti, 
                      const Int iCh,
                      CoefType *pCoeff, 
                      CoefType *pCoeffDiff)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    CoefType *pBuf;
    CoefType *pBufDst;
    Int iBand;
    const Int iSizeCurr = prti->m_iSizeCurr;
    Int cBands, iStartBand;
    Int cBandsInterp=0, iStartBandInterp;
    Bool bIsSameBandConfig = WMAB_TRUE;
    Bool bFirstHalfOfSeg, bCodeLMRMInterp;
    CxReverbFilter *pcxrf = pcx->m_pcxrf;
    CxAnchorReconTileInfo *pcxartiSegSave = prti->m_pcxartiSeg;
    ChexType ratio;
    Void *pfnSave = NULL;

    pfnSave = pau->cxpfnReconMonoDiff;

    if (pcx->m_bNoNextCodedTile)
        prti->m_pcxartiSeg = prti->m_pcxartiCode;

    assert(pcx->m_prtiNextCodedTile);
    if (pcx->m_prtiNextCodedTile->m_pcxartiSeg !=
        pcx->m_prtiNextCodedTile->m_pcxartiCode)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    if (prti->m_pcxartiSeg == NULL)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    cBands = prti->m_pcxartiSeg->m_cBands;
    iStartBand = CHEX_RECON_STARTBAND(prti);

    if (prti->m_pcxartiCode)
        bIsSameBandConfig =
            chexIsSameBandConfig(prti->m_pcxartiCode,
                                 pcx->m_prtiNextCodedTile->m_pcxartiCode);

    bFirstHalfOfSeg = (prti->m_pcxartiCode != prti->m_pcxartiSeg);
    if (prti->m_pcxartiSeg != pcx->m_prtiNextCodedTile->m_pcxartiSeg &&
           WMAB_FALSE != bFirstHalfOfSeg)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    if (WMAB_FALSE == bIsSameBandConfig)
    {
        if (bFirstHalfOfSeg)
        {
            // previous tile configuration, use prti->m_pcxartiCode
            // interp holds previous config
            TRACEWMA_EXIT(wmaResult, 
                          chexInitTileConfig(pcx, prti, WMAB_FALSE, iSizeCurr));
            cBandsInterp = prti->m_pcxartiCode->m_cBands;
        }
        else
        {
            // next coded tile configuration, interp holds next
            TRACEWMA_EXIT(wmaResult, 
                chexInitTileConfig(pcx, pcx->m_prtiNextCodedTile, WMAB_FALSE,
                                   iSizeCurr));
            cBandsInterp = pcx->m_prtiNextCodedTile->m_pcxartiSeg->m_cBands;
        }
        memcpy(pcx->m_rgiBandSizesInterp, pcx->m_rgiBandSizes,
               cBandsInterp*sizeof(Int));
    }

    if (bFirstHalfOfSeg && prti->m_pcxartiCode)
    {
        bCodeLMRMInterp = prti->m_pcxartiCode->m_bCodeLMRM;
        iStartBandInterp = prti->m_pcxartiCode->m_iStartBand;
    }
    else
    {
        bCodeLMRMInterp = pcx->m_prtiNextCodedTile->m_pcxartiSeg->m_bCodeLMRM;
        iStartBandInterp = pcx->m_prtiNextCodedTile->m_pcxartiSeg->m_iStartBand;
    }
    // cx params sent for all bands, even if not used
    iStartBandInterp = 0;

    TRACEWMA_EXIT(wmaResult, chexInitTileConfig(pcx, prti, WMAB_TRUE, 0)); // current

    //if (0 == iCh) printf("RST = %d\n", prti->m_iStartPt);

    if (0 == iCh)
    {
        if (pcx->m_prtiLastCodedTileInSeg == NULL)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        ratio = chexComputeInterpRatio(pcx, prti, pcx->m_prtiNextCodedTile);
        if (pcx->m_bNoNextCodedTile)
            ratio = CX_FROM_FLOAT(0.0f);
        // compute the 2x2 matrix
        pBuf = pCoeff + CHEX_RECON_START(pcx);
        pcx->m_cStartIndex = CHEX_RECON_START(pcx);
        for (iBand=iStartBand; iBand < cBands; iBand++)
        {
            Bool bNoInterp = WMAB_FALSE;
            Int iBandPrev, iBandNext;
            Int iBandMap=-1, iTotal=0, iMidFreq;
            ChexType bandRatio;

            pcx->m_iBand = iBand;

            if (WMAB_TRUE == bIsSameBandConfig)
            {
                iBandPrev = iBand;
                iBandNext = iBand;
            }
            else
            {
                iMidFreq = pcx->m_cStartIndex+(pcx->m_rgiBandSizes[iBand]>>1);
                chexMapBandConfig(iMidFreq,
                                  pcx->m_rgiBandSizesInterp, cBandsInterp,
                                  &iTotal, &iBandMap);
                if (bFirstHalfOfSeg)
                {
                    iBandPrev = iBandMap;
                    iBandNext = iBand;
                }
                else
                {
                    iBandPrev = iBand;
                    iBandNext = iBandMap;
                }
                if (iBandMap < iStartBandInterp)
                    bNoInterp = WMAB_TRUE;
            }

            bandRatio = ratio;

            if (iBand < iStartBandInterp)
                bNoInterp = WMAB_TRUE;

            if (bCodeLMRMInterp != prti->m_pcxartiSeg->m_bCodeLMRM)
                bNoInterp = WMAB_TRUE;
            
            if (bNoInterp)
                bandRatio = bFirstHalfOfSeg ?
                  CX_FROM_FLOAT(1.0f) : CX_FROM_FLOAT(0.0f);

            if (prti->m_pcxartiSeg->m_bCodeLMRM)
                chexComputeLRScMatLMRM(pau, prti, bandRatio,
                                       iBandPrev, iBandNext);
            else
                chexComputeLRScMat(pau, prti, bandRatio,
                                   iBandPrev, iBandNext);

            pcx->m_rgMonoSc[iBand] =
                chexComputeBandSc(pBuf, pcx->m_rgiBandSizes[iBand], iSizeCurr );

            if (pcx->m_rgMonoSc[iBand] < 0)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }

            pcx->m_cStartIndex += pcx->m_rgiBandSizes[iBand];
            pBuf += pcx->m_rgiBandSizes[iBand];
        }
    }

    // filter the data
    //if (0==iCh) cxReverbDumpHistBuf(pcxrf, 0, 0, NULL);
    (pau->cxpfnReverbFilter)(pcxrf, iCh);
    //if (0==iCh) cxReverbDumpHistBuf(pcxrf, 0, 1, NULL);

    // get the new output
    cxReverbGetOutput(pcxrf, pCoeffDiff, pCoeffDiff+iSizeCurr,
                      iSizeCurr, iCh,
                      prti->m_pcxartiSeg->m_eFilterTapOutput);
    //if (0==iCh) cxReverbDumpOutput(pcxrf, pCoeffDiff, iSizeCurr, NULL);

#if defined(BUILD_INT_FLOAT) && !defined(WMA_DISABLE_SSE1)
    if (CHEX_RECON_START(pcx) % 4 != 0 &&
        pau->cxpfnReconMonoDiff == chexReconMonoDiff_SSE1)
    {
        pau->cxpfnReconMonoDiff = chexReconMonoDiff;
    }
#endif

#if (CX_DCT_ONLY==1)
    pau->cxpfnReconMonoDiff = chexReconMonoDiffDCTOnly;
#endif

    // recon from mono
    pBuf = pCoeff + CHEX_RECON_START(pcx);
    (pau->cxpfnReconMonoDiff)(pau, prti, iCh, pBuf, pBuf, WMAB_TRUE);

    // add new input to filter
    cxReverbAddInput(pcxrf, pCoeff, pCoeff+iSizeCurr, iSizeCurr, iCh);

    // recon the reverb
    pBuf = pCoeffDiff + CHEX_RECON_START(pcx);
    pBufDst = pCoeff + CHEX_RECON_START(pcx);
    pcx->m_cStartIndex = CHEX_RECON_START(pcx);
    (pau->cxpfnReconMonoDiff)(pau, prti, iCh, pBuf, pBufDst, WMAB_FALSE);

    prti->m_pcxartiSeg = pcxartiSegSave;

    pau->cxpfnReconMonoDiff = pfnSave;

exit:
    return wmaResult;
}

// Optimized version. memset was used first, but they are not actually necessary. 
Void chexClearFexParams(Fex *pfx, ReconTileInfo *prti)
{
    CAudioObject    *pau = pfx->m_pau;
    PerChannelRecon *ppcr;
    Int iCh, iBand;
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;

    prfxrti->m_cFexScaleBands = 0;
    prfxrti->m_cFexMvBands = 0;
    prfxrti->m_cFexBaseBands = 0;
    prfxrti->m_cFexStart = 0;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        if (!(prti->m_uChannelMask & (1<<iCh)))
            continue;

        ppcr = prfxrti->m_rgpcr + iCh;

#ifdef BUILD_WMAPROLBRV2
        if (pau->m_bEncoder)
        {
            for (iBand = 0; iBand < pfx->m_cMaxBands; iBand++)
                ppcr->m_rgiFexLogScaleFacIndex[iBand] = g_fexScaleIntpl;
        }
        else
        {
            ppcr->m_rgiFexLogScaleFacIndex = NULL;
        }
#endif
        ppcr->m_iFexScaleFacPred = FexScaleFacNo;
    }
}

WMARESULT chexReconReconFex(CAudioObject *pau, PerChannelInfo *ppcinfo,
                            Int iChSrc,
                            ReconTileInfo *prti, CoefType *pCoeff,
                            CoefType *pfLowband,
                            CoefType *pfTempBuf)
{
    Fex *pfx = &(pau->m_fex);
    I16        cSubFrameSampleHalfSaved;
    WMARESULT  wmaResult = WMA_OK;
    Int iFexCh;
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;

    // Decode recon fex here -- during processing
    if (pau->m_prp->m_pfnDecodeReconFexTile)
    {
        assert(!pau->m_bFirstPlusFrameAfterReset);
        assert(!pau->m_bFirstPlusFrameAfterSuperframe);

        TRACEWMA_EXIT(wmaResult, freqexSwitchFexDomain(pau, WMAB_TRUE));
        TRACEWMA_EXIT(wmaResult,
                      pau->m_prp->m_pfnDecodeReconFexTile(pau, prti, iChSrc));

        if(pfx->m_iVersion > 2)
        {
            if (chexInfoStatNoFx(prti->m_uInfoStat))
            {
                // no fex
                prfxrti->m_cFexScaleBands = prfxrti->m_cFexMvBands = 0;
                prfxrti->m_cFexStart = prti->m_iSizeCurr;
                prfxrti->m_rgpcr[iChSrc].m_iFexScaleFacPred = FexScaleFacNo;
            }
            if (!chexInfoStatCodeBs(prti->m_uInfoStat))
            {
                // no base-scaling
                prfxrti->m_cFexBaseBands = 0;
            }
        }
    }

    iFexCh = chexGetFexChannel(pau, iChSrc);

    if ( prfxrti->m_cFexStart > prti->m_iSizeCurr || 
         iFexCh < 0 )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    
    if (iChSrc != iFexCh)
    {
#if (CX_DCT_ONLY==0)
        CoefType *pSrc = pau->m_rgpcinfo[iFexCh].m_ppcinfoShr->m_pDCTBufNext;
#else
        CoefType *pSrc = pau->m_rgpcinfo[iFexCh].m_ppcinfoShr->m_pDCTBufCurr;
#endif
        assert(pau->m_bCx);
        memcpy(pCoeff+prfxrti->m_cFexStart, pSrc+prfxrti->m_cFexStart,
               (prti->m_iSizeCurr - prfxrti->m_cFexStart) * sizeof(CoefType));
        goto exit;
    }

    if ( iChSrc >= pfx->m_iAllocCh )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    // save orignal parameters and set to local
    cSubFrameSampleHalfSaved = ppcinfo->m_cSubFrameSampleHalf;
    ppcinfo->m_cSubFrameSampleHalf = (I16)prti->m_iSizeCurr;

#ifdef BUILD_WMAPROLBRV2
    // transfer recon fex params

    freqexSetCommonTilePtrs(pau, prti);
    freqexRestoreCommonTileParams(pau, prti);
    freqexSetPerChTilePtrs(pau, prti, ppcinfo, iChSrc);
    freqexRestorePerChTileParams(pau, prti, ppcinfo, iChSrc);
#endif

#ifdef BUILD_WMAPROLBRV3
    // prepare for base-scale + rfx
    memcpy(pfTempBuf, pCoeff, prti->m_iSizeCurr * sizeof(CoefType));
    pfx->m_pfBaseRfx = pfTempBuf;
#endif

    // set baseband coefs
    if (!pau->m_bIgnoreFreqex)
        memset(pCoeff + prfxrti->m_cFexStart, 0,
               (prti->m_iSizeCurr - prfxrti->m_cFexStart) * sizeof(CoefType));

    // call fex recon
    pfx->m_prtiCurr = prti;
    pfx->m_pfLowband = pfLowband;
    pfx->m_pfRecon = pCoeff;
    pfx->m_bReconDomain = WMAB_TRUE;
    pfx->m_cTileSize = prti->m_iSizeCurr;

    TRACEWMA_EXIT(wmaResult, freqexRecon(pau, ppcinfo, iChSrc, FFLT_ONE ));
#ifdef BUILD_WMAPROLBRV2
    freqexResetCommonTileParams(pau, prti);
#endif

    // retrieve original params
    pfx->m_bReconDomain = WMAB_FALSE;
    ppcinfo->m_cSubFrameSampleHalf = cSubFrameSampleHalfSaved;

exit:
    return wmaResult;
}

Void chexCopyParams(Chex *pcx,
                    ReconTileInfo *prtiCurr, ReconTileInfo *prtiPrev)
{
    CAudioObject *pau = pcx->m_pau;
    ReconProc *prp = pau->m_prp;

    if (chexInfoStatNoCx(prtiPrev->m_uInfoStat) ||
        NULL == prtiPrev ||
        pcx->m_bNoInterpFromPrev)
    {
        chexReleaseCxCodeAnchor(prtiCurr);
    }
    else
    {
        chexSetCodeAnchor(prtiCurr, prtiPrev->m_pcxartiCode);
    }

    if (0 != pcx->m_iTilesRemInSegment && !prtiCurr->m_pcxartiSeg)
    {
        assert(!pau->m_bEncoder);
        chexSetSegAnchor(prtiCurr, prtiPrev->m_pcxartiSeg);
        pcx->m_iTilesRemInSegment--;
    }

    if (!prtiPrev || pcx->m_bNoNextCodedTile)
        prtiCurr->m_iTilesInCoding = 1;
    else
        prtiCurr->m_iTilesInCoding = prtiPrev->m_iTilesInCoding + 1;
}

// =====================================================================

// following functions add a chex tile into the tile buffer, basically
// its start and size

Void chexAddPair(U32 uChannelMask, U32 *rguGroup,
                 Int *piGrp, Int iPos0, Int iPos1)
{
    if ((uChannelMask & iPos0) && (uChannelMask & iPos1))
    {
        rguGroup[*piGrp] = iPos0 | iPos1;
        *piGrp = *piGrp + 1;
    }
    else if (uChannelMask & iPos0)
    {
        rguGroup[*piGrp] = iPos0;
        *piGrp = *piGrp + 1;
    }
    else if (uChannelMask & iPos1)
    {
        rguGroup[*piGrp] = iPos1;
        *piGrp = *piGrp + 1;
    }
}

Void chexAddSingle(U32 uChannelMask, U32 *rguGroup,
                   Int *piGrp, Int iPos)
{
    if (uChannelMask & iPos)
    {
        rguGroup[*piGrp] = iPos;
        *piGrp = *piGrp + 1;
    }
}

U32 auMaskToWMAMask(U32 uTotalChannelMask, U32 uChannelMask,
                    Int cChannels)
{
    U32 uNewMask;
    Int i, iCh;

    uNewMask = 0;
    iCh = 0;
    for (i=0; i < 32; i++)
    {
        if (uChannelMask & (1<<i))
            uNewMask |= (1<<iCh);
        if (uTotalChannelMask & (1<<i))
            iCh++;
        if (iCh == cChannels)
            break;
    }

    return uNewMask;
}

Int chexSetChGroups(CAudioObject *pau, U32 *rguGroupCh)
{
    Int iGrp, iCh, i;
    U32 uChannelMask = pau->m_nChannelMask;
    U32 uTotalMask;

    iGrp = 0;
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_FRONT_LEFT, SPEAKER_FRONT_RIGHT);
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_FRONT_CENTER, SPEAKER_BACK_CENTER);
    chexAddSingle(uChannelMask, rguGroupCh, &iGrp,
                  SPEAKER_LOW_FREQUENCY);
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_BACK_LEFT, SPEAKER_BACK_RIGHT);
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_FRONT_LEFT_OF_CENTER, SPEAKER_FRONT_RIGHT_OF_CENTER);
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_SIDE_LEFT, SPEAKER_SIDE_RIGHT);
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_TOP_FRONT_LEFT, SPEAKER_TOP_FRONT_RIGHT);
    chexAddPair(uChannelMask, rguGroupCh, &iGrp,
                SPEAKER_TOP_BACK_LEFT, SPEAKER_TOP_BACK_RIGHT);

    uTotalMask = 0;
    for (i=0; i < iGrp; i++)
        uTotalMask |= rguGroupCh[i];

    for (iCh=0; iCh < 32; iCh++)
    {
        if ((uChannelMask & (1<<iCh)) && !(uTotalMask & (1<<iCh)))
        {
            chexAddSingle(uChannelMask, rguGroupCh, &iGrp, iCh);
            uTotalMask |= rguGroupCh[iGrp-1];
        }
    }

    assert(uChannelMask == uTotalMask);

    for (i=0; i < iGrp; i++)
        rguGroupCh[i] = auMaskToWMAMask(uChannelMask, rguGroupCh[i],
                                        pau->m_cChannel);

    return iGrp;
}

WMARESULT chexCopyFex(CAudioObject *pau, Int iCh)
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &pau->m_fex;
    Chex *pcx = pau->m_pcx;
    Int i, iBand;

    if (WMAB_TRUE == pfx->m_bReconDomain)
        goto exit;

    // after recon copy fex from channel iCh into all chex channels
    for (i=0; i < pau->m_cChannel; i++)
    {
        if (0 == (pcx->m_rguFexChannel[iCh] & (1<<i)))
            continue;

        if (i == iCh)
            continue;

        if (pau->m_rgpcinfo[i].m_bNoDecodeForCx)
            continue;

        if (pau->m_rgpcinfo[iCh].m_iSizeCurr < pfx->m_cOrigStart)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        memcpy(pau->m_rgpcinfo[i].m_rgCoefRecon + pfx->m_cOrigStart,
               pau->m_rgpcinfo[iCh].m_rgCoefRecon + pfx->m_cOrigStart,
               (pau->m_rgpcinfo[iCh].m_iSizeCurr - pfx->m_cOrigStart)*
               sizeof(CoefType));

        for (iBand=0; iBand < pfx->m_cHoleBands; iBand++)
            memcpy(pau->m_rgpcinfo[i].m_rgCoefRecon + pfx->m_rgiBandStart[iBand],
                   pau->m_rgpcinfo[iCh].m_rgCoefRecon + pfx->m_rgiBandStart[iBand],
                   pfx->m_piScaleBandSizes[iBand]*sizeof(CoefType));
    }
exit:
    return wmaResult;
}

// =========================================================================

Void chexInitPcInfo(CAudioObject *pau, PerChannelInfo *ppcinfo, Int iCh)
{
    ReconProc *prp = pau->m_prp;

    ppcinfo->m_rgCoefHistMCLT = pau->m_rgCoefHistMCLT +
        RECONPROC_HIST_SIZE*iCh;

    ppcinfo->m_rgPCMBuf = ppcinfo->m_rgCoefReconBase;
}

Void chexInitPcInfoShr(CAudioObject *pau, PerChannelInfo *ppcinfo, Int iCh)
{
    ReconProc *prp = pau->m_prp;
    PerChannelInfoShr *ppcinfoShr = ppcinfo->m_ppcinfoShr;

    ppcinfoShr->m_pDCTBufCurr =
        pau->m_rgDCTBuf + prp->m_cFrameSampleHalfChex*iCh*2;
#if (CX_DCT_ONLY==0)
    ppcinfoShr->m_pDCTBufNext =
        ppcinfoShr->m_pDCTBufCurr + prp->m_cFrameSampleHalfChex;

    ppcinfoShr->m_pIDCTBufPrev =
        pau->m_rgDCTBuf + prp->m_cFrameSampleHalfChex*pau->m_cChannel*2 +
        prp->m_cFrameSampleHalfChex*iCh*3;
    ppcinfoShr->m_pIDCTBufCurr =
        ppcinfoShr->m_pIDCTBufPrev + prp->m_cFrameSampleHalfChex;
    ppcinfoShr->m_pIDCTBufNext =
        ppcinfoShr->m_pIDCTBufCurr + prp->m_cFrameSampleHalfChex;
#endif
}

Int chexGetLastTileNextSize(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;
    if (ReconProcTileSplitBasic == prp->m_iTileSplitType)
        return pau->m_cFrameSampleHalf/prp->m_iNTilesPerFrameBasic;
    else
        return pau->m_cFrameSampleHalf;
}

Void chexClearReverbHistory(CAudioObject *pau)
{
    if (pau->m_bCx)
    {
        Chex *pcx = pau->m_pcx;
        if (pcx)
        {
            CxReverbFilter *pcxrf = pcx->m_pcxrf;
            if (pcxrf && pcxrf->m_rgpHistBuf)
#if ( 1 == CX_SMALL_REVERB )
                memset(pcxrf->m_rgpHistBuf[0][0][0], 0,
                       pcxrf->m_nTotalHistSize*sizeof(CoefType));
#else // so ( 0 == CX_SMALL_REVERB )
                memset(pcxrf->m_rgpHistBuf[0][0], 0,
                       2*CXREVERB_HIST_LEN*pcxrf->m_iNumFreq*
                       pcxrf->m_iNumChannel*sizeof(CoefType));
#endif // CX_SMALL_REVERB
        }

        pcx->m_iTilesRemInSegment = 0;

        memset(pcx->m_rgiMaxStartBandForFrame, 0,
               NUM_CX_MAXBANDDEP*sizeof(Int));
        pcx->m_iMaxStartBandIndex = 0;
        pcx->m_iMaxStartBandCurr = 0;
    }
}

Void chexReset(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;
    Int i, iEnd;

    // Reconstruction starts at 1/2 into previous frame -- for decoder
    // first frame starts at -pau->m_cFrameSampleHalf/2
    // previous frame is initialized to have size pau->m_cFrameSampleHalf
    // by setting in encoder\encinit.c function prvInitPcInfoENC
    // by setting in decoder\msaudiodec.c function audecReset
    // m_rgiSubFrameSize[-1] = pau->m_cFrameSampleHalf
    // thus starting pcm sample is -pau->m_cFrameSampleHalf
    // encoder has extra silence (undcoded frame of size cFrameSampleHalf)
    for (i=0; i < pau->m_cChannel; i++)
    {
        if (pau->m_bEncoder)
            prp->m_rgiPCMEndReconPoint[i] = -2*pau->m_cFrameSampleHalf;
        else
            prp->m_rgiPCMEndReconPoint[i] = -pau->m_cFrameSampleHalf;
        prp->m_rgiPCMSamplesReady[i] = 0;

        iEnd = prp->m_rgiPCMEndReconPoint[i] + pau->m_cFrameSampleHalf/2;
        prp->m_rgiPCMStart[i] = iEnd - prp->m_iPCMPrevFrameSave;

        if (pau->m_rgpcinfo)
            pau->m_rgpcinfo[i].m_fHistIsMCLT = WMAB_FALSE;
    }

    // although encoder has extra silent frame at start, we skip tiles
    // for these
    prp->m_iStartPt = -pau->m_cFrameSampleHalf/2;
    prp->m_iEndPt = 0; // will be recalc on every addition of tile
    for (i=0; i < prp->m_nTilesInBuf; i++)
    {
        prp->m_rgchextiBuf[i].m_iStartPt = prp->m_iStartPt;
        prp->m_rgchextiBuf[i].m_iSizePrev = chexGetLastTileNextSize(pau);
        prp->m_rgchextiBuf[i].m_iSizeCurr = 0;
        prp->m_rgchextiBuf[i].m_iSizeNext = 0;
        prp->m_rgchextiBuf[i].m_iTileCnt = 0;
        prp->m_rgchextiBuf[i].m_pcxartiCode = NULL;
        prp->m_rgchextiBuf[i].m_pcxartiSeg = NULL;
        prp->m_rgchextiBuf[i].m_prfxrti = NULL;
        prp->m_rgchextiBuf[i].m_iStart = 0;
        prp->m_rgchextiBuf[i].m_iEnd = 0;
        chexSetTileNotInUse(prp, prp->m_rgchextiBuf+i);
    }
    prp->m_iEndOutPt = prp->m_iStartPt;

    prp->m_iRecon = prp->m_rgiPCMStart[0];

#if defined(_DEBUG)
    for (i=0; i < prp->m_nrfxrti; i++)
        prp->m_rgrfxrti[i].m_prti = NULL;
#endif

    for (i=0; i < prp->m_ncxarti; i++)
        prp->m_rgcxarti[i].m_iRefCount = 0;

    prp->m_icxarti = 0;

    prp->m_bFirstTile = WMAB_TRUE;
    prp->m_bLastTile = WMAB_FALSE;

    prp->m_iBufAddPos = 0;
    prp->m_iBufCalcPos = 0;
    prp->m_iBufCodePos = 0;
    prp->m_iBufReconPos = 0;
    prp->m_iBufXFormPos = 0;
    prp->m_iBufXFormReconPos = 0;
    prp->m_iBufSegPos = 0;

    prp->m_iBufCalcFxPos = 0;
    prp->m_iBufCodeFxPos = 0;

    prp->m_iBufMonoPos = 0;

    prp->m_iBufBasePos = 0;

    prp->m_iTilesInSubframeAdd = 0;
    prp->m_iTilesInSubframeCalc = 0;
    prp->m_iTilesInSubframeCode = 0;
    prp->m_iTilesInSubframeXForm = 0;
    prp->m_iTilesInSubframeXFormRecon = 0;
    prp->m_iTilesInSubframeSeg = 0;

    memset(prp->m_rgiTilesInSubframeAdd, 0, 4*sizeof(Int));
    prp->m_iTilesInSubframeAddPos = 0;

    prp->m_iTilesInSubframeCalcFx = 0;
    prp->m_iTilesInSubframeCodeFx = 0;

    prp->m_iTilesInSubframeBase = 0;

    prp->m_iSampleOffset = 0;

    prp->m_bTileInit = WMAB_FALSE;

    if (pau->m_bCx)
    {
        Chex *pcx = pau->m_pcx;
        pcx->m_bNoInterpFromPrev = WMAB_TRUE;
    }

    // clear mclt history buffer
    memset(pau->m_rgCoefHistMCLT, 0,
           RECONPROC_HIST_SIZE*sizeof(CoefType)*pau->m_cChannel);

    // clear the cx reverb filter
    chexClearReverbHistory(pau);

#if (CX_DECODE_MONO==1)
    if (pau->m_bCx && 2==pau->m_cChannel && pau->m_rgpcinfo &&
        !pau->m_bEncoder)
        pau->m_rgpcinfo[1].m_bNoDecodeForCx = WMAB_TRUE;
#endif
}

Int reconProcGetCap()
{
    return 16;
}

Int reconProcCapToIndex(Int iCap)
{
    switch (iCap)
    {
        case 32: return 3; break;
        case 16: return 2; break;
        case  8: return 1; break;
        case  4:
        default: return 0; break;
    }
}

Int reconProcIndexToCap(Int iIndex)
{
    if (iIndex >= 0 && iIndex <= 3)
        return (4 << iIndex);
    else
        return 0;
}

// =======================================================================

Void reconProcMinMaxFromIndex(Int iIndex, Int *piMin, Int *piMax)
{
    Int iOffset, iNextOffset, i;

    iOffset = 0;
    i = 0;
    while (1)
    {
        iNextOffset = iOffset + i + 1;
        if (iNextOffset > iIndex)
            break;
        iOffset = iNextOffset;
        i++;
    }
    *piMax = i;
    *piMin = iIndex - iOffset;
}

Void reconProcIndexFromMinMax(Int *piIndex, Int iMin, Int iMax)
{
    Int i;

    *piIndex = 0;
    for (i=0; i < iMax; i++)
        *piIndex += i + 1;
    *piIndex += iMin;
}

Int reconProcTilesToIndex(Int iMinTiles, Int iMaxTiles)
{
    // values are 2, 4, 8, 16, 32
    Int iMin = LOG2(iMinTiles)-1;
    Int iMax = LOG2(iMaxTiles)-1;
    Int iIndex;

    assert(iMin < 5);
    assert(iMax < 5);

    reconProcIndexFromMinMax(&iIndex, iMin, iMax);

    // number of possible values = 5(6)/2 = 15
    assert(iIndex >= 0 && iIndex < 15);

    return iIndex;
}

Void reconProcIndexToTiles(Int iIndex, Int *piMinTiles, Int *piMaxTiles)
{
    reconProcMinMaxFromIndex(iIndex, piMinTiles, piMaxTiles);

    *piMinTiles = (1<<(*piMinTiles + 1));
    *piMaxTiles = (1<<(*piMaxTiles + 1));
}

// =======================================================================

Int chexIndexToMaxAnchors(Int iIndex, Int iMinTiles)
{
    Int iMaxAnchors;

    assert(iIndex >= 0 && iIndex < 4); // 0, 1, 2, 3
    iMaxAnchors = (1<<iIndex); // 1, 2, 4, 8
    if (iMinTiles > 8 && 3 == iIndex)
        // for 16, 32 case allow upto 16 anchors per frame
        iMaxAnchors *= 2;

    return iMaxAnchors;
}

Int chexMaxAnchorsToIndex(Int iMaxAnchors, Int iMinTiles)
{
    if (iMinTiles > 8 && 16 == iMaxAnchors)
        return 3;
    else
        return LOG2(iMaxAnchors);
}

// =======================================================================

Int reconProcGetMaxTiles(CAudioObject *pau)
{
    Int iIndex, iMinTiles, iMaxTiles;

    if (WMAB_FALSE == pau->m_bReconProc)
        return 0;

    iIndex = (pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_RTILE) >>
              ENCOPT4_PLUSV2_RTILE_BITSOFFSET;
    reconProcIndexToTiles(iIndex, &iMinTiles, &iMaxTiles);

    return iMaxTiles;
}

WMARESULT reconProcInit(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Int i, iIndex, iMinTiles, iMaxTiles, iPrevNeed, iCurrNeed;
    Chex *pcx = pau->m_pcx;
    Fex *pfx = &(pau->m_fex);
    WMAMALLOC_COUNT_DECL;

    if (NULL == prp)
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);

    prp->m_pau = pau;

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
    REPL_PARAM(prp->m_iNTilesPerFrameBasic, g_iNTilesPerFrame);
#endif

    iIndex = (pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_RTILE) >>
              ENCOPT4_PLUSV2_RTILE_BITSOFFSET;
    reconProcIndexToTiles(iIndex, &iMinTiles, &iMaxTiles);
    // only for testing recon domain processing in absence of chex/recon fex
    if (pau->m_bReconProc && !pau->m_bCx && !pau->m_bReconFex)
    {
        iMinTiles = 8;
        iMaxTiles = 16;
    }
    prp->m_iMaxTilesPerFrame = iMaxTiles;
    prp->m_iNTilesPerFrameBasic = iMinTiles;
    prp->m_iMinTileSize = pau->m_cFrameSampleHalf / prp->m_iMaxTilesPerFrame;

    if (pau->m_bEncoder)
        prp->m_nTilesInBuf = prp->m_iMaxTilesPerFrame*3 + 2;
    else
        prp->m_nTilesInBuf = 3*prp->m_iMaxTilesPerFrame/2 + 2;

    WMAMALLOC_COUNT_STORE(0);
    WMAMALLOC_COUNT_STORE(1);

    prp->m_cFrameSampleChex = pau->m_cFrameSample/prp->m_iNTilesPerFrameBasic;
    prp->m_cFrameSampleHalfChex = prp->m_cFrameSampleChex/2;

#if 0
#define IMCLT_MAXN 256
#define INVSQRT2 0.70710678118654752440084436210485
    pau->m_rgIMCLTSinCosTable = (BP2Type*)callocAligned(IMCLT_MAXN * 2 * sizeof(BP2Type), 32);
    CHECKWMA_ALLOC( wmaResult, pau->m_rgIMCLTSinCosTable );

    {
        BP1Type ca = BP2_FROM_FLOAT(INVSQRT2),
                sa = ca,
                tm,
                cstep = BP2_FROM_FLOAT(-0.0061358846491544753596402345903726),
                sstep = BP2_FROM_FLOAT(-0.99998117528260114265699043772857);
        int k;
        for (k = 1; k < IMCLT_MAXN; k++) 
        {
            tm = MULT_ADD2_BP2(ca, cstep,  sa, sstep);
            sa = MULT_ADD2_BP2(sa, cstep, -ca, sstep);
            ca = tm;

            pau->m_rgIMCLTSinCosTable[             k] = ca;
            pau->m_rgIMCLTSinCosTable[IMCLT_MAXN + k] = sa;
        }
    }
#else
#define IMCLT_MAXN 0
#endif

    pau->m_rgCoefHistMCLT = (CoefType*)callocAligned(RECONPROC_HIST_SIZE*sizeof(CoefType)*pau->m_cChannel, 32);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgCoefHistMCLT);

#if (CX_DECODE_MONO==1)
    if (pau->m_bCx && !pau->m_bEncoder)
    {
        // +2 to prevent reading past allocated memory in MMX/SSE version of auReconSample (caught by AppVerifier)
        pau->m_rgCoefSampMCLT = (CoefType*)callocAligned((prp->m_cFrameSampleHalfChex*(pau->m_cChannel-pcx->m_iMaxPairs)+2)*sizeof(CoefType), 32);
        CHECKWMA_ALLOC(wmaResult, pau->m_rgCoefSampMCLT);
    }
#endif

#if defined(CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL) && CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL
    // auWindowReflectionAndDctIV256() requires fixed offset between data buffer and cos table
    // For ARM: Need to add 2 words at end of buffer, so we can write more efficient asm code by pre-loading 2 words
    // before a loop, which will cause 2 extra words to be read at end of buffer. We want to ensure that those
    // 2 extra words are valid memory.
    pau->m_rgCoefDct256tab = (BP1Type*)callocAligned(256 * sizeof(BP1Type) + (prp->m_cFrameSampleHalfChex*2 + 2 + 2)*sizeof(CoefType), 32);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgCoefDct256tab);
    conWinRefPre128FFTbl(pau->m_rgCoefDct256tab);
    pau->m_rgCoefXFormMCLT = (CoefType*)(pau->m_rgCoefDct256tab + 256);
#else   
    // +2 is for the extra {real, complex} pair wasted by the Ccs fft representation in the context of direct IMCLT
    // For ARM: Add 2 words at end of buffer, so we can write more efficient asm code by pre-loading 2 words
    // before a loop, which will cause 2 extra words to be read at end of buffer. We want to ensure that those
    // 2 extra words are valid memory.
    pau->m_rgCoefXFormMCLT = (CoefType*)callocAligned((prp->m_cFrameSampleHalfChex*2 + 2 + 2)*sizeof(CoefType), 32);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgCoefXFormMCLT);
#endif  // CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL

#if (CX_DCT_ONLY==0)
    pau->m_rgCoefXFormMCLTDiff = (CoefType*)callocAligned(prp->m_cFrameSampleHalfChex*sizeof(CoefType)*2, 32);
#else
    pau->m_rgCoefXFormMCLTDiff = (CoefType*)callocAligned(prp->m_cFrameSampleHalfChex*sizeof(CoefType), 32);
#endif
    CHECKWMA_ALLOC(wmaResult, pau->m_rgCoefXFormMCLTDiff);

    //printf("      S=%d %d %d\n", prp->m_cFrameSampleHalfChex, iMinTiles, iMaxTiles);
    WMAMALLOC_COUNT_PRT("      Alloc bufs", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

    if (pau->m_bReconFex)
        prp->m_iTileSplitType = ReconProcTileSplitBaseSmall;
    else
        prp->m_iTileSplitType = ReconProcTileSplitBasic;

    prp->m_rgiPCMEndReconPoint = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, prp->m_rgiPCMEndReconPoint);
    prp->m_rgiPCMSamplesReady = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, prp->m_rgiPCMSamplesReady);
    prp->m_rgchextiBuf =
        (ReconTileInfo*)auCalloc(prp->m_nTilesInBuf*sizeof(ReconTileInfo));
    CHECKWMA_ALLOC(wmaResult, prp->m_rgchextiBuf);

    prp->m_rgiPCMStart = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, prp->m_rgiPCMStart);

    WMAMALLOC_COUNT_PRT("      Basic buffers", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

    if (pcx && pau->m_bCx)
    {
        Int iMaxAnchorsPerFrame;

        iIndex =
            (pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_CXMAXANCHORS) >>
            ENCOPT4_PLUSV2_CXMAXANCHORS_BITSOFFSET;

        iMaxAnchorsPerFrame = chexIndexToMaxAnchors(iIndex, iMinTiles);
        pcx->m_iMaxAnchorsPerFrame = iMaxAnchorsPerFrame;

        prp->m_ncxarti = 2*iMaxAnchorsPerFrame + 1;
        // Encoder needs one more since it segments one frame ahead
        if (pau->m_bEncoder)
            prp->m_ncxarti += iMaxAnchorsPerFrame;

        prp->m_rgcxarti = (CxAnchorReconTileInfo*)auCalloc(prp->m_ncxarti*
                                              sizeof(CxAnchorReconTileInfo));
        CHECKWMA_ALLOC(wmaResult, prp->m_rgcxarti);
        for (i=0; i < prp->m_ncxarti; i++)
        {
            TRACEWMA_EXIT(wmaResult,
                    chexInitAnchorReconTileInfo(pau, pcx, prp->m_rgcxarti+i));
        }

#if (CX_DCT_ONLY==0)
        // 1 scale per frequency.
#ifndef WMA_TARGET_ARM
        pcx->m_rgReconBandScales =
            (ChexType*)callocAligned(prp->m_cFrameSampleHalfChex*
                                     sizeof(ChexType)*2,16);
#else
    // For ARM: Add 1 word at end of buffer, so we can write more efficient asm code by pre-loading 1 word
    // before a loop, which will cause 1 extra word to be read at end of buffer. We want to ensure that the
    // extra word is in valid memory.
        pcx->m_rgReconBandScales =
            (ChexType*)callocAligned((prp->m_cFrameSampleHalfChex*2+1)*
                                     sizeof(ChexType),16);
#endif
        CHECKWMA_ALLOC(wmaResult, pcx->m_rgReconBandScales);
#endif

        WMAMALLOC_COUNT_PRT("      Cx anchor info", 0, -1);
        WMAMALLOC_COUNT_STORE(0);

        // init the reverb filter using a fixed band configuration (20 bands)
        pcx->m_iNumBandIndex = chexMaxBandsToIndex(20, pau->m_iPlusVersion);
        pcx->m_iBandMultIndex = 0; // g_iChexBandSizesM20_1
        pcx->m_iStartBand = 0;
        TRACEWMA_EXIT(wmaResult, cxReverbInit(pau, pcx->m_pcxrf));

        WMAMALLOC_COUNT_PRT("      Cx reverb", 0, -1);
        WMAMALLOC_COUNT_STORE(0);
    }

    {
        RFxReconTileInfo *prfxrti;

        prp->m_nrfxrti = prp->m_iMaxTilesPerFrame;
        prp->m_rgrfxrti =
            (RFxReconTileInfo*)auCalloc(prp->m_nrfxrti*
                                        sizeof(RFxReconTileInfo));
        CHECKWMA_ALLOC(wmaResult, prp->m_rgrfxrti);
        for (i=0; i < prp->m_nrfxrti; i++)
        {
            prfxrti = prp->m_rgrfxrti + i;
            if (pau->m_bReconFex)
                TRACEWMA_EXIT(wmaResult,
                              fexInitReconTileInfo(pau, pfx, prfxrti, i));
        }
    }

    WMAMALLOC_COUNT_PRT("      RFX info", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

    if (pau->m_bCx && pau->m_bReconFex)
    {
#if (CX_DCT_ONLY==0)
        // curr/next for DCT buf
        // prev/curr/next for IDCT buf
        prp->m_iDCTBufSize = pau->m_cChannel*prp->m_cFrameSampleHalfChex*5;
#else
        prp->m_iDCTBufSize = prp->m_cFrameSampleHalfChex;
#endif
    }
    else if (pau->m_bReconProc)
    {
        prp->m_iDCTBufSize = prp->m_cFrameSampleHalfChex;
    }

    if (prp->m_iDCTBufSize != 0)
    {
        pau->m_rgDCTBuf =
            (CoefType*)callocAligned(prp->m_iDCTBufSize*sizeof(CoefType), 32);
        CHECKWMA_ALLOC(wmaResult, pau->m_rgDCTBuf);
    }

#if (CX_DCT_ONLY==0)
    pau->m_rgCoefXFormDST =
        (CoefType*)callocAligned(prp->m_cFrameSampleHalfChex*sizeof(CoefType),
                                 32);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgCoefXFormDST);
#endif

    WMAMALLOC_COUNT_PRT("      DCT/DST buf", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

    for (i=0; i < prp->m_nTilesInBuf; i++)
    {
        ReconTileInfo *prti;

        prti = prp->m_rgchextiBuf + i;

        TRACEWMA_EXIT(wmaResult, initReconTileInfo(pau, prp, prti));
        if (pau->m_bCx)
        {
            TRACEWMA_EXIT(wmaResult, chexInitReconTileInfo(pau, pcx, prti));
        }
    }

    // to determine pcm size, need framesamplehalf-1/2*minsubframesize to store
    // current frame, and need 1/2*framesamplehalf+3/2*maxreconframesize
    iPrevNeed = pau->m_cFrameSampleHalf/2 + 3*prp->m_cFrameSampleHalfChex/2;
#if (CX_DCT_ONLY==0)
    // the following is only needed if recon domain processing happens
    // in decode instead of getpcm stage
    iPrevNeed += prp->m_cFrameSampleHalfChex - prp->m_iMinTileSize;
#endif
    prp->m_iPCMPrevFrameSave = iPrevNeed;
    iCurrNeed = pau->m_cFrameSampleHalf;
    prp->m_iPCMSize = iCurrNeed + iPrevNeed;

    prp->m_rgbTileSplitArbitrary =
        (Bool*)auCalloc(2*prp->m_iMaxTilesPerFrame*sizeof(Bool));
    CHECKWMA_ALLOC(wmaResult, prp->m_rgbTileSplitArbitrary);

    WMAMALLOC_COUNT_PRT("      Chex params + misc", 0, -1);

    // open the intermediate files for debugging CX stages
    DBG_CX_OPEN

    chexReset(pau);

exit:
    WMAMALLOC_COUNT_PRT("    Total RFx+Cx", 1, -1);
    return wmaResult;
}

Void reconProcFree(CAudioObject *pau)
{
    Int i;
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    Fex *pfx = &pau->m_fex;

    // close the intermediate files for debugging CX stages
    DBG_CX_CLOSE

    freeAligned(pau->m_rgCoefHistMCLT);
    freeAligned(pau->m_rgCoefSampMCLT);
#if defined(CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL) && CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL
    freeAligned(pau->m_rgCoefDct256tab);
#else
    freeAligned(pau->m_rgCoefXFormMCLT);
#endif
    freeAligned(pau->m_rgCoefXFormMCLTDiff);

    freeAligned(pau->m_rgDCTBuf);
    freeAligned(pau->m_rgCoefXFormDST);

    if (NULL == prp)
        return;

    for (i=0; i < prp->m_nTilesInBuf; i++)
    {
        freeReconTileInfo(pau, prp, &prp->m_rgchextiBuf[i]);
        if (WMAB_TRUE == pau->m_bCx)
            chexFreeReconTileInfo(pau, pcx, &prp->m_rgchextiBuf[i]); 
   }

    for (i=0; i < prp->m_ncxarti; i++)
    {
        chexFreeAnchorReconTileInfo(pau, pcx, prp->m_rgcxarti+i);
    }

    for (i=0; i < prp->m_nrfxrti; i++)
    {
        if (WMAB_TRUE == pau->m_bReconFex)
            fexFreeReconTileInfo(pau, pfx, prp->m_rgrfxrti+i, i);
    }
    DELETE_ARRAY(prp->m_rgrfxrti);

    DELETE_ARRAY(prp->m_rgiPCMSamplesReady);
    DELETE_ARRAY(prp->m_rgiPCMEndReconPoint);
    DELETE_ARRAY(prp->m_rgchextiBuf);
    DELETE_ARRAY(prp->m_rgcxarti);

    DELETE_ARRAY(prp->m_rgiPCMStart);

    DELETE_ARRAY(prp->m_rgbTileSplitArbitrary);
}

// to prevent overflow in integer math
Void chexShiftPoints(CAudioObject *pau, Int iSampleShift)
{
    ReconProc *prp = pau->m_prp;
    Int iTileShift;
    Int i;

    // Do Tile shift
    iTileShift = (1<<28); // arbitrary
    if (prp->m_rgchextiBuf[0].m_iTileCnt >= iTileShift)
    {
        for (i=0; i < prp->m_nTilesInBuf; i++)
        {
            if (chexTileNotInUse(prp->m_rgchextiBuf+i))
                prp->m_rgchextiBuf[i].m_iTileCnt = -4*prp->m_nTilesInBuf;
            else
                prp->m_rgchextiBuf[i].m_iTileCnt -= iTileShift;
        }
    }

    // Sample shift
    if (0 == iSampleShift)
        return;

    prp->m_iSampleOffset += iSampleShift;

    for (i=0; i < pau->m_cOrigChannel; i++)
    {
        prp->m_rgiPCMEndReconPoint[i] -= iSampleShift;
        prp->m_rgiPCMStart[i] -= iSampleShift;
    }

    for (i=0; i < prp->m_nTilesInBuf; i++)
    {
        prp->m_rgchextiBuf[i].m_iStartPt -= iSampleShift;
    }

    prp->m_iStartPt -= iSampleShift;
    prp->m_iEndPt -= iSampleShift;
    prp->m_iEndOutPt -= iSampleShift;
    prp->m_iRecon -= iSampleShift;
}

WMARESULT chexShiftBuf(CAudioObject *pau, Int iChSrc)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChSrc;
    Int iOffset, iCopy, iMinPtNeeded;

    iMinPtNeeded = pau->m_iFrameStart - prp->m_iPCMPrevFrameSave;

    iOffset = iMinPtNeeded - prp->m_rgiPCMStart[iChSrc];
    if (0 == iOffset)
        goto exit2;

    assert(iOffset < prp->m_iPCMSize);
    
    iCopy = min(prp->m_iPCMSize-iOffset, prp->m_iPCMPrevFrameSave);
    if (iCopy != prp->m_iPCMPrevFrameSave)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    if (ppcinfo->m_bNoDecodeForCx)
        goto exit;

    if (iOffset >= prp->m_iPCMPrevFrameSave)
    {
        memcpy(ppcinfo->m_rgPCMBuf, ppcinfo->m_rgPCMBuf+iOffset,
               iCopy*sizeof(CoefType));
    }
    else
    {
        assert(prp->m_iNTilesPerFrameBasic <= 2);
        assert(iOffset >= prp->m_iPCMPrevFrameSave/2);
        memcpy(ppcinfo->m_rgPCMBuf, ppcinfo->m_rgPCMBuf+iOffset,
               (prp->m_iPCMPrevFrameSave-iOffset)*sizeof(CoefType));
        memcpy(ppcinfo->m_rgPCMBuf+prp->m_iPCMPrevFrameSave-iOffset,
               ppcinfo->m_rgPCMBuf+prp->m_iPCMPrevFrameSave,
               (iCopy-(prp->m_iPCMPrevFrameSave-iOffset))*sizeof(CoefType));
    }

exit:
    prp->m_rgiPCMStart[iChSrc] += iOffset;
    prp->m_iRecon = prp->m_rgiPCMStart[iChSrc];
exit2:
    return wmaResult;
}

WMARESULT chexSubframeRecon(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Int iCh, iChSrc, iReconSamples;
    PerChannelInfo *ppcinfo;
    CoefType *pctOut, *pctHist, *pctNew;

#if defined(ALLOW_EXTERNAL_FILE_FOR_RECON) && 0
    // does not work for decoder since don't know ppcinfo->m_iSizeNext
    if (WMAB_TRUE == g_bReplaceForChex)
    {
        prvReplaceSamplesFromFilePostXForm(pau);
        if (WMAB_TRUE == pau->m_bCx)
            prvCreateMono(pau);
    }
#endif

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        if (ppcinfo->m_bNoDecodeForCx)
            continue;

        pctHist = ppcinfo->m_rgCoefRecon - ppcinfo->m_iSizePrev/2;
        pctNew = ppcinfo->m_rgCoefRecon;
        pctOut = ppcinfo->m_rgCoefRecon - ppcinfo->m_iSizePrev/2;

        // NOTE: this overlap-add needs to use the "bFlip = 1" because
        // it is overwriting the output samples in the same place
        // as the history buffer and new transform coeffs, otherwise
        // PCM samples would have to be rearranged after this function
        TRACEWMA_EXIT(wmaResult, auOverlapAddV3(pau, pctOut, pctHist, pctNew,
                                                NULL, NULL,
                                                ppcinfo->m_iSizePrev,
                                                ppcinfo->m_iSizeCurr,
                                                WMAB_TRUE, WMAB_FALSE, 1,
                                                WMAB_TRUE));

        iReconSamples = (ppcinfo->m_iSizePrev+ppcinfo->m_iSizeCurr)/2;

        prvDumpVals("out.raw", (0==iCh) ? "wb" : "ab", iReconSamples, pctOut);

        // buffer stores all samples recon and unrecon
        if (prp)
            prp->m_rgiPCMEndReconPoint[iChSrc] += iReconSamples;
    }

    if (prp && (pau->m_cCodedChannel != pau->m_cOrigChannel))
    {
        for (iCh=1; iCh < pau->m_cOrigChannel; iCh++)
        {
            prp->m_rgiPCMEndReconPoint[iCh] = prp->m_rgiPCMEndReconPoint[0];
            prp->m_rgiPCMStart[iCh] = prp->m_rgiPCMStart[0];
        }
    }
#if 0
    printf("PCM start=%d PCM end=%d\n", prp->m_rgiPCMStart[0],
           prp->m_rgiPCMEndReconPoint[0]);
    {
        static int pt = -1024;
        pt += ppcinfo->m_iSizePrev/2+ppcinfo->m_iSizeCurr/2;
        printf("pcm samples upo=%d\n", pt);
    }
#endif

exit:
    return wmaResult;
}

Void prvObtainSamplesFromFile(CAudioObject *pau,
                              const TCHAR *szFile, Int iStart, Int iLen,
                              Int iCh, CoefType *pCoeff);

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
Void auCompareSamps(CAudioObject *pau, CoefType *pCoeff, ReconTileInfo *prti,
                    Int iCh)
{
    // have 2nd 1/2 of prev and 1st 1/2 of curr
    CoefType pBuf[4096];
    Int iStart = prti->m_iStartPtInFile-prti->m_iSizePrev/2;
    Int iEnd = prti->m_iStartPtInFile+prti->m_iSizeCurr/2;
    Int iLen = iEnd - iStart;
    Int i;

    prvObtainSamplesFromFile(pau, g_szReplaceFile, iStart, iLen, iCh, pBuf);
    for (i=0; i < iLen; i++)
    {
        printf("AAA=%d %d %f %f\n", iCh, i, pBuf[i], pCoeff[i]);
    }
}
#endif

Int chexTilesInFrame(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;

    return prp->m_iTilesInSubframeCode;
}

INLINE Int chexGet2ndHalfPts(ReconTileInfo *prti, Int *piStart, Int *piEnd)
{
    Int iStart = max(prti->m_iSizeCurr/2, prti->m_iStart);
    Int iEnd   = max(prti->m_iSizeCurr/2, prti->m_iEnd);
    assert(iEnd >= iStart);
    *piStart = iStart;
    *piEnd = iEnd;
    return (iEnd-iStart);
}

INLINE Int chexGet1stHalfPts(ReconTileInfo *prti, Int *piStart, Int *piEnd)
{
    Int iStart = min(prti->m_iSizeCurr/2, prti->m_iStart);
    Int iEnd   = min(prti->m_iSizeCurr/2, prti->m_iEnd);
    assert(iEnd >= iStart);
    *piStart = iStart;
    *piEnd = iEnd;
    return (iEnd-iStart);
}

#if defined(ALLOW_EXTERNAL_FILE_FOR_RECON)

Void chexObtainTileMCLTFromFile(CAudioObject *pau, const TCHAR *szFile,
                                ReconTileInfo *prti, Int iCh,
                                CoefType *pBuf)
{
    Int iStart = prti->m_iStartPtInFile-prti->m_iSizeCurr/2;

    prvObtainSamplesFromFile(pau, szFile, iStart, prti->m_iSizeCurr*2,
                             iCh, pBuf);

    pau->m_pfnApplyWindow(pau, pBuf, prti->m_iSizePrev, prti->m_iSizeCurr,
                          prti->m_iSizeNext, WMAB_FALSE);
    auApplyReflectionV3(pBuf, prti->m_iSizeCurr);

    catchFP();
    chexDctHelper(pau, NULL, pBuf, BP2_FROM_FLOAT(1), prti->m_iSizeCurr);
    chexDstHelper(pau, NULL, pBuf+prti->m_iSizeCurr, BP2_FROM_FLOAT(1), prti->m_iSizeCurr);
    initFP();
}

#endif // defined(ALLOW_EXTERNAL_FILE_FOR_RECON)

#if defined(CHEX_VERIFY) && defined(ALLOW_EXTERNAL_FILE_FOR_RECON)

Void chexDumpOrigNew(CAudioObject *pau, ReconTileInfo *prti, Int iCh,
                     CoefType *pReconBuf, Bool bCompute, Bool bReal)
{
    __declspec(align(32)) static CoefType buf[4096];
    ReconProc *prp = pau->m_prp;
    CoefType *pBuf;
    Int i, iIndex;

    if (!strcmp(g_szReplaceFile, ""))
        return;

    if (bCompute)
        chexObtainTileMCLTFromFile(pau, g_szReplaceFile, prti, iCh, buf);

    if (bReal)
        pBuf = buf;
    else
        pBuf = buf + prti->m_iSizeCurr;

    prvDumpVals("outr.raw", "wb", prti->m_iSizeCurr, pBuf);
    prvDumpVals("outr.raw", "ab", prti->m_iSizeCurr, pReconBuf);

    if (!g_bVerify)
        return;

    iIndex = prp->m_cStart;
    for (i=0; i < prp->m_cBands; i++)
    {
        if (1 == prp->m_rgiBandSizes[iIndex] && ABS(pBuf[iIndex])>5)
            assert(ABS(pReconBuf[iIndex]-pBuf[iIndex])/pBuf[iIndex]<0.01f);
        iIndex += prp->m_rgiBandSizes[i];
    }
}

#endif // defined(CHEX_VERIFY) && defined(ALLOW_EXTERNAL_FILE_FOR_RECON)

WMARESULT chexGetSamplesFromPCMBuf(CAudioObject *pau,
                                   PerChannelInfo *ppcinfo,
                                   Int iChSrc,
                                   ReconTileInfo *prti,
                                   CoefType *pDest)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Int iStart, iEnd,  iOffset;
    ReconTileInfo *prtiPrev, *prtiNext;

    iStart = prti->m_iStartPt - min(prti->m_iSizeCurr, prti->m_iSizePrev)/2;
    iEnd   = prti->m_iStartPt + prti->m_iSizeCurr + min(prti->m_iSizeCurr, prti->m_iSizeNext)/2;

    // account for leading/trailing silence
    prtiPrev = chexPrevTile(prp, prti);
    prtiNext = chexNextTile(prp, prti);

    if (iStart < prp->m_iRecon)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);   
    }

    assert(iStart >= prp->m_rgiPCMStart[iChSrc] ||
           (iStart+prp->m_iSampleOffset < 0));
    if (iEnd > prp->m_rgiPCMEndReconPoint[iChSrc] &&
           !chexInfoStatLastTile(prti->m_uInfoStat) &&
           !prp->m_bLastTile)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);   
    }

    iStart = max(iStart, prp->m_rgiPCMStart[iChSrc]);
    iEnd = min(iEnd, prp->m_rgiPCMEndReconPoint[iChSrc]);

    // copy from iStart to iEnd-1
    memset(pDest, 0, 2*prti->m_iSizeCurr*sizeof(CoefType));
    iOffset = iStart - (prti->m_iStartPt - prti->m_iSizeCurr/2);
    assert(iOffset >= 0);
    if (iEnd-iStart >= 0)
        memcpy(pDest+iOffset,
               ppcinfo->m_rgPCMBuf+(iStart-prp->m_rgiPCMStart[iChSrc]),
               (iEnd-iStart)*sizeof(CoefType));

exit:
    return wmaResult;
}

Void reconProcGetDSTDCTFromDCTBuf(CAudioObject *pau,
                                  PerChannelInfo *ppcinfo,
                                  ReconTileInfo *prti,
                                  CoefType *pDst)
{
    PerChannelInfoShr *ppcinfoShr = ppcinfo->m_ppcinfoShr;
    const CoefType *pIDCTPrev = ppcinfoShr->m_pIDCTBufPrev;
    const CoefType *pIDCTCurr = ppcinfoShr->m_pIDCTBufCurr;
    const CoefType *pIDCTNext = ppcinfoShr->m_pIDCTBufNext;

    memcpy(pDst, ppcinfoShr->m_pDCTBufCurr,
           prti->m_iSizeCurr*sizeof(CoefType));
#if (CX_DCT_ONLY==0)
    auDSTFromDCTV3(pau, pDst+prti->m_iSizeCurr,
                   pIDCTPrev, pIDCTCurr, pIDCTNext,
                   prti->m_iSizePrev, prti->m_iSizeCurr, prti->m_iSizeNext);
#endif
}

// call this after MCLT processing (i.e. Cx) is done
// Have 3 IDCT buffers (prev, curr, next)
// Shift               (curr, next,     ) --> Shift by iSizePrev to left
// Have 2  DCT buffers (      curr, next)
// Shift               (      next,     ) --> Shift by iSizeCurr to left
INLINE
Void reconProcShiftDCTBufs(CAudioObject *pau,
                           PerChannelInfo *ppcinfo)
{
    PerChannelInfoShr *ppcinfoShr = ppcinfo->m_ppcinfoShr;
    CoefType *pTemp;

    pTemp = ppcinfoShr->m_pIDCTBufPrev;
    ppcinfoShr->m_pIDCTBufPrev = ppcinfoShr->m_pIDCTBufCurr;
    ppcinfoShr->m_pIDCTBufCurr = ppcinfoShr->m_pIDCTBufNext;
    ppcinfoShr->m_pIDCTBufNext = pTemp;

    pTemp = ppcinfoShr->m_pDCTBufCurr;
    ppcinfoShr->m_pDCTBufCurr = ppcinfoShr->m_pDCTBufNext;
    ppcinfoShr->m_pDCTBufNext = pTemp;
}

// call these after MLT processing (i.e. RFx) is done
// Add current IDCT & DCT to DCT buffers
INLINE
Void reconProcAddDCTBuf(CAudioObject *pau,
                        PerChannelInfo *ppcinfo,
                        ReconTileInfo *prtiPrev,
                        CoefType *pDCTBuf)
{
    PerChannelInfoShr *ppcinfoShr = ppcinfo->m_ppcinfoShr;

    memcpy(ppcinfoShr->m_pDCTBufNext,
           pDCTBuf, prtiPrev->m_iSizeNext*sizeof(CoefType));
}

INLINE
Void reconProcAddIDCTBuf(CAudioObject *pau,
                         PerChannelInfo *ppcinfo,
                         ReconTileInfo *prtiPrev,
                         CoefType *pIDCTBuf)
{
    PerChannelInfoShr *ppcinfoShr = ppcinfo->m_ppcinfoShr;

    memcpy(ppcinfoShr->m_pIDCTBufNext, pIDCTBuf,
           prtiPrev->m_iSizeNext*sizeof(CoefType));
}

INLINE
Void reconProcZeroDCTBuf(CAudioObject *pau,
                         ReconTileInfo *prti)
{
    PerChannelInfoShr *ppcinfoShr;
    Int iCh;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        ppcinfoShr = pau->m_rgpcinfoShr + iCh;

        memset(ppcinfoShr->m_pDCTBufNext, 0,
               prti->m_iSizeNext*sizeof(CoefType));
        memset(ppcinfoShr->m_pIDCTBufNext, 0,
               prti->m_iSizeNext*sizeof(CoefType));
    }
}

#if (IMCLT_MAXN != 0)

void AecCcsInvMclt
(
    CAudioObject *pau,
    unsigned  n,
    CoefType * t
)
{
    unsigned     k;
    CoefType r1, i1;
    CoefType flNyq, flDC;

    // t[0..n-1] is real input, t[n..2n-1] is imag input
    // t[0..2n-1] also serves as output buffer
    // output speed is 2x input speed, but imag begins at half, so output never quite catches up to imag input
    // real part gets overwritten right away, so save it
    CoefType Real[IMCLT_MAXN], *pImag;
    if (n > IMCLT_MAXN) { assert(0); return; }
    memcpy(Real, t, n * sizeof(Real[0])); // copy because it gets overwritten
    pImag = t + n;
    flDC = MULT_SQRT2(Real[0] + pImag[0]);
    flNyq = -MULT_SQRT2(Real[n-1] + pImag[n-1]);

    /* Apply IMCLT-to-IDFT mapping */
    if (IMCLT_MAXN == n) // max happens to be the most common
    {
        BP1Type* tab = pau->m_rgIMCLTSinCosTable;
        for (k = 1; k < n; k++) 
        {
            r1 = pImag[k]   + Real[k-1];
            i1 = pImag[k-1] - Real[k];
            t[k*2  ] = MULT_ADD2_BP2(tab[      k], r1,  -tab[256 + k], i1);
            t[k*2+1] = MULT_ADD2_BP2(tab[256 + k], r1,   tab[      k], i1);
        }
    }
    else
    {
        BP1Type   ca, sa, tm, cstep, sstep;

        if (128 == n)
        {
            cstep = BP2_FROM_FLOAT(-0.012271);
            sstep = BP2_FROM_FLOAT(-0.999925);
        }
        else
        { 
            assert(0); // doesn't seem to get used
            cstep = sstep = 0;
            /* unintegerized reference code
            BP1Type uL, g;
            uL =  (FLOAT)(0.5 / n);
            g = (FLOAT)(PI * (0.5 + uL));
            cstep =  (FLOAT)(cos(g)); 
            sstep =  (FLOAT)(sin(-g));
            */
        }
       
        ca =  BP2_FROM_FLOAT(INVSQRT2); 
        sa = ca;
        for (k = 1; k < n; k++) 
        {
            r1 = pImag[k]   + Real[k-1];
            i1 = pImag[k-1] - Real[k];
            tm = MULT_ADD2_BP2(ca, cstep,   sa, sstep);
            sa = MULT_ADD2_BP2(sa, cstep,  -ca, sstep);
            ca = tm;
            t[k*2]   = MULT_ADD2_BP2(ca, r1,  -sa, i1);
            t[k*2+1] = MULT_ADD2_BP2(sa, r1,  ca, i1);
        }
    }
    t[0] = flDC;
    t[1] = 0;
    t[2*n] = flNyq;
    t[2*n+1] = 0;
    pau->m_pfnInvFftComplexConjugate(pau->m_hIntelFFTCcsInfo, t, LOG2(n) + 1, NULL, 4096 );
}

#endif

#if 0

FILE *g_file_fwtxfm = NULL;

#if !defined( BUILD_INTEGER )

// log the float base-band coefficients to a file.

#define DBG_REFRESH_FWTXFM() {                          \
    if( NULL == g_file_fwtxfm )                         \
        g_file_fwtxfm = fopen( "fwtxfm.flt", "wb" );    \
    fwrite( pBuf, sizeof(float),                        \
        2*prti->m_iSizeCurr, g_file_fwtxfm ); }         \

#else

// read the float base-band coeffs, measure max
// error between int & flt, and then replace the
// current coefficients with the float coeffs.

#define DBG_REFRESH_FWTXFM() {                          \
    int i; static float flt[4096];                      \
    const int n = 2*prti->m_iSizeCurr;                  \
    CoefType *ptr = (CoefType*)pBuf;                    \
    if( NULL == g_file_fwtxfm )                         \
        g_file_fwtxfm = fopen( "fwtxfm.flt", "rb" );    \
    fread( flt, sizeof(float), n, g_file_fwtxfm );      \
    for( i=0; i< n ; ++i )                              \
        ptr[i] = COEF_FROM_FLOAT( flt[i] ); }

#endif

#else

#define DBG_REFRESH_FWTXFM()

#endif



// forward transform for channel (MCLT)
INLINE
Void cxMCLTTile(CAudioObject *pau, CoefType *pBuf, ReconTileInfo *prti)
{
    pau->m_pfnApplyWindow(pau, pBuf,
                          prti->m_iSizePrev,
                          prti->m_iSizeCurr,
                          prti->m_iSizeNext,
                          WMAB_FALSE);

    auApplyReflectionV3(pBuf, prti->m_iSizeCurr);
    
    catchFP();
        
    chexDctHelper(pau, pau->m_rgpcinfo, pBuf, 
                  BP2_FROM_FLOAT(1),
                  prti->m_iSizeCurr);

    chexDstHelper(pau, pau->m_rgpcinfo,
                  pBuf+prti->m_iSizeCurr, 
                  BP2_FROM_FLOAT(1),
                  prti->m_iSizeCurr);
    initFP();

    DBG_REFRESH_FWTXFM();
}

INLINE
Void cxMLTTile(CAudioObject *pau, CoefType *pBuf, ReconTileInfo *prti)
{
#if defined(CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL) && CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL
    if (256 == prti->m_iSizeCurr &&
        256 == prti->m_iSizePrev &&
        256 == prti->m_iSizeNext)
    {
        // specialized MLT for (256, 256, 256) combining
        // (window, reflection, and pre-twiddle) into single step
        // followed by FFT followed by post-twiddle
        chexWindowReflectionAndDct256(pau, pau->m_rgpcinfo,
                                      pBuf, 
                                      BP2_FROM_FLOAT(1.0f),
                                      prti->m_iSizeCurr);
    }
    else
#endif  // CHEX_WINDOW_REFLECTION_DCT_LOOKUPTBL
    {
        // forward transform for channel (MCLT)
        pau->m_pfnApplyWindow(pau, pBuf,
                              prti->m_iSizePrev,
                              prti->m_iSizeCurr,
                              prti->m_iSizeNext,
                              WMAB_FALSE);

        // only need to do first portion of refelection here
        auApplyReflectionV3(pBuf, prti->m_iSizeCurr);

        chexDctHelper(pau, pau->m_rgpcinfo, pBuf, 
                    BP2_FROM_FLOAT(1),
                    prti->m_iSizeCurr);
    }

    DBG_REFRESH_FWTXFM();
}

WMARESULT chexIMCLTTile(CAudioObject *pau,
                        PerChannelInfo *ppcinfo,
                        ReconTileInfo *prti,
                        Bool bMCLT,
                        CoefType *pBuf, // transform coeff buffer
                        CoefType *pOut, // output samples
                        CoefType *pHist) // history buffer
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    CoefType *pHistDST = pHist + prp->m_cFrameSampleHalfChex/2;
    CoefType *pBufDST = pBuf + prti->m_iSizeCurr;
    const BP2Type fDecScale = BP2_FROM_FLOAT(1.0f) / prti->m_iSizeCurr * 2;

#if (IMCLT_MAXN != 0)
    if (pau->m_fIntelCcsFFT && !pau->m_bEncoder && bMCLT
        && (prti->m_iSizePrev == prti->m_iSizeCurr)
        && (prti->m_iSizeCurr == prti->m_iSizeNext)
        && (prti->m_iSizeCurr <= IMCLT_MAXN))
    {
        // Direct inverse MCLT
        AecCcsInvMclt(pau, prti->m_iSizeCurr, pBuf);

        if (ppcinfo->m_fHistIsMCLT)
        {
            auOverlapAddV3DirectMCLT(pOut, pHist, pBuf, prti->m_iSizeCurr);
        }
        else
        {
            auOverlapAddV3DirectMCLTHistDCTDSTWrap(pau, pOut, pHist,
                                                   pBuf, pHistDST, 0,
                                                   prti->m_iSizePrev,
                                                   prti->m_iSizeCurr,
                                                   WMAB_FALSE);
        }

        memcpy(pHist, pBuf + prti->m_iSizeCurr,
               prti->m_iSizeCurr * sizeof(CoefType));
        ppcinfo->m_fHistIsMCLT = WMAB_TRUE;
    }
    else
#endif // IMCLT_MAXN != 0
    {
        // overlap add into output buffer
        // inverse transform (DCT)

        catchFP();
        chexDctHelper(pau, ppcinfo, pBuf, fDecScale, prti->m_iSizeCurr);
        initFP();

        if (bMCLT)
        {
            // Use MCLT
            chexDstHelper(pau, ppcinfo, pBufDST, fDecScale, prti->m_iSizeCurr);
            initFP();

            TRACEWMA_EXIT(wmaResult,
                          auOverlapAddV3(pau, pOut,
                                         pHist, pBuf, pHistDST, pBufDST,
                                         prti->m_iSizePrev, prti->m_iSizeCurr,
                                         ppcinfo->m_fHistIsMCLT, WMAB_TRUE, 0,
                                         WMAB_FALSE));

            auShiftHistoryV3(pHistDST, pBufDST, prti->m_iSizeCurr, 0);
        }
        else
        {
            // Use MLT
            TRACEWMA_EXIT(wmaResult,
                          auOverlapAddV3(pau, pOut, pHist, pBuf, NULL, NULL,
                                         prti->m_iSizePrev, prti->m_iSizeCurr,
                                         WMAB_TRUE, WMAB_FALSE, 0,
                                         WMAB_FALSE));
        }

        // shift history
        auShiftHistoryV3(pHist, pBuf, prti->m_iSizeCurr, 0);
        ppcinfo->m_fHistIsMCLT = WMAB_FALSE;
    }

exit:
    return wmaResult;
}

WMARESULT chexCreateMono(CAudioObject *pau,
                         ReconTileInfo *prti,
                         Bool bMLT, Int iCh0, Int iCh1)
{
    // create mono from "start band" up to "max start band+1"
    WMARESULT wmaResult = WMA_OK;
    Chex *pcx = pau->m_pcx;
    Int iStart, iEnd, iStartBand, iCoeff;

#if (CX_DECODE_MONO==1)
    goto exit;
#else
    if (!pau->m_bCx || pau->m_bIgnoreCx)
        goto exit;

    if (pau->m_cOrigChannel != pau->m_cCodedChannel)
        goto exit;

    if (chexInfoStatNoCx(prti->m_uInfoStat))
        goto exit;

    if (prti->m_pcxartiSeg == NULL)
    {
        // Prevent null pointer dereferencing below...
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    iStartBand = CHEX_RECON_STARTBAND(prti);
    assert(pcx->m_iMaxStartBandCurr >= iStartBand);
    if (pcx->m_iMaxStartBandCurr <= iStartBand)
        goto exit;
#endif

    iStart = pcx->m_rgiBandStart[iStartBand];
    iEnd = pcx->m_rgiBandStart[pcx->m_iMaxStartBandCurr];
    iEnd = min(iEnd, prti->m_iSizeCurr);

    // fwd xform
    TRACEWMA_EXIT(wmaResult,
                  chexGetSamplesFromPCMBuf(pau, pau->m_rgpcinfo+iCh1, iCh1,
                                           prti, pau->m_rgCoefXFormMCLTDiff));

    if (bMLT)
        cxMLTTile (pau, pau->m_rgCoefXFormMCLTDiff, prti);
    else
        cxMCLTTile(pau, pau->m_rgCoefXFormMCLTDiff, prti);

    for (iCoeff=iStart; iCoeff < iEnd; iCoeff++)
    {
#if defined(BUILD_INTEGER)
        pau->m_rgCoefXFormMCLT[iCoeff] =
            ((pau->m_rgCoefXFormMCLT[iCoeff]>>1) +
             (pau->m_rgCoefXFormMCLTDiff[iCoeff]>>1));
#else
        pau->m_rgCoefXFormMCLT[iCoeff] += pau->m_rgCoefXFormMCLTDiff[iCoeff];
        pau->m_rgCoefXFormMCLT[iCoeff] *= 0.5f;
#endif
    }

exit:
    return wmaResult;
}

// recon tile using forward transform, process, inverse transform
// suppose the maximum subframe size for CHEX is M samples, then at
// most we will need (2M) samples for a forward transform (curr+prev/2+next/2)
// and will need to store at most M samples for history (curr/2+next/2)
// since we don't want to invert the forward transform after completing,
// we will first store (curr/2+next/2) in the beginning of buffer and then
// process
//
// suppose m_rgCoefMCLT is buffer of size (3M)
// data needed for forward transform starts at M and is of size (2*curr)

WMARESULT chexProcessTileMLT(CAudioObject *pau, 
                          ReconTileInfo *prti,
                          ReconTileInfo *prtiPrev);

// MCLT processing or just MLT processing
WMARESULT chexProcessTile(CAudioObject *pau, 
                          ReconTileInfo *prti,
                          ReconTileInfo *prtiPrev)
{
    WMARESULT wmaResult = WMA_OK;

    ReconProc *prp = pau->m_prp;
    Chex *pcx =  pau->m_pcx;
    Fex *pfx  = &pau->m_fex;
    PerChannelInfo *ppcinfo;
    ReconTileInfo *prtiNext = chexNextTile(prp, prti);
    CxAnchorReconTileInfo *pcxartiCode = prti->m_pcxartiCode;

    const Int iSizePrev = prti->m_iSizePrev;
    const Int iSizeCurr = prti->m_iSizeCurr;
    const Int iSizeNext = prti->m_iSizeNext;
    const Int iSamples = (iSizePrev+iSizeCurr)/2;

    // copy last (next) samples to beginning of buffer so
    // that the first (next) amount of samples can be applied to next subframe

    const Int iCopyAmt   = iSizeNext/2 + min(iSizeNext, iSizeCurr)/2;
    const Int iCopyStart = iSizeNext - iCopyAmt;

    Int iStartPrev, iEndPrev, iStartCurr, iEndCurr;
    Int iCh, iNoCodeCh, iPCMDiff;

    // chexProcessTile() pipeline truth table.

    // =======================================================================
    //  v2 PLUS MODE   | use DCT | use DST | save DCT | obt.DST | shift buf
    //------------------------------------------------------------------------
    //    cx only      |    1    |    1    |    0     |    0    |    0
    //------------------------------------------------------------------------
    //    rx only      |    1    |    0    |    0     |    0    |    0
    //------------------------------------------------------------------------
    //    rx + cx      |    1    |    1    |    0     |    1    |    1
    //------------------------------------------------------------------------
    // rx+cx, MLT pass |    1    |    0    |    1     |    0    |    0
    // =======================================================================

    // bObtainDSTFromDCT is misnamed, it should be bObtainDSTfromIDCT,
    // because it is using the post-reconFex inverse DCT ( PCM ) data.

#if (CX_DCT_ONLY==1)
    const Bool bShiftDCTBuf      = WMAB_FALSE;
    const Bool bObtainDSTFromDCT = WMAB_FALSE;
    const Bool bUseDSTRecon      = WMAB_FALSE;
#else
    const Bool bShiftDCTBuf      = pau->m_bCx && pau->m_bReconFex;
    const Bool bObtainDSTFromDCT = pau->m_bCx && pau->m_bReconFex;
    const Bool bUseDSTRecon      = pau->m_bCx;
#endif

    Bool bHaveDST = WMAB_FALSE;
    Bool bCxTile  = WMAB_FALSE;
    Bool bRFxTile = WMAB_FALSE;

    initFP();
    // make sure this tile is valid
    if (chexTileNotInUse(prti))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    // at least one of either reconFex or chex must be enabled.
    assert( pau->m_bReconFex || pau->m_bCx  || pau->m_bReconProc );

#if (CX_DCT_ONLY==0)
    if( pau->m_bReconFex && pau->m_bCx )
    {
        // if both reconFex and chex are enabled, then we need 
        // to get the post-reconFex PCM data for this tile and
        // the next. this PCM data is used to generate the DST 
        // portion of the MCLT. 

        if (!chexInfoStatMLTProc(prti->m_uInfoStat))
        {   // do MLT processing on the current tile
            TRACEWMA_EXIT(wmaResult, chexProcessTileMLT(pau, prti, prtiPrev));
        }

        if (prtiNext != NULL)
        {   // do MLT processing on next tile
            TRACEWMA_EXIT(wmaResult, chexProcessTileMLT(pau, prtiNext, prti));
        }
        else
        {   // clear the buffer.
            reconProcZeroDCTBuf(pau, prti);
        }

        // at this point, MLT processing is complete for
        // both the current tile & the next, so revert to
        // full processing ( include the chex portion ).
    }
#endif

    if (pau->m_bCx && (!pcxartiCode || pcxartiCode->m_bCxInterpolate))
    {

        pcx->m_prtiNextCodedTile = chexNextCodedTile(prp, prti);
        pcx->m_bNoNextCodedTile = WMAB_FALSE;
        if (NULL == pcx->m_prtiNextCodedTile)
        {
            // assert(WMAB_FALSE);
            // following is for safety
            pcx->m_prtiNextCodedTile = prti;
            pcx->m_bNoNextCodedTile = WMAB_TRUE;
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        assert(NULL != pcx->m_prtiNextCodedTile);
        if (pcx->m_prtiNextCodedTile != prti)
        {
            pcx->m_prtiLastCodedTileInSeg =
                chexPrevTile(prp, pcx->m_prtiNextCodedTile);
            assert(NULL != pcx->m_prtiLastCodedTileInSeg);
        }
    }

    assert(chexTileReadyForRecon(prp, prti) ||
           prp->m_bLastTile ||
           pcx->m_bNoNextCodedTile);

    if( chexInfoStatCode(prti->m_uInfoStat) && pau->m_bCxPresent )
    {
        assert(!chexInfoStatNoCx(prti->m_uInfoStat));
        bCxTile = WMAB_TRUE;
    }
    else
    {
        assert( chexInfoStatNoCx(prti->m_uInfoStat) || !pau->m_bCxPresent );
        bCxTile = WMAB_FALSE;
    }

    if (pau->m_bIgnoreCx)
        bCxTile = WMAB_FALSE;

    if (pau->m_bReconFexPresent &&
        (chexInfoStatCodeFx(prti->m_uInfoStat) ||
         chexInfoStatCodeBs(prti->m_uInfoStat)))
    {
        assert(!chexInfoStatNoFx(prti->m_uInfoStat) || pfx->m_iVersion > 2);
        bRFxTile = WMAB_TRUE;
    }
    else
    {
        if (!chexInfoStatNoFx(prti->m_uInfoStat) && pau->m_bReconFex &&
               !prp->m_bLastTile)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        bRFxTile = WMAB_FALSE;
    }

    // uncomment below to skip Rfx or Cx part in decoder.
    //bRFxTile = 0;
    //bCxTile = 0;

#if (CX_DCT_ONLY==0)
    if( pau->m_bReconFex && pau->m_bCx )
    {
        // reconFex work was completed in MLT pass.
        bRFxTile = WMAB_FALSE;
    }

    // this code is not designed to perform
    // both Cx & RFx processes in the same pass.

    assert( !( bCxTile && bRFxTile ) );
#endif

    // recon
    iNoCodeCh = 0;
    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        const Int iFexCh = chexGetFexChannel( pau, iCh );
        PerChannelInfo *ppcinfoFex = pau->m_rgpcinfo + iFexCh;

        if (iFexCh < 0)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        
        if (0 == (prti->m_uChannelMask & (1<<iCh)))
            continue;

        ppcinfo = pau->m_rgpcinfo + iCh;

        if (WMAB_FALSE == bObtainDSTFromDCT && WMAB_FALSE == bHaveDST)
        {
            // Used if only recon fex is being used
            TRACEWMA_EXIT(wmaResult,
                chexGetSamplesFromPCMBuf(pau, ppcinfo, iCh, prti,
                                     pau->m_rgCoefXFormMCLT));

#if defined(CX_LOW_POWER)
            assert(0 == iCh || pau->m_bCx == WMAB_FALSE);
#endif

            DBG_CX_REFRESH(PCM);

            prvDumpVals("out2.raw", "wb", 2*prti->m_iSizeCurr,
                        pau->m_rgCoefXFormMCLT);

            auPreScaleCoeffsLBR( pau, prti );

            if (bUseDSTRecon)
                cxMCLTTile(pau, pau->m_rgCoefXFormMCLT, prti);
            else
                cxMLTTile (pau, pau->m_rgCoefXFormMCLT, prti);

            // chexCreateMono does nothing under CX_DECODE_MONO

            if (0 == iCh)
                chexCreateMono(pau, prti, !bUseDSTRecon, 0, 1);
            else
                chexCreateMono(pau, prti, !bUseDSTRecon, 1, 0);

            auPostScaleCoeffsLBR( pau, prti );

            DBG_CX_REFRESH(FWDMLT);

#if defined(ALLOW_EXTERNAL_FILE_FOR_RECON)
            if (WMAB_TRUE == g_bReplaceForChex)
            {
#if 1
                prvReplaceSamplesFromFileReconProc(pau, prti, iCh,
                                                   pau->m_rgCoefXFormMCLT,
                                                   -1, -1);
#else
                prvReplaceSamplesFromFileReconProc(pau, prti, iCh,
                                                   pau->m_rgCoefXFormMCLT,
                                                   3000.0f, 5000.0f);
#endif
            }
#endif
#if defined(CXTEST_NOQUANT)
            prvReplaceSamplesFromFileReconProc(pau, prti, iCh,
                                               pau->m_rgCoefXFormMCLT,
                                               -1, -1);
#endif
#if (CX_DCT_ONLY==0)
            if (pau->m_bCx && CHEX_FULL_SPECTRUM(prti))
            {
                memcpy(pau->m_rgDCTBuf,
                       pau->m_rgCoefXFormMCLT,
                       prti->m_iSizeCurr*sizeof(CoefType));
                memcpy(pau->m_rgCoefXFormDST,
                       pau->m_rgCoefXFormMCLT+prti->m_iSizeCurr,
                       prti->m_iSizeCurr*sizeof(CoefType));
                bHaveDST = WMAB_TRUE;
            }
#endif
        }
        else if (WMAB_FALSE == bObtainDSTFromDCT && bHaveDST)
        {
            memcpy(pau->m_rgCoefXFormMCLT,
                   pau->m_rgDCTBuf,
                   prti->m_iSizeCurr*sizeof(CoefType));
#if (CX_DCT_ONLY==0)
            memcpy(pau->m_rgCoefXFormMCLT+prti->m_iSizeCurr,
                   pau->m_rgCoefXFormDST,
                   prti->m_iSizeCurr*sizeof(CoefType));
#endif
        }
        else if( !bHaveDST || !CHEX_FULL_SPECTRUM(prti) )
        {
            // Used for first channel in chex + [recon fex (optional)]

            // reconstruct this channel's DST from the DCT of the
            // FEX channel. If this is the FEX channel, then the
            // ppcinfo ptrs should be equal. this allows the DCT, 
            // reconFex, & iDCT work to be re-used.

            assert( iFexCh != iCh || ppcinfo == ppcinfoFex );

            reconProcGetDSTDCTFromDCTBuf(pau, ppcinfo, prti,
                                         pau->m_rgCoefXFormMCLT);

            if (CHEX_FULL_SPECTRUM(prti))
                memcpy(pau->m_rgCoefXFormDST,
                       pau->m_rgCoefXFormMCLT+prti->m_iSizeCurr,
                       prti->m_iSizeCurr*sizeof(CoefType));

            bHaveDST = WMAB_TRUE;
        }
        else
        {
            // Used for second channel in chex + [recon fex (optional)]
            memcpy(pau->m_rgCoefXFormMCLT,
                   ppcinfoFex->m_ppcinfoShr->m_pDCTBufCurr,
                   prti->m_iSizeCurr*sizeof(CoefType));
#if (CX_DCT_ONLY==0)
            memcpy(pau->m_rgCoefXFormMCLT+prti->m_iSizeCurr,
                   pau->m_rgCoefXFormDST,
                   prti->m_iSizeCurr*sizeof(CoefType));
#endif
        }

#ifdef CHEX_VERIFY
        // this is what encoder used to compute coefficients
        prvDumpVals("outdct.raw", "wb", prti->m_iSizeCurr, prti->m_DCT);
        // this is what recon is using for recon, if replacement file used
        // for recon, this is from replaced file, forward of mono
        prvDumpVals("outdct.raw", "ab", prti->m_iSizeCurr,
                    pau->m_rgCoefXFormMCLT);
#endif
        // recon for recon-domain fex
        if (bRFxTile && (iFexCh==iCh || !CHEX_FULL_SPECTRUM(prti)))
        {
            // pau->m_rgCoefXFormMCLTDiff used as temp buffer
            TRACEWMA_EXIT(wmaResult,
                          chexReconReconFex(pau, ppcinfo, iCh, prti,
                                            pau->m_rgCoefXFormMCLT,
                                            pau->m_rgCoefXFormMCLT,
                                            pau->m_rgCoefXFormMCLTDiff));
        }

        if (iCh == 0)
            DBG_CX_REFRESH(RFX);

#if (CX_DCT_ONLY==1)
        if (pau->m_bCx && WMAB_FALSE==bHaveDST)
        {
            memcpy(pau->m_rgDCTBuf,
                   pau->m_rgCoefXFormMCLT,
                   prti->m_iSizeCurr*sizeof(CoefType));
            if (CHEX_FULL_SPECTRUM(prti))
                bHaveDST = WMAB_TRUE;
        }
#endif

        // recon for each channel
        if (bCxTile)
        {
            TRACEWMA_EXIT(wmaResult,
                          chexReconCh(pau, prti, iCh, pau->m_rgCoefXFormMCLT,
                                      pau->m_rgCoefXFormMCLTDiff));
        }

        DBG_CX_REFRESH(CX)

#if defined(CHEX_VERIFY)
        chexDumpOrigNew(pau, prti, iCh, pau->m_rgCoefXFormMCLT,
                        WMAB_TRUE, WMAB_TRUE);
#endif

#if (CX_DECODE_MONO==1)
        if (ppcinfo->m_bNoDecodeForCx)
        {
            // use separate buffer, since rgCoefRecon does not exist
            ppcinfo->m_rgCoefSampMCLT =
                pau->m_rgCoefSampMCLT + prp->m_cFrameSampleHalfChex*iNoCodeCh;
            iNoCodeCh++;
        }
        else
#endif
        {
            // use same buffer as rgCoefRecon
            ppcinfo->m_rgCoefSampMCLT =
                ppcinfo->m_rgPCMBuf + prp->m_iRecon - prp->m_rgiPCMStart[iCh];
            iPCMDiff = (Int)((ppcinfo->m_rgPCMBuf + prp->m_iPCMSize) - 
                             (ppcinfo->m_rgCoefSampMCLT +
                              prti->m_iSizePrev/2 + prti->m_iSizeCurr/2));
            // the following makes it harder to put chex tile processing
            // in audecDecode, but can be done by increasing buffer size
            // this only happens if CX_DCT_ONLY==0
            if (iPCMDiff < 0)
                ppcinfo->m_rgCoefSampMCLT += iPCMDiff;
        }

        chexIMCLTTile(pau, ppcinfo, prti, bUseDSTRecon,
                      pau->m_rgCoefXFormMCLT, ppcinfo->m_rgCoefSampMCLT,
                      ppcinfo->m_rgCoefHistMCLT);

#if defined(CHEX_VERIFY)
        chexDumpOrigNew(pau, prti, iCh, pau->m_rgCoefXFormMCLT,
                        WMAB_FALSE, WMAB_FALSE);
#endif

        auIntFromCoeff(pau, ppcinfo->m_rgCoefSampMCLT, iSamples);
        ppcinfo->m_rgCoefSampMCLTCurr = ppcinfo->m_rgCoefSampMCLT;

        // 2nd half of prev
        prp->m_rgiPCMSamplesReady[iCh] +=
            chexGet2ndHalfPts(prtiPrev, &iStartPrev, &iEndPrev);
        ppcinfo->m_rgCoefSampMCLTCurr +=
            (iStartPrev-prtiPrev->m_iSizeCurr/2);

        // 1st half of curr
        prp->m_rgiPCMSamplesReady[iCh] +=
            chexGet1stHalfPts(prti, &iStartCurr, &iEndCurr);

        if (iStartPrev==prtiPrev->m_iSizeCurr)
        {
            ppcinfo->m_rgCoefSampMCLTCurr += iStartCurr;
        }
        else if (iStartCurr != 0 || prtiPrev->m_iSizeCurr != iEndPrev)
        {
            Int iGap = prtiPrev->m_iSizeCurr-iEndPrev+iStartCurr;
            memmove(ppcinfo->m_rgCoefSampMCLTCurr+(iEndPrev-iStartPrev),
                    ppcinfo->m_rgCoefSampMCLTCurr+(iEndPrev-iStartPrev)+iGap,
                    (iEndCurr-iStartCurr)*sizeof(CoefType));
        }
    } // for (iCh=...)

    if (WMAB_FALSE==pau->m_bCx)
    {
        // No MLT pass taken place, rfx happening here
        rfxReleaseTiles(prp, prti);
        prp->m_iDecodeRFxTileInFrame++;
    }

    if( bShiftDCTBuf )
    {
        // shift the DCT buffer after processing all
        // channels instead of during. this allows the
        // DCT data to be re-used from the FEX base
        // channel onto those channels it extends to.

        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            if (0 == (prti->m_uChannelMask & (1<<iCh))) continue;
            reconProcShiftDCTBufs(pau, pau->m_rgpcinfo + iCh);
        }
    }
    
    prp->m_iEndOutPt += iSamples;
    prp->m_iRecon += iSamples;

exit:

    return wmaResult;
}

// MLT only processing in case both MLT + MCLT processing is being done
WMARESULT chexProcessTileMLT(CAudioObject *pau, 
                          ReconTileInfo *prti,
                          ReconTileInfo *prtiPrev)
{
    WMARESULT wmaResult = WMA_OK;

    ReconProc *prp = pau->m_prp;
    Chex *pcx =  pau->m_pcx;
    Fex *pfx  = &pau->m_fex;
    PerChannelInfo *ppcinfo;
    ReconTileInfo *prtiNext = chexNextTile(prp, prti);
    CxAnchorReconTileInfo *pcxartiCode = prti->m_pcxartiCode;

    const BP2Type fDecScale = BP2_FROM_FLOAT(1.0f) / prti->m_iSizeCurr * 2;
    const BP2Type fRFxScale = BP2_FROM_FLOAT(1.0f);

    Int iCh;

    Bool bRFxTile = WMAB_FALSE;

    initFP();

    // both reconFex and chex must be enabled.
    assert( pau->m_bReconFex && pau->m_bCx );

    assert(chexTileReadyForReconNoCx(prp, prti) ||
           prp->m_bLastTile);

    if (pau->m_bReconFexPresent &&
        (chexInfoStatCodeFx(prti->m_uInfoStat) ||
         chexInfoStatCodeBs(prti->m_uInfoStat)))
    {
        assert(!chexInfoStatNoFx(prti->m_uInfoStat) || pfx->m_iVersion > 2);
        bRFxTile = WMAB_TRUE;
    }
    else
    {
        assert(chexInfoStatNoFx(prti->m_uInfoStat) || !pau->m_bReconFex ||
               prp->m_bLastTile);
        bRFxTile = WMAB_FALSE;
    }

    // uncomment below to skip Rfx part in decoder.
    //bRFxTile = 0;

    // MLT pass does not include chex work.
    chexSetInfoStatMLTProc(&prti->m_uInfoStat);

    // recon
    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        const Int iFexCh = chexGetFexChannel( pau, iCh );
        PerChannelInfo *ppcinfoFex = pau->m_rgpcinfo + iFexCh;
        if (iFexCh < 0)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
       

        if (0 == (prti->m_uChannelMask & (1<<iCh)))
            continue;

        // if this is the reconFex pass over
        // a channel other than the base FEX
        // channel, then skip some processes.

        if (iFexCh != iCh && CHEX_FULL_SPECTRUM(prti))
            continue;

        ppcinfo = pau->m_rgpcinfo + iCh;

        TRACEWMA_EXIT(wmaResult,
                      chexGetSamplesFromPCMBuf(pau, ppcinfo, iCh, prti,
                                               pau->m_rgCoefXFormMCLT));

        prvDumpVals("out2.raw", "wb", 2*prti->m_iSizeCurr,
                    pau->m_rgCoefXFormMCLT);

        auPreScaleCoeffsLBR( pau, prti );

        // forward transform for channel (MCLT)
        cxMLTTile(pau, pau->m_rgCoefXFormMCLT, prti);

        if (0 == iCh)
            chexCreateMono(pau, prti, WMAB_TRUE, 0, 1);
        else
            chexCreateMono(pau, prti, WMAB_TRUE, 1, 0);

        auPostScaleCoeffsLBR( pau, prti );

        // recon for recon-domain fex
        if (bRFxTile)
        {
            // pau->m_rgCoefXFormMCLTDiff used as temp buffer
            TRACEWMA_EXIT(wmaResult,
                          chexReconReconFex(pau, ppcinfo, iCh, prti,
                                            pau->m_rgCoefXFormMCLT,
                                            pau->m_rgCoefXFormMCLT,
                                            pau->m_rgCoefXFormMCLTDiff));
        }

        catchFP();
        reconProcAddDCTBuf(pau, ppcinfo, prtiPrev, pau->m_rgCoefXFormMCLT);
        chexDctHelper(pau, ppcinfo, pau->m_rgCoefXFormMCLT,
                      fDecScale, prti->m_iSizeCurr);
        reconProcAddIDCTBuf(pau, ppcinfo, prtiPrev,pau->m_rgCoefXFormMCLT);
        initFP();

    } // for (iCh=...)

    rfxReleaseTiles(prp, prti);

    prp->m_iDecodeRFxTileInFrame++;

exit:
    return wmaResult;
}

INLINE Int reconProcGetReconPos(CAudioObject *pau, ReconProc *prp)
{
    Int iPos;

#if (CX_DCT_ONLY==0)
    if (pau->m_bCx && pau->m_bReconFex)
        iPos = chexOffsetBuf(prp, prp->m_iBufCodeFxPos,
                             -prp->m_iTilesInSubframeCodeFx-1);
    else
#endif
        iPos = chexOffsetBuf(prp, prp->m_iBufCodeFxPos,
                             -prp->m_iTilesInSubframeCodeFx);

    return iPos;
}

Void reconProcReleaseTiles(CAudioObject *pau,
                           ReconTileInfo *prti);

// process any tiles that did not get processed, basically release them
// can also use this at encoder if only cx being used without recon buffer
WMARESULT reconProcessUnprocessedTiles(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Int iPos, iTiles, i, iReconPos, iPrevPos;
    ReconTileInfo *prti, *prtiNext, *prtiPrev;
    Bool bJustRelease = WMAB_FALSE;

    if (WMAB_FALSE==pau->m_bReconProc || prp->m_bFirstTile)
        goto exit; // nothing has been added as of yet into tile buffer

    // this is actual recon pos
    iPos = prp->m_iBufReconPos;
    // this is what recon pos should be
    iReconPos = prp->m_iBufCodeFxPos;
#if (CX_DCT_ONLY==0)
    if (pau->m_bCx && pau->m_bReconFex)
        iReconPos = chexOffsetBuf(prp, iReconPos, -1);
#endif

    if (prp->m_bLastTile)
    {
        // release all unprocessed tiles in buffer
        assert(!pau->m_bEncoder);
        iReconPos = prp->m_iBufAddPos;
        prp->m_iBufCodeFxPos = iReconPos;
        prp->m_iBufCalcFxPos = iReconPos;
        memset(prp->m_rgiTilesInSubframeAdd, 0, 4*sizeof(Int));
        chexClearReverbHistory(pau);
        if (pau->m_bCx)
        {
            ReconTileInfo *prtiCxPrev =
                prp->m_rgchextiBuf + chexOffsetBuf(prp, iReconPos, -1);
            chexReleaseCxCodeAnchor(prtiCxPrev);
            prtiCxPrev->m_iTilesInCoding = 0;
        }
        memset(pau->m_rgDCTBuf, 0, sizeof(CoefType)*prp->m_iDCTBufSize);
        memset(pau->m_rgiCoefReconOrig, 0, sizeof(CBT)*pau->m_iCoefReconSize);
        bJustRelease = WMAB_TRUE;
    }

    iTiles = iReconPos - iPos;
    if (iTiles < 0)
        iTiles += prp->m_nTilesInBuf;

    if (pau->m_bEncoder && WMAB_TRUE==prp->m_bNoRecon)
        bJustRelease = WMAB_TRUE;

    iPrevPos = chexOffsetBuf(prp, iPos, -1);

    if (pau->m_bCx)
        cxUpdateCurrMaxStartBand(pau->m_pcx);

#if (CX_DCT_ONLY==0)
    prti = prp->m_rgchextiBuf + iPos;
    if (pau->m_bCx && pau->m_bReconFex && 0==iTiles &&
        !chexInfoStatMLTProc(prti->m_uInfoStat))
    {
        if (bJustRelease)
        {
            chexSetInfoStatMLTProc(&prti->m_uInfoStat);
            rfxReleaseTiles(prp, prti);
        }
        else
        {
            prtiPrev = prp->m_rgchextiBuf + iPrevPos;
            chexProcessTileMLT(pau, prti, prtiPrev);
        }
    }
#endif

    for (i=0; i < iTiles; i++)
    {
        prti = prp->m_rgchextiBuf + iPos;
        prtiPrev = prp->m_rgchextiBuf + iPrevPos;
        prtiNext = chexNextTile(prp, prti);

        if (!chexInfoStatAdd(prti->m_uInfoStat))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        if (bJustRelease)
        {
            if (pau->m_bReconFex && pau->m_bCx)
            {
                //assert(prtiNext);

                if (!chexInfoStatMLTProc(prti->m_uInfoStat))
                {
                    // do MLT processing on the current tile
                    chexSetInfoStatMLTProc(&prti->m_uInfoStat);
                    rfxReleaseTiles(prp, prti);
                }

                if (prtiNext)
                {
                    chexSetInfoStatMLTProc(&prtiNext->m_uInfoStat);
                    rfxReleaseTiles(prp, prtiNext);
                }
            }

            if (WMAB_FALSE==pau->m_bCx)
                // No MLT pass taken place, rfx happening here
                rfxReleaseTiles(prp, prti);

            prp->m_iEndOutPt += (prtiPrev->m_iSizeCurr+prti->m_iSizeCurr)/2;
        }
        else
        {
            TRACEWMA_EXIT(wmaResult, chexProcessTile(pau, prti, prtiPrev));
        }

        reconProcReleaseTiles(pau, prti);

        iPrevPos = iPos;
        iPos = chexOffsetBuf(prp, iPos, 1);
    }

    prp->m_iBufReconPos = iPos;

    assert(prp->m_iBufReconPos == iReconPos);

exit:
    return wmaResult;
}

// this is how many samples we can output with what information we have
Int chexGetSamplesReady(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;
    Int iPos, iTiles, i, iStart, iEnd, iPrevPos;
    ReconTileInfo *prti=0, *prtiPrev=0;

    iTiles = prp->m_iTilesInSubframeCodeFx;
    iPos = reconProcGetReconPos(pau, prp);
    iPrevPos = chexOffsetBuf(prp, iPos, -1);

    prp->m_cSamplesReady = 0;

    for (i=0; i < iTiles; i++)
    {
        prti = prp->m_rgchextiBuf + iPos;
        prtiPrev = prp->m_rgchextiBuf + iPrevPos;
        if (chexInfoStatAdd(prtiPrev->m_uInfoStat))
            prp->m_cSamplesReady += chexGet2ndHalfPts(prtiPrev, &iStart, &iEnd);
        if (chexInfoStatAdd(prti->m_uInfoStat))
            prp->m_cSamplesReady += chexGet1stHalfPts(prti, &iStart, &iEnd);
        iPrevPos = iPos;
        iPos = chexOffsetBuf(prp, iPos, 1);
    }

    if (WMAB_TRUE == prp->m_bLastTile)
    {
        Int cSamplesReadyOrig=prp->m_cSamplesReady;
        Int cSamplesToGo;

        prp->m_cSamplesReady =
            prp->m_rgiPCMEndReconPoint[0] - 
            prp->m_iTrailingSize - 
            prp->m_iEndOutPt;

        cSamplesToGo = prp->m_cSamplesReady - cSamplesReadyOrig;
        if (0 == iTiles)
            prti = prp->m_rgchextiBuf + iPos;
        if (chexInfoStatAdd(prti->m_uInfoStat))
            cSamplesToGo += chexGet1stHalfPts(prti, &iStart, &iEnd);
        while (prti && chexInfoStatAdd(prti->m_uInfoStat))
        {
            prti->m_iEnd = checkRange(cSamplesToGo,
                                      prti->m_iStart, prti->m_iEnd);
            cSamplesToGo -= (prti->m_iEnd - prti->m_iStart);
            prti = chexNextTile(prp, prti);
        }
    }

    return max(0, prp->m_cSamplesReady);
}

Int chexCalcSamplesReady(Int *piSamplesReady, Int nCh)
{
    Int cSamplesReady, i;

    cSamplesReady = piSamplesReady[0];
    for (i=1; i < nCh; i++)
        cSamplesReady = min(cSamplesReady, piSamplesReady[i]);
    return cSamplesReady;
}

Void chexRemoveSamplesReady(Int *piSamplesReady, Int nCh, Int cSamples)
{
    Int i;
    for (i=0; i < nCh; i++)
        piSamplesReady[i] -= cSamples;
}

Void reconProcReleaseTiles(CAudioObject *pau,
                           ReconTileInfo *prti)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prtiPrev;

    // release this anchor
    chexReleaseCxAnchor(prti);

    prtiPrev = chexPrevTile(prp, prti);
    if (WMAB_FALSE == pau->m_bReconFex ||
        NULL == prti->m_prfxrti ||
        WMAB_TRUE == prti->m_prfxrti->m_bLastTileInFrame)
    {
        while (prtiPrev != NULL)
        {
            ReconTileInfo *prtiPrevPrev;

            prtiPrevPrev = chexPrevTile(prp, prtiPrev);
            chexSetTileNotInUse(prp, prtiPrev);
            prtiPrev = prtiPrevPrev;
        }
        rfxReleaseTileInfo(prti);
    }
}

WMARESULT chexGetPCM(CAudioObject *pau,  // [in]  the audio structure
                   Void *pHandle,      // [in]  the caller (encoder/decoder)
                   U16 *pcSample,      // [in/out] number of output samples
                   U8 **ppbDst,        // [in/out] output buffer
                   U32 cbDstLength,    // [in] the output buffer length
                   U16 cChannel,       // [in] the number of channels
                   Bool fSPDIF)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Int cSamplesReady, cSamplesRecon, iCh;
    ReconTileInfo *prti, *prtiNext, *prtiPrev;
    PCMSAMPLE *piOutputCurr;
    Int iBytesProduced;
    Int cSamples = *pcSample;
    Int cSamplesOut = 0;
    PCMSAMPLE *piOutput = (PCMSAMPLE*)ppbDst[0];
    U16 cChannelTemp;
    U32 cMaxSamplesInDst = (cbDstLength/pau->m_nBytePerSample/pau->m_cChannel);
    Int cSamplesReconTemp;
    FN_CNT;

    if (WMAB_TRUE == pau->m_bEncoder)
    {
        // Encoder
        if (pau->m_fTrailingSilence)
        {
            Int iLast;
            prp->m_bLastTile = WMAB_TRUE;
            prp->m_iTrailingSize = (Int)pau->m_u32TrailingSize;
            // set last tile flag
            iLast = chexOffsetBuf(prp, prp->m_iBufCodePos, -1);
            chexSetInfoStatLastTile(&prp->m_rgchextiBuf[iLast].m_uInfoStat);
        }
        TRACEWMA_EXIT(wmaResult, chexAuGetPCM(pau, fSPDIF, &cSamples));
        assert(cSamples == *pcSample);
        if ((Int)cMaxSamplesInDst < cSamples)
            TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
        chexGetSamplesReady(pau);
        cSamples = prp->m_cSamplesReady;
    }
    else
    {
        // Decoder
        assert(cSamples <= prp->m_cSamplesReady);
        cSamples = *pcSample;
    }

    cSamples = min(cSamples, (Int)cMaxSamplesInDst);
    cSamples = min(cSamples, prp->m_cSamplesReady);
    cSamples = min(cSamples, SHRT_MAX); // for security

    assert(sizeof(CBT) == sizeof(CoefType));

    if (pau->m_bCx)
        cxUpdateCurrMaxStartBand(pau->m_pcx);

    piOutputCurr = piOutput;
    while (cSamples > 0)
    {
        // see how many samples are finished currently
        cSamplesReady = chexCalcSamplesReady(prp->m_rgiPCMSamplesReady,
                                             pau->m_cChannel);
        // output these
        cSamplesRecon = min(cSamples, cSamplesReady);

        cChannelTemp = pau->m_cChannel; // save
        pau->m_cChannel = cChannel; // overwrite

        for (iCh=0; iCh < pau->m_cChannel; iCh++)
            pau->m_rgpcinfo[iCh].m_rgiPCMBuffer =
                (CBT*)pau->m_rgpcinfo[iCh].m_rgCoefSampMCLTCurr;

#if 0
        // Post process whatever is possible before getting pcm samples
        // - postproc channel xform (only for multichannel)
        // - channel folddown (only for multichannel)
        // - drc
        // All would work theoretically since they don't change sampling rate
        // but recon domain processing is currently only for <= 2 channels,
        // so this would essentially just enable DRC for recon domain proc
        if (NULL != pau->m_pfnPostProcess)
        {
            U16 iRetrieve = cSamplesRecon;
            TRACEWMA_EXIT(wmaResult,
                          pau->m_pfnPostProcess(pHandle, &iRetrieve, NULL, 0));
        }
#endif

#ifdef DUMP_CHEXBUFS
        {
            static FILE *fp[2] = {NULL, NULL};
            chexDumpBuf((CoefType*)pau->m_rgpcinfo[0].m_rgiPCMBuffer,
                      cSamplesRecon, &fp[0], "ccc0.raw");
            chexDumpBuf((CoefType*)pau->m_rgpcinfo[1].m_rgiPCMBuffer,
                      cSamplesRecon, &fp[1], "ccc1.raw");
        }
#endif // DUMP_CHEXBUFS

        // original number of samples to reconstruct
        cSamplesReconTemp = cSamplesRecon;

        // adjust for SSE to work
        if ( 0 != (cSamplesRecon & 0x0f) )
        {
            // round up to multiple of 16
            cSamplesRecon = (cSamplesRecon + 15) & (~0x0f);

            if( cSamplesRecon > (Int)cMaxSamplesInDst )
            {
                // go down to one less multiple
                cSamplesRecon -= 0x10;
                cSamplesReconTemp = cSamplesRecon;
                cSamples = cSamplesRecon;
            }
        }

        assert(cSamplesRecon <= (Int)cMaxSamplesInDst);
        TRACEWMA_EXIT(wmaResult,
               pau->aupfnReconSample(pau, piOutputCurr, (U16)cSamplesRecon));
        cSamplesRecon = cSamplesReconTemp;
        pau->m_cChannel = cChannelTemp; // restore
        cSamples -= cSamplesRecon;
        cMaxSamplesInDst -= cSamplesRecon;
        chexRemoveSamplesReady(prp->m_rgiPCMSamplesReady, pau->m_cChannel,
                             cSamplesRecon);
        prp->m_cSamplesReady -= cSamplesRecon;
        cSamplesOut += cSamplesRecon;
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pau->m_rgpcinfo[iCh].m_rgiPCMBuffer += cSamplesRecon;
            pau->m_rgpcinfo[iCh].m_rgCoefSampMCLTCurr += cSamplesRecon;
        }
        iBytesProduced = pau->m_nBytePerSample*pau->m_cChannel*cSamplesRecon;
        piOutputCurr = (PCMSAMPLE*)((U8*)piOutputCurr+iBytesProduced);
        if (cSamples == 0)
            break;

        prti = &prp->m_rgchextiBuf[prp->m_iBufReconPos];
        prtiNext =
            prp->m_rgchextiBuf + chexOffsetBuf(prp, prp->m_iBufReconPos, 1);
        prtiPrev =
            prp->m_rgchextiBuf + chexOffsetBuf(prp, prp->m_iBufReconPos, -1);

        // check to see output buffers empty
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
            if (prti->m_uChannelMask & (1<<iCh))
                assert(0 == prp->m_rgiPCMSamplesReady[iCh]);

        // do some tile processing

        TRACEWMA_EXIT(wmaResult, chexProcessTile(pau, prti, prtiPrev));

#ifdef DUMP_CHEXBUFS
        {
            static FILE *fp[2] = {NULL, NULL};
            chexDumpBuf(pau->m_rgpcinfo[0].m_rgCoefSampMCLTCurr,
                      prti->m_iSizeCurr, &fp[0], "bbb0.raw");
            chexDumpBuf(pau->m_rgpcinfo[1].m_rgCoefSampMCLTCurr,
                      prti->m_iSizeCurr, &fp[1], "bbb1.raw");
        }
#endif // DUMP_CHEXBUFS

        prp->m_iBufReconPos = chexOffsetBuf(prp, prp->m_iBufReconPos, 1);

        reconProcReleaseTiles(pau, prti);
    }

    if (0 == prp->m_cSamplesReady)
    {
#if (CX_DCT_ONLY==0)
        if (prp->m_iBufCodeFxPos != 
               chexOffsetBuf(prp, prp->m_iBufReconPos,
                             pau->m_bCx && pau->m_bReconFex ? 1 : 0) &&
               !prp->m_bLastTile)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
#else
        if (prp->m_iBufCodeFxPos != prp->m_iBufReconPos  &&
               !prp->m_bLastTile)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
#endif
    }

#if 0
    printf("RFX DEC %d %d\n",
           prp->m_rgchextiBuf[chexOffsetBuf(prp, prp->m_iBufCodeFxPos, -prp->m_iTilesInSubframeCodeFx)].m_iTileCnt,
           prp->m_iTilesInSubframeCodeFx);
    printf("GET CALL\n");
#endif

    if (WMAB_TRUE == pau->m_bEncoder)
        assert(prp->m_cSamplesReady == 0);

exit:
    *pcSample = (U16)cSamplesOut;
    return wmaResult;
}

WMARESULT chexAuGetPCM(CAudioObject* pau,  // [in]  the audio structure
                     Bool fSPDIF,
                     Int *pcSamples)
{  
    WMARESULT hr = WMA_OK;
    ReconProc *prp = pau->m_prp;
    U16 iRetrieve = 0;

    iRetrieve = (U16)(pau->m_iPCMReconEnd - pau->m_iPCMReconStart);

    assert(iRetrieve != 0);

    pau->m_iPCMReconStart += iRetrieve;
    // delay the shift of the pcm buffer until we have used up the samples
    if (pau->m_iPCMReconStart >= pau->m_cFrameSampleHalfAdjusted)
        auShiftPCMBuffer(pau, pau->m_cFrameSampleHalfAdjusted);

    if (CODEC_BEGIN == pau->m_codecStatus)
        pau->m_codecStatus = CODEC_STEADY;

    *pcSamples = iRetrieve;

    return hr;
} // chexAuGetPCM

// this is for taking into account silence due to syncing
// first 1/2 of the frame is thrown away (prvInitDiscardSilence)
Void chexAdjustTileStartEnd(CAudioObject *pau)
{
    U32 uLeadingSize = pau->m_rgiDiscardSilence[0];
    ReconProc *prp = pau->m_prp;
    Int iTiles;
    Int i, iPos;
    ReconTileInfo *prti;

    if (WMAB_FALSE==pau->m_bReconProc)
        return;

    iTiles = reconProcGetFrameTiles(prp, -1);

    uLeadingSize = max(uLeadingSize - pau->m_cFrameSampleHalf/2, 0);

    // for common seek case, prp->m_iBufAddPos = prp->m_iTilesInSubframeAdd
    // after a seek since prp->m_iBufAddPos hase been set to 0 in chexReset
    iPos = chexOffsetBuf(prp, prp->m_iBufAddPos, -iTiles);
    for (i=0; i < iTiles; i++)
    {
        prti = prp->m_rgchextiBuf + iPos;
        assert(chexInfoStatAdd(prti->m_uInfoStat));

        prti->m_iStart =
            checkRange((Int)uLeadingSize-prti->m_iStartPtInFrame,
                       0,
                       prti->m_iSizeCurr);

        iPos = chexOffsetBuf(prp, iPos, 1);
    }
}

// Ts corresponds to 1/2 way between first tile (or first max size tile??)
Int prvReconProcDecodeAdjustment(const CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti, *prtiPrev;
    Int iStart, iEnd, iReconPt, iTsPt, iCh;
    Int iMaxSize = 0;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
        iMaxSize =
            max(pau->m_rgpcinfo[iCh].m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[0],
                iMaxSize);

    iTsPt = pau->m_iFrameStart + iMaxSize/2;
    iReconPt = iTsPt;

    // find starting reconstruction point
    prti = prp->m_rgchextiBuf + prp->m_iBufReconPos;
    while (prti && chexInfoStatAdd(prti->m_uInfoStat))
    {
        if (prti->m_iStart != prti->m_iEnd)
        {
            iReconPt = prti->m_iStartPt + prti->m_iStart;
            prtiPrev = chexPrevTile(prp, prti);
            if (prtiPrev)
                iReconPt -= chexGet2ndHalfPts(prtiPrev, &iStart, &iEnd);
            break;
        }
        prti = chexNextTile(prp, prti);
    }

    return (iTsPt - iReconPt);
}

Void chexAddTile(CAudioObject *pau,
                 ReconProc *prp,
                 Int iTile,
                 Int iBufSubframePos,
                 Int iSizeCurr,
                 Int iStartPtInFrame,
                 U32 uChannelMask,
                 Int iSizeNext,
                 Bool bNext,
                 Bool bNoCx,
                 ConfigFrame ecfConfig)
{
    ReconTileInfo *prtiCurr, *prtiPrev;
    U32 uLeadingSize=0;
    Int iFrameNumber, iFrameStart;

    iFrameNumber = pau->m_iFrameNumber;
    iFrameStart = pau->m_iFrameStart;
    if (CONFIG_NEXTFRM == ecfConfig)
    {
        pau->m_iFrameNumber++;
        pau->m_iFrameStart += pau->m_cFrameSampleHalf;
    }

    prtiCurr = prp->m_rgchextiBuf + iBufSubframePos;
    prtiPrev = prp->m_rgchextiBuf + chexOffsetBuf(prp, iBufSubframePos, -1);

    assert(chexTileNotInUse(prtiCurr));
    
    // add this tile to the chex subframe buffer
    prtiPrev->m_iSizeNext = iSizeCurr;
    prtiCurr->m_iSizePrev = prtiPrev->m_iSizeCurr;
    prtiCurr->m_iSizeCurr = iSizeCurr;
    prtiCurr->m_iStartPtInFrame = iStartPtInFrame;
    prtiCurr->m_uChannelMask = uChannelMask;
    prtiCurr->m_bCodingFex = pau->m_bFreqex;
    if (bNext)
    {
        prtiCurr->m_iSizeNext = iSizeNext;
    }

    if (WMAB_FALSE == prp->m_bFirstTile)
    {
        prtiCurr->m_iStartPt = prtiPrev->m_iStartPt + prtiCurr->m_iSizePrev;
        prtiCurr->m_iTileCnt = prtiPrev->m_iTileCnt + 1;
        chexSetInfoStatNextKnown(&prtiPrev->m_uInfoStat);
    }
    else
        prtiCurr->m_iTileCnt = 0;
    chexSetInfoStatAdd(&prtiCurr->m_uInfoStat);

    assert(iStartPtInFrame+pau->m_iFrameStart == prtiCurr->m_iStartPt);

#if defined(ALLOW_EXTERNAL_FILE_FOR_RECON)
    prtiCurr->m_iStartPtInFile =
        (pau->m_iFrameNumber-1)*pau->m_cFrameSampleHalf-
        pau->m_cFrameSampleHalf*3/2 + iStartPtInFrame;
    // decoder is one frame ahead
    if (!pau->m_bEncoder)
        prtiCurr->m_iStartPtInFile += pau->m_cFrameSampleHalf;
#endif

    if (0 == iStartPtInFrame)
        prtiCurr->m_iTileInFrame = 0;
    else
        prtiCurr->m_iTileInFrame = prtiPrev->m_iTileInFrame + 1;

    if (WMAB_TRUE == pau->m_bCxPresent)
        prtiCurr->m_iNChGroups = chexSetChGroups(pau, prtiCurr->m_rguGroupCh);
    else
        prtiCurr->m_iNChGroups = 0;

    // divide leading silence into 2nd half of curr and 1st half of next
    if (pau->m_fLeadingSilence)
    {
        uLeadingSize =
            max(pau->m_u32LeadingSize - pau->m_cFrameSampleHalf/2, 0);
    }

    if (WMAB_TRUE == pau->m_bEncoder)
    {
        if (1==pau->m_iFrameNumber)
            uLeadingSize = pau->m_cFrameSampleHalf;
        else if (2==pau->m_iFrameNumber)
            uLeadingSize = pau->m_cFrameSampleHalf/2;
        else
            uLeadingSize = 0;
    }

    prtiCurr->m_iStart =
        checkRange((Int)uLeadingSize-prtiCurr->m_iStartPtInFrame,
                   0,
                   prtiCurr->m_iSizeCurr);
    prtiCurr->m_iEnd = prtiCurr->m_iSizeCurr;

    prp->m_iTrailingSize = pau->m_u32TrailingSize;
    prp->m_bLastTile = WMAB_FALSE;
    if (pau->m_fTrailingSilence)
    {
        Int iTilesInFrame = chexTilesInFrame(pau);
        if (iTile==iTilesInFrame-1)
        {
            chexSetInfoStatLastTile(&prtiCurr->m_uInfoStat);
            prp->m_bLastTile = WMAB_TRUE;
        }
    }

    // prev's next should already be correct if writing next
    if (WMAB_TRUE == bNext && WMAB_FALSE == prp->m_bFirstTile)
        assert(iSizeCurr == prtiPrev->m_iSizeNext);

    prp->m_bFirstTile = WMAB_FALSE;

    //printf("FF=%d %d %d %d %d S=%d E=%d\n", pau->m_iFrameNumber, pau->m_fLeadingSilence, pau->m_u32LeadingSize, pau->m_u32TrailingSize, prtiCurr->m_iStartPtInFile, prtiCurr->m_iStart, prtiCurr->m_iEnd);
    //printf("ST=%d END=%d\n",
    //        prtiCurr->m_iStartPt, prtiCurr->m_iStartPt+prtiCurr->m_iSizeCurr);

    prp->m_iStartPt = prtiCurr->m_iStartPt;
    prp->m_iEndPt = prtiCurr->m_iStartPt+prtiCurr->m_iSizeCurr;

    prp->m_iStartPt += iSizeCurr;

    if (WMAB_TRUE == chexInfoStatLastTile(prtiPrev->m_uInfoStat) &&
        WMAB_TRUE == prp->m_bLastTile)
    {
        if (!bNext)
        {
            // This variable will be checked upstream
            prp->m_wmaResult = WMA_E_BROKEN_FRAME;
        }
        chexSetInfoStatLastTile(&prtiCurr->m_uInfoStat);
    }

    if (WMAB_TRUE == bNoCx)
    {
        chexSetInfoStatNoCx(&prtiCurr->m_uInfoStat);
        chexSetInfoStatNoFx(&prtiCurr->m_uInfoStat);
    }

    // restore original values
    pau->m_iFrameNumber = iFrameNumber;
    pau->m_iFrameStart = iFrameStart;
}

Int chexGetReconTilesInSubframe(CAudioObject *pau, Int iTileEnd, Int iBufPos)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti;
    Int iChexTiles = 0;

    prti = prp->m_rgchextiBuf + iBufPos;
    if (chexInfoStatAdd(prti->m_uInfoStat))
    {
        while (prti && prti->m_iStartPt+prti->m_iSizeCurr <= iTileEnd)
        {
            iChexTiles++;
            prti = chexNextTile(prp, prti);
        }
    }

    return iChexTiles;
}

Void chexAddAllFrameTiles(CAudioObject *pau, Int iBufPos,
                          Int N, U32 uChannelMask, Bool bNoCx,
                          ConfigFrame ecfConfig)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti;
    Chex *pcx = pau->m_pcx;
    Int iChexTileSize = pau->m_cFrameSampleHalf / N;
    Int iStartPtInFrame = 0;
    Int iTile;

    assert(N <= prp->m_iMaxTilesPerFrame);

    prti = prp->m_rgchextiBuf + chexOffsetBuf(prp, iBufPos, -1);
    if (chexInfoStatAdd(prti->m_uInfoStat))
    {
        // count the last tile of previous frame
        //assert(chexInfoStatNextKnown(prti->m_uInfoStat) == WMAB_FALSE);
        prp->m_iTilesInSubframeXForm++;
    }

    for (iTile=0; iTile < N; iTile++)
    {
        chexAddTile(pau, prp, iTile, iBufPos, iChexTileSize,
                    iStartPtInFrame, uChannelMask, 0, WMAB_TRUE,
                    bNoCx, ecfConfig);
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        iStartPtInFrame += iChexTileSize;
    }
    if (WMAB_TRUE == pau->m_bCx)
        pcx->m_bBandConfigComputed = WMAB_FALSE;

    prp->m_iTilesInSubframeAdd += N;
    prp->m_iTilesInSubframeXForm += (N - 1);
}

Int  chexAddFrameTilesMatchWithBaseSmallSize(CAudioObject *pau, Int iBufPos,
                                             U32 uChannelMask,
                                             Bool bNext, Bool bNoCx,
                                             ConfigFrame ecfConfig)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti;
    Chex *pcx = pau->m_pcx;
    Int iSizeNext = 0;
    Int i, iSubframe, iSizeCurr, iStartPtInFrame;
    Int cTilesAdd, cTilesXForm, iSizeBasic, iSizeMin, iSize;
    SubFrameConfigInfo  *psubfrmconfig;

    assert(prp->m_iNTilesPerFrameBasic <= prp->m_iMaxTilesPerFrame);

    auConvertSubframeConfigToTileConfig(pau, ecfConfig);

    iSizeBasic = pau->m_cFrameSampleHalf / prp->m_iNTilesPerFrameBasic;
    iSizeMin   = pau->m_cFrameSampleHalf / prp->m_iMaxTilesPerFrame;

    assert( iSizeBasic >= iSizeMin );

    cTilesAdd = cTilesXForm = 0;

    prti = prp->m_rgchextiBuf + chexOffsetBuf(prp, iBufPos, -1);
    if (chexInfoStatAdd(prti->m_uInfoStat))
    {
        // count the last tile of previous frame
        assert(chexInfoStatNextKnown(prti->m_uInfoStat) == WMAB_FALSE);
        cTilesXForm++;
    }

    // note: iNextSize of each tile is set at the next tile,
    //       so no need to pass correct next size at the moment of adding tile
    iStartPtInFrame = 0;
    iSizeCurr = 0;
    for (i = 0; i < pau->m_cTiles; i++)
    {
        psubfrmconfig = pau->m_rgtci[i].m_psfci;
        iSubframe = pau->m_rgtci[i].m_iSubFrame;
        iSizeCurr += pau->m_rgtci[i].m_iSubFrameSize;

        iSize = iSizeBasic;
        while (iSize >= iSizeMin)
        {
            while (iSizeCurr >= iSize)
            {
                chexAddTile(pau, prp, cTilesAdd,
                            iBufPos, iSize, iStartPtInFrame,
                            uChannelMask, 0,
                            bNext || bNoCx, bNoCx, ecfConfig);
                iBufPos = chexOffsetBuf(prp, iBufPos, 1);
                cTilesAdd++;
                cTilesXForm++;
                iStartPtInFrame += iSize;
                iSizeCurr -= iSize;
            }
            iSize = iSize >> 1;
        }
    }
    assert( iSizeCurr == 0 );

    // note: although the last tile with unknown next size is added, it is not counted for xform here
    //       it will be done in next frame
    cTilesXForm--;

    if (WMAB_TRUE == pau->m_bCx)
        pcx->m_bBandConfigComputed = WMAB_FALSE;

    prp->m_iTilesInSubframeAdd += cTilesAdd;
    prp->m_iTilesInSubframeXForm += cTilesXForm;

    return cTilesAdd;
}

Int  chexAddFrameTilesArbitrary(CAudioObject *pau, Int iBufPos,
                                U32 uChannelMask, Bool bNext, Bool bNoCx,
                                ConfigFrame ecfConfig)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti;
    Chex *pcx = pau->m_pcx;
    Int iSizeNext = 0;
    Int i, iTile, iSizeCurr, iStartPtInFrame;
    Int cTilesAdd, cTilesXForm, iSizeBasic, cTiles;
    Bool *pbTileSplitArbitrary;

    iSizeBasic = pau->m_cFrameSampleHalf / prp->m_iNTilesPerFrameBasic;
    cTilesAdd = cTilesXForm = 0;

    prti = prp->m_rgchextiBuf + chexOffsetBuf(prp, iBufPos, -1);
    if (chexInfoStatAdd(prti->m_uInfoStat))
    {
        // count the last tile of previous frame
        assert(chexInfoStatNextKnown(prti->m_uInfoStat) == WMAB_FALSE);
        cTilesXForm++;
    }

    pbTileSplitArbitrary = (ecfConfig == CONFIG_CURRFRM) ? 
                                prp->m_rgbTileSplitArbitrary :
                                prp->m_rgbTileSplitArbitrary + prp->m_iNTilesPerFrameBasic;

    iStartPtInFrame = 0;
    for (iTile=0; iTile < prp->m_iNTilesPerFrameBasic; iTile++)
    {
        if (pbTileSplitArbitrary[iTile] == WMAB_TRUE)
        {
            // split into half
            iSizeCurr = iSizeBasic / 2;
            cTiles = 2;
        }
        else
        {
            // no split
            iSizeCurr = iSizeBasic;
            cTiles = 1;
        }

        // split into half
        for (i = 0;  i < cTiles; i++)
        {
            chexAddTile(pau, prp, cTilesAdd, iBufPos, iSizeCurr,
                        iStartPtInFrame, uChannelMask, 0,
                        bNext || bNoCx, bNoCx, ecfConfig);
            iStartPtInFrame += iSizeCurr;
            cTilesAdd++;
            cTilesXForm++;
            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
        }
    }
    // note: although the last tile with unknown next size is added, it is not counted for xform here
    //       it will be done in next frame
    cTilesXForm--;

    if (WMAB_TRUE == pau->m_bCx)
        pcx->m_bBandConfigComputed = WMAB_FALSE;

    prp->m_iTilesInSubframeAdd += cTilesAdd;
    prp->m_iTilesInSubframeXForm += cTilesXForm;

    return cTilesAdd;
}

Void reconProcUpdateCodingFexFlag(CAudioObject *pau)
{
    ReconProc       *prp = pau->m_prp;
    ReconTileInfo   *prti;
    Int     iBufPos, iBaseTile, iSizeCurr, iCodingFexMaxFreq;
    Bool    bCodingFex;

    iSizeCurr = 0;
    bCodingFex = WMAB_TRUE;
    iCodingFexMaxFreq = pau->m_iSamplingRate/2;

    iBufPos = prp->m_iBufCodePos;
    prti = prp->m_rgchextiBuf + iBufPos;
    if (!chexInfoStatAdd(prti->m_uInfoStat))
        return;

    for (iBaseTile = 0; iBaseTile <= pau->m_iCurrTile; iBaseTile++)
    {
        iSizeCurr += pau->m_rgtci[iBaseTile].m_iSubFrameSize;
        bCodingFex &= pau->m_rgtci[iBaseTile].m_bCodingFex;
        iCodingFexMaxFreq = min(iCodingFexMaxFreq, pau->m_rgtci[iBaseTile].m_iCodingFexMaxFreq);

        while (iSizeCurr - prti->m_iSizeCurr >= 0)
        {
            prti->m_bCodingFex = bCodingFex;
            prti->m_iCodingFexMaxFreq = iCodingFexMaxFreq;
            iSizeCurr -= prti->m_iSizeCurr;

            iBufPos = chexOffsetBuf(prp, iBufPos, 1);
            prti = prp->m_rgchextiBuf + iBufPos;
        }
        if (iSizeCurr == 0)
        {
            bCodingFex = WMAB_TRUE;
            iCodingFexMaxFreq = pau->m_iSamplingRate/2;
        }
    }
}

Void reconProcStoreFrameTiles(ReconProc *prp, Int iTiles)
{
    prp->m_rgiTilesInSubframeAdd[prp->m_iTilesInSubframeAddPos++] = iTiles;
    if (prp->m_iTilesInSubframeAddPos == 4)
        prp->m_iTilesInSubframeAddPos = 0;
}

Int reconProcGetFrameTiles(ReconProc *prp, Int iOffset)
{
    Int iPos = (prp->m_iTilesInSubframeAddPos + iOffset + 4) % 4;
    assert(iOffset >= -3);
    return prp->m_rgiTilesInSubframeAdd[iPos];
}

#if 0
Void reconProcRandomizeArbitraryTileConfig(ReconProc *prp)
{
    Int i;
    U32 x = (U32)rand();
    x = x % 256;

    for(i=0;i<prp->m_iNTilesPerFrameBasic;i++)
        prp->m_rgbTileSplitArbitrary[i] = prp->m_rgbTileSplitArbitrary[i+prp->m_iNTilesPerFrameBasic];
    printf("\n");
    for(i=0;i<prp->m_iNTilesPerFrameBasic;i++)
    {
        prp->m_rgbTileSplitArbitrary[i+prp->m_iNTilesPerFrameBasic] = x & 0x1;
        x = (x >> 1);
        printf("%1d",prp->m_rgbTileSplitArbitrary[i+prp->m_iNTilesPerFrameBasic]);
    }
}
#endif

// update tiling for chex for subframe
WMARESULT chexInitSubframeTilingInfo(CAudioObject *pau,
                                     Int iChInTile, I16 *rgiChInTile,
                                     Int iTile, Bool bNext, Bool bNoCx)
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    U32 uChannelMask = 0;
    Int iBufPos, i, cTiles, cTilesAdd;
    Int iCurrAdd, iPrevAdd, iNextAdd=0;
    ConfigFrame ecfConfig;
    Bool bStoreNext = WMAB_FALSE;
    Bool bSave = (pau->m_nChannelMask != pau->m_nOrigChannelMask);

    if (bSave)
        prvSaveCurChannels(pau);
    prvSetOrigChannels(pau);

    if( pau->m_bEncoder && pau->m_iFrameNumber == 1 )
    {
        if (pau->m_bCx && pcx)
            pcx->m_iNChGroups = chexSetChGroups(pau, pcx->m_rguGroupCh);
        goto exit;
    }

    if (WMAB_TRUE == pau->m_bCx)
    {
        assert(iChInTile == pau->m_cChInTile);
        for (i=0; i < iChInTile; i++)
            assert(rgiChInTile[i] == pau->m_rgiChInTile[i]);
    }

    // for encoder we are actually going to add next frame tiles, except
    // the first time, when we add both
    bStoreNext = pau->m_bEncoder;

    ecfConfig = bStoreNext ? CONFIG_NEXTFRM : CONFIG_CURRFRM;

    auConvertSubframeConfigToTileConfig(pau, CONFIG_CURRFRM);
    cTiles = pau->m_cTiles;
    uChannelMask = (1<<pau->m_cChannel)-1;
    prp->m_iTilesInSubframeAdd = 0;
    prp->m_iTilesInSubframeXForm = 0;
    if (((cTiles-1 == iTile) && !pau->m_bEncoder) ||
        ((0 == iTile) && pau->m_bEncoder))
    {
#if 0
        if (pau->m_bEncoder) // randomize arbitrary split config
            reconProcRandomizeArbitraryTileConfig(prp);
#endif
        prp->m_wmaResult = WMA_OK;
        
        iBufPos = prp->m_iBufAddPos;
        // add all tiles in one shot, however code in usual ways
        cTilesAdd = prp->m_iNTilesPerFrameBasic;
        if (bStoreNext && prp->m_iBufCodePos == prp->m_iBufAddPos)
        {
            switch (prp->m_iTileSplitType)
            {
                case ReconProcTileSplitBasic:
                    chexAddAllFrameTiles(pau, iBufPos,
                                         prp->m_iNTilesPerFrameBasic,
                                         uChannelMask, bNoCx, CONFIG_CURRFRM);
                    break;
                case ReconProcTileSplitBaseSmall:
                    cTilesAdd = chexAddFrameTilesMatchWithBaseSmallSize(pau, iBufPos, uChannelMask, bNext, 
                                                                        bNoCx, CONFIG_CURRFRM);
                    break;
                case ReconProcTileSplitArbitrary:
                    cTilesAdd = chexAddFrameTilesArbitrary(pau, iBufPos, uChannelMask,
                                                           bNext, bNoCx, CONFIG_CURRFRM);
                    break;
                default: 
                    assert(WMAB_FALSE);
                    break;
            }
            reconProcStoreFrameTiles(prp, cTilesAdd);
            iBufPos = chexOffsetBuf(prp, iBufPos, cTilesAdd);
        }
        switch (prp->m_iTileSplitType)
        {
            case ReconProcTileSplitBasic:
                chexAddAllFrameTiles(pau, iBufPos,
                                     prp->m_iNTilesPerFrameBasic,
                                     uChannelMask, bNoCx, ecfConfig);
                break;
            case ReconProcTileSplitBaseSmall:
                cTilesAdd = chexAddFrameTilesMatchWithBaseSmallSize(pau, iBufPos, uChannelMask, bNext,
                                                                    bNoCx, ecfConfig);
                break;
            case ReconProcTileSplitArbitrary:
                cTilesAdd = chexAddFrameTilesArbitrary(pau, iBufPos, uChannelMask,
                                                       bNext, bNoCx, ecfConfig);
                break;
            default:
                assert(WMAB_FALSE);
                break;
        }
        reconProcStoreFrameTiles(prp, cTilesAdd);
        iBufPos = chexOffsetBuf(prp, iBufPos, cTilesAdd);

        // Were there errors while adding tiles above?
        if (WMA_FAILED(prp->m_wmaResult))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        
        if (pau->m_fTrailingSilence && WMAB_FALSE==prp->m_bLastTile)
        {
            Int iLastPos = chexOffsetBuf(prp, iBufPos, -1);
            ReconTileInfo *prtiLast = prp->m_rgchextiBuf + iLastPos;

            chexSetInfoStatLastTile(&prtiLast->m_uInfoStat);
            prp->m_bLastTile = WMAB_TRUE;
        }
    }

    // set channel groups for base
    // m_bCxPresent can be corrupted; changed to m_bCx
    if (pau->m_bCx)
        pcx->m_iNChGroups = chexSetChGroups(pau, pcx->m_rguGroupCh);
    else if (pcx)
        pcx->m_iNChGroups = 0;

    if (bStoreNext)
    {
        iPrevAdd = reconProcGetFrameTiles(prp, -3);
        iCurrAdd = reconProcGetFrameTiles(prp, -2);
        iNextAdd = reconProcGetFrameTiles(prp, -1);
    }
    else
    {
        iPrevAdd = reconProcGetFrameTiles(prp, -2);
        iCurrAdd = reconProcGetFrameTiles(prp, -1);
    }

    auConvertSubframeConfigToTileConfig(pau, CONFIG_CURRFRM);

    prp->m_iTilesInSubframeCalc = 0;
    prp->m_iTilesInSubframeCode = 0;
    prp->m_iTilesInSubframeSeg = 0;

    if (iTile == 0 && pau->m_bEncoder)
    {
        // iTile = 0:
        //      obtain estimated # of bits at first subframe and distribute it over the frame
        // iTile = cTiles-1:
        //      overwrite and put in last tile to avoid overhead (match with rfx)
        prp->m_iTilesInSubframeCalc = iCurrAdd;
        prp->m_iTilesInSubframeCode = iCurrAdd;
    }
    else if (iTile == pau->m_cTiles - 1)
    {
        prp->m_iTilesInSubframeCode = iCurrAdd;
    }

    iBufPos = prp->m_iBufCodePos;
    for (i=0; i < prp->m_iTilesInSubframeCode; i++)
    {
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }

    assert(prp->m_iBufBasePos==prp->m_iBufCodePos || 0 != iTile);
    prp->m_iTilesInSubframeBase =
        chexGetReconTilesInSubframe(pau,
                                    pau->m_iFrameStart+
                                    pau->m_rgtci[iTile].m_iSubFrameStart+
                                    pau->m_rgtci[iTile].m_iSubFrameSize,
                                    prp->m_iBufBasePos);

    if (prp->m_bTileInit && !bNoCx)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    // call this for non-recon fex for determining # of samples ready
    if (WMAB_TRUE == pau->m_bReconFex || 1)
    {
        prp->m_iTilesInSubframeXFormRecon = 0;
        prp->m_iTilesInSubframeCalcFx = 0;
        prp->m_iTilesInSubframeCodeFx = 0;

        // hold fex recon until last subframe, so that all of recon is available
        if ((iTile == 0 && pau->m_bEncoder) || iTile == pau->m_cTiles-1)
        {
            ReconTileInfo *prti, *prtiAdd;
            Bool          bPrevAdd;
            Int           cSamplesInFrame;
            Int           iTile1 = 0;

            prtiAdd = prp->m_rgchextiBuf + prp->m_iBufAddPos;
            prti = prp->m_rgchextiBuf + prp->m_iBufCodeFxPos;
            assert(prti->m_iTileCnt >= prtiAdd->m_iTileCnt - iCurrAdd - iPrevAdd);

            iBufPos = prp->m_iBufCodeFxPos;
            cSamplesInFrame = 0;
            bPrevAdd = WMAB_TRUE;
            while( WMAB_TRUE )
            {
                prti = prp->m_rgchextiBuf + iBufPos;

                if (bPrevAdd == WMAB_TRUE && prti->m_iStartPtInFrame > 0)
                {
                    rfxSetReconTileInfo(pau, prp, prti);
                    prp->m_iTilesInSubframeXFormRecon++;
                }
                else
                {
                    bPrevAdd = WMAB_FALSE;
                    if ((prti->m_iStartPtInFrame + prti->m_iSizeCurr*3/2 <=
                         pau->m_cFrameSampleHalf / 2))
                    {
                        rfxSetReconTileInfo(pau, prp, prti);
                        prp->m_iTilesInSubframeXFormRecon++;
                        iTile1++;
                    }
                    else
                    {
                        // this tile not added
                        break;
                    }
                }
                cSamplesInFrame += prti->m_iSizeCurr;
                iBufPos = chexOffsetBuf(prp, iBufPos, 1);
            }

            // iTile = 0:
            //      obtain estimated # of bits at first subframe and distribute it over the frame
            //      will set these counters zeros in chexEncEndSubframeTilingInfo() to avoid conflict with the last tile
            // iTile = cTiles-1:
            //      code rfex
            prp->m_iTilesInSubframeCalcFx = prp->m_iTilesInSubframeXFormRecon;
            prp->m_iTilesInSubframeCodeFx = prp->m_iTilesInSubframeXFormRecon;

            if (prp->m_bLastTile)
            {
                Int iRemTile1 = iCurrAdd-iTile1;
                Int iPos = chexOffsetBuf(prp, prp->m_iBufCodeFxPos,
                                         prp->m_iTilesInSubframeCodeFx);
                for (i=0; i < iRemTile1; i++)
                {
                    ReconTileInfo *prti = prp->m_rgchextiBuf + iPos;
                    chexSetInfoStatNoFx(&prti->m_uInfoStat);
                    iPos = chexOffsetBuf(prp, iPos, 1);
                }
            }
            if (prp->m_iTilesInSubframeCodeFx > 0)
            {
                prti = prp->m_rgchextiBuf +
                    chexOffsetBuf(prp, prp->m_iBufCodeFxPos, prp->m_iTilesInSubframeCodeFx-1);
                prti->m_prfxrti->m_bLastTileInFrame = WMAB_TRUE;
            }
        }
    }

    prp->m_bTileInit = WMAB_TRUE;

    if (pau->m_bCx && 0==iTile)
        pcx->m_bSegmentationDone = WMAB_FALSE;

exit:
    if (bSave)
        prvRestoreCurChannels(pau);
    return wmaResult;
}

Void chexEndSubframeTilingInfo(CAudioObject *pau, Int iTile)
{
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    Int iBufPos, i;
    ReconTileInfo *prti;
    I16 *rgiChInTile;

    // guard against double calls (especially at decoder end)
    if (WMAB_FALSE == prp->m_bTileInit)
        return;

    rgiChInTile = pau->m_rgiChInTile;

    // set the coded tiles to coded
    iBufPos = prp->m_iBufCodePos;
    for (i=0; i < prp->m_iTilesInSubframeCode; i++)
    {
        prti = prp->m_rgchextiBuf + iBufPos;
        if (!chexInfoStatCode(prti->m_uInfoStat))
            chexSetInfoStatNoCx(&prti->m_uInfoStat);
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }

    iBufPos = prp->m_iBufCodeFxPos;
    for (i=0; i < prp->m_iTilesInSubframeCodeFx; i++)
    {
        prti = prp->m_rgchextiBuf + iBufPos;
        if (!chexInfoStatCodeFx(prti->m_uInfoStat))
            chexSetInfoStatNoFx(&prti->m_uInfoStat);
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }

    prp->m_iBufAddPos = chexOffsetBuf(prp, prp->m_iBufAddPos,
                                      prp->m_iTilesInSubframeAdd);
    prp->m_iBufCalcPos = chexOffsetBuf(prp, prp->m_iBufCalcPos,
                                       prp->m_iTilesInSubframeCalc);
    prp->m_iBufCodePos = chexOffsetBuf(prp, prp->m_iBufCodePos,
                                       prp->m_iTilesInSubframeCode);
    prp->m_iBufXFormPos = chexOffsetBuf(prp, prp->m_iBufXFormPos,
                                        prp->m_iTilesInSubframeXForm);
    prp->m_iBufXFormReconPos = chexOffsetBuf(prp, prp->m_iBufXFormReconPos,
                                             prp->m_iTilesInSubframeXFormRecon);
    prp->m_iBufSegPos = chexOffsetBuf(prp, prp->m_iBufSegPos,
                                      prp->m_iTilesInSubframeSeg);

    prp->m_iBufCalcFxPos = chexOffsetBuf(prp, prp->m_iBufCalcFxPos,
                                         prp->m_iTilesInSubframeCalcFx);
    prp->m_iBufCodeFxPos = chexOffsetBuf(prp, prp->m_iBufCodeFxPos,
                                         prp->m_iTilesInSubframeCodeFx);

    prp->m_iBufBasePos = chexOffsetBuf(prp, prp->m_iBufBasePos,
                                       prp->m_iTilesInSubframeBase);

    prp->m_iDecodeRFxTileInFrame = 0;
    pau->m_fex.m_bFirstTileV2Recon = WMAB_TRUE;

    prp->m_bTileInit = WMAB_FALSE;

    if (iTile == pau->m_cTiles-1 && pau->m_bEncoder)
        pau->m_bFirstPlusFrameAfterReset = WMAB_FALSE;
}

// ==================================================================

Void chexSetNoCodeCx(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    ReconTileInfo *prti;
    Int i, iBufPos;

    iBufPos = prp->m_iBufCodePos;
    for (i=0; i <  prp->m_iTilesInSubframeCode; i++)
    {
        prti = prp->m_rgchextiBuf + iBufPos;
        chexUnsetInfoStatCode(&prti->m_uInfoStat);
        chexSetInfoStatNoCx(&prti->m_uInfoStat);
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }
    // set start of segment to next tile to be coded
    if (0 != prp->m_iTilesInSubframeCode)
    {
        pcx->m_prtiSegStart = prp->m_rgchextiBuf + iBufPos;
        pcx->m_iTilesRemInSegment = 0;
    }
}

Void chexSetNoCodeRFx(CAudioObject *pau)
{
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti;
    Int i, iBufPos;

    iBufPos = prp->m_iBufCodeFxPos;
    for (i=0; i <  prp->m_iTilesInSubframeCodeFx; i++)
    {
        prti = prp->m_rgchextiBuf + iBufPos;
        chexUnsetInfoStatCodeFx(&prti->m_uInfoStat);
        chexSetInfoStatNoFx(&prti->m_uInfoStat);
        chexUnsetInfoStatCodeBs(&prti->m_uInfoStat);
        iBufPos = chexOffsetBuf(prp, iBufPos, 1);
    }
}

// =====================================================================

WMARESULT chexTileInit(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    Int i, iCh, iFirstCh=-1, iFirstChInGroup;
    PerChannelInfo *ppcinfo;
    ReconProc *prp = pau->m_prp;
    Chex *pcx = pau->m_pcx;
    Fex *pfx = &pau->m_fex;
    Int iChCode;

    if (!pcx || 0 == pcx->m_iNChGroups)
        goto exit;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        pcx->m_rguFexChannel[iCh] = 0;
        pau->m_rgpcinfo[iCh].m_bNoDecodeForCx = WMAB_FALSE;
    }

    iChCode = 0;
    for (i=0; i < pcx->m_iNChGroups; i++)
    {
        iFirstCh = -1;
        iFirstChInGroup = -1;
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            if (!(pcx->m_rguGroupCh[i] & (1<<iCh)))
                continue;

            ppcinfo = pau->m_rgpcinfo + iCh;

#if (CX_DECODE_MONO==1)
            if (-1 != iFirstChInGroup && WMAB_FALSE==pau->m_bEncoder)
                ppcinfo->m_bNoDecodeForCx = WMAB_TRUE;
#endif

            if (-1 != iFirstCh)
            {
                ppcinfo->m_bFex = WMAB_FALSE;
                continue;
            }

            if (ppcinfo->m_bFex ||
                (WMAB_FALSE==pau->m_bFreqexPresent &&
                 WMAB_FALSE==pau->m_bReconFexPresent))
            {
                iFirstCh = iCh;
                iChCode++;
            }

            if (-1 == iFirstChInGroup)
                iFirstChInGroup = iCh;

            if (pau->m_bCx && iCh != 0 && ppcinfo->m_bFex)
            {
                // Only the 1st channel should have Fex enabled
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }

        if (iFirstCh >= 0)
            pcx->m_rguFexChannel[iFirstCh] = pcx->m_rguGroupCh[i];
        else
            pcx->m_rguFexChannel[iFirstChInGroup] = pcx->m_rguGroupCh[i];
    }

    if (pfx &&
        (pau->m_bFreqexPresent || pau->m_bReconFexPresent) &&
        -1 != iFirstCh)
    {
        pfx->m_nChCode = iChCode;
        if (pfx->m_bHasPower != (0 != pfx->m_nChCode))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
    }

exit:
    return wmaResult;
}

// ===================================================================
// Cx reverb filter

#include "reverbfilter.c"

#if !defined(VOLKANO) && (defined(_DEBUG) || !defined(UNDER_CE))
Void chexDumpCodedParams(CAudioObject *pau, ReconTileInfo *prti, FILE *fp)
{
    Int i;
    Chex *pcx = pau->m_pcx;
    CxAnchorReconTileInfo *pcxarti = prti->m_pcxartiSeg;
    FILE_DUMP_INIT(cxparams);

    fprintf(fp, "STARTPT=%d\n", prti->m_iStartPt+pau->m_prp->m_iSampleOffset);
    fprintf(fp, "NUMBANDINDEX=%d %d %d\n", pcx->m_bBandConfigPerTile,
            pcx->m_iNumBandIndex, pcxarti->m_iNumBandIndex);
    fprintf(fp, "BANDMULTINDEX=%d %d\n",
            pcx->m_iBandMultIndex, pcxarti->m_iBandMultIndex);
    fprintf(fp, "STARTBAND=%d %d %d\n", pcx->m_bStartBandPerTile,
            pcx->m_iStartBand, pcxarti->m_iStartBand);
    fprintf(fp, "QSI=%d %d %d\n",
            pcx->m_iQuantStepIndex,
            pcx->m_iQuantStepIndexPhase,
            pcx->m_bCodeLMRM ? 0 : pcx->m_iQuantStepIndexLR);
    fprintf(fp, "ASTH=%d\n", pcx->m_iAdjustScaleThreshIndex);
    fprintf(fp, "AUTOADJUST=%d %d\n",
            pcx->m_eAutoAdjustScale, pcxarti->m_eAutoAdjustScale);
    fprintf(fp, "MAXMTXSC=%d\n", pcx->m_iMaxMatrixScaleIndex);
    fprintf(fp, "CODELMRM=%d\n", pcx->m_bCodeLMRM);
    fprintf(fp, "TAPOUT=%d %d\n",
            pcx->m_eFilterTapOutput, pcxarti->m_eFilterTapOutput);
    fprintf(fp, "CXCH=%d %d\n",
            pcx->m_eCxChCoding, pcxarti->m_eCxChCoding);
    fprintf(fp, "EVEN=%d\n", pcxarti->m_bEvenLengthCxSegment);

    for (i=0; i < pcxarti->m_cBands; i++)
    {
        fprintf(fp, "%d %s: %f\n", i, pcx->m_bCodeLMRM ? "LM" : "L",
                pcxarti->m_param0[0][i]);
        fprintf(fp, "%d %s: %f\n", i, pcx->m_bCodeLMRM ? "RM" : "LR",
                pcxarti->m_param1[0][i]);
        fprintf(fp, "%d %s: %f\n", i, "LRA", pcxarti->m_param2[0][i]);
        if (ChexChCodingPerBand == pcxarti->m_eCxChCoding)
            fprintf(fp, "%d %d\n", i, pcxarti->m_iCodeMono[i]);
    }

    fflush(fp);
}
#endif	// _DEBUG

#endif // BUILD_WMAPROLBRV2

