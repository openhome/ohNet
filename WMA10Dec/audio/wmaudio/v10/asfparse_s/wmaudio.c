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

#include "wmaudio_inc.h"

#define TRUE 1
#define FALSE 0

#ifdef WMDRM_NETWORK
#include "DrmAesEx.h"
#endif

#ifndef WMAAPI_NO_DRM
const BYTE APPSEC_1100[APPSEC_LEN] = {0x0, 0x0, 0x4, 0x4C};
#endif
//extern int iSubFrm;

#ifdef WMDRM_PORTABLE
static const DRM_WCHAR s_szLicense[] = L"c:\\wmdrmpd\\sample.hds";
static const DRM_CONST_STRING s_strLicense = CREATE_DRM_STRING( s_szLicense );
#endif

#if (  defined(WIN32) || defined(_WIN32_WINCE) ) && ( !defined(_XBOX) || defined(_DEBUG) )
#define ISBADPTR
C_ASSERT( sizeof(tWMAFileHdrState) == sizeof(tWMAFileHdrStateInternal) );
#endif


#if !defined(C_ASSERT)
#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#endif // C_ASSERT



//BYTE bGlobalDataBuffer[256];
#if 0
/****************************************************************************/
extern "C" size_t
strlen(const char *p)
{
    int cnt = 0;
    while(*p++)
    {
        cnt++;
    }
    return cnt;
}
#endif

/****************************************************************************/
/*
static tWMAFileStatus
TranslateCode(tWMAStatus rc)
{
    switch(rc)
    {
    case kWMA_NoErr:
        return cWMA_NoErr;
    case kWMA_BrokenFrame:
        return cWMA_BrokenFrame;
    case kWMA_NoMoreFrames:
        return cWMA_NoMoreFrames;
    case kWMA_BadSamplingRate:
        return cWMA_BadSamplingRate;
    case kWMA_BadNumberOfChannels:
        return cWMA_BadNumberOfChannels;
    case kWMA_BadVersionNumber:
        return cWMA_BadVersionNumber;
    case kWMA_BadWeightingMode:
        return cWMA_BadWeightingMode;
    case kWMA_BadPacketisation:
        return cWMA_BadPacketization;
    }

#ifdef LOCAL_DEBUG
    while(1);
#else
    return cWMA_Internal;
#endif
}
*/

WMA_I32 WMA_CompareWToC(WMA_U8 *pC, WMA_U16 *pW,  WMA_U16 len, WMA_U32 *pValues )
{

    WMA_U8 *pbTemp = NULL;
    WMA_U16 i =0, j=0;
    WMA_U8  fWildFound =0;

    for (i=0; i <len/2; i++)
    {
        pbTemp = (WMA_U8 *)pW;

        if (1 == fWildFound && (*pbTemp < '0' || *pbTemp > '9' ))
        {
            fWildFound =0;
            j++;
        }
        
        // Using % to skip the comparision of numbers and if pValues are not NULL, Get those values.
        if (*pC == '%')
        {
            fWildFound =1;
            if (NULL != pValues)
                pValues[j] = 0;
        }

        if (1 == fWildFound && NULL != pValues)
        {
            // Try to get this values
            pValues[j] = pValues[j] *10 + *pbTemp - '0';
        }



        if (0 == fWildFound && *pC != '?') // Using '?' for wildcard char
        {
            if (*pbTemp != *pC)
               return -1;
        }
        pW++;
        pC++;
    }
    return 0;
}

WMARESULT WMA_ParseFoldDown(WMA_U16 *pW,  WMA_U32 len, WMA_I32 *pValues, WMA_U16 wNumValIn )
{

    WMA_U8 *pbTemp = NULL;
    WMA_U16 i =0, j=0, digits =0;
    WMA_U8  fMakeNegative = 0;

    if (NULL == pValues)
        return WMAERR_FAIL;

    memset(pValues, 0, sizeof(WMA_I32)*wNumValIn);
    
    for (i=0; i <len/2; i++)
    {
        pbTemp = (WMA_U8 *)pW;

        if (*pbTemp == ',' )
        {
            if (1 == fMakeNegative)
            {
                pValues[j] = 0 - pValues[j];
                fMakeNegative =0;
            }
            
            if (j >= wNumValIn -1)
                return WMAERR_FAIL;
            j++;
            digits =0;

        }
        else if (*pbTemp == '-')
        {
            if (digits > 0)
                return WMAERR_FAIL;
            fMakeNegative = 1;

        }
        else if (*pbTemp >= '0' && *pbTemp <= '9' )
        {
             pValues[j] = pValues[j] *10 + *pbTemp - '0';
             digits++;
        }
        else if (*pbTemp == 0) // end
        {
            if (1 == fMakeNegative)
            {
                pValues[j] = 0 - pValues[j];
                fMakeNegative =0;
            }
        }
        else
            return WMAERR_FAIL;
        pW++;
    }

    if (j != wNumValIn -1)
        return WMAERR_FAIL;

    return WMA_OK;
}


/****************************************************************************/
tWMAFileStatus WMAF_UpdateNewPayload (tWMAFileStateInternal *pInt)
{
    /* internal call, so pInt should be okay */

    /* HongCho: separated out these parts from the parsing loop, because
     *          other parts (when a new payload is about to be retrieved)
     *          need to update the offsets and other states.
     *
     *          used in WMAFileDecodeData() and WMARawDecCBGetData ().
     */

    WMAERR wmarc;
#ifndef WMAAPI_NO_DRM
    tWMA_U32 cbRead =0;
    HRESULT hr;
    BYTE *pLast15 = NULL;
#endif
#ifndef WMAAPI_NO_DRM_STREAM
    tWMA_U32 cbLeftover =0;
    BYTE *pbDRMPayload = NULL;
    WORD wDRMOffset =0;
#endif

    do
    {
        switch (pInt->parse_state)
        {
        case csWMA_NewAsfPacket:

#ifdef WMAAPI_DEMO
            if (pInt->nSampleCount >= WMAAPI_DEMO_LIMIT*pInt->hdr_parse.nSamplesPerSec)
            {
                return cWMA_DemoExpired;
            }
#endif /* WMAAPI_DEMO */

            if (pInt->hdr_parse.nextPacketOffset > pInt->hdr_parse.cbLastPacketOffset)
            {
                return cWMA_NoMoreFrames;
            }

            pInt->hdr_parse.currPacketOffset = pInt->hdr_parse.nextPacketOffset;

            wmarc = WMA_ParsePacketHeader (pInt);

            if (pInt->ppex.cbExplicitPacketLength) {
                pInt->hdr_parse.nextPacketOffset += pInt->ppex.cbExplicitPacketLength; // + pInt->ppex.cbPadding;
            }
            else {
                pInt->hdr_parse.nextPacketOffset += pInt->hdr_parse.cbPacketSize;
            }

            if (wmarc == WMAERR_BUFFERTOOSMALL)
            {
                pInt->hdr_parse.nextPacketOffset = pInt->hdr_parse.currPacketOffset;
            //  pInt->hdr_parse.currPacketOffset -= pInt->hdr_parse.cbPacketSize;
                return cWMA_NoMoreDataThisTime;
            }


            if(wmarc != WMAERR_OK)
            {
                return cWMA_BadPacketHeader;
            }

            if (pInt->ppex.fEccPresent && pInt->ppex.fParityPacket)
            {
                /* HongCho: for some reason, ARM's code thinks a parity packet is
                 *          only at the end...  Here, I am not assuming that.
                 */
                break;
            }

            pInt->parse_state = csWMA_DecodePayloadStart;
            pInt->iPayload = 0;
            break;

        case csWMA_DecodePayloadStart:

            if (pInt->iPayload >= pInt->ppex.cPayloads)
            {
                pInt->parse_state = csWMA_NewAsfPacket;
                break;
            }

            wmarc = WMA_ParsePayloadHeader(pInt);
            if(wmarc != WMAERR_OK)
            {
                pInt->parse_state = csWMA_DecodePayloadEnd;
                break;
            }

            pInt->wPayStart = pInt->payload.cbPacketOffset + pInt->payload.cbTotalSize
                            - pInt->payload.cbPayloadSize;

#ifndef WMAAPI_NO_DRM_STREAM
            if( pInt->payload.bStreamId == pInt->hdr_parse.bDRMAuxStreamNum )
            {
                /* Read this payload's data (should be 7-15 bytes) */
                cbRead = WMAFileCBGetData(
                                    (tHWMAFileState *) pInt,
                                    pInt->hdr_parse.currPacketOffset + pInt->wPayStart,
                                    pInt->payload.cbPayloadSize,
                                    &pbDRMPayload );
                
                if (cbRead != pInt->payload.cbPayloadSize)
                    return (cWMA_NoMoreFrames);
#ifdef ISBADPTR
                if (IsBadReadPtr(pbDRMPayload, cbRead))
                    return cWMA_NoMoreFrames;
#endif


                if (cbRead > sizeof (pInt->rgbNextPayloadEnd))
                    cbRead = sizeof (pInt->rgbNextPayloadEnd);

                cbLeftover = sizeof (pInt->rgbNextPayloadEnd) - cbRead;

                /* Copy this payload's data into our internal state data */

                // Check if payload size id 8 bytes or 9 bytes. Amit on 09/10/2001

                memset( pInt->rgbNextPayloadEnd, 0, 15 );

                if (pInt->payload.cbPayloadSize == 9)
                {
                    pInt->cbNextPayloadEndValid = (BYTE) cbRead - 1;

                    memcpy( pInt->rgbNextPayloadEnd + 7, pbDRMPayload+1, cbRead-1 );
                }
                else if (pInt->payload.cbPayloadSize == 8)
                {
                    pInt->cbNextPayloadEndValid = (BYTE) cbRead ;
                    memcpy( pInt->rgbNextPayloadEnd + 7, pbDRMPayload, cbRead);
                }

                /* Move on to the next payload, which should be the corresponding audio data */
                pInt->parse_state = csWMA_DecodePayloadEnd;
                break;
            }
#endif  /* WMAAPI_NO_DRM_STREAM */

            if( pInt->payload.cbRepData != 1 )
            {
                pInt->parse_state = csWMA_DecodePayload;
                pInt->payload.bIsCompressedPayload =0; // Amit to take care of compressed payloads.
                break;
            }
            else if(pInt->payload.cbRepData == 1)    // Amit to take care of compressed payloads.
            {
                pInt->parse_state = csWMA_DecodeCompressedPayload;
                pInt->payload.bIsCompressedPayload =1;
                break;
            }
            /* a payload has to be a multiple of audio "packets" */

            if(pInt->payload.cbPayloadSize%pInt->hdr_parse.nBlockAlign != 0)
            {
                return cWMA_BrokenFrame;
            }
            pInt->parse_state = csWMA_DecodePayloadEnd;
            break;

        case csWMA_DecodePayload:
            if (pInt->payload.bStreamId !=pInt->hdr_parse.wAudioStreamId) // Added by Amit to skip Video Payload
            {
                 pInt->parse_state = csWMA_DecodePayloadEnd;
                break;
           
            }
            pInt->cbPayloadOffset = pInt->hdr_parse.currPacketOffset + pInt->wPayStart;
            pInt->bBlockStart     = TRUE;
            pInt->cbBlockLeft     = pInt->hdr_parse.nBlockAlign;
            assert( pInt->payload.cbPayloadSize >= pInt->cbBlockLeft );
            pInt->cbPayloadLeft   = pInt->payload.cbPayloadSize - pInt->cbBlockLeft;

            /* new payload, so take care of DRM */

#ifdef WMDRM_PORTABLE
            if( pInt->bHasDRM || pInt->bHasJanusDRM )
#else
            if(pInt->bHasDRM)
#endif
            {

#ifdef WMAAPI_NO_DRM

                return cWMA_DRMUnsupported;

#else  /* WMAAPI_NO_DRM */

#ifndef WMAAPI_NO_DRM_STREAM

                if( 0 != pInt->cbNextPayloadEndValid )
                {
                    /* We pre-cached the last bytes of this payload - no need to seek / read */
                    pLast15 = pInt->rgbNextPayloadEnd;

                    /* Move the bytes to the appropriate offset */
                    wDRMOffset = pInt->payload.cbPayloadSize % 8;

                    if( ( 0 != wDRMOffset ) && ( 8 == pInt->cbNextPayloadEndValid ) )
                    {
                        memmove( pLast15 + 7 - wDRMOffset, pLast15 + 7, 8 );
                        memset( pLast15 + 15 - wDRMOffset, 0, wDRMOffset );
                    }
                }
                else
                {

#endif  /* WMAAPI_NO_DRM_STREAM */

                    /* We need to seek & read the last data from the end of this payload */
                    cbRead = WMAFileCBGetData(
                                    (tHWMAFileState *)pInt,
                                    pInt->cbPayloadOffset + pInt->payload.cbPayloadSize - 15,
                                    15,
                                    &pLast15 );

                    if (cbRead != 15)
                        return (cWMA_NoMoreFrames);
#ifdef ISBADPTR
                if (IsBadReadPtr(pLast15, cbRead))
                    return cWMA_NoMoreFrames;
#endif


#ifndef WMAAPI_NO_DRM_STREAM
                }
#endif  /* WMAAPI_NO_DRM_STREAM */

                /* Initialize DRM so it can decrypt this payload properly */
#ifdef WMDRM_PORTABLE
                if( pInt->bHasJanusDRM )
                {
                    hr = DRM_MGR_InitDecrypt( pInt->pJanusDecryptContext,
                                              pLast15,
                                              pInt->payload.cbPayloadSize );
                }
                else
#endif // WMDRM_PORTABLE

                hr = CDrmPD_InitPacket(pInt->pDRM_state, pLast15, pInt->payload.cbPayloadSize);
                if(hr != S_OK)
                {
#ifdef LOCAL_DEBUG
                    SerialPrintf("++ WMA_UpdateNewPayload: CDrmPD_InitPacket failed (0x%08x).\n\r", hr);
#endif /* LOCAL_DEBUG */
                    return cWMA_DRMFailed;
                }

#ifndef WMAAPI_NO_DRM_STREAM
                pInt->cbNextPayloadEndValid = 0;
#endif  /* WMAAPI_NO_DRM_STREAM */

#endif /* WMAAPI_NO_DRM */

            }

            /* Done updating */
/*            if (pInt->bDecInWaitState == 1)
            {
                pInt->parse_state = csWMA_DecodeLoopStart;
                pInt->bDecInWaitState =0;
            
            }
            else */
            {
                pInt->parse_state = csWMA_DecodeAudioData;
            }
            return cWMA_NoErr;

        case csWMA_DecodePayloadEnd:
            pInt->iPayload++;
            pInt->parse_state = csWMA_DecodePayloadStart;
            break;

        case csWMA_DecodeCompressedPayload: // Added by Amit to take care of compressed payloads
            if (pInt->payload.bStreamId !=pInt->hdr_parse.wAudioStreamId) // Added by Amit to skip Video Payload
            {
                 pInt->parse_state = csWMA_DecodePayloadEnd;
                break;           
            }
            pInt->cbPayloadOffset = pInt->hdr_parse.currPacketOffset + pInt->wPayStart;
            pInt->bBlockStart     = TRUE;
            pInt->cbBlockLeft     = pInt->hdr_parse.nBlockAlign;
            pInt->payload.wBytesRead =0;
            pInt->payload.bSubPayloadState = 1;

/****************************************************************************************/    
            
            /* new payload, so take care of DRM */

#ifdef WMDRM_PORTABLE
            if( pInt->bHasDRM || pInt->bHasJanusDRM )
#else
            if(pInt->bHasDRM)
#endif
            {

#ifdef WMAAPI_NO_DRM

                return cWMA_DRMUnsupported;

#else  /* WMAAPI_NO_DRM */

#ifndef WMAAPI_NO_DRM_STREAM

                if( 0 != pInt->cbNextPayloadEndValid )
                {
                    /* We pre-cached the last bytes of this payload - no need to seek / read */
                    pLast15 = pInt->rgbNextPayloadEnd;

                    /* Move the bytes to the appropriate offset */
                    wDRMOffset = pInt->payload.cbPayloadSize % 8;

                    if( ( 0 != wDRMOffset ) && ( 8 == pInt->cbNextPayloadEndValid ) )
                    {
                        memmove( pLast15 + 7 - wDRMOffset, pLast15 + 7, 8 );
                        memset( pLast15 + 15 - wDRMOffset, 0, wDRMOffset );
                    }
                }
                else
                {

#endif  /* WMAAPI_NO_DRM_STREAM */

                    /* We need to seek & read the last data from the end of this payload */
                    cbRead = WMAFileCBGetData(
                                    (tHWMAFileState *)pInt,
                                    pInt->cbPayloadOffset + pInt->payload.cbPayloadSize - 15,
                                    15,
                                    &pLast15 );

                    if (cbRead != 15)
                        return (cWMA_NoMoreFrames);
#ifdef ISBADPTR
                if (IsBadReadPtr(pLast15, cbRead))
                    return cWMA_NoMoreFrames;
#endif


#ifndef WMAAPI_NO_DRM_STREAM
                }
#endif  /* WMAAPI_NO_DRM_STREAM */

                /* Initialize DRM so it can decrypt this payload properly */

#ifdef WMDRM_PORTABLE
                if( pInt->bHasJanusDRM )
                {
                    hr = DRM_MGR_InitDecrypt( pInt->pJanusDecryptContext,
                                              pLast15,
                                              pInt->payload.cbPayloadSize );
                }
                else
#endif // WMDRM_PORTABLE
                hr = CDrmPD_InitPacket(pInt->pDRM_state, pLast15, pInt->payload.cbPayloadSize);
                if(hr != S_OK)
                {
#ifdef LOCAL_DEBUG
                    SerialPrintf("++ WMA_UpdateNewPayload: CDrmPD_InitPacket failed (0x%08x).\n\r", hr);
#endif /* LOCAL_DEBUG */
                    return cWMA_DRMFailed;
                }

#ifndef WMAAPI_NO_DRM_STREAM
                pInt->cbNextPayloadEndValid = 0;
#endif  /* WMAAPI_NO_DRM_STREAM */

#endif /* WMAAPI_NO_DRM */

            }

/*******************************************************************************************/            
            pInt->parse_state = csWMA_DecodeAudioData;
            
            return cWMA_NoErr;
            break;

        default:
#ifdef LOCAL_DEBUG
            while(1);
#else  /* LOCAL_DEBUG */
            return cWMA_Internal;
#endif /* LOCAL_DEBUG */
        }

    } while(1);

    return cWMA_NoErr;
}

