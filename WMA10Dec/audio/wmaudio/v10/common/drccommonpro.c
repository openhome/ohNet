//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*  -*-c++-*-
 *  Sanjeev Mehrotra
 *  2001/09/20
 *
 *  Used only by WMA Pro: WMA Std and WMA Lossless do not need this functionality.
 *
 */


#include <stdio.h>
#include <math.h>

#ifdef UNDER_CE
#include <windows.h>
#   include <dbgapi.h>
#   define assert ASSERT
#else
    // The following are ANSI C includes, and so should be safe for all platforms
#   include <assert.h>     // If this doesn't exist, you must write an "assert" macro
#endif
#include "msaudiodec.h"
#include "drccommon.h"

// ========================================================================
#if defined(BUILD_WMAPRO)

#if defined(_SH4_)
#pragma warning(push)
#pragma warning(disable:4719)
#endif

#define CHECK_ALLOC(x) { \
  if ((x) == NULL) { \
    wr = WMA_E_OUTOFMEMORY; \
    goto exit; \
  } \
}

#ifdef STANDALONE_POSTPROCDRC
#define false 0
#define true  1
#else
#define false WMAB_FALSE
#define true  WMAB_TRUE
#endif

// =========================================================================

#define WMA_DRC_MED_POS (0)
#define WMA_DRC_LOW_POS (1)

// ========================================================================

#define MAX_INT24ABSSAMPLE (8388608)
//#define MIN_INT24DSAMPLE (-(Double)(MAX_INT24ABSSAMPLE))
//#define MAX_INT24DSAMPLE ((Double)(MAX_INT24ABSSAMPLE-1))

#define MAX_PEAKVAL (MAX_INT24ABSSAMPLE-2)

#define MIN_INT24SAMPLE (-MAX_INT24ABSSAMPLE)
#define MAX_INT24SAMPLE (MAX_INT24ABSSAMPLE-1)

// ========================================================================
// defines

#define USE_TABLES
//#define USE_AVG_WINDOW
#define ADJUST_FOR_CLIP
#define DRC_DECODE_USE_TABLES

// =========================================================================

// change definitions of these when integrating with "wmaudio"
#ifdef STANDALONE_POSTPROCDRC

// CHECKCHECK -- assumes pointers are byte pointers
#define DRC_GET_SAMPLE(sample, ptr) { sample = *(I32*)(ptr); }
#define DRC_PUT_SAMPLE(sample, ptr) { *(I32*)ptr = (sample); }
#define DRC_ADVANCE_PTR(ptr) (ptr += sizeof(I32))
#define DRC_ADVANCE_PTR_N(ptr, N) (ptr += (N)*sizeof(I32))

#else // #ifdef STANDALONE_POSTPROCDRC

// change to PPGETSAMPLE, etc... if doing before PCM
#define DRC_GET_SAMPLE(sample, ptr) { \
  sample = p->m_pau->m_pfnGetSample((PCMSAMPLE*)ptr, \
    p->m_pau->m_nBytePerSample, \
    p->m_pau->m_nValidBitsPerSample, 0); \
  if (p->m_amtToLeftShift >= 0) { \
    sample <<= p->m_amtToLeftShift; \
  } else { \
    sample >>= -p->m_amtToLeftShift; \
  } \
}
#define DRC_PUT_SAMPLE(sample, ptr) { \
  if (p->m_amtToLeftShift >= 0) { \
    sample >>= p->m_amtToLeftShift; \
  } else { \
    sample <<= -p->m_amtToLeftShift; \
  } \
  p->m_pau->m_pfnSetSample(sample, (PCMSAMPLE*)ptr, p->m_pau, 0); \
}
#define DRC_ADVANCE_PTR(ptr) { \
  ptr = (U8*)prvAdvancePCMPointer((PCMSAMPLE*)ptr, \
    p->m_pau->m_nBytePerSample, 1); \
}
#define DRC_ADVANCE_PTR_N(ptr, N) { \
  ptr = (U8*)prvAdvancePCMPointer((PCMSAMPLE*)ptr, \
    p->m_pau->m_nBytePerSample, N); \
}

#endif // #ifdef STANDALONE_POSTPROCDRC

// ======================================================================

#define LN10 (2.30258509299405)
#define pow10(x) (exp((x)*LN10))

#define ONE_OVER_LN2 (1.4426950408889634073599246810019)
#define flog2(x) (log(x)*ONE_OVER_LN2)

// =====================================================================

#ifdef DRC_BUILD_INTEGER_TABLE

#define DB_TABLE_MSB (24)

#define TableType I32
#include "fntable.h"

//#define MAKE_DRC_TABS

#ifdef MAKE_DRC_TABS
FnTableInterp g_drcFnTableDb;
FnTableInterp g_drcFnTableScale;
FnTableInterp g_drcFnTableExp;
#include "../vcmake/maktbls/drcinttables.c"
#else
#include "drctables.c"
#endif

#endif

// =====================================================================

#ifdef DRC_BUILD_INTEGER_TABLE

#define drcMult(sample, scale) MULT_DRCSCALE((sample), (scale))
#define drcTypeToI32(sample) (sample)
#define drcTypeToSample(sample) (sample)
#define drcMultRange(sample, scale) MULT_DRCSCALE((sample), (scale))

#if (DB_TABLE_MSB == 16)

INLINE DRCDbType drcInt16ToDb(const I32 x)
{
  return prvGetFnTable((FnTableInterp*)&g_drcFnTableDb, x);
}

INLINE DRCDbType drcInt24ToDb(const I32 x)
{
  return drcInt16ToDb(x>>8);
}

#elif (DB_TABLE_MSB == 24)

INLINE DRCDbType drcInt24ToDb(const I32 x)
{
  return prvGetFnTable((FnTableInterp*)&g_drcFnTableDb, x);
}

#else
#error "DB_TABLE_MSB must be 16 or 24!"
#endif

INLINE DRCScaleType drcDbToScale(DRCDbType x)
{
  x = checkRange(x, g_drcFnTableScale.m_offset, g_drcFnTableScale.m_maxVal);
  return prvGetFnTable((FnTableInterp*)&g_drcFnTableScale, x);
}

#else // #ifdef DRC_BUILD_INTEGER_TABLE

#ifdef DRC_USE_FLOAT
#define drcMult(sample, scale) (ROUNDF( (DRCType)(sample) * (scale)))
#define drcTypeToI32(sample) (ROUNDF(sample))
#else // use doubles
#define drcMult(sample, scale) (ROUNDD( (DRCType)(sample) * (scale)))
#define drcTypeToI32(sample) (ROUNDD(sample))
#endif

INLINE I32 drcTypeToSample(const DRCType sample)
{
  I32 val = drcTypeToI32(sample);
  return checkRange(val, MIN_INT24SAMPLE, MAX_INT24SAMPLE);
}

INLINE I32 drcMultRange(const I32 sample, const DRCType scale)
{
  I32 val = drcMult(sample, scale);
  return checkRange(val, MIN_INT24SAMPLE, MAX_INT24SAMPLE);
}

// Note: the following macros do double math
INLINE Double drcInt24ToDb(const I32 x)
{
  if (x <= 0.0) return DRC_MIN_DB;
  return max(-20.0 * log10((Double)MAX_INT24ABSSAMPLE/x), DRC_MIN_DB);
}

INLINE Double drcInt24DToDb(const Double x)
{
  if (x <= 0.0) return DRC_MIN_DB;
  return max(-20.0 * log10((Double)MAX_INT24ABSSAMPLE/x), DRC_MIN_DB);
}

#define drcDbToScale(x) (pow10((Double)(x)/20.0))

#endif // #ifdef DRC_BUILD_INTEGER_TABLE

// decoder tables -----------------------------------------------------

#ifdef DRC_DECODE_USE_TABLES
AVRT_DATA DRCType g_drcIndexToSF[256]; // could dynamically alloc, but then need ref counts, locks when allocating (to support multiple threads), etc... -- too much pain
AVRT_DATA Bool g_drcIndexToSFInit = false;
#endif

// ---------------------------------------------------------

INLINE U8 quantScaleFactor(const DRCScaleType scaleFactor)
{
  U8 quantScaleFactor;
  Int shiftScale;
  Int multScale;

#define SHIFT_SCALE_BITS (3) // signed
#define MULT_SCALE_BITS (5) // unsigned
#define MIN_SHIFT_SCALE (-(1<<(SHIFT_SCALE_BITS-1)))
#define MAX_SHIFT_SCALE ((1<<(SHIFT_SCALE_BITS-1))-1)
#define MIN_MULT_SCALE (0)
#define MAX_MULT_SCALE ((1<<MULT_SCALE_BITS)-1)
#if ((MULT_SCALE_BITS - MAX_SHIFT_SCALE) < 0)
#error "Won't work"
#endif

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast(disable: 297)
#endif // _PREFAST_

#ifdef DRC_BUILD_INTEGER_TABLE
  shiftScale = LOG2(scaleFactor) - DRC_SCALE_BITS;
#else
  shiftScale = (Int)floor(flog2(scaleFactor));
#endif
  if (shiftScale < MIN_SHIFT_SCALE) {
    shiftScale = MIN_SHIFT_SCALE;
    multScale = MIN_MULT_SCALE;
  } else if (shiftScale > MAX_SHIFT_SCALE) {
    shiftScale = MAX_SHIFT_SCALE;
    multScale = MAX_MULT_SCALE;
  } else {
#ifdef DRC_BUILD_INTEGER_TABLE
    multScale =
      (Int)(scaleFactor>>(DRC_SCALE_BITS - MULT_SCALE_BITS + shiftScale))
      - (1<<(MULT_SCALE_BITS));
#else
    multScale =
      (Int)(scaleFactor*(DRCScaleType)(1<<(MULT_SCALE_BITS - shiftScale)))
      - (1<<(MULT_SCALE_BITS));
#endif
  }
  assert(multScale >= 0 && multScale < (1<<MULT_SCALE_BITS));

  quantScaleFactor = (U8)(shiftScale << MULT_SCALE_BITS) | (U8)multScale;

#ifdef _PREFAST_
#pragma prefast(pop)
#endif // _PREFAST_

  return quantScaleFactor;
}

