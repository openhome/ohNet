//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#include <string.h>
#include <float.h>
#include "wmapcmacc.h"
#include "wmaassert.h"

void WMAPCMAccSetFormat(WMAPCMAcc* pAcc, PCMFormat* pFormat)
{
  memcpy(&(pAcc->fmt), pFormat, sizeof(pAcc->fmt));
  if (PCMDataIEEE_FLOAT == pFormat->pcmData) {
    pAcc->type = PCMAccFlt;
  } else if (1 == pFormat->cbPCMContainerSize && 8 == pFormat->nValidBitsPerSample) {
      pAcc->type = PCMAcc8;
  } else if (2 == pFormat->cbPCMContainerSize && 16 >= pFormat->nValidBitsPerSample && 12 <= pFormat->nValidBitsPerSample) {
      pAcc->type = PCMAcc16;
  } else if (3 == pFormat->cbPCMContainerSize && 24 >= pFormat->nValidBitsPerSample && 20 <= pFormat->nValidBitsPerSample) {
      pAcc->type = PCMAcc24;
  } else if (4 == pFormat->cbPCMContainerSize && 24 == pFormat->nValidBitsPerSample) {
      pAcc->type = PCMAcc2432;
  } else if (4 == pFormat->cbPCMContainerSize && 32 == pFormat->nValidBitsPerSample) {
      pAcc->type = PCMAcc32;
  } else {
      pAcc->type = PCMAccGeneric;
  }
}

// probably not needed - the double version is probably faster
float WMAPCMAccGetPCMGeneric(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb)
{
#if 1
    return (float) WMAPCMAccGetPCMGenericD(vb, cb, pb);
#else
    WMA_I32 i;
    WMA_U32 c = cb - 1;
    float fltVal;
    assert(cb > 0);
    i = ((signed char*)pb)[c];
    while (c > cb - vb)
    {
        c--;
        i <<= 8;
        i |= (WMA_I32)((pb)[c]);
    }
    fltVal = ((float)i) / 128.0f;
    for (c = 0; c < vb - 1; c++)
    {
        fltVal /= 256.0f;
    }
    return fltVal;
#endif
}

double WMAPCMAccGetPCMGenericD(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb)
{
    WMA_I32 i;
    WMA_U32 c = cb - 1;
    double dblVal;
    assert(cb > 0);
    i = ((signed char*)pb)[c];
    while (c > cb - vb)
    {
        c--;
        i <<= 8;
        i |= (WMA_I32)((pb)[c]);
    }
    dblVal = ((double)i) / 128.0;
    for (c = 0; c < vb - 1; c++)
    {
        dblVal /= 256.0;
    }
    return dblVal;
}

// probably not needed - the double version is probably faster
void WMAPCMAccPutPCMGeneric(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb, float fltVal)
{
#if 1
    WMAPCMAccPutPCMGenericD(vb, cb, pb, (double)fltVal);
#else
    WMA_I32 i;
    WMA_U32 c;
    CLIPF(dblVal);
    fltVal *= 128.0f;
    for (c = 0; c < vb - 1; c++)
    {
        fltVal *= 256.0f;
    }
    FLOAT2I32(fltVal,i);
    for (c = cb - vb; c < cb; c++, i >>= 8)
    {
        (pb)[c] = (WMA_U8)i;
    }
#endif
}

void WMAPCMAccPutPCMGenericD(WMA_U32 vb, WMA_U32 cb, WMA_U8* pb, double dblVal)
{
  WMA_I32 i;
  WMA_U32 c;
  CLIPD(dblVal);
  dblVal *= 128.0;
  for (c = 0; c < vb - 1; c++)
  {
      dblVal *= 256.0;
  }
  DOUBLE2I32(dblVal,i);
  for (c = cb - vb; c < cb; c++, i >>= 8)
  {
      (pb)[c] = (WMA_U8)i;
  }
}


