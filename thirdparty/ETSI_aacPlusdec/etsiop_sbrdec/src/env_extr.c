/*
   envelope extraction
*/

#include <string.h>
#include <assert.h>
#include "ffr.h"
#include "sbr_ram.h"
#include "sbr_rom.h"
#include "env_extr.h"
#include "sbr_const.h"       /* Various defines */
#include "intrinsics.h"
#include "count.h"
#ifndef MONO_ONLY
#include "ps_bitdec.h"
#include "ps_dec.h"
#endif

static Word16 extractFrameInfo (HANDLE_BIT_BUF hBitBuf,
                                HANDLE_SBR_FRAME_DATA h_frame_data);
static Word16 sbrGetEnvelope (HANDLE_SBR_HEADER_DATA hHeaderData,
                              HANDLE_SBR_FRAME_DATA h_frame_data,
                              HANDLE_BIT_BUF hBitBuf);
static void sbrGetDirectionControlData (HANDLE_SBR_FRAME_DATA hFrameData,
                                        HANDLE_BIT_BUF hBitBuf);
static void sbrGetNoiseFloorData (HANDLE_SBR_HEADER_DATA hHeaderData,
                                  HANDLE_SBR_FRAME_DATA h_frame_data,
                                  HANDLE_BIT_BUF hBitBuf);
static Word16 checkFrameInfo (FRAME_INFO *pFrameInfo);



/*!
  \brief     Decode one Huffman code word
  \return    decoded value
*/
Word16
decode_huff_cw (Huffman h,                   /*!< pointer to huffman codebook table */
                HANDLE_BIT_BUF hBitBuf)   /*!< Handle to Bitbuffer */
{
  Word16 index;
  Word16 value, bit;
  index = 0;                                                    move16();

  while (index >= 0) {                                          test();
    bit = (Word16)ReadBits (hBitBuf, 1);
    test();
    if ( bit ) {
      Word16 sign = h[index] & 0x0080;                          logic16(); 
      test();
      if (sign) {
        index = h[index] | 0xff80;                              logic16();
      }
      else {
        index = h[index] & 0x007f;                              logic16();
      }
    }
    else {
      index = shr(h[index], 8);
    }
  }

  value = add(index, 64); /* Add offset */

  return( value );
}


/*!
  \brief     Initialize SBR header data
*/
void
initHeaderData (SBR_HEADER_DATA *hHeaderData, /*!< Static SBR data to be initialized */
                Word32 sampleRate,              /*!< Core sampling frequency */
                Word16 samplesPerFrame)         /*!< Core frame size */
{
  HANDLE_FREQ_BAND_DATA hFreq = &FreqBandData;

  /* Fill in default values first */
                                                                memop16(sizeof(SBR_HEADER_DATA)/sizeof(Word16));
  memcpy(hHeaderData, &sbr_defaultHeader, sizeof(SBR_HEADER_DATA));

  /* Setup pointers to frequency band tables */
  hFreq->freqBandTable[LOW_RES]  = hFreq->freqBandTableLo;      move16();
  hFreq->freqBandTable[HIGH_RES] = hFreq->freqBandTableHi;      move16();
  hHeaderData->hFreqBandData = hFreq;                           move16();

  /* Patch some entries */
  hHeaderData->codecFrameSize = samplesPerFrame;                move16();
  hHeaderData->outSampleRate = L_shl(sampleRate,1);             move32();

  /* One SBR timeslot corresponds to 32 or 64 samples */
  hHeaderData->numberTimeSlots = extract_l(L_shr(samplesPerFrame, add(4,hHeaderData->timeStep)));
}


/*!
  \brief   Initialize the SBR_PREV_FRAME_DATA struct
*/
void
initSbrPrevFrameData (HANDLE_SBR_PREV_FRAME_DATA h_prev_data, /*!< handle to struct SBR_PREV_FRAME_DATA */
                      Word16 timeSlots)                          /*!< Framelength in SBR-timeslots */
{
  Word16 i;

  /* Set previous energy and noise levels to 0 for the case
     that decoding starts in the middle of a bitstream */
  for (i=0; i < MAX_FREQ_COEFFS; i++) {
    h_prev_data->sfb_nrg_prev[i] = 0;                           move16();
  }
  for (i=0; i < MAX_NOISE_COEFFS; i++) {
    h_prev_data->prevNoiseLevel[i] = 0;                         move16();
  }
  for (i=0; i < MAX_INVF_BANDS; i++) {
    h_prev_data->sbr_invf_mode[i] = INVF_OFF;                   move16();
  }

  h_prev_data->stopPos = timeSlots;                             move16();
  h_prev_data->coupling = COUPLING_OFF;                         move16();
  h_prev_data->ampRes = 0;                                      move16();
  h_prev_data->maxQmfSubbandAac = 0;                            move16();
}


