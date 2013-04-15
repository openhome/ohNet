/*
   envelope decoding
 */

#include <string.h>
#include <assert.h>
#include "env_dec.h"
#include "sbr_const.h"         /* Various defines */
#include "env_extr.h"
#include "ffr.h"
#include "assert.h"
#include "intrinsics.h"
#include "count.h"

static void decodeEnvelope (HANDLE_SBR_HEADER_DATA hHeaderData,
                            HANDLE_SBR_FRAME_DATA h_sbr_data,
                            HANDLE_SBR_PREV_FRAME_DATA h_prev_data,
                            HANDLE_SBR_PREV_FRAME_DATA h_prev_data_otherChannel);
static void sbr_envelope_unmapping (HANDLE_SBR_HEADER_DATA hHeaderData,
                                    HANDLE_SBR_FRAME_DATA h_data_left,
                                    HANDLE_SBR_FRAME_DATA h_data_right);
static void requantizeEnvelopeData (HANDLE_SBR_FRAME_DATA h_sbr_data,
                                    Word16 ampResolution);
static void deltaToLinearPcmEnvelopeDecoding (HANDLE_SBR_HEADER_DATA hHeaderData,
                                              HANDLE_SBR_FRAME_DATA h_sbr_data,
                                              HANDLE_SBR_PREV_FRAME_DATA h_prev_data);
static void decodeNoiseFloorlevels (HANDLE_SBR_HEADER_DATA hHeaderData,
                                    HANDLE_SBR_FRAME_DATA h_sbr_data,
                                    HANDLE_SBR_PREV_FRAME_DATA h_prev_data);
static void timeCompensateFirstEnvelope (HANDLE_SBR_HEADER_DATA hHeaderData,
                                         HANDLE_SBR_FRAME_DATA h_sbr_data,
                                         HANDLE_SBR_PREV_FRAME_DATA h_prev_data);
static Word16 checkEnvelopeData (HANDLE_SBR_HEADER_DATA hHeaderData,
                                 HANDLE_SBR_FRAME_DATA h_sbr_data,
                                 HANDLE_SBR_PREV_FRAME_DATA h_prev_data);



#define SBR_ENERGY_PAN_OFFSET   12
#define SBR_MAX_ENERGY          35
#define DECAY                    1
#define DECAY_COUPLING           1


/*!
  \brief  Convert table index
*/
static Word16 indexLow2High(Word16 offset, /*!< mapping factor */
                            Word16 index,  /*!< index to scalefactor band */
                            Word16 res)    /*!< frequency resolution */
{
  test();
  if(sub(res,LO) == 0)
  {
    test();
    if (offset >= 0)
    {
      test();
      if (sub(index, offset) < 0)
        return(index);
      else
        return(sub(shl(index,1), offset));
    }
    else
    {
      offset = negate(offset);
      test();
      if (sub(index, offset) < 0)
        return(2*index+index);
      else
        return(add(shl(index,1), offset));
    }
  }
  else
    return(index);
}


/*!
  \brief  Update previous envelope value for delta-coding
*/
static void mapLowResEnergyVal(Word16  currVal,  /*!< current energy value */
                               Word16* prevData, /*!< pointer to previous data vector */
                               Word16 offset,    /*!< mapping factor */
                               Word16 index,     /*!< index to scalefactor band */
                               Word16 res)       /*!< frequeny resolution */
{
  test();
  if(sub(res, LO) == 0)
  {
    test();
    if (offset >= 0)
    {
      test();
      if(sub(index, offset) < 0) {
        prevData[index] = currVal;                               move16();
      }
      else
      {
        Word16  index_2;
        index_2 = sub(add(index, index), offset);
        prevData[index_2] = currVal;                             move16();
        prevData[index_2+1] = currVal;                           move16();
      }
    }
    else
    {
      test();
      offset = negate(offset);
      test();
      if (sub(index, offset) < 0)
      {
        Word16  index_3;
        index_3 = add(add(index, index), index);
        prevData[index_3] = currVal;                             move16();
        prevData[index_3+1] = currVal;                           move16();
        prevData[index_3+2] = currVal;                           move16();
      }
      else
      {
        Word16  index_2;
        index_2 = add(add(index, index), offset);
        prevData[index_2] = currVal;                             move16();
        prevData[index_2+1] = currVal;                           move16();
      }
    }    
  }
  else {
    prevData[index] = currVal;                                   move16();
  }
}



