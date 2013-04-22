//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// This file is needed only for WMA Lossless functionality
//*@@@---@@@@******************************************************************

#if !defined(_WIN32_WCE) && !defined(HITACHI)
#include <time.h>
#endif  // _WIN32_WCE
#include <math.h>
#include <limits.h>
#include "msaudio.h"
#include "stdio.h"
#include "AutoProfile.h"


#if defined (BUILD_WMALSL)

// V3 LLMB Chao 03-20-02
WMARESULT prvInitMCLMSPredictor(CAudioObject * pau, MCLMSPredictor * pMCLMSPrdtr, I16 iMaxOrder)
{
    WMARESULT wmaResult = WMA_OK;
    assert(iMaxOrder > 0);

    // We need this assert right now because we don't keep iMaxOrder in pMCLMSPrdtr.
    // Therefore we suppose all buffer size is related to LLMB_MCLMS_MAX_ORDER_EACHCH.
    assert(iMaxOrder == LLMB_MCLMS_MAX_ORDER_EACHCH);
    pMCLMSPrdtr->m_iOrder = iMaxOrder; // sent this for the first BackupFilter call.
    pMCLMSPrdtr->m_rgiFilter = (I16 *)mallocAligned(sizeof(pMCLMSPrdtr->m_rgiFilter[0]) * iMaxOrder * pau->m_cChannel * pau->m_cChannel, 64);
    if(pMCLMSPrdtr->m_rgiFilter == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pMCLMSPrdtr->m_rgiFilter, 0, sizeof(pMCLMSPrdtr->m_rgiFilter[0]) * iMaxOrder * pau->m_cChannel * pau->m_cChannel);

    pMCLMSPrdtr->m_rgiFilterBackup = (I16 *)mallocAligned(sizeof(pMCLMSPrdtr->m_rgiFilterBackup[0]) * iMaxOrder * pau->m_cChannel * pau->m_cChannel, 64);
    if(pMCLMSPrdtr->m_rgiFilterBackup == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pMCLMSPrdtr->m_rgiFilterBackup, 0, sizeof(pMCLMSPrdtr->m_rgiFilterBackup[0]) * iMaxOrder * pau->m_cChannel * pau->m_cChannel);

    pMCLMSPrdtr->m_rgiFilterCurrTime = (I16 *)mallocAligned(sizeof(pMCLMSPrdtr->m_rgiFilterCurrTime[0]) * pau->m_cChannel * pau->m_cChannel, 64);
    if(pMCLMSPrdtr->m_rgiFilterCurrTime == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pMCLMSPrdtr->m_rgiFilterCurrTime, 0, sizeof(pMCLMSPrdtr->m_rgiFilterCurrTime[0]) * pau->m_cChannel * pau->m_cChannel);

    pMCLMSPrdtr->m_rgiFilterCurrTimeBackup = (I16 *)mallocAligned(sizeof(pMCLMSPrdtr->m_rgiFilterCurrTimeBackup[0]) * pau->m_cChannel * pau->m_cChannel, 64);
    if(pMCLMSPrdtr->m_rgiFilterCurrTimeBackup == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pMCLMSPrdtr->m_rgiFilterCurrTimeBackup, 0, sizeof(pMCLMSPrdtr->m_rgiFilterCurrTimeBackup[0]) * pau->m_cChannel * pau->m_cChannel);

    pMCLMSPrdtr->m_rgiPrevVal = (I32 *)mallocAligned(sizeof(pMCLMSPrdtr->m_rgiPrevVal[0]) * iMaxOrder * pau->m_cChannel * 2, 64);
    if(pMCLMSPrdtr->m_rgiPrevVal == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pMCLMSPrdtr->m_rgiPrevVal, 0, sizeof(pMCLMSPrdtr->m_rgiPrevVal[0]) * iMaxOrder * pau->m_cChannel * 2);

    pMCLMSPrdtr->m_rgiUpdate = (I16 *)mallocAligned(sizeof(pMCLMSPrdtr->m_rgiUpdate[0]) * iMaxOrder * pau->m_cChannel * 2, 64);
    if(pMCLMSPrdtr->m_rgiUpdate == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pMCLMSPrdtr->m_rgiUpdate, 0, sizeof(pMCLMSPrdtr->m_rgiUpdate[0]) * iMaxOrder * pau->m_cChannel * 2);

    // prvMCLMSPredictorReset(pau, pMCLMSPrdtr);
    //TODO: init ColombK
exit:
    return wmaResult;
}

