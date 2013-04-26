//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************


#include "msaudio.h"
#if defined (BUILD_WMAPROLBRV2) && defined (BUILD_WMAPRO)
#include "basepluspro.h"

#if defined(BUILD_WMAPROLBRV1)
#include "fex.h"
#endif

AVRT_DATA const I32 g_rgiHoleWidthCodeBook[2] = {400, 800};

AVRT_DATA const U32 g_rgiSFFreq_inf	[SFFREQ_INF_SIZE] =  // Same as g_rgiBarkFreqV3
{  
   100,    200,    300,    400,    510, 
   630,    770,    920,   1080,   1270,
  1480,   1720,   2000,   2320,   2700,
  3150,   3700,   4400,   5300,   6400,
  7700,   9500,  12000,  15500,  20675,
 28575,  41375,  63875
}; 


AVRT_DATA const U32 g_rgiSFFreq_1600	[SFFREQ_16K_SIZE] = 
{
   100,    200,    300,    400,    510,    630,    770,    920,   1080,   1270,
  1480,   1720,   2000,   2320,   2700,   3150,   3700,   4400,   5300,   6400,
  7700,   9500,  12000,  13750,  15500,  17225,  18950,  20675,  22650,  24625,
 26600,  28575,  30175,  31775,  33375,  34975,  36575,  38175,  39775,  41375,
 42982,  44589,  46196,  47803,  49410,  51017,  52624,  54231,  55838,  57445,
 59052,  60659,  62266,  63875
};



AVRT_DATA const U32 g_rgiSFFreq_800	[SFFREQ_8K_SIZE] = 
{
   100,    200,    300,    400,    510,    630,    770,    920,   1080,   1270,
  1480,   1720,   2000,   2320,   2700,   3150,   3700,   4400,   5300,   6400,
  7700,   8600,   9500,  10333,  11166,  12000,  12875,  13750,  14625,  15500,
 16362,  17224,  18086,  18948,  19810,  20675,  21552,  22429,  23306,  24183,
 25060,  25937,  26814,  27691,  28575,  29375,  30175,  30975,  31775,  32575,
 33375,  34175,  34975,  35775,  36575,  37375,  38175,  38975,  39775,  40575,
 41375,  42178,  42981,  43784,  44587,  45390,  46193,  46996,  47799,  48602,
 49405,  50208,  51011,  51814,  52617,  53420,  54223,  55026,  55829,  56632,
 57435,  58238,  59041,  59844,  60647,  61450,  62253,  63056,  63875
};


AVRT_DATA const U32 g_rgiSFFreq_400	[SFFREQ_4K_SIZE] = 
{
        100,    200,    300,    400,    510,    630,    770,    920,   1080,   1270,
        1480,   1720,   2000,   2320,   2700,   3150,   3700,   4400,   4850,   5300,
        5850,   6400,   6833,   7266,   7700,   8150,   8600,   9050,   9500,   9916,
        10332,  10748,  11164,  11580,  12000,  12437,  12874,  13311,  13748,  14185,
        14622,  15059,  15500,  15931,  16362,  16793,  17224,  17655,  18086,  18517,
        18948,  19379,  19810,  20241,  20675,  21090,  21505,  21920,  22335,  22750,
        23165,  23580,  23995,  24410,  24825,  25240,  25655,  26070,  26485,  26900,
        27315,  27730,  28145,  28575,  28975,  29375,  29775,  30175,  30575,  30975,
        31375,  31775,  32175,  32575,  32975,  33375,  33775,  34175,  34575,  34975,
        35375,  35775,  36175,  36575,  36975,  37375,  37775,  38175,  38575,  38975,
        39375,  39775,  40175,  40575,  40975,  41375,  41776,  42177,  42578,  42979,
        43380,  43781,  44182,  44583,  44984,  45385,  45786,  46187,  46588,  46989,
        47390,  47791,  48192,  48593,  48994,  49395,  49796,  50197,  50598,  50999,
        51400,  51801,  52202,  52603,  53004,  53405,  53806,  54207,  54608,  55009,
        55410,  55811,  56212,  56613,  57014,  57415,  57816,  58217,  58618,  59019,
        59420,  59821,  60222,  60623,  61024,  61425,  61826,  62227,  62628,  63029,
        63430,  63875
};

AVRT_DATA const U32 MAX_SF_BANDS_TBL[NUM_SFBAND_TABLES]  = 
{SFFREQ_INF_SIZE, SFFREQ_16K_SIZE, SFFREQ_8K_SIZE, SFFREQ_4K_SIZE};

// 0.90
const U16 gNLQDecTblSize9 = 18;
AVRT_DATA const FPNLQ gNLQDecTbl9[18] = {
    FPNLQFRMFLT(0.0000f),  FPNLQFRMFLT(1.0400f),  FPNLQFRMFLT(2.2032f),  FPNLQFRMFLT(3.4346f),  
    FPNLQFRMFLT(4.7127f),  FPNLQFRMFLT(6.0268f),  FPNLQFRMFLT(7.3704f),  FPNLQFRMFLT(8.7391f), 
    FPNLQFRMFLT(10.1296f), FPNLQFRMFLT(11.5396f), FPNLQFRMFLT(12.9670f), FPNLQFRMFLT(14.4104f), 
    FPNLQFRMFLT(15.8683f), FPNLQFRMFLT(17.3398f), FPNLQFRMFLT(18.8240f), FPNLQFRMFLT(20.3199f), 
    FPNLQFRMFLT(21.8269f), FPNLQFRMFLT(23.3444f)
};

// 0.80
const U16 gNLQDecTblSize8 = 18;
AVRT_DATA const FPNLQ gNLQDecTbl8[18] = {
    FPNLQFRMFLT(0.0000f),  FPNLQFRMFLT(1.0000f),  FPNLQFRMFLT(2.3784f),  FPNLQFRMFLT(3.9482f),  
    FPNLQFRMFLT(5.6569f),  FPNLQFRMFLT(7.4767f),  FPNLQFRMFLT(9.3905f),  FPNLQFRMFLT(11.3860f), 
    FPNLQFRMFLT(13.4543f), FPNLQFRMFLT(15.5885f), FPNLQFRMFLT(17.7828f), FPNLQFRMFLT(20.0328f), 
    FPNLQFRMFLT(22.3345f), FPNLQFRMFLT(24.6848f), FPNLQFRMFLT(27.0807f), FPNLQFRMFLT(29.5198f), 
    FPNLQFRMFLT(32.0000f), FPNLQFRMFLT(34.5192f)
};

// 0.70
const U16 gNLQDecTblSize7 = 12;
AVRT_DATA const FPNLQ gNLQDecTbl7[12] = {
    FPNLQFRMFLT(0.0000f),  FPNLQFRMFLT(1.1691f),  FPNLQFRMFLT(2.9167f),  FPNLQFRMFLT(5.0705f),  
    FPNLQFRMFLT(7.5467f),  FPNLQFRMFLT(10.2969f), FPNLQFRMFLT(13.2887f), FPNLQFRMFLT(16.4984f),
    FPNLQFRMFLT(19.9080f), FPNLQFRMFLT(23.5028f), FPNLQFRMFLT(27.2710f), FPNLQFRMFLT(31.2024f)
};

// 0.60
const U16 gNLQDecTblSize6 = 12;
AVRT_DATA const FPNLQ gNLQDecTbl6[12] = {
    FPNLQFRMFLT(0.0000f),  FPNLQFRMFLT(1.2802f),  FPNLQFRMFLT(3.6086f),  FPNLQFRMFLT(6.8039f), 
    FPNLQFRMFLT(10.7592f), FPNLQFRMFLT(15.4069f), FPNLQFRMFLT(20.6985f), FPNLQFRMFLT(26.5968f),
    FPNLQFRMFLT(33.0721f), FPNLQFRMFLT(40.0996f), FPNLQFRMFLT(47.6583f), FPNLQFRMFLT(55.7303f)
};


CBasePlusObject* bpNew()
{
    CBasePlusObject* pbp = (CBasePlusObject*) auMalloc (sizeof (CBasePlusObject));

    if ( pbp == NULL )
    {
        WMARESULT wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        // Cant return wmaResult!
        return pbp;
    }

    memset(pbp, 0, sizeof(CBasePlusObject));

    return pbp;
} // bpNew

Void bpDelete(CAudioObject*    pau,
              CBasePlusObject* pbp)
{

    if (NULL == pbp)
        return;

    if (pbp->m_rgrgcValidSFBand)
    {
        Int k;
        for (k = 0; k < NUM_SFBAND_TABLES; k++)
        {
            DELETE_ARRAY(pbp->m_rgrgcValidSFBand[k]);
        }
        DELETE_ARRAY(pbp->m_rgrgcValidSFBand);
    }

    if (pbp->m_rgrgiSFBandIndexOrig)
    {
        Int k;

        for (k = 0; k < NUM_SFBAND_TABLES; k++)
        {
            DELETE_ARRAY(pbp->m_rgrgiSFBandIndexOrig[k]);
        }
        DELETE_ARRAY(pbp->m_rgrgiSFBandIndexOrig);
    }

    DELETE_ARRAY(pbp->m_rgiSFBandIndexPrev);
    DELETE_ARRAY(pbp->m_rgiSFBandIndexCurr);
    DELETE_ARRAY(pbp->m_rgiSFQ);
    DELETE_ARRAY(pbp->m_rgiSFBandMarker);
    DELETE_ARRAY(pbp->m_rgiSFQResampled);
#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
    freeAligned (pbp->m_rgBPCoef);
#endif //BASEPLUS_CREATE_DECODER_BPCOEF_BUF
    freeAligned (pbp->m_rgiBPBadCoef);
    DELETE_ARRAY(pbp->m_rgrgiBPBadCoef);
    freeAligned (pbp->m_rgiBadCoefSegPos);
    freeAligned (pbp->m_rgiBPWeightFactor);

    if (pau != NULL) 
    {
        prvDeleteChannelGrpInfo(&(pbp->m_rgBPChannelGrpInfo), pau->m_cChannel);
    }
    DELETE_ARRAY(pbp->m_rgfBPVisited);
    DELETE_ARRAY(pbp);

} // bpDelete

