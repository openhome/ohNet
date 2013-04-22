//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    MsAudio.cpp

Abstract:

    Implementation of public member functions for CAudioObject.

Author:

    Wei-ge Chen (wchen) 16-November-1998

Revision History:

    Sil Sanders (sils) 8-Feb-00 - combine Integer and Float versions and simplify
    This file contains stubs for building BUILD_WMASTD, BUILD_WMAPRO, & BUILD_WMALSL variants.
*************************************************************************/

#if !defined(_WIN32_WCE) && !defined(HITACHI)
#include <time.h>
#endif  // _WIN32_WCE
#include <math.h>
#include <limits.h>
#include "msaudio.h"
#include "stdio.h"
#include "AutoProfile.h"


#if !defined (BUILD_WMALSL)
Void prvFreeMCLMSPredictor(MCLMSPredictor * pMCLMSPrdtr)
{
}

Void prvMCLMSPredictorReset(CAudioObject * pau, 
                            MCLMSPredictor * pMCLMSPrdtr)
{
}

WMARESULT prvInitMCLMSPredictor(CAudioObject * pau, 
                                MCLMSPredictor * pMCLMSPrdtr, I16 iMaxOrder)
{
    return WMA_OK;
}

Void prvMCLMSPredictorUpdate_I16_C(CAudioObject * pau, 
                                   MCLMSPredictor * pMCLMSPredictor, 
                                   CBT * rgiInput, CBT *rgiPred)
{
}

Void prvMCLMSPredictorPred_I16_C(CAudioObject * pau, 
                                 MCLMSPredictor * pMCLMSPredictor, 
                                 CBT *rgiInput, CBT *rgiPred, Bool bDecoder)
{
}


Void prvMCLMSPredictorUpdate_I32_C(CAudioObject * pau, 
                                   MCLMSPredictor * pMCLMSPredictor, 
                                   CBT * rgiInput, CBT *rgiPred)
{
}

Void prvMCLMSPredictorPred_I32_C(CAudioObject * pau, 
                                 MCLMSPredictor * pMCLMSPredictor, 
                                 CBT *rgiInput, CBT *rgiPred, Bool bDecoder)
{
}
#endif // !BUILD_WMALSL

#if !(defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)) && !defined (BUILD_WMALSL)
Void prvFreeLMSPredictor(LMSPredictor * pLMSPrdtr)
{
}

WMARESULT prvResetLMSPredictor(CAudioObject * pau, LMSPredictor * pLMSPrdtr)
{
    return WMA_OK;
}

WMARESULT prvInitLMSPredictor(LMSPredictor * pLMSPrdtr, U16 iMaxOrder, U8 * pMem, I32 * pcbMemUsed, I32 cbMemTtl)
{
    return WMA_OK;
}

I32 prvLMSPredictorPred_I32_C(LMSPredictor * pLMSPredictor)
{
    return 0;
}

Void prvLMSPredictorUpdate_I32_C(CAudioObject * pau, 
                                 LMSPredictor * pLMSPredictor, 
                                 I32 iInput, I32 iPred)
{
}

I32 prvLMSPredictorPred_I16_C(LMSPredictor * pLMSPredictor)
{
    return 0;
}

Void prvLMSPredictorUpdate_I16_C(CAudioObject * pau, 
                                 LMSPredictor * pLMSPredictor, 
                                 I32 iInput, I32 iPred)
{
}

Void prvLMSPredictorUpdateSpeedChange(CAudioObject * pau, 
                                      LMSPredictor * pLMSPredictor,
                                      Bool bFast)
{
}
#endif // !(BUILD_WMAPRO && BUILD_WMAPRO_PLLM) && !BUILD_WMALSL

#if !defined (BUILD_WMASTD)
WMARESULT prvLpcToSpectrum(CAudioObject* pau, 
                           const LpType* rgLpcCoef,
                           PerChannelInfo* ppcinfo)
{
    return WMA_OK;
}

Void    auLsp2lpc(CAudioObject* pau, U8 *lsfQ,
                  LpType *lpc, Int order)
{
}

Void prvInitInverseQuadRootTable (CAudioObject* pau)
{
}
Void gLZLTableInit(Void)
{
}
#endif // BUILD_WMASTD


const int g_silence_LNK4211_lpc = 0;