INLINE DRCType unquantScaleFactor(DRC *p, U8 quantScaleFactor)
{
  DRCType scaleFactor;
  I8 shiftScale;
  U8 multScale;

  shiftScale = (I8)quantScaleFactor >> MULT_SCALE_BITS;
  multScale = (U8)(quantScaleFactor & MAX_MULT_SCALE);

#if defined(DRC_BUILD_INTEGER_TABLE) && (DRC_SCALE_BITS-MULT_SCALE_BITS-4 <= 0)
#error "This won't work!!"
#endif

#ifdef DRC_BUILD_INTEGER_TABLE
  scaleFactor = (multScale + (1<<MULT_SCALE_BITS))<<
    (DRC_SCALE_BITS-MULT_SCALE_BITS+shiftScale);
#else
  scaleFactor = (DRCType)(multScale + (1<<MULT_SCALE_BITS)) /
    (DRCType)(1<<(MULT_SCALE_BITS - shiftScale));
#endif

  return scaleFactor;
}

// =====================================================================

#ifndef DRC_BUILD_INTEGER_TABLE

#define L2TOMONO  ((DRCType)0.5)
#define R2TOMONO  ((DRCType)0.5)

#define L5TOMONO  ((DRCType)0.05480055608295)
#define R5TOMONO  ((DRCType)0.05480055608295)
#define C5TOMONO  ((DRCType)0.86853028278959)
#define LB5TOMONO ((DRCType)0.01093414843917)
#define RB5TOMONO ((DRCType)0.01093414843917)

INLINE DRCType getMonoAbsSample(I32 *samples, int nChannels)
{
  DRCType sample;

  if (nChannels == 1) {
    sample = (DRCType)samples[0];
  }
  else if (nChannels == 2) {
    sample =
      L2TOMONO*(DRCType)samples[0] +
      R2TOMONO*(DRCType)samples[1];
  }
  else if (nChannels == 6) { // 5.1 to mono
    sample =
      L5TOMONO*(DRCType)samples[0] +
      R5TOMONO*(DRCType)samples[1] +
      C5TOMONO*(DRCType)samples[2] +
      LB5TOMONO*(DRCType)samples[4] +
      RB5TOMONO*(DRCType)samples[5];
  }
  else {
    sample = 0;
    assert(false);
  }

  return (sample < (DRCType)0) ? -sample : sample;
}

#undef L2TOMONO
#undef R2TOMONO

#undef L5TOMONO
#undef R5TOMONO
#undef C5TOMONO
#undef LB5TOMONO
#undef RB5TOMONO

#else // #ifndef DRC_BUILD_INTEGER_TABLE

#define getMonAbsSample getMonoAbsISample

#endif // #ifndef DRC_BUILD_INTEGER_TABLE

#define L5TOMONO (8)
#define R5TOMONO (8)
#define C5TOMONO (110)
#define LB5TOMONO (1)
#define RB5TOMONO (1)

#define FIVETOONEBITS (7)
#if (L5TOMONO + R5TOMONO + C5TOMONO + LB5TOMONO + RB5TOMONO != \
     (1<<FIVETOONEBITS))
#error "Bits do not add up properly"
#endif

INLINE I32 getMonoAbsISample(I32 *samples, int nChannels)
{
  I32 sample;

  if (nChannels == 1) {
    return (samples[0] < 0) ? -samples[0] : samples[0];
  }
  if (nChannels == 2) {
    sample = (samples[0] + samples[1])>>1;
    return (sample < 0) ? -sample : sample;
  }
  if (nChannels == 6) {
    sample = (samples[0]*L5TOMONO + samples[1]*R5TOMONO +
              samples[2]*C5TOMONO + 
              samples[3]*LB5TOMONO + samples[4]*RB5TOMONO) >> FIVETOONEBITS;
    return (sample < 0) ? -sample : sample;
  }

  assert(false);
  return 0;
}

#undef L5TOMONO
#undef R5TOMONO
#undef C5TOMONO
#undef LB5TOMONO
#undef RB5TOMONO

#undef FIVETOONEBITS

INLINE I32 getMaxAbsSample(I32 *samples, int nChannels)
{
  I32 abssamples[6];

  if (nChannels == 1) {
    return
      (samples[0] < 0) ? -samples[0] : samples[0];
  }
  if (nChannels == 2) {
    abssamples[0] = (samples[0] < 0) ? -samples[0] : samples[0];
    abssamples[1] = (samples[1] < 0) ? -samples[1] : samples[1];
    return max(abssamples[0], abssamples[1]);
  }
  if (nChannels == 6) { // 5.1
    abssamples[0] = (samples[0] < 0) ? -samples[0] : samples[0];
    abssamples[1] = (samples[1] < 0) ? -samples[1] : samples[1];
    abssamples[2] = (samples[2] < 0) ? -samples[2] : samples[2];
    abssamples[3] = (samples[3] < 0) ? -samples[3] : samples[3];
    abssamples[4] = (samples[4] < 0) ? -samples[4] : samples[4];
    abssamples[5] = (samples[5] < 0) ? -samples[5] : samples[5];
    return max(abssamples[0],
               max(abssamples[1],
                   max(abssamples[2],
                       max(abssamples[3],
                           max(abssamples[4], abssamples[5])))));
  }
  {
    Int i;
    I32 maxSample=0, abssample;
    for (i=0; i < nChannels; i++) {
      abssample = (samples[i] < 0) ? -samples[i] : samples[i];
      if (abssample > maxSample) maxSample = abssample;
    }
    return maxSample;
  }
}

INLINE
WMARESULT drcDataFormatToDb(DRCDbType *pValDb,
                            PostProcDrcDataFormatVal value,
                            PostProcDrcDataFormat format,
                            Int nValidBitsPerSample)
{
  WMARESULT wr = WMA_OK;
  DRCDbType valDb=(DRCDbType)0;
  Int amtToLeftShift;

  switch (format) {
  case PostProcDrcDataInDb:
    valDb = value.dB;
    break;
  case PostProcDrcDataInI32:
    assert(nValidBitsPerSample != 0);
    amtToLeftShift = 24 - nValidBitsPerSample;
    if (amtToLeftShift >= 0)
      valDb = drcInt24ToDb(value.val << amtToLeftShift);
    else
      valDb = drcInt24ToDb(value.val >> -amtToLeftShift);
    break;
  case PostProcDrcDataInNormU16:
    amtToLeftShift = 24 - 16; // maximum here is 0x7fff which means 16 bits, since it is signed
    valDb = drcInt24ToDb(value.normVal << amtToLeftShift);
    break;
  default: assert(false);  wr = WMA_E_INVALIDARG;  goto exit;
  }

exit:
  if (pValDb) *pValDb = valDb;
  return wr;
}

#define PEAKTORMS_MED_DB (FLOAT_TO_DRCDB(12))
//#define PEAKTORMS_LOW_DB (FLOAT_TO_DRCDB(8))
#define PEAKTORMS_LOW_DB (FLOAT_TO_DRCDB(6))

// the following values are obtained from looking at values
// E[X^2] = p(X<T) E[X^2 | X<T] + p(Y>=T) E[X^2 | X>=T]
// after drc, get Y = DRC(X) = (X if X<T, T if X>=T)
// E[Y^2] = p(Y<T) E[Y^2 | Y<T] + p(Y>=T) E[Y^2 | Y>=T]
//        = p(X<T) E[X^2 | X<T] + p(X>=T) T*T
// Therefore the loss in squared energy by doing drc is
// loss = P(X>=T) (E[X^2 | X>=T] - T*T)
// we use this loss to determin boost up thresholds by looking at several files
//  this is scaled by amount of loss in peak
#define RMS_MED_DB (FLOAT_TO_DRCDB(0.8/8.0))
//#define RMS_LOW_DB (1.7/8.0) // for 8
#define RMS_LOW_DB (FLOAT_TO_DRCDB(2.0/8.0)) // for 6

WMARESULT drcSuggestedDesiredRmsPeakWMA(DRCData *pd,
                                        DRCDbType *pDesiredRmsDb,
                                        DRCDbType *pDesiredPeakDb,
                                        I16 nDRCSetting)
{
  WMARESULT wr = WMA_OK;
  DRCDbType rmsDb, peakDb;
  DRCDbType desiredRmsDb=(DRCDbType)0, desiredPeakDb=(DRCDbType)0;
  DRCDbType diffPeakDb;

  TRACEWMA_EXIT(wr, drcDataFormatToDb(&rmsDb, pd->rms,
                                      pd->dataFormatRms, 0));
  TRACEWMA_EXIT(wr, drcDataFormatToDb(&peakDb, pd->peak,
                                      pd->dataFormatPeak, 0));

  if (nDRCSetting == WMA_DRC_MED) {
    diffPeakDb = peakDb - (rmsDb + PEAKTORMS_MED_DB);
    desiredRmsDb =
      min(0, rmsDb + MULT_DRCDB(RMS_MED_DB, max(diffPeakDb, 0)));
    desiredPeakDb = min(0, desiredRmsDb + PEAKTORMS_MED_DB);
  }
  if (nDRCSetting == WMA_DRC_LOW) {
    diffPeakDb = peakDb - (rmsDb + PEAKTORMS_LOW_DB);
    desiredRmsDb =
      min(0, rmsDb + MULT_DRCDB(RMS_LOW_DB, max(diffPeakDb, 0.0)));
    desiredPeakDb = min(0, desiredRmsDb + PEAKTORMS_LOW_DB);
  }

exit:
  if (pDesiredRmsDb) *pDesiredRmsDb = desiredRmsDb;
  if (pDesiredPeakDb) *pDesiredPeakDb = desiredPeakDb;

  return wr;
}

DRCDbType drcBoostPeakChop(DRCDbType origRmsDb, DRCDbType desiredRmsDb,
                             DRCDbType origPeakDb, DRCDbType desiredPeakDb)
{
  DRCDbType origDynamicRange = origPeakDb - origRmsDb;
  DRCDbType desiredDynamicRange = desiredPeakDb - desiredRmsDb;

  // give 1 dB boost for 8 dB in peak chopping
  DRCDbType diffDynamicRange = origDynamicRange - desiredDynamicRange;
#ifdef DRC_BUILD_INTEGER_TABLE
  return max(diffDynamicRange, 0) >> 3;
#else
  return max(diffDynamicRange, 0.0)/8.0;
#endif
}

