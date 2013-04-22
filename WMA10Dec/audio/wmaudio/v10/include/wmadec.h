//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef __WMADEC_H__
#define __WMADEC_H__

#if defined(SCRAMBLE_GLOBAL_SYMBOL_NAMES) || defined(UNDER_CE)
#include "scramble.h"
#endif

#include "wmatyps.h"
#include "wmaerror.h"
#include "playropt.h"
#include "pcmfmt.h"
#include "wmafmt.h"

//
// The WMA decoder interface has two modes of operation:
//  - normal (no callback)
//  - callback-based
// The difference between the two is in how input gets into the decoder.
//
// In normal mode, input is fed to the decoder by calling audecInput() -
// see below for details on when audecInput() should be called.
//
// In callback mode, input is requested by the decoder via a
// caller-supplied callback function (PFNGETMOREDATA).
//
// The mode is set at initialization time based on the pfnGetMoreData
// member of the audecInitParams struct.  If pfnGetMoreData is NULL,
// the decoder works in callbackless (normal) mode.  If it is non-NULL,
// the decoder works in callback mode.
//
// Most programmers will prefer the normal (callbackless) mode.
// The callback mode exists for device implementations which wish to
// optimize out (remove) the decoder state machine.  In normal mode,
// the decoder uses a somewhat complex set of state variables to keep
// track of what it was decoding when it ran out of data.  When additional
// data is provided via audecInput(), the decoder uses those variables to
// determine what to do next.  The callback mode allows the state variables
// to be eliminated by relying on the callstack to preserve decoder state.
// Note, however, that using the callback mode does not automatically eliminate
// the state variables - a separate code cleanup task (in addition to using
// the callback-based interface) is required to actually realize the potential
// performance benefits of using the callback interface.  
//
// Although it is conceptually possible to mix callback-based and callbackless
// operation in the same session (i.e., the pfnGetMoreData callback sometimes
// returns data and other times returns WMA_E_ONHOLD), no known scenario where
// such operation would be useful exists at the time of this writing, and the
// decoder has not been tested in mixed mode.  In fact, the author vaguely
// recalls that some subtlety in the implementation of ibstrmGetMoreData() required
// making assumptions which might prevent mixed mode from working at all.  I.e.,
// mixing callback-based and callbackless operation is strongly discouraged.
//
// Most of the structures and methods below are used in both modes.  Exceptions:
//  audecInput(): this method should not be used in callback-based mode
//  audecInputParams: this structure is only used in callbackless mode
//  audecInputBufferInfo: this structure is only used in callback-based mode
// A careful reader might make the following observation:
//   audecInput() arguments + audecInputParams ~= audecInputBufferInfo
// Indeed, the information returned by pfnGetMoreData in the audecInputBufferInfo
// structure in callback-based mode is identical to the information passed to
// audecInput() in callbackless mode.  The existence of separate structures is
// purely historical and might some day get cleaned up by making audecInput()
// accept audecInputBufferInfo() (in fact, an internal decoder function used in
// both modes to process each new input buffer - prvNewInputBuffer() - already
// takes audecInputBufferInfo in both modes).
//

//
// Another dimension in which the decoder has two distinct modes of operation is
// WMA SPDIF frame decoding vs packetized (normal) WMA stream decoding.  These
// modes are meant for different WMA stream formats, so the choice is dictated by
// the format of the incoming data.
//
// ASF files (so far) always use the regular/packetized format, where each block
// ("packet") of data given to the decoder is of the same size - WAVEFORMATEX::nBlockAlign.
// But the duration of WMA packets is variable because a WMA packet may contain
// multiple WMA frames (WMA frames can also straddle WMA packet boundaries).
//
// The WMA SPDIF format does not have a packet layer - the decoder receives raw
// WMA frames in this mode.  Each WMA frame has the same duration, and WMA frames
// are related to SPDIF burts in a simple fashion (some modes store exactly 1 WMA
// frame per SPDIF burst, other modes use two SPDIF bursts to store every WMA frame).
// 
// The main difference between the SPDIF and packetized modes as they relate to the
// decoder interface is in the meaining of flags 'fNewPacket' and 'fNoMoreInput' below.
//
// The SPDIF mode is selected by setting audecInitParams::fSPDIF to TRUE in the call to
// audecInit().
//

