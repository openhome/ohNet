//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#define WIN32_LEAN_AND_MEAN

//#pragma warning( disable : 4103 )
#include "../include/AutoProfile.h"

#ifdef WMAPROFILE

#include <stdio.h>
//#include <assert.h>
#include <tchar.h>

//****************************************************************************************
//
// The Zen and the Art of Profiling 
//   by Sil after much befuddlement
//
// Profile as few things as possible to get your result.  
//
// Each profile start-stop pair costs 3.770 microsocnds on a 500MHz Pentium.
// So profiling a per-coefficent function like getNextRunLevelHighRate costs 
// 2.3 seconds of execution time for a process which otherwise only takes 1.6 seconds
//
// Unless you correct for the start-stop overhead, changing the profile configurtation
// will effect the overall results.  A spreadsheet could take this current output and
// do such a correction - given you measure the start-stop overhead of your test machines.
//
// The start-stop overhead gets distributed to the parent and the child functions.
//
// Some runs are significantly off - if the results don't make sense, repeat them.
//
// But similiar runs are pretty similar.  I have not quantified the variance.
//
//****************************************************************************************
   
ProfileFunctionDeffinitionType Profiler_functionDefintions[MAX_FUNCTIONS_TO_PROFILE] = {0,_T(""),

MSAC_DECODE_PROFILE					,_T("Decode"),
DECODE_PROFILE                      ,_T("..audecDecode"),
WMA_FILE_DECODE_DATA_PROFILE        ,_T("..WMAFileDecodeData"),
DECODE_PACKET_PROFILE               ,_T("....DecodePacket"),
DECODE_FRAME_PROFILE                ,_T("......DecodeFrame"),
AUDEC_DECODE_DATA_PROFILE           ,_T("......audecDecodeData"),
SAVE_HISTORY_MONO_PROFILE			,_T("........Save History Mono"),
DECODE_SUB_FRAME_PROFILE            ,_T("........DecodeSubFrame"),
DECODE_SUB_FRAME_HIGH_RATE_PROFILE  ,_T("........DecodeSubFrameHighRate"),
DECODE_FRAME_HEADER_PROFILE         ,_T("..........DecodeFrameHeader"),
UPDATE_SUB_FRAME_CONFIG_PROFILE     ,_T("............UpdateSubFrameConfig"),
ADAPT_TO_SUB_FRAME_CONFIG_PROFILE   ,_T("............AdaptToSubFrameConfig"),
SET_DET_TABLE_PROFILE               ,_T("............SetDetTable"),
FRAME_HEADER_NOISE_SUB_PROFILE		,_T("............DecodeFrameHeaderNoiseSub"),
FRAME_HEADER_LPC_PROFILE			,_T("............DecodeFrameHeaderLpc"),
LPC_TO_SPECTRUM_PROFILE  			,_T("..............prvLpcToSpectrum"),
FFT32_PROFILE                       ,_T("................prvFFT32"),
GET_BAND_WEIGHTS_PROFILE			,_T("............GetBandWeightXxxRate"),
INVERSE_QUAN_HIGH_RATE_PROFILE      ,_T("..........InverseQuantizeHighRate"),
DECODE_COEFFICENTS_HIGH_RATE_PROFILE,_T("..........ReconCoefficentsHighRate"),

DECODE_COEFFICENT_STEREO_PROFILE    ,_T("..........DecodeCoefficientStereo"),
DECODE_COEFFICENT_MONO_PROFILE      ,_T("............prvDecodeCoefficientMono"),
DECODE_RUN_LEVEL_PROFILE            ,_T("..............prvDecodeRunLevel"),
HUFF_DEC_GET_PROFILE                ,_T("................HuffDecGet"),
INVERSE_QUAN_HIGH_SDTOLR_PROFILE	,_T("..........InverseQuantizeHighRateSDtoLR"),
INVERSE_QUAN_LOW_RATE_PROFILE		,_T("..........prvInverseQuantizeLowRate"),
INVERSE_QUAN_MID_RATE_PROFILE		,_T("..........prvInverseQuantizeMidRate"),
DCTIV_PROFILE                       ,_T("..........DctIV"),
FFT_PROFILE                         ,_T("............FFT"),

WMA_FILE_GET_PCM_PROFILE            ,_T("..WMAFileGetPCM"),
AU_GET_PCM_PROFILE                  ,_T("....auGetPCM"),
INVERSE_TRANSFORM_AND_RECON_PROFILE ,_T("........InverseTransformAndRecon"),
INVERSE_TRANSFORM_MONO_PROFILE		,_T("..........InverseTransformMono"),
RECON_MONO_PROFILE          		,_T("..........ReconMono"),
CONVERT_SD_TO_LR_PROFILE            ,_T("Convert s/d to l/r"),
INVERSE_OUANTIZE_SPECTRUM_PROFILE	,_T("Quantize Spectrum"),
0,_T("")
}; 

