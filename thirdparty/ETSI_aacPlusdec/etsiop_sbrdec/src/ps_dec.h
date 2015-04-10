/*
   parametric stereo decoding
 */

#ifndef __PS_DEC_H
#define __PS_DEC_H

#include "sbrdecoder.h"
#include "hybrid.h"
#include "sbrdecsettings.h"
#include "sbr_scale.h"
#include "intrinsics.h"
#include "typedef.h"


#define MAX_NUM_COL                 32
#define NO_SUB_QMF_CHANNELS         12
#define NO_QMF_CHANNELS             64
#define NO_ALLPASS_CHANNELS         23
#define NO_DELAY_CHANNELS           (NO_QMF_CHANNELS-NO_ALLPASS_CHANNELS)
#define DELAY_ALLPASS               2
#define SHORT_DELAY_START           12
#define SHORT_DELAY                 1
#define LONG_DELAY                  14
#define MAX_REV_LINK_DELAY          5
#define NO_QMF_ALLPASS_CHANNELS    (NO_ALLPASS_CHANNELS-NO_QMF_CHANNELS_IN_HYBRID)
#define NO_QMF_ICC_CHANNELS        (NO_QMF_ALLPASS_CHANNELS+NO_DELAY_CHANNELS)
#define HYBRIDGROUPS                8
#define DECAY_CUTOFF                3
#define DECAY_SLOPE                 0x0666
#define PEAK_DECAY_FACTOR           0x620a
#define NO_SERIAL_ALLPASS_LINKS     3
#define MAX_NO_PS_ENV               5
#define PSC_SQRT05F                     ( 0x5a82 ) /* 1.0/1.41421356237309504880 */
#define NO_BINS                         ( 20 )
#define NO_HI_RES_BINS                  ( 34 )
#define NO_LOW_RES_BINS                 ( NO_IID_BINS / 2 )
#define NO_IID_BINS                     ( NO_BINS )
#define NO_ICC_BINS                     ( NO_BINS )
#define NO_LOW_RES_IID_BINS             ( NO_LOW_RES_BINS )
#define NO_LOW_RES_ICC_BINS             ( NO_LOW_RES_BINS )
#define SUBQMF_GROUPS                   ( 10 )
#define QMF_GROUPS                      ( 12 )
#define NO_IID_GROUPS                   ( SUBQMF_GROUPS + QMF_GROUPS )
#define NO_IID_STEPS                    ( 7 )  /* 1 .. +7 */
#define NO_IID_STEPS_FINE               ( 15 ) /* 1 .. +15 */
#define NO_ICC_STEPS                    ( 8 )
#define NO_IID_LEVELS                   ( 2 * NO_IID_STEPS + 1 )       /* -7 .. +7 */
#define NO_IID_LEVELS_FINE              ( 2 * NO_IID_STEPS_FINE + 1 ) /* -15 .. +15 */
#define NO_ICC_LEVELS                   ( NO_ICC_STEPS )

/****************************************************************
  Type definitions
 ****************************************************************/

/*! Every entry of the array points to a delay buffer allocated by InitPsScale(). */
typedef Word16* REVERB_BUFFERS[NO_SERIAL_ALLPASS_LINKS][MAX_REV_LINK_DELAY];

