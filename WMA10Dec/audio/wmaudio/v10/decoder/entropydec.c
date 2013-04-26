//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains the logic common to WMA Std, WMA Pro & WMA Lossless decoders.
// Also contains a few stub functions, if actual implementations are not needed.
//*@@@---@@@@******************************************************************

#include "msaudiodec.h"
#include "huffdec.h"
#include "AutoProfile.h"  
#include "entropydec.h"

#if defined (BUILD_WMAPROLBRV1)
#include "fex.h"
#endif

//#define DEBUG_DECODE_TRACE
#undef DEBUG_DECODE_TRACE
#if defined (DEBUG_DECODE_TRACE)
extern unsigned int g_ulOutputSamples;
#define DEBUG_TRACE_QUANT(a, b, c)                                              \
                WMAPrintf("%d %d %d %u\n", a, b, c, g_ulOutputSamples);                                  \
                FFLUSH (stdout);
#pragma COMPILER_MESSAGE(__FILE__ "(43) : Warning - m_iQuantStepSize Debug Code Enabled.")
#else
#define DEBUG_TRACE_QUANT(a, b, c)
#endif

#if defined (_DEBUG)
#define COUNT_BITS(a,b) a += b
#else
#define COUNT_BITS(a,b)
#endif

//*****************************************************************************************
//
// prvDecodeFrameHeader
//
//*****************************************************************************************
WMARESULT prvDecodeFrameHeader (CAudioObjectDecoder* paudec)
{   
    WMARESULT wmaResult     = WMA_OK;
    CAudioObject* pau       = paudec->pau;        
    PerChannelInfo* ppcinfo = NULL;
    SubFrameConfigInfo* psubfrmconfig = NULL;
    
    I16 iCh;
    U32 iResult;
    I16 iSizePrev = 0, iSizeCurr = 0;
    I32 cBitSize  = 0;
    I32 cBitSize0 = 0;
    I32 cBitSize1 = 0;
                
#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_FRAME_HEADER_PROFILE);
#endif

    if (pau->m_fAllowSubFrame && pau->m_iMaxSubFrameDiv <= 1)        //avoid log(0) below
    {
        REPORT_BITSTREAM_CORRUPTION();
        wmaResult = WMA_E_BROKEN_FRAME;
        CHECKWMA_EXIT(wmaResult);
    }

    if (pau->m_bPureLosslessMode == WMAB_TRUE) {
        pau->m_u32TrailingSize = 0;
    }
    while (paudec->m_fhdrdecsts != FHDR_DONE) 
    {        
        switch (paudec->m_fhdrdecsts)
        {
        case FHDR_PREV:
            if (pau->m_fAllowSubFrame && pau->m_iVersion <= 2)
            {
                //peek enough bits for this "case" if not enough will be on hold
                Int cBitsNeed = LOG2 ((U32) LOG2 ((U32)pau->m_iMaxSubFrameDiv)) + 1;
                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, cBitsNeed * 2));
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitsNeed, &iResult));
                iSizePrev = (I16)(pau->m_cFrameSampleHalf / (1 << iResult));
                
                //current
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitsNeed, &iResult));
                iSizeCurr = (I16)(pau->m_cFrameSampleHalf / (1 << iResult));
                
                assert (iSizePrev != 0 && iSizeCurr != 0);
                if (iSizePrev  < pau->m_cMinSubFrameSampleHalf || iSizePrev > pau->m_cFrameSampleHalf ||
                    iSizeCurr  < pau->m_cMinSubFrameSampleHalf || iSizeCurr > pau->m_cFrameSampleHalf)
                {
                    REPORT_BITSTREAM_CORRUPTION();
                    return TraceResult(WMA_E_BROKEN_FRAME);
                }
                
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    ppcinfo = pau->m_rgpcinfo + iCh;
                    //only useful in case of packet loss and prev info lost or first in sequece
                    assert (ppcinfo->m_iCurrSubFrame == 0);
                    ppcinfo->m_rgsubfrmconfig [CONFIG_CURRFRM].m_rgiSubFrameSize [-1] = iSizePrev;

                    //first frame in super and first sub frame; init
                    ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame = 0;
                    ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [0] = iSizeCurr;
                    ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0] = 0;
                    ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame++;
                }

                paudec->m_fhdrdecsts = FHDR_ADJUST_TIMESTAMP;
                break;
            
            } else if (pau->m_iVersion > 2) {   // Version 3 or above

                paudec->m_fhdrdecsts = FHDR_SIZE;
                prvInitDecodeTileHdr(paudec, CONFIG_CURRFRM);
                break;
            }
            else            //non - superframe
            {
                paudec->m_fhdrdecsts = FHDR_ADJUST_TIMESTAMP;
                break;
            }

        case FHDR_SIZE:
            if (pau->m_fWriteFrameSize)
            {
                assert(pau->m_iVersion > 2);
#ifdef BUILD_UES
                if(WMAB_TRUE == paudec->pau->m_fUES)
                {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, UES_NUM_OF_BITS_FOR_FRAMESIZE, (U32 *)&pau->m_cComprFrameSizeBits));
                }
                else
