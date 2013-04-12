/*
   QMF filtering
*/

#ifndef __QMF_DEC_H
#define __QMF_DEC_H


#include "sbr_scale.h"
#include "sbrdecsettings.h"
#include "intrinsics.h"

#ifndef MONO_ONLY
#include "ps_dec.h"
#endif

typedef struct
{
  Word16 no_channels;

  const Word16 *p_filter_ana;      /*!< Pointer to filter coefficients */

  const Word16 *p_filter;          /*!< Pointer to filter coefficients */

  Word16 *ralt_sin_twiddle;        /*!< dct twiddle factors (LP-SBR) */ 
  Word32 dctTempBuffer[64];        /*!< dct temp buffer  (LP-SBR)*/

#ifndef LP_SBR_ONLY
  const Word16 *cos_twiddle;       /*!< Twiddle factors */
  const Word16 *sin_twiddle;       /*!< Twiddle factors */
  const Word16 *alt_sin_twiddle;   /*!< Twiddle factors */
  
  const Word16 *t_cos;             /*!< Twiddle factors */
  const Word16 *t_sin;             /*!< Twiddle factors */
#endif

  Word16 *FilterStatesAna;         /*!< Pointer to buffer of filter states */
  Word16 *FilterStates;            /*!< Pointer to buffer of filter states */
  
  Word16 no_col;                   /*!< Number of time slots */

  Word16 lsb;                      /*!< sbr start subband */
  Word16 usb;                      /*!< sbr stop subband  */

  Word16 qmf_filter_state_size;
}
SBR_QMF_FILTER_BANK;

typedef SBR_QMF_FILTER_BANK *HANDLE_SBR_QMF_FILTER_BANK;

void 
cplxAnalysisQmfFiltering(const Word16 *timeIn,
                         SBR_SCALE_FACTOR  *sbrScaleFactor,
                         Word32 **qmfReal,
#ifndef LP_SBR_ONLY
                         Word32 **qmfImag,
#endif
                         HANDLE_SBR_QMF_FILTER_BANK qmfBank,
                         Flag bUseLP);

void 
cplxSynthesisQmfFiltering(Word32 **qmfReal,
#ifndef LP_SBR_ONLY
                          Word32 **qmfImag,
#endif
                          Word32 splitSlot,
                          SBR_SCALE_FACTOR *sbrScaleFactor,
                          Word16 *timeOut,
                          HANDLE_SBR_QMF_FILTER_BANK qmfBank,
#ifndef MONO_ONLY
                          HANDLE_PS_DEC hPS,
                          Flag active,
#endif
                          Flag bUseLP);

Word32
createCplxAnalysisQmfBank(HANDLE_SBR_QMF_FILTER_BANK h_sbrQmf,
                          SBR_SCALE_FACTOR  *sbrScaleFactor,
                          Word16 noCols,
                          Word16 usb,
                          Word16 chan);

Word32
createCplxSynthesisQmfBank(HANDLE_SBR_QMF_FILTER_BANK h_sbrQmf,
                           SBR_SCALE_FACTOR *sbrScaleFactor,
                           Word16 noCols,
                           Word16 lsb,
                           Word16 usb,
                           Word16 chan,
                           Flag bDownSample);



#endif
