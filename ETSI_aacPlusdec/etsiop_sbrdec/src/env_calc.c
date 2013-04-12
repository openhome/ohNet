/*
   Envelope calculation
 */


#include <string.h>
#include <assert.h>
#include "env_calc.h"
#include "sbr_const.h"             /* Various defines */
#include "freq_sca.h"
#include "env_extr.h"
#include "ffr.h"
#include "sbr_ram.h"
#include "sbr_rom.h"
#include "intrinsics.h"
#include "basic_op.h"
#include "count.h"




static void equalizeFiltBufferExp(Word16 *filtBuffer_m,
                                  Word16 *filtBuffer_e,
                                  Word16 *NrgGain_m,
                                  Word16 *NrgGain_e,
                                  Word16  subbands);

static void updateFiltBuffer(Word16  *filtBuffer_m,
                             Word16  *filtBufferNoise_m,
                             Word16  *nrgGain_m,
                             Word16  *noiseLevel_m,
                             Word16   noSubbands);

static void rescaleNoiseLevels(Word16 *noiseLevel_m,
                               Word16 *pNoise_e,
                               Word16  new_e,
                               Word16  noSubbands);

static void calcNrgPerSubband(Word32    **analysBufferReal,
#ifndef LP_SBR_ONLY
                              Word32    **analysBufferImag,
#endif
                              Word16    lowSubband, Word16 highSubband,
                              Word16    start_pos,  Word16 next_pos,
                              Word16 frameExp,
                              Word16 *nrgEst_m,
                              Word16 *nrgEst_e,
                              Flag   bUseLP);

static void calcNrgPerSfb(Word32 **analysBufferReal,
#ifndef LP_SBR_ONLY
                          Word32 **analysBufferImag,
#endif
                          Word16 nSfb,
                          Word16 *freqBandTable,
                          Word16 start_pos,  Word16 next_pos,
                          Word16 maxQmfSubbandAac,
                          Word16 frameExp,
                          Word16 *nrg_est_m,
                          Word16 *nrg_est_e,
                          Flag   bUseLP);

static void calcSubbandGain(Word16  nrgRef_m,
                            Word16  nrgEst_m,
                            Word16  tmpNoise_m,

                            Word16 nrgRef_e,
                            Word16 nrgEst_e,
                            Word16 tmpNoise_e,

                            Flag   sinePresentFlag,
                            Flag   sineMapped,
                            Flag   noNoiseFlag,

                            Word16  *ptrNrgGain_m,
                            Word16  *ptrNrgGain_e,
                            Word16  *ptrNoiseLevel_m,
                            Word16  *ptrNoiseLevel_e,
                            Word16  *ptrNrgSine_m,
                            Word16  *ptrNrgSine_e);

static void calcAvgGain(Word16  *nrgRef_m,
                        Word16  *nrgRef_e,
                        Word16  *nrgEst_m,
                        Word16  *nrgEst_e,
                        Word16  lowSubband,
                        Word16  highSubband,
                        Word16  *sumRef_m,
                        Word16  *sumRef_e,
                        Word16  *ptrAvgGain_m,
                        Word16  *ptrAvgGain_e);

static void adjustTimeSlotLP(Word32  *ptrReal,
                             Word16  *gain_m,
                             Word16  *gain_e,
                             Word16  *noiseLevel_m,
                             Word16  *sineLevel_m,
                             Word16  *sineLevel_e,
                             Word16   noise_e,
                             Word16  *ptrHarmIndex,
                             Word16   lowSubbands,
                             Word16   noSubbands,
                             Word16   scale_change,
                             Word16   lowband_e,
                             Flag    noNoiseFlag,
                             Word16 *ptrPhaseIndex);

#ifndef LP_SBR_ONLY
static void adjustTimeSlot(Word32  *ptrReal,
                           Word32  *ptrImag,
                           Word16  *filtBuffer_m,
                           Word16  *filtBufferNoise_m,
                           Word16  *gain_m,
                           Word16  *gain_e,
                           Word16  *noiseLevel_m,
                           Word16  *sineLevel_m,
                           Word16  *sineLevel_e,
                           Word16   noise_e,
                           Word16  *ptrHarmIndex,
                           Word16  lowSubbands,
                           Word16  noSubbands,
                           Word16  scale_change,
                           Word16  smooth_ratio,
                           Flag    noNoiseFlag,
                           Word16  *ptrPhaseIndex);
#endif

/*!
  \brief     Map sine flags from bitstream to QMF bands
*/
static void mapSineFlags(Word16 *freqBandTable, /*!< Band borders (there's only 1 flag per band) */
                         Word16 nSfb,                     /*!< Number of bands in the table */
                         Flag *addHarmonics,           /*!< vector with 1 flag per sfb */
                         Flag *harmFlagsPrev,           /*!< Packed 'addHarmonics' */
                         Word16 tranEnv,                  /*!< Transient position */
                         Word16 *sineMapped)             /*!< Resulting vector of sine start positions for each QMF band */
                         
{
  /*unsigned int mask;*/
  Word16 mask;
  Word16 qmfband2, li, ui, i;
  Word16 lowSubband2;
  Word16 bitcount;
  Word16 oldflags;
  Word16 newflags;

  lowSubband2 = shl(freqBandTable[0], 1);
  bitcount = 0;                                         move16();
  oldflags = 0;                                         move16();
  newflags = 0;                                         move16();

  /* Reset the output vector first:  MAX_ENVELOPES means 'no sine' */
  for (i=MAX_FREQ_COEFFS-1; i>=0; i--) {
    sineMapped[i] = MAX_ENVELOPES;                      move16();
  }

  assert(nSfb > 0);
  for (i=sub(nSfb,1); i>=0; i--) {
    /* Lower limit of the current scale factor band. */
    li = freqBandTable[i];                              move16();
    /* Upper limit of the current scale factor band. */
    ui = freqBandTable[i+1];                            move16();
    mask = shl(1, bitcount);

    test();
    if (bitcount == 0) {
      oldflags = *harmFlagsPrev;        move16(); /* Fetch 16 of the old flags */
      newflags = 0;                     move16(); 
    }

    test();
    if ( addHarmonics[i] ) {               /* There is a sine in this band */
      newflags |= mask;                 logic16(); /* Set flag */

      qmfband2 = sub(add(ui, li), lowSubband2); /* 2 times the QMF-band where the sine will be added. */
      /*
        If there was a sine in the last frame, let it continue from the first envelope on
        else start at the transient position.
      */
      logic16(); test();
      if (oldflags & mask) {
        sineMapped[shr(qmfband2,1)] = 0;                move16();
      }
      else {
        sineMapped[shr(qmfband2,1)] = tranEnv;   move16();
      }
    }

    bitcount = add(bitcount, 1);
    test(); test(); 
    if ((sub(bitcount,16) == 0) || i==0) {
      bitcount = 0;                                     move16();
      *harmFlagsPrev++ = newflags;                      move16();
    }
  }
}



/*!
  \brief     Reduce gain-adjustment induced aliasing for real valued filterbank.
*/
static void
aliasingReduction(Word16* degreeAlias,       /*!< estimated aliasing for each QMF channel */
                  Word16* nrgGain_m,         /*!< subband gains to be modified (mantissas) */
                  Word16* nrgGain_e,         /*!< subband gains to be modified (exponents) */
                  Word16* nrgEst_m,          /*!< subband energy before amplification (mantissas) */
                  Word16* nrgEst_e,          /*!< subband energy before amplification (exponents) */
                  Word16* useAliasReduction, /*!< synthetic sine engergy for each subband, used as flag */
                  Word16  noSubbands)        /*!< number of QMF channels to process */
{
  Word16 group, grouping, index, noGroups, k;
  Word16 groupVector[MAX_FREQ_COEFFS];

  grouping = 0;                                         move16();
  index = 0;                                            move16();

  /* Calculate grouping*/
  sub(noSubbands,1);
  for (k = 0; k < noSubbands-1; k++ ){
    test(); test();
    if ( (degreeAlias[k + 1] != 0) && useAliasReduction[k] ) {
      test();
      if(grouping==0){
        groupVector[index] = k;                         move16();
        grouping = 1;                                   move16();
        index++;
      }
      else{
        test();
        if(sub(add(groupVector[index-1], 3), k) == 0){
          groupVector[index] = add(k, 1);
          grouping = 0;                                 move16();
          index++;
        }
      }
    }
    else{
      test();
      if(grouping){
        test();
        if(useAliasReduction[k]) {
          groupVector[index] = add(k, 1);               move16();
        }
        else {
          groupVector[index] = k;                       move16();
        }
        grouping = 0;                                   move16();
        index++;
      }
    }
  }        

  test();
  if(grouping){
    groupVector[index] = noSubbands;                    move16();
    index++;
  }
  noGroups = shr(index, 1);


  /*Calculate new gain*/
  move16(); /* initialize the counter 2*group */
  for (group = 0; group < noGroups; group++) {
    Word16  nrgOrig_m = 0;     /* Original signal energy in current group of bands */
    Word16  nrgOrig_e = 0;
    Word16  nrgAmp_m = 0;      /* Amplified signal energy in group (using current gains) */
    Word16  nrgAmp_e = 0;
    Word16  nrgMod_m = 0;      /* Signal energy in group when applying modified gains */
    Word16  nrgMod_e = 0;
    Word16  groupGain_m;       /* Total energy gain in group */
    Word16  groupGain_e;
    Word16  compensation_m;    /* Compensation factor for the energy change when applying modified gains */
    Word16   compensation_e;

    Word16 startGroup = groupVector[2*group];
    Word16 stopGroup  = groupVector[2*group+1];

    move16(); move16(); move16(); move16();
    move16(); move16(); move16(); move16();

    /* Calculate total energy in group before and after amplification with current gains: */
    for(k = startGroup; k < stopGroup; k++){
      /* Get original band energy */
      Word16  tmp_m = nrgEst_m[k];
      Word16  tmp_e = nrgEst_e[k];

      move16(); /* init tmp_m */
      move16(); /* init tmp_e from a 8-bit aligned data */

      ffr_add_MantExp(tmp_m, tmp_e, nrgOrig_m, nrgOrig_e, &nrgOrig_m, &nrgOrig_e);

      /* Multiply band energy with current gain */
      tmp_m = mult(tmp_m, nrgGain_m[k]);
      tmp_e = add(tmp_e, nrgGain_e[k]);

      ffr_add_MantExp(tmp_m, tmp_e, nrgAmp_m, nrgAmp_e, &nrgAmp_m, &nrgAmp_e);
    }

    /* Calculate total energy gain in group */
    ffr_divide_MantExp(nrgAmp_m, nrgAmp_e,
                       nrgOrig_m, nrgOrig_e,
                       &groupGain_m, &groupGain_e);    

    for(k = startGroup; k < stopGroup; k++){
      Word16  tmp_m;
      Word16  tmp_e;

      Word16 alpha = degreeAlias[k];
      test();
      if (sub(k, sub(noSubbands,1)) < 0) {
        test();
        if (sub(degreeAlias[k + 1], alpha) > 0) {
          alpha = degreeAlias[k + 1];                   move16();
        }
      }

      /* Modify gain depending on the degree of aliasing */
      ffr_add_MantExp( mult(alpha, groupGain_m), groupGain_e,
                       mult(sub(0x7fff,alpha), nrgGain_m[k]), nrgGain_e[k],
                       &nrgGain_m[k], &nrgGain_e[k] );

      /* Apply modified gain to original energy */
      tmp_m = mult(nrgGain_m[k], nrgEst_m[k]);
      tmp_e = add(nrgGain_e[k], nrgEst_e[k]);

      /* Accumulate energy with modified gains applied */
      ffr_add_MantExp( tmp_m, tmp_e,
                       nrgMod_m, nrgMod_e,
                       &nrgMod_m, &nrgMod_e );
    }

    /* Calculate compensation factor to retain the energy of the amplified signal */
    ffr_divide_MantExp(nrgAmp_m, nrgAmp_e,
                       nrgMod_m, nrgMod_e,
                       &compensation_m, &compensation_e);    

    /* Apply compensation factor to all gains of the group */
    for(k = startGroup; k < stopGroup; k++){
      nrgGain_m[k] = mult(nrgGain_m[k], compensation_m);         move16();
      nrgGain_e[k] = (Word8)add(nrgGain_e[k], compensation_e);   move16();
    }
  }
}