#endif
                {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, pau->m_cBitsBitsPacketLength, (U32 *)&pau->m_cComprFrameSizeBits));
                }

                //WMAPrintf("Actual Frame Size: %d\n", pau->m_cComprFrameSizeBits);
                if (paudec->m_fSPDIF)
                { 
                    ibstrmSetGap(&paudec->m_ibstrm, pau->m_cComprFrameSizeBits - pau->m_cBitsBitsPacketLength);
                }
            }
            paudec->m_fhdrdecsts = FHDR_CURR;

        case  FHDR_CURR:
            if (pau->m_iVersion > 2)
            {
                TRACEWMA_EXIT(wmaResult, prvDecodeTileHdr(paudec, CONFIG_CURRFRM));

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
    #ifdef WMA_COMPRESSION_TOOL
                // Professional Encoder Related
                // V3 write subframing configuration meta file.
                if (paudec->m_fWriteMetaFile == WMAB_TRUE){
                    TRACEWMA_EXIT (wmaResult, prvWriteMetaFileSubFrmConfig (paudec, paudec->pau->m_rgpcinfo, CONFIG_CURRFRM, paudec->m_pMetaFileDir));
                }
    #endif //WMA_COMPRESSION_TOOL
#endif // #if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
            }
            paudec->m_ppxformsts = PPXFORM_BEGIN;
            paudec->m_fhdrdecsts = FHDR_PPXFORM;
            
        case  FHDR_PPXFORM:
            //assert(pau->m_iVersion >= 3);
            TRACEWMA_EXIT(wmaResult, prvEntropyDecodePostProcXform(paudec));
            paudec->m_fhdrdecsts = FHDR_DRC_PARAM;

        case  FHDR_DRC_PARAM:
            if (pau->m_fGenerateDrcParams)
            {
                assert(pau->m_iVersion > 2);
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, BITS_PER_BYTE, &iResult));
                pau->m_ucDrcFrameScaleFactor = (U8)iResult;
                //WMAFprintf(stdout, "Fac=%d\n", pau->m_ucDrcFrameScaleFactor);
            }
            paudec->m_fhdrdecsts = FHDR_SILENCE;
            break;

        case FHDR_SILENCE:
            // Leading/trailing silence for v3 only
            iResult = WMAB_FALSE;
            if (pau->m_iVersion > 2)
            {
                pau->m_fLeadingSilence = WMAB_FALSE;
                pau->m_fTrailingSilence = WMAB_FALSE;

                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            }

            if (WMAB_FALSE == iResult)
            {
                // No leading or trailing silence
                paudec->m_fhdrdecsts = FHDR_ADJUST_TIMESTAMP;
            }
            else
            {
                // Leading or trailing silence: find out lead/trail or both
                paudec->m_fhdrdecsts = FHDR_SILENCE_LEAD_FLAG;
            }
            break;

        case FHDR_SILENCE_LEAD_FLAG:
            // We know we need to look at 1 more bits: reserve them, go on hold if not avail
            // Look for leading silence indicator
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_fLeadingSilence = iResult;

            if (iResult)
            {
                // Leading silence: we now need to read the size of leading silence
                paudec->m_fhdrdecsts = FHDR_SILENCE_LEAD;
            }
            else
            {
                paudec->m_fhdrdecsts = FHDR_SILENCE_TRAIL_FLAG;
            }

            break;

        case FHDR_SILENCE_LEAD:
            {
                const I32 cBit = LOG2(pau->m_cFrameSample);
                iResult = 0;

                // Read in the amount of leading silence to discard
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, cBit, &iResult));
                pau->m_u32LeadingSize = iResult;
            }
            paudec->m_fhdrdecsts = FHDR_SILENCE_TRAIL_FLAG;

            break;

        case FHDR_SILENCE_TRAIL_FLAG:
            // Next, check for trailing silence
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            if (iResult)
            {
                // Trailing silence: we now need to read the end-of-PCM marker
                paudec->m_fhdrdecsts = FHDR_SILENCE_TRAIL;
            }
            else
                paudec->m_fhdrdecsts = FHDR_ADJUST_TIMESTAMP;

            break;

        case FHDR_SILENCE_TRAIL:
            {
                const I32 cBit = LOG2(pau->m_cFrameSample);
                iResult = 0;

                // Read in the amount of trailing silence to discard
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, cBit, &iResult));
                assert (pau->m_u32TrailingSize == 0);
                pau->m_u32TrailingSize = iResult;
                pau->m_fTrailingSilence = WMAB_TRUE;
            }
            paudec->m_fhdrdecsts = FHDR_ADJUST_TIMESTAMP;
            break;

        case FHDR_ADJUST_TIMESTAMP:
            if (pau->m_iVersion > 2)
            {
        #ifdef WMA_COMPRESSION_TOOL
                 paudec->m_ulCurrSeekPoint = prvContinuousDecodeAdjustment(pau);                                            
        #endif //WMA_COMPRESSION_TOOL
                // If we crossed packet boundary, subtract continuous decode adjustment
                // from the timestamp
                if (paudec->m_fContinuousDecodeAdj &&
                    0 == paudec->m_iContinuousDecodeCountdown &&
                    WMAB_FALSE == pau->m_bReconProc)
                {
                    I32 iContinuousDecodeAdj;

                    iContinuousDecodeAdj = prvContinuousDecodeAdjustment(pau);
                    if (iContinuousDecodeAdj <= paudec->m_iCurrPresTime) {
                        // V3: Normally Encoder puts the presentation time of the middle of the subframe which starts a packet as
                        // that packet's timestamp. But if there is trailing silience and if the last frame starts the packet, 
                        // Encoder put the last PCM's presentation as the last packet's timestamp. In that case, we need to 
                        // substract (duration - trailsize).
                        // currently, the encoder timestamp does not consider trailing silence (see CodecDSP bug #4815)
                        // The handling of last frame below is causing timestamp mismatch (wmadec_s).
                        // keep as is for now since this is not a critical issue. hongwang 4/6/05
                        if (pau->m_u32TrailingSize > 0 && pau->m_bPureLosslessMode != WMAB_TRUE)
                        {
                            Int iDuration;
                            U32 u32TrailingSizeAdjusted = AU_HALF_OR_DOUBLE(pau->m_fHalfTransform, pau->m_fPad2XTransform, pau->m_u32TrailingSize);
                            prvGetFramePCM (pau, &iDuration);
                            // GetFramePCM does not return duration actually. The return includes the left over in PCM buffer.
                            // Fortunately GetFramePCM does not change iPCMReconEnd/Start and iEnd-iStart is the size
                            // of the left over. Therefore, the true iDuration is iDuration - (iEnd - iStart).
                            // Certainly, if we make sure PCMBuffer moving only happens after we output all available
                            // PCM samples (like what we did in SAVE_PCMBUFFER_IN_PLLM, we have iEnd == iStart thus 
                            // no need to update iDuration.
                            assert(pau->m_iPCMReconEnd >= pau->m_iPCMReconStart);
                            if (pau->m_iPCMReconEnd > pau->m_iPCMReconStart)
                                iDuration = iDuration - (pau->m_iPCMReconEnd - pau->m_iPCMReconStart);

                            assert(iDuration >= (Int)u32TrailingSizeAdjusted);
                            if (iDuration >= (Int)u32TrailingSizeAdjusted)
                            {
                                I32 iLastFrameAdj = iDuration - u32TrailingSizeAdjusted;
                                assert(iLastFrameAdj >= 0);
                                if (iLastFrameAdj < iContinuousDecodeAdj)
                                    paudec->m_iCurrPresTime -= iLastFrameAdj;
                                else
                                    paudec->m_iCurrPresTime -= iContinuousDecodeAdj;
                            }
                            if (paudec->m_iCurrPresTime < 0)
                                paudec->m_iCurrPresTime = 0;
                        }
                        else 
                        {
                            paudec->m_iCurrPresTime -= iContinuousDecodeAdj;
                        }
                    }
                    else { 
                        //* The problem also happens when there is bit stuff in the first packet
                        //  after the first frame. But that is a bug which will be fixed by the
                        //  same checkin.
                        //* If the first frame uses more than 1 packet (Unified WMA). 
                        //  The second packet will have paudec->m_iCurrPresTime = iContinuousDecodeAdj
                        //  Due to some round error, iContinuousDecodeAdj could be slightly
                        //  bigger than paudec->m_iCurrPresTime. But we should have:
                        paudec->m_iCurrPresTime = 0;
                    }

                    paudec->m_fContinuousDecodeAdj = WMAB_FALSE;
                }
#if defined(BUILD_WMAPROLBRV2)
                else if (paudec->m_fContinuousDecodeAdj &&
                         0 == paudec->m_iContinuousDecodeCountdown)
                {
                    paudec->m_iCurrPresTime -= prvReconProcDecodeAdjustment(pau);
                    paudec->m_fContinuousDecodeAdj = WMAB_FALSE;
                }
#endif // BUILD_WMAPROLBRV2
            }
            paudec->m_fhdrdecsts = FHDR_DONE;
            break;
        }
    }
    
    if (pau->m_bPureLosslessMode == WMAB_TRUE)
        pau->m_u32ValidSamples = pau->m_cFrameSampleHalf - pau->m_u32TrailingSize;
exit:
    
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    
    return wmaResult;
} // prvDecodeFrameHeader


