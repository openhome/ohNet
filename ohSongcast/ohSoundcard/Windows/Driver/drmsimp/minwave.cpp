/*++

Copyright (c) 1997-2000  Microsoft Corporation All Rights Reserved

Module Name:

    minwave.cpp

Abstract:

    Implementation of wavecyclic miniport.

--*/

#pragma warning (disable : 4127)

#include <msvad.h>
#include <common.h>
#include "drmsimp.h"
#include "minwave.h"
#include "wavtable.h"
#include "network.h"

FAST_MUTEX MpusFastMutex;

SOCKADDR MpusAddress;

ULONG MpusActive;
ULONG MpusTtl;
ULONG MpusAddr;
ULONG MpusPort;
ULONG MpusAudioSampleRate;
ULONG MpusAudioBitRate;
ULONG MpusAudioBitDepth;
ULONG MpusAudioChannels;
ULONG MpusSendFormat;

KEVENT WskInitialisedEvent;

CWinsock* Wsk;
CSocketOhm* Socket;

void SocketInitialised(void* aContext);
void WskInitialised(void* aContext);
void MpusStop();
void MpusSend(UCHAR* aBuffer, UINT aBytes);
void MpusSetFormat(ULONG aSampleRate, ULONG aBitRate, ULONG aBitDepth, ULONG aChannels);

#pragma code_seg("PAGE")

//=============================================================================
// CMiniportWaveCyclic
//=============================================================================

//=============================================================================
NTSTATUS
CreateMiniportWaveCyclicMSVAD
( 
    OUT PUNKNOWN *              Unknown,
    IN  REFCLSID,
    IN  PUNKNOWN                UnknownOuter OPTIONAL,
    IN  POOL_TYPE               PoolType 
)
/*++

Routine Description:

  Create the wavecyclic miniport.

Arguments:

  Unknown - 

  RefClsId -

  UnknownOuter -

  PoolType -

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    ASSERT(Unknown);

    STD_CREATE_BODY(CMiniportWaveCyclic, Unknown, UnknownOuter, PoolType);
}

//=============================================================================
CMiniportWaveCyclic::~CMiniportWaveCyclic
( 
    void 

)
/*++

Routine Description:

  Destructor for wavecyclic miniport

Arguments:

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    DPF_ENTER(("[CMiniportWaveCyclic::~CMiniportWaveCyclic]"));
} // ~CMiniportWaveCyclic


//=============================================================================
STDMETHODIMP_(NTSTATUS)
CMiniportWaveCyclic::DataRangeIntersection
( 
    IN  ULONG                       PinId,
    IN  PKSDATARANGE                ClientDataRange,
    IN  PKSDATARANGE                MyDataRange,
    IN  ULONG                       OutputBufferLength,
    OUT PVOID                       ResultantFormat,
    OUT PULONG                      ResultantFormatLength 
)
/*++

Routine Description:

  The DataRangeIntersection function determines the highest quality 
  intersection of two data ranges.

Arguments:

  PinId -           Pin for which data intersection is being determined. 

  ClientDataRange - Pointer to KSDATARANGE structure which contains the data 
                    range submitted by client in the data range intersection 
                    property request. 

  MyDataRange -         Pin's data range to be compared with client's data 
                        range. In this case we actually ignore our own data 
                        range, because we know that we only support one range.

  OutputBufferLength -  Size of the buffer pointed to by the resultant format 
                        parameter. 

  ResultantFormat -     Pointer to value where the resultant format should be 
                        returned. 

  ResultantFormatLength -   Actual length of the resultant format placed in 
                            ResultantFormat. This should be less than or equal 
                            to OutputBufferLength. 

  Return Value:

    NT status code.

--*/
{
    UNREFERENCED_PARAMETER(PinId);
    UNREFERENCED_PARAMETER(ClientDataRange);
    UNREFERENCED_PARAMETER(MyDataRange);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(ResultantFormat);
    UNREFERENCED_PARAMETER(ResultantFormatLength);

	PAGED_CODE();

    // This driver only supports PCM formats.
    // Portcls will handle the request for us.
    //

    return STATUS_NOT_IMPLEMENTED;
} // DataRangeIntersection

