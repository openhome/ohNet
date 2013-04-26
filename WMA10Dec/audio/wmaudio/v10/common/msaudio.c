//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Std, WMA Pro, and WMA Lossless.
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    MsAudio.cpp

Abstract:

    Implementation of public member functions for CAudioObject.

Author:

    Wei-ge Chen (wchen) 11-March-1998

Revision History:


*************************************************************************/

// Print out the target we're building for
#define COMMONMACROS_OUTPUT_TARGET

#if !defined (_WIN32_WCE) && !defined (HITACHI)
#include <time.h>
#endif  // _WIN32_WCE

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include "msaudio.h"
#include "AutoProfile.h"
#include "float.h"
#include "wavfileexio.h"
#include "drccommon.h"
#include "fex.h"

#if (!defined(WMA_DISABLE_SSE1) || defined(WMA_TARGET_X86)) && !defined (DISABLE_OPT)
#include "cpudetect.h"
#endif  // !defined(WMA_DISABLE_SSE1) ...

#if !defined(DISABLE_INTELFFT)
#include "IntelIPP.h"
#endif // !defined(DISABLE_INTELFFT)

#define MIN_SUBFRAME_SIZE_V2 (128)

#if defined(_SH4_)
#    pragma warning(push)
#    pragma warning(disable:4719)
#endif // #if defined(_SH4_)


//*****************************************************************************************
// Forward Function Declarations
//*****************************************************************************************
#if defined (WMA_OPT_AUGETPCM_XENON)
void* XMemCpy(void *dest, const void *src, unsigned long count);
#endif 
Void prvSetAdjustedValues(CAudioObject *pau, I16 cSubbandAdjusted);
Void prvSetAdjustedValuesPC(CAudioObject *pau, PerChannelInfo *ppcinfo);
Void prvFFT4DCT(Void *pFFTInfo, CoefType data[], Int nLog2np, FftDirection fftDirection);

//*****************************************************************************************
//
// auNew
// create and initialize a CAudioObject
//
//*****************************************************************************************
CAudioObject* auNew ()
{
    CAudioObject* pau = (CAudioObject*) auMalloc (sizeof (CAudioObject));

    if ( pau == NULL )
    {
        WMARESULT wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        // Cant return wmaResult!
        return pau;
    }

    memset(pau, 0, sizeof(CAudioObject));

    memset(&pau->m_qstQuantStep, 0, sizeof(pau->m_qstQuantStep)); // May be struct or float/double
    // memset(pau->m_rgiQuantStepFract, 0, sizeof(pau->m_rgiQuantStepFract));
    pau->m_iPacketCurr = 0;
    pau->m_cBitPackedFrameSize = 0;
    pau->m_cBitPacketLength = 0;
    pau->m_cRunOfZeros = 0;
    pau->m_iLevel = 0; 
    pau->m_iSign = 0;

    pau->m_cRunOfMaskZeros    = 0;
    pau->m_iMaskLevel         = 0;
    pau->m_iCurrReconMaskBand = 0;

    pau->m_fNoiseSub = WMAB_FALSE; 
    pau->m_BitsPerSample = 0;
    pau->m_WeightedBitsPerSample = 0;

    pau->m_iMaxEscSize = 9;
    pau->m_iMaxEscLevel = (1 << pau->m_iMaxEscSize) - 1;

    pau->m_iVersion   = 0;
    pau->m_iEncodeOpt = 0;
    pau->m_codecStatus     = CODEC_NULL;
    pau->m_fSeekAdjustment = WMAB_FALSE;
    pau->m_iSamplingRate  = 0;
    pau->m_cBytePerSec    = 0;
    pau->m_cChannel       = 0;
    pau->m_nBytePerSample = 2;
    pau->m_nBitsPerSample = 16;
    pau->m_nValidBitsPerSample = 16;
    pau->m_iBitDepthSelector   = BITDEPTH_16;
    pau->m_dataType            = PCMDataPCM;
    pau->m_nSubWooferChannel   = -1;
  
    // V3 RTM bits
    pau->m_bV3RTM   = WMAB_FALSE;

    // V3 lossless LPC
    pau->m_bEnforcedUnifiedLLM = WMAB_FALSE;
#if !defined(DISABLE_ENC_MLLM)
    pau->m_fEnableUnifiedLLM = WMAB_TRUE;
#else // !DISABLE_ENC_MLLM
    pau->m_fEnableUnifiedLLM = WMAB_FALSE;
#endif // DISABLE_ENC_MLLM
    pau->m_bUnifiedLLM = WMAB_FALSE; // Lossless is not the default choice. ChaoHe 8-20-2001

//    pau->m_bMLLMUsePLLMPrevFrm = WMAB_FALSE;
    pau->m_bUnifiedPureLLMCurrFrm = WMAB_FALSE;
    pau->m_bUnifiedPureLLMNextFrm = WMAB_FALSE;

    pau->m_bFirstUnifiedPureLLMFrm = WMAB_FALSE;
    pau->m_bSecondUnifiedPureLLMFrm = WMAB_FALSE;
    pau->m_bLastUnifiedPureLLMFrm = WMAB_FALSE;

    pau->m_bPureLosslessMode  = WMAB_FALSE;
    pau->m_bDoInterChDecorr   = WMAB_FALSE;
    pau->m_bDoMCLMS           = WMAB_FALSE;
    pau->m_bSeekable          = WMAB_FALSE;
    pau->m_iPCMTrailZeros     = 0;
    pau->m_bOutputRawPCM      = WMAB_FALSE;
    pau->m_cGetPCMSamplesDone = 0;

    pau->m_fAllowSuperFrame = WMAB_FALSE;
    pau->m_fAllowSubFrame   = WMAB_FALSE;
    pau->m_fV5Lpc           = WMAB_FALSE;

    pau->m_iCurrReconCoef          = 0;
    pau->m_iSubFrameSizeWithUpdate = 0;
    pau->m_iMaxSubFrameDiv         = 1;
    pau->m_cMinSubFrameSample      = 0;
    pau->m_cMinSubFrameSampleHalf  = 0;
    pau->m_cMinSubFrameSampleQuad  = 0;
    pau->m_cPossibleWinSize = 0;

    pau->m_cBitsSubbandMax  = 0;
    pau->m_cFrameSample     = 0;
    pau->m_cFrameSampleHalf = 0;
    pau->m_cFrameSampleQuad = 0;

    pau->m_cLowCutOff      = 0;
    pau->m_cHighCutOff     = 0;
    pau->m_cLowCutOffLong  = 0;
    pau->m_cHighCutOffLong = 0;

    pau->m_bFreqex = WMAB_FALSE;
    // remaining fex members set to 0 by memset above
    pau->m_bCx = WMAB_FALSE;

    pau->m_iWeightingMode  = LPC_MODE;
    pau->m_stereoMode      = STEREO_LEFTRIGHT;
    pau->m_iEntropyMode    = 0;
    pau->m_fltDitherLevel  = 0.04F;
    pau->m_iQuantStepSize  = (MIN_QUANT + MAX_QUANT - 1) / 2;

    pau->m_fltDctScale           = 0;
    pau->m_cValidBarkBand        = 0;
    pau->m_rgiBarkIndex          = NULL;
    pau->m_cSubWooferCutOffIndex = 0;
    pau->m_rgiCoefQ              = NULL;

    pau->m_rgpcinfo              = NULL;

    pau->m_rgiCoefReconOrig      = NULL;
    pau->m_rgiCoefReconMLLMOrig  = NULL;
    
    pau->m_rgiMaskQ              = NULL;
    pau->m_rgiMaskQResampled     = NULL;
    pau->m_rgcValidBarkBand      = NULL;
    pau->m_rgiBarkIndexOrig      = NULL;
    pau->m_rgrgrgnBarkResampleMatrix = NULL;
    pau->m_rgcSubWooferCutOffIndex   = NULL;

    pau->m_rgiPCMInHistory = NULL;
    pau->m_rgiDiscardSilence = NULL;
    pau->m_rgiInterlacedInput = NULL;
    pau->m_rgiInterlacedInputT = NULL;
    pau->m_fLeadingSilence = WMAB_FALSE;
    pau->m_u32LeadingSize = 0;
    pau->m_u32TrailingSize = 0;
    pau->m_iPCMReconStart = 0;
    pau->m_iPCMReconEnd = 0;

#ifdef ENABLE_ALL_ENCOPT
    pau->m_fltFirstNoiseFreq = 0;
    pau->m_iFirstNoiseBand = 0;
    pau->m_iFirstNoiseIndex = 0;
    pau->m_iNoisePeakIgnoreBand = 1;

    pau->m_rgiFirstNoiseBand = NULL;
    pau->m_rgbBandNotCoded = NULL;
    pau->m_rgffltSqrtBWRatio = NULL;
    pau->m_rgiNoisePower = NULL;

#if defined(_DEBUG) && defined(LPC_COMPARE)
    memset(pau->m_rgfltLpsSpecCos, 0, sizeof(pau->m_rgfltLpsSpecCos));
    memset(pau->m_rgfltLpsSpecSin, 0, sizeof(pau->m_rgfltLpsSpecSin));
#endif  // _DEBUG
#endif  // ENABLE_ALL_ENCOPT

    pau->m_rgWeightFactor    = NULL;
#if !defined(BUILD_INTEGER)
    pau->m_rgfltWeightFactor = NULL;
#endif
    pau->m_rguiWeightFactor  = NULL;

    pau->m_iFrameNumber = 0;
    
    // transform domain resampling (by 2^n or 1/2^n, where n is (+) integer)
    pau->m_fHalfTransform         = WMAB_FALSE;
    pau->m_fPad2XTransform        = WMAB_FALSE;
    pau->m_iXformSamplingRate     = 0;
    pau->m_iAdjustSizeShiftFactor = 0;
    pau->m_fWMAProHalfTransform   = WMAB_FALSE;

    pau->m_cFrameSampleAdjusted     = 0; 
    pau->m_cFrameSampleHalfAdjusted = 0;
    pau->m_cHighCutOffAdjusted      = 0;

#ifdef ENABLE_ALL_ENCOPT
    pau->aupfnInverseQuantize = prvInverseQuantizeMidRate;
#else
    pau->aupfnInverseQuantize = NULL;
#endif
    pau->prvpfnInverseTransformMono = NULL; // Not currently used
    pau->aupfnGetNextRun = NULL;

    pau->aupfnReconSample = auReconSample;
    pau->m_pfnPostProcess = NULL;

#if defined(BUILD_WMASTD) || defined(BUILD_WMAPRO)

    pau->aupfnDctIV       = auDctIV;
    pau->aupfnFFT         = prvFFT4DCT;
    pau->m_pfnInvFftComplexConjugate = prvInvFftComplexConjugate;
    pau->m_pfnApplyWindow = auApplyWindow;

    pau->m_pfnSetSample   = NULL;
    pau->m_pfnGetSample   = NULL;

#endif // BUILD_WMASTD || BUILD_WMAPRO

#if !defined(DISABLE_INTELFFT)
    pau->m_fIntelFFT     = WMAB_FALSE;
    pau->m_fIntelCcsFFT  = WMAB_FALSE;
    pau->m_hIntelFFTInfo = NULL;
    pau->m_hIntelFFTCcsInfo = NULL;
#endif  // !defined(DISABLE_INTELFFT)

    RandStateClear(&(pau->m_tRandState));

#ifdef USE_SIN_COS_TABLES
    //MMX tables
    pau->m_piSinForRecon8192 = NULL;
    pau->m_piSinForRecon4096 = NULL;
    pau->m_piSinForRecon2048 = NULL;
    pau->m_piSinForRecon1024 = NULL;
    pau->m_piSinForRecon512 = NULL;
    pau->m_piSinForRecon256 = NULL;
    pau->m_piSinForRecon128 = NULL;
    pau->m_piSinForRecon64 = NULL;
#endif

    pau->m_rgrgrgfltMultiXIDCT = NULL;
    pau->m_rgfltCoefDst        = NULL;
    pau->m_rgpfltCoefGrpSrc    = NULL;
    pau->m_rgfltGivensTmp0     = NULL;
    pau->m_rgfltGivensTmp1     = NULL;

    pau->m_ucDrcFrameScaleFactor = 0;
    pau->m_pDrc = NULL;

    pau->m_cChannelGroup    = 0;
    pau->m_rgChannelGrpInfo = NULL;
    pau->m_cChInTile        = 0;
    pau->m_rgiChInTile      = NULL;
    
    pau->m_fUseVecCoder = WMAB_FALSE;

    pau->m_fWriteFrameSize = WMAB_FALSE;
    pau->m_fExtraBitsInPktHeader = WMAB_FALSE;
    pau->m_fByteAlignFrame = WMAB_FALSE;
    pau->m_cComprFrameSizeBits = 0;

    pau->m_fGenerateDrcParams = WMAB_FALSE;

    pau->m_rgcSamplesREQ  = NULL;

#ifdef WMA_COMPRESSION_TOOL
    // Init members for Professional WMA encoder.
    pau->m_bSegDecode = WMAB_FALSE;
    pau->m_bSegDecodePeekMode = WMAB_FALSE;  
    pau->m_bPeekModeNonSekPkt = WMAB_FALSE;
    pau->m_bPeekModeDone = WMAB_FALSE;
    pau->m_cFrmsInSeg = 0;  
    pau->m_cPktsInSeg = 0;

    // Professional Encoder Related
    pau->m_rgbFrameBits = NULL;
    pau->m_cFrmUsedBitsFromParser = 0;
    pau->m_cFrmHdrBitsFromParser = 0;
    pau->m_cFrmHdrBitsFromParserOrg = 0;
#endif //WMA_COMPRESSION_TOOL

    // OK, now verify the sizes of all fundamental type definitions
#ifndef __QNX__
    assert(sizeof(U64) == 8);
    assert(sizeof(I64) == 8);
#endif
    assert(sizeof(U32) == 4);
    assert(sizeof(I32) == 4);
    assert(sizeof(U16) == 2);
    assert(sizeof(I16) == 2);
    assert(sizeof(U8) == 1);
    assert(sizeof(I8) == 1);
#ifdef WMA_DEBUG_OUTPUT
    {
        Int m;
        TCHAR str[20];
        pau->m_iWmaDebugModes[0] = 0;

        for(m=1;m<=WMA_DEBUG_NUM_MODES;m++)
        {
//            _vstprintf(str, TEXT("c:\\temp%d.dat"),m);
            _stprintf(str, TEXT("c:\\temp%d.dat"), m);
            pau->fp[m] = _tfopen(str, TEXT("wb"));
            if(pau->fp[m] != NULL)
            {
                pau->m_iWmaDebugModes[m]=1;
            }
            else
            {
                pau->m_iWmaDebugModes[m] = 0;
            }
        }
    }
#endif

#ifdef WMA_TARGET_ARM
	pau->m_ulSizeOfPerChannelInfo = sizeof(PerChannelInfo);;
#endif

    return pau;
} // auNew

//*****************************************************************************************
//
// auDelete
// delete a CAudioObject
//
//*****************************************************************************************

#if defined(BUILD_WMAPROLBRV1)

Void auDeletePlus(CAudioObject *pau)
{
    auFree(pau->m_rgiPlusBsBuf);

#if defined(BUILD_WMAPROLBRV2)
    reconProcFree(pau);
    DELETE_PTR(pau->m_prp);
#endif

    freqexFree(pau);

#if defined(BUILD_WMAPROLBRV2)
    chexFree(pau);
    DELETE_PTR(pau->m_pcx);
#endif

#if defined(BUILD_WMAPROLBRV2)
    bpDelete(pau, pau->m_pbp);
    pau->m_pbp = NULL;
#endif
}

#endif // BUILD_WMAPROLBRV1

Void auDelete(CAudioObject* pau)
{
    if (NULL == pau)
        return;

    //V3 LLMB Chao 03-20-02
    prvFreeMCLMSPredictor(&pau->m_MCLMSPredictor);

    //V3 LLM-B. Chao. Add. 03-15-02 in the common PerChannelInfo we have some auMalloced memory. 
    //delete them before delete pau->m_rgpcinfo;
//    auDeletePcInfoCommon (pau, pau->m_rgpcinfo);
#if 0
    if (pau->m_rgpcinfo)
    {
        for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
        {
            U16 i;
            PerChannelInfo * ppcinfo = pau->m_rgpcinfo + iCh;        
            for (i = 0; i < ppcinfo->m_cLMSPredictors; i++) 
            {
                prvFreeLMSPredictor(ppcinfo->m_rgLMSPredictors + i);
            }
            for (i = 0; i < ppcinfo->m_cRLSPredictors; i++) 
            {
                prvFreeRLSPredictor(ppcinfo->m_rgRLSPredictors + i);
            }

            //V3 LLMB. Chao. Add. 03-18-02
    //        prvFreeLMSPredictor(&ppcinfo->m_MCLMSPredictor);
        }
        DELETE_ARRAY (pau->m_rgpcinfo);
    }
#endif
    DELETE_ARRAY (pau->m_rgiPCMInHistory);
    DELETE_ARRAY (pau->m_rgiDiscardSilence);
    freeAligned(pau->m_rgiInterlacedInput);
    freeAligned(pau->m_rgiInterlacedInputT);

    freeAligned(pau->m_rgiCoefReconOrig);
    freeAligned(pau->m_rgiCoefReconMLLMOrig);
    
    DELETE_ARRAY (pau->m_rguiWeightFactor);

#if !defined(BUILD_INTEGER)
    pau->m_rgfltWeightFactor = NULL;
#endif
    pau->m_rgWeightFactor    = NULL;

    DELETE_ARRAY (pau->m_rgcValidBarkBand);
    DELETE_ARRAY (pau->m_rgiBarkIndexOrig);

    prvDeleteBarkResampleMatrix(pau);
    
    DELETE_ARRAY (pau->m_rgcSubWooferCutOffIndex);
    DELETE_ARRAY (pau->m_rgiMaskQ);
    DELETE_ARRAY (pau->m_rgiMaskQResampled);

    // V3 LLM
//  DELETE_ARRAY (pau->m_rgiLLMContextProb);

#ifdef ENABLE_ALL_ENCOPT
    {
#if defined(_DEBUG) && defined(LPC_COMPARE)
        Int i;
        for (i = 0; i < LPCORDER; i++)  
        {
            if ( pau->m_rgfltLpsSpecCos[i] != NULL )
                DELETE_ARRAY (pau->m_rgfltLpsSpecCos[i]);
            if ( pau->m_rgfltLpsSpecSin[i] != NULL )
                DELETE_ARRAY (pau->m_rgfltLpsSpecSin[i]);
        }
#endif
        DELETE_ARRAY (pau->m_rgiFirstNoiseBand);
        DELETE_ARRAY (pau->m_rgbBandNotCoded);
        DELETE_ARRAY (pau->m_rgffltSqrtBWRatio);
        DELETE_ARRAY (pau->m_rgiNoisePower);
    }
#endif //ENABLE_ALL_ENCOPT

    DELETE_ARRAY (pau->m_rgiCoefQ);

#if !defined(DISABLE_INTELFFT)
    if (pau->m_fIntelFFT)
    {
        WMARESULT wmaResult;

        wmaResult = auFreeIntelFFT(pau, INTLIPP_FREE_PROCESS);
        TraceError(wmaResult);
    }
    if (pau->m_fIntelCcsFFT)
    {
        WMARESULT wmaResult;

        wmaResult = auFreeIntelCcsFFT(pau, INTLIPP_FREE_PROCESS);
        TraceError(wmaResult);
    }
#endif  // !DISABLE_INTELFFT

    if (pau->m_iVersion > 2)
        prvMultiXIDCTDelete(pau);
    DELETE_ARRAY(pau->m_rgfltCoefDst);
    DELETE_ARRAY(pau->m_rgpfltCoefGrpSrc);
    DELETE_ARRAY(pau->m_rgfltGivensTmp0);
    DELETE_ARRAY(pau->m_rgfltGivensTmp1);
    
#if defined (BUILD_WMAPRO)
    if (pau->m_pDrc != NULL) drcFree(pau->m_pDrc);
#endif // BUILD_WMAPRO

    DELETE_PTR(pau->m_pDrc);
    DELETE_ARRAY (pau->m_rgiChInTile);

    DELETE_ARRAY (pau->m_rgcSamplesREQ);

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder Related
    DELETE_ARRAY (pau->m_rgbFrameBits);
#endif //WMA_COMPRESSION_TOOL

#if defined(BUILD_WMAPROLBRV1)
    if (pau->m_bPlusV1 || pau->m_bPlusV2 || pau->m_bReconProc)
        auDeletePlus(pau);
#endif

    DELETE_ARRAY(pau->m_rgiSubframeStart);
    DELETE_ARRAY(pau->m_rgiCurrSubframe);
    DELETE_ARRAY(pau->m_rgtci);

    DELETE_ARRAY(pau->m_rgpcinfoShr);

    // UES
#ifdef BUILD_UES
    UESDelete(pau->m_pUES);
    pau->m_pUES = NULL;
#endif

    // debug
#ifdef WMA_DEBUG_OUTPUT
    _fcloseall();
#endif


    auFree (pau);

    DUMP_MONITOR_RANGES(0);
} // auDelete

