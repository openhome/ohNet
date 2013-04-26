//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

//#define FEX_LOWRATE_DEBUG

#ifdef FEX_LOWRATE_DEBUG
FILE *fplrfex_bitstream=NULL;
#ifdef BUILD_WMAPROLBRV3
char *globalupdatetype[]={"No","Full","List","TileList","Frame","Tile"};
#endif
#endif

// ----- functions from fexdec.c -----
WMARESULT freqexDecodeBandConfig(CAudioObjectDecoder *paudec);
INLINE
WMARESULT freqexDecodeMinRatioBandSizeM(const CAudioObjectDecoder *paudec,
                                        Int *piMinRatioBandSizeM);
INLINE
WMARESULT freqexDecodeBandSizeM(const CAudioObjectDecoder *paudec,
                                const Int *piFexBandSizesM,
                                Int  iMinRatioBandSizeM,
                                Int  *piBandSizeM,
                                Int  bUseUniformBands,
                                UInt *puiExpBandSizeMIndex,
                                Int  *piExpBandSizeM,
                                Int  *piExpBandSizeMTmp,
                                Int  *piMaxBandsTemp,
                                Int  cMaxBands,
                                const Int cBands,
                                Bool *pbArbitraryBandConfig);

WMARESULT freqexDecodeMvBand(CAudioObjectDecoder *paudec,
                             PerChannelInfo *ppcinfo,
                             Int *piMv, Int iCb, Int iBand);
WMARESULT freqexDecodePeakToNoiseScale( const CAudioObjectDecoder *paudec,
                                        const PerChannelInfo *ppcinfo,
                                        const Int iBand,
                                        FastFloat *pfScale);
WMARESULT freqexDecodeAndGetTileConfig(CAudioObjectDecoder *paudec,
                                       Int cSubFrameSampleHalf);
WMARESULT freqexDecodeScale(CAudioObjectDecoder *paudec,
                            PerChannelInfo *ppcinfo, Int iChCode,
                            Int iBand, Int iActLen);
WMARESULT freqexDecodeScaleBand( const CAudioObjectDecoder *paudec,
                                 FastFloat *pfScale, I32 *piLogScaleIndex);
// -----

