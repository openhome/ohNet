//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// This file is needed for decoding both WMA Pro & WMA Lossless, but not for WMA
//*@@@---@@@@******************************************************************
#include <math.h>
#include <stdio.h>
#include "msaudio.h"
#include "msaudiodec.h"

#if defined (_DEBUG)
#define COUNT_BITS(a,b) a += b
#else
#define COUNT_BITS(a,b)
#endif

#define MIN(a,b) ((a) > (b) ? b : a)
#define MAX(a,b) ((a) > (b) ? a : b)


#if defined (BUILD_WMAPRO) || defined (BUILD_WMALSL)
Void prvSubFrameDeQuantize(CAudioObject *pau)
{
    I16 iCh;
    I32 i;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo * ppcinfo = pau->m_rgpcinfo + iChSrc;
        const I32 iLen = ppcinfo->m_cSubFrameSampleHalf;
        // add the offset of subframe from m_rgiCoefRecon.
        // This looks weird. We assign Recon buffer for Input. Check the explanation in interdecorr
        CBT * rgiInput = ppcinfo->m_rgiCoefRecon + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];
        for (i = 0; i < iLen; i++) {
            rgiInput[i] = (I32)((I32)rgiInput[i] * pau->m_bPLLMQStepSize);
        }
    }
}  // prvSubFrameDeQuantize

// Recover the DC in each channel.
WMARESULT prvSubFrameRestoreChannelDC(CAudioObject *pau)
{
    WMARESULT hr = WMAB_TRUE;
    I16 iCh;
    I32 i;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo * ppcinfo = pau->m_rgpcinfo + iChSrc;
        const I32 iLen = ppcinfo->m_cSubFrameSampleHalf;
        // This looks weird. We assign Recon buffer for Input. Check the explanation in interdecorr
        CBT * rgiInput = ppcinfo->m_rgiCoefRecon + ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameStart[0];

        switch (pau->m_iACFilterOrder) {
        case 1:
            {
                rgiInput[0] = (I32)((I32)rgiInput[0] + ((pau->m_iACFilter[0] * ppcinfo->m_iLastSamples[0]) >> pau->m_iACFilterScaling));
                for (i = 1; i < iLen; i++) {
                    rgiInput[i] = (I32)((I32)rgiInput[i] + ((pau->m_iACFilter[0] * (I32)rgiInput[i - 1]) >> pau->m_iACFilterScaling));
                }
                ppcinfo->m_iLastSamples[0] = (I32)rgiInput[iLen - 1];
                break;
            }
        case 2:
            {
                rgiInput[0] = (I32)((I32)rgiInput[0] + ((pau->m_iACFilter[0] * ppcinfo->m_iLastSamples[0] + pau->m_iACFilter[1] * ppcinfo->m_iLastSamples[1]) >> pau->m_iACFilterScaling));
                rgiInput[1] = (I32)((I32)rgiInput[1] + ((pau->m_iACFilter[0] * (I32)rgiInput[0] + pau->m_iACFilter[1] * ppcinfo->m_iLastSamples[0]) >> pau->m_iACFilterScaling));
                
                for (i = 2; i < iLen; i++) {
                    rgiInput[i] = (I32)((I32)rgiInput[i] + 
                       ((pau->m_iACFilter[0] * (I32)rgiInput[i - 1] + pau->m_iACFilter[1] * (I32)rgiInput[i - 2]) >> pau->m_iACFilterScaling));
                }
                ppcinfo->m_iLastSamples[0] = (I32)rgiInput[iLen - 1];
                ppcinfo->m_iLastSamples[1] = (I32)rgiInput[iLen - 2];
                break;
            }
        default:
            {
                I16 j;
                I32 iPredictedVal = 0;
                assert(pau->m_iACFilterOrder <= LLM_VERB_ACFILTER_ORDER_MAX);
                assert(pau->m_iACFilterOrder > 2);

                for (i = 0; i < pau->m_iACFilterOrder ; i++) {
                    iPredictedVal = 0;
                    for (j = 0; j < pau->m_iACFilterOrder; j++) {
                        if (i > j)
                            iPredictedVal += pau->m_iACFilter[j] * (I32)rgiInput[i - j - 1];
                        else
                            iPredictedVal += pau->m_iACFilter[j] * ppcinfo->m_iLastSamples[j - i];
                    }
                    rgiInput[i] = (I32)((I32)rgiInput[i] + (iPredictedVal >> pau->m_iACFilterScaling));
                }

                for (i = pau->m_iACFilterOrder; i < iLen; i++) {
                    iPredictedVal = 0;
                    for (j = 0; j < pau->m_iACFilterOrder; j++) {
                        iPredictedVal += pau->m_iACFilter[j] * (I32)rgiInput[i - j - 1];
                    }
                    rgiInput[i] = (I32)((I32)rgiInput[i] + (iPredictedVal >> pau->m_iACFilterScaling));
                }
                for (i = 0 ; i < pau->m_iACFilterOrder; i++) {
                    ppcinfo->m_iLastSamples[i] = (I32)rgiInput[iLen - 1 - i];
                }

                break;
            }
       }
    }
    return hr;
} // prvSubFrameRestoreChannelDC