Void auDeletePcInfoCommon (CAudioObject* pau, PerChannelInfo* rgpcinfo)
{
    //V3 LLM-B. Chao. Add. 03-15-02 in the common PerChannelInfo we have some auMalloced memory. 
    //delete them before delete pau->m_rgpcinfo;
    I16 iCh;
    if (NULL != rgpcinfo &&
        NULL != pau)
    {
        for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
        {
            U16 i;
            PerChannelInfo * ppcinfo = rgpcinfo + iCh;
            for (i = 0; i < LLMB_CLMSFLT_TTL_MAX; i++) 
            {
                prvFreeLMSPredictor(ppcinfo->m_rgLMSPredictors + i);
            }
        }
        DELETE_ARRAY (rgpcinfo);
    }
} // auDeletePcInfoCommon

WMARESULT prvInitOutputSampleFormatParameters(CAudioObject *pau,
                                              U32 nBytePerSample,
                                              PCMData dataType)
{
    pau->m_nBytePerSample = nBytePerSample;
    pau->m_dataType = dataType;

    return WMA_OK;
}

//***************************************************************************
//***************************************************************************

Int prvGetPlusVersion(Int uAdvancedEncodeOpt)
{
    Int iPlusVersion = uAdvancedEncodeOpt & ENCOPT4_PLUSVER;

#if defined(BUILD_WMAPROLBRV1)
    if (iPlusVersion == ENCOPT4_PLUSV1 || iPlusVersion == ENCOPT4_PLUSV1ALT)
        return 1;
#endif

#if defined(BUILD_WMAPROLBRV2)
    if (iPlusVersion == ENCOPT4_PLUSV2)
        return 2;
#endif

#if defined(BUILD_WMAPROLBRV3)
    if (iPlusVersion == ENCOPT4_PLUSV3)
        return 3;
#endif

    return 0;
}

