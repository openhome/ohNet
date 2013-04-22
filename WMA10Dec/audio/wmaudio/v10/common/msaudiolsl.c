//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions only needed by WMA Lossless.
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

#if defined (BUILD_WMALSL)

#define RECONMONO_PURELLM(FnName, RSS, RSS_MIN, RSS_MAX, ADVPTR)                            \
void FnName(const CAudioObject *pau, Int *pi, const Int iSegEnd,                            \
            I16 **ppcSampleGet, PCMSAMPLE **ppiDst, CBT **ppiData,                          \
            const Int cChan)                                                                \
                                                                                            \
{                                                                                           \
    Int i = *pi;                                                                            \
    I16 *pcSampleGet = *ppcSampleGet;                                                       \
    PCMSAMPLE *piDst = *ppiDst;                                                             \
    CBT *piData = *ppiData;                                                                 \
    I32 iResult;                                                                            \
    for (; i < iSegEnd; i++,(*pcSampleGet)++)    {                                          \
        iResult = (I32)piData[i];                                                           \
        RSS( piDst, iResult, RSS_MIN, RSS_MAX);                                             \
        piDst = ADVPTR(piDst, pau->m_nBytePerSample, cChan);                                \
    }                                                                                       \
    *pi = i;                                                                                \
    *ppcSampleGet = pcSampleGet;                                                            \
    *ppiDst = piDst;                                                                        \
}

// Instantiate general loop functions
RECONMONO_PURELLM(prvReconMonoPureLLM, ROUND_SATURATE_STORE_LLM,
                PCMSAMPLE_MIN(pau->m_nValidBitsPerSample),
                PCMSAMPLE_MAX(pau->m_nValidBitsPerSample),
                prvAdvancePCMPointer)

// Instantiate 24-bit loop functions
RECONMONO_PURELLM(prvReconMonoPureLLM_I24, ROUND_SATURATE_STORE24_LLM,
                I24_MIN, I24_MAX, prvAdvancePCMPointer24)

// Instantiate 2024-bit loop functions
RECONMONO_PURELLM(prvReconMonoPureLLM_I2024, ROUND_SATURATE_STORE2024_LLM,
                I2024_MIN, I2024_MAX, prvAdvancePCMPointer24)

// Instantiate 16-bit loop functions
RECONMONO_PURELLM(prvReconMonoPureLLM_I16, ROUND_SATURATE_STORE16_LLM,
                SHRT_MIN, SHRT_MAX, prvAdvancePCMPointer16)



WMARESULT auReconMonoPureLLM ( CAudioObject* pau, 
                        PerChannelInfo* ppcinfo, 
                        PCMSAMPLE* piOutput, 
                        I16* pcSampleGet,
                        Bool fForceTransformAll,
                        I16 iCh)
{
    //all starting from the begining of this frame
    //official starting of a subfrm (including leading zeros)
    //case 1 (Large -> Small):  starts later than what's been reconstructed w/o leading zeros
    //                          in this case dst should be skiped (this may mean memcpy from prev)
    //                          src and coef are fine
    //                          
    //case 2 (Small -> Large):  starts earler than what's been reconstructed but all leading zeros
    //                          in this case dst 

//    CoefType *piCoef;   //floating vlaue = (float)*piCoef/(1<<5)  assuming TRANSFORM_FRACT_BITS = 5
    Int i, iEnd, iSegEnd;
//    PCMSAMPLE *piSrc, *piDst; 
    PCMSAMPLE *piDst;
    // get local copies of these values which are used frequently or repeatedly (helps optimization)
    Int cChan = pau->m_cChannel;
    Int cSubFrameSampleHalf = ppcinfo->m_cSubFrameSampleHalfAdjusted;
    CBT * piData = ppcinfo->m_rgiCoefRecon;

#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,RECON_MONO_PROFILE);
#endif
//    DEBUG_IT_FRAME_BREAK;

    //persistent states

    i = pau->m_cGetPCMSamplesDone;       //current position in a frame

    //eventually we'll use piOutput directly
    piDst = piOutput;

    iEnd = i + *pcSampleGet;
    *pcSampleGet = 0;

    if (i < pau->m_rgiPCMInHistory[iCh])
    {
        assert(iEnd <= pau->m_rgiPCMInHistory[iCh]);
        iSegEnd = min (pau->m_rgiPCMInHistory[iCh], iEnd);

        if (pau->m_rgiPCMInHistory[iCh] > pau->m_cFrameSampleHalf) {
            return (WMA_E_FAIL);
        }

        switch (pau->m_iBitDepthSelector)
        {
            case BITDEPTH_24:
                prvReconMonoPureLLM_I24(pau, &i, iSegEnd, &pcSampleGet, &piDst, &piData, cChan);
                break;

            case BITDEPTH_2024:
                prvReconMonoPureLLM_I2024(pau, &i, iSegEnd, &pcSampleGet, &piDst, &piData, cChan);
                break;

            case BITDEPTH_16:
                prvReconMonoPureLLM_I16(pau, &i, iSegEnd, &pcSampleGet, &piDst, &piData, cChan);
                break;

            default:
                prvReconMonoPureLLM(pau, &i, iSegEnd, &pcSampleGet, &piDst, &piData, cChan);
                break;
        }
    }

#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return WMA_OK;
} // auReconMonoPureLLM

