/*
   SBR main functions
 */

#ifndef __SBR_DEC_H
#define __SBR_DEC_H


#include "sbr_const.h"
#include "lpp_tran.h"
#include "qmf_dec.h"
#include "env_calc.h"

typedef struct
{
  Word32 * ptrsbr_OverlapBuffer;
  
  SBR_QMF_FILTER_BANK     CodecQmfBank;
  SBR_QMF_FILTER_BANK     SynthesisQmfBank;
  SBR_CALCULATE_ENVELOPE  SbrCalculateEnvelope;
  SBR_LPP_TRANS           LppTrans;

  SBR_SCALE_FACTOR        sbrScaleFactor;

  Word8                   qmfLpChannel;
  Flag                    bApplyQmfLp;
}
SBR_DEC;

typedef SBR_DEC *HANDLE_SBR_DEC;


typedef struct
{
  HANDLE_SBR_PREV_FRAME_DATA hPrevFrameData;
  SBR_DEC SbrDec;
}
SBR_CHANNEL;


void sbr_dec (HANDLE_SBR_DEC hSbrDec,
              Word16 *timeData,
              HANDLE_SBR_HEADER_DATA hHeaderData,
              HANDLE_SBR_FRAME_DATA hFrameData,
              HANDLE_SBR_PREV_FRAME_DATA hPrevFrameData,
#ifndef MONO_ONLY
              HANDLE_PS_DEC hPS,
              SBR_QMF_FILTER_BANK *hSynthesisQmfBankRight,
              SBR_SCALE_FACTOR *sbrScaleFactorRight,
#endif
              Flag applyProcessing,
              Flag bUseLP);
     
Word16
createSbrDec (SBR_CHANNEL * hSbrChannel,
              HANDLE_SBR_HEADER_DATA hHeaderData,
              Word16 chan,
              Flag bDownSample,
              Flag  bApplyQmfLp,
              Word32 sampleRate);

Word8
resetSbrDec (HANDLE_SBR_DEC hSbrDec,
             HANDLE_SBR_HEADER_DATA hHeaderData,
             Flag bUseLP);



#endif