#if 0
/****************************************************************************/
WMARESULT WMARawDecCBGetData (U8_WMARawDec **ppBuffer, U32_WMARawDec *pcbBuffer, U32UP_WMARawDec dwUserData)
{
    tWMAFileStateInternal *pInt = (tWMAFileStateInternal *) dwUserData;
    tWMA_U32 num_bytes = WMA_MAX_DATA_REQUESTED;
    tWMA_U32 cbActual =0;
    tWMA_U32 cbWanted =0;
    BYTE *pbuff = NULL;
    tWMAFileStatus rc;
    tWMAParseState parse_state;

#ifndef WMAAPI_NO_DRM
    HRESULT hr;
#endif // WMAAPI_NO_DRM

    if(pInt == NULL || ppBuffer == NULL || pcbBuffer == NULL)
    {
        if(ppBuffer != NULL)
        {
            *ppBuffer = NULL;
        }
        if(pcbBuffer != NULL)
        {
            *pcbBuffer = 0;
        }

        return WMA_E_INVALIDARG;
    }

    *ppBuffer = NULL;
    *pcbBuffer = 0;

    /* If we used up the current payload, try to get the
     * next one.
     */
    
    // Added by Amit to take care of compressed payloads
    if (pInt->payload.bIsCompressedPayload == 1)
    {
        do
        {
            switch (pInt->payload.bSubPayloadState)
            {
            case 1: // Compressed payload just started
                cbWanted = 1; //to read subpayload length
                cbActual = WMAFileCBGetData ((tHWMAFileState *)pInt, pInt->cbPayloadOffset, cbWanted, &pbuff);
                pInt->cbPayloadOffset += cbWanted;
                pInt->bBlockStart = TRUE;
                pInt->cbBlockLeft = pInt->hdr_parse.nBlockAlign;

                pInt->payload.bNextSubPayloadSize = pbuff[0];
                pInt->payload.wSubpayloadLeft = pInt->payload.bNextSubPayloadSize;
                if (pInt->payload.wSubpayloadLeft > 0)
                    pInt->payload.wSubpayloadLeft -= (WORD)pInt->cbBlockLeft;

                if( pInt->payload.wTotalDataBytes > pInt->payload.bNextSubPayloadSize)
                    pInt->payload.wBytesRead = pInt->payload.bNextSubPayloadSize+1;
                else if ( pInt->payload.wTotalDataBytes == pInt->payload.bNextSubPayloadSize)
                    pInt->payload.wBytesRead = pInt->payload.bNextSubPayloadSize;

                pInt->payload.bSubPayloadState = 2;
                break;
            case 2: // Subpayload started
                if (pInt->cbBlockLeft == 0 && pInt->payload.wSubpayloadLeft == 0)
                {
                    pInt->payload.bSubPayloadState =3;
                    break;
                }
                else
                {
                    if(pInt->cbBlockLeft == 0)
                    {
                        if (/*pInt->cbPayloadLeft*/pInt->payload.wSubpayloadLeft == 0) /* done with the file */
                            return WMA_S_NEWPACKET;

                        if (pInt->payload.wSubpayloadLeft > 0)
                            pInt->payload.wSubpayloadLeft -= (WORD) pInt->hdr_parse.nBlockAlign;
                        pInt->bBlockStart = TRUE;
                        pInt->cbBlockLeft = pInt->hdr_parse.nBlockAlign;
                    }
                    if(num_bytes > pInt->cbBlockLeft)
                        num_bytes = pInt->cbBlockLeft;

                    *pcbBuffer = (unsigned int)WMAFileCBGetData((tHWMAFileState *)pInt,
                                                                pInt->cbPayloadOffset, num_bytes, ppBuffer);
                    pInt->cbPayloadOffset+=*pcbBuffer;
                    //pInt->payload.wSubpayloadLeft -= *pcbBuffer;
                    pInt->cbBlockLeft     -= *pcbBuffer;
                
/****************************************************************************************/
#ifdef WMDRM_PORTABLE
                    if( pInt->bHasJanusDRM )
                    {

                        hr = DRM_MGR_Decrypt( pInt->pJanusDecryptContext,
                                              *ppBuffer,
                                              *pcbBuffer);
                        if( hr != S_OK )
                        {
                            *ppBuffer = NULL;
                            *pcbBuffer = 0;
                            return WMA_S_NEWPACKET;
                        }
                    }
#endif // WMDRM_PORTABLE

                    if (pInt->bHasDRM)
                    {

#ifdef WMAAPI_NO_DRM
                        return WMA_S_NEWPACKET;
#else  /* WMAAPI_NO_DRM */

                        hr = CDrmPD_Decrypt (pInt->pDRM_state, *ppBuffer, *pcbBuffer);
                        if (hr != S_OK) {
#ifdef LOCAL_DEBUG
                            SerialPrintf("++ WMARawDecCBGetData: CDrmPD_Decrypt failed (0x%08x).\n\r", hr);
#endif /* LOCAL_DEBUG */
                            *ppBuffer = NULL;
                            *pcbBuffer = 0;
                            return WMA_S_NEWPACKET;
                        }

#endif /* WMAAPI_NO_DRM */

                    }



/****************************************************************************************/
                    if (pInt->bBlockStart) {
                        pInt->bBlockStart = FALSE;
                        return WMA_S_NEWPACKET;
                    }


                    return WMA_OK;
                }

                break;
            case 3: // Subpayload finished
                if ( pInt->payload.wTotalDataBytes > pInt->payload.wBytesRead)
                { // there are payloads to decode
                    cbWanted = 1; //to read subpayload length
                    cbActual = WMAFileCBGetData((tHWMAFileState *)pInt,
                                                        pInt->cbPayloadOffset, cbWanted, &pbuff);
                    pInt->cbPayloadOffset+=cbWanted;
                    pInt->bBlockStart     = TRUE;
                    pInt->cbBlockLeft     = pInt->hdr_parse.nBlockAlign;

                    
                    pInt->payload.bNextSubPayloadSize = pbuff[0];
                    pInt->payload.wSubpayloadLeft = pInt->payload.bNextSubPayloadSize;
                    if (pInt->payload.wSubpayloadLeft > 0)
                        pInt->payload.wSubpayloadLeft -= (WORD)pInt->cbBlockLeft;
                    pInt->payload.wBytesRead+=pInt->payload.bNextSubPayloadSize+1;
                    pInt->payload.bSubPayloadState =2;                
                }
                else
                    pInt->payload.bSubPayloadState =4; // all subpayloads finished
                break;

            case 4: // All Subpayloads finished

                parse_state = pInt->parse_state;
                pInt->payload.bSubPayloadState =0;
                pInt->cbPayloadLeft =0;
                pInt->payload.bIsCompressedPayload =0;

                pInt->parse_state = csWMA_DecodePayloadEnd;
                rc = WMAF_UpdateNewPayload(pInt);
                pInt->parse_state = parse_state;  //restore 
                if((rc != cWMA_NoErr)) 
                    return WMA_S_NEWPACKET;
                break;
            }
        } while(1);


    }          
    else
    {
        if(pInt->cbBlockLeft == 0 && pInt->cbPayloadLeft == 0)
        {
            tWMAFileStatus rc;
            tWMAParseState parse_state;

            parse_state = pInt->parse_state;

            pInt->parse_state = csWMA_DecodePayloadEnd;
            rc = WMAF_UpdateNewPayload(pInt);
            pInt->parse_state = parse_state; /* restore */

            if(rc != cWMA_NoErr)
                return WMA_S_NEWPACKET;
        }

        /* return as much as we currently have left */

        if(pInt->cbBlockLeft == 0)
        {
            if(pInt->cbPayloadLeft == 0)
            {
                /* done with the file */
                return WMA_S_NEWPACKET;
            }

            pInt->cbPayloadLeft -= pInt->hdr_parse.nBlockAlign;
            pInt->bBlockStart = TRUE;
            pInt->cbBlockLeft = pInt->hdr_parse.nBlockAlign;
        }
        if(num_bytes > pInt->cbBlockLeft)
            num_bytes = pInt->cbBlockLeft;

        *pcbBuffer = (unsigned int)WMAFileCBGetData((tHWMAFileState *)pInt,
                                                    pInt->cbPayloadOffset, num_bytes, ppBuffer);
        pInt->cbPayloadOffset += *pcbBuffer;
        pInt->cbBlockLeft     -= *pcbBuffer;

        /* DRM decryption if necessary */

#ifdef WMDRM_PORTABLE
        if( pInt->bHasJanusDRM )
        {
            hr = DRM_MGR_Decrypt( pInt->pJanusDecryptContext,
                                  *ppBuffer,
                                  *pcbBuffer);
            if( hr != S_OK )
            {
                *ppBuffer = NULL;
                *pcbBuffer = 0;
                return WMA_S_NEWPACKET;
            }
        }
#endif // WMDRM_PORTABLE

        if (pInt->bHasDRM)
        {

#ifdef WMAAPI_NO_DRM
            return WMA_S_NEWPACKET;
#else  /* WMAAPI_NO_DRM */

            hr = CDrmPD_Decrypt (pInt->pDRM_state, *ppBuffer, *pcbBuffer);
            if (hr != S_OK) {
#ifdef LOCAL_DEBUG
                SerialPrintf("++ WMARawDecCBGetData: CDrmPD_Decrypt failed (0x%08x).\n\r", hr);
#endif /* LOCAL_DEBUG */
                *ppBuffer = NULL;
                *pcbBuffer = 0;
                return WMA_S_NEWPACKET;
            }

#endif /* WMAAPI_NO_DRM */

        }

        if (pInt->bBlockStart) {
            pInt->bBlockStart = FALSE;
            return WMA_S_NEWPACKET;
        }

        return WMA_OK;
    }
    return WMA_OK;
}

