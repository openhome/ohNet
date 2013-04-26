//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#if (DNMIX_INT==1)

#define prvChannelDownMixType prvChannelDownMixInt
#define prvChannelDownMixLtRt prvChannelDownMixLtRtInt
#ifdef CHANFLDDN_PREPCM
#define rgpbTemp m_ppcbtTemp
#define GET_COEFF(ch) (CoefType)paudec->rgpbTemp[ch][iBlock]
#define DNMIXADVSRCPTR(i)
#define DNMIXADVDSTPTR(i)
#define SET_COEFF(sample, ch, i) paudec->rgpbTemp[ch][i] = sTemp;
#define SampleType CBT
#define DNMIXCLIP(x)
#ifdef BUILD_INTEGER
#define DNMIXROUND(x) ((SampleType)x)
#else
#define DNMIXROUND(x) (ROUNDF(x))
#endif
#else // CHANFLDDN_PREPCM
#define GET_COEFF(ch) (CoefType)PPPOSTGETSAMPLE(piSrc, ch)
#define DNMIXADVSRCPTR(i) PPPOSTADVPTR(piSrc, i)
#define DNMIXADVDSTPTR(i) PPPOSTADVPTR(piDst, i)
#define SET_COEFF(sample, ch, i) PPPOSTSETSAMPLE(sample, piDst, ch)
#define SampleType PCMSAMPLE
#define DNMIXCLIP(x) CLIP_PCMRANGE(x)
#ifdef BUILD_INTEGER
#define DNMIXROUND(x) ((SampleType)x)
#else // BUILD_INTEGER
#define DNMIXROUND(x) (ROUNDF(x))
#endif // BUILD_INTEGER
#endif // CHANFLDDN_PREPCM

#elif (DNMIX_INT==0)

#define prvChannelDownMixType prvChannelDownMixFloat
#define prvChannelDownMixLtRt prvChannelDownMixLtRtFloat
#ifdef CHANFLDDN_PREPCM
#define rgpbTemp m_rgpctTemp
#define GET_COEFF(ch) (CoefType)paudec->rgpbTemp[ch][iBlock]
#define DNMIXADVSRCPTR(i)
#define DNMIXADVDSTPTR(i)
#define SET_COEFF(sample, ch, i) paudec->rgpbTemp[ch][i] = sTemp;
#define SampleType CoefType
#define DNMIXCLIP(x)
#define DNMIXROUND(x) (x)
#else // CHANFLDDN_PREPCM
#ifdef BUILD_INTEGER
#define NOT_SUPPORTED
#else // BUILD_INTEGER
#define GET_COEFF(ch) pctSrc[ch]
#define DNMIXADVSRCPTR(i) pctSrc += i;
#define DNMIXADVDSTPTR(i) pctDst += i;
#define SET_COEFF(sample, ch, i) pctDst[ch] = sample;
#define SampleType CoefType
#define DNMIXCLIP(x)
#define DNMIXROUND(x) (x)
#endif // BUILD_INTEGER
#endif // CHANFLDDN_PREPCM

#endif // DNMIX_INT

#if defined(BUILD_WMAPRO)

