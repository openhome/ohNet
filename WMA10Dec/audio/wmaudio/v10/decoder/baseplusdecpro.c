//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include "msaudiodec.h"

#if defined (BUILD_WMAPRO) && defined (BUILD_WMAPROLBRV2)

#include "baseplusdecpro.h"
#include "huffdec.h"

#undef RL_PRINT_SRC
#if defined (RL_PRINT_SRC)
#define DBG_RUNLEVEL_DEC(a,b,c,e)     \
                    if(e) {\
                        WMAPrintf("%d %d %d\n", a, b, c);\
                        FFLUSH (stdout);\
                    }
#pragma COMPILER_MESSAGE(__FILE__ "(43) : Warning - RunLevel Debug Code Enabled.")

#else 
#define DBG_RUNLEVEL_DEC(a,b,c,e)
#endif //DBG_RUNLEVEL_DEC

#define CX_SET_RECON_COEF_BP(ctDst, ctSrc)      \
            if (!ppcinfo->m_bNoDecodeForCx)     \
            {                                   \
                (ctDst) = (ctSrc);              \
            }

AVRT_DATA const U16 g_rgunRunWeightV3[] = {
        0,      1,      2,      3,      0,      1,      2,      0,      1,      0,  
};

AVRT_DATA const U16 g_rgunLevelWeightV3[] = {
        1,      1,      1,      1,      2,      2,      2,      3,      3,      4,  
};

AVRT_DATA const U16 g_rgunHuffDecTblWeightRLCV3[24] = {
    0x8802, 0x0003, 0x8401, 0x8401, 0x8c03, 0x8c03, 0x0002, 0x9006, 
    0x0004, 0x9807, 0x9404, 0x9404, 0xa005, 0x0003, 0x9c09, 0x9c09, 
    0x0004, 0xa800, 0xa408, 0xa408, 0xac0a, 0xac0a, 0xac0b, 0xac0b
};



AVRT_DATA const U16 g_rgunRunMaskV3BP0[] = {
        0,      0,      1,      2,      3,      4,      5,      6,      7,      8,      
        9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     
       19,     20,     21,     22,     23,      0,      1,      2,      3,      4,      
        5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     
       15,     16,     17,      0,      1,      2,      3,      4,      0,      1,      
        2,      0,      1,      0,      1  
};

AVRT_DATA const U16 g_rgunRunMaskV3BP1[] = {
        0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     
       10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     
       20,     21,     22,     23,      0,      1,      2,      3,      4,      5,      
        6,      7,      8,      9,     10,     11,     12,     13,     14,     15,      
        0,      1,      2,      3,      4,      0,      1,      2,      3,      0,      
        1,      2,      0,      1,      0,      1  
};

AVRT_DATA const U16 g_rgunRunMaskV3BP2[] = {
        0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     
       10,     11,      0,      1,      2,      3,      4,      5,      6,      7,      
        0,      1,      2,      3,      4,      0,      1,      2,      3,      0,      
        1,      2,      3,      0,      1,      0,      1  
};

AVRT_DATA const U16 g_rgunRunMaskV3BP3[] = {
        0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     
       10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     
       20,     21,     22,     23,      0,      1,      2,      3,      4,      5,      
        6,      7,      8,      0,      1,      2,      3,      4, 
};

AVRT_DATA const U16 g_rgunLevelMaskV3BP0[] = {
        1,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      2,      2,      2,      3,      3,      3,      3,      3,      
        3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      
        3,      3,      3,      4,      4,      4,      4,      4,      5,      5,      
        5,      6,      6,      7,      7
};

AVRT_DATA const U16 g_rgunLevelMaskV3BP1[] = {
        2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      2,      2,      3,      3,      3,      3,      3,      3,      
        3,      3,      3,      3,      3,      3,      3,      3,      3,      3,      
        4,      4,      4,      4,      4,      5,      5,      5,      5,      6,      
        6,      6,      7,      7,      8,      8
};

AVRT_DATA const U16 g_rgunLevelMaskV3BP2[] = {
        2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      3,      3,      3,      3,      3,      3,      3,      3,      
        4,      4,      4,      4,      4,      5,      5,      5,      5,      6,      
        6,      6,      6,      7,      7,      8,      8

};

AVRT_DATA const U16 g_rgunLevelMaskV3BP3[] = {
        2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      2,      2,      2,      2,      2,      2,      2,      2,      
        2,      2,      2,      2,      3,      3,      3,      3,      3,      3,      
        3,      3,      3,      4,      4,      4,      4,      4
};


AVRT_DATA const U16 g_rgunHuffDecTblMaskRLCV3BP0[104] = {
    0x8803, 0x0003, 0x001e, 0x003d, 0x901b, 0x0003, 0x8c04, 0x8c04, 
    0x0004, 0x000f, 0x941c, 0x941c, 0xa020, 0x0003, 0xa00e, 0x0005, 
    0xa402, 0xa402, 0xa415, 0xa415, 0xa424, 0xa424, 0xa829, 0xa831, 
    0xa02f, 0x0003, 0xa00f, 0xa035, 0xa416, 0xa416, 0xa425, 0xa425, 
    0x0004, 0x9000, 0x9001, 0x0011, 0x0004, 0x981d, 0x9406, 0x9406, 
    0x0004, 0xa010, 0x0006, 0xa021, 0xa419, 0xa419, 0xa82c, 0xa838, 
    0xa430, 0xa430, 0xa82b, 0xa82a, 0x9407, 0x9407, 0x9808, 0x0001, 
    0xa011, 0x0003, 0x9c0b, 0x9c0b, 0xa418, 0xa418, 0xa434, 0xa434, 
    0x0004, 0x9005, 0x000e, 0x0019, 0x9832, 0x0003, 0x942d, 0x942d, 
    0xa022, 0xa014, 0xa013, 0x0001, 0xa426, 0xa426, 0xa427, 0xa427, 
    0x0004, 0x0007, 0x9809, 0x981e, 0x9c0d, 0x9c0d, 0xa017, 0xa012, 
    0x9c0c, 0x9c0c, 0xa036, 0xa023, 0x982e, 0x0003, 0x980a, 0x981f, 
    0x9c33, 0x9c33, 0x0002, 0xa01a, 0xa428, 0xa428, 0xa437, 0xa437
};


AVRT_DATA const U16 g_rgunHuffDecTblMaskRLCV3BP1[116] = {
    0x0004, 0x8802, 0x002e, 0x0059, 0x0004, 0x0013, 0x8c1a, 0x8c1a, 
    0x0004, 0x9805, 0x9404, 0x9404, 0x0004, 0x0007, 0x9c06, 0x9c06, 
    0xa414, 0xa414, 0xa826, 0xa827, 0xa421, 0xa421, 0xa423, 0xa423, 
    0x0004, 0x000f, 0x942f, 0x942f, 0xa036, 0xa00c, 0x0002, 0x0005, 
    0xa437, 0xa437, 0xa415, 0xa415, 0xa416, 0xa416, 0xa438, 0xa438, 
    0x9c07, 0x9c07, 0x0002, 0xa02d, 0xa832, 0xa819, 0xa412, 0xa412, 
    0x0004, 0x9003, 0x9001, 0x0011, 0x0004, 0x0007, 0x9400, 0x9400, 
    0x9c2c, 0x9c2c, 0x9c08, 0x9c08, 0xa00d, 0x0003, 0xa00e, 0xa01f, 
    0xa829, 0xa828, 0xa424, 0xa424, 0x0004, 0x000f, 0x0012, 0x981d, 
    0x9c0a, 0x9c0a, 0x0002, 0x0005, 0xa42e, 0xa42e, 0xa418, 0xa418, 
    0xa439, 0xa439, 0xa417, 0xa417, 0x9c0b, 0x9c0b, 0xa031, 0xa020, 
    0x9c09, 0x9c09, 0x9c34, 0x9c34, 0x902a, 0x901b, 0x0002, 0x000d, 
    0x9833, 0x0003, 0x942b, 0x942b, 0xa00f, 0x0003, 0x9c1e, 0x9c1e, 
    0xa425, 0xa425, 0xa435, 0xa435, 0x9830, 0x0003, 0x941c, 0x941c, 
    0xa011, 0xa013, 0xa010, 0xa022
};

AVRT_DATA const U16 g_rgunHuffDecTblMaskRLCV3BP2[80] = {
    0x0004, 0x0007, 0x0022, 0x0039, 0x901b, 0x9003, 0x8c02, 0x8c02, 
    0x0004, 0x0017, 0x8c0e, 0x8c0e, 0x9417, 0x9417, 0x0002, 0x0009, 
    0x0004, 0xa019, 0x9c11, 0x9c11, 0xa414, 0xa414, 0xa41e, 0xa41e, 
    0xa00d, 0x0003, 0x9c07, 0x9c07, 0xa822, 0xa815, 0xa41a, 0xa41a, 
    0x9404, 0x9404, 0x941f, 0x941f, 0x9001, 0x0003, 0x900f, 0x0009, 
    0x9400, 0x9400, 0x0002, 0x9820, 0xa013, 0xa026, 0x9c1d, 0x9c1d, 
    0x0004, 0x9806, 0x941c, 0x941c, 0x0004, 0xa021, 0x9c24, 0x9c24, 
    0xa40b, 0xa40b, 0xa40a, 0xa40a, 0x8c16, 0x8c16, 0x0002, 0x0009, 
    0x9818, 0x0003, 0x9405, 0x9405, 0x9c08, 0x9c08, 0x9c25, 0x9c25, 
    0x9410, 0x9410, 0x0002, 0x9823, 0xa009, 0xa00c, 0x9c12, 0x9c12
};

AVRT_DATA const U16 g_rgunHuffDecTblMaskRLCV3BP3[88] = {
    0x0004, 0x0023, 0x0032, 0x004d, 0x8c01, 0x8c01, 0x0002, 0x0005, 
    0x941b, 0x941b, 0x9407, 0x9407, 0x0004, 0x000b, 0x980a, 0x0011, 
    0x9c24, 0x9c24, 0xa010, 0x0001, 0xa421, 0xa421, 0xa426, 0xa426, 
    0x9c0d, 0x9c0d, 0xa011, 0x0001, 0xa415, 0xa415, 0xa423, 0xa423, 
    0x9c1e, 0x9c1e, 0xa012, 0xa020, 0x9005, 0x0003, 0x8c02, 0x8c02, 
    0x9408, 0x9408, 0x0002, 0x981d, 0xa025, 0x0003, 0x9c0e, 0x9c0e, 
    0xa417, 0xa417, 0xa418, 0xa418, 0x8c03, 0x8c03, 0x0002, 0x000d, 
    0x941a, 0x941a, 0x980b, 0x0001, 0x9c1f, 0x9c1f, 0x0002, 0xa013, 
    0xa416, 0xa416, 0xa422, 0xa422, 0x9400, 0x9400, 0x980c, 0x0001, 
    0x9c0f, 0x9c0f, 0xa014, 0x0001, 0xa419, 0xa419, 0xa427, 0xa427, 
    0x8c04, 0x8c04, 0x9006, 0x0001, 0x941c, 0x941c, 0x9409, 0x9409
};

DecoderRunLevelTables g_rgDecRunLevelTables[4];

WMARESULT prvGetNextSFRunDEC(Void* pobjin, 
                             PerChannelInfo *ppcinfo,
                             const U16      *rgiRunEntry,
                             const U16      *rgiLevelEntry,
                             const U16      *rgunHuffDecTblMaskRLCV3,
                             const U16      ESC_RUNBITS,
                             const U16      ESC_LEVBITS)
{
    U32 uSign  = 0;     //1 for positive 0 for nonpositive
    I32 iSign  = 0;
    U32 iEntry = 0;     //index to the Vlc table entry
    U32 iResult;
    U16 cBitsTotal;
    WMARESULT     wmaResult = WMA_OK;
    CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pobjin;
    CAudioObject*        pau = paudec->pau;
    CWMAInputBitStream*  pibstrm = paudec->m_pibsPlus;
    DEBUG_ONLY( Bool fPrint = (pau->m_iFrameNumber  == 19 && pau->m_rgpcinfo->m_iCurrSubFrame == 1); );

    switch (paudec->m_maskrlsts)  {
        case VLC:
            TRACEWMA_EXIT(wmaResult, huffDecGet (rgunHuffDecTblMaskRLCV3, paudec->m_pibsPlus,
                &iResult, &iEntry, &uSign));
            TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, iResult));   //flush bits used by huffDecGet
            if (iEntry == 0)
                goto escape;
            if (iEntry == 1)
            {
                /*
                // [1], end of mask for this channel of the subFrame 
                */
                pau->m_iMaskLevel = 0;
                pau->m_cRunOfMaskZeros = (I16) (pau->m_pbp->m_cValidSFBand - pau->m_iCurrReconMaskBand - 1);
            }
            else 
            {
                assert (iEntry >= 2);
                TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(paudec->m_pibsPlus, 1));   //flush the sign bit also
                pau->m_cRunOfMaskZeros = rgiRunEntry [iEntry - 2] & 0x7FFFFFFF;
                assert (pau->m_cRunOfMaskZeros >= 0);
                pau->m_iMaskLevel = rgiLevelEntry [iEntry - 2];
                pau->m_iMaskSign = (I32) (uSign >> 31) - 1;
            }
            break;

        case ESCAPE:
escape:
            paudec->m_maskrlsts = ESCAPE;
            cBitsTotal = ESC_RUNBITS + ESC_LEVBITS + 1; 
            assert (cBitsTotal <= 27);

            TRACEWMA_EXIT(wmaResult, ibstrmGetBits (paudec->m_pibsPlus, cBitsTotal, &iResult));

            cBitsTotal = ESC_RUNBITS +1;
            pau->m_iMaskLevel = (I16) (iResult >> cBitsTotal);
            pau->m_iMaskSign = (I32) (iResult & 0x00000001) - 1;

            pau->m_cRunOfMaskZeros = (I16) (iResult & (0xFFFFFFFF >> (32 - cBitsTotal))) >> 1;
            pau->m_cRunOfMaskZeros &= 0x7FFFFFFF;
            paudec->m_maskrlsts = VLC;
    }

#ifdef WMA_ENTROPY_TEST
    if (g_maskTest) {
        //assert(pau->m_cRunOfMaskZeros != 0 || pau->m_iMaskLevel != 0);
        putEntropyTest(iEntry,
                       pau->m_cRunOfMaskZeros, pau->m_iMaskLevel,
                       pau->m_iMaskSign);
    }
#endif

exit:
    DBG_RUNLEVEL_DEC(g_cBitGet-21,pau->m_cRunOfMaskZeros,pau->m_iMaskLevel,fPrint);
    return wmaResult;
} // prvGetNextSFRunDEC

//*****************************************************************************************
//
// prvDecodeMaskRunLevel
// Performs entropy decoding of scale factors, and adds to prediction.
//*****************************************************************************************

