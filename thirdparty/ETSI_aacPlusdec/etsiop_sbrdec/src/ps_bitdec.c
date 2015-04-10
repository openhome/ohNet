/*
   parametric stereo bitstream processing and decoding
 */
#ifndef MONO_ONLY

#include "env_extr.h"
#include "ps_bitdec.h"
#include "ps_dec.h"
#include "sbr_rom.h"
#include "count.h"

static const Word16 aNoBins[3] = {NO_LOW_RES_BINS, NO_BINS, NO_HI_RES_BINS};
static const Word16 aFixNoEnvDecode[4] = {0, 1, 2, 4};


/*!
  \brief  Limit input value to a certain range

  \return Limited value
*/
static Word16
limitMinMax(Word16 i,    /*!< Input value to be checked */
            Word16 min,  /*!< Minimum allowed value */
            Word16 max)  /*!< Maximum allowed value */
{
  int result = i;

  test();
  if ( sub(i,min)<0){
    result = min;                                               move16();
  }
  else {
    test();
    if ( sub(i,max)>0) {
      result = max;                                             move16();
    }
  }

  return result;
}


static Word16 divideBy2(Word16 op)
{
  Flag sign = (op < 0);                                         logic16();

  test();
  if (sign) {
    op = negate(op);
  }

  op = shr(op, 1);

  test();
  if (sign) {
    op = negate(op);
  }

  return op;
}


static Word16 divideBy3(Word16 op)
{
  Word16 temp, ret;
  Flag sign = (op < 0);                                         logic16();

  test();
  if (sign) {
    op = negate(op);
  }

  /* Convert to fractional number and shift left to get rid of rounding effects */
  temp = shl(op,2);

  /* Now perform the division (multiplication by 1/3) */
  temp = mult(temp, 0x2aab);

  /* Compensate for left-shift */
  ret = shr(temp,2);

  test();
  if (sign) {
    ret = negate(ret);
  }

  return ret;
}


/***************************************************************************/
/*!
  \brief  Decodes delta values in-place and updates
          data buffers according to quantization classes.

  \return none

****************************************************************************/
static void
deltaDecodeArray(Flag enable,            /*!< Flag if new data is available */
                 Word16 *aIndex,         /*!< Input/output data */
                 Word16 *aPrevFrameIndex,/*!< Decoded data from previous envelope */
                 Flag DtDf,              /*!< Delta coding direction in time or frequency */
                 Word16 nrElements,      /*!< Number of values to be processed */
                 Word16 stride,          /*!< Step size in previous data: 1=dflt, 2=half freq. resolution */
                 Word16 minIdx,          /*!< Minimum allowed index */
                 Word16 maxIdx)          /*!< Maximum allowed index */
{
  Word16 i;
  Word16 tmp;

  test();
  if ( enable ) {
    test();
    if (DtDf)  { 
      Word16 is;
      /* Delta coded in time */
      is = 0; move16();
      for (i = 0; i < nrElements; i++) {
        tmp       = add(aPrevFrameIndex[is], aIndex[i]);
        aIndex[i] = limitMinMax(tmp,minIdx,maxIdx);             move16();  
        is += stride;
      }
    }
    else {
      /* Delta coded in freq */
      aIndex[0] = limitMinMax(aIndex[0],minIdx,maxIdx);         move16();
      for (i = 1; i < nrElements; i++) {
        tmp       = add(aIndex[i-1], aIndex[i]);
        aIndex[i] = limitMinMax(tmp,minIdx,maxIdx);             move16();
      }
    }
  }
  else {
    /* No data is sent, set index to zero */
    for (i = 0; i < nrElements; i++) {
      aIndex[i] = 0;                                            move16();
    }
  }
  
  test();
  if ( sub(stride,2)==0 ) {
    sub(shl(nrElements,1),1);
    for (i=nrElements*stride-1; i>0; i--) {
      aIndex[i] = aIndex[shr(i,1)];                                 move16();
    }
  }

}