WMARESULT prvChannelDownMixType(CAudioObjectDecoder *paudec, 
                            U8 *piSrc, 
                            Int nBlocks,
                            U8 *piDst)
{
#ifdef NOT_SUPPORTED
    return WMA_E_FAIL;
#else // NOT_SUPPORTED
    CAudioObject* pau     = paudec->pau;
    Int cSrcChannel       = pau->m_cChannel;
    Int cDstChannel       = paudec->m_cDstChannel;
    WMARESULT wmaResult   = WMA_OK;
    CoefType* pctTemp     = paudec->m_pctTemp;
    CoefType* pctSrc      = (CoefType*) piSrc;
    CoefType* pctDst      = (CoefType*) piDst;
    Int iBlock, iChSrc, iChDst;
    SampleType sTemp;

#ifdef BOOST_CHANFLDDN_POWER
    Float fltSrcChPower = 0.0F;
    Float fltDstChPower = 0.0F;
    CoefType ctMaxAbsSample = 0;
    Bool bComputeFoldDownGain = (pau->m_bPureLosslessMode == WMAB_FALSE && 
                                 paudec->m_bAuthorControlledChDnMixMtx == WMAB_FALSE &&
                                 paudec->m_fLtRtDownmix == WMAB_FALSE);
#endif
	
	if (!paudec->m_fChannelFoldDown)
    {
        goto exit;
    }

#ifdef TEST_VRHEADPHONE

    TRACEWMA_EXIT(wmaResult, AVRHeadphoneProcess (paudec->m_pVRHPhone, piSrc, nBlocks, piDst));
        //(paudec, (U8*) pbDst, nBlocks, (U8*) pbDst));

#else // So !TEST_VRHEADPHONE

    if (paudec->m_fLtRtDownmixNonnormal)
    {
        cDstChannel = 3; // LTRT_SRC_CHANNELS
    }

#ifdef CHANFLDDN_PREPCM
    for (iChSrc=0; iChSrc < cSrcChannel; iChSrc++)
    {
        paudec->rgpbTemp[iChSrc] = (SampleType*)pau->m_rgpcinfo[iChSrc].m_rgiPCMBuffer;
    }
#endif

    if (6 == cSrcChannel && 2 == cDstChannel)
    {
        // Unroll loop for popular scenario
        // Block transform: channel down mixing.
        ChDnMixType chdnMix00 = paudec->m_rgrgfltChDnMixMtx[0][0];
        ChDnMixType chdnMix01 = paudec->m_rgrgfltChDnMixMtx[0][1];
        ChDnMixType chdnMix02 = paudec->m_rgrgfltChDnMixMtx[0][2];
        ChDnMixType chdnMix03 = paudec->m_rgrgfltChDnMixMtx[0][3];
        ChDnMixType chdnMix04 = paudec->m_rgrgfltChDnMixMtx[0][4];
        ChDnMixType chdnMix05 = paudec->m_rgrgfltChDnMixMtx[0][5];
        ChDnMixType chdnMix10 = paudec->m_rgrgfltChDnMixMtx[1][0];
        ChDnMixType chdnMix11 = paudec->m_rgrgfltChDnMixMtx[1][1];
        ChDnMixType chdnMix12 = paudec->m_rgrgfltChDnMixMtx[1][2];
        ChDnMixType chdnMix13 = paudec->m_rgrgfltChDnMixMtx[1][3];
        ChDnMixType chdnMix14 = paudec->m_rgrgfltChDnMixMtx[1][4];
        ChDnMixType chdnMix15 = paudec->m_rgrgfltChDnMixMtx[1][5];

        for (iBlock = 0; iBlock < nBlocks; iBlock++)
        {
            CoefType ctTemp0, ctTemp1;
            CoefType ctCh0 = GET_COEFF(0);
            CoefType ctCh1 = GET_COEFF(1);
            CoefType ctCh2 = GET_COEFF(2);
            CoefType ctCh3 = GET_COEFF(3);
            CoefType ctCh4 = GET_COEFF(4);
            CoefType ctCh5 = GET_COEFF(5);
                
            ctTemp0 = 
                (CoefType) MULT_CHDN(ctCh0, chdnMix00) +
                (CoefType) MULT_CHDN(ctCh1, chdnMix01) +
                (CoefType) MULT_CHDN(ctCh2, chdnMix02) +
                (CoefType) MULT_CHDN(ctCh3, chdnMix03) +
                (CoefType) MULT_CHDN(ctCh4, chdnMix04) +
                (CoefType) MULT_CHDN(ctCh5, chdnMix05);

            ctTemp1 = 
                (CoefType) MULT_CHDN(ctCh0, chdnMix10) +
                (CoefType) MULT_CHDN(ctCh1, chdnMix11) +
                (CoefType) MULT_CHDN(ctCh2, chdnMix12) +
                (CoefType) MULT_CHDN(ctCh3, chdnMix13) +
                (CoefType) MULT_CHDN(ctCh4, chdnMix14) +
                (CoefType) MULT_CHDN(ctCh5, chdnMix15);

			sTemp = DNMIXROUND(ctTemp0);
            DNMIXCLIP(sTemp);
            SET_COEFF(sTemp, 0, iBlock);

            sTemp = DNMIXROUND(ctTemp1);
            DNMIXCLIP(sTemp);
            SET_COEFF(sTemp, 1, iBlock);

#ifdef BOOST_CHANFLDDN_POWER
            if (bComputeFoldDownGain)
            {
                CoefType ctTemp;
                fltSrcChPower += (I64)ctCh0 * ctCh0 + (I64)ctCh1 * ctCh1 + (I64)ctCh2 * ctCh2 + (I64)ctCh3 * ctCh3 + (I64)ctCh4 * ctCh4 + (I64)ctCh5 * ctCh5;
                fltDstChPower += (I64)ctTemp0 * ctTemp0 + (I64)ctTemp1 * ctTemp1;
                ctTemp = ABS(ctTemp0);
                if (ctMaxAbsSample < ctTemp) ctMaxAbsSample = ctTemp;
                ctTemp = ABS(ctTemp1);
                if (ctMaxAbsSample < ctTemp) ctMaxAbsSample = ctTemp;
            }
#endif

            DNMIXADVSRCPTR(6);
            DNMIXADVDSTPTR(2);
        }
    }
    else if (cSrcChannel >= cDstChannel)
    {
        // Block transform: channel down mixing.
        for (iBlock = 0; iBlock < nBlocks; iBlock++)
        {
            // Initialize
            memset(pctTemp, 0, sizeof(CoefType) * cDstChannel);
            for (iChDst = 0; iChDst < cDstChannel; iChDst++)
            {
                for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
                {
                    CoefType c = GET_COEFF(iChSrc);
                    pctTemp[iChDst] += MULT_CHDN(c, paudec->m_rgrgfltChDnMixMtx[iChDst][iChSrc]);
#ifdef BOOST_CHANFLDDN_POWER
                    if (bComputeFoldDownGain)
                    {
                        fltSrcChPower += (I64)c * c;
                    }
#endif
                }
#ifdef BOOST_CHANFLDDN_POWER
                if (bComputeFoldDownGain)
                {
                    CoefType ctTemp;
                    fltDstChPower += (I64)pctTemp[iChDst] * pctTemp[iChDst];
                    ctTemp = ABS(pctTemp[iChDst]);
                    if (ctMaxAbsSample < ctTemp) ctMaxAbsSample = ctTemp;
                }
#endif
            }
            // One block completed: copy back results
            for (iChDst = 0; iChDst < cDstChannel; iChDst++) 
            {
                sTemp = DNMIXROUND(pctTemp[iChDst]);
                DNMIXCLIP(sTemp);
                SET_COEFF(sTemp, iChDst, iBlock);
            }
            //Stride ahead to the next block
            DNMIXADVSRCPTR(cSrcChannel);
            DNMIXADVDSTPTR(cDstChannel);
        }
    }
    else if (paudec->m_fChannelFoldDown && (cSrcChannel < cDstChannel))
    {
        // up mixing done backwards so as to not overwrite needed memory
        // Block transform: channel up mixing.
        DNMIXADVSRCPTR(cSrcChannel*(nBlocks-1));
        DNMIXADVDSTPTR(cDstChannel*(nBlocks-1));

        for (iBlock = nBlocks-1; iBlock >= 0; iBlock--)
        {
            // Initialize
            memset(pctTemp, 0, sizeof(CoefType) * cDstChannel);
            for (iChDst = 0; iChDst < cDstChannel; iChDst++)
            {
                for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
                {
                    pctTemp[iChDst] += MULT_CHDN(GET_COEFF(iChSrc), paudec->m_rgrgfltChDnMixMtx[iChDst][iChSrc]);
                }
            }
            // One block completed: copy back results
            for (iChDst = 0; iChDst < cDstChannel; iChDst++) 
            {
                sTemp = DNMIXROUND(pctTemp[iChDst]);
                DNMIXCLIP(sTemp);
                SET_COEFF(sTemp, iChDst, iBlock);
            }
            //Stride back to the previous block
            DNMIXADVSRCPTR(-cSrcChannel);
            DNMIXADVDSTPTR(-cDstChannel);
        }
    }

#endif  // TEST_VRHEADPHONE

#ifdef BOOST_CHANFLDDN_POWER
    if (bComputeFoldDownGain)
    {
        if (fltDstChPower > 0.0 && fltSrcChPower > 0.0)
        {
            paudec->m_fltChannelFoldDownGain = (Float) sqrt (fltSrcChPower / fltDstChPower);

            // Reduce folddown gain to prevent overflow 
            if (paudec->m_fltChannelFoldDownGain * ctMaxAbsSample > pau->m_iSampleMaxValue)
            {
                paudec->m_fltChannelFoldDownGain = ((Float)pau->m_iSampleMaxValue / ctMaxAbsSample) * 0.98F;
            }
        }
        // else use the previous gain factor 
    }
    else
    {
        paudec->m_fltChannelFoldDownGain = 1.0F;
    }
#endif

exit:
    return wmaResult;

#endif // NOT_SUPPORTED

} // prvChannelDownMix

