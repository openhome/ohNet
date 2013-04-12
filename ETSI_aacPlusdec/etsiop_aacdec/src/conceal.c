/*
   independent channel concealment
 */

#include "conceal.h"
#include "aac_rom.h"
#include "aac_ram.h"
#include "sbr_rom.h"
#include "count.h"
#include "intrinsics.h"

#ifdef LP_SBR_ONLY
extern const Word16 sbr_randomPhase[AAC_NF_NO_RANDOM_VAL + 48];
#else
extern const Word32 sbr_randomPhase[AAC_NF_NO_RANDOM_VAL + 48];
#endif

#define N_FADE_IN_FRAMES  5  /*!< no of frames for rising slope */
#define N_VALID_FRAMES    5  /*!< Valid frames until rising slope starts again after mute state */
#define N_FADE_OUT_FRAMES 5  /*!< no of frames for falling slope */


static const Word16 facMod4Table[4] = {
  0x4000,
  0x4c1b,
  0x5a82,
  0x6ba2
};


static const Word16 fadeFacTable[5] = {
  0x5a82,  /* MINUS_3dB */
  0x4000,  /* MINUS_3dB * MINUS_3dB */
  0x2d41,
  0x2000,
  0x16a1   /* MINUS_3dB * MINUS_3dB * MINUS_3dB * MINUS_3dB * MINUS_3dB */
};


static 
void CConcealment_UpdateState (CConcealmentInfo *pConcealmentInfo,
                               Flag FrameOk,
                               Word16  ch
                               );

static 
void CConcealment_ApplyRandomSign (CConcealmentInfo *pConcealmentInfo,
                                   Word32 *spec);
static
void CConcealment_CalcBandEnergy (Word32                    *spectrum,
                                  Word16                     blockType,
                                  Word32                     samplingRateIndex,
                                  CConcealmentExpandType     ex,
                                  Word16                    *sfbEnergy);

static
void CConcealment_InterpolateBuffer (Word32       *spectrum,
                                     Word16       *pSpecScalePrev,
                                     Word16       *pSpecScaleAct,
                                     Word16       *pSpecScaleOut,
                                     Word16       *enPrev,
                                     Word16       *enAct,
                                     Word16        sfbCnt,
                                     const Word16 *pSfbOffset);




/*!
  \brief Init concealment information

  The function initializes the concealment information.

  \return  none
*/
CConcealmentInfo*
CConcealment_Init (Word16 maxChan           /*!< max channels */
                   )
{
  Word16 i;
  Word16  ch;

  CConcealmentInfo *pConcealmentInfo = &ConcealmentInfoInstance;                                   move16();

  for(ch=0; ch<maxChan; ch++){
    for (i = 0; i < FRAME_SIZE; i++) {
      pConcealmentInfo->SpectralCoefficient[ch][i] = 0;                                            move32();
    }

    for (i = 0; i < MAX_WINDOWS; i++) {
      pConcealmentInfo->SpecScale[ch][i] = 0;                                                      move16();
    }

    pConcealmentInfo->WindowSequence[ch] = 0;                                                      move16();
    pConcealmentInfo->WindowShape[ch] = 0;                                                         move16();
    pConcealmentInfo->prevFrameOk[ch][0] = pConcealmentInfo->prevFrameOk[ch][1] = 0;               move16(); move16();
    pConcealmentInfo->cntConcealFrame[ch] = 0;                                                     move16();
    pConcealmentInfo->ConcealState[ch] = CConcealment_Uninitialized;                               move16();
  }
  
  pConcealmentInfo->iRandomPhase   = 0;                                                            move16();
  return pConcealmentInfo;
}


