#include "Soundcard.h"
#include "Icon.h"

#include <Ascii.h>
#include <Maths.h>
#include <Arch.h>
#include <Debug.h>

#include <Setupapi.h>
#include <ks.h>
#include <ksmedia.h>
#include <initguid.h>

EXCEPTION(SoundcardError);

using namespace OpenHome;
using namespace OpenHome::Net;

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
				iHandle = CreateFile(deviceInterfaceDetailData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

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
    KSPROPERTY prop;
				
	prop.Set = SNEAKY_GUID;
    prop.Id = KSPROPERTY_SNEAKY_ENABLED;
    prop.Flags = KSPROPERTY_TYPE_SET;

    DWORD bytes;

	DWORD value = aValue ? 1 : 0;

    DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), &value, sizeof(value), &bytes, 0);
}

void OhmSenderDriverWindows::SetActive(TBool  aValue)
{
    KSPROPERTY prop;
				
	prop.Set = SNEAKY_GUID;
    prop.Id = KSPROPERTY_SNEAKY_ACTIVE;
    prop.Flags = KSPROPERTY_TYPE_SET;

    DWORD bytes;

	DWORD value = aValue ? 1 : 0;

    DeviceIoControl(iHandle, IOCTL_KS_PROPERTY, &prop, sizeof(KSPROPERTY), &value, sizeof(value), &bytes, 0);
}

