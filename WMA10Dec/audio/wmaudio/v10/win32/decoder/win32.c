//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    Win32.c

Abstract:

    Win32-specific functions.

Author:

    Raymond Cheng (raych)       Aug 25, 1999

Revision History:
  
    Thumpudi Naveen (tnaveen)   May 9, 2000    Added NT specific timer.

*************************************************************************/

#include "macros.h"


// Only build these functions for WIN32
#if defined (WMA_OSTARGET_WIN32) && !defined (WMA_TARGET_ANSI)

// **************************************************************************
// COMMON FUNCTIONS
// **************************************************************************

#ifdef WMA_TARGET_ANSI
#include "ansiwin.h"
#else   // WMA_TARGET_ANSI

#ifndef _WIN32
#define _WIN32  // We need this when including windows.h
#endif  // !_WIN32

#include "windows.h"
#endif  // WMA_TARGET_ANSI


#ifdef PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING
#define OUTPUT_DEBUG_STRING(sz) OutputDebugString(sz)
#endif  // PLATFORM_SPECIFIC_OUTPUTDEBUGSTRING

#if defined(UNDER_CE) && defined(OUTPUT_DEBUG_STRING)
// we don't have a unicode provision for OutputDebugString on WinCE - need to add conversion
#undef OUTPUT_DEBUG_STRING
#define OUTPUT_DEBUG_STRING(sz)
#endif

#if defined(UNDER_CE) || defined(BUILD_VC) || (_MSC_VER < 1400)
#ifdef UNICODE
#define SPRINTF(_Dst, _Size, _Format, _Arg1) swprintf((_Dst), (_Format), (_Arg1))
#define STRCPY(_Dst, _Size, _Src)            wcscpy((_Dst), (_Src))
#else   // UNICODE
#define SPRINTF(_Dst, _Size, _Format, _Arg1) sprintf((_Dst), (_Format), (_Arg1))
#define STRCPY(_Dst, _Size, _Src)            strcpy((_Dst), (_Src))
#endif  // UNICODE
#else // UNDER_CE || BUILD_VC
// So !CE, !BUILD_VC
#ifdef UNICODE
#define SPRINTF swprintf_s
#define STRCPY  wcscpy_s
#else   // UNICODE
#define SPRINTF sprintf_s
#define STRCPY  strcpy_s
#endif  // UNICODE
#endif // UNDER_CE || BUILD_VC

#ifdef WMA_OSTARGET_WIN32


DWORD prvGetRegistryDword( HKEY hKeyBase, LPCTSTR lpcKey, LPCTSTR lpcValue, DWORD dwDefault )
{
    HKEY hKey;
    U32  Type;                // address of buffer for value type
    U32  dwData = dwDefault;  // address of data buffer
    U32  cbData = 4;          // address of data buffer size
    I32  result;

    result = RegOpenKeyEx( hKeyBase, lpcKey, 0, KEY_READ, &hKey );

    if( result != ERROR_SUCCESS )
        return dwDefault;

    result = RegQueryValueEx( hKey, lpcValue, 0, &Type, (LPBYTE)&dwData, &cbData );

    RegCloseKey( hKey );

    if( result != ERROR_SUCCESS )
        return dwDefault;

    return dwData;
}

#define WMA_DEC_REGKEY  TEXT("SOFTWARE\\Microsoft\\Scrunch\\WMAudio\\Decoder")
#define WMA_ENC_REGKEY  TEXT("SOFTWARE\\Microsoft\\Scrunch\\WMAudio\\Encoder")
#define LTRT_REGKEY     TEXT("SOFTWARE\\Microsoft\\DirectX\\DirectShow\\WMADecoder\\LtRt")

DWORD prvGetRegistryDisablePlusV1()
{
    return prvGetRegistryDword( HKEY_CURRENT_USER, WMA_DEC_REGKEY, TEXT( "DisablePlusV1" ), 0 );
}

DWORD prvGetRegistryDisablePlusV2()
{
    return prvGetRegistryDword( HKEY_CURRENT_USER, WMA_DEC_REGKEY, TEXT( "DisablePlusV2" ), 0 );
}

