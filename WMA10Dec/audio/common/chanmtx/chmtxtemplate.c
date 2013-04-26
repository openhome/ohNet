//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

// Speaker direction in degrees: all must be +ve, between 0 & 360.
// Else will get ignored.
static WMARESULT SetMixFromAngles(I32UP cSrcChannels, I32UP cDstChannels,
                           F32UP *fltSrcAngles, F32UP *fltDstAngles,
                           RsC *fltMixMtx)
{
  WMARESULT wmar = WMA_OK;
  I32UP *iSrcMap=NULL, *iDstMap=NULL;
  I32UP i, j, k1, k2, startSrc, startDst, cActDstChannels;
  F32UP d1, dt, c1, c2;
  F32UP *fltDstScale = NULL;

  iSrcMap = (I32UP*)auMalloc(cSrcChannels*sizeof(I32UP));
  CHECK_ALLOC(iSrcMap);
  iDstMap = (I32UP*)auMalloc(cDstChannels*sizeof(I32UP));
  CHECK_ALLOC(iDstMap);
  fltDstScale = (F32UP*)auMalloc(cDstChannels*sizeof(F32UP));
  CHECK_ALLOC(fltDstScale);

#define NORMANG(ang) ((ang) - floor((ang)/360.0f)*360.0f)

  // Sort the angles with map
  for (i=0; i < cSrcChannels; i++) iSrcMap[i] = i;
  for (i=0; i < cDstChannels; i++) iDstMap[i] = i;
  BubbleSort(fltSrcAngles, iSrcMap, cSrcChannels);
  BubbleSort(fltDstAngles, iDstMap, cDstChannels);
  startSrc = cSrcChannels;
  startDst = cDstChannels;
  for (i=0; i < cSrcChannels; i++)
    if (fltSrcAngles[i] >= 0.0f) { startSrc = i;  break; }
  for (i=0; i < cDstChannels; i++)
    if (fltDstAngles[i] >= 0.0f) { startDst = i;  break; }
  cActDstChannels = cDstChannels - startDst;

  for (i=0; i < cDstChannels; i++) {
    fltDstScale[i] = 0.0f;
    for (j=0; j < cSrcChannels; j++) {
      MIXMTX(i, j) = (RsC)0.0f;
    }
  }

  // if no valid destination channels present, simply return
  if (cActDstChannels <= 0) {
    WMAASSERT(startDst == cDstChannels);
    goto lerror;
  }

  // Ignore (-) angle channels
  for (i=startSrc; i < cSrcChannels; i++) {
    // Find which output channels are affected by this source channel
    for (j=startDst; j < cDstChannels; j++) {
      if (fltSrcAngles[i] <= fltDstAngles[j]) break;
    }
    // j-startDst between 0 and cActDstChannels-1
    // j-startDst-1 between -1 and cActDstChannels-2, so add cActDstChannels
    k2 = j-startDst;
    k1 = j-1-startDst+cActDstChannels;
    k2 = (k2 % cActDstChannels) + startDst;
    k1 = (k1 % cActDstChannels) + startDst;
    dt = (F32UP) NORMANG(fltDstAngles[k2]-fltDstAngles[k1]);
    d1 = (F32UP) NORMANG(fltSrcAngles[i]-fltDstAngles[k1]);
    // want c1^2 + c2^2 = 1, so c1 = cos(d1*pi/2), c2 = sin(d1*pi/2)
    if (k1 == k2) { // only one dst angle
      MIXMTX(iDstMap[k1], iSrcMap[i]) = (RsC)1.0f;
      fltDstScale[iDstMap[k1]] += 1.0f;
    } else {
      if (dt == 0.0f) {
        WMAASSERT(!"Angles too close together");
        wmar = WMA_E_INVALIDARG;
        goto lerror;
      }
      c1 = (F32UP)cos(d1/dt*PI/2.0);
      if (c1 < 0.0f) c1 = 0.0f;
      c2 = (F32UP)sin(d1/dt*PI/2.0);
      if (c2 < 0.0f) c2 = 0.0f;
      if (cDstChannels == 1) c1 = c2 = 1.0f;
      MIXMTX(iDstMap[k1], iSrcMap[i]) = (RsC)c1;
      MIXMTX(iDstMap[k2], iSrcMap[i]) = (RsC)c2;
      fltDstScale[iDstMap[k1]] += c1;
      fltDstScale[iDstMap[k2]] += c2;
    }
  }

#undef NORMANG

lerror:
  auFree(iSrcMap);
  auFree(iDstMap);
  auFree(fltDstScale);
  return wmar;
}

Void NormalizeMixMtx(I32UP cSrcChannels, I32UP cDstChannels,
                     RsC *fltMixMtx)
{
  I32UP i, j;
  F32UP fltDstScale, fltMaxScale;

  fltMaxScale = (F32UP)0;
  for (i=0; i < cDstChannels; i++) {
    fltDstScale = 0;
    for (j=0; j < cSrcChannels; j++) {
      fltDstScale += (F32UP)MIXMTX(i, j);
    }
    if (fltDstScale > fltMaxScale)
      fltMaxScale = (F32UP)fltDstScale;
  }
  if ((F32UP)0 == fltMaxScale)
    return;
  for (i=0; i < cDstChannels; i++) {
    for (j=0; j < cSrcChannels; j++) {
      MIXMTX(i, j) = MIXMTX(i, j) / (RsC)fltMaxScale;
      // limit the precision
      MIXMTX(i, j) = (RsC)((I32UP)(1000.0f*MIXMTX(i, j) + 0.5f))/1000.0f;
    }
  }
}

