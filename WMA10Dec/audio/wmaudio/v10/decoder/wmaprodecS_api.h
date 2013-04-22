//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef _WMAPRODECRAW_API_H_
#define _WMAPRODECRAW_API_H_
typedef void  WMA_VOID;
#ifndef __PLAYROPT_H__
#define __PLAYROPT_H__

// **************************************************************************
// Player Options
// **************************************************************************
#define PLAYOPT_HALFTRANSFORM      0x0002
#define PLAYOPT_PAD2XTRANSFORM     0x0008
#define PLAYOPT_DYNAMICRANGECOMPR  0x0080
#define PLAYOPT_LTRT               0x0100
#define PLAYOPT_IGNOREFREQEX       0x0200
#define PLAYOPT_IGNORECX           0x0400

// defines for WMAVoice
// in this CPU_RESOURCE field, 0 and 4 both equate to a 206 MHz StrongARM level of cpu performance.  
// Some future release may implement auomatic adaption for 0 but not for 4.
// 1 is suitable for an ARM7 or ARM9 implementation that runs at about 70 MHz.
// other CPU's should probably pass 0 but can try other values.
// the codec may apply higher levels of post processing for higher levels of this value which will result in higher quality.
// However, raising the number too far will cause the codec to try too complex post processing and result in stuttering audio.
#define PLAYOPT_CPU_RESOURCE_MASK   0x000F0000
#define PLAYOPT_CPU_RESOURCE_AUTO   0
#define PLAYOPT_CPU_RESOURCE(a) ((a)<<16)
#define PLAYOPT_CPU_RESOURCE_LOW    PLAYOPT_CPU_RESOURCE(2)
#define PLAYOPT_CPU_RESOURCE_NORMAL PLAYOPT_CPU_RESOURCE(8)

// **************************************************************************
// Dynamic Range Control settings
// **************************************************************************
#define WMA_DRC_HIGH 0
#define WMA_DRC_MED 1
#define WMA_DRC_LOW 2

// **************************************************************************
// Player Info Structure
// **************************************************************************

typedef struct _WMAPlayerInfo
{
    WMA_U16 nPlayerOpt;        // Bit fields based on above defines
    WMA_I32 *rgiMixDownMatrix; // Can be null to invoke defaults
    WMA_I32 iPeakAmplitudeRef;
    WMA_I32 iRmsAmplitudeRef;
    WMA_I32 iPeakAmplitudeTarget;
    WMA_I32 iRmsAmplitudeTarget;
    WMA_I16 nDRCSetting;       // Dynamic range control setting
    WMA_I32 iLtRtBufsize;
    WMA_I32 iLtRtQuality;
} WMAPlayerInfo;

#endif//__PLAYROPT_H__


//PCMFormat
#ifndef __PCMFMT_COM_H__
#define __PCMFMT_COM_H__

typedef enum _PCMData {
    PCMDataPCM        = 0,
    PCMDataIEEE_FLOAT = 1,
} PCMData;

#pragma pack (push)
#pragma pack () // default
typedef struct _PCMFormat {
    WMA_U32 nSamplesPerSec;               
    WMA_U32 nChannels;
    WMA_U32 nChannelMask;
    WMA_U32 nValidBitsPerSample;
    WMA_U32 cbPCMContainerSize;
    PCMData pcmData;
} PCMFormat;
#pragma pack (pop)

#endif//__PCMFMT_COM_H__

//WMAFORMAT
#ifndef __WMAFMT_COM_H__
#define __WMAFMT_COM_H__

#pragma pack (push)
#pragma pack () // default
typedef struct _WMAFormat {
    WMA_U16 wFormatTag;
    WMA_U16 nChannels;
    WMA_U32 nSamplesPerSec;
    WMA_U32 nAvgBytesPerSec;
    WMA_U16 nBlockAlign;
    WMA_U16 nValidBitsPerSample;
    WMA_U32 nChannelMask;
    WMA_U16 wEncodeOpt;
    WMA_U16 wAdvancedEncodeOpt;
    WMA_U32 dwAdvancedEncodeOpt2;
} WMAFormat;
#pragma pack (pop)

#endif//__WMAFMT_COM_H__

//
// The WMAProRawDec interface has two modes of operation:
//  - normal (no callback)
//  - callback-based
// The difference between the two is in how input gets into the decoder.
//
// In normal mode, input is fed to the decoder by calling WMAProRawDecInit()
//
// In callback mode, input is requested by the decoder via a
// caller-supplied callback function (PFNWMAPROGETMOREDATA).
//
// The mode is set at initialization time based on the pfnGetMoreData
// member of the WMAProRawDecInitParams struct.  If pfnGetMoreData is NULL,
// the decoder works in callbackless (normal) mode.  If it is non-NULL,
// the decoder works in callback mode.
//

