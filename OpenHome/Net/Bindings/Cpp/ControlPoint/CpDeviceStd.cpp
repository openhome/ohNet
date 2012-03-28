#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpDevice

const std::string& CpDeviceCpp::Udn() const
{
    return iUdn;
}

TBool CpDeviceCpp::operator==(const CpDeviceCpp& aDevice) const
{
    return iDevice==aDevice.iDevice;
}

TBool CpDeviceCpp::operator!=(const CpDeviceCpp& aDevice) const
{
    return iDevice!=aDevice.iDevice;
}

void CpDeviceCpp::AddRef()
{
    iRefCount++;
    iDevice.AddRef();
}

void CpDeviceCpp::RemoveRef()
{
    iDevice.RemoveRef();
    if (--iRefCount == 0) {
        delete this;
    }
}

TBool CpDeviceCpp::GetAttribute(const char* aKey, std::string& aValue) const
{
    Brh val;
    aValue.erase(aValue.begin(), aValue.end());
    if (iDevice.GetAttribute(aKey, val)) {
        aValue.append((const char*)val.Ptr(), val.Bytes());
        return true;
    }
    return false;
}

CpiDevice& CpDeviceCpp::Device()
{
    return iDevice;
}

CpDeviceCpp::CpDeviceCpp(CpiDevice& aDevice)
    : iDevice(aDevice)
    , iUdn((const char*)aDevice.Udn().Ptr(), aDevice.Udn().Bytes())
    , iRefCount(1)
{
    iDevice.AddRef();
}

CpDeviceCpp::~CpDeviceCpp()
{
}


// CpDeviceListCpp

CpDeviceListCpp::~CpDeviceListCpp()
{
    iLock->Wait();
    iActive = false;
    iLock->Signal();
    delete iList;
    delete iLock;
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        it->second->RemoveRef();
        it++;
    }
    iMap.clear();
}

void CpDeviceListCpp::Refresh()
{
    iList->Refresh();
}

CpDeviceListCpp::CpDeviceListCpp(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved)
    : iAdded(aAdded)
    , iRemoved(aRemoved)
    , iActive(true)
{
    iLock = new Mutex("DLCM");
    ASSERT(iAdded);
    ASSERT(iRemoved);
}

void CpDeviceListCpp::GetAddedFunctor(FunctorCpiDevice& aFunctor)
{
    aFunctor = MakeFunctorCpiDevice(*this, &CpDeviceListCpp::Added);
}

void CpDeviceListCpp::GetRemovedFunctor(FunctorCpiDevice& aFunctor)
{
    aFunctor = MakeFunctorCpiDevice(*this, &CpDeviceListCpp::Removed);
}

void CpDeviceListCpp::Added(CpiDevice& aDevice)
{
    if (!LockIfActive()) {
        return;
    }
    CpDeviceCpp* device = new CpDeviceCpp(aDevice);
    /* No mutex used for Added or Removed as we assume the underlying list's
       lock already protects us */
    Brn udn(device->Udn().c_str());
    iMap.insert(std::pair<Brn,CpDeviceCpp*>(udn, device));
    iLock->Signal();
    iAdded(*device);
}

void CpDeviceListCpp::Removed(CpiDevice& aDevice)
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
        CpDeviceCpp* device = it->second;
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

TBool CpDeviceListCpp::LockIfActive()
{
    iLock->Wait();
    if (iActive) {
        return true;
    }
    iLock->Signal();
    return false;
}
