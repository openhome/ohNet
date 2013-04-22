//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Std & WMA Pro; These are not needed by WMA Lossless.
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
#include "macros.h"
#include "float.h"
#include "wavfileexio.h"
#include "drccommon.h"

#ifdef OVERLAPADD_LOOKUPTBL
#include "overlapadd_tabs.h"
#endif

#if defined (BUILD_WMASTD) || defined (BUILD_WMAPRO)
//*****************************************************************************************
//
// prvSetBarkIndex
// part of prvAllocate which is part of auInit
//
//*****************************************************************************************
Void prvSetBarkIndex (CAudioObject* pau)
{
    Int i, iWin;
    Float fltSamplingPeriod;

    Int *piBarkIndex;
    Int cFrameSample;
    Bool bCombined;
    const I32 cMaxBarkBand = (pau->m_iVersion <= 2) ? 25 : NUM_BARK_BAND;
    const U32* rgiBarkFreq = (pau->m_iVersion <= 2) ? g_rgiBarkFreqV2 : g_rgiBarkFreqV3;

    //calculate index of each bark freq
    fltSamplingPeriod = 1.0F / pau->m_iSamplingRate;
    // wchen: we need to think what to do with the cut off frequencies: not include at all or include zeros.
    //for long window
    piBarkIndex = pau->m_rgiBarkIndexOrig;

    // for the v1 compatibility
    if(pau->m_iVersion == 1)
    {
        assert(pau->m_cPossibleWinSize == 1);

        // set up the bark index
        piBarkIndex[0] = 0;
        for (i = 0; i < cMaxBarkBand; i++)
        {
            piBarkIndex [i + 1] = (Int) (rgiBarkFreq [i] * pau->m_cFrameSample * 
                                         fltSamplingPeriod + 0.5f); //open end
            assert (piBarkIndex [i + 1]);
            if (piBarkIndex [i + 1] > pau->m_cFrameSample / 2)
            {
                piBarkIndex [i + 1] = pau->m_cFrameSample / 2;
                pau->m_rgcValidBarkBand [0] = i + 1;
                break;
            }
        }
    }
    else
    {
        for (iWin = 0; iWin < pau->m_cPossibleWinSize; iWin++)    {
            piBarkIndex  [0] = 0;
            cFrameSample = pau->m_cFrameSample / (1 << iWin);
            bCombined = WMAB_FALSE;
            if (pau->m_iVersion <= 2) 
            {
                if (pau->m_iSamplingRate >= 44100) {
                    if(cFrameSample == 1024) { // winsize = 512
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand[iWin] = 17;
                        piBarkIndex[1]  = 5;    piBarkIndex[2]  = 12;
                        piBarkIndex[3]  = 18;   piBarkIndex[4]  = 25;
                        piBarkIndex[5]  = 34;   piBarkIndex[6]  = 46;
                        piBarkIndex[7]  = 54;   piBarkIndex[8]  = 63;
                        piBarkIndex[9]  = 86;   piBarkIndex[10] = 102;
                        piBarkIndex[11] = 123;  piBarkIndex[12] = 149;
                        piBarkIndex[13] = 179;  piBarkIndex[14] = 221;
                        piBarkIndex[15] = 279;  piBarkIndex[16] = 360;
                        piBarkIndex[17] = 512;
                    }
                    else if(cFrameSample == 512) { // winsize = 256
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand[iWin] = 15;
                        piBarkIndex[1]  = 5;    piBarkIndex[2]  = 11;
                        piBarkIndex[3]  = 17;   piBarkIndex[4]  = 23;
                        piBarkIndex[5]  = 31;   piBarkIndex[6]  = 37;
                        piBarkIndex[7]  = 43;   piBarkIndex[8]  = 51;
                        piBarkIndex[9]  = 62;   piBarkIndex[10] = 74;
                        piBarkIndex[11] = 89;   piBarkIndex[12] = 110;
                        piBarkIndex[13] = 139;  piBarkIndex[14] = 180;
                        piBarkIndex[15] = 256;
                    }
                    else if(cFrameSample == 256)  { // winsize = 128
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand [iWin] = 12;
                        piBarkIndex[1]  = 4;   piBarkIndex[2]  = 9;
                        piBarkIndex[3]  = 12;  piBarkIndex[4]  = 16;
                        piBarkIndex[5]  = 21;  piBarkIndex[6]  = 26;
                        piBarkIndex[7]  = 37;  piBarkIndex[8]  = 45;
                        piBarkIndex[9]  = 55;  piBarkIndex[10] = 70;
                        piBarkIndex[11] = 90;  piBarkIndex[12] = 128;
                    }
                }
                else if(pau->m_iSamplingRate >= 32000) {
                    if(cFrameSample == 1024) { // winsize = 512
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand[iWin] = 16;
                        piBarkIndex[1]  = 6;   piBarkIndex[2]  = 13;
                        piBarkIndex[3]  = 20;  piBarkIndex[4]  = 29;
                        piBarkIndex[5]  = 41;  piBarkIndex[6]  = 55;
                        piBarkIndex[7]  = 74;  piBarkIndex[8]  = 101;
                        piBarkIndex[9]  = 141; piBarkIndex[10] = 170;
                        piBarkIndex[11] = 205; piBarkIndex[12] = 246;
                        piBarkIndex[13] = 304; piBarkIndex[14] = 384;
                        piBarkIndex[15] = 496; piBarkIndex[16] = 512;
                    }
                    else if(cFrameSample == 512) { // winsize = 256
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand[iWin] = 15;
                        piBarkIndex[1]  = 5;   piBarkIndex[2]  = 10;
                        piBarkIndex[3]  = 15;  piBarkIndex[4]  = 20;
                        piBarkIndex[5]  = 28;  piBarkIndex[6]  = 37;
                        piBarkIndex[7]  = 50;  piBarkIndex[8]  = 70;
                        piBarkIndex[9]  = 85;  piBarkIndex[10] = 102;
                        piBarkIndex[11] = 123; piBarkIndex[12] = 152;
                        piBarkIndex[13] = 192; piBarkIndex[14] = 248;
                        piBarkIndex[15] = 256;
                    }
                    else if(cFrameSample == 256)  { // winsize = 128
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand [iWin] = 11;
                        piBarkIndex[1]  = 4;   piBarkIndex[2]  = 9;
                        piBarkIndex[3]  = 14;  piBarkIndex[4]  = 19;
                        piBarkIndex[5]  = 25;  piBarkIndex[6]  = 35;
                        piBarkIndex[7]  = 51;  piBarkIndex[8]  = 76;
                        piBarkIndex[9]  = 96;  piBarkIndex[10] = 124;
                        piBarkIndex[11] = 128;
                    }
                }
                else if(pau->m_iSamplingRate >= 22050) {
                    if(cFrameSample == 512) { // winsize = 256
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand [iWin] = 14;
                        piBarkIndex[1]  = 5;   piBarkIndex[2]  = 12;
                        piBarkIndex[3]  = 18;  piBarkIndex[4]  = 25;
                        piBarkIndex[5]  = 34;  piBarkIndex[6]  = 46;
                        piBarkIndex[7]  = 63;  piBarkIndex[8]  = 86;
                        piBarkIndex[9]  = 102; piBarkIndex[10] = 123;
                        piBarkIndex[11] = 149; piBarkIndex[12] = 179;
                        piBarkIndex[13] = 221; piBarkIndex[14] = 256;
                    }
                    else if(cFrameSample == 256) { // winsize = 128
                        bCombined = WMAB_TRUE;
                        pau->m_rgcValidBarkBand [iWin] = 10;
                        piBarkIndex[1]  = 5;   piBarkIndex[2]  = 11;
                        piBarkIndex[3]  = 17;  piBarkIndex[4]  = 23;
                        piBarkIndex[5]  = 31;  piBarkIndex[6]  = 43;
                        piBarkIndex[7]  = 62;  piBarkIndex[8]  = 89;
                        piBarkIndex[9]  = 110; piBarkIndex[10] = 128;
                    }
                }
            }

            if(!bCombined)
            {
                Float fltTemp = cFrameSample*fltSamplingPeriod;
                Int iIndex;
                Int iFreqCurr = 0;
                Int iCurr = 1;
                while(WMAB_TRUE)
                {
                    if (pau->m_iVersion <= 2)
                        iIndex = ((Int) ((rgiBarkFreq [iFreqCurr++]*fltTemp + 2.0f)/4.0f))*4; // open end
                    else
                    {
                        // Integerized version
                        iIndex  = ((rgiBarkFreq [iFreqCurr++]*cFrameSample)/pau->m_iSamplingRate + 2);
                        iIndex -= iIndex % 4; // Make a multiple of 4 through truncation
                    }

                    if(iIndex > piBarkIndex[iCurr - 1])
                        piBarkIndex[iCurr++] = iIndex;

                    // We change > to >= because > has a problem in (v2 fz=2964).
                    // Basically, in the second window size loop we has last BarkIndex as 516, but
                    // in the third window size loop, 516 is mapped to 256 which is exactlly equal
                    // to cFrameSample/2. Then, we get one more BarkBand. But later, we alway assume
                    // the first window size has most BarkBands and we assign pau->m_rgcValidBarkBand [0]
                    // to pau->m_cValidBarkBand. As a result, we will encounter buffer overrun.
                    // This fix may change bitsteam. I verified that it does not change the behavior 
                    // of the codec for standard settings like (44100, 48000, etc). To be more safer,
                    // I put an assert inside the block. It should not be hit because at this time
                    // we only encode and decode wma at standard sampling rates.
                    if(iFreqCurr >= cMaxBarkBand ||
                       piBarkIndex[iCurr - 1] >= cFrameSample/2)
                    {
                        // This assert is put here for safety. It is used to verify the above fix does 
                        // not change the behavior of codec for standard sampling rate. Once in future
                        // we permit continuous sampling rate (or in TEST_CORRUPT_BITSTREAM) we should 
                        // remove it. But we should notice the previous player may not be able to 
                        // decode wma files with some continuous sampling rate correctly if
                        // piBarkIndex[iCurr - 1] == cFrameSample here.
                    #if !defined TEST_CORRUPT_BITSTREAM
                        assert(piBarkIndex[iCurr - 1] != cFrameSample/2 || pau->m_iSamplingRate == 24000);
                    #endif
                        piBarkIndex[iCurr - 1] = cFrameSample/2;
                        pau->m_rgcValidBarkBand[iWin] = iCurr - 1;
                        break;
                    }
                }
            }
            else
            {
                for (i = 0; i < pau->m_rgcValidBarkBand [iWin]; i++) {
                    piBarkIndex [i + 1] = ((piBarkIndex [i + 1] + 2) / 4) * 4;  //rounding
                    assert (piBarkIndex [i + 1] > piBarkIndex [i]);
                }
            }

            piBarkIndex +=  NUM_BARK_BAND + 1;
        }
    }
    //default
    pau->m_rgiBarkIndex = pau->m_rgiBarkIndexOrig;
    pau->m_cValidBarkBand = pau->m_rgcValidBarkBand [0];

    // Check pau->m_rgcValidBarkBand [0] is the biggest.
    for (iWin = 0; iWin < pau->m_cPossibleWinSize; iWin++) {
        assert(pau->m_rgcValidBarkBand[iWin] <= pau->m_cValidBarkBand);
    }

#ifdef DEBUG
    // checking for multiples of 4!!!
    if(pau->m_iVersion != 1)
    {
        Int iBand;
        for(iWin = 0; iWin < pau->m_cPossibleWinSize; iWin++)
        {
            for(iBand = 0; iBand <= pau->m_rgcValidBarkBand[iWin]; iBand++)
            {
                i = pau->m_rgiBarkIndexOrig[iWin*(NUM_BARK_BAND + 1) + iBand];
                assert(i%4 == 0);
            }
        }
    }
#endif // DEBUG

} // prvSetBarkIndex

