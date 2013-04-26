//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

// In integer build, ValType is alaways I32, DRCType is I32
// In float build, ValType is float for drcDecodeBlockCoeff

// For WMA Lsl
#ifdef DRC_DECODE_LSL

#undef drcDecodeBlock
#undef ValType
#undef VAL_INT
#undef BufType
#undef rgpbTemp
#undef VAL_TO_DRCT

#define drcDecodeBlock drcDecodeBlockLsl
#define ValType I32
#define VAL_INT 1
#define BufType CBT
#define rgpbTemp m_ppcbtTemp
#define VAL_TO_DRCT(val) ((DRCType)(val))

#endif // DRC_DECODE_LSL

// For WMA Pro
#ifdef DRC_DECODE_PRO

#undef drcDecodeBlock
#undef ValType
#undef BufType
#undef rgpbTemp
#undef VAL_TO_DRCT
#undef VAL_INT

#define drcDecodeBlock drcDecodeBlockPro
#ifdef BUILD_INTEGER
#define ValType I32
#define VAL_INT 1
#define VAL_TO_DRCT(val) ((DRCType)(val))
#else
#define ValType Float
#define VAL_INT 0
#ifdef DRC_BUILD_INTEGER_TABLE
#define VAL_TO_DRCT(val) ((DRCType)ROUNDF(val))
#else
#define VAL_TO_DRCT(val) ((DRCType)(val))
#endif
#endif
#define BufType CoefType
#define rgpbTemp m_rgpctTemp

#endif // DRC_DECODE_PRO

#define THRESH (0.92f)
//#define OLD_DRC
// #define PRINT_SCALE_FACTORS
#define NEW_DRC_CODE 

