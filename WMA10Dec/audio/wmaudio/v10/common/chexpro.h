//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __CHEX_H
#define __CHEX_H

#if defined(BUILD_WMAPROLBRV1)

#ifdef __cplusplus
extern "C" {
#endif

// ========================================================

// huffman training of tables for chex
#if defined(CHEX_EXP) || 0
#define CHEX_HUFFTRAIN 
#endif

//#define CHEX_HUFFTRAIN

// ========================================================

//#define JOINT_CODE_LMRM

// ========================================================

ChexType qstCalcQuantStepInterp( const ChexType fScale );

INLINE
Int reconProcBufPos( const ReconProc     * const prp, 
                     const ReconTileInfo * const prti,
                     const Int iOffset )
{
    return chexOffsetBuf(prp, (Int)(prti - prp->m_rgchextiBuf), iOffset);
}

INLINE
ReconTileInfo* chexOffsetTile( const ReconProc     * const prp, 
                                     ReconTileInfo * const prti,
                               const Int iOffset )
{
    const Int iPos = (Int)(prti - prp->m_rgchextiBuf);
    const Int iOffsetPos = chexOffsetBuf(prp, iPos, iOffset);
    ReconTileInfo * const prtiOffset = prp->m_rgchextiBuf + iOffsetPos;

    if (prtiOffset->m_iTileCnt - prti->m_iTileCnt == iOffset)
        return prtiOffset;
    else
        return NULL;
}

INLINE
ReconTileInfo *chexNextTile( const ReconProc     * const prp, 
                             const ReconTileInfo * const prti )
{
    const Int iPos = (Int)(prti - prp->m_rgchextiBuf);
    const Int iNextPos = chexOffsetBuf(prp, iPos, 1);
    ReconTileInfo * const prtiNext = prp->m_rgchextiBuf + iNextPos;

    if (prtiNext->m_iTileCnt == prti->m_iTileCnt+1)
        return prtiNext;
    else
        return NULL;
}

INLINE
ReconTileInfo* chexPrevTile(ReconProc *prp, ReconTileInfo *prti)
{
    Int iPos = (Int)(prti - prp->m_rgchextiBuf);
    Int iPrevPos = chexOffsetBuf(prp, iPos, -1);
    ReconTileInfo *prtiPrev = prp->m_rgchextiBuf + iPrevPos;
    if (prtiPrev->m_iTileCnt == prti->m_iTileCnt-1)
        return prtiPrev;
    else
        return NULL;
}

// ========================================================

// "Code" means chex parameters have been encoded/decoded
// "NoCx" means no chex is done for this tile, assume default params
INLINE Void chexSetInfoStatAdd(U32 *puStat)       { *puStat |= (1<<0); }
INLINE Void chexSetInfoStatCalc(U32 *puStat)      { *puStat |= (1<<1); }
INLINE Void chexSetInfoStatCode(U32 *puStat)      { *puStat |= (1<<2); }
INLINE Void chexSetInfoStatNextKnown(U32 *puStat) { *puStat |= (1<<3); }
INLINE Void chexSetInfoStatLastTile(U32 *puStat)  { *puStat |= (1<<4); }
INLINE Void chexSetInfoStatNoCx(U32 *puStat)      { *puStat |= (1<<5); }

INLINE Void chexSetInfoStatCalcFx(U32 *puStat)    { *puStat |= (1<<6); }
INLINE Void chexSetInfoStatCodeFx(U32 *puStat)    { *puStat |= (1<<7); }
INLINE Void chexSetInfoStatNoFx(U32 *puStat)      { *puStat |= (1<<8); }

INLINE Void chexSetInfoStatXForm(U32 *puStat)      { *puStat |= (1<<9);  }
INLINE Void chexSetInfoStatXFormRecon(U32 *puStat) { *puStat |= (1<<10); }

INLINE Void chexSetInfoStatMLTProc(U32 *puStat) { *puStat |= (1<<11); }

INLINE Void chexSetInfoStatCreateMono(U32 *puStat) { *puStat |= (1<<12); }

INLINE Void chexSetInfoStatCodeBs(U32 *puStat) { *puStat |= (1<<13); }

// ========================================================

INLINE Void chexUnsetInfoStatCode(U32 *puStat) { *puStat &= ~(1<<2); }

INLINE Void chexUnsetInfoStatCodeFx(U32 *puStat) { *puStat &= ~(1<<7); }

INLINE Void chexUnsetInfoStatNoFx(U32 *puStat) { *puStat &= ~(1<<8); }

INLINE Void chexUnsetInfoStatXForm(U32 *puStat) { *puStat &= ~(1<<9); }
INLINE Void chexUnsetInfoStatXFormRecon(U32 *puStat) { *puStat &= ~(1<<10); }

INLINE Void chexUnsetInfoStatCodeBs(U32 *puStat) { *puStat &= ~(1<<13); }

// ========================================================

INLINE U32 chexInfoStatAdd(U32 uStat)       { return (uStat >> 0) & 0x1; }
INLINE U32 chexInfoStatCalc(U32 uStat)      { return (uStat >> 1) & 0x1; }
INLINE U32 chexInfoStatCode(U32 uStat)      { return (uStat >> 2) & 0x1; }
INLINE U32 chexInfoStatNextKnown(U32 uStat) { return (uStat >> 3) & 0x1; }
INLINE U32 chexInfoStatLastTile(U32 uStat)  { return (uStat >> 4) & 0x1; }
INLINE U32 chexInfoStatNoCx(U32 uStat)      { return (uStat >> 5) & 0x1; }

INLINE U32 chexInfoStatCalcFx(U32 uStat)    { return (uStat >> 6) & 0x1; }
INLINE U32 chexInfoStatCodeFx(U32 uStat)    { return (uStat >> 7) & 0x1; }
INLINE U32 chexInfoStatNoFx(U32 uStat)      { return (uStat >> 8) & 0x1; }

INLINE U32 chexInfoStatXForm(U32 uStat)      { return (uStat >> 9) & 0x1;  }
INLINE U32 chexInfoStatXFormRecon(U32 uStat) { return (uStat >> 10) & 0x1; }

INLINE U32 chexInfoStatMLTProc(U32 uStat) { return (uStat >> 11) & 0x1; }

INLINE U32 chexInfoStatCreateMono(U32 uStat) { return (uStat >> 12) & 0x1; }

INLINE U32 chexInfoStatCodeBs(U32 uStat) { return (uStat >> 13) & 0x1; }

// ========================================================

INLINE Void chexReleaseCxCodeAnchor(ReconTileInfo *prti)
{
    if (prti->m_pcxartiCode)
    {
        prti->m_pcxartiCode->m_iRefCount--;
        prti->m_pcxartiCode = NULL;
    }
}

INLINE Void chexReleaseCxSegAnchor(ReconTileInfo *prti)
{
    if (prti->m_pcxartiSeg)
    {
        prti->m_pcxartiSeg->m_iRefCount--;
        prti->m_pcxartiSeg = NULL;
    }
}

INLINE Void chexReleaseCxAnchor(ReconTileInfo *prti)
{
    chexReleaseCxCodeAnchor(prti);
    chexReleaseCxSegAnchor(prti);
}

INLINE Void rfxSetReconTileInfo(CAudioObject *pau,
                                ReconProc *prp, ReconTileInfo *prti)
{
    prti->m_prfxrti =
        prp->m_rgrfxrti + prp->m_iTilesInSubframeXFormRecon;

#if defined(_DEBUG)
    assert(WMAB_FALSE == pau->m_bReconFex ||
           NULL == prti->m_prfxrti->m_prti ||
           prti == prti->m_prfxrti->m_prti);
    prti->m_prfxrti->m_prti = prti;
#endif

    prti->m_prfxrti->m_bLastTileInFrame = WMAB_FALSE;
}

INLINE Void rfxReleaseTileInfo(ReconTileInfo *prti)
{
    if (prti->m_prfxrti)
    {
#if defined(_DEBUG)
        prti->m_prfxrti->m_prti = NULL;
#endif
        prti->m_prfxrti = NULL;
    }
}

INLINE Void rfxReleaseTiles(ReconProc *prp, ReconTileInfo *prti)
{
    if (prti->m_prfxrti && prti->m_prfxrti->m_bLastTileInFrame)
    {
        ReconTileInfo *prtiC = prti;
        while (prtiC != NULL)
        {
            rfxReleaseTileInfo(prtiC);
            prtiC = chexPrevTile(prp, prtiC);
        }
    }
}

INLINE Void chexSetTileNotInUse(ReconProc *prp, ReconTileInfo *prti)
{
    prti->m_uInfoStat = 0;
    prti->m_iSizePrev = 0;
    prti->m_iSizeCurr = 0;
    prti->m_iSizeNext = 0;
    prti->m_iTileCnt = -4*prp->m_nTilesInBuf;
    if (prp->m_pfnParentSetTileNotInUse)
        prp->m_pfnParentSetTileNotInUse(prp->m_phParent, prti);
    chexReleaseCxAnchor(prti);
    rfxReleaseTileInfo(prti);
}

INLINE CxAnchorReconTileInfo* chexGetNewAnchor(ReconProc *prp)
{
    assert(0 == prp->m_rgcxarti[prp->m_icxarti].m_iRefCount);
    return prp->m_rgcxarti + prp->m_icxarti;
}

INLINE Void chexUpdateNextAnchorPos(ReconProc *prp)
{
    prp->m_icxarti++;
    if (prp->m_icxarti == prp->m_ncxarti)
        prp->m_icxarti = 0;
}

INLINE Bool chexSetCodeAnchor(ReconTileInfo *prti,
                              CxAnchorReconTileInfo *pcxarti)
{
    if (prti->m_pcxartiCode != pcxarti)
    {
        assert(NULL == prti->m_pcxartiCode);
        chexReleaseCxCodeAnchor(prti);
        prti->m_pcxartiCode = pcxarti;
        pcxarti->m_iRefCount++;
        return WMAB_TRUE;
    }
    return WMAB_FALSE;
}

INLINE Bool chexSetSegAnchor(ReconTileInfo *prti,
                             CxAnchorReconTileInfo *pcxarti)
{
    if (prti->m_pcxartiSeg != pcxarti)
    {
        assert(NULL == prti->m_pcxartiSeg);
        chexReleaseCxSegAnchor(prti);
        prti->m_pcxartiSeg = pcxarti;
        pcxarti->m_iRefCount++;
        return WMAB_TRUE;
    }
    return WMAB_FALSE;
}

INLINE Void chexSetTileHold(ReconTileInfo *prti)
{
    prti->m_uInfoStat = 0;
    chexSetInfoStatAdd(&prti->m_uInfoStat);
}

INLINE U32 chexTileNotInUse(ReconTileInfo *prti)
{
    return (0 == prti->m_uInfoStat);
}

// gets next coded tile, starting at prti
INLINE ReconTileInfo* chexNextCodedTile(ReconProc *prp, ReconTileInfo *prti)
{
    const Chex *pcx = prp->m_pau->m_pcx;
    ReconTileInfo *prtiOrig = prti;

    if (prti->m_bParamsCoded &&
        prti->m_pcxartiCode &&
        prti->m_pcxartiCode->m_bEvenLengthCxSegment)
        prti = chexNextTile(prp, prti);

    while (WMAB_TRUE)
    {
        if (NULL == prti)
            return NULL;

        if (chexInfoStatCode(prti->m_uInfoStat))
            if (prti->m_bParamsCoded)
                return prti;

        // hit the end w/o finding coded tile
        if (chexInfoStatLastTile(prti->m_uInfoStat) |
            chexInfoStatNoCx(prti->m_uInfoStat))
            return prtiOrig;

        if (!chexInfoStatCode(prti->m_uInfoStat))
            return NULL;

        prti = chexNextTile(prp, prti);
    }
}

INLINE U32 chexNextParamsCoded(ReconProc *prp, ReconTileInfo *prti)
{
    while (WMAB_TRUE)
    {
        if (NULL == prti)
            return 0;

        if (chexInfoStatCode(prti->m_uInfoStat))
            if (prti->m_bParamsCoded)
                return 1;

        if (chexInfoStatLastTile(prti->m_uInfoStat) |
            chexInfoStatNoCx(prti->m_uInfoStat))
            return 1;

        if (!chexInfoStatCode(prti->m_uInfoStat))
            return 0;

        prti = chexNextTile(prp, prti);
    }
}

INLINE Bool chexTileReadyForReconCx(ReconProc *prp, ReconTileInfo *prti)
{
    const Chex *pcx = prp->m_pau->m_pcx;
    const U32 uStat = prti->m_uInfoStat;
    ReconTileInfo *prtiNext = prti;
    CxAnchorReconTileInfo *pcxarti = prti->m_pcxartiCode;

    if (prti->m_bParamsCoded &&
        prti->m_pcxartiCode &&
        prti->m_pcxartiCode->m_bEvenLengthCxSegment)
        prtiNext = chexNextTile(prp, prti);

    if (NULL==pcxarti || WMAB_TRUE==pcxarti->m_bCxInterpolate)
        return
            (chexInfoStatCode(uStat) & chexInfoStatNextKnown(uStat) &
             chexNextParamsCoded(prp, prtiNext)) |
            (chexInfoStatCode(uStat) & chexInfoStatLastTile(uStat)) |
            chexInfoStatNoCx(uStat);
    else
        return
            (chexInfoStatCode(uStat) & chexInfoStatNextKnown(uStat)) |
            (chexInfoStatCode(uStat) & chexInfoStatLastTile(uStat)) |
            chexInfoStatNoCx(uStat);
}

INLINE Bool chexTileReadyForReconFex(ReconProc *prp, ReconTileInfo *prti)
{
    const U32 uStat = prti->m_uInfoStat;

    return
        (chexInfoStatCodeFx(uStat) & chexInfoStatNextKnown(uStat)) |
        (chexInfoStatCodeFx(uStat) & chexInfoStatLastTile(uStat)) |
        chexInfoStatNoFx(uStat);
}

INLINE Bool chexTileReadyForRecon(ReconProc *prp, ReconTileInfo *prti)
{
    if (WMAB_TRUE == prp->m_pau->m_bReconFex && WMAB_TRUE == prp->m_pau->m_bCx)
        return chexTileReadyForReconCx(prp, prti) &&
            chexTileReadyForReconFex(prp, prti);
    else if (WMAB_TRUE == prp->m_pau->m_bCx)
        return chexTileReadyForReconCx(prp, prti);
    else if (WMAB_TRUE == prp->m_pau->m_bReconFex)
        return chexTileReadyForReconFex(prp, prti);
    else
        return (chexInfoStatNextKnown(prti->m_uInfoStat) |
                chexInfoStatLastTile(prti->m_uInfoStat));
}

INLINE Bool chexTileReadyForReconNoCx(ReconProc *prp, ReconTileInfo *prti)
{
    if (WMAB_TRUE == prp->m_pau->m_bReconFex)
        return chexTileReadyForReconFex(prp, prti);
    else
        return (chexInfoStatNextKnown(prti->m_uInfoStat) |
                chexInfoStatLastTile(prti->m_uInfoStat));
}

#if (CX_DECODE_MONO==0)
#define CHEX_FULL_SPECTRUM(prti) \
    (!prti->m_pcxartiSeg || 0 == prti->m_pcxartiSeg->m_iStartBand)
#else
#define CHEX_FULL_SPECTRUM(prti) (1)
#endif

// ========================================================

INLINE Void cxUpdateMaxStartBandIndex(Chex *pcx)
{
    pcx->m_iMaxStartBandIndex++;
    if (NUM_CX_MAXBANDDEP == pcx->m_iMaxStartBandIndex)
        pcx->m_iMaxStartBandIndex = 0;
}

INLINE Void cxUpdateFrameMaxStartBand(Chex *pcx,
                                      CxAnchorReconTileInfo *pcxarti)
{
    pcx->m_rgiMaxStartBandForFrame[pcx->m_iMaxStartBandIndex] =
        max(pcx->m_rgiMaxStartBandForFrame[pcx->m_iMaxStartBandIndex],
            pcxarti->m_iStartBand);
}

INLINE Void cxUpdateCurrMaxStartBand(Chex *pcx)
{
    Int i;
    pcx->m_iMaxStartBandCurr = 0;
    for (i=0; i < NUM_CX_MAXBANDDEP; i++)
        pcx->m_iMaxStartBandCurr =
            max(pcx->m_iMaxStartBandCurr, pcx->m_rgiMaxStartBandForFrame[i]);
}

// ======================================================================

INLINE
Int chexChannelsInGroup(CAudioObject *pau,
                        ReconTileInfo *prti, Int iGrp, Int *piCh0, Int *piCh1)
{
    Int nCh, iCh;

    nCh = 0;
    *piCh0 = 0;
    *piCh1 = 0;
    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        if (prti->m_rguGroupCh[iGrp] & (1<<iCh))
        {
            if (0 == nCh)
            {
                *piCh0 = iCh;
                nCh++;
            }
            else if (1 == nCh)
            {
                *piCh1 = iCh;
                nCh++;
            }
            else
            {
                assert(0);
                nCh++;
            }
        }
    }

    return nCh;
}

