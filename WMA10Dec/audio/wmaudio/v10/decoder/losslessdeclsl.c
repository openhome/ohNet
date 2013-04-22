//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// This file is needed only for decoding WMA Lossless streams (not WMA Pro or WMA)
//*@@@---@@@@******************************************************************
#include <math.h>
#include <stdio.h>
#include "msaudio.h"
#include "msaudiodec.h"

#define MIN(a,b) ((a) > (b) ? b : a)
#define MAX(a,b) ((a) > (b) ? a : b)

#if defined (BUILD_WMALSL)

WMARESULT prvDecodeSubFramePureLosslessMode (CAudioObjectDecoder* paudec)
{
    WMARESULT hr = WMA_OK;
    I16     iCh;
    CAudioObject* pau = paudec->pau;

#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,DECODE_SUB_FRAME_HIGH_RATE_PROFILE);
#endif  // WMAPROFILE

    assert(paudec->pau->m_bPureLosslessMode == WMAB_TRUE);
    assert(pau->m_iVersion >= 3);

    while (paudec->m_subfrmdecsts != SUBFRM_DONE) {
        switch (paudec->m_subfrmdecsts)
        {
            case SUBFRM_HDR :   
                TRACEWMA_EXIT(hr, prvDecodeSubFrameHeaderPureLosslessMode(paudec));    
#ifdef WMA_COMPRESSION_TOOL
                if (pau->m_bSegDecodePeekMode == WMAB_TRUE)
                {
                    if (pau->m_iVersion >= 3) {
                        if (pau->m_bUnifiedLLM == WMAB_TRUE)
                            pau->m_bPeekModeNonSekPkt = WMAB_TRUE;
                    }
                    return (hr = WMA_E_ONHOLD);
                }
#endif //WMA_COMPRESSION_TOOL
                paudec->m_subfrmdecsts = SUBFRM_COEFDEC_PLLM;

                paudec->m_iChannel = 0;
                    paudec->m_LLMdecsts = CH_BEGIN;
                         paudec->m_iCurrLPCCoef = 0;
                              paudec->pau->m_iCurrReconCoef = 0;
                                   paudec->m_Colombdecsts = FIRST_PART;
                                        paudec->m_iResQ = 0;
                                        paudec->m_iRem = 0;
                break;

            case SUBFRM_COEFDEC_PLLM:
                {
                    if (pau->m_bOutputRawPCM == WMAB_FALSE) {
                        // We are going to use LMS filters. We assume we have decoded
                        // them successfully. But if we start to decode at a RAWPCM frame,
                        // and the next frame's seekable bit is corrputted (to 0), we will
                        // try to use invalid LMS fitler. Next line is used to catch that
                        // problem.
                        if (paudec->m_bGotValidFilterInfo == WMAB_FALSE) {
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);                            
                        }
                        for (; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) 
                        {
                            I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                            if (ppcinfo->m_iPower != 0) {
                                TRACEWMA_EXIT(hr, prvDecodeSubFrameChannelResiduePureLosslessModeVerB(pau, paudec, ppcinfo));    
                            }

                            if (paudec->pau->m_iCurrReconCoef > (I16) ppcinfo->m_cSubband)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);
                            // set up for next channel.
                            paudec->m_LLMdecsts = CH_BEGIN;
                            paudec->m_iCurrLPCCoef = 0;

                            paudec->pau->m_iCurrReconCoef = 0;
                            paudec->m_Colombdecsts = FIRST_PART;
                            paudec->m_iResQ = 0;
                            paudec->m_iRem = 0;

                        }
                        paudec->m_subfrmdecsts = SUBFRM_REC_PLLM;
                    }
                    else if (pau->m_bOutputRawPCM == WMAB_TRUE) {
                        for (; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) 
                        {
                            I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                            TRACEWMA_EXIT(hr, prvDecodeSubFrameChannelRawPCMPureLosslessMode(pau, paudec, ppcinfo));    
                            if (paudec->pau->m_iCurrReconCoef > (I16) ppcinfo->m_cSubband)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);

                            // set up for next channel.
                            paudec->m_LLMdecsts = CH_BEGIN;
                            paudec->pau->m_iCurrReconCoef = 0;
                        }
                        paudec->m_subfrmdecsts = SUBFRM_SAVE_PREV;
                    }
                    paudec->m_iChannel = 0;
                }
                break;

            case SUBFRM_REC_PLLM:
                // clear zero coefficients.
                // V3 LLM. Chao. Problem. We can start from 0 here. This part does not need to support onhold/resume.
                for (paudec->m_iChannel = 0; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) 
                {
                    I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                    PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                    if (ppcinfo->m_iPower == 0) {
                        // decoder use m_rgiSubFrameStart in a different way from encoder. In encoder side, 
                        // m_rgiSubFrameStart is an array pointing to the start position of all subframes but
                        // in decoder only the first elment is used (m_rgiSubFrameStart[0]) which points to
                        // the current subframe's start poition. The new subframe will overwrite 
                        // m_rgiSubFrameStart[0]. That is the reason we see a lot of m_rgiSubFrameStart[0]
                        // in decoder side.
                        memset (ppcinfo->m_rgiCoefRecon + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0], 
                                0, sizeof (CoefType) * ppcinfo->m_cSubFrameSampleHalf);
                        ppcinfo->m_iActualPower = 0;
                    }
                }

                if (pau->m_bDoMCLMS == WMAB_TRUE) {
                    I32 iCoeff;
                    I32 iLen = (pau->m_rgpcinfo + pau->m_rgiChInTile[0])->m_cSubFrameSampleHalf;
                    CBT * rgiBuf = pau->m_rgiInterlacedInput;
                    CBT * rgiBufT = pau->m_rgiInterlacedInputT;

                    if (pau->m_cChInTile != pau->m_cChannel)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);

                    for (iCoeff = 0; iCoeff < iLen; iCoeff++) {
                        for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
                            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
                            CBT * rgiInputNew = ppcinfo->m_rgiCoefRecon + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
                            rgiBuf[iCh] = rgiInputNew[iCoeff];
                            // pass the channel power information to Predictor
                            if (ppcinfo->m_iPower == WMAB_FALSE) {
                                rgiBufT[iCh] = 0;
                            }
                            else {
                                rgiBufT[iCh] = 1;
                            }
                        }

                    //only for ARM decoder now, and will apply to another platforms and encoder as well
                    #if defined(WMA_TARGET_ARM) || defined(WMA_TARGET_SH4)
                        pau->pprvMCLMSUpdate(pau, &pau->m_MCLMSPredictor, rgiBuf, rgiBufT);
                    #elif defined(WMA_TARGET_MIPS)
                        pau->pprvMCLMSUpdate(pau, &pau->m_MCLMSPredictor, rgiBuf, rgiBufT);
                    #else
                        pau->pprvMCLMSPred(pau, &pau->m_MCLMSPredictor, rgiBuf, rgiBufT, WMAB_TRUE);
                        pau->pprvMCLMSUpdate(pau, &pau->m_MCLMSPredictor, rgiBuf, rgiBufT);
                    #endif //WMA_TARGET_ARM || WMA_TARGET_SH4

                        for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
                            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
                            CBT * rgiCoefRecon = (CBT *)ppcinfo->m_rgiCoefRecon + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
                            rgiCoefRecon[iCoeff] = rgiBuf[iCh];
                        }
                    }
                }


                if (pau->m_bDoInterChDecorr == DO_CHANNEL_MIXING) {
                    if (pau->m_cChInTile == 2) {
                        U32 iCoeff;
                        I16 iChSrc0 = pau->m_rgiChInTile [0];
                        I16 iChSrc1 = pau->m_rgiChInTile [1];
                        PerChannelInfo* ppcinfo0 = pau->m_rgpcinfo + iChSrc0;
                        PerChannelInfo* ppcinfo1 = pau->m_rgpcinfo + iChSrc1;            
    
                        CBT * rgiCoefRecon0 = ppcinfo0->m_rgiCoefRecon
                            + ppcinfo0->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
                        CBT * rgiCoefRecon1 = ppcinfo1->m_rgiCoefRecon
                            + ppcinfo1->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
                        U32 iLen =  ppcinfo0->m_cSubband;
                        for (iCoeff = 0; iCoeff < iLen; iCoeff++) {
                            rgiCoefRecon0[iCoeff] -= (rgiCoefRecon1[iCoeff] >> 1);
                            rgiCoefRecon1[iCoeff] += rgiCoefRecon0[iCoeff];
                        }
                    }
                    else { // multi-channel
                    }
                }
                
                // No tiling support in LLM_VERB.
                if (pau->m_cChInTile != pau->m_cChannel)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);                   

                if (pau->m_bDoACFilter == WMAB_TRUE) {
                        prvSubFrameRestoreChannelDC(pau);
                }
                if (pau->m_bPLLMQStepSize != 1) {
                    prvSubFrameDeQuantize(pau);
                }
                if (pau->m_bV3RTM == WMAB_TRUE) {
                    if (pau->m_bDoLPC == WMAB_TRUE) {
                        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                        {
                            I16 iChSrc = pau->m_rgiChInTile[iCh];
                            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;        
                            I16 iOrder = pau->m_iLPCOrder;
                            I32 * rgiLPCFilter = ppcinfo->m_rgiLPCFilter;            
                            I32 * rgiLPCPrevSamples = ppcinfo->m_rgiLPCPrevSamples;
                            CBT * rgiCoefRecon = ppcinfo->m_rgiCoefRecon;
                            U32 iLen = ppcinfo->m_cSubFrameSampleHalf;
                            prvLPCFilteringInv(pau, rgiCoefRecon, rgiLPCPrevSamples, rgiCoefRecon, rgiLPCFilter, iLen, pau->m_iLPCOrder);
                        }
                    }
                }

                paudec->m_subfrmdecsts = SUBFRM_SAVE_PREV;
                break;
            
            // TODO: we'd better to change SUBFRM_SAVE_PREV to something else.
            // and we should combine this block with above block since they
            // don't decode bit stream.
            case SUBFRM_SAVE_PREV:

                // scale back to ORIGINAL PCM samples.
                if (pau->m_iPCMTrailZeros) {
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
                        I32 iCoeff;
                        I16 iChSrc = pau->m_rgiChInTile [iCh];
                        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                        const I32 iLen = ppcinfo->m_cSubFrameSampleHalf;
                        CBT * rgiCoefRecon = (CBT *)ppcinfo->m_rgiCoefRecon
                            + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
                        for (iCoeff = 0; iCoeff < iLen; iCoeff++) {
                            rgiCoefRecon[iCoeff] = (rgiCoefRecon[iCoeff] << pau->m_iPCMTrailZeros);
                        }
                    }
                }

                // update rgsubfrmconfig
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                {
                    I16 iChSrc = pau->m_rgiChInTile [iCh];
                    PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                    I16* rgiSize  = ppcinfo->m_rgsubfrmconfig->m_rgiSubFrameSize;
                    I16* rgiStart = ppcinfo->m_rgsubfrmconfig->m_rgiSubFrameStart;
                    rgiStart[0] += rgiSize [ppcinfo->m_iCurrSubFrame];
                }

                // update rgiPCMInHistory
                if (pau->m_bPureLosslessMode == WMAB_TRUE) {
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                    {
                        I16 iChSrc = pau->m_rgiChInTile [iCh];
                        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                        pau->m_rgiPCMInHistory[iChSrc] += ppcinfo->m_cSubFrameSampleHalf;
                    }
                }
                paudec->m_subfrmdecsts = SUBFRM_DONE;            
                break;
        }
    }    