void drcSetDefaultOptions(DRCOptions *p)
{
  memset(p, 0, sizeof(DRCOptions)); // just to be safe

  // desired rmsDb for normalization
  p->m_fNormalizeRms = false;
  p->m_dataFormatRms = PostProcDrcDataUndefined;
  p->m_dataFormatPeak = PostProcDrcDataUndefined;
  p->m_desiredRms.undefined = 0;
  p->m_desiredPeak.undefined = 0;

  // soft clipping thresholds
  p->m_fUseDRCOnNormalize = true;
  p->m_clipThresholdYDb = FLOAT_TO_DRCDB(-6.0);

  // Dynamic range compression params
  p->m_fDRC = false;
  p->m_fDRCEncode = false;
  p->m_fDRCDecode = false;
  p->m_nDRCCurvePoints = 0;
  p->m_pDRCCurve = NULL;

  // Smooth gain using attack/release times
  p->m_fSmoothGain = false;
  // attack time
  p->m_attackTimeMs = FLOAT_TO_DRCTC(1.0);
  // release time
  p->m_releaseTimeMs = FLOAT_TO_DRCTC(500.0);

  // Use mono channel for obtaining level, default is max channel value
  p->m_fUseMonoChannel = false;

  // use smoothed rms value (IIR filter using attack/release times)
  //  as current level
  p->m_fUseRmsVal = false;
  // use smoothed peak value as current level
  p->m_fUsePeakVal = false;
  // level measurement attack time
  p->m_levelAttackTimeMs = FLOAT_TO_DRCTC(0.5);
  // level measurement release time
  p->m_levelReleaseTimeMs = FLOAT_TO_DRCTC(200.0);

  // use lookahead
  p->m_fUseLookahead = false;
  // lookahead window in milliseconds
  p->m_lookaheadWindowMs = FLOAT_TO_DRCTC(2.0);

  // use average rms value over window as level for entire window
  p->m_fUseAvgWindow = false;
  // linearly interpolate gain between window segments
  p->m_fUseLinInterpGainAvgWindow = false;

  // use lookup tables with interpolation instead of log/antilog calculations
  p->m_fUseTables = true;

  // use wma defaults
  p->m_fUseWmaDefaults = false;
}

void drcDataZero(DRCData *p)
{
  memset(p, 0, sizeof(DRCData)); // just to be safe

  p->dataFormatRms = PostProcDrcDataUndefined;
  p->dataFormatPeak = PostProcDrcDataUndefined;
  p->peak.undefined = 0;
  p->rms.undefined = 0;
  p->fContainsSampleInfo = false;
  p->samplingRate = 0;
  p->nChannels = 0;
  p->nBytePerSample = 0;
  p->nValidBitsPerSample = 0;
#ifndef STANDALONE_POSTPROCDRC
  p->pau = NULL;
#endif
}

void drcZero(DRC *p)
{
  memset(p, 0, sizeof(DRC)); // just to be safe
  memset(&p->m_opt, 0, sizeof(DRCOptions));

  p->m_nChannels = 0;

  p->m_amtToLeftShift = 0;
#ifndef BUILD_INTEGER
  p->m_amtToScale = 0.0f;
#endif

  p->m_actualRms = (DRCDbType)0;
  p->m_numSampleBlocks = 0;

  p->m_actualPeak = 0;

  // level measurement params ("input" attack/release)
  p->m_curLevel = (DRCType)0;
  p->m_levelAttackCoeff = (DRCType)0;
  p->m_levelReleaseCoeff = (DRCType)0;
  p->m_oneMinusLevelAttackCoeff = (DRCType)0;
  p->m_oneMinusLevelReleaseCoeff = (DRCType)0;
  p->m_cSamplesForAttack = 0;
  p->m_cSamplesForRelease = 0;

  // gain smoothing ("output" attack/relase)
  p->m_curScaleFactor = (DRCType)0;
  p->m_attackCoeff = (DRCType)0;
  p->m_releaseCoeff = (DRCType)0;
  p->m_oneMinusAttackCoeff = (DRCType)0;
  p->m_oneMinusReleaseCoeff = (DRCType)0;
  // linear range scale factor
  p->m_scaleFactor = NULL;
  p->m_fNeedDRCOnNormalize = NULL;

  // params for static curve
  p->m_gainDb = (DRCDbType)0.0;
  p->m_ratioDb = (DRCDbType)0.0;
  p->m_linearThresholdDb = (DRCDbType)0.0;

  // for lookahead
  p->m_nLookahead = 0;
  p->m_lookaheadCount = 0;

  // for avg window
  p->m_windowCount = 0;
  p->m_windowSize = 0;
  p->m_floorHalfWindowSize = 0;
  p->m_prevLevel = (DRCType)0;
  p->m_windowPeakLevel = (DRCType)0;
  // for linearly interpolating gain
  p->m_scaleFactor0 = (DRCType)0;
  p->m_scaleFactor1 = (DRCType)0;
  p->m_scaleFactor0Slope = (DRCType)0;
  p->m_scaleFactor1Slope = (DRCType)0;

  // dynamic scale changing, tables store scale factors, not output values
  p->m_nScaleTables = 0;
  p->m_scaleTable = NULL;
  p->m_scaleSlopeTable = NULL;
  p->m_scaleTableBase = NULL;
  p->m_scaleSlopeTableBase = NULL;

  p->m_maxPeakValEnc = 0;
  p->m_maxPeakValDec = NULL;

#ifndef STANDALONE_POSTPROCDRC
  p->m_pau = NULL;
#endif

  p->m_curSamples = NULL;
  p->m_lookaheadSamples = NULL;

  p->m_intSlopeShiftBits = NULL;

#ifdef MAKE_DRC_TABS
  drcIntTabsZero();
#endif
}

#define DRCFREE(p) { if (p) auFree(p); }

//#define FPRINT_SFAC
#ifdef FPRINT_SFAC
FILE *fsfac = NULL;
FILE *fssfac = NULL;
FILE *fqsfac = NULL;
#define DRCFCLOSE(p) { if (p) FCLOSE(p); }
#endif

void drcFree(DRC *p)
{
  Int i;

  if (NULL == p)
    return;

#ifdef FPRINT_SFAC
  DRCFCLOSE(fsfac);
  DRCFCLOSE(fssfac);
  DRCFCLOSE(fqsfac);
#endif

  DRCFREE(p->m_scaleFactor);
  DRCFREE(p->m_fNeedDRCOnNormalize);
  DRCFREE(p->m_intSlopeShiftBits);

  for (i=0; i < p->m_nScaleTables; i++) { // actual memory only from base
    if (p->m_scaleTableBase) DRCFREE(p->m_scaleTableBase[i]);
    if (p->m_scaleSlopeTableBase) DRCFREE(p->m_scaleSlopeTableBase[i]);
  }
  DRCFREE(p->m_scaleTableBase);
  DRCFREE(p->m_scaleSlopeTableBase);
  DRCFREE(p->m_scaleTable);
  DRCFREE(p->m_scaleSlopeTable);

  DRCFREE(p->m_maxPeakValDec);

  DRCFREE(p->m_opt.m_pDRCCurve);

  DRCFREE(p->m_curSamples);
  DRCFREE(p->m_lookaheadSamples);

#ifdef MAKE_DRC_TABS
  drcIntTabsFree();
#endif

  drcZero(p);
}

// return scale factor in dB
DRCDbType drcApplyDrcCurve(DRC *p, DRCDbType absvalDb)
{
  int i;
  Double *pX = p->m_opt.m_pDRCCurve;
  Double *pY = p->m_opt.m_pDRCCurve+1;
  Double *pSlope = p->m_opt.m_pDRCCurve+2;
  int stride = 3;

  assert(absvalDb >= DRC_MIN_DB && absvalDb <= (DRCDbType)0.0);
  for (i=0; i < p->m_opt.m_nDRCCurvePoints-1; i++) {
    if (absvalDb>=DOUBLE_TO_DRCDB(pX[0]) &&
        absvalDb<=DOUBLE_TO_DRCDB(pX[stride])) {
      return DOUBLE_TO_DRCDB(pY[0]) + 
        MULT_DRCDB((absvalDb-DOUBLE_TO_DRCDB(pX[0])),
                   DOUBLE_TO_DRCDB(pSlope[0]));
    }
    pX += stride;
    pY += stride;
    pSlope += stride;
  }
  assert(false);
  return (DRCDbType)0.0;
}

DRCDbType drcGetDrcCurveScale(DRC *p, DRCDbType absvalDb)
{
  return drcApplyDrcCurve(p, absvalDb) - absvalDb;
}

DRCDbType drcGetRmsNormCurveScale(DRC *p, DRCDbType absvalDb)
{
  if (absvalDb <= p->m_linearThresholdDb) {
    return p->m_gainDb;
  } else {
    return p->m_linearThresholdDb + p->m_gainDb +
      MULT_DRCDB((absvalDb-p->m_linearThresholdDb), p->m_ratioDb) - absvalDb;
  }
}

DRCScaleType drcGetScaleFactor(DRC *p, DRCDbType absvalDb)
{
  DRCDbType outsampleDb, scaleDb;
  if (p->m_opt.m_fDRC && p->m_opt.m_fNormalizeRms) {
    if (p->m_opt.m_pDRCCurve == NULL) {
      scaleDb = drcGetRmsNormCurveScale(p, absvalDb);
    } else {
      outsampleDb = drcApplyDrcCurve(p, absvalDb);
      scaleDb = drcGetRmsNormCurveScale(p, outsampleDb);
      scaleDb += outsampleDb - absvalDb;
    }
  } else if (p->m_opt.m_fDRC) {
    scaleDb = drcGetDrcCurveScale(p, absvalDb);
  } else if (p->m_opt.m_fNormalizeRms) {
    scaleDb = drcGetRmsNormCurveScale(p, absvalDb);
  } else {
    scaleDb = (DRCDbType)0.0;
  }
  return drcDbToScale(scaleDb);
}