WMARESULT prvBasePlusDecodeScaleFactorRunLevel  (CAudioObjectDecoder* paudec, 
                                  PerChannelInfo* ppcinfo,
                                  Int iBandLim,
                                  PerChannelInfo* ppcinfoPred,
                                  const U16     *rgiRunEntry,
                                  const U16     *rgiLevelEntry,
                                  const U16     *rgunHuffDecTblMaskRLCV3)
{
    I32 *rgiMaskQ             = ppcinfo->m_rgiSFQ;
    CAudioObject *pau = paudec->pau;
    CBasePlusObject *pbp = pau->m_pbp;
    I16* piMaskBand = &pau->m_iCurrReconMaskBand;   
#ifdef DEBUG_DECODE_TRACE
    DEBUG_ONLY( Bool fPrint = (g_ulOutputSamples==0x4e00); )
#else
    DEBUG_ONLY( Bool fPrint = (pau->m_iFrameNumber  <= 10 && pau->m_rgpcinfo->m_iCurrSubFrame == 0); )
#endif
    WMARESULT   wmaResult = WMA_OK;
    Int iBand;
    Int iSFBand;
    const Int cValidSFBand = pbp->m_cValidSFBand;
    const I16* rgiSFBandIndex = pau->m_pbp->m_rgiSFBandIndex;
    I8 *rgiMaskQMarker = pau->m_pbp->m_rgiSFBandMarker;

    I32 *piRefSFQ = NULL; 
    I32 rgiRefSFQSmooth[MAX_SF_BANDS];
    I32 iSFBand2;

#ifdef WMA_ENTROPY_TEST
    if (g_maskTest && *piMaskBand == 0) initEntropyTest();
#endif

    // This function is too frequently called to be profiled
    //FUNCTION_PROFILE(fp);
    //FUNCTION_PROFILE_START(&fp,DECODE_RUN_LEVEL_PROFILE);
    while (*piMaskBand < iBandLim) 
    {
        TRACEWMA_EXIT(wmaResult, prvGetNextSFRunDEC(paudec,
                                                    ppcinfo, 
                                                    rgiRunEntry, 
                                                    rgiLevelEntry, 
                                                    rgunHuffDecTblMaskRLCV3,
                                                    BASEPLUS_MASK_ESC_RUNBITS,
                                                    BASEPLUS_MASK_ESC_LEVBITS));
        pau->m_iMaskLevel = (I16) ((pau->m_iMaskLevel ^ pau->m_iMaskSign) - pau->m_iMaskSign);
        DBG_RUNLEVEL_DEC(g_cBitGet-21,pau->m_cRunOfMaskZeros,pau->m_iMaskLevel,fPrint);
        if ( (*piMaskBand+ pau->m_cRunOfMaskZeros) >= iBandLim) 
        {
            break;
        }

        *piMaskBand += (I16) pau->m_cRunOfMaskZeros;

        // Add to the prediction already available
        rgiMaskQ [*piMaskBand] += pau->m_iMaskLevel; 
        //fprintf(stdout, "\nSF[%d] = %d\n", (Int)*piMaskBand, (Int)rgiMaskQ [*piMaskBand]);
        (*piMaskBand)++;
        paudec->m_maskrlsts = VLC;
    }

exit:
#ifdef WMA_ENTROPY_TEST
    if (g_maskTest &&
        !WMA_FAILED(wmaResult)) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (ppcinfo->m_fIntlvSF)
    {
        Int i = 0;
        I32 rgiMaskQNewOrder[MAX_SF_BANDS];

        if (cValidSFBand > MAX_SF_BANDS)
        {
            ASSERTWMA_EXIT(wmaResult, WMA_E_FAIL);
        }

        // reverse interleaving
        for( iSFBand = 0; iSFBand < cValidSFBand; iSFBand++ ) 
        {
            if (rgiMaskQMarker[iSFBand] == 1)
            {
                rgiMaskQNewOrder[iSFBand] = ppcinfo->m_rgiSFQ[i];
                i++;
            }
        }

        for (iSFBand = 0; iSFBand < cValidSFBand; iSFBand++ )
        {
            if (rgiMaskQMarker[iSFBand] == 0)
            {
                rgiMaskQNewOrder[iSFBand] = ppcinfo->m_rgiSFQ[i];
                i++;
            }
        }
        memcpy(ppcinfo->m_rgiSFQ, rgiMaskQNewOrder, cValidSFBand * sizeof(I32));

        // if TEMPORAL or SPATIAL prediction is used, we need to revert the additional
        // band limited SPECTRAL prediction here.
        if (SFPRED_TEMPORAL == ppcinfo->m_sfPredictionType ||
            SFPRED_SPATIAL  == ppcinfo->m_sfPredictionType)
        {
            rgiMaskQNewOrder[0] = ppcinfo->m_rgiSFQ[0];
            for( iSFBand = 1; iSFBand < cValidSFBand; iSFBand++ ) 
            {
                if (rgiMaskQMarker[iSFBand])
                    rgiMaskQNewOrder[iSFBand] = ppcinfo->m_rgiSFQ[iSFBand];                   
                else
                    rgiMaskQNewOrder[iSFBand] = ppcinfo->m_rgiSFQ[iSFBand] + rgiMaskQNewOrder[iSFBand-1];
            }
            memcpy(ppcinfo->m_rgiSFQ, rgiMaskQNewOrder, cValidSFBand * sizeof(I32));            
        }
        
    }

    if (SFPRED_TEMPORAL == ppcinfo->m_sfPredictionType) 
        piRefSFQ = ppcinfo->m_rgiSFQResampled;
    if (SFPRED_SPATIAL == ppcinfo->m_sfPredictionType)
        piRefSFQ = ppcinfoPred->m_rgiSFQ;

    // smooth referenceSF if intlvsf is on.
    if ((ppcinfo->m_fIntlvSF) &&
        ((SFPRED_TEMPORAL == ppcinfo->m_sfPredictionType) ||
         (SFPRED_SPATIAL == ppcinfo->m_sfPredictionType)
        )
       )
    {
        int iPrevMark = 0;
        int iSFQSum = piRefSFQ[0];
        int iSFQAvg = 0;
        for (iSFBand = 1; iSFBand < cValidSFBand; iSFBand++)
        {
            if (rgiMaskQMarker[iSFBand])
            {
                // compute average
                iSFQAvg = ROUNDF((float)iSFQSum / (iSFBand - iPrevMark));
                // apply average
                for (iSFBand2 = iPrevMark; iSFBand2 < iSFBand; iSFBand2++)
                    rgiRefSFQSmooth[iSFBand2] = iSFQAvg;
                // next bark band.
                iSFQSum = piRefSFQ[iSFBand];
                iPrevMark = iSFBand;
            }
            else
            {
                iSFQSum += piRefSFQ[iSFBand];
            }
        }
        // last bark band
        // compute average
        iSFQAvg = ROUNDF((float)iSFQSum / (iSFBand - iPrevMark));
        // apply average
        for (iSFBand2 = iPrevMark; iSFBand2 < iSFBand; iSFBand2++)
            rgiRefSFQSmooth[iSFBand2] = iSFQAvg;

        piRefSFQ = rgiRefSFQSmooth;
    }

    // Inverse DPCM
    if (SFPRED_TEMPORAL == ppcinfo->m_sfPredictionType)
    {
        // Temporal DPCM
        ppcinfo->m_rgiSFQ[0] += piRefSFQ[0];
        ppcinfo->m_iMaxSFQ = ppcinfo->m_rgiSFQ[0];
        // fprintf(stdout, "SF[%d] %d ", 0, ppcinfo->m_rgiSFQ[0]);
        for (iBand = 1; iBand < pbp->m_cValidSFBand; iBand++)
        {
            ppcinfo->m_rgiSFQ[iBand] += piRefSFQ[iBand];
            ppcinfo->m_iMaxSFQ        = max(ppcinfo->m_iMaxSFQ, ppcinfo->m_rgiSFQ[iBand]);
            //  fprintf(stdout, "SF[%d] %d ", iBand, ppcinfo->m_rgiSFQ[iBand]);
        }
    }
    else if (SFPRED_SPECTRAL == ppcinfo->m_sfPredictionType)
    {
        ppcinfo->m_fAnchorSFAvailable = WMAB_TRUE;
        
        ppcinfo->m_rgiSFQ[0] += (FIRST_V3_MASKQUANT / pbp->m_iSFQMultiplier);
        ppcinfo->m_iMaxSFQ = ppcinfo->m_rgiSFQ[0];
        // fprintf(stdout, "SF[%d] %d ", 0, ppcinfo->m_rgiSFQ[0]);
        for (iBand = 1; iBand < pbp->m_cValidSFBand; iBand++)
        {
            ppcinfo->m_rgiSFQ[iBand] += ppcinfo->m_rgiSFQ[iBand-1];
            ppcinfo->m_iMaxSFQ        = max(ppcinfo->m_iMaxSFQ, ppcinfo->m_rgiSFQ[iBand]);
            //  fprintf(stdout, "SF[%d] %d ", iBand, ppcinfo->m_rgiSFQ[iBand]);
        }
    }
    else
    {
        if (WMAB_FALSE == (SFPRED_SPATIAL == ppcinfo->m_sfPredictionType))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        ppcinfo->m_fAnchorSFAvailable = WMAB_TRUE;
        // Spatial DPCM
        ppcinfo->m_rgiSFQ[0] += piRefSFQ[0];
        ppcinfo->m_iMaxSFQ = ppcinfo->m_rgiSFQ[0];
        // fprintf(stdout, "SF[%d] %d ", 0, ppcinfo->m_rgiSFQ[0]);
        for (iBand = 1; iBand < pbp->m_cValidSFBand; iBand++)
        {
            ppcinfo->m_rgiSFQ[iBand] += piRefSFQ[iBand];
            ppcinfo->m_iMaxSFQ        = max(ppcinfo->m_iMaxSFQ, ppcinfo->m_rgiSFQ[iBand]);
            //  fprintf(stdout, "SF[%d] %d ", iBand, ppcinfo->m_rgiSFQ[iBand]);
        }

    }
    ppcinfo->m_cSubFrameSampleHalfWithSFUpdate = ppcinfo->m_cSubFrameSampleHalf;
    ppcinfo->m_cValidSFBandLatestUpdate = pbp->m_cValidSFBand;
    
    //FUNCTION_PROFILE_STOP(&fp);
    return wmaResult;
} // prvBasePlusDecodeScaleFactorRunLevel


extern I32 g_rgiHoleWidthCodeBook[2]; //defined in baseplus.c

WMARESULT prvDecodeWeightRunLevel  (CAudioObjectDecoder* paudec, 
                                    PerChannelInfo* ppcinfo,
                                    Int iBandLim,
                                    const U16     *rgiRunEntry,
                                    const U16     *rgiLevelEntry,
                                    const U16     *rgunHuffDecTblMaskRLCV3)
{
    //Int* rgiMaskQ             = ppcinfo->m_rgiSFQ;
    WMARESULT   wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;
    CBasePlusObject*  pbp = pau->m_pbp;

    I16 *piMaskBand = &pau->m_iCurrReconMaskBand;   
    I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;  
    I32 *rgiBPCoefWeight = ppcinfo->m_rgiBPWeightFactor;

    I16 iSeg;
    I32 iPrevWeight = 0;

    memset(rgiBPCoefWeight, 0, sizeof(rgiBPCoefWeight[0])*BPPLUS_MAXBADCOEFSEG);
    while (*piMaskBand < iBandLim) 
    {
        TRACEWMA_EXIT(wmaResult, prvGetNextSFRunDEC(paudec,
                                                    ppcinfo, 
                                                    rgiRunEntry, 
                                                    rgiLevelEntry, 
                                                    rgunHuffDecTblMaskRLCV3,
                                                    BASEPLUS_WEIGHT_ESC_RUNBITS,
                                                    BASEPLUS_WEIGHT_ESC_LEVBITS));
        pau->m_iMaskLevel = (I16) ((pau->m_iMaskLevel ^ pau->m_iMaskSign) - pau->m_iMaskSign);
        DBG_RUNLEVEL_DEC(g_cBitGet-21,pau->m_cRunOfMaskZeros,pau->m_iMaskLevel,fPrint);
        if ( (*piMaskBand+ pau->m_cRunOfMaskZeros) >= iBandLim) 
        {
            break;
        }

        *piMaskBand += (I16) pau->m_cRunOfMaskZeros;

        rgiBPCoefWeight[*piMaskBand] = pau->m_iMaskLevel; 
        (*piMaskBand)++;
        paudec->m_maskrlsts = VLC;
    }

    assert(ppcinfo->m_cBadCoefSegs < BPPLUS_MAXBADCOEFSEG);
    for (iSeg = 0; iSeg < ppcinfo->m_cBadCoefSegs; iSeg++)
    {
        rgiBPCoefWeight[iSeg] = rgiBPCoefWeight[iSeg] + iPrevWeight;
        iPrevWeight = rgiBPCoefWeight[iSeg];
    }
    // for debugging only
    if (iSeg < BPPLUS_MAXBADCOEFSEG)
    {
        rgiBPCoefWeight[iSeg] = -1;            
    }
exit:
    return wmaResult;
}
WMARESULT bpdecInit(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = NULL;
    CBasePlusObject* pbp = NULL;
    Int iCh;
    
    if (NULL == paudec ||
        NULL == paudec->pau)
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
    pau = paudec->pau;


    if (pau->m_iVersion < 3 ||
        WMAB_FALSE == pau->m_fBasePlus)
    {
        // No base plus for WMA Standard
        return wmaResult;
    }

    if (NULL == paudec->pau->m_pbp)
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
    pbp = pau->m_pbp;

    paudec->m_fDecodingBPlus = WMAB_FALSE;

    // Per-channel things
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        // Same pointer in each bucket
        paudec->m_rgpcinfo[iCh].m_rgiSFQ    = pbp->m_rgiSFQ   + iCh * MAX_SF_BANDS;
        paudec->m_rgpcinfo[iCh].m_rgiSFQResampled    = pbp->m_rgiSFQResampled   + iCh * MAX_SF_BANDS;
        paudec->m_rgpcinfo[iCh].m_rgiBPWeightFactor = pbp->m_rgiBPWeightFactor + iCh * BPPLUS_MAXBADCOEFSEG;
#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
        paudec->m_rgpcinfo[iCh].m_rgBPCoef  = pbp->m_rgBPCoef + iCh * pau->m_cFrameSampleHalf;
#else
        // do not set m_rgBPCoef as m_rgCoefRecon here since m_rgCoefRecon points to the beginning
        // of the 3/2 buffer now. The value is going to be changed later in auAdaptToSubFrameConfigDEC
        paudec->m_rgpcinfo[iCh].m_rgBPCoef  = NULL;
#endif
        paudec->m_rgpcinfo[iCh].m_fAnchorSFAvailable = WMAB_FALSE;
        paudec->m_rgpcinfo[iCh].m_rgiBPBadCoef = pbp->m_rgiBPBadCoef + iCh * pau->m_cFrameSampleHalf/32;
        paudec->m_rgpcinfo[iCh].m_rgiBadCoefSegPos = pbp->m_rgiBadCoefSegPos + iCh * BPPLUS_MAXBADCOEFSEG * 2;         
    }

    g_rgDecRunLevelTables[0].piIndexToRun = g_rgunRunMaskV3BP0;
    g_rgDecRunLevelTables[0].piIndexToLevel = g_rgunLevelMaskV3BP0;
    g_rgDecRunLevelTables[0].piRunLevelTableDec = g_rgunHuffDecTblMaskRLCV3BP0;

    g_rgDecRunLevelTables[1].piIndexToRun = g_rgunRunMaskV3BP1;
    g_rgDecRunLevelTables[1].piIndexToLevel = g_rgunLevelMaskV3BP1;
    g_rgDecRunLevelTables[1].piRunLevelTableDec = g_rgunHuffDecTblMaskRLCV3BP1;

    g_rgDecRunLevelTables[2].piIndexToRun = g_rgunRunMaskV3BP2;
    g_rgDecRunLevelTables[2].piIndexToLevel = g_rgunLevelMaskV3BP2;
    g_rgDecRunLevelTables[2].piRunLevelTableDec = g_rgunHuffDecTblMaskRLCV3BP2;

    g_rgDecRunLevelTables[3].piIndexToRun = g_rgunRunMaskV3BP3;
    g_rgDecRunLevelTables[3].piIndexToLevel = g_rgunLevelMaskV3BP3;
    g_rgDecRunLevelTables[3].piRunLevelTableDec = g_rgunHuffDecTblMaskRLCV3BP3;

exit:
    return wmaResult;
} // bpdecInit

#if !defined (BIT_DISTRIBUTION_VARS)
#define BIT_DISTRIBUTION_VARS       
#endif
#if !defined (BIT_DISTRIBUTION_PRECHECK)
#define BIT_DISTRIBUTION_PRECHECK
#endif
#if !defined (BIT_DISTRIBUTION_POSTCHECK)
#define BIT_DISTRIBUTION_POSTCHECK   
#endif

#ifdef WMA_ENTCODE_DEBUG
#define CHECK_VALS { \
  if (wmaEntCodeCount == 0) { \
    pDbgFile = FOPEN("coeff", "rb"); \
  } \
  if (!WMA_FAILED(wmaResult) && pDbgFile!=NULL) { \
    int run, level, sign; \
    FREAD(&run, 1, sizeof(Int), pDbgFile); \
    FREAD(&level, 1, sizeof(Int), pDbgFile); \
    FREAD(&sign, 1, sizeof(Int), pDbgFile);  \
    if (sign) sign = 0; \
    else sign = -1; \
    if (pau->m_cRunOfZeros != run || \
        pau->m_iLevel != level || \
        (pau->m_iSign!=sign && level!=0 && 1)) { \
      WMAPrintf("Don't match\n"); \
      assert(0); \
    } \
    wmaEntCodeCount++; \
  } \
}
#else
#define CHECK_VALS
#endif

#define GET_NEXT_RUN_INIT \
  WMARESULT wmaResult = WMA_OK; \
  CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pobjin; \
  CAudioObject*        pau = paudec->pau; \
  CWMAInputBitStream*  pibstrm = paudec->m_pibsPlus; \
  DecRunLevelVecState *pState = &paudec->m_decRunLevelVecState; \
  Int iResult=0


WMARESULT prvGetBPFreqAdaptTblIdx(Void *pobjin,
                                PerChannelInfo *ppcinfo,
                                Int i)
{
    GET_NEXT_RUN_INIT;
    Int idx, last, iTblBits, iNTblBits;

    iTblBits = g_iWmaEntCodeTblBitsV4[i];
    if (pState->iBark >= pau->m_cValidBarkBand)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    if (pState->iBark-pState->iLastSwitchPt[i] >= pState->nTbls[i])
    {
        iNTblBits = CEILLOG2(pau->m_cValidBarkBand-pState->iBark-1);
        TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(pibstrm, 
                                                   1+iNTblBits+iTblBits));
        pState->iLastSwitchPt[i] = pState->iBark;
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 1,
                                               (U32 *)&iResult));
        last = iResult;
        //fprintf(stdout, "\nTBL %d %d\n", iResult, 1);
        TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, iTblBits,
                                               (U32 *)&iResult));
        //fprintf(stdout, "\nTBL %d %d\n", iResult, iTblBits);
        idx = iResult;
        pState->iTblIdx[i] = iResult;
        if (last == 1)
        {
            pState->nTbls[i] = pau->m_cValidBarkBand - pState->iBark;
        }
        else
        {
            if (iNTblBits != 0)
            {
                TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm,
                                                       iNTblBits,
                                                       (U32 *)&iResult));
                //fprintf(stdout, "\nTBL2 %d %d\n", iResult, iNTblBits);
            }
            else
            {
                iResult = 0;
            }
            pState->nTbls[i] = iResult + 1;
            if (pState->nTbls[i] > pau->m_cValidBarkBand-pState->iBark)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
        }
        switch (i)
        {
        case 0:
            pState->huffDecTbl4d = g_wmaHuffDecTbls4d[idx];
            if (g_wmaIsSmallTbl4d[idx])
            {
                pState->iEscVal4d = g_wmaSmallTblMax4d-1;
                pState->uSymToVec4 = g_wmaSmallSymBaseToVec4;
            }
            else
            {
                pState->iEscVal4d = g_wmaVec4NSyms;
                pState->uSymToVec4 = g_wmaSymToVec4;
            }
            break;
        case 1:
            pState->huffDecTbl2d = g_wmaHuffDecTbls2d[idx];
            if (g_wmaIsSmallTbl2d[idx])
            {
                pState->iEscVal2d = g_wmaSmallTblMax2d-1;
                pState->uSymToVec2 = g_wmaSmallSymBaseToVec2;
            }
            else
            {
                pState->iEscVal2d = g_wmaVec2NSyms;
                pState->uSymToVec2 = g_wmaSymToVec2;
            }
            break;
        case 2:
            pState->huffDecTbl1d = g_wmaHuffDecTbls1d[idx];
            if (g_wmaIsSmallTbl1d[idx])
                pState->iEscVal1d = g_wmaSmallTblMax1d-1;
            else
                pState->iEscVal1d = g_wmaVec1NSyms;
            break;
        case 3:
            pState->huffDecTblRL = g_wmaHuffDecTblsRL[idx];
            pState->smallHuffDecTblRL = g_wmaSmallHuffDecTblRL[idx];
            ppcinfo->m_rgiRunEntry = g_wmaRunLevelToRun[idx];
            ppcinfo->m_rgiLevelEntry = g_wmaRunLevelToLevel[idx];
            pState->iEscValRL = g_wmaSmallTblMaxRL[idx];
            pState->smallSymLeafRunLevelToRun =
                g_wmaSmallSymLeafRunLevelToRun[idx];
            pState->smallSymLeafRunLevelToLevel =
                g_wmaSmallSymLeafRunLevelToLevel[idx];
            break;
        }
    }

exit:
    return wmaResult;
} // prvGetBPFreqAdaptTblIdx

#define INCR_BARK \
  if (pState->iCoeff == ppcinfo->m_cSubbandActual) \
  { \
      while (pState->iCoeff > pau->m_rgiBarkIndex[pState->iBark+1]) \
          pState->iBark++; \
  } \
  else \
  { \
      while (pState->iCoeff >= pau->m_rgiBarkIndex[pState->iBark+1]) \
          pState->iBark++; \
  }

INLINE
WMARESULT prvDecodeBPEscapeLargeVal(Int *pSymbol, Int max,
                                  CWMAInputBitStream *pibstrm,
                                  CAudioObjectDecoder* paudec,
                                  DecRunLevelVecState *pState)
{
  WMARESULT wmaResult = WMA_OK;
  U32 iResult;

  while (1) {
    switch (pState->getLargeState) {
    case LargeValBitCnt:
      TRACEWMA_EXIT(wmaResult,
               ibstrmPeekBits(pibstrm, 3, &iResult));
      iResult >>= 32-3;
      if      ((iResult & 0x4)>>2 == 0) {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
        pState->getLargeState = LargeVal8;  // 0xx
      }
      else if ((iResult & 0x6)>>1 == 2) {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 2));
        pState->getLargeState = LargeVal16; // 10x
      }
      else if ((iResult      )    == 6) {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 3));
        pState->getLargeState = LargeVal24; // 110
      }
      else                              {
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 3));
        pState->getLargeState = LargeVal32_1; //111
      }
      break;
    case LargeVal8:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 8, (U32 *)pSymbol));
      goto done;
    case LargeVal16:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 16, (U32 *)pSymbol));
      goto done;
    case LargeVal24:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 24, (U32 *)pSymbol));
      goto done;
    case LargeVal32_1:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 24, (U32 *)&pState->symbol));
      pState->getLargeState = LargeVal32_2;
      // fall through for next 7 bits (LSBs)
    case LargeVal32_2:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 7, (U32 *)pSymbol));
      *pSymbol |= (pState->symbol << 7);
      goto done;
    }
  }

done:
  *pSymbol += max;

  // successs so reset
  pState->getLargeState = LargeValBitCnt;

exit:

  return wmaResult;
} // prvDecodeBPEscapeLargeVal

