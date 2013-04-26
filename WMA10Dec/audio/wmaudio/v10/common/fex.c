//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "msaudio.h"
#include "fex.h"
#include "fexdectbls.h"
#include "catchflops.h"
 
// =========================================================================

#if defined(BUILD_WMAPROLBRV1)

#if defined(BUILD_INTEGER) && defined(FEX_POW10_OPT)
U32 g_pow2LUT[FEX_P2LUT_SIZE] = {0};
U32 g_p2lut_init = 0;
#endif // BUILD_INTEGER && FEX_POW10_OPT

#if defined(FEX_DBG_PRINT)
Bool g_fxdbgprint = WMAB_FALSE;
#endif

#ifdef FEX_WRITEINDEX

Bool g_fWriteIndex = WMAB_TRUE; // only in training phase
char *g_exargfile = "fexhuffargs.txt";
int g_nscbins;
int g_nmvbins;
int g_nscbinspred;
int g_nmvbinspred;
int g_nstartposbins = FEX_STARTPOSBINS;

WMARESULT freqexInitExArgs(Fex *pfx)
{
    WMARESULT wmaResult = WMA_OK;
    FILE *fexargs=NULL;

    g_nmvbins = pfx->m_cMvBins;
    g_nmvbinspred = pfx->m_cMvBinsPred;

    g_nscbins = pfx->m_cScaleBins;
    g_nscbinspred = pfx->m_cScaleBinsPred;

    fexargs = fopen(g_exargfile, "rt");
    if (NULL!=fexargs)
    {
        char argval[100]; // how to know what is max size when reading string?
        while (fscanf(fexargs, "%s", argval) != EOF) {
            if (!strcmpi(argval, "-noindex"))
            {
                g_fWriteIndex = WMAB_FALSE;
                printf("No index dump\n");
            }
            else if (!strcmpi(argval, "-nscbins"))
            {
                fscanf(fexargs, "%d", &g_nscbins);
                printf("Number of scale bins = %d\n", g_nscbins);
            }
            else if (!strcmpi(argval, "-nscbinspred"))
            {
                fscanf(fexargs, "%d", &g_nscbinspred);
                printf("Number of scale bins pred = %d\n", g_nscbinspred);
            }
            else if (!strcmpi(argval, "-nmvbins"))
            {
                fscanf(fexargs, "%d", &g_nmvbins);
                printf("Number of mv bins = %d\n", g_nmvbins);
            }
            else if (!strcmpi(argval, "-nmvbinspred"))
            {
                fscanf(fexargs, "%d", &g_nmvbinspred);
                printf("Number of mv bins pred = %d\n", g_nmvbinspred);
            }
            else if (!strcmpi(argval, "-nstartposbins"))
            {
                fscanf(fexargs, "%d", &g_nstartposbins);
                printf("Number of start pos bins = %d\n", g_nstartposbins);
            }
            else
            {
                printf("don't understand %s", argval);
                wmaResult = WMA_E_FAIL;
                goto exit;
            }
        }
    }
    else
    {
        //printf("file %s not found\n", g_exargfile);
        //wmaResult = WMA_E_FAIL;
        //goto exit;
    }

exit:
    return wmaResult;
}

#endif // #ifdef FEX_WRITEINDEX

// =========================================================================

#include "fexnoise.c"
AVRT_DATA const Int g_iFexNoiseLen = 1024;
AVRT_DATA const Int g_iFexMaxNoiseBandSize = 1024-FEX_NUMNOISETRY+1;

// =========================================================================

AVRT_DATA const Int g_iFexNumBandSize = 4;
AVRT_DATA const Int g_rgiFexBandSizesM[] = {1, 2, 4, 8};
AVRT_DATA Int g_rgiFexNBandsAtSize[] = {0, 2, 4, 8, 16};
#ifdef BUILD_WMAPROLBRV2
AVRT_DATA const Int g_rgiFexBandSizesMLinearSlope[] = {2, 3, 4, 5};
#endif

Void freqexSetMvBins(Fex *pfx)
{
    // multiplier will be a power of 2
    if (pfx->m_iPrevMvBinsMultiplier != pfx->m_iMvBinsMultiplier)
    {
        pfx->m_cMvBins = pfx->m_cMvDefaultBins * pfx->m_iMvBinsMultiplier;
        pfx->m_cMvBinsPred = pfx->m_cMvBins;

        pfx->m_cMvBits = LOG2((U32)pfx->m_cMvBins);
#if 1
        pfx->m_iPredMvClose = pfx->m_cMvBinsPred/8 - 1;
        pfx->m_iPredMvLeftClose = pfx->m_cMvBinsPred/16 - 1;
        pfx->m_iPredMvRightClose = pfx->m_cMvBinsPred/16;
        pfx->m_iPredMvCloseBits = LOG2((U32)pfx->m_cMvBinsPred) - 3;
        pfx->m_iPredMvRemVals = pfx->m_cMvBinsPred*7/8;
#else
        pfx->m_iPredMvClose = pfx->m_cMvBinsPred/16 - 1;
        pfx->m_iPredMvLeftClose = pfx->m_cMvBinsPred/32 - 1;
        pfx->m_iPredMvRightClose = pfx->m_cMvBinsPred/32;
        pfx->m_iPredMvCloseBits = LOG2((U32)pfx->m_cMvBinsPred) - 4;
        pfx->m_iPredMvRemVals = pfx->m_cMvBinsPred*15/16;
#endif
        pfx->m_iPredMvRemValsBits = CEILLOG2((U32)pfx->m_iPredMvRemVals);
        pfx->m_iPredMvRemShortVals =
            (1<<pfx->m_iPredMvRemValsBits)-pfx->m_iPredMvRemVals;

        pfx->m_iPrevMvBinsMultiplier = pfx->m_iMvBinsMultiplier;
    }
}

Void freqexSetScBins(Fex *pfx)
{
    // multiplier will be a power of 2
    if (pfx->m_iPrevScBinsMultiplier != pfx->m_iScBinsMultiplier)
    {
        pfx->m_cScaleBins = pfx->m_cScaleDefaultBins*pfx->m_iScBinsMultiplier;
        pfx->m_cScaleBinsPred = pfx->m_cScaleBins;

        // following 2 only used if FEX_WRITEINDEX defined
        pfx->m_cScaleBits = CEILLOG2((U32)pfx->m_cScaleBins);
        pfx->m_cScaleBitsPred = CEILLOG2((U32)pfx->m_cScaleBinsPred);
        pfx->m_cScaleIndexExtraBits =
            LOG2((U32)pfx->m_cScaleBins/FEX_SCBINSHUFF);
        assert((1<<pfx->m_cScaleIndexExtraBits)*FEX_SCBINSHUFF ==
               pfx->m_cScaleBins);
        pfx->m_cScaleResIndexMask  = (1<<pfx->m_cScaleIndexExtraBits)-1;
        pfx->m_cScaleHuffIndexMask = (~0 & ~(pfx->m_cScaleResIndexMask));

#if !defined(BUILD_INTEGER)
        pfx->m_fltScaleQuantStep     =     MAX_FEXLOGSCALE  / pfx->m_cScaleBins;
        pfx->m_fltScaleQuantStepPred = ( 2*MAX_FEXLOGSCALE )/ pfx->m_cScaleBinsPred;
#endif

        // reconstruction for non prediction is:
        // (i+0.5)*deltanopred, i an integer
        // reconstruction for prediction is:
        // (i+0.5)*deltapred - range + prev, i an integer
        // suppose deltanopred = delta*Np & deltapred = delta*N
        // then, recon for all cases is given by
        // (i+0.5)*delta*N + delta*M + prev, which is a multiple of delta/2
        // by recursion, all reconstructions will be at a multiple of delta/2,
        // where delta is smallest delta, do any thresholding at multiple
        // delta/2*1.5 = 3*delta/4
    }
    pfx->m_iMvThreshold = 2;
}

WMARESULT freqexInit(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(pau->m_fex);
    Int iIndex, iAllocBands, iAllocCh;

    pfx->m_pau = pau;

    // Fex version always matches LBR version
    pfx->m_iVersion = pau->m_iPlusVersion;

    if (pau->m_bPlusV1)
    {
        iIndex = (pau->m_iAdvancedEncodeOpt & ENCOPT4_FEXMVBINS) >>
            ENCOPT4_FEXMVBINS_BITSOFFSET;
        pfx->m_cMvDefaultBins = freqexIndexToMvBins(iIndex);
        pfx->m_iPrevMvBinsMultiplier = 0;
        pfx->m_iMvBinsMultiplier = 1;

        iIndex = (pau->m_iAdvancedEncodeOpt & ENCOPT4_FEXSCBINS) >>
            ENCOPT4_FEXSCBINS_BITSOFFSET;
        pfx->m_cScaleDefaultBins = freqexIndexToScaleBins(iIndex);
        pfx->m_iPrevScBinsMultiplier = 0;
        pfx->m_iScBinsMultiplier = 1;

        iIndex = (pau->m_iAdvancedEncodeOpt & ENCOPT4_FEXMAXBANDS) >>
            ENCOPT4_FEXMAXBANDS_BITSOFFSET;
        pfx->m_cMaxBands = freqexIndexToMaxBands(iIndex);
    }
    else if(pau->m_bPlusV2)
    {
        iIndex = (pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_FEXMAXBANDS) >>
            ENCOPT4_PLUSV2_FEXMAXBANDS_BITSOFFSET;
        pfx->m_cMaxBands = freqexIndexToMaxBands(iIndex);
    }
    // *2 since uniform / arbitrary allow for 2x of max bands
    pfx->m_cMaxBands *= 2; // for purposes of allocation

    if (1 == pfx->m_iVersion)
        // *2x for Rico split
        iAllocBands = pfx->m_cMaxBands * 2;
    else
        iAllocBands = pfx->m_cMaxBands;

    if (pau->m_bCx && !pau->m_bEncoder)
        iAllocCh = pau->m_pcx->m_iMaxPairs;
    else
        iAllocCh = pau->m_cChannel;
    pfx->m_iAllocCh = iAllocCh;

    pau->m_rgiFexLogScaleFacIndex =
        (I32*)auMalloc(iAllocCh*iAllocBands*sizeof(I32));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexLogScaleFacIndex);

    // *2 for (total, noise)
    pau->m_rgffltFexScaleFac =
        (FastFloat*)auCalloc(iAllocCh*iAllocBands*sizeof(FastFloat)*2);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgffltFexScaleFac);

    pfx->m_pffltFexScaleFacPeaks =
        (FastFloat*)auCalloc(iAllocBands*sizeof(FastFloat));
    CHECKWMA_ALLOC(wmaResult, pfx->m_pffltFexScaleFacPeaks);

    pfx->m_pffltFexScaleFacNoise = 
        (FastFloat*)auMalloc(iAllocBands*sizeof(FastFloat));
    CHECKWMA_ALLOC(wmaResult, pfx->m_pffltFexScaleFacNoise);

    // *2 here for iMv and iMv2 (2 motion vector case)
    pau->m_rgiFexMv = (Int*)auMalloc(iAllocCh*iAllocBands*sizeof(Int)*2);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexMv);
    pau->m_rgiFexCb = (Int*)auMalloc(iAllocCh*iAllocBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexCb);
    pau->m_rgFexExp = (FexType*)auMalloc(iAllocCh*iAllocBands*sizeof(FexType));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgFexExp);

    pau->m_rgiFexSign = (Int*)auMalloc(iAllocCh*iAllocBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexSign);

    pau->m_rgbFexRev = (Bool*)auMalloc(iAllocCh*iAllocBands*sizeof(Bool));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgbFexRev);

    pfx->m_rgiBandStart = (Int*)auCalloc(pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiBandStart);

    pfx->m_rgiScaleBandSizes = (Int*)auMalloc(pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiScaleBandSizes);
    pfx->m_piScaleBandSizes = pfx->m_rgiScaleBandSizes;

    pfx->m_rgiMvBandSizes = (Int*)auMalloc(pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiMvBandSizes);
    pfx->m_piMvBandSizes    = pfx->m_rgiMvBandSizes;

    pfx->m_rgiBandSizeM = (Int*)auMalloc(iAllocCh*pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiBandSizeM);
    pfx->m_rgiExpBandSizeM = (Int*)auMalloc(pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiExpBandSizeM);
    pfx->m_rgiMaxBandsTemp = (Int*)auMalloc(pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiMaxBandsTemp);

    pfx->m_rgcScaleBandsPerMvBand = (Int*)auMalloc(pfx->m_cMaxBands*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgcScaleBandsPerMvBand);

    pfx->m_rgiChCode = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgiChCode);

    if (pfx->m_iVersion > 1)
    {
        Int iSize;

        iSize = iAllocCh*pfx->m_cMaxBands;

        pau->m_rgffltFexScaleFacBase =
            (FastFloat*)auCalloc(iSize*sizeof(FastFloat));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgffltFexScaleFacBase);

        pau->m_rgiFexLogScaleFacBaseIndex =
            (I32*)auMalloc(iSize*sizeof(I32));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexLogScaleFacBaseIndex);

        pau->m_rgiFexLogScaleFacIndexRef =
            (I32*)auMalloc(pau->m_cChannel*sizeof(I32));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexLogScaleFacIndexRef);

        pau->m_rgcFexSubframesMvMerged =
            (I32*)auMalloc(pau->m_cChannel*sizeof(I32));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgcFexSubframesMvMerged);

        pau->m_rgFexScaleFacPred =
            (FexScaleFacPredType*)auMalloc(pau->m_cChannel*sizeof(FexScaleFacPredType));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgFexScaleFacPred);

        pau->m_rgFexScaleFacBasePred =
            (FexScaleFacPredType*)auMalloc(iAllocCh*sizeof(FexScaleFacPredType));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgFexScaleFacBasePred);

        pfx->m_rgiBaseBandSizes = (Int*)auMalloc(pfx->m_cMaxBands*sizeof(Int));
        CHECKWMA_ALLOC(wmaResult, pfx->m_rgiBaseBandSizes);
        pfx->m_piBaseBandSizes = pfx->m_rgiBaseBandSizes;

        pau->m_rgffBandScale =
            (FastFloat*)auCalloc(iSize*sizeof(FastFloat));
        CHECKWMA_ALLOC(wmaResult, pau->m_rgffBandScale);

#if defined(BUILD_WMAPROLBRV2)
        {
            Int iCh;
            Int iMaxTiles = reconProcGetMaxTiles(pau);

            if (!pau->m_bReconFex)
                iMaxTiles = 1;

            pfx->m_rgrgpfLogScaleFac = 
                (FastFloat**)auCalloc(iMaxTiles * sizeof(FastFloat*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgrgpfLogScaleFac);

            pfx->m_rgrgpfLogScaleFacBase = 
                (FastFloat**)auCalloc(iMaxTiles * sizeof(FastFloat*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgrgpfLogScaleFacBase);

            pfx->m_rgrgpiLogScaleFacIndex = 
                (Int***)auCalloc(iMaxTiles * sizeof(Int**));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgrgpiLogScaleFacIndex);

            pfx->m_rgrgpiLogScaleFacBaseIndex = 
                (Int***)auCalloc(iMaxTiles * sizeof(Int**));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgrgpiLogScaleFacBaseIndex);

            pfx->m_rgpiLogScaleFacRef = 
                (Int**)auCalloc(iMaxTiles * sizeof(Int*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgpiLogScaleFacRef);

            pfx->m_rgpScFacPredType = 
                (FexScaleFacPredType**)auCalloc(iMaxTiles * sizeof(FexScaleFacPredType*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgpScFacPredType);

            pfx->m_rgpScFacBasePredType = 
                (FexScaleFacPredType**)auCalloc(iMaxTiles * sizeof(FexScaleFacPredType*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgpScFacBasePredType);

            pfx->m_rgrgiScFacResidualIndex =
                (Int**)auCalloc(iAllocCh * sizeof(Int*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgrgiScFacResidualIndex);
            for (iCh = 0; iCh < iAllocCh; iCh++)
            {
                pfx->m_rgrgiScFacResidualIndex[iCh] =
                    (Int*)auCalloc(iMaxTiles * pfx->m_cMaxBands * sizeof(Int));
                CHECKWMA_ALLOC(wmaResult, pfx->m_rgrgiScFacResidualIndex[iCh]);
            }

            pfx->m_rguScFacSignIndex = 
                (UInt*)auCalloc(((iMaxTiles * pfx->m_cMaxBands + sizeof(UInt) * BITS_PER_BYTE - 1)
                                  / (sizeof(UInt) * BITS_PER_BYTE)) * sizeof(UInt) );
            CHECKWMA_ALLOC(wmaResult, pfx->m_rguScFacSignIndex);

            pfx->m_rgiScFacFirstNoRef = 
                (Int*)auCalloc(iMaxTiles * sizeof(Int));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgiScFacFirstNoRef);

            pfx->m_rgiScFacResidualBufOffset =
                (Int*)auCalloc(iAllocCh * sizeof(Int));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgiScFacResidualBufOffset);

            pfx->m_rgprtiMvAnchor =
                (ReconTileInfo**)auCalloc(pau->m_cChannel * sizeof(ReconTileInfo*));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgprtiMvAnchor);

            pfx->m_rgcScFacBaseBands =
                (Int*)auCalloc(iMaxTiles * sizeof(Int));
            CHECKWMA_ALLOC(wmaResult, pfx->m_rgcScFacBaseBands);

            pau->m_rgiFexMvOffsetNoiseCB = (Int*)auMalloc(iAllocCh*iAllocBands*sizeof(Int));
            CHECKWMA_ALLOC(wmaResult, pau->m_rgiFexMvOffsetNoiseCB);
        }
#endif
#ifdef BUILD_WMAPROLBRV3
        if( pfx->m_iVersion > 2 )
        {
            pau->m_iMaxBasePeakCoef = 32;
            pau->m_rgiBasePeakCoefPos = (I16*)auCalloc(pau->m_cChannel * pau->m_iMaxBasePeakCoef * sizeof(I16));
            CHECKWMA_ALLOC(wmaResult, pau->m_rgiBasePeakCoefPos);
            pau->m_rgcBasePeakCoefs = (Int*)auCalloc(pau->m_cChannel * sizeof(Int));
            CHECKWMA_ALLOC(wmaResult, pau->m_rgcBasePeakCoefs);
            pau->m_rgiBasePeakMaskQSave = (Int*)auCalloc(pau->m_cChannel * MAX_SF_BANDS * sizeof(Int));
            CHECKWMA_ALLOC(wmaResult, pau->m_rgiBasePeakMaskQSave);
        }
#endif
    }

    pfx->m_piFexBandSizesM = g_rgiFexBandSizesM;
    g_rgiFexNBandsAtSize[g_iFexNumBandSize] = pfx->m_cMaxBands;
    pfx->m_piBaseBandSizesM = g_rgiFexBandSizesM;

#ifdef FEX_WRITEINDEX
    TRACEWMA_EXIT(wmaResult, freqexInitExArgs(pfx));
    pfx->m_cScaleBins     = g_nscbins;
    pfx->m_cMvBins        = g_nmvbins;
    pfx->m_cScaleBinsPred = g_nscbinspred;
    pfx->m_cMvBinsPred    = g_nmvbinspred;
    pfx->m_cStartPosBins  = g_nstartposbins;
#else
    // in scalar quantization, entropy coded uniform quantization
    // is as good as non-uniform quantization
    pfx->m_cStartPosBins = FEX_STARTPOSBINS;
#endif

    freqexSetScBins(pfx);
    freqexSetMvBins(pfx);

    pfx->m_cBandsBits = LOG2((U32)pfx->m_cMaxBands/2);
    pfx->m_cStartPosBits  = LOG2((U32)pfx->m_cStartPosBins);

    // calculate end pos bits/bins
    pfx->m_cEndPosBits =
        CEILLOG2((pau->m_iSamplingRate/2 - FEX_MINMAXBW)/FEX_BWRES);
    pfx->m_cEndPosBins = ( 1 << pfx->m_cEndPosBits );

#ifdef BUILD_INTEGER
    pfx->m_iBitScale = freqexBitScale(pau);
#else
    pfx->m_fBitScale = freqexBitScale(pau);
#endif

    pfx->m_iMinBandSize = 1;
    pfx->m_iMaxBandSize = g_iFexMaxNoiseBandSize;

    //pfx->m_bMergeNoiseVecAdj = WMAB_TRUE;
    //pfx->m_bMergeNoiseVecAll = WMAB_TRUE;
    //pfx->m_bUseRandomNoise = WMAB_TRUE;
    //pau->m_bDoFexOnCodedChannels = WMAB_TRUE;
    pau->m_bTileReconFex  = WMAB_FALSE;
#if defined(BUILD_WMAPROLBRV2) && defined(TEST_RECONFEX)
    pau->m_bTileReconFex = 1;
#endif

    // only needs to be as large as largest band actually (769), and can 
    // be optimized by making it a bit mask (needs only ceil(769/8) = 97 bytes)
    {
        Int iMaskSize = (pau->m_bEncoder ? pau->m_cFrameSampleHalf :
                         pfx->m_iMaxBandSize);
        pfx->m_rgucCwMask = (U8*)auMalloc(iMaskSize*sizeof(U8));
        CHECKWMA_ALLOC(wmaResult, pfx->m_rgucCwMask);
    }

    // only needed for virtual channel case, after chex experiments done
    // possibly can be removed
    if (pau->m_bEncoder)
    {
        pfx->m_rgfReconChannel =
            (CoefType*)auMalloc(pau->m_cFrameSampleHalf*sizeof(CoefType));
        CHECKWMA_ALLOC(wmaResult, pfx->m_rgfReconChannel);
    }

    pfx->m_rgbMvCoded = (Bool*)auMalloc(pfx->m_cMaxBands*sizeof(Bool)*2);
    CHECKWMA_ALLOC(wmaResult, pfx->m_rgbMvCoded);

    pfx->m_bFirstTile = WMAB_TRUE;
    if (pfx->m_iVersion > 1)
        pfx->m_bFirstTileV2Coding = WMAB_TRUE;

exit:
    return wmaResult;
}

Void freqexReset(CAudioObject *pau)
{
    Fex *pfx = &(pau->m_fex);
    pfx->m_bSplitTileIntoSubtiles = WMAB_FALSE;
    if (!pau->m_bFreqex)
    {
        pau->m_bFreqexPresent = WMAB_FALSE;
    }
}

Void freqexFree(CAudioObject *pau)
{
    Fex *pfx = &(pau->m_fex);
    Int iCh;

    DELETE_ARRAY(pfx->m_rgfReconChannel);

    DELETE_ARRAY(pau->m_rgiFexLogScaleFacIndex);

    DELETE_ARRAY(pau->m_rgffltFexScaleFac);
    DELETE_ARRAY(pfx->m_pffltFexScaleFacPeaks);
    DELETE_ARRAY(pfx->m_pffltFexScaleFacNoise);
    DELETE_ARRAY(pau->m_rgiFexMv);
    DELETE_ARRAY(pau->m_rgiFexMvOffsetNoiseCB);
    DELETE_ARRAY(pau->m_rgiFexCb);
    DELETE_ARRAY(pau->m_rgFexExp);
    DELETE_ARRAY(pau->m_rgiFexSign);
    DELETE_ARRAY(pau->m_rgbFexRev);

    DELETE_ARRAY(pfx->m_rgiBandStart);

    DELETE_ARRAY(pau->m_rgffltFexScaleFacBase);
    DELETE_ARRAY(pau->m_rgiFexLogScaleFacBaseIndex);
    DELETE_ARRAY(pau->m_rgiFexLogScaleFacIndexRef);
    DELETE_ARRAY(pau->m_rgcFexSubframesMvMerged);
    DELETE_ARRAY(pau->m_rgFexScaleFacPred);
    DELETE_ARRAY(pau->m_rgFexScaleFacBasePred);
#ifdef BUILD_WMAPROLBRV3
    DELETE_ARRAY(pau->m_rgiBasePeakCoefPos);
    DELETE_ARRAY(pau->m_rgcBasePeakCoefs);
    DELETE_ARRAY(pau->m_rgiBasePeakMaskQSave);
#endif
    DELETE_ARRAY(pfx->m_rgiScaleBandSizes);
    DELETE_ARRAY(pfx->m_rgiMvBandSizes);
    DELETE_ARRAY(pfx->m_rgiBaseBandSizes);

    DELETE_ARRAY(pfx->m_rgiBandSizeM);
    DELETE_ARRAY(pfx->m_rgiExpBandSizeM);

    DELETE_ARRAY(pfx->m_rgiMaxBandsTemp);

    DELETE_ARRAY(pfx->m_rgcScaleBandsPerMvBand);

    DELETE_ARRAY(pfx->m_rgiChCode);

    DELETE_ARRAY(pfx->m_rgucCwMask);

    DELETE_ARRAY(pfx->m_rgbMvCoded);

    if (pau->m_bPlusV1 || pau->m_bPlusV2 || pau->m_bReconProc) {
        DELETE_ARRAY(pau->m_ucNonzeroCoeffMask);
    }

    DELETE_ARRAY(pau->m_rgffBandScale);

    DELETE_ARRAY(pfx->m_rgrgpfLogScaleFac);
    DELETE_ARRAY(pfx->m_rgrgpfLogScaleFacBase);
    DELETE_ARRAY(pfx->m_rgrgpiLogScaleFacIndex);
    DELETE_ARRAY(pfx->m_rgrgpiLogScaleFacBaseIndex);
    DELETE_ARRAY(pfx->m_rgpiLogScaleFacRef);
    DELETE_ARRAY(pfx->m_rgpScFacPredType);
    DELETE_ARRAY(pfx->m_rgpScFacBasePredType);
    if (pfx->m_rgrgiScFacResidualIndex)
    {
        for (iCh = 0; iCh < pfx->m_iAllocCh; iCh++)
            DELETE_ARRAY(pfx->m_rgrgiScFacResidualIndex[iCh]);
        DELETE_ARRAY(pfx->m_rgrgiScFacResidualIndex);
    }
    DELETE_ARRAY(pfx->m_rguScFacSignIndex);
    DELETE_ARRAY(pfx->m_rgiScFacFirstNoRef);
    DELETE_ARRAY(pfx->m_rgiScFacResidualBufOffset);
    DELETE_ARRAY(pfx->m_rgprtiMvAnchor);
    DELETE_ARRAY(pfx->m_rgcScFacBaseBands);
}