#endif

/* ===========================================================================
 * WMAFileMBRAudioStreams
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileMBRAudioStreams (tHWMAFileState pstate, 
                                       tWMA_U16 *pTotalAudioStreams)
{
    
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)pstate;
    WMAERR wmarc = WMAERR_OK;

    if(NULL == pInt ||
       NULL == pTotalAudioStreams)
    {
        return cWMA_BadArgument;
    }
#ifdef ISBADPTR
    if (IsBadWritePtr(pTotalAudioStreams, sizeof(tWMA_U16)))
        return cWMA_BadArgument;
#endif
    
    *pTotalAudioStreams = pInt->cAudioStreams;

    return wmarc;
} // WMAFileMBRAudioStreams

/* ===========================================================================
 * WMAFileMBRAudioStreams
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileSetTargetMBRAudioStream (tHWMAFileState pstate, 
                                               tWMA_U16 wTargetAudioStream)
{
    
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)pstate;
    WMAERR wmarc = WMAERR_OK;

    if(NULL == pInt || 
       0 == wTargetAudioStream)
    {
        return cWMA_BadArgument;
    }
    
    pInt->wTargetAudioStreamNumber = wTargetAudioStream;
    

    return wmarc;
} // WMAFileMBRAudioStreams


/* ===========================================================================
 * WMAFileIsWMA
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileIsWMA (tWMAFileHdrState *pstate)
{
    
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)pstate;
    WMAERR wmarc = WMAERR_OK;

    if(pInt == NULL)
        return cWMA_BadArgument;
#ifdef ISBADPTR
    if (IsBadReadPtr(pstate, sizeof(tWMAFileHdrState)))
        return cWMA_BadArgument;
#endif

    /* parse ASF header */

    wmarc = WMA_ParseAsfHeader(pInt, 0);

    WMADebugMessage( "Wma::WMAFileIsWMA s/s %d, ch %d, al %d, bps %d\n", 
        pInt->nSamplesPerSec, pInt->nChannels, pInt->nBlockAlign, pInt->nAvgBytesPerSec);
        
    if(wmarc != WMAERR_OK)
        return cWMA_BadAsfHeader;

// Amit 03/15/2002 Check Audio properties before init codec

    if (pInt->nSamplesPerSec == 0||
        pInt->nChannels == 0||
        pInt->nBlockAlign == 0 ||
        pInt->nAvgBytesPerSec ==0
        )
        return cWMA_BadAsfHeader; 


    return cWMA_NoErr;
}

tWMAFileStatus WMAFreeFileHdrState (tWMAFileHdrState *state)
{
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)state;
    
    if (pInt->m_pDesc)
    {
        tWMAFileContDesc *pDesc = pInt->m_pDesc;

        // it's OK to pass NULL pointers to free
        free(pDesc->pTitle);
        free(pDesc->pAuthor);
        free(pDesc->pCopyright);
        free(pDesc->pDescription);
        free(pDesc->pRating);

        free(pInt->m_pDesc);
        pInt->m_pDesc = NULL;
    }

    return cWMA_NoErr;
}

/* ===========================================================================
 * WMAGetLicenseStore
--------------------------------------------------------------------------- */
BYTE * WMAGetLicenseStore (tWMAFileHdrState *pstate,tWMA_U32 *pLen)
{
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)pstate;

    if((pInt == NULL) || (pLen == NULL))
        return NULL;

#ifdef ISBADPTR
    if (IsBadReadPtr(pstate, sizeof(tWMAFileHdrState)))
        return NULL;
    if (IsBadReadPtr(pLen, sizeof(tWMA_U32)))
        return NULL;
#endif


    *pLen = pInt->m_dwLicenseLen;

    return pInt->m_pLicData;
}

/* ===========================================================================
 * WMAFileDecodeClose
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileDecodeClose (tHWMAFileState* phstate)
{
    tWMAFileStateInternal *pInt;
    unsigned int i =0;

    if ((phstate == NULL) ||(*phstate == NULL))
        return cWMA_BadArgument;

    pInt = (tWMAFileStateInternal*) (*phstate);

#ifdef ISBADPTR
    if (IsBadReadPtr(*phstate, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif
 
    
    if (pInt != NULL ) {

#ifdef  USE_SPDTX
        spdtxDelete (pInt->hSPDTX);
        if( pInt->szmdata ) free( pInt->szmdata );
        pInt->szmdata = NULL;
        pInt->hSPDTX  = NULL;
#else
        audecDelete (pInt->hWMA);
        pInt->hWMA = NULL;
#endif

#ifndef WMAAPI_NO_DRM
        if (pInt->pDRM_state != NULL) {
            free (pInt->pDRM_state);
            pInt->pDRM_state = NULL;
        }
#endif

#ifdef WMDRM_PORTABLE
        if( pInt->pJanusContext != NULL )
        {
            free( pInt->pJanusContext );
            pInt->pJanusContext = NULL;
        }

        if( pInt->pJanusDecryptContext != NULL )
        {
            free( pInt->pJanusDecryptContext );
            pInt->pJanusDecryptContext = NULL;
        }

        if( pInt->hdr_parse.pbCEncExData != NULL )
        {
            free( pInt->hdr_parse.pbCEncExData );
            pInt->hdr_parse.pbCEncExData = NULL;
        }
#endif

#if 0
        if (pInt->hdr_parse.m_pMarkers) {
            for (i=0;i<pInt->hdr_parse.m_dwMarkerNum;i++)
                if ( pInt->hdr_parse.m_pMarkers[i].m_pwDescName != NULL )
                {
                    free (pInt->hdr_parse.m_pMarkers[i].m_pwDescName);
                    pInt->hdr_parse.m_pMarkers[i].m_pwDescName = NULL;
                }
            free (pInt->hdr_parse.m_pMarkers);
            pInt->hdr_parse.m_pMarkers = NULL;
        }
#endif 
        if (pInt->hdr_parse.m_pLicData) 
        {
            free (pInt->hdr_parse.m_pLicData);
            pInt->hdr_parse.m_pLicData = NULL;
        }

        if(NULL != pInt->hdr_parse.m_pDesc) 
		{
			tWMAFileContDesc *pDesc = pInt->hdr_parse.m_pDesc;
			free(pDesc->pTitle);
			free(pDesc->pAuthor);
			free(pDesc->pCopyright);
			free(pDesc->pDescription);
			free(pDesc->pRating);
			free(pDesc);
			pInt->hdr_parse.m_pDesc = 0;
		}

        if(pInt->hdr_parse.m_pECDesc != NULL) {
            if(pInt->hdr_parse.m_pECDesc->cDescriptors > 0) {
                for (i = 0; i < (unsigned int) pInt->hdr_parse.m_pECDesc->cDescriptors; i++) {
                    free(pInt->hdr_parse.m_pECDesc->pDescriptors[i].uValue.pbBinary);
                    free(pInt->hdr_parse.m_pECDesc->pDescriptors[i].pwszName);
                    pInt->hdr_parse.m_pECDesc->pDescriptors[i].uValue.pbBinary = NULL;
                    pInt->hdr_parse.m_pECDesc->pDescriptors[i].pwszName = NULL;
                }
                free(pInt->hdr_parse.m_pECDesc->pDescriptors);
                pInt->hdr_parse.m_pECDesc->pDescriptors = NULL;
            }
            free(pInt->hdr_parse.m_pECDesc);
            pInt->hdr_parse.m_pECDesc = NULL;
        }


        // Free Metadata        
        if(pInt->hdr_parse.ptMetaDataEntry != NULL) 
        {
            if(pInt->hdr_parse.ptMetaDataEntry->m_wDescRecordsCount > 0) 
            {
                for (i = 0; i < (unsigned int) pInt->hdr_parse.ptMetaDataEntry->m_wDescRecordsCount; i++) 
                {
                    if (NULL != pInt->hdr_parse.ptMetaDataEntry->pDescRec)
                    {
                        if (pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName)
                            free(pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName);
                        pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName = NULL;

                        if (pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData)
                            free(pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData);
                        pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData = NULL;
                    }
                }
                free(pInt->hdr_parse.ptMetaDataEntry->pDescRec);
                pInt->hdr_parse.ptMetaDataEntry->pDescRec = NULL;
            }
            free(pInt->hdr_parse.ptMetaDataEntry);
            pInt->hdr_parse.ptMetaDataEntry = NULL;
        }
        
        
        if (pInt->pCallBackBuffer != NULL)
            free(pInt->pCallBackBuffer);
        pInt->pCallBackBuffer = NULL;

        if (pInt->pPlayerInfo != NULL)
		{
			WMAPlayerInfo *pPlayerInfo = (WMAPlayerInfo *)pInt->pPlayerInfo;
			if (NULL != pPlayerInfo->rgiMixDownMatrix)
				free(pPlayerInfo->rgiMixDownMatrix);
			
			free(pPlayerInfo);
		}
        pInt->pPlayerInfo = NULL;


        free (pInt);
        *phstate = NULL;
    }
    phstate = NULL;
    return cWMA_NoErr;
}

/* ===========================================================================
 * WMAFileDecodeCreate
--------------------------------------------------------------------------- */
BYTE pDrmBuffer[4096];
tWMAFileStatus WMAFileDecodeCreate (tHWMAFileState *phstate)
{
    tWMAFileStateInternal *pInt;

#ifdef USE_WOW_FILTER
    WowControls         tempWowControls;
#endif

    if (NULL == phstate)
        return cWMA_BadArgument;

#ifdef ISBADPTR
    if (IsBadReadPtr(phstate, sizeof(tHWMAFileState)))
        return cWMA_BadArgument;
#endif


    // first try to close in case someone calls us without prior close
    WMAFileDecodeClose (phstate);

    // Now start to allocate and initialize

    pInt = (tWMAFileStateInternal*) malloc (sizeof (tWMAFileStateInternal));

    if (pInt == NULL)
        return cWMA_Failed;

    memset (pInt, 0, sizeof (tWMAFileStateInternal));

    /* initialize the some state */

    pInt->parse_state = csWMA_HeaderStart;

    /* parse ASF header */

    *phstate = (tHWMAFileState) pInt;

    return cWMA_NoErr;
}