// ======================================================================

Int chexReduceBands(Int *piBandSizes, Int nBands, Int nBandsFinal);
Void chexSetTileParamsFromGlobalParam(Chex *pcx,
                                      CxAnchorReconTileInfo *pcxarti);
WMARESULT chexInitTileConfig(Chex *pcx, ReconTileInfo *prti, Bool bUseSeg,
                             Int iSizeCurr);
Void chexCopyParams(Chex *pcx, ReconTileInfo *prtiDst, ReconTileInfo *prtiSrc);
#if defined(_DEBUG) || !defined(UNDER_CE)
Void chexDumpCodedParams(CAudioObject *pau, ReconTileInfo *prti, FILE *fp);
#endif
Int chexTilesInFrame(CAudioObject *pau);
Void chexSetDefaultTileParamsCh(ReconTileInfo *prti, Int iCh,
                                Int iStartBand, Int iEndBand);

// ======================================================================
// QuantFlt functions

WMARESULT qfInit(QuantFlt *pqf, ChexType fMin, ChexType fMax,
                 Int iBins, Int iBinsPred, Bool bRndSign);

INLINE
ChexType qfInRange(QuantFlt *pqf, ChexType fVal)
{
    return checkRange(fVal, pqf->m_fMin, CX_FROM_FLOAT(pqf->m_fMax*0.999f));
}

