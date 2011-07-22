/*++

Copyright (c) 1997-2000  Microsoft Corporation All Rights Reserved

Module Name:

    mintopo.cpp

Abstract:

    Implementation of topology miniport.

--*/

#pragma warning (disable : 4127)

#include <msvad.h>
#include <common.h>
#include "drmsimp.h"
#include "minwave.h"
#include "mintopo.h"
#include "toptable.h"

FAST_MUTEX MpusFastMutex;

UINT MpusEnabled;
UINT MpusActive;
UINT MpusTtl;
UINT MpusAddr;
UINT MpusPort;


PHYSICALCONNECTIONTABLE TopologyPhysicalConnections =
{
    KSPIN_TOPO_WAVEOUT_SOURCE,  // TopologyIn
    (ULONG)-1,                  // TopologyOut
    (ULONG)-1,                  // WaveIn
    KSPIN_WAVE_RENDER_SOURCE    // WaveOut
};

#pragma code_seg("PAGE")

//=============================================================================
NTSTATUS
CreateMiniportTopologyMSVAD
( 
    OUT PUNKNOWN *              Unknown,
    IN  REFCLSID,
    IN  PUNKNOWN                UnknownOuter OPTIONAL,
    IN  POOL_TYPE               PoolType 
)
/*++

Routine Description:

    Creates a new topology miniport.

Arguments:

  Unknown - 

  RefclsId -

  UnknownOuter -

  PoolType - 

Return Value:

  NT status code.

--*/
{
    PAGED_CODE();

    ASSERT(Unknown);

    STD_CREATE_BODY(CMiniportTopology, Unknown, UnknownOuter, PoolType);
} // CreateMiniportTopologyMSVAD

//=============================================================================
CMiniportTopology::~CMiniportTopology
(
    void
)
/*++

Routine Description:

  Topology miniport destructor

Arguments:

Return Value:

  NT status code.

--*/
{
    PAGED_CODE();

    DPF_ENTER(("[CMiniportTopology::~CMiniportTopology]"));

	m_Port->Release();

} // ~CMiniportTopology

//=============================================================================
NTSTATUS
CMiniportTopology::DataRangeIntersection
( 
    IN  ULONG                   PinId,
    IN  PKSDATARANGE            ClientDataRange,
    IN  PKSDATARANGE            MyDataRange,
    IN  ULONG                   OutputBufferLength,
    OUT PVOID                   ResultantFormat     OPTIONAL,
    OUT PULONG                  ResultantFormatLength 
)
/*++

Routine Description:

  The DataRangeIntersection function determines the highest quality 
  intersection of two data ranges.

Arguments:

  PinId - Pin for which data intersection is being determined. 

  ClientDataRange - Pointer to KSDATARANGE structure which contains the data range 
                    submitted by client in the data range intersection property 
                    request. 

  MyDataRange - Pin's data range to be compared with client's data range. 

  OutputBufferLength - Size of the buffer pointed to by the resultant format 
                       parameter. 

  ResultantFormat - Pointer to value where the resultant format should be 
                    returned. 

  ResultantFormatLength - Actual length of the resultant format that is placed 
                          at ResultantFormat. This should be less than or equal 
                          to OutputBufferLength. 

Return Value:

  NT status code.

--*/
{
    PAGED_CODE();

    return 
        CMiniportTopologyMSVAD::DataRangeIntersection
        (
            PinId,
            ClientDataRange,
            MyDataRange,
            OutputBufferLength,
            ResultantFormat,
            ResultantFormatLength
        );
} // DataRangeIntersection

//=============================================================================
STDMETHODIMP
CMiniportTopology::GetDescription
( 
    OUT PPCFILTER_DESCRIPTOR *  OutFilterDescriptor 
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

    return CMiniportTopologyMSVAD::GetDescription(OutFilterDescriptor);
} // GetDescription

