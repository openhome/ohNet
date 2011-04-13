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

class CSocketUdpClient;
class CSocketUdpClientMulticast;
class CSocketUdpListenerMulticast;

class CWinsock
{
	friend class CSocketUdpClient;
	friend class CSocketMultipus;
	friend class CSocketUdpListenerMulticast;
public:
	static void Initialise(PSOCKADDR aSocket);
	static void Initialise(PSOCKADDR aSocket, UCHAR aAddr1, UCHAR aAddr2, UCHAR aAddr3, UCHAR aAddr4, USHORT aPort);
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

class CSocketUdpClient
{
private:
    KSPIN_LOCK iSpinLock;
	bool iInitialised;
};


// Multipus Header
// 
// ByteStart Bytes                   Desc
// 0         4                       Ascii representation of "Mpus"
// 4         1                       MultipusHeader Major Version
// 5         3                       Uid
// 8         4                       Frame #
// 12        4                       Timestamp
// 16        1                       Sub Msg Type (0 = MultipusMsgAudio)
// 17        1                       Sub Msg Header Bytes (doubles as Minor Version for Sub Msg)
// 18        2                       Total Bytes (including all header bytes)

// 
// Audio Header
// 
// ByteStart Bytes                   Desc
// 0         4                       Sample Start Offset
// 4         4                       Sample Rate
// 8         1                       Bit depth of audio (16, 24)
// 9         1                       Channels
// 10        1                       Flags (lsb is halt flag)
// 11        1                       Reserved
// 12        TotalBytes - 16 - 12    Sample data in big endian, channels interleaved, packed

typedef struct
{
	UCHAR iMpus[4];
	UCHAR iMajorVersion;
	UCHAR iUid[3];
	ULONG iFrameNo;
	ULONG iTimestamp;
	UCHAR iSubMsgType;
	UCHAR iSubMsgHeaderBytes;
	USHORT iTotalBytes;
	ULONG iSampleStartOffset;
	ULONG iSampleRate;
	UCHAR iBitDepth;
	UCHAR iChannels;
	UCHAR iFlags;
	UCHAR iReserved;
} MPUSHEADER, *PMPUSHEADER;

class CSocketMultipus
{
public:
	CSocketMultipus();
	NTSTATUS Initialise(CWinsock& aWsk, NETWORK_CALLBACK* aCallback, void*  aContext);
	//NTSTATUS Send(PSOCKADDR aAddress, PVOID aBuffer, ULONG aBytes);
	//NTSTATUS Send(PSOCKADDR aAddress, PVOID aBuffer, ULONG aBytes);
	void Stop(PSOCKADDR aAddress, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels);
	void Send(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels);

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
	MPUSHEADER iHeader;
	ULONG iFrameNo;
};
	
class CSocketUdpListenerMulticast
{
private:
    KSPIN_LOCK iSpinLock;
	bool iInitialised;
};


#endif          // (NTDDI_VERSION >= NTDDI_VISTA)

#endif          // _NETWORK_H_


