/********************************************************************************
**    Copyright (c) 1998-2000 Microsoft Corporation. All Rights Reserved.
**
**       Portions Copyright (c) 1998-1999 Intel Corporation
**
********************************************************************************/

// Every debug output has "Modulname text"
static char STR_MODULENAME[] = "OHSOUNDCARD Network: ";

#include "network.h"
//#include "wdm.h"

#if (NTDDI_VERSION >= NTDDI_VISTA)

// CWinsock

void CWinsock::Initialise(PSOCKADDR aSocket, ULONG aAddress, ULONG aPort)
{
	SOCKADDR_IN* addr = (SOCKADDR_IN*) aSocket;

	addr->sin_family = AF_INET;
	addr->sin_port = ((aPort >> 8) & 0x00ff) + ((aPort << 8) & 0xff00);
	addr->sin_addr.S_un.S_un_b.s_b1 = (aAddress >> 24) & 0xff;
	addr->sin_addr.S_un.S_un_b.s_b2 = (aAddress >> 16) & 0xff;
	addr->sin_addr.S_un.S_un_b.s_b3 = (aAddress >> 8) & 0xff;
	addr->sin_addr.S_un.S_un_b.s_b4 = (aAddress & 0xff);
	addr->sin_zero[0] = 0;
	addr->sin_zero[1] = 0;
	addr->sin_zero[2] = 0;
	addr->sin_zero[3] = 0;
	addr->sin_zero[4] = 0;
	addr->sin_zero[5] = 0;
	addr->sin_zero[6] = 0;
	addr->sin_zero[7] = 0;
}

void CWinsock::Initialise(PSOCKADDR aSocket)
{
	Initialise(aSocket, 0, 0);
}