/*!
  \brief   Read header data from bitstream 
                
  \return  error status - 0 if ok
*/
SBR_HEADER_STATUS
sbrGetHeaderData (SBR_HEADER_DATA *h_sbr_header, /*!< handle to struct SBR_HEADER_DATA */
                  HANDLE_BIT_BUF hBitBuf,        /*!< handle to struct BIT_BUFFER */
                  Flag stereoFlag)               /*!< 0: mono  1: stereo */
{
  SBR_HEADER_DATA lastHeader;
  Word16 dummy;
  Flag headerExtra1, headerExtra2;

  /* Copy header to temporary header */
                                                                memop16(sizeof(SBR_HEADER_DATA)/sizeof(Word16));
  memcpy (&lastHeader, h_sbr_header, sizeof(SBR_HEADER_DATA));

  /* Read new header from bitstream */

  h_sbr_header->ampResolution = (Word16)ReadBits (hBitBuf, SI_SBR_AMP_RES_BITS);  move16();

  h_sbr_header->startFreq = (Word16)ReadBits (hBitBuf, SI_SBR_START_FREQ_BITS); move16();

  h_sbr_header->stopFreq = (Word16)ReadBits (hBitBuf, SI_SBR_STOP_FREQ_BITS); move16();

  h_sbr_header->xover_band = (Word16)ReadBits (hBitBuf, SI_SBR_XOVER_BAND_BITS);  move16();

  dummy = (Word16)ReadBits (hBitBuf, SI_SBR_RESERVED_BITS_HDR);
  headerExtra1 = (Flag)ReadBits (hBitBuf, SI_SBR_HEADER_EXTRA_1_BITS);
  headerExtra2 = (Flag)ReadBits (hBitBuf, SI_SBR_HEADER_EXTRA_2_BITS);

  test();
  if (stereoFlag) {
    h_sbr_header->channelMode = STEREO;                         move16();
  }
  else {
    h_sbr_header->channelMode = MONO; /* may be overridden later */ move16();
  }

  /* Handle extra header information */
  test();
  if(headerExtra1) {
    h_sbr_header->freqScale = (Word16)ReadBits (hBitBuf, SI_SBR_FREQ_SCALE_BITS); move16();

    h_sbr_header->alterScale = (Word16)ReadBits (hBitBuf, SI_SBR_ALTER_SCALE_BITS); move16();
    h_sbr_header->noise_bands = (Word16)ReadBits (hBitBuf, SI_SBR_NOISE_BANDS_BITS);  move16();
  }
  else {
    h_sbr_header->freqScale   = SBR_FREQ_SCALE_DEFAULT;         move16();
    h_sbr_header->alterScale  = SBR_ALTER_SCALE_DEFAULT;        move16();
    h_sbr_header->noise_bands = SBR_NOISE_BANDS_DEFAULT;        move16();
  }

  test();
  if(headerExtra2) {
    h_sbr_header->limiterBands = (Word16)ReadBits (hBitBuf, SI_SBR_LIMITER_BANDS_BITS); move16();
    h_sbr_header->limiterGains = (Word16)ReadBits (hBitBuf, SI_SBR_LIMITER_GAINS_BITS); move16();
    h_sbr_header->interpolFreq = (Word16)ReadBits (hBitBuf, SI_SBR_INTERPOL_FREQ_BITS); move16();
    h_sbr_header->smoothingLength = (Word16)ReadBits (hBitBuf, SI_SBR_SMOOTHING_LENGTH_BITS); move16();
  }
  else {
    h_sbr_header->limiterBands    = SBR_LIMITER_BANDS_DEFAULT;    move16();
    h_sbr_header->limiterGains    = SBR_LIMITER_GAINS_DEFAULT;    move16(); 
    h_sbr_header->interpolFreq    = SBR_INTERPOL_FREQ_DEFAULT;    move16(); 
    h_sbr_header->smoothingLength = SBR_SMOOTHING_LENGTH_DEFAULT; move16();  
  }



  /* Look for new settings */
  test(); test(); test(); test(); test(); test(); test();
  if(sub(h_sbr_header->syncState, SBR_ACTIVE)               != 0 ||
     sub(lastHeader.startFreq, h_sbr_header->startFreq)     != 0 ||
     sub(lastHeader.stopFreq, h_sbr_header->stopFreq)       != 0 ||
     sub(lastHeader.xover_band, h_sbr_header->xover_band)   != 0 ||
     sub(lastHeader.freqScale, h_sbr_header->freqScale)     != 0 ||
     sub(lastHeader.alterScale, h_sbr_header->alterScale)   != 0 ||
     sub(lastHeader.noise_bands, h_sbr_header->noise_bands) != 0) {
    return HEADER_RESET; /* New settings */
  }

  return HEADER_OK; /* Everything ok */
}

/*!
  \brief   Get missing harmonics parameters (only used for AAC+SBR)
                
  \return  error status - 0 if ok
*/
static Word16
sbrGetSyntheticCodedData(HANDLE_SBR_HEADER_DATA hHeaderData,
                         HANDLE_SBR_FRAME_DATA hFrameData,                         
                         HANDLE_BIT_BUF     hBitBuf)
{
  Word16 i, bitsRead;
  Flag flag = (Flag)ReadBits(hBitBuf,1);

  bitsRead = 1;                                         move16();
  
  test();
  if(flag){
    move16(); /*hHeaderData->hFreqBandData->nSfb[HI]*/
    for(i=0;i<hHeaderData->hFreqBandData->nSfb[HI];i++){
      hFrameData->addHarmonics[i]  = (Flag)ReadBits (hBitBuf, SI_SBR_ADDITIONAL_HARMONICS_BITS );     move16();
      bitsRead = add(bitsRead, 1);
    }
  }
  else {
    for(i=0; i<MAX_FREQ_COEFFS; i++) {
      hFrameData->addHarmonics[i]  = 0;                 move16();
    }
  }
  return(bitsRead);
}


