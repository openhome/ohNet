//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#if !defined(_AUTO_PROFILE_INCLUDED_)
#define _AUTO_PROFILE_INCLUDED_

#if defined(WMAPROFILE) 

#define WIN32_LEAN_AND_MEAN

#pragma warning( disable : 4103 4142 )
#include <windows.h>   
#pragma warning( default : 4103 4142 )
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_FUNCTIONS_TO_PROFILE 100

typedef struct  
{
    int id;
    TCHAR name[80];
}ProfileFunctionDeffinitionType;

extern ProfileFunctionDeffinitionType functionDefintions[MAX_FUNCTIONS_TO_PROFILE];
extern int Profiler_functionCountCalls[];


#define FFT_PROFILE 1
#define INVERSE_QUAN_HIGH_RATE_PROFILE 2
#define INVERSE_TRANSFORM_AND_RECON_PROFILE 3
#define INVERSE_OUANTIZE_SPECTRUM_PROFILE 4
#define DCTIV_PROFILE 5
#define POWER_TO_RMS_PROFILE 6 
#define ADAPT_TO_SUB_FRAME_CONFIG_PROFILE 7
#define INVERSE_TRANSFORM_MONO_PROFILE 8
#define DECODE_FRAME_HEADER_PROFILE 9
#define DECODE_COEFFICENT_MONO_PROFILE 10
#define DECODE_COEFFICENT_STEREO_PROFILE 11
#define DECODE_RUN_LEVEL_PROFILE 12
#define SET_DET_TABLE_PROFILE 13
#define DECODE_SUB_FRAME_PROFILE 14
#define UPDATE_SUB_FRAME_CONFIG_PROFILE 15
#define CALC_QUANT_STEP_PROFILE 16
#define DECODE_FRAME_PROFILE 17
#define DECODE_PACKET_PROFILE 18 
#define DECODE_PROFILE 19
#define CONVERT_SD_TO_LR_PROFILE 20
#define HUFF_DEC_GET_PROFILE 21
#define MSAC_DECODE_PROFILE 22
#define INVERSE_QUAN_HIGH_SDTOLR_PROFILE 23
#define SAVE_HISTORY_MONO_PROFILE 24

#define FRAME_HEADER_LPC_PROFILE 25
#define FRAME_HEADER_NOISE_SUB_PROFILE 26
#define GET_BAND_WEIGHTS_PROFILE 27
#define INVERSE_QUAN_LOW_RATE_PROFILE 28
#define INVERSE_QUAN_MID_RATE_PROFILE 29

#define WMA_FILE_DECODE_DATA_PROFILE 30
#define AU_GET_PCM_PROFILE 31
#define RECON_MONO_PROFILE 32
#define AUDEC_DECODE_DATA_PROFILE 33
#define WMA_FILE_GET_PCM_PROFILE 34
#define DECODE_COEFFICENTS_HIGH_RATE_PROFILE 35
#define DECODE_SUB_FRAME_HIGH_RATE_PROFILE 36
#define LPC_TO_SPECTRUM_PROFILE 37
#define FFT32_PROFILE 38

#if 1
#define Profiler_getTimer(ptime64) QueryPerformanceCounter((LARGE_INTEGER*)ptime64)
#else
__inline __int64 Profiler_getTimer(__int64 *time64)
{
    __int64 time;
    QueryPerformanceCounter((LARGE_INTEGER*)&time);
    *time64 = time;
    return time;
}
#endif
 
extern void Profiler_init(LPCTSTR szFileName);
extern void Profiler_initEX(LPCTSTR szFileName,int fAppend);
extern void Profiler_close();
extern void Profiler_closeEX(unsigned int Duration, DWORD TotalTime, LPCTSTR szMsg);
extern void Profiler_print(LPCTSTR szMsg);

typedef struct 
{
    __int64 StartTime;
    int functionIndex;
    void *parent;
}FunctionProfile;

extern __int64 Profiler_functionTimings[MAX_FUNCTIONS_TO_PROFILE];
extern __int64 Profiler_functionPlusChildTimings[MAX_FUNCTIONS_TO_PROFILE];
extern __int64 Profiler_totalTime;
extern __int64 profileStartTime;
extern HANDLE hProfile;
extern FunctionProfile *Profiler_lastFunctionProfiler;



void Profile_print(LPCTSTR fmt);


__inline void FunctionProfileStart(FunctionProfile *fp, int FunctionID) 
{
    Profiler_getTimer(&fp->StartTime);
    fp->functionIndex = FunctionID;
    fp->parent = Profiler_lastFunctionProfiler;
    Profiler_lastFunctionProfiler = fp;
	Profiler_functionCountCalls[FunctionID]++;
};

__inline void FunctionProfileStop(FunctionProfile *fp){
    __int64 endTime;
    __int64 time;
    Profiler_getTimer(&endTime);
    time = (int)(endTime-fp->StartTime);
    
    Profiler_functionTimings[fp->functionIndex] += time;

    if (fp->parent != NULL) {
        Profiler_functionTimings[((FunctionProfile*)(fp->parent))->functionIndex] -= time;
    } else {
        Profiler_totalTime+=time; 
    }

    Profiler_functionPlusChildTimings[fp->functionIndex] += time;
    Profiler_lastFunctionProfiler = ((FunctionProfile*)(fp->parent));
}

#define FUNCTION_PROFILE(fp) FunctionProfile fp;
#define FUNCTION_PROFILE_START(fp,id) FunctionProfileStart(fp,id)
#define FUNCTION_PROFILE_STOP(fp) FunctionProfileStop(fp)

#ifdef __cplusplus
}
#endif

#else	// !WMAPROFILE
#define FUNCTION_PROFILE(fp)
#define FUNCTION_PROFILE_START(fp,id)
#define FUNCTION_PROFILE_STOP(fp)

#endif	// !WMAPROFILE

#endif  // !defined(_AUTO_PROFILE_INCLUDED_)