void CConcealment_Apply (CConcealmentInfo *pConcealmentInfo, /*!< Concealment handle */
                         Word32 *pSpectralCoefficient,       /*!< Poninter to spectral data */
                         Word16 *pSpecScale,                 /*!< Corresponding scaling factor(s) */
                         CIcsInfo *pIcsInfo,                 /*!< IndividualChannelStream
                                                               contains windowShape, BlockType,
                                                               pointer to samplingRateIndex */
                         Word16 ch,                          /*!< Current channel */
                         Flag frameOK                        /*!< Indicates if current frame is valid */
 )
{
  Word16 sfbEnergyPrev[MAXSFB];
  Word16 sfbEnergyAct[MAXSFB];
  Word16    tmp1;
  Word32   tmp2;
  Word16   tmp3;
  Word16      i;

  /* if the current frame is ok, save it (and swap out stored frame, i.e. the stored
     frame will be current output frame. For correct frames, this means that the
     previous frame will be played now. */

                                                                                                   test();
  if (frameOK) {
    tmp1 = pIcsInfo->WindowShape;                                                                  move16();
    pIcsInfo->WindowShape = pConcealmentInfo->WindowShape[ch];                                     move16();
    pConcealmentInfo->WindowShape[ch] = tmp1;                                                      move16();

    tmp1 = pIcsInfo->WindowSequence;                                                               move16();
    pIcsInfo->WindowSequence = pConcealmentInfo->WindowSequence[ch];                               move16();
    pConcealmentInfo->WindowSequence[ch] = tmp1;                                                   move16();

    for (i = 0; i < FRAME_SIZE; i++) {
      tmp2 = pSpectralCoefficient[i];                                                              move32();
      pSpectralCoefficient[i] = pConcealmentInfo->SpectralCoefficient[ch][i];                      move32();
      pConcealmentInfo->SpectralCoefficient[ch][i] = tmp2;                                         move32();
    }

    for (i = 0; i < MAX_WINDOWS; i++) {
      tmp3 = pSpecScale[i];                                                                        move16();
      pSpecScale[i] = pConcealmentInfo->SpecScale[ch][i];                                          move16();
      pConcealmentInfo->SpecScale[ch][i] = tmp3;                                                   move16();
    }
  } else {
    pIcsInfo->WindowShape = pConcealmentInfo->WindowShape[ch];                                     move16();
    pIcsInfo->WindowSequence = pConcealmentInfo->WindowSequence[ch];                               move16();

    for (i = 0; i < FRAME_SIZE; i++) {
      pSpectralCoefficient[i] = pConcealmentInfo->SpectralCoefficient[ch][i];                      move32();
    }

    for (i = 0; i < MAX_WINDOWS; i++) {
      pSpecScale[i] = pConcealmentInfo->SpecScale[ch][i];                                          move32();
    }
  }

  CConcealment_UpdateState(pConcealmentInfo, frameOK, ch);

  #define FRAMESIZE_DIV_MAXWINDOWS (Word16)(FRAME_SIZE / MAX_WINDOWS)

  /* if previous frame was not ok */                                                               test();
  if (!pConcealmentInfo->prevFrameOk[ch][1]) {

    /* if current frame (f_n) is ok and the last but one frame (f_(n-2))
       was ok, too, then interpolate both frames in order to generate 
       the current output frame (f_(n-1)). Otherwise, use the last stored 
       frame (f_(n-2) or f_(n-3) or ...). */                                                       test(); test();
    if (frameOK && pConcealmentInfo->prevFrameOk[ch][0]) {

                                                                                                   test();
      if (sub(pIcsInfo->WindowSequence,EightShortSequence) == 0) { /* f_(n-2) == EightShortSequence */
        /* short--??????--short, short--??????--long interpolation */
        /* short--short---short, short---long---long interpolation */
        Word16 wnd;
        
        tmp3 = sub( pConcealmentInfo->WindowSequence[ch],EightShortSequence );                     test();
        if ( tmp3 == 0 ) { /* f_n == EightShortSequence */

          Word16 scaleFactorBandsTotal = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].NumberOfScaleFactorBands_Short;
          const Word16 *pSfbOffset     = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].ScaleFactorBands_Short;                        
                                                                                                                                           move16();move16();


          pIcsInfo->WindowShape = 1;                                                                                                       move16();
          pIcsInfo->WindowSequence = EightShortSequence;                                                                                   move16();

          for (wnd = 0; wnd < MAX_WINDOWS; wnd++) {

            CConcealment_CalcBandEnergy(&pSpectralCoefficient[wnd * FRAMESIZE_DIV_MAXWINDOWS], /* spec_(n-2) */
                                        EightShortSequence,
                                        pIcsInfo->SamplingRateIndex,
                                        CConcealment_NoExpand,
                                        sfbEnergyPrev);

            CConcealment_CalcBandEnergy(&pConcealmentInfo->SpectralCoefficient[ch][wnd * (FRAMESIZE_DIV_MAXWINDOWS)], /* spec_n */
                                        EightShortSequence,
                                        pIcsInfo->SamplingRateIndex,
                                        CConcealment_NoExpand,
                                        sfbEnergyAct);

            CConcealment_InterpolateBuffer(&pSpectralCoefficient[wnd * (FRAMESIZE_DIV_MAXWINDOWS)], /* spec_(n-1) */
                                           &pSpecScale[wnd],
                                           &pConcealmentInfo->SpecScale[ch][wnd],
                                           &pSpecScale[wnd],
                                           sfbEnergyPrev,
                                           sfbEnergyAct,
                                           scaleFactorBandsTotal,
                                           pSfbOffset);
          }

        } else { /* f_n != EightShortSequence */

          Word16 scaleFactorBandsTotal = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].NumberOfScaleFactorBands_Long;                 
          const Word16 *pSfbOffset     = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].ScaleFactorBands_Long;                         
          Word16 specScaleOut;                                                                                                             move16();move16();

          CConcealment_CalcBandEnergy(&pSpectralCoefficient[FRAME_SIZE - FRAMESIZE_DIV_MAXWINDOWS], /* spec_(n-2) */
                                      EightShortSequence,
                                      pIcsInfo->SamplingRateIndex,
                                      CConcealment_Expand,
                                      sfbEnergyAct);

          CConcealment_CalcBandEnergy(pConcealmentInfo->SpectralCoefficient[ch], /* spec_n */
                                      OnlyLongSequence,
                                      pIcsInfo->SamplingRateIndex,
                                      CConcealment_NoExpand,
                                      sfbEnergyPrev);

          pIcsInfo->WindowShape = 0;                                                                                                       move16();
          pIcsInfo->WindowSequence = LongStopSequence;                                                                                     move16();         

          for (i = 0; i < FRAME_SIZE; i++) {
            pSpectralCoefficient[i] = pConcealmentInfo->SpectralCoefficient[ch][i]; /* spec_n */                                           move32();
          }

          for (i = 0; i < MAX_WINDOWS; i++) { /* search for max(SpecScale) */
            tmp3 = sub( pSpecScale[i],pSpecScale[0] );                                                                                     test();
            if ( tmp3 > 0 ) {
              pSpecScale[0] = pSpecScale[i];                                                                                               move16();
            }
          }

          CConcealment_InterpolateBuffer(pSpectralCoefficient, /* spec_(n-1) */
                                         &pConcealmentInfo->SpecScale[ch][0],
                                         &pSpecScale[0],
                                         &specScaleOut,
                                         sfbEnergyPrev,
                                         sfbEnergyAct,
                                         scaleFactorBandsTotal,
                                         pSfbOffset);

          pSpecScale[0] = specScaleOut;                                                                                                    move16();
        }
      }
      else {
        /* long--??????--short, long--??????--long interpolation */
        /* long---long---short, long---long---long interpolation */

        Word16 scaleFactorBandsTotal = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].NumberOfScaleFactorBands_Long;
        const Word16 *pSfbOffset     = SamplingRateInfoTable[pIcsInfo->SamplingRateIndex].ScaleFactorBands_Long;
        Word16 specScaleAct          = pConcealmentInfo->SpecScale[ch][0];                                                                 move16();move16();move16();

        CConcealment_CalcBandEnergy(pSpectralCoefficient,  /* spec_(n-2) */
                                    OnlyLongSequence,
                                    pIcsInfo->SamplingRateIndex,
                                    CConcealment_NoExpand,
                                    sfbEnergyPrev);

        tmp3 = sub( pConcealmentInfo->WindowSequence[ch],EightShortSequence );                                                             test();
        if( tmp3 == 0 ) {  /* f_n == EightShortSequence */


          pIcsInfo->WindowShape = 1;                                                                                                       move16();
          pIcsInfo->WindowSequence = LongStartSequence;                                                                                    move16();

          for (i = 1; i < MAX_WINDOWS; i++) { /* search for max(SpecScale) */
            tmp3 = sub ( pConcealmentInfo->SpecScale[ch][i], specScaleAct );                                                               test();
            if ( tmp3 > 0 ) {
              specScaleAct = pConcealmentInfo->SpecScale[ch][i];                                                                           move16();
            }
          }

          /* Expand first short spectrum */
          CConcealment_CalcBandEnergy(pConcealmentInfo->SpectralCoefficient[ch],  /* spec_n */
                                      EightShortSequence,
                                      pIcsInfo->SamplingRateIndex,
                                      CConcealment_Expand,
                                      sfbEnergyAct);
        }
        else {

          pIcsInfo->WindowShape = 0;                                                                                                       move16();
          pIcsInfo->WindowSequence = OnlyLongSequence;                                                                                     move16();

          CConcealment_CalcBandEnergy(pConcealmentInfo->SpectralCoefficient[ch],  /* spec_n */
                                      OnlyLongSequence,
                                      pIcsInfo->SamplingRateIndex,
                                      CConcealment_NoExpand,
                                      sfbEnergyAct);
        }

        CConcealment_InterpolateBuffer(pSpectralCoefficient,  /* spec_(n-1) */
                                       &pSpecScale[0],
                                       &specScaleAct,
                                       &pSpecScale[0],
                                       sfbEnergyPrev,
                                       sfbEnergyAct,
                                       scaleFactorBandsTotal,
                                       pSfbOffset);
      }
    }

    /* Noise substitution of sign of the output spectral coefficients */
    CConcealment_ApplyRandomSign (pConcealmentInfo,
                                  pSpectralCoefficient);
  }

  /* 
     update FrameOk flag
  */
  pConcealmentInfo->prevFrameOk[ch][0]  = pConcealmentInfo->prevFrameOk[ch][1];                                                            move16();
  pConcealmentInfo->prevFrameOk[ch][1]  = frameOK;                                                                                         move16();


  /* CConcealment_FadeOut */                                                                                                               logic16();test();
  if ( pConcealmentInfo->ConcealState[ch] & CConcealment_FadeOut ) { 
    for (i = 0; i < FRAME_SIZE; i++) {
      pSpectralCoefficient[i] = fixmul_32x16b(pSpectralCoefficient[i], fadeFacTable[pConcealmentInfo->cntConcealFrame[ch]]);               move32();
    }
  }
  /* CConcealment_FadeIn */
  else {                                                                                                                                   logic16();test();
    if ( pConcealmentInfo->ConcealState[ch] & CConcealment_FadeIn ) {
      for (i = 0; i < FRAME_SIZE; i++) {
        pSpectralCoefficient[i] = fixmul_32x16b(pSpectralCoefficient[i], fadeFacTable[sub(sub(N_FADE_IN_FRAMES, pConcealmentInfo->cntConcealFrame[ch]),1)]);    move32();
      }
    }
    /* CConcealment_Mute */
    else {                                                                                                                                 logic16();test();
      if ( pConcealmentInfo->ConcealState[ch] & CConcealment_Mute ) {
        for (i = 0; i < FRAME_SIZE; i++) {
          pSpectralCoefficient[i] = 0;                                                                                                     move32();
        }
                                                                                                                                           logic16();test();      }
    }
  }

  return;
}


