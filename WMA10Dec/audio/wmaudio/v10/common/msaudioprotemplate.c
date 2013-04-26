//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Contains functions needed for WMA Pro. Not needed for WMA Std or Lossless.
//*@@@---@@@@******************************************************************

// reconstructs iSizePrev/2 + iSizeCurr/2 samples
// (2nd half of prev, 1st half of curr)
// hist contains 2nd half of prev samples (iSizePrev/2)
// new contains entire curr samples (iSizeCurr)
//
// hist points to something prev/2 back, new points to current

#if defined(AU_OVERLAPADDV3)
INLINE WMARESULT auOverlapAddV3tpl(CAudioObject *pau, CoefType *pctCoefOut,
						 CoefType *pctCoefHist, CoefType *pctCoefNew,
                         CoefType *pctCoefHistDST, CoefType *pctCoefNewDST,
                         Int iSizePrev, Int iSizeCurr,
                         Bool fBase)
{
    WMARESULT wmaResult = WMA_OK;
    Int iOverlap, iCoeff;
    TR2_TYPE bp2Sin, bp2Cos;
    TR2_TYPE bp2Sin1, bp2Cos1;
    TR2_TYPE bp2Step;
#if !((bUseMCLT==1) && (bUseDCT==1)) || (bDirectMCLT==1)
    CoefType ctPrevData;
#endif
#if (bDirectMCLT==0)
    CoefType ctCurrData;
#endif
    CoefType *pctOut, *pctOutBottom, *pctHist, *pctNew;
#if (bUseMCLT==1) && (bUseDCT==1) && (bDirectMCLT==0)
    CoefType *pctHist2;
#endif
#if (bDirectMCLT==1)
    CoefType *pctNew2;
#endif
#if (bUseMCLT==1)
#if (bUseDCT==0)||(bDirectMCLT==1)
    CoefType *pctHistDST;
#endif
#if (bDirectMCLT==0)
    CoefType *pctNewDST;
#endif
#if (bUseDCT==0) || (bDirectMCLT==1)
    CoefType ctPrevDataDST;
#endif
#if (bDirectMCLT==0)
    CoefType ctCurrDataDST;
#endif
#endif
    const SinCosTable *pSinCosTable;
    I16 iQ1, iQ2;

    // flip all the new coefficients
#if (bFlip==1)
    auFlipCoeff(pctCoefNew, iSizeCurr);
#if (bUseMCLT==1)
    auFlipCoeff(pctCoefNewDST, iSizeCurr);
#endif
#endif

    if (fBase)
    {
        prvCalcQ1Q2(pau, WMAB_TRUE, (I16)iSizePrev, (I16)iSizeCurr,
                         &iQ1, &iQ2);

        iOverlap = (iQ2 - iQ1)/2;
    }
    else
    {
        iOverlap = min(iSizePrev, iSizeCurr) / 2;
    }

#if ((bUseMCLT==1) && (bUseDCT==1))
    assert(iSizePrev == iSizeCurr);
#else

// flat part of 2nd half of prev
#if (bFlip==1)
    pctHist = pctCoefHist;
#if (bUseMCLT==1)
    pctHistDST = pctCoefHistDST;
#endif
#else
    pctHist = pctCoefHist + iSizePrev/2 - 1;
#if (bUseMCLT==1)
    pctHistDST = pctCoefHistDST + iSizePrev/2 - 1;
#endif
#endif
    pctOut = pctCoefOut;
    for (iCoeff=-iSizePrev/2; iCoeff < -iOverlap; iCoeff++)
    {
#if (bUseMCLT==1)
        *pctOut = (*pctHist + *pctHistDST)/2;
#else
        *pctOut = *pctHist;
#endif
        pctOut++;
#if (bFlip==1)
        pctHist++;
#if (bUseMCLT==1)
        pctHistDST++;
#endif
#else
        pctHist--;
#if (bUseMCLT==1)
        pctHistDST--;
#endif
#endif
    }

#endif//((bUseMCLT==1) && (bUseDCT==1))

    assert(((iOverlap >= 32 && iOverlap <= 4096) || iOverlap==0) &&
           CHECK_POWER_OF_TWO(iOverlap));

    pSinCosTable = rgSinCosTables[iOverlap>>6];

    // START = sin( PI/(4*cSB) ) and cos( PI/(4*cSB) )
    bp2Sin = TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2Cos = TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    // PRIOR should be sin(PI/(4*cSB) - PI/(2*cSB) ) = sin( -PI/(4*cSB) )
    bp2Sin1 = -TR2_FROM_BP1(pSinCosTable->sin_PIby4cSB);
    bp2Cos1 = TR2_FROM_BP1(pSinCosTable->cos_PIby4cSB);
    // STEP = 2*sin(PI/2/iSizeCurr)
    bp2Step = TR2_FROM_BP2(SINSTEP_SCALE(pSinCosTable->sin_PIby2cSB));

    // move history pointers to start of overlap region
    // move current pointers to end of overlap region
    // move destination pointers to start of overlap region for output
#if (bFlip==1)
    pctHist = pctCoefHist + iSizePrev/2 - iOverlap;
    pctNew = pctCoefNew + iOverlap - 1;
#if (bUseMCLT==1)
    pctHistDST = pctCoefHistDST + iSizePrev/2 - iOverlap;
    pctNewDST = pctCoefNewDST + iOverlap - 1;
#endif
#else
#if (bUseMCLT==1) && (bUseDCT==1) && (bDirectMCLT==0)
    pctHist = pctCoefHist; // history is in direct MCLT format
    pctHist2 = pctCoefHist + iSizeCurr - 1;
#else
    pctHist = pctCoefHist + iOverlap - 1;
#endif
#if bDirectMCLT==1
    pctNew = pctCoefNew;
    pctNew2 = pctCoefNew + iSizeCurr - 1;
#else
    pctNew = pctCoefNew + iSizeCurr - iOverlap;
#endif
#if (bUseMCLT==1)
#if (bUseDCT==0)||(bDirectMCLT==1)
    pctHistDST = pctCoefHistDST + iOverlap - 1;
#endif
#if (bDirectMCLT==0)
    pctNewDST = pctCoefNewDST + iSizeCurr - iOverlap;
#endif
#endif
#endif
    pctOut = pctCoefOut + iSizePrev/2 - iOverlap;
    pctOutBottom = pctOut + 2*iOverlap - 1;
    for (iCoeff=0; iCoeff < iOverlap; iCoeff++)
    {

#if defined(RECALC_R) || defined(RECALC)
        if (DORECALC_R(iCoeff))
        {
            bp2Sin = TR2_FROM_FLOAT(sin(PI*(2*iCoeff+1)/(8*iOverlap)));
            bp2Cos = TR2_FROM_FLOAT(cos(PI*(2*iCoeff+1)/(8*iOverlap)));
        }
#endif
#if !((bUseMCLT==1) && (bUseDCT==1)) || (bDirectMCLT==1)
        ctPrevData = *pctHist;
#endif
#if (bDirectMCLT==0)
        ctCurrData = *pctNew;
#endif
#if (bUseMCLT==1)
#if (bUseDCT==0) || (bDirectMCLT==1)
        ctPrevDataDST = *pctHistDST;
#endif
#if (bDirectMCLT==0)
        ctCurrDataDST = *pctNewDST;
#endif
#endif

#if defined(BUILD_INTEGER)
#if !((bUseMCLT==1) && (bUseDCT==1)) || (bDirectMCLT==1)
        assert( ctPrevData <= INT_MAX && ctPrevData >= INT_MIN );
#endif
#if (bDirectMCLT==0)
        assert( ctCurrData <= INT_MAX && ctCurrData >= INT_MIN );
#endif
#endif

        // MCLT
#if (bUseMCLT==1)
#if (bUseDCT==1)
#if (bDirectMCLT==1) // this frame direct MCLT, history DCT/DST style
        *pctOut =
            ( *pctNew + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctPrevData + ctPrevDataDST ) ) / 2;
        *pctOutBottom =
            (MULT_BP2( BP2_FROM_TR2(bp2Sin), ctPrevData - ctPrevDataDST ) + *pctNew2 ) / 2;
#else // this frame DST/DCT, history direct MCLT style
        *pctOut =
            (MULT_BP2(BP2_FROM_TR2(bp2Sin), ctCurrDataDST - ctCurrData) + *pctHist)/2;
        *pctOutBottom =
            (*pctHist2 + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctCurrData + ctCurrDataDST) ) / 2;
