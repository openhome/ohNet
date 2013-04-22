//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#include "msaudiotemplate.h"

#if defined (BUILD_WMAPROLBRV1)
#include "fex.h"
#endif

#if defined (_WMA_TARGET_XBOX2_)
#include "ppcintrinsics.h"
#endif 

#ifdef AUINV_RECON_CHANNEL

#ifdef AUINV_RECON_CHANNEL_ENC
#define auGetNextRun prvGetNextRunENC
#endif
#ifdef AUINV_RECON_CHANNEL_DEC
#define auGetNextRun (*pau->aupfnGetNextRun)
#endif

// Use of the next three defines is only in decoder, and are defined in msaudiodec.c
#if !defined (BIT_DISTRIBUTION_VARS)
#define BIT_DISTRIBUTION_VARS       
#endif
#if !defined (BIT_DISTRIBUTION_PRECHECK)
#define BIT_DISTRIBUTION_PRECHECK
#endif
#if !defined (BIT_DISTRIBUTION_POSTCHECK)
#define BIT_DISTRIBUTION_POSTCHECK   
#endif

#if defined (WMA_OPT_AURECONCOEFFSHIGH_XENON) || defined (WMA_OPT_AURECONCOEFFSHIGHPRO_XENON)
//Lookup table for int -> float conversions for common pau->m_iLevel values (avoid 40 cycle LHS)
static const float FLOAT_CACHE_XENON[64] =     {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                                      10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f,
                                      20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f,
                                      30.0f, 31.0f, 32.0f, 33.0f, 34.0f, 35.0f, 36.0f, 37.0f, 38.0f, 39.0f,
                                      40.0f, 41.0f, 42.0f, 43.0f, 44.0f, 45.0f, 46.0f, 47.0f, 48.0f, 49.0f,
                                      50.0f, 51.0f, 52.0f, 53.0f, 54.0f, 55.0f, 56.0f, 57.0f, 58.0f, 59.0f,
                                      60.0f, 61.0f, 62.0f, 63.0f};  
#endif //WMA_OPT_AURECONCOEFFSHIGH_XENON

#include "entropydec.h"

#if defined (BUILD_WMASTD)
///*****************************************************************************************
//
// auReconCoefficentsHighRate  - Integer or IntFloat Version
//
//*****************************************************************************************
//wchen: this function is not threadsafe!!
WMARESULT auReconCoefficentsHighRate (CAudioObject* pau, Void* pcaller,
                                      PerChannelInfo* ppcinfo)
{
    WMARESULT   wmaResult = WMA_OK;

    CoefType* rgiCoefRecon   = (CoefType*) ppcinfo->m_rgiCoefRecon;
    CoefType ctCoefRecon;
    Int iMaskResampleRatio, cValidBarkBandLatestUpdate;
    Int iBark = 0;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    INTEGER_ONLY( Int iShift=0; )
    Int iMaskResampleRatioPow;
    const Int *rgiBarkIndex;
    I16 iHighCutOff = 0;
    I16 iNextBarkIndex = -1; 
    Int iHighToBeZeroed;
    QuantFloat qfltQuantizer;   // either a FastFloat or a Float, as appropriate to the build.
    Bool fPrint;
    SubFrameConfigInfo* psubfrmconfigCurr;
    qfltQuantizer.iFraction = 0;
    qfltQuantizer.iFracBits = 0;
    fPrint = (pau->m_iFrameNumber == 17);
    psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
    BIT_DISTRIBUTION_VARS;

#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif

    assert (pau->m_iVersion <= 2);
    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);
    assert (0 != ppcinfo->m_cSubFrameSampleHalf);
    assert (pau->m_cFrameSampleHalf <= (1<<12));                                            
    DEBUG_BREAK_AT_FRAME_DECODE;

    //Prefetch the 2-cache line FLOAT_CACHE_XENON table
#if defined (WMA_OPT_AURECONCOEFFSHIGH_XENON)
    __dcbt(0, FLOAT_CACHE_XENON);
    __dcbt(128, FLOAT_CACHE_XENON);
