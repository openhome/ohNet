//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    WmaOS.c

Abstract:

    Functions that should work under any generic OS.

Author:

    Raymond Cheng (raych)       September 27, 1999

Revision History:


*************************************************************************/

#include "msaudio.h"
#include "macros.h"
#include "AutoProfile.h"
#include <stdio.h>
#if defined(_DEBUG) && defined(WMA_MONITOR)
#	include <math.h>
#endif
#if defined(HEAP_DEBUG_TEST) && defined(_DEBUG)
#include <malloc.h>
#endif
#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)
#include <stdarg.h>
#endif

#if !defined(_WIN32_WCE) || defined(MEASURE_CLOCK)	// disable for CE unless used by test app
#ifndef PLATFORM_SPECIFIC_PERFTIMER

#include <time.h>

typedef struct tagPERFTIMERINFO
{
    int     fFirstTime;         // Used to record total time spent in decode loop
    clock_t cDecodeTime;        // Time spent decoding only (running total)
    clock_t cTotalDecLoopTime;  // Total time spent in decode loop
    clock_t cDecodeStart;       // Could be easily optimized out but it's not worth it
    clock_t cAccumulatedTime;   // Time accumulated before a PerfTimerPause
    long    lSamplesPerSec;     // Samples per second, counting all channels
    long    lPlaybackTime;      // Time required for playback (running total)
} PERFTIMERINFO;

PERFTIMERINFO *PerfTimerNew(long lSamplesPerSecOutput)
{
    PERFTIMERINFO  *pInfo;

    pInfo = (PERFTIMERINFO*)(auMalloc(sizeof(PERFTIMERINFO)));
    if (NULL == pInfo)
        return NULL;

    pInfo->fFirstTime = WMAB_TRUE;
    pInfo->cDecodeTime = 0;
    pInfo->cTotalDecLoopTime = 0;
    pInfo->cDecodeStart = 0;
    pInfo->cAccumulatedTime = 0;
    pInfo->lSamplesPerSec = lSamplesPerSecOutput;
    pInfo->lPlaybackTime = 0;

    return pInfo;
}

void PerfTimerStart(PERFTIMERINFO *pInfo)
{
    pInfo->cDecodeStart = clock();
    pInfo->cAccumulatedTime = 0;

    if (pInfo->fFirstTime)
    {
        pInfo->cTotalDecLoopTime = pInfo->cDecodeStart;
        pInfo->fFirstTime = WMAB_FALSE;
    }
}

void PerfTimerPause(PERFTIMERINFO *pInfo)
{
    clock_t cDecodeTime;

    cDecodeTime = clock() - pInfo->cDecodeStart;
    pInfo->cAccumulatedTime += cDecodeTime;
}


void PerfTimerResume(PERFTIMERINFO *pInfo)
{
    pInfo->cDecodeStart = clock();
}


void PerfTimerStop(PERFTIMERINFO *pInfo, long lSamplesDecoded)
{
    clock_t cDecodeTime;

    cDecodeTime = clock() - pInfo->cDecodeStart;
    cDecodeTime += pInfo->cAccumulatedTime;
    pInfo->cDecodeTime += cDecodeTime;

    // Record output playback time from this decode call, in clock() ticks
    pInfo->lPlaybackTime += lSamplesDecoded * CLOCKS_PER_SEC / pInfo->lSamplesPerSec;
}

void PerfTimerStopElapsed(PERFTIMERINFO *pInfo)
{
    pInfo->cTotalDecLoopTime = clock() - pInfo->cTotalDecLoopTime;
}