void OhmSenderDriverWindows::SetEndpoint(const Endpoint& aEndpoint)
{
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

// C interface

THandle SoundcardCreate(uint32_t aSubnet, uint32_t aChannel, uint32_t aTtl, uint32_t aMulticast, uint32_t aEnabled, uint32_t aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr)
{
	return (Soundcard::Create(aSubnet, aChannel, aTtl, (aMulticast == 0) ? false : true, (aEnabled == 0) ? false : true, aPreset, aReceiverCallback, aReceiverPtr));
}

void SoundcardSetSubnet(THandle aSoundcard, uint32_t aValue)
{
	((Soundcard*)aSoundcard)->SetSubnet(aValue);
}

void SoundcardSetChannel(THandle aSoundcard, uint32_t aValue)
{
	((Soundcard*)aSoundcard)->SetChannel(aValue);
}

void SoundcardSetTtl(THandle aSoundcard, uint32_t aValue)
{
	((Soundcard*)aSoundcard)->SetTtl(aValue);
}

void SoundcardSetMulticast(THandle aSoundcard, uint32_t aValue)
{
	((Soundcard*)aSoundcard)->SetMulticast((aValue == 0) ? false : true);
}

void SoundcardSetEnabled(THandle aSoundcard, uint32_t aValue)
{
	((Soundcard*)aSoundcard)->SetEnabled((aValue == 0) ? false : true);
}

void SoundcardSetPreset(THandle aSoundcard, uint32_t aValue)
{
	((Soundcard*)aSoundcard)->SetPreset(aValue);
}

void SoundcardSetTrack(THandle aSoundcard, const char* aUri, const char* aMetadata, uint64_t aSamplesTotal, uint64_t aSampleStart)
{
	((Soundcard*)aSoundcard)->SetTrack(aUri, aMetadata, aSamplesTotal, aSampleStart);
}

void SoundcardSetMetatext(THandle aSoundcard, const char* aValue)
{
	((Soundcard*)aSoundcard)->SetMetatext(aValue);
}

void SoundcardDestroy(THandle aSoundcard)
{
	delete ((Soundcard*)aSoundcard);
}

const char* ReceiverUdn(THandle aReceiver)
{
	return (((Receiver*)aReceiver)->Udn());
}

const char* ReceiverRoom(THandle aReceiver)
{
	return (((Receiver*)aReceiver)->Room());
}

const char* ReceiverGroup(THandle aReceiver)
{
	return (((Receiver*)aReceiver)->Group());
}

const char* ReceiverName(THandle aReceiver)
{
	return (((Receiver*)aReceiver)->Name());
}

EReceiverStatus ReceiverStatus(THandle aReceiver)
{
	return (((Receiver*)aReceiver)->Status());
}

void ReceiverPlay(THandle aReceiver)
{
	((Receiver*)aReceiver)->Play();
}

void ReceiverStop(THandle aReceiver)
{
	((Receiver*)aReceiver)->Stop();
}

void ReceiverStandby(THandle aReceiver)
{
	((Receiver*)aReceiver)->Standby();
}

void ReceiverAddRef(THandle aReceiver)
{
	((Receiver*)aReceiver)->AddRef();
}

void ReceiverRemoveRef(THandle aReceiver)
{
	((Receiver*)aReceiver)->RemoveRef();
}

// Receiver

Receiver::Receiver(ReceiverManager3Receiver& aReceiver)
	: iReceiver(aReceiver)
	, iUdn(iReceiver.Udn())
	, iRoom(iReceiver.Room())
	, iGroup(iReceiver.Group())
	, iName(iReceiver.Name())
	, iRefCount(1)
{
	iReceiver.AddRef();
}

const TChar* Receiver::Udn() const
{
	return (iUdn.CString());
}

const TChar* Receiver::Room() const
{
	return (iRoom.CString());
}

const TChar* Receiver::Group() const
{
	return (iGroup.CString());
}

const TChar* Receiver::Name() const
{
	return (iName.CString());
}

EReceiverStatus Receiver::Status() const
{
	return (EReceiverStatus)iReceiver.Status();
}


void Receiver::Play()
{
	iReceiver.Play();
}

void Receiver::Stop()
{
	iReceiver.Stop();
}

void Receiver::Standby()
{
	iReceiver.Standby();
}

void Receiver::AddRef()
{
	iRefCount++;
}

void Receiver::RemoveRef()
{
	if (--iRefCount == 0) {
		delete (this);
	}
}

Receiver::~Receiver()
{
	iReceiver.RemoveRef();
}

// Soundcard

Soundcard* Soundcard::Create(TIpAddress aSubnet, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr)
{
	try {
		Soundcard* soundcard = new Soundcard(aSubnet, aChannel, aTtl, aMulticast, aEnabled, aPreset, aReceiverCallback, aReceiverPtr);
		return (soundcard);
	}
	catch (SoundcardError) {
	}
	return (0);
}

Soundcard::Soundcard(TIpAddress /* aSubnet */, TUint aChannel, TUint aTtl, TBool aMulticast, TBool aEnabled, TUint aPreset, ReceiverCallback aReceiverCallback, void* aReceiverPtr)
	: iReceiverCallback(aReceiverCallback)
	, iReceiverPtr(aReceiverPtr)
{
	InitialisationParams* initParams = InitialisationParams::Create();

	UpnpLibrary::Initialise(initParams);

	std::vector<NetworkInterface*>* list = UpnpLibrary::CreateSubnetList();

	ASSERT(list->size() > 0);

	NetworkInterface* iface = *list->begin();

	printf("Using %x\n", iface->Address());
    
    UpnpLibrary::StartCombined(iface->Address());

	delete (list);

	Bws<kMaxUdnBytes> computer;
	Bws<kMaxUdnBytes> udn;
	Bws<kMaxUdnBytes + 1> friendly;

	TUint bytes = computer.MaxBytes();

	if (!GetComputerName((LPSTR)computer.Ptr(), (LPDWORD)&bytes)) {
		THROW(SoundcardError);
	}

	computer.SetBytes(bytes);
	udn.Replace("ohSoundcard-");
	udn.Append(computer);
	friendly.Replace(udn);
	friendly.Append('\0');

	iDevice = new DvDeviceStandard(udn);
    
	iDevice->SetAttribute("Upnp.Domain", "av.openhome.org");
    iDevice->SetAttribute("Upnp.Type", "Soundcard");
    iDevice->SetAttribute("Upnp.Version", "1");
    iDevice->SetAttribute("Upnp.FriendlyName", (TChar*)friendly.Ptr());
    iDevice->SetAttribute("Upnp.Manufacturer", "Openhome");
    iDevice->SetAttribute("Upnp.ManufacturerUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.ModelDescription", "OpenHome Soundcard");
    iDevice->SetAttribute("Upnp.ModelName", "ohSoundcard");
    iDevice->SetAttribute("Upnp.ModelNumber", "1");
    iDevice->SetAttribute("Upnp.ModelUrl", "http://www.openhome.org");
    iDevice->SetAttribute("Upnp.SerialNumber", "");
    iDevice->SetAttribute("Upnp.Upc", "");

    iDriver = new OhmSenderDriverWindows();
    
	Brn icon(icon_png, icon_png_len);

	iSender = new OhmSender(*iDevice, *iDriver, computer, aChannel, iface->Address(), aTtl, aMulticast, aEnabled, icon, Brn("image/png"), aPreset);
	
    iDevice->SetEnabled();

	iReceiverManager = new ReceiverManager3(*this, iSender->SenderUri(), iSender->SenderMetadata());
}

void Soundcard::SetSubnet(TIpAddress /* aValue */)
{
	// TOOD
}

void Soundcard::SetChannel(TUint aValue)
{
	iSender->SetChannel(aValue);
}

void Soundcard::SetTtl(TUint aValue)
{
	iSender->SetTtl(aValue);
}

void Soundcard::SetMulticast(TBool aValue)
{
	iSender->SetMulticast(aValue);
	iReceiverManager->SetMetadata(iSender->SenderMetadata());
}

void Soundcard::SetEnabled(TBool aValue)
{
	iSender->SetEnabled(aValue);
}

void Soundcard::SetPreset(TUint aValue)
{
	iSender->SetPreset(aValue);
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

// IReceiverManager3Handler

void Soundcard::ReceiverAdded(ReceiverManager3Receiver& aReceiver)
{
	Receiver* receiver = new Receiver(aReceiver);
	aReceiver.SetUserData(receiver);
	(*iReceiverCallback)(iReceiverPtr, eAdded, (THandle)receiver);
}

void Soundcard::ReceiverChanged(ReceiverManager3Receiver& aReceiver)
{
	Receiver* receiver = (Receiver*)(aReceiver.UserData());
	ASSERT(receiver);
	(*iReceiverCallback)(iReceiverPtr, eChanged, (THandle)receiver);
}

void Soundcard::ReceiverRemoved(ReceiverManager3Receiver& aReceiver)
{
	Receiver* receiver = (Receiver*)(aReceiver.UserData());
	ASSERT(receiver);
	(*iReceiverCallback)(iReceiverPtr, eRemoved, (THandle)receiver);
	receiver->RemoveRef();
}