/*!
  \brief    Convert raw envelope and noisefloor data to energy levels
*/
void
decodeSbrData (HANDLE_SBR_HEADER_DATA hHeaderData,          /*!< Static control data */
               HANDLE_SBR_FRAME_DATA h_data_left,           /*!< pointer to left channel frame data */
               HANDLE_SBR_PREV_FRAME_DATA h_prev_data_left, /*!< pointer to left channel previous frame data */
               HANDLE_SBR_FRAME_DATA h_data_right,          /*!< pointer to right channel frame data */
               HANDLE_SBR_PREV_FRAME_DATA h_prev_data_right)/*!< pointer to right channel previous frame data */
{
  Flag errLeft;

  decodeEnvelope (hHeaderData, h_data_left, h_prev_data_left, h_prev_data_right);
  decodeNoiseFloorlevels (hHeaderData, h_data_left, h_prev_data_left);
  
  test();
  if(h_data_right != NULL) {
    errLeft = hHeaderData->frameErrorFlag;                      move16();
    decodeEnvelope (hHeaderData, h_data_right, h_prev_data_right, h_prev_data_left);
    decodeNoiseFloorlevels (hHeaderData, h_data_right, h_prev_data_right);

    test(); test();
    if (!errLeft && hHeaderData->frameErrorFlag) {
      decodeEnvelope (hHeaderData, h_data_left, h_prev_data_left, h_prev_data_right);
    }

    test();
    if (h_data_left->coupling) {
      sbr_envelope_unmapping (hHeaderData, h_data_left, h_data_right);
    }
  }

}