typedef struct {
  Flag bForceMono;

  Word16 delay_buffer_scale;                          /*!< Common scale of subband samples in the delay buffer */
  Word16  usb;                                        /*!< Uppermost QMF subband + 1 */

  Word16 aIidPrevFrameIndex[NO_HI_RES_BINS];          /*!< IID index of the previous frame */
  Word16 aIccPrevFrameIndex[NO_HI_RES_BINS];          /*!< ICC index of the previous frame */

  Flag bPsDataAvail;                                  /*!< Set if new data available from bitstream */

  Flag bEnableIid;                                    /*!< Use Interchannel-Intensity-Difference */
  Flag bEnableIcc;                                    /*!< Use Interchannel-Coherence */

  Flag bEnableExt;                                    /*!< Reserved flag for future extensions */

  Word16 freqResIid;                                  /*!< Selects 3 frequency resolutions and fine/coarse quantization for IID */
  Word16 freqResIcc;
  Flag bFineIidQ;                                     /*!< Use fine Iid quantisation. */

  Flag bFrameClass;                                   /*!< Type of time grid */
  Word16 noEnv;                                       /*!< Number of envelopes (parameter sets) in current frame */
  Word16 aEnvStartStop[MAX_NO_PS_ENV+2];              /*!< Start and stop position in time for each envelope */

  Flag abIidDtFlag[MAX_NO_PS_ENV];                    /*!< Flags deltacoding in time/freq flag for IID, 0 => freq */
  Flag abIccDtFlag[MAX_NO_PS_ENV];                    /*!< Flags deltacoding in time/freq flag for ICC, 0 => freq */

  Word16 aaIidIndex[MAX_NO_PS_ENV+2][NO_HI_RES_BINS]; /*!< The IID index for all envelopes and all IID bins */
  Word16 aaIccIndex[MAX_NO_PS_ENV+2][NO_HI_RES_BINS]; /*!< The ICC index for all envelopes and all ICC bins */

  Word16 delayBufIndex;                               /*!< Pointer to where the latest sample is in buffer */
  Word16 delayBufIndexLong;

  Word16 *aaRealDelayBufferQmf[NO_QMF_ICC_CHANNELS];  /*!< Real part delay buffer */
  Word16 *aaImagDelayBufferQmf[NO_QMF_ICC_CHANNELS];  /*!< Imaginary part delay buffer */

  Word16 *aaRealDelayBufferSubQmf[SUBQMF_GROUPS];
  Word16 *aaImagDelayBufferSubQmf[SUBQMF_GROUPS];

  Word16 aDelayRBufIndexSer[NO_SERIAL_ALLPASS_LINKS];
  Word16 aNoSampleDelayRSer[NO_SERIAL_ALLPASS_LINKS];

  REVERB_BUFFERS aaaRealDelayRBufferSerQmf;
  REVERB_BUFFERS aaaImagDelayRBufferSerQmf;

  REVERB_BUFFERS aaaRealDelayRBufferSerSubQmf;
  REVERB_BUFFERS aaaImagDelayRBufferSerSubQmf;

  Word32 *aPeakDecayFast;
  Word32 *aPrevNrg;
  Word32 *aPrevPeakDiff;

  Word32 *mHybridRealLeft;
  Word32 *mHybridImagLeft;
  Word32 *mHybridRealRight;
  Word32 *mHybridImagRight;

  HYBRID hybrid;

  Word16 h11Prev[NO_IID_GROUPS];
  Word16 h12Prev[NO_IID_GROUPS];
  Word16 h21Prev[NO_IID_GROUPS];
  Word16 h22Prev[NO_IID_GROUPS];

  Word16 H11[NO_IID_GROUPS];
  Word16 H12[NO_IID_GROUPS];
  Word16 H21[NO_IID_GROUPS];
  Word16 H22[NO_IID_GROUPS];

  Word16 deltaH11[NO_IID_GROUPS];
  Word16 deltaH12[NO_IID_GROUPS];
  Word16 deltaH21[NO_IID_GROUPS];
  Word16 deltaH22[NO_IID_GROUPS];
}
PS_DEC;

typedef PS_DEC *HANDLE_PS_DEC;

/****************************************************************
  Functions
 ****************************************************************/
int
CreatePsDec(HANDLE_PS_DEC h_ps_dec);

void
InitPsScale(HANDLE_PS_DEC hPS,
            SBR_SCALE_FACTOR  *sbrScaleFactor);
                      
void
InitRotationEnvelope(HANDLE_PS_DEC h_ps_dec,
                     Word16 env,
                     Word16 usb);
void
ApplyPsSlot(HANDLE_PS_DEC h_ps_dec,
            Word32 **rBufferLeft,
            Word32 **iBufferLeft,
            Word32 *rBufferRight,
            Word32 *iBufferRight, 
            SBR_SCALE_FACTOR  *sbrScaleFactor,
            Word16 slot,                         
            Word16 lsb);
#endif
