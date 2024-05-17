#include <OpenHome/Net/C/DvDevice.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include "DviDeviceC.h"
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/Os.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviDeviceC

DviDeviceC::DviDeviceC(const char* aUdn)
{
    Brn udn(aUdn);
    iDevice = new DvDevice(*gDvStack, udn);
    iResourceManager = NULL;
    iCallbackArg = NULL;
}

DviDeviceC::DviDeviceC()
{
    iResourceManager = NULL;
    iCallbackArg = NULL;
}

DviDeviceC::~DviDeviceC()
{
    delete iDevice;
}

DvDevice* DviDeviceC::Device()
{
    return iDevice;
}

void DviDeviceC::WriteResource(const Brx& aUriTail, const TIpAddress& aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
    ASSERT(iResourceManager != NULL);
    Brhz uriTail(aUriTail);
    int32_t err = iResourceManager(iCallbackArg, uriTail.CString(), aInterface.iV4, &aLanguageList, &aResourceWriter, WriteResourceBegin, WriteResource, WriteResourceEnd);
    if (err != 0) {
        THROW(WriterError);
    }
}

int32_t STDCALL DviDeviceC::WriteResourceBegin(void* aPtr, uint32_t aTotalBytes, const char* aMimeType)
{ // static
    IResourceWriter* writer = reinterpret_cast<IResourceWriter*>(aPtr);
    ASSERT(writer != NULL);
    try {
        writer->WriteResourceBegin(aTotalBytes, aMimeType);
    }
    catch (AssertionFailed& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (...) {
        return -1;
    }
    return 0;
}

int32_t STDCALL DviDeviceC::WriteResource(void* aPtr, const uint8_t* aData, uint32_t aBytes)
{ // static
    IResourceWriter* writer = reinterpret_cast<IResourceWriter*>(aPtr);
    ASSERT(writer != NULL);
    try {
        writer->WriteResource(aData, aBytes);
    }
    catch (AssertionFailed& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (...) {
        return -1;
    }
    return 0;
}

int32_t STDCALL DviDeviceC::WriteResourceEnd(void* aPtr)
{ // static
    IResourceWriter* writer = reinterpret_cast<IResourceWriter*>(aPtr);
    ASSERT(writer != NULL);
    try {
        writer->WriteResourceEnd();
    }
    catch (AssertionFailed& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (...) {
        return -1;
    }
    return 0;
}


// DviDeviceStandardC

DviDeviceStandardC::DviDeviceStandardC(const char* aUdn)
{
    Brn udn(aUdn);
    iDevice = new DvDeviceStandard(*gDvStack, udn);
}

DviDeviceStandardC::DviDeviceStandardC(const char* aUdn, OhNetCallbackResourceManager aResourceManager, void* aPtr)
{
    Brn udn(aUdn);
    iDevice = new DvDeviceStandard(*gDvStack, udn, *this);
    iResourceManager = aResourceManager;
    iCallbackArg = aPtr;
}


// C APIs

DvDeviceC STDCALL DvDeviceCreate(const char* aUdn)
{
    try {
        DviDeviceC* wrapper = new DviDeviceC(aUdn);
        return (DvDeviceC)wrapper;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

void STDCALL DvDeviceDestroy(DvDeviceC aDevice)
{
    try {
        delete (DviDeviceC*)aDevice;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

const char* STDCALL DvDeviceUdn(DvDeviceC aDevice)
{
    try {
        return (const char*)DviDeviceC::DeviceFromHandle(aDevice)->Udn().Ptr();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return NULL;
}

void STDCALL DvDeviceGetUdn(DvDeviceC aDevice, const char** aUdn, uint32_t* aLen)
{
    try {
        Brn udn(DviDeviceC::DeviceFromHandle(aDevice)->Udn());
        if (udn.Bytes() == 0) {
            *aUdn = NULL;
            *aLen = 0;
        }
        else {
            *aUdn = (const char*)udn.Ptr();
            *aLen = udn.Bytes();
        }
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

int32_t STDCALL DvDeviceEnabled(DvDeviceC aDevice)
{
    try {
        return (DviDeviceC::DeviceFromHandle(aDevice)->Enabled()? 1 : 0);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

void STDCALL DvDeviceSetEnabled(DvDeviceC aDevice)
{
    try {
        DviDeviceC::DeviceFromHandle(aDevice)->SetEnabled();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvDeviceSetDisabled(DvDeviceC aDevice, OhNetCallback aCompleted, void* aPtr)
{
    try {
        Functor completed = MakeFunctor(aPtr, aCompleted);
        DviDeviceC::DeviceFromHandle(aDevice)->SetDisabled(completed);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvDeviceGetAttribute(DvDeviceC aDevice, const char* aKey, const char** aValue)
{
    try {
        DviDeviceC::DeviceFromHandle(aDevice)->GetAttribute(aKey, aValue);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

void STDCALL DvDeviceSetAttribute(DvDeviceC aDevice, const char* aKey, const char* aValue)
{
    try {
        DviDeviceC::DeviceFromHandle(aDevice)->SetAttribute(aKey, aValue);
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

DvDeviceC STDCALL DvDeviceStandardCreateNoResources(const char* aUdn)
{
    try {
        DviDeviceStandardC* wrapper = new DviDeviceStandardC(aUdn);
        return (DvDeviceC)wrapper;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

char* STDCALL DvDeviceStandardResourceManagerUri(DvDeviceC aDevice, THandle aAdapter)
{
    try {
        Brh uri;
        NetworkAdapter* nif = (NetworkAdapter*)aAdapter;
        ASSERT(nif != NULL);
        reinterpret_cast<DvDeviceStandard*>(DviDeviceC::DeviceFromHandle(aDevice))->GetResourceManagerUri(*nif, uri);
        if (uri.Bytes() == 0) {
            return NULL;
        }
        else {
            Brhz uriz(uri);
            return (char*)uriz.Transfer();
        }
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return NULL;
}

void STDCALL DvDeviceStandardGetResourceManagerUri(DvDeviceC aDevice, THandle aAdapter, char** aUri, uint32_t* aLen)
{
    try {
        Brh uri;
        NetworkAdapter* nif = (NetworkAdapter*)aAdapter;
        ASSERT(nif != NULL);
        reinterpret_cast<DvDeviceStandard*>(DviDeviceC::DeviceFromHandle(aDevice))->GetResourceManagerUri(*nif, uri);
        if (uri.Bytes() == 0) {
            *aUri = NULL;
            *aLen = 0;
        }
        else {
            *aLen = uri.Bytes();
            *aUri = (char*)uri.Extract();
        }
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
}

DvDeviceC STDCALL DvDeviceStandardCreate(const char* aUdn, OhNetCallbackResourceManager aResourceManager, void* aPtr)
{
    try {
        DviDeviceStandardC* wrapper = new DviDeviceStandardC(aUdn, aResourceManager, aPtr);
        return (DvDeviceC)wrapper;
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return kHandleNull;
}

uint32_t STDCALL DvResourceWriterLanguageCount(THandle aLanguageList)
{
    try {
        std::vector<char*>* list = reinterpret_cast<std::vector<char*>*>(aLanguageList);
        ASSERT(list != NULL);
        return (uint32_t)list->size();
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return 0;
}

const char* STDCALL DvResourceWriterLanguage(THandle aLanguageList, uint32_t aIndex)
{
    try {
        std::vector<char*>* list = reinterpret_cast<std::vector<char*>*>(aLanguageList);
        ASSERT(list != NULL);
        ASSERT(aIndex < (uint32_t)list->size());
        return (*list)[aIndex];
    }
    catch (Exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    catch (std::exception& ex) {
        UnhandledExceptionHandler(ex);
    }
    return NULL;
}
