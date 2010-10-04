#include <C/DvDevice.h>
#include <Core/DvDevice.h>
#include <C/DviDeviceC.h>

using namespace Zapp;

DviDeviceC::DviDeviceC(const char* aUdn)
{
	Brn udn(aUdn);
	iDevice = new DvDevice(udn, *this);
	iResourceManager = NULL;
	iCallbackArg = NULL;
	iResourceWriter = NULL;
}

DviDeviceC::DviDeviceC(const char* aUdn, ZappCallbackResourceManager aResourceManager, void* aPtr)
{
	Brn udn(aUdn);
	iDevice = new DvDevice(udn, *this);
	iResourceManager = aResourceManager;
	iCallbackArg = aPtr;
	iResourceWriter = NULL;
}

DviDeviceC::~DviDeviceC()
{
	delete iDevice;
}

DvDevice* DviDeviceC::Device()
{
	return iDevice;
}

void DviDeviceC::WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter)
{
	ASSERT(iResourceManager != NULL);
	iResourceWriter = &aResourceWriter;
	Brhz uriTail(aUriTail);
	iResourceManager(iCallbackArg, uriTail.CString(), aInterface, this, WriteResourceBegin, WriteResource, WriteResourceEnd);
}

void DviDeviceC::WriteResourceBegin(void* aPtr, uint32_t aTotalBytes, const char* aMimeType)
{
	DviDeviceC* self = reinterpret_cast<DviDeviceC*>(aPtr);
	self->iResourceWriter->WriteResourceBegin(aTotalBytes, aMimeType);
}

void DviDeviceC::WriteResource(void* aPtr, const uint8_t* aData, uint32_t aBytes)
{
	DviDeviceC* self = reinterpret_cast<DviDeviceC*>(aPtr);
	self->iResourceWriter->WriteResource(aData, aBytes);
}

void DviDeviceC::WriteResourceEnd(void* aPtr)
{
	DviDeviceC* self = reinterpret_cast<DviDeviceC*>(aPtr);
	self->iResourceWriter->WriteResourceEnd();
}



DvDeviceC DvDeviceCreateNoResources(const char* aUdn)
{
	DviDeviceC* wrapper = new DviDeviceC(aUdn);
	return (DvDeviceC)wrapper;
}

DvDeviceC DvDeviceCreate(const char* aUdn, ZappCallbackResourceManager aResourceManager, void* aPtr)
{
	DviDeviceC* wrapper = new DviDeviceC(aUdn, aResourceManager, aPtr);
	return (DvDeviceC)wrapper;
}

void DvDeviceDestroy(DvDeviceC aDevice)
{
	delete DviDeviceC::DeviceFromHandle(aDevice);
}

const char* DvDeviceUdn(DvDeviceC aDevice)
{
	return (const char*)DviDeviceC::DeviceFromHandle(aDevice)->Udn().Ptr();
}

int32_t DvDeviceEnabled(DvDeviceC aDevice)
{
	return (DviDeviceC::DeviceFromHandle(aDevice)->Enabled()? 1 : 0);
}

void DvDeviceSetEnabled(DvDeviceC aDevice)
{
	DviDeviceC::DeviceFromHandle(aDevice)->SetEnabled();
}

void DvDeviceSetDisabled(DvDeviceC aDevice, ZappCallback aCompleted, void* aPtr)
{
	Functor completed = MakeFunctor(aPtr, aCompleted);
	DviDeviceC::DeviceFromHandle(aDevice)->SetDisabled(completed);
}

void DvDeviceGetAttribute(DvDeviceC aDevice, const char* aKey, const char** aValue)
{
	DviDeviceC::DeviceFromHandle(aDevice)->GetAttribute(aKey, aValue);
}

void DvDeviceSetAttribute(DvDeviceC aDevice, const char* aKey, const char* aValue)
{
	DviDeviceC::DeviceFromHandle(aDevice)->SetAttribute(aKey, aValue);
}
