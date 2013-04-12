/*
   Envelope calculation prototypes
 */
#ifndef __ENV_CALC_H
#define __ENV_CALC_H


#include "env_extr.h"  /* for HANDLE_SBR_HEADER_DATA */
#include "ffr.h"
#include "sbr_scale.h"
#include "sbrdecsettings.h"

typedef struct
{
  Word16 *filtBuffer_m;      /*!< Mantissas of previous gains (required for smoothing) */
  Word16 *filtBufferNoise_m; /*!< Mantissas of previous noise levels (required for smoothing) */
  Word16 *filtBuffer_e;      /*!< Exponents of previous gains */
  Word16  filtBufferNoise_e; /*!< Common exponent of previous noise levels */

  Flag startUp;              /*!< flag to signal initial conditions in buffers */
  Word16 phaseIndex;         /*!< Index for randomPase array */
  Word16 prevTranEnv;        /*!< The transient envelope of the previous frame. */

  Flag harmFlagsPrev[(MAX_FREQ_COEFFS+15)/16]; 
  /*!< Words with 16 flags each indicating where a sine was added in the previous frame.*/
  Word16 harmIndex;           /*!< Current phase of synthetic sine */

}
SBR_CALCULATE_ENVELOPE;

typedef SBR_CALCULATE_ENVELOPE *HANDLE_SBR_CALCULATE_ENVELOPE;



void 
calculateSbrEnvelope (SBR_SCALE_FACTOR  *sbrScaleFactor,
                      HANDLE_SBR_CALCULATE_ENVELOPE h_sbr_cal_env,
                      HANDLE_SBR_HEADER_DATA hHeaderData,
                      HANDLE_SBR_FRAME_DATA hFrameData,
                      HANDLE_SBR_PREV_FRAME_DATA hPrevFrameData,
                      Word32 **analysBufferReal_m,
#ifndef LP_SBR_ONLY
                      Word32 **analysBufferImag_m,
#endif
                      Word16 *degreeAlias,
                      Flag bUseLP
                      );

Word16
createSbrEnvelopeCalc (HANDLE_SBR_CALCULATE_ENVELOPE hSbrCalculateEnvelope,
                       HANDLE_SBR_HEADER_DATA hHeaderData,
                       Word16 chan);

void
resetSbrEnvelopeCalc (HANDLE_SBR_CALCULATE_ENVELOPE hCalEnv);

Word16
ResetLimiterBands ( Word16 *limiterBandTable,
                    Word16 *noLimiterBands,
                    Word16 *freqBandTable,
                    Word16 noFreqBands,
                    const PATCH_PARAM *patchParam,
                    Word16 noPatches,
                    Word16 limiterBands);

void rescaleSubbandSamples(Word32 ** re,
#ifndef LP_SBR_ONLY
                           Word32 ** im,
#endif
                           Word16 lowSubband, Word16 noSubbands,
                           Word16 start_pos,  Word16 next_pos,
                           Word16 shift,
                           Flag bUseLP);

Word16 expSubbandSamples( Word32 ** analysBufferReal_m,
#ifndef LP_SBR_ONLY
                          Word32 ** analysBufferImag_m,
#endif
                          Word16 lowSubband,
                          Word16 highSubband,
                          Word16 start_pos,
                          Word16 stop_pos,
                          Flag bUseLP);

#endif
