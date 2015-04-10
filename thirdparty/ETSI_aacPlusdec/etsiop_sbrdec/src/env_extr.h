/*
   envelope extraction prototypes
 */

#ifndef __ENVELOPE_EXTRACTION_H
#define __ENVELOPE_EXTRACTION_H


#include "sbr_const.h"
#include "FFR_bitbuffer.h"
#include "sbrdecoder.h"
#include "ffr.h"
#include "sbrdecsettings.h"
#include "lpp_tran.h"

#ifndef MONO_ONLY
#include "ps_dec.h"
#endif


#define ENV_EXP_FRACT 0
/*!< Can be set to 8 instead of 0 to enhance accuracy during concealment.  */

#define EXP_BITS 6
/*!< Size of exponent-part of a pseudo float envelope value (should be at least 6).
  The remaining bits in each word are used for the mantissa (should be at least 10).  */

#define MASK_M (((1 << (SHORT_BITS - EXP_BITS)) - 1) << EXP_BITS)  /*!< Mask for extracting the mantissa of a pseudo float envelope value */
#define MASK_E ((1 << EXP_BITS) - 1)           /*!< Mask for extracting the exponent of a pseudo float envelope value */

#define SIGN_EXT ( ((char)-1) ^ MASK_E)        /*!< a char-constant with all bits above our sign-bit set */
#define ROUNDING ( 1<<(EXP_BITS-1) )           /*!< 0.5-offset for rounding the mantissa of a pseudo-float envelope value */
#define NRG_EXP_OFFSET  16                     /*!< Will be added to the reference energy's exponent to prevent negative numbers */
#define NOISE_EXP_OFFSET  38                   /*!< Will be added to the noise level exponent to prevent negative numbers */

typedef const Word16 *Huffman;

typedef enum
{
  HEADER_OK,
  HEADER_RESET,
  CONCEALMENT,
  HEADER_NOT_INITIALIZED  
}
SBR_HEADER_STATUS;

typedef enum
{
  SBR_NOT_INITIALIZED,
  UPSAMPLING,
  SBR_ACTIVE
}
SBR_SYNC_STATE;


typedef enum
{
  COUPLING_OFF,
  COUPLING_LEVEL,
  COUPLING_BAL
}
COUPLING_MODE;

typedef enum
{
  UNDEFINED_CHANNEL_MODE,
  MONO,
  STEREO
#ifndef MONO_ONLY
  ,PS_STEREO
#endif
}
CHANNEL_MODE;


typedef struct
{
  Word16 nSfb[2];           /*!< Number of SBR-bands for low and high freq-resolution */
  Word16 nNfb;              /*!< Actual number of noise bands to read from the bitstream*/
  Word16 numMaster;         /*!< Number of SBR-bands in v_k_master */
  Word16 lowSubband;        /*!< QMF-band where SBR frequency range starts */
  Word16 highSubband;       /*!< QMF-band where SBR frequency range ends */
  Word16 limiterBandTable[MAX_NUM_LIMITERS+1]; /*!< Limiter band table. */
  Word16 noLimiterBands;    /*!< Number of limiter bands. */  
  Word16 nInvfBands;        /*!< Number of bands for inverse filtering */
  Word16 *freqBandTable[2]; /*!< Pointers to freqBandTableLo and freqBandTableHi */
  Word16 freqBandTableLo[MAX_FREQ_COEFFS/2+1];
                                   /*!< Mapping of SBR bands to QMF bands for low frequency resolution */
  Word16 freqBandTableHi[MAX_FREQ_COEFFS+1];
                                   /*!< Mapping of SBR bands to QMF bands for high frequency resolution */
  Word16 freqBandTableNoise[MAX_NOISE_COEFFS+1];
                                   /*!< Mapping of SBR noise bands to QMF bands */
  Word16 v_k_master[MAX_FREQ_COEFFS+1];
                                   /*!< Master BandTable which freqBandTable is derived from */
}
FREQ_BAND_DATA;

typedef FREQ_BAND_DATA *HANDLE_FREQ_BAND_DATA;

typedef struct
{
  SBR_SYNC_STATE syncState;  /*!< The current initialization status of the header */
  Flag frameErrorFlag;       /*!< Current frame data valid ? */
  Flag prevFrameErrorFlag;   /*!< Previous frame data valid ? */
  Word16 numberTimeSlots;   
  Word16 timeStep;           /*!< Time resolution of SBR in QMF-slots */
  Word16 codecFrameSize;     /*!< Core coder frame size in samples */
  Word32 outSampleRate;      /*!< Output sampling frequency */

  /* Changes in these variables causes concealment */
  CHANNEL_MODE  channelMode;         /*!< Mono, pseudo-stereo or stereo */
  Word16 ampResolution;       /*!< Amplitude resolution of envelope values (0: 1.5dB, 1: 3dB) */

  /* Changes in these variables causes a reset of the decoder */
  Word16 startFreq;           /*!< Index for SBR start frequency */
  Word16 stopFreq;            /*!< Index for SBR highest frequency */
  Word16 xover_band;          /*!< Start index in #v_k_master[] used for dynamic crossover frequency */
  Word16 freqScale;           /*!< 0: linear scale,  1-3 logarithmic scales */
  Word16 alterScale;          /*!< Flag for coarser frequency resolution */
  Word16 noise_bands;         /*!< Noise bands per octave, read from bitstream*/

  /* don't require reset */
  Word16 limiterBands;        /*!< Index for number of limiter bands per octave */
  Word16 limiterGains;        /*!< Index to select gain limit */
  Word16 interpolFreq;        /*!< Select gain calculation method (1: per QMF channel, 0: per SBR band) */
  Word16 smoothingLength;     /*!< Smoothing of gains over time (0: on  1: off) */
  HANDLE_FREQ_BAND_DATA hFreqBandData;  /*!< Pointer to struct #FREQ_BAND_DATA */
}
SBR_HEADER_DATA;

