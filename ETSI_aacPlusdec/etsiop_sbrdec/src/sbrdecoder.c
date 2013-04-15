/*
   SBR decoder frontend
 */

#include <string.h>
#include <assert.h>
#include "sbr_const.h"
#include "sbrdecoder.h"
#include "FFR_bitbuffer.h"
#include "freq_sca.h"
#include "env_extr.h"
#include "sbr_dec.h"
#include "env_dec.h"
#include "sbr_ram.h"
#include "sbr_rom.h"
#include "ffr.h"
#ifndef MONO_ONLY
#include "ps_bitdec.h"
#include "ps_dec.h"
#endif
#include "sbr_crc.h"
#include "count.h"

struct SBR_DECODER_INSTANCE
{
  SBR_CHANNEL      SbrChannel[MAXNRSBRCHANNELS];
  SBR_HEADER_DATA  sbr_header;
#ifndef MONO_ONLY
  PS_DEC           ParametricStereoDec;
#endif
} sbrDecoderInstance;


static void
map2channelSbrData2one(HANDLE_SBR_FRAME_DATA hFrameDataLeft,
                       HANDLE_SBR_FRAME_DATA hFrameDataRight,
                       HANDLE_SBR_HEADER_DATA hHeaderData);

/*!
  \brief     Set up SBR decoder phase 1

  \return    Handle
*/
SBRDECODER openSBR (Word32 sampleRate, Word16 samplesPerFrame, Flag bDownSample, Flag bApplyQmfLp)
{
  Word16 i;
  Word16 err;
  SBR_CHANNEL *SbrChannel;
  HANDLE_SBR_HEADER_DATA hHeaderData;

  SbrChannel  = &sbrDecoderInstance.SbrChannel[0];                                                  move16();
  hHeaderData = &sbrDecoderInstance.sbr_header;                                                     move16();


  /* init a default header such that we can at least do upsampling later */
  initHeaderData( hHeaderData,
                  sampleRate,
                  samplesPerFrame);

  for (i = 0; i < MAXNRSBRCHANNELS; i++) {

    err = createSbrDec (&(SbrChannel[i]),
                        hHeaderData,
                        i,
                        bDownSample,
                        bApplyQmfLp,
                        sampleRate );
                                                                                                    test();
    if (err) {
      return NULL;
    }
  }

  memset(sbr_OverlapBuffer, 0, sizeof(sbr_OverlapBuffer));                                          memop32(sizeof(sbr_OverlapBuffer)/sizeof(Word32));

#ifndef MONO_ONLY
  err = CreatePsDec(&sbrDecoderInstance.ParametricStereoDec);
                                                                                                    test();
  if ( err) {
    return NULL;
  }
#endif

  return &sbrDecoderInstance;
}


/*!
  \brief   Prepare filterbank for upsampling
  \return  0 if everything is fine
*/
static
Word16 prepareUpsampling(HANDLE_SBR_HEADER_DATA hHeaderData,
                         SBR_CHANNEL *SbrChannel,
                         Flag bUseLP)
{
  Word16 err, lr;

  /*
    Use default header
  */
  initHeaderData( hHeaderData,
                  L_shr(hHeaderData->outSampleRate, 1),
                  1024);

  err = resetFreqBandTables(hHeaderData);

  /* As the default header would limit the frequency range,
     lowSubband and highSubband must be patched. */
  hHeaderData->hFreqBandData->lowSubband  = NO_ANALYSIS_CHANNELS;                                   move16();
  hHeaderData->hFreqBandData->highSubband = NO_SYNTHESIS_CHANNELS;                                  move16();

  for (lr = 0 ; lr < 2; lr++) {
    /*
      Always reset both channels, because a HEADER_RESET is not necessarily
      triggered when switching from MONO to STEREO.
    */
    err |= resetSbrDec (&(SbrChannel[lr].SbrDec),
                        hHeaderData,
                        bUseLP);                                                                    logic16();
  }
  hHeaderData->syncState = UPSAMPLING;                                                              move16();

  return err;
}


/*!
  \brief     SBR decoder processing

  \return SBRDEC_OK if successful, else error code */