WMARESULT prvDecodeSubFrameHeader (CAudioObjectDecoder* paudec)
{      
    CAudioObject* pau = paudec->pau;        
    PerChannelInfo* ppcinfo = NULL;
    PerChannelInfoDEC* ppcinfoDEC = NULL;
    SubFrameConfigInfo* psubfrmconfig = NULL;
    
    Bool fSkipAll;
    Bool fUpdateMask = WMAB_FALSE;
    I16  *piChannel = &paudec->m_iChannel;
    Int iMaskQPrev;
    Int iSizeNext = pau->m_cFrameSampleHalf;
    I16 iStartMin; 
    I16 iSizeMin;
    I16 iCh, iChSrc;
    
    WMARESULT   wmaResult = WMA_OK;
    U32         iResult;

#if defined (_DEBUG)
    Int cBitOrig = paudec->m_ibstrm.m_cFrmBitCnt;
#endif 

#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_SUBFRAME_HEADER_PROFILE);
#endif


    while (paudec->m_hdrdecsts != HDR_DONE) {
        switch (paudec->m_hdrdecsts)
        {
        case HDR_SIZE:
            if (pau->m_iVersion <= 2)
            {
                if (pau->m_fAllowSubFrame) 
                {
                    //peek enough bits for this "case" if not enough will be on hold
                    Int cBitsNeed = LOG2 ((U32) LOG2 ((U32)pau->m_iMaxSubFrameDiv)) + 1;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBitsNeed, &iResult));
                    iSizeNext = pau->m_cFrameSampleHalf / (1 << iResult);
                    if (iSizeNext  < pau->m_cMinSubFrameSampleHalf || iSizeNext > pau->m_cFrameSampleHalf)
                    {
                        REPORT_BITSTREAM_CORRUPTION();
                        return TraceResult(WMA_E_BROKEN_FRAME);
                    }
                }
                pau->m_cChInTile = pau->m_cChannel;
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    pau->m_rgiChInTile [iCh] = iCh;
                }
                wmaResult = prvUpdateSubFrameConfig(paudec, iSizeNext);
                if (WMA_FAILED(wmaResult))
                {
                    int dummy = TraceResult(wmaResult);
                    REPORT_BITSTREAM_CORRUPTION();
                    goto exit;
                }
            }
            else 
            {
                //search for tile starting position
                I32 cSampleLeft = pau->m_cFrameSampleHalf * pau->m_cChannel;
                ppcinfo = pau->m_rgpcinfo;
                iStartMin = (I16) pau->m_cFrameSampleHalf;
                iSizeMin  = (I16) pau->m_cFrameSampleHalf;
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {            
//                    I16* piStart = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart + ppcinfo->m_iCurrSubFrame;
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
//                    if (iStartMin == rgiStart [*piSubFrmCurr])
                    if (iStartMin == *rgiStart)
                    {
                        if (iSizeMin == rgiSize [*piSubFrmCurr])
                        {                                   
                            pau->m_rgiChInTile [pau->m_cChInTile] = iCh;
                            pau->m_cChInTile++;
                            ppcinfo->m_iSizeNext = (I16) rgiSize [*piSubFrmCurr + 1];
                            ppcinfo->m_iSizeCurr = (I16) rgiSize [*piSubFrmCurr];
                            ppcinfo->m_iSizePrev = (I16) rgiSize [*piSubFrmCurr - 1];
                            cSampleLeft -= rgiSize [*piSubFrmCurr];
                            *rgiStart += rgiSize [*piSubFrmCurr];
                        }
                    }
                    ppcinfo++;
                }
//              assert (pau->m_cChInTile <= pau->m_cChannel && pau->m_cChInTile > 0);
//              assert (cSampleLeft >= 0);
                if (pau->m_cChInTile > pau->m_cChannel || pau->m_cChInTile <= 0 || cSampleLeft < 0) {
                    REPORT_BITSTREAM_CORRUPTION();
                    wmaResult = TraceResult(WMA_E_BROKEN_FRAME);
                    goto exit;
                }

                // Initialize m_cLastCodedIndex
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    ppcinfo->m_cLastCodedIndex = 1;
                }
                pau->m_cLastCodedIndex = 1;

                paudec->m_fLastSubFrame = (cSampleLeft == 0);                
            }
            
            ASSERTWMA_EXIT(wmaResult, auAdaptToSubFrameConfig (pau));
            ASSERTWMA_EXIT(wmaResult, auAdaptToSubFrameConfigDEC (pau));
            
            if (pau->m_iVersion <= 2)
            {
                paudec->m_hdrdecsts = HDR_V2_POWER;
                break;
            }
            else 
            {                
                // V3 LLM. Chao. Add. Coordinate with AnchorMask. 

                for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;

                    // Initializations for mask updates
                    if (ppcinfo->m_iCurrSubFrame == 0) 
                    {
                        ppcinfo->m_fAnchorMaskAvailable = WMAB_FALSE;
                        ppcinfo->m_iMaskQuantMultiplier = 1;
                        memset(ppcinfo->m_rgiMaskQ, 0, sizeof(Int) * NUM_BARK_BAND);
                        memset(ppcinfo->m_rgiMaskQResampled, 0, sizeof(Int) * NUM_BARK_BAND);
                        ppcinfo->m_iMaxMaskQ = 0;
                    }            
                
                    prvSetDecTable  (paudec, ppcinfo, 0);
                }
                paudec->m_hdrdecsts = HDR_V3_ESCAPE;
            }
            break;

        case HDR_V3_ESCAPE:
            // V3 Subframe Escape
#ifdef BUILD_UES
            if(WMAB_FALSE == paudec->pau->m_fUES || 
                (WMAB_TRUE == paudec->pau->m_fUES && paudec->m_pCUESdec->m_cbAudioPayloadLeft>0))
#endif
            {
                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, 1+2+4+15));
            }
            paudec->m_iSubfrmEscDataBits = 0;
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, 1, &iResult));
            if (0 == iResult)
                paudec->m_hdrdecsts = HDR_V3_LLM;
            else
            {
                // Find out how many data bits are coming
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, 2, &iResult));
                if (iResult > 0)
                {
                    assert(iResult <= 3);
                    paudec->m_iSubfrmEscDataBits = iResult;
                    paudec->m_hdrdecsts = HDR_V3_ESCAPE_SKIPDATA;
                }
                else
                {
                    I32 iSubframeEscBitsLog2;

                    // First, read in the width (# bits) of next item
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, 4,
                        (U32 *)&iSubframeEscBitsLog2));

                    // Read in the number of data bits coming our way
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm,
                        iSubframeEscBitsLog2, &iResult));

                    // Since zero is invalid # data bits, encoder maps "1" to zero.
                    // Add that 1 back.
                    paudec->m_iSubfrmEscDataBits = iResult + 1;
                    paudec->m_hdrdecsts = HDR_V3_ESCAPE_SKIPDATA;
                }
            }

#if defined(BUILD_WMAPROLBRV1) && !defined(WRITE_PLUS_TO_FILE)
            pau->m_iPlusBits = 0;
            if (WMAB_FALSE == paudec->m_bSkipPlus)
            {
                if (pau->m_bPlusV1 || pau->m_bPlusV2)
                {
                    pau->m_iPlusBits = paudec->m_iSubfrmEscDataBits;
                    paudec->m_iFexByteCnt = 0;
                    paudec->m_hdrdecsts = HDR_V3_FREQEX_DATA;
                }
            }
#endif // BUILD_WMAPROLBRV1 && WRITE_PLUS_TO_FILE
            break;

        case HDR_V3_FREQEX_DATA:
            while (paudec->m_iSubfrmEscDataBits > 0)
            {
                Bool bOverflow = WMAB_FALSE;
                I32 iCurrReq = min(8, paudec->m_iSubfrmEscDataBits);

                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm,
                    iCurrReq, &iResult));

                if (iCurrReq < 8)
                    iResult = (U8)iResult<<(8-iCurrReq);

