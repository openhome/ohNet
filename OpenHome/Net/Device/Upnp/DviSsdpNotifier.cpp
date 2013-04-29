#include <OpenHome/Net/Private/DviSsdpNotifier.h>
#include <OpenHome/Net/Private/DviProtocolUpnp.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// SsdpNotifierScheduler

SsdpNotifierScheduler::~SsdpNotifierScheduler()
{
}

SsdpNotifierScheduler::SsdpNotifierScheduler(DvStack& aDvStack, ISsdpNotifyListener& aListener)
    : iDvStack(aDvStack)
    , iListener(aListener)
{
    Functor functor = MakeFunctor(*this, &SsdpNotifierScheduler::SendNextMsg);
    iTimer = new Timer(iDvStack.Env(), functor);
}

void SsdpNotifierScheduler::Start(TUint aDuration, TUint aMsgCount)
{
    iStop = false;
    iEndTimeMs = Os::TimeInMs(iDvStack.Env().OsCtx()) + aDuration;
    ScheduleNextTimer(aMsgCount);
}

void SsdpNotifierScheduler::Stop()
{
    iStop = true;
}

void SsdpNotifierScheduler::NotifyComplete()
{
}

void SsdpNotifierScheduler::SendNextMsg()
{
    TUint remaining = 0;
    TBool stop = true;
    try {
        stop = (iStop || (remaining = NextMsg()) == 0);
    }
    catch (WriterError&) {}
    catch (NetworkError&) {}
    if (stop) {
        NotifyComplete();
        iListener.NotifySchedulerComplete(this);
        return;
    }
    else {
        ScheduleNextTimer(remaining);
    }
}

void SsdpNotifierScheduler::ScheduleNextTimer(TUint aRemainingMsgs) const
{
    TUint interval;
    TInt remaining = iEndTimeMs - Os::TimeInMs(iDvStack.Env().OsCtx());
    TInt maxUpdateTimeMs = (TInt)iDvStack.Env().InitParams().DvMaxUpdateTimeSecs() * 1000;
    ASSERT(remaining <= maxUpdateTimeMs);
    TInt maxInterval = remaining / (TInt)aRemainingMsgs;
    if (maxInterval < kMinTimerIntervalMs) {
        // we're running behind.  Schedule another timer to run immediately
        interval = 0;
    }
    else {
        interval = Random((TUint)maxInterval);
    }
    iTimer->FireIn(interval);
}


// MsearchResponse

#define NEXT_MSG_ROOT         (0)
#define NEXT_MSG_UUID         (1)
#define NEXT_MSG_DEVICE_TYPE  (2)
#define NEXT_MSG_SERVICE_TYPE (3)

MsearchResponse::MsearchResponse(DvStack& aDvStack, ISsdpNotifyListener& aListener)
    : SsdpNotifierScheduler(aDvStack, aListener)
    , iAnnouncementData(NULL)
{
    iNotifier = new SsdpMsearchResponder(aDvStack);
}

void MsearchResponse::StartAll(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    TUint nextMsgIndex = NEXT_MSG_ROOT;
    TUint msgCount = 3 + aAnnouncementData.ServiceCount();
    if (!aAnnouncementData.IsRoot()) {
        msgCount--;
        nextMsgIndex = NEXT_MSG_UUID;
    }
    Start(aAnnouncementData, msgCount, nextMsgIndex, aRemote, aMx, aUri, aConfigId);
}

void MsearchResponse::StartRoot(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    Start(aAnnouncementData, 1, NEXT_MSG_ROOT, aRemote, aMx, aUri, aConfigId);
}

void MsearchResponse::StartUuid(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    Start(aAnnouncementData, 1, NEXT_MSG_UUID, aRemote, aMx, aUri, aConfigId);
}

void MsearchResponse::StartDeviceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    Start(aAnnouncementData, 1, NEXT_MSG_DEVICE_TYPE, aRemote, aMx, aUri, aConfigId);
}

void MsearchResponse::StartServiceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const OpenHome::Net::ServiceType& aServiceType, const Brx& aUri, TUint aConfigId)
{
    TUint index = 0;
    for (;;) {
        const OpenHome::Net::ServiceType& st = aAnnouncementData.Service(index).ServiceType();
        if (st.Domain() == aServiceType.Domain() && st.Name() == aServiceType.Name() && st.Version() == aServiceType.Version()) {
            break;
        }
        index++;
    }
    Start(aAnnouncementData, 1, NEXT_MSG_SERVICE_TYPE + index, aRemote, aMx, aUri, aConfigId);
}