/*!
  \brief      Reads extension data from the bitstream

  \return  ok-flag (1=ok, 0=error)
*/
static Word16 extractExtendedData(HANDLE_SBR_FRAME_DATA hFrameData,     /*!< Destination for extracted data of left channel */
                               HANDLE_SBR_FRAME_DATA hFrameDataRight,/*!< Destination for extracted data of right channel */
#ifndef MONO_ONLY
                               HANDLE_SBR_HEADER_DATA hHeaderData,   /*!< handle to sbr header */
                               HANDLE_PS_DEC          hPS,           /*!< Parametric Stereo Decoder */
#endif
                               HANDLE_BIT_BUF     hBitBuf)           /*!< Handle to the bit buffer */
{
  Word16 i;
  Word16 extended_data;
  Word16 nBitsLeft;

  extended_data = (Word16)ReadBits(hBitBuf, SI_SBR_EXTENDED_DATA_BITS);

  test();
  if (extended_data) {
    Word16 cnt;
    Flag bPsRead;

    bPsRead = 0;                                                move16();

    cnt = (Word16)ReadBits(hBitBuf, SI_SBR_EXTENSION_SIZE_BITS);
    test();
    if (sub(cnt, (1<<SI_SBR_EXTENSION_SIZE_BITS)-1) == 0) {
      cnt = add(cnt, (Word16)ReadBits(hBitBuf, SI_SBR_EXTENSION_ESC_COUNT_BITS));
    }


    nBitsLeft = shl(cnt, 3);
    test();
    while (sub(nBitsLeft,7) > 0) {                              
      Word16 extension_id = (Word16)ReadBits(hBitBuf, SI_SBR_EXTENSION_ID_BITS);
                                                                test();

      nBitsLeft = sub(nBitsLeft, SI_SBR_EXTENSION_ID_BITS);

      sub(1, 1); test();
      switch(extension_id) {

#ifndef MONO_ONLY
      case EXTENSION_ID_PS_CODING:
        test();
        if (hPS==NULL) {
          return 0;
        }
        
        test(); logic16();
        if (! (hPS->bForceMono || bPsRead)) {
          
          nBitsLeft = sub(nBitsLeft, ReadPsData(hPS, hBitBuf, nBitsLeft));
          test();
          if (nBitsLeft < 0)
            return 0;
          hHeaderData->channelMode = PS_STEREO;                move16();
          bPsRead = 1;                                         move16();
          break;
        }
#endif

      default:
        /* An unknown extension id causes the remaining extension data
           to be skipped */
        cnt = shr(nBitsLeft, 3); /* number of remaining bytes */
        for (i=0; i<cnt; i++)
          ReadBits(hBitBuf, 8);
        nBitsLeft = sub(nBitsLeft, shl(cnt,3));
        break;
      }
      test(); /* end of while */
    }

    test();
    if (nBitsLeft < 0)
      return 0;

    /* Skip remaining bits of extended data */
    ReadBits(hBitBuf, nBitsLeft);

  }
  return 1;
}



/*!
  \brief   Read bitstream elements of one channel

  \return  SbrFrameOK:  1=ok, 0=error
*/
Word8
sbrGetSingleChannelElement (HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
                            HANDLE_SBR_FRAME_DATA  hFrameData,  /*!< Control data of current frame */
#ifndef MONO_ONLY
                            HANDLE_PS_DEC          hPS,         /*!< handle to struct PS_DEC */
#endif
                            HANDLE_BIT_BUF         hBitBuf)     /*!< handle to struct BIT_BUF */
{
  Word16 i, bit;

  hFrameData->coupling = COUPLING_OFF;  move16();

    /* reserved bits */
  bit = (Word16)ReadBits(hBitBuf, 1);
  test();
  if (bit)
    ReadBits(hBitBuf, SI_SBR_RESERVED_BITS_DATA);


  /*
    Grid control
  */
  test();
  if ( !extractFrameInfo (hBitBuf, hFrameData) )
    return 0;
  
  test();
  if ( !checkFrameInfo (&hFrameData->frameInfo) )
    return 0;


  /*
    Fetch domain vectors (time or frequency direction for delta-coding)
  */
  sbrGetDirectionControlData (hFrameData, hBitBuf);
  test();
  if (sub(hFrameData->domain_vec[0],FREQ) == 0) {
    hHeaderData->frameErrorFlag = 0;                            move16();
  }

  move16(); /* hHeaderData->hFreqBandData->nInvfBands */
  for (i=0; i<hHeaderData->hFreqBandData->nInvfBands; i++) {
    hFrameData->sbr_invf_mode[i] =
      (INVF_MODE) ReadBits (hBitBuf, SI_SBR_INVF_MODE_BITS);  move16();
  }


  /* raw data */
  test();
  if ( !sbrGetEnvelope (hHeaderData, hFrameData, hBitBuf) )
    return 0;

  sbrGetNoiseFloorData (hHeaderData, hFrameData, hBitBuf);
  
  sbrGetSyntheticCodedData(hHeaderData, hFrameData, hBitBuf);

  /* sbr extended data */
  extractExtendedData(hFrameData,
                      NULL,
#ifndef MONO_ONLY
                      hHeaderData,
                      hPS,
#endif
                      hBitBuf );

  return 1;
}