#if defined(BUILD_WMAPROLBRV1)
                if (paudec->m_iFexByteCnt >= pau->m_iPlusBsSize)
                {
                    // assert(WMAB_FALSE);
                    pau->m_iPlusBits = 0; // skip any decoding of +
                    bOverflow = WMAB_TRUE;
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                }
                else
                {
                    ((U8*)pau->m_rgiPlusBsBuf)[paudec->m_iFexByteCnt++] = (U8)iResult;
                }
#endif
                paudec->m_iSubfrmEscDataBits -= iCurrReq;
            }
            //printf("%d %d %d %x\n", pau->m_iFrameNumber, paudec->m_iCurrTile,
            //pau->m_iPlusBits, pau->m_rgiPlusBsBuf[0]);

            assert(0 == paudec->m_iSubfrmEscDataBits); // Done skipping bits
            paudec->m_hdrdecsts = HDR_V3_LLM;
            break;

        case HDR_V3_ESCAPE_SKIPDATA:
            // Read 24 bits at a time (LookForBits cannot check for > 24)
            while (paudec->m_iSubfrmEscDataBits > 0)
            {
                I32 iCurrReq = min(24, paudec->m_iSubfrmEscDataBits);

                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm,
                    iCurrReq, &iResult));

                paudec->m_iSubfrmEscDataBits -= iCurrReq;
            }

            assert(0 == paudec->m_iSubfrmEscDataBits); // Done skipping bits
            paudec->m_hdrdecsts = HDR_V3_LLM;
            break;

        case HDR_V3_LLM:
            assert(pau->m_iVersion >= 3);

            //peek enough bits for this "case" if not enough will be on hold
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            if (pau->m_bPlusV2 && (Bool)iResult)           // No UnifiedLLM for Plus V2
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
            pau->m_bUnifiedLLM = (Bool)iResult;
            pau->m_bUnifiedPureLLMCurrFrm = WMAB_FALSE;


            // Save m_bUnifiedLLM information to every channel.
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
            {
                iChSrc = pau->m_rgiChInTile [iCh];
                ppcinfo = pau->m_rgpcinfo + iChSrc;
//                ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_bUnifiedLLM[ppcinfo->m_iCurrSubFrame] = (U8) pau->m_bUnifiedLLM;
            }

            if (pau->m_bUnifiedLLM == WMAB_FALSE) {
                paudec->m_hdrdecsts = HDR_V3_CHXFORM;
                paudec->m_chxformsts = CHXFORM_BEGIN;
                pau->m_bSeekable = WMAB_TRUE; // all lossy frames are seekable.
            }
            else {
                pau->m_bSeekable = WMAB_TRUE; // if not in PURE_IN_MLLM mode, all MLLM frames are seekable.
                paudec->m_hdrdecsts = HDR_PURE_IN_MLLM;
            }
            break;

        case  HDR_V3_CHXFORM:
            // Multi-channel transform data
            assert(pau->m_iVersion >= 3);
            TRACEWMA_EXIT(wmaResult, prvEntropyDecodeChannelXform(paudec));
            paudec->m_hdrdecsts  = HDR_V3_POWER;
            
        case HDR_V3_POWER:

#if defined (BUILD_WMAPRO)
            fSkipAll = WMAB_TRUE;
            
            assert(pau->m_iVersion >= 3);
            
            // Power information
            //peek enough bits for this information if not enough will be on hold
            TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, pau->m_cChInTile));
            
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
            {
                iChSrc = pau->m_rgiChInTile [iCh];
                ppcinfo = pau->m_rgpcinfo + iChSrc;                
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                ppcinfo->m_iPower = iResult;
                fSkipAll &= (ppcinfo->m_iPower == 0);

                // Do the mask resampling for this channel
                TRACEWMA_EXIT(wmaResult, prvPrepareResampledMaskV3_Channel(pau, ppcinfo));
            }
            
            // shift it back by the minimum for decode or in case of exit
            // Version 2 does not come here
            // 90 for 16 bits, 112 for 20 bits, 135 for 24 bits.
            pau->m_iQuantStepSize = 90 * pau->m_nValidBitsPerSample / 16;
                     
            paudec->m_iQuantStepSign    = INT_MAX;

            if (fSkipAll) {
#               if defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
                // no bits will be read
                if (pau->m_iWeightingMode == LPC_MODE) 
                    TRACEWMA_EXIT(wmaResult, prvDecodeSubFrameHeaderLpc(paudec));
#               endif  // defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)

                paudec->m_hdrdecsts = HDR_DONE;
                goto exit;
            }
#endif // BUILD_WMAPRO
            paudec->m_hdrdecsts = HDR_V3_VECCODER_POSEXIST;
            break;

        case HDR_PURE_IN_MLLM:
#if defined BUILD_WMAPRO
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bUnifiedPureLLMCurrFrm = (Bool)iResult;
//            assert(pau->m_bMLLMUsePLLM == WMAB_FALSE); // not supported now.
            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
    #if !defined (BUILD_WMAPRO_PLLM)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);                
    #endif //(BUILD_WMAPRO_PLLM)
                paudec->m_hdrdecsts = HDR_PURE_IN_MLLM_FIRST_FRM;
                // This is a frame level flag. Once we set it to be true, we don't change it back later.
                pau->m_bEnforcedUnifiedLLM = WMAB_TRUE;
            }
            else {
                paudec->m_hdrdecsts = HDR_V3_RAWPCM_LLM;
            }
            break;
#endif //BUILD_WMAPRO


        case HDR_PURE_IN_MLLM_FIRST_FRM:

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bFirstUnifiedPureLLMFrm = (Bool)iResult;
#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            paudec->m_hdrdecsts = HDR_PURE_IN_MLLM_LAST_FRM;

        case HDR_PURE_IN_MLLM_LAST_FRM:

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bLastUnifiedPureLLMFrm = (Bool)iResult;
#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            paudec->m_hdrdecsts  = HDR_PURE_IN_MLLM_SEEKABLE;

        case HDR_PURE_IN_MLLM_SEEKABLE:

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bSeekable = (Bool)iResult;
            paudec->m_hdrdecsts = HDR_V3_RAWPCM_LLM;

#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

        case HDR_V3_RAWPCM_LLM:
#if defined (BUILD_WMAPRO)
            // RAW PCM or LPC?
            assert(pau->m_bUnifiedLLM == WMAB_TRUE);
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
            pau->m_bOutputRawPCM = (Bool)iResult;
#endif // BUILD_WMAPRO
            paudec->m_hdrdecsts = HDR_V3_POWER_LLM;

        case HDR_V3_POWER_LLM:
            {
#if defined (BUILD_WMAPRO)
                PerChannelInfo* rgpcinfo = pau->m_rgpcinfo;

                assert(pau->m_iVersion >= 3);
                assert(pau->m_bUnifiedLLM == WMAB_TRUE);

                // Power information
                //peek enough bits for this information if not enough will be on hold
                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, pau->m_cChannel));

                for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                    // V3 LLM. In encoder we have m_iPower and m_iPowerOri but in decoder we just use m_iPower.
                    // therefore, in decoder, m_iPower represents original channel power or mixed channel power
                    // depending the LLM.
                    ppcinfo->m_iPower = iResult;
                    // Do the mask resampling for this channel:
                    // While lossless decoding itself would not require masks, if a mask
                    // update happens in this tile, then the prediction must be correct.
                    TRACEWMA_EXIT(wmaResult, prvPrepareResampledMaskV3_Channel(pau, ppcinfo));
                }

                //Lossless mode has no noise substitution. ChaoHe 8-20-2001.     
                pau->m_fNoiseSub = WMAB_FALSE;      
                //                paudec->m_hdrdecsts = HDR_MLLM_FILTER;
