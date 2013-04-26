//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    MsAudioDec.cpp

Abstract:

    Implementation of top level functions of CAudioObjectDecoder.

Author:

    Wei-ge Chen (wchen) 14-July-1998

Revision History:


*************************************************************************/


#if defined(_WMA_COUNT_CPU_CYCLES_IF_REGKEY_) || defined(WIN32)
#ifdef _XBOX
#include <xtl.h>
#else // _XBOX
#include <windows.h>
#endif // !_XBOX
#endif
#include "msaudiodec.h"
#include "macros.h"
#include "drccommon.h"
#if defined(BUILD_WMAPROLBRV2)
#include "chexpro.h"
#endif
//#include "wmsdecfunc.h"

#ifdef TEST_VRHEADPHONE
  #include "pcmfmt.h"
  #include "..\..\..\vrheadphone\AVRHPhoneC.h"
#endif //TEST_VRHEADPHONE

#if defined(WMA_TARGET_X86) && !defined (DISABLE_OPT)
  #include "cpudetect.h"
#endif

#if defined (TEST_PEAKRATE)
extern unsigned int g_iLargestFrame;
extern unsigned int g_cSamplesPerFrame;
#endif // TEST_PEAKRATE

#include "AutoProfile.h" 

#if defined(_DEBUG) || defined(BITRATE_REPORT)
extern Int g_cBitGet = 0;
#endif  // _DEBUG || BITRATE_REPORT

#define NEW_DRC_DECODE

#ifndef WMA_DECPK_BUILD         //temporarily disable channel boosting for PK release to match up v9
#define BOOST_CHANFLDDN_POWER     
#endif

#ifdef _WMA_COUNT_CPU_CYCLES_IF_REGKEY_
#include <time.h>

#define CYCLE_DIVISOR 1000

#define CCS_START(fnID) WMACCSStart(&paudec->m_CCSStruct, fnID)
#define CCS_END(fnID) WMACCSEnd(&paudec->m_CCSStruct, fnID)
#define CCS_INIT() WMACCSInit(&paudec->m_CCSStruct, pWMAFormat)
#define CCS_CLOSE() WMACCSClose(&paudec->m_CCSStruct)
#define CCS_FRM_BDRY() WMACCSFrmBdry(&paudec->m_CCSStruct)

#define HrTmrGet ReadTimeStampCounter

unsigned short __cdecl _byteswap_ushort(unsigned short);
#pragma intrinsic(_byteswap_ushort)

void WMACCSStart(CCSStruct* pccs, CCSID id) {
    CCSPerFunStruct* p = &(pccs->fns[id]);
    if (!pccs->fEnabled) return;
    assert(!p->fIn); p->fIn = WMAB_TRUE;
    pccs->fDirty = WMAB_TRUE;

    p->iCurStartCycles = HrTmrGet();
}

void WMACCSEnd(CCSStruct* pccs, CCSID id) {
    CCSPerFunStruct* p = &(pccs->fns[id]);
    if (!pccs->fEnabled) return;
    assert(p->fIn); p->fIn = WMAB_FALSE;

    p->iCurFrmCycles += (HrTmrGet() - p->iCurStartCycles);
}

Bool WMACCSTopLevelIndex(CCSID i) {
    return (i == CCS_audecDecode) || (i == CCS_audecGetPCM);
}

void WMACCSFrmBdry(CCSStruct* pccs) {
    int i;
    I64 iCurFrmOverallCycles = 0;
    if (!pccs->fEnabled || !pccs->fDirty) return;

    for (i = 0; i < CCS_NUM_FUNS; i++) {
        CCSPerFunStruct* p = &(pccs->fns[i]);
        assert(!p->fIn); // frm bdry in the middle of a start/end pair ?

        if (p->iCurFrmCycles > p->iMaxFrmCycles) {
            p->iMaxFrmCycles = p->iCurFrmCycles;
            p->iMaxPos = pccs->iFrmCount;
        }
        if (WMACCSTopLevelIndex(i))
            iCurFrmOverallCycles += p->iCurFrmCycles;
        p->iTotalCycles += p->iCurFrmCycles;
        p->iCurFrmCycles = 0;
    }

    if (iCurFrmOverallCycles > pccs->iMaxOverallFrmCycles) {
        pccs->iMaxOverallFrmCycles = iCurFrmOverallCycles;
        pccs->iOverallMaxPos = pccs->iFrmCount;
    }
    pccs->iFrmCount++;
}

void WMACCSInit(CCSStruct* pccs, WMAFormat* pFormat) {
    HKEY hKey;
    ZeroMemory(pccs, sizeof(*pccs));
    if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Scrunch"), &hKey)) {
    DWORD dwType, dwVal, cbVal = sizeof(dwVal);
        if (ERROR_SUCCESS == RegQueryValueEx(hKey, TEXT("Count Cycles"), 0, &dwType, (BYTE*)&dwVal, &cbVal)) {
            if ((sizeof(dwVal) == cbVal) && (dwVal)) {
                memcpy(&pccs->Format, pFormat, sizeof(pccs->Format));
                pccs->fEnabled = WMAB_TRUE;
            }
        }
    }
}
     
void WMACCSClose(CCSStruct* pccs) {
    FILE* fp;
    I64 iTotalOverallCycles = 0;
    int i;
    if (!pccs->fEnabled || !pccs->fDirty) return;

    WMACCSFrmBdry(pccs);

    for (i = 0; i < CCS_NUM_FUNS; i++) {
        CCSPerFunStruct* p = &(pccs->fns[i]);
        assert(!p->fIn); // close in the middle of a start/end pair ?
        assert(!p->iCurFrmCycles); // close in the middle of a frame ?

        if (WMACCSTopLevelIndex(i))
            iTotalOverallCycles += p->iTotalCycles;
    }

    fp = FOPEN("c:\\CountCyclesWMADecLog.txt", "at");
    if (fp) {
        time_t t;
        time(&t);
        WMAFprintf(fp,"# wFormatTag=0x%04hX %d bps: %d %hd-byte packets decoded at ",
                pccs->Format.wFormatTag,
                pccs->Format.nAvgBytesPerSec * 8,
                pccs->iFrmCount,
                (int)pccs->Format.nBlockAlign);
        WMAFprintf(fp,"%s", ctime(&t));
        WMAFprintf(fp,"Decode: avg=%d, max=%d @%d;  GetPCM: avg=%d, max=%d @%d;  Overall: avg=%d, max=%d @%d\n",
                (int)(pccs->fns[CCS_audecDecode].iTotalCycles / pccs->iFrmCount / CYCLE_DIVISOR),
                (int)(pccs->fns[CCS_audecDecode].iMaxFrmCycles / CYCLE_DIVISOR),
                pccs->fns[CCS_audecDecode].iMaxPos,
                (int)(pccs->fns[CCS_audecGetPCM].iTotalCycles / pccs->iFrmCount / CYCLE_DIVISOR),
                (int)(pccs->fns[CCS_audecGetPCM].iMaxFrmCycles / CYCLE_DIVISOR),
                pccs->fns[CCS_audecGetPCM].iMaxPos,
                (int)(iTotalOverallCycles / pccs->iFrmCount / CYCLE_DIVISOR),
                (int)(pccs->iMaxOverallFrmCycles / CYCLE_DIVISOR),
                pccs->iOverallMaxPos);
        FCLOSE(fp);
    }
}

#else

#define CCS_START(fnID)
#define CCS_END(fnID)
#define CCS_INIT()
#define CCS_CLOSE()
#define CCS_FRM_BDRY()

#endif


#if 0
#define audecLog(x) audecLogF x
void audecLogF (void* pUser, char* strr, ...) {
  static char s[80];
  FILE *fp;
  sprintf(s,"c:\\audec%08X.log", pUser);
  fp = FOPEN(s, "at");
  if (fp) {
    va_list ap;
    va_start (ap, strr);
    vfprintf (fp, strr, ap);
    va_end (ap);
    putc('\n', fp);
    FCLOSE(fp);
  }
}
#else
#define audecLog(x)
#endif

//#define PRINT_EFFECTIVE_BW

#ifdef PRINT_EFFECTIVE_BW
Void printEffectiveBw(CAudioObject *pau)
{
    // Identify the last non-zero coef
    Int iCoef;
    Bool fFound = 0;
    for (iCoef = pau->m_cSubbandAdjusted-1; iCoef >= 0 && !fFound; iCoef--) {
        for (iChannel = 0; iChannel < pau->m_cChannel && !fFound; iChannel++) {
            PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChannel;
            if (ppcinfo->m_rgiCoefRecon[iCoef]) {
                fFound = 1;
                break;
            }
        }
    }
    WMAFprintf(stdout, "%d %d %d %f\n", 
               paudec->pau->m_iFrameNumber ,
               paudec->m_iCurrTile,
               iCoef, (Float)iCoef/(Float)pau->m_cSubband);
    FFLUSH(stdout);
}
#endif

//***************************************************************************
// Local Function Prototypes
//***************************************************************************
Void auInitPcInfoDEC (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeTrailerBit (CAudioObjectDecoder* paudec);
WMARESULT prvReConfig (CAudioObjectDecoder* paudec);
//*****************************************************************************************
//*****************************************************************************************
//
//  Outline of decoding process - major function call graph (HighRate is >= 32kbps)
//  Decode
//  ..audecDecode
//  ....prvDecodePacket
//  ......prvDecodeData
//  ........auSaveHistoryMono
//  ........prvDecodeSubFrameHighRate
//  ..........prvDecodeFrameHeader
//  ............prvUpdateSubFrameConfig
//  ............auAdaptToSubFrameConfig
//  ............prvSetDetTable
//  ............prvReconWeightingFactor
//  ..........qstCalcQuantStep                      ; calc sub frame's quantization step size
//  ..........prvDecodeCoefficentsHighRate<float.c> ; fills rgiCoefRecon[] from bitstream with amplitude as a function of frequency
//  ..........InverseQuantizeHighRate<float.c>
//  ..........dctIV
//  ............FFT
//  ......audecGetPCM
//  ......prvDecodeInfo
//*****************************************************************************************
//*****************************************************************************************

Void prvDeletePcInfoDEC(CAudioObjectDecoder* paudec, PerChannelInfo* rgpcinfo)
{
    CAudioObject* pau = paudec->pau;
    I16 i;

    DELETE_ARRAY(paudec->m_rgpcinfoDEC);

    if (pau != NULL && rgpcinfo != NULL)
    {
        for (i = 0; i < pau->m_cChannel; i++)
        {
            PerChannelInfo* ppcinfo = rgpcinfo + i;

            if (ppcinfo) 
            {
                if (ppcinfo->m_rgsubfrmconfig) 
                {
                    DELETE_ARRAY(ppcinfo->m_rgsubfrmconfig->m_rgiSizeBuf);
                }
                DELETE_ARRAY(ppcinfo->m_rgsubfrmconfig);
            }
        }
    }
} // prvDeleteAllocPcInfoDEC


#if defined (VERIFY_PKT_SIGNATURE)
FILE* g_fpSignDec=NULL;
U8    g_unSign = 0;
I32   g_cPktBytesDone = 0;
#endif // VERIFY_PKT_SIGNATURE

#if defined (BUILD_WMAPROLBRV1)
Void prvPlusDecDelete(CAudioObjectDecoder *paudec)
{
    DELETE_ARRAY(paudec->m_pibsPlus);
    freqexDecFree(paudec);
}
#endif

//************************************************************
//        prvDecDelete: Deletes members of paudec.
//                      Does not self delete. 
//                      Currently always returns WMA_OK.
//************************************************************
WMARESULT prvDecDelete (CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau   = NULL;
    Int k;

    if (paudec == NULL)
        goto exit;
    
    pau = paudec->pau;

    prvSetOrigChannels(pau);
    
    if (pau != NULL) 
        prvDeleteChannelGrpInfo(&(paudec->m_rgChannelGrpInfo), pau->m_cChannel);


    if (paudec->m_rgrgfltChDnMixMtx)
    {
        for (k = 0; k < paudec->m_cDstChannelInChDnMixMtx; k++) 
        {
            DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtx[k]);
        }
    }
    DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtx);
    
    if (paudec->m_rgrgfltChDnMixMtxTmp)
    {
        for (k = 0; k < paudec->m_cDstChannelInChDnMixMtx; k++) 
        {
            DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtxTmp[k]);
        }
    }
    DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtxTmp);
    


#ifdef TEST_VRHEADPHONE
    TRACEWMA_EXIT (wmaResult, AVRHeadphoneDelete (&(paudec->m_pVRHPhone)));
#endif //TEST_VRHEADPHONE


    DELETE_ARRAY(paudec->m_rgpiRecon);
    DELETE_ARRAY(paudec->m_rgpcmsTemp);
    DELETE_ARRAY(paudec->m_rgpctTemp);

    prvDeletePcInfoDEC(paudec, paudec->m_rgpcinfo);
    if (NULL !=pau)
    {
        auDeletePcInfoCommon (pau, paudec->m_rgpcinfo);
        paudec->m_rgpcinfo = NULL;
    }
    
#ifdef WMA_ENTROPY_TEST
    totalPrintEntropyTest(1);
#endif    

    if (paudec->m_pLtRtDownmix) {
#if defined (BUILD_WMASTD) || defined (BUILD_WMAPRO)
        ltrtDownmixFree(paudec->m_pLtRtDownmix);
#endif
        auFree(paudec->m_pLtRtDownmix);
    }

    if (paudec->m_iLastSample) auFree(paudec->m_iLastSample);
    if (paudec->m_iPriorSample) auFree(paudec->m_iPriorSample);

    DELETE_ARRAY (paudec->m_rgfltPostProcXform);
    DELETE_ARRAY (paudec->m_rgfltPostProcXformPrev);
    DELETE_ARRAY (paudec->m_rgfltPostProcXformBlend);

#if defined (BUILD_WMAPROLBRV1)
    prvPlusDecDelete(paudec);
#endif

    if (pau != NULL) {
#ifdef BUILD_UES
        if(WMAB_TRUE == pau->m_fUES)
        {
            UESDecDelete(pau->m_pUES, paudec->m_pCUESdec);
            pau->m_pUES = NULL;
            paudec->m_pCUESdec = NULL;
        }
#endif
        auDelete (paudec->pau);
        paudec->pau = NULL;
    }
    
exit:

#if defined (VERIFY_PKT_SIGNATURE)
    if (g_fpSignDec)
    {
        FCLOSE(g_fpSignDec);
        g_fpSignDec = NULL;
    }
#endif // VERIFY_PKT_SIGNATURE

    return wmaResult;
} // prvDecDelete

//*****************************************************************************************
//
// audecDelete
//   free up and delete the CAudioObjectDecoder
//
//*****************************************************************************************

Void audecDelete (void* pDecHandle)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    WMARESULT wmaResult = WMA_OK;
    
    if (paudec == NULL)
        return;
    
    auMallocSetState(MAS_DELETE, NULL, 0);
    
    TRACEWMA_EXIT(wmaResult, prvDecDelete (paudec));

exit:
    CCS_CLOSE();
    auFree(paudec);
} // audecDelete

//*********************************************************************************
//         prvWipeCleanDecoder: Brings paudec to a known-to-be-clean state by
//                              1) deleting any allocated memory inside of paudec.
//                              2) wiping clean the structure
//
//*********************************************************************************
WMARESULT prvWipeCleanDecoder(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    
    // Delete any allocated memory inside of paudec
    TRACEWMA_EXIT(wmaResult, prvDecDelete(paudec));
    
    // Wipe clean entire structure
    memset(paudec, 0, sizeof(CAudioObjectDecoder));
    
    // Set member values that must be non-zero.
    // It is wise to move such initializations to audecInit.
    // Some of the enums/defines are zeroes, but are still kept here for possible future changes.
    
    paudec->m_fPacketLoss   = WMAB_TRUE;
    paudec->m_bGotValidFilterInfo = WMAB_FALSE;
    paudec->m_decsts        = BEGIN_PACKET;
    paudec->m_subfrmdecsts  = SUBFRM_HDR;
    paudec->m_hdrdecsts     = HDR_SIZE;
    paudec->m_fhdrdecsts    = FHDR_PREV;
    paudec->m_rlsts         = VLC;
    paudec->m_fLastSubFrame = WMAB_TRUE;
    paudec->m_iContinuousDecodeCountdown = 2;
    paudec->m_externalState = audecStateDone;
    paudec->m_fNeedHeader   = WMAB_TRUE;
#ifdef BUILD_UES
    paudec->m_iUESInitFlag = UES_DEC_INIT_NONE;
#endif
    
exit:
    return wmaResult;
} // prvWipeCleanDecoder


//*****************************************************************************************
//
// audecNew
//   create and initialize a CAudioObjectDecoder object
//
//*****************************************************************************************
void* audecNew (void *pMemBuf, const I32 iMemBufSize)
{
    CAudioObjectDecoder* paudec = NULL;
    WMARESULT wmaResult         = WMA_OK;
    
    if (pMemBuf != NULL && iMemBufSize < 0) {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        // Can not return wmaResult
        return paudec;
    }
    
    auMallocSetState(MAS_ALLOCATE, pMemBuf, iMemBufSize);
    paudec = (CAudioObjectDecoder*) auMalloc (sizeof (CAudioObjectDecoder));
    if(paudec == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        // Can not return wmaResult
        return paudec;
    }
    
    // Wipe clean the object just allocated
    memset(paudec, 0, sizeof(CAudioObjectDecoder));
    
    // Set all non-zero initializations
    wmaResult = prvWipeCleanDecoder(paudec);
    
    if (WMA_FAILED(wmaResult)) {
        DELETE_ARRAY(paudec);
        return NULL;
    }

    return (void*)paudec;
} // audecNew

//*****************************************************************************************
//
// prvAllocPcInfoDEC
//   Allocates memory for m_rgpcinfoDEC
//
//*****************************************************************************************
WMARESULT prvAllocPcInfoDEC(CAudioObjectDecoder* paudec, PerChannelInfo* rgpcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;
    I16 i;

    assert(paudec->m_rgpcinfoDEC == NULL);
    paudec->m_rgpcinfoDEC = (PerChannelInfoDEC*) auMalloc(sizeof(PerChannelInfoDEC) * pau->m_cChannel);
    if (paudec->m_rgpcinfoDEC == NULL)
    {
        wmaResult = WMA_E_OUTOFMEMORY;
        goto exit;
    }

    for (i = 0; i < pau->m_cChannel; i++)
    {
        PerChannelInfo* ppcinfo = rgpcinfo + i;

        ppcinfo->m_rgsubfrmconfig = (SubFrameConfigInfo*)  auMalloc (sizeof(SubFrameConfigInfo));
        if (ppcinfo->m_rgsubfrmconfig == NULL) 
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(ppcinfo->m_rgsubfrmconfig, 0, (sizeof(SubFrameConfigInfo)));
#define SIZEBUFD ((pau->m_iMaxSubFrameDiv + 2) * sizeof (I16) + sizeof (I16) + sizeof (U8))
        ppcinfo->m_rgsubfrmconfig->m_rgiSizeBuf = (I16*)  auMalloc (SIZEBUFD);
        if (ppcinfo->m_rgsubfrmconfig->m_rgiSizeBuf == NULL) 
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(ppcinfo->m_rgsubfrmconfig->m_rgiSizeBuf, 0, SIZEBUFD);

        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize = 
                        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSizeBuf + 1; //for -1 indexing
#if defined (_PREFAST_)
#pragma prefast(suppress: 12009, "PREfast noise") 
#endif
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart = 
                        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize + pau->m_iMaxSubFrameDiv + 1; //for + count indexing
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate = 
                        (U8*) (ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart + 1);        
    }
exit:
    return wmaResult;
} // prvAllocPcInfoDEC

#ifdef TEST_CORRUPT_BITSTREAM
/* This function corrupt pParam but make sure they pass the Check.
typedef struct _audecInitParams {
  WMA_U16 wFormatTag;
  WMA_U16 nChannels;
  WMA_U32 nSamplesPerSec;
  WMA_U32 nAvgBytesPerSec;
  WMA_U16 nBlockAlign;
  WMA_U16 nValidBitsPerSample;
  WMA_U32 nChannelMask;

  WMA_U16 wEncodeOpt;

  WMA_U32 cbPCMContainerSize;
  WMAPlayerInfo PlayerInfo;

  WMA_I32 iMemBufUsed; //out
  audecState audecState; //out
} audecInitParams;
*/
WMARESULT prvDamageFormat(WMAFormat* pWMAFormat, PCMFormat* pPCMFormat)
{
    WMARESULT wmaResult = WMA_OK;
    if ((rand() * 5) < RAND_MAX) {
        int iCorruptBits = rand() % 20;
        int i;
        int iParamSize = sizeof(WMAFormat); //don't touch PlayInfo/iMemBufUsed/audecState.
        for (i = 0; i < iCorruptBits; i++) {
            ((char *)pFormat)[rand() % iParamSize] ^= (rand() % 8);
        }
    }

    if (pFormat->wFormatTag < 0x160 || pFormat->wFormatTag > 0x163) {
        pFormat->wFormatTag = rand() % (0x163 - 0x160 + 1) + 0x160;
    }

    // >32 channel is valid but it takes a lot of time to malloc memory and finally out of memory and return.
    // we don't test it now.
    if (pFormat->nChannels <= 0 || pFormat->nChannels > 32)
    {
        pFormat->nChannels = rand() % 32 + 1;
    }

    if (pFormat->wFormatTag <= 0x161)
    {
        pFormat->nSamplesPerSec = (rand() % 48000 + 1);
        pFormat->nChannels = rand() % 2 + 1;
    }

    pPCMFormat->cbPCMContainerSize = rand() % 2 + 2;
    pFormat->nValidBitsPerSample = (rand() % 3) * 4 + 16;
    
    if (!(pPCMFormat->nValidBitsPerSample == 16)) {
        if  (pPCMFormat->cbPCMContainerSize < (unsigned)((pWMAFormat->nValidBitsPerSample + (BITS_PER_BYTE - 1))/BITS_PER_BYTE)) {
            pPCMFormat->cbPCMContainerSize = (unsigned)((pWMAFormat->nValidBitsPerSample + (BITS_PER_BYTE - 1))/BITS_PER_BYTE);
        }
    }
    
    if (pFormat->nAvgBytesPerSec & 0x80000000) {
        pFormat->nAvgBytesPerSec &= (~0x80000000);
    }

    if (pFormat->nBlockAlign <= 0) {
        pFormat->nBlockAlign = - pFormat->nBlockAlign;
    }
    
    if (pPlayerInfo->iOutputSamplingRate < 0) {
        pPlayerInfo->iOutputSamplingRate = -pPlayerInfo->iOutputSamplingRate;
    }
    if (pPlayerInfo->nDRCSetting < 0 || 
        pPlayerInfo->nDRCSetting > 2)
    {
        pPlayerInfo->nDRCSetting = rand() % 2;
    }
    
    return wmaResult;

}
#endif //TEST_CORRUPT_BITSTREAM

//#define CALLBACK_TEST
#ifdef CALLBACK_TEST
#define CALLBACK_STRESS
WMARESULT audecGetMoreData(void* dwUser, audecInputBufferInfo* pRet)
{
    audecInputBufferInfo* pBuf = (audecInputBufferInfo*) dwUser;
    memcpy(pRet, pBuf, sizeof(*pRet));
    
    if (pRet->cbIn == 0)
    {
        if (pRet->fNoMoreInput)
        {
            return WMA_OK;
        }
        else
        {
            return WMA_E_ONHOLD;
        }
    }

#ifdef CALLBACK_STRESS
    if (pBuf->cbIn >= 16)
    {   // feed a pseudo-random number of bytes between 8 and 15
        pRet->cbIn = 8 + *pRet->pbIn % (min(8, pBuf->cbIn - 15));
        pBuf->pbIn += pRet->cbIn;
        pBuf->cbIn -= pRet->cbIn;

        pRet->fNoMoreInput = WMAB_FALSE; // there is more in pBuf

        // these should only be set with the first portion of the buffer (if at all)
        pBuf->fTime = WMAB_FALSE;
        pBuf->fNewPacket = WMAB_FALSE;
        pBuf->cSkipBits  = 0;
    }
    else
#endif
    {
        pBuf->cbIn = 0;
    }
    
    assert(pRet->cbIn >= 8);
    return WMA_OK;
}

audecInputBufferInfo g_audecInputBuffer;
#endif//CALLBACK_TEST

#ifdef CALLBACK_TEST
#define INPUT_STATE audecStateInput
#else
#define INPUT_STATE (paudec->m_ibstrm.m_pfnGetMoreData ? audecStateDecode : audecStateInput)
#endif

// This function handles output format checks that can be performed on PCMFormat in isolation.
// Checks that require comparing PCMFormat to WMAFormat still occur in audecCheckInitParams().
// Luckily, there are currently no cross-checks involving the output sample format.
WMARESULT audecCheckOutputSampleFormat(PCMFormat* pPCMFormat)
{
    WMARESULT wmaResult = WMA_OK;

#if (BUILD_INTEGER)
    if (PCMDataPCM != pPCMFormat->pcmData)
    {
        // Integer decoder can not produce IEEE Float output
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
#endif // BUILD_INTEGER
    
    if (PCMDataPCM == pPCMFormat->pcmData)
    {
        if (pPCMFormat->nValidBitsPerSample != 16 &&
            pPCMFormat->nValidBitsPerSample != 20 &&
            pPCMFormat->nValidBitsPerSample != 24 &&
            pPCMFormat->nValidBitsPerSample != 32)
        {
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }

        if (pPCMFormat->cbPCMContainerSize != 2 &&
            pPCMFormat->cbPCMContainerSize != 3 &&
            pPCMFormat->cbPCMContainerSize != 4) 
        {
            // We intend to support decoding into 3 bytes even for V2 & V1.
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }
    else if( PCMDataIEEE_FLOAT == pPCMFormat->pcmData)
    {
        // IEEE Floating point output

        if ((sizeof(Float) * BITS_PER_BYTE != pPCMFormat->nValidBitsPerSample) ||
            (sizeof(Float) != pPCMFormat->cbPCMContainerSize))
        {
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }
    else
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    if  (pPCMFormat->cbPCMContainerSize < (unsigned)((pPCMFormat->nValidBitsPerSample + (BITS_PER_BYTE - 1))/BITS_PER_BYTE)) {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

exit:
    return wmaResult;
}

WMARESULT audecCheckInitParams(WMAFormat* pWMAFormat, PCMFormat* pPCMFormat, WMAPlayerInfo *pPlayerInfo, audecInitParams* pParams)
{
    WMARESULT wmaResult = WMA_OK;
    U16 wPlayerOpt = 0;
    U32 nIn, nOut;
    Bool fWMAStd      = WMAB_FALSE;
    Bool fWMAPro      = WMAB_FALSE;
    Bool fWMALossless = WMAB_FALSE;
    Bool fWMAProPlusV2CxLC = WMAB_FALSE;
    Bool fWMAProPlus  = WMAB_FALSE;
    //const DWORD Version = _byteswap_ushort((unsigned short)GetVersion());
#if defined(UNDER_CE) || defined(_XBOX) || defined(WMA_DECPK_BUILD)
    Bool fLH          = WMAB_FALSE;
#else
    //Bool fLH          = (Version >= 0x00000600);
    Bool fLH          = WMAB_TRUE;
#endif

    if (!pWMAFormat || !pPCMFormat)
    {
        WMADebugMessage( " audecCheckInitParams !pWMAFormat 0x%x || !pPCMFormat 0x%x\n", pWMAFormat, pPCMFormat);      
        assert (WMAB_FALSE);
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }

    fWMAStd = (0x160 == pWMAFormat->wFormatTag ||
               0x161 == pWMAFormat->wFormatTag ||
               0x165 == pWMAFormat->wFormatTag) ? WMAB_TRUE : WMAB_FALSE;
    fWMAPro = (0x162 == pWMAFormat->wFormatTag ||
               0x166 == pWMAFormat->wFormatTag) ? WMAB_TRUE : WMAB_FALSE;
    fWMAProPlus = (fWMAPro && (pWMAFormat->wAdvancedEncodeOpt || pWMAFormat->dwAdvancedEncodeOpt2));
    fWMALossless = (0x163 == pWMAFormat->wFormatTag ||
                    0x167 == pWMAFormat->wFormatTag) ? WMAB_TRUE : WMAB_FALSE;

    if (fWMAPro &&
        (((pWMAFormat->wAdvancedEncodeOpt & ENCOPT4_PLUSVER)==ENCOPT4_PLUSV2) ||
         ((pWMAFormat->wAdvancedEncodeOpt & ENCOPT4_PLUSVER)==ENCOPT4_PLUSV3)) &&
        (pWMAFormat->wAdvancedEncodeOpt & ENCOPT4_PLUSV2_CHEX)==ENCOPT4_PLUSV2_CHEX &&
        (pWMAFormat->dwAdvancedEncodeOpt2 & ENCOPT4_PLUSV2_CXLCCHMASK)!=0)
      fWMAProPlusV2CxLC = WMAB_TRUE;
    
    if (!fWMAStd && !fWMAPro && !fWMALossless)
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
    
    //we do not resample lossless content
    if (fWMALossless && pWMAFormat->nSamplesPerSec != pPCMFormat->nSamplesPerSec) {
    
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    if (fWMAStd)
    {
        if (pWMAFormat->nSamplesPerSec > 48000)
        {
            // V3 still does not have an upper bound on iSamplingRate
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
        if (pWMAFormat->nChannels > 2)
        {
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
        // Finally overcame the fear to add this
        if (pWMAFormat->nValidBitsPerSample != 16)
        {
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }
    else
    {
        // WMA Pro, WMA Lossless
#if defined(BUILD_WMAPROSTEREOONLY)
        if (pWMAFormat->nChannels > 2)
        {
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
#endif
        if (pWMAFormat->nChannels > 32)
        {
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }
    
#if !defined (BUILD_WMASTD)
    if (fWMAStd)
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
#endif // !BUILD_WMASTD

#if !defined (BUILD_WMAPRO)
    if (fWMAPro)
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
#endif // !BUILD_WMAPRO

#if !defined (BUILD_WMALSL)
    if (fWMALossless)
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
#endif // !BUILD_WMALSL
    
    if (pWMAFormat->nSamplesPerSec <= 0)
    {
      wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
      goto exit;
    }
   
    if (pWMAFormat->nChannels == 0)
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    TRACEWMA_EXIT(wmaResult, audecCheckOutputSampleFormat(pPCMFormat));
    
    if (pWMAFormat->nValidBitsPerSample != 16 && 
        pWMAFormat->nValidBitsPerSample != 20 &&
        pWMAFormat->nValidBitsPerSample != 24 &&
        pWMAFormat->nValidBitsPerSample != 32)
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }


    //  U32 nChannelMask
    // Ideally the number of 1's in nChannelMask should match cChannel.
    // However, we permit Channel mask to be 0 (to support 'track' coding in the future).
    // Since channel mask is mainly for presentation (not decoding), we ignore it 
    // currently.

    if (pWMAFormat->nAvgBytesPerSec & 0x80000000) {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }

    if (pWMAFormat->nBlockAlign <= 0) {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }

    WMADebugMessage( " audecCheckInitParams pPCMFormat->nChannels %d, pWMAFormat->nChannels %d\n", pPCMFormat->nChannels, pWMAFormat->nChannels);      
    WMADebugMessage( " audecCheckInitParams pPCMFormat->nChannelMask %d, pWMAFormat->nChannelMask %d\n", pPCMFormat->nChannelMask, pWMAFormat->nChannelMask);      

#define USE_JJ_FOLDDOWN
//#undef USE_JJ_FOLDDOWN // use Corona style pre-defined limited set of fold-down matrices

#if !defined (USE_JJ_FOLDDOWN)

    if (pPCMFormat->nChannels == pWMAFormat->nChannels)
    {
        if (pPCMFormat->nChannelMask != pWMAFormat->nChannelMask)
        {
            WMADebugMessage( " audecCheckInitParams 1\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }
    else
    {
        // We have down-mix capability for some combinations of source & sink
        if (((pPCMFormat->nChannels != 1) && (pPCMFormat->nChannels != 2)) || 
            (pWMAFormat->nChannels < 3) || 
            (pWMAFormat->nChannels > 8))
        {
            WMADebugMessage( " audecCheckInitParams 2\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }
#endif // !USE_JJ_FOLDDOWN

    if (pPCMFormat->nChannelMask != pWMAFormat->nChannelMask)
    {
        if (fWMAStd || 
            ((2 != pPCMFormat->nChannels) && fWMALossless))
        {
            // Channel mask conversion available only in WMA Pro, with the exception 
            // of stereo out on WMA Lossless
            WMADebugMessage( " audecCheckInitParams 3\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }

    if ((pPCMFormat->nChannels != pWMAFormat->nChannels) &&
        fWMAStd)
    {
        // Fold-down is not supported for WMA Standard
        WMADebugMessage( " audecCheckInitParams 4\n");
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
    
    if (fWMALossless && 
        (pPCMFormat->nChannels != pWMAFormat->nChannels) &&
        2 != pPCMFormat->nChannels)
    {
        // WMA Lossless allows fold-down to stereo, but not to other configurations
        WMADebugMessage( " audecCheckInitParams 5\n");
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }
    
    // U16 wEncodeOpt: what can be tested? TODO
    
    if (pPlayerInfo) {
        // Do all kinds of player options tests.
        if (pPlayerInfo->nDRCSetting < 0 || 
            pPlayerInfo->nDRCSetting > 2)
        {
            WMADebugMessage( " audecCheckInitParams 6\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }

        // pPlayerInfo->nPlayerOpt tests are done way deep inside during auInit

        // pPlayerInfo->rgiMixDownMatrix can be null. Currently no check on size of the 
        // array.

        // pPlayerInfo->wPeakAmplitude;

        // pPlayerInfo->wRmsAmplitude;
        wPlayerOpt = pPlayerInfo->nPlayerOpt;
    }
    
    // check resample opt
    nIn  = pWMAFormat->nSamplesPerSec;
    nOut = pPCMFormat->nSamplesPerSec;

    // in WMA Lsl we don’t support internal resampling of any kind.
    if (fWMALossless)
    {   
         if (nIn != nOut || 
             wPlayerOpt & PLAYOPT_PAD2XTRANSFORM || 
             wPlayerOpt & PLAYOPT_HALFTRANSFORM)
         {
             WMADebugMessage( " audecCheckInitParams 7\n");
             wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
             goto exit;
         }
    }

    if (fWMAProPlus)
    {
        // Decoder does not support resampling for ProPlus
        if (nIn != nOut)
        {
            WMADebugMessage( " audecCheckInitParams 8\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;		
        }
    }
    
    if (fWMAPro)
    {
        // in WMA Pro we don’t support PAD2XTRANSFORM due to mixed lossless.
        // in WMA Pro we don't support upsampling due to PAD2XTRANSFORM issue.
        if (wPlayerOpt & PLAYOPT_PAD2XTRANSFORM || nIn < nOut)
        {
            WMADebugMessage( " audecCheckInitParams 9\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;		
        }
        // in WMA Pro we only support HALFTRANSFORM by 2 due to mixed lossless.
        // in WMA Pro we only support downsampling by 2 due to HALFTRANSFORM issue.
        if (nIn > 2 * nOut)
        { 
            WMADebugMessage( " audecCheckInitParams 10\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;		
        }
    }

    if (fWMAStd)
    {
        if (nIn > 4 * nOut)
        {
            // For WMA Std, limit to quarter sample rate for quality considerations
            WMADebugMessage( " audecCheckInitParams 11\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
             goto exit;
        }
 
        // allow arbitrary ratios up to 6x, so that 8KHz content can be played 
        // in 48KHz systems. Plays ugly though.
        if (nIn * 6 < nOut)
        {
            WMADebugMessage( " audecCheckInitParams 12\n");
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
    }

    // U32 dwUserData
    // I32 *piMemUsed: Can be NULL

    // for LH: does not support up-mixing
    //         Supports channel fold down to only 2 channels
    // (see winos bug #1185825)
    if( fLH && pPCMFormat->nChannels > pWMAFormat->nChannels && !fWMAProPlusV2CxLC)
    {
        WMADebugMessage( " audecCheckInitParams 13\n");
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
    }
    if( fLH && pPCMFormat->nChannels < pWMAFormat->nChannels && pPCMFormat->nChannels != 2)
    {
        WMADebugMessage( " audecCheckInitParams 14\n");
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
    }

exit:
    return wmaResult;
} // audecCheckInitParams

//*****************************************************************************************
//
// auInitDec
// initialize a CAudioObject based on information from input file or stream
//
//*****************************************************************************************
WMARESULT auInitDec (CAudioObject* pau, 
                Int  iVersionNumber,
                Bool fUES,
                Int cSubband, 
                Int cSamplePerSec, 
                U16 cChannel, 
                U32 nBytePerSample,
                U16 nValidBitsPerSample,
                U32 nChannelMask,
                Int cBytePerSec, 
                Int cbPacketLength,
                U16 iEncodeOpt,
                U16 uAdvancedEncodeOpt,
                U32 uAdvancedEncodeOpt2,
                Int iOutputSamplingRate,
                PCMData dataType,
                WMAPlayerInfo *pWmaPlayerInfo)
{
    WMARESULT   wmaResult = WMA_OK;
    WMAMALLOC_COUNT_DECL;

    // Check and store the input parameters into member variables
    TRACEWMA_EXIT(wmaResult, prvInitCommonParameters(pau, iVersionNumber, fUES, cSubband, cSamplePerSec,
        cChannel, nBytePerSample, nValidBitsPerSample, nChannelMask, cBytePerSec,
        cbPacketLength, iEncodeOpt, uAdvancedEncodeOpt, uAdvancedEncodeOpt2,
        iOutputSamplingRate, dataType, pWmaPlayerInfo));
    WMADebugMessage( " auInitDec 1\n");      
    // Set member variables based on input parameters
    TRACEWMA_EXIT(wmaResult, prvInitCommonSecondaryFixed(pau));

    // Allocate memory buffers, then initialize them
    WMADebugMessage( " auInitDec 2\n");      
    TRACEWMA_EXIT(wmaResult, prvInitCommonAllocate(pau, WMAB_FALSE));
    WMADebugMessage( " auInitDec 3\n");      
    TRACEWMA_EXIT(wmaResult, prvInitCommonSecondaryAllocated(pau));

    // Select optimized functions based on current platform and/or CPU capabilities
    WMADebugMessage( " auInitDec 4\n");      
    TRACEWMA_EXIT(wmaResult, prvInitCommonSetFunctionPtrs(pau));

    // Reset operational variables
    WMADebugMessage( " auInitDec 5\n");      
    TRACEWMA_EXIT(wmaResult, prvInitCommonResetOperational(pau));

#if defined(WMA_TARGET_MIPS)
    auCheckMIPSIIProcessor(pau);
#endif

exit:
    WMAMALLOC_COUNT_PRT("TotalDEC", -1, -1);
    return wmaResult;
} // auInitDec

WMARESULT prvInitDecoderSetFunctionPtrs(CAudioObjectDecoder *paudec)
{
    WMARESULT       wmaResult = WMA_OK;
    CAudioObject   *pau = paudec->pau;
    // We don't call prvInitCommonSetFunctionPtrs here like encoder since
    // it is called in auInitDec (encoder does not call auInitDec);

#if (defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)) || defined (BUILD_WMALSL)
    // --- initialize LMS (MCLMS and CDLMS) function pointers --- //
    assert(pau->m_nValidBitsPerSample > 0);
    if (pau->m_nValidBitsPerSample <= 16) {
#   if defined(_WMA_TARGET_XBOX2_) && defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
        paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I16_C_XENON;
#   else
        paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I16_C;
#   endif  //XENON
    }
    else {
#   if defined(_WMA_TARGET_XBOX2_) && defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
        paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I32_C_XENON;
#   else
        paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I32_C;
#   endif
    }

#if defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_LOSSLESSDECPROLSL)
    if( mips_use_MIPSII_strict ) {
        if (pau->m_nValidBitsPerSample <= 16) {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I16_MIPSII;
        } else {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I32_MIPSII;
        }
    } else {
        if (pau->m_nValidBitsPerSample <= 16) {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I16_MIPS32;
        } else {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I32_MIPS32;
        }
    }
#endif

#if defined(WMA_TARGET_X86) && !defined (DISABLE_OPT) && !defined(WMA_DISABLE_MMX)
    // --- initialize LMS (MCLMS and CDLMS) function pointers --- //
    if (pau->m_nValidBitsPerSample <= 16) {
        if( g_SupportMMX() ) {
            paudec->pprvDecLMSPredictor= prvDecLMSPredictor_I16_MMX;
    #ifdef LLM_TEST_COMPUTATION_CONSISTENCE
            if (rand() % 2 == 0) {
                paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I16_C;
            }
    #endif
        }
        else {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I16_C;
        }
    }
    else {
        if( g_SupportMMX() ) {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I32_C;
        }
        else {
            paudec->pprvDecLMSPredictor = prvDecLMSPredictor_I32_C;
        }
    }
#else

#endif // WMA_TARGET_X86 && !DISABLE_OPT && !WMA_DISABLE_MMX

    // function pointer can remain NULL for BUILD_WMASTD

#endif // // (BUILD_WMAPRO && BUILD_WMAPRO_PLLM) || BUILD_WMALSL

    return wmaResult;
}

// Why don't we fail when cbPCMContainerSize is too small ?  Must be some historical reason...
// This code is not new, it used to live in audecInit().
// hongwang CR: 
// *pcbPCMContainerSize (input): this is from required decoder output bit depth
// nEncoderBitsPerSample: bit depth of input audio file at the encoder
// *pcbPCMContainerSize (output): the maximum of the two input are needed for decoding and 
//                                PCM reconstruction.
static void prvFixPCMContainerSize(U32 *pcbPCMContainerSize, U32 nEncoderBitsPerSample)
{
    // Set the container size that is needed by the current crop of decoders
    U32 nBytePerSampleTmp = ((nEncoderBitsPerSample + (BITS_PER_BYTE - 1))/BITS_PER_BYTE);
    *pcbPCMContainerSize = max (*pcbPCMContainerSize, nBytePerSampleTmp);
}

// This code used to live in audecInit()
static void audecInitRequantizeTo16Bits(CAudioObjectDecoder* paudec,
                                        PCMFormat* pPCMFormat)
{   // Requantizing to 16 bits
    CAudioObject* pau = paudec->pau;

    paudec->m_fReQuantizeTo16   = WMAB_FALSE;
    paudec->m_nDstBytePerSample = pau->m_nBytePerSample;
    paudec->m_nDstValidBitsPerSample = pau->m_nValidBitsPerSample;
    if (pau->m_nValidBitsPerSample != 16 && pPCMFormat->nValidBitsPerSample == 16)
    {
        assert(pau->m_iVersion > 2); // Just to catch bugs
        paudec->m_fReQuantizeTo16 = WMAB_TRUE;
        paudec->m_nDstValidBitsPerSample = 16;
        paudec->m_nDstBytePerSample = min(2, pau->m_nBytePerSample);
        if (paudec->m_nDstBytePerSample == pau->m_nBytePerSample) { // Why extra steps?
            paudec->m_fReQuantizeTo16 = WMAB_FALSE;
            paudec->m_nDstValidBitsPerSample = pau->m_nValidBitsPerSample;
        }
    }
}


// This function may be called to "try" an output format, without necessarily expecting
// it to succeed.  Therefore, this function should (1) avoid audec state changes until
// success is assured, and (2) not assert or do anything rash if pPCMFormat is not accepted.
WMARESULT audecChangeOutputFormat(void* pDecHandle, PCMFormat* pPCMFormat, WMA_Bool fTestOnly)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    WMARESULT   wmaResult = WMA_OK;
    U32 nBytePerSample;

    if (NULL == paudec || NULL == paudec->pau) 
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }

    // only output sample format changes are currently supported
    if ((pPCMFormat->nSamplesPerSec != (WMA_U32)paudec->m_iDstSamplingRate) ||
        (pPCMFormat->nChannels      != (WMA_U32)paudec->m_cDstChannel     ) ||
        (pPCMFormat->nChannelMask   != paudec->m_nDstChannelMask ))
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    TRACEWMA_EXIT(wmaResult, audecCheckOutputSampleFormat(pPCMFormat));

    if (fTestOnly)
    {
        goto exit;
    }

    nBytePerSample = pPCMFormat->cbPCMContainerSize;
    prvFixPCMContainerSize(&nBytePerSample, paudec->pau->m_nValidBitsPerSample);
    
    // these never fail, hence no logic here to recover from their failure
    TRACEWMA_EXIT(wmaResult, prvInitOutputSampleFormatParameters(paudec->pau, nBytePerSample, pPCMFormat->pcmData));
    TRACEWMA_EXIT(wmaResult, prvInitOutputSampleFormatSecondaryFixed(paudec->pau));
    TRACEWMA_EXIT(wmaResult, prvInitOutputSampleFormatSetFunctionPtrs(paudec->pau));

    audecInitRequantizeTo16Bits(paudec, pPCMFormat);
#ifdef BUILD_UES
    if (WMAB_TRUE == paudec->pau->m_fUES)
    {
        if (paudec->pau->m_pUES->m_pPCMFormat)
        {
            memcpy(paudec->pau->m_pUES->m_pPCMFormat, pPCMFormat, sizeof(PCMFormat));
        }
    }
#endif

exit:
    return wmaResult;
}

#if defined(BUILD_WMAPROLBRV1)
WMARESULT audecPlusInit(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;

    if (pau->m_bFreqex || pau->m_bCx || pau->m_bReconProc
#if defined(BUILD_WMAPROLBRV2)
        || pau->m_fBasePlus
#endif
        )
    {
        paudec->m_pibsPlus =
            (CWMAInputBitStream*)auMalloc(sizeof(CWMAInputBitStream));
        CHECKWMA_ALLOC(wmaResult, paudec->m_pibsPlus);
        ibstrmInit(paudec->m_pibsPlus, paudec);
#if defined(WRITE_PLUS_TO_FILE)
        wmaResult = plusGetMoreData(paudec);
#endif
    }

    if (pau->m_bFreqex)
    {
        TRACEWMA_EXIT(wmaResult, freqexDecInit(paudec));
    }

#if defined (BUILD_WMAPROLBRV2)
    if (pau->m_fBasePlus)
    {
        TRACEWMA_EXIT(wmaResult, bpdecInit(paudec));
    }
#endif // BUILD_WMAPROLBRV2

    if (pau->m_bReconProc)
    {
        pau->m_prp->m_phParent = (Void*)paudec;
        pau->m_prp->m_pfnParentSetTileNotInUse = NULL;
#if defined(BUILD_WMAPROLBRV2)
        pau->m_prp->m_pfnDecodeReconFexTile = chexDecodeReconFexTile;
#else
        pau->m_prp->m_pfnDecodeReconFexTile = NULL;
#endif
    }

exit:
    return wmaResult;
}
#endif // BUILD_WMAPROLBRV1


//*****************************************************************************************
//
// audecInit
//   initialize a CAudioObjectDecoder for parameters from input file or stream
//
//*****************************************************************************************
WMARESULT audecInit (void* pDecHandle, WMAFormat* pWMAFormat, PCMFormat* pPCMFormat,
                                       WMAPlayerInfo *pPlayerInfo, audecState *paudecState,
                                       audecInitParams* pParams)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    Float fltBitsPerSample = 0.0F;
    CAudioObject* pau = NULL;
    WMARESULT   wmaResult = WMA_OK;
    Int k;
    Int cSubband;
    Int iVersion;
    Bool fLossless;
    U16 nPlayerOpt = 0;
    I32* rgiMixDownMatrix = NULL;
    U32 nBytePerSample;
    U8  nHdrBits = 0;
    Bool fUES = WMAB_FALSE;

    WMADebugMessage( " audecInit()\n"); 
    
#ifdef CORRUPT_BITSTREAM_TEST
    WMAFormat DamagedWMAFormat;
    PCMFormat DamagedPCMFormat;
#endif

#if 0
    gReadExtraArgs();
#endif

#if defined(BUILD_WMASTD) || defined(BUILD_WMAPRO)

#if defined(FFT_LOOKUPTBL) && FFT_LOOKUPTBL
    conFFT128Tbl();
#endif
#if defined(DCT_LOOKUPTBL) && DCT_LOOKUPTBL
    conpre128FFTbl(g_pre128FFTTbl_scale1, &g_nFacExponent_scale1, 1.0f);
    conpre128FFTbl(g_pre128FFTTbl_scale2_256, &g_nFacExponent_scale2_256, 2.0f/256);
    conpost128FFTbl(g_post128FFTTbl);
#endif
#ifdef FFTDCT_VAR_LOOKUPTBL
    genVarTblFFT();
    genVarTblPreFFT(g_pbp1VarTblPreFFT, g_nFacVarTblPreFFT, 1.0f);
    genVarTblPreFFT(g_pbp1VarTblPreFFT2, g_nFacVarTblPreFFT2, 2.0f);
    genVarTblPostFFT(g_pbp1VarTblPostFFT);
#endif // FFTDCT_VAR_LOOKUPTBL

#endif // BUILD_WMASTD || BUILD_WMAPRO

#ifdef TEST_CODE
    {
    int i;
    U32 iRVSeed = (unsigned)time( NULL );
//    iRVSeed = 1036024048;
    WMAPrintf("The seed for random-number generation is %d\n", iRVSeed);
    srand(iRVSeed);
    // get rid of the first 100 rand numbers.
    for (i = 0; i < rand() % 100; i++)
        rand();
    }
#endif //TEST_CODE

    if (NULL == paudec || 
        NULL == paudecState) 
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        WMADebugMessage( " audecInit - fail 1\n"); 
        goto exit;
    }

#ifdef TEST_CORRUPT_BITSTREAM
    // use private copies so decapp doesn't have to repair our damage
    memcpy(&DamagedWMAFormat, pWMAFormat, sizeof(WMAFormat));
    memcpy(&DamagedPCMFormat, pPCMFormat, sizeof(PCMFormat));
    pWMAFormat = &DamagedWMAFormat;
    pPCMFormat = &DamagedPCMFormat;
    prvDamageFormat(pWMAFormat, pPCMFormat);
//  pWMAFormat->nSamplesPerSec = 2946; // in v2 it trigger a bug in prvSetBarkIndex (CAudioObject* pau)
//  pWMAFormat->nSamplesPerSec = 16000;
#endif //TEST_CORRUPT_BITSTREAM

    WMADebugMessage("audecInit(0x%04X, %d, %d, %d, %d, %d, %08X, %04X, %d, %d, %d)\n",
              pWMAFormat->wFormatTag, pWMAFormat->nChannels, pWMAFormat->nSamplesPerSec,
              pWMAFormat->nAvgBytesPerSec, pWMAFormat->nBlockAlign,
              pWMAFormat->nValidBitsPerSample, pWMAFormat->nChannelMask, pWMAFormat->wEncodeOpt,
              pPCMFormat->nSamplesPerSec, pPCMFormat->nValidBitsPerSample, pPCMFormat->cbPCMContainerSize);

    fLossless = WMAB_FALSE;
    switch (pWMAFormat->wFormatTag) {
    case 0x160: iVersion = 1; break;
    case 0x161: iVersion = 2; break;
    case 0x162: iVersion = 3; break;
    case 0x163: iVersion = 3; fLossless = WMAB_TRUE; break;
    case 0x165: iVersion = 2; fUES      = WMAB_TRUE; break;
    case 0x166: iVersion = 3; fUES      = WMAB_TRUE; break;
    case 0x167: iVersion = 3; fUES      = WMAB_TRUE; fLossless = WMAB_TRUE; break;
    default: WMADebugMessage("Wrong input FormatTag %d", pWMAFormat->wFormatTag); 
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }

    if(WMAB_FALSE == fUES)
    {               
        WMADebugMessage( " audecInit 1\n");      
    // First, do some sanity checks on input
        TRACEWMA_EXIT(wmaResult, audecCheckInitParams(pWMAFormat, pPCMFormat, pPlayerInfo, pParams));
    
        WMADebugMessage( " audecInit 2\n");      
    // To protect from multiple initializations, bring to a known "new" state.
        TRACEWMA_EXIT(wmaResult, prvWipeCleanDecoder(paudec));

        assert(pau == NULL);

        paudec->pau = pau = auNew ();
        if (NULL == pau) 
        {
            WMADebugMessage( " audecInit - fail 2\n"); 
            TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
            goto exit; // to keep Prefast happy
        }
        assert( CODEC_NULL == pau->m_codecStatus ); // an unnecessary check was removed. Added this assert to make sure that future changes do not voilate the assumption
    
    // Fill in function ptrs with decoder fns
        pau->aupfnGetNextRun = prvGetNextRunDEC;
        paudec->m_pprvNewInputBuffer = prvNewInputBuffer;
    }
#ifdef BUILD_UES
    else // when fUES == WMAB_TRUE
    {
        WMADebugMessage( " audecInit 3\n");      
        wmaResult=prvaudecInitUES(paudec, pWMAFormat, pPCMFormat, pPlayerInfo, pParams);
        paudec->m_externalState = INPUT_STATE;
        *paudecState = INPUT_STATE;

        if(WMA_S_DEC_PARTIAL_INIT == wmaResult)
        {
            wmaResult = WMA_OK;
            WMADebugMessage( " audecInit - fail 3\n"); 
            goto exit;
        }
        if(WMA_FAILED(wmaResult))
        {
            WMADebugMessage( " audecInit - fail 4\n"); 
            TraceResult(wmaResult);
            goto exit;
        }
        pau = paudec->pau;
    }
#endif
    pau->m_bEncoder = WMAB_FALSE;
    pau->m_hParent = (Void*)paudec;

    paudec->m_fSPDIF = pParams ? pParams->fSPDIF : WMAB_FALSE;
    paudec->m_fSPDIFStyleGetPCM = paudec->m_fSPDIF;
    //paudec->m_fSPDIFStyleGetPCM = WMAB_TRUE; // not supported for v2 - prvInitDiscardSilence() will assert
 
    //wchen: in the future we should use the one directly from the bitstream.
    //but for now the one in the bistream doesn't represent Sample/Frame
    //instead it represents Sample/Raw Packet that is useless for the decoder
    //other than serving the stupidity in the V4RTM decoder. We can't change the format for now.
    //but it should be changed to reprsent Sample/Frame and that should nullify the following function call.
    cSubband = msaudioGetSamplePerFrame (pWMAFormat->nSamplesPerSec, pWMAFormat->nAvgBytesPerSec * 8, iVersion, pWMAFormat->wEncodeOpt);

#if defined(DEBUG_ENCODE_FOR_XBOX) && defined (_DEBUG)
    fprintf(stdout, "Format Tag:        %d\n", (I32)pWMAFormat->wFormatTag);
    fprintf(stdout, "#Channels:         %d\n", (I32)pWMAFormat->nChannels);
    fprintf(stdout, "Sampling Rate:     %d\n", (I32)pWMAFormat->nSamplesPerSec);
    fprintf(stdout, "Avg Byte Rate:     %d\n", (I32)pWMAFormat->nAvgBytesPerSec);
    fprintf(stdout, "Valid Bits/Sample: %d\n", (I32)pWMAFormat->nValidBitsPerSample);
    fprintf(stdout, "Channel Mask:      0x%x\n", (I32) pWMAFormat->nChannelMask);
    fprintf(stdout, "Encode Options:    0x%x\n", (I32)pWMAFormat->wEncodeOpt);
    fprintf(stdout, "Packet Size:       %d bytes\n", (I32)pWMAFormat->nBlockAlign);
    fprintf(stdout, "Frame Size:        %d samples\n\n\n", cSubband);
#endif // DEBUG_ENCODE_FOR_XBOX && _DEBUG

   if (cSubband <= 0) {
        WMADebugMessage( " audecInit - fail 5\n"); 
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
        goto exit; // to keep Prefast happy
    }
    
    // shallow copy of player info (e.g. matrix not copied)
    if (pPlayerInfo)
        memcpy(&paudec->m_wmapi, pPlayerInfo, sizeof(paudec->m_wmapi));
    else
        memset(&paudec->m_wmapi, 0, sizeof(paudec->m_wmapi));
    
    nPlayerOpt = paudec->m_wmapi.nPlayerOpt;
    rgiMixDownMatrix = paudec->m_wmapi.rgiMixDownMatrix;

    if (nPlayerOpt & PLAYOPT_IGNOREFREQEX)
    {
        pau->m_bIgnoreFreqex = WMAB_TRUE;
    }
    if (nPlayerOpt & PLAYOPT_IGNORECX)
    {
        pau->m_bIgnoreCx = WMAB_TRUE;
    }
    
    if (paudec->m_wmapi.nDRCSetting != WMA_DRC_HIGH) {
        nPlayerOpt |= PLAYOPT_DYNAMICRANGECOMPR; // used by routines which see which player options are supported
        paudec->m_wmapi.nPlayerOpt |= PLAYOPT_DYNAMICRANGECOMPR;
    }

    nBytePerSample = pPCMFormat->cbPCMContainerSize;
    prvFixPCMContainerSize(&nBytePerSample, pWMAFormat->nValidBitsPerSample);

    WMADebugMessage( " audecInit 4, fUES = %d\n", fUES);      

    // should some day pass fLossless to auInitDec and get rid of the lossless bit in wEncOpt 
    TRACEWMA_EXIT(wmaResult, auInitDec (pau, iVersion, fUES, cSubband, pWMAFormat->nSamplesPerSec, 
        pWMAFormat->nChannels, nBytePerSample, pWMAFormat->nValidBitsPerSample, pWMAFormat->nChannelMask,
        pWMAFormat->nAvgBytesPerSec, pWMAFormat->nBlockAlign, pWMAFormat->wEncodeOpt,
        pWMAFormat->wAdvancedEncodeOpt, pWMAFormat->dwAdvancedEncodeOpt2,
        pPCMFormat->nSamplesPerSec, pPCMFormat->pcmData,
        &paudec->m_wmapi));

    nHdrBits = WMA_get_nHdrBits(paudec); 
    if (nHdrBits > BITS_PER_DWORD)
    {
        // Current decoder can not deal with this bit stream
        WMADebugMessage( " audecInit - fail 6\n"); 
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    WMADebugMessage( " audecInit 5\n");      
    TRACEWMA_EXIT(wmaResult, prvInitDecoderSetFunctionPtrs(paudec));

    paudec->m_rgpcinfo = (PerChannelInfo*) auMalloc (sizeof (PerChannelInfo) * pau->m_cChannel);
    if(paudec->m_rgpcinfo == NULL)
    {
        WMADebugMessage( " audecInit - fail 7\n"); 
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (paudec->m_rgpcinfo, 0, sizeof (PerChannelInfo) * pau->m_cChannel);
    WMADebugMessage( " audecInit 6\n");      
    TRACEWMA_EXIT(wmaResult, prvAllocatePcInfoCommon(pau, paudec->m_rgpcinfo));
    WMADebugMessage( " audecInit 7\n");      
    TRACEWMA_EXIT(wmaResult, prvAllocPcInfoDEC(paudec, paudec->m_rgpcinfo));
    WMADebugMessage( " audecInit 8\n");      
    TRACEWMA_EXIT(wmaResult, prvResetPcInfoCommon(pau, paudec->m_rgpcinfo));
    pau->m_rgpcinfo = paudec->m_rgpcinfo;

    WMADebugMessage( " audecInit 9\n");      
    TRACEWMA_EXIT (wmaResult, prvReConfig (paudec));

    if (pau->m_fUseVecCoder)
    {
        paudec->m_decRunLevelVecState.getState = TABLE_INDEX;
        paudec->m_pfnResetEntropyCoder = prvResetVecCoder;
        pau->aupfnGetNextRun = prvGetNextRunDECVecTableIndex;
    }

    // Handle player settings
    // Downmixing output
    paudec->m_fChannelFoldDown= WMAB_FALSE;
    paudec->m_fLtRtDownmix    = WMAB_FALSE;
    paudec->m_cDstChannel     = pPCMFormat->nChannels;
    paudec->m_nDstChannelMask = pPCMFormat->nChannelMask;
    paudec->m_fltChannelFoldDownGain = 1.0F;
    paudec->m_bAuthorControlledChDnMixMtx = WMAB_FALSE;
    
    if ((pau->m_cChannel != paudec->m_cDstChannel) ||
        (pau->m_nChannelMask != paudec->m_nDstChannelMask))
    {
        if (pau->m_iVersion <= 2)
        {
            WMADebugMessage( " audecInit - fail 8\n"); 
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
        paudec->m_fChannelFoldDown = WMAB_TRUE;
    }

#if defined (BUILD_WMAPRO)
    if (paudec->m_fChannelFoldDown == WMAB_TRUE)
    {
    WMADebugMessage( " audecInit 10\n");      
        // only handle ltrt downmixing in specific cases
        if (nPlayerOpt & PLAYOPT_LTRT)
        {
            paudec->m_fLtRtDownmix = WMAB_TRUE;
        }

        if (!(paudec->m_fLtRtDownmix == WMAB_TRUE &&
              paudec->m_cDstChannel == 2 &&
              pau->m_cChannel > 2))
        {
            paudec->m_fLtRtDownmix = WMAB_FALSE;
        }

        if (paudec->m_fLtRtDownmix == WMAB_FALSE) // regular downmixing
        {
            wmaResult = prvInitChDnMix(paudec, rgiMixDownMatrix,
                                       pau->m_cChannel, pau->m_nChannelMask,
                                       paudec->m_cDstChannel, paudec->m_nDstChannelMask);
            if (wmaResult != WMA_OK)
            {
                WMADebugMessage( " audecInit - fail 9\n"); 
                wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
                goto exit;
            }
        }
        else // LtRt downmixing
        {
            PCMFormat inPCMFormat;
            Int cLtRtQuality;

            paudec->m_fLtRtDownmixNonnormal = WMAB_FALSE;

            paudec->m_pLtRtDownmix = (LtRtDownmix*)auMalloc(sizeof(LtRtDownmix));
            if (paudec->m_pLtRtDownmix == NULL)
            {
                WMADebugMessage( " audecInit - fail 10\n"); 
                wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
                goto exit;
            }
            ltrtDownmixZero(paudec->m_pLtRtDownmix);
            
            WMAFormat2PCMFormat(pWMAFormat, &inPCMFormat);

            paudec->m_cLtRtBufSize = 1000; // can be anything
            cLtRtQuality = 40;
#ifdef UNDER_CE
            paudec->m_cLtRtBufSize = (Int)(pPlayerInfo->iLtRtBufsize);
            cLtRtQuality = (int)(pPlayerInfo->iLtRtQuality);
#endif
            TRACEWMA_EXIT(wmaResult,
                        ltrtDownmixInitBuf(paudec->m_pLtRtDownmix,
                                           cLtRtQuality,
                                           //max(10, 20*pau->m_iXformSamplingRate/96000),
                                           pau->m_iXformSamplingRate,
                                           (DataType)((1<<(pau->m_nValidBitsPerSample-1))-1),
                                           paudec->m_cLtRtBufSize, &inPCMFormat)); 

			// if (pau->m_cChannel != LTRT_SRC_CHANNELS || pau->m_nChannelMask != LTRT_SRC_MASK)
            paudec->m_fLtRtDownmixNonnormal = WMAB_TRUE;
            // to go to format that we know how to do ltrt on
            // The down mixing matrix used will be the one generated in paudec->m_pLtRtDownmix above.
            TRACEWMA_EXIT(wmaResult, prvInitChDnMix(paudec, NULL,
                               pau->m_cChannel, pau->m_nChannelMask,
                               // LTRT_SRC_CHANNELS, LTRT_SRC_MASK));
                               3, 0));
        }
    }
    
    paudec->m_rgfltPostProcXform      = NULL;
    paudec->m_rgfltPostProcXformPrev  = NULL;
    paudec->m_rgfltPostProcXformBlend = NULL;
    paudec->m_fPostProcXform          = WMAB_FALSE;
    paudec->m_fPostProcXformPrev      = WMAB_FALSE;
    
    if (pau->m_iVersion > 2)
    {
        paudec->m_rgfltPostProcXform = (ChPPXFormType*) auMalloc(sizeof(ChPPXFormType) * pau->m_cChannel * pau->m_cChannel);
        if (paudec->m_rgfltPostProcXform == NULL)
        {
            WMADebugMessage( " audecInit - fail 11\n"); 
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        paudec->m_rgfltPostProcXformPrev = (ChPPXFormType*) auMalloc(sizeof(ChPPXFormType) * pau->m_cChannel * pau->m_cChannel);
        if (paudec->m_rgfltPostProcXformPrev == NULL)
        {
            WMADebugMessage( " audecInit - fail 12\n"); 
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        paudec->m_rgfltPostProcXformBlend = (ChPPXFormType*) auMalloc(sizeof(ChPPXFormType) * pau->m_cChannel * pau->m_cChannel);
        if (paudec->m_rgfltPostProcXformBlend == NULL)
        {
            WMADebugMessage( " audecInit - fail 13\n"); 
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
    }
#endif // BUILD_WMAPRO

    {
        Int iMaxCh, iMemSize;
        iMaxCh = max(pau->m_cChannel, paudec->m_cDstChannel);
        if (paudec->m_fLtRtDownmixNonnormal)
            iMaxCh = max(iMaxCh, LTRT_SRC_CHANNELS);
        iMemSize = max(sizeof(PCMSAMPLE), sizeof(CoefType)) * iMaxCh;
        paudec->m_rgpcmsTemp = (PCMSAMPLE*) auMalloc(iMemSize);
        if (paudec->m_rgpcmsTemp == NULL)
        {
            WMADebugMessage( " audecInit - fail 14\n"); 
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        paudec->m_pctTemp = (CoefType*) paudec->m_rgpcmsTemp;
        paudec->m_rgpctTemp = (CoefType**) auMalloc(sizeof(CoefType*)*iMaxCh);
        if (NULL == paudec->m_rgpctTemp)
        {
            WMADebugMessage( " audecInit - fail 15\n"); 
            TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
        }
        paudec->m_ppcbtTemp = (CBT**) paudec->m_rgpctTemp;
    }

    WMADebugMessage( " audecInit 11\n");      
    audecInitRequantizeTo16Bits(paudec, pPCMFormat);

    paudec->m_iDstSamplingRate = pPCMFormat->nSamplesPerSec;
    paudec->m_fUpsample2x = WMAB_FALSE;
    paudec->m_fResample = WMAB_FALSE;
    paudec->m_fLowPass = WMAB_FALSE;
    
    if (paudec->m_iDstSamplingRate == 2 * pau->m_iXformSamplingRate) {
        paudec->m_fUpsample2x = WMAB_TRUE;
    }
    else if (paudec->m_iDstSamplingRate!=pau->m_iXformSamplingRate)
    {
        paudec->m_fResample = WMAB_TRUE;
        // if downsampling, should use lowpass filter
        if (paudec->m_iDstSamplingRate < pau->m_iXformSamplingRate)
            paudec->m_fLowPass = WMAB_TRUE;
    }

    // always initialize these variables, use in audecGetPCM
    prvInterpolateInit(paudec, pau->m_iXformSamplingRate,
                       paudec->m_iDstSamplingRate);
    paudec->m_iInterpolCurPos = paudec->m_iInterpolDstBlkSize;
    // check resampling rates are reasonable...
    if (paudec->m_iInterpolSrcBlkSize >= 10000 ||
        paudec->m_iInterpolDstBlkSize >= 10000) {
        WMADebugMessage( " audecInit 12\n");      
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }

    // interpolation resampling done after downmixing, so use m_cDstChannel
    if (paudec->m_fUpsample2x || paudec->m_fResample) {
      paudec->m_iPriorSample =
        (I32*)auMalloc(paudec->m_cDstChannel*sizeof(I32));
      if (paudec->m_iPriorSample == NULL) {
        WMADebugMessage( " audecInit 13\n");      
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
      }
      for (k = 0; k < paudec->m_cDstChannel; k++)
        paudec->m_iPriorSample[k] = 0;
      paudec->m_iLastSample =
        (PCMSAMPLE*)auMalloc(paudec->m_cDstChannel*sizeof(PCMSAMPLE));
      if (paudec->m_iLastSample == NULL) {
        WMADebugMessage( " audecInit 14\n");      
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
      }
    }

    // set postprocessing function pointer
    pau->m_pfnPostProcess = audecPostProcessPrePCM;

#ifdef TEST_VRHEADPHONE
    if (pau->m_cChannel != 6 ||
        paudec->m_cDstChannel!= 2 ||
        (paudec->m_iDstSamplingRate != 44100 && paudec->m_iDstSamplingRate != 48000) ||
        paudec->m_nDstValidBitsPerSample != 16)
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        // Cant return wmaResult
        return wmaResult;
    }

    // Decoder can generate WAV in a format other than specified in WMAFormat. Application gives decoder a PCMFormat 
    // to specify the output format it wants. The decoder computes the container size of both WMAFormat and PCMFormat 
    // and choose the larger one (save in pau->m_nBytePerSample) as the container size of internal data (such as the 
    // input to the chdownmix). (The PCMFormat's container size is paudec->m_nDstBytePerSample and WMAFormat is computed
    // online). The data type (PCMDataPCM or PCMDataIEEE_FLOAT) is decided by PCMFormat. Therefore, 
    // if the PCMFormat's container is larger than the WMAFormat's container, the internal data is already in the 
    // format of what the application wants and everthing just goes through. But if WMAFormat has larger container
    // size, we have to do the conversion (at chdownmixing) to convert the data in pau->m_nBytePerSample container
    // to paudec->m_nDstBytePerSample container). That only happens when application set the output to
    // 16 bits since the WMAFormat only supports 16 or 24 bits container. There is a special mode 
    // (paudec->m_fRequantizeto16) to handle it.
    //
    // * In computation, we only care about container size and data type. ValidBitPerSample could be ignored.
    // * If WMA is 16bits and we want 24 bits PCM, the output WAV could have 16 bits ValidBitsPerSample in 3 
    //   bytes containers.

    paudec->m_fmtI.nSamplesPerSec = paudec->m_iDstSamplingRate; // in chdownmix, data is already in Dst format.
    paudec->m_fmtI.nChannels = pau->m_cChannel; // from pWMAFormat.
    paudec->m_fmtI.nChannelMask = pau->m_nChannelMask; // from pWMAFormat.
    paudec->m_fmtI.nValidBitsPerSample = pau->m_nValidBitsPerSample; // The value comes from pWMAFormat
    // pau->m_nBytePerSample is the larger of the pWMAFormat and pPCMFormat container sizes, 
    // therefore it is also the size for internal data. Certainly it is the size of downmixing's input data.
    paudec->m_fmtI.cbPCMContainerSize = pau->m_nBytePerSample; 
    paudec->m_fmtI.pcmData = pau->m_dataType; // comes from pPCMFormat

    paudec->m_fmtO.nSamplesPerSec = paudec->m_iDstSamplingRate; // in chdownmix, data is already in Dst format.
    paudec->m_fmtO.nChannels = paudec->m_cDstChannel; // from pPCMFormat.
    paudec->m_fmtO.nChannelMask = paudec->m_nDstChannelMask; // from pPCMFormat.
    // paudec->m_nDstValidBitsPerSample usually from pWMAFormat but if it is 16 in pPCMFormat 
    // it will be 16. (paudec->m_fReQuantizeTo16)
    paudec->m_fmtO.nValidBitsPerSample = paudec->m_nDstValidBitsPerSample; 
    paudec->m_fmtO.cbPCMContainerSize = paudec->m_nDstBytePerSample;  // This is the output container size.
    paudec->m_fmtO.pcmData = pau->m_dataType; // comes from pPCMFormat

    if (paudec->m_fReQuantizeTo16)
    {
        assert (paudec->m_nDstValidBitsPerSample == 16);
        assert (paudec->m_nDstBytePerSample == 2);
        assert (paudec->m_fmtO.pcmData == PCMDataPCM);
    }

    TRACEWMA_EXIT (wmaResult, AVRHeadphoneNew (&(paudec->m_pVRHPhone), paudec->m_fmtI, paudec->m_fmtO));
#endif // #ifdef TEST_VRHEADPHONE

#if defined (BUILD_WMAPRO)
    paudec->m_fDRC = WMAB_FALSE;

    WMADebugMessage( " audecInit 15\n");      
    // this must be after requantizeTo16 flag is set.
	if (nPlayerOpt & PLAYOPT_DYNAMICRANGECOMPR) {
        TRACEWMA_EXIT(wmaResult,
            prvInitDecodeDRC(paudec, paudec->m_wmapi.nDRCSetting));
    }
#ifdef BOOST_CHANFLDDN_POWER
    else
    {
        if (paudec->m_fChannelFoldDown == WMAB_TRUE)
        {
        WMADebugMessage( " audecInit 16\n");      
        TRACEWMA_EXIT(wmaResult,
            prvInitDecodeDRC(paudec, WMA_DRC_HIGH));
        }
    }
#endif
#endif // BUILD_WMAPRO

    auInitPcInfoDEC (paudec);

    if (pWMAFormat->nChannels == 1)
        paudec->m_pfnDecodeCoefficient = &prvDecodeCoefficientMono;
    else
        paudec->m_pfnDecodeCoefficient = &prvDecodeCoefficientStereo;

    ibstrmInit (&paudec->m_ibstrm, paudec);

#ifdef CALLBACK_TEST
    ibstrmSetGetMoreData (&paudec->m_ibstrm, audecGetMoreData);
    ibstrmSetUserData (&paudec->m_ibstrm, &g_audecInputBuffer); //need to change for real streaming mode
#else
    if (pParams)
    {
        ibstrmSetGetMoreData (&paudec->m_ibstrm, pParams->pfnGetMoreData);
        ibstrmSetUserData (&paudec->m_ibstrm, pParams->dwUser); //need to change for real streaming mode
    }
#endif
    
    if (pau->m_iEntropyMode == SIXTEENS_OB)   {
        pau->m_rgpcinfo [0].m_rgiHuffDecTbl = g_rgiHuffDecTbl16smOb;
#if defined (WMA_OPT_VLC_DEC_ARM) && WMA_OPT_VLC_DEC_ARM
        pau->m_rgpcinfo [0].m_rgiHuffDecTbl_Pre = g_rgiHuffDecTbl16smOb_Pre;
#endif
        pau->m_rgpcinfo [0].m_rgiRunEntry   = gRun16smOb;
        pau->m_rgpcinfo [0].m_rgiLevelEntry = gLevel16smOb;
    }
#ifdef ENABLE_ALL_ENCOPT
    else if (pau->m_iEntropyMode == FOURTYFOURS_QB)   {
        pau->m_rgpcinfo [0].m_rgiHuffDecTbl = g_rgiHuffDecTbl44smQb; 
#if defined (WMA_OPT_VLC_DEC_ARM) && WMA_OPT_VLC_DEC_ARM
        pau->m_rgpcinfo [0].m_rgiHuffDecTbl_Pre = g_rgiHuffDecTbl44smQb_Pre; 
#endif
        pau->m_rgpcinfo [0].m_rgiRunEntry   = gRun44smQb; 
        pau->m_rgpcinfo [0].m_rgiLevelEntry = gLevel44smQb;
    }
    else if (pau->m_iEntropyMode == FOURTYFOURS_OB)   {
        pau->m_rgpcinfo [0].m_rgiHuffDecTbl = g_rgiHuffDecTbl44smOb; 
#if defined (WMA_OPT_VLC_DEC_ARM) && WMA_OPT_VLC_DEC_ARM
        pau->m_rgpcinfo [0].m_rgiHuffDecTbl_Pre = g_rgiHuffDecTbl44smOb_Pre; 
#endif
        pau->m_rgpcinfo [0].m_rgiRunEntry   = gRun44smOb; 
        pau->m_rgpcinfo [0].m_rgiLevelEntry = gLevel44smOb;
    }
#endif // ENABLE_ALL_ENCOPT
    else {
        assert (WMAB_FALSE);
        WMADebugMessage( " audecInit 17\n");      
        WMADebugMessage( " audecInit - fail 16\n"); 
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
   
    pau->m_codecStatus = CODEC_BEGIN;
    pau->m_iPacketCurr = -2;                // force a Packet Loss to begin

#ifdef BITRATE_REPORT
    WMAPrintf("Fr#\tSubF#\tTime\tPCM\tSF Bits\tSF Bitr\tFr Bits\tFr Bitrate\n");
    WMAPrintf("---\t-----\t----\t---\t-------\t-------\t-------\t----------\n");
#endif   // BITRATE_REPORT

    if (pParams) pParams->iMemBufUsed = auMallocGetCount();
    
    paudec->m_cChannelGroup = 0;

        WMADebugMessage( " audecInit 18\n");      
    TRACEWMA_EXIT(wmaResult, 
        prvAllocChannelGrpInfo((CChannelGroupInfo**)&(paudec->m_rgChannelGrpInfo), pau->m_cChannel));
    
#if defined (BUILD_WMAPRO)
    for (k = 0; k < paudec->pau->m_cChannel; k++) {
        paudec->m_rgChannelGrpInfo[k].m_rgfltMultiXForward = NULL;
        // No extra space needed at decoder for inverse: No inversion performed.
        paudec->m_rgChannelGrpInfo[k].m_rgfltMultiXInverse = (ChXFormType*) auMalloc(sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
        if (paudec->m_rgChannelGrpInfo[k].m_rgfltMultiXInverse == NULL) 
        {
            WMADebugMessage( " audecInit - fail 17\n"); 
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(paudec->m_rgChannelGrpInfo[k].m_rgfltMultiXInverse, 0, sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
    }
#endif // BUILD_WMAPRO

    // Set pointers to be used by common part
    pau->m_rgChannelGrpInfo     = paudec->m_rgChannelGrpInfo;
    pau->m_cChannelGroup = 0;


    // V3 LLM. chao. Add.
    // we have redundant bits to indicate pure lossless mode. One in FormatTag one in EncodeOpt.
    // The problem is we first used EncodeOpt and later moved it up to FormatTag but forget to remove
    // EncodeOpt stuff. So now we accept either or both of them as pure lossles mode flag. The encoder
    // dmo should set all of them but old encapp only set EncodeOpt.
    // must check m_iVersion since V2 and V3 have overlapped Encode Options
    if ((pau->m_iVersion >= 3 && (pau->m_iEncodeOpt&ENCOPT3_PURE_LOSSLESS)) || fLossless)
        pau->m_bPureLosslessMode = WMAB_TRUE;
    else
        pau->m_bPureLosslessMode = WMAB_FALSE;
    
    // We don't know it at the frame level. We have to decode into frames.
    pau->m_bEnforcedUnifiedLLM = WMAB_FALSE;

    // First subFrm is seekable.
    pau->m_bNextSbFrmCanBeSeekable = WMAB_TRUE;

    //oahc

    paudec->m_rgpiRecon =  (U8**)auMalloc(pau->m_cChannel * sizeof(U8*));
    if (paudec->m_rgpiRecon == NULL) {
        WMADebugMessage( " audecInit 19\n");      
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
    }
    memset(paudec->m_rgpiRecon, 0, pau->m_cChannel * sizeof(U8*));
    auMallocSetState(MAS_LOCKED, NULL, 0);

    paudec->m_externalState = INPUT_STATE;
    paudec->m_fNeedHeader = WMAB_TRUE;
    paudec->m_ibstrm.m_fNoMoreInput = WMAB_FALSE;

    paudec->m_fNewTimeBase = WMAB_FALSE;
    paudec->m_iNewTimeBase = ((I64)1 << 63);
    paudec->m_iNewTimeBaseTemp = ((I64)1 << 63);
    paudec->m_iTtlNTBs = 0;
    paudec->m_bBrokenFrame = WMAB_FALSE;

    if (paudecState) *paudecState = paudec->m_externalState;

#if defined(BUILD_WMAPROLBRV1)
    WMADebugMessage( " audecInit 20\n");      
    TRACEWMA_EXIT(wmaResult, audecPlusInit(paudec));
#endif

#ifdef BUILD_INTEGER
    //used for calling auPreScaleCoeffsV3()
    if (pau->m_cChannel != 1)
        pau->m_iLog2MaxIntvalCh =
            MAXINTVAL_CH_LOG2 - (LOG2(pau->m_cChannel-1)+1);
    else
        pau->m_iLog2MaxIntvalCh = MAXINTVAL_CH_LOG2;
#endif

    // UES: noticify UES that decoder is truly intialized
#ifdef BUILD_UES
    if(WMAB_TRUE == fUES)
    {
        TRACEWMA_EXIT(wmaResult, prvUESSetDecInit(paudec));
    }
#endif
    CCS_INIT();

    prvSetCodedChannels(pau);

    WMADebugMessage( " audecInit - pre-exit:\n"); 
exit:
    WMADebugMessage( " audecInit - exit:\n"); 

#if defined (VERIFY_PKT_SIGNATURE)
    if (g_fpSignDec)
    {
        FCLOSE(g_fpSignDec);
        g_fpSignDec = NULL;
    }
    g_fpSignDec = FOPEN("c:\\wmastreamsgn.dat", "rb");
#endif // VERIFY_PKT_SIGNATURE

    return wmaResult;
} // audecInit

#ifdef WMA_COMPRESSION_TOOL

WMARESULT audecInitCompressionTool (void* pDecHandle, 
                                    Bool fCompressionTool, 
                                    const char * pMetaFileDir,
                                    Bool fDumpMetaData,
                                    Bool fParsingOnly)
{
    WMARESULT   wmaResult = WMA_OK;
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    paudec->m_fWriteMetaFile = fCompressionTool;
    paudec->m_pMetaFileDir = pMetaFileDir; 
    paudec->m_fDumpMetaData = fDumpMetaData;
    paudec->m_fParsingOnly = fParsingOnly;
    return wmaResult;
}

WMARESULT audecGetFrameBits ( void *pDecHandle, 
                              WMA_I32 *piPCMFrameNumber, 
                              WMAFrameBitsInfo *pFrmBitInf,
                              WMA_U8  **ppbFrameBits)

{
    WMARESULT   wmaResult = WMA_OK;
    CAudioObjectDecoder *paudec = (CAudioObjectDecoder*)pDecHandle;
    CAudioObject *pau = paudec->pau;

    // support v3 is our first step.
    assert ( pau->m_iVersion >= 3 );
    // We assume external app always retrieve framebits on time. 
    // so m_fFrameBitsReady is either 0 or 1.
    assert ( paudec->m_fFrameBitsReady <= 1 );
    if ( paudec->m_fFrameBitsReady == 1 )
    {
        *piPCMFrameNumber = prvGetPCMFrameNumber (pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);
        pFrmBitInf->nHdr0Bits = 0;
        *ppbFrameBits = pau->m_rgbFrameBits;
        pFrmBitInf->nFrameBits = pau->m_cFrmUsedBitsFromParser;
        pFrmBitInf->nHdr1Bits = pau->m_cFrmHdrBitsFromParser;
        pFrmBitInf->cDuration = 0;        
        pFrmBitInf->iPresTime = paudec->m_iCurrPresTime;
        paudec->m_fFrameBitsReady--;
        if (pau->m_iFrameNumber > 1)
        {
            pFrmBitInf->cCurrSeekAdj = paudec->m_ulCurrSeekPoint;
        }
        else
        {
            //CTODO: first frame has leading slience = seekadj. so 
            // final seekadj is 0. Ideally when we compute the seekadj
            // we should take leading and trailing silence into consideration.
            pFrmBitInf->cCurrSeekAdj = 0;
        }
    }
    else
    {
        pFrmBitInf->nHdr0Bits = 0;
        *ppbFrameBits = NULL;
        pFrmBitInf->nFrameBits = 0;
        pFrmBitInf->nHdr1Bits = 0;
        pFrmBitInf->cDuration = 0;
        pFrmBitInf->cCurrSeekAdj = 0;
        pFrmBitInf->iPresTime = 0;
    }
    pFrmBitInf->cNextSeekAdj = (U32)(-1); // cNextSeekAdj is unknown now.
    return wmaResult;
}
#endif //WMA_COMPRESSION_TOOL

//*****************************************************************************************
//
// auInitPcInfoDEC
//
//*****************************************************************************************
Void auInitPcInfoDEC (CAudioObjectDecoder* paudec)
{
    I16 i;
    CAudioObject* pau = paudec->pau;
    I16 cSubband = (I16) pau->m_cFrameSampleHalfAdjusted;

    memset(paudec->m_rgpcinfoDEC, 0, sizeof(PerChannelInfoDEC) * pau->m_cChannel);

    for (i = 0; i < pau->m_cChannel; i++)
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + i;

        ppcinfo->m_ppcinfoShr = pau->m_rgpcinfoShr + i;

//      memset(ppcinfo->m_rgfltMask, 0, sizeof(ppcinfo->m_rgfltMask));
        ppcinfo->m_rgiCoefQ = NULL;
        ppcinfo->m_rgiMaskQ = pau->m_rgiMaskQ + NUM_BARK_BAND * i;
        ppcinfo->m_rgiMaskQResampled = pau->m_rgiMaskQResampled + NUM_BARK_BAND * i;
        ppcinfo->m_rgiHuffDecTbl = NULL;
        ppcinfo->m_rgiRunEntry = NULL;
        ppcinfo->m_rgiLevelEntry = NULL;
        ppcinfo->m_cSubbandActual = pau->m_cHighCutOff - pau->m_cLowCutOff;
        ppcinfo->m_iPower = 0;
        ppcinfo->m_iActualPower = 0;

#if defined(BUILD_WMAPROLBRV2) && (CX_DECODE_MONO==1)

        // in CX_DECODE_MONO, only a single channel of recon data is allocated
        // (per chex-pair). This was done in order to save memory. Here, avoid
        // initializing "CoefRecon" pointers to un-allocated memory.

        if ( !pau->m_bCx || pau->m_bEncoder || i < pau->m_pcx->m_iMaxPairs )
#endif
        {
            //TODO: Actually, LLM doesn't need 3/2 cSubband size.
            //ppcinfo->m_rgiWeightFactor: initialized below

            ppcinfo->m_rgiCoefRecon = pau->m_rgiCoefReconOrig + (cSubband*3/2)*i + (cSubband / 2);
            ppcinfo->m_rgCoefRecon  = (CoefType *)(ppcinfo->m_rgiCoefRecon); //This will soon be removed
        }

        ppcinfo->m_iMaxMaskQ = 0;
        ppcinfo->m_iCurrGetPCM_SubFrame = CURRGETPCM_INVALID;

        ppcinfo->m_fiSinRampUpStart = 0;
        ppcinfo->m_fiCosRampUpStart = 0;
        ppcinfo->m_fiSinRampUpPrior = 0;
        ppcinfo->m_fiCosRampUpPrior = 0;
        ppcinfo->m_fiSinRampUpStep = 0;
        ppcinfo->m_fiSinRampDownStart = 0;
        ppcinfo->m_fiCosRampDownStart = 0;
        ppcinfo->m_fiSinRampDownPrior = 0;
        ppcinfo->m_fiCosRampDownPrior = 0;
        ppcinfo->m_fiSinRampDownStep = 0;

#ifdef USE_SIN_COS_TABLES
        //MMX tables
        ppcinfo->m_piSinForRecon = NULL;
#endif
        ppcinfo->m_iSizePrev = 0;
        ppcinfo->m_iSizeCurr = 0;
        ppcinfo->m_iSizeNext = 0;
        ppcinfo->m_iCoefRecurQ1 = 0;
        ppcinfo->m_iCoefRecurQ2 = 0;
        ppcinfo->m_iCoefRecurQ3 = 0;
        ppcinfo->m_iCoefRecurQ4 = 0;
        ppcinfo->m_iCurrSubFrame = 0;
        ppcinfo->m_cSubFrameSampleHalf = 0;
    
        //ppcinfo->m_rgfltWeightFactor: initialized below
        ppcinfo->m_wtMaxWeight = 0; // Currently always used because LPC not integerized at encoder
    
        if (pau->m_iWeightingMode == LPC_MODE)
        { // LPC
            ppcinfo->m_rguiWeightFactor = pau->m_rguiWeightFactor + pau->m_cFrameSampleHalf * i;
#if defined(LPC_COMPARE)
            ppcinfo->m_rgfltWeightFactor = (float*)(pau->m_rguiWeightFactor + pau->m_cFrameSampleHalf * i);
#endif
        } 
        else 
        {
            ppcinfo->m_rguiWeightFactor =(U32*) pau->m_rgpcinfo [i].m_rgiMaskQ;
#if defined(LPC_COMPARE)
            ppcinfo->m_rgfltWeightFactor = (float*)(pau->m_rgpcinfo [i].m_rgiMaskQ);
#endif
        }

        ppcinfo->m_rgbBandNotCoded = NULL;
        ppcinfo->m_rgffltSqrtBWRatio = NULL;
        ppcinfo->m_rgiNoisePower = NULL;
#ifdef ENABLE_ALL_ENCOPT
        //set up default pcinfo for noise sub
        ppcinfo->m_rgbBandNotCoded   = pau->m_rgbBandNotCoded   + pau->m_cValidBarkBand * i;
        ppcinfo->m_rgffltSqrtBWRatio = pau->m_rgffltSqrtBWRatio + pau->m_cValidBarkBand * i;
        ppcinfo->m_rgiNoisePower     = pau->m_rgiNoisePower     + pau->m_cValidBarkBand * i;
#endif        
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame = 1;
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [0] = (I16) pau->m_cFrameSampleHalf;
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [-1] = (I16) pau->m_cFrameSampleHalf;
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart [0] = 0;

#if defined(BUILD_WMAPROLBRV2)
        if (WMAB_TRUE == pau->m_bReconProc)
        {
            chexInitPcInfo(pau, ppcinfo, i);
            chexInitPcInfoShr(pau, ppcinfo, i);
        }
#endif

        pau->m_rgpcinfo [i].ppcinfoENC = NULL;
    } // for
} // auInitPcInfoDEC

// this function called after seek or broken frame, not during cont. decode
WMARESULT audecReset (void* pDecHandle)
{
    WMARESULT wmaResult = WMA_OK;

    CAudioObjectDecoder *paudec = (CAudioObjectDecoder*)pDecHandle;
    CAudioObject* pau;
    Int iCh;

    if (paudec == NULL)
        return WMA_OK;
    pau = paudec->pau;
    
    if (pau == NULL)
        return WMA_OK;
    
	audecLog((paudec, "audecReset()\n"));

    // UES
#ifdef BUILD_UES
    if(WMAB_TRUE == paudec->pau->m_fUES)
    {
        UESdecReset(paudec->pau->m_pUES, paudec->m_pCUESdec);
        if(paudec->m_pCUESdec->m_fDecInitialized == WMAB_FALSE)
        {
            goto exit;
        }
    }
#endif
    //to suppress packet loss check
    ibstrmReset(&paudec->m_ibstrm);
    ibstrmSuppressPacketLoss(&paudec->m_ibstrm);
    ibstrmSetPacketHeader(&paudec->m_ibstrm, 0);
    ibstrmSetPacketHeaderT(&paudec->m_ibstrm, 0);
    
    // Reset PCM reconstruction variables
    memset(pau->m_rgiPCMInHistory, 0, sizeof(*pau->m_rgiPCMInHistory) * pau->m_cChannel);

    //moved to decodeInfo   
    //unlock ourself because there is an error already
    //wouldn't continue to decode the frame, making sure decodeInfo will be called
    pau->m_codecStatus = CODEC_BEGIN;

    //== to codec begin
    pau->m_iPacketCurr = -2;        //make sure we see a packet loss

    // Reset previous subframe size array
    pau->m_iPCMReconStart = 0;
    pau->m_iPCMReconEnd = 0;
    for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
        // These pointers will be correctly assigned in encoder and decoder
        pau->m_rgpcinfo[iCh].m_iSizePrev = (I16)(pau->m_cFrameSampleHalf/2);
        pau->m_rgpcinfo[iCh].m_iSizeCurr = pau->m_rgpcinfo[iCh].m_iSizePrev;
        pau->m_rgpcinfo[iCh].m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [-1] = (I16) pau->m_cFrameSampleHalf;
        pau->m_rgpcinfo[iCh].m_iCurrCoefPosition = 0;
    }
    
#ifdef WMA_COMPRESSION_TOOL
    // Reset members for Professional WMA encoder.
    pau->m_bSegDecode = WMAB_FALSE;
    pau->m_bSegDecodePeekMode = WMAB_FALSE;  
    pau->m_bPeekModeNonSekPkt = WMAB_FALSE;
    pau->m_bPeekModeDone = WMAB_FALSE;
    pau->m_cFrmsInSeg = 0;  
    pau->m_cPktsInSeg = 0;
#endif //WMA_COMPRESSION_TOOL

    paudec->m_fPacketLoss = WMAB_TRUE;
    paudec->m_bGotValidFilterInfo = WMAB_FALSE;
    ibstrmSetPrevPacketNum(&paudec->m_ibstrm, -2);
    paudec->m_iCurrPresTime = 0;    
    paudec->m_fContinuousDecodeAdj = WMAB_FALSE;
    paudec->m_iContinuousDecodeCountdown = 2;
    paudec->m_iSubfrmEscDataBits = 0;
    paudec->m_externalState = INPUT_STATE;
    paudec->m_fNeedHeader = WMAB_TRUE;
    paudec->m_ibstrm.m_fNoMoreInput = WMAB_FALSE;
    paudec->m_fltChannelFoldDownGain = 1.0F;
    paudec->m_bBrokenFrame = WMAB_FALSE;

    paudec->m_fNewTimeBase = WMAB_FALSE;
    // suppose 1 << 63 is not a valid time stamp.
    paudec->m_iNewTimeBase = ((I64)1 << 63);
    paudec->m_iNewTimeBaseTemp = ((I64)1 << 63);
    paudec->m_iTtlNTBs = 0;

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder Related
    paudec->m_ibstrm.m_iFrameStart = 0;
    paudec->m_ibstrm.m_iFrameEnd = 0;
    paudec->pau->m_cFrmUsedBitsFromParser = 0; //optional. Since fWriteMetaFile has been change to false.
#endif //WMA_COMPRESSION_TOOL

    // We need to reset paudec->m_decsts since in wmadec_s DecodeInfo may termiate a seek test (reach MAX_SEEK_DECODE)
    // with paudec->m_decsts == SEEK_TO_NEXT_PACKET and make the next seek test call DecodeInfo
    // using a wrong state (SEEK_TO_NEXT_PACKET). Please check bug # 2629
    paudec->m_decsts = BEGIN_PACKET;
    
#ifdef BUILD_WMAPROLBRV2
    TRACEWMA_EXIT(wmaResult, prvBasePlusReset (paudec));
#endif //

    // Reset operational variables
    TRACEWMA_EXIT(wmaResult, prvInitCommonResetOperational(pau));

    pau->m_bFirstPlusFrameAfterReset = WMAB_TRUE;
    pau->m_bFirstFrameAfterReset = WMAB_TRUE;

exit:
    return wmaResult;
} // audecReset


#if defined (VERIFY_PKT_SIGNATURE)
Void prvVerifyPktSignature(Bool fNewPacket,
                           I32 cPktLengthInBytes,
                           U8* pbIn, 
                           I32 cbIn)
{
    //assert(cbIn == cPktLengthInBytes);
    I32 cbLeft = cbIn;
    U8* pbTmp  = pbIn;

    if (g_fpSignDec)
    {
        if (fNewPacket)
        {
          //  assert(g_cPktBytesDone == 0);
        }
        while ((g_cPktBytesDone < cPktLengthInBytes) &&
            (cbLeft > 0))
        {
            g_unSign = g_unSign ^ *pbTmp;
            pbTmp++;
            g_cPktBytesDone++;
            cbLeft--;
        }
        if (g_cPktBytesDone == cPktLengthInBytes)
        {
            // Read one byte from file
            U8 unSignFromFile = 0;
            if (FREAD(&unSignFromFile, sizeof(U8), 1, g_fpSignDec) == 1)
            {
                assert(unSignFromFile == g_unSign);
            }
            g_cPktBytesDone = 0;
            g_unSign = 0;
        }
    }
} // prvVerifyPktSignature
#endif // VERIFY_PKT_SIGNATURE

WMARESULT audecInput (void* pDecHandle, WMA_U8* pbIn, WMA_U32 cbIn,
                                        WMA_Bool  fNewPacket, WMA_Bool fNoMoreInput,
                                        WMA_Bool  fTime, WMA_I64 rtTime,
                                        audecState* paudecState, audecInputParams* pParams)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    audecInputBufferInfo buf;
    WMARESULT hr = WMA_OK;
    
    if (paudec == NULL      || 
        paudec->pau == NULL ||
        (pbIn == NULL && cbIn != 0) ||
        paudecState == NULL)
    {
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
        goto exit;
    }

    assert(paudec->m_externalState == audecStateInput);
    
    // I think this logic could serve the non-SPDIF case as well, but I am afraid to make the change
    if (paudec->m_fSPDIF && paudec->m_fNeedHeader && !fNewPacket)
    {
        if (!paudec->m_ibstrm.m_pfnGetMoreData)
        {
            paudec->m_externalState = audecStateInput;
        }
        goto exit;
    }

    paudec->m_externalState = audecStateDone; // changed below on success

    memset(&buf, 0, sizeof(buf));
    buf.pbIn = pbIn;
    buf.cbIn = cbIn;
    buf.fTime = fTime;
    buf.rtTime = rtTime;
    buf.fNewPacket = fNewPacket;
    buf.fNoMoreInput = fNoMoreInput;
    if (pParams)
    {
        buf.pfnDescramble = pParams->pfnDescramble;
        buf.cSkipBits = pParams->cSkipBits;
    }

#ifdef CALLBACK_TEST
    memcpy(&g_audecInputBuffer, &buf, sizeof(g_audecInputBuffer));
#else
    assert(!paudec->m_ibstrm.m_pfnGetMoreData); // mixing callback with audecInput has problems - see ibstrmReset() call in audecDecode()
    
    TRACEWMA_EXIT(hr, paudec->m_pprvNewInputBuffer(paudec, &buf));
#endif

    if(WMAB_FALSE == paudec->pau->m_fUES)
    {
        paudec->m_externalState = audecStateDecode;
    }

exit:
    if (paudecState && paudec)
    {
        *paudecState = paudec->m_externalState;
    }
    return hr;
}

#if !defined(UNDER_CE)
//#pragma code_seg(push, no_bbtopt, ".no_bbt")
#endif

WMARESULT prvNewInputBuffer(CAudioObjectDecoder* paudec, audecInputBufferInfo* pBuf)
{
    WMARESULT hr = WMA_OK;
    WMA_U8*   pbIn = pBuf->pbIn;
    WMA_U32   cbIn = pBuf->cbIn;
    WMA_Bool  fNewPacket   = pBuf->fNewPacket;
    WMA_Bool  fNoMoreInput = pBuf->fNoMoreInput;
    WMA_Bool  fTime  = pBuf->fTime;
    WMA_I64   rtTime = pBuf->rtTime;
    WMA_I32   cSkipBits = pBuf->cSkipBits;

#if defined (VERIFY_PKT_SIGNATURE)
    prvVerifyPktSignature(fNewPacket, paudec->pau->m_cBitPacketLength >> 3, pbIn, cbIn);
#endif

    if (fNewPacket) {
        CCS_FRM_BDRY();
        if (fTime) {
            audecLog((paudec, "audecInput(%d) %d", cbIn, (int)(rtTime / 10000)));
        } else {
            audecLog((paudec, "audecInput(%d) no time", cbIn));
        }
    } else {
        audecLog((paudec, "audecInput(%d)", cbIn));
    }
    if (fNoMoreInput) {
        audecLog((paudec, "No more input"));
    }

    if (paudec->m_fSPDIF && !paudec->m_ibstrm.m_pfnGetMoreData && !paudec->m_fNeedHeader && fNewPacket)
    {
        assert(!"previous frame never completed ??"); // unexpected
        audecReset(paudec); // not sure this is enough
        paudec->m_fNeedHeader = WMAB_TRUE;
    }
    
    if (fNewPacket && fTime) {
        // We may have 0 or 1 saved NTB now but definitely no 2.
        if (paudec->m_iTtlNTBs > 1)
        {   
            // Naveent: Commented out this assert as a workaround for WinOS bug#876366
            // TODO: Identify & fix the problem.
            
            // when we see 2 NTB now, there is timestamp error. 
            // But we supress it by overwriting the last NTB.
            // assert (WMAB_FALSE);
            paudec->m_iTtlNTBs--;
        }
        // Compare the rtTime with the iNewTimeBase. If they are the same, we think this rtTime
        // is an useless TimeStamp. Because it will be overwritten by another TimeStamp without
        // being processed. (when big frame crossing mutiple packets.)
        // Notice that the iNewTimeBase here may or may not have been processed. If there is 
        // one saved valid NTB now, it must be NewTimeBase. Otherwise, NewTimeBase is the last
        // processed NTB.
        // One problem of this fix is it can not detect a timestamp error of a WMA file with 
        // same time stamp on each packet.
        if (paudec->m_iNewTimeBase != rtTime)
        {   // We got a new (different) TimeBase. We need to save it.
            if (paudec->m_fNewTimeBase == WMAB_FALSE)
            {   // No NTB in buffer. Load the rtTime to NewTimeBase.
                paudec->m_fNewTimeBase = WMAB_TRUE;
                paudec->m_iNewTimeBase = rtTime;    
                paudec->m_iTtlNTBs = 1;
            }
            else
            {   // 1 NTB in buffer. Load the rtTime to NewTimeBaseTemp.
                paudec->m_iNewTimeBaseTemp = rtTime;    
                paudec->m_iTtlNTBs ++;  // == 2;
                if (paudec->m_iTtlNTBs != 2)
                {
                    assert(WMAB_FALSE);
                    // Anyway, reset it and continue.
                    paudec->m_fNewTimeBase = 0;
                    paudec->m_iTtlNTBs = 0;

                }                    
            }
        }
    }
    CCS_START(CCS_ibstrmAttach);
    if (paudec->m_fSPDIF && fNewPacket)
    {
        ibstrmReset(&paudec->m_ibstrm);
    }
    else
    {
        assert(paudec->m_ibstrm.m_cbBuflen == 0);
        assert(paudec->m_ibstrm.m_pBuffer == paudec->m_ibstrm.m_pBufferBegin + paudec->m_ibstrm.m_cbBuflenBegin || !paudec->m_fSPDIF);
    }

#ifdef _WMA_DRM_DESCRAMBLE_
    if (pBuf->pfnDescramble)
    {
        TRACEWMA_EXIT(hr, ibstrmAttachP(&paudec->m_ibstrm,
                                       pBuf->pbIn, pBuf->cbIn,
                                       pBuf->fNewPacket, pBuf->fNoMoreInput,
                                       paudec->m_fSPDIF, paudec->pau->m_iVersion, pBuf->pfnDescramble));
    }
    else
#endif
    {
        TRACEWMA_EXIT(hr, ibstrmAttach(&paudec->m_ibstrm,
                                       pBuf->pbIn, pBuf->cbIn,
                                       pBuf->fNewPacket, pBuf->fNoMoreInput,
                                       paudec->m_fSPDIF, paudec->pau->m_iVersion));
    }
    CCS_END(CCS_ibstrmAttach);
    if (hr == WMA_S_LOSTPACKET) {
        int dummy;
        CAudioObject* pau = paudec->pau;
        audecLog((paudec, "...LOST_PACKET"));
        pau->m_codecStatus = CODEC_HEADER;
        paudec->m_fNeedHeader = WMAB_TRUE;
        dummy = TraceResult (hr);
    }

    if (paudec->m_fSPDIF)
    {
        if (!fNewPacket && cSkipBits)
        {
            TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
        }
        
        if (cSkipBits)
        {
            assert(pBuf->cbIn > 0);
            if (cSkipBits >= 8)
            {
                TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
            }

            assert(fNewPacket && (paudec->m_fNeedHeader || paudec->m_ibstrm.m_pfnGetMoreData));// cSkipBits only happens at the beginning of a frame

            // The gap location comes from decoding the frame header, so we can't be expecting
            // a gap yet (frame headers are degapped in pktpare.c by the SPDIF transmitter
            // during depacketization).
            assert(!paudec->m_ibstrm.m_fDeferredGap);

            // skip the gap
            ASSERTWMA_EXIT(hr, ibstrmFlushBits(&paudec->m_ibstrm, cSkipBits));
        }
    }

exit:
    return hr;
}

#if !defined(UNDER_CE)
//#pragma code_seg(pop, no_bbtopt)
#endif

//*****************************************************************************************
//
// audecDecode
//
//*****************************************************************************************
WMARESULT audecDecode (void* pDecHandle, WMA_U32* pcSamplesReady, audecState* paudecState,
                                         audecDecodeParams* pParams)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    WMARESULT hr = WMA_OK;
    CAudioObject* pau = NULL;
    U16 cSamplesReady;
#if !defined(BUILD_INTEGER)
    unsigned int origFPExceptionMask = DEFAULT_FP_EXCEPTION_MASK;
#endif
#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,DECODE_PACKET_PROFILE);
#endif

#if !defined(BUILD_INTEGER)
    prvDisableFPExceptions(&origFPExceptionMask);
#endif

    CCS_START(CCS_audecDecode);
    
    if (paudec == NULL      || 
        paudec->pau == NULL ||
        pcSamplesReady == NULL ||
        paudecState == NULL)
    {
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
        goto exit;
    }

    audecLog((paudec, "audecDecode()"));

    pau = paudec->pau;

    if (paudec->m_externalState != audecStateDecode) {
      assert(!"audecDecode called at an inappropriate time");
      TRACEWMA_EXIT(hr, WMA_E_WRONGSTATE);
    }
    paudec->m_externalState = audecStateDone; // changed below on success
    *pcSamplesReady = 0;
    
    if (pau->m_codecStatus == CODEC_DONE)
        goto exit; //we are done don't do anything

    if(WMAB_TRUE == pau->m_fUES)
    {
        paudec->m_fNeedHeader = WMAB_FALSE;
    }

    if (paudec->m_fNeedHeader)
    {
        I32 cIterations = 0;
        
        // audecNewInputBuffer() normally does this, but that's too late in callback mode.
        // But we can't reset the bstrm here in non-callback mode because ibstrmAttach()
        // has already happened.  So we do it here if and only if the callback is used.
        if (paudec->m_fSPDIF && paudec->m_ibstrm.m_pfnGetMoreData)
        { 
            ibstrmReset(&paudec->m_ibstrm);
        }
        
        do {
            audecLog((paudec, "  DecodeInfo()"));
            CCS_START(CCS_audecDecodeInfo);
            hr = prvDecodeInfo (paudec);
            CCS_END(CCS_audecDecodeInfo);
            if (hr != WMA_E_BROKEN_FRAME)
                break;
            
            audecLog((paudec, "...BROKEN_FRAME"));
            audecReset (paudec);        //codecsts will be begin
            if (cIterations++ > 1000000) {
                assert(!"DecodeInfo() appears to be stuck");
                hr = WMA_E_ONHOLD; // force new input
                break;
            }
        } while (1);
        
        if (hr == WMA_E_ONHOLD)
        {
            assert(!paudec->m_fSPDIF); // prvDecodeInfo() does very little in SPDIF mode
            audecLog((paudec, "...ONHOLD"));
            // m_codecStatus unchanged because we still need the header
#ifdef _WMA_DRM_DESCRAMBLE_
            ibstrmDetach(&paudec->m_ibstrm); // no-op for non-DRM
#endif
            paudec->m_externalState = (paudec->m_ibstrm.m_fNoMoreInput && !paudec->m_fSPDIF) ? audecStateDone : INPUT_STATE;
            hr = WMA_OK;
            goto exit;
        }
        
        CHECKWMA_EXIT(hr);
        paudec->m_fNeedHeader = WMAB_FALSE;
    }

    // If no superframes, WMA_S_NO_MORE_SRCDATA always happens at the end of
    // each frame and should constitute an exit condition. If superframes,
    // WMA_S_NO_MORE_SRCDATA should not exit this loop or we may not decode
    // last frame.
    HEAP_DEBUG_CHECK;
    cSamplesReady = 0;
    audecLog((paudec, "  DecodeData()"));
    CCS_START(CCS_audecDecodeData);
    hr = prvDecodeData (paudec, &cSamplesReady, NULL);
    CCS_END(CCS_audecDecodeData);
    HEAP_DEBUG_CHECK;

    *pcSamplesReady = cSamplesReady;
    if (paudec->pau->m_iXformSamplingRate != paudec->m_iDstSamplingRate)
    {
        *pcSamplesReady = prvNumDstSamplesFromXFormSamples(paudec, *pcSamplesReady);
    }

    if (hr == WMA_E_BROKEN_FRAME)
    {
        audecLog((paudec, "...BROKEN_FRAME"));
        audecReset (paudec);        //codecsts will be begin
        TraceResult (hr = WMA_OK); //map it to okay for the app
    }
    else if (hr == WMA_S_NO_MORE_FRAME)
    {
        audecLog((paudec, "...NO_MORE_FRAME"));
        paudec->m_fNeedHeader = WMAB_TRUE;
        pau->m_codecStatus = CODEC_HEADER;
        if (paudec->m_fSPDIF && pParams)
        {
#ifdef CALLBACK_STRESS
            pParams->cbFrameBytesInLastBuffer = -1; // paudec->m_ibstrm.m_pBufferBegin points in the middle of the user's buffer in this case
#else
            pParams->cbFrameBytesInLastBuffer = (U32)(paudec->m_ibstrm.m_pBuffer - paudec->m_ibstrm.m_pBufferBegin) - ibstrmBitsInDots(&paudec->m_ibstrm) / 8;
#endif
        }
    }
    else if (hr == WMA_E_ONHOLD)
    {
        // m_codecStatus unchanged because we are still decoding data
        audecLog((paudec, "...ONHOLD"));
        assert(cSamplesReady == 0);
        paudec->m_externalState = (paudec->m_ibstrm.m_fNoMoreInput && !paudec->m_fSPDIF) ? 
audecStateDone : INPUT_STATE;
#ifdef BUILD_UES
        if(WMAB_TRUE == pau->m_fUES)
        {
            if(paudec->m_pCUESdec->m_cbAudioPayloadLeft == 0) // something is wrong 
            {
                audecReset(paudec);
            }
        }
#endif
        TraceResult (hr = WMA_OK); //map it to okay for the app
    }
    else
    {
        pau->m_codecStatus = CODEC_DATA;
    }

    CHECKWMA_EXIT(hr);
    
exit:

    //FUNCTION_PROFILE_STOP(&fp);
    HEAP_DEBUG_CHECK;
    if (WMA_FAILED(hr)) {
        audecLog((paudec, "...%08X", hr));
        if (paudec)
            paudec->m_externalState = audecStateDone;
    }

    CCS_END(CCS_audecDecode);

    if (paudec &&
        (paudec->m_fSPDIF || paudec->pau->m_fUES)&& 
        paudec->m_fNeedHeader && 
        paudec->m_externalState == audecStateDecode)
    {
        paudec->m_externalState = INPUT_STATE;
    }
    // UES mode
//#ifdef BUILD_UES
    if(WMAB_TRUE == paudec->pau->m_fUES)
    {
        WMADebugMessage(" UES present !!!! \n");
#ifdef BUILD_UES
        if(paudec->m_cFrmInPacket == 0 )
        {
            if(paudec->m_pCUESdec->m_cbAudioPayloadLeft>0)
            {
                // possible packet loss
                audecReset(paudec);
            }
            if(paudec->m_ibstrm.m_dwBitsLeft<=7 && paudec->m_ibstrm.m_cbBuflen==0)
            {
                paudec->m_ibstrm.m_dwBitsLeft = 0; // possible padding bits
            }
            if( paudec->m_ibstrm.m_dwBitsLeft>=8 || paudec->m_ibstrm.m_cbBuflen>0)
            {
                audecReset(paudec);
            }
        }
        if(paudec->m_externalState == audecStateInput && paudec->m_pCUESdec->m_cbIn != 0)
        {
            audecInput (paudec, 
                        paudec->m_pCUESdec->m_pbIn, 
                        paudec->m_pCUESdec->m_cbIn,
                        WMAB_FALSE, 
                        WMAB_FALSE, // WMA_Bool fNoMoreInput,
                        WMAB_FALSE,  // WMA_Bool  fTime, 
                        0, //WMA_I64 rtTime,
                        &paudec->m_externalState, 
                        NULL); //audecInputParams* pParams
        }
#endif
    }
//#endif
    if (paudec && paudecState)
        *paudecState = paudec->m_externalState;

#ifdef WMA_COMPRESSION_TOOL
    if (paudec && 
        paudec->pau && 
        paudec->m_fWriteMetaFile == WMAB_TRUE)
    {
        // we are going to get new input and call audecInput. Before we do that, we have to dump the 
        // data of curr input if necessary.
        if (paudec->m_externalState == audecStateInput)
        {
            hr = ibstrmDumpFrmBitsPreGetMoreData(&paudec->m_ibstrm, paudec->pau->m_iFrameNumber, paudec->pau->m_iVersion);                                    
        }
    }
#endif //WMA_COMPRESSION_TOOL


#if !defined(BUILD_INTEGER)
    prvRestoreFPExceptions(origFPExceptionMask);
#endif
    return hr;
} // audecDecode


void prvRotateTimestampQueue( CAudioObjectDecoder *paudec )
{
    // Do we always have paudec->m_fNewTimeBase == TRUE here? (before this checkin) 
    // FALSE means TimeStampe error?
    // If fNewTimeBase is always TRUE here, we can have a much simpler solution
    // by binding the NTB queue and the PktHdr queue. Everytime PktHdr queue moves
    // NTB queue follows it. 
    // That method is simple but the current method also has advantage. 
    // It can check the timestamp after decodeframe done. No need
    // to proceed to call DecodeInfo to get the correct timestamp.
//    assert(paudec->m_fNewTimeBase == WMAB_TRUE);

    if (paudec->m_fNewTimeBase == WMAB_TRUE)
    {
        if (paudec->m_iTtlNTBs == 1)
        {
			audecLog((paudec, "- NTB #1 -" ));

            //convert 100ns to samples
            paudec->m_iCurrPresTime = paudec->m_iNewTimeBase * 
                                      paudec->m_iDstSamplingRate / 10000000;
            paudec->m_fNewTimeBase  = WMAB_FALSE;
            paudec->m_iTtlNTBs--;
        }
        else if (paudec->m_iTtlNTBs == 2)
        {
			audecLog((paudec, "- NTB #2 -" ));

            paudec->m_iCurrPresTime = paudec->m_iNewTimeBase * 
                                      paudec->m_iDstSamplingRate / 10000000;
            paudec->m_iNewTimeBase  = paudec->m_iNewTimeBaseTemp;
            paudec->m_iTtlNTBs--;
        }
        else
        {
            // with the fix in audecInput we should not hit this assert.
            assert(WMAB_FALSE);
            // Anyway, reset.
            paudec->m_fNewTimeBase = WMAB_FALSE;
            paudec->m_iTtlNTBs = 0;
        }
        // We crossed a packet boundary. However, we have not read the frame
        // header yet. Once we've read the frame header, then we can apply
        // continuous decode adjustment.
        paudec->m_fContinuousDecodeAdj = WMAB_TRUE;

#if defined(WMA_SEEK_MATCH)
        paudec->pau->m_tRandState.iPrior = (I32) (paudec->m_iNewTimeBase >> 32);
        paudec->pau->m_tRandState.uiRand = (U32) (paudec->m_iNewTimeBase >> 32);
        quickRand (&(paudec->pau->m_tRandState));
        quickRand (&(paudec->pau->m_tRandState));
        quickRand (&(paudec->pau->m_tRandState));
#endif
    }
}

//*****************************************************************************************
//
// prvDecodeInfo
//
//*****************************************************************************************
WMARESULT prvDecodeInfo (CAudioObjectDecoder* paudec)
{   
    Int cBitLeftOver = 0;
    Int cBitLs, cBitRs;
    WMARESULT   wmaResult = WMA_OK;
    I32  nBitsFrmCnt = 0; 
    CAudioObject* pau = NULL;
    I16 i;

    if (paudec == NULL) {
        TRACEWMA_EXIT (wmaResult, WMA_E_INVALIDARG);
        goto exit;
    }
    
    pau = paudec->pau;
    if (pau == NULL) {
        TRACEWMA_EXIT (wmaResult, WMA_E_INVALIDARG);
        goto exit;
    }
    
    //for v3, do after header decoding
    if (pau->m_iVersion <= 2)
    {
        nBitsFrmCnt = NBITS_FRM_CNT;
    }

    if (paudec->m_decsts == SEEK_TO_NEXT_PACKET)
      goto seekToNextPacket;

    paudec->m_decsts = BEGIN_PACKET;
    paudec->m_cFrmInPacket = 1;

    if (paudec->m_fSPDIF)
    {
        wmaResult = WMA_OK;
        goto exit;
    }

    if (pau->m_fAllowSuperFrame || pau->m_iVersion > 2)
    {
        //no left over
NEXT_HDR:
        while(ibstrmGetPacketHeader(&paudec->m_ibstrm) == 0) 
        {
            CWMAInputBitStream* pibs = &paudec->m_ibstrm;

            if (ibstrmGetPacketHeaderT(&paudec->m_ibstrm) == 0)
            {
                ibstrmReset(pibs);
                //theoretically we can be on-hold but not tested as apcx don't do this
                TRACEWMA_EXIT(wmaResult, ibstrmGetMoreData(&paudec->m_ibstrm, ModePktHdr, WMA_get_nHdrBits(paudec)));
            }
            else 
            {
                ibstrmSetPacketHeader(pibs, ibstrmGetPacketHeaderT (pibs));
                ibstrmSetPacketHeaderT(pibs, 0);
            }
        }

        if (pau->m_iVersion <= 2)
        {
            cBitLs = NBITS_PACKET_CNT;
            cBitRs = BITS_PER_DWORD - nBitsFrmCnt;
            paudec->m_cFrmInPacket = (U16) ((ibstrmGetPacketHeader(&paudec->m_ibstrm) 
                                     << cBitLs) >> cBitRs);
            //assert (paudec->m_cFrmInPacket < (1 << nBitsFrmCnt));
            cBitLs = NBITS_PACKET_CNT + nBitsFrmCnt;
            cBitRs = BITS_PER_DWORD - (pau->m_cBitPackedFrameSize + 3); 
            cBitLeftOver = (ibstrmGetPacketHeader(&paudec->m_ibstrm) << cBitLs) >> cBitRs;
            paudec->m_cBitSeekToNextPacket = cBitLeftOver;
            paudec->m_cBitsOverCurrPkt = cBitLeftOver;
            // TODO: when we see a cFrmInPacket == 0, should we goto the next hdr directly
            // now? (like V3). Currently, in V2, it is done later when decoder tries
            // to decode the next framehdr.
#ifdef WMA_COMPRESSION_TOOL            
            // in v2 suc a frame can be treated as seekable. Actually it is the same in v3 but v3 will indicate
            // it is nonseekable at pkthdr. should be fine for both case.
            if (pau->m_bSegDecodePeekMode == WMAB_TRUE)
            {
                if (paudec->m_cFrmInPacket == 0)
                    pau->m_bPeekModeNonSekPkt = WMAB_TRUE;
            }
#endif //WMA_COMPRESSION_TOOL
        }
        else
        {
//            U8 iVal;      
            U32 dwHdr = ibstrmGetPacketHeader(&paudec->m_ibstrm);
            //get 1 bit
            cBitLs = NBITS_PACKET_CNT;
            cBitRs = BITS_PER_DWORD - NBITS_PACKET_EMPTYNESS;

            paudec->m_cSeekableFrmInPacket = (I16) ((dwHdr << cBitLs) >> cBitRs); // 1 bit
#ifdef BUILD_WMAPROLBRV2
            // CTODO: Baseplus is not reading seekable info from bitstream now. It just relies on m_iTempPredRefOffset.
            //        In future we might need to read seekable info to catch bitstream syntax error. 
            // pau->m_bSeekable = paudec->m_cSeekableFrmInPacket;
#endif //BUILD_WMAPROLBRV2
            cBitLs += (NBITS_PACKET_EMPTYNESS);
            cBitRs = BITS_PER_DWORD - NBITS_FORCE_PACKETLOSS;

            // Forced Packet loss has been (and should be) taken care in ibStrmAttach function.

            cBitLs += (NBITS_FORCE_PACKETLOSS);
            cBitRs = BITS_PER_DWORD - pau->m_cBitPackedFrameSize;


            cBitLeftOver = ((dwHdr << cBitLs) >> cBitRs);

            paudec->m_cBitSeekToNextPacket = cBitLeftOver;
            paudec->m_cBitsOverCurrPkt = cBitLeftOver;
            cBitLs += pau->m_cBitPackedFrameSize;

            if (paudec->m_cSeekableFrmInPacket == 1) {

				audecLog((paudec, "-- seekable packet\n" ));

                // Seekable Packet must have a frame starting in it and the offset obviously has a valid value.
                paudec->m_cFrmInPacket = 1;
                if (!(cBitLeftOver + cBitLs < pau->m_cBitPacketLength)) {
                    REPORT_BITSTREAM_CORRUPTION();
                    return WMA_E_BROKEN_FRAME;
                }
            }
            else {
				
				audecLog((paudec, "-- NON-seekable packet\n" ));

                // (Removed : In LLM, )we use offset to check if there is frame starting in this packet.
                // If the offset value is not valid (overflow, point outside the packet), we know this is
                // a packet without a frame starting in it.
                if (cBitLeftOver + cBitLs >= pau->m_cBitPacketLength) {
                    paudec->m_cFrmInPacket = 0;
                    // drop off 1 timestamp from the timestamp queue. Normally the dropped timestamp is not supposed
                    // to be used by any frame since no frame starting from this packet. Previously we don't need to 
                    // drop it since next packet will have the same timestamp so it will be NOT pushed into the queue. But
                    // in editing scenario or when encoder gets discontinued input timestamp, next packet's timestamp
                    // could be different and we end up with one extra timestamp in the queue forever. 
                    // But please note in some special cases we may drop a valid timestamp. It should be ok. 
                    // special case:
                    /*
			|******XXX|XXXXXXXXX_|*****XXXXXX| 
                        '|' packet boundary
                        '*' frame 1 and 3
                        'X' frame 2 and 4
                    */
                    prvRotateTimestampQueue( paudec );
                }
                else {
                    paudec->m_cFrmInPacket = 1;
                    // After MLLMUsePLLM is added, lossy is not always seekable.
                    /*
                    // we suppose all frames are seekable in lossy.
                    if (!(paudec->pau->m_bPureLosslessMode == WMAB_TRUE)) {
                        assert(!"corrupt bitstream");
                        return WMA_E_BROKEN_FRAME;
                    }
                    */
                }
#ifdef WMA_COMPRESSION_TOOL
                if (pau->m_bSegDecodePeekMode == WMAB_TRUE)
                {
                    pau->m_bPeekModeNonSekPkt = WMAB_TRUE;
                }
#endif //WMA_COMPRESSION_TOOL
            }
   
            // A more clear logic:
            if (paudec->m_fPacketLoss == WMAB_FALSE) {
                // not seeking
                if (paudec->m_cFrmInPacket == 0) {
                    /* 
                        2)  description 1) is not accurate. We have queue of two packethdrbuf 
                            (pibs->m_dwHeaderBuf and pibs->m_dwHeaderBufTemp). When a packet is in, 
                            its header first go to pibs->m_dwHeaderBufTemp. And the original content in pibs->m_dwHeaderBufTemp 
                            goes to pibs->m_dwHeaderBuf. Therefore, when we see a FrmInPacket == 0 here, there are
                            two possibilities: 
                            a) pibs->m_dwHeaderBuf IS the header of current packet. The current packet underflows
                            b) pibs->m_dwHeaderBuf is acutally the packet header of previous packet, the current
                               packet's header is in pibs->m_dwHeaderBufTemp. This case means that one frame uses 
                               the whole previous packet. Underflowing of previous packet is not possible here. Since 
                               if it was underflow, we should have decoded previous packet's header in previous DecodeInfo call.
                               (Each trailing bit == 0 inits a DecodeInfo call and DecodeInfo call consumes the packetheader 
                               of current packet. But if one frame overlap multiple packets, some packets do not have chance 
                               to trigger DecodeInfo Call. Their packet headers are pushed into the queue).
                        1) no more frame in packet, move to next packet
                    */
                    ibstrmSetPacketHeader(&paudec->m_ibstrm, 0);
                    goto NEXT_HDR;                   
                }
            }
            else if (paudec->m_fPacketLoss == WMAB_TRUE) {
                // seeking
                if (paudec->m_cSeekableFrmInPacket == 0)
                {
                    // no seekable frame in packet, set packet loss status and move to next packet.
                    ibstrmSetPrevPacketNum(&paudec->m_ibstrm, -2);
                    ibstrmSetPacketHeader(&paudec->m_ibstrm, 0);
                    // suppress packetloss when seeking. getmoredata will ignore packetloss signal and move forward.
                    ibstrmReset(&paudec->m_ibstrm);
                    ibstrmSuppressPacketLoss(&paudec->m_ibstrm);

                    // drop off 1 timestamp from the timestamp queue.
                    prvRotateTimestampQueue( paudec );

                    goto NEXT_HDR;
                }
            }

////            
            //no frm staring in this packet; //move the queue
            if (cBitLeftOver + cBitLs >= pau->m_cBitPacketLength)
            {
                // we think this block is redundent with the if (paudec->m_cFrmInPacket == 0) block.
                // we think the decoder never enters this block.
                // we will remove it if the testing verifies our assumption.
                assert(WMAB_FALSE);
                if (paudec->m_fPacketLoss == WMAB_TRUE)
                    ibstrmSetPrevPacketNum(&paudec->m_ibstrm, -2);
                ibstrmSetPacketHeader(&paudec->m_ibstrm, 0);
                goto NEXT_HDR;
            }
        }

        if (cBitLeftOver == 0) 
            ibstrmResetPacket(&paudec->m_ibstrm);
        ibstrmSetPacketHeader(&paudec->m_ibstrm, 0);
    } // if (pau->m_fAllowSuperFrame || pau->m_iVersion > 2)
    else 
    {
        Int iCurrPrevDiff;
        paudec->m_fPacketLoss = WMAB_FALSE;
        // We should only hit this on very first frame
        if (pau->m_iPacketCurr < 0)
        {
            //In callbackless mode, we've already read the packet header
            //assert(ibstrmGetPacketHeader(&paudec->m_ibstrm) == 0);
            pau->m_iPacketCurr = 0;
            paudec->m_fPacketLoss = WMAB_TRUE;
        }

        iCurrPrevDiff = ibstrmGetPacketHeader(&paudec->m_ibstrm) -
            pau->m_iPacketCurr;

        // Non-superframe mode can't really lose packets
#if defined (BITSTREAM_CORRUPTION_ASSERTS)
        // These assertions can get triggered by corrupted bitstreams.
        assert(iCurrPrevDiff >= 0 || iCurrPrevDiff <= 1 - NONSUPER_WRAPAROUND);
        assert(iCurrPrevDiff < 0 || iCurrPrevDiff <= 1);
        assert(iCurrPrevDiff >= 0 || NONSUPER_WRAPAROUND + iCurrPrevDiff <= 1);
#endif // BITSTREAM_CORRUPTION_ASSERTS

        // If, while processing the last frame we loaded in the start of next frame,
        // cue bitstream pointer to start of next frame
        if (iCurrPrevDiff != 0)
        {
            ibstrmFlushOldBits(&paudec->m_ibstrm); // used to be ibstrmResetPacket, but that caused problems for DRM
        }

        // Advance to next payload: discard data until we hit next frame
        while (ibstrmGetPacketHeader(&paudec->m_ibstrm) == (U32)pau->m_iPacketCurr)
        {
            ibstrmReset(&paudec->m_ibstrm);
            TRACEWMA_EXIT(wmaResult, WMA_E_ONHOLD);
        }

        pau->m_iPacketCurr = ibstrmGetPacketHeader(&paudec->m_ibstrm);
    } // if (!pau->m_fAllowSuperFRame && pau->m_iVersion <= 2)

    prvRotateTimestampQueue( paudec );


#if defined(SEEK_DECODE_TEST)
    if (paudec->m_pSaveRandState != NULL ) {
        *paudec->m_pSaveRandState = pau->m_tRandState;
        paudec->m_pSaveRandState = NULL;
    }
#   endif // SEEK_DECODE_TEST

    if (paudec->m_fPacketLoss == WMAB_FALSE)
    {
        wmaResult = WMA_OK;
        goto exit;
    }
    else    
    {
        seekToNextPacket:

        paudec->m_decsts = SEEK_TO_NEXT_PACKET;

        //packet loss or a broken frame earlier, seek to next complete frm
        //need to redecode trailer bits
        while (paudec->m_cBitSeekToNextPacket > 24)   {
            TRACEWMA_EXIT(wmaResult, ibstrmFlushBits (&paudec->m_ibstrm, 24));
            paudec->m_cBitSeekToNextPacket -= 24;
        }
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits (&paudec->m_ibstrm, paudec->m_cBitSeekToNextPacket));

        for (i = 0; i < pau->m_cChannel; i++)
        {
            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + i;
            ppcinfo->m_iCurrGetPCM_SubFrame = (I16) CURRGETPCM_INVALID;
        }

        pau->m_codecStatus = CODEC_BEGIN;
        paudec->m_decsts = BEGIN_PACKET;

        // Ignore packet loss, we're already set to deal with it
        wmaResult = WMA_OK; // WMA_BROKEN_FRAME;
        goto exit;
    }
        
exit:

    assert (paudec && paudec->m_cFrmInPacket >= 0);

    return wmaResult;
} // prvDecodeInfo


#ifdef BITRATE_REPORT
#define BITRATE_REPORT_VARS         Int cBitGet
#define BITRATE_REPORT_CHECKPT      cBitGet = g_cBitGet
#define BITRATE_REPORT_PRINT        PrintSubframeStats(paudec, cBitGet)

Float g_fltRunningTime = 0;
Int g_cSubframeBits = 0;

void PrintSubframeStats(const CAudioObjectDecoder *paudec, const Int cBitGetCheckPt)
{
    CAudioObject* pau = paudec->pau;
    Int iSubframePCM;
    Int iBitsInSubframe;
    Float fltSubframeTime;

    iSubframePCM = pau->m_cSubbandAdjusted;
    iBitsInSubframe = g_cBitGet - cBitGetCheckPt;
    fltSubframeTime = iSubframePCM / (float)pau->m_iSamplingRate;

    // Print frame number only for first subframe (helps with visual formatting)
    if (0 == paudec->m_iCurrTile)
        WMAPrintf("%d\t", pau->m_iFrameNumber);
    else
        WMAPrintf("\t");

    // Print subframe stats
    WMAPrintf("%d\t%6.3f\t%4d\t%6d\t%7.0f", paudec->m_iCurrTile,
        g_fltRunningTime, iSubframePCM, iBitsInSubframe,
        iBitsInSubframe / fltSubframeTime);

    g_fltRunningTime += fltSubframeTime;
    g_cSubframeBits += iBitsInSubframe;

    // If last subframe in frame, print frame summary
    if (paudec->m_iCurrTile + 1 >= pau->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame)
    {
        const Float fltFrameTime = (float)(2048.0 / pau->m_iSamplingRate);
        WMAPrintf("\t%6d\t%7.0f\n", g_cSubframeBits, g_cSubframeBits / fltFrameTime);
        g_cSubframeBits = 0;
    }
    else
        WMAPrintf("\n");
} // PrintSubframeStats
#else    // BITRATE_REPORT
#define BITRATE_REPORT_VARS
#define BITRATE_REPORT_CHECKPT
#define BITRATE_REPORT_PRINT
#endif  // BITRATE_REPORT

#if 0
#pragma COMPILER_MESSAGE("--- Warning: Dumping code defined ---")
void ccReadDump(int x, int shift, CAudioObject *pau)
{
  static int first = 1;
  static FILE *fp[10][10];
  static float *buf = NULL;
  static char fname[100];
  static int xread, chread, read;
  int i, j, ch;
  PerChannelInfo *ppcinfo;
  static int count[10][10], count2[10][10];
  int end;

  if (first) {
    for (i=0; i < 10; i++) for (j=0; j < 10; j++) {
      fp[i][j] = NULL;
      count[i][j] = 0;
      count2[i][j] = 0;
    }
  }
  if (buf == NULL) {
    buf = (float*)auMalloc(pau->m_cFrameSample*sizeof(float));
    assert(buf);
  }
  if (first) {
    FILE *f = NULL;
    f = FOPEN("dumpargs.txt", "rt");
    if (f == NULL) {
      read = 0;
      sprintf(fname, "%s", "");
      xread = 1000;
      chread = 1000;
    } else {
      fscanf(f, "%d", &read);
      fscanf(f, "%s", fname);
      fscanf(f, "%d", &xread);
      fscanf(f, "%d", &chread);
      FCLOSE(f);
    }
  }
  if (x!=xread && xread!=-1) goto exit;
  if (x < 10) {
    char name[100];
    for (i=0; i < pau->m_cChInTile; i++) {
      ch = pau->m_rgiChInTile[i];
      if (ch!=chread && chread!=-1) continue;
      ppcinfo = &pau->m_rgpcinfo[ch];
      assert(ppcinfo->m_cSubFrameSampleHalf <= pau->m_cFrameSample);
      if (fp[x][ch] == NULL) {
        if (strlen(fname) != 0) {
          sprintf(name, "%s.%d.%d", fname, x, ch);
        } else {
          sprintf(name, "recon.raw.%d.%d", x, ch);
        }
        if (read) {
          fp[x][ch] = FOPEN(name, "rb");
        } else {
          fp[x][ch] = FOPEN(name, "wb");
        }
      }
      if (shift == 10) {
        end = ppcinfo->m_cSubbandActual;
        if (ppcinfo->m_rgiCoefQ == NULL) end = 0;
      } else {
        end = ppcinfo->m_cSubFrameSampleHalf;
      }
      if (read) {
        //int zz;
        //zz = FTELL(fp[x][ch]);
        //WMAPrintf("X=%d Ch=%d Position = %d Read = %d\n", x, ch, zz, zz/4);
        FREAD(buf, sizeof(float), end, fp[x][ch]);
        //zz = FTELL(fp[x][ch]);
        //WMAPrintf("X=%d Ch=%d Position = %d Read = %d\n", x, ch, zz, zz/4);
      }
      for (j=0; j < end; j++) {
        if (read) {
          if (shift == 10) {
            ppcinfo->m_rgiCoefQ[j] = (int)buf[j];
          } else {
#ifdef BUILD_INTEGER
            if (shift == 1) // post inverse quantization
              ppcinfo->m_rgiCoefRecon[j] = WMACFFPQ(buf[j]);
            else if (shift == 2 || shift == 0) // pre inverse quantization
              ppcinfo->m_rgiCoefRecon[j] = WMACFF(buf[j]);
#else
            ((float*)ppcinfo->m_rgiCoefRecon)[j] = buf[j];
#endif
          }
        } else {
          if (shift == 10) {
            buf[j] = (float)ppcinfo->m_rgiCoefQ[j];
          } else {
#ifdef BUILD_INTEGER
            if (shift == 1) // post inverse quantization
              buf[j] = WMAFFCPQ(ppcinfo->m_rgiCoefRecon[j]);
            else if (shift == 2 || shift == 0) // pre inverse quantization
              buf[j] = WMAFFC(ppcinfo->m_rgiCoefRecon[j]);
#else
            buf[j] = ((float*)ppcinfo->m_rgiCoefRecon)[j];
#endif
          }
        }
        count[x][ch]++;
      }
      if (!read) {
        FWRITE(buf, end, sizeof(float), fp[x][ch]);
        FFLUSH(fp[x][ch]);
      }
      count2[x][ch] += ppcinfo->m_cSubFrameSampleHalf;
#if 0
      if (count2[x][ch] >= 6563905 && x==0) {
          WMAPrintf("Problem at coeff = %d",
                 6563905-(count2[x][ch]-ppcinfo->m_cSubFrameSampleHalf));
          g_break = 1;
      }
#endif
    }
  }
exit:
  if (first) first = 0;
}
#define CCDUMP(x, shift) ccReadDump(x, shift, pau)
#else
#define CCDUMP(x, shift)
#endif

//#define PRINT_SUBFRAME_SEGMENTS

#ifdef PRINT_SUBFRAME_SEGMENTS

Void prvPrintSubframeSegments(CAudioObjectDecoder *paudec)
{
    CAudioObject *pau = paudec->pau;
    static Int iTileCnt = 0;
    static Int iPrevFrameNum = 0;
    static Int iFrameTileCnt = 0;
    static Int iSampleCnt[16];
    static Float cSampleRate;
    Int iCh, cSubframeSize;

    if (pau->m_cChannel > 16)
    {
        assert(WMAB_FALSE);
        return;
    }
    if (iTileCnt == 0)
    {
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
            iSampleCnt[iCh] = -pau->m_rgiDiscardSilence[iCh];
        cSampleRate = (Float)pau->m_iSamplingRate;
    }

    if (SUBFRM_DONE == paudec->m_subfrmdecsts)
    {
        if (iPrevFrameNum != (Int)pau->m_iFrameNumber)
        {
            iPrevFrameNum = (Int)pau->m_iFrameNumber;
            iFrameTileCnt = 0;
        }

        cSubframeSize =
          pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubFrameSampleHalf;
        printf("%4d %2d %6d %5d %8d %8d %7.3f %7.3f ",
               pau->m_iFrameNumber, iFrameTileCnt,
               iTileCnt, cSubframeSize,
               iSampleCnt[pau->m_rgiChInTile[0]],
               iSampleCnt[pau->m_rgiChInTile[0]]+cSubframeSize,
               iSampleCnt[pau->m_rgiChInTile[0]]/cSampleRate,
               (iSampleCnt[pau->m_rgiChInTile[0]]+cSubframeSize)/cSampleRate);
        for (iCh=0; iCh < pau->m_cChInTile; iCh++)
        {
            printf("%1x", pau->m_rgiChInTile[iCh]);
            iSampleCnt[pau->m_rgiChInTile[iCh]] += cSubframeSize;
        }
        printf("\n");
        iTileCnt++;
        iFrameTileCnt++;
    }
}

#endif // PRINT_SUBFRAME_SEGMENTS

//*****************************************************************************************
//
// prvDecodeData
//
//*****************************************************************************************
WMARESULT prvDecodeData (CAudioObjectDecoder* paudec, 
                           U16* pcSampleReady, 
                           I16* pcSampleSeekAdj)
{
    CAudioObject* pau = paudec->pau;
    PerChannelInfo* ppcinfo = pau->m_rgpcinfo;
    WMARESULT hr = WMA_OK;
    I16 iCh, iChSrc;
    I16 cSampleSeekAdj;

#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,AUDEC_DECODE_DATA_PROFILE);
#endif

    if (paudec == NULL || pcSampleReady == NULL) {
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
        goto exit;
    }
    // pcSampleSeekAdj can be NULL

    pau = paudec->pau;
    
    if (pau == NULL) {
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
        goto exit;
    }

    ppcinfo = pau->m_rgpcinfo;
    
    assert (pcSampleReady != NULL);
    *pcSampleReady = 0;
    if (pcSampleSeekAdj != NULL)
        *pcSampleSeekAdj = 0;
    //if we are being resumed, we need to get the new data
    while(1)
    {
        BITRATE_REPORT_VARS;
        switch (paudec->m_decsts)
        {
            case BEGIN_SUBFRAME :
                if (!paudec->m_fLastSubFrame) 
                {                   
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                    {
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;
                        // We no used to check on the value of ppcinfo->m_iCurrGetPCM_SubFrame
                        // here, but this is no longer valid due to lazy reconstruction and
                        // history buffer in-place reconstruction.

                        // Effectively disable GetPCM in case we find broken frame or packet
                        // (disingenuous caller maps WMA_E_LOSTPACKET to WMA_OK and therefore
                        // will try to retrieve the PCM, in which case we must return nothing)
                        ppcinfo->m_iCurrGetPCM_SubFrame = CURRGETPCM_INVALID;
                    }

                    BITRATE_REPORT_CHECKPT;
                    paudec->m_decsts = DECODE_SUBFRAME; 
                    paudec->m_subfrmdecsts = SUBFRM_HDR;
                    paudec->m_hdrdecsts = HDR_SIZE;
                    paudec->m_iChannel = 0;  
                    paudec->m_iBand = 0;     

                }
                //else 
                //    paudec->m_decsts = END_SUBFRAME2; // This assignment is redundant, and should be removed.

                // Initialize m_cLastCodedIndex
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    ppcinfo->m_cLastCodedIndex = 1;
                }
                pau->m_cLastCodedIndex = 1;

                // Fall into
            case DECODE_SUBFRAME :
                // V3 Pure LLM. Chao. Add.
                if (paudec->pau->m_bPureLosslessMode == WMAB_TRUE) {
#if defined (BUILD_WMALSL)
                    TRACEWMA_EXIT(hr, prvDecodeSubFramePureLosslessMode(paudec));

#endif // BUILD_WMALSL
                }
                else 
                {
                    hr = (*(paudec->m_pfnDecodeSubFrame))(paudec);
                    if ((WMA_E_ONHOLD == hr) && ibstrmNoMoreInput(&paudec->m_ibstrm) && paudec->m_fSPDIF)
                    {
                        hr = WMA_S_NO_MORE_FRAME; // doesn't really matter - set later
                        paudec->m_decsts = END_SUBFRAME1;
                        paudec->m_fLastSubFrame = 1;
                        paudec->m_cFrmInPacket = 0;
                        break;
                    }
                    else
                    {
                        if (WMA_FAILED(hr))
                        {
                            int dummy = TraceResult(hr);
                            goto exit;
                        }
                    }
                }
//                WMAPrintf("%d %d %d\n", pau->m_iFrameNumber, pau->m_rgpcinfo->m_iCurrSubFrame, paudec->m_ibstrm.m_cFrmBitCnt);
//                FFLUSH(stdout);

                HEAP_DEBUG_CHECK;
                BITRATE_REPORT_PRINT;
                if (paudec->m_subfrmdecsts == SUBFRM_DONE)
                {
                    if (paudec->m_fLastSubFrame) {
                       if (paudec->pau->m_bPureLosslessMode == WMAB_TRUE) {
                           // PLLM does not need stuffing bit.
                            paudec->m_decsts = DECODE_TRAILERBIT;
                            break;
                        }
                        else
                            if(paudec->m_cbWMAV_Version>0){
                                paudec->m_decsts = END_SUBFRAME1;
                                break;
                            }else{
                                paudec->m_decsts = DECODE_STUFFINGBITS;
                            }
                    }
                    else
                    {
                        paudec->m_decsts = END_SUBFRAME1;
                        break;
                    }
                }


            case DECODE_STUFFINGBITS:
                if (pau->m_iVersion >= 3) 
                {
                    U32 iResult = 0;
                    while (iResult != 1)
                    {
                        //due to the nature of this mini-state machine
                        //we don't need to look for bits.
                        TRACEWMA_EXIT(hr, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                        //if m_fNoMoreData is true
                        //we could either 1/ had enough of 1 bit (should go one)
                        //                2/ didn't have enough (getBit must have put us on hold)
                        //so in either case, we don't need the following
#if 0
                        if(paudec->m_fNoMoreData)
                        {
                            hr = WMA_E_ONHOLD;
                            goto exit;
                        }
#endif
                    }
                   // DEBUG_ONLY(assert(count <= 8));
                }
                paudec->m_decsts = DECODE_TRAILERBIT;

            case DECODE_TRAILERBIT:
                if (pau->m_iVersion <= 2)
                {
                    paudec->m_cFrmInPacket--;
                }
                else    //get trailer bits
                    TRACEWMA_EXIT(hr, prvDecodeTrailerBit (paudec));
                if (paudec->m_fSPDIF)
                {
                    paudec->m_cFrmInPacket = 0;
                }
#ifdef WMA_COMPRESSION_TOOL
                // Professional Encoder
                // Report the bit position of the ending of a frame.
                if (paudec->m_fWriteMetaFile == WMAB_TRUE)
                {
                    I32 iPCMFrameNumber = prvGetPCMFrameNumber (pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);
                    TRACEWMA_EXIT(hr, prvRecordFrameEndInBitStrm (paudec, &paudec->m_ibstrm));
                    TRACEWMA_EXIT(hr, ibstrmDumpFrmBitsAfterFrameEnd (&paudec->m_ibstrm, pau->m_iFrameNumber, pau->m_iVersion));
                    TRACEWMA_EXIT(hr, prvWriteMetaFileGetCommonFrmHdr (paudec));
                    TRACEWMA_EXIT(hr, prvWriteMetaFileFrameBitsInfo (paudec, paudec->m_pMetaFileDir));
                    TRACEWMA_EXIT(hr, prvWriteMetaFileFrameBitsData (paudec, paudec->m_pMetaFileDir, iPCMFrameNumber));                    
                    // frame bits count should be consistent.
                    assert(paudec->m_ibstrm.m_cFrmBitCnt == (pau->m_cFrmUsedBitsFromParser - pau->m_cFrmHdrBitsFromParser) + pau->m_cFrmHdrBitsFromParserOrg);
                }
                // we have framebits ready in m_rgbFrameBits buffer now. External
                // application should get them and decrease this flag.
                paudec->m_fFrameBitsReady++;
#endif //WMA_COMPRESSION_TOOL

#ifdef AVS_TEST_MODES_PRINTFRMBITS
                TRACEWMA_EXIT(hr, prvRecordFrameEndInBitStrm (paudec, &paudec->m_ibstrm));
#endif //AVS_TEST_MODES_PRINTFRMBITS
                paudec->m_decsts = END_SUBFRAME1;

                // Fall-into
            case END_SUBFRAME1 :
#if defined(BUILD_WMAPROLBRV2)
                if (WMAB_TRUE == pau->m_bReconProc)
                    chexEndSubframeTilingInfo(pau, paudec->m_iCurrTile);
#endif

#ifdef WMA_COMPRESSION_TOOL
                if (paudec->m_fWriteMetaFile == WMAB_TRUE)
                {
                    I32 iPCMFrameNumber = prvGetPCMFrameNumber (pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);
                    TRACEWMA_EXIT(hr, prvWriteMetaFileTileInfo (paudec, iPCMFrameNumber, paudec->m_iCurrTile, paudec->m_pMetaFileDir));
                    TRACEWMA_EXIT(hr, prvWriteMetaFileCHX (paudec, iPCMFrameNumber, paudec->m_iCurrTile, paudec->m_pMetaFileDir));
                }
#endif //WMA_COMPRESSION_TOOL
                if (pcSampleSeekAdj == NULL)
                    pcSampleSeekAdj = &cSampleSeekAdj;

                // V3 Pure LLM. Problem. Chao.
                // better to make another auPreGetPCM function for Pure LLM.
                if (paudec->pau->m_bPureLosslessMode == WMAB_TRUE) {
                    prvCountAlignedPCM(pau, pcSampleReady, CAP_NODISCARDSILENCE, CAP_SUBFRAMELVL, paudec->m_fSPDIFStyleGetPCM);
                    if (pcSampleSeekAdj != NULL) 
                        *pcSampleSeekAdj = 0;
                }else{
                    // Change auPreGetPCM to auSubframeRecon
#ifdef WMA_COMPRESSION_TOOL
                    if (!paudec->m_fParsingOnly)
#endif //WMA_COMPRESSION_TOOL
                    {
                        auSubframeRecon(pau);
                    }
                }

                paudec->m_iCurrTile++;
                pau->m_iCurrTile++;
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    if (ppcinfo->m_iCurrSubFrame >= ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame) {
                        // Somewhere we messed up in this frame for this channel
                        hr = TraceResult(WMA_E_BROKEN_FRAME);
                        goto exit;
                    }
                    ppcinfo->m_iCurrSubFrame++;
                }

            case END_SUBFRAME2 :
                // Test if we need discard silence
                if (paudec->pau->m_bPureLosslessMode == WMAB_FALSE) {
                    if (CODEC_BEGIN == pau->m_codecStatus) {
                        if (paudec->m_cbWMAV_Version > 0)
                            paudec->pau->m_fLeadingSilence = WMAB_TRUE;
                        prvInitDiscardSilence(pau, paudec->m_fSPDIFStyleGetPCM);
                    }
                }

#ifdef PRINT_SUBFRAME_SEGMENTS
                prvPrintSubframeSegments(paudec);
#endif

                if (paudec->m_fLastSubFrame) 
                {
                    pau->m_bFirstFrameAfterReset = WMAB_FALSE;
                    prvShiftTimeIndex(pau);
                #ifndef UNDER_CE //the statement may not be true for WinCE 
                                 //because assembly optimization does not trace paudec->m_ibstrm.m_cFrmBitCnt in debug mode
                    // check bit count
                    if(!(!pau->m_fWriteFrameSize || paudec->m_fSPDIF ||
                           paudec->pau->m_fUES == WMAB_TRUE ||
                           pau->m_cComprFrameSizeBits == pau->m_cBitPacketLength ||
                           pau->m_cComprFrameSizeBits == paudec->m_ibstrm.m_cFrmBitCnt))
                    {
                        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);
                    }
                #endif //UNDER_CE

                    #if defined (TEST_PEAKRATE)
                    if (pau->m_cComprFrameSizeBits != pau->m_cBitPacketLength)
                    {
                        g_iLargestFrame = max(g_iLargestFrame, (unsigned int)pau->m_cComprFrameSizeBits);
                        g_cSamplesPerFrame = pau->m_cFrameSampleHalf;
                    }
                    #endif // TEST_PEAKRATE
                    #if defined(DEBUG_ENCODE_FOR_XBOX) && defined(_DEBUG)
                        fprintf(stdout, "Compressed Frame %d size %d bits\n", paudec->pau->m_iFrameNumber, paudec->m_ibstrm.m_cFrmBitCnt);
                    #endif

                    // ====== Now it is the end of a frame ======
                    // ====== NEW PCM RECON! Only allow PCM output at this time ======
                    if (paudec->pau->m_bPureLosslessMode == WMAB_FALSE) 
                    {
                        if( pau->m_iPCMReconEnd > pau->m_iPCMReconStart ) 
                        {
                            // we still have samples in buffer, output them first
                            *pcSampleReady = (U16)(pau->m_iPCMReconEnd - pau->m_iPCMReconStart);
                            break;
                        }
                        else
                        {
                            Int iMinSizeOutput;   // Min output size for all the channels

                            // the m_iPCMReconStart must wrap around first
                            assert( pau->m_iPCMReconStart < pau->m_cFrameSampleHalfAdjusted / 2);
                            if( pau->m_iPCMReconStart < 0 || 
                                pau->m_iPCMReconStart >= pau->m_cFrameSampleHalfAdjusted / 2 )
                            {
                                hr = WMA_E_FAIL;
                                goto exit;
                            }

                            // ---- Compute how many samples we have in the buffer ----
                            if( paudec->m_fSPDIFStyleGetPCM )  // Tian SPDIF
                            {
                                iMinSizeOutput = pau->m_cFrameSampleHalfAdjusted - pau->m_iPCMReconStart;
                            }
                            else
                            {
                                prvGetFramePCM( pau, &iMinSizeOutput );
                            }

                            // iMinSizeOutput is the number of sample available, will be feed to *pcSampleReady
                            pau->m_iPCMReconEnd = iMinSizeOutput + pau->m_iPCMReconStart;

                            // ---- Discard silence ----
                            if( pau->m_rgiDiscardSilence[0] > 0 && !paudec->m_fSPDIFStyleGetPCM )
                            {
                                // we need to discard silence samples
                                if( pau->m_rgiDiscardSilence[0] >= iMinSizeOutput ){

                                    pau->m_rgiDiscardSilence[0] -= iMinSizeOutput;
                                    pau->m_iPCMReconStart = pau->m_iPCMReconEnd;

                                } else {

                                    pau->m_iPCMReconStart += pau->m_rgiDiscardSilence[0];
                                    pau->m_rgiDiscardSilence[0] = 0;
                                    
                                }

                                // **** here we need to shift PCM buffer like in auGetPCM
                                prvShiftPCMBuffer ( pau );

                                if( (pau->m_iVersion >= 3) && (pau->m_u32TrailingSize > 0) ){
                                    // In this case, if we seek to the last packet, we may have negtive available samples.
                                    // If so just return 0
                                    U32 u32TrailingSizeAdjusted = AU_HALF_OR_DOUBLE(pau->m_fHalfTransform, pau->m_fPad2XTransform, pau->m_u32TrailingSize);
                                    if( pau->m_iPCMReconEnd - (I32)u32TrailingSizeAdjusted < pau->m_iPCMReconStart ){
                                        pau->m_iPCMReconStart = 0;
                                        pau->m_iPCMReconEnd = 0;
                                        pau->m_u32TrailingSize = 0;
                                    }
                                }
                            }

                            // ---- Discard trailing samples ----
                            if (pau->m_iVersion >= 3 && !paudec->m_fSPDIFStyleGetPCM ){
                                // V3 above we also need to discard trailing silence 
                                U32 u32TrailingSizeAdjusted = AU_HALF_OR_DOUBLE(pau->m_fHalfTransform, pau->m_fPad2XTransform, pau->m_u32TrailingSize);
                                pau->m_iPCMReconEnd -= u32TrailingSizeAdjusted;
                            }

                            // ---- Setup the number of output samples
                            if( pau->m_iPCMReconEnd < pau->m_iPCMReconStart ){
                                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(hr);
                            }

                            *pcSampleReady = (U16)(pau->m_iPCMReconEnd - pau->m_iPCMReconStart);

                            // ---- adjust the timestamp if needed ----
                            if( pau->m_fSeekAdjustment ) {

                                if (pcSampleSeekAdj == NULL)
                                    pcSampleSeekAdj = &cSampleSeekAdj;
                                *pcSampleSeekAdj = 0;

                                if( pau->m_iVersion <= 2 ){
                                    // we need to adjust Time-stamp for seeking
                                    // for v2 and earlier, there is a risk 
                                    //       to do the adjustment if !m_fAllowSuperFrame
                                    //       since the fStartSteam can't be detected.
                                    //       Now we are always doing it at the expense of 
                                    //       screwing the begining of the file where it should not be done.
                                    I16  iSizePrev, iSizeCurr, Q1, Q2;

                                    iSizePrev = (I16)pau->m_rgpcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[-1];
                                    iSizeCurr = (I16)pau->m_rgpcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [0];

                                    if (pau->m_fHalfTransform) {
                                        iSizeCurr >>= pau->m_iAdjustSizeShiftFactor;
                                        iSizePrev >>= pau->m_iAdjustSizeShiftFactor;
                                    }else if (pau->m_fPad2XTransform) {
                                        iSizeCurr <<= pau->m_iAdjustSizeShiftFactor;
                                        iSizePrev <<= pau->m_iAdjustSizeShiftFactor;
                                    }
                                    
                                    prvCalcQ1Q2(pau, WMAB_TRUE, iSizePrev, iSizeCurr, &Q1, &Q2 );

                                    *pcSampleSeekAdj += (I16) (Q2 - Q1);
                                }
                                else
                                { 
                                    // V3 or above, we are sending the correct Time-Stamp for seeking
                                    // There is no timestamp issue for SPDIF
                                }

                                pau->m_fSeekAdjustment = WMAB_FALSE;

                                if (pcSampleSeekAdj) 
                                    paudec->m_iCurrPresTime += *pcSampleSeekAdj;

                            } // fSeekAdjustment
                        } // pau->m_cGetPCMSamplesDone == 0
                    } // lossy mode

                    //take care the end of a frame
                    if (pau->m_fAllowSuperFrame)
                    {
                        //copy next subfrm config to curr
                        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                        {                            
                            SubFrameConfigInfo* psubfrmconfig = (pau->m_rgpcinfo + iCh)->m_rgsubfrmconfig + CONFIG_CURRFRM;
                            I32                     cSizeCurr = psubfrmconfig->m_cSubFrame;
                            if( pau->m_iVersion <= 2 )
                            {
                                psubfrmconfig->m_rgiSubFrameSize[-1] = psubfrmconfig->m_rgiSubFrameSize[cSizeCurr-1];
                                psubfrmconfig->m_rgiSubFrameSize[0]  = psubfrmconfig->m_rgiSubFrameSize[cSizeCurr];
                                psubfrmconfig->m_rgiSubFrameStart[0] = 0;
                                psubfrmconfig->m_cSubFrame = 1;
                            }
                            else
                            {
                                psubfrmconfig->m_rgiSubFrameSize[-1] = psubfrmconfig->m_rgiSubFrameSize[cSizeCurr-1];
                            }
                        }
                    }
                    
                    //WMAPrintf("LL%d %d %d\n", pau->m_iFrameNumber, pau->m_rgpcinfo->m_iCurrSubFrame, paudec->m_ibstrm.m_cFrmBitCnt);
                    //FFLUSH(stdout);

                    //start decoding the next frame
                    paudec->m_decsts = BEGIN_FRAME; 
                    paudec->m_fhdrdecsts = FHDR_SIZE;
#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
                    if (pau->m_iVersion > 2) 
                        prvInitDecodeTileHdr(paudec, CONFIG_CURRFRM);
#endif

                    if (paudec->m_cFrmInPacket <= 0)
                    {
                        hr = WMA_S_NO_MORE_FRAME;
                        goto exit;
                    }
                }
                else                    
                    paudec->m_decsts = BEGIN_SUBFRAME; //goto the start of next subfrm
                goto exit;

           case BEGIN_PACKET:
                assert (paudec->pau->m_fAllowSuperFrame || (paudec->m_cFrmInPacket == 1));
                paudec->m_decsts = BEGIN_FRAME;                 
                paudec->m_fhdrdecsts = FHDR_PREV;

                // Countdown to first continous decode adjustment
                if (paudec->m_iContinuousDecodeCountdown > 0)
                    paudec->m_iContinuousDecodeCountdown -= 1;

                break;
           case BEGIN_FRAME:
                //WMAPrintf("Frame %d\n", paudec->pau->m_iFrameNumber);
#ifdef WMA_ENTROPY_TEST
                pauInitModelsEntropyTest(pau, NULL, g_maskTest);
#endif
                paudec->pau->m_iFrameNumber++;                
                paudec->m_fLastSubFrame = WMAB_FALSE;
                paudec->m_iCurrTile = 0;
                pau->m_iCurrTile = 0;
                pau->m_u32TrailingSize = 0;
                paudec->m_ibstrm.m_cFrmBitCnt = 0;

#if defined(BUILD_WMAPROLBRV1)
                freqexFrameInit(pau);
#if defined(BUILD_WMAPROLBRV3)
                bpeakFrameInit(pau);
#endif
#endif // BUILD_WMAPROLBRV1

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPROLBRV2)
                prvBasePlusFrameInit(pau);
#endif

#if defined(BUILD_WMAPROLBRV2)
                TRACEWMA_EXIT(hr, reconProcessUnprocessedTiles(pau));
#endif

                if (paudec->pau->m_bPureLosslessMode == WMAB_TRUE) 
                {
                    // init for getPCM. (Pure Lossless Mode)
                    pau->m_cGetPCMSamplesDone = 0;
                }
                else
                {
                    // NEW PCM RECON: here we wait for PCM output
                    // until the buffer pointer wrap around
                    if( pau->m_iPCMReconEnd > pau->m_iPCMReconStart ){
                        *pcSampleReady = (U16)(pau->m_iPCMReconEnd - pau->m_iPCMReconStart);
                        break;
                    }
//                    assert ( pau->m_iPCMReconStart < pau->m_cFrameSampleHalfAdjusted / 2) {
                    if ( pau->m_iPCMReconStart >= pau->m_cFrameSampleHalfAdjusted / 2) {
                        pau->m_iPCMReconEnd = 0;
                        pau->m_iPCMReconStart = 0;
                    }
                }

                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    ppcinfo = pau->m_rgpcinfo + iCh;
                    ppcinfo->m_iCurrSubFrame = 0;
                    //TODOCHAO: we'd better to check the previous frame output the correct PCM samples.
                    // set iPCMInHistory as 0 in PLLM.
                    if (pau->m_bPureLosslessMode == WMAB_TRUE)
                        pau->m_rgiPCMInHistory[iCh] = 0;
                }
                paudec->m_decsts = FRAME_HDR;
                break;
            case FRAME_HDR:             
                if (paudec->m_cFrmInPacket == 0)
                {
                    hr = WMA_S_NO_MORE_FRAME;
                    goto exit;
                }
#ifdef WMA_COMPRESSION_TOOL
                // Professional Encoder
                // Report the bit position of the starting of a frame.
                if (paudec->m_fWriteMetaFile == WMAB_TRUE)
                {
                    TRACEWMA_EXIT(hr, prvRecordFrameStartInBitStrm(paudec, &paudec->m_ibstrm));
                }
    #ifdef AVS_TEST_MODES_PRINTFRMBITS
                assert (paudec->m_fWriteMetaFile != WMAB_TRUE);
                TRACEWMA_EXIT(hr, prvRecordFrameStartInBitStrm(paudec, &paudec->m_ibstrm));
    #endif //AVS_TEST_MODES_PRINTFRMBITS
#endif //WMA_COMPRESSION_TOOL
                TRACEWMA_EXIT(hr, prvDecodeFrameHeader (paudec));                

#ifdef WMA_COMPRESSION_TOOL
                // Report the bit position of the end of the frame hdr.
                if (paudec->m_fWriteMetaFile == WMAB_TRUE)
                {
                    TRACEWMA_EXIT(hr, prvRecordFrameHdrBits(paudec, paudec->m_ibstrm.m_cFrmBitCnt));
                }
#endif //WMA_COMPRESSION_TOOL
                //WMAPrintf("FH%d %d %d\n", pau->m_iFrameNumber, pau->m_rgpcinfo->m_iCurrSubFrame, paudec->m_ibstrm.m_cFrmBitCnt);
                //FFLUSH(stdout);

                // ======== Setup the coef buffer pointer to the beginning of the buffer ========
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    ppcinfo = pau->m_rgpcinfo + iCh;
                    ppcinfo->m_iCurrCoefPosition = 0;
                }

                paudec->m_decsts = BEGIN_SUBFRAME;
                break;
         }
    }

exit:
    if (pcSampleReady != NULL && *pcSampleReady > 0)
    {
        paudec->m_externalState = audecStateGetPCM;
        paudec->m_cSamplesReady = *pcSampleReady;
        audecLog((paudec, "...%d samples ready", paudec->m_cSamplesReady));
    }
    else
    {
        paudec->m_externalState = audecStateDecode;
    }

#if defined(BUILD_WMAPROLBRV2)
    if (!WMA_FAILED(hr) && WMAB_TRUE == pau->m_bReconProc)
    {
        WMARESULT wr;
        wr = chexEndDecodeData(paudec, pcSampleReady);
        if (WMA_FAILED(wr))
            hr = wr;
    }
#endif // BUILD_WMAPROLBRV1

    //FUNCTION_PROFILE_STOP(&fp);
#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
        prvWmaShowFrames(paudec->pau->m_iFrameNumber, paudec->m_iCurrTile,
            paudec->pau->m_cFrameSampleAdjusted, paudec->pau->m_cSubFrameSampleAdjusted,
            paudec->pau->m_cSubbandAdjusted, "RetDecD",
            hr<0 ? " 0x%08x " : " %d ", hr );
#endif
    HEAP_DEBUG_CHECK;
    return hr;
} // prvDecodeData


// Function GCD() is already defined in rsa32.lib (rsa_math.obj) for the CE build
// on ARM platforms.

// Stolen from Algorithms in C, Sedgewick
static Int  GCD (Int u, Int v)
{
    Int t;

    while (u > 0)
    {
        if (u < v)
        {
            // Swap 'em
            t = u;
            u = v;
            v = t;
        }
        u = u - v;
    }

    return v;
}


void prvInterpolateInit(CAudioObjectDecoder *paudec, Int iXformSampleRate,
                        Int iDstSampleRate)
{
    Int iGCD;

    paudec->m_iInterpolSrcBlkSize = iXformSampleRate;
    paudec->m_iInterpolDstBlkSize = iDstSampleRate;

    // Calculate the greatest common divisor between iXformSampleRate
    // and iDstSampleRate and use to reduce iSrcBlkSize, iDstBlkSize
    iGCD = GCD(iXformSampleRate, iDstSampleRate);
    if (0 != iGCD)
    {
        paudec->m_iInterpolSrcBlkSize /= iGCD;
        paudec->m_iInterpolDstBlkSize /= iGCD;
    }
} // prvInterpolateInit

void auLowPass2(CAudioObjectDecoder *paudec, CoefType *rgCoef, Int iNumCoefs)
{
    CoefType    *pEnd = rgCoef + iNumCoefs * 2; // Re and Im coefs (so times 2)
    CoefType    *pCurr;
    Int     iPassThruCoefs;

    //return;

    // Figure out how many coefficients will pass through untouched
    assert(paudec->m_iInterpolDstBlkSize <= 10000);
    assert(iNumCoefs <= 10000);
    iPassThruCoefs = paudec->m_iInterpolDstBlkSize * iNumCoefs /
      paudec->m_iInterpolSrcBlkSize;
    pCurr = rgCoef + (2 * iPassThruCoefs);   // Re and Im coefs (so times 2)
    iNumCoefs -= iPassThruCoefs;

    if (iNumCoefs <= 0) return;

    while (iNumCoefs > 0)
    {
        *pCurr++ = 0;       // Re coef
        *pCurr++ = 0;       // Im coef
        iNumCoefs -= 1;
    }

    assert(pCurr == pEnd);
} // auLowPass2

// ===========================

Int prvNumDstSamplesFromXFormSamples(CAudioObjectDecoder *paudec,
                                     Int nTransformSamples)
{
    Int nDstSamples = nTransformSamples;

    if (paudec->m_fUpsample2x && nTransformSamples > 0)
    {
        nDstSamples = 2*nTransformSamples;
    }
    else if (paudec->m_fResample && nTransformSamples > 0)
    {
        nDstSamples = (nTransformSamples*paudec->m_iInterpolDstBlkSize - 
                  paudec->m_iInterpolCurPos)/paudec->m_iInterpolSrcBlkSize + 1;
    }

    return nDstSamples;
}

#if defined (_DEBUG)
static I32 iSampleTotal = 0;
#endif  //_DEBUG

#if defined(SH4) || defined(_SH4_)
#   pragma warning(disable:4719)
#endif
WMARESULT prvInterpolate2X(CAudioObjectDecoder *paudec,
                           U8 *pbBuf, U16 *pcSample, Int cbDstLength)
{
    // work from back of buffer to front so we do not overwrite any
    // values we still need to use
    Int iChannel;
    Int iSamplesPerChannel = *pcSample;
    PCMSAMPLE *piInput, *piOutput, *piFirst, *piSecond;
    PCMSAMPLE iNextInput, iPrevInput, iCurOutput, iLastInput;
    PCMSAMPLE *piBuf = (PCMSAMPLE*)pbBuf;
    CAudioObject *pau = paudec->pau;
    const Int nCh = paudec->m_cDstChannel;

    if ((((cbDstLength/pau->m_nBytePerSample)/nCh)/2) < *pcSample)  // precheck
    {
        assert(WMAB_FALSE);
        return WMA_E_INVALIDARG;
    }
    
    for (iChannel = 0; iChannel < nCh; iChannel++)
    {
        piInput =
            PAUPRVADVANCEPCMPTR(piBuf, (iSamplesPerChannel-1)*nCh + iChannel);
        piOutput =
            PAUPRVADVANCEPCMPTR(piBuf, (2*iSamplesPerChannel-1)*nCh + iChannel);

        iNextInput = PAUPFNGETSAMPLE0(piInput);
        iLastInput = iNextInput;
        piFirst = PAUPRVADVANCEPCMPTR(piBuf, iChannel);
        piSecond = PAUPRVADVANCEPCMPTR(piBuf, nCh + iChannel);
        while (piOutput > piSecond)
        {
             // 1 ahead of in
            assert(piOutput >= PAUPRVADVANCEPCMPTR(piInput, nCh));
            
            PAUPFNSETSAMPLE0(iNextInput, piOutput);

            piOutput = PAUPRVADVANCEPCMPTR(piOutput, -nCh);
            assert(piOutput >= piSecond); // At least at second sample
            piInput = PAUPRVADVANCEPCMPTR(piInput, -nCh);
            assert(piInput >= piFirst); // At least at first sample

            iPrevInput = iNextInput;
            iNextInput = PAUPFNGETSAMPLE0(piInput);

            iCurOutput = (iPrevInput>>1) + (iNextInput>>1);
            assert(fabs((double)iCurOutput-
                        ((double)iPrevInput+(double)iNextInput)/2.0) <= 1.0);

            PAUPFNSETSAMPLE0(iCurOutput, piOutput);

            piOutput = PAUPRVADVANCEPCMPTR(piOutput, -nCh);
            assert(piOutput >= piSecond);
        }

        assert(piInput == piFirst);
        assert(piOutput == piSecond);
        PAUPFNSETSAMPLE0(iNextInput, piOutput);
        piOutput = PAUPRVADVANCEPCMPTR(piOutput, -nCh);
        assert(piOutput == piFirst);

        iPrevInput = iNextInput;
        iNextInput = paudec->m_iPriorSample[iChannel];

        iCurOutput = (iPrevInput>>1) + (iNextInput>>1);
        assert(fabs((double)iCurOutput-
                    ((double)iPrevInput+(double)iNextInput)/2.0) <= 1.0);

        PAUPFNSETSAMPLE0(iCurOutput, piOutput);

        paudec->m_iPriorSample[iChannel] = iLastInput;
    }
    
    *pcSample *= 2;

    return WMA_OK;
} // prvInterpolate2X
#if defined(SH4) || defined(_SH4_)
#   pragma warning(default:4719)
#endif

WMARESULT prvInterpolateResample(CAudioObjectDecoder *paudec,
                                 U8 *pbBuf, U16 *pcSamples, Int cbDstLength)
{
    U8 *pbSrc, *pbDst, *pbBuf2;
    PCMSAMPLE iLeftSample, iRightSample, iCurOutput;
    CAudioObject *pau = paudec->pau;
    Int nCh = paudec->m_cDstChannel;
    Int lastPos, curPos, end, i, incr, shift, lastPosS;
    const Int srcBlkSize = paudec->m_iInterpolSrcBlkSize;
    const Int dstBlkSize = paudec->m_iInterpolDstBlkSize;

    assert(paudec->m_iInterpolCurPos != 0);

    if (*pcSamples*dstBlkSize < paudec->m_iInterpolCurPos)
    {
        paudec->m_iInterpolCurPos -= *pcSamples*dstBlkSize;
        if (*pcSamples != 0)
        {
            for (i=0; i < nCh; i++)
              paudec->m_iPriorSample[i] =
                PAUPFNGETSAMPLE((PCMSAMPLE*)pbBuf, (*pcSamples-1)*nCh+i);
        }
        *pcSamples = 0;
        return WMA_OK;
    }
    end = (*pcSamples*dstBlkSize - paudec->m_iInterpolCurPos)/srcBlkSize;

    if (((cbDstLength/(Int)pau->m_nBytePerSample)/nCh) < (end+1))  // precheck
    {
        assert(WMAB_FALSE);
        return WMA_E_INVALIDARG;
    }

    lastPos = paudec->m_iInterpolCurPos + end*srcBlkSize;

    lastPosS = lastPos/dstBlkSize;

    for (i=0; i < nCh; i++) {
        paudec->m_iLastSample[i] =
          PAUPFNGETSAMPLE((PCMSAMPLE*)pbBuf, (*pcSamples-1)*nCh+i);
    }

    // jump src, dst to end
    pbSrc = (U8*)PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pbBuf, lastPosS*nCh);
    pbDst = (U8*)PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pbBuf,
                                      max(lastPosS,end)*nCh);
    shift = 0;
    if (lastPosS > end) shift = lastPosS-end;
    pbBuf2 = (U8*)PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pbBuf, nCh);
    curPos = lastPos;
    curPos -= lastPosS*dstBlkSize;
    assert(curPos >= 0 && curPos < dstBlkSize);
    while (pbSrc >= pbBuf2)
    {
        assert(pbDst >= pbBuf);
        for (i=0; i < nCh; i++)
        {
            if (curPos != 0)
              iRightSample = PAUPFNGETSAMPLE((PCMSAMPLE*)pbSrc, 0+i);
            else
              iRightSample = 0;
            iLeftSample = PAUPFNGETSAMPLE((PCMSAMPLE*)pbSrc, -nCh+i);
            iCurOutput = (iRightSample*curPos+iLeftSample*(dstBlkSize-curPos))/
              dstBlkSize;
            PAUPFNSETSAMPLE(iCurOutput, (PCMSAMPLE*)pbDst, i);
        }
        curPos -= srcBlkSize;
        if (curPos <= 0)
        {
            incr = (curPos - dstBlkSize + 1)/dstBlkSize;
            curPos -= incr*dstBlkSize;
            assert(curPos >= 0 && curPos < dstBlkSize);
            pbSrc = (U8*)PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pbSrc, incr*nCh);
        }
        pbDst = (U8*)PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pbDst, -nCh);
    }

    if (paudec->m_iInterpolCurPos>0 && paudec->m_iInterpolCurPos<dstBlkSize)
    {
        for (i=0; i < nCh; i++)
        {
            iRightSample = PAUPFNGETSAMPLE((PCMSAMPLE*)pbBuf, i);
            iLeftSample = paudec->m_iPriorSample[i];
            iCurOutput = (iRightSample*curPos+iLeftSample*(dstBlkSize-curPos))/
              dstBlkSize;
            PAUPFNSETSAMPLE(iCurOutput, (PCMSAMPLE*)pbDst, i);
        }
    }
    for (i=0; i < nCh; i++)
      paudec->m_iPriorSample[i] = paudec->m_iLastSample[i];

    lastPos += srcBlkSize - *pcSamples*dstBlkSize;
    paudec->m_iInterpolCurPos = lastPos;

    if (shift != 0)
    {
        memcpy(pbBuf, (U8*)PAUPRVADVANCEPCMPTR((PCMSAMPLE*)pbBuf, shift*nCh),
               (end+1)*nCh*pau->m_nBytePerSample);
    }

    *pcSamples = (U16)(end+1);

    return WMA_OK;
} // prvInterpolateResample

//#define DUMP_AUDEC_OUTPUT

#define POSTPROCESS_PREPCM

#ifndef BOOST_CHANFLDDN_POWER
// Leave it the way it was - undefined
//#define CHANFLDDN_PREPCM
#else
// Channel folddown should be done before PCM reconstruction
#define CHANFLDDN_PREPCM
#endif

#define CLIP_PCMRANGE(y) \
  if (y < pau->m_iPCMSampleMin) \
     y = pau->m_iPCMSampleMin; \
  else if (y > pau->m_iPCMSampleMax) \
     y = pau->m_iPCMSampleMax;

// For post processing done post PCM buffer
#define PPPOSTADVPTR(p, amt) { (p) += (amt)*pau->m_nBytePerSample; }
#define PPPOSTADVPTR16(p, amt) { (p) += (amt)*2; }
#define PPPOSTGETSAMPLE(p, ch) (PAUPFNGETSAMPLE((PCMSAMPLE*)(p), (ch)))
#define PPPOSTSETSAMPLE(v, p, ch) (PAUPFNSETSAMPLE(v, (PCMSAMPLE*)(p), (ch)))
#define PPPOSTSETSAMPLE16(v, p, ch) (prvSetSample16INLINE(v, (PCMSAMPLE*)p, pau, ch))
#define PPPOSTCLIPRANGE(x) CLIP_PCMRANGE(x)

#ifdef BOOST_CHANFLDDN_POWER
// We need to have prvChannelDownMixFloat and prvChannelDownMixInt (for Pure lossless)
// However, we need to be careful about the macros we define before including msaudiodectemplate.c
// Assumptions: BOOST_CHANFLDDN_POWER implies that CHANFLDDN_PREPCM has been defined
// So...get prvChannelDownMixFloat
#define DNMIX_INT 0
#include "msaudiodectemplate.c"
#undef DNMIX_INT
// ...and then get prvChannelDownMixInt, but with CHANFLDDN_POWER UN-defined
#undef CHANFLDDN_PREPCM
#define DNMIX_INT 1
#include "msaudiodectemplate.c"
#undef DNMIX_INT
#define CHANFLDDN_PREPCM
#else
// Leave things the way they were
#define DNMIX_INT 0
#include "msaudiodectemplate.c"
#undef DNMIX_INT
#ifndef CHANFLDDN_PREPCM
#define DNMIX_INT 1
#include "msaudiodectemplate.c"
#undef DNMIX_INT
#endif
#endif

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
WMARESULT audecPostProcessPrePCM(Void *pDecHandle, U16 *pcSamplesReturned,
                                 U8 *pbDst, U32 cbDstLength)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    CAudioObject* pau = NULL;
    WMARESULT wmaResult = WMA_OK;
    U16 cSamplesReturned = 0;
    Int nDRCSetting = paudec->m_wmapi.nDRCSetting;

    if (pDecHandle == NULL || pcSamplesReturned == NULL)
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);
    }

    pau = paudec->pau;
    cSamplesReturned = *pcSamplesReturned;

#if defined (BUILD_WMAPRO)

#ifdef POSTPROCESS_PREPCM
    if (paudec->m_fPostProcXform)
    {
        TRACEWMA_EXIT(wmaResult, prvPostProcChannelXformV3 (paudec, (U8*) pbDst, cSamplesReturned));
    }
#endif

#ifdef CHANFLDDN_PREPCM
    if (paudec->m_fChannelFoldDown == WMAB_TRUE)
    {
        // Fold down for lossless will happen after PCM reconstruction
        if (WMAB_FALSE==pau->m_bPureLosslessMode)
        {
            if (WMAB_FALSE == paudec->m_fLtRtDownmix || 
                WMAB_TRUE == paudec->m_fLtRtDownmixNonnormal) 
            {
                TRACEWMA_EXIT(wmaResult, prvChannelDownMixFloat(paudec, (U8*) pbDst, cSamplesReturned, (U8*) pbDst));
            }
            if (WMAB_TRUE == paudec->m_fLtRtDownmix)
            {
                TRACEWMA_EXIT(wmaResult, prvChannelDownMixLtRtFloat(paudec, (U8*) pbDst, &cSamplesReturned, (U8*) pbDst));
            }
        }
    }
#endif

#ifdef NEW_DRC_DECODE
    // Initialize drc if not already done -- and perform DRC
    TRACEWMA_EXIT(wmaResult, prvInitDecodeDRC(paudec, nDRCSetting));
#ifdef BOOST_CHANFLDDN_POWER
    if (paudec->m_fDRC == WMAB_TRUE && (paudec->m_fChannelFoldDown == WMAB_TRUE || nDRCSetting != WMA_DRC_HIGH))
#else
    if (paudec->m_fDRC == WMAB_TRUE && nDRCSetting != WMA_DRC_HIGH)
#endif
    {
        if (WMAB_FALSE==pau->m_bPureLosslessMode)
        {
            TRACEWMA_EXIT(wmaResult,
                          drcDecodeBlockPro(pau->m_pDrc,
                                            paudec,
                                            pau->m_ucDrcFrameScaleFactor,
                                            nDRCSetting,
                                            cSamplesReturned));
        }
        else
        {
            TRACEWMA_EXIT(wmaResult,
                          drcDecodeBlockLsl(pau->m_pDrc,
                                            paudec,
                                            pau->m_ucDrcFrameScaleFactor,
                                            nDRCSetting,
                                            cSamplesReturned));
        }
    }
#endif

#endif // #if defined (BUILD_WMAPRO)

exit:
    if (pcSamplesReturned) *pcSamplesReturned = cSamplesReturned;
    return wmaResult;
} // audecPostProcessPrePCM

#else
// So !BUILD_WMAPRO && !BUILD_WMALSL
WMARESULT audecPostProcessPrePCM(Void *pDecHandle, U16 *pcSamplesReturned,
                                 U8 *pbDst, U32 cbDstLength)
{
	return WMA_OK;
}
#endif // BUILD_WMAPRO || BUILD_WMALSL

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
WMARESULT audecPostProcessPostPCM(Void *pDecHandle, U16 *pcSamplesReturned,
                                  U8 *pbDst, U32 cbDstLength, I16 nDRCSetting)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    CAudioObject* pau = NULL;
    WMARESULT wmaResult = WMA_OK;
    U16 cSamplesReturned = 0;

    if (pDecHandle == NULL || pcSamplesReturned == NULL)
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);
    }

    pau = paudec->pau;
    cSamplesReturned = *pcSamplesReturned;

    if (cSamplesReturned*(Int)paudec->m_nDstBytePerSample*paudec->m_cDstChannel > (Int)cbDstLength ||
        cSamplesReturned > (Int)cbDstLength)
    {
        assert(WMAB_FALSE);
        return WMA_E_FAIL;
    }

#if defined (BUILD_WMAPRO)
#ifndef POSTPROCESS_PREPCM
    //Move to prepcm
    if (paudec->m_fPostProcXform)
    {
        TRACEWMA_EXIT(wmaResult, prvPostProcChannelXformV3 (paudec, (U8*) pbDst, cSamplesReturned));
    }
#endif

#ifdef CHANFLDDN_PREPCM
    // Fold down for lossless mode should happen after PCM recosntruction
    if (WMAB_TRUE == pau->m_bPureLosslessMode)
    {
        if (paudec->m_fChannelFoldDown == WMAB_TRUE)
        {
            if (WMAB_FALSE == paudec->m_fLtRtDownmix ||
                WMAB_TRUE == paudec->m_fLtRtDownmixNonnormal)
            {
                if (PCMDataPCM  == pau->m_dataType)
                {
                    TRACEWMA_EXIT(wmaResult, prvChannelDownMixInt (paudec, (U8*) pbDst, cSamplesReturned, (U8*) pbDst));
                }
                else
                {
                    TRACEWMA_EXIT(wmaResult, prvChannelDownMixFloat (paudec, (U8*) pbDst, cSamplesReturned, (U8*) pbDst));
                }
            }
            if (WMAB_TRUE == paudec->m_fLtRtDownmix)
            {
                TRACEWMA_EXIT(wmaResult, prvChannelDownMixLtRtInt (paudec, (U8*) pbDst, &cSamplesReturned, (U8*) pbDst));
            }
        }
    }
#else
    if (paudec->m_fChannelFoldDown == WMAB_TRUE)
    {
        if (WMAB_FALSE == paudec->m_fLtRtDownmix ||
            WMAB_TRUE == paudec->m_fLtRtDownmixNonnormal)
        {
            if (PCMDataPCM  == pau->m_dataType)
            {
                // optimized code for ARM, else just call prvChannelDownMixInt
                TRACEWMA_EXIT(wmaResult, prvChannelDownMix (paudec, (U8*) pbDst, cSamplesReturned, (U8*) pbDst));
            }
            else
            {
                TRACEWMA_EXIT(wmaResult, prvChannelDownMixFloat (paudec, (U8*) pbDst, cSamplesReturned, (U8*) pbDst));
            }
        }
        if (WMAB_TRUE == paudec->m_fLtRtDownmix)
        {
            TRACEWMA_EXIT(wmaResult, prvChannelDownMixLtRtInt (paudec, (U8*) pbDst, &cSamplesReturned, (U8*) pbDst));
        }
    }
#endif

#ifndef NEW_DRC_DECODE
    // Initialize drc if not already done
    TRACEWMA_EXIT(wmaResult, prvInitDecodeDRC(paudec, nDRCSetting));

    // Do drc on minimum sampling rate & minimum channels
    if (paudec->m_fDRC == WMAB_TRUE &&
        nDRCSetting != WMA_DRC_HIGH &&
        pau->m_iXformSamplingRate <= paudec->m_iDstSamplingRate)
    {
        TRACEWMA_EXIT(wmaResult,
                      drcDecode(pau->m_pDrc,
                                pau->m_ucDrcFrameScaleFactor,
                                (U8*)pbDst, cSamplesReturned, nDRCSetting));
    }
#endif
#endif // BUILD_WMAPRO

    // interpolate 2X 
    /* This simple linear interpolation is fast but does not
       remove aliasing */
    /* So it should not be used with the HALF_TRANSFORM case if
       audio quality is important */
    if (paudec->m_fUpsample2x && cSamplesReturned > 0)
    {
        // these two give slightly different results
        // prvInterpolate2X gives one extra value and is shifted by 1
        // from what it should be.  This is because it does back to 
        // front writing and stuff between 2 frames is not written
        // until next frame.  So first sample is extra (time starts
        // at -1/2 sample rather than at 0 as in interpolateResample)
#if 1
        TRACEWMA_EXIT(wmaResult, prvInterpolate2X(paudec, pbDst,
                                                  &cSamplesReturned,
                                                  cbDstLength));
#else
        TRACEWMA_EXIT(wmaResult, prvInterpolateResample(paudec, pbDst,
                                                        &cSamplesReturned,
                                                        cbDstLength));
#endif
    }

    if (paudec->m_fResample && cSamplesReturned > 0)
    {
        TRACEWMA_EXIT(wmaResult, prvInterpolateResample(paudec, pbDst,
                                                        &cSamplesReturned,
                                                        cbDstLength));
    }

#if defined (BUILD_WMAPRO)
#ifndef NEW_DRC_DECODE
    // Do drc on minimum sampling rate 
    if (paudec->m_fDRC == WMAB_TRUE &&
        nDRCSetting != WMA_DRC_HIGH &&
        paudec->m_iDstSamplingRate < paudec->pau->m_iXformSamplingRate)
    {
        TRACEWMA_EXIT(wmaResult,
                      drcDecode(pau->m_pDrc,
                                pau->m_ucDrcFrameScaleFactor,
                                (U8*)pbDst, cSamplesReturned, nDRCSetting));
    }
#endif
#endif // BUILD_WMAPRO

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
    if (paudec->m_fReQuantizeTo16 == WMAB_TRUE)
    {
        TRACEWMA_EXIT(wmaResult, prvRequantizeTo16(paudec, pbDst, cSamplesReturned));
    }
#endif // BUILD_WMAPRO || BUILD_WMALSL

exit:
    if (pcSamplesReturned) *pcSamplesReturned = cSamplesReturned;
    return wmaResult;
} // audecPostProcessPostPCM

#else
// So !BUILD_WMAPRO && !BUILD_WMALSL
WMARESULT audecPostProcessPostPCM(Void *pDecHandle, U16 *pcSamplesReturned,
                                  U8 *pbDst, U32 cbDstLength, I16 nDRCSetting)
{
	return WMA_OK;
}
#endif // BUILD_WMAPRO || BUILD_WMALSL

WMARESULT audecGetPCMWrap (void* pDecHandle, WMA_U32 cSamplesRequested, WMA_U32 *pcSamplesReturned,
                                             __out_ecount(cbDstLength) WMA_U8* pbDst, 
                                             WMA_U32 cbDstLength,
                                             WMA_U32* pcbDstUsed, WMA_I64* prtTime,
                                             audecState *paudecState, WMAPlayerInfo *pPI,
                                             audecGetPCMParams* pParams)
{
    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    WMARESULT wmaResult = WMA_OK;
    U8**  rgpiRecon = NULL; 
    I16  iCh;
    CAudioObject* pau = NULL;
    U32 cbDstLengthAdjusted = cbDstLength;
    I16 nDRCSetting;
    U16 cTransformSamples;
    U16 cSamplesReturned = 0;
    U16 cGetChannels;
    U32 cSamplesReady;
#if !defined(BUILD_INTEGER)
    unsigned int origFPExceptionMask = DEFAULT_FP_EXCEPTION_MASK;

    prvDisableFPExceptions(&origFPExceptionMask);
#endif
    CCS_START(CCS_audecGetPCM);
    audecLog((paudec, "audecGetPCM(%d)", cSamplesRequested));

    prvSaveCurChannels(paudec->pau);
    prvSetOrigChannels(paudec->pau);
    
    if (paudec == NULL        ||
        paudec->pau == NULL   ||
        pcSamplesReturned == NULL ||
        (cSamplesRequested > 0 && pbDst == NULL))
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);
        goto exit;
    }

    pau = paudec->pau;

    if (paudec->m_externalState != audecStateGetPCM) {
      assert(!"audecGetPCM called at an inappropriate time");
      TRACEWMA_EXIT(wmaResult, WMA_E_WRONGSTATE);
    }
#if defined(BUILD_WMAPROLBRV1)
    if (WMAB_TRUE == pau->m_bReconProc)
        cSamplesReady = pau->m_prp->m_cSamplesReady;
    else
#endif // BUILD_WMAPROLBRV1
        cSamplesReady = paudec->m_cSamplesReady;

    assert(cSamplesReady > 0);

#ifdef DUMP_AUDEC_OUTPUT
    static FILE *fp = NULL;
    if (fp == NULL) {
        fp = FOPEN("c:/dump.raw", "wb");
    }
#endif
    
    cSamplesReturned = (U16)cSamplesReady;  

    // update ignore freqex setting
    if (pPI)
    {
        if (pPI->nPlayerOpt & PLAYOPT_IGNOREFREQEX)
            pau->m_bIgnoreFreqex = WMAB_TRUE;
        else
            pau->m_bIgnoreFreqex = WMAB_FALSE;

        if (pPI->nPlayerOpt & PLAYOPT_IGNORECX)
            pau->m_bIgnoreCx = WMAB_TRUE;
        else
            pau->m_bIgnoreCx = WMAB_FALSE;
    }

    // Override freqex with registry setting, if any
    if (paudec->m_bIgnoreFreqexThroughRegistry)
    {
        pau->m_bIgnoreFreqex = WMAB_TRUE;
    }


    paudec->m_wmapi.nDRCSetting = nDRCSetting = pPI ? pPI->nDRCSetting : WMA_DRC_HIGH; // update

    paudec->m_externalState = audecStateDone; // changed below on success
    pau = paudec->pau;
    rgpiRecon = paudec->m_rgpiRecon; 
    
    memset(rgpiRecon, 0, sizeof(U8*) * pau->m_cChannel);
    
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
        rgpiRecon [iCh] = (U8*) prvAdvancePCMPointer((PCMSAMPLE *)pbDst,
            pau->m_nBytePerSample, iCh);

    }
    
    //get pcm only when we are in these states
    if (paudec->m_decsts == BEGIN_FRAME || 
        paudec->m_decsts == BEGIN_SUBFRAME || 
        paudec->m_decsts == END_SUBFRAME1)
    {
        // post processing may require more buffer than before post processing
        // i.e., we are upsampling rate or number of channels.
        // find out how much of buffer we can use to get samples.
        // adjust cbDstLength to take care of time-domain player options
        //   - changing number of channels ("downmix")
        //   - adjusting sampling rate
        //   - bitdepth is taken care of since pau->m_nBytePerSample
        //     is already adjusted to dst.
        // adjust buffer size here since auGetPCM is common function
        // and does not have decoder specific member variables available.
        if (paudec->pau->m_iXformSamplingRate != paudec->m_iDstSamplingRate)
        {
            cbDstLengthAdjusted = min(cbDstLength,
              cbDstLength*paudec->m_iInterpolSrcBlkSize/paudec->m_iInterpolDstBlkSize);
        }
		if (WMAB_TRUE == paudec->m_fLtRtDownmixNonnormal)
        {
            cbDstLengthAdjusted = min(cbDstLengthAdjusted,
              cbDstLengthAdjusted*pau->m_cChannel/LTRT_SRC_CHANNELS);
        }
        else
        { 
            cbDstLengthAdjusted = min(cbDstLengthAdjusted,
              cbDstLengthAdjusted*pau->m_cChannel/paudec->m_cDstChannel);
        } 

        cGetChannels = pau->m_cChannel;
#ifdef CHANFLDDN_PREPCM
        if (paudec->m_fChannelFoldDown == WMAB_TRUE)
        {
            cGetChannels = (U16)paudec->m_cDstChannel;
        }
#endif

        if (!paudec->m_bBrokenFrame)
        {
                wmaResult = auGetPCM (pau, (Void*)paudec, &cSamplesReturned, rgpiRecon, cbDstLengthAdjusted,
                                                   cGetChannels, paudec->m_fSPDIFStyleGetPCM);
                if (WMA_FAILED(wmaResult))
                {                         
                    int dummy = TraceResult(wmaResult);
                    if (wmaResult == WMA_E_BROKEN_FRAME)
                    {
                        paudec->m_bBrokenFrame = WMAB_TRUE;
                    }
                    else
                    {
                        goto exit;
                    }
                }
        }

        if (paudec->m_bBrokenFrame)
        {
            // For a broken frame, return silence
            cSamplesReturned = (U16)min(cSamplesReady, (cbDstLength / paudec->m_nDstBytePerSample / paudec->m_cDstChannel));
            cTransformSamples = cSamplesReturned;
            memset(pbDst, 0, cbDstLength);
            audecLog((paudec, "...BROKEN_FRAME in auGetPCM"));
            TraceResult (wmaResult = WMA_OK); //map it to okay for the app
        }
        else
        {
            // these are the number of transform samples that are consumed.
            // actual number of samples output may be smaller or larger than this.
            cTransformSamples = cSamplesReturned;
            TRACEWMA_EXIT(wmaResult, audecPostProcessPostPCM(pDecHandle, &cSamplesReturned, pbDst, cbDstLength, nDRCSetting));
        }

    }
    else 
    {
        int dummy;
        cSamplesReturned = 0;         //we are in a state of error; don't return anything
        wmaResult = WMA_E_FAIL;
        dummy = TraceResult(wmaResult);
        goto exit;
    }

    if (pcbDstUsed) *pcbDstUsed = cSamplesReturned * paudec->m_nDstBytePerSample * paudec->m_cDstChannel;

#ifdef DUMP_AUDEC_OUTPUT
    if (pbDst != NULL)
      FWRITE(pbDst, 1, *pcbDstUsed, fp);
#endif

#if defined (_DEBUG)
    // TODO: why use [0]?
    iSampleTotal += cSamplesReturned;
#endif //_DEBUG)

    //convert back to 100ns
    // timestamps are donw using iCurrPresTime, which are calculated using
    // destination sampling rate; therefore iCurrPresTime should be updated
    // using actual number of samples that are output
    if (prtTime) *prtTime = paudec->m_iCurrPresTime * 10000000 / paudec->m_iDstSamplingRate;

	audecLog((paudec, "...%d @ %d [ %d ]", cSamplesReturned, (int)paudec->m_iCurrPresTime, 
		(int)(paudec->m_iCurrPresTime*1000/paudec->m_iDstSamplingRate) ));

    paudec->m_iCurrPresTime += cSamplesReturned;

#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
    prvWmaShowFrames(pau->m_iFrameNumber, paudec->m_iCurrTile,
        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
        pau->m_cSubbandAdjusted, "RetGetP",
        wmaResult<0 ? " 0x%08x " : " %d ", wmaResult );
#endif

#if 0
    assert(cSamplesReady >= cSamplesReturned);
    cSamplesReady -= cSamplesReturned;
#else // cSamplesReady are number of transform samples
    assert(cSamplesReady >= cTransformSamples);
    cSamplesReady -= cTransformSamples;
#endif

    if (cSamplesReady > 0)
      paudec->m_externalState = audecStateGetPCM;
    else
    {
        if (paudec->m_bBrokenFrame)
        {
            // This will set puadec->m_externalState to audecStateInput
            audecReset(paudec); 
        }
        else
        {
            paudec->m_externalState = audecStateDecode;
        }
    }

#if defined(BUILD_WMAPROLBRV1)
    if (WMAB_TRUE == pau->m_bReconProc)
        pau->m_prp->m_cSamplesReady = cSamplesReady;
    else
#endif // BUILD_WMAPROLBRV1
        paudec->m_cSamplesReady = cSamplesReady;
    
exit:
    prvRestoreCurChannels(pau);

    if (pcSamplesReturned) *pcSamplesReturned = cSamplesReturned;
    if (paudec->m_fSPDIF && paudec->m_fNeedHeader && paudec->m_externalState == audecStateDecode)
    {
        paudec->m_externalState = INPUT_STATE;
    }
    if (paudecState) *paudecState = paudec->m_externalState;

    CCS_END(CCS_audecGetPCM);

#if !defined(BUILD_INTEGER)
    prvRestoreFPExceptions(origFPExceptionMask);
#endif
    return wmaResult;
} // audecGetPCMWrap

WMARESULT audecGetPCM (void* pDecHandle, WMA_U32 cSamplesRequested, WMA_U32 *pcSamplesReturned,
                                         WMA_U8* pbDst, WMA_U32 cbDstLength,
                                         WMA_U32* pcbDstUsed, WMA_I64* prtTime,
                                         audecState *paudecState, WMAPlayerInfo *pPI,
                                         audecGetPCMParams* pParams)
{
    WMA_TRY_AND_EXCEPT_AV(audecGetPCMWrap(pDecHandle, cSamplesRequested, pcSamplesReturned,
                                         pbDst, cbDstLength, pcbDstUsed, prtTime,
                                         paudecState, pPI, pParams));
}


// Should be called only during decode state
WMARESULT prvdecSetPlayerInfo(void* pDecHandle, 
                              audecState *paudecState, 
                              WMAPlayerInfo *pPI,
                              WMA_Bool fSetChDnMixMtx,
                              WMA_Bool fSetDRCRefAndTarget)
{
    WMARESULT wmaResult = WMA_OK;

#if defined(BUILD_WMAPRO)

    CAudioObjectDecoder* paudec = (CAudioObjectDecoder*)pDecHandle;
    CAudioObject *pau;

    if (NULL == paudec ||
        NULL == paudec->pau ||
        paudec->pau->m_iVersion <= 2 ||
        NULL == pPI ||
        !(fSetChDnMixMtx || fSetDRCRefAndTarget))
    {
        // Nothing to set
        goto exit;
    }

    pau = paudec->pau;

    if (paudec->m_externalState != audecStateGetPCM) 
    {
        assert(!"audecSetPlayerInfo called at an inappropriate time");
        TRACEWMA_EXIT(wmaResult, WMA_E_WRONGSTATE);
    }
    
    // Update mix-down matrix
    if (fSetChDnMixMtx && 
//        pPI->rgiMixDownMatrix &&
        WMAB_TRUE ==  paudec->m_fChannelFoldDown &&
        WMAB_FALSE == paudec->m_fLtRtDownmix)
    {
        TRACEWMA_EXIT(wmaResult,
                      prvInitChDnMix(paudec, pPI->rgiMixDownMatrix,
                           pau->m_cChannel, pau->m_nChannelMask,
                           paudec->m_cDstChannel, paudec->m_nDstChannelMask));
    }
    
    // Update DRC parameters
    if (fSetDRCRefAndTarget)

    {
        paudec->m_wmapi.iPeakAmplitudeRef    = pPI->iPeakAmplitudeRef;
        paudec->m_wmapi.iRmsAmplitudeRef     = pPI->iRmsAmplitudeRef;
        paudec->m_wmapi.iPeakAmplitudeTarget = pPI->iPeakAmplitudeTarget;
        paudec->m_wmapi.iRmsAmplitudeTarget  = pPI->iRmsAmplitudeTarget;
        paudec->m_wmapi.nDRCSetting          = pPI->nDRCSetting;

        paudec->m_fDRC = WMAB_FALSE; // set it to false, so it can reinit.
        TRACEWMA_EXIT(wmaResult,
                      prvInitDecodeDRC(paudec, paudec->m_wmapi.nDRCSetting));
    }

exit:
#endif // BUILD_WMAPRO

    // We dont change states in this function.
    return wmaResult;
} // prvdecSetPlayerInfo

WMARESULT audecSetPlayerInfo(void* pDecHandle, 
                             audecState *paudecState, 
                             WMAPlayerInfo *pPI,
                             WMA_Bool fSetChDnMixMtx,
                             WMA_Bool fSetDRCRefAndTarget)
{
    WMA_TRY_AND_EXCEPT_AV(prvdecSetPlayerInfo(pDecHandle, paudecState, pPI, fSetChDnMixMtx, fSetDRCRefAndTarget));
} // audecSetPlayerInfo


// Translate the Givens angle/sign information into channel transform
WMARESULT prvDecodeChannelXform(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    Int iChGrp;
    CChannelGroupInfo* pcgi = NULL;
    CAudioObject* pau = paudec->pau;

    if (pau->m_iVersion <= 2)
        return wmaResult;
    
    for (iChGrp = 0; iChGrp < pau->m_cChannelGroup; iChGrp++) {
        pcgi = pau->m_rgChannelGrpInfo + iChGrp;
        if (pcgi->m_fIsPredefinedXform == WMAB_FALSE) {
            // Reconstruct the inverse matrix from angle/sign information
            TRACEWMA_EXIT(wmaResult, 
                auGetTransformFromGivensFactors(pcgi->m_rgbRotationAngle, 
                pcgi->m_rgbRotationSign, 
                pcgi->m_cChannelsInGrp,
                pau->m_cChannel,  // only for security
                pcgi->m_rgfltMultiXInverse,
                pau->m_rgfltGivensTmp0,
                pau->m_rgfltGivensTmp1));
        }
    }
exit:
    return wmaResult;
} // prvDecodeChannelXform

Void prvResetRunLevelState(CAudioObjectDecoder *paudec)
{
    if (paudec->pau->m_iVersion <= 2) {
        paudec->m_rlsts = VLC;
    } else {
        paudec->m_rlsts = TBL_INDEX;
        if (paudec->m_pfnResetEntropyCoder)
          (*(paudec->m_pfnResetEntropyCoder))(paudec);
    }
#ifdef WMA_ENTROPY_TEST
    if (!g_maskTest) initEntropyTest();
#endif
}

#if defined(BUILD_WMAPROLBRV1)

WMARESULT prvInitPlusStream(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int iBytes = (Int)((pau->m_iPlusBits+7)>>3);

    if (!pau->m_bPlusV1 && !pau->m_bPlusV2)
        goto exit;

#if !defined(WRITE_PLUS_TO_FILE)
    ibstrmReset(paudec->m_pibsPlus);
    TRACEWMA_EXIT(wmaResult,
                  ibstrmAttach(paudec->m_pibsPlus, (U8*)pau->m_rgiPlusBsBuf,
                         (I32)(iBytes + 3), // lie about 3 more
                         WMAB_FALSE, WMAB_FALSE, WMAB_FALSE, pau->m_iVersion));
#endif

exit:
    return wmaResult;
}

#define CHECK_BITSEND() \
    iBitsRem = (Int)pau->m_iPlusBits - ibstrmBitCount(paudec->m_pibsPlus); \
    if (iBitsRem <= 0) \
        goto exit;

#if defined(BUILD_WMAPROLBRV2)
WMARESULT plusDecodeBase(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int iBitsRem;
    U32 fBasePlusTileCoded = 0;

    if (pau->m_fBasePlusPresent)
    {
        if (pau->m_fBasePlusPresentTile)
        {
            // else bit has already been flushed
            CHECK_BITSEND();
            PLUS_GETBITS(wmaResult, 1, &fBasePlusTileCoded);
        }
        TRACEWMA_EXIT(wmaResult, bpdecDecodeTile(paudec, fBasePlusTileCoded));
    }

exit:
    return wmaResult;
}
#endif

WMARESULT plusPeekBasePlusBit(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int iBitsRem;
    U32 fBasePlusTileCoded;

    pau->m_fBasePlusPresentTile = WMAB_FALSE;
    if (pau->m_fBasePlusPresent)
    {
        CHECK_BITSEND();
        PLUS_PEEKBITS(wmaResult, 1, &fBasePlusTileCoded);
        if (fBasePlusTileCoded == 1)
        {
            pau->m_fBasePlusPresentTile = WMAB_TRUE;
        }
        else
        {
            // this 1-bit has to be flushed out to start peak decoding with base recon
            PLUS_FLUSHBITS(wmaResult, 1);
        }
    }
exit:
    return wmaResult;
}

#if defined(BUILD_WMAPROLBRV1) && defined(BUILD_WMAPROLBRV3)
WMARESULT plusDecodeBasePeak(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int  iBitsRem, iCh;
    U32  uVal;
    Bool fSkipAll;

    pau->m_bBasePeakPresentTile = WMAB_FALSE;
    pau->m_cBasePeakLastCodedIndex = (U16)pau->m_cFrameSampleHalf;

    if (!pau->m_bPlusV2 || pau->m_fex.m_iVersion <= 2)
        goto exit;
    if (!pau->m_bBasePeakPresent)
        goto exit;
    if (pau->m_bFirstPlusFrameAfterReset)
        goto exit;

    CHECK_BITSEND();

    fSkipAll = WMAB_TRUE;
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        Int iChSrc = pau->m_rgiChInTile [iCh];
        if( pau->m_rgpcinfo[iChSrc].m_iPower != 0 )
            fSkipAll = WMAB_FALSE;
    }
    if (fSkipAll)
        goto exit;

    // decode global on/off
    PLUS_GETBITS(wmaResult, 1, &uVal);
    if (uVal)
    {
        pau->m_bBasePeakPresentTile = WMAB_TRUE;
        if (pau->m_fBasePlusPresentTile &&
            !pau->m_pbp->m_fOverlayMode)
        {
            pau->m_cBasePeakLastCodedIndex = 1;
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
            {
                Int iChSrc = pau->m_rgiChInTile[iCh];
#if defined(BUILD_WMAPROLBRV2)
                Int iFexCh = chexGetFexChannel(pau, iChSrc);
                if (iFexCh != iChSrc)
                    continue;
#endif // defined(BUILD_WMAPROLBRV2)
                pau->m_cBasePeakLastCodedIndex = 
                    max(pau->m_rgpcinfo[iChSrc].m_cLastCodedIndex,
                        pau->m_cBasePeakLastCodedIndex);
            }
        }
        else
        {
            pau->m_cBasePeakLastCodedIndex = pau->m_cLastCodedIndex;
        }
    }

exit:
    return wmaResult;
}

WMARESULT plusDecodeBasePeak_Channel(CAudioObjectDecoder *paudec, PerChannelInfo *ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Bool bCoded = WMAB_FALSE;
    Int  iBitsRem;

    if (!pau->m_bPlusV2 || pau->m_fex.m_iVersion <= 2)
        goto exit1;
    if (!pau->m_bBasePeakPresent || !pau->m_bBasePeakPresentTile)
        goto exit;
    if (pau->m_bFirstPlusFrameAfterReset)
        goto exit;

    CHECK_BITSEND();

    TRACEWMA_EXIT(wmaResult, bpeakDecodeTile_Channel(paudec, ppcinfo));
    if (*(ppcinfo->m_pcBasePeakCoefs) > 0)
        bCoded = WMAB_TRUE;
exit:
    if (!bCoded)
        bpeakClearPeakCoef(ppcinfo, pau->m_iMaxBasePeakCoef);
exit1:
    return wmaResult;
}
#endif

#if defined(BUILD_WMAPROLBRV2)
WMARESULT plusDecodeCx(CAudioObjectDecoder *paudec, Bool *pbNoCodeCx)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Bool bCoded = WMAB_FALSE;
    Int iBitsRem;
    U32 uVal;

    if (pau->m_bCxPresent)
    {
        bCoded = (0 != pau->m_prp->m_iTilesInSubframeCode);
        if (bCoded)
        {
            if (!pau->m_bFreqexPresent && !pau->m_bReconFexPresent)
            {
                TRACEWMA_EXIT(wmaResult, chexTileInit(pau));
            }
            CHECK_BITSEND();
            if (!pau->m_bCxIsLast)
            {
                PLUS_GETBITS(wmaResult, 1, &uVal);
            }
            else
            {
                uVal = 1; // presence of any bits indicates cx
            }
            if (uVal)
            {
                TRACEWMA_EXIT(wmaResult, chexDecodeTile(paudec));
                *pbNoCodeCx = WMAB_FALSE;
            }
        }
    }

exit:
    return wmaResult;
}
#endif // BUILD_WMAPROLBRV2

WMARESULT plusDecodeFex(CAudioObjectDecoder *paudec, Bool *pbNoCodeFx)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &pau->m_fex;
    Bool bCoded = WMAB_FALSE;
    Int iBitsRem;
    U32 uVal;

    if (pau->m_bFreqexPresent)
    {
        pfx->m_iIteration = 3;
        bCoded = freqexTileCoded(pau);
#if defined(BUILD_WMAPROLBRV2)
        TRACEWMA_EXIT(wmaResult, chexTileInit(pau));
#endif
        if (bCoded)
        {
            CHECK_BITSEND();
            if (pau->m_bPlusV1)
            {
                PLUS_GETBITS(wmaResult, 1, &uVal);
                if (0 != uVal)  // bit for base+ which never existed
                {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                }
            }

            if (!pau->m_bFxIsLast || pau->m_bPlusV1)
            {
                PLUS_GETBITS(wmaResult, 1, &uVal);
            }
            else
            {
                uVal = 1;
            }

            if (uVal)
            {
                TRACEWMA_EXIT(wmaResult, freqexSwitchFexDomain(pau, WMAB_FALSE));
                TRACEWMA_EXIT(wmaResult, freqexDecodeTile(paudec));
                *pbNoCodeFx = WMAB_FALSE;
                if (pfx->m_bOverlayOnly)
                    *pbNoCodeFx = WMAB_TRUE;
            }
        }
    }

exit:
    return wmaResult;
}

WMARESULT plusDecodeReconFex(CAudioObjectDecoder *paudec, Bool *pbNoCodeRFx)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &pau->m_fex;
    Int iBitsRem;

    if (pau->m_bReconFexPresent)
    {
        pau->m_bTileReconFex = freqexReconTileCoded(pau);
#if defined(BUILD_WMAPROLBRV2)
        TRACEWMA_EXIT(wmaResult, chexTileInit(pau));
#endif
        iBitsRem = (Int)pau->m_iPlusBits - ibstrmBitCount(paudec->m_pibsPlus);
        if (iBitsRem <= 0)
            pau->m_bTileReconFex = WMAB_FALSE;

        TRACEWMA_EXIT(wmaResult, freqexSwitchFexDomain(pau, WMAB_TRUE));
#if defined(BUILD_WMAPROLBRV2)
        TRACEWMA_EXIT(wmaResult, chexDecodeReconFex(paudec));
#endif // BUILD_WMAPROLBRV2
        *pbNoCodeRFx = pau->m_bTileReconFex ? WMAB_FALSE : WMAB_TRUE;
    }

exit:

    return wmaResult;
}

#if defined(BUILD_WMAPROLBRV2)

WMARESULT plusDecodeCxHeader(CAudioObjectDecoder *paudec)
{
    CAudioObject *pau = paudec->pau;
    Chex *pcx = pau->m_pcx;
    ReconProc *prp = pau->m_prp;
    WMARESULT wmaResult = WMA_OK;
    Bool bNoInterpFromPrev = WMAB_FALSE;
    U32 uVal;

    // Band configuration
    // number of bands
    PLUS_GETBITS(wmaResult, pcx->m_iNumBandIndexBits, &uVal);
    if (pcx->m_iNumBandIndex != (Int)uVal)
        bNoInterpFromPrev = WMAB_TRUE;
    pcx->m_iNumBandIndex = (Int)uVal;
    pcx->m_cBands = pcx->m_piCxBands[pcx->m_iNumBandIndex];
    // band config multiplier
    if (pcx->m_cBands >= g_iMinCxBandsForTwoConfigs)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        if (pcx->m_iBandMultIndex != (Int)uVal)
            bNoInterpFromPrev = WMAB_TRUE;
        pcx->m_iBandMultIndex = (Int)uVal;
    }
    else
    {
        pcx->m_iBandMultIndex = 0;
    }

    // allow update for band config
    PLUS_GETBITS(wmaResult, 1, &uVal);
    pcx->m_bBandConfigPerTile = (Bool)uVal;
    // start band
    TRACEWMA_EXIT(wmaResult, freqexGet1ofNVals(paudec, pcx->m_cBands, &uVal));
    pcx->m_iStartBand = (Int)uVal;
    // allow update for start band
    PLUS_GETBITS(wmaResult, 1, &uVal);
    pcx->m_bStartBandPerTile = (Bool)uVal;
    // Parameters + thresholds
    // bCodeLMRM
    PLUS_GETBITS(wmaResult, 1, &uVal);
    if (pcx->m_bCodeLMRM != (Bool)uVal)
        bNoInterpFromPrev = WMAB_TRUE;
    pcx->m_bCodeLMRM = (Bool)uVal;
    // reverb strength adjustment threshold
    PLUS_GETBITS(wmaResult, pcx->m_iAdjustScaleThreshBits, &uVal);
    pcx->m_iAdjustScaleThreshIndex = (Int)uVal;
    // auto matrix scale adjustment
    TRACEWMA_EXIT(wmaResult,
               freqexGet1ofNVals(paudec, pcx->m_iAutoAdjustScaleVals, &uVal));
    pcx->m_eAutoAdjustScale = (ChexAutoAdjust)uVal;
    // max matrix scale
    PLUS_GETBITS(wmaResult, pcx->m_iMaxMatrixScaleBits, &uVal);
    pcx->m_iMaxMatrixScaleIndex = (Int)uVal;
    // filter tap
    TRACEWMA_EXIT(wmaResult,
              freqexGet1ofNVals(paudec, pcx->m_iFilterTapOutputVals, &uVal));
    pcx->m_eFilterTapOutput = (ChexFilterOutput)uVal;
    // whether phase is coded or not
    pcx->m_bNoPhase = WMAB_FALSE;
    if (pau->m_iPlusVersion >= 3)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pcx->m_bNoPhase = uVal;
    }
    // Quantization step sizes
    PLUS_GETBITS(wmaResult, pcx->m_iQuantStepIndexBits, &uVal);
    pcx->m_iQuantStepIndex = (Int)uVal;
    if (WMAB_FALSE == pcx->m_bNoPhase)
    {
        PLUS_GETBITS(wmaResult, pcx->m_iQuantStepIndexBits, &uVal);
        pcx->m_iQuantStepIndexPhase = (Int)uVal;
    }
    if (WMAB_FALSE == pcx->m_bCodeLMRM)
    {
        PLUS_GETBITS(wmaResult, pcx->m_iQuantStepIndexBits, &uVal);
        pcx->m_iQuantStepIndexLR = (Int)uVal;
    }
    // Channel coding
    TRACEWMA_EXIT(wmaResult,
                  freqexGet1ofNVals(paudec, pcx->m_iCxChCodingVals, &uVal));
    pcx->m_eCxChCoding = (ChexChCoding)uVal;

    pcx->m_bNoInterpFromPrev = bNoInterpFromPrev;
    pcx->m_bNoInterpFromPrev = WMAB_FALSE;

    TRACEWMA_EXIT(wmaResult, chexInitConfig(pau));

exit:
    return wmaResult;
}

WMARESULT plusDecodeCodingFexHeader(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex          *pfx = &(pau->m_fex);

    TRACEWMA_EXIT(wmaResult, freqexSwitchFexDomain(pau, WMAB_FALSE));
#ifdef BUILD_WMAPROLBRV2
    if (pfx->m_iVersion == 2)
    {
        TRACEWMA_EXIT(wmaResult, freqexDecodeCodingGlobalParam(paudec, WMAB_TRUE, WMAB_TRUE, WMAB_TRUE, WMAB_TRUE));
    }
#ifdef BUILD_WMAPROLBRV3
    else if (pfx->m_iVersion > 2)
    {
        TRACEWMA_EXIT(wmaResult, freqexDecodeGlobalParamV3(paudec, FexGlobalParamUpdateFull));
    }
#endif
#endif
exit:
    return wmaResult;
}

WMARESULT plusDecodeReconFexHeader(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex          *pfx = &(pau->m_fex);

    TRACEWMA_EXIT(wmaResult, freqexSwitchFexDomain(pau, WMAB_TRUE));
#ifdef BUILD_WMAPROLBRV2
    if (pfx->m_iVersion == 2)
    {
        TRACEWMA_EXIT(wmaResult, freqexDecodeReconGlobalParam(paudec, WMAB_TRUE, WMAB_TRUE, WMAB_TRUE, WMAB_TRUE));
    }
#ifdef BUILD_WMAPROLBRV3
    else if (pfx->m_iVersion > 2)
    {
        TRACEWMA_EXIT(wmaResult, freqexDecodeGlobalParamV3(paudec, FexGlobalParamUpdateFull));
    }
#endif
#endif
exit:
    return wmaResult;
}

WMARESULT plusDecodeReconProcHeader(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    ReconProc *prp = pau->m_prp;
    U32 uVal;

    PLUS_GETBITS(wmaResult, 1, &uVal);
    if (uVal == 0)
    {
        prp->m_iTileSplitType = ReconProcTileSplitBaseSmall;
    }
    else
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        prp->m_iTileSplitType = (uVal == 0) ? ReconProcTileSplitBasic :
                                              ReconProcTileSplitArbitrary;
    }

exit:
    return wmaResult;
}

WMARESULT plusDecodeReconProcTileSplitArbitrary(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    ReconProc *prp = pau->m_prp;
    Int iTile;
    Bool bAllowSplit;
    U32 uVal;

    bAllowSplit = (prp->m_iNTilesPerFrameBasic < prp->m_iMaxTilesPerFrame) ? WMAB_TRUE : WMAB_FALSE;

    for (iTile = 0; iTile < prp->m_iNTilesPerFrameBasic; iTile++)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        if (uVal == 1 && !bAllowSplit)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        prp->m_rgbTileSplitArbitrary[iTile] = (uVal == 1) ? WMAB_TRUE : WMAB_FALSE;
    }

exit:
    return wmaResult;
}

#endif // BUILD_WMAPROLBRV2

Void plusPrintOptions(CAudioObject *pau)
{
    static Bool bFirst = WMAB_TRUE;
    if (bFirst)
    {
        Int iFxVersion;

        iFxVersion = pau->m_bFreqex && pau->m_bFreqexPresent ?
            pau->m_fex.m_iVersion : 0;
        printf("Coding FEX: v%d%s\n", (int)iFxVersion,
               0==iFxVersion ? " -- off" : "");
        iFxVersion = pau->m_bReconFex && pau->m_bReconFexPresent ?
            pau->m_fex.m_iVersion : 0;
        printf("Recon  FEX: v%d%s\n", (int)iFxVersion,
               0==iFxVersion ? " -- off" : "");
        printf("CX        : %d - v%d\n",
        		(int)(pau->m_bCx && pau->m_bCxPresent ?
               (pau->m_cOrigChannel != pau->m_cCodedChannel)+1 : 0),
            		   (int)pau->m_iPlusVersion);
#if defined(BUILD_WMAPROLBRV2)
        printf("BASEPLUS  : %s\n",
               pau->m_fBasePlus && pau->m_fBasePlusPresent ?
               (pau->m_pbp->m_fOverlayMode ? "overlay" : "exclusive/extend") :
               "off");
#endif
        printf("BASEPEAK  : %d\n",
        		(int)pau->m_bBasePeakPresent);
        bFirst = WMAB_FALSE;
    }
}

WMARESULT plusDecodeSuperframeHeaderLastTileV2(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    U32 uVal;
    Int iBitsRem;

    CHECK_BITSEND();

    if (pau->m_bPlusSuperframe)
    {
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pau->m_bCxPresent = uVal;
        if (pau->m_bCxPresent && !pau->m_bCx)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        PLUS_GETBITS(wmaResult, 1, &uVal);
        pau->m_bReconFexPresent = uVal;
        if (pau->m_bReconFexPresent && !pau->m_bReconFex)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
#if defined(BUILD_WMAPROLBRV2)
        if (pau->m_bCxPresent)
            TRACEWMA_EXIT(wmaResult, plusDecodeCxHeader(paudec));
        if (pau->m_bReconFexPresent)
            TRACEWMA_EXIT(wmaResult, plusDecodeReconFexHeader(paudec));
        if (pau->m_bCxPresent || pau->m_bReconFexPresent)
            TRACEWMA_EXIT(wmaResult, plusDecodeReconProcHeader(paudec));
#endif // BUILD_WMAPROLBRV2

        PLUS_GETBITS(wmaResult, 1, &uVal);
        pau->m_bCodePresentForAllPlus = (Bool)uVal;
    }
#if defined(BUILD_WMAPROLBRV2)
    if ((pau->m_bCxPresent || pau->m_bReconFexPresent) &&
        pau->m_prp->m_iTileSplitType == ReconProcTileSplitArbitrary)
    {
        // decode arbitrary split if needed
        TRACEWMA_EXIT(wmaResult, 
                      plusDecodeReconProcTileSplitArbitrary(paudec));
    }
#endif

#if 0
    plusPrintOptions(pau);
#endif

exit:
    return wmaResult;
}

WMARESULT plusDecodeSuperframeHeaderFirstTileV2(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Chex *pcx = pau->m_pcx;
    Int iBitsRem;
    U32 uVal;
    FN_CNT;

    pau->m_bFirstPlusFrameAfterSuperframe = WMAB_FALSE;
    pau->m_bPlusSuperframe = WMAB_FALSE;
    pau->m_bLastTilePlusHeaderCoded = WMAB_FALSE;

    CHECK_BITSEND();

    PLUS_GETBITS(wmaResult, 1, &uVal);
    if (uVal == 1)
    {
        pau->m_bPlusSuperframe = WMAB_TRUE;
        pau->m_bSkipPlusDueToRFx = WMAB_FALSE;

#ifdef BUILD_WMAPROLBRV3
        if (pau->m_fex.m_iVersion > 2)
        {
            PLUS_GETBITS(wmaResult, 1, &uVal);
            pau->m_bBasePeakPresent = uVal;
        }
#endif
        PLUS_GETBITS(wmaResult, 1, &uVal); // uVal == pau->m_fBasePlusPresent
        if (uVal && !pau->m_fBasePlus)     // Check consistency of uVal before assigning to pau->m_fBasePlusPresent
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        pau->m_fBasePlusPresent = uVal;

        PLUS_GETBITS(wmaResult, 1, &uVal);
        pau->m_bFreqexPresent = uVal;
        if (pau->m_bFreqexPresent && !pau->m_bFreqex)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }

#if defined BUILD_WMAPROLBRV2
        if (pau->m_fBasePlusPresent)
        {
            TRACEWMA_EXIT(wmaResult, plusDecodeBasePlusSuperFrameHeader(paudec));
        }
#endif

#if defined(BUILD_WMAPROLBRV2)
        if (pau->m_bFreqexPresent)
            TRACEWMA_EXIT(wmaResult, plusDecodeCodingFexHeader(paudec));
#endif
        if (pau->m_bFreqexPresent || pau->m_fBasePlusPresent)
        {
            pau->m_bLastTilePlusHeaderCoded = WMAB_TRUE;
            TRACEWMA_EXIT(wmaResult,
                          plusDecodeSuperframeHeaderLastTileV2(paudec));
        }

        if (pau->m_bFirstPlusFrameAfterReset)
        {
            pau->m_bFirstPlusFrameAfterSuperframe = WMAB_TRUE;
            pau->m_bFirstPlusFrameAfterReset = WMAB_FALSE;
        }
    }

exit:
    return wmaResult;
}

WMARESULT plusDecodeTileHeader(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Int iBitsRem;

    prvSaveCurChannels(pau);
    prvSetOrigChannels(pau);

    if (WMAB_TRUE == paudec->m_bSkipPlus)
        goto exit;

    if (WMAB_FALSE==pau->m_bPlusV1 && WMAB_FALSE==pau->m_bPlusV2 &&
        WMAB_FALSE==pau->m_bReconProc)
        goto exit;

    auConvertSubframeConfigToTileConfig(pau, CONFIG_CURRFRM);
    pau->m_bTileCodingFex = WMAB_FALSE;
    pau->m_rgtci[pau->m_iCurrTile].m_bCodingFex = WMAB_FALSE;

    iBitsRem = (Int)pau->m_iPlusBits - ibstrmBitCount(paudec->m_pibsPlus);
    if (pau->m_bPlusV2 && (0==pau->m_iCurrTile))
        TRACEWMA_EXIT(wmaResult,
                      plusDecodeSuperframeHeaderFirstTileV2(paudec));

    if (pau->m_bPlusV2 && (pau->m_cTiles-1==pau->m_iCurrTile) &&
        WMAB_FALSE==pau->m_bLastTilePlusHeaderCoded)
        TRACEWMA_EXIT(wmaResult, 
                      plusDecodeSuperframeHeaderLastTileV2(paudec));

    prvSetPlusOrder(pau);

#if defined(BUILD_WMAPROLBRV2)
    if (WMAB_TRUE == pau->m_bReconProc)
    {
        TRACEWMA_EXIT(wmaResult, chexInitSubframeTilingInfo(pau, pau->m_cChInTile, pau->m_rgiChInTile,
                                          paudec->m_iCurrTile, WMAB_FALSE, WMAB_FALSE));
    }

    if (pau->m_bCx && !pau->m_bFirstPlusFrameAfterReset)
    {
        TRACEWMA_EXIT(wmaResult, chexTileInit(pau));
    }
#endif

exit:
    prvRestoreCurChannels(pau);
    return wmaResult;
}

WMARESULT plusDecodeTile(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    Fex *pfx = &pau->m_fex;
    Int iBitsRem;
    Bool bNoCodeRFx = WMAB_TRUE;
    Bool bNoCodeCx = WMAB_TRUE;
    Bool bNoCodeFx = WMAB_TRUE;
    Bool bUpdateCodingFex = WMAB_TRUE;

    prvSaveCurChannels(pau);
    prvSetOrigChannels(pau);

    if (WMAB_TRUE == paudec->m_bSkipPlus)
        goto exit;

    if (WMAB_FALSE==pau->m_bPlusV1 && WMAB_FALSE==pau->m_bPlusV2 &&
        WMAB_FALSE==pau->m_bReconProc)
        goto exit;

    if ((pau->m_bFirstPlusFrameAfterReset || pau->m_bSkipPlusDueToRFx) &&
        !pau->m_bPlusV1)
        goto exit;

    if (pau->m_bPlusV1)
        pau->m_bFreqexPresent = pau->m_bFreqex;

#if defined(BUILD_WMAPROLBRV2)
    TRACEWMA_EXIT(wmaResult, plusDecodeBase(paudec));
#endif
    CHECK_BITSEND();
#if defined(BUILD_WMAPROLBRV2)
    TRACEWMA_EXIT(wmaResult, plusDecodeCx(paudec, &bNoCodeCx));
#endif
    TRACEWMA_EXIT(wmaResult, plusDecodeFex(paudec, &bNoCodeFx));

    // update flags with actual situation
    pau->m_bTileCodingFex = (bNoCodeFx == WMAB_FALSE);
    pau->m_rgtci[pau->m_iCurrTile].m_bCodingFex = (U8)pau->m_bTileCodingFex;
#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bReconProc == WMAB_TRUE)
    {
        // need to feedback actual coding-fex decision to recon tile
        reconProcUpdateCodingFexFlag(pau);
        bUpdateCodingFex = WMAB_FALSE;
    }
#endif

#if defined(BUILD_WMAPROLBRV2)
    TRACEWMA_EXIT(wmaResult, plusDecodeReconFex(paudec, &bNoCodeRFx));
#endif

exit:
#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bReconProc == WMAB_TRUE && bUpdateCodingFex == WMAB_TRUE)
    {
        // need to feedback actual coding-fex decision to recon tile
        reconProcUpdateCodingFexFlag(pau);
        bUpdateCodingFex = WMAB_FALSE;
    }
#endif

#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bCx && WMAB_TRUE==bNoCodeCx)
        chexSetNoCodeCx(pau);
    if (pau->m_bReconFex && WMAB_TRUE==bNoCodeRFx)
        chexSetNoCodeRFx(pau);
#endif

    prvRestoreCurChannels(pau);
    return wmaResult;
}

#endif  // BUILD_WMAPROLBRV1

//*****************************************************************************************
//
// prvDecodeSubFrame
//
// Code Path:
//  lossy
//          SUBFRM_HDR -> SUBFRM_COEFDEC_LOSSY -----------------------------------------> SUBFRM_REC_LOSSY -> SUBFRM_DONE
//  lossless (mixed)
//          SUBFRM_HDR ----------------------> SUBFRM_COEFDEC_MLLM -> SUBFRM_REC_MLLM ----------------------> SUBFRM_DONE
//
//
//*****************************************************************************************
WMARESULT prvDecodeSubFrame (CAudioObjectDecoder* paudec)
{
    WMARESULT hr = WMA_OK;
    I16       iCh, iChSrc;
    CAudioObject* pau = paudec->pau;
    PerChannelInfo* ppcinfo;
    Bool fSkipAll;

    assert(pau->m_iVersion <= 2);
    assert(WMAB_FALSE == pau->m_bUnifiedLLM);

#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,DECODE_SUB_FRAME_PROFILE);
#endif
    while (paudec->m_subfrmdecsts != SUBFRM_DONE) {
        switch (paudec->m_subfrmdecsts)
        {
            case SUBFRM_HDR :   
                TRACEWMA_EXIT(hr, prvDecodeSubFrameHeader (paudec));
                assert (paudec->m_hdrdecsts == HDR_DONE);
                paudec->m_subfrmdecsts = SUBFRM_COEFDEC_LOSSY;
                paudec->pau->m_iCurrReconCoef = 0;             //iRecon is offset by -1 so comarison 
                paudec->m_iChannel = 0;
                prvResetRunLevelState(paudec); // reset run level decoding

                break;

            case SUBFRM_COEFDEC_LOSSY:
                TRACEWMA_EXIT(hr, (*(paudec->m_pfnDecodeCoefficient))(paudec, pau->m_rgpcinfo));
                paudec->m_subfrmdecsts = SUBFRM_REC_LOSSY;

                break;

            case SUBFRM_REC_LOSSY:
                // WMA Timestamps: To detect start-of-stream and discard correct amount of silence,
                // we need to verify claim that m_iPower[*] = 1, ForceMaskUpdate and actual power = 0.
                // If m_rgiCoefQ is all 0, we will accept that as actual power = 0 even though it is
                // theoretically possible for actual power != 0 if all bands inside noise-sub band are
                // substituted.
                if (CODEC_BEGIN == pau->m_codecStatus)
                {
                    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                    {
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;
                        if (ppcinfo->m_iPower != 0)
                            SetActualPower (ppcinfo->m_rgiCoefQ, ppcinfo->m_cSubbandActual,
                                           ppcinfo, pau->m_codecStatus);
                    }
                }

                //CCDUMP(0, 10);

                pau->m_qstQuantStep = qstCalcQuantStep(pau->m_iQuantStepSize,0);
                for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    if (ppcinfo->m_iPower != 0)
                    {
                        TRACEWMA_EXIT(hr, (*pau->aupfnInverseQuantize)(pau, ppcinfo, (I32*)ppcinfo->m_rguiWeightFactor));
                    }
                    else
                    {
                        memset (ppcinfo->m_rgiCoefRecon, 0, sizeof (CoefType) * AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,pau->m_fPad2XTransform,ppcinfo->m_cSubband));
                    }
                }

                //CCDUMP(1, 0);

#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
                if (pau->m_cChannel==1)
                    prvWmaShowFrames(pau->m_iFrameNumber, pau->m_iCurrSubFrame,
                        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
                        pau->m_cSubbandAdjusted,
                        "\nDecSub ", " %2d   0x%08x            [%4d %4d %4d]",
                        pau->m_rgpcinfo[0].m_iPower,
                        pau->m_rgpcinfo[0].m_rgiCoefRecon,
                        pau->m_cFrameSample,
                        pau->m_cSubFrameSample,
                        pau->m_cSubband );
                else
                    prvWmaShowFrames(pau->m_iFrameNumber, pau->m_iCurrSubFrame,
                        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
                        pau->m_cSubbandAdjusted, "\nDecSub ",
                        " %2d%2d 0x%08x 0x%08x [%4d %4d %4d]",
                        pau->m_rgpcinfo[0].m_iPower,
                        pau->m_rgpcinfo[1].m_iPower,
                        pau->m_rgpcinfo[0].m_rgiCoefRecon,
                        pau->m_rgpcinfo[1].m_rgiCoefRecon,
                        pau->m_cFrameSample,
                        pau->m_cSubFrameSample,
                        pau->m_cSubband );
#endif

                // Decode Givens angles & signs into inverse multichannel transform.
                TRACEWMA_EXIT(hr, prvDecodeChannelXform(paudec));

                // Apply top level hierarchical xform
                auInvChannelXForm (pau, WMAB_TRUE);
                // Apply bottom level hierarchical xform
                auInvChannelXForm (pau, WMAB_FALSE);

                // Check if all channels in this tile are zero (to be used later)
                fSkipAll = WMAB_TRUE;
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    if (pau->m_rgpcinfo[iChSrc].m_iPower)
                    {
                        fSkipAll = WMAB_FALSE;
                        break;
                    }
                }

#if defined (PRINT_EFFECTIVE_BW)
                printEffectiveBw(pau);
#endif // PRINT_EFFECTIVE_BW

            if ( ! pau->m_fNoiseSub )
            {   
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    Int iHighToBeZeroed;
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    // V4 only zeroed above HighCutOff when NoiseSubstitution was not in effect - e.g. it only zeros for HighRate
                    iHighToBeZeroed = sizeof(CoefType) * (ppcinfo->m_cSubbandAdjusted - pau->m_cHighCutOffAdjusted);
                    memset (ppcinfo->m_rgiCoefRecon + pau->m_cHighCutOffAdjusted, 0, iHighToBeZeroed);
#           if defined(_DEBUG) && defined(WMA_MONITOR)
                    {   Int ii;
                        for( ii = 0; ii < iHighToBeZeroed; ii += sizeof(Int) )
                            MONITOR_RANGE(gMR_CoefRecon,0);
                    }
#           endif
                }
            }

            if (WMAB_FALSE == fSkipAll)
            {
                for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                {
                    BP2Type fltAfterScaleFactor;
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    fltAfterScaleFactor = (pau->m_iVersion == 1) ? pau->m_fltDctScale :
                        ( BP2_FROM_FLOAT(1.0f) /ppcinfo->m_cSubband * 2);
                    // INTERPOLATED_DOWNSAMPLE
                    if (paudec->m_fLowPass)
                    {
                        auLowPass2(paudec, (CoefType*) ppcinfo->m_rgiCoefRecon,
                            ppcinfo->m_cSubband / 2);
                    }
                    if (ppcinfo->m_iPower != 0 || pau->m_iVersion > 2) 
                    {
                        // Due to the special buffer alignment of ppcinfo->m_rgiCoefQ, in 2x transform case,
                        // the second half of the ppcinfo->m_rgiCoefRecon buffer could be overwritten by
                        // prvDecodeRunLevel function. Therefore we need to clear it to zeros before calling DCTIV.
                        if (ppcinfo->m_cSubbandAdjusted > ppcinfo->m_cSubband)
                        {
                            memset(ppcinfo->m_rgiCoefRecon + ppcinfo->m_cSubband, 0, 
                                    (ppcinfo->m_cSubbandAdjusted - ppcinfo->m_cSubband)*sizeof(CoefType));
                        }
                        (*pau->aupfnDctIV) ((CoefType*) ppcinfo->m_rgiCoefRecon,
                            fltAfterScaleFactor, NULL, ppcinfo->m_cSubbandAdjusted,
                            pau->aupfnFFT, pau->m_hIntelFFTInfo, pau->m_iFrameNumber,
                            ppcinfo->m_iCurrSubFrame, pau->m_cFrameSampleAdjusted,
                            ppcinfo->m_cSubFrameSampleHalfAdjusted*2);
                    }
                }
            }

            //CCDUMP(2, 0);

            paudec->m_subfrmdecsts = SUBFRM_DONE;                
            break;
        }
    }
        
exit:
    //FUNCTION_PROFILE_STOP(&fp);
    return hr;
} // prvDecodeSubFrame

//*****************************************************************************************
//
// prvUpdateSubFrameConfig
//
//*****************************************************************************************
WMARESULT prvUpdateSubFrameConfig (CAudioObjectDecoder* paudec, Int iSizeNext)
{
    I16 iCh;
    CAudioObject* pau = paudec->pau;
/*** less than 0.5%
#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,UPDATE_SUB_FRAME_CONFIG_PROFILE);
#endif
*///

    assert (pau->m_iVersion <= 2);

    //constant size case; not sent
    if (iSizeNext == 0) {
//        assert (ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame > 0);
        paudec->m_fLastSubFrame = WMAB_TRUE;
        return WMA_OK;
    }

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        PerChannelInfo     *ppcinfo = &pau->m_rgpcinfo[ pau->m_rgiChInTile[ iCh ] ];
        SubFrameConfigInfo * const psfinfo = &ppcinfo->m_rgsubfrmconfig[ CONFIG_CURRFRM ];
        
        const I16 iCurr      = ppcinfo->m_iCurrSubFrame;
        const Int iStartCurr = psfinfo->m_rgiSubFrameStart[0] 
                             + psfinfo->m_rgiSubFrameSize [ iCurr ];

        psfinfo->m_rgiSubFrameSize[ iCurr+1 ] = (I16)iSizeNext;

        if( iStartCurr >= pau->m_cFrameSampleHalf )
        {
            paudec->m_fLastSubFrame = WMAB_TRUE;    //init the next frame
        }
        else
        {
            //must be within one frame; must have received the first one
            
            assert ( psfinfo->m_cSubFrame == iCurr+1 );
            //assert (iSizeNext < pau->m_cFrameSampleHalf);        //> 1 subfrm

            psfinfo->m_rgiSubFrameStart[0] += psfinfo->m_rgiSubFrameSize [ iCurr ];

            // confirm that subframe start + subframe size does not exceed the
            // length of a frame. such an occurance indicates corrupted bits.

            if( psfinfo->m_rgiSubFrameStart[0] + 
                psfinfo->m_rgiSubFrameSize [ iCurr+1 ] > pau->m_cFrameSampleHalf )
            {
                REPORT_BITSTREAM_CORRUPTION();
                return TraceResult(WMA_E_BROKEN_FRAME);
            }

            // detect subframes that are not aligned with their sizes.
            // this is not handled correctly by some 3rd party WMA-STD
            // decoder implementations.

            if( pau->m_iVersion < 3 &&
              ( psfinfo->m_rgiSubFrameStart[0] % 
                psfinfo->m_rgiSubFrameSize [ iCurr+1 ] != 0 ))
            {
	            audecLog((paudec, "- unaligned subframe detected! [ %d @ %d ]\n", 
		            psfinfo->m_rgiSubFrameSize [ iCurr+1 ],
		            psfinfo->m_rgiSubFrameStart[0] ));
            }

            psfinfo->m_cSubFrame++;
        }
        ppcinfo++;
    }

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder Related
    // V3 write subframing configuration meta file.
    if (paudec->m_fWriteMetaFile == WMAB_TRUE){
        if (paudec->m_fLastSubFrame == WMAB_TRUE){
            prvWriteMetaFileSubFrmConfig (paudec, paudec->pau->m_rgpcinfo, CONFIG_CURRFRM, paudec->m_pMetaFileDir);
        }
    }
#endif //WMA_COMPRESSION_TOOL
#endif // #if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)

    /***
#ifdef WMAPROFILE
    //FunctionProfileStop(&fp);
#endif
*///

    return WMA_OK;
} // prvUpdateSubFrameConfig

#if defined (DEBUG_BIT_DISTRIBUTION)
#define BIT_DISTRIBUTION_VARS        Int iBandCur=0, cBitGet=0;
#define BIT_DISTRIBUTION_PRECHECK    cBitGet = g_cBitGet
#define BIT_DISTRIBUTION_POSTCHECK   { \
                                        ppcinfo->m_rgcBitsPerBand[iBandCur] += g_cBitGet - cBitGet;\
                                        while (pau->m_rgiBarkIndexOrig[iBandCur+1] < (*piRecon * pau->m_cFrameSampleHalf/ppcinfo->m_cSubbandAdjusted)) \
                                        {\
                                         iBandCur++;\
                                        }\
                                     }
#define PRINT_BIT_DISTRIBUTION \
    {\
       Int iBand;\
       fprintf(stdout, "Frame %3d Tile %2d Ch%1d: ", \
               (pau->m_iVersion < 3 ? pau->m_iFrameNumber : pau->m_iFrameNumber+1), paudec->m_iCurrTile, iChSrc);\
       for (iBand = 0; iBand < pau->m_rgcValidBarkBand[0]; iBand++)\
       {\
           fprintf(stdout, " %d", ppcinfo->m_rgcBitsPerBand[iBand]);\
       }\
       fprintf(stdout, "\n");\
    }
#else // so !DEBUG_BIT_DISTRIBUTION
#define BIT_DISTRIBUTION_VARS    
#define BIT_DISTRIBUTION_PRECHECK
#define BIT_DISTRIBUTION_POSTCHECK
#define PRINT_BIT_DISTRIBUTION
#endif //  DEBUG_BIT_DISTRIBUTION

#define AUINV_RECON_CHANNEL
#define AUINV_RECON_CHANNEL_DEC
#include "msaudiotemplate.c"
#undef AUINV_RECON_CHANNEL_DEC
#undef AUINV_RECON_CHANNEL

//#define DUMP_QUANTVALS
#ifdef DUMP_QUANTVALS
Void prvDumpQuantVals(CAudioObjectDecoder *paudec,
                      PerChannelInfo *ppcinfo)
{
    FILE *fp = NULL;
    Int cSubframeSize = ppcinfo->m_cSubFrameSampleHalf;

    fp = fopen("wmatrain.raw", "ab");
    if (fp == NULL) return;

    fwrite(&cSubframeSize, sizeof(I32), 1, fp);
    fwrite(ppcinfo->m_rgiCoefRecon, sizeof(CoefType), cSubframeSize, fp);

    fclose(fp);
}
#endif // DUMP_QUANTVALS

//*****************************************************************************************
//
// prvDecodeSubFrameHighRate
// 
// Code Path:
//  lossy
//          SUBFRM_HDR -> SUBFRM_COEFDEC_LOSSY -----------------------------------------> SUBFRM_REC_LOSSY -> SUBFRM_DONE
//  lossless (mixed)
//          SUBFRM_HDR ----------------------> SUBFRM_COEFDEC_MLLM -> SUBFRM_REC_MLLM ----------------------> SUBFRM_DONE
//
//*****************************************************************************************
WMARESULT prvDecodeSubFrameHighRate (CAudioObjectDecoder* paudec)
{
    WMARESULT hr = WMA_OK;
    I16     iCh, iChSrc;
    PerChannelInfo* ppcinfo;
    CAudioObject* pau = paudec->pau;
    Bool fSkipAll, fOnHold = WMAB_FALSE;

#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,DECODE_SUB_FRAME_HIGH_RATE_PROFILE);
#endif  // WMAPROFILE

    while (paudec->m_subfrmdecsts != SUBFRM_DONE) {
        switch (paudec->m_subfrmdecsts)
        {
            case SUBFRM_HDR :   
                TRACEWMA_EXIT(hr, prvDecodeSubFrameHeader(paudec));    
                assert (paudec->m_hdrdecsts == HDR_DONE);

#if defined(BUILD_WMAPROLBRV2)
                initSubframeTilingInfo(pau, pau->m_cChInTile, pau->m_rgiChInTile);
#endif // BUILD_WMAPROLBRV1

#ifdef WMA_COMPRESSION_TOOL
                if (paudec->m_fWriteMetaFile == WMAB_TRUE)
                {
                    I32 iPCMFrameNumber = prvGetPCMFrameNumber (pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);
                    TRACEWMA_EXIT(hr, prvWriteMetaFileMask (paudec, iPCMFrameNumber, paudec->m_iCurrTile, paudec->m_pMetaFileDir));
                }

                if (pau->m_bSegDecodePeekMode == WMAB_TRUE)
                {
                    if (pau->m_iVersion >= 3) {
                        if (pau->m_bUnifiedLLM == WMAB_TRUE)
                            pau->m_bPeekModeNonSekPkt = WMAB_TRUE;
                    }
                    pau->m_bPeekModeDone = WMAB_TRUE;
                    return (hr = WMA_E_ONHOLD);
                }
#endif //WMA_COMPRESSION_TOOL
                if (pau->m_bUnifiedLLM == WMAB_FALSE)
                {
                    pau->m_qstQuantStep = qstCalcQuantStep(pau->m_iQuantStepSize,0);

#if defined(BUILD_WMAPROLBRV1)
                    if (pau->m_bNeedMaskProc)
                    {
                        freqexSetChannelDependencyGroup(pau, pau->m_rgChannelGrpInfo,
                                                        pau->m_cChannelGroup);
                        freqexZeroNonzeroMask(pau);
                    }
                    TRACEWMA_EXIT(hr, prvInitPlusStream(paudec));
                    TRACEWMA_EXIT(hr, plusDecodeTileHeader(paudec));
                    TRACEWMA_EXIT(hr, plusPeekBasePlusBit(paudec));
#endif

                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                    {
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;
                        if (!ppcinfo->m_bNoDecodeForCx && NULL != ppcinfo->m_rgiCoefRecon )
                            memset (ppcinfo->m_rgiCoefRecon, 0, sizeof (CoefType) * pau->m_cHighCutOffAdjusted);
#if defined (DEBUG_BIT_DISTRIBUTION)
                        memset (ppcinfo->m_rgcBitsPerBand, 0, sizeof(I32) * NUM_BARK_BAND);
#endif 
                    }
                    paudec->m_subfrmdecsts = SUBFRM_COEFDEC_LOSSY;

                    //iRecon is offset by -1 so comarison 
                    paudec->pau->m_iCurrReconCoef = (I16) (pau->m_cLowCutOff-1);
    
                    paudec->m_iChannel = 0;
                    prvResetRunLevelState(paudec); // reset run level decoding
                }
                else
                {
                    assert(pau->m_iVersion >= 3);
                    
                    pau->m_cLastCodedIndex = (I16)pau->m_cHighCutOff;

                    //Not necessary to call resetall function for isolated MLLM>
                    //isolated MLLM
                    if (pau->m_bUnifiedLLM == WMAB_TRUE && pau->m_bUnifiedPureLLMCurrFrm != WMAB_TRUE) {
                        ASSERTWMA_EXIT(hr, prvLLMVerBResetAllCom_MLLM(pau, pau->m_rgpcinfo));
                    }

                    // Set seekable MLLMUsePLLM frames.
                    // The first and last MLLMUsePLLM can also be set in below call.
                    if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && pau->m_bSeekable == WMAB_TRUE) {
                        ASSERTWMA_EXIT(hr, prvLLMVerBResetAllCom_MLLM(pau, pau->m_rgpcinfo));
                    }

                    // indent shows the level.
                    paudec->m_subfrmdecsts = SUBFRM_COEFDEC_MLLM;
                        paudec->m_iChannel = 0;
                            paudec->m_iCurrPart = 0;
                                paudec->m_LLMdecsts = CH_LPC_COEF;
                                    paudec->m_iCurrLPCCoef = 0;
                        
                                    paudec->pau->m_iCurrReconCoef = 0;
                                        paudec->m_Colombdecsts = FIRST_PART;
                                            paudec->m_iResQ = 0;
                                            paudec->m_iRem = 0;
                }
                break;

            case SUBFRM_COEFDEC_LOSSY:
                //Decode coefficents for sum channel or left & right channels 
                for (; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) 
                {
                    iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;
                    paudec->m_cMaxRun = (I16) LOG2 (ppcinfo->m_cSubbandActual - 1) + 1;

#if defined(BUILD_INTEGER)
                    ppcinfo->m_cLeftShiftBitsTotal = pau->m_cLeftShiftBitsFixedPre;
#endif

                    if (ppcinfo->m_iPower != 0)
                    {
                        if (pau->m_iVersion >= 3) {
                            if (!pau->m_fHalfTransform)
                            {
                                hr = auInvRlcCoefV3_Channel (pau, paudec, ppcinfo, iChSrc);
                            }
                            else
                            {
                                // Reduced memory
                                hr = auInvRlcCoefV3_ChannelHT (pau, paudec, ppcinfo, iChSrc);
                            }

                            if ((WMA_E_ONHOLD == hr) && ibstrmNoMoreInput(&paudec->m_ibstrm) && paudec->m_fSPDIF)
                            {
                                fOnHold = WMAB_TRUE;
                            }
                            else
                            {
                                if (WMA_FAILED(hr))
                                {
                                    int dummy = TraceResult(hr);
                                    goto exit;
                                }
                            }
#ifdef DUMP_QUANTVALS
                            prvDumpQuantVals(paudec, ppcinfo);
#endif
                        } 
                        else {
                            TRACEWMA_EXIT(hr, auReconCoefficentsHighRate (pau, paudec, ppcinfo));
                        } 
                    } 
                    pau->m_cLastCodedIndex = max(pau->m_cLastCodedIndex, ppcinfo->m_cLastCodedIndex);

                   // CHECKCHECK - rescale for BUILD_INTEGER...
                    // rescale here to prevent overflow, in case v3 channel
                    // levels too high -- to be done

                    if(pau->m_iVersion == 1) 
                    {
                        DEBUG_ONLY(paudec->m_ibstrm.m_cFrmBitCnt += ibstrmBitsLeft (&paudec->m_ibstrm) % 8;)
                        ibstrmFlush(&paudec->m_ibstrm);
                    }

                    //usually <= V2 should only go up to highCutoff but certain V1 contents do go up as high as m_cSubband
                    assert (paudec->pau->m_iCurrReconCoef <= (I16) ppcinfo->m_cSubband);
                    pau->m_iCurrReconCoef = (I16) (pau->m_cLowCutOff-1);             //iRecon is offset by -1 so comarison 
                    prvResetRunLevelState(paudec); // reset run level decoding
                }
#if defined(BUILD_WMAPROLBRV1) && defined(BUILD_WMAPROLBRV3)
                if (pau->m_fBasePlusPresentTile == WMAB_FALSE)
                {
                    U16 cLastCodedIndex = pau->m_cLastCodedIndex;

                    TRACEWMA_EXIT(hr, plusDecodeBasePeak(paudec));
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                    {
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;

                        if (pau->m_bNeedMaskProc)
                            freqexSetGroup(pau, iChSrc, WMAB_FALSE, WMAB_FALSE);

                        TRACEWMA_EXIT(hr, plusDecodeBasePeak_Channel(paudec, ppcinfo));
                        // pau->m_cLastCodedIndex should be unchanged during peak decoding
                        if (ppcinfo->m_cLastCodedIndex > cLastCodedIndex)
                            cLastCodedIndex = ppcinfo->m_cLastCodedIndex;
                    }
                    pau->m_cLastCodedIndex = max(pau->m_cLastCodedIndex, cLastCodedIndex);
                }
#endif
                // WMAFprintf(stdout, "%f\n", (Float)pau->m_cLastCodedIndex / (Float)ppcinfo->m_cSubband);
                // scale m_cLastCodedIndex to deal with half-transforms
                if (pau->m_fHalfTransform && pau->m_iVersion > 2)
                {
                    pau->m_cLastCodedIndex = min(pau->m_cLastCodedIndex, 
                        (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubband / 2);
                }
                paudec->m_subfrmdecsts = SUBFRM_REC_LOSSY;
                break;
          
            case SUBFRM_COEFDEC_MLLM:
#if defined (BUILD_WMAPRO)
                assert(pau->m_iVersion >= 3);
                assert(pau->m_bUnifiedLLM == WMAB_TRUE);
                for (; paudec->m_iChannel < pau->m_cChInTile; paudec->m_iChannel++) 
                {
                    iChSrc = pau->m_rgiChInTile [paudec->m_iChannel];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;

#if defined(BUILD_INTEGER)
                    ppcinfo->m_cLeftShiftBitsTotal = pau->m_cLeftShiftBitsFixedPre;
#endif

                    if (ppcinfo->m_iPower != 0)
                    {
                        TRACEWMA_EXIT(hr, prvDecodeSubFrameChannelResidueMono_Unified_MLLM_Or_PLLM(paudec->pau, paudec, ppcinfo));
                    } 
                    if (pau->m_bOutputRawPCM == WMAB_FALSE) {
//                        assert (paudec->pau->m_iCurrReconCoef <= (I16) ppcinfo->m_cSubband /2);
                    }
                    else {
                        assert (paudec->pau->m_iCurrReconCoef <= (I16) ppcinfo->m_cSubband);
                    }

                    if (ppcinfo->m_iPower != 0)
                    {
                        TRACEWMA_EXIT(hr, prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_Or_PLLM(paudec->pau, paudec, ppcinfo));                        
                        // WMA Timestamps: To detect start-of-stream and discard correct amount of silence,
                        // we need to verify claim that m_iPower[*] = 1, ForceMaskUpdate and actual power = 0.
                        ppcinfo->m_iActualPower = 0;
                        if (CODEC_BEGIN == pau->m_codecStatus)
                        {
                            SetActualPowerHighRate (pau->m_fWMAProHalfTransform ? pau->m_rgiCoefReconMLLMOrig : ppcinfo->m_rgiCoefRecon, 
                                ppcinfo->m_cSubbandAdjusted, ppcinfo, pau->m_codecStatus);
                        }
                    }
                    else 
                    {
                        memset (pau->m_fWMAProHalfTransform ? pau->m_rgiCoefReconMLLMOrig : ppcinfo->m_rgiCoefRecon, 
                            0, sizeof (CoefType) * ppcinfo->m_cSubbandAdjusted);
                        ppcinfo->m_iActualPower = 0;
                    }
                    
                    if (pau->m_fWMAProHalfTransform)
                    {
                        // Decimation is already done: Copy over results
                        memcpy(ppcinfo->m_rgiCoefRecon, pau->m_rgiCoefReconMLLMOrig, sizeof (CoefType) * ppcinfo->m_cSubbandAdjusted);
                    }
                    
                    // set up for next channel.
                    paudec->m_iCurrPart = 0;
                    paudec->m_LLMdecsts = CH_LPC_COEF;
                    paudec->m_iCurrLPCCoef = 0;

                    paudec->pau->m_iCurrReconCoef = 0;
                    paudec->m_Colombdecsts = FIRST_PART;
                    paudec->m_iResQ = 0;
                    paudec->m_iRem = 0;
                }
#endif // BUILD_WMAPRO
                paudec->m_subfrmdecsts = SUBFRM_REC_MLLM;
                break;

            // clear those zero coefficient to zero.
            case SUBFRM_REC_MLLM:
#if defined(BUILD_WMAPRO) && defined(BUILD_INTEGER)
                // postscale
                if (WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
                    TRACEWMA_EXIT(hr, auPostScaleCoeffsV3(pau));
#endif // BUILD_WMAPRO
        #if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
                if (pau->m_cChannel==1)
                    prvWmaShowFrames(pau->m_iFrameNumber, pau->m_iCurrSubFrame,
                        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
                        pau->m_cSubbandAdjusted,
                        "\nDecSubH", " %2d   0x%08x            [%4d %4d %4d]",
                        pau->m_rgpcinfo[0].m_iPower,
                        pau->m_rgpcinfo[0].m_rgiCoefRecon,
                        pau->m_cFrameSample,
                        pau->m_cSubFrameSample,
                        pau->m_cSubband );
                else
                    prvWmaShowFrames(pau->m_iFrameNumber, pau->m_iCurrSubFrame,
                        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
                        pau->m_cSubbandAdjusted,
                        "\nDecSubH", " %2d%2d 0x%08x 0x%08x [%4d %4d %4d]",
                        pau->m_rgpcinfo[0].m_iPower,
                        pau->m_rgpcinfo[1].m_iPower,
                        pau->m_rgpcinfo[0].m_rgiCoefRecon,
                        pau->m_rgpcinfo[1].m_rgiCoefRecon,
                        pau->m_cFrameSample,
                        pau->m_cSubFrameSample,
                        pau->m_cSubband );
        #endif
                paudec->m_subfrmdecsts = SUBFRM_DONE;   
                break;

            case SUBFRM_REC_LOSSY:
              #ifdef WMA_COMPRESSION_TOOL
                if (paudec->m_fParsingOnly)
                {
                    paudec->m_subfrmdecsts = SUBFRM_DONE;                
                    break;
                }
              #endif //WMA_COMPRESSION_TOOL

                for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    ppcinfo = pau->m_rgpcinfo + iChSrc;

                    PRINT_BIT_DISTRIBUTION;
    
                    ppcinfo->m_iActualPower = 0;
                    if (!ppcinfo->m_bNoDecodeForCx)
                    {
                        if (ppcinfo->m_iPower != 0)
                        {
                            // WMA Timestamps: To detect start-of-stream and discard correct amount of silence,
                            // we need to verify claim that m_iPower[*] = 1, ForceMaskUpdate and actual power = 0.
                            if (CODEC_BEGIN == pau->m_codecStatus)
                            {
                                SetActualPowerHighRate (ppcinfo->m_rgiCoefRecon, 
                                                        ppcinfo->m_cSubband, ppcinfo, pau->m_codecStatus);
                            }
                        }
                        else 
                        {
                            memset (ppcinfo->m_rgiCoefRecon, 0, sizeof (CoefType) * ppcinfo->m_cSubbandAdjusted);
                        }
                    }
                }
        #if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
                if (pau->m_cChannel==1)
                    prvWmaShowFrames(pau->m_iFrameNumber, pau->m_iCurrSubFrame,
                        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
                        pau->m_cSubbandAdjusted,
                        "\nDecSubH", " %2d   0x%08x            [%4d %4d %4d]",
                        pau->m_rgpcinfo[0].m_iPower,
                        pau->m_rgpcinfo[0].m_rgiCoefRecon,
                        pau->m_cFrameSample,
                        pau->m_cSubFrameSample,
                        pau->m_cSubband );
                else
                    prvWmaShowFrames(pau->m_iFrameNumber, pau->m_iCurrSubFrame,
                        pau->m_cFrameSampleAdjusted, pau->m_cSubFrameSampleAdjusted,
                        pau->m_cSubbandAdjusted,
                        "\nDecSubH", " %2d%2d 0x%08x 0x%08x [%4d %4d %4d]",
                        pau->m_rgpcinfo[0].m_iPower,
                        pau->m_rgpcinfo[1].m_iPower,
                        pau->m_rgpcinfo[0].m_rgiCoefRecon,
                        pau->m_rgpcinfo[1].m_rgiCoefRecon,
                        pau->m_cFrameSample,
                        pau->m_cSubFrameSample,
                        pau->m_cSubband );
        #endif

                // Check if all channels in this tile are zero (to be used later)
                fSkipAll = WMAB_TRUE;
                for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                {
                    iChSrc = pau->m_rgiChInTile [iCh];
                    if (pau->m_rgpcinfo[iChSrc].m_iPower)
                    {
                        fSkipAll = WMAB_FALSE;
                        break;
                    }
                }

                // figure out maximum per channel quantization stepsize
#if defined(BUILD_INTEGER)
                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll &&
                    WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
                    TRACEWMA_EXIT(hr, auPreScaleQuantV3(pau, WMAB_FALSE));
#endif
                // Decode Givens angles & signs into inverse multichannel transform.
                TRACEWMA_EXIT(hr, prvDecodeChannelXform(paudec));

                CCDUMP(0, 0);
                // prescale for channel transform and inverse quantization
#if defined(BUILD_INTEGER)
                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll &&
                    WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
                {
                    DEBUG_ONLY( pau->m_maxOutputAllowed =
                                (CoefType)(MAXINTVAL_CH/pau->m_cChInTile) );
                    TRACEWMA_EXIT(hr,
                        auPreScaleCoeffsV3(pau,
                                           (CoefType)pau->m_iLog2MaxIntvalCh,
                                           WMAB_FALSE, WMAB_TRUE, 'C' ));
                }
#endif
                CCDUMP(1, 2);
                // Apply top level hierarchical xform
                auInvChannelXForm (pau, WMAB_TRUE);
                // Apply bottom level hierarchical xform
                auInvChannelXForm (pau, WMAB_FALSE);

#if defined(BUILD_INTEGER)
                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll &&
                    WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
                {
                    // pre-scale coefficients prior to inverse
                    // quantization. subtract 1 from # of bits
                    // used, so that iDCT input is unlikely to
                    // require pre-scaling.

                    DEBUG_ONLY( pau->m_maxOutputAllowed =
                                (CoefType)MAXINTVAL_IQ );
                    TRACEWMA_EXIT(hr,
                        auPreScaleCoeffsV3(pau,
                            (CoefType)MAXINTVAL_IQ_LOG2-1,
                            WMAB_TRUE, WMAB_FALSE, 'Q' ));
                }
#endif

                CCDUMP(2, 2);

                // Due to Scrunch Bug #32, we used to always force mask update at
                // the start (all channels). We no longer do this for v3, so we
                // must not call auInvWeightSpectrumV3 for zero-power subframes at the
                // start-of-stream, because the first mask update will come with the
                // first non-zero subframe. Note that if even one channel is non-zero,
                // we must process all channels due to v3 auInvChannelXForm.
                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll) {
                    //prvDumpQuantStepSizesV3(pau, NULL);
                    // On each channel, do the mask weighting.
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                    {
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;

                        if (ppcinfo->m_bNoDecodeForCx)
                            continue;

                        // discard subwoofer coeffs.
                        if (iChSrc == pau->m_nSubWooferChannel &&
                            WMAB_FALSE == ppcinfo->m_bNoDecodeForCx) {
                            assert(pau->m_cSubWooferCutOffIndex < ppcinfo->m_cSubband);
                            memset((Void*)(ppcinfo->m_rgiCoefRecon + pau->m_cSubWooferCutOffIndex),
                                    0, sizeof(CoefType) * (ppcinfo->m_cSubbandAdjusted - pau->m_cSubWooferCutOffIndex));
                        }

                        pau->m_iCurrReconCoef = -1;
                        TRACEWMA_EXIT(hr, auInvWeightSpectrumV3 (pau, ppcinfo, 
                                      ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0]));
                    }
                }

                CCDUMP(3, 1);

#if defined(BUILD_WMAPROLBRV1)
#if defined(BUILD_WMAPROLBRV3)
                // retrieve mask values which have been modified in base peak coding
                if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2 &&
                    pau->m_fBasePlusPresentTile == WMAB_FALSE &&
                    pau->m_bBasePeakPresentTile == WMAB_TRUE)
                {
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                    {
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;
                        if( ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0] )
                            memcpy(ppcinfo->m_rgiMaskQ,
                                   ppcinfo->m_piBasePeakMaskQSave, 
                                   pau->m_cValidBarkBand * sizeof(Int));
                        else
                            memcpy(ppcinfo->m_rgiMaskQResampled,
                                   ppcinfo->m_piBasePeakMaskQSave, 
                                   pau->m_cValidBarkBand * sizeof(Int));
                    }
                }
#endif
                TRACEWMA_EXIT(hr, plusDecodeTile(paudec));
#endif
                // Compression Tool: dump MDCT coefficients here
#ifdef WMA_COMPRESSION_TOOL
                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll) 
                {
                    if (paudec->m_fWriteMetaFile == WMAB_TRUE)
                    {
                        I32 iPCMFrameNumber = prvGetPCMFrameNumber (pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);
                        TRACEWMA_EXIT(hr, prvWriteMetaFileMDCTCoeffs (paudec, iPCMFrameNumber, paudec->m_iCurrTile, paudec->m_pMetaFileDir));
                    }
                }
#endif //WMA_COMPRESSION_TOOL

#if defined (PRINT_EFFECTIVE_BW)
                printEffectiveBw(pau);
#endif   // PRINT_EFFECTIVE_BW

#if defined(BUILD_INTEGER)
                // prescale for fft

                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll &&
                    WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
                {
                    DEBUG_ONLY( pau->m_maxOutputAllowed =
                                (CoefType)MAXINTVAL_FFT/2 );
                    TRACEWMA_EXIT(hr,
                        auPreScaleCoeffsV3(pau,
                                           (CoefType)MAXINTVAL_FFT_LOG2-1,
                                           WMAB_FALSE, WMAB_FALSE, 'D' ));
                }
#endif

                CCDUMP(4, 1);

#ifdef CACHE_IMPACT_TEST
			{
				extern int g_iCacheImpactReadSize;
				extern int *g_pCacheImpactReadBuffer;
				extern void ReadBuffer(int *p, int n);

				ReadBuffer(g_pCacheImpactReadBuffer, g_iCacheImpactReadSize);
			}
#endif

                if (WMAB_FALSE == fSkipAll || pau->m_bFreqex
#if defined(BUILD_WMAPROLBRV2)
                    || pau->m_fBasePlus
#endif
                    )
                {
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
                    {
                        BP2Type fltAfterScaleFactor;
                        iChSrc = pau->m_rgiChInTile [iCh];
                        ppcinfo = pau->m_rgpcinfo + iChSrc;
                        fltAfterScaleFactor = (pau->m_iVersion == 1) ? pau->m_fltDctScale :
                                          ( BP2_FROM_FLOAT(1.0f)/ppcinfo->m_cSubband * 2 );

                        if (ppcinfo->m_bNoDecodeForCx)
                            continue;

                        // INTERPOLATED_DOWNSAMPLE
                        if (paudec->m_fLowPass)
                        {
                            auLowPass2(paudec, (CoefType*) ppcinfo->m_rgiCoefRecon,
                                ppcinfo->m_cSubband / 2);
                        }
                        if (ppcinfo->m_iPower != 0 || pau->m_iVersion > 2) 
                        {
                            // Due to the special buffer alignment of ppcinfo->m_rgiCoefQ, in 2x transform case,
                            // the second half of the ppcinfo->m_rgiCoefRecon buffer could be overwritten by
                            // prvDecodeRunLevel function. Therefore we need to clear it to zeros before calling DCTIV.
                            if (ppcinfo->m_cSubbandAdjusted > ppcinfo->m_cSubband)
                            {
                                memset(ppcinfo->m_rgiCoefRecon + ppcinfo->m_cSubband, 0, 
                                        (ppcinfo->m_cSubbandAdjusted - ppcinfo->m_cSubband)*sizeof(CoefType));
                            }
                            catchFP();
                            (*pau->aupfnDctIV) ((CoefType*) ppcinfo->m_rgiCoefRecon,
                                fltAfterScaleFactor, NULL, ppcinfo->m_cSubbandAdjusted,
                                pau->aupfnFFT, pau->m_hIntelFFTInfo, pau->m_iFrameNumber, ppcinfo->m_iCurrSubFrame,
                                pau->m_cFrameSampleAdjusted,
                                ppcinfo->m_cSubFrameSampleHalfAdjusted * 2);
                            initFP();
                        }
                    }
                }

                CCDUMP(5, 1);

#if defined(BUILD_INTEGER)
                // postscale
                if (pau->m_iVersion > 2 && WMAB_FALSE == fSkipAll &&
                    WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
                    TRACEWMA_EXIT(hr, auPostScaleCoeffsV3(pau));
#endif

                CCDUMP(6, 0);

                paudec->m_subfrmdecsts = SUBFRM_DONE;                
                break;
        }
    }

exit:
#ifdef WMAPROFILE
    //FunctionProfileStop(&fp);
#endif  // WMAPROFILE

    if (fOnHold)
        return WMA_E_ONHOLD;
    return hr;
} //prvDecodeSubFrameHighRate

// Decoder-only portion of auAdaptToSubFrameConfig
WMARESULT auAdaptToSubFrameConfigDEC (CAudioObject* pau)
{
    Int iCh, iChSrc, iFrameSize;
    PerChannelInfo* ppcinfo = NULL;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile [iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        // Why use the buffer from the end? chao
        if (WMAB_FALSE == pau->m_bPureLosslessMode &&
            WMAB_FALSE == pau->m_bReconProc)
        {
            // ======== Setup the rgiCoefRecon to the proper place ========
            iFrameSize = AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform, pau->m_fPad2XTransform, pau->m_cFrameSampleHalf);
            ppcinfo->m_rgiCoefRecon   = pau->m_rgiCoefReconOrig + (iFrameSize*3/2) * iChSrc + 
                                             (iFrameSize >> 1) +
                                             ppcinfo->m_iCurrCoefPosition;
            ppcinfo->m_rgCoefRecon        = (CoefType*)(ppcinfo->m_rgiCoefRecon);
            ppcinfo->m_iCurrCoefPosition += (I16)ppcinfo->m_cSubFrameSampleHalfAdjusted;
        }
    }

    return WMA_OK;
} // auAdaptToSubFrameConfigDEC
    
//reconfig the decoder: don't allow memroy allocation here!!!
WMARESULT prvReConfig (CAudioObjectDecoder* paudec)
{
    I16 i;
    CAudioObject* pau = paudec->pau;
    if (pau->m_iWeightingMode == LPC_MODE || pau->m_fNoiseSub)
    {
        //low rate or mid rate
        paudec->m_pfnDecodeSubFrame = prvDecodeSubFrame;
#ifdef WMA_COMPRESSION_TOOL
        assert(!"Compression tool does not support LPC_MODE and m_fNoiseSub");
#endif //WMA_COMPRESSION_TOOL
    }
    else
    {
        //high rate
        paudec->m_pfnDecodeSubFrame = prvDecodeSubFrameHighRate;
    }
    for (i = 0; i < pau->m_cChannel; i++)
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + i;

        if (pau->m_iWeightingMode == LPC_MODE)
        { // LPC
            ppcinfo->m_rguiWeightFactor = pau->m_rguiWeightFactor + DOUBLE(pau->m_fPad2XTransform,pau->m_cFrameSampleHalf) * i;
#if defined(LPC_COMPARE)
            ppcinfo->m_rgfltWeightFactor = (Float*)(pau->m_rguiWeightFactor + DOUBLE(pau->m_fPad2XTransform,pau->m_cFrameSampleHalf) * i);
#endif
        } else 
        {
            ppcinfo->m_rguiWeightFactor =(U32*) pau->m_rgpcinfo [i].m_rgiMaskQ;
#if defined(LPC_COMPARE)
            ppcinfo->m_rgfltWeightFactor = (Float*)(pau->m_rgpcinfo [i].m_rgiMaskQ);
#endif
        }

    } // for
    return WMA_OK;
} // prvReConfig

#if defined (BUILD_WMAPRO)
void prvSetChDnMix(ChDnMixType **rgrgDnMix, Int nSrc, Int nDst,
                   Int *channel, ChDnMixType *coeff)
{
    Int i, j, k;
    ChDnMixType scale;

    scale = (ChDnMixType)0;
#ifndef BUILD_INTEGER
    for (i=0; i < nSrc; i++) scale += coeff[i];
#endif
    for (i=0, k=0; i < nDst; i++) {
        for (j=0; j < nSrc; j++, k++) {
            rgrgDnMix[i][channel[k]] = coeff[j];
#ifndef BUILD_INTEGER
            rgrgDnMix[i][channel[k]] /= scale;
#endif
        }
    }
}
#endif // BUILD_WMAPRO

#if defined(_SH4_)
#pragma warning(push)
#pragma warning(disable:4719)
#endif

#if 0 // for testing matrix 2 coeff, coeff 2 matrix code.
#include "downmix.h"
void DownmixTest(CAudioObjectDecoder *paudec)
{
    Int numCoeff;
    I32 *pMatrix, *pMatrix2, *pCoeff;
    Int ii, jj;

    pMatrix = (I32*)malloc(12*sizeof(I32));
    pMatrix2 = (I32*)malloc(12*sizeof(I32));
    for (jj=0; jj < 2; jj++) {
        for (ii=0; ii < 6; ii++) {
            if (paudec->m_rgrgfltChDnMixMtx[jj][ii] <= 0.0)
                pMatrix[ii*2 + jj] = I32_MIN;
            else
                pMatrix[ii*2 + jj] = (I32)((65536.0*20.0)*log10(
                                         paudec->m_rgrgfltChDnMixMtx[jj][ii]));
        }
    }
    //pMatrix[0] = -100000;

    WMADownmixMatrixToCoeff(pMatrix, NULL, &numCoeff,
                                    6, 2, 0x3f, 0x3);
    pCoeff = (I32*)malloc(numCoeff*sizeof(I32));
    WMAownmixMatrixToCoeff(pMatrix, pCoeff, &numCoeff,
                                    6, 2, 0x3f, 0x3);

    WMADownmixCoeffToMatrix(pMatrix2, pCoeff, numCoeff,
                                    6, 2, 0x3f, 0x3);

    for (jj=0; jj < 2; jj++) {
        for (ii=0; ii < 6; ii++) {
            WMAPrintf("%8d ", pMatrix[ii*2 + jj]);
        }
        WMAPrintf("\n");
    }
    WMAPrintf("\n");

    for (jj=0; jj < 2; jj++) {
        for (ii=0; ii < 6; ii++) {
            WMAPrintf("%8d ", pMatrix2[ii*2 + jj]);
        }
        WMAPrintf("\n");
    }
    WMAPrintf("\n");

    for (ii=0; ii < numCoeff; ii++) {
        WMAPrintf("%8d ", pCoeff[ii]);
    }
    WMAPrintf("\n");

    free(pMatrix);
    free(pMatrix2);
    free(pCoeff);
}
#include "../pktparse/pktparse.c"
#endif

#if defined (BUILD_WMAPRO)


// !!!Changes rgfltInp!!!
Void prvDumbBubble(Float *rgfltInp, Int * rgiInMap, Int cNum)
{
    Int i, iTmp;
    Bool fChanged;
    Float fltTmp;

    fChanged = WMAB_FALSE;

    do {
        fChanged=WMAB_FALSE;
        for(i = 0; i < cNum-1; i++)
        {
            if (rgfltInp[i] > rgfltInp[i+1])
            {
                fltTmp        = rgfltInp[i];
                iTmp          = rgiInMap[i];
                rgfltInp[i]   = rgfltInp[i+1];
                rgiInMap[i]   = rgiInMap[i+1];
                rgfltInp[i+1] = fltTmp;
                rgiInMap[i+1] = iTmp;
                fChanged      = WMAB_TRUE;
            }
        }
    } while (fChanged);

    return;
} // prvDumbBubble

WMARESULT prvInitNonLFEChDnMixThroughProjections (
    Int          cSrcChan,
    U32            nSrcChannelMask,
    Int          cDstChan,
    U32            nDstChannelMask,
    Float**        rgrgfltChDnMixMtx)
{
    WMARESULT wmaResult = WMA_OK;

    // Speaker direction in degrees: all must be +ve, between 0 & 360.
    const Float rgfltSpeakerDirection[] =
    {
        -30.0F + 360.0F, // SPEAKER_FRONT_LEFT
        +30.0F, // SPEAKER_FRONT_RIGHT
        0.0F,   // SPEAKER_FRONT_CENTER 
        0.0F,   // SPEAKER_LOW_FREQUENCY 
        -135.0F + 360.0F, // SPEAKER_BACK_LEFT              
        +135.0F, // SPEAKER_BACK_RIGHT
        -15.0F + 360.0F,  // SPEAKER_FRONT_LEFT_OF_CENTER
        +15.0F,  // SPEAKER_FRONT_RIGHT_OF_CENTER
        +180.0F, // SPEAKER_BACK_CENTER
        -110.0F + 360.0F, // SPEAKER_SIDE_LEFT
        +110.0F  // SPEAKER_SIDE_RIGHT
        // Any top-speakers should be dealt with by outer systems.
/*
#define SPEAKER_TOP_CENTER              0x800
#define SPEAKER_TOP_FRONT_LEFT          0x1000
#define SPEAKER_TOP_FRONT_CENTER        0x2000
#define SPEAKER_TOP_FRONT_RIGHT         0x4000
#define SPEAKER_TOP_BACK_LEFT           0x8000
#define SPEAKER_TOP_BACK_CENTER         0x10000
#define SPEAKER_TOP_BACK_RIGHT          0x20000
*/
    };
    Float fltPi;
    Int rgiInCMap[32];
    Int rgiOutCMap[32];
    Int iTmp0;
    U32   nMask;
    Int i,j;

    Float rgfltInPhi[32];
    
    Float fltSource;
    Float fltG1, fltG2;
    Int   iTarg1, iTarg2;
    Float fltTmp, fltBTmp;

    Float rgfltOutPhi[32];
    Float rgfltOutDel[32];
    
    // Duplicated test to satisfy Prefix
    if (cSrcChan < 1 || cDstChan < 1)
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }
    
    for(i=0;i<cDstChan;i++)
    {
        for (j=0;j<cSrcChan;j++) 
        {
            rgrgfltChDnMixMtx[i][j] = 0.0F;
        }
    }

    // Deal with special cases
    // Treat two kinds of 5.1 to be identical
    if (5 == cSrcChan && 5 == cDstChan &&
        ((0x607 == nSrcChannelMask && 0x037 == nDstChannelMask) ||
         (0x037 == nSrcChannelMask && 0x607 == nDstChannelMask)))
    {
        for (i = 0; i < 5; i++)
        {
            // Diagonal
            rgrgfltChDnMixMtx[i][i] = 1.0F;
        }
        return wmaResult;
    }
    
    fltPi = (Float) atan(1.0F) * 4.0F;

    nMask = 1;
    iTmp0 = 0;

    for(i = 0; i < cSrcChan; i++)
    {
        rgiInCMap[i]=i;

        // Find the position of ith source channel
        while (!(nSrcChannelMask & nMask))
        {
            nMask <<= 1;
            iTmp0++;
            if (iTmp0 > 10)
            {
                // internal erorr: we can not deal with top speakers
                TRACEWMA_EXIT(wmaResult, WMA_E_FAIL);
            }
        }
        rgfltInPhi[i] = rgfltSpeakerDirection[iTmp0];
        assert(rgfltInPhi[i] >= 0.0F);

        // WMAFprintf(stdout, "angle (in degrees) for in channel %d is: %f\n",i, rgfltInPhi[i]);
        nMask <<= 1;
        iTmp0++;
    }

    prvDumbBubble(rgfltInPhi, rgiInCMap, cSrcChan);

    nMask = 1;
    iTmp0 = 0;

    for(i = 0; i < cDstChan; i++)
    {
        rgiOutCMap[i] = i;

        // Find the position of ith destination channel
        while (!(nDstChannelMask & nMask))
        {
            nMask <<= 1;
            iTmp0++;
            if (iTmp0 > 10)
            {
                // internal erorr: we can not deal with top speakers
                TRACEWMA_EXIT(wmaResult, WMA_E_FAIL);
            }
        }
        rgfltOutPhi[i] = rgfltSpeakerDirection[iTmp0];
        assert(rgfltOutPhi[i] >= 0.0F);

        //WMAFprintf(stdout, "angle (in degrees) for out channel %d is: %f\n",i, rgfltOutPhi[i]);
        nMask <<= 1;
        iTmp0++;
    }
    prvDumbBubble(rgfltOutPhi, rgiOutCMap, cDstChan);

    for(i = 0; i <  cDstChan-1; i++)
    {
        rgfltOutDel[i] = rgfltOutPhi[i+1] - rgfltOutPhi[i];
    }
    rgfltOutDel[cDstChan-1] = rgfltOutPhi[0] - rgfltOutPhi[cDstChan-1] + 360.0F;

    /*for(i = 0; i < cSrcChan; i++)
    {
    WMAFprintf(stdout, "%d %f %d\n",i, rgfltInPhi[i], rgiInCMap[i]);
    }
    for(i = 0; i < cDstChan; i++)
    {
    WMAFprintf(stdout, "%d %f %f %d \n",i,rgfltOutPhi[i], rgfltOutDel[i], rgiOutCMap[i]);
    }

    for(i = 0; i < cDstChan; i++)
    {
    if (rgfltOutDel[i] < 15.0F)
    {
    WMAFprintf(stdout, "speakers too close at %d and next\n", rgiOutCMap[i]);
    return (-5);
    }
    }
    */

    for (i = 0; i < cSrcChan; i++)
    {
        fltSource = rgfltInPhi[i];
        
        j = 0;
        while ((fltSource > rgfltOutPhi[j]) && (j < cDstChan))
        {
            j++;
        }
        if (j == 0)
        {
            iTarg1 = cDstChan - 1;
            iTarg2=0;
        } 
        else if ( j > cDstChan-1 ) 
        {
            iTarg1 = cDstChan - 1;
            iTarg2 = 0;
        }
        else 
        {
            iTarg1 = j-1;
            iTarg2 = j;
        }
        // WMAPrintf("targets are %d %d\n",iTarg1, iTarg2);

        fltTmp = fltSource - rgfltOutPhi[iTarg1];
        while ( fltTmp < 0.0F ) 
        {
            fltTmp = fltTmp + 360.0F;
        }
        fltTmp = fltTmp/rgfltOutDel[iTarg1];

        fltG1 = (Float) cos(fltTmp * fltPi/2.0F);
        if (fltG1 < 0 )
        {
            fltG1 = 0;
        }
        fltG2 = (Float) sin(fltTmp * fltPi/2.0F);
        if ( fltG2 < 0) 
        {
            fltG2 = 0;
        }
        if (cDstChan == 1 )
        {
            fltG1 = fltG2 = 1.0F;
        }

        rgrgfltChDnMixMtx[rgiOutCMap[iTarg1]][rgiInCMap[i]] = fltG1;
        rgrgfltChDnMixMtx[rgiOutCMap[iTarg2]][rgiInCMap[i]] = fltG2;
    }

    fltBTmp = 0.0F;
    for (i = 0; i < cDstChan; i++)
    {
        fltTmp = 0.0F;
        for(j = 0; j < cSrcChan; j++)
        {
            fltTmp += rgrgfltChDnMixMtx[i][j];
        }
        if (fltBTmp < fltTmp)
        {
            fltBTmp = fltTmp;
        }
    }

    if (fltBTmp <= 0.0F )
    { 
        // WMAFprintf(stderr, "completely impossible error, max gain is %d\n",fltBTmp);
        // internal erorr: we can not deal with top speakers
        TRACEWMA_EXIT(wmaResult, WMA_E_FAIL);
    }

    for(i = 0; i < cDstChan; i++)
    {
        for(j = 0; j < cSrcChan; j++)
        {
            rgrgfltChDnMixMtx[i][j] = 
                ((Float) (   (Int)     (1000.0F* rgrgfltChDnMixMtx[i][j]/fltBTmp + 0.5F) ) )/1000.0F;
        }
    }

    /*
    for(i = 0; i < cDstChan; i++) 
    {
    WMAFprintf(stdout, "Gains for output channel %d are: ",i);
    for(j = 0; j < cSrcChan; j++)
    {
    WMAPrintf("%5.3f ",rgrgfltChDnMixMtx[i][j]);
    }
    WMAPrintf("\n");
    }
    */

exit:
    return wmaResult;
} // prvInitNonLFEChDnMixThroughProjections

WMARESULT prvInitChDnMixThroughProjections (
    Int          cSrcChannel,
    U32            nSrcChannelMask,
    Int          cDstChannel,
    U32            nDstChannelMask,
    ChDnMixType**  rgrgfltChDnMixMtx,
    Float**        rgrgfltChDnMixMtxTmp)
{
    WMARESULT wmaResult = WMA_OK;
    Int i, cSrcChannelTmp, cDstChannelTmp;
    Int iChSrc, iChDst;
    U32   nSrcChannelMaskTmp, nDstChannelMaskTmp;
    U32   nMask = 0x1;
    I16   nSrcSubWooferChan = -1, nDstSubWooferChan = -1;
    
    if (NULL == rgrgfltChDnMixMtx ||
        cSrcChannel > 32 ||
        cSrcChannel < 1 ||
        cDstChannel > 32 ||
        cDstChannel < 1 ||
        0 == nSrcChannelMask ||
        0 == nDstChannelMask)
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }
    
    // Check saninty of channel masks. If we dont understand, do not proceed.
    // Trying to use top speakers?
    if ((nSrcChannelMask & 0xFFFFF800) ||
        (nDstChannelMask & 0xFFFFF800))
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }

    // Incomplete channel mask?
    cSrcChannelTmp = cDstChannelTmp = 0;
    for (i = 0; i < 32; i++)
    {
        cSrcChannelTmp += (nSrcChannelMask & nMask) ? 1 : 0;
        cDstChannelTmp += (nDstChannelMask & nMask) ? 1 : 0;
        nMask <<= 1;
    }
    if ((cSrcChannelTmp != cSrcChannel) ||
        (cDstChannelTmp != cDstChannel))
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);
    }
    
    // Exclude sub-woofer and generate fold-down matrix
    cSrcChannelTmp     = cSrcChannel;
    nSrcChannelMaskTmp = nSrcChannelMask;
    if (nSrcChannelMaskTmp & SPEAKER_LOW_FREQUENCY)
    {
        nSrcChannelMaskTmp &= ~SPEAKER_LOW_FREQUENCY;
        cSrcChannelTmp -= 1;
    }
    
    cDstChannelTmp     = cDstChannel;
    nDstChannelMaskTmp = nDstChannelMask;
    if (nDstChannelMaskTmp & SPEAKER_LOW_FREQUENCY)
    {
        nDstChannelMaskTmp &= ~SPEAKER_LOW_FREQUENCY;
        cDstChannelTmp -= 1;
    }
    
    // Are we left with pure LFE channels?
    if (cSrcChannelTmp < 1 || cDstChannelTmp < 1)
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }

    // Prepare a matrix for the non-lfe channels
    TRACEWMA_EXIT(wmaResult, prvInitNonLFEChDnMixThroughProjections (cSrcChannelTmp,
        nSrcChannelMaskTmp,
        cDstChannelTmp,
        nDstChannelMaskTmp,
        rgrgfltChDnMixMtxTmp));

    // Clean-up
    for (iChDst = 0; iChDst < cDstChannel; iChDst++)
    {
        for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
        {
            rgrgfltChDnMixMtx[iChDst][iChSrc] = (ChDnMixType) 0;
        }
    }
    
    // Find the channel number of LFE in src, dst, if present.
    prvGetChannelNumAtSpeakerPosition(nSrcChannelMask, 
        SPEAKER_LOW_FREQUENCY, 
        &nSrcSubWooferChan);
    prvGetChannelNumAtSpeakerPosition(nDstChannelMask, 
        SPEAKER_LOW_FREQUENCY, 
        &nDstSubWooferChan);
    
    if ((nSrcSubWooferChan != -1) &&
        (nDstSubWooferChan != -1))
    {
        // Both source and destination have LFE: Pass thru
        rgrgfltChDnMixMtx[nDstSubWooferChan][nSrcSubWooferChan] = CHDN_FROM_FLOAT(1.0F);
        for (iChDst = 0; iChDst < nDstSubWooferChan; iChDst++)
        {
            for (iChSrc = 0; iChSrc < nSrcSubWooferChan; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst][iChSrc]);
            }
            for (iChSrc = nSrcSubWooferChan+1; iChSrc < cSrcChannel; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst][iChSrc-1]);
            }
        }
        for (iChDst = nDstSubWooferChan+1; iChDst < cDstChannel; iChDst++)
        {
            for (iChSrc = 0; iChSrc < nSrcSubWooferChan; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst-1][iChSrc]);
            }
            for (iChSrc = nSrcSubWooferChan+1; iChSrc < cSrcChannel; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst-1][iChSrc-1]);
            }
        }
    }
    else if ((nSrcSubWooferChan == -1) &&
        (nDstSubWooferChan != -1))
    {
        // Only destination has an LFE: pump silence out of it
        for (iChDst = 0; iChDst < nDstSubWooferChan; iChDst++)
        {
            for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst][iChSrc]);
            }
        }
        // leave nDstSubWooferChan with zeros
        for (iChDst = nDstSubWooferChan+1; iChDst < cDstChannel; iChDst++)
        {
            for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst-1][iChSrc]);
            }
        }
    }
    else if ((nSrcSubWooferChan != -1) &&
        (nDstSubWooferChan == -1))
    {
        // Only source has an LFE: spread 20% of it over all output channels
        for (iChDst = 0; iChDst < cDstChannel; iChDst++)
        {
            for (iChSrc = 0; iChSrc < nSrcSubWooferChan; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst][iChSrc] * cDstChannel/(cDstChannel + 0.2F));
            }
            iChSrc = nSrcSubWooferChan;
            rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(0.2F/(cDstChannel + 0.2F));
            for (iChSrc = nSrcSubWooferChan+1; iChSrc < cSrcChannel; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst][iChSrc-1] * cDstChannel/(cDstChannel + 0.2F));
            }
        }
    }
    else
    {
        // Neither source nor destination have LFEs: Simple copy
        for (iChDst = 0; iChDst < cDstChannel; iChDst++)
        {
            for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
            {
                rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(rgrgfltChDnMixMtxTmp[iChDst][iChSrc]);
            }
        }
    }

    /*
    {
        Int j;
        for(i = 0; i < cDstChannel; i++) 
        {
            WMAFprintf(stdout, "Gains for output channel %d are: ",i);
            for(j = 0; j < cSrcChannel; j++)
            {
                WMAPrintf("%5.3f ",rgrgfltChDnMixMtx[i][j]);
            }
            WMAPrintf("\n");
        }
    }
    */

exit:
    return wmaResult;
} // prvInitChDnMixThroughProjections

WMARESULT prvInitChDnMix(CAudioObjectDecoder* paudec, I32* rgiMixDownMatrix,
                         Int cSrcChannel, U32 nSrcChannelMask,
                         Int cDstChannel, U32 nDstChannelMask)
{
    WMARESULT wmaResult = WMA_OK;
    Int iCh, k;
    CAudioObject *pau = NULL;

    if (NULL == paudec || NULL == paudec->pau)
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
    
    pau = paudec->pau;

    // Do not leak memory if re-initializing.
    if (paudec->m_rgrgfltChDnMixMtx)
    {
        for (k = 0; k < paudec->m_cDstChannelInChDnMixMtx; k++)
        {
            DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtx[k]);
        }
        DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtx);
    }

    if (paudec &&
        paudec->m_rgrgfltChDnMixMtxTmp)
    {
        for (k = 0; k < paudec->m_cDstChannelInChDnMixMtx; k++)
        {
            DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtxTmp[k]);
        }
        DELETE_ARRAY(paudec->m_rgrgfltChDnMixMtxTmp);
    }
    
    pau = paudec->pau;
    
    // Allocate memory for m_rgrgfltChDnMixMtx.
    paudec->m_rgrgfltChDnMixMtx = (ChDnMixType**)  auMalloc (sizeof(ChDnMixType*) * cDstChannel);
    if (paudec->m_rgrgfltChDnMixMtx == NULL) 
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
    }

    memset(paudec->m_rgrgfltChDnMixMtx, 0, sizeof(ChDnMixType*) * cDstChannel);
    
    paudec->m_cDstChannelInChDnMixMtx = cDstChannel;
    for (iCh = 0; iCh < cDstChannel; iCh++)
    {
        paudec->m_rgrgfltChDnMixMtx[iCh] = (ChDnMixType*)  auMalloc (sizeof(ChDnMixType) * cSrcChannel);
        if (paudec->m_rgrgfltChDnMixMtx[iCh] == NULL) 
        {
            TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
        }
        memset(paudec->m_rgrgfltChDnMixMtx[iCh], 0, sizeof(ChDnMixType) * cSrcChannel);
    }
 
    // Allocate memory for m_rgrgfltChDnMixMtxTmp.
    paudec->m_rgrgfltChDnMixMtxTmp = (Float**)  auMalloc (sizeof(Float*) * cDstChannel);
    if (paudec->m_rgrgfltChDnMixMtxTmp == NULL) 
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
    }

    memset(paudec->m_rgrgfltChDnMixMtxTmp, 0, sizeof(Float*) * cDstChannel);
    
    for (iCh = 0; iCh < cDstChannel; iCh++)
    {
        paudec->m_rgrgfltChDnMixMtxTmp[iCh] = (Float*)  auMalloc (sizeof(Float) * cSrcChannel);
        if (paudec->m_rgrgfltChDnMixMtxTmp[iCh] == NULL) 
        {
            TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
        }
        memset(paudec->m_rgrgfltChDnMixMtxTmp[iCh], 0, sizeof(Float) * cSrcChannel);
    }
    
    if (paudec->m_fLtRtDownmixNonnormal == WMAB_TRUE)
    {
        // Using non-normal LtRt downmixing 
        // Get the matrix from paudec->m_pLtRtDownmix
        // Note: if paudec->m_fLtRtDownmixNonnormal is TRUE, then ltrtDownmixInitBuf must be called before calling this function.

        Int iChSrc, iChDst;
        Float *pfChanMtx = paudec->m_pLtRtDownmix->m_fChanMtx;

        assert (paudec->m_pLtRtDownmix->m_cInChannels == cSrcChannel );
        
        for (iChDst = 0; iChDst < cDstChannel; iChDst++)
            for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
                paudec->m_rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(*pfChanMtx++);
    }
    else
    {
        if (rgiMixDownMatrix != NULL) 
        {
            // Use the matrix that got sent from outside world:
            // They are fixed point dB scale
            Int iChSrc, iChDst;
            I32 iMixDownCoeff;
            for (iChDst = 0; iChDst < cDstChannel; iChDst++) 
            {
                for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++) 
                {
                    iMixDownCoeff = rgiMixDownMatrix[iChSrc*cDstChannel + iChDst];
                    if (iMixDownCoeff == I32_MIN)
                    {
                        paudec->m_rgrgfltChDnMixMtx[iChDst][iChSrc] = CHDN_FROM_FLOAT(0.0F);
                    }
                    else
                    {
                        paudec->m_rgrgfltChDnMixMtx[iChDst][iChSrc] = 
                          CHDN_FROM_FLOAT(
                            (Float)pow(10.0, ((double)iMixDownCoeff)/(65536.0 * 20.0)));
                    }
                }
            }
	        paudec->m_bAuthorControlledChDnMixMtx = WMAB_TRUE;
        } 
        else if (paudec->m_fChannelFoldDown) 
        {
	        paudec->m_bAuthorControlledChDnMixMtx = WMAB_FALSE;
            // Use JJ's function to initialize Folddown matrix
#if defined (USE_JJ_FOLDDOWN)
            TRACEWMA_EXIT(wmaResult, prvInitChDnMixThroughProjections (
                cSrcChannel,
                nSrcChannelMask,
                cDstChannel,
                nDstChannelMask,
                paudec->m_rgrgfltChDnMixMtx,
                paudec->m_rgrgfltChDnMixMtxTmp));

#else
            // !USE_JJ_FOLDDOWN
            // Use internal default matrices.
            if (cSrcChannel < 3 || 
                cSrcChannel > 8) 
            {
                TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
            }

            if (cDstChannel != 2 && cDstChannel != 1) 
            {
                TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
            }

            if (cSrcChannel == 3 &&
                cDstChannel == 2)
            {
                // Home Theater 3.0 to stereo
                Int iChannel[] = {0, 2,
                                  1, 2};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613, 
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0))}; // center
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 2, 2,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 3 &&
                     cDstChannel == 1)
            {
                // Home Theater 3.0 to mono
                Int iChannel[] = {0, 1, 2};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613, 
                                         3165613, 
                                         4476852};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (2.0/sqrt(2.0))}; // center
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 3, 1,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 4 &&
                     cDstChannel == 2 &&
                     nSrcChannelMask == 0x33)
            {
                // XP 4.0 to stereo
                Int iChannel[] = {0, 2,
                                  1, 3};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613,
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0))}; // back or side left
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 2, 2,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 4 &&
                     cDstChannel == 2 &&
                     nSrcChannelMask == 0x107)
            {
                // HT 4.0 to stereo
                Int iChannel[] = {0, 2, 3,
                                  1, 2, 3};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613,
                                         2238426,
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0)), // center
                                         (Float) (1.0/sqrt(2.0))}; // back or side left
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 3, 2,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 4 &&
                cDstChannel == 1 &&
                nSrcChannelMask == 0x33)
            {
                // XP 4.0 to mono
                Int iChannel[] = {0, 1, 2, 3};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613, 3165613,
                                         2238426, 2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (1.0/sqrt(2.0)),// back or side left
                                         (Float) (1.0/sqrt(2.0))};// back or side right
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 42, 1,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 4 &&
                     cDstChannel == 1 &&
                     nSrcChannelMask == 0x107)
            {
                // HT 4.0 to mono
                Int iChannel[] = {0, 1, 2, 3};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613,
                                         3165613,
                                         4476852,
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (2.0/sqrt(2.0)), // center
                                         (Float) (1.0/sqrt(2.0))}; // back or side left
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 4, 1,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 5 &&
                     cDstChannel == 2)
            {
                // Either XP or Home Theater 5.0 to stereo
                // Treat side left & back left the same way.
                Int iChannel[] = {0, 2, 3,
                                  1, 2, 4};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613,
                                         2238426,
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0)), // center
                                         (Float) (1.0/sqrt(2.0))}; // back or side left
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 3, 2,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 5 &&
                     cDstChannel == 1)
            {
                // Either XP or Home Theater 5.0 to mono
                // Treat side left & back left the same way.
                Int iChannel[] = {0, 1, 2, 3, 4};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613,
                                         3165613,
                                         4476852,
                                         2238426,
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (2.0/sqrt(2.0)), // center
                                         (Float) (1.0/sqrt(2.0)), // back or side left
                                         (Float) (1.0/sqrt(2.0))};// back or side right
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 5, 1,
                              iChannel, fltCoef);
            }
            else if (cSrcChannel == 6 && 
                cDstChannel == 2 &&
                pau->m_nSubWooferChannel == 3)
            {
                // Either XP or Home Theater 5.1 to stereo
                Int iChannel[] = {0, 2, 3, 4,
                                  1, 2, 3, 5};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {3165613,
                                         2238426,
                                         746142,
                                         2238426};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0)), // center
                                         (Float) (1.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0))}; // back left
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 4, 2,
                              iChannel, fltCoef);
            } 
            else if (cSrcChannel == 6 && 
                cDstChannel == 1 &&
                pau->m_nSubWooferChannel == 3) 
            {
                // Either XP or Home Theater 5.1 to mono
                Int iChannel[] = {0, 1, 2, 3, 4, 5};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {1582806,
                                         1582806,
                                         2238426,
                                         746142,
                                         1119213,
                                         1119213};
#else
                ChDnMixType fltCoef[] = {1.0F, // left,
                                         1.0F, // right,
                                         (Float) (2.0/sqrt(2.0)), // center
                                         (Float) (2.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0)), // back left
                                         (Float) (1.0/sqrt(2.0))}; // back right
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 6, 1,
                              iChannel, fltCoef);
            } 
            else if (cSrcChannel == 7 && 
                cDstChannel == 2 &&
                nSrcChannelMask == 0x13F) 
            {
                // XP 6.1 to stereo
                Int iChannel[] = {0, 2, 3, 4, 6,
                                  1, 2, 3, 5, 6};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {2498823,
                                         1766935,
                                         588978,
                                         1766935,
                                         1766935};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0)), // center
                                         (Float) (1.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0)), // back left
                                         (Float) (1.0/sqrt(2.0))}; // back center
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 5, 2,
                              iChannel, fltCoef );
            } 
            else if (cSrcChannel == 7 && 
                cDstChannel == 2 &&
                nSrcChannelMask == 0x70F) 
            {
                // Home Theater 6.1 to stereo
                Int iChannel[] = {0, 2, 3, 4, 5,
                                  1, 2, 3, 4, 6};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {2498823,
                                         1766935,
                                         588978,
                                         1766935,
                                         1766935};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0)), // center
                                         (Float) (1.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0)), // back center
                                         (Float) (1.0/sqrt(2.0))}; // side left
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 5, 2,
                              iChannel, fltCoef );
            } 
            else if (cSrcChannel == 7 && 
                cDstChannel == 1 &&
                nSrcChannelMask == 0x13F) 
            {
                // XP 6.1 to mono
                Int iChannel[] = {0, 1, 2, 3, 4, 5, 6};

#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {2498823, 
                                         2498823,
                                         3533870,
                                         1177956,
                                         1766935,
                                         1766935,
                                         3533870};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (2.0/sqrt(2.0)), // center
                                         (Float) (2.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0)), // back left
                                         (Float) (1.0/sqrt(2.0)), // back right
                                         (Float) (2.0/sqrt(2.0))}; // back center
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 7, 1,
                              iChannel, fltCoef );
            } 
            else if (cSrcChannel == 7 && 
                cDstChannel == 1 &&
                nSrcChannelMask == 0x70F) 
            {
                // Home Theater 6.1 to mono
                Int iChannel[] = {0, 1, 2, 3, 4, 5, 6};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {2498823,
                                         2498823,
                                         3533870,
                                         1177956,
                                         3533870,
                                         1766935,
                                         1766935};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (2.0/sqrt(2.0)), // center
                                         (Float) (2.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (2.0/sqrt(2.0)), // back center
                                         (Float) (1.0/sqrt(2.0)), // side left
                                         (Float) (1.0/sqrt(2.0))}; // side right
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 7, 1,
                              iChannel, fltCoef );
            } 
            else if (cSrcChannel == 8 && 
                cDstChannel == 2 &&
                pau->m_nSubWooferChannel == 3) 
            {
                // Either XP or Home Theater 7.1 to stereo
                // Treat left of center & side left same way :(
                Int iChannel[] = {0, 2, 3, 4, 6,
                                  1, 2, 3, 5, 7};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {2498823,
                                         1766935,
                                         588978,
                                         1766935,
                                         1766935};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         (Float) (1.0/sqrt(2.0)), // center
                                         (Float) (1.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0)), // back left
                                         (Float) (1.0/sqrt(2.0))}; // left of center
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 5, 2,
                              iChannel, fltCoef );
            } 
            else if (cSrcChannel == 8 && 
                cDstChannel == 1 &&
                pau->m_nSubWooferChannel == 3)
            {
                // Either XP or Home Theater 7.1 to mono
                // Treat left of center & side left same way :(
                Int iChannel[] = {0, 1, 2, 3, 4, 5, 6, 7};
#ifdef BUILD_INTEGER
                ChDnMixType fltCoef[] = {1249412,
                                         1249412,
                                         1766935,
                                         588978,
                                         883467,
                                         883467,
                                         883467,
                                         883467};
#else
                ChDnMixType fltCoef[] = {1.0F, // left
                                         1.0F, // right
                                         (Float) (2.0/sqrt(2.0)), // center
                                         (Float) (2.0/(3.0*sqrt(2.0))), // subwoofer
                                         (Float) (1.0/sqrt(2.0)), // back left
                                         (Float) (1.0/sqrt(2.0)), // back right
                                         (Float) (1.0/sqrt(2.0)), // left of center
                                         (Float) (1.0/sqrt(2.0))}; // right of center
#endif
                prvSetChDnMix(paudec->m_rgrgfltChDnMixMtx, 8, 1,
                              iChannel, fltCoef );
            }
            else
            {
                TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
            }
#endif // USE_JJ_FOLDDOWN
        } 
        else 
        {
            // Just for safety
            if (cDstChannel != cSrcChannel)
            {
                // Actually an internal error
                TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
            }
            // The matrix is already zeroed elsewhere: just make it diagonal
            for (iCh = 0; iCh < cDstChannel; iCh++) 
                paudec->m_rgrgfltChDnMixMtx[iCh][iCh] = CHDN_FROM_FLOAT(1.0F);
        }
    }


#if 0
    DownmixTest(paudec);
#endif

exit:

#if 0
    {
        Int iChDst, iChSrc;
        for (iChDst = 0; iChDst < cDstChannel; iChDst++)
        {
            for (iChSrc = 0; iChSrc < cSrcChannel; iChSrc++)
            {
                WMAFprintf(stdout, "%f ", paudec->m_rgrgfltChDnMixMtx[iChDst][iChSrc]);
            }
            WMAFprintf(stdout, "\n");
        }
        FFLUSH(stdout);
    }
#endif
    return wmaResult;
} //prvInitChDnMix

#endif // BUILD_WMAPRO

#if defined(_SH4_)
#pragma warning(pop)
#endif

#if defined (BUILD_WMAPRO) && !defined(CHANFLDDN_PREPCM)
// We assume piSrc and piDst point to PCMSAMPLE, channel-interleaved buffers
// We also assume piSrc & piDst are identical.
#if !( defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_CHANNEL_DOWN_MIX))
#if !WMA_OPT_CHANNEL_DOWNMIX_ARM
WMARESULT prvChannelDownMix (CAudioObjectDecoder *paudec, U8 *piSourceBuffer, Int nBlocks,
                             U8 *piDestBuffer)
{
    return prvChannelDownMixInt(paudec, piSourceBuffer, nBlocks, piDestBuffer);
} // prvChannelDownMix
#endif // WMA_OPT_CHANNEL_DOWNMIX_ARM
#endif // WMA_TARGET_MIPS && PLATFORM_SPECIFIC_CHANNEL_DOWN_MIX 
#endif // BUILD_WMAPRO

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
#if !WMA_OPT_REQUANTO16_ARM
#if !( defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_REQUANTO16) )
WMARESULT prvRequantizeTo16(CAudioObjectDecoder *paudec, U8 *piSrc, Int nBlocks)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;
    PCMSAMPLE pcmsTemp;
    Int iBlock, iChSrc;
    PFNSETSAMPLE pfnSetSample;
    Int nShift;
    Int cDstChannel = paudec->m_cDstChannel;
    U8 *piDst = piSrc;
 
    if (!paudec->m_fReQuantizeTo16)
        goto exit;

    // In the future if this condition is false, return WMA_E_FAIL or something
    assert(paudec->m_nDstBytePerSample == 2);
    pfnSetSample = prvSetSample16INLINE;
    //nShift = (pau->m_nBytePerSample - paudec->m_nDstBytePerSample) * BITS_PER_BYTE;
    nShift = pau->m_nValidBitsPerSample - 16;
    assert(nShift > 0);

    for (iBlock = 0; iBlock < nBlocks; iBlock++) 
    {
        // Initialize
        for (iChSrc = 0; iChSrc < cDstChannel; iChSrc++) 
        {
            pcmsTemp = PPPOSTGETSAMPLE(piSrc, iChSrc);
            pcmsTemp >>= nShift;
            PPPOSTSETSAMPLE16(pcmsTemp, piDst, iChSrc);
        }
        //Stride ahead to the next block
        PPPOSTADVPTR(piSrc, cDstChannel);
        PPPOSTADVPTR16(piDst, cDstChannel);
    }

exit:
    return wmaResult;
}
#endif
#endif //WMA_OPT_REQUANTO16_ARM
#endif

#if defined (BUILD_WMAPRO)
WMARESULT prvPrepareResampledMaskV3_Channel(CAudioObject* pau, PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;

    if (ppcinfo->m_fAnchorMaskAvailable) {
        Int iMax;
        I16 iBand;

        // Resample existing mask for temporal prediction
        auResampleMaskV3 (pau, 
            ppcinfo->m_rgiMaskQ, ppcinfo->m_cSubFrameSampleHalfWithUpdate, ppcinfo->m_cValidBarkBandLatestUpdate,
            ppcinfo->m_rgiMaskQResampled, ppcinfo->m_cSubFrameSampleHalf, pau->m_cValidBarkBand);
        // Find max mask on the resampled mask: needed if mask is not updated.
        iMax = ppcinfo->m_rgiMaskQResampled[0];

        for (iBand = 1; iBand < pau->m_cValidBarkBand; iBand++)
        {
            if (ppcinfo->m_rgiMaskQResampled[iBand] > iMax)
                iMax = ppcinfo->m_rgiMaskQResampled[iBand];
        }
        ppcinfo->m_iMaxMaskQ = iMax;
        // This initialization is useful in case the subframe is completely skipped
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0] = WMAB_FALSE;
    }
    return wmaResult;
} // prvPrepareResampledMaskV3_Channel
#endif // BUILD_WMAPRO

#if defined (_DEBUG)
#define DEBUG_PRINT_POSTPROCXFORM(fPrint) \
{ \
    if (fPrint) {\
        Int iCh0, iCh1;\
        for (iCh0 = 0; iCh0 < pau->m_cChannel; iCh0++) {\
            for (iCh1 = 0; iCh1 < pau->m_cChannel; iCh1++) {\
                WMAFprintf(stdout, "%f ", paudec->m_rgfltPostProcXformBlend[iCh0 * pau->m_cChannel + iCh1]);\
            }\
            WMAFprintf(stdout,"\n");\
        }\
    }\
}
#else
#define DEBUG_PRINT_POSTPROCXFORM(fPrint) 
#endif // _DEBUG

#if 0
STATIC_INLINE Void *prvSetSampleCoefType(const CoefType cValue, CoefType *pCurrentPos,
                                         const Int iOffset)
{
    *(pCurrentPos + iOffset) = cValue;
}
#endif

#if defined (BUILD_WMAPRO)
// Post processing multi-channel transform in time domain.
// Must be done in place.
WMARESULT prvPostProcChannelXformV3(CAudioObjectDecoder *paudec,
                                    U8 *piDataBuffer/*In, out*/, 
                                    const U16 cSampleReady)
{
    CAudioObject* pau     = paudec->pau;
    Int cChannel          = pau->m_cChannel;
    WMARESULT wmaResult   = WMA_OK;
    U8  *piSrc            = piDataBuffer;
    U8  *piDst            = piDataBuffer;
    Int iCh, iSample;

#ifdef POSTPROCESS_PREPCM
    for (iCh=0; iCh < cChannel; iCh++)
    {
        paudec->m_rgpctTemp[iCh] = (CoefType*)pau->m_rgpcinfo[iCh].m_rgiPCMBuffer;
    }
#endif

    // this function should only be used when performing post-processing multi-channel transform,
    if (!paudec->m_fPostProcXform) 
        return wmaResult;

    for (iSample = 0; iSample < cSampleReady; iSample++)
    {
        if (paudec->m_fPostProcXformPrev)
        {
#ifndef BUILD_INTEGER
            // Generate blended channel transform
            Float fltAlpha = 0.0F;
            Float fltBeta  = (Float) iSample/ (Float)cSampleReady;

            //// For simplifying future integerized decoders, reduce precision to 3 fractional bits
            //fltBeta = ((Int)(fltBeta * 8.0F))/8.0F;
            fltAlpha  = (1.0F - fltBeta); // complement
#endif
            for (iCh = 0; iCh < cChannel * cChannel; iCh++)
            {
#ifdef BUILD_INTEGER // iSample <= 8192 = 2^13, so to prevent overflow, 2*2^13*2^x <= 2^31, or x <= 17
#define SHIFT_BITS (CHPP_FRAC_BITS - 17)
                paudec->m_rgfltPostProcXformBlend[iCh] =
                  (((cSampleReady-iSample) * (paudec->m_rgfltPostProcXformPrev[iCh] >> SHIFT_BITS) +
                    iSample * (paudec->m_rgfltPostProcXform[iCh] >> SHIFT_BITS))/cSampleReady) << SHIFT_BITS;
#undef SHIFT_BITS
#else
                paudec->m_rgfltPostProcXformBlend[iCh] = 
                fltAlpha * paudec->m_rgfltPostProcXformPrev[iCh] + 
                fltBeta  * paudec->m_rgfltPostProcXform[iCh];
                // The resulting transform currently needs more than 3 fractional bits.
#endif
            }
        }
        else
        {
            // Use currently decoded channel transform
            memcpy(paudec->m_rgfltPostProcXformBlend, 
                paudec->m_rgfltPostProcXform,
                sizeof(Float) * cChannel * cChannel);
        }

        // add dynamic precision before post processing
        for (iCh = 0; iCh < cChannel; iCh++)
        {
#ifdef POSTPROCESS_PREPCM
            paudec->m_pctTemp[iCh] = CHPP2_FROM_INT(*(paudec->m_rgpctTemp[iCh]));
#else
            paudec->m_rgpcmsTemp[iCh] = CHPP2_FROM_INT(PPPOSTGETSAMPLE(piSrc, iCh));
#endif
        }
#ifndef POSTPROCESS_PREPCM
        PPPOSTADVPTR(piSrc, cChannel);
#endif

        DEBUG_PRINT_POSTPROCXFORM(WMAB_FALSE);
        // Do the transform, set the output
        for (iCh = 0; iCh < cChannel; iCh++)
        {
#ifndef POSTPROCESS_PREPCM
            Int     iValue;
#endif
            CoefType fltValue = (CoefType)0;
            Int i;
            // First do the transform, get output value.
            ChPPXFormType* rgfltXform = paudec->m_rgfltPostProcXformBlend + iCh * cChannel;
            for (i = 0; i < cChannel; i++)
            {
#ifdef POSTPROCESS_PREPCM
                fltValue += MULT_CHPP(paudec->m_pctTemp[i], rgfltXform[i]);
#else
                fltValue += MULT_CHPP(paudec->m_rgpcmsTemp[i], rgfltXform[i]);
#endif
            }
            // Set the value
#ifdef POSTPROCESS_PREPCM
            *(paudec->m_rgpctTemp[iCh]) = INT_FROM_CHPP2(fltValue);
            paudec->m_rgpctTemp[iCh]++;
#else
#if defined (BUILD_INTEGER)
            iValue = (PCMSAMPLE) INT_FROM_CHPP2(fltValue);
#else
            iValue = (PCMSAMPLE) ROUNDF(fltValue);
#endif
            PPPOSTCLIPRANGE(iValue);
            PPPOSTSETSAMPLE(iValue, piDst, iCh);
#endif // POSTPROCESS_PREPCM
        }
#ifndef POSTPROCESS_PREPCM
        PPPOSTADVPTR(piDst, cChannel);
#endif
    }
    return wmaResult;
} // prvPostProcChannelXformV3
#endif // BUILD_WMAPRO

#if defined (BUILD_WMAPRO)
WMARESULT prvInitDecodeDRC(CAudioObjectDecoder *paudec,
                           Int nDRCSetting)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    DRCData drcData;
    DRCOptions drcOpts;

#ifdef BOOST_CHANFLDDN_POWER
    if ((nDRCSetting == WMA_DRC_HIGH && paudec->m_fChannelFoldDown == WMAB_FALSE) || pau->m_iVersion < 3) goto exit;
#else
    if (nDRCSetting == WMA_DRC_HIGH || pau->m_iVersion < 3) goto exit;
#endif
    if (paudec->m_fDRC) goto exit; // already inited

    // DRC data
    drcDataZero(&drcData);
    // pau, paudec
    drcData.pau = pau;
    // rms, peak data
    drcData.dataFormatRms = PostProcDrcDataInNormU16;
    drcData.rms.normVal = paudec->m_wmapi.iRmsAmplitudeRef;
    drcData.dataFormatPeak = PostProcDrcDataInNormU16;
    drcData.peak.normVal = paudec->m_wmapi.iPeakAmplitudeRef;
    // other data (sample info.)
    drcData.fContainsSampleInfo = WMAB_TRUE;
    drcData.samplingRate = min(pau->m_iXformSamplingRate,
                               paudec->m_iDstSamplingRate);
#if defined(NEW_DRC_DECODE) && !defined(CHANFLDDN_PREPCM)
    drcData.nChannels = pau->m_cChannel;
#else
    drcData.nChannels = paudec->m_cDstChannel;
#endif
    drcData.nBytePerSample = pau->m_nBytePerSample;
    drcData.nValidBitsPerSample = pau->m_nValidBitsPerSample;

    // DRC options
    drcSetDefaultOptions(&drcOpts);

    // set scaling, etc...
    //drcOpts.m_fDRCDecode = pau->m_fGenerateDrcParams;
    drcOpts.m_fDRCDecode = WMAB_TRUE;
    drcOpts.m_fNormalizeRms = WMAB_TRUE;
    //drcOpts.m_fUseDRCOnNormalize = WMAB_FALSE;
    // desired rms in norm val set to same as original
    drcOpts.m_dataFormatRms = PostProcDrcDataInNormU16;
    drcOpts.m_desiredRms.normVal = paudec->m_wmapi.iRmsAmplitudeTarget;
    drcOpts.m_dataFormatPeak = PostProcDrcDataInNormU16;
    drcOpts.m_desiredPeak.normVal = paudec->m_wmapi.iPeakAmplitudeTarget;

    drcOpts.m_fUseWmaDefaults = WMAB_TRUE; // this will adjust values as needed

    if (pau->m_pDrc)
    {
        drcFree(pau->m_pDrc);
        auFree(pau->m_pDrc);
        pau->m_pDrc = NULL;
    }
    pau->m_pDrc = (DRC*) auMalloc (sizeof(DRC));
    if (NULL == pau->m_pDrc)
    {
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY);
    }
    drcZero(pau->m_pDrc);
    TRACEWMA_EXIT(wmaResult, drcInit(pau->m_pDrc, NULL, &drcData, &drcOpts));

    paudec->m_fDRC = WMAB_TRUE; // succesfully initialized

exit:
    return wmaResult;
}
#endif // BUILD_WMAPRO

#ifdef WMA_COMPRESSION_TOOL
// Professional Encoder Related.
WMARESULT prvRecordFrameStartInBitStrm (CAudioObjectDecoder * paudec, CWMAInputBitStream * pibstrm)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject * pau = paudec->pau;
    U8 nHdrBits = WMA_get_nHdrBits(pibstrm->m_dwOwner);
    assert(pibstrm->m_dwOwner == paudec); 

    //due to onhold/resume we may call this function repeatly.
    if (pibstrm->m_dumpFrmBitSts != NEED_FRAME_STA)
        return wmaResult;
    pibstrm->m_iFrameStart = pibstrm->m_cTtlBits - ((pibstrm->m_cbBuflen << 3) + pibstrm->m_dwBitsLeft);
    if (pibstrm->m_fNewPacketCurr == WMAB_TRUE)
    {
        // If iFrameStart fall into pkthdr or before the pkthdr, dwBitsLeft includes bits before and/or 
        // after pkthdr (ibstrmAttach did that). Corespondingly we need to subtract iFrameStart by cHdrBits.
        if (pibstrm->m_iFrameStart < (pibstrm->m_cTtlBits - (U32)(pibstrm->m_cbInputBuffer << 3) + nHdrBits))
        {
            pibstrm->m_iFrameStart -= nHdrBits;
        }
    }

    assert(pibstrm->m_iFrameStart < (pibstrm->m_cTtlBits - (U32)(pibstrm->m_cbBuflen << 3) + nHdrBits));
    pibstrm->m_f1stNewFrmInPkt = (paudec->m_fhdrdecsts == FHDR_PREV);
    pibstrm->m_dumpFrmBitSts = NEED_FRAME_END;
    // reset the frame bits buffer.
    pau->m_cFrmUsedBitsFromParser = 0;

#ifndef AVS_TEST_MODES_PRINTFRMBITS  // rgbFrameBits is not malloced in AVS_TEST_MODES.
    memset(pau->m_rgbFrameBits, 0, pau->m_cFrameBitsBufLen / 8 + 1);
#endif //AVS_TEST_MODES_PRINTFRMBITS

#ifdef AVS_TEST_MODES_PRINTFRMBITS    
    printf("Frame %10d Start %10I64d ",
        prvGetPCMFrameNumber(pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion),pibstrm->m_iFrameStart);
#endif //AVS_TEST_MODES_PRINTFRMBITS

    return wmaResult;
}

WMARESULT prvRecordFrameHdrBits (CAudioObjectDecoder * paudec, I32 cFrmHdrBits)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject * pau = paudec->pau;
    pau->m_cFrmHdrBitsFromParser = cFrmHdrBits;
    pau->m_cFrmHdrBitsFromParserOrg = cFrmHdrBits;
    return wmaResult;
}

WMARESULT prvRecordFrameEndInBitStrm (CAudioObjectDecoder * paudec, CWMAInputBitStream * pibstrm)
{
    WMARESULT wmaResult = WMA_OK;
    U8 nHdrBits = WMA_get_nHdrBits(pibstrm->m_dwOwner);
    assert(pibstrm->m_dwOwner == paudec);

    pibstrm->m_iFrameEnd = pibstrm->m_cTtlBits - ((pibstrm->m_cbBuflen << 3) + pibstrm->m_dwBitsLeft);
    if (pibstrm->m_fNewPacketCurr == WMAB_TRUE)
    {
        // If iFrameEnd fall into pkthdr or before the pkthdr, dwBitsLeft includes bits before and/or 
        // after pkthdr (ibstrmAttach did that). Corespondingly we need to subtract iFrameStart by cHdrBits.
        if (pibstrm->m_iFrameEnd < (pibstrm->m_cTtlBits - (U32)(pibstrm->m_cbBuflenBegin << 3) + nHdrBits))
        {
            pibstrm->m_iFrameEnd -= nHdrBits;
        }
    }

    pibstrm->m_dumpFrmBitSts = NEED_FRAME_STA;
#ifdef AVS_TEST_MODES_PRINTFRMBITS
    printf("End %10I64d\n",pibstrm->m_iFrameEnd);
#endif //AVS_TEST_MODES_PRINTFRMBITS
    return wmaResult;
}

// v2 has a frmae hdr0 for the purpose of seeking. It will be removed before we dump frame info and bits
// because it is meaningless in repacketization. v3 may have framesize in hdr. Since its width depends
// on the bitrate we use to encode and is not fixed, we need to remove it also.
WMARESULT prvWriteMetaFileGetCommonFrmHdr (CAudioObjectDecoder * paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject * pau = paudec->pau;
    I32 cSkipBits = 0;
    // Only v2 and AllowSubFrame have hdr0
    if (pau->m_fAllowSubFrame && pau->m_iVersion <= 2)
    {
        // Only first new frame in packet has hdr0
        if (paudec->m_ibstrm.m_f1stNewFrmInPkt == WMAB_TRUE)
        {
            //peek enough bits for this "case" if not enough will be on hold
            Int cBitsNeed = LOG2 ((U32) LOG2 ((U32)pau->m_iMaxSubFrameDiv)) + 1;
            cSkipBits = 2 * cBitsNeed;
            pau->m_cFrmHdrBitsFromParser -= cBitsNeed * 2;
            assert(pau->m_cFrmHdrBitsFromParser == 0); // v2 does not have hdr1.
        }
    }

    // remove framesize in hdr
    if (pau->m_fWriteFrameSize == WMAB_TRUE && pau->m_iVersion >= 3)
    {
        cSkipBits += pau->m_cBitsBitsPacketLength;
        pau->m_cFrmHdrBitsFromParser -= pau->m_cBitsBitsPacketLength;
    }

    pau->m_cFrmUsedBitsFromParser = prvBitsMove (pau->m_rgbFrameBits, pau->m_cFrameBitsBufLen / 8 + 1, 
                                        cSkipBits, pau->m_cFrmUsedBitsFromParser, 
                                        pau->m_rgbFrameBits, pau->m_cFrameBitsBufLen / 8 + 1, 0);

    return wmaResult;
}


// 
WMARESULT prvWriteMetaFileFrameBitsInfo (CAudioObjectDecoder * paudec, LPCSTR pMetaFileName)
{
    CAudioObject * pau = paudec->pau;
    WMARESULT wmaResult = WMA_OK;

#ifndef WMA_COMPTOOL_NODUMPING
    FILE * fp = NULL;
    I32 iPCMFrameNumber;
    char fileName[_MAX_PATH];

    RAWBS_FRMINFO stFrmInfo;

    if (paudec->m_fWriteMetaFile != WMAB_TRUE)
        return wmaResult;

    iPCMFrameNumber = prvGetPCMFrameNumber(pau->m_iFrameNumber, WMAB_FALSE, pau->m_iVersion);

    // Skip the first frame in v2.
    if (iPCMFrameNumber < 0)
        return wmaResult;
    
    sprintf(fileName, "%sFrmBitsInfo.dat", pMetaFileName);    
    fp = FOPEN(fileName, "at+");
    if ( fp )
    {

    //    WMAFprintf(fp, "PCMFrmNum %10d FrmSta %15I64d FrmEnd %15I64d FrmBits %10d 1stNewFrmInPkt %1d\n", 
    //        iPCMFrameNumber, paudec->m_ibstrm.m_iFrameStart, paudec->m_ibstrm.m_iFrameEnd, paudec->m_cUsedBitsFromParser, paudec->m_ibstrm.m_f1stNewFrmInPkt);
        WMAFprintf(fp, "PCMFrmNum %10d FrmHdrBits %4d FrmTtlBits %10d 1stNewFrmInPkt %1d\n", 
            iPCMFrameNumber, pau->m_cFrmHdrBitsFromParser, pau->m_cFrmUsedBitsFromParser, paudec->m_ibstrm.m_f1stNewFrmInPkt);

        FCLOSE(fp);
    }

    stFrmInfo.iFrameNumber = iPCMFrameNumber;
    stFrmInfo.cFrameBits = (pau->m_cFrmUsedBitsFromParser + 7)/ 8;
    stFrmInfo.iOffset = 0;
#endif //WMA_COMPTOOL_NODUMPING
    return wmaResult;
}

// Dump frame bits.
WMARESULT prvWriteMetaFileFrameBitsData (CAudioObjectDecoder * paudec, LPCSTR pMetaFileName, I32 iPCMFrameNumber)
{
    CAudioObject * pau = paudec->pau;
    WMARESULT wmaResult = WMA_OK;
    FILE * fp = NULL;
    char fileName[_MAX_PATH] = "";
    size_t cFrameBytes;

    // CTODO: in editing project, we may still need the first frame in V2.
    // Skip the first frame in v2.
    if (iPCMFrameNumber < 0)
        return wmaResult;

    cFrameBytes = (pau->m_cFrmUsedBitsFromParser + 7)/ 8;
    assert(cFrameBytes < (size_t)(pau->m_cFrameBitsBufLen / 8 + 1));

    // Turn all trailing bit to 0 in v3 in order to have perfect match with encoder dump
    if (paudec->pau->m_iVersion >= 3)
    {
        I32 iByte = pau->m_cFrmUsedBitsFromParser / 8;
        U8 iRem = (U8)(pau->m_cFrmUsedBitsFromParser % 8);
        if (iRem)
            pau->m_rgbFrameBits[iByte] = (pau->m_rgbFrameBits[iByte] >> (8 - iRem + 1)) << (8 - iRem + 1);
        else
            pau->m_rgbFrameBits[iByte - 1] = pau->m_rgbFrameBits[iByte - 1] & 0xFFFE;
    }

    // set the extra bits in last byte to 0s.
    if (pau->m_cFrmUsedBitsFromParser % 8 != 0)
    {
        I32 iShiftRight = 8 - pau->m_cFrmUsedBitsFromParser % 8;
        pau->m_rgbFrameBits[cFrameBytes - 1] = (pau->m_rgbFrameBits[cFrameBytes - 1] >> iShiftRight) << iShiftRight;
    }

#ifndef WMA_COMPTOOL_NODUMPING
    // dump framebits to file.
    sprintf(fileName, "%sFrmBits-%010d.dat",pMetaFileName, iPCMFrameNumber);
    fp = FOPEN(fileName, "wb");
    if (fp)
    {
        // Write frame bits out.
        if (FWRITE(pau->m_rgbFrameBits, 1, cFrameBytes ,fp) != cFrameBytes)
        {
            assert(WMAB_FALSE);
        }
        FCLOSE(fp);
    }
#endif //WMA_COMPTOOL_NODUMPING

    return wmaResult;
}

WMARESULT prvAddBitsToFrameBitsBuf (void *pDec, U8 * pbSrc, I32 cbSrc, I32 iStart, I32 iEnd)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObjectDecoder * paudec = (CAudioObjectDecoder *)pDec;
    CAudioObject * pau = paudec->pau;

    if (pau->m_cFrmUsedBitsFromParser + (iEnd - iStart) > (pau->m_cFrameBitsBufLen << 3))
    {
        // This frame includes too much bits. Something wrong.
        return ASSERTWMA_EXIT (wmaResult, WMA_E_BROKEN_FRAME);
    }
    assert(pbSrc != NULL);
    assert(pau->m_rgbFrameBits != NULL);

    pau->m_cFrmUsedBitsFromParser = prvBitsCopy (pbSrc, cbSrc, iStart, iEnd, 
                            pau->m_rgbFrameBits, pau->m_cFrameBitsBufLen / 8 + 1, pau->m_cFrmUsedBitsFromParser);
exit:
    return wmaResult;
}

WMARESULT prvWriteMetaFileMask (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject * pau = paudec->pau;  
#ifndef WMA_COMPTOOL_NODUMPING

    PerChannelInfo * ppcinfo;

    I16 iCh, iChSrc;
    I32 iMaskBand;
    char fileName[_MAX_PATH];
    FILE * fp;

    sprintf(fileName, "%sMask-%010d-%04d.dat",pMetaFileName, iPCMFrameNumber, iCurrTile);
    
    fp = FOPEN(fileName,"wt+");
    if (fp == NULL)
    {
        // assert(0);
        return wmaResult;
    }

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        iChSrc = pau->m_rgiChInTile [iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;
        WMAFprintf(fp, "PCMFrmNum = %6d iCurrTile = %4d iCh = %2d MaskUpdate = %1d MaskQuatMultiplier = %3d cValidBarkBand = %3d ", 
            iPCMFrameNumber, iCurrTile, iChSrc, ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0], 
            ppcinfo->m_iMaskQuantMultiplier, pau->m_cValidBarkBand);
        for (iMaskBand = 0; iMaskBand < pau->m_cValidBarkBand; iMaskBand++)
        {
            WMAFprintf(fp, "%4d ",ppcinfo->m_rgiMaskQ[iMaskBand]);
        }
        WMAFprintf(fp,"\n");
    }
    FCLOSE(fp);
#endif //WMA_COMPTOOL_NODUMPING
    return wmaResult;

}

WMARESULT prvWriteMetaFileTileInfo (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName)
{
    WMARESULT wmaResult = WMA_OK;
#ifndef WMA_COMPTOOL_NODUMPING
    CAudioObject * pau = paudec->pau;  
    char fileName[_MAX_PATH];
    FILE * fp;

    sprintf(fileName, "%sSubFrmInfo-%010d-%04d.dat",pMetaFileName, iPCMFrameNumber, iCurrTile);
    
    fp = FOPEN(fileName,"wt");
    if (fp == NULL)
    {
        // assert(0);
        return wmaResult;
    }

    WMAFprintf(fp, "StereoMode %2d Stepsize %4d\n", pau->m_stereoMode, pau->m_iQuantStepSize);
    FCLOSE(fp);
#endif //WMA_COMPTOOL_NODUMPING
    return wmaResult;
}

WMARESULT prvWriteMetaFileCHX (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject * pau = paudec->pau;

#ifndef WMA_COMPTOOL_NODUMPING

    I16 iChGrp = 0;
    I16 iCh, iBand = 0;

    char fileName[_MAX_PATH];
    FILE * fp;

    if (pau->m_cChannel == 1 && pau->m_bMonoV3)
        return wmaResult;

    sprintf(fileName, "%sChX-%010d-%04d.dat",pMetaFileName, iPCMFrameNumber, iCurrTile);
    
    fp = FOPEN(fileName,"wt");
    if (fp == NULL)
    {
        // assert(0);
        return wmaResult;
    }

    WMAFprintf(fp, "Total Groups %04d\n", paudec->m_cChannelGroup);
    for (iChGrp = 0; iChGrp < paudec->m_cChannelGroup; iChGrp++) {
        CChannelGroupInfo * pcgi = paudec->m_rgChannelGrpInfo + iChGrp;
        I32 cAngles = (pcgi->m_cChannelsInGrp * (pcgi->m_cChannelsInGrp - 1)) / 2;
        I32 cSigns = pcgi->m_cChannelsInGrp;
        I32 i;

        WMAFprintf(fp, "Group %4d ChInGrp %03d SuperGrp %01d PredefX %01d PredefXType %02d AllBarksOn %01d ", 
            iChGrp, pcgi->m_cChannelsInGrp, pcgi->m_fIsSuperGroupXform, 
            pcgi->m_fIsPredefinedXform, pcgi->m_predefinedXformType, pcgi->m_fAllBarksOn);
        WMAFprintf(fp, "ChMask ");
        for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
        {
            WMAFprintf(fp, " %02d ", paudec->m_rgChannelGrpInfo[iChGrp].m_rgfChannelMask[iCh]);
        }
        WMAFprintf(fp, "XformOn cBands %03d", pau->m_cValidBarkBand);
        for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++)
        {
            WMAFprintf(fp, " %02d ", paudec->m_rgChannelGrpInfo[iChGrp].m_rgfXformOn[iCh]);
        }
        WMAFprintf(fp, "Angles ");
        for (i = 0; i < cAngles; i++) {
            assert(pcgi->m_rgbRotationAngle[i] < MAX_ROTATION_ANGLE_INDEX);
            assert(pcgi->m_rgbRotationAngle[i] >= -MAX_ROTATION_ANGLE_INDEX);
            WMAFprintf(fp, " %05d ",pcgi->m_rgbRotationAngle[i]);
        }
        WMAFprintf(fp, "cSigns ");
        for (i = 0; i < cSigns; i++) {
            assert(pcgi->m_rgbRotationSign[i] == 0 || pcgi->m_rgbRotationSign[i] == 1);
            WMAFprintf(fp, " %05d ",pcgi->m_rgbRotationSign[i]);
        }
        WMAFprintf(fp, "\n");
    }
    FCLOSE(fp);

#endif WMA_COMPTOOL_NODUMPING
    return wmaResult;
}

WMARESULT prvWriteMetaFileMDCTCoeffs (CAudioObjectDecoder * paudec, I32 iPCMFrameNumber, I16 iCurrTile, LPCSTR pMetaFileName)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject * pau = paudec->pau;

#ifndef WMA_COMPTOOL_NODUMPING

    I16 iCh, iBand = 0;

    char fileName[_MAX_PATH];
    FILE * fp;

    sprintf(fileName, "%sMDCTCoef-%010d-%04d.dat",pMetaFileName, iPCMFrameNumber, iCurrTile);
    
    fp = FOPEN(fileName,"wb");
    if (fp == NULL)
    {
        // assert(0);
        return wmaResult;
    }
    
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        CoefType *pfltCoefRecon;
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChSrc;
        pfltCoefRecon = (CoefType *)pau->m_rgpcinfo[iChSrc].m_rgiCoefRecon;
        fwrite (pfltCoefRecon, 1, sizeof(Float) * ppcinfo->m_cSubbandAdjusted, fp);
    }
    fclose (fp);
#endif WMA_COMPTOOL_NODUMPING

    return wmaResult;
}
#endif //WMA_COMPRESSION_TOOL

#if defined(BUILD_WMAPROLBRV2) && defined(INCLUDE_BASEPLUS)
#include "baseplusdecpro.c"
#endif