INLINE
ChexType qfLogInRange(QuantFlt *pqf, Float fVal)
{
    assert(fVal >= 0);

    if (fVal != 0)
        return qfInRange(pqf, CX_FROM_FLOAT((Float)log10(fVal)));
    else
        return pqf->m_fMin;
}

INLINE
ChexType qfLogInRangeRnd(QuantFlt *pqf, Float fVal)
{
    assert(fVal >= 0);

    if (fVal != 0)
        return checkRange(CX_FROM_FLOAT((Float)log10(fVal)),
                          -pqf->m_fMax, pqf->m_fMax);
    else
        return -pqf->m_fMax;
}

INLINE
Int qfQuant(QuantFlt *pqf, ChexType fVal)
{
    Int iIndex;

    assert(fVal >= pqf->m_fMin && fVal < pqf->m_fMax);
    fVal -= pqf->m_fMin;

    iIndex = CX_FLOOR(fVal, pqf->m_fStep);

    return iIndex;
}

// iPredDec is with fMin as offset in units of fMinStepHalf
INLINE
Int qfQuantPred(QuantFlt *pqf, ChexType fVal, Int iPredDec)
{
    Int iIndex;

    assert(fVal >= pqf->m_fMin && fVal < pqf->m_fMax);
    fVal -= pqf->m_fMin;

    // now subtract off prediction (in integer domain)
    fVal -= (iPredDec-pqf->m_iMinStepHalfBins)*pqf->m_fMinStepHalf;

    iIndex = CX_FLOOR(fVal, pqf->m_fStepPred);

    return iIndex;
}