WMARESULT freqexDecodeFreqV2( CAudioObjectDecoder *paudec,
                              Int    *piFreq )
{
    Int       iKHz, iHz;
    U32       uVal;
    WMARESULT   wmaResult = WMA_OK;

    // KHz
    PLUS_GETBITS( wmaResult, 3, &uVal );
    iKHz = uVal * 1000;
    if( uVal == 7 )
    {
        while( WMAB_TRUE )
        {
            PLUS_GETBITS( wmaResult, 2, &uVal );
            iKHz += uVal * 1000;
            if( uVal < 3 )
                break;
        }
    }

    // Hz
    PLUS_GETBITS( wmaResult, 1, &uVal );
    iHz = 0;
    if( uVal == 1 )
    {
        PLUS_GETBITS( wmaResult, 2, &uVal );
        switch( uVal )
        {
            case 0: iHz = 250; break;
            case 1: iHz = 500; break;
            case 2: iHz = 750; break;
            case 3:
                PLUS_GETBITS( wmaResult, 2, &uVal );
                switch( uVal )
                {
                    case 0: iHz = 125; break;
                    case 1: iHz = 375; break;
                    case 2: iHz = 625; break;
                    case 3: iHz = 875; break;
                    default: wmaResult = WMA_E_FAIL; break;
                }
                break;
            default: wmaResult = WMA_E_FAIL; break;
        }
    }

    *piFreq = iKHz + iHz;

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeNumScMvBands( CAudioObjectDecoder *paudec,
                                      Fex                 *pfx,
                                      FexGlobalParam      *pfxgp )
{
    I32       cMaxBands;
    U32       uVal, iCb;
    WMARESULT wmaResult = WMA_OK;
    const Int (*ppcScMvCb[4])[2], *pcEntriesScMvCb, *pcBitsScMvCb;

    cMaxBands = 1 << (I32)pfx->m_cBandsBits;
    if( cMaxBands == 8 || cMaxBands == 16 )
    {
        if( cMaxBands == 8 )
        {
            ppcScMvCb[0] = g_rgrgcNumScMvBands_8_0;
            ppcScMvCb[1] = g_rgrgcNumScMvBands_8_1;
            ppcScMvCb[2] = g_rgrgcNumScMvBands_8_2;
            ppcScMvCb[3] = g_rgrgcNumScMvBands_8_3;
            pcEntriesScMvCb = g_rgcNumEntriesScMvBands_8;
            pcBitsScMvCb = g_rgcBitsScMvBands_8;
        }
        else if( cMaxBands == 16 )
        {
            ppcScMvCb[0] = g_rgrgcNumScMvBands_16_0;
            ppcScMvCb[1] = g_rgrgcNumScMvBands_16_1;
            ppcScMvCb[2] = g_rgrgcNumScMvBands_16_2;
            ppcScMvCb[3] = g_rgrgcNumScMvBands_16_3;
            pcEntriesScMvCb = g_rgcNumEntriesScMvBands_16;
            pcBitsScMvCb = g_rgcBitsScMvBands_16;
        }
        iCb = 0;
        PLUS_GETBITS( wmaResult, (UInt)pcBitsScMvCb[0], &uVal );
        if( (Int)uVal >= pcEntriesScMvCb[0] )
        {
            // escape decoding
            iCb = (U32)(uVal - pcEntriesScMvCb[0] + 1);
            if( iCb > 3 )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
            PLUS_GETBITS( wmaResult, (UInt)pcBitsScMvCb[iCb], &uVal );
        }
        if( (Int)uVal >= pcEntriesScMvCb[iCb] )
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        pfxgp->m_cScaleBands = ppcScMvCb[iCb][uVal][0];
        pfxgp->m_cMvBands    = ppcScMvCb[iCb][uVal][1];
    }
    else
    {
        PLUS_GETBITS( wmaResult, (UInt)pfx->m_cBandsBits, &uVal );
        pfxgp->m_cScaleBands = uVal + 1;
        pfxgp->m_cMvBands = pfxgp->m_cScaleBands;
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeArbitraryUniformBandConfig( CAudioObjectDecoder *paudec,
                                                    Fex                 *pfx,
                                                    FexGlobalParam      *pfxgp )
{
    Int       cBands;
    U32       uVal;
    WMARESULT wmaResult = WMA_OK;

    // uniform bandsplit
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bUseUniformScaleBands = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    // arbitrary bandsplit
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bArbitraryScaleBandConfig = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    // #ScBands
    if( pfxgp->m_bUseUniformScaleBands || pfxgp->m_bArbitraryScaleBandConfig )
    {
        PLUS_GETBITS( wmaResult, (UInt)(pfx->m_cBandsBits + 1), &uVal );
    }
    else
    {
        PLUS_GETBITS( wmaResult, (UInt)pfx->m_cBandsBits, &uVal );
    }
    cBands = uVal + 1;

    if( pfxgp->m_bArbitraryScaleBandConfig )
    {
        Bool bArbitraryScaleBandConfig;

        TRACEWMA_EXIT(wmaResult, freqexDecodeMinRatioBandSizeM( paudec, &pfxgp->m_iMinRatioBandSizeM ));
        TRACEWMA_EXIT(wmaResult, 
        freqexDecodeBandSizeM( paudec,
                               freqexSetBandSizeM( pfxgp->m_bScaleBandSplitV2 ),
                               pfxgp->m_iMinRatioBandSizeM,
                               pfxgp->m_piBandSizeM,
                               pfxgp->m_bUseUniformScaleBands,
                               &pfx->m_uiExpBandSizeMIndex,
                               &pfx->m_iExpBandSizeM,
                               pfx->m_rgiExpBandSizeM,
                               pfx->m_rgiMaxBandsTemp,
                               pfx->m_cMaxBands,
                               cBands,
                               &bArbitraryScaleBandConfig ));
        // ignore the result of bArbitraryScaleBandConfig 
        // even if it doesn't match with pfxgp->m_bArbitraryScaleBandConfig
    }
    pfxgp->m_cScaleBands = cBands;
    pfxgp->m_cMvBands    = cBands;

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconGrpA( CAudioObjectDecoder *paudec,
                                   Fex                 *pfx,
                                   FexGlobalParam      *pfxgp )
{
    U32          uVal;
    WMARESULT    wmaResult = WMA_OK;

    // band split
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bScaleBandSplitV2 = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

    // band configurations
    pfxgp->m_bUseUniformScaleBands     = WMAB_FALSE;
    pfxgp->m_bArbitraryScaleBandConfig = WMAB_FALSE;
    PLUS_GETBITS( wmaResult, 1, &uVal );
    if( uVal == 0 )
    {
        TRACEWMA_EXIT( wmaResult, freqexDecodeNumScMvBands( paudec, pfx, pfxgp ) );
    }
    else
    {
        TRACEWMA_EXIT( wmaResult, freqexDecodeArbitraryUniformBandConfig( paudec, pfx, pfxgp ) );
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconGrpB( CAudioObjectDecoder *paudec,
                                   Fex                 *pfx,
                                   FexGlobalParam      *pfxgp )
{
    U32         uVal;
    WMARESULT   wmaResult = WMA_OK;
    Bool        bArbitraryOrUniformScaleBands = WMAB_FALSE;

    PLUS_GETBITS( wmaResult, 1, &uVal );
    if( uVal == 0 )
    {
        pfxgp->m_cBaseBands = 0;
    }
    else
    {
        // base split
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bBaseBandSplitV2 = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        // #BaseBands
        PLUS_GETBITS( wmaResult, (UInt)pfx->m_cBandsBits, &uVal );
        pfxgp->m_cBaseBands = uVal + 1;
        // end base freq
        TRACEWMA_EXIT( wmaResult, freqexDecodeFreqV2( paudec, &pfxgp->m_iMaxBaseFreq ) );
        // base step size
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_iBaseFacStepSize = (uVal == 0) ? 1 : 3;
    }

    // start fex freq
    TRACEWMA_EXIT( wmaResult, freqexDecodeFreqV2( paudec, &pfxgp->m_iMinFreq ) );

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconGrpC( CAudioObjectDecoder *paudec,
                                   Fex                 *pfx,
                                   FexGlobalParam      *pfxgp )
{
    U32         uVal;
    Int         iMv;
    WMARESULT   wmaResult = WMA_OK;

    // Scale factor stepsize
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_iScFacStepSize = (uVal == 0) ? 1 : 3;
    // MvBins multiplier
    PLUS_GETBITS( wmaResult, 3, &uVal );
    pfxgp->m_iMvBinsIndex = (Int)uVal;
    // MvCodebook
    if( pfxgp->m_iMvCodebookSet == 0 )
    {
        pfxgp->m_iMvCodebook = -1;
        PLUS_GETBITS( wmaResult, 1, &uVal );    // noise floor
        pfxgp->m_bEnableNoiseFloor = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        PLUS_GETBITS( wmaResult, 1, &uVal );    // exponent
        pfxgp->m_bEnableExponent = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        PLUS_GETBITS( wmaResult, 1, &uVal );    // sign
        pfxgp->m_bEnableSign = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        PLUS_GETBITS( wmaResult, 1, &uVal );    // reverse
        pfxgp->m_bEnableReverse = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }
    else
    {
        PLUS_GETBITS( wmaResult, 2, &uVal );
        if( uVal == 3 )
        {
            if( pfxgp->m_iMvCodebookSet == 1 )
            {
                PLUS_GETBITS( wmaResult, 2, &uVal );
                uVal += 12;
            }
            else
            {
                PLUS_GETBITS( wmaResult, 3, &uVal );
                uVal += 24;
            }
        }
        for( iMv = 0; iMv < g_cNumMvCodebooks; iMv++ )
        {
            if( (pfxgp->m_iMvCodebookSet == 1 && g_rgMvCodebook[iMv].m_iIndexWithNoiseFloor == (Int)uVal) ||
                (pfxgp->m_iMvCodebookSet == 2 && g_rgMvCodebook[iMv].m_iIndexWithoutNoiseFloor == (Int)uVal) )
                break;
        }
        if( iMv == g_cNumMvCodebooks )
        {
            wmaResult = WMA_E_FAIL;
            goto exit;
        }
        pfxgp->m_iMvCodebook = iMv;
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconGrpD( CAudioObjectDecoder *paudec,
                                   Fex                 *pfx,
                                   FexGlobalParam      *pfxgp )
{
    CAudioObject *pau = paudec->pau;
    U32          uVal;
    Int        iDiff;
    WMARESULT    wmaResult = WMA_OK;

    // Mv recursive
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bRecursiveCwGeneration = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    // Mv recursive width
    if( pfxgp->m_bRecursiveCwGeneration )
    {
        PLUS_GETBITS( wmaResult, 2, &uVal );
        pfxgp->m_iKHzRecursiveCwWidth = uVal + 1;
    }
    // Mv range type
    PLUS_GETBITS( wmaResult, 2, &uVal );
    pfxgp->m_iMvRangeType = uVal;
    // Mv resolution type
    PLUS_GETBITS( wmaResult, 2, &uVal );
    pfxgp->m_iMvResType = uVal;
    // Codebook set
    PLUS_GETBITS( wmaResult, 1, &uVal );
    if( uVal == 0 )
    {
        pfxgp->m_iMvCodebookSet = 0;
    }
    else
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
            pfxgp->m_iMvCodebookSet = 1;
        else
            pfxgp->m_iMvCodebookSet = 2;
    }

    if( pfxgp->m_iMvCodebookSet == 0 || pfxgp->m_iMvCodebookSet == 1 )
    {
        // random noise
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bUseRandomNoise = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        // noise floor threshold
        PLUS_GETBITS( wmaResult, 2, &uVal );
        pfxgp->m_iNoiseFloorThresh = uVal;
    }
    // fex end pos
    iDiff = 0;
    while( WMAB_TRUE )
    {
        PLUS_GETBITS( wmaResult, 2, &uVal );
        if( uVal < 3 )
        {
            iDiff += uVal;
            break;
        }
        else
        {
            iDiff += 3;
        }
    }
    pfxgp->m_iMaxFreq = freqexInvQuantBwV2( pau, iDiff );
    if( pfxgp->m_iMaxFreq <= 0 )
    {
        wmaResult = WMA_E_FAIL;
        goto exit;
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconUpdateGrp( CAudioObjectDecoder *paudec,
                                        Bool                *pfUpdateGrpA,
                                        Bool                *pfUpdateGrpB,
                                        Bool                *pfUpdateGrpC,
                                        Bool                *pfUpdateGrpD )
{
    CAudioObject *pau = paudec->pau;
    U32          uVal;
    WMARESULT    wmaResult = WMA_OK;

    // find out which Groups are updated
    PLUS_GETBITS( wmaResult, 2, &uVal );

    // 00: Full     100: B
    // 01: A        101: C
    //              110: A+B
    //              111: A+B+C
    if( uVal == 0 )
        *pfUpdateGrpA =  *pfUpdateGrpB = *pfUpdateGrpC = *pfUpdateGrpD = WMAB_TRUE;
    else if( uVal == 1 )
        *pfUpdateGrpA = WMAB_TRUE;
    else if( uVal == 2 )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );

        if( uVal == 0 )
            *pfUpdateGrpB = WMAB_TRUE;
        else
            *pfUpdateGrpC = WMAB_TRUE;
    }
    else if( uVal == 3 )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );

        if( uVal == 0 )
            *pfUpdateGrpA = *pfUpdateGrpB = WMAB_TRUE;
        else
            *pfUpdateGrpA = *pfUpdateGrpB = *pfUpdateGrpC = WMAB_TRUE;
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconGlobalParam( CAudioObjectDecoder *paudec,
                                          Bool                fUpdateGrpA,
                                          Bool                fUpdateGrpB,
                                          Bool                fUpdateGrpC,
                                          Bool                fUpdateGrpD )
{
    CAudioObject   *pau = paudec->pau;
    Fex            *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    WMARESULT      wmaResult = WMA_OK;

    if( fUpdateGrpD )
        TRACEWMA_EXIT( wmaResult, freqexDecodeReconGrpD( paudec, pfx, pfxgp ) );
    if( fUpdateGrpA )
        TRACEWMA_EXIT( wmaResult, freqexDecodeReconGrpA( paudec, pfx, pfxgp ) );
    if( fUpdateGrpB )
        TRACEWMA_EXIT( wmaResult, freqexDecodeReconGrpB( paudec, pfx, pfxgp ) );
    if( fUpdateGrpC )
        TRACEWMA_EXIT( wmaResult, freqexDecodeReconGrpC( paudec, pfx, pfxgp ) );

exit:
    return wmaResult;
}

Void freqexGetReconTileConfigV2( CAudioObjectDecoder *paudec,
                                 Int cSubFrameSampleHalf )
{
    CAudioObject *pau = paudec->pau;
    Fex          *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    PerChannelInfo *ppcinfo;
    PerChannelInfoShr *pcis;
    Int          i, iChSrc, iChCode;

    // parameter setting
    pfx->m_cSubtiles = 1;
    pfx->m_cSubFrameSampleHalf = cSubFrameSampleHalf;
    pfx->m_cTileSize = pfx->m_cSubFrameSampleHalf;
    pfx->m_cStart = (2 * pfxgp->m_iMinFreq * pfx->m_cSubFrameSampleHalf /
                     pau->m_iSamplingRate);
    pfx->m_cOrigEnd = pfx->m_cEnd;
    pfx->m_bV1Compatible = WMAB_FALSE;
    pfx->m_bOverlayOnly = WMAB_FALSE;

    for (i=0; i < pfx->m_nChCode; i++)
    {
        iChCode = pfx->m_rgiChCode[i];
        pcis = pau->m_rgpcinfoShr + iChCode;
        pcis->m_iFxBandConfig = 0;
    }

    for (i=0; i < pau->m_cChInTile; i++)
    {
        iChSrc = pau->m_rgiChInTile[i];
        ppcinfo = pau->m_rgpcinfo + iChSrc;
        // this will be propagated to pfx->m_iMaxLastCodedIndex
        ppcinfo->m_cLastCodedIndex = (U16)pfx->m_cStart;
    }
    pau->m_cLastCodedIndex = (U16)pfx->m_cStart;
}

WMARESULT   freqexDecodeReconTileConfigV2( CAudioObjectDecoder *paudec )
{
    CAudioObject *pau = paudec->pau;
    Fex          *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    Int          i, iMinFreqDiff;
    U32          uVal;
    Bool         fUpdateGrpA, fUpdateGrpB, fUpdateGrpC, fUpdateGrpD;
    WMARESULT    wmaResult = WMA_OK;

    fUpdateGrpA = fUpdateGrpB = fUpdateGrpC = fUpdateGrpD = WMAB_FALSE;

    // GlobalParam update
    PLUS_GETBITS( wmaResult, 1, &uVal );

    if( uVal == 1 )
    {
        TRACEWMA_EXIT( wmaResult, 
            freqexDecodeReconUpdateGrp( paudec, &fUpdateGrpA, &fUpdateGrpB, &fUpdateGrpC, &fUpdateGrpD ) );
        TRACEWMA_EXIT( wmaResult, 
            freqexDecodeReconGlobalParam( paudec, fUpdateGrpA, fUpdateGrpB, fUpdateGrpC, fUpdateGrpD ) );
    }

    if( pfxgp->m_cScaleBands + pfxgp->m_cBaseBands > pfx->m_cMaxBands )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
    }

    if( !fUpdateGrpB )
    {
        iMinFreqDiff = 0;

        // min freq diff
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 1 )
        {
            // abs value
            PLUS_GETBITS( wmaResult, 2, &uVal );
            switch( uVal )
            {
                case 0:  iMinFreqDiff =  125; break;
                case 1:  iMinFreqDiff =  250; break;
                case 2:  iMinFreqDiff =  500; break;
                case 3:  iMinFreqDiff = 1000; break;
                default: TRACEWMA_EXIT( wmaResult, WMA_E_FAIL ); break;
            }
            // sign
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 1 )
                iMinFreqDiff = -iMinFreqDiff;
        }
        pfxgp->m_iMinFreq += iMinFreqDiff;
    }

    if( pfxgp->m_iMinFreq < 0 )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
    }

    if( pfx->m_nChCode > 1 )
    {
        // single mv
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfx->m_bUseSingleMv = (uVal == 1) ? 1 : 0;
    }

    for (i=0; i < pau->m_cChInTile; i++)
        *(pau->m_rgpcinfo[pau->m_rgiChInTile[i]].m_pcFexSubframesMvMerged) = 0;

#ifdef FEX_LOWRATE_DEBUG
        if(fplrfex_bitstream==NULL)fplrfex_bitstream=fopen("debuglrfexdecbit.txt","wb");
        if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n\nFrame=%d Subframe=%d",pau->m_iFrameNumber,pau->m_iCurrTile);fflush(fplrfex_bitstream);}
        if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n rFrameGrobalParam:    A%d B%d C%d D%d",fUpdateGrpA,fUpdateGrpB,fUpdateGrpC,fUpdateGrpD);fflush(fplrfex_bitstream);}
#endif

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeCodingGrpA( CAudioObjectDecoder *paudec,
                                    Fex                 *pfx,
                                    FexGlobalParam      *pfxgp )
{
    CAudioObject *pau = paudec->pau;
    U32          uVal;
    WMARESULT    wmaResult = WMA_OK;

    // scale split
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bScaleBandSplitV2 = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

    // band configurations
    pfxgp->m_bNoArbitraryUniformConfig = WMAB_FALSE;
    PLUS_GETBITS( wmaResult, 1, &uVal );
    if( uVal == 0 )
        pfxgp->m_bNoArbitraryUniformConfig = WMAB_TRUE;

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeCodingGrpB( CAudioObjectDecoder *paudec,
                                    Fex                 *pfx,
                                    FexGlobalParam      *pfxgp )
{
    CAudioObject *pau = paudec->pau;
    U32          uVal;
    WMARESULT    wmaResult = WMA_OK;

    // flag to specify implicit/exlicit start position
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bUseImplicitStartPos = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

    if( pfxgp->m_bUseImplicitStartPos )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bOverlay = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }
    else
    {
        // start fex freq
        TRACEWMA_EXIT( wmaResult, freqexDecodeFreqV2( paudec, &pfxgp->m_iMinFreq ) );
    }

    if( pfxgp->m_bUseImplicitStartPos == WMAB_FALSE || pfxgp->m_bOverlay == WMAB_TRUE )
    {
        // encode min # of zeros for overlay
        PLUS_GETBITS( wmaResult, 2, &uVal );
        pfxgp->m_cMinRunOfZerosForOverlayIndex = uVal;
    }

exit:
    return wmaResult;
}

INLINE
WMARESULT   freqexDecodeCodingGrpC( CAudioObjectDecoder *paudec,
                                    Fex                 *pfx,
                                    FexGlobalParam      *pfxgp )
{
    U32       uVal;
    WMARESULT wmaResult = WMA_OK;

    if( pfxgp->m_bEnableV1Compatible )
    {
        PLUS_GETBITS( wmaResult, 3, &uVal );
        pfxgp->m_iScBinsIndex = (Int)uVal;
    }

    TRACEWMA_EXIT( wmaResult, freqexDecodeReconGrpC( paudec, pfx, pfxgp ) );
exit:
    return wmaResult;
}

INLINE
WMARESULT   freqexDecodeCodingGrpD( CAudioObjectDecoder *paudec,
                                    Fex                 *pfx,
                                    FexGlobalParam      *pfxgp )
{
    U32       uVal;
    WMARESULT wmaResult = WMA_OK;

    // v1 compatible switch
    PLUS_GETBITS( wmaResult, 1, &uVal );
    pfxgp->m_bEnableV1Compatible = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

    TRACEWMA_EXIT( wmaResult, freqexDecodeReconGrpD( paudec, pfx, pfxgp ) );
exit:
    return wmaResult;
}

INLINE
WMARESULT   freqexDecodeCodingUpdateGrp( CAudioObjectDecoder *paudec,
                                         Bool                *pfUpdateGrpA,
                                         Bool                *pfUpdateGrpB,
                                         Bool                *pfUpdateGrpC,
                                         Bool                *pfUpdateGrpD )
{
    return freqexDecodeReconUpdateGrp( paudec, pfUpdateGrpA, pfUpdateGrpB, pfUpdateGrpC, pfUpdateGrpD );
}

WMARESULT   freqexDecodeCodingGlobalParam( CAudioObjectDecoder *paudec,
                                           Bool                fUpdateGrpA,
                                           Bool                fUpdateGrpB,
                                           Bool                fUpdateGrpC,
                                           Bool                fUpdateGrpD )
{
    CAudioObject   *pau = paudec->pau;
    Fex            *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);
    WMARESULT      wmaResult = WMA_OK;

    if( fUpdateGrpD )
        TRACEWMA_EXIT( wmaResult, freqexDecodeCodingGrpD( paudec, pfx, pfxgp ) );
    if( fUpdateGrpA )
        TRACEWMA_EXIT( wmaResult, freqexDecodeCodingGrpA( paudec, pfx, pfxgp ) );
    if( fUpdateGrpB )
        TRACEWMA_EXIT( wmaResult, freqexDecodeCodingGrpB( paudec, pfx, pfxgp ) );
    if( fUpdateGrpC )
        TRACEWMA_EXIT( wmaResult, freqexDecodeCodingGrpC( paudec, pfx, pfxgp ) );

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeMvCbSet0( CAudioObjectDecoder *paudec,
                                  Fex                 *pfx,
                                  FexGlobalParam      *pfxgp )
{
    CAudioObject *pau = paudec->pau;
    Int       i;
    U32       uVal;
    WMARESULT wmaResult = WMA_OK;
    PerChannelInfoShr *pcis, *pcis0;

    if( pfxgp->m_iMvCodebookSet != 0 )
        goto exit;

    pcis0 = pau->m_rgpcinfoShr + pfx->m_rgiChCode[0];

    pcis0->m_bFxUseNoiseFloor = WMAB_FALSE;
    pcis0->m_bFxUseExponent = WMAB_FALSE;
    pcis0->m_bFxUseSign = WMAB_FALSE;
    pcis0->m_bFxUseReverse = WMAB_FALSE;

    if( pfxgp->m_bEnableNoiseFloor )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pcis0->m_bFxUseNoiseFloor = (uVal == 1) ? 1 : 0;
    }
    if( pfxgp->m_bEnableExponent )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pcis0->m_bFxUseExponent = (uVal == 1) ? 1 : 0;
    }
    if( pfxgp->m_bEnableSign )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pcis0->m_bFxUseSign = (uVal == 1) ? 1 : 0;
    }
    if( pfxgp->m_bEnableReverse )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pcis0->m_bFxUseReverse = (uVal == 1) ? 1 : 0;
    }
    for (i=1; i < pfx->m_nChCode; i++)
    {
        pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

        pcis->m_bFxUseExponent = pcis0->m_bFxUseExponent;
        pcis->m_bFxUseSign = pcis0->m_bFxUseSign;
        pcis->m_bFxUseNoiseFloor = pcis0->m_bFxUseNoiseFloor;
        pcis->m_bFxUseReverse = pcis0->m_bFxUseReverse;
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeAndGetCodingTileConfigV2( CAudioObjectDecoder *paudec,
                                                  Int cSubFrameSampleHalf )
{
    CAudioObject *pau = paudec->pau;
    Fex          *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);
    Int        i;
    U32          uVal;
    Bool         fUpdateGrpA, fUpdateGrpB, fUpdateGrpC, fUpdateGrpD;
    PerChannelInfoShr *pcis;
    WMARESULT    wmaResult = WMA_OK;

    fUpdateGrpA = fUpdateGrpB = fUpdateGrpC = fUpdateGrpD = WMAB_FALSE;

#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream==NULL)fplrfex_bitstream=fopen("debuglrfexdecbit.txt","wb");
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n\nFrame=%d Subframe=%d",pau->m_iFrameNumber,pau->m_iCurrTile);fflush(fplrfex_bitstream);}
#endif

    uVal = 0;
    if( pfx->m_bFirstTileV2Coding )
    {
        // GlobalParam update
        PLUS_GETBITS( wmaResult, 1, &uVal );

        if( uVal == 1 )
        {
            TRACEWMA_EXIT( wmaResult, 
                freqexDecodeCodingUpdateGrp( paudec, &fUpdateGrpA, &fUpdateGrpB, &fUpdateGrpC, &fUpdateGrpD ) );
            TRACEWMA_EXIT( wmaResult, 
                freqexDecodeCodingGlobalParam( paudec, fUpdateGrpA, fUpdateGrpB, fUpdateGrpC, fUpdateGrpD ) );
        }

#ifdef FEX_LOWRATE_DEBUG
        if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n cFrameGrobalParam:    A%d B%d C%d D%d",fUpdateGrpA,fUpdateGrpB,fUpdateGrpC,fUpdateGrpD);fflush(fplrfex_bitstream);}
#endif

        pfx->m_bFirstTileV2Coding = WMAB_FALSE;

        pfx->m_bV1Compatible = WMAB_FALSE;
        if( pfxgp->m_bEnableV1Compatible )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfx->m_bV1Compatible = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            if( pfx->m_bV1Compatible )
            {
                pfx->m_cScaleDefaultBins = freqexIndexToScaleBins( pfxgp->m_iScBinsIndex );
                pfx->m_iPrevScBinsMultiplier = 0;
                freqexSetScBins( pfx );
                pfx->m_cMvDefaultBins = freqexIndexToMvBins( pfxgp->m_iMvBinsIndex );
                pfx->m_iPrevMvBinsMultiplier = 0;
                freqexSetMvBins( pfx );

                TRACEWMA_EXIT( wmaResult, freqexDecodeAndGetTileConfig( paudec, cSubFrameSampleHalf ) );
                goto exit;
            }
        }

        if( pfx->m_nChCode > 1 )
        {
            // single mv
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfx->m_bUseSingleMv = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        }
    }

    if( pfx->m_bV1Compatible )
    {
        pfx->m_cScaleDefaultBins = freqexIndexToScaleBins( pfxgp->m_iScBinsIndex );
        pfx->m_iPrevScBinsMultiplier = 0;
        freqexSetScBins( pfx );
        pfx->m_cMvDefaultBins = freqexIndexToMvBins( pfxgp->m_iMvBinsIndex );
        pfx->m_iPrevMvBinsMultiplier = 0;
        freqexSetMvBins( pfx );

        TRACEWMA_EXIT( wmaResult, freqexDecodeAndGetTileConfig( paudec, cSubFrameSampleHalf ) );
        goto exit;
    }

    pfx->m_bOverlayOnly = WMAB_FALSE;
    if( !pfxgp->m_bUseImplicitStartPos || pfxgp->m_bOverlay )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfx->m_bOverlayOnly = (uVal == 1) ? 1 : 0;
    }

    if( pfxgp->m_iMvCodebookSet == 0 )
    {
        TRACEWMA_EXIT( wmaResult, freqexDecodeMvCbSet0( paudec, pfx, pfxgp ) );
    }
    else
    {
        for( i = 0; i < pfx->m_nChCode; i++ )
        {
            pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

            pcis->m_bFxUseNoiseFloor = WMAB_TRUE;
            pcis->m_bFxUseExponent = WMAB_TRUE;
            pcis->m_bFxUseSign = WMAB_TRUE;
            pcis->m_bFxUseReverse = WMAB_TRUE;
        }
    }

    if( pfx->m_bUseSingleMv )
        pfx->m_iNumMvChannels = 1;
    else
        pfx->m_iNumMvChannels = pfx->m_nChCode;

    // parameter setting
    pfx->m_cSubtiles = 1;
    pfx->m_cSubFrameSampleHalf = cSubFrameSampleHalf;
    pfx->m_cTileSize = pfx->m_cSubFrameSampleHalf;
    pfx->m_cOrigEnd = pfx->m_cEnd;
    pfx->m_iExplicitStartPos = (2 * pfxgp->m_iMinFreq * pfx->m_cSubFrameSampleHalf / pau->m_iSamplingRate);

    for (i=0; i < pfx->m_nChCode; i++)
    {
        pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];
        pcis->m_iFxBandConfig = 0;
    }

    // decode band configuration
    if( pfxgp->m_bNoArbitraryUniformConfig )
    {
        pfxgp->m_bArbitraryScaleBandConfig = WMAB_FALSE;
        pfxgp->m_bUseUniformScaleBands = WMAB_FALSE;
        TRACEWMA_EXIT( wmaResult, freqexDecodeNumScMvBands( paudec, pfx, pfxgp ) );
    }
    else
    {
        TRACEWMA_EXIT( wmaResult, freqexDecodeArbitraryUniformBandConfig( paudec, pfx, pfxgp ) );
    }

exit:
    return wmaResult;
}