// Offset for current subtile in Rico split
WMARESULT freqexOffsetPcInfo( CAudioObject *pau, 
                              PerChannelInfo *ppcinfo,
                        const Int iSubtile)
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(pau->m_fex);

    Int iOffset = pfx->m_cMaxBands * pfx->m_iAllocCh * iSubtile;

    if (pfx->m_bReconDomain)
    {
        assert(0 == iSubtile);
        goto exit;
    }

    ppcinfo->m_pffltFexScaleFac      += 2*iOffset;
    ppcinfo->m_pffltFexScaleFacNoise += 2*iOffset;

    ppcinfo->m_piFexMv  += 2*iOffset;
    ppcinfo->m_piFexMv2 += 2*iOffset;

    ppcinfo->m_piFexCb   += iOffset;
    ppcinfo->m_pFexExp   += iOffset;
    ppcinfo->m_piFexSign += iOffset;
    ppcinfo->m_pbFexRev  += iOffset;

    ppcinfo->m_piFexLogScaleFacIndex += iOffset;

    pfx->m_pbMvCoded += pfx->m_cMaxBands * iSubtile;

    if( pfx->m_iVersion > 1 )
    {
        if (0 != iSubtile) // otherwise bump up allocation for some
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        ppcinfo->m_pffltFexScaleFacBase      += iOffset;
        ppcinfo->m_piFexLogScaleFacBaseIndex += iOffset;

        ppcinfo->m_piFexLogScaleFacIndexRef += iSubtile;
        ppcinfo->m_pcFexSubframesMvMerged += iSubtile;
        ppcinfo->m_piFexMvOffsetNoiseCB += iSubtile;
        ppcinfo->m_pFexScaleFacPred += iSubtile;
        ppcinfo->m_pFexScaleFacBasePred += iSubtile;

        ppcinfo->m_pffBandScale += iOffset;
    }
exit:
    return wmaResult;
}

Void freqexInitPcInfo(       CAudioObject *pau, 
                             PerChannelInfo *ppcinfo, 
                       const Int iChSrc )
{
    Fex *pfx = &(pau->m_fex);

    const Int iOffset  = pfx->m_cMaxBands * iChSrc;
    const Int iOffset2 = pfx->m_cMaxBands * pfx->m_iAllocCh;

    ppcinfo->m_pffltFexScaleFac      = pau->m_rgffltFexScaleFac + iOffset;
    ppcinfo->m_pffltFexScaleFacNoise = pau->m_rgffltFexScaleFac + iOffset + iOffset2;

    ppcinfo->m_piFexMv   = pau->m_rgiFexMv   + iOffset;
    ppcinfo->m_piFexMv2  = pau->m_rgiFexMv   + iOffset + iOffset2;
    ppcinfo->m_piFexCb   = pau->m_rgiFexCb   + iOffset;
    ppcinfo->m_pFexExp   = pau->m_rgFexExp   + iOffset;
    ppcinfo->m_piFexSign = pau->m_rgiFexSign + iOffset;
    ppcinfo->m_pbFexRev  = pau->m_rgbFexRev  + iOffset;

    ppcinfo->m_piFexLogScaleFacIndex = pau->m_rgiFexLogScaleFacIndex + iOffset;

    pfx->m_pbMvCoded = pfx->m_rgbMvCoded;

    if( pfx->m_iVersion > 1 )
    {
        ppcinfo->m_pffltFexScaleFacBase      = pau->m_rgffltFexScaleFacBase + iOffset;
        ppcinfo->m_piFexLogScaleFacBaseIndex = pau->m_rgiFexLogScaleFacBaseIndex + iOffset;

        ppcinfo->m_piFexLogScaleFacIndexRef = pau->m_rgiFexLogScaleFacIndexRef + iChSrc;
        ppcinfo->m_pcFexSubframesMvMerged = pau->m_rgcFexSubframesMvMerged + iChSrc;
        ppcinfo->m_piFexMvOffsetNoiseCB = pau->m_rgiFexMvOffsetNoiseCB + iOffset;
        ppcinfo->m_pFexScaleFacPred = pau->m_rgFexScaleFacPred + iChSrc;
        ppcinfo->m_pFexScaleFacBasePred = pau->m_rgFexScaleFacBasePred + iChSrc;

        ppcinfo->m_pffBandScale = pau->m_rgffBandScale + iOffset;
#ifdef BUILD_WMAPROLBRV3
        if( pfx->m_iVersion > 2 )
        {
            ppcinfo->m_piBasePeakCoefPos   = pau->m_rgiBasePeakCoefPos   + iChSrc * pau->m_iMaxBasePeakCoef;
            ppcinfo->m_pcBasePeakCoefs     = pau->m_rgcBasePeakCoefs     + iChSrc;
            ppcinfo->m_piBasePeakMaskQSave = pau->m_rgiBasePeakMaskQSave + iChSrc * MAX_SF_BANDS;
        }
#endif
    }
}

// =====================================================================

Void freqexSetMvConfig( const CAudioObject   * const pau, Fex * const pfx,
                        const PerChannelInfo * const ppcinfo,
                        const Int cBandSize,
                        const Int iCb,
                        const Int bGetMax )
{
    Int iMaxStart, iPredMv, iMvRange, iMaxLimit, cUnusedSize;
    Bool bUseNoise, bUseMvPred;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + pfx->m_iChSrc;
    FexMvRangeType eMvRangeType = pcis->m_eFxMvRangeType;

    bUseNoise = ((iCb % 2)==1 ? WMAB_TRUE : WMAB_FALSE);

    // The following rules are to be applied when determining range
    // in order of precedence given
    // 1. start + bandsize <= tilesize
    // 2. start + bandsize <= max index that has been coded (by base or fex)+1
    //    start + bandsize <= max(max coded index, band start)
    // 3. base:     start + bandsize <= start of fex
    //    prevband: start + bandsize <= start of band
    //    full:     start + bandsize <= tile size
    // Simplifications:
    // base:     start = min(start of fex, max(max coded index, band start),
    //                       tilesize)
    //           since (band start > start of fex)
    //           start = min(start of fex, tilesize) = start of fex
    // prevband: start = min(band start, max(max coded index, band start),
    //                       tilesize)
    //           start = min(band start, tilesize) = band start
    // full:     start = min(tilesize,
    //                       max(max coded index+bandsize, band start))

    if (pfx->m_iBand < pfx->m_cHoleBands)
        eMvRangeType = MvRangePrevBand;

    // apply rule #3
    switch (eMvRangeType)
    {
    case MvRangeBase:
        iMaxStart = pfx->m_cStart;
        break;
    case MvRangePrevBand:
        iMaxStart = pfx->m_cStartIndex;
        break;
    case MvRangeFullNoOverwriteBase:
    case MvRangeFullOverwriteBase:
        iMaxStart = pfx->m_cTileSize;
        break;
    default:
        iMaxStart = 0;
        assert(WMAB_FALSE);
    }
    // apply rule #2 -- make exception for bMvRangeFull case
    if (pfx->m_iIteration >= 2)
    {
        if (WMAB_TRUE==pfx->m_bMvRangeFull)
            iMaxLimit = max(pfx->m_iMaxLastCodedIndex+cBandSize,
                            pfx->m_cStartIndex);
        else
            iMaxLimit = max(pfx->m_iMaxLastCodedIndex, pfx->m_cStartIndex);
    }
    else
    {
        iMaxLimit = pfx->m_cTileSize; // max coded index is incorrect
    }
    iMaxStart = min(iMaxStart, iMaxLimit);

    // add extra size for recursive generation
    if (MvRangePrevBand == eMvRangeType &&
        WMAB_TRUE       == pfx->m_bRecursiveCwGeneration)
    {
        cUnusedSize = (2 * pfx->m_iKHzRecursiveCwWidth * 1000 * pfx->m_cTileSize / pau->m_iSamplingRate);
        iMaxStart += (cBandSize - cUnusedSize);
    }
    // apply rule #1
    iMaxStart = min(iMaxStart, pfx->m_cTileSize);

    if (bGetMax)
    {
        pfx->m_iMinStartPos = 0;
        pfx->m_iMaxStartPos = max(iMaxStart-cBandSize, FEX_NUMNOISETRY-1);
        return;
    }

    // get range of mv's
    if (bUseNoise)
    {
        iMaxStart = FEX_NUMNOISETRY-1;
        iMvRange = FEX_NUMNOISETRY-1;
    }
    else
    {
        iMaxStart = iMaxStart - cBandSize;
        switch (pcis->m_iFxMvResType)
        {
        case 0:
            iMvRange = iMaxStart;
            break;
        case 1:
            iMvRange = iMaxStart/2;
            break;
        case 2:
            iMvRange = 2*pfx->m_cMvBins-1; // hi mv resolution modes
            break;
        case 3:
            iMvRange = 4*pfx->m_cMvBins-1;
            break;
        default:
            assert(WMAB_FALSE);
            iMvRange = iMaxStart+1;
        }
        iMvRange = max(iMvRange, pfx->m_cMvBins); // at least mv bins
        iMvRange = min(iMvRange, iMaxStart); // at mose max start
    }
    assert(iMvRange <= iMaxStart);

    // for finding mv pred
    pfx->m_iMinStartPos = 0;
    pfx->m_iMaxStartPos = iMaxStart;

    bUseMvPred = freqexUseMvPred(pfx, iCb);

    if (bUseMvPred)
    {
        iPredMv = freqexGetMvPred(pfx, iCb);
        // +/- around prediction
        pfx->m_iMinStartPos = iPredMv - iMvRange/2;
        pfx->m_iMaxStartPos = iPredMv + (iMvRange+1)/2;
    }
    else
    {
        pfx->m_iMaxStartPos = iMaxStart;
        pfx->m_iMinStartPos = iMaxStart - iMvRange;
    }

    // make sure we have correct # of points
    assert(pfx->m_iMaxStartPos-pfx->m_iMinStartPos+1 == iMvRange+1 ||
           iMvRange < 0);

    // put into proper range
    if (pfx->m_iMinStartPos < 0)
    {
        pfx->m_iMinStartPos = 0;
        pfx->m_iMaxStartPos = iMvRange;
    }
    else if (pfx->m_iMaxStartPos > iMaxStart)
    {
        pfx->m_iMinStartPos = iMaxStart - iMvRange;
        pfx->m_iMaxStartPos = iMaxStart;
    }
}

// =====================================================================

Void prvSetChannelDependencyMask(CAudioObject *pau,
                                 CChannelGroupInfo *rgcgi,
                                 Int cChannelGroup,
                                 Int iChSrc)
{
    Int iChGrp, iCh;
    Bool *rgfChannelMask;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + iChSrc;
    CChannelGroupInfo *pcgi;

    for (iChGrp=0; iChGrp < cChannelGroup; iChGrp++)
    {
        pcgi = rgcgi + iChGrp;
        rgfChannelMask = pcgi->m_rgfChannelMask;

        // channel iChSrc present in this group
        if (WMAB_TRUE==rgfChannelMask[iChSrc])
        {
            // channel group is not identity
            if (pcgi->m_cChannelsInGrp != 1 &&
                (pcgi->m_fIsPredefinedXform != WMAB_TRUE ||
                 pcgi->m_predefinedXformType != MULTICH_IDENTITY))
            {
                for (iCh=0; iCh < pau->m_cChannel; iCh++)
                {
                    if (WMAB_TRUE==rgfChannelMask[iCh])
                        pcis->m_uFxChannelDependencyMask |= (1<<iCh);
                }
                    // channel present in group & group not identity
                pcis->m_uFxChannelGroupMask |= (1<<iChGrp);
            }
            else
            {
                pcis->m_uFxChannelDependencyMask |= (1<<iChSrc);
            }
        }
    }
}

Void freqexSetChannelDependencies(CAudioObject *pau,
                                  CChannelGroupInfo *rgcgi,
                                  Int cChannelGroup,
                                  Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    Int iCh;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + iChSrc;
    FN_CNT;

    //fprintf(stdout, "CC=%d\n", count);
    //fflush(stdout);
    //if (count == 17965)
    //    printf("");

    pcis->m_uFxChannelDependencyMask = 0;
    pcis->m_uFxChannelGroupMask = 0;

    if (pfx->m_iIteration == 0)
    {
        // dependent on all channels in tile
        for (iCh=0; iCh < pau->m_cChInTile; iCh++)
        {
            pcis->m_uFxChannelDependencyMask |= (1<<(pau->m_rgiChInTile[iCh]));
        }
    }
    else
    {
        prvSetChannelDependencyMask(pau, rgcgi, cChannelGroup, iChSrc);
    }
}

Void freqexSetChannelDependencyGroupV2(CAudioObject *pau,
                                       CChannelGroupInfo *rgcgi,
                                       Int cChannelGroup)
{
    Int iChGrp, iCh, iCh2, iGrp, iGrp2, iNGrps, iFirstChInGroup;
    CChannelGroupInfo *pcgi;
    Bool *rgfChannelMask;
    PerChannelInfoShr *pcis, *pcis2;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
        pau->m_rgpcinfoShr[iCh].m_iFxChannelDependencyGroup = -1;

    iNGrps = 0;
    for (iChGrp=0; iChGrp < cChannelGroup; iChGrp++)
    {
        pcgi = rgcgi + iChGrp;
        rgfChannelMask = pcgi->m_rgfChannelMask;

        iGrp = pau->m_cChannel;
        iFirstChInGroup = -1;
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pcis = pau->m_rgpcinfoShr + iCh;
            if (WMAB_TRUE==rgfChannelMask[iCh])
            {
                if (pcis->m_iFxChannelDependencyGroup != -1 &&
                    pcis->m_iFxChannelDependencyGroup < iGrp)
                    iGrp = pcis->m_iFxChannelDependencyGroup;
                if (-1 == iFirstChInGroup)
                    iFirstChInGroup = iCh;
            }
        }

        // create new group if nothing found
        if (iGrp == pau->m_cChannel)
        {
            iGrp = iFirstChInGroup;
            iNGrps++;
        }

        // merge groups
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pcis = pau->m_rgpcinfoShr + iCh;
            if (WMAB_TRUE==rgfChannelMask[iCh])
            {
                if (pcis->m_iFxChannelDependencyGroup == -1)
                    pcis->m_iFxChannelDependencyGroup = iGrp;
                else
                {
                    iGrp2 = pcis->m_iFxChannelDependencyGroup;
                    for (iCh2=0; iCh2 < pau->m_cChannel; iCh2++)
                    {
                        pcis2 = pau->m_rgpcinfoShr + iCh2;
                        if (pcis2->m_iFxChannelDependencyGroup == iGrp2)
                            pcis2->m_iFxChannelDependencyGroup = iGrp;
                    }
                }
            }
        }
    }

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        prvSetChannelDependencyMask(pau, rgcgi, cChannelGroup,
                                    pau->m_rgiChInTile[iCh]);
    }

    pau->m_cChannelDependencyGroups = iNGrps;
}

Void freqexSetChannelDependencyGroupV1(CAudioObject *pau,
                                       CChannelGroupInfo *rgcgi,
                                       Int cChannelGroup)
{
    Int iChGrp, iCh, iCh2, iGrp, iGrp2, iNGrps;
    CChannelGroupInfo *pcgi;
    Bool *rgfChannelMask;
    PerChannelInfoShr *pcis, *pcis2;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        pau->m_rgpcinfoShr[iCh].m_iFxChannelDependencyGroup = -1;
    }

    iNGrps = 0;
    for (iChGrp=0; iChGrp < cChannelGroup; iChGrp++)
    {
        pcgi = rgcgi + iChGrp;
        rgfChannelMask = pcgi->m_rgfChannelMask;

        // skip identity transforms
        if (pcgi->m_cChannelsInGrp==1 ||
            (pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
             pcgi->m_predefinedXformType == MULTICH_IDENTITY))
            continue;

        iGrp = pau->m_cChannel;
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pcis = pau->m_rgpcinfoShr + iCh;
            if (WMAB_TRUE==rgfChannelMask[iCh])
            {
                if (pcis->m_iFxChannelDependencyGroup != -1 &&
                    pcis->m_iFxChannelDependencyGroup < iGrp)
                    iGrp = pcis->m_iFxChannelDependencyGroup;
            }
        }

        // create new group if nothing found
        if (iGrp == pau->m_cChannel)
            iGrp = iNGrps++;

        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pcis = pau->m_rgpcinfoShr + iCh;
            if (WMAB_TRUE==rgfChannelMask[iCh])
            {
                if (pcis->m_iFxChannelDependencyGroup == -1)
                    pcis->m_iFxChannelDependencyGroup = iGrp;
                else
                {
                    iGrp2 = pcis->m_iFxChannelDependencyGroup;
                    for (iCh2=0; iCh2 < pau->m_cChannel; iCh2++)
                    {
                        pcis2 = pau->m_rgpcinfoShr + iCh2;
                        if (pcis2->m_iFxChannelDependencyGroup == iGrp2)
                            pcis2->m_iFxChannelDependencyGroup = iGrp;
                    }
                }
            }
        }
    }

    pau->m_cChannelDependencyGroups = iNGrps;
    assert(iNGrps <= pau->m_cChannel/2);
}

Void freqexSetChannelDependencyGroup(CAudioObject *pau,
                                     CChannelGroupInfo *rgcgi,
                                     Int cChannelGroup)
{
    pau->m_cChannelGroups = cChannelGroup;

    if (pau->m_bPlusV1)
        freqexSetChannelDependencyGroupV1(pau, rgcgi, cChannelGroup);
    else if (pau->m_bPlusV2)
        freqexSetChannelDependencyGroupV2(pau, rgcgi, cChannelGroup);
}

// =======================================================================
// Overlay and hole detection

Bool freqexIsBarkInd(CAudioObject *pau,
                     const Int iStartBark, const Int iEndBark);

Bool prvIsBarkInd(CAudioObject *pau,
                  const Int iChSrc, const Int iBark);

// this uses an unprocessed mask
Void freqexInitHoleOverlay(CAudioObject *pau, CoefType *pfRecon)
{
    Fex *pfx = &pau->m_fex;

    pfx->m_bHoleBand = pfx->m_bEntireHoleOverlay && (pfRecon != NULL);
    pfx->m_iCurrHoleSearchPos = pfx->m_cStartHoleFill;
}

Void freqexGetNextHole(CAudioObject *pau)
{
    Fex *pfx = &pau->m_fex;
    U8 *pucMask = pau->m_pucNonzeroMask;
    Int iCurPos = pfx->m_iCurrHoleSearchPos;
    Int i, iCurrRunStart=0, iCount=0;
    Int iMinRun = pfx->m_cMinRunOfZerosForOverlay;

    assert(0 != (pfx->m_uChGroupProcessed & (1<<pau->m_iChGroup)));

    pfx->m_iHoleBandStart = -1;
    for (i=iCurPos; i < pfx->m_cEndHoleFill; i++)
    {
        if (freqexGetNonzeroMask(pau, i) != 0)
        {
            if (0 == iCount)
                iCurrRunStart = i;
            iCount++;
        }
        else
        {
            if (iCount >= iMinRun)
                break;
            else
                iCount = 0;
        }
    }
    pfx->m_iCurrHoleSearchPos = i+1; // i not incremented prior to break

    if (iCount >= iMinRun)
    {
        pfx->m_iHoleBandStart = iCurrRunStart;
        pfx->m_iHoleBandSize = iCount;
    }
    else
    {
        pfx->m_bHoleBand = WMAB_FALSE;
    }
}

Void freqexProcessValidMaskHelper(CAudioObject *pau, U8 *pucMask,
                                  Int iStartCoeff, Int iSize, Int iMinRun)
{
    Int iStart = max(0, iStartCoeff-iMinRun+1);
    Int iCount = 0;
    Int i, j, iCurrRunStart;
    Fex *pfx = &pau->m_fex;
    U8 *pMaskTmp = pau->m_pucNonzeroMask;

    pau->m_pucNonzeroMask = pucMask;

    if (iMinRun == 0)
    {
        for (i=iStartCoeff; i < iSize; i++)
        {
            if (freqexGetNonzeroMask(pau, i) == 0)
                freqexSetNonzeroMask(pau, i);
            else
                freqexUnsetNonzeroMask(pau, i);
        }
    }
    else
    {
        iCurrRunStart = iStart;
        for (i=iStart; i < iSize; i++)
        {
            if (freqexGetNonzeroMask(pau, i) == 0)
            {
                if (0 == iCount)
                    iCurrRunStart = i;
                iCount++;
            }
            else
            {
                freqexUnsetNonzeroMask(pau, i);
                iCount = 0;
            }

            if (iCount == iMinRun)
            {
                for (j=iCurrRunStart; j < i; j++)
                    freqexSetNonzeroMask(pau, j);
            }

            if (iCount >= iMinRun)
                freqexSetNonzeroMask(pau, i);
        }
    }
    pau->m_pucNonzeroMask = pMaskTmp;
}

Void freqexProcessValidMaskSplit(CAudioObject *pau,
                                 U8 *pucMaskDst, U8 *pucMaskSrc,
                                 Int iStartCoeff, Int iSize, Int iMinRun)
{
    Fex *pfx = &pau->m_fex;
    Int i;
    U8 *p0, *p1, uVal, uIn;

    assert((iSize & 0xf) == 0);

    p0 = pucMaskDst;
    p1 = pucMaskSrc;
    for (i=0; i < iSize/16; i++)
    {
        uVal = 0;
        uIn = p1[0];
        uVal |= (((uIn>>0) & 0x01) | ((uIn>>1) & 0x01)) << 0;
        uVal |= (((uIn>>2) & 0x01) | ((uIn>>3) & 0x01)) << 1;
        uVal |= (((uIn>>4) & 0x01) | ((uIn>>5) & 0x01)) << 2;
        uVal |= (((uIn>>6) & 0x01) | ((uIn>>7) & 0x01)) << 3;
        uIn = p1[1];
        uVal |= (((uIn>>0) & 0x01) | ((uIn>>1) & 0x01)) << 4;
        uVal |= (((uIn>>2) & 0x01) | ((uIn>>3) & 0x01)) << 5;
        uVal |= (((uIn>>4) & 0x01) | ((uIn>>5) & 0x01)) << 6;
        uVal |= (((uIn>>6) & 0x01) | ((uIn>>7) & 0x01)) << 7;
        *p0 = uVal;
        p0 += 1;
        p1 += 2;
    }

    freqexProcessValidMaskHelper(pau, pucMaskDst, iStartCoeff/2, iSize/2,
                                 iMinRun);
}

// calculate the mask from the base band Coefs
Void freqexCalculateNonzeroMaskFromCoef(CAudioObject *pau)
{
    Int iCh, iGroup = pau->m_iChGroup;
    Fex *pfx = &pau->m_fex;

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        I16 iChSrc = pau->m_rgiChInTile[iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;

        freqexSetGroup(pau, iChSrc, pfx->m_bChannelIndependent, pfx->m_bSplitTileIntoSubtiles);
        freqexSetNonzeroMaskFromCoef(pau, ppcinfo->m_rgCoefRecon, ppcinfo->m_cSubFrameSampleHalf, WMAB_TRUE);
    }

    // need to restore the original group here as the above loop may have changed it.
    freqexSetGroupGrp(pau, iGroup, pfx->m_bSplitTileIntoSubtiles);
}

