//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*  -*-c++-*-
 *  Sanjeev Mehrotra
 *  2001/10/03
 */

#ifndef _DRCCOMMON_H
#define _DRCCOMMON_H

#include "wavfileexio.h"

#ifndef STANDALONE_POSTPROCDRC
#include "msaudio.h"
#else // STANDALONE_POSTPROCDRC
#include "wmamalloc.h"
#endif // STANDALONE_POSTPROCDRC

#if defined(BUILD_INTEGER)
#define DRC_BUILD_INTEGER_TABLE
#endif

// use integer math (even in float build)
#define DRC_BUILD_INTEGER_TABLE

#if defined (BUILD_WMAPRO)
#ifdef DRC_BUILD_INTEGER_TABLE

#define DRCDataType I32

#define FLOAT_TO_DRCT(x, bits) ((I32)((x)*(1<<bits)))
#define DOUBLE_TO_DRCT(x, bits) FLOAT_TO_DRCT(x, bits)
#define INT_TO_DRCT(x, bits) ((x)<<bits)
#define DRCT_TO_FLOAT(x, bits) ((Float)(x)/(Float)(1<<bits))
#define DRCT_TO_DOUBLE(x, bits) ((Double)(x)/(Double)(1<<bits))
#define DRCT_TO_INT(x, bits) ((x) >> bits)
#define MULT_DRCT(a, b, bits) ((I32)(((I64)(a)*(I64)(b))>>bits))
// bug 13374. need to right-shift (a) instead of left-shift (b) to avoid rounding
#define DIV_DRCT(a, b, bits, divbits) ((I32)((((I64)(a)<<(divbits))/(b))<<(bits-divbits)))
#define DIV_DRCT_CHECK(a, b, bits, divbits) \
  ( ((b)>>divbits == 0) ? 0 : DIV_DRCT(a, b, bits, divbits) )

#else

#define DRCDataType Double

#define FLOAT_TO_DRCT(x, bits) (x)
#define DOUBLE_TO_DRCT(x, bits) (x)
#define INT_TO_DRCT(x, bits) (x)
#define DRCT_TO_FLOAT(x, bits) ((Float)(x))
#define DRCT_TO_DOUBLE(x, bits) ((Double)(x))
#define DRCT_TO_INT(x, bits) (x)
#define MULT_DRCT(a, b, bits) ((a)*(b))
#define DIV_DRCT(a, b, bits, divbits) ((a)/(b))
#define DIV_DRCT_CHECK(a, b, bits, divbits) \
  ( ((b)==0) ? 0 : DIV_DRCT(a, b, bits, divbits) )

#endif

// used for representing db's
#define DRCDbType DRCDataType
// only used in integer builds
#define DRC_DB_BITS (20) // precision bits
#define DRC_DB_DIV_BITS (10)
#define FLOAT_TO_DRCDB(x) FLOAT_TO_DRCT(x, DRC_DB_BITS)
#define DOUBLE_TO_DRCDB(x) DOUBLE_TO_DRCT(x, DRC_DB_BITS)
#define DRCDB_TO_FLOAT(x) DRCT_TO_FLOAT(x, DRC_DB_BITS)
#define DRCDB_TO_DOUBLE(x) DRCT_TO_DOUBLE(x, DRC_DB_BITS)
#define MULT_DRCDB(a, b) MULT_DRCT(a, b, DRC_DB_BITS)
#define DIV_DRCDB(a, b) DIV_DRCT(a, b, DRC_DB_BITS, DRC_DB_DIV_BITS)
#define DIV_DRCDB_CHECK(a, b) DIV_DRCT_CHECK(a, b, DRC_DB_BITS, DRC_DB_DIV_BITS)

// used for representing time constants
#define DRCTcType DRCDataType
#define DRC_TC_BITS (0)
#define DRCTC_TO_DOUBLE(x) DRCT_TO_DOUBLE(x, DRC_TC_BITS)
#define DOUBLE_TO_DRCTC(x) DOUBLE_TO_DRCT(x, DRC_TC_BITS)
#define FLOAT_TO_DRCTC(x) FLOAT_TO_DRCT(x, DRC_TC_BITS)
#define DRCTC_TO_INT(x) DRCT_TO_INT(x, DRC_TC_BITS)

// x is in milliseconds, want to calculate -2.2 / (tc*fs/1000)
// if argument is (tc*fs/10000), exp table should get exp(-.22 / x) since
// exp(-2.2 / (tc*fs/1000)) = exp(-.22 / (tc*fs/10000))
#define TC_TO_EXPARG(tc,fs) ((tc)*(fs)/1000)
#define TC_EXP_ARG(i) (-2.2 / (i))