WMARESULT bpInit (CAudioObject*    pau,
                  CBasePlusObject* pbp)
{
    WMARESULT wmaResult = WMA_OK;
    Int k;
    Int cShrBufLen = 0;

    if (NULL == pau ||
        NULL == pbp)
    {
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
    if (pau->m_iVersion < 3)
    {
        // No base plus for WMA Standard
        return wmaResult;
    }

    // Allocate memory
    pbp->m_rgrgcValidSFBand = (Int**) auMalloc (sizeof(Int*) * NUM_SFBAND_TABLES);
    if (NULL == pbp->m_rgrgcValidSFBand)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pbp->m_rgrgcValidSFBand, 0, sizeof(Int*) * NUM_SFBAND_TABLES);

    for (k = 0; k < NUM_SFBAND_TABLES; k++)
    {
        pbp->m_rgrgcValidSFBand[k] = (Int*) auMalloc (sizeof (Int) * pau->m_cPossibleWinSize);
        if (NULL == pbp->m_rgrgcValidSFBand[k])
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(pbp->m_rgrgcValidSFBand[k], 0, sizeof(Int*) * pau->m_cPossibleWinSize);
    }
    
    pbp->m_rgrgiSFBandIndexOrig = (I16**) auMalloc (sizeof (I16*) * NUM_SFBAND_TABLES);
    if (NULL == pbp->m_rgrgiSFBandIndexOrig)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pbp->m_rgrgiSFBandIndexOrig, 0, sizeof(I16*) * NUM_SFBAND_TABLES);

    for (k = 0; k < NUM_SFBAND_TABLES; k++)
    {
        pbp->m_rgrgiSFBandIndexOrig[k] = (I16*) auMalloc (sizeof (I16) * (MAX_SF_BANDS_TBL[k] + 1)); //+1 : including bottom and top end
        if (NULL == pbp->m_rgrgiSFBandIndexOrig[k])
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(pbp->m_rgrgiSFBandIndexOrig[k], 0, sizeof(I16) * (MAX_SF_BANDS_TBL[k] + 1));
    }

    pbp->m_rgiSFBandIndexPrev = (I16*) auMalloc (sizeof(I16) * (MAX_SF_BANDS + 1));
    if (NULL == pbp->m_rgiSFBandIndexPrev)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pbp->m_rgiSFBandIndexPrev, 0, sizeof(I16) * (MAX_SF_BANDS + 1));

    pbp->m_rgiSFBandIndexCurr = (I16*) auMalloc (sizeof(I16) * (MAX_SF_BANDS + 1));
    if (NULL == pbp->m_rgiSFBandIndexCurr)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pbp->m_rgiSFBandIndexCurr, 0, sizeof(I16) * (MAX_SF_BANDS + 1));

    //default
    pbp->m_iCurrSFBandTable = 0;
    pbp->m_rgiSFBandIndex = pbp->m_rgrgiSFBandIndexOrig[0];
    pbp->m_cValidSFBand   = pbp->m_rgrgcValidSFBand [0][0];
   
    pbp->m_fFrameParamUpdate = WMAB_FALSE;
    pbp->m_fUseProMaskRunLevelTbl = WMAB_FALSE;
    pbp->m_fLowDelayWindow = WMAB_FALSE;
    pbp->m_iOverlapWindowDelay = 1; //10ms, can be 10ms, 20ms, 40ms
    pbp->m_iCurrSFBandTable = 3;    // 1-3 for finer SF.
    pbp->m_fLinearQuantization = 1; // linear quantization.
    pbp->m_NLQIdx = 1;
    pbp->m_fScalePriorToChannelXformAtDec = WMAB_FALSE;    

    pbp->m_iHoleWidthMinIdx = 0;
    pbp->m_bSingleWeightFactor = WMAB_TRUE;
    pbp->m_iWeightQuantMultiplier = 1;

    pbp->m_rgiSFQ         = (I32*) auMalloc (sizeof (I32) * MAX_SF_BANDS * pau->m_cChannel);
    if (NULL == pbp->m_rgiSFQ)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgiSFQ, 0, sizeof (I32) * MAX_SF_BANDS * pau->m_cChannel);

    pbp->m_rgiSFBandMarker = (I8*) auMalloc (sizeof (I8) * MAX_SF_BANDS);
    if (NULL == pbp->m_rgiSFBandMarker)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgiSFBandMarker, 0, sizeof (I8) * MAX_SF_BANDS);

    pbp->m_rgiSFQResampled         = (I32*) auMalloc (sizeof (I32) * MAX_SF_BANDS * pau->m_cChannel);
    if (NULL == pbp->m_rgiSFQResampled)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgiSFQResampled, 0, sizeof (I32) * MAX_SF_BANDS * pau->m_cChannel);

#ifdef BASEPLUS_CREATE_DECODER_BPCOEF_BUF
    pbp->m_rgBPCoef      = (CoefType*) mallocAligned (sizeof (CoefType) * pau->m_cFrameSampleHalf * pau->m_cChannel, 32);
    if (NULL == pbp->m_rgBPCoef)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgBPCoef, 0, sizeof (CoefType) * pau->m_cFrameSampleHalf * pau->m_cChannel);
#endif //BASEPLUS_CREATE_DECODER_BPCOEF_BUF

    assert(pau->m_cFrameSampleHalf % 32 == 0);
    // max(2, pau->m_cChannel) guarantee buffer is large then to for m_rgi16BPTmpBufA and m_rgi16BPTmpBufB which
    // are both pau->m_cFrameSampleHalf / 4 bytes.
    cShrBufLen = max((I32)sizeof(I32) * pau->m_cFrameSampleHalf / 32 * pau->m_cChannel, (I32)pau->m_cFrameSampleHalf / 4 * 2);
    pbp->m_rgiBPBadCoef = (I32*) mallocAligned(cShrBufLen, 32);
    if (NULL == pbp->m_rgiBPBadCoef)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgiBPBadCoef, 0, cShrBufLen);

    pbp->m_rgrgiBPBadCoef = (I32**) auMalloc(sizeof(I8*) * pau->m_cChannel);
    if (NULL == pbp->m_rgrgiBPBadCoef)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgrgiBPBadCoef, 0, sizeof(I32*) * pau->m_cChannel);

    pbp->m_rgiBadCoefSegPos = (I16*) mallocAligned(sizeof(I16) * BPPLUS_MAXBADCOEFSEG * 2 * pau->m_cChannel, 32);
    if (NULL == pbp->m_rgiBadCoefSegPos)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgiBadCoefSegPos, 0, sizeof(I16) * BPPLUS_MAXBADCOEFSEG * 2 * pau->m_cChannel);

    pbp->m_rgiBPWeightFactor = (I32*) mallocAligned(sizeof(I32) * BPPLUS_MAXBADCOEFSEG * pau->m_cChannel, 32);
    if (NULL == pbp->m_rgiBPWeightFactor)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset (pbp->m_rgiBPWeightFactor, 0, sizeof(I32) * BPPLUS_MAXBADCOEFSEG * pau->m_cChannel);


    // Channel matrices
    pbp->m_cBPChannelGroup = 0;

    TRACEWMA_EXIT(wmaResult, 
        prvAllocChannelGrpInfo((CChannelGroupInfo**)&(pbp->m_rgBPChannelGrpInfo), pau->m_cChannel));
    
    for (k = 0; k < pau->m_cChannel; k++) 
    {
        pbp->m_rgBPChannelGrpInfo[k].m_rgfltMultiXForward = NULL;
        // No extra space needed at decoder for inverse: No inversion performed.
        pbp->m_rgBPChannelGrpInfo[k].m_rgfltMultiXInverse = (ChXFormType*) auMalloc(sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
        if (pbp->m_rgBPChannelGrpInfo[k].m_rgfltMultiXInverse == NULL) 
        {
            wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
            goto exit;
        }
        memset(pbp->m_rgBPChannelGrpInfo[k].m_rgfltMultiXInverse, 0, sizeof(ChXFormType) * pau->m_cChannel * pau->m_cChannel);
    }
    pbp->m_rgfBPVisited = (Bool*) auMalloc(sizeof(Bool) * pau->m_cChannel);
    if (NULL == pbp->m_rgfBPVisited)
    {
        wmaResult = TraceResult(WMA_E_OUTOFMEMORY);
        goto exit;
    }
    memset(pbp->m_rgfBPVisited, 0, sizeof(Bool) * pau->m_cChannel);

    // m_rgi16BPTmpBufA and m_rgi16BPTmpBufB are only used in exclusive mode and m_rgiBPBadCoef is only used
    // in overlay mode so they share the same memory. both m_rgi16BPTmpBufA/B need cFrameSampleHalf/4 bytes
    pbp->m_rgi16BPTmpBufA = (I16*)pbp->m_rgiBPBadCoef;
    pbp->m_rgi16BPTmpBufB = (I16*)((I8*)pbp->m_rgiBPBadCoef + pau->m_cFrameSampleHalf / 4);
    assert(pau->m_cFrameSampleHalf / 4 * 2 <= cShrBufLen);
    pbp->m_rgi16BPTmpBufC = (I16*)pbp->m_rgiBPBadCoef; //for runtblmap

    // Initialize all resolutions of barks.
    assert(SFFREQ_INF_SIZE == sizeof(g_rgiSFFreq_inf)/sizeof(g_rgiSFFreq_inf[0]));
    assert(SFFREQ_16K_SIZE== sizeof(g_rgiSFFreq_1600)/sizeof(g_rgiSFFreq_1600[0]));
    assert(SFFREQ_8K_SIZE == sizeof(g_rgiSFFreq_800)/sizeof(g_rgiSFFreq_800[0]));
    assert(SFFREQ_4K_SIZE == sizeof(g_rgiSFFreq_400)/sizeof(g_rgiSFFreq_400[0]));

    prvSetSFIndex(pau,
        0,
        g_rgiSFFreq_inf,
        SFFREQ_INF_SIZE,
        pbp->m_rgrgiSFBandIndexOrig[0],
        pbp->m_rgrgcValidSFBand[0]);
    prvSetSFIndex(pau,
        1,
        g_rgiSFFreq_1600,
        SFFREQ_16K_SIZE,
        pbp->m_rgrgiSFBandIndexOrig[1],
        pbp->m_rgrgcValidSFBand[1]);
    prvSetSFIndex(pau,
        2,
        g_rgiSFFreq_800,
        SFFREQ_8K_SIZE,
        pbp->m_rgrgiSFBandIndexOrig[2],
        pbp->m_rgrgcValidSFBand[2]);
    prvSetSFIndex(pau,
        3,
        g_rgiSFFreq_400,
        SFFREQ_4K_SIZE,
        pbp->m_rgrgiSFBandIndexOrig[3],
        pbp->m_rgrgcValidSFBand[3]);
 
    // Per-channel: Done in encoder & decoder
exit:
    return wmaResult;
} // bpInit

Void  prvSetSFIndex(CAudioObject* pau,
                    const I32  iTblIdx,
                    const U32* rgiSFFreq,
                    const I32  cSFFreqSize,
                    I16*       rgiSFBandIndexOrig,
                    Int*       rgcValidSFBand)
{
    Int iWin;
        
    for (iWin = 0; iWin < pau->m_cPossibleWinSize; iWin++)  
    {
        I16 *piSFBandIndex = rgiSFBandIndexOrig;
        I16 *piSFBandIndexWin0 = rgiSFBandIndexOrig;
        Int  cFrameSample  = pau->m_cFrameSample / (1 << iWin);
        I16 iIndex;
        Int iFreqCurr = 0;
        Int iCurr = 1;

        if (0 == iWin)
        {
            piSFBandIndex  [0] = 0;
            while(WMAB_TRUE)
            {
                assert((U32)iCurr < MAX_SF_BANDS_TBL[iTblIdx]);
                assert((U32)iFreqCurr < MAX_SF_BANDS_TBL[iTblIdx]);
                iIndex  = (I16)((rgiSFFreq[iFreqCurr] * cFrameSample)/pau->m_iSamplingRate + 2);
                iIndex -= iIndex % 4; // Make a multiple of 4 through truncation
                
                if(iIndex > piSFBandIndex[iCurr - 1])
                {
                    piSFBandIndex[iCurr] = iIndex;
                    iCurr++;
                }

                iFreqCurr++;
                if(iFreqCurr >= cSFFreqSize ||
                    piSFBandIndex[iCurr - 1] >= cFrameSample/2)
                {
                    piSFBandIndex[iCurr - 1] = (I16)cFrameSample/2;
                    rgcValidSFBand[iWin] = iCurr - 1;
                    break;
                }
            }
        }
        else
        {
            Int iHalfScale = (1 << (iWin+1));  // 1<<(iWin-1)*4
            Int iCurrWin0 = 0;
            Int iLastValidIndexNew = 0;
            for (iCurrWin0 = 1; iCurrWin0 <= rgcValidSFBand[0]; iCurrWin0++)
            {
                Int iIndexNew = (piSFBandIndexWin0[iCurrWin0] + iHalfScale) >> (iWin + 2);
                iIndexNew = iIndexNew << 2;
                assert(iIndexNew <= cFrameSample/2);
                if (iIndexNew > iLastValidIndexNew)
                {
                    iLastValidIndexNew = iIndexNew;
                    iCurr++;
                }
            }
            rgcValidSFBand[iWin] = iCurr - 1;
        }
    }
} // prvInitSFIndex


