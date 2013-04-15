/*
   parametric stereo decoding
 */
#ifndef MONO_ONLY

#include <string.h>

#include <stdlib.h>
#include <math.h>
#include "ffr.h"
#include "sbr_rom.h"
#include "sbr_ram.h"
#include "aac_rom.h"
#include "aac_ram.h"
#include "ps_dec.h"
#include "typedef.h"
#include "count.h"


#include <assert.h>

#define LD_TRIG_DATA 9
#define TRIG_DATA_SIZE (1<<LD_TRIG_DATA)

static void deCorrelate( HANDLE_PS_DEC h_ps_dec,
                         Word32 *rIntBufferLeft, Word32 *iIntBufferLeft,
                         Word32 *rIntBufferRight, Word32 *iIntBufferRight);

static void applyRotation( HANDLE_PS_DEC pms,
                           Word32 *qmfLeftReal , Word32 *qmfLeftImag,
                           Word32 *qmfRightReal, Word32 *qmfRightImag );

/***************************************************************************/
/*!
  \brief  Creates one instance of the PS_DEC struct

  \return Error info (0 = no error)

****************************************************************************/
int
CreatePsDec(HANDLE_PS_DEC h_ps_dec)
{
  Word8 i, j;
  Word16 *ptr1 = (Word16*)&sbr_OverlapBuffer[MAXNRSBRCHANNELS-1][0]; 
  Word32 *ptr2 = (Word32*)&OverlapBuffer[512];                           
  
  move16(); move16();

  memset(h_ps_dec, 0, sizeof(PS_DEC));                          memop16( sizeof(PS_DEC) );

   /* initialisation */

  h_ps_dec->bPsDataAvail = 0;                                   move16();
  h_ps_dec->bEnableIid = 0;                                     move16();
  h_ps_dec->bEnableIcc = 0;                                     move16();
  h_ps_dec->bEnableExt = 0;                                     move16();
  h_ps_dec->freqResIid = 0;                                     move16();
  h_ps_dec->freqResIcc = 0;                                     move16();


  h_ps_dec->aPeakDecayFast = ptr2; ptr2+=NO_BINS; move16();
  memset(h_ps_dec->aPeakDecayFast,0,sizeof(Word32)*NO_BINS);    memop32(NO_BINS);

  h_ps_dec->aPrevNrg = ptr2; ptr2+=NO_BINS; move16();
  memset(h_ps_dec->aPrevNrg,0,sizeof(Word32)*NO_BINS);          memop32(NO_BINS);

  h_ps_dec->aPrevPeakDiff = ptr2; ptr2+=NO_BINS; move16();
  memset(h_ps_dec->aPrevPeakDiff,0,sizeof(Word32)*NO_BINS);     memop32(NO_BINS);


  CreateHybridFilterBank ( &h_ps_dec->hybrid, &ptr2);


  h_ps_dec->mHybridRealLeft = ptr2; ptr2+=SUBQMF_GROUPS; move16();
  memset(h_ps_dec->mHybridRealLeft,0,sizeof(Word32)*SUBQMF_GROUPS); memop32(SUBQMF_GROUPS);

  h_ps_dec->mHybridImagLeft = ptr2; ptr2+=SUBQMF_GROUPS; move16();
  memset(h_ps_dec->mHybridImagLeft,0,sizeof(Word32)*SUBQMF_GROUPS); memop32(SUBQMF_GROUPS);

  h_ps_dec->mHybridRealRight = ptr2; ptr2+=SUBQMF_GROUPS; move16();
  memset(h_ps_dec->mHybridRealRight,0,sizeof(Word32)*SUBQMF_GROUPS); memop32(SUBQMF_GROUPS);

  h_ps_dec->mHybridImagRight = ptr2; ptr2+=SUBQMF_GROUPS; move16();
  memset(h_ps_dec->mHybridImagRight,0,sizeof(Word32)*SUBQMF_GROUPS); memop32(SUBQMF_GROUPS);

  h_ps_dec->delayBufIndex   = 0;                                move16();
  h_ps_dec->delayBufIndexLong = 0;                              move16();


  for (i = 0; i < NO_QMF_ICC_CHANNELS; i++) {
    Word8 delay;

    if (sub(i, NO_QMF_ALLPASS_CHANNELS)< 0){
      delay = 2; move16();

      h_ps_dec->aaRealDelayBufferQmf[i] = ptr1; ptr1+= delay; move16();
      memset(h_ps_dec->aaRealDelayBufferQmf[i],0,delay*sizeof(Word16)); memop16(delay);

      h_ps_dec->aaImagDelayBufferQmf[i] = ptr1; ptr1+= delay; move16();
      memset(h_ps_dec->aaImagDelayBufferQmf[i],0,delay*sizeof(Word16)); memop16(delay);
    }
    else{
      if (sub(i,NO_QMF_ALLPASS_CHANNELS+SHORT_DELAY_START) < 0) {
        delay = LONG_DELAY;  move16();
      } else {
        delay = SHORT_DELAY; move16();
      }

      h_ps_dec->aaRealDelayBufferQmf[i] = ptr1; ptr1+= delay; move16();
      memset(h_ps_dec->aaRealDelayBufferQmf[i],0,delay*sizeof(Word16)); memop16(delay);

      h_ps_dec->aaImagDelayBufferQmf[i] = ptr1; ptr1+= delay; move16();
      memset(h_ps_dec->aaImagDelayBufferQmf[i],0,delay*sizeof(Word16)); memop16(delay);
    }
  }

  for (i = 0; i < SUBQMF_GROUPS; i++) {
    h_ps_dec->aaRealDelayBufferSubQmf[i] = ptr1; ptr1+= DELAY_ALLPASS; move16();
    memset(h_ps_dec->aaRealDelayBufferSubQmf[i],0,DELAY_ALLPASS*sizeof(Word16)); memop16(DELAY_ALLPASS);

    h_ps_dec->aaImagDelayBufferSubQmf[i] = ptr1; ptr1+= DELAY_ALLPASS; move16();
    memset(h_ps_dec->aaImagDelayBufferSubQmf[i],0,DELAY_ALLPASS*sizeof(Word16)); memop16(DELAY_ALLPASS);
  }

  for (i=0 ; i < NO_SERIAL_ALLPASS_LINKS ; i++) {

    h_ps_dec->aDelayRBufIndexSer[i] = 0;
    h_ps_dec->aNoSampleDelayRSer[i] = aRevLinkDelaySer[i];

    for (j = 0; j < h_ps_dec->aNoSampleDelayRSer[i]; j++) {
      h_ps_dec->aaaRealDelayRBufferSerQmf[i][j] = ptr1; ptr1+= NO_QMF_ALLPASS_CHANNELS; move16();
      memset(h_ps_dec->aaaRealDelayRBufferSerQmf[i][j],0,NO_QMF_ALLPASS_CHANNELS*sizeof(Word16)); memop16(NO_QMF_ALLPASS_CHANNELS);

      h_ps_dec->aaaImagDelayRBufferSerQmf[i][j] = ptr1; ptr1+= NO_QMF_ALLPASS_CHANNELS; move16();
      memset(h_ps_dec->aaaImagDelayRBufferSerQmf[i][j],0,NO_QMF_ALLPASS_CHANNELS*sizeof(Word16)); memop16(NO_QMF_ALLPASS_CHANNELS);

      h_ps_dec->aaaRealDelayRBufferSerSubQmf[i][j] = ptr1; ptr1+= SUBQMF_GROUPS; move16();
      memset(h_ps_dec->aaaRealDelayRBufferSerSubQmf[i][j],0,SUBQMF_GROUPS*sizeof(Word16)); memop16(SUBQMF_GROUPS);

      h_ps_dec->aaaImagDelayRBufferSerSubQmf[i][j] = ptr1; ptr1+= SUBQMF_GROUPS; move16();
      memset(h_ps_dec->aaaImagDelayRBufferSerSubQmf[i][j],0,SUBQMF_GROUPS*sizeof(Word16)); memop16(SUBQMF_GROUPS);
    }
  }

  for ( i = 0; i < NO_IID_GROUPS; i++ )
  {
    h_ps_dec->h11Prev[i] = 0x7fff;                              move16();
    h_ps_dec->h12Prev[i] = 0x7fff;                              move16();
  }

  memset( h_ps_dec->h21Prev, 0, sizeof( h_ps_dec->h21Prev ) );  memop16(NO_IID_GROUPS);
  memset( h_ps_dec->h22Prev, 0, sizeof( h_ps_dec->h22Prev ) );  memop16(NO_IID_GROUPS);
  return 0;
}