//=============================================================================
STDMETHODIMP
CMiniportTopology::Init
( 
    IN PUNKNOWN                 UnknownAdapter,
    IN PRESOURCELIST            ResourceList,
    IN PPORTTOPOLOGY            Port_ 
)
/*++

Routine Description:

  The Init function initializes the miniport. Callers of this function 
  should run at IRQL PASSIVE_LEVEL

Arguments:

  UnknownAdapter - A pointer to the Iuknown interface of the adapter object. 

  ResourceList - Pointer to the resource list to be supplied to the miniport 
                 during initialization. The port driver is free to examine the 
                 contents of the ResourceList. The port driver will not be 
                 modify the ResourceList contents. 

  Port - Pointer to the topology port object that is linked with this miniport. 

Return Value:

  NT status code.

--*/
{
    UNREFERENCED_PARAMETER(ResourceList);

    PAGED_CODE();

    ASSERT(UnknownAdapter);
    ASSERT(Port_);

    DPF_ENTER(("[CMiniportTopology::Init]"));

    NTSTATUS                    ntStatus;

	ExInitializeFastMutex(&MpusFastMutex);

	ExAcquireFastMutex(&MpusFastMutex);

	MpusEnabled = 0;
	MpusActive = 0;
	MpusTtl = 0;
	MpusAddr = 0;
	MpusPort = 0;

	ExReleaseFastMutex(&MpusFastMutex);

    ntStatus = CMiniportTopologyMSVAD::Init (
        UnknownAdapter,
        Port_
    );

    if (NT_SUCCESS(ntStatus)) {
        m_FilterDescriptor = &MiniportFilterDescriptor;
		m_Port = Port_;
		m_Port->AddRef();
    }

    return ntStatus;
} // Init

//=============================================================================
STDMETHODIMP
CMiniportTopology::NonDelegatingQueryInterface
( 
    IN  REFIID                  Interface,
    OUT PVOID                   * Object 
)
/*++

Routine Description:

  QueryInterface for MiniportTopology

Arguments:

  Interface - GUID of the interface

  Object - interface object to be returned.

Return Value:

  NT status code.

--*/
{
    PAGED_CODE();

    ASSERT(Object);

    if (IsEqualGUIDAligned(Interface, IID_IUnknown))
    {
        *Object = PVOID(PUNKNOWN(this));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IMiniport))
    {
        *Object = PVOID(PMINIPORT(this));
    }
    else if (IsEqualGUIDAligned(Interface, IID_IMiniportTopology))
    {
        *Object = PVOID(PMINIPORTTOPOLOGY(this));
    }
    else
    {
        *Object = NULL;
    }

    if (*Object)
    {
        // We reference the interface for the caller.
        PUNKNOWN(*Object)->AddRef();
        return(STATUS_SUCCESS);
    }

    return(STATUS_INVALID_PARAMETER);
} // NonDelegatingQueryInterface

//=============================================================================
// called with the fast mutex locked

void
CMiniportTopology::CreateWaveMiniport()
{ 
    PAGED_CODE();

	MpusEnabled = 1;
	JackDescSpeakers.IsConnected = true;

    DPF_ENTER(("[CreateWaveMiniport]"));

	PUNKNOWN* waveport = m_AdapterCommon->WavePortDriverDest();
	
	if (!*waveport) {
		return;
	}

	PDEVICE_OBJECT device = m_AdapterCommon->GetDeviceObject();

    // Register the subdevice (port/miniport combination).
    
	PcRegisterSubdevice (
        device,
        L"Wave",
        *waveport 
    );

    // register wave <=> topology connections

    PcRegisterPhysicalConnection ( 
        device,
        *waveport,
        KSPIN_WAVE_RENDER_SOURCE,
        m_Port,
        KSPIN_TOPO_WAVEOUT_SOURCE
    );
}

//=============================================================================
// called with the fast mutex locked

void
CMiniportTopology::DestroyWaveMiniport()
{
    PAGED_CODE();

	MpusEnabled = 0;
	JackDescSpeakers.IsConnected = false;

    DPF_ENTER(("[DestroyWaveMiniport]"));

	PUNKNOWN* waveport = m_AdapterCommon->WavePortDriverDest();
	
	if (!*waveport) {
		return;
	}

	PDEVICE_OBJECT device = m_AdapterCommon->GetDeviceObject();

    // Unregister wave <=> topology connections

	IUnregisterPhysicalConnection* unregisterPhysicalConnection;

	m_Port->QueryInterface(IID_IUnregisterPhysicalConnection, (PVOID*)&unregisterPhysicalConnection);

	unregisterPhysicalConnection->UnregisterPhysicalConnection ( 
        device,
        *waveport,
        KSPIN_WAVE_RENDER_SOURCE,
        m_Port,
        KSPIN_TOPO_WAVEOUT_SOURCE
    );

	unregisterPhysicalConnection->Release();

    // Unregister the subdevice (port/miniport combination).
    
	IUnregisterSubdevice* unregisterSubdevice;

	m_Port->QueryInterface(IID_IUnregisterSubdevice, (PVOID*)&unregisterSubdevice);

	unregisterSubdevice->UnregisterSubdevice (
        device,
        *waveport 
    );

	unregisterSubdevice->Release();

	//TODO - when disabled
	//if (MpusActive) {
	//	Socket->Send(&MpusAddress, (UCHAR*)0, 0, 1, MpusAudioSampleRate, MpusAudioBitRate, MpusAudioBitDepth,  MpusAudioChannels);
	//}
	//MpusSendFormat = 1;
}