/****************************************************************************
**
** Function:        auSubframeRecon
**
** Description:     subframe reconstruction from coef to PCM samples
**
** Return:          None
**
*****************************************************************************/
#if !(defined (PLATFORM_SPECIFIC_SUBFRAMERECON) && (defined (WMA_TARGET_MIPS) || defined(WMA_TARGET_SH4)))
#if !defined(WMA_OPT_SUBFRAMERECON_XENON)
WMARESULT auSubframeRecon ( CAudioObject* pau )
{
    WMARESULT hr = WMA_OK;
    I16 iCh, iChSrc;
    I16 iSizePrev, iSizeCurr, iSizePrev2;
    PerChannelInfo *ppcinfo, *ppcinfo2;
    Int     i, iOverlapSize;
    I16 iPrevCoefRecurQ3, iPrevCoefRecurQ4, iCurrCoefRecurQ1, iCurrCoefRecurQ2;
    TR2_TYPE bp2Sin;
    TR2_TYPE bp2Cos;
    TR2_TYPE bp2Sin1;
    TR2_TYPE bp2Cos1;
    TR2_TYPE bp2Step;
    CoefType *piPrevCoef, *piCurrCoef;
    CoefType cfPrevData, cfCurrData;
    

#ifdef WMAPROFILE
    FunctionProfile fp;
    FunctionProfileStart(&fp,RECON_MONO_PROFILE);
#endif

#if defined(BUILD_WMAPROLBRV2)
    if (WMAB_TRUE == pau->m_bReconProc)
    {
        TRACEWMA_EXIT(hr, chexSubframeRecon(pau));
        goto exit;
    }
#endif // BUILD_WMAPROLBRV1

#ifdef BUILD_INTEGER
    if (pau->m_iVersion >= 3) {
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
            iChSrc = pau->m_rgiChInTile [iCh];
            ppcinfo = pau->m_rgpcinfo + iChSrc;
    
            iSizePrev = ppcinfo->m_iSizePrev;
            iSizeCurr = ppcinfo->m_iSizeCurr;

            // In Unified WMA, we must call prvCalcQ1Q2/Q3Q4 to get the window shape. 
            // iOverlapSize = min(iSizePrev, iSizeCurr) / 2;
            prvCalcQ1Q2(pau, WMAB_TRUE, iSizePrev, iSizeCurr, &iCurrCoefRecurQ1, &iCurrCoefRecurQ2);
            iOverlapSize = (iCurrCoefRecurQ2 - iCurrCoefRecurQ1) / 2;

        
            piCurrCoef = ppcinfo->m_rgiCoefRecon;
            for (i = -iSizePrev / 2; i < - iOverlapSize; i++) {
                piCurrCoef[i] = INT_FROM_COEF(piCurrCoef[i]);
            }
        }
    }
#endif // BUILD_INTEGER

    i = WMAB_FALSE;
    if( pau->m_cChInTile == 2 ){
        
        // ======== Setup the init condition for PCM reconstruction ========
        ppcinfo = &pau->m_rgpcinfo[pau->m_rgiChInTile[0]];
        ppcinfo2 = &pau->m_rgpcinfo[pau->m_rgiChInTile[1]];

        iSizePrev = ppcinfo->m_iSizePrev;
        iSizePrev2 = ppcinfo2->m_iSizePrev;

        if( (pau->m_iVersion <= 2) || (iSizePrev == iSizePrev2) )
            i = WMAB_TRUE;
    }
            
    // ********** Reconstruction for each channel in the tile **********
    if( i == WMAB_TRUE ){

        CoefType *piPrevCoef2, *piCurrCoef2;

        // get previous subframe size
        iSizeCurr = ppcinfo->m_iSizeCurr;

#ifdef OVERLAPADD_LOOKUPTBL
        if (ppcinfo->m_overlapAddSize <= MAX_OVADD_TLU_SIZE) {
            bp2Sin  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[0]);
            bp2Cos  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[1]);
        }
        else
#endif
        {
            // Reset trig recursion
            bp2Sin  = TR2_FROM_BP2(ppcinfo->m_fiSinRampUpStart);
            bp2Cos  = TR2_FROM_BP2(ppcinfo->m_fiCosRampUpStart);
            bp2Sin1 = TR2_FROM_BP2(ppcinfo->m_fiSinRampUpPrior);
            bp2Cos1 = TR2_FROM_BP2(ppcinfo->m_fiCosRampUpPrior);
            bp2Step = TR2_FROM_BP2(ppcinfo->m_fiSinRampUpStep);
        }

        prvCalcQ3Q4(pau, WMAB_FALSE, iSizePrev, iSizeCurr, iSizePrev, &iPrevCoefRecurQ3, &iPrevCoefRecurQ4);
        prvCalcQ1Q2(pau, WMAB_TRUE, iSizePrev, iSizeCurr, &iCurrCoefRecurQ1, &iCurrCoefRecurQ2);

        //==================================================================
        // ==== In-place Reconstruction between prev and curr subframes ====
        //==================================================================

        // ---- Now move unused coef to the end of current subframe coef buffer ----
        piCurrCoef = (CoefType *)ppcinfo->m_rgiCoefRecon;   // now reverse the coef buffer
        piCurrCoef2 = (CoefType *)ppcinfo2->m_rgiCoefRecon;   // now reverse the coef buffer
#if !(defined(WMA_OPT_SUBFRAMERECON_ARM) && WMA_OPT_SUBFRAMERECON_ARM)
        for(i = 0; i < iSizeCurr/2; i++) {
            cfCurrData = piCurrCoef[i];
            piCurrCoef[i] = piCurrCoef[iSizeCurr - 1 - i];
            piCurrCoef[iSizeCurr - 1 - i] = cfCurrData;

            cfCurrData = piCurrCoef2[i];
            piCurrCoef2[i] = piCurrCoef2[iSizeCurr - 1 - i];
            piCurrCoef2[iSizeCurr - 1 - i] = cfCurrData;
        }
#else  // WMA_OPT_SUBFRAMERECON_ARM
        auSubframeRecon_swapData_Std(piCurrCoef, piCurrCoef2, iSizeCurr);
#endif // WMA_OPT_SUBFRAMERECON_ARM

        iOverlapSize = (iCurrCoefRecurQ2 - iCurrCoefRecurQ1) / 2;

        // ---- Setup the coef buffer pointer ----
        piPrevCoef = (CoefType *)ppcinfo->m_rgiCoefRecon - iOverlapSize;       // go forward
        piCurrCoef = (CoefType *)ppcinfo->m_rgiCoefRecon + iOverlapSize - 1;   // go backward

        piPrevCoef2 = (CoefType *)ppcinfo2->m_rgiCoefRecon - iOverlapSize;       // go forward
        piCurrCoef2 = (CoefType *)ppcinfo2->m_rgiCoefRecon + iOverlapSize - 1;   // go backward
        
#if !(defined(WMA_OPT_SUBFRAMERECON_ARM) && WMA_OPT_SUBFRAMERECON_ARM)
        // ---- Now we do overlap and add here ----
        for(i = 0; i < iOverlapSize; i++ ){

#ifdef RECALC
#define RECALC_R
#endif
#ifdef RECALC_R
            if (DORECALC_R(i)) {
              //BP2Type SinSave = bp2Sin;
              //BP2Type CosSave = bp2Cos;
              //BP2Type d1, d2;
              Int cSB;
              if (ppcinfo->m_iSizePrev >= ppcinfo->m_iSizeCurr)
                cSB = ppcinfo->m_iSizeCurr;  //just forward copy curr
              else
                cSB = ppcinfo->m_iSizePrev;  //long start
              bp2Sin = TR2_FROM_FLOAT(sin(PI*(2*i+1)/(4*cSB)));
              bp2Cos = TR2_FROM_FLOAT(cos(PI*(2*i+1)/(4*cSB)));
              //d1 = BPX_ABS(bp2Sin - SinSave);
              //d2 = BPX_ABS(bp2Cos - CosSave);
              //assert(d1 <= 4);
              //assert(d2 <= 4);
            }
#endif

            cfPrevData = *piPrevCoef;
            cfCurrData = *piCurrCoef;

            *piPrevCoef++  = INT_FROM_COEF( MULT_ADD2_BP2(BP2_FROM_TR2(-bp2Sin), cfCurrData,  BP2_FROM_TR2(bp2Cos), cfPrevData) );
            *piCurrCoef--  = INT_FROM_COEF( MULT_ADD2_BP2(BP2_FROM_TR2(bp2Sin), cfPrevData,  BP2_FROM_TR2(bp2Cos), cfCurrData) );

            cfPrevData = *piPrevCoef2;
            cfCurrData = *piCurrCoef2;

            *piPrevCoef2++ = INT_FROM_COEF( MULT_ADD2_BP2(BP2_FROM_TR2(-bp2Sin), cfCurrData, BP2_FROM_TR2(bp2Cos), cfPrevData) );
            *piCurrCoef2-- = INT_FROM_COEF( MULT_ADD2_BP2( BP2_FROM_TR2(bp2Sin), cfPrevData, BP2_FROM_TR2(bp2Cos), cfCurrData) );
            
#ifdef OVERLAPADD_LOOKUPTBL
            if (ppcinfo->m_overlapAddSize <= MAX_OVADD_TLU_SIZE) {
                bp2Sin  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[2*i+2]);
                bp2Cos  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[2*i+3]);
            }
            else
#endif
            {
               /* sin(a+b) = sin(a-b) + 2*sin(b)*cos(a) */
                /* cos(a+b) = cos(a-b) - 2*sin(b)*sin(a) */
                TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1,bp2Step)
                /*
                bp2SinT = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
                bp2CosT = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
                bp2Sin1 = bp2Sin;  bp2Sin = bp2SinT;
                bp2Cos1 = bp2Cos;  bp2Cos = bp2CosT;
                */
            }
        }
#else    // WMA_OPT_SUBFRAMERECON_ARM
#ifdef OVERLAPADD_LOOKUPTBL
        if (ppcinfo->m_overlapAddSize <= MAX_OVADD_TLU_SIZE) {
            auSubframeRecon_applyWindow_Std_TLU(piPrevCoef, piCurrCoef, piPrevCoef2, piCurrCoef2, 
                ppcinfo->m_overlapAddTable, iOverlapSize, pau->m_cLeftShiftBitsFixedPost);
        }
        else
#endif
        {
            auSubframeRecon_applyWindow_Std(piPrevCoef, piCurrCoef, piPrevCoef2, piCurrCoef2, 
                BP2_FROM_TR2(bp2Sin), BP2_FROM_TR2(bp2Cos), BP2_FROM_TR2(bp2Sin1), BP2_FROM_TR2(bp2Cos1), BP2_FROM_TR2(bp2Step), iOverlapSize, pau->m_cLeftShiftBitsFixedPost);
        }
#endif    // WMA_OPT_SUBFRAMERECON_ARM

    } else {
        // mono or version 3 and above
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {

            // ======== Setup the init condition for PCM reconstruction ========
            iChSrc = pau->m_rgiChInTile [iCh];
            ppcinfo = pau->m_rgpcinfo + iChSrc;

            // get previous subframe size
            iSizePrev = ppcinfo->m_iSizePrev;
            iSizeCurr = ppcinfo->m_iSizeCurr;

#ifdef OVERLAPADD_LOOKUPTBL
            if (ppcinfo->m_overlapAddSize <= MAX_OVADD_TLU_SIZE) {
                bp2Sin  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[0]);
                bp2Cos  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[1]);
            }
            else