// for represnting blendig coefficients for attack/release times
#define DRCTccType DRCDataType
#define DRC_TCC_BITS (30)
#define FLOAT_TO_DRCTCC(x) FLOAT_TO_DRCT(x, DRC_TCC_BITS)
#define DOUBLE_TO_DRCTCC(x) DOUBLE_TO_DRCT(x, DRC_TCC_BITS)
#define MULT_DRCTCC(a, b) MULT_DRCT(a, b, DRC_TCC_BITS)

#define DRCScaleType DRCDataType
#define DRC_SCALE_BITS (20)
#define MULT_DRCSCALE(a, b) MULT_DRCT(a, b, DRC_SCALE_BITS)
// bug 13374. need to avoid rounding sc before comparison. 
#define DIV_DRCSCALE(a, sc) ((sc) > (1<<DRC_SCALE_BITS)? DIV_DRCT((a), (sc), DRC_SCALE_BITS, DRC_SCALE_BITS) : a)
#define DOUBLE_TO_DRCSCALE(x) DOUBLE_TO_DRCT(x, DRC_SCALE_BITS)
#define FLOAT_TO_DRCSCALE(x) FLOAT_TO_DRCT(x, DRC_SCALE_BITS)
#define INT_TO_DRCSCALE(x) INT_TO_DRCT(x, DRC_SCALE_BITS)
#define DRCSCALE_TO_FLOAT(x) DRCT_TO_FLOAT(x, DRC_SCALE_BITS)

#define DRCLevelType DRCDataType
#define DRC_LEVEL_BITS (0)
#if (DRC_LEVEL_BITS != 0) && defined(DRC_BUILD_INTEGER_TABLE)
#error "Cannont change level bits -- build integer won't work w/o changes!"
#endif
#define FLOAT_TO_DRCLEVEL(x) FLOAT_TO_DRCT(x, DRC_LEVEL_BITS)

#ifdef DRC_BUILD_INTEGER_TABLE
#define MULT_DRCTCC2(a, b, c, d) \
  ((I32)(((I64)(a)*(I64)(b) + (I64)(c)*(I64)(d))>>DRC_TCC_BITS))
//  MULT_DRCTCC(a,b) + MULT_DRCTCC(c,d)
#define DIV_LEVEL_SCALE_BITS (6)
#define DIV_LEVEL_TO_SCALE(a, b) \
  ((((a)<<DIV_LEVEL_SCALE_BITS)/(b))<<(DRC_SCALE_BITS-DIV_LEVEL_SCALE_BITS))
#define DIV_LEVEL_SCALE_BITS64 (36)
#define DIV_LEVEL_TO_SCALE64(a, b) \
  (I32)((((I64)(a)<<DIV_LEVEL_SCALE_BITS64)/(b))>>(DIV_LEVEL_SCALE_BITS64-DRC_SCALE_BITS))
#else
#define MULT_DRCTCC2(a, b, c, d) \
  ((a)*(b) + (c)*(d))
#define DIV_LEVEL_TO_SCALE(a, b) \
  ((a)/(b))
#define DIV_LEVEL_TO_SCALE64(a, b) DIV_LEVEL_TO_SCALE(a, b)
#endif

// peak normalized value between 0 and 0x7fff
//#define POSTPROC_DRC_PEAKNORMU16 (0x7fff)

#define DRC_MIN_DB_FLOAT (-200.0)
#define DRC_MIN_DB (FLOAT_TO_DRCDB(DRC_MIN_DB_FLOAT)) // something smaller than -20*log(2^24) = -144 dB

#define DRC_SUGGESTED_ATTACKTIME_MS (FLOAT_TO_DRCTC(100.0)) // attack time in milliseconds
#define DRC_SUGGESTED_RELEASETIME_MS (FLOAT_TO_DRCTC(500.0)) // release time in milliseconds

// forward declaration
typedef struct _DRC DRCFwdDef;
typedef struct CAudioObject CAudioObjectFwdDef;
typedef struct CAudioObjectDecoder CAudioObjectDecoderFwdDef;

// determines whether DRCData.peak, DRCData.rms, and DRCOptions.desiredRms
//   are in dB, amplitude, or normalized amplitude
typedef enum {
  PostProcDrcDataUndefined = 0,
  PostProcDrcDataInDb,
  PostProcDrcDataInI32,
  PostProcDrcDataInNormU16
} PostProcDrcDataFormat;