void WMAPCMAccGetPCMMulti(WMAPCMAcc* pAcc, WMA_U8* pb, float* pflt, WMA_U32 count)
{
   WMA_U32 i;
   switch(pAcc->type) {
   case PCMAccFlt: for (i = count; i > 0; i--, pb += 4, pflt++) { GETPCMFLT(pb,(*pflt)); } break;
   case PCMAcc16:  for (i = count; i > 0; i--, pb += 2, pflt++) { GETPCM16 (pb,(*pflt)); } break;
   case PCMAcc24:  for (i = count; i > 0; i--, pb += 3, pflt++) { GETPCM24 (pb,(*pflt)); } break;
   case PCMAcc2432:for (i = count; i > 0; i--, pb += 4, pflt++) { GETPCM24 (pb+1,(*pflt)); } break;
   case PCMAcc32:  for (i = count; i > 0; i--, pb += 4, pflt++) { GETPCM32 (pb,(*pflt)); } break;
   case PCMAcc8:   for (i = count; i > 0; i--, pb += 1, pflt++) { GETPCM8  (pb,(*pflt)); } break;
   case PCMAccGeneric: for (i = count; i > 0; i--, pb += pAcc->fmt.cbPCMContainerSize, pflt++) { *pflt = WMAPCMAccGetPCMGeneric((pAcc->fmt.nValidBitsPerSample + 7) / 8, pAcc->fmt.cbPCMContainerSize, pb); } break;
   default: WMAASSERT(0);
   }
}

void WMAPCMAccGetPCMMultiD(WMAPCMAcc* pAcc, WMA_U8* pb, double* pdbl, WMA_U32 count)
{
   WMA_U32 i;
   switch(pAcc->type) {
   case PCMAccFlt: for (i = count; i > 0; i--, pb += 4, pdbl++) { GETPCMFLTD(pb,(*pdbl)); } break;
   case PCMAcc16:  for (i = count; i > 0; i--, pb += 2, pdbl++) { GETPCM16D (pb,(*pdbl)); } break;
   case PCMAcc24:  for (i = count; i > 0; i--, pb += 3, pdbl++) { GETPCM24D (pb,(*pdbl)); } break;
   case PCMAcc2432:for (i = count; i > 0; i--, pb += 4, pdbl++) { GETPCM24D (pb+1,(*pdbl)); } break;
   case PCMAcc32:  for (i = count; i > 0; i--, pb += 4, pdbl++) { GETPCM32D (pb,(*pdbl)); } break;
   case PCMAcc8:   for (i = count; i > 0; i--, pb += 1, pdbl++) { GETPCM8D  (pb,(*pdbl)); } break;
   case PCMAccGeneric: for (i = count; i > 0; i--, pb += pAcc->fmt.cbPCMContainerSize, pdbl++) { *pdbl = WMAPCMAccGetPCMGenericD((pAcc->fmt.nValidBitsPerSample + 7) / 8, pAcc->fmt.cbPCMContainerSize, pb); } break;
   default: WMAASSERT(0);
   }
}