// **************************************************************************
// A flow chart demonstrating the usage of the functions defined in this
// header file.  This flowchart does not accommodate error conditions.
//
// The chart also enumerates all currently possible transition states. 
// (in the future, no guarantees, all transitions possible)
//
//                             |
//                             |
//                             V
//                     -------------------
//                    | WMAProRawDecNew() |
//                     -------------------
//                             |
//                             |
//                             V
//                     --------------------
//                    | WMAProRawDecInit() |
//                     --------------------
//                             |
//                             |   
//              |----> normal (callbackless mode)? <------------
//              |              |                               |
//              |              |      NO                       |
//              |              |--------------------           |
//              |              |                   |           |
//              |              | Yes               |           |
//              |              |                   |           |
//              |    WMAProRawDecStateInput <--    |           |
//              |              |              |    |           |
//              |              |              |    |           |
//              |              V              |    |           |
//              |     ---------------------   |    |           |
//              |    | WMAProRawDecInput() |  |    |           |
//              |     ---------------------   |    |           |
//              |              |              |    |           |
//              |              |---------------    |           |
//    Need more |              |                   |           |
//       data   |              |                   |           |
//              |              |                   |           |
//              |   WMAProRawDecStateDecode <------            |
//              |              |                   |           |
//              |              |                   |           |
//              |              V                   |           |
//              |    ----------------------        |           |
//              |   | WMAProRawDecDecode() |       |           |
//              |    ----------------------        |           |
//              |              |                   |           |
//              ---------------|                   |           |
//                             |                   |           |
//                             |--------------------           |
//                             |                   |           |
//                    MAProRawDecStateGetPCM <---  |           |
//                             |                |  |           |
//                             V                |  |           |
//                   ----------------------     |  |           |
//                  | WMAProRawDecGetPCM() |    |  |           |
//                   ----------------------     |  |           |
//                             |                |  |           |
//                             |-----------------  |           |
//                             |                   |           |
//                             |--------------------           |
//                             |--------------------------------                            
//                             |  
//                   WMAProRawDecStateDone                          
//                             |                            
//                             V                            
//                    ----------------------
//                   | WMAProRawDecDelete() |
//                    ----------------------
//
//
// WMAProRawDecStateInput, WMAProRawDecStateDecode, WMAProRawDecStateGetPCM and WMAProRawDecStateDone
// are decoder status returned from WMAProRawDecInit(), WMAProRawDecInput(), WMAProRawDecDecode()
// and WMAProRawDecGetPCM().
//
// **************************************************************************


// WMAProRaw Decoder handle
typedef void* WMAProRawDecHandle;

// WMAProRaw Decoder Status
typedef enum _WMAProRawDecState {
  WMAProRawDecStateDone = 0,
  WMAProRawDecStateInput,
  WMAProRawDecStateDecode,
  WMAProRawDecStateGetPCM
} WMAProRawDecState;

// this structure is only used in callback-based mode
typedef struct _WMAProRawDecInputBufferInfo {
    WMA_U8*   pbIn;
    WMA_U32   cbIn;
    WMA_Bool  fNewPacket;
    WMA_Bool  fNoMoreInput;
    WMA_Bool  fTime;
    WMA_I64   rtTime;
} WMAProRawDecInputBufferInfo;

// caller-supplied callback function used in callback mode
typedef WMARESULT (*PFNWMAPROGETMOREDATA)(WMAProRawDecInputBufferInfo*);

// If you use any of the structures below, please memset() the entire struct to 0 before setting its fields.
// This will ensure reasonable default behavior if a new member is added but the calling code is not updated.

typedef struct _WMAProRawDecInitParams {
    WMA_I32 iMemBufUsed;                 // [out]
    PFNWMAPROGETMOREDATA pfnGetMoreData; // [in] set to NULL for normal (callbackless) mode
    WMA_U32 dwUser;                      // [in] context for pfnGetMoreData (ignored if pfnGetMoreData==NULL)
    WMA_Bool fSPDIF;                     // [in] SPDIF mode in not supported, always set to FALSE for packetized (normal) mode
} WMAProRawDecInitParams;

//SPDIF mode is not supported by WMAProRawDec APIs
typedef struct _WMAProRawDecInputParams {
    WMA_I32 cSkipBits;                   // [in] SPDIF only
} WMAProRawDecInputParams;

