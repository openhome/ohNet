//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************

#ifndef __WMAASSERT_H__
#define __WMAASSERT_H__

#ifdef UNDER_CE
  #if !defined WMA_TARGET_ANSI
    #include <windows.h>
  #endif
#endif

#if ( defined(DBG) && ( 1 == DBG )) || defined(_DEBUG) 
  #if (_MSC_VER >= 1300)
    #define WMAASSERT(cond) if (!(cond)) {__debugbreak();}
  #else
    #define WMAASSERT(cond) if (!(cond)) *((int*)0) = 0;
  #endif
#else
  #define WMAASSERT(cond) ((void)0);
#endif

#ifdef assert
#   undef assert
#endif

#define assert WMAASSERT

#endif // __WMAASSERT_H__
