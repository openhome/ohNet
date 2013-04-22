//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*
 * Windows Media Audio (WMA) Decoder API (implementation)
 *
 * Copyright (c) Microsoft Corporation 1999.  All Rights Reserved.
 */

#ifndef USE_SPDTX

#include "wmaudio_inc.h"
#include "macros.h"

#if (  defined(WIN32) || defined(_WIN32_WINCE) ) && ( !defined(_XBOX) || defined(_DEBUG) )
#define ISBADPTR
#endif

/* ===========================================================================
 * WMAFileDecodeData
--------------------------------------------------------------------------- */

#ifdef PERFRM_TIMING
#pragma warning ( disable : 4035 )
__forceinline I64 HrTmrGet (void) {
   __asm rdtsc;
}
int g_cCurFrmSamples;
I64 g_iCurFrmTm;
int g_cFrm = 0;
extern FILE* g_fpPerfrmLog;
#endif

tWMAFileStatus WMAFileDecodeData(tHWMAFileState hstate, tWMA_U32 *pnDecodedSamples)
{
    tWMAFileStateInternal *pInt;
    WMARESULT wmar = WMA_OK;
    tWMAFileStatus rc;
    FUNCTION_PROFILE(fp);

    pInt = (tWMAFileStateInternal*) hstate;

 //   WMADebugMessage("WMAFileDecodeData parse_state %d, audecState %d\n", pInt->parse_state, pInt->audecState); 

    if(pInt == NULL || pInt->hWMA == NULL)
        return cWMA_BadArgument;

    //wchen: need to initialize
    if (pnDecodedSamples != NULL)
        *pnDecodedSamples = 0;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
    if (IsBadWritePtr(pnDecodedSamples, sizeof(tWMA_U32)))
        return cWMA_BadArgument;
#endif

    FUNCTION_PROFILE_START(&fp,WMA_FILE_DECODE_DATA_PROFILE);

    do
    {
        switch(pInt->parse_state)
        {
        case csWMA_DecodeAudioData:
#ifdef WMAAPI_DEMO
            if(pInt->nSampleCount >= WMAAPI_DEMO_LIMIT*pInt->hdr_parse.nSamplesPerSec)
            {
                FUNCTION_PROFILE_STOP(&fp);
                return cWMA_DemoExpired;
            }
#endif /* WMAAPI_DEMO */
            switch(pInt->audecState) {
            case audecStateInput: {
                WMAFileGetInputParam tmp;
                U8* pbIn = NULL;
                U32 cbIn = 0;
                Bool fNoMoreInput = 0, fNewPacket = 0;
                
                memset(&tmp, 0, sizeof(WMAFileGetInputParam));
                wmar = WMAFileGetInput(pInt, &pbIn, &cbIn, &tmp);

                if (wmar == WMA_E_NO_MORE_SRCDATA) {
                  fNoMoreInput = 1;
                } else if (WMA_FAILED(wmar)) {
                  pInt->parse_state = csWMA_DecodePayloadEnd;
                  return wmar;
                }
                
                if (wmar == WMA_S_NEWPACKET) 
                {
                    fNewPacket = 1;
#ifdef WMA_COMPRESSION_TOOL
                    ((CAudioObjectDecoder *)(pInt->hWMA))->pau->m_cPktsInSeg++;
#endif //WMA_COMPRESSION_TOOL
                }
                wmar = audecInput(pInt->hWMA, pbIn, cbIn, fNewPacket, fNoMoreInput,
                                              tmp.m_fTimeIsValid, tmp.m_iTime, &pInt->audecState, NULL);
                if (WMA_FAILED(wmar)) {
                  pInt->parse_state = csWMA_DecodePayloadEnd;
                  return cWMA_Failed;
                }

#if defined (WMA_SEEK_TEST)
                if (wmar == WMA_S_LOSTPACKET) {
                    fprintf(stdout, "\r**WMAFileDecodeData: WMADecodeData: Lost packet\n");
                    fflush(stdout);
                }
#endif // WMA_SEEK_TEST

                break;
            }
            case audecStateDecode: {
#ifdef PERFRM_TIMING
                I64 tmp = HrTmrGet();
#endif
                wmar = audecDecode(pInt->hWMA, pnDecodedSamples, &pInt->audecState, NULL);
#ifdef PERFRM_TIMING
                tmp = HrTmrGet() - tmp;
                if (audecStateGetPCM == pInt->audecState)
                    g_cCurFrmSamples = *pnDecodedSamples;
                g_iCurFrmTm += tmp;
#endif
                if (WMA_FAILED(wmar)) {
                  pInt->parse_state = csWMA_DecodePayloadEnd;
                  return cWMA_Failed;
                }

                break;
            }
            case audecStateGetPCM:
                assert(!"WMAFileDecodeData called when WMAFileGetPCM should have been called");
                wmar = WMA_OK;
                break;
            case audecStateDone:
                wmar = cWMA_NoMoreFrames;
                break;
            default:
                assert(!"bad audecState");
            }
                    
            if (wmar == WMA_S_NO_MORE_SRCDATA) {
#ifdef LOCAL_DEBUG
                SerialSendString("\r** WMAFileDecodeData: WMADecodeData: no more data\n");
#endif /* LOCAL_DEBUG */
                return cWMA_NoMoreFrames;
            }
            if (pInt->audecState == audecStateDone)
                return cWMA_NoMoreFrames;
            else
                return cWMA_NoErr;

        default:
            /* All other state operation is done in this function
             *   so that it can be done somewhere else as well
             */

            {
                rc = WMAF_UpdateNewPayload(pInt);
                if(rc != cWMA_NoErr)
                {
#ifdef LOCAL_DEBUG
                    SerialSendString("\r** WMAFileDecodeData: WMA_UpdateNewPlayload failed\n");
#endif /* LOCAL_DEBUG */
                    FUNCTION_PROFILE_STOP(&fp);
                    return rc;
                }
            }
            break;
        }
#ifdef WMA_COMPRESSION_TOOL
        // in peek mode we must return to upper caller.
        if (((CAudioObjectDecoder*)(pInt->hWMA))->pau->m_bSegDecodePeekMode == WMAB_TRUE) 
        {
            break;
        }
#endif //WMA_COMPRESSION_TOOL

    } while(1);

    FUNCTION_PROFILE_STOP(&fp);
    return cWMA_NoErr;
} // WMAFileDecodeData