//=============================================================================
NTSTATUS
PropertyHandler_Jack
( 
    IN PPCPROPERTY_REQUEST      PropertyRequest 
)
/*++

Routine Description:

  Redirects property request to miniport object

Arguments:

  PropertyRequest - 

Return Value:

  NT status code.

--*/
{
    PAGED_CODE();

    ASSERT(PropertyRequest);

    DPF_ENTER(("[PropertyHandler_TopoFilter]"));

    NTSTATUS            ntStatus = STATUS_INVALID_DEVICE_REQUEST;

    if (IsEqualGUIDAligned(*PropertyRequest->PropertyItem->Set, KSPROPSETID_Jack))
	{
		if (PropertyRequest->PropertyItem->Id == KSPROPERTY_JACK_DESCRIPTION)
		{
			if (PropertyRequest->InstanceSize >= sizeof(ULONG))
			{
				ULONG nPinId = *(PULONG(PropertyRequest->Instance));

				if ((nPinId < ARRAYSIZE(JackDescriptions)) && (JackDescriptions[nPinId] != NULL))
				{
					if (PropertyRequest->Verb & KSPROPERTY_TYPE_BASICSUPPORT)
					{
						ntStatus = PropertyHandler_BasicSupport (
							PropertyRequest,
							KSPROPERTY_TYPE_BASICSUPPORT | KSPROPERTY_TYPE_GET,
							VT_ILLEGAL
						);
					}
					else
					{
						ULONG cbNeeded = sizeof(KSMULTIPLE_ITEM) + sizeof(KSJACK_DESCRIPTION);

						if (PropertyRequest->ValueSize == 0)
						{
							PropertyRequest->ValueSize = cbNeeded;
							ntStatus = STATUS_BUFFER_OVERFLOW;
						}
						else if (PropertyRequest->ValueSize < cbNeeded)
						{
							ntStatus = STATUS_BUFFER_TOO_SMALL;
						}
						else
						{
							if (PropertyRequest->Verb & KSPROPERTY_TYPE_GET)
							{
								PKSMULTIPLE_ITEM pMI = (PKSMULTIPLE_ITEM)PropertyRequest->Value;
								PKSJACK_DESCRIPTION pDesc = (PKSJACK_DESCRIPTION)(pMI+1);

								pMI->Size = cbNeeded;
								pMI->Count = 1;

								RtlCopyMemory(pDesc, JackDescriptions[nPinId], sizeof(KSJACK_DESCRIPTION));
								ntStatus = STATUS_SUCCESS;
							}
						}
					}
				}
			}
		}
    }

    return ntStatus;
} // PropertyHandler_TopoFilter