#endif // BUILD_WMAPRO
                paudec->m_hdrdecsts = HDR_ENTROPY_CODING;
            }
            //            break;

        case HDR_ENTROPY_CODING:
#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)
            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && 
                pau->m_bSeekable == WMAB_TRUE &&
                pau->m_bOutputRawPCM != WMAB_TRUE &&
                pau->m_bFirstUnifiedPureLLMFrm != WMAB_TRUE &&
                pau->m_bLastUnifiedPureLLMFrm != WMAB_TRUE) 
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));    
                if (iResult == WMAB_TRUE) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                } else {
                    pau->m_bDoArithmCoding = (Bool)iResult;
                }
                //assert(pau->m_bDoArithmCoding == WMAB_FALSE);
                if (pau->m_cChInTile != pau->m_cChannel)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
#endif // defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)
            paudec->m_hdrdecsts = HDR_V3_LPC_UNIFIED;
            
        case HDR_V3_LPC_UNIFIED:
#if defined (BUILD_WMAPRO)
            if (pau->m_bV3RTM == WMAB_TRUE) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                pau->m_bDoLPC = (Bool)iResult;
            }
#endif // BUILD_WMAPRO
            paudec->m_hdrdecsts = HDR_V3_LPC_ORDER;

        case HDR_V3_LPC_ORDER:
#if defined (BUILD_WMAPRO)
            if (pau->m_bV3RTM == WMAB_TRUE) {
                if (pau->m_bDoLPC == WMAB_TRUE) {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LPC_ORDER_UNIFIED_BITS, &iResult));
                    pau->m_iLPCOrder = (I16)iResult + 1;
                }
            }
            else {
                if(pau->m_bSeekable == WMAB_TRUE && pau->m_bOutputRawPCM != WMAB_TRUE) {
                    assert(MLLM_FILTER_SCALING > 0);
        //            pau->m_iACFilterOrder = 1;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, MLLM_FILTER_SCALING, &iResult));
                    if ((iResult >= (1 << MLLM_FILTER_SCALING)) || ((I16)iResult < 0)) {
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    } else {
                        pau->m_iACFilter[0] = (I16)iResult;
                    }
                }
            }
#endif // BUILD_WMAPRO
            paudec->m_hdrdecsts = HDR_V3_LPC_UNIFIED_SCALING;

        case HDR_V3_LPC_UNIFIED_SCALING:
#if defined (BUILD_WMAPRO)
            if (pau->m_bV3RTM == WMAB_TRUE && pau->m_bDoLPC == WMAB_TRUE) {
                assert((1 << LLMB_INTEGERIZATION_SCALING_BITS) > (LLMB_INTEGERIZATION_SCALING_MAX - LLMB_INTEGERIZATION_SCALING_MIN));  
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_INTEGERIZATION_SCALING_BITS, &iResult));               
                //assert(pau->m_iACFilterScaling <= LLMB_INTEGERIZATION_SCALING_MAX);
                if ((((I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN) > LLMB_INTEGERIZATION_SCALING_MAX) ||
                    (((I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN) < LLMB_INTEGERIZATION_SCALING_MIN)) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                } else {
                    pau->m_iLPCFilterScaling = (I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN;
                }
                //assert(pau->m_iACFilterScaling >= LLMB_INTEGERIZATION_SCALING_MIN);
            }
#endif // BUILD_WMAPRO
            paudec->m_hdrdecsts = HDR_V3_LPC_UNIFIED_INTBITS;

        case HDR_V3_LPC_UNIFIED_INTBITS:
#if defined (BUILD_WMAPRO)
            if (pau->m_bV3RTM == WMAB_TRUE && pau->m_bDoLPC == WMAB_TRUE) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, BITS_LPC_INTBITS_UNIFIED, &iResult));               
                if ((((I16)iResult + MIN_LPC_INTBITS_UNIFIED) < MIN_LPC_INTBITS_UNIFIED) ||
                    (((I16)iResult + MIN_LPC_INTBITS_UNIFIED) > MAX_LPC_INTBITS_UNIFIED)) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                } else {
                    pau->m_iLPCFilterIntBits = (I16)iResult + MIN_LPC_INTBITS_UNIFIED;
                }
            }
#endif // BUILD_WMAPRO
            paudec->m_hdrdecsts = HDR_MLLM_QUANT_STEPSIZE;
//            break;

        case HDR_MLLM_QUANT_STEPSIZE:
#if defined (BUILD_WMAPRO)
            if (pau->m_bOutputRawPCM != WMAB_TRUE && pau->m_bSeekable == WMAB_TRUE) {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, MLLM_QUANTSTEPSIZE_BITS, &iResult));
                pau->m_iMLLMResidueQStepSize = (I16)iResult + 1;
            }
#endif // BUILD_WMAPRO
            // MLLMUsePLLM doesn't need mask.
            // Mixed lossless must decode mask if it is in the bitstream.
            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
                paudec->m_hdrdecsts = HDR_INTERCH_DECORR;
            }
            else {
                paudec->m_hdrdecsts = HDR_MSKUPD;
            }
            break;

        case HDR_INTERCH_DECORR:

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && 
                pau->m_bSeekable == WMAB_TRUE &&
                pau->m_bOutputRawPCM != WMAB_TRUE &&
                pau->m_bFirstUnifiedPureLLMFrm != WMAB_TRUE &&
                pau->m_bLastUnifiedPureLLMFrm != WMAB_TRUE ) 
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));  
                // not enabled in MLLMUsePLLM.
                if (iResult == WMAB_TRUE) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                } else {
                    pau->m_bDoInterChDecorr = (Bool)iResult;
                }
                //assert(pau->m_bDoInterChDecorr == WMAB_FALSE);
            }

#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            paudec->m_hdrdecsts = HDR_INTERCH_DECORR_MCLMS;

        case HDR_INTERCH_DECORR_MCLMS:

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && 
                pau->m_bSeekable == WMAB_TRUE &&
                pau->m_bOutputRawPCM != WMAB_TRUE &&
                pau->m_bFirstUnifiedPureLLMFrm != WMAB_TRUE &&
                pau->m_bLastUnifiedPureLLMFrm != WMAB_TRUE ) 
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));  
                // not enabled in MLLMUsePLLM
                if (iResult == WMAB_TRUE) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                } else {
                    pau->m_bDoMCLMS = (Bool)iResult;
                }
                //assert(pau->m_bDoMCLMS == WMAB_FALSE);
            }   
#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            paudec->m_hdrdecsts = HDR_CDLMS_SEND;

        case HDR_CDLMS_SEND:

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && 
                pau->m_bSeekable == WMAB_TRUE &&
                pau->m_bOutputRawPCM != WMAB_TRUE &&
                pau->m_bFirstUnifiedPureLLMFrm != WMAB_TRUE &&
                pau->m_bLastUnifiedPureLLMFrm != WMAB_TRUE ) 
            {
                assert(pau->m_cChInTile == pau->m_cChannel);
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult)); 
                if (iResult == WMAB_TRUE) {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                } else {
                    pau->m_bSendCDLMS = (Bool)iResult;
                }
                //assert(pau->m_bSendCDLMS == WMAB_FALSE);
            }