#ifdef WMDRM_NETWORK
tWMAFileStatus WMASetWMDRMNetworkAESKey( tHWMAFileState phstate, 
                                         DRM_AES_KEY *pKey )
{
    tWMAFileStateInternal *pInt;
    pInt = (tWMAFileStateInternal*) phstate;

    if( NULL != pKey )
    {
        pInt->pWMDRMNetworkKey = pKey;
        pInt->bHasWMDRMNetworkDRM = TRUE;
    }
    else
    {
        pInt->bHasWMDRMNetworkDRM = FALSE;
    }

    return cWMA_NoErr;
}
#endif

/* ===========================================================================
 * WMAFileDecodeInit
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileDecodeInit (tHWMAFileState hstate, tWMA_U16 nPlayerOpt)
{
    // nPlayerOpt is ignored!!
    PCMFormat pcmFormat;

    return WMAFileDecodeInitEx (hstate, 0, 0, 0, 0, 0, &pcmFormat, 1);
}

tWMAFileStatus WMAFileDecodeInit2 (tHWMAFileState hstate,
                                   WMAFormat *pWMAFormat,
                                   PCMFormat *pPCMFormat,
                                   WMAPlayerInfo *pPlayerInfo)
{
    WMARESULT wmar = WMA_OK;    
    tWMAFileStateInternal *pInt;
    pInt = (tWMAFileStateInternal*) hstate;

    wmar = WMAFileDecodeInitEx (hstate, 0, 0, 0, 0, 0, pPCMFormat, 1);
    
    pWMAFormat->wFormatTag           = (WMA_U16) pInt->hdr_parse.wFormatTag;           
    pWMAFormat->nChannels            = (WMA_U16) pInt->hdr_parse.nChannels;          
    pWMAFormat->nSamplesPerSec       = (WMA_U32) pInt->hdr_parse.nSamplesPerSec;     
    pWMAFormat->nAvgBytesPerSec      = (WMA_U32) pInt->hdr_parse.nAvgBytesPerSec;    
    pWMAFormat->nBlockAlign          = (WMA_U16) pInt->hdr_parse.nBlockAlign;        
    pWMAFormat->nValidBitsPerSample  = (WMA_U16) pInt->hdr_parse.wValidBitsPerSample;
    pWMAFormat->nChannelMask         = (WMA_U32) pInt->hdr_parse.dwChannelMask;      
    pWMAFormat->wEncodeOpt           = (WMA_U16) pInt->hdr_parse.nEncodeOpt;
    pWMAFormat->wAdvancedEncodeOpt   = (WMA_U16) pInt->hdr_parse.nAdvancedEncodeOpt;
    pWMAFormat->dwAdvancedEncodeOpt2 = (WMA_U32) pInt->hdr_parse.nAdvancedEncodeOpt2;

    pPCMFormat->cbPCMContainerSize   = (WMA_U32) pInt->hdr_parse.wBitsPerSample/8;   
    pPCMFormat->nSamplesPerSec       = (WMA_U32) pInt->hdr_parse.nSamplesPerSec;     
    pPCMFormat->nValidBitsPerSample  = (WMA_U16) pInt->hdr_parse.wValidBitsPerSample;
    
    WMAFormat2PCMFormat(pWMAFormat, pPCMFormat);
    memcpy ( pPlayerInfo, pInt->pPlayerInfo, sizeof(WMAPlayerInfo));

    return wmar;

}


tWMAFileStatus WMAFileDecodeInitEx (tHWMAFileState hstate, tWMA_U16 nDecoderFlags,
                                    tWMA_U16 nDRCSetting,  tWMA_Bool bDropPacket,
                                    tWMA_U32 nDstChannelMask,  
                                    tWMA_U32 nInterpResampRate,
                                    PCMFormat* pPCMFormat,
                                    tWMA_U16 wTargetAudioStream)
{
    tWMAFileStateInternal *pInt;
    WMAERR wmarc = WMAERR_OK;
    WMARESULT wmar = WMA_OK;
    WMAPlayerInfo PlayerInfo;
    WMAFormat WMAFormat;
    tWMA_U16 nPlayerOpt = 0;
    WMA_U16 i=0;


    WMA_I32 *rgiMixDownMatrix = NULL; // Can be null to invoke defaults
    WMA_I32 iPeakAmplitudeRef = 0;
    WMA_I32 iRmsAmplitudeRef = 0;
    WMA_I32 iPeakAmplitudeTarget = 0;
    WMA_I32 iRmsAmplitudeTarget = 0;
    WMA_U16 nInChannels =0;
    WMA_U16 nOutChannels =0;
    WMA_U32 nMask =0;
        
#ifndef WMAAPI_NO_DRM
    HRESULT hr;
#endif // WMAAPI_NO_DRM

#ifdef USE_WOW_FILTER
    WowControls         tempWowControls;
#endif

    WMADebugMessage( " WMAFileDecodeInitEx\n"); 
    
    // we dont have drc headers from ASF file yet.
    if (NULL == pPCMFormat || 
        0 == wTargetAudioStream)
    {
        WMADebugMessage( " WMAFileDecodeInitEx - fail 1\n"); 
        return cWMA_BadArgument;
    }

    pInt = (tWMAFileStateInternal*) hstate;

    if (pInt == NULL)
    {
        WMADebugMessage( " WMAFileDecodeInitEx - fail 2\n"); 
        return cWMA_BadArgument;
    }
#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif

    pInt->hdr_parse.wTargetAudioStreamNumber = wTargetAudioStream;

    wmarc = WMA_ParseAsfHeader(&pInt->hdr_parse, 1);
    if (wmarc != WMAERR_OK)
    {
        WMADebugMessage( " WMAFileDecodeInitEx - fail 3\n"); 
        return cWMA_BadAsfHeader;
    }
// Amit 03/15/2002 Check Audio properties before init codec

    if (pInt->hdr_parse.nSamplesPerSec == 0||
        pInt->hdr_parse.nChannels == 0||
        pInt->hdr_parse.nBlockAlign == 0 ||
        pInt->hdr_parse.nAvgBytesPerSec ==0
        )
    {
        WMADebugMessage( " WMAFileDecodeInitEx - fail 4\n"); 
        return cWMA_BadAsfHeader; 
    }
	assert(pInt->pPlayerInfo == NULL);

    // Try to get metadata

    if (NULL != pInt->hdr_parse.ptMetaDataEntry)
    {
        WMA_U8 PeakRef[] = {'W','M','/','W','M','A','D','R','C','P','e','a','k','R','e','f','e','r','e','n','c','e',0x00};
        WMA_U8 PeakTgt[] = {'W','M','/','W','M','A','D','R','C','P','e','a','k','T','a','r','g','e','t',0x00};
        WMA_U8 RmsRef[] =  {'W','M','/','W','M','A','D','R','C','A','v','e','r','a','g','e','R','e','f','e','r','e','n','c','e',0x00};
        WMA_U8 RmsTgt[] =  {'W','M','/','W','M','A','D','R','C','A','v','e','r','a','g','e','T','a','r','g','e','t',0x00};
        WMA_U8 Fold[] =    {'F','o','l','d','%','T','o','%','C','h','a','n','n','e','l','s','%',0x00};
        WMA_U32 dwValues[3] = {0,0,0};

        WMADebugMessage( " WMAFileDecodeInitEx - metadata\n"); 
        
        
        if (pInt->hdr_parse.ptMetaDataEntry->m_wDescRecordsCount > 0  &&
            NULL != pInt->hdr_parse.ptMetaDataEntry->pDescRec)
        {
            for (i=0; i< pInt->hdr_parse.ptMetaDataEntry->m_wDescRecordsCount; i++)
            {
                if (pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wStreamNumber == 0 ||
                    pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wStreamNumber == 
                    pInt->hdr_parse.wAudioStreamId)
                {
                    // Data is for that stream.
                    if (0==WMA_CompareWToC(PeakRef,pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName, pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wNameLenth, NULL))
                        iPeakAmplitudeRef = (WMA_I32)(*(WMA_U32 *)pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData);
                        
                    else if (0==WMA_CompareWToC(RmsRef,pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName, pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wNameLenth, NULL))
                        iRmsAmplitudeRef = (WMA_I32) (*(WMA_U32 *)pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData);

                    else if (0==WMA_CompareWToC(PeakTgt,pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName, pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wNameLenth, NULL))
                        iPeakAmplitudeTarget = (WMA_I32) (*(WMA_U32 *)pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData);

                    else if (0==WMA_CompareWToC(RmsTgt,pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName, pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wNameLenth, NULL))
                        iRmsAmplitudeTarget = (WMA_I32) (*(WMA_U32 *)pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData);
                    
                    else if (0==WMA_CompareWToC(Fold,pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pwName, pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].wNameLenth, dwValues))
                    {
                    
                        nInChannels = (WMA_U16) dwValues[0];
                        nOutChannels = (WMA_U16) dwValues[1];
                        nMask = dwValues[2];
                        assert(pInt->hdr_parse.nChannels == nInChannels);
                        if (nInChannels == pInt->hdr_parse.nChannels)
                        {
                            // Now get the values
                            rgiMixDownMatrix = (WMA_I32 *)malloc(sizeof(WMA_I32)*nInChannels*nOutChannels);

                            wmar = WMA_ParseFoldDown((WMA_U16 *)pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].pData,  
                                                      pInt->hdr_parse.ptMetaDataEntry->pDescRec[i].dwDataLength,
                                                      rgiMixDownMatrix, (WMA_U16)(nInChannels*nOutChannels));
                            if (WMA_OK != wmar)
                            {
                                nInChannels = 0;
                                nOutChannels = 0;
                                nMask = 0;
                            }

                        }
                        else
                        {
                            nInChannels = 0;
                            nOutChannels = 0;
                            nMask = 0;
                            rgiMixDownMatrix = NULL;
                        }
                    }

                }
            }
        }
    }




    /* Set up and initialize the WMA bitstreamd decoder */
    WMADebugMessage( " WMAFileDecodeInitEx - bitstream decoder\n"); 

#ifdef USE_SPDTX
    pInt->hSPDTX = spdtxNew(NULL,0);
    if(!pInt->hSPDTX) return cWMA_Failed;
#else
    pInt->hWMA = audecNew(NULL,0);
    if (!pInt->hWMA) return cWMA_Failed;