WMARESULT prvBPInvQuantize_Channel(CAudioObject*        pau, 
                                   PerChannelInfo*      ppcinfo,
                                   Int                  iCh)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;
    CoefType* rgBPCoef = ppcinfo->m_rgBPCoef;

    const I16* rgiSFBandIndex = pbp->m_rgiSFBandIndex;
    const Int  cValidSFBand   = pbp->m_cValidSFBand;
    Int cValidBarkBand = pau->m_cValidBarkBand;
    Int iBand, i;
    U16 cLastCodedIndex = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;

    if (ppcinfo->m_bNoDecodeForCx)
        goto exit;

    assert (WMAB_FALSE == pbp->m_fOverlayMode);

    for (iBand = 0; iBand < cValidSFBand; iBand++)
    {
        QuantFloat qfltQuantizer; 
        Int iIndex;
        
        iIndex = (ppcinfo->m_rgiSFQ[iBand] - ppcinfo->m_iMaxSFQ) * pbp->m_iSFQMultiplier;
        iIndex = pbp->m_cBPTileQuant + ppcinfo->m_iBPChannelQuant + iIndex;

        if (rgiSFBandIndex[iBand+1] < pbp->m_iExplicitStartPos)
            continue;

        if (pbp->m_fLinearQuantization)
        {
            qfltQuantizer = qstCalcQuantStep( iIndex, ppcinfo->m_cLeftShiftBitsQuant );
            CHECK_COEF_MUL_FFLT( qfltQuantizer );
            for (i = rgiSFBandIndex[iBand]; i < min(cLastCodedIndex, rgiSFBandIndex[iBand+1]); i++)
            {                
                if (i >= pbp->m_iExplicitStartPos)
                {
                    rgBPCoef[i] = MULT_QUANT_AND_SCALE(rgBPCoef [i],qfltQuantizer);
                }
            }
        }
        else
        {
            qfltQuantizer = qstCalcQuantStep( iIndex, ppcinfo->m_cLeftShiftBitsQuant );
            CHECK_COEF_MUL_FFLT( qfltQuantizer );
            for (i = rgiSFBandIndex[iBand]; i < min(cLastCodedIndex, rgiSFBandIndex[iBand+1]); i++)
            {
                if (i >= pbp->m_iExplicitStartPos)
                {
                    // Reverse the nonlinear processing in encoder.
                    const CoefType coef = rgBPCoef[i];
                    const Int iSign     = ( coef > 0 ) ? 0x80000000 : 0;
                    I32 coefAbs    = LEVEL_FROM_COEF(ABS_COEF( coef ));
                    FPNLQ fpNLQScale = 0;
                    // CTODO: should put /coefAbs into the table.
                    if (coefAbs > 0)
                    {
                        if (coefAbs < pbp->m_NLQDecTblSize)
                        {
                            // rgBPCoef[i] = COEF_FROM_FPNLQ(pbp->m_NLQDecTbl[coefAbs]);
                            fpNLQScale = pbp->m_NLQDecTbl[coefAbs] / coefAbs;
                        }
                        else
                        {
                            FPNLQ fpNLQDist = pbp->m_NLQDecTbl[pbp->m_NLQDecTblSize-1] - pbp->m_NLQDecTbl[pbp->m_NLQDecTblSize-2];
                            fpNLQScale = (pbp->m_NLQDecTbl[pbp->m_NLQDecTblSize-1] 
                                        + (coefAbs-(pbp->m_NLQDecTblSize-1)) * fpNLQDist) / coefAbs;
                        }

                        rgBPCoef[i] = MULT_QUANT_AND_SCALE(rgBPCoef [i],qfltQuantizer);
                        rgBPCoef[i] = MULT_COEF_BY_NLQSCALE(rgBPCoef[i], fpNLQScale);
                    }
                }
            }
        }
    }
    //DUMPDATA(rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "coef_invquan_flt.dat", "wb");
exit:
    return wmaResult;
} // prvBPInvQuantize_Channel

WMARESULT prvBPInvQuantize_Channel_Overlay(CAudioObject*        pau, 
                                   PerChannelInfo*      ppcinfo,
                                   Int                  iCh)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;
    CoefType* rgBPCoef = ppcinfo->m_rgBPCoef;

    const I16* rgiSFBandIndex = pbp->m_rgiSFBandIndex;
    const Int  cValidSFBand   = pbp->m_cValidSFBand;
    Int cValidBarkBand = pau->m_cValidBarkBand;
    Int iBand;
    U16 cLastCodedIndex = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;
    
    I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;         
    I32 *rgiBPCoefWeight = ppcinfo->m_rgiBPWeightFactor;         

    QuantFloat qfltQuantizer; 

    Int iIndex;
    Int iCoef;
    Int iSeg;

    // In overlay mode, use base layer's mask
    // CTODO: we should make this pbp->m_iSFQMultiplier per channel thing 
    //        so we can move this block to prvBasePlusEncodeTile
    pbp->m_iSFQMultiplier  = ppcinfo->m_iMaskQuantMultiplier;
    ppcinfo->m_iMaxSFQ = ppcinfo->m_iMaxMaskQ;
    assert(cValidSFBand == cValidBarkBand);
    ppcinfo->m_iBPChannelQuant = ppcinfo->m_ucQuantStepModifierIndex;

    assert (WMAB_TRUE == pbp->m_fLinearQuantization);
    assert (WMAB_TRUE == pbp->m_fOverlayMode);

    iBand = 0;
    iIndex = (ppcinfo->m_rgiSFQ[iBand] - ppcinfo->m_iMaxSFQ) * pbp->m_iSFQMultiplier;
    iIndex = pbp->m_cBPTileQuant + ppcinfo->m_iBPChannelQuant + iIndex;
    qfltQuantizer = qstCalcQuantStep( iIndex, ppcinfo->m_cLeftShiftBitsQuant );

    if (ppcinfo->m_bNoDecodeForCx)
        goto exit;

    for (iSeg = 0; iSeg < ppcinfo->m_cBadCoefSegs; iSeg++)
    {
        I32 iStart = rgiBadCoefSegPos[iSeg<<1];
        I32 iEnd = rgiBadCoefSegPos[(iSeg<<1)+1];
        for (iCoef = iStart; iCoef <= iEnd; iCoef++)
        {
            while (iCoef >= rgiSFBandIndex[iBand+1])
		    {
                iBand++;
                assert(iBand < cValidSFBand);
                iIndex = (ppcinfo->m_rgiSFQ[iBand] - ppcinfo->m_iMaxSFQ) * pbp->m_iSFQMultiplier;
                iIndex = pbp->m_cBPTileQuant + ppcinfo->m_iBPChannelQuant + iIndex;
                qfltQuantizer = qstCalcQuantStep( iIndex, ppcinfo->m_cLeftShiftBitsQuant ); 
                CHECK_COEF_MUL_FFLT( qfltQuantizer );
            }

            rgBPCoef[iCoef] = MULT_QUANT_AND_SCALE(rgBPCoef [iCoef],qfltQuantizer);
        }
    }

exit:
    return wmaResult;
} // prvBPInvQuantize_Channel_Overlay

WMARESULT prvBPInvQuantize(CAudioObject*        pau, 
                           CChannelGroupInfo*   pcgi)
{
    WMARESULT wmaResult = WMA_OK;
    Int iCh;
    
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
        Bool *rgfChannelMask = pcgi->m_rgfChannelMask;
        
        if (rgfChannelMask[iChSrc] == WMAB_TRUE) 
        {
            // This channel needs inverse quantization.
            if (pau->m_pbp->m_fOverlayMode)
            {
#ifdef BUILD_WMAPROLBRV3
                if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2)
                {
                    // get the base-peak segement inverse-quantized
                    if (*(ppcinfo->m_pcBasePeakCoefs) > 0)
                        ppcinfo->m_cBadCoefSegs++;
                }
#endif

                TRACEWMA_EXIT(wmaResult, prvBPInvQuantize_Channel_Overlay(pau, ppcinfo, iChSrc));

#ifdef BUILD_WMAPROLBRV3
                if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2)
                {
                    // retrieve #Segs to avoid other places processing the base peak segment
                    if (*(ppcinfo->m_pcBasePeakCoefs) > 0)
                        ppcinfo->m_cBadCoefSegs--;
                }
#endif
            }
            else
            {
                TRACEWMA_EXIT(wmaResult, prvBPInvQuantize_Channel(pau, ppcinfo, iChSrc));
            }
        }
    }

exit:
    return wmaResult;
} // prvBPInvQuantize

WMARESULT prvBPInvChannelXForm(CAudioObject*        pau, 
                               CoefType**           rgpCoefGrpSrc, 
                               CChannelGroupInfo*   pcgi)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject*  pbp = pau->m_pbp;

    I16 iChSrc, iChDst;
    PerChannelInfo* ppcinfo = pau->m_rgpcinfo;
    I32 iCoef;
    
    CoefType* rgfltCoefDst = pau->m_rgfltCoefDst;
    Bool fAllSkip = WMAB_TRUE;

    // V3 bits. Perform inverse multichannel transform
    //I16 cSubbandAdj = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;
    //const U16 cLastCodedIndex = pau->m_cHighCutOff;
    U16 cLastCodedIndex = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;
    Int iBand;
    Bool *rgfChannelMask = pcgi->m_rgfChannelMask;

 
#if (CX_DECODE_MONO==1)
    if (pau->m_bCx && WMAB_FALSE==pau->m_bEncoder)
    {
        CChannelGroupInfo* pcgi = pau->m_rgChannelGrpInfo + 0;
        if (1 != pau->m_cChannelGroup)
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        if (pau->m_cChannel != pcgi->m_cChannelsInGrp ||
            WMAB_FALSE == pcgi->m_fIsPredefinedXform)
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        goto exit;
    }