void MsearchResponse::Start(IUpnpAnnouncementData& aAnnouncementData, TUint aTotalMsgs, TUint aNextMsgIndex, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    iAnnouncementData = &aAnnouncementData;
    iNextMsgIndex = aNextMsgIndex;
    iRemainingMsgs = aTotalMsgs;
    static_cast<SsdpMsearchResponder*>(iNotifier)->SetRemote(aRemote, aConfigId);
    iUri.Replace(aUri);
    SsdpNotifierScheduler::Start(aMx, iRemainingMsgs);
}

TUint MsearchResponse::NextMsg()
{
    switch (iNextMsgIndex)
    {
    case 0:
        iNotifier->SsdpNotifyRoot(iAnnouncementData->Udn(), iUri);
        break;
    case 1:
        iNotifier->SsdpNotifyUuid(iAnnouncementData->Udn(), iUri);
        break;
    case 2:
        iNotifier->SsdpNotifyDeviceType(iAnnouncementData->Domain(), iAnnouncementData->Type(), iAnnouncementData->Version(), iAnnouncementData->Udn(), iUri);
        break;
    default:
        DviService& service = iAnnouncementData->Service(iNextMsgIndex - 3);
        const OpenHome::Net::ServiceType& serviceType = service.ServiceType();
        iNotifier->SsdpNotifyServiceType(serviceType.Domain(), serviceType.Name(), serviceType.Version(), iAnnouncementData->Udn(), iUri);
        break;
    }
    iNextMsgIndex++;
    return --iRemainingMsgs;
}


// DeviceAnnouncement

DeviceAnnouncement::DeviceAnnouncement(DvStack& aDvStack, ISsdpNotifyListener& aListener)
    : SsdpNotifierScheduler(aDvStack, aListener)
    , iSsdpNotifier(aDvStack)
    , iNotifierAlive(iSsdpNotifier)
    , iNotifierByeBye(iSsdpNotifier)
    , iNotifierUpdate(iSsdpNotifier)
    , iCurrentNotifier(NULL)
{
}

void DeviceAnnouncement::StartAlive(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId)
{
    iCompleted = Functor();
    Start(iNotifierAlive, aAnnouncementData, aAdapter, aUri, aConfigId, kMsgIntervalMsAlive);
}

void DeviceAnnouncement::StartByeBye(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, Functor& aCompleted)
{
    iCompleted = aCompleted;
    Start(iNotifierByeBye, aAnnouncementData, aAdapter, aUri, aConfigId, kMsgIntervalMsByeBye);
}

void DeviceAnnouncement::StartUpdate(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, Functor& aCompleted)
{
    iCompleted = aCompleted;
    Start(iNotifierUpdate, aAnnouncementData, aAdapter, aUri, aConfigId, kMsgIntervalMsUpdate);
}

void DeviceAnnouncement::Start(ISsdpNotify& aNotifier, IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, TUint aMsgInterval)
{
    iCurrentNotifier = &aNotifier;
    iAnnouncementData = &aAnnouncementData;
    iNextMsgIndex = (iAnnouncementData->IsRoot()? 0 : 1);
    iTotalMsgs = 3 + iAnnouncementData->ServiceCount();
    iSsdpNotifier.Start(aAdapter, aConfigId);
    iUri.Replace(aUri);
    SsdpNotifierScheduler::Start(aMsgInterval * iTotalMsgs, iTotalMsgs);
}

TUint DeviceAnnouncement::NextMsg()
{
    switch (iNextMsgIndex)
    {
    case 0:
        iCurrentNotifier->SsdpNotifyRoot(iAnnouncementData->Udn(), iUri);
        break;
    case 1:
        iCurrentNotifier->SsdpNotifyUuid(iAnnouncementData->Udn(), iUri);
        break;
    case 2:
        iCurrentNotifier->SsdpNotifyDeviceType(iAnnouncementData->Domain(), iAnnouncementData->Type(), iAnnouncementData->Version(), iAnnouncementData->Udn(), iUri);
        break;
    default:
        DviService& service = iAnnouncementData->Service(iNextMsgIndex - 3);
        const OpenHome::Net::ServiceType& serviceType = service.ServiceType();
        iCurrentNotifier->SsdpNotifyServiceType(serviceType.Domain(), serviceType.Name(), serviceType.Version(), iAnnouncementData->Udn(), iUri);
        break;
    }
    iNextMsgIndex++;
    return (iTotalMsgs - iNextMsgIndex);
}

void DeviceAnnouncement::NotifyComplete()
{
    if (iCompleted) {
        iCompleted();
    }
}


// DviDiscoveryManager

