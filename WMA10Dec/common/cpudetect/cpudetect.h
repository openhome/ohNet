//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) 1996 -- 1998  Microsoft Corporation

Module Name:

    CPUDetect.cpp

Abstract:

    Several CPU detection utilities.

Author:

    Joseph Wu (sjwu@microsoft.com)          05/98
    Bruce Line (blin@microsoft.com)         05/98
    Ming-Chieh Lee (mingcl@microsoft.com)   06/98

Revision History:

*************************************************************************/

#ifndef __CPUDETECT_H_
#define __CPUDETECT_H_

#ifndef _JOLT_
#ifdef _WIN32
#include <basetsd.h>
#endif
#endif

// Currently it is not clear what to do with XBOX regarding registry key accesses.
// Disabling CPU_DOWNGRADE_IF_REGKEY completely tentatively.
#if defined(_XBOX) || defined(_JOLT_)
#   undef   CPU_DOWNGRADE_IF_REGKEY
#endif

#ifndef CALL_CONVENTION
#   if !defined(_XBOX) && !defined(_JOLT_)

/*
 * Under Windows Platform, default command build use stdcall convention.
 * Under Windows CE platform, default build use cdecl convention - because windef.h overide stdcall with
 * _cdecl. To conform to this (some includes windows.h, some not), we by default build cpudect with cdecl call.
 */

#       ifdef UNDER_CE
#           define CALL_CONVENTION  __cdecl
#       else
#           ifdef _WIN32
#           define CALL_CONVENTION  __stdcall
#           else
#           define CALL_CONVENTION
#           endif
#       endif
#   else
#       define CALL_CONVENTION
#   endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CPU_DOWNGRADE_IF_REGKEY)
void CALL_CONVENTION    g_RefreshCPURegKey(void);
void CALL_CONVENTION    setCPUControlMask(unsigned int dControlMask);
#endif // #if defined(CPU_DOWNGRADE_IF_REGKEY)

// HongCho: It's better for these "support" functions to be defined regardless
//          of the platform.  If not supported either because of the architecture
//          or the API, the default return value should be just FALSE.
int CALL_CONVENTION g_SupportMMX (void);
int CALL_CONVENTION g_SupportSSE1 (void);
int CALL_CONVENTION g_SupportSSE2 (void);
int CALL_CONVENTION g_SupportSSE2_Intrin (void);
int CALL_CONVENTION g_SupportSSE2_64_Intrin (void);
int CALL_CONVENTION g_SupportSSE3 (void);
int CALL_CONVENTION g_SupportSSSE3 (void);
int CALL_CONVENTION g_SupportMVI (void);
int CALL_CONVENTION g_SupportCMOV (void);
// g_SupportPNI() has been renamed to g_SupportSSE3().  However, videoBM tree still
// uses g_SupportPNI() and it is currently under a lockdown status, therefore a simple
// fix is introducing a macro to tentatively provide a definition for g_SupportPNI().
#define g_SupportPNI            g_SupportSSE3

#if (defined(_M_IX86) && !defined(UNDER_CE)) || defined(_M_AMD64)
void CALL_CONVENTION            InitLogicProcTable();
unsigned int CALL_CONVENTION    GetNumPhysicalProc();
unsigned int CALL_CONVENTION    GetNumLogicalProc();
unsigned int CALL_CONVENTION    GetNumThreadsDesired();
DWORD_PTR CALL_CONVENTION       GetThreadAffinMaskByIndex(unsigned int uiIndex);
#endif // #if (defined(_M_IX86) && !defined(UNDER_CE)) || defined(_M_AMD64)

#if defined(_M_AMD64) || defined(_M_IA64)
int CALL_CONVENTION g_CPUClock (void);
#endif

#ifdef _M_IX86
int CALL_CONVENTION cpuidIsIntelP5 (void); // To detect Intel P5
int CALL_CONVENTION g_CPUClock (void);
#define _SCRUNCH_INLINEASM
#endif // _M_IX86

#ifdef _Embedded_x86
int CALL_CONVENTION cpuidIsIntelP5 (void); // to detect 486, P5, or P6
#endif

#ifdef macintosh
int CALL_CONVENTION g_SupportAltiVec(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // __CPUDETECT_H_