/*!
  \brief  Apply spectral envelope to subband samples
*/
void
calculateSbrEnvelope (SBR_SCALE_FACTOR  *sbrScaleFactor,  /*!< Scaling factors */
                      HANDLE_SBR_CALCULATE_ENVELOPE h_sbr_cal_env, /*!< Handle to struct filled by the create-function */
                      HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
                      HANDLE_SBR_FRAME_DATA  hFrameData,  /*!< Control data of current frame */
                      HANDLE_SBR_PREV_FRAME_DATA  hPrevFrameData, /*!< Control data of previous frame */
                      Word32 **analysBufferReal_m,           /*!< Real part of subband samples to be processed */
#ifndef LP_SBR_ONLY
                      Word32 **analysBufferImag_m,           /*!< Imag part of subband samples to be processed */
#endif
                      Word16 *degreeAlias,                  /*!< Estimated aliasing for each QMF channel */
                      Flag bUseLP
                      )
{
  Word16 c, i, j, k, m;
  Word16 envNoise;
  Word16 start_pos, stop_pos, freq_res;
  Word16 nEnvelopes = hFrameData->frameInfo.nEnvelopes;
  Word16 *borders = hFrameData->frameInfo.borders;

  Word16  *noiseLevels = hFrameData->sbrNoiseFloorLevel;
  HANDLE_FREQ_BAND_DATA hFreq = hHeaderData->hFreqBandData;

  Flag noNoiseFlag;
  Word16 smooth_length;

  const Word16 *nSfb = hFreq->nSfb;
  const Word16 noNoiseBands = hFreq->nNfb;

  Word16 lowSubband = hFreq->lowSubband;
  Word16 highSubband = hFreq->highSubband;
  Word16 noSubbands;
  Word16 skipBands;

  Word16 first_start;

  Word16  limiterGain_m;
  Word16  limiterGain_e, maxSfbNrg_e;
  Word16  charTemp;  /*! \var charTemp  */

  Word16  nrgRef_m[MAX_FREQ_COEFFS];
  Word16  nrgRef_e[MAX_FREQ_COEFFS];
  Word16  nrgEst_m[MAX_FREQ_COEFFS];
  Word16  nrgEst_e[MAX_FREQ_COEFFS];
  Word16  nrgGain_m[MAX_FREQ_COEFFS];
  Word16  noiseLevel_m[MAX_FREQ_COEFFS];
  Word16  nrgGain_e[MAX_FREQ_COEFFS], noiseLevel_e[MAX_FREQ_COEFFS];
  Word16  nrgSine_m[MAX_FREQ_COEFFS];
  Word16  nrgSine_e[MAX_FREQ_COEFFS];
  Word16  sineMapped[MAX_FREQ_COEFFS];
  Word16  sumRef_e;

  Word16   input_e;
  Word16   ov_adj_e;
  Word16   adj_e;
  Word16   output_e;
  Word16   final_e;
  Word16   noise_e;

  Word16   useAliasReduction[64];

  move16(); move16(); move16(); move16();
  move16(); move16(); move16(); move16();

  m = 0;                                                        move16();
  envNoise = 0;                                                 move16();
  nEnvelopes = hFrameData->frameInfo.nEnvelopes;                move16();
  borders = hFrameData->frameInfo.borders;                      move16();
  noSubbands = sub(highSubband, lowSubband);
  skipBands = sub(hFrameData->maxQmfSubbandAac, lowSubband);
  first_start = shr(extract_l(L_mult(borders[0], SBR_TIME_STEP)), 1);
  input_e = (Word8)sub(15, sbrScaleFactor->hb_scale);
  ov_adj_e = (Word8)sub(15, sbrScaleFactor->ov_hb_scale);
  adj_e = 0;                                                    move16();
  final_e = 0;                                                  move16();

  limiterGain_m = sbr_limGains_m[hHeaderData->limiterGains];    move16();
  limiterGain_e = sbr_limGains_e[hHeaderData->limiterGains];    move16();


  /*
    Extract sine flags for all QMF bands
  */
  mapSineFlags(hFreq->freqBandTable[HI],
               hFreq->nSfb[HI],
               hFrameData->addHarmonics,
               h_sbr_cal_env->harmFlagsPrev,
               hFrameData->frameInfo.tranEnv,
               sineMapped);


  /*
    Scan for maximum in bufferd noise levels.
  */
  {
    Word16 maxNoise;
    Word16 firstBand;

    test();
    if (sub(hPrevFrameData->maxQmfSubbandAac, hFrameData->maxQmfSubbandAac) > 0)
      firstBand = sub(hPrevFrameData->maxQmfSubbandAac, lowSubband);
    else
      firstBand = sub(hFrameData->maxQmfSubbandAac, lowSubband);

    maxNoise = 0;                                               move16();
    for (i=firstBand; i<noSubbands; i++) {
      test();
      if (sub(h_sbr_cal_env->filtBufferNoise_m[i], maxNoise) > 0) {
        maxNoise = h_sbr_cal_env->filtBufferNoise_m[i];         move16();
      }
    }
    adj_e = sub(sub(h_sbr_cal_env->filtBufferNoise_e, ffr_norm32(maxNoise)), 16);
  }

  /*
    Scan for maximum reference energy
  */

  assert(nEnvelopes > 0);
  for (i = 0; i < nEnvelopes; i++) {
    maxSfbNrg_e = NRG_EXP_OFFSET- SHORT_BITS; /* start value for maximum search */

    /* Fetch frequency resolution for current envelope: */
    freq_res = hFrameData->frameInfo.freqRes[i];                move16();

    assert(nSfb[freq_res] > 0);
    for ( j=0; j<nSfb[freq_res]; j++) {
      charTemp = extract_l((hFrameData->iEnvelope[m] & MASK_E));logic16();
      test();
      if (sub(charTemp, maxSfbNrg_e) > 0) {
        maxSfbNrg_e = charTemp;                                 move16();
      }
      m = add(m, 1);
    }
    maxSfbNrg_e = sub(maxSfbNrg_e, NRG_EXP_OFFSET);

    /* Energy -> magnitude (sqrt halfens exponent) */
    charTemp = (Word8)shr(add(maxSfbNrg_e, 13), 1);

    test();
    if (sub(borders[i] /* start_pos */, SBR_TIME_SLOTS) < 0) {
      /* This envelope affects timeslots that belong to the output frame */
      if (sub(charTemp,adj_e) > 0) {
        adj_e = charTemp;                                       move16();
      }
    }
    test();
    if (sub(borders[i+1] /* stop_pos */, SBR_TIME_SLOTS) > 0) {
      /* This envelope affects timeslots after the output frame */
      test();
      if (sub(charTemp,final_e) > 0) {
        final_e = charTemp;                                     move16();
      }
    }
  }


  m = 0;                                                        move16();
  /*
    Calculate adjustment factors and apply them for every envelope.
  */
  assert(nEnvelopes > 0);
  for (i = 0; i < nEnvelopes; i++) {

    /*
      Helper variables.
    */
    start_pos = shr(extract_l(L_mult(SBR_TIME_STEP, borders[i])), 1);     /* Start-position in time (subband sample) for current envelope. */
    stop_pos = shr(extract_l(L_mult(SBR_TIME_STEP, borders[i+1])), 1);    /* Stop-position in time (subband sample) for current envelope. */
    freq_res = hFrameData->frameInfo.freqRes[i];  /* Frequency resolution for current envelope. */ move16();

    /* If the start-pos of the current envelope equals the stop pos of the current
       noise envelope, increase the pointer (i.e. choose the next noise-floor).*/
    test();
    if (sub(borders[i], hFrameData->frameInfo.bordersNoise[envNoise+1]) == 0){
      noiseLevels += noNoiseBands;   /* The noise floor data is stored in a row [noiseFloor1 noiseFloor2...].*/
      envNoise = add(envNoise, 1);
    }

    test(); test();
    if(sub(i,hFrameData->frameInfo.tranEnv)==0 || sub(i,h_sbr_cal_env->prevTranEnv)==0) {   /* attack */
      noNoiseFlag = 1;                                          move16();
      smooth_length = 0;  /* No smoothing on attacks! */        move16();
    }
    else {
      noNoiseFlag = 0;                                          move16();
      smooth_length = shl(sub(1, hHeaderData->smoothingLength), 2);  /* can become either 0 or 4 */
    }


    /*
      Energy estimation in transposed highband.
    */

    test();
    if (hHeaderData->interpolFreq)
      calcNrgPerSubband(analysBufferReal_m,
#ifndef LP_SBR_ONLY
                        analysBufferImag_m,
#endif
                        hFrameData->maxQmfSubbandAac, highSubband,
                        start_pos, stop_pos,
                        input_e,
                        nrgEst_m,
                        nrgEst_e,
                        bUseLP);
    else
      calcNrgPerSfb(analysBufferReal_m,
#ifndef LP_SBR_ONLY
                    analysBufferImag_m,
#endif
                    nSfb[freq_res],
                    hFreq->freqBandTable[freq_res],
                    start_pos, stop_pos,
                    hFrameData->maxQmfSubbandAac,
                    input_e,
                    nrgEst_m,
                    nrgEst_e,
                    bUseLP);

    /*
      Calculate subband gains
    */
    {
      Word16 * table = hFreq->freqBandTable[freq_res];
      Word16 uiNoise = hFreq->freqBandTableNoise[1]; /*! Upper limit of the current noise floor band. */
      Word16 noiseBandIndex = 0;
      Word16 cc=0;
      move16(); move16(); move16(); move16();
      c = 0;                                                    move16();

      assert(nSfb[freq_res] > 0);
      for (j = 0; j < nSfb[freq_res]; j++) {
        Word16 li = table[j];
        Word16 ui = table[j+1];
        Flag   sinePresentFlag = 0;                             move16();

        assert(ui > li);
        for (k=li; k<ui; k++) {
          test();
          if(sub(i, sineMapped[cc]) >= 0) {
            sinePresentFlag = 1;                                move16();
          }
          cc++;
        }
        for (k=li; k<ui; k++) {
          test();
          if(sub(k, uiNoise) >= 0){
            noiseBandIndex = add(noiseBandIndex, 1);
            uiNoise = hFreq->freqBandTableNoise[noiseBandIndex+1];     move16();
          }

          test();
          if (bUseLP) {

            test();
            if (sinePresentFlag) {
              useAliasReduction[k-lowSubband] = 0;              move16();
            }
            else {
              useAliasReduction[k-lowSubband] = 1;              move16();
            }
          }

          test();
          if (sub(k, hFrameData->maxQmfSubbandAac) >= 0) {
            Word16  tmpNoise_m;
            Word16  tmpNoise_e;

            nrgRef_e[c] = sub((hFrameData->iEnvelope[m] & (Word16)MASK_E), NRG_EXP_OFFSET);     logic16();
            nrgRef_m[c] = hFrameData->iEnvelope[m] & MASK_M;    logic16();

            nrgSine_e[c] = 0;                                   move16();
            nrgSine_m[c] = 0;                                   move16();

            tmpNoise_m = extract_l(noiseLevels[noiseBandIndex] & MASK_M);  logic16();
            tmpNoise_e = extract_l(noiseLevels[noiseBandIndex] & MASK_E);  logic16();
            tmpNoise_e = sub(tmpNoise_e, NOISE_EXP_OFFSET);

            test(); move16();
            calcSubbandGain(nrgRef_m[c],
                            nrgEst_m[c],
                            tmpNoise_m,

                            nrgRef_e[c],
                            nrgEst_e[c],
                            tmpNoise_e,
                            sinePresentFlag,
                            sub(i, sineMapped[c+skipBands]) >= 0 ? (Flag)1 : (Flag)0,
                            noNoiseFlag,

                            &nrgGain_m[c], &nrgGain_e[c],
                            &noiseLevel_m[c], &noiseLevel_e[c],
                            &nrgSine_m[c], &nrgSine_e[c]
                            );
            c++;
          }
        }
        m++;
      }
    }



    /*
      Noise limiting
    */

    assert(hFreq->noLimiterBands > 0);
    for (c = 0; c < hFreq->noLimiterBands; c++) {
      Word16  maxGain_m;
      Word16  sumRef_m;
      Word16  maxGain_e;
      Word32  maxTemp;
      Word16  startBand;
      Word16  stopBand;
      test();
      if (sub(hFreq->limiterBandTable[c], skipBands) > 0) {
        startBand = sub(hFreq->limiterBandTable[c], skipBands);
      }
      else {
        startBand = 0;                                          move16();
      }
      test();
      if (sub(hFreq->limiterBandTable[c+1], skipBands) > 0) {
        stopBand = sub(hFreq->limiterBandTable[c+1], skipBands);
      }
      else {
        stopBand = 0;                                          move16();
      }

      test();
      if (sub(startBand, stopBand) < 0) {

        calcAvgGain(nrgRef_m, nrgRef_e,
                    nrgEst_m, nrgEst_e,
                    startBand, stopBand,
                    &sumRef_m, &sumRef_e,
                    &maxGain_m, &maxGain_e);

        /* Multiply maxGain with limiterGain: */
        maxTemp = L_mult(maxGain_m, limiterGain_m);
        maxGain_e = (Word8)add(maxGain_e, limiterGain_e);

        charTemp = (Word8)ffr_norm32(maxTemp);

        maxGain_e = (Word8)sub(maxGain_e, charTemp);
        maxGain_m = extract_h(L_shl(maxTemp, charTemp));
        test();
        if (sub(maxGain_e, MAX_GAIN_EXP) >= 0) { /* upper limit (e.g. 96 dB) */
          maxGain_m = 0x3000;                              move16();
          maxGain_e = MAX_GAIN_EXP;                             move16();
        }


        /* Every subband gain is compared to the scaled "average gain"
         and limited if necessary: */
        assert(startBand < stopBand);
        for (k = startBand; k < stopBand; k++) {
          Word16  noiseAmp_m;
          Word16  noiseAmp_e;

          test(); test(); test();
          if ( (sub(nrgGain_e[k],maxGain_e)>0) || (sub(nrgGain_e[k],maxGain_e)==0 && sub(nrgGain_m[k],maxGain_m)>0) ) {
            ffr_divide_MantExp(maxGain_m, maxGain_e, nrgGain_m[k], nrgGain_e[k], &noiseAmp_m, &noiseAmp_e);  
            noiseLevel_m[k] = extract_h(L_shl( L_mult(noiseLevel_m[k], noiseAmp_m), noiseAmp_e));

            nrgGain_m[k] = maxGain_m;                           move16();
            nrgGain_e[k] = maxGain_e;                           move16();
          }
        }

        /*
          Boost gain
        */
        {
          Word16  boostGain_m;
          Word16  accu_m;
          Word16  boostGain_e, accu_e;

          accu_m = 0;                                           move16();
          accu_e = 0;                                           move16();

          /*
            Calculate and apply boost factor for each limiter band:
          */
          for (k = startBand; k < stopBand; k++) {
            Word16  tmp_m;
            Word16  tmp_e = 0;                                  move16();

            /* 1.a  Add energy of adjusted signal (using preliminary gain) */
            tmp_m = mult(nrgGain_m[k], nrgEst_m[k]);
            tmp_e = add(nrgGain_e[k], nrgEst_e[k]);
            ffr_add_MantExp(tmp_m, tmp_e, accu_m, accu_e, &accu_m, &accu_e);

            /* 1.b  Add sine energy (if present) */
            test();
            if(nrgSine_m[k] != 0) {
              ffr_add_MantExp(nrgSine_m[k], nrgSine_e[k], accu_m, accu_e, &accu_m, &accu_e);
            } 
            else {
              /* 1.c  Add noise energy (if present) */
              test();
              if(noNoiseFlag == 0) {
                ffr_add_MantExp(noiseLevel_m[k], noiseLevel_e[k], accu_m, accu_e, &accu_m, &accu_e);
              }
            }
          }

          /* 2.a  Calculate ratio of wanted energy and accumulated energy */
          ffr_divide_MantExp(sumRef_m, sumRef_e,
                             accu_m, accu_e,
                             &boostGain_m, &boostGain_e);    

          /* 2.b  Limit the boost factor to +4 dB */
          test(); test(); test();
          if(sub(boostGain_e,2)>0 || (sub(boostGain_e,2)==0 && sub(boostGain_m,0x5061)>0 )) {
            boostGain_m = 0x5061;                    move16();
            boostGain_e = 2;                                    move16();
          }

          /* 3.  Multiply all signal components with the boost factor */
          for (k = startBand; k < stopBand; k++) {
            nrgGain_m[k] = mult(nrgGain_m[k], boostGain_m);
            nrgGain_e[k] = add(nrgGain_e[k], boostGain_e);

            nrgSine_m[k] = mult(nrgSine_m[k], boostGain_m);
            nrgSine_e[k] = add(nrgSine_e[k], boostGain_e);

            noiseLevel_m[k] = mult(noiseLevel_m[k], boostGain_m);
            noiseLevel_e[k] = add(noiseLevel_e[k], boostGain_e);
          }
        }
      }
    }

    test();
    if (bUseLP) {
      aliasingReduction(degreeAlias+lowSubband,
                        nrgGain_m,
                        nrgGain_e,
                        nrgEst_m,
                        nrgEst_e,
                        useAliasReduction,
                        noSubbands);
    }

    /* For the timeslots within the range for the output frame,
       use the same scale for the noise levels.
    */
    test();
    if (sub(start_pos, MAX_COLS) < 0) {
      noise_e = adj_e;                                           move16();
    }
    else {
      noise_e = final_e;                                         move16();
    }


    /*
      Convert energies to amplitude levels
    */
    assert(noSubbands-skipBands >= 1);
    for (k=0; k<noSubbands-skipBands; k++) {
      Word16 shift;

      ffr_sqrt_MantExp(&nrgSine_m[k], &nrgSine_e[k]);
      ffr_sqrt_MantExp(&nrgGain_m[k], &nrgGain_e[k]);
      ffr_sqrt_MantExp(&noiseLevel_m[k], &noiseLevel_e[k]);

      /* Shift noise-level so that it fits the scale of the attenuated
         subband samples for the timeslots going into the QMF-synthesis. */
      shift = sub(noise_e, noiseLevel_e[k]);
      /* Compensate for implicit factor 1/16 in the randomPhase table */
      shift = sub(shift, 4);
      noiseLevel_m[k] = shr(noiseLevel_m[k], shift);             move16();
    }


    /*
      Apply calculated gains and adaptive noise 
    */
    {
      Word16  l;
      Word8   scale_change;

      /* Initialize smoothing buffers with the first valid values */
      test();
      if (h_sbr_cal_env->startUp) {
        h_sbr_cal_env->filtBufferNoise_e = noise_e;             move16();

        for (k = skipBands; k < noSubbands; k++) {
          h_sbr_cal_env->filtBuffer_e[k] = nrgGain_e[k-skipBands];     move16();
          h_sbr_cal_env->filtBufferNoise_m[k] = noiseLevel_m[k-skipBands];      move16();
          h_sbr_cal_env->filtBuffer_m[k] = nrgGain_m[k-skipBands];     move16();
        }

        h_sbr_cal_env->startUp = 0;                             move16();
      }

      equalizeFiltBufferExp(&h_sbr_cal_env->filtBuffer_m[skipBands],  /* buffered */
                            &h_sbr_cal_env->filtBuffer_e[skipBands],  /* buffered */
                            nrgGain_m,     /* current  */
                            nrgGain_e,     /* current  */
                            sub(noSubbands, skipBands));


      assert(stop_pos - start_pos >= 2);
      for (l = start_pos; l < stop_pos; l++) {

        test();
        if (sub(l,MAX_COLS) < 0) {
          /* This timeslot is located within the first part of the processing buffer
             and will be fed into the QMF-synthesis for the current frame.
          */
          scale_change = (Word8)sub(adj_e, input_e);
        }
        else {
          /* This timeslot will not yet be fed into the QMF so we do not care
             about the adj_e. */
          scale_change = (Word8)sub(final_e, input_e);
        }

        test(); test();
        if ( (sub(l,MAX_COLS)==0) && (sub(start_pos,MAX_COLS)<0) ) {
          /* Update scale of noise levels when reaching the part of the buffer
             that will be synthesized in the next frame */
          rescaleNoiseLevels(noiseLevel_m,
                             &noise_e,    /* current scale */
                             final_e,     /* desired scale */
                             noSubbands - skipBands);
        }

        /* Adapt exponent of buffered noise levels to the current exponent
           so they can easily be smoothed */
        rescaleNoiseLevels(h_sbr_cal_env->filtBufferNoise_m, /* buffered */
                           &h_sbr_cal_env->filtBufferNoise_e, /* buffered */
                           noise_e,      /* current  */
                           noSubbands);

        
        test();
        if (bUseLP) {
          Word32 *analysBufferReal_m_l;
          analysBufferReal_m_l = analysBufferReal_m[l];  move16();
          adjustTimeSlotLP(&analysBufferReal_m_l[hFrameData->maxQmfSubbandAac],
                            nrgGain_m,
                            nrgGain_e,
                            noiseLevel_m,
                            nrgSine_m,
                            nrgSine_e,
                            sub(noise_e, 16),
                            &h_sbr_cal_env->harmIndex,
                            hFrameData->maxQmfSubbandAac,
                            sub(noSubbands,skipBands),
                            scale_change,
                            sub(15, sbrScaleFactor->lb_scale),
                            noNoiseFlag,
                            &h_sbr_cal_env->phaseIndex);
        }
#ifndef LP_SBR_ONLY
        else {

          Word16  smooth_ratio;
          Word32 *analysBufferReal_m_l, *analysBufferImag_m_l;
          analysBufferReal_m_l = analysBufferReal_m[l];  move16();
          analysBufferImag_m_l = analysBufferImag_m[l];  move16();

          /* Prevent the smoothing filter from running on constant levels */
          test();
          if (sub(sub(l,start_pos),smooth_length) < 0) {
            smooth_ratio = sbr_smoothFilter[sub(l,start_pos)];  move16();
          }
          else {
            smooth_ratio = 0;                                   move16();
          }
          
          adjustTimeSlot(&analysBufferReal_m_l[hFrameData->maxQmfSubbandAac],
                         &analysBufferImag_m_l[hFrameData->maxQmfSubbandAac],
                         &h_sbr_cal_env->filtBuffer_m[skipBands],
                         &h_sbr_cal_env->filtBufferNoise_m[skipBands],
                          nrgGain_m,
                          nrgGain_e,
                          noiseLevel_m,
                          nrgSine_m,
                          nrgSine_e,
                          sub(noise_e, 16),
                          &h_sbr_cal_env->harmIndex,
                          hFrameData->maxQmfSubbandAac,
                          sub(noSubbands,skipBands),
                          scale_change,
                          smooth_ratio,
                          noNoiseFlag,
                          &h_sbr_cal_env->phaseIndex);
        }
#endif

      }

      updateFiltBuffer(h_sbr_cal_env->filtBuffer_m + skipBands,
                       h_sbr_cal_env->filtBufferNoise_m + skipBands,
                       nrgGain_m,
                       noiseLevel_m,
                       sub(noSubbands, skipBands));
    }
  }

  /* Rescale output samples */
  {
    Word16 ov_reserve, reserve;

    ov_reserve = reserve = 0;                                   move16(); move16();

#ifndef MONO_ONLY
    test();
    if (sub(hHeaderData->channelMode,PS_STEREO) == 0) {
      /* Use optimum scale when applying PS to the spectral data
         1. Determine headroom in old adjusted samples */
      ov_reserve = expSubbandSamples(analysBufferReal_m,
                                     analysBufferImag_m,
                                     hFrameData->maxQmfSubbandAac,
                                     highSubband,
                                     0,
                                     first_start,
                                     bUseLP);

      /* 2. Determine headroom in new adjusted samples */
      reserve = expSubbandSamples(analysBufferReal_m,
                                  analysBufferImag_m,
                                  hFrameData->maxQmfSubbandAac,
                                  highSubband,
                                  first_start,
                                  MAX_COLS,
                                  bUseLP);
    }
#endif

    /* Determine common output exponent */
    test();
    if (sub(sub(ov_adj_e,ov_reserve), sub(adj_e,reserve)) > 0) /* set output_e to the maximum */ 
      output_e = (Word8)sub(ov_adj_e, ov_reserve);
    else
      output_e = (Word8)sub(adj_e, reserve);

    /* Rescale old samples */
    rescaleSubbandSamples(analysBufferReal_m,
#ifndef LP_SBR_ONLY
                          analysBufferImag_m,
#endif
                          hFrameData->maxQmfSubbandAac,
                          highSubband,
                          0, first_start,
                          sub(ov_adj_e, output_e),
                          bUseLP);

    /* Rescale new samples */
    rescaleSubbandSamples(analysBufferReal_m,
#ifndef LP_SBR_ONLY
                          analysBufferImag_m,
#endif
                          hFrameData->maxQmfSubbandAac,
                          highSubband,
                          first_start, MAX_COLS,
                          sub(adj_e, output_e),
                          bUseLP);
  }

  /* Update hb_scale */
  sbrScaleFactor->hb_scale = sub(15, output_e);                 move16();

  /* Save the current final exponent for the next frame: */
  sbrScaleFactor->ov_hb_scale = sub(15, final_e);               move16();


  /* We need to remember to the next frame that the transient
     will occur in the first envelope (if tranEnv == nEnvelopes). */
  test();
  if(sub(hFrameData->frameInfo.tranEnv, nEnvelopes) == 0) {
    h_sbr_cal_env->prevTranEnv = 0;                             move16();
  }
  else {
    h_sbr_cal_env->prevTranEnv = -1;                            move16();
  }

}