/*!
  \brief   Convert from coupled channels to independent L/R data
*/
static void
sbr_envelope_unmapping (HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
                        HANDLE_SBR_FRAME_DATA h_data_left,  /*!< pointer to left channel */
                        HANDLE_SBR_FRAME_DATA h_data_right) /*!< pointer to right channel */
{
  Word16 i;
  Word16  tempL_m, tempR_m, tempRplus1_m, newL_m, newR_m;
  Word16  tempL_e, tempR_e, tempRplus1_e, newL_e, newR_e;
  Word16  i_end;

  /* 1. Unmap (already dequantized) coupled envelope energies */
  assert(h_data_left->nScaleFactors > 0);
  move16(); /* h_data_left->nScaleFactors */
  for (i = 0; i < h_data_left->nScaleFactors; i++) {
    tempR_m = h_data_right->iEnvelope[i] & MASK_M;              logic16();
    tempR_e = h_data_right->iEnvelope[i] & (Word8)MASK_E;       logic16();

    tempR_e = sub(tempR_e, add(18, NRG_EXP_OFFSET));  /* -18 = ld(UNMAPPING_SCALE / h_data_right->nChannels) */
    tempL_m = h_data_left->iEnvelope[i] & MASK_M;               logic16();
    tempL_e = h_data_left->iEnvelope[i] & (Word8)MASK_E;        logic16();

    tempL_e = sub(tempL_e, NRG_EXP_OFFSET);

    /* Calculate tempRight+1 */
    ffr_add_MantExp( tempR_m, tempR_e,
                     0x4000, 1,  /* 1.0 */
                     &tempRplus1_m, &tempRplus1_e);

    ffr_divide_MantExp( tempL_m, add(tempL_e,1),  /*  2 * tempLeft */
                        tempRplus1_m, tempRplus1_e,
                        &newR_m, &newR_e );

    newL_m = mult(tempR_m, newR_m);
    newL_e = add(tempR_e, newR_e);

    h_data_right->iEnvelope[i] = add(add(newR_m, ROUNDING) & (Word16)MASK_M, add(newR_e, NRG_EXP_OFFSET) & (Word16)MASK_E);   logic16(); logic16(); move16();
    h_data_left->iEnvelope[i] =  add(add(newL_m, ROUNDING) & (Word16)MASK_M, add(newL_e, NRG_EXP_OFFSET) & (Word16)MASK_E);   logic16(); logic16(); move16();
  }

  /* 2. Dequantize and unmap coupled noise floor levels */
  assert(hHeaderData->hFreqBandData->nNfb * h_data_left->frameInfo.nNoiseEnvelopes > 0);
  i_end = shr(extract_l(L_mult(hHeaderData->hFreqBandData->nNfb, h_data_left->frameInfo.nNoiseEnvelopes)),1);
  for (i = 0; i < i_end; i++) {

    tempL_e = sub((h_data_left->sbrNoiseFloorLevel[i] & (Word16)MASK_E), NOISE_EXP_OFFSET);  logic16();
    tempR_e = sub(h_data_right->sbrNoiseFloorLevel[i], 12) /*SBR_ENERGY_PAN_OFFSET*/;

    /* Calculate tempR+1 */
    ffr_add_MantExp( 0x4000, add(1,tempR_e), /* tempR */
                     0x4000, 1,         /*  1.0  */
                     &tempRplus1_m, &tempRplus1_e);

    /* Calculate 2*tempLeft/(tempR+1) */
    ffr_divide_MantExp( 0x4000, add(tempL_e,1),  /*  2 * tempLeft */
                        tempRplus1_m, tempRplus1_e,
                        &newR_m, &newR_e );

    /* L = tempR * R */
    newL_m = newR_m;                                            move16();
    newL_e = add(newR_e, tempR_e);
    h_data_right->sbrNoiseFloorLevel[i] = add(add(newR_m, ROUNDING) & (Word16)MASK_M, add(newR_e, NOISE_EXP_OFFSET) & (Word16)MASK_E);   logic16(); logic16();  move16();
    h_data_left->sbrNoiseFloorLevel[i] =  add(add(newL_m, ROUNDING) & (Word16)MASK_M, add(newL_e, NOISE_EXP_OFFSET) & (Word16)MASK_E);   logic16(); logic16();  move16();
  }
}