/*!
  \brief Randomizes the sign of the spectral data

  The function toggles the sign of the spectral data randomly. This is 
  useful to ensure the quality of the concealed frames.

  \return  none
*/
static
void CConcealment_ApplyRandomSign (CConcealmentInfo *pConcealmentInfo,
                                   Word32 *spec)
{
  Word16 i;

  for(i = 0; i < FRAME_SIZE; i++) {                                                                                                        test();
    if( sbr_randomPhase[pConcealmentInfo->iRandomPhase] < 0 ) {
      spec[i] = L_negate(spec[i]);
    }
    pConcealmentInfo->iRandomPhase = L_add(pConcealmentInfo->iRandomPhase,1) & (AAC_NF_NO_RANDOM_VAL - 1);                                 logic32();move32();
  }
}

/*!
  \brief Calculate the spectral energy

  The function calculates band-wise the spectral energy. This is used for 
  frame interpolation.

  \return  none
*/
static
void CConcealment_CalcBandEnergy (Word32                  *spectrum,
                                  Word16                   blockType,
                                  Word32                   samplingRateIndex,
                                  CConcealmentExpandType   expandType,
                                  Word16                  *sfbEnergy)
{
  Word16 temp;
  Word16 line;
  Word16  sfb;
  const Word16 *pSfbOffset;
  Word16 scaleFactorBandsTotal = 0;
  Word32 enAccu = 0;

  /* In the following calculations, enAccu is initialized with LSB-value in order to avoid zero energy-level */

  move32(); /* init enAccu */
  move16(); /* init scaleFactorBandsTotal */

  line = 0;                                                                                                            move16();

  temp = sub( blockType, EightShortSequence );

  /* OnlyLongSequence, LongStartSequence, LongStopSequence */                                                          test();
  if ( temp != 0 ) {

    Word16 temp = sub( expandType, CConcealment_NoExpand );                                                            test();

    if( temp == 0 ) {
      /* standard long calculation */
      scaleFactorBandsTotal = SamplingRateInfoTable[samplingRateIndex].NumberOfScaleFactorBands_Long;                  move16();
      pSfbOffset = SamplingRateInfoTable[samplingRateIndex].ScaleFactorBands_Long;                                     move16();

      for (sfb = 0; sfb < scaleFactorBandsTotal; sfb++) {
        Word16 line_stop;
        enAccu = 1;                                                                                                    move32();

        line_stop = pSfbOffset[sfb+1]; move16();
        for( ; line < line_stop; line++) {
          Word16 tmp = extract_h(spectrum[line]);
          enAccu = L_add( enAccu, L_shr( L_mult(tmp, tmp) ,1));
        }
        sfbEnergy[sfb] = ffr_norm32(enAccu);                                                                                move16();
      }
    }
    else {
      /* compress long to short */
      scaleFactorBandsTotal = SamplingRateInfoTable[samplingRateIndex].NumberOfScaleFactorBands_Short;                 move16();
      pSfbOffset = SamplingRateInfoTable[samplingRateIndex].ScaleFactorBands_Short;                                    move16();

      for (sfb = 0; sfb < scaleFactorBandsTotal; sfb++) {
        Word16 line_stop;
        enAccu = 1;                                                                                                    move32();

        line_stop = shl(pSfbOffset[sfb+1],3);
        for(; line < line_stop; line++) {
          Word16 tmp;
          Word32 tmpAccu;
          tmp = extract_h(spectrum[line]);                                                                             move32();
          tmpAccu = L_add( enAccu, L_shr( L_mult(tmp, tmp) ,1));

          enAccu = L_add(enAccu, L_shr(tmpAccu, 3));
        }
        sfbEnergy[sfb] = ffr_norm32(enAccu);                                                                                move16();
      }
    }
  }
  /* EightShortSequence */
  else {

    Word16 temp = sub( expandType, CConcealment_NoExpand );                                                            test();
   
    if(temp == 0) {   
      /*   standard short calculation */
      scaleFactorBandsTotal = SamplingRateInfoTable[samplingRateIndex].NumberOfScaleFactorBands_Short;                 move16();
      pSfbOffset = SamplingRateInfoTable[samplingRateIndex].ScaleFactorBands_Short;                                    move16();

      for(sfb = 0; sfb < scaleFactorBandsTotal; sfb++) {
        Word16 line_stop;
        enAccu = 1;                                                                                                    move32();

        line_stop = pSfbOffset[sfb+1]; move16();
        for( ; line < line_stop; line++) {
          Word16 tmp = extract_h(spectrum[line]);
          enAccu = L_add( enAccu, L_shr( L_mult(tmp, tmp),1));
        }
        sfbEnergy[sfb] = ffr_norm32(enAccu);                                                                                move16();

      }
    }
    else {

      /*  expand short to long spectrum */
      scaleFactorBandsTotal = SamplingRateInfoTable[samplingRateIndex].NumberOfScaleFactorBands_Long;                  move16();
      pSfbOffset = SamplingRateInfoTable[samplingRateIndex].ScaleFactorBands_Long;                                     move16();

      for (sfb = 0; sfb < scaleFactorBandsTotal; sfb++) {
        Word16 line_stop;
        enAccu = 1;                                                                                                    move32();

        line_stop = pSfbOffset[sfb+1]; move16();
        for ( ; line < line_stop; line++) {
          Word16 tmp = extract_h(spectrum[shr(line, 3)]);
          enAccu = L_add( enAccu, L_shr( L_mult(tmp, tmp) ,1));
        } 
        sfbEnergy[sfb] = ffr_norm32(enAccu);                                                                                move16();
      }
    }
  }

}

