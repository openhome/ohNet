#include <Core/CpDevice.h>
#include <CpiDevice.h>

using namespace Zapp;

// CpDevice

const Brx& CpDevice::Udn() const
{
    return iDevice.Udn();
}

TBool CpDevice::operator==(const CpDevice& aDevice) const
{
    return iDevice==aDevice.iDevice;
}

TBool CpDevice::operator!=(const CpDevice& aDevice) const
{
    return iDevice!=aDevice.iDevice;
}

void CpDevice::AddRef()
{
    iRefCount++;
    iDevice.AddRef();
}

void CpDevice::RemoveRef()
{
    iDevice.RemoveRef();
    if (--iRefCount == 0) {
        delete this;
    }
}

TBool CpDevice::GetAttribute(const char* aKey, Brh& aValue) const
{
    return iDevice.GetAttribute(aKey, aValue);
}

CpiDevice& CpDevice::Device()
{
    return iDevice;
}

CpDevice::CpDevice(CpiDevice& aDevice)
    : iDevice(aDevice)
    , iRefCount(1)
{
    iDevice.AddRef();
}

CpDevice::~CpDevice()
{
}


// CpDeviceList

CpDeviceList::~CpDeviceList()
{
    delete iList;
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        it->second->RemoveRef();
        it++;
    }
    iMap.clear();
}

void CpDeviceList::Refresh()
{
    iList->Refresh();
}

CpDeviceList::CpDeviceList(FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : iAdded(aAdded)
    , iRemoved(aRemoved)
{
    ASSERT(iAdded);
    ASSERT(iRemoved);
}

void CpDeviceList::GetAddedFunctor(FunctorCpiDevice& aFunctor)
{
    aFunctor = MakeFunctorCpiDevice(*this, &CpDeviceList::Added);
}

void CpDeviceList::GetRemovedFunctor(FunctorCpiDevice& aFunctor)
{
    aFunctor = MakeFunctorCpiDevice(*this, &CpDeviceList::Removed);
}

void CpDeviceList::Added(CpiDevice& aDevice)
{
    CpDevice* device = new CpDevice(aDevice);
    /* No mutex used for Added or Removed as we assume the underlying list's
       lock already protects us */
    Brn udn(device->Udn());
    iMap.insert(std::pair<Brn,CpDevice*>(udn, device));
    iAdded(*device);
}

void CpDeviceList::Removed(CpiDevice& aDevice)
{
    Brn udn(aDevice.Udn());
    Map::iterator it = iMap.find(udn);
    if (it != iMap.end()) {
        CpDevice* device = it->second;
        iRemoved(*device);
        device->RemoveRef();
        iMap.erase(it);
    }
}