#endif

    if (pcgi->m_cChannelsInGrp == 1 || 
        (pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
        pcgi->m_predefinedXformType == MULTICH_IDENTITY)) 
    {
        // Identity transform for this channel group: do nothing
    } 
    else if (pau->m_cChannel == 2 &&
        pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
        pcgi->m_predefinedXformType == MULTICH_HADAMARD) 
    {
        // Somewhat faster processing for stereo-pairs in stereo coding: weights absorbed into
        // encoder's forward matrix.
        CoefType* pfltCoefSrc0 = rgpCoefGrpSrc[0];
        CoefType* pfltCoefSrc1 = rgpCoefGrpSrc[1];
                    
        assert(pcgi->m_cChannelsInGrp == 2);

        for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++)
        {
            if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE)
            {
                for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                    iCoef <  min(cLastCodedIndex, pau->m_rgiBarkIndex[iBand+1]); 
                    iCoef++) 
                {
                    if (iCoef >= pbp->m_iExplicitStartPos)
                    {
                        CoefType fltDst0 = *pfltCoefSrc0 - *pfltCoefSrc1;
                        CoefType fltDst1 = *pfltCoefSrc0 + *pfltCoefSrc1;

                        *pfltCoefSrc0++ = fltDst0;
                        *pfltCoefSrc1++ = fltDst1;
                    }
                    else
                    {
                        pfltCoefSrc0++;
                        pfltCoefSrc1++;
                    }
                }
            } 
            else 
            {
                //WMAFprintf(stdout, "Here\n");
                // identity transform for this bark: Just do the scaling.
                for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                    iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                    iCoef++) 
                {
                    if (iCoef >= pbp->m_iExplicitStartPos)
                    {
                        *pfltCoefSrc0 = MULT_CH_SQRT2(*pfltCoefSrc0);
                        *pfltCoefSrc1 = MULT_CH_SQRT2(*pfltCoefSrc1);
                    }
					pfltCoefSrc0++;
					pfltCoefSrc1++;
                }
            }
        }
    }           //end of Hadamard
    else    //generic transform
    {
        // Multiple channels or generalized transformation
        // Other predefined transforms, if used, should have proper values set in m_rgfltMultiXInverse

        // Collect group members and associated matrices together: could be done outside to
        // save some cycles in encoding loops: to be done.
        CoefType** rgpCoefGrpSrc = (CoefType**)pau->m_rgpfltCoefGrpSrc;
        Int    cChannelsInGrp = pcgi->m_cChannelsInGrp;
        Int    iCh0=0, iCh1=0;
        ChXFormType* rgfltMultiXGrpInverse = pcgi->m_rgfltMultiXInverse;

        // Code bloat for a few popular channel group sizes.
        if (cChannelsInGrp == 2)
        {
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (iCoef >= pbp->m_iExplicitStartPos)
                        {
                            const CoefType dst0 = 
                                MULT_CH(rgfltMultiXGrpInverse[0], *(rgpCoefGrpSrc [0])) + 
                                MULT_CH(rgfltMultiXGrpInverse[1], *(rgpCoefGrpSrc [1]));
                            const CoefType dst1 = 
                                MULT_CH(rgfltMultiXGrpInverse[2], *(rgpCoefGrpSrc [0])) + 
                                MULT_CH(rgfltMultiXGrpInverse[3], *(rgpCoefGrpSrc [1]));
                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                        }
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else if (cChannelsInGrp == 3)
        {
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (iCoef >= pbp->m_iExplicitStartPos)
                        {
    #define DOT_PRODUCT_3(n) MULT_CH(rgfltMultiXGrpInverse[3*(n)+0], *(rgpCoefGrpSrc [0])) + \
        MULT_CH(rgfltMultiXGrpInverse[3*(n)+1], *(rgpCoefGrpSrc [1])) + \
        MULT_CH(rgfltMultiXGrpInverse[3*(n)+2], *(rgpCoefGrpSrc [2]))

                            const CoefType dst0 = DOT_PRODUCT_3(0);
                            const CoefType dst1 = DOT_PRODUCT_3(1);
                            const CoefType dst2 = DOT_PRODUCT_3(2);

                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                            *rgpCoefGrpSrc[2]++ = dst2;
    #undef DOT_PRODUCT_3
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                            rgpCoefGrpSrc[2]++;
                        }
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [2] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else if (cChannelsInGrp == 4)
        {
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (iCoef >= pbp->m_iExplicitStartPos)
                        {
    #define DOT_PRODUCT_4(n) MULT_CH(rgfltMultiXGrpInverse[4*(n)+0], *(rgpCoefGrpSrc [0])) + \
        MULT_CH(rgfltMultiXGrpInverse[4*(n)+1], *(rgpCoefGrpSrc [1])) + \
        MULT_CH(rgfltMultiXGrpInverse[4*(n)+2], *(rgpCoefGrpSrc [2])) + \
        MULT_CH(rgfltMultiXGrpInverse[4*(n)+3], *(rgpCoefGrpSrc [3]))

                            const CoefType dst0 = DOT_PRODUCT_4(0);
                            const CoefType dst1 = DOT_PRODUCT_4(1);
                            const CoefType dst2 = DOT_PRODUCT_4(2);
                            const CoefType dst3 = DOT_PRODUCT_4(3);

                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                            *rgpCoefGrpSrc[2]++ = dst2;
                            *rgpCoefGrpSrc[3]++ = dst3;
    #undef DOT_PRODUCT_4
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                            rgpCoefGrpSrc[2]++;
                            rgpCoefGrpSrc[3]++;
                        }
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [2] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [3] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else if (cChannelsInGrp == 5)
        {
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (iCoef >= pbp->m_iExplicitStartPos)
                        {
    #define DOT_PRODUCT_5(n) MULT_CH(rgfltMultiXGrpInverse[5*(n)+0], *(rgpCoefGrpSrc [0])) + \
        MULT_CH(rgfltMultiXGrpInverse[5*(n)+1], *(rgpCoefGrpSrc [1])) + \
        MULT_CH(rgfltMultiXGrpInverse[5*(n)+2], *(rgpCoefGrpSrc [2])) + \
        MULT_CH(rgfltMultiXGrpInverse[5*(n)+3], *(rgpCoefGrpSrc [3])) + \
        MULT_CH(rgfltMultiXGrpInverse[5*(n)+4], *(rgpCoefGrpSrc [4]))

                            const CoefType dst0 = DOT_PRODUCT_5(0);
                            const CoefType dst1 = DOT_PRODUCT_5(1);
                            const CoefType dst2 = DOT_PRODUCT_5(2);
                            const CoefType dst3 = DOT_PRODUCT_5(3);
                            const CoefType dst4 = DOT_PRODUCT_5(4);

                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                            *rgpCoefGrpSrc[2]++ = dst2;
                            *rgpCoefGrpSrc[3]++ = dst3;
                            *rgpCoefGrpSrc[4]++ = dst4;
    #undef DOT_PRODUCT_5
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                            rgpCoefGrpSrc[2]++;
                            rgpCoefGrpSrc[3]++;
                            rgpCoefGrpSrc[4]++;
                        }
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [2] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [3] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [4] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else
        {
            // Group size is larger than 5
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (iCoef >= pbp->m_iExplicitStartPos)
                        {
                            for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++) {
                                rgfltMultiXGrpInverse = pcgi->m_rgfltMultiXInverse + iChDst * cChannelsInGrp;

                                ((CoefType*)rgfltCoefDst) [iChDst] = 0;
                                for (iChSrc = 0; iChSrc < cChannelsInGrp; iChSrc++) {
                                    ((CoefType*)rgfltCoefDst) [iChDst] += MULT_CH(rgfltMultiXGrpInverse[iChSrc], *(rgpCoefGrpSrc [iChSrc]));
                                }
                            }
                            // Assign back weighted sums.
                            for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++) {
                                *rgpCoefGrpSrc [iChDst] = ((CoefType*)rgfltCoefDst) [iChDst];
                                rgpCoefGrpSrc [iChDst]++;
                            }
                        }
                        else
                        {
                            for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++) {
                                rgpCoefGrpSrc [iChDst]++;
                            }
                        }
                    }
                } 
                else 
                {
                    // identity transform for this bark: do not sweat on this bark band
                    for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++)
                        rgpCoefGrpSrc [iChDst] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            } 
        }
    }

#if (CX_DECODE_MONO==1)
exit:
#endif

    return wmaResult;
} // prvBPInvChannelXForm