/*!
  \brief Interpolate buffer

  The function creates the interpolated spectral data according to the 
  energy of the last good frame and the current (good) frame.

  \return  none
*/
static
void CConcealment_InterpolateBuffer (Word32       *spectrum,
                                     Word16       *pSpecScalePrev,
                                     Word16       *pSpecScaleAct,
                                     Word16       *pSpecScaleOut,
                                     Word16       *enPrev,
                                     Word16       *enAct,
                                     Word16        sfbCnt,
                                     const Word16 *pSfbOffset)
{
  Word16 sfb, line;
  Word16 fac_shift;
  Word16 fac_mod;
  Word32 accu;
  
  line = 0;                                                                                                            move16();

  for(sfb = 0; sfb < sfbCnt; sfb++) {

    fac_shift = add(sub(enPrev[sfb],enAct[sfb]),(shl(sub(*pSpecScaleAct,*pSpecScalePrev),1)));
    fac_mod   = fac_shift & 3;                                                                                         logic16();
    fac_shift = add(shr(fac_shift,2),1);
    fac_shift = add( fac_shift, sub( *pSpecScalePrev, S_max(*pSpecScalePrev, *pSpecScaleAct)));

    for(; line < pSfbOffset[sfb+1]; line++) {
      accu = fixmuldiv2_32x16b(spectrum[line], facMod4Table[fac_mod]);
      spectrum[line] = L_shl(accu, add(fac_shift,1));                                                                  move32();

    }
  }

  *pSpecScaleOut = S_max(*pSpecScalePrev, *pSpecScaleAct);                                                             move16();
}