#endif
#else
        *pctOut =
            ( MULT_BP2(BP2_FROM_TR2(bp2Sin), ctCurrDataDST - ctCurrData ) + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctPrevData + ctPrevDataDST ) ) / 2;
        *pctOutBottom =
            (MULT_BP2( BP2_FROM_TR2(bp2Sin), ctPrevData - ctPrevDataDST ) + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctCurrData + ctCurrDataDST) ) / 2;
#endif
#elif (bUseDCT==1)
        // MLT = Real(MCLT)
        *pctOut =
            MULT_BP2(BP2_FROM_TR2(-bp2Sin), ctCurrData) + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctPrevData);
        *pctOutBottom =
            MULT_BP2( BP2_FROM_TR2(bp2Sin), ctPrevData) + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctCurrData);
#else
        // Imag(MCLT)
        *pctOut =
            MULT_BP2( BP2_FROM_TR2(bp2Sin), ctCurrData) + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctPrevData);
        *pctOutBottom =
            MULT_BP2(BP2_FROM_TR2(-bp2Sin), ctPrevData) + MULT_BP2(BP2_FROM_TR2(bp2Cos), ctCurrData);
#endif

#if (bFlip==1)
        pctHist++;
        pctNew--;
#if (bUseMCLT==1)
        pctHistDST++;
        pctNewDST--;