//=============================================================================
STDMETHODIMP_(NTSTATUS)
CMiniportWaveCyclic::GetDescription
( 
    OUT PPCFILTER_DESCRIPTOR * OutFilterDescriptor 
)
/*++

Routine Description:

  The GetDescription function gets a pointer to a filter description. 
  It provides a location to deposit a pointer in miniport's description 
  structure. This is the placeholder for the FromNode or ToNode fields in 
  connections which describe connections to the filter's pins. 

Arguments:

  OutFilterDescriptor - Pointer to the filter description. 

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    ASSERT(OutFilterDescriptor);

    return 
        CMiniportWaveCyclicMSVAD::GetDescription(OutFilterDescriptor);
} // GetDescription

//=============================================================================
STDMETHODIMP_(NTSTATUS)
CMiniportWaveCyclic::Init
( 
    IN  PUNKNOWN                UnknownAdapter_,
    IN  PRESOURCELIST           ResourceList_,
    IN  PPORTWAVECYCLIC         Port_ 
)
/*++

Routine Description:

  The Init function initializes the miniport. Callers of this function 
  should run at IRQL PASSIVE_LEVEL

Arguments:

  UnknownAdapter - A pointer to the IUnknown interface of the adapter object. 

  ResourceList - Pointer to the resource list to be supplied to the miniport 
                 during initialization. The port driver is free to examine the 
                 contents of the ResourceList. The port driver will not be 
                 modify the ResourceList contents. 

  Port - Pointer to the topology port object that is linked with this miniport. 

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    ASSERT(UnknownAdapter_);
    ASSERT(Port_);

    NTSTATUS                    ntStatus;

    DPF_ENTER(("[CMiniportWaveCyclic::Init]"));

    m_MaxOutputStreams      = MAX_OUTPUT_STREAMS;
    m_MaxInputStreams       = MAX_INPUT_STREAMS;
    m_MaxTotalStreams       = MAX_TOTAL_STREAMS;

    m_MinChannels           = MIN_CHANNELS;
    m_MaxChannelsPcm        = MAX_CHANNELS_PCM;

    m_MinBitsPerSamplePcm   = MIN_BITS_PER_SAMPLE_PCM;
    m_MaxBitsPerSamplePcm   = MAX_BITS_PER_SAMPLE_PCM;
    m_MinSampleRatePcm      = MIN_SAMPLE_RATE;
    m_MaxSampleRatePcm      = MAX_SAMPLE_RATE;
    
    ntStatus =
        CMiniportWaveCyclicMSVAD::Init
        (
            UnknownAdapter_,
            ResourceList_,
            Port_
        );
    if (NT_SUCCESS(ntStatus))
    {
        // Set filter descriptor.
        m_FilterDescriptor = &MiniportFilterDescriptor;

        m_fCaptureAllocated = FALSE;
        m_fRenderAllocated = FALSE;
    }

	ExInitializeFastMutex(&MpusFastMutex);

	ExAcquireFastMutex(&MpusFastMutex);

	MpusActive = 0;
	MpusTtl = 0;
	MpusAddr = 0;
	MpusPort = 0;
	MpusAudioSampleRate = 0;
	MpusAudioBitRate = 0;
	MpusAudioBitDepth = 0;
	MpusAudioChannels = 0;
	MpusSendFormat = 0;

	MpusActive = 1;
	MpusTtl = 4;
	MpusAddr = 0xeffd0001;
	MpusPort = 51972;

	CWinsock::Initialise(&MpusAddress, MpusAddr, MpusPort);

	CWinsock::Initialise(&MpusAddress, MpusAddr, MpusPort);

	ExReleaseFastMutex(&MpusFastMutex);

	KeInitializeEvent(&WskInitialisedEvent, NotificationEvent, false);

	Wsk = CWinsock::Create(WskInitialised, this);

	if (Wsk == NULL)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	LARGE_INTEGER timeout;

	timeout.QuadPart = -100000000; // 1 second

	ntStatus = KeWaitForSingleObject(&WskInitialisedEvent, Executive, KernelMode, false, &timeout);

	if(ntStatus != STATUS_SUCCESS)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}

    return ntStatus;
} // Init

//=============================================================================
STDMETHODIMP_(NTSTATUS)
CMiniportWaveCyclic::NewStream
( 
    OUT PMINIPORTWAVECYCLICSTREAM * OutStream,
    IN  PUNKNOWN                OuterUnknown,
    IN  POOL_TYPE               PoolType,
    IN  ULONG                   Pin,
    IN  BOOLEAN                 Capture,
    IN  PKSDATAFORMAT           DataFormat,
    OUT PDMACHANNEL *           OutDmaChannel,
    OUT PSERVICEGROUP *         OutServiceGroup 
)
/*++

Routine Description:

  The NewStream function creates a new instance of a logical stream 
  associated with a specified physical channel. Callers of NewStream should 
  run at IRQL PASSIVE_LEVEL.

Arguments:

  OutStream -

  OuterUnknown -

  PoolType - 

  Pin - 

  Capture - 

  DataFormat -

  OutDmaChannel -

  OutServiceGroup -

Return Value:

  NT status code.

--*/
{
    UNREFERENCED_PARAMETER(PoolType);

	PAGED_CODE();

    ASSERT(OutStream);
    ASSERT(DataFormat);
    ASSERT(OutDmaChannel);
    ASSERT(OutServiceGroup);

    DPF_ENTER(("[CMiniportWaveCyclic::NewStream]"));

    NTSTATUS                    ntStatus = STATUS_SUCCESS;
    PCMiniportWaveCyclicStream  stream = NULL;

    // Check if we have enough streams.
    if (Capture)
    {
        if (m_fCaptureAllocated)
        {
            DPF(D_TERSE, ("[Only one capture stream supported]"));
            ntStatus = STATUS_INSUFFICIENT_RESOURCES;
        }
    }
    else
    {
        if (m_fRenderAllocated)
        {
            DPF(D_TERSE, ("[Only one render stream supported]"));
            ntStatus = STATUS_INSUFFICIENT_RESOURCES;
        }
    }

    // Determine if the format is valid.
    //
    if (NT_SUCCESS(ntStatus))
    {
        ntStatus = ValidateFormat(DataFormat);
    }

    // Instantiate a stream. Stream must be in
    // NonPagedPool because of file saving.
    //
    if (NT_SUCCESS(ntStatus))
    {
        stream = new (NonPagedPool, SNEAKY_POOLTAG) 
            CMiniportWaveCyclicStream(OuterUnknown);

        if (stream)
        {
            stream->AddRef();

            ntStatus = 
                stream->Init
                ( 
                    this,
                    Pin,
                    Capture,
                    DataFormat
                );
        }
        else
        {
            ntStatus = STATUS_INSUFFICIENT_RESOURCES;
        }
    }

    if (NT_SUCCESS(ntStatus))
    {
        if (Capture)
        {
            m_fCaptureAllocated = TRUE;
        }
        else
        {
            m_fRenderAllocated = TRUE;
        }

        *OutStream = PMINIPORTWAVECYCLICSTREAM(stream);
        (*OutStream)->AddRef();
        
        *OutDmaChannel = PDMACHANNEL(stream);
        (*OutDmaChannel)->AddRef();

        *OutServiceGroup = m_ServiceGroup;
        (*OutServiceGroup)->AddRef();

        // The stream, the DMA channel, and the service group have
        // references now for the caller.  The caller expects these
        // references to be there.
    }

    // This is our private reference to the stream.  The caller has
    // its own, so we can release in any case.
    //
    if (stream)
    {
        stream->Release();
    }
    
    return ntStatus;
} // NewStream