#endif

    memset(&PlayerInfo, 0, sizeof(PlayerInfo));
    PlayerInfo.nPlayerOpt = nPlayerOpt;
    WMAFormat.wFormatTag           = (WMA_U16) pInt->hdr_parse.wFormatTag;           
    WMAFormat.nChannels            = (WMA_U16) pInt->hdr_parse.nChannels;          
    WMAFormat.nSamplesPerSec       = (WMA_U32) pInt->hdr_parse.nSamplesPerSec;     
    WMAFormat.nAvgBytesPerSec      = (WMA_U32) pInt->hdr_parse.nAvgBytesPerSec;    
    WMAFormat.nBlockAlign          = (WMA_U16) pInt->hdr_parse.nBlockAlign;        
    WMAFormat.nValidBitsPerSample  = (WMA_U16) pInt->hdr_parse.wValidBitsPerSample;
    WMAFormat.nChannelMask         = (WMA_U32) pInt->hdr_parse.dwChannelMask;      
    WMAFormat.wEncodeOpt           = (WMA_U16) pInt->hdr_parse.nEncodeOpt;         
    WMAFormat.wAdvancedEncodeOpt   = (WMA_U16) pInt->hdr_parse.nAdvancedEncodeOpt;
    WMAFormat.dwAdvancedEncodeOpt2 = (WMA_U32) pInt->hdr_parse.nAdvancedEncodeOpt2;
    pPCMFormat->cbPCMContainerSize   = (WMA_U32) pInt->hdr_parse.wBitsPerSample/8;   
    pPCMFormat->nSamplesPerSec       = (WMA_U32) pInt->hdr_parse.nSamplesPerSec;     
    pPCMFormat->nValidBitsPerSample  = (WMA_U16) pInt->hdr_parse.wValidBitsPerSample;
    
    WMAFormat2PCMFormat(&WMAFormat, pPCMFormat);
    
    //
    // Adjust PlayerInfo and output format based on command line args
    //
    if (nDecoderFlags & DECOPT_CHANNEL_DOWNMIXING) 
    {
        U32 dwDstChannelMask = nDstChannelMask; // Temporary variable
        
        pPCMFormat->nChannels = 0;
        pPCMFormat->nChannelMask = dwDstChannelMask;
        while (dwDstChannelMask)
        {
            pPCMFormat->nChannels += dwDstChannelMask & 0x1;
            dwDstChannelMask >>= 1;
        }
    }
    
    if (nDecoderFlags & DECOPT_LTRTDOWNMIX)
    {
        PlayerInfo.nPlayerOpt |= PLAYOPT_LTRT;
        // Make the player downsample data
        pPCMFormat->nChannels = min(2,pPCMFormat->nChannels);
        if (pPCMFormat->nChannels == 2)
        {
            // Left-right channels
            pPCMFormat->nChannelMask = 0x3;
        }
    }

    
    if (nDecoderFlags & DECOPT_REQUANTTO16) 
    {
        pPCMFormat->nValidBitsPerSample = 16;
        pPCMFormat->cbPCMContainerSize = 2;
    }
    else if(nDecoderFlags & DECOPT_PCM24_OUT)
    {
        // valid bits dictated by wma format
        pPCMFormat->cbPCMContainerSize = 3;
    }
    else if (nDecoderFlags & DECOPT_PCM32_OUT)
    {
        // valid bits dictated by wma format
        pPCMFormat->cbPCMContainerSize = 4;
    }

    PlayerInfo.nDRCSetting = WMA_DRC_HIGH;
    if (nDecoderFlags & DECOPT_DRC)
    {
        PlayerInfo.nPlayerOpt |= PLAYOPT_DYNAMICRANGECOMPR;
        PlayerInfo.nDRCSetting = nDRCSetting;
    }
    
    if (nDecoderFlags & DECOPT_INTERPOLATED_DOWNSAMPLE)
    {
        if (32000==WMAFormat.nSamplesPerSec && 0==nInterpResampRate)
            nInterpResampRate = 22050;
        if (0!=nInterpResampRate)
            pPCMFormat->nSamplesPerSec = nInterpResampRate;
    }

    if (nDecoderFlags & DECOPT_HALF_UP_TRANSFORM)
    {
        // test this for audio driver which does not support half the sampling rate
        PlayerInfo.nPlayerOpt |= PLAYOPT_HALFTRANSFORM;
    }
    else if (nDecoderFlags & DECOPT_HALF_TRANSFORM)
    {
        // normal case for audio driver which supports half the sampling rate
        PlayerInfo.nPlayerOpt |= PLAYOPT_HALFTRANSFORM;
        pPCMFormat->nSamplesPerSec /= 2;
    } 
    else if (nDecoderFlags & DECOPT_2X_TRANSFORM)
    {
        pPCMFormat->nSamplesPerSec *= 2;
    }

    if (nDecoderFlags & DECOPT_DOWNSAMPLETO44OR48)
    {
        if (pPCMFormat->nSamplesPerSec % 44100 == 0)
            pPCMFormat->nSamplesPerSec = 44100;
        if (pPCMFormat->nSamplesPerSec % 48000 == 0)
            pPCMFormat->nSamplesPerSec = 48000;
    }

    if (nDecoderFlags & DECOPT_FLOAT_OUT)
    {
        // Verify if it clashes with other options
        if ((nDecoderFlags & DECOPT_REQUANTTO16)||
            (nDecoderFlags & DECOPT_PCM24_OUT) || 
            (nDecoderFlags & DECOPT_PCM32_OUT))
        {
            //fprintf(stderr, "Can not specify pcm out, float out at the same time\n");
            return cWMA_Failed;
        }
        pPCMFormat->pcmData = PCMDataIEEE_FLOAT;
        pPCMFormat->nValidBitsPerSample = sizeof(Float) * BITS_PER_BYTE;
        pPCMFormat->cbPCMContainerSize  = sizeof(Float);
    }

    if (nDecoderFlags & DECOPT_IGNOREFREQEX)
    {
        PlayerInfo.nPlayerOpt |= PLAYOPT_IGNOREFREQEX;
    }

    if (nDecoderFlags & DECOPT_IGNORECX)
    {
        PlayerInfo.nPlayerOpt |= PLAYOPT_IGNORECX;
    }

    // PlayerInfo needs lot more stuff to be filled: TODO.

    PlayerInfo.iPeakAmplitudeRef = iPeakAmplitudeRef;
    PlayerInfo.iRmsAmplitudeRef = iRmsAmplitudeRef;
    PlayerInfo.iPeakAmplitudeTarget = iPeakAmplitudeTarget;
    PlayerInfo.iRmsAmplitudeTarget = iRmsAmplitudeTarget;
    PlayerInfo.rgiMixDownMatrix = rgiMixDownMatrix;

#ifdef USE_SPDTX

    {
        tWMAFileContDesc *pDesc = pInt->hdr_parse.m_pDesc;

        WMA_METADATA_DRC drc = 
        {
            iPeakAmplitudeRef,
            iRmsAmplitudeRef,
            iPeakAmplitudeTarget,
            iRmsAmplitudeTarget
        };

        WMA_METADATA_FDMTX fdmtx =
        {
            rgiMixDownMatrix,
            nInChannels,
            nOutChannels
        };

        char *rgsz[ CT_TAGS ] = {0};

        if( pDesc )
        {
            const int len = pDesc->title_len + pDesc->author_len + 
                      pDesc->description_len + pDesc->copyright_len + 4;

            char *sz = pInt->szmdata = malloc( len );

            if( NULL == sz ) return cWMA_Failed;

            memset( sz, 0, len );

            if( pDesc->pTitle )
            {
                wcstombs( sz, (wchar_t*)pDesc->pTitle, pDesc->title_len );
                rgsz[ CT_TITLE ] = sz; sz += pDesc->title_len;
                sz[0] = '\0'; ++sz;
            }

            if( pDesc->pAuthor )
            {
                wcstombs( sz, (wchar_t*)pDesc->pAuthor, pDesc->author_len );
                rgsz[ CT_ARTIST ] = sz; sz += pDesc->author_len;
                sz[0] = '\0'; ++sz;
            }

            if( pDesc->pDescription )
            {
                wcstombs( sz, (wchar_t*)pDesc->pDescription, pDesc->description_len );
                rgsz[ CT_ALBUM ] = sz; sz += pDesc->description_len;
                sz[0] = '\0'; ++sz;
            }

            if( pDesc->pCopyright )
            {
                wcstombs( sz, (wchar_t*)pDesc->pCopyright, pDesc->copyright_len );
                rgsz[ CT_MISC ] = sz; sz += pDesc->copyright_len;
                sz[0] = '\0'; ++sz;
            }
        }

        if (wmar != WMA_OK) return cWMA_Failed;
        wmar = spdtxInit( pInt->hSPDTX, &WMAFormat, pInt->nLeadingBursts );
        if( WMA_FAILED( wmar ) ) return cWMA_Failed;
        wmar = spdtxInitWMAMetadata( pInt->hSPDTX, &drc, &fdmtx );
        if( WMA_FAILED( wmar ) ) return cWMA_Failed;
        wmar = spdtxInitMetadata( pInt->hSPDTX, rgsz );
        if( WMA_FAILED( wmar ) ) return cWMA_Failed;
    }
#else
    wmar = audecInit(pInt->hWMA, &WMAFormat, pPCMFormat, &PlayerInfo, &pInt->audecState, NULL);
    if ( WMA_FAILED( wmar ) )
    {
        WMADebugMessage( " WMAFileDecodeInitEx - audecInit() failed\n"); 
        return wmar;
    }
#endif

    // Dont Free rgiMixDownMatrix as we need it in pInt->pPlayerInfo
    
/*	if (NULL != rgiMixDownMatrix)
        free(rgiMixDownMatrix);
    rgiMixDownMatrix = NULL; */
    
/*    if (wmar == 0x80040000)
        return cWMA_BadSamplingRate; */

    if (wmar != WMA_OK)
    {
        WMADebugMessage( " WMAFileDecodeInitEx - fail 6\n"); 
        return cWMA_Failed;
    }
    pInt->pPlayerInfo = malloc(sizeof(WMAPlayerInfo));

	if (NULL != pInt->pPlayerInfo)
		memcpy(pInt->pPlayerInfo, &PlayerInfo, sizeof(WMAPlayerInfo));



    /* Set up the decryption if necessary */

    pInt->bHasDRM = (BOOL) 0;
#ifdef WMDRM_PORTABLE
    pInt->bHasJanusDRM = (BOOL) 0 ;
#endif

#ifdef WMDRM_NETWORK
    if( !pInt->bHasWMDRMNetworkDRM )
    {
#endif
#ifdef WMDRM_PORTABLE
    if( ( pInt->hdr_parse.cbSecretData > 0 ) ||
        ( pInt->hdr_parse.cbCEncExData > 0 ) )
    {
        DRM_RESULT dr;
        DRM_STRING *rgRights[ 1 ];

        if( pInt->pJanusContext != NULL )
        {
            free( pInt->pJanusContext );
        }

        pInt->pJanusContext = malloc( sizeof( DRM_MANAGER_CONTEXT ) );
        if( NULL == pInt->pJanusContext )
        {
            return( cWMA_DRMFailed );
        }

        if( pInt->pJanusDecryptContext )
        {
            free( pInt->pJanusDecryptContext );
        }

        pInt->pJanusDecryptContext = malloc( sizeof( DRM_MANAGER_DECRYPT_CONTEXT ) );
        if( NULL == pInt->pJanusDecryptContext )
        {
            return( cWMA_DRMFailed );
        }

        //
        // Request the playback right; change this if the device is doing
        // anything else with the file.
        //
        rgRights[ 0 ] = (DRM_STRING *) &g_dstrWMDRM_RIGHT_PLAYBACK;

        dr = DRM_MGR_Initialize( pInt->pJanusContext, &s_strLicense );
        if( DRM_SUCCESS != dr )
        {
            return( cWMA_DRMFailed );
        }

        dr = DRM_SUCCESS;

        do
        {
            if( pInt->hdr_parse.cbSecretData > 0 )
            {
                //
                // Tell DRM_MGR about the old header object, if it exists.
                //
                dr = DRM_MGR_SetV1Header( pInt->pJanusContext,
                                          (DRM_BYTE *) pInt->hdr_parse.pbKeyID,
                                          32,
                                          (DRM_BYTE *) pInt->hdr_parse.pbSecretData,
                                          pInt->hdr_parse.cbSecretData,
                                          (DRM_BYTE *) "",
                                          2 );
                if( DRM_SUCCESS != dr )
                {
                    break;
                }
            }

            if( pInt->hdr_parse.cbCEncExData > 0 )
            {
                //
                // The DRM_MGR about the new header object, which will exist.
                //
                dr = DRM_MGR_SetV2Header( pInt->pJanusContext,
                                          (DRM_BYTE *) pInt->hdr_parse.pbCEncExData,
                                          pInt->hdr_parse.cbCEncExData );
                if( DRM_SUCCESS != dr )
                {
                    break;
                }
            }

            //
            // Find the license for this content.
            //
            dr = DRM_MGR_Bind( pInt->pJanusContext,
                               (const DRM_CONST_STRING **) rgRights,
                               1,
                               NULL,
                               NULL,
                               pInt->pJanusDecryptContext );
            if( DRM_SUCCESS == dr )
            {
                //
                // Since we're definitely going to play the file, go ahead
                // and commit right now.
                //
                dr = DRM_MGR_Commit( pInt->pJanusContext );
                if( DRM_SUCCESS != dr )
                {
                    break;
                }
                
                pInt->bHasJanusDRM = (BOOL) 1;
            }
            else
            {
                //
                // OK, just no license. That's fine; try for a PDDRM license.
                //
                dr = DRM_SUCCESS;
            }
        }
        while( FALSE );

        DRM_MGR_Uninitialize( pInt->pJanusContext );
        free( pInt->pJanusContext );
        pInt->pJanusContext = NULL;

        if( DRM_SUCCESS != dr )
        {
            return( cWMA_DRMFailed );
        }

    }
#endif
#ifdef WMDRM_NETWORK
    }
#endif

#ifdef WMDRM_NETWORK
    if( !pInt->bHasWMDRMNetworkDRM )
    {
#endif
#ifdef WMDRM_PORTABLE
    if( !pInt->bHasJanusDRM && ( pInt->hdr_parse.cbSecretData > 0 ) )
#else
    if(pInt->hdr_parse.cbSecretData > 0)
#endif
    {
        /* only for DRM now */
        char *p = (char *)pInt->hdr_parse.pbType;

        if(p[0] == 'D' && p[1] == 'R' && p[2] == 'M' && p[3] == '\0')
        {
            pInt->bHasDRM = (BOOL)( 1 );

#ifndef WMAAPI_NO_DRM
            pInt->pDRM_state = malloc (SAFE_DRM_SIZE);
            if (pInt->pDRM_state == NULL)
                return cWMA_DRMFailed;
#ifndef WMAAPI_NO_DRM
#ifdef GLOBAL_SECRET
            SetSecret_1of7 (pInt->pDRM_state);
#endif // GLOBAL_SECRET
#endif /* WMAAPI_NO_DRM */
            hr = CDrmPD_Init(pInt->pDRM_state,pDrmBuffer,2048);
            if(hr != S_OK)
                return cWMA_DRMFailed;
#endif /* WMAAPI_NO_DRM */
        }
        else
            return cWMA_BadDRMType;
    }
#ifdef WMDRM_NETWORK
    }