#endif
#else
#if (bUseMCLT==1) && (bUseDCT==1) && (bDirectMCLT==0)
        pctHist++;
        pctHist2--;
#else
        pctHist--;
#endif
        pctNew++;
#if (bUseMCLT==1)
#if (bDirectMCLT==1)
        pctNew2--;
#endif
#if (bUseDCT==0) || (bDirectMCLT==1)
        pctHistDST--;
#endif
#if (bDirectMCLT==0)
        pctNewDST++;
#endif
#endif
#endif
        pctOut++;
        pctOutBottom--;

        /* sin(a+b) = sin(a-b) + 2*sin(b)*cos(a) */
        /* cos(a+b) = cos(a-b) - 2*sin(b)*sin(a) */
        TR2_RECURR_INC_UPDATE_PREV(bp2Cos,bp2Sin,bp2Cos1,bp2Sin1,bp2Step);
        /*
        bp2SinTemp = bp2Sin1 + MULT_BP2(bp2Step,bp2Cos);
        bp2CosTemp = bp2Cos1 - MULT_BP2(bp2Step,bp2Sin);
        bp2Sin1 = bp2Sin;  bp2Sin = bp2SinTemp;
        bp2Cos1 = bp2Cos;  bp2Cos = bp2CosTemp;
        */
    }

#if (bDirectMCLT==0)

    // flat part of first half of cur
#if (bFlip==1)
    pctNew = pctCoefNew + iOverlap;
#if (bUseMCLT==1)
    pctNewDST = pctCoefNewDST + iOverlap;
#endif
#else
    pctNew = pctCoefNew + iSizeCurr - 1 - iOverlap;
#if (bUseMCLT==1)
    pctNewDST = pctCoefNewDST + iSizeCurr - 1 - iOverlap;
#endif
#endif
    pctOut = pctCoefOut + iSizePrev/2 + iOverlap;
    for (iCoeff=iOverlap; iCoeff < iSizeCurr/2; iCoeff++)
    {
#if (bUseMCLT==1)
        *pctOut = (*pctNew + *pctNewDST)/2;
#else
        *pctOut = *pctNew;
#endif

        pctOut++;

#if (bFlip==1)
        pctNew++;
#if (bUseMCLT==1)
        pctNewDST++;
#endif
#else
        pctNew--;
#if (bUseMCLT==1)
        pctNewDST--;
#endif
#endif
    }

#endif//(bDirectMCLT==0)

    return wmaResult;
}
#endif // AU_OVERLAPADDV3