Word16
applySBR (SBRDECODER self,
          SBRBITSTREAM * Bitstr,    /*!< Pointer to payload data */
          Word16 *timeData,         /*!< Input and finally upsampled output data */
          Word16 *numChannels,      /*!< 1: mono,  2: stereo */
          Flag   SbrFrameOK,        /*!< Flag from core decoder to indicate good frames */
          Flag   bDownSample,       /*!< Flag, apply downsampling in QMF synthesis ? */
          Flag   bBitstreamDownMix  /*!< Flag, apply SBR stereo to mono bitstream downmix ? */
          )
{
  Word16 lr;
  Word16 i;
  Flag   prevStereo, prevPs=0;
  Flag   psPresent;              /* may be cleared later */
  Flag   stereo=0;
  Flag   readHeader;
  Word16 err;

  SBR_CHANNEL *SbrChannel;
  struct BIT_BUF bitBuf;
  HANDLE_SBR_HEADER_DATA hHeaderData;
  SBR_HEADER_STATUS headerStatus;
  Word16 codecFrameSize;
  SBR_SYNC_STATE initialSyncState;

  SBR_FRAME_DATA *hFrameDataLeft;
  SBR_FRAME_DATA *hFrameDataRight;
  Flag bUseLP = 1;                                                                                  move16();

  psPresent    = 1;                                                                                 move16();
  err          = 0;                                                                                 move16();

  SbrChannel       = &self->SbrChannel[0];                                                          move16();
  hHeaderData      = &self->sbr_header;                                                             move16();
  headerStatus     = HEADER_NOT_INITIALIZED;                                                        move16();
  codecFrameSize   = hHeaderData->codecFrameSize;                                                   move16();
  initialSyncState = hHeaderData->syncState;                                                        move16();

  hFrameDataLeft   = (SBR_FRAME_DATA*) &timeData[MAX_FRAME_SIZE];                                   move16();
  hFrameDataRight  = (SBR_FRAME_DATA*) &timeData[3*MAX_FRAME_SIZE];                                 move16();

  test();
  if(sub(*numChannels,1) == 0) {
    bUseLP = 0;                                                                                     move16();
  }

#if (defined LP_SBR_ONLY || defined MONO_ONLY)
  bUseLP = 1;                                                                                       move16();
#endif

  assert( sizeof(SBR_FRAME_DATA) <= MAX_FRAME_SIZE*sizeof(Word16));

  prevStereo = (hHeaderData->channelMode == STEREO);                                                test();
#ifndef MONO_ONLY
  prevPs = (hHeaderData->channelMode == PS_STEREO);                                                 test();
#endif

  /* Save last error flag */
  hHeaderData->prevFrameErrorFlag = hHeaderData->frameErrorFlag;                                    move16();

                                                                                                    test();
  if (Bitstr->nrElements == 0) {
    SbrFrameOK = 0;                                                                                 move16();
  }

  move16(); /* Bitstr->nrElements */
  for (i=0; i<Bitstr->nrElements; i++)
  {

    /* Check channel configuration */
    switch (Bitstr->sbrElement[i].elementID) {
    case SBR_ID_SCE:
                                                                                                    test();
      stereo = 0;                                                                                   move16();
      break;
    case SBR_ID_CPE:
      test();test();
      stereo = 1;                                                                                   move16();
      break;
    default:
      test();test();
      SbrFrameOK = 0;                                                                               move16();
    }

                                                                                                    test();
    if (SbrFrameOK) {
      /*
        Read SBR-Bitstream
      */
      CreateInitializedBitBuffer(&bitBuf,
                                 (UWord8 *)Bitstr->sbrElement[i].pData,
                                 Bitstr->sbrElement[i].sizePayload);

      /* Skip first nibble; it does not contain data */
      ReadBits (&bitBuf, LEN_NIBBLE);


      {
        Word16 CRCLen;
        Word8  crcEnable;

        CRCLen    = 0;                                                                              move16();
        crcEnable = 0;                                                                              move16();

        /*
          Get enable flag and length of CRC
        */
                                                                                                    test();
        if (sub(Bitstr->sbrElement[i].extensionType,SBR_EXTENSION_CRC) == 0) {       /* change: 0 => i */
          crcEnable = 1;                                                                            move16();
          CRCLen = extract_l(L_add(L_shl(L_sub(Bitstr->sbrElement[i].sizePayload, 1), 3),
                             (+4 - SI_SBR_CRC_BITS)));                     /* change: 0 => i */

                                                                                                    test();
          if (CRCLen < 0) {
            crcEnable  = 0;                                                                         move16();
            SbrFrameOK = 0;                                                                         move16();
          }
        }

        /*
          Now do the CRC-check
        */
                                                                                                    test();
        if (crcEnable)
          SbrFrameOK = SbrCrcCheck (&bitBuf, CRCLen);
      }

      /* read the header_flag  */
      readHeader = (Word8)ReadBits (&bitBuf, 1);


      /*
        Read in the header data and issue a reset if change occured
      */
                                                                                                    test();
      if (readHeader) {

        headerStatus = sbrGetHeaderData (hHeaderData,
                                         &bitBuf,
                                         stereo);

        /* Avoid SBR if CRC was O.K. by chance */
                                                                                                    test();
        if (sub(headerStatus,HEADER_NOT_INITIALIZED) == 0) {
          hHeaderData->syncState = SBR_NOT_INITIALIZED;                                             move16();
        }

                                                                                                    test();
        if (sub(headerStatus,HEADER_RESET) == 0) {
          /*
            change of control data, reset decoder
          */
          err = resetFreqBandTables(hHeaderData);

                                                                                                    test();
          if (!err) {
            for (lr = 0 ; lr < 2; lr++) {
              /*
                Always reset both channels, because a HEADER_RESET is not necessarily
                triggered when switching from MONO to STEREO.
              */
              err |= resetSbrDec (&(SbrChannel[lr].SbrDec),
                                  hHeaderData,
                                  bUseLP);                                                          logic16();
            }
          }
                                                                                                    test();
          if (err==0) {
            hHeaderData->syncState = SBR_ACTIVE;                                                    move16();
          }
        }
      }
    }

 
    /*
      Fallback: Perform upsampling if the header reset failed
    */
                                                                                                    test(); test();
    if (err || sub(hHeaderData->syncState,SBR_NOT_INITIALIZED) == 0) {
      prepareUpsampling(hHeaderData,
                        SbrChannel,
                        bUseLP);
    }



                                                                                                    test(); test();
    if (SbrFrameOK && sub(hHeaderData->syncState,SBR_ACTIVE) == 0) {

      /* now get the rest */

                                                                                                    test();
      if (stereo) {
        SbrFrameOK = sbrGetChannelPairElement(hHeaderData,
                                              hFrameDataLeft,
                                              hFrameDataRight,
                                              &bitBuf);
      }
      else {
         
#ifndef MONO_ONLY                     
        test(); move16();
        if (bBitstreamDownMix)  {
          sbrDecoderInstance.ParametricStereoDec.bForceMono = 1;
        }
        else {
          sbrDecoderInstance.ParametricStereoDec.bForceMono = 0;
        }
#endif

                                                                test(); move16();
        SbrFrameOK = sbrGetSingleChannelElement(hHeaderData,
                                                (i==0) ? hFrameDataLeft : hFrameDataRight,
#ifndef MONO_ONLY
                                                &sbrDecoderInstance.ParametricStereoDec,
#endif                                                        
                                                &bitBuf);
      }


      {
        /* consistency check */
        Word32 payloadbits;
        Word32 fillbits;

        payloadbits = GetNrBitsRead (&bitBuf);
        fillbits    = L_sub(8, (payloadbits & 7)) & 7;                                              logic16(); logic16();

                                                                                                    test();
        if (L_sub(L_add(payloadbits, fillbits),L_shl(Bitstr->sbrElement[i].sizePayload, 3)) != 0) {
          SbrFrameOK = 0;                                                                           move16();
        }
      }



    }
  }


                                                                                                    test(); test(); test();
  if (!SbrFrameOK || sub(hHeaderData->syncState,SBR_ACTIVE) != 0 || hHeaderData->frameErrorFlag) {
    hHeaderData->frameErrorFlag    = 1;                                                             move16();

    /* Upsampling and SBR-concealment shall preserve the number of channels */
    stereo = ( *numChannels == 2) ? 1 : 0 ;                                                         test(); move16();
    if (sub(hHeaderData->channelMode, UNDEFINED_CHANNEL_MODE) == 0) {                               test();
      hHeaderData->channelMode = stereo ? STEREO : MONO;                                            test(); move16();
    }
  }
                                                                                                    test();
  if (!stereo) {
    /* Turn coupling off explicitely to avoid access to absent right frame data later */
    hFrameDataLeft->coupling = COUPLING_OFF;                                                        move16();
  }


  /*
    SBR not initialized => Continue with upsampling
  */
                                                                                                    test();
  if ( sub(hHeaderData->syncState,SBR_NOT_INITIALIZED) == 0) {
    prepareUpsampling(hHeaderData, SbrChannel, bUseLP);
  }


  /* decoding */

                                                                                                    test();
  if (sub(hHeaderData->syncState,SBR_ACTIVE) == 0) {
                                                                                                    test();
    if (!prevStereo) {
      /* Duplicate grid and energy levels for previous frame */
      memcpy(SbrChannel[1].hPrevFrameData,
             SbrChannel[0].hPrevFrameData,
             sizeof(SBR_PREV_FRAME_DATA));                                                          memop16(sizeof(SBR_PREV_FRAME_DATA)/sizeof(Word16));
      SbrChannel[1].hPrevFrameData->coupling = COUPLING_BAL;                                        move16();
    }

    decodeSbrData (hHeaderData,
                   hFrameDataLeft,
                   SbrChannel[0].hPrevFrameData,
                   (stereo) ? hFrameDataRight : NULL,
                   (stereo) ? SbrChannel[1].hPrevFrameData : NULL);                                 test(); move16(); test(); move16();

#ifndef MONO_ONLY
                                                                                                    test();
    if(sub(hHeaderData->channelMode,PS_STEREO) == 0) {
      DecodePs(&sbrDecoderInstance.ParametricStereoDec);
    }
    else {
      psPresent = 0;                                                                             move16();
    }
#endif


    /* Assume the AAC frequency range ends where SBR starts */
    hFrameDataLeft->maxQmfSubbandAac  = hHeaderData->hFreqBandData->lowSubband;                     move16();
    hFrameDataRight->maxQmfSubbandAac = hHeaderData->hFreqBandData->lowSubband;                     move16();


  }

  /* One more plausibility check before activating SBR */
                                                                                                    test(); test();
  if ( sub(initialSyncState,SBR_NOT_INITIALIZED) == 0 && hHeaderData->frameErrorFlag ) {
    hHeaderData->syncState = SBR_NOT_INITIALIZED;                                                   move16();
  }

                                                                                                    test(); test();
  if(sub(hHeaderData->syncState,SBR_ACTIVE) == 0 && bBitstreamDownMix){

    SbrChannel[0].hPrevFrameData->stopPos = hFrameDataLeft->frameInfo.borders[hFrameDataLeft->frameInfo.nEnvelopes]; move16();

                                                                                                    test();
    if(stereo)  {
      SbrChannel[1].hPrevFrameData->stopPos = hFrameDataRight->frameInfo.borders[hFrameDataRight->frameInfo.nEnvelopes]; move16();
    }
  }

                                                                                                    test(); test();
  if (sub(*numChannels,2) == 0 && !stereo) {
    /* AAC generated a Stereo output, but the SBR side channel is not yet valid
       => Downmix AAC to Mono and apply Mono-SBR. */
    for (i=0; i<MAX_FRAME_SIZE; i++ ) {
      timeData[i] = add(shr(timeData[i], 1), shr(timeData[2*MAX_FRAME_SIZE+i], 1));                 move16();
    }
  }

  test(); test();
  if(stereo && bBitstreamDownMix){
    /* AAC generated a Stereo output, a stereo SBR bitstreams is present but the output
       shall be mono
       => Downmix AAC to Mono and apply SBR bitstream downmix */

    test();
    if(sub(hHeaderData->syncState,SBR_ACTIVE) == 0){
      map2channelSbrData2one(hFrameDataLeft,hFrameDataRight,hHeaderData);
    }

    for(i = 0; i<MAX_FRAME_SIZE; i++){
      timeData[i] = add(shr(timeData[i], 1), shr(timeData[2*MAX_FRAME_SIZE+i], 1));                 move16();
    }

  }



  /*
    Prevent drop outs and discontinuities when switching
    between mono and stereo (see also in aacdecoder.c)
    3 cases follow:
  */
                                                                                                    test(); test(); test(); test();
  if ( (!prevStereo && !prevPs) &&  /* switch from mono */
       (stereo || psPresent) ) {    /* to stereo or parametric stereo */
    /*
      (1) mono -> stereo or PS
      Duplicate synthesis filter states because there was no right
      channel in the previous frame.
    */
    memcpy(SbrChannel[1].SbrDec.SynthesisQmfBank.FilterStates,
           SbrChannel[0].SbrDec.SynthesisQmfBank.FilterStates,
           QMF_FILTER_STATE_SYN_SIZE * sizeof(Word16));                                             memop16(QMF_FILTER_STATE_SYN_SIZE);

    SbrChannel[1].SbrDec.sbrScaleFactor.st_syn_scale =
      SbrChannel[0].SbrDec.sbrScaleFactor.st_syn_scale;                                             move16();
  }


                                                                                                    test(); test();
  if (!prevStereo && stereo)
  {
    /* (2) mono -> stereo */

    /* Duplicate analysis filter states */
    memcpy(SbrChannel[1].SbrDec.CodecQmfBank.FilterStatesAna,
           SbrChannel[0].SbrDec.CodecQmfBank.FilterStatesAna,
           QMF_FILTER_STATE_ANA_SIZE * sizeof(Word16));                                             memop16(QMF_FILTER_STATE_ANA_SIZE);

    SbrChannel[1].SbrDec.sbrScaleFactor.st_lb_scale =
      SbrChannel[0].SbrDec.sbrScaleFactor.st_lb_scale;                                              move16();

    /* Duplicate overlap buffer */
#ifdef LP_SBR_ONLY
    memcpy(SbrChannel[1].SbrDec.ptrsbr_OverlapBuffer,
           SbrChannel[0].SbrDec.ptrsbr_OverlapBuffer,
           MAX_OV_COLS * NO_SYNTHESIS_CHANNELS * sizeof(Word32));                                   memop32(MAX_OV_COLS * NO_SYNTHESIS_CHANNELS);
#else
    memcpy(SbrChannel[1].SbrDec.ptrsbr_OverlapBuffer,
           SbrChannel[0].SbrDec.ptrsbr_OverlapBuffer,
           2 * MAX_OV_COLS * NO_SYNTHESIS_CHANNELS * sizeof(Word32));                               memop32(2 * MAX_OV_COLS * NO_SYNTHESIS_CHANNELS);
#endif

    SbrChannel[1].SbrDec.sbrScaleFactor.ov_lb_scale =
      SbrChannel[0].SbrDec.sbrScaleFactor.ov_lb_scale;                                              move16();
    SbrChannel[1].SbrDec.sbrScaleFactor.ov_hb_scale =
      SbrChannel[0].SbrDec.sbrScaleFactor.ov_hb_scale;                                              move16();
  }

                                                                                                    test(); test();
  if (prevStereo && !stereo) {
    /* (3) Downmix  Stereo -> Mono */

    Word16 commonScale, lbShiftL, lbShiftR, hbShiftL, hbShiftR;
    Word16 k, slot;

    Word16 slot_cnt_1;
#ifndef LP_SBR_ONLY
    Word16 slot_cnt_2;
#endif

    /*
      Merge analysis filter states
    */
    
    commonScale = S_min(SbrChannel[0].SbrDec.sbrScaleFactor.st_lb_scale,
                        SbrChannel[1].SbrDec.sbrScaleFactor.st_lb_scale);
    lbShiftL = sub(add(1 /* divide L+R by 2 */, SbrChannel[0].SbrDec.sbrScaleFactor.st_lb_scale),
                   commonScale);
    lbShiftR = sub(add(1 /* divide L+R by 2 */, SbrChannel[1].SbrDec.sbrScaleFactor.st_lb_scale),
                   commonScale);
    SbrChannel[0].SbrDec.sbrScaleFactor.st_lb_scale = commonScale;                                  move16();

    for (k=0; k<QMF_FILTER_STATE_ANA_SIZE; k++) {
      SbrChannel[0].SbrDec.CodecQmfBank.FilterStatesAna[k] =
        add(shr(SbrChannel[0].SbrDec.CodecQmfBank.FilterStatesAna[k], lbShiftL),
            shr(SbrChannel[1].SbrDec.CodecQmfBank.FilterStatesAna[k], lbShiftR));                   move16();
    }

    /*
      Merge synthesis filter states
    */
    commonScale = S_min(SbrChannel[0].SbrDec.sbrScaleFactor.st_syn_scale,
                        SbrChannel[1].SbrDec.sbrScaleFactor.st_syn_scale);
    lbShiftL = sub(add(1 /* divide L+R by 2 */, SbrChannel[0].SbrDec.sbrScaleFactor.st_syn_scale),
                   commonScale);
    lbShiftR = sub(add(1 /* divide L+R by 2 */, SbrChannel[1].SbrDec.sbrScaleFactor.st_syn_scale),
                   commonScale);
    SbrChannel[0].SbrDec.sbrScaleFactor.st_syn_scale = commonScale;                                 move16();

    for (k=0; k<QMF_FILTER_STATE_SYN_SIZE; k++) {
      SbrChannel[0].SbrDec.SynthesisQmfBank.FilterStates[k] =
        add(shr(SbrChannel[0].SbrDec.SynthesisQmfBank.FilterStates[k], lbShiftL),
            shr(SbrChannel[1].SbrDec.SynthesisQmfBank.FilterStates[k], lbShiftR));                  move16();
    }

    /*
      Merge overlap buffer
    */
    /* Determine shift values for lowband */
    commonScale = S_min(SbrChannel[0].SbrDec.sbrScaleFactor.ov_lb_scale,
                        SbrChannel[1].SbrDec.sbrScaleFactor.ov_lb_scale);
    lbShiftL = sub(add(1 /* divide L+R by 2 */, SbrChannel[0].SbrDec.sbrScaleFactor.ov_lb_scale),
                   commonScale);
    lbShiftR = sub(add(1 /* divide L+R by 2 */, SbrChannel[1].SbrDec.sbrScaleFactor.ov_lb_scale),
                   commonScale);
    SbrChannel[0].SbrDec.sbrScaleFactor.ov_lb_scale = commonScale;                                  move16();

    /* Determine shift values for highband */
    commonScale = S_min(SbrChannel[0].SbrDec.sbrScaleFactor.ov_hb_scale,
                        SbrChannel[1].SbrDec.sbrScaleFactor.ov_hb_scale);
    hbShiftL = sub(add(1 /* divide L+R by 2 */, SbrChannel[0].SbrDec.sbrScaleFactor.ov_hb_scale),
                   commonScale);
    hbShiftR = sub(add(1 /* divide L+R by 2 */, SbrChannel[1].SbrDec.sbrScaleFactor.ov_hb_scale),
                   commonScale);
    SbrChannel[0].SbrDec.sbrScaleFactor.ov_hb_scale = commonScale;                                  move16();

    slot_cnt_1=0; move16(); /* init counter slot*NO_SYNTHESIS_CHANNELS */
#ifndef LP_SBR_ONLY
    slot_cnt_2=0; move16(); /* init counter slot*(2*NO_SYNTHESIS_CHANNELS) */
#endif
    for (slot=0; slot<MAX_OV_COLS; slot++) { 
      Word32 *ptrRealL, *ptrRealR;
#ifndef LP_SBR_ONLY
      Word32 **ptrImagL, *ptrImagR;
#endif
                                                                                                    test();
      if (bUseLP) {
        ptrRealL = &(SbrChannel[0].SbrDec.ptrsbr_OverlapBuffer[slot_cnt_1]);        move16();
        ptrRealR = &(SbrChannel[0].SbrDec.ptrsbr_OverlapBuffer[slot_cnt_1]);        move16();
      }
#ifndef LP_SBR_ONLY
      else {
        ptrRealL = &(SbrChannel[0].SbrDec.ptrsbr_OverlapBuffer[slot_cnt_2]);    move16();
        ptrImagL = &ptrRealL[NO_SYNTHESIS_CHANNELS];                                                move16();
        ptrRealR = &(SbrChannel[1].SbrDec.ptrsbr_OverlapBuffer[slot_cnt_2]);    move16();
        ptrImagR = &ptrRealR[NO_SYNTHESIS_CHANNELS];                                                move16();
      }
#endif

      /* Shift lowband subsamples */
      move16(); /* SbrChannel[0].hPrevFrameData->maxQmfSubbandAac */
      for (k=0; k<SbrChannel[0].hPrevFrameData->maxQmfSubbandAac; k++) {
        ptrRealL[k] = L_add(L_shr(ptrRealL[k], lbShiftL), L_shr(ptrRealR[k], lbShiftR));            move32();
#ifndef LP_SBR_ONLY
                                                                                                    test();
        if (!bUseLP) {
          ptrImagL[k] = L_add(L_shr(ptrImagL[k], lbShiftL), L_shr(ptrImagR[k], lbShiftR));          move32();
        }
#endif
      }
      /* Shift highband subsamples before first envelope start position */
      /* if (slot < sub(hHeaderData->timeStep * SbrChannel[0].hPrevFrameData->stopPos, SBR_TIME_SLOTS)) */
      test();
      if (add(slot,shr(extract_l(L_msu(SBR_TIME_SLOTS<<1, hHeaderData->timeStep, SbrChannel[0].hPrevFrameData->stopPos)),1)) < 0) {
        for (k=SbrChannel[0].hPrevFrameData->maxQmfSubbandAac; k<NO_SYNTHESIS_CHANNELS; k++) {
          ptrRealL[k] = L_add(L_shr(ptrRealL[k], hbShiftL), L_shr(ptrRealR[k], hbShiftR));          move32();
#ifndef LP_SBR_ONLY
                                                                                                    test();
          if (!bUseLP) {
            ptrImagL[k] = L_add(L_shr(ptrImagL[k], hbShiftL), L_shr(ptrImagR[k], hbShiftR));        move32();
          }
#endif
        }
      }
      slot_cnt_1 += NO_SYNTHESIS_CHANNELS;
#ifndef LP_SBR_ONLY
      slot_cnt_2 += 2*NO_SYNTHESIS_CHANNELS;
#endif
    }

    /* Clear overlap buffer of right channel because it is used
       as the delay line of parametric stereo */
                   
#ifdef LP_SBR_ONLY
    memset(SbrChannel[1].SbrDec.ptrsbr_OverlapBuffer, 0,
           MAX_OV_COLS * NO_SYNTHESIS_CHANNELS * sizeof(Word32));                                   memop32(MAX_OV_COLS * NO_SYNTHESIS_CHANNELS);
#else
    memset(SbrChannel[1].SbrDec.ptrsbr_OverlapBuffer, 0,
           2 * MAX_OV_COLS * NO_SYNTHESIS_CHANNELS * sizeof(Word32));                               memop32(2 * MAX_OV_COLS * NO_SYNTHESIS_CHANNELS);
#endif
  }


  /* Process left channel */
  logic16();
  sbr_dec (&SbrChannel[0].SbrDec,
           timeData,
           hHeaderData,
           hFrameDataLeft,
           SbrChannel[0].hPrevFrameData,
#ifndef MONO_ONLY
           &sbrDecoderInstance.ParametricStereoDec,
           &SbrChannel[1].SbrDec.SynthesisQmfBank,
           &SbrChannel[1].SbrDec.sbrScaleFactor,
#endif
           hHeaderData->syncState == SBR_ACTIVE,
           bUseLP);

                                                                                                    test(); test();
  if (!bBitstreamDownMix &&stereo) {
    /* Process right channel */
                                                                                                    test();
    sbr_dec (&SbrChannel[1].SbrDec,
             &timeData[shl(codecFrameSize,1)],
             hHeaderData,
             hFrameDataRight,
             SbrChannel[1].hPrevFrameData,
#ifndef MONO_ONLY
             NULL,
             NULL,
             NULL,
#endif
             hHeaderData->syncState == SBR_ACTIVE,
             bUseLP);

  }
  else {
#ifndef MONO_ONLY
                                                                                                    test();
    if(sub(hHeaderData->channelMode,PS_STEREO) == 0) {
      *numChannels = 2;                                                                             move16();
    }
    else
#endif
    {
    /* Mono: Copy left channal data into right channel */
      memcpy(&timeData[shl(codecFrameSize,1)], timeData, 2*codecFrameSize*sizeof(Word16) );               memop16(2*codecFrameSize);
    }
  }

    return SBRDEC_OK;
}