//=============================================================================
STDMETHODIMP_(NTSTATUS)
CMiniportWaveCyclic::NonDelegatingQueryInterface
( 
    IN  REFIID  Interface,
    OUT PVOID * Object 
)
/*++

Routine Description:

  QueryInterface

Arguments:

  Interface - GUID

  Object - interface pointer to be returned.

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    ASSERT(Object);

    if (IsEqualGUIDAligned(Interface, IID_IUnknown))
    {
        *Object = PVOID(PUNKNOWN(PMINIPORTWAVECYCLIC(this)));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IMiniport))
    {
        *Object = PVOID(PMINIPORT(this));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IMiniportWaveCyclic))
    {
        *Object = PVOID(PMINIPORTWAVECYCLIC(this));
    }
    else
    {
        *Object = NULL;
    }

    if (*Object)
    {
        // We reference the interface for the caller.

        PUNKNOWN(*Object)->AddRef();
        return STATUS_SUCCESS;
    }

    return STATUS_INVALID_PARAMETER;
} // NonDelegatingQueryInterface


NTSTATUS PropertyHandler_Wave
(
    IN PPCPROPERTY_REQUEST PropertyRequest
)
{
	PAGED_CODE();

    ASSERT (PropertyRequest);

    // We only have a get defined.
    if (PropertyRequest->Verb & KSPROPERTY_TYPE_GET)
    {
        // Check the ID ("function" in "group").
        if (PropertyRequest->PropertyItem->Id != KSPROPERTY_SNEAKY_FEATURES)
		{
            return STATUS_INVALID_PARAMETER;
		}

        // validate buffer size.
        if (PropertyRequest->ValueSize < sizeof (SneakyFeatures))
		{
            return STATUS_INVALID_PARAMETER;
		}

        // The "Value" is the out buffer that you pass in DeviceIoControl call.
        SneakyFeatures *pSneakyFeatures = (SneakyFeatures *) PropertyRequest->Value;
        
        // Check the buffer.
        if (!pSneakyFeatures)
		{
            return STATUS_INVALID_PARAMETER;
		}

		ExAcquireFastMutex(&MpusFastMutex);

        pSneakyFeatures->iVersion = 1;

		ExReleaseFastMutex(&MpusFastMutex);

		return STATUS_SUCCESS ;
    }
    else if (PropertyRequest->Verb & KSPROPERTY_TYPE_SET)
    {
        if (PropertyRequest->PropertyItem->Id == KSPROPERTY_SNEAKY_ENDPOINT)
		{
			if (PropertyRequest->ValueSize != (sizeof (UINT) * 2))
			{
				return STATUS_INVALID_PARAMETER;
			}

            UINT* pValue = (UINT *)PropertyRequest->Value;

			ULONG addr = *pValue++;
			ULONG port = *pValue;

			ExAcquireFastMutex(&MpusFastMutex);

			if (MpusAddr != addr || MpusPort != port)
			{
				MpusAddr = addr;
				MpusPort = port;

				CWinsock::Initialise(&MpusAddress, MpusAddr, MpusPort);
			}

			ExReleaseFastMutex(&MpusFastMutex);

			return STATUS_SUCCESS;
		}
        else if (PropertyRequest->PropertyItem->Id == KSPROPERTY_SNEAKY_ACTIVE)
		{
			if (PropertyRequest->ValueSize != sizeof (UINT))
			{
				return STATUS_INVALID_PARAMETER;
			}

            UINT* pValue = (UINT *)PropertyRequest->Value;

			ULONG active = *pValue;

			ExAcquireFastMutex(&MpusFastMutex);

			if (!active) {
				if (MpusActive) { // turning off
					Socket->Send(&MpusAddress, (UCHAR*)0, 0, 1, MpusAudioSampleRate, MpusAudioBitRate, MpusAudioBitDepth,  MpusAudioChannels);
					MpusActive = 0;
					MpusSendFormat = 1;
				}
			}
			else {
				MpusActive = 1;
			}

			ExReleaseFastMutex(&MpusFastMutex);

			return STATUS_SUCCESS;
		}
        else if (PropertyRequest->PropertyItem->Id == KSPROPERTY_SNEAKY_TTL)
		{
			if (PropertyRequest->ValueSize != sizeof (UINT))
			{
				return STATUS_INVALID_PARAMETER;
			}

            UINT* pValue = (UINT *)PropertyRequest->Value;

			ExAcquireFastMutex(&MpusFastMutex);

			MpusTtl = *pValue;

			Socket->SetTtl(MpusTtl);

			ExReleaseFastMutex(&MpusFastMutex);

			return STATUS_SUCCESS;
		}
    }

    return STATUS_INVALID_PARAMETER;
}

//=============================================================================
// CMiniportWaveStreamCyclicSimple
//=============================================================================

//=============================================================================
CMiniportWaveCyclicStream::~CMiniportWaveCyclicStream
( 
    void 
)
/*++

Routine Description:

  Destructor for wavecyclicstream 

Arguments:

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    DPF_ENTER(("[CMiniportWaveCyclicStream::~CMiniportWaveCyclicStream]"));

    if (NULL != m_pMiniportLocal)
    {
        if (m_fCapture)
        {
            m_pMiniportLocal->m_fCaptureAllocated = FALSE;
        }
        else
        {
            m_pMiniportLocal->m_fRenderAllocated = FALSE;
        }
    }
} // ~CMiniportWaveCyclicStream

//=============================================================================
NTSTATUS
CMiniportWaveCyclicStream::Init
( 
    IN PCMiniportWaveCyclic         Miniport_,
    IN ULONG                        Pin_,
    IN BOOLEAN                      Capture_,
    IN PKSDATAFORMAT                DataFormat_
)
/*++

Routine Description:

  Initializes the stream object. Allocate a DMA buffer, timer and DPC

Arguments:

  Miniport_ -

  Pin_ -

  Capture_ -

  DataFormat -

  DmaChannel_ -

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    m_pMiniportLocal = Miniport_;

    return 
        CMiniportWaveCyclicStreamMSVAD::Init
        (
            Miniport_,
            Pin_,
            Capture_,
            DataFormat_
        );
} // Init

//=============================================================================
STDMETHODIMP_(NTSTATUS)
CMiniportWaveCyclicStream::NonDelegatingQueryInterface
( 
    IN  REFIID  Interface,
    OUT PVOID * Object 
)
/*++

Routine Description:

  QueryInterface

Arguments:

  Interface - GUID

  Object - interface pointer to be returned

Return Value:

  NT status code.

--*/
{
	PAGED_CODE();

    ASSERT(Object);

    if (IsEqualGUIDAligned(Interface, IID_IUnknown))
    {
        *Object = PVOID(PUNKNOWN(PMINIPORTWAVECYCLICSTREAM(this)));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IMiniportWaveCyclicStream))
    {
        *Object = PVOID(PMINIPORTWAVECYCLICSTREAM(this));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IDmaChannel))
    {
        *Object = PVOID(PDMACHANNEL(this));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IDrmAudioStream))
    {
        *Object = (PVOID)(PDRMAUDIOSTREAM)this;
    }
    else
    {
        *Object = NULL;
    }

    if (*Object)
    {
        PUNKNOWN(*Object)->AddRef();
        return STATUS_SUCCESS;
    }

    return STATUS_INVALID_PARAMETER;
} // NonDelegatingQueryInterface