INLINE
Int qfQuantRnd(QuantFlt *pqf, ChexType fVal)
{
    Int iIndex;

    assert(fVal >= pqf->m_fMin-pqf->m_fStep/2 &&
           fVal <  pqf->m_fMax+pqf->m_fStep/2);
    fVal -= pqf->m_fMin;

    iIndex = CX_ROUND(fVal, pqf->m_fStep);
    iIndex = checkRange(iIndex, 0, pqf->m_iBins-1);

    return iIndex;
}

INLINE
Int qfWrapParam(QuantFlt *pqf, Int iIndex)
{
    // make sure param is between -(pqf->m_iBins-1) & (pqf->m_iBins-1)
    while (iIndex >= pqf->m_iBins)
    {
        iIndex -= 2*(pqf->m_iBins-1);
    }
    while (iIndex <= -pqf->m_iBins+1)
    {
        iIndex += 2*(pqf->m_iBins-1);
    }

    return iIndex;
}

// the use of integer math for both non-prediction and prediction cases
// makes it easier for integerization as well as for lookup tables, since
// we have a limited number of outputs, can also do similar things for deadzone
// i.e. handle deadzone in integer domain
//
// setpsize is in ChexType, index is just integer
INLINE
ChexType qfInvQuant(QuantFlt *pqf, Int iIndex, Int *piPredDec)
{
    assert(iIndex >= 0 && iIndex < pqf->m_iBins);
    *piPredDec = (2*iIndex+1)*pqf->m_iStep;

    assert(*piPredDec >= 0 && *piPredDec <= pqf->m_iMinStepHalfBins);
    
    return *piPredDec*pqf->m_fMinStepHalf + pqf->m_fMin;
}