Void prvGetRegistryLTRTSettings( DWORD * const pdwMode, DWORD * const pdwBufSize, DWORD * const pdwQuality )
{
    *pdwMode    = prvGetRegistryDword(HKEY_LOCAL_MACHINE, LTRT_REGKEY, TEXT("Mode"), 0);
    *pdwBufSize = prvGetRegistryDword(HKEY_LOCAL_MACHINE, LTRT_REGKEY, TEXT("BufSize"), 1000);
    *pdwQuality = prvGetRegistryDword(HKEY_LOCAL_MACHINE, LTRT_REGKEY, TEXT("Quality"), 40);
}

#endif // !WMA_TARGET_ANSI

#ifndef WMA_TARGET_ANSI
// [HKEY_CURRENT_USER\Software\Microsoft\Scrunch\WMAudio\Encoder]
// "PlusSelection"=dword:00000000

Void prvSetPlusSelectionThroughRegistry(LPCTSTR value,
                                        Bool* pfKeyExists,
                                        U32* pulPlusSelection)
{
    HKEY hkey1, hkey2, hkey3, hkey4, hkey5;
    U32  Type;      // address of buffer for value type
    U8   Data [80];       // address of data buffer
    U32  cbData = 80;    // address of data buffer size);
    I32  result;
    
    if (NULL == pfKeyExists ||
        NULL == pulPlusSelection)
    {
        return;
    }

    *pfKeyExists      = WMAB_FALSE;
    *pulPlusSelection = 0;

    result = RegOpenKeyEx (HKEY_CURRENT_USER, TEXT("SOFTWARE"), 0, KEY_READ,
                           &hkey1);
    if (result != ERROR_SUCCESS)
    {
        return;
    }

    result = RegOpenKeyEx (hkey1, TEXT("Microsoft"), 0, KEY_READ, &hkey2);
    if (result != ERROR_SUCCESS) 
    {
        RegCloseKey(hkey1);
        return;
    }

    result = RegOpenKeyEx (hkey2, TEXT("Scrunch"), 0, KEY_READ, &hkey3);
    if (result != ERROR_SUCCESS) 
    {
        RegCloseKey(hkey2);
        RegCloseKey(hkey1);
        return;
    }

    result = RegOpenKeyEx (hkey3, TEXT("WMAudio"), 0, KEY_READ, &hkey4);
    if (result != ERROR_SUCCESS) 
    {
        RegCloseKey(hkey3);
        RegCloseKey(hkey2);
        RegCloseKey(hkey1);
        return;
    }

    result = RegOpenKeyEx (hkey4, TEXT("Encoder"), 0, KEY_READ, &hkey5);
    if (result != ERROR_SUCCESS) 
    {
        RegCloseKey(hkey4);
        RegCloseKey(hkey3);
        RegCloseKey(hkey2);
        RegCloseKey(hkey1);
        return;
    }

    result = RegQueryValueEx (hkey5, value, 0, &Type, &(Data[0]), &cbData);
    if (result != ERROR_SUCCESS) 
    {
        RegCloseKey(hkey5);
        RegCloseKey(hkey4);
        RegCloseKey(hkey3);
        RegCloseKey(hkey2);
        RegCloseKey(hkey1);
        return;
    }
    
    *pfKeyExists      = WMAB_TRUE;
    *pulPlusSelection = (U32) Data[0];
   
    // Clean-up
    RegCloseKey(hkey5);
    RegCloseKey(hkey4);
    RegCloseKey(hkey3);
    RegCloseKey(hkey2);
    RegCloseKey(hkey1);

    return;

} // prvSetPlusSelectionThroughRegistry
#endif // !WMA_TARGET_ANSI

#if !defined(_WIN32_WCE) || defined(MEASURE_CLOCK)	// disable for CE unless used by test app
#ifdef PLATFORM_SPECIFIC_PERFTIMER

#include <stdio.h>
#include "wmamalloc.h" 