typedef SBR_HEADER_DATA *HANDLE_SBR_HEADER_DATA;


typedef struct
{
  Word16 frameClass;               /*!< Select grid type */
  Word16 nEnvelopes;               /*!< Number of envelopes */
  Word16 borders[MAX_ENVELOPES+1]; /*!< Envelope borders (in SBR-timeslots, e.g. mp3PRO: 0..11) */
  Word16 freqRes[MAX_ENVELOPES];   /*!< Frequency resolution for each envelope (0=low, 1=high) */
  Word16 tranEnv;                  /*!< Transient envelope, -1 if none */
  Word16 nNoiseEnvelopes;          /*!< Number of noise envelopes */
  Word16 bordersNoise[MAX_NOISE_ENVELOPES+1];/*!< borders of noise envelopes */
}
FRAME_INFO;


typedef struct
{
  Word16  sfb_nrg_prev[MAX_FREQ_COEFFS];  /*!< Previous envelope (required for differential-coded values) */
  Word16  prevNoiseLevel[MAX_NOISE_COEFFS]; /*!< Previous noise envelope (required for differential-coded values) */
  Word16 ampRes;                  /*!< Previous amplitude resolution (0: 1.5dB, 1: 3dB) */
  Word16 stopPos;                 /*!< Position in time where last envelope ended */
  Word16 maxQmfSubbandAac;        /*!< Solves the 'undefined x-over problem' for the enhancement */
  COUPLING_MODE coupling;                /*!< Stereo-mode of previous frame */
  INVF_MODE sbr_invf_mode[MAX_INVF_BANDS]; /*!< Previous strength of filtering in transposer */
}
SBR_PREV_FRAME_DATA;

typedef SBR_PREV_FRAME_DATA *HANDLE_SBR_PREV_FRAME_DATA;


typedef struct
{
  Word16 nScaleFactors;                    /*!< total number of scalefactors in frame */

  FRAME_INFO frameInfo;                 /*!< time grid for current frame */
  Word16 domain_vec[MAX_ENVELOPES];  /*!< Bitfield containing direction of delta-coding for each envelope (0:frequency, 1:time) */
  Word16 domain_vec_noise[MAX_NOISE_ENVELOPES]; /*!< Same as above, but for noise envelopes */

  INVF_MODE sbr_invf_mode[MAX_INVF_BANDS]; /*!< Strength of filtering in transposer */
  COUPLING_MODE coupling;               /*!< Stereo-mode */
  Word16 ampResolutionCurrentFrame;        /*!< Amplitude resolution of envelope values (0: 1.5dB, 1: 3dB) */

  Flag addHarmonics[MAX_FREQ_COEFFS];   /*!< Flags for synthetic sine addition */
  Word16 maxQmfSubbandAac;       /*!< Solves the 'undefined x-over problem' for the enhancement */

  Word16 iEnvelope[MAX_NUM_ENVELOPE_VALUES];       /*!< Envelope data */
  Word16 sbrNoiseFloorLevel[MAX_NUM_NOISE_VALUES]; /*!< Noise envelope data */
}
SBR_FRAME_DATA;

typedef SBR_FRAME_DATA *HANDLE_SBR_FRAME_DATA;


void initSbrPrevFrameData (HANDLE_SBR_PREV_FRAME_DATA h_prev_data,
                           Word16 timeSlots);

Word8  sbrGetSingleChannelElement (HANDLE_SBR_HEADER_DATA hHeaderData,
                                   HANDLE_SBR_FRAME_DATA  hFrameData,
#ifndef MONO_ONLY
                                   HANDLE_PS_DEC hPS,
#endif
                                   HANDLE_BIT_BUF hBitBuf);
Word8  sbrGetChannelPairElement (HANDLE_SBR_HEADER_DATA hHeaderData,
                                 HANDLE_SBR_FRAME_DATA hFrameDataLeft,
                                 HANDLE_SBR_FRAME_DATA hFrameDataRight,
                                 HANDLE_BIT_BUF hBitBuf);

SBR_HEADER_STATUS
sbrGetHeaderData (SBR_HEADER_DATA *h_sbr_header,
                  HANDLE_BIT_BUF hBitBuf,
                  Flag stereoFlag);

void
initHeaderData  (SBR_HEADER_DATA *headerData,
                 Word32 sampleRate,
                 Word16 samplesPerFrame);

Word16
decode_huff_cw (Huffman h,
                HANDLE_BIT_BUF hBitBuf);


#endif