WMARESULT drcCreateScaleTables(DRC *p, Int nTable)
{
  WMARESULT wr = WMA_OK;
  Int i;
  Int startPoint, numEntries;
  I32 sample;
  DRCDbType absvalDb;
  DRCScaleType scaleFactor;
  DRCType *scaleTableBase=NULL, *scaleTable=NULL;
  DRCType *scaleSlopeTableBase=NULL, *scaleSlopeTable=NULL;
#ifdef DRC_BUILD_INTEGER_TABLE
  DRCType maxDiffVal, diff;
  Int maxDiffValBits;
#endif

  if (!p->m_opt.m_fUseTables) goto exit;

#define TABLE_SCALE_BITS (10)
#define TABLE_SCALE_SIZE (1<<TABLE_SCALE_BITS)
#define REM_SCALE_BITS (24-TABLE_SCALE_BITS-1) // -1 for sign bit

#define TABLE_SCALE_MASK (0xffffffff >> (32-TABLE_SCALE_BITS) << REM_SCALE_BITS)
#define REM_SCALE_MASK (0xffffffff >> (32-REM_SCALE_BITS))
#define SLOPE_INT_BITS (30)

  // tables can be created for both (+) and (-) for all regions to
  //  avoid any if statements... (largest table)
  // tables can also be created for only non-linear (+) regions (smallest)

  startPoint = 0;
  numEntries = TABLE_SCALE_SIZE - startPoint;
  //WMAPrintf("Num entries = %d\n", numEntries);

  scaleTableBase = (DRCType*) auMalloc((numEntries+1)*sizeof(DRCType));
  CHECK_ALLOC(scaleTableBase);
  scaleTable = scaleTableBase - startPoint;
  for (i=startPoint; i <= TABLE_SCALE_SIZE; i++) {
    sample = i << REM_SCALE_BITS; // i is always positive
#ifdef DRC_BUILD_INTEGER_TABLE
    if (sample == 0x800000) absvalDb = 0;
    else absvalDb = drcInt24ToDb(sample);
#else
    absvalDb = drcInt24ToDb(sample);
#endif
    scaleFactor = drcGetScaleFactor(p, absvalDb);
    scaleTable[i] = (DRCType)(scaleFactor);
  }
  if (scaleTable[0] >= FLOAT_TO_DRCSCALE(20))
    scaleTable[0] = scaleTable[1];

  scaleSlopeTableBase = (DRCType*) auMalloc((numEntries+1)*sizeof(DRCType));
  CHECK_ALLOC(scaleSlopeTableBase);
  scaleSlopeTable = scaleSlopeTableBase - startPoint;
  
#ifdef DRC_BUILD_INTEGER_TABLE
  maxDiffVal = 0;
  for (i=startPoint; i < TABLE_SCALE_SIZE; i++) {
    diff = ABS(scaleTable[i+1] - scaleTable[i]);
    if (diff > maxDiffVal) maxDiffVal = diff;
  }
  maxDiffVal = max(maxDiffVal, 2);
  maxDiffValBits = LOG2(maxDiffVal-1)+1;
  p->m_intSlopeShiftBits[nTable] = SLOPE_INT_BITS - maxDiffValBits;
  // at least 0
  p->m_intSlopeShiftBits[nTable] = max(p->m_intSlopeShiftBits[nTable], 0);
#endif  

  for (i=startPoint; i < TABLE_SCALE_SIZE; i++) {
#ifdef DRC_BUILD_INTEGER_TABLE
    scaleSlopeTable[i] = ((scaleTable[i+1] - scaleTable[i])<<p->m_intSlopeShiftBits[nTable]) >> REM_SCALE_BITS;
    // take care of overshoots
    if (scaleTable[i+1] > scaleTable[i]) { // increasing, + slope
      if (scaleTable[i]+((scaleSlopeTable[i]*(DRCType)REM_SCALE_MASK)>>p->m_intSlopeShiftBits[nTable]) > scaleTable[i+1])
        scaleSlopeTable[i] = 0;
    } else { // decreasing, -slope
      if (scaleTable[i]+((scaleSlopeTable[i]*(DRCType)REM_SCALE_MASK)>>p->m_intSlopeShiftBits[nTable]) < scaleTable[i+1])
        scaleSlopeTable[i] = 0;
    }
#else
    scaleSlopeTable[i] =
      (DRCType)(((DRCScaleType)scaleTable[i+1] - (DRCScaleType)scaleTable[i]) /
                (DRCScaleType) (1 << REM_SCALE_BITS));
#endif
  }
  // need this last entry for sample = -2^23 = -8388608
  scaleSlopeTable[i] = (DRCType)0;

exit:
  // set after exit, so any successfully allocated memory will get freed
  p->m_scaleTableBase[nTable] = scaleTableBase;
  p->m_scaleTable[nTable] = scaleTable;
  p->m_scaleSlopeTableBase[nTable] = scaleSlopeTableBase;
  p->m_scaleSlopeTable[nTable] = scaleSlopeTable;

  return wr;
}

WMARESULT drcCreateUnquantTables(DRC *p)
{
#ifdef DRC_DECODE_USE_TABLES
  WMARESULT wr = WMA_OK;
  int i;

  if (g_drcIndexToSFInit) goto exit;

  for (i=0; i < 256; i++) {
    g_drcIndexToSF[i] = unquantScaleFactor(p, (U8)i);
  }

  g_drcIndexToSFInit = true;

exit:
  return wr;
#else
  return WMA_E_NOTSUPPORTED;
#endif
}

WMARESULT drcInit(DRC *p, WAVEFORMATEXTENSIBLE *pwfx,
                  DRCData *pd, DRCOptions *po)
{
  WMARESULT wr = WMA_OK;
  Int samplingRate, nValidBitsPerSample, nChannels, nBytePerSample, i, j;
  DRCDbType rmsValDb=0, peakValDb=0;
  DRCDbType desiredRmsDb[2], desiredPeakDb[2];
  Bool fNormalizeRms;

  drcFree(p);

#ifdef MAKE_DRC_TABS
  wr = drcIntTabsMake();
  if (WMA_FAILED(wr)) goto exit;
#endif

#ifdef FPRINT_SFAC
  fsfac = FOPEN("sfac", "w");
  fssfac = FOPEN("ssfac", "w");
  fqsfac = FOPEN("qsfac", "w");
#endif

  // copy waveformat data
  if (pd == NULL) { wr = WMA_E_INVALIDARG;  goto exit; }
  if (pwfx == NULL) {
    if (pd->fContainsSampleInfo == false)
      { wr = WMA_E_INVALIDARG;  goto exit; }
    samplingRate = pd->samplingRate;
    nValidBitsPerSample = pd->nValidBitsPerSample;
    nChannels = pd->nChannels;
    nBytePerSample = pd->nBytePerSample;
  } else {
    if (pd->fContainsSampleInfo == true)
      { wr = WMA_E_INVALIDARG;  goto exit; }
    samplingRate = pwfx->Format.nSamplesPerSec;
    nValidBitsPerSample = pwfx->Samples.wValidBitsPerSample;
    nChannels = pwfx->Format.nChannels;
    nBytePerSample = (pwfx->Format.wBitsPerSample + 7)>>3;
  }
  // check data values
  //if (nValidBitsPerSample > 24) { wr = WMA_E_INVALIDARG; goto exit; }
  // now allow > 24 bit data, by right shifting instead of left shifting,
  // since scale factors are computed by using 10 most significant bits
  // of sample in a table lookup, with 13 bits used for linear interpolation,
  // in 32 bit data, the least 8 significant bits won't make much difference
  // if they are or are not used in the interpolation, hence just throw them
  // away.
  if (samplingRate <= 0) { wr = WMA_E_INVALIDARG;  goto exit; }

  // set data values
  p->m_amtToLeftShift = 24 - nValidBitsPerSample;
#ifndef BUILD_INTEGER
  if (p->m_amtToLeftShift >= 0)
    p->m_amtToScale = (Float)(1<<p->m_amtToLeftShift);
  else
    p->m_amtToScale = 1.0f/(Float)(1<<-p->m_amtToLeftShift);
#endif
#ifndef STANDALONE_POSTPROCDRC
  p->m_pau = pd->pau;
#endif
  p->m_nChannels = nChannels;

  // copy options
  if (po == NULL) drcSetDefaultOptions(&p->m_opt);
  else { // to copy drc curve, and also store slope
    // check option values
    if (po->m_attackTimeMs < 0 || po->m_releaseTimeMs < 0 ||
        po->m_levelAttackTimeMs < 0 || po->m_levelReleaseTimeMs < 0 ||
        po->m_lookaheadWindowMs < 0) {
      wr = WMA_E_INVALIDARG;  goto exit;
    }
    memcpy(&p->m_opt, po, sizeof(DRCOptions));
    // overwrite drc curve
    p->m_opt.m_pDRCCurve = NULL;
    if (p->m_opt.m_fDRC || p->m_opt.m_fDRCEncode) {
      if (po->m_pDRCCurve == NULL) {
        wr = WMA_E_INVALIDARG;  goto exit;
      }
      if (p->m_opt.m_nDRCCurvePoints < 2) {
        wr = WMA_E_INVALIDARG;  goto exit;
      }
      if (po->m_pDRCCurve[0] != DRC_MIN_DB_FLOAT) {
        wr = WMA_E_INVALIDARG;  goto exit;
      }
      if (po->m_pDRCCurve[2*(p->m_opt.m_nDRCCurvePoints-1)] != 0.0) {
        wr = WMA_E_INVALIDARG;  goto exit;
      }
      p->m_opt.m_pDRCCurve =
        (Double*)auMalloc(3*p->m_opt.m_nDRCCurvePoints*sizeof(Double));
      CHECK_ALLOC(p->m_opt.m_pDRCCurve);
      for (i=0, j=0; j < p->m_opt.m_nDRCCurvePoints*2; i+=3, j+=2) {
        p->m_opt.m_pDRCCurve[i]   = po->m_pDRCCurve[j];
        p->m_opt.m_pDRCCurve[i+1] = po->m_pDRCCurve[j+1];
        if (j != (p->m_opt.m_nDRCCurvePoints-1)*2) {
          p->m_opt.m_pDRCCurve[i+2] =
            (po->m_pDRCCurve[j+3] - po->m_pDRCCurve[j+1])/
            (po->m_pDRCCurve[j+2] - po->m_pDRCCurve[j]);
          if (po->m_pDRCCurve[j+2] < po->m_pDRCCurve[j]) {
            wr = WMA_E_INVALIDARG;  goto exit;
          }
        } else {
          p->m_opt.m_pDRCCurve[i+2] = (Double)0.0;
        }
      }
    }
    // overwrite attack, release times
    if (p->m_opt.m_fUseWmaDefaults) {
      p->m_opt.m_fSmoothGain = WMAB_TRUE;
      p->m_opt.m_attackTimeMs = DRC_SUGGESTED_ATTACKTIME_MS;
      p->m_opt.m_releaseTimeMs = DRC_SUGGESTED_RELEASETIME_MS;
    }
    // overwrite the drc flag
    p->m_opt.m_fDRC = po->m_fDRC || po->m_fDRCEncode || po->m_fDRCDecode;
    // overwite fUseAvgWindow flag
    if (p->m_opt.m_fUseLinInterpGainAvgWindow) p->m_opt.m_fUseAvgWindow = true;
    // overwrite clipThresholdYDb
    if (!p->m_opt.m_fUseDRCOnNormalize)
      p->m_opt.m_clipThresholdYDb = (DRCDbType)0.0;
    // overwrite fUseTables flag
#ifndef USE_TABLES
    // no static tables, only scale found using table
    p->m_opt.m_fUseTables = false;
#endif
    //if (p->m_fUseTables) WMAPrintf("Using tables\n");
    //if (p->m_fUseStaticTables) WMAPrintf("Using Static tables\n");
  }
  // additional checks
  if (p->m_opt.m_fUseMonoChannel &&
      (p->m_nChannels != 1 && p->m_nChannels != 2 && p->m_nChannels != 6)) {
    wr = WMA_E_INVALIDARG;  goto exit;
  }
  if (p->m_opt.m_fUseRmsVal && p->m_opt.m_fUsePeakVal) { // which one to use??
    wr = WMA_E_INVALIDARG;  goto exit;
  }

  // allocate buffers ====================================================
  p->m_curSamples = (I32*)auMalloc(p->m_nChannels*sizeof(I32));
  CHECK_ALLOC(p->m_curSamples);
  p->m_lookaheadSamples = (I32*)auMalloc(p->m_nChannels*sizeof(I32));
  CHECK_ALLOC(p->m_lookaheadSamples);

  // calculate attack release coeffs =================================
  // if attack, release times close to 0, attack, release coeffs close to 1.0
#ifdef DRC_BUILD_INTEGER_TABLE
#define TIMEMS_TO_COEFF(ONEMINUSCOEFF, COEFF, TIMEMS) { \
  I32 temp = TC_TO_EXPARG(TIMEMS, samplingRate); \
  if (TIMEMS != 0) \
    COEFF = (DRCTccType) (FLOAT_TO_DRCTCC(1.0) - \
              prvGetFnTable((FnTableInterp*)&g_drcFnTableExp, temp)); \
  else \
    COEFF = (DRCTccType) FLOAT_TO_DRCTCC(1.0); \
  ONEMINUSCOEFF = FLOAT_TO_DRCTCC(1.0) - COEFF; \
}
#else
#define TIMEMS_TO_COEFF(ONEMINUSCOEFF, COEFF, TIMEMS) { \
  if (TIMEMS != 0) \
    COEFF = (DRCType) (1.0-exp(-2.2 / (TIMEMS/1000.0*samplingRate))); \
  else \
    COEFF = (DRCType)1.0; \
  ONEMINUSCOEFF = (DRCType)1.0 - COEFF; \
}
#endif

  TIMEMS_TO_COEFF(p->m_oneMinusAttackCoeff, p->m_attackCoeff,
                  p->m_opt.m_attackTimeMs);
  TIMEMS_TO_COEFF(p->m_oneMinusReleaseCoeff, p->m_releaseCoeff,
                  p->m_opt.m_releaseTimeMs);
  TIMEMS_TO_COEFF(p->m_oneMinusLevelAttackCoeff, p->m_levelAttackCoeff,
                  p->m_opt.m_levelAttackTimeMs);
  TIMEMS_TO_COEFF(p->m_oneMinusLevelReleaseCoeff, p->m_levelReleaseCoeff,
                  p->m_opt.m_levelReleaseTimeMs);
  p->m_cSamplesForRelease = FLOAT_TO_DRCTCC(1.0f)/p->m_releaseCoeff;
  p->m_cSamplesForAttack = FLOAT_TO_DRCTCC(1.0f)/p->m_attackCoeff;