/***************************************************************************/
/*!
  \brief   Determines headroom in parametric stereo states

  \return  Number of headroom bits

****************************************************************************/
static int getPsStatesScale(HANDLE_PS_DEC hPS)  /*!< Parametric stereo handle */
{

  Word8 i,m;

  Word16 scale = INT_BITS-1; move16();

  for (m=0; m<NO_QMF_ALLPASS_CHANNELS; m++) {
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaRealDelayBufferQmf[m], 2)); 
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaImagDelayBufferQmf[m], 2)); 
  }
  for ( ; m<NO_QMF_ALLPASS_CHANNELS+SHORT_DELAY_START; m++) {
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaRealDelayBufferQmf[m], LONG_DELAY)); 
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaImagDelayBufferQmf[m], LONG_DELAY)); 
  }
  for ( ; m<NO_QMF_ICC_CHANNELS; m++) {
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaRealDelayBufferQmf[m], SHORT_DELAY)); 
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaImagDelayBufferQmf[m], SHORT_DELAY)); 
  }
  for (m=0; m<SUBQMF_GROUPS; m++) {
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaRealDelayBufferSubQmf[m], DELAY_ALLPASS)); 
    scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaImagDelayBufferSubQmf[m], DELAY_ALLPASS)); 
  }

  for (i=0; i<NO_SERIAL_ALLPASS_LINKS; i++) {
    for (m=0; m<hPS->aNoSampleDelayRSer[i]; m++) {
      scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaaRealDelayRBufferSerQmf[i][m], NO_QMF_ALLPASS_CHANNELS));
      scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaaImagDelayRBufferSerQmf[i][m], NO_QMF_ALLPASS_CHANNELS));
      scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaaRealDelayRBufferSerSubQmf[i][m], SUBQMF_GROUPS));
      scale = S_min(scale, ffr_getScalefactorOfShortVector(hPS->aaaImagDelayRBufferSerSubQmf[i][m], SUBQMF_GROUPS)); 
    }
  }

  for (i=0; i<NO_QMF_CHANNELS_IN_HYBRID; i++) {
    scale = S_min(scale, ffr_getScalefactorOfWord32Vector(hPS->hybrid.mQmfBufferReal[i], hPS->hybrid.qmfBufferMove)); 
    scale = S_min(scale, ffr_getScalefactorOfWord32Vector(hPS->hybrid.mQmfBufferImag[i], hPS->hybrid.qmfBufferMove)); 
  }

  return scale;
}