typedef struct tagPERFTIMERINFO
{
    int             fFirstTime;         // Used to record total time spent in decode loop
    LARGE_INTEGER   cDecodeTime;        // Time spent decoding only (running total)
    LARGE_INTEGER   cTotalDecLoopTime;  // Total time spent in decode loop
    LARGE_INTEGER   cDecodeStart;       // Could be easily optimized out but it's not worth it
    LARGE_INTEGER   cAccumulatedTime;   // Time accumulated before a PerfTimerPause
    long            lSamplesPerSec;     // Samples per second, counting all channels
    LARGE_INTEGER   cPlaybackTime;      // Time required for playback (running total)
    LARGE_INTEGER   cPerfFrequency;     // Frequency of PerformanceCounter
    
    Bool            bIsWindowsNT;       // GetProcessTime available
} PERFTIMERINFO;


PERFTIMERINFO *PerfTimerNew(long lSamplesPerSecOutput)
{
    PERFTIMERINFO  *pInfo;
    Bool            fResult;
    OSVERSIONINFO   osVersionInfo;
    
    pInfo = (PERFTIMERINFO*) auMalloc(sizeof(PERFTIMERINFO));
    if (NULL == pInfo)
        return NULL;
    
    pInfo->fFirstTime = WMAB_TRUE;
    pInfo->cDecodeTime.QuadPart = 0;
    pInfo->cTotalDecLoopTime.QuadPart  = 0;
    pInfo->cDecodeStart.QuadPart  = 0;
    pInfo->cAccumulatedTime.QuadPart = 0;
    pInfo->lSamplesPerSec = lSamplesPerSecOutput;
    pInfo->cPlaybackTime.QuadPart  = 0;
    
    // Determine if we are running on NT
    osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    // Default: Not NT
    pInfo->bIsWindowsNT = WMAB_FALSE;

#if !defined(USE_QUERY_TIMER)
    if (GetVersionEx(&osVersionInfo)) 
        pInfo->bIsWindowsNT = (osVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT);
#endif // USE_QUERY_TIMER
    
    if (pInfo->bIsWindowsNT) {
        pInfo->cPerfFrequency.QuadPart = 10000000; // Ticks are hard coded to be 100ns
    } else {
        fResult = QueryPerformanceFrequency(&pInfo->cPerfFrequency);
        if (WMAB_FALSE == fResult)
            pInfo->cPerfFrequency.QuadPart = -1;
    }
    
    return pInfo;
}

void prvPerfTimerGetCurrentTime(PERFTIMERINFO *pInfo, LARGE_INTEGER *pliCurrTime)
{
    Bool     fResult;

#ifndef UNDER_CE
    if (pInfo->bIsWindowsNT) 
    {
        // Measures user time. Aggregate of all threads in the process. 
        // Should we measure wall clock time? Should we add kernel time
        // to the user time?
        // Get pseudo handle of the current process. No need to close
        // pseudo-handles.
        HANDLE   hProcess;
        FILETIME ftCreationTime, ftExitTime, ftKernelTime, ftUserTime;

        hProcess = GetCurrentProcess();
        fResult = GetProcessTimes(hProcess, &ftCreationTime, 
            &ftExitTime, &ftKernelTime, &ftUserTime);
        if (WMAB_FALSE == fResult) 
            pliCurrTime->QuadPart = 0;
        else
        {
            pliCurrTime->LowPart = ftUserTime.dwLowDateTime;
            pliCurrTime->HighPart = ftUserTime.dwHighDateTime;
        }
    } 
    else 
    {
#endif  // !UNDER_CE

        fResult = QueryPerformanceCounter(pliCurrTime);
        if (WMAB_FALSE == fResult)
            pliCurrTime->QuadPart = 0;

#ifndef UNDER_CE
    }
#endif  // !UNDER_CE

} // prvPerfTimerGetCurrentTime