exit:
#ifdef WMAPROFILE
    //FunctionProfileStop(&fp);
#endif  // WMAPROFILE

    return hr;
} // prvDecodeSubFramePureLosslessMode

WMARESULT prvDecodeSubFrameHeaderPureLosslessMode (CAudioObjectDecoder* paudec)
{      
    Bool fSkipAll;
    I16  *piChannel = &paudec->m_iChannel;
    CAudioObject* pau = paudec->pau;
    // PerChannelInfo* ppcinfo = pau->m_rgpcinfo;
    SubFrameConfigInfo* psubfrmconfig = NULL;
    
    WMARESULT   wmaResult = WMA_OK;
    U32         iResult;
    I16 iStartMin; 
    I16 iSizeMin;
    I16 iCh;
    
#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_FRAME_HEADER_PROFILE);
#endif

    if (pau->m_iVersion < 3)
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                

    while (paudec->m_hdrdecsts != HDR_DONE) {
        switch (paudec->m_hdrdecsts)
        {
        case HDR_SIZE:
            {
                //search for tile starting position
                I32 cSampleLeft = pau->m_cFrameSampleHalf * pau->m_cChannel;
                PerChannelInfo* ppcinfo = pau->m_rgpcinfo;
                iStartMin = (I16) pau->m_cFrameSampleHalf;
                iSizeMin  = (I16) pau->m_cFrameSampleHalf;
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {            
                    I16* piStart = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart;
                    I16* piSize  = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize + ppcinfo->m_iCurrSubFrame;
                    if (iStartMin > *piStart)
                    {
                        iStartMin = (I16) *piStart;
                        iSizeMin  = (I16) *piSize;  
                    }
                    ppcinfo++;
                }

                pau->m_cChInTile = 0;
                ppcinfo   = pau->m_rgpcinfo;
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    I16* rgiSize;
                    I16* rgiStart;
                    I16* piSubFrmCurr;

                    psubfrmconfig= ppcinfo->m_rgsubfrmconfig; //curr
                    rgiSize      = psubfrmconfig->m_rgiSubFrameSize;
                    rgiStart     = psubfrmconfig->m_rgiSubFrameStart;
                    piSubFrmCurr = &ppcinfo->m_iCurrSubFrame;
                                
                    cSampleLeft -= rgiStart [0]; //covered so far
                    //possibly a ch in tile
                    if (iStartMin == rgiStart [0])
                    {
                        if (iSizeMin == rgiSize [*piSubFrmCurr])
                        {                                   
                            pau->m_rgiChInTile [pau->m_cChInTile] = iCh;
                            pau->m_cChInTile++;
                            ppcinfo->m_iSizeNext = (I16) rgiSize [*piSubFrmCurr + 1];
                            ppcinfo->m_iSizeCurr = (I16) rgiSize [*piSubFrmCurr];
                            ppcinfo->m_iSizePrev = (I16) rgiSize [*piSubFrmCurr - 1];
                            cSampleLeft -= rgiSize [*piSubFrmCurr];
                            // rgiStart [0] += rgiSize [*piSubFrmCurr];
                        }
                    }
                    ppcinfo++;
                }
                if (pau->m_cChInTile > pau->m_cChannel || pau->m_cChInTile <= 0 || cSampleLeft < 0) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                }
                paudec->m_fLastSubFrame = (cSampleLeft == 0);                
            }
            
            ASSERTWMA_EXIT(wmaResult, auAdaptToSubFrameConfig (pau));
            ASSERTWMA_EXIT(wmaResult, auAdaptToSubFrameConfigDEC (pau));
            
            paudec->m_hdrdecsts = HDR_SEEKABLE;
            break;

        case HDR_SEEKABLE:
            // get 1 bit to indicate it is seekable or not.
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bSeekable = iResult;

            if (pau->m_cChInTile != pau->m_cChannel)
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
 
            if (pau->m_bSeekable == WMAB_TRUE) {
                paudec->m_hdrdecsts = HDR_ENTROPY_CODING;
            }
            else {
                paudec->m_hdrdecsts = HDR_RAWPCM;
            }
            break;

        case HDR_ENTROPY_CODING:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));               
            pau->m_bDoArithmCoding = (Bool)iResult;
            if (pau->m_bDoArithmCoding == WMAB_TRUE) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
            paudec->m_hdrdecsts = HDR_DO_ACFILTER; 

        case HDR_DO_ACFILTER:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));               
            pau->m_bDoACFilter = (Bool)iResult;
            paudec->m_hdrdecsts = HDR_INTERCH_DECORR; 

        case HDR_INTERCH_DECORR:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));               
            pau->m_bDoInterChDecorr = (Bool)iResult;
            paudec->m_hdrdecsts = HDR_INTERCH_DECORR_MCLMS;

        case HDR_INTERCH_DECORR_MCLMS:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));               
            pau->m_bDoMCLMS = (Bool)iResult;
            paudec->m_hdrdecsts = HDR_ACFILTER_ORDER; 
            break;

        case HDR_ACFILTER_ORDER:
            if (pau->m_bDoACFilter == WMAB_TRUE) {
                assert((1 << LLM_VERB_ACFILTER_ORDER_BITS) >= (LLM_VERB_ACFILTER_ORDER_MAX - LLM_VERB_ACFILTER_ORDER_MIN + 1));
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLM_VERB_ACFILTER_ORDER_BITS, (U32 *)&iResult));
                // assert(pau->m_iACFilterOrder <= LLM_VERB_ACFILTER_ORDER_MAX);
                if (iResult + LLM_VERB_ACFILTER_ORDER_MIN > LLM_VERB_ACFILTER_ORDER_MAX)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                //assert(pau->m_iACFilterOrder >= LLM_VERB_ACFILTER_ORDER_MIN);
                if (iResult + LLM_VERB_ACFILTER_ORDER_MIN < LLM_VERB_ACFILTER_ORDER_MIN)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                pau->m_iACFilterOrder = (I16)(iResult + LLM_VERB_ACFILTER_ORDER_MIN);
            }
            paudec->m_hdrdecsts = HDR_ACFILTER_SCALING;

        case HDR_ACFILTER_SCALING:
            if (pau->m_bDoACFilter == WMAB_TRUE) {
                assert((1 << LLMB_INTEGERIZATION_SCALING_BITS) > (LLMB_INTEGERIZATION_SCALING_MAX - LLMB_INTEGERIZATION_SCALING_MIN));  
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_INTEGERIZATION_SCALING_BITS, &iResult));               
                //assert(pau->m_iACFilterScaling <= LLMB_INTEGERIZATION_SCALING_MAX);
                if ((I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN > LLMB_INTEGERIZATION_SCALING_MAX)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                //assert(pau->m_iACFilterScaling >= LLMB_INTEGERIZATION_SCALING_MIN);
                if ((I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN < LLMB_INTEGERIZATION_SCALING_MIN)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                pau->m_iACFilterScaling = (I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN;
            }
            pau->m_iACFilterCurr = 0;
            paudec->m_hdrdecsts = HDR_ACFILTER;

        case HDR_ACFILTER:
            if (pau->m_bDoACFilter == WMAB_TRUE) {
                for (/*pau->m_iACFilterCurr*/; pau->m_iACFilterCurr < pau->m_iACFilterOrder; pau->m_iACFilterCurr++) {
                    if (pau->m_bSeekable == WMAB_TRUE) {
                        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, pau->m_iACFilterScaling, (U32 *)&iResult));
                        //assert(pau->m_iACFilter[pau->m_iACFilterCurr] > 0);
                        if ((I32) (iResult + 1) <= 0)
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                        // assert(pau->m_iACFilter[pau->m_iACFilterCurr] <= (1 << pau->m_iACFilterScaling));
                        if ((I32) (iResult + 1) > (1 << pau->m_iACFilterScaling))
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                        pau->m_iACFilter[pau->m_iACFilterCurr] = (I16)(iResult + 1);
                    }
                }
            }
            paudec->m_hdrdecsts = HDR_MCLMS_ORDER;

        case HDR_MCLMS_ORDER:
            if (pau->m_bDoMCLMS == WMAB_TRUE) {
                assert((1 << LLMB_MCLMS_ORDER_BITS) * LLMB_MCLMS_MIN_ORDER_EACHCH >= LLMB_MCLMS_MAX_ORDER_EACHCH);
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_MCLMS_ORDER_BITS, &iResult));               
                //assert(pau->m_MCLMSPredictor.m_iOrder <= LLMB_MCLMS_MAX_ORDER_EACHCH);
                if ((iResult + 1) * LLMB_MCLMS_MIN_ORDER_EACHCH > LLMB_MCLMS_MAX_ORDER_EACHCH)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                // assert(pau->m_MCLMSPredictor.m_iOrder >= LLMB_MCLMS_MIN_ORDER_EACHCH);   
                if ((iResult + 1) * LLMB_MCLMS_MIN_ORDER_EACHCH < LLMB_MCLMS_MIN_ORDER_EACHCH)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                pau->m_MCLMSPredictor.m_iOrder = (iResult + 1) * LLMB_MCLMS_MIN_ORDER_EACHCH;
            }
            paudec->m_hdrdecsts = HDR_MCLMS_SCALING; 

        case HDR_MCLMS_SCALING:
            if (pau->m_bDoMCLMS == WMAB_TRUE) {
                assert((1 << LLMB_INTEGERIZATION_SCALING_BITS) > (LLMB_INTEGERIZATION_SCALING_MAX - LLMB_INTEGERIZATION_SCALING_MIN));  
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_INTEGERIZATION_SCALING_BITS, &iResult));               
                //assert(pau->m_MCLMSPredictor.m_iScaling <= LLMB_INTEGERIZATION_SCALING_MAX);
                if ((I32) iResult + LLMB_INTEGERIZATION_SCALING_MIN > LLMB_INTEGERIZATION_SCALING_MAX)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                //assert(pau->m_MCLMSPredictor.m_iScaling >= LLMB_INTEGERIZATION_SCALING_MIN);
                if ((I32) iResult + LLMB_INTEGERIZATION_SCALING_MIN < LLMB_INTEGERIZATION_SCALING_MIN)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                pau->m_MCLMSPredictor.m_iScaling = iResult + LLMB_INTEGERIZATION_SCALING_MIN;
                prvMCLMSPredictorReset(pau, &pau->m_MCLMSPredictor);
            }
            paudec->m_hdrdecsts = HDR_MCLMS_SEND;

        case HDR_MCLMS_SEND:
            if (pau->m_bDoMCLMS == WMAB_TRUE) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));               
                pau->m_bSendMCLMS = (Bool)iResult;
            }
            paudec->m_iLMSCurrCoeff = 0;
            paudec->m_hdrdecsts = HDR_MCLMS_COEFF_BITS;

        case HDR_MCLMS_COEFF_BITS:
            if (pau->m_bDoMCLMS == WMAB_TRUE) {
                if (pau->m_bSendMCLMS == WMAB_TRUE) {
                    I32 cBits;
                    cBits = LOG2(pau->m_MCLMSPredictor.m_iScaling + 1);
                    if ((1 << cBits) < (pau->m_MCLMSPredictor.m_iScaling + 1))
                        cBits++;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, &iResult));
                    // assert(pau->m_MCLMSPredictor.m_cBitsSentPerCoeff <= pau->m_MCLMSPredictor.m_iScaling + 2);
                    if ((I32) iResult + 2 > pau->m_MCLMSPredictor.m_iScaling + 2)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    pau->m_MCLMSPredictor.m_cBitsSentPerCoeff = (I16)iResult + 2;
                }
            }
            paudec->m_iLMSCurrCoeff = 0;
            paudec->m_hdrdecsts = HDR_MCLMS_COEFF_A;

        case HDR_MCLMS_COEFF_A:
            if (pau->m_bDoMCLMS == WMAB_TRUE) {
                if (pau->m_bSendMCLMS == WMAB_TRUE) {
                    // read MCLMS filter
                    I32 iShiftL, iShiftR;
                    I32 cBits;
                    iShiftL = 32 - pau->m_MCLMSPredictor.m_cBitsSentPerCoeff;
                    iShiftR = 32 - 2 - pau->m_MCLMSPredictor.m_iScaling;

                    // below two for loops are seek and resume safe.
                    for (/*paudec->m_iLMSCurrCoeff*/;
                        paudec->m_iLMSCurrCoeff < pau->m_MCLMSPredictor.m_iOrder * pau->m_cChannel * pau->m_cChannel;
                        paudec->m_iLMSCurrCoeff++) {
                        cBits = pau->m_MCLMSPredictor.m_cBitsSentPerCoeff;
                        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, &iResult));
                        iResult = (iResult << iShiftL);
                        iResult = ((I32)iResult >> iShiftR);
                        pau->m_MCLMSPredictor.m_rgiFilterBackup[paudec->m_iLMSCurrCoeff] = (I16)iResult;
                    }
                }
            }
            paudec->m_iChannel = 0;
            paudec->m_iLMSCurrCoeff = 0;
            paudec->m_hdrdecsts = HDR_MCLMS_COEFF_B;

        case HDR_MCLMS_COEFF_B:
            if (pau->m_bDoMCLMS == WMAB_TRUE) {
                if (pau->m_bSendMCLMS == WMAB_TRUE) {
                    I32 iShiftL, iShiftR;
                    I32 cBits;
                    iShiftL = 32 - pau->m_MCLMSPredictor.m_cBitsSentPerCoeff;
                    iShiftR = 32 - 2 - pau->m_MCLMSPredictor.m_iScaling;
                    for (/*paudec->m_iChannel*/; paudec->m_iChannel < pau->m_cChannel; paudec->m_iChannel++) {
                        for (/*paudec->m_iLMSCurrCoeff*/; paudec->m_iLMSCurrCoeff < paudec->m_iChannel; paudec->m_iLMSCurrCoeff++) {
                            cBits = pau->m_MCLMSPredictor.m_cBitsSentPerCoeff;
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, &iResult));
                            iResult = (iResult << iShiftL);
                            iResult = ((I32)iResult >> iShiftR);
                            pau->m_MCLMSPredictor.m_rgiFilterCurrTimeBackup[paudec->m_iChannel * pau->m_cChannel + paudec->m_iLMSCurrCoeff] = (I16)iResult;                                  
                        }
                        paudec->m_iLMSCurrCoeff = 0;
                    }
                }
            }
            paudec->m_hdrdecsts = HDR_CDLMS_SEND;

        case HDR_CDLMS_SEND:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));               
            pau->m_bSendCDLMS = (Bool)iResult;

            paudec->m_iChannel = 0;
            paudec->m_hdrdecsts = HDR_FILTERS_PARA;
            paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_AMOUNT;

        case HDR_FILTERS_PARA:
            for (; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) {                       
                I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                PerChannelInfo* ppcInfoComm = pau->m_rgpcinfo + iChSrc;
                switch(paudec->m_hdrdecFilterParasts)
                {
                    case HDRFLT_CLMS_AMOUNT:
                        assert((1 << LLMB_CLMSFLT_TTL_BITS) >= (LLMB_CLMSFLT_TTL_MAX - LLMB_CLMSFLT_TTL_MIN + 1));
                        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_CLMSFLT_TTL_BITS, (U32 *)&iResult));
                        
                        // assert(ppcInfoComm->m_cLMSPredictors <= LLMB_CLMSFLT_TTL_MAX);
                        if ((iResult + LLMB_CLMSFLT_TTL_MIN) > LLMB_CLMSFLT_TTL_MAX)
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                        // assert(ppcInfoComm->m_cLMSPredictors >= LLMB_CLMSFLT_TTL_MIN);
                        if ((iResult + LLMB_CLMSFLT_TTL_MIN) < LLMB_CLMSFLT_TTL_MIN)
                            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                        ppcInfoComm->m_cLMSPredictors = (I16)(iResult + LLMB_CLMSFLT_TTL_MIN);
                        ppcInfoComm->m_iLMSPredictorCurr = 0;
                        paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_ORDERS;

                    case HDRFLT_CLMS_ORDERS:
                        assert((1<< LLMB_CLMSFLT_ORDER_BITS) * LLMB_CLMSFLT_MIN_ORDER >= LLMB_CLMSFLT_MAX_ORDER);
                        for (/*ppcInfoComm->m_iLMSPredictorCurr*/; ppcInfoComm->m_iLMSPredictorCurr < ppcInfoComm->m_cLMSPredictors; ppcInfoComm->m_iLMSPredictorCurr++) {
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_CLMSFLT_ORDER_BITS, (U32 *)&iResult));
                            // assert(ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iOrder <= LLMB_CLMSFLT_MAX_ORDER);
                            if ((iResult + 1) * LLMB_CLMSFLT_MIN_ORDER > LLMB_CLMSFLT_MAX_ORDER)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                            // assert(ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iOrder >= LLMB_CLMSFLT_MIN_ORDER);
                            if ((iResult + 1) * LLMB_CLMSFLT_MIN_ORDER < LLMB_CLMSFLT_MIN_ORDER)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                            ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iOrder = (iResult + 1) * LLMB_CLMSFLT_MIN_ORDER;

                        }
                        ppcInfoComm->m_iLMSPredictorCurr = 0;
                        paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_SCALINGS;

                    case HDRFLT_CLMS_SCALINGS:
                        assert((1 << LLMB_INTEGERIZATION_SCALING_BITS) > (LLMB_INTEGERIZATION_SCALING_MAX - LLMB_INTEGERIZATION_SCALING_MIN));  
                        for (/*ppcInfoComm->m_iLMSPredictorCurr*/; ppcInfoComm->m_iLMSPredictorCurr < ppcInfoComm->m_cLMSPredictors; ppcInfoComm->m_iLMSPredictorCurr++) {
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_INTEGERIZATION_SCALING_BITS, (U32 *)&iResult));
                            // assert(ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling <= LLMB_INTEGERIZATION_SCALING_MAX);
                            if ((I32) iResult + LLMB_INTEGERIZATION_SCALING_MIN > LLMB_INTEGERIZATION_SCALING_MAX)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                            // assert(ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling >= LLMB_INTEGERIZATION_SCALING_MIN);
                            if ((I32) iResult + LLMB_INTEGERIZATION_SCALING_MIN < LLMB_INTEGERIZATION_SCALING_MIN)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                            ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling = iResult + LLMB_INTEGERIZATION_SCALING_MIN;
                        }
                        ppcInfoComm->m_iLMSPredictorCurr = 0;
                        paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_COEFF;
                        paudec->m_hdrdecFilterParaCLMSsts = HDRFLT_CLMS_COEFFS_SENT;
                    case HDRFLT_CLMS_COEFF:
                        if (pau->m_bSendCDLMS == WMAB_TRUE) {
                            I32 cBits;
                            I32 iShiftL, iShiftR;
                            for (/*ppcInfoComm->m_iLMSPredictorCurr*/; ppcInfoComm->m_iLMSPredictorCurr < ppcInfoComm->m_cLMSPredictors; ppcInfoComm->m_iLMSPredictorCurr++) {
                                switch(paudec->m_hdrdecFilterParaCLMSsts) 
                                {
                                    case HDRFLT_CLMS_COEFFS_SENT:
                                        cBits = LOG2(ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iOrder);
                                        if ((1 << cBits) < ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iOrder)
                                            cBits++;
                                        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, &iResult));
                                        ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_cCoeffsSent = (I16)iResult + 1;
                                        paudec->m_hdrdecFilterParaCLMSsts = HDRFLT_CLMS_COEFFS_SENTBITS;

                                    case HDRFLT_CLMS_COEFFS_SENTBITS:
                                        cBits = LOG2(ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling + 1);
                                        if ((1 << cBits) < (ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling + 1))
                                            cBits++;
                                        TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, &iResult));
                                        ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_cBitsSentPerCoeff = (I16)iResult + 2;

                                        paudec->m_iLMSCurrCoeff = 0;
                                        paudec->m_hdrdecFilterParaCLMSsts = HDRFLT_CLMS_COEFFS_VALUE;
                                        
                                    case HDRFLT_CLMS_COEFFS_VALUE:
                                        iShiftL = 32 - ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_cBitsSentPerCoeff;
                                        iShiftR = 32 - 2 - ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling;
                                        cBits = ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_cBitsSentPerCoeff;
                                        for (/*paudec->m_iLMSCurrCoeff*/;
                                                paudec->m_iLMSCurrCoeff < ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_cCoeffsSent;
                                                paudec->m_iLMSCurrCoeff++) 
                                        {
                                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, &iResult));
                                            iResult = (iResult << iShiftL);
                                            iResult = ((I32)iResult >> iShiftR);
                                            ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_rgiFilterBackup[paudec->m_iLMSCurrCoeff] = (I16)iResult;
                                                
                                        }
                                        paudec->m_hdrdecFilterParaCLMSsts = HDRFLT_CLMS_COEFFS_SENT;

                                }
                                paudec->m_hdrdecFilterParaCLMSsts = HDRFLT_CLMS_COEFFS_SENT;
                            }
                        }
                        ppcInfoComm->m_iLMSPredictorCurr = 0;
                        paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_AMOUNT;
                }
            }            

            paudec->m_hdrdecsts = HDR_RES_MEM_SCALING;

        case HDR_RES_MEM_SCALING:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_RESIDUE_MEMORY_TTLWEIGHT_BITS, &iResult));
            pau->m_iResidueMemScaling = (I16)iResult;
            paudec->m_hdrdecsts = HDR_QSTEPSIZE_B4_PLLM;

        case HDR_QSTEPSIZE_B4_PLLM:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_QUANTSTEPSIZE_B4_PLLM_BITS, &iResult));
            // assert(pau->m_bPLLMQStepSize >= LLMB_QUANTSTEPSIZE_B4_PLLM_MIN);
            if (iResult + LLMB_QUANTSTEPSIZE_B4_PLLM_MIN < LLMB_QUANTSTEPSIZE_B4_PLLM_MIN)
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            // assert(pau->m_bPLLMQStepSize <= LLMB_QUANTSTEPSIZE_B4_PLLM_MAX);
            if (iResult + LLMB_QUANTSTEPSIZE_B4_PLLM_MIN > LLMB_QUANTSTEPSIZE_B4_PLLM_MAX)
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            pau->m_bPLLMQStepSize = (I16)iResult + LLMB_QUANTSTEPSIZE_B4_PLLM_MIN;

            //TODO: I think I should put ResetAll function at the end of decodeheader.
            // After getting all information, set the filters.
            if (pau->m_bSeekable == WMAB_TRUE) {
                //After we read filter info from bit stream we reset all filters.
                prvLLMVerBResetAllCom(pau, pau->m_rgpcinfo);
            }
            paudec->m_hdrdecsts = HDR_RAWPCM;

        case HDR_RAWPCM:
            // get 1 bit to indicate this subframe is coded as raw PCM.
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bOutputRawPCM = iResult;

            // set all channel power to 1.
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
                I16 iChSrc = pau->m_rgiChInTile [iCh];
                PerChannelInfo * ppcinfo = pau->m_rgpcinfo + iChSrc;               
                ppcinfo->m_iPower = 1;
            }
            if (pau->m_bOutputRawPCM == WMAB_TRUE) {
                paudec->m_hdrdecsts = HDR_PADDED_ZEROS;
            }
            else {
                paudec->m_hdrdecsts = HDR_V3_POWER;
            }
            break;

        case HDR_V3_POWER:
            {
                PerChannelInfo* rgpcinfo = pau->m_rgpcinfo;
                fSkipAll = WMAB_TRUE;
                
                // Power information
                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, pau->m_cChInTile));                
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
                    I16 iChSrc = pau->m_rgiChInTile [iCh];
                    PerChannelInfo * ppcinfo = pau->m_rgpcinfo + iChSrc;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                    
                    // This comment is only for LLM_VERA
                    // V3 LLM. In encoder we have m_iPower and m_iPowerOri but
                    // in decoder we just use m_iPower. Therefore, in decoder,
                    // m_iPower represents original channel power or mixed 
                    // channel power depending on whether channel mixing is done.

                    ppcinfo->m_iPower = iResult;
                }
            }
            pau->m_iMltChlsMixingRnd = 0;
            paudec->m_hdrdecsts = HDR_MLTCHL_MIX_SEQ;

        case HDR_MLTCHL_MIX_SEQ:
            if (pau->m_bV3RTM == WMAB_TRUE) {
                paudec->m_hdrdecsts = HDR_V3_LPC_UNIFIED;
            }
            else {
                paudec->m_hdrdecsts = HDR_PADDED_ZEROS;
            }
            break;

        case HDR_V3_LPC_UNIFIED:
            if (pau->m_bV3RTM == WMAB_TRUE) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                pau->m_bDoLPC = (Bool)iResult;
            }
            paudec->m_hdrdecsts = HDR_V3_LPC_ORDER;

        case HDR_V3_LPC_ORDER:
            if (pau->m_bV3RTM == WMAB_TRUE) {
                if (pau->m_bDoLPC == WMAB_TRUE) {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LPC_ORDER_UNIFIED_BITS, &iResult));
                    pau->m_iLPCOrder = (I16)iResult + 1;
                }
            }
            paudec->m_hdrdecsts = HDR_V3_LPC_UNIFIED_SCALING;

        case HDR_V3_LPC_UNIFIED_SCALING:
            if (pau->m_bV3RTM == WMAB_TRUE) {
                if (pau->m_bDoLPC == WMAB_TRUE) {
                    assert((1 << LLMB_INTEGERIZATION_SCALING_BITS) > (LLMB_INTEGERIZATION_SCALING_MAX - LLMB_INTEGERIZATION_SCALING_MIN));  
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_INTEGERIZATION_SCALING_BITS, &iResult));               
                    //assert(pau->m_iACFilterScaling <= LLMB_INTEGERIZATION_SCALING_MAX);
                    if ((I32) iResult + LLMB_INTEGERIZATION_SCALING_MIN > LLMB_INTEGERIZATION_SCALING_MAX)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    //assert(pau->m_iACFilterScaling >= LLMB_INTEGERIZATION_SCALING_MIN);
                    if ((I32) iResult + LLMB_INTEGERIZATION_SCALING_MIN < LLMB_INTEGERIZATION_SCALING_MIN)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    pau->m_iLPCFilterScaling = (I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN;
                }
            }
            paudec->m_hdrdecsts = HDR_V3_LPC_UNIFIED_INTBITS;

        case HDR_V3_LPC_UNIFIED_INTBITS:
            if (pau->m_bV3RTM == WMAB_TRUE) {
                if (pau->m_bDoLPC == WMAB_TRUE) {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, BITS_LPC_INTBITS_UNIFIED, &iResult));               
                    if (iResult + MIN_LPC_INTBITS_UNIFIED < MIN_LPC_INTBITS_UNIFIED)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    if (iResult + MIN_LPC_INTBITS_UNIFIED > MAX_LPC_INTBITS_UNIFIED)
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    pau->m_iLPCFilterIntBits = (I16)iResult + MIN_LPC_INTBITS_UNIFIED;
                }
            }
            paudec->m_iChannel = 0;
            paudec->m_iCurrLPCCoef = 0;
            paudec->m_hdrdecsts = HDR_V3_LPC_COEF;

        case HDR_V3_LPC_COEF:
            if (pau->m_bV3RTM == WMAB_TRUE) {
                if (pau->m_bDoLPC == WMAB_TRUE) {
                    for (; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) {                       
                        I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                        I32 * rgiLPCFilter = ppcinfo->m_rgiLPCFilter;
                        // read LPC coefficients.
                        for (; paudec->m_iCurrLPCCoef < pau->m_iLPCOrder; paudec->m_iCurrLPCCoef++) {
                            I16 cBits = pau->m_iLPCFilterScaling + pau->m_iLPCFilterIntBits;
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, (U32 *)&iResult));
                            // (I16) just cut the low 16 bits? It must be cut to get the correct sign bit.
                            rgiLPCFilter[paudec->m_iCurrLPCCoef] = ((I32)iResult << (32 - cBits)) >> (32 - cBits);
                        }
                        paudec->m_iCurrLPCCoef = 0;
                    }
                }
            }
            paudec->m_hdrdecsts = HDR_PADDED_ZEROS;
            break;

        case HDR_PADDED_ZEROS:
            // DONE. TODO: there are two possibilites: 1 bit and 6 bits. Finally I will add more state to separate them.
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            if (iResult == 0) {
                pau->m_iPCMTrailZeros = 0;
                paudec->m_hdrdecsts = HDR_DONE;
            }
            else {
                paudec->m_hdrdecsts = HDR_PADDED_ZEROS_B;
            }
            break;

        case HDR_PADDED_ZEROS_B:
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 5, &iResult));
            if (iResult >= pau->m_nValidBitsPerSample) {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);           
            }
            else {
                pau->m_iPCMTrailZeros = (U8)iResult;
            }
            paudec->m_hdrdecsts = HDR_DONE;
            break;

        }
    }
    // check if we have successfully decoded filter info.
    // If the current frame is seekable and we came here, we have got 
    // the valid filter info.
    if (pau->m_bSeekable == WMAB_TRUE) {
        paudec->m_bGotValidFilterInfo = WMAB_TRUE;
    }