Void freqexProcessValidMask(CAudioObject *pau, Int iGrp)
{
    Fex *pfx = &pau->m_fex;
    U8 *pucMask, *pucMaskDst;
    
    if (WMAB_FALSE == pfx->m_bOverlayUsedForBand)
        return;

    if (pfx->m_uChGroupProcessed & (1<<iGrp))
    {
        // do nothing when MinRun match the recorded MinRun for the current processed mask
        if (pfx->m_cMinRunOfZerosForOverlayProcessed == pfx->m_cMinRunOfZerosForOverlay)
            return;
               
        assert(pfx->m_cMinRunOfZerosForOverlayProcessed != -1 && pau->m_bEncoder);
        
        // need to reset the processed flag to clear all groups and reset channel transform
        pfx->m_uChGroupProcessed = 0;
        pau->m_bXChannelProc = WMAB_FALSE;
    }

    if (pfx->m_iVersion >= 2)
        freqexProcessZeroMaskXChannel(pau);

    pucMask = pau->m_ucNonzeroCoeffMask + iGrp*pau->m_cFrameSampleHalf/8;

    if (pfx->m_bSplitTileIntoSubtiles)
    {
        assert(1 == pfx->m_iVersion);

        pucMaskDst =
            pau->m_ucNonzeroCoeffMask +
            pau->m_iNonzeroMaskCh*pau->m_cFrameSampleHalf/8 +
            iGrp*pau->m_cFrameSampleHalf/16;
        freqexProcessValidMaskSplit(pau, pucMaskDst, pucMask,
                                    0, pfx->m_cSubFrameSampleHalf,
                                    pfx->m_cMinRunOfZerosForOverlay);
    }

    freqexProcessValidMaskHelper(pau, pucMask, 0,
                                 pfx->m_cSubFrameSampleHalf,
                                 pfx->m_bSplitTileIntoSubtiles ? 
                                 2*pfx->m_cMinRunOfZerosForOverlay :
                                 pfx->m_cMinRunOfZerosForOverlay);

    pfx->m_uChGroupProcessed |= (1<<iGrp);
    pfx->m_cMinRunOfZerosForOverlayProcessed = pfx->m_cMinRunOfZerosForOverlay;
}

// ========================================================================

Void freqexZeroNonzeroMask(CAudioObject *pau)
{
    if (pau->m_bPlusV1)
        memset(pau->m_ucNonzeroCoeffMask,
             0, pau->m_iNonzeroMaskCh*pau->m_cFrameSampleHalf*3/16*sizeof(U8));
    else if (pau->m_bPlusV2)
        memset(pau->m_ucNonzeroCoeffMask,
             0, pau->m_iNonzeroMaskCh*pau->m_cFrameSampleHalf/8*sizeof(U8));
    pau->m_fex.m_uChGroupProcessed = 0;
    pau->m_fex.m_cMinRunOfZerosForOverlayProcessed = -1;
    pau->m_bXChannelProc = WMAB_FALSE;
}

Void freqexSetNonzeroMaskFromCoef(CAudioObject *pau,
                                  CoefType *pf, Int iLen,
                                  Bool bForceCalc)
{
    Int i;
    Fex *pfx = &(pau->m_fex);

    if (pfx->m_bReconDomain)
        return;

    if (WMAB_FALSE == pfx->m_bMinRunOfZerosForOverlayCoded &&
        WMAB_FALSE == bForceCalc)
        return;

    memset(pau->m_pucNonzeroMask, 0, pau->m_cFrameSampleHalf/8);

    for (i=0; i < iLen; i++)
    {
        if (pf[i] != 0)
            freqexSetNonzeroMask(pau, (Int)i);
    }
}

// ========================================================================

Void freqexSetEnd(CAudioObject *pau, Int cSubFrameSampleHalf)
{
    Fex *pfx = &(pau->m_fex);
    pfx->m_cEnd =
        (cSubFrameSampleHalf*pfx->m_iMaxFreq)/(pau->m_iSamplingRate/2);
    pfx->m_cEnd = min(pfx->m_cEnd, cSubFrameSampleHalf);
}

Void freqexSetBaseEnd(CAudioObject *pau, Int cSubFrameSampleHalf, Bool bBaseScaleOnly)
{
    Fex *pfx = &(pau->m_fex);
    pfx->m_cBaseEnd =
        (cSubFrameSampleHalf*pfx->m_iMaxBaseFreq)/(pau->m_iSamplingRate/2);
    if (!bBaseScaleOnly)
        pfx->m_cBaseEnd = min(pfx->m_cStart, pfx->m_cBaseEnd);
}

Void freqexGetExpectedMultipliers(const Int  *piFexBandSizesM,
                                  const Int  iMinRatioBandSizeM,
                                  const Bool bUseUniformBands,
                                  UInt *puiExpBandSizeMIndex,
                                  Int  *piExpBandSizeM,
                                  Int  *rgiBandBreakPts)
{
    Int i, j, k;

    for (i=0, j=0, k=0; i <= g_iFexNumBandSize; i++)
    {
        for (; j < g_rgiFexNBandsAtSize[i]; j++)
        {
            if (bUseUniformBands)
                rgiBandBreakPts[k] = iMinRatioBandSizeM;
            else
                rgiBandBreakPts[k] =
                    iMinRatioBandSizeM * piFexBandSizesM[i-1];
            k++;
        }
    }
    *puiExpBandSizeMIndex = 0;
    *piExpBandSizeM = rgiBandBreakPts[0];
}

Void freqexUpdateExpectedBandSizeM( const Int  *rgiBandBreakPts,
                                    const Int   iActBandSizeM,
                                    const UInt  cMaxBands,
                                          UInt *puiExpBandSizeMIndex,
                                           Int *piExpBandSizeM )
{
    *piExpBandSizeM -= iActBandSizeM;
    while (*piExpBandSizeM <= 0)
    {
        (*puiExpBandSizeMIndex)++;
        if (*puiExpBandSizeMIndex < cMaxBands)
            *piExpBandSizeM += rgiBandBreakPts[*puiExpBandSizeMIndex];
        else
            *piExpBandSizeM += rgiBandBreakPts[cMaxBands-1];
    }
}

Int freqexFindStartPosForOverlay(CAudioObject *pau,
                                 Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    Int i, iPos;
    Bool bChannelIndependent = pfx->m_bChannelIndependent;
    Bool bSplit = pfx->m_bSplitTileIntoSubtiles;
    Int cTileSize = pfx->m_cTileSize;
    Int cMinRunOfZerosForOverlay = pfx->m_cMinRunOfZerosForOverlay;
    Bool bOverlayUsedForBand = pfx->m_bOverlayUsedForBand;
    PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChSrc;
    PerChannelInfoShr *pcis = ppcinfo->m_ppcinfoShr;
    CoefType *pfRecon = ppcinfo->m_rgCoefRecon;

    pfx->m_bChannelIndependent =
      (pcis->m_iFxChannelDependencyGroup==-1 ? WMAB_TRUE : WMAB_FALSE);

    pfx->m_cStartIndex = 0;
    pfx->m_bOverlayUsedForBand = WMAB_TRUE;

    if (pfx->m_iVersion >= 2)
        freqexProcessZeroMaskXChannel(pau);

    freqexSetGroup(pau, iChSrc, pfx->m_bChannelIndependent, WMAB_FALSE);
    freqexProcessValidMask(pau, pau->m_iChGroup);

    for (i=0; i < ppcinfo->m_cSubFrameSampleHalf; i++)
    {
        if (IS_VALID_FEXPT())
        {
            break;
        }
    }

    pfx->m_bChannelIndependent = bChannelIndependent;
    pfx->m_bSplitTileIntoSubtiles = bSplit;
    pfx->m_cTileSize = cTileSize;
    pfx->m_cMinRunOfZerosForOverlay = cMinRunOfZerosForOverlay;
    pfx->m_bOverlayUsedForBand = bOverlayUsedForBand;

    // apply rules in descending order of precedence
    // 1. start pos >= first hole
    // 2. start pos <= max coded index * 0.5
    // 3. start pos >= 4000 hz (THRESH)

#if defined(FEX_DBG_PRINT)
    fxprintf(("VALID PT FOR OVERLAY = %d LAST CODED IDX = %d\n", i,
              pfx->m_iMaxLastCodedIndexOrig));
#endif

#define THRESH (4000)
    // don't go below 4kHz threshold, otherwise get noisy
    iPos = (ppcinfo->m_cSubFrameSampleHalf*THRESH)/(pau->m_iSamplingRate/2);
    // don't go above 50% of max coded index
    // i.e. if base codec codes > 8 kHz, start filling holes at 4kHz
    //      if base codec codes < 8 kHz, start filling at 0.5*bandwidth
    //      so if base codec codes upto 4kHz, fill holes from 2kHz
    iPos = min(iPos, pfx->m_iMaxLastCodedIndexOrig/2);
    // don't go below first hole
    iPos = max(iPos, i);

    return iPos;
}

Void freqexSetStartPosChannel(CAudioObject *pau, Int iChCode, Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + iChSrc;

    if (WMAB_TRUE==pfx->m_bUseSingleMv && 0!=iChCode)
    {
        // all channels must have same start position
        return;
    }

    pfx->m_cStartHoleFill = 0;
    pfx->m_cEndHoleFill = 0;
    pfx->m_bEntireHoleOverlay = WMAB_FALSE;

    // following only used by encoder
    if (pfx->m_iIteration < 2)
    {
        pfx->m_cStart = pfx->m_iExplicitStartPos;
    }
    else
    {
        if (pcis->m_bFxUseImplicitStartPos)
        {
            if (pfx->m_bMvRangeFull)
            {
                pfx->m_cStart = 0;
            }
            else if (pfx->m_iVersion <= 2 || pfx->m_bV1Compatible)
            {
                freqexSetLastCodedIndex(pau, iChSrc);
                pfx->m_cStart = pfx->m_iMaxLastCodedIndexOrig;
                if (pfx->m_bOverlay)
                    pfx->m_cStart = freqexFindStartPosForOverlay(pau, iChSrc);
            }
            else
            {
                assert(pfx->m_iVersion > 2);
                freqexSetLastCodedIndex(pau, iChSrc);
                freqexSetEnd(pau, pfx->m_cSubFrameSampleHalf);
                pfx->m_cStart = min(pfx->m_iMaxLastCodedIndexOrig,
                                    pfx->m_cEnd);
                if (pfx->m_bOverlay)
                {
                    pfx->m_cStartHoleFill = 0;
                    pfx->m_cEndHoleFill = pfx->m_cStart;
                    pfx->m_bEntireHoleOverlay = WMAB_TRUE;
                }
            }
        }
        else
        {
            pfx->m_cStart = pfx->m_iExplicitStartPos;
            if( pfx->m_iVersion > 2 && !pfx->m_bV1Compatible)
            {
                freqexSetLastCodedIndex(pau, iChSrc);
                freqexSetEnd(pau, pfx->m_cSubFrameSampleHalf);
                if( pfx->m_iExplicitStartPos < pfx->m_iMaxLastCodedIndexOrig )
                {
                    pfx->m_cStart = min(pfx->m_iMaxLastCodedIndexOrig,
                                        pfx->m_cEnd);
                    pfx->m_cStartHoleFill = pfx->m_iExplicitStartPos;
                    pfx->m_cEndHoleFill = pfx->m_cStart;
                    pfx->m_bEntireHoleOverlay = WMAB_TRUE;
                }
                else
                {
                    pfx->m_cStart = min(pfx->m_iExplicitStartPos,
                                        pfx->m_cEnd);
                }
            }
        }
    }
#if 0
    printf("%d %d\n", pfx->m_cStart, pfx->m_iMaxLastCodedIndex);
#endif

    pfx->m_cOrigStart = pfx->m_cStart;
    if (pfx->m_bSplitTileIntoSubtiles)
        pfx->m_cStart /= 2;
}

Void freqexSetScaleBandsPerMvBand( Fex *pfx,
                                   Int cScaleBands,
                                   Int cMvBands,
                                   Int *pcScaleBandsPerMvBand )
{
    Int   i = 0;

    while( cMvBands > 0 )
    {
        if (i < pfx->m_cHoleBands)
            pcScaleBandsPerMvBand[i] = 1;
        else
            pcScaleBandsPerMvBand[i] = cScaleBands / cMvBands;

        cScaleBands -= pcScaleBandsPerMvBand[i];
        cMvBands--;
        i++;
    }
}

#ifdef BUILD_WMAPROLBRV2
Void freqexSetBandConfigForMergedMv( CAudioObject *pau,
                                     Int cScaleBands,
                                     Int cMvBands )
{
    Fex   *pfx = &(pau->m_fex);
    Int i;

    assert( cScaleBands >= cMvBands );

    // get scale band config
    pfx->m_cScaleBands = 
        freqexSetBandConfig( pau, cScaleBands, WMAB_FALSE, WMAB_FALSE );
    pfx->m_cMvBands =
        freqexSetBandConfig( pau, cMvBands, WMAB_FALSE, WMAB_TRUE );

    // set # of scale bands per mv band
    freqexSetScaleBandsPerMvBand( pfx, pfx->m_cScaleBands, pfx->m_cMvBands, pfx->m_rgcScaleBandsPerMvBand );

    // compute size for each mv band
    for( cMvBands = cScaleBands = 0; cMvBands < pfx->m_cMvBands; cMvBands++ )
    {
        pfx->m_piMvBandSizes[cMvBands] = 0;
        for( i = 0; i < pfx->m_rgcScaleBandsPerMvBand[cMvBands]; i++ )
            pfx->m_piMvBandSizes[cMvBands] += pfx->m_piScaleBandSizes[cScaleBands++];
    }
}

//#define DEBUG_QUANT_SCALES
#ifdef DEBUG_QUANT_SCALES
static FILE *g_quantScaleLog[2] = {0};
#endif

Int freqexQuantScaleV2( const Fex *pfx, const Int iStepSize, FastFloat fScale )
{
    Int           iScaleIndex;

#ifndef BUILD_INTEGER

    fScale *= pfx->m_fBitScale;

    if( fScale > 0.0f )
        fScale = (Float)(20.0f * log10( fScale )); // in log domain
    else
        fScale = 0.0f;

    iScaleIndex = ROUNDF( fScale / iStepSize );
    iScaleIndex = __max( iScaleIndex, 0 );

#else 

    assert( pfx->m_iBitScale >= 0 );
    fScale.iFracBits += pfx->m_iBitScale;

    // !! need to integerize this part.

    catchFP();

    if( 0 < fScale.iFraction )
        fScale = FASTFLOAT_FROM_FLOAT( (Float)(20.0f * 
          log10( FLOAT_FROM_FASTFLOAT( fScale ) ) ));
    else
        fScale.iFraction = 0;

    iScaleIndex = ROUNDF( FLOAT_FROM_FASTFLOAT( fScale ) / iStepSize );
    iScaleIndex = iScaleIndex > 0 ? iScaleIndex : 0;
   // iScaleIndex = __max( iScaleIndex, 0 );

    initFP();

#endif

#ifdef DEBUG_QUANT_SCALES
#ifdef BUILD_INTEGER
    {
        int count = 0;
        int iScaleIndexFlt = 0;
        if( NULL == g_quantScaleLog[0] )
        {
            g_quantScaleLog[0] = fopen( "d:\\inttest\\qscale.flt", "r" );
            g_quantScaleLog[1] = fopen( "d:\\inttest\\qscale.int", "w" );
        }
        count = fscanf ( g_quantScaleLog[0], "%i\n", &iScaleIndexFlt );
        fprintf( g_quantScaleLog[1], "%i\n",  iScaleIndex );
        fflush ( g_quantScaleLog[1] );
        //assert( iScaleIndexFlt == iScaleIndex );
        if( 1 == count ) iScaleIndex = iScaleIndexFlt;
    }
#else
    {
        if( NULL == g_quantScaleLog[0] ) 
            g_quantScaleLog[0] = fopen( "d:\\inttest\\qscale.flt", "w" );
        fprintf( g_quantScaleLog[0], "%i\n", iScaleIndex );
        fflush ( g_quantScaleLog[0] );
    }
#endif
#endif // DEBUG_QUANT_SCALES

    return iScaleIndex;
}

FastFloat freqexInvQuantScaleV2( const Fex *pfx, const Int iStepSize, const FastFloat fIndex )
{
#ifndef BUILD_INTEGER

    Float fScale;

    fScale = ( fIndex * iStepSize ) * 0.05f;
    fScale = (Float)pow( 10.0f, fScale ) / pfx->m_fBitScale;
    return fScale;

#else

    // the integer computation uses qstCalcQuantStep() to look up the
    // value of pow( 10, fIndex * iStepSize * 0.05f ). But the lookup
    // only takes integer arguments, so this function interpolates
    // between two adjacent entries.

#   define BITS 4
#   define MASK ((1<<BITS)-1)

    Int iFraction = fIndex.iFraction;
    Int iFracBits = fIndex.iFracBits;

    if( (1<<24) < abs(iFraction) ) 
    {
        iFraction >>= 8;
        iFracBits  -= 8;
    }

    assert( (1<<30) > ((I64)abs(iFraction)*iStepSize) );

    iFraction *= iStepSize;

    // this interpolation will use 'BITS' of precision,
    // so shift 'iFraction' to that fixed position.

    if( BITS > iFracBits ) iFraction <<= BITS-iFracBits;
    if( BITS < iFracBits ) iFraction >>= iFracBits-BITS;

    if( 0 == ( MASK & iFraction ) )
    {
        // if 'iFraction' has no fractional component,
        // just return the lookup from qstCalcQuantStep().

        return qstCalcQuantStep( iFraction >> BITS, -pfx->m_iBitScale );
    }
    else
    {
        // in this case, there is a fractional part,
        // so interpolate between 2 table entries.

        const Int iQSS0 = iFraction >> BITS;                // 1st LUT index
        const Int iQSS1 = iQSS0 + ((0<iFraction)?1:-1);     // 2nd LUT index
        const Int iFrac = MASK  & ((0<iFraction)?           // fractional component
                        iFraction : (-iFraction));

        FastFloat ffScale0   = qstCalcQuantStep( iQSS0,0 ); // 1st table entry
        FastFloat ffScale1   = qstCalcQuantStep( iQSS1,0 ); // 2nd table entry

        ffScale0.iFraction >>= BITS;                        // make room for weighting
        ffScale1.iFraction >>= BITS;                        // each of the fast-floats.

        ffScale0.iFraction  *= (1<<BITS)-iFrac;             // scale by 1-frac,
        ffScale1.iFraction  *=           iFrac;             // scale by   frac

        ffScale0 = FASTFLOAT_ADD( ffScale0, ffScale1 );     // add the 2 components
        ffScale0.iFracBits -= pfx->m_iBitScale;             // & shift by bit-scale.

        return ffScale0;
    }

#   undef BITS
#   undef MASK
#endif
}

WMARESULT freqexSetLocalParamsFromGlobalParam( CAudioObject *pau,
                                               FexGlobalParam *pfxgp )
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(pau->m_fex);
    Int iCh, iChSrc;
    PerChannelInfo *ppcinfo;
    PerChannelInfoShr *pcis;

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;
        pcis = ppcinfo->m_ppcinfoShr;

        if (!ppcinfo->m_bFex)
            continue;

        if (pau->m_bCx && iCh != 0 && ppcinfo->m_bFex)
        {
            // Only the 1st channel should have Fex enabled
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        pcis->m_bFxArbitraryBandConfig = pfxgp->m_bArbitraryScaleBandConfig;
        pcis->m_bFxUseUniformBands = pfxgp->m_bUseUniformScaleBands;
        if( pfxgp->m_bArbitraryScaleBandConfig )
            memcpy( pfx->m_rgiBandSizeM + pcis->m_iFxBandConfig * pfx->m_cMaxBands, 
                    pfxgp->m_piBandSizeM, pfxgp->m_cScaleBands * sizeof(Int) );
    }

    pfx->m_piFexBandSizesM = freqexSetBandSizeM( pfxgp->m_bScaleBandSplitV2 );
    pfx->m_piBaseBandSizesM = freqexSetBandSizeM( pfxgp->m_bBaseBandSplitV2 );

    pfx->m_cMvDefaultBins = freqexIndexToMvBins( pfxgp->m_iMvBinsIndex );
    pfx->m_iMvBinsMultiplier = 1;
    pfx->m_iPrevMvBinsMultiplier = 0;
    freqexSetMvBins( pfx );

    pfx->m_bRecursiveCwGeneration = pfxgp->m_bRecursiveCwGeneration;
    pfx->m_iKHzRecursiveCwWidth = pfxgp->m_iKHzRecursiveCwWidth;
    pfx->m_iMaxFreq = pfxgp->m_iMaxFreq;
    pfx->m_iMaxBaseFreq = pfxgp->m_iMaxBaseFreq;
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;
        pcis = ppcinfo->m_ppcinfoShr;

        if (!ppcinfo->m_bFex)
            continue;

        pcis->m_eFxMvRangeType = pfxgp->m_iMvRangeType;
        pcis->m_iFxMvResType = pfxgp->m_iMvResType;
        pcis->m_bFxUseImplicitStartPos = pfxgp->m_bUseImplicitStartPos;
        pcis->m_iFxNoiseFloorThresh = pfxgp->m_iNoiseFloorThresh;
        pcis->m_bFxUseRandomMv2 = pfxgp->m_bUseRandomNoise;
    }
    freqexSetMvType(pfx);

    pfx->m_bOverlay = pfxgp->m_bOverlay;
    pfx->m_cMinRunOfZerosForOverlayIndex = 0;
    pfx->m_cMinRunOfZerosForOverlay = 0;
    pfx->m_cMaxRunOfZerosPerBandForOverlayIndex = 0;
    pfx->m_cMaxRunOfZerosPerBandForOverlay = 0;
    pfx->m_bMinRunOfZerosForOverlayCoded = WMAB_FALSE;
    pfx->m_iEndHoleFillConditionIndex = 0;
    pfx->m_bEntireHoleOverlay = WMAB_FALSE;
    /*
    Note: In the case where pfxgp->m_bUseImplicitStartPos == WMAB_TRUE, the processed mask
    at the encoder end does not match the processed mask at the decoder end
    But this is OK, since the mask is not used
    */
    if( !pfx->m_bReconDomain && 
        (pfxgp->m_bUseImplicitStartPos == WMAB_FALSE || pfxgp->m_bOverlay == WMAB_TRUE) )
    {
        if( pfx->m_iVersion == 2 )
        {
            pfx->m_cMinRunOfZerosForOverlayIndex = pfxgp->m_cMinRunOfZerosForOverlayIndex;
            pfx->m_cMinRunOfZerosForOverlay =
                freqexIndexToMinRunOfZerosForOverlay(pau, pfx,
                                                    pfx->m_cMinRunOfZerosForOverlayIndex);
        }
#ifdef BUILD_WMAPROLBRV3
        else if( pfx->m_iVersion > 2 )
        {
            pfx->m_cMinRunOfZerosForOverlayIndex = pfxgp->m_cMinRunOfZerosForOverlayIndex;
            pfx->m_cMinRunOfZerosForOverlay =
                freqexIndexToMinRunOfZerosForOverlayV3(pau, pfx,
                                                       pfx->m_cMinRunOfZerosForOverlayIndex);
            pfx->m_cMaxRunOfZerosPerBandForOverlayIndex = pfxgp->m_cMaxRunOfZerosPerBandForOverlayIndex;
            pfx->m_cMaxRunOfZerosPerBandForOverlay =
                freqexIndexToMaxRunOfZerosPerBandForOverlayV3(pau, pfx,
                                                              pfx->m_cMaxRunOfZerosPerBandForOverlayIndex);
            pfx->m_iEndHoleFillConditionIndex = pfxgp->m_iEndHoleFillConditionIndex;
        }
#endif
        pfx->m_bMinRunOfZerosForOverlayCoded = WMAB_TRUE;
    }

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;
        pcis = ppcinfo->m_ppcinfoShr;

        if (!ppcinfo->m_bFex)
            continue;

        // set the end position
        freqexSetEnd( pau, ppcinfo->m_cSubFrameSampleHalf );

        pcis->m_iFxScaleBands = pfxgp->m_cScaleBands;
        pcis->m_iFxMvBands = pfxgp->m_cMvBands;
        pcis->m_bFxUseImplicitStartPos = pfxgp->m_bUseImplicitStartPos;
    }
    pfx->m_cBaseBandsGlobal = pfxgp->m_cBaseBands;

    pfx->m_bBaseScaleOnly = WMAB_FALSE;
    pfx->m_bShrinkBaseBand = WMAB_FALSE;
