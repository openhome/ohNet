//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
// 
// This file is needed for decoding WMA Pro streams (not needed for WMA Lossless or WMA)
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


#if defined (BUILD_WMAPRO)
WMARESULT prvDecodeSubFrameChannelResidueMono_Unified_MLLM_Or_PLLM(CAudioObject* pau, CAudioObjectDecoder *paudec,
                            PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;

    I32 iCoeff;
    I32 iResult;
    I16 iTap = 0;
    I32 iResidue;
    I32 iLen;

    assert(WMAB_TRUE == pau->m_bUnifiedLLM);
    assert(pau->m_iVersion >=3);

    if (pau->m_bOutputRawPCM == WMAB_TRUE) {
        // CoefType * rgfltCoefRecon = (CoefType *)ppcinfo->m_rgiCoefRecon;
        CoefType * rgfltCoefRecon = (pau->m_fWMAProHalfTransform) ? (CoefType *) pau->m_rgiCoefReconMLLMOrig : (CoefType *)ppcinfo->m_rgiCoefRecon;
        
        iLen = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;
        for (; pau->m_iCurrReconCoef < iLen; pau->m_iCurrReconCoef++) {
            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, pau->m_nValidBitsPerSample, (U32 *)&iResult));
            if (iResult & ((I32)1 << (pau->m_nValidBitsPerSample - 1)))
                iResult = (~(((I32)1 << (pau->m_nValidBitsPerSample - 1)) - 1)) | iResult;
            rgfltCoefRecon[pau->m_iCurrReconCoef] = COEF_FROM_INT((I32)(iResult << 1));
        }
        goto exit;
    }

    iLen = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;
    for (; paudec->m_iCurrPart < 1; paudec->m_iCurrPart++) {

        // rgiCoefRecon and rgifltCoefRecon actually use the same memory.
        // Use Double memory as I32
        //    I32 * rgiLPCFilter = (I32 *)ppcinfo->m_rgrgdblLLMLPCFilter[paudec->m_iCurrPart];
        I32 * rgiLPCFilter = ppcinfo->m_rgiLPCFilter;            

        //CBT * rgiCoefRecon = ppcinfo->m_rgiCoefRecon + paudec->m_iCurrPart * iLen;
        CBT * rgiCoefRecon = (pau->m_fWMAProHalfTransform) ? (pau->m_rgiCoefReconMLLMOrig  + paudec->m_iCurrPart * iLen ): (ppcinfo->m_rgiCoefRecon + paudec->m_iCurrPart * iLen);
        //CoefType * rgfltCoefRecon = (CoefType *)ppcinfo->m_rgiCoefRecon + paudec->m_iCurrPart * iLen;
        CoefType * rgfltCoefRecon = (pau->m_fWMAProHalfTransform) ? ((CoefType *)pau->m_rgiCoefReconMLLMOrig + paudec->m_iCurrPart * iLen) : ((CoefType *)ppcinfo->m_rgiCoefRecon + paudec->m_iCurrPart * iLen);
        CBT * rgiLPCResidue = rgiCoefRecon; // share the same memory.
        assert(sizeof(I32) == sizeof(Float)); // necessary for memory share.                        
                
        switch (paudec->m_LLMdecsts) 
        {
            case CH_LPC_COEF:

// #ifdef MLLM_LPC
                if (pau->m_bV3RTM == WMAB_TRUE && pau->m_bDoLPC == WMAB_TRUE) {
                    // read LPC coefficients.
                    for (; paudec->m_iCurrLPCCoef < pau->m_iLPCOrder; paudec->m_iCurrLPCCoef++) {
                            I16 cBits = pau->m_iLPCFilterScaling + pau->m_iLPCFilterIntBits;
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, cBits, (U32 *)&iResult));
                            // (I16) just cut the low 16 bits? It must be cut to get the correct sign bit.
                            rgiLPCFilter[paudec->m_iCurrLPCCoef] = ((I32)iResult << (32 - cBits)) >> (32 - cBits);
                    }
                }