/*!
  \brief Update the concealment state

  The function updates the state of the concealment state-machine. The 
  states are: mute, fade-in, fade-out, and frame-ok.

  \return  none
*/
static
void CConcealment_UpdateState(CConcealmentInfo *pConcealmentInfo,
                              Flag FrameOk,
                              Word16  ch
                              )
{

  /* CConcealment_Ok */                                                                                                test();
  /* CConcealment_Ok is 0x0000, therefore, no need to instrument */
  if ( pConcealmentInfo->ConcealState[ch] == CConcealment_Ok ) {
                                                                                                                           test(); test(); test(); test(); 
    if(!(pConcealmentInfo->prevFrameOk[ch][1] ||
         (pConcealmentInfo->prevFrameOk[ch][0] &&
          !pConcealmentInfo->prevFrameOk[ch][1] &&
          FrameOk))) {

      pConcealmentInfo->ConcealState[ch] = CConcealment_FadeOut;                                                       move16();
    }
  }
  else {
    /* CConcealment_Uninitialized */                                                                                   test();
    if ( pConcealmentInfo->ConcealState[ch] < 0 ) {                                                                    test();
      if (pConcealmentInfo->prevFrameOk[ch][1])
        pConcealmentInfo->ConcealState[ch]    = CConcealment_Ok;                                                       move16();
    }
    else {
      /* CConcealment_FadeIn */                                                                                        logic16();test();
      if ( pConcealmentInfo->ConcealState[ch] & CConcealment_FadeIn ) {
                                                                                                                       test(); test(); test(); test();
        if(pConcealmentInfo->prevFrameOk[ch][1] ||
           (pConcealmentInfo->prevFrameOk[ch][0] &&
            !pConcealmentInfo->prevFrameOk[ch][1] &&
            FrameOk)) {

          Word16 temp;

          add(pConcealmentInfo->cntConcealFrame[ch], 1); move16();
          pConcealmentInfo->cntConcealFrame[ch]++;

          temp = sub( pConcealmentInfo->cntConcealFrame[ch], N_FADE_IN_FRAMES );
          if( temp == 0 ) {
            pConcealmentInfo->cntConcealFrame[ch] = 0;                                                                 move16();
            pConcealmentInfo->ConcealState[ch]    = CConcealment_Ok;                                                   move16();
          }
        }
        else{
          pConcealmentInfo->cntConcealFrame[ch]  = 0;                                                                  move16();
          pConcealmentInfo->ConcealState[ch]     = CConcealment_FadeOut;                                               move16();
        }
      }
      else {                               
        /* CConcealment_FadeOut */                                                                                     logic16();test();
        if ( pConcealmentInfo->ConcealState[ch] & CConcealment_FadeOut ) {                                             test();
          if(pConcealmentInfo->prevFrameOk[ch][1]) {                                                                          

            pConcealmentInfo->cntConcealFrame[ch] = 0;                                                                 move16();
            pConcealmentInfo->ConcealState[ch]    = CConcealment_Ok;                                                   move16();
          }
          else{

            Word16 temp;

            add(pConcealmentInfo->cntConcealFrame[ch], 1); move16();
            pConcealmentInfo->cntConcealFrame[ch]++;

            temp = sub( pConcealmentInfo->cntConcealFrame[ch], N_FADE_OUT_FRAMES );
                                                                                                                       test();
            if( temp == 0 ) {
              pConcealmentInfo->cntConcealFrame[ch] = 0;                                                               move16();
              pConcealmentInfo->ConcealState[ch]    = CConcealment_Mute;                                               move16();
            }
          }
        }
        /* CConcealment_Mute */
        else {                                                                                                         test();
          if(pConcealmentInfo->prevFrameOk[ch][1]) {

            Word16 temp;

            add(pConcealmentInfo->cntConcealFrame[ch], 1); move16();
            pConcealmentInfo->cntConcealFrame[ch]++;

            temp = sub( pConcealmentInfo->cntConcealFrame[ch], N_VALID_FRAMES );
                                                                                                                       test();
            if ( temp > 0 ){
              pConcealmentInfo->cntConcealFrame[ch] = 0;                                                               move16();
              pConcealmentInfo->ConcealState[ch]    = CConcealment_FadeIn;                                             move16();
            }
          }
          else{
            pConcealmentInfo->cntConcealFrame[ch]  = 0;                                                                move16();
          }
        }
      }
    }
  }
}