CWinsock* CWinsock::Create(NETWORK_CALLBACK aCallback, void* aContext)
{
	CWinsock* winsock = (CWinsock*) ExAllocatePoolWithTag(NonPagedPool, sizeof(CWinsock), 0);

	if (winsock != NULL)
	{
		winsock->iInitialised = false;

		KeInitializeSpinLock(&winsock->iSpinLock);

		winsock->iAppDispatch.Version = MAKE_WSK_VERSION(1,0);
		winsock->iAppDispatch.Reserved = 0;
		winsock->iAppDispatch.WskClientEvent = NULL;

		winsock->iCallback = aCallback;
		winsock->iContext = aContext;

		// Register as a WSK application

		WSK_CLIENT_NPI clientNpi;

		clientNpi.ClientContext = winsock;
		clientNpi.Dispatch = &winsock->iAppDispatch;

		NTSTATUS status = WskRegister(&clientNpi, &winsock->iRegistration);

		if(status == STATUS_SUCCESS)
		{
			HANDLE handle;
			OBJECT_ATTRIBUTES oa;
			InitializeObjectAttributes(&oa, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
			status = PsCreateSystemThread(&handle, THREAD_ALL_ACCESS, &oa, NULL, NULL, Init, winsock);

			if (status == STATUS_SUCCESS)
			{
				return (winsock);
			}

			WskDeregister(&winsock->iRegistration);
		}

		ExFreePool(winsock);
	}

	return (NULL);
}

void CWinsock::Close()
{
	WskDeregister(&iRegistration);

	ExFreePool(this);
}

void CWinsock::Init(void* aContext)
{
	CWinsock* winsock = (CWinsock*)aContext;

	NTSTATUS status;

	// Capture the WSK Provider NPI. If WSK subsystem is not ready yet, wait until it becomes ready.

	status = WskCaptureProviderNPI(&(winsock->iRegistration), WSK_INFINITE_WAIT, &(winsock->iProviderNpi));

	if (status != STATUS_SUCCESS)
	{
		return;
	}

	// Indicate that we are initialised

	KIRQL oldIrql;

	KeAcquireSpinLock (&(winsock->iSpinLock), &oldIrql);

	winsock->iInitialised = true;

	KeReleaseSpinLock (&(winsock->iSpinLock), oldIrql);

	(*winsock->iCallback)(winsock->iContext);
}

bool CWinsock::Initialised()
{
	KIRQL oldIrql;

	KeAcquireSpinLock (&iSpinLock, &oldIrql);

	bool initialised = iInitialised;

	KeReleaseSpinLock (&iSpinLock, oldIrql);

	return initialised;
}

// CSocketOhm

CSocketOhm::CSocketOhm()
{
	iInitialised = false;

	KeInitializeSpinLock(&iSpinLock);

	iHeader.iMagic[0] = 'O';
	iHeader.iMagic[1] = 'h';
	iHeader.iMagic[2] = 'm';
	iHeader.iMagic[3] = ' ';

	iHeader.iMajorVersion = 1;
	iHeader.iMsgType = 3;
	iHeader.iAudioHeaderBytes = 50;
	iHeader.iAudioNetworkTimestamp = 0;
	iHeader.iAudioMediaLatency = 0;
	iHeader.iAudioMediaTimestamp = 0;
	iHeader.iAudioSampleStartHi = 0;
	iHeader.iAudioSampleStartLo = 0;
	iHeader.iAudioSamplesTotalHi = 0;
	iHeader.iAudioSamplesTotalLo = 0;
	iHeader.iAudioVolumeOffset = 0;
	iHeader.iReserved = 0;
	iHeader.iCodecNameBytes = 6;  // 3
	iHeader.iCodecName[0] = 'P';
	iHeader.iCodecName[1] = 'C';
	iHeader.iCodecName[2] = 'M';
	iHeader.iCodecName[3] = '/';
	iHeader.iCodecName[4] = 'S';
	iHeader.iCodecName[5] = 'C';

	iFrame = 0;
	iSampleStart = 0;
	iSamplesTotal = 0;
	iSampleRate = 0;
}

NTSTATUS CSocketOhm::Initialise(CWinsock& aWsk, NETWORK_CALLBACK aCallback, void* aContext)
{
	iWsk = &aWsk;
	iCallback = aCallback;
	iContext = aContext;

	// Create the socket

	NTSTATUS status;

	PIRP irp;

	// Allocate an IRP
	irp = IoAllocateIrp(1, FALSE);

	// Check result

	if (irp == NULL) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

	// Set the completion routine for the IRP
	IoSetCompletionRoutine(irp,	CreateComplete, this, TRUE, TRUE, TRUE);

	// Initiate the creation of the socket

	status = iWsk->iProviderNpi.Dispatch->WskSocket(
		  iWsk->iProviderNpi.Client,
		  AF_INET,
		  SOCK_DGRAM,
		  IPPROTO_UDP,
		  WSK_FLAG_DATAGRAM_SOCKET,
		  NULL,
		  NULL,
		  NULL,
		  NULL,
		  NULL,
		  irp
		  );


	return (status);
}

NTSTATUS CSocketOhm::CreateComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
	UNREFERENCED_PARAMETER(aDeviceObject);

	if (aIrp->IoStatus.Status == STATUS_SUCCESS)
	{
		CSocketOhm* socket = (CSocketOhm*)aContext;

		// Save the socket object for the new socket
		socket->iSocket = (PWSK_SOCKET)(aIrp->IoStatus.Information);

		// Reuse the Irp
		IoReuseIrp(aIrp, STATUS_SUCCESS);

		// Set the completion routine for the IRP
		IoSetCompletionRoutine(aIrp, BindComplete, socket, TRUE, TRUE, TRUE);

		// Bind the socket

		SOCKADDR addr;

		CWinsock::Initialise(&addr);

		((PWSK_PROVIDER_DATAGRAM_DISPATCH)(socket->iSocket->Dispatch))->WskBind(socket->iSocket, &addr, 0, aIrp);
	}
	else
	{
		IoFreeIrp(aIrp);
	}

	// Always return STATUS_MORE_PROCESSING_REQUIRED to
	// terminate the completion processing of the IRP.
	return STATUS_MORE_PROCESSING_REQUIRED;
}