// We assume piSrc and piDst point to PCMSAMPLE, channel-interleaved buffers
WMARESULT prvChannelDownMixLtRt(CAudioObjectDecoder *paudec,
                                U8 *piSrc, U16 *pcSampleReady,
                                U8 *piDst)
{
    // LtRt downmix not supported for build integer
#if defined(NOT_SUPPORTED) || defined(BUILD_INTEGER)
    return WMA_E_FAIL;
#else
    CAudioObject* pau     = paudec->pau;
    Int cSrcChannel       = pau->m_cChannel;
    Int cDstChannel       = paudec->m_cDstChannel;
    LtRtDownmix *ltrt     = paudec->m_pLtRtDownmix;
    WMARESULT wmaResult   = WMA_OK;
    Int iBlock, iChSrc, iChDst;
    Int nBlocks = *pcSampleReady;
    Int iSamples = 0;
    Int iBlockDst;
    Int nBlocksOut = 0;
    Int iChSrcIndex;
    CoefType* pctSrc = (CoefType*) piSrc;
    CoefType* pctDst = (CoefType*) piDst;
    SampleType sTemp;

    if (!paudec->m_fChannelFoldDown) 
    {
        return wmaResult;
    }

    if (paudec->m_fLtRtDownmixNonnormal)
    {
        cSrcChannel = 3; // LTRT_SRC_CHANNELS
    }
    assert(cSrcChannel == 3);  // == LTRT_SRC_CHANNELS

#ifdef CHANFLDDN_PREPCM
    for (iChSrc=0; iChSrc < cSrcChannel; iChSrc++)
    {
        paudec->rgpbTemp[iChSrc] = (SampleType*)pau->m_rgpcinfo[iChSrc].m_rgiPCMBuffer;
    }
#endif

    for (iBlock = 0; iBlock < nBlocks; iBlock++)
    {
        // Collect samples into LtRtBuf
        for (iChSrc = 0, iChSrcIndex = 0; iChSrc < cSrcChannel; iChSrc++)
        {
            ltrt->m_buf[iChSrcIndex*paudec->m_cLtRtBufSize + iSamples] =
                GET_COEFF(iChSrc);
            iChSrcIndex++;
        }
        DNMIXADVSRCPTR(cSrcChannel);
        iSamples++;
        if (iSamples==paudec->m_cLtRtBufSize || iBlock==nBlocks-1)
        {
            Int nOut;
            wmaResult = ltrtDownmix(paudec->m_pLtRtDownmix, iSamples, &nOut);
            assert(nOut <= iSamples);
            if (nOut > iSamples) return WMA_E_FAIL;
            for (iBlockDst = 0; iBlockDst < nOut; iBlockDst++)
            {
                for (iChDst = 0; iChDst < cDstChannel; iChDst++)
                {
                    sTemp = DNMIXROUND(ltrt->m_buf[iChDst*paudec->m_cLtRtBufSize + iBlockDst]);
                    SET_COEFF(sTemp, iChDst, nBlocksOut+iBlockDst);
                }
                DNMIXADVDSTPTR(cDstChannel);
            }
            nBlocksOut += nOut;
            iSamples = 0;
        }
    }
    assert(nBlocksOut <= *pcSampleReady);
    *pcSampleReady = (U16)nBlocksOut;

    return wmaResult;
#endif // NOT_SUPPORTED
} // prvChannelDownMixLtRt

#endif // BUILD_WMAPRO

#undef prvChannelDownMixType
#undef prvChannelDownMixLtRt
#undef rgpbTemp
#undef GET_COEFF
#undef SampleType
#undef DNMIXADVSRCPTR
#undef DNMIXADVDSTPTR
#undef SET_COEFF
#undef DNMIXCLIP
#undef DNMIXROUND
#undef NOT_SUPPORTED

