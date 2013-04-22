//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*************************************************************************

Copyright (C) Microsoft Corporation, 1996 - 1999

Module Name:

    wmaresults.h

Abstract:

    Return codes and definitions.

Author:

    Kazuhito Koishida (kazukoi)       Jan 31, 2003

Revision History:


*************************************************************************/

#ifndef __WMARESULTS_H
#define __WMARESULTS_H

// *****************************************************
//                  WMA return codes
// *****************************************************
// SUCCESS codes
#define WMA_OK                   0x00000000
#define WMA_S_FALSE              0x00000001
#define WMA_S_BUFUNDERFLOW       0x00000002
#define WMA_S_NEWPACKET          0x00000003
#define WMA_S_NO_MORE_FRAME      0x00000004
#define WMA_S_NO_MORE_SRCDATA    0x00000005
#define WMA_S_LOSTPACKET         0x00000006

#define WMA_S_SWITCHCHMODE       0x00010001 // Internal error, corrected internally
// the matrix input to matrixinvert is or close to singular. can not invert or the inversion is not precise.
#define WMA_S_SINGULARMATRIX     0x00010002
#define WMA_S_MODELLING          0x00010003 // Modelling, skip full encode steps
#define WMA_S_CANTMAKEBITS       0x00010004 // Can't make the cMin/cMax bit constraint
#define WMA_S_DEFAULT            0x00010005
#define WMA_S_NOMOREOUTPUT       0x00010006
#define WMA_S_PLLM_NOLPC         0x00010007 // Did not get reliable LPC filter.
#define WMA_S_PLLM_UNSTABLELPC   0x00010008 // unstable LPC can not be converted to LSP domain.

// ERROR codes
#define WMA_E_FAIL               0x80004005
#define WMA_E_OUTOFMEMORY        0x8007000E
#define WMA_E_INVALIDARG         0x80070057
#define WMA_E_NOTSUPPORTED       0x80040000
#define WMA_E_BROKEN_FRAME       0x80040002
#define WMA_E_BUFFEROVERFLOW     0x80040003
#define WMA_E_ONHOLD             0x80040004 
#define WMA_E_NO_MORE_SRCDATA    0x80040005
#define WMA_E_WRONGSTATE         0x8004000A
#define WMA_E_NOMOREINPUT        0x8004000B // Streaming mode: absolutely no more data (returned via GetMoreData callback)

#define WMA_E_BUFFERUNDERFLOW    0x80010001
#define WMA_E_INVALIDRECHDR      0x80010002
#define WMA_E_SYNCERROR          0x80010003
#define WMA_E_NOTIMPL            0x80010004
#define WMA_E_FLUSHOVERFLOW      0x80010005 // Too much input data provided to flush
#define WMA_E_CANNOTPREDICT      0x80010007 // Cannot make bit-constrained VBR prediction due to insufficient data
#define WMA_E_COEFSTRMFILE       0x80010008 // Failure reading or writing from coefficient stream file.
#define WMA_E_FILESTRMFILEIO     0x80010009 // Error in filestrm.c with File I/O (opening, reading or writing).
#define WMA_E_MODELINVALID       0x8001000A // Two-pass VBR model cannot predict using given dependent var
#define WMA_E_INPUTBUFUNDERFLOW  0x8001000B // Two-pass VBR, 2nd pass, not enough input PCM supplied to correlate to output
#define WMA_E_FRAMECAPOVERFLOW   0x8001000C // v2 only
#define WMA_E_NMRPREDICTFAILURE  0x8001000D // Two-pass VBR: predictor is unable to generate a meaningful estimate for global NMR
#define WMA_E_MODELDEVIATION     0x8001000E // Two-pass VBR: current results directly conflict with previous model datapoints (eg, same QStep, diff NMR).
#define WMA_E_MODELNOROOM        0x8001000F // Two-pass VBR: no more room for additional datapoints!

// *****************************************************
//            WMA Voice internal return codes
// *****************************************************
// SUCCESS codes
#define WMA_S_OUTPUT_BUFFER_FULL 0x00020001
#define WMA_S_INPUTBUFFER_EMPTY  0x00020002
#define WMA_S_EOF                0x00020003

// ERROR codes
#define WMA_E_LOSTPACKET         0x80050001

#endif // __WMARESULTS_H