INLINE
ChexType qfInvQuantPred(QuantFlt *pqf, Int iIndex, Int *piPredDec)
{
    Int iPredDec;

    assert(iIndex >= 0 && iIndex < pqf->m_iBinsPred);
    iPredDec = (2*iIndex+1)*pqf->m_iStepPred;

    iPredDec += *piPredDec-pqf->m_iMinStepHalfBins;
    
    assert(iPredDec >= -1 && iPredDec <= pqf->m_iMinStepHalfBins+1);
    iPredDec = checkRange(iPredDec, 0, pqf->m_iMinStepHalfBins);

    *piPredDec = iPredDec;

    return *piPredDec*pqf->m_fMinStepHalf + pqf->m_fMin;
}

INLINE
ChexType qfInvQuantRnd(QuantFlt *pqf, Int iIndex)
{
    return iIndex*pqf->m_fStep + pqf->m_fMin;
}

// ================================================================

#define USE_LRPOWERMATRIX (5)
#define USE_LRPOWERMATRIXLMRM (6)

#define SET_CODING_FLAG(flag, field) flag |= 1<<(field)
#define UNSET_CODING_FLAG(flag, field) flag &= ~(1<<(field))
#define IS_SET_FLAG(flag, field) ((flag) & (1<<(field)))

// ================================================================