#endif
            {
                // Reset trig recursion
                bp2Sin  = TR2_FROM_BP2(ppcinfo->m_fiSinRampUpStart);
                bp2Cos  = TR2_FROM_BP2(ppcinfo->m_fiCosRampUpStart);
                bp2Sin1 = TR2_FROM_BP2(ppcinfo->m_fiSinRampUpPrior);
                bp2Cos1 = TR2_FROM_BP2(ppcinfo->m_fiCosRampUpPrior);
                bp2Step = TR2_FROM_BP2(ppcinfo->m_fiSinRampUpStep);
            }

            prvCalcQ3Q4(pau, WMAB_FALSE, iSizePrev, iSizeCurr, iSizePrev, &iPrevCoefRecurQ3, &iPrevCoefRecurQ4);
            prvCalcQ1Q2(pau, WMAB_TRUE, iSizePrev, iSizeCurr, &iCurrCoefRecurQ1, &iCurrCoefRecurQ2);

            //==================================================================
            // ==== In-place Reconstruction between prev and curr subframes ====
            //==================================================================

            // ---- Now move unused coef to the end of current subframe coef buffer ----
            piCurrCoef = (CoefType *)ppcinfo->m_rgiCoefRecon;   // now reverse the coef buffer
            for(i = 0; i < iSizeCurr/2; i++) {
                cfCurrData = piCurrCoef[i];
                piCurrCoef[i] = piCurrCoef[iSizeCurr - 1 - i];
                piCurrCoef[iSizeCurr - 1 - i] = cfCurrData;
            }

            iOverlapSize = (iCurrCoefRecurQ2 - iCurrCoefRecurQ1) / 2;

            // ---- Setup the coef buffer pointer ----
            piPrevCoef = (CoefType *)ppcinfo->m_rgiCoefRecon - iOverlapSize;       // go forward
            piCurrCoef = (CoefType *)ppcinfo->m_rgiCoefRecon + iOverlapSize - 1;   // go backward

            // ---- Now we do overlap and add here ----
            for(i = 0; i < iOverlapSize; i++ ){

#ifdef RECALC_R
              if (DORECALC_R(i)) {
                //BP2Type SinSave = bp2Sin;
                //BP2Type CosSave = bp2Cos;
                //BP2Type d1, d2;
                Int cSB;
                if (ppcinfo->m_iSizePrev >= ppcinfo->m_iSizeCurr)
                  cSB = ppcinfo->m_iSizeCurr;  //just forward copy curr
                else
                  cSB = ppcinfo->m_iSizePrev;  //long start
                bp2Sin = TR2_FROM_FLOAT(sin(PI*(2*i+1)/(4*cSB)));
                bp2Cos = TR2_FROM_FLOAT(cos(PI*(2*i+1)/(4*cSB)));
                //d1 = BPX_ABS(bp2Sin - SinSave);
                //d2 = BPX_ABS(bp2Cos - CosSave);
                //assert(d1 <= 4);
                //assert(d2 <= 4);
              }
#endif
                cfPrevData = *piPrevCoef;
                cfCurrData = *piCurrCoef;
                *piPrevCoef++ = INT_FROM_COEF( MULT_ADD2_BP2(BP2_FROM_TR2(-bp2Sin), cfCurrData,  BP2_FROM_TR2(bp2Cos), cfPrevData) );
                *piCurrCoef-- = INT_FROM_COEF( MULT_ADD2_BP2( BP2_FROM_TR2(bp2Sin), cfPrevData,  BP2_FROM_TR2(bp2Cos), cfCurrData) );
#ifdef OVERLAPADD_LOOKUPTBL
                if (ppcinfo->m_overlapAddSize <= MAX_OVADD_TLU_SIZE) {
                    bp2Sin  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[2*i+2]);
                    bp2Cos  = TR2_FROM_BP2(ppcinfo->m_overlapAddTable[2*i+3]);
                }
                else
#endif
                {
                    /* sin(a+b) = sin(a-b) + 2*sin(b)*cos(a) */
                    /* cos(a+b) = cos(a-b) - 2*sin(b)*sin(a) */
                   TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step)
                    /*
                    bp2SinT = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
                    bp2CosT = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
                    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinT;
                    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosT;
                    */
                }
            }
        }
    }

#ifdef BUILD_INTEGER
    {
        I16 iSizeNext;
        Int iOverlapSizeNext, iEnd;
        I16 iCurrCoefRecurQ3 = 0, iCurrCoefRecurQ4 = 0;
        for (iCh = 0; iCh < pau->m_cChInTile; iCh++) {
            iChSrc = pau->m_rgiChInTile [iCh];
            ppcinfo = pau->m_rgpcinfo + iChSrc;
    
            iSizePrev = ppcinfo->m_iSizePrev;
            iSizeCurr = ppcinfo->m_iSizeCurr;
            iSizeNext = ppcinfo->m_iSizeNext;

            // In Unified WMA, we must call prvCalcQ1Q2/Q3Q4 to get the window shape. 
            // iOverlapSize = min(iSizePrev, iSizeCurr) / 2;
            prvCalcQ1Q2(pau, WMAB_TRUE, iSizePrev, iSizeCurr, &iCurrCoefRecurQ1, &iCurrCoefRecurQ2);
            iOverlapSize = (iCurrCoefRecurQ2 - iCurrCoefRecurQ1) / 2;

            // iOverlapSizeNext = min(iSizeNext, iSizeCurr) / 2;
            prvCalcQ3Q4(pau, WMAB_TRUE, iSizeCurr, iSizeNext, iSizeCurr, &iCurrCoefRecurQ3, &iCurrCoefRecurQ4);
            iOverlapSizeNext = (iCurrCoefRecurQ4 - iCurrCoefRecurQ3) / 2;

            if (pau->m_iVersion < 3) {
                iEnd = iSizeCurr - iOverlapSizeNext;
            } else { // for v3, the other half is done during the next subframe (at the top)
                iEnd = iSizeCurr / 2;
            }
        
            piCurrCoef = ppcinfo->m_rgiCoefRecon;

            WMADebugMessage("auSubframeRecon() pau->m_cLeftShiftBitsFixedPost %d, piCurrCoef[0] %d -> ", pau->m_cLeftShiftBitsFixedPost, piCurrCoef[0]);

#if !(defined(WMA_OPT_SUBFRAMERECON_ARM) && WMA_OPT_SUBFRAMERECON_ARM)
            for (i = iOverlapSize; i < iEnd; i++) {
//               piCurrCoef[i] = INT_FROM_COEF(piCurrCoef[i]);                                               
               piCurrCoef[i] = piCurrCoef[i]>>pau->m_cLeftShiftBitsFixedPost;
            }
            WMADebugMessage("%d\n", piCurrCoef[0]);

#else    // WMA_OPT_SUBFRAMERECON_ARM
        auSubframeRecon_ScaleCoef(&piCurrCoef[iOverlapSize], iEnd - iOverlapSize, pau->m_cLeftShiftBitsFixedPost);
#endif    // WMA_OPT_SUBFRAMERECON_ARM
        }
    }
#endif // BUILD_INTEGER

#if defined(BUILD_WMAPROLBRV2)
exit:
#endif
#ifdef WMAPROFILE
    FunctionProfileStop(&fp);
#endif
    return hr;
} // auSubframeRecon
#endif //WMA_OPT_SUBFRAMERECON_XENON
#endif //PLATFORM_SPECIFIC_SUBFRAMERECON

//*****************************************************************************************
//
// prvInverseTransformMono
//  transform, window and combine an overlapping subframe of audio data
//  called repeatedly for each subframe in a frame
// 
//  using abbreviated names, the process in outline form is as follows:
//  
//      pSrc points to someplace in current or previous time-domain Output array
//      pDst points to someplace in current or previous time-domain Output array
//      between each "upto" step below, these two points may change
//
//      Coef is an array of frequency-domain coefs
//
//      call DCT and transform Coef to time-domain
//      pCoef set to middle of the now time-domain coeffiecents
//
//      Window and combine the transformed Coef and pSrc into pDst as follows:
//
//      Window
//                  ________________
//                 /
//                /
//               /
//      ________/                       _________
//      |       | | |       |      | | |         |
//      0       Q Q Q       H      Q 3 Q         F
//              1 u 2       a      3 Q 4         u
//                a         l        u           l
//                d         f        a           l
//                                   d
//      
//      upto Q1 (eg 0): 
//          Dst <- Src                              [[++pDst, ++pCoef, ++pSrc]]
//
//      upto cSubFrameSampleQuad (eg 1024):
//          Dst <- ( sin(a) * Coef + Src<<5 ) >> 5  [[++pDst, ++pCoef, ++pSrc, ++a]]
//
//      upto Q2 (eg 2048):
//          Dst <- ( sin(a) * Coef + Src<<5 ) >> 5  [[++pDst, --pCoef, ++pSrc, ++a]]
//
//      upto cSubFrameSampleHalf (eg 2048):
//          Dst <- Coef >> 5                        [[++pDst, --pCoef]]
//
//      upto Q3 (eg 2944):
//          Dst <- Coef >> 5                        [[++pDst, --pCoef]]
//
//      upto 3 * cSubFrameSampleQuad (eg 3072):
//          Dst <- ( sin(a) * Coef ) >> 5;          [[++pDst, --pCoef]]
//      
//      upto Q4 (eg 3200):
//          Dst <- ( sin(a) * Coef ) >> 5;          [[++pDst, ++pCoef]]
//
//
//  
//  Values decoding the first few frames of Tough_44m_64.cmp (9/22/99 12:08PM version)
//  where pDst is relative to piOutput when c. and to piPrevOutput when p.
//
//                          iCurrSubFrame       iSubFrmOffset   pDst prior to loop:
//              FrameSample         cSubFrameSample               Q1     Q2     Q3     Q4
//                              
//  Decode             4096
//    inverseTransform          0       4096           0        c....0 c.1024 p....0 p.1024
//  Decode             4096
///   inverseTransform          0       2048         512        c..512 c.1024 c.1536 p....0
//    inverseTransform          1        256        1984        c.1984 p....0 p...64 p..128
//    inverseTransform          2        256        2112        p...64 p. 128 p..192 p..256
//    inverseTransform          3        256        2240        p. 192 p. 256 p..320 p..384
//    inverseTransform          4        256        2368        p..320 p..320 p..448 p..512
//    inverseTransform          5       1024        2304        p..256 p..512 p..768 p.1024
//  Decode             4096
//    inverseTransform          0       4096           0        c....0 c.1024 p....0 p.1024
//  Decode             4096
//    inverseTransform          0       4096           0        c....0 c.1024 p....0 p.1024
//  Decode             4096
//    inverseTransform          0       4096           0        c....0 c.1024 p....0 p.1024
//  Decode             4096
//    inverseTransform          0       2048         512        c..512 c.1024 c.1536 p....0
//    inverseTransform          1        512        1920        c.1920 p....0 p..128 p..256
//    inverseTransform          2        256        2240        p..192 p..256 p..320 p..384
//    inverseTransform          3        256        2368        p..320 p..384 p..448 p..512
//    inverseTransform          4        256        2496        p..448 p..512 p..576 p..640
//    inverseTransform          5        256        2624        p..576 p..640 p..704 p..768
//    inverseTransform          6        512        2688        p..640 p..768 p..896 p.1024
//
//*****************************************************************************************

#if defined(_DEBUG)
// Debugging Macros to break at a particular output sample or when sample values are out of range or to print sin values
//
// set IT_BREAK_AT_SAMPLE to a non-negative value to break when that sample is about to be processed
//#define IT_BREAK_AT_SAMPLE -2049
//
// set IT_BREAK_OUT_OF_RANGE to a positive value to break when a sample is stored out of the range
//#define IT_BREAK_OUT_OF_RANGE 32767
//#define IT_BREAK_OUT_OF_RANGE_PAST_SAMPLE 0
//
// set IT_SIN_PRINT_ALL to print out all sin values as they are used
//#define IT_SIN_PRINT_ALL
//
// set IT_SIN_PRINT_INIT to print out initial sin values as they are used
//#define IT_SIN_PRINT_INIT
//
// set IT_SAMPLE_PRINT to print out sample values as they are generated
//#define IT_SAMPLE_PRINT
// 
// set IT_FRAME_PRINT to print out sample values as they are generated
//#define IT_FRAME_PRINT
// 
#   if defined(IT_BREAK_AT_SAMPLE) || defined(IT_BREAK_OUT_OF_RANGE)|| defined(IT_SIN_PRINT_ALL) \
    || defined(IT_SIN_PRINT_INIT) || defined(IT_SAMPLE_PRINT) || defined(IT_FRAME_PRINT)
#       pragma COMPILER_MESSAGE(__FILE__ "(1101) : Warning - Inverse Transform Debug Code Enabled.")
#       if defined(IT_BREAK_AT_SAMPLE)
            static int nSampleBreak = IT_BREAK_AT_SAMPLE;
#       else
            static int nSampleBreak = -2049;
#       endif
        static int nSampleBreakIdx = -2048;             // correction factor for startup
        static int nSampleBreakFrameSample = 0;         // prior frame's sample size
        static int iSubFrmOffset = 0;                   // Needed to add after merging with wchen's 12/17/99 checkin ???
#   endif
#   define IT_NO_SIN 0x7FEDCBA9
    static double dIorF2F = INTEGER_OR_INT_FLOAT(1.0/NF2BP2,1.0);
#   if defined(IT_SIN_PRINT_ALL)
#       define IT_DO_SIN_PRINT(idx1,idx2,v)                                     \
            if (v != IT_NO_SIN)                                                 \
                WMAPrintf("%8d %4d %+.10f\n", idx1, idx2, v*dIorF2F )
#   else
#       define IT_DO_SIN_PRINT(a,b,c)
#   endif
#   if defined(IT_SAMPLE_PRINT)
#       define IT_DO_SAMPLE_PRINT(idx1,idx2,v) \
                WMAPrintf("%8d %4d %+10d\n", idx1, idx2, (I32)v )