/*!
  \brief   Create envelope instance
*/
Word16
createSbrEnvelopeCalc (HANDLE_SBR_CALCULATE_ENVELOPE hs,   /*!< pointer to envelope instance */
                       HANDLE_SBR_HEADER_DATA hHeaderData, /*!< static SBR control data, initialized with defaults */
                       Word16 chan)                           /*!< Channel for which to assign buffers */
{
  Word16 err;
  Word16 i;

  err = 0;                                              move16();

  /* Clear previous missing harmonics flags */
  for (i=0; i<(MAX_FREQ_COEFFS+15)/16; i++) {
    hs->harmFlagsPrev[i] = 0;                           move16();
  }
  hs->harmIndex = 0;                                    move16();

  /*
    Setup pointers for time smoothing.
    The buffer itself will be initialized later triggered by the startUp-flag.
  */
  hs->filtBuffer_m      = sbr_GainSmooth_m[chan];       move16();
  hs->filtBufferNoise_m = sbr_NoiseSmooth_m[chan];      move16();
  hs->filtBuffer_e = sbr_GainSmooth_e[chan];            move16();
  hs->prevTranEnv = -1;                                 move16();


  /* initialization */
  resetSbrEnvelopeCalc(hs);

  test();
  if (chan==0) { /* do this only once */
    err = resetFreqBandTables(hHeaderData);
  }

  return err;
}