#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            paudec->m_iChannel = 0;
            paudec->m_hdrdecsts = HDR_FILTERS_PARA;
            paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_AMOUNT;

        case HDR_FILTERS_PARA:
            if (pau->m_cChInTile != pau->m_cChannel)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && 
                pau->m_bSeekable == WMAB_TRUE &&
                pau->m_bOutputRawPCM != WMAB_TRUE &&
                pau->m_bFirstUnifiedPureLLMFrm != WMAB_TRUE &&
                pau->m_bLastUnifiedPureLLMFrm != WMAB_TRUE ) 
            {
                for (; paudec->m_iChannel < pau->m_cChannel; paudec->m_iChannel++) {                       
    //                I16 iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                    PerChannelInfo* ppcInfoComm = pau->m_rgpcinfo + paudec->m_iChannel;
                    switch(paudec->m_hdrdecFilterParasts)
                    {
                        case HDRFLT_CLMS_AMOUNT:
                            assert((1 << LLMB_CLMSFLT_TTL_BITS) >= (LLMB_CLMSFLT_TTL_MAX - LLMB_CLMSFLT_TTL_MIN + 1));
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_CLMSFLT_TTL_BITS, (U32 *)&iResult));
                            if ((((I16)(iResult + LLMB_CLMSFLT_TTL_MIN)) > LLMB_CLMSFLT_TTL_MAX) ||
                                (((I16)(iResult + LLMB_CLMSFLT_TTL_MIN)) < LLMB_CLMSFLT_TTL_MIN)) {
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                            } else {
                                ppcInfoComm->m_cLMSPredictors = (I16)(iResult + LLMB_CLMSFLT_TTL_MIN);
                            }
                            ppcInfoComm->m_iLMSPredictorCurr = 0;
                            paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_ORDERS;

                        case HDRFLT_CLMS_ORDERS:
                            assert((1<< LLMB_CLMSFLT_ORDER_BITS) * LLMB_CLMSFLT_MIN_ORDER >= LLMB_CLMSFLT_MAX_ORDER);
                            
			    for (/*ppcInfoComm->m_iLMSPredictorCurr*/;
					    ppcInfoComm->m_iLMSPredictorCurr < ppcInfoComm->m_cLMSPredictors;
					    ppcInfoComm->m_iLMSPredictorCurr++)
			    {
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_CLMSFLT_ORDER_BITS, (U32 *)&iResult));
                                if ((((iResult + 1) * LLMB_CLMSFLT_MIN_ORDER) > LLMB_CLMSFLT_MAX_ORDER) ||
                                    (((iResult + 1) * LLMB_CLMSFLT_MIN_ORDER) < LLMB_CLMSFLT_MIN_ORDER)) {
                                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                                } else {
                                    ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iOrder = (iResult + 1) * LLMB_CLMSFLT_MIN_ORDER;
                                }
                            }
                            ppcInfoComm->m_iLMSPredictorCurr = 0;
                            paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_SCALINGS;

                        case HDRFLT_CLMS_SCALINGS:
                            assert((1 << LLMB_INTEGERIZATION_SCALING_BITS) > (LLMB_INTEGERIZATION_SCALING_MAX - LLMB_INTEGERIZATION_SCALING_MIN));  
                            for (/*ppcInfoComm->m_iLMSPredictorCurr*/; ppcInfoComm->m_iLMSPredictorCurr < ppcInfoComm->m_cLMSPredictors; ppcInfoComm->m_iLMSPredictorCurr++) {
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, LLMB_INTEGERIZATION_SCALING_BITS, (U32 *)&iResult));
                                if ((((I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN) > LLMB_INTEGERIZATION_SCALING_MAX) ||
                                    (((I16)iResult + LLMB_INTEGERIZATION_SCALING_MIN) < LLMB_INTEGERIZATION_SCALING_MIN)) {
                                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                                } else {
                                    ppcInfoComm->m_rgLMSPredictors[ppcInfoComm->m_iLMSPredictorCurr].m_iScaling = iResult + LLMB_INTEGERIZATION_SCALING_MIN;
                                }
                            }
                            ppcInfoComm->m_iLMSPredictorCurr = 0;
                            paudec->m_hdrdecFilterParasts = HDRFLT_CLMS_AMOUNT;
                    }
                }            
/*
                //reset all
                if (pau->m_bSeekable == WMAB_TRUE && pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
                    ASSERTWMA_EXIT(wmaResult, prvLLMVerBResetAll_MLLM(pau, pau->m_rgpcinfo, WMAB_FALSE));
                }
*/
                // we have got valid LMS filters so far.
                paudec->m_bGotValidFilterInfo = WMAB_TRUE;
            }

#endif //defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)

            paudec->m_hdrdecsts = HDR_DONE;
            break;

        case HDR_V2_POWER:
            assert(pau->m_cChannel <= 2);
            TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, pau->m_cChannel + 1));
            if (pau->m_cChannel == 1)    {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                pau->m_rgpcinfo [0].m_iPower = iResult;
                
                fSkipAll = (pau->m_rgpcinfo [0].m_iPower == 0);
                
                pau->m_rgpcinfo->m_stereoMode = STEREO_LEFTRIGHT;
                // Help WM Compression Tool
                pau->m_stereoMode = STEREO_LEFTRIGHT;
            }
            else {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                
                pau->m_rgpcinfo->m_stereoMode = (StereoMode) iResult;
                (pau->m_rgpcinfo + 1)->m_stereoMode = (StereoMode) iResult;

                // Help WM Compression Tool
                pau->m_stereoMode = (StereoMode) iResult;
                
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                pau->m_rgpcinfo [0].m_iPower = iResult;
                
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                pau->m_rgpcinfo [1].m_iPower = iResult;
                
                fSkipAll = (pau->m_rgpcinfo [0].m_iPower == 0) & (pau->m_rgpcinfo [1].m_iPower == 0);
                if (pau->m_rgpcinfo->m_stereoMode == STEREO_SUMDIFF)
                    prvSetDecTable  (paudec,  pau->m_rgpcinfo + 1, 1);
                else 
                    prvSetDecTable  (paudec,  pau->m_rgpcinfo + 1, 0);
            }
            // shift it back by the minimum for decode or in case of exit
            // V3 does not come here
            pau->m_iQuantStepSize = MIN_QUANT;
            
            if (fSkipAll) {
#               if defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
                    // no bits will be read
                    if (pau->m_iWeightingMode == LPC_MODE) 
                    {
                        // Make sure there is a rightly defined process for dither decoding
                        // Since no bits are read, we do not need additional states for this
                        for (paudec->m_iChannel = 0; 
                            paudec->m_iChannel < pau->m_cChInTile; 
                            paudec->m_iChannel++)   
                        {
                            iChSrc =  pau->m_rgiChInTile [paudec->m_iChannel];
                            ppcinfo = pau->m_rgpcinfo + iChSrc;

                            if (ppcinfo->m_iCurrSubFrame > 0)
                            {
                                // Anchor mask is most likely already available: resample it
                                ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] = WMAB_FALSE;
                            }
                            else
                            {
                                // Anchor mask is not available: reset the mask
                                ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] = WMAB_TRUE;
                            }
                        }
                        // Set correct channel# for prvDecodeSubFrameHeaderLpc to work.
                        paudec->m_iChannel = 0;
                        TRACEWMA_EXIT(wmaResult, prvDecodeSubFrameHeaderLpc(paudec));
                    }
