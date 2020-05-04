#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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


// AutoRefCpDevice

AutoRefCpDevice::AutoRefCpDevice(CpDevice& aDevice)
    : iDevice(aDevice)
{
}

AutoRefCpDevice::~AutoRefCpDevice()
{
    iDevice.RemoveRef();
}


// CpDeviceList

CpDeviceList::~CpDeviceList()
{
    iLock->Wait();
    iActive = false;
    iLock->Signal();
    delete iList;
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        it->second->RemoveRef();
        it++;
    }
    iMap.clear();
    delete iLock;
}

void CpDeviceList::Refresh()
{
    iList->Refresh();
}

CpDeviceList::CpDeviceList(FunctorCpDevice aAdded, FunctorCpDevice aRemoved)
    : iAdded(aAdded)
    , iRemoved(aRemoved)
    , iActive(true)
{
    iLock = new Mutex("DLCM");
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
    if (!LockIfActive()) {
        return;
    }
    CpDevice* device = new CpDevice(aDevice);
    /* No mutex used for Added or Removed as we assume the underlying list's
       lock already protects us */
    Brn udn(device->Udn());
    iMap.insert(std::pair<Brn,CpDevice*>(udn, device));
    iLock->Signal();
    iAdded(*device);
}

void CpDeviceList::Removed(CpiDevice& aDevice)
{
    if (!LockIfActive()) {
        return;
    }
    Brn udn(aDevice.Udn());
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        iLock->Signal();
    }
    else {
        CpDevice* device = it->second;
        iMap.erase(it);
        iLock->Signal();
        try {
            iRemoved(*device);
        }
        catch (...) {
            ASSERTS();
        }
        device->RemoveRef();
    }
}

TBool CpDeviceList::LockIfActive()
{
    iLock->Wait();
    if (iActive) {
        return true;
    }
    iLock->Signal();
    return false;
}