WMARESULT prvBPEscapeDecodeRunV3(Int *pcRunOfZeros, Int cMaxRun,
                               CWMAInputBitStream *pibstrm)
{
  WMARESULT wmaResult = WMA_OK;
  Int iResult;

  // Look & peek don't alter bitstream state, so do as many times as it takes
  TRACEWMA_EXIT(wmaResult, ibstrmLookForBits(pibstrm, 3 + cMaxRun));
  TRACEWMA_EXIT(wmaResult, ibstrmPeekBits(pibstrm, 3, (U32 *)&iResult));

  //run code:   0    = no run.
  //            10   = 2
  //            110  = cBitMaxRun
  if ((iResult & 0x80000000) == 0)
    {
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
      *pcRunOfZeros = 0;
    }
  else if ((iResult & 0x40000000) == 0)
    {
      //flush and get bits can be combined 
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 2));
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits (pibstrm, 2, (U32 *)&iResult));
      *pcRunOfZeros = iResult + 1;
    }
  else if ((iResult & 0x20000000) == 0)
    {
      //flush and get bits can be combined 
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 3));
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits (pibstrm, cMaxRun, (U32 *)&iResult));
      *pcRunOfZeros = iResult + 4;
    }
  else 
    {
      TRACEWMA_EXIT(wmaResult, WMA_E_BROKEN_FRAME);
    }

exit:
  return wmaResult;
} // prvBPEscapeDecodeRunV3


WMARESULT prvGetNextBPRunDECVecRLV4(Void*           pobjin, 
                                  PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  U32 uSign;
  Int bitCnt, run;

#ifdef WMA_ENTCODE_DEBUG
  if (wmaEntCodeCount >= 8749062) {
    WMAPrintf("");
  }
#endif

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) startEntropyTest();
#endif

  while (1) {
    switch (pState->getState) {
    case FREQADAPTIDX_RL:
      TRACEWMA_EXIT(wmaResult, prvGetBPFreqAdaptTblIdx(pobjin, ppcinfo, 3));
      pState->getState = DECODE_RL;      
      break;
    case DECODE_RL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTblRL,
                             pibstrm,
                             (U32*)&bitCnt, (U32*)&iResult, (U32*)&uSign));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == 0) { // escape
        pState->getState = DECODE_ESC_RLLEVEL;
        pau->m_iSign = 0;
        break;
      }
      else if (iResult == 1) { // end of block
        pau->m_iLevel = 0;
        pau->m_cRunOfZeros = (I16) (ppcinfo->m_cSubbandActual - pau->m_iCurrReconCoef - 1);
        pState->iCoeff = ppcinfo->m_cSubbandActual;
        pau->m_iSign = 0;
        goto done;
      }
      else if (iResult < pState->iEscValRL) { // actual block
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
        run = ppcinfo->m_rgiRunEntry[iResult - 2] & 0x7FFFFFFF;
        pState->curRun += run;
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pState->curRun = 0;
        assert (pau->m_cRunOfZeros >= 0);
        pau->m_iLevel = ppcinfo->m_rgiLevelEntry[iResult - 2];
        pau->m_iSign = (I32)(uSign >> 31) - 1;
        pState->iCoeff += run + 1;
        goto done;
      } else {
        pState->getState = DECODE_RLSMALL;
        break;
      }
    case DECODE_RLSMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->smallHuffDecTblRL, pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, (U32*)&uSign));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, 1));
      run = pState->smallSymLeafRunLevelToRun[iResult] & 0x7FFFFFFF;
      pState->curRun += run;
      pau->m_cRunOfZeros = (I16)pState->curRun;
      pState->curRun = 0;
      assert (pau->m_cRunOfZeros >= 0);
      pau->m_iLevel = pState->smallSymLeafRunLevelToLevel[iResult];
      pau->m_iSign = (I32)(uSign >> 31) - 1;
      pState->iCoeff += run + 1;
      pState->getState = DECODE_RL;
      goto done;
    case DECODE_ESC_RLLEVEL:
      TRACEWMA_EXIT(wmaResult,
                    prvDecodeBPEscapeLargeVal(&iResult, 0,
                                            pibstrm,
                                            paudec, pState));
      pau->m_iLevel = iResult;
      pState->iCoeff++;
      pState->getState = DECODE_ESC_RLRUN;
    case DECODE_ESC_RLRUN:
      TRACEWMA_EXIT(wmaResult,
                    prvBPEscapeDecodeRunV3(&iResult, paudec->m_cMaxRun,
                                         pibstrm));
      pState->iCoeff += iResult;
      pState->curRun += iResult;
      pau->m_cRunOfZeros = (I16)pState->curRun;
      pState->curRun = 0;
      pState->getState = DECODE_ESC_RLSIGN;
    case DECODE_ESC_RLSIGN:
      TRACEWMA_EXIT(wmaResult, ibstrmGetBits(pibstrm, 1, (U32 *)&iResult));
      pau->m_iSign = iResult - 1;
      pState->getState = DECODE_RL;
      goto done;
    }
  }

done:
  if (pState->iCoeff > ppcinfo->m_cSubbandActual)
  {
      REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
  }
  INCR_BARK;
#if 0
  if (pState->iCoeff == ppcinfo->m_cSubbandActual)
      assert(pState->iBark == pau->m_cValidBarkBand);
#endif
  pState->iVecType = 0;
  pState->getState = FREQADAPTIDX_RL;

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest)
    putEntropyTestV3(pau->m_cRunOfZeros, pau->m_iLevel, pau->m_iSign);
#endif

exit:
  CHECK_VALS;

  return wmaResult;
} // prvGetNextBPRunDECVecRLV4


WMARESULT prvGetNextBPRunDECVecNonRLV4(Void*           pobjin, 
                                     PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  Int bitCnt;
  Int cSubband = ppcinfo->m_cSubbandActual;
  Int threshold = cSubband / 256;

#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) startEntropyTest();
#endif

#ifdef WMA_ENTCODE_DEBUG
  if (wmaEntCodeCount >= 8749062) {
    WMAPrintf("");
  }
#endif

  while (1) {
    switch (pState->getState) {
    case FREQADAPTIDX_4D:
      TRACEWMA_EXIT(wmaResult, prvGetBPFreqAdaptTblIdx(pobjin, ppcinfo, 0));
      pState->getState = GET_VEC4;
      break;
    case FREQADAPTIDX_2D:
      TRACEWMA_EXIT(wmaResult, prvGetBPFreqAdaptTblIdx(pobjin, ppcinfo, 1));
      pState->getState = GET_VEC2;
      break;
    case FREQADAPTIDX_1D:
      TRACEWMA_EXIT(wmaResult, prvGetBPFreqAdaptTblIdx(pobjin, ppcinfo, 2));
      pState->getState = GET_VEC1;
      break;
    case GET_VEC4:
      pState->vecIdx = 0;
      if (pau->m_fExpVecsInNonRLMode &&
          pState->cVecsInNonRLMode==ppcinfo->m_iVecsInNonRLMode) {
        pState->getState = DECODE_RL;
        break;
      }
      if (pau->m_iCurrReconCoef + pState->curRun + 1 >= cSubband) { // end of block
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pau->m_iLevel = 0;
        pau->m_iSign = 0;
        goto done;
      }
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTbl4d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->cVecsInNonRLMode++;
      if (iResult == pState->iEscVal4d)
      {
          pState->getState = FREQADAPTIDX_2D;
      }
      else if (iResult < pState->iEscVal4d)
      {
          pState->vec[0] = (pState->uSymToVec4[iResult] >> 12) & 0xf;
          pState->vec[1] = (pState->uSymToVec4[iResult] >>  8) & 0xf;
          pState->vec[2] = (pState->uSymToVec4[iResult] >>  4) & 0xf;
          pState->vec[3] = (pState->uSymToVec4[iResult]      ) & 0xf;
          pState->getState = GET_SIGN4;
      }
      else
      {
          pState->getState = GET_VEC4SMALL;
      }
      break;
    case GET_VEC4SMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(g_wmaSmallHuffDecTbl4d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->vec[0] = (g_wmaSmallSymLeafToVec4[iResult] >> 12) & 0xf;
      pState->vec[1] = (g_wmaSmallSymLeafToVec4[iResult] >>  8) & 0xf;
      pState->vec[2] = (g_wmaSmallSymLeafToVec4[iResult] >>  4) & 0xf;
      pState->vec[3] = (g_wmaSmallSymLeafToVec4[iResult]      ) & 0xf;
      pState->getState = GET_SIGN4;
      break;
    case GET_VEC2:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTbl2d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == pState->iEscVal2d)
      {
          pState->getState = FREQADAPTIDX_1D;
      }
      else if (iResult < pState->iEscVal2d)
      {
          pState->vec[pState->vecIdx]   = (pState->uSymToVec2[iResult] >> 4) & 0xf;
          pState->vec[pState->vecIdx+1] = (pState->uSymToVec2[iResult]     ) & 0xf;
          pState->vecIdx += 2;
          if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      }
      else
      {
          pState->getState = GET_VEC2SMALL;
      }
      break;
    case GET_VEC2SMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(g_wmaSmallHuffDecTbl2d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->vec[pState->vecIdx]   = (g_wmaSmallSymLeafToVec2[iResult] >> 4) & 0xf;
      pState->vec[pState->vecIdx+1] = (g_wmaSmallSymLeafToVec2[iResult]     ) & 0xf;
      pState->vecIdx += 2;
      if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC2; // only allow bark increments on 4d, no need to go to FREQADAPTIDX_2D again
      break;
    case GET_VEC1:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(pState->huffDecTbl1d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      if (iResult == pState->iEscVal1d)
      {
          pState->getState = GET_ESC_VEC1;
      }
      else if (iResult < pState->iEscVal1d)
      {
          pState->vec[pState->vecIdx] = iResult;
          pState->vecIdx++;
          if (pState->vecIdx == 2) pState->getState = GET_VEC2;
          else if (pState->vecIdx == 4) pState->getState= GET_SIGN4;
      }
      else
      {
          pState->getState = GET_VEC1SMALL;
      }
      break;
    case GET_VEC1SMALL:
      TRACEWMA_EXIT(wmaResult,
                    huffDecGet(g_wmaSmallHuffDecTbl1d,
                               pibstrm,
                               (U32*)&bitCnt, (U32*)&iResult, NULL));
      TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, bitCnt));
      pState->vec[pState->vecIdx] = iResult + g_wmaSmallTblMax1d - 1;
      pState->vecIdx++;
      if (pState->vecIdx == 2) pState->getState = GET_VEC2;
      else if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC1;
      break;
    case GET_ESC_VEC1:
      TRACEWMA_EXIT(wmaResult,
                    prvDecodeBPEscapeLargeVal(&iResult, g_wmaVec1NSyms,
                                            pibstrm,
                                            paudec, pState));
      pState->vec[pState->vecIdx] = iResult;
      pState->vecIdx++;
      if (pState->vecIdx == 2) pState->getState = GET_VEC2;
      else if (pState->vecIdx == 4) pState->getState = GET_SIGN4;
      else pState->getState = GET_VEC1;
      break;
    case GET_SIGN4:
      TRACEWMA_EXIT(wmaResult, ibstrmPeekBits(pibstrm, 4, (U32 *)&iResult));
      {
        U32 mask = 0x80000000;
        int cnt = 0;
        if (pState->vec[0] != 0)
          { pState->sgn[0] = (iResult & mask) >> (31-  0); mask >>= 1; cnt++; }
        if (pState->vec[1] != 0)
          { pState->sgn[1] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        if (pState->vec[2] != 0)
          { pState->sgn[2] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        if (pState->vec[3] != 0)
          { pState->sgn[3] = (iResult & mask) >> (31-cnt); mask >>= 1; cnt++; }
        TRACEWMA_EXIT(wmaResult, ibstrmFlushBits(pibstrm, cnt));
      }
      pState->getState = DECODE_NONRL;
      pState->vecIdx = 0;
      pState->iCoeff += 4;
      pState->iVecType = 0;
      INCR_BARK;
      break;
    case DECODE_NONRL:
      if (pState->vec[pState->vecIdx] == 0) {
        pState->vecIdx++;
        pState->curRun++;
        if (pau->m_fExpVecsInNonRLMode == WMAB_FALSE)
          if (pState->curRun > threshold) pState->trip = 1; // after finish
        if (pau->m_iCurrReconCoef + pState->curRun + 1 >= cSubband) { // end of block
          pau->m_cRunOfZeros = (I16)pState->curRun;
          pau->m_iLevel = 0;
          pau->m_iSign = 0;
          goto done;
        }
        if (pState->vecIdx == 4) {
          if (pState->trip) pState->getState = DECODE_RL;
          else pState->getState = FREQADAPTIDX_4D;
        }
      } else {
        if (pau->m_fExpVecsInNonRLMode == WMAB_FALSE)
          if (pState->curRun > threshold) pState->trip = 1; // after finish
        pau->m_cRunOfZeros = (I16)pState->curRun;
        pState->curRun = 0;
        pau->m_iLevel = pState->vec[pState->vecIdx];
        pau->m_iSign = pState->sgn[pState->vecIdx] - 1;
        pState->vecIdx++;
        if (pState->vecIdx == 4) {
          if (pState->trip) pState->getState = DECODE_RL;
          else pState->getState = FREQADAPTIDX_4D;
        }
        goto done;
      }
      break;
    case DECODE_RL:
      pau->aupfnGetNextRun = prvGetNextBPRunDECVecRLV4;
      pState->getState = FREQADAPTIDX_RL;
      TRACEWMA_EXIT(wmaResult,
                    prvGetNextBPRunDECVecRLV4(pobjin, ppcinfo));
      goto exit;
    }
  }

done:
#ifdef WMA_ENTROPY_TEST
  if (!g_maskTest) 
    putEntropyTestV3(pau->m_cRunOfZeros, pau->m_iLevel, pau->m_iSign);
#endif

  CHECK_VALS;

exit:
  return wmaResult;
} // prvGetNextBPRunDECVecNonRLV4


WMARESULT prvGetNextBPRunDECVecTableIndex(Void*           pobjin, 
                                          PerChannelInfo* ppcinfo)
{
  GET_NEXT_RUN_INIT;
  Int i;

  pState->trip = 0;
  pState->getState = GET_VEC4;
  pState->curRun = 0;
  pState->cVecsInNonRLMode = 0;
  pState->iBark = 0;
  pState->iCoeff = 0;
  pState->iVecType = 0;
  for (i=0; i < 4; i++)
  {
      pState->iLastSwitchPt[i] = 0;
      pState->nTbls[i] = 0;
  }

  pState->getState = FREQADAPTIDX_4D;
  pau->aupfnGetNextRun = prvGetNextBPRunDECVecNonRLV4;
  TRACEWMA_EXIT(wmaResult,
                pau->aupfnGetNextRun(pobjin, ppcinfo));

exit:
  return wmaResult;
} // prvGetNextBPRunDECVecTableIndex


WMARESULT prvBasePlusDecodeRLCCoefQ (CAudioObject* pau, 
                                  CAudioObjectDecoder* pcaller, 
                                  PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;

    I32 iResult = 0;
    CoefType* rgiCoefRecon = ppcinfo->m_rgBPCoef;

    CoefType ctCoefLevel;
    CoefType ctCoefRecon;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    Int iHighCutOff = 0;
    Bool fPrint = WMAB_FALSE;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
#ifdef PROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif
    BIT_DISTRIBUTION_VARS;

    if (pbp->m_iExplicitStartPos > 0)
    {
       return prvBasePlusDecodeRLCCoefQ_ExplicitStartPos(pau, pcaller, ppcinfo);
    }

    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] != 0);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);

    // V3 LLM. Chao. Added. LLM mode should not enter this function.
    assert (pau->m_bUnifiedLLM == WMAB_FALSE);
    assert (pau->m_bPureLosslessMode == WMAB_FALSE);

    DEBUG_BREAK_AT_FRAME_DECODE;
    
    if (ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
//    pau->m_iLevel = 0;    
    iHighCutOff = pau->m_cHighCutOff-1;


    BIT_DISTRIBUTION_PRECHECK;
    TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    
    assert(pau->m_cRunOfZeros < SHRT_MAX);

    *piRecon += (I16) (pau->m_cRunOfZeros+1);

    //INTEGER_ONLY( iShift = 0; )
    while (*piRecon < iHighCutOff) {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        do {
            ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                    pau->m_iSign ? -ctCoefLevel : ctCoefLevel ); 

#if (CX_DECODE_MONO==1)
            CX_SET_RECON_COEF_BP(rgiCoefRecon[*piRecon], ctCoefRecon);
#else
            rgiCoefRecon [*piRecon] = ctCoefRecon;
#endif

            BIT_DISTRIBUTION_POSTCHECK;
            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
            BIT_DISTRIBUTION_PRECHECK;
            TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);

            *piRecon += (I16)(pau->m_cRunOfZeros+1);

            
            if (*piRecon >= iHighCutOff)
                break;
            ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);

        } while (WMAB_TRUE);   
    }
    
    // Boundary case
    if (*piRecon == iHighCutOff)
    {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                pau->m_iSign ? -ctCoefLevel : ctCoefLevel ); 

#if (CX_DECODE_MONO==1)
            CX_SET_RECON_COEF_BP(rgiCoefRecon[*piRecon], ctCoefRecon);
#else
            rgiCoefRecon [*piRecon] = ctCoefRecon;
#endif
    
        BIT_DISTRIBUTION_POSTCHECK;
        //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
        MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
        MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
    }

#if defined(WMA_ENTROPY_TEST) && defined(AUINV_RECON_CHANNEL_DEC)
    if (!g_maskTest) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (*piRecon > pau->m_cHighCutOff)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    CHECKWMA_EXIT (wmaResult);

    //assert (*piRecon <= ppcinfo->m_cSubband); 
    
   
exit:

/*  since we do coefficient reordering, we need to compute cLastCodedIndex explicitly later (
    in reordering function).
    // Based on the reason for exiting the above loops, we have different answers.
    if (*piRecon == iHighCutOff)
    {
        ppcinfo->m_cLastCodedIndex = (I16)iHighCutOff+1;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = *piRecon - (I16)(pau->m_cRunOfZeros+1) + 1;
    }
*/
#ifdef PROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // prvBasePlusDecodeRLCCoefQ


WMARESULT prvBasePlusDecodeRLCCoefQ_ExplicitStartPos (CAudioObject* pau, 
                                  CAudioObjectDecoder* pcaller, 
                                  PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;

    I32 iResult = 0;
    CoefType* rgiCoefRecon = ppcinfo->m_rgBPCoef + pbp->m_iExplicitStartPos;

    CoefType ctCoefLevel;
    CoefType ctCoefRecon;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    Int iHighCutOff = 0;
    Int iHighCutOffReal = 0;
    Bool fPrint = WMAB_FALSE;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
#ifdef PROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif
    BIT_DISTRIBUTION_VARS;

    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] != 0);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);

    // V3 LLM. Chao. Added. LLM mode should not enter this function.
    assert (pau->m_bUnifiedLLM == WMAB_FALSE);
    assert (pau->m_bPureLosslessMode == WMAB_FALSE);

    DEBUG_BREAK_AT_FRAME_DECODE;
    
    if (ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    
    iHighCutOff = pau->m_cHighCutOff - 1;
    iHighCutOffReal = pau->m_cHighCutOff - 1 - pbp->m_iExplicitStartPos;

    BIT_DISTRIBUTION_PRECHECK;
    TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    
    assert(pau->m_cRunOfZeros < SHRT_MAX);

    *piRecon += (I16) (pau->m_cRunOfZeros+1);

    //INTEGER_ONLY( iShift = 0; )
    while (*piRecon < iHighCutOff) {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        do {
            if (*piRecon <= iHighCutOffReal)
            {
                ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                        pau->m_iSign ? -ctCoefLevel : ctCoefLevel ); 

    #if (CX_DECODE_MONO==1)
                CX_SET_RECON_COEF_BP(rgiCoefRecon[*piRecon], ctCoefRecon);
    #else
                rgiCoefRecon [*piRecon] = ctCoefRecon;
    #endif
                BIT_DISTRIBUTION_POSTCHECK;
                //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
                MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
                MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
                BIT_DISTRIBUTION_PRECHECK;
            }
            TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);

            *piRecon += (I16)(pau->m_cRunOfZeros+1);
            
            if (*piRecon >= iHighCutOff)
                break;
            ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);

        } while (WMAB_TRUE);   
    }
    
    // Boundary case
    if (*piRecon == iHighCutOff)
    {
        if (*piRecon <= iHighCutOffReal)
        {
            ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
            ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                    pau->m_iSign ? -ctCoefLevel : ctCoefLevel ); 

    #if (CX_DECODE_MONO==1)
                CX_SET_RECON_COEF_BP(rgiCoefRecon[*piRecon], ctCoefRecon);
    #else
                rgiCoefRecon [*piRecon] = ctCoefRecon;
    #endif
        
            BIT_DISTRIBUTION_POSTCHECK;
            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
        }
    }