void PerfTimerStart(PERFTIMERINFO *pInfo)
{
    LARGE_INTEGER   liCurrTime;

    prvPerfTimerGetCurrentTime(pInfo, &liCurrTime);
    pInfo->cDecodeStart.QuadPart = liCurrTime.QuadPart;
    pInfo->cAccumulatedTime.QuadPart = 0;

    if (pInfo->fFirstTime)
    {
        pInfo->cTotalDecLoopTime.QuadPart = pInfo->cDecodeStart.QuadPart;
        pInfo->fFirstTime = WMAB_FALSE;
    }
}

void PerfTimerPause(PERFTIMERINFO *pInfo)
{
    LARGE_INTEGER   cDecodeTime;
    LARGE_INTEGER   liCurrTime;

    prvPerfTimerGetCurrentTime(pInfo, &liCurrTime);
    cDecodeTime.QuadPart = liCurrTime.QuadPart - pInfo->cDecodeStart.QuadPart;

    pInfo->cAccumulatedTime.QuadPart += cDecodeTime.QuadPart;
}


void PerfTimerResume(PERFTIMERINFO *pInfo)
{
    LARGE_INTEGER   liCurrTime;

    prvPerfTimerGetCurrentTime(pInfo, &liCurrTime);
    pInfo->cDecodeStart.QuadPart = liCurrTime.QuadPart;
}

void PerfTimerStop(PERFTIMERINFO *pInfo, long lSamplesDecoded)
{
    LARGE_INTEGER   cEndTime;
    
    prvPerfTimerGetCurrentTime(pInfo, &cEndTime);

    pInfo->cDecodeTime.QuadPart += cEndTime.QuadPart -
        pInfo->cDecodeStart.QuadPart;

    pInfo->cDecodeTime.QuadPart += pInfo->cAccumulatedTime.QuadPart;
    
    // Record output playback time from this decode call, in clock() ticks
    pInfo->cPlaybackTime.QuadPart += lSamplesDecoded *
        pInfo->cPerfFrequency.QuadPart / pInfo->lSamplesPerSec;
}

void PerfTimerStopElapsed(PERFTIMERINFO *pInfo)
{
    LARGE_INTEGER   cEndElapsedTime;
    Bool            fResult;
    
#ifndef UNDER_CE
    if (pInfo->bIsWindowsNT) 
    { 
        // Measures user time. Aggregate of all threads in the process
        // Should we measure wall clock time? Should we add kernel time
        // to the user time?
        // Get pseudo handle of the current process. No need to close
        // pseudo-handles.
        HANDLE          hProcess;
        FILETIME        ftCreationTime, ftExitTime, ftKernelTime, ftUserTime;
        hProcess = GetCurrentProcess();
        fResult = GetProcessTimes(hProcess, &ftCreationTime, 
            &ftExitTime, &ftKernelTime, &ftUserTime);
        if (WMAB_FALSE == fResult) 
            cEndElapsedTime.QuadPart = 0;
        else
        {
            cEndElapsedTime.LowPart = ftUserTime.dwLowDateTime;
            cEndElapsedTime.HighPart = ftUserTime.dwHighDateTime;
        }
    }
    else 
    {
        fResult = QueryPerformanceCounter(&cEndElapsedTime);
        if (WMAB_FALSE == fResult)
            cEndElapsedTime.QuadPart = 0;
    }
#else   // UNDER_CE
    fResult = QueryPerformanceCounter(&cEndElapsedTime);
    if (WMAB_FALSE == fResult)
        cEndElapsedTime.QuadPart = 0;
#endif  // UNDER_CE
    pInfo->cTotalDecLoopTime.QuadPart = cEndElapsedTime.QuadPart -
        pInfo->cTotalDecLoopTime.QuadPart;
}