WMARESULT prvBPInvChannelXFormOverlay(CAudioObject*        pau, 
                               CoefType**           rgpCoefGrpSrc, 
                               I32**                 rgrgiBPBadCoef,
                               CChannelGroupInfo*   pcgi)
{
    WMARESULT wmaResult = WMA_OK;

    CBasePlusObject *pbp = pau->m_pbp;

    I16 iChSrc, iChDst;
    PerChannelInfo* ppcinfo = pau->m_rgpcinfo;
    I32 iCoef;
    
    CoefType* rgfltCoefDst = pau->m_rgfltCoefDst;
    Bool fAllSkip = WMAB_TRUE;

    // V3 bits. Perform inverse multichannel transform
    //I16 cSubbandAdj = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;
    //const U16 cLastCodedIndex = pau->m_cHighCutOff;
    U16 cLastCodedIndex = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;
    Int iBand;
    Bool *rgfChannelMask = pcgi->m_rgfChannelMask;

    assert(pbp->m_fOverlayMode);

#if (CX_DECODE_MONO==1)
    if (pau->m_bCx && WMAB_FALSE==pau->m_bEncoder)
    {
        CChannelGroupInfo* pcgi = pau->m_rgChannelGrpInfo + 0;
        if (1 != pau->m_cChannelGroup)
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        if (pau->m_cChannel != pcgi->m_cChannelsInGrp ||
            WMAB_FALSE == pcgi->m_fIsPredefinedXform)
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        goto exit;
    }
#endif
 
    if (pcgi->m_cChannelsInGrp == 1 || 
        (pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
        pcgi->m_predefinedXformType == MULTICH_IDENTITY)) 
    {
        // Identity transform for this channel group: do nothing
    } 
    else if (pau->m_cChannel == 2 &&
        pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
        pcgi->m_predefinedXformType == MULTICH_HADAMARD) 
    {
        // Somewhat faster processing for stereo-pairs in stereo coding: weights absorbed into
        // encoder's forward matrix.
        CoefType* pfltCoefSrc0 = rgpCoefGrpSrc[0];
        CoefType* pfltCoefSrc1 = rgpCoefGrpSrc[1];
        I32* rgiBPBadCoef0 = rgrgiBPBadCoef[0];   
        I32* rgiBPBadCoef1 = rgrgiBPBadCoef[1];   
        assert(pcgi->m_cChannelsInGrp == 2);

        for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++)
        {
            if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE)
            {
                for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                    iCoef <  min(cLastCodedIndex, pau->m_rgiBarkIndex[iBand+1]); 
                    iCoef++) 
                {
                    // no need to check the other channel since identifyhole function
                    // guarantee rgiBPBadCoef1[iCoef] == rgiBPBadCoef0[iCoef]
                    if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                    {
                        CoefType fltDst0 = *pfltCoefSrc0 - *pfltCoefSrc1;
                        CoefType fltDst1 = *pfltCoefSrc0 + *pfltCoefSrc1;

                        *pfltCoefSrc0 = fltDst0;
                        *pfltCoefSrc1 = fltDst1;
                    }
                    pfltCoefSrc0++;
                    pfltCoefSrc1++;
                }
            } 
            else 
            {
                //WMAFprintf(stdout, "Here\n");
                // identity transform for this bark: Just do the scaling.
                for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                    iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                    iCoef++) 
                {
                    if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                        *pfltCoefSrc0 = MULT_CH_SQRT2(*pfltCoefSrc0);
                    pfltCoefSrc0++;

                    if (GETBADCOEFFLAG(rgiBPBadCoef1, iCoef))
                        *pfltCoefSrc1 = MULT_CH_SQRT2(*pfltCoefSrc1);
                    pfltCoefSrc1++;
                }
            }
        }
    }           //end of Hadamard
    else    //generic transform
    {
        // Multiple channels or generalized transformation
        // Other predefined transforms, if used, should have proper values set in m_rgfltMultiXInverse

        // Collect group members and associated matrices together: could be done outside to
        // save some cycles in encoding loops: to be done.
        CoefType** rgpCoefGrpSrc = (CoefType**)pau->m_rgpfltCoefGrpSrc;
        Int    cChannelsInGrp = pcgi->m_cChannelsInGrp;
        Int    iCh0=0, iCh1=0;
        ChXFormType* rgfltMultiXGrpInverse = pcgi->m_rgfltMultiXInverse;

        // Code bloat for a few popular channel group sizes.
        if (cChannelsInGrp == 2)
        {
            I32* rgiBPBadCoef0 = rgrgiBPBadCoef[0];   

            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                        {
                            const CoefType dst0 = 
                                MULT_CH(rgfltMultiXGrpInverse[0], *(rgpCoefGrpSrc [0])) + 
                                MULT_CH(rgfltMultiXGrpInverse[1], *(rgpCoefGrpSrc [1]));
                            const CoefType dst1 = 
                                MULT_CH(rgfltMultiXGrpInverse[2], *(rgpCoefGrpSrc [0])) + 
                                MULT_CH(rgfltMultiXGrpInverse[3], *(rgpCoefGrpSrc [1]));
                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                        }
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else if (cChannelsInGrp == 3)
        {
            I32* rgiBPBadCoef0 = rgrgiBPBadCoef[0];   
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
#define DOT_PRODUCT_3(n) MULT_CH(rgfltMultiXGrpInverse[3*(n)+0], *(rgpCoefGrpSrc [0])) + \
    MULT_CH(rgfltMultiXGrpInverse[3*(n)+1], *(rgpCoefGrpSrc [1])) + \
    MULT_CH(rgfltMultiXGrpInverse[3*(n)+2], *(rgpCoefGrpSrc [2]))
                        
                        if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                        {
                            const CoefType dst0 = DOT_PRODUCT_3(0);
                            const CoefType dst1 = DOT_PRODUCT_3(1);
                            const CoefType dst2 = DOT_PRODUCT_3(2);

                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                            *rgpCoefGrpSrc[2]++ = dst2;
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                            rgpCoefGrpSrc[2]++;
                        }
#undef DOT_PRODUCT_3
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [2] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else if (cChannelsInGrp == 4)
        {
            I32* rgiBPBadCoef0 = rgrgiBPBadCoef[0];   
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
#define DOT_PRODUCT_4(n) MULT_CH(rgfltMultiXGrpInverse[4*(n)+0], *(rgpCoefGrpSrc [0])) + \
    MULT_CH(rgfltMultiXGrpInverse[4*(n)+1], *(rgpCoefGrpSrc [1])) + \
    MULT_CH(rgfltMultiXGrpInverse[4*(n)+2], *(rgpCoefGrpSrc [2])) + \
    MULT_CH(rgfltMultiXGrpInverse[4*(n)+3], *(rgpCoefGrpSrc [3]))

                        if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                        {
                            const CoefType dst0 = DOT_PRODUCT_4(0);
                            const CoefType dst1 = DOT_PRODUCT_4(1);
                            const CoefType dst2 = DOT_PRODUCT_4(2);
                            const CoefType dst3 = DOT_PRODUCT_4(3);

                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                            *rgpCoefGrpSrc[2]++ = dst2;
                            *rgpCoefGrpSrc[3]++ = dst3;
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                            rgpCoefGrpSrc[2]++;
                            rgpCoefGrpSrc[3]++;
                        }
#undef DOT_PRODUCT_4
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [2] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [3] += (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else if (cChannelsInGrp == 5)
        {
            I32* rgiBPBadCoef0 = rgrgiBPBadCoef[0];   

            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        
#define DOT_PRODUCT_5(n) MULT_CH(rgfltMultiXGrpInverse[5*(n)+0], *(rgpCoefGrpSrc [0])) + \
    MULT_CH(rgfltMultiXGrpInverse[5*(n)+1], *(rgpCoefGrpSrc [1])) + \
    MULT_CH(rgfltMultiXGrpInverse[5*(n)+2], *(rgpCoefGrpSrc [2])) + \
    MULT_CH(rgfltMultiXGrpInverse[5*(n)+3], *(rgpCoefGrpSrc [3])) + \
    MULT_CH(rgfltMultiXGrpInverse[5*(n)+4], *(rgpCoefGrpSrc [4]))

                        if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                        {
                            const CoefType dst0 = DOT_PRODUCT_5(0);
                            const CoefType dst1 = DOT_PRODUCT_5(1);
                            const CoefType dst2 = DOT_PRODUCT_5(2);
                            const CoefType dst3 = DOT_PRODUCT_5(3);
                            const CoefType dst4 = DOT_PRODUCT_5(4);

                            *rgpCoefGrpSrc[0]++ = dst0;
                            *rgpCoefGrpSrc[1]++ = dst1;
                            *rgpCoefGrpSrc[2]++ = dst2;
                            *rgpCoefGrpSrc[3]++ = dst3;
                            *rgpCoefGrpSrc[4]++ = dst4;
                        }
                        else
                        {
                            rgpCoefGrpSrc[0]++;
                            rgpCoefGrpSrc[1]++;
                            rgpCoefGrpSrc[2]++;
                            rgpCoefGrpSrc[3]++;
                            rgpCoefGrpSrc[4]++;
                        }
#undef DOT_PRODUCT_5
                    }
                } 
                else
                {
                    // identity transform for this bark: do not sweat on this bark band
                    rgpCoefGrpSrc [0] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [1] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [2] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [3] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                    rgpCoefGrpSrc [4] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            }
        }
        else
        {
            // Group size is larger than 5
            for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) 
            {
                if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) 
                {
                    I32* rgiBPBadCoef0 = rgrgiBPBadCoef[0];   
                    for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                        iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                        iCoef++) 
                    {
                        if (GETBADCOEFFLAG(rgiBPBadCoef0, iCoef))
                        {
                            for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++) {
                                rgfltMultiXGrpInverse = pcgi->m_rgfltMultiXInverse + iChDst * cChannelsInGrp;

                                ((CoefType*)rgfltCoefDst) [iChDst] = 0;
                                for (iChSrc = 0; iChSrc < cChannelsInGrp; iChSrc++) {
                                    ((CoefType*)rgfltCoefDst) [iChDst] += MULT_CH(rgfltMultiXGrpInverse[iChSrc], *(rgpCoefGrpSrc [iChSrc]));
                                }
                            }
                            // Assign back weighted sums.
                            for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++) {
                                *rgpCoefGrpSrc [iChDst] = ((CoefType*)rgfltCoefDst) [iChDst];
                                rgpCoefGrpSrc [iChDst]++;
                            }
                        }
                        else
                        {
                            for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++) 
                            {
                                rgpCoefGrpSrc [iChDst]++;
                            }
                        }
                    }
                } 
                else 
                {
                    // identity transform for this bark: do not sweat on this bark band
                    for (iChDst = 0; iChDst < cChannelsInGrp; iChDst++)
                        rgpCoefGrpSrc [iChDst] +=  (pau->m_rgiBarkIndex[iBand+1]- pau->m_rgiBarkIndex[iBand]);
                }
            } 
        }
    }

#if (CX_DECODE_MONO==1)
exit:
#endif

    return wmaResult;
} // prvBPInvChannelXFormOverlay

WMARESULT prvBasePlusReconCoefficients(CAudioObject* pau)
{
    WMARESULT        wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;
    Int cChannelGrp = pbp->m_cBPChannelGroup, iChGrp;
    Bool fScalePriorToChannelXform = pbp->m_fScalePriorToChannelXformAtDec; 

    Int iSeg, iCoef, iEnd;

    assert(pau->m_fBasePlusPresent);

    // reset group and mask for exclusive mode
    if (pau->m_bFreqex &&
        (WMAB_FALSE == pbp->m_fOverlayMode) &&
        ((prvBasePlusIfBaseIsZero(pau) && (!pau->m_bEncoder)) || // decoder use this
         (!pbp->m_fExtendMode && pau->m_bEncoder)))              // encoder use this
    {
        freqexSetChannelDependencyGroup(pau, pbp->m_rgBPChannelGrpInfo,
                                        cChannelGrp);
        freqexZeroNonzeroMask(pau); // clear all mask
    }

    if (WMAB_FALSE == pbp->m_fOverlayMode)
    {
        Int iCh;
        if ((prvBasePlusIfBaseIsZero(pau) && (!pau->m_bEncoder)) || // decoder use this
            (!pbp->m_fExtendMode && pau->m_bEncoder)            // encoder use this
           )
        {	//baseplus exclusive mode
            pau->m_cLastCodedIndex = 1;
            for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
            {
                I16 iChSrc = pau->m_rgiChInTile [iCh];
                PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
                ppcinfo->m_cLastCodedIndex = 1;
            }
        }
        // else // don't reset cLastCodedIndex in semi baseplus exclusive mode.
    }

    pau->m_bXChannelProc = WMAB_FALSE; // reprocess cross channel


    for (iChGrp = 0; iChGrp < cChannelGrp; iChGrp++)
    {
        // Channel transform happens on Bark bands, not Scalefactor bands.
        // Position src correctly for this channel group
        CChannelGroupInfo* pcgi = pbp->m_rgBPChannelGrpInfo + iChGrp;
        Bool *rgfChannelMask = pcgi->m_rgfChannelMask;
        // Collect group members and associated matrices together: could be done outside to
        // save some cycles in encoding loops: to be done.
        CoefType** rgpCoefGrpSrc = (CoefType**)pau->m_rgpfltCoefGrpSrc;
        I32 ** rgrgiBPBadCoef = pbp->m_rgrgiBPBadCoef;
        Int    cChannelsInGrp = pcgi->m_cChannelsInGrp;
        Int    iCh0=0, iCh1=0, iCh;
        ChXFormType* rgfltMultiXGrpInverse = pcgi->m_rgfltMultiXInverse;

        // Collect channel group members together
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
        {
            Int iFexCh;
            I16 iChSrcTmp = pau->m_rgiChInTile [iCh];
            PerChannelInfo* ppcinfoTmp = pau->m_rgpcinfo + iChSrcTmp;

            if (rgfChannelMask[iChSrcTmp] == WMAB_TRUE) 
            {
                iFexCh = chexGetFexChannel(pau, iChSrcTmp);
                freqexSetGroup(pau, iChSrcTmp, WMAB_FALSE, WMAB_FALSE);

                rgpCoefGrpSrc[iCh0] = ppcinfoTmp->m_rgBPCoef;
                rgrgiBPBadCoef[iCh0] = ppcinfoTmp->m_rgiBPBadCoef;
                iCh0++;

                if (pau->m_bFreqex &&
                    ppcinfoTmp->m_rgBPCoef != NULL &&
                    ppcinfoTmp->m_bNoDecodeForCx == WMAB_FALSE &&
                    iFexCh == iChSrcTmp &&
                    ppcinfoTmp->m_iPower)
                {                        
                    if( !pbp->m_fOverlayMode )
                    {
                        for (iCoef = pbp->m_iExplicitStartPos; iCoef < ppcinfoTmp->m_cSubFrameSampleHalf; iCoef++)
                        {
                            if( ppcinfoTmp->m_rgBPCoef[iCoef] != 0 )
                            {
                                freqexSetNonzeroMask(pau, iCoef);
                                if (iCoef + 1 > ppcinfoTmp->m_cLastCodedIndex)
                                {
                                    ppcinfoTmp->m_cLastCodedIndex = (U16)(iCoef + 1);
                                }
                            }
                        }
                        if (ppcinfoTmp->m_cLastCodedIndex > pau->m_cLastCodedIndex)
                            pau->m_cLastCodedIndex = ppcinfoTmp->m_cLastCodedIndex;
                    }
                    else
                    {
                        if (pau->m_bBasePeakPresentTile)
                            ppcinfoTmp->m_cBadCoefSegs++;
                        for (iSeg = 0; iSeg < ppcinfoTmp->m_cBadCoefSegs; iSeg++)
                        {
                            iCoef = ppcinfoTmp->m_rgiBadCoefSegPos[iSeg * 2];
                            iEnd  = ppcinfoTmp->m_rgiBadCoefSegPos[iSeg * 2 + 1];
                            while( iCoef <= iEnd )
                            {
                                if( ppcinfoTmp->m_rgBPCoef[iCoef] != 0 )
                                {
                                    freqexSetNonzeroMask(pau, iCoef);
                                    if (iCoef + 1 > ppcinfoTmp->m_cLastCodedIndex)
                                    {
                                        ppcinfoTmp->m_cLastCodedIndex = (U16)(iCoef + 1);
                                    }
                                }
                                iCoef++;
                            }
                        }
                        if (ppcinfoTmp->m_cLastCodedIndex > pau->m_cLastCodedIndex)
                            pau->m_cLastCodedIndex = ppcinfoTmp->m_cLastCodedIndex;
                        if (pau->m_bBasePeakPresentTile)
                            ppcinfoTmp->m_cBadCoefSegs--;
                    }
                }
            }
        }
        assert(iCh0 == cChannelsInGrp);

        if (pbp->m_fOverlayMode)    
        {   
            //Overlay mode
            assert(WMAB_FALSE == fScalePriorToChannelXform);

            if (pbp->m_bWeightFactorOnCodedChannel)
            {
                // CTODO: I see diff of 14 in overlay mode between flt and int32. I believe the primiary 
                // reason is we do weight before quantization (unformately we have to do in that way
                // when m_bWeightFactorOnCodedChannel is on because weight is applied on coded channel.
                // After InvWeightBPCoefOverlay the absolute noise is 1/32 but the orignal signal is 
                // pretty small (< 16dB = 10^(16/20) = 6.3096). So the relative noise level is pretty
                // huge after InvWeightBPCoefOverlay. I believe the solution is to apply a large offset
                // in prvInvWeightBPCoefOverlay.
                TRACEWMA_EXIT(wmaResult, prvInvWeightBPCoefOverlay(pau, pcgi));
                // Do channel transform
                TRACEWMA_EXIT(wmaResult, prvBPInvChannelXFormOverlay(pau, rgpCoefGrpSrc, rgrgiBPBadCoef, pcgi));

                TRACEWMA_EXIT(wmaResult, prvBPInvQuantize(pau, pcgi));

                TRACEWMA_EXIT(wmaResult, prvInvWeightBPCoefOverlay16dBCompensation(pau, pcgi));
            }
            else
            {
                // Do channel transform
                TRACEWMA_EXIT(wmaResult, prvBPInvChannelXFormOverlay(pau, rgpCoefGrpSrc, rgrgiBPBadCoef, pcgi));

                TRACEWMA_EXIT(wmaResult, prvBPInvQuantize(pau, pcgi));

                TRACEWMA_EXIT(wmaResult, prvInvWeightBPCoefOverlay(pau, pcgi));
            }
        }           
        else 
        {
            //Exclusive mode                        
            if (fScalePriorToChannelXform)
            {
                assert(WMAB_FALSE == pbp->m_fOverlayMode);
                // Do inverse quantization
                TRACEWMA_EXIT(wmaResult, prvBPInvQuantize(pau, pcgi));
                // Do channel transform
                TRACEWMA_EXIT(wmaResult, prvBPInvChannelXForm(pau, rgpCoefGrpSrc, pcgi));
            }
            else
            {
                // !fScalePriorToChannelXform
                // Do channel transform
                TRACEWMA_EXIT(wmaResult, prvBPInvChannelXForm(pau, rgpCoefGrpSrc, pcgi));
                // Do inverse quantization
                TRACEWMA_EXIT(wmaResult, prvBPInvQuantize(pau, pcgi));
            }
        }
    }

exit:

    return wmaResult;
} // prvBasePlusReconCoefficients