#if defined(WMA_ENTROPY_TEST) && defined(AUINV_RECON_CHANNEL_DEC)
    if (!g_maskTest) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (*piRecon > pau->m_cHighCutOff)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    CHECKWMA_EXIT (wmaResult);

    //assert (*piRecon <= ppcinfo->m_cSubband); 
    
   
exit:

/*  since we do coefficient reordering, we need to compute cLastCodedIndex explicitly later (
    in reordering function).
    // Based on the reason for exiting the above loops, we have different answers.
    if (*piRecon == iHighCutOff)
    {
        ppcinfo->m_cLastCodedIndex = (I16)iHighCutOff+1;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = *piRecon - (I16)(pau->m_cRunOfZeros+1) + 1;
    }
*/
#ifdef PROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // prvBasePlusDecodeRLCCoefQ_ExplicitStartPos

WMARESULT prvBasePlusDecodeCOEFQRLC_PDFShiftMode (CAudioObject* pau, 
                                  CAudioObjectDecoder* pcaller, 
                                  PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;
    CBasePlusObject *pbp = pau->m_pbp;

    I32 iResult = 0;
    CoefType* rgiCoefRecon = ppcinfo->m_rgBPCoef + pbp->m_iExplicitStartPos;

    CoefType ctCoefLevel;
    CoefType ctCoefRecon;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    Int iHighCutOff = 0;
    Int iHighCutOffReal = 0;
    Bool fPrint = WMAB_FALSE;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);

    I16 iReconReal = -1;
    I16 *rgiRunMapTable = pbp->m_rgi16BPTmpBufC;
    Int cSubband = ppcinfo->m_cSubFrameSampleHalf;
    I32 cSizeRunMapTable = cSubband/BPLUS_MIN_PERIODS_PERSUBFRM_PDFSHIFT * 2;
    //CoefType *rgiBPCoefTemp = (CoefType*)pbp->m_rgiBPCoefTemp;
    //I32 cBPQRLC;
    //I32 iCoef;
    I32 cRun;
    I32 cOut = 0;

    I32 iInsertPos = ppcinfo->m_iInsertPos;
    I32 iPeriod = ppcinfo->m_iPeriod4PDFShift;
    
    I32 iOffset = 0;
    I32 iRun;
    I32 iCurr;

    //I32 cTtlRun;
    //I32 iRecon;

    assert(cSubband/BPLUS_MIN_PERIODS_PERSUBFRM_PDFSHIFT * 2 * sizeof(I16) <= (U32)pau->m_cFrameSampleHalf / 2);
    // pbp->m_rgiBPCoefTemp is malloced as CoefType. Make sure we don't buffer overrun.
    assert(sizeof(I16) * 2 <= sizeof(CoefType));

    cOut = 0;
    cRun = 0;

#ifdef PROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif
    BIT_DISTRIBUTION_VARS;

    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] != 0);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);

    // V3 LLM. Chao. Added. LLM mode should not enter this function.
    assert (pau->m_bUnifiedLLM == WMAB_FALSE);
    assert (pau->m_bPureLosslessMode == WMAB_FALSE);

    DEBUG_BREAK_AT_FRAME_DECODE;
    
    if (ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    // memset(rgiBPCoefTemp, 0, sizeof(CoefType) * cSubband);

    for (iRun = 0; iRun < cSizeRunMapTable; iRun++)
    {
        rgiRunMapTable[iRun] = (I16)iRun;
    }

    iCurr = iInsertPos;
    iOffset = 0;
    while (1)
    {
        assert(iPeriod+iOffset < cSizeRunMapTable);
        assert(iPeriod > iOffset);
        if (iOffset == 0)
        {
            rgiRunMapTable[iCurr++] = (I16)iPeriod;
        }
        else
        {
            rgiRunMapTable[iCurr++] = (I16)(iPeriod - iOffset);
            rgiRunMapTable[iCurr++] = (I16)(iPeriod + iOffset);
        }

        if (iPeriod - iOffset == iInsertPos + iOffset)
            break;

        rgiRunMapTable[iCurr++] = (I16)(iInsertPos + iOffset);

        if (iPeriod - iOffset == iInsertPos + iOffset + 1)
            break;
        
        iOffset++;
    }

//    pau->m_iLevel = 0;
    iHighCutOff = pau->m_cHighCutOff-1;
    iHighCutOffReal = pau->m_cHighCutOff-1-pbp->m_iExplicitStartPos;


    BIT_DISTRIBUTION_PRECHECK;
    TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    
    assert(pau->m_cRunOfZeros < SHRT_MAX);

    *piRecon += (I16) (pau->m_cRunOfZeros+1);
    if (pau->m_cRunOfZeros < cSizeRunMapTable)
        iReconReal += (I16)(rgiRunMapTable[pau->m_cRunOfZeros] + 1);
    else 
        iReconReal += (I16)(pau->m_cRunOfZeros+1);

    //INTEGER_ONLY( iShift = 0; )
    while (*piRecon < iHighCutOff) {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        
        do {
            //rgiCoefRecon [*piRecon] = INTEGER_OR_INT_FLOAT( (ctCoefRecon^pau->m_iSign)-pau->m_iSign, 
            //    pau->m_iSign ? -ctCoefRecon : ctCoefRecon );
            if (iReconReal <= iHighCutOffReal)
            {
                ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                        pau->m_iSign ? -ctCoefLevel : ctCoefLevel ); 
              #if (CX_DECODE_MONO==1)
                CX_SET_RECON_COEF_BP(rgiCoefRecon[iReconReal], ctCoefRecon);
              #else
                rgiCoefRecon [iReconReal] = ctCoefRecon;
              #endif
                BIT_DISTRIBUTION_POSTCHECK;
                //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
                MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[iReconReal]));
                MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[iReconReal]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
                BIT_DISTRIBUTION_PRECHECK;
            }
            TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);

            *piRecon += (I16)(pau->m_cRunOfZeros+1);
            if (pau->m_cRunOfZeros < cSizeRunMapTable)
                iReconReal += (I16)(rgiRunMapTable[pau->m_cRunOfZeros] + 1);
            else 
                iReconReal += (I16)(pau->m_cRunOfZeros+1);

            // note: iReconReal could be > iHighCutOffReal here. For example, in encoder, if last coef is coded,
            // after PDF mapping, total run could be smaller than cSuband. So encoder adds an EOB. Then
            // decoder will decode EOB here and iReconReal becomes > iHighCutOffReal. But there will not be
            // buffer overrun since we always check if (iReconReal <= iHighCutOffReal) before any write
            // operation.
            if (iReconReal < 0) // catch integer overflow. TODO: change iReconReal to U16.
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
            }
    

            if (*piRecon >= iHighCutOff)
                break;

            ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        } while (WMAB_TRUE);   
    }
    
    // Boundary case
    if (*piRecon == iHighCutOff)
    {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        //rgiCoefRecon [*piRecon] = INTEGER_OR_INT_FLOAT( (ctCoefRecon^pau->m_iSign)-pau->m_iSign, 
        //    pau->m_iSign ? -ctCoefRecon : ctCoefRecon );
        if (iReconReal <= iHighCutOffReal)
        {
            ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign,
                                                pau->m_iSign ? -ctCoefLevel : ctCoefLevel );

          #if (CX_DECODE_MONO==1)
            CX_SET_RECON_COEF_BP(rgiCoefRecon[iReconReal], ctCoefRecon);
          #else
            rgiCoefRecon [iReconReal] = ctCoefRecon;
          #endif
          
            BIT_DISTRIBUTION_POSTCHECK;
            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
        }
    }

#if defined(WMA_ENTROPY_TEST) && defined(AUINV_RECON_CHANNEL_DEC)
    if (!g_maskTest) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (*piRecon > pau->m_cHighCutOff)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    CHECKWMA_EXIT (wmaResult);

    //assert (*piRecon <= ppcinfo->m_cSubband); 
    
   
exit:

#ifdef PROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // prvBasePlusDecodeCOEFQRLC_PDFShiftMode

WMARESULT prvBasePlusDecodeRLCCoefQOverlay (CAudioObject* pau, 
                                  CAudioObjectDecoder* pcaller, 
                                  PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;

    I32 iResult = 0;
    I32 iRun; 
    I16 iReconReal = -1; // This is the actual position. piRecon is the position after reorder.
    I32 *rgiBPBadCoef = ppcinfo->m_rgiBPBadCoef;
    CoefType* rgiCoefRecon = ppcinfo->m_rgBPCoef;

    CoefType ctCoefLevel;
    CoefType ctCoefRecon;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    Int iHighCutOff = 0;
    Bool fPrint = WMAB_FALSE;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
#ifdef PROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif
    BIT_DISTRIBUTION_VARS;

    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] != 0);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);

    // V3 LLM. Chao. Added. LLM mode should not enter this function.
    assert (pau->m_bUnifiedLLM == WMAB_FALSE);
    assert (pau->m_bPureLosslessMode == WMAB_FALSE);

    DEBUG_BREAK_AT_FRAME_DECODE;
    
    if (ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
//    pau->m_iLevel = 0;
    iHighCutOff = pau->m_cHighCutOff-1;


    BIT_DISTRIBUTION_PRECHECK;
    TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    
    assert(pau->m_cRunOfZeros < SHRT_MAX);

    *piRecon += (I16) (pau->m_cRunOfZeros+1);

    // find real position.
    iRun = pau->m_cRunOfZeros+1;
    while (iRun)
    {
        // if *piReconReal is at the end and we still have iRun > 0,
        // the current symbol should be EOB and we can safely break here.
        if (iReconReal >= iHighCutOff)
            break;

        if (GETBADCOEFFLAG(rgiBPBadCoef, iReconReal+1))
        {
            iRun--;
        }
        iReconReal++;        
    }

    //INTEGER_ONLY( iShift = 0; )
    while (*piRecon < iHighCutOff) {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        
        do {
            ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                pau->m_iSign ? -ctCoefLevel : ctCoefLevel );

          #if (CX_DECODE_MONO==1)
            CX_SET_RECON_COEF_BP(rgiCoefRecon[iReconReal], ctCoefRecon);
          #else
            rgiCoefRecon [iReconReal] = ctCoefRecon;
          #endif
          

            BIT_DISTRIBUTION_POSTCHECK;
            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[iReconReal]));
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[iReconReal]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
            BIT_DISTRIBUTION_PRECHECK;
            TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);

            *piRecon += (I16)(pau->m_cRunOfZeros+1);

            // find real position.
            iRun = pau->m_cRunOfZeros+1;
            while (iRun)
            {
                // if iReconReal is at the end and we still have iRun > 0,
                // the current symbol should be EOB and we can safely break here.
                // CTODO: probably we use the position of the last bad coef 
                // instead of iHighCutOff for sake of performance.
                if (iReconReal >= iHighCutOff)
                    break;

                if (GETBADCOEFFLAG(rgiBPBadCoef, iReconReal+1))
                {
                    iRun--;
                }
                iReconReal++;       
            }
            
            if (*piRecon >= iHighCutOff)
                break;
            ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        } while (WMAB_TRUE);   
    }
    
    // Boundary case
    if (*piRecon == iHighCutOff)
    {
        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
        ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
            pau->m_iSign ? -ctCoefLevel : ctCoefLevel );

      #if (CX_DECODE_MONO==1)
        CX_SET_RECON_COEF_BP(rgiCoefRecon[iReconReal], ctCoefRecon);
      #else
        rgiCoefRecon [iReconReal] = ctCoefRecon;
      #endif

        BIT_DISTRIBUTION_POSTCHECK;
        //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
        MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
        MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
    }

#if defined(WMA_ENTROPY_TEST) && defined(AUINV_RECON_CHANNEL_DEC)
    if (!g_maskTest) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (*piRecon > pau->m_cHighCutOff)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    CHECKWMA_EXIT (wmaResult);

    //assert (*piRecon <= ppcinfo->m_cSubband); 
    
   
exit:

/*  since we do coefficient reordering, we need to compute cLastCodedIndex explicitly later (
    in reordering function).
    // Based on the reason for exiting the above loops, we have different answers.
    if (*piRecon == iHighCutOff)
    {
        ppcinfo->m_cLastCodedIndex = (I16)iHighCutOff+1;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = *piRecon - (I16)(pau->m_cRunOfZeros+1) + 1;
    }
*/
#ifdef PROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // prvBasePlusDecodeRLCCoefQOverlay

//#define DEBUG_PRINT_COEF
#if defined (DEBUG_PRINT_COEF)
#define DEBUG_PRINT_I32_TILECOEF(fPrint, szText, iArray, cSize) \
    if (fPrint)                                                 \
    {                                                           \
        Int i, iCh, iChSrc;                                     \
        for (iCh=0; iCh < pau->m_cChInTile; iCh++)              \
        {                                                       \
            iChSrc     = pau->m_rgiChInTile[iCh];               \
            ppcinfo    = pau->m_rgpcinfo + iChSrc;              \
            fprintf(stdout, "CH %d %s\n", iChSrc, szText);      \
            for (i = 0; i < cSize; i++)                         \
            {                                                   \
                fprintf(stdout, "%d ", (Int)(iArray)[i]);      \
            }                                                   \
            fprintf(stdout, "\n");                              \
        }                                                       \
    }                                                           \

#else 
#define DEBUG_PRINT_I32_TILECOEF(fPrint, szText, iArray, cSize)
#endif // DEBUG_PRINT_COEF

WMARESULT plusDecodeBasePlusSuperFrameHeader(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;

    I32 iResult;
//#define BASEPLUS_USE_SUPERFRAMEHEADER
#if defined BASEPLUS_USE_SUPERFRAMEHEADER
    PLUS_GETBITS(wmaResult, 4, &iResult);
    assert (0xA == iResult);
#endif

    // reset baseplus decoder state in case of bit stream corruption
    // probably need to create a separate function bpreset.
    paudec->m_fDecodingBPlus = WMAB_FALSE;

    PLUS_GETBITS(wmaResult, 1, &iResult);
    pbp->m_fOverlayMode = iResult;

    if (WMAB_FALSE == pbp->m_fOverlayMode)
    {
        TRACEWMA_EXIT(wmaResult, prvDecodeSFBandTableIndex(paudec));
    
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fScalePriorToChannelXformAtDec);
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fLinearQuantization);
        if (WMAB_FALSE == pbp->m_fLinearQuantization)
        {
            PLUS_GETBITS(wmaResult, 2, &pbp->m_NLQIdx);
            prvBasePlusSetNonLinearQuantizer (pbp); 
        }
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fFrameParamUpdate);
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fUseProMaskRunLevelTbl);
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fLowDelayWindow);
        if (pbp->m_fLowDelayWindow)
        {   
            PLUS_GETBITS(wmaResult, 1, &iResult);
            if (0 == iResult)
            {
                pbp->m_iOverlapWindowDelay = 1;
            }
            else 
            {
                PLUS_GETBITS(wmaResult, 1, &iResult);
                if (0 == iResult)
                    pbp->m_iOverlapWindowDelay = 2;
                else
                    pbp->m_iOverlapWindowDelay = 4;
            }
        }
    }
    else
    {
        PLUS_GETBITS(wmaResult, 1, &pbp->m_iHoleWidthMinIdx);
        PLUS_GETBITS(wmaResult, 1, &pbp->m_iHoleSegWidthMinIdx);
        PLUS_GETBITS(wmaResult, 1, &pbp->m_bSingleWeightFactor);
        PLUS_GETBITS(wmaResult, 2, &pbp->m_iWeightQuantMultiplier);        
        pbp->m_iWeightQuantMultiplier++;
        PLUS_GETBITS(wmaResult, 1, &pbp->m_bWeightFactorOnCodedChannel);        
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fFrameParamUpdate);
    }
exit:
    return wmaResult;
}

WMARESULT bpdecDecodeTile(CAudioObjectDecoder* paudec, U32 uVal)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Fex *pfx = &(pau->m_fex);
    Int iCh;
    Bool fPrint = (pau->m_iFrameNumber == 98);
    I32 iResult = 0;

    assert(pau->m_fBasePlus);

    prvSetCodedChannels(pau);

    if (0 == uVal)
    {
        // set all channels' m_fAnchorSFAvailable to false
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
            ppcinfo->m_fAnchorSFAvailable = WMAB_FALSE;
            if (WMAB_FALSE == pbp->m_fOverlayMode)
            {
                if (prvBasePlusIfBaseIsZero(pau))
                {
                    assert(0 == ppcinfo->m_iPower);
                    assert(1 == ppcinfo->m_cLastCodedIndex);
                    ppcinfo->m_cLastCodedIndexBasePlus = 1;
                }
            }
        }

        if (WMAB_FALSE == pbp->m_fOverlayMode)
        {
            if (prvBasePlusIfBaseIsZero(pau))
            {   // make sure in semiexclusive mode base sets pau->m_cLastCodedIndex correctly.
                assert(1 == pau->m_cLastCodedIndex);
            }
        }

        // reset group and mask for exclusive mode
        if (pau->m_bFreqex &&
            (WMAB_FALSE == pbp->m_fOverlayMode)&&
            prvBasePlusIfBaseIsZero(pau))
        {
            freqexSetChannelDependencyGroup(pau, pbp->m_rgBPChannelGrpInfo,
                                            pbp->m_cBPChannelGroup);
            freqexZeroNonzeroMask(pau); // clear all mask
        }
    }
    else
    {
//#define BPTILE_SYNCBITS_DEBUG
#ifdef BPTILE_SYNCBITS_DEBUG
        PLUS_GETBITS(wmaResult, 8, &iResult);
        assert(0xAA == iResult);
#endif


        // start decoding bplus layer
        paudec->m_fDecodingBPlus = WMAB_TRUE;
        if (pbp->m_fOverlayMode)
        {
            TRACEWMA_EXIT(wmaResult, prvDecodeBasePlusOverlayMode(paudec));
        }
        else
        {
            TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeTileExclusiveMode(paudec));
        }
#ifdef BPTILE_SYNCBITS_DEBUG
        PLUS_GETBITS(wmaResult, 8, &iResult);
        assert(0xAA == iResult);
#endif

        // bplus layer decoding done
        paudec->m_fDecodingBPlus = WMAB_FALSE;
    }      

    // do Not need to add base plus to the base layer since in decoder base plus
    // works on rgCoefRecon buffer directly
    pau->m_iCurrReconMaskBand = 0;
    paudec->m_maskrlsts = VLC;

