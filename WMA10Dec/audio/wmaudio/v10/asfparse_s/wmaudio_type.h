//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
/*
 * Windows Media Audio (WMA) Decoder API (implementation)
 *
 * Copyright (c) Microsoft Corporation 1999.  All Rights Reserved.
 */

#ifndef _WMAUDIO_IMPL_H_
#define _WMAUDIO_IMPL_H_

#include "wmaerr.h"
#include "asfwmatypes.h"
#ifndef WMAAPI_NO_DRM
#include "drmpd_ext.h"
#endif /* WMAAPI_NO_DRM */
#include "wmadec.h"
#ifdef USE_WOW_FILTER
#include "wow_interface.h"
#endif
#define MIN_OBJECT_SIZE     24
#define DATA_OBJECT_SIZE    50

#ifdef WMDRM_PORTABLE
#include "drmcommon.h"
#include "drmutilities.h"
#include "drmhds.h"
#include "drmsecurestore.h"
#include "drmlicense.h"
#include "drmcontextsizes.h"
#include "drmmanager.h"
#endif

#ifdef _XBOX
typedef unsigned __int64 U64;
#endif

/* parser state  */
typedef enum
{
    csWMA_NotValid = 0,

    csWMA_HeaderStart,
    csWMA_HeaderError,

    csWMA_NewAsfPacket,

    /* packet parsing states */

    csWMA_DecodePayloadStart,
    csWMA_DecodePayload,
    csWMA_DecodeAudioData,
    csWMA_DecodePayloadEnd,
    csWMA_DecodeCompressedPayload,

    csWMA_End_

} tWMAParseState;


typedef struct tagWMA_MetaDataDescRecords 
{
    WORD     wLangIdIndex;   // Specifies the index of the language ID in the Language List Object
    WORD     wStreamNumber;  // Specifies whether the entry applies to a specific media stream or 
                                // whether it applies to the whole file. A value of 0 in this field 
                                // indicates that it applies to the whole file; otherwise, the entry 
                                // applies only to the indicated stream number.
    WORD     wNameLenth;     // Specifies the number of valid bytes stored in the Name field.
    WORD     wDataType;      // Specifies the type of information being stored. The following values are recognized:
                                // Value Type   Description
                                //  0x0000      Unicode string. The data consists of a sequence of Unicode characters.
                                //  0x0001      BYTE array. The type of the data is implementation-specific.
                                //  0x0002      BOOL. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer. Only 0x0000 or 0x0001 are permitted values.
                                //  0x0003      DWORD. The data is 4 bytes long and should be interpreted as a 32-bit unsigned integer.
                                //  0x0004      QWORD. The data is 8 bytes long and should be interpreted as a 64-bit unsigned integer.
                                //  0x0005      WORD. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer.
                                //  0x0006      GUID. The data is 8 bytes long and should be interpreted as a 128-bit GUID.
                                //  0x8000      Extended Unicode string. The data consists of a sequence of Unicode characters.
                                //  0x8001      Extended BYTE array. The type of the data is implementation-specific.
                                //  0x8002      Extended BOOL. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer.  Only 0x0000 or 0x0001 are permitted values.
                                //  0x8003      Extended DWORD. The data is 4 bytes long and should be interpreted as a 32-bit unsigned integer.
                                //  0x8004      Extended QWORD. The data is 8 bytes long and should be interpreted as a 64-bit unsigned integer.
                                //  0x8005      Extended WORD. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer.
                                //  0x8006      Extended GUID. The data is 8 bytes long and should be interpreted as a 128-bit GUID.
    DWORD     dwDataLength;    // Specifies the length in bytes of the Data field.
    WORD      *pwName;        // Specifies the name that uniquely identifies the attribute being described. Names are case-sensitive.
    BYTE      *pData;         // Specifies the actual metadata being stored. The Data field should be interpreted according to the value 
                                // stored in the Data Type field. If the Data Type is one of the extended values, this field may not contain 
                                //any data if the file is being streamed over the wire.
} WMA_MetaDataDescRecords;


typedef struct tagWMA_MetaDataEntry 
{
    WORD     m_wDescRecordsCount;
    WMA_MetaDataDescRecords *pDescRec;
} WMA_MetaDataEntry;


#define FILEPROPFLAG_BROADCAST	1

#ifdef WMDRM_NETWORK
#define WMA_MAX_PAYLOAD_EXTENSION_STREAMS 4
#define WMA_MAX_PAYLOAD_EXTENSIONS 4


typedef struct tagWMA_PayloadExtensionSystem
{
    WORD   cbDataSize;
    BOOL   bIsSampleId;
} WMA_PayloadExtensionSystem;

typedef struct tagWMA_StreamPayloadExtensionData
{
    WORD   wStreamNum;
    WMA_PayloadExtensionSystem Systems[ WMA_MAX_PAYLOAD_EXTENSIONS ];
} WMA_StreamPayloadExtensionData;
#endif

/****************************************************************************/
#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef PACKED struct tGUID
{
    DWORD   Data1;
    WORD    Data2;
    WORD    Data3;
    BYTE    Data4[ 8 ];

}   GUID;
#endif
/****************************************************************************/