#endif

#ifdef WMDRM_PORTABLE
    if( ( pInt->hdr_parse.cbSecretData > 0 ) ||
        ( pInt->hdr_parse.cbCEncExData > 0 ) )
    {
        if( !pInt->bHasDRM && !pInt->bHasJanusDRM )
        {
            //
            // No license.
            //
            return( cWMA_DRMFailed );
        }
    }
#endif

#ifdef WMDRM_NETWORK
    if( pInt->bHasWMDRMNetworkDRM )
    {
        if(pInt->hdr_parse.cbSecretData == 0)
        {
            //
            // Sanity: There should be a content encryption object.
            //
            return cWMA_DRMFailed;
        }
    }
#endif

    pInt->hdr_parse.cbLastPacketOffset = pInt->hdr_parse.cbFirstPacketOffset;
    if (pInt->hdr_parse.cPackets > 0)
    {
        if( bDropPacket ) --pInt->hdr_parse.cPackets;
        pInt->hdr_parse.cbLastPacketOffset += ((U64)pInt->hdr_parse.cPackets - 1)*pInt->hdr_parse.cbPacketSize;
    }

    // If broadcast flag is set, packet count is invalid. Override cbLastPacketOffset
    if (FILEPROPFLAG_BROADCAST & pInt->hdr_parse.dwFilePropertiesFlags)
    {
        // Set last packet offset to MAX - 1 packet. This prevents us from wrapping around.
        pInt->hdr_parse.cbLastPacketOffset = -1; // By -1 we mean MAX UNSIGNED VALUE
        pInt->hdr_parse.cbLastPacketOffset -= pInt->hdr_parse.cbPacketSize;
    }


    pInt->hdr_parse.currPacketOffset = pInt->hdr_parse.cbHeader;// Added by amit
    pInt->hdr_parse.nextPacketOffset = pInt->hdr_parse.cbHeader;
    pInt->parse_state = csWMA_NewAsfPacket;



#ifdef USE_WOW_FILTER
    tempWowControls.bEnableWow = TRUE;
    tempWowControls.bMonoInput = FALSE;
    tempWowControls.bHighBitRate = TRUE;
    tempWowControls.iSampleRate = k44100;
    tempWowControls.mBrightness = kHigh;
    tempWowControls.mSpeakerSize = kMedium;
    tempWowControls.dTruBass = 0.8;
    tempWowControls.dWidthControl = 0.6;

    switch(pInt->hdr_parse.nSamplesPerSec)
    {
        case 22050:
                tempWowControls.iSampleRate = k22050;
                break;
        case 32000:
                tempWowControls.iSampleRate = k32000;
                break;
        case 44100:
                tempWowControls.iSampleRate = k44100;
                break;
        default:
                break;
    }

    if ( pInt->hdr_parse.nChannels  == 1)
    {
        tempWowControls.bMonoInput          = TRUE;
    }

    if ( pInt->hdr_parse.nAvgBytesPerSec * 8 < 64000)
        tempWowControls.bHighBitRate    = FALSE;

    tempWowControls.bEnableWow      = TRUE;

    if ( InitWow(&(pInt->sWowChannel), &tempWowControls ) != 0) {
        return cWMA_BadDRMType;   //NQF_temp
    }

#endif  //USE_WOW_FILTER

#ifdef WMDRM_NETWORK
    if( pInt->bHasWMDRMNetworkDRM )
    {
        //
        // Allocate a larger buffer so we can decrypt whole media objects
        // at a time.
        //
        pInt->pCallBackBuffer = (BYTE *)malloc(pInt->hdr_parse.cbAudioSize);
    }
    else
    {
        pInt->pCallBackBuffer = (BYTE *)malloc(CALLBACK_BUFFERSIZE);
    }
#else
    pInt->pCallBackBuffer = (BYTE *)malloc(CALLBACK_BUFFERSIZE);
#endif
    if (NULL == pInt->pCallBackBuffer)
    {
        WMADebugMessage( " WMAFileDecodeInitEx - fail 10\n"); 
        return cWMA_Internal;
    }

    WMADebugMessage( " WMAFileDecodeInitEx - PASS\n"); 
    return cWMA_NoErr;
}

tWMAFileStatus WMAFileIsLosslessWMA (tHWMAFileState hstate)
{
    tWMAFileStateInternal *pInt;
    WMAERR wmarc = WMAERR_OK;
    WMARESULT wmar = WMA_OK;
    
    pInt = (tWMAFileStateInternal*) hstate;

    if (pInt == NULL)
        return cWMA_BadArgument;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif
    // Check if it is WMA Lossless
    if ((pInt->hdr_parse.wFormatTag != 0x163) || ((pInt->hdr_parse.nEncodeOpt & ENCOPT3_PURE_LOSSLESS) == 0))
    {           
        // assert(pInt->hdr_parse.nEncodeOpt & ENCOPT3_PURE_LOSSLESS);
        return cWMA_Failed;
    }    
    return cWMA_NoErr;
}

#ifdef ISBADPTR
#define CHECK_STATEPTR(pInt, retVal) \
if (!pInt || IsBadReadPtr(pInt, sizeof(tWMAFileHdrState))) \
    return retVal;
#else
#define CHECK_STATEPTR(pInt, retVal) \
if (!pInt) \
    return retVal;
#endif

#if !defined(USE_SPDTX)

int WMAFileLBRVersion(tHWMAFileState hstate)
{
    tWMAFileStateInternal *pInt = (tWMAFileStateInternal*)hstate;
    CHECK_STATEPTR(pInt, -1);

    return prvGetPlusVersion(pInt->hdr_parse.nAdvancedEncodeOpt);
}

int WMAFileNoiseSubUsed(tHWMAFileState hstate)
{
    tWMAFileStateInternal *pInt = (tWMAFileStateInternal*)hstate;
    CHECK_STATEPTR(pInt, -1);

    return audecGetNoiseSubUsed(pInt->hWMA);
}

#endif

/* ===========================================================================
 * WMAFileDecodeInfo
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileDecodeInfo(tHWMAFileState hstate,
                  tWMAFileHeader *hdr)
{
    tWMAFileStateInternal *pInt; 
    pInt = (tWMAFileStateInternal*) hstate;

    if(pInt == NULL || hdr == NULL)
        return cWMA_BadArgument;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
    if (IsBadWritePtr(hdr, sizeof(tWMAFileHeader)))
        return cWMA_BadArgument;
#endif


    /* Fill in the structure */

    hdr->version      = (tWMAFileVersion)pInt->hdr_parse.nVersion;
    hdr->num_channels = (tWMAFileChannels)pInt->hdr_parse.nChannels;

    hdr->sample_rate = pInt->hdr_parse.nSamplesPerSec;
    hdr->duration            = pInt->hdr_parse.msDuration;
    hdr->packet_size         = pInt->hdr_parse.cbPacketSize;
    hdr->first_packet_offset = pInt->hdr_parse.cbFirstPacketOffset;
    hdr->last_packet_offset  = pInt->hdr_parse.cbLastPacketOffset;

    hdr->has_DRM             = (tWMA_U32)pInt->bHasDRM;

    hdr->LicenseLength       = (tWMA_U32)pInt->hdr_parse.m_dwLicenseLen;

    hdr->bitrate             = pInt->hdr_parse.nAvgBytesPerSec*8;

    // Added in V9
    hdr->pcm_format_tag        = pInt->hdr_parse.wPCMFormatTag;
    
    hdr->bits_per_sample       = pInt->hdr_parse.wBitsPerSample;
    
    hdr->valid_bits_per_sample = pInt->hdr_parse.wValidBitsPerSample;
    
    hdr->channel_mask          = pInt->hdr_parse.dwChannelMask;
    
    hdr->subformat_data1       = pInt->hdr_parse.SubFormat.Data1;
    
    hdr->subformat_data2       = pInt->hdr_parse.SubFormat.Data2;
    
    hdr->subformat_data3       = pInt->hdr_parse.SubFormat.Data3;
    
    memcpy(hdr->subformat_data4, pInt->hdr_parse.SubFormat.Data4, 8);
    
    return cWMA_NoErr;
}


/* ===========================================================================
 * WMAFileContentDesc
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileContentDesc (tHWMAFileState hstate, const tWMAFileContDesc **ppDesc)
{
    tWMAFileStateInternal *pInt; 
    DWORD cbOffset =0;
    DWORD cbWanted =0;
    DWORD cbActual =0;

    pInt = (tWMAFileStateInternal*) hstate;
    if(pInt == NULL || ppDesc == NULL)
        return cWMA_BadArgument;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif

    if(pInt->hdr_parse.m_pDesc == NULL) {
        *ppDesc = NULL;
    }
    else {
        *ppDesc  = pInt->hdr_parse.m_pDesc;
    }

    return cWMA_NoErr;
}

/* ===========================================================================
 * WMAFileExtendedContentDesc
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileExtendedContentDesc (tHWMAFileState hstate, const tWMAExtendedContentDesc **pECDesc)
{
    tWMAFileStateInternal *pInt;

    pInt = (tWMAFileStateInternal*) hstate;
    if((pInt == NULL) || (pECDesc == NULL))
        return cWMA_BadArgument;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif


    if(pInt->hdr_parse.m_pECDesc == NULL) {
        *pECDesc = NULL;
    }
    else {
        *pECDesc = pInt->hdr_parse.m_pECDesc;
    }

    return cWMA_NoErr;
}

/******************************************************************************/

/* ===========================================================================
 * WMAGetNumberOfMarkers
--------------------------------------------------------------------------- */
int WMAGetNumberOfMarkers(tWMAFileHdrState *state)
{
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)state;

    if(pInt == NULL)
    {
        return 0;
    }

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif


    if (WMAERR_OK == WMA_GetMarkerObject(pInt, -1)) // filled up pInt->m_dwMarkerNum 
    {
        return pInt->m_dwMarkerNum;
    } else {
        return 0;  
    }
}


/* ===========================================================================
 * WMAGetMarker
--------------------------------------------------------------------------- */
tWMAFileStatus  WMAGetMarker(tWMAFileHdrState *state, int iIndex, MarkerEntry *pEntry)
{
    tWMAFileHdrStateInternal *pInt = (tWMAFileHdrStateInternal *)state;

    if(pInt == NULL || pEntry == NULL)
    {
       return cWMA_BadArgument; 
    }
 
#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
    if (IsBadWritePtr(pEntry, sizeof(MarkerEntry)))
        return cWMA_BadArgument;
#endif
 
    
    if (WMAERR_OK != WMA_GetMarkerObject(pInt, -1)) // filled up pInt->m_dwMarkerNum
    {
        return cWMA_Failed;  
    } 

    if ( pInt->m_dwMarkerNum == 0 ) 
    {
        return cWMA_Failed;  
    } 

    pInt->m_pMarker = pEntry;

    if ( iIndex >=0 &&  iIndex < (int) pInt->m_dwMarkerNum )
    {
        if (WMAERR_OK == WMA_GetMarkerObject(pInt, iIndex))
        {
            return cWMA_NoErr;
        }
        else
        {
            return cWMA_Failed;
        }

    }
    else 
    {

        return cWMA_Failed; 
        
    }
}