#undef TIMES_TO_COEFF
#if 0 // "Digital Audio Signal Processing" book uses this
  if (p->m_fUsePeakVal) { 
    p->m_oneMinusLevelAttackCoeff -= p->m_levelReleaseCoeff;
    p->m_levelReleaseCoeff = (DRCType)0.0;
  }
#endif
  //WMAPrintf("AttackCoeff=%f Release=%f LevelAttack=%f LevelRelease\n",
  //       p->m_attackCoeff, p->m_releaseCoeff, p->m_levelAttackCoeff,
  //       p->m_levelReleaseCoeff);
  // ====================================================================

  // ====================================================================
  // Set rms, peak, etc... in dB

  // check if values do exist
  if (pd->dataFormatRms == PostProcDrcDataInNormU16) {
    if (pd->rms.normVal <= 0) {
      p->m_opt.m_fNormalizeRms = WMAB_FALSE; // don't know what to do
    }
  }
  if (pd->dataFormatPeak == PostProcDrcDataInNormU16) {
    if (pd->peak.normVal <= 0) {
      pd->dataFormatPeak = PostProcDrcDataInDb;
      pd->peak.dB = (DRCDbType)0.0;
    }
  }
  if (po->m_dataFormatRms == PostProcDrcDataInNormU16) {
    if (po->m_desiredRms.normVal <= 0) {
      po->m_dataFormatRms = pd->dataFormatRms;
      memcpy(&po->m_desiredRms, &pd->rms, sizeof(PostProcDrcDataFormatVal));
    }
  }
  if (po->m_dataFormatPeak == PostProcDrcDataInNormU16) {
    if (po->m_desiredPeak.normVal <= 0) {
      po->m_dataFormatPeak = pd->dataFormatPeak;
      memcpy(&po->m_desiredPeak, &pd->peak, sizeof(PostProcDrcDataFormatVal));
    }
  }

  if (p->m_opt.m_fNormalizeRms) {
    TRACEWMA_EXIT(wr, drcDataFormatToDb(&rmsValDb, pd->rms,
                                        pd->dataFormatRms,
                                        nValidBitsPerSample));
    TRACEWMA_EXIT(wr, drcDataFormatToDb(&peakValDb, pd->peak,
                                        pd->dataFormatPeak,
                                        nValidBitsPerSample));
    TRACEWMA_EXIT(wr, drcDataFormatToDb(&desiredRmsDb[0], po->m_desiredRms,
                                        po->m_dataFormatRms,
                                        nValidBitsPerSample));
    TRACEWMA_EXIT(wr, drcDataFormatToDb(&desiredPeakDb[0], po->m_desiredPeak,
                                        po->m_dataFormatPeak,
                                        nValidBitsPerSample));
    // If imaginary data provided, no drc
    if (peakValDb < rmsValDb ||
        desiredPeakDb[0] < desiredRmsDb[0])
      p->m_opt.m_fNormalizeRms = WMAB_FALSE;
  }

  if (!p->m_opt.m_fDRCDecode ||
      (p->m_opt.m_fDRCDecode &&
       p->m_opt.m_fNormalizeRms &&
       p->m_opt.m_fUseDRCOnNormalize)) {
    p->m_nScaleTables = 1;
  }

  if (p->m_opt.m_fNormalizeRms) {
    if (p->m_opt.m_fUseWmaDefaults) { // adjust as needed to get good affect
      DRCDbType dynamicRange;
      if (rmsValDb == desiredRmsDb[0] &&
          peakValDb == desiredPeakDb[0]) { // to get 12 dB
        desiredPeakDb[0] = min(0, rmsValDb + PEAKTORMS_MED_DB);
      }
      // get desired peak for low setting
      desiredRmsDb[1] = desiredRmsDb[0];
      dynamicRange = desiredPeakDb[0] - desiredRmsDb[0];
      assert(dynamicRange >= (DRCDbType)0.0);
#ifdef DRC_BUILD_INTEGER_TABLE
      desiredPeakDb[1] = desiredRmsDb[1] + (dynamicRange >> 1);
#else
      desiredPeakDb[1] = desiredRmsDb[1] + dynamicRange/2.0;
#endif
      {
        DRCDbType boost;
        boost = drcBoostPeakChop(rmsValDb, desiredRmsDb[0],
                                 peakValDb, desiredPeakDb[0]);
        desiredRmsDb[0] = min(0, desiredRmsDb[0]+boost);
        desiredPeakDb[0] = min(0, desiredPeakDb[0]+boost);
        boost = drcBoostPeakChop(rmsValDb, desiredRmsDb[1],
                                 peakValDb, desiredPeakDb[1]);
        desiredRmsDb[1] = min(0, desiredRmsDb[1]+boost);
        desiredPeakDb[1] = min(0, desiredPeakDb[1]+boost);
      }
      // set for 2 tables
      p->m_nScaleTables = 2;
    }
  }

  // allocate table buffers ------------------------------------------------
  if (p->m_nScaleTables > 0) {
    p->m_scaleFactor = (DRCType*)auMalloc(p->m_nScaleTables * sizeof(DRCType));
    CHECK_ALLOC(p->m_scaleFactor);
    memset(p->m_scaleFactor, 0, p->m_nScaleTables * sizeof(DRCType));

    p->m_fNeedDRCOnNormalize = (Bool*)auMalloc(p->m_nScaleTables*sizeof(Bool));
    CHECK_ALLOC(p->m_fNeedDRCOnNormalize);
    memset(p->m_fNeedDRCOnNormalize, 0, p->m_nScaleTables * sizeof(Bool));

    p->m_intSlopeShiftBits = (I32*)auMalloc(p->m_nScaleTables*sizeof(I32));
    CHECK_ALLOC(p->m_intSlopeShiftBits);
    memset(p->m_intSlopeShiftBits, 0, p->m_nScaleTables * sizeof(I32));

    p->m_maxPeakValDec = (DRCType*)auMalloc(p->m_nScaleTables*sizeof(DRCType));
    CHECK_ALLOC(p->m_maxPeakValDec);
    memset(p->m_maxPeakValDec, 0, p->m_nScaleTables * sizeof(DRCType));
  }

  if (p->m_opt.m_fUseTables) {
    if (!p->m_opt.m_fDRCDecode ||
        (p->m_opt.m_fDRCDecode &&
         p->m_opt.m_fNormalizeRms &&
         p->m_opt.m_fUseDRCOnNormalize)) {
      assert(p->m_nScaleTables > 0);
      p->m_scaleTable =
        (DRCType**)auMalloc(p->m_nScaleTables*sizeof(DRCType*));
      CHECK_ALLOC(p->m_scaleTable);
      memset(p->m_scaleTable, 0, p->m_nScaleTables*sizeof(DRCType*));
      p->m_scaleTableBase =
        (DRCType**)auMalloc(p->m_nScaleTables*sizeof(DRCType*));
      CHECK_ALLOC(p->m_scaleTableBase);
      memset(p->m_scaleTableBase, 0, p->m_nScaleTables*sizeof(DRCType*));
      p->m_scaleSlopeTable =
        (DRCType**)auMalloc(p->m_nScaleTables*sizeof(DRCType*));
      CHECK_ALLOC(p->m_scaleSlopeTable);
      memset(p->m_scaleSlopeTable, 0, p->m_nScaleTables*sizeof(DRCType*));
      p->m_scaleSlopeTableBase =
        (DRCType**)auMalloc(p->m_nScaleTables*sizeof(DRCType*));
      CHECK_ALLOC(p->m_scaleSlopeTableBase);
      memset(p->m_scaleSlopeTableBase, 0, p->m_nScaleTables*sizeof(DRCType*));
    }
  }

  if (p->m_nScaleTables>1 && !p->m_opt.m_fUseTables) { // besides table, only one set of variables stored for gain, linear threshold, ratio...
    assert(false);
    wr = WMA_E_NOTSUPPORTED;
    goto exit;
  }

  // calculate parameters for rms normalization, peak clipping ======
  fNormalizeRms = false;
  for (i=0; i < p->m_nScaleTables; i++) {
    p->m_gainDb = 0;
    p->m_linearThresholdDb = 0;
    p->m_ratioDb = 0;
    p->m_fNeedDRCOnNormalize[i] = false;
    if (p->m_opt.m_fNormalizeRms) { // set up gain, threshold, ratio...
      DRCDbType clipDb;
      desiredRmsDb[i] = min(desiredRmsDb[i], 0);
      desiredPeakDb[i] = min(desiredPeakDb[i], 0);
      p->m_gainDb = desiredRmsDb[i] - rmsValDb;
      clipDb = desiredPeakDb[i] - peakValDb;
      p->m_scaleFactor[i] = (DRCType) drcDbToScale(p->m_gainDb);
      // if no rms normalization (gaindb=0) and
      // no peak clipping (desiredpeak > peak ==> clipDb > 0)
      // then no rms normalization needed
      if (p->m_gainDb > FLOAT_TO_DRCDB(-0.01) &&
          p->m_gainDb < FLOAT_TO_DRCDB(0.01) &&
          clipDb > FLOAT_TO_DRCDB(-0.01)) {
      } else {
        fNormalizeRms = true;
      }
      if (p->m_gainDb + peakValDb >= desiredPeakDb[i]) {
        p->m_linearThresholdDb =
          desiredPeakDb[i] + p->m_opt.m_clipThresholdYDb - p->m_gainDb;
        p->m_ratioDb = DIV_DRCDB_CHECK(p->m_opt.m_clipThresholdYDb,
                                       p->m_linearThresholdDb);
        p->m_fNeedDRCOnNormalize[i] = p->m_opt.m_fUseDRCOnNormalize;
      }
    }
    if (!p->m_opt.m_fDRCDecode ||
        (p->m_opt.m_fDRCDecode && p->m_fNeedDRCOnNormalize[i])) {
      wr = drcCreateScaleTables(p, i);
      if (WMA_FAILED(wr)) goto exit;
    }
  }
  p->m_opt.m_fNormalizeRms = fNormalizeRms;

  // ===================================================================
  // Set peak values
