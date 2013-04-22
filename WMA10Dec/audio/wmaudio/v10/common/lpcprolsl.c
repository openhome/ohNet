//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// This file is needed for both WMA Lossless and WMA Pro functionality, but not for WMA Standard.
//*@@@---@@@@******************************************************************


#if !defined(_WIN32_WCE) && !defined(HITACHI)
#include <time.h>
#endif  // _WIN32_WCE
#include <math.h>
#include <limits.h>
#include "msaudio.h"
#include "stdio.h"
#include "AutoProfile.h"

#if (defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM))|| defined (BUILD_WMALSL)

/***
*   Function: prvInitLMSPredictor
*   Purpose: prvInitLMSPredictor is called at codec initialization. This function mallocs the buffer for LMS filter. 
*       But it doesn't set the LMS filter's order/updating speed/limit... That work is done at prvResetLMSPredictor.
*   Input: iMaxOrder    - Maximum order of LMS filter. Buffers are malloced based on this value.
*   Output: Nothing.
************************************************/
WMARESULT prvInitLMSPredictor(LMSPredictor * pLMSPrdtr, U16 iMaxOrder, U8 * pMem, I32 * pcbMemUsed, I32 cbMemTtl)
{
    WMARESULT wmaResult = WMA_OK;

    // We need this assert right now because we don't keep iMaxOrder in pMCLMSPrdtr.
    // Therefore we suppose all buffer size is related to LLMB_CLMSFLT_MAX_ORDER.
    assert(iMaxOrder == LLMB_CLMSFLT_MAX_ORDER);

    pLMSPrdtr->m_iOrder = iMaxOrder; // set for backupfilter call.
#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
    pLMSPrdtr->m_rgiFilter = (Float *)mallocAligned(sizeof(pLMSPrdtr->m_rgiFilter[0]) * iMaxOrder, 64);
#else
    pLMSPrdtr->m_rgiFilter = (I16 *)mallocAligned(sizeof(pLMSPrdtr->m_rgiFilter[0]) * iMaxOrder, 64);    
#endif
    if(pLMSPrdtr->m_rgiFilter == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pLMSPrdtr->m_rgiFilter, 0, sizeof(pLMSPrdtr->m_rgiFilter[0]) * iMaxOrder);

#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
    pLMSPrdtr->m_rgiFilterBackup = (Float *)mallocAligned(sizeof(pLMSPrdtr->m_rgiFilterBackup[0]) * iMaxOrder, 64);
#else
    pLMSPrdtr->m_rgiFilterBackup = (I16 *)mallocAligned(sizeof(pLMSPrdtr->m_rgiFilterBackup[0]) * iMaxOrder, 64);   
#endif
    if(pLMSPrdtr->m_rgiFilterBackup == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pLMSPrdtr->m_rgiFilterBackup, 0, sizeof(pLMSPrdtr->m_rgiFilterBackup[0]) * iMaxOrder);

    pLMSPrdtr->m_rgiPrevVal = (I32 *)mallocAligned(sizeof(pLMSPrdtr->m_rgiPrevVal[0]) * iMaxOrder * 2, 64);
    if(pLMSPrdtr->m_rgiPrevVal == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pLMSPrdtr->m_rgiPrevVal, 0, sizeof(pLMSPrdtr->m_rgiPrevVal[0]) * iMaxOrder * 2);

#if 0
    pLMSPrdtr->m_rgiPrevValBackup = (I32 *)mallocAligned(sizeof(pLMSPrdtr->m_rgiPrevValBackup[0]) * iMaxOrder * 2, 64);
    if(pLMSPrdtr->m_rgiPrevValBackup == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pLMSPrdtr->m_rgiPrevValBackup, 0, sizeof(pLMSPrdtr->m_rgiPrevValBackup[0]) * iMaxOrder * 2);
#endif

#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)  
    pLMSPrdtr->m_rgiUpdate = (Float *)mallocAligned(sizeof(pLMSPrdtr->m_rgiUpdate[0]) * iMaxOrder * 2, 64);
#else
    pLMSPrdtr->m_rgiUpdate = (I16 *)mallocAligned(sizeof(pLMSPrdtr->m_rgiUpdate[0]) * iMaxOrder * 2, 64);
#endif

    if(pLMSPrdtr->m_rgiUpdate == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pLMSPrdtr->m_rgiUpdate, 0, sizeof(pLMSPrdtr->m_rgiUpdate[0]) * iMaxOrder * 2);

#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)  
    pLMSPrdtr->m_rgiUpdateBackup = (Float *)mallocAligned(sizeof(pLMSPrdtr->m_rgiUpdateBackup[0]) * iMaxOrder * 2, 64);
#else
    pLMSPrdtr->m_rgiUpdateBackup = (I16 *)mallocAligned(sizeof(pLMSPrdtr->m_rgiUpdateBackup[0]) * iMaxOrder * 2, 64);
#endif

    if(pLMSPrdtr->m_rgiUpdateBackup == NULL)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pLMSPrdtr->m_rgiUpdateBackup, 0, sizeof(pLMSPrdtr->m_rgiUpdateBackup[0]) * iMaxOrder * 2);