WMARESULT freqexDecodeScaleFacWithPred_1dB( CAudioObjectDecoder *paudec,
                                            PerChannelInfo      *ppcinfo, 
                                            Fex                 *pfx,
                                            FexGlobalParam      *pfxgp,
                                            Bool                bBaseBand,
                                            Int                 iChCode )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Int             iTile, iBand, iLevel;
    Int             ***ppiIndex, *piResidualIndex, cNumBands, iPos, *pcNumBands, cTilesProc;
    U32             uVal, uBitCnt;
    WMARESULT       wmaResult = WMA_OK;
    FexScaleFacPredType **ppPredType;

    pfx->m_iScFacChPredOffset = 0;
    cTilesProc = pfx->m_iTilesInSubframeProcFx;
    cNumBands = pfx->m_cScaleBands;
    pcNumBands = NULL;
    piResidualIndex = &pfx->m_rgrgiScFacResidualIndex[iChCode][pfx->m_rgiScFacResidualBufOffset[iChCode]];
    ppiIndex = pfx->m_rgrgpiLogScaleFacIndex;
    ppPredType = pfx->m_rgpScFacPredType;

    if( bBaseBand )
    {
        pfx->m_bScFacIntraPredNoRef = WMAB_TRUE;
        cTilesProc = (pfx->m_iVersion > 2) ? pfx->m_iTilesInSubframeProcBs :
                                             pfx->m_iTilesInSubframeProcFx;
        pcNumBands = pfx->m_rgcScFacBaseBands;
        ppiIndex  = pfx->m_rgrgpiLogScaleFacBaseIndex;
        ppPredType = pfx->m_rgpScFacBasePredType;

        iPos = 0;
        for( iTile = 0; iTile < cTilesProc; iTile++ )
        {
            cNumBands = pcNumBands[iTile];
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                *(ppPredType[iTile]) = FexScaleFacIntraPredNoRef;
                PLUS_GETBITS( wmaResult, 7, &uVal );
                piResidualIndex[iPos] = (Int)uVal;
            }
            else
            {
                *(ppPredType[iTile]) = FexScaleFacReconPred;
            }
            iPos += cNumBands;
        }
    }
    else if( pfx->m_bScFacChPred == WMAB_TRUE )
    {
        for( iTile = 0; iTile < cTilesProc; iTile++ )
            *(ppPredType[iTile]) = FexScaleFacChPred;

        // decode offset
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
        {
            // no offset
            pfx->m_iScFacChPredOffset = 0;
        }
        else
        {
            // decode value
            PLUS_GETBITS( wmaResult, 4, &uVal );
            pfx->m_iScFacChPredOffset = (Int)uVal + 1;
            // decode sign
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 1 )
                pfx->m_iScFacChPredOffset = -pfx->m_iScFacChPredOffset;
        }
    }
    else
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfx->m_bScFacIntraPredNoRef = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

        *(ppPredType[0]) = FexScaleFacIntraPred;
        if( pfx->m_bScFacIntraPredNoRef )
        {
            *(ppPredType[0]) = FexScaleFacIntraPredNoRef;
            PLUS_GETBITS( wmaResult, 7, &uVal );
            piResidualIndex[0] = (Int)uVal;
        }

        for( iTile = 1; iTile < cTilesProc; iTile++ )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                if( pfx->m_bScFacIntraPredNoRef )
                {
                    *(ppPredType[iTile]) = FexScaleFacIntraPredNoRef;
                    PLUS_GETBITS( wmaResult, 7, &uVal );
                    piResidualIndex[iTile*cNumBands] = (Int)uVal;
                }
                else
                {
                    *(ppPredType[iTile]) = FexScaleFacIntraPred;
                }
            }
            else
            {
                *(ppPredType[iTile]) = FexScaleFacInterPred;
            }
        }
    }

    iPos = 0;
    for( iTile = 0; iTile < cTilesProc; iTile++ )
    {
        if( pcNumBands )
            cNumBands = pcNumBands[iTile];
        switch( *(ppPredType[iTile]) )
        {
            case FexScaleFacIntraPred:
            case FexScaleFacIntraPredNoRef:
                if( *(ppPredType[iTile]) == FexScaleFacIntraPredNoRef )
                    iBand = 1;
                else
                    iBand = 0;
                for( ; iBand < cNumBands; iBand++ )
                {
                    PLUS_GETDATA( wmaResult,
                                  huffDecGet( g_fexScFacLevelDecTableIntra_1dB,
                                              paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
                    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
                    if( uVal == 97 )
                    {
                        // escape level
                        PLUS_GETBITS( wmaResult, 5, &uVal );
                        iLevel = (Int)uVal;
                        while( uVal == 31 && iLevel < g_fexScaleMaxLevel_1dB )
                        {
                            PLUS_GETBITS( wmaResult, 5, &uVal );
                            iLevel += (Int)uVal;
                        }
                        iLevel++;
                        // escape sign
                        PLUS_GETBITS( wmaResult, 1, &uVal );
                        if( uVal == 0 )
                            iLevel = g_fexScaleMaxLevelIntra_1dB + iLevel;
                        else
                            iLevel = g_fexScaleMinLevelIntra_1dB - iLevel;
                        piResidualIndex[iPos + iBand] = iLevel;
                    }
                    else
                    {
                        piResidualIndex[iPos + iBand] = (Int)uVal + g_fexScaleMinLevelIntra_1dB;
                    }
                }
                break;

            case FexScaleFacInterPred:
                for( iBand = 0; iBand < cNumBands; iBand++ )
                {
                    PLUS_GETDATA( wmaResult,
                                  huffDecGet( g_fexScFacLevelDecTableInter_1dB,
                                              paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
                    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
                    piResidualIndex[iPos + iBand] = (Int)uVal + g_fexScaleMinLevelInter_1dB;
                }
                break;

            case FexScaleFacChPred:
                for( iBand = 0; iBand < cNumBands; iBand++ )
                {
                    PLUS_GETDATA( wmaResult,
                                  huffDecGet( g_fexScFacLevelDecTableCh_1dB,
                                              paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
                    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
                    piResidualIndex[iPos + iBand] = (Int)uVal + g_fexScaleMinLevelCh_1dB + pfx->m_iScFacChPredOffset;
                }
                break;

            case FexScaleFacReconPred:
                for( iBand = 0; iBand < cNumBands; iBand++ )
                {
                    PLUS_GETDATA( wmaResult,
                                  huffDecGet( g_fexScFacLevelDecTableRecon_1dB,
                                              paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
                    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
                    piResidualIndex[iPos + iBand] = (Int)uVal + g_fexScaleMinLevelRecon_1dB;
                }
                break;

            default:
                TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
                break;
        }
        iPos += cNumBands;
    }

    iPos = 0;
    for( iTile = 0; iTile < cTilesProc; iTile++ )
    {
        if( pcNumBands )
            cNumBands = pcNumBands[iTile];
        if( pfx->m_bReconDomain )
            *(ppiIndex[iTile]) = &piResidualIndex[iPos]; // assign pointer
        else
            memcpy( *(ppiIndex[iTile]), &piResidualIndex[iPos], sizeof(Int)*cNumBands ); // copy values
        iPos += cNumBands;
    }
    if( pfx->m_bReconDomain )
        pfx->m_rgiScFacResidualBufOffset[iChCode] += iPos;

#ifdef FEX_LOWRATE_DEBUG
    for(iTile=0;iTile<cTilesProc;iTile++){
        if(pcNumBands)cNumBands=pcNumBands[iTile];
        if(fplrfex_bitstream){
            if(bBaseBand)fprintf(fplrfex_bitstream,"\n  b(%d)  ",*(pfx->m_rgpScFacBasePredType[iTile]));
            else         fprintf(fplrfex_bitstream,"\n   (%d)[%d] ",*(pfx->m_rgpScFacPredType[iTile]),*(pfx->m_rgpiLogScaleFacRef[iTile]));}
        for(iBand=0;iBand<cNumBands;iBand++)
            if(fplrfex_bitstream){
                if((*ppiIndex[iTile])[iBand]!=g_fexScaleIntpl)fprintf(fplrfex_bitstream,"%3d ",(*ppiIndex[iTile])[iBand]);
                else fprintf(fplrfex_bitstream,"  * ");fflush(fplrfex_bitstream);}}
#endif

exit:
    return wmaResult;
}

WMARESULT freqexDecodeScaleEscape_3dB( CAudioObjectDecoder *paudec,
                                       Int *pcRun, Int *piLevel)
{
    U32             uVal;
    WMARESULT       wmaResult = WMA_OK;

    // escape run
    *pcRun = 0;
    do
    {
        PLUS_GETBITS( wmaResult, 4, &uVal );
        *pcRun += uVal;
    }
    while( uVal == 15 );

    // escape level
    *piLevel = 1;
    do
    {
        PLUS_GETBITS( wmaResult, 3, &uVal );
        *piLevel += uVal;
    }
    while( uVal == 7 && *piLevel < g_fexScaleIntpl);

    if( *piLevel > g_fexScaleIntpl )
        TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );

exit:
    return wmaResult;
}

Void freqexPackSign( Int  *piSignSrc,
                     Int  cSigns,
                     UInt *puSign,
                     Int  *piSignPos,
                     UInt **pSignDst )
{
    Int cPacked;

    while( cSigns > 0 )
    {
        if( cSigns <= *piSignPos )
            cPacked = cSigns;
        else
            cPacked = (*piSignPos + 1);

        cSigns -= cPacked;
        while( cPacked > 0 )
        {
            *puSign |= (*piSignSrc) << *piSignPos;
            piSignSrc++;
            (*piSignPos)--;
            cPacked--;
        }
        if( *piSignPos < 0 )
        {
            *piSignPos = sizeof(UInt) * BITS_PER_BYTE - 1;
            **pSignDst = *puSign;
            (*pSignDst)++;
            *puSign = 0;
        }
    }
}

Bool freqexGetSign( UInt **puSignIndex, UInt *puSignMask )
{
    Bool bFlag;

    bFlag = (**puSignIndex & *puSignMask) > 0 ? WMAB_TRUE : WMAB_FALSE;

    *puSignMask = *puSignMask >> 1;
    if( *puSignMask == 0 )
    {
        *puSignMask = 1 << (sizeof(UInt) * BITS_PER_BYTE - 1);
        (*puSignIndex)++;
    }

    return bFlag;
}


WMARESULT freqexDecodeScaleFacWithPred_3dB( CAudioObjectDecoder *paudec,
                                            PerChannelInfo      *ppcinfo, 
                                            Fex                 *pfx,
                                            FexGlobalParam      *pfxgp,
                                            Bool                bBaseBand,
                                            Int                 iChCode )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Int             iTile, iBand, rgcBands[6], rgcSignsNeeded[6], cSignsDecoded, cSigns, cBands, iRun, cRun, iLevel, iSign;
    Int             *piResidualIndex, *piFirstScFacNoRef, ***ppiIndex;
    Int             iResPos, iSignPos, iPosDst, iPosSrc, cBandsIntraPred, cResCoefs, cNumBands, *pcNumBands, cTilesProc, cFirstScFac;
    UInt            uSign, *puSignIndex;
    U32             uVal, uBitCnt;
    WMARESULT       wmaResult = WMA_OK;
    FexScaleFacPredType iPredType, **ppPredType;
    Int             iMaxTiles = reconProcGetMaxTiles(pau);

    if (!pau->m_bReconFex)
        iMaxTiles = 1;

    piResidualIndex = pfx->m_rgrgiScFacResidualIndex[iChCode] +
                        pfx->m_rgiScFacResidualBufOffset[iChCode];
    puSignIndex = pfx->m_rguScFacSignIndex;
    piFirstScFacNoRef = pfx->m_rgiScFacFirstNoRef;

    rgcBands[FexScaleFacIntraPred] = 0;
    rgcBands[FexScaleFacIntraPredNoRef] = 0;
    rgcBands[FexScaleFacInterPred] = 0;
    rgcBands[FexScaleFacIntplPred] = 0;
    rgcBands[FexScaleFacChPred] = 0;
    rgcBands[FexScaleFacReconPred] = 0;

    pfx->m_iScFacChPredOffset = 0;
    cTilesProc = pfx->m_iTilesInSubframeProcFx;
    cNumBands = pfx->m_cScaleBands;
    pcNumBands = NULL;
    ppiIndex = pfx->m_rgrgpiLogScaleFacIndex;
    ppPredType = pfx->m_rgpScFacPredType;
    if( bBaseBand )
    {
        pfx->m_bScFacIntraPredNoRef = WMAB_TRUE;
        cTilesProc = (pfx->m_iVersion > 2) ? pfx->m_iTilesInSubframeProcBs :
                                             pfx->m_iTilesInSubframeProcFx;
        pcNumBands = pfx->m_rgcScFacBaseBands;
        ppiIndex  = pfx->m_rgrgpiLogScaleFacBaseIndex;
        ppPredType = pfx->m_rgpScFacBasePredType;
        cFirstScFac = 0;
        for( iTile = 0; iTile < cTilesProc; iTile++ )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                *(ppPredType[iTile]) = FexScaleFacIntraPredNoRef;
                PLUS_GETBITS( wmaResult, 5, &uVal );
                iLevel = (Int)uVal;
                if( uVal == 31 )
                {
                    PLUS_GETBITS( wmaResult, 3, &uVal );
                    iLevel += (Int)uVal;
                }
                piFirstScFacNoRef[cFirstScFac] = iLevel;
                rgcBands[FexScaleFacIntraPredNoRef] += (pcNumBands[iTile] - 1);
                cFirstScFac++;
            }
            else
            {
                *(ppPredType[iTile]) = FexScaleFacReconPred;
                rgcBands[FexScaleFacReconPred] += pcNumBands[iTile];
            }
        }
    }
    else if( pfx->m_bScFacChPred == WMAB_TRUE )
    {
        for( iTile = 0; iTile < cTilesProc; iTile++ )
            *(ppPredType[iTile]) = FexScaleFacChPred;
        rgcBands[FexScaleFacChPred] = cTilesProc;

        // decode offset
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
        {
            // no offset
            pfx->m_iScFacChPredOffset = 0;
        }
        else
        {
            // decode value
            PLUS_GETBITS( wmaResult, 2, &uVal );
            pfx->m_iScFacChPredOffset = (Int)uVal + 1;
            // decode sign
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 1 )
                pfx->m_iScFacChPredOffset = -pfx->m_iScFacChPredOffset;
        }
    }
    else
    {
        *(ppPredType[0]) = FexScaleFacIntraPred;
        rgcBands[FexScaleFacIntraPred]++;

        // decode flag for no referece
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfx->m_bScFacIntraPredNoRef = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        if( pfx->m_bScFacIntraPredNoRef == WMAB_TRUE )
        {
            *(ppPredType[0]) = FexScaleFacIntraPredNoRef;
            PLUS_GETBITS( wmaResult, 5, &uVal );
            iLevel = (Int)uVal;
            if( uVal == 31 )
            {
                PLUS_GETBITS( wmaResult, 3, &uVal );
                iLevel += (Int)uVal;
            }
            piFirstScFacNoRef[0] = iLevel;
            rgcBands[FexScaleFacIntraPred] = 0;
            rgcBands[FexScaleFacIntraPredNoRef] = 1;
        }
        // decode prediction
        for( iTile = 1; iTile < cTilesProc; iTile++ )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                *(ppPredType[iTile]) = FexScaleFacInterPred;
                rgcBands[FexScaleFacInterPred]++;
            }
            else
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 0 )
                {
                    if( pfx->m_bScFacIntraPredNoRef )
                    {
                        *(ppPredType[iTile]) = FexScaleFacIntraPredNoRef;
                        PLUS_GETBITS( wmaResult, 5, &uVal );
                        iLevel = (Int)uVal;
                        if( uVal == 31 )
                        {
                            PLUS_GETBITS( wmaResult, 3, &uVal );
                            iLevel += (Int)uVal;
                        }
                        piFirstScFacNoRef[rgcBands[FexScaleFacIntraPredNoRef]] = iLevel;
                        rgcBands[FexScaleFacIntraPredNoRef]++;
                    }
                    else
                    {
                        *(ppPredType[iTile]) = FexScaleFacIntraPred;
                        rgcBands[FexScaleFacIntraPred]++;
                    }
                }
                else
                {
                    *(ppPredType[iTile]) = FexScaleFacIntplPred;
                    rgcBands[FexScaleFacIntplPred]++;
                }
            }
        }
    }

    if( !bBaseBand )
    {
        cFirstScFac = rgcBands[FexScaleFacIntraPredNoRef];

        rgcBands[FexScaleFacIntraPred] *= cNumBands;
        rgcBands[FexScaleFacIntraPredNoRef] *= (cNumBands-1); // subtract absolutely coded scale
        rgcBands[FexScaleFacInterPred] *= cNumBands;
        rgcBands[FexScaleFacIntplPred] *= cNumBands;
        rgcBands[FexScaleFacChPred] *= cNumBands;
        rgcBands[FexScaleFacReconPred] *= cNumBands;
    }
    cResCoefs = rgcBands[FexScaleFacIntraPred] +
                rgcBands[FexScaleFacIntraPredNoRef] +
                rgcBands[FexScaleFacInterPred] +
                rgcBands[FexScaleFacIntplPred] +
                rgcBands[FexScaleFacChPred] + 
                rgcBands[FexScaleFacReconPred];

    rgcSignsNeeded[FexScaleFacIntraPred] = 0;
    rgcSignsNeeded[FexScaleFacIntraPredNoRef] = 0;
    rgcSignsNeeded[FexScaleFacInterPred] = 0;
    rgcSignsNeeded[FexScaleFacIntplPred] = 0;
    rgcSignsNeeded[FexScaleFacChPred] = 0;
    rgcSignsNeeded[FexScaleFacReconPred] = 0;
    cSignsDecoded = 0;
    iResPos = 0;
    uSign = 0;
    iSignPos = sizeof(UInt) * BITS_PER_BYTE - 1;

    // decode run-level
    cBandsIntraPred = (pfx->m_bScFacIntraPredNoRef) ? rgcBands[FexScaleFacIntraPredNoRef] :
                                                      rgcBands[FexScaleFacIntraPred];
    cBands = 0;
    while( cBands < cBandsIntraPred )
    {
        PLUS_GETDATA( wmaResult,
                      huffDecGet( g_fexScFacRunLevelDecTableIntra_3dB,
                                  paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
        if( uVal == 62 )
        {
            TRACEWMA_EXIT( wmaResult, 
                           freqexDecodeScaleEscape_3dB( paudec, &cRun, &iLevel ) );
            if( iLevel == 1 )
                iLevel = 0;
            // compensate run
            if( iLevel < g_fexScaleRunLevelMaxLevelIntra_3dB )
            {
                cRun += (g_fexScaleRunLevelVLCAtLevelIntra_3dB[iLevel+1] 
                            - g_fexScaleRunLevelVLCAtLevelIntra_3dB[iLevel]);
            }

        }
        else
        {
            cRun = g_fexScFacRunIntra_3dB[uVal];
            iLevel = g_fexScFacLevelIntra_3dB[uVal];
        }
        
        // ensure that the index in the loop below stays inbounds
        if (pfx->m_rgiScFacResidualBufOffset[iChCode] + iResPos + cRun + 1 
            > iMaxTiles * pfx->m_cMaxBands)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        for( iRun = 0; iRun < cRun; iRun++ )
            piResidualIndex[iResPos++] = 1;
        piResidualIndex[iResPos++] = iLevel;

        rgcSignsNeeded[FexScaleFacIntraPred] += cRun; // "1" is run
        if( iLevel != 0 )
            rgcSignsNeeded[FexScaleFacIntraPred]++;

        cBands += cRun + 1;
    }
    cSigns = cBands - cBandsIntraPred;
    if( cSigns > 0 )
    {
        // save signs padded
        iResPos -= cSigns;
        freqexPackSign( &piResidualIndex[iResPos], cSigns, &uSign, &iSignPos, &puSignIndex );
        // exclude signs padded
        cSignsDecoded += cSigns;
        rgcSignsNeeded[FexScaleFacIntraPred] -= (cSigns - 1);
    }
    
    // insert first scale factor for FexScaleFacIntraPredNoRef
    if( pfx->m_bScFacIntraPredNoRef )
    {
        Bool fBufferUnderflow = WMAB_FALSE;
        iPosSrc = iResPos - 1;
        iPosDst = iPosSrc + cFirstScFac;
        iLevel = cFirstScFac - 1;
        iTile = cTilesProc;
        while( iPosDst >= 0 )
        {
            if( pcNumBands )
            {
                while( (--iTile) >= 0 )
                {
                    if( *(ppPredType[iTile]) == FexScaleFacIntraPredNoRef )
                        break;
                }
                if( iTile < 0 )
                {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
                }
                cNumBands = pcNumBands[iTile];
            }
            for( iRun = 0; iRun < (cNumBands-1) && iPosDst >= 0; iRun++ )
                piResidualIndex[iPosDst--] = piResidualIndex[iPosSrc--];

            if (iPosDst >= 0) // Write to iPosDst only if it will not cause underflow
            {
                // make the value minus so that applying sign is skipped later
                piResidualIndex[iPosDst--] = -piFirstScFacNoRef[iLevel--];
            }
            else             // above loop caused underflow
                fBufferUnderflow = WMAB_TRUE;
        }
        if ( iPosDst != -1 || iPosSrc != -1 || fBufferUnderflow)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        // increment buffer position by # of intra
        iResPos += cFirstScFac;
    }

    cBands = 0;
    while( cBands < rgcBands[FexScaleFacInterPred] )
    {
        PLUS_GETDATA( wmaResult,
                      huffDecGet( g_fexScFacRunLevelDecTableInter_3dB,
                                  paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );

        // ensure that the index in the loop below stays inbounds
        if (pfx->m_rgiScFacResidualBufOffset[iChCode] + iResPos + g_fexScFacRunInter_3dB[uVal] + 1 
            > iMaxTiles * pfx->m_cMaxBands)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        for( iRun = 0; iRun < g_fexScFacRunInter_3dB[uVal]; iRun++ )
            piResidualIndex[iResPos++] = 1;
        piResidualIndex[iResPos++] = g_fexScFacLevelInter_3dB[uVal];

        rgcSignsNeeded[FexScaleFacInterPred] += g_fexScFacRunInter_3dB[uVal];  // "1" is run
        if( g_fexScFacLevelInter_3dB[uVal] != 0 )
            rgcSignsNeeded[FexScaleFacInterPred]++;

        cBands += g_fexScFacRunInter_3dB[uVal] + 1;
    }
    cSigns = cBands - rgcBands[FexScaleFacInterPred];
    if( cSigns > 0 )
    {
        // rewind index
        iResPos -= cSigns;
        // check if max run is used to terminate run-level. if so, ignore the last one
        if( g_fexScFacRunInter_3dB[uVal] + 1 == g_fexScaleRunLevelVLCAtLevelInter_3dB[g_fexScFacLevelInter_3dB[uVal]+1]
                                                - g_fexScaleRunLevelVLCAtLevelInter_3dB[g_fexScFacLevelInter_3dB[uVal]] )
        {
            cSigns--;
            rgcSignsNeeded[FexScaleFacInterPred] -= cSigns;
        }
        else
        {
            rgcSignsNeeded[FexScaleFacInterPred] -= (cSigns - 1); // -1 because last sign is always 0
        }

        if( cSigns > 0 )
        {
            // save signs padded
            freqexPackSign( &piResidualIndex[iResPos], cSigns, &uSign, &iSignPos, &puSignIndex );
            // exclude signs padded
            cSignsDecoded += cSigns;
        }
    }

    cBands = 0;
    while( cBands < rgcBands[FexScaleFacIntplPred] )
    {
        PLUS_GETDATA( wmaResult,
                      huffDecGet( g_fexScFacRunLevelDecTableIntpl_3dB,
                                  paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );

        // ensure that the index in the loop below stays inbounds
        if (pfx->m_rgiScFacResidualBufOffset[iChCode] + iResPos + g_fexScFacRunIntpl_3dB[uVal] + 1 
            > iMaxTiles * pfx->m_cMaxBands)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        for( iRun = 0; iRun < g_fexScFacRunIntpl_3dB[uVal]; iRun++ )
            piResidualIndex[iResPos++] = g_fexScaleIntpl;
        piResidualIndex[iResPos++] = g_fexScFacLevelIntpl_3dB[uVal];

        if( g_fexScFacLevelIntpl_3dB[uVal] != 0 ) // "0" is run
            rgcSignsNeeded[FexScaleFacIntplPred]++;

        cBands += g_fexScFacRunIntpl_3dB[uVal] + 1;
    }
    cSigns = cBands - rgcBands[FexScaleFacIntplPred];
    if( cSigns > 0 )
    {
        // rewind index
        iResPos -= cSigns;
        // check if max run is used to terminate run-level. if so, ignore the last one
        if( g_fexScFacRunIntpl_3dB[uVal] + 1 == g_fexScaleRunLevelVLCAtLevelIntpl_3dB[g_fexScFacLevelIntpl_3dB[uVal]+1]
                                                - g_fexScaleRunLevelVLCAtLevelIntpl_3dB[g_fexScFacLevelIntpl_3dB[uVal]] )
        {
            cSigns--;
            if( g_fexScFacLevelIntpl_3dB[uVal] != 0 )
                rgcSignsNeeded[FexScaleFacIntplPred]--;
        }
        else
        {
            rgcSignsNeeded[FexScaleFacIntplPred]--; // exclude the last sign which is always "1"
        }

        if( cSigns > 0 )
        {
            // save signs padded
            for( iSign = 0; iSign < cSigns; iSign++ )
            {
                if( piResidualIndex[iResPos + iSign] == g_fexScaleIntpl )
                    piResidualIndex[iResPos + iSign] = 0;
            }
            freqexPackSign( &piResidualIndex[iResPos], cSigns, &uSign, &iSignPos, &puSignIndex );
            // exclude signs padded
            cSignsDecoded += cSigns;
        }
    }

    cBands = 0;
    while( cBands < rgcBands[FexScaleFacChPred] )
    {
        PLUS_GETDATA( wmaResult,
                      huffDecGet( g_fexScFacRunLevelDecTableCh_3dB,
                                  paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
        if( uVal == 29 )
        {
            TRACEWMA_EXIT( wmaResult,
                           freqexDecodeScaleEscape_3dB( paudec, &cRun, &iLevel ) );

            // compensate run
            if( iLevel < g_fexScaleRunLevelMaxLevelCh_3dB )
            {
                cRun += (g_fexScaleRunLevelVLCAtLevelCh_3dB[iLevel+1] 
                            - g_fexScaleRunLevelVLCAtLevelCh_3dB[iLevel]);
            }
        }
        else
        {
            cRun = g_fexScFacRunCh_3dB[uVal];
            iLevel = g_fexScFacLevelCh_3dB[uVal];
        }
        // ensure that the index in the loop below stays inbounds
        if (pfx->m_rgiScFacResidualBufOffset[iChCode] + iResPos + cRun + 1 
            > iMaxTiles * pfx->m_cMaxBands)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        for( iRun = 0; iRun < cRun; iRun++ )
            piResidualIndex[iResPos++] = 0;
        piResidualIndex[iResPos++] = iLevel;

        if( iLevel != 0 )
            rgcSignsNeeded[FexScaleFacChPred]++;

        cBands += cRun + 1;
    }
    cSigns = cBands - rgcBands[FexScaleFacChPred];
    if( cSigns > 0 )
    {
        // save signs padded
        iResPos -= cSigns;
        freqexPackSign( &piResidualIndex[iResPos], cSigns, &uSign, &iSignPos, &puSignIndex );
        // exclude signs padded
        cSignsDecoded += cSigns;
        rgcSignsNeeded[FexScaleFacChPred]--;
    }

    cBands = 0;
    while( cBands < rgcBands[FexScaleFacReconPred] )
    {
        PLUS_GETDATA( wmaResult,
                      huffDecGet( g_fexScFacRunLevelDecTableRecon_3dB,
                                  paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
        if( uVal == 32 )
        {
            TRACEWMA_EXIT( wmaResult,
                           freqexDecodeScaleEscape_3dB( paudec, &cRun, &iLevel ) );
            // compensate run
            if( iLevel < g_fexScaleRunLevelMaxLevelRecon_3dB )
            {
                cRun += (g_fexScaleRunLevelVLCAtLevelRecon_3dB[iLevel+1] 
                            - g_fexScaleRunLevelVLCAtLevelRecon_3dB[iLevel]);
            }
        }
        else
        {
            cRun = g_fexScFacRunRecon_3dB[uVal];
            iLevel = g_fexScFacLevelRecon_3dB[uVal];
        }
        // ensure that the index in the loop below stays inbounds
        if (pfx->m_rgiScFacResidualBufOffset[iChCode] + iResPos + cRun + 1 
            > iMaxTiles * pfx->m_cMaxBands)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        for( iRun = 0; iRun < cRun; iRun++ )
            piResidualIndex[iResPos++] = 0;
        piResidualIndex[iResPos++] = iLevel;

        if( iLevel != 0 )
            rgcSignsNeeded[FexScaleFacReconPred]++;

        cBands += cRun + 1;
    }
    cSigns = cBands - rgcBands[FexScaleFacReconPred];
    if( cSigns > 0 )
    {
        // save signs padded
        iResPos -= cSigns;
        freqexPackSign( &piResidualIndex[iResPos], cSigns, &uSign, &iSignPos, &puSignIndex );
        // exclude signs padded
        cSignsDecoded += cSigns;
        rgcSignsNeeded[FexScaleFacReconPred]--;
    }

    if( (iResPos - cFirstScFac) != cResCoefs )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
    }

    while( cSignsDecoded < rgcSignsNeeded[FexScaleFacIntraPred] + 
                           rgcSignsNeeded[FexScaleFacInterPred] +
                           rgcSignsNeeded[FexScaleFacIntplPred] + 
                           rgcSignsNeeded[FexScaleFacChPred]    +
                           rgcSignsNeeded[FexScaleFacReconPred] )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        freqexPackSign( (Int *)&uVal, 1, &uSign, &iSignPos, &puSignIndex );
        cSignsDecoded++;
    }

    // put remaining signs into buffer
    if( iSignPos < sizeof(UInt) * BITS_PER_BYTE - 1 )
        *puSignIndex = uSign;

    // apply sign
    iResPos = 0;
    uSign = 1 << (sizeof(UInt) * BITS_PER_BYTE - 1);
    puSignIndex = pfx->m_rguScFacSignIndex;
    while( iResPos < (cResCoefs + cFirstScFac) )
    {
        iLevel = piResidualIndex[iResPos];
        if( iLevel != g_fexScaleIntpl )
        {
            if( iLevel > 0 )
            {
                if( freqexGetSign( &puSignIndex, &uSign ) )
                    iLevel = -iLevel;
                iSignPos++;
            }
            else if( iLevel < 0 )
            {
                // it is absolutely coded
                iLevel = -iLevel;
            }
        }
        piResidualIndex[iResPos] = iLevel + pfx->m_iScFacChPredOffset;
        iResPos++;
    }

    // re-order residual
    iResPos = 0;
    for( iPredType = FexScaleFacIntraPred; iPredType <= FexScaleFacReconPred; iPredType++ )
    {
        for( iTile = 0; iTile < cTilesProc; iTile++ )
        {
            if( pcNumBands )
                cNumBands = pcNumBands[iTile];
            if( *(ppPredType[iTile]) == iPredType )
            {
                if( *(ppPredType[iTile]) == FexScaleFacReconPred )
                {
                    for( iBand = 0; iBand < cNumBands; iBand++ )
                        piResidualIndex[iResPos+iBand] = -piResidualIndex[iResPos+iBand];
                }

                if( pfx->m_bReconDomain )
                    *(ppiIndex[iTile]) = &piResidualIndex[iResPos]; // assign pointer
                else
                    memcpy( *(ppiIndex[iTile]), &piResidualIndex[iResPos], sizeof(Int) * cNumBands ); // copy values
                iResPos += cNumBands;
            }
        }
    }
    if( pfx->m_bReconDomain )
        pfx->m_rgiScFacResidualBufOffset[iChCode] += iResPos;

#ifdef FEX_LOWRATE_DEBUG
    for(iTile=0;iTile<cTilesProc;iTile++){
        if(fplrfex_bitstream){
            if( pcNumBands )cNumBands = pcNumBands[iTile];
            if(bBaseBand)fprintf(fplrfex_bitstream,"\n  b(%d)  ",*(pfx->m_rgpScFacBasePredType[iTile]));
            else         fprintf(fplrfex_bitstream,"\n   (%d) [%d]  ",*(pfx->m_rgpScFacPredType[iTile]),*(pfx->m_rgpiLogScaleFacRef[iTile]));}
        for(iBand=0;iBand<cNumBands;iBand++)
            if(fplrfex_bitstream){
                if((*ppiIndex[iTile])[iBand]!=g_fexScaleIntpl)fprintf(fplrfex_bitstream,"%3d ",(*ppiIndex[iTile])[iBand]);
                else fprintf(fplrfex_bitstream,"  * ");fflush(fplrfex_bitstream);}}
#endif

exit:
    return wmaResult;
}

WMARESULT freqexDecodeScaleFacFrameV2( CAudioObjectDecoder *paudec,
                                       PerChannelInfo      *ppcinfo,
                                       PerChannelInfo      *ppcinfoFirst,
                                       Int                 iChCode )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp=0;
    Int             iBand, iLevel;
    U32             uVal;
    WMARESULT       wmaResult = WMA_OK;
    WMARESULT       (*pfnDecodeScaleFacWithPred)( CAudioObjectDecoder *paudec,
                                                  PerChannelInfo      *ppcinfo, 
                                                  Fex                 *pfx,
                                                  FexGlobalParam      *pfxgp,
                                                  Bool                bBaseBand,
                                                  Int                 iChCode);

#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n  iChCode=%d",iChCode);fflush(fplrfex_bitstream);}
#endif

    if( pfx->m_bReconDomain && !pfx->m_bFirstTileV2Recon )
    {
        goto end;
    }
    else if( pfx->m_bReconDomain )
    {
        if( prp == NULL )
            return TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
        pfx->m_iTilesInSubframeProcFx = prp->m_iTilesInSubframeProcFx;
    }
    else
    {
        pfx->m_iTilesInSubframeProcFx = 1;
    }

    if( pfx->m_iTilesInSubframeProcFx <= 0 )
        goto end;

    if( pfx->m_bReconDomain )
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    switch( pfxgp->m_iScFacStepSize )
    {
        case 1:
            pfnDecodeScaleFacWithPred = freqexDecodeScaleFacWithPred_1dB;
            break;
        case 3:
            pfnDecodeScaleFacWithPred = freqexDecodeScaleFacWithPred_3dB;
            break;
        default:
            TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
            break;
    }

    if( iChCode == 0 )
    {
        pfx->m_bScFacIntraPredNoRef = WMAB_FALSE;

        pfx->m_bScFacChPred = WMAB_FALSE;
        TRACEWMA_EXIT( wmaResult, 
                       pfnDecodeScaleFacWithPred( paudec, ppcinfo, pfx, pfxgp, WMAB_FALSE, iChCode ) );
    }
    else
    {
        // decode ch pred
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
            pfx->m_bScFacChPred = WMAB_FALSE;
        else
            pfx->m_bScFacChPred = WMAB_TRUE;
        // decode scale factors
        TRACEWMA_EXIT( wmaResult,
                       pfnDecodeScaleFacWithPred( paudec, ppcinfo, pfx, pfxgp, WMAB_FALSE, iChCode ) );
    }

end:

    if( !pfx->m_bReconDomain )
    {
        // reconstruct scale factors
        if( iChCode == 0 || pfx->m_bScFacChPred == WMAB_FALSE )
        {
            // with intra prediction
            if( pfx->m_bScFacIntraPredNoRef )
                iLevel = 0;
            else
                iLevel = *(ppcinfo->m_piFexLogScaleFacIndexRef);

            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                iLevel += ppcinfo->m_piFexLogScaleFacIndex[iBand];
                ppcinfo->m_piFexLogScaleFacIndex[iBand] = iLevel;
                ppcinfo->m_pffltFexScaleFac[iBand] =
                    freqexInvQuantScaleV2( pfx, pfxgp->m_iScFacStepSize, 
                                           FASTFLOAT_FROM_INT( iLevel ) );
            }
        }
        else
        {
            // with channel prediction
            for( iBand = 0; iBand < pfx->m_cScaleBands; iBand++ )
            {
                ppcinfo->m_pffltFexScaleFac[iBand] =
                    freqexInvQuantScaleV2( pfx, pfxgp->m_iScFacStepSize, 
                        FASTFLOAT_FROM_INT( ppcinfo->m_piFexLogScaleFacIndex[iBand] ) );

                ppcinfo->m_pffltFexScaleFac[iBand] =
                    FASTFLOAT_MULT( ppcinfo->m_pffltFexScaleFac[iBand],
                                    ppcinfoFirst->m_pffltFexScaleFac[iBand] );

                ppcinfo->m_piFexLogScaleFacIndex[iBand] += ppcinfoFirst->m_piFexLogScaleFacIndex[iBand];
            }
        }
    }

    if( !pfx->m_bReconDomain || !chexInfoStatNoFx( pfx->m_prtiCurr->m_uInfoStat ) )
        *(ppcinfo->m_pFexScaleFacPred) = *(pfx->m_rgpScFacPredType[0]);

exit:
    return wmaResult;
}

#if 0
WMARESULT freqexDecodeScaleFacV1Style( CAudioObjectDecoder *paudec,
                                       PerChannelInfo      *ppcinfo,
                                       Int                 iChCode )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    CoefType        *pfRecon;
    Int             iBand;
    WMARESULT       wmaResult = WMA_OK;

    if( pfx->m_bReconDomain )
    {
        if( pfx->m_cScaleBands != pfx->m_cScaleBandsOverlayOnly )
            TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
    }
    else
    {
        if( (pfx->m_bOverlayOnly && pfx->m_cScaleBands < pfx->m_cScaleBandsOverlayOnly) ||
            (!pfx->m_bOverlayOnly && pfx->m_cScaleBands != pfx->m_cScaleBandsOverlayOnly) )
            TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
    }

    pfx->m_cStartIndex = pfx->m_cStart;
    pfRecon = pfx->m_pfRecon+pfx->m_cStart;
    for( iBand = 0; iBand < min( pfx->m_cScaleBands, pfx->m_cScaleBandsOverlayOnly ); iBand++ )
    {
        Int iActLen = 1; // initialize to any non-0 value

        pfx->m_cBandSize = pfx->m_piScaleBandSizes[iBand];
        freqexSetBandParams( pau, ppcinfo, iChCode, iBand );
        if( !pfx->m_bReconDomain && WMAB_TRUE == pfx->m_bOverlayUsedForBand )
            iActLen = freqexGetValidLength( pfx, pfRecon, pfx->m_cBandSize );

        if( 0 == iBand )
            pfx->m_bFirstScaleFacBand = WMAB_TRUE;

        TRACEWMA_EXIT( wmaResult,
                       freqexDecodeScale( paudec, ppcinfo, iChCode, iBand, iActLen ) );
#ifdef FEX_LOWRATE_DEBUG
        if(fplrfex_bitstream){if(iBand==0)fprintf(fplrfex_bitstream,"\n");fprintf(fplrfex_bitstream," %3d",ppcinfo->m_piFexLogScaleFacIndex[iBand]);}
#endif
        pfx->m_cStartIndex += pfx->m_cBandSize;
        pfRecon += pfx->m_cBandSize;
    }

    for( ; iBand < pfx->m_cScaleBands; iBand++ )
    {
        ppcinfo->m_pffltFexScaleFac[iBand] = FFLT_ZERO;
        ppcinfo->m_piFexLogScaleFacIndex[iBand] = 0;
    }
exit:
    return wmaResult;
}

WMARESULT freqexDecodeScaleBase( CAudioObjectDecoder *paudec,
                                 PerChannelInfo      *ppcinfo,
                                 Int iChCode,
                                 Int iBand )
{
    WMARESULT wmaResult = WMA_OK;
    Fex *pfx = &(paudec->pau->m_fex);

    if( pfx->m_bFirstScaleFacCh && pfx->m_bFirstScaleFacBand )
    {
        pfx->m_bUseScalePred = WMAB_FALSE;
    }
    else
    {
        if( pfx->m_bFirstScaleFacBand )
            pfx->m_iPrevLogScaleIndex = pfx->m_iFirstChLogScaleBaseIndex;
        pfx->m_bUseScalePred = WMAB_TRUE;
    }
    
    TRACEWMA_EXIT( wmaResult,
                   freqexDecodeScaleBand( paudec, 
                                          &ppcinfo->m_pffltFexScaleFacBase[iBand],
                                          &ppcinfo->m_piFexLogScaleFacBaseIndex[iBand]) );

    if( pfx->m_bFirstScaleFacCh && pfx->m_bFirstScaleFacBand )
        pfx->m_iFirstChLogScaleBaseIndex = pfx->m_iPrevLogScaleIndex;
    pfx->m_bFirstScaleFacBand = WMAB_FALSE;
    pfx->m_bFirstScaleFacCh = WMAB_FALSE;

exit:
    return wmaResult;
}

WMARESULT freqexDecodeScaleFacBaseV1Style( CAudioObjectDecoder *paudec,
                                           PerChannelInfo      *ppcinfo,
                                           Int                 iChCode )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    CoefType        *pfRecon;
    Int             iBand;
    WMARESULT       wmaResult = WMA_OK;

    if( pfx->m_cBaseBands == 0 )
        goto exit;

    pfx->m_cStartIndex = pfx->m_cStart;
    pfRecon = pfx->m_pfRecon+pfx->m_cStart;
    for( iBand = 0; iBand < pfx->m_cBaseBands; iBand++ )
    {
        if( 0 == iBand )
            pfx->m_bFirstScaleFacBand = WMAB_TRUE;

        TRACEWMA_EXIT( wmaResult,
                       freqexDecodeScaleBase( paudec, ppcinfo, iChCode, iBand ) );
#ifdef FEX_LOWRATE_DEBUG
        if(fplrfex_bitstream){if(iBand==0)fprintf(fplrfex_bitstream,"\n");fprintf(fplrfex_bitstream," %3d",ppcinfo->m_piFexLogScaleFacBaseIndex[iBand]);}
#endif
        pfx->m_cStartIndex += pfx->m_cBandSize;
        pfRecon += pfx->m_cBandSize;
    }

exit:
    return wmaResult;
}
#endif

WMARESULT freqexDecodeScaleFacBaseFrameV2( CAudioObjectDecoder *paudec,
                                           PerChannelInfo      *ppcinfo,
                                           Int                 iChCode )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp;
    WMARESULT       wmaResult = WMA_OK;

    if( pfx->m_cBaseBands == 0 || !pfx->m_bReconDomain )
        goto exit;

    if( !pfx->m_bFirstTileV2Recon )
        goto end;

    pfx->m_iTilesInSubframeProcFx = prp->m_iTilesInSubframeProcFx;
    pfx->m_iTilesInSubframeProcBs = prp->m_iTilesInSubframeProcBs;
    pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);

    switch( pfxgp->m_iBaseFacStepSize )
    {
        case 1:
            TRACEWMA_EXIT( wmaResult, 
                           freqexDecodeScaleFacWithPred_1dB( paudec, ppcinfo, pfx, pfxgp, WMAB_TRUE, iChCode ) );
            break;
        case 3:
            TRACEWMA_EXIT( wmaResult, 
                           freqexDecodeScaleFacWithPred_3dB( paudec, ppcinfo, pfx, pfxgp, WMAB_TRUE, iChCode ) );
            break;
        default:
            TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
            break;
    }

