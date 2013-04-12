/*
   hybrid filter bank
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "ffr.h"
#include "hybrid.h"
#include "sbr_rom.h"
#include "dsp_fft32x32s.h"
#include "count.h"


/*!
  \brief  2-channel real-valued filtering with 6-tap delay
*/
static void twoChannelFiltering( const Word32 *pQmf,
                                 Word32 *mHybrid )
{
  Word16 n, p;
  Word32 cum0, cum1;

  /*
    Apply polyphase filters
  */

  /* First filter has one nonzero coefficient only. */
  cum0 = L_shr(pQmf[HYBRID_FILTER_DELAY], 1);
  cum1 = 0L;             move32();

  /* Second filter. */
  p=1; move16(); /* initialize the 2*n+1 counter */
  for(n = 0; n < 6; n++) {
    /* pQmf[2*n+1] */
    cum1 = L_add(cum1, fixmul_32x16b(pQmf[p], p2_6[n]));
    p += 2;
  }

  /*
    Combine polyphase output
  */
  mHybrid[0] = L_add(cum0, cum1);       move32();
  mHybrid[1] = L_sub(cum0, cum1);       move32();
}


/*!
  \brief  8-channel complex-valued filtering with 6-tap delay
*/
static void eightChannelFiltering( const Word32 *pQmfReal,
                                   const Word32 *pQmfImag,
                                   Word32 *mHybridReal,
                                   Word32 *mHybridImag )
{
  const Word16 tcos = 0x7642; /*!< cos(PI/8) */
  const Word16 tsin = 0x30fc; /*!< sin(PI/8) */
  const Word16 tcom = 0x5a82; /*!< cos(PI/4) = sin(PI/4) */
  Word32 real, imag;
  Word32 cum[16];

  /*
    Apply polyphase filters
  */

  /* First filter has two taps. */
  real = L_add(fixmul_32x16b(pQmfReal[4], p8_13[4]), fixmul_32x16b(pQmfReal[12], p8_13[12]));
  imag = L_add(fixmul_32x16b(pQmfImag[4], p8_13[4]), fixmul_32x16b(pQmfImag[12], p8_13[12]));

  /* Multiply with twiddle factors. */
  cum[4] = fixmul_32x16b(  L_sub(imag, real), tcom);                              move32();
  cum[5] = fixmul_32x16b(L_negate(L_add(imag, real)), tcom);                      move32();

  /* Second filter has two taps. */
  real = L_add(fixmul_32x16b(pQmfReal[3], p8_13[3]), fixmul_32x16b(pQmfReal[11], p8_13[11]));
  imag = L_add(fixmul_32x16b(pQmfImag[3], p8_13[3]), fixmul_32x16b(pQmfImag[11], p8_13[11]));

  /* Multiply with twiddle factors. */
  cum[6] = L_sub(fixmul_32x16b(imag, tcos), fixmul_32x16b(real, tsin));           move32();
  cum[7] = L_negate(L_add(fixmul_32x16b(imag, tsin), fixmul_32x16b(real, tcos))); move32();

  /* Third filter has two taps. */
  cum[9] = fixmul_32x16b(L_sub(pQmfReal[2], pQmfReal[10]), p8_13[10]);            move32();
  cum[8] = fixmul_32x16b(L_sub(pQmfImag[2], pQmfImag[10]), p8_13[2]);             move32();

  /* Fourth filter has two taps. */
  real = L_add(fixmul_32x16b(pQmfReal[1], p8_13[1]), fixmul_32x16b(pQmfReal[9], p8_13[9]));
  imag = L_add(fixmul_32x16b(pQmfImag[1], p8_13[1]), fixmul_32x16b(pQmfImag[9], p8_13[9]));

  /* Multiply with twiddle factors. */
  cum[10] = L_add(fixmul_32x16b(imag, tcos), fixmul_32x16b(real, tsin));          move32();
  cum[11] = L_sub(fixmul_32x16b(imag, tsin), fixmul_32x16b(real, tcos));          move32();

  /* Fifth filter has two taps. */
  real = L_add(fixmul_32x16b(pQmfReal[0], p8_13[0]), fixmul_32x16b(pQmfReal[8], p8_13[8]));
  imag = L_add(fixmul_32x16b(pQmfImag[0], p8_13[0]), fixmul_32x16b(pQmfImag[8], p8_13[8]));

  /* Multiply with twiddle factors. */
  cum[12] = fixmul_32x16b(L_add(imag, real), tcom);                               move32();
  cum[13] = fixmul_32x16b(L_sub(imag, real), tcom);                               move32();

  /* Sixth filter has one tap. */
  real = fixmul_32x16b(pQmfReal[7], p8_13[7]);
  imag = fixmul_32x16b(pQmfImag[7], p8_13[7]);

  /* Multiply with twiddle factors. */
  cum[14] = L_add(fixmul_32x16b(imag, tsin), fixmul_32x16b(real, tcos));          move32();
  cum[15] = L_sub(fixmul_32x16b(imag, tcos), fixmul_32x16b(real, tsin));          move32();

  /* Seventh filter has one tap. */
  cum[0] = fixmul_32x16b(pQmfReal[HYBRID_FILTER_DELAY], p8_13[HYBRID_FILTER_DELAY]);move32();
  cum[1] = fixmul_32x16b(pQmfImag[HYBRID_FILTER_DELAY], p8_13[HYBRID_FILTER_DELAY]);move32();

  /* Eighth filter has one tap. */
  real = fixmul_32x16b(pQmfReal[5], p8_13[5]);
  imag = fixmul_32x16b(pQmfImag[5], p8_13[5]);

  /* Multiply with twiddle factors. */
  cum[2] = L_sub(fixmul_32x16b(real, tcos), fixmul_32x16b(imag, tsin));           move32();
  cum[3] = L_add(fixmul_32x16b(real, tsin), fixmul_32x16b(imag, tcos));           move32();

  /*
    8-point inverse FFT
  */
  inv_dit_fft_8pt(cum, mHybridReal, mHybridImag);

}