exit:
    return wmaResult;
}


//V3 LLM-B. Chao. Add. 03-15-02 Free the memory malloced for LMSPredictor.
Void prvFreeLMSPredictor(LMSPredictor * pLMSPrdtr)
{
/*
    assert(pLMSPrdtr->m_rgiFilter);
    assert(pLMSPrdtr->m_rgiFilterBackup);
    assert(pLMSPrdtr->m_rgiPrevVal);
    assert(pLMSPrdtr->m_rgiUpdate);
*/
    freeAligned(pLMSPrdtr->m_rgiFilter);
    freeAligned(pLMSPrdtr->m_rgiFilterBackup);
    freeAligned(pLMSPrdtr->m_rgiPrevVal);
#if 0
    freeAligned(pLMSPrdtr->m_rgiPrevValBackup);
#endif
    freeAligned(pLMSPrdtr->m_rgiUpdate);
    freeAligned(pLMSPrdtr->m_rgiUpdateBackup);
}

//--- Lossless LMS functions ---//

// We permit the computational overflow but make sure they overflow in the same way (C/MMX).
I32 prvLMSPredictorPred_I16_C(LMSPredictor * pLMSPredictor)
{
    I32 iPred = 0;
#if !defined(WMA_OPT_FLOAT_PREDICTOR_XENON)  

    I32 i;
    I16 * rgiFilter = pLMSPredictor->m_rgiFilter;
    I16 * rgiPrevVal = (I16 *)pLMSPredictor->m_rgiPrevVal + pLMSPredictor->m_iRecent;
    I32 iPredLeft0 = 0, iPredRight0 = 0;
    I32 iPredLeft1 = 0, iPredRight1 = 0;
    for (i = 0; i < pLMSPredictor->m_iOrder_Div_8; i++) {
        iPredLeft0 += (I32)(rgiFilter[0]) * (I32)(rgiPrevVal[0]) + (I32)(rgiFilter[1]) * (I32)(rgiPrevVal[1]);
        iPredRight0 += (I32)(rgiFilter[2]) * (I32)(rgiPrevVal[2]) + (I32)(rgiFilter[3]) * (I32)(rgiPrevVal[3]);
        iPredLeft1 += (I32)(rgiFilter[4]) * (I32)(rgiPrevVal[4]) + (I32)(rgiFilter[5]) * (I32)(rgiPrevVal[5]);
        iPredRight1 += (I32)(rgiFilter[6]) * (I32)(rgiPrevVal[6]) + (I32)(rgiFilter[7]) * (I32)(rgiPrevVal[7]);
        rgiFilter += 8;
        rgiPrevVal += 8;
    }
    iPred = (iPredLeft0 + iPredLeft1) + (iPredRight0 + iPredRight1);
    iPred += pLMSPredictor->m_iScalingOffset;
    iPred = (iPred >> pLMSPredictor->m_iScaling);
//    iPredOld = iPred;
#endif
    return (iPred);
}