end:
    *(ppcinfo->m_pFexScaleFacBasePred) = *(pfx->m_rgpScFacBasePredType[0]);

exit:
    return wmaResult;
}

WMARESULT freqexDecodeMvMergedV2( CAudioObjectDecoder *paudec,
                                  PerChannelInfo      *ppcinfo,
                                  PerChannelInfo      *ppcinfoFirst,
                                  Int                 iChCode,
                                  Bool                *pbMvUpdate )
{
    CAudioObject    *pau = paudec->pau;
    ReconProc       *prp = pau->m_prp;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    U32             uVal;
    WMARESULT       wmaResult = WMA_OK;

    if( !pfx->m_bReconDomain )
        goto exit;

    *pbMvUpdate = WMAB_FALSE;
    if (*(ppcinfo->m_pcFexSubframesMvMerged) == 0)
    {
        if( iChCode == 0 || !pfx->m_bUseSingleMv )
        {
            // decode 1st bit
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                // set all subframes to be merged
                *(ppcinfo->m_pcFexSubframesMvMerged) = prp->m_iTilesInSubframeProcFx;
            }
            else
            {
                do
                {
                    PLUS_GETBITS( wmaResult, 3, &uVal );
                    *(ppcinfo->m_pcFexSubframesMvMerged) += uVal;

                }
                while( uVal == 7 && 
                       *(ppcinfo->m_pcFexSubframesMvMerged) < prp->m_iTilesInSubframeProcFx );

                *(ppcinfo->m_pcFexSubframesMvMerged) += 1;
            }
            pfx->m_rgprtiMvAnchor[iChCode] = pfx->m_prtiCurr;

            if( pfxgp->m_iMvCodebookSet == 0 )
            {
                // decode Use{NoiseFloor,Exponent,Sign,Reverse}
                TRACEWMA_EXIT( wmaResult, freqexDecodeMvCbSet0( paudec, pfx, pfxgp ) );
            }

#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n     MvMerged=%d",*(ppcinfo->m_pcFexSubframesMvMerged));fflush(fplrfex_bitstream);}
#endif
        }
        else
        {
            // for single-mv (add 1 since the value in ppcinfoFirst has been decremented)
            *(ppcinfo->m_pcFexSubframesMvMerged) = *(ppcinfoFirst->m_pcFexSubframesMvMerged) + 1;
            pfx->m_rgprtiMvAnchor[iChCode] = pfx->m_rgprtiMvAnchor[0];
        }
        *pbMvUpdate = WMAB_TRUE;
    }