Void prvMCLMSPredictorReset(CAudioObject * pau, MCLMSPredictor * pMCLMSPrdtr)
{
    I32 i;
    I32 iOrder = pMCLMSPrdtr->m_iOrder;
    assert(iOrder <= LLMB_MCLMS_MAX_ORDER_EACHCH);

    for (i = 0; i < iOrder * pau->m_cChannel * pau->m_cChannel; i++) {
        pMCLMSPrdtr->m_rgiFilter[i] = 0;       
    }

    for (i = 0; i < pau->m_cChannel * pau->m_cChannel; i++) {
          pMCLMSPrdtr->m_rgiFilterCurrTime[i] = 0;       
    }
    for (i = 0; i < pau->m_cChannel; i++) {
        pMCLMSPrdtr->m_rgiFilterCurrTime[i * pau->m_cChannel] = 0;
    }

    if (pau->m_bSendMCLMS == WMAB_TRUE) {
        for (i = 0; i < pau->m_MCLMSPredictor.m_iOrder * pau->m_cChannel * pau->m_cChannel; i++) {
            pau->m_MCLMSPredictor.m_rgiFilter[i] = pau->m_MCLMSPredictor.m_rgiFilterBackup[i];
        }
        for (i = 0; i < pau->m_cChannel * pau->m_cChannel; i++) {
            pau->m_MCLMSPredictor.m_rgiFilterCurrTime[i] = pau->m_MCLMSPredictor.m_rgiFilterCurrTimeBackup[i];
        }
    }
    memset (pMCLMSPrdtr->m_rgiPrevVal, 0, sizeof(pMCLMSPrdtr->m_rgiPrevVal[0]) * iOrder * pau->m_cChannel * 2);
    memset (pMCLMSPrdtr->m_rgiUpdate, 0, sizeof(pMCLMSPrdtr->m_rgiUpdate[0]) * iOrder * pau->m_cChannel * 2);
    pMCLMSPrdtr->m_iRecent = iOrder * pau->m_cChannel;
    pMCLMSPrdtr->m_iOrder_X_CH = iOrder * pau->m_cChannel;
    pMCLMSPrdtr->m_iScalingOffset = (1 << (pMCLMSPrdtr->m_iScaling - 1));

    pMCLMSPrdtr->m_iUpdStepSize = 1;
}

/*****************************************************************************
   V3 LLMB MCLMS 03-20-02
                       Encoder                 Decoder
   Input:rgiInput:     PCM                     residue
   Output:rgiInput:    PCM                     PCM
*****************************************************************************/
// TODO: Current code is not efficient at processing zero power channel.
Void prvMCLMSPredictorPred_I16_C(CAudioObject * pau, MCLMSPredictor * pMCLMSPredictor, CBT *rgiInput, CBT *rgiPred, Bool bDecoder)
{
    I32 i,j;
    I16 * piFilter = pMCLMSPredictor->m_rgiFilter;
    I16 * piFilterCurrTime = pMCLMSPredictor->m_rgiFilterCurrTime;
    I16 * piPrevVal = (I16 *)pMCLMSPredictor->m_rgiPrevVal + pMCLMSPredictor->m_iRecent;
    I16 * piUpdate = pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iRecent;
    I32 iPred = 0;

    for (j = 0; j < pau->m_cChannel; j++) {     //predict channel j
        if (rgiPred[j] == 0) { // decoder : this channel has zero power.
            // piFilter += pau->m_cChannel * pMCLMSPredictor->m_iOrder;
            piFilter += pMCLMSPredictor->m_iOrder_X_CH;
            piFilterCurrTime += pau->m_cChannel;
            assert(rgiInput[j] == 0);
            continue;
        }
        iPred = 0;
        // Use previous time PCM samples to predict.
        for (i = 0; i < (pMCLMSPredictor->m_iOrder_X_CH >> 1); i++) {
            iPred += ((I32)(*(piFilter + 2*i)) * (I32)(*(piPrevVal + 2*i)) + (I32)(*(piFilter + 2*i+1)) * (I32)(*(piPrevVal + 2*i+1)));
        }
        // Use PCM sample at the same time to predict.
        for (i = 0; i < j; i++) {
            iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));
        }

        iPred += (pMCLMSPredictor->m_iScalingOffset);
        iPred = iPred >> (pMCLMSPredictor->m_iScaling);
        rgiPred[j] = iPred;

        if (bDecoder) {
            rgiInput[j] = rgiInput[j] + rgiPred[j];
        }
        piFilter += pMCLMSPredictor->m_iOrder_X_CH;
        piFilterCurrTime += pau->m_cChannel;
    }
}

