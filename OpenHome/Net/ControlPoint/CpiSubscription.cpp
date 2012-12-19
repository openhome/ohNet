#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Net/Private/XmlParser.h>

#include <list>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// Subscription

const Brx& CpiSubscription::Sid() const
{
    return iSid;
}

void CpiSubscription::AddRef()
{
    Stack::Mutex().Wait();
    iRefCount++;
    Stack::Mutex().Signal();
}

void CpiSubscription::RemoveRef()
{
    TBool dead;
    Stack::Mutex().Wait();
    ASSERT(iRefCount != 0);
    dead = (--iRefCount == 0);
    Stack::Mutex().Signal();
    if (dead) {
        delete this;
    }
}

TBool CpiSubscription::UpdateSequenceNumber(TUint aSequenceNumber)
{
    if (aSequenceNumber != iNextSequenceNumber) {
        return false;
    }
    iNextSequenceNumber++;
    return true;
}

void CpiSubscription::SetNotificationError()
{
    /* we've missed part or all of update message(s).  The only sure way to recover an
       accurate view on the state of all variables is to unsubscribe then subscribe again
       (relying on subscription generating a notification covering all state variables) */
    Schedule(eResubscribe);
}

void CpiSubscription::Unsubscribe()
{
    AddRef();
    iLock.Wait();
    iEventProcessor = NULL;
    if (iInterruptHandler != NULL) {
        iInterruptHandler->Interrupt();
    }
    iLock.Signal();
    Schedule(eUnsubscribe, true);
    RemoveRef();
}

void CpiSubscription::SetInterruptHandler(IInterruptHandler* aHandler)
{
    iLock.Wait();
    iInterruptHandler = aHandler;
    iLock.Signal();
}

void CpiSubscription::SetSid(Brh& aSid)
{
    Stack::Mutex().Wait();
    aSid.TransferTo(iSid);
    Stack::Mutex().Signal();
}

const OpenHome::Net::ServiceType& CpiSubscription::ServiceType() const
{
    return iServiceType;
}

void CpiSubscription::RunInSubscriber()
{
    AutoMutex a(iSubscriberLock);
    Stack::Mutex().Wait();
    EOperation op = iPendingOperation;
    iPendingOperation = eNone;
    Stack::Mutex().Signal();
    switch (op)
    {
    case eNone:
        break;
    case eSubscribe:
        DoSubscribe();
        break;
    case eRenew:
        DoRenew();
        break;
    case eUnsubscribe:
        DoUnsubscribe();
        break;
    case eResubscribe:
        DoUnsubscribe();
        Schedule(eSubscribe);
        break;
    }
}

CpiSubscription::CpiSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType)
    : iLock("SUBM")
    , iSubscriberLock("SBM2")
    , iDevice(aDevice)
    , iEventProcessor(&aEventProcessor)
    , iServiceType(aServiceType)
    , iPendingOperation(eNone)
    , iRefCount(1)
    , iInterruptHandler(NULL)
{
    iTimer = new Timer(MakeFunctor(*this, &CpiSubscription::Renew));
    iDevice.AddRef();
    iRejectFutureOperations = false;
    Schedule(eSubscribe);
    Stack::AddObject(this);
}

CpiSubscription::~CpiSubscription()
{
    iTimer->Cancel();
    ASSERT(iSid.Bytes() == 0);
    iDevice.RemoveRef();
    delete iTimer;
    Stack::RemoveObject(this);
}

void CpiSubscription::Schedule(EOperation aOperation, TBool aRejectFutureOperations)
{
    Stack::Mutex().Wait();
    if (iRejectFutureOperations) {
        Stack::Mutex().Signal();
        return;
    }
    if (aRejectFutureOperations) {
        iRejectFutureOperations = true;
    }
    iRefCount++;
    iPendingOperation = aOperation;
    Stack::Mutex().Signal();
    CpiSubscriptionManager::Schedule(*this);
}