exit:

    prvSetOrigChannels(pau);
    paudec->m_fDecodingBPlus = WMAB_FALSE;

    // printf("iFrame %d iSubFrm %d cLastCodedIndex %d\n", pau->m_iFrameNumber, pau->m_iCurrTile, pau->m_cLastCodedIndex);
    // baseplus decoding should not come to WMA_E_ONHOLD state. Report bit stream corruption error if so.
    if (WMA_E_ONHOLD == wmaResult)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);            
    }
    return wmaResult;
} // bpdecDecodeTile

WMARESULT prvDecodeBasePlusOverlayMode(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;        
    CBasePlusObject* pbp = pau->m_pbp;
    U32 iResult = 0;
    I32 iCh;
    // 1-5 for finer SF.
    pbp->m_iCurrSFBandTable = 0;
    pbp->m_fLinearQuantization = 1;
    pbp->m_fScalePriorToChannelXformAtDec = 0;                

    prvBasePlusAdaptToSubFrameConfig(pau);
    prvBasePlusDecodeFirstTileHeaderOverlayMode(paudec);

    // Move here since pbp->m_bWeightFactorOnCodedChannel = false mode needs badcoefseg info.
    TRACEWMA_EXIT(wmaResult, prvBasePlusCopyChannelXFormFromBaseCommon(pau));
    TRACEWMA_EXIT(wmaResult, prvBasePlusCopyMaskBandIndexFromBaseOverlay(pau));

    prvBasePlusIdentifyBadlyCodedCoef(pau);

    if (WMAB_FALSE == pbp->m_bWeightFactorOnCodedChannel)
    {
        prvBasePlusDecodeWeightFactorOverlayMode(paudec);
    }


    pbp->m_cBPTileQuant = pau->m_iQuantStepSize;

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        U32 ulPower;
        I16 iChSrc     = pau->m_rgiChInTile[iCh];
        PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;
#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
         memset(ppcinfo->m_rgBPCoef, 0, sizeof(CoefType) * ppcinfo->m_cSubFrameSampleHalf);       
#else
        // set m_rgBPCoef to point to m_rgCoefRecon in decoder.
        if (WMAB_FALSE == ppcinfo->m_bNoDecodeForCx)
            ppcinfo->m_rgBPCoef = ppcinfo->m_rgCoefRecon;
        else
            ppcinfo->m_rgBPCoef = NULL;
#endif
        if (ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate [0])
            memcpy(ppcinfo->m_rgiSFQ, ppcinfo->m_rgiMaskQ, sizeof(Int) * pbp->m_cValidSFBand);
        else
            memcpy(ppcinfo->m_rgiSFQ, ppcinfo->m_rgiMaskQResampled, sizeof(Int) * pbp->m_cValidSFBand);
        // Entropy decode coefficients
        // Is the coded channel zero?
        PLUS_GETBITS(wmaResult, 1, &ulPower);

        ppcinfo->m_iPowerBaseplus = ulPower;
        ppcinfo->m_iPower = ppcinfo->m_iPower || ppcinfo->m_iPowerBaseplus; 

        if (ulPower)
        {
            Int cValidSFBandBackup = pbp->m_cValidSFBand;

            /* Not a syntax restriction.
            // if baselayer coded a channel as silence, baseplus overlay
            // should skip it.
            if (WMAB_FALSE == ppcinfo->m_iPower)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);            
            }
            */
            // get the weight info.
            pau->m_iCurrReconMaskBand = 0;
            paudec->m_maskrlsts = VLC;
            
            // make prvGetNextSFRunDEC work
            pbp->m_cValidSFBand = ppcinfo->m_cBadCoefSegs;

            if (pbp->m_bWeightFactorOnCodedChannel)
            {
                if (pbp->m_bSingleWeightFactor)
                {
                    PLUS_GETBITS(wmaResult, CEILLOG2(MAX_WEIGHT_FACTOR/pbp->m_iWeightQuantMultiplier), &ppcinfo->m_iMaxWeightFactor);
                }
                else
                {
                    TRACEWMA_EXIT(wmaResult, prvDecodeWeightRunLevel  (
                                    paudec, 
                                    ppcinfo,
                                    ppcinfo->m_cBadCoefSegs,
                                    g_rgunRunWeightV3,//g_rgunRunMaskV3BP0,
                                    g_rgunLevelWeightV3, //g_rgunLevelMaskV3BP0,
                                    g_rgunHuffDecTblWeightRLCV3//g_rgunHuffDecTblMaskRLCV3BP0
                                    ));
                }
            }

            pbp->m_cValidSFBand = cValidSFBandBackup;

            paudec->pau->m_iCurrReconCoef = -1;
            pau->aupfnGetNextRun = prvGetNextRunDECVecNonRL;
            prvResetRunLevelState(paudec); // reset run level decoding

            TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeRLCCoefQOverlay (pau, paudec, ppcinfo));       
            //TRACEWMA_EXIT(wmaResult, prvBasePlusUpdateLastCodedCoefIndex (pau, ppcinfo));
        }
        else
        {
            ppcinfo->m_cLastCodedIndexBasePlus = 1;
        }
    }

#ifdef BUILD_WMAPROLBRV3
    // decode base peak
    {
        U16  cLastCodedIndex = pau->m_cLastCodedIndex;

        TRACEWMA_EXIT(wmaResult, plusDecodeBasePeak(paudec));
        for (iCh=0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc     = pau->m_rgiChInTile[iCh];
            PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;

            TRACEWMA_EXIT(wmaResult, plusDecodeBasePeak_Channel(paudec, ppcinfo));
            if( ppcinfo->m_cLastCodedIndex > cLastCodedIndex )
                cLastCodedIndex = ppcinfo->m_cLastCodedIndex;
        }
        if( pau->m_bBasePeakPresentTile )
        {
            for (iCh=0; iCh < pau->m_cChInTile; iCh++)
            {
                I16 iChSrc     = pau->m_rgiChInTile[iCh];
                PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;
                // check if #Segs doesn't reach its max(31)
                if( ppcinfo->m_cBadCoefSegs >= BPPLUS_MAXBADCOEFSEG - 1 )
                {
                    REPORT_BITSTREAM_CORRUPTION_AND_EXIT( wmaResult );
                }
                ppcinfo->m_rgiBadCoefSegPos[ppcinfo->m_cBadCoefSegs*2]   = pau->m_cLastCodedIndex; //start
                ppcinfo->m_rgiBadCoefSegPos[ppcinfo->m_cBadCoefSegs*2+1] = cLastCodedIndex - 1;    //end
                // note: ppcinfo->m_cBadCoefSegs is not incremented here,
                //       it will be done when needed in reconstruction
            }
        }
    }
#endif

    TRACEWMA_EXIT(wmaResult, prvBasePlusReconCoefficients(pau));
#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
    // Add base plus to the base layer.
    TRACEWMA_EXIT(wmaResult, prvBPAddBasePlustoBase(pau));
#endif

#ifdef BUILD_WMAPROLBRV3
    if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2)
    {
        // retrieve mask values which have been modified in base peak coding
        if (pau->m_bBasePeakPresentTile )
        {
            for (iCh=0; iCh < pau->m_cChInTile; iCh++)
            {
                I16 iChSrc     = pau->m_rgiChInTile[iCh];
                PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;

                memcpy(ppcinfo->m_rgiSFQ, ppcinfo->m_piBasePeakMaskQSave, pbp->m_cValidSFBand * sizeof(Int));
            }
        }
    }
#endif
exit:

    // make sure we don't cause trouble for base layer.
    paudec->pau->m_iCurrReconCoef = -1;
    pau->aupfnGetNextRun = prvGetNextRunDECVecNonRL;
    prvResetRunLevelState(paudec); // reset run level decoding

    return wmaResult;
}

WMARESULT prvBasePlusDecodeTileExclusiveMode(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject *pbp = paudec->pau->m_pbp;
    CAudioObject *pau = paudec->pau;
    I32 iCh;

    //What is the (freq) resolution of scale factors?
    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeFirstTileHeaderExclusiveMode(paudec));
    TRACEWMA_EXIT(wmaResult, prvBasePlusDecideStartPositionExclusiveMode(pau));
    prvBasePlusAdaptToSubFrameConfig(paudec->pau);
        
    // Decode channel transform
    TRACEWMA_EXIT(wmaResult, prvBasePlusEntropyDecodeChannelXform(paudec));

    // copy the channel grouping info back to base layer since fex will use it.
    TRACEWMA_EXIT(wmaResult, prvBasePlusCopyChannelXFormToBase(paudec));

    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeTileScaleFactors(paudec));
    
    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeTileQuantStepSize(paudec,
        &pbp->m_cBPTileQuant));
    
    // Channel quantization
    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeChannelQuantStepSize(paudec));

    if (prvBasePlusIfBaseIsZero(pau))
    {
        assert(1 == pau->m_cLastCodedIndex);
        pau->m_cLastCodedIndex = 1;
    }

    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        U32 ulPower;
        I16 iChSrc     = pau->m_rgiChInTile[iCh];
        PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;

        if (0 == ppcinfo->m_iPower)
        {
            assert(1 == ppcinfo->m_cLastCodedIndex);
            ppcinfo->m_cLastCodedIndex = 1;
        }

#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
        assert( ppcinfo->m_rgBPCoef != ppcinfo->m_rgCoefRecon);
#else
        // set m_rgBPCoef to point to m_rgCoefRecon in decoder.
        if (WMAB_FALSE == ppcinfo->m_bNoDecodeForCx)
            ppcinfo->m_rgBPCoef = ppcinfo->m_rgCoefRecon;
        else
            ppcinfo->m_rgBPCoef = NULL;
#endif
        if (WMAB_FALSE == ppcinfo->m_bNoDecodeForCx)
        {
            memset(ppcinfo->m_rgBPCoef + pbp->m_iExplicitStartPos, 0, sizeof(CoefType) * (ppcinfo->m_cSubFrameSampleHalf - pbp->m_iExplicitStartPos));
        }
        // Entropy decode coefficients
        // Is the coded channel zero?
        PLUS_GETBITS(wmaResult, 1, &ulPower);
        // Final power is base power || baseplus power.
        // Encoder guarantee base power >= base plus power.
        // So this line could be redundant. 
        // CTODO: we should separate base power and baseplus power.
        ppcinfo->m_iPowerBaseplus = ulPower;
        ppcinfo->m_iPower = ppcinfo->m_iPower || ppcinfo->m_iPowerBaseplus; 
        if (ulPower)
        {
            U32 bUseToolboxs = 0;
            U32 iToolboxIdx = 0;
            U32 iResult = 0;

            paudec->pau->m_iCurrReconCoef = -1;

            pau->aupfnGetNextRun = prvGetNextBPRunDECVecTableIndex;

            PLUS_GETBITS(wmaResult, 1, &bUseToolboxs);

            if (bUseToolboxs)
            {
    
                //BPLUS_TOOLBOX_PREDICTIVE    0   :   0
                //BPLUS_TOOLBOX_INTERLEAVE    1   :   10
                //BPLUS_TOOLBOX_PDFSHIFT      2   :   11
                //Int iToolBoxBits[3]         = {1,  2,  2};
                //Int iToolBoxHuffManTable[3] = {0, 10, 11};

                PLUS_GETBITS(wmaResult, 1, &iResult);
                if (0 == iResult)
                {   // 0
                    iToolboxIdx = BPLUS_TOOLBOX_PREDICTIVE;
                }
                else
                {
                    PLUS_GETBITS(wmaResult, 1, &iResult);
                    if (0 == iResult)
                    {   // 10
                        iToolboxIdx = BPLUS_TOOLBOX_INTERLEAVE;
                    }
                    else
                    {   // 11
                        iToolboxIdx = BPLUS_TOOLBOX_PDFSHIFT;
                    }
                }

                if (BPLUS_TOOLBOX_INTERLEAVE == iToolboxIdx) //itlv toolbox
                {
                    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeInterleaveModeParams(paudec, ppcinfo));
                    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeRLCCoefQAndDeinterleaveCoefQ (paudec, ppcinfo));
                }
                else if (BPLUS_TOOLBOX_PREDICTIVE == iToolboxIdx) //predictive toolbox
                {
                    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeCoefQPredictor (paudec, ppcinfo));
                    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeRLCCoefQ (pau, paudec, ppcinfo));           
                    if (WMAB_FALSE == ppcinfo->m_bNoDecodeForCx)
                    {
                        TRACEWMA_EXIT(wmaResult, prvBasePlusInverseCoefQPrediction( pau, paudec, ppcinfo));
                    }
                }
                else if (BPLUS_TOOLBOX_PDFSHIFT == iToolboxIdx ) // 
                {
                    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodePDFShiftModeParams (paudec, ppcinfo));
                    // TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeRLCCoefQ (pau, paudec, ppcinfo));     
                    TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeCOEFQRLC_PDFShiftMode(pau, paudec, ppcinfo));
                    // TRACEWMA_EXIT(wmaResult, prvBasePlusInversePDFShiftRLCCoefQ (paudec, ppcinfo));
                }            
            }
            else
            {
                TRACEWMA_EXIT(wmaResult, prvBasePlusDecodeRLCCoefQ (pau, paudec, ppcinfo));
            }        
            //TRACEWMA_EXIT(wmaResult, prvBasePlusUpdateLastCodedCoefIndex (pau, ppcinfo));       
        } // else, retain zeros
        else
        {
            ppcinfo->m_cLastCodedIndexBasePlus = 1;
            if (1 == prvBasePlusIfBaseIsZero(pau))
            {
                assert(1 == ppcinfo->m_cLastCodedIndex);
            }
        }
    }
    
#ifdef BUILD_WMAPROLBRV3
    pau->m_cLastCodedIndex = 1;
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        I16 iChSrc     = pau->m_rgiChInTile[iCh];
        PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;
        Int iCoef;

        // need to find out the last coded index
        // for ppcinfo->m_rgBPCoef=NULL(i.e.,ppcinfo->m_bNoDecodeForCx=1)
        // passing ppcinfo->m_cLastCodedIndex=1 to peak decoding is ok for just bit decoding,
        // since no reconstruction will happen there
        if (ppcinfo->m_rgBPCoef)
        {
            // find non-zero coefs in base+ region only, and update last coded index only if found
            for (iCoef = ppcinfo->m_cSubFrameSampleHalf - 1; iCoef >= pbp->m_iExplicitStartPos; iCoef--)
            {
                if (ppcinfo->m_rgBPCoef[iCoef] != 0)
                {
                    ppcinfo->m_cLastCodedIndex = (U16)(iCoef + 1);
                    break;
                }
            }
        }
        pau->m_cLastCodedIndex = max(pau->m_cLastCodedIndex, ppcinfo->m_cLastCodedIndex);
    }
    // decode base peak
    TRACEWMA_EXIT(wmaResult, plusDecodeBasePeak(paudec));
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        I16 iChSrc     = pau->m_rgiChInTile[iCh];
        PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;

        TRACEWMA_EXIT(wmaResult, plusDecodeBasePeak_Channel(paudec, ppcinfo));
    }
#endif

    TRACEWMA_EXIT(wmaResult, prvBasePlusReconCoefficients(pau));
#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
    // Add base plus to the base layer.
    TRACEWMA_EXIT(wmaResult, prvBPAddBasePlustoBase(pau));
#endif

#ifdef BUILD_WMAPROLBRV3
    if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2)
    {
        // retrieve mask values which have been modified in base peak coding
        if( pau->m_bBasePeakPresentTile )
        {
            for (iCh=0; iCh < pau->m_cChInTile; iCh++)
            {
                I16 iChSrc     = pau->m_rgiChInTile[iCh];
                PerChannelInfo *ppcinfo    = pau->m_rgpcinfo + iChSrc;

                memcpy(ppcinfo->m_rgiSFQ, ppcinfo->m_piBasePeakMaskQSave, pbp->m_cValidSFBand * sizeof(Int));
            }
        }
    }
#endif

