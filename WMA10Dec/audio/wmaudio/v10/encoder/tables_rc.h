//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
//+-------------------------------------------------------------------------
//
//  Microsoft Windows Media
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       tables_rc.h
//
//--------------------------------------------------------------------------

#ifndef _TABLES_RC_H_
#define _TABLES_RC_H_

#include "macros.h"
#include "enctypes.h"

#include "dectables.h"
#include "wmavechufftbls.h"
#ifdef USE_V4ENTCODING
#include "enttblsencv4.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BUILD_WMAPRO)

extern const U32    gHuffTblMskV3[];
extern const Int    gSizeHuffTblMskV3;

extern const U32    gHuffTblMaskRunLevelV3 [241];
extern const I16    g_rgiMaskRunLevelVLCV3 [12];

#endif // BUILD_WMAPRO

#if defined(BUILD_WMASTD)

extern const U32    gHuffTblMsk[];
extern const Int    gSizeHuffTblMsk;

extern const U32    gHuffTblRunLevel44smQb[];
extern const U32    gHuffTblRunLevel44ssQb[];
extern const U32    gHuffTblRunLevel44smOb[];
extern const U32    gHuffTblRunLevel44ssOb[];
extern const U32    gHuffTblRunLevel16smOb[];
extern const U32    gHuffTblRunLevel16ssOb[];

extern const I16 g_rgiRunLevelVLCAtLevel44smQb [63];
extern const I16 g_rgiRunLevelVLCAtLevel44ssQb [43];
extern const I16 g_rgiRunLevelVLCAtLevel44smOb [343];
extern const I16 g_rgiRunLevelVLCAtLevel44ssOb [183];
extern const I16 g_rgiRunLevelVLCAtLevel16smOb [74];
extern const I16 g_rgiRunLevelVLCAtLevel16ssOb [44];

#endif // BUILD_WMASTD

extern const Int    g_rgiHuffTblNoisePower[75];
extern const Int    g_iSizeHuffTblNoisePower;

#if !defined(BUILD_INTEGER_MASK)
extern const Float g_rgflt10PowIBandx0_025[60];
#else // !BUILD_INTEGER_MASK
extern const U32 g_rgi10PowIBandx0_025[60];
#endif // BUILD_INTEGER_MASK

#ifdef __cplusplus
}
#endif

#endif // _TABLES_RC_H_
