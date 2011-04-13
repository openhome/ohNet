/********************************************************************************
**    Copyright (c) 1998-2000 Microsoft Corporation. All Rights Reserved.
**
**       Portions Copyright (c) 1998-1999 Intel Corporation
**
********************************************************************************/

// Every debug output has "Modulname text"
static char STR_MODULENAME[] = "Sneaky Soundcard Network: ";

#include "network.h"
//#include "wdm.h"

#if (NTDDI_VERSION >= NTDDI_VISTA)

// CWinsock

void CWinsock::Initialise(PSOCKADDR aSocket, UCHAR aAddr1, UCHAR aAddr2, UCHAR aAddr3, UCHAR aAddr4, USHORT aPort)
{
	SOCKADDR_IN* addr = (SOCKADDR_IN*) aSocket;

	addr->sin_family = AF_INET;
	addr->sin_port = ((aPort >> 8) & 0x00ff) + ((aPort << 8) & 0xff00);
	addr->sin_addr.S_un.S_un_b.s_b1 = aAddr1;
	addr->sin_addr.S_un.S_un_b.s_b2 = aAddr2;
	addr->sin_addr.S_un.S_un_b.s_b3 = aAddr3;
	addr->sin_addr.S_un.S_un_b.s_b4 = aAddr4;
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
	Initialise(aSocket, 0, 0, 0, 0, 0);
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

	if(status != STATUS_SUCCESS)
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

// CSocketMultipus

CSocketMultipus::CSocketMultipus()
{
	iInitialised = false;

	KeInitializeSpinLock(&iSpinLock);

	iHeader.iMpus[0] = 'M';
	iHeader.iMpus[1] = 'p';
	iHeader.iMpus[2] = 'u';
	iHeader.iMpus[3] = 's';

	iHeader.iMajorVersion = 1;

	iHeader.iUid[0] = 0;
	iHeader.iUid[1] = 0;
	iHeader.iUid[2] = 0;

	iHeader.iFrameNo = 0;
	iHeader.iTimestamp = 0;
	iHeader.iSubMsgType = 1;
	iHeader.iSubMsgHeaderBytes = 12;

	iHeader.iTotalBytes = 0;
	
	iHeader.iSampleStartOffset = 0;
	iHeader.iSampleRate = 0;
	iHeader.iBitDepth = 0;
	iHeader.iChannels = 0;
	iHeader.iFlags = 0;
	iHeader.iReserved = 0;

	iFrameNo = 0;
}

NTSTATUS CSocketMultipus::Initialise(CWinsock& aWsk, NETWORK_CALLBACK aCallback, void* aContext)
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

NTSTATUS CSocketMultipus::CreateComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
    UNREFERENCED_PARAMETER(aDeviceObject);

	if (aIrp->IoStatus.Status == STATUS_SUCCESS)
	{
		CSocketMultipus* socket = (CSocketMultipus*)aContext;

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


NTSTATUS CSocketMultipus::BindComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
    UNREFERENCED_PARAMETER(aDeviceObject);

	if (aIrp->IoStatus.Status == STATUS_SUCCESS)
	{
		CSocketMultipus* socket = (CSocketMultipus*)aContext;

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

NTSTATUS CSocketMultipus::InitialiseComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
{
    UNREFERENCED_PARAMETER(aDeviceObject);

	CSocketMultipus* socket = (CSocketMultipus*)aContext;

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

void CSocketMultipus::Stop(PSOCKADDR aAddress, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels)
{
    UNREFERENCED_PARAMETER(aAddress);
    UNREFERENCED_PARAMETER(aSampleRate);
    UNREFERENCED_PARAMETER(aBitDepth);
    UNREFERENCED_PARAMETER(aChannels);
}

/*
void CSocketMultipus::Stop(PSOCKADDR aAddress, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels)
{
	PIRP irp;

	// Allocate an IRP

	irp = IoAllocateIrp(1, FALSE);

	// Check result

	if (irp == NULL)
	{
        return;
    }

	void* alloc = ExAllocatePoolWithTag(NonPagedPool, sizeof(UDPSEND) + sizeof(MPUSHEADER), 0);

	if (alloc == NULL)
	{
        return;
	}

	PUDPSEND udp = (PUDPSEND) alloc;
	PMPUSHEADER header = (PMPUSHEADER) (udp + 1);

	udp->iBuf.Offset = 0;
	udp->iBuf.Length = sizeof(MPUSHEADER);
	udp->iBuf.Mdl = IoAllocateMdl(header, sizeof(MPUSHEADER), FALSE, FALSE, NULL);

	if (udp->iBuf.Mdl == NULL)
	{
		ExFreePool(alloc);
        return;
	}

	MmBuildMdlForNonPagedPool(udp->iBuf.Mdl);

	RtlCopyMemory(&udp->iAddr, aAddress, sizeof(SOCKADDR));

	KIRQL oldIrql;

	KeAcquireSpinLock (&iSpinLock, &oldIrql);

	ULONG frame = ++iFrameNo;

	RtlCopyMemory(header, &iHeader, sizeof(MPUSHEADER));

	KeReleaseSpinLock (&iSpinLock, oldIrql);

	// Fill in multipus header

	header->iFrameNo = frame >> 24 & 0x000000ff;
	header->iFrameNo += frame >> 8 & 0x0000ff00;
	header->iFrameNo += frame << 8 & 0x00ff0000;
	header->iFrameNo += frame << 24 & 0xff000000;

	header->iSampleRate = aSampleRate >> 24 & 0x000000ff;
	header->iSampleRate += aSampleRate >> 8 & 0x0000ff00;
	header->iSampleRate += aSampleRate << 8 & 0x00ff0000;
	header->iSampleRate += aSampleRate << 24 & 0xff000000;

	header->iBitDepth = (UCHAR) aBitDepth;
	header->iChannels = (UCHAR) aChannels;

	header->iFlags = 1;

	USHORT bytes = (USHORT)(sizeof(MPUSHEADER));

	header->iTotalBytes = bytes >> 8 & 0x00ff;
	header->iTotalBytes += bytes << 8 & 0xff00;

	// Set the completion routine for the IRP

	IoSetCompletionRoutine(irp,	SendComplete, alloc, TRUE, TRUE, TRUE);

	((PWSK_PROVIDER_DATAGRAM_DISPATCH)(iSocket->Dispatch))->WskSendTo(iSocket, &udp->iBuf, 0, &udp->iAddr, 0, NULL, irp);
}
*/
/*
void CSocketMultipus::Send(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels)
{
    UNREFERENCED_PARAMETER(aAddress);
    UNREFERENCED_PARAMETER(aBuffer);
    UNREFERENCED_PARAMETER(aBytes);
    UNREFERENCED_PARAMETER(aSampleRate);
    UNREFERENCED_PARAMETER(aBitDepth);
    UNREFERENCED_PARAMETER(aChannels);
}
*/

void CSocketMultipus::Send(PSOCKADDR aAddress, UCHAR* aBuffer, ULONG aBytes, ULONG aSampleRate, ULONG aBitDepth, ULONG aChannels)
{
	PIRP irp;

	// Allocate an IRP

	irp = IoAllocateIrp(1, FALSE);

	// Check result

	if (irp == NULL)
	{
        return;
    }

	void* alloc = ExAllocatePoolWithTag(NonPagedPool, sizeof(UDPSEND) + sizeof(MPUSHEADER) + aBytes, 0);

	if (alloc == NULL)
	{
        return;
	}

	PUDPSEND udp = (PUDPSEND) alloc;
	PMPUSHEADER header = (PMPUSHEADER) (udp + 1);
	UCHAR* audio = (UCHAR*) (header + 1);

	udp->iBuf.Offset = 0;
	udp->iBuf.Length = aBytes + sizeof(MPUSHEADER);
	udp->iBuf.Mdl = IoAllocateMdl(header, sizeof(MPUSHEADER) + aBytes, FALSE, FALSE, NULL);

	if (udp->iBuf.Mdl == NULL)
	{
		ExFreePool(alloc);
        return;
	}

	MmBuildMdlForNonPagedPool(udp->iBuf.Mdl);

	RtlCopyMemory(&udp->iAddr, aAddress, sizeof(SOCKADDR));

	KIRQL oldIrql;

	KeAcquireSpinLock (&iSpinLock, &oldIrql);

	ULONG frame = ++iFrameNo;

	RtlCopyMemory(header, &iHeader, sizeof(MPUSHEADER));

	KeReleaseSpinLock (&iSpinLock, oldIrql);

	// Fill in multipus header

	header->iFrameNo = frame >> 24 & 0x000000ff;
	header->iFrameNo += frame >> 8 & 0x0000ff00;
	header->iFrameNo += frame << 8 & 0x00ff0000;
	header->iFrameNo += frame << 24 & 0xff000000;

	header->iSampleRate = aSampleRate >> 24 & 0x000000ff;
	header->iSampleRate += aSampleRate >> 8 & 0x0000ff00;
	header->iSampleRate += aSampleRate << 8 & 0x00ff0000;
	header->iSampleRate += aSampleRate << 24 & 0xff000000;

	header->iBitDepth = (UCHAR) aBitDepth;
	header->iChannels = (UCHAR) aChannels;

	USHORT bytes = (USHORT)(sizeof(MPUSHEADER) + aBytes);

	header->iTotalBytes = bytes >> 8 & 0x00ff;
	header->iTotalBytes += bytes << 8 & 0xff00;

	// Copy the audio

	CopyAudio(audio, aBuffer, aBytes, aBitDepth);

	// Set the completion routine for the IRP

	IoSetCompletionRoutine(irp,	SendComplete, alloc, TRUE, TRUE, TRUE);

	((PWSK_PROVIDER_DATAGRAM_DISPATCH)(iSocket->Dispatch))->WskSendTo(iSocket, &udp->iBuf, 0, &udp->iAddr, 0, NULL, irp);
}


void CSocketMultipus::CopyAudio(UCHAR* aDestination, UCHAR* aSource, ULONG aBytes, ULONG aBitDepth)
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

NTSTATUS CSocketMultipus::SendComplete(PDEVICE_OBJECT aDeviceObject, PIRP aIrp, PVOID aContext)
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

bool CSocketMultipus::Initialised()
{
	KIRQL oldIrql;

	KeAcquireSpinLock (&iSpinLock, &oldIrql);

	bool initialised = iInitialised;

	KeReleaseSpinLock (&iSpinLock, oldIrql);

	return initialised;
}



#endif