/*!
  \brief      Read bitstream elements of a channel pair
  \return     SbrFrameOK  
*/
Word8
sbrGetChannelPairElement (HANDLE_SBR_HEADER_DATA hHeaderData,   /*!< Static control data */
                          HANDLE_SBR_FRAME_DATA hFrameDataLeft, /*!< Dynamic control data for first channel */
                          HANDLE_SBR_FRAME_DATA hFrameDataRight,/*!< Dynamic control data for second channel */
                          HANDLE_BIT_BUF hBitBuf)            /*!< handle to struct BIT_BUF */
{
  Word16 i, bit;


    /* reserved bits */
  bit = (Word16)ReadBits(hBitBuf, 1);
  test();
  if (bit) {
    ReadBits(hBitBuf, SI_SBR_RESERVED_BITS_DATA);
    ReadBits(hBitBuf, SI_SBR_RESERVED_BITS_DATA);
  }

  test();
  if (sub(hHeaderData->channelMode,STEREO) != 0) {
    /* There has been received a MONO-header but this is a ChannelPairElement!
       SBR will be disabled until the next header is received.
     */
    hHeaderData->syncState = UPSAMPLING;                        move16();
    return 0;
  }

  /* Read coupling flag */
  bit = (Word16)ReadBits (hBitBuf, SI_SBR_COUPLING_BITS);
  test();
  if (bit) {
    hFrameDataLeft->coupling = COUPLING_LEVEL;                  move16();
    hFrameDataRight->coupling = COUPLING_BAL;                   move16();
  }
  else {
    hFrameDataLeft->coupling = COUPLING_OFF;                    move16();
    hFrameDataRight->coupling = COUPLING_OFF;                   move16();
  }


  /*
    Grid control
  */
  test();
  if ( !extractFrameInfo (hBitBuf, hFrameDataLeft) )
    return 0;
  test();
  if ( !checkFrameInfo (&hFrameDataLeft->frameInfo) )
    return 0;

  test();
  if (hFrameDataLeft->coupling) {
                                                                memop16(sizeof(FRAME_INFO)/sizeof(Word16));
    memcpy (&hFrameDataRight->frameInfo, &hFrameDataLeft->frameInfo, sizeof(FRAME_INFO));
  }
  else {
    test();
    if ( !extractFrameInfo (hBitBuf, hFrameDataRight) )
      return 0;
    test();
    if ( !checkFrameInfo (&hFrameDataRight->frameInfo) )
      return 0;
  }

  /*
    Fetch domain vectors (time or frequency direction for delta-coding)
  */
  sbrGetDirectionControlData (hFrameDataLeft, hBitBuf);
  sbrGetDirectionControlData (hFrameDataRight, hBitBuf);
  /*
    To avoid distortions after some bad frames,
    we clear the error flag only if no delta coding in time occurs.
    However, SBR can take a little longer to come up again.
  */
  test(); test();
  if ((sub(hFrameDataLeft->domain_vec[0],FREQ)==0) && (sub(hFrameDataRight->domain_vec[0],FREQ)==0)) {
    hHeaderData->frameErrorFlag = 0;                            move16();
  }


  move16(); /* hHeaderData->hFreqBandData->nInvfBands */
  for (i=0; i<hHeaderData->hFreqBandData->nInvfBands; i++) {
    hFrameDataLeft->sbr_invf_mode[i] = (INVF_MODE) ReadBits (hBitBuf, SI_SBR_INVF_MODE_BITS);
  }

  test();
  if (hFrameDataLeft->coupling) {
    move16(); /* hHeaderData->hFreqBandData->nInvfBands */
    for (i=0; i<hHeaderData->hFreqBandData->nInvfBands; i++) {
      hFrameDataRight->sbr_invf_mode[i] = hFrameDataLeft->sbr_invf_mode[i]; move16();
    }


    test();
    if ( !sbrGetEnvelope (hHeaderData, hFrameDataLeft, hBitBuf) ) {
      return 0;
    }

    sbrGetNoiseFloorData (hHeaderData, hFrameDataLeft, hBitBuf);

    test();
    if ( !sbrGetEnvelope (hHeaderData, hFrameDataRight, hBitBuf) ) {
      return 0;
    }
  }
  else {
    move16(); /* hHeaderData->hFreqBandData->nInvfBands */    
    for (i=0; i<hHeaderData->hFreqBandData->nInvfBands; i++) {
      hFrameDataRight->sbr_invf_mode[i] = (INVF_MODE) ReadBits (hBitBuf, SI_SBR_INVF_MODE_BITS);  move16();
    }


    test();
    if ( !sbrGetEnvelope (hHeaderData, hFrameDataLeft, hBitBuf ) )
      return 0;

    test();
    if ( !sbrGetEnvelope (hHeaderData, hFrameDataRight, hBitBuf) )
      return 0;

    sbrGetNoiseFloorData (hHeaderData, hFrameDataLeft, hBitBuf);

  }
  sbrGetNoiseFloorData (hHeaderData, hFrameDataRight, hBitBuf);

  sbrGetSyntheticCodedData(hHeaderData, hFrameDataLeft, hBitBuf);
  sbrGetSyntheticCodedData(hHeaderData, hFrameDataRight, hBitBuf);

  /* sbr extended data */
  extractExtendedData(hFrameDataLeft,
                      hFrameDataRight,
#ifndef MONO_ONLY
                      hHeaderData,
                      NULL,
#endif
                      hBitBuf );

  return 1;
}




/*!
  \brief   Read direction control data from bitstream 
*/
void
sbrGetDirectionControlData (HANDLE_SBR_FRAME_DATA h_frame_data, /*!< handle to struct SBR_FRAME_DATA */
                            HANDLE_BIT_BUF hBitBuf)          /*!< handle to struct BIT_BUF */
{
  Word16 i;
  move16(); /* h_frame_data->frameInfo.nEnvelopes */
  for (i = 0; i < h_frame_data->frameInfo.nEnvelopes; i++) {
    h_frame_data->domain_vec[i] = (Word16)ReadBits (hBitBuf, SI_SBR_DOMAIN_BITS); move16();
  }

  move16(); /* h_frame_data->frameInfo.nNoiseEnvelopes */
  for (i = 0; i < h_frame_data->frameInfo.nNoiseEnvelopes; i++) {
    h_frame_data->domain_vec_noise[i] = (Word16)ReadBits (hBitBuf, SI_SBR_DOMAIN_BITS); move16();
  }
}