/***************************************************************************/
/*!
 
  \brief  Shift up parametric stereo states

  \return none

****************************************************************************/
static void scalePsStates(HANDLE_PS_DEC hPS,  /*!< Parametric stereo handle */
                          Word16 scale)       /*!< Number of bits to shift left */
{
  Word8 i,m;
 
  for(m=0; m<NO_QMF_ALLPASS_CHANNELS; m++) {
    ffr_scaleShortVector(hPS->aaRealDelayBufferQmf[m], 2, scale);
    ffr_scaleShortVector(hPS->aaImagDelayBufferQmf[m], 2, scale);
  }
  for( ; m<NO_QMF_ALLPASS_CHANNELS+SHORT_DELAY_START; m++) {
    ffr_scaleShortVector(hPS->aaRealDelayBufferQmf[m], LONG_DELAY, scale);
    ffr_scaleShortVector(hPS->aaImagDelayBufferQmf[m], LONG_DELAY, scale);
  }
  for ( ; m<NO_QMF_ICC_CHANNELS; m++) {
    ffr_scaleShortVector(hPS->aaRealDelayBufferQmf[m], SHORT_DELAY, scale);
    ffr_scaleShortVector(hPS->aaImagDelayBufferQmf[m], SHORT_DELAY, scale);
  }
  for (m=0; m<SUBQMF_GROUPS; m++) {
    ffr_scaleShortVector(hPS->aaRealDelayBufferSubQmf[m], DELAY_ALLPASS, scale);
    ffr_scaleShortVector(hPS->aaImagDelayBufferSubQmf[m], DELAY_ALLPASS, scale);
  }

  for (i=0; i<NO_SERIAL_ALLPASS_LINKS; i++) {
    move16(); /* hPS->aNoSampleDelayRSer[i] */
    for (m=0; m<hPS->aNoSampleDelayRSer[i]; m++) {
      ffr_scaleShortVector(hPS->aaaRealDelayRBufferSerQmf[i][m], NO_QMF_ALLPASS_CHANNELS, scale);
      ffr_scaleShortVector(hPS->aaaImagDelayRBufferSerQmf[i][m], NO_QMF_ALLPASS_CHANNELS, scale);
      ffr_scaleShortVector(hPS->aaaRealDelayRBufferSerSubQmf[i][m], SUBQMF_GROUPS, scale);
      ffr_scaleShortVector(hPS->aaaImagDelayRBufferSerSubQmf[i][m], SUBQMF_GROUPS, scale);
    }
  }

  for (i=0; i<NO_QMF_CHANNELS_IN_HYBRID; i++) {
    ffr_scaleWord32Vector(hPS->hybrid.mQmfBufferReal[i], hPS->hybrid.qmfBufferMove, scale);
    ffr_scaleWord32Vector(hPS->hybrid.mQmfBufferImag[i], hPS->hybrid.qmfBufferMove, scale);
  }

  /*
    Rescale some energy values: Since they were retrieved from squared samples,
    they need to be shifted by two times the scale
  */
  scale = add(scale, scale);

  ffr_scaleWord32Vector(hPS->aPeakDecayFast, NO_BINS, scale);
  ffr_scaleWord32Vector(hPS->aPrevNrg, NO_BINS, scale);
  ffr_scaleWord32Vector(hPS->aPrevPeakDiff, NO_BINS, scale);

}


/***************************************************************************/
/*!                                                                          
  \brief  calculates new common scalfactor ps_scale for ov_lb, lb and hb 
          scales reverb buffer states
****************************************************************************/
void
InitPsScale(HANDLE_PS_DEC hPS,                 /*!< Parametric stereo handle */
            SBR_SCALE_FACTOR  *sbrScaleFactor) /*!< SBR scales */
                      
{
  Word16 reserve, change;
 
  /*
    determinate headroom in reverb buffers
  */
  reserve = getPsStatesScale(hPS);
  
  hPS->delay_buffer_scale = add(hPS->delay_buffer_scale, reserve); move16();

  sbrScaleFactor->ps_scale = S_min(sbrScaleFactor->lb_scale, sbrScaleFactor->ov_lb_scale); 
  sbrScaleFactor->ps_scale = S_min(sbrScaleFactor->ps_scale, sbrScaleFactor->hb_scale); 
  sbrScaleFactor->ps_scale = S_min(sbrScaleFactor->ps_scale, hPS->delay_buffer_scale); 
  sbrScaleFactor->ps_scale = sub(sbrScaleFactor->ps_scale, 1);  /* we need some headroom */ move16();

  /* 
    scale reverb buffers to common scale 
  */
  change = sub(sbrScaleFactor->ps_scale, hPS->delay_buffer_scale);
  change = add(change, reserve);
  scalePsStates(hPS, change);

  hPS->delay_buffer_scale = sbrScaleFactor->ps_scale;           move16();
}


/*!
  \brief  Apply parametric stereo processing for one QMF slot
*/
void
ApplyPsSlot(HANDLE_PS_DEC h_ps_dec,           /*!< Handle to parametric stereo data */
            Word32 **rIntBufferLeft,          /*!< Mono input and Left output (real) */
            Word32 **iIntBufferLeft,          /*!< Mono input and Left output (imaginary) */
            Word32 *rIntBufferRight,          /*!< Right channel output (real) */
            Word32 *iIntBufferRight,          /*!< Right channel output (imaginary) */
            SBR_SCALE_FACTOR *sbrScaleFactor, /*!< Sbr scalefactors */
            Word16 slot,                      /*!< slot sumber to determinate overlap region */
            Word16 lsb)                       /*!< start of highband region */
{
  Word16 ch;
  Word16 shift;
  Word16 lb_scale = ( sub(slot, MAX_OV_COLS) <0 ) ? sbrScaleFactor->ov_lb_scale : sbrScaleFactor->lb_scale;

  test(); move16();

  /*
    Shift input slot values to a common scale (sbrScaleFactor->ps_scale)
  */
  shift = sub(lb_scale, sbrScaleFactor->ps_scale);
  for (ch=0; ch<lsb; ch++) {
    rIntBufferLeft[0][ch] = L_shr_r(rIntBufferLeft[0][ch], shift); move32();
    iIntBufferLeft[0][ch] = L_shr_r(iIntBufferLeft[0][ch], shift); move32();
  }
  shift = sub(sbrScaleFactor->hb_scale, sbrScaleFactor->ps_scale);
  logic16(); logic16(); /* 8-bit boundary read access for h_ps_dec->usb */ 
  for (ch=lsb; ch<h_ps_dec->usb; ch++) {
    rIntBufferLeft[0][ch] = L_shr_r(rIntBufferLeft[0][ch], shift); move32();
    iIntBufferLeft[0][ch] = L_shr_r(iIntBufferLeft[0][ch], shift); move32();
  }

  /*
    Feed lowest QMF channels into the hybrid filter bank.
    There is a look-ahead by #HYBRID_FILTER_DELAY slots to compensate
    for the filter delay. Because of this, the values have not yet
    been shifted to sbrScaleFactor->ps_scale.

    All subsequent processing is performed separately for
    the hybrid bank subsamples and the remaining QMF channels.
  */
  HybridAnalysis ( rIntBufferLeft[HYBRID_FILTER_DELAY],
                   iIntBufferLeft[HYBRID_FILTER_DELAY],
                   h_ps_dec->mHybridRealLeft,
                   h_ps_dec->mHybridImagLeft,
                   &h_ps_dec->hybrid,
                   sbrScaleFactor->lb_scale - sbrScaleFactor->ps_scale);

  /*
    Generate a decorrelated signal from the left channel and store it
    in the right channel
  */
  deCorrelate(h_ps_dec,
              rIntBufferLeft[0],
              iIntBufferLeft[0],
              rIntBufferRight,
              iIntBufferRight);

  /*
    Modify left and right channel according to the coefficients calculated
    by InitRotationEnvelope()
  */
  applyRotation(h_ps_dec,
                rIntBufferLeft[0],
                iIntBufferLeft[0],
                rIntBufferRight,
                iIntBufferRight);

  /*
    Transform lowest bands of LEFT channel back to QMF domain
  */
  HybridSynthesis ( h_ps_dec->mHybridRealLeft,
                    h_ps_dec->mHybridImagLeft,
                    rIntBufferLeft[0],
                    iIntBufferLeft[0],
                    &h_ps_dec->hybrid );

  /*
    Transform lowest bands of RIGHT channel back to QMF domain
  */
  HybridSynthesis ( h_ps_dec->mHybridRealRight,
                    h_ps_dec->mHybridImagRight,
                    rIntBufferRight,
                    iIntBufferRight,
                    &h_ps_dec->hybrid );
}



