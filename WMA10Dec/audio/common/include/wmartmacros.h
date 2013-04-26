//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************/


#ifndef __WMARTMACROS_H__
#define __WMARTMACROS_H__

#if defined(_WINDOWS) && (_WIN32_WINNT >= 0x600) && !defined(DISABLE_OPT)

#include "wmdsprt.h"

#else // (_WINDOWS) && (_WIN32_WINNT >= 0x600) && !(DISABLE_OPT)

#define AVRT_CODE_BEGIN
#define AVRT_CODE_END
#define AVRT_DATA
#define AVRT_BSS
#define AVRT_VTABLES_BEGIN
#define AVRT_VTABLES_END

#endif // (_WINDOWS) && (_WIN32_WINNT >= 0x600) && !(DISABLE_OPT)

#endif//__WMARTMACROS_H__