/*!
  \brief  Map high-resolution parametric stereo data to low-resolution

*/
static void map34IndexTo20(Word16 *aIndex)
{
  aIndex[0]  = divideBy3(add(add(aIndex[0],aIndex[0]),aIndex[1])); move16();
  aIndex[1]  = divideBy3(add(aIndex[1],add(aIndex[2],aIndex[2]))); move16();
  aIndex[2]  = divideBy3(add(add(aIndex[3],aIndex[3]),aIndex[4])); move16();
  aIndex[3]  = divideBy3(add(aIndex[4],add(aIndex[5],aIndex[5]))); move16();
  aIndex[4]  = divideBy2(add(aIndex[6],aIndex[7]));                move16();
  aIndex[5]  = divideBy2(add(aIndex[8],aIndex[9]));                move16();
  aIndex[6]  = aIndex[10];                                         move16();
  aIndex[7]  = aIndex[11];                                         move16();
  aIndex[8]  = divideBy2(add(aIndex[12],aIndex[13]));              move16();
  aIndex[9]  = divideBy2(add(aIndex[14],aIndex[15]));              move16();
  aIndex[10] = aIndex[16];                                         move16();
  aIndex[11] = aIndex[17];                                         move16();
  aIndex[12] = aIndex[18];                                         move16();
  aIndex[13] = aIndex[19];                                         move16();
  aIndex[14] = divideBy2(add(aIndex[20],aIndex[21]));              move16();
  aIndex[15] = divideBy2(add(aIndex[22],aIndex[23]));              move16();
  aIndex[16] = divideBy2(add(aIndex[24],aIndex[25]));              move16();
  aIndex[17] = divideBy2(add(aIndex[26],aIndex[27]));              move16();
  aIndex[18] = divideBy2( divideBy2(add(add(aIndex[28],aIndex[29]),add(aIndex[30],aIndex[31]))) ); move16();
  aIndex[19] = divideBy2(add(aIndex[32],aIndex[33]));              move16();
}