exit:
    
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    
    return wmaResult;
} // prvDecodeSubFrameHeaderPureLosslessMode

//V3 LLMB. Chao.
#if !WMA_OPT_LOSSLESSDECLSL_ARM
WMARESULT prvDecodeSubFrameChannelResiduePureLosslessModeVerB (CAudioObject* pau, CAudioObjectDecoder *paudec,
                            PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    I32 iResult;
    U32 uiResidue;
    I32 iResidue;
    CBT * rgiCoefRecon = ppcinfo->m_rgiCoefRecon
            + ppcinfo->m_rgsubfrmconfig[0].m_rgiSubFrameStart[0];
    CBT * rgiLPCResidue = rgiCoefRecon; // share the same memory.
    I32 iLen = ppcinfo->m_cSubFrameSampleHalf;
    PerChannelInfo* ppcInfoComm = ppcinfo;

    U32 iSum;
    U32 iMean = 0;
    U32 iDiv = 1;
    U32 iRem = 0;
    U32 iDivPow2 = 0;

    U32 uiOffset0 = 1 << (pau->m_iResidueMemScaling - 1);
    U32 uiOffset1 = 1 << pau->m_iResidueMemScaling;
    I16 iShift0 = pau->m_iResidueMemScaling;
    I16 iShift1 = (pau->m_iResidueMemScaling + 1);

    if ((ppcinfo->m_rgsubfrmconfig[0].m_rgiSubFrameStart[0]) >= pau->m_cFrameSampleHalf)
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

    if ((ppcinfo->m_rgsubfrmconfig[0].m_rgiSubFrameStart[0] + iLen) > pau->m_cFrameSampleHalf)
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

    if (ppcInfoComm->m_cLMSPredictors > LLMB_CLMSFLT_TTL_MAX ||
            ppcInfoComm->m_cLMSPredictors < LLMB_CLMSFLT_TTL_MIN)
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

    { // No arithmatic coding.
        switch (paudec->m_LLMdecsts) 
        {
            case CH_BEGIN:
                paudec->m_LLMdecsts = CH_TRANSIENT;

            case CH_TRANSIENT:
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                if (iResult == WMAB_TRUE) {// There is transient.
                    paudec->m_LLMdecsts = CH_TRANSIENT_POS;
                    ppcinfo->m_iTransientPosition = 0;
                }
                else {                     // There is no transient.
                    paudec->m_LLMdecsts = CH_DIVISOR;
                    ppcinfo->m_iTransientPosition = -1;
                }

            case CH_TRANSIENT_POS:
                if (ppcinfo->m_iTransientPosition != -1) {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LOG2(iLen), (U32 *)&iResult));
                    ppcinfo->m_iTransientPosition = iResult;
                }
                paudec->m_LLMdecsts = CH_DIVISOR;

            case CH_DIVISOR:
                if (pau->m_bSeekable == WMAB_TRUE) {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, pau->m_nValidBitsPerSample, (U32 *)&iResult));
                    iMean = iResult;
                    // bug. should be
                    // ppcInfoComm->m_iSum = iMean * (1 << pau->m_iResidueMemScaling);
                    // see the resetallenc for comments.
                    // we can not fix for backward compatibility reasons
                    ppcInfoComm->m_iSum = iMean * LLMA_RESIDUE_MEMORY_TTLWEIGHT;
                    ppcInfoComm->m_iSum = (ppcInfoComm->m_iSum << 1);
                }
                paudec->m_LLMdecsts = CH_COEF;
                paudec->m_Dec1stSplsts = FIRSTSPL_SIGN_BIT;
                pau->m_iCurrReconCoef = 0;

            case CH_COEF:
                // read subframe coefficients residue.
                if (pau->m_bSeekable == WMAB_TRUE) {
                    // Read the first coefficient.
                    if (pau->m_iCurrReconCoef == 0) { 
                        if(pau->m_bDoInterChDecorr == DO_CHANNEL_MIXING) {

                        // #ifdef WMALSL_C_OPTIMIZATION
                        #if 0    //can not get more than 24 bits at one time.
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, (UInt)(pau->m_nValidBitsPerSample+1), (U32 *)&iResult));
                            if (iResult & ((I32)1 << pau->m_nValidBitsPerSample))
                                iResult = (~(((I32)1 << pau->m_nValidBitsPerSample) - 1)) | iResult;
                            rgiLPCResidue[0] = (I32)iResult;
                        #else //original C code
                            switch (paudec->m_Dec1stSplsts)
                            {
                            case FIRSTSPL_SIGN_BIT:
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, (UInt)(1), (U32 *)&iResult));
                                paudec->m_1stSplSignBit = iResult;
                                paudec->m_Dec1stSplsts = FIRSTSPL_OTHER_BITS;

                            case FIRSTSPL_OTHER_BITS:
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, (UInt)(pau->m_nValidBitsPerSample), (U32 *)&iResult));
                                iResult = iResult | (paudec->m_1stSplSignBit << pau->m_nValidBitsPerSample);
                                if (iResult & ((I32)1 << (pau->m_nValidBitsPerSample + 1 - 1)))
                                    iResult = (~(((I32)1 << (pau->m_nValidBitsPerSample + 1 - 1)) - 1)) | iResult;
                                rgiLPCResidue[0] = (I32)iResult;
                            
                            }
                        #endif //WMALSL_C_OPTIMIZATION

                        }
                        else if (pau->m_bDoInterChDecorr == NO_CHANNEL_MIXING) {
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, (UInt)(pau->m_nValidBitsPerSample), (U32 *)&iResult));
                            if (iResult & ((I32)1 << (pau->m_nValidBitsPerSample - 1)))
                                iResult = (~(((I32)1 << (pau->m_nValidBitsPerSample - 1)) - 1)) | iResult;
                            rgiLPCResidue[0] = (I32)iResult;
                        }
                        pau->m_iCurrReconCoef++;
                    }
                }

                for (; pau->m_iCurrReconCoef < iLen; pau->m_iCurrReconCoef++) {
                    switch (paudec->m_Colombdecsts)
                    {
                        case FIRST_PART:
                            TRACEWMA_EXIT(wmaResult, ibstrmCountSerial1Bits(&paudec->m_ibstrm, &paudec->m_iResQ));

                            if (paudec->m_iResQ < RESQ_ESCAPE_VALUE) {
                                paudec->m_Colombdecsts = SECOND_PART;
                                goto COLOMB_SECOND_PART;
                            }
                            else {
                                paudec->m_Colombdecsts = FIRST_PART_B;
                            }

                        case FIRST_PART_B:                    
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 5, (U32 *)&iResult));
                            // assert(paudec->m_iResQBits <= 32);
                            if (iResult + 1 > 32)
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                            paudec->m_iResQBits = iResult + 1;
                            paudec->m_Colombdecsts = FIRST_PART_C;

                        case FIRST_PART_C:
                            if (paudec->m_iResQBits <= 24) {
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, paudec->m_iResQBits, (U32 *)&iResult));
                                paudec->m_iResQ += iResult;
                            }
                            else { // 24 - 32 bits
                                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, paudec->m_iResQBits));                        
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, paudec->m_iResQBits - 24, (U32 *)&iResult));
                                paudec->m_iResQ += (((U32)iResult) << 24);
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 24, (U32 *)&iResult));
                                paudec->m_iResQ += ((U32)iResult);
                            }
                            paudec->m_Colombdecsts = SECOND_PART;

