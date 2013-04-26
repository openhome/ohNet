//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifdef SCRAMBLE_GLOBAL_SYMBOL_NAMES
#include "scramble.h"
#endif

#include "wmacommon.h"
#include "wmachmtx.h"
#include "wmamalloc.h"
#include "wmawfxdefs.h"
#include "wmaassert.h"

#include "math.h"

#define CHECK_ALLOC(p) if (!(p)) { wmar = WMA_E_OUTOFMEMORY; goto lerror; }
#define PI 3.1415926535

// sort in ascending order
static Void BubbleSort(F32UP *rgfltInp, I32UP *rgiInMap, I32UP cNum)
{
  I32UP i, iChanged;

#define RSBSWAP(type, x, y) { \
  type rsb_temp; \
  rsb_temp = x; \
  x = y; \
  y = rsb_temp; \
}

  while (1) {
    iChanged = 0;
    for(i = 0; i < cNum-1; i++) {
      if (rgfltInp[i] > rgfltInp[i+1]) {
        RSBSWAP(F32UP, rgfltInp[i], rgfltInp[i+1]);
        RSBSWAP(I32UP, rgiInMap[i], rgiInMap[i+1]);
        iChanged = 1;
      }
    }
    if (iChanged == 0) break;
  }

#undef RSBSWAP
}

Void FixAnglesForSideBackAmbiguity(U32 uSrcMask, U32 uDstMask,
                                   F32UP *pfltSpeakerDirection,
                                   Int iNumSpeakerPos)
{
  Int i, j;

  // adjust masks to take care of ambiguity between backLR / sideLR
  // from JJ's notes:
  // For ambiguity between sideLR and backLR when only one of them exists in both input and output formats, we MUST pass them directly through. That's the only case that we do this for
  if (( (uSrcMask & SPEAKER_BACK_LEFT) &&
       !(uSrcMask & SPEAKER_SIDE_LEFT) &&
        (uDstMask & SPEAKER_SIDE_LEFT) &&
       !(uDstMask & SPEAKER_BACK_LEFT)) ||
      ( (uSrcMask & SPEAKER_SIDE_LEFT) &&
       !(uSrcMask & SPEAKER_BACK_LEFT) &&
        (uDstMask & SPEAKER_BACK_LEFT) &&
       !(uDstMask & SPEAKER_SIDE_LEFT)))
  {
    // make both side left and back left angles the same, so pass through
    // occurs
    for (i=0; i < iNumSpeakerPos; i++)
      if ((1<<i) == SPEAKER_SIDE_LEFT)
        break;
    for (j=0; j < iNumSpeakerPos; j++)
      if ((1<<j) == SPEAKER_BACK_LEFT)
        break;
    assert(iNumSpeakerPos != i && iNumSpeakerPos != j);
    pfltSpeakerDirection[i] = pfltSpeakerDirection[j];
  }

  if (( (uSrcMask & SPEAKER_BACK_RIGHT) &&
       !(uSrcMask & SPEAKER_SIDE_RIGHT) &&
        (uDstMask & SPEAKER_SIDE_RIGHT) &&
       !(uDstMask & SPEAKER_BACK_RIGHT)) ||
      ( (uSrcMask & SPEAKER_SIDE_RIGHT) &&
       !(uSrcMask & SPEAKER_BACK_RIGHT) &&
        (uDstMask & SPEAKER_BACK_RIGHT) &&
       !(uDstMask & SPEAKER_SIDE_RIGHT)))
  {
    // make both side right and back right angles the same, so pass through
    // occurs
    for (i=0; i < iNumSpeakerPos; i++)
      if ((1<<i) == SPEAKER_SIDE_RIGHT)
        break;
    for (j=0; j < iNumSpeakerPos; j++)
      if ((1<<j) == SPEAKER_BACK_RIGHT)
        break;
    assert(iNumSpeakerPos != i && iNumSpeakerPos != j);
    pfltSpeakerDirection[i] = pfltSpeakerDirection[j];
  }
}

#define MIXMTX(i, j) fltMixMtx[i*cSrcChannels + j]

#define RsC float
#define SetMixFromAngles SetMixFromAnglesF
#define SetMixFromChannelMask SetMixFromChannelMaskF
#define NormalizeMixMtx NormalizeMixMtxF
#include "chmtxtemplate.c"
#undef SetMixFromAngles
#undef SetMixFromChannelMask
#undef NormalizeMixMtx
#undef RsC

#define RsC double
#define SetMixFromAngles SetMixFromAnglesD
#define SetMixFromChannelMask SetMixFromChannelMaskD
#define NormalizeMixMtx NormalizeMixMtxI
#include "chmtxtemplate.c"
#undef SetMixFromAngles
#undef SetMixFromChannelMask
#undef NormalizeMixMtx
#undef RsC

WMARESULT SetMixFromChannelMaskI(I32UP cSrcChannels, I32UP cDstChannels,
                                U32 srcMask, U32 dstMask, int *rgiMixMtx)
{
    return WMA_E_NOTSUPPORTED;
}