// #endif //MLLM_LPC
                paudec->m_LLMdecsts = CH_DIVISOR_WIDTH;

            case CH_DIVISOR_WIDTH:
                // read divisorwidth;
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 5, (U32 *)&iResult));
                assert ( pau->m_nValidBitsPerSample <= 24);
                if (iResult > pau->m_nValidBitsPerSample)
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
                paudec->m_iDivisorWidth = (I16) iResult;
                paudec->m_LLMdecsts = CH_COEF;
                paudec->m_Dec1stSplsts = FIRSTSPL_SIGN_BIT;
                pau->m_iCurrReconCoef = 0; 

            case CH_COEF:
                //test for first coeff
                if (pau->m_bSeekable == WMAB_TRUE) {
                    if (pau->m_iCurrReconCoef == 0) {
                        switch (paudec->m_Dec1stSplsts)
                        {
                        case FIRSTSPL_SIGN_BIT:
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, (UInt)(1), (U32 *)&iResult));
                            paudec->m_1stSplSignBit = iResult;
                            paudec->m_Dec1stSplsts = FIRSTSPL_OTHER_BITS;

                        case FIRSTSPL_OTHER_BITS:
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, (UInt)(pau->m_nValidBitsPerSample), (U32 *)&iResult));
                            iResult = iResult | (paudec->m_1stSplSignBit << pau->m_nValidBitsPerSample);
                            if (iResult & ((I32)1 << (pau->m_nValidBitsPerSample + 1 - 1)))
                                iResult = (~(((I32)1 << (pau->m_nValidBitsPerSample + 1 - 1)) - 1)) | iResult;
                            rgiLPCResidue[0] = (I32)iResult;
                    
                        }
                        pau->m_iCurrReconCoef++;
                    }
                }
                // read subframe coefficients lpc residue.
                for (; pau->m_iCurrReconCoef < iLen; pau->m_iCurrReconCoef++) {
                    switch (paudec->m_Colombdecsts)
                    {
                        case FIRST_PART:
                            while (1) {
                                TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, 1, (U32 *)&iResult));
                        
                                //iResQ should be kept in paudec for decoder onhold/resume reason. 
                                if (iResult == 1)
                                    paudec->m_iResQ++; 
                                else
                                    break;
                            }
                            paudec->m_Colombdecsts = SECOND_PART;

                        case SECOND_PART:
                            iResult = 0;
                            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (&paudec->m_ibstrm, paudec->m_iDivisorWidth, (U32 *)&iResult));
                            // actually iRem does not need to be in paudec. Doing that just to be consistent with iResQ.
                            paudec->m_iRem = iResult;

                    }
                    iResidue = (paudec->m_iResQ << paudec->m_iDivisorWidth) + paudec->m_iRem;
                    rgiLPCResidue[pau->m_iCurrReconCoef] = iResidue;
                    // set up for next coefficient.
                    paudec->m_Colombdecsts = FIRST_PART;
                    paudec->m_iResQ = 0;
                    paudec->m_iRem = 0;
                }
        }

        // reconstruct subframe coefficients
        if (pau->m_bSeekable == WMAB_TRUE) {
            rgiCoefRecon[0] = rgiLPCResidue[0];
            iCoeff = 1;
        }
        else {
            iCoeff = 0;
        }
        for (/*iCoeff*/; iCoeff < iLen; iCoeff++) {
            iResidue = (I32)rgiLPCResidue[iCoeff];
            if (iResidue & 0x01)
                rgiCoefRecon[iCoeff] = (I32)(-((iResidue+1) >> 1));
            else
                rgiCoefRecon[iCoeff] = (I32)((iResidue >> 1));
        }
        // set up for next part. indents show the levels.
        paudec->m_LLMdecsts = CH_LPC_COEF;
            paudec->m_iCurrLPCCoef = 0;
            
            pau->m_iCurrReconCoef = 0;
                paudec->m_Colombdecsts = FIRST_PART;
                    paudec->m_iResQ = 0;
                    paudec->m_iRem = 0;       
    }   