Void prvLMSPredictorUpdate_I16_C(CAudioObject * pau, LMSPredictor * pLMSPredictor, I32 iInput, I32 iPred)
{
#if !defined(WMA_OPT_FLOAT_PREDICTOR_XENON) 
    I32 iPredErr = iInput - iPred;
    I32 iUpdate = 0;

    I16 * rgiFilter = pLMSPredictor->m_rgiFilter;
    I16 * rgiUpdate = pLMSPredictor->m_rgiUpdate;
    I16 * rgiPrevVal = (I16 *)pLMSPredictor->m_rgiPrevVal;

    // actually, we should also control the updating speed based on their position in cascaded struture.
    // The earlier the filter, the slower the updating speed. Because if you update the early filters two fast,
    // the result would be very tough for following filters. Need more consideration.
    if (iPredErr > 0) 
    {
        I32 i = 0;
        for (i = 0; i < pLMSPredictor->m_iOrder; i++) {
            rgiFilter[i] +=  rgiUpdate[i + pLMSPredictor->m_iRecent];
        }
    }
    else if (iPredErr < 0 ){
        I32 i = 0;
        for (i = 0; i < pLMSPredictor->m_iOrder; i++) {
            rgiFilter[i] -=  rgiUpdate[i + pLMSPredictor->m_iRecent];
        }
    }

    assert(pLMSPredictor->m_iRecent >= 0);
    assert(pLMSPredictor->m_iRecent < 2 * pLMSPredictor->m_iOrder);

    if (pLMSPredictor->m_iRecent == 0) {
        memcpy(rgiPrevVal + pLMSPredictor->m_iOrder, rgiPrevVal, sizeof(rgiPrevVal[0]) * pLMSPredictor->m_iOrder);
        memcpy(rgiUpdate + pLMSPredictor->m_iOrder, rgiUpdate, sizeof(rgiUpdate[0]) * pLMSPredictor->m_iOrder);
        pLMSPredictor->m_iRecent = pLMSPredictor->m_iOrder - 1;
    }
    else
        pLMSPredictor->m_iRecent = pLMSPredictor->m_iRecent - 1;

    //  truncate to I16 is used to simulate the MMX behavior since we decided to pack 4 samples together.
    //  results show that the performance loss is small.
    //    pLMSPredictor->m_rgiPrevVal[pLMSPredictor->m_iRecent] = (I16)iInput;

    //    assert(pau->m_iSampleMaxValue == (1 << 15) - 1);
    //    assert(pau->m_iSampleMinValue == -((1 << 15) - 1));

    if (iInput > pau->m_iSampleMaxValue ) {
        rgiPrevVal[pLMSPredictor->m_iRecent] = ((I16)pau->m_iSampleMaxValue);
    }
    else if (iInput < pau->m_iSampleMinValue) {
        rgiPrevVal[pLMSPredictor->m_iRecent] = ((I16)pau->m_iSampleMinValue);        
    }
    else
        rgiPrevVal[pLMSPredictor->m_iRecent] = ((I16)iInput);

    if (iInput > 0)
        rgiUpdate[pLMSPredictor->m_iRecent] = (I16)pLMSPredictor->m_iUpdStepSize_X_8;
    else if (iInput < 0)
        rgiUpdate[pLMSPredictor->m_iRecent] = - (I16)pLMSPredictor->m_iUpdStepSize_X_8;
    else
        rgiUpdate[pLMSPredictor->m_iRecent] = 0;

    rgiUpdate[pLMSPredictor->m_iRecent + pLMSPredictor->m_iOrder_Div_16] >>= 2;
    rgiUpdate[pLMSPredictor->m_iRecent + pLMSPredictor->m_iOrder_Div_8] >>= 1;
#endif
}