//=============================================================================
STDMETHODIMP_(NTSTATUS) 
CMiniportWaveCyclicStream::SetContentId
(
    IN  ULONG                   contentId,
    IN  PCDRMRIGHTS             drmRights
)
/*++

Routine Description:

  Sets DRM content Id for this stream. Also updates the Mixed content Id.

Arguments:

  contentId - new content id

  drmRights - rights for this stream.

Return Value:

  NT status code.

--*/
{
    UNREFERENCED_PARAMETER(contentId);
    UNREFERENCED_PARAMETER(drmRights);

	PAGED_CODE();

    DPF_ENTER(("[CMiniportWaveCyclicStream::SetContentId]"));

    // if (drmRights.CopyProtect==TRUE)
    // Stop writing this stream to disk
    // 
    // if (drmRights.DigitalOutputDisable == TRUE)
    // Mute S/PDIF out. 
    // MSVAD does not support S/PDIF out. 
    //
    // To learn more about managing multiple streams, please look at MSVAD\drmmult
    //
    
	//m_SaveData.Disable(drmRights->CopyProtect);
    
    return STATUS_SUCCESS;
} // SetContentId

#pragma code_seg()

//=============================================================================
// SocketInitialised
//=============================================================================

void SocketInitialised(void* aContext)
{
    UNREFERENCED_PARAMETER(aContext);

	KeSetEvent(&WskInitialisedEvent, 0, false);
}