void PerfTimerReport(PERFTIMERINFO *pInfo)
{
    char    sz[256];
    float   fltDecodeTime;
    float   fltEntireDecodeTime;
    float   fltDecodeTimeFraction;
    float   fltPlaybackTime;

    sprintf(sz, "\n\n** Ticks per second (clock resolution): %ld.\n", CLOCKS_PER_SEC);
    OUTPUT_DEBUG_STRING(sz);

    fltDecodeTime = (float) pInfo->cDecodeTime / (float) CLOCKS_PER_SEC;
    fltEntireDecodeTime = (float) pInfo->cTotalDecLoopTime /
        (float) CLOCKS_PER_SEC;
    sprintf(sz, "** Decode time: %f sec. Entire decode time: %f sec.\n",
        fltDecodeTime, fltEntireDecodeTime);
    OUTPUT_DEBUG_STRING(sz);

    fltPlaybackTime = (float) pInfo->lPlaybackTime / (float) CLOCKS_PER_SEC;
    sprintf(sz, "** Playback time : %f sec.\n",
        fltPlaybackTime);
    OUTPUT_DEBUG_STRING(sz);

    fltDecodeTimeFraction = (float)pInfo->cDecodeTime / (float) pInfo->lPlaybackTime;
    sprintf(sz, "** Percentage of playback time spent decoding: %f%%.\n",
        fltDecodeTimeFraction * 100);
    OUTPUT_DEBUG_STRING(sz);
#	if defined(WMA_MONITOR)
		WMAFprintf(stderr,"%s\n",sz);
#	endif

    sprintf(sz, "** Minimum MHz for realtime playback: %f of current CPU speed.\n",
        fltDecodeTimeFraction);
    OUTPUT_DEBUG_STRING(sz);

    sprintf(sz, "** This CPU is %f times faster than required.\n\n",
        (float)1.0 / fltDecodeTimeFraction);
    OUTPUT_DEBUG_STRING(sz);

#ifdef WRITE_TIME_TO_FILE
    {
        FILE*   fOut;
        
        fOut = fopen("time.txt", "wt");
        if (fOut != NULL) 
        { 
            fprintf(fOut, "%f\n", (float) fltDecodeTime);
            fclose(fOut);
            fOut = NULL;
        }
    }
#endif  //WRITE_TIME_TO_FILE
}

float fltPerfTimerDecodeTime(PERFTIMERINFO *pInfo)
{
    return (float) pInfo->cDecodeTime / (float) CLOCKS_PER_SEC;
}

void PerfTimerFree(PERFTIMERINFO *pInfo)
{
    auFree(pInfo);
}

#endif  // PLATFORM_SPECIFIC_PERFTIMER
#endif	// !defined(_WIN32_WCE) || defined(MEASURE_CLOCK)


#if defined(_DEBUG) && defined(WMA_MONITOR)

#define DECL_MONITOR_RANGE(a) AVRT_DATA extern double a[4] = { 1.0e30, -1.0e30, 0, 0 };  AVRT_DATA extern long lc##a = 0;