/*!
  \brief    Simple alternative to the real SBR concealment
*/
static void
leanSbrConcealment(HANDLE_SBR_HEADER_DATA hHeaderData,     /*!< Static control data */
                   HANDLE_SBR_FRAME_DATA  h_sbr_data,      /*!< pointer to current data */
                   HANDLE_SBR_PREV_FRAME_DATA h_prev_data  /*!< pointer to data of last frame */
                   )
{
  Word16  target;  /* targeted level for sfb_nrg_prev during fade-down */
  Word16  step;    /* speed of fade */
  Word16 i;

  Word16 currentStartPos;
  Word16 currentStopPos;

  currentStartPos = sub(h_prev_data->stopPos, hHeaderData->numberTimeSlots);
  currentStopPos = hHeaderData->numberTimeSlots;                move16();
 
  /* Use some settings of the previous frame */
  h_sbr_data->ampResolutionCurrentFrame = h_prev_data->ampRes;  move16();
  h_sbr_data->coupling = h_prev_data->coupling;                 move16();
  h_sbr_data->maxQmfSubbandAac = h_prev_data->maxQmfSubbandAac; move16();
  for(i=0;i<MAX_INVF_BANDS;i++) {
    h_sbr_data->sbr_invf_mode[i] = h_prev_data->sbr_invf_mode[i];  move16();
  }

  /* Generate control data */

  h_sbr_data->frameInfo.nEnvelopes = 1;                         move16();
  h_sbr_data->frameInfo.borders[0] = currentStartPos;           move16();
  h_sbr_data->frameInfo.borders[1] = currentStopPos;            move16();
  h_sbr_data->frameInfo.freqRes[0] = 1;                         move16();
  h_sbr_data->frameInfo.tranEnv = -1;  /* no transient */       move16();
  h_sbr_data->frameInfo.nNoiseEnvelopes = 1;                    move16();
  h_sbr_data->frameInfo.bordersNoise[0] = currentStartPos;      move16();
  h_sbr_data->frameInfo.bordersNoise[1] = currentStopPos;;      move16();

  h_sbr_data->nScaleFactors = hHeaderData->hFreqBandData->nSfb[1]; move16();

  /* Generate fake envelope data */

  h_sbr_data->domain_vec[0] = TIME;                             move16();

  test();
  if (sub(h_sbr_data->coupling, COUPLING_BAL) == 0) {
    target = SBR_ENERGY_PAN_OFFSET;                             move16();
    step = DECAY_COUPLING;                                      move16();
  }
  else {
    target = 0;                                                 move16();
    step = DECAY;                                               move16();
  }
  test();
  if (sub(h_sbr_data->ampResolutionCurrentFrame, SBR_AMP_RES_1_5) == 0) {
    target = shl(target, 1);
    step   = shl(step, 1);
  }

  assert(h_sbr_data->nScaleFactors > 0);
  move16(); /* h_sbr_data->nScaleFactors */
  for (i=0; i < h_sbr_data->nScaleFactors; i++) {
    test();
    if (sub(h_prev_data->sfb_nrg_prev[i], target) > 0)
      h_sbr_data->iEnvelope[i] = negate(step);
    else
      h_sbr_data->iEnvelope[i] = step;                          move16();
  }

  /* Noisefloor levels are always cleared ... */

  h_sbr_data->domain_vec_noise[0] = TIME;                       move16();
  move16(); /*hHeaderData->hFreqBandData->nNfb*/
  for (i=0; i<hHeaderData->hFreqBandData->nNfb; i++) {
    h_sbr_data->sbrNoiseFloorLevel[i] = 0;                      move16();
  }

  /* ... and so are the sines */
  for (i=0; i<MAX_FREQ_COEFFS; i++) {
    h_sbr_data->addHarmonics[i] = 0;                            move16();
  }
}