#endif

    if (pau->m_iSubFrameSizeWithUpdate <= 0 || 
        ppcinfo->m_cSubFrameSampleHalf <= 0)
    {
        REPORT_BITSTREAM_CORRUPTION();
        wmaResult = WMA_E_BROKEN_FRAME;
        CHECKWMA_EXIT (wmaResult);
    }

    iMaskResampleRatio = (pau->m_iSubFrameSizeWithUpdate << 12) /                           
                          ppcinfo->m_cSubFrameSampleHalf;    
    iMaskResampleRatioPow = LOG2(iMaskResampleRatio);
    rgiBarkIndex       = pau->m_rgiBarkIndexOrig + (NUM_BARK_BAND + 1) *                    
                         LOG2 (pau->m_cFrameSampleHalf / pau->m_iSubFrameSizeWithUpdate);   
    cValidBarkBandLatestUpdate = pau->m_rgcValidBarkBand [LOG2 (pau->m_cFrameSampleHalf / pau->m_iSubFrameSizeWithUpdate)];

    //// DEBUG NOTES below are preceeded by four slashes and typically allow cut and paste so you can view scaled integers as floats
    //// They are on the line below where the calculation occurs - of course, with BUILD_INT_FLOAT, they are unnecessary

    // zero all coefs so we can just skip the many zero ones as we detect them below
    // note 70% of coefficents are zero in High Rate
    // wchen: moved to outside
    //memset (rgiCoefRecon , 0, sizeof (CoefType) * pau->m_cHighCutOff);//(iRun+pau->m_cLowCutOff));                     

    iBark = 0;
    //pau->m_iLevel = 0; // remove this line -- since GetNextRun guaranteed to return a value for this on success, on failure, don't care, and causes problems since level gets reset when it should not
    iHighCutOff = (I16) (ppcinfo->m_cSubbandActual-1);//values need to be offset by -1 too 
    iNextBarkIndex = -1; 

    //Scan for the first bark index = note iRecon is 0 and rgiBarkIndex[1] ==0 for 16000 Hz and 11025 Hz frames with 128 oir 64 samples

    while ((((*piRecon) * iMaskResampleRatio) >> 12) >= rgiBarkIndex [iBark+1]) 
        ++iBark;

    BIT_DISTRIBUTION_PRECHECK;

    TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    *piRecon += (I16) ( pau->m_cRunOfZeros+1 );

    while (*piRecon < iHighCutOff && iBark < cValidBarkBandLatestUpdate)
    {
        //Search for the next bark index
        while ((((*piRecon) * iMaskResampleRatio) >> 12) >= rgiBarkIndex [iBark+1]) 
            ++iBark;

        if ( iBark >= cValidBarkBandLatestUpdate )
        {
            assert( iBark < cValidBarkBandLatestUpdate );
            break;
        }

        // Get the quantStep * (10^(1/16))^(MaxMaskQ-MaskQ[iRecon])
        // as qfltQuantizer.fraction/(1<<(23-qfltQuantizer.exponent))
        // then scale coefficent to give it five FracBits
        if (*piRecon == iNextBarkIndex) 
        {                               
            //Reconstruct the coefficent before getting the next weighting factor if it lies at the end of a bark band        
            ctCoefRecon = MULT_QUANT(pau->m_iLevel,qfltQuantizer);

            //// Unsigned Float CoefRecon = ctCoefRecon/(1.0F*(1<<(qfltQuantizer.iFracBits+16-31)))
            INTEGER_ONLY( ctCoefRecon = SCALE_COEF_RECON(ctCoefRecon) );
            //// Unsigned Float CoefRecon = ctCoefRecon/32.0F
            VERIFY_DECODED_COEFFICENT(iBark-1);
            qfltQuantizer = prvWeightedQuantization(pau,ppcinfo,iBark);

            //// Float Quantizer = qfltQuantizer.iFraction/(1024.0F*(1<<(qfltQuantizer-10)))
            MAKE_MASK_FOR_SCALING(qfltQuantizer.iFracBits);
        } 
        else 
        {
            //Otherwize get the next weighting factor first
            assert( *piRecon > iNextBarkIndex );
            qfltQuantizer = prvWeightedQuantization(pau,ppcinfo,iBark);

            //// Float Quantizer = qfltQuantizer.iFraction/(1024.0F*(1<<(qfltQuantizer-10)))
            MAKE_MASK_FOR_SCALING(qfltQuantizer.iFracBits);
            ctCoefRecon = MULT_QUANT(pau->m_iLevel,qfltQuantizer);

            //// Unsigned Float CoefRecon = ctCoefRecon/(1.0F*(1<<(qfltQuantizer.iFracBits+16-31)))
            INTEGER_ONLY( ctCoefRecon = SCALE_COEF_RECON(ctCoefRecon) );
            //// Unsigned Float CoefRecon = ctCoefRecon/32.0F
            VERIFY_DECODED_COEFFICENT(iBark);
        }

        //Calculate the index of the end of this bark band
        if (iMaskResampleRatioPow > 12){
            iNextBarkIndex = (I16)((rgiBarkIndex [iBark + 1] + (1<<(iMaskResampleRatioPow-13))) >> (iMaskResampleRatioPow-12));
        } else {
            iNextBarkIndex = (I16) (rgiBarkIndex [iBark + 1] << (12-iMaskResampleRatioPow));
        }
        iNextBarkIndex--; //correct by -1
        if (iNextBarkIndex > iHighCutOff) 
            iNextBarkIndex = iHighCutOff;

#if !(defined (WMA_OPT_VLC_DEC_ARM) && WMA_OPT_VLC_DEC_ARM)
        do
        {
            rgiCoefRecon [*piRecon] = INTEGER_OR_INT_FLOAT( (ctCoefRecon^pau->m_iSign)-pau->m_iSign, 
                                    pau->m_iSign ? -ctCoefRecon : ctCoefRecon );

            BIT_DISTRIBUTION_POSTCHECK;

            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,rgiCoefRecon[*piRecon]);
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);

            BIT_DISTRIBUTION_PRECHECK;

            TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            *piRecon += (I16) ( pau->m_cRunOfZeros+1 );
            if (*piRecon >= iNextBarkIndex) 
                break;
            //Lookup (float)pau->m_iLevel if it's in FLOAT_CACHE_XENON table.  Note that the operation
            //we are trying to avoid occurs elsewhere in this function but those places are relatively
            //uncommon, such that branch overhead incurred by this optimization will hurt perf.  So we only 
            //use it here...