WMARESULT chexSetTileSegmentParameters(CAudioObject *pau, ReconTileInfo *prtiOrig);

Int chexMaxBandsToIndex(Int iMaxBands, Int iPlusVersion);

// ================================================================

INLINE
Int chexGetFexChannel(CAudioObject *pau, Int iCh)
{
    Int i;
    const Chex *pcx = pau->m_pcx;

    if (!pau->m_bCxPresent)
        return iCh;

    for (i=0; i < pau->m_cChannel; i++)
        if (pcx->m_rguFexChannel[i] & (1<<iCh))
            return i;

    assert(WMAB_FALSE);
    return -1;
}

Void chexTransferCommonFexParams(Fex *pfx, RFxReconTileInfo *prti,
                                 Bool bFexToChex);

Void chexTransferPerChannelFexParams( const RFxReconTileInfo * const prti,
                                            PerChannelInfo   * const ppcinfo,
                                            PerChannelRecon  * const ppcr,
                                      const Bool bFexToChex,
                                      const Bool bOnlyScaleFac );

Int reconProcGetFrameTiles(ReconProc *prp, Int iOffset);

Void chexGetRMLimits(Chex *pcx, const Int iLM, Int *piMinRM, Int *piMaxRM,
                     const CxPredType predType, const Int iPrevRM);

// ================================================================

//#define CHEX_EXP
#if defined(CHEX_EXP) && !defined(ALLOW_EXTERNAL_FILE_FOR_RECON)
#error "should define both CHEX_EXP and ALLOW_EXTERNAL_FILE_FOR_RECON"
#endif

#ifdef __cplusplus
}
#endif

#endif // BUILD_WMAPROLBRV1

#endif // __CHEX_H_