/*!
  \brief  Decodes parametric stereo data
*/
void
DecodePs(HANDLE_PS_DEC h_ps_dec) /*!< Handle to struct containing parametric stereo data */
{
  Word8 gr, env;
  Word16 noEnvm1;

  test();
  if (!h_ps_dec->bPsDataAvail) {
    /* no new PS data available (e.g. frame loss) */
    /* => keep latest data constant (i.e. FIX with noEnv=0) */
    h_ps_dec->noEnv = 0;                                        move16();
  }

  move16(); /* h_ps_dec->noEnv */
  for (env=0; env<h_ps_dec->noEnv; env++) {
    Word16 *aPrevIidIndex;
    Word16 *aPrevIccIndex;
    Word16 noIidSteps = h_ps_dec->bFineIidQ ? NO_IID_STEPS_FINE:NO_IID_STEPS; test(); move16();

    test();
    if (env==0) {
      aPrevIidIndex = h_ps_dec->aIidPrevFrameIndex;             move16();
      aPrevIccIndex = h_ps_dec->aIccPrevFrameIndex;             move16();   
    }
    else {
      aPrevIidIndex = h_ps_dec->aaIidIndex[env-1];              move16();
      aPrevIccIndex = h_ps_dec->aaIccIndex[env-1];              move16();
    }

    deltaDecodeArray(h_ps_dec->bEnableIid,
                     h_ps_dec->aaIidIndex[env],
                     aPrevIidIndex,
                     h_ps_dec->abIidDtFlag[env],
                     aNoBins[h_ps_dec->freqResIid],
                     (h_ps_dec->freqResIid)?1:2,
                     negate(noIidSteps),
                     noIidSteps);                               test(); move16();

    deltaDecodeArray(h_ps_dec->bEnableIcc,
                     h_ps_dec->aaIccIndex[env],
                     aPrevIccIndex,
                     h_ps_dec->abIccDtFlag[env],
                     aNoBins[h_ps_dec->freqResIcc],
                     (h_ps_dec->freqResIcc)?1:2,
                     0,
                     NO_ICC_STEPS-1);                           test(); move16();

  }   /* for (env=0; env<h_ps_dec->noEnv; env++) */


  test();
  if (h_ps_dec->noEnv==0) {
    /* set noEnv=1, keep last parameters or force 0 if not enabled */
    h_ps_dec->noEnv = 1;                                        move16();

    test();
    if (h_ps_dec->bEnableIid) {
      for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
        h_ps_dec->aaIidIndex[0][gr] =
          h_ps_dec->aIidPrevFrameIndex[gr];                     move16();
      }
    }
    else {
      for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
        h_ps_dec->aaIidIndex[0][gr] = 0;                        move16();
      }
    }

    test();
    if (h_ps_dec->bEnableIcc) {
      for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
        h_ps_dec->aaIccIndex[0][gr] =
          h_ps_dec->aIccPrevFrameIndex[gr];                     move16();
      }
    }
    else {
      for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
        h_ps_dec->aaIccIndex[0][gr] = 0;                        move16();
      }
    }
  }


  /* Update previous frame index buffers */
  noEnvm1 = sub(h_ps_dec->noEnv,1);
  for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
    h_ps_dec->aIidPrevFrameIndex[gr] =
      h_ps_dec->aaIidIndex[noEnvm1][gr];                        move16();
  }

  for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
    h_ps_dec->aIccPrevFrameIndex[gr] =
      h_ps_dec->aaIccIndex[noEnvm1][gr];                        move16();
  }

  h_ps_dec->bPsDataAvail = 0;                                   move16();

  test();
  if (h_ps_dec->bFrameClass == 0) {
    /* FIX_BORDERS NoEnv=0,1,2,4 */
    Word16 env_count;
    Word16 shift;

    switch (h_ps_dec->noEnv){
    case 1:
      shift = 0;                                                test(); move16();
      break;
    case 2:
      shift = 1;                                                test(); test(); move16();
      break;
    case 4:
      shift = 2;                                                test(); test(); test(); move16();
      break;
    }
    h_ps_dec->aEnvStartStop[0] = 0;                             move16();
    env_count = 0;                                              move16();
    move16(); /* h_ps_dec->noEnv */
    for (env=1; env<h_ps_dec->noEnv; env++) {
      env_count = add(env_count, MAX_NUM_COL);
      h_ps_dec->aEnvStartStop[env] = shr(env_count, shift); move16(); 
    }
    h_ps_dec->aEnvStartStop[h_ps_dec->noEnv] = MAX_NUM_COL;     move16();
  }
  else {
    /* VAR_BORDERS NoEnv=1,2,3,4 */

    h_ps_dec->aEnvStartStop[0] = 0;                             move16();

    /* Handle case aEnvStartStop[noEnv]<noSubSample for VAR_BORDERS by
       duplicating last PS parameters and incrementing noEnv */
    test();
    if ( sub(h_ps_dec->aEnvStartStop[h_ps_dec->noEnv],MAX_NUM_COL) < 0) {
      Word16 noEnvm1, noEnvm2;
      h_ps_dec->noEnv++;                                        add(h_ps_dec->noEnv,1); move16();
      h_ps_dec->aEnvStartStop[h_ps_dec->noEnv] = MAX_NUM_COL;   move16();

      noEnvm1 = sub(h_ps_dec->noEnv,1);                         move16(); 
      noEnvm2 = sub(h_ps_dec->noEnv,2);                         move16();
      for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
        h_ps_dec->aaIidIndex[noEnvm1][gr] =
          h_ps_dec->aaIidIndex[noEnvm2][gr];                    move16();
      }

      for (gr = 0; gr < NO_HI_RES_BINS; gr++) {
        h_ps_dec->aaIccIndex[noEnvm1][gr] =
          h_ps_dec->aaIccIndex[noEnvm2][gr];                    move16();
      }
    }

    /* Enforce strictly monotonic increasing borders */
    move16(); /* h_ps_dec->noEnv */
    for (env=1; env<h_ps_dec->noEnv; env++) {
      Word16 thr;
      thr = sub(MAX_NUM_COL, add(h_ps_dec->noEnv, env));

      test();
      if ( sub(h_ps_dec->aEnvStartStop[env], thr) > 0) {
        h_ps_dec->aEnvStartStop[env] = thr;                     move16();
      }
      else {
        thr = add(h_ps_dec->aEnvStartStop[env-1],1);

        test();
        if (sub(h_ps_dec->aEnvStartStop[env], thr) < 0) {
          h_ps_dec->aEnvStartStop[env] = thr;                   move16();
        }
      }
    }
  }

  for (env=0; env<h_ps_dec->noEnv; env++) {
    test();
    if ( sub(h_ps_dec->freqResIid,2) == 0 )
      map34IndexTo20 (h_ps_dec->aaIidIndex[env]);

    test();
    if ( sub(h_ps_dec->freqResIcc,2) == 0 )
      map34IndexTo20 (h_ps_dec->aaIccIndex[env]);
  }

}