#               endif  // defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
                paudec->m_hdrdecsts = HDR_DONE;
                goto exit;
            }
            paudec->m_hdrdecsts = HDR_QUANT;
            break;

        case HDR_V3_VECCODER_POSEXIST:
            pau->m_fExpVecsInNonRLMode = WMAB_FALSE;
            if (pau->m_iVersion >= 3)
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(&paudec->m_ibstrm, 1, &iResult));
                if (iResult != 0) pau->m_fExpVecsInNonRLMode = WMAB_TRUE;
            }
            *piChannel = 0;
            paudec->m_hdrdecsts = HDR_V3_VECCODER_POS;

        case HDR_V3_VECCODER_POS:
            if (pau->m_fExpVecsInNonRLMode == WMAB_TRUE) {
                Int nBits;
                for (; *piChannel < pau->m_cChInTile; (*piChannel)++) {
                    iChSrc = pau->m_rgiChInTile [*piChannel];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    nBits = (Int)LOG2((ppcinfo->m_cSubbandActual+3)>>2) + 1;
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, nBits, &iResult));
                    ppcinfo->m_iVecsInNonRLMode = iResult;
                }
            }
            paudec->m_hdrdecsts = HDR_QUANT;

        case HDR_QUANT:
            if (pau->m_iVersion <= 2)
            {
                TRACEWMA_EXIT(wmaResult, prvDecodeQuantStepV2(paudec));
            }
            else
            {
                TRACEWMA_EXIT(wmaResult, prvDecodeQuantStepV3(paudec));
            }
            auUpdateMaxEsc(pau, pau->m_iQuantStepSize);
            *piChannel  = -1;
            // Some sensible initialization for quant modifiers (needed in V3 and up)
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
            {
                iChSrc = pau->m_rgiChInTile [iCh];
                ppcinfo = pau->m_rgpcinfo + iChSrc;
                ppcinfo->m_ucQuantStepModifierIndex = 0;
                ppcinfo->m_qstQuantStepModifier = qstCalcQuantStep(0, 0);
            }
            paudec->m_cBitQuantStepModifierIndex = 0;
            paudec->m_hdrdecsts = HDR_V3_QUANT_MODIFIER;

        case HDR_V3_QUANT_MODIFIER:
            TRACEWMA_EXIT(wmaResult, prvDecodeQuantStepModifiers(paudec));

#ifdef ENABLE_ALL_ENCOPT
            paudec->m_iBand     = (I16) pau->m_iFirstNoiseBand;;
#endif // ENABLE_ALL_ENCOPT
            *piChannel  = 0;
            paudec->m_hdrdecsts = HDR_NOISE1;

        case HDR_NOISE1 : // Fall into
        case HDR_NOISE2 : // Fall into
#           ifdef ENABLE_ALL_ENCOPT
            if (pau->m_fNoiseSub == WMAB_TRUE)
            {
                TRACEWMA_EXIT(wmaResult, prvDecodeSubFrameHeaderNoiseSub(paudec));
            }
#           endif //ENABLE_ALL_ENCOPT
            paudec->m_hdrdecsts = HDR_MSKUPD;
        case HDR_MSKUPD :
            if (pau->m_iVersion <= 2)  //v3 is done as part of mask
            {
                fUpdateMask = WMAB_TRUE;
                TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(&paudec->m_ibstrm, 1));
                if (pau->m_fAllowSubFrame && pau->m_rgpcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame > 1) 
                {
                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, &iResult));
                    fUpdateMask = iResult;
                    // First subframe must have fUpdateMask. Otherwise it will cause 
                    // problem in prvGetBandWeightMidRate (v2, 16000hz) if there is bit-stream corruption. 
                    // (assert( iMaskBand == iRsmpBand || (iMaskBand+1) == iRsmpBand )
                    // because the ratio is 4.)
                    if ((pau->m_rgpcinfo->m_iCurrSubFrame == 0) && (fUpdateMask != 1)) 
                    {   
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                    }
                }
            }

            //Setup the pointer to the quantized coefficents. This must be done after 
            //prvDecodeFrameHeaderNoiseSub since it changes the value of m_cSubbandActual
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
            {
                iChSrc = pau->m_rgiChInTile [iCh];
                ppcinfo = pau->m_rgpcinfo + iChSrc;
                ppcinfoDEC = paudec->m_rgpcinfoDEC + iChSrc;
/*
                ppcinfo->m_rgiCoefQ       = ((I32*) (pau->m_rgiCoefReconOrig 
                                          + DOUBLE(pau->m_fPad2XTransform, (iChSrc + 1) * pau->m_cFrameSampleHalf)))  
                                          - DOUBLE(pau->m_fPad2XTransform, ppcinfo->m_cSubbandActual);
*/
                // Offset with ppcinfo->m_cSubFrameSampleHalf- ppcinfo->m_cSubbandActual is necessary
                // for noise-sub: entropy decoded symbols must be expanded to fit full subframe. To avoid
                // overwriting shared rgiCoefQ and rgfltCoefRecon (aka rgiCoefRecon): Naveen
                ppcinfo->m_rgiCoefQ = (I32 *)(ppcinfo->m_rgiCoefRecon + 
                    AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,pau->m_fPad2XTransform, ppcinfo->m_cSubFrameSampleHalf)) - 
                    AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,pau->m_fPad2XTransform, ppcinfo->m_cSubbandActual);

                if (!ppcinfo->m_bNoDecodeForCx)
                    memset (ppcinfo->m_rgiCoefQ, 0,
                            sizeof (I32) *
                            AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,
                                              pau->m_fPad2XTransform,
                                              ppcinfo->m_cSubbandActual));

                // V3 and up: One bit per channel mask presence information
                ppcinfoDEC->m_fMaskHeaderDone = WMAB_FALSE;
                ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] = (U8) fUpdateMask;
            }            
            
            *piChannel = 0;
            paudec->m_iBand = 0;
            paudec->m_hdrdecsts = HDR_BARK;
            
        case HDR_BARK :
            if (pau->m_iWeightingMode == BARK_MODE) 
            {
                for (; *piChannel < pau->m_cChInTile; (*piChannel)++)
                {
                    iChSrc = pau->m_rgiChInTile [*piChannel];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    ppcinfoDEC = paudec->m_rgpcinfoDEC + iChSrc;
                    if (pau->m_iVersion > 2 && ppcinfoDEC->m_fMaskHeaderDone == WMAB_FALSE)
                        TRACEWMA_EXIT(wmaResult, prvDecodeMaskHeaderV3_Channel(paudec, iChSrc));

                    fUpdateMask = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0];

                    if (ppcinfo->m_iPower != 0 || pau->m_iVersion > 2) 
                    {
                        Int* rgiMaskQ = ppcinfo->m_rgiMaskQ;
                        const U16 *pDecodeTable = (pau->m_iVersion <= 2) ? g_rgiHuffDecTblMsk : g_rgunHuffDecTblMaskVLCV3;

                        if (fUpdateMask == WMAB_TRUE)    
                        {
                            if (pau->m_iVersion > 2 && ppcinfo->m_fAnchorMaskAvailable == WMAB_TRUE) {
                                // Perform run-level decoding
                                TRACEWMA_EXIT(wmaResult, prvDecodeMaskRunLevel  (paudec, 
                                    ppcinfo,
                                    pau->m_cValidBarkBand));
                            } 
                            else {
                                    // Perform simple VLC decoding.
                                if (pau->m_iVersion == 1) {
                                    TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm,
                                        NBITS_FIRST_MASKQUANT, &iResult));
                                    rgiMaskQ [0] = iResult + MIN_MASKQ_IN_DB_V1;
                                    paudec->m_iBand++;
                                }
                                
                                for (; paudec->m_iBand < pau->m_cValidBarkBand; paudec->m_iBand++)  
                                {
                                    Int iDiff;                        
                                    TRACEWMA_EXIT(wmaResult, huffDecGet (pDecodeTable,
                                        &paudec->m_ibstrm, &iResult, (unsigned long *)&iDiff, (unsigned long *)0));

                                    TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(&paudec->m_ibstrm, iResult));   //flush bits used by huffDecGet
                                    iDiff -= MAX_MASKQUANT_DIFF;
                                    assert (iDiff >= -MAX_MASKQUANT_DIFF);
                                    assert (pau->m_iVersion <= 2 || ppcinfo->m_fAnchorMaskAvailable == WMAB_FALSE);
                                    
                                    if (pau->m_iVersion > 2 && paudec->m_iBand == 0)
                                        iMaskQPrev = (Int)(FIRST_V3_MASKQUANT / ppcinfo->m_iMaskQuantMultiplier);
                                    else 
                                        iMaskQPrev = (paudec->m_iBand == 0) ? FIRST_V2_MASKQUANT : rgiMaskQ [paudec->m_iBand - 1];
                                    
                                    rgiMaskQ [paudec->m_iBand] = iDiff + iMaskQPrev;
                                    MONITOR_RANGE(gMR_rgiMaskQ, rgiMaskQ[paudec->m_iBand]);
                                }
                            }
                            pau->m_iSubFrameSizeWithUpdate = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame];
                            paudec->m_iBand = 0;
                        }
                        
                        //for IntFloat this gets done inside ReconWeightFactor()
                        //Scan For Max Weight
                        if (fUpdateMask)
                        {
                            Int iMax = rgiMaskQ[0];
                            I16 iBand;
                            for (iBand = 1; iBand < pau->m_cValidBarkBand; iBand++)
                            {
                                if (rgiMaskQ[iBand] > iMax)
                                    iMax = rgiMaskQ[iBand];
                            }
                            ppcinfo->m_iMaxMaskQ = iMax;
                            // Now we have an mask anchor for this channel for temporal delta
                            // decoding in future subframes.
                            ppcinfo->m_fAnchorMaskAvailable = WMAB_TRUE;
                        } 
                    }
                    else if (fUpdateMask == WMAB_TRUE)    
                    {   //else artifically set to constants since nothing got sent; see comments in msaudioenc.c
                        //0 db = 1.0 for weightfactor
                        memset( ppcinfo->m_rgiMaskQ, 0, pau->m_cValidBarkBand*sizeof(Int) );
                        ppcinfo->m_iMaxMaskQ = 0;
                    }
                    if (pau->m_iVersion > 2) 
                    {
                        if (fUpdateMask == WMAB_TRUE) 
                        {
                            // Now that the mask has Make a note of when the mask got updated for this channel
                            ppcinfo->m_cSubFrameSampleHalfWithUpdate = ppcinfo->m_cSubband;
                            ppcinfo->m_cValidBarkBandLatestUpdate = pau->m_cValidBarkBand;
                        }
                    }
                }
            }