/*!
  \brief  Generate a decorrelated signal from the input
*/
static void
deCorrelate(HANDLE_PS_DEC h_ps_dec,  /*!< Parametric stereo handle */
            Word32 *rIntBufferLeft,  /*!< Input data for all bands above the hybrid filterbank (real) */
            Word32 *iIntBufferLeft,  /*!< Input data for all bands above the hybrid filterbank (imaginary) */
            Word32 *rIntBufferRight, /*!< Output: Artificial right channel for all bands above the hybrid filterbank (real) */
            Word32 *iIntBufferRight  /*!< Output: Artificial right channel for all bands above the hybrid filterbank (imaginary) */
            )
{
  Word16 sb, maxsb, gr, sb_delay, m, bin;

  Word32 peakDiff, nrg;
  Word32 aPower[NO_BINS];
  Word16 aTransRatio[NO_BINS];

  Word32 *aLeftReal;
  Word32 *aLeftImag;
  Word32 *aRightReal;
  Word32 *aRightImag;

  REVERB_BUFFERS * pppRealDelayRBufferSer;
  REVERB_BUFFERS * pppImagDelayRBufferSer;
  Word16 **ppRealDelayBuffer;
  Word16 **ppImagDelayBuffer;

  const Word16 *pFractDelayPhaseFactorRe;
  const Word16 *pFractDelayPhaseFactorIm;
  const Word16 **ppFractDelayPhaseFactorSerRe;
  const Word16 **ppFractDelayPhaseFactorSerIm;
  Word16 usb = h_ps_dec->usb;

  Word16  delayBufIndex; 

  logic16(); logic16(); /* 8-bit boundary read access for h_ps_dec->usb */ 

  aLeftReal = h_ps_dec->mHybridRealLeft;     move16();
  aLeftImag = h_ps_dec->mHybridImagLeft;     move16();
  aRightReal = h_ps_dec->mHybridRealRight;   move16();
  aRightImag = h_ps_dec->mHybridImagRight;   move16();

  pppRealDelayRBufferSer = &h_ps_dec->aaaRealDelayRBufferSerSubQmf; move16();
  pppImagDelayRBufferSer = &h_ps_dec->aaaImagDelayRBufferSerSubQmf; move16();

  ppRealDelayBuffer = h_ps_dec->aaRealDelayBufferSubQmf;   move16();
  ppImagDelayBuffer = h_ps_dec->aaImagDelayBufferSubQmf;   move16();

  pFractDelayPhaseFactorRe = aFractDelayPhaseFactorReSubQmf; move16();
  pFractDelayPhaseFactorIm = aFractDelayPhaseFactorImSubQmf; move16();

  ppFractDelayPhaseFactorSerRe = aaFractDelayPhaseFactorSerReSubQmf; move16();
  ppFractDelayPhaseFactorSerIm = aaFractDelayPhaseFactorSerImSubQmf; move16();


  /*
    Calculate energies:
    Since all input samples are < 0.5, up to 4 squared values can be added
    without overflows. For wider groups, shifing becomes necessary.
    The actual scale of the energies does not matter, as long as it is kept
    constant for each group.
  */

  /* groups within the hybrid range */
  {
    Word16 re0, im0, re1, im1;

    re0 = etsiopround(aLeftReal[0]);
    im0 = etsiopround(aLeftImag[0]);
    re1 = etsiopround(aLeftReal[5]);
    im1 = etsiopround(aLeftImag[5]);

    aPower[0] = L_mult(re0, re0);
    aPower[0] = L_mac(aPower[0], im0, im0);
    aPower[0] = L_mac(aPower[0], re1, re1);
    aPower[0] = L_mac(aPower[0], im1, im1);

    re0 = etsiopround(aLeftReal[4]);
    im0 = etsiopround(aLeftImag[4]);
    re1 = etsiopround(aLeftReal[1]);
    im1 = etsiopround(aLeftImag[1]);

    aPower[1] = L_mult(re0, re0);
    aPower[1] = L_mac(aPower[1], im0, im0);
    aPower[1] = L_mac(aPower[1], re1, re1);
    aPower[1] = L_mac(aPower[1], im1, im1);
  }

  bin = 4-2; move16();
  for (gr=4; gr < SUBQMF_GROUPS; gr++) {
    Word16 re, im;
    sb = groupBorders[gr];
    re = etsiopround(aLeftReal[sb]);
    im = etsiopround(aLeftImag[sb]);
    aPower[bin] = L_mult(re, re);
    aPower[bin] = L_mac(aPower[bin], im, im);
    bin++;
  }

  aLeftReal = rIntBufferLeft;  move16();
  aLeftImag = iIntBufferLeft;  move16();

  /* groups above the hybrid range with a width of 1 channel */
  bin = NO_QMF_CHANNELS_IN_HYBRID+5; move16();
  for ( sb=NO_QMF_CHANNELS_IN_HYBRID; sb < NO_QMF_CHANNELS_IN_HYBRID+6; sb++) {
    Word16 re = etsiopround(aLeftReal[sb]);
    Word16 im = etsiopround(aLeftImag[sb]);
    aPower[bin] = L_mult(re, re);
    aPower[bin] = L_mac(aPower[bin], im, im);
    bin++;
  }

  /* wider groups above the hybrid range */
  bin=16-2; move16();
  for (gr=16; gr < NO_IID_GROUPS; gr++) {
    Word32 accu = 0, tmp = 0;
    Word16 re, im;

    maxsb = S_min(usb, groupBorders[gr+1]);

    for (sb = groupBorders[gr]; sb < maxsb; sb++) {
      re = etsiopround(aLeftReal[sb]);
      im = etsiopround(aLeftImag[sb]);

      tmp = L_mult(re, re);
      tmp = L_mac(tmp, im, im);
      tmp = L_shr(tmp, groupShift[gr - (SUBQMF_GROUPS+6)]);

      accu = L_add(accu, tmp);
    }
    aPower[bin] = accu;                                         move32();
    bin++;
  }

  aLeftReal = h_ps_dec->mHybridRealLeft;   move16();
  aLeftImag = h_ps_dec->mHybridImagLeft;   move16();


  /*
    Transient detector
  */
  for (bin=0; bin < NO_BINS; bin++) {

    aPower[bin] = L_max(0, aPower[bin]);                          move32();

    h_ps_dec->aPeakDecayFast[bin] = fixmul_32x16b(h_ps_dec->aPeakDecayFast[bin] , PEAK_DECAY_FACTOR); move32();

    test();
    if ( L_sub(h_ps_dec->aPeakDecayFast[bin], aPower[bin]) < 0) {
      h_ps_dec->aPeakDecayFast[bin] = aPower[bin];              move32();
    }

    peakDiff = L_add( fixmul_32x16b(h_ps_dec->aPrevPeakDiff[bin], 0x6000),
                      ( L_shr(L_sub(h_ps_dec->aPeakDecayFast[bin],aPower[bin]),2) ) );

    h_ps_dec->aPrevPeakDiff[bin] = peakDiff;                    move32();

    nrg = L_add(fixmul_32x16b(h_ps_dec->aPrevNrg[bin], 0x6000), L_shr(aPower[bin],2));
    h_ps_dec->aPrevNrg[bin] = nrg;                              move32();

    peakDiff = L_add(peakDiff, L_shr(peakDiff, 1));

    test();
    if ( L_sub(peakDiff, nrg) <= 0 ) {
      aTransRatio[bin] = 0x7fff;                                move16();
    }
    else {
      aTransRatio[bin] = extract_l(ffr_divide16(nrg, peakDiff));
    }
  } /* bin */


  /*
    Filtering part 1: Sub-QMF bands
  */
  delayBufIndex = h_ps_dec->delayBufIndex;  move16();
  for (sb=0; sb < SUBQMF_GROUPS; sb++) {
    Word16 rTmp, iTmp, rTmp0, iTmp0, rIn, iIn, bin;

    rTmp0 = ppRealDelayBuffer[sb][delayBufIndex];
    iTmp0 = ppImagDelayBuffer[sb][delayBufIndex];

    rIn = sub( mult(rTmp0, pFractDelayPhaseFactorRe[sb]), mult(iTmp0, pFractDelayPhaseFactorIm[sb]) );
    iIn = add( mult(rTmp0, pFractDelayPhaseFactorIm[sb]), mult(iTmp0, pFractDelayPhaseFactorRe[sb]) );

    ppRealDelayBuffer[sb][delayBufIndex] = etsiopround(aLeftReal[sb]); move16();
    ppImagDelayBuffer[sb][delayBufIndex] = etsiopround(aLeftImag[sb]); move16();

    for (m=0; m<NO_SERIAL_ALLPASS_LINKS ; m++) {
      Word16 decay;
      Word16 delayRBufIndexSer_m;
      delayRBufIndexSer_m = h_ps_dec->aDelayRBufIndexSer[m]; move16();
      rTmp0 = (*pppRealDelayRBufferSer)[m][delayRBufIndexSer_m][sb]; move16();
      iTmp0 = (*pppImagDelayRBufferSer)[m][delayRBufIndexSer_m][sb]; move16();

      rTmp = sub( mult(rTmp0, ppFractDelayPhaseFactorSerRe[m][sb]), mult(iTmp0, ppFractDelayPhaseFactorSerIm[m][sb]) );
      iTmp = add( mult(rTmp0, ppFractDelayPhaseFactorSerIm[m][sb]), mult(iTmp0, ppFractDelayPhaseFactorSerRe[m][sb]) );

      decay = aRevLinkDecaySer[m]; move16();

      rTmp = sub(rTmp, mult(rIn, decay));
      iTmp = sub(iTmp, mult(iIn, decay));

      (*pppRealDelayRBufferSer)[m][delayRBufIndexSer_m][sb] = add(rIn, mult(rTmp, decay)); move16();
      (*pppImagDelayRBufferSer)[m][delayRBufIndexSer_m][sb] = add(iIn, mult(iTmp, decay)); move16();

      rIn = rTmp; move16();
      iIn = iTmp; move16();
    }

    bin = aHybridToBin[sb];                                     move16();
    aRightReal[sb] = L_mult(rIn, aTransRatio[bin]);             move32(); 
    aRightImag[sb] = L_mult(iIn, aTransRatio[bin]);             move32();
  }



  /*
    Filtering part 2: QMF bands up to NO_ALLPASS_CHANNELS
  */
  aLeftReal = rIntBufferLeft;     move16();
  aLeftImag = iIntBufferLeft;     move16();
  aRightReal = rIntBufferRight;   move16();
  aRightImag = iIntBufferRight;   move16();

  pppRealDelayRBufferSer = &h_ps_dec->aaaRealDelayRBufferSerQmf; move16();
  pppImagDelayRBufferSer = &h_ps_dec->aaaImagDelayRBufferSerQmf; move16();

  ppRealDelayBuffer = h_ps_dec->aaRealDelayBufferQmf; move16();
  ppImagDelayBuffer = h_ps_dec->aaImagDelayBufferQmf; move16();

  pFractDelayPhaseFactorRe = aFractDelayPhaseFactorReQmf; move16();
  pFractDelayPhaseFactorIm = aFractDelayPhaseFactorImQmf; move16();

  ppFractDelayPhaseFactorSerRe = aaFractDelayPhaseFactorSerReQmf; move16();
  ppFractDelayPhaseFactorSerIm = aaFractDelayPhaseFactorSerImQmf; move16();


  for (sb = NO_QMF_CHANNELS_IN_HYBRID; sb < NO_ALLPASS_CHANNELS; sb++) {
    Word16 rTmp, iTmp, rTmp0, iTmp0, rIn, iIn, decayScaleFactor;

    sb_delay = sub(sb, NO_QMF_CHANNELS_IN_HYBRID);
    /* decayScaleFactor = 0x7fff - sb_delay * DECAY_SLOPE */
    decayScaleFactor = extract_l(L_shr(L_msu(0x0000fffeL,
                                             sb_delay,DECAY_SLOPE),1));

    rTmp0 = ppRealDelayBuffer[sb_delay][delayBufIndex]; move16();
    iTmp0 = ppImagDelayBuffer[sb_delay][delayBufIndex]; move16();

    rIn = sub( mult(rTmp0, pFractDelayPhaseFactorRe[sb_delay]), mult(iTmp0, pFractDelayPhaseFactorIm[sb_delay]) );
    iIn = add( mult(rTmp0, pFractDelayPhaseFactorIm[sb_delay]), mult(iTmp0, pFractDelayPhaseFactorRe[sb_delay]) );

    ppRealDelayBuffer[sb_delay][delayBufIndex] = etsiopround(aLeftReal[sb]); move16();
    ppImagDelayBuffer[sb_delay][delayBufIndex] = etsiopround(aLeftImag[sb]); move16();

    for (m=0; m<NO_SERIAL_ALLPASS_LINKS ; m++) {
      Word16 decay;
      Word16 delayRBufIndexSer_m;
      delayRBufIndexSer_m = h_ps_dec->aDelayRBufIndexSer[m]; move16();

      rTmp0 = (*pppRealDelayRBufferSer)[m][delayRBufIndexSer_m][sb_delay]; move16();
      iTmp0 = (*pppImagDelayRBufferSer)[m][delayRBufIndexSer_m][sb_delay]; move16();

      rTmp = sub( mult(rTmp0, ppFractDelayPhaseFactorSerRe[m][sb_delay]), mult(iTmp0, ppFractDelayPhaseFactorSerIm[m][sb_delay]) );
      iTmp = add( mult(rTmp0, ppFractDelayPhaseFactorSerIm[m][sb_delay]), mult(iTmp0, ppFractDelayPhaseFactorSerRe[m][sb_delay]) );

      decay = mult(decayScaleFactor, aRevLinkDecaySer[m]);

      rTmp = sub(rTmp, mult(rIn, decay));
      iTmp = sub(iTmp, mult(iIn, decay));

      (*pppRealDelayRBufferSer)[m][delayRBufIndexSer_m][sb_delay] = add(rIn, mult(rTmp, decay)); move16();
      (*pppImagDelayRBufferSer)[m][delayRBufIndexSer_m][sb_delay] = add(iIn, mult(iTmp, decay)); move16();

      rIn = rTmp; move16();
      iIn = iTmp; move16();
    }

    bin = aDelayToBin[sb_delay]; move16();
    aRightReal[sb] = L_mult(rIn, aTransRatio[bin]);             move32();
    aRightImag[sb] = L_mult(iIn, aTransRatio[bin]);             move32();
  }


  /*
    Filtering part 3: Remaining QMF bands
  */
  {
    /* Group 20: 14 samples delay */
    Word16 transRatio = aTransRatio[18];
    maxsb = S_min(usb, groupBorders[21]);
    delayBufIndex = h_ps_dec->delayBufIndexLong; move16();
    sb_delay = sub(groupBorders[20],NO_QMF_CHANNELS_IN_HYBRID); 
    for (sb = groupBorders[20]; sb < maxsb; sb++) {
      Word16 rIn, iIn;

      rIn = ppRealDelayBuffer[sb_delay][delayBufIndex]; move16();
      iIn = ppImagDelayBuffer[sb_delay][delayBufIndex]; move16();

      ppRealDelayBuffer[sb_delay][delayBufIndex] = etsiopround(aLeftReal[sb]); move16();
      ppImagDelayBuffer[sb_delay][delayBufIndex] = etsiopround(aLeftImag[sb]); move16();

      aRightReal[sb] = L_mult(rIn, transRatio);                 move32();
      aRightImag[sb] = L_mult(iIn, transRatio);                 move32();
      sb_delay++;
    }

    h_ps_dec->delayBufIndexLong = add(h_ps_dec->delayBufIndexLong,1); move16();
    test();
    if (sub(h_ps_dec->delayBufIndexLong, 14) >= 0) {
      h_ps_dec->delayBufIndexLong = 0;                          move16();
    }

    /* Group 21: 1 sample delay */
    transRatio = aTransRatio[19];                               move16();
    maxsb = S_min(usb, groupBorders[22]);
    sb_delay = sub(groupBorders[21],NO_QMF_CHANNELS_IN_HYBRID);
    for (sb = groupBorders[21]; sb < maxsb; sb++) {
      Word16 rIn, iIn;

      rIn = ppRealDelayBuffer[sb_delay][0];  move16();
      iIn = ppImagDelayBuffer[sb_delay][0];  move16();

      ppRealDelayBuffer[sb_delay][0] = etsiopround(aLeftReal[sb]); move16();
      ppImagDelayBuffer[sb_delay][0] = etsiopround(aLeftImag[sb]); move16();

      aRightReal[sb] = L_mult(rIn, transRatio);                 move32();
      aRightImag[sb] = L_mult(iIn, transRatio);                 move32();
      sb_delay++;
    }
  }


  /*
    Clear all unused QMF channels
  */
  for (sb = usb; sb < NO_SYNTHESIS_CHANNELS; sb++) {
    aRightReal[sb] = 0;                                         move32();
    aRightImag[sb] = 0;                                         move32();
  }


  /*
    Increase delay indices
  */
  h_ps_dec->delayBufIndex = add(h_ps_dec->delayBufIndex,1);
  test();
  if ( sub(h_ps_dec->delayBufIndex, DELAY_ALLPASS) >= 0 ) {
    h_ps_dec->delayBufIndex = 0;                                move16();
  }

  for (m=0; m<NO_SERIAL_ALLPASS_LINKS ; m++) {
    test();
    h_ps_dec->aDelayRBufIndexSer[m] = add(h_ps_dec->aDelayRBufIndexSer[m],1);
    if ( sub(h_ps_dec->aDelayRBufIndexSer[m], h_ps_dec->aNoSampleDelayRSer[m]) >= 0 ) {
      h_ps_dec->aDelayRBufIndexSer[m] = 0;                      move16();
    }
  }


} /* END deCorrelate */