DviDiscoveryManager::DviDiscoveryManager(DvStack& aDvStack)
    : iDvStack(aDvStack)
    , iLock("DVDM")
    , iShutdownSem("DVDM", 1)
{
}

DviDiscoveryManager::~DviDiscoveryManager()
{
    iShutdownSem.Wait();
    
    // nasty way of ensuring NotifySchedulerComplete has released iLock
    iLock.Wait();
    iLock.Signal();

    ASSERT(iActiveResponders.size() == 0);
    ASSERT(iActiveAnnouncers.size() == 0);
    Delete(iFreeResponders);
    Delete(iFreeAnnouncers);
}

void DviDiscoveryManager::AnnouncementAlive(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId)
{
    AutoMutex a(iLock);
    Announcer* announcer = GetAnnouncer();
    if (announcer != NULL) {
        SetActive(announcer, aAnnouncementData);
        announcer->Announcement().StartAlive(aAnnouncementData, aAdapter, aUri, aConfigId);
    }
}

void DviDiscoveryManager::AnnouncementByeBye(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, Functor& aCompleted)
{
    AutoMutex a(iLock);
    Announcer* announcer = GetAnnouncer();
    if (announcer != NULL) {
        SetActive(announcer, aAnnouncementData);
        announcer->Announcement().StartByeBye(aAnnouncementData, aAdapter, aUri, aConfigId, aCompleted);
    }
}

void DviDiscoveryManager::AnnouncementUpdate(IUpnpAnnouncementData& aAnnouncementData, TIpAddress aAdapter, const Brx& aUri, TUint aConfigId, Functor& aCompleted)
{
    AutoMutex a(iLock);
    Announcer* announcer = GetAnnouncer();
    if (announcer != NULL) {
        SetActive(announcer, aAnnouncementData);
        announcer->Announcement().StartUpdate(aAnnouncementData, aAdapter, aUri, aConfigId, aCompleted);
    }
}

void DviDiscoveryManager::MsearchResponseAll(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    AutoMutex a(iLock);
    Responder* responder = GetResponder();
    SetActive(responder, aAnnouncementData);
    responder->Response().StartAll(aAnnouncementData, aRemote, aMx, aUri, aConfigId);
}

void DviDiscoveryManager::MsearchResponseRoot(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    AutoMutex a(iLock);
    Responder* responder = GetResponder();
    SetActive(responder, aAnnouncementData);
    responder->Response().StartRoot(aAnnouncementData, aRemote, aMx, aUri, aConfigId);
}

void DviDiscoveryManager::MsearchResponseUuid(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    AutoMutex a(iLock);
    Responder* responder = GetResponder();
    SetActive(responder, aAnnouncementData);
    responder->Response().StartUuid(aAnnouncementData, aRemote, aMx, aUri, aConfigId);
}

void DviDiscoveryManager::MsearchResponseDeviceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const Brx& aUri, TUint aConfigId)
{
    AutoMutex a(iLock);
    Responder* responder = GetResponder();
    SetActive(responder, aAnnouncementData);
    responder->Response().StartDeviceType(aAnnouncementData, aRemote, aMx, aUri, aConfigId);
}

void DviDiscoveryManager::MsearchResponseServiceType(IUpnpAnnouncementData& aAnnouncementData, const Endpoint& aRemote, TUint aMx, const OpenHome::Net::ServiceType& aServiceType, const Brx& aUri, TUint aConfigId)
{
    AutoMutex a(iLock);
    Responder* responder = GetResponder();
    SetActive(responder, aAnnouncementData);
    responder->Response().StartServiceType(aAnnouncementData, aRemote, aMx, aServiceType, aUri, aConfigId);
}

void DviDiscoveryManager::Stop(const Brx& aUdn)
{
    iLock.Wait();
    Stop(iActiveResponders, aUdn);
    Stop(iActiveAnnouncers, aUdn);
    iLock.Signal();
}

void DviDiscoveryManager::Stop(std::list<Notifier*>& aList, const Brx& aUdn)
{
    std::list<Notifier*>::iterator it = aList.begin();
    while (it != aList.end()) {
        if ((*it)->MatchesDevice(aUdn)) {
            (*it)->Scheduler()->Stop();
        }
        it++;
    }
}

void DviDiscoveryManager::Delete(std::list<Notifier*>& aList)
{
    std::list<Notifier*>::iterator it = aList.begin();
    while (it != aList.end()) {
        delete *it;
        it++;
    }
}