WMARESULT prvInitPlusParameters(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;

    if (pau->m_iVersion < 3)
        goto exit;

    pau->m_iPlusVersion = prvGetPlusVersion(pau->m_iAdvancedEncodeOpt);

    pau->m_bPlusV1 = (1 == pau->m_iPlusVersion);
    pau->m_bPlusV2 = (2 == pau->m_iPlusVersion ||
                      3 == pau->m_iPlusVersion);

#if defined(WMA_OSTARGET_WIN32) && !defined(WMA_TARGET_ANSI)

    if( prvGetRegistryDisablePlusV1() )
        pau->m_bPlusV1 = WMAB_FALSE;

    if( prvGetRegistryDisablePlusV2() )
        pau->m_bPlusV2 = WMAB_FALSE;

#endif // WMA_OSTARGET_WIN32 && !WMA_TARGET_ANSI

    if ((pau->m_iVersion >= 3) && 
        pau->m_bPureLosslessMode)
    {
        // No Freqex with lossless encoding
        pau->m_bPlusV1 = WMAB_FALSE;
        pau->m_bPlusV2 = WMAB_FALSE;
    }

    // Either V1 or V2.
    if( pau->m_bPlusV1 && pau->m_bPlusV2 )
    {
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    pau->m_fBasePlus = WMAB_FALSE;

    // In PlusV1
    if (pau->m_bPlusV1)
    {
        pau->m_bFreqex = WMAB_TRUE;
        pau->m_bReconFex = WMAB_FALSE;
        pau->m_bCx = WMAB_FALSE;
        pau->m_fBasePlus = WMAB_FALSE;
    }

    if (pau->m_bPlusV2)
    {
        pau->m_bFreqex = WMAB_TRUE;
        if ((pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_RFEX) ==
            ENCOPT4_PLUSV2_RFEX)
            pau->m_bReconFex = WMAB_TRUE;
        else
            pau->m_bReconFex = WMAB_FALSE;

        if (pau->m_cChannel > 1 && 
            ((pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_CHEX) ==
             ENCOPT4_PLUSV2_CHEX))
            pau->m_bCx = WMAB_TRUE;
        else 
            pau->m_bCx = WMAB_FALSE;

        if (pau->m_bCx || pau->m_bReconFex)
            pau->m_bReconProc = WMAB_TRUE;
        else
            pau->m_bReconProc = WMAB_FALSE;

        if ((pau->m_iAdvancedEncodeOpt & ENCOPT4_PLUSV2_BASEPLUS) ==
            ENCOPT4_PLUSV2_BASEPLUS)
            pau->m_fBasePlus = WMAB_TRUE;
        else
            pau->m_fBasePlus = WMAB_FALSE;
    }
    WMADebugMessage( " prvInitPlusParameters 2\n");      

    if (pau->m_bPlusV2 && pau->m_cOrigChannel > 2)
        return WMA_E_NOTSUPPORTED;

#if defined(BUILD_WMAPROLBRV1)
    if (pau->m_bFreqex || pau->m_fBasePlus)
        pau->m_bNeedMaskProc = WMAB_TRUE;
#endif

    // use to test recon domain processing (even w/o chex or recon fex)
    //pau->m_bReconProc = 1;

exit:
    return wmaResult;
}

// Coded means base coding channels
// Orig means actual channels (which plus will decode)
Void prvAdjustChannelForCx(U16 uAdvancedEncodeOpt,
                           U32 uAdvancedEncodeOpt2,
                           U16 iCodedCh, U16 *piOrigCh,
                           U32 uCodedChMask, U32 *puOrigChMask)
{
    //return; // use this to simulate old decoder, along with pau->m_bReconProc=0 and direct return from plusDecodeTile
#if defined(BUILD_WMAPROLBRV2)
    Int iPlusVersion = prvGetPlusVersion(uAdvancedEncodeOpt);

    if ((2 == iPlusVersion || 3 == iPlusVersion) &&
        (uAdvancedEncodeOpt & ENCOPT4_PLUSV2_CHEX) == ENCOPT4_PLUSV2_CHEX)
    {
        Int iIndex =
            (Int)((uAdvancedEncodeOpt2 & ENCOPT4_PLUSV2_CXLCCHMASK) >>
                  ENCOPT4_PLUSV2_CXLCCHMASK_BITSOFFSET);
        // overwrite original channel for allocation, etc...
        switch (iIndex)
        {
        case CxSpeakerOrig:
            *piOrigCh = iCodedCh;
            *puOrigChMask = uCodedChMask;
            break;
        case CxSpeaker2:
            *piOrigCh = 2;
            *puOrigChMask = MCMASK_STEREO;
            break;
        case CxSpeaker3:
            *piOrigCh = 3;
            *puOrigChMask = MCMASK_THREE;
            break;
        case CxSpeaker4:
            *piOrigCh = 4;
            *puOrigChMask = MCMASK_QUAD;
            break;
        case CxSpeaker5:
            *piOrigCh = 5;
            *puOrigChMask = MCMASK_5;
            break;
        case CxSpeaker6DTS:
            *piOrigCh = 6;
            *puOrigChMask = MCMASK_5DOT1_DTS;
            break;
        case CxSpeaker6Dolby:
            *piOrigCh = 6;
            *puOrigChMask = MCMASK_5DOT1_DOLBY;
            break;
        case CxSpeaker8:
            *piOrigCh = 8;
            *puOrigChMask = MCMASK_7DOT1;
            break;
        default:
            assert(!"Invalid CxSpeaker index");
            break;
        }
    }
#endif // BUILD_WMAPROLBRV2
}

WMARESULT prvInitCommonParameters(CAudioObject *pau,
                                  Int           iVersionNumber,
                                  Bool          fUES,
                                  Int           cSubband, 
                                  Int           cSamplePerSec, 
                                  U16           cChannel, 
                                  U32           nBytePerSample,
                                  U16           nValidBitsPerSample,
                                  U32           nChannelMask,
                                  Int           cBytePerSec, 
                                  Int           cbPacketLength,
                                  U16           iEncodeOpt,
                                  U16           uAdvancedEncodeOpt,
                                  U32           uAdvancedEncodeOpt2,
                                  Int           iOutputSamplingRate,
                                  PCMData       dataType,
                                  WMAPlayerInfo *pWmaPlayerInfo)
{
    WMARESULT   wmaResult = WMA_OK;
    U16         iNonSupportedPlayerOpt;
    U16         iPlayerOpt = (pWmaPlayerInfo ? pWmaPlayerInfo->nPlayerOpt : 0);

    static const char fOKOptions[16] = {
        // WinCE Player Option Combinations
        WMAB_TRUE,  // 0: normal
        WMAB_TRUE,  // 1: Device that does not support 32kHz sampling -> interpolated downsample to 22kHz
        WMAB_TRUE,  // 2: Background HalfTransform mode to save CPU cycles
        WMAB_TRUE,  // 3: Background HalfTransform mode on device that does not support 32kHz sampling, ends up at 11kHz
        WMAB_TRUE,  // 4: A slow CPU which does not support F0 but does support 2*F0
        WMAB_TRUE,  // 5: Device that does not support 32kHz sample nor 22kHz playback, plays 32kHz data via 22kHz quality at 44kHz
        WMAB_TRUE,  // 6: Background HalfTransform mode for device that does not support half sampling rate
        WMAB_TRUE,  // 7: Background with downsampling - why?
        WMAB_TRUE,  // 8: Hide HP-430's lack of a low-pass filter for 22kHz output
        WMAB_FALSE, // 9: not appropriate - would need to interpolate to 44kHz if appropriate
        WMAB_TRUE,  // A: Background HalfTransform mode on a HP-430 at 22kHz, decode as normal (neither half nor doubled)
        WMAB_TRUE,  // B: why but why not allow?? 
        WMAB_FALSE, // C: not appropriate
        WMAB_FALSE, // D: not appropriate
        WMAB_FALSE, // E: not appropriate
        WMAB_FALSE  // F: not appropriate
    };
    assert( PLAYOPT_HALFTRANSFORM==2 && PLAYOPT_PAD2XTRANSFORM==8 );

    pau->m_iVersion = iVersionNumber;
    pau->m_fUES     = fUES;
    pau->m_cFrameSampleHalf  = cSubband;
    pau->m_iSamplingRate = cSamplePerSec;
    pau->m_cChannel = cChannel;
    pau->m_cCodedChannel = pau->m_cChannel;
    prvInitOutputSampleFormatParameters(pau, nBytePerSample, dataType);
    pau->m_nValidBitsPerSample = nValidBitsPerSample;
    pau->m_iPCMSampleMin = PCMSAMPLE_MIN(pau->m_nValidBitsPerSample);
    pau->m_iPCMSampleMax = PCMSAMPLE_MAX(pau->m_nValidBitsPerSample);
    pau->m_nChannelMask = nChannelMask;
    pau->m_nCodedChannelMask = pau->m_nChannelMask;
    pau->m_cBytePerSec = cBytePerSec;
    pau->m_cBitPacketLength = cbPacketLength * BITS_PER_BYTE;
    pau->m_iEncodeOpt = iEncodeOpt;
    pau->m_iAdvancedEncodeOpt = (I32)uAdvancedEncodeOpt;
    pau->m_uAdvancedEncodeOpt2 = uAdvancedEncodeOpt2;
    pau->m_cBytePacketLength = (pau->m_cBitPacketLength >> 3);
    assert((pau->m_cBytePacketLength<<3) == pau->m_cBitPacketLength);
    pau->m_cBitsBytePacketLength = LOG2(pau->m_cBytePacketLength) + 1;
    pau->m_cBitsBitsPacketLength = LOG2(pau->m_cBitPacketLength) + 1;
    assert(pau->m_cBytePacketLength < (1<<pau->m_cBitsBytePacketLength));
    assert(pau->m_cBitPacketLength < (1<<pau->m_cBitsBitsPacketLength));


    if (pau->m_iVersion >= 3)
        prvAdjustChannelForCx((U16)pau->m_iAdvancedEncodeOpt,
                              pau->m_uAdvancedEncodeOpt2,
                              pau->m_cChannel, &pau->m_cChannel,
                              pau->m_nChannelMask, &pau->m_nChannelMask);

    pau->m_cOrigChannel = pau->m_cChannel;
    pau->m_nOrigChannelMask = pau->m_nChannelMask;

    // --- Handle player options ---
    // First, figure out if the player has asked us for an option that we
    // didn't build
    iNonSupportedPlayerOpt = ~0; // Turn everything on
    if (pau->m_bPureLosslessMode == WMAB_TRUE) 
    {
        assert(pau->m_iVersion > 2);
        // LLM doesn't support many options.
        iNonSupportedPlayerOpt &= ~(PLAYOPT_DYNAMICRANGECOMPR);
    }
    else 
    {
        iNonSupportedPlayerOpt &= ~(PLAYOPT_HALFTRANSFORM);
        iNonSupportedPlayerOpt &= ~(PLAYOPT_PAD2XTRANSFORM);
        iNonSupportedPlayerOpt &= ~(PLAYOPT_DYNAMICRANGECOMPR);
        iNonSupportedPlayerOpt &= ~(PLAYOPT_IGNOREFREQEX);
        iNonSupportedPlayerOpt &= ~(PLAYOPT_IGNORECX);

        if (pau->m_iVersion > 2) 
        {
            iNonSupportedPlayerOpt &= ~(PLAYOPT_LTRT);
        }
    }
    WMADebugMessage( " prvInitCommonParameters player opt 0x%x, iNonSupportedPlayerOpt 0x%x\n", iPlayerOpt, iNonSupportedPlayerOpt);      

    if ( (iNonSupportedPlayerOpt & iPlayerOpt) || !fOKOptions[iPlayerOpt&0xF] )
    {
        // Player has requested something that we didn't build 
        // or wants an unsupported combination of options
        wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
        goto exit;
    }

    if ( (iPlayerOpt&(PLAYOPT_HALFTRANSFORM|PLAYOPT_PAD2XTRANSFORM))==(PLAYOPT_HALFTRANSFORM|PLAYOPT_PAD2XTRANSFORM) )
    {
        // if in pad2X mode and a shift into the background sets half transform mode, do neither
        iPlayerOpt &= ~(PLAYOPT_HALFTRANSFORM|PLAYOPT_PAD2XTRANSFORM);
    }

    pau->m_iXformSamplingRate = pau->m_iSamplingRate;
    pau->m_iAdjustSizeShiftFactor = 0;

    // PLAYOPT_XXXTRANSFORM are for testing the 2x/half-transform, so honor them first
    if (iPlayerOpt & PLAYOPT_HALFTRANSFORM)
    {
      pau->m_iAdjustSizeShiftFactor++;
      pau->m_iXformSamplingRate >>= 1;
    }
    else if (iPlayerOpt & PLAYOPT_PAD2XTRANSFORM)
    {
      pau->m_iAdjustSizeShiftFactor--;
      pau->m_iXformSamplingRate <<= 1;
    }
    else if (iOutputSamplingRate!=pau->m_iSamplingRate)
    {
        pau->m_iAdjustSizeShiftFactor =
          ROUNDF((float)(log((Double)pau->m_iSamplingRate/iOutputSamplingRate)/log(2.0)));
        if (pau->m_iAdjustSizeShiftFactor > 0)
          pau->m_iXformSamplingRate = pau->m_iSamplingRate >> pau->m_iAdjustSizeShiftFactor;
        else
          pau->m_iXformSamplingRate = pau->m_iSamplingRate << (-pau->m_iAdjustSizeShiftFactor);
    }
    pau->m_fHalfTransform = WMAB_FALSE;
    pau->m_fPad2XTransform = WMAB_FALSE;
    pau->m_fWMAProHalfTransform = WMAB_FALSE;
    
    if (pau->m_iAdjustSizeShiftFactor < 0)
    {
      pau->m_iAdjustSizeShiftFactor = -pau->m_iAdjustSizeShiftFactor;
      pau->m_fPad2XTransform = WMAB_TRUE;
    } 
    else if (pau->m_iAdjustSizeShiftFactor > 0)
    {
      pau->m_fHalfTransform = WMAB_TRUE;

      if (pau->m_iVersion > 2 && pau->m_bPureLosslessMode == WMAB_FALSE)
          // Can reduce memory allocations for WMAPro clips
          pau->m_fWMAProHalfTransform = WMAB_TRUE;
    }

#ifdef USE_SIN_COS_TABLES          
        pau->m_piSinForRecon8192 = (BP2Type*)g_SinTableForReconstruction;
        pau->m_piSinForRecon4096 = pau->m_piSinForRecon8192+8192;
        pau->m_piSinForRecon2048 = pau->m_piSinForRecon4096+4096;
        pau->m_piSinForRecon1024 = pau->m_piSinForRecon2048+2048;
        pau->m_piSinForRecon512  = pau->m_piSinForRecon1024+1024;
        pau->m_piSinForRecon256  = pau->m_piSinForRecon512+512;
        pau->m_piSinForRecon128  = pau->m_piSinForRecon256+256;
        pau->m_piSinForRecon64   = pau->m_piSinForRecon128+128;
#endif

    TRACEWMA_EXIT(wmaResult, prvInitPlusParameters(pau));

#ifdef BUILD_INTEGER
    pau->m_cLeftShiftBitsFixedPre  = COEF_FRAC_BITS;
    pau->m_cLeftShiftBitsFixedPost = COEF_FRAC_BITS;

    if (pau->m_iVersion > 2)
    {
        pau->m_bUseDynamicIntegerPrec = WMAB_TRUE;

        //if( 16 == pau->m_BitsPerSample )
        //    pau->m_bUseDynamicIntegerPrec = WMAB_FALSE;
 
#ifdef BUILD_WMAPROLBRV1
        //if( pau->m_bFreqex )
        //    pau->m_bUseDynamicIntegerPrec = WMAB_FALSE;
#endif

#ifdef BUILD_WMAPROLBRV2
        // baseplus doesn't support dynmaic integer yet.
        if( pau->m_fBasePlus )
            pau->m_bUseDynamicIntegerPrec = WMAB_FALSE;
        //if( pau->m_bCx )
        //    pau->m_bUseDynamicIntegerPrec = WMAB_FALSE;
        //if( pau->m_bReconFex )
        //    pau->m_bUseDynamicIntegerPrec = WMAB_FALSE;
        //if( pau->m_bPlusV2 )
        //    pau->m_bUseDynamicIntegerPrec = WMAB_FALSE;
#endif
    }

    if (WMAB_TRUE == pau->m_bUseDynamicIntegerPrec)
    {
        // it is essential not to left shift the input by any amount when
        // coefficients coming in since max coef is 31 bits... really?
        pau->m_cLeftShiftBitsFixedPre  = COEF_FRAC_BITS;

            
        if( 16 < pau->m_nValidBitsPerSample ) 
            pau->m_cLeftShiftBitsFixedPre = 0;

        // having a fixed shift before overlap add reduces pcm mismatches by
        // 1 or 2, since pcm input is never more than 24 bits (even after
        // quantization shouldn't be very much larger) a shift of 2 is okay.
        pau->m_cLeftShiftBitsFixedPost = COEF_FRAC_BITS;

        // On 24 bit implementations, we should change this value to 0,
        // and take the hit of 1 or 2 in pcm mismatch, else we risk overflowing
        // or should check both subframes before overlapp-add to see if
        // overflow will occur, wh  ich may result in slowdown.
        // if number of bits less than 28, set fixed shift to 0.
        if (MAX32BITVAL <= 0x7ffffff)
            pau->m_cLeftShiftBitsFixedPost = 0;
    }
#endif

exit:
    return wmaResult;
} // prvInitCommonParameters

WMARESULT prvInitOutputSampleFormatSecondaryFixed(CAudioObject *pau)
{
    assert(pau->m_nBytePerSample > 0 && pau->m_nBytePerSample <= 4);
    
    if (PCMDataPCM == pau->m_dataType)
    {
        pau->m_iBitDepthSelector = (BITDEPTH)((pau->m_nBytePerSample - 1) |
            ((pau->m_nValidBitsPerSample - 1) << 2));
    }
    else if (PCMDataIEEE_FLOAT == pau->m_dataType)
    {
        // Force usage of prvGetSample & prvSetSample for floating point output.
        pau->m_iBitDepthSelector = (BITDEPTH) 0;
    }

    pau->m_nBitsPerSample = pau->m_nBytePerSample * 8;

    return WMA_OK;
}

WMARESULT prvInitCommonSecondaryFixed(CAudioObject *pau)
{
    WMARESULT   wmaResult = WMA_OK;

    if (pau->m_iVersion > 2)
        pau->m_fAllowSuperFrame = WMAB_TRUE;

    // m_iBitDepthSelector is a one-step way to consider both bytePerSample/validBitsPerSample
    assert(pau->m_nValidBitsPerSample > 0 && pau->m_nValidBitsPerSample <= 32);
    prvInitOutputSampleFormatSecondaryFixed(pau);

    {
        const Float fltBPS = pau->m_cBytePerSec * 8.0f / ( pau->m_iSamplingRate * pau->m_cCodedChannel );

        // With the same QuantStep, the stereo is equivalent to the mono with 1.6 times the bitrate/ch.
    
        Float fltWBPS = ( 2 == pau->m_cCodedChannel ) ?  ( fltBPS * MSA_STEREO_WEIGHT  ) :
                      ( ( 2 <  pau->m_cCodedChannel ) ?  ( fltBPS * MSA_MULTICH_WEIGHT ) :
                                                      fltBPS );

#if 0
        // disable as it seems to work worse
        if (2 == pau->m_cChannel && WMAB_TRUE == pau->m_bCx)
            fltWBPS = (pau->m_cBytePerSec * 8.0f - CX_BITRATE) / pau->m_iSamplingRate;
#endif

        // in the integer build, this converts floating point values to fixed point

        pau->m_BitsPerSample         = WBPS( fltBPS  );
        pau->m_WeightedBitsPerSample = WBPS( fltWBPS );
    }

    // Identify subwoofer position
    prvGetChannelNumAtSpeakerPosition (pau->m_nChannelMask, SPEAKER_LOW_FREQUENCY,
                                       &(pau->m_nSubWooferChannel));
    //pau->m_nSubWooferChannel = 5; // Temporary hardcoding for some old content.    
    pau->m_cFrameSample      = 2 * pau->m_cFrameSampleHalf;
    pau->m_cFrameSampleQuad  = pau->m_cFrameSampleHalf / 2; 

    if (pau->m_iVersion <= 2)
    {
        pau->m_iWeightingMode    = (pau->m_iEncodeOpt & ENCOPT_BARK) ? BARK_MODE : LPC_MODE;
        pau->m_fV5Lpc = (pau->m_iEncodeOpt & ENCOPT_V5LPC) ? WMAB_TRUE : WMAB_FALSE;
        
#ifndef ENABLE_LPC
        if (LPC_MODE == pau->m_iWeightingMode)
        {
            WMADebugMessage( " prvInitCommonSecondaryFixed LPC_MODE\n");      
            // This build of the codec does not support LPC!
            wmaResult = TraceResult(WMA_E_NOTSUPPORTED);
            goto exit;
        }
#endif  // ENABLE_LPC

        pau->m_fAllowSuperFrame  = !!(pau->m_iEncodeOpt & ENCOPT_SUPERFRAME);
        pau->m_fAllowSubFrame    = pau->m_fAllowSuperFrame && !!(pau->m_iEncodeOpt & ENCOPT_SUBFRAME);

        if (pau->m_fAllowSubFrame) 
        {
            pau->m_iMaxSubFrameDiv = ((pau->m_iEncodeOpt & ENCOPT_SUBFRAMEDIVMASK) >>
                ENCOPT_SUBFRAMEDIVSHR);
            if (pau->m_cBytePerSec / pau->m_cChannel >= 4000)
                pau->m_iMaxSubFrameDiv = (8 << pau->m_iMaxSubFrameDiv);
            else 
                pau->m_iMaxSubFrameDiv = (2 << pau->m_iMaxSubFrameDiv);
        }
        else 
        {
            pau->m_iMaxSubFrameDiv = 1;
        }

        if (pau->m_iMaxSubFrameDiv > pau->m_cFrameSample / MIN_SUBFRAME_SIZE_V2 / 2)
            pau->m_iMaxSubFrameDiv = pau->m_cFrameSample / MIN_SUBFRAME_SIZE_V2 / 2;
    }
    else 
    {
        //These may not be the best for very low bitrate;
        //but since V3 doesn't allow them anyway, we have to revisit
        //when working on that.
        pau->m_iWeightingMode    = BARK_MODE; //retiring the LPC mode
        pau->m_fV5Lpc = WMAB_TRUE;            //irrelavent
        pau->m_fAllowSuperFrame  = WMAB_TRUE; //always true for V3; we can achieve low delay with this as well just more work
        pau->m_iMaxSubFrameDiv = 1 << ((pau->m_iEncodeOpt & ENCOPT3_SUBFRM_DIV) >> 3);
        if (pau->m_iMaxSubFrameDiv > 1)
            pau->m_fAllowSubFrame = WMAB_TRUE;
        else
            pau->m_fAllowSubFrame = WMAB_FALSE;
    }
    if (pau->m_iVersion == 1)
        pau->m_cPossibleWinSize = 1;
    else 
        pau->m_cPossibleWinSize = LOG2 (pau->m_iMaxSubFrameDiv) + 1;

    pau->m_cMinSubFrameSample    = pau->m_cFrameSampleHalf * 2 / pau->m_iMaxSubFrameDiv;
    pau->m_cMinSubFrameSampleHalf= pau->m_cMinSubFrameSample / 2;
    pau->m_cMinSubFrameSampleQuad= pau->m_cMinSubFrameSampleHalf / 2; 

    // When using noise substitution for uncoded bark or frequency bands, 
    // m_fltDitherLevel sets an overall "gain" of the substitution noise
    if (pau->m_iWeightingMode == LPC_MODE)
        pau->m_fltDitherLevel = 0.04F;
    else // BARK_MODE
        pau->m_fltDitherLevel = 0.02F;

#if defined (ENABLE_ALL_ENCOPT)
    // find the region to apply noise subsitution, in the frequencies...
    WMADebugMessage( " prvInitCommonSecondaryFixed 2\n");      
    TRACEWMA_EXIT(wmaResult, prvInitNoiseSubSecondaryFixed (pau));
#else
    pau->m_fNoiseSub = WMAB_FALSE;
#endif // ENABLE_ALL_ENCOPT

    pau->m_cBitsSubbandMax = LOG2 ((U32)pau->m_cFrameSampleHalf);

    if(pau->m_iVersion == 1)
        pau->m_cLowCutOffLong    = LOW_CUTOFF_V1;                     //need investigation
    else
        pau->m_cLowCutOffLong    = LOW_CUTOFF;                        //need investigation

    if (pau->m_iVersion < 3)
        pau->m_cHighCutOffLong       = pau->m_cFrameSampleHalf - 9 * pau->m_cFrameSampleHalf / 100; //need investigation
    else
        pau->m_cHighCutOffLong       = pau->m_cFrameSampleHalf;

    //default
    pau->m_cLowCutOff            = pau->m_cLowCutOffLong;
    pau->m_cHighCutOff           = pau->m_cHighCutOffLong;
    
    if (pau->m_iVersion <= 2)
    {
        //set up some global coding condtions based on bitrate
        pau->m_iEntropyMode = SIXTEENS_OB;                     //default
        
        if( pau->m_WeightedBitsPerSample < WBPS( 0.72f ) ) 
        {
            if (pau->m_iSamplingRate >= 32000)
                pau->m_iEntropyMode = FOURTYFOURS_QB;
        }
        else if( pau->m_WeightedBitsPerSample < WBPS( 1.16f ) )
        {
            if (pau->m_iSamplingRate >= 32000) 
            {
                pau->m_iEntropyMode = FOURTYFOURS_OB;
            }
        }
    } 
    else 
    {
        pau->m_iEntropyMode = FOURTYFOURS_OB;                  //default
    }

    // Adjust frame sizes for half/double transform
    prvSetAdjustedValues(pau, 0);

    //initialize constants for packetization
    if (pau->m_iVersion <= 2)
    {
        pau->m_cBitPackedFrameSize = LOG2 ((U32)ROUNDF ( 
            FLOAT_FROM_WBPS( pau->m_BitsPerSample ) *
            pau->m_cFrameSampleHalf / 8.0F)) + 2;
    }
    else    //variable
    {  
        pau->m_cBitPackedFrameSize = LOG2 (pau->m_cBitPacketLength) + 1;
    }

    //for v2 it has to be dynamically decided
    if (pau->m_iVersion == 1) 
        pau->m_fltDctScale = BP2_FROM_FLOAT((Float) sqrt (2.0 / pau->m_cFrameSampleHalfAdjusted));

#if defined(ENABLE_ALL_ENCOPT) && defined(_DEBUG) && defined(LPC_COMPARE)
//    if (pau->m_iWeightingMode == LPC_MODE) 
    //wchen: always do since encodeopt delay
    {
        Int i;
        for (i = 0; i < LPCORDER; i++) 
        {
            pau->m_rgfltLpsSpecCos [i] = NULL;
            pau->m_rgfltLpsSpecSin [i] = NULL;
        }                                             
    }
#endif // defined(ENABLE_ALL_ENCOPT) && defined(_DEBUG) && defined(LPC_COMPARE)

#if defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)
    prvInitInverseQuadRootTable(pau);    
#endif  // defined(ENABLE_ALL_ENCOPT) && defined(ENABLE_LPC)

    if (pau->m_iVersion >= 3) 
    {
            WMADebugMessage( " prvInitCommonSecondaryFixed 3\n");      
        if (pau->m_iEncodeOpt & ENCOPT3_UNSUPPORTED_OPTS)
            TRACEWMA_EXIT(wmaResult, WMA_E_NOTSUPPORTED);
    }

    if (pau->m_iVersion >= 3)
    {
        pau->m_fUseVecCoder = WMAB_TRUE; // by default use vector huffman code
    }

    if (pau->m_iVersion >= 3)
    {
        if (pau->m_iEncodeOpt & ENCOPT3_WRITE_FRAMESIZE_IN_HDR)
            pau->m_fWriteFrameSize = WMAB_TRUE;
    }

    pau->m_bMonoV3 = WMAB_FALSE; // This flag is switched on/off in WMA Voice for old content.

    if (pau->m_iVersion >= 3)
    {
        if (pau->m_iEncodeOpt &  ENCOPT3_GENERATE_DRC_PARAMS)
            pau->m_fGenerateDrcParams = WMAB_TRUE;
        if (pau->m_cCodedChannel == 1)
            pau->m_bMonoV3 = WMAB_TRUE;
        if (pau->m_iEncodeOpt & ENCOPT3_RTMBITS)
            pau->m_bV3RTM = WMAB_TRUE;
        if (pau->m_iEncodeOpt &  ENCOPT3_EXTRABITS_IN_PKTHDR)
            pau->m_fExtraBitsInPktHeader = WMAB_TRUE;
    }

#ifdef ENABLE_MULTIPLE_OF_160
    if ((pau->m_iVersion >= 3) &&
        !pau->m_bMonoV3 &&
        pau->m_iEncodeOpt & ENCOPT3_ADV_FRMSIZE_MOD_ON)
    {
            WMADebugMessage( " prvInitCommonSecondaryFixed 4\n");      
        // Wrong mode is being used in WMA Pro. This mode can only be used in WMA Voice
        TRACEWMA_EXIT(wmaResult, WMA_E_INVALIDARG);
    }
#endif

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder Related
    pau->m_cFrameBitsBufLen = pau->m_cFrameSample * pau->m_cChannel * pau->m_nValidBitsPerSample * LLM_BUFSIZE_OVER_RAWPCM;
#endif //WMA_COMPRESSION_TOOL
exit:
    return wmaResult;
} // prvInitCommonSecondaryFixed

WMARESULT prvAllocatePcInfoCommon(CAudioObject* pau, PerChannelInfo* rgpcinfo)
{
    WMARESULT   wmaResult = WMA_OK;
    I16 iCh;

    //V3 LLM-B. Chao. Add. 03-15-02. We initialize LMS filters here.
    for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
    {
        U16   i;
        U8 * pMem = NULL;
        I32 cbMemTtl = 0;
        I32 cbMemUsed = 0;
        PerChannelInfo * ppcinfo = rgpcinfo + iCh;        
        ppcinfo->m_cLMSPredictors = LLMB_CLMSFLT_TTL_MAX;
        
        for (i = 0; i < LLMB_CLMSFLT_TTL_MAX; i++)
        {        
                TRACEWMA_EXIT(wmaResult, 
                    prvInitLMSPredictor(ppcinfo->m_rgLMSPredictors + i, LLMB_CLMSFLT_MAX_ORDER, pMem, &cbMemUsed, cbMemTtl));
                TRACEWMA_EXIT(wmaResult, 
                    prvResetLMSPredictor(pau, ppcinfo->m_rgLMSPredictors + i));
        }
    }

exit:
    return wmaResult;
} // prvAllocatePcInfoCommon

#if defined(BUILD_WMAPROLBRV1)

// SPDIF Limits imposed by encoder
Int prvFrameBitLimit(CAudioObject *pau)
{
    Int iBitFrameLimit = 65200;
    Int cOverhead = 65536 - 65200 + 128;

    if (pau->m_cFrameSampleHalf >= 4096 && 
        pau->m_cChannel > 6)
    {
        iBitFrameLimit = 2 * (65536 - cOverhead)-128;
    }
    else if (pau->m_cFrameSampleHalf >= 2048) 
    {
        iBitFrameLimit = 65536 - cOverhead;
    }
    else if (pau->m_cFrameSampleHalf >= 1024)
    {
        iBitFrameLimit = 65536/2 - cOverhead;
    }
    else
    {
        iBitFrameLimit = 65536/4 - cOverhead;
    }

    return iBitFrameLimit;
}

WMARESULT prvInitPlusAllocate(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    WMAMALLOC_COUNT_DECL;

#ifdef ALLOW_EXTERNAL_FILE_FOR_RECON
    initReplArgs();
#endif

    WMAMALLOC_COUNT_STORE(0);
    WMAMALLOC_COUNT_STORE(1);

    if (!pau->m_bPlusV1 && !pau->m_bPlusV2 && !pau->m_bReconProc)
        goto exit;

    // Calculate bit-stream size
    pau->m_iPlusBsSize = pau->m_cBitPacketLength;
    // at least 6 frames of buffer (increase for low delay modes)
    pau->m_iPlusBsSize = max(pau->m_iPlusBsSize,
                             ROUNDF(6.0f*
                                    pau->m_cFrameSampleHalf/
                                    pau->m_iSamplingRate*
                                    pau->m_cBytePerSec*8+1));
    // increase for base plus to SPDIF frame limit
    if (pau->m_fBasePlus)
        pau->m_iPlusBsSize = max(pau->m_iPlusBsSize, prvFrameBitLimit(pau));
    // convert to bytes (rounded up to int32)
    pau->m_iPlusBsSize = (pau->m_iPlusBsSize+31)/32*4;

    pau->m_rgiPlusBsBuf = (I32*)auMalloc(pau->m_iPlusBsSize*sizeof(I8));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiPlusBsBuf);

    WMAMALLOC_COUNT_PRT("  Plus buffer", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bCx)
    {
        pau->m_pcx = (Chex*)auCalloc(sizeof(Chex));
        CHECKWMA_ALLOC(wmaResult, pau->m_pcx);
        TRACEWMA_EXIT(wmaResult, chexInit(pau));
    }
#endif // BUILD_WMAPROLBRV2

    WMAMALLOC_COUNT_PRT("  Cx", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

    if (pau->m_bFreqex || pau->m_bReconFex)
    {
        TRACEWMA_EXIT(wmaResult, freqexInit(pau));
    }

    WMAMALLOC_COUNT_PRT("  FexInit", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

#if defined (BUILD_WMAPROLBRV2)
    if (pau->m_fBasePlus)
    {
        pau->m_pbp = bpNew();
        if (NULL == pau->m_pbp)
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        TRACEWMA_EXIT(wmaResult, bpInit(pau, pau->m_pbp));
    }
#endif // BUILD_WMAPRO && BUILD_WMAPROLBRV2

    WMAMALLOC_COUNT_PRT("  Bx", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bReconProc)
    {
        pau->m_prp = (ReconProc*)auCalloc(sizeof(ReconProc));
        CHECKWMA_ALLOC(wmaResult, pau->m_prp);
        TRACEWMA_EXIT(wmaResult, reconProcInit(pau));
    }
#endif

    WMAMALLOC_COUNT_PRT("  Reconproc", 0, -1);
    WMAMALLOC_COUNT_STORE(0);

    // this may need to be expanded as we may need to create masks during
    // entropy decoding since seeing if point is valid is very slow currently
    // may need to be (pau->m_cChannel/2 + pau->m_cChannel)
    // only needed for overlay mode
    if (pau->m_bNeedMaskProc && pau->m_bPlusV1)
    {
        pau->m_iNonzeroMaskCh = pau->m_cChannel/2 + 1;
        pau->m_ucNonzeroCoeffMask =
            (U8*)auMalloc(pau->m_iNonzeroMaskCh*pau->m_cFrameSampleHalf*3/16*
                          sizeof(U8));
        CHECKWMA_ALLOC(wmaResult, pau->m_ucNonzeroCoeffMask);
    }
    else if (pau->m_bNeedMaskProc && pau->m_bPlusV2)
    {
        pau->m_iNonzeroMaskCh = pau->m_cChannel;
        pau->m_ucNonzeroCoeffMask =
            (U8*)auMalloc(pau->m_iNonzeroMaskCh*pau->m_cFrameSampleHalf/8*
                          sizeof(U8));
        CHECKWMA_ALLOC(wmaResult, pau->m_ucNonzeroCoeffMask);
    }

exit:
    WMAMALLOC_COUNT_PRT("TotalPlus", 1, -1);
    return wmaResult;
}

#endif // BUILD_WMAPROLBRV1

WMARESULT prvInitCommonAllocate(CAudioObject *pau, Bool bEncoder)
{
    WMARESULT   wmaResult = WMA_OK;
    I32 iSize, iSizeCBT;
    I64 i64tmp;
    WMAMALLOC_COUNT_DECL
    
    // follow checkin 111415.
    I32 nBitsPerSampleOri = ((pau->m_nValidBitsPerSample + 7) / 8 * 8);
    pau->m_iSampleMaxValue = (1 << (nBitsPerSampleOri - 1)) - 1;
    pau->m_iSampleMinValue = -(1 << (nBitsPerSampleOri - 1));

#if defined(BUILD_WMAPROLBRV1)
    TRACEWMA_EXIT(wmaResult, prvInitPlusAllocate(pau));
#endif

    TRACEWMA_EXIT(wmaResult, prvInitMCLMSPredictor(pau, &pau->m_MCLMSPredictor, LLMB_MCLMS_MAX_ORDER_EACHCH));
    prvMCLMSPredictorReset(pau, &pau->m_MCLMSPredictor);

    iSize = sizeof(I32) * pau->m_cChannel;
    iSizeCBT = sizeof(CBT) * pau->m_cChannel;
    pau->m_rgiPCMInHistory = (I32 *)auMalloc(iSize);
    if (NULL == pau->m_rgiPCMInHistory)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pau->m_rgiPCMInHistory, 0, iSize);

    iSize = sizeof(I32) * pau->m_cChannel;
    pau->m_rgiDiscardSilence = (I32 *)auMalloc(iSize);
    if (NULL == pau->m_rgiDiscardSilence)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pau->m_rgiDiscardSilence, 0, iSize);

    pau->m_rgiInterlacedInput = (CBT *)mallocAligned (iSizeCBT, 32);
    if (NULL == pau->m_rgiInterlacedInput) 
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pau->m_rgiInterlacedInput, 0, iSizeCBT);

    pau->m_rgiInterlacedInputT = (CBT *)mallocAligned (iSizeCBT, 32);
    if (NULL == pau->m_rgiInterlacedInputT) 
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pau->m_rgiInterlacedInputT, 0, iSizeCBT);

    if(pau->m_fPad2XTransform)
    { 
        if(LOG2(pau->m_cFrameSampleHalf*3/2)+1+pau->m_iAdjustSizeShiftFactor +
           LOG2(sizeof(CBT)) >= sizeof(I32)*8)
        {
            wmaResult = TraceResult(WMA_E_INVALIDARG);
            goto exit;
        }
        i64tmp = (I64)sizeof(CBT)*
            (I64)(pau->m_cFrameSampleHalf*3/2<<pau->m_iAdjustSizeShiftFactor)*
            (I64)pau->m_cChannel;
        if(i64tmp > I32_MAX)
        {
            wmaResult = TraceResult(WMA_E_INVALIDARG);
            goto exit;
        }
    }