COLOMB_SECOND_PART:                     
                        case SECOND_PART:
                            iResult = 0;
                            iSum = ppcInfoComm->m_iSum;
                            iMean = (iSum + uiOffset1) >> iShift1;
                            // Find the first 2^n >= mean(abs(residue)).
                            // for (iDivPow2 = 0; ((U32)1 << iDivPow2) < iMean; iDivPow2++);
                            CEILOFLOG2(iDivPow2, iMean);
                                
                            if (iDivPow2 <= 24) {
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, iDivPow2, (U32 *)&iResult));
                                // actually iRem does not need to be in paudec. Doing that just to be consistent with iResQ.
                                iRem = iResult;
                            }
                            else { // 24-32 (actually 27?)
                                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, iDivPow2));
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, iDivPow2 - 24, (U32 *)&iResult));
                                // actually iRem does not need to be in paudec. Doing that just to be consistent with iResQ.
                                iRem = (((U32)iResult) << 24);
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 24, (U32 *)&iResult));
                                // actually iRem does not need to be in paudec. Doing that just to be consistent with iResQ.
                                iRem += ((U32)iResult);
                            }
                    }

                    uiResidue = (paudec->m_iResQ << iDivPow2) + iRem;
                    ppcInfoComm->m_iSum  = uiResidue + ppcInfoComm->m_iSum - (ppcInfoComm->m_iSum >> iShift0);  

                    iResidue = (I32)(uiResidue >> 1);
                    if (uiResidue & 0x1) {
                        iResidue = -iResidue - 1;
                        // iResidue = ~iResidue;
                    }

                    rgiLPCResidue[pau->m_iCurrReconCoef] = iResidue;

                    // set up for next coefficient.
                    paudec->m_Colombdecsts = FIRST_PART;
                    paudec->m_iResQ = 0;
                    paudec->m_iRem = 0;

                }
                paudec->m_LLMdecsts = CH_DONE;
            case CH_DONE:
                ;
        }
   }


    // LMSs
    if (pau->m_bSeekable == WMAB_TRUE) {
        ppcInfoComm->m_iUpdSpdUpSamples = ppcInfoComm->m_cSubFrameSampleHalf;
    }

    prvDecoderCDLMSPredictorHelper(paudec, ppcinfo, ppcinfo, rgiCoefRecon, iLen);