#ifdef BUILD_WMAPROLBRV3
    if (pfx->m_iVersion > 2 &&
        pfx->m_bReconDomain &&
        pau->m_bTileReconAnyBsOnly &&
        chexInfoStatCodeBs(pfx->m_prtiCurr->m_uInfoStat))
    {
        if (chexInfoStatNoFx(pfx->m_prtiCurr->m_uInfoStat))
            pfx->m_bBaseScaleOnly = WMAB_TRUE;
        else
            pfx->m_bShrinkBaseBand = WMAB_TRUE;
    }
#endif

exit:
    return wmaResult;
}

FastFloat fexPower( const CoefType *pfVec, 
   const Int cSize, const Int cLeftShiftBits )
{

#ifndef BUILD_INTEGER

    Float fScale = 0;
    Int i;

    for( i = 0; i < cSize; ++i )
        fScale += pfVec[i] * (Float)pfVec[i];
    if( cSize != 0 )
        fScale = (Float)sqrt( fScale / cSize );

    return fScale;

#else

    FastFloat fScale;
    I64 accum = 0;
    Int i;



    for( i = 0; i < cSize; ++i )
    {
        const CoefType coef = pfVec[i] >> (cLeftShiftBits/2);
        accum += coef * (I64)coef;
        assert( 0 <= accum );
    }

    if( 0 < accum && 0 < cSize )
    {
        Int rshift = 2*(cLeftShiftBits-(cLeftShiftBits/2));

        while( 0x70000000 > accum )
        {
            accum <<= 1;
            rshift += 1;
        }

        accum /= cSize;

        while( 0x7fffffff < accum )
        {
            accum >>= 2;
            rshift -= 2;
        }

        fScale.iFraction = (I32)accum;
        fScale.iFracBits = rshift;

        fScale = FASTFLOAT_SQRT( fScale );
    }
    else
    {
        fScale.iFraction = 0;
        fScale.iFracBits = 0;
    }

    return fScale;

#endif
}

Int freqexComputeScaleRefV2( Fex      *pfx,
                             const CoefType *pfRecon,
                             const Int cLeftShiftBits )
{
    Int cBandSize;
    FastFloat fBandScale;
    const CoefType *pfVec;
    WMARESULT  wmaResult = WMA_OK;
    FexGlobalParam *pfxgp;

    if( pfx->m_bReconDomain )
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    //assert(0 != pfx->m_piScaleBandSizes[0]); // otherwise infinite loop
    if (0 >= pfx->m_piScaleBandSizes[0])
    {
        NO_ERROR_REPORT_BITSTREAM_CORRUPTION_AND_EXIT;
    }

    cBandSize = 0;
    while( cBandSize < 10 )
        cBandSize += pfx->m_piScaleBandSizes[0];
    cBandSize = min( cBandSize, pfx->m_cStart );
    pfVec = pfRecon + pfx->m_cStart - cBandSize;

    fBandScale = fexPower( pfVec, cBandSize, cLeftShiftBits );
exit:
    return freqexQuantScaleV2( pfx, pfxgp->m_iScFacStepSize, fBandScale );
}

Void freqexSetCommonTilePtrs(CAudioObject *pau, ReconTileInfo *prti)
{
    Fex *pfx = &(pau->m_fex);
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;

    pfx->m_piBaseBandSizes  = prfxrti->m_rgiFexBaseBandSizes;
    pfx->m_piScaleBandSizes = prfxrti->m_rgiFexScaleBandSizes;
    pfx->m_piMvBandSizes    = prfxrti->m_rgiFexMvBandSizes;
}

Void freqexSaveCommonTileParams(CAudioObject *pau, ReconTileInfo *prti)
{
    Fex *pfx = &(pau->m_fex);
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;

    prfxrti->m_cFexScaleBands = pfx->m_cScaleBands;
    prfxrti->m_cFexMvBands    = pfx->m_cMvBands;
    prfxrti->m_cFexBaseBands  = pfx->m_cBaseBands;
    prfxrti->m_cFexStart      = pfx->m_cStart;
}

Void freqexResetCommonTileParams(CAudioObject *pau, ReconTileInfo *prti)
{
    Fex *pfx = &(pau->m_fex);

    pfx->m_piBaseBandSizes  = pfx->m_rgiBaseBandSizes;
    pfx->m_piScaleBandSizes = pfx->m_rgiScaleBandSizes;
    pfx->m_piMvBandSizes    = pfx->m_rgiMvBandSizes;
}

Void freqexRestoreCommonTileParams(CAudioObject *pau, ReconTileInfo *prti)
{
    Fex *pfx = &(pau->m_fex);
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;

    pfx->m_cScaleBands = prfxrti->m_cFexScaleBands;
    pfx->m_cMvBands    = prfxrti->m_cFexMvBands;
    pfx->m_cBaseBands  = prfxrti->m_cFexBaseBands;
    pfx->m_cStart      = prfxrti->m_cFexStart;
}

Void freqexSetPerChTilePtrs(CAudioObject *pau,
                            ReconTileInfo *prti,
                            PerChannelInfo *ppcinfo, 
                            const Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;
    PerChannelRecon *ppcr = prfxrti->m_rgpcr + iChSrc;

    // Base scaling
    ppcinfo->m_pffltFexScaleFacBase      = ppcr->m_rgfFexScaleFacBase;
    ppcinfo->m_piFexLogScaleFacBaseIndex = ppcr->m_rgiFexLogScaleFacBaseIndex;
    
    // Scale factor
    ppcinfo->m_pffltFexScaleFac      = ppcr->m_rgfFexScaleFac;
    ppcinfo->m_pffltFexScaleFacNoise = ppcr->m_rgfFexScaleFacNoise;
    ppcinfo->m_piFexLogScaleFacIndex = ppcr->m_rgiFexLogScaleFacIndex;

    // Mv
    ppcinfo->m_piFexMv    = ppcr->m_rgiFexMv;
    ppcinfo->m_piFexMv2   = ppcr->m_rgiFexMv2;
    ppcinfo->m_piFexCb    = ppcr->m_rgiFexCb;
    ppcinfo->m_pFexExp    = ppcr->m_rgFexExp;
    ppcinfo->m_piFexSign  = ppcr->m_rgiFexSign;
    ppcinfo->m_pbFexRev   = ppcr->m_rgbFexRev;
}

Void freqexSavePerChTileParams(CAudioObject *pau,
                               ReconTileInfo *prti,
                               PerChannelInfo *ppcinfo,
                               const Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;
    PerChannelRecon *ppcr = prfxrti->m_rgpcr + iChSrc;

    ppcr->m_iFexLogScaleFacIndexRef = *ppcinfo->m_piFexLogScaleFacIndexRef;
    ppcr->m_iFexScaleFacPred = *ppcinfo->m_pFexScaleFacPred;
    ppcr->m_iFexScaleFacBasePred = *ppcinfo->m_pFexScaleFacBasePred;
}

Void freqexRestorePerChTileParams(CAudioObject *pau, 
                                  ReconTileInfo *prti,
                                  PerChannelInfo *ppcinfo, 
                                  const Int iChSrc)
{ 
    Fex *pfx = &(pau->m_fex);
    RFxReconTileInfo *prfxrti = prti->m_prfxrti;
    PerChannelRecon *ppcr = prfxrti->m_rgpcr + iChSrc;

    *ppcinfo->m_piFexLogScaleFacIndexRef = ppcr->m_iFexLogScaleFacIndexRef;
    *ppcinfo->m_pFexScaleFacPred = ppcr->m_iFexScaleFacPred;
    *ppcinfo->m_pFexScaleFacBasePred = ppcr->m_iFexScaleFacBasePred;
}

 
#if 0
#ifndef BUILD_INTEGER
#   define DEBUG_LOG_SCALE_FAC( i ) \
            printf( "%i\n",  i );
#else
#   define DEBUG_LOG_SCALE_FAC( i ) \
            printf( "%i\t",  i );   \
            scanf ( "%i\n", &i );   \
            printf( "%i\n",  i );
#endif
#else
#   define DEBUG_LOG_SCALE_FAC( i )
#endif // DEBUG_LOG_SCALE_FAC


WMARESULT freqexReconScaleBandsV2( CAudioObject    *pau,
                                   PerChannelInfo  *ppcinfo,
                                   Int             iChSrc )
{
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    ReconProc       *prp = pau->m_prp;
    PerChannelRecon *ppcr, *ppcrNextIntra;
    ReconTileInfo   *prtiPrev, *prtiNext;
    I32             iBand, iPrev, iNext, cPrev, cNext, iNextIntra;
    Int             iFexCh;
    FastFloat       fIndex;
    Bool            bLastTile;
    WMARESULT       wmaResult = WMA_OK;

    if (pfx->m_cScaleBands == 0)
        goto exit;

    iFexCh = chexGetFexChannel(pau, iChSrc);
    if (iFexCh < 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    
    // simple fix for FUZZ bug
    if (ppcinfo->m_piFexLogScaleFacIndex == 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
    ppcr->m_iFexLogScaleFacIndexRef = *(ppcinfo->m_piFexLogScaleFacIndexRef);

    switch( *(ppcinfo->m_pFexScaleFacPred) )
    {
        case FexScaleFacIntraPred:
            iPrev = ppcr->m_iFexLogScaleFacIndexRef;

            DEBUG_LOG_SCALE_FAC( iPrev );

            // check if reference scale need to be updated
            prtiPrev = chexPrevTile( prp, pfx->m_prtiCurr );
            if( prtiPrev != NULL &&
                prtiPrev->m_prfxrti &&
                chexInfoStatAdd( prtiPrev->m_uInfoStat ) &&
                prtiPrev->m_prfxrti->m_rgpcr[iFexCh].m_iFexScaleFacPred == FexScaleFacIntplPred )
            {
                ppcr = prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                // find the farthest interpolation subframe
                for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
                {
                    iPrev = g_fexScaleIntpl;
                    if( ppcr->m_rgiFexLogScaleFacIndex )
                        iPrev = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    while( chexInfoStatAdd( prtiPrev->m_uInfoStat ) && 
                           (ppcr->m_iFexScaleFacPred == FexScaleFacNo || iPrev == g_fexScaleIntpl) )
                    {
                        prtiPrev = chexPrevTile( prp, prtiPrev );
                        ppcr =  prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                        iPrev = g_fexScaleIntpl;
                        if( ppcr->m_rgiFexLogScaleFacIndex )
                            iPrev = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    }
                }
                // one subframe back,
                // because prtiPrev is one before the farthest interpolation subframe
                prtiPrev = chexNextTile( prp, prtiPrev );
                ppcr = prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                while( ppcr->m_iFexScaleFacPred == FexScaleFacNo )
                {
                    prtiPrev = chexPrevTile( prp, prtiPrev );
                    ppcr =  prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                }
                iPrev = ppcr->m_iFexLogScaleFacIndexRef;

                DEBUG_LOG_SCALE_FAC( iPrev );

                ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
                ppcr->m_iFexLogScaleFacIndexRef = iPrev;
            }
            // intraframe prediction
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                ppcinfo->m_piFexLogScaleFacIndex[iBand] += iPrev;
                ppcinfo->m_pffltFexScaleFac[iBand] = 
                    FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacIndex[iBand] );
                iPrev = ppcinfo->m_piFexLogScaleFacIndex[iBand];
            }
            break;

        case FexScaleFacIntraPredNoRef:
            // intraframe prediction
            iPrev = 0;
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                ppcinfo->m_piFexLogScaleFacIndex[iBand] += iPrev;
                ppcinfo->m_pffltFexScaleFac[iBand] =
                    FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacIndex[iBand] );
                iPrev = ppcinfo->m_piFexLogScaleFacIndex[iBand];
            }
            break;

        case FexScaleFacInterPred:
            // interframe prediction
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                // find previous anchor
                prtiPrev = chexPrevTile( prp, pfx->m_prtiCurr );
                ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
                iPrev = g_fexScaleIntpl;
                while ( (ppcr->m_iFexScaleFacPred == FexScaleFacNo || iPrev == g_fexScaleIntpl) &&
                        prtiPrev != NULL && chexInfoStatAdd( prtiPrev->m_uInfoStat ) )
                {
                    ppcr =  prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                    iPrev = g_fexScaleIntpl;
                    if( ppcr->m_rgiFexLogScaleFacIndex )
                        iPrev = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    prtiPrev = chexPrevTile( prp, prtiPrev );
                }
                if( iPrev == g_fexScaleIntpl ) // this shouldn't happen
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

                ppcinfo->m_piFexLogScaleFacIndex[iBand] += iPrev;
                ppcinfo->m_pffltFexScaleFac[iBand] =
                    FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacIndex[iBand] );
            }
            break;

        case FexScaleFacIntplPred:
            // find if any intra frame dependency in future
            prtiNext = chexNextTile( prp, pfx->m_prtiCurr );
            ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
            bLastTile = pfx->m_prtiCurr->m_prfxrti->m_bLastTileInFrame;
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                // find future anchor
                iNext = g_fexScaleIntpl;
                if( ppcr->m_rgiFexLogScaleFacIndex )
                    iNext = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                while( (ppcr->m_iFexScaleFacPred == FexScaleFacNo || iNext == g_fexScaleIntpl) &&
                       prtiNext != NULL && !bLastTile )
                {
                    ppcr = prtiNext->m_prfxrti->m_rgpcr + iFexCh;
                    iNext = g_fexScaleIntpl;
                    if( ppcr->m_rgiFexLogScaleFacIndex )
                        iNext = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    bLastTile = prtiNext->m_prfxrti->m_bLastTileInFrame;
                    prtiNext = chexNextTile( prp, prtiNext );
                }
            }
            if( prtiNext != NULL )
                prtiNext = chexPrevTile( prp, prtiNext ); // rewind one subframe back,
                                                          // prtiNext is one subframe ahead of anchor
            ppcrNextIntra = NULL;
            iNextIntra = 0;
            if( prtiNext != NULL &&
                ppcr->m_iFexScaleFacPred == FexScaleFacIntraPred )
            {
                // find the reference scale from previous
                prtiPrev = chexPrevTile( prp, prtiNext );
                ppcr = prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
                {
                    iPrev = g_fexScaleIntpl;
                    if( ppcr->m_rgiFexLogScaleFacIndex )
                        iPrev = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    while( chexInfoStatAdd( prtiPrev->m_uInfoStat ) && 
                           (ppcr->m_iFexScaleFacPred == FexScaleFacNo || iPrev == g_fexScaleIntpl) )
                    {
                        prtiPrev = chexPrevTile( prp, prtiPrev );
                        ppcr =  prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                        iPrev = g_fexScaleIntpl;
                        if( ppcr->m_rgiFexLogScaleFacIndex )
                            iPrev = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    }
                }
                // one subframe back,
                // because prtiPrev is one before the farthest interpolation subframe
                prtiPrev = chexNextTile( prp, prtiPrev );
                ppcr = prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                while( ppcr->m_iFexScaleFacPred == FexScaleFacNo )
                {
                    prtiPrev = chexNextTile( prp, prtiPrev );
                    ppcr = prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                }
                iPrev = ppcr->m_iFexLogScaleFacIndexRef;

                DEBUG_LOG_SCALE_FAC( iPrev );

                ppcr = prtiNext->m_prfxrti->m_rgpcr + iFexCh;
                ppcr->m_iFexLogScaleFacIndexRef = iPrev;
                ppcrNextIntra = ppcr;
                iNextIntra = ppcrNextIntra->m_iFexLogScaleFacIndexRef;

                DEBUG_LOG_SCALE_FAC( iNextIntra );

            }
            else if( ppcr->m_iFexScaleFacPred == FexScaleFacIntraPredNoRef )
            {
                ppcrNextIntra = ppcr;
                iNextIntra = 0;
            }

            // interpolation
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                cPrev = cNext = 0;
                // find previous anchor
                prtiPrev = chexPrevTile( prp, pfx->m_prtiCurr );
                ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
                iPrev = g_fexScaleIntpl;
                while( (ppcr->m_iFexScaleFacPred == FexScaleFacNo || iPrev == g_fexScaleIntpl) &&
                       chexInfoStatAdd( prtiPrev->m_uInfoStat ) )
                {
                    ppcr =  prtiPrev->m_prfxrti->m_rgpcr + iFexCh;
                    iPrev = g_fexScaleIntpl;
                    if( ppcr->m_rgiFexLogScaleFacIndex )
                        iPrev = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                    prtiPrev = chexPrevTile( prp, prtiPrev );
                    cPrev++;
                }

                if( iPrev == g_fexScaleIntpl ) // this shouldn't happen
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

                // update scale factor of future intra subframe
                if( ppcrNextIntra != NULL )
                    iNextIntra += ppcrNextIntra->m_rgiFexLogScaleFacIndex[iBand];

                if( ppcinfo->m_piFexLogScaleFacIndex[iBand] == g_fexScaleIntpl )
                {
                    // find next anchor to do interpolation
                    prtiNext = chexNextTile( prp, pfx->m_prtiCurr );
                    ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
                    bLastTile = pfx->m_prtiCurr->m_prfxrti->m_bLastTileInFrame;
                    iNext = g_fexScaleIntpl;
                    while( (ppcr->m_iFexScaleFacPred == FexScaleFacNo || iNext == g_fexScaleIntpl) &&
                           prtiNext != NULL && !bLastTile )
                    {
                        ppcr = prtiNext->m_prfxrti->m_rgpcr + iFexCh;
                        iNext = g_fexScaleIntpl;
                        if( ppcr->m_rgiFexLogScaleFacIndex )
                            iNext = ppcr->m_rgiFexLogScaleFacIndex[iBand];
                        bLastTile = prtiNext->m_prfxrti->m_bLastTileInFrame;
                        prtiNext = chexNextTile( prp, prtiNext );
                        cNext++;
                    }
                    // no update on index to keep anchor positions visible
                    if( iNext == g_fexScaleIntpl )
                    {
                        // hold value
                        ppcinfo->m_pffltFexScaleFac[iBand] = FASTFLOAT_FROM_INT( iPrev );
                    }
                    else
                    {
                        switch( ppcr->m_iFexScaleFacPred )
                        {
                            case FexScaleFacIntraPred:
                            case FexScaleFacIntraPredNoRef:
                                iNext = iNextIntra;
                                break;

                            case FexScaleFacInterPred:
                            case FexScaleFacIntplPred:
                                iNext += iPrev;
                                break;

                            default:
                                ASSERTWMA_EXIT( wmaResult, WMA_E_FAIL );
                                break;
                        }
                        // do interpolation
#ifndef BUILD_INTEGER
                        fIndex = (Float)(cNext*iPrev + cPrev*iNext) / (cNext + cPrev);
#else
                        assert( cPrev < 128 && iPrev < 128 );
                        assert( cNext < 128 && iNext < 128 );

                        fIndex.iFracBits  = 16;
                        fIndex.iFraction  = ( cNext*iPrev+cPrev*iNext ) << 16;
                        fIndex.iFraction /= ( cNext + cPrev );

                        Norm4FastFloat( &fIndex );
#endif
                        ppcinfo->m_pffltFexScaleFac[iBand] = fIndex;
                    }
                }
                else
                {
                    // interframe prediction
                    ppcinfo->m_piFexLogScaleFacIndex[iBand] += iPrev;
                    ppcinfo->m_pffltFexScaleFac[iBand] = 
                        FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacIndex[iBand] );
                }
            }
            // change prediction type for the last tile of this frame,
            // so that the first tile in the next frame won't refer tiles in this frame
            prtiNext = chexNextTile( prp, pfx->m_prtiCurr );
            if( prtiNext != NULL && pfx->m_prtiCurr->m_prfxrti->m_bLastTileInFrame )
            {
                ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr + iFexCh;
                ppcr->m_iFexScaleFacPred = FexScaleFacIntraPred;
                *(ppcinfo->m_pFexScaleFacPred) = FexScaleFacIntraPred;
            }
            break;

        case FexScaleFacChPred:
            // scale adjustment for channel prediction
            ppcr = pfx->m_prtiCurr->m_prfxrti->m_rgpcr; // first coded channel
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                ppcinfo->m_pffltFexScaleFac[iBand] =
                    freqexInvQuantScaleV2( pfx, pfxgp->m_iScFacStepSize, 
                    FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacIndex[iBand] ) );

                ppcinfo->m_pffltFexScaleFac[iBand] =
                    FASTFLOAT_MULT( ppcr->m_rgfFexScaleFac[iBand],
                                    ppcinfo->m_pffltFexScaleFac[iBand] );
            }
            break;

        default:
            ASSERTWMA_EXIT( wmaResult, WMA_E_FAIL );
            break;
    }

    if( *(ppcinfo->m_pFexScaleFacPred) != FexScaleFacChPred )
    {
        // log to linear
        for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            ppcinfo->m_pffltFexScaleFac[iBand] = 
                freqexInvQuantScaleV2( pfx, pfxgp->m_iScFacStepSize,
                                ppcinfo->m_pffltFexScaleFac[iBand] );
    }


exit:
    return wmaResult;
}

WMARESULT freqexReconBaseScaleBandsV2( CAudioObject    *pau,
                                       PerChannelInfo  *ppcinfo )
{
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    I32             iBand, iPrev;
    FastFloat       fScale;
    CoefType        *pfVec;
    WMARESULT       wmaResult = WMA_OK;

    if( pfx->m_cBaseBands == 0 )
        goto exit;

    switch( *(ppcinfo->m_pFexScaleFacBasePred) )
    {
        case FexScaleFacIntraPredNoRef:
            // intraframe prediction
            pfVec = pfx->m_pfRecon;
            iPrev = 0;
            for( iBand = 0; iBand < pfx->m_cBaseBands; iBand++ )
            {
                pfx->m_cBandSize = pfx->m_piBaseBandSizes[iBand];

                // target baseband scale
                ppcinfo->m_piFexLogScaleFacBaseIndex[iBand] += iPrev;
                ppcinfo->m_pffltFexScaleFacBase[iBand] = 
                    freqexInvQuantScaleV2( pfx, pfxgp->m_iBaseFacStepSize,
                        FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacBaseIndex[iBand] ) );
                iPrev = ppcinfo->m_piFexLogScaleFacBaseIndex[iBand];

                if( ppcinfo->m_piFexLogScaleFacBaseIndex[iBand] > 0 )
                {
                    // actual baseband scale

                    fScale = fexPower( pfVec, pfx->m_cBandSize, pau->m_cLeftShiftBitsFixedPost );
#ifdef BUILD_INTEGER
                    if( 0 != fScale.iFraction )
#else
                    if( 0 != fScale )
#endif
                        fScale = FASTFLOAT_DIV( FFLT_ONE, fScale );
                    else
                        fScale = FFLT_ZERO;

                    // derive adjustment scale
                    ppcinfo->m_pffltFexScaleFacBase[iBand] = 
                        FASTFLOAT_MULT( ppcinfo->m_pffltFexScaleFacBase[iBand], fScale );
                }
                else
                {
                    ppcinfo->m_pffltFexScaleFacBase[iBand] = FFLT_ONE;
                }
                pfVec += pfx->m_cBandSize;
            }
            break;

        case FexScaleFacReconPred:
            // recon pred
            for( iBand = 0; iBand < pfx->m_cBaseBands; iBand++ )
            {
                ppcinfo->m_pffltFexScaleFacBase[iBand] =
                    freqexInvQuantScaleV2( pfx, pfxgp->m_iBaseFacStepSize,
                    FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacBaseIndex[iBand] ) );
            }
            break;

        default:
            // ASSERTWMA_EXIT( wmaResult, WMA_E_FAIL );
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            break;
    }
exit:
    return wmaResult;
}

#if 0
WMARESULT freqexReconBaseScaleBandsV1Style( CAudioObject    *pau,
                                            PerChannelInfo  *ppcinfo )
{
    Fex       *pfx = &(pau->m_fex);
    I32       iBand, iCoef;
    Float     fScale;
    CoefType  *pfVec;
    WMARESULT wmaResult = WMA_OK;

    if( pfx->m_cBaseBands == 0 )
        goto exit;

    pfVec = pfx->m_pfRecon;
    for( iBand = 0; iBand < pfx->m_cBaseBands; iBand++ )
    {
        pfx->m_cBandSize = pfx->m_piBaseBandSizes[iBand];
        // actual baseband scale
        if( ppcinfo->m_piFexLogScaleFacBaseIndex[iBand] > 1 )
        {
            fScale = 0;
            for( iCoef = 0; iCoef < pfx->m_cBandSize; iCoef++ )
                fScale += pfVec[iCoef] * pfVec[iCoef];
            if( fScale > 0 )
                fScale = (Float)sqrt( pfx->m_cBandSize / fScale ); // inverse

            // derive adjustment scale
            ppcinfo->m_pffltFexScaleFacBase[iBand] = 
                FASTFLOAT_MULT( ppcinfo->m_pffltFexScaleFacBase[iBand], 
                                FASTFLOAT_FROM_FLOAT( fScale ) );
        }
        pfVec += pfx->m_cBandSize;
    }

exit:
    return wmaResult;
}
#endif