#   else
#       define IT_DO_SAMPLE_PRINT(a,b,c)
#   endif
#   if defined(IT_FRAME_PRINT)
#       define IT_DO_FRAME_PRINT                                                \
            if ( pau->m_iFrameNumber==0 )                                       \
                WMAPrintf("\n");                                                   \
            WMAPrintf("Frame %4d  SubFrm %2d  SFSamples %4d\n", pau->m_iFrameNumber, pau->m_iCurrSubFrame, pau->m_cSubFrameSampleAdjusted )
#   else
#       define IT_DO_FRAME_PRINT
#   endif
#   if defined(IT_BREAK_AT_SAMPLE) && defined(IT_BREAK_OUT_OF_RANGE)
#       define DEBUG_IT_SAMPLE_BREAK(idx,Dst,iSin)                              \
            if ( (nSampleBreakIdx+idx+iSubFrmOffset) == nSampleBreak || Dst < -IT_BREAK_OUT_OF_RANGE || Dst > IT_BREAK_OUT_OF_RANGE ) \
                DEBUG_BREAK();                                                  \
            IT_DO_SIN_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,iSin);        \
            IT_DO_SAMPLE_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,Dst)
#   elif defined(IT_BREAK_AT_SAMPLE)
#       define DEBUG_IT_SAMPLE_BREAK(idx,Dst,iSin)                              \
            if ( (nSampleBreakIdx+idx+iSubFrmOffset) == nSampleBreak )          \
                DEBUG_BREAK();                                                  \
            IT_DO_SIN_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,iSin);        \
            IT_DO_SAMPLE_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,Dst)
#   elif defined(IT_BREAK_OUT_OF_RANGE)
#       define DEBUG_IT_SAMPLE_BREAK(idx,Dst,iSin)                              \
            if ( ( Dst < -IT_BREAK_OUT_OF_RANGE || Dst > IT_BREAK_OUT_OF_RANGE )\
                 && (nSampleBreakIdx+idx+iSubFrmOffset) > IT_BREAK_OUT_OF_RANGE_PAST_SAMPLE )  \
                DEBUG_BREAK();                                                  \
            IT_DO_SIN_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,iSin);        \
            IT_DO_SAMPLE_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,Dst)
#   else
#       define DEBUG_IT_SAMPLE_BREAK(idx,Dst,iSin)                              \
            IT_DO_SIN_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,iSin);        \
            IT_DO_SAMPLE_PRINT(nSampleBreakIdx+idx+iSubFrmOffset,idx,Dst)
#   endif
#   if defined(IT_SIN_PRINT_INIT)
#       define DEBUG_IT_SIN_INIT(n,a,b,c,d,e)   \
                WMAPrintf("%d  %+.10f  %+.10f  %+.10f  %+.10f  %+.10f\n", n, a*dIorF2F, b*dIorF2F, c*dIorF2F, d*dIorF2F, e*dIorF2F )
#   else
#       define DEBUG_IT_SIN_INIT(n,a,b,c,d,e)
#   endif
#   if defined(IT_BREAK_AT_SAMPLE) || defined(IT_BREAK_OUT_OF_RANGE) || defined(IT_SIN_PRINT_ALL) || defined(IT_SIN_PRINT_INIT)
        // break when nSampleBreak is within subframe
#       define DEBUG_IT_FRAME_BREAK \
            if ( pau->m_iCurrSubFrame == 0 && ppcinfo == pau->m_rgpcinfo )      \
            {   /* on first subframe of left channel */                         \
                nSampleBreakIdx += nSampleBreakFrameSample;                     \
                nSampleBreakFrameSample = pau->m_cFrameSampleHalfAdjusted;      \
            }                                                                   \
            IT_DO_FRAME_PRINT;                                                  \
            if ( nSampleBreakIdx+iSubFrmOffset <= nSampleBreak && nSampleBreak < (nSampleBreakIdx+iSubFrmOffset+pau->m_cSubFrameSampleAdjusted) )   \
                DEBUG_BREAK();
#   else
#       define DEBUG_IT_FRAME_BREAK
#   endif
#else
#   define DEBUG_IT_FRAME_BREAK
#   define DEBUG_IT_SAMPLE_BREAK(a,b,c)
#   define IT_NO_SIN 0x40000000
#   define DEBUG_IT_SIN_INIT(n,a,b,c,d,e)
#endif


#ifndef WMA_TARGET_SH4
void prvCalcQ1Q2(CAudioObject * pau, Bool bCurrWindow, const I16 iSizePrev, const I16 iSizeCurr,
                 I16 *piCoefRecurQ1, I16 *piCoefRecurQ2)
{

#ifdef BUILD_WMAPROLBRV2
     CBasePlusObject* pbp = pau->m_pbp;
#endif

    //This function can calculate the Q1/Q2 or current window or next window but
    //so far we only it for the current window although this function support next window.
    assert(bCurrWindow);
    //if the adjacent size is bigger; just keep your own shape
    //otherwise a transition window is needed.
    if (iSizePrev >= iSizeCurr) 
    {
        //just forward copy curr
        *piCoefRecurQ1 = 0;
        *piCoefRecurQ2 = iSizeCurr;
    }
    else  
    {
        //long start
        *piCoefRecurQ1 = (iSizeCurr - iSizePrev) / 2;
        *piCoefRecurQ2 = (iSizeCurr + iSizePrev) / 2;
    }

    // update for MLLMUsePLLM.
    if (bCurrWindow == WMAB_TRUE) {
        if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
            if (pau->m_bFirstUnifiedPureLLMFrm == WMAB_FALSE) {
                *piCoefRecurQ1 = (*piCoefRecurQ1 + *piCoefRecurQ2) / 2;
                *piCoefRecurQ2 = *piCoefRecurQ1;
            }            
        }
    }
    else { // we are working on next window
        if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
            if (pau->m_bLastUnifiedPureLLMFrm == WMAB_FALSE) {
                *piCoefRecurQ1 = (*piCoefRecurQ1 + *piCoefRecurQ2) / 2;
                *piCoefRecurQ2 = *piCoefRecurQ1;
            }            
        }
    }

#ifdef BUILD_WMAPROLBRV2
    if (pau->m_fBasePlusPresent)
    {
        if (pbp->m_fLowDelayWindow)
        {
            assert(WMAB_FALSE == pau->m_bUnifiedPureLLMCurrFrm);
            // in baseplus low delay mode, we limit the overlap size to be <= 10ms
            while (((*piCoefRecurQ2) - (*piCoefRecurQ1)) > pbp->m_iOverlapWindowDelay * pau->m_iSamplingRate / 100)        
            {
                I16 iQ1, iQ2;
                iQ1 = *piCoefRecurQ1;
                iQ2 = *piCoefRecurQ2;
                assert(((iQ2-iQ1)%4) == 0);
                (*piCoefRecurQ1) = iQ1 + (iQ2-iQ1)/4;
                (*piCoefRecurQ2) = iQ2 - (iQ2-iQ1)/4;
            }
        }
    }
#endif 

}


void prvCalcQ3Q4(CAudioObject *pau, Bool bCurrWindow, const I16 iSizeCurr, const I16 iSizeNext,
                 const Int cSubFrameSampleHalfAdjusted,
                 I16 *piCoefRecurQ3, I16 *piCoefRecurQ4)
{
    //This function can calculate the Q1/Q2 or current window or prev window but
    //so far we only it for the current window.

#ifdef BUILD_WMAPROLBRV2
     CBasePlusObject* pbp = pau->m_pbp;
#endif

    if (iSizeNext >= iSizeCurr) 
    {
        *piCoefRecurQ3 = (I16) cSubFrameSampleHalfAdjusted;
        *piCoefRecurQ4 = (I16) cSubFrameSampleHalfAdjusted * 2;
    }
    else    {
        //just backward copy curr
        *piCoefRecurQ3 = (I16) cSubFrameSampleHalfAdjusted +
            (iSizeCurr - iSizeNext) / 2;
        *piCoefRecurQ4 = (I16) cSubFrameSampleHalfAdjusted +
            (iSizeCurr + iSizeNext) / 2;
    }

    // update for MLLMUsePLLM.
    if (bCurrWindow == WMAB_TRUE) {
        if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
            if (pau->m_bLastUnifiedPureLLMFrm == WMAB_FALSE) {
                *piCoefRecurQ3 = (*piCoefRecurQ3 + *piCoefRecurQ4) / 2;
                *piCoefRecurQ4 = *piCoefRecurQ3;
            }            
        }
    }
    else { // we are working on prev window
        if (pau->m_bUnifiedPureLLMCurrFrm == WMAB_TRUE) {
            if (pau->m_bFirstUnifiedPureLLMFrm == WMAB_FALSE) {
                *piCoefRecurQ3 = (*piCoefRecurQ3 + *piCoefRecurQ4) / 2;
                *piCoefRecurQ4 = *piCoefRecurQ3;
            }            
        }
    }
#ifdef BUILD_WMAPROLBRV2
    if (pau->m_fBasePlusPresent)
    {
        if (pbp->m_fLowDelayWindow)
        {
            assert(WMAB_FALSE == pau->m_bUnifiedPureLLMCurrFrm);
            // in baseplus low delay mode, we limit the overlap size to be <= 10ms
            while (((*piCoefRecurQ4) - (*piCoefRecurQ3)) >  pbp->m_iOverlapWindowDelay * pau->m_iSamplingRate / 100)
            {
                I16 iQ3, iQ4;
                iQ3 = *piCoefRecurQ3;
                iQ4 = *piCoefRecurQ4;
                assert(((iQ4-iQ3)%4) == 0);
                (*piCoefRecurQ3) = iQ3 + (iQ4-iQ3)/4;
                (*piCoefRecurQ4) = iQ4 - (iQ4-iQ3)/4;
            }
        }
    }
#endif 

}
#endif //!WMA_TARGET_SH4

#if defined(SH4) || defined(_SH4_)
#   pragma warning(disable:4719)
#endif
WMARESULT prvAdaptTrigToSubframeConfig(CAudioObject *pau)
{
    WMARESULT wmaResult = WMA_OK;
    I16                 iSize2Use, iCh;

#ifdef WMAPROFILE
    //FunctionProfile fp;
    //FunctionProfileStart(&fp,ADAPT_TRIG_TO_SUB_FRAME_CONFIG_PROFILE);
#endif

    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        I16 iChSrc = pau->m_rgiChInTile [iCh];
        PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iChSrc;

        //if the adjacent size is bigger; just keep your own shape
        //otherwise a transition window is needed.
        if (ppcinfo->m_iSizePrev >= ppcinfo->m_iSizeCurr)
            iSize2Use = ppcinfo->m_iSizeCurr;  //just forward copy curr
        else
            iSize2Use = ppcinfo->m_iSizePrev;  //long start

#ifdef USE_SIN_COS_TABLES
        switch (iSize2Use){
            case 8192:
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon8192;
                break;
            case 4096:
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon4096;
                break;
            case 2048:
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon2048;
                break;
            case 1024:
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon1024;
                break;
            case 512 :
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon512;
                break;
            case 256 :
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon256;
                break;
            case 128 :
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon128;
                break;
            case 64  :
                ppcinfo->m_piSinForRecon = pau->m_piSinForRecon64;
                break;
            default: 
                REPORT_BITSTREAM_CORRUPTION();
                return (TraceResult (WMA_E_BROKEN_FRAME));
        }
#endif //weight input still uses the recursion
        // Use lookup-tables if we can
        if (iSize2Use >= 64 && iSize2Use <= 2048 && CHECK_POWER_OF_TWO(iSize2Use) )
        {
            const SinCosTable* pSinCosTable = rgSinCosTables[iSize2Use>>7];

            // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
            ppcinfo->m_fiSinRampUpStart =  BP2_FROM_BP1(pSinCosTable->sin_PIby4cSB);    //(Int) (sin (0.5 * PI / iSizeCurr / 2) * 0x3FFFFFFF);
            ppcinfo->m_fiCosRampUpStart =  BP2_FROM_BP1(pSinCosTable->cos_PIby4cSB);    //(Int) (cos (0.5 * PI / iSizeCurr / 2) * 0x3FFFFFFF);

            // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
            ppcinfo->m_fiSinRampUpPrior = -BP2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
            ppcinfo->m_fiCosRampUpPrior =  BP2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
            ppcinfo->m_fiSinRampUpStep  =  SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB);   // STEP = 2 * sin (PI / 2 / iSizeCurr) * 0x3FFFFFFF;
        }
        else
        {
            ppcinfo->m_fiSinRampUpStart =  (BP2Type) (sin (0.5f * PI / iSize2Use / 2) * NF2BP2);
            ppcinfo->m_fiCosRampUpStart =  (BP2Type) (cos (0.5f * PI / iSize2Use / 2) * NF2BP2);
            ppcinfo->m_fiSinRampUpPrior =  (BP2Type) -(sin(0.5f * PI / iSize2Use / 2) * NF2BP2);
            ppcinfo->m_fiCosRampUpPrior =  (BP2Type) (cos (0.5f * PI / iSize2Use / 2) * NF2BP2);
            ppcinfo->m_fiSinRampUpStep  =  (BP2Type) (sin (PI / 2 / iSize2Use) * NF2BP1);
        }