#if 1
  p->m_maxPeakValEnc = (DRCType)MAX_PEAKVAL;
#else
  p->m_maxPeakValEnc =
    (DRCType)MULT_DRCSCALE(MAX_PEAKVAL,
      drcDbToScale(MULT_DRCDB(opt.thresholdDb,
                              (FLOAT_TO_DRCDB(1.0)-opt.ratioDb)) +
                   opt.gainDb));
#endif
  for (i=0; i < p->m_nScaleTables; i++) {
#if 1
    p->m_maxPeakValDec[i] = (DRCType)MAX_PEAKVAL;
    if (p->m_opt.m_fNormalizeRms) {
      p->m_maxPeakValDec[i] =
        (DRCType)MULT_DRCSCALE(MAX_PEAKVAL,
                               drcDbToScale(desiredPeakDb[i]));
    }
#else
    p->m_maxPeakValDec[i] =
      (DRCType)MULT_DRCSCALE(MAX_PEAKVAL,
        drcDbToScale(MULT_DRCDB(opt.thresholdDb,
                                (FLOAT_TO_DRCDB(1.0)-opt.ratioDb)) +
                     opt.gainDb));
#endif
  }

  // ====================================================================
  // Create decoder unquantization tables

  if (p->m_opt.m_fDRCDecode) {
#ifdef DRC_DECODE_USE_TABLES
    if (p->m_opt.m_fDRC) {
      wr = drcCreateUnquantTables(p);
      if (WMA_FAILED(wr)) goto exit;
    }
#endif
    if (!p->m_opt.m_fNormalizeRms) {
      for (i=0; i < p->m_nScaleTables; i++)
        p->m_scaleFactor[i] = (DRCType)FLOAT_TO_DRCSCALE(1.0);
    }
  }

  if (p->m_opt.m_fUseTables) { // done with drc curve, delete to save memory
    DRCFREE(p->m_opt.m_pDRCCurve);
    p->m_opt.m_pDRCCurve = NULL;
    p->m_opt.m_nDRCCurvePoints = 0;
  }

  // Initialize some parameters ==========================================
  p->m_curLevel = (DRCType)FLOAT_TO_DRCLEVEL(0.0);
  p->m_curScaleFactor = (DRCType)FLOAT_TO_DRCSCALE(1.0);

  // ======================================================================

  // calculate lookahead
  p->m_lookaheadCount = 0;
  if (p->m_opt.m_fUseLookahead) {
#ifdef DRC_BUILD_INTEGER_TABLE
    p->m_nLookahead =
      DRCTC_TO_INT(p->m_opt.m_lookaheadWindowMs*samplingRate/1000);
#else
    p->m_nLookahead = ROUNDD(p->m_opt.m_lookaheadWindowMs*samplingRate/1000.0f);
#endif
  } else {
    p->m_nLookahead = 0;
  }
  //p->m_nLookahead = 9;
  //WMAPrintf("lookahead = %d\n", p->m_nLookahead);

  // Set parameters for window averaging method
  if (p->m_opt.m_fUseAvgWindow) {
    if (!p->m_opt.m_fUseLinInterpGainAvgWindow)
      p->m_windowSize = p->m_nLookahead+1;
    else {
      p->m_windowSize = (p->m_nLookahead+1)/2;
      p->m_floorHalfWindowSize = p->m_windowSize/2;
    }
    p->m_windowCount = 0;
    p->m_prevLevel = (DRCType)0;
    p->m_windowPeakLevel = (DRCType)0;
    if (p->m_opt.m_fUseLinInterpGainAvgWindow) {
      p->m_scaleFactor0 = (DRCType)FLOAT_TO_DRCSCALE(1.0);
      p->m_scaleFactor1 = (DRCType)FLOAT_TO_DRCSCALE(1.0);
      p->m_scaleFactor0Slope = (DRCType)0;
      p->m_scaleFactor1Slope = (DRCType)0;
    }
  }
  //WMAPrintf("window size = %d\n", p->m_windowSize);

exit:
  return wr;
}

INLINE void drcGetSamples(const DRC *p, I32 *samples, U8 *buf)
{
  int i;
  for (i=0; i < p->m_nChannels; i++) {
    DRC_GET_SAMPLE(samples[i], buf);
    DRC_ADVANCE_PTR(buf);
  }
}

INLINE void drcPutSamples(const DRC *p, I32 *samples, U8 *buf)
{
  int i;
  for (i=0; i < p->m_nChannels; i++) {
    DRC_PUT_SAMPLE(samples[i], buf);
    DRC_ADVANCE_PTR(buf);
  }
}

INLINE void drcAdvanceBuffer(const DRC *p, U8 **buf)
{
  DRC_ADVANCE_PTR_N(*buf, p->m_nChannels);
}

#if 0

WMARESULT drcCalcMsAndPeak(DRC *p, U8 *buffer, Int numSampleBlocks)
{
  WMARESULT wr = WMA_OK;
  int i, j;
  Double sample, rms;
  I32 abssample;

  if (p->m_nChannels != 1 && p->m_nChannels != 2 && p->m_nChannels != 6) {
    wr = WMA_E_NOTSUPPORTED;
    goto exit;
  }

  rms = 0.0;

  for (i=0; i < numSampleBlocks; i++) {
    drcGetSamples(p, p->m_curSamples, buffer);
    // could use getMaxSample, but max of max is slower...
    for (j=0; j < p->m_nChannels; j++) {
      abssample = p->m_curSamples[j];
      if (abssample < 0) abssample = -abssample;
      if (abssample > p->m_actualPeak) p->m_actualPeak = abssample;
    }
    // get mono sample
    sample = getMonoAbsSample(p->m_curSamples, p->m_nChannels);
    drcAdvanceBuffer(p, &buffer);

#if 0
    abort(); // CHECKCHECK -- not work currently
    p->m_curRmsVal = p->m_rmsCoeff*sample*sample +
      (1-p->m_rmsCoeff)*p->m_curRmsVal;
    rms += p->m_curRmsVal;
#else
    rms += sample*sample;
#endif
  }

  p->m_actualRms =
    (p->m_actualRms*p->m_numSampleBlocks + rms) /
    ((Double)p->m_numSampleBlocks + (Double)numSampleBlocks);

  p->m_numSampleBlocks += numSampleBlocks;

exit:
  return wr;
}

#endif