Void prvLPCFilteringInv(CAudioObject *pau, CBT * rgiCoefRecon, I32 * rgiLPCPrevSamples, CBT * rgiLPCResidue, I32 * rgiLPCFilter, I32 iLen, I16 iOrder)
{
    I32 iCoeff, iTap, j, i;
    for (iCoeff = 0; iCoeff < iLen; iCoeff++) {
        I32 temp = 0;
        if (iCoeff < iOrder) {
            if (pau->m_bSeekable == WMAB_TRUE) {
                if (iCoeff == 0) {
                    rgiCoefRecon[0] = (I32)rgiLPCResidue[0];
                }
                if (iCoeff == 1) {
                    rgiCoefRecon[1] = (I32)((I32)rgiLPCResidue[1] + (I32)rgiCoefRecon[0]);
                }
                else if (iCoeff > 1) {
                    rgiCoefRecon[iCoeff] = (I32)((I32)rgiLPCResidue[iCoeff] + (I32)rgiCoefRecon[iCoeff - 1] * 2 -  (I32)rgiCoefRecon[iCoeff - 2]);
                }
                continue;
            }
            else { //unseekable
                temp = 0;
                for (j = 0; j < pau->m_iLPCOrder; j++) {
                    if (iCoeff > j)
                        temp += rgiLPCFilter[j] * (I32)rgiCoefRecon[iCoeff - j - 1];
                    else
                        temp += rgiLPCFilter[j] * rgiLPCPrevSamples[j - iCoeff];
                }
                rgiCoefRecon[iCoeff] = (I32)((I32)rgiLPCResidue[iCoeff] - (temp >> pau->m_iLPCFilterScaling));
                continue;                
            }
        }

        for (iTap = 0; iTap < iOrder; iTap++) {
            temp += 
                ((iCoeff - (iTap + 1)) >= 0? (I32)rgiCoefRecon[iCoeff - (iTap + 1)] : 0) * 
                rgiLPCFilter[iTap];
        }
        rgiCoefRecon[iCoeff] = (I32)((I32)rgiLPCResidue[iCoeff] - (temp >> pau->m_iLPCFilterScaling));
    }
    // take care of case iLPCOrder changed between frames.
    memset(rgiLPCPrevSamples, 0, sizeof(rgiLPCPrevSamples[0]) * LLM_LPC_ORDER);
    assert(iLen >= LLM_LPC_ORDER);
    for (i = iLen - 1, j = 0; i >= iLen - (I32)LLM_LPC_ORDER; i--) {
        rgiLPCPrevSamples[j++] = (I32)rgiCoefRecon[i];
    }
} // prvLPCFilteringInv

#if (defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)) || defined (BUILD_WMALSL)