/* ===========================================================================
 * WMAFormatDate
--------------------------------------------------------------------------- */
void WMAFormatDate( tWMADateParams LicDate, BYTE *pbuffer )
{
    pbuffer[0] = (BYTE)(LicDate.year /100);
    pbuffer[1] = (BYTE)(LicDate.year %100);
    pbuffer[2] = (BYTE)(LicDate.month);
    pbuffer[3] = (BYTE)(LicDate.day);
}
/* ===========================================================================
 * WMAFileLicenseInit
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileLicenseInit (tHWMAFileState hstate, tWMAFileLicParams *lic_params, tWMA_U32 rights, tWMADateParams currentDate)
{
    tWMAFileStateInternal *pInt; 

    pInt = (tWMAFileStateInternal*) hstate;

    if(pInt == NULL || lic_params == NULL)
        return cWMA_BadArgument;

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
    if (IsBadReadPtr(lic_params, sizeof(tWMAFileLicParams)))
        return cWMA_BadArgument;
#endif
 
#ifdef WMDRM_PORTABLE
    if( pInt->bHasJanusDRM )
    {
        return( cWMA_NoErr );
    }
#endif

    if(pInt->bHasDRM)
    {

#ifdef WMAAPI_NO_DRM

        return cWMA_DRMUnsupported;

#else  /* WMAAPI_NO_DRM */

        HRESULT hr;
        PMLICENSE pmlic;
        DWORD dwRight;

        BYTE *pData;
        DWORD dwOffset;
        DWORD dwActual;
        BYTE dateArray[DATE_LEN];

        /* set up for InitDecrypt */

        memset (&pmlic, 0, sizeof(pmlic));
        memcpy (pmlic.ld.KID, (char *)pInt->hdr_parse.pbKeyID,
               strlen((const char *)pInt->hdr_parse.pbKeyID) + 1);
        if (currentDate.day) { 
            WMAFormatDate(currentDate,dateArray);
            memcpy (pmlic.ld.appSec, APPSEC_1100, APPSEC_LEN);
            memcpy (pmlic.ld.expiryDate, dateArray, DATE_LEN);
        }
        else {
            memcpy (pmlic.ld.appSec, APPSEC_1000, APPSEC_LEN);
            memset(pmlic.ld.expiryDate, 0, DATE_LEN);
        }


        dwRight = rights;
        //NOTE: This statement masks out any unwanted set bit in the user supplied flag
        //Any new rights added to the API will have to be added here as well
        dwRight &= (WMA_NONSDMI_LIC | WMA_SDMI_LIC | WMA_BURNCD_LIC); 

        memcpy (pmlic.ld.rights, (BYTE *)&dwRight, RIGHTS_LEN);

        dwOffset = 0;
        dwActual = WMA_MAX_DATA_REQUESTED;
 
        pData = pInt->hdr_parse.m_pLicData;
        dwActual = pInt->hdr_parse.m_dwLicenseLen;

        //NOTE: The dwOffset and dwAcual were suppose to return the number of bytes still to be supplied for 
        // complete license if we do not supply entire license at one time. now they are not needed anymore
        //as we supply the entire license at once. So no checking on them
        hr = CDrmPD_InitDecrypt(pInt->pDRM_state,
                                    &pmlic,
                                    lic_params->pPMID,
                                    lic_params->cbPMID,
                                    pData,
                                    &dwOffset,
                                    &dwActual);



        if (hr == S_OK)
            return cWMA_NoErr;
#endif /* WMAAPI_NO_DRM */
    }

    return cWMA_DRMFailed;
}

tWMA_U64 WMAFileHeaderSize (tHWMAFileState hstate)
{
    tWMAFileStateInternal *pInt;
    pInt = (tWMAFileStateInternal*) hstate;
    return (pInt->hdr_parse.cbHeader);
}

tWMAFileStatus WMAFileSeek (tHWMAFileState hstate, tWMA_U32 msSeek, tWMA_U32 *pmsActual, tWMA_U64 *pBytes)
{    
    tWMA_U32 iPacket = 0;
    tWMAFileStatus rc;
    tWMAFileStateInternal *pInt;
    pInt = (tWMAFileStateInternal*) hstate;

    rc = WMAFileSeekBase (hstate, & msSeek, & iPacket, pmsActual, WMAB_FALSE, WMAB_FALSE);
    *pBytes = pInt->hdr_parse.nextPacketOffset;

    return rc;
}

/* ===========================================================================
 * WMAFileSeek
--------------------------------------------------------------------------- */
tWMAFileStatus WMAFileSeekBase(tHWMAFileState hstate, tWMA_U32 * pmsSeek, 
                               tWMA_U32 * piPacket, tWMA_U32 * pmsActual,
                               tWMA_Bool fProWMAEncoder, tWMA_Bool fSeekToPacket)
{
    tWMA_U32 msSeek = *pmsSeek;
    tWMAFileStateInternal *pInt; 
    tWMA_U32 nPacket = *piPacket;
    WMARESULT wmar = WMA_OK;
    tWMA_U8 bDone =0;
    tWMA_U32 i =0;
    tWMA_U32 msPacketDuration = 0;
    tWMA_U32 msDiff=0;
    tWMA_U8 goForward =0;  
    tWMA_U8 dwGoingForward =0;  
    tWMA_U8 dwGoingBackword =0;  
    tWMA_U8 bGotAudioPayload =0;


    pInt = (tWMAFileStateInternal*) hstate; 
    if(pInt == NULL || pmsActual == NULL )
    {
        return cWMA_BadArgument;
    }
#ifdef USE_SPDTX 
    if(pInt->hSPDTX == NULL) return cWMA_BadArgument;
#else
    if(pInt->hWMA   == NULL) return cWMA_BadArgument;
#endif

#ifdef ISBADPTR
    if (IsBadReadPtr(pInt, sizeof(tWMAFileStateInternal)))
        return cWMA_BadArgument;
#endif

    *pmsActual = 0;

    /* which packet? */

    if (fSeekToPacket != WMAB_TRUE)
    {
        nPacket = 0;
        if(pInt->hdr_parse.msDuration > 0)
        {
            /* rounding down because I want the requested time frame to be
            * played */

            if (msSeek > pInt->hdr_parse.msDuration)
                return cWMA_BadArgument;

            msPacketDuration = pInt->hdr_parse.msDuration / pInt->hdr_parse.cPackets;  
            if ( 0 != msPacketDuration )
                nPacket = msSeek / msPacketDuration;  
            else
                nPacket = 1;    //fix a bug when cPackets is faked to be very big 

            //NQF, 061800, temp fix for the seek() bug reported by Creative 
            if ((nPacket) &&( nPacket % 16 == 0 )){
                nPacket++;  
            }
        }
    }
    /* see if it's within the bounds */

    if (nPacket >= pInt->hdr_parse.cPackets) 
        nPacket = pInt->hdr_parse.cPackets -1; // Go to last packet

    /* Amit: Skip VideoPayload  Bug : if that packet doesnt contain any audio payload we should go to next packet*/

#if 1 //don't iterate, take first estimate as best guess as we don't have random access to the file
    pInt->hdr_parse.currPacketOffset = pInt->hdr_parse.cbHeader + nPacket*pInt->hdr_parse.cbPacketSize;
#else
    do
    {
        /* parse the packet and the payload header
         *
         * a bit of a duplication from WMAF_UpdateNewPayload...
         */

        pInt->hdr_parse.currPacketOffset = pInt->hdr_parse.cbHeader
                                         + nPacket*pInt->hdr_parse.cbPacketSize;

        if(WMA_ParsePacketHeader(pInt) != WMAERR_OK)
        {
            return cWMA_BadPacketHeader;
        }

        if(pInt->ppex.fEccPresent && pInt->ppex.fParityPacket)
        {
            return cWMA_BadPacketHeader;
        }

        pInt->iPayload = 0;

        for (i=0; i < pInt->ppex.cPayloads; i++ )
        {
            if(WMA_ParsePayloadHeader(pInt) != WMAERR_OK)
            {
                return cWMA_BadPacketHeader;
            }

            /* Amit: Skip VideoPayload */

            if(pInt->payload.bStreamId == pInt->hdr_parse.wAudioStreamId)
            {
                *pmsActual = pInt->payload.msObjectPres - pInt->hdr_parse.msPreroll;
                bGotAudioPayload =1;
                break;
            } 
            pInt->iPayload++;
        }
        if (bGotAudioPayload)
        {
            if (fSeekToPacket == WMAB_TRUE)
            {
                bDone = 1;
                break;
            }
            bGotAudioPayload =0;
            if ((dwGoingBackword == 1) &&(dwGoingForward == 1))
                bDone=1;

            if ( *pmsActual > msSeek )
            {
                msDiff = *pmsActual - msSeek;  
                goForward = 0;
                dwGoingForward = 1;  
            } 
            else 
            {
                msDiff =  msSeek - *pmsActual;  
                goForward = 1; 
                dwGoingBackword = 1; 
            }
        }
        else
        {
            if (fSeekToPacket == WMAB_TRUE)
            {
                goForward = 0;
            }

            if (goForward==0)
            {
                if (nPacket > 0)
                {
                    nPacket--;
                }
                else
                {
                    goForward = 1;
                    dwGoingBackword = 1;  
                    nPacket++;
                }
            }
            else
            {
                nPacket++;
            }
            
            continue;
        }

        if (fProWMAEncoder == WMAB_TRUE)
        {
            if ((msDiff == 0) || (bDone == 1))
                goto lexit;
            if (nPacket == 0)
                goto lexit;
        }
        else
        {
            if ( (msDiff <  5 * msPacketDuration / 4) /*|| ((dwGoingBackword == 1) &&(dwGoingForward == 1)) */)
            bDone = 1;  
 
            if ( (nPacket == 0) || (bDone && nPacket % 16 != 0)) 
            {
                goto lexit;
            }
        }

        if (goForward) 
            nPacket++;  
        else 
            nPacket--;  

    
    }while((nPacket < pInt->hdr_parse.cPackets));
    
    if (bDone !=1)
    {
        nPacket = pInt->hdr_parse.cPackets;
        *pmsActual = pInt->hdr_parse.msDuration;
    }

lexit:
#endif

    /* reset the states */
#ifdef USE_SPDTX
    assert(!"don't have a reset.\n");
#else
    wmar = audecReset (pInt->hWMA);
    pInt->audecState = audecStateInput;
#endif

    if (wmar != WMA_OK)
        return cWMA_Failed;
    pInt->hdr_parse.nextPacketOffset = pInt->hdr_parse.cbHeader
                                     + nPacket*pInt->hdr_parse.cbPacketSize;
    pInt->parse_state = csWMA_NewAsfPacket;
    //wchen: it seems after seek decodeStatus won't be called until this guy is 2
//    pInt->bDecInWaitState = 2; 
    *pmsSeek = *pmsActual;
    *piPacket = nPacket;
    return cWMA_NoErr;
}

#if 0
typedef struct WmaGetDataParam
{
    U32  m_dwUser;
    Bool m_fTimeIsValid;
    I64  m_iTime;
} WMAFileGetInputParam 
#endif