//=============================================================================
// WskInitialised
//=============================================================================

void WskInitialised(void* aContext)
{
	Socket = new (NonPagedPool, SNEAKY_POOLTAG) CSocketOhm();
	Socket->Initialise(*Wsk, SocketInitialised, aContext);
}

//=============================================================================
// MpusStop
//=============================================================================

void MpusStop()
{
	ExAcquireFastMutex(&MpusFastMutex);

	if (MpusActive)
	{
		Socket->Send(&MpusAddress, (UCHAR*) 0, 0, 1, MpusAudioSampleRate, MpusAudioBitRate, MpusAudioBitDepth,  MpusAudioChannels);
	}

	ExReleaseFastMutex(&MpusFastMutex);
}

//=============================================================================
// MpusSend
//=============================================================================

void MpusSend(UCHAR* aBuffer, UINT aBytes)
{
	ExAcquireFastMutex(&MpusFastMutex);

	if (MpusActive)
	{
		if (MpusSendFormat)
		{
			MpusSendFormat = 0;
			Socket->Send(&MpusAddress, (UCHAR*)0, 0, 0, MpusAudioSampleRate, MpusAudioBitRate, MpusAudioBitDepth,  MpusAudioChannels);
		}

		Socket->Send(&MpusAddress, aBuffer, aBytes, 0, MpusAudioSampleRate, MpusAudioBitRate, MpusAudioBitDepth,  MpusAudioChannels);
	}

	ExReleaseFastMutex(&MpusFastMutex);
}

//=============================================================================
// MpusSetFormat
//=============================================================================

void MpusSetFormat(ULONG aSampleRate, ULONG aBitRate, ULONG aBitDepth, ULONG aChannels)
{
	ExAcquireFastMutex(&MpusFastMutex);

	MpusAudioSampleRate = aSampleRate;
	MpusAudioBitRate = aBitRate;
	MpusAudioBitDepth = aBitDepth;
	MpusAudioChannels = aChannels;
	MpusSendFormat = 1;

	ExReleaseFastMutex(&MpusFastMutex);
}