/*!
  \brief   Reset envelope instance
*/
void
resetSbrEnvelopeCalc (HANDLE_SBR_CALCULATE_ENVELOPE hCalEnv) /*!< pointer to envelope instance */
{
  hCalEnv->phaseIndex = 0;                              move16();
  hCalEnv->filtBufferNoise_e = 0;                       move16();

  hCalEnv->startUp = 1;                                 move16();
}


/*!
  \brief  Equalize exponents of the buffered gain values and the new ones
*/
static void equalizeFiltBufferExp(Word16 *filtBuffer_m, /*!< mantissas of bufferd gains */
                                  Word16 *filtBuffer_e, /*!< exponents of bufferd gains */
                                  Word16 *nrgGain_m,    /*!< mantissas of gains for current envelope */
                                  Word16 *nrgGain_e,    /*!< exponents of gains for current envelope */
                                  Word16 subbands)      /*!< Number of QMF subbands */
{
  Word16   band;
  Word16  diff;

  assert(subbands >= 1);
  for (band=0; band<subbands; band++){
    diff = sub(nrgGain_e[band], filtBuffer_e[band]);
    test();
    if (diff>0) {
      /* New gain is bigger, use its exponent */
      filtBuffer_e[band] = add(filtBuffer_e[band], diff);
      /* Compensate for the scale change by shifting the mantissa. */

      filtBuffer_m[band] = shr(filtBuffer_m[band], diff);
    }
    else {
      test();
      if (diff<0) {
        /* The buffered gains seem to be larger, but maybe there
           are some unused bits left in the mantissa */
        Word16 temp, reserve = SHORT_BITS;              move16();
        temp = sub(ffr_norm32(filtBuffer_m[band]), 16);

        test();
        if (sub(temp,reserve) < 0) {
          reserve = temp;                               move16();
        }

        test();
        if (add(diff,reserve) >= 0) {
          /* There is enough space in the buffered mantissa so
             that we can take the new exponent as common.
             */
          filtBuffer_m[band] = shr(filtBuffer_m[band], diff);   move16();
          filtBuffer_e[band] = add(filtBuffer_e[band], diff);  move16(); /* becomes equal to *ptrNewExp */
        }
        else {
          Word16 shift;

          /* Shift the mantissa as far as possible: */
          filtBuffer_m[band] = shl(filtBuffer_m[band], reserve); move16();
          /* Compensate in the exponent: */
          filtBuffer_e[band] = sub(filtBuffer_e[band], reserve);  move16();
          /* For the remaining difference, change the new gain value */
          shift = add(reserve, diff);
          nrgGain_m[band] = shl(nrgGain_m[band], shift);         move16();   
          nrgGain_e[band] = sub(nrgGain_e[band], shift);  move16();
        }
      }
    }
  }
}


/*!
  \brief  Update time-smoothing-buffers for gains and noise levels
*/
static void updateFiltBuffer(Word16 * filtBuffer_m,      /*!< buffered gains array (mantissas) */
                             Word16 * filtBufferNoise_m, /*!< buffered noise-level array (mantissas) */
                             Word16 *  nrgGain_m,         /*!< mantissas for gains of current envelope */
                             Word16 *  noiseLevel_m,      /*!< mantissas for noise levels of current envelope */
                             Word16    noSubbands)                 /*!< Number of QMF subbands */
{
  Word8 k;
  assert(noSubbands >= 1);
  for (k=0; k<noSubbands; k++) {
    *filtBuffer_m++ = *nrgGain_m++;                     move16();
    *filtBufferNoise_m++ = *noiseLevel_m++;             move16();
  }
}