#if defined(NEW_DRC_CODE) && defined(OLD_DRC)
#error "NEW_DRC_CODE and OLD_DRC cannot be defined together !!!"
#endif
WMARESULT drcDecodeBlock(DRC *p,
                         CAudioObjectDecoder *paudec,
                         U8 quantScaleFactor,
                         Int nDRCSetting,
                         Int cSamples)
{
  WMARESULT wr = WMA_OK;
  CAudioObject *pau = p->m_pau;
  Int iCh, iRecon, iLo, iMid, iHi, iBlock, iMidBits;
  DRCType scaleFactor, sampleScaleFactor, curScaleFactor, slopeScaleFactor;
  DRCType prevScaleFactor;
  ValType chPower, maxChPower, absVal;
#ifdef BUILD_INTEGER
  DRCType actScaleFactor;
#else
  Float actScaleFactor;
#endif
  DRCType sampleVal;
  Int nDRCPos=0;
#define MAX_DRC_BLOCKS (16)
  Int iBlocks;
#ifndef OLD_DRC
  Int iBlockBoundary[MAX_DRC_BLOCKS+1];
#endif
  Int cBlockSize, cChannel;
  BufType *pbt;
  // BufType maxVal = 0;
#if 0
  BufType btMaxSampleVal;
#endif
  Int cLeftShift;
#ifdef DRC_BUILD_INTEGER_TABLE
  Int iSlopeShiftBits;
#endif
  DRCType maxPeakValDec;
#ifdef NEW_DRC_CODE
  ValType maxInputInThisBlock,  // peak input value in current block
          maxInputVal;          // Given a scale factor, the peak input value that will not cause clipping
  DRCType sampleScaleFactorSaved;
#endif
#ifdef PRINT_SCALE_FACTORS
  static int count = 0;
#endif

  switch (nDRCSetting) {
    case WMA_DRC_HIGH: if (paudec->m_fChannelFoldDown == WMAB_FALSE || 
                           pau->m_bPureLosslessMode == WMAB_TRUE) goto exit;
                       if (paudec->m_fltChannelFoldDownGain == 1.0F) goto exit; // If WMA_DRC_HIGH, the only gain to be applied is 
                                                                                // m_fltChannelFoldDownGain. If this gain is 1.0, there is
                                                                                // nothing to be done.
                       break; 
    case WMA_DRC_MED:  nDRCPos = WMA_DRC_MED_POS; break; 
    case WMA_DRC_LOW:  nDRCPos = WMA_DRC_LOW_POS; break;
    default: assert(false);  wr = WMA_E_INVALIDARG;  goto exit;
  }

  if (!p->m_opt.m_fNormalizeRms && !p->m_opt.m_fDRC && !paudec->m_fChannelFoldDown) goto exit;

  if (!p->m_opt.m_fDRC) {
    scaleFactor = (DRCType)FLOAT_TO_DRCSCALE(1.0f);
  } else {
#ifdef DRC_DECODE_USE_TABLES
    scaleFactor = g_drcIndexToSF[quantScaleFactor];
#else
    scaleFactor = unquantScaleFactor(p, quantScaleFactor);
#endif
  }

// decode on subframe level -- before overlap/add
//#define DRC_SUBFRAME
#ifdef DRC_SUBFRAME
  {
    Int iChSrc;
    PerChannelInfo *ppcinfo;

    cBlockSize = pau->m_rgpcinfo[pau->m_rgiChInTile[0]].m_cSubbandAdjusted;
    cChannel = pau->m_cChInTile;
    for (iCh=0; iCh < pau->m_cChInTile; iCh++) {
      iChSrc = pau->m_rgiChInTile[iCh];
      ppcinfo = pau->m_rgpcinfo + iChSrc;
      paudec->m_rgpctTemp[iCh] = (CoefType*)ppcinfo->m_rgiCoefRecon;
    }
  }
#else
  cBlockSize = cSamples;
  cChannel = p->m_nChannels;
  for (iCh=0; iCh < cChannel; iCh++) {
    paudec->rgpbTemp[iCh] = (BufType*)pau->m_rgpcinfo[iCh].m_rgiPCMBuffer;
  }
#endif

#ifdef OLD_DRC
  iBlocks = cSamples;
#else
  iBlocks = (cSamples/256);
  iBlocks = checkRange(iBlocks, 2, MAX_DRC_BLOCKS);
  for (iBlock=0; iBlock <= iBlocks; iBlock++) {
    iBlockBoundary[iBlock] = (iBlock*cBlockSize)/iBlocks;
  }
#endif

#if 0
#if (VAL_INT==1)
  if (p->m_amtToLeftShift > 0)
    btMaxSampleVal = (BufType)p->m_maxPeakValDec[nDRCPos]>>p->m_amtToLeftShift;
  else if (p->m_amtToLeftShift < 0)
    btMaxSampleVal = (BufType)p->m_maxPeakValDec[nDRCPos]<<-p->m_amtToLeftShift;
#else
  btMaxSampleVal = (BufType)p->m_maxPeakValDec[nDRCPos]/p->m_amtToScale;
#endif
#endif

  for (iBlock=0; iBlock < iBlocks; iBlock++) {

#ifdef OLD_DRC
    iLo = iBlock;
    iHi = iBlock + 1;
#else
    iLo = iBlockBoundary[iBlock];
    iHi = iBlockBoundary[iBlock+1];
#endif

    maxChPower = 0;
    // maxVal = 0;
    // find average power in subframe
    for (iCh=0; iCh < cChannel; iCh++) {
      chPower = (ValType)0;
      pbt = &paudec->rgpbTemp[iCh][iLo];
      for (iRecon=iLo; iRecon < iHi; iRecon++, pbt++) {
#if defined(COEF64BIT)
        assert(ABS(*pbt) < ((I64)1<<31));
#endif
        absVal = ABS((ValType)*pbt);
        if (absVal > chPower) chPower = absVal;
      }
      if (chPower > maxChPower) maxChPower = chPower;
    }

#if defined(BUILD_INTEGER) && defined(DRC_SUBFRAME)
    cLeftShift = p->m_amtToLeftShift - pau->m_cLeftShiftBitsFixedPost;
#else
    cLeftShift = p->m_amtToLeftShift;
#endif
#ifdef NEW_DRC_CODE
    maxInputInThisBlock = maxChPower;  // save this value before scaling maxChPower...
#endif
#if (VAL_INT==1)
    if (cLeftShift > 0)
      maxChPower = maxChPower<<cLeftShift;
    else if (cLeftShift < 0)
      maxChPower = maxChPower>>-cLeftShift;
#else
    maxChPower *= p->m_amtToScale;
#endif

    sampleVal = min(VAL_TO_DRCT(maxChPower), MAX_INT24SAMPLE);

#if 0
    {
      static int count = 1;
      count++;
    }
#endif

    if (nDRCSetting != WMA_DRC_HIGH) 
    {
        if (p->m_opt.m_fNormalizeRms && p->m_fNeedDRCOnNormalize[nDRCPos]) {
          sampleScaleFactor =
            MULT_DRCSCALE(scaleFactor, drcGetScaleFactorFTable(p,
              MULT_DRCSCALE((DRCType)sampleVal, scaleFactor), nDRCPos));
          maxPeakValDec = p->m_maxPeakValDec[nDRCPos];
        } else {
          if (p->m_opt.m_fNormalizeRms) {
            sampleScaleFactor =
              MULT_DRCSCALE(scaleFactor, p->m_scaleFactor[nDRCPos]);
            maxPeakValDec = p->m_maxPeakValDec[nDRCPos];
          } else {
            sampleScaleFactor = scaleFactor;
            maxPeakValDec = MAX_PEAKVAL;
          }
        }
    }
    else
    {
        sampleScaleFactor = (DRCType)FLOAT_TO_DRCSCALE(1.0F);
        maxPeakValDec = MAX_PEAKVAL;
    }
  
    if (paudec->m_fChannelFoldDown &&
      pau->m_bPureLosslessMode == WMAB_FALSE)
    {
      sampleScaleFactor = MULT_DRCSCALE(sampleScaleFactor, (DRCType)FLOAT_TO_DRCSCALE(paudec->m_fltChannelFoldDownGain));
    }

#undef CUR_SC_FACTOR
#if defined(DRC_BUILD_INTEGER_TABLE)
#  ifdef BUILD_INTEGER
#    define CUR_SC_FACTOR(sc) ((sc)>>iSlopeShiftBits)
#    define CUR_SC_FACTOR2(sc) (sc)
#    define DRC_SCALE (1.0f)
#  else // BUILD_INTEGER
#    define CUR_SC_FACTOR(sc) ((Float)((sc)>>iSlopeShiftBits)*DRC_SCALE)
#    define CUR_SC_FACTOR2(sc) ((Float)(sc)*DRC_SCALE)
#    define DRC_SCALE (1.0f/(1<<DRC_SCALE_BITS))
#  endif // BUILD_INTEGER
#else // DRC_BUILD_INTEGER_TABLE
#  define CUR_SC_FACTOR(sc) (sc)
#  define CUR_SC_FACTOR2(sc) (sc)
#  define DRC_SCALE (1.0f)
#endif // DRC_BUILD_INTEGER_TABLE

#undef MULT_SC
#ifdef BUILD_INTEGER
#define MULT_SC(coeff, sc) MULT_DRCSCALE((DRCType)(coeff), sc)
#else // BUILD_INTEGER
#ifdef DRC_DECODE_LSL
#define MULT_SC(coeff, sc) (ROUNDF((coeff)*(sc)))
#else // DRC_DECODE_LSL
#define MULT_SC(coeff, sc) ((coeff)*(sc))
#endif // DRC_DECODE_LSL
#endif // BUILD_INTEGER

#undef DIV_SC
#ifdef BUILD_INTEGER
#define DIV_SC(coeff, sc) DIV_DRCSCALE((DRCType)(coeff), sc)
#else // BUILD_INTEGER
#ifdef DRC_DECODE_LSL
#define DIV_SC(coeff, sc) ((sc) > 1 ? ROUNDF((coeff)/(sc)) : coeff)
#else // DRC_DECODE_LSL
#define DIV_SC(coeff, sc) ((sc) > 1 ? (coeff)/(sc) : coeff)
#endif // DRC_DECODE_LSL
#endif // BUILD_INTEGER

    prevScaleFactor = p->m_curScaleFactor;

#if defined(OLD_DRC)
    sampleScaleFactor = drcSmoothGain(p, sampleScaleFactor,
                                      VAL_TO_DRCT(maxChPower),
                                      maxPeakValDec);
#endif

#if 1
    sampleScaleFactorSaved = sampleScaleFactor;
    sampleScaleFactor = drcSmoothGain2(p, sampleScaleFactor,
                                       VAL_TO_DRCT(maxChPower),
                                       maxPeakValDec,
                                       iHi-iLo);
#ifdef NEW_DRC_CODE
    // Compute the highest input value that will cause clipping, given this scale factor
    maxInputVal = DIV_SC((maxPeakValDec - 2), CUR_SC_FACTOR2( sampleScaleFactor));
    
    // scale this maxInputVal down...
#if (VAL_INT==1)
    if (cLeftShift > 0)
      maxInputVal = maxInputVal>>cLeftShift;
    else if (cLeftShift < 0)
      maxInputVal = maxInputVal<<-cLeftShift;
#else
    maxInputVal /= p->m_amtToScale;
#endif
#endif
#endif

    // if attack time is 0, will never need clip since attack time of 0
    // means instant gain reduction.
    // of course if maxChPower is not max, but actually some other norm
    // then we can still get overflow -- but check is still pointless.
    // we can also get overflow from blending, so check for this
#if 0 && !defined(OLD_DRC)
    if (MULT_SC(maxChPower, CUR_SC_FACTOR2(prevScaleFactor)) >
        maxPeakValDec) {
      prevScaleFactor = DIV_LEVEL_TO_SCALE64(maxPeakValDec,
                                             VAL_TO_DRCT(maxChPower));
      prevScaleFactor = max(prevScaleFactor, sampleScaleFactor);
    }
#endif

    // hit new scale factor in approx. 50% of time
    iMid = (iHi-iLo)>>2;
    if (iMid != 0) {
      iMidBits = LOG2(iMid);
      iMid = (1<<iMidBits);
    } else {
      iMidBits = 0;
    }
#if 1 || defined(OLD_DRC) // no blending of scale factors
    iMid = 0;
    iMidBits = 0;
#endif

#if defined(DRC_BUILD_INTEGER_TABLE)
    {
      DRCType maxFactor = max(sampleScaleFactor, prevScaleFactor);
      maxFactor = max(maxFactor, 2);
      iSlopeShiftBits = 30-LOG2(maxFactor-1)-1;
    }
    iSlopeShiftBits = max(iSlopeShiftBits, 0);
    slopeScaleFactor =
      ((sampleScaleFactor-prevScaleFactor)<<iSlopeShiftBits)>>iMidBits;
#else // DRC_BUILD_INTEGER_TABLE
    slopeScaleFactor = (sampleScaleFactor-prevScaleFactor)/iMid;
#endif // DRC_BUILD_INTEGER_TABLE

    //printf("%f\n", (Float)sampleScaleFactor*DRC_SCALE);

    actScaleFactor = CUR_SC_FACTOR2(sampleScaleFactor);

#if 0
    {
      static int count = 1;
      printf("%d %d %d %d %f\n", count, (Int)maxChPower, (Int)scaleFactor, (Int)sampleScaleFactor, (float)sampleScaleFactor/(1<<DRC_SCALE_BITS));
      count++;
    }
#endif

    // now apply to all coeffs in block
    iMid += iLo;

#ifndef NEW_DRC_CODE
    for (iCh=0; iCh < cChannel; iCh++) {
      pbt = &paudec->rgpbTemp[iCh][iLo];
#ifdef DRC_BUILD_INTEGER_TABLE
      curScaleFactor = prevScaleFactor<<iSlopeShiftBits;
#else
      curScaleFactor = prevScaleFactor;
#endif
      for (iRecon=iLo; iRecon < iMid; iRecon++, pbt++) {
        curScaleFactor += slopeScaleFactor;
        *pbt = MULT_SC(*pbt, CUR_SC_FACTOR(curScaleFactor));
        absVal = ABS((ValType)*pbt);
        if (absVal > maxVal) maxVal = absVal;
#if 0
        if (*pbt >= btMaxSampleVal || *pbt <= -btMaxSampleVal)
          *pbt = checkRange(*pbt, -btMaxSampleVal, btMaxSampleVal);
#endif
        //if (iCh==0) printf("%f\n", DRCSCALE_TO_FLOAT(curScaleFactor>>iSlopeShiftBits));
#ifdef PRINT_SCALE_FACTORS
      if (iCh == 0) printf("%d, %0.12f, %0.12f\n", ++count, paudec->m_fltChannelFoldDownGain, CUR_SC_FACTOR(curScaleFactor));
#endif
      }
      for (; iRecon < iHi; iRecon++, pbt++) {
        *pbt = MULT_SC(*pbt, actScaleFactor);
        absVal = ABS((ValType)*pbt);
        if (absVal > maxVal) maxVal = absVal;
#if 0
        if (*pbt >= btMaxSampleVal || *pbt <= -btMaxSampleVal)
          *pbt = checkRange(*pbt, -btMaxSampleVal, btMaxSampleVal);
#endif
        //if (iCh==0) printf("%f\n", DRCSCALE_TO_FLOAT(sampleScaleFactor));
#ifdef PRINT_SCALE_FACTORS
      if (iCh == 0) printf("%d, %0.12f, %0.12f\n", ++count, paudec->m_fltChannelFoldDownGain, actScaleFactor);
#endif
      }
    }
#else // ifdef NEW_DRC_CODE
    if (maxInputInThisBlock > maxInputVal) // There are samples in this block that will clip
    {
        for (iRecon=iLo; iRecon < iHi; iRecon++) 
        {
            // Get the peak value from all channels
            absVal = 0;
            for (iCh=0; iCh < cChannel; iCh++)
            {
                const ValType absValTemp = ABS((ValType)paudec->rgpbTemp[iCh][iRecon]);
                if (absValTemp > absVal) absVal = absValTemp;
            }

            if (absVal >= maxInputVal)
            {
                // This sample is going to clip, so reduce the gain here

#if (VAL_INT==1)
                if (cLeftShift > 0)
                    absVal = absVal<<cLeftShift;
                else if (cLeftShift < 0)
                    absVal = absVal>>-cLeftShift;
#else
                absVal *= p->m_amtToScale;
#endif
                sampleScaleFactor = drcSmoothGain(p, sampleScaleFactorSaved,
                                                    VAL_TO_DRCT(absVal),
                                                    maxPeakValDec);
                actScaleFactor = CUR_SC_FACTOR2(sampleScaleFactor);
            }

            for (iCh=0; iCh < cChannel; iCh++)
            {
                paudec->rgpbTemp[iCh][iRecon] = MULT_SC(paudec->rgpbTemp[iCh][iRecon], actScaleFactor);
            }
    #ifdef PRINT_SCALE_FACTORS
            printf("%d, %0.12f, %0.12f\n", ++count, paudec->m_fltChannelFoldDownGain, actScaleFactor);
    #endif
        }
    }
    else  // No sample in the block will clip
    {
        for (iCh=0; iCh < cChannel; iCh++) {
          pbt = &paudec->rgpbTemp[iCh][iLo];
#ifdef DRC_BUILD_INTEGER_TABLE
          curScaleFactor = prevScaleFactor<<iSlopeShiftBits;
#else
          curScaleFactor = prevScaleFactor;
#endif
          for (iRecon=iLo; iRecon < iMid; iRecon++, pbt++) {
            curScaleFactor += slopeScaleFactor;
            *pbt = MULT_SC(*pbt, CUR_SC_FACTOR(curScaleFactor));
            // absVal = ABS((ValType)*pbt);
            // if (absVal > maxVal) maxVal = absVal;

#ifdef PRINT_SCALE_FACTORS
          if (iCh == 0) printf("%d, %0.12f, %0.12f\n", ++count, paudec->m_fltChannelFoldDownGain, CUR_SC_FACTOR(curScaleFactor));
#endif
          }
          for (; iRecon < iHi; iRecon++, pbt++) {
            *pbt = MULT_SC(*pbt, actScaleFactor);
            // absVal = ABS((ValType)*pbt);
            // if (absVal > maxVal) maxVal = absVal;
#ifdef PRINT_SCALE_FACTORS
          if (iCh == 0) printf("%d, %0.12f, %0.12f\n", ++count, paudec->m_fltChannelFoldDownGain, actScaleFactor);
#endif
          }
        }
    }

#endif

#if 0 // Soft clipping after scaling - Not used anymore
      // since the NEW_DRC_CODE above takes care of reducing the 
      // gain when clipping occurs
    if (maxVal > pau->m_iSampleMaxValue)
    {
        Float threshold = pau->m_iSampleMaxValue * THRESH;
        maxVal = max(maxVal, (pau->m_iSampleMaxValue * 2));

#if 0
        if (cChannel == 2) // unrolled loop
        {
            BufType *pbt0 = &paudec->rgpbTemp[0][iLo];
            BufType *pbt1 = &paudec->rgpbTemp[1][iLo];
            for (iRecon=iLo; iRecon < iHi; iRecon++, pbt0++, pbt1++)
            {
                const BufType absVal0 = ABS((ValType)*pbt0);
                const BufType absVal1 = ABS((ValType)*pbt1);
                const BufType absVal = max(absVal0, absVal1);
                Float gain;
                if (absVal > threshold)
                {
                    //                    (threshold - MAXVALUE)
                    //  X = MAXVALUE +   --------------------------- * (X - MAX_X_VALUE)^2
                    //                    (threshold - MAX_X_VALUE)^2
                    //
                    // threshold : All values less than threshold have a gain of 1. All values greater than threshold will be soft-clipped
                    // MAX_X_VALUE: Highest input value.
                    
                    gain = (Float)
                           (((pau->m_iSampleMaxValue - 5) +     // -5 for safety  
                           (((threshold - pau->m_iSampleMaxValue) * (absVal - maxVal) * (absVal - maxVal)) 
                           / (threshold - maxVal) / (threshold - maxVal))) / absVal);
                    *pbt0 *= gain;
                    *pbt1 *= gain;
                }
            }
        }
        else
        {
            for (iRecon=iLo; iRecon < iHi; iRecon++)
            {
                BufType absVal = 0;
                Float gain;
                for (iCh=0; iCh < cChannel; iCh++)
                {
                    const BufType absValTemp = ABS((ValType)paudec->rgpbTemp[iCh][iRecon]);
                    if (absValTemp > absVal) absVal = absValTemp;
                }

                if (absVal > threshold)
                {
                    gain = (Float)
                           (((pau->m_iSampleMaxValue - 5) +     // -5 for safety  
                           (((threshold - pau->m_iSampleMaxValue) * (absVal - maxVal) * (absVal - maxVal)) 
                           / (threshold - maxVal) / (threshold - maxVal))) / absVal);

                    for (iCh=0; iCh < cChannel; iCh++)
                    {
                        paudec->rgpbTemp[iCh][iRecon] *= gain;
                    }
                }
            }
        }
#else
        // This code scales the channels independently
        for (iCh=0; iCh < cChannel; iCh++)
        {
            pbt = &paudec->rgpbTemp[iCh][iLo];
            for (iRecon=iLo; iRecon < iHi; iRecon++, pbt++)
            {
                const BufType absVal = ABS((ValType)*pbt);
                BufType newVal;
                if (absVal > threshold)
                {
                    //                    (threshold - MAXVALUE)
                    //  X = MAXVALUE +   --------------------------- * (X - MAX_X_VALUE)^2
                    //                    (threshold - MAX_X_VALUE)^2
                    //
                    // threshold : All values less than threshold have a gain of 1. All values greater than threshold will be soft-clipped
                    // MAX_X_VALUE: Highest input value.
                    
                    newVal = (BufType)
                        ((pau->m_iSampleMaxValue - 5) +     // -5 for safety  
                        (((threshold - pau->m_iSampleMaxValue) * (absVal - maxVal) * (absVal - maxVal)) 
                         / (threshold - maxVal) / (threshold - maxVal)));
                    *pbt = (newVal * *pbt) / (absVal);      // restore sign
                }
            }
        }
#endif
    }
#endif
#ifdef OLD_DRC
    assert(p->m_curScaleFactor == sampleScaleFactor);
#endif
    p->m_curScaleFactor = sampleScaleFactor;

  } // iBlock loop

exit:
  return wr;
}