/*!
  \brief   Read noise-floor-level data from bitstream 
*/
void
sbrGetNoiseFloorData (HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
                      HANDLE_SBR_FRAME_DATA h_frame_data, /*!< handle to struct SBR_FRAME_DATA */
                      HANDLE_BIT_BUF hBitBuf)          /*!< handle to struct BIT_BUF */
{
  Word16 i,j;
  Word16 delta;
  COUPLING_MODE coupling;
  Word16 noNoiseBands;

  Huffman hcb_noiseF;
  Huffman hcb_noise;
  Word16  envDataTableCompFactor;

  Word16 start_bits;
  Word16 start_bits_balance;

  Word16 index;

  noNoiseBands = hHeaderData->hFreqBandData->nNfb;                   move16();
  start_bits = SI_SBR_START_NOISE_BITS_AMP_RES_3_0;                  move16();
  start_bits_balance = SI_SBR_START_NOISE_BITS_BALANCE_AMP_RES_3_0;  move16();

  coupling = h_frame_data->coupling;                            move16();


  /*
    Select huffman codebook depending on coupling mode
  */
  test();
  if (sub(coupling, COUPLING_BAL) == 0) {
    hcb_noise = (Huffman)&sbr_huffBook_NoiseBalance11T;         move16();
    hcb_noiseF = (Huffman)&sbr_huffBook_EnvBalance11F;          move16(); /* "sbr_huffBook_NoiseBalance11F" */
    envDataTableCompFactor = 1;                                 move16();
  }
  else {
    hcb_noise = (Huffman)&sbr_huffBook_NoiseLevel11T;           move16();
    hcb_noiseF = (Huffman)&sbr_huffBook_EnvLevel11F;            move16(); /* "sbr_huffBook_NoiseLevel11F" */
    envDataTableCompFactor = 0;                                 move16();
  }

  /*
    Read raw noise-envelope data
  */
  index = 0;                                                    move16();
  move16(); /* h_frame_data->frameInfo.nNoiseEnvelopes */
  for (i=0; i<h_frame_data->frameInfo.nNoiseEnvelopes; i++) {

    test();
    if (sub(h_frame_data->domain_vec_noise[i], FREQ) == 0) {
      test();
      if (sub(coupling, COUPLING_BAL) == 0) {
        h_frame_data->sbrNoiseFloorLevel[index] =
          shl((Word16)ReadBits (hBitBuf,start_bits_balance), envDataTableCompFactor); move16();
      }
      else {
        h_frame_data->sbrNoiseFloorLevel[index] =
          (Word16)ReadBits (hBitBuf, start_bits); move16();
      }

      for (j = 1; j < noNoiseBands; j++) {
        delta = decode_huff_cw(hcb_noiseF, hBitBuf);
        h_frame_data->sbrNoiseFloorLevel[index+j] = shl(delta, envDataTableCompFactor); move16();
      }
    }
    else {
      for (j = 0; j < noNoiseBands; j++) {
        delta = decode_huff_cw(hcb_noise, hBitBuf);
        h_frame_data->sbrNoiseFloorLevel[index+j] = shl(delta, envDataTableCompFactor); move16();
      }
    }

    index += noNoiseBands;
  }
}


/*!
  \brief   Read envelope data from bitstream 
*/
Word16
sbrGetEnvelope (HANDLE_SBR_HEADER_DATA hHeaderData, /*!< Static control data */
                HANDLE_SBR_FRAME_DATA h_frame_data, /*!< handle to struct SBR_FRAME_DATA */
                HANDLE_BIT_BUF hBitBuf)          /*!< handle to struct BIT_BUF */
{
  COUPLING_MODE coupling = h_frame_data->coupling;
  Huffman hcb_t, hcb_f;
  Word16 i, j;
  Word16 no_band[MAX_ENVELOPES];
  Word16 delta;
  Word16 offset,
    ampRes,
    nEnvelopes,
    envDataTableCompFactor,
    start_bits, start_bits_balance;

  delta = 0;                                                    move16();
  ampRes = hHeaderData->ampResolution;                          move16();
  nEnvelopes = h_frame_data->frameInfo.nEnvelopes;              move16();

  h_frame_data->nScaleFactors = 0;                              move16();

  test(); test();
  if ( (sub(h_frame_data->frameInfo.frameClass, FIXFIX) == 0) &&
       (sub(nEnvelopes, 1) == 0) ) {
    ampRes = SBR_AMP_RES_1_5;                                   move16();
  }
  h_frame_data->ampResolutionCurrentFrame = ampRes;             move16();

  /*
    Set number of bits for first value depending on amplitude resolution
  */
  test();
  if(sub(ampRes, SBR_AMP_RES_3_0) == 0)
  {
    start_bits = SI_SBR_START_ENV_BITS_AMP_RES_3_0;                  move16();
    start_bits_balance = SI_SBR_START_ENV_BITS_BALANCE_AMP_RES_3_0;  move16();
  }    
  else
  {
    start_bits = SI_SBR_START_ENV_BITS_AMP_RES_1_5;                  move16();
    start_bits_balance = SI_SBR_START_ENV_BITS_BALANCE_AMP_RES_1_5;  move16();
  }

  /*
    Calculate number of values for each envelope and alltogether
  */
  for (i = 0; i < nEnvelopes; i++) {
    no_band[i] = hHeaderData->hFreqBandData->nSfb[h_frame_data->frameInfo.freqRes[i]];  move16();
    h_frame_data->nScaleFactors = add(h_frame_data->nScaleFactors, no_band[i]); move16();
  }
  test();
  if (sub(h_frame_data->nScaleFactors, MAX_NUM_ENVELOPE_VALUES) > 0)
    return 0;

  /*
    Select Huffman codebook depending on coupling mode and amplitude resolution
  */
  test();
  if (sub(coupling, COUPLING_BAL) == 0) {
    envDataTableCompFactor = 1;                                 move16();
    test();
    if (sub(ampRes, SBR_AMP_RES_1_5) == 0) {
      hcb_t = (Huffman)&sbr_huffBook_EnvBalance10T;
      hcb_f = (Huffman)&sbr_huffBook_EnvBalance10F;
    }
    else {
      hcb_t = (Huffman)&sbr_huffBook_EnvBalance11T;
      hcb_f = (Huffman)&sbr_huffBook_EnvBalance11F;
    }
  }
  else {
    envDataTableCompFactor = 0;                                 move16();
    test();
    if (sub(ampRes, SBR_AMP_RES_1_5) == 0) {
      hcb_t = (Huffman)&sbr_huffBook_EnvLevel10T;
      hcb_f = (Huffman)&sbr_huffBook_EnvLevel10F;
    }
    else {
      hcb_t = (Huffman)&sbr_huffBook_EnvLevel11T;
      hcb_f = (Huffman)&sbr_huffBook_EnvLevel11F;
    }
  }

  /*
    Now read raw envelope data
  */
  offset = 0;                                                   move16();
  for (j = 0; j < nEnvelopes; j++) {

    test();
    if (sub(h_frame_data->domain_vec[j], FREQ) == 0) {
      test();
      if (sub(coupling, COUPLING_BAL) == 0) {
        h_frame_data->iEnvelope[offset] =
          shl( (Word16)ReadBits(hBitBuf, start_bits_balance), envDataTableCompFactor); move16();
      }
      else {
        h_frame_data->iEnvelope[offset] =
          (Word16)ReadBits (hBitBuf, start_bits); move16();
      }
    }
    move16(); /* no_band[j] */
    for (i = sub(1, h_frame_data->domain_vec[j]); i < no_band[j]; i++) {

      test();
      if (sub(h_frame_data->domain_vec[j], FREQ) == 0) {
        delta = decode_huff_cw(hcb_f, hBitBuf);
      }
      else {
        delta = decode_huff_cw(hcb_t, hBitBuf);
      }

      h_frame_data->iEnvelope[offset+i] = shl(delta, envDataTableCompFactor);
    }
    offset = add(offset, no_band[j]);
  }

  return 1;
}


