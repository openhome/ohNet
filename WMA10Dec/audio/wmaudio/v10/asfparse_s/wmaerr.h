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
//  File:       wmaerr.h
//
//--------------------------------------------------------------------------

#ifndef WMAERR_H
#define WMAERR_H

#ifndef _WMAERR_DEFINED
#define _WMAERR_DEFINED
typedef int WMAERR;
#endif /* _WMAERR_DEFINED */

#define WMAERR_OK               0
#define WMAERR_FAIL             1
#define WMAERR_INVALIDARG       2
#define WMAERR_BUFFERTOOSMALL   3
#define WMAERR_INVALIDHEADER    4
#define WMAERR_OUTOFMEMORY      5
#define WMAERR_CORRUPTDATA      6
#define WMAERR_NOTDONE          7 /* need more data to finish the work */
#define WMAERR_INVALIDSTATE     8

#endif // WMAERR_H
