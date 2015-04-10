/*
   declaration of constant tables
 */

#ifndef __SBR_ROM_H
#define __SBR_ROM_H


#include "ffr.h"
#include "sbrdecsettings.h" /* for MAXNRSBRCHANNELS */
#include "sbrdecoder.h"
#include "env_extr.h"
#include "qmf_dec.h"


#define INV_INT_TABLE_SIZE     49
#define SBR_NF_NO_RANDOM_VAL  512   /*!< Size of random number array for noise floor */

/*
  Frequency scales
*/
extern const Word8 sbr_start_freq_44[16];
extern const Word8 sbr_start_freq_16[16];
extern const Word8 sbr_start_freq_22[16];
extern const Word8 sbr_start_freq_24[16];
extern const Word8 sbr_start_freq_32[16];
extern const Word8 sbr_start_freq_48[16];

/*
  Envelope Adjustor
*/
extern const Word16  sbr_limGains_m[4];
extern const Word16   sbr_limGains_e[4];
extern const Word16  sbr_limiterBandsPerOctaveDiv4[4];
extern const Word16  sbr_smoothFilter[4];
extern const Word16  sbr_invIntTable[INV_INT_TABLE_SIZE];
#ifdef LP_SBR_ONLY
extern const Word16  sbr_randomPhase[SBR_NF_NO_RANDOM_VAL + MAX_FREQ_COEFFS];
#else
extern const Word32  sbr_randomPhase[SBR_NF_NO_RANDOM_VAL + MAX_FREQ_COEFFS];
#endif

/*
  QMF
*/
extern const Word16 sbr_qmf_64_640[QMF_FILTER_STATE_ANA_SIZE+2*NO_POLY];

extern const Word16 sbr_ralt_sin_twiddle_L64[];
extern const Word16 sbr_ralt_sin_twiddle_L32[];

#ifndef LP_SBR_ONLY
extern const Word16 sbr_cos_twiddle_L64[];
extern const Word16 sbr_sin_twiddle_L64[];
extern const Word16 sbr_alt_sin_twiddle_L64[];
extern const Word16 sbr_cos_twiddle_ds_L32[];
extern const Word16 sbr_sin_twiddle_ds_L32[];
extern const Word16 sbr_cos_twiddle_L32[];
extern const Word16 sbr_sin_twiddle_L32[];
extern const Word16 sbr_alt_sin_twiddle_L32[];
extern const Word16 sbr_t_cos_L32[];
extern const Word16 sbr_t_sin_L32[];
#endif
/*
  Envelope Extractor
*/
extern const FRAME_INFO sbr_frame_info1_16;
extern const FRAME_INFO sbr_frame_info2_16;
extern const FRAME_INFO sbr_frame_info4_16;
extern const FRAME_INFO sbr_frame_info8_16;

extern const SBR_HEADER_DATA sbr_defaultHeader;

extern const Word16 sbr_huffBook_EnvLevel10T[120];
extern const Word16 sbr_huffBook_EnvLevel10F[120];
extern const Word16 sbr_huffBook_EnvBalance10T[48];
extern const Word16 sbr_huffBook_EnvBalance10F[48];
extern const Word16 sbr_huffBook_EnvLevel11T[62];
extern const Word16 sbr_huffBook_EnvLevel11F[62];
extern const Word16 sbr_huffBook_EnvBalance11T[24];
extern const Word16 sbr_huffBook_EnvBalance11F[24];
extern const Word16 sbr_huffBook_NoiseLevel11T[62];
extern const Word16 sbr_huffBook_NoiseBalance11T[24];

/*
  Parametric stereo
*/
extern const Word16 p2_6[6];
extern const Word16 p8_13[13];
extern const Word16 pHybridResolution[];
#ifndef MONO_ONLY

extern const Word16 aRevLinkDecaySer[NO_SERIAL_ALLPASS_LINKS];
extern const Word16 aRevLinkDelaySer[];
extern const Word16 groupBorders[NO_IID_GROUPS + 1];
extern const Word16 groupShift[];
extern const Word16 aGroupToBin[NO_IID_GROUPS];
extern const Word16 aHybridToBin[SUBQMF_GROUPS];
extern const Word16 aDelayToBin[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorReQmf[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorImQmf[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorReSubQmf[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorImSubQmf[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorSerReQmf0[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorSerReQmf1[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorSerReQmf2[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorSerImQmf0[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorSerImQmf1[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorSerImQmf2[NO_QMF_ALLPASS_CHANNELS];
extern const Word16 aFractDelayPhaseFactorSerReSubQmf0[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorSerReSubQmf1[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorSerReSubQmf2[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorSerImSubQmf0[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorSerImSubQmf1[SUBQMF_GROUPS];
extern const Word16 aFractDelayPhaseFactorSerImSubQmf2[SUBQMF_GROUPS];
extern const Word16 *aaFractDelayPhaseFactorSerReQmf[3];
extern const Word16 *aaFractDelayPhaseFactorSerImQmf[3];
extern const Word16 *aaFractDelayPhaseFactorSerReSubQmf[3];
extern const Word16 *aaFractDelayPhaseFactorSerImSubQmf[3];
extern const Word16 scaleFactors[NO_IID_LEVELS];
extern const Word16 scaleFactorsFine[NO_IID_LEVELS_FINE];
extern const Word16 alphas[NO_ICC_LEVELS];
extern const Word16 aBookPsIidTimeDecode[28];
extern const Word16 aBookPsIidFreqDecode[28];
extern const Word16 aBookPsIccTimeDecode[14];
extern const Word16 aBookPsIccFreqDecode[14];
extern const Word16 aBookPsIidFineTimeDecode[60];
extern const Word16 aBookPsIidFineFreqDecode[60];
#endif /* MONO_ONLY */



#endif