void PerfTimerReport(PERFTIMERINFO *pInfo)
{
    TCHAR           sz[256];
    float           fltDecodeTime;
    float           fltEntireDecodeTime;
    float           fltDecodeTimeFraction;
    float           fltPlaybackTime;
    
    if (pInfo->bIsWindowsNT) {
        STRCPY(sz, 
            256, 
            TEXT("\n** Reporting aggregate of user time in all threads (NT)\n"));
        OUTPUT_DEBUG_STRING(sz);
    }
    
    SPRINTF(sz, 256, TEXT("\n\n** Ticks per second (clock resolution): %f.\n"),
        (float)pInfo->cPerfFrequency.QuadPart);
    OUTPUT_DEBUG_STRING(sz);
    
    fltDecodeTime = (float) pInfo->cDecodeTime.QuadPart /
        (float) pInfo->cPerfFrequency.QuadPart;
    fltEntireDecodeTime = (float) pInfo->cTotalDecLoopTime.QuadPart /
        (float) pInfo->cPerfFrequency.QuadPart;
    SPRINTF(sz, 256, TEXT("** Decode time: %f sec. Entire decode time: \n"),
        fltDecodeTime);
    SPRINTF(sz, 256, TEXT("%f sec.\n"),
        fltEntireDecodeTime);
    OUTPUT_DEBUG_STRING(sz);
    
    fltPlaybackTime = (float) pInfo->cPlaybackTime.QuadPart /
        (float) pInfo->cPerfFrequency.QuadPart;
    SPRINTF(sz, 256, TEXT("** Playback time : %f sec.\n"),
        fltPlaybackTime);
    OUTPUT_DEBUG_STRING(sz);
    
    fltDecodeTimeFraction = (float)pInfo->cDecodeTime.QuadPart /
        (float) pInfo->cPlaybackTime.QuadPart;
    SPRINTF(sz, 256, TEXT("** Percentage of playback time spent decoding: %f%%.\n"),
        fltDecodeTimeFraction * 100);
    OUTPUT_DEBUG_STRING(sz);
#       if defined(WMA_MONITOR)
    fprintf(stderr,"%s\n",sz);
#       endif
    
    SPRINTF(sz, 256, TEXT("** Minimum MHz for realtime playback: %f of current CPU speed.\n"),
        fltDecodeTimeFraction);
    OUTPUT_DEBUG_STRING(sz);
    
    SPRINTF(sz, 256, TEXT("** This CPU is %f times faster than required.\n\n"),
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
    return (float) pInfo->cDecodeTime.QuadPart /
        (float) pInfo->cPerfFrequency.QuadPart;
}


void PerfTimerFree(PERFTIMERINFO *pInfo)
{
    auFree(pInfo);
}

#endif  // PLATFORM_SPECIFIC_PERFTIMER
#endif	// !defined(_WIN32_WCE) || defined(MEASURE_CLOCK)

#ifdef UNDER_CE
#	ifndef _CLOCK_T_DEFINED
		typedef long clock_t;
#		define _CLOCK_T_DEFINED
#	endif

	clock_t __cdecl clock(void) { 
		return (clock_t)GetTickCount(); 
	}

#	ifndef _TIME_T_DEFINED
		typedef long time_t;        /* time value */
#		define _TIME_T_DEFINED     /* avoid multiple def's of time_t */
#	endif

	time_t __cdecl time(time_t * pt) {
		SYSTEMTIME stNowTime;
		SYSTEMTIME st1970 = { 1970, 1, 0, 1, 0, 0, 0, 0 };
		FILETIME   ftNowTime, ft1970;
		ULARGE_INTEGER ulNowTime, ul1970;
		time_t tNowTime;	// seconds since 1/1/1970
		GetSystemTime( &stNowTime );
		if ( SystemTimeToFileTime( &stNowTime, &ftNowTime ) && SystemTimeToFileTime( &st1970, &ft1970 ) )
		{
			ulNowTime.HighPart = ftNowTime.dwHighDateTime;
			ulNowTime.LowPart  = ftNowTime.dwLowDateTime;
			ul1970.HighPart    = ft1970.dwHighDateTime;
			ul1970.LowPart     = ft1970.dwLowDateTime;
			tNowTime = (time_t)( (ulNowTime.QuadPart - ul1970.QuadPart)/10000000 );
		} else 
		{
			tNowTime = (time_t)clock();
		}
		if ( pt != NULL )
			*pt = tNowTime;
		return tNowTime;
	}
#endif


#endif  // WMA_OSTARGET_WIN32 && !WMA_TARGET_ANSI