#ifdef OVERLAPADD_LOOKUPTBL
        switch (iSize2Use){
            case 8192:
                ppcinfo->m_overlapAddTable = OverlapAddTab_8192;
                ppcinfo->m_overlapAddSize = 8192;
                break;
            case 4096:
                ppcinfo->m_overlapAddTable = OverlapAddTab_4096;
                ppcinfo->m_overlapAddSize = 4096;
                break;
            case 2048:
                ppcinfo->m_overlapAddTable = OverlapAddTab_2048;
                ppcinfo->m_overlapAddSize = 2048;
                break;
            case 1024:
                ppcinfo->m_overlapAddTable = OverlapAddTab_1024;
                ppcinfo->m_overlapAddSize = 1024;
                break;
            case 512 :
                ppcinfo->m_overlapAddTable = OverlapAddTab_512;
                ppcinfo->m_overlapAddSize = 512;
                break;
            case 256 :
                ppcinfo->m_overlapAddTable = OverlapAddTab_256;
                ppcinfo->m_overlapAddSize = 256;
                break;
            case 128 :
                ppcinfo->m_overlapAddTable = OverlapAddTab_128;
                ppcinfo->m_overlapAddSize = 128;
                break;
            case 64  :
                ppcinfo->m_overlapAddTable = OverlapAddTab_64;
                ppcinfo->m_overlapAddSize = 64;
                break;
        }
#endif

    // Include the next code-block to verify changes to the lookup-table
#if defined (_DEBUG) && defined (BUILD_INTEGER) && !defined(CATCH_FLOATOPS)
        assert(abs(ppcinfo->m_fiSinRampUpStart - ((BP2Type) (sin (0.5 * PI / iSize2Use / 2) * NF2BP2))) <= 10000);
        assert(abs(ppcinfo->m_fiCosRampUpStart - ((BP2Type) (cos (0.5 * PI / iSize2Use / 2) * NF2BP2))) <= 10000);
        assert(abs(ppcinfo->m_fiSinRampUpPrior - ((BP2Type) -(sin(0.5 * PI / iSize2Use / 2) * NF2BP2))) <= 10000);
        assert(abs(ppcinfo->m_fiCosRampUpPrior - ((BP2Type) (cos (0.5 * PI / iSize2Use / 2) * NF2BP2))) <= 10000);
        assert(abs(ppcinfo->m_fiSinRampUpStep  - ((BP2Type) (sin (PI / 2 / iSize2Use) * NF2BP1))) <= 10000); // STEP = 2 * 
#endif
        ppcinfo++;
    }
    return wmaResult;
}
#if defined(SH4) || defined(_SH4_)
#   pragma warning(default:4719)
#endif
//#endif  // defined(BUILD_INTEGER)

//*****************************************************************************************
//
// auUpdateMaxEsc
//
//*****************************************************************************************
Void    auUpdateMaxEsc(CAudioObject* pau, Int iQuantStepSize)
{
    // HongCho: Adjust the max Tunstall level according to the quantization step...
    //          Matching if's in the decoder...
    //          Too many?  Maybe...
    // HongCho: Note...  For 22.05kHz, even with all 15bits, the bells don't ring...
    if (pau->m_iVersion >= 3)
    {
        pau->m_iMaxEscSize = 31;
        pau->m_iMaxEscLevel = 0x7fffffff; // (1<<31) - 1 seems risky
    }
    else
    {
        if(iQuantStepSize < 5)       pau->m_iMaxEscSize = 13;
        else if(iQuantStepSize < 15) pau->m_iMaxEscSize = 13;
        else if(iQuantStepSize < 32) pau->m_iMaxEscSize = 12;
        else if(iQuantStepSize < 40) pau->m_iMaxEscSize = 11;
        else if(iQuantStepSize < 45) pau->m_iMaxEscSize = 10;
        else if(iQuantStepSize < 55) pau->m_iMaxEscSize =  9;
        else                         pau->m_iMaxEscSize =  9;
        pau->m_iMaxEscLevel = (1<<pau->m_iMaxEscSize) - 1;
    }
}


void auLowPass(CAudioObject *pau, CoefType *rgCoef, Int iNumCoefs,
               Int iPassThruCoefs)
{
    CoefType    *pEnd = rgCoef + iNumCoefs * 2; // Re and Im coefs (so times 2)
    CoefType    *pCurr;
    //Int     iPassThruCoefs;

    // Figure out how many coefficients will pass through untouched
    //iPassThruCoefs = (pau->m_iInterpolDstBlkSize * iNumCoefs) / 
    //    pau->m_iInterpolSrcBlkSize;
    pCurr = rgCoef + (2 * iPassThruCoefs);   // Re and Im coefs (so times 2)
    iNumCoefs -= iPassThruCoefs;

    while (iNumCoefs > 0)
    {
        *pCurr++ = 0;       // Re coef
        *pCurr++ = 0;       // Im coef
        iNumCoefs -= 1;
    }

    assert(pCurr == pEnd);
}

//*****************************************************************************************
//
// qstCalcQuantStep
// like auCalcQuantStep but returns a QuantStepType which is either:
//   a FastFloat (for integer builds), a Float (Decoder) or a Double(Encoder)
//
//*****************************************************************************************
   
// is a negative index still possible? apparently V5 encoder could produce negative indices.
// qstCalcQuantStep() is also used by WMA-Pro+ V2, in the freqexInvQuantScaleV2() function;
// that function requires negative indices for this lookup table.

#define QSTEP_LUT_MAX 258

#ifdef BUILD_WMAPROLBRV2
#define QSTEP_LUT_MIN -32
#else
#define QSTEP_LUT_MIN 0
#endif

static QuantStepType g_qstQStepLUT[ QSTEP_LUT_MAX-QSTEP_LUT_MIN ];
static Bool g_qst_init = 0;

// !! need to prevent race condition when multiple encoders
// !! are instantiated. Just make the table 'static const'.

static void InitQstQuantStepLUT()
{
    Int iQSS;

    catchFP();
    for( iQSS = QSTEP_LUT_MIN; iQSS < QSTEP_LUT_MAX; ++iQSS )
    {
        g_qstQStepLUT[ iQSS-QSTEP_LUT_MIN ] = FASTFLOAT_FROM_FLOAT( (Float)pow( 10, iQSS * 0.05f ) );
    }
    initFP();

    g_qst_init = 1;
}

QuantStepType qstCalcQuantStep( const Int iQSS, const Int cLeftShiftBits )
{
    FastFloat fflt;

    //assert( iQSS >= QSTEP_LUT_MIN );
    //assert( iQSS <  QSTEP_LUT_MAX );

    //iQSS = max( iQSS, QSTEP_LUT_MIN   );
    //iQSS = min( iQSS, QSTEP_LUT_MAX-1 );

    if( !g_qst_init ) InitQstQuantStepLUT();

    if( QSTEP_LUT_MIN <= iQSS && QSTEP_LUT_MAX > iQSS )
    {
        fflt = g_qstQStepLUT[ iQSS-QSTEP_LUT_MIN ];
    }
    else
    {
        catchFP();
        TraceInfo1( " *** TRACE *** iQSS out of LUT bounds. ( %i )\n", iQSS );
        fflt = FASTFLOAT_FROM_FLOAT( (Float)pow( 10, iQSS * 0.05f ) );
        initFP();
    }

#ifdef BUILD_INTEGER
    fflt.iFracBits += cLeftShiftBits;
#endif

    return fflt;
}

//*****************************************************************************************

void prvInitDiscardSilence(CAudioObject *pau, Bool fSPDIF)
{
    Bool fStartOfStream = WMAB_TRUE;
    Int  iCh;

    assert(CODEC_BEGIN == pau->m_codecStatus);

    // We do not discard any silence for lossless mode
    if (pau->m_bPureLosslessMode)
        return;

    // ********** Start of file detection ***********

    // If this is the very first frame, we need to determine if we are at the
    // start-of-file, rather than seeking. If so, we need to discard the silence
    // frames. If not, we need to only discard half a subframe. NOTE that for
    // V4 encoded streams, WE WILL GUESS INCORRECTLY. Our justification for accepting
    // this is that V4 never had timestamps and so sync was never guaranteed anyway.

    if (pau->m_iVersion <= 2)
    {
        // Due to SCRUNCH bug #32, v5 encoder forces fMaskUpdate to TRUE and
        // all channels' m_iPower to 1 in the very first frame only. If we find that
        // fMaskUpdate, m_iPower are all TRUE but in fact there is no power here,
        // then we know this is a v5-encoded file and this is start-of-file
        //wchen: subfrmconfig should be the same for all channels for V2
        if (WMAB_FALSE == pau->m_rgpcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgfMaskUpdate[0])
            fStartOfStream = WMAB_FALSE;

        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
        {
            if (0 == pau->m_rgpcinfo[iCh].m_iPower)
                fStartOfStream = WMAB_FALSE;
        }

        if (fStartOfStream)
        {
            // Bitstream has forced update, claims non-zero power for all channels.
            // Verify that claim.
            for (iCh = 0; iCh < pau->m_cChannel; iCh++)
            {
                if (0 != pau->m_rgpcinfo[iCh].m_iActualPower)
                    fStartOfStream = WMAB_FALSE;
            } // for (channels)
        }
    }

    // For v3, pau->m_fLeadingSilence indicates star-of-file

    // ********* Now set pau->m_rgiDiscardSilence array for each channel **********
    pau->m_fSeekAdjustment = WMAB_FALSE;

    if (pau->m_iVersion <= 2)
    {
        I32 iDiscardSilence = 0;

        assert( !fSPDIF );  // we don't expect fSPDIF to be true for v2

        if (fStartOfStream) 
        {
            iDiscardSilence = pau->m_cFrameSampleAdjusted;

        } 
        else
        {
            I16  iSizePrev, iSizeCurr, Q1, Q2;

            iSizePrev = (I16)pau->m_rgpcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[-1];
            iSizeCurr = (I16)pau->m_rgpcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize [0];

            if (pau->m_fHalfTransform) {
                iSizeCurr >>= pau->m_iAdjustSizeShiftFactor;
                iSizePrev >>= pau->m_iAdjustSizeShiftFactor;
            }else if (pau->m_fPad2XTransform) {
                iSizeCurr <<= pau->m_iAdjustSizeShiftFactor;
                iSizePrev <<= pau->m_iAdjustSizeShiftFactor;
            }

            prvCalcQ1Q2(pau, WMAB_TRUE, iSizePrev, iSizeCurr, &Q1, &Q2 );

            //iDiscardSilence = iSizePrev / 2 + Q2 - iSizeCurr / 2;
            iDiscardSilence = pau->m_cFrameSampleHalfAdjusted / 2 + Q2 - iSizeCurr / 2;
            pau->m_fSeekAdjustment = WMAB_TRUE;
        }

        assert(iDiscardSilence >= 0);

        // Propagate iDiscardSilence to all channels
        for (iCh = 0; iCh < pau->m_cChannel; iCh++)
            pau->m_rgiDiscardSilence[iCh] = iDiscardSilence;
    }
    else
    {
        // ====== For V3 or above ======
        if( pau->m_fLeadingSilence )
        {
            // ---- We are at the beginning of a file, so discard one frame ----
            // for SPDIF actually we don't want to discard silence,
            // however we disable this in msaudiodec.c by checking SPDIF flag
            // so we are fine here to set non-zero values for SPDIF
            for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                pau->m_rgiDiscardSilence[iCh] = AU_HALF_OR_DOUBLE(pau->m_fHalfTransform, pau->m_fPad2XTransform, pau->m_u32LeadingSize);
        }
        else
        {
            // ---- We are at the first frame for seeking ----
            Int     iSubframeSize, iMaxSubframeSize = 0;

            if( fSPDIF )    // in reality this won't happen
            {
                iMaxSubframeSize = -pau->m_cFrameSampleHalfAdjusted;
            }
            else
            {
                // we try to find the max first subframe size for all the channel
                for ( iCh = 0; iCh < pau->m_cChannel; iCh++ ) {

                    PerChannelInfo* ppcinfo = pau->m_rgpcinfo + iCh;

                    iSubframeSize = ppcinfo->m_rgsubfrmconfig[CONFIG_CURRFRM].m_rgiSubFrameSize[0];

                    if (pau->m_fHalfTransform) {
                        iSubframeSize >>= pau->m_iAdjustSizeShiftFactor;
                    }else if (pau->m_fPad2XTransform) {
                        iSubframeSize <<= pau->m_iAdjustSizeShiftFactor;
                    }

                    if( iSubframeSize > iMaxSubframeSize )
                        iMaxSubframeSize = iSubframeSize;
                }
            }

            // now discard half of the max subframe size
            for (iCh = 0; iCh < pau->m_cChannel; iCh++)
                pau->m_rgiDiscardSilence[iCh] = (pau->m_cFrameSampleHalfAdjusted + iMaxSubframeSize) / 2;
#if defined(BUILD_WMAPROLBRV2)
            chexAdjustTileStartEnd(pau);
            // at this point, decoder has no recon tiles added unless current
            // frame only has 1 base tile, so for cases when there is more than
            // 1 base tile, we can simply set leading silence to true
            if (pau->m_bReconProc)
            {
                assert(0 == pau->m_iAdjustSizeShiftFactor);
                assert(!pau->m_bEncoder);
                pau->m_fLeadingSilence = WMAB_TRUE;
                pau->m_u32LeadingSize = pau->m_rgiDiscardSilence[0];
            }
#endif
        }
    }

    if (CODEC_BEGIN == pau->m_codecStatus) {
        pau->m_codecStatus = CODEC_STEADY;
    }

} // prvInitDiscardSilence