/*!
  \brief     SBR bitstream data conversion from stereo to mono.

 \return none.
*/
static void
map2channelSbrData2one(HANDLE_SBR_FRAME_DATA hFrameDataLeft,
                       HANDLE_SBR_FRAME_DATA hFrameDataRight,
                       HANDLE_SBR_HEADER_DATA hHeaderData)
{
  Word16 band, env, envLeft, envRight, offset, offsetLeft,offsetRight, nScaleFactors;
  Word16 i;

  HANDLE_FREQ_BAND_DATA hFreq  = hHeaderData->hFreqBandData;
  FRAME_INFO *frameInfoLeft    = &hFrameDataLeft->frameInfo;
  FRAME_INFO *frameInfoRight   = &hFrameDataRight->frameInfo;

  FRAME_INFO frameInfoMerge;
  Flag addHarmonicsMerge[MAX_FREQ_COEFFS];

  Word16 bordersTemp[MAX_ENVELOPES*2 +2];
  Word16 nEnvelopes = 1;

  INVF_MODE sbr_invf_modeMerge[MAX_INVF_BANDS];

  Word16  iEnvelopeMerge[MAX_NUM_ENVELOPE_VALUES];
  Word16  sbrNoiseFloorLevelMerge[MAX_NUM_NOISE_VALUES];

  Word16*  iEnvelopeLeft           = hFrameDataLeft->iEnvelope;
  Word16*  iEnvelopeRight          = hFrameDataRight->iEnvelope;
  Word16*  sbrNoiseFloorLevelLeft  = hFrameDataLeft->sbrNoiseFloorLevel;
  Word16*  sbrNoiseFloorLevelRight = hFrameDataRight->sbrNoiseFloorLevel;

  Word16 noSubbands;
  Word16 noNoiseBands = hFreq->nNfb;
  Word16* nSfb        = hFreq->nSfb;

  memop16(sizeof(FRAME_INFO)/sizeof(Word16)); /* init frameInfoMerge[] */
  memop16(MAX_FREQ_COEFFS);     /* init addHarmonicsMerge[] */
  memop16(MAX_ENVELOPES*2 +2);  /* init bordersTemp[] */
  memop16(MAX_INVF_BANDS);      /* init sbr_invf_modeMerge[] */
  memop16(MAX_NUM_ENVELOPE_VALUES); /* init iEnvelopeMerge[] */
  memop16(MAX_NUM_NOISE_VALUES); /* init sbrNoiseFloorLevelMerge[] */

  move16(); /* init nEnvelopes */
  move16(); /* init iEnvelopeLeft */ 
  move16(); /* init iEnvelopeRight */ 
  move16(); /* init sbrNoiseFloorLevelLeft */ 
  move16(); /* init sbrNoiseFloorLevelRight */ 
  move16(); /* init noNoiseBands */ 
  move16(); /* init nSfb */ 
  
  noSubbands = sub(hFreq->highSubband, hFreq->lowSubband);

  for(band = 0; band < noNoiseBands; band++){
    sbr_invf_modeMerge[band] = S_max(hFrameDataLeft->sbr_invf_mode[band],
                                     hFrameDataRight->sbr_invf_mode[band]); move16();
  }

  for(band = 0; band < noSubbands; band++){
    addHarmonicsMerge[band] = (hFrameDataLeft->addHarmonics[band] ||
                               hFrameDataRight->addHarmonics[band]); logic16(); move16();
  }


  bordersTemp[0] = S_max(frameInfoLeft->borders[0], frameInfoRight->borders[0]); move16();

  bordersTemp[nEnvelopes] = S_max(frameInfoLeft->borders[frameInfoLeft->nEnvelopes],
                                  frameInfoRight->borders[frameInfoRight->nEnvelopes]); move16();


  envLeft = 0;

  test();
  while( sub(frameInfoLeft->borders[envLeft], bordersTemp[0]) <= 0 ) {
    envLeft++;                                                  test(); add(0,0);
  }

  envRight = 0;

  test();
  while( sub(frameInfoRight->borders[envRight], bordersTemp[0]) <= 0 ) {
    envRight++;                                                 test(); add(0,0);
  }

  test(); test();
  while( (sub(envLeft, frameInfoLeft->nEnvelopes) <= 0) && (sub(envRight, frameInfoRight->nEnvelopes) <= 0) ) {
    Word16 borderLeftChannel  = frameInfoLeft->borders[envLeft];
    Word16 borderRightChannel = frameInfoRight->borders[envRight];

    bordersTemp[nEnvelopes + 1] = bordersTemp[nEnvelopes];      move16();

    test();
    if ( sub(borderLeftChannel, borderRightChannel) < 0 ){
      bordersTemp[nEnvelopes] = frameInfoLeft->borders[envLeft]; move16();
      envLeft++;
    }
    else{
      bordersTemp[nEnvelopes] = frameInfoRight->borders[envRight]; move16();
      envRight++;
    }

    nEnvelopes++;
    /* end of while */   test(); test();
  }

  sub(nEnvelopes, 1);
  for(env = 0; env < nEnvelopes - 1; env++){
    test(); test();
    while( (sub(sub(bordersTemp[env + 1], bordersTemp[env]), 2) < 0) && (add(sub(env, nEnvelopes),1)  <  0) ){
      sub(sub(nEnvelopes,env),1);
      for (i=0; i<nEnvelopes-env-1; i++) {
        bordersTemp[env+1+i] = bordersTemp[env+2+i];            move16();
      }

      nEnvelopes--;
      /*end of while */ test(); test();
    }

  }

  test();
  if( sub(sub(bordersTemp[nEnvelopes], bordersTemp[nEnvelopes - 1]), 2) < 0 ){
    bordersTemp[nEnvelopes - 1] = bordersTemp[nEnvelopes];      move16();
    nEnvelopes--;
  }

    test();
  while( sub(nEnvelopes, 5) > 0){
    for(env = nEnvelopes; env > 0; env--){
      test();
      if( sub(sub(bordersTemp[env], bordersTemp[env - 1]),4) < 0)
        break;
    }
    sub(sub(nEnvelopes,env),1);
    for (i=0; i<nEnvelopes - env + 1; i++) {
      bordersTemp[env-1+i] =  bordersTemp[env+i];               move16();
    }
    nEnvelopes--;
    /*end of while */ test();
  }
      
  frameInfoMerge.nEnvelopes = nEnvelopes;                       move16();

  for(env = 0; env <= nEnvelopes; env++){
    frameInfoMerge.borders[env] = bordersTemp[env];             move16();
  }

  test();
  if( add(frameInfoLeft->tranEnv,1) == 0){
    frameInfoMerge.tranEnv = frameInfoRight->tranEnv;           move16();
  }
  else{
    test();
    if( add(frameInfoRight->tranEnv,1) == 0){
      frameInfoMerge.tranEnv = frameInfoLeft->tranEnv;          move16();
    }
    else{
      frameInfoMerge.tranEnv = S_min(frameInfoLeft->tranEnv, frameInfoRight->tranEnv); move16();
    }
  }

  frameInfoMerge.nNoiseEnvelopes = S_max(frameInfoLeft->nNoiseEnvelopes,frameInfoRight->nNoiseEnvelopes); move16();

  test();
  if( sub(frameInfoMerge.nNoiseEnvelopes,1) > 0){

    test();
    if(sub(frameInfoLeft->nNoiseEnvelopes, frameInfoRight->nNoiseEnvelopes) <0) {
      frameInfoMerge.bordersNoise[0] = frameInfoMerge.borders[0];                         move16();
      frameInfoMerge.bordersNoise[1] = frameInfoRight->bordersNoise[1];                   move16();
      frameInfoMerge.bordersNoise[2] = frameInfoMerge.borders[frameInfoMerge.nEnvelopes]; move16();
    }
    else{

      test();
      if( sub(frameInfoRight->nNoiseEnvelopes, frameInfoLeft->nNoiseEnvelopes) < 0 ){
        frameInfoMerge.bordersNoise[0] = frameInfoMerge.borders[0];                         move16();
        frameInfoMerge.bordersNoise[1] = frameInfoLeft->bordersNoise[1];                    move16();
        frameInfoMerge.bordersNoise[2] = frameInfoMerge.borders[frameInfoMerge.nEnvelopes]; move16();
      }
      else{
        frameInfoMerge.bordersNoise[0] = frameInfoMerge.borders[0];                         move16();
        frameInfoMerge.bordersNoise[1] = S_min(frameInfoLeft->bordersNoise[1],frameInfoRight->bordersNoise[1]); move16();
        frameInfoMerge.bordersNoise[2] = frameInfoMerge.borders[frameInfoMerge.nEnvelopes]; move16();
      }
    }
  }
  else{
    frameInfoMerge.bordersNoise[0] = frameInfoMerge.borders[0];                         move16();
    frameInfoMerge.bordersNoise[1] = frameInfoMerge.borders[frameInfoMerge.nEnvelopes]; move16();
  }


  test();
  if( sub(frameInfoMerge.nNoiseEnvelopes,1) > 0){
    move16(); /*frameInfoMerge.nEnvelopes*/
    for(env = 1; env < frameInfoMerge.nEnvelopes; env++){
      test();
      if( sub(frameInfoMerge.borders[env],frameInfoMerge.bordersNoise[1]) >= 0){
        break;
      }
    }

    frameInfoMerge.bordersNoise[1] = frameInfoMerge.borders[env]; move16();
  }



  envLeft     = 0;  move16();
  envRight    = 0;  move16();
  offset      = 0;  move16();
  offsetRight = 0;  move16();
  offsetLeft  = 0;  move16();

  move16(); /*frameInfoMerge.nEnvelopes*/
  for(env = 0; env < frameInfoMerge.nEnvelopes;env++){
    Word16 freqResLeft  = frameInfoLeft->freqRes[envLeft];
    Word16 freqResRight = frameInfoRight->freqRes[envRight];
    Word16 freqRes;
    Word16 bandLeft  = 0;
    Word16 bandRight = 0;
    Word16 band;

    move16(); /* init bandLeft */
    move16(); /* init bandRight */
    move16(); /* init freqResLeft */
    move16(); /* init freqResRight */

    test();
    if( sub(frameInfoMerge.borders[env + 1], frameInfoLeft->borders[envLeft+1]) > 0){

      test();
      if( add(sub(envLeft, frameInfoLeft->nEnvelopes), 1) < 0){
        offsetLeft += nSfb[freqResLeft];                        move16();
        envLeft++;
      }
    }

    test();
    if( sub(frameInfoMerge.borders[env + 1], frameInfoRight->borders[envRight+1]) > 0){

      test();
      if( add(sub(envRight, frameInfoRight->nEnvelopes), 1) < 0){
        offsetRight += nSfb[freqResRight];                      move16();
        envRight++;
      }
    }

    freqResLeft  = frameInfoLeft->freqRes[envLeft];             move16();
    freqResRight = frameInfoRight->freqRes[envRight];           move16();

    freqRes      = freqResLeft || freqResRight;                 logic16();

    frameInfoMerge.freqRes[env] = freqRes;                      move16();

    move16(); /* nSfb[freqRes] */
    for(band = 0; band < nSfb[freqRes]; band++){
      Word16 ui      = hFreq->freqBandTable[freqRes     ][band+1];
      Word16 uiLeft  = hFreq->freqBandTable[freqResLeft ][bandLeft+1];
      Word16 uiRight = hFreq->freqBandTable[freqResRight][bandRight+1];
      Word16 mant;
      Word16 exp;

      test();
      if( sub(ui, uiLeft) > 0) {
        bandLeft++;
      }

      test();
      if( sub(ui, uiRight) > 0) {
        bandRight++;
      }
      
      logic16(); logic16();
      ffr_add_MantExp(iEnvelopeLeft[bandLeft + offsetLeft],
                      iEnvelopeLeft[bandLeft + offsetLeft] & (Word16)MASK_E,
                      iEnvelopeRight[bandRight + offsetRight],
                      iEnvelopeRight[bandRight + offsetRight] & (Word16)MASK_E,
                      &mant,
                      &exp);
      exp = sub(exp, 1);

      logic16(); logic16(); move16();
      iEnvelopeMerge[band + offset] = (mant & MASK_M) | exp;
    }
    offset = add(offset, nSfb[freqRes]);
  }

  nScaleFactors = offset; move16();


  envLeft     = 0;  move16();
  envRight    = 0;  move16();
  offset      = 0;  move16();
  offsetRight = 0;  move16();
  offsetLeft  = 0;  move16();

  move16(); /*frameInfoMerge.nNoiseEnvelopes*/
  for(env = 0; env < frameInfoMerge.nNoiseEnvelopes; env++){
    Word16 band;

    test(); test();
    if( (sub(frameInfoMerge.bordersNoise[env], frameInfoLeft->bordersNoise[envLeft]) > 0) &&
        (add(sub(envLeft,frameInfoLeft->nNoiseEnvelopes),1) < 0) ){
      envLeft++;
      offsetLeft += noNoiseBands;
    }

    test(); test();
    if( (sub(frameInfoMerge.bordersNoise[env],frameInfoRight->bordersNoise[envRight]) > 0) &&
        (add(sub(envRight,frameInfoRight->nNoiseEnvelopes), 1) < 0) ){
      envRight++;
      offsetRight += noNoiseBands;
    }

    for(band = 0; band < noNoiseBands; band++){
      Word16 mant;
      Word16 exp;

      logic16(); logic16();
      ffr_add_MantExp(sbrNoiseFloorLevelLeft[band + offsetLeft],
                      sbrNoiseFloorLevelLeft[band + offsetLeft] & (Word16)MASK_E,
                      sbrNoiseFloorLevelRight[band + offsetRight],
                      sbrNoiseFloorLevelRight[band + offsetRight] & (Word16)MASK_E,
                      &mant,
                      &exp);

      exp = sub(exp, 1);

      logic16(); logic16(); move16();
      sbrNoiseFloorLevelMerge[band + offset] = (mant & MASK_M) | exp;
    }

    offset += noNoiseBands;
  }


  memcpy(frameInfoLeft,&frameInfoMerge,sizeof(FRAME_INFO)); memop16(sizeof(FRAME_INFO)/sizeof(Word16));

  memcpy(frameInfoLeft->borders, frameInfoMerge.borders, (MAX_ENVELOPES+1)*sizeof(Word16)); memop16(MAX_ENVELOPES+1);

  memcpy(frameInfoLeft->freqRes, frameInfoMerge.freqRes, (MAX_ENVELOPES)*sizeof(Word16)); memop16(MAX_ENVELOPES);

  memcpy(frameInfoLeft->bordersNoise, frameInfoMerge.bordersNoise, (MAX_NOISE_ENVELOPES+1)*sizeof(Word16)); memop16(MAX_NOISE_ENVELOPES+1);

  memcpy(iEnvelopeLeft, iEnvelopeMerge, MAX_NUM_ENVELOPE_VALUES*sizeof(Word16)); memop16(MAX_NUM_ENVELOPE_VALUES);

  memcpy(sbrNoiseFloorLevelLeft, sbrNoiseFloorLevelMerge, MAX_NUM_NOISE_VALUES*sizeof(Word16)); memop16(MAX_NUM_NOISE_VALUES);

  memcpy(hFrameDataLeft->addHarmonics, addHarmonicsMerge,MAX_FREQ_COEFFS*sizeof(Flag)); memop16(MAX_FREQ_COEFFS);

  memcpy(hFrameDataLeft->sbr_invf_mode, sbr_invf_modeMerge, MAX_INVF_BANDS*sizeof(INVF_MODE)); memop16(MAX_INVF_BANDS);

  hFrameDataLeft->nScaleFactors = nScaleFactors; move16();

}