/**************************************************************************/
/*!
  \brief  Hybrid filterbank analysis
*/
/**************************************************************************/
void
HybridAnalysis ( const Word32 *mQmfReal, /*!< Real part of QMF timeslot */
                 const Word32 *mQmfImag, /*!< Imag part of QMF timeslot */
                 Word32 *mHybridReal,    /*!< Real part of hybrid sub-subsamples */
                 Word32 *mHybridImag,    /*!< Imag part of hybrid sub-subsamples */
                 HANDLE_HYBRID hHybrid,  /*!< Handle to hybrid filterbank struct */
                 Word16 scale)           /*!< Scaling required for QMF input */

{
  Word16 band;
  Word8 chOffset = 0;

  move16();

  for(band = 0; band < NO_QMF_CHANNELS_IN_HYBRID; band++) {

    memcpy(hHybrid->pWorkReal, hHybrid->mQmfBufferReal[band],
           hHybrid->qmfBufferMove * sizeof(Word32));                            memop32(hHybrid->qmfBufferMove);

    memcpy(hHybrid->pWorkImag, hHybrid->mQmfBufferImag[band],
           hHybrid->qmfBufferMove * sizeof(Word32));                            memop32(hHybrid->qmfBufferMove);

    hHybrid->pWorkReal [hHybrid->qmfBufferMove] = L_shr(mQmfReal[band], scale); move32();
    hHybrid->pWorkImag [hHybrid->qmfBufferMove] = L_shr(mQmfImag[band], scale); move32();

    memcpy(hHybrid->mQmfBufferReal[band], hHybrid->pWorkReal + 1,
           hHybrid->qmfBufferMove * sizeof(Word32));                            memop32(hHybrid->qmfBufferMove);

    memcpy(hHybrid->mQmfBufferImag[band], hHybrid->pWorkImag + 1,
           hHybrid->qmfBufferMove * sizeof(Word32));                            memop32(hHybrid->qmfBufferMove);

    switch(hHybrid->pResolution[band]) {
    case NO_HYBRID_CHANNELS_LOW:
      test();
      twoChannelFiltering( hHybrid->pWorkReal,
                           hHybrid->mTempReal );

      twoChannelFiltering( hHybrid->pWorkImag,
                           hHybrid->mTempImag );

      mHybridReal [chOffset] = hHybrid->mTempReal [0];                          move32();
      mHybridImag [chOffset] = hHybrid->mTempImag [0];                          move32();
      mHybridReal [chOffset + 1] = hHybrid->mTempReal [1];                      move32();
      mHybridImag [chOffset + 1] = hHybrid->mTempImag [1];                      move32();

      chOffset += 2;

      break;
    case NO_HYBRID_CHANNELS_HIGH:
      test();test();
      eightChannelFiltering( hHybrid->pWorkReal,
                             hHybrid->pWorkImag,
                             hHybrid->mTempReal,
                             hHybrid->mTempImag );

      mHybridReal [chOffset + 0] = hHybrid->mTempReal [0];                      move32();
      mHybridImag [chOffset + 0] = hHybrid->mTempImag [0];                      move32();
      mHybridReal [chOffset + 1] = hHybrid->mTempReal [1];                      move32();
      mHybridImag [chOffset + 1] = hHybrid->mTempImag [1];                      move32();
      mHybridReal [chOffset + 2] = L_add(hHybrid->mTempReal [2], hHybrid->mTempReal [5]); move32();
      mHybridImag [chOffset + 2] = L_add(hHybrid->mTempImag [2], hHybrid->mTempImag [5]); move32();
      mHybridReal [chOffset + 3] = L_add(hHybrid->mTempReal [3], hHybrid->mTempReal [4]); move32();
      mHybridImag [chOffset + 3] = L_add(hHybrid->mTempImag [3], hHybrid->mTempImag [4]); move32();
      mHybridReal [chOffset + 4] = hHybrid->mTempReal [6];                      move32();
      mHybridImag [chOffset + 4] = hHybrid->mTempImag [6];                      move32();
      mHybridReal [chOffset + 5] = hHybrid->mTempReal [7];                      move32();
      mHybridImag [chOffset + 5] = hHybrid->mTempImag [7];                      move32();

      chOffset += 6;

      break;
    default:
      assert(0);
    }
  }

}