DviDiscoveryManager::Responder* DviDiscoveryManager::GetResponder()
{
    if (iFreeResponders.size() == 0) {
        MsearchResponse* msr = new MsearchResponse(iDvStack, *this);
        return new Responder(msr);
    }
    DviDiscoveryManager::Responder* responder = static_cast<DviDiscoveryManager::Responder*>(iFreeResponders.front());
    iFreeResponders.pop_front();
    return responder;
}

DviDiscoveryManager::Announcer* DviDiscoveryManager::GetAnnouncer()
{
    if (iFreeAnnouncers.size() == 0) {
        try {
            DeviceAnnouncement* da = new DeviceAnnouncement(iDvStack, *this);
            return new Announcer(da);
        }
        catch (NetworkError&) {
            return NULL;
        }
    }
    DviDiscoveryManager::Announcer* announcer = static_cast<DviDiscoveryManager::Announcer*>(iFreeAnnouncers.front());
    iFreeAnnouncers.pop_front();
    return announcer;
}

void DviDiscoveryManager::SetActive(DviDiscoveryManager::Responder* aResponder, IUpnpAnnouncementData& aAnnouncementData)
{
    SetActive(iActiveResponders, aResponder, aAnnouncementData);
}

void DviDiscoveryManager::SetActive(DviDiscoveryManager::Announcer* aAnnouncer, IUpnpAnnouncementData& aAnnouncementData)
{
    SetActive(iActiveAnnouncers, aAnnouncer, aAnnouncementData);
}

void DviDiscoveryManager::SetActive(std::list<Notifier*>& aList, DviDiscoveryManager::Notifier* aNotifier, IUpnpAnnouncementData& aAnnouncementData)
{
    aNotifier->SetActive(aAnnouncementData.Udn());
    if (iActiveResponders.size() == 0 && iActiveAnnouncers.size() == 0) {
        // First active Notifier.  Will need to wait on any active Notifiers completing inside ~DviDiscoveryManager
        iShutdownSem.Wait();
    }
    aList.push_back(aNotifier);
}

void DviDiscoveryManager::NotifySchedulerComplete(SsdpNotifierScheduler* aScheduler)
{
    iLock.Wait();
    if (!TryMove(aScheduler, iActiveResponders, iFreeResponders)) {
        const TBool matched = TryMove(aScheduler, iActiveAnnouncers, iFreeAnnouncers);
        if (!matched) {
            ASSERTS(); // MSVC will warn about const conditional expr if we ASSERT(TryMove(...
        }
    }
    if (iActiveResponders.size() == 0 && iActiveAnnouncers.size() == 0) {
        // No active Notifiers so its currently safe to delete DviDiscoveryManager
        iShutdownSem.Signal();
    }
    iLock.Signal();
}

TBool DviDiscoveryManager::TryMove(SsdpNotifierScheduler* aScheduler, std::list<Notifier*>& aFrom, std::list<Notifier*>& aTo)
{
    std::list<Notifier*>::iterator it = aFrom.begin();
    while (it != aFrom.end()) {
        if ((*it)->Scheduler() == aScheduler) {
            Notifier* notifier = *it;
            notifier->SetInactive();
            (void)aFrom.erase(it);
            aTo.push_back(notifier);
            return true;
        }
        it++;
    }
    return false;
}


// DviDiscoveryManager::Notifier

DviDiscoveryManager::Notifier::~Notifier()
{
    delete iScheduler;
}

SsdpNotifierScheduler* DviDiscoveryManager::Notifier::Scheduler()
{
    return iScheduler;
}

TBool DviDiscoveryManager::Notifier::MatchesDevice(const Brx& aUdn) const
{
    return iUdn==aUdn;
}

void DviDiscoveryManager::Notifier::SetActive(const Brx& aUdn)
{
    iUdn.Set(aUdn);
}

void DviDiscoveryManager::Notifier::SetInactive()
{
    iUdn.Set(Brx::Empty());
}

DviDiscoveryManager::Notifier::Notifier(SsdpNotifierScheduler* aScheduler)
    : iScheduler(aScheduler)
{
}


// DviDiscoveryManager::Responder

DviDiscoveryManager::Responder::Responder(MsearchResponse* aResponder)
    : DviDiscoveryManager::Notifier(aResponder)
{
}

MsearchResponse& DviDiscoveryManager::Responder::Response()
{
    return *static_cast<MsearchResponse*>(iScheduler);
}


// DviDiscoveryManager::Announcer

DviDiscoveryManager::Announcer::Announcer(DeviceAnnouncement* aAnnouncer)
    : DviDiscoveryManager::Notifier(aAnnouncer)
{
}

DeviceAnnouncement& DviDiscoveryManager::Announcer::Announcement()
{
    return *static_cast<DeviceAnnouncement*>(iScheduler);
}