exit:
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;

} // prvDecodeSubFrameChannelResidueMono_Unified_MLLM_Or_PLLM

WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_Or_PLLM(CAudioObject* pau, CAudioObjectDecoder *paudec,
                            PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;

    I32 iCoeff;
    I16 iTap = 0;
    I32 iLen = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;

    // We don't need offset here. In lossy(unified) subframe always overwrite rgiCoefRecon
    // from the beginning. This is different from the pure lossless case which use an offset
    // to make sure subframes in one frame does not overlap in rgiCoefRecon.
    //CBT * rgiCoefRecon = (CBT *)ppcinfo->m_rgiCoefRecon; // + paudec->m_iCurrPart * iLen;
    CBT * rgiCoefRecon = (pau->m_fWMAProHalfTransform) ? (CBT *)pau->m_rgiCoefReconMLLMOrig : (CBT *)ppcinfo->m_rgiCoefRecon; // + paudec->m_iCurrPart * iLen;
    //CoefType * rgfltCoefRecon = (CoefType *)ppcinfo->m_rgfltCoefRecon; // + paudec->m_iCurrPart * iLen;
    CoefType * rgCoefRecon = (pau->m_fWMAProHalfTransform) ? (CoefType *)pau->m_rgiCoefReconMLLMOrig : (CoefType *)ppcinfo->m_rgCoefRecon; // + paudec->m_iCurrPart * iLen;
    CBT * rgiLPCResidue = (CBT *)rgiCoefRecon; // share the same memory.
    assert(sizeof(CoefType) <= sizeof(CBT));    
    assert(WMAB_TRUE == pau->m_bUnifiedLLM);
    assert(pau->m_iVersion >=3);

    if (pau->m_bOutputRawPCM == WMAB_FALSE) {        
        if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE && 
            pau->m_bFirstUnifiedPureLLMFrm != WMAB_TRUE &&
            pau->m_bLastUnifiedPureLLMFrm!= WMAB_TRUE) 
        {
            if (paudec->m_bGotValidFilterInfo == WMAB_FALSE) {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);                            
            }
            ASSERTWMA_EXIT(wmaResult, prvDecodeSubFrameReconWindowedFrameMono_Unified_PLLM(paudec, ppcinfo, rgiCoefRecon, rgiCoefRecon, iLen));
        }
        else {
            if (pau->m_bSeekable == WMAB_FALSE)
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);

            if (pau->m_bV3RTM == WMAB_TRUE) {
        // #ifdef MLLM_LPC
                ASSERTWMA_EXIT(wmaResult, prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_LPC(pau, ppcinfo, rgiCoefRecon, rgiCoefRecon, iLen));
        // #endif //MLLM_LPC
            }
            else { //V3 beta bits.
        // #ifdef MLLM_POLY
                ASSERTWMA_EXIT(wmaResult, prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_POLY(pau, ppcinfo, rgiCoefRecon, rgiCoefRecon, iLen));
        // #endif //MLLM_POLY
            }
        }        
        // DUMPINTDATATOFILE(rgiCoefRecon,iLen, "c:\\temp\\coefOutput.dat");
        // convert back to float.

        for (iCoeff = 0; iCoeff < iLen; iCoeff++) {
            rgCoefRecon[iCoeff] = COEF_FROM_INT(rgiCoefRecon[iCoeff]); 
        }
    }

    // Take care of HalfTransform in unified WMA (WM Codecs_DSP bug 2824). This checkin
    // finally fixed the problem.
    if (pau->m_fHalfTransform == WMAB_TRUE) {
        prvFixMLLM4HalfTransform(pau, ppcinfo, rgCoefRecon);
    }
    if (pau->m_fPad2XTransform == WMAB_TRUE) 
    {
        // In place computation.
        for (iCoeff = iLen - 1; iCoeff >= 0; iCoeff--) 
        {
            const CoefType tmp = (CoefType) (rgCoefRecon[ iCoeff ] / 1.414F);
            rgCoefRecon[ iCoeff + iCoeff     ] = tmp;
            rgCoefRecon[ iCoeff + iCoeff + 1 ] = tmp;
        }
    }