#if defined (WMA_OPT_AURECONCOEFFSHIGH_XENON)
            if(pau->m_iLevel < 64)
            {
                assert(pau->m_iLevel >= 0);  //Should not be negative
                ctCoefRecon = FLOAT_CACHE_XENON[pau->m_iLevel] * qfltQuantizer;
            }
            else
                ctCoefRecon = MULT_QUANT(pau->m_iLevel,qfltQuantizer);
#else       
            //Else just perform the conversion
            ctCoefRecon = MULT_QUANT(pau->m_iLevel,qfltQuantizer);
#endif  //WMA_OPT_AURECONCOEFFSHIGH_XENON

            INTEGER_ONLY( ctCoefRecon = SCALE_COEF_RECON(ctCoefRecon) );
            VERIFY_DECODED_COEFFICENT(iBark);
        } while (WMAB_TRUE);
#else   // WMA_OPT_VLC_DEC_ARM
        {
            CAudioObjectDecoder* paudec  = (CAudioObjectDecoder*) pcaller;
            CWMAInputBitStream*  pibstrm = &(paudec->m_ibstrm);
            U32 iResult;

            // Equivalent of prvGetNextRunDEC for paudec->m_rlsts == TBL_INDEX
            if (paudec->m_rlsts == TBL_INDEX)
            {
                TRACEWMA_EXIT (wmaResult, ibstrmGetBits (pibstrm, 1, &iResult));      
                prvSetDecTable (paudec,  ppcinfo, (I16) iResult);        
                paudec->m_rlsts = VLC;
            }

            assert(paudec->m_rlsts == VLC);
            TRACEWMA_EXIT (wmaResult, decodeVLC(pau, pcaller, ppcinfo, iNextBarkIndex, iShift, qfltQuantizer, ctCoefRecon, piRecon));			
		}