WMARESULT prvInvWeightBPCoefOverlay16dBCompensation(CAudioObject *pau, CChannelGroupInfo* pcgi)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject*        pbp    = pau->m_pbp;

    Int iCh;
    
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
        Bool *rgfChannelMask = pcgi->m_rgfChannelMask;
        
        if (ppcinfo->m_bNoDecodeForCx)
            continue;

        if (rgfChannelMask[iChSrc] == WMAB_TRUE) 
        {
            PerChannelInfo*    ppcinfo    = pau->m_rgpcinfo + iChSrc;
            CoefType* rgBPCoef = ppcinfo->m_rgBPCoef;

            I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;         
            I32 *rgiBPCoefWeight = ppcinfo->m_rgiBPWeightFactor;         

            I16 iCoef;
            I16 iSeg;

            QuantFloat qfltQuantizer = qstCalcQuantStep( 
                        -MAX_WEIGHT_FACTOR, 
                        ppcinfo->m_cLeftShiftBitsQuant );
            CHECK_COEF_MUL_FFLT( qfltQuantizer );

            //DUMPDATA(ppcinfo->m_rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "X86PointC.dat", "ab+");

            for (iSeg = 0; iSeg < ppcinfo->m_cBadCoefSegs; iSeg++)
            {
                I16 iStart = rgiBadCoefSegPos[iSeg*2];
                I16 iEnd = rgiBadCoefSegPos[iSeg*2+1];
                // assert(iEnd - iStart + 1 >= pbp->m_iHoleSegWidthMin);

                for (iCoef = iStart; iCoef <= iEnd; iCoef++)
                {
                    rgBPCoef[iCoef] = MULT_QUANT_AND_SCALE(rgBPCoef [iCoef],qfltQuantizer);
                }
            }
            //DUMPDATA(ppcinfo->m_rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "X86PointD.dat", "ab+");

        }
    }

    return wmaResult;
}

// CTODO: need to call after InvQ?.
WMARESULT prvInvWeightBPCoefOverlay(CAudioObject *pau, CChannelGroupInfo* pcgi)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject*        pbp    = pau->m_pbp;

    Int iCh;

    // if m_bWeightFactorOnCodedChannel is true, 
    // we need to do 16dB (MAX_WEIGHT_FACTOR) pre offset here because we can not keep enough precision in integer build if
    // we directly use - ppcinfo->m_iMaxWeightFactor. And MAX_WEIGHT_FACTOR will be compensated after InvQ
    // in InvWeightCoefQ16dBCompensation function.
    U32 iWeightPreOffset = pbp->m_bWeightFactorOnCodedChannel ? MAX_WEIGHT_FACTOR : 0;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
        Bool *rgfChannelMask = pcgi->m_rgfChannelMask;
        
        if (ppcinfo->m_bNoDecodeForCx)
            continue;

        if (rgfChannelMask[iChSrc] == WMAB_TRUE) 
        {
            // This channel needs inverse quantization.
            PerChannelInfo*    ppcinfo    = pau->m_rgpcinfo + iChSrc;
            CoefType* rgBPCoef = ppcinfo->m_rgBPCoef;

            I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;         
            I32 *rgiBPCoefWeight = ppcinfo->m_rgiBPWeightFactor;         

            I16 iCoef;
            I16 iSeg;

            // note we use -m_iMaxWeightFactor in order to do divide.
            QuantFloat qfltQuantizer = qstCalcQuantStep( 
                    (iWeightPreOffset - ppcinfo->m_iMaxWeightFactor * pbp->m_iWeightQuantMultiplier), 
                    ppcinfo->m_cLeftShiftBitsQuant );
            CHECK_COEF_MUL_FFLT( qfltQuantizer );

            //DUMPDATA(ppcinfo->m_rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "X86PointA.dat", "ab+");

            // since we save Weight in rgiSFQ buffer, make sure buffer is large enough.
            assert(BPPLUS_MAXBADCOEFSEG <= MAX_SF_BANDS);
            for (iSeg = 0; iSeg < ppcinfo->m_cBadCoefSegs; iSeg++)
            {
                I16 iStart = rgiBadCoefSegPos[iSeg*2];
                I16 iEnd = rgiBadCoefSegPos[iSeg*2+1];
                // assert(iEnd - iStart + 1 >= pbp->m_iHoleSegWidthMin);

                if (WMAB_FALSE == pbp->m_bSingleWeightFactor)
                {
                    // note we use -rgiBPCoefWeight[iSeg] in order to do divide.
                    qfltQuantizer = qstCalcQuantStep( 
                            (iWeightPreOffset - rgiBPCoefWeight[iSeg] * pbp->m_iWeightQuantMultiplier), 
                            ppcinfo->m_cLeftShiftBitsQuant );
                    CHECK_COEF_MUL_FFLT( qfltQuantizer );
                }
                for (iCoef = iStart; iCoef <= iEnd; iCoef++)
                {
                    rgBPCoef[iCoef] = MULT_QUANT_AND_SCALE(rgBPCoef [iCoef],qfltQuantizer);
                }
            }

            //DUMPDATA(ppcinfo->m_rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "X86PointB.dat", "ab+");
        }
    }

    return wmaResult;
} // prvInvWeightBPCoefOverlay


WMARESULT prvBPAddBasePlustoBase(CAudioObject*      pau)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject*  pbp = pau->m_pbp;
    Int iCh, iCoef;

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
        I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;         
        
        //DUMPDATA(ppcinfo->m_rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "d:\\temp\\dumpencbase.dat", "ab+");
        // This channel needs merging with base
        if (pau->m_pbp->m_fOverlayMode)
        {
            Int iSeg;
#ifdef BUILD_WMAPROLBRV3
            if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2)
            {
                // get the base-peak segement copied
                if (*(ppcinfo->m_pcBasePeakCoefs) > 0)
                    ppcinfo->m_cBadCoefSegs++;
            }
#endif
            for (iSeg = 0; iSeg < ppcinfo->m_cBadCoefSegs; iSeg++)
            {
                I16 iStart = rgiBadCoefSegPos[iSeg*2];
                I16 iEnd = rgiBadCoefSegPos[iSeg*2+1];
                assert(iEnd > 0);
                assert(iEnd <= ppcinfo->m_cSubFrameSampleHalf);
                for (iCoef = iStart; iCoef <= iEnd; iCoef++)
                {
                    ppcinfo->m_rgCoefRecon[iCoef] = ppcinfo->m_rgBPCoef[iCoef];
                }
            }
#ifdef BUILD_WMAPROLBRV3
            if (pau->m_iVersion > 2 && pau->m_bPlusV2 && pau->m_fex.m_iVersion > 2)
            {
                // retrieve #Segs to avoid other places processing the base peak segment
                if (*(ppcinfo->m_pcBasePeakCoefs) > 0)
                    ppcinfo->m_cBadCoefSegs--;
            }
#endif
        }
        else
        {
            memcpy(ppcinfo->m_rgCoefRecon + pbp->m_iExplicitStartPos, ppcinfo->m_rgBPCoef + pbp->m_iExplicitStartPos, 
                    sizeof(CoefType) * (ppcinfo->m_cSubFrameSampleHalf - pbp->m_iExplicitStartPos));
        }
        //DUMPDATA(ppcinfo->m_rgBPCoef, ppcinfo->m_cSubFrameSampleHalf * sizeof(CoefType), "d:\\temp\\dumpencbp.dat", "ab+");
    }
    return wmaResult;
} // prvBPAddBasePlustoBase

WMARESULT prvBasePlusGetSFIndex(const CAudioObject *pau, I16 *piSFBandIndex, Int iWin)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject *pbp = pau->m_pbp;
    I16 *piSFBandIndexWin0 = pbp->m_rgrgiSFBandIndexOrig[pbp->m_iCurrSFBandTable];
    Int cValidSFBandWin0 = pbp->m_rgrgcValidSFBand[pbp->m_iCurrSFBandTable][0];
    Int cValidSFBand   = pbp->m_rgrgcValidSFBand[pbp->m_iCurrSFBandTable][iWin];

    Int iHalfScale = (1 << (iWin+1));  // 1<<(iWin-1)*4
    Int iCurrWin0 = 0;
    Int iCurr = 1;

    Int  cFrameSample  = pau->m_cFrameSample / (1 << iWin);

    if (0 == iWin)
    {
        memcpy(piSFBandIndex, piSFBandIndexWin0, sizeof(I16)*(cValidSFBandWin0+1));
    }
    else
    {
        for (iCurrWin0 = 1; iCurrWin0 <= cValidSFBandWin0; iCurrWin0++)
        {
            Int iIndexNew = (piSFBandIndexWin0[iCurrWin0] + iHalfScale) >> (iWin + 2);
            iIndexNew = iIndexNew << 2;
            assert(iIndexNew <= cFrameSample/2);
            if (iIndexNew > piSFBandIndex[iCurr - 1])
            {
                piSFBandIndex[iCurr] = (I16)iIndexNew;
                iCurr++;
            }
        }
        assert(iCurr - 1 == cValidSFBand);
    }    

    return wmaResult;
}

