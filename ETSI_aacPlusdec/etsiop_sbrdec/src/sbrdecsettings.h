/*
   default Decoder Settings
 */

#ifndef _SBRDECSETTINGS_H
#define _SBRDECSETTINGS_H

/*
  Common
*/
#define SBR_UPSAMPLE_FAC        2 /*!< Upsampling Factor between core decoder and sbr decoder */

/* Set MAX_FRAME_SIZE to the largest value of all supported BSFORMATs
   by overriding MAX_FRAME_SIZE in the correct order: */
#define MAX_FRAME_SIZE       1024 /*!< Maximum supported frame size of input time signal */


/*
  QMF
*/
#define QMF_FILTER_STATE_SYN_SIZE 1280/*!< Number of qmf synthesis filter taps, speed optimized */
#define QMF_FILTER_STATE_ANA_SIZE 320 /*!< Number of qmf analysis filter taps */
#define NO_SYNTHESIS_CHANNELS      64 /*!< Number of qmf synthesis channels */
#define NO_ANALYSIS_CHANNELS   (NO_SYNTHESIS_CHANNELS / SBR_UPSAMPLE_FAC) /*!< Number of qmf analysis channels */
#define NO_POLY                (QMF_FILTER_STATE_ANA_SIZE / (2*NO_ANALYSIS_CHANNELS)) /*! Number of polyphase filter taps */

#define NO_SYNTHESIS_CHANNELS_DOWN_SAMPLED     (NO_SYNTHESIS_CHANNELS/2)
#define QMF_FILTER_STATE_SYN_SIZE_DOWN_SAMPLED (QMF_FILTER_STATE_SYN_SIZE/2)

/*
  Frequency scales
*/
#define CALC_STOP_BAND            /*!< Defining makes the stop_freq-tables obsolete but needs some additional processing time (e.g. #sbr_stop_freq_44) */


/*
  Env-Adjust
*/
#define MAX_NOISE_ENVELOPES      2
#define MAX_NOISE_COEFFS         5
#define MAX_NUM_NOISE_VALUES     (MAX_NOISE_ENVELOPES * MAX_NOISE_COEFFS)
#define MAX_NUM_LIMITERS        12

#define MAX_ENVELOPES           5

#define MAX_FREQ_COEFFS         48
#define MAX_FREQ_COEFFS_FS44100 35
#define MAX_FREQ_COEFFS_FS48000 32

#define SBR_TIME_STEP            2

#define MAX_NUM_ENVELOPE_VALUES (MAX_ENVELOPES * MAX_FREQ_COEFFS)

#define MAX_GAIN_EXP            34
/* Maximum gain will be sqrt(0.5 * 2^MAX_GAIN_EXP)
   example: 34=99dB   */


/*
  LPP Transposer
*/

#define LPC_ORDER       2

#define MAX_INVF_BANDS          MAX_NOISE_COEFFS


/*
  Derived from above defines
*/
#define MAX_COLS               (MAX_FRAME_SIZE / NO_ANALYSIS_CHANNELS) /*!< Maximum number of QMF timeslots for one frame */
#define MAX_OV_COLS            6
#define MAX_ENV_COLS           (MAX_COLS + MAX_OV_COLS) /*!< Maximum number of QMF timeslots spanned by the envelopes of one frame */

#define SBR_TIME_SLOTS         (MAX_COLS / SBR_TIME_STEP)
#define SBR_OV_SLOTS           (MAX_OV_COLS / SBR_TIME_STEP)

#endif