#endif  // WMA_OPT_VLC_DEC_ARM

        iBark++;
    }

    if (*piRecon == iHighCutOff) {
        if ( *piRecon >= iNextBarkIndex  )
        {   // skipped here via a cRunOfZeros past one or more iBark increments
        
            while ( ((iBark-1) < cValidBarkBandLatestUpdate) && (((*piRecon) * iMaskResampleRatio) >> 12) >= rgiBarkIndex [iBark] ) 
                ++iBark;

            if ( (iBark-1) <= cValidBarkBandLatestUpdate )
            {   
                qfltQuantizer = prvWeightedQuantization(pau,ppcinfo,iBark-1);

                //// Float Quantizer = qfltQuantizer.iFraction/(1024.0F*(1<<(qfltQuantizer-10)))
                MAKE_MASK_FOR_SCALING(qfltQuantizer.iFracBits);
            }
        }
        else
        {
            assert(WMAB_FALSE);
        }
        ctCoefRecon = MULT_QUANT(pau->m_iLevel,qfltQuantizer);

        //// Unsigned Float CoefRecon = ctCoefRecon/(1.0F*(1<<(qfltQuantizer.iFracBits+16-31)))
        INTEGER_ONLY( ctCoefRecon = SCALE_COEF_RECON(ctCoefRecon) );
        //// Unsigned Float CoefRecon = ctCoefRecon/32.0F
        VERIFY_DECODED_COEFFICENT(iBark-1);
        rgiCoefRecon [*piRecon] = INTEGER_OR_INT_FLOAT( (ctCoefRecon^pau->m_iSign)-pau->m_iSign, 
                                pau->m_iSign ? -ctCoefRecon : ctCoefRecon );

        BIT_DISTRIBUTION_POSTCHECK;

        //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
        MONITOR_RANGE(gMR_CoefRecon,rgiCoefRecon[*piRecon]);
        MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
    }
    if (*piRecon > ppcinfo->m_cSubband)
    {
        REPORT_BITSTREAM_CORRUPTION();
        wmaResult = WMA_E_BROKEN_FRAME;
    }
    CHECKWMA_EXIT (wmaResult);
    assert (iBark <=  cValidBarkBandLatestUpdate );

    // do low cutoff here so there is less branching in the above loop
    if ( pau->m_cLowCutOff > 0 )
    {
        memset (rgiCoefRecon, 0, sizeof (Int) * pau->m_cLowCutOff);

#       if defined(_DEBUG) && defined(WMA_MONITOR)
        {   int ii;
            for( ii = 0; ii < pau->m_cLowCutOff; ii++ )
                MONITOR_RANGE(gMR_CoefRecon,0);
        }
#       endif
    }

    //do high cutoff here 
    iHighToBeZeroed = sizeof(CoefType) * (ppcinfo->m_cSubbandAdjusted - pau->m_cHighCutOffAdjusted);
    memset (rgiCoefRecon + pau->m_cHighCutOffAdjusted, 0, iHighToBeZeroed);

#   if defined(_DEBUG) && defined(WMA_MONITOR)
    {   
    int ii;
    for( ii = 0; ii < iHighToBeZeroed; ii += sizeof(Int) )
        MONITOR_RANGE(gMR_CoefRecon,0);
    }
#   endif

#if defined(WMA_ENTROPY_TEST) && defined(AUINV_RECON_CHANNEL_DEC)
    if (!g_maskTest) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (*piRecon == iHighCutOff)
    {
        ppcinfo->m_cLastCodedIndex = (I16)iHighCutOff+1;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = *piRecon - (I16)(pau->m_cRunOfZeros+1) + 1;
    }
#if 0
    assert(freqexCheckLastCodedIndex(rgiCoefRecon,
                                     ppcinfo->m_cLastCodedIndex,
                                     ppcinfo->m_cSubbandAdjusted));
#endif

exit:

#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
}
#else // BUILD_WMASTD
// so !BUILD_WMASTD
WMARESULT auReconCoefficentsHighRate (CAudioObject* pau, Void* pcaller,
                                      PerChannelInfo* ppcinfo)
{
    return WMA_OK;
}
#endif // BUILD_WMASTD

#if defined (BUILD_WMAPRO)

INLINE
Int prvGetQuantIndex(const CAudioObject *pau,
                     const PerChannelInfo *ppcinfo,
                     const Int iBark)
{
    Bool bMaskUpdate =
        ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0];
    Int iIndex;

    if (bMaskUpdate) {
        iIndex = (ppcinfo->m_rgiMaskQ[iBark] - ppcinfo->m_iMaxMaskQ) *
            ppcinfo->m_iMaskQuantMultiplier;
    } else {
        iIndex = (ppcinfo->m_rgiMaskQResampled[iBark] - ppcinfo->m_iMaxMaskQ) *
            ppcinfo->m_iMaskQuantMultiplier;
    }

    return
        + pau->m_iQuantStepSize
        + ppcinfo->m_ucQuantStepModifierIndex
        + iIndex;
}