exit:
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;

} // prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_Or_PLLM

WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_PLLM(CAudioObjectDecoder * paudec,
                                                       PerChannelInfo * ppcInfoComm, 
                                                       // actually rgiCoefRecon and rgiLPCResidue point to the same memory.
                                                       CBT * rgiCoefRecon, 
                                                       CBT * rgiLPCResidue, 
                                                       I32 iLen)
{
    WMARESULT hr = WMAB_TRUE;
#if defined BUILD_WMAPRO_PLLM
    CAudioObject * pau = paudec->pau;
    I32 i;
    I32 iTemp;


    memcpy(rgiCoefRecon, rgiLPCResidue, sizeof(CBT)*iLen);

    for (i = ppcInfoComm->m_cLMSPredictors - 1; i >= 0; i--) {
        LMSPredictor * pLMSPredictor = ppcInfoComm->m_rgLMSPredictors + i;
        paudec->pprvDecLMSPredictor(pau, pLMSPredictor, rgiCoefRecon, iLen);
    }

    if (pau->m_bV3RTM == WMAB_TRUE) {
        I16 iOrder = pau->m_iLPCOrder;
        // I32 * rgiLPCFilter = (I32 *)ppcInfoComm->m_rgrgdblLLMLPCFilter[0];
        I32 * rgiLPCFilter = ppcInfoComm->m_rgiLPCFilter;            
        I32 * rgiLPCPrevSamples = ppcInfoComm->m_rgiLPCPrevSamples;
        // Noise feedback coding.
        prvNoiseFeedbackFilterDecode(rgiCoefRecon, iLen, pau->m_iMLLMResidueQStepSize);        
        if (pau->m_bDoLPC == WMAB_TRUE) {
            prvLPCFilteringInv(pau, rgiCoefRecon, rgiLPCPrevSamples, rgiCoefRecon, rgiLPCFilter, iLen, iOrder);
        }
    }
    else {
        if (pau->m_bSeekable == WMAB_TRUE)
            rgiCoefRecon[0] = rgiCoefRecon[0];
        else
            rgiCoefRecon[0] = (I32)rgiCoefRecon[0] + ((ppcInfoComm->m_iLastSamples[0] * pau->m_iACFilter[0] + (1 << (MLLM_FILTER_SCALING - 1))) >> MLLM_FILTER_SCALING);

        for (i = 1; i < iLen; i++) {
            rgiCoefRecon[i] = (I32)rgiCoefRecon[i] + (((I32)rgiCoefRecon[i - 1] * pau->m_iACFilter[0] + (1 << (MLLM_FILTER_SCALING - 1))) >> MLLM_FILTER_SCALING);
        }   
        ppcInfoComm->m_iLastSamples[0] = (I32)rgiCoefRecon[iLen - 1];
    }

    // mapping
    assert(iLen %2 == 0);
    for (i = 0; i < (iLen >> 1); i++) {
        iTemp = (I32)rgiCoefRecon[iLen - 1 - i];
        rgiCoefRecon[iLen - 1 - i] = rgiCoefRecon[i];
        rgiCoefRecon[i] = iTemp;
    }
#endif // defined BUILD_WMAPRO_PLLM

    return(hr);
} // prvDecodeSubFrameReconWindowedFrameMono_Unified_PLLM

WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_LPC(CAudioObject * pau,
                                                       PerChannelInfo * ppcinfo, 
                                                       // actually rgiCoefRecon and rgiLPCResidue point to the same memory.
                                                       CBT * rgiCoefRecon, 
                                                       CBT * rgiLPCResidue, 
                                                       I32 iLen)
{
    WMARESULT hr = WMAB_TRUE;
    // I32 * rgiLPCFilter = (I32 *)ppcinfo->m_rgrgdblLLMLPCFilter[0];
    I32 * rgiLPCFilter = ppcinfo->m_rgiLPCFilter;            
    I32 * rgiLPCPreSamples = ppcinfo->m_rgiLPCPrevSamples;
    // Noise feedback coding.
    prvNoiseFeedbackFilterDecode(rgiCoefRecon, iLen, pau->m_iMLLMResidueQStepSize);        
    if (pau->m_bDoLPC == WMAB_TRUE) {
        prvLPCFilteringInv(pau, rgiCoefRecon, rgiLPCPreSamples, rgiLPCResidue, rgiLPCFilter, iLen, pau->m_iLPCOrder);
    }
    return hr;
} // prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_LPC

WMARESULT prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_POLY(CAudioObject * pau,
                                                       PerChannelInfo * ppcinfo, 
                                                       // actually rgiCoefRecon and rgiLPCResidue point to the same memory.
                                                       CBT * rgiCoefRecon, 
                                                       CBT * rgiLPCResidue, 
                                                       I32 iLen)
{
    WMARESULT hr = WMAB_TRUE;

    I16 iCoeff;
    // Noise feedback coding.
    prvNoiseFeedbackFilterDecode(rgiCoefRecon, iLen, pau->m_iMLLMResidueQStepSize);        

    rgiCoefRecon[0] = rgiCoefRecon[0];
    for (iCoeff = 1; iCoeff < iLen; iCoeff++) {
        rgiCoefRecon[iCoeff] = (I32)((I32)rgiCoefRecon[iCoeff] + (((I32)rgiCoefRecon[iCoeff - 1] * pau->m_iACFilter[0] + (1 << (MLLM_FILTER_SCALING - 1))) >> MLLM_FILTER_SCALING));
    }
    return hr;
} // prvDecodeSubFrameReconWindowedFrameMono_Unified_MLLM_POLY