WMARESULT prvBasePlusResampleScaleFactor (const CAudioObject* pau, 
                         __in_ecount(cValidSFIn) Int* rgiSFQIn, Int cSubbandIn, Int cValidSFIn, 
                         __out_ecount(cValidSFOut) Int* rgiSFQOut, Int cSubbandOut, Int cValidSFOut)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iBandIn, iBandOut;

    Int iWinIn  = LOG2(pau->m_cFrameSampleHalf / cSubbandIn);
    Int iWinOut = LOG2(pau->m_cFrameSampleHalf / cSubbandOut);

    Int iFreqIn = 0, iFreqOut = 0;

    // update SF related stuffs.
    I32 cValidSFBandIn   = pbp->m_rgrgcValidSFBand[pbp->m_iCurrSFBandTable][iWinIn];
    I16 *rgiSFBandIndexIn = pbp->m_rgiSFBandIndexPrev;

    I32 cValidSFBandOut   = pbp->m_rgrgcValidSFBand[pbp->m_iCurrSFBandTable][iWinOut];
    I16 *rgiSFBandIndexOut = pbp->m_rgiSFBandIndexCurr;

    // CTODO: not always need to recompute the SFBandIndexPrev.
    prvBasePlusGetSFIndex(pau, pbp->m_rgiSFBandIndexPrev, iWinIn);

    // out should be current
    assert(cValidSFBandOut == pbp->m_cValidSFBand);
    assert(rgiSFBandIndexOut == pbp->m_rgiSFBandIndex);

    assert(pau->m_iVersion > 2);
    assert(cValidSFIn > 0);
    assert(cValidSFOut > 0);
    assert(cSubbandIn > 0);
    assert(cSubbandOut > 0);

    assert (cValidSFBandIn == cValidSFIn);
    assert (cValidSFBandIn == cValidSFIn);

    for (iBandOut = 0; iBandOut < cValidSFOut; iBandOut++)
    {
        iFreqOut = (rgiSFBandIndexOut[iBandOut] + rgiSFBandIndexOut[iBandOut+1] -1) * (1 << iWinOut)/ 2;
        // Locate the first iBark1 in subframe size iWin1 that includes iFreq0
        iBandIn = 0;
        while ((iFreqIn = rgiSFBandIndexIn[iBandIn+1] * (1 << iWinIn)) < iFreqOut) 
        {
            iBandIn++;
        }
        assert(iBandIn < cValidSFIn);
        assert(iBandIn < 256);
        rgiSFQOut[iBandOut] = rgiSFQIn[iBandIn];
    }
    return wmaResult;
} // prvBasePlusResampleScaleFactor


Void prvBasePlusAdaptToSubFrameConfig(CAudioObject* pau)
{
    CBasePlusObject *pbp = pau->m_pbp;
    Int cValidBarkBand = pau->m_cValidBarkBand;
    const Int *rgiBarkBandIndex = pau->m_rgiBarkIndex;
    Int cValidSFBand = 0;             //this is decided later.
    const I16 *rgiSFBandIndex = NULL; //this is decided later.
    I8 *rgiMaskQMarker = pau->m_pbp->m_rgiSFBandMarker;

    I32 iSFBand = 0;
    I32 iBarkBand = 0;

    I16 iIncr = (I16) LOG2 ((U32)(pau->m_cFrameSampleHalf / (pau->m_rgpcinfo + pau->m_rgiChInTile[0])->m_cSubFrameSampleHalf));

    assert(pau->m_fBasePlus);

    // update SF related stuffs.
    pbp->m_cValidSFBand   = pbp->m_rgrgcValidSFBand[pbp->m_iCurrSFBandTable][iIncr];
    pbp->m_rgiSFBandIndex = pbp->m_rgiSFBandIndexCurr;

    prvBasePlusGetSFIndex(pau, pbp->m_rgiSFBandIndexCurr, iIncr);

    cValidSFBand = pbp->m_cValidSFBand;   
    rgiSFBandIndex = pbp->m_rgiSFBandIndex;
    
    // compute MaskQMarker.
    iBarkBand = 0;
    for (iSFBand = 0; iSFBand < cValidSFBand; iSFBand++)
    {
        rgiMaskQMarker[iSFBand] = 0;
        while ( ( ( rgiSFBandIndex[iSFBand] + rgiSFBandIndex[iSFBand+1] )/2 >= rgiBarkBandIndex[iBarkBand+1] ) &&
                ( iBarkBand < (cValidBarkBand - 1) )
              )
        {
            iBarkBand++;
            // starting of a BarkBand.
            rgiMaskQMarker[iSFBand] = 1;
        }
    }
    rgiMaskQMarker[0] = 1;
} // prvBasePlusAdaptToSubFrameConfig

Void prvBasePlusFrameInit(CAudioObject* pau)
{
    if (pau->m_fBasePlus && pau->m_pbp)
    {
        // Force update of table index
        pau->m_pbp->m_bFirstTile = WMAB_TRUE;
    }
} // prvBasePlusFrameInit

Int prvBasePlusIdentifyBadlyCodedCoef(CAudioObject* pau)
{
    WMARESULT  wmaResult = WMA_OK;
    CBasePlusObject *pbp = pau->m_pbp;
    Int iCh, iChGrp, iChSrc, iChSrcTmp, iBand, iCoef, iCoefTmp;
    Int cChannelGrp = pbp->m_cBPChannelGroup;
    PerChannelInfo *ppcinfo = NULL;
    PerChannelInfo *ppcinfoTmp = NULL;

    const PerChannelInfo *ppcinfoFirst = pau->m_rgpcinfo + pau->m_rgiChInTile[0];
    Bool fJointlyCoded;
    Bool fLargeHole = WMAB_FALSE;

    Bool fTooManyHoles = WMAB_FALSE;

    I32 iTotalBadCoef = 0;
    I32 iTotalCoef = 0;

    const Int cSubband       = ppcinfoFirst->m_cSubFrameSampleHalf;
    const Int cHoleWidthInHZ = g_rgiHoleWidthCodeBook[pbp->m_iHoleWidthMinIdx];
    pbp->m_iHoleWidthMin = max((cHoleWidthInHZ * cSubband / (pau->m_iSamplingRate / 2)), 4);
    pbp->m_iHoleSegWidthMin = (pbp->m_iHoleSegWidthMinIdx == 0) ? pbp->m_iHoleWidthMin/2 : pbp->m_iHoleWidthMin;

    assert(pbp->m_iHoleSegWidthMin <= pbp->m_iHoleWidthMin);

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile [iCh];
        ppcinfo    = pau->m_rgpcinfo + iChSrc;
        memset(ppcinfo->m_rgiBPBadCoef, 0XFFFFFFFF, sizeof(I32) * ppcinfo->m_cSubFrameSampleHalf/32);
    }

    // Go through each channel group
    for (iChGrp = 0; iChGrp < cChannelGrp; iChGrp++)
    {
        CChannelGroupInfo* pcgi = pbp->m_rgBPChannelGrpInfo + iChGrp;
        Bool *rgfChannelMask = pcgi->m_rgfChannelMask;
        I32 *rgiBPBadCoef = NULL;

        for (iChSrc = 0; iChSrc < pau->m_cChannel; iChSrc++)
        {
            Int iCurrRun = 0;

            CoefType ctLastCodedCoef = 0;

            ppcinfo    = pau->m_rgpcinfo    + iChSrc;
            rgiBPBadCoef = ppcinfo->m_rgiBPBadCoef;

            fJointlyCoded = WMAB_TRUE;

            if (!rgfChannelMask[iChSrc])
                continue; // move to next channel

            if (ppcinfo->m_bNoDecodeForCx)
                continue;

            iTotalCoef += ppcinfo->m_cLastCodedIndex;

            freqexSetGroup(pau, iChSrc, WMAB_FALSE, WMAB_FALSE);
            memcpy(rgiBPBadCoef, pau->m_pucNonzeroMask, ppcinfo->m_cSubFrameSampleHalf/8);
            // take care of coefficients above cLastCodedIndex
            for (iCoef = pau->m_cLastCodedIndex; iCoef < ppcinfo->m_cSubFrameSampleHalf; iCoef++)
            {
                CLRBADCOEFFLAG(rgiBPBadCoef, iCoef);
            }

            // remove tiny bad spots
            ppcinfo->m_cBPBadCoef = 0;
            iCurrRun = 0;
            for (iCoef = 0; iCoef < min(pau->m_cLastCodedIndex + 1, ppcinfo->m_cSubFrameSampleHalf); iCoef++)
            {
                if (GETBADCOEFFLAG(rgiBPBadCoef, iCoef))
                    iCurrRun++;
                else 
                {
                    // Current run of ones ended
                    if (iCurrRun < pbp->m_iHoleWidthMin && iCurrRun > 0)
                    {
                        // Short run, so clear it off
                        for (iCoefTmp = iCoef - iCurrRun; iCoefTmp < iCoef; iCoefTmp++)
                        {
                            CLRBADCOEFFLAG(rgiBPBadCoef, iCoefTmp);
                        }
                    }
                    else
                    {
                        ppcinfo->m_cBPBadCoef += iCurrRun;
                    }
                    iCurrRun = 0;
                }
            }
            ppcinfo->m_cBPBadCoef += iCurrRun;
            iTotalBadCoef += ppcinfo->m_cBPBadCoef;
        }

        // if bCx is on, left and right channel are identical. So no need for cross channel
        // smearing.
        if (!pau->m_bCx)
        {    
            // CTODO: should do coef loop first to get better performance?
            // copy badlycodedflag across channels which are under same channel transform.
            for (iChSrc = 0; iChSrc < pau->m_cChannel; iChSrc++)
            {
                ppcinfo    = pau->m_rgpcinfo    + iChSrc;
                rgiBPBadCoef = ppcinfo->m_rgiBPBadCoef;

                fJointlyCoded = WMAB_TRUE;

                if (!rgfChannelMask[iChSrc])
                    continue; // move to next channel

                iBand = 0;
                // Is the current band mixed with other channels? If so, 
                if ((pcgi->m_fIsPredefinedXform && pcgi->m_predefinedXformType == MULTICH_IDENTITY) ||
                    (!pcgi->m_rgfXformOn[iBand])
                )
                {
                    fJointlyCoded = WMAB_FALSE;
                }

                // Check the goodness of this channel
                for (iCoef = 0; iCoef < pau->m_cLastCodedIndex; iCoef++)
                {
                    // Update bark band number
                    while (iCoef >= pau->m_rgiBarkIndex[iBand+1])
                    {
                        iBand++;
                        fJointlyCoded = WMAB_TRUE;
                        if ((pcgi->m_fIsPredefinedXform &&
                            pcgi->m_predefinedXformType == MULTICH_IDENTITY) ||
                            !pcgi->m_rgfXformOn[iBand])
                        {
                            fJointlyCoded = WMAB_FALSE;
                        }
                    }
                    assert(iBand < pau->m_cValidBarkBand);

                    if ((!GETBADCOEFFLAG(rgiBPBadCoef, iCoef)) && fJointlyCoded)
                    {
                        // If channels are joint coded, if coded coefficients in all 
                        // channels are zero they are all badcoef, otherwise, they are
                        // all good coefficients.
                        for (iChSrcTmp = 0; iChSrcTmp < pau->m_cChannel; iChSrcTmp++)
                        {
                            if (rgfChannelMask[iChSrcTmp] && iChSrcTmp != iChSrc)
                            {
                                ppcinfoTmp = pau->m_rgpcinfo + iChSrcTmp;
                                CLRBADCOEFFLAG (ppcinfoTmp->m_rgiBPBadCoef, iCoef);
                            }
                        }
                    }
                }
            }
        }
    }

    // generate badcoef segment index
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        I16 iSegStart = 0;
        I16 iSegEnd = -1;
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChSrc;
        I32 *rgiBPBadCoef = ppcinfo->m_rgiBPBadCoef;
        I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;
        Bool bInSegment = WMAB_FALSE;
        I16 iSegs = 0;
        I16 iCoef;

        if (ppcinfo->m_bNoDecodeForCx)
            continue;

        for (iCoef = 0; iCoef < pau->m_cLastCodedIndex; iCoef++)
        {
            if (GETBADCOEFFLAG(rgiBPBadCoef, iCoef))
            {
                if (!bInSegment)
                {
                    iSegStart = iCoef;
                }
                bInSegment = WMAB_TRUE;
                iSegEnd = iCoef;
            }
            else
            {
                if (bInSegment)
                {
                    assert(iSegEnd >= iSegStart);
                    // found a segment.
                    assert(iSegs < BPPLUS_MAXBADCOEFSEG);
                    if (iSegEnd - iSegStart + 1 >= pbp->m_iHoleSegWidthMin)
                    {
                        I32 cSubSegs = (iSegEnd - iSegStart + 1) / pbp->m_iHoleSegWidthMin;                             
                        I32 iSubSeg = 0;
                        for (iSubSeg = 0; iSubSeg < cSubSegs - 1; iSubSeg++)
                        {
                            rgiBadCoefSegPos[iSegs*2] = (I16)(iSegStart + iSubSeg * pbp->m_iHoleSegWidthMin);
                            rgiBadCoefSegPos[iSegs*2+1] = (I16)(iSegStart + (iSubSeg + 1) * pbp->m_iHoleSegWidthMin - 1);
                            iSegs++;
                            if (iSegs >= BPPLUS_MAXBADCOEFSEG)
                                goto earlyexit;
                        }
                        rgiBadCoefSegPos[iSegs*2] = (I16)(iSegStart + iSubSeg * pbp->m_iHoleSegWidthMin);
                        rgiBadCoefSegPos[iSegs*2+1] = iSegEnd;
                        //assert(rgiBadCoefSegPos[iSegs*2] < rgiBadCoefSegPos[iSegs*2+1]);
                        iSegs++;
                        if (iSegs >= BPPLUS_MAXBADCOEFSEG)
                            goto earlyexit;
                    }
                    else
                    {
                        // after cross channel smearing we could have < m_iHoeSegWidthMin holes.
                        rgiBadCoefSegPos[iSegs*2] = iSegStart;
                        rgiBadCoefSegPos[iSegs*2+1] = iSegEnd;
                        iSegs++;
                        if (iSegs >= BPPLUS_MAXBADCOEFSEG)
                            goto earlyexit;
                        //assert(rgiBadCoefSegPos[iSegs*2] < rgiBadCoefSegPos[iSegs*2+1]);
                    }

                    iSegStart = 0;
                    iSegEnd = -1;
                    bInSegment = WMAB_FALSE;
                }
            }
        }

        if (iSegEnd > iSegStart)
        {
            assert(iSegEnd == pau->m_cLastCodedIndex - 1);
            // found a segment.
            assert(iSegs < BPPLUS_MAXBADCOEFSEG);
            rgiBadCoefSegPos[iSegs*2] = iSegStart;
            rgiBadCoefSegPos[iSegs*2+1] = iSegEnd;
            //assert(rgiBadCoefSegPos[iSegs*2] < rgiBadCoefSegPos[iSegs*2+1]);
            iSegs++;
            if (iSegs >= BPPLUS_MAXBADCOEFSEG)
                goto earlyexit;          
            iSegStart = 0;
            iSegEnd = -1;
        }
        // for debug purpose only
        if (iSegs < BPPLUS_MAXBADCOEFSEG)
        {
            rgiBadCoefSegPos[iSegs*2] = -1;
            rgiBadCoefSegPos[iSegs*2+1] = -1;
        }