exit:
    return wmaResult;
} // prvDecodeSubFrameChannelResiduePureLosslessModeVerB
#endif //WMA_OPT_LOSSLESSDECLSL_ARM

WMARESULT prvDecodeSubFrameChannelRawPCMPureLosslessMode (CAudioObject* pau, CAudioObjectDecoder *paudec,
                            PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    U32 iResult;
    I32 iLen = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;
    // Float * rgfltRecon = (Float *)ppcinfo->m_rgfltCoefRecon;
    CBT * rgiRecon = ppcinfo->m_rgiCoefRecon
            + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
    assert((void *)ppcinfo->m_rgiCoefRecon == (void *)ppcinfo->m_rgCoefRecon); // verify above change.

    assert(WMAB_TRUE == pau->m_bPureLosslessMode);
    assert(pau->m_iVersion >= 3);

    assert(sizeof(I32) == sizeof(Float)); // necessary for memory share.                        

    switch (paudec->m_LLMdecsts) 
    {
        case CH_BEGIN:
            paudec->m_LLMdecsts = CH_COEF;

        case CH_COEF:
            // read subframe coefficients lpc residue.
            // assert(pau->m_iPCMTrailZeros < pau->m_nValidBitsPerSample);
            if (pau->m_iPCMTrailZeros >= pau->m_nValidBitsPerSample)
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

            for (; pau->m_iCurrReconCoef < iLen; pau->m_iCurrReconCoef++) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, pau->m_nValidBitsPerSample- pau->m_iPCMTrailZeros, (U32 *)&iResult));
                if (iResult & ((I32)1 << (pau->m_nValidBitsPerSample - pau->m_iPCMTrailZeros - 1)))
                    iResult = (~(((I32)1 << (pau->m_nValidBitsPerSample - pau->m_iPCMTrailZeros - 1)) - 1)) | iResult;
                rgiRecon[pau->m_iCurrReconCoef] = (I32)(iResult);
                   
            }
            paudec->m_LLMdecsts = CH_DONE;

        case CH_DONE:
            ;
    }