typedef union {
  U64 undefined; /* PostPRocDrcDataUndefined, simply used for zeroing memory
                    pick to be largest size, instead of memset */
  DRCDbType dB; // PostProcDrcDataInDb
  I32 val; // PostProcDrcDataInI32
  I32 normVal; // PostProcDrcDataInNormU16
} PostProcDrcDataFormatVal;

typedef struct _DRCData
{
  PostProcDrcDataFormat dataFormatPeak;
  PostProcDrcDataFormat dataFormatRms;
  PostProcDrcDataFormatVal peak;
  PostProcDrcDataFormatVal rms;
  Bool fContainsSampleInfo;
  Int samplingRate;
  Int nChannels;
  U32 nBytePerSample;
  Int nValidBitsPerSample;
#ifndef STANDALONE_POSTPROCDRC
  CAudioObjectFwdDef *pau;
#endif
} DRCData;

typedef struct _DRCOptions
{
  PostProcDrcDataFormat m_dataFormatPeak;
  PostProcDrcDataFormat m_dataFormatRms;

  // normalize volume over entire file
  Bool m_fNormalizeRms;
  // desired rmsDb and peakDb for normalization
  PostProcDrcDataFormatVal m_desiredRms;
  PostProcDrcDataFormatVal m_desiredPeak;
  // soft clipping thresholds, applied on rms normalization
  DRCDbType m_clipThresholdYDb;
  // peak clipping for drc

  // Dynamic range compression params
  Bool m_fDRC;
  Bool m_fDRCEncode;
  Bool m_fDRCDecode;
  // Pointer to curve -- list of (x,y) pairs on curve -- must be sorted in x
  Double *m_pDRCCurve;
  // Number of points in curve
  Int m_nDRCCurvePoints;

  // Smooth gain using attack/release times
  Bool m_fSmoothGain;
  // attack time
  DRCTcType m_attackTimeMs;
  // release time
  DRCTcType m_releaseTimeMs;

  // Use mono channel for obtaining level, default is max channel value
  Bool m_fUseMonoChannel;
  // use smoothed rms value (IIR filter using attack/release times)
  //  as current level

  Bool m_fUseRmsVal;
  // use smoothed peak value as current level
  Bool m_fUsePeakVal;
  // level measurement attack time
  DRCTcType m_levelAttackTimeMs;
  // level measurement release time
  DRCTcType m_levelReleaseTimeMs;

  // use lookahead
  Bool m_fUseLookahead;
  // lookahead window in milliseconds
  DRCTcType m_lookaheadWindowMs;

  // use average rms value over window as level for entire window
  Bool m_fUseAvgWindow;
  // linearly interpolate gain between window segments
  Bool m_fUseLinInterpGainAvgWindow;

  // use drc if clip on rms normalize
  Bool m_fUseDRCOnNormalize;

  // use lookup tables with interpolation instead of log/antilog calculations
  Bool m_fUseTables;

  // use wma defaults when initializing
  Bool m_fUseWmaDefaults;

} DRCOptions;

#ifdef __cplusplus
extern "C" {
#endif

// use to zero out a DrcData structure, else in undefined state
void drcDataZero(DRCData *p);

void drcZero(DRCFwdDef *p);

void drcSetDefaultOptions(DRCOptions *p);

WMARESULT drcSuggestedDesiredRmsPeakWMA(DRCData *pDrcData,
                                        DRCDbType *pDesiredRmsDb,
                                        DRCDbType *pDesiredPeakDb,
                                        I16 nDRCSetting);

WMARESULT drcInit(DRCFwdDef *pDrc,
                  WAVEFORMATEXTENSIBLE *pwfx,
                  DRCData *pDrcData,
                  DRCOptions *pDrcOptions);

void drcFree(DRCFwdDef *p);

// must be called first until returns true if lookahead being done
Bool drcLookaheadInit(DRCFwdDef *p,
                      U8 *buffer,
                      Int numSampleBlocksIn);

/* if *pNumSampleBlocksProcessed != numSampleBlocksIn,
   it is up to caller to save data, and send it in as first data in
   next call, i.e., no internal buffering
   - this will only happen if lookahead is being used 
*/
WMARESULT drcProcess(DRCFwdDef *p,
                     U8 *buffer,
                     Int numSampleBlocksIn,
                     Int *pNumSampleBlocksProcessed);

// returns a scale factor
U8 drcEncode(DRCFwdDef *p, Float frameRmsValue);

// decode and normalize using scale factor -- faster to do both at once
WMARESULT drcDecode(DRCFwdDef *p,
                    U8 quantScaleFactor,
                    U8 *buffer,
                    Int numSampleBlocksIn,
                    Int nDRCSetting);
WMARESULT drcDecodeBlockLsl(DRCFwdDef *p,
                            CAudioObjectDecoderFwdDef *paudec,
                            U8 quantScaleFactor,
                            Int nDRCSetting,
                            Int cSamples);
WMARESULT drcDecodeBlockPro(DRCFwdDef *p,
                            CAudioObjectDecoderFwdDef *paudec,
                            U8 quantScaleFactor,
                            Int nDRCSetting,
                            Int cSamples);

// min size needed in # of sample blocks
I32 drcMinBufSize(DRCFwdDef *p);

#ifdef __cplusplus
}
#endif