NTSTATUS CSocketOhm::BindComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
	UNREFERENCED_PARAMETER(aDeviceObject);

	if (aIrp->IoStatus.Status == STATUS_SUCCESS)
	{
		CSocketOhm* socket = (CSocketOhm*)aContext;

		// Reuse the Irp
		IoReuseIrp(aIrp, STATUS_SUCCESS);

		// Set the completion routine for the IRP
		IoSetCompletionRoutine(aIrp, InitialiseComplete, socket, TRUE, TRUE, TRUE);

		// Set the TTL

		ULONG ttl = 4;

		((PWSK_PROVIDER_BASIC_DISPATCH)(socket->iSocket->Dispatch))->WskControlSocket(socket->iSocket, WskSetOption, IP_MULTICAST_TTL, IPPROTO_IP, sizeof(ttl), &ttl, 0, NULL, NULL, aIrp);
	}
	else
	{
		IoFreeIrp(aIrp);
	}

	// Always return STATUS_MORE_PROCESSING_REQUIRED to
	// terminate the completion processing of the IRP.
	return STATUS_MORE_PROCESSING_REQUIRED;
}

NTSTATUS CSocketOhm::InitialiseComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
	UNREFERENCED_PARAMETER(aDeviceObject);

	CSocketOhm* socket = (CSocketOhm*)aContext;

	if (aIrp->IoStatus.Status == STATUS_SUCCESS)
	{
		KIRQL oldIrql;

		KeAcquireSpinLock (&(socket->iSpinLock), &oldIrql);

		socket->iInitialised = true;

		KeReleaseSpinLock (&(socket->iSpinLock), oldIrql);
	}

	(*(socket->iCallback))(socket->iContext);

	// Free the IRP

	IoFreeIrp(aIrp);

	// Always return STATUS_MORE_PROCESSING_REQUIRED to
	// terminate the completion processing of the IRP.
	return STATUS_MORE_PROCESSING_REQUIRED;
}

typedef struct
{
	WSK_BUF iBuf;
	SOCKADDR iAddr;
} UDPSEND, *PUDPSEND;

void CSocketOhm::SetTtl(ULONG aValue)
{
    UNREFERENCED_PARAMETER(aValue);
}

/*
void CSocketOhm::Send(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, UCHAR aHalt, ULONG aSampleRate, ULONG aBitRate, ULONG aBitDepth, ULONG aChannels)
{
	UNREFERENCED_PARAMETER(aAddress);
	UNREFERENCED_PARAMETER(aBuffer);
	UNREFERENCED_PARAMETER(aBytes);
	UNREFERENCED_PARAMETER(aHalt);
	UNREFERENCED_PARAMETER(aSampleRate);
	UNREFERENCED_PARAMETER(aBitRate);
	UNREFERENCED_PARAMETER(aBitDepth);
	UNREFERENCED_PARAMETER(aChannels);
}
*/