/*!
  \brief   Shift mantissas of the noise level vector and update the (common) exponent.
*/
static void rescaleNoiseLevels(Word16 *noiseLevel_m,   /*!< vector of noise level mantissas */
                               Word16 *ptrNoise_e,     /*!< current exponent to be updated */
                               Word16  final_e,         /*!< desired exponent */
                               Word16  noSubbands)      /*!< Length of vector (number of QMF subbands) */
{
  Word8 k;
  Word16 diff = sub(final_e, *ptrNoise_e);

  test();
  if (diff != 0) {
    for (k=0; k<noSubbands; k++) {
      noiseLevel_m[k] = shr(noiseLevel_m[k], diff);             move16();
    }
  }
  *ptrNoise_e = final_e;                move16();
}


/*!
  \brief  Shift left the mantissas of all subband samples in the given
          time and frequency range by the specified number of bits.
*/
void rescaleSubbandSamples(Word32 ** re,      /*!< Real part of input and output subband samples */
#ifndef LP_SBR_ONLY
                           Word32 ** im,      /*!< Imaginary part of input and output subband samples */
#endif
                           Word16 lowSubband, /*!< Begin of frequency range to process */
                           Word16 highSubband,/*!< End of frequency range to process */
                           Word16 start_pos,  /*!< Begin of time rage (QMF-timeslot) */
                           Word16 next_pos,   /*!< End of time rage (QMF-timeslot) */
                           Word16 shift,      /*!< number of bits to shift */
                           Flag bUseLP)
{
  Word16 k,l;

  test();
  if (shift != 0) {

    Word16 noSubbands = sub(highSubband, lowSubband);

    test();
    if (sub(shift,31) > 0) {
      shift = 31;                               move16();
    }
    test();
    if (sub(shift,-31) < 0) {
      shift = -31;                              move16();
    }

    for (l=start_pos; l<next_pos; l++) {
      Word32 * ptr = re[l] + lowSubband;        move16();
      for (k=noSubbands; k!=0; k--) {
	*ptr = L_shl(*ptr, shift);              move32();
        ptr++;
      }
#ifndef LP_SBR_ONLY
      test();
      if (!bUseLP) {
        ptr = im[l] + lowSubband;               move16();
        for (k=noSubbands; k!=0; k--) {
          *ptr = L_shl(*ptr, shift);            move32();
          ptr++;
        }
      }
#endif
    }
  }
}


/*!
  \brief   Determine headroom for shifting
  \return  Number of free bits in the biggest spectral value
*/
Word16 expSubbandSamples(Word32 ** re,      /*!< Real part of input and output subband samples */
#ifndef LP_SBR_ONLY
                         Word32 ** im,      /*!< Imaginary part of input and output subband samples */
#endif
                         Word16 lowSubband, /*!< Begin of frequency range to process */
                         Word16 highSubband,/*!< Number of QMF bands to process */
                         Word16 start_pos,  /*!< Begin of time rage (QMF-timeslot) */
                         Word16 next_pos,   /*!< End of time rage (QMF-timeslot) */
                         Flag bUseLP
                        )
{
  Word16 l,k, maxShift;

  Word32 value;
  Word32 maxAbs;
  Word16 noSubbands;

  Word32* ptrRe;
#ifndef LP_SBR_ONLY
  Word32* ptrIm;
#endif

  maxAbs = 1;                                   move32();
  noSubbands = sub(highSubband, lowSubband);

  for (l=start_pos; l<next_pos; l++) {

    ptrRe = re[l] + lowSubband;                 move16();

#ifndef LP_SBR_ONLY
    test();
    if (!bUseLP) {
      ptrIm = im[l] + lowSubband;               move16();
    }
#endif

    for (k=noSubbands; k!=0; k--) {
      value = L_abs(*ptrRe++);
      maxAbs |= value;                          logic32(); 

#ifndef LP_SBR_ONLY
      test();
      if (!bUseLP) {
        value = L_abs(*ptrIm++);
        maxAbs |= value;                        logic32();
      }
#endif
    }

  }
  maxShift = ffr_norm32(maxAbs);

  return maxShift;
}



#define SHIFT_BEFORE_SQUARE 4



static void calcNrgPerSubband(Word32  **analysBufferReal,   /*!< Real part of subband samples */
#ifndef LP_SBR_ONLY
                              Word32  **analysBufferImag,   /*!< Imaginary part of subband samples */
#endif
                              Word16    lowSubband,         /*!< Begin of the SBR frequency range */
                              Word16    highSubband,        /*!< High end of the SBR frequency range */
                              Word16    start_pos,          /*!< First QMF-slot of current envelope */
                              Word16    next_pos,           /*!< Last QMF-slot of current envelope + 1 */
                              Word16   frameExp,           /*!< Common exponent for all input samples */
                              Word16  *nrgEst_m,          /*!< Mantissa of resulting Energy (0..1) */
                              Word16  *nrgEst_e,          /*!< Exponent of resulting Energy */
                              Flag bUseLP)
{
  Word16 temp;
  Word16 invWidth;
  Word16 preShift;
  Word16 shift;
  Word16 sum_m;
  Word32 accu; /* Single precision would be sufficient,
                  but overflow bits are required for accumulation */
  Word16 k,l;

  /* Divide by width of envelope later: */
  invWidth = sbr_invIntTable[sub(next_pos,start_pos)];     move16();
  /* The common exponent needs to be doubled because all mantissas are squared: */
  frameExp = (Word8)shl(frameExp, 1);

  for (k=lowSubband; k<highSubband; k++) {

    /* Determine how much we can shift up to gain accuracy */
    Word32 maxVal = 1; /* set LSB to avoid norm=0 */

    assert(next_pos - start_pos >= 2);
    for (l=start_pos; l<next_pos; l++) {
      Word32 value = L_abs(analysBufferReal[l][k]);
      test();
      if (L_sub(value, maxVal) > 0) {
        maxVal = value;                  move32();
      }
#ifndef LP_SBR_ONLY
      test();
      if (!bUseLP) {
        value = L_abs(analysBufferImag[l][k]);
        test();
        if (L_sub(value, maxVal) > 0) {
          maxVal = value;                  move32();
        }
      }
#endif
    }
    preShift = sub(ffr_norm32(maxVal), SHIFT_BEFORE_SQUARE);

    /* Accumulate the energy over the length of the envelope */

    accu = 0L;                   move32();

    for (l=start_pos; l<next_pos; l++) {
      temp = extract_l(L_shr(analysBufferReal[l][k], sub(16,preShift)));
      accu = L_mac(accu, temp, temp);
#ifndef LP_SBR_ONLY
      test();
      if (!bUseLP) {
        temp = extract_l(L_shr(analysBufferImag[l][k], sub(16,preShift)));
        accu = L_mac(accu, temp, temp);
      }
#endif
    }

    /* Convert double precision to Mantissa/Exponent:
    */

    test();
    if (accu != 0L) {

      shift = negate(ffr_norm32(accu));

      sum_m = extract_l(L_shr(accu, add(16, shift)));

      /* Divide by width of envelope and apply frame scale: */
      *nrgEst_m++ = mult(sum_m, invWidth); move16();
      shift = sub(shift, shl(preShift,1));
      test();
      if (bUseLP) {
        shift = add(shift, 1); /* +1 due to missing imag. part */
      }
      *nrgEst_e++ = add(frameExp, shift); move16();
    }
    else {
      /* Prevent a zero-mantissa-number from being misinterpreted
         due to its exponent. */
      *nrgEst_m++ = 0;                  move16();
      *nrgEst_e++ = 0;                  move16();
    }
  }
}


/*!
  \brief   Estimates the mean energy of each Scale factor band for the
           duration of the current envelope.
*/
static void calcNrgPerSfb(Word32 **analysBufferReal,  /*!< Real part of subband samples */
#ifndef LP_SBR_ONLY
                          Word32 **analysBufferImag,  /*!< Imaginary part of subband samples */
#endif
                          Word16 nSfb,                /*!< Number of scale factor bands */
                          Word16 *freqBandTable,/*!< First Subband for each Sfb */
                          Word16 start_pos,           /*!< First QMF-slot of current envelope */
                          Word16 next_pos,            /*!< Last QMF-slot of current envelope + 1 */
                          Word16 maxQmfSubbandAac, /*!< Actual start band in this frame */
                          Word16 frameExp,            /*!< Common exponent for all input samples */
                          Word16 *nrgEst_m,           /*!< Mantissa of resulting Energy (0..1) */
                          Word16 *nrgEst_e,           /*!< Exponent of resulting Energy */
                          Flag   bUseLP)
{
  Word16 invWidth;
  Word16 preShift;
  Word16 shift, sum_e;
  Word16 sum_m;

  Word16 c;
  Word16 j,k,l;
  Word16 li,ui;
  Word32 sumLine; /* Single precision would be sufficient,
                   but overflow bits are required for accumulation */
  Word32 sumAll;

  c = 0;                                                move16();

  /* Divide by width of envelope later: */
  invWidth = sbr_invIntTable[sub(next_pos,start_pos)];     move16();
  /* The common exponent needs to be doubled because all mantissas are squared: */
  frameExp = (Word8)shl(frameExp, 1);

  for(j=0; j<nSfb; j++) {
    li = freqBandTable[j];                              move16();

    test();
    if (sub(li,maxQmfSubbandAac) >= 0) {
      ui = freqBandTable[j+1];                          move16();

      preShift = expSubbandSamples(analysBufferReal,
#ifndef LP_SBR_ONLY
                                   analysBufferImag,
#endif
                                   li,
                                   ui,
                                   start_pos,
                                   next_pos,
                                   bUseLP);

      preShift = sub(preShift, SHIFT_BEFORE_SQUARE);

      sumAll = 0;                                       move32();

      for (k=li; k<ui; k++) {

        sumLine = 0L;                                   move32();

        assert(next_pos - start_pos >= 2);

        for (l=start_pos; l<next_pos; l++) {
	  Word16 temp;

          temp    = extract_l(L_shr(analysBufferReal[l][k], sub(16,preShift)));
          sumLine = L_mac(sumLine, temp, temp);
#ifndef LP_SBR_ONLY
          test();
          if (!bUseLP) {
            temp    = extract_l(L_shr(analysBufferImag[l][k], sub(16,preShift)));
            sumLine = L_mac(sumLine, temp, temp);
          }
#endif
        }
        /*
           Shift right far enough that no overflow bits will be used in the end.
           (Max energy:  15 QMF-channels * 38 slots * (re+im) = 930  => 10 bits */
        sumAll = L_add(sumAll, L_shr(sumLine, 10));
      }

      /* Convert double precision to Mantissa/Exponent: */
      shift = ffr_norm32(sumAll);

      /* shift can become negative if overflow bits are used */
      sum_m = extract_l(L_shr(sumAll, sub(16,shift)));

      test();
      if (sum_m == 0) {
        /* Prevent a zero-mantissa-number from being misinterpreted
           due to its exponent. */
        sum_e = 0;                                      move16();
      }
      else {
        /* Divide by width of envelope: */
        sum_m = mult(sum_m, invWidth);

        /* Divide by width of Sfb: */
        sub(ui,li);
        sum_m = mult(sum_m, sbr_invIntTable[ui-li]);

        /* Set all Subband energies in the Sfb to the average energy: */
        test();
        if (bUseLP) {
          sum_e = sub(add(frameExp, 11), shift); /* -10 to compensate right-shift, +1 due to missing imag. part */
        }
#ifndef LP_SBR_ONLY
        else {
          sum_e = sub(add(frameExp, 10), shift); /* -10 to compensate right-shift */
        }
#endif
        sum_e = sub(sum_e, shl(preShift, 1));
      }

      for (k=li; k<ui; k++) {
        nrgEst_m[c] = sum_m;                      move16();
        nrgEst_e[c] = sum_e;               move16();
        c++;
      }
    }
  }
}



