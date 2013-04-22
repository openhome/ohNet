//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __WMAUDIO_INC_H_
#define __WMAUDIO_INC_H_

#define STDCALL __stdcall // For drmpd_ext.h

#include <stdio.h>

#ifndef __arm
#include "malloc.h"
#else
#define FAR
#define TRUE  1
#define FALSE 0
#endif //__arm

//#pragma warning( disable : 4005 )
#if ( defined(BOOL) || defined(_WIN32_WCE) ) && !defined(_BOOL_DEFINED)
#define _BOOL_DEFINED
#endif
#include "wmatypes.h"
#include "playropt.h"
#include "wmaudio.h"
#include "wmaudio_type.h"
#include "loadstuff.h"
#include "wmaguids.h"
#include "wavfileexio.h"
#include "AutoProfile.h"

#ifdef USE_SPDTX
#include "spdtx.h"

// !! having this typedef here is not very wise,
// but it releases asfparse_s from its dependency
// upon msaudiodec.h in the SPDIF transmitter case.
// this is preferred because msaudiodec.h drags
// in many decoder headers that are otherwise
// irrelevant to the transmitter.

typedef struct WmaGetDataParam
{
    U32  m_dwUser;
    Bool m_fTimeIsValid;
    I64  m_iTime;
} WmaGetDataParam;

#else

#include "msaudiodec.h"
#include "wmadec.h"
#endif

#ifndef MIN
#define MIN(x, y)  ((x) < (y) ? (x) : (y))
#endif /* MIN */

#define WMAAPI_DEMO_LIMIT 60
#define CALLBACK_BUFFERSIZE WMA_MAX_DATA_REQUESTED*2

//static const WMARESULT WMA_E_ONHOLD         = 0x80040004; 

#define WMAFileGetInputParam WmaGetDataParam


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

WMARESULT WMAFileGetInput (tWMAFileStateInternal *pInt, U8 **ppBuffer, U32 *pcbBuffer, WMAFileGetInputParam*);
tWMAFileStatus WMAF_UpdateNewPayload (tWMAFileStateInternal *pInt);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // wmaudio_inc.h