#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bReconProc)
        pau->m_iCoefBufSize = pau->m_prp->m_iPCMSize;
    else
#endif // defined(BUILD_WMAPROLBRV2)
        pau->m_iCoefBufSize = 
            AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,
                              pau->m_fPad2XTransform,
                              pau->m_cFrameSampleHalf*3/2);

#if defined(BUILD_WMAPROLBRV2) && (CX_DECODE_MONO==1)
    if (pau->m_bCx && WMAB_FALSE==pau->m_bEncoder)
        pau->m_iCoefReconSize = pau->m_iCoefBufSize*pau->m_pcx->m_iMaxPairs;
    else
#endif
        pau->m_iCoefReconSize = pau->m_iCoefBufSize*pau->m_cChannel;
    pau->m_rgiCoefReconOrig =
        (CBT*)mallocAligned(sizeof(CBT)*pau->m_iCoefReconSize, 32);
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiCoefReconOrig);

    if (pau->m_fWMAProHalfTransform)
    {
        // Special one-channel worth of memory for Half transforming MLLM
        pau->m_rgiCoefReconMLLMOrig     = (CBT*) mallocAligned (sizeof (CBT) *
            pau->m_cFrameSampleHalf, 32);
        if (pau->m_rgiCoefReconMLLMOrig == NULL)
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
    }

#if defined (BUILD_WMASTD) || defined (BUILD_WMAPRO)
    pau->m_rgcValidBarkBand  = (Int*) auMalloc (sizeof (Int) * pau->m_cPossibleWinSize);
    if (pau->m_rgcValidBarkBand == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }

    pau->m_rgiBarkIndexOrig = (Int*) auMalloc (sizeof (Int) * (NUM_BARK_BAND + 1) * pau->m_cPossibleWinSize); //+1 : including bottom and top end
    if (pau->m_rgiBarkIndexOrig == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    prvSetBarkIndex(pau);
#endif // BUILD_WMASTD || BUILD_WMAPRO

    // Technically prvSetBarkIndex is an initialization but I have no choice but to call it,
    // as some of the following allocs require m_cValidBarkBand which is non-trivial to
    // set outside of prvSetBarkIndex.

    
    // Allocate mask resample matrices.
    TRACEWMA_EXIT(wmaResult, prvAllocateBarkResampleMatrix(pau));

    pau->m_rgcSubWooferCutOffIndex  = (Int*) auMalloc (sizeof (Int) * pau->m_cPossibleWinSize);
    if (pau->m_rgcSubWooferCutOffIndex == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }

#if defined (BUILD_WMASTD) || defined (BUILD_WMAPRO)
    pau->m_rgiMaskQ         = (Int*) auMalloc (sizeof (Int) * NUM_BARK_BAND * pau->m_cChannel);
    if (pau->m_rgiMaskQ == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    //disable for now since it suppressed an assert in v2 + basehf (which is actually not supported).
    //memset(pau->m_rgiMaskQ, 0, sizeof (Int) * NUM_BARK_BAND * pau->m_cChannel);
#endif // BUILD_WMASTD || BUILD_WMAPRO

#if defined (BUILD_WMAPRO)
    // V3
    pau->m_rgiMaskQResampled    = (Int*) auMalloc (sizeof (Int) * NUM_BARK_BAND * pau->m_cChannel);
    if (pau->m_rgiMaskQResampled == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
#endif // BUILD_WMAPRO

#if defined (ENABLE_ALL_ENCOPT) && defined (BUILD_WMASTD)
    //noise sub stuff
    pau->m_rgiFirstNoiseBand = (Int*) auMalloc (sizeof (Int) * pau->m_cPossibleWinSize);
    if(pau->m_rgiFirstNoiseBand == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);
    pau->m_rgbBandNotCoded  = (U8*) auMalloc (pau->m_cValidBarkBand * pau->m_cChannel); 
    if (pau->m_rgbBandNotCoded == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);
    pau->m_rgiNoisePower    = (Int*) auMalloc (sizeof (Int) * pau->m_cValidBarkBand * pau->m_cChannel);
    if (pau->m_rgiNoisePower == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);
    pau->m_rgffltSqrtBWRatio    = (FastFloat*) auMalloc (sizeof (FastFloat) * pau->m_cValidBarkBand * pau->m_cChannel);
    if (pau->m_rgffltSqrtBWRatio == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);
#endif // ENABLE_ALL_ENCOPT && BUILD_WMASTD
    
    TRACEWMA_EXIT(wmaResult, prvMultiXIDCTAllocate(pau));
    
    pau->m_rgfltCoefDst = (CoefType*) auMalloc(sizeof(CoefType) * pau->m_cChannel);
    if (pau->m_rgfltCoefDst == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);

    pau->m_rgpfltCoefGrpSrc = (CoefType**) auMalloc(sizeof(CoefType*) * pau->m_cChannel);
    if (pau->m_rgpfltCoefGrpSrc == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);
    
#if defined (BUILD_WMAPRO)
    if (pau->m_iVersion > 2) 
    {
        pau->m_rgfltGivensTmp0 = (ChXFormType*) auMalloc(sizeof(ChXFormType) * pau->m_cChannel);
        if (pau->m_rgfltGivensTmp0 == NULL)
            return TraceResult(WMA_E_OUTOFMEMORY);

        pau->m_rgfltGivensTmp1 = (ChXFormType*) auMalloc(sizeof(ChXFormType) * pau->m_cChannel);
        if (pau->m_rgfltGivensTmp1 == NULL)
            return TraceResult(WMA_E_OUTOFMEMORY);
    }
#endif // BUILD_WMAPRO
    
    pau->m_rgiChInTile  = (I16*) auMalloc(sizeof(I16) * pau->m_cChannel);
    if (pau->m_rgiChInTile == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);
    
    pau->m_rgcSamplesREQ = (U16*) auMalloc(sizeof(U16) * pau->m_cChannel);
    if (pau->m_rgcSamplesREQ == NULL)
        return TraceResult(WMA_E_OUTOFMEMORY);

    if (pau->m_iWeightingMode == LPC_MODE && pau->m_rguiWeightFactor==NULL)    
    {
        if( pau->m_fPad2XTransform )
        {
            if (LOG2((U32)(pau->m_cFrameSampleHalf))+1 + pau->m_iAdjustSizeShiftFactor + LOG2(sizeof(UInt)) >= sizeof(I32)*8)
            {
                wmaResult = TraceResult(WMA_E_INVALIDARG);
                goto exit;
            }
            i64tmp = (I64)sizeof(CBT)*((I64)pau->m_cFrameSampleHalf<<(I64)pau->m_iAdjustSizeShiftFactor)*(I64)pau->m_cChannel;
            if(i64tmp > I32_MAX)
            {
                wmaResult = TraceResult(WMA_E_INVALIDARG);
                goto exit;
            }
        }
        pau->m_rguiWeightFactor = (UInt*) auMalloc (sizeof (UInt) * pau->m_cFrameSampleHalf * pau->m_cChannel);
        if (pau->m_rguiWeightFactor == NULL)
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
    }

#ifdef WMA_COMPRESSION_TOOL
    // Professional Encoder Related
    pau->m_rgbFrameBits = (U8 *)auMalloc(pau->m_cFrameBitsBufLen / 8 + 1);
    if (pau->m_rgbFrameBits == NULL) 
    {
        pau->m_cFrameBitsBufLen = 0;
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pau->m_rgbFrameBits, 0, pau->m_cFrameBitsBufLen / 8 + 1);
#endif //WMA_COMPRESSION_TOOL

    pau->m_rgiSubframeStart = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiSubframeStart);
    pau->m_rgiCurrSubframe = (Int*)auCalloc(pau->m_cChannel*sizeof(Int));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgiCurrSubframe);
    pau->m_rgtci = (TileConfigInfo*)auCalloc(pau->m_cChannel*pau->m_iMaxSubFrameDiv*sizeof(TileConfigInfo));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgtci);

    pau->m_rgpcinfoShr =
       (PerChannelInfoShr*)auCalloc(pau->m_cChannel*sizeof(PerChannelInfoShr));
    CHECKWMA_ALLOC(wmaResult, pau->m_rgpcinfoShr);

exit:
    WMAMALLOC_COUNT_PRT("TotalCommon", -1, -1);
    return wmaResult;
} // prvInitCommonAllocate


WMARESULT prvResetPcInfoCommon(CAudioObject* pau, PerChannelInfo* rgpcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    I16 iCh;
    // Initialize quantizer modifiers.
    for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
    {
        rgpcinfo[iCh].m_ucQuantStepModifierIndex = 0;
        rgpcinfo[iCh].m_qstQuantStepModifier = qstCalcQuantStep(0, 0);
    }

    // Initialize mask value setup
    for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
    {
        // These pointers will be correctly assigned in encoder and decoder
        rgpcinfo[iCh].m_rgiMaskQResampled    = NULL;
        rgpcinfo[iCh].m_fAnchorMaskAvailable = WMAB_FALSE;
        rgpcinfo[iCh].m_iMaskQuantMultiplier = 1;
    }
    // Reset previous subframe size array
    for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
    {
        // These pointers will be correctly assigned in encoder and decoder
        rgpcinfo[iCh].m_iSizePrev = (I16)pau->m_cFrameSampleHalf/2;
        rgpcinfo[iCh].m_iSizeCurr = rgpcinfo[iCh].m_iSizePrev;
        rgpcinfo[iCh].m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[0] = (I16) pau->m_cFrameSampleHalf;
        rgpcinfo[iCh].m_iCurrCoefPosition = 0;
        rgpcinfo[iCh].m_rgCoefReconBase = (CoefType*)pau->m_rgiCoefReconOrig + pau->m_iCoefBufSize*iCh;
    }

#if (CX_DECODE_MONO==1)
    if (pau->m_bCx && 2==pau->m_cChannel && !pau->m_bEncoder)
        rgpcinfo[1].m_bNoDecodeForCx = WMAB_TRUE;
#endif

//exit:
    return wmaResult;
} // prvResetPcInfoCommon

WMARESULT prvInitCommonSecondaryAllocated(CAudioObject *pau)
{
    WMARESULT   wmaResult = WMA_OK;

    // Initialize mask resample matrices.
#if !defined (DEBUG_PRINT_BARK_NMR)
    if (pau->m_iVersion > 2)
#endif
    {
        auInitBarkResampleMatrix(pau);
    }

    prvSetSubWooferCutOffs (pau);
    TRACEWMA_EXIT(wmaResult, prvMultiXIDCTInit(pau));

#if defined (ENABLE_ALL_ENCOPT)
    TRACEWMA_EXIT(wmaResult, prvInitNoiseSubSecondaryAllocated(pau));
#endif

exit:
    return wmaResult;
} // prvInitCommonSecondaryAllocated

WMARESULT prvInitCommonResetOperational(CAudioObject *pau)
{
    WMARESULT   wmaResult = WMA_OK;
    Int iCh;
    PerChannelInfo *ppcinfo;
    Bool bSave = (pau->m_nChannelMask != pau->m_nOrigChannelMask);
    
    if (bSave)
        prvSaveCurChannels(pau);
    prvSetOrigChannels(pau);

    pau->m_iPacketCurr = 0;
    pau->m_iFrameNumber = 0;
    pau->m_fExpVecsInNonRLMode = WMAB_FALSE;

    memset (pau->m_rgiPCMInHistory, 0,
            sizeof(*pau->m_rgiPCMInHistory) * pau->m_cChannel);
    memset(pau->m_rgiCoefReconOrig, 0, sizeof(CBT)*pau->m_iCoefReconSize);

    if (pau->m_fWMAProHalfTransform)
    {
        memset (pau->m_rgiCoefReconMLLMOrig, 0, sizeof (CBT) *
            pau->m_cFrameSampleHalf);
    }
    pau->m_iPCMReconStart = 0;
    pau->m_iPCMReconEnd = 0;
    // Reset silence variables
    pau->m_fLeadingSilence = WMAB_FALSE;
    memset(pau->m_rgiDiscardSilence, 0, sizeof(pau->m_rgiDiscardSilence[0]) * pau->m_cChannel);
    memset(pau->m_rgiInterlacedInput, 0, sizeof(pau->m_rgiInterlacedInput[0]) * pau->m_cChannel);
    memset(pau->m_rgiInterlacedInputT, 0, sizeof(pau->m_rgiInterlacedInputT[0]) * pau->m_cChannel);
    pau->m_iQuantStepSize = (MIN_QUANT + MAX_QUANT - 1) / 2;

    if (pau->m_bEncoder)
        pau->m_iFrameStart = -3*pau->m_cFrameSampleHalf/2;
    else
        pau->m_iFrameStart = -pau->m_cFrameSampleHalf/2;
    
#if defined(BUILD_WMAPROLBRV2)
    if (!pau->m_bReconFex)
    {
        pau->m_bReconFexPresent = WMAB_FALSE;
    }

    if (!pau->m_bCx)
    {
        pau->m_bCxPresent = WMAB_FALSE;
    }

    if (WMAB_TRUE == pau->m_bReconProc)
        chexReset(pau);
#endif

    if (pau->m_rgpcinfo)
    {
        for (iCh=0; iCh < pau->m_cChannel; iCh++)
        {
            ppcinfo = pau->m_rgpcinfo + iCh;
            ppcinfo->m_bFex = WMAB_FALSE;
        }
    }
    
#if defined(BUILD_WMAPROLBRV1)
    freqexReset(pau);
#ifdef BUILD_WMAPROLBRV3
    bpeakReset(pau);
#endif
#endif // BUILD_WMAPROLBRV1

//exit:
    if (bSave)
        prvRestoreCurChannels(pau);

    return wmaResult;
} // prvInitCommonResetOperational

void prvInitGetSetFn(PFNGETSAMPLE *ppfnGetSample,
                     PFNSETSAMPLE *ppfnSetSample,
                     const BITDEPTH iBitDepthSelector)
{
        WMADebugMessage(" prvInitGetSetFn iBitDepthSelector = %d\n", iBitDepthSelector);
    // if PCMDataIEEE_FLOAT == dataType, we do not use ppfnSetSample & ppfnGetSample.
    switch (iBitDepthSelector)
    {
    case BITDEPTH_24:
        *ppfnSetSample = prvSetSample24;
        *ppfnGetSample = prvGetSample24;
        break;

    case BITDEPTH_2024:
        *ppfnSetSample = prvSetSample2024;
        *ppfnGetSample = prvGetSample2024;
        break;

    case BITDEPTH_16:
        *ppfnSetSample = prvSetSample16;
        *ppfnGetSample = prvGetSample16;
        break;

    case 0: 
        // IEEE_FLOAT buffer
        *ppfnSetSample = prvSetPCMSampleFloatBuf;
        *ppfnGetSample = prvGetPCMSampleFloatBuf;
        break;

    default:
        *ppfnSetSample = prvSetSample;
        *ppfnGetSample = prvGetSample;
        break;
    }
} // prvInitGetSetFn

WMARESULT prvInitOutputSampleFormatSetFunctionPtrs(CAudioObject *pau)
{
    prvInitGetSetFn(&pau->m_pfnGetSample, &pau->m_pfnSetSample,
                    pau->m_iBitDepthSelector);

    // Default reconstruct function
    if (PCMDataPCM  == pau->m_dataType)
    {
        pau->aupfnReconSample = auReconSample;
    }
    else 
    {
        assert (PCMDataIEEE_FLOAT == pau->m_dataType);
        pau->aupfnReconSample = auReconSampleFloat;
    }

#if defined(WMA_TARGET_X86) && !defined (DISABLE_OPT)
#ifdef BUILD_INT_FLOAT
    if( g_SupportCMOV() && 
        (PCMDataPCM  == pau->m_dataType) && 
        (pau->m_iBitDepthSelector == BITDEPTH_24 ||
         pau->m_iBitDepthSelector == BITDEPTH_16 ||
         pau->m_iBitDepthSelector == BITDEPTH_2024) ) 
    {

        pau->aupfnReconSample = auReconSample_X86; // general X86 function
    }

#ifndef WMA_DISABLE_SSE1
    if( g_SupportSSE1() &&
        (PCMDataPCM  == pau->m_dataType))
    {
        if( pau->m_iBitDepthSelector == BITDEPTH_16 )
        {
            pau->aupfnReconSample = auReconSample16_SSE1;
        }
        else if( pau->m_iBitDepthSelector == BITDEPTH_24 )
        {
            pau->aupfnReconSample = auReconSample24_SSE1;
        }
    }
#endif //WMA_DISABLE_SSE1
#endif // BUILD_INT_FLOAT
#endif  // WMA_TARGET_X86 && !DISABLE_OPT

#ifdef WMA_TARGET_ARM
    if( PCMDataPCM  == pau->m_dataType )
    {
        if( pau->m_iBitDepthSelector == BITDEPTH_16 )
        {
            pau->aupfnReconSample = auReconSample16_ARM;
        }
        else if( pau->m_iBitDepthSelector == BITDEPTH_24 )
        {
            pau->aupfnReconSample = auReconSample24_ARM;
        }
    }
#endif //WMA_TARGET_ARM

#if defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_RECON)
    if( PCMDataPCM  == pau->m_dataType )
    {
        if( pau->m_iBitDepthSelector == BITDEPTH_16 )
        {
            pau->aupfnReconSample = auReconSample16_MIPS;
        }
        else if( pau->m_iBitDepthSelector == BITDEPTH_24 )
        {
            pau->aupfnReconSample = auReconSample24_MIPS;
        }
    }
#endif //WMA_TARGET_MIPS && PLATFORM_SPECIFIC_RECON

#if defined (_WMA_TARGET_XBOX2_) && defined (WMA_OPT_AURECON_XENON) && defined (BUILD_INT_FLOAT)
    if( PCMDataPCM  == pau->m_dataType )
    {
        if( pau->m_iBitDepthSelector == BITDEPTH_16 )
        {
            pau->aupfnReconSample = auReconSample16_XENON;
        }
        else if( pau->m_iBitDepthSelector == BITDEPTH_24 )
        {
            pau->aupfnReconSample = auReconSample24_XENON;
        }
    }
    if( PCMDataIEEE_FLOAT == pau->m_dataType)
    {
        pau->aupfnReconSample = auReconSampleFloat_XENON;
    }    
#endif //_WMA_TARGET_XBOX2_

    return WMA_OK;
}