WMARESULT freqexSetScaleFacPtrChannel( CAudioObject *pau, PerChannelInfo *ppcinfo, Int iChSrc )
{
    WMARESULT wmaResult = WMA_OK;
    ReconProc       *prp = pau->m_prp;
    ReconTileInfo   *prti;
    PerChannelRecon *ppcr;
    Fex         *pfx = &(pau->m_fex);
    Int       iTile;

    if( pfx->m_iVersion == 1 )
        goto exit;

    if( !pfx->m_bReconDomain )
    {
        pfx->m_rgrgpfLogScaleFac     [0] = ppcinfo->m_pffltFexScaleFac;
        pfx->m_rgrgpiLogScaleFacIndex[0] = &(ppcinfo->m_piFexLogScaleFacIndex);
        pfx->m_rgpiLogScaleFacRef    [0] = ppcinfo->m_piFexLogScaleFacIndexRef;
        pfx->m_rgpScFacPredType      [0] = ppcinfo->m_pFexScaleFacPred;

        pfx->m_rgrgpfLogScaleFacBase     [0] = NULL;
        pfx->m_rgrgpiLogScaleFacBaseIndex[0] = NULL;
        pfx->m_rgpScFacBasePredType      [0] = NULL;
        goto exit;
    }

    if( pfx->m_bFirstTileV2Recon )
    {
        prti = pfx->m_prtiCurr;
        iTile = 0;
        while( iTile < prp->m_iTilesInSubframeProcFx )
        {
            if (prti == NULL)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
            if( !chexInfoStatNoFx(prti->m_uInfoStat) )
            {
                if (prti->m_prfxrti == NULL)
                {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                }
                ppcr = prti->m_prfxrti->m_rgpcr + iChSrc;

                pfx->m_rgrgpfLogScaleFac     [iTile] = ppcr->m_rgfFexScaleFac;
                pfx->m_rgrgpiLogScaleFacIndex[iTile] = &(ppcr->m_rgiFexLogScaleFacIndex);
                pfx->m_rgpiLogScaleFacRef    [iTile] = &(ppcr->m_iFexLogScaleFacIndexRef);
                pfx->m_rgpScFacPredType      [iTile] = &(ppcr->m_iFexScaleFacPred);

                pfx->m_rgrgpfLogScaleFacBase     [iTile] = ppcr->m_rgfFexScaleFacBase;
                pfx->m_rgrgpiLogScaleFacBaseIndex[iTile] = &(ppcr->m_rgiFexLogScaleFacBaseIndex);
                pfx->m_rgpScFacBasePredType      [iTile] = &(ppcr->m_iFexScaleFacBasePred);

                pfx->m_rgcScFacBaseBands[iTile]  = pfx->m_cBaseBands;

                iTile++;
            }
    
            prti = chexNextTile( prp, prti );
        }
#ifdef BUILD_WMAPROLBRV3
        if( pfx->m_iVersion > 2 && pau->m_bTileReconBs )
        {
            Int iTileCnt;
            // redo scale bands
            prti = pfx->m_prtiCurr;
            iTile = iTileCnt = 0;
            while( iTile < prp->m_iTilesInSubframeProcFx )
            {
                if( !chexInfoStatNoFx(prti->m_uInfoStat) )
                {
                    if (prti->m_prfxrti == NULL)
                    {
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    }
                    ppcr = prti->m_prfxrti->m_rgpcr + iChSrc;

                    pfx->m_rgrgpfLogScaleFac     [iTile] = ppcr->m_rgfFexScaleFac;
                    pfx->m_rgrgpiLogScaleFacIndex[iTile] = &(ppcr->m_rgiFexLogScaleFacIndex);
                    pfx->m_rgpiLogScaleFacRef    [iTile] = &(ppcr->m_iFexLogScaleFacIndexRef);
                    pfx->m_rgpScFacPredType      [iTile] = &(ppcr->m_iFexScaleFacPred);
                    iTile++;
                }
                prti = chexNextTile( prp, prti );
            }
            // redo base scale
            prti = pfx->m_prtiCurr;
            iTile = iTileCnt = 0;
            while( iTile < prp->m_iTilesInSubframeProcBs )
            {
                if( chexInfoStatCodeBs(prti->m_uInfoStat) )
                {
                    if (prti->m_prfxrti == NULL)
                    {
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    }
                    ppcr = prti->m_prfxrti->m_rgpcr + iChSrc;

                    pfx->m_rgrgpfLogScaleFacBase     [iTile] = ppcr->m_rgfFexScaleFacBase;
                    pfx->m_rgrgpiLogScaleFacBaseIndex[iTile] = &(ppcr->m_rgiFexLogScaleFacBaseIndex);
                    pfx->m_rgpScFacBasePredType      [iTile] = &(ppcr->m_iFexScaleFacBasePred);

                    pfx->m_rgcScFacBaseBands[iTile]  = prti->m_prfxrti->m_cFexBaseBands;

                    iTile++;
                }
                prti = chexNextTile( prp, prti );
            }
        }
#endif
    }
    else
    {
        prti = pfx->m_prtiCurr;
        ppcr = prti->m_prfxrti->m_rgpcr + iChSrc;

        assert(!chexInfoStatNoFx(prti->m_uInfoStat) || pfx->m_iVersion > 2);

        iTile = 0;
        pfx->m_rgrgpfLogScaleFac     [iTile] = ppcr->m_rgfFexScaleFac;
        pfx->m_rgrgpiLogScaleFacIndex[iTile] = &(ppcr->m_rgiFexLogScaleFacIndex);
        pfx->m_rgpiLogScaleFacRef    [iTile] = &(ppcr->m_iFexLogScaleFacIndexRef);
        pfx->m_rgpScFacPredType      [iTile] = &(ppcr->m_iFexScaleFacPred);

        pfx->m_rgrgpfLogScaleFacBase     [iTile] = ppcr->m_rgfFexScaleFacBase;
        pfx->m_rgrgpiLogScaleFacBaseIndex[iTile] = &(ppcr->m_rgiFexLogScaleFacBaseIndex);
        pfx->m_rgpScFacBasePredType      [iTile] = &(ppcr->m_iFexScaleFacBasePred);

#ifdef BUILD_WMAPROLBRV3
        if( pfx->m_iVersion > 2 )
        {
            if( chexInfoStatNoFx(prti->m_uInfoStat) )
            {
                pfx->m_rgrgpfLogScaleFac     [iTile] = NULL;
                pfx->m_rgrgpiLogScaleFacIndex[iTile] = NULL;
                pfx->m_rgpiLogScaleFacRef    [iTile] = NULL;
                pfx->m_rgpScFacPredType      [iTile] = NULL;
            }
        }
#endif
        for( iTile = 1; iTile < prp->m_iTilesInSubframeProcFx; iTile++ )
        {
            pfx->m_rgrgpfLogScaleFac     [iTile] = NULL;
            pfx->m_rgrgpiLogScaleFacIndex[iTile] = NULL;
            pfx->m_rgpiLogScaleFacRef    [iTile] = NULL;
            pfx->m_rgpScFacPredType      [iTile] = NULL;

            pfx->m_rgrgpfLogScaleFacBase     [iTile] = NULL;
            pfx->m_rgrgpiLogScaleFacBaseIndex[iTile] = NULL;
            pfx->m_rgpScFacBasePredType      [iTile] = NULL;
        }
#ifdef BUILD_WMAPROLBRV3
        if( pfx->m_iVersion > 2 )
        {
            for( ; iTile < prp->m_iTilesInSubframeProcBs; iTile++ )
            {
                pfx->m_rgrgpfLogScaleFacBase     [iTile] = NULL;
                pfx->m_rgrgpiLogScaleFacBaseIndex[iTile] = NULL;
                pfx->m_rgpScFacBasePredType      [iTile] = NULL;
            }
        }
#endif
    }

exit:
    return wmaResult;
}

Int freqexSetBaseBandConfigSize(CAudioObject *pau, Int cBands, Bool bGetMax)
{
    Fex *pfx = &(pau->m_fex);
    Int cNewBands, cBandsBeforeLastCodedIndex, iStartPosAfterLastIdx;

    cBandsBeforeLastCodedIndex = 0;

    pfx->m_cHoleBands = 0;
    pfx->m_rgiBandStart[pfx->m_cHoleBands] = 0;

    cNewBands = freqexSetBandConfigLoop(cBands, bGetMax, 0, pfx->m_cBaseEnd,
                                        pfx->m_piBaseBandSizes,
                                        pfx->m_iMinBandSize,
                                        pfx->m_iMaxBandSize,
                                        WMAB_FALSE,
                                        WMAB_FALSE,
                                        pfx->m_piBaseBandSizesM,
                                        cBandsBeforeLastCodedIndex,
                                        &iStartPosAfterLastIdx);

    return cNewBands;
}

Int freqexSetBaseBandConfig(CAudioObject *pau, Int cBands, Bool bGetMax)
{
    Fex *pfx = &(pau->m_fex);
    Int i, cNewBands;

    // set end position
    freqexSetBaseEnd(pau, pfx->m_cSubFrameSampleHalf,
                        pfx->m_bShrinkBaseBand ? WMAB_TRUE : pfx->m_bBaseScaleOnly);
    cNewBands = freqexSetBaseBandConfigSize(pau, cBands, bGetMax);

    if (pfx->m_bShrinkBaseBand)
    {
        assert(!pfx->m_bBaseScaleOnly);
        // shrink #BaseBands
        pfx->m_cStartIndex = 0;
        for (i = 0; i < cNewBands; i++)
        {
            // get #bands which covers iMinFreq at least
            if (pfx->m_cStartIndex >= pfx->m_cStart)
                break;
            pfx->m_cStartIndex += pfx->m_piBaseBandSizes[i];
        }
        cNewBands = i;
        // do band sizing with shrinked value
        freqexSetBaseEnd(pau, pfx->m_cSubFrameSampleHalf, pfx->m_bBaseScaleOnly);
        cNewBands = freqexSetBaseBandConfigSize( pau, cNewBands, bGetMax );
    }

    return cNewBands;
}

#ifdef BUILD_WMAPROLBRV3
WMARESULT freqexBaseScaleAndAddToRecon( CAudioObject *pau,
                                        PerChannelInfo * ppcinfo,
                                        Int iBand,
                                        CoefType *pfBase,
                                        CoefType *pfRecon )
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(pau->m_fex);
    Int iCoef;
    FastFloat fflt;

    if (pfx->m_iVersion <= 2 || 
        !pfx->m_bReconDomain ||
        ppcinfo->m_piFexCb[iBand] != 4)
        goto exit;

    fflt = ppcinfo->m_pffltFexScaleFacNoise[iBand];
    CHECK_COEF_MUL_FFLT( fflt );
    for (iCoef = 0; iCoef < pfx->m_cBandSize; iCoef++)
    {
        pfRecon[iCoef] += COEF_MUL_FFLT(pfBase[iCoef], fflt);
    }
exit:
    return wmaResult;
}
#endif
#endif // BUILD_WMAPROLBRV2

Void freqexSetLastCodedIndex(CAudioObject *pau, Int iChCodeSrc)
{
    Fex *pfx = &(pau->m_fex);
    Int iCh, iChSrc, iMax, iNum, iFexCh;
    PerChannelInfo *ppcinfo;
    PerChannelInfoShr *pcisSrc = pau->m_rgpcinfoShr + iChCodeSrc;
    Bool bPower = WMAB_FALSE;
    Int cChannel;

    cChannel = pau->m_cChInTile;

    iMax = 0;
    iNum = 0;
    for (iCh=0; iCh < cChannel; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

#if defined(BUILD_WMAPROLBRV2)
        iFexCh = chexGetFexChannel(pau, iChSrc);
        if (iFexCh != iChSrc)
            continue;
#endif // defined(BUILD_WMAPROLBRV2)

        if (pfx->m_bUseSingleMv ||
            (pcisSrc->m_uFxChannelDependencyMask & (1<<iChSrc)))
        {
            iMax = max(iMax, ppcinfo->m_cLastCodedIndex);
            iNum++;
            bPower |= (ppcinfo->m_iPower != 0);
        }
    }
    if (iNum == pau->m_cChInTile && iMax != pau->m_cLastCodedIndex &&
           bPower)
    {
        pfx->m_wmaResult = WMA_E_BROKEN_FRAME; // Will be checked upstream
    }
    pfx->m_iMaxLastCodedIndexOrig = iMax;
    if (WMAB_TRUE==pfx->m_bSplitTileIntoSubtiles)
        pfx->m_iMaxLastCodedIndex = pfx->m_iMaxLastCodedIndexOrig/2;
    else
        pfx->m_iMaxLastCodedIndex = pfx->m_iMaxLastCodedIndexOrig;
}

Bool freqexNeedChCode(CAudioObject *pau, PerChannelInfo *ppcinfo, Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    Int iCh,  iFexCh;

    // skip subwoofer channel
    if (!pau->m_bDoFexOnCodedChannels &&
        iChSrc == pau->m_nSubWooferChannel)
        return WMAB_FALSE;
    if (pau->m_bDoFexOnCodedChannels &&
        iChSrc == pau->m_nSubWooferChannel &&
        freqexIsChannelIndependent(pfx, iChSrc))
        return WMAB_FALSE;

    if (pfx->m_iIteration == 0)
        return WMAB_TRUE;

    assert( pau->m_rgpcinfo + iChSrc == ppcinfo );
    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
#if defined(BUILD_WMAPROLBRV2)
        iFexCh = chexGetFexChannel(pau, iCh);
        if (iFexCh != iCh)
            continue;
#endif // defined(BUILD_WMAPROLBRV2)

        if (pau->m_rgpcinfoShr[iChSrc].m_uFxChannelDependencyMask & (1<<iCh))
        {
            ppcinfo = pau->m_rgpcinfo + iCh;
            if (ppcinfo->m_iPower != 0)
                return WMAB_TRUE;
        }
    }

    return WMAB_FALSE;
}

Void freqexProcessZeroMaskXChannel(CAudioObject *pau)
{
    Fex *pfx = &pau->m_fex;
    U8 *pucMask0, *pucMask1;
    Int iGrp, iCh, iFexCh;
    Int iBark, iStartCoeff, iEndCoeff, iStartByte, iEndByte, iByte, iBits;
    PerChannelInfoShr *pcis;
    U8 sByte, eByte, uMask;

    if (pau->m_bXChannelProc)
        return;

    for (iGrp=0; iGrp < pau->m_cChannelDependencyGroups; iGrp++)
    {
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pcis = pau->m_rgpcinfoShr + iCh;

            if (!(pcis->m_uFxChannelGroupMask & (1<<iGrp)))
                continue;

            if (pcis->m_iFxChannelDependencyGroup == iCh)
                continue;

            // for chex don't do cross channel processing across shared
            // channels
#if defined(BUILD_WMAPROLBRV2)
            iFexCh = chexGetFexChannel(pau, iCh);
            if (pcis->m_iFxChannelDependencyGroup == iFexCh)
                continue;
#endif // defined(BUILD_WMAPROLBRV2)

            for (iBark=0; iBark < pau->m_cValidBarkBand; iBark++)
            {
                if (!prvIsBarkInd(pau, iCh, iBark) || pau->m_bCx)
                {
                    pucMask0 = pau->m_ucNonzeroCoeffMask +
                        pcis->m_iFxChannelDependencyGroup*
                        pau->m_cFrameSampleHalf/8;
                    pucMask1 = pau->m_ucNonzeroCoeffMask +
                        iCh*
                        pau->m_cFrameSampleHalf/8;
                    iStartCoeff = pau->m_rgiBarkIndex[iBark];
                    iEndCoeff = pau->m_rgiBarkIndex[iBark+1]-1;
                    iStartByte = iStartCoeff/8;
                    iEndByte = iEndCoeff/8;
                    sByte = pucMask0[iStartByte];
                    eByte = pucMask0[iEndByte];
                    for (iByte=iStartByte; iByte <= iEndByte; iByte++)
                        pucMask0[iByte] |= pucMask1[iByte];
                    // set iBits of LSB to sByte
                    iBits = iStartCoeff-iStartByte*8;
                    uMask = 0xff<<iBits;
                    pucMask0[iStartByte] &= uMask;
                    pucMask0[iStartByte] |= (sByte & ~uMask);
                    // set iBits of MSB to eByte
                    iBits = (iEndByte+1)*8 - iEndCoeff - 1;
                    uMask = 0xff>>iBits;
                    pucMask0[iEndByte] &= uMask;
                    pucMask0[iEndByte] |= (eByte & ~uMask);
                }
            }
        }
    }

    for (iGrp=0; iGrp < pau->m_cChannelDependencyGroups; iGrp++)
    {
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            pcis = pau->m_rgpcinfoShr + iCh;

            if (!(pcis->m_uFxChannelGroupMask & (1<<iGrp)))
                continue;

            if (pcis->m_iFxChannelDependencyGroup == iCh)
                continue;

            for (iBark=0; iBark < pau->m_cValidBarkBand; iBark++)
            {
                if (!prvIsBarkInd(pau, iCh, iBark) || pau->m_bCx)
                {
                    pucMask0 = pau->m_ucNonzeroCoeffMask +
                        pcis->m_iFxChannelDependencyGroup*
                        pau->m_cFrameSampleHalf/8;
                    pucMask1 = pau->m_ucNonzeroCoeffMask +
                        iCh*
                        pau->m_cFrameSampleHalf/8;
                    iStartCoeff = pau->m_rgiBarkIndex[iBark];
                    iEndCoeff = pau->m_rgiBarkIndex[iBark+1]-1;
                    iStartByte = iStartCoeff/8;
                    iEndByte = iEndCoeff/8;
                    sByte = pucMask1[iStartByte];
                    eByte = pucMask1[iEndByte];
                    memcpy(pucMask1+iStartByte,
                           pucMask0+iStartByte,
                           (iEndByte-iStartByte+1));
                    // set iBits of LSB to sByte
                    iBits = iStartCoeff-iStartByte*8;
                    uMask = 0xff<<iBits;
                    pucMask1[iStartByte] &= uMask;
                    pucMask1[iStartByte] |= (sByte & ~uMask);
                    // set iBits of MSB to eByte
                    iBits = (iEndByte+1)*8 - iEndCoeff - 1;
                    uMask = 0xff>>iBits;
                    pucMask1[iEndByte] &= uMask;
                    pucMask1[iEndByte] |= (eByte & ~uMask);
                }
            }
        }
    }

    pau->m_bXChannelProc = WMAB_TRUE;
}

Void freqexSetBandConfigChannel(CAudioObject *pau, Int iChCode, Int iChSrc)
{
    Fex *pfx = &(pau->m_fex);
    Int cBands, i;
    Int iConfig = pau->m_rgpcinfoShr[iChSrc].m_iFxBandConfig;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + iChSrc;

    if( !pfx->m_bReconDomain )
        freqexSetStartPosChannel(pau, iChCode, iChSrc);

    if (pfx->m_iVersion >= 2)
    {
        if (pfx->m_bEntireHoleOverlay)
            freqexProcessZeroMaskXChannel(pau);
        freqexSetGroup(pau, iChSrc, WMAB_FALSE, WMAB_FALSE);
    }

    // set the band configuration for this channel
#ifdef BUILD_WMAPROLBRV2
    if( pcis->m_iFxScaleBands == pcis->m_iFxMvBands )
    {
#endif
        cBands = freqexSetBandConfig(pau, pcis->m_iFxScaleBands,
                                    WMAB_FALSE, WMAB_FALSE);
        pfx->m_cScaleBands = cBands;

        cBands = freqexSetBandConfig(pau, pcis->m_iFxMvBands,
                                    WMAB_FALSE, WMAB_TRUE);
        pfx->m_cMvBands = cBands;

        for( i = 0; i < pfx->m_cMvBands; i++ )
            pfx->m_rgcScaleBandsPerMvBand[i] = 1;

#ifdef BUILD_WMAPROLBRV2
    }
    else if( pcis->m_iFxScaleBands > pcis->m_iFxMvBands &&
             pfx->m_iVersion > 1 && !pfx->m_bV1Compatible)
    {
        freqexSetBandConfigForMergedMv( pau, pcis->m_iFxScaleBands,
                                        pcis->m_iFxMvBands );
    }
    else
    {
        assert( WMAB_FALSE );
        return;
    }

    pfx->m_cBaseBands = pfx->m_cBaseBandsGlobal;
    if( pfx->m_cBaseBands > 0 )
    {
        cBands = freqexSetBaseBandConfig( pau, pfx->m_cBaseBands, WMAB_FALSE );
        pfx->m_cBaseBands = cBands;
    }
#endif

#if 0
    if (pfx->m_iIteration == 3)
    {
        Int i;
        printf("MAXIDX=%d STARTIDX=%d CHCODE=%d NBANDS=%d\n",
               pfx->m_iMaxLastCodedIndex, pfx->m_cStart,
               iChCode, pfx->m_cScaleBands);
        for (i=0; i < pfx->m_cScaleBands; i++)
        {
            printf("%d ", pfx->m_piScaleBandSizes[i]);
        }
        printf("\n");
    }
#endif
}

#define FEXBANDCONFIG_SCALE (2048)

Bool freqexSetBandSizes(Int *cBandSizes, Int iCoeffs, Int iTotal,
                        Int iMinBandSize, Int iMaxBandSize,
                        Int cBands, Int *pcBands, Bool bSort,
                        Bool bAllowZeroSizeBands)
{
    Int iStartScale, iCurTotal, iNewTotal;
    Bool bOverflow;
    Int i, k;

    iStartScale = iCoeffs*FEXBANDCONFIG_SCALE / iTotal;
    iCurTotal = 0;
    iTotal = 0;
    iNewTotal = 0;
    bOverflow = WMAB_FALSE;
    for (i=0; i < cBands; i++)
    {
        iCurTotal += iStartScale * cBandSizes[i];
        cBandSizes[i] = (iCurTotal-iTotal)/FEXBANDCONFIG_SCALE;
        if (i == cBands-1) // last band
        {
            cBandSizes[i] = iCoeffs-iNewTotal;
        }
        if (cBandSizes[i] > iMaxBandSize)
        {
            cBandSizes[i] = iMaxBandSize;
            bOverflow = WMAB_TRUE;
        }
        if (cBandSizes[i] < iMinBandSize)
        {
            cBandSizes[i] = iMinBandSize;
            NO_ERROR_REPORT_BITSTREAM_CORRUPTION_AND_EXIT;
        }
        iTotal += cBandSizes[i]*FEXBANDCONFIG_SCALE;
        iNewTotal += cBandSizes[i];
        if (WMAB_TRUE==bSort)
        { // insertion sort
            Int j, l;
            Int iTmp = cBandSizes[i];
            for (j=i-1; j>=0; j--)
            { // going backward faster, since already sorted
                if (cBandSizes[j] <= iTmp)
                    break;
            }
            j++; // this is the point to insert
            for (l=i; l > j; l--)
            {
                cBandSizes[l] = cBandSizes[l-1];
            }
            cBandSizes[j] = iTmp;
        }
    }
    assert(iNewTotal == iCoeffs ||
           ((iNewTotal <= iCoeffs) && bOverflow));

    // remove size 0 bands
    if (WMAB_FALSE==bAllowZeroSizeBands)
    {
        for (i=0; i < cBands; i++)
        {
            if (0 == cBandSizes[i])
            {
                for (k=i; k < cBands-1; k++)
                    cBandSizes[k] = cBandSizes[k+1];
                cBands--;
                i--;
            }
        }
    }

    *pcBands = cBands;
exit:
    return bOverflow;
}