/*!
  \brief  Calculate gain, noise, and additional sine level for one subband.
*/
static void calcSubbandGain(Word16  nrgRef_m,   /*!< Reference Energy according to envelope data (mantissa) */
                            Word16  nrgEst_m,   /*!< Energy in transposed signal (mantissa) */
                            Word16  tmpNoise_m, /*!< Relative noise level (mantissa) */

                            Word16  nrgRef_e,   /*!< Reference Energy according to envelope data (exponent) */
                            Word16  nrgEst_e,   /*!< Energy in transposed signal (exponent) */
                            Word16  tmpNoise_e, /*!< Relative noise level (exponent) */
                            Flag    sinePresentFlag,  /*!< Indicates if sine is present on band */
                            Flag    sineMapped,       /*!< Indicates if sine must be added */
                            Flag    noNoiseFlag,      /*!< Flag to suppress noise addition */

                            Word16  *ptrNrgGain_m,    /*!< Resulting energy gain (mantissa) */
                            Word16  *ptrNrgGain_e,    /*!< Resulting energy gain (exponent) */
                            Word16  *ptrNoiseLevel_m, /*!< Resulting absolute noise energy (mantissa) */
                            Word16  *ptrNoiseLevel_e, /*!< Resulting absolute noise energy (exponent) */
                            Word16  *ptrNrgSine_m,    /*!< Additional sine energy (mantissa) */
                            Word16  *ptrNrgSine_e)    /*!< Additional sine energy (exponent) */

{
  Word16  a_m;
  Word16  b_m;
  Word16  a_e, b_e;
  Word16  c_m;
  Word16  c_e;

  /*
     This addition of 1 prevents divisions by zero in the reference code.
  */
  ffr_add_MantExp( nrgEst_m, nrgEst_e,
                   0x4000, 1,  /* 1.0 */
                   &nrgEst_m, &nrgEst_e);

  /*  A = NrgRef * TmpNoise */
  a_m = mult(nrgRef_m, tmpNoise_m);
  a_e = (Word8)add(nrgRef_e, tmpNoise_e);

  /*  B = 1 + TmpNoise */
  ffr_add_MantExp( tmpNoise_m, tmpNoise_e,
                   0x4000, 1,  /* 1.0 */
                   &b_m, &b_e);

  /*  noiseLevel = A / B = (NrgRef * TmpNoise) / (1 + TmpNoise) */
  ffr_divide_MantExp( a_m,  a_e,
                      b_m,  b_e,
                      ptrNoiseLevel_m, ptrNoiseLevel_e);

  test();
  if (sinePresentFlag) {

    /*  C = (1 + TmpNoise) * NrgEst */
    c_m = mult(b_m, nrgEst_m);
    c_e = (Word8)add(b_e, nrgEst_e);

    /*  gain = A / C = (NrgRef * TmpNoise) / (1 + TmpNoise) * NrgEst */
    ffr_divide_MantExp( a_m,  a_e,
                        c_m,  c_e,
                        ptrNrgGain_m, ptrNrgGain_e);

    test();
    if (sineMapped) {
      /*  sineLevel = nrgRef / (1 + TmpNoise) */
      ffr_divide_MantExp( nrgRef_m,  nrgRef_e,
                          b_m,  b_e,
                          ptrNrgSine_m, ptrNrgSine_e);
    }
  }
  else {
    test();
    if (noNoiseFlag) {
      /*  B = NrgEst */
      b_m = nrgEst_m;                                           move16();
      b_e = nrgEst_e;                                           move16();
    }
    else {
      /*  B = NrgEst * (1 + TmpNoise) */
      b_m = mult(b_m, nrgEst_m);
      b_e = (Word8)add(b_e, nrgEst_e);
    }

    /*  gain = nrgRef / B */
    ffr_divide_MantExp( nrgRef_m,  nrgRef_e,
                        b_m,  b_e,
                        ptrNrgGain_m, ptrNrgGain_e);
  }
}


/*!
  \brief  Calculate "average gain" for the specified subband range.
*/
static void calcAvgGain(Word16  *  nrgRef_m,    /*!< Reference Energy according to envelope data (mantissa) */
                        Word16  *  nrgRef_e,    /*!< Reference Energy according to envelope data (exponent) */
                        Word16  *  nrgEst_m,    /*!< Energy in transposed signal (mantissa) */
                        Word16  *  nrgEst_e,    /*!< Energy in transposed signal (exponent) */
                        Word16     lowSubband,  /*!< Begin of the limiter band */
                        Word16     highSubband, /*!< High end of the limiter band */
                        Word16  *  ptrSumRef_m,
                        Word16  *  ptrSumRef_e,
                        Word16  *  ptrAvgGain_m,/*!< Resulting overall gain (mantissa) */
                        Word16  *  ptrAvgGain_e)/*!< Resulting overall gain (exponent) */
{
  Word16 sumRef_m;
  Word16 sumEst_m;
  Word16 sumRef_e;
  Word16 sumEst_e;
  Word16 k;

  sumRef_m = 1;                                         move16();
  sumEst_m = 1;                                         move16();
  sumRef_e = -SHORT_BITS;                               move16();
  sumEst_e = -SHORT_BITS;                               move16();

  assert(lowSubband < highSubband);
  for (k=lowSubband; k<highSubband; k++){
    /* Add nrgRef[k] to sumRef: */
    ffr_add_MantExp( sumRef_m, sumRef_e,
                     nrgRef_m[k], nrgRef_e[k],
                     &sumRef_m, &sumRef_e );

    /* Add nrgEst[k] to sumEst: */
    ffr_add_MantExp( sumEst_m, sumEst_e,
                     nrgEst_m[k], nrgEst_e[k],
                     &sumEst_m, &sumEst_e );
  }

  ffr_divide_MantExp(sumRef_m, sumRef_e,
                     sumEst_m, sumEst_e,
                     ptrAvgGain_m, ptrAvgGain_e);

  *ptrSumRef_m = sumRef_m;                              move16();
  *ptrSumRef_e = sumRef_e;                              move16();
}


