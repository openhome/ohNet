/*
   SBR main functions
 */

#include <assert.h>
#include <string.h>
#include "ffr.h"
#include "sbr_ram.h"
#include "sbr_dec.h"
#include "sbrdecsettings.h"
#include "env_extr.h"
#include "env_calc.h"
#ifndef MONO_ONLY
#include "ps_dec.h"
#endif

#include "count.h"
extern int cntIdExt1, cntIdExt2, cntIdExt3;

/*#define MEASURE_QMF*/

/*!
  \brief Rescale already processed spectral data between old and new Xover frequency
*/
static void 
rescaleXoverlap(HANDLE_SBR_DEC hSbrDec,    /*!< top level handle for this channel */
                Word32 ** OverlapBufferReal,  /*!< Spectral data to be scaled (real part) */
#ifndef LP_SBR_ONLY
                Word32 ** OverlapBufferImag,  /*!< Spectral data to be scaled (imag part) */
#endif
                Word16 old_lsb,               /*!< SBR start band from previous frame */
                Word16 new_lsb,               /*!< SBR start band from current frame */
                Word16 startSlot,             /*!< start position in time of current frame (0,2,4,6) */
                Flag bUseLP)
{
  Word16 k, l;
  Word16 startBand, stopBand;
  Word16 target_lsb, target_usb;
  Word16 source_scale, target_scale, delta_scale, reserve;

  startBand = S_min(old_lsb, new_lsb);
  stopBand =  S_max(old_lsb, new_lsb);

                                                                                        logic16(); logic16(); test();
  if (new_lsb != old_lsb  &&  old_lsb > 0) {

    /* When the x-over-frequency raises, initialize the spectral gap with zero */
    for (l=startSlot; l<6 ; l++) {
      for (k=old_lsb; k<new_lsb; k++) {
        OverlapBufferReal[l][k] = 0L;                                                   move32();
#ifndef LP_SBR_ONLY
        test();
        if (!bUseLP) {
          OverlapBufferImag[l][k] = 0L;                                                 move32();
        }
#endif
      }
    }

    sub(new_lsb, old_lsb); test(); 
    if (new_lsb > old_lsb) {
      /* The x-over-area was part of the highband before and will now belong to the lowband */
      source_scale = hSbrDec->sbrScaleFactor.ov_hb_scale;                               move16();
      target_scale = hSbrDec->sbrScaleFactor.ov_lb_scale;                               move16();
      target_lsb   = 0;                                                                 move16();
      target_usb   = old_lsb;                                                           move16();
    }
    else {
      /* The x-over-area was part of the lowband before and will now belong to the highband */
      source_scale = hSbrDec->sbrScaleFactor.ov_lb_scale;                               move16();
      target_scale = hSbrDec->sbrScaleFactor.ov_hb_scale;                               move16();
      target_lsb   = old_lsb;                                                           move16();
      target_usb   = hSbrDec->SynthesisQmfBank.usb; /* old usb would be sufficient */   move16();
    }

    /* Shift left all samples of the x-over-area as much as possible
       An unnecessary coarse scale could cause ov_lb_scale or ov_hb_scale to be
       adapted and the accuracy in the next frame would seriously suffer! */
    reserve = expSubbandSamples(OverlapBufferReal,
#ifndef LP_SBR_ONLY
                                OverlapBufferImag,
#endif
                                startBand,
                                stopBand,
                                0,
                                startSlot,
                                bUseLP);

    rescaleSubbandSamples(OverlapBufferReal,
#ifndef LP_SBR_ONLY
                          OverlapBufferImag,
#endif
                          startBand,
                          stopBand,
                          0,
                          startSlot,
                          reserve,
                          bUseLP);

    source_scale = add(source_scale, reserve);

    delta_scale = sub(target_scale, source_scale);

                                                                                        test();
    if (delta_scale > 0) { /* x-over-area is dominant */
      delta_scale = negate(delta_scale);
      startBand = target_lsb;                                                           move16();
      stopBand = target_usb;                                                            move16();

      sub(new_lsb, old_lsb); test();
      if (new_lsb > old_lsb) {
        /* The lowband has to be rescaled */
        hSbrDec->sbrScaleFactor.ov_lb_scale = source_scale;                             move16();
      }
      else {
        /* The highband has to be rescaled */
        hSbrDec->sbrScaleFactor.ov_hb_scale = source_scale;                             move16();
      }
    }

    rescaleSubbandSamples(OverlapBufferReal,
#ifndef LP_SBR_ONLY
                          OverlapBufferImag,
#endif
                          startBand,
                          stopBand,
                          0,
                          startSlot,
                          delta_scale,
                          bUseLP);
  }
}