void CpiSubscription::DoSubscribe()
{
    Bws<Uri::kMaxUriBytes> uri;
    uri.Append(Http::kSchemeHttp);
    NetworkAdapter* nif = Stack::NetworkAdapterList().CurrentAdapter("CpiSubscription::DoSubscribe");
    if (nif == NULL) {
        THROW(NetworkError);
    }
    TIpAddress nifAddr = nif->Address();
    nif->RemoveRef("CpiSubscription::DoSubscribe");
    Endpoint endpt(CpiSubscriptionManager::EventServerPort(), nifAddr);
    Endpoint::EndpointBuf buf;
    endpt.AppendEndpoint(buf);
    uri.Append(buf);
    uri.Append('/');
    Uri subscriber(uri);

    LOG(kEvent, "Subscribing - service = ");
    LOG(kEvent, iServiceType.FullName());
    LOG(kEvent, "\n    subscriber = ");
    LOG(kEvent, subscriber.AbsoluteUri());
    LOG(kEvent, "\n");

    iNextSequenceNumber = 0;
    TUint renewSecs;
    try {
        renewSecs = iDevice.Subscribe(*this, subscriber);
    }
    catch (XmlError&) {
        // we don't expect to ever get here.  Its worth capturing some debug info if we do.
        Brh deviceXml;
        if (!iDevice.GetAttribute("Upnp.DeviceXml", deviceXml)) {
            deviceXml.Set("[missing]");
        }
        const Brx& udn = iDevice.Udn();
        Stack::Mutex().Wait();
        Log::Print("XmlError attempting to subscribe to device ");
        Log::Print(udn);
        Log::Print(", with xml\n\n");
        Log::Print(deviceXml);
        Log::Print("\n\n");
        Stack::Mutex().Signal();
        THROW(XmlError);
    }

    CpiSubscriptionManager::Add(*this);

    LOG(kEvent, "Subscription for ");
    LOG(kEvent, iServiceType.FullName());
    LOG(kEvent, " completed\n    Sid is ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n    Renew in %u secs\n", renewSecs);

    SetRenewTimer(renewSecs);
}

void CpiSubscription::Renew()
{
    Schedule(eRenew);
}

void CpiSubscription::DoRenew()
{
    LOG(kEvent, "Renewing sid ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n");

    TUint renewSecs = 0;
    try {
        renewSecs = iDevice.Renew(*this);

        LOG(kEvent, "Renewed ");
        LOG(kEvent, iSid);
        LOG(kEvent, ".  Renew again in %u secs\n", renewSecs);

        SetRenewTimer(renewSecs);
    }
    catch (NetworkTimeout&) {
        Schedule(eResubscribe);
    }
    catch (NetworkError&) {
        Schedule(eResubscribe);
    }
    catch (HttpError&) {
        Schedule(eResubscribe);
    }
    catch (WriterError&) {
        Schedule(eResubscribe);
    }
    catch (ReaderError&) {
        Schedule(eResubscribe);
    }
    catch (Exception& e) {
        Log::Print("ERROR - unexpected exception renewing subscription: %s from %s:%u\n", e.Message(), e.File(), e.Line());
        ASSERTS();
    }
}

void CpiSubscription::DoUnsubscribe()
{
    LOG(kEvent, "Unsubscribing sid ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n");

    iTimer->Cancel();
    if (iSid.Bytes() == 0) {
        LOG(kEvent, "Skipped unsubscribing since sid is empty (we're not subscribed)\n");
        return;
    }
    CpiSubscriptionManager::Remove(*this);
    Brh sid;
    Stack::Mutex().Wait();
    iSid.TransferTo(sid);
    Stack::Mutex().Signal();
    iDevice.Unsubscribe(*this, sid);
    LOG(kEvent, "Unsubscribed sid ");
    LOG(kEvent, sid);
    LOG(kEvent, "\n");
}

void CpiSubscription::SetRenewTimer(TUint aMaxSeconds)
{
    if (aMaxSeconds == 0) {
        LOG2(kEvent, kError, "ERROR: subscription sid ");
        LOG2(kEvent, kError, iSid);
        LOG2(kEvent, kError, " has 0s renew time\n");
        return;
    }
    TUint renewMs = Random((aMaxSeconds*1000*3)/4, (aMaxSeconds*1000)/2);
    iTimer->FireIn(renewMs);
}

void CpiSubscription::EventUpdateStart()
{
    iLock.Wait();
    if (iEventProcessor != NULL) {
        iEventProcessor->EventUpdateStart();
    }
}

void CpiSubscription::EventUpdate(const Brx& aName, const Brx& aValue, IOutputProcessor& aProcessor)
{
    if (iEventProcessor != NULL) {
        iEventProcessor->EventUpdate(aName, aValue, aProcessor);
    }
}

void CpiSubscription::EventUpdateEnd()
{
    if (iEventProcessor != NULL) {
        iEventProcessor->EventUpdateEnd();
    }
    iLock.Signal();
}

void CpiSubscription::ListObjectDetails() const
{
    Log::Print("  CpiSubscription: addr=%p, device=", this);
    Log::Print(iDevice.Udn());
    Log::Print(", refCount=%u, sid=", iRefCount);
    Log::Print(iSid);
    Log::Print("\n");
}


// Subscriber

Subscriber::Subscriber(const TChar* aName, Fifo<Subscriber*>& aFree)
    : Thread(aName)
    , iFree(aFree)
    , iSubscription(NULL)
{
}

Subscriber::~Subscriber()
{
    Kill();
    Join();
}

