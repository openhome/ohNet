#include <C/CpDevice.h>
#include <CpiDevice.h>

#include <stdlib.h>
#include <string.h>

using namespace Zapp;

const char* CpDeviceCUdn(CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    return (const char*)device->Udn().Ptr();
}

void CpDeviceCAddRef(CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    device->AddRef();
}

void CpDeviceCRemoveRef(CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    device->RemoveRef();
}

int32_t CpDeviceCGetAttribute(CpDeviceC aDevice, const char* aKey, char** aValue)
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

void CpDeviceListDestroy(HandleCpDeviceList aListHandle)
{
    CpiDeviceList* list = reinterpret_cast<CpiDeviceList*>(aListHandle);
    delete list;
}

void CpDeviceListRefresh(HandleCpDeviceList aListHandle)
{
    CpiDeviceList* list = reinterpret_cast<CpiDeviceList*>(aListHandle);
    ASSERT(list != NULL);
    list->Refresh();
}