/* internal structure for the ASF header parsing */
typedef struct tagWMAFileHdrStateInternal
{
    U64     currPacketOffset;     /* not just for packets */
    U64     nextPacketOffset;

    /* ASF header */

    DWORD   cbHeader;
    DWORD   cbPacketSize;
    DWORD   cbAudioSize;
    DWORD   cPackets;
    DWORD   msDuration;
    DWORD   msPreroll;
    U64     cbFirstPacketOffset;
    U64     cbLastPacketOffset;
    DWORD   dwFilePropertiesFlags;

    /* audio prop */
    WORD    nVersion;
    WORD    wFormatTag;
    DWORD   nSamplesPerSec;
    DWORD   nAvgBytesPerSec;
    DWORD   nBlockAlign;
    WORD    nChannels;
    DWORD   nSamplesPerBlock;
    WORD    nEncodeOpt;
    WORD    nAdvancedEncodeOpt;
    DWORD   nAdvancedEncodeOpt2;
    
    // Added in V9
    WORD    wPCMFormatTag;
    WORD    wBitsPerSample; // container size
    WORD    wValidBitsPerSample; // actual valid data depth in the decoded stream
    DWORD   dwChannelMask;
    GUID    SubFormat;
    WORD    wOriginalBitDepth; // actual valid data depth in the original source (informational)
    
    /* DRM */
    
    BYTE    pbSecretData[32];
    DWORD   cbSecretData;
    BYTE    pbType[16];
    BYTE    pbKeyID[32];

#ifdef WMDRM_PORTABLE
    WORD cbCEncExData;
    BYTE *pbCEncExData;
#endif

    /* Content Description */
	tWMAFileContDesc		*m_pDesc;

    /* Extended Content Description */

    tWMAExtendedContentDesc *m_pECDesc;

    /* Marker */
    DWORD   m_dwMarkerNum;
    MarkerEntry *m_pMarker;

    /* License Store */
    DWORD   m_dwLicenseLen;
    BYTE   *m_pLicData;

#ifndef WMAAPI_NO_DRM_STREAM
    BYTE    bAudioStreamNum;
    BYTE    bDRMAuxStreamNum;
#endif
// Members added by Amit 
    WORD    wAudioStreamId;
    WMA_MetaDataEntry *ptMetaDataEntry;

    // Members added by Naveen for MBR support
    WORD    wTargetAudioStreamNumber;
    WORD    cAudioStreams;

#ifdef WMDRM_NETWORK
    WORD cPEData;
    WMA_StreamPayloadExtensionData PEData[ WMA_MAX_PAYLOAD_EXTENSION_STREAMS ];
#endif
} tWMAFileHdrStateInternal;

//typedef void * WMADecHANDLE;

/* internal structure for the WMAudio library state */
typedef struct tagWMAFileStateInternal
{
    tWMAFileHdrStateInternal hdr_parse;

    /* parse_state */
    
    tWMAParseState parse_state;

    /* payload parsing */

    U64   cbPayloadOffset;
    U64   cbPayloadLeft;

    BOOL  bBlockStart;
    DWORD cbBlockLeft;

    /* packet parsing */

    PACKET_PARSE_INFO_EX ppex;

    PAYLOAD_MAP_ENTRY_EX payload;
    DWORD iPayload;
    WORD wPayStart;

    /* other states */

    BOOL    bHasDRM;
#ifdef WMDRM_PORTABLE
    BOOL    bHasJanusDRM;
#endif
#ifdef WMDRM_NETWORK
    BOOL    bHasWMDRMNetworkDRM;
#endif

    DWORD   nSampleCount;

    /* objects */

//    tWMAState wma_state;
//    WMADHANDLE hWMA;

    void* hSPDTX;   // handle to spdif transmitter state machine
    char* szmdata;  // content descriptor metadata for spdif transmitter
    BYTE* pbIn;     // used only by spdif transmitter ( for input buffer )
    DWORD cbIn;     // used only by spdif transmitter ( for input buffer )
    DWORD nLeadingBursts;     // leading empty spdif bursts
    DWORD nTrailingBursts;    // trailing empty spdif bursts

    void* hWMA;     // handle to audio decoder
    audecState audecState; // audio decoder state

#ifndef WMAAPI_NO_DRM
    VOID* pDRM_state;
#endif /* WMAAPI_NO_DRM */

#ifdef WMDRM_PORTABLE
    VOID *pJanusContext;
    VOID *pJanusDecryptContext;
#endif

#ifdef WMDRM_NETWORK
    DRM_AES_KEY *pWMDRMNetworkKey;
    DRM_UINT64  qwWMDRMNetworkSampleID;
#endif

#ifndef WMAAPI_NO_DRM_STREAM
    BYTE cbNextPayloadEndValid;
    BYTE rgbNextPayloadEnd[15];
#endif

#ifdef _XBOX
    void *pvUserContext;
#endif
    
#ifdef USE_WOW_FILTER
    WowChannel sWowChannel;
#endif
    BYTE *pCallBackBuffer;
	void *pPlayerInfo;
} tWMAFileStateInternal;

/* ASF parsing functions */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/* use (only) for reading possibly large chunk */
WMAERR WMA_LoadObjectHeader(tWMAFileHdrStateInternal *pInt, GUID *pObjectId, QWORD *pqwSize);
WMAERR WMA_LoadHeaderObject(tWMAFileHdrStateInternal *pInt, int isFull);
WMAERR WMA_LoadPropertiesObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize, int isFull);
WMAERR WMA_LoadAudioObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize, int isFull);
WMAERR WMA_LoadEncryptionObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize);
WMAERR WMA_LoadContentDescriptionObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize);
WMAERR WMA_LoadExtendedContentDescObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize);

WMAERR WMA_ParseAsfHeader(tWMAFileHdrStateInternal *pInt, int isFull);
WMAERR WMA_ParsePacketHeader(tWMAFileStateInternal *pInt);
WMAERR WMA_ParsePayloadHeader(tWMAFileStateInternal *pInt);

WMAERR WMA_GetMarkerObject(tWMAFileHdrStateInternal *pInt, int k);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WMAUDIO_IMPL_H_ */