Int freqexSetBandConfigLoop(Int cBands, Bool bGetMax, Int cStart, Int cEnd,
                          Int *piBandSizes, Int iMinBandSize, Int iMaxBandSize,
                          Bool bArbitraryBandConfig, Bool bUseUniformBands,
                          const Int *piBandSizeM,
                          Int cNumBandsBelowLastCodedIndex,
                          Int *piFirstBandStartPosAfterLastCodedIdx)
{
    Int i, j, k;
    Int cNewBands, cActBands=0;
    Int *cBandSizes;
    Int iTotal;
    Int iFexCoeffs = cEnd - cStart;
    Bool bOverflow;
    FN_CNT;

    *piFirstBandStartPosAfterLastCodedIdx = cStart;

    cBandSizes = piBandSizes;

    // in order to prevent overshifting of mv and give enough start positions
    // we have to impose minimum and maximum band sizes
    // max mv shift = (max start pos + 1)/(2*mv bins)
    // max mv shift <= band size / N
    // (max start pos + 1)/(2*mv bins) <= band size / N
    // band size >= (N*max start pos+N)/(2*mv bins)
    // max start pos = (cutoff-band size)
    // band size >= (N*(cutoff-band size)+N)/(2*mv bins)
    // band size*(2*mv bins + N) >= N*(cutoff+1)
    //
    // band size >= N*(cutoff+1)/(2*mv bins + N) (for non-noise)
    // band size >= 0 (for noise) since we can adjust max start pos accordingly
    //
    // Also to have at least one start pos
    // max start pos = (cutoff - band size) >= 0
    //
    // band size <= cutoff (for non-noise)
    // band size <= g_iFexNoiseLen (for noise)since we can adjust max start pos

    // no limit on min band size, if we are overshifting, just turn on
    // pfxe->m_bOnlySearchQuantPts

    // cBands for fex start to fex end
    if (iFexCoeffs <= 0)
        cBands = 0;
    if (cBands==0 && !bGetMax)
    {
        cNewBands = 0;
        goto exit;
    }
    iTotal = 0;
    for (k=0; k < cNumBandsBelowLastCodedIndex; )
    {
        cBandSizes[k] = iMinBandSize;
        iTotal += cBandSizes[k];
        k++; // increment k before following break
        if (iTotal >= iFexCoeffs || ((k==cBands) && !bGetMax))
            goto done;
    }
    for (i=0; i < g_iFexNumBandSize; i++)
    {
        for (j=g_rgiFexNBandsAtSize[i]; j < g_rgiFexNBandsAtSize[i+1]; j++)
        {
            if (bArbitraryBandConfig)
                cBandSizes[k] = piBandSizeM[k] * iMinBandSize;
            else if (bUseUniformBands)
                cBandSizes[k] = iMinBandSize;
            else
                cBandSizes[k] = piBandSizeM[i] * iMinBandSize;
            iTotal += cBandSizes[k];
            k++;
            if (iTotal >= iFexCoeffs || ((k==cBands) && !bGetMax))
                goto done;
        }
    }
done:
    assert(iTotal != 0);
    if (iTotal < iFexCoeffs)
    {
        // have to code more coeffs than we can using cBands of min size
        // maximum # of bands using min size will be higher.
        if (bGetMax)
            cBands = k;
        else
            assert(k==cBands); // leave cBands unmodified
    }
    else if (iTotal > iFexCoeffs)
    {
        // have to code less coeffs than we can using cBands of min size
        // cBands is the maximum # of bands
        cBands = k-1; // reduce the number of bands
        iTotal -= cBandSizes[cBands];
    }
    else
    {
        // cBands is the maximum # of bands
        cBands = k;
    }
    cNewBands = cBands;
    if (cNewBands == 0 || bGetMax)
        goto exit;
    assert(iFexCoeffs >= iTotal);

    bOverflow = freqexSetBandSizes(cBandSizes, iFexCoeffs, iTotal,
                                   iMinBandSize, iMaxBandSize,
                                   cBands, &cActBands, WMAB_FALSE, WMAB_FALSE);

    if (cBands != cActBands)
    {
        NO_ERROR_REPORT_BITSTREAM_CORRUPTION_AND_EXIT;
    }

    for (i=0; i < cNumBandsBelowLastCodedIndex; i++)
        *piFirstBandStartPosAfterLastCodedIdx += cBandSizes[i];

exit:
    return cNewBands;
}

Int freqexSetBandConfigNoHole(CAudioObject *pau, Int cBands,
                              Bool bGetMax, Bool bMvBands)
{
    Fex *pfx = &(pau->m_fex);
    Int cNewBands, cBandsBeforeLastCodedIndex, iStartPosAfterLastIdx;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + pfx->m_iChSrc;
    Int *piBandSizes = (bMvBands == WMAB_TRUE) ?
        pfx->m_piMvBandSizes : pfx->m_piScaleBandSizes;
    Int *piBandSizeM = (pcis->m_bFxArbitraryBandConfig == WMAB_TRUE) ?
        (Int *)pfx->m_piBandSizeM : (Int *)pfx->m_piFexBandSizesM;

    pfx->m_rgiBandStart[pfx->m_cHoleBands] = pfx->m_cStart;

    piBandSizes += pfx->m_cHoleBands;

    cBandsBeforeLastCodedIndex = 0;
    while (1)
    {
        cNewBands =
            freqexSetBandConfigLoop(cBands, bGetMax,
                                    pfx->m_cStart, pfx->m_cEnd,
                                    piBandSizes,
                                    pfx->m_iMinBandSize, pfx->m_iMaxBandSize,
                                    pcis->m_bFxArbitraryBandConfig,
                                    pcis->m_bFxUseUniformBands,
                                    piBandSizeM,
                                    cBandsBeforeLastCodedIndex,
                                    &iStartPosAfterLastIdx);

        if (iStartPosAfterLastIdx >= pfx->m_iMaxLastCodedIndex ||
            pfx->m_iIteration < 2 ||
            cNewBands <= cBandsBeforeLastCodedIndex)
            break;

        cBandsBeforeLastCodedIndex++;
    }

    return cNewBands;
}

Int freqexSetBandConfigHole(CAudioObject *pau, Int cBands,
                            Bool bGetMax, Bool bMvBands)
{
    Fex *pfx = &pau->m_fex;
    Int *piBandSizes = (bMvBands == WMAB_TRUE) ?
        pfx->m_piMvBandSizes : pfx->m_piScaleBandSizes;
    Int *piBandStart = pfx->m_rgiBandStart;
    Int cNewBands, cHoleBands, cLastCodedIndexSave;

    cHoleBands = 0;

    if (pfx->m_iIteration >= 2)
    {
        assert(pau->m_rgpcinfo[0].m_rgCoefRecon);

        freqexInitHoleOverlay(pau, pau->m_rgpcinfo[0].m_rgCoefRecon);
        while (1)
        {
            freqexGetNextHole(pau);
            if (!pfx->m_bHoleBand)
                break;
            if (cHoleBands >= pfx->m_cMaxBands/2)
                break;

            cNewBands = (pfx->m_iHoleBandSize-1) / pfx->m_cMaxRunOfZerosPerBandForOverlay + 1;
            cNewBands = min(cNewBands, pfx->m_cMaxBands/2 - cHoleBands);
            while (cNewBands > 0)
            {
                piBandSizes[cHoleBands] = pfx->m_iHoleBandSize / cNewBands;
                piBandStart[cHoleBands] = pfx->m_iHoleBandStart;
                pfx->m_iHoleBandSize -= piBandSizes[cHoleBands];
                pfx->m_iHoleBandStart += piBandSizes[cHoleBands];
                cHoleBands++;
                cNewBands--;
            }
        }
        cHoleBands = min(cHoleBands, cBands);
        if (pfx->m_iEndHoleFillConditionIndex == 0 && cHoleBands > 0)
        {
            cHoleBands = 0;
            pfx->m_cStart = piBandStart[0];
        }
        else if (pfx->m_iEndHoleFillConditionIndex == 1 && cHoleBands > pfx->m_cMaxBands/4)
        {
            cHoleBands = pfx->m_cMaxBands/4;
            pfx->m_cStart = piBandStart[cHoleBands];
        }
    }

    pfx->m_cHoleBands = cHoleBands;

    cLastCodedIndexSave = pfx->m_iMaxLastCodedIndex;
    pfx->m_iMaxLastCodedIndex = pfx->m_cStart;
    cNewBands = freqexSetBandConfigNoHole(pau,
                                          max(0, cBands-pfx->m_cHoleBands),
                                          bGetMax, bMvBands);
    pfx->m_iMaxLastCodedIndex = cLastCodedIndexSave;

//    assert(cNewBands + cHoleBands <= pfx->m_cMaxBands/2);

    return (cNewBands + cHoleBands);
}

Int freqexSetBandConfig(CAudioObject *pau, Int cBands,
                        Bool bGetMax, Bool bMvBands)
{
    Fex *pfx = &pau->m_fex;

    pfx->m_cHoleBands = 0;

    if (pfx->m_bEntireHoleOverlay && !pfx->m_bReconDomain)
        return freqexSetBandConfigHole(pau, cBands, bGetMax, bMvBands);
    else
        return freqexSetBandConfigNoHole(pau, cBands, bGetMax, bMvBands);
}

// ==================================================================

INLINE Int freqexRandomMv( const Fex *pfx )
{
    // iMv+cBandSize-1 <= 1023,
    // or iMv <= 1024-cBandSize, iMv < 1025-cBandSize

    return rand()*(g_iFexNoiseLen+1-pfx->m_cBandSize)/(((U32)RAND_MAX)+1);
}

// deterministic "random" vector based upon band size, start index, mask len,
// primary mv
INLINE Int freqexRandomMv2( const Fex *pfx, const Int iMaskLen, const Int iMv )
{
    Int a = (iMaskLen+iMv) % 10;
    Int b = pfx->m_cBandSize % 10;
    Int c = pfx->m_cStartIndex % 10;
    // 0 to g_iFexNoiseLen-pfx->m_cBandSize
    return (c*100+b*10+a) % (g_iFexNoiseLen+1-pfx->m_cBandSize);
}


#define CHECK_RANDOM_MV(iMv) \
if (iMv+pfx->m_cBandSize > g_iFexNoiseLen || iMv < 0) \
{ \
    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult); \
}

Void freqexGetRandomVec( Float *pVec, Int iLen )
{
    for (; iLen > 0; iLen--)
    {
        // want to use gaussian noise, but just try with uniform for now
        // sqrt(12)*(rand()/RAND_MAX-0.5) should have variance of 1.0
        *pVec++ = (Float)rand()/RAND_MAX-0.5f;
        //*pVec++ = (Float)quickRand(&pau->m_tRandState); // triang noise
    }
}

Int freqexComplementMask( U8 *pMask, Int iLen )
{
    Int iMaskLen;

    iMaskLen = 0;
    for (; iLen > 0; iLen--)
    {
        *pMask = !(*pMask);
        iMaskLen += *pMask;
        pMask++;
    }

    return iMaskLen;
} 

INLINE
FastFloat freqexGetBandScale( FastFloat fBandScale, 
                        const FastFloat fMvScale,
                        const QuantStepType fGlobalQ )
{

#if 0
    if( 1.0f > FLOAT_FROM_FASTFLOAT( fMvScale ) )
        return fBandScale;
#endif

#ifndef BUILD_INTEGER

    if (fGlobalQ != 0.0f && fGlobalQ != 1.0f)
        fBandScale *= (1.0f / fGlobalQ);

    if (fMvScale != 0.0f && fMvScale != 1.0f )
        fBandScale *= (1.0f / fMvScale);

    return fBandScale;

#else // !BUILD_INTEGER
 
    if (fGlobalQ.iFraction != 0 )
        fBandScale = FASTFLOAT_DIV( fBandScale, fGlobalQ );

    if (fMvScale.iFraction != 0 )
        fBandScale = FASTFLOAT_DIV( fBandScale, fMvScale );

    return fBandScale;

#endif // BUILD_INTEGER
}

Void freqexRemovePeaksFromNoise(CoefType *pVec, const U8* pMask, Int iLen)
{
    for (; iLen > 0; iLen--)
    {
        if (*pMask)
            *pVec = 0;
        pVec++;
        pMask++;
    }
}

#if 0

// write freqexScaleBand() data to "fsb.log". this logs source
// coefficient, freqex coefficient, final scale factor, target
// scale ( numerator ), source scale ( denominator ), and exp.

FILE *g_file_fsb = NULL;

#if !defined( BUILD_INTEGER )
static const LPCSTR g_filename_fsb = "fsb_log.flt";
#else
static const LPCSTR g_filename_fsb = "fsb_log.int";
#endif 

#define DBG_FREQEX_SCALE_BAND()                         \
if( !bNoise &&  (                                       \
    ( FLOAT_FROM_FASTFLOAT( fBandScale ) > 1 && 0 ) ||  \
    ( FLOAT_FROM_FASTFLOAT( fMvScale )   < 1 && 1 ) ) ) \
{   if( NULL == g_file_fsb )                            \
        g_file_fsb = fopen( g_filename_fsb, "w" );      \
    fprintf( g_file_fsb, "%f\t%f\t%f\n",                \
        FLOAT_FROM_FASTFLOAT( fBandScale ),             \
        FLOAT_FROM_FASTFLOAT( fMvScale ),               \
        FLOAT_FROM_FEXT( fExp ) );                      \
}

#else

//#define DBG_FREQEX_SCALE_BAND()

#endif



#define FEX_OVERLAYBAND
#include "fextemplate.c"
#undef FEX_OVERLAYBAND
#include "fextemplate.c"

Int freqexKeepPeaks(Fex *pfx, 
                      const CoefType *pVec, 
                      const CoefType *pfRecon,
                      U8 *pMask, const Int iLen,
                      const Bool bRev,
                      const Int iRecLen,
                      Int *piCbStart,
                      const I32 cLeftShiftBits,
                      Int *piActLen)
{
    if (WMAB_TRUE == pfx->m_bOverlayUsedForBand)
        return freqexKeepPeaksOverlay(pfx, pVec, pfRecon, pMask, iLen,
                                      bRev, iRecLen, piCbStart, cLeftShiftBits, piActLen);
    else
        return freqexKeepPeaksNoOverlay(pfx, pVec, pfRecon, pMask, iLen,
                                      bRev, iRecLen, piCbStart, cLeftShiftBits, piActLen);
}

FastFloat freqexGetMvBandScale( Fex      *pfx,
                          const CoefType *pVec, 
                          const CoefType *pfRecon,
                          const Int iLen,
                          const FexType fExp,
                          const Bool bRev,
                          const Int iRecLen,
                                Int *piCbStart,
                                Int lshift )
{
    FastFloat rv;

    if (WMAB_TRUE == pfx->m_bOverlayUsedForBand) 
        rv = freqexGetMvBandScaleOverlay(pfx, pVec, pfRecon, iLen,
                                         fExp, bRev, iRecLen, piCbStart, lshift);
    else 
        rv = freqexGetMvBandScaleNoOverlay(pfx, pVec, pfRecon, iLen,
                                           fExp, bRev, iRecLen, piCbStart, lshift);
    return rv;
}

FastFloat freqexGetMvBandScaleWithMask( Fex *pfx,
                                    const CoefType *pVec, 
                                    const CoefType *pfRecon,
                                    const U8 *pucMask, 
                                    const Int iLen,
                                    const Bool bRev,
                                    const Int iRecLen,
                                          Int *piCbStart,
                                          Int lshift )
{
    if (NULL==pucMask)
        return freqexGetMvBandScale(pfx, pVec, pfRecon, iLen,
                                    FEXT_FROM_FLOAT(1.0f), 
                                    bRev, iRecLen, piCbStart, (Int)lshift);

    if (WMAB_TRUE == pfx->m_bOverlayUsedForBand)
        return freqexGetMvBandScaleWithMaskOverlay(pfx, pVec, pfRecon,
                                                   pucMask, iLen,
                                                   bRev, iRecLen, piCbStart, lshift);
    else
        return freqexGetMvBandScaleWithMaskNoOverlay(pfx, pVec, pfRecon,
                                                     pucMask, iLen,
                                                     bRev, iRecLen, piCbStart, lshift);
}

WMARESULT freqexScaleBand( PerChannelInfo *ppcinfo, Fex *pfx, 
                           const FastFloat *pfScaleFac,
                           const FastFloat fMvScale, CoefType *pfRecon,
                           const CoefType *pVec, const U8 *pucMask,
                           CoefType *pReconDST, const CoefType *pVecDST,
                           const Int iLen, const QuantStepType fGlobalQ,
                           const FexType fExp, const Int iCwSign,
                           const Bool bRev, const Int iRecLen,
                           Int *piCbStart,
                           Int *plshift, const Bool bNoise,
                           FastFloat *pfBandScale)
{
    WMARESULT rv;

    if (WMAB_TRUE == pfx->m_bOverlayUsedForBand)
        rv =  freqexScaleBandOverlay(ppcinfo, pfx, pfScaleFac, fMvScale,
                                     pfRecon, pVec, pucMask,
                                     pReconDST, pVecDST, iLen,
                                     fGlobalQ, fExp, iCwSign, bRev,
                                     iRecLen, piCbStart, plshift,
                                     bNoise, pfBandScale);
    else
        rv =  freqexScaleBandNoOverlay(ppcinfo, pfx, pfScaleFac, fMvScale,
                                       pfRecon, pVec, pucMask,
                                       pReconDST, pVecDST, iLen,
                                       fGlobalQ, fExp, iCwSign, bRev,
                                       iRecLen, piCbStart, plshift,
                                       bNoise, pfBandScale);
    return rv;
}

#if (defined(FEX_SCALE_BAND_C_OPT) && !WMA_OPT_FEX_SCL_BAND_OPT_ARM)  
void freqexScaleBandLoop(const CoefType *pVec, CoefType *pfRecon, const U8 *pucMask,   
    const Int iCwSign, const FexType fExp, FastFloat *pfBandScale1, Int * piAccumRshift,          
    const Bool bNoise, Int * plshift, 
    const Int iStart, const Int iEnd, Int k, const Int iStep)
{
    Int i;
       
    for (i=iStart; i < iEnd; i++, k+=iStep)
    {
        if (NULL==pucMask || pucMask[i]==1)
        {

            CoefType coef = pVec[k];

            if( 0 == coef )
            {
                pfRecon[i] = 0;
            }
            else
            {
                FastFloat fval;

                fval.iFraction = (I32)coef * iCwSign;
                fval.iFracBits = ( bNoise ) ? FEXT_BITS : *plshift;
                Norm4FastFloat( &fval );

                if( FEXT_FROM_FLOAT( 1.0f ) != fExp )
                {
                    I32 iSign = 1;
                    
                    if( 0 > fval.iFraction )
                    {
                        iSign = -1;
                        fval.iFraction = -fval.iFraction;
                    }

                    if( FEXT_FROM_FLOAT( 0.5f ) == fExp )
                    {
                        fval = FASTFLOAT_SQRT( fval );
                    }
                    else if( FEXT_FROM_FLOAT( 2.0f ) && DBG_EXP_2 )
                    {
                        fval = FASTFLOAT_MULT( fval, fval );
                    }

                    if( 0 > iSign )
                        fval.iFraction = -fval.iFraction;
                }

                fval = FASTFLOAT_MULT( fval, *pfBandScale1 );

                if( fval.iFracBits > 31 )
                {
                    pfRecon[i] = 0;
                }
                else if( 0 > fval.iFracBits )
                {
                    const Int rshift = -fval.iFracBits;

                    *piAccumRshift += rshift;

                    *plshift -= rshift;
                    pfBandScale1->iFracBits += rshift;

                    pfRecon[i] = fval.iFraction;
                }

                else
                {
                    pfRecon[i] = (CoefType)( fval.iFraction >> fval.iFracBits );
                }
            }
        }       // if (IS_VALID_MASK())
    }       // for (i=0; i < iLen; i++,k+=step)
}
#endif  // #if (defined(FEX_SCALE_BAND_C_OPT) && !WMA_OPT_FEX_SCL_BAND_OPT_ARM)

#if (defined FEX_GET_MV_SCALE_C_OPT && !WMA_OPT_FEX_GET_MV_SCALE_ARM)
void freqexGetMvBandScaleLoop(const CoefType *pVec, const Int iLen, Int j0, Int i0, 
    I32 rshift, I64 *pfScale, const FexType fExp, Bool bRev)
{
    Int  i, j, step = (bRev) ? -1 : 1;

    for( j=j0, i=i0; j < iLen; i+=step,++j )
    {
        assert( U32_MAX > ABS( pVec[i] ) );

        if( FEXT_FROM_FLOAT( 0.5f ) == fExp )
        {
//            *pfScale += COEF_ABS( pVec[i] ) >> rshift;
            *pfScale += COEF_ABS( pVec[i] >> rshift ) ;
        }
        else if( FEXT_FROM_FLOAT( 1.0f ) == fExp )
        {  
            *pfScale += ( (I64)(pVec[i] >> (rshift/2)) * (I64)(pVec[i] >> (rshift/2)) ) ;
        }
        else if( FEXT_FROM_FLOAT( 2.0f ) == fExp )
        {
            I32 tmp = (I32)( (I64)(pVec[i] >> (rshift/4)) * (I64)(pVec[i] >> (rshift/4)) );
            *pfScale += (I64)tmp * (I64)tmp;
        }
        else
        {
            assert( !"only exponents of 0.5, 1, and 2 are supported." );
        }
        assert( 0 <= *pfScale );
    }
}
#endif  // FEX_GET_MV_SCALE_C_OPT

// recon an mv band
WMARESULT freqexReconBand(       CAudioObject *pau,
                                 PerChannelInfo * ppcinfo,
                           const Int iBand,
                                 CoefType *pfRecon,
                           const CoefType *pfLowband,
                           const QuantStepType fGlobalQ )
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(pau->m_fex);
    PerChannelInfoShr *pcis = ppcinfo->m_ppcinfoShr;
    //CoefType *pfReconOrig = pfRecon;

#ifndef BUILD_INTEGER
    Int cLeftShiftBits = 0; // does nothing in float build.
#else
    Int cLeftShiftBits =
        pfx->m_bReconDomain ?
        pau->m_cLeftShiftBitsFixedPost :
        ( ppcinfo->m_cLeftShiftBitsTotal 
        - ppcinfo->m_cLeftShiftBitsQuant );
#endif

    const Int cTileSizeAdjusted = auGetAdjustedSize(pau, pfx->m_cTileSize);

    const Bool bNeedMvCoding = pfx->m_bNeedMvCoding;
    const Bool bUseExponent  = pfx->m_bNeedMvCoding && ( pfx->m_bReconDomain || pcis->m_bFxUseExponent );
    const Bool bUseSign      = pfx->m_bNeedMvCoding && ( pfx->m_bReconDomain || pcis->m_bFxUseSign );

    const Int     iCb   = bNeedMvCoding ? ppcinfo->m_piFexCb  [iBand] : 1;
    const Bool    bRev  = bNeedMvCoding ? ppcinfo->m_pbFexRev [iBand] : WMAB_FALSE;
    const Int     iSign = bUseSign      ? ppcinfo->m_piFexSign[iBand] : 1;
          FexType fExp  = bUseExponent  ? ppcinfo->m_pFexExp  [iBand] : FEXT_FROM_FLOAT(1.0f);
          Int     iMv   = bNeedMvCoding ? ppcinfo->m_piFexMv  [iBand] : 0;
          Int     iMv2  =                 ppcinfo->m_piFexMv2 [iBand];

    const Int cCoeffsDec = max( 0, min( pfx->m_cBandSize, 
                cTileSizeAdjusted - pfx->m_cStartIndex ) );

    FastFloat fMvScale;
    Int cCoeffsRem, cCoeffsRec, cCoeffsActRem;
    Int iCbStart, iCbStart1, j, iScaleBandStart, cStartIndexSaved;

    const CoefType *pfCb=0, *pfCbDST;

    if (pau->m_bIgnoreFreqex)
        goto exit;

    if (ppcinfo->m_bNoDecodeForCx)
        goto exit;

    if (pfx->m_bReconDomain)
    {
        if (0 != pfx->m_cHoleBands ||
            (0 == iBand && pfx->m_cStartIndex != pfx->m_cStart))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
    }

#if 0
    if (!pfx->m_bReconDomain)
    {
    printf("%d %d %d %d %d ",
           pau->m_iFrameStart, pfx->m_bReconDomain,
           pfx->m_iBand < pfx->m_cHoleBands,
           pfx->m_bReconDomain ?
           pfx->m_prtiCurr->m_iStartPt :
           pau->m_iCurrTile,
           iBand);
    if (iCb==0 || iCb==1)
        printf("%d %d %f %d %f\n",
               iCb, iMv, FLOAT_FROM_FEXT( fExp ), iSign, 
        FLOAT_FROM_FASTFLOAT( ppcinfo->m_pffltFexScaleFac[iBand] ) );

    else
        printf("%d %d %d %f %d %f %f\n",
               iCb, iMv, iMv2, FLOAT_FROM_FEXT( fExp ), iSign,
               FLOAT_FROM_FASTFLOAT(ppcinfo->m_pffltFexScaleFac[iBand]),
               FLOAT_FROM_FASTFLOAT(ppcinfo->m_pffltFexScaleFacNoise[iBand]));
    }