#if !WMA_OPT_LOSSLESSDECPROLSL_ARM && !defined(WMA_OPT_FLOAT_PREDICTOR_XENON)
//#if !((defined(WMA_TARGET_MIPS) || defined(WMA_TARGET_SH4)) && defined(PLATFORM_SPECIFIC_LOSSLESSDECPROLSL))
Void prvDecLMSPredictor_I16_C(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen)
{
    I32 iPredErr;
    I32 iInput;
    I32 iPred;
    I16 * rgiFilterBuf = pLMSPredictor->m_rgiFilter;
    I16 * rgiUpdateRdBuf = pLMSPredictor->m_rgiUpdate;
    I16 * rgiPrevValRdBuf = (I16 *)pLMSPredictor->m_rgiPrevVal;
   
    I32 iOrder = pLMSPredictor->m_iOrder;
    I32 iOrder_Div_8 = pLMSPredictor->m_iOrder_Div_8;
    I32 iOrder_Div_16 = pLMSPredictor->m_iOrder_Div_16;
    I32 iOrder_X_2 = iOrder + iOrder;
    I32 iRecent = pLMSPredictor->m_iRecent;
    I32 iScalingOffset = pLMSPredictor->m_iScalingOffset;
    I32 iScaling = pLMSPredictor->m_iScaling;
   
    I16 iUpdStepSize_X_8 = (I16)pLMSPredictor->m_iUpdStepSize_X_8;
    I32 i;
    I32 j;

    I16 * rgiFilter;
    I16 * rgiPrevVal;   
    I16 * rgiUpdate;

    //TODO: update rgiUpdate and rgiPrevVal in very iteration.
    for (i = 0; i < iLen; i++) {
        iPredErr = (I32)*rgiResidue;

        rgiFilter = rgiFilterBuf;
        rgiPrevVal = rgiPrevValRdBuf + iRecent;

        iPred = iScalingOffset;
        for (j = 0; j < iOrder_Div_8; j++) {
            iPred += (I32)(rgiFilter[0]) * (I32)(rgiPrevVal[0]) + (I32)(rgiFilter[1]) * (I32)(rgiPrevVal[1]);
            iPred += (I32)(rgiFilter[2]) * (I32)(rgiPrevVal[2]) + (I32)(rgiFilter[3]) * (I32)(rgiPrevVal[3]);
            iPred += (I32)(rgiFilter[4]) * (I32)(rgiPrevVal[4]) + (I32)(rgiFilter[5]) * (I32)(rgiPrevVal[5]);
            iPred += (I32)(rgiFilter[6]) * (I32)(rgiPrevVal[6]) + (I32)(rgiFilter[7]) * (I32)(rgiPrevVal[7]);
            rgiFilter += 8;
            rgiPrevVal += 8;
        }
        iPred = (iPred >> iScaling);

        iInput = iPredErr + iPred;

        rgiFilter = rgiFilterBuf;
        rgiUpdate = rgiUpdateRdBuf + iRecent;

        // actually, we should also control the updating speed based on their position in cascaded struture.
        // The earlier the filter, the slower the updating speed. Because if you update the early filters two fast,
        // the result would be very tough for following filters. Need more consideration.
        if (iPredErr > 0) 
        {
            for (j = 0; j < iOrder; j++) {
                rgiFilter[j] +=  rgiUpdate[j];
            }
        }
        else if (iPredErr < 0 ){
            for (j = 0; j < iOrder; j++) {
                rgiFilter[j] -=  rgiUpdate[j];
            }
        }      

        assert(iRecent >= 0);
        assert(iRecent < 2 * iOrder);

        //BUGBUG in BETA. We cannot take advantge of long buffer (reduce memcpy times) in BETA. It is a BETA bug
        //please check updateSpeed function. In RTM we fix the bug and we can use
        //  memcpy(rgiUpdate + iMaxOrder * 2 - iOrder, rgiUpdate, ...);
        if (iRecent == 0) {
            memcpy(rgiPrevValRdBuf + iOrder, rgiPrevValRdBuf, iOrder_X_2);
            memcpy(rgiUpdateRdBuf + iOrder, rgiUpdateRdBuf, iOrder_X_2);
            iRecent = iOrder - 1;
        }
        else
            iRecent = iRecent - 1;

        rgiPrevVal = rgiPrevValRdBuf + iRecent;
        rgiUpdate = rgiUpdateRdBuf + iRecent;

        //  truncate to I16 is used to simulate the MMX behavior since we decided to pack 4 samples together.
        //  results show that the performance loss is small.
        * rgiPrevVal = ((I16)iInput);   
        if (iInput > 0) {
            * rgiUpdate = iUpdStepSize_X_8;
            if (iInput > (I32)0X00007FFF) {
                * rgiPrevVal = (I16)0X7FFF;
            }
        }
        else if (iInput < 0) {
            * rgiUpdate = - iUpdStepSize_X_8;
            if (iInput < (I32)0XFFFF8000) {
                * rgiPrevVal = (I16)0X8000;        
            }
        }
        else {
            * rgiUpdate = 0;
        }

        rgiUpdate[iOrder_Div_16] >>= 2;
        rgiUpdate[iOrder_Div_8] >>= 1;

        * rgiResidue = iInput;
        rgiResidue = rgiResidue + 1;
    }    
    pLMSPredictor->m_iRecent = iRecent;
} // prvDecLMSPredictor_I16_C