/*!
  \brief   Amplify one timeslot of the signal with the calculated gains
           and add the noisefloor.
*/
static void adjustTimeSlotLP(Word32  *  ptrReal,        /*!< Subband samples to be adjusted, real part */
                             Word16  *  gain_m,         /*!< Gains of current envelope, mantissa */
                             Word16  *  gain_e,         /*!< Gains of current envelope, exponent */
                             Word16  *  noiseLevel_m,   /*!< Noise levels of current envelope, mantissa */
                             Word16  *  sineLevel_m,    /*!< Sine levels, mantissa */
                             Word16  *  sineLevel_e,    /*!< Sine levels, exponent */
                             Word16  noise_e,           /*!< Noise levels exponent */
                             Word16  *  ptrHarmIndex,   /*!< Harmonic index */
                             Word16   lowSubband,        /*!< Lowest QMF-channel in the currently used SBR range. */
                             Word16   noSubbands,        /*!< Number of QMF subbands */
                             Word16   scale_change,      /*!< Number of bits to shift adjusted samples */
                             Word16   lowband_e,         /*!< Scale of spectral data below lowSubband */
                             Flag    noNoiseFlag,       /*!< Flag to suppress noise addition */
                             Word16 *  ptrPhaseIndex    /*!< Start index to random number array */
                             )
{
  Word16 k=0;
  Word16 shift;
  Word32 signalReal;
  Word16 index = *ptrPhaseIndex;
  Word16 harmIndex = *ptrHarmIndex;
  Word16 freqInvFlag = (lowSubband & 1);
  Word32 sineLevel, sineLevelPrev, sineLevelNext;
  Word16 tone_count= 0;

#ifdef LP_SBR_ONLY
  const Word16 *ptrRandomPhase = &sbr_randomPhase[index]; move16();
#else
  const Word32 *ptrRandomPhase = &sbr_randomPhase[index]; move16();
#endif

  move16(); /* init index */
  move16(); /* init harmIndex */
  move16(); logic16(); /* init freqInvFlag */
  move16(); /* init tone_count */

  *ptrPhaseIndex = add(index,noSubbands) & (SBR_NF_NO_RANDOM_VAL-1); logic16(); move16(); 

  /*
    First pass for k=0 pulled out of the loop:
  */

  ptrRandomPhase++;

  /*
    The next multiplication constitutes the actual envelope adjustment
    of the signal
  */
  signalReal = fixmul_32x16b(*ptrReal, gain_m[0]);
  shift = sub (gain_e[0], scale_change); /* shift can become negative */
  test();
  if (shift>0)
    signalReal = L_shl(signalReal, shift); 
  else
    signalReal = L_shr(signalReal, negate(shift));
  
  shift = sub(sineLevel_e[0], noise_e);
  test();
  if (shift>0)
    sineLevel = L_shl(L_deposit_l(sineLevel_m[0]), shift);
  else
    sineLevel = L_shr(L_deposit_l(sineLevel_m[0]), negate(shift));
  
  test();
  if ( sub(noSubbands,1) > 0) {
    shift = sub(sineLevel_e[1], noise_e);
    test();
    if (shift>0)
      sineLevelNext = L_shl(L_deposit_l(sineLevel_m[1]), shift);
    else
      sineLevelNext = L_shr(L_deposit_l(sineLevel_m[1]), negate(shift));
  }
  else {
    sineLevelNext = 0;
  }


  test();
  if (sineLevel_m[0] != 0) {
    tone_count = add(tone_count,1);
  }
  else {
    test();
    if (!noNoiseFlag) {
      /* Add noisefloor to the amplified signal */
#ifdef LP_SBR_ONLY
      signalReal = L_mac(signalReal, *ptrRandomPhase, noiseLevel_m[0]);
#else
      signalReal = L_mac(signalReal, extract_h(*ptrRandomPhase), noiseLevel_m[0]);
#endif
    }
  }
  
  switch(harmIndex) {

  case 0:
    test();
    signalReal = L_add(signalReal, sineLevel);
    break;

  case 2:
    test(); test();
    signalReal = L_sub(signalReal, sineLevel);
    break;

  case 1:
    test();test();test();
    test();
    if (freqInvFlag) {
      *(ptrReal-1) = L_add( *(ptrReal-1), L_shl(fixmul_32x16b(sineLevel, 0x010b), sub(noise_e, lowband_e)) ); move32();
      signalReal   = L_sub(  signalReal,  fixmul_32x16b(sineLevelNext, 0x010b) );
    }
    else {
      *(ptrReal-1) = L_sub( *(ptrReal-1), L_shl(fixmul_32x16b(sineLevel, 0x010b), sub(noise_e, lowband_e)) ); move32();
      signalReal   = L_add(  signalReal,  fixmul_32x16b(sineLevelNext, 0x010b) );
    }
    break;

  case 3:
    test();test();test();test();
   test();
    if (freqInvFlag) {
      *(ptrReal-1) = L_sub( *(ptrReal-1), L_shl(fixmul_32x16b(sineLevel, 0x010b), sub(noise_e, lowband_e)) ); move32();
      signalReal   = L_add(  signalReal,  fixmul_32x16b(sineLevelNext, 0x010b) );
    }
    else {
      *(ptrReal-1) = L_add( *(ptrReal-1), L_shl(fixmul_32x16b(sineLevel, 0x010b), sub(noise_e, lowband_e)) ); move32();
      signalReal   = L_sub(  signalReal,  fixmul_32x16b(sineLevelNext, 0x010b) );
    }
    break;
  }
  *ptrReal++ = signalReal;    move32();
  freqInvFlag = !freqInvFlag; logic16();

  switch(harmIndex) {
    
  case 0:
    test();
    for (k=1; k<noSubbands-1; k++) {
      ptrRandomPhase++;
      /*
        The next multiplication constitutes the actual envelope adjustment
        of the signal
      */
      signalReal = fixmul_32x16b(*ptrReal, gain_m[k]);
      shift = sub(gain_e[k], scale_change); /* shift can become negative */
      signalReal = L_shl(signalReal, shift);

      sineLevelPrev = sineLevel;   move32();
      sineLevel =  sineLevelNext;  move32();
      sineLevelNext = L_shl(sineLevel_m[k+1], sub(sineLevel_e[k+1], noise_e));

      test(); test();
      if (sineLevel_m[k] == 0 && !noNoiseFlag) {
        /* Add noisefloor to the amplified signal */
#ifdef LP_SBR_ONLY
        signalReal = L_mac(signalReal, *ptrRandomPhase, noiseLevel_m[k]);
#else
        signalReal = L_mac(signalReal, extract_h(*ptrRandomPhase), noiseLevel_m[k]);
#endif
      }

      *ptrReal++ = L_add(signalReal, sineLevel); move32();
    }
    break;

  case 1:
    test();test();
    for (k=1; k<noSubbands-1; k++) {
      ptrRandomPhase++;
      /*
        The next multiplication constitutes the actual envelope adjustment
        of the signal
      */
      signalReal = fixmul_32x16b(*ptrReal, gain_m[k]);
      shift = sub(gain_e[k], scale_change); /* shift can become negative */
      signalReal = L_shl(signalReal, shift);

      sineLevelPrev = sineLevel;          move32();
      sineLevel     = sineLevelNext;      move32();
      sineLevelNext = L_shl(sineLevel_m[k+1], sub(sineLevel_e[k+1], noise_e));

      test();
      if (sineLevel_m[k] != 0) {
        tone_count=add(tone_count,1);
      }
      else {
        test();
        if (!noNoiseFlag) {
          /* Add noisefloor to the amplified signal */
#ifdef LP_SBR_ONLY
          signalReal = L_mac(signalReal, *ptrRandomPhase, noiseLevel_m[k]);
#else
          signalReal = L_mac(signalReal, extract_h(*ptrRandomPhase), noiseLevel_m[k]);
#endif
        }
      }

      test();
      if (sub(tone_count, 16) <= 0) {
        Word32 addSine = fixmul_32x16b(L_sub(sineLevelPrev, sineLevelNext) , 0x010b );
        test();
        if (freqInvFlag) {
          signalReal = L_add(signalReal, addSine);
        }
        else {
          signalReal = L_sub(signalReal, addSine);
        }
      }
      *ptrReal++ = signalReal; move32();
      freqInvFlag = negate(freqInvFlag);
    }
    break;

  case 2:
    test();test();test();
    for (k=1; k<noSubbands-1; k++) {
      ptrRandomPhase++;
      /*
        The next multiplication constitutes the actual envelope adjustment
        of the signal
      */
      signalReal = fixmul_32x16b(*ptrReal, gain_m[k]);
      shift = sub(gain_e[k], scale_change); /* shift can become negative */
      signalReal = L_shl(signalReal, shift);

      sineLevelPrev = sineLevel;      move32();
      sineLevel     = sineLevelNext;  move32();
      sineLevelNext = L_shl(sineLevel_m[k+1], sub(sineLevel_e[k+1], noise_e));

      test(); test();
      if (sineLevel_m[k] == 0 && !noNoiseFlag) {
        /* Add noisefloor to the amplified signal */
#ifdef LP_SBR_ONLY
        signalReal = L_mac(signalReal, *ptrRandomPhase, noiseLevel_m[k]);
#else
        signalReal = L_mac(signalReal, extract_h(*ptrRandomPhase), noiseLevel_m[k]);
#endif
      }

      *ptrReal++ = L_sub(signalReal, sineLevel); move32();
    }
    break;

  case 3:
    test();test();test();test();
    sub(noSubbands,1);
    for (k=1; k<noSubbands-1; k++) {
      ptrRandomPhase++;
      /*
        The next multiplication constitutes the actual envelope adjustment
        of the signal
      */
      signalReal = fixmul_32x16b(*ptrReal, gain_m[k]);
      shift = sub(gain_e[k], scale_change); /* shift can become negative */
      signalReal = L_shl(signalReal, shift);

      sineLevelPrev = sineLevel;     move32();
      sineLevel     = sineLevelNext; move32();
      sineLevelNext = L_shl(sineLevel_m[k+1], sub(sineLevel_e[k+1], noise_e));

      test();
      if (sineLevel_m[k] != 0) {
        tone_count = add(tone_count,1);
      }
      else {
        test();
        if (!noNoiseFlag) {
          /* Add noisefloor to the amplified signal */
#ifdef LP_SBR_ONLY
          signalReal = L_mac(signalReal, *ptrRandomPhase, noiseLevel_m[k]);
#else
          signalReal = L_mac(signalReal, extract_h(*ptrRandomPhase), noiseLevel_m[k]);
#endif
        }
      }

      test();
      if (sub(tone_count,16) <= 0) {
        Word32 addSine = fixmul_32x16b(L_sub(sineLevelPrev, sineLevelNext) , 0x010b );

        test();
        if (freqInvFlag) {
          signalReal = L_sub(signalReal, addSine);
        }
        else {
          signalReal = L_add(signalReal, addSine);
        }
      }
      *ptrReal++ = signalReal;     move32();
      freqInvFlag = !freqInvFlag;  logic16();
    }
  }

  ptrRandomPhase++;

  test();
  if (sub(noSubbands,1) > 0) {
    /*
      The next multiplication constitutes the actual envelope adjustment
      of the signal
    */
    signalReal = fixmul_32x16b(*ptrReal, gain_m[k]);
    shift = sub(gain_e[k], scale_change); /* shift can become negative */
    signalReal = L_shl(signalReal, shift);
    
    sineLevelPrev = fixmul_32x16b(sineLevel, 0x010b);
    sineLevel =  sineLevelNext;  move32();
    
    test();
    if (sineLevel_m[k] != 0) {
      tone_count = add(tone_count,1);
    }
    else {
      test();
      if (!noNoiseFlag) {
        /* Add noisefloor to the amplified signal */
#ifdef LP_SBR_ONLY
        signalReal = L_mac(signalReal, *ptrRandomPhase, noiseLevel_m[k]);
#else
        signalReal = L_mac(signalReal, extract_h(*ptrRandomPhase), noiseLevel_m[k]);
#endif
      }
    }
    
    switch(harmIndex) {
      
    case 0:
      test();
      *ptrReal = L_add(signalReal, sineLevel); move32();
      break;
      
    case 2:
      test();test();
      *ptrReal = L_sub(signalReal, sineLevel); move32();
      break;
      
    case 1:
      test();test();test();
      test();
      if(sub(tone_count,16) <= 0){
        test();
        if (freqInvFlag) {
          *ptrReal++ = L_add(signalReal, sineLevelPrev); move32();
          test();
          if ( sub(add(k,lowSubband),62) < 0) {
            *ptrReal = L_sub( *ptrReal, fixmul_32x16b(sineLevel, 0x010b) ); move32();
          }
        }
        else {
          *ptrReal++ = L_sub(signalReal, sineLevelPrev); move32();
          test();
          if ( sub(add(k,lowSubband),62) < 0) {
            *ptrReal = L_add( *ptrReal, fixmul_32x16b(sineLevel, 0x010b) ); move32();
          }
        }
      }
      else {
        *ptrReal = signalReal; move32();
      }
      break;
      
    case 3:
      test();test();test();test();
      test();
      if(sub(tone_count,16) <= 0){
        test();
        if (freqInvFlag) {
          *ptrReal++ = L_sub(signalReal, sineLevelPrev); move32();
          test();
          if ( sub(add(k,lowSubband),62) < 0) {
            *ptrReal = L_add( *ptrReal, fixmul_32x16b(sineLevel, 0x010b) ); move32();
          }
        }
        else {
          *ptrReal++ = L_add(signalReal, sineLevelPrev); move32();
          test();
          if ( sub(add(k,lowSubband),62) < 0) {
            *ptrReal = L_sub( *ptrReal, fixmul_32x16b(sineLevel, 0x010b) ); move32();
          }
        }
      }
      else {
        *ptrReal = signalReal; move32();
      }
      break;
    }
  } /* if (sub(noSubbands,1) > 0) */

  *ptrHarmIndex = (add(harmIndex,1)) & 3;                       logic16(); move16();
}