void CSocketOhm::Send(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, UCHAR aHalt, ULONG aSampleRate, ULONG aBitRate, ULONG aBitDepth, ULONG aChannels)
{
	PIRP irp;

	// Allocate an IRP

	irp = IoAllocateIrp(1, FALSE);

	// Check result

	if (irp == NULL)
	{
        return;
    }

	void* alloc = ExAllocatePoolWithTag(NonPagedPool, sizeof(UDPSEND) + sizeof(OHMHEADER) + aBytes, 0);

	if (alloc == NULL)
	{
        return;
	}

	PUDPSEND udp = (PUDPSEND) alloc;
	POHMHEADER header = (POHMHEADER) (udp + 1);
	UCHAR* audio = (UCHAR*) (header + 1);

	udp->iBuf.Offset = 0;
	udp->iBuf.Length = aBytes + sizeof(OHMHEADER);
	udp->iBuf.Mdl = IoAllocateMdl(header, sizeof(OHMHEADER) + aBytes, FALSE, FALSE, NULL);

	if (udp->iBuf.Mdl == NULL)
	{
		ExFreePool(alloc);
        return;
	}

	MmBuildMdlForNonPagedPool(udp->iBuf.Mdl);

	RtlCopyMemory(&udp->iAddr, aAddress, sizeof(SOCKADDR));

	KIRQL oldIrql;

	KeAcquireSpinLock (&iSpinLock, &oldIrql);

	ULONG frame = ++iFrame;

	RtlCopyMemory(header, &iHeader, sizeof(OHMHEADER));

	KeReleaseSpinLock (&iSpinLock, oldIrql);

	// Fill in multipus header

	UCHAR flags = 6; // lossless + timestamped 

	if (aHalt != 0)
	{
		flags |= 1; // halt flag
	}

	header->iAudioFlags = flags;

	USHORT samples = (USHORT)(aBytes / ((ULONG)aChannels * (ULONG)aBitDepth / 8));

	header->iAudioSamples = samples >> 8 & 0x00ff;
	header->iAudioSamples += samples << 8 & 0xff00;

	header->iAudioFrame = frame >> 24 & 0x000000ff;
	header->iAudioFrame += frame >> 8 & 0x0000ff00;
	header->iAudioFrame += frame << 8 & 0x00ff0000;
	header->iAudioFrame += frame << 24 & 0xff000000;

	header->iAudioSampleRate = aSampleRate >> 24 & 0x000000ff;
	header->iAudioSampleRate += aSampleRate >> 8 & 0x0000ff00;
	header->iAudioSampleRate += aSampleRate << 8 & 0x00ff0000;
	header->iAudioSampleRate += aSampleRate << 24 & 0xff000000;

	header->iAudioBitRate = aBitRate >> 24 & 0x000000ff;
	header->iAudioBitRate += aBitRate >> 8 & 0x0000ff00;
	header->iAudioBitRate += aBitRate << 8 & 0x00ff0000;
	header->iAudioBitRate += aBitRate << 24 & 0xff000000;

	header->iAudioBitDepth = (UCHAR) aBitDepth;
	header->iAudioChannels = (UCHAR) aChannels;

	USHORT bytes = (USHORT)(sizeof(OHMHEADER) + aBytes);

	header->iTotalBytes = bytes >> 8 & 0x00ff;
	header->iTotalBytes += bytes << 8 & 0xff00;

	// Create Timestamps

	if (iSampleRate != aSampleRate)
	{
		iSampleRate = aSampleRate;

		iTimestampMultiplier = 48000 * 256;

		if ((iSampleRate % 441) == 0)
		{
			iTimestampMultiplier = 44100 * 256;
		}
	}

	LARGE_INTEGER frequency;
    LARGE_INTEGER timestamp = KeQueryPerformanceCounter(&frequency);

	timestamp.QuadPart *= iTimestampMultiplier;
	timestamp.QuadPart /= frequency.QuadPart;

	header->iAudioNetworkTimestamp = timestamp.LowPart >> 24 & 0x000000ff;
	header->iAudioNetworkTimestamp += timestamp.LowPart >> 8 & 0x0000ff00;
	header->iAudioNetworkTimestamp += timestamp.LowPart << 8 & 0x00ff0000;
	header->iAudioNetworkTimestamp += timestamp.LowPart << 24 & 0xff000000;

	header->iAudioMediaTimestamp = header->iAudioNetworkTimestamp;

	// Copy the audio

	CopyAudio(audio, aBuffer, aBytes, aBitDepth);

	// Set the completion routine for the IRP

	IoSetCompletionRoutine(irp,	SendComplete, alloc, TRUE, TRUE, TRUE);

	((PWSK_PROVIDER_DATAGRAM_DISPATCH)(iSocket->Dispatch))->WskSendTo(iSocket, &udp->iBuf, 0, &udp->iAddr, 0, NULL, irp);
}

void CSocketOhm::CopyAudio(UCHAR* aDestination, UCHAR* aSource, ULONG aBytes, ULONG aBitDepth)
{
	UCHAR* dst = aDestination;
	UCHAR* src = aSource;
	ULONG sb = aBitDepth / 8;

	ULONG bytes = aBytes;

	while (bytes > 0)
	{
		UCHAR* s = src + sb;

		while (s > src)
		{
			*dst++ = *--s;
		}

		src += sb;
		bytes -= sb;
	}
}

NTSTATUS CSocketOhm::SendComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
    UNREFERENCED_PARAMETER(aDeviceObject);

	PUDPSEND udpsend = (PUDPSEND)aContext;

	IoFreeIrp(aIrp);
	IoFreeMdl(udpsend->iBuf.Mdl);
	ExFreePool(aContext);

	// Always return STATUS_MORE_PROCESSING_REQUIRED to
	// terminate the completion processing of the IRP.

	return STATUS_MORE_PROCESSING_REQUIRED;
}

bool CSocketOhm::Initialised()
{
	KIRQL oldIrql;

	KeAcquireSpinLock (&iSpinLock, &oldIrql);

	bool initialised = iInitialised;

	KeReleaseSpinLock (&iSpinLock, oldIrql);

	return initialised;
}

#endif