exit:
    return wmaResult;
}
WMARESULT prvBasePlusDecodeTileScaleFactors(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    I16 iCh, iChSrc, iChGrp;
    CAudioObject*     pau = paudec->pau;
    CBasePlusObject*  pbp = pau->m_pbp;
    CChannelGroupInfo* pcgi = NULL;
    Bool fOneScaleFactorPerChannelGroup = WMAB_FALSE;
    PerChannelInfo* ppcinfo = NULL;
    Int iSFPredEntpTbl = 0;

    // Init SF anchors
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc     = pau->m_rgiChInTile[iCh];
        ppcinfo    = pau->m_rgpcinfo + iChSrc;
        
        /* Can not use m_iCurrSubFrame to set m_fAnchorSFAvailable
           Leading tile(s) may not be encoded by bp layer so the 
           first bp coded tile doesn't have Anchor but iCurrSubFrame
           is not 0.
        if (0 == ppcinfo->m_iCurrSubFrame)
        {
            ppcinfo->m_fAnchorSFAvailable = WMAB_FALSE;
        }
        */
        
        if (ppcinfo->m_fAnchorSFAvailable)
        {
            // Do the mask resampling for this channel
            TRACEWMA_EXIT(wmaResult, prvBasePlusResampleScaleFactor (pau, 
                ppcinfo->m_rgiSFQ, 
                ppcinfo->m_cSubFrameSampleHalfWithSFUpdate, 
                ppcinfo->m_cValidSFBandLatestUpdate,
                ppcinfo->m_rgiSFQResampled, 
                ppcinfo->m_cSubFrameSampleHalf, pbp->m_cValidSFBand));
        }
    }

    // For each channel group, find the first channel
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        CChannelGroupInfo* pcgi = NULL;
        Bool *rgfChannelMask = NULL;
        PerChannelInfo* ppcinfoPred = NULL;

        //one in the tile
        iChSrc     = pau->m_rgiChInTile[iCh];
        ppcinfo    = pau->m_rgpcinfo + iChSrc;

        ppcinfo->m_fFirstChannelInGrp = WMAB_TRUE;
        ppcinfo->m_iFirstChannelInGrp = 0;
        ppcinfoPred = pau->m_rgpcinfo + ppcinfo->m_iFirstChannelInGrp;
    
        // Is this channel the first channel in its channel group? Slow loop
        for (iChGrp = 0; iChGrp <  pbp->m_cBPChannelGroup; iChGrp++)
        {
            Int iChTmp;

            pcgi = pbp->m_rgBPChannelGrpInfo + iChGrp;
            rgfChannelMask = pcgi->m_rgfChannelMask;

            if (!rgfChannelMask[iChSrc])
                continue;

            // Found the channel group for this channel.
            ppcinfo->m_fFirstChannelInGrp = iChSrc;
            for (iChTmp = 0; iChTmp < iChSrc; iChTmp++)
            {
                if (rgfChannelMask[iChTmp])
                {
                    ppcinfo->m_iFirstChannelInGrp = iChTmp;
                    ppcinfoPred = pau->m_rgpcinfo + ppcinfo->m_iFirstChannelInGrp;
                    break;
                }
            }
            ppcinfo->m_fFirstChannelInGrp = (ppcinfo->m_iFirstChannelInGrp == iChSrc) ? WMAB_TRUE : WMAB_FALSE;
            break;
        }
    }
    
    for (iChGrp = 0; iChGrp < pbp->m_cBPChannelGroup; iChGrp++)
    {
        pcgi = pbp->m_rgBPChannelGrpInfo + iChGrp;

        if (pcgi->m_cChannelsInGrp > 1)
        {
            PLUS_GETBITS(wmaResult, 1, &fOneScaleFactorPerChannelGroup);
        }
        else
        {
            fOneScaleFactorPerChannelGroup = WMAB_TRUE;
        }

        if (fOneScaleFactorPerChannelGroup)
        {
            Bool fTemporalPred = WMAB_FALSE, fSpectralPred = WMAB_FALSE, fSpatialPred = WMAB_FALSE;
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
            {
                iChSrc     = pau->m_rgiChInTile[iCh];
                ppcinfo    = pau->m_rgpcinfo + iChSrc;
                if (pcgi->m_rgfChannelMask[iChSrc])
                    break;
            }

            // first channel in the group
            if (iCh >= pau->m_cChInTile)
            {
                REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);            
            }
            memset(ppcinfo->m_rgiSFQ, 0, pbp->m_cValidSFBand * sizeof(Int));

            if (ppcinfo->m_fAnchorSFAvailable)
            {
                PLUS_GETBITS(wmaResult, 1, &fTemporalPred);
            }
            if (!ppcinfo->m_fFirstChannelInGrp && 
                !fTemporalPred)
            {
                PLUS_GETBITS(wmaResult, 1, &fSpatialPred);
            }

            if (fTemporalPred)
            {
                ppcinfo->m_sfPredictionType = SFPRED_TEMPORAL;
            }
            else if (fSpatialPred)
            {
                ppcinfo->m_sfPredictionType = SFPRED_SPATIAL;
            }
            else
            {
                ppcinfo->m_sfPredictionType = SFPRED_SPECTRAL;
            }

            if (0 != pbp->m_iCurrSFBandTable)
            {
                PLUS_GETBITS(wmaResult, 1, &(ppcinfo->m_fIntlvSF));
            }
            else
            {
                ppcinfo->m_fIntlvSF = 0;
            }

            // RLDecode masks
            pau->m_iCurrReconMaskBand = 0;
            paudec->m_maskrlsts = VLC;

            if (WMAB_FALSE == pbp->m_fUseProMaskRunLevelTbl)
            {
                PLUS_GETBITS(wmaResult, 2, &(ppcinfo->m_iSFQHuffmanTbl));
                TRACEWMA_EXIT(wmaResult, 
                    prvBasePlusDecodeScaleFactorRunLevel 
                    (
                        paudec, 
                        ppcinfo,
                        pbp->m_cValidSFBand,
                        pau->m_rgpcinfo + ppcinfo->m_iFirstChannelInGrp,
                        g_rgDecRunLevelTables[ppcinfo->m_iSFQHuffmanTbl].piIndexToRun,
                        g_rgDecRunLevelTables[ppcinfo->m_iSFQHuffmanTbl].piIndexToLevel,
                        g_rgDecRunLevelTables[ppcinfo->m_iSFQHuffmanTbl].piRunLevelTableDec
                    )
                );
            }
            else
            {
                TRACEWMA_EXIT(wmaResult, 
                    prvBasePlusDecodeScaleFactorRunLevel 
                    (
                        paudec, 
                        ppcinfo,
                        pbp->m_cValidSFBand,
                        pau->m_rgpcinfo + ppcinfo->m_iFirstChannelInGrp,
                        g_rgunRunMaskV3,
                        g_rgunLevelMaskV3,
                        g_rgunHuffDecTblMaskRLCV3
                    )
                );
            }
            // Copy over to other channels in the group
            iCh++;
            for (; iCh < pau->m_cChInTile; iCh++)
            {
                iChSrc     = pau->m_rgiChInTile[iCh];
                
                if (pcgi->m_rgfChannelMask[iChSrc])
                {
                    PerChannelInfo* ppcinfoTmp    = pau->m_rgpcinfo + iChSrc;
                    
                    memcpy(ppcinfoTmp->m_rgiSFQ, ppcinfo->m_rgiSFQ, sizeof(Int) * pbp->m_cValidSFBand);
                    ppcinfoTmp->m_iMaxSFQ = ppcinfo->m_iMaxSFQ;
                    ppcinfoTmp->m_fAnchorSFAvailable = ppcinfo->m_fAnchorSFAvailable;
                    ppcinfoTmp->m_cSubFrameSampleHalfWithSFUpdate = ppcinfo->m_cSubFrameSampleHalf;
                    ppcinfoTmp->m_cValidSFBandLatestUpdate = pbp->m_cValidSFBand;
                }
            }
        }
        else
        {
            for (iCh=0; iCh < pau->m_cChInTile; iCh++)
            {
                Bool fMaskUpdate = WMAB_FALSE;
                Bool fTemporalPred = WMAB_FALSE, fSpectralPred = WMAB_FALSE, fSpatialPred = WMAB_FALSE;
                
                iChSrc     = pau->m_rgiChInTile[iCh];
                ppcinfo    = pau->m_rgpcinfo + iChSrc;
                
                if (!pcgi->m_rgfChannelMask[iChSrc]) 
                    continue;

                memset(ppcinfo->m_rgiSFQ, 0, pbp->m_cValidSFBand * sizeof(Int));
                ppcinfo->m_iMaxSFQ = 0;
                
                PLUS_GETBITS(wmaResult, 1, &fMaskUpdate);
                
                if (!fMaskUpdate)
                {
                    // Use resampled mask
                    if (ppcinfo->m_fAnchorSFAvailable)
                    {
                        memcpy(ppcinfo->m_rgiSFQ, ppcinfo->m_rgiSFQResampled, pbp->m_cValidSFBand * sizeof(Int));                    
                    }
                    continue; 
                }
                
                if (ppcinfo->m_fAnchorSFAvailable)
                {
                    PLUS_GETBITS(wmaResult, 1, &fTemporalPred);
                }
                if (!ppcinfo->m_fFirstChannelInGrp && 
                    !fTemporalPred)
                {
                    PLUS_GETBITS(wmaResult, 1, &fSpatialPred);
                }

                if (fTemporalPred)
                {
                    ppcinfo->m_sfPredictionType = SFPRED_TEMPORAL;
                }
                else if (fSpatialPred)
                {
                    ppcinfo->m_sfPredictionType = SFPRED_SPATIAL;
                }
                else
                {
                    ppcinfo->m_sfPredictionType = SFPRED_SPECTRAL;
                }

                if (0 != pbp->m_iCurrSFBandTable)
                {
                    PLUS_GETBITS(wmaResult, 1, &(ppcinfo->m_fIntlvSF));
                }
                else
                {
                    ppcinfo->m_fIntlvSF = 0;
                }
                
                // RLDecode masks
                pau->m_iCurrReconMaskBand = 0;
                paudec->m_maskrlsts = VLC;

                if (WMAB_FALSE == pbp->m_fUseProMaskRunLevelTbl)
                {
                    PLUS_GETBITS(wmaResult, 2, &(ppcinfo->m_iSFQHuffmanTbl));
                    TRACEWMA_EXIT(wmaResult, 
                        prvBasePlusDecodeScaleFactorRunLevel  
                        (
                            paudec, 
                            ppcinfo,
                            pbp->m_cValidSFBand,
                            pau->m_rgpcinfo + ppcinfo->m_iFirstChannelInGrp,
                            g_rgDecRunLevelTables[ppcinfo->m_iSFQHuffmanTbl].piIndexToRun,
                            g_rgDecRunLevelTables[ppcinfo->m_iSFQHuffmanTbl].piIndexToLevel,
                            g_rgDecRunLevelTables[ppcinfo->m_iSFQHuffmanTbl].piRunLevelTableDec
                        )
                    );
                }
                else
                {
                    TRACEWMA_EXIT(wmaResult, 
                        prvBasePlusDecodeScaleFactorRunLevel 
                        (
                            paudec, 
                            ppcinfo,
                            pbp->m_cValidSFBand,
                            pau->m_rgpcinfo + ppcinfo->m_iFirstChannelInGrp,
                            g_rgunRunMaskV3,
                            g_rgunLevelMaskV3,
                            g_rgunHuffDecTblMaskRLCV3
                        )
                    );
                }
            }
        }
    }

    /*
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc     = pau->m_rgiChInTile[iCh];
        ppcinfo    = pau->m_rgpcinfo + iChSrc;

        TRACEWMA_EXIT(wmaResult, prvReOrderBPSFQInOverlayMode(pau, ppcinfo, iChSrc, WMAB_FALSE));
    }
    */
exit:
    return wmaResult;
} // prvBasePlusDecodeTileScaleFactors

// Copy/paste/edit from prvDecodeQuantStepV3
WMARESULT prvBasePlusDecodeTileQuantStepSize(CAudioObjectDecoder* paudec,
                                       Int* piBPTileQuant)
{
    CAudioObject* pau = paudec->pau;        
    U32         iResult;
    Int iStepSize;
    CBasePlusObject* pbp = pau->m_pbp;
    Int  iQuantStepSize = 90 * pau->m_nValidBitsPerSample / 16;
    Bool fQuantStepEscaped = WMAB_FALSE;
    Int  iQuantStepSign;
    WMARESULT wmaResult = WMA_OK;
    
    PLUS_GETBITS(wmaResult, 6, &iResult);

    // Determine the sign
    iStepSize = iResult;
    iQuantStepSign = (iStepSize & 0x20) ? -1 : 1;
    // Extend the sign.
    if (iQuantStepSign == -1)
        iStepSize |= 0xFFFFFFC0;
    // Accumulate the result
    iQuantStepSize += iStepSize;
    // Determine if escape coded
    if (iStepSize <= -32 || iStepSize >= 31)
        fQuantStepEscaped = WMAB_TRUE;
    

    while(fQuantStepEscaped) 
    {
        PLUS_GETBITS(wmaResult, NUM_BITS_QUANTIZER_V3, &iResult);

        iStepSize = iResult;
        assert(iStepSize <= MSA_MAX_QUANT_ESC_V3);
        if(iStepSize != MSA_MAX_QUANT_ESC_V3) 
        {
            // the last one...
            iQuantStepSize += (iStepSize * iQuantStepSign);
            break;
        }

        // escape code, so on to the next level...
        iQuantStepSize += (MSA_MAX_QUANT_ESC_V3 * iQuantStepSign);
        if (iQuantStepSize < MIN_QUANT)
        {
            // set some what safer step size.
            iQuantStepSize = 2 * MSA_MAX_QUANT_ESC_V3;
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);        
        }
    }
    
exit:

    *piBPTileQuant = iQuantStepSize;
    return wmaResult;
} // prvBasePlusDecodeTileQuantStepSize

// copy/paste/edit from prvDecodeQuantStepModifiers
WMARESULT prvBasePlusDecodeChannelQuantStepSize(CAudioObjectDecoder* paudec)
{
    WMARESULT   wmaResult = WMA_OK;

    CAudioObject* pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iResult = 0, cBitQuantStepModifierIndex = 0;
    Int iCh;
    
    if (pau->m_cChInTile == 1)
    {
        // No need of balancing # for mono tile.
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + pau->m_rgiChInTile [0];
        ppcinfo->m_iBPChannelQuant = 0;
        goto exit;
    } 

    // Read size information.
    iResult = 0;
    PLUS_GETBITS(wmaResult, 3, &iResult);
    cBitQuantStepModifierIndex = iResult;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
        
        // Is the scale index 0?
        iResult = 0;
        PLUS_GETBITS(wmaResult, 1, &iResult);
        if (0 == iResult)
        {
            ppcinfo->m_iBPChannelQuant = 0;
        } 
        else
        {
            // index is not 0.
            if (0 == cBitQuantStepModifierIndex)
            {
                // no need to read the bits, but use an index of 1.
                ppcinfo->m_iBPChannelQuant = 1;
            }
            else 
            {
                // Must read the bits to get index value.
                iResult = 0;
                PLUS_GETBITS(wmaResult, cBitQuantStepModifierIndex, &iResult);
                ppcinfo->m_iBPChannelQuant = (U8) iResult + 1;
            }
        }
    }
    
exit:
    return wmaResult;
} // prvBasePlusDecodeChannelQuantStepSize

// And also settle transform values if predefined
// Copy/paste/edit from prvDecideXformType
WMARESULT prvBPDecideXformType (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
    Int iCh, iCh0, iCh1;
    CAudioObject* pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int     iResult = 0;
    Int     cChannelsInGrp = pbp->m_rgBPChannelGrpInfo[pbp->m_cBPChannelGroup].m_cChannelsInGrp;
    CChannelGroupInfo *pcgi = NULL;
    
    assert(pbp->m_cBPChannelGroup <= pau->m_cChannel);
    assert(cChannelsInGrp <= pau->m_cChannel);

    pcgi = pbp->m_rgBPChannelGrpInfo + pbp->m_cBPChannelGroup;
    
    // The inverse transform is assumed to have been zeroed initially for this channel group
    pcgi->m_fIsPredefinedXform = WMAB_FALSE;
    pcgi->m_fIsSuperGroupXform = WMAB_FALSE; // No hierarchical transform in base plus
    
    if (cChannelsInGrp == 1) 
    {
        // pre-defined identity: hunt for the channel
        pcgi->m_fIsPredefinedXform = WMAB_TRUE;
        pcgi->m_predefinedXformType = MULTICH_IDENTITY;
        pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT(1.0F);
    } 
    else if (cChannelsInGrp == 2)
    {
        // All the bits needed are available
        iResult = 0;
        PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
        if (iResult == 0)
        {
            // Joint standard (Hadamard)
            // Set joint standard xform: These get used only for non-stereo cases.
            // Values are quantized to 1.8bits
            pcgi->m_fIsPredefinedXform = WMAB_TRUE;
            pcgi->m_predefinedXformType = MULTICH_HADAMARD;
            pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT( 0.70703125F);
            pcgi->m_rgfltMultiXInverse[1] = CH_FROM_FLOAT(-0.70703125F);
            pcgi->m_rgfltMultiXInverse[2] = CH_FROM_FLOAT( 0.70703125F);
            pcgi->m_rgfltMultiXInverse[3] = CH_FROM_FLOAT( 0.70703125F);
        } 
        else 
        {
            // Read one more bit
            iResult = 0;
            PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
            if (iResult == 0) 
            {
                // 2 independently coded channels
                // Set joint standard xform
                pcgi->m_fIsPredefinedXform = WMAB_TRUE;
                pcgi->m_predefinedXformType = MULTICH_IDENTITY;
                pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT(1.0F);
                pcgi->m_rgfltMultiXInverse[1] = CH_FROM_FLOAT(0.0F);
                pcgi->m_rgfltMultiXInverse[2] = CH_FROM_FLOAT(0.0F);
                pcgi->m_rgfltMultiXInverse[3] = CH_FROM_FLOAT(1.0F);
            } 
            else 
            {
                // Joint flexible coded.
            }
        }
    } 
    else 
    {
        // More than 2 channels in this channel group.
        iResult = 0;
        PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
        if (iResult == 0) 
        {
            // All independently coded channels
            pcgi->m_fIsPredefinedXform = WMAB_TRUE;
            pcgi->m_predefinedXformType = MULTICH_IDENTITY;
            for (iCh = 0; iCh < cChannelsInGrp; iCh++)
            {
                pcgi->m_rgfltMultiXInverse[iCh * cChannelsInGrp + iCh] = CH_FROM_FLOAT(1.0F);
            }
        }
        else
        {
            // Either DCT or free style

            iResult = 0;
            PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
            if (iResult == 0)
            {
                // DCT-Type 2
                assert(pcgi->m_cChannelsInGrp > 0 && pcgi->m_cChannelsInGrp <= MAX_CHANNEL);
                pcgi->m_fIsPredefinedXform = WMAB_TRUE;
                pcgi->m_predefinedXformType = MULTICH_DCT;
                // Fill the inverse transform for the channels in this group
                for (iCh0 = 0; iCh0 < cChannelsInGrp; iCh0++) 
                {
                    for (iCh1 = 0; iCh1 < cChannelsInGrp; iCh1++)
                    {
                        pcgi->m_rgfltMultiXInverse[iCh0 * cChannelsInGrp + iCh1] = 
                            pau->m_rgrgrgfltMultiXIDCT[cChannelsInGrp][iCh0][iCh1];
                    }
                }
                //assert(0);
            }
            else 
            {
                // Free style
                pcgi->m_fIsPredefinedXform = WMAB_FALSE;
                pcgi->m_predefinedXformType = MULTICH_INVALID;
            }
        }
    }
exit:
    return wmaResult;
} // prvBPDecideXformType

// Copy/paste/edit of prvBPDecodeTransformOnOffInfo
WMARESULT prvBPDecodeTransformOnOffInfo (CAudioObjectDecoder* paudec)
{   
    WMARESULT   wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int     iResult = 0;
    Int     iBand;
    Int     cBits0 = min(24, pau->m_cValidBarkBand+1); // Maximum 24 bits to be read at a time.
    CChannelGroupInfo *pcgi = NULL;
    
    pcgi = pbp->m_rgBPChannelGrpInfo + pbp->m_cBPChannelGroup;
    
    assert(pbp->m_cBPChannelGroup < pau->m_cChannel);
    assert((pau->m_cValidBarkBand+1) <= 2 * 24);
    
    if ((pcgi->m_cChannelsInGrp > 1) &&
        ((pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
        pcgi->m_predefinedXformType != MULTICH_IDENTITY) ||
        (pcgi->m_fIsPredefinedXform == WMAB_FALSE))) 
    {
        // Read the on-off information
        // Are all the barks on?
        PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
        pcgi->m_fAllBarksOn = iResult;
        if (iResult == WMAB_TRUE)
        {
            // All barks have transform on
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
                pcgi->m_rgfXformOn[iBand] = WMAB_TRUE;
            goto exit;
        } 
        else
        {
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
                pcgi->m_rgfXformOn[iBand] = iResult;
            }
        }
    } 
    else 
    {
        // All barks have transform on
        for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
        {
            pcgi->m_rgfXformOn[iBand] = WMAB_TRUE;
        }
    }
    
exit:
    
    return wmaResult;
} // prvBPDecodeTransformOnOffInfo

// Copy/paste/edit of prvDecodeChannelMask
WMARESULT prvBPDecodeChannelMask (CAudioObjectDecoder* paudec,
                                  Int cBPChannelsLeft)
{      
    WMARESULT   wmaResult = WMA_OK;
    Int iCh;
    CAudioObject* pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iResult       = 0;
    CChannelGroupInfo* pcgi = NULL;
        
    if (pbp->m_cBPChannelGroup >= pau->m_cChannel || pbp->m_cBPChannelGroup < 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);    
    }
    pcgi = pbp->m_rgBPChannelGrpInfo + pbp->m_cBPChannelGroup;
    
    assert(pbp->m_cBPChannelGroup < pau->m_cChannel);
    pcgi->m_cChannelsInGrp = 0;
    memset(pcgi->m_rgfChannelMask, 0, sizeof(Bool) * pau->m_cChannel);
    
    if (cBPChannelsLeft <= 2) 
    {
        // Derive from current state
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {
            pcgi->m_rgfChannelMask[iCh] = (pbp->m_rgfBPVisited[iCh] == WMAB_TRUE) ? WMAB_FALSE : WMAB_TRUE;
            // Now all channels are visited
            pbp->m_rgfBPVisited[iCh] = WMAB_TRUE;
        }
        pcgi->m_cChannelsInGrp = cBPChannelsLeft;
    }
    else 
    {
        // (paudec->m_cChannelsLeft > 2) 
        // Must read the bitstream and decode: enough bits are available
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];

            if (pbp->m_rgfBPVisited[iChSrc] == WMAB_FALSE) 
            {
                PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
                if (iResult == 1)
                {
                    pcgi->m_rgfChannelMask[iChSrc] = WMAB_TRUE;
                    pbp->m_rgfBPVisited[iChSrc] = WMAB_TRUE;
                    pcgi->m_cChannelsInGrp = pcgi->m_cChannelsInGrp + 1;
                }
            }
        }
    }

    if (pcgi->m_cChannelsInGrp < 1)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);    
    }
    
exit:
    
    return wmaResult;
} // prvBPDecodeChannelMask