INLINE
Void cxSetCoefRecon(const PerChannelInfo *ppcinfo,
                    const CChannelGroupInfo *pcgi,
                    const Int iBark,
                    const Bool bSameWt,
                    QuantStepType wt0, QuantStepType wt1,
                    const CoefType ctCoefRecon,
                    CoefType *pRecon)
{
    if (ppcinfo->m_bNoDecodeForCx)
    {
        if (!bSameWt || WMAB_FALSE==pcgi->m_rgfXformOn[iBark])
        {
            CHECK_COEF_MUL_FFLT(wt1);
            *pRecon += MULT_QUANT_AND_SCALE(ctCoefRecon, wt1);
        }
    }
    else
    {
        if (!bSameWt || WMAB_FALSE==pcgi->m_rgfXformOn[iBark])
        {
            CHECK_COEF_MUL_FFLT(wt0);
            *pRecon = MULT_QUANT_AND_SCALE(ctCoefRecon, wt0);
        }
        else
        {
            *pRecon = ctCoefRecon;
        }
    }
}

STATIC_INLINE
Void prvGetLRWts(const CAudioObject *pau,
                 const CChannelGroupInfo *pcgi,
                 const Int iBark,
                 Bool *pbSameWt,
                 QuantStepType *pqWt0, QuantStepType *pqWt1)
{
    const PerChannelInfo *ppcinfo0 = pau->m_rgpcinfo + 0;
    const PerChannelInfo *ppcinfo1 = pau->m_rgpcinfo + 1;
    Int iIndex0 = prvGetQuantIndex(pau, ppcinfo0, iBark);
    Int iIndex1 = prvGetQuantIndex(pau, ppcinfo1, iBark);

    if (iIndex0 == iIndex1)
    {
        *pbSameWt = WMAB_TRUE;

        if (WMAB_FALSE==pcgi->m_rgfXformOn[iBark])
        {
            *pqWt0 = FFLT_INV_SQRT2;
            *pqWt1 = *pqWt0;
        }
    }
    else
    {
        QuantStepType qst;
        
        qst = qstCalcQuantStep(iIndex1 - iIndex0, 0);

        *pbSameWt = WMAB_FALSE;

        if (WMAB_FALSE==pcgi->m_rgfXformOn[iBark])
        {
            *pqWt0 = FFLT_INV_SQRT2;
            *pqWt1 = FASTFLOAT_MULT(qst, *pqWt0);
        }
        else
        {
            *pqWt0 = FASTFLOAT_ADD( qst, FFLT_ONE );
            *pqWt1 = FASTFLOAT_SUB( qst, FFLT_ONE );
#if defined(BUILD_INTEGER)
            pqWt0->iFracBits++; // div by 2
            pqWt1->iFracBits++;
#else
            *pqWt0 /= 2.0f;
            *pqWt1 /= 2.0f;
#endif
        }
    }
}