// 
// The following descriptions apply equally to the audecInputBufferInfo structure
// (callback mode) and to the arguments accepted by audecInput() (callbackless mode).
//
//
// (pbIn,cbIn) represents an input buffer.  A buffer either passed to audecInput()
// or returned by pfnGetMoreData is assumed to remain valid until additional input
// is requested by the decoder, i.e., until one of the decoder methods sets audecState
// to audecStateInput (or audecStateDone).  More details on audecState below.
//
// Please do not pass an input buffer smaller than 8 bytes unless no additional input
// is expected for the current frame/stream (as indicated by fNoMoreInput - see below
// for notes about SPDIF vs packetized modes).  An assert in ibstrmGetMoreData() exsits
// to guard this restriction.  It is theoretically possible to handle buffers as small
// as 3 or 4 bytes in certain cases, but the rule is set at 8 for simplicity.  Also,
// small input buffers are extremely inefficient in the function call and buffer
// bookkeeping overhead they imply.
//
//
//
// fNewPacket and fNewInput have similar meanings but refer to different units of input
// in SPDIF mode vs packetized mode.
//
//
// fNewPacket: in SPDIF mode this flag means that the buffer it is associated with begins
// a new WMA frame.  In packetized (normal) mode this flag indicates that the buffer
// begins a new WMA packet.  In both modes, the decoder requies that every frame/packet
// boundary occur on an input buffer boundary.  I.e., it is not legal to pass two packets
// (packetized mode) or two frames (SPDIF mode) in a single input buffer.
//
//
// fNoMoreInput: in SPDIF mode fNoMoreInput refers to the curret WMA frame (usually
// transmitted as a single SPDIF burst or a pair of back-to-back SPDIF bursts).
// In packetized (normal) mode, fNoMoreInput refers to the entire WMA stream (e.g.,
// the entire audio stream in an ASF file).  Thus fNoMoreInput == TRUE is a frequent
// (frame-periodic) occurrence in SPDIF mode but a once-per-streaming-session occurrence
// in packetized mode.
//
// In both modes, fNoMoreInput indicates that no additional input is expected for the
// current unit of input (as defined above).  The flag is necessary to unblock the
// entropy decoder when the frame/stream ends at or near the end of the passed in
// buffer (the entropy decoder uses lookahead which, without the fNoMoreInput flag,
// would otherwise force it to wait for additional input even though the available
// input may be sufficient to finish decoding the current unit of input).
//
// If fNoMoreInput is set to TRUE and cbIn > 0, fNoMoreInput is assumed to refer to the
// end of the buffer represented by (pbIn,cbIn) - i.e., the decoder processes (pbIn,cbIn)
// and assumes that no further input will be available.  This is the preferred method.
// However, it is also legal (necessary in some situations - e.g., when reading from a
// stream whose size is not known upfront) to set fNoMoreInput to TRUE and cbIn to 0 as
// an after-the-fact indication that the end of the input turns out to have been reached
// when the previous input buffer was passed in.
//
// If cbIn is 0, fNoMoreInput is assumed to be TRUE even if it is set to FALSE.  However,
// callers of the decoder are encouraged to set fNoMoreInput to TRUE explicitly in case
// a different use for 0-length buffers is found in the future and the implicit mechanism
// is removed.
//
// 
// fTime indicates that a timestamp is present whose value (in 100-nanosecond units) is
// in rtTime.  rtTime is not looked at unless fTime is set.  The decoder uses this value
// to return timestamps when audecGetPCM() is called.  Once a timestamp is passed in,
// audecGetPCM() returns timestamps based on that value (extrapolated based on the PCM
// sample count and the sampling rate) until a new value is passed in.
//
//
// cSkipBits is only used/valid in SPDIF mode and indicates that the first few bits (< 8)
// of the first byte pointed to by pbIn should be skipped - i.e., the WMA frame begins
// somewhere in the middle of the first byte.  cSkipBits is only valid at the beginning
// of a WMA frame (when fNewPacket is set to TRUE in SPDIF mode).
//
typedef struct _audecInputBufferInfo {
    WMA_U8*   pbIn;
    WMA_U32   cbIn;
    WMA_Bool  fNewPacket;
    WMA_Bool  fNoMoreInput;
    WMA_Bool  fTime;
    WMA_I64   rtTime;
    WMA_I32   cSkipBits;
    void*     pfnDescramble;
} audecInputBufferInfo;

typedef WMARESULT (*PFNGETMOREDATA)(void* dwUser, audecInputBufferInfo*);