/*!
  \brief   Extract the frame information (structure FRAME_INFO) from the bitstream
  \return  Zero for bitstream error, one for correct.
*/
Word16
extractFrameInfo (HANDLE_BIT_BUF hBitBuf,          /*!< bitbuffer handle */
                  HANDLE_SBR_FRAME_DATA h_frame_data) /*!< pointer to memory where the frame-info will be stored */
{

  Word16 i, k, n;
  Word16 pointer_bits, nEnv, b, border, p, temp;
  Word16 staticFreqRes, frameClass;
  Word16 aL, aR, nL, nR;
  FRAME_INFO * pFrameInfo = &h_frame_data->frameInfo;           move16();

  n = 0;                                                        move16();
  pointer_bits = 0;                                             move16();
  nEnv = 0;                                                     move16();
  b = 0;                                                        move16();
  temp = 0;                                                     move16();


  frameClass = (Word16)ReadBits (hBitBuf, SBR_CLA_BITS); /* frameClass = C [2 bits] */
  pFrameInfo->frameClass = frameClass;                          move16();

  switch (frameClass) {
  case FIXFIX:
    test();
    temp = (Word16)ReadBits (hBitBuf, SBR_ENV_BITS);     /* E [2 bits ] */

    staticFreqRes = (Word16)ReadBits (hBitBuf, SBR_RES_BITS);

    nEnv = shl(1, temp);    /* E -> e */
    test();
    if (sub(nEnv, MAX_ENVELOPES) > 0)
      return 0;
    b = add(nEnv, 1);
    switch (nEnv) {
    case 1:
      test();
                                                                memop16(sizeof(FRAME_INFO)/sizeof(Word16));
      memcpy (pFrameInfo, &sbr_frame_info1_16, sizeof(FRAME_INFO));
      break;
    case 2:
      test();test();
                                                                memop16(sizeof(FRAME_INFO)/sizeof(Word16));
      memcpy (pFrameInfo, &sbr_frame_info2_16, sizeof(FRAME_INFO));
      break;
    case 4:
      test();test();test();
                                                                memop16(sizeof(FRAME_INFO)/sizeof(Word16));
      memcpy (pFrameInfo, &sbr_frame_info4_16, sizeof(FRAME_INFO));
      break;
    case 8:
      test();test();test();test();
#if (MAX_ENVELOPES >= 8)
                                                                memop16(sizeof(FRAME_INFO)/sizeof(Word16));
      memcpy (pFrameInfo, &sbr_frame_info8_16, sizeof(FRAME_INFO));
      break;
#else
      return 0;
#endif
    }
    /* Apply correct freqRes (High is default) */
  test();
    if (!staticFreqRes) {
      for (i = 0; i < nEnv ; i++)
        pFrameInfo->freqRes[i] = 0;                                move16();
    }

    break;
  case FIXVAR:
  case VARFIX:
    test(); test();
    temp = (Word16)ReadBits (hBitBuf, SBR_ABS_BITS);   /* A [SBR_ABS_BITS bits] */

    n    = (Word16)ReadBits (hBitBuf, SBR_NUM_BITS);   /* n = N [SBR_NUM_BITS bits] */

    nEnv = add(n, 1);                             /* # envelopes */
    b = add(nEnv, 1);                             /* # borders   */

    break;
  }


  switch (frameClass) {
    Word16 nEnvm1;
  case FIXVAR:
    test();
    /* Decode borders: */
    pFrameInfo->borders[0] = 0;               /* first border          */ move16();
    border = add(temp, SBR_TIME_SLOTS);       /* A -> aR               */
    i = sub(b, 1);                            /* frame info index for last border */
    pFrameInfo->borders[i] = border;          /* last border                      */ move16();

    for (k = 0; k < n; k++) {
      temp = (Word16)ReadBits (hBitBuf, SBR_REL_BITS); /* R [SBR_REL_BITS bits] */
      border = sub(border, add(shl(temp,1),2));/* R -> r                */
      i--;
      pFrameInfo->borders[i] = border;                          move16();
    }


    /* Decode pointer: */
    pointer_bits = sub(sub(INT_BITS, 1), ffr_norm32(add(n,1)));

    p = (Word16)ReadBits (hBitBuf, pointer_bits);      /* p = P [pointer_bits bits] */

    test();
    if (sub(p, add(n,1)) > 0)
      return 0;

    /*pFrameInfo->tranEnv = p ? n + 2 - p : -1;*/
    test();
    if (p) {
      pFrameInfo->tranEnv = sub(add(n, 2), p);  move16();
    }
    else {
      pFrameInfo->tranEnv = -1;                                 move16();
    }


    /* Decode freq res: */
    for (k = n; k >= 0; k--) {
      pFrameInfo->freqRes[k] = (Word16)ReadBits (hBitBuf, SBR_RES_BITS); /* f = F [SBR_RES_BITS bits] */
      move16();
    }


    /* Calculate noise floor middle border: */
    test(); test();
    if (p == 0 || sub(p,1) == 0)
      pFrameInfo->bordersNoise[1] = pFrameInfo->borders[n];
    else
      pFrameInfo->bordersNoise[1] = pFrameInfo->borders[pFrameInfo->tranEnv];
    move16();

    break;

  case VARFIX:
    test();test();
    /* Decode borders: */
    border = temp;                            /* A -> aL */           move16();
    pFrameInfo->borders[0] = border;          /* first border */      move16();

    for (k = 1; k <= n; k++) {
      temp = (Word16)ReadBits (hBitBuf, SBR_REL_BITS); /* R [SBR_REL_BITS bits] */
      border = add(border, add(shl(temp,1),2));/* R -> r                */
      pFrameInfo->borders[k] = border;                                 move16();
    }
    pFrameInfo->borders[k] = SBR_TIME_SLOTS;  /* last border */        move16();


    /* Decode pointer: */
    pointer_bits = sub(INT_BITS- 1, ffr_norm32(add(n,1)));

    p = (Word16)ReadBits (hBitBuf, pointer_bits);      /* p = P [pointer_bits bits] */
    test();
    if (sub(p,add(n,1)) > 0)
      return 0;

    test(); test();
    if (p == 0 || sub(p,1) == 0) {
      pFrameInfo->tranEnv = -1;                                  move16();
    }
    else {
      pFrameInfo->tranEnv = sub(p, 1);                           move16();
    }



    /* Decode freq res: */
    for (k = 0; k <= n; k++) {
      pFrameInfo->freqRes[k] = (Word16)ReadBits(hBitBuf, SBR_RES_BITS); /* f = F [SBR_RES_BITS bits] */
      move16();
    }



    /* Calculate noise floor middle border: */
    switch (p) {
    case 0:
      test();
      pFrameInfo->bordersNoise[1] = pFrameInfo->borders[1];     move16();
      break;
    case 1:
      test();test();
      pFrameInfo->bordersNoise[1] = pFrameInfo->borders[n];     move16();
      break;
    default:
      test();test();
      pFrameInfo->bordersNoise[1] = pFrameInfo->borders[(Word32) pFrameInfo->tranEnv]; move16();
      break;
    }

    break;

  case VARVAR:
    test();test();test();
    aL = (Word16)ReadBits (hBitBuf, SBR_ABS_BITS);       /* AL [SBR_ABS_BITS bits], AL -> aL */

    aR = (Word16)ReadBits (hBitBuf, SBR_ABS_BITS) + SBR_TIME_SLOTS;     /* AR [SBR_ABS_BITS bits], AR -> aR */

    nL = (Word16)ReadBits (hBitBuf, SBR_NUM_BITS);       /* nL = NL [SBR_NUM_BITS bits] */

    nR = (Word16)ReadBits (hBitBuf, SBR_NUM_BITS);       /* nR = NR [SBR_NUM_BITS bits] */



    /*-------------------------------------------------------------------------
      Calculate help variables
      --------------------------------------------------------------------------*/

    /* general: */
    nEnv = add(add(nL, nR), 1);            /* # envelopes */
    test();
    if (sub(nEnv, MAX_ENVELOPES) > 0)
      return 0;
    b = add(nEnv, 1);                  /* # borders   */



    /*-------------------------------------------------------------------------
      Decode envelopes
      --------------------------------------------------------------------------*/


    /* L-borders:   */
    border            = aL;                   /* first border */    move16();
    pFrameInfo->borders[0] = border;                                move16();

    for (k = 1; k <= nL; k++) {
      temp = (Word16)ReadBits (hBitBuf, SBR_REL_BITS); /* R [SBR_REL_BITS bits] */
      border = add(border, add(shl(temp,1),2));               /* R -> r                */
      pFrameInfo->borders[k] = border;                              move16();
    }


    /* R-borders:  */
    border = aR;                              /* last border */     move16();
    i      = nEnv;                                                  move16(); 

    pFrameInfo->borders[i] = border;                                move16();

    for (k = 0; k < nR; k++) {
      temp = (Word16)ReadBits (hBitBuf, SBR_REL_BITS); /* R [SBR_REL_BITS bits] */
      border = sub(border, add(shl(temp,1),2));               /* R -> r                */
      i--;
      pFrameInfo->borders[i] = border;                              move16();
    }


    /* decode pointer: */
    pointer_bits = sub(INT_BITS-1, ffr_norm32(add(add(nL,nR),1)));

    p = (Word16)ReadBits (hBitBuf, pointer_bits);      /* p = P [pointer_bits bits] */
    test();
    if (sub(p, add(add(nL,nR),1)) > 0)
      return 0;

    test();
    if (p) {
      pFrameInfo->tranEnv = sub(b, p);  move16();
    }
    else {
      pFrameInfo->tranEnv = -1;                                 move16();
    }



    /* decode freq res: */
    for (k = 0; k < nEnv; k++) {
      pFrameInfo->freqRes[k] =(Word16) ReadBits(hBitBuf, SBR_RES_BITS); /* f = F [SBR_RES_BITS bits] */
      move16();
    }



    /*-------------------------------------------------------------------------
      Decode noise floors
      --------------------------------------------------------------------------*/
    pFrameInfo->bordersNoise[0] = aL;                           move16();

    test();
    nEnvm1 = sub(nEnv,1);
    if (nEnvm1 == 0) {
      /* 1 noise floor envelope: */
      pFrameInfo->bordersNoise[1] = aR;                         move16();
    }
    else {
      /* 2 noise floor envelopes */
      test(); logic16();
      if (p == 0 || sub(p,1) == 0)
        pFrameInfo->bordersNoise[1] = pFrameInfo->borders[nEnvm1];
      else
        pFrameInfo->bordersNoise[1] = pFrameInfo->borders[(int) pFrameInfo->tranEnv];
      move16();
      pFrameInfo->bordersNoise[2] = aR;                         move16();
    }
    break;
  }


  /*
    Store number of envelopes and noise floor envelopes
  */
  pFrameInfo->nEnvelopes = nEnv;                                move16();

  test();
  if (sub(nEnv,1) == 0)
    pFrameInfo->nNoiseEnvelopes = 1;
  else
    pFrameInfo->nNoiseEnvelopes = 2;
  move16();


  test(); test();
  if (sub(frameClass, VARFIX) == 0 || sub(frameClass, FIXVAR) == 0) {
    /* calculate noise floor first and last borders: */
    pFrameInfo->bordersNoise[0] = pFrameInfo->borders[0];       move16();
    pFrameInfo->bordersNoise[pFrameInfo->nNoiseEnvelopes] = pFrameInfo->borders[nEnv]; move16();
  }


  return 1;
}