I32 prvLMSPredictorPred_I32_C(LMSPredictor * pLMSPredictor)
{
    I32 iPred = 0;
#if !defined(WMA_OPT_FLOAT_PREDICTOR_XENON) 
    I32 i;
    // I keep rgiFilter in I16 in order to pack more data together to get a faster LMSPredictorUpdateI32
    // Certainly this will cause extra work to pack I16 to I32 struture. But it is feasiable by punpck instruction.
    I16 * rgiFilter = pLMSPredictor->m_rgiFilter;
    I32 * rgiPrevVal = (I32 *)pLMSPredictor->m_rgiPrevVal + pLMSPredictor->m_iRecent;

    I32 iPred0 = 0, iPred1 = 0, iPred2 = 0, iPred3 = 0;
    for (i = 0; i < pLMSPredictor->m_iOrder_Div_8; i++) {
        iPred0 += (I32)rgiFilter[0] * rgiPrevVal[0];
        iPred1 += (I32)rgiFilter[1] * rgiPrevVal[1];
        iPred2 += (I32)rgiFilter[2] * rgiPrevVal[2];
        iPred3 += (I32)rgiFilter[3] * rgiPrevVal[3];
        iPred0 += (I32)rgiFilter[4] * rgiPrevVal[4];
        iPred1 += (I32)rgiFilter[5] * rgiPrevVal[5];
        iPred2 += (I32)rgiFilter[6] * rgiPrevVal[6];
        iPred3 += (I32)rgiFilter[7] * rgiPrevVal[7];
        rgiFilter += 8;
        rgiPrevVal += 8;
    }
    iPred = (iPred0 + iPred2) + (iPred1 + iPred3);
    iPred += pLMSPredictor->m_iScalingOffset;
    iPred = iPred >> pLMSPredictor->m_iScaling;
#endif
    return (iPred);
}

Void prvLMSPredictorUpdate_I32_C(CAudioObject * pau, LMSPredictor * pLMSPredictor, I32 iInput, I32 iPred)
{
#if !defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
    I32 iPredErr = iInput - iPred;
    I32 iUpdate = 0;

    I16 * rgiFilter = pLMSPredictor->m_rgiFilter;
    I16 * rgiUpdate = pLMSPredictor->m_rgiUpdate;
    I32 * rgiPrevVal = (I32 *)pLMSPredictor->m_rgiPrevVal;

    // actually, we should also control the updating speed based on their position in cascaded struture.
    // The earlier the filter, the slower the updating speed. Because if you update the early filters two fast,
    // the result would be very tough for following filters. Need more consideration.
    if (iPredErr > 0) 
    {
        I32 i = 0;
        for (i = 0; i < pLMSPredictor->m_iOrder; i++) {
            rgiFilter[i] +=  rgiUpdate[i + pLMSPredictor->m_iRecent];
        }
    }
    else if (iPredErr < 0 ){
        I32 i = 0;
        for (i = 0; i < pLMSPredictor->m_iOrder; i++) {
            rgiFilter[i] -=  rgiUpdate[i + pLMSPredictor->m_iRecent];
        }
    }
    assert(pLMSPredictor->m_iRecent >= 0);
    assert(pLMSPredictor->m_iRecent < 2 * pLMSPredictor->m_iOrder);

    if (pLMSPredictor->m_iRecent == 0) {
        memcpy(rgiPrevVal + pLMSPredictor->m_iOrder, rgiPrevVal, sizeof(rgiPrevVal[0]) * pLMSPredictor->m_iOrder);
        memcpy(rgiUpdate + pLMSPredictor->m_iOrder, rgiUpdate, sizeof(rgiUpdate[0]) * pLMSPredictor->m_iOrder);
        pLMSPredictor->m_iRecent = pLMSPredictor->m_iOrder - 1;
    }
    else
        pLMSPredictor->m_iRecent = pLMSPredictor->m_iRecent - 1;
    //  truncate to I16 is used to simulate the MMX behavior since we decided to pack 4 samples together.
    //  results show that the performance loss is small.
    //    pLMSPredictor->m_rgiPrevVal[pLMSPredictor->m_iRecent] = (I16)iInput;
    //    pau->m_iSampleMaxValue = (1 << 23) - 1;
    //    pau->m_iSampleMinValue = -pau->m_iSampleMaxValue;
    //    assert(pau->m_iSampleMaxValue == (1 << 23) - 1);
    //    assert(pau->m_iSampleMinValue == -((1 << 23) - 1));
    if (iInput > pau->m_iSampleMaxValue ) {
        rgiPrevVal[pLMSPredictor->m_iRecent] = (I32)pau->m_iSampleMaxValue;
    }
    else if (iInput < pau->m_iSampleMinValue) {
        rgiPrevVal[pLMSPredictor->m_iRecent] = (I32)pau->m_iSampleMinValue;        
    }
    else
        rgiPrevVal[pLMSPredictor->m_iRecent] = (I32)iInput;

    if (iInput > 0)
        rgiUpdate[pLMSPredictor->m_iRecent] = (I16)pLMSPredictor->m_iUpdStepSize_X_8;
    else if (iInput < 0)
        rgiUpdate[pLMSPredictor->m_iRecent] = - (I16)pLMSPredictor->m_iUpdStepSize_X_8;
    else
        rgiUpdate[pLMSPredictor->m_iRecent] = 0;

    rgiUpdate[pLMSPredictor->m_iRecent + pLMSPredictor->m_iOrder_Div_16] >>= 2;
    rgiUpdate[pLMSPredictor->m_iRecent + pLMSPredictor->m_iOrder_Div_8] >>= 1;
#endif
}