INLINE DRCType drcGetScaleFactorTable(const DRC *p, const I32 sample,
                                      const Int nTable)
{
  I32 index = sample >> REM_SCALE_BITS;
  I32 rem = sample & REM_SCALE_MASK;

  assert(index < TABLE_SCALE_SIZE);

#ifdef DRC_BUILD_INTEGER_TABLE
  return
    p->m_scaleTable[nTable][index] +
    (((DRCType)rem*p->m_scaleSlopeTable[nTable][index])>>p->m_intSlopeShiftBits[nTable]);
#else
  return
    p->m_scaleTable[nTable][index] +
    (DRCType)rem*p->m_scaleSlopeTable[nTable][index];
#endif
}

INLINE DRCType drcGetScaleFactorFTable(const DRC *p, const DRCType abssample,
                                       const Int nTable)
{
  return drcGetScaleFactorTable(p, drcTypeToI32(abssample), nTable);
}

// this is not integerized and is not needed for wma
// encoder/decoder implementation
#ifndef DRC_BUILD_INTEGER_TABLE

INLINE DRCType getCurAbsSample(DRC *p, I32 *samples)
{
  DRCType sample;
#ifdef USE_AVG_WINDOW
  DRCType newScaleFactor;
#endif

  if (p->m_opt.m_fUseMonoChannel)
    sample = getMonoAbsSample(samples, p->m_nChannels);
  else
    sample = (DRCType)getMaxAbsSample(samples, p->m_nChannels);

#ifdef USE_AVG_WINDOW
  if (p->m_opt.m_fUseAvgWindow) {
    if (sample > p->m_windowPeakLevel) p->m_windowPeakLevel = sample;
    p->m_curLevel += sample*sample;
    p->m_windowCount++;
    if (p->m_windowCount == p->m_windowSize) {
      p->m_windowCount = 0;
      p->m_curLevel = (DRCType)sqrt(p->m_curLevel/p->m_windowSize);

      newScaleFactor = drcGetScaleFactorFTable(p, p->m_curLevel, 0);
#if 0
      if (newScaleFactor*p->m_windowPeakLevel >= p->m_maxPeakValEnc)
        newScaleFactor = p->m_maxPeakValEnc / p->m_windowPeakLevel;
#endif
      p->m_scaleFactor0 = p->m_scaleFactor1;
      p->m_scaleFactor1 = newScaleFactor;
      p->m_scaleFactor0Slope = p->m_scaleFactor1Slope;
      p->m_scaleFactor1Slope = (p->m_scaleFactor1 - p->m_scaleFactor0) /
        (DRCType)p->m_windowSize;

      p->m_prevLevel = p->m_curLevel;
      p->m_curLevel = (DRCType)0;
      p->m_windowPeakLevel = (DRCType)0;
      //WMAPrintf("level = %f\n", p->m_prevLevel);
    }
    //WMAPrintf("count = %d level = %f\n", p->m_windowCount, p->m_prevLevel);
    return p->m_prevLevel;
  }
#endif

  // Use current RMS value
  if (p->m_opt.m_fUseRmsVal) {
    if (sample > p->m_curLevel) {
      p->m_curLevel = (DRCType)sqrt(p->m_levelAttackCoeff*sample*sample +
                p->m_oneMinusLevelAttackCoeff*p->m_curLevel*p->m_curLevel);
    } else {
      p->m_curLevel = (DRCType)sqrt(p->m_levelReleaseCoeff*sample*sample +
                p->m_oneMinusLevelReleaseCoeff*p->m_curLevel*p->m_curLevel);
    }
    return p->m_curLevel;
  }

  // Use current peak value
  if (p->m_opt.m_fUsePeakVal) {
    if (sample > p->m_curLevel) {
      p->m_curLevel = p->m_levelAttackCoeff*sample +
        p->m_oneMinusLevelAttackCoeff*p->m_curLevel;
    } else {
      p->m_curLevel = p->m_levelReleaseCoeff*sample +
        p->m_oneMinusLevelReleaseCoeff*p->m_curLevel;
    }
    return p->m_curLevel;
  }

  // use current sample
  return sample;
}

#define getCurAbsISample(p, samples) \
  drcTypeToSample(getCurAbsSample(p, samples))

#endif // #ifndef DRC_BUILD_INTEGER_TABLE

#ifdef ADJUST_FOR_CLIP
//#pragma warning(push)
INLINE void drcAdjustGainForClip(DRC *p, const I32 abssample,
                                 const DRCType maxVal)
{
  // immediate reduction regardless of attack/release coeffs.
  // same as attack time of 0, on overshoots
//#pragma warning(disable : 4723)
  if (MULT_DRCSCALE(abssample, p->m_curScaleFactor) >= maxVal &&
      abssample != 0) {
    p->m_curScaleFactor = DIV_LEVEL_TO_SCALE64(maxVal, abssample);
  }
}
//#pragma warning(pop)
#else
#define drcAdjustGainForClip(p, abssample, maxVal)
#endif

INLINE DRCType drcSmoothGain(DRC *p, DRCType desiredScaleFactor,
                             const I32 abssample, const DRCType maxVal)
{
#ifdef USE_AVG_WINDOW
  if (p->m_opt.m_fUseLinInterpGainAvgWindow) {
    if (p->m_windowCount == p->m_floorHalfWindowSize)
      p->m_curScaleFactor = p->m_scaleFactor0; // reset prevents drift error
    else if (p->m_windowCount < p->m_floorHalfWindowSize)
      p->m_curScaleFactor += p->m_scaleFactor0Slope;
    else
      p->m_curScaleFactor += p->m_scaleFactor1Slope;
    drcAdjustGainForClip(p, abssample, maxVal);
    return p->m_curScaleFactor;
  }

  if (p->m_opt.m_fUseAvgWindow) {
    desiredScaleFactor = p->m_scaleFactor1;
  }
#endif

  if (!p->m_opt.m_fSmoothGain) return desiredScaleFactor;
  else {
#if 1
    if (desiredScaleFactor <= p->m_curScaleFactor) {
      p->m_curScaleFactor =
        MULT_DRCTCC2(p->m_attackCoeff, desiredScaleFactor,
                     p->m_oneMinusAttackCoeff, p->m_curScaleFactor);
    } else {
      p->m_curScaleFactor =
        MULT_DRCTCC2(p->m_releaseCoeff, desiredScaleFactor,
                     p->m_oneMinusReleaseCoeff, p->m_curScaleFactor);
    }
#else
    if (fAboveThreshold) {
      p->m_curScaleFactor =
        MULT_DRCTCC2(p->m_attackCoeff ,desiredScaleFactor,
                     p->m_oneMinusAttackCoeff, p->m_curScaleFactor);
    } else {
      p->m_curScaleFactor =
        MULT_DRCTCC2(p->m_releaseCoeff, desiredScaleFactor,
                     p->m_oneMinusReleaseCoeff, p->m_curScaleFactor);
    }
#endif
    drcAdjustGainForClip(p, abssample, maxVal);
    return p->m_curScaleFactor;
  }
}

INLINE DRCType drcSmoothGain2(DRC *p, DRCType desiredScaleFactor,
                              const I32 abssample, const DRCType maxVal,
                              Int cJump)
{
  if (!p->m_opt.m_fSmoothGain) return desiredScaleFactor;
  else {
    if (desiredScaleFactor <= p->m_curScaleFactor) {
      if (cJump >= p->m_cSamplesForAttack) return desiredScaleFactor;
      p->m_curScaleFactor =
        MULT_DRCTCC2(p->m_attackCoeff*cJump, desiredScaleFactor,
           FLOAT_TO_DRCTCC(1.0)-p->m_attackCoeff*cJump, p->m_curScaleFactor);
    } else {
      if (cJump >= p->m_cSamplesForRelease) return desiredScaleFactor;
      p->m_curScaleFactor =
        MULT_DRCTCC2(p->m_releaseCoeff*cJump, desiredScaleFactor,
           FLOAT_TO_DRCTCC(1.0)-p->m_releaseCoeff*cJump, p->m_curScaleFactor);
    }

    // Do not reduce the scale factor here if clipping occurs - this causes pops in the 
    // decoded file. Instead, apply soft clipping if required after scaling.
#if 0
    // same as attack time of 0, on overshoots
    if (MULT_DRCSCALE(abssample, p->m_curScaleFactor) >= maxVal) {
      p->m_curScaleFactor = DIV_LEVEL_TO_SCALE64(maxVal, abssample);
    }
#endif
    return p->m_curScaleFactor;
  }
}

#ifndef DRC_BUILD_INTEGER_TABLE

Bool drcLookaheadInit(DRC *p,
                      U8 *buffer,
                      Int numSampleBlocksIn)
{
  int i;
  I32 abssample;

  DRCType drcscale;

  if (!p->m_opt.m_fUseLookahead) goto returnTrue;
  if (p->m_nLookahead == p->m_lookaheadCount) goto returnTrue;

  for (i=0; i < numSampleBlocksIn; i++) {
    drcGetSamples(p, p->m_curSamples, buffer);
    drcAdvanceBuffer(p, &buffer);
    abssample = getCurAbsISample(p, p->m_curSamples);
    drcscale = drcGetScaleFactorTable(p, abssample, 0);
    drcscale = drcSmoothGain(p, drcscale, 0, p->m_maxPeakValDec[0]);
    p->m_lookaheadCount++;
    if (p->m_nLookahead == p->m_lookaheadCount) goto returnTrue;
  }

  return false;

returnTrue:
  return true;
}

#endif // DRC_BUILD_INTEGER_TABLE

#define DRC_DECODE_LSL
#include "drcprotemplate.c"
#undef DRC_DECODE_LSL
#define DRC_DECODE_PRO
#include "drcprotemplate.c"
#undef DRC_DECODE_PRO