Void prvDecLMSPredictor_I32_C(CAudioObject * pau, LMSPredictor * pLMSPredictor, CBT *rgiResidue, I32 iLen)
{
    I32 iPredErr;
    I32 iInput;
    I32 iPred;
    I16 * rgiFilterBuf = pLMSPredictor->m_rgiFilter;
    I16 * rgiUpdateRdBuf = pLMSPredictor->m_rgiUpdate;
    I32 * rgiPrevValRdBuf = (I32 *)pLMSPredictor->m_rgiPrevVal;
   
    I32 iOrder = pLMSPredictor->m_iOrder;
    I32 iOrder_Div_8 = pLMSPredictor->m_iOrder_Div_8;
    I32 iOrder_Div_16 = pLMSPredictor->m_iOrder_Div_16;
    I32 iOrder_X_2 = iOrder + iOrder;
    I32 iOrder_X_4 = iOrder_X_2 + iOrder_X_2;
    I32 iRecent = pLMSPredictor->m_iRecent;
    I32 iScalingOffset = pLMSPredictor->m_iScalingOffset;
    I32 iScaling = pLMSPredictor->m_iScaling;
   
    I16 iUpdStepSize_X_8 = (I16)pLMSPredictor->m_iUpdStepSize_X_8;
    I32 i;
    I32 j;

    I16 * rgiFilter;
    I32 * rgiPrevVal;
    I16 * rgiUpdate;

    //TODO: update rgiUpdate and rgiPrevVal in very iteration.
    for (i = 0; i < iLen; i++) {
        iPredErr = (I32)*rgiResidue;
        rgiFilter = rgiFilterBuf;
        rgiPrevVal = rgiPrevValRdBuf + iRecent;

        iPred = iScalingOffset;
        for (j = 0; j < iOrder_Div_8; j++) {
            iPred += (I32)rgiFilter[0] * rgiPrevVal[0];
            iPred += (I32)rgiFilter[1] * rgiPrevVal[1];
            iPred += (I32)rgiFilter[2] * rgiPrevVal[2];
            iPred += (I32)rgiFilter[3] * rgiPrevVal[3];
            iPred += (I32)rgiFilter[4] * rgiPrevVal[4];
            iPred += (I32)rgiFilter[5] * rgiPrevVal[5];
            iPred += (I32)rgiFilter[6] * rgiPrevVal[6];
            iPred += (I32)rgiFilter[7] * rgiPrevVal[7];
            rgiFilter += 8;
            rgiPrevVal += 8;
        }
        iPred = iPred >> iScaling;

        iInput = iPredErr + iPred;
        
        rgiFilter = rgiFilterBuf;
        rgiUpdate = rgiUpdateRdBuf + iRecent;

        // actually, we should also control the updating speed based on their position in cascaded struture.
        // The earlier the filter, the slower the updating speed. Because if you update the early filters two fast,
        // the result would be very tough for following filters. Need more consideration.
        if (iPredErr > 0) 
        {
            for (j = 0; j < iOrder; j++) {
                rgiFilter[j] +=  rgiUpdate[j];
            }
        }
        else if (iPredErr < 0 ){
            for (j = 0; j < iOrder; j++) {
                rgiFilter[j] -=  rgiUpdate[j];
            }
        }
        assert(iRecent >= 0);
        assert(iRecent < 2 * iOrder);

        //BUGBUG in BETA. We cannot take advantge of long buffer (reduce memcpy times) in BETA. It is a BETA bug
        //please check updateSpeed function. In RTM we fix the bug and we can use
        //  memcpy(rgiUpdate + iMaxOrder * 2 - iOrder, rgiUpdate, ...);

        if (iRecent == 0) {
            memcpy(rgiPrevValRdBuf + iOrder, rgiPrevValRdBuf, iOrder_X_4);
            memcpy(rgiUpdateRdBuf + iOrder, rgiUpdateRdBuf, iOrder_X_2);
            iRecent = iOrder - 1;
        }
        else
            iRecent = iRecent - 1;

        rgiPrevVal = rgiPrevValRdBuf + iRecent;
        rgiUpdate = rgiUpdateRdBuf + iRecent;


        //  truncate to I16 is used to simulate the MMX behavior since we decided to pack 4 samples together.
        //  results show that the performance loss is small.
        //    pLMSPredictor->m_rgiPrevVal[pLMSPredictor->m_iRecent] = (I16)iInput;
        //    pau->m_iSampleMaxValue = (1 << 23) - 1;
        //    pau->m_iSampleMinValue = -pau->m_iSampleMaxValue;
        //    assert(pau->m_iSampleMaxValue == (1 << 23) - 1);
        //    assert(pau->m_iSampleMinValue == -((1 << 23) - 1));
        * rgiPrevVal = ((I32)iInput);   
        if (iInput > 0) {
            * rgiUpdate = iUpdStepSize_X_8;
            if (iInput > (I32)0X007FFFFF) {
                * rgiPrevVal = (I32)0X007FFFFF;
            }
        }
        else if (iInput < 0) {
            * rgiUpdate = - iUpdStepSize_X_8;
            if (iInput < (I32)0XFF800000) {
                * rgiPrevVal = (I32)0XFF800000;        
            }
        }
        else {
            * rgiUpdate = 0;
        }

        rgiUpdate[iOrder_Div_16] >>= 2;
        rgiUpdate[iOrder_Div_8] >>= 1;

        * rgiResidue = iInput;
        rgiResidue = rgiResidue + 1;

    }    
    pLMSPredictor->m_iRecent = iRecent;
} // prvDecLMSPredictor_I32_C
//#endif
#endif //WMA_OPT_LOSSLESSDECPROLSL_ARM
#endif // (defined (BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM)) || defined (BUILD_WMALSL)

#endif // BUILD_WMAPRO || BUILD_WMALSL