//
// Each of the WMA decoder methods - audecInit(), audecInput(), audecDecode(),
// and audecGetPCM() - has an [out] parameter of the type audecState.  This
// parameter tells the caller which method should be called next.  The following
// caller loop structure is therefore suggested (callbackless/normal mode):
//
//  audecState state;
//  WMA_U32 cSamplesReady;
//  audecInit(..., &state, ...)
//  while (audecStateDone != state) {
//      switch (state) {
//      case audecStateInput: {
//          WMA_U8 *pbIn; WMA_U32 cbIn; ...
//          read_some_input_data(&pbIn, &cbIn, ...); // caller-supplied logic
//          audecInput(pbIn, cbIn, ... &state, ...);
//      }; break;
//      case audecStateDecode: {
//          audecDecode(..., &cSamplesReady, &state, ...);
//      }; break;
//      case audecStateGetPCM: {
//          WMA_U8* pbOut; WMA_U32 cbOut;
//          get_next_output_buffer(&pbOut, &cbOut); // caller-supplied logic
//          audecGetPCM(cSamplesReady, ... pbOut, cbOut, ..., &state, ...);
//      }; break;
//      default: assert(0); // not other states are currently defined
//  }
//
// I.e., each audecXxxx() method sets 'state' according to what the decoder thinks
// the next step should be, and the caller calls the appropriate audecXxxx() method
// based on the returned value of 'state'.
//
// In practice, the above structure may be too loose to fit well within existing
// architectures.  Certain assumptions can be made safely:
//  - in callbackless (normal) mode, audecInit() always set 'state' to audecStateInput
//    (except on error it sets 'state' to audecStateDone).  It is conceivable that
//    a future version of the decoder or bitstream might require the first call to
//    be audecDecode() instead of audecInput(), in which case audecInit() would set
//    'state' to audecStateDecode.  However, no such plans currently exist.  It is
//    difficult to imagine a situation where audecInit() would set 'state' to
//    audecStatePCM, but the flexibility exists in the interface for completeness.
//  - in callback mode, audecInit() always sets 'state' to audecStateDecode (except
//    on error)
//  - audecStateInput() never sets 'state' to audecStateGetPCM.
//  - the only time audecStateInput() sets 'state' to audecStateInput is in certain
//    erratic situations where the input buffer passed to audecInput() is for some
//    reason deemed useless (e.g., a buffer with fNewPacket set to FALSE in SPDIF
//    mode when a new frame is expected because the previous frame has completed).
//  - the only time audecGetPCM() sets 'state' to audecStateGetPCM is when the
//    output buffer passed to audecGetPCM() is too small to receive the number of
//    available output samples returned by audecDecode() (cSamplesReady above).
// An assumption that is markedly NOT valid is that audecGetPCM() always sets
// 'state' to audecStateInput.  In fact, audecGetPCM() routinely sets 'state' to
// audecStateDecode.  While cycling between Decode and GetPCM might seem redundant
// (i.e., "why not decode all of the available input so that the next thing after
// GetPCM is audecInput"), the find granularity of audecDecode() operations allows
// output to be available sooner than it would otherwise be, and the fine processing 
// granularity makes scheduling easier on systems/devices that do not have threads.
//
// Any of the audecXxxx() methods set 'state' to audecStateDone when an unrecoverable
// error occurs.  audecInit() or audecReset() must be called to clear audecStateDone.
//
// audecGetPCM() sets 'state' to audecStateInput (callbackless/normal mode) or
// audecStateDecode (callback mode) if fNoMoreInput was set to TRUE on
// the most recent input buffer, and that input buffer has been fully decoded and
// its output fetched.
//
// audecReset() does not take an audecState argument.  The state is implicitly
// audecStateInput (callbackless/normal mode) or audecStateDecode (callback mode)
// after audecReset() returns (assuming that the most recent audecInit() call succeeded).
//
// The decoder remembers what it set the state to during the most recent call,
// and each of { audecInput(), audecDecode(), audecGetPCM() } checks the stored
// state.  These functions assert and return an error if called unexpectedly.
//
// audecDecode() / audecGetPCM() will never set 'state' to audecStateInput (and
// audecState() should never be called) if a non-NULL value was passed for
// pfnGetMoreData to audecInit().
//
typedef enum _audecState {
  audecStateDone = 0,
  audecStateInput,
  audecStateDecode,
  audecStateGetPCM
} audecState;