// declare and define some range monitors in _DEBUG mode when WMA_MONITOR is defined
DECL_MONITOR_RANGE(gMR_iQuantStepSize)
DECL_MONITOR_RANGE(gMR_qstQuantStep)
DECL_MONITOR_RANGE(gMR_iCoefQ);
DECL_MONITOR_RANGE(gMC_0CoefQ);
DECL_MONITOR_RANGE(gMR_rgiMaskQ)
DECL_MONITOR_RANGE(gMR_rgiNoisePower)				// only for LowRate and MidRate
DECL_MONITOR_RANGE(gMR_rgiLspFreqQ)					// only for LowRate, e.g. LPC
DECL_MONITOR_RANGE(gMR_rgfltLspFreq)				// only for LowRate, e.g. LPC
DECL_MONITOR_RANGE(gMR_fltLPC_F)					// only for LowRate, e.g. LPC
DECL_MONITOR_RANGE(gMR_fltLPC_F1)					// only for LowRate, e.g. LPC
DECL_MONITOR_RANGE(gMR_fltLPC_F2)					// only for LowRate, e.g. LPC
DECL_MONITOR_RANGE(gMR_fltLPC_F3)					// only for LowRate, e.g. LPC
DECL_MONITOR_RANGE(gMR_rgfltWeightFactor)
DECL_MONITOR_RANGE(gMR_WeightRatio)
DECL_MONITOR_RANGE(gMR_rgfltBandWeight)				// only for MidRate and LowRate
DECL_MONITOR_RANGE(gMR_rgffltSqrtBWRatio)
DECL_MONITOR_RANGE(gMR_CoefRecon)
DECL_MONITOR_RANGE(gMC_zeroCoefRecon)
DECL_MONITOR_RANGE(gMR_DCTCoefIntoFFT)
DECL_MONITOR_RANGE(gMR_DCTCoefOut)
DECL_MONITOR_RANGE(gMC_ScalePowerToRMS)
DECL_MONITOR_RANGE(gMC_ScaleInverseQuadRoot)
DECL_MONITOR_RANGE(gMC_IQ)
//DECL_MONITOR_RANGE(gMC_IQ_iFractionBitsQuantStep)
DECL_MONITOR_RANGE(gMC_IQ_cQSIMWFracBits)
DECL_MONITOR_RANGE(gMR_QuantStepXInvMaxWeight)
DECL_MONITOR_RANGE(gMR_QuantStepXMaxWeightXWeightFactor)
DECL_MONITOR_RANGE(gMC_IQ_cWFFracBits)
DECL_MONITOR_RANGE(gMR_weightFactor)
DECL_MONITOR_RANGE(gMC_IQ_scale)
DECL_MONITOR_RANGE(gMC_IQ_scale2)
DECL_MONITOR_RANGE(gMC_IQ_Float)
DECL_MONITOR_RANGE(gMC_IQ_fltNoisePowCount)
DECL_MONITOR_RANGE(gMC_GBW_floats)

#if defined(WMA_MONITOR_FILE)
#	if defined(OUTPUT_DEBUG_STRING)
#		undef DUMP_MONITOR_RANGE
#		define DUMP_MONITOR_RANGE(a) if (lc##a>0) { sprintf(sz,"%14.6g %14.6g %14.6g %14.6g %8ld " #a "\n", a[0], a[1], a[2]/lc##a, sqrt((lc##a*a[3]-a[2]*a[2])/(((double)lc##a)*(lc##a-1))), lc##a ); OUTPUT_DEBUG_STRING(sz); }
#	else
#		undef DUMP_MONITOR_RANGE
#		define DUMP_MONITOR_RANGE(a) if (lc##a>0) WMAFprintf(fp,"%14.6g %14.6g %14.6g %14.6g %8ld " #a "\n", a[0], a[1], a[2]/lc##a, sqrt((lc##a*a[3]-a[2]*a[2])/(((double)lc##a)*(lc##a-1))), lc##a );
#	endif
#endif