#ifndef LP_SBR_ONLY
static void adjustTimeSlot(Word32    *  ptrReal,           /*!< Subband samples to be adjusted, real part */
                           Word32    *  ptrImag,           /*!< Subband samples to be adjusted, imag part */
                           Word16  *  filtBuffer_m,      /*!< Gains of last envelope, mantissa */
                           Word16  *  filtBufferNoise_m, /*!< Noise levels of last envelope, mantissa */
                           Word16  *  gain_m,            /*!< Gains of current envelope, mantissa */
                           Word16  *  gain_e,            /*!< Gains of current envelope, exponent */
                           Word16  *  noiseLevel_m,      /*!< Noise levels of current envelope, mantissa */
                           Word16  *  sineLevel_m,       /*!< Sine levels, mantissa */
                           Word16  *  sineLevel_e,       /*!< Sine levels, exponent */
                           Word16   noise_e,            /*!< Noise levels exponent */
                           Word16  *ptrHarmIndex,      /*!< Harmonic index */
                           Word16  lowSubband,         /*!< Lowest QMF-channel in the currently used SBR range. */
                           Word16  noSubbands,         /*!< Number of QMF subbands */
                           Word16  scale_change,       /*!< Number of bits to shift adjusted samples */
                           Word16  smooth_ratio,       /*!< Impact of last envelope */
                           Flag    noNoiseFlag,        /*!< Flag to suppress noise addition */
                           Word16  *ptrPhaseIndex)     /*!< Start index to random number array */
{
  Word16  k;
  Word16  shift;
  Word32  signalReal, signalImag;
  Word16 *smoothedGain, *smoothedNoise;
  Word16  direct_ratio;
  Word16  index = *ptrPhaseIndex;
  Word16  harmIndex = *ptrHarmIndex;
  Word16  freqInvFlag;
  Word32  sineLevel;
  const Word32  *ptrRandomPhase;

  move16(); /* init index */
  move16(); /* init harmIndex */

  direct_ratio = sub(0x7fff, smooth_ratio);
  freqInvFlag = (lowSubband & 1);                               logic16();

  scale_change = (Word8)sub(scale_change, 1);

  ptrRandomPhase = &sbr_randomPhase[index];                     move16();
  *ptrPhaseIndex = add(index,noSubbands) & (SBR_NF_NO_RANDOM_VAL-1); move16();

  test();
  if (smooth_ratio) {
    assert(noSubbands >= 1);
    for (k=0; k<noSubbands; k++) {
    /*
      Smoothing: The old envelope has been bufferd and a certain ratio
      of the old gains and noise levels is used.
    */
      filtBuffer_m[k] = add(mult(smooth_ratio, filtBuffer_m[k]),
                            mult(direct_ratio, gain_m[k])); move16();

      filtBufferNoise_m[k] = add(mult(smooth_ratio, filtBufferNoise_m[k]),
                                 mult(direct_ratio, noiseLevel_m[k])); move16();

    }
    smoothedGain = filtBuffer_m;        move16();
    smoothedNoise = filtBufferNoise_m;  move16();
  }
  else {
    smoothedGain = gain_m;              move16();
    smoothedNoise = noiseLevel_m;       move16();
  }

  assert(noSubbands >= 1);
  for (k=0; k<noSubbands; k++) {
    signalReal = fixmuldiv2_32x16b(*ptrReal, smoothedGain[k]);
    signalImag = fixmuldiv2_32x16b(*ptrImag, smoothedGain[k]);

    shift = sub(gain_e[k], scale_change);
    signalReal = L_shl(signalReal, shift);
    signalImag = L_shl(signalImag, shift);

    ptrRandomPhase++;

    test();
    if (sineLevel_m[k] != 0) {
      sineLevel = L_shl(sineLevel_m[k], sub(sineLevel_e[k], noise_e));
  
      switch(harmIndex) {
      case 0:
        test();
        *ptrReal = L_add(signalReal, sineLevel);        move32();

        *ptrImag = signalImag;                          move32();
        break;
      case 2:
        test();test();
        *ptrReal = L_sub(signalReal, sineLevel);        move32();

        *ptrImag = signalImag;                          move32();
        break;
      case 1:
        test();test();test();
        *ptrReal = signalReal;                          move32();
        test();
        if (freqInvFlag) {
          *ptrImag = L_sub(signalImag, sineLevel);      move32();
        } else {
          *ptrImag = L_add(signalImag, sineLevel);      move32();
        }
        break;
      case 3:
        test();test();test();test();
        *ptrReal = signalReal;                          move32();
        test();
        if (freqInvFlag) {
          *ptrImag = L_add(signalImag, sineLevel);      move32();
        } else {
          *ptrImag = L_sub(signalImag, sineLevel);      move32();
        }
        break;
      }
    }
    else {
      test();
      if (noNoiseFlag) {
        /* Just the amplified signal is saved */
        *ptrReal = signalReal;                          move32();
        *ptrImag = signalImag;                          move32();
      }
      else {
        /* Add noisefloor to the amplified signal */
        Word32 random = *ptrRandomPhase;                
        Word16 noise  = smoothedNoise[k];               move16();
        move16(); /* init random */

        *ptrReal = L_mac(signalReal, extract_h(random), noise); move32();
        *ptrImag = L_mac(signalImag, extract_l(random), noise); move32();
      }
    }
    freqInvFlag = !freqInvFlag;                         logic16();

    ptrReal++;
    ptrImag++;
  }
  *ptrHarmIndex = add(harmIndex,1) & 3;                 logic16(); move16();
}
#endif


/*!
  \brief   Reset limiter bands.

  \return  0 if ok,  -1 on error
*/
Word16
ResetLimiterBands ( Word16 *limiterBandTable,   /*!< Resulting band borders in QMF channels */
                    Word16 *noLimiterBands,     /*!< Resulting number of limiter band */
                    Word16 *freqBandTable,      /*!< Table with possible band borders */
                    Word16 noFreqBands,                   /*!< Number of bands in freqBandTable */
                    const PATCH_PARAM *patchParam,     /*!< Transposer patch parameters */
                    Word16 noPatches,                     /*!< Number of transposer patches */
                    Word16 limiterBands)                  /*!< Selected 'band density' from bitstream */
{
  Word16 i, k;
  Word16 isPatchBorder[2], loLimIndex, hiLimIndex, tempNoLim, nBands;
  Word16 workLimiterBandTable[MAX_FREQ_COEFFS / 2 + MAX_NUM_PATCHES + 1];
  Word16 patchBorders[MAX_NUM_PATCHES + 1];
  Word16 kx, k2;
  Word16 temp;

  Word16 lowSubband = freqBandTable[0];
  Word16 highSubband = freqBandTable[noFreqBands];
  move16(); move16();

  /* 1 limiter band. */
  test();
  if(limiterBands == 0) {
    limiterBandTable[0] = 0;                                    move16();
    limiterBandTable[1] = sub(highSubband, lowSubband);         move16();
    nBands = 1;                                                 move16();
  } else {
    assert(noPatches > 0);
    for (i = 0; i < noPatches; i++) {
      patchBorders[i] = sub(patchParam[i].guardStartBand, lowSubband);
    }
    patchBorders[i] = sub(highSubband, lowSubband);

    /* 1.2, 2, or 3 limiter bands/octave plus bandborders at patchborders. */
    assert(noFreqBands > 0);
    for (k = 0; k <= noFreqBands; k++) {
      workLimiterBandTable[k] = sub(freqBandTable[k], lowSubband); move16();
    }
    for (k = 1; k < noPatches; k++) {
      workLimiterBandTable[noFreqBands + k] = patchBorders[k];  move16();
    }

    tempNoLim = nBands = sub(add(noFreqBands, noPatches), 1);   move16();
    shellsort(workLimiterBandTable, add(tempNoLim,1));

    loLimIndex = 0;                                             move16();
    hiLimIndex = 1;                                             move16();

                                                                test();
    while (sub(hiLimIndex,tempNoLim) <= 0) {
      k2 = add(workLimiterBandTable[hiLimIndex], lowSubband);
      kx = add(workLimiterBandTable[loLimIndex], lowSubband);

      temp = ffr_getNumOctavesDiv8(kx,k2); /* Number of octaves */
      temp = mult(sbr_limiterBandsPerOctaveDiv4[limiterBands], temp);


      test();
      if (sub(temp, 0x01f6) < 0) {
        test();
        if (sub(workLimiterBandTable[hiLimIndex], workLimiterBandTable[loLimIndex]) == 0) {
          workLimiterBandTable[hiLimIndex] = highSubband;       move16();
          nBands = sub(nBands,1);
          hiLimIndex = add(hiLimIndex,1);
          /* end of while ()*/                                  test();
          continue;
        }
        isPatchBorder[0] = isPatchBorder[1] = 0;        move16(); move16();
        for (k = 0; k <= noPatches; k++) {
          test();
          if (sub(workLimiterBandTable[hiLimIndex], patchBorders[k]) == 0) {
            isPatchBorder[1] = 1;                               move16();
            break;
          }
        }
        test();
        if (!isPatchBorder[1]) {
          workLimiterBandTable[hiLimIndex] = highSubband;       move16();
          nBands = sub(nBands,1);
          hiLimIndex = add(hiLimIndex,1);
          /* end of while ()*/                                  test();
          continue;
        }
        assert(noPatches > 0);
        for (k = 0; k <= noPatches; k++) {
          test();
          if (sub(workLimiterBandTable[loLimIndex], patchBorders[k]) == 0) {
            isPatchBorder[0] = 1;                               move16();
            break;
          }
        }
        test();
        if (!isPatchBorder[0]) {
          workLimiterBandTable[loLimIndex] = highSubband;       move16();
          nBands = sub(nBands,1);
        }
      }
      loLimIndex = hiLimIndex;                                  move16();
      hiLimIndex = add(hiLimIndex,1);
      /* end of while ()*/                                      test();
    }
    shellsort(workLimiterBandTable, add(tempNoLim,1));

    /* Test if algorithm exceeded maximum allowed limiterbands */
    test(); test();
    if( sub(nBands, MAX_NUM_LIMITERS) > 0 || nBands <= 0) {
      return -1;
    }

    /* Copy limiterbands from working buffer into final destination */
    assert(nBands > 0);
    for (k = 0; k <= nBands; k++) {
      limiterBandTable[k] = workLimiterBandTable[k];            move16();
    }
  }

  *noLimiterBands = nBands;                                     move16();

  return 0;
}