// Only (1) unravels the run-length coding, 
//      (2) Does not multiply with step size. 
//      (3) Does not multiply with resampled mask.
//      (4) Used only in V3 bitstreams.
//      (5) is based on copy and delete from auReconCoefficentsHighRate
WMARESULT auInvRlcCoefV3_Channel (CAudioObject* pau, Void* pcaller,
                                  PerChannelInfo* ppcinfo,
                                  Int iChSrc)
{
    WMARESULT   wmaResult = WMA_OK;
    
    CoefType* rgiCoefRecon   = (CoefType*) ppcinfo->m_rgiCoefRecon;
    CoefType ctCoefLevel, ctCoefRecon;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if (CX_DECODE_MONO==1)
    Int iBark = 0, iPrevBark = -1;
    Bool bSameWt=0;
    FastFloat wt0, wt1;
    CChannelGroupInfo* pcgi;
    Int iHighCutOff;
    Bool fPrint;
    SubFrameConfigInfo *psubfrmconfigCurr;
    wt0.iFraction = 0;
    wt0.iFracBits = 0;
    wt1.iFraction = 0;
    wt1.iFracBits = 0;
    pcgi = pau->m_rgChannelGrpInfo + 0;
#endif
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    iHighCutOff = 0;
    fPrint = WMAB_FALSE;
    psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
#ifdef WMAPROFILE
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
        wmaResult = WMA_E_BROKEN_FRAME;
    CHECKWMA_EXIT (wmaResult);

//    pau->m_iLevel = 0;
    iHighCutOff = pau->m_cHighCutOff-1;

    BIT_DISTRIBUTION_PRECHECK;
    TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    
    assert(pau->m_cRunOfZeros < SHRT_MAX);

    *piRecon += (I16) (pau->m_cRunOfZeros+1);
#if (CX_DECODE_MONO==1)
    while( iBark < pau->m_cValidBarkBand && 
        *piRecon >= pau->m_rgiBarkIndex[iBark+1] )
    {
        iBark++;
    }
    if (iBark != iPrevBark && pau->m_bCx && 2==pau->m_cChannel)
    {
        prvGetLRWts(pau, pcgi, iBark, &bSameWt, &wt0, &wt1);
        iPrevBark = iBark;
    }
#if defined(BUILD_WMAPROLBRV2)
    if (ppcinfo->m_bNoDecodeForCx)
    {
        Int iCh;
        if (2 == pau->m_cChannel)
            iCh = 0;
        else
            iCh = chexGetFexChannel(pau, iChSrc);
        
        if (iCh < 0)
        {
            REPORT_BITSTREAM_CORRUPTION_AND_EXIT(wmaResult);
        }
        
        rgiCoefRecon = (CoefType*)pau->m_rgpcinfo[iCh].m_rgiCoefRecon;
    }
#endif
#endif

#ifdef BUILD_WMAPROLBRV1
    if (pau->m_bNeedMaskProc)
        freqexSetGroup(pau, iChSrc, WMAB_FALSE, WMAB_FALSE);
#endif

    //INTEGER_ONLY( iShift = 0; )
    while (*piRecon < iHighCutOff) {
        ctCoefLevel = COEF_FROM_INT(pau->m_iLevel);
        
        do {
            ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                pau->m_iSign ? -ctCoefLevel : ctCoefLevel );
#if (CX_DECODE_MONO==1)
            if (pau->m_bCx && 2==pau->m_cChannel)
                cxSetCoefRecon(ppcinfo, pcgi, iBark, bSameWt, wt0, wt1,
                               ctCoefRecon, rgiCoefRecon+(*piRecon));
            else
#endif
                rgiCoefRecon[*piRecon] = ctCoefRecon;

#if defined(BUILD_WMAPROLBRV1)
            if (pau->m_bNeedMaskProc && ctCoefLevel!=0)
                freqexSetNonzeroMask(pau, *piRecon);
#endif
            
            BIT_DISTRIBUTION_POSTCHECK;
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(ctCoefRecon));
            MONITOR_COUNT_CONDITIONAL(ctCoefRecon==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
            BIT_DISTRIBUTION_PRECHECK;
            TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);
            *piRecon += (I16)(pau->m_cRunOfZeros+1);
#if (CX_DECODE_MONO==1)
            while( iBark < pau->m_cValidBarkBand && 
                *piRecon >= pau->m_rgiBarkIndex[iBark+1] )
            {
	            iBark++;
            }
            if (iBark != iPrevBark && pau->m_bCx && 2==pau->m_cChannel)
            {
                prvGetLRWts(pau, pcgi, iBark, &bSameWt, &wt0, &wt1);
                iPrevBark = iBark;
            }
#endif
            
            if (*piRecon >= iHighCutOff)
                break;
#if defined (WMA_OPT_AURECONCOEFFSHIGHPRO_XENON)
            if(pau->m_iLevel < 64)
            {
                assert(pau->m_iLevel >= 0);  //Should not be negative
                ctCoefLevel = FLOAT_CACHE_XENON[pau->m_iLevel];
            }
            else
                ctCoefLevel = COEF_FROM_INT(pau->m_iLevel);
#else       
            //Else just perform the conversion
            ctCoefLevel = COEF_FROM_INT(pau->m_iLevel);
#endif  //WMA_OPT_AURECONCOEFFSHIGH_XENON            

        } while (WMAB_TRUE);   
    }
    
    // Boundary case
    if (*piRecon == iHighCutOff)
    {
        ctCoefLevel = COEF_FROM_INT(pau->m_iLevel);
        ctCoefRecon = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
            pau->m_iSign ? -ctCoefLevel : ctCoefLevel );