/*!
  \brief   Build reference energies and noise levels from bitstream elements
*/
static void
decodeEnvelope (HANDLE_SBR_HEADER_DATA hHeaderData,     /*!< Static control data */
                HANDLE_SBR_FRAME_DATA  h_sbr_data,      /*!< pointer to current data */
                HANDLE_SBR_PREV_FRAME_DATA h_prev_data, /*!< pointer to data of last frame */
                HANDLE_SBR_PREV_FRAME_DATA otherChannel /*!< other channel's last frame data */
                )
{
  Word16 i;
  Flag Error_flag;
  Word16 tempSfbNrgPrev[MAX_FREQ_COEFFS];
  


  /* Check that the previous stop position and the current start position match.  */
  test(); test(); test();
  if ( (!hHeaderData->prevFrameErrorFlag) && (!hHeaderData->frameErrorFlag) &&
       (sub(h_sbr_data->frameInfo.borders[0], sub(h_prev_data->stopPos, hHeaderData->numberTimeSlots)) != 0) ) {
    /* Both the previous as well as the current frame are flagged to be ok, but they do not match! */
    test();
    if (sub(h_sbr_data->domain_vec[0], TIME) == 0) {
      /* Prefer concealment over delta-time coding between the mismatching frames */
      hHeaderData->frameErrorFlag = 1;                          move16();
    }
    else {
      /* Close the gap in time by triggering timeCompensateFirstEnvelope() */
      hHeaderData->prevFrameErrorFlag = 1;                      move16();
    }
  }


  test();
  if (hHeaderData->frameErrorFlag)       /* Error is detected */
  {
    leanSbrConcealment(hHeaderData,
        h_sbr_data,
        h_prev_data);

    /* decode the envelope data to linear PCM */
    deltaToLinearPcmEnvelopeDecoding (hHeaderData, h_sbr_data, h_prev_data);
  }
  else                          /*Do a temporary dummy decoding and check that the envelope values are within limits */
  {
    test();
    if (hHeaderData->prevFrameErrorFlag) {
      timeCompensateFirstEnvelope (hHeaderData, h_sbr_data, h_prev_data);
      test();
      if (sub(h_sbr_data->coupling, h_prev_data->coupling) != 0) {
        /*
           Coupling mode has changed during concealment.
           The stored energy levels need to be converted.
           */
        assert(hHeaderData->hFreqBandData->nSfb[HI] >= 1);
        move16(); /* hHeaderData->hFreqBandData->nSfb[HI] */
        for (i = 0; i < hHeaderData->hFreqBandData->nSfb[HI]; i++) {
          /* Former Level-Channel will be used for both channels */
          test();
          if (sub(h_prev_data->coupling, COUPLING_BAL) == 0) {
            h_prev_data->sfb_nrg_prev[i] = otherChannel->sfb_nrg_prev[i];  move16();
          }
          /* Former L/R will be combined as the new Level-Channel */
          else {
            test();
            if (sub(h_sbr_data->coupling, COUPLING_LEVEL) == 0) {
              h_prev_data->sfb_nrg_prev[i] = shr(add(h_prev_data->sfb_nrg_prev[i], otherChannel->sfb_nrg_prev[i]), 1);
              move16();
            }
            else {
              test();
              if (sub(h_sbr_data->coupling, COUPLING_BAL) == 0)
                h_prev_data->sfb_nrg_prev[i] = SBR_ENERGY_PAN_OFFSET;  move16();
            }
          }
        }
      }
    }
    for (i=0; i<MAX_FREQ_COEFFS; i++) {
      tempSfbNrgPrev[i] = h_prev_data->sfb_nrg_prev[i];         move16();
    }

    deltaToLinearPcmEnvelopeDecoding (hHeaderData, h_sbr_data, h_prev_data);

    Error_flag = checkEnvelopeData (hHeaderData, h_sbr_data, h_prev_data);

    test();
    if (Error_flag)
    {
      hHeaderData->frameErrorFlag = 1;                          move16();
      for (i=0; i<MAX_FREQ_COEFFS; i++) {
        h_prev_data->sfb_nrg_prev[i] = tempSfbNrgPrev[i];       move16();
      }
      decodeEnvelope (hHeaderData, h_sbr_data, h_prev_data, otherChannel);
      return;
    }
  }

  requantizeEnvelopeData (h_sbr_data, h_sbr_data->ampResolutionCurrentFrame);
}


/*!
  \brief   Verify that envelope energies are within the allowed range
  \return  0 if all is fine, 1 if an envelope value was too high
*/
static Word16
checkEnvelopeData (HANDLE_SBR_HEADER_DATA hHeaderData,     /*!< Static control data */
                   HANDLE_SBR_FRAME_DATA h_sbr_data,       /*!< pointer to current data */
                   HANDLE_SBR_PREV_FRAME_DATA h_prev_data  /*!< pointer to data of last frame */
                   )
{
  Word16  *iEnvelope = h_sbr_data->iEnvelope;
  Word16  *sfb_nrg_prev = h_prev_data->sfb_nrg_prev;
  Word16  i;
  Flag    errorFlag;
  Word16  sbr_max_energy;

  move16(); /* init iEnvelope */
  move16(); /* init sfb_nrg_prev */
  errorFlag = 0;                                                move16();

  test();
  if (sub(h_sbr_data->ampResolutionCurrentFrame, SBR_AMP_RES_3_0) == 0) {
    sbr_max_energy = SBR_MAX_ENERGY;                            move16();
  }
  else {
    sbr_max_energy = shl(SBR_MAX_ENERGY, 1);
  }

  /*
    Range check for current energies
  */
  assert(h_sbr_data->nScaleFactors > 0);
  move16(); /* h_sbr_data->nScaleFactors */ 
  for (i = 0; i < h_sbr_data->nScaleFactors; i++) {
    test();
    if (sub(iEnvelope[i], sbr_max_energy) > 0) {
      errorFlag = 1;                                            move16();
    }
    test();
    if (iEnvelope[i] < 0) {
      iEnvelope[i] = 0;                                         move16();
    }
  }

  /*
    Range check for previous energies
  */
  assert(hHeaderData->hFreqBandData->nSfb[HI] >= 1);
  move16(); /* hHeaderData->hFreqBandData->nSfb[HI] */
  for (i = 0; i < hHeaderData->hFreqBandData->nSfb[HI]; i++) {
    test();
    if (sfb_nrg_prev[i] < 0) {
      sfb_nrg_prev[i] = 0;                                      move16();
    }
    else {
      test();
      if (sub(sfb_nrg_prev[i], sbr_max_energy) > 0)
        sfb_nrg_prev[i] = sbr_max_energy;                       move16();
    }
  }

  return (errorFlag);
}