/*!
  \brief      SBR decoder core function for one channel
*/
void
sbr_dec (HANDLE_SBR_DEC hSbrDec,            /*!< handle to Decoder channel */
         Word16 *timeData,                  /*!< pointer to time signal */
         HANDLE_SBR_HEADER_DATA hHeaderData,/*!< Static control data */
         HANDLE_SBR_FRAME_DATA hFrameData,  /*!< Control data of current frame */
         HANDLE_SBR_PREV_FRAME_DATA hPrevFrameData,  /*!< Some control data of last frame */
#ifndef MONO_ONLY
         HANDLE_PS_DEC hPS,                                /*!< parametric stereo data */
         HANDLE_SBR_QMF_FILTER_BANK hSynthesisQmfBankRight,/*!< handle for the right channel qmf filter bank */
         SBR_SCALE_FACTOR *sbrScaleFactorRight,            /*!< scale factor for the right channel */
#endif
         Flag applyProcessing,
         Flag bUseLP
         )
{
  Word16 i;
  Word16 slot, reserve;
  Word16 saveLbScale;
  Word16 ov_len;

  /* 1+1/3 frames of spectral data: */
  Word32  *QmfBufferReal[MAX_ENV_COLS];
#ifndef LP_SBR_ONLY
  Word32  *QmfBufferImag[MAX_ENV_COLS];
#endif
  Word32  *ptr;

  /* Number of QMF slots per frame */
  Word16 noCols;

  ov_len = 6;                                                                           move16();
  shr(extract_l(L_mult(hHeaderData->numberTimeSlots,hHeaderData->timeStep)),1);
  noCols = hHeaderData->numberTimeSlots * hHeaderData->timeStep;
  
#ifndef LP_SBR_ONLY
                                                                                        test();
  if (bUseLP)  {
#endif

    /* Assign overlap timeslots to a static buffer: */
    ptr = hSbrDec->ptrsbr_OverlapBuffer;                                                move16();

    for(slot=0; slot<ov_len; slot++) {
      QmfBufferReal[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
    }
    
    /* Assign timeslots to Workbuffer1 */
    ptr = &WorkBuffer1[0];                                                              move16();
    for(i=0; i<noCols; i++) {
      QmfBufferReal[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
      slot++;
    }

#ifndef LP_SBR_ONLY
  }
  else {
    
    /* Number of QMF timeslots in one half of a frame (size of Workbuffer1 or 2): */
    Word16 halflen = shr(noCols, 1);
    
    /* Assign overlap timeslots to a static buffer: */
    ptr = hSbrDec->ptrsbr_OverlapBuffer;                                                move16();

    for(slot=0; slot<ov_len; slot++) {
      QmfBufferReal[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
      QmfBufferImag[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
    }
    
    /* Assign first half of timeslots to Workbuffer1 */
    ptr = &WorkBuffer1[0];                                                              move16();
    for(i=0; i<halflen; i++) {
      QmfBufferReal[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
      QmfBufferImag[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
      slot++;
    }
    
    /* Assign second half of timeslots to Workbuffer2 */
    ptr = &WorkBuffer2[0];                                                              move16();
    for(i=0; i<halflen; i++) {
      QmfBufferReal[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
      QmfBufferImag[slot] = ptr;                                                        move16();
      ptr += NO_SYNTHESIS_CHANNELS;
      slot++;
    }

  }
#endif

  assert(slot == noCols+ov_len);


  /* Set scaling factor for low band signal to zero; */
  hSbrDec->sbrScaleFactor.lb_scale = 0;                                                 move16();


  /* Set effective start frequency for SBR processing */
                                                                                        test();
  if (applyProcessing) {
    hSbrDec->CodecQmfBank.usb = hFrameData->maxQmfSubbandAac;                           move16();
    hSbrDec->SynthesisQmfBank.lsb = hFrameData->maxQmfSubbandAac;                       move16();

    shr(extract_l(L_mult(sub(hPrevFrameData->stopPos,
                             hHeaderData->numberTimeSlots),
                         hHeaderData->timeStep)),1);
    rescaleXoverlap(hSbrDec,
                    QmfBufferReal,
#ifndef LP_SBR_ONLY
                    QmfBufferImag,
#endif
                    hPrevFrameData->maxQmfSubbandAac,
                    hFrameData->maxQmfSubbandAac,
                    hHeaderData->timeStep * (hPrevFrameData->stopPos - hHeaderData->numberTimeSlots),
                    bUseLP
                    );
  }

#ifdef MEASURE_QMF
  /* initiate counter */
  setCounter(cntIdExt1); 
  Reset_WMOPS_counter ();
#endif


  /*
    low band codec signal subband filtering
  */
  cplxAnalysisQmfFiltering (timeData,
                            &hSbrDec->sbrScaleFactor,
                            &QmfBufferReal[ov_len],
#ifndef LP_SBR_ONLY
                            &QmfBufferImag[ov_len],
#endif
                            &hSbrDec->CodecQmfBank,
                            bUseLP);

#ifdef MEASURE_QMF
  fwc(); WMOPS_output(0);
#endif


  /*
    Shift spectral data left to gain accuracy in transposer and adjustor
  */
  reserve = expSubbandSamples(QmfBufferReal,
#ifndef LP_SBR_ONLY
                              QmfBufferImag,
#endif
                              0,
                              hSbrDec->CodecQmfBank.usb,
                              ov_len,
                              add(noCols,ov_len),
                              bUseLP);

                                                                                        test();
  if (sub(add(hSbrDec->sbrScaleFactor.lb_scale, reserve),INT_BITS) < 0) {
    /* If all data is zero, lb_scale could become too large */
    rescaleSubbandSamples(QmfBufferReal,
#ifndef LP_SBR_ONLY
                          QmfBufferImag,
#endif
                          0,
                          hSbrDec->CodecQmfBank.usb,
                          ov_len,
                          add(noCols,ov_len),
                          reserve,
                          bUseLP);
    hSbrDec->sbrScaleFactor.lb_scale = add(hSbrDec->sbrScaleFactor.lb_scale, reserve);  move16();
  }
  /*
    save low band scale, wavecoding may modify it
  */
  saveLbScale = hSbrDec->sbrScaleFactor.lb_scale;                                       move16();


  /*
    Clear upper half of spectrum
  */
  add(noCols,ov_len);
  for (slot = ov_len; slot < noCols+ov_len; slot++) {
    Word16 k;
    for (k=NO_ANALYSIS_CHANNELS; k<NO_SYNTHESIS_CHANNELS; k++){
      QmfBufferReal[slot][k] = 0;                                                       move32();
#ifndef LP_SBR_ONLY
      test();
      if (!bUseLP) {
        QmfBufferImag[slot][k] = 0;                                                     move32();
      }
#endif
    }
  }

                                                                                        test();
  if (applyProcessing)
  {
    /*
      Inverse filtering of lowband and transposition into the SBR-frequency range
    */
    Word16 degreeAlias[NO_SYNTHESIS_CHANNELS];
    Word16 * borders = hFrameData->frameInfo.borders;
    move16(); 
    test();
    if (bUseLP) {
      memset(degreeAlias, 0, NO_SYNTHESIS_CHANNELS * sizeof (Word16));                  memop16(NO_SYNTHESIS_CHANNELS);
    }

    lppTransposer ( &hSbrDec->LppTrans,
                    &hSbrDec->sbrScaleFactor,
                    QmfBufferReal,
#ifndef LP_SBR_ONLY
                    QmfBufferImag,
#endif
                    degreeAlias,
                    hHeaderData->timeStep,
                    borders[0],
                    sub(borders[hFrameData->frameInfo.nEnvelopes], hHeaderData->numberTimeSlots),
                    hHeaderData->hFreqBandData->nInvfBands,
                    hFrameData->maxQmfSubbandAac,
                    hFrameData->sbr_invf_mode,
                    hPrevFrameData->sbr_invf_mode,
                    bUseLP
                    );

    /*
      Adjust envelope of current frame.
    */
    calculateSbrEnvelope (&hSbrDec->sbrScaleFactor,
                          &hSbrDec->SbrCalculateEnvelope,
                          hHeaderData,
                          hFrameData,
                          hPrevFrameData,
                          QmfBufferReal,
#ifndef LP_SBR_ONLY
                          QmfBufferImag,
#endif
                          degreeAlias,
                          bUseLP
                          );



    /*
      Update hPrevFrameData (to be used in the next frame)
    */
    move16(); /*hHeaderData->hFreqBandData->nInvfBands*/
    for (i=0; i<hHeaderData->hFreqBandData->nInvfBands; i++) {
      hPrevFrameData->sbr_invf_mode[i] = hFrameData->sbr_invf_mode[i];                  move16();
    }
    hPrevFrameData->coupling = hFrameData->coupling;                                    move16();
    hPrevFrameData->maxQmfSubbandAac = hFrameData->maxQmfSubbandAac;                    move16();
    hPrevFrameData->stopPos = borders[hFrameData->frameInfo.nEnvelopes];                move16();
    hPrevFrameData->ampRes = hFrameData->ampResolutionCurrentFrame;                     move16();
  }
  else {
    /* Reset hb_scale if no highband is present, because hb_scale is considered in the QMF-synthesis */
    hSbrDec->sbrScaleFactor.hb_scale = saveLbScale;                                     move16();
  }

  for (i=0; i<LPC_ORDER; i++){
    /*
      Store the unmodified qmf Slots values (required for LPC filtering)
    */
    Word16 loBand;
    for (loBand=0; loBand<hSbrDec->CodecQmfBank.usb; loBand++) {
                                                                                        move32();
      hSbrDec->LppTrans.lpcFilterStatesReal[i][loBand] = QmfBufferReal[32-LPC_ORDER+i][loBand];
#ifndef LP_SBR_ONLY
                                                                                        test();
      if (!bUseLP) {
                                                                                        move32();
        hSbrDec->LppTrans.lpcFilterStatesImag[i][loBand] = QmfBufferImag[32-LPC_ORDER+i][loBand];
      }
#endif
    }
  }

  test();
  if(hSbrDec->bApplyQmfLp){

    for (i = 0; i < noCols; i++){

      memop32(NO_SYNTHESIS_CHANNELS-hSbrDec->qmfLpChannel);
      memset(QmfBufferReal[i] + hSbrDec->qmfLpChannel,0,(NO_SYNTHESIS_CHANNELS-hSbrDec->qmfLpChannel)*sizeof(Word32));

#ifndef LP_SBR_ONLY
      test();
      if (!bUseLP)  {
      memop32(NO_SYNTHESIS_CHANNELS-hSbrDec->qmfLpChannel);
        memset(QmfBufferImag[i] + hSbrDec->qmfLpChannel,0,(NO_SYNTHESIS_CHANNELS-hSbrDec->qmfLpChannel)*sizeof(Word32));
      }
#endif

    }
  }


  /*
    Synthesis subband filtering.
  */

#ifdef MEASURE_QMF
  /* initiate counter */
  setCounter(cntIdExt2); 
  Reset_WMOPS_counter ();
#endif

#ifndef MONO_ONLY
  test(); sub(hHeaderData->channelMode, PS_STEREO); test(); 
  if(applyProcessing && hHeaderData->channelMode==PS_STEREO)
  {
    InitPsScale(hPS, &hSbrDec->sbrScaleFactor);

    /*
      synthesize left
    */
    cplxSynthesisQmfFiltering (QmfBufferReal,
                               QmfBufferImag,
                               ov_len,
                               &hSbrDec->sbrScaleFactor,
                               timeData,
                               &hSbrDec->SynthesisQmfBank,
                               hPS,
                               1,
                               0);

    sbrScaleFactorRight->ov_lb_scale=hSbrDec->sbrScaleFactor.ps_scale; move16();
    sbrScaleFactorRight->lb_scale=hSbrDec->sbrScaleFactor.ps_scale; move16();
    sbrScaleFactorRight->hb_scale=hSbrDec->sbrScaleFactor.ps_scale; move16();

    /*
      synthesize right
    */
    cplxSynthesisQmfFiltering (QmfBufferReal,
                               QmfBufferImag,
                               ov_len,
                               sbrScaleFactorRight,
                               &timeData[MAX_COLS*NO_SYNTHESIS_CHANNELS],
                               hSynthesisQmfBankRight,
                               hPS,
                               0,
                               0);
  }
  else{
#endif

    cplxSynthesisQmfFiltering (QmfBufferReal,
#ifndef LP_SBR_ONLY
                               QmfBufferImag,
#endif
                               ov_len,
                               &hSbrDec->sbrScaleFactor,
                               timeData,
                               &hSbrDec->SynthesisQmfBank,
#ifndef MONO_ONLY
                               hPS,
                               0,
#endif
                               bUseLP);

#ifndef MONO_ONLY
  }
#endif

#ifdef MEASURE_QMF
  fwc(); WMOPS_output(0);
#endif

  /*
    Update overlap buffer
    Even bands above usb are copied to avoid outdated spectral data in case
    the stop frequency raises.
  */

  for ( i=0; i<ov_len; i++ ) {
    Word16 k;
    for ( k=0; k<NO_SYNTHESIS_CHANNELS; k++ ) {
      QmfBufferReal[i][k] = QmfBufferReal[i+noCols][k];                                 move32();
#ifndef LP_SBR_ONLY
                                                                                        test();
      if (!bUseLP) {
        QmfBufferImag[i][k] = QmfBufferImag[i+noCols][k];                               move32();
      }
#endif
    }
  }
  hSbrDec->sbrScaleFactor.ov_lb_scale = saveLbScale;                                    move16();

}


/*!
  \brief     Creates sbr decoder structure 
  \return    errorCode, 0 if successful
*/
Word16
createSbrDec (SBR_CHANNEL * hSbrChannel,
              HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
              Word16 chan,                        /*!< Channel for which to assign buffers etc. */
              Flag bDownSample,
              Flag  bApplyQmfLp,
              Word32 sampleFreq)

{
  Word16 err;
  Word16 timeSlots;                               /* Number of SBR slots per frame */
  Word16 noCols;                                  /* Number of QMF slots per frame */
  HANDLE_SBR_DEC hs = &(hSbrChannel->SbrDec);                                           move16();

  timeSlots = hHeaderData->numberTimeSlots;                                             move16();
  shr(extract_l(L_mult(timeSlots, hHeaderData->timeStep)),1);
  noCols    = timeSlots * hHeaderData->timeStep;

  hs->bApplyQmfLp  = bApplyQmfLp; move16();

  sub(bApplyQmfLp,8); test();
  if(bApplyQmfLp == 8)
  {
    hs->qmfLpChannel = (Word8) (ffr_Integer_Div (8000 * NO_SYNTHESIS_CHANNELS, sampleFreq));
  }
  sub(bApplyQmfLp,4); test();
  if(bApplyQmfLp == 4)
  {
    hs->qmfLpChannel = (Word8) (ffr_Integer_Div (4000 * NO_SYNTHESIS_CHANNELS, sampleFreq));
  }



  /* Initialize scale factors */
  hs->sbrScaleFactor.st_lb_scale = INT_BITS - 1;                                      move16();
  hs->sbrScaleFactor.ov_lb_scale = INT_BITS - 1;                                      move16();
  hs->sbrScaleFactor.ov_hb_scale = INT_BITS - 1;                                      move16();
  hs->sbrScaleFactor.st_syn_scale = INT_BITS - 1;                                     move16();
  hs->sbrScaleFactor.hb_scale = INT_BITS - 1;                                         move16();

  hSbrChannel->hPrevFrameData = &PrevFrameData[chan];                                 move16();

  /*
    create envelope calculator
  */
  err = createSbrEnvelopeCalc (&hs->SbrCalculateEnvelope,
                               hHeaderData,
                               chan);
                                                                                        test();
  if (err) {
    return (-1);
  }

  /*
    create QMF filter banks
  */
  createCplxAnalysisQmfBank (&hs->CodecQmfBank, 
                             &hs->sbrScaleFactor,
                             noCols,
                             hHeaderData->hFreqBandData->lowSubband,
                             chan);

  createCplxSynthesisQmfBank (&hs->SynthesisQmfBank, 
                              &hs->sbrScaleFactor,
                              noCols,
                              hHeaderData->hFreqBandData->lowSubband,
                              hHeaderData->hFreqBandData->highSubband,
                              chan,
                              bDownSample);


  initSbrPrevFrameData (hSbrChannel->hPrevFrameData, timeSlots);

  /*
    create transposer
  */
  err = createLppTransposer (&hs->LppTrans,
                             hHeaderData->hFreqBandData->lowSubband,
                             hHeaderData->hFreqBandData->v_k_master,
                             hHeaderData->hFreqBandData->numMaster,
                             hs->SynthesisQmfBank.usb,
                             hs->CodecQmfBank.no_col,
                             hHeaderData->hFreqBandData->freqBandTableNoise,
                             hHeaderData->hFreqBandData->nNfb,
                             hHeaderData->outSampleRate,
                             chan);
                                                                                        test();
  if (err) {
    return (-1);
  }

  hs->ptrsbr_OverlapBuffer = sbr_OverlapBuffer[chan];                                   move16();

  return 0;
}


/*!
  \brief     resets sbr decoder structure 
  \return    errorCode, 0 if successful
*/
Word8
resetSbrDec (HANDLE_SBR_DEC hSbrDec,
             HANDLE_SBR_HEADER_DATA hHeaderData,
             Flag bUseLP)
{ 
  Word16 old_lsb, new_lsb;
  Word16 l;
  Word8  err;

  old_lsb = hSbrDec->SynthesisQmfBank.lsb;                                              move16();
  new_lsb = hHeaderData->hFreqBandData->lowSubband;                                     move16();
  err=0;                                                                                move16();

  resetSbrEnvelopeCalc (&hSbrDec->SbrCalculateEnvelope); 

  hSbrDec->SynthesisQmfBank.lsb = hHeaderData->hFreqBandData->lowSubband;               move16();
  hSbrDec->SynthesisQmfBank.usb = hHeaderData->hFreqBandData->highSubband;              move16();

  hSbrDec->CodecQmfBank.lsb = 0;                                                        move16();
  hSbrDec->CodecQmfBank.usb = hSbrDec->SynthesisQmfBank.lsb;                            move16();


  /*
    reset LPC filter states for additional QMF channels in lowband
  */
  for (l=old_lsb; l<new_lsb; l++) {
                                                                                        move32(); move32();
    hSbrDec->LppTrans.lpcFilterStatesReal[0][l] =  hSbrDec->LppTrans.lpcFilterStatesReal[1][l] = 0L;
#ifndef LP_SBR_ONLY
                                                                                        test();
    if (!bUseLP) {
                                                                                        move32(); move32();
      hSbrDec->LppTrans.lpcFilterStatesImag[0][l] =  hSbrDec->LppTrans.lpcFilterStatesImag[1][l] = 0L;
    }
#endif
  }


  err |= resetLppTransposer (&hSbrDec->LppTrans,
                             hHeaderData->hFreqBandData->lowSubband,
                             hHeaderData->hFreqBandData->v_k_master,
                             hHeaderData->hFreqBandData->numMaster,
                             hHeaderData->hFreqBandData->freqBandTableNoise,
                             hHeaderData->hFreqBandData->nNfb,
                             hHeaderData->hFreqBandData->highSubband,
                             hHeaderData->outSampleRate); logic16();

  err |= ResetLimiterBands ( hHeaderData->hFreqBandData->limiterBandTable,
                             &hHeaderData->hFreqBandData->noLimiterBands,
                             hHeaderData->hFreqBandData->freqBandTable[LO],
                             hHeaderData->hFreqBandData->nSfb[LO],
                             hSbrDec->LppTrans.pSettings->patchParam,
                             hSbrDec->LppTrans.pSettings->noOfPatches,
                             hHeaderData->limiterBands); logic16();

  return err;
}