WMARESULT auInvChannelXForm (CAudioObject *pau,
                             Bool fInvertSuperGroupXform)
{
    WMARESULT wmaResult = WMA_OK;
    I16 iChSrc, iChDst, iCh;
    PerChannelInfo* ppcinfo = pau->m_rgpcinfo;
    I32 iCoef;

    CoefType* rgfltCoefDst = pau->m_rgfltCoefDst;
    Bool fAllSkip = WMAB_TRUE;

#if 0
    prvPrintChMatrix(pau);
#endif

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

    if ((pau->m_iVersion > 2) &&
        ((pau->m_rgChannelGrpInfo == NULL) || (pau->m_cChannelGroup == 0)))
    {
        assert (WMAB_FALSE);
        wmaResult = TraceResult(WMA_E_INVALIDARG);
        goto exit;
    }
    
    for (iCh = 0; iCh < pau->m_cChInTile; iCh++)
    {
        iChSrc = pau->m_rgiChInTile [iCh];
        fAllSkip &= ((pau->m_rgpcinfo + iChSrc)->m_iPower == 0);
    }
    
    if (pau->m_iVersion <= 2 && !fInvertSuperGroupXform) {
        CoefType*  piCoefRecon0;
        CoefType*  piCoefRecon1;

        assert(pau->m_cChannel <= 2);
        if (ppcinfo->m_stereoMode != STEREO_LEFTRIGHT && !fAllSkip)
        {
            //faster, special case for sum and diff
            piCoefRecon0 = (CoefType*) pau->m_rgpcinfo[0].m_rgiCoefRecon;
            piCoefRecon1 = (CoefType*) pau->m_rgpcinfo[1].m_rgiCoefRecon;
            // Do channel mixing.
            assert(pau->m_cChannel == 2);
            for (iChSrc = 0; iChSrc < pau->m_cChannel; iChSrc++)
            {
                (pau->m_rgpcinfo + iChSrc)->m_iPower = 1;
            }
#if !(defined(WMA_OPT_INV_CH_XFORM_ARM) && WMA_OPT_INV_CH_XFORM_ARM)  
            for (iCoef = (I16) ppcinfo->m_cSubbandAdjusted; iCoef > 0; iCoef--) 
            {
                CoefType    cfTemp0;
                CoefType    cfTemp1;

                cfTemp0 = *piCoefRecon0;
                cfTemp1 = *piCoefRecon1;
                *piCoefRecon0 = cfTemp0 + cfTemp1;
                *piCoefRecon1 = cfTemp0 - cfTemp1;
                piCoefRecon0++;
                piCoefRecon1++;
            }
#else   // WMA_OPT_INV_CH_XFORM_ARM
            auInvChannelXForm_Loop(piCoefRecon0, piCoefRecon1, ppcinfo->m_cSubbandAdjusted);
#endif  // WMA_OPT_INV_CH_XFORM_ARM
        }
    } 
    else if (pau->m_iVersion >= 3)
    {
        // V3 bits. Perform inverse multichannel transform
        //I16 cSubbandAdj = (pau->m_rgpcinfo + pau->m_rgiChInTile [0])->m_cSubFrameSampleHalf;
        //const U16 cLastCodedIndex = pau->m_cHighCutOff;
        U16 cLastCodedIndex = pau->m_cLastCodedIndex;

#if defined(BUILD_WMAPROLBRV1)

        if (pau->m_bFreqex && pau->m_bDoFexOnCodedChannels)
        {
            cLastCodedIndex = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;
        }

#endif // BUILD_WMAPROLBRV1

        if (!fAllSkip) 
        {
            Int iChGrp, iBand;
            
            // Do the transform on a channel group basis
            for (iChGrp = 0; iChGrp < pau->m_cChannelGroup; iChGrp++) {
                // Position src correctly for this channel group
                CChannelGroupInfo* pcgi = pau->m_rgChannelGrpInfo + iChGrp;
                Bool *rgfChannelMask = pcgi->m_rgfChannelMask;
            
                // are we supposed to process this channel group
                if (pcgi->m_fIsSuperGroupXform != fInvertSuperGroupXform)
                    continue;

                if (pcgi->m_cChannelsInGrp == 1 || 
                    (pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
                    pcgi->m_predefinedXformType == MULTICH_IDENTITY)) 
                {
                    // Identity transform for this channel group: do nothing
#if defined(BUILD_WMAPROLBRV2)
                    //if (pau->m_bCxPresent)
                    //    chexCopyChannelsForIdentityXForm(pau);
#endif
                } 
                else if (pau->m_cChannel == 2 &&
                         pcgi->m_fIsPredefinedXform == WMAB_TRUE &&
                         pcgi->m_predefinedXformType == MULTICH_HADAMARD) 
                {
                    // Somewhat faster processing for stereo-pairs in stereo coding: weights absorbed into
                    // encoder's forward matrix.
                    CoefType* pfltCoefSrc0 = (CoefType*)pau->m_rgpcinfo[0].m_rgiCoefRecon;
                    CoefType* pfltCoefSrc1 = (CoefType*)pau->m_rgpcinfo[1].m_rgiCoefRecon;
                    
                    assert(pau->m_rgChannelGrpInfo[iChGrp].m_cChannelsInGrp == 2);

                    for (iBand = 0; iBand < pau->m_cValidBarkBand; iBand++) {
                        if (pcgi->m_rgfXformOn[iBand] == WMAB_TRUE) {
                            for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                                iCoef <  min(cLastCodedIndex, pau->m_rgiBarkIndex[iBand+1]); 
                                iCoef++) 
                            {
                                CoefType fltDst0 = *pfltCoefSrc0 - *pfltCoefSrc1;
                                CoefType fltDst1 = *pfltCoefSrc0 + *pfltCoefSrc1;

                                *pfltCoefSrc0++ = fltDst0;
                                *pfltCoefSrc1++ = fltDst1;
                            }
                        } else {
                            //WMAFprintf(stdout, "Here\n");
                            // identity transform for this bark: Just do the scaling.
                            for (iCoef = pau->m_rgiBarkIndex[iBand]; 
                                iCoef < min(cLastCodedIndex,pau->m_rgiBarkIndex[iBand+1]); 
                                iCoef++) 
                            {
                                *pfltCoefSrc0 = MULT_CH_SQRT2(*pfltCoefSrc0);
                                *pfltCoefSrc1 = MULT_CH_SQRT2(*pfltCoefSrc1);
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

                    // Collect channel group members together
                    for (iCh = 0; iCh < pau->m_cChInTile; iCh++) 
                    {
                        I16 iChSrcTmp = pau->m_rgiChInTile [iCh];
                        PerChannelInfo* ppcinfoTmp = pau->m_rgpcinfo + iChSrcTmp;
                        if (rgfChannelMask[iChSrcTmp] == WMAB_TRUE) 
                        {
                            rgpCoefGrpSrc[iCh0] = ppcinfoTmp->m_rgCoefRecon;
                            iCh0++;
                        }
                    }
                    assert(iCh0 == cChannelsInGrp);

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
                                    const CoefType dst0 = 
                                        MULT_CH(rgfltMultiXGrpInverse[0], *(rgpCoefGrpSrc [0])) + 
                                        MULT_CH(rgfltMultiXGrpInverse[1], *(rgpCoefGrpSrc [1]));
                                    const CoefType dst1 = 
                                        MULT_CH(rgfltMultiXGrpInverse[2], *(rgpCoefGrpSrc [0])) + 
                                        MULT_CH(rgfltMultiXGrpInverse[3], *(rgpCoefGrpSrc [1]));
                                    *rgpCoefGrpSrc[0]++ = dst0;
                                    *rgpCoefGrpSrc[1]++ = dst1;
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
            }
        }
    }

exit:
    return wmaResult;

} // auInvChannelXForm

#ifdef RECALC
AVRT_DATA Int g_rcFFT = 1;
AVRT_DATA Int g_rcEverySampleFFT = 0;
AVRT_DATA Int g_rcNxFFT = 1;
AVRT_DATA Int g_rcNFFT = 8;
AVRT_DATA Int g_rcR = 1;
AVRT_DATA Int g_rcEverySampleR = 0;
AVRT_DATA Int g_rcNxR = 1;
AVRT_DATA Int g_rcNR = 8;
AVRT_DATA I64 g_maxValFFT = 0;
#endif

// suppose we have subframes sizes (prev, curr, next), then
//
// define pt=s, where s = subframe start within frame to be start of curr
//
// window size              = curr*2
// valid range for window   = s + [-curr/2 3*curr/2-1]
// nonzero range for window = s + [-min(prev,curr)/2 curr+min(curr,next)/2-1]
//
// divide valid range into 7 ranges (5 window ranges)
// let curr=c, next=n, prev=p
//
// 1. [s-c/2               s-min(p,c)/2-1    ] 0's
// 2. [s-min(p,c)/2        s-1               ] rising window from prev
// 3. [s                   s+min(p,c)/2      ] rising window from curr
// 4. [s+min(p,c)/2+1      s+c-min(c,n)/2-1  ] 1's
// 5. [s+c-min(c,n)/2      s+c-1             ] falling window from curr
// 6. [s+c                 s+c+min(c,n)/2-1  ] falling window from next
// 7. [s+c+min(c,n)/2      s+3*c/2-1         ] 0's
//
// 1st quarter: regions 1 & 2
// 2nd quarter: regions 3 & part of 4
// 3rd quarter: regions part of 4 & 5
// 4th quarter: regions 6 & 7
// 
// Let s = c/2
// then region 1 becomes [0 c/2-min(p,c)/2-1]
// and so on...
//
// window size is 2*iSizeCurr

#if !defined(WMA_OPT_AUWINDOW_XENON) 

#   if  defined(BUILD_INTEGER) || defined (DISABLE_OPT) || !defined (WMA_TARGET_X86)

// auApplyWindow steps forward 1 increment at a time under BUILD_INTEGER.
#       ifdef APPLYWINDOW_C_OPT
Void auApplyWindow(CAudioObject *pau, CoefType *pctCoef,
                     Int iSizePrev, Int iSizeCurr, Int iSizeNext, Bool fBase)
{
    Int i, j, iPrevOverlap, iNextOverlap;
    const SinCosTable *pSinCosTable;

    TR2_TYPE bp2Sin, bp2Cos;
    TR2_TYPE bp2Sin1, bp2Cos1;
    TR2_TYPE bp2Step;
    const BP2Type* pbp2Window;

    if (fBase)
    {
        I16 iQ1, iQ2, iQ3, iQ4;
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr, &iQ1, &iQ2);
        iPrevOverlap = (iQ2 - iQ1) / 2;
        prvCalcQ3Q4(pau, WMAB_TRUE, (I16)iSizeCurr, (I16)iSizeNext, (I16)iSizeCurr, &iQ3, &iQ4);
        iNextOverlap = (iQ4 - iQ3) / 2;
    }
    else
    {
        iPrevOverlap = min(iSizePrev, iSizeCurr) / 2;
        iNextOverlap = min(iSizeCurr, iSizeNext) / 2;
    }

    if (iPrevOverlap == iNextOverlap)
    {
        // need only 2 loops: one for zeros and one for window
        j = iSizeCurr / 2 - iPrevOverlap;
        for (i = 0; i < j; i++)
        {
            pctCoef[i] = 0;
            pctCoef[(iSizeCurr << 1) - 1 - i] = 0;
        }
        // Same as (iPrevOverlap == 64 || iPrevOverlap == 128) since iPrevOverlap is power of 2
        if (iPrevOverlap & ( 64 | 128))
        {
            pbp2Window = (iPrevOverlap == 64) ? g_bp2SinLUT128 : g_bp2SinLUT256;
#if !defined(WMA_OPT_APPLYWINDOW_ARM) || !WMA_OPT_APPLYWINDOW_ARM
            j = iSizeCurr / 2 + iPrevOverlap;
            for (; i < j; i++ )
            {
                pctCoef[i] = MULT_BP2(*pbp2Window, pctCoef[i]);
                pctCoef[(iSizeCurr << 1) - 1 - i] = MULT_BP2(*pbp2Window++, pctCoef[(iSizeCurr << 1) - 1 - i]);
            }
#else
            assert((iPrevOverlap & 1) == 0); // 2 * iPrevOverlap is multiple of 4 assumed in ASM
            auApplyWindowLoop_LUT_Bidirectional(&pctCoef[i], &pctCoef[(iSizeCurr << 1) - 1 - i],
                                                pbp2Window, iPrevOverlap << 1);
#endif
        }
        else if (iPrevOverlap)
        {
            assert(SINCOSTABLE_ENTRIES > (iPrevOverlap >> 6));
            pSinCosTable = rgSinCosTables[iPrevOverlap >> 6];
            bp2Sin   =  TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
            bp2Cos   =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
            bp2Sin1  = -bp2Sin;
            bp2Cos1  =  bp2Cos;
            bp2Step  = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));
            j = iSizeCurr / 2 + iPrevOverlap;
            for (; i < j; i += 2)
            {
                pctCoef[i] = MULT_BP2(BP2_FROM_TR2(bp2Sin), pctCoef[i]);
                pctCoef[(iSizeCurr << 1) - 1 - i] = MULT_BP2(BP2_FROM_TR2(bp2Sin), pctCoef[(iSizeCurr << 1) - 1 - i]);
                TR2_RECURR_INC(bp2Cos1, bp2Sin1, bp2Cos, bp2Sin,bp2Step);
                /*
                bp2Sin1 = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
                bp2Cos1 = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
                */
                pctCoef[i + 1] = MULT_BP2(BP2_FROM_TR2(bp2Sin1), pctCoef[i + 1]);
                pctCoef[(iSizeCurr << 1) - 2 - i] = MULT_BP2(BP2_FROM_TR2(bp2Sin1), pctCoef[(iSizeCurr << 1) - 2 - i]);
                /*
                bp2Sin = bp2Sin + MULT_TR2(bp2Step,bp2Cos1);
                bp2Cos = bp2Cos - MULT_TR2(bp2Step,bp2Sin1);
                */
                TR2_RECURR_INC(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1,bp2Step);
             }
        }
    }
    else
    {
        // region 1 -- # of points = iSizeCurr/2-iPrevOverlap
        j = iSizeCurr / 2 - iPrevOverlap;
        for (i = 0; i < j; i++)
        {
            pctCoef[i] = 0;
        }

        // regions 2 & 3 -- # of points = 2*iPrevOverlap, rising window
        // Same as (iPrevOverlap == 64 || iPrevOverlap == 128) since iPrevOverlap is power of 2
        if (iPrevOverlap & ( 64 | 128))
        {
            pbp2Window = (iPrevOverlap == 64) ? g_bp2SinLUT128 : g_bp2SinLUT256;
#if !defined(WMA_OPT_APPLYWINDOW_ARM) || !WMA_OPT_APPLYWINDOW_ARM
            j = iSizeCurr / 2 + iPrevOverlap;
            for (; i < j; i++)
            {
                pctCoef[i] = MULT_BP2(*pbp2Window++, pctCoef[i]);
            }
#else
            assert((iPrevOverlap & 1) == 0); // 2 * iPrevOverlap is multiple of 4 assumed in ASM
            auApplyWindowLoop_LUT_Forward(&pctCoef[i], pbp2Window, iPrevOverlap << 1);
#endif
        }
        else if (iPrevOverlap)
        {
            assert(SINCOSTABLE_ENTRIES > (iPrevOverlap >> 6));
            pSinCosTable = rgSinCosTables[iPrevOverlap >> 6];

            // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
            bp2Sin   =  TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
            bp2Cos   =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
            // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
            bp2Sin1  = -bp2Sin;
            bp2Cos1  =  bp2Cos;
            // STEP = 2*sin(PI/2/iSizeCurr)
            bp2Step  = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));

            j = iSizeCurr / 2 + iPrevOverlap;
            for (; i < j; i += 2)
            {
                pctCoef[i] = MULT_BP2(BP2_FROM_TR2(bp2Sin), pctCoef[i]);
                TR2_RECURR_INC(bp2Cos1, bp2Sin1, bp2Cos, bp2Sin, bp2Step);
                /*
                bp2Sin1 = bp2Sin1 + MULT_TR2(bp2Step, bp2Cos);
                bp2Cos1 = bp2Cos1 - MULT_TR2(bp2Step, bp2Sin);
                */
                pctCoef[i + 1] = MULT_BP2(BP2_FROM_TR2(bp2Sin1), pctCoef[i + 1]);
                TR2_RECURR_INC(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
                /*
                bp2Sin = bp2Sin + MULT_TR2(bp2Step, bp2Cos1);
                bp2Cos = bp2Cos - MULT_TR2(bp2Step, bp2Sin1);
                */
            }
        }

        // region 4 (flat 1's -- nothing to do)
        // # of points = (iSizeCurr/2-iPrevOverlap)+(iSizeCurr/2-iNextOverlap)
        i = 3 * iSizeCurr / 2 - iNextOverlap;

        // region 5 & 6 -- # of points = 2*iNextOverlap, falling window
        // Same as (iNextOverlap == 64 || iNextOverlap == 128) since iNextOverlap is power of 2
        if (iNextOverlap & ( 64 | 128))
        {
            pbp2Window = (iNextOverlap == 64) ? (g_bp2SinLUT128 + 127): (g_bp2SinLUT256 + 255);
#if !defined(WMA_OPT_APPLYWINDOW_ARM) || !WMA_OPT_APPLYWINDOW_ARM
            j = 3 * iSizeCurr / 2 + iNextOverlap;
            for (; i < j; i++)
            {
                pctCoef[i] = MULT_BP2(*pbp2Window--, pctCoef[i]);
            }
#else
            assert((iNextOverlap & 1) == 0); // 2 * iNextOverlap is multiple of 4 assumed in ASM
            auApplyWindowLoop_LUT_Reverse(&pctCoef[i], pbp2Window, iNextOverlap << 1);
            i = 3 * iSizeCurr / 2 + iNextOverlap;
#endif
        }
        else if (iNextOverlap)
        {
            assert(SINCOSTABLE_ENTRIES > (iNextOverlap >> 6));
            pSinCosTable = rgSinCosTables[iNextOverlap >> 6];

            bp2Sin   =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
            bp2Cos   = -TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
            bp2Sin1  =  bp2Sin;
            bp2Cos1  = -bp2Cos;
            bp2Step  =  TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));

            j = 3 * iSizeCurr / 2 + iNextOverlap;
            for (; i < j; i += 2)
            {
                pctCoef[i] = MULT_BP2(BP2_FROM_TR2(bp2Sin), pctCoef[i]);
                TR2_RECURR_INC(bp2Cos1, bp2Sin1, bp2Cos, bp2Sin, bp2Step);
                /*
                bp2Sin1 = bp2Sin1 + MULT_TR2(bp2Step, bp2Cos);
                bp2Cos1 = bp2Cos1 - MULT_TR2(bp2Step, bp2Sin);
                */
                pctCoef[i + 1] = MULT_BP2(BP2_FROM_TR2(bp2Sin1), pctCoef[i + 1]);
                TR2_RECURR_INC(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
                /*
                bp2Sin = bp2Sin + MULT_TR2(bp2Step, bp2Cos1);
                bp2Cos = bp2Cos - MULT_TR2(bp2Step, bp2Sin1);
                */
            }
        }

        // region 7 -- # of points = iSizeCurr/2-iNextOverlap, falling window
        j = iSizeCurr << 1;
        for (; i < j; i++)
        {
            pctCoef[i] = 0;
        }
    }
}