/*!
  \brief   Cosine function by table lookup
  \return  cos(4*phiDiv4)
*/
static Word16 cos512(Word16 phiDiv4) /*!< Angle scaled by 1/4 */
{
  Word16 index;
  const Word32 rescale = 0x0517cc1b;

  /* Map phi from [-PI..PI] to [-1024..1024] */
  index = etsiopround( L_abs(fixmul_32x16b(rescale, phiDiv4)) );
  logic16();
  index = index & (Word16)(2*TRIG_DATA_SIZE - 1);
  
  test();
  if ( sub(index,TRIG_DATA_SIZE) < 0 ) {
    /* 0 < phi < PI/2 */
    sub(TRIG_DATA_SIZE, index);
    return trigData[TRIG_DATA_SIZE - index];
  }
  else {
    /* PI/2 < phi < PI */
    sub(TRIG_DATA_SIZE, index); 
    return negate(trigData[index - TRIG_DATA_SIZE]);
  }
  
}


/*!
  \brief   Sine function by table lookup
  \return  sin(4*phiDiv4)
*/
static Word16 sin512(Word16 phiDiv4) /*!< Angle scaled by 1/4 */
{
  Word16 index;
  const Word32 rescale = 0x0517cc1b;

  /* Map phi from [-PI..PI] to [-1024..1024] */
  index = etsiopround( fixmul_32x16b(rescale, phiDiv4) );
  
  test();
  if (index < 0) {
    
    logic16();
    index = negate(index) & (Word16)(2*TRIG_DATA_SIZE - 1);
    
    test();
    if ( sub(index, TRIG_DATA_SIZE) < 0 ) {
      /* -PI/2 < phi < 0 */
      return negate(trigData[index]);
    }
    else {
      /* -PI < phi < PI/2 */
      sub(2*TRIG_DATA_SIZE, index); 
      return negate(trigData[2*TRIG_DATA_SIZE - index]);
    }
  }
  else {
    
    logic16();
    index = index & (Word16)(2*TRIG_DATA_SIZE - 1);
    
    test();
    if ( sub(index,TRIG_DATA_SIZE) < 0 ) {
      /* 0 < phi < PI/2 */
      return  trigData[index];
    }
    else {
      /* PI/2 < phi < PI */
      sub(TRIG_DATA_SIZE, index);
      return trigData[2*TRIG_DATA_SIZE - index];
    }
  }

}