typedef struct _WMAProRawDecDecodeParams {
    WMA_I32 cbFrameBytesInLastBuffer;    // [out] SPDIF only, obsolete - superseded by an SPDIF payload header field
} WMAProRawDecDecodeParams;

typedef struct _WMAProRawDecGetPCMParams {
    WMA_U32 dwReserved;
} WMAProRawDecGetPCMParams;


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// **************************************************************************
// WMAProRawDecNew()
// This function create a WMAProRawDec handle
//
// Return values
// WMA_OK              indicates success
// WMA_E_FAIL          indicates failure
// **************************************************************************
WMARESULT WMAProRawDecNew (
    WMAProRawDecHandle* pphWMAProRawDec, // [out] WMAProRawDec handle 
    void *pMemBuf,                       // [in] (normally NULL) user-supplied memory for heapless environments
    const WMA_I32 iMemBufSize            // [in] user-supplied buffer size, 0 if pMemBuf is NULL
);


// **************************************************************************
// WMAProRawDecInit()
// This function initializes WMAProRawDec decoder
//
// Return values
// WMA_OK              indicates success
// WMA_E_INVALIDARG    indicates failure, invalid parameter(s)
// WMA_E_NOTSUPPORTED  indicates failure, unsupported request
// WMA_E_OUTOFMEMORY   indicates failure, allocate memory failure
// **************************************************************************
WMARESULT WMAProRawDecInit (
    WMAProRawDecHandle phWMAProRawDec,   // [in] WMAProRawDec handle
    WMAFormat* pWMAFormat,               // [in] WMAFormat for input WMA files
    PCMFormat* pPCMFormat,               // [in] PCMFormat for output PCM data
    WMAPlayerInfo *pPI,                  // [in] PlayerInfo
    WMAProRawDecState *paudecState,      // [out] decoder status 
    WMAProRawDecInitParams* pParams      // [in] InitParams, set NULL for normal (callbackless) mode
);

  
// **************************************************************************
// WMAProRawDecInput()
// This function feeds input data to the decoder. It is only used for normal (callbackless) mode.
//
// Return values
// WMA_OK              indicates success
// WMA_E_INVALIDARG    indicates failure, invalid parameter(s) (input buffer over 1 packet, etc)
// WMA_E_BROKEN_FRAME  indicates failure, corrupted input bit stream
// **************************************************************************
WMARESULT WMAProRawDecInput (
    WMAProRawDecHandle phWMAProRawDec,   // [in] WMAProRawDec handle
    WMA_U8* pbIn,                        // [in] input data buffer
    WMA_U32 cbIn,                        // [in] input data buffer size, minimal 8 bytes, maximal 1 packet   
    WMA_Bool fNewPacket,                 // [in] indicates input is a new data packet
    WMA_Bool fNoMoreInput,               // [in] indicates no additional input is expected
    WMA_Bool fTime,                      // [in] indicates timestamp is present
    WMA_I64 rtTime,                      // [in] timestamp value in 100-nanosecond units if fTime is set
    WMAProRawDecState* paudecState,      // [out] decode status
    WMAProRawDecInputParams* pParams     // [in] input parameter, NULL for normal packetized model (none SPDIF)
);


// **************************************************************************
// WMAProRawDecDecode()
// This function decode input data
//
// Return values
// WMA_OK              indicates success
// WMA_S_NO_MORE_FRAME indicates success and no additional input is expected
// WMA_E_INVALIDARG    indicates failure, invalid parameter(s) (input buffer over 1 packet, etc)
// WMA_E_WRONGSTATE    indicates failure, WMAProRawDecDecode() called at an inappropriate time
// **************************************************************************
WMARESULT WMAProRawDecDecode (
    WMAProRawDecHandle phWMAProRawDec,   // [in] WMAProRawDec handle
    WMA_U32* pcSamplesReady,             // [out] how many samples are availble for WMAProRawDecGetPCM()
    WMAProRawDecState* paudecState,      // [out] decode status
    WMAProRawDecDecodeParams* pParams    // [out] DecodeParams, NULL for normal packetized model (none SPDIF)
);