void DumpMonitorRanges(int fAppend) {
	FILE* fp = NULL;
#	if defined(WMA_MONITOR_FILE)
#		if defined(OUTPUT_DEBUG_STRING)
			char sz[256];
			int bODX = 0;
			if ( stricmp(WMA_MONITOR_FILE,"OutputDebugString")
				bODS = 1;
			else 
#		endif	// defined(OUTPUT_DEBUG_STRING)
		if ( stricmp(WMA_MONITOR_FILE,"stdout")
			fp = stdout;
		else
			fp = FOPEN(WMA_MONITOR_FILE,fAppend ? "w+" : "w");
#	else
		fp = stdout;
#	endif		

#	if defined(OUTPUT_DEBUG_STRING)
		if ( bODX )
			OUTPUT_DEBUG_STRING("\n       Minimum        Maximum           Mean StandDeviation    Count Variable\n");
		else
#	endif
		WMAFprintf(fp,"\n       Minimum        Maximum           Mean StandDeviation    Count Variable\n");

	DUMP_MONITOR_RANGE(gMR_iQuantStepSize);
	DUMP_MONITOR_RANGE(gMR_qstQuantStep);
	DUMP_MONITOR_RANGE(gMR_iCoefQ);
	DUMP_MONITOR_RANGE(gMC_0CoefQ);
	DUMP_MONITOR_RANGE(gMR_rgiMaskQ);
#	ifdef ENABLE_LPC
		DUMP_MONITOR_RANGE(gMR_rgiLspFreqQ);
#		ifndef BUILD_INTEGER
			DUMP_MONITOR_RANGE(gMR_rgfltLspFreq);
#		endif
		DUMP_MONITOR_RANGE(gMR_fltLPC_F1);
		DUMP_MONITOR_RANGE(gMR_fltLPC_F2);
		DUMP_MONITOR_RANGE(gMR_fltLPC_F3);
#	endif
	DUMP_MONITOR_RANGE(gMR_rgiNoisePower);
	DUMP_MONITOR_RANGE(gMR_rgfltWeightFactor);
	DUMP_MONITOR_RANGE(gMR_WeightRatio);
	DUMP_MONITOR_RANGE(gMR_rgfltBandWeight);
	DUMP_MONITOR_RANGE(gMR_rgffltSqrtBWRatio);
	DUMP_MONITOR_RANGE(gMR_CoefRecon);
	DUMP_MONITOR_RANGE(gMC_zeroCoefRecon);
	DUMP_MONITOR_RANGE(gMR_DCTCoefIntoFFT);
	DUMP_MONITOR_RANGE(gMR_DCTCoefOut);
	DUMP_MONITOR_RANGE(gMR_QuantStepXInvMaxWeight);
	DUMP_MONITOR_RANGE(gMR_QuantStepXMaxWeightXWeightFactor);

	DUMP_MONITOR_RANGE(gMR_weightFactor);

	DUMP_MONITOR_RANGE(gMC_ScalePowerToRMS);
	DUMP_MONITOR_RANGE(gMC_ScaleInverseQuadRoot);
	DUMP_MONITOR_RANGE(gMC_IQ);
	//DUMP_MONITOR_RANGE(gMC_IQ_iFractionBitsQuantStep);
	DUMP_MONITOR_RANGE(gMC_IQ_cQSIMWFracBits);
	DUMP_MONITOR_RANGE(gMC_IQ_cWFFracBits);
	DUMP_MONITOR_RANGE(gMC_IQ_scale);
	DUMP_MONITOR_RANGE(gMC_IQ_scale2);
	DUMP_MONITOR_RANGE(gMC_IQ_Float);
	DUMP_MONITOR_RANGE(gMC_IQ_fltNoisePowCount);
	DUMP_MONITOR_RANGE(gMC_GBW_floats);
	if ( fp != NULL && fp != stdout )
		FCLOSE(fp);
}
#	pragma COMPILER_MESSAGE(__FILE__ "(302) : Warning - WMA_MONITOR Debug Code Enabled.")
#endif


#if defined(WMA_SHOW_FRAMES) && defined(_DEBUG)

static FILE* fileShowFrames = NULL;

void prvWmaShowFrames(const Int iFrameNumber, const Int iCurrSubFrame,
                      const Int cFrameSampleAdjusted, const Int cSubFrameSampleAdjusted,
                      const Int cSubbandAdjusted, const char* pszID, const char* pszFmt, ...)
{
#ifdef UNDER_CE
    if ( fileShowFrames == NULL )
        fileShowFrames = FOPEN("ShowFrames.txt","wt");
    if ( fileShowFrames == NULL )
        return;
#else
	fileShowFrames = stderr;
#endif
    WMAFprintf(fileShowFrames,"%7s %3d.%d [%4d %4d %4d]",
        pszID,
        iFrameNumber,
        iCurrSubFrame,
        cFrameSampleAdjusted,
        cSubFrameSampleAdjusted,
        cSubbandAdjusted
    );
    if ( pszFmt != NULL )
    {
        char    sz[512];
        va_list vargs;

        va_start(vargs, pszFmt);
        vsprintf(sz, pszFmt, vargs);
        va_end(vargs);

        WMAFprintf(fileShowFrames,"%s",sz);
    }
    WMAFprintf(fileShowFrames,"\n" );
}

#	pragma COMPILER_MESSAGE(__FILE__ "(341) : Warning - SHOW_FRAMES Debug Code Enabled.")
#endif

#if defined(SDE_WANTS_PRINTFIO) && defined(UNDER_CE)
#   pragma COMPILER_MESSAGE(__FILE__ "(337) : Warning - Print Stdio enabled - for SDE use only!")
#endif
#if defined(BUILD_INT_FLOAT) && ( defined(WMA_TARGET_SH3) || (defined(WMA_TARGET_MIPS) && !(defined(MIPSFP) || defined(MIPSIV_FP))))
#	pragma COMPILER_MESSAGE(__FILE__ "(373) : Warning - Integer Float Build.")
#endif
#ifdef WMAPROFILE
#	pragma COMPILER_MESSAGE(__FILE__ "(376) : Warning - WMAPROFILE Enabled.")
#endif
#if defined(SDE_WANTS_ASSERTS) && defined(_DEBUG) && !defined(UNDER_CE)
#   pragma COMPILER_MESSAGE(__FILE__ "(379) : Warning - Asserts are enabled - for SDE use only!")
#endif

#if defined(SPEW_WMA_CONFIG)
#if defined(_DEBUG) && defined(BUILD_WMASTD) && defined(BUILD_WMAPRO) && defined (BUILD_WMAPRO_PLLM) && defined(BUILD_WMALSL)
//#	pragma COMPILER_MESSAGE(__FILE__ "(382) : Note - WMA, WMA Pro, and WMA Lossless are enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMASTD) && defined(BUILD_WMAPRO)
#	pragma COMPILER_MESSAGE(__FILE__ "(384) : Note - WMA and WMA Pro are enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMAPRO) && defined(BUILD_WMALSL)
#	pragma COMPILER_MESSAGE(__FILE__ "(386) : Note - WMA Pro and WMA Lossless are enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMASTD) && defined(BUILD_WMALSL)
#	pragma COMPILER_MESSAGE(__FILE__ "(388) : Note - WMA and WMA Lossless are enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMASTD)
#	pragma COMPILER_MESSAGE(__FILE__ "(390) : Note - Only WMA is enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMAPRO) && defined(BUILD_WMAPRO_PLLM)
#	pragma COMPILER_MESSAGE(__FILE__ "(392) : Note - Only WMA Pro (with pure lossless support) is enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMAPRO) && !defined(BUILD_WMAPRO_PLLM)
#	pragma COMPILER_MESSAGE(__FILE__ "(394) : Note - Only WMA Pro (without pure lossless support) is enabled!")
#elif defined(_DEBUG) && defined(BUILD_WMALSL)
#	pragma COMPILER_MESSAGE(__FILE__ "(396) : Note - Only WMA Lossless is enabled!")
#endif
#endif

#if defined(HEAP_DEBUG_TEST) && defined(_DEBUG)
// check the heap - see macros in msaudio.h
// _heapchk does not seem to be available under WinCE
void HeapDebugCheck()
	{ int  heapstatus;
	   /* Check heap status */
	   heapstatus = _heapchk();
	   switch( heapstatus )
	   {
	   case _HEAPOK:
		  //WMAPrintf(" OK - heap is fine\n" );
		  break;
	   case _HEAPEMPTY:
		  WMAPrintf(" OK - heap is empty\n" );
		  break;
	   case _HEAPBADBEGIN:
		  WMAPrintf( "ERROR - bad start of heap\n" );
		  break;
	   case _HEAPBADNODE:
		  WMAPrintf( "ERROR - bad node in heap\n" );
		  break;
	   }
	}
#endif

#ifdef UNDER_CE
// se need to define at least one public symbol
extern void wmaos_pacify(void) {}
#endif