Void prvMCLMSPredictorPred_I32_C(CAudioObject * pau, MCLMSPredictor * pMCLMSPredictor, CBT *rgiInput, CBT *rgiPred, Bool bDecoder)
{
    I32 i,j;
    I16 * piFilter = pMCLMSPredictor->m_rgiFilter;
    I16 * piFilterCurrTime = pMCLMSPredictor->m_rgiFilterCurrTime;
    I32 * piPrevVal = pMCLMSPredictor->m_rgiPrevVal + pMCLMSPredictor->m_iRecent;
    I16 * piUpdate = pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iRecent;
    I32 iPredTemp = 0, iPredHi = 0, iPredLo = 0;
    I32 iPred = 0;

    for (j = 0; j < pau->m_cChannel; j++) {     //predict channel j
        if (rgiPred[j] == 0) { // decoder : this channel has zero power.
            piFilter += pau->m_cChannel * pMCLMSPredictor->m_iOrder;
            piFilterCurrTime += pau->m_cChannel;
            assert(rgiInput[j] == 0);
            continue;
        }
        iPred = 0;
        // Use previous time PCM samples to predict.
        for (i = 0; i < pau->m_cChannel * pMCLMSPredictor->m_iOrder / 2; i++) {
            iPred += ((I32)(*(piFilter + 2*i)) * (*(piPrevVal + 2*i)) + (I32)(*(piFilter + 2*i+1)) * (*(piPrevVal + 2*i+1)));
        }

        // Use PCM sample at the same time to predict.
        for (i = 0; i < j; i++) {
            iPred += (I32)rgiInput[i] * (*(piFilterCurrTime + i));
        }

        iPred += (pMCLMSPredictor->m_iScalingOffset);
        iPred = iPred >> (pMCLMSPredictor->m_iScaling);
        rgiPred[j] = iPred;
        if (bDecoder) {
            rgiInput[j] = rgiInput[j] + rgiPred[j];
        }
        piFilter += pMCLMSPredictor->m_iOrder_X_CH;
        piFilterCurrTime += pau->m_cChannel;
    }
}

