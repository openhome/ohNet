#include "Soundcard.h"

#include <Ascii.h>
#include <Maths.h>
#include <Arch.h>
#include <Debug.h>

#include <Setupapi.h>
#include <ks.h>
#include <ksmedia.h>
#include <initguid.h>

EXCEPTION(SoundcardError);

using namespace Zapp;

// OhmSenderDriverWindows

DEFINE_GUID(SNEAKY_GUID, 0xff89e492, 0x5c4a, 0x4b2c, 0x87, 0x9a, 0x6a, 0xf, 0xa6, 0x56, 0x1a, 0x63);

static const TUint KSPROPERTY_SNEAKY_VERSION = 0;
static const TUint KSPROPERTY_SNEAKY_ENABLED = 1;
static const TUint KSPROPERTY_SNEAKY_ACTIVE = 2;
static const TUint KSPROPERTY_SNEAKY_ENDPOINT = 3;
static const TUint KSPROPERTY_SNEAKY_TTL = 4;

OhmSenderDriverWindows::OhmSenderDriverWindows()
{
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&KSCATEGORY_AUDIO, 0, 0, DIGCF_DEVICEINTERFACE | DIGCF_PROFILE | DIGCF_PRESENT);

	if (deviceInfoSet == 0) {
		THROW(SoundcardError);
	}

	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;

	deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	// build a DevInfo Data structure

	SP_DEVINFO_DATA deviceInfoData;

	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		 
	// build a Device Interface Detail Data structure

	TByte* detail = new TByte[1000];

	PSP_DEVICE_INTERFACE_DETAIL_DATA deviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)detail;

	deviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

	for (TUint i = 0; SetupDiEnumDeviceInterfaces(deviceInfoSet, 0, &KSCATEGORY_AUDIO, i, &deviceInterfaceData); i++)
	{
		// now we can get some more detailed information

		if (SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &deviceInterfaceData, deviceInterfaceDetailData, 1000, 0, &deviceInfoData))
		{
			try
			{
				iHandle = CreateFile(deviceInterfaceDetailData->DevicePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

                KSPROPERTY prop;
				
				prop.Set = SNEAKY_GUID;
                prop.Id = KSPROPERTY_SNEAKY_VERSION;
                prop.Flags = KSPROPERTY_TYPE_GET;

                TByte buffer[4];

                DWORD bytes;

                if (DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), buffer, sizeof(buffer), &bytes, 0))
                {
					TUint version = *(TUint*)buffer;

					if (version == 1) {
						delete [] detail;
						SetupDiDestroyDeviceInfoList(deviceInfoSet);
						return;
					}
                }
			}
			catch (...)
			{
			}
		}
	}

	delete [] detail;
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
	THROW(SoundcardError);
}

void OhmSenderDriverWindows::SetEnabled(TBool aValue)
{
	printf("ENABLED %d\n", aValue);

    KSPROPERTY prop;
				
	prop.Set = SNEAKY_GUID;
    prop.Id = KSPROPERTY_SNEAKY_ENABLED;
    prop.Flags = KSPROPERTY_TYPE_SET;

    DWORD bytes;

    DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), &aValue, sizeof(aValue), &bytes, 0);
}

void OhmSenderDriverWindows::SetActive(TBool  aValue)
{
	printf("ACTIVE %d\n", aValue);

    KSPROPERTY prop;
				
	prop.Set = SNEAKY_GUID;
    prop.Id = KSPROPERTY_SNEAKY_ACTIVE;
    prop.Flags = KSPROPERTY_TYPE_SET;

    DWORD bytes;

    DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), &aValue, sizeof(aValue), &bytes, 0);
}

void OhmSenderDriverWindows::SetEndpoint(const Endpoint& aEndpoint)
{
	printf("ENDPOINT %x:%d\n", aEndpoint.Address(), aEndpoint.Port());

	KSPROPERTY prop;
				
	prop.Set = SNEAKY_GUID;
    prop.Id = KSPROPERTY_SNEAKY_ENDPOINT;
    prop.Flags = KSPROPERTY_TYPE_SET;

	TByte buffer[8];

	ULONG* ptr = (ULONG*)buffer;
	
	*ptr++ = Arch::BigEndian4(aEndpoint.Address());
	*ptr++ = aEndpoint.Port();

    DWORD bytes;

    DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), &buffer, sizeof(buffer), &bytes, 0);
}


void OhmSenderDriverWindows::SetTtl(TUint aValue)
{
	printf("TTL %d\n", aValue);

    KSPROPERTY prop;
				
	prop.Set = SNEAKY_GUID;
    prop.Id = KSPROPERTY_SNEAKY_TTL;
    prop.Flags = KSPROPERTY_TYPE_SET;

    DWORD bytes;

    DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), &aValue, sizeof(aValue), &bytes, 0);
}

void OhmSenderDriverWindows::SetTrackPosition(TUint64 /*aSamplesTotal*/, TUint64 /*aSampleStart*/)
{
}



// Soundcard

Soundcard* Soundcard::Create(const TChar* aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled)
{
	try {
		return (new Soundcard(aName, aChannel, aInterface, aTtl, aMulticast, aEnabled));
	}
	catch (SoundcardError) {
	}
	return (0);
}

Soundcard::Soundcard(const TChar* aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled)
{
	InitialisationParams* initParams = InitialisationParams::Create();

    UpnpLibrary::Initialise(initParams);
    
    UpnpLibrary::StartDv();

	Bws<kMaxUdnBytes> computer;
	Bws<kMaxUdnBytes> udn;

	TUint bytes = computer.MaxBytes();

	if (GetComputerName((LPSTR)computer.Ptr(), (LPDWORD)&bytes)) {
		computer.SetBytes(bytes);
		udn.Replace("ohSoundcard-");
		udn.Append(computer);
	}

	iDevice = new DvDeviceStandard(udn);
    
	iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Soundcard");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", aName);
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "OpenHome Soundcard");
    iDevice->SetAttribute("Upnp.ModelName", "ohSoundcard");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new OhmSenderDriverWindows();
    
	iSender = new OhmSender(*iDevice, *iDriver, Brn(aName), aChannel, aInterface, aTtl, aMulticast, aEnabled);
	
    iDevice->SetEnabled();
}

void Soundcard::SetName(const TChar* aValue)
{
	iSender->SetName(Brn(aValue));
}

void Soundcard::SetChannel(TUint aValue)
{
	iSender->SetChannel(aValue);
}

void Soundcard::SetInterface(TIpAddress aValue)
{
	iSender->SetInterface(aValue);
}

void Soundcard::SetTtl(TUint aValue)
{
	iSender->SetTtl(aValue);
}

void Soundcard::SetMulticast(TBool aValue)
{
	iSender->SetMulticast(aValue);
}

void Soundcard::SetEnabled(TBool aValue)
{
	iSender->SetEnabled(aValue);
}

void Soundcard::SetTrack(const TChar* aUri, const TChar* aMetadata, TUint64 aSamplesTotal, TUint64 aSampleStart)
{
	iSender->SetTrack(Brn(aUri), Brn(aMetadata), aSamplesTotal, aSampleStart);
}

void Soundcard::SetMetatext(const TChar* aValue)
{
	iSender->SetMetatext(Brn(aValue));
}
    
Soundcard::~Soundcard()
{
    delete (iSender);
	delete (iDriver);
	delete (iDevice);
}