#if (CX_DECODE_MONO==1)
        if (pau->m_bCx && 2==pau->m_cChannel)
            cxSetCoefRecon(ppcinfo, pcgi, iBark, bSameWt, wt0, wt1,
                           ctCoefRecon, rgiCoefRecon+(*piRecon));
        else
#endif
            rgiCoefRecon[*piRecon] = ctCoefRecon;

#if defined(BUILD_WMAPROLBRV1)
        if (pau->m_bNeedMaskProc && ctCoefLevel!=0)
            freqexSetNonzeroMask(pau, *piRecon);
#endif
        BIT_DISTRIBUTION_POSTCHECK;
        MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(ctCoefRecon));
        MONITOR_COUNT_CONDITIONAL(ctCoefRecon==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
    }

#if 0
    if (1==iChSrc && !pau->m_bEncoder)
    {
        for (iBark=0; iBark < pau->m_cValidBarkBand; iBark++)
        {
            printf("%d %d %d %d SUM %f\n",
                  pau->m_iFrameStart, pau->m_iCurrTile, iBark,
                  pcgi->m_rgfXformOn[iBark],
                  pau->m_rgpcinfo[0].m_rgCoefRecon[pau->m_rgiBarkIndex[iBark]]*
                  qstCalcQuantStep(prvGetQuantIndex(pau,
                                                    pau->m_rgpcinfo,
                                                    iBark), 0));
        }
    }
#endif

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

    // Based on the reason for exiting the above loops, we have different answers.
    if (*piRecon == iHighCutOff)
    {
        ppcinfo->m_cLastCodedIndex = (I16)iHighCutOff+1;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = *piRecon - (I16)(pau->m_cRunOfZeros+1) + 1;
    }

#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // auInvRlcCoefV3_Channel

// Only (1) unravels the run-length coding, 
//      (2) Does not multiply with step size. 
//      (3) Does not multiply with resampled mask.
//      (4) Used only in V3 bitstreams.
//      (5) is based on copy and delete from auReconCoefficentsHighRate
//      (6) assumes anything beyond half freq point are not needed
WMARESULT auInvRlcCoefV3_ChannelHT (CAudioObject* pau, Void* pcaller,
                                    PerChannelInfo* ppcinfo,
                                    Int iChSrc)
{
    WMARESULT   wmaResult = WMA_OK;
    
    CoefType* rgiCoefRecon   = (CoefType*) ppcinfo->m_rgiCoefRecon;
    CoefType ctCoefLevel;
    I16* piRecon = &pau->m_iCurrReconCoef;
#if defined(PLATFORM_OPTIMIZATION_MINIMIZE_BRANCHING)
    Int iMask1,iMask2;
#endif
    //INTEGER_ONLY( Int iShift; )
    Int iHighCutOff = 0;
    Int iMidCutOff  = 0;
    Bool fPrint = WMAB_FALSE;
    SubFrameConfigInfo *psubfrmconfigCurr = &(ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM]);
#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,DECODE_COEFFICENTS_HIGH_RATE_PROFILE);
#endif
    
    assert (!pau->m_fNoiseSub &&  pau->m_iWeightingMode == BARK_MODE);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] != 0);
    assert (psubfrmconfigCurr->m_rgiSubFrameSize [ppcinfo->m_iCurrSubFrame] == ppcinfo->m_cSubFrameSampleHalf);

    // V3 LLM. Chao. Added. LLM mode should not enter this function.
    assert (pau->m_bUnifiedLLM == WMAB_FALSE);
    assert (pau->m_bPureLosslessMode == WMAB_FALSE);

    DEBUG_BREAK_AT_FRAME_DECODE;
    
    if (ppcinfo->m_cSubFrameSampleHalf <= 0)
        wmaResult = WMA_E_BROKEN_FRAME;
    CHECKWMA_EXIT (wmaResult);