// **************************************************************************
// WMAProRawDecGetPCM()
// This function returns the PCM samples decoded by WMAProRawDecDecode()
//
// Return values
// WMA_OK              indicates success
// WMA_E_FAIL          indicates failure
// WMA_E_INVALIDARG    indicates failure, invalid parameter(s)
// WMA_E_WRONGSTATE    indicates failure, WMAProRawDecGetPCM() called at an inappropriate time
//
// Remarks
// The value of samples produced (*pcSamplesReturned) is up to cSamplesRequested if enough output buffer is provided.
// As Codec uses the provided output buffer for mixdown operations (6 channels fold down to 2, etc), 
// the correct way to calculate the adequate output buffer size is as below, 
//
// cbDstLength = cSamplesRequested * max(nInputChannels, nOutptChannels) 
//                                 * max(nInputBitdepth, nOutputBitdepth) / 8  (in bytes)
//
// If less buffer is provided, less samples produced by Codec.
// WMAProRawDecGetPCM() will need to be called again for remain samples.
// **************************************************************************
WMARESULT WMAProRawDecGetPCM (
    WMAProRawDecHandle phWMAProRawDec,   // [in] WMAProRawDec handle 
    WMA_U32 cSamplesRequested,           // [in] how many samples request for output, up to *pcSamplesReady (from WMAProRawDecDecode())
    WMA_U32 *pcSamplesReturned,          // [out] the actual samples produced
    WMA_U8* pbDst,                       // [out] output data buffer
    WMA_U32 cbDstLength,                 // [in] output buffer size
    WMA_U32* pcbDstUsed,                 // [out] produced data in bytes
    WMA_I64* prtTime,                    // [out] time stamp (in 100ns) of 1st sample returned
    WMAProRawDecState *paudecState,      // [out] decode status
    WMAPlayerInfo *pWmaPI,               // [in] PlayerInfo, dynamic configuration of some Init params
    WMAProRawDecGetPCMParams* pParams    // [in] GetPCMParams, usually set to NULL
);


// **************************************************************************
// WMAProRawDecReset()
// This function reset decoder and decoder status.
// It should be called whenever a file seek happens.
//
// Return values
// WMA_OK              indicates success
// **************************************************************************
WMARESULT WMAProRawDecReset (
	WMAProRawDecHandle phWMAProRawDec    // [in] WMAProRawDec handle
);


// **************************************************************************
// WMAProRawDecDelete()
// This function delete decoder handle and clean up memory
//
// Return values
// WMA_OK              indicates success
// **************************************************************************
WMARESULT WMAProRawDecDelete (
	WMAProRawDecHandle phWMAProRawDec    // [in] WMAProRawDec handle
);


///////////////////////////////////////////
// Helper functions
///////////////////////////////////////////

// **************************************************************************
// WMAProGetSamplePerFrame()
// This function get the maximal number of samples per frame, 
// For determining the maximal buffer size needed for WMAProRawDecGetPCM()
//
// Return values
// the maximal number of samples per frame
// **************************************************************************
WMA_I32 WMAProGetSamplePerFrame (
    WMA_I32   cSamplePerSec,             // [in] Sample per second 
    WMA_U32   dwBitPerSec,               // [in] bit per second 
    WMA_I32   iVersion,                  // [in] WMA version, WMAV1 = 1, WMAV2 = 2, WMAV3/WMALossless = 3
    WMA_U16   wEncOpt                    // [in] Encode option
);

// **************************************************************************
// WMAProDefaultChannelMask()
// this function retrieve default channel mask 
//
// Return values
// the default channel mask used by WMAFormat structure
// **************************************************************************
WMA_U32  WMAProDefaultChannelMask(
	WMA_U32 nChannels                    // [in] number of channels
);

// **************************************************************************
// WMAProWMAFormat2PCMFormat()
// this function converts WMAFormat to PCMFormat
//
// Return values
// none
// **************************************************************************
WMA_VOID WMAProWMAFormat2PCMFormat(
	WMAFormat* pSrc,                     // [in] WMAFormat
	PCMFormat* pDst                      // [out] PCMFormat
);



// **************************************************************************
// WMAProWaveFormat2WMAFormat()
// this function converts a WAVEFORMATEX into a WMAFormat
//
// Return values
// none
// **************************************************************************

#ifdef _WAVEFORMATEX_
void WMAProWaveFormat2WMAFormat(WAVEFORMATEX* wfx, WMAFormat* wmafmt);
#endif

// **************************************************************************
// WMAProRawDecSetLtrtPlayerOptionsFromRegistryCE()
// this function examins the registry and enables the LtRt in WMAPlayerInfo
// as well as the LtRt bufsize and filter quality
//
// Return values
// none
// **************************************************************************
#ifdef UNDER_CE
WMA_VOID WMAProRawDecSetLtrtPlayerOptionsFromRegistryCE(WMAPlayerInfo *pPI);
#endif

#ifdef __cplusplus
}
#endif  // __cplusplus


#endif // _WMAPRODECRAW_API_H_