/***
*   Function: prvResetLMSPredictor
*   Purpose: prvResetLMSPredictor is called at codec initialization and seekable points. This function sets the LMS filter's
*       order and other parameters. But it doesn't malloc buffer for filter. That work is done at prvInitLMSPredictor
*   Input:
*   Output: no.
*   Usage: m_iOrder, m_fltLamda, and m_fltUpdLmt should be set before calling this function.
********************************************/

WMARESULT prvResetLMSPredictor(CAudioObject * pau, LMSPredictor * pLMSPrdtr)
{
    WMARESULT wmaResult = WMA_OK;
    
    // Must be less thant LLMB_CLMSFLT_MAX_ORDER which is used to malloc the buffer.
    assert(pLMSPrdtr->m_iOrder <= LLMB_CLMSFLT_MAX_ORDER);
    assert(pLMSPrdtr->m_iOrder >= 8);
    assert((pLMSPrdtr->m_iOrder % 8) == 0);
    
    pLMSPrdtr->m_iOrder_Div_16 = (pLMSPrdtr->m_iOrder >> 4);
    pLMSPrdtr->m_iOrder_Div_8 = (pLMSPrdtr->m_iOrder >> 3);
//  pLMSPrdtr->m_iOrder_Div_4 = (pLMSPrdtr->m_iOrder >> 2);
//  pLMSPrdtr->m_iOrder_Div_2 = (pLMSPrdtr->m_iOrder >> 1);
    pLMSPrdtr->m_iRecent = pLMSPrdtr->m_iOrder;  // at the beginning of the second part of double size buffer.

    assert(pLMSPrdtr->m_rgiFilter != NULL);
    assert(pLMSPrdtr->m_rgiFilterBackup != NULL);
    assert(pLMSPrdtr->m_rgiPrevVal != NULL);
    assert(pLMSPrdtr->m_rgiUpdate != NULL);

    memset(pLMSPrdtr->m_rgiFilter, 0, sizeof(pLMSPrdtr->m_rgiFilter[0]) * pLMSPrdtr->m_iOrder);
    if (pau->m_bSendCDLMS == WMAB_TRUE) {
        I32 i;
        for (i = 0; i < pLMSPrdtr->m_cCoeffsSent; i++) {
            pLMSPrdtr->m_rgiFilter[i] = pLMSPrdtr->m_rgiFilterBackup[i];
        }
    }
    memset(pLMSPrdtr->m_rgiPrevVal, 0, sizeof(pLMSPrdtr->m_rgiPrevVal[0]) * LLMB_CLMSFLT_MAX_ORDER * 2);
    memset(pLMSPrdtr->m_rgiUpdate, 0, sizeof(pLMSPrdtr->m_rgiUpdate[0]) * LLMB_CLMSFLT_MAX_ORDER * 2);

    // TODOCHAO set this to 0 make the update speed after the seek point very big. But seekable require this be 0.
    // pLMSPrdtr->m_iSqSum = 0;
    pLMSPrdtr->m_iScalingOffset = (1 << (pLMSPrdtr->m_iScaling - 1));
    pLMSPrdtr->m_iUpdStepSize = 1;
    pLMSPrdtr->m_iUpdStepSize_X_8 = pLMSPrdtr->m_iUpdStepSize * 8;
    // pLMSPrdtr->m_iUpdStepSize_X_8_Neg = -pLMSPrdtr->m_iUpdStepSize_X_8;
    return wmaResult;

}