WMARESULT prvInitCommonSetFunctionPtrs(CAudioObject *pau)
{
    WMARESULT   wmaResult = WMA_OK;

    prvInitOutputSampleFormatSetFunctionPtrs(pau);

#if defined(BUILD_WMASTD) || defined(BUILD_WMAPRO)

    pau->aupfnDctIV = auDctIV;
    pau->aupfnFFT = prvFFT4DCT;
    pau->m_pfnApplyWindow = auApplyWindow;
    pau->m_pfnInvFftComplexConjugate = prvInvFftComplexConjugate;

#endif // BUILD_WMASTD || BUILD_WMAPRO

    // --- initialize LMS (MCLMS and CDLMS) function pointers --- //
    if (pau->m_nValidBitsPerSample <= 16) 
    {
        assert(pau->m_nValidBitsPerSample > 0);
#if (defined(WMA_TARGET_ARM) || defined(WMA_TARGET_SH4)) && defined(BUILD_WMALSL)
        pau->pprvMCLMSUpdate = prvDecMCLMSPredictorPredAndUpdate_I16;
#elif defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_LPCLSL)
        pau->pprvMCLMSPred = prvMCLMSPredictorPred_I16_C;
        pau->pprvMCLMSUpdate = prvDecMCLMSPredictorPredAndUpdate_I16_MIPSII;
#else
        pau->pprvMCLMSPred = prvMCLMSPredictorPred_I16_C;
        pau->pprvMCLMSUpdate = prvMCLMSPredictorUpdate_I16_C;
#endif
        pau->pprvCDLMSPred  = prvLMSPredictorPred_I16_C;
        pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I16_C;
    }
    else
    {
#if (defined(WMA_TARGET_ARM) || defined(WMA_TARGET_SH4)) && defined(BUILD_WMALSL)
        pau->pprvMCLMSUpdate = prvDecMCLMSPredictorPredAndUpdate_I32;
#elif defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_LPCLSL)
        pau->pprvMCLMSPred = prvMCLMSPredictorPred_I32_C;
        pau->pprvMCLMSUpdate = prvDecMCLMSPredictorPredAndUpdate_I32_MIPSII;
#else
        pau->pprvMCLMSPred = prvMCLMSPredictorPred_I32_C;
        pau->pprvMCLMSUpdate = prvMCLMSPredictorUpdate_I32_C;
#endif
        pau->pprvCDLMSPred  = prvLMSPredictorPred_I32_C;
        pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I32_C;
    }

#if defined(WMA_TARGET_X86) && !defined (DISABLE_OPT) && !defined(WMA_DISABLE_MMX)
    // --- initialize LMS (MCLMS and CDLMS) function pointers --- //
    if (pau->m_nValidBitsPerSample <= 16) 
    {
        assert(pau->m_nValidBitsPerSample > 0);
        if( g_SupportMMX() ) 
        {
            pau->pprvMCLMSPred = prvMCLMSPredictorPred_I16_C; // No MMX for MCLMS right now. Use C code instead
            pau->pprvMCLMSUpdate = prvMCLMSPredictorUpdate_I16_C; // No MMX for MCLMS right now. Use C code instead
            pau->pprvCDLMSPred  = prvLMSPredictorPred_I16_MMX;
            pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I16_MMX;
    #ifdef TEST_LLM_COMPUTATION_CONSISTENCE
            if (rand() % 2 == 0) 
            {
                pau->pprvCDLMSPred  = prvLMSPredictorPred_I16_C;
                pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I16_C;
            }
    #endif

        }
        else 
        {
            pau->pprvMCLMSPred = prvMCLMSPredictorPred_I16_C;
            pau->pprvMCLMSUpdate = prvMCLMSPredictorUpdate_I16_C;
            pau->pprvCDLMSPred  = prvLMSPredictorPred_I16_C;
            pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I16_C;
        }
    }
    else 
    {
        if( g_SupportMMX() )
        {
            pau->pprvMCLMSPred = prvMCLMSPredictorPred_I32_C; // No MMX for MCLMS right now. Use C code instead
            pau->pprvMCLMSUpdate = prvMCLMSPredictorUpdate_I32_C; // No MMX for MCLMS right now. Use C code instead
            pau->pprvCDLMSPred  = prvLMSPredictorPred_I32_C;
            pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I32_C;
        }
        else
        {
            pau->pprvMCLMSPred = prvMCLMSPredictorPred_I32_C;
            pau->pprvMCLMSUpdate = prvMCLMSPredictorUpdate_I32_C;
            pau->pprvCDLMSPred  = prvLMSPredictorPred_I32_C;
            pau->pprvCDLMSUpdate = prvLMSPredictorUpdate_I32_C;
        }
    }

#endif  // WMA_TARGET_X86 && !DISABLE_OPT && !WMA_DISABLE_MMX

#if !defined(DISABLE_INTELFFT)
#if defined (BUILD_WMASTD) || defined (BUILD_WMAPRO) 
    // auInitIntelFFT call checks CPU abilities for us (MMX, SIMD, etc)
    wmaResult = auInitIntelFFT(pau, INTLIPP_INIT_PROCESS);
    if (WMA_SUCCEEDED(wmaResult))
    {
        pau->m_fIntelFFT = WMAB_TRUE;
#if !defined(ENABLE_NON_POWER_OF_TWO)
        pau->aupfnFFT = prvFFT4DCT_INTEL;
#else
        if (CHECK_POWER_OF_TWO(pau->m_cFrameSampleHalfAdjusted))
            pau->aupfnFFT = prvFFT4DCT_INTEL;
        else
            pau->aupfnFFT = prvDFT4DCT_INTEL;
#endif
    }
    
    // note: encoder only needs this #if ENABLE_LPC && ENABLE_ALL_ENCOPT && BUILD_WMASTD
    if (pau->m_bCx || pau->m_bEncoder)
    {
        // Intel special libaries are possibility
        wmaResult = auInitIntelCcsFFT(pau, INTLIPP_INIT_PROCESS);
        if (WMA_SUCCEEDED(wmaResult))
        {
            pau->m_fIntelCcsFFT = WMAB_TRUE;
#if !defined(ENABLE_NON_POWER_OF_TWO)
            pau->m_pfnInvFftComplexConjugate = prvInvFftComplexConjugate_INTEL;
#else
            if (CHECK_POWER_OF_TWO(pau->m_cFrameSampleHalfAdjusted))
                pau->m_pfnInvFftComplexConjugate = prvInvFftComplexConjugate_INTEL;
            else
                pau->m_pfnInvFftComplexConjugate = prvInvDftComplexConjugate_INTEL;
#endif
        }
    }
   
    // Failure means no applicable optimizations. This isn't a fatal error, so suppress it.
    wmaResult = WMA_OK;
#endif // BUILD_WMASTD || BUILD_WMAPRO
#endif  // !defined(DISABLE_INTELFFT)

#ifdef ENABLE_ALL_ENCOPT
    if (pau->m_iWeightingMode == BARK_MODE) 
    {
        if (!pau->m_fNoiseSub)   
            pau->aupfnInverseQuantize = NULL;
        else
            pau->aupfnInverseQuantize = prvInverseQuantizeMidRate;
    }
    else
        pau->aupfnInverseQuantize = prvInverseQuantizeLowRate;
#endif  // ENABLE_ALL_ENCOPT

#if defined (_WMA_TARGET_XBOX2_) && defined (BUILD_INT_FLOAT)
#   if defined (WMA_OPT_FFT_XENON)
        pau->aupfnFFT = prvFFT4DCT_XENON;
#   endif
#   if defined (WMA_OPT_DCT_XENON)
        pau->aupfnDctIV = auDctIV_XENON;
#   endif
#endif

#if defined(BUILD_INT_FLOAT) && !defined (WMA_DISABLE_SSE1)
        if(g_SupportSSE1())
        {
            pau->aupfnDctIV = auDctIV_SSE1;
            pau->m_pfnApplyWindow = auApplyWindow_SSE1;
        }
#endif

#ifdef BUILD_WMAPROLBRV2
        pau->cxpfnReverbFilter = cxReverbFilter;
        pau->cxpfnReconMonoDiff = chexReconMonoDiff;

#if defined(BUILD_INT_FLOAT) && !defined (WMA_DISABLE_SSE1) && ( 0 == CX_SMALL_REVERB )
        if(g_SupportSSE1())
        {
            pau->cxpfnReverbFilter = cxReverbFilter_SSE1;
            pau->cxpfnReconMonoDiff = chexReconMonoDiff_SSE1;
        }
#endif
#endif

    return wmaResult;
} // prvInitCommonSetFunctionPtrs

//***************************************************************************
// Function: prvGetFramePCM
//
// Purpose:
//   This function intends to return how much PCM is available for retrieval 
//   for the entire frame.
//***************************************************************************
void prvGetFramePCM( CAudioObject* pau, Int *piFramePCM ) 
{
    Int iCh;
    Int iMinSizeOutput;

    iMinSizeOutput = SHRT_MAX; // just a init number
    for ( iCh = 0; iCh < pau->m_cChannel; iCh++ ) 
    {
        Int iSubframeNum, iSizeCurr, iSizeNext, iSizeOutput;
        I16 iQ3, iQ4;
        
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;

        iSubframeNum = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_cSubFrame;
        iSizeCurr = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[iSubframeNum-1];

        if (pau->m_fHalfTransform)
        {
            iSizeCurr >>= pau->m_iAdjustSizeShiftFactor;
        }
        else if (pau->m_fPad2XTransform)
        {
            iSizeCurr <<= pau->m_iAdjustSizeShiftFactor;
        }

        if( pau->m_iVersion <= 2 )
        {

            iSizeNext = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[iSubframeNum];

            if (pau->m_fHalfTransform)
            {
                iSizeNext >>= pau->m_iAdjustSizeShiftFactor;
            }
            else if (pau->m_fPad2XTransform)
            {
                iSizeNext <<= pau->m_iAdjustSizeShiftFactor;
            }
            
            prvCalcQ3Q4(pau, WMAB_TRUE, (I16)iSizeCurr, (I16)iSizeNext, (I16)iSizeCurr, &iQ3, &iQ4);

            iSizeOutput = pau->m_cFrameSampleHalfAdjusted + iQ3 - iSizeCurr*3/2;

        } 
        else 
        {

            // v3 and above we don't know the size of next subframe
            iSizeOutput = pau->m_cFrameSampleHalfAdjusted - iSizeCurr / 2;

        }

        // consider history 
        iSizeOutput += pau->m_cFrameSampleHalfAdjusted / 2;
        if( iSizeOutput < iMinSizeOutput )
            iMinSizeOutput = iSizeOutput;
    }

    *piFramePCM = iMinSizeOutput - pau->m_iPCMReconStart;
} // prvGetFramePCM

// shift pcm buffer iShiftAmt to the left
Void auShiftPCMBuffer(CAudioObject *pau, Int iShiftAmt)
{
    Int iCh;
    CoefType *pctPCMBuf, *pctSrc, *pctDst;
    Int iFrameSize, iCopyAmt;

    if (WMAB_TRUE == pau->m_bReconProc)
        goto exit;

    iFrameSize = AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,
                                   pau->m_fPad2XTransform,
                                   pau->m_cFrameSampleHalf);

    // except when pau->m_fHalfTransform is defined
    // iFrameSize == cFrameSampelHalfAdjusted

    iCopyAmt =
        (pau->m_cFrameSampleHalfAdjusted>>1) -
        (pau->m_iPCMReconStart - iShiftAmt);

    assert(iCopyAmt <= iShiftAmt);

    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        pctPCMBuf =
            (CoefType*)pau->m_rgiCoefReconOrig +
            (iFrameSize*3/2)*iCh +
            (iFrameSize >> 1) -
            (pau->m_cFrameSampleHalfAdjusted>>1);

        pctSrc = pctPCMBuf + pau->m_iPCMReconStart;
        pctDst = pctPCMBuf + pau->m_iPCMReconStart - iShiftAmt;

        // cannot copy more than shift amt anyways
        memcpy(pctDst, pctSrc, iCopyAmt*sizeof(CoefType));
    }

exit:
    pau->m_iPCMReconStart -= iShiftAmt;
    pau->m_iPCMReconEnd -= iShiftAmt;
}

void prvShiftPCMBuffer( CAudioObject* pau )
{
    Int iCh, iCopySize, iFrameSize;
    CoefType *pcfPCMBuf;

    // if m_iPCMReconStart go beyond frame boundary
    if( pau->m_iPCMReconStart >= pau->m_cFrameSampleHalfAdjusted )
    {

        if (WMAB_TRUE == pau->m_bReconProc)
            goto done;

        iFrameSize = AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,
                                       pau->m_fPad2XTransform,
                                       pau->m_cFrameSampleHalf);

        iCopySize = pau->m_cFrameSampleHalfAdjusted>>1;
        for( iCh = 0; iCh < pau->m_cChannel; iCh++ )
        {
            pcfPCMBuf = (CoefType *)pau->m_rgiCoefReconOrig + 
                                            (iFrameSize*3/2)*iCh +
                                            (iFrameSize >> 1) - 
                                            iCopySize;

            memcpy(pcfPCMBuf, pcfPCMBuf+pau->m_cFrameSampleHalfAdjusted, 
                   iCopySize*sizeof(CoefType));
        }
    done:
        pau->m_iPCMReconStart -= pau->m_cFrameSampleHalfAdjusted;
        pau->m_iPCMReconEnd -= pau->m_cFrameSampleHalfAdjusted;
    }
} // prvShiftPCMBuffer

//***************************************************************************
// Function: prvCountAlignedPCM
//
// Purpose:
//   This function returns how much aligned PCM is available for retrieval,
//     after silence is discarded.
//
// Arguments:
//   CAudioObject *pau [in] - CAudioObject
//   I32 *piAlignedPCM [out] - The amount of aligned PCM currently available
//     for reconstruction and return to user, minus discarded silence: eg, if
//     all aligned PCM is to be discarded, the value returned here will be zero.
//   Bool fDiscardSilence [in] - if TRUE, this function pre-discards silence
//     (simulates a call to auGetPCM, but omits the actual reconstruction work).
//     Regardless of the value of this argument, silence is always discarded
//     from the *piAlignedPCM value.
//   Bool fEntireFrame [in] - if TRUE, this function counts the aligned PCM
//     which the entire frame should return. Otherwise only operates on the
//     current (subframe) data.
//***************************************************************************
void prvCountAlignedPCM(CAudioObject *pau,
                        U16 *piAlignedPCM,
                        Bool fDiscardSilence,
                        Bool fEntireFrame,
                        Bool fSPDIF)
{
    Int iCh;
    U16 iAlignedPCMMin = SHRT_MAX;

    // There are likely issues with v2 concerning prvInitDiscardSilence (m_iActualPower
    // not set yet). Fix those before enabling this function for frame duration in v2.
    // wchen: temporarilly enable v2. tian, pleae make sure this is okay.
//    assert(WMAB_FALSE == fEntireFrame || pau->m_iVersion > 2);

    // In calculating the amount of aligned PCM available, we need to subtract
    // silence PCM, because in v3, silence is not necessarily aligned across channels.
    if (CODEC_BEGIN == pau->m_codecStatus)
        prvInitDiscardSilence(pau, fSPDIF);

    for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
        U16 iSamplesAvail = (U16)pau->m_rgiPCMInHistory[iCh];

        if (fEntireFrame)
        {
            Int i = 0;
            Int iNominalSubfrSum = 0;

            do
            {
                I16 iQ1, iQ2, iQ3, iQ4;
                const I16 iCurrSubFrameSizeHalf = (I16) ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].
                    m_rgiSubFrameSize[i];
                
                // Obtain reconstruction width of current subframe
                prvCalcQ1Q2(pau, WMAB_TRUE,
                    (I16)ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[i - 1], // -1 is valid index
                    iCurrSubFrameSizeHalf,
                    &iQ1, &iQ2);

                // There might be issues with half/double transform, because
                // cSubFrameSampleHalfAdjusted might not == iCurrSubFrameSizeHalf.
                // Verify later, but for now assert to call attention to this.
                assert(WMAB_FALSE == pau->m_fHalfTransform);
                assert(WMAB_FALSE == pau->m_fPad2XTransform);
                prvCalcQ3Q4(pau, WMAB_TRUE, iCurrSubFrameSizeHalf,
                    (I16)ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[i + 1],
                    iCurrSubFrameSizeHalf, &iQ3, &iQ4);

                if( pau->m_iVersion <= 2 )
                    iSamplesAvail += iQ3 - iQ1;
                else
                    iSamplesAvail += (U16)( ( iCurrSubFrameSizeHalf + 
                                              ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[i-1] )/2 );

                // We'll know we're finished with current frame when we hit cFrameSampleHalf
                iNominalSubfrSum += iCurrSubFrameSizeHalf;

                // Advance index
                i += 1;

            } while(iNominalSubfrSum < pau->m_cFrameSampleHalf);
            assert(pau->m_cFrameSampleHalf == iNominalSubfrSum);
        }
        else
        {
            if (pau->m_bPureLosslessMode == WMAB_FALSE &&
                CURRGETPCM_INVALID != ppcinfo->m_iCurrGetPCM_SubFrame)
            {
                if( pau->m_iVersion <= 2 )
                {
                    assert(ppcinfo->m_iCurrGetPCM_SubFrame >= ppcinfo->m_iCoefRecurQ1);
                    iSamplesAvail += ppcinfo->m_iCoefRecurQ3 - ppcinfo->m_iCoefRecurQ1;
                }
                else
                {
                    iSamplesAvail += (ppcinfo->m_iSizeCurr + ppcinfo->m_iSizePrev) / 2;
                }
            }
        }

        if( fEntireFrame )
        {
            // Subtract any silence which must be discarded
            if (pau->m_rgiDiscardSilence[iCh] > 0)
            {
                U16 iSilenceToDiscard;

                iSilenceToDiscard = (U16) min(iSamplesAvail, pau->m_rgiDiscardSilence[iCh]);
                iSamplesAvail -= iSilenceToDiscard;
            }
        }
        else
        {
            // Subtract any silence which must be discarded
            if (pau->m_rgiDiscardSilence[iCh] > 0)
            {
                U16 iSilenceToDiscard;

                iSilenceToDiscard = (U16) min(iSamplesAvail, pau->m_rgiDiscardSilence[iCh]);
                iSamplesAvail -= iSilenceToDiscard;

                pau->m_rgiDiscardSilence[iCh] -= iSilenceToDiscard;
            }

            // we simulate the reconstruction only in subframe mode
            pau->m_rgiPCMInHistory[iCh] = iSamplesAvail;
        }

        // Calculate minimum PCM output available
        if (iSamplesAvail < iAlignedPCMMin)
            iAlignedPCMMin = iSamplesAvail;
    }

    // Lossless mode has some exceptions: apply them now
    if (pau->m_bPureLosslessMode) 
    {
        if (fEntireFrame) 
            iAlignedPCMMin = (I16)pau->m_cFrameSampleHalf;
        iAlignedPCMMin = (I16)min(iAlignedPCMMin, pau->m_u32ValidSamples);
        if (fEntireFrame == WMAB_FALSE)
            iAlignedPCMMin -= pau->m_cGetPCMSamplesDone;
    }

    *piAlignedPCM = (U16)iAlignedPCMMin;
} // prvCountAlignedPCM

