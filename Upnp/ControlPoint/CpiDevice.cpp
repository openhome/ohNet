#include <CpiDevice.h>
#include <Thread.h>
#include <Debug.h>
#include <ZappTypes.h>

using namespace Zapp;

// CpiDevice

const Brx& CpiDevice::Udn() const
{
    return iUdn;
}

const TChar* CpiDevice::UdnAsCString() const
{
    return iUdn.CString();
}

TBool CpiDevice::operator==(const CpiDevice& aDevice) const
{
    return (&aDevice == this);
}

TBool CpiDevice::operator!=(const CpiDevice& aDevice) const
{
    return (&aDevice != this);
}

void CpiDevice::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void CpiDevice::RemoveRef()
{
    TBool dead;
    iLock.Wait();
    dead = (--iRefCount <= 0);
    iLock.Signal();
    if (dead) {
        delete this;
    }
}

void CpiDevice::SetReady()
{
    iReady = true;
}

TBool CpiDevice::IsReady() const
{
    return iReady;
}

void CpiDevice::SetExpired(TBool aExpired)
{
    iExpired = aExpired;
}

TBool CpiDevice::HasExpired() const
{
    return iExpired;
}

CpiDevice::CpiDevice(const Brx& aUdn)
    : iUdn(aUdn)
    , iLock("CDVM")
    , iRefCount(1)
    , iReady(false)
    , iExpired(false)
{
}

CpiDevice::~CpiDevice()
{
    LOG(kDevice, "~CpiDevice for device ");
    LOG(kDevice, iUdn);
    LOG(kDevice, "\n");
    ASSERT(iRefCount == 0);
}


// CpiDeviceList

void CpiDeviceList::Refresh()
{
}

CpiDevice* CpiDeviceList::RefDevice(const Brx& aUdn)
{
    AutoMutex a(iLock);
    return RefDeviceLocked(aUdn);
}

CpiDevice* CpiDeviceList::RefDeviceLocked(const Brx& aUdn)
{
    Brn udn(aUdn);
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        return NULL;
    }
    CpiDevice* device = it->second;
    device->AddRef();
    return device;
}

CpiDeviceList::CpiDeviceList(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : iActive(false)
    , iRefreshing(false)
    , iLock("CDLM")
    , iAdded(aAdded)
    , iRemoved(aRemoved)
{
    ASSERT(iAdded);
    ASSERT(iRemoved);
}

CpiDeviceList::~CpiDeviceList()
{
    ClearMap(iMap);
    ClearMap(iRefreshMap);
}

void CpiDeviceList::Add(CpiDevice* aDevice)
{
    LOG(kDevice, "CpiDeviceList::Add for device ");
    LOG(kDevice, aDevice->Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    if (aDevice->HasExpired() || !iActive) {
        LOG(kDevice, "< CpiDeviceList::Add, device expired or list stopped\n");
        aDevice->RemoveRef();
        iLock.Signal();
        return;
    }
    if (iRefreshing) {
        Brn udn(aDevice->Udn());
        Map::iterator it = iRefreshMap.find(udn);
        if (it == iRefreshMap.end()) {
            iRefreshMap.insert(std::pair<Brn,CpiDevice*>(udn, aDevice));
            aDevice->AddRef(); // for refresh list
        }
    }
    CpiDevice* tmp = RefDeviceLocked(aDevice->Udn());
    if (tmp != NULL) {
        // device is already in the list, ignore this call to Add()
        LOG(kDevice, "< CpiDeviceList::Add, device already in list\n");
        tmp->RemoveRef();
        aDevice->RemoveRef();
        iLock.Signal();
        return;
    }
    Brn udn(aDevice->Udn());
    iMap.insert(std::pair<Brn,CpiDevice*>(udn, aDevice));
    aDevice->AddRef(); // for observer
    iLock.Signal();
    if (IsDeviceReady(*aDevice)) {
        SetDeviceReady(*aDevice);
    }
    aDevice->RemoveRef(); // observer's ref
}

void CpiDeviceList::Remove(const Brx& aUdn)
{
    LOG(kDevice, "> CpiDeviceList::Remove for device ");
    LOG(kDevice, aUdn);
    LOG(kDevice, "\n");
    iLock.Wait();
    if (!iActive) {
        LOG(kDevice, "< CpiDeviceList::Remove, list not active\n");
        iLock.Signal();
        return;
    }
    TBool callObserver;
    Brn udn(aUdn);
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        // device isn't in this list
        LOG(kDevice, "< CpiDeviceList::Remove, device not in list\n");
        iLock.Signal();
        return;
    }
    CpiDevice* device = it->second;
    // don't remove our ref to the device yet, re-use it for the observer
    callObserver = device->IsReady();
    it->second = NULL;
    iMap.erase(it);
    iLock.Signal();
    if (callObserver) {
        iRemoved(*device);
    }
    device->RemoveRef();
}

TBool CpiDeviceList::IsDeviceReady(CpiDevice& /*aDevice*/)
{
    return true;
}

TBool CpiDeviceList::StartRefresh()
{
    TBool refreshAlreadyInProgress;
    iLock.Wait();
    refreshAlreadyInProgress = iRefreshing;
    iRefreshing = true;
    iLock.Signal();
    return refreshAlreadyInProgress;
}

void CpiDeviceList::RefreshComplete()
{
    iLock.Wait();
    iRefreshing = false;
    if (iActive) {
        /* map iterator is invalidated by removing an item so we'll need to iterate once per removal
           assume that the 0.5 * O(n^2) ish cost is bearable as refresh is a rare operation which
           can only feasibly run once ever few seconds in the worst possible case */
        Map::iterator it = iMap.begin();
        while (it != iMap.end()) {
            Map::iterator found = iRefreshMap.find(it->first);
            if (found != iRefreshMap.end()) {
                // device still exists
                it++;
            }
            else {
                CpiDevice* device = it->second;
                device->AddRef();
                iLock.Signal();
                Remove(device->Udn());
                device->RemoveRef();
                iLock.Wait();
                it = iMap.begin();
            }
        }
    }
    ClearMap(iRefreshMap);
    iLock.Signal();
}

void CpiDeviceList::SetDeviceReady(CpiDevice& aDevice)
{
    LOG(kDevice, "CpiDeviceList::SetDeviceReady for device ");
    LOG(kDevice, aDevice.Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    if (!iActive) {
        iLock.Signal();
        return;
    }
    aDevice.SetReady();
    iLock.Signal();
    iAdded(aDevice);
}

void CpiDeviceList::ClearMap(Map& aMap)
{
    Map::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second->RemoveRef();
        it->second = NULL;
        it++;
    }
    aMap.clear();
}