Void prvLMSPredictorUpdateSpeedChange(CAudioObject * pau, LMSPredictor * pLMSPredictor, Bool bFast)
{
#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
    Float * rgiUpdate = (Float *)pLMSPredictor->m_rgiUpdate;
#else
    I16 * rgiUpdate = (I16 *)pLMSPredictor->m_rgiUpdate;
#endif

    I16 i = 0;
    if (pau->m_bV3RTM == WMAB_TRUE) {
        rgiUpdate += pLMSPredictor->m_iRecent;
    }

    if (bFast == WMAB_TRUE) {
        pLMSPredictor->m_iUpdStepSize = 2;
        pLMSPredictor->m_iUpdStepSize_X_8 = pLMSPredictor->m_iUpdStepSize * 8;
        // pLMSPredictor->m_iUpdStepSize_X_8_Neg = -pLMSPredictor->m_iUpdStepSize_X_8;
        // Please read the comments in else block.
        for (i = 0; i < pLMSPredictor->m_iOrder; i++) {
#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
            rgiUpdate[i] *= 2;
#else
            rgiUpdate[i] <<= 1;
#endif
        }
    }
    else {
        pLMSPredictor->m_iUpdStepSize = 1;
        pLMSPredictor->m_iUpdStepSize_X_8 = pLMSPredictor->m_iUpdStepSize * 8;
        // pLMSPredictor->m_iUpdStepSize_X_8_Neg = -pLMSPredictor->m_iUpdStepSize_X_8;

        // Following code is used to simulate the original behavior of update updating speed. In original code,
        // once we leave the high speed updating mode, all the filter coefficients are updated normally.
        // But in new code (integerization), since we keep an arry m_rgiUpdate, at the end of high speed,
        // all the element in m_rgiUpdate are actually double of the normal value. If we continue, we are actually 
        // using those doubled updating stepsize to update the filter in normal mode. Therefore, we move it
        // back to its orignal value for normal mode updating. 
        // But this is not mandatory.
        for (i = 0; i < pLMSPredictor->m_iOrder; i++) {
#if defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
            rgiUpdate[i] /= 2;
#else
            rgiUpdate[i] >>= 1;
#endif
        }
    }
}

#endif // (defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM))|| defined (BUILD_WMALSL)

#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
// This noise feedback filter is just a prototype. But the merit of noise feedback coding is
// the decoder doesn't need any change.
Void prvNoiseFeedbackFilterEncode(I32 *rgiInput, I32 iLen, I16 iQuant)
{
    I32 i;
    assert(iQuant > 0);
    for (i = 0; i < iLen; i++) {
        if (rgiInput[i] >= 0)
            rgiInput[i] = (rgiInput[i] + (iQuant >> 1)) / iQuant;
        else
            rgiInput[i] = (rgiInput[i] - (iQuant >> 1)) / iQuant;
    }
}
// Decoder doesn't need any change for noise feedback coding.
Void prvNoiseFeedbackFilterDecode(CBT *rgiInput, I32 iLen, I16 iQuant)
{
    I32 i;
    assert(iQuant > 0);
    for (i = 0; i < iLen; i++) {
        rgiInput[i] = rgiInput[i] * iQuant;
    }
}

#endif // defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