// Copy/paste/update from prvEntropyDecodeChannelXform
WMARESULT prvBasePlusEntropyDecodeChannelXform (CAudioObjectDecoder* paudec)
{      
    WMARESULT   wmaResult = WMA_OK;
   
    CAudioObject*    pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iCh;
    Int iResult = 0;
    Int cChannelsInGrp;
    CChannelGroupInfo* pcgi = NULL;
    Int cBPChannelsLeft = pau->m_cChInTile;
    Int iAngle=0, cAngles=0, iSign=0, cSigns=0;
    assert(pau->m_iVersion >= 3);
	
    if (pau->m_cChannel == 1 && pau->m_bMonoV3)
    {
        // nothing to decode
        pbp->m_cBPChannelGroup = pbp->m_cBPChannelGroup = 1;
        pcgi = pbp->m_rgBPChannelGrpInfo;
                
        pcgi->m_cChannelsInGrp = 1;
        memset(pcgi->m_rgfChannelMask, 0, sizeof(Bool) * pau->m_cChannel);
        pcgi->m_rgfChannelMask[0] = WMAB_TRUE;
        pcgi->m_fIsSuperGroupXform = WMAB_FALSE;
        pcgi->m_fIsPredefinedXform = WMAB_TRUE;
        pcgi->m_predefinedXformType = MULTICH_INVALID;
        pcgi->m_fAllBarksOn = WMAB_TRUE;
        memset(pcgi->m_rgfXformOn, 0, sizeof(Bool) * NUM_BARK_BAND);
        memset(pcgi->m_rgfltMultiXInverse, 0, sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
        pcgi->m_fIsPredefinedXform = WMAB_TRUE;
        pcgi->m_predefinedXformType = MULTICH_IDENTITY;
        pcgi->m_rgfltMultiXInverse[0] = CH_FROM_FLOAT(1.0F);
        return WMA_OK;
    }

    // Clean slate
    pbp->m_cBPChannelGroup = 0;
    for (iCh = 0; iCh < pau->m_cChannel; iCh++)
    {
        pbp->m_rgfBPVisited[iCh] = WMAB_FALSE;
    }
    
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        pcgi = pbp->m_rgBPChannelGrpInfo + iCh;
        
        pcgi->m_cChannelsInGrp = 0;
        memset(pcgi->m_rgfChannelMask, 0, sizeof(Bool) * pau->m_cChannel);
        pcgi->m_fIsSuperGroupXform = WMAB_FALSE;
        pcgi->m_fIsPredefinedXform = WMAB_FALSE;
        pcgi->m_predefinedXformType = MULTICH_INVALID;
        pcgi->m_fAllBarksOn = WMAB_FALSE;
        memset(pcgi->m_rgfXformOn, 0, sizeof(Bool) * NUM_BARK_BAND);
        memset(pcgi->m_rgfltMultiXInverse, 0, sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
    }

    iResult = 0;
    PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
    if (iResult != 0)
    {
        // No hierarchical multi-channel
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    while (cBPChannelsLeft > 0)
    {
        iResult = 0;

        // decode channel mask for the group
        TRACEWMA_EXIT(wmaResult, prvBPDecodeChannelMask(paudec, cBPChannelsLeft));

        // Decide if we need a flexible transform or predefined
        TRACEWMA_EXIT(wmaResult, prvBPDecideXformType(paudec));
            
        assert(pbp->m_cBPChannelGroup <= pau->m_cChannel);
        cChannelsInGrp    = pbp->m_rgBPChannelGrpInfo[pbp->m_cBPChannelGroup].m_cChannelsInGrp;
        assert(cChannelsInGrp <= pau->m_cChannel);
        cAngles = (cChannelsInGrp * (cChannelsInGrp-1))/2;
        cSigns  = cChannelsInGrp;
        
        iSign   = 0;

        // Decode angles
        pcgi = pbp->m_rgBPChannelGrpInfo + pbp->m_cBPChannelGroup;
        if (!pcgi->m_fIsPredefinedXform) 
        {
            for (iAngle  = 0; iAngle < cAngles; iAngle++) 
            {
                iResult = 0;
                PLUS_GETBITS(wmaResult, ROTATION_ANGLE_BITS, (U32 *)&iResult);
                // Map iResult into quantized index 
                pcgi->m_rgbRotationAngle[iAngle] = (I8)(iResult-MAX_ROTATION_ANGLE_INDEX);
            }
        }

        //Decode signs
        pcgi = pbp->m_rgBPChannelGrpInfo + pbp->m_cBPChannelGroup;
        if (!pcgi->m_fIsPredefinedXform) 
        {
            for (iSign = 0; iSign < cSigns; iSign++) 
            {
                iResult = 0;
                PLUS_GETBITS(wmaResult, 1, (U32 *)&iResult);
                pcgi->m_rgbRotationSign[iSign] = (I8)iResult;
            }
        }

        // Transform on-off information
        assert(pbp->m_cBPChannelGroup < pau->m_cChannel);

        // prvDecodeTransformOnOffInfo distinguishes between CHXFORM_XFORMONOFF0 and CHXFORM_XFORMONOFF1.
        TRACEWMA_EXIT(wmaResult, prvBPDecodeTransformOnOffInfo(paudec));
        cBPChannelsLeft -= pcgi->m_cChannelsInGrp;
        pbp->m_cBPChannelGroup += 1;
    }
    
exit:    
    return wmaResult;
} // prvBasePlusEntropyDecodeChannelXform

WMARESULT prvDecodeSFBandTableIndex(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject*    pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iResult = 0;
    
    PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
    
    if (0 == iResult)
    {
        pbp->m_iCurrSFBandTable = 0;
    }
    else
    {
        PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
        if (0 == iResult)
        {
            pbp->m_iCurrSFBandTable = 1;
        }
        else
        {
            PLUS_GETBITS(wmaResult, 1, (U32*)&iResult);
            pbp->m_iCurrSFBandTable = iResult + 2;
        }
    }

exit:
    return wmaResult;
} // prvDecodeSFBandTableIndex

WMARESULT prvBasePlusDecodeFirstTileHeaderExclusiveMode(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject*    pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    I32 iResult = 0;

    if (!pbp->m_bFirstTile)
    {
        // No need to read
        goto exit;
    }
    else
    {
        I32 iCh;
        // set all channels' m_fAnchorSFAvailable to false
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
            ppcinfo->m_fAnchorSFAvailable = WMAB_FALSE;
        }
    }
    
    if (pbp->m_fFrameParamUpdate)
    {
        TRACEWMA_EXIT(wmaResult, prvDecodeSFBandTableIndex(paudec));
        
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fScalePriorToChannelXformAtDec);        
        // Quantization linear or not
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fLinearQuantization);
        if (WMAB_FALSE == pbp->m_fLinearQuantization)
        {
            PLUS_GETBITS(wmaResult, 2, &pbp->m_NLQIdx);
            prvBasePlusSetNonLinearQuantizer (pbp);
        }
        PLUS_GETBITS(wmaResult, 1, &pbp->m_fUseProMaskRunLevelTbl);

    }        

    // Mask multiplier
    pbp->m_iSFQMultiplier = 1;
    PLUS_GETBITS(wmaResult, 2, &pbp->m_iSFQMultiplier);
    pbp->m_iSFQMultiplier += 1;

    pbp->m_bFirstTile = WMAB_FALSE;
        
exit: 
    return wmaResult;
} // prvBasePlusDecodeFirstTileHeaderExclusiveMode

WMARESULT prvBasePlusDecodeFirstTileHeaderOverlayMode(CAudioObjectDecoder* paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject*    pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    I32 iResult = 0;

    if (!pbp->m_bFirstTile)
    {
        // No need to read
        goto exit;
    }
    
    if (pbp->m_fFrameParamUpdate)
    {
        PLUS_GETBITS(wmaResult, 1, &pbp->m_iHoleWidthMinIdx);    
        PLUS_GETBITS(wmaResult, 1, &pbp->m_iHoleSegWidthMinIdx);    
        PLUS_GETBITS(wmaResult, 1, &pbp->m_bSingleWeightFactor); 
        PLUS_GETBITS(wmaResult, 2, &pbp->m_iWeightQuantMultiplier);
        pbp->m_iWeightQuantMultiplier++;
        PLUS_GETBITS(wmaResult, 1, &pbp->m_bWeightFactorOnCodedChannel);
    }

    pbp->m_bFirstTile = WMAB_FALSE;

exit: 
    return wmaResult;
} // prvBasePlusDecodeFirstTileHeaderOverlayMode

WMARESULT prvBasePlusDecodeCoefQPredictor (CAudioObjectDecoder* paudec, 
                                           PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    U32 ulResult;
    I32 iOrder = 0;
    Int i;
    Int iSeg;

    // --- get lpc order
    // iOrder   1    2    4    8
    // bits     0   10  110  111
    // first check LPCOrder is power of 2
    Int iOrderBits[4] = {1, 2, 3, 3};
    Int iOrderHuffManTable[4] = {0, 2, 6, 7}; // 0, 10, 110, 111

    PLUS_GETBITS(wmaResult, 1, &ulResult);
    if (0 == ulResult)
    {   //0
        iOrder = 1;
    }   
    else
    {
        PLUS_GETBITS(wmaResult, 1, &ulResult);
        if (0 == ulResult)
        {   //10
            iOrder = 2;
        }
        else
        {
            PLUS_GETBITS(wmaResult, 1, &ulResult);
            if (0 == ulResult)
            {   //110
                iOrder = 4;
            }
            else
            {   //111
                iOrder = 8;
            }
        }
    }
    ppcinfo->m_iQCoefLPCOrder = iOrder;

    // --- get lpc shift
    PLUS_GETBITS(wmaResult, LOG2(BPLUS_QCOEF_LPCSHIFT_MAX), (&ppcinfo->m_iQCoefLPCShift));
    ppcinfo->m_iQCoefLPCShift++;
    assert(ppcinfo->m_iQCoefLPCShift > 0 && ppcinfo->m_iQCoefLPCShift <= 8);

    // --- get lpc segment.
    if (ppcinfo->m_cSubband > BPLUS_QCOEF_SEG_MINLEN)
    {
        PLUS_GETBITS(wmaResult, LOG2(min(BPLUS_QCOEF_LPCSEGMT_MAX, ppcinfo->m_cSubband/BPLUS_QCOEF_SEG_MINLEN)), &ulResult);
        ppcinfo->m_iQCoefLPCSegmt = ulResult + 1;
    }
    else
    {
        ppcinfo->m_iQCoefLPCSegmt = 1;
    }
    // --- get segment mask.
    ppcinfo->m_iQCoefLPCMasks = 1;
    if (ppcinfo->m_iQCoefLPCSegmt > 1)
    {
        PLUS_GETBITS(wmaResult, ppcinfo->m_iQCoefLPCSegmt, &ulResult);
        ppcinfo->m_iQCoefLPCMasks = ulResult;
    }

    // --- get lpc coeff
    for (iSeg = 0; iSeg < ppcinfo->m_iQCoefLPCSegmt; iSeg++)
    {
        for (i = 0; i < iOrder; i++)
        {
            PLUS_GETBITS(wmaResult, ppcinfo->m_iQCoefLPCShift + 2, &ulResult);
            ppcinfo->m_rgiQuantizedCoefPredictor[iSeg][i] = ((Int)ulResult) - ((1 << (ppcinfo->m_iQCoefLPCShift + 1)) - 1);
        }
    }

exit:
    return wmaResult;
} // prvBasePlusDecodeCoefQPredictor

