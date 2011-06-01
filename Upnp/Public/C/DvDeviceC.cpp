#include <C/DvDevice.h>
#include <Core/DvDevice.h>
#include <C/DviDeviceC.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviDeviceC

DviDeviceC::DviDeviceC(const char* aUdn)
{
	Brn udn(aUdn);
	iDevice = new DvDevice(udn);
	iResourceManager = NULL;
	iCallbackArg = NULL;
	iResourceWriter = NULL;
}

DviDeviceC::DviDeviceC()
{
	iResourceManager = NULL;
	iCallbackArg = NULL;
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

void DviDeviceC::WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
	ASSERT(iResourceManager != NULL);
	iResourceWriter = &aResourceWriter;
	Brhz uriTail(aUriTail);
	iResourceManager(iCallbackArg, uriTail.CString(), aInterface, &aLanguageList, this, WriteResourceBegin, WriteResource, WriteResourceEnd);
}

void DviDeviceC::WriteResourceBegin(void* aPtr, uint32_t aTotalBytes, const char* aMimeType)
{ // static
	DviDeviceStandardC* self = reinterpret_cast<DviDeviceStandardC*>(aPtr);
	self->iResourceWriter->WriteResourceBegin(aTotalBytes, aMimeType);
}

void DviDeviceC::WriteResource(void* aPtr, const uint8_t* aData, uint32_t aBytes)
{ // static
	DviDeviceStandardC* self = reinterpret_cast<DviDeviceStandardC*>(aPtr);
	self->iResourceWriter->WriteResource(aData, aBytes);
}

void DviDeviceC::WriteResourceEnd(void* aPtr)
{ // static
	DviDeviceStandardC* self = reinterpret_cast<DviDeviceStandardC*>(aPtr);
	self->iResourceWriter->WriteResourceEnd();
}


// DviDeviceStandardC

DviDeviceStandardC::DviDeviceStandardC(const char* aUdn)
{
	Brn udn(aUdn);
	iDevice = new DvDeviceStandard(udn);
}

DviDeviceStandardC::DviDeviceStandardC(const char* aUdn, OhNetCallbackResourceManager aResourceManager, void* aPtr)
{
	Brn udn(aUdn);
	iDevice = new DvDeviceStandard(udn, *this);
	iResourceManager = aResourceManager;
	iCallbackArg = aPtr;
	iResourceWriter = NULL;
}


// C APIs

DvDeviceC DvDeviceCreate(const char* aUdn)
{
	DviDeviceC* wrapper = new DviDeviceC(aUdn);
	return (DvDeviceC)wrapper;
}

void DvDeviceDestroy(DvDeviceC aDevice)
{
	delete (DviDeviceC*)aDevice;
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

void DvDeviceSetDisabled(DvDeviceC aDevice, OhNetCallback aCompleted, void* aPtr)
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

void DvDeviceSetXmlExtension(DvDeviceC aDevice, const char* aXml)
{
	DviDeviceC::DeviceFromHandle(aDevice)->SetXmlExtension(aXml);
}

DvDeviceC DvDeviceStandardCreateNoResources(const char* aUdn)
{
	DviDeviceStandardC* wrapper = new DviDeviceStandardC(aUdn);
	return (DvDeviceC)wrapper;
}

DvDeviceC DvDeviceStandardCreate(const char* aUdn, OhNetCallbackResourceManager aResourceManager, void* aPtr)
{
	DviDeviceStandardC* wrapper = new DviDeviceStandardC(aUdn, aResourceManager, aPtr);
	return (DvDeviceC)wrapper;
}

uint32_t DvResourceWriterLanguageCount(THandle aLanguageList)
{
    std::vector<char*>* list = reinterpret_cast<std::vector<char*>*>(aLanguageList);
    ASSERT(list != NULL);
    return (uint32_t)list->size();
}

const char* DvResourceWriterLanguage(THandle aLanguageList, uint32_t aIndex)
{
    std::vector<char*>* list = reinterpret_cast<std::vector<char*>*>(aLanguageList);
    ASSERT(list != NULL);
    ASSERT(aIndex < (uint32_t)list->size());
    return (*list)[aIndex];
}