/****************************************************************************
**
** Function:        auPreGetPCM
**
** Description:     Compute home many samples can be generated for each subframe
**
** Return:          None
**
** Note: Now this is no need to setup for real PCM reconstruction
**
*****************************************************************************/
Void auPreGetPCM (CAudioObject* pau, U16* pcSampleDecoded, 
                  I16* pcSamplesSeekAdj, 
                  Bool fSPDIF)
{
    I16 iCh, j = 0;

    if (pau->m_bPureLosslessMode == WMAB_TRUE)
    {
        prvCountAlignedPCM(pau, pcSampleDecoded, CAP_NODISCARDSILENCE, CAP_SUBFRAMELVL, fSPDIF);
        if (pcSamplesSeekAdj != NULL) 
            *pcSamplesSeekAdj = 0;
        return;
    }

    for (iCh = 0; iCh < pau->m_cChannel; iCh++) 
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
        U16 iSamplesAvail = 0;

        ppcinfo->m_iCurrGetPCM_SubFrame = CURRGETPCM_INVALID;
    }

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;

        ppcinfo->m_iCurrGetPCM_SubFrame = (I16) ppcinfo->m_iCoefRecurQ1;
    }

    prvCountAlignedPCM(pau, pcSampleDecoded, CAP_DISCARDSILENCE,
        CAP_SUBFRAMELVL, fSPDIF);

} // auPreGetPCM

/****************************************************************************
**
** Function:        auGetPCM
**
** Description:     Generate PCM samples for output
**
** Return:          WMARESULT
**
*****************************************************************************/
WMARESULT auGetPCM (CAudioObject* pau,  // [in]  the audio structure
                    Void* pHandle,      // [in]  the caller (encoder/decoder)
                    U16* pcSample,      // [in/out] the number of samples for output
                    U8** ppbDst,        // [in/out] output buffer
                    U32 cbDstLength,    // [in] the output buffer length
                    U16 cChannel,       // [in] the number of channels
                    Bool fSPDIF)
{  
    WMARESULT hr = WMA_OK;
    U16 *rgcSamplesREQ = NULL;
    U16 cSampleREQmax;   
    I16 iCh;
    U16 iPCMRequested;
    // pau->m_nBytePerSample is destination bytes per sample, so this is okay.
    U32 cMaxSamplesInDst = (cbDstLength / pau->m_nBytePerSample / pau->m_cOrigChannel);
    CoefType *pcfPCMBuf;
    U16 cChannelTemp;
    Bool bSave = (pau->m_nChannelMask != pau->m_nOrigChannelMask);

    WMADebugMessage("auGetPCM samples %d\n", *pcSample);

    if (bSave)
        prvSaveCurChannels(pau);
    prvSetOrigChannels(pau);

#if defined(BUILD_WMAPROLBRV2)
    if (WMAB_TRUE==pau->m_bReconProc)
    {
        TRACEWMA_EXIT(hr,
                      chexGetPCM(pau, pHandle, pcSample, ppbDst, cbDstLength,
                                 cChannel, fSPDIF));
        goto exit;
    }
#endif // BUILD_WMAPROLBRV1
    
    // ======== Check the input parameter ========
    if (pau == NULL) 
    {
        TRACEWMA_EXIT(hr, WMA_E_INVALIDARG);
        goto exit;
    }

    rgcSamplesREQ = pau->m_rgcSamplesREQ;

    // ======== Limit user request to maximum aligned PCM available ========
    iPCMRequested = *pcSample;
    if (pau->m_bPureLosslessMode == WMAB_TRUE) 
    {
        prvCountAlignedPCM(pau, &iPCMRequested, CAP_NODISCARDSILENCE, CAP_SUBFRAMELVL, fSPDIF);
        if (*pcSample < iPCMRequested)
        {
            // *pcSample must be a multiple of 16: Cannot copy fractional
            // (signbit) registers at this time
            *pcSample &= ~(0x0F);
            iPCMRequested = *pcSample;
        }
    }

    // ======== For each channel setup target number of output samples ========
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
        ppcinfo->m_cSamplesLeft = iPCMRequested;

    }

    // ======== Do PCM reconstruction ========
    if (pau->m_bPureLosslessMode == WMAB_FALSE) 
    {
        I32         u32MaxSamplesReq;
        U16         iRetrieve;
        Int         iFrameSize;
        U8          *pbOutput;
        PerChannelInfo* ppcinfo;

        // ---- Check if we do have samples for output ----
        iRetrieve = (U16)(pau->m_iPCMReconEnd - pau->m_iPCMReconStart);

        u32MaxSamplesReq = min(iPCMRequested, cMaxSamplesInDst);
        u32MaxSamplesReq = min(u32MaxSamplesReq, SHRT_MAX);

        if( u32MaxSamplesReq > iRetrieve )
            u32MaxSamplesReq = iRetrieve;

        iFrameSize = AU_HALF_OR_DOUBLE(pau->m_fWMAProHalfTransform,pau->m_fPad2XTransform, pau->m_cFrameSampleHalf);
        iRetrieve = (U16)u32MaxSamplesReq;

        if( iRetrieve == 0  )
        {
            *pcSample = cSampleREQmax = 0;
        } 
        else 
        {
            // Setup number of samples requested for each channel
            // Now start to output, we simplify it a little bit.
            // we use ppbDst[0], and do interleave by ourself
            pbOutput = ppbDst[0];
            
            // first setup the buffer pointer for each channel
            for( iCh = 0; iCh < pau->m_cChannel; iCh++ )
            {
                ppcinfo = pau->m_rgpcinfo + iCh;
                ppcinfo->m_rgiPCMBuffer = pau->m_rgiCoefReconOrig + (iFrameSize*3/2) * iCh +
                                                        (iFrameSize >> 1) - 
                                                        (pau->m_cFrameSampleHalfAdjusted >> 1) + 
                                                        pau->m_iPCMReconStart;
            }

            // Post process whatever is possible before getting pcm samples
            if (NULL != pau->m_pfnPostProcess)
            {
                TRACEWMA_EXIT(hr, pau->m_pfnPostProcess(pHandle, &iRetrieve, NULL, 0));
            }

            // now read each channel
            cChannelTemp = pau->m_cChannel;
            pau->m_cChannel = cChannel;
            TRACEWMA_EXIT(hr, pau->aupfnReconSample(pau, (PCMSAMPLE*)pbOutput,
                                                    iRetrieve));
            pau->m_cChannel = cChannelTemp; // restore

            assert( iRetrieve <= (U16)(pau->m_iPCMReconEnd - pau->m_iPCMReconStart));

            pau->m_iPCMReconStart += iRetrieve;
            *pcSample = iRetrieve;

            // ******** test if m_iPCMReconStart go beyond frame boundary ********
            if( pau->m_iPCMReconStart >= pau->m_cFrameSampleHalfAdjusted )
            {
                // ==== here we need to shift PCM buffer ====
                u32MaxSamplesReq = (pau->m_cFrameSampleHalfAdjusted >> 1);

                pau->m_iPCMReconStart -= pau->m_cFrameSampleHalfAdjusted;
                pau->m_iPCMReconEnd -= pau->m_cFrameSampleHalfAdjusted;
                if( pau->m_iPCMReconStart < 0 ||
                    pau->m_iPCMReconStart >= pau->m_cFrameSampleHalfAdjusted / 2 )
                {
                    hr = WMA_E_FAIL;
                    goto exit;
                }

                for( iCh = 0; iCh < pau->m_cChannel; iCh++ )
                {
                    pcfPCMBuf = (CoefType *)pau->m_rgiCoefReconOrig + (iFrameSize*3/2) * iCh +
                                                (iFrameSize >> 1) - 
                                                u32MaxSamplesReq;
                    /* ================================================================
                    for( i = 0; i < (pau->m_cFrameSampleHalfAdjusted >> 1); i++ )
                        pcfPCMBuf[i] = pcfPCMBuf[i + pau->m_cFrameSampleHalfAdjusted];
                    =================================================================== */
#if defined (WMA_OPT_AUGETPCM_XENON)  //Use XMemCpy (faster)
                    XMemCpy( pcfPCMBuf+pau->m_iPCMReconStart, 
                            pcfPCMBuf+pau->m_cFrameSampleHalfAdjusted + pau->m_iPCMReconStart, 
                            (u32MaxSamplesReq-pau->m_iPCMReconStart)*sizeof(CoefType) );
#else
                     memcpy( pcfPCMBuf+pau->m_iPCMReconStart, 
                            pcfPCMBuf+pau->m_cFrameSampleHalfAdjusted + pau->m_iPCMReconStart, 
                            (u32MaxSamplesReq-pau->m_iPCMReconStart)*sizeof(CoefType) );
#endif  //WMA_OPT_AUGETPCM_XENON
                }
            }

        } // end of if( u32MaxSamplesReq != 0 )

    }
    else if (pau->m_bPureLosslessMode)
    {
        U16 iRetrieve = 0;

        // cMaxSamplesInDst must be a multiple of 16: Cannot copy fractional
        // (signbit) registers at this time
        cMaxSamplesInDst &= ~(0x0F);
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {
            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
            // Limit requested number of bytes to fit within the buffer
            const U32 u32MaxSamplesReq = min(ppcinfo->m_cSamplesLeft, cMaxSamplesInDst);
            
            // limit request to fit in PCMSAMPLE
            rgcSamplesREQ [iCh] = (I16) min(u32MaxSamplesReq, SHRT_MAX);
            // TODO: I request caller asks for all available samples. Need to simplify
//            assert((U32)rgcSamplesREQ[iCh] == rgcSamplesLeft[iCh]);
            ppcinfo->m_rgiPCMBuffer = ppcinfo->m_rgiCoefRecon+pau->m_cGetPCMSamplesDone;
            assert(pau->m_rgiPCMInHistory[iCh]==pau->m_rgiPCMInHistory[0]);
            assert(pau->m_rgpcinfo[iCh].m_cSamplesLeft==pau->m_rgpcinfo[0].m_cSamplesLeft);
            iRetrieve = (U16)min(pau->m_rgiPCMInHistory[iCh]-pau->m_cGetPCMSamplesDone,
                                 (Int)min(min(pau->m_rgpcinfo[iCh].m_cSamplesLeft, cMaxSamplesInDst), SHRT_MAX));
        }

        // Post process whatever is possible before getting pcm samples for lossless
        if (NULL != pau->m_pfnPostProcess)
        {
            TRACEWMA_EXIT(hr, pau->m_pfnPostProcess(pHandle, &iRetrieve, NULL, 0));
        }

        //TODO: in PLLM, cSamplesREQ is enough.
        TRACEWMA_EXIT(hr, auReconstructPureLLM(pau,
            ppbDst,
            (short *)rgcSamplesREQ,
            WMAB_FALSE));

        *pcSample = rgcSamplesREQ[0];
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {
            assert((U32)rgcSamplesREQ[iCh] == *pcSample);
        }

        cSampleREQmax = * pcSample; //useful?
    }

    if (CODEC_BEGIN == pau->m_codecStatus)
    {
        pau->m_codecStatus = CODEC_STEADY;
    }

    //FUNCTION_PROFILE_STOP(&fp);
exit:
    if (bSave)
        prvRestoreCurChannels(pau);

    return hr;
} // auGetPCM

Int auGetAdjustedSize( const CAudioObject *pau, const Int iSize)
{
    if (pau->m_fHalfTransform)
        return iSize >> pau->m_iAdjustSizeShiftFactor;
    if (pau->m_fPad2XTransform)
        return iSize << pau->m_iAdjustSizeShiftFactor;
    return iSize;
}

void prvSetAdjustedValuesPC(CAudioObject *pau, PerChannelInfo *ppcinfo)
{
    if (pau->m_fHalfTransform)
    {
        ppcinfo->m_cSubbandAdjusted = ppcinfo->m_cSubband>>pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_cSubFrameSampleHalfAdjusted = ppcinfo->m_cSubFrameSampleHalf>>pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_iSizePrev >>= pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_iSizeCurr >>= pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_iSizeNext >>= pau->m_iAdjustSizeShiftFactor;
    }
    else if (pau->m_fPad2XTransform)
    {
        ppcinfo->m_cSubbandAdjusted = ppcinfo->m_cSubband<<pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_cSubFrameSampleHalfAdjusted = ppcinfo->m_cSubFrameSampleHalf<<pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_iSizePrev <<= pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_iSizeCurr <<= pau->m_iAdjustSizeShiftFactor;
        ppcinfo->m_iSizeNext <<= pau->m_iAdjustSizeShiftFactor;
    }
    else
    {
        ppcinfo->m_cSubbandAdjusted = ppcinfo->m_cSubband;
        ppcinfo->m_cSubFrameSampleHalfAdjusted = ppcinfo->m_cSubFrameSampleHalf;
    }
}

void prvSetAdjustedValues(CAudioObject *pau, I16 cSubbandAdjusted)
{
    if (pau->m_fHalfTransform)
    {
        pau->m_cFrameSampleAdjusted        = pau->m_cFrameSample>>pau->m_iAdjustSizeShiftFactor;
        pau->m_cFrameSampleHalfAdjusted    = pau->m_cFrameSampleHalf>>pau->m_iAdjustSizeShiftFactor;
        pau->m_cHighCutOffAdjusted         = min(pau->m_cHighCutOff, cSubbandAdjusted); // unchanged unless actual number of bands is fewer
    }
    else if (pau->m_fPad2XTransform)
    {
        pau->m_cFrameSampleAdjusted        = pau->m_cFrameSample<<pau->m_iAdjustSizeShiftFactor;
        pau->m_cFrameSampleHalfAdjusted    = pau->m_cFrameSampleHalf<<pau->m_iAdjustSizeShiftFactor;
        pau->m_cHighCutOffAdjusted         = pau->m_cHighCutOff;    // unchanged
    }
    else 
    {
        pau->m_cFrameSampleAdjusted        = pau->m_cFrameSample; 
        pau->m_cFrameSampleHalfAdjusted    = pau->m_cFrameSampleHalf;
        pau->m_cHighCutOffAdjusted         = pau->m_cHighCutOff;
    }
}

Void auConvertSubframeConfigToTileConfig(CAudioObject *pau,
                                         ConfigFrame ecfConfig)
{
    Int iCh, iTile, cChInTile, cSampleLeft, iStartMin, iSizeMin;
    PerChannelInfo *ppcinfo;
    U32 uChannelMask;
    Int *piStart, *piSubFrmCurr;
    I16 *piSize;
    SubFrameConfigInfo *psubfrmconfig, *psubfrmconfigTile=0;
    Int iSubframeTile=0;

    for (iCh=0; iCh < pau->m_cCodedChannel; iCh++)
    {
        pau->m_rgiSubframeStart[iCh] = 0;
        pau->m_rgiCurrSubframe[iCh] = 0;
    }

    iTile = 0;
    cSampleLeft = pau->m_cFrameSampleHalf*pau->m_cCodedChannel;
    while (cSampleLeft > 0)
    {
        //search for tile starting position
        ppcinfo = pau->m_rgpcinfo;
        iStartMin = pau->m_cFrameSampleHalf;
        iSizeMin  = pau->m_cFrameSampleHalf;
        for (iCh=0; iCh < pau->m_cCodedChannel; iCh++)
        {            
            piStart = pau->m_rgiSubframeStart + iCh;
            piSize  = 
                ppcinfo->m_rgsubfrmconfig[ecfConfig].m_rgiSubFrameSize +
                pau->m_rgiCurrSubframe[iCh];
            if (iStartMin > *piStart)
            {
                iStartMin = *piStart;
                iSizeMin  = *piSize;
            }
            ppcinfo++;
        }

        cChInTile = 0;
        ppcinfo   = pau->m_rgpcinfo;
        uChannelMask = 0;
        for (iCh=0; iCh < pau->m_cCodedChannel; iCh++)
        {
            psubfrmconfig = ppcinfo->m_rgsubfrmconfig + ecfConfig;
            piSize        = psubfrmconfig->m_rgiSubFrameSize;
            piStart       = pau->m_rgiSubframeStart + iCh;
            piSubFrmCurr  = pau->m_rgiCurrSubframe + iCh;

            //possibly a ch in tile
            if (iStartMin == *piStart)
            {
                if (iSizeMin == piSize[*piSubFrmCurr])
                {
                    iSubframeTile = *piSubFrmCurr;
                    psubfrmconfigTile = psubfrmconfig;
                    uChannelMask |= (1<<iCh);
                    cSampleLeft -= piSize[*piSubFrmCurr];
                    *piStart += piSize[*piSubFrmCurr];
                    (*piSubFrmCurr)++;
                    cChInTile++;
                }
            }
            ppcinfo++;
        }

        pau->m_rgtci[iTile].m_psfci = psubfrmconfigTile;
        pau->m_rgtci[iTile].m_iSubFrame = iSubframeTile;
        pau->m_rgtci[iTile].m_iSubFrameSize = iSizeMin;
        pau->m_rgtci[iTile].m_iSubFrameStart = iStartMin;
        pau->m_rgtci[iTile].m_cChannels = cChInTile;
        pau->m_rgtci[iTile].m_uChannelMask = uChannelMask;

        iTile++;
    }

    pau->m_cTiles = iTile;
}

//*****************************************************************************************
//
// auAdaptToSubFrameConfig
// setup paramters for handling and transisting between varying size subframes
//
//*****************************************************************************************
WMARESULT auAdaptToSubFrameConfig (CAudioObject* pau)
{
    I16 i, iTotal, iSizeCurr, iCh, iIncr;
    WMARESULT   wmaResult = WMA_OK;

#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,ADAPT_TO_SUB_FRAME_CONFIG_PROFILE);
#endif

    if (pau->m_bPureLosslessMode == WMAB_TRUE) 
    {
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
            SubFrameConfigInfo* psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
            assert (psubfrmconfigCurr->m_cSubFrame <= 16);
            ppcinfo->m_iSizeCurr = iSizeCurr = (I16) psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame];
            ppcinfo->m_cSubFrameSampleHalf   = iSizeCurr;
            // Next two function can be removed since in lossless mode, there is no adjusted values needed.
            // prvSetAdjustedValues(pau);
            // prvSetAdjustedValuesPC(pau, ppcinfo);
        }
    }
    else if (pau->m_bPureLosslessMode == WMAB_FALSE) 
    {
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
            SubFrameConfigInfo* psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);

            assert (psubfrmconfigCurr->m_cSubFrame <= 16);

            ppcinfo->m_iSizeCurr = iSizeCurr = (I16) psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame];
            //to decide the current window shape; look at sizes on the left and right
            ppcinfo->m_iSizePrev = (I16) psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame - 1];
            ppcinfo->m_iSizeNext = (I16) psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame + 1];

            if (psubfrmconfigCurr->m_cSubFrame > 1) 
            {
                iIncr = (I16) LOG2 ((U32)(pau->m_cFrameSampleHalf / iSizeCurr));
                if (iIncr >= pau->m_cPossibleWinSize)
                {
                    REPORT_BITSTREAM_CORRUPTION();
                    wmaResult = TraceResult(WMA_E_BROKEN_FRAME);
                    goto exit;
                }
                i = 0;
                iTotal = 0;
                while (i < iIncr) 
                {
                    iTotal += (I16) (pau->m_cFrameSampleQuad >> i);
                    i++;
                }

                pau->m_cValidBarkBand = pau->m_rgcValidBarkBand [iIncr];
                pau->m_rgiBarkIndex   = pau->m_rgiBarkIndexOrig + iIncr * (NUM_BARK_BAND + 1);
                pau->m_cSubWooferCutOffIndex = pau->m_rgcSubWooferCutOffIndex [iIncr];
            }
            else 
            {
                iIncr = 0;
                pau->m_cValidBarkBand       = pau->m_rgcValidBarkBand [0];
                pau->m_rgiBarkIndex         = pau->m_rgiBarkIndexOrig;
                pau->m_cSubWooferCutOffIndex = pau->m_rgcSubWooferCutOffIndex [0];
            }
            pau->m_cLowCutOff  = iSizeCurr * pau->m_cLowCutOffLong / pau->m_cFrameSampleHalf;    //proportional
            pau->m_cHighCutOff = iSizeCurr * pau->m_cHighCutOffLong / pau->m_cFrameSampleHalf;    //proportional

            ppcinfo->m_cSubFrameSampleHalf   = iSizeCurr;

            //init; could be modified by noise sub
            ppcinfo->m_cSubbandActual = pau->m_cHighCutOff - pau->m_cLowCutOff;

    #ifdef ENABLE_ALL_ENCOPT
            //update first noise index
            if (pau->m_fNoiseSub == WMAB_TRUE)    
            {
                pau->m_iFirstNoiseIndex = (Int) (0.5F + pau->m_fltFirstNoiseFreq * ppcinfo->m_cSubFrameSampleHalf * 2 
                    / ((Float) pau->m_iSamplingRate));  //open end

                if (pau->m_iFirstNoiseIndex > ppcinfo->m_cSubband) 
                    pau->m_iFirstNoiseIndex = ppcinfo->m_cSubband;

                // use precalculated values
                pau->m_iFirstNoiseBand = pau->m_rgiFirstNoiseBand[iIncr];
            }
    #endif //ENABLE_ALL_ENCOPT

            prvSetAdjustedValuesPC(pau, ppcinfo);
            if (iCh==0) prvSetAdjustedValues(pau, ppcinfo->m_cSubbandAdjusted);

            prvCalcQ1Q2(pau, WMAB_TRUE, ppcinfo->m_iSizePrev, ppcinfo->m_iSizeCurr, &ppcinfo->m_iCoefRecurQ1,
                &ppcinfo->m_iCoefRecurQ2);

            prvCalcQ3Q4(pau, WMAB_TRUE, ppcinfo->m_iSizeCurr, ppcinfo->m_iSizeNext,
                ppcinfo->m_cSubFrameSampleHalfAdjusted, &ppcinfo->m_iCoefRecurQ3,
                &ppcinfo->m_iCoefRecurQ4);

