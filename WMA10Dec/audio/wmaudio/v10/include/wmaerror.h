//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef __WMAERROR_H__
#define __WMAERROR_H__

#include "wmatyps.h"

// SUCCESS codes
#define WMA_OK                0x00000000
#define WMA_S_FALSE           0x00000001
#define WMA_S_BUFUNDERFLOW    0x00000002
#define WMA_S_NEWPACKET       0x00000003
#define WMA_S_NO_MORE_FRAME   0x00000004
#define WMA_S_NO_MORE_SRCDATA 0x00000005
#define WMA_S_LOSTPACKET      0x00000006
#define WMA_S_NEW_PROPERTIES  0x00000007 // Need to reinitialize codec
#define WMA_S_DEC_PARTIAL_INIT 0x00000008 // UES decoder partially initialized

// ERROR codes
#define WMA_E_FAIL            0x80004005
#define WMA_E_OUTOFMEMORY     0x8007000E
#define WMA_E_INVALIDARG      0x80070057
#define WMA_E_NOTSUPPORTED    0x80040000
#define WMA_E_BROKEN_FRAME    0x80040002
#define WMA_E_BUFFEROVERFLOW  0x80040003
#define WMA_E_ONHOLD          0x80040004 
#define WMA_E_NO_MORE_SRCDATA 0x80040005
#define WMA_E_WRONGSTATE      0x8004000A
#define WMA_E_NOMOREINPUT     0x8004000B // Streaming mode: absolutely no more data (returned via GetMoreData callback)

// wmaerrormacros.h defines following too.
#ifndef WMA_SUCCEEDED
#define WMA_SUCCEEDED(Status) ((WMARESULT)(Status) >= 0)
#endif //WMA_SUCCEEDED

#ifndef WMA_FAILED
#define WMA_FAILED(Status) ((WMARESULT)(Status)<0)
#endif //WMA_FAILED

#endif//__WMAERROR_H__