WMARESULT SetMixFromChannelMask(I32UP cSrcChannels, I32UP cDstChannels,
                                U32 srcMask, U32 dstMask, RsC *fltMixMtx)
{
  WMARESULT wmar = WMA_OK;
  I32UP i, j, cSrcCh, cDstCh;
  U32 mask;

  // Speaker direction in degrees: all must be +ve, between 0 & 360.
#define SPEAKER_POS (11)
  F32UP rgfltSpeakerDirection[SPEAKER_POS] = {
    -30.0f + 360.0f,  // SPEAKER_FRONT_LEFT
    +30.0f,           // SPEAKER_FRONT_RIGHT
    0.0f,             // SPEAKER_FRONT_CENTER 
    -360.0f,          // SPEAKER_LOW_FREQUENCY -- ignore in calculation
    -135.0f + 360.0f, // SPEAKER_BACK_LEFT              
    +135.0f,          // SPEAKER_BACK_RIGHT
    -15.0f + 360.0f,  // SPEAKER_FRONT_LEFT_OF_CENTER
    +15.0f,           // SPEAKER_FRONT_RIGHT_OF_CENTER
    +180.0f,          // SPEAKER_BACK_CENTER
    -110.0f + 360.0f, // SPEAKER_SIDE_LEFT
    +110.0f           // SPEAKER_SIDE_RIGHT
    // Any top-speakers should be dealt with by outer systems.
  };

  F32UP *fltSrcAngles=NULL, *fltDstAngles=NULL;

  //prefast warning
  if (cSrcChannels > 32 || cDstChannels > 32) { wmar = WMA_E_INVALIDARG;  goto lerror; }


  fltSrcAngles = (F32*)auMalloc(cSrcChannels*sizeof(F32));
  CHECK_ALLOC(fltSrcAngles);
  fltDstAngles = (F32*)auMalloc(cDstChannels*sizeof(F32));
  CHECK_ALLOC(fltDstAngles);  

  FixAnglesForSideBackAmbiguity(srcMask, dstMask, rgfltSpeakerDirection,
                                SPEAKER_POS);

  cSrcCh = 0;
  cDstCh = 0;
  mask = 0x1;
  for (i=0; i < SPEAKER_POS; i++) {
    if (mask & srcMask) {
      if (cSrcCh == cSrcChannels) { wmar = WMA_E_INVALIDARG;  goto lerror; }
      fltSrcAngles[cSrcCh++] = rgfltSpeakerDirection[i];
    }
    if (mask & dstMask) {
      if (cDstCh == cDstChannels) { wmar = WMA_E_INVALIDARG;  goto lerror; }
      fltDstAngles[cDstCh++] = rgfltSpeakerDirection[i];
    }
    mask <<= 1;
  }
  for (i=cSrcCh; i < cSrcChannels; i++) fltSrcAngles[i] = -360.0f;
  for (i=cDstCh; i < cDstChannels; i++) fltDstAngles[i] = -360.0f;

  wmar = SetMixFromAngles(cSrcChannels, cDstChannels,
                          fltSrcAngles, fltDstAngles, fltMixMtx);
  if (WMA_FAILED(wmar)) { goto lerror; }

  // Take care of (-) angles such as subwoofer
  cSrcCh = 0;
  cDstCh = 0;
  mask = 0x1;
  for (i=0; i < SPEAKER_POS; i++) {    
    // check if already taken care of
    if ((i < SPEAKER_POS) && rgfltSpeakerDirection[i]>=0.0f) goto loopend;
    // See if (-) angle mask present in both src & dst, if so pass through
    if ((mask & srcMask) && (mask & dstMask))
      MIXMTX(cDstCh, cSrcCh) = (RsC)1.0f;
    // If (-) angle mask present in dst only, set to 0 -- nothing to do
    if (!(mask & srcMask) && (mask & dstMask)) {
      if (!(mask & SPEAKER_LOW_FREQUENCY)) {
        wmar = WMA_E_NOTSUPPORTED;
        goto lerror;
      }
    }
    // If (-) angle mask present in src only, distribute only for subwoofer
    if ((mask & srcMask) && !(mask & dstMask)) {
      if (mask & SPEAKER_LOW_FREQUENCY) {
        // distribute 20% over destination channels, 20% matches what WMA
        // uses for downmixing
        for (j=0; j < cDstChannels; j++)
          MIXMTX(j, cSrcCh) = (RsC)(0.2*(1.0/cDstChannels));
      } else {
        wmar = WMA_E_NOTSUPPORTED;
        goto lerror;
      }
    }
  loopend:
    if (mask & srcMask) cSrcCh++;
    if (mask & dstMask) cDstCh++;
    mask <<= 1;
  }

  NormalizeMixMtx(cSrcChannels, cDstChannels, fltMixMtx);

#undef SPEAKER_POS
#if 0
  for (i=0; i < cDstChannels; i++) {
    for (j=0; j < cSrcChannels; j++) {
      printf("%8.6f ", MIXMTX(i, j));
    }
    printf("\n");
  }
#endif

lerror:
  auFree(fltSrcAngles);
  auFree(fltDstAngles);
  return wmar;
}

