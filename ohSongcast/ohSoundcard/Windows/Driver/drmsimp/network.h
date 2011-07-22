/********************************************************************************
**    Copyright (c) 1998-2000 Microsoft Corporation. All Rights Reserved.
**
**       Portions Copyright (c) 1998-1999 Intel Corporation
**
********************************************************************************/

#ifndef _NETWORK_H_
#define _NETWORK_H_

#pragma warning(push)
#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4214) // bit field types other than int

#include <ntddk.h>
#include <wsk.h>

#pragma warning(pop)

#if (NTDDI_VERSION >= NTDDI_VISTA)

/*****************************************************************************
 * Constants
 *****************************************************************************
 */

/*****************************************************************************
 * Classes
 *****************************************************************************
 */

typedef void NETWORK_CALLBACK(void* aContect);

class CSocketOhm;

class CWinsock
{
	friend class CSocketOhm;

public:
	static void Initialise(PSOCKADDR aSocket);
	static void Initialise(PSOCKADDR aSocket, ULONG aAddress, ULONG aPort);
	static CWinsock* Create(NETWORK_CALLBACK* aCallback, void*  aContext);
	bool Initialised();
	void Close();

private:
	static KSTART_ROUTINE Init;

private:
    KSPIN_LOCK iSpinLock;
	bool iInitialised;

	WSK_CLIENT_DISPATCH iAppDispatch;
	WSK_REGISTRATION iRegistration;
	WSK_PROVIDER_NPI iProviderNpi;
	NETWORK_CALLBACK* iCallback;
	void* iContext;
};


// Ohm Header

//Offset    Bytes                   Desc
//0         4                       Ascii representation of "Ohm "
//4         1                       Major Version
//5         1                       Msg Type
//6         2                       Total Bytes (Absolutely all bytes in the entire frame)

// Audio Header

//Offset    Bytes                   Desc
//0         1                       Msg Header Bytes (without the codec name)
//1         1                       Flags (lsb first: halt flag, lossless flag, timestamped flag all other bits 0)
//2         2                       Samples in this msg
//4         4                       Frame
//8         4                       Network Timestamp
//12        4                       Media Latency (delay through audio buffers)
//16        4                       Media Timestamp
//20        8                       Sample Start (first sample's offset from the beginiing of this track)
//28        8                       Samples Total (total samples for this track)
//36        4                       Sample Rate
//40        4                       Bit Rate
//44        2                       Volume Offset
//46        1                       Bit depth of audio (16, 24)
//47        1                       Channels
//48        1                       Reserved (must be zero)
//49        1                       Codec Name Bytes
//50        n                       Codec Name
//50 + n    Msg Total Bytes - Msg Header Bytes - Code Name Bytes (Sample data in big endian, channels interleaved, packed)

typedef struct
{
	UCHAR iMagic[4]; // "Ohm "
	UCHAR iMajorVersion; // 1
	UCHAR iMsgType; // 3 - Audio
	USHORT iTotalBytes;
	UCHAR iAudioHeaderBytes;
	UCHAR iAudioFlags;
	USHORT iAudioSamples;
	ULONG iAudioFrame;
	ULONG iAudioNetworkTimestamp;
	ULONG iAudioMediaLatency;
	ULONG iAudioMediaTimestamp;
	ULONG iAudioSampleStartHi;
	ULONG iAudioSampleStartLo;
	ULONG iAudioSamplesTotalHi;
	ULONG iAudioSamplesTotalLo;
	ULONG iAudioSampleRate;
	ULONG iAudioBitRate;
	USHORT iAudioVolumeOffset;
	UCHAR iAudioBitDepth;
	UCHAR iAudioChannels;
	UCHAR iReserved;
	UCHAR iCodecNameBytes;  // 6
	UCHAR iCodecName[6]; // "PCM   "
} OHMHEADER, *POHMHEADER;

class CSocketOhm
{
public:
	CSocketOhm();
	NTSTATUS Initialise(CWinsock& aWsk, NETWORK_CALLBACK* aCallback, void*  aContext);
	void SetTtl(ULONG aValue);
	void Send(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, UCHAR aHalt, ULONG aSampleRate, ULONG aBitRate, ULONG aBitDepth, ULONG aChannels);

	bool Initialised();


private:
	static IO_COMPLETION_ROUTINE CreateComplete;
	static IO_COMPLETION_ROUTINE BindComplete;
	static IO_COMPLETION_ROUTINE InitialiseComplete;
	static IO_COMPLETION_ROUTINE SendComplete;

	void SendPacket(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels);
	static void CopyAudio(UCHAR* aDestination, UCHAR* aSource, ULONG aBytes, ULONG aBitDepth);

private:
    KSPIN_LOCK iSpinLock;
	bool iInitialised;
	CWinsock* iWsk;
	NETWORK_CALLBACK* iCallback;
	void* iContext;
	PWSK_SOCKET iSocket;
	OHMHEADER iHeader;
	ULONG iFrame;
	ULONGLONG iSampleStart;
	ULONGLONG iSamplesTotal;
	ULONG iSampleRate;
	ULONG iTimestampMultiplier;
};

#endif          // (NTDDI_VERSION >= NTDDI_VISTA)

#endif          // _NETWORK_H_