/*!
  \brief   Verify that the noise levels are within the allowed range
*/
static void
limitNoiseLevels(HANDLE_SBR_HEADER_DATA hHeaderData,     /*!< Static control data */
                 HANDLE_SBR_FRAME_DATA h_sbr_data)       /*!< pointer to current data */
{
  Word16 i, i_end;
  Word16 value;
  Word16 nNfb;
  Word16 lowerLimit, upperLimit; 

  nNfb = hHeaderData->hFreqBandData->nNfb;                      move16();
  /*
    Set range limits. The exact values depend on the coupling mode.
    However this limitation is primarily intended to avoid unlimited
    accumulation of the delta-coded noise levels.
  */
  lowerLimit = 0;     /* lowerLimit actually refers to the _highest_ noise energy */    move16();
  upperLimit = 35;    /* upperLimit actually refers to the _lowest_ noise energy */     move16();

  /*
    Range check for current noise levels
  */
  assert(h_sbr_data->frameInfo.nNoiseEnvelopes * nNfb > 0);
  i_end = shr(extract_l(L_mult(h_sbr_data->frameInfo.nNoiseEnvelopes, nNfb)), 1);
  for (i = 0; i < i_end; i++) {
    value = h_sbr_data->sbrNoiseFloorLevel[i];                  move16();
    test();
    if (sub(value, upperLimit) > 0) {
      h_sbr_data->sbrNoiseFloorLevel[i] = upperLimit;           move16();
    }
    else {
      test();
      if (sub(value, lowerLimit) < 0) {
        h_sbr_data->sbrNoiseFloorLevel[i] = lowerLimit;         move16();
      }
    }
  }
}


/*!
  \brief   Compensate for the wrong timing that might occur after a frame error.
*/
static void
timeCompensateFirstEnvelope (HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
                             HANDLE_SBR_FRAME_DATA h_sbr_data,   /*!< pointer to actual data */
                             HANDLE_SBR_PREV_FRAME_DATA h_prev_data)  /*!< pointer to data of last frame */
{
  Word16 i, nScalefactors;
  FRAME_INFO *pFrameInfo = &h_sbr_data->frameInfo;
  Word16 *nSfb = hHeaderData->hFreqBandData->nSfb;
  Word16 estimatedStartPos;
  Word16 refLen, newLen, shift;
  Word16  deltaExp;

  move16(); move16();
  estimatedStartPos = sub(h_prev_data->stopPos, hHeaderData->numberTimeSlots);

  /* Original length of first envelope according to bitstream */
  refLen = sub(pFrameInfo->borders[1], pFrameInfo->borders[0]);
  /* Corrected length of first envelope (concealing can make the first envelope longer) */
  newLen = sub(pFrameInfo->borders[1], estimatedStartPos);

  test();
  if (newLen <= 0) {
    newLen = refLen;                                            move16();
    estimatedStartPos = pFrameInfo->borders[0];                 move16();
  }

  deltaExp = ffr_getNumOctavesDiv8(newLen, refLen);

  /* Shift by -3 to rescale ld-table, 1-ampRes to enable coarser steps */
  shift = sub(SHORT_BITS-ENV_EXP_FRACT-3, h_sbr_data->ampResolutionCurrentFrame);
  deltaExp = shr(deltaExp, shift);
  pFrameInfo->borders[0] = estimatedStartPos;                   move16();
  pFrameInfo->bordersNoise[0] = estimatedStartPos;              move16();

  test();
  if (sub(h_sbr_data->coupling, COUPLING_BAL) != 0) {
    test(); move16();
    nScalefactors = (pFrameInfo->freqRes[0]) ? nSfb[HI] : nSfb[LO];

    assert(nScalefactors > 0);
    for (i = 0; i < nScalefactors; i++) {
      h_sbr_data->iEnvelope[i] = add(h_sbr_data->iEnvelope[i], deltaExp); move16();
    }
  }
}