/*!
  \brief   Check if the frameInfo vector has reasonable values.
  \return  Zero for error, one for correct
*/
Word16
checkFrameInfo (FRAME_INFO * pFrameInfo) /*!< pointer to frameInfo */
{
  Word16  i,j;
  Word16 startPos, stopPos, tranEnv, startPosNoise, stopPosNoise,
    nEnvelopes, nNoiseEnvelopes;

  nEnvelopes = pFrameInfo->nEnvelopes;                          move16();
  nNoiseEnvelopes = pFrameInfo->nNoiseEnvelopes;                move16();

  test(); test();
  if(sub(nEnvelopes,1) < 0 || sub(nEnvelopes, MAX_ENVELOPES) > 0)
    return 0;
  
  test();
  if(sub(nNoiseEnvelopes, MAX_NOISE_ENVELOPES) > 0)
    return 0;

  startPos        = pFrameInfo->borders[0];                     move16();
  stopPos         = pFrameInfo->borders[nEnvelopes];            move16();
  tranEnv         = pFrameInfo->tranEnv;                        move16();
  startPosNoise   = pFrameInfo->bordersNoise[0];                move16();
  stopPosNoise    = pFrameInfo->bordersNoise[nNoiseEnvelopes];  move16();
  
  /* Check that the start and stop positions of the frame are reasonable values. */
  test(); test();
  if( (startPos < 0) || (sub(startPos, stopPos) >= 0) )
    return 0;
  test();
  if( sub(startPos, SBR_OV_SLOTS) > 0 ) /* First env. must start in or directly after the overlap buffer */
    return 0;
  test();
  if( sub(stopPos, SBR_TIME_SLOTS) < 0 ) /* One complete frame must be ready for output after processing */
    return 0;
  test();
  if(sub(stopPos, add(SBR_TIME_SLOTS, SBR_OV_SLOTS)) > 0)
    return 0;

  /* Check that the  start border for every envelope is strictly later in time */
  for(i=0;i<nEnvelopes;i++) {
    test();
    if(sub(pFrameInfo->borders[i], pFrameInfo->borders[i+1]) >= 0)
      return 0;
  }
  
  /* Check that the envelope to be shortened is actually among the envelopes */
  test();
  if(sub(tranEnv,nEnvelopes) > 0)
    return 0;


  /* Check the noise borders */
  test(); test();
  if(sub(nEnvelopes,1)==0 && sub(nNoiseEnvelopes,1)>0)
    return 0;

  test(); test();
  if(sub(startPos, startPosNoise) != 0 || sub(stopPos, stopPosNoise) != 0)
    return 0;


  /* Check that the  start border for every noise-envelope is strictly later in time*/
  for(i=0; i<nNoiseEnvelopes; i++) {
    test();
    if(sub(pFrameInfo->bordersNoise[i], pFrameInfo->bordersNoise[i+1]) >= 0)
      return 0;
  }
  
  /* Check that every noise border is the same as an envelope border*/
  for(i=0; i<nNoiseEnvelopes; i++) {
    startPosNoise = pFrameInfo->bordersNoise[i];                move16();
    
    for(j=0; j<nEnvelopes; j++) {
      test();
      if(sub(pFrameInfo->borders[j], startPosNoise) == 0)
        break;
    }
    test();
    if(sub(j, nEnvelopes) == 0)
      return 0;
  }

  return 1;
}