exit:
    return wmaResult;
}

WMARESULT freqexDecodeCbV2( CAudioObjectDecoder *paudec,
                            PerChannelInfo      *ppcinfo,
                            PerChannelInfo      *ppcinfoFirst,
                            PerChannelRecon     *ppcrFirst,
                            Int                 iChCode,
                            Int                 iBand )
{
    CAudioObject    *pau = paudec->pau;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp;
    I32             iCb;
    U32             uVal;
    PerChannelInfoShr *pcis0;
    WMARESULT       wmaResult = WMA_OK;

    if( WMAB_TRUE == pfx->m_bUseSingleMv && 0 == iChCode )
        pfx->m_pbMvCoded[iBand] = WMAB_FALSE;

    if( WMAB_FALSE == pfx->m_bNeedMvCoding )
        goto exit;  // use random noise, set during recon

    pcis0 = pau->m_rgpcinfoShr + pfx->m_rgiChCode[0];

    if( WMAB_TRUE == pfx->m_bUseSingleMv &&
        WMAB_TRUE == pfx->m_pbMvCoded[iBand] )
    {
        if( !pfx->m_bReconDomain )
            ppcinfo->m_piFexCb[iBand] = ppcinfoFirst->m_piFexCb[iBand];
        else
            ppcinfo->m_piFexCb[iBand] = ppcrFirst->m_rgiFexCb[iBand];

        goto exit;
    }

    if( pfx->m_bReconDomain )
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    if( pfxgp->m_iMvCodebookSet == 0 )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        iCb = (uVal == 0) ? 0 : 1;
        if( iCb == 0 )
        {
            if( pcis0->m_bFxUseNoiseFloor )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 1 )
                {
                    iCb = 2;
#ifdef BUILD_WMAPROLBRV3
                    if( pfxgp->m_bUseCb4 )
                        iCb = 4;
#endif
                }
            }
        }
    }
    else
    {
        if( !g_rgMvCodebook[pfxgp->m_iMvCodebook].m_bNoiseMv )
        {
            // no need to decode
            iCb = 0;
        }
        else if( !g_rgMvCodebook[pfxgp->m_iMvCodebook].m_bPredMv )
        {
            // no need to decode
            iCb = 1;
        }
        else
        {
            // decode Cb
            PLUS_GETBITS( wmaResult, 1, &uVal );
            iCb = (uVal == 1) ? 1 : 0;

            if( iCb == 0 && g_rgMvCodebook[pfxgp->m_iMvCodebook].m_bPredNoiseFloor )
            {
                // decode for Cb=0 or 2
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 1 )
                {
                    iCb = 2;
#ifdef BUILD_WMAPROLBRV3
                    if( pfxgp->m_bUseCb4 )
                        iCb = 4;
#endif
                }
            }
        }
    }
    ppcinfo->m_piFexCb[iBand] = iCb;

exit:
    return wmaResult;
}