WMARESULT prvBasePlusInverseCoefQPrediction(CAudioObject*  pau, 
                                        CAudioObjectDecoder* paudec,
                                        PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject*  pbp = paudec->pau->m_pbp;

    CoefType* rgiCoefRecon = ppcinfo->m_rgBPCoef + pbp->m_iExplicitStartPos;
    Int iCoef, cSubband = ppcinfo->m_cSubFrameSampleHalf;

    I32 iOrder = ppcinfo->m_iQCoefLPCOrder;
    I32 iShift = ppcinfo->m_iQCoefLPCShift;
    I32 *piPred = ppcinfo->m_rgiQuantizedCoefPredictor[0];
   
    I32 iSegLen = 0;

    if (0 == iOrder)
    {
        // Nothing to add!
        goto exit;
    }

    if (cSubband % ppcinfo->m_iQCoefLPCSegmt != 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    iSegLen = cSubband / ppcinfo->m_iQCoefLPCSegmt;
    assert (iSegLen >= BPLUS_QCOEF_LPCORDER_MAX); 

    for (iCoef = iOrder; iCoef < cSubband - pbp->m_iExplicitStartPos; iCoef++)
    {
        const Int iSeg = iCoef / iSegLen;
        Int iOffset = (1 << iShift) / 2;
        Int pred = 0;
        Int iTap;   
    
        piPred = ppcinfo->m_rgiQuantizedCoefPredictor[iSeg];
        // if the mask for this segment is 1, we do LPC.        
        if ((ppcinfo->m_iQCoefLPCMasks >> iSeg) & 1)
        {
            for (iTap = 0; iTap < iOrder; iTap++)
            {
                pred += LEVEL_FROM_COEF( rgiCoefRecon[iCoef-iTap-1] ) * piPred[iTap];
            }       
            pred = (pred + iOffset) >> iShift;
            rgiCoefRecon[iCoef] += COEF_FROM_LEVEL( pred );
        }
    }
    
exit:
    return wmaResult;
} // prvBasePlusInverseCoefQPrediction


WMARESULT prvBasePlusDecodeInterleaveModeParams(CAudioObjectDecoder* paudec, PerChannelInfo *ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    Int cSubband = ppcinfo->m_cSubband;

    Int iPeriodLimit = (ppcinfo->m_cSubFrameSampleHalf/BPLUS_MIN_PERIODS_PERSUBFRM);
    Int iScale = 1 << BPLUS_PERIOD_FRACTION_BITS;
    Int cMaxPeriods;

    Int iResult;
    // get iPeriod
    PLUS_GETBITS(wmaResult, LOG2(iPeriodLimit), (&iResult));
    ppcinfo->m_iPeriod = iResult + 1;
    if (WMAB_FALSE == (ppcinfo->m_iPeriod >= 8 && ppcinfo->m_iPeriod <= iPeriodLimit))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
   
    // get iPeriodFraction
    PLUS_GETBITS(wmaResult, BPLUS_PERIOD_FRACTION_BITS, &iResult);
    ppcinfo->m_iPeriodFraction = iResult;
    if (WMAB_FALSE == (ppcinfo->m_iPeriodFraction >= 0 && ppcinfo->m_iPeriodFraction < (1 << BPLUS_PERIOD_FRACTION_BITS)))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    // get
    cMaxPeriods = (cSubband * iScale) / (ppcinfo->m_iPeriod * iScale + ppcinfo->m_iPeriodFraction);
    PLUS_GETBITS(wmaResult, LOG2(BPLUS_MAX_FIRSTITLVPERIOD), &iResult);
    ppcinfo->m_iFirstItlvPeriod = iResult;

    PLUS_GETBITS(wmaResult, CEILLOG2(cMaxPeriods), &iResult);
    ppcinfo->m_iLastItlvPeriod = iResult;
    if (WMAB_FALSE == (ppcinfo->m_iFirstItlvPeriod <= BPLUS_MAX_FIRSTITLVPERIOD && 
                       ppcinfo->m_iFirstItlvPeriod >= 0 && 
                       ppcinfo->m_iLastItlvPeriod <= cMaxPeriods))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    PLUS_GETBITS(wmaResult, LOG2(BPLUS_MAX_PREROLL), &iResult);
    ppcinfo->m_iPreroll = iResult;
    if (WMAB_FALSE == (ppcinfo->m_iPreroll < BPLUS_MAX_PREROLL))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

exit:
    return wmaResult;
}

#if 0
WMARESULT prvBasePlusInversePDFShiftRLCCoefQ(CAudioObjectDecoder *paudec, PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject *pau = paudec->pau;
    CBasePlusObject*  pbp = paudec->pau->m_pbp;
    CoefType* rgBPCoef = ppcinfo->m_rgBPCoef;

    I16 *rgiRunMapTable = pbp->m_rgi16BPTmpBufB;
    Int cSubband = ppcinfo->m_cSubFrameSampleHalf;
    I32 cSizeRunMapTable = cSubband/BPLUS_MIN_PERIODS_PERSUBFRM_PDFSHIFT * 2;
    I32 cBPQRLC;
    I32 iCoef;
    I32 cRun;
    I32 cOut = 0;

    I32 iInsertPos = ppcinfo->m_iInsertPos;
    I32 iPeriod = ppcinfo->m_iPeriod4PDFShift;
    
    I32 iOffset = 0;
    I32 iRun;
    I32 iCurr;

    I32 cTtlRun;
    I32 iRecon;

    I16 *rgiBPQRLCBackup = (I16*)pbp->m_rgiBPCoefTemp;

    //CoefType *rgiBPCoefTemp = (CoefType *)pbp->m_rgiBPCoefTemp;
    //CoefType rgiTemp[4096];
    //I32 i;

    //DUMPDATA(rgiBPCoefTemp, sizeof(CoefType)*cSubband, "d:\\temp\\a.dat","wb");
    //memcpy(rgiTemp, rgiBPCoefTemp, sizeof(CoefType)*cSubband);
    // m_rgi16BPTmpBufB is cFrameSampleHalf/2 * I16
    assert(cSubband/BPLUS_MIN_PERIODS_PERSUBFRM_PDFSHIFT * 2 <= pau->m_cFrameSampleAdjusted / 2);
    // pbp->m_rgiBPCoefTemp is malloced as CoefType. Make sure we don't buffer overrun.
    assert(sizeof(I16) * 2 <= sizeof(CoefType));

    cOut = 0;
    cRun = 0;
    for (iCoef = 0; iCoef < cSubband; iCoef++)
    {
        if (!rgBPCoef[iCoef])
        {
            cRun++;
        }
        else
        {
            const CoefType coef = rgBPCoef[iCoef];
            const I16 iSign    = ( coef > 0 ) ? 0x8000 : 0;
            const I16 iLevel   = (I16)LEVEL_FROM_COEF( ABS_COEF( coef ) );
        
            rgiBPQRLCBackup[ cOut++ ] = (I16)cRun;
            rgiBPQRLCBackup[ cOut++ ] = (I16)(iSign | iLevel);

            cRun = 0;
        }
    }
    if (cRun > 0)
    {
        // Final symbol
        rgiBPQRLCBackup[ cOut++ ] = (I16)cRun;
        rgiBPQRLCBackup[ cOut++ ] = 0;
    }
    cBPQRLC = cOut;

    for (iRun = 0; iRun < cSizeRunMapTable; iRun++)
    {
        rgiRunMapTable[iRun] = (I16)iRun;
    }

    iCurr = iInsertPos;
    iOffset = 0;
    while (1)
    {
        assert(iPeriod+iOffset < cSizeRunMapTable);
        assert(iPeriod > iOffset);
        if (iOffset == 0)
        {
            rgiRunMapTable[iCurr++] = (I16)iPeriod;
        }
        else
        {
            rgiRunMapTable[iCurr++] = (I16)(iPeriod - iOffset);
            rgiRunMapTable[iCurr++] = (I16)(iPeriod + iOffset);
        }

        if (iPeriod - iOffset == iInsertPos + iOffset)
            break;

        rgiRunMapTable[iCurr++] = (I16)(iInsertPos + iOffset);

        if (iPeriod - iOffset == iInsertPos + iOffset + 1)
            break;
        
        iOffset++;
    }

    for (iRun = 0; iRun < cBPQRLC/2; iRun++)
    {
        if (rgiBPQRLCBackup[iRun * 2] >= 0 && rgiBPQRLCBackup[iRun * 2] < cSizeRunMapTable)
        {
            rgiBPQRLCBackup[iRun * 2] = rgiRunMapTable[rgiBPQRLCBackup[iRun * 2]];
        }
    }

    cTtlRun = 0;
    for (iRun = 0; iRun < cBPQRLC/2-1; iRun++)
    {
        cTtlRun += (rgiBPQRLCBackup[iRun * 2]+1);
    }
    cTtlRun += rgiBPQRLCBackup[iRun * 2];
    if (rgiBPQRLCBackup[iRun * 2 + 1] != 0)
        cTtlRun ++;

    // CTODO: should report bitstream corruption.
    if (WMAB_FALSE == (cTtlRun >= cSubband))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    
    if (cTtlRun > cSubband)
    {
        if (WMAB_FALSE == (rgiBPQRLCBackup[iRun*2+1] == 0))
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        if (rgiBPQRLCBackup[iRun*2] > cTtlRun - cSubband)
        {
            rgiBPQRLCBackup[iRun*2] -= (I16)(cTtlRun - cSubband);
        }
        else if (rgiBPQRLCBackup[iRun*2] == cTtlRun - cSubband)
        {
            cBPQRLC -= 2;
        }
        else
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
            
    }


    memset(rgBPCoef, 0, sizeof(CoefType) * cSubband);

    iRecon = 0;
    for (iRun = 0; iRun < cBPQRLC/2; iRun++)
    {
        if (rgiBPQRLCBackup[iRun*2+1] > 0)
        {
            iRecon += rgiBPQRLCBackup[iRun*2];
            rgBPCoef[iRecon++] = -COEF_FROM_LEVEL(rgiBPQRLCBackup[iRun*2+1]);
        }
        else if (rgiBPQRLCBackup[iRun*2+1] < 0)
        {
            iRecon += rgiBPQRLCBackup[iRun*2];
            rgBPCoef[iRecon++] = COEF_FROM_LEVEL(rgiBPQRLCBackup[iRun*2+1] & 0x7FFF);
        }
    }

    //DUMPDATA(rgBPCoef, sizeof(CoefType)*cSubband, "d:\\temp\\b.dat","wb");
    //for (i = 0; i < cSubband; i++)
    //{
    //    assert(rgBPCoef[i] == rgiTemp[i]);
    //}

    return wmaResult;
}
#endif

WMARESULT prvBasePlusDecodeRLCCoefQAndDeinterleaveCoefQ(CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;

    CAudioObject            *pau    = paudec->pau;
    CBasePlusObject         *pbp    = pau->m_pbp;

    CoefType *rgBPCoef = ppcinfo->m_rgBPCoef + pbp->m_iExplicitStartPos;
    // CoefType *rgBPCoefReOrder = pbp->m_rgiBPCoefTemp;

    I16 *rgPeriodStartsOrig = pbp->m_rgi16BPTmpBufA; // cFrameSampleHalf/4 elements
    I16 *rgPeriodStartsCurr = pbp->m_rgi16BPTmpBufB; // cFrameSampleHalf/4 elements

    Int cSubband = ppcinfo->m_cSubband;
    // Int iCoef;

#if 0
    Double dblDiff1 = 0.0;
    Double dblDiff2 = 0.0;
#endif 

    Int      i;
    Int      iPeriodIdx;

    Int iPeriod = ppcinfo->m_iPeriod;
    Int iPeriodFraction = ppcinfo->m_iPeriodFraction;
    Int iFirstItlvPeriod = ppcinfo->m_iFirstItlvPeriod;
    Int iLastItlvPeriod = ppcinfo->m_iLastItlvPeriod;
    Int iPreroll = ppcinfo->m_iPreroll;

    CAudioObjectDecoder* pcaller = paudec;
    CoefType ctCoefLevel;
    CoefType ctCoefRecon;
    I16* piRecon = &pau->m_iCurrReconCoef;

    Int iHighCutOff = 0;
    Int iHighCutOffReal = 0;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);

    BIT_DISTRIBUTION_VARS;

    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] != 0);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);
    // V3 LLM. Chao. Added. LLM mode should not enter this function.
    assert (pau->m_bUnifiedLLM == WMAB_FALSE);
    assert (pau->m_bPureLosslessMode == WMAB_FALSE);

    DEBUG_BREAK_AT_FRAME_DECODE;
    if (ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    iHighCutOff = pau->m_cHighCutOff - 1;
    iHighCutOffReal = pau->m_cHighCutOff - 1 - pbp->m_iExplicitStartPos;
    assert(pau->m_cHighCutOff == cSubband);

    BIT_DISTRIBUTION_PRECHECK;

    i = 0;  
   
    iPeriodIdx = 0;
    while (1)
    {
        Int iScale = 1 << BPLUS_PERIOD_FRACTION_BITS;
        Int iStart = (iPeriodIdx * (iPeriod * iScale + iPeriodFraction) + iScale/2) / iScale;
        iStart = max(iStart - iPreroll, 0);
        if (iStart >= cSubband)
            break;
        rgPeriodStartsOrig[iPeriodIdx] = (I16)iStart;
        iPeriodIdx++;
        if (iPeriodIdx >= cSubband/8)
            break;            
    }
    if (WMAB_FALSE == (iPeriodIdx <= cSubband/8))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }
    if (WMAB_FALSE == (iLastItlvPeriod < iPeriodIdx))
    {
        REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
    }

    //memcpy (rgBPCoefReOrder, rgBPCoef, sizeof(CoefType)*cSubband);
    memcpy (rgPeriodStartsCurr, rgPeriodStartsOrig, sizeof(I16)*cSubband/8);

    TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    assert(pau->m_cRunOfZeros < SHRT_MAX);
    *piRecon += (I16) (pau->m_cRunOfZeros+1);
    ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);

    for (i = 0; i < rgPeriodStartsOrig[iFirstItlvPeriod]; i++)
    {
        //rgBPCoef[i] = rgBPCoefReOrder[i]; //redundant.
        if (*piRecon == i)
        {
            if ( i <= iHighCutOffReal )
            {
                ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                                                    pau->m_iSign ? -ctCoefLevel : ctCoefLevel );
            #if (CX_DECODE_MONO==1)
                CX_SET_RECON_COEF_BP(rgBPCoef[i], ctCoefRecon);
            #else
                rgBPCoef[i] = ctCoefRecon;
            #endif
            }
            // i < iHighCutOff means we need to continue to decode RLC
            if (i < iHighCutOff)
            {
                TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
                DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
                assert(pau->m_cRunOfZeros < SHRT_MAX);
                *piRecon += (I16) (pau->m_cRunOfZeros+1);
                ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
            }
        }
    }
    while (1)
    {
        for (iPeriodIdx = iFirstItlvPeriod; iPeriodIdx < iLastItlvPeriod; iPeriodIdx++)
        {
            if (rgPeriodStartsCurr[iPeriodIdx] < rgPeriodStartsOrig[iPeriodIdx+1])
            {
                // rgBPCoef[rgPeriodStartsCurr[iPeriodIdx]] = rgBPCoefReOrder[i];
                if (*piRecon == i)
                {
                    if ( rgPeriodStartsCurr[iPeriodIdx] <= iHighCutOffReal )
                    {
                        ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                                                            pau->m_iSign ? -ctCoefLevel : ctCoefLevel );

                    #if (CX_DECODE_MONO==1)
                        CX_SET_RECON_COEF_BP(rgBPCoef[rgPeriodStartsCurr[iPeriodIdx]], ctCoefRecon);
                    #else
                        rgBPCoef[rgPeriodStartsCurr[iPeriodIdx]] = ctCoefRecon;
                    #endif
                    }
                    // i < iHighCutOff means we need to continue to decode RLC
                    if (i < iHighCutOff)
                    {
                        TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
                        DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
                        assert(pau->m_cRunOfZeros < SHRT_MAX);
                        *piRecon += (I16) (pau->m_cRunOfZeros+1);
                        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
                    }
                }
                rgPeriodStartsCurr[iPeriodIdx]++;
                i++;
            }
            while (rgPeriodStartsCurr[iPeriodIdx] - rgPeriodStartsOrig[iPeriodIdx] <= iPreroll &&
                   rgPeriodStartsCurr[iPeriodIdx] < rgPeriodStartsOrig[iPeriodIdx+1])
            {
                // rgBPCoef[rgPeriodStartsCurr[iPeriodIdx]] = rgBPCoefReOrder[i];
                if (*piRecon == i)                                      
                {
                    if ( rgPeriodStartsCurr[iPeriodIdx] <= iHighCutOffReal )
                    {
                        ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                                                            pau->m_iSign ? -ctCoefLevel : ctCoefLevel );
                    #if (CX_DECODE_MONO==1)
                        CX_SET_RECON_COEF_BP(rgBPCoef[rgPeriodStartsCurr[iPeriodIdx]], ctCoefRecon);
                    #else
                        rgBPCoef[rgPeriodStartsCurr[iPeriodIdx]] = ctCoefRecon;
                    #endif
                    }
                    // i < iHighCutOff means we need to continue to decode RLC
                    if (i < iHighCutOff)
                    {
                        TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
                        DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
                        assert(pau->m_cRunOfZeros < SHRT_MAX);
                        *piRecon += (I16) (pau->m_cRunOfZeros+1);
                        ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
                    }
                }
                rgPeriodStartsCurr[iPeriodIdx]++;
                i++;
            }
        }
        if (i >= rgPeriodStartsOrig[iLastItlvPeriod])
            break;
    }

    for (/*i*/; i < cSubband; i++)
    {
        //rgBPCoef[i] = rgBPCoefReOrder[i]; //redundant.
        if (*piRecon == i)
        {
            if (i <= iHighCutOffReal)
            {
                ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                                                    pau->m_iSign ? -ctCoefLevel : ctCoefLevel );
            #if (CX_DECODE_MONO==1)
                CX_SET_RECON_COEF_BP(rgBPCoef[i], ctCoefRecon);
            #else
                rgBPCoef[i]  = ctCoefRecon;
            #endif
            }
            if (i < iHighCutOff)
            {
                TRACEWMA_EXIT (wmaResult, pau->aupfnGetNextRun (pcaller, ppcinfo));
                DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
                assert(pau->m_cRunOfZeros < SHRT_MAX);
                *piRecon += (I16) (pau->m_cRunOfZeros+1);
                ctCoefLevel = COEF_FROM_LEVEL(pau->m_iLevel);
            }
        }
    }

#if 0
    for (iCoef = 0; iCoef < cSubband; iCoef++)
    {
        dblDiff1 += LEVEL_FROM_COEF( ABS_COEF(rgBPCoef[iCoef]) );
        dblDiff2 += LEVEL_FROM_COEF( ABS_COEF(rgBPCoefReOrder[iCoef]) );
    }
    // assert((dblDiff1 -dblDiff2) < 1.0);
#endif //
    //DUMPDATA(rgBPCoef, cSubband*sizeof(CoefType), "d:\\temp\\c.dat","wb");
    //DUMPDATA(rgBPCoefReOrder, cSubband*sizeof(CoefType), "d:\\temp\\d.dat","wb");
exit:
    return wmaResult;
} // prvInterleavedRLCBPCoefQ


WMARESULT prvBasePlusDecodePDFShiftModeParams (CAudioObjectDecoder* paudec, 
                                   PerChannelInfo* ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    U32 ulResult;
    const Int iPeriodLimit = (ppcinfo->m_cSubFrameSampleHalf/BPLUS_MIN_PERIODS_PERSUBFRM_PDFSHIFT);

    PLUS_GETBITS(wmaResult, LOG2(iPeriodLimit), &ulResult);
    ppcinfo->m_iPeriod4PDFShift = ulResult + 1;

    PLUS_GETBITS(wmaResult, CEILLOG2(ppcinfo->m_iPeriod4PDFShift/2), &ulResult);
    ppcinfo->m_iInsertPos = ulResult;

exit:
    return wmaResult;
} // prvBasePlusDecodePDFShiftModeParams 

WMARESULT prvDecodeRunLevelBP(CAudioObjectDecoder* paudec, 
                              PerChannelInfo* ppcinfo,
                              Int iCoefFirst, 
                              Int iCoefLim)
{
    I32* rgiCoefQ       = ppcinfo->m_rgiCoefQ;
    const U16* rgiRunEntry    = ppcinfo->m_rgiRunEntry;    
    const U16* rgiLevelEntry  = ppcinfo->m_rgiLevelEntry;    
    CAudioObject* pau = paudec->pau;
    I16* piCoef = &pau->m_iCurrReconCoef;   
#ifdef DEBUG_DECODE_TRACE
    DEBUG_ONLY( Bool fPrint = (g_ulOutputSamples==0x4e00); )
#else
    DEBUG_ONLY( Bool fPrint = (pau->m_iFrameNumber  <= 10 && pau->m_rgpcinfo->m_iCurrSubFrame == 0); )
#endif
    WMARESULT   wmaResult = WMA_OK;

    // This function is too frequently called to be profiled
    //FUNCTION_PROFILE(fp);
    //FUNCTION_PROFILE_START(&fp,DECODE_RUN_LEVEL_PROFILE);
    paudec->m_cMaxRun = (I16) LOG2 (iCoefLim - 1) + 1;
    while (*piCoef < iCoefLim) 
    {
        TRACEWMA_EXIT(wmaResult, prvGetNextRunDEC(paudec,ppcinfo));
        pau->m_iLevel = ((pau->m_iLevel ^ pau->m_iSign) - pau->m_iSign);
        DBG_RUNLEVEL_DEC(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,fPrint);
        if ( (*piCoef+ pau->m_cRunOfZeros) >= iCoefLim)  
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);        
        }
//        memset (rgiCoefQ + *piCoef, 0, pau->m_cRunOfZeros * sizeof (I16));
        *piCoef += (I16) pau->m_cRunOfZeros;
        assert(pau->m_iLevel < (1<<16));
        rgiCoefQ [*piCoef] = (U32)pau->m_iLevel;
        MONITOR_RANGE(gMR_iCoefQ,rgiCoefQ [*piCoef]);
        MONITOR_COUNT_CONDITIONAL(pau->m_cRunOfZeros>0,gMC_0CoefQ,pau->m_cRunOfZeros);
        (*piCoef)++;
        paudec->m_rlsts = VLC;
    }

    // no early exit here, so need to add the 1.
    if (pau->m_iLevel != 0)
    {
        ppcinfo->m_cLastCodedIndex = (U16)iCoefLim;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = (U16)(*piCoef - (pau->m_cRunOfZeros+1));
    }
#if 0
    assert(freqexCheckLastCodedIndexI32(rgiCoefQ,
                                        ppcinfo->m_cLastCodedIndex,
                                        iCoefLim));
#endif

exit:
#ifdef WMA_ENTROPY_TEST
    if (!g_maskTest &&
        !WMA_FAILED(wmaResult)) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif
    //FUNCTION_PROFILE_STOP(&fp);
    return wmaResult;
} // prvDecodeRunLevel

WMARESULT prvBasePlusCopyChannelXFormToBase (CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iChGrp;
    Int cChannel = pau->m_cChannel;
    CChannelGroupInfo* pcgiSrc = NULL;
    CChannelGroupInfo* pcgiDst = NULL;

    pau->m_cChannelGroup = pbp->m_cBPChannelGroup;
    for (iChGrp = 0; iChGrp <  pau->m_cChannelGroup; iChGrp++)
    {
        pcgiDst = pau->m_rgChannelGrpInfo + iChGrp;
        pcgiSrc = pbp->m_rgBPChannelGrpInfo + iChGrp;
    
        pcgiDst->m_cChannelsInGrp      = pcgiSrc->m_cChannelsInGrp;
        pcgiDst->m_fIsSuperGroupXform  = pcgiSrc->m_fIsSuperGroupXform;
        pcgiDst->m_fIsPredefinedXform  = pcgiSrc->m_fIsPredefinedXform;
        pcgiDst->m_predefinedXformType = pcgiSrc->m_predefinedXformType;
        pcgiDst->m_fAllBarksOn         = pcgiSrc->m_fAllBarksOn;
        memcpy(pcgiDst->m_rgfXformOn, pcgiSrc->m_rgfXformOn, sizeof(Bool) * NUM_BARK_BAND);
        memcpy(pcgiDst->m_rgfChannelMask, pcgiSrc->m_rgfChannelMask, sizeof(Bool) * cChannel);
        memcpy(pcgiDst->m_rgbRotationAngle, pcgiSrc->m_rgbRotationAngle,
            sizeof(I8) * (cChannel * (cChannel -1)/2));
        memcpy(pcgiDst->m_rgbRotationSign, pcgiSrc->m_rgbRotationSign,
            sizeof(I8) * cChannel);
        // Memory not allocated in CBasePlusObject
      //  memcpy(pcgiDst->m_rgfltMultiXForward, pcgiSrc->m_rgfltMultiXForward, 
      //      sizeof(Float) *
      //              cChannel * cChannel);
        memcpy(pcgiDst->m_rgfltMultiXInverse, pcgiSrc->m_rgfltMultiXInverse, 
               sizeof(ChXFormType) * cChannel * cChannel);
    }
    return wmaResult;
} // prvBasePlusCopyChannelXFormFromBase

WMARESULT prvBasePlusDecodeWeightFactorOverlayMode(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    CAudioObject* pau = paudec->pau;        
    CBasePlusObject* pbp = pau->m_pbp;
    
    PerChannelInfo *ppcinfo = NULL;
    Int cValidSFBandBackup = pbp->m_cValidSFBand;
    I32 iCh, iChSrc;
    
    for (iCh=0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile[iCh];
        ppcinfo = pau->m_rgpcinfo + iChSrc;

        pau->m_iCurrReconMaskBand = 0;
        paudec->m_maskrlsts = VLC;
        
        // make prvGetNextSFRunDEC work
        pbp->m_cValidSFBand = ppcinfo->m_cBadCoefSegs;

        if (pbp->m_bSingleWeightFactor)
        {
            PLUS_GETBITS(wmaResult, CEILLOG2(MAX_WEIGHT_FACTOR/pbp->m_iWeightQuantMultiplier), &ppcinfo->m_iMaxWeightFactor);
        }
        else
        {
            TRACEWMA_EXIT(wmaResult, prvDecodeWeightRunLevel  (
                            paudec, 
                            ppcinfo,
                            ppcinfo->m_cBadCoefSegs,
                            g_rgunRunWeightV3,//g_rgunRunMaskV3BP0,
                            g_rgunLevelWeightV3, //g_rgunLevelMaskV3BP0,
                            g_rgunHuffDecTblWeightRLCV3//g_rgunHuffDecTblMaskRLCV3BP0
                            ));
        }
        pbp->m_cValidSFBand = cValidSFBandBackup;

        paudec->pau->m_iCurrReconCoef = -1;
        pau->aupfnGetNextRun = prvGetNextRunDECVecNonRL;
        prvResetRunLevelState(paudec); // reset run level decoding

    }
exit:

    pbp->m_cValidSFBand = cValidSFBandBackup;

    paudec->pau->m_iCurrReconCoef = -1;
    pau->aupfnGetNextRun = prvGetNextRunDECVecNonRL;
    prvResetRunLevelState(paudec); // reset run level decoding

    return wmaResult;   
}

WMARESULT prvBasePlusReset(CAudioObjectDecoder *paudec)
{
    WMARESULT wmaResult = WMA_OK;
    paudec->m_fDecodingBPlus = WMAB_FALSE;
    paudec->pau->m_fBasePlusPresent = WMAB_FALSE;
    return wmaResult;
}

#endif // (BUILD_WMAPRO) && (BUILD_WMAPROLBRV2)