/**************************************************************************/
/*!
  \brief  Hybrid filterbank synthesis
*/
/**************************************************************************/
void
HybridSynthesis ( const Word32 *mHybridReal, /*!< Real part of hybrid sub-subsamples */
                  const Word32 *mHybridImag, /*!< Imag part of hybrid sub-subsamples */
                  Word32 *mQmfReal,          /*!< Real part of QMF timeslot */
                  Word32 *mQmfImag,          /*!< Imag part of QMF timeslot */
                  HANDLE_HYBRID hHybrid )    /*!< Handle to hybrid filterbank struct */
{
  Word16 k, band;
  Word16 hybridRes;
  Word8  chOffset = 0;

  move16();

  for(band = 0; band < NO_QMF_CHANNELS_IN_HYBRID; band++) {

    mQmfReal[band] = mQmfImag[band] = 0;                        move32(); move32();
    hybridRes = S_min(hHybrid->pResolution[band],6);

    for(k = 0; k < hybridRes; k++) {
      mQmfReal[band] = L_add(mQmfReal[band], mHybridReal[chOffset + k]);        move32();
      mQmfImag[band] = L_add(mQmfImag[band], mHybridImag[chOffset + k]);        move32();
    }

    chOffset += hybridRes;
  }
}


/**************************************************************************/
/*!
  \brief    Initialize buffers for hybrid filterbank

  \return   errorCode, 0 if successful.
*/
/**************************************************************************/
int
CreateHybridFilterBank ( HANDLE_HYBRID hs, /*!< Handle to HYBRID struct. */
                         Word32 **pPtr)    /*!< Memory to be assigned to internal buffers */
{
  Word16 i, ptr_step;
  Word32 *ptr = (Word32*)*pPtr;

  hs->pResolution = pHybridResolution;                          move16();
  hs->qmfBufferMove = HYBRID_FILTER_LENGTH - 1;                 move16();

  ptr_step = add(1, hs->qmfBufferMove);
  hs->pWorkReal = ptr;                                          move16();
  ptr += ptr_step;
  hs->pWorkImag = ptr;                                          move16();
  ptr += ptr_step;

  for (i = 0; i < NO_QMF_CHANNELS_IN_HYBRID; i++) {
    hs->mQmfBufferReal[i] = ptr;                                move16();
    ptr += hs->qmfBufferMove;
    memset(hs->mQmfBufferReal[i],0,hs->qmfBufferMove*sizeof(Word32));   memop32(hs->qmfBufferMove);

    hs->mQmfBufferImag[i] = ptr;                                move16();
    ptr += hs->qmfBufferMove;
    memset(hs->mQmfBufferImag[i],0,hs->qmfBufferMove*sizeof(Word32));   memop32(hs->qmfBufferMove);
  }

  hs->mTempReal = ptr;                                          move16();
  ptr += NO_HYBRID_CHANNELS_HIGH;
  memset(hs->mTempReal, 0, NO_HYBRID_CHANNELS_HIGH*sizeof(Word32));     memop32(NO_HYBRID_CHANNELS_HIGH);

  hs->mTempImag = ptr;                                          move16();
  ptr += NO_HYBRID_CHANNELS_HIGH;
  memset(hs->mTempImag, 0, NO_HYBRID_CHANNELS_HIGH*sizeof(Word32));     memop32(NO_HYBRID_CHANNELS_HIGH);

  /* Update pointer of the calling function */
  *pPtr = ptr;                                                  move16();

  return 0;
}