WMARESULT freqexDecodePeakToNoiseScaleV2( const CAudioObjectDecoder *paudec,
                                          const PerChannelInfo *ppcinfo,
                                          const Int iBand,
                                          FastFloat *pfScale )
{
    CAudioObject    *pau = paudec->pau;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp;
    FastFloat       fScale = FFLT_ZERO;
    I32             iLogScale;
    U32             uVal, uBitCnt;
    WMARESULT       wmaResult = WMA_OK;

    if( pfx->m_bReconDomain )
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    PLUS_GETDATA( wmaResult,
                    huffDecGet( g_fexScFacLevelDecTableRecon_1dB,
                                paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );

    iLogScale = (Int)uVal + g_fexScaleMinLevelRecon_1dB;
#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"  NL=%d",iLogScale);fflush(fplrfex_bitstream);}
#endif

    // for rfex, predicted value is applied in the reconstruction, since scale factors are unknown now
    if( !pfx->m_bReconDomain )
        iLogScale += ppcinfo->m_piFexLogScaleFacIndex[iBand]; // add predicted value

    // unquantize noise scale factor
    fScale = freqexInvQuantScaleV2( pfx, pfxgp->m_iScFacStepSize, 
                        FASTFLOAT_FROM_INT( iLogScale ) );

exit:
    *pfScale = fScale;
    return wmaResult;
}

#ifdef BUILD_WMAPROLBRV3
WMARESULT freqexDecodeBandBaseScaleV3( const CAudioObjectDecoder *paudec,
                                       const PerChannelInfo *ppcinfo,
                                       const Int iBand,
                                       FastFloat *pfScale )
{
    CAudioObject    *pau = paudec->pau;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp;
    FastFloat       fScale = FFLT_ZERO;
    I32             iLogScale;
    U32             uVal, uBitCnt;
    WMARESULT       wmaResult = WMA_OK;

    if( !pfx->m_bReconDomain ||
        !pfx->m_bNeedMvCoding ||
        ppcinfo->m_piFexCb[iBand] != 4 )
        goto exit;

    pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);

    if( !pfxgp->m_bUseCb4 )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    PLUS_GETDATA( wmaResult,
                    huffDecGet( g_fexScFacLevelDecTableRecon_1dB,
                                paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );

    iLogScale = (Int)uVal + g_fexScaleMinLevelRecon_1dB;
#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"  Bs=%d",iLogScale);fflush(fplrfex_bitstream);}
#endif

    // unquantize noise scale factor
    fScale = freqexInvQuantScaleV2( pfx, pfxgp->m_iBaseFacStepSize, 
                        FASTFLOAT_FROM_INT( iLogScale ) );

exit:
    *pfScale = fScale;
    return wmaResult;
}
#endif


WMARESULT freqexDecodeMvV2( CAudioObjectDecoder *paudec,
                            PerChannelInfo      *ppcinfo,
                            PerChannelInfo      *ppcinfoFirst,
                            PerChannelRecon     *ppcrFirst,
                            Int                 iChCode,
                            Int                 iBand )
{
    CAudioObject    *pau = paudec->pau;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp;
    const FexMvCodebook *pmvcb;
    Int             iMv=0, iMv2=0, iCb=0, iSign = 1;
    FexType         fExp = FEXT_FROM_FLOAT( 1.0f );
    Bool            bRev = WMAB_FALSE;
    U32             uVal;
    WMARESULT       wmaResult = WMA_OK;
    PerChannelInfoShr *pcis0 = pau->m_rgpcinfoShr + pfx->m_rgiChCode[0];

    if( WMAB_FALSE == pfx->m_bNeedMvCoding )
        goto exit;  // use random noise, set during recon

    iCb = ppcinfo->m_piFexCb[iBand]; // already decoded

    if( WMAB_TRUE == pfx->m_bUseSingleMv &&
        WMAB_TRUE == pfx->m_pbMvCoded[iBand] )
    {
        if( !pfx->m_bReconDomain )
        {
            freqexCopyMvState(ppcinfo, ppcinfoFirst, iBand);
        }
        else
        {
            ppcinfo->m_piFexCb  [iBand] = ppcrFirst->m_rgiFexCb  [iBand];
            ppcinfo->m_pFexExp  [iBand] = ppcrFirst->m_rgFexExp  [iBand];
            ppcinfo->m_piFexMv  [iBand] = ppcrFirst->m_rgiFexMv  [iBand];
            ppcinfo->m_piFexMv2 [iBand] = ppcrFirst->m_rgiFexMv2 [iBand];
            ppcinfo->m_piFexSign[iBand] = ppcrFirst->m_rgiFexSign[iBand];
            ppcinfo->m_pbFexRev [iBand] = ppcrFirst->m_rgbFexRev [iBand];
        }
        goto end;
    }

    if( pfx->m_bReconDomain )
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    if( pfxgp->m_iMvCodebookSet == 0)
    {
        // exponent
        if( pcis0->m_bFxUseExponent && 2 != iCb )
        {
            PLUS_PEEKBITS( wmaResult, 2, &uVal );
            if( ((uVal & 2)>>1) == 0 ) // 0
            {
                fExp = FEXT_FROM_FLOAT( 0.5f );
                PLUS_FLUSHBITS( wmaResult, 1 );
            }
            else if( uVal == 2 ) // 10
            {
                fExp = FEXT_FROM_FLOAT( 1.0f );
                PLUS_FLUSHBITS( wmaResult, 2 );
            }
            else if (uVal == 3) // 11
            {
                fExp = FEXT_FROM_FLOAT( 2.0f );
                PLUS_FLUSHBITS( wmaResult, 2 );
            }
        }

        // sign
        iSign = 1;
        if( pcis0->m_bFxUseSign )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            iSign = (uVal == 0) ? 1 : -1;
        }
        // mv
        TRACEWMA_EXIT( wmaResult, 
                       freqexDecodeMvBand( paudec, ppcinfo, &iMv, iCb, iBand ) );
        // rev
        if( pcis0->m_bFxUseReverse )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            bRev = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        }
    }
    else
    {
        pmvcb = &(g_rgMvCodebook[pfxgp->m_iMvCodebook]);
        // decode exponent if needed
        if( (iCb == 0 && pmvcb->m_bPredExp) || 
            (iCb == 1 && pmvcb->m_bNoiseExp) ||
            (iCb == 4 && pmvcb->m_bPredExp) )
        {
            PLUS_PEEKBITS( wmaResult, 2, &uVal );
            if( ((uVal & 2)>>1) == 0 ) // 0
            {
                fExp = FEXT_FROM_FLOAT( 0.5f );
                PLUS_FLUSHBITS( wmaResult, 1 );
            }
            else if( uVal == 2 ) // 10
            {
                fExp = FEXT_FROM_FLOAT( 1.0f );
                PLUS_FLUSHBITS( wmaResult, 2 );
            }
            else if (uVal == 3) // 11
            {
                fExp = FEXT_FROM_FLOAT( 2.0f );
                PLUS_FLUSHBITS( wmaResult, 2 );
            }
        }

        // decode sign if needed
        iSign = 1;
        if( ((iCb == 0 || iCb == 2 || iCb == 4) && pmvcb->m_bPredSign) ||
            ( iCb == 1                          && pmvcb->m_bPredSign) )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            iSign = (uVal == 0) ? 1 : -1;
        }

        // decode mv if needed
        if( ((iCb == 0 || iCb == 2 || iCb == 4) && pmvcb->m_bPredMv) ||
            ( iCb == 1                          && pmvcb->m_bNoiseMv) )
        {
            TRACEWMA_EXIT( wmaResult, 
                           freqexDecodeMvBand( paudec, ppcinfo, &iMv, iCb, iBand ) );
        }

        // decode rev if needed
        if( ((iCb == 0 || iCb == 2 || iCb == 4) && pmvcb->m_bPredRev) ||
            ( iCb == 1                          && pmvcb->m_bNoiseRev) )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            bRev = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            if( pfx->m_bMvRangeFull && bRev )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
            }
        }
    }

#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n     %d:(%4d,%4d) Cb=%d  Mv=%3d  Exp=%.1f  Sing=%d  Rev=%d",iBand,pfx->m_cStartIndex,pfx->m_cBandSize,iCb,iMv,fExp,iSign,bRev);fflush(fplrfex_bitstream);}
#endif

    // decode secondary mv if needed
    if( (iCb == 2 && pfxgp->m_bUseRandomNoise == WMAB_FALSE) )
    {
        TRACEWMA_EXIT( wmaResult, 
                       freqexDecodeMvBand( paudec, ppcinfo, &iMv2, 3, iBand ) );
#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"  Mv2=%3d",iMv2);fflush(fplrfex_bitstream);}
#endif
    }

    ppcinfo->m_piFexMv  [iBand] = (I32)iMv;
    ppcinfo->m_piFexMv2 [iBand] = (I32)iMv2;
    ppcinfo->m_pFexExp  [iBand] = fExp;
    ppcinfo->m_piFexSign[iBand] = (I32)iSign;
    ppcinfo->m_pbFexRev [iBand] = bRev;

    if( pfx->m_bUseSingleMv )
    {
        freqexCopyMvState( ppcinfoFirst, ppcinfo, iBand );
        pfx->m_pbMvCoded[iBand] = WMAB_TRUE; // set this to true
    }

end:
    if( iCb == 2 )
    {
        // read peak to noise floor scale ratio
        TRACEWMA_EXIT( wmaResult,
                       freqexDecodePeakToNoiseScaleV2( paudec, ppcinfo, iBand, 
                                                       &ppcinfo->m_pffltFexScaleFacNoise[iBand] ) );
    }

exit:
    return wmaResult;
}

Void freqexDumpV1BandInfoDec(Fex *pfx, PerChannelInfo *ppcinfo, Int iChCode, Int iBand)
{
#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream){
        if(iBand==0){
            if(iChCode==0)
                fprintf(fplrfex_bitstream,"\nFrame=%d v1Tile=%d",pfx->m_pau->m_iFrameNumber,pfx->m_pau->m_iCurrTile);
            fprintf(fplrfex_bitstream,"\n iChCode=%d",iChCode);
        }
        fprintf(fplrfex_bitstream,"\n   Sc=%3d",ppcinfo->m_piFexLogScaleFacIndex[iBand]);
        if(pfx->m_bNeedMvCoding){
            fprintf(fplrfex_bitstream,"  Cb=%d  Mv=%4d  Exp=%.1f Sign=%2d Rev=%2d",ppcinfo->m_piFexCb[iBand],ppcinfo->m_piFexMv[iBand],ppcinfo->m_pFexExp[iBand],ppcinfo->m_piFexSign[iBand],ppcinfo->m_pbFexRev[iBand]);
            if(ppcinfo->m_piFexCb[iBand]==2){
                if(ppcinfo->m_ppcinfoShr->m_bFxUseRandomMv2)
                    fprintf(fplrfex_bitstream," Mv2=%4d",ppcinfo->m_piFexMv2[iBand]);
                fprintf(fplrfex_bitstream," NL=%.2f",ppcinfo->m_pffltFexScaleFacNoise[iBand]);
            }
        }
        fflush(fplrfex_bitstream);
    }
#endif
}