/***************************************************************************/
/*!
  \brief  Reads IID and ICC data from bitstream

  \return Number of bits consumed

****************************************************************************/
Word16
ReadPsData (HANDLE_PS_DEC h_ps_dec, /*!< Handle to struct PS_DEC*/
            HANDLE_BIT_BUF hBitBuf, /*!< Handle to struct BIT_BUF */
            Word16 nBitsLeft           /*!< Maximum number of bits available */
           )
{
  Word8   gr, env;
  Flag    dtFlag;
  Word16  startbits;
  Huffman CurrentTable;
  Flag    bEnableHeader;

  test();
  if (!h_ps_dec) {
    return 0;
  }

  startbits = GetNrBitsAvailable(hBitBuf);

  /*
    Read header
  */
  bEnableHeader = ReadBits(hBitBuf, 1);

  test();
  if (bEnableHeader) {
    h_ps_dec->bEnableIid = ReadBits(hBitBuf, 1);                move16();

    test();
    if (h_ps_dec->bEnableIid) {
      h_ps_dec->freqResIid = (Word8) ReadBits(hBitBuf, 3);      move16(); logic16(); logic16(); logic16(); 
    }

    h_ps_dec->bEnableIcc = ReadBits(hBitBuf, 1);                move16();

    test();
    if (h_ps_dec->bEnableIcc) {
      h_ps_dec->freqResIcc = (Word8)ReadBits(hBitBuf, 3);       move16(); logic16(); logic16(); logic16();
    }

    h_ps_dec->bEnableExt = ReadBits(hBitBuf, 1);                move16();

    test(); test();
    if ((sub(h_ps_dec->freqResIid,5) > 0) || (sub(h_ps_dec->freqResIcc,5) > 0)) {

      /* Not supported, previous stereo image will continue */
      h_ps_dec->bPsDataAvail = 0;                               move16();

      nBitsLeft = sub(nBitsLeft,sub(startbits, GetNrBitsAvailable(hBitBuf)));

      /* Skip remaining PS data */
      test();
      while (nBitsLeft > 0) {
        Word16 i = nBitsLeft;                                   move16();

        test();
        if (sub(i,8)>0) {
          i = 8;                                                move16();
        }
        ReadBits(hBitBuf, i);
        nBitsLeft = sub(nBitsLeft, i);
        test(); /* end of while */
      }
      return sub(startbits, GetNrBitsAvailable(hBitBuf));
    }
        
    /* Extract flag for fine IID quantization */
    test();
    if (sub(h_ps_dec->freqResIid,2) > 0){
      h_ps_dec->bFineIidQ = 1;                                  move16();
      h_ps_dec->freqResIid = sub(h_ps_dec->freqResIid,3);       move16();
    }
    else{
      h_ps_dec->bFineIidQ = 0;                                  move16();
    }

    /* Extract flag for PCA mixing method */
    test();
    if ( sub(h_ps_dec->freqResIcc,2) > 0){
      h_ps_dec->freqResIcc = sub(h_ps_dec->freqResIcc,3);       move16();
    }

  }


  /*
    Read time grid
  */
  h_ps_dec->bFrameClass = (Flag)ReadBits(hBitBuf, 1); move16();

  test();
  if (h_ps_dec->bFrameClass == 0) {
    h_ps_dec->noEnv = aFixNoEnvDecode[(Word16)ReadBits(hBitBuf, 2)]; move16();
  }
  else {
    h_ps_dec->noEnv = shr(shl(add(1, (Word16)ReadBits(hBitBuf, 2)),8),8); move16();
    add(h_ps_dec->noEnv,1);
    for (env=1; env<h_ps_dec->noEnv+1; env++) {
      h_ps_dec->aEnvStartStop[env] = shr(shl(add((Word16)ReadBits(hBitBuf, 5), 1),8),8); move16();
    }
  }


  /*
    Read huffman coded IID data
  */
  test();
  if (h_ps_dec->bEnableIid) {
    move16(); /* h_ps_dec->noEnv */
    for (env=0; env<h_ps_dec->noEnv; env++) {
      dtFlag = (Flag)ReadBits(hBitBuf, 1); move16();

      test();
      if (!dtFlag) {
        test(); move16();
        if (h_ps_dec->bFineIidQ)
          CurrentTable = (Huffman)&aBookPsIidFineFreqDecode;
        else
          CurrentTable = (Huffman)&aBookPsIidFreqDecode;
      }
      else {
        test(); move16();
        if (h_ps_dec->bFineIidQ)
          CurrentTable = (Huffman)&aBookPsIidFineTimeDecode;
        else
          CurrentTable = (Huffman)&aBookPsIidTimeDecode;
      }

      move16(); /* aNoBins[h_ps_dec->freqResIid] */
      for (gr = 0; gr < aNoBins[h_ps_dec->freqResIid]; gr++) {
        h_ps_dec->aaIidIndex[env][gr] = decode_huff_cw(CurrentTable,hBitBuf); move16();
      }
      h_ps_dec->abIidDtFlag[env] = dtFlag;                      move16();
    }
  }


  /*
    Read huffman coded ICC data
  */
  test();
  if (h_ps_dec->bEnableIcc) {

    for (env=0; env<h_ps_dec->noEnv; env++) {
      dtFlag = ReadBits(hBitBuf, 1);                            move16();

      test();
      if (!dtFlag) {
        CurrentTable = (Huffman)&aBookPsIccFreqDecode; move16();
      }
      else {
        CurrentTable = (Huffman)&aBookPsIccTimeDecode; move16();
      }

      for (gr = 0; gr < aNoBins[h_ps_dec->freqResIcc]; gr++) {
        h_ps_dec->aaIccIndex[env][gr] = decode_huff_cw(CurrentTable,hBitBuf); move16();
      }
      h_ps_dec->abIccDtFlag[env] = dtFlag;                      move16();
    }
  }


  /*
    Skip extensions:
    IPD/OPD data can be conveyed there, which is not evaluated
    by a baseline parametric stereo decoder.
  */
  test();
  if (h_ps_dec->bEnableExt) {

    Word16 cnt = (Word16)ReadBits(hBitBuf, 4);
    test();
    if (sub(cnt,15) == 0)
    {
      cnt = add(cnt,(Word16)ReadBits(hBitBuf, 8));
    }

    sub(cnt, 1); test(); 
    while (cnt--) {
      ReadBits(hBitBuf, 8);
      sub(cnt, 1); test(); 
    }
  }

  h_ps_dec->bPsDataAvail = 1;                                   move16();

  return sub(startbits,GetNrBitsAvailable(hBitBuf));
}
#endif