earlyexit:
        // if we found iseg more than 31 we don't code this
        // channel in overlay mode. 1)31 is large enough since
        // each hole is 400Hz, 2) problem should be fixed in
        // base layer. 3) we want to limit the memory usage.
        if (iSegs >= BPPLUS_MAXBADCOEFSEG)
        {
            fTooManyHoles = WMAB_TRUE;
            break;
        }
        else
        {
            ppcinfo->m_cBadCoefSegs = iSegs;
        }
    }

    if (fTooManyHoles)
    {
        // if we found too many holes in one channel, disable hole filling
        // for the whole tile.
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChSrc;

            I32 *rgiBPBadCoef = ppcinfo->m_rgiBPBadCoef;
            I16 *rgiBadCoefSegPos = ppcinfo->m_rgiBadCoefSegPos;

            if (ppcinfo->m_bNoDecodeForCx)
                continue;

            ppcinfo->m_cBadCoefSegs = 0;
            rgiBadCoefSegPos[0] = -1;
            rgiBadCoefSegPos[1] = -1;   
            // clear m_rgiBPBadCoef buffer since we still use BadCoef directly in several
            // places such as invxfrom
            memset(ppcinfo->m_rgiBPBadCoef, 0, sizeof(I32) * ppcinfo->m_cSubFrameSampleHalf/32);
        }
        iTotalBadCoef = 0;
    }

    if (pau->m_bCx)
    {
        PerChannelInfo *ppcinfoCh0 = pau->m_rgpcinfo;
        for (iCh = 1; iCh < pau->m_cChInTile; iCh++)
        {
            I16 iChSrc = pau->m_rgiChInTile [iCh];
            PerChannelInfo *ppcinfo = pau->m_rgpcinfo + iChSrc;

            ppcinfo->m_cBadCoefSegs = ppcinfoCh0->m_cBadCoefSegs;
            memcpy(ppcinfo->m_rgiBPBadCoef, ppcinfoCh0->m_rgiBPBadCoef, sizeof(I32) * ppcinfo->m_cSubFrameSampleHalf/32);
            memcpy(ppcinfo->m_rgiBadCoefSegPos, ppcinfoCh0->m_rgiBadCoefSegPos, sizeof(I16) * BPPLUS_MAXBADCOEFSEG * 2);
        }
    }

    return (iTotalCoef ? 100*iTotalBadCoef/iTotalCoef : 0);
} // prvBasePlusIdentifyBadlyCodedCoef


WMARESULT prvBasePlusUpdateLastCodedCoefIndex(CAudioObject* pau, 
                                      PerChannelInfo *ppcinfo)
{
    WMARESULT wmaResult = WMA_OK;
    I32 iCoef;
    ppcinfo->m_cLastCodedIndexBasePlus = 1;

    if (ppcinfo->m_bNoDecodeForCx)
        goto exit;

    for (iCoef = ppcinfo->m_cSubband - 1; iCoef >= 0; iCoef--)
    {
        if (ppcinfo->m_rgBPCoef[iCoef])
        {
            ppcinfo->m_cLastCodedIndexBasePlus = (U16)iCoef + 1;
            break;
        }
    }

exit:
    ppcinfo->m_cLastCodedIndex = max(ppcinfo->m_cLastCodedIndex, ppcinfo->m_cLastCodedIndexBasePlus);
    pau->m_cLastCodedIndex = max(ppcinfo->m_cLastCodedIndex, pau->m_cLastCodedIndex);

    return wmaResult;
}


WMARESULT prvBasePlusCopyChannelXFormFromBaseCommon (CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject* pbp = pau->m_pbp;
    Int iChGrp;
    Int cChannel = pau->m_cChannel;
    CChannelGroupInfo* pcgiSrc = NULL;
    CChannelGroupInfo* pcgiDst = NULL;

    pbp->m_cBPChannelGroup = pau->m_cChannelGroup;
    for (iChGrp = 0; iChGrp <  pbp->m_cBPChannelGroup; iChGrp++)
    {
        pcgiDst = pbp->m_rgBPChannelGrpInfo + iChGrp;
        pcgiSrc = pau->m_rgChannelGrpInfo + iChGrp;
    
        pcgiDst->m_cChannelsInGrp     = pcgiSrc->m_cChannelsInGrp;
        pcgiDst->m_fIsSuperGroupXform = pcgiSrc->m_fIsSuperGroupXform;
        pcgiDst->m_fIsPredefinedXform = pcgiSrc->m_fIsPredefinedXform;
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
            sizeof(ChXFormType) *
                    cChannel * cChannel);
    }
    return wmaResult;
} // prvBasePlusCopyChannelXFormFromBase

WMARESULT prvBasePlusSetNonLinearQuantizer (CBasePlusObject *pbp)
{
    WMARESULT wmaResult = WMA_OK;

    switch (pbp->m_NLQIdx)
    {   
    case 0:
        pbp->m_NLQDecTblSize = gNLQDecTblSize9;
        pbp->m_NLQDecTbl = gNLQDecTbl9;
        break;
    case 1:
        pbp->m_NLQDecTblSize = gNLQDecTblSize8;
        pbp->m_NLQDecTbl = gNLQDecTbl8;
        break;
    case 2:
        pbp->m_NLQDecTblSize = gNLQDecTblSize7;
        pbp->m_NLQDecTbl = gNLQDecTbl7;
        break;
    case 3:
        pbp->m_NLQDecTblSize = gNLQDecTblSize6;
        pbp->m_NLQDecTbl = gNLQDecTbl6;
        break;
    default:
        assert(WMAB_FALSE);
    }
    return wmaResult;
}


WMARESULT prvBasePlusCopyMaskBandIndexFromBaseOverlay(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject *pbp = pau->m_pbp;
    Int iBand = 0;
    assert(pbp->m_cValidSFBand == pau->m_cValidBarkBand);
    
    pbp->m_cValidSFBand = pau->m_cValidBarkBand;
    for (iBand = 0; iBand < pbp->m_cValidSFBand; iBand++)
    {        
        // assert(pbp->m_rgiSFBandIndexCurr[iBand] == (I16)pau->m_rgiBarkIndex[iBand]);
        pbp->m_rgiSFBandIndexCurr[iBand] = (I16)pau->m_rgiBarkIndex[iBand];
    }
    return wmaResult;
}

WMARESULT prvBasePlusDecideStartPositionExclusiveMode(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    CBasePlusObject *pbp = pau->m_pbp;

    if (1 == prvBasePlusIfBaseIsZero(pau))
        pbp->m_iExplicitStartPos = 0;
    else
        pbp->m_iExplicitStartPos = pau->m_cLastCodedIndex;

    return wmaResult;
}

Bool prvBasePlusIfBaseIsZero(CAudioObject *pau)
{
    Int iCh;
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;
        if (ppcinfo->m_iPower)
            return 0;
    }
    return 1;
}

#endif // BUILD_WMAPROLBRV2 && BUILD_WMAPRO