#       else // so !APPLYWINDOW_C_OPT
Void auApplyWindow(CAudioObject *pau, CoefType *pctCoef,
                     Int iSizePrev, Int iSizeCurr, Int iSizeNext, Bool fBase)
{
    Int i;
    Int iPrevOverlap, iNextOverlap;
    const SinCosTable *pSinCosTable;

    TR2_TYPE bp2Sin, bp2Cos;
    TR2_TYPE bp2Sin1, bp2Cos1;
    /*
#if !defined(WMA_OPT_APPLYWINDOW_ARM) || !WMA_OPT_APPLYWINDOW_ARM
    TR2_TYPE bp2SinTemp, bp2CosTemp;
#endif
    */
    TR2_TYPE bp2Step;
    CoefType* top;

    if (fBase)
    {
        I16 iQ1, iQ2, iQ3, iQ4;
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr, &iQ1, &iQ2);
        iPrevOverlap = (iQ2 - iQ1) / 2;
        prvCalcQ3Q4(pau, WMAB_TRUE, (I16)iSizeCurr, (I16)iSizeNext, (I16)iSizeCurr, &iQ3, &iQ4);
        iNextOverlap = (iQ4 - iQ3) / 2;
    }
    else
    {
        iPrevOverlap = min(iSizePrev, iSizeCurr) / 2;
        iNextOverlap = min(iSizeCurr, iSizeNext) / 2;
    }

    // region 1 -- # of points = iSizeCurr/2-iPrevOverlap
    for (i=0; i < iSizeCurr/2-iPrevOverlap; i++)
    {
        pctCoef[i] = 0;
    }

    assert( SINCOSTABLE_ENTRIES > (iPrevOverlap>>6) );
    pSinCosTable = rgSinCosTables[ iPrevOverlap>>6 ];

    // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
    bp2Sin   =  TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2Cos   =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
    bp2Sin1  = -TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2Cos1  =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    // STEP = 2*sin(PI/2/iSizeCurr)
    bp2Step  = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));

#if !defined(WMA_OPT_APPLYWINDOW_ARM) || !WMA_OPT_APPLYWINDOW_ARM
    // regions 2 & 3 -- # of points = 2*iPrevOverlap, rising window
    for (top = pctCoef + iSizeCurr/2+iPrevOverlap-1; i < iSizeCurr/2; i++, top-- )
    {
        pctCoef[i] = MULT_BP2(BP2_FROM_TR2(bp2Sin), pctCoef[i]);
        top[0] = MULT_BP2(BP2_FROM_TR2(bp2Cos), top[0]);

        TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
        /*
        bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
        bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
        bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
        bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
        */
    }
#else   // WMA_OPT_APPLYWINDOW_ARM
    auApplyWindowLoop(&pctCoef[i], BP2_FROM_TR2(bp2Sin), BP2_FROM_TR2(bp2Cos), BP2_FROM_TR2(bp2Sin1), BP2_FROM_TR2(bp2Cos1), BP2_FROM_TR2(bp2Step), iSizeCurr/2+iPrevOverlap-i);
#endif  // WMA_OPT_APPLYWINDOW_ARM

    // region 4 (flat 1's -- nothing to do)
    // # of points = (iSizeCurr/2-iPrevOverlap)+(iSizeCurr/2-iNextOverlap)
    i = 3*iSizeCurr/2-iNextOverlap;

    assert( SINCOSTABLE_ENTRIES > (iNextOverlap>>6) );
    pSinCosTable = rgSinCosTables[ iNextOverlap>>6 ];

    bp2Sin   =  TR2_FROM_BP1 ( pSinCosTable->cos_PIby4cSB );
    bp2Cos   = -TR2_FROM_BP1 ( pSinCosTable->sin_PIby4cSB );
    bp2Sin1  =  TR2_FROM_BP1 ( pSinCosTable->cos_PIby4cSB );
    bp2Cos1  =  TR2_FROM_BP1 ( pSinCosTable->sin_PIby4cSB );
    bp2Step  =  TR2_FROM_BP2(SINSTEP_SCALE( pSinCosTable->sin_PIby2cSB ));