// If you use any of the structures below, please memset() the entire struct to 0 before setting its fields.
// This will ensure reasonable default behavior if a new member is added but the calling code is not updated.

typedef struct _audecInitParams {
    WMA_I32 iMemBufUsed; // [out]
    PFNGETMOREDATA pfnGetMoreData; // [in] set to NULL for normal (callbackless) mode
    void*    dwUser; // [in] context for pfnGetMoreData (ignored if pfnGetMoreData==NULL)
    WMA_Bool fSPDIF; // [in] TRUE for SPDIF mode, FALSE for packetized (normal) mode
} audecInitParams;

typedef struct _audecInputParams {
    WMA_I32 cSkipBits;         // SPDIF only - see above
    void* pfnDescramble;
} audecInputParams;

typedef struct _audecDecodeParams {
    WMA_I32 cbFrameBytesInLastBuffer; // [out] SPDIF only, obsolete - superseded by an SPDIF payload header field
} audecDecodeParams;

typedef struct _audecGetPCMParams {
    WMA_U32 dwReserved;
} audecGetPCMParams;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void* audecNew (void *pMemBuf, // [in] (normally NULL) user-supplied memory for heapless environments
                const WMA_I32 iMemBufSize);
void audecDelete (void* paudec);
WMARESULT audecCheckInitParams(WMAFormat*, PCMFormat*, WMAPlayerInfo *pPI,
                               audecInitParams* pParams);
WMARESULT audecInit (void* paudec, WMAFormat* pWMAFormat, PCMFormat* pPCMFormat,
                                   WMAPlayerInfo *pPI, audecState *paudecState,
                                   audecInitParams* pParams);

WMARESULT audecReset (void* paudec);
WMARESULT audecInput (void* paudec,
                      WMA_U8* pbIn, // [in]
                      WMA_U32 cbIn,
                      WMA_Bool  fNewPacket,
                      WMA_Bool fNoMoreInput,
                      WMA_Bool  fTime,
                      WMA_I64 rtTime,
                      audecState* paudecState, // [out]
                      audecInputParams* pParams // [in]
                     );
WMARESULT audecDecode (void* paudec,
                       WMA_U32* pcSamplesReady, // [out] - how much is availble from GetPCM()
                       audecState* paudecState, // [out]
                       audecDecodeParams* pParams // [out]
                      );

WMARESULT audecGetPCM (void* paudec,
                       WMA_U32 cSamplesRequested, // up to *pcSamplesReady (from audecDecode())
                       WMA_U32 *pcSamplesReturned, // [out] redundant with *pcbDstUsed below
                       WMA_U8* pbDst,
                       WMA_U32 cbDstLength, // ~ redundant with cSamplesRequested
                       WMA_U32* pcbDstUsed, // [out] redundant with *pcSamplesReturned above
                       WMA_I64* prtTime, // [out] time stamp (in 100ns) of 1st sample returned
                       audecState *paudecState, // [out]
                       WMAPlayerInfo *pWmaPI, // [in] - dynamic configuration of some Init params
                       audecGetPCMParams* pParams
                      );

WMARESULT audecSetPlayerInfo(void* pDecHandle, 
                             audecState *paudecState, 
                             WMAPlayerInfo *pPI,
                             WMA_Bool fSetChDnMixMtx,
                             WMA_Bool fSetDRCRefAndTarget);

WMARESULT audecChangeOutputFormat(void* pDecHandle,
                                  PCMFormat* pPCMFormat,
                                  WMA_Bool fTestOnly);

WMARESULT WMAPktParseDownmixCoeffToMatrix(WMA_I32 *rgiDownMix,  // [out] - downmix matrix of size cDstChannel * cSrcChannel, can't be NULL
                                          WMA_I32 *rgiCoeff,    // [in]  - matrix parameters sent, can't be NULL
                                          WMA_I32 iNumCoeff,    // [in]  - number of parameters, can't be NULL
                                          WMA_I32 cNumInCh,     // [in]  - number of input channels
                                          WMA_I32 cNumOutCh,    // [in]  - number of output channels
                                          WMA_U32 dwInChMask,   // [in]  - input channel mask
                                          WMA_U32 dwOutChMask); // [in]  - output channel mask

#ifdef __cplusplus
}
#endif  // __cplusplus

#define WAVEFORMATEX2audecInitParams(a,b) { \
}

#endif//__WMADEC_H__