//=============================================================================
NTSTATUS
PropertyHandler_Wave
(
    IN PPCPROPERTY_REQUEST		PropertyRequest
)
{
    PAGED_CODE();

    ASSERT(PropertyRequest);

    DPF_ENTER(("[PropertyHandler_TopoFilter]"));

	if (IsEqualGUIDAligned(*PropertyRequest->PropertyItem->Set, KSPROPSETID_Private))
    {
		if (PropertyRequest->Verb & KSPROPERTY_TYPE_GET)
		{
			// Check the ID ("function" in "group").
			if (PropertyRequest->PropertyItem->Id != KSPROPERTY_OHSOUNDCARD_VERSION)
			{
				return STATUS_INVALID_PARAMETER;
			}

			// validate buffer size.
			if (PropertyRequest->ValueSize != sizeof (UINT))
			{
				return STATUS_INVALID_PARAMETER;
			}

			// The "Value" is the out buffer that you pass in DeviceIoControl call.

			UINT* pValue = (UINT*)PropertyRequest->Value;
        
			// Check the buffer.

			if (!pValue)
			{
				return STATUS_INVALID_PARAMETER;
			}

			*pValue = 1; // Version 1

			return STATUS_SUCCESS;
		}
		else if (PropertyRequest->Verb & KSPROPERTY_TYPE_SET)
		{
			if (PropertyRequest->PropertyItem->Id == KSPROPERTY_OHSOUNDCARD_ENABLED) {
				if (PropertyRequest->ValueSize != sizeof (UINT)) {
					return STATUS_INVALID_PARAMETER;
				}

				UINT* pValue = (UINT*)PropertyRequest->Value;

				UINT enabled = *pValue;

				PCMiniportTopology  pMiniport = (PCMiniportTopology)PropertyRequest->MajorTarget;

				ExAcquireFastMutex(&MpusFastMutex);

				if (MpusEnabled != enabled) {
					if (enabled) {
						pMiniport->CreateWaveMiniport();
					}
					else {
						pMiniport->DestroyWaveMiniport();
					}
				}

				ExReleaseFastMutex(&MpusFastMutex);

				return STATUS_SUCCESS;
			}
			else if (PropertyRequest->PropertyItem->Id == KSPROPERTY_OHSOUNDCARD_ACTIVE) {

				if (PropertyRequest->ValueSize != sizeof (UINT)) {
					return STATUS_INVALID_PARAMETER;
				}

				UINT* pValue = (UINT*)PropertyRequest->Value;

				UINT active = *pValue;

				ExAcquireFastMutex(&MpusFastMutex);

				if (MpusActive != active) {
					if (active) {
						MpusActive = 1;
						//TODO - when activated
					}
					else {
						MpusActive = 0;
						//TODO when deactivated
						//if (MpusEnabled) {
						//	Socket->Send(&MpusAddress, (UCHAR*)0, 0, 1, MpusAudioSampleRate, MpusAudioBitRate, MpusAudioBitDepth,  MpusAudioChannels);
						//}
						//MpusSendFormat = 1;
					}
				}

				ExReleaseFastMutex(&MpusFastMutex);

				return STATUS_SUCCESS;
			}
			else if (PropertyRequest->PropertyItem->Id == KSPROPERTY_OHSOUNDCARD_ENDPOINT) {

				if (PropertyRequest->ValueSize != (sizeof (UINT) * 2)) {
					return STATUS_INVALID_PARAMETER;
				}

				UINT* pValue = (UINT*)PropertyRequest->Value;

				UINT addr = *pValue++;
				UINT port = *pValue;

				ExAcquireFastMutex(&MpusFastMutex);

				if (MpusAddr != addr || MpusPort != port) {
					MpusAddr = addr;
					MpusPort = port;
					//TODO when endpoint changes
					//CWinsock::Initialise(&MpusAddress, MpusAddr, MpusPort);
				}

				ExReleaseFastMutex(&MpusFastMutex);

				return STATUS_SUCCESS;
			}
			else if (PropertyRequest->PropertyItem->Id == KSPROPERTY_OHSOUNDCARD_TTL) {

				if (PropertyRequest->ValueSize != sizeof (UINT)) {
					return STATUS_INVALID_PARAMETER;
				}

				UINT* pValue = (UINT*)PropertyRequest->Value;

				UINT ttl = *pValue;

				ExAcquireFastMutex(&MpusFastMutex);

				if (MpusTtl != ttl) {
					MpusTtl = *pValue;
					//TODO when ttl changes
					//Socket->SetTtl(MpusTtl);
				}

				ExReleaseFastMutex(&MpusFastMutex);

				return STATUS_SUCCESS;
			}
		}

		return STATUS_INVALID_PARAMETER;
	}

	return STATUS_INVALID_DEVICE_REQUEST;
}

//=============================================================================
NTSTATUS
PropertyHandler_Topology
( 
    IN PPCPROPERTY_REQUEST      PropertyRequest 
)
/*++

Routine Description:

  Redirects property request to miniport object

Arguments:

  PropertyRequest - 

Return Value:

  NT status code.

--*/
{
    PAGED_CODE();

    ASSERT(PropertyRequest);

    DPF_ENTER(("[PropertyHandler_Topology]"));

    return ((PCMiniportTopology)
        (PropertyRequest->MajorTarget))->PropertyHandlerGeneric
        (
            PropertyRequest
        );
} // PropertyHandler_Topology


#pragma code_seg()