int     Profiler_functionCountCalls[MAX_FUNCTIONS_TO_PROFILE];
__int64 Profiler_functionTimings[MAX_FUNCTIONS_TO_PROFILE];
__int64 Profiler_functionPlusChildTimings[MAX_FUNCTIONS_TO_PROFILE];
__int64 Profiler_totalTime;
__int64 profileStartTime;
HANDLE hProfile;
FunctionProfile *Profiler_lastFunctionProfiler;

void Profiler_init(LPCTSTR wcsProfilerName )
{
	Profiler_initEX(wcsProfilerName, 0 );
}

void Profiler_initEX(LPCTSTR szProfilerName, int fAppend )
{
    LONGLONG startTime;
#if defined(_UNICODE) || defined(UNICODE)
	LPCTSTR wcsProfilerName = szProfilerName;
#else
    WCHAR wcsProfilerName[200];
    mbstowcs( wcsProfilerName, szProfilerName, strlen(szProfilerName)+1 );
#endif

    hProfile = CreateFileW(wcsProfilerName, 
						   GENERIC_WRITE, FILE_SHARE_WRITE, NULL, 
						   fAppend ? OPEN_ALWAYS : CREATE_ALWAYS, 
						   FILE_ATTRIBUTE_NORMAL, NULL);

	if ( fAppend && hProfile != NULL )
		SetFilePointer( hProfile, 0L, NULL, FILE_END ); 

	memset( Profiler_functionCountCalls, 0, sizeof(int)*MAX_FUNCTIONS_TO_PROFILE );
	memset( Profiler_functionTimings, 0, sizeof(__int64)*MAX_FUNCTIONS_TO_PROFILE );
	memset( Profiler_functionPlusChildTimings, 0, sizeof(__int64)*MAX_FUNCTIONS_TO_PROFILE );

    Profiler_lastFunctionProfiler = NULL;
    Profiler_totalTime = 0;
    Profiler_getTimer(&startTime);
    profileStartTime = startTime;
}

void Profiler_print(LPCTSTR szMsg)
{
    DWORD dwBytesWritten;		
    if (hProfile)
    {
        WriteFile(hProfile, (void*) szMsg, sizeof(TCHAR) * _tcslen(szMsg), &dwBytesWritten, NULL);
    }		
}

void Profiler_close(void)
{
	Profiler_closeEX(0,0,NULL);
}

void Profiler_closeEX(unsigned int Duration, DWORD TotalTime, LPCTSTR szMsg)
{
    LONGLONG stopTime;
    int i = 1;
    TCHAR buff[120];
	float fltTotalTime;
    Profiler_getTimer(&stopTime);
    Profiler_totalTime = stopTime-profileStartTime;
	fltTotalTime = (float)Profiler_totalTime;
	if (szMsg != NULL)
		Profiler_print(szMsg);
    _stprintf(buff,_T("Total Time %10.0f\r\n\r\n"),fltTotalTime);
    Profiler_print(buff);
	if ( Duration != 0 && TotalTime != 0 )
	{	// change duration to media play duration converted to profiling time units
		fltTotalTime = Duration * (fltTotalTime/TotalTime);
		_stprintf(buff,_T("Play Time  %10.0f ms == %10.0f profile time units.\r\n\r\n"),(float)Duration, fltTotalTime);
		Profiler_print(buff);
	}
    _stprintf(buff,_T("  Function   Function  Function  Function\r\n"));
    Profiler_print(buff);
    _stprintf(buff,_T("   + child       only  + child   only\r\n"));
    Profiler_print(buff);
    _stprintf(buff,_T("      time       time  ratio     ratio     Count  Function Name\r\n\r\n"));
    Profiler_print(buff);
    do {
        int j = Profiler_functionDefintions[i].id;
        if (Profiler_functionPlusChildTimings[j] > 0) {
            
            _stprintf(buff,_T("%10.0f %10.0f  %7.5f   %7.5f %7d  %s,\r\n"),
				(float)(Profiler_functionPlusChildTimings[j]),
				(float)(Profiler_functionTimings[j]),
				((float)Profiler_functionPlusChildTimings[j]/fltTotalTime),
				((float)Profiler_functionTimings[j]/fltTotalTime),
				Profiler_functionCountCalls[j],
				Profiler_functionDefintions[i].name);
            Profiler_print(buff);
        }
    } while (++i < MAX_FUNCTIONS_TO_PROFILE);

	CloseHandle(hProfile);
}
#endif	// WMAPROFILE