/****************************************************************************/
WMARESULT WMAFileGetInput (tWMAFileStateInternal *pInt, U8 **ppBuffer, U32 *pcbBuffer, WMAFileGetInputParam* pgdParam)
{

    tWMA_U32 num_bytes = WMA_MAX_DATA_REQUESTED;
    tWMA_U32 cbActual =0;
    tWMA_U32 cbWanted =0;
    BYTE *pbuff = NULL;
    tWMAFileStatus rc;
    tWMAParseState parse_state;

#ifndef WMAAPI_NO_DRM
    HRESULT hr;
#endif // WMAAPI_NO_DRM

    pgdParam->m_fTimeIsValid = 0;

    if(pInt == NULL || ppBuffer == NULL || pcbBuffer == NULL)
    {
        if(ppBuffer != NULL)
        {
            *ppBuffer = NULL;
        }
        if(pcbBuffer != NULL)
        {
            *pcbBuffer = 0;
        }

        return WMA_E_INVALIDARG;
    }


    *ppBuffer = NULL;
    *pcbBuffer = 0;

    /* If we used up the current payload, try to get the
     * next one.
     */
    
    // Added by Amit to take care of compressed payloads
    do
    {
        switch (pInt->payload.bIsCompressedPayload)
        {


        case 1:
            {
                do
                {
                    switch (pInt->payload.bSubPayloadState)
                    {
                    case 1: // Compressed payload just started
                        cbWanted = 1; //to read subpayload length
                        cbActual = WMAFileCBGetData ((tHWMAFileState *)pInt, pInt->cbPayloadOffset, cbWanted, &pbuff);
                        if ((cbActual != cbWanted) || NULL == pbuff)
                                return WMA_E_NO_MORE_SRCDATA;

                        
                        pInt->cbPayloadOffset += cbWanted;
                        pInt->bBlockStart = TRUE;
                        pInt->cbBlockLeft = pInt->hdr_parse.nBlockAlign;
                        pInt->payload.wSubCount =0;

                        pInt->payload.bNextSubPayloadSize = pbuff[0];
                        pInt->payload.wSubpayloadLeft = pInt->payload.bNextSubPayloadSize;
                        if (pInt->payload.wSubpayloadLeft > 0)
                            pInt->payload.wSubpayloadLeft -= (WORD)pInt->cbBlockLeft;

                        if( pInt->payload.wTotalDataBytes > pInt->payload.bNextSubPayloadSize)
                            pInt->payload.wBytesRead = pInt->payload.bNextSubPayloadSize+1;
                        else if ( pInt->payload.wTotalDataBytes == pInt->payload.bNextSubPayloadSize)
                            pInt->payload.wBytesRead = pInt->payload.bNextSubPayloadSize;

                        pInt->payload.bSubPayloadState = 2;
                        break;
                    case 2: // Subpayload started
                        if (pInt->cbBlockLeft == 0 && pInt->payload.wSubpayloadLeft == 0)
                        {
                            pInt->payload.bSubPayloadState =3;
                            break;
                        }
                        else
                        {
                            if(pInt->cbBlockLeft == 0)
                            {
                                if (/*pInt->cbPayloadLeft*/pInt->payload.wSubpayloadLeft == 0) /* done with the file */
                                    return WMA_S_NEWPACKET;

                                if (pInt->payload.wSubpayloadLeft > 0)
                                    pInt->payload.wSubpayloadLeft -= (WORD) pInt->hdr_parse.nBlockAlign;
                                pInt->bBlockStart = TRUE;
                                pInt->cbBlockLeft = pInt->hdr_parse.nBlockAlign;
                            }
                            if(num_bytes > pInt->cbBlockLeft)
                                num_bytes = pInt->cbBlockLeft;

                            *pcbBuffer = (unsigned int)WMAFileCBGetData((tHWMAFileState *)pInt,
                                                                        pInt->cbPayloadOffset, num_bytes, ppBuffer);
                            if (*pcbBuffer != num_bytes )
                                return WMA_E_NO_MORE_SRCDATA;


#ifdef ISBADPTR
                            if (IsBadReadPtr(ppBuffer, *pcbBuffer))
                                return WMA_E_NO_MORE_SRCDATA;
#endif

#ifdef WMDRM_NETWORK
                            if( pInt->bHasWMDRMNetworkDRM )
                            {
                                //
                                // WMDRM-ND files shouldn't have compressed
                                // payloads, because there is nowhere to put
                                // the sample ID.
                                //
                                *ppBuffer = NULL;
                                *pcbBuffer = 0;
                                return WMA_S_NEWPACKET;
                            }
#endif

                            if ((*pcbBuffer <=CALLBACK_BUFFERSIZE) && ppBuffer && *ppBuffer)
                            {
                                memcpy(pInt->pCallBackBuffer, *ppBuffer,*pcbBuffer);
                                *ppBuffer = pInt->pCallBackBuffer;
                            }
                            else
                            {
                                *ppBuffer = NULL;
                                return WMA_S_NEWPACKET;
                            
                            }

                            pInt->cbPayloadOffset+=*pcbBuffer;
                            //pInt->payload.wSubpayloadLeft -= *pcbBuffer;
                            pInt->cbBlockLeft     -= *pcbBuffer;
                
#ifdef WMDRM_PORTABLE
                            if (pInt->bHasJanusDRM)
                            {
                                hr = DRM_MGR_Decrypt( 
                                    pInt->pJanusDecryptContext,
                                    *ppBuffer,
                                    *pcbBuffer);
                                if( hr != S_OK )
                                {
                                    *ppBuffer = NULL;
                                    *pcbBuffer = 0;
                                    return WMA_S_NEWPACKET;
                                }
                            }
#endif // WMDRM_PORTABLE

                            if (pInt->bHasDRM)
                            {
#ifdef WMAAPI_NO_DRM
                                return WMA_S_NEWPACKET;
#else  /* WMAAPI_NO_DRM */
                                hr = CDrmPD_Decrypt (pInt->pDRM_state, *ppBuffer, *pcbBuffer);
                                if (hr != S_OK)
                                {
#ifdef LOCAL_DEBUG
                                    SerialPrintf("++ WMARawDecCBGetData: CDrmPD_Decrypt failed (0x%08x).\n\r", hr);
#endif /* LOCAL_DEBUG */
                                    *ppBuffer = NULL;
                                    *pcbBuffer = 0;
                                    return WMA_S_NEWPACKET;
                                }

#endif /* WMAAPI_NO_DRM */

                            }

                            if (pInt->bBlockStart) 
                            {
                                if (pInt->payload.wSubpayloadLeft == pInt->payload.bNextSubPayloadSize - pInt->hdr_parse.nBlockAlign)
                                {
                                    pgdParam->m_fTimeIsValid = 1;
                                    pgdParam->m_iTime = 10000 * (tWMA_I64)( (pInt->payload.msObjectPres - pInt->hdr_parse.msPreroll) + pInt->payload.dwDeltaTime * pInt->payload.wSubCount);
                                    pInt->payload.wSubCount++;
                                }
                                
                                pInt->bBlockStart = FALSE;
                                return WMA_S_NEWPACKET;
                            }

                            return WMA_OK;
                        }

                        break;
                    case 3: // Subpayload finished
                        if ( pInt->payload.wTotalDataBytes > pInt->payload.wBytesRead)
                        { // there are payloads to decode
                            cbWanted = 1; //to read subpayload length
                            cbActual = WMAFileCBGetData((tHWMAFileState *)pInt,
                                                                pInt->cbPayloadOffset, cbWanted, &pbuff);
                            if ((cbActual != cbWanted) || NULL == pbuff)
                                    return WMA_E_NO_MORE_SRCDATA;
                            
                            pInt->cbPayloadOffset+=cbWanted;
                            pInt->bBlockStart     = TRUE;
                            pInt->cbBlockLeft     = pInt->hdr_parse.nBlockAlign;

                    
                            pInt->payload.bNextSubPayloadSize = pbuff[0];
                            pInt->payload.wSubpayloadLeft = pInt->payload.bNextSubPayloadSize;
                            if (pInt->payload.wSubpayloadLeft > 0)
                                pInt->payload.wSubpayloadLeft -= (WORD)pInt->cbBlockLeft;
                            pInt->payload.wBytesRead+=pInt->payload.bNextSubPayloadSize+1;
                            pInt->payload.bSubPayloadState =2;                
                        }
                        else
                            pInt->payload.bSubPayloadState =4; // all subpayloads finished
                        break;

                    case 4: // All Subpayloads finished

                        parse_state = pInt->parse_state;
                        pInt->payload.bSubPayloadState =0;
                        pInt->cbPayloadLeft =0;
                        pInt->payload.bIsCompressedPayload =0;

                        pInt->parse_state = csWMA_DecodePayloadEnd;
                        rc = WMAF_UpdateNewPayload(pInt);
                        if (rc == cWMA_NoMoreDataThisTime)
                        {
                            *pcbBuffer = 0;
                            return WMA_OK;
                        }

                        pInt->parse_state = parse_state;  //restore 
                        if((rc != cWMA_NoErr)) 
                            return WMA_S_NEWPACKET;
                        break;
                    default:
                        return WMA_S_NEWPACKET;

                    }
                } while(1);

                break;
            }          
        default :
            {
                if(pInt->cbBlockLeft == 0 && pInt->cbPayloadLeft == 0)
                {
                    tWMAFileStatus rc1;
                    tWMAParseState parse_state1;

                    parse_state1 = pInt->parse_state;

                    pInt->parse_state = csWMA_DecodePayloadEnd;
                    rc1 = WMAF_UpdateNewPayload(pInt);
                    if (rc1 == cWMA_NoMoreDataThisTime)
                    {
                        *pcbBuffer = 0;
                        return WMA_OK;
                    }
                    pInt->parse_state = parse_state1; /* restore */
                    
                    if (pInt->payload.bIsCompressedPayload ==1)
                        break;
                    
                    if (cWMA_NoMoreFrames == rc1)
                    {
                        *pcbBuffer = 0;
                        return WMA_E_NO_MORE_SRCDATA;
                    }
                    
                    if(rc1 != cWMA_NoErr)
                        return WMA_S_NEWPACKET;
                }

                /* return as much as we currently have left */

                if(pInt->cbBlockLeft == 0)
                {
                    if(pInt->cbPayloadLeft == 0)
                    {
                        /* done with the file */
                        return WMA_S_NEWPACKET;
                    }

                    pInt->cbPayloadLeft -= pInt->hdr_parse.nBlockAlign;
                    pInt->bBlockStart = TRUE;
                    pInt->cbBlockLeft = pInt->hdr_parse.nBlockAlign;
                }
                if(num_bytes > pInt->cbBlockLeft)
                    num_bytes = pInt->cbBlockLeft;

                *pcbBuffer = (unsigned int)WMAFileCBGetData((tHWMAFileState *)pInt,
                                                            pInt->cbPayloadOffset, num_bytes, ppBuffer);

                if (*pcbBuffer != num_bytes )
                    return WMA_E_NO_MORE_SRCDATA;
#ifdef ISBADPTR
                if (IsBadReadPtr(ppBuffer, *pcbBuffer))
                    return WMA_E_NO_MORE_SRCDATA;
#endif

#ifdef WMDRM_NETWORK
                if( pInt->bHasWMDRMNetworkDRM )
                {
                    if( pInt->payload.cbPayloadSize > 
                        pInt->hdr_parse.cbAudioSize )
                    {
                        //
                        // Hmm... this payload is bigger than expected. There
                        // must be a problem with this file.
                        //
                        return WMA_E_FAIL;
                    }

                    if( ( pInt->payload.cbPayloadSize -
                          pInt->cbBlockLeft -
                          pInt->cbPayloadLeft +
                          *pcbBuffer ) >
                        pInt->hdr_parse.cbAudioSize )
                    {
                        //
                        // Uhoh... we were going to overwrite our buffer...
                        // there must be something wrong with the file.
                        //
                        return WMA_E_FAIL;
                    }

                    memcpy( pInt->pCallBackBuffer + 
                            pInt->payload.cbPayloadSize -
                            pInt->cbBlockLeft -
                            pInt->cbPayloadLeft,
                            *ppBuffer,
                            *pcbBuffer );
                }
                else
#endif
                if (*pcbBuffer <=CALLBACK_BUFFERSIZE)
                {
                    memcpy(pInt->pCallBackBuffer, *ppBuffer,*pcbBuffer);
                    *ppBuffer = pInt->pCallBackBuffer;
                }
                else
                {
                    *ppBuffer = NULL;
                    return WMA_S_NEWPACKET;
                
                }

                pInt->cbPayloadOffset += *pcbBuffer;
                pInt->cbBlockLeft     -= *pcbBuffer;

                /* DRM decryption if necessary */

#ifdef WMDRM_PORTABLE
                if( pInt->bHasJanusDRM )
                {
                    hr = DRM_MGR_Decrypt( pInt->pJanusDecryptContext,
                                          *ppBuffer,
                                          *pcbBuffer);
                    if( hr != S_OK )
                    {
                        *ppBuffer = NULL;
                        *pcbBuffer = 0;
                        return WMA_S_NEWPACKET;
                    }
                }
#endif // WMDRM_PORTABLE

                if (pInt->bHasDRM)
                {

#ifdef WMAAPI_NO_DRM
                    return WMA_S_NEWPACKET;
#else  /* WMAAPI_NO_DRM */

                    hr = CDrmPD_Decrypt (pInt->pDRM_state, *ppBuffer, *pcbBuffer);
                    if (hr != S_OK) {
#ifdef LOCAL_DEBUG
                        SerialPrintf("++ WMARawDecCBGetData: CDrmPD_Decrypt failed (0x%08x).\n\r", hr);
#endif /* LOCAL_DEBUG */
                        *ppBuffer = NULL;
                        *pcbBuffer = 0;
                        return WMA_S_NEWPACKET;
                    }

#endif /* WMAAPI_NO_DRM */

                }

#ifdef WMDRM_NETWORK
                if( pInt->bHasWMDRMNetworkDRM )
                {
                    if( pInt->cbBlockLeft > 0 || pInt->cbPayloadLeft > 0 )
                    {
                        //
                        // We haven't accumulated the whole payload yet, so we
                        // can't decrypt yet. Don't return anything.
                        //
                        *ppBuffer = NULL;
                        *pcbBuffer = 0;
                    }
                    else
                    {
                        DRM_RESULT dr;
                        dr = DrmAesCtrProcessData( 
                            pInt->pWMDRMNetworkKey,
                            pInt->pCallBackBuffer,
                            pInt->payload.cbPayloadSize,
                           &pInt->qwWMDRMNetworkSampleID );
                        if( DRM_FAILED( dr ) )
                        {
                            *ppBuffer = NULL;
                            *pcbBuffer = 0;
                            return WMA_S_NEWPACKET;
                        }

                        *ppBuffer = pInt->pCallBackBuffer;
                        *pcbBuffer = pInt->payload.cbPayloadSize;
                    }
                }
#endif

                if (pInt->bBlockStart) {
                    pInt->bBlockStart = FALSE;
                    //hopefully the following test if the beginning of a payload
                    if (pInt->cbPayloadLeft == pInt->payload.cbPayloadSize - pInt->hdr_parse.nBlockAlign)
                    {
                        pgdParam->m_fTimeIsValid = 1;
                        pgdParam->m_iTime = 10000 * (tWMA_I64) (pInt->payload.msObjectPres - pInt->hdr_parse.msPreroll);
                    }
#ifdef WMDRM_NETWORK
                    if( !pInt->bHasWMDRMNetworkDRM )
                    {
                        return WMA_S_NEWPACKET;
                    }
#else
                    return WMA_S_NEWPACKET;
#endif
                }

#ifdef WMDRM_NETWORK
                if( pInt->bHasWMDRMNetworkDRM )
                {
                    if( NULL == *ppBuffer )
                    {
                        //
                        // We haven't accumulated enough data yet to perform
                        // a WMDRM-ND decryption. Go ahead and break here; this
                        // will cause the loop to run again, which will
                        // fetch more data.
                        //
                        break;
                    }
                    else
                    {
                        return WMA_S_NEWPACKET;
                    }
                }
#endif
                return WMA_OK;
            }
        }


    }while(1);
    
    return WMA_OK;
}
