#include <OpenHome/Net/C/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <stdlib.h>
#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Net;

const char* STDCALL CpDeviceCUdn(CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    return (const char*)device->Udn().Ptr();
}

void STDCALL CpDeviceCGetUdn(CpDeviceC aDevice, const char** aUdn, uint32_t* aLen)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    Brn udn(device->Udn());
    if (udn.Bytes() == 0) {
        *aUdn = NULL;
        *aLen = 0;
    }
    else {
        *aUdn = (const char*)udn.Ptr();
        *aLen = udn.Bytes();
    }
}

void STDCALL CpDeviceCAddRef(CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    device->AddRef();
}

void STDCALL CpDeviceCRemoveRef(CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    device->RemoveRef();
}

int32_t STDCALL CpDeviceCGetAttribute(CpDeviceC aDevice, const char* aKey, char** aValue)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    Brh val;
    ASSERT(device != NULL);
    if (device->GetAttribute(aKey, val)) {
        TUint len = val.Bytes();
        *aValue = (char*)malloc(len+1);
        (void)memcpy(*aValue, val.Ptr(), len);
        (*aValue)[len] = '\0';
        return 1;
    }
    return 0;
}

void STDCALL CpDeviceListDestroy(HandleCpDeviceList aListHandle)
{
    CpiDeviceList* list = reinterpret_cast<CpiDeviceList*>(aListHandle);
    delete list;
}

void STDCALL CpDeviceListRefresh(HandleCpDeviceList aListHandle)
{
    CpiDeviceList* list = reinterpret_cast<CpiDeviceList*>(aListHandle);
    ASSERT(list != NULL);
    list->Refresh();
}