WMARESULT auReconstructPureLLM (CAudioObject* pau, U8** ppbDst,
                                I16* pcSampleGet, Bool fForceTransformAll)
{
    I16 iChannel;
    WMARESULT hr = WMA_OK;
    I16 cSamples;
    assert (pau->m_bPureLosslessMode == WMAB_TRUE);
    for (iChannel = 0; iChannel < pau->m_cChannel; iChannel++)
    {
        TRACEWMA_EXIT(hr, auReconMonoPureLLM (pau, 
                      pau->m_rgpcinfo + iChannel, 
                      (PCMSAMPLE*) ppbDst [iChannel],                     
                      (I16*) pcSampleGet + iChannel,
                      fForceTransformAll,
                      iChannel));
    }
    cSamples = pcSampleGet[0];
    for (iChannel = 0; iChannel < pau->m_cChannel; iChannel++) {
        assert(pcSampleGet[iChannel] == cSamples);
    }
    pau->m_cGetPCMSamplesDone += cSamples;

exit:
    return hr;
} // auReconstructPureLLM


//V3 LLMA Chao 03-25-02
Void prvChsForwSTransform(I32 * rgiInput1, I32 * rgiInput2, I32 * rgiS, I32 * rgiD, U32 cLen)
{
    U32 iCoeff;
    for (iCoeff = 0; iCoeff < cLen; iCoeff++) {
        rgiD[iCoeff] = rgiInput2[iCoeff] - rgiInput1[iCoeff];
        rgiS[iCoeff] = rgiInput1[iCoeff] + (rgiD[iCoeff] >> 1);
    }
} // prvChsForwSTransform

Void prvChsInveSTransform(I32 * rgiInput1, I32 * rgiInput2, I32 * rgiS, I32 * rgiD, U32 cLen)
{
    U32 iCoeff;
    for (iCoeff = 0; iCoeff < cLen; iCoeff++) {
        rgiInput1[iCoeff] = rgiInput1[iCoeff] - (rgiD[iCoeff] >> 1);
        rgiInput2[iCoeff] = rgiInput2[iCoeff] + rgiInput1[iCoeff];
    }
} // prvChsInveSTransform

void prvResetColombKinLLMB(CAudioObject * pau, PerChannelInfo * ppcinfo)
{
    ppcinfo->m_iSum = 0;
} // prvResetColombKinLLMB

Void prvBackupFiltersLLM_VERB(CAudioObject * pau, PerChannelInfo * ppcInfoComms)
{
    I16 iCh;
    I16 i,k;

    // DUMPINTDATATOFILE(pau->m_MCLMSPredictor.m_rgiFilter, pau->m_MCLMSPredictor.m_iOrder * pau->m_cChannel, "c:\\temp\\MCLMS.dat")

    // clear Backup buffer to solve the problem when order changes at seeking points.
    memset(pau->m_MCLMSPredictor.m_rgiFilterBackup, 0, 
        sizeof(pau->m_MCLMSPredictor.m_rgiFilterBackup[0]) * LLMB_MCLMS_MAX_ORDER_EACHCH * pau->m_cChannel * pau->m_cChannel);

    // backup rgiFilter
    for (i = 0; i < pau->m_MCLMSPredictor.m_iOrder * pau->m_cChannel * pau->m_cChannel; i++) {
        pau->m_MCLMSPredictor.m_rgiFilterBackup[i] = pau->m_MCLMSPredictor.m_rgiFilter[i];
    }

    // clear Backup buffer to solve the problem when order changes at seeking points.
    memset(pau->m_MCLMSPredictor.m_rgiFilterCurrTimeBackup, 0, 
        sizeof(pau->m_MCLMSPredictor.m_rgiFilterCurrTimeBackup[0]) *  pau->m_cChannel * pau->m_cChannel);

    // backup rgiFilterCurrTime
    for (i = 0; i < pau->m_cChannel * pau->m_cChannel; i++) {
        pau->m_MCLMSPredictor.m_rgiFilterCurrTimeBackup[i] = pau->m_MCLMSPredictor.m_rgiFilterCurrTime[i];
    }

    for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
        PerChannelInfo * ppcInfoComm = ppcInfoComms + iCh;                           

        for (k = 0; k < ppcInfoComm->m_cLMSPredictors; k++) {
            // DUMPINTDATATOFILE(ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilter, ppcInfoComm->m_rgLMSPredictors[k].m_iOrder, "c:\\temp\\CDLMS.dat")
            // clear Backup buffer to solve the problem when order changes at seeking points.
            memset(ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilterBackup, 0, 
                sizeof(ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilterBackup[0]) * LLMB_CLMSFLT_MAX_ORDER);

            for (i = 0; i < ppcInfoComm->m_rgLMSPredictors[k].m_iOrder; i++) {
                ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilterBackup[i] = ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilter[i];
            }
            for (i = 0; i < ppcInfoComm->m_rgLMSPredictors[k].m_iOrder * 2; i++) {
                // 2. We don't backup prevVal.
                // 1. TODO:PrevVal may be 16 bits or 32 bits.
                // ppcInfoComm->m_rgLMSPredictors[k].m_rgiPrevValBackup[i] = ppcInfoComm->m_rgLMSPredictors[k].m_rgiPrevVal[i];
                ppcInfoComm->m_rgLMSPredictors[k].m_rgiUpdateBackup[i] = ppcInfoComm->m_rgLMSPredictors[k].m_rgiUpdate[i];
            }
        }
    }
} // prvBackupFiltersLLM_VERB