#if !defined(WMA_OPT_APPLYWINDOW_ARM) || !WMA_OPT_APPLYWINDOW_ARM
    // region 5 & 6 -- # of points = 2*iNextOverlap, falling window
    for (top = pctCoef + 3*iSizeCurr/2 + iNextOverlap - 1; i < 3*iSizeCurr/2; i++, top-- )
    {
        pctCoef[i] = MULT_BP2(BP2_FROM_TR2(bp2Sin), pctCoef[i]);
        top[0] = -MULT_BP2(BP2_FROM_TR2(bp2Cos), top[0]);

        TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
        /*
        bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
        bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
        bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
        bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
        */
    }
#else   // WMA_OPT_APPLYWINDOW_ARM
    auApplyWindowLoop(&pctCoef[i], BP2_FROM_TR2(bp2Sin), BP2_FROM_TR2(bp2Cos), BP2_FROM_TR2(bp2Sin1), BP2_FROM_TR2(bp2Cos1), BP2_FROM_TR2(bp2Step), 3*iSizeCurr/2+iNextOverlap-i);
    i = 3*iSizeCurr/2+iNextOverlap;
#endif  // WMA_OPT_APPLYWINDOW_ARM

    // region 7 -- # of points = iSizeCurr/2-iNextOverlap, falling window
    for (i = 3*iSizeCurr/2+iNextOverlap; i < 2*iSizeCurr; i++)
    {
        pctCoef[i] = 0;
    }
}
#       endif // !APPLYWINDOW_C_OPT
#   else // so !BUILD_INTEGER && !DISABLE_OPT && !WMA_TARGET_X86

// auApplyWindow() steps forward 4 elements at a time under BUILD_INTFLOAT.
// this is an SSE-friendly version, which is prepared for vector implementation.
// SSE version of this function is located in x86.c
// fBase: base layer of baseplus layer
Void auApplyWindow(CAudioObject *pau, CoefType *pctCoef, 
    Int iSizePrev, Int iSizeCurr, Int iSizeNext, Bool fBase)
{
    Int i;
    Int iPrevOverlap, iNextOverlap;
    const SinCosTable *pSinCosTable;

    BP2Type vSin[4], vCos[4], vSin1[4], vCos1[4], vSTmp[4], vCTmp[4];
    
    TR2_TYPE bp2Sin, bp2Cos;
    TR2_TYPE bp2Sin1, bp2Cos1;
    TR2_TYPE bp2SinTemp, bp2CosTemp;
    TR2_TYPE bp2Step, bp2Step4;

    if (fBase)
    {
        I16 iQ1, iQ2, iQ3, iQ4;
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr, &iQ1, &iQ2);
        iPrevOverlap = (iQ2 - iQ1) / 2;
        prvCalcQ3Q4(pau, WMAB_TRUE, (I16)iSizeCurr, (I16)iSizeNext, (I16)iSizeCurr, &iQ3, &iQ4);
        iNextOverlap = (iQ4 - iQ3) / 2;
    }
    else
    {
        iPrevOverlap = min(iSizePrev, iSizeCurr) / 2;
        iNextOverlap = min(iSizeCurr, iSizeNext) / 2;
    }

    // region 1 -- # of points = iSizeCurr/2-iPrevOverlap
    for (i=0; i < iSizeCurr/2-iPrevOverlap; i++)
    {
        pctCoef[i] = 0;
    }

    assert( SINCOSTABLE_ENTRIES > (iPrevOverlap>>6) );
    pSinCosTable = rgSinCosTables[ iPrevOverlap>>6 ];

    bp2Sin   =  TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2Cos   =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    bp2Sin1  = -TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2Cos1  =  TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    bp2Step  =  TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));
    bp2Step4 =  TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_2PIbycSB));

    // compute the first 4 sin/cos points one at
    // a time, and then step forward 4 at a time.

    vSin[0] = BP2_FROM_TR2(bp2Sin); vCos[0] = BP2_FROM_TR2(bp2Cos);

    bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,TR2_FROM_BP2(vCos[0]));
    bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,TR2_FROM_BP2(vSin[0]));
    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;

    vSin[1] = BP2_FROM_TR2(bp2Sin); vCos[1] = BP2_FROM_TR2(bp2Cos);

    TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
    /*
    bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
    bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
    */

    vSin[2] = BP2_FROM_TR2(bp2Sin); vCos[2] = BP2_FROM_TR2(bp2Cos);

    TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
    /*
    bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
    bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
    */

    vSin[3] = BP2_FROM_TR2(bp2Sin); vCos[3] = BP2_FROM_TR2(bp2Cos);

    vSin1[0] = -vSin[3];    vSin1[1] = -vSin[2];
    vSin1[2] = -vSin[1];    vSin1[3] = -vSin[0];

    vCos1[0] =  vCos[3];    vCos1[1] =  vCos[2];
    vCos1[2] =  vCos[1];    vCos1[3] =  vCos[0];

    assert( 0 == i%4 && 0 == (iSizeCurr/2+iPrevOverlap)%4 );

    // regions 2 & 3 -- # of points = 2*iPrevOverlap, rising window
  
    for (; i < iSizeCurr/2+iPrevOverlap; i += 4 )
    {
        Int j = 0;

        pctCoef[i+0] = MULT_BP2(vSin[0], pctCoef[i+0]);
        pctCoef[i+1] = MULT_BP2(vSin[1], pctCoef[i+1]);
        pctCoef[i+2] = MULT_BP2(vSin[2], pctCoef[i+2]);
        pctCoef[i+3] = MULT_BP2(vSin[3], pctCoef[i+3]);

        vSTmp[0] = vSin1[0] + MULT_BP2(BP2_FROM_TR2(bp2Step4),vCos[0]);
        vSTmp[1] = vSin1[1] + MULT_BP2(BP2_FROM_TR2(bp2Step4),vCos[1]);
        vSTmp[2] = vSin1[2] + MULT_BP2(BP2_FROM_TR2(bp2Step4),vCos[2]);
        vSTmp[3] = vSin1[3] + MULT_BP2(BP2_FROM_TR2(bp2Step4),vCos[3]);

        vCTmp[0] = vCos1[0] - MULT_BP2(BP2_FROM_TR2(bp2Step4),vSin[0]);
        vCTmp[1] = vCos1[1] - MULT_BP2(BP2_FROM_TR2(bp2Step4),vSin[1]);
        vCTmp[2] = vCos1[2] - MULT_BP2(BP2_FROM_TR2(bp2Step4),vSin[2]);
        vCTmp[3] = vCos1[3] - MULT_BP2(BP2_FROM_TR2(bp2Step4),vSin[3]);

        vSin1[0] = vSin[0]; vSin[0] = vSTmp[0];
        vSin1[1] = vSin[1]; vSin[1] = vSTmp[1];
        vSin1[2] = vSin[2]; vSin[2] = vSTmp[2];
        vSin1[3] = vSin[3]; vSin[3] = vSTmp[3];

        vCos1[0] = vCos[0]; vCos[0] = vCTmp[0];
        vCos1[1] = vCos[1]; vCos[1] = vCTmp[1];
        vCos1[2] = vCos[2]; vCos[2] = vCTmp[2];
        vCos1[3] = vCos[3]; vCos[3] = vCTmp[3];
    }

    // region 4 (flat 1's -- nothing to do)
    // # of points = (iSizeCurr/2-iPrevOverlap)+(iSizeCurr/2-iNextOverlap)
    i = 3*iSizeCurr/2-iNextOverlap;

    assert( SINCOSTABLE_ENTRIES > (iNextOverlap>>6) );
    pSinCosTable = rgSinCosTables[ iNextOverlap>>6 ];

    bp2Sin   =  TR2_FROM_BP1 ( pSinCosTable->cos_PIby4cSB );
    bp2Cos   = -TR2_FROM_BP1 ( pSinCosTable->sin_PIby4cSB );
    bp2Sin1  =  TR2_FROM_BP1 ( pSinCosTable->cos_PIby4cSB );
    bp2Cos1  =  TR2_FROM_BP1 ( pSinCosTable->sin_PIby4cSB );
    bp2Step  =  TR2_FROM_BP2(SINSTEP_SCALE( pSinCosTable->sin_PIby2cSB ));
    bp2Step4 =  TR2_FROM_BP2(SINSTEP_SCALE( pSinCosTable->sin_2PIbycSB ));

    vSin[0] = BP2_FROM_TR2(bp2Sin); vCos[0] = BP2_FROM_TR2(bp2Cos);
    
    TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
    /*
    bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
    bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
    */

    vSin[1] = BP2_FROM_TR2(bp2Sin); vCos[1] = BP2_FROM_TR2(bp2Cos);

    TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
    /*
    bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
    bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
    */

    vSin[2] = BP2_FROM_TR2(bp2Sin); vCos[2] = BP2_FROM_TR2(bp2Cos);

    TR2_RECURR_INC_UPDATE_PREV(bp2Cos, bp2Sin, bp2Cos1, bp2Sin1, bp2Step);
    /*
    bp2SinTemp = bp2Sin1 + MULT_TR2(bp2Step,bp2Cos);
    bp2CosTemp = bp2Cos1 - MULT_TR2(bp2Step,bp2Sin);
    bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
    bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
    */

    vSin[3] = BP2_FROM_TR2(bp2Sin); vCos[3] = BP2_FROM_TR2(bp2Cos);

    vSin1[0] =  vSin[3];    vSin1[1] =  vSin[2];
    vSin1[2] =  vSin[1];    vSin1[3] =  vSin[0];

    vCos1[0] = -vCos[3];    vCos1[1] = -vCos[2];
    vCos1[2] = -vCos[1];    vCos1[3] = -vCos[0];

    assert( 0 == i%4 && 0 == (3*iSizeCurr/2+iNextOverlap)%4 );

    // region 5 & 6 -- # of points = 2*iNextOverlap, falling window

    for (; i < 3*iSizeCurr/2+iNextOverlap; i += 4 )
    {
        Int j = 0;

        pctCoef[i+0] = MULT_TR2(vSin[0], pctCoef[i+0]);
        pctCoef[i+1] = MULT_TR2(vSin[1], pctCoef[i+1]);
        pctCoef[i+2] = MULT_TR2(vSin[2], pctCoef[i+2]);
        pctCoef[i+3] = MULT_TR2(vSin[3], pctCoef[i+3]);

        vSTmp[0] = vSin1[0] + MULT_TR2(BP2_FROM_TR2(bp2Step4),vCos[0]);
        vSTmp[1] = vSin1[1] + MULT_TR2(BP2_FROM_TR2(bp2Step4),vCos[1]);
        vSTmp[2] = vSin1[2] + MULT_TR2(BP2_FROM_TR2(bp2Step4),vCos[2]);
        vSTmp[3] = vSin1[3] + MULT_TR2(BP2_FROM_TR2(bp2Step4),vCos[3]);

        vCTmp[0] = vCos1[0] - MULT_TR2(BP2_FROM_TR2(bp2Step4),vSin[0]);
        vCTmp[1] = vCos1[1] - MULT_TR2(BP2_FROM_TR2(bp2Step4),vSin[1]);
        vCTmp[2] = vCos1[2] - MULT_TR2(BP2_FROM_TR2(bp2Step4),vSin[2]);
        vCTmp[3] = vCos1[3] - MULT_TR2(BP2_FROM_TR2(bp2Step4),vSin[3]);

        vSin1[0] = vSin[0]; vSin[0] = vSTmp[0];
        vSin1[1] = vSin[1]; vSin[1] = vSTmp[1];
        vSin1[2] = vSin[2]; vSin[2] = vSTmp[2];
        vSin1[3] = vSin[3]; vSin[3] = vSTmp[3];

        vCos1[0] = vCos[0]; vCos[0] = vCTmp[0];
        vCos1[1] = vCos[1]; vCos[1] = vCTmp[1];
        vCos1[2] = vCos[2]; vCos[2] = vCTmp[2];
        vCos1[3] = vCos[3]; vCos[3] = vCTmp[3];
    }

    // region 7 -- # of points = iSizeCurr/2-iNextOverlap, falling window
    for (; i < 2*iSizeCurr; i++)
    {
        pctCoef[i] = 0;
    }
}

#   endif // !BUILD_INTEGER && !DISABLE_OPT && !WMA_TARGET_X86

#endif //

#endif // defined (BUILD_WMASTD) || defined (BUILD_WMAPRO)