void WMAPCMAccPutPCMMulti(WMAPCMAcc* pAcc, WMA_U8* pb, float* pflt, WMA_U32 count, WMA_Bool fClip)
{
   WMA_U32 i;
   if (PCMAccFlt == pAcc->type)
   {
       for (i = count; i > 0; i--, pb += 4, pflt++) { PUTPCMFLT(pb,(*pflt)); }
   }
   else if (PCMAccGeneric == pAcc->type)
   {
       for (i = count; i > 0; i--, pb += pAcc->fmt.cbPCMContainerSize, pflt++) { WMAPCMAccPutPCMGeneric((pAcc->fmt.nValidBitsPerSample + 7) / 8, pAcc->fmt.cbPCMContainerSize, pb,(*pflt)); }
   }
   else
   {
       if (fClip)
       {
           switch(pAcc->type) {
           case PCMAcc16:  for (i = count; i > 0; i--, pb += 2, pflt++) { PUTPCM16CLIP (pb,(*pflt)); } break;
           case PCMAcc24:  for (i = count; i > 0; i--, pb += 3, pflt++) { PUTPCM24CLIP (pb,(*pflt)); } break;
           case PCMAcc2432:for (i = count; i > 0; i--, pb += 4, pflt++) { PUTPCM24CLIP (pb+1,(*pflt)); } break;
           case PCMAcc32:  for (i = count; i > 0; i--, pb += 4, pflt++) { PUTPCM32CLIP (pb,(*pflt)); } break;
           case PCMAcc8:   for (i = count; i > 0; i--, pb += 1, pflt++) { PUTPCM8CLIP  (pb,(*pflt)); } break;
           default: WMAASSERT(0);
           }
       }
       else
       {
           switch(pAcc->type) {
           case PCMAcc16:  for (i = count; i > 0; i--, pb += 2, pflt++) { PUTPCM16 (pb,(*pflt)); } break;
           case PCMAcc24:  for (i = count; i > 0; i--, pb += 3, pflt++) { PUTPCM24 (pb,(*pflt)); } break;
           case PCMAcc2432:for (i = count; i > 0; i--, pb += 4, pflt++) { PUTPCM24 (pb+1,(*pflt)); } break;
           case PCMAcc32:  for (i = count; i > 0; i--, pb += 4, pflt++) { PUTPCM32 (pb,(*pflt)); } break;
           case PCMAcc8:   for (i = count; i > 0; i--, pb += 1, pflt++) { PUTPCM8  (pb,(*pflt)); } break;
           default: WMAASSERT(0);
           }
       }
   }
}

void WMAPCMAccPutPCMMultiD(WMAPCMAcc* pAcc, WMA_U8* pb, double* pdbl, WMA_U32 count, WMA_Bool fClip)
{
   WMA_U32 i;
   if (PCMAccFlt == pAcc->type)
   {
       for (i = count; i > 0; i--, pb += 4, pdbl++) { PUTPCMFLTD(pb,(*pdbl)); }
   }
   else if (PCMAccGeneric == pAcc->type)
   {
       for (i = count; i > 0; i--, pb += pAcc->fmt.cbPCMContainerSize, pdbl++) { WMAPCMAccPutPCMGenericD((pAcc->fmt.nValidBitsPerSample + 7) / 8, pAcc->fmt.cbPCMContainerSize, pb,(*pdbl)); }
   }
   else
   {
       if (fClip)
       {
           switch(pAcc->type) {
           case PCMAcc16:  for (i = count; i > 0; i--, pb += 2, pdbl++) { PUTPCM16CLIPD (pb,(*pdbl)); } break;
           case PCMAcc24:  for (i = count; i > 0; i--, pb += 3, pdbl++) { PUTPCM24CLIPD (pb,(*pdbl)); } break;
           case PCMAcc2432:for (i = count; i > 0; i--, pb += 4, pdbl++) { PUTPCM24CLIPD (pb+1,(*pdbl)); } break;
           case PCMAcc32:  for (i = count; i > 0; i--, pb += 4, pdbl++) { PUTPCM32CLIPD (pb,(*pdbl)); } break;
           case PCMAcc8:   for (i = count; i > 0; i--, pb += 1, pdbl++) { PUTPCM8CLIPD  (pb,(*pdbl)); } break;
           default: WMAASSERT(0);
           }
       }
       else
       {
           switch(pAcc->type) {
           case PCMAcc16:  for (i = count; i > 0; i--, pb += 2, pdbl++) { PUTPCM16D (pb,(*pdbl)); } break;
           case PCMAcc24:  for (i = count; i > 0; i--, pb += 3, pdbl++) { PUTPCM24D (pb,(*pdbl)); } break;
           case PCMAcc2432:for (i = count; i > 0; i--, pb += 4, pdbl++) { PUTPCM24D (pb+1,(*pdbl)); } break;
           case PCMAcc32:  for (i = count; i > 0; i--, pb += 4, pdbl++) { PUTPCM32D (pb,(*pdbl)); } break;
           case PCMAcc8:   for (i = count; i > 0; i--, pb += 1, pdbl++) { PUTPCM8D  (pb,(*pdbl)); } break;
           default: WMAASSERT(0);
           }
       }
   }
}