#endif

    if( cCoeffsDec == 0 ) goto exit;

    if (pfx->m_bUseRandomNoise && iCb==1)
    {
        iMv = freqexRandomMv(pfx);
        CHECK_RANDOM_MV(iMv);
    }

    iScaleBandStart = 0;
    for (j = 0; j < iBand; j++)
        iScaleBandStart += pfx->m_rgcScaleBandsPerMvBand[j];

    // form the codeword
    if (iCb==0 || iCb==2 || iCb==4)
    {
        if (pfx->m_bReconDomain && WMAB_FALSE==pau->m_bEncoder)
        {
            iMv = iMv*pfx->m_prtiCurr->m_iSizeCurr /
                pfx->m_rgprtiMvAnchor[pfx->m_iChCode]->m_iSizeCurr;
            iMv2 = iMv2*pfx->m_prtiCurr->m_iSizeCurr / 
                pfx->m_rgprtiMvAnchor[pfx->m_iChCode]->m_iSizeCurr;
        }

        // either both or pure lowband
        if( !bRev )
        {
            pfCb = pfLowband + iMv;
            cCoeffsRem  = cTileSizeAdjusted - iMv;
        }
        else
        {
            pfCb = pfLowband + pfx->m_cStartIndex - 1 - iMv;
            cCoeffsRem  = cTileSizeAdjusted - (pfx->m_cStartIndex - iMv);
        }

        pfCbDST = pfCb + cTileSizeAdjusted;
        cCoeffsRem  = max(0, cCoeffsRem);
        cCoeffsRem  = min(cCoeffsRem, pfx->m_cBandSize);

        cCoeffsRec  = cCoeffsRem;
        // reset recursive coeffs for recursive codeword generation
        if( pfx->m_cStartIndex - iMv < pfx->m_cBandSize )
        {
            if( WMAB_FALSE == pfx->m_bRecursiveCwGeneration &&
                WMAB_FALSE == pfx->m_bMvRangeFull )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult)
            }
            cCoeffsRec  = pfx->m_cStartIndex - iMv;
        }
        iCbStart = 0;
    }
    else if (iCb==1)
    {
        if (pfx->m_bReconDomain && !pfx->m_bUseRandomNoise && WMAB_FALSE==pau->m_bEncoder)
        {
            if( ppcinfo->m_piFexMvOffsetNoiseCB[iBand] < 0 )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult)
            }
            // add offset

            iMv += ppcinfo->m_piFexMvOffsetNoiseCB[iBand];
            while (iMv >= g_iFexNoiseLen)
                iMv -= g_iFexNoiseLen;
            // increment for next tile
            ppcinfo->m_piFexMvOffsetNoiseCB[iBand] += pfx->m_cBandSize;
        }
        // pure noise
        pfCb = g_rgfFexNoise;
        pfCbDST = NULL;
        cCoeffsRem  = pfx->m_cBandSize;
        cCoeffsRec  = g_iFexNoiseLen;
        iCbStart    = iMv;
    }
    else
    {
        assert(WMAB_FALSE);
        cCoeffsRem = 0;
        cCoeffsRec = 0;
        iCbStart   = 0;
    }

    // but the following should also hold true
    if (cCoeffsRem != pfx->m_cBandSize && cCoeffsDec > 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    if (iCb==2)
    {
        Int iScaleBandSave, iCoeffScaleFacBandSave, iMaskLen;
        Int iActLen;
        Int bits;

        assert( FEXT_FROM_FLOAT( 1.0f ) == fExp );

        // compute noise scale if rfex, and store it in pfx
        for (j = 0; j < pfx->m_rgcScaleBandsPerMvBand[iBand]; j++)
        {
            if (pfx->m_bReconDomain)
            {
                pfx->m_pffltFexScaleFacNoise[iScaleBandStart+j] =
                    FASTFLOAT_MULT( ppcinfo->m_pffltFexScaleFacNoise[iBand],
                                    ppcinfo->m_pffltFexScaleFac[iScaleBandStart+j] );
            }
            else
            {
                pfx->m_pffltFexScaleFacNoise[iScaleBandStart+j] = ppcinfo->m_pffltFexScaleFacNoise[iBand];
            }
        }

        // modify the codeword by only keeping peaks & adding noise mv
        cStartIndexSaved = pfx->m_cStartIndex;
        for (j = 0; j < pfx->m_rgcScaleBandsPerMvBand[iBand]; j++)
        {
            cCoeffsActRem = min(cCoeffsRem,
                                pfx->m_piScaleBandSizes[iScaleBandStart+j]);
            iCbStart1 = iCbStart;

            iMaskLen = freqexKeepPeaks(pfx, pfCb, pfRecon,
                                       pfx->m_rgucCwMask, cCoeffsActRem,
                                       bRev, cCoeffsRec, &iCbStart1, 
                                       cLeftShiftBits,
                                       &iActLen);

            if (iMaskLen <= 0)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }

            // determine peak scale factor

            bits = 1 + LOG2( (U32)iActLen );

            pfx->m_pffltFexScaleFacPeaks[iScaleBandStart+j] =
                FASTFLOAT_FLOAT_DIV( FASTFLOAT_ADD(
                FASTFLOAT_FLOAT_MULT( ppcinfo->m_pffltFexScaleFac[iScaleBandStart+j],
                                                iActLen , bits ),
                FASTFLOAT_FLOAT_MULT( pfx->m_pffltFexScaleFacNoise[iScaleBandStart+j],
                                                (iMaskLen-iActLen), bits ) ),
                                     iMaskLen, bits );

            //printf("%d\n", iMaskLen);
            // get mv scale for peaks
            // no need to use mask, since coeffs have been 0'd
            iCbStart1 = iCbStart;
            fMvScale = freqexGetMvBandScaleWithMask( pfx,
                                                     pfCb, pfRecon,
                                                     pfx->m_rgucCwMask,
                                                     cCoeffsActRem,
                                                     bRev, cCoeffsRec, &iCbStart1, 
                                                     cLeftShiftBits );
            // recon peaks
            iScaleBandSave = pfx->m_iScaleBand;
            iCoeffScaleFacBandSave = pfx->m_iCoeffScaleFacBand;

            iCbStart1 = iCbStart;

            TRACEWMA_EXIT(wmaResult,
                          freqexScaleBand( ppcinfo, pfx,
                                           pfx->m_pffltFexScaleFacPeaks,
                                           fMvScale, pfRecon, pfCb,
                                           pfx->m_rgucCwMask, NULL, NULL,
                                           cCoeffsActRem,
                                           fGlobalQ, FEXT_FROM_FLOAT( 1.0f ),
                                           iSign, bRev, cCoeffsRec, &iCbStart1,
                                           &cLeftShiftBits, WMAB_FALSE, NULL ));

            if (pcis->m_bFxUseRandomMv2)
            {
                iMv2 = freqexRandomMv2(pfx, iMaskLen, iMv);
                CHECK_RANDOM_MV(iMv2);
            }
            
            if ( pfx->m_cBandSize > pfx->m_iMaxBandSize )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
            // complement the mask
            freqexComplementMask(pfx->m_rgucCwMask, pfx->m_cBandSize);
            // get mv scale for noise
            iCbStart1 = iCbStart;
            fMvScale = freqexGetMvBandScaleWithMask( pfx,
                                                     g_rgfFexNoise + iMv2,
                                                     pfRecon, pfx->m_rgucCwMask,
                                                     cCoeffsActRem,
                                                     bRev, cCoeffsRec, &iCbStart1,
                                                     FEXT_BITS );
            // recon noise
            pfx->m_iScaleBand = iScaleBandSave;
            pfx->m_iCoeffScaleFacBand = iCoeffScaleFacBandSave;

            TRACEWMA_EXIT(wmaResult,
                          freqexScaleBand( ppcinfo, pfx,
                                           pfx->m_pffltFexScaleFacNoise,
                                           fMvScale, pfRecon, g_rgfFexNoise+iMv2,
                                           pfx->m_rgucCwMask, NULL, NULL,
                                           cCoeffsActRem,
                                           fGlobalQ, FEXT_FROM_FLOAT( 1.0f ),
                                           1, bRev, cCoeffsRem, &iCbStart,
                                           &cLeftShiftBits, WMAB_TRUE, NULL ));
            
            pfx->m_cStartIndex += pfx->m_piScaleBandSizes[iScaleBandStart+j];
            pfRecon += pfx->m_piScaleBandSizes[iScaleBandStart+j];
            cCoeffsRem -= cCoeffsActRem;
            assert( cCoeffsRem >= 0 );
        }
        pfx->m_cStartIndex = cStartIndexSaved;
    }
#ifdef BUILD_WMAPROLBRV3
    else if (iCb == 4 && !pfx->m_bReconDomain)
    {
        Int iScaleBandSave, iCoeffScaleFacBandSave, iMaskLen, iActLen;
        Bool bUseObtainedBandScaleSave = pfx->m_bUseObtainedBandScale;
        FastFloat fObtainedBandScaleSave = pfx->m_fObtainedBandScale;

        cStartIndexSaved = pfx->m_cStartIndex;
        for (j = 0; j < pfx->m_rgcScaleBandsPerMvBand[iBand]; j++)
        {
            cCoeffsActRem = min(cCoeffsRem,
                                pfx->m_piScaleBandSizes[iScaleBandStart+j]);

            // apply exponent only (don't apply scale and sign)
            iCbStart1 = iCbStart;
            pfx->m_bUseObtainedBandScale = WMAB_TRUE;
            pfx->m_fObtainedBandScale = FFLT_ONE;
            iScaleBandSave = pfx->m_iScaleBand;
            iCoeffScaleFacBandSave = pfx->m_iCoeffScaleFacBand;
            TRACEWMA_EXIT(wmaResult,
                            freqexScaleBand( ppcinfo, pfx,
                                             ppcinfo->m_pffltFexScaleFac,
                                             FFLT_ONE, pfRecon, pfCb, NULL,
                                             NULL, NULL, cCoeffsActRem,
                                             FFLT_ONE, fExp, 1, bRev,
                                             cCoeffsRec, &iCbStart1,
                                             &cLeftShiftBits,
                                             WMAB_FALSE, NULL ));
            pfx->m_bUseObtainedBandScale = bUseObtainedBandScaleSave;
            pfx->m_fObtainedBandScale = fObtainedBandScaleSave;
            pfx->m_iScaleBand = iScaleBandSave;
            pfx->m_iCoeffScaleFacBand = iCoeffScaleFacBandSave;

            // get mask from exponented coef
            iCbStart1 = iCbStart;
            iMaskLen = freqexKeepPeaks(pfx, pfRecon, pfRecon,
                                       pfx->m_rgucCwMask, cCoeffsActRem,
                                       bRev, cCoeffsRec, &iCbStart1, 
                                       cLeftShiftBits,
                                       &iActLen);
            // get mv scale from masked coef
            iCbStart1 = iCbStart;
            fMvScale = freqexGetMvBandScaleWithMask( pfx,
                                                     pfRecon, pfRecon,
                                                     pfx->m_rgucCwMask,
                                                     cCoeffsActRem,
                                                     bRev, cCoeffsRec, &iCbStart1, 
                                                     cLeftShiftBits );
            // reconstruct peaks
            memset(pfRecon, 0, sizeof(CoefType) * cCoeffsActRem);
            TRACEWMA_EXIT(wmaResult,
                          freqexScaleBand( ppcinfo, pfx,
                                           ppcinfo->m_pffltFexScaleFac,
                                           fMvScale, pfRecon, pfCb,
                                           pfx->m_rgucCwMask, NULL, NULL,
                                           cCoeffsActRem,
                                           fGlobalQ, fExp,
                                           iSign, bRev, cCoeffsRec, &iCbStart,
                                           &cLeftShiftBits, WMAB_FALSE, NULL ));

            pfx->m_cStartIndex += pfx->m_piScaleBandSizes[iScaleBandStart+j];
            pfRecon += pfx->m_piScaleBandSizes[iScaleBandStart+j];
            cCoeffsRem -= cCoeffsActRem;
            assert( cCoeffsRem >= 0 );
        }
        pfx->m_cStartIndex = cStartIndexSaved;
    }
#endif
    else
    {
        cStartIndexSaved = pfx->m_cStartIndex;
        for (j = 0; j < pfx->m_rgcScaleBandsPerMvBand[iBand]; j++)
        {
            FastFloat fBandScale;
            iCbStart1 = iCbStart;
            cCoeffsActRem = min(cCoeffsRem,
                                pfx->m_piScaleBandSizes[iScaleBandStart+j]);

            if (WMAB_FALSE==pfx->m_bUseObtainedBandScale)
            {
                // can overwrite with good mv, etc... here

                fMvScale = freqexGetMvBandScale( pfx, pfCb, pfRecon,
                                cCoeffsActRem, fExp, bRev, cCoeffsRec,
                                &iCbStart1,
                                ( 1 == iCb ) ? FEXT_BITS : cLeftShiftBits );
            }
            else
            {
                assert(pfx->m_iVersion > 1 && !pfx->m_bV1Compatible);
                pfx->m_fObtainedBandScale =
                    ppcinfo->m_pffBandScale[iScaleBandStart+j];
            }

            if (WMAB_TRUE==pfx->m_bAdjustScaleForDelayedExp &&
                WMAB_TRUE==pfx->m_bUseObtainedBandScale)
                fExp = FEXT_FROM_FLOAT(1.0f); // delay the exponentiation

            TRACEWMA_EXIT(wmaResult,
                            freqexScaleBand( ppcinfo, pfx,
                                            ppcinfo->m_pffltFexScaleFac,
                                            fMvScale, pfRecon, pfCb, NULL,
                                            NULL, NULL, cCoeffsActRem,
                                            fGlobalQ, fExp, iSign, bRev,
                                            cCoeffsRec, &iCbStart,
                                            &cLeftShiftBits,
                                            ( 1 == iCb ), &fBandScale ));

#if defined(ALLOW_EXTERNAL_FILE_FOR_RECON)
            if (pau->m_bEncoder && !pfx->m_bReconDomain && g_bReplaceCFx)
                prvReplaceSamplesExtBufCh(pau, ppcinfo,
                                 pfx->m_cStartIndex,
                                 pfx->m_cStartIndex +
                                 pfx->m_piScaleBandSizes[iScaleBandStart+j]);
#endif

            pfx->m_cStartIndex += pfx->m_piScaleBandSizes[iScaleBandStart+j];
            pfRecon += pfx->m_piScaleBandSizes[iScaleBandStart+j];
            cCoeffsRem -= cCoeffsActRem;
            assert( cCoeffsRem >= 0 );
            if (WMAB_FALSE == pfx->m_bUseObtainedBandScale && iCbStart != iCbStart1)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }

            if (pfx->m_iVersion > 1 && !pfx->m_bV1Compatible)
            {
                if (WMAB_FALSE==pfx->m_bUseObtainedBandScale)
                {
#if !defined(BUILD_INTEGER)
                    if (1 == iCb || 1)
                        fBandScale /= 2.0f;
#else
                    if (1 == iCb || 1 )
                        ++fBandScale.iFracBits;
#endif
                    ppcinfo->m_pffBandScale[iScaleBandStart+j] = fBandScale;
                }
            }
        }
        pfx->m_cStartIndex = cStartIndexSaved;
    }

#if 0
    if (!pfx->m_bReconDomain)
    {
        Int ii;
        FILE *fp = NULL;
        FILE_DUMP_INIT(rec);
        if (0)
            fprintf(fp, "F=%d SF=%d B=%d S=%d Z=%d\n",
                    pau->m_bEncoder ?
                    pau->m_iFrameNumber-1 : pau->m_iFrameNumber,
                    pau->m_iCurrTile, iBand,
                    pfx->m_cStartIndex, pfx->m_cBandSize);
        for (ii=0; ii < pfx->m_cBandSize; ii++)
            fprintf(fp, "%f\n", pfReconOrig[ii]);
    }
#endif

    if( pfx->m_cScaleBands == pfx->m_cMvBands )
        assert(iBand+1 == pfx->m_iScaleBand);

exit:
    return wmaResult;
}

WMARESULT freqexRecon( CAudioObject   *pau,
                       PerChannelInfo *ppcinfo,
                       Int            iChSrc,
                 const QuantStepType   fGlobalQ )
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(pau->m_fex);
    Int iBand;
    CoefType *pfRecon;

    initFP();

    // NOTE: pfx->m_pfRecon   = recon buffer
    //     : pfx->m_pfLowband = baseband buffer
    assert( pfx->m_pfRecon != NULL );
    assert( pfx->m_pfLowband != NULL );

    // redo this for recon fex
    freqexSetScaleBandsPerMvBand(pfx, pfx->m_cScaleBands, pfx->m_cMvBands,
                                 pfx->m_rgcScaleBandsPerMvBand);

#ifdef BUILD_WMAPROLBRV2
    if( pfx->m_iVersion > 1 && pfx->m_bReconDomain )
    {
        // compute reference scale factor
        if( pfx->m_cScaleBands > 0 )
            *(ppcinfo->m_piFexLogScaleFacIndexRef) = 
                freqexComputeScaleRefV2( pfx, pfx->m_pfRecon,
                            pau->m_cLeftShiftBitsFixedPost );
        // reconstruct scale factors
        // base scale
        TRACEWMA_EXIT(wmaResult,
                      freqexReconBaseScaleBandsV2(pau, ppcinfo));
        // fex scale
        TRACEWMA_EXIT(wmaResult,
                      freqexReconScaleBandsV2(pau, ppcinfo, iChSrc));
    }
#endif

    pfx->m_rgiBandStart[pfx->m_cHoleBands] = pfx->m_cStart;
    pfx->m_iScaleBand = 0;
    pfx->m_iCoeffScaleFacBand = 0;

    for (iBand=0; iBand < pfx->m_cMvBands; iBand++)
    {
        Int iValidLen = 1;

        pfx->m_cBandSize = pfx->m_piMvBandSizes[iBand];
        if (iBand <= pfx->m_cHoleBands)
            pfx->m_cStartIndex = pfx->m_rgiBandStart[iBand];
        pfRecon = pfx->m_pfRecon+pfx->m_cStartIndex;

        freqexSetBandParams(pau, ppcinfo, pfx->m_iChCode, iBand);
        assert(pfx->m_cBandSize == pfx->m_piMvBandSizes[iBand]);

        if( !pfx->m_bReconDomain )
            iValidLen = freqexGetValidLength(pfx, pfRecon, pfx->m_cBandSize);

        freqexSetNeedMvCoding(pfx, ppcinfo, iBand, iValidLen);
        TRACEWMA_EXIT(wmaResult,
                      freqexReconBand(pau, ppcinfo, iBand, pfRecon,
                                      pfx->m_pfLowband, fGlobalQ));
#ifdef BUILD_WMAPROLBRV3
        if (pfx->m_bReconDomain && pfx->m_iVersion > 2)
        {
            CoefType *pfBaseRfx = pfx->m_pfBaseRfx + pfx->m_cStartIndex;
            TRACEWMA_EXIT(wmaResult,
                          freqexBaseScaleAndAddToRecon(pau, ppcinfo, iBand, pfBaseRfx, pfRecon));
        }
#endif
        if (iBand >= pfx->m_cHoleBands)
            pfx->m_cStartIndex += pfx->m_cBandSize;
    }

#ifdef BUILD_WMAPROLBRV2
    if( pfx->m_iVersion > 1 && pfx->m_bReconDomain )
    {
        // baseband scale adjustment
        pfRecon = pfx->m_pfRecon;
        for (iBand = 0; iBand < pfx->m_cBaseBands; iBand++)
        {
            FastFloat fflt = ppcinfo->m_pffltFexScaleFacBase[iBand];
            Int iCoef;

            pfx->m_cBandSize = pfx->m_piBaseBandSizes[iBand];

            CHECK_COEF_MUL_FFLT( fflt );

            for (iCoef = 0; iCoef < pfx->m_cBandSize; iCoef++)
                pfRecon[iCoef] = COEF_MUL_FFLT( pfRecon[iCoef], fflt );

            pfRecon += pfx->m_cBandSize;
        }
    }
#endif

#if defined(FEX_DBG_RECON_PRINT)
    {
        Int l, j, k;
        printf("================\n");
        k = 0;
        for (l=0; l < pfx->m_cStart; l++, k++)
            printf("%d %d %f -1 -1\n", 0, k,
                   pfx->m_pfRecon[k]);
        for (l=0; l < pfx->m_cMvBands; l++) {
            for (j=0; j < pfx->m_piMvBandSizes[l]; j++, k++)
                printf("%d %d %f %d %d\n", 0, k,
                       pfx->m_pfRecon[k], l,
                       ppcinfo->m_piFexMv[l]);
        }
        for (; k < pfx->m_cTileSize; k++)
            printf("0\n");
    }
#endif
exit:

    catchFP();
    return wmaResult;
}

// ====================================================================

// in place interleave/deinterleave of buffer
Void freqexBufInterleave( CoefType *pBuf, const Int nVals,
                          const Bool bDeInterleave )
{
    CoefType temp, *pBuf1, *pBuf2;
    Int iStages, iBlkSize, iBlkSize4, iBlocks;
    Int i, j, k;

    iStages = LOG2((UInt)nVals);
    assert( nVals == (1<<iStages) );

    if (bDeInterleave)
    {
        iBlocks   = nVals>>2;
        iBlkSize  = 1;
        iBlkSize4 = 4;
    }
    else
    {
        iBlocks   = 1;
        iBlkSize  = nVals>>2;
        iBlkSize4 = nVals;
    }
    for (i=0; i < iStages; i++)
    {
        pBuf1 = pBuf + iBlkSize;
        pBuf2 = pBuf + (iBlkSize<<1);
        for (j=0; j < iBlocks; j++)
        {
            // swap the middle two elements
            for (k=0; k < iBlkSize; k++)
            {
                temp     = pBuf1[k];
                pBuf1[k] = pBuf2[k];
                pBuf2[k] = temp;
            }
            pBuf1 += iBlkSize4;
            pBuf2 += iBlkSize4;
        }
        if (bDeInterleave)
        {
            iBlocks   >>= 1;
            iBlkSize  <<= 1;
            iBlkSize4 <<= 1;
        }
        else
        {
            iBlocks   <<= 1;
            iBlkSize  >>= 1;
            iBlkSize4 >>= 1;
        }
    }
}

Void freqexInvSplitRecon( const Fex *pfx, CoefType *pfRecon,
                          const PerChannelInfo *ppcinfo)
{
    CoefType *psrc0, *psrc1, dst0, dst1;
    Int i;
    PerChannelInfoShr *pcis = pfx->m_pau->m_rgpcinfoShr + pfx->m_iChSrc;

    psrc0 = pfRecon;
    psrc1 = pfRecon + pfx->m_cSubFrameSampleHalf/2;

    for (i=0; i < pfx->m_cSubFrameSampleHalf/2; i++)
    {
        dst0 = psrc0[i] + psrc1[i];
        dst1 = psrc0[i] - psrc1[i];
        psrc0[i] = dst0;
        psrc1[i] = dst1;
    }
    freqexBufInterleave(pfRecon, pfx->m_cSubFrameSampleHalf, WMAB_FALSE);
    if ((pfx->m_cOrigStart & 1) &&
        (pcis->m_fFxSplitTileSaveCoeff != 0) &&
        (WMAB_FALSE==pfx->m_bOverwriteBase))
    {
        //printf("Overwrite %d %f\n", pfx->m_cOrigStart-1,
        //    pfx->m_rgfSplitTileSaveCoeff[pfx->m_iChCode]);
        pfRecon[pfx->m_cOrigStart-1] = pcis->m_fFxSplitTileSaveCoeff;
    }
}