/*!
  \brief  Initialize rotation
*/
void
InitRotationEnvelope(HANDLE_PS_DEC hPS, /*!< Parametric stereo handle */
                     Word16 env,        /*!< Number of envelope */
                     Word16 usb)        /*!< Uppermost QMF channel + 1 */
{
  Word16  group, bin, noIidSteps;
  Word16  scaleL, scaleR;
  Word32  alpha, beta;
  Word16  h11, h12, h21, h22;
  Word16  invEnvLength;
  const Word16 *pScaleFactors;

  test();
  if (env == 0)
  {
    Word16 lastUsb = hPS->usb;
    hPS->usb = usb;                                             move16();

    test(); test();
    if (sub(usb, lastUsb) > 0 && lastUsb) {
      Word16 sb, i, j, delay;

      for (sb = lastUsb - NO_QMF_CHANNELS_IN_HYBRID; sb < usb - NO_QMF_CHANNELS_IN_HYBRID; sb++)
      {
        if (sub(sb, NO_QMF_ALLPASS_CHANNELS)< 0) {
          for (i=0 ; i < NO_SERIAL_ALLPASS_LINKS ; i++) {
            for (j = 0; j < hPS->aNoSampleDelayRSer[i]; j++) {
              hPS->aaaRealDelayRBufferSerQmf[i][j][sb] = 0; move16();
              hPS->aaaImagDelayRBufferSerQmf[i][j][sb] = 0; move16();
            }
          }
        }
        else {
          if (sub(sb,NO_QMF_ALLPASS_CHANNELS+SHORT_DELAY_START) < 0) {
            delay = LONG_DELAY;  move16();
          } else {
            delay = SHORT_DELAY; move16();
          }

          memset(hPS->aaRealDelayBufferQmf[sb],0,delay*sizeof(Word16)); memop16(delay);
          memset(hPS->aaImagDelayBufferQmf[sb],0,delay*sizeof(Word16)); memop16(delay);
        }
      }
    }
  }

  test();
  if (hPS->bFineIidQ)
  {
    noIidSteps = NO_IID_STEPS_FINE;                             move16();
    pScaleFactors = scaleFactorsFine;                           move16();
  }
  else{
    noIidSteps = NO_IID_STEPS;                                  move16();
    pScaleFactors = scaleFactors;                               move16();
  }

  invEnvLength = sbr_invIntTable[ sub(hPS->aEnvStartStop[env + 1], hPS->aEnvStartStop[env]) ]; move16();
 
  for ( group = 0; group < NO_IID_GROUPS; group++ )
  {
    Word16 bplusa, bminusa;
    Word16 noIidIndex, noIccIndex;

    bin = aGroupToBin[group];  move16();

    noIidIndex = hPS->aaIidIndex[env][bin]; move16();
    noIccIndex = hPS->aaIccIndex[env][bin]; move16();

    scaleR = pScaleFactors[add(noIidSteps, noIidIndex)]; move16();
    scaleL = pScaleFactors[sub(noIidSteps, noIidIndex)]; move16();

    beta   = fixmul_32x16b( L_mult(alphas[noIccIndex], sub(scaleR,scaleL)), PSC_SQRT05F);
    alpha  = L_shr( L_deposit_h(alphas[noIccIndex]), 1); /* multiply by 0.5 */
    /* alpha and beta are now scaled by 1/4 */

    bplusa  = etsiopround( L_add(beta, alpha) );
    bminusa = etsiopround( L_sub(beta, alpha) );

    h11 = mult(cos512(bplusa), scaleL);
    h12 = mult(cos512(bminusa), scaleR);
    h21 = mult(sin512(bplusa), scaleL);
    h22 = mult(sin512(bminusa), scaleR);


    hPS->deltaH11[group]  = mult(invEnvLength, sub(h11,hPS->h11Prev[group])); move16();
    hPS->deltaH12[group]  = mult(invEnvLength, sub(h12,hPS->h12Prev[group])); move16();
    hPS->deltaH21[group]  = mult(invEnvLength, sub(h21,hPS->h21Prev[group])); move16();
    hPS->deltaH22[group]  = mult(invEnvLength, sub(h22,hPS->h22Prev[group])); move16();

    hPS->H11[group]  = hPS->h11Prev[group];                     move16();
    hPS->H12[group]  = hPS->h12Prev[group];                     move16();
    hPS->H21[group]  = hPS->h21Prev[group];                     move16();
    hPS->H22[group]  = hPS->h22Prev[group];                     move16();

    hPS->h11Prev[group] = h11;                                  move16();
    hPS->h12Prev[group] = h12;                                  move16();
    hPS->h21Prev[group] = h21;                                  move16();
    hPS->h22Prev[group] = h22;                                  move16();
  } /* groups loop */


} /* END InitRotationEnvelope */