#if defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
            else 
            {
                TRACEWMA_EXIT(wmaResult, prvDecodeSubFrameHeaderLpc(paudec));
                if (pau->m_fNoiseSub == WMAB_TRUE)  
                    prvGetBandWeightLowRate (paudec);
            }
#else   // defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
            else {
                assert(WMAB_FALSE);
            }
#endif  // defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
            paudec->m_hdrdecsts = HDR_DONE;
            break;
        }
    }
    
exit:
    
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    //WMAPrintf("Sh%d %d %d\n", pau->m_iFrameNumber, pau->m_rgpcinfo->m_iCurrSubFrame, paudec->m_ibstrm.m_cFrmBitCnt - cBitOrig);
    //FFLUSH(stdout);
    
    return wmaResult;
} // prvDecodeSubFrameHeader


//******************************************************************************
//
//     Stub functions
//
//******************************************************************************

#if !defined (BUILD_WMAPRO) && !defined (BUILD_WMALSL)
// i.e purely BUILD_WMASTD
I32 prvDecodeTileHdr(CAudioObjectDecoder* paudec, 
                     ConfigFrame iFrame)
{
    return 0;
}
Void prvInitDecodeTileHdr(CAudioObjectDecoder *paudec, 
                          ConfigFrame iFrame)
{
}
WMARESULT prvDecodeTrailerBit (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
#endif // !BUILD_WMAPRO && !BUILD_WMALSL


#if !defined (BUILD_WMAPRO)
// WMAPRO Stub functions. Actual implementations are needed only for WMAPRO,
// and are provided in entropydecpro.c
WMARESULT prvEntropyDecodePostProcXform (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
WMARESULT prvDecodeMaskRunLevel  (CAudioObjectDecoder* paudec, 
                                  PerChannelInfo* ppcinfo,
                                  Int iBandLim)
{
    return WMA_OK;
}
WMARESULT prvDecodeMaskHeaderV3_Channel (CAudioObjectDecoder* paudec, 
                                         Int iCh)
{
    return WMA_OK;
}
WMARESULT prvDecodeQuantStepModifiers (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
WMARESULT prvDecodeQuantStepV3 (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
WMARESULT prvEscapeDecodeRunV3(Int *pcRunOfZeros, Int cMaxRun,
                               CWMAInputBitStream *pibstrm)
{
    return WMA_OK;
}
WMARESULT prvEntropyDecodeChannelXform (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
WMARESULT prvGetNextRunDECVecTableIndex(Void*           pobjin, 
                                        PerChannelInfo* ppcinfo)
{
    return WMA_OK;
}
Void prvResetVecCoder(CAudioObjectDecoder *paudec)
{
}
#endif // !BUILD_WMAPRO

#if !defined (BUILD_WMASTD)
// WMASTD Stub functions. Actual implementations are needed only for WMASTD,
// and are provided in entropydecstd.c
WMARESULT prvDecodeQuantStepV2 (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
WMARESULT prvDecodeSubFrameHeaderLpc (CAudioObjectDecoder* paudec) 
{
    return WMA_OK;
}
Void    prvSetDecTable  (CAudioObjectDecoder* paudec,  PerChannelInfo* ppcinfo, I16 iSet)
{
}
WMARESULT prvDecodeCoefficientMono  (CAudioObjectDecoder* paudec, 
                                     PerChannelInfo* ppcinfo)
{
    return WMA_OK;
}
WMARESULT prvDecodeCoefficientStereo (CAudioObjectDecoder* paudec, 
                                    PerChannelInfo* ppcinfo)
{
    return WMA_OK;
}
WMARESULT prvGetNextRunDEC(Void*             pobjin, 
                           PerChannelInfo* ppcinfo)
{
    return WMA_OK;
}
#ifdef ENABLE_ALL_ENCOPT
WMARESULT prvDecodeSubFrameHeaderNoiseSub (CAudioObjectDecoder* paudec)
{
    return WMA_OK;
}
Void prvGetBandWeightLowRate (CAudioObjectDecoder* paudec)
{
}
#endif // ENABLE_ALL_ENCOPT
#endif // !BUILD_WMASTD