WMARESULT prvFixMLLM4HalfTransform (CAudioObject * pau, PerChannelInfo* ppcinfo, CoefType * rgfltCoef)
{
    WMARESULT wmaResult = WMA_OK;

#ifdef MLLM_HALFDCT_FILTERBASED

    #define HT_FLTLEN 32  //must use even value.
    #if ((HT_FLTLEN % 4) != 0)
    #error HT_FLTLEN must be 4x.
    #endif

    I32 iDatLen = ppcinfo->m_cSubFrameSampleHalf;
    I32 N = iDatLen;
    I32 iFltLen = HT_FLTLEN;
    I32 i, j;
    
    #define HFF HTFT_FROM_FLOAT
    HTFilterType rgfltHtFilterTable[HT_FLTLEN/2] = 
    {
        HFF(-0.014521f), HFF(-0.015523f), HFF( 0.016673f), HFF( 0.018006f), 
        HFF(-0.019572f), HFF(-0.021436f), HFF( 0.023693f), HFF( 0.026480f), 
        HFF(-0.030011f), HFF(-0.034628f), HFF( 0.040923f), HFF( 0.050018f), 
        HFF(-0.064308f), HFF(-0.090032f), HFF( 0.150053f), HFF( 0.450158f), 
    };
    HTFilterType rgfltHtFilter[HT_FLTLEN];

    CoefType rgfltCoefHead[HT_FLTLEN/4];
    CoefType rgfltCoefTail[HT_FLTLEN/4];

    Float PIOver4N;

    CoefType fltOutput;

    I32 iDatOriInFlt;       //Data's origin's corresponding position in filter
    I32 iFltOriInDat;       //Filter's origin's corresonding position in data
    I32 iDatEndInFlt;       //Data's end's corresponding position in filter

    // Filter length has to be 4x and has to be smaller than quarter of the data len.
    // Actually half the data len is still ok.
    if (iFltLen > iDatLen / 4)
        iFltLen = ((iDatLen / 4) >> 2) << 2; // iFltLen has to be 4x.

    // Data length has to be even.
    assert (iDatLen % 2 == 0);
    // Filter length should not be too small.
    assert (iFltLen >= 4);
    if (iFltLen <= 4)
        iFltLen = 4;
    assert (iFltLen <= HT_FLTLEN);


    // Compute the filter.
    /*
            Filter
                  **                                    **
               ***| ***                              *** |***
           ****   |    ****                      ****    |   ****
          -S------AB------E--                   -S------CD------E--
                  |                                      |
           Data   |                                      |
                  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

           Filter is symmetric and has even length.
           When computing the first output, A corresponds to rgfltCoef[0].
           When computing the last output, D corressponds to rgfltCoef[N-1].

           HT = HTA+HTB
           In HTA matrix, HTA(i,j) = sin(N*a)/(sqrt(2)*N*sin(a), a = pi/(4*N)*(4*i+2*j+3);
           In HTB matrix, HTB(i,j) = sin(N*b)/(sqrt(2)*N*sin(b), b = pi/(4*N)*(4*i-2*j+1);
           Representation here is slightly different from that in hdct due to different
           origin point between C and matlab.

           Notice above equation is slightly different from the equation in matlab script 
           (hdct.m) because matlab index starts from 1 and C starts from 0.

           HTB corresponds to a filter which is rgfltHtFilter here. When i = 0,
                h = sin(N*b)/(sqrt(2)*N*sin(b), b = pi/(4*N)*(-2*j+1).
           Right shift by (M/2-1), S becomes the origin of the filter.
           HTA can actually be computed by applying h on symmetric padding data. 
           (see hdct.m for details).
    */

    if (HT_FLTLEN == iFltLen)
    {
        memcpy (rgfltHtFilter, rgfltHtFilterTable, sizeof(HTFilterType) * (HT_FLTLEN/2));
        for (j = HT_FLTLEN/2; j < HT_FLTLEN; j++)
        {
            rgfltHtFilter[j] = rgfltHtFilterTable[HT_FLTLEN - 1 - j];
        }
    }
    else
    {
        PIOver4N = (Float)(PI / (4 * N));
        for (j = 0; j < iFltLen; j++)
        {
            Float a = (PIOver4N * (-2 * (j - iFltLen / 2 + 1) + 1));
            Float fltCoef;
            // originally it is (sin(N * a) / (NSqrt2 * sin(a))), but somehow there is 
            // sqrt(2) scaling difference if compared with what we get from DCT approach
            // implemented here. So add sqrt(2) back
            fltCoef = (Float)((sin(N * a) / (2 * N * sin(a)))); 
            assert (fabs(fltCoef) <= 1.0f); // we have this assumption in integrization. But our scaling factor is 28.
            // Windowsing. w = 0.5-0.5*cos(2*pi*[0:N-1]/(N-1)), not sure if it is hanning window.
            rgfltHtFilter[j] = HTFT_FROM_FLOAT ((Float)(fltCoef * (0.5f - 0.5f * cos(2 * PI * j / (iFltLen - 1)))));
        }
    }    
    iDatOriInFlt = iFltLen / 2 - 1; // Use S as filter's origin.
    for (i = 0; i < iFltLen / 4; i++)
    {
        fltOutput = (CoefType)0;
        for (j = iDatOriInFlt; j < iFltLen; j++)
        {
            fltOutput += MULT_HTFT(rgfltHtFilter[j], rgfltCoef[j - iDatOriInFlt]);
        }
        for (j = iDatOriInFlt - 1; j >= 0; j--)
        {   // -(x)-1: symmetric padding. 0|-1, 1|-2,...
            fltOutput += MULT_HTFT(rgfltHtFilter[j], rgfltCoef[ -(j - iDatOriInFlt) - 1]);
        }
        rgfltCoefHead[i] = fltOutput;
        iDatOriInFlt -= 2;
    }

    assert (-1 == iDatOriInFlt); // -1 means we need to enter the center region.
    iFltOriInDat = -iDatOriInFlt;
    for (i = iFltLen / 4; i < iDatLen / 2 - iFltLen / 4; i++)
    {
        fltOutput = (CoefType)0;
        for (j = 0; j < iFltLen; j++)
        {
            fltOutput += MULT_HTFT(rgfltHtFilter[j], rgfltCoef[j + iFltOriInDat]);
        }
        // Since iFltOriInDat starts from 1 we are safe to save the result
        // to rgfltCoef[0] and so on.
        rgfltCoef[i - iFltLen / 4] = fltOutput;
        iFltOriInDat += 2;
    }

    // At this time, iFltEndInDat is iDateLen - iFltLen + 1 + iFltLen - 1 = iDateLen,
    // which means we need to enter the tail region.
    assert (iDatLen - iFltLen + 1 == iFltOriInDat);
    iDatEndInFlt = iDatLen - 1 - iFltOriInDat;
    assert (iDatEndInFlt == iFltLen - 2);
    for (i = iDatLen/2 - iFltLen/4; i < iDatLen/2; i++)
    {
        fltOutput = (CoefType)0;
        for (j = 0; j <= iDatEndInFlt; j++)
        {
            fltOutput += MULT_HTFT (rgfltHtFilter[j], rgfltCoef[iDatLen - 1 - iDatEndInFlt + j]);
        }
        for (j = iDatEndInFlt + 1; j < iFltLen; j++)
        {   // N - 1 - (j - iDatEndInFlt - 1): symmetric padding at the end. N|N-1 N+1|N-2
            fltOutput += MULT_HTFT (rgfltHtFilter[j], rgfltCoef[iDatLen - 1 - (j - iDatEndInFlt - 1)]);
        }
        rgfltCoefTail[i - iDatLen / 2 + iFltLen / 4] = fltOutput;
        iDatEndInFlt -= 2;
    }
    assert (iFltLen / 2 - 2 == iDatEndInFlt); 

    memmove(rgfltCoef + iFltLen / 4, rgfltCoef, sizeof(CoefType) * (iDatLen / 2 - iFltLen / 2));
    memcpy(rgfltCoef, rgfltCoefHead, sizeof(CoefType) * iFltLen / 4);
    memcpy(rgfltCoef + iDatLen / 2 - iFltLen / 4, rgfltCoefTail, sizeof(CoefType) * iFltLen / 4);

#endif //#ifdef MLLM_HALFDCT_FILTERBASED

#ifdef MLLM_HALFDCT_TRANSFORMBASED
    (*pau->aupfnDctIV) (rgfltCoef,
        1, NULL, ppcinfo->m_cSubband,
        pau->aupfnFFT, pau->m_hIntelFFTInfo, pau->m_iFrameNumber, ppcinfo->m_iCurrSubFrame,
        pau->m_cFrameSample, ppcinfo->m_cSubFrameSampleHalf * 2);

    (*pau->aupfnDctIV) (rgfltCoef,
        2.0f / (ppcinfo->m_cSubband), NULL, ppcinfo->m_cSubbandAdjusted,
        pau->aupfnFFT, pau->m_hIntelFFTInfo, pau->m_iFrameNumber, ppcinfo->m_iCurrSubFrame,
        pau->m_cFrameSampleAdjusted, ppcinfo->m_cSubFrameSampleHalfAdjusted * 2);
#endif //MLLM_HALFDCT_TRANSFORMBASED
    return wmaResult;
}//prvFixMLLM4HalfTransform

#endif // BUILD_WMAPRO