// returns a scale factor
U8 drcEncode(DRC *p, Float frameRmsValue)
{
  I32 val;
#ifndef DRC_BUILD_INTEGER_TABLE
  // in 32 bit data, there is potential for overflow, since frameRmsValue
  // might be close to maximum, in such cases divide first, then convert to int
  if (p->m_amtToLeftShift >= 0) {
    val = drcTypeToI32((DRCType)frameRmsValue);
    val <<= p->m_amtToLeftShift;
  } else { // > 24 bit data, divide then convert
    val = drcTypeToI32((DRCType)frameRmsValue/
                       (DRCType)(1<<-p->m_amtToLeftShift));
  }
#else
  val = drcTypeToI32((DRCType)frameRmsValue);
  if (p->m_amtToLeftShift >= 0)
    val <<= p->m_amtToLeftShift;
  else
    val >>= -p->m_amtToLeftShift;
#endif
  // check to make sure within range, may exceed maximum depending on accuracy
  // of computation
  val = checkRange(val, MIN_INT24SAMPLE, MAX_INT24SAMPLE);
#if 0
  {
    DRCType s = drcGetScaleFactorTable(p, val, 0);
    U8 qs = quantScaleFactor(s);
    WMAPrintf("Val=%d Scale=%f QScale=%d UQScale=%f\n", val,
              (float)s*DRC_SCALE, qs,
              (float)unquantScaleFactor(p, qs)*DRC_SCALE);
    return qs;
  }
#else
  return quantScaleFactor(drcGetScaleFactorTable(p, val, 0));
#endif
}

// Optimizations for get routines used by following codepaths =========

#ifdef ADJUST_FOR_CLIP
#  define GET_CUR_MAX_SAMPLE \
     { maxSample = getMaxAbsSample(p->m_curSamples, p->m_nChannels); }
#else
#  define GET_CUR_MAX_SAMPLE { maxSample = 0; }
#endif

// decode and normalize using scale factor -- faster to do both at once
WMARESULT drcDecode(DRC *p,
                    U8 quantScaleFactor,
                    U8 *buffer,
                    Int numSampleBlocksIn,
                    Int nDRCSetting)
{
  WMARESULT wr = WMA_OK;
  Int i, j;
  DRCType scaleFactor, actScaleFactor, sampleScaleFactor;
  I32 maxSample;
  Int nDRCPos;
  DRCType maxPeakValDec;

  if (NULL == buffer) goto exit;  // just to be safe

  switch (nDRCSetting) {
  case WMA_DRC_HIGH:  goto exit;
  case WMA_DRC_MED:  nDRCPos = WMA_DRC_MED_POS; break;
  case WMA_DRC_LOW:  nDRCPos = WMA_DRC_LOW_POS; break;
  default: assert(false);  wr = WMA_E_INVALIDARG;  goto exit;
  }

  if (!p->m_opt.m_fNormalizeRms && !p->m_opt.m_fDRC) goto exit;

  if (!p->m_opt.m_fDRC) {
    scaleFactor = (DRCType)1.0;
  } else {
#ifdef DRC_DECODE_USE_TABLES
    scaleFactor = g_drcIndexToSF[quantScaleFactor];
#else
    scaleFactor = unquantScaleFactor(p, quantScaleFactor);
#endif
  }

  if (p->m_opt.m_fNormalizeRms && p->m_fNeedDRCOnNormalize[nDRCPos]) {
    for (i=0; i < numSampleBlocksIn; i++) {
      drcGetSamples(p, p->m_curSamples, buffer);
      maxSample = getMaxAbsSample(p->m_curSamples, p->m_nChannels);
      sampleScaleFactor =
        MULT_DRCSCALE(scaleFactor, drcGetScaleFactorFTable(p,
          MULT_DRCSCALE((DRCType)maxSample, scaleFactor), nDRCPos));
      actScaleFactor = drcSmoothGain(p, sampleScaleFactor, maxSample,
                                     p->m_maxPeakValDec[nDRCPos]);
#if 0
      {
        static FILE *fp = NULL;
#ifdef DRC_BUILD_INTEGER_TABLE
        if (fp == NULL) fp = FOPEN("g:/scalefac.int", "wt");
#else
        if (fp == NULL) fp = FOPEN("g:/scalefac.flt", "wt");
#endif // DRC_BUILD_INTEGER_TABLE
        WMAFprintf(fp, "%f %f %f\n",
                DRCSCALE_TO_FLOAT(scaleFactor),
                DRCSCALE_TO_FLOAT(sampleScaleFactor),
                DRCSCALE_TO_FLOAT(actScaleFactor));
      }
#endif // 0
      for (j=0; j < p->m_nChannels; j++) {
        p->m_curSamples[j] = drcMultRange(p->m_curSamples[j], actScaleFactor);
      }
      drcPutSamples(p, p->m_curSamples, buffer);
      drcAdvanceBuffer(p, &buffer);
    }
  } else if (p->m_opt.m_fNormalizeRms || p->m_opt.m_fDRC) {
    // multiple by fixed scale factor if normalizing rms but not
    //   using drc on normalization
    if (p->m_opt.m_fNormalizeRms) {
      sampleScaleFactor =
        MULT_DRCSCALE(scaleFactor, p->m_scaleFactor[nDRCPos]);
      maxPeakValDec = p->m_maxPeakValDec[nDRCPos];
    } else {
      sampleScaleFactor = scaleFactor;
      maxPeakValDec = MAX_PEAKVAL;
    }
    for (i=0; i < numSampleBlocksIn; i++) {
      drcGetSamples(p, p->m_curSamples, buffer);
      GET_CUR_MAX_SAMPLE;
      actScaleFactor = drcSmoothGain(p, sampleScaleFactor, maxSample,
                                     maxPeakValDec);
      for (j=0; j < p->m_nChannels; j++) {
        p->m_curSamples[j] = drcMultRange(p->m_curSamples[j], actScaleFactor);
      }
      drcPutSamples(p, p->m_curSamples, buffer);
      drcAdvanceBuffer(p, &buffer);
    }
  }

exit:
  return wr;
}

#ifndef DRC_BUILD_INTEGER_TABLE

WMARESULT drcProcess(DRC *p,
                     U8 *buffer,
                     Int numSampleBlocksIn,
                     Int *pNumSampleBlocksProcessed)
{
  WMARESULT wr = WMA_OK;
  Int i, j, numSampleBlocks;
  Double absvalDb, dAbssample;
  DRCType scaleFactor;
  I32 abssample, maxSample;
  U8 *lookaheadBuffer;

  if (p->m_opt.m_fUseLookahead && (p->m_lookaheadCount != p->m_nLookahead)) {
    return WMA_E_FAIL;
  }

  if (numSampleBlocksIn < drcMinBufSize(p)) {
    numSampleBlocks = numSampleBlocksIn;
  } else {
    numSampleBlocks = numSampleBlocksIn - p->m_nLookahead;
  }
  *pNumSampleBlocksProcessed = numSampleBlocks;

  lookaheadBuffer = buffer;
  DRC_ADVANCE_PTR_N(lookaheadBuffer, p->m_nChannels*p->m_nLookahead);

  // Flush ===============================================================

  if (numSampleBlocksIn < drcMinBufSize(p)) {
    for (i=0; i < numSampleBlocks; i++) {
      drcGetSamples(p, p->m_curSamples, buffer);
      GET_CUR_MAX_SAMPLE;
      scaleFactor = drcSmoothGain(p, (DRCType)1.0, maxSample,
                                  p->m_maxPeakValDec[0]);
      for (j=0; j < p->m_nChannels; j++) {
        p->m_curSamples[j] = drcMultRange(p->m_curSamples[j], scaleFactor);
      }
      drcPutSamples(p, p->m_curSamples, buffer);
      drcAdvanceBuffer(p, &buffer);
    }
  }

  // Scale factor using table ============================================

  else if (p->m_opt.m_fUseTables) {
    for (i=0; i < numSampleBlocks; i++) {
      drcGetSamples(p, p->m_curSamples, buffer);
      drcGetSamples(p, p->m_lookaheadSamples, lookaheadBuffer);
      abssample = getCurAbsISample(p, p->m_lookaheadSamples);
      GET_CUR_MAX_SAMPLE;
      scaleFactor = drcGetScaleFactorTable(p, abssample, 0);
#ifdef FPRINT_SFAC
      WMAFprintf(fsfac, "%f\n", scaleFactor);
#endif
      scaleFactor = drcSmoothGain(p, scaleFactor, maxSample,
                                  p->m_maxPeakValDec[0]);
      assert(scaleFactor != 0);
#ifdef FPRINT_SFAC
      WMAFprintf(fssfac, "%f ", scaleFactor);
#endif
      for (j=0; j < p->m_nChannels; j++) {
#if 1 && defined(FPRINT_SFAC)
        I32 sample;
        sample = p->m_curSamples[j];
#endif
        p->m_curSamples[j] = drcMultRange(p->m_curSamples[j], scaleFactor);
#if 0
        if (p->m_curSamples[j] == MIN_INT24SAMPLE ||
            p->m_curSamples[j] == MAX_INT24SAMPLE) {
          WMAPrintf("Bad\n");
        }
#endif
#if 1 && defined(FPRINT_SFAC)
        WMAFprintf(fssfac, "%f ", (DRCType)p->m_curSamples[j]/sample);
#endif
      }
#if 1 && defined(FPRINT_SFAC)
      WMAFprintf(fssfac, "\n");
#endif
      drcPutSamples(p, p->m_curSamples, buffer);
      drcAdvanceBuffer(p, &lookaheadBuffer);
      drcAdvanceBuffer(p, &buffer);
    }
  }

  // No tables ==========================================================

  else {
    for (i=0; i < numSampleBlocks; i++) {
      drcGetSamples(p, p->m_curSamples, buffer);
      drcGetSamples(p, p->m_lookaheadSamples, lookaheadBuffer);
      dAbssample = getCurAbsSample(p, p->m_lookaheadSamples);
      GET_CUR_MAX_SAMPLE;
      absvalDb = drcInt24DToDb(dAbssample);
      scaleFactor = (DRCType)drcGetScaleFactor(p, absvalDb);
      scaleFactor = drcSmoothGain(p, scaleFactor, maxSample,
                                  p->m_maxPeakValDec[0]);
      for (j=0; j < p->m_nChannels; j++) {
        p->m_curSamples[j] = drcMultRange(p->m_curSamples[j], scaleFactor);
      }
      drcPutSamples(p, p->m_curSamples, buffer);
      drcAdvanceBuffer(p, &lookaheadBuffer);
      drcAdvanceBuffer(p, &buffer);
    }
  }

  return wr;
}

#endif // #ifndef DRC_BUILD_INTEGER_TABLE

//#pragma warning(pop) // warning 4723

#if defined(_SH4_)
#pragma warning(pop) // warning 4719
#endif

#endif // BUILD_WMAPRO