// TODO: if channel power is zero, we still call this function. But since input and pred are all zero, the filter
// will not be changed actually. Any better approach?
Void prvMCLMSPredictorUpdate_I16_C(CAudioObject * pau, MCLMSPredictor * pMCLMSPredictor, CBT * rgiInput, CBT *rgiPred)
{
    I32 i, j;
    I32 iUpdate = 1;

    I16 * piFilter = pMCLMSPredictor->m_rgiFilter;
    I16 * piFilterCurrTime = pMCLMSPredictor->m_rgiFilterCurrTime;
    I16 * piUpdate = pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iRecent;
    I16 * rgiPrevVal = (I16 *)pMCLMSPredictor->m_rgiPrevVal;
    
    for (j = 0; j < pau->m_cChannel; j++) {        
        I32 iPredErr = (I32)rgiInput[j] - (I32)rgiPred[j];
        if (iPredErr > 0) {
            for (i = 0; i < pau->m_cChannel * pMCLMSPredictor->m_iOrder; i++) {
                (*(piFilter + i)) += (*(piUpdate + i));
            }
            for (i = 0; i < j; i++) {
                if (rgiInput[i] > 0)
                    (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        else if (iPredErr < 0) {
            for (i = 0; i < pau->m_cChannel * pMCLMSPredictor->m_iOrder; i++) {
                (*(piFilter + i)) -= (*(piUpdate + i));
            }
            for (i = 0; i < j; i++) {
                if (rgiInput[i] > 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        piFilter += pMCLMSPredictor->m_iOrder_X_CH;
        piFilterCurrTime += pau->m_cChannel;
    }

    assert(pMCLMSPredictor->m_iRecent <= pMCLMSPredictor->m_iOrder * pau->m_cChannel);
    assert(pMCLMSPredictor->m_iRecent > 0);

    for (j = pau->m_cChannel - 1; j >= 0; j--) {
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iRecent - 1;

        if (rgiInput[j] > pau->m_iSampleMaxValue)
            rgiPrevVal[pMCLMSPredictor->m_iRecent] = (I16)pau->m_iSampleMaxValue;
        else if (rgiInput[j] < pau->m_iSampleMinValue)
            rgiPrevVal[pMCLMSPredictor->m_iRecent] = (I16)pau->m_iSampleMinValue;
        else
            rgiPrevVal[pMCLMSPredictor->m_iRecent] = (I16)rgiInput[j];
        if (rgiInput[j] > 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = pMCLMSPredictor->m_iUpdStepSize;
        else if (rgiInput[j] < 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = -pMCLMSPredictor->m_iUpdStepSize;
        else
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = 0;
    }

    if (pMCLMSPredictor->m_iRecent == 0) {
        memcpy(rgiPrevVal + pMCLMSPredictor->m_iOrder * pau->m_cChannel, rgiPrevVal, sizeof(rgiPrevVal[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        memcpy(pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iOrder * pau->m_cChannel, pMCLMSPredictor->m_rgiUpdate, sizeof(pMCLMSPredictor->m_rgiUpdate[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iOrder_X_CH;
    }
}

Void prvMCLMSPredictorUpdate_I32_C(CAudioObject * pau, MCLMSPredictor * pMCLMSPredictor, CBT * rgiInput, CBT * rgiPred)
{
    I32 i, j;
    I32 iUpdate = 1;

    I16 * piFilter = pMCLMSPredictor->m_rgiFilter;
    I16 * piFilterCurrTime = pMCLMSPredictor->m_rgiFilterCurrTime;
    I16 * piUpdate = pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iRecent;
    I32 * rgiPrevVal = (I32 *)pMCLMSPredictor->m_rgiPrevVal;
    for (j = 0; j < pau->m_cChannel; j++) {        
        I32 iPredErr = (I32)rgiInput[j] - (I32)rgiPred[j];
        if (iPredErr > 0) {
            for (i = 0; i < pau->m_cChannel * pMCLMSPredictor->m_iOrder; i++) {
                (*(piFilter + i)) += (*(piUpdate + i));
            }
            for (i = 0; i < j; i++) {
                if (rgiInput[i] > 0)
                    (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        else if (iPredErr < 0) {
            for (i = 0; i < pau->m_cChannel * pMCLMSPredictor->m_iOrder; i++) {
                (*(piFilter + i)) -= (*(piUpdate + i));
            }
            for (i = 0; i < j; i++) {
                if (rgiInput[i] > 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        piFilter += pMCLMSPredictor->m_iOrder_X_CH;
        piFilterCurrTime += pau->m_cChannel;
    }

    assert(pMCLMSPredictor->m_iRecent <= pMCLMSPredictor->m_iOrder * pau->m_cChannel);
    assert(pMCLMSPredictor->m_iRecent > 0);

    for (j = pau->m_cChannel - 1; j >= 0; j--) {
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iRecent - 1;

        if (rgiInput[j] > pau->m_iSampleMaxValue)
            rgiPrevVal[pMCLMSPredictor->m_iRecent] = (I32)pau->m_iSampleMaxValue;
        else if (rgiInput[j] < pau->m_iSampleMinValue)
            rgiPrevVal[pMCLMSPredictor->m_iRecent] = (I32)pau->m_iSampleMinValue;
        else
            rgiPrevVal[pMCLMSPredictor->m_iRecent] = (I32)rgiInput[j];
 
        if (rgiInput[j] > 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = pMCLMSPredictor->m_iUpdStepSize;
        else if (rgiInput[j] < 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = -pMCLMSPredictor->m_iUpdStepSize;
        else
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = 0;
    }

    if (pMCLMSPredictor->m_iRecent == 0) {
        memcpy(pMCLMSPredictor->m_rgiPrevVal + pMCLMSPredictor->m_iOrder * pau->m_cChannel, pMCLMSPredictor->m_rgiPrevVal, sizeof(pMCLMSPredictor->m_rgiPrevVal[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        memcpy(pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iOrder * pau->m_cChannel, pMCLMSPredictor->m_rgiUpdate, sizeof(pMCLMSPredictor->m_rgiUpdate[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iOrder_X_CH;
    }
}

#if !WMA_OPT_LPCLSL_ARM
#if !( (defined(WMA_TARGET_MIPS) || defined(WMA_TARGET_SH4))  && defined(PLATFORM_SPECIFIC_LPCLSL))
//Combine prvMCLMSPredictorPred_I16_C and prvMCLMSPredictorUpdate_I16_C into one function
Void prvDecMCLMSPredictorPredAndUpdate_I16(CAudioObject * pau, MCLMSPredictor * pMCLMSPredictor, CBT *rgiInput, CBT *rgiPred)
{
    I32 i,j;
    I32 iPred;

    I16 * piFilter = pMCLMSPredictor->m_rgiFilter;
    I16 * piFilterCurrTime = pMCLMSPredictor->m_rgiFilterCurrTime;
    I16 * piPrevVal = (I16 *)pMCLMSPredictor->m_rgiPrevVal + pMCLMSPredictor->m_iRecent;
    I16 * piUpdate = pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iRecent;

    for (j = 0; j < pau->m_cChannel; j++) {     //predict channel j
        if (rgiPred[j] == 0) { // decoder : this channel has zero power.
            // piFilter += pau->m_cChannel * pMCLMSPredictor->m_iOrder;
            piFilter += pMCLMSPredictor->m_iOrder_X_CH;
            piFilterCurrTime += pau->m_cChannel;
            assert(rgiInput[j] == 0);
            continue;
        }

        iPred = (pMCLMSPredictor->m_iScalingOffset);

        if (rgiInput[j] > 0){
            // Use previous time PCM samples to predict.
            for (i = 0; i < pMCLMSPredictor->m_iOrder_X_CH; i++) {
                iPred += ((I32)(*(piFilter + i)) * (I32)(*(piPrevVal + i)));
                (*(piFilter + i)) += (*(piUpdate + i));
            }

            // Use PCM sample at the same time to predict.
            for (i = j-1; i >= 0; i--) {
                iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));

                if (rgiInput[i] > 0)
                   (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        else if (rgiInput[j] < 0){
            // Use previous time PCM samples to predict.
            for (i = 0; i < pMCLMSPredictor->m_iOrder_X_CH; i++) {
                iPred += ((I32)(*(piFilter + i)) * (I32)(*(piPrevVal + i)));
                (*(piFilter + i)) -= (*(piUpdate + i));
            }

            // Use PCM sample at the same time to predict.
            for (i = j-1; i >= 0; i--) {
                iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));
                
                if (rgiInput[i] > 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        else { // (rgiInput[j] == 0)
            for (i = 0; i < pMCLMSPredictor->m_iOrder_X_CH; i++) {
                iPred += ((I32)(*(piFilter + i)) * (I32)(*(piPrevVal + i)));
            }

            // Use PCM sample at the same time to predict.
            for (i = j-1; i >= 0; i--) {
                iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));
            }
        }

        iPred = iPred >> (pMCLMSPredictor->m_iScaling);
        rgiPred[j] = iPred;
        rgiInput[j] = rgiInput[j] + iPred;

        piFilter += pMCLMSPredictor->m_iOrder_X_CH;
        piFilterCurrTime += pau->m_cChannel;
    }

    assert(pMCLMSPredictor->m_iRecent <= pMCLMSPredictor->m_iOrder * pau->m_cChannel);
    assert(pMCLMSPredictor->m_iRecent > 0);

    piPrevVal = (I16 *)pMCLMSPredictor->m_rgiPrevVal;

    for (j = pau->m_cChannel - 1; j >= 0; j--) {
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iRecent - 1;

        if (rgiInput[j] > pau->m_iSampleMaxValue)
            piPrevVal[pMCLMSPredictor->m_iRecent] = (I16)pau->m_iSampleMaxValue;
        else if (rgiInput[j] < pau->m_iSampleMinValue)
            piPrevVal[pMCLMSPredictor->m_iRecent] = (I16)pau->m_iSampleMinValue;
        else
            piPrevVal[pMCLMSPredictor->m_iRecent] = (I16)rgiInput[j];

        if (rgiInput[j] > 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = pMCLMSPredictor->m_iUpdStepSize;
        else if (rgiInput[j] < 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = -pMCLMSPredictor->m_iUpdStepSize;
        else
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = 0;
    }

    if (pMCLMSPredictor->m_iRecent == 0) {
        memcpy(piPrevVal + pMCLMSPredictor->m_iOrder_X_CH, piPrevVal, sizeof(piPrevVal[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        memcpy(pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iOrder_X_CH, pMCLMSPredictor->m_rgiUpdate, sizeof(pMCLMSPredictor->m_rgiUpdate[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iOrder_X_CH;
    }
}


//Combine prvMCLMSPredictorPred_I32_C and prvMCLMSPredictorUpdate_I32_C into one function
Void prvDecMCLMSPredictorPredAndUpdate_I32(CAudioObject * pau, MCLMSPredictor * pMCLMSPredictor, CBT *rgiInput, CBT *rgiPred)
{
    I32 i,j;
    I32 iPred;

    I16 * piFilter = pMCLMSPredictor->m_rgiFilter;
    I16 * piFilterCurrTime = pMCLMSPredictor->m_rgiFilterCurrTime;
    I32 * piPrevVal = pMCLMSPredictor->m_rgiPrevVal + pMCLMSPredictor->m_iRecent;
    I16 * piUpdate = pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iRecent;

    for (j = 0; j < pau->m_cChannel; j++) {     //predict channel j
        if (rgiPred[j] == 0) { // decoder : this channel has zero power.
            // piFilter += pau->m_cChannel * pMCLMSPredictor->m_iOrder;
            piFilter += pMCLMSPredictor->m_iOrder_X_CH;
            piFilterCurrTime += pau->m_cChannel;
            assert(rgiInput[j] == 0);
            continue;
        }

        iPred = (pMCLMSPredictor->m_iScalingOffset);

        if (rgiInput[j] > 0){
            // Use previous time PCM samples to predict.
            for (i = 0; i < pMCLMSPredictor->m_iOrder_X_CH; i++) {
                iPred += ((I32)(*(piFilter + i)) * (*(piPrevVal + i)));
                (*(piFilter + i)) += (*(piUpdate + i));
            }

            // Use PCM sample at the same time to predict.
            for (i = j-1; i >= 0; i--) {
                iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));

                if (rgiInput[i] > 0)
                   (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        else if (rgiInput[j] < 0){
            // Use previous time PCM samples to predict.
            for (i = 0; i < pMCLMSPredictor->m_iOrder_X_CH; i++) {
                iPred += ((I32)(*(piFilter + i)) * (*(piPrevVal + i)));
                (*(piFilter + i)) -= (*(piUpdate + i));
            }

            // Use PCM sample at the same time to predict.
            for (i = j-1; i >= 0; i--) {
                iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));
                
                if (rgiInput[i] > 0)
                    (*(piFilterCurrTime + i)) -= pMCLMSPredictor->m_iUpdStepSize;
                else if (rgiInput[i] < 0)
                    (*(piFilterCurrTime + i)) += pMCLMSPredictor->m_iUpdStepSize;
            }
        }
        else { // (rgiInput[j] == 0)
            for (i = 0; i < pMCLMSPredictor->m_iOrder_X_CH; i++) {
                iPred += ((I32)(*(piFilter + i)) * (*(piPrevVal + i)));
            }

            // Use PCM sample at the same time to predict.
            for (i = j-1; i >= 0; i--) {
                iPred += (I32)rgiInput[i] * (I32)(*(piFilterCurrTime + i));
            }
        }

        iPred = iPred >> (pMCLMSPredictor->m_iScaling);
        rgiPred[j] = iPred;
        rgiInput[j] = rgiInput[j] + iPred;

        piFilter += pMCLMSPredictor->m_iOrder_X_CH;
        piFilterCurrTime += pau->m_cChannel;
    }

    assert(pMCLMSPredictor->m_iRecent <= pMCLMSPredictor->m_iOrder * pau->m_cChannel);
    assert(pMCLMSPredictor->m_iRecent > 0);

    piPrevVal = (I32 *)pMCLMSPredictor->m_rgiPrevVal;

    for (j = pau->m_cChannel - 1; j >= 0; j--) {
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iRecent - 1;

        if (rgiInput[j] > pau->m_iSampleMaxValue)
            piPrevVal[pMCLMSPredictor->m_iRecent] = (I32)pau->m_iSampleMaxValue;
        else if (rgiInput[j] < pau->m_iSampleMinValue)
            piPrevVal[pMCLMSPredictor->m_iRecent] = (I32)pau->m_iSampleMinValue;
        else
            piPrevVal[pMCLMSPredictor->m_iRecent] = (I32)rgiInput[j];

        if (rgiInput[j] > 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = pMCLMSPredictor->m_iUpdStepSize;
        else if (rgiInput[j] < 0)
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = -pMCLMSPredictor->m_iUpdStepSize;
        else
            pMCLMSPredictor->m_rgiUpdate[pMCLMSPredictor->m_iRecent] = 0;
    }

    if (pMCLMSPredictor->m_iRecent == 0) {
        memcpy(piPrevVal + pMCLMSPredictor->m_iOrder_X_CH, piPrevVal, sizeof(piPrevVal[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        memcpy(pMCLMSPredictor->m_rgiUpdate + pMCLMSPredictor->m_iOrder_X_CH, pMCLMSPredictor->m_rgiUpdate, sizeof(pMCLMSPredictor->m_rgiUpdate[0]) * pMCLMSPredictor->m_iOrder_X_CH);
        pMCLMSPredictor->m_iRecent = pMCLMSPredictor->m_iOrder_X_CH;
    }
}
#endif //WMA_TARGET_MIPS
#endif //WMA_OPT_LPCLSL_ARM

//V3 LLM-B. Chao. Add. 03-20-02 Free the memory malloced for MCLMSPredictor.
Void prvFreeMCLMSPredictor(MCLMSPredictor * pMCLMSPrdtr)
{
/*    
    assert(pMCLMSPrdtr->m_rgiFilter != NULL);
    assert(pMCLMSPrdtr->m_rgiPrevVal != NULL);
    assert(pMCLMSPrdtr->m_rgiFilterCurrTime != NULL);
    assert(pMCLMSPrdtr->m_rgiUpdate != NULL);
*/
    freeAligned(pMCLMSPrdtr->m_rgiFilter);
    freeAligned(pMCLMSPrdtr->m_rgiFilterBackup);
    freeAligned(pMCLMSPrdtr->m_rgiFilterCurrTime);
    freeAligned(pMCLMSPrdtr->m_rgiFilterCurrTimeBackup);
    freeAligned(pMCLMSPrdtr->m_rgiPrevVal);
    freeAligned(pMCLMSPrdtr->m_rgiUpdate);
}

#endif // BUILD_WMALSL