#if defined(BUILD_WMAPROLBRV2)


#if (CX_DECODE_MONO==1)

            // under CX_DECODE_MONO, m_rgiCoefReconOrig is
            // only allocated for one channel. So, we need
            // to avoid accessing un-allocated buffers.

            if ( !pau->m_bCx || pau->m_bEncoder || iChSrc < pau->m_pcx->m_iMaxPairs )
#endif
            if (WMAB_TRUE == pau->m_bReconProc)
            {
                if (0 == pau->m_iCurrTile)
                    TRACEWMA_EXIT(wmaResult, chexShiftBuf(pau, (Int)iChSrc));
                ppcinfo->m_rgCoefRecon =
                    ppcinfo->m_rgCoefReconBase +
                    pau->m_prp->m_iPCMPrevFrameSave +
                    ppcinfo->m_iCurrCoefPosition;
                assert(ppcinfo->m_iCurrCoefPosition + ppcinfo->m_iSizeCurr +
                       pau->m_prp->m_iPCMPrevFrameSave
                       <= pau->m_iCoefBufSize);
                ppcinfo->m_iCurrCoefPosition +=
                    (I16)ppcinfo->m_cSubFrameSampleHalfAdjusted;
                ppcinfo->m_rgiCoefRecon = (CBT*)ppcinfo->m_rgCoefRecon;
            }
#endif // defined(BUILD_WMAPROLBRV2)

            ppcinfo++;
        }
        prvAdaptTrigToSubframeConfig(pau);
    }
exit:
#ifdef WMAPROFILE
    //FunctionProfileStop(&fp);
#endif

    return wmaResult;
}



//*****************************************************************************************
//
// VERIFY_DECODED_COEFFICENT
//
// define VERIFY_DECODED_COEFS and set fltCoefIntFloatThreshold
//
//*****************************************************************************************
//#define VERIFY_DECODED_COEFS
#if defined(_DEBUG) && defined(VERIFY_DECODED_COEFS)
#   pragma COMPILER_MESSAGE(__FILE__ "(1235) : Warning - Decode Coef HighRate Debug Code Enabled.")
// define threshold ((it can be changed from debugger))
static Float fltCoefIntFloatThreshold = 0.00075F;
static void VerifyDecodedCoefficentHR(CAudioObject* pau, PerChannelInfo* ppcinfo, 
                                      Int iBark, CoefType iRecon, I16 iLevel,
                                      CoefType ctCoefRecon) {
    Float ff, f3, dif, rel, fltRecon;
    static Float fltReconMin = 1.0e30F;
    static Float fltReconMax = -1;
    Double dblQuantStep = DOUBLE_FROM_QUANTSTEPTYPE(pau->m_qstQuantStep);
    Float fltWeightFactor = ((float)ppcinfo->m_rgiWeightFactor[iBark])  / (1<<WEIGHTFACTOR_FRACT_BITS);     // divide by 1024.
    Float fltInvMaxWeight = 1.0F / ((float)ppcinfo->m_iMaxWeight / (1<<WEIGHTFACTOR_FRACT_BITS));           // didive by 1024.
    fltRecon = FLOAT_FROM_COEF(ctCoefRecon);                                                                // divide by 32.
    // This is the statement in float.c we are to match
    // rgfltCoefRecon [iRecon] = ((Float) rgiCoefQ [iCoefQ]) * rgfltWeightFactor [iBark] * ((Float) dblQuantStep) * fltInvMaxWeight;
    ff = fltWeightFactor * ((Float) dblQuantStep) * fltInvMaxWeight;
    f3 = ((Float) iLevel) * ff;
    dif = (float) fabs(f3 - fltRecon);  
    rel = (float) fabs(dif/f3); 
    // was ((iRecon < pau->m_cHighCutOff) && (dif > 2) && rel > 0.2)
    // fltRecon seems to range from 1e7 down to about 1.0, small values seem to be less accurate
    // consider using the same comparison as used with MidRate (See LowRate.c)
   if ( rel > (f3 > 100 ? fltCoefIntFloatThreshold : (fltCoefIntFloatThreshold*100/f3)) )   
        DEBUG_BREAK();
}
#endif

// looks like an encoder function, but is needed by decoder.
void SetActualPower(const I32 *piCoefQ, const Int iCount,
                    PerChannelInfo *ppcinfo, const Status codecStatus)
{
    Int i;

    ppcinfo->m_iActualPower = 0;
    if (CODEC_BEGIN != codecStatus || 0 == ppcinfo->m_iPower || NULL == piCoefQ)
        return;

    for (i = 0; i < iCount; i++)
    {
        if (0 != piCoefQ[i])
        {
            ppcinfo->m_iActualPower = 1;
            break;
        }
    }
}

// looks like an encoder function, but is needed by decoder.
void SetActualPowerHighRate(const CBT *piCoefRecon, const int iCount,
                            PerChannelInfo *ppcinfo, const Status codecStatus)
{
    int i;

    ppcinfo->m_iActualPower = 0;
    if (CODEC_BEGIN != codecStatus || 0 == ppcinfo->m_iPower || NULL == piCoefRecon)
        return;

    for (i = 0; i < iCount; i++)
    {
        if (0 != piCoefRecon[i])
        {
            ppcinfo->m_iActualPower = 1;
            break;
        }
    }
}


//***************************************************************************
// 24-bit Encoding
//***************************************************************************

PCMSAMPLE prvGetSample(const PCMSAMPLE *pCurrentPos,
                       const Int nBytePerSample,
                       const Int nValidBitsPerSample,
                       const Int iOffset)
{
    PCMSAMPLE   iResult = 0;
    U8 *pbSrc = (U8*) pCurrentPos;
    U8 *pbDst = (U8*) &iResult;
    const Int iBytesPerSample = nBytePerSample;
    const Int iSignbits = BITS_PER_BYTE * (sizeof(PCMSAMPLE) - iBytesPerSample);
    const Int iPadBits = (8 * nBytePerSample) - nValidBitsPerSample;
    Int i;

    assert(iBytesPerSample <= sizeof(PCMSAMPLE));

    // Read the sample in one byte at a time. Slow but easy to implement. We'll fix later.
    pbSrc += iBytesPerSample * iOffset; // Skip iOffset worth of samples
    for (i = 0; i < iBytesPerSample; i++)
    {
        *pbDst = *pbSrc;

        // Advance pointers
        pbSrc += 1;
        pbDst += 1;
    }

    //assert(0 == (iResult & ((1 << iPadBits) - 1))); // Verify that pad bits are zero

    // Extend sign bits
#ifndef _BIG_ENDIAN_
    iResult <<= iSignbits;
#endif
    iResult >>= (iSignbits + iPadBits); // Dump LSB's (should all be zero)

    return iResult;
} // prvGetSample

WMARESULT auReconSample(CAudioObject* pau, PCMSAMPLE* piOutput, U16 cSamples)
{
    WMARESULT hr = WMA_OK;
    I16 i, iCh;
    Int offset;
    CoefType cfPCMData;
    const CoefType *pcfPCMBuf;
    PCMSAMPLE   iPCMData;
    const Int cChannel = pau->m_cChannel;
    
    for( iCh = 0; iCh < cChannel; iCh++ )
    {
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;
        pcfPCMBuf = (CoefType *)ppcinfo->m_rgiPCMBuffer;
        offset = iCh;

 //       WMADebugMessage(" pcfPCMBuf: %d,  %d,  %d,  %d\n", pcfPCMBuf[0], pcfPCMBuf[1], pcfPCMBuf[2], pcfPCMBuf[3] );
 //       WMADebugMessage("auReconSample (%d, %d) %d -> ", PCMSAMPLE_MIN(pau->m_nValidBitsPerSample), PCMSAMPLE_MAX(pau->m_nValidBitsPerSample), pcfPCMBuf[0]);
        for( i = 0; i < cSamples; i++ )
        {
            cfPCMData = pcfPCMBuf[i];

#if defined(BUILD_INTEGER) && defined(COEF64BIT)
            ROUND_AND_CHECK_RANGE( iPCMData, (PCMSAMPLE)cfPCMData,
                                   PCMSAMPLE_MIN(pau->m_nValidBitsPerSample),
                                   PCMSAMPLE_MAX(pau->m_nValidBitsPerSample) );
#else
            ROUND_AND_CHECK_RANGE( iPCMData, cfPCMData,
                                   PCMSAMPLE_MIN(pau->m_nValidBitsPerSample),
                                   PCMSAMPLE_MAX(pau->m_nValidBitsPerSample) );
//            if (i == 0) {
//                WMADebugMessage(" iPCMData %d, cfPCMData %d\n", iPCMData, cfPCMData);
//                }
#endif

//            pau->m_pfnSetSample(iPCMData, piOutput, pau, offset);         // doesn't work
            ((U16*)piOutput)[offset] = iPCMData;                            // temp replace with this - ToDo 

            offset += cChannel;
        }
   //     WMADebugMessage(" piOutput: %lld,  %lld,  %lld,  %lld\n", piOutput[0], piOutput[1], piOutput[2], piOutput[3] );
    }

    return hr;
} // auReconSample

#if defined (BUILD_INTEGER)
WMARESULT auReconSampleFloat(CAudioObject* pau, PCMSAMPLE* piOutput, U16 cSamples)
{
    assert(0);
    return WMA_E_FAIL;
}
#else
WMARESULT auReconSampleFloat(CAudioObject* pau, PCMSAMPLE* piOutput, U16 cSamples)
{
    WMARESULT hr = WMA_OK;
    Float fltScale = 1.0F/(1 << (pau->m_nValidBitsPerSample-1));
    I16 i, iCh;
    Int offset;
    CoefType cfPCMData, *pcfPCMBuf;
    Float *pfltOutput = (Float*) piOutput;
    
    offset = 0;
    for( i = 0; i < cSamples; i++ )
    {
        
        for( iCh = 0; iCh < pau->m_cChannel; iCh++ )
        {

            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;

            pcfPCMBuf = (CoefType *)ppcinfo->m_rgiPCMBuffer;

            cfPCMData = pcfPCMBuf[i];

#if 0
            // Scale so that output is nominally between +1 to -1.
            cfPCMData /= (1 << (pau->m_nValidBitsPerSample-1));

            prvSetFloatSampleFloatBuf(cfPCMData, piOutput, pau, offset);
#else
            cfPCMData *= fltScale;
            pfltOutput[offset] = cfPCMData;
#endif
            offset++;
        }
    }

    return hr;
} // auReconSampleFloat
#endif // BUILD_INTEGER

PCMSAMPLE prvGetSample16(const PCMSAMPLE *pCurrentPos,
                         const Int nBytePerSample,
                         const Int nValidBitsPerSample,
                         const Int iOffset)
{
    U8 *pbSrc = (U8*) pCurrentPos;

    pbSrc += 2 * iOffset; // Skip iOffset worth of samples
    return *((I16*)pbSrc);
} // prvGetSample16
 

#if !( defined(WMA_TARGET_MIPS) && defined(PLATFORM_SPECIFIC_GETSAMPLE) )
PCMSAMPLE prvGetSample24(const PCMSAMPLE *pCurrentPos,
                         const Int nBytePerSample,
                         const Int nValidBitsPerSample,
                         const Int iOffset)
{
    U8 *pbSrc = (U8*) pCurrentPos;
    I32 iResult;

    pbSrc += 3 * iOffset; // Skip iOffset worth of samples
#if defined (_BIG_ENDIAN_)
    iResult = (*(I32*)pbSrc) >> 8;
#elif defined (UNDER_CE)
    iResult = (*((U8*)pbSrc) | (*((U8*)(pbSrc + 1)) << 8) | (*((I8*)(pbSrc + 2)) << 16));
#else
    iResult = (*((U16*)pbSrc) | (*((I8*)(pbSrc + 2)) << 16));
#endif

    return iResult;
} // prvGetSample24
#endif


PCMSAMPLE prvGetSample2024(const PCMSAMPLE *pCurrentPos,
                           const Int nBytePerSample,
                           const Int nValidBitsPerSample,
                           const Int iOffset)
{
    U8 *pbSrc = (U8*) pCurrentPos;
    I32 iResult;

    pbSrc += 3 * iOffset; // Skip iOffset worth of samples
    iResult = (*((U16*)pbSrc) | (*((I8*)(pbSrc + 2)) << 16));

    // This assert fired when encoding content with a bit depth of 24 to 20-bits
    // In such cases we will always throw away the 4 least significant bits as is 
    // done in prvGetSample
    // assert(0 == (iResult & 0x0F)); // Verify that 4 least signficant bits always zero

    iResult >>= 4; // Dump the 4 least-significant bits (should always be zero)
    return iResult;
} // prvGetSample2024



void prvSetSample(const PCMSAMPLE iValue,
                  PCMSAMPLE *pCurrentPos,
                  const CAudioObject *pau,
                  const Int iOffset)
{
    PCMSAMPLE iNewValue;
    U8 *pbDst = (U8*) pCurrentPos;
    U8 *pbSrc = (U8*) &iNewValue;
    Int i;
    
    const Int iBytesPerSample = pau->m_nBytePerSample;
    const Int iPadBits = pau->m_nBitsPerSample - pau->m_nValidBitsPerSample;

#ifdef _BIG_ENDIAN_
    assert(pau->m_nBytePerSample == 2); //only support 16bits sample size for Mac
    pbSrc += 2;
#endif

    // We used to check if new value fit in valid bits: don't, because auSaveHistory
    // can feed us values > valid bits. Expectation is that we truncate to valid bits.

    // Pad to fit within container, MSB-justified (LSB's are zero)
    iNewValue = (iValue << iPadBits);

    // Write the sample one byte at a time. Slow but easy to implement. We'll fix later.
    pbDst += iBytesPerSample * iOffset; // Skip iOffset worth of samples
    for (i = 0; i < iBytesPerSample; i++)
    {
        *pbDst = *pbSrc;

        // Advance pointers
        pbSrc += 1;
        pbDst += 1;
    }
} // prvSetSample

void prvSetSample16(const PCMSAMPLE iValue,
                    PCMSAMPLE *pCurrentPos,
                    const CAudioObject *pau,
                    const Int iOffset)
{
    U8 *pbDst = (U8*) pCurrentPos;
    U8 *pbSrc = (U8*) &iValue;

    pbDst += 2 * iOffset; // Skip iOffset worth of samples
#ifdef _BIG_ENDIAN_
    //assert(pau->m_nBytePerSample == 2); //only support 16bits sample size for Mac

#    ifdef EARLIER_SWITCH
    *((I8*)(pbDst)) = *((I8*)(pbSrc + 3));
    *((I8*)(pbDst + 1)) = *((I8*)(pbSrc + 2));
#    else
    *((I16*)pbDst) = (I16)iValue;  
#    endif // #ifdef EARLIER_SWITCH
#else
    *((I16*)pbDst) = *((I16*)pbSrc);
#endif // #ifdef _BIG_ENDIAN_
} // prvSetSample16


void prvSetSample24(const PCMSAMPLE iValue,
                    PCMSAMPLE *pCurrentPos,
                    const CAudioObject *pau,
                    const Int iOffset)
{
    U8 *pbDst = (U8*) pCurrentPos;
    U8 *pbSrc = (U8*) &iValue;

    pbDst += 3 * iOffset; // Skip iOffset worth of samples
#if defined (_BIG_ENDIAN_)
    {
        PCMSAMPLE iTemp = iValue;

        *((I8*)(pbDst + 2)) = (I8)iTemp;
        iTemp >>= 8;
        *((I8*)(pbDst + 1)) = (I8)iTemp;
        iTemp >>= 8;
        *((I8*)pbDst) = (I8)iTemp;
    }
#elif defined (UNDER_CE)
    *((I8*)pbDst) = *((I8*)pbSrc);
    *((I8*)(pbDst + 1)) = *((I8*)(pbSrc + 1));
    *((I8*)(pbDst + 2)) = *((I8*)(pbSrc + 2));
#else
    *((I16*)pbDst) = *((I16*)pbSrc);
    *((I8*)(pbDst + 2)) = *((I8*)(pbSrc + 2));
#endif
} // prvSetSample24



void prvSetSample2024(const PCMSAMPLE iValue,
                      PCMSAMPLE *pCurrentPos,
                      const CAudioObject *pau,
                      const Int iOffset)
{
    I32 iNewValue;
    U8 *pbDst = (U8*) pCurrentPos;
    U8 *pbSrc = (U8*) &iNewValue;

    // We used to check if incoming value was < 20-bit: don't, because auSaveHistory
    // can feed us values > 20-bit. Expectation is that we truncate to 20 bits.
    iNewValue = (iValue << 4);

    pbDst += 3 * iOffset; // Skip iOffset worth of samples
    *((I16*)pbDst) = *((I16*)pbSrc);
    *((I8*)(pbDst + 2)) = *((I8*)(pbSrc + 2));
} // prvSetSample2024



Int prvCountSamples(const PCMSAMPLE *pCurrentPos,
                    const PCMSAMPLE *pBasePos,
                    const CAudioObject *pau,
                    const Int iChannels)
{
    Int iTotalSamples;

    iTotalSamples = (Int) ((U8*) pCurrentPos - (U8*) pBasePos);
    assert(0 == (iTotalSamples % pau->m_nBytePerSample));
    iTotalSamples /= pau->m_nBytePerSample;

    assert(0 != iChannels);
    assert(0 == iTotalSamples % iChannels);
    return iTotalSamples / iChannels;
} // prvCountSamples

//******************************************************************
//
//  Stub functions that are not needed for specialized builds
//
//******************************************************************