void Subscriber::Subscribe(CpiSubscription* aSubscription)
{
    iSubscription = aSubscription;
    Signal();
}

#ifdef DEFINE_TRACE
void Subscriber::Error(const TChar* aErr)
#else
void Subscriber::Error(const TChar* /*aErr*/)
#endif
{
    LOG2(kEvent, kError, "Error - %s - from SID ", aErr);
    if (iSubscription->Sid().Bytes() > 0) {
        LOG2(kEvent, kError, iSubscription->Sid());
    }
    else {
        LOG2(kEvent, kError, "(null)");
    }
    LOG2(kEvent, kError, "\n");
    // don't try to resubscribe as we may get stuck in an endless cycle of errors
}

void Subscriber::Run()
{
    for (;;) {
        TBool exit = false;
        try {
            Wait();
        }
        catch (ThreadKill&) {
            if (iSubscription == NULL) {
                return;
            }
            exit = true;
        }
        try {
            iSubscription->RunInSubscriber();
        }
        catch (HttpError&) {
            Error("Http");
        }
        catch (NetworkError&) {
            Error("Network");
        }
        catch (NetworkTimeout&) {
            Error("Timeout");
        }
        catch (WriterError&) {
            Error("Writer");
        }
        catch (ReaderError&) {
            Error("Reader");
        }
        catch (XmlError&) {
            Error("XmlError");
        }
        iSubscription->RemoveRef();
        iSubscription = NULL;
        if (exit) {
            break;
        }
        iFree.Write(this);
    }
}


// CpiSubscriptionManager

CpiSubscriptionManager::CpiSubscriptionManager()
    : Thread("SBSM")
    , iLock("SBSL")
    , iFree(Stack::InitParams().NumSubscriberThreads())
    , iWaiter("SBSS", 0)
    , iWaiters(0)
    , iShutdownSem("SBMS", 0)
{
    NetworkAdapterList& ifList = Stack::NetworkAdapterList();
    AutoNetworkAdapterRef ref("CpiSubscriptionManager ctor");
    const NetworkAdapter* currentInterface = ref.Adapter();
    Functor functor = MakeFunctor(*this, &CpiSubscriptionManager::CurrentNetworkAdapterChanged);
    iInterfaceListListenerId = ifList.AddCurrentChangeListener(functor);
    functor = MakeFunctor(*this, &CpiSubscriptionManager::SubnetListChanged);
    iSubnetListenerId = ifList.AddSubnetListChangeListener(functor);
    if (currentInterface == NULL) {
        iEventServer = NULL;
    }
    else {
        iLock.Wait();
        iEventServer = new EventServerUpnp(currentInterface->Address());
        iLock.Signal();
    }

    TChar thName[5] = "SBS ";
#ifndef _WIN32
    ASSERT(Stack::InitParams().NumSubscriberThreads() <= 9);
#endif
    iSubscribers = (Subscriber**)malloc(sizeof(*iSubscribers) * Stack::InitParams().NumSubscriberThreads());
    for (TUint i=0; i<Stack::InitParams().NumSubscriberThreads(); i++) {
        thName[3] = (TChar)('0'+i);
        iSubscribers[i] = new Subscriber(&thName[0], iFree);
        iFree.Write(iSubscribers[i]);
        iSubscribers[i]->Start();
    }

    iActive = true;
    Start();
}

CpiSubscriptionManager::~CpiSubscriptionManager()
{
    LOG(kEvent, "> ~CpiSubscriptionManager()\n");

    iLock.Wait();
    iActive = false;
    TBool wait = !ReadyForShutdown();
    iShutdownSem.Clear();
    iLock.Signal();
    if (wait) {
        // wait 1 minute then proceed
        // we'll have leaked some subscriptions but this'll be logged later during shutdown
        try {
            iShutdownSem.Wait(60*1000);
        }
        catch(Timeout&) {
            Log::Print("WARNING: Subscription manager failed to shutdown cleanly\n");
            Stack::ListObjects();
        }
    }

    Kill();
    Join();

    for (TUint i=0; i<Stack::InitParams().NumSubscriberThreads(); i++) {
        delete iSubscribers[i];
    }
    free(iSubscribers);

    Stack::NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListenerId);
    Stack::NetworkAdapterList().RemoveCurrentChangeListener(iInterfaceListListenerId);
    delete iEventServer;

    LOG(kEvent, "< ~CpiSubscriptionManager()\n");
}

CpiSubscription* CpiSubscriptionManager::NewSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType)
{
    return new CpiSubscription(aDevice, aEventProcessor, aServiceType);
}