/*!
  \brief  Rotation
*/
static void
applyRotation( HANDLE_PS_DEC  hPS,
               Word32        *qmfLeftReal,
               Word32        *qmfLeftImag,
               Word32        *qmfRightReal,
               Word32        *qmfRightImag
             )
{
  Word16   group, subband, maxSubband, usb;
  Word32  *hybrLeftReal;
  Word32  *hybrLeftImag;
  Word32  *hybrRightReal;
  Word32  *hybrRightImag;
  Word32   tempLeftReal, tempLeftImag;
  Word32   tempRightReal, tempRightImag;

  usb = hPS->usb;

  /*
    Apply rotation on sub-QMF bands
  */
  hybrLeftReal  = hPS->mHybridRealLeft;   move16();
  hybrLeftImag  = hPS->mHybridImagLeft;   move16();
  hybrRightReal = hPS->mHybridRealRight;  move16();
  hybrRightImag = hPS->mHybridImagRight;  move16();

  for ( subband = 0; subband < SUBQMF_GROUPS; subband++ )
  {
    hPS->H11[subband] = add(hPS->H11[subband], hPS->deltaH11[subband]); move16();
    hPS->H12[subband] = add(hPS->H12[subband], hPS->deltaH12[subband]); move16();
    hPS->H21[subband] = add(hPS->H21[subband], hPS->deltaH21[subband]); move16();
    hPS->H22[subband] = add(hPS->H22[subband], hPS->deltaH22[subband]); move16();

    tempLeftReal  = L_add(fixmul_32x16b(hybrLeftReal[subband], hPS->H11[subband]), fixmul_32x16b(hybrRightReal[subband], hPS->H21[subband]));
    tempLeftImag  = L_add(fixmul_32x16b(hybrLeftImag[subband], hPS->H11[subband]), fixmul_32x16b(hybrRightImag[subband], hPS->H21[subband]));
    tempRightReal = L_add(fixmul_32x16b(hybrLeftReal[subband], hPS->H12[subband]), fixmul_32x16b(hybrRightReal[subband], hPS->H22[subband]));
    tempRightImag = L_add(fixmul_32x16b(hybrLeftImag[subband], hPS->H12[subband]), fixmul_32x16b(hybrRightImag[subband], hPS->H22[subband]));

    hybrLeftReal [subband] = L_shl(tempLeftReal,1);             move32();
    hybrLeftImag [subband] = L_shl(tempLeftImag,1);             move32();
    hybrRightReal[subband] = L_shl(tempRightReal,1);            move32();
    hybrRightImag[subband] = L_shl(tempRightImag,1);            move32();
  } /* subband loop */

  /*
    Apply rotation on remaining QMF bands
  */
  hybrLeftReal  = qmfLeftReal;    move16();
  hybrLeftImag  = qmfLeftImag;    move16();
  hybrRightReal = qmfRightReal;   move16();
  hybrRightImag = qmfRightImag;   move16();

  for ( group = SUBQMF_GROUPS; group < NO_IID_GROUPS; group++ )
  {
    maxSubband = S_min(usb, groupBorders[group + 1]);

    hPS->H11[group] = add(hPS->H11[group], hPS->deltaH11[group]); move16();
    hPS->H12[group] = add(hPS->H12[group], hPS->deltaH12[group]); move16();
    hPS->H21[group] = add(hPS->H21[group], hPS->deltaH21[group]); move16();
    hPS->H22[group] = add(hPS->H22[group], hPS->deltaH22[group]); move16();

    for ( subband = groupBorders[group]; subband < maxSubband; subband++ )
    {
      tempLeftReal  = L_add(fixmul_32x16b(hybrLeftReal[subband], hPS->H11[group]), fixmul_32x16b(hybrRightReal[subband], hPS->H21[group]) );
      tempLeftImag  = L_add(fixmul_32x16b(hybrLeftImag[subband], hPS->H11[group]), fixmul_32x16b(hybrRightImag[subband], hPS->H21[group]) );
      tempRightReal = L_add(fixmul_32x16b(hybrLeftReal[subband], hPS->H12[group]), fixmul_32x16b(hybrRightReal[subband], hPS->H22[group]) );
      tempRightImag = L_add(fixmul_32x16b(hybrLeftImag[subband], hPS->H12[group]), fixmul_32x16b(hybrRightImag[subband], hPS->H22[group]) );

      hybrLeftReal [subband] = L_shl(tempLeftReal, 1);          move32();
      hybrLeftImag [subband] = L_shl(tempLeftImag, 1);          move32();
      hybrRightReal[subband] = L_shl(tempRightReal, 1);         move32();
      hybrRightImag[subband] = L_shl(tempRightImag, 1);         move32();
    } /* subband loop */
  } /* groups loop */

} /* END applyRotation */

#endif