#ifdef BUILD_WMAPROLBRV3
WMARESULT freqexDecodeGlobalParamV3( CAudioObjectDecoder       *paudec,
                                     FexGlobalParamUpdateType  iUpdateType )
{
    CAudioObject    *pau = paudec->pau;
    Fex             *pfx = &(pau->m_fex);
    FexGlobalParam  *pfxgp;
    Int             iMv, iDiff;
    U32             uVal, uUpdateFlag, uUpdateListFrame0, uUpdateListTile0, uUpdateListMask;
    Bool            bDiffCoding, bRegularCoding;
    WMARESULT       wmaResult = WMA_OK;

    if( pfx->m_bReconDomain )
        pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    else
        pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);

    uUpdateFlag = 0;
    uUpdateListFrame0 = uUpdateListTile0 = 0;
    bDiffCoding = WMAB_FALSE;
    switch( iUpdateType )
    {
        case FexGlobalParamUpdateFull:
            uUpdateFlag = FEX_GLOBALPARAM_MASK_LISTFRAME - 1;

        case FexGlobalParamUpdateList:
            uUpdateFlag |= FEX_GLOBALPARAM_MASK_LISTFRAME;
            uUpdateListFrame0 = FEX_GLOBALPARAM_MASK_LISTFRAME - 1;

        case FexGlobalParamUpdateTileList:
            uUpdateFlag |= FEX_GLOBALPARAM_MASK_LISTTILE;
            uUpdateListTile0 = pfxgp->m_uUpdateListFrame;
            break;

        case FexGlobalParamUpdateFrame:
            // take out flags which is on tile level 
            uUpdateFlag = pfxgp->m_uUpdateListFrame & ~(pfxgp->m_uUpdateListTile);
            bDiffCoding = WMAB_TRUE;
            break;

        case FexGlobalParamUpdateTile:
            uUpdateFlag = pfxgp->m_uUpdateListTile;
            bDiffCoding = WMAB_TRUE;
            break;

        default:
            TRACEWMA_EXIT( wmaResult, WMA_E_FAIL );
            break;
    }

    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MVBINS )
    {
        // MvBins multiplier
        PLUS_GETBITS( wmaResult, 3, &uVal );
        pfxgp->m_iMvBinsIndex = (Int)uVal;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MVCBSET )
    {
        // Codebook set
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
        {
            pfxgp->m_iMvCodebookSet = 0;
        }
        else
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
                pfxgp->m_iMvCodebookSet = 1;
            else
                pfxgp->m_iMvCodebookSet = 2;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MVCB )
    {
        // MvCodebook
        if( pfxgp->m_iMvCodebookSet == 0 )
        {
            pfxgp->m_iMvCodebook = -1;
            PLUS_GETBITS( wmaResult, 1, &uVal );    // noise floor
            pfxgp->m_bEnableNoiseFloor = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            PLUS_GETBITS( wmaResult, 1, &uVal );    // exponent
            pfxgp->m_bEnableExponent = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            PLUS_GETBITS( wmaResult, 1, &uVal );    // sign
            pfxgp->m_bEnableSign = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            PLUS_GETBITS( wmaResult, 1, &uVal );    // reverse
            pfxgp->m_bEnableReverse = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        }
        else
        {
            PLUS_GETBITS( wmaResult, 2, &uVal );
            if( uVal == 3 )
            {
                if( pfxgp->m_iMvCodebookSet == 1 )
                {
                    PLUS_GETBITS( wmaResult, 2, &uVal );
                    uVal += 12;
                }
                else
                {
                    PLUS_GETBITS( wmaResult, 3, &uVal );
                    uVal += 24;
                }
            }
            for( iMv = 0; iMv < g_cNumMvCodebooks; iMv++ )
            {
                if( (pfxgp->m_iMvCodebookSet == 1 && g_rgMvCodebook[iMv].m_iIndexWithNoiseFloor == (Int)uVal) ||
                    (pfxgp->m_iMvCodebookSet == 2 && g_rgMvCodebook[iMv].m_iIndexWithoutNoiseFloor == (Int)uVal) )
                    break;
            }
            if( iMv == g_cNumMvCodebooks )
            {
                wmaResult = WMA_E_FAIL;
                goto exit;
            }
            pfxgp->m_iMvCodebook = iMv;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_USERNDNS )
    {
        // random noise
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bUseRandomNoise = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_NFTHR )
    {
        // noise floor threshold
        PLUS_GETBITS( wmaResult, 2, &uVal );
        pfxgp->m_iNoiseFloorThresh = uVal;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MVRANGE )
    {
        // Mv range type
        PLUS_GETBITS( wmaResult, 2, &uVal );
        pfxgp->m_iMvRangeType = uVal;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MVRES )
    {
        // Mv resolution type
        PLUS_GETBITS( wmaResult, 2, &uVal );
        pfxgp->m_iMvResType = uVal;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_RECCB )
    {
        // Mv recursive
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bRecursiveCwGeneration = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        // Mv recursive width
        if( pfxgp->m_bRecursiveCwGeneration )
        {
            PLUS_GETBITS( wmaResult, 2, &uVal );
            pfxgp->m_iKHzRecursiveCwWidth = uVal + 1;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_SINGLEMV )
    {
        // Single mv
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bUseSingleMv = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_SCALESS )
    {
        // Scale factor stepsize
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_iScFacStepSize = (uVal == 0) ? 1 : 3;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_SCSPLIT )
    {
        // band split
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bScaleBandSplitV2 = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_SCMVBANDS )
    {
        // band configurations
        pfxgp->m_bUseUniformScaleBands     = WMAB_FALSE;
        pfxgp->m_bArbitraryScaleBandConfig = WMAB_FALSE;
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
        {
            bRegularCoding = WMAB_TRUE;
            if( bDiffCoding )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 0 )
                    bRegularCoding = WMAB_FALSE; // no change
            }
            if( bRegularCoding )
                TRACEWMA_EXIT( wmaResult, freqexDecodeNumScMvBands( paudec, pfx, pfxgp ) );
        }
        else
        {
            TRACEWMA_EXIT( wmaResult, freqexDecodeArbitraryUniformBandConfig( paudec, pfx, pfxgp ) );
        }
        pfxgp->m_bNoArbitraryUniformConfig = (!pfxgp->m_bUseUniformScaleBands && 
                                              !pfxgp->m_bArbitraryScaleBandConfig);
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MINFREQ )
    {
        // start fex freq
        bRegularCoding = WMAB_TRUE;
        if( bDiffCoding )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                // uVal=0 -> no change
                if( uVal == 1 )
                {
                    // diff coding
                    PLUS_GETBITS( wmaResult, 2, &uVal );
                    iDiff = (Int)(uVal + 1) * 250;
                    PLUS_GETBITS( wmaResult, 1, &uVal );
                    if( uVal == 1 )
                        iDiff = -iDiff;
                    pfxgp->m_iMinFreq += iDiff;
                }
                bRegularCoding = WMAB_FALSE;
            }
            // uVal=1 means regular coding
        }
        
        if ( pfxgp->m_iMinFreq < 0 )
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

        if( bRegularCoding )
            TRACEWMA_EXIT( wmaResult, freqexDecodeFreqV2( paudec, &pfxgp->m_iMinFreq ) );
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MAXFREQ )
    {
        // end fex freq
        bRegularCoding = WMAB_TRUE;
        if( bDiffCoding )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                // uVal=0 -> no change
                if( uVal == 1 )
                {
                    // diff coding
                    PLUS_GETBITS( wmaResult, 2, &uVal );
                    iDiff = (Int)(uVal + 1) * 250;
                    PLUS_GETBITS( wmaResult, 1, &uVal );
                    if( uVal == 1 )
                        iDiff = -iDiff;
                    pfxgp->m_iMaxFreq += iDiff;
                }
                bRegularCoding = WMAB_FALSE;
            }
            // uVal=1 means regular coding
        }
        if( bRegularCoding )
        {
            TRACEWMA_EXIT( wmaResult, freqexDecodeFreqV2( paudec, &pfxgp->m_iMaxFreq ) );
            pfxgp->m_iMaxFreq = pau->m_iSamplingRate / 2 - pfxgp->m_iMaxFreq;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_USECB3 )
    {
        // flag for cb=4
        PLUS_GETBITS( wmaResult, 1, &uVal );
        pfxgp->m_bUseCb4 = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_IMPLCT_BSSPLIT )
    {
        if( pfx->m_bReconDomain )
        {
            // base split
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfxgp->m_bBaseBandSplitV2 = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        }
        else
        {
            // flag to specify implicit/exlicit start position
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfxgp->m_bUseImplicitStartPos = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MNZERO_BSBANDS )
    {
        if( pfx->m_bReconDomain )
        {
            // #BaseBands
            bRegularCoding = WMAB_TRUE;
            if( bDiffCoding )
            {
                if( !pau->m_bTileReconBs )
                {
                    pfxgp->m_cBaseBands = 0;
                    bRegularCoding = WMAB_FALSE;
                }
                else
                {
                    PLUS_GETBITS( wmaResult, 1, &uVal );
                    if( uVal == 0 )
                        bRegularCoding = WMAB_FALSE; // no change
                }
            }
            if( bRegularCoding )
            {
                uVal = 1;
                if( !bDiffCoding )
                {
                    PLUS_GETBITS( wmaResult, 1, &uVal );
                }
                if( uVal == 0 )
                {
                    pfxgp->m_cBaseBands = 0;
                }
                else
                {
                    // #BaseBands
                    PLUS_GETBITS( wmaResult, (UInt)pfx->m_cBandsBits, &uVal );
                    pfxgp->m_cBaseBands = uVal + 1;
                }
            }
        }
        else
        {
            // encode min # of zeros for overlay
            PLUS_GETBITS( wmaResult, 3, &uVal );
            pfxgp->m_cMinRunOfZerosForOverlayIndex = uVal;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_MXZERO_BSMXFRQ )
    {
        if( pfx->m_bReconDomain )
        {
            // max base freq
            bRegularCoding = WMAB_TRUE;
            if( bDiffCoding )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 0 )
                {
                    PLUS_GETBITS( wmaResult, 1, &uVal );
                    // uVal=0 -> no change
                    if( uVal == 1 )
                    {
                        // diff coding
                        PLUS_GETBITS( wmaResult, 2, &uVal );
                        iDiff = (Int)(uVal + 1) * 250;
                        PLUS_GETBITS( wmaResult, 1, &uVal );
                        if( uVal == 1 )
                            iDiff = -iDiff;
                        pfxgp->m_iMaxBaseFreq += iDiff;
                    }
                    bRegularCoding = WMAB_FALSE;
                }
                // uVal=1 means regular coding
            }
            if( bRegularCoding )
            {
                TRACEWMA_EXIT( wmaResult, freqexDecodeFreqV2( paudec, &pfxgp->m_iMaxBaseFreq ) );
                pfxgp->m_iMaxBaseFreq = pau->m_iSamplingRate / 2 - pfxgp->m_iMaxBaseFreq;
            }
        }
        else
        {
            // encode min # of zeros for overlay
            PLUS_GETBITS( wmaResult, 3, &uVal );
            pfxgp->m_cMaxRunOfZerosPerBandForOverlayIndex = uVal;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_OVRLY_BSSS )
    {
        if( pfx->m_bReconDomain )
        {
            // base step size
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfxgp->m_iBaseFacStepSize = (uVal == 0) ? 1 : 3;
        }
        else
        {
            // overlay
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfxgp->m_bOverlay = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_HFEND )
    {
        if( !pfx->m_bReconDomain )
        {
            // hole fill end condition
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfxgp->m_iEndHoleFillConditionIndex = (Int)uVal;
            if( uVal == 1 )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                pfxgp->m_iEndHoleFillConditionIndex += (Int)uVal;
            }
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_V1COMP )
    {
        if( !pfx->m_bReconDomain )
        {
            // v1 compatible switch
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfxgp->m_bEnableV1Compatible = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            if( pfxgp->m_bEnableV1Compatible )
            {
                PLUS_GETBITS( wmaResult, 3, &uVal );
                pfxgp->m_iScBinsIndex = (Int)uVal;
            }
        }
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_LISTFRAME )
    {
        // update frame list
        pfxgp->m_uUpdateListFrame = 0;
        uUpdateListMask = 0x1;
        while( uUpdateListFrame0 )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 1 )
                pfxgp->m_uUpdateListFrame |= uUpdateListMask;
            uUpdateListFrame0 >>= 1;
            uUpdateListMask <<= 1;
        }
        uUpdateListTile0 = pfxgp->m_uUpdateListFrame;
    }
    if( uUpdateFlag & FEX_GLOBALPARAM_MASK_LISTTILE )
    {
        // update tile list
        pfxgp->m_uUpdateListTile = 0;
        uUpdateListMask = 0x1;
        while( uUpdateListTile0 )
        {
            if( uUpdateListTile0 & 0x1 )
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 1 )
                    pfxgp->m_uUpdateListTile |= uUpdateListMask;
            }
            uUpdateListTile0 >>= 1;
            uUpdateListMask <<= 1;
        }
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeAndGetCodingTileConfigV3( CAudioObjectDecoder *paudec,
                                                  Int cSubFrameSampleHalf )
{
    CAudioObject   *pau = paudec->pau;
    Fex            *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexCodingGlobalParamFrame]);
    Int            i;
    U32            uVal;
    Bool           bDoneUpdateFull = WMAB_FALSE;
    WMARESULT      wmaResult = WMA_OK;
    PerChannelInfoShr *pcis;
    FexGlobalParamUpdateType iFexGlobalParamUpdate = FexGlobalParamUpdateNo;

#ifdef FEX_LOWRATE_DEBUG
    if(fplrfex_bitstream==NULL)fplrfex_bitstream=fopen("debuglrfexdecbit.txt","wb");
    if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n\nFrame=%d cSubframe=%d Size=%d",pau->m_iFrameNumber,pau->m_iCurrTile,cSubFrameSampleHalf);fflush(fplrfex_bitstream);}
#endif

    uVal = 0;
    if( pfx->m_bFirstTileV2Coding )
    {
        // GlobalParam update
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 1 )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            if( uVal == 0 )
            {
                iFexGlobalParamUpdate = FexGlobalParamUpdateTileList;
            }
            else
            {
                PLUS_GETBITS( wmaResult, 1, &uVal );
                if( uVal == 0 )
                {
                    iFexGlobalParamUpdate = FexGlobalParamUpdateList;
                }
                else
                {
                    iFexGlobalParamUpdate = FexGlobalParamUpdateFull;
                    bDoneUpdateFull = WMAB_TRUE;
                }
            }
            TRACEWMA_EXIT( wmaResult, 
                freqexDecodeGlobalParamV3( paudec, iFexGlobalParamUpdate ) );
        }

        if( !bDoneUpdateFull )
        {
            TRACEWMA_EXIT( wmaResult, 
                freqexDecodeGlobalParamV3( paudec, FexGlobalParamUpdateFrame ) );
        }

#ifdef FEX_LOWRATE_DEBUG
        if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n cFrameGrobalParam: %s  FrmList=%d TileList=%d",globalupdatetype[iFexGlobalParamUpdate],pfxgp->m_uUpdateListFrame,pfxgp->m_uUpdateListTile);fflush(fplrfex_bitstream);}
#endif

        pfx->m_bFirstTileV2Coding = WMAB_FALSE;

        pfx->m_bV1Compatible = WMAB_FALSE;
        if( pfxgp->m_bEnableV1Compatible )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfx->m_bV1Compatible = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
            if( pfx->m_bV1Compatible )
            {
                pfx->m_cScaleDefaultBins = freqexIndexToScaleBins( pfxgp->m_iScBinsIndex );
                pfx->m_iPrevScBinsMultiplier = 0;
                freqexSetScBins( pfx );
                pfx->m_cMvDefaultBins = freqexIndexToMvBins( pfxgp->m_iMvBinsIndex );
                pfx->m_iPrevMvBinsMultiplier = 0;
                freqexSetMvBins( pfx );

                TRACEWMA_EXIT( wmaResult, freqexDecodeAndGetTileConfig( paudec, cSubFrameSampleHalf ) );
                goto exit;
            }
        }

    }

    if( pfx->m_bV1Compatible )
    {
        pfx->m_cScaleDefaultBins = freqexIndexToScaleBins( pfxgp->m_iScBinsIndex );
        pfx->m_iPrevScBinsMultiplier = 0;
        freqexSetScBins( pfx );
        pfx->m_cMvDefaultBins = freqexIndexToMvBins( pfxgp->m_iMvBinsIndex );
        pfx->m_iPrevMvBinsMultiplier = 0;
        freqexSetMvBins( pfx );

        TRACEWMA_EXIT( wmaResult, freqexDecodeAndGetTileConfig( paudec, cSubFrameSampleHalf ) );
        goto exit;
    }

    if( !bDoneUpdateFull )
    {
        TRACEWMA_EXIT( wmaResult, 
            freqexDecodeGlobalParamV3( paudec, FexGlobalParamUpdateTile ) );
    }

    pfx->m_bOverlayOnly = WMAB_FALSE;
    if( pfx->m_iVersion == 2 )
    {
        if( !pfxgp->m_bUseImplicitStartPos || pfxgp->m_bOverlay )
        {
            PLUS_GETBITS( wmaResult, 1, &uVal );
            pfx->m_bOverlayOnly = (uVal == 1) ? 1 : 0;
        }
    }

    if( pfxgp->m_iMvCodebookSet == 0 )
    {
        TRACEWMA_EXIT( wmaResult, freqexDecodeMvCbSet0( paudec, pfx, pfxgp ) );
    }
    else
    {
        for( i = 0; i < pfx->m_nChCode; i++ )
        {
            pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];

            pcis->m_bFxUseNoiseFloor = WMAB_TRUE;
            pcis->m_bFxUseExponent = WMAB_TRUE;
            pcis->m_bFxUseSign = WMAB_TRUE;
            pcis->m_bFxUseReverse = WMAB_TRUE;
        }
    }

    pfx->m_bUseSingleMv = pfxgp->m_bUseSingleMv;
    if( pfx->m_bUseSingleMv )
        pfx->m_iNumMvChannels = 1;
    else
        pfx->m_iNumMvChannels = pfx->m_nChCode;

    // parameter setting
    pfx->m_cSubtiles = 1;
    pfx->m_cSubFrameSampleHalf = cSubFrameSampleHalf;
    pfx->m_cTileSize = pfx->m_cSubFrameSampleHalf;
    pfx->m_cOrigEnd = pfx->m_cEnd;
    pfx->m_iExplicitStartPos = (2 * pfxgp->m_iMinFreq * pfx->m_cSubFrameSampleHalf / pau->m_iSamplingRate);

    for (i=0; i < pfx->m_nChCode; i++)
    {
        pcis = pau->m_rgpcinfoShr + pfx->m_rgiChCode[i];
        pcis->m_iFxBandConfig = 0;
    }

exit:
    return wmaResult;
}

WMARESULT   freqexDecodeReconTileConfigV3( CAudioObjectDecoder *paudec )
{
    CAudioObject   *pau = paudec->pau;
    Fex            *pfx = &(pau->m_fex);
    FexGlobalParam *pfxgp = &(pfx->m_rgGlobalParam[FexReconGlobalParamFrame]);
    Int            i;
    U32            uVal;
    Bool           bDoneUpdateFull = WMAB_FALSE;
    WMARESULT      wmaResult = WMA_OK;
    FexGlobalParamUpdateType iFexGlobalParamUpdate = FexGlobalParamUpdateNo;

    // GlobalParam update
    PLUS_GETBITS( wmaResult, 1, &uVal );
    if( uVal == 1 )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 0 )
        {
            iFexGlobalParamUpdate = FexGlobalParamUpdateList;
        }
        else
        {
            iFexGlobalParamUpdate = FexGlobalParamUpdateFull;
            bDoneUpdateFull = WMAB_TRUE;
        }
        TRACEWMA_EXIT( wmaResult, 
            freqexDecodeGlobalParamV3( paudec, iFexGlobalParamUpdate ) );
    }

    if( !bDoneUpdateFull )
    {
        TRACEWMA_EXIT( wmaResult, 
            freqexDecodeGlobalParamV3( paudec, FexGlobalParamUpdateFrame ) );
    }

    if( pfxgp->m_cScaleBands + pfxgp->m_cBaseBands > pfx->m_cMaxBands )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
    }

    for (i=0; i < pau->m_cChInTile; i++)
        *(pau->m_rgpcinfo[pau->m_rgiChInTile[i]].m_pcFexSubframesMvMerged) = 0;

#ifdef FEX_LOWRATE_DEBUG
        if(fplrfex_bitstream==NULL)fplrfex_bitstream=fopen("debuglrfexdecbit.txt","wb");
        if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n\nFrame=%d rSubframe=%d",pau->m_iFrameNumber,pau->m_iCurrTile);fflush(fplrfex_bitstream);}
        if(fplrfex_bitstream){fprintf(fplrfex_bitstream,"\n rFrameGrobalParam: %s  FrmList=%d TileList=%d",globalupdatetype[iFexGlobalParamUpdate],pfxgp->m_uUpdateListFrame,pfxgp->m_uUpdateListTile);fflush(fplrfex_bitstream);}
#endif

    pfx->m_bUseSingleMv = pfxgp->m_bUseSingleMv;

exit:
    return wmaResult;
}

#include "basepluspro.h"
extern U16 gNLQDecTblSize9;
extern FPNLQ gNLQDecTbl9[];
extern U16 gNLQDecTblSize8;
extern FPNLQ gNLQDecTbl8[];
extern U16 gNLQDecTblSize7;
extern FPNLQ gNLQDecTbl7[];
extern U16 gNLQDecTblSize6;
extern FPNLQ gNLQDecTbl6[];

#ifdef DBG_BASE_PEAK
FILE *g_bpf_file = NULL;
FILE *g_bpi_file = NULL;
#endif

Void bpeakClearPeakCoef( PerChannelInfo *ppcinfo, Int iMaxPeakCoef )
{
    Int iCoef;

    for( iCoef = 0; iCoef < iMaxPeakCoef; iCoef++ )
        ppcinfo->m_piBasePeakCoefPos[iCoef] = -1;
    *(ppcinfo->m_pcBasePeakCoefs) = 0;
}