void CpiSubscriptionManager::WaitForPendingAdd(const Brx& aSid)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    PendingSubscription* pending = new PendingSubscription(aSid);
    self->iPendingSubscriptions.push_back(pending);
    self->iLock.Signal();
    try {
        pending->iSem.Wait(Stack::InitParams().PendingSubscriptionTimeoutMs());
    }
    catch(Timeout&) {
        self->iLock.Wait();
        self->RemovePendingAdd(aSid);
        self->iLock.Signal();
    }
    delete pending;
}

void CpiSubscriptionManager::Add(CpiSubscription& aSubscription)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    Brn sid(aSubscription.Sid());
    ASSERT(sid.Bytes() > 0);
    self->iMap.insert(std::pair<Brn,CpiSubscription*>(sid, &aSubscription));
    self->RemovePendingAdd(sid);
    self->iLock.Signal();
}

CpiSubscription* CpiSubscriptionManager::FindSubscription(const Brx& aSid)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    AutoMutex a(self->iLock);
    Brn sid(aSid);
    Map::iterator it = self->iMap.find(sid);
    if (it == self->iMap.end()) {
        return NULL;
    }
    CpiSubscription* subscription = it->second;
    subscription->AddRef();
    return subscription;
}

void CpiSubscriptionManager::Remove(CpiSubscription& aSubscription)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    Brn sid(aSubscription.Sid());
    Map::iterator it = self->iMap.find(sid);
    if (it != self->iMap.end()) {
        it->second = NULL;
        self->iMap.erase(it);
    }
    TBool shutdownSignal = self->ReadyForShutdown();
    self->iLock.Signal();
    if (shutdownSignal) {
        self->iShutdownSem.Signal();
    }
}

void CpiSubscriptionManager::Schedule(CpiSubscription& aSubscription)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    ASSERT(self->iActive);
    self->iList.push_back(&aSubscription);
    self->Signal();
    self->iLock.Signal();
}

TUint CpiSubscriptionManager::EventServerPort()
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    AutoMutex a(self->iLock);
    EventServerUpnp* server = self->iEventServer;
    if (server == NULL) {
        THROW(ReaderError);
    }
    return server->Port();
}

CpiSubscriptionManager* CpiSubscriptionManager::Self()
{
    return &CpiStack::SubscriptionManager();
}

void CpiSubscriptionManager::RemovePendingAdd(const Brx& aSid)
{
    for (TUint i=0; i<iPendingSubscriptions.size(); i++) {
        PendingSubscription* pending = iPendingSubscriptions[i];
        if (pending->iSid == aSid) {
            pending->iSem.Signal();
            iPendingSubscriptions.erase(iPendingSubscriptions.begin() + i);
            break;
        }
    }
}

void CpiSubscriptionManager::CurrentNetworkAdapterChanged()
{
    HandleInterfaceChange();
}

void CpiSubscriptionManager::SubnetListChanged()
{
    HandleInterfaceChange();
}

void CpiSubscriptionManager::HandleInterfaceChange()
{
    iLock.Wait();
    // trigger CpiSubscriptionManager::WaitForPendingAdd
    while (iPendingSubscriptions.size() > 0) {
        RemovePendingAdd(iPendingSubscriptions[0]->iSid);
    }
    EventServerUpnp* server = iEventServer;
    iEventServer = NULL;
    // releasing the lock here leaves a tiny window in which an event session thread can
    // block at CpiSubscriptionManager::WaitForPendingAdds.  This will add a very rare delay
    // of a few seconds so it's acceptable to risk this rather than add complicated, hard
    // to test, code.
    iLock.Signal();

    // recreate the event server on the new interface
    delete server;
    AutoNetworkAdapterRef ref("CpiSubscriptionManager::HandleInterfaceChange");
    const NetworkAdapter* currentInterface = ref.Adapter();
    if (currentInterface != NULL) {
        iEventServer = new EventServerUpnp(currentInterface->Address());
    }
}

TBool CpiSubscriptionManager::ReadyForShutdown() const
{
    if (!iActive) {
        if (iMap.size() == 0 && iList.size() == 0) {
            return true;
        }
    }
    return false;
}

void CpiSubscriptionManager::Run()
{
    for (;;) {
        Wait();
        Subscriber* subscriber = iFree.Read();
        iLock.Wait();
        CpiSubscription* subscription = iList.front();
        iList.front() = NULL;
        iList.pop_front();
        iLock.Signal();

        subscriber->Subscribe(subscription);

        iLock.Wait();
        TBool shutdownSignal = ReadyForShutdown();
        iLock.Signal();
        if (shutdownSignal) {
            iShutdownSem.Signal();
        }
    }
}


// CpiSubscriptionManager::PendingSubscription

CpiSubscriptionManager::PendingSubscription::PendingSubscription(const Brx& aSid)
    : iSid(aSid)
    , iSem("SMPS", 0)
{
}
