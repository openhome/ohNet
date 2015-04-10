/*
   hybrid filter bank
 */

#ifndef _HYBRID_H
#define _HYBRID_H

#include "ffr.h"
#include "sbr_const.h"


#define HYBRID_FILTER_LENGTH  13
#define HYBRID_FILTER_DELAY    6
#define NO_QMF_CHANNELS_IN_HYBRID   3
#define NO_HYBRID_CHANNELS_LOW     2
#define NO_HYBRID_CHANNELS_HIGH    8

typedef struct
{
  const Word16 *pResolution;
  Word8  qmfBufferMove;

  Word32 *pWorkReal;
  Word32 *pWorkImag;

  Word32 *mQmfBufferReal[NO_QMF_CHANNELS_IN_HYBRID];
  Word32 *mQmfBufferImag[NO_QMF_CHANNELS_IN_HYBRID];
  Word32 *mTempReal;
  Word32 *mTempImag;

} HYBRID;

typedef HYBRID *HANDLE_HYBRID;

void
HybridAnalysis ( const Word32 *mQmfReal,
                 const Word32 *mQmfImag,
                 Word32 *mHybridReal,
                 Word32 *mHybridImag,
                 HANDLE_HYBRID hHybrid,
                 Word16 scale);
void
HybridSynthesis ( const Word32 *mHybridReal,
                  const Word32 *mHybridImag,
                  Word32 *mQmfReal,
                  Word32 *mQmfImag,
                  HANDLE_HYBRID hHybrid );

int
CreateHybridFilterBank ( HANDLE_HYBRID hHybrid,
                         Word32 **pPtr);

#endif /* _HYBRID_H */