#if !defined (BUILD_WMAPRO)
I32 prvNextSeekPoint(const CAudioObject *pau)
{
    return 0;
}
WMARESULT prvLLMVerBResetAllCom_MLLM(CAudioObject * pau, PerChannelInfo * ppcInfoComms)
{
    return WMA_OK;
}
I32 prvContinuousDecodeAdjustment(const CAudioObject *pau)
{
    return 0;
}
WMARESULT prvMultiXIDCTAllocate(CAudioObject *pau)
{
    return WMA_OK;
}
WMARESULT prvMultiXIDCTInit(CAudioObject *pau)
{
    return WMA_OK;
}
Void prvMultiXIDCTDelete  (CAudioObject *pau)
{
}
Void prvSetSubWooferCutOffs (CAudioObject* pau)
{
}
Void prvGetChannelNumAtSpeakerPosition (U32 nChannelMask,
                                        U32 nSpeakerPosition,
                                        I16 *pnChannelNum)
{
}
WMARESULT prvAllocChannelGrpInfo(CChannelGroupInfo **prgChannelGrpInfo, 
                                 Int cChannel)
{
    return WMA_OK;
}
Void prvDeleteChannelGrpInfo(CChannelGroupInfo **prgChannelGrpInfo, 
                             Int cChannel)
{
    return;
}
QuantStepType qstCalcQuantStepModifier(Int iQSS,
                                       Int cLeftShiftBitsQuant) 
{
    return FFLT_ONE;
}
WMARESULT auGetTransformFromGivensFactors(I8* rgbRotationAngle, 
                                          I8* rgbRotationSign, 
                                          Int cSize, 
                                          Int cMaxChannel,  // only for security
                                          ChXFormType* rgfltMultiXInverse,
                                          ChXFormType* rgfltTmpCurr,
                                          ChXFormType* rgfltTmpFinal)
{
    return WMA_OK;
}
WMARESULT auInvWeightSpectrumV3 (CAudioObject* pau, 
                                 PerChannelInfo* ppcinfo,
                                 U8 fMaskUpdate)
{
    return WMA_OK;
}
WMARESULT auPreScaleCoeffsV3(CAudioObject *pau,
                             CoefType iLog2MaxOutputAllowed,
                             Bool fUseQuantStep,
                             Bool fUseGlobalScale, char c )
{
    return WMA_OK;
}
WMARESULT auPreScaleQuantV3(CAudioObject *pau,
                            Bool fUseGlobalQuantScale)
{
    return WMA_OK;
}
WMARESULT auPostScaleCoeffsV3(CAudioObject *pau)
{
    return WMA_OK;
}
WMARESULT prvAllocateBarkResampleMatrix(CAudioObject* pau)
{
    return WMA_OK;
}
Void prvDeleteBarkResampleMatrix(CAudioObject* pau)
{
}
Void auInitBarkResampleMatrix (CAudioObject* pau)
{
}


WMARESULT auOverlapAddV3(CAudioObject *pau,
                         CoefType *pctCoefOut,
                         CoefType *pctCoefHist,
                         CoefType *pctCoefNew,
                         CoefType *pctCoefHistDST,
                         CoefType *pctCoefNewDST,
                         Int iSizePrev, Int iSizeCurr,
                         Bool bUseDCT,
                         Bool bUseMCLT,
                         Bool bFlip,
                         Bool fBase)
{
    return WMA_OK;
}

Void auApplyReflectionV3(CoefType *pctCoef,
                         Int iSizeCurr)
{
}

#endif // !BUILD_WMAPRO

#if !defined (BUILD_WMASTD) && !defined (BUILD_WMAPRO)
// stub functions; actual implementations needed only for 
// WMA PRO & WMA Std, but not for WMA Lossless.
QuantStepType qstCalcQuantStep(const Int iQSS, const Int cLeftShiftBits) 
{
    return FFLT_ONE;
}
Void prvInitDiscardSilence(CAudioObject *pau, Bool fSPDIF)
{
}
Void prvSetBarkIndex (CAudioObject* pau)
{
}
WMARESULT auInvChannelXForm (CAudioObject *pau,
                             Bool fInvertSuperGroupXform)
{
    return WMA_OK;
}
WMARESULT auSubframeRecon ( CAudioObject* pau )
{
    return WMA_OK;
}
Void prvCalcQ3Q4(CAudioObject *pau, Bool bCurrWindow, const I16 iSizeCurr, const I16 iSizeNext,
                 const Int cSubFrameSampleHalfAdjusted,
                 I16 *piCoefRecurQ3, I16 *piCoefRecurQ4)
{
}
Void prvCalcQ1Q2(CAudioObject * pau, Bool bCurrWindow,
                 const I16 iSizePrev, const I16 iSizeCurr,
                 I16 *piCoefRecurQ1, I16 *piCoefRecurQ2)
{
}
WMARESULT prvAdaptTrigToSubframeConfig(CAudioObject *pau)
{
    return WMA_OK;
}
Void    auUpdateMaxEsc(CAudioObject* pau, Int iQuantStepSize)
{
}
Void auApplyWindow(CAudioObject *pau, CoefType *pctCoef,
                   Int iSizePrev, Int iSizeCurr, Int iSizeNext, Bool fBase)
{
}
#endif // !BUILD_WMASTD && !BUILD_WMAPRO

#if !defined (BUILD_WMALSL)
// stub functions; actual implementations needed only for WMA Lossless
WMARESULT auReconstructPureLLM (CAudioObject* pau, U8** ppbDst,
                                I16* pcSampleGet, Bool fForceTransformAll)
{
    return WMA_OK;
}
#endif // !BUILD_WMALSL

#if defined(_SH4_)
#    pragma warning(pop)
#endif // #if defined(_SH4_)

#ifdef WMA_COMPRESSION_TOOL
// TODO: This bit move is just an very lazy solution. It should be rewritten.
I32 prvBitsMove (U8 *pbSrc, I32 cbSrc, I32 iSrcStart, I32 iSrcEnd, U8 * pbDst, I32 cbDst, I32 iDstStart)
{
    I32 cBitsToMove = iSrcEnd - iSrcStart;
    // We need one more byte because prvBitsCopy may access one more extra byte
    // when it is trying to copy the last iDstLastTailBits bits.
    // CTODO: we should fix prbBitsCopy to avoid this problem.
    I32 cbTmp = iSrcEnd / 8 + 2;
    I32 iDstCurr;
    U8 * pbTmp = NULL;


    pbTmp = (U8*) auMalloc(cbTmp);
    assert(pbTmp != NULL);
    if (NULL == pbTmp)
    {
        return -1;
    }

    prvBitsCopy(pbSrc, cbSrc, iSrcStart, iSrcEnd, pbTmp, cbTmp, 0);
    iDstCurr = prvBitsCopy(pbTmp, cbTmp, 0, cBitsToMove, pbDst, cbDst, iDstStart);
    auFree(pbTmp);
    return iDstCurr;
} // prvBitsMove

I32 prvBitsCopy (U8 *pbSrc, I32 cbSrc, I32 iSrcStart, I32 iSrcEnd, U8 * pbDst, I32 cbDst, I32 iDstStart)
{
    I32 iSrcCurr = iSrcStart;
    I32 iSrcByteStart = iSrcStart / 8;
    I32 iSrcByteCurr = iSrcByteStart;
    I32 iSrcFractionalBits = iSrcStart % 8;
    I32 iSrcLeadingBits = (8 - iSrcFractionalBits);

    I32 iDstCurr = iDstStart;
    I32 iDstByteStart = iDstCurr / 8;
    I32 iDstByteCurr = iDstByteStart;
    I32 iDstByteEnd = (iDstCurr + iSrcEnd - iSrcStart) / 8;
    I32 iDstFractionalBits = iDstCurr % 8;
    I32 iDstLeadingBits = (8 - iDstFractionalBits);

    I32 iDstLastTailBits = (iDstCurr + iSrcEnd - iSrcStart) % 8;

    U16 iTemp;

    assert(iSrcEnd >= iSrcStart);
    assert(iDstCurr + (iSrcEnd - iSrcStart) <= cbDst * 8);
    // Mem can not overlapped.
    assert(pbSrc + cbSrc < pbDst || pbDst + cbDst < pbSrc);
    assert(iSrcEnd <= cbSrc * 8);

    if (iSrcEnd == iSrcStart)
        return iDstCurr;

    // if only one byte in pbDst need to be changed.
    if (iDstLeadingBits >= iSrcEnd - iSrcStart)
    {
        if (iDstLastTailBits == 0)
        {
            iDstLastTailBits = 8;
        }
        iTemp = (pbSrc[iSrcByteCurr] << 8) + pbSrc[iSrcByteCurr + 1];
        iTemp = ((U16)(iTemp << iSrcFractionalBits)) >> (iDstFractionalBits + 8);
        iTemp = (iTemp >> (8 - iDstLastTailBits)) << (8 - iDstLastTailBits);
        pbDst[iDstByteCurr] = (((U8)(pbDst[iDstByteCurr] >> iDstLeadingBits)) << iDstLeadingBits)
            | (((U8)(pbDst[iDstByteCurr] << iDstLastTailBits)) >> iDstLastTailBits)
            | iTemp;
        iDstCurr += (iSrcEnd - iSrcStart);
        return iDstCurr;
    }

    // Copy the first iDstLeadingBits bits.
    if (iDstFractionalBits > 0)
    {
        iTemp = (pbSrc[iSrcByteCurr] << 8) + pbSrc[iSrcByteCurr + 1];
        iTemp = ((U16)(iTemp << iSrcFractionalBits)) >> (iDstFractionalBits + 8);

        pbDst[iDstByteCurr] = (U8)iTemp | ((pbDst[iDstByteCurr] >> iDstLeadingBits) << iDstLeadingBits);

        iDstCurr += iDstLeadingBits; // optional
        iSrcCurr += iDstLeadingBits; // optional

        iDstByteCurr = iDstCurr / 8;
        iDstFractionalBits = iDstCurr % 8; 
        assert(iDstFractionalBits == 0);
        iDstLeadingBits = 8 - iDstFractionalBits;

        iSrcByteCurr = iSrcCurr / 8;
        iSrcFractionalBits = iSrcCurr % 8;
        iSrcLeadingBits = 8 - iSrcFractionalBits;            
    }

    // Now iDstCurr are byte aligned. Copy one byte per time.
    while (iDstByteCurr < iDstByteEnd)
    {
        pbDst[iDstByteCurr] = (pbSrc[iSrcByteCurr] << iSrcFractionalBits) 
            | (pbSrc[iSrcByteCurr + 1] >> iSrcLeadingBits);
        iDstByteCurr++;
        iSrcByteCurr++;
        iDstCurr += 8; // optional
        iSrcCurr += 8; // optional 
    }


    if (iDstLastTailBits)
    {
        // copy the last iDstLastTailBits bits.
        assert (iSrcByteCurr < cbSrc);
        if (iSrcByteCurr < cbSrc - 1)
            iTemp = (pbSrc[iSrcByteCurr] << 8) + pbSrc[iSrcByteCurr + 1];
        else
            iTemp = (pbSrc[iSrcByteCurr] << 8);
        iTemp = (iTemp << iSrcFractionalBits) >> 8;
        iTemp = (iTemp >> (8 - iDstLastTailBits)) << (8 - iDstLastTailBits);
        pbDst[iDstByteCurr] = ((U8)(pbDst[iDstByteCurr] << iDstLastTailBits)) >> iDstLastTailBits;
        pbDst[iDstByteCurr] = pbDst[iDstByteCurr] | (U8) iTemp;
        iSrcCurr += iDstLastTailBits; // optional
        iDstCurr += iDstLastTailBits; // optional
        assert(iSrcCurr == iSrcEnd);
        assert((iDstStart + iSrcEnd - iSrcStart) == iDstCurr);
    }
    return iDstCurr;
} // prvBitsCopy

// Get PCM frame number. Map the pau->m_iFrameNumber to PCM frame number.
// v2/v3/decoder/encoder have different iFrameNumber counting. In order
// to have a unified frame count, we map them to iPCMFrameNumber.
// A windowed frame covers two PCM frames (prev and curr).
I32 prvGetPCMFrameNumber (I32 iWinFrameNumber, Bool fEncoder, I32 iVersion)
{
    I32 iPCMFrameNumber;

    if (fEncoder == WMAB_TRUE)
    {   // called by encoder
        iPCMFrameNumber = iWinFrameNumber - 2;
    }
    else
    {   // called by decoder
        if (iVersion >= 3)
            iPCMFrameNumber = (I32)iWinFrameNumber - 1;
        else
            iPCMFrameNumber = (I32)iWinFrameNumber - 2;
    }
    assert(iPCMFrameNumber >= -1); 
    return iPCMFrameNumber;
} // prvGetPCMFrameNumber

#endif //WMA_COMPRESSION_TOOL

#if defined (BUILD_INTEGER)
void prvSetPCMSampleFloatBuf(const PCMSAMPLE iValue,
                             PCMSAMPLE *pCurrentPos,
                             const CAudioObject *pau,
                             const Int iOffset)
{
}
#else
void prvSetPCMSampleFloatBuf(const PCMSAMPLE iValue,
                             PCMSAMPLE *pCurrentPos,
                             const CAudioObject *pau,
                             const Int iOffset)
{
    Float *pfltDst = ((Float*) pCurrentPos) + iOffset;

    // Scale so that float buffer is nominally between 1.0 & -1.0.
    *pfltDst = ((Float)iValue)/(1 << (pau->m_nValidBitsPerSample-1));
} // prvSetPCMSampleFloatBuf
#endif // BUILD_INTEGER

#if defined (BUILD_INTEGER)
PCMSAMPLE prvGetPCMSampleFloatBuf(const PCMSAMPLE *pCurrentPos,
                                  const Int nBytePerSample,
                                  const Int nValidBitsPerSample,
                                  const Int iOffset)
{
    return 0;
}
#else
PCMSAMPLE prvGetPCMSampleFloatBuf(const PCMSAMPLE *pCurrentPos,
                                  const Int nBytePerSample,
                                  const Int nValidBitsPerSample,
                                  const Int iOffset)
{
    // nBytePerSample is not used
    PCMSAMPLE iPCMData = 0;

    Float fltValue = (Float)*(((Float*) pCurrentPos) + iOffset);
    // Scale the +1 to -1 float data to PCMSAMPLE.
    fltValue *= (1 << (nValidBitsPerSample-1));
    ROUND_AND_CHECK_RANGE( iPCMData, fltValue,
        PCMSAMPLE_MIN(nValidBitsPerSample),
        PCMSAMPLE_MAX(nValidBitsPerSample) );
    return iPCMData;
} // prvGetPCMSampleFloatBuf
#endif // BUILD_INTEGER

// ====================================================================

Void auIntFromCoeff(CAudioObject *pau, CoefType *pctCoeff, Int iSize)
{
#ifdef BUILD_INTEGER
    Int i;

    for (i=0; i < iSize; i++)
    {
        pctCoeff[i] = INT_FROM_COEF(pctCoeff[i]);
    }
#endif
}

// ====================================================================

WMARESULT prvAllocateNDimArr(U8 ***p, Int nDims, Int *dims, Int *size)
{
    WMARESULT wr = WMA_OK;
    Int i;

    if (nDims <= 0 ||
    (Int)(I32)size[0] != size[0] || 
        (Int)(I32)dims[0] != dims[0] || 
        size[0]*dims[0] != (I64)size[0]*dims[0])
    {
        wr = WMA_E_INVALIDARG;
        goto exit;
    }

    *p = (U8 **)auMalloc(size[0]*dims[0]);
    CHECKWMA_ALLOC(wr, *p);
    memset(*p, 0, size[0]*dims[0]);
    if (nDims != 1)
    {
        for (i=0; i < dims[0]; i++)
        {
            TRACEWMA_EXIT(wr, prvAllocateNDimArr((U8 ***)&(*p)[i], nDims-1, dims+1, size+1));
        }
    }

exit:
    return wr;
}

Void prvDeleteNDimArr(U8 **p, Int nDims, Int *dims)
{
    Int i;

    if (nDims != 1 && NULL!=p)
    {
        for (i=0; i < dims[0]; i++)
        {
            prvDeleteNDimArr((U8 **)p[i], nDims-1, dims+1);
        }
    }
    DELETE_ARRAY(p);
}

Void initSubframeTilingInfo(CAudioObject *pau,
                            Int iChInTile, I16 *rgiChInTile)
{
    Int iStartPtInFrame;
    Int i, iChSrc;
    PerChannelInfo *ppcinfo;
    SubFrameConfigInfo *psubfrmconfig;

    for (i=0; i < iChInTile; i++)
    {
        iChSrc = rgiChInTile[i];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        psubfrmconfig = &ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM];
        iStartPtInFrame = prvGetStartPtInFrame(psubfrmconfig,
                                               ppcinfo->m_iCurrSubFrame);
        
        ppcinfo->m_iStartPtInFile = (pau->m_iFrameNumber-1)*pau->m_cFrameSampleHalf-pau->m_cFrameSampleHalf*3/2 + iStartPtInFrame;
        if (!pau->m_bEncoder)
            ppcinfo->m_iStartPtInFile += pau->m_cFrameSampleHalf;
    }
}

// to prevent integer overflow
Int prvShiftTimeIndex(CAudioObject *pau)
{
    Int iSampleShift = 10000000;

    pau->m_iFrameStart += pau->m_cFrameSampleHalf;

    // determine shift amount
    if (pau->m_iFrameStart <= iSampleShift)
        iSampleShift = 0;

    pau->m_iFrameStart -= iSampleShift;

#if defined(BUILD_WMAPROLBRV2)
    if (pau->m_bReconProc)
        chexShiftPoints(pau, iSampleShift);
#endif

    return iSampleShift;
}

Void prvSetPlusOrder(CAudioObject *pau)
{
    // order is bx, bpx, cx, fx, rfx
    pau->m_bBxIsLast = WMAB_FALSE;
    pau->m_bBPxIsLast = WMAB_FALSE;
    pau->m_bCxIsLast = WMAB_FALSE;
    pau->m_bFxIsLast = WMAB_FALSE;
    pau->m_bRFxIsLast = WMAB_FALSE;

    // if presence bit present for all plus modes, set all "IsLast" to false
    if (pau->m_bCodePresentForAllPlus)
        return;

    if (pau->m_cTiles-1 == pau->m_iCurrTile)
    {
        if (pau->m_bReconFexPresent)
            pau->m_bRFxIsLast = WMAB_TRUE;
        else if (pau->m_bFreqexPresent)
            pau->m_bFxIsLast = WMAB_TRUE;
        else if (pau->m_bCxPresent)
            pau->m_bCxIsLast = WMAB_TRUE;
        else if (pau->m_bBasePeakPresent)
            pau->m_bBPxIsLast = WMAB_TRUE;
        else if (pau->m_fBasePlusPresent)
            pau->m_bBxIsLast = WMAB_TRUE;
    }
    else
    {
        // only bx, bpx, fx
        if (pau->m_bFreqexPresent)
            pau->m_bFxIsLast = WMAB_TRUE;
        else if (pau->m_bBasePeakPresent)
            pau->m_bBPxIsLast = WMAB_TRUE;
        else if (pau->m_fBasePlusPresent)
            pau->m_bBxIsLast = WMAB_TRUE;
    }
}

#ifdef BUILD_INTEGER


#define ISQRT_BITS 8

#define BITS     (30-ISQRT_BITS)
#define LUT_MAX  ((1<<ISQRT_BITS)+1)
#define LUT_MIN  (LUT_MAX>>2)
#define LUT_SIZE (LUT_MAX-LUT_MIN+1)
#define ONE      (1<<28)
#define RND      (1<<(BITS-1))
#define MSK      (~((1<<BITS)-1))

#ifndef UNDER_CE
static 
#endif
U32 g_isqrt_init =  0;

#ifndef UNDER_CE
static 
#endif
U16 g_isqrtLUT[ LUT_SIZE ] = {0};

U32 isqrt( U32 x )
{
    //Int s = 14;

    if( 0 == x )
        return 0;

    if( !g_isqrt_init )
    {
        U32 i;

        for( i = 0; i < LUT_SIZE; ++i )
        {
            const U32 s = isqrt32( ONE + ( i << BITS ) );
            g_isqrtLUT[i] = (U16)( ONE / s );
        }
        g_isqrt_init = 1;
    }

    //while( ONE*4 <= x ){ x >>= 2; s -= 1; }
    //while( ONE    > x ){ x <<= 2; s += 1; }

    assert( ONE*4 > x );
    assert( ONE  <= x );

    {
        // a, b, and c have 2 integer bits.

        const U32 a = (( x - ONE + RND ) & MSK )>>15;
        const U32 b = (x >> 15) + (ONE >> 15) + a;
        const U32 c = g_isqrtLUT[ a>>(BITS-15) ] * b;

        assert(( a>>BITS ) < LUT_SIZE );

        return c;
        //return (U16)( (s<0)? ( c <<-s ) : ( c >> s ) );
    }
}

#endif

#if defined(BUILD_WMAPROLBRV2) && defined(INCLUDE_BASEPLUS)
#include "basepluspro.c"
#endif