/*!
  \brief   Convert each envelope value from logarithmic to linear domain
*/
static void
requantizeEnvelopeData (HANDLE_SBR_FRAME_DATA h_sbr_data, Word16 ampResolution)
{
  Word16 i;
  Word16 mantissa;
  Word16 ampShift;
  Word16 exponent;

  ampShift = sub(1, ampResolution);

  assert(h_sbr_data->nScaleFactors > 0);
  for (i = 0; i < h_sbr_data->nScaleFactors; i++) {
    exponent = h_sbr_data->iEnvelope[i];                        move16();

    /* In case of the high amplitude resolution, 1 bit of the exponent gets lost by the shift.
       This will be compensated by a mantissa of 0.5*sqrt(2) instead of 0.5 if that bit is 1. */
    logic16(); test(); move16();
    mantissa = (exponent & ampShift) ? 0x5a82 : 0x4000;
    exponent = shr(exponent, ampShift);

    /*
      Mantissa was set to 0.5 (instead of 1.0, therefore increase exponent by 1).
      Multiply by L=nChannels=64 by increasing exponent by another 6.
      => Increase exponent by 7
    */
    exponent = add(exponent, add(7, NRG_EXP_OFFSET));

    /* Combine mantissa and exponent and write back the result */
    h_sbr_data->iEnvelope[i] = (mantissa & (Word16)MASK_M) | (exponent & (Word16)MASK_E);  logic16(); logic16(); logic16(); move16();

  }
}


/*!
  \brief   Build new reference energies from old ones and delta coded data
*/
static void
deltaToLinearPcmEnvelopeDecoding (HANDLE_SBR_HEADER_DATA hHeaderData,     /*!< Static control data */
                                  HANDLE_SBR_FRAME_DATA h_sbr_data,       /*!< pointer to current data */
                                  HANDLE_SBR_PREV_FRAME_DATA h_prev_data) /*!< pointer to previous data */
{
  Word16 i, domain, no_of_bands, band, freqRes;

  Word16 *  sfb_nrg_prev = h_prev_data->sfb_nrg_prev; 
  Word16 *  ptr_nrg = h_sbr_data->iEnvelope;

  Word16 offset;
  move16(); move16();
  
  offset = sub(shl(hHeaderData->hFreqBandData->nSfb[LO], 1), hHeaderData->hFreqBandData->nSfb[HI]);

  assert(h_sbr_data->frameInfo.nEnvelopes > 0);
  move16(); /*h_sbr_data->frameInfo.nEnvelopes*/
  for (i = 0; i < h_sbr_data->frameInfo.nEnvelopes; i++) {
    domain = h_sbr_data->domain_vec[i];                         move16();
    freqRes = h_sbr_data->frameInfo.freqRes[i];                 move16();

    no_of_bands = hHeaderData->hFreqBandData->nSfb[freqRes];    move16();

    test();
    if (sub(domain, FREQ) == 0)
    {
      mapLowResEnergyVal(*ptr_nrg, sfb_nrg_prev, offset, 0, freqRes);
      ptr_nrg++;
      for (band = 1; band < no_of_bands; band++) 
      {
        *ptr_nrg = add(*ptr_nrg, *(ptr_nrg-1)); move16();
        mapLowResEnergyVal(*ptr_nrg, sfb_nrg_prev, offset, band, freqRes);
        ptr_nrg++;
      }
    }
    else 
    {
      assert(no_of_bands > 0);
      for (band = 0; band < no_of_bands; band++) 
      {
        *ptr_nrg = add(*ptr_nrg, sfb_nrg_prev[indexLow2High(offset, band, freqRes)]); move16();
        mapLowResEnergyVal(*ptr_nrg, sfb_nrg_prev, offset, band, freqRes);
        ptr_nrg++;
      }
    }
  }
}