//    pau->m_iLevel = 0;
    iHighCutOff = pau->m_cHighCutOff-1;
    iMidCutOff  = ((ppcinfo->m_cSubFrameSampleHalf) >> pau->m_iAdjustSizeShiftFactor);
    iMidCutOff = min(iMidCutOff, iHighCutOff); // in case high cutoff is less
    
    TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
    DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
    
    assert(pau->m_cRunOfZeros < SHRT_MAX);

    *piRecon += (I16) (pau->m_cRunOfZeros+1);

#ifdef BUILD_WMAPROLBRV1
    if (pau->m_bNeedMaskProc)
        freqexSetGroup(pau, iChSrc, WMAB_FALSE, WMAB_FALSE);
#endif

    //INTEGER_ONLY( iShift = 0; )
    // Decode and copy results upto & excluding MidCutOff.
    while (*piRecon < iMidCutOff) {
        ctCoefLevel = COEF_FROM_INT(pau->m_iLevel);
        
        do {
            rgiCoefRecon [*piRecon] = INTEGER_OR_INT_FLOAT( (ctCoefLevel^pau->m_iSign)-pau->m_iSign, 
                pau->m_iSign ? -ctCoefLevel : ctCoefLevel );
#if defined(BUILD_WMAPROLBRV1)
            if (pau->m_bNeedMaskProc && ctCoefLevel!=0)
                freqexSetNonzeroMask(pau, *piRecon);
#endif
            
            //// Float CoefRecon = rgiCoefRecon [iRecon]/32.0F
            MONITOR_RANGE(gMR_CoefRecon,FLOAT_FROM_COEF(rgiCoefRecon[*piRecon]));
            MONITOR_COUNT_CONDITIONAL(rgiCoefRecon[*piRecon]==0,gMC_zeroCoefRecon,pau->m_cRunOfZeros);
            TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);
            *piRecon += (I16)(pau->m_cRunOfZeros+1);
            
            if (*piRecon >= iMidCutOff)
                break;
            
            ctCoefLevel = COEF_FROM_INT(pau->m_iLevel);
        } while (WMAB_TRUE);   
    }
    assert(*piRecon >= iMidCutOff);
    
    // Decode but not capture beyond iMidCutOff
    while (*piRecon < iHighCutOff) {
        
        do {
            TRACEWMA_EXIT (wmaResult, auGetNextRun (pcaller, ppcinfo));
            DBG_RUNLEVEL(g_cBitGet-21,pau->m_cRunOfZeros,pau->m_iLevel,pau->m_iSign,fPrint);
            assert(pau->m_cRunOfZeros < SHRT_MAX);
            *piRecon += (I16)(pau->m_cRunOfZeros+1);
            
            if (*piRecon >= iHighCutOff)
                break;
        } while (WMAB_TRUE);   
    }
            
#if defined(WMA_ENTROPY_TEST) && defined(AUINV_RECON_CHANNEL_DEC)
    if (!g_maskTest) pauEndEntropyTest(pau, ppcinfo, g_maskTest);
#endif

    if (*piRecon > pau->m_cHighCutOff)
    {
        REPORT_BITSTREAM_CORRUPTION();
        wmaResult = WMA_E_BROKEN_FRAME;
    }
    CHECKWMA_EXIT (wmaResult);

    //assert (*piRecon <= ppcinfo->m_cSubband); 
    
   
exit:

    // Based on the reason for exiting the above loops, we have different answers.
    if (*piRecon == iHighCutOff)
    {
        ppcinfo->m_cLastCodedIndex = (I16)iHighCutOff+1;
    }
    else
    {
        ppcinfo->m_cLastCodedIndex = *piRecon - (I16)(pau->m_cRunOfZeros+1) + 1;
    }

#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return wmaResult;
} // auInvRlcCoefV3_ChannelHT
#else // BUILD_WMAPRO
// so !BUILD_WMAPRO
WMARESULT auInvRlcCoefV3_Channel (CAudioObject* pau, Void* pcaller,
                                  PerChannelInfo* ppcinfo,
                                  Int iChSrc )
{
    return WMA_OK;
}
WMARESULT auInvRlcCoefV3_ChannelHT (CAudioObject* pau, Void* pcaller,
                                    PerChannelInfo* ppcinfo,
                                    Int iChSrc )
{
    return WMA_OK;
}
#endif // BUILD_WMAPRO

#endif // AUINV_RECON_CHANNEL