// Looks like this function is useless. We do the restore in reset function if we need.
Void prvRestoreFiltersLLM_VERB(CAudioObject * pau, PerChannelInfo * ppcInfoComms)
{
    I16 iCh;
    I16 i,k;

    // DUMPINTDATATOFILE(pau->m_MCLMSPredictor.m_rgiFilter, pau->m_MCLMSPredictor.m_iOrder * pau->m_cChannel, "c:\\temp\\MCLMS.dat")

    // Restore rgiFilter
    for (i = 0; i < pau->m_MCLMSPredictor.m_iOrder * pau->m_cChannel * pau->m_cChannel; i++) {
        pau->m_MCLMSPredictor.m_rgiFilter[i] = pau->m_MCLMSPredictor.m_rgiFilterBackup[i];
    }
    // Restore rgiFilterCurrTime
    for (i = 0; i < pau->m_cChannel * pau->m_cChannel; i++) {
        pau->m_MCLMSPredictor.m_rgiFilterCurrTime[i] = pau->m_MCLMSPredictor.m_rgiFilterCurrTimeBackup[i];
    }

    for (iCh = 0; iCh < pau->m_cChannel; iCh++) {
        PerChannelInfo * ppcInfoComm = ppcInfoComms + iCh;                           

        for (k = 0; k < ppcInfoComm->m_cLMSPredictors; k++) {
            // DUMPINTDATATOFILE(ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilter, ppcInfoComm->m_rgLMSPredictors[k].m_iOrder, "c:\\temp\\CDLMS.dat")
            for (i = 0; i < ppcInfoComm->m_rgLMSPredictors[k].m_iOrder; i++) {
                ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilter[i] = ppcInfoComm->m_rgLMSPredictors[k].m_rgiFilterBackup[i];
            }
            for (i = 0; i < ppcInfoComm->m_rgLMSPredictors[k].m_iOrder * 2; i++) {
                // 2. We don't backup and restore PrevVal.
                // 1. TODO:PrevVal may be 16 bits or 32 bits.
                // ppcInfoComm->m_rgLMSPredictors[k].m_rgiPrevVal[i] = ppcInfoComm->m_rgLMSPredictors[k].m_rgiPrevValBackup[i];
                ppcInfoComm->m_rgLMSPredictors[k].m_rgiUpdate[i] = ppcInfoComm->m_rgLMSPredictors[k].m_rgiUpdateBackup[i];
            }
        }
    }
} // prvRestoreFiltersLLM_VERB


WMARESULT prvLLMVerBResetAllCom(CAudioObject * pau, PerChannelInfo * ppcInfoComms)
{
    WMARESULT     hr = WMA_OK;
    I16 iCh;

    prvMCLMSPredictorReset(pau, &pau->m_MCLMSPredictor);

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        I16 k;
        PerChannelInfo * ppcInfoComm = ppcInfoComms + iChSrc;
        // reset LPC prevsamples.
        memset(ppcInfoComm->m_rgiLPCPrevSamples, 0, LLM_LPC_ORDER * sizeof(I32));
        // Step 1
        memset(ppcInfoComm->m_iLastSamples, 0, LLM_VERB_ACFILTER_ORDER_MAX * sizeof(I32));
        // Step 2
        for (k = 0; k < ppcInfoComm->m_cLMSPredictors; k++) {
            prvResetLMSPredictor(pau, &ppcInfoComm->m_rgLMSPredictors[k]);
        }
        // Step 3
        // We need this call to set m_iSum to a default value. If the seekable 
        // frame is zero power, we won't have chance to compute m_iSum later.
        prvResetColombKinLLMB(pau, ppcInfoComm);

        ppcInfoComm->m_iUpdSpdUpSamples = 0;
        ppcInfoComm->m_iTransientPosition = -1;
        ppcInfoComm->m_iShrtAve = 0;
        ppcInfoComm->m_iLongAve = 0;

        if (ppcInfoComm->m_bUpdateSpeedUp == WMAB_TRUE) {
            U16 j;
            ppcInfoComm->m_bUpdateSpeedUp = WMAB_FALSE;
            for (j = 0; j < ppcInfoComm->m_cLMSPredictors; j++) {
                prvLMSPredictorUpdateSpeedChange(pau, ppcInfoComm->m_rgLMSPredictors + j, WMAB_FALSE);
            }     
        }
    }
    return(hr);
} // prvLLMVerBResetAllCom
#endif // BUILD_WMALSL