// =======================================================================
// Private implementation

#ifdef __cplusplus
extern "C" {
#endif
// semi-private helper if you need to calculate file rms, and peak
WMARESULT drcCalcMsAndPeak(DRCFwdDef *p, U8 *buffer, int numSampleBlocks);
#ifdef __cplusplus
}
#endif

#ifdef DRC_BUILD_INTEGER_TABLE

typedef I32 DRCType;

#else // #ifdef DRC_BUILD_INTEGER_TABLE

#define DRC_USE_FLOAT
#ifdef DRC_USE_FLOAT
typedef Float DRCType;
#else // use doubles
typedef Double DRCType;
#endif

#endif // #ifdef DRC_BUILD_INTEGER_TABLE

typedef struct _DRC
{

  DRCOptions m_opt;

  Int  m_nChannels;

  // amount to left shift
  Int m_amtToLeftShift;
#ifndef BUILD_INTEGER
  Float m_amtToScale;
#endif

  // for RMS calcs
  DRCDbType m_actualRms;
  Int    m_numSampleBlocks;

  // for peak calcs
  I32 m_actualPeak;

  // level measurement
  DRCType m_curLevel;
  DRCType m_levelAttackCoeff;
  DRCType m_levelReleaseCoeff;
  DRCType m_oneMinusLevelAttackCoeff;
  DRCType m_oneMinusLevelReleaseCoeff;
  Int m_cSamplesForAttack;
  Int m_cSamplesForRelease;

  // gain smoothing
  DRCType m_curScaleFactor;
  DRCType m_attackCoeff;
  DRCType m_releaseCoeff;
  DRCType m_oneMinusAttackCoeff;
  DRCType m_oneMinusReleaseCoeff;
  // gain in linear region
  DRCType *m_scaleFactor; // scale factors for each scale table
  Bool *m_fNeedDRCOnNormalize; // use drc in rms normalization or not

  // Params for static curve for rms normalize
  // used only when table not set, so can't use if scale tables > 1
  DRCDbType m_gainDb;
  DRCDbType m_ratioDb;
  DRCDbType m_linearThresholdDb;

  // for lookahead
  Int m_nLookahead;
  Int m_lookaheadCount;

  // for avg window
  // if gain linearly interpolated, window size is floor((lookahead+1)/2)
  //   else window size is equal to (lookahead+1)
  Int m_windowCount;
  Int m_windowSize; // determined from lookahead
  Int m_floorHalfWindowSize;
  DRCType m_windowPeakLevel;
  DRCType m_prevLevel; // for obtaining current amplitude "level"
  // for linearly interpolating gain
  DRCType m_scaleFactor0;
  DRCType m_scaleFactor1;
  DRCType m_scaleFactor0Slope;
  DRCType m_scaleFactor1Slope;

  // Table lookup on scale factors
  Int m_nScaleTables;
  DRCType **m_scaleTable;
  DRCType **m_scaleSlopeTable;
  DRCType **m_scaleTableBase;
  DRCType **m_scaleSlopeTableBase;

  DRCType m_maxPeakValEnc;
  DRCType *m_maxPeakValDec;

#ifndef STANDALONE_POSTPROCDRC
  CAudioObjectFwdDef *m_pau;
#endif

  // misc buffers
  I32 *m_curSamples;
  I32 *m_lookaheadSamples;

  // shift amount on slope
  I32 *m_intSlopeShiftBits;

} DRC;

#ifdef __cplusplus
extern "C" {
#endif
INLINE I32 drcMinBufSize(DRC *p)
{
  return (p->m_nLookahead+1);
}
#ifdef __cplusplus
}
#endif

#endif // BUILD_WMAPRO
#endif // _DRCCOMMON_H