Void freqexBufOps( CAudioObject *pau, 
             const FexBufOp bufOp, 
             const Int nVals,
                   CoefType *dst,
                   CoefType *src,
             const Int iLen )
{
    Fex *pfx = &(pau->m_fex);
    Int i, j;
    CoefType *pdst0, *pdst1, dst0, dst1;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + pfx->m_iChSrc;

    if (WMAB_FALSE==pfx->m_bSplitTileIntoSubtiles)
    {
        switch (bufOp)
        {
        case ClearBuf:
            memset(dst, 0, iLen*sizeof(CoefType));
            break;
        case CopyBuf:
            memcpy(dst, src, iLen*sizeof(CoefType));
            break;
        case AddToBuf:
            for (i=0; i < iLen; i++)
            {
                dst[i] += src[i];
            }
            break;
        case AvgBuf:
            for (i=0; i < iLen; i++)
            {
                dst[i] /= (CoefType)nVals;
            }
            break;
        }
    }
    else if (dst != src)
    {
        pdst0 = dst;
        pdst1 = dst + pfx->m_cSubFrameSampleHalf/2;
        switch(bufOp)
        {
        case ClearBuf:
            memset(pdst0, 0, iLen/2*sizeof(CoefType));
            memset(pdst1, 0, iLen/2*sizeof(CoefType));
            break;
        case CopyBuf:
            for (i=0, j=0; i < iLen; i+=2, j++)
            {
                pdst0[j] = (src[i] + src[i+1])/(CoefType)2;
                pdst1[j] = (src[i] - src[i+1])/(CoefType)2;
            }
            break;
        case AddToBuf:
            for (i=0, j=0; i < iLen; i+=2, j++)
            {
                pdst0[j] += (src[i] + src[i+1])/(CoefType)2;
                pdst1[j] += (src[i] - src[i+1])/(CoefType)2;
            }
            break;
        case AvgBuf:
            for (j=0; j < iLen/2; j++)
            {
                pdst0[j] /= (CoefType)nVals;
                pdst1[j] /= (CoefType)nVals;
            }
            break;
        }
    }
    else // in place
    {
        assert(pfx->m_cSubFrameSampleHalf == iLen);
        // save last coeff & set to 0
        if (pfx->m_cOrigStart & 1)
        {
            //printf("SAVE %f\n", src[pfx->m_cOrigStart-1]);
            pcis->m_fFxSplitTileSaveCoeff = src[pfx->m_cOrigStart-1];
            src[pfx->m_cOrigStart-1] = 0;
        }
        switch (bufOp)
        {
        case ClearBuf: assert(WMAB_FALSE);  break;
        case CopyBuf:
            for (i=0; i < iLen; i+=2)
            {
                dst0 = (src[i] + src[i+1])/(CoefType)2;
                dst1 = (src[i] - src[i+1])/(CoefType)2;
                src[i] = dst0;
                src[i+1] = dst1;
            }
            break;
        case AddToBuf: assert(WMAB_FALSE);  break;
        case AvgBuf: assert(WMAB_FALSE);  break;
        }
        freqexBufInterleave(src, iLen, WMAB_TRUE);
    }
}

// =====================================================================

Void freqexFrameInit(CAudioObject *pau)
{
    Fex *pfx = &(pau->m_fex);

    if (pfx)
    {
        pfx->m_bFirstTile = WMAB_TRUE;
        if (pfx->m_iVersion > 1)
            pfx->m_bFirstTileV2Coding = WMAB_TRUE;
        // set overlay params coded & noise floor params coded to false
        pfx->m_bOverlayCoded = WMAB_FALSE;
        pfx->m_bNoiseFloorParamsCoded = WMAB_FALSE;
        pfx->m_bMinRunOfZerosForOverlayCoded = WMAB_FALSE;
    }
}

// =====================================================================

Bool prvIsBarkInd(CAudioObject *pau,
                  const Int iChSrc, const Int iBark)
{
    Int iGroup;
    Bool bInd = WMAB_TRUE;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + iChSrc;

    if ((Int)(pcis->m_uFxChannelDependencyMask) == (1<<iChSrc))
        goto exit;

    for (iGroup=0; iGroup < pau->m_cChannelGroups; iGroup++)
    {
        if (pcis->m_uFxChannelGroupMask & (1<<iGroup))
        {
            if (WMAB_TRUE == 
                pau->m_rgChannelGrpInfo[iGroup].m_rgfXformOn[iBark])
            {
                bInd = WMAB_FALSE;
                goto exit;
            }
        }
    }

exit:
    return bInd;
}

Bool freqexIsBarkInd(CAudioObject *pau,
                     const Int iStartBark, const Int iEndBark)
{
    Fex *pfx = &pau->m_fex;
    Int iGroup, iBark;
    Bool bInd = WMAB_TRUE;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + pfx->m_iChSrc;

    for (iGroup=0; iGroup < pau->m_cChannelGroup; iGroup++)
    {
        if (pcis->m_uFxChannelGroupMask & (1<<iGroup))
        {
            for (iBark=iStartBark; iBark < iEndBark; iBark++)
            {
                if (WMAB_TRUE == 
                    pau->m_rgChannelGrpInfo[iGroup].m_rgfXformOn[iBark])
                {
                    bInd = WMAB_FALSE;
                    goto exit;
                }
            }
        }
    }

exit:
    return bInd;
}

Void freqexSetBandParams( CAudioObject   * const pau,
                    const PerChannelInfo * const ppcinfo,
                    const Int iChCode    , const Int iBand )
{
    Fex * const pfx = &(pau->m_fex);
    const PerChannelInfoShr * const pcis = pau->m_rgpcinfoShr + pfx->m_iChSrc;

    Int iStartPos, iEndPos, iBark;

    pfx->m_iBand = iBand;

    pfx->m_bChannelIndependent =
      (pcis->m_iFxChannelDependencyGroup==-1 ? WMAB_TRUE : WMAB_FALSE);

    // check to see if coding is independent for this fex band
    if (WMAB_FALSE == pfx->m_bChannelIndependent &&
        WMAB_FALSE == pfx->m_bReconDomain &&
        1 == pfx->m_iVersion)
    {
        iStartPos = pfx->m_cStartIndex;
        iEndPos = iStartPos + pfx->m_cBandSize;
        if (pfx->m_bSplitTileIntoSubtiles)
        {
            iStartPos *= 2;
            iEndPos *= 2;
        }
        // find starting/ending bark index
        iBark = 0;
        while (iStartPos >= pau->m_rgiBarkIndex[iBark+1])
            iBark++;
        iStartPos = iBark;
        iBark = 0;
        while (iEndPos-1 >= pau->m_rgiBarkIndex[iBark+1])
            iBark++;
        iEndPos = iBark + 1;

        pfx->m_bChannelIndependent = freqexIsBarkInd(pau, iStartPos, iEndPos);
    }

    if (pfx->m_cStartIndex < pfx->m_iMaxLastCodedIndex ||
        (WMAB_TRUE==pfx->m_bSplitTileIntoSubtiles &&
         pfx->m_cStartIndex==pfx->m_iMaxLastCodedIndex))
        pfx->m_bOverlayUsedForBand = WMAB_TRUE;
    else
        pfx->m_bOverlayUsedForBand = WMAB_FALSE;

    if (WMAB_TRUE == pfx->m_bReconDomain)
        pfx->m_bOverlayUsedForBand = WMAB_FALSE;

    if (iBand < pfx->m_cHoleBands)
        pfx->m_bOverlayUsedForBand = WMAB_FALSE;

    if ((pfx->m_bOverlayUsedForBand || pfx->m_bEntireHoleOverlay) &&
        pfx->m_iVersion >= 2)
        freqexProcessZeroMaskXChannel(pau);

    freqexSetGroup(pau, pfx->m_iChSrc, pfx->m_bChannelIndependent,
                   pfx->m_bSplitTileIntoSubtiles);

    if (pfx->m_bOverlayUsedForBand)
        freqexProcessValidMask(pau, pau->m_iChGroup);
}

// =====================================================================
WMARESULT freqexSwitchFexDomain( CAudioObject *pau, Bool bRecon )
{
    Fex *pfx = &(pau->m_fex);
    Int iCh;

    if( pfx->m_iVersion == 1 )
        return WMA_OK;

    if( bRecon == WMAB_TRUE )
    {
        // go to recon domain
        pfx->m_bReconDomain = WMAB_TRUE;
    }
    else
    {
        // go to coding parameters
        pfx->m_bReconDomain = WMAB_FALSE;

        pfx->m_prtiCurr = NULL;
        if (pfx->m_rgprtiMvAnchor)
        {
            for( iCh = 0; iCh < pau->m_cChannel; iCh++ )
                if (pau->m_rgpcinfo[iCh].m_bFex)
                    pfx->m_rgprtiMvAnchor[iCh] = NULL;
        }
    }

    return WMA_OK;
}

// =====================================================================

Void freqexDumpConfig(CAudioObject *pau, Fex *pfx, Int iSubframe)
{
#ifdef FEX_DBG_PRINT
    Int i;
    Bool bAnyUseNoiseFloor=0, bAnyUseExplicitPos=0, bAnyUseImplicit=0;
    PerChannelInfoShr *pcis = pau->m_rgpcinfoShr + pfx->m_iChSrc;

    fxprintf(("====================\n"));
    fxprintf(("FRAME=%d SUBFRAME=%d SIZE=%d\n",
              pau->m_bEncoder ? pau->m_iFrameNumber-1:pau->m_iFrameNumber,
              iSubframe,
              pfx->m_cSubFrameSampleHalf));
    if (1==pfx->m_iVersion)
        fxprintf(("QBW=%d BW=%d EP=%d\n", freqexQuantBw(pau, pfx, pfx->m_iMaxFreq),
                  pfx->m_iMaxFreq, pfx->m_cOrigEnd));
    fxprintf(("SMV=%d\n", pfx->m_bUseSingleMv));
    fxprintf(("SPLIT=%d\n", pfx->m_bSplitTileIntoSubtiles));
    fxprintf(("SCBINS=%d\n", pfx->m_cScaleBins));
    fxprintf(("MVBINS=%d\n", pfx->m_cMvBins));
    for (i=0; i < pfx->m_iNumMvChannels; i++)
    {
        fxprintf(("USEEXP[%d]=%d\n", i, pcis->m_bFxUseExponent));
        fxprintf(("USENF[%d]=%d\n", i, pcis->m_bFxUseNoiseFloor));
        fxprintf(("USESIGN[%d]=%d\n", i, pcis->m_bFxUseSign));
        fxprintf(("USEIMPLICITSTARTPOS[%d]=%d\n",
                  i, pcis->m_bFxUseImplicitStartPos));
        bAnyUseNoiseFloor |= pcis->m_bFxUseNoiseFloor;
        bAnyUseExplicitPos |= !pcis->m_bFxUseImplicitStartPos;
        bAnyUseImplicit |= pcis->m_bFxUseImplicitStartPos;
    }
    if (WMAB_TRUE==bAnyUseImplicit && WMAB_FALSE==pfx->m_bMvRangeFull)
        fxprintf(("OVERLAY=%d\n", pfx->m_bOverlay));
    else
        fxprintf(("OVERLAYNOTCODED\n"));
    if (bAnyUseNoiseFloor)
    {
        fxprintf(("USERANDMV2=%d\n", pcis->m_bFxUseRandomMv2));
        fxprintf(("NFTHRESH=%d\n", pcis->m_iFxNoiseFloorThresh));
    }
    else
    {
        fxprintf(("NOISEFLOORPARAMSNOTCODED\n"));
    }
    fxprintf(("MVRANGETYPE=%d\n", pcis->m_eFxMvRangeType));
    fxprintf(("MVPREDLOWBAND=%d\n", pfx->m_bUseMvPredLowband));
    fxprintf(("MVPREDNOISE=%d\n", pfx->m_bUseMvPredNoise));
    //fxprintf(("MVRESTYPE=%d\n", pfx->m_rgiMvResType[0]));
    if (WMAB_TRUE==bAnyUseExplicitPos ||
        WMAB_TRUE==pfx->m_bOverlay ||
        MvRangeFullNoOverwriteBase==pcis->m_eFxMvRangeType)
        fxprintf(("MINRUNOFZEROSFOROVERLAY=%d\n",
                  pfx->m_cMinRunOfZerosForOverlay));
    else
        fxprintf(("MINRUNOFZEROSFOROVERLAYNOTCODED\n"));
    fxprintf(("IMPLPOS=%d ",
              pfx->m_bMvRangeFull ? 0 : pau->m_cLastCodedIndex));
    if (bAnyUseExplicitPos)
        fxprintf(("EXPLICITQSP=%d EXPLICITSP=%d\n",
                  freqexQuantStartPos(pau, pfx, pfx->m_iExplicitStartPos),
                  pfx->m_iExplicitStartPos));
    else
        fxprintf(("EXPLICITPOSNOTCODED\n"));
    fxprintf(("====================\n"));
#endif
}

// during decoding of band config's
Void freqexDumpBandConfigCfg(Fex *pfx, Int iConfig,
                             PerChannelInfoShr *pcis)
{
#ifdef FEX_DBG_PRINT
    Int j;

    fxprintf(("CFG = %d\n", iConfig));
    fxprintf(("CFGBANDS = %d\n", pcis->m_iFxScaleBands));
    fxprintf(("UNIFORM = %d\n", pcis->m_bFxUseUniformBands));
    fxprintf(("ARBITRARY = %d\n", pcis->m_bFxArbitraryBandConfig));
    if (pcis->m_bFxArbitraryBandConfig)
    {
        fxprintf(("MINRATIOBANDM = %d\n", pfx->m_iMinRatioBandSizeM));
        fxprintf(("EXPBANDM = "));
        for (j=0; j < pcis->m_iFxScaleBands; j++)
            fxprintf(("%3d ", pfx->m_rgiExpBandSizeM[j]));
        fxprintf(("\n"));

        fxprintf(("BANDM = "));
        for (j=0; j < pcis->m_iFxScaleBands; j++)
            fxprintf(("%3d ", pfx->m_piBandSizeM[j]));
        fxprintf(("\n"));
    }
#endif
}

// after computing band sizes for each channel
Void freqexDumpBandConfig(Fex *pfx)
{
#ifdef FEX_DBG_PRINT
    Int i, j, iConfig=0;
    PerChannelInfoShr *pcis = pfx->m_pau->m_rgpcinfoShr + pfx->m_iChSrc;

    i = pfx->m_iChCode;
    iConfig = pcis->m_iFxBandConfig;

    fxprintf(("CFG[%d]=%d\n", i, iConfig));
    fxprintf(("CFGBANDS[%d]=%d\n", i, pfx->m_cScaleBands));
    fxprintf(("UNIFORMBANDS[%d]=%d\n",
              i, pcis->m_bFxUseUniformBands));
    fxprintf(("ARBITRARYBANDS[%d]=%d\n",
              i, pcis->m_bFxArbitraryBandConfig));
    fxprintf(("START=%d END=%d\n", pfx->m_cStart, pfx->m_cEnd));

    if (pcis->m_bFxArbitraryBandConfig)
    {
        fxprintf(("BANDM[%d]=", i));
        for (j=0; j < pfx->m_cScaleBands; j++)
            fxprintf(("%3d ", pfx->m_piBandSizeM[j]));
        fxprintf(("\n"));
    }

    fxprintf(("BANDSIZES[%d]=", i));
    for (j=0; j < pfx->m_cScaleBands; j++)
    {
        fxprintf(("%3d ", pfx->m_piScaleBandSizes[j]));
        assert(pfx->m_piScaleBandSizes[j] == pfx->m_piMvBandSizes[j]);
    }
    fxprintf(("\n"));
#endif
}

// =========================================================================

// does not work for multiple recon tiles with differing channel configs
// for that we will have to have separate vars for each tile.
Bool freqexReconTileCoded(CAudioObject *pau)
{
    Fex *pfx = &pau->m_fex;
    Int iCh, iChCode=0;
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti = prp->m_rgchextiBuf + prp->m_iBufCodeFxPos;
    PerChannelInfo *ppcinfo;
    PerChannelInfoShr *pcis;

    if (prp->m_iTilesInSubframeCodeFx==0)
        return WMAB_FALSE;

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        assert(prti->m_uChannelMask == (U32)((1<<pau->m_cChannel)-1));

        if (!(prti->m_uChannelMask & (1<<iCh)))
            continue;

        ppcinfo = pau->m_rgpcinfo + iCh;
        pcis = ppcinfo->m_ppcinfoShr;

        // which channels upon channel iCh is depenedent
        pcis->m_uFxChannelDependencyMask = prti->m_uChannelMask;
        // which channel groups this channel belongs to
        pcis->m_uFxChannelGroupMask = 0;
        // which channel dependency group this channel belongs to
        pcis->m_iFxChannelDependencyGroup = 0; // setting to 0 means not ind
       
        ppcinfo->m_bFex = WMAB_FALSE;
        
        if (iCh == pau->m_nSubWooferChannel)
            continue;

        pfx->m_rgiChCode[iChCode] = iCh;

        iChCode++;

        ppcinfo->m_bFex = WMAB_TRUE;
    }
    pfx->m_nChCode = iChCode;
    pfx->m_bHasPower = (pfx->m_nChCode != 0);

    return (0 != iChCode && 0 != prp->m_iTilesInSubframeCodeFx);
}

Bool freqexTileCoded(CAudioObject *pau)
{
    Fex *pfx = &pau->m_fex;
    PerChannelInfo *ppcinfo;
    Int iChCode, iCh, iChSrc;
    Bool bSkipAll;

    iChCode = 0;
    bSkipAll = WMAB_TRUE;
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc     = pau->m_rgiChInTile[iCh];
        ppcinfo    = pau->m_rgpcinfo + iChSrc;

        freqexSetChannelDependencies(pau, pau->m_rgChannelGrpInfo,
                                     pau->m_cChannelGroup, iChSrc);

        ppcinfo->m_bFex = WMAB_FALSE;

        if (WMAB_FALSE == freqexNeedChCode(pau, ppcinfo, iChSrc))
        {
            //assert(iChSrc==pau->m_nSubWooferChannel || ppcinfo->m_iPower==0);
            continue;
        }

        pfx->m_rgiChCode[iChCode] = iChSrc;

        ppcinfo->m_bFex = WMAB_TRUE;

        iChCode++;
        if (ppcinfo->m_iPower != 0 || 0 == pfx->m_iIteration)
            bSkipAll= WMAB_FALSE;
    }
    pfx->m_nChCode = iChCode;
    pfx->m_bHasPower = !bSkipAll;

    return (0 != iChCode);
}

// =========================================================================

#define NOPTBITS(opt, offset) (LOG2((opt>>offset)+1))
#define NOPTBINS(opt, offset) ((opt>>offset)+1)
#define FEXOPT_MVBINS NOPTBINS(ENCOPT4_FEXMVBINS, ENCOPT4_FEXMVBINS_BITSOFFSET)
#define FEXOPT_SCBINS NOPTBINS(ENCOPT4_FEXSCBINS, ENCOPT4_FEXSCBINS_BITSOFFSET)
#define FEXOPT_MAXBANDBINS NOPTBINS(ENCOPT4_FEXMAXBANDS, ENCOPT4_FEXMAXBANDS_BITSOFFSET)

Int freqexMvBinsToIndex(Int iMvBins)
{
    return freqexQuant(LOG2((U32)iMvBins/16), FEXOPT_MVBINS, 0,
                       FEXOPT_MVBINS-1);
}

Int freqexIndexToMvBins(Int iIndex)
{
    return (1<<freqexInvQuantCenter(iIndex, FEXOPT_MVBINS, 0,
                                    FEXOPT_MVBINS-1))*16;
}

Int freqexScaleBinsToIndex(Int iScaleBins)
{
    return freqexQuant(LOG2((U32)iScaleBins/FEX_SCBINSHUFF), FEXOPT_SCBINS, 0,
                       FEXOPT_SCBINS-1);
}

Int freqexIndexToScaleBins(Int iIndex)
{
    return (1<<freqexInvQuantCenter(iIndex, FEXOPT_SCBINS, 0,
                                    FEXOPT_SCBINS-1))*FEX_SCBINSHUFF;
}

Int freqexMaxBandsToIndex(Int iMaxBands)
{
    return freqexQuant(LOG2((U32)iMaxBands/8), FEXOPT_MAXBANDBINS, 0,
                       FEXOPT_MAXBANDBINS-1);
}

Int freqexIndexToMaxBands(Int iIndex)
{
    return (1<<freqexInvQuantCenter(iIndex, FEXOPT_MAXBANDBINS, 0,
                                    FEXOPT_MAXBANDBINS-1))*8;
}

// ===============================================================
// encoder side things only

Int freqexGetMvBins(Int nSamplesPerSec, Int nChannels, Int nBitrate)
{
    return 64;
}

Int freqexGetScaleBins()
{
    return FEX_SCBINSHUFF;
}

Int freqexGetMaxBands()
{
    return 16;
    //return 32;
}

// =====================================================================
#if defined(BUILD_WMAPROLBRV2)

#include "chexpro.h"
#if defined (_DEBUG) || !defined (UNDER_CE)
Void prvDumpMvInfo(CAudioObject *pau, FILE *fp, Int iType)
{
    Int i, j, iCh;
    ReconProc *prp = pau->m_prp;
    ReconTileInfo *prti;
    PerChannelRecon *ppcr;

    if (0 == iType)
    {
        FILE_DUMP_INIT(mvdump);
    }
    else
    {
        FILE_DUMP_INIT(expdump);
    }

    for (iCh=0; iCh < pau->m_cChannel; iCh++)
    {
        prti = prp->m_rgchextiBuf + prp->m_iBufCodeFxPos;
        i = 0;
        while( i < prp->m_iTilesInSubframeProcFx )
        {
            if(!chexInfoStatNoFx(prti->m_uInfoStat))
            {
                if (!(prti->m_uChannelMask & (1<<iCh)))
                    continue;

                ppcr = prti->m_prfxrti->m_rgpcr + iCh;
                for (j=0; j < prti->m_prfxrti->m_cFexMvBands; j++)
                {
                    if (0 == iType)
                        fprintf(fp, "%d ", (int)ppcr->m_rgiFexMv[j]);
                    else if (1 == iType)
                        fprintf(fp, "%f ", (float)ppcr->m_rgFexExp[j]);
                }
                fprintf(fp, "\n");
                i++;
            }
            prti = chexNextTile(prp, prti);
        }
    }
    fprintf(fp, "\n");
}
#endif // _DEBUG

#endif // BUILD_WMAPROLBRV2

#ifdef BUILD_WMAPROLBRV3
Void bpeakFrameInit( CAudioObject *pau )
{
    pau->m_bBasePeakFirstTile = WMAB_TRUE;
}

Void bpeakReset( CAudioObject *pau )
{
    if( pau->m_rgcBasePeakCoefs )
        memset( pau->m_rgcBasePeakCoefs, 0, pau->m_cOrigChannel * sizeof(Int) );
}

Void bpeakResamplePeakPos( PerChannelInfo *ppcinfo,
                           I16            iSizeFrom,
                           I16            iSizeTo )
{
    I16 iFac, iCoef;

    if( iSizeFrom == iSizeTo )
    {
        return;
    }
    else if( iSizeFrom > iSizeTo )
    {
        iFac = iSizeFrom / iSizeTo;
        assert( iFac * iSizeTo == iSizeFrom );

        for( iCoef = 0; iCoef < *(ppcinfo->m_pcBasePeakCoefs); iCoef++ )
            ppcinfo->m_piBasePeakCoefPos[iCoef] /= iFac;
    }
    else
    {
        iFac = iSizeTo / iSizeFrom;
        assert( iFac * iSizeFrom == iSizeTo );

        for( iCoef = 0; iCoef < *(ppcinfo->m_pcBasePeakCoefs); iCoef++ )
            ppcinfo->m_piBasePeakCoefPos[iCoef] *= iFac;
    }
}

Int bpeakGetBasePeakBarkStart( CAudioObject *pau,
                               I16 cLastCodedIndex )
{
    Int iBand;

    for( iBand = pau->m_cValidBarkBand - 1; iBand >= 0; iBand-- )
    {
        if( cLastCodedIndex > pau->m_rgiBarkIndex[iBand]  )
            break;
    }
    return (iBand + 1);
}

Int bpeakGetBasePeakBarkStart_BasePlus( CBasePlusObject *pbp,
                                        I16 cLastCodedIndex )
{
    Int iBand;

    for( iBand = pbp->m_cValidSFBand - 1; iBand >= 0; iBand-- )
    {
        if( cLastCodedIndex > pbp->m_rgiSFBandIndex[iBand]  )
            break;
    }
    return (iBand + 1);
}

WMARESULT bpeakGetShape( Int iIndex, CoefType fCoef, CoefType *pfCoef0, CoefType *pfCoef1 )
{
    *pfCoef0 = *pfCoef1 = fCoef;
    switch( iIndex )
    {
        case 0: *pfCoef1 = 0;             break; // (1,0)
        case 1: *pfCoef1 = -(*pfCoef1);   break; // (1,-1)
        case 2: *pfCoef0 = -(*pfCoef0/2); break; // (-1/2,1)
        case 3: *pfCoef1 = -(*pfCoef1/2); break; // (1,-1/2)
        case 4:                           break; // (1,1)
        case 5: *pfCoef0 = (*pfCoef0/2);  break; // (1/2,1)
        case 6: *pfCoef1 = (*pfCoef1/2);  break; // (1,1/2)
        default: assert( WMAB_FALSE ); return WMA_E_FAIL; break;
    }
    return WMA_OK;
}
#endif
#endif // BUILD_WMAPROLBRV1