WMARESULT bpeakDecodeTile_Channel( CAudioObjectDecoder *paudec,
                                   PerChannelInfo *ppcinfo )
{
    CAudioObject         *pau = paudec->pau;
    Int                  iCoef, iCoefPred, iCoef1, iShift, iLevel, iPos, iMask, iBand;
    Int                  cBitsRun, cMaxBitsRun, iOffsetZeroRun, cBasePeakIndCoefs, iLastCodedIndex, *piMaskQ;
    CoefType             fPeakCoef0, fPeakCoef1, *pCoefRecon;
    U32                  uVal, uBitCnt;
    Bool                 bConstrainedZeroRun, bEnableShortZeroRun;
    BasePeakCoefPredType iBasePeakCoefPred;
    WMARESULT            wmaResult = WMA_OK;

    // decode mask
    PLUS_GETDATA( wmaResult,
                    huffDecGet( g_bpeakMaskDeltaHuffDec,
                                paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
    ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
    if( uVal == g_bpeakMaxMaskDelta - g_bpeakMinMaskDelta + 2 )
    {
        // - escape coding
        PLUS_GETBITS( wmaResult, 3, &uVal );
        iMask = (g_bpeakMinMaskDelta - 1 - (Int)uVal);
    }
    else if( uVal == g_bpeakMaxMaskDelta - g_bpeakMinMaskDelta + 1 )
    {
        // + escape coding
        PLUS_GETBITS( wmaResult, 3, &uVal );
        iMask = (g_bpeakMaxMaskDelta + 1 + (Int)uVal);
    }
    else
    {
        // normal
        iMask = (g_bpeakMinMaskDelta + (Int)uVal);
    }
    // modify mask values and store original for retrieving after recon
    if( pau->m_fBasePlusPresentTile )
    {
        // get mask from base+
        piMaskQ = ppcinfo->m_rgiSFQ;
        ppcinfo->m_iBasePeakBarkStart = 
            bpeakGetBasePeakBarkStart_BasePlus( pau->m_pbp, pau->m_cBasePeakLastCodedIndex );
        iBand = max( ppcinfo->m_iBasePeakBarkStart - 1, 0 );
        iMask += piMaskQ[iBand];
        memcpy( ppcinfo->m_piBasePeakMaskQSave, piMaskQ, pau->m_pbp->m_cValidSFBand * sizeof( Int ) );
        for( iBand = ppcinfo->m_iBasePeakBarkStart; iBand < pau->m_pbp->m_cValidSFBand; iBand++ )
            piMaskQ[iBand] = iMask;
    }
    else
    {
        // get mask from base
        if( ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0] )
            piMaskQ = ppcinfo->m_rgiMaskQ;
        else
            piMaskQ = ppcinfo->m_rgiMaskQResampled;
        ppcinfo->m_iBasePeakBarkStart = 
            bpeakGetBasePeakBarkStart( pau, pau->m_cBasePeakLastCodedIndex );
        iBand = max( ppcinfo->m_iBasePeakBarkStart - 1, 0 );
        iMask += piMaskQ[iBand];
        memcpy( ppcinfo->m_piBasePeakMaskQSave, piMaskQ, pau->m_cValidBarkBand * sizeof( Int ) );
        for( iBand = ppcinfo->m_iBasePeakBarkStart; iBand < pau->m_cValidBarkBand; iBand++ )
            piMaskQ[iBand] = iMask;
    }

    if( ppcinfo->m_iPower == 0 )
    {
        bpeakClearPeakCoef( ppcinfo, pau->m_iMaxBasePeakCoef );
        goto exit;
    }

    // decode mode
    PLUS_GETBITS( wmaResult, 2, &uVal );
    switch( uVal )
    {
        case 0: iBasePeakCoefPred = BasePeakCoefNo;              break;
        case 1: iBasePeakCoefPred = BasePeakCoefInd;             break;
        case 2: iBasePeakCoefPred = BasePeakCoefInterPred;       break;
        case 3: iBasePeakCoefPred = BasePeakCoefInterPredAndInd; break;
        default: wmaResult = WMA_E_FAIL; goto exit;              break;
    }

    if( (iBasePeakCoefPred == BasePeakCoefInterPred ||
         iBasePeakCoefPred == BasePeakCoefInterPredAndInd) &&
         *(ppcinfo->m_pcBasePeakCoefs) == 0 )
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
    }

    if( iBasePeakCoefPred == BasePeakCoefNo )
    {
        bpeakClearPeakCoef( ppcinfo, pau->m_iMaxBasePeakCoef );
        goto exit;
    }

    // decode quantizer
    if( pau->m_bBasePeakFirstTile )
    {
        PLUS_GETBITS( wmaResult, 2, &uVal );
        switch( uVal )
        {
            case 0: pau->m_pBasePeakNLQDecTbl = gNLQDecTbl9;
                    pau->m_iBasePeakNLQDecTblSize = gNLQDecTblSize9; break;
            case 1: pau->m_pBasePeakNLQDecTbl = gNLQDecTbl8;
                    pau->m_iBasePeakNLQDecTblSize = gNLQDecTblSize8; break;
            case 2: pau->m_pBasePeakNLQDecTbl = gNLQDecTbl7;
                    pau->m_iBasePeakNLQDecTblSize = gNLQDecTblSize7; break;
            case 3: pau->m_pBasePeakNLQDecTbl = gNLQDecTbl6;
                    pau->m_iBasePeakNLQDecTblSize = gNLQDecTblSize6; break;
            default: wmaResult = WMA_E_FAIL; goto exit;              break;
        }
        pau->m_bBasePeakFirstTile = WMAB_FALSE;
    }

    // resample peaks
    bpeakResamplePeakPos( ppcinfo, (I16)pau->m_cFrameSampleHalf, ppcinfo->m_cSubFrameSampleHalf );

    // decode shape codebook
    PLUS_GETBITS( wmaResult, 1, &uVal );
    ppcinfo->m_iBasePeakShapeCB = (Int)uVal;
    if( uVal == 1 )
    {
        PLUS_GETBITS( wmaResult, 1, &uVal );
        ppcinfo->m_iBasePeakShapeCB += (Int)uVal;
    }

    // decode inter-pred positions
    iCoefPred = 0;
    if( iBasePeakCoefPred == BasePeakCoefInterPred ||
        iBasePeakCoefPred == BasePeakCoefInterPredAndInd )
    {
        for( iCoef = 0; iCoef < *(ppcinfo->m_pcBasePeakCoefs); iCoef++ )
        {
            // shift
            PLUS_GETDATA( wmaResult,
                          huffDecGet( g_bpeakCoefShiftHuffDec,
                                      paudec->m_pibsPlus, &uBitCnt, &uVal, NULL) );
            ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
            iShift = (Int)uVal - g_bpeakShiftRange;

            if( iShift == g_bpeakShiftRange + 1 )
                continue; // this peak dies out
            ppcinfo->m_piBasePeakCoefPos[iCoefPred] =
                        ppcinfo->m_piBasePeakCoefPos[iCoef] + (I16)iShift;
            iCoefPred++;
        }
    }
    *(ppcinfo->m_pcBasePeakCoefs) = iCoefPred;

    // decode individual positions
    if( iBasePeakCoefPred == BasePeakCoefInd ||
        iBasePeakCoefPred == BasePeakCoefInterPredAndInd )
    {
        if( pau->m_iMaxBasePeakCoef - *(ppcinfo->m_pcBasePeakCoefs) <= 0 )
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
        }

        // decode # of coefs
        cBitsRun = min( 3, CEILLOG2( pau->m_iMaxBasePeakCoef - *(ppcinfo->m_pcBasePeakCoefs) ) );
        uVal = 0;
        if( cBitsRun > 0 )
            PLUS_GETBITS( wmaResult, cBitsRun, &uVal );
        cBasePeakIndCoefs = (Int)uVal + 1;
        if( uVal == 7 )
        {
            // escape
            cBitsRun = CEILLOG2( pau->m_iMaxBasePeakCoef - *(ppcinfo->m_pcBasePeakCoefs) - 8 );
            if( cBitsRun > 0 )
                PLUS_GETBITS( wmaResult, cBitsRun, &uVal );
            cBasePeakIndCoefs += (Int)uVal;
        }

        if( cBasePeakIndCoefs + *(ppcinfo->m_pcBasePeakCoefs) > pau->m_iMaxBasePeakCoef )
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
        }

        // decode flag to enable short run
        PLUS_GETBITS( wmaResult, 1, &uVal );
        bEnableShortZeroRun = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
        // decode flag to constrain zero-run length
        PLUS_GETBITS( wmaResult, 1, &uVal );
        bConstrainedZeroRun = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;

        cMaxBitsRun = LOG2( ppcinfo->m_cSubFrameSampleHalf >> 3 );
        iOffsetZeroRun = 0;
        if( bEnableShortZeroRun )
            iOffsetZeroRun = 3;

        // decode zero-run coding
        iLastCodedIndex = pau->m_cBasePeakLastCodedIndex - 1;
        for( iCoef = iCoefPred = 0; iCoef < cBasePeakIndCoefs; iCoef++ )
        {
            if( iLastCodedIndex >= ppcinfo->m_cSubFrameSampleHalf )
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
            }
            // get #bits
            cBitsRun = CEILLOG2( ppcinfo->m_cSubFrameSampleHalf - iLastCodedIndex - 1 - iOffsetZeroRun );
            if( bConstrainedZeroRun )
                cBitsRun = min( cBitsRun, cMaxBitsRun );

            if( bEnableShortZeroRun )
            {
                PLUS_GETBITS( wmaResult, 2, &uVal );
                iLastCodedIndex += (Int)uVal + 1;
                if( uVal == 3 )
                {
                    // escape
                    uVal = 0;
                    if( cBitsRun > 0 )
                        PLUS_GETBITS( wmaResult, cBitsRun, &uVal );
                    iLastCodedIndex += uVal;
                }
            }
            else
            {
                uVal = 0;
                if( cBitsRun > 0 )
                    PLUS_GETBITS( wmaResult, cBitsRun, &uVal );
                iLastCodedIndex += uVal + 1;
            }

            // find insertion index
            while( iCoefPred < *(ppcinfo->m_pcBasePeakCoefs) )
            {
                if( iLastCodedIndex < ppcinfo->m_piBasePeakCoefPos[iCoefPred] )
                    break;
                iCoefPred++;
            }
            // shift buffer
            for( iCoef1 = *(ppcinfo->m_pcBasePeakCoefs); iCoef1 > iCoefPred; iCoef1-- )
                ppcinfo->m_piBasePeakCoefPos[iCoef1] = ppcinfo->m_piBasePeakCoefPos[iCoef1-1];
            // insert new peak
            ppcinfo->m_piBasePeakCoefPos[iCoefPred] = (I16)iLastCodedIndex;
            (*(ppcinfo->m_pcBasePeakCoefs))++;
        }
    }

    // set pointer to recon buffer
    if( pau->m_fBasePlusPresentTile )
        pCoefRecon = ppcinfo->m_rgBPCoef;
    else
        pCoefRecon = ppcinfo->m_rgCoefRecon;

    iLastCodedIndex = pau->m_cBasePeakLastCodedIndex - 1;
    for( iCoef = 0; iCoef < *(ppcinfo->m_pcBasePeakCoefs); iCoef++ )
    {
        // level
        PLUS_GETDATA( wmaResult,
                        huffDecGet( g_bpeakCoefLevelHuffDec,
                                    paudec->m_pibsPlus, &uBitCnt, &uVal, NULL ) );
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
        iLevel = (Int)uVal + 1;
        if( iLevel == g_bpeakMaxLevel + 1 )
        {
            // escape coding
            cBitsRun = 4;
            PLUS_GETBITS( wmaResult, cBitsRun, &uVal );
            iLevel += (Int)uVal;
        }
        if( iLevel < pau->m_iBasePeakNLQDecTblSize )
        {
            fPeakCoef0 = pau->m_pBasePeakNLQDecTbl[iLevel];
        }
        else
        {
            FPNLQ fpNLQDist = pau->m_pBasePeakNLQDecTbl[pau->m_iBasePeakNLQDecTblSize-1] - 
                              pau->m_pBasePeakNLQDecTbl[pau->m_iBasePeakNLQDecTblSize-2];

            fPeakCoef0 = (pau->m_pBasePeakNLQDecTbl[pau->m_iBasePeakNLQDecTblSize-1] 
                            + (iLevel-(pau->m_iBasePeakNLQDecTblSize-1)) * fpNLQDist);
        }

        // shape
        switch( ppcinfo->m_iBasePeakShapeCB )
        {
            case 0:
                uVal = 0; uBitCnt = 0;
                break;
            case 1: 
                PLUS_GETDATA( wmaResult,
                              huffDecGet( g_bpeakShapeCB1HuffDec,
                                          paudec->m_pibsPlus, &uBitCnt, &uVal, NULL ) );
                if( uVal > 3 )
                {
                    wmaResult = WMA_E_FAIL;
                    goto exit;
                }
                break;
            case 2: 
                PLUS_GETDATA( wmaResult,
                              huffDecGet( g_bpeakShapeCB2HuffDec,
                                          paudec->m_pibsPlus, &uBitCnt, &uVal, NULL ) );
                if( uVal > 6 )
                {
                    wmaResult = WMA_E_FAIL;
                    goto exit;
                }
                break;
            default:
                wmaResult = WMA_E_FAIL;
                goto exit;
                break;
        }
        ASSERTWMA_EXIT( wmaResult, ibstrmFlushBits( paudec->m_pibsPlus, uBitCnt ) );
        TRACEWMA_EXIT( wmaResult, 
                       bpeakGetShape( (Int)uVal, fPeakCoef0, &fPeakCoef0, &fPeakCoef1 ) );

        // sign
        PLUS_GETBITS( wmaResult, 1, &uVal );
        if( uVal == 1 )
        {
            fPeakCoef0 = -fPeakCoef0;
            fPeakCoef1 = -fPeakCoef1;
        }

        // put coefs into recon buffer
        if( pCoefRecon )
        {
            iPos = ppcinfo->m_piBasePeakCoefPos[iCoef];
            if( iPos >= iLastCodedIndex )
            {

#ifdef  DBG_BASE_PEAK
#ifndef BUILD_INTEGER
                if( NULL == g_bpf_file ) g_bpf_file = fopen( "bpCoefs.flt", "wt" );
                fprintf( g_bpf_file, "%f\t%f\n", fPeakCoef0, fPeakCoef1 );
#else
                float flt0 = 0, flt1 = 0;

                const float int0 = (float)fPeakCoef0/(1<<FPNLQ_FRAC_BITS);
                const float int1 = (float)fPeakCoef1/(1<<FPNLQ_FRAC_BITS);

                if( NULL == g_bpf_file ) g_bpf_file = fopen( "bpCoefs.flt", "rt" );
                if( NULL == g_bpi_file ) g_bpi_file = fopen( "bpCoefs.int", "wt" );

                fscanf ( g_bpf_file, "%f\t%f\n", &flt0, &flt1 );
                fprintf( g_bpi_file, "%f\t%f\t%f\t%f\n", flt0, flt1, int0, int1 );

                //assert( fabs(flt0-int0) < 1 && fabs(flt1-int1) < 1 );
                fPeakCoef0 = ROUNDF(flt0*(1<<FPNLQ_FRAC_BITS));
                fPeakCoef1 = ROUNDF(flt1*(1<<FPNLQ_FRAC_BITS));

                initFP();
#endif
#endif // DBG_BASE_PEAK

                // instead of looking at ppcinfo->m_cLastCodedIndex,
                // iLastCodedIndex makes it possible for next peak to overwrite privious peaks
                if( iPos < ppcinfo->m_cSubFrameSampleHalf )
                {
                    pCoefRecon[iPos] = COEF_FROM_FPNLQ( fPeakCoef0 );
                    ppcinfo->m_cLastCodedIndex = (U16)iPos + 1;
#if defined(BUILD_WMAPROLBRV1)
                    if( pau->m_bNeedMaskProc &&
                        !pau->m_fBasePlusPresentTile )
                        freqexSetNonzeroMask( pau, iPos );
#endif
                }
                iPos++;
                if( iPos < ppcinfo->m_cSubFrameSampleHalf && fPeakCoef1 != 0 )
                {
                    pCoefRecon[iPos] = COEF_FROM_FPNLQ( fPeakCoef1 );
                    ppcinfo->m_cLastCodedIndex = (U16)iPos + 1;
#if defined(BUILD_WMAPROLBRV1)
                    if( pau->m_bNeedMaskProc &&
                        !pau->m_fBasePlusPresentTile )
                        freqexSetNonzeroMask( pau, iPos );
#endif
                }
            }
            iLastCodedIndex = iPos;
        }
    }

    // resample back to full-size domain for next tile
    bpeakResamplePeakPos( ppcinfo,  ppcinfo->m_cSubFrameSampleHalf, (I16)pau->m_cFrameSampleHalf );

exit:
    return wmaResult;
}
#endif