/* ===========================================================================
 * WMAFileGetPCM
--------------------------------------------------------------------------- */
tWMA_U32 WMAFileGetPCM (
    tHWMAFileState hstate,
    tWMA_I16 *pi16Channel0, tWMA_I16 *pi16Channel1,
    tWMA_U32 iSizeOfChannel0,
    tWMA_U32 max_nsamples,
    tWMA_I64* piTimeStamp)
{
    tWMAFileStateInternal *pInt; 
    WMARESULT wmar = WMA_OK;
    WMA_U32 cSamples = 0;
    FUNCTION_PROFILE(fp);

    pInt = (tWMAFileStateInternal*) hstate;

    if (pInt == NULL || pInt->hWMA == NULL || pi16Channel0 == NULL || piTimeStamp == NULL)
        return 0;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
    if (IsBadWritePtr(pi16Channel0, iSizeOfChannel0))
        return cWMA_BadArgument;
    if (IsBadWritePtr(piTimeStamp, sizeof(tWMA_I64)))
        return cWMA_BadArgument;
#endif

    if (pInt->audecState != audecStateGetPCM)
        return 0;

    FUNCTION_PROFILE_START (&fp,WMA_FILE_GET_PCM_PROFILE);

#ifdef PERFRM_TIMING
    I64 tmp = HrTmrGet();
#endif

    if (pi16Channel1 == NULL ||
        pi16Channel1 == pi16Channel0 + 1 ||
        pInt->hdr_parse.nChannels <= 1 ) 
    {
        // caller wants interleaved data or this sound is mono
        // Testing dynamic update of player information.
        // audecSetPlayerInfo(pInt->hWMA, &pInt->audecState, (WMAPlayerInfo*)pInt->pPlayerInfo, 1, 1);

        wmar = audecGetPCM (pInt->hWMA, max_nsamples, &cSamples,
                            (WMA_U8*)pi16Channel0, iSizeOfChannel0,
                            NULL, piTimeStamp,&pInt->audecState, 
                            (WMAPlayerInfo *)pInt->pPlayerInfo, NULL);
    } 
    else 
    {
        // caller wants de-interleaved stereo data
        WMA_U16 i;
        tWMA_I16 *pi16C0src = pi16Channel0;
        tWMA_I16 *pi16C0dst = pi16Channel0;
        tWMA_I16 *pi16C1    = pi16Channel1;
        
//      assert (pInt->hdr_parse.nChannels == 2);  // if it is  greather than two, this needs work...
        // half the stereo samples in one buffer then they will get split into both

        wmar = audecGetPCM (pInt->hWMA, (U16)max_nsamples >> 1, &cSamples,
                            (WMA_U8*)pi16Channel0, iSizeOfChannel0,
                            NULL, piTimeStamp, &pInt->audecState, (WMAPlayerInfo *)pInt->pPlayerInfo, NULL);
        if (WMA_SUCCEEDED(wmar))
        {
            for (i = 0; i < cSamples; i++)
            {
                *pi16C0dst++ = *pi16C0src++;
                *pi16C1++ = *pi16C0src++;
            }
        }
    }

#ifdef PERFRM_TIMING
    tmp = HrTmrGet() - tmp;
    g_iCurFrmTm += tmp;
    
    if (audecStateGetPCM != pInt->audecState) 
    {
        if (g_fpPerfrmLog)
            fprintf(g_fpPerfrmLog, "%d %d %I64d\n", g_cFrm++, g_cCurFrmSamples, g_iCurFrmTm);
        else
            fprintf(stderr, "!!! LOG FILE ERROR !!!");
        g_cCurFrmSamples = 0;
        g_iCurFrmTm = 0;
    }
#endif
    
    WMAASSERT(WMA_SUCCEEDED(wmar)); // looks like auGetPCM can never fail
    if (WMA_FAILED(wmar))
    {
        pInt->parse_state = csWMA_DecodePayloadEnd;
        pInt->nSampleCount = cSamples = 0;
        pInt->audecState = audecStateInput;
        wmar = audecReset(pInt->hWMA);
        
        goto exit;
    }
    
    if (cSamples == 0) 
    {
        WMAASSERT(!"GetPCM returned 0.  This could cause an infinite loop.");
        pInt->audecState = audecStateDecode;
        pInt->nSampleCount = 0;

        goto exit;
    }
    
    
    pInt->nSampleCount = cSamples;
    
#ifdef USE_WOW_FILTER
    wowFilter(&(pInt->sWowChannel), pi16Channel0, pi16Channel1, samples_available);
#endif //USE_WOW_FILTER

exit:
    FUNCTION_PROFILE_STOP(&fp);
    return cSamples;
} // WMAFileGetPCM

#ifdef WMA_COMPRESSION_TOOL

tWMA_U32 WMAFileGetFrameBits ( tHWMAFileState hstate, 
                               tWMA_I32 *piPCMFrameNumber,
                               tWMA_U8  **ppbHdr0Bits,
                               tWMA_U32 *pnHdr0Bits,          
                               tWMA_U8  **ppbFrameBits, 
                               tWMA_U32 *pnFrameBits,
                               tWMA_U32 *pnHdr1Bits)
{
    tWMAFileStateInternal *pInt; 
    WMARESULT wmar = WMA_OK;
    WMA_U32 cSamples = 0;
    WMAFrameBitsInfo frmBitInf;

    FUNCTION_PROFILE(fp);

    pInt = (tWMAFileStateInternal*) hstate;
    wmar = audecGetFrameBits ( pInt->hWMA, 
                               piPCMFrameNumber, 
                               &frmBitInf,
                               ppbFrameBits);

    return (*pnFrameBits);
}

#endif //WMA_COMPRESSION_TOOL

#endif // !USE_SPDTX