exit:
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;

} // prvDecodeSubFrameChannelRawPCMPureLosslessMode

Void prvDecoderCDLMSPredictorHelper(CAudioObjectDecoder *paudec, PerChannelInfo* ppcinfoComm, PerChannelInfo* ppcinfo, CBT * rgiResidue, I32 iDataLen)
{
    CAudioObject * pau = paudec->pau;
    I32 i;
    I32 Q1;
    I32 Q2;
    I32 Q3;

    Q1 = ppcinfoComm->m_iUpdSpdUpSamples;
    if (ppcinfoComm->m_iTransientPosition >= 0) {
        if (ppcinfoComm->m_iTransientPosition <= ppcinfoComm->m_iUpdSpdUpSamples) {
            Q1 = MAX(ppcinfoComm->m_iTransientPosition + (ppcinfo->m_cSubFrameSampleHalf >> 1), ppcinfoComm->m_iUpdSpdUpSamples);
            ppcinfoComm->m_iUpdSpdUpSamples = Q1 - ppcinfo->m_cSubFrameSampleHalf;
            Q1 = MIN(Q1, ppcinfo->m_cSubFrameSampleHalf);
            Q2 = Q1;
            Q3 = Q2;
        }
        else {
            Q2 = ppcinfoComm->m_iTransientPosition;
            assert(ppcinfoComm->m_iUpdSpdUpSamples < ppcinfo->m_cSubFrameSampleHalf);
            assert(ppcinfoComm->m_iTransientPosition < ppcinfo->m_cSubFrameSampleHalf);
            Q3 = ppcinfoComm->m_iTransientPosition + (ppcinfo->m_cSubFrameSampleHalf >> 1);
            ppcinfoComm->m_iUpdSpdUpSamples = Q3 - ppcinfo->m_cSubFrameSampleHalf;
            Q3 = MIN(Q3, ppcinfo->m_cSubFrameSampleHalf); 
        }
    }
    else {
        ppcinfoComm->m_iUpdSpdUpSamples = ppcinfoComm->m_iUpdSpdUpSamples - ppcinfo->m_cSubFrameSampleHalf;
        Q1 = MIN(Q1, ppcinfo->m_cSubFrameSampleHalf);
        Q2 = Q1;
        Q3 = Q2;        
    }
    if (ppcinfoComm->m_iUpdSpdUpSamples  < 0) ppcinfoComm->m_iUpdSpdUpSamples = 0;

    for (i = ppcinfoComm->m_cLMSPredictors - 1; i >= 0; i--) {
        LMSPredictor * pLMSPredictor = ppcinfoComm->m_rgLMSPredictors + i;
        if (Q1 > 0) {
            prvLMSPredictorUpdateSpeedChange(pau, pLMSPredictor, WMAB_TRUE);
            paudec->pprvDecLMSPredictor(pau, pLMSPredictor, rgiResidue, Q1 - 0);
            prvLMSPredictorUpdateSpeedChange(pau, pLMSPredictor, WMAB_FALSE);        
        }
        if (Q2 > Q1) 
            paudec->pprvDecLMSPredictor(pau, pLMSPredictor, rgiResidue + Q1, Q2 - Q1);
        if (Q3 > Q2) {
            prvLMSPredictorUpdateSpeedChange(pau, pLMSPredictor, WMAB_TRUE);
            paudec->pprvDecLMSPredictor(pau, pLMSPredictor, rgiResidue + Q2, Q3 - Q2);
            prvLMSPredictorUpdateSpeedChange(pau, pLMSPredictor, WMAB_FALSE);
        }
        if (iDataLen > Q3)
            paudec->pprvDecLMSPredictor(pau, pLMSPredictor, rgiResidue + Q3, iDataLen - Q3);
    }
    return;
} // prvDecoderCDLMSPredictorHelper

#endif // BUILD_WMALSL