/*!
  \brief   Build new noise levels from old ones and delta coded data
*/
static void
decodeNoiseFloorlevels (HANDLE_SBR_HEADER_DATA hHeaderData,     /*!< Static control data */
                        HANDLE_SBR_FRAME_DATA h_sbr_data,       /*!< pointer to current data */
                        HANDLE_SBR_PREV_FRAME_DATA h_prev_data) /*!< pointer to previous data */
{
  Word16 i;
  Word16 nNfb;
  Word16 nNoiseFloorEnvelopes;
  Word16 offset;

  nNfb = hHeaderData->hFreqBandData->nNfb;                      move16();
  nNoiseFloorEnvelopes = h_sbr_data->frameInfo.nNoiseEnvelopes; move16();

  /* Decode first noise envelope */

  test();
  if (sub(h_sbr_data->domain_vec_noise[0], FREQ) == 0) {
    for (i = 1; i < nNfb; i++) {
      h_sbr_data->sbrNoiseFloorLevel[i] =
        add(h_sbr_data->sbrNoiseFloorLevel[i], h_sbr_data->sbrNoiseFloorLevel[i-1]);  move16();
    }
  }
  else {
    assert(nNfb > 0);
    for (i = 0; i < nNfb; i++) {
      h_sbr_data->sbrNoiseFloorLevel[i] =
        add(h_sbr_data->sbrNoiseFloorLevel[i], h_prev_data->prevNoiseLevel[i]); move16();
    }
  }

  /* If present, decode the second noise envelope */

  test();
  if (sub(nNoiseFloorEnvelopes, 1) > 0) {
    test();
    if (sub(h_sbr_data->domain_vec_noise[1], FREQ) == 0) {
      Word16 nNfb_2;
      nNfb_2 = shl(nNfb,1);
      for (i = add(nNfb,1); i < nNfb_2; i++) {
        h_sbr_data->sbrNoiseFloorLevel[i] =
          add(h_sbr_data->sbrNoiseFloorLevel[i], h_sbr_data->sbrNoiseFloorLevel[i-1]);  move16();
      }
    }
    else {
      assert(nNfb > 0);
      for (i = 0; i < nNfb; i++) {
        h_sbr_data->sbrNoiseFloorLevel[i+nNfb] =
          add(h_sbr_data->sbrNoiseFloorLevel[i+nNfb], h_sbr_data->sbrNoiseFloorLevel[i]); move16();
      }
    }
  }

  limitNoiseLevels(hHeaderData, h_sbr_data);

  /* Update prevNoiseLevel with the last noise envelope */
  assert(nNfb > 0);
  offset = shr(extract_l(L_mult(nNfb,sub(nNoiseFloorEnvelopes,1))),1);
  for (i = 0; i < nNfb; i++) {
    h_prev_data->prevNoiseLevel[i] = h_sbr_data->sbrNoiseFloorLevel[i + offset]; move16();
  }

  /* Requantize the noise floor levels in COUPLING_OFF-mode */
  test();
  if (sub(h_sbr_data->coupling,COUPLING_BAL) != 0) {
    Word16 nf_e, i_end;

    assert(nNoiseFloorEnvelopes*nNfb);
    i_end = shr(extract_l(L_mult(nNfb,nNoiseFloorEnvelopes)),1);
    for (i = 0; i < i_end; i++) {
      nf_e = sub(NOISE_FLOOR_OFFSET+1+NOISE_EXP_OFFSET, 
                 h_sbr_data->sbrNoiseFloorLevel[i]);
      /* +1 to compensate for a mantissa of 0.5 instead of 1.0 */

      h_sbr_data->sbrNoiseFloorLevel[i] = 
        add(0x4000,  /* mantissa */
            (nf_e & (Word16)MASK_E)); /* exponent */                    logic16();  move16();

    }
  }
}
