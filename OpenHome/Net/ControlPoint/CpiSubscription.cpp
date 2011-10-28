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
    Schedule(eUnsubscribe);
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
    Stack::Mutex().Wait();
    EOperation op = iPendingOperation;
    iPendingOperation = eNone;
    Stack::Mutex().Signal();
    RunInSubscriber(op);
    RemoveRef();
}

void CpiSubscription::RunInSubscriber(EOperation aOperation)
{
    AutoMutex a(iSubscriberLock);
    switch (aOperation)
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
    , iSubscribeCompleted("SUBS", 0)
{
    iTimer = new Timer(MakeFunctor(*this, &CpiSubscription::Renew));
    iDevice.AddRef();
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

void CpiSubscription::Schedule(EOperation aOperation)
{
    Stack::Mutex().Wait();
    iRefCount++;
    if (iPendingOperation == eSubscribe) {
        iSubscribeCompleted.Signal();
    }
    iPendingOperation = aOperation;
    Stack::Mutex().Signal();
    CpiSubscriptionManager::Schedule(*this);
}

void CpiSubscription::DoSubscribe()
{
    Bws<Uri::kMaxUriBytes> uri;
    uri.Append(Http::kUriPrefix);
    NetworkAdapter* nif = Stack::NetworkAdapterList().CurrentAdapter();
    if (nif == NULL) {
        THROW(NetworkError);
    }
    Endpoint endpt(CpiSubscriptionManager::EventServer()->Port(), nif->Address());
    nif->RemoveRef();
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
    CpiSubscriptionManager::NotifyAddPending(*this);
    TUint renewSecs;
    try {
        (void)iSubscribeCompleted.Clear();
        renewSecs = iDevice.Subscribe(*this, subscriber);
    }
    catch (HttpError&) {
        NotifyAddAborted();
        THROW(HttpError);
    }
    catch (NetworkError&) {
        NotifyAddAborted();
        THROW(NetworkError);
    }
    catch (NetworkTimeout&) {
        NotifyAddAborted();
        THROW(NetworkTimeout);
    }
    catch (WriterError&) {
        NotifyAddAborted();
        THROW(WriterError);
    }
    catch (ReaderError&) {
        NotifyAddAborted();
        THROW(ReaderError);
    }

    CpiSubscriptionManager::Add(*this);
    iSubscribeCompleted.Signal();

    LOG(kEvent, "Subscription for ");
    LOG(kEvent, iServiceType.FullName());
    LOG(kEvent, " completed\n    Sid is ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n    Renew in %u secs\n", renewSecs);

    if (renewSecs > 0) {
        TUint renewMs = (renewSecs*1000)/2;
        iTimer->FireIn(renewMs);
    }
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
    }
    catch (HttpError&) {
        Schedule(eResubscribe);
        THROW(HttpError);
    }
    catch (WriterError&) {
        Schedule(eResubscribe);
        THROW(WriterError);
    }

    LOG(kEvent, "Renewed ");
    LOG(kEvent, iSid);
    LOG(kEvent, ".  Renew again in %u secs\n", renewSecs);

    if (renewSecs > 0) {
        TUint renewMs = (renewSecs*1000)/2;
        iTimer->FireIn(renewMs);
    }
}

void CpiSubscription::DoUnsubscribe()
{
    LOG(kEvent, "Unsubscribing sid ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n");

    iSubscribeCompleted.Wait();
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

void CpiSubscription::NotifyAddAborted()
{
    CpiSubscriptionManager::NotifyAddAborted(*this);
    iSubscribeCompleted.Signal();
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
    iSubscription->RemoveRef();
}

void Subscriber::Run()
{
    for (;;) {
        Wait();
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

        iFree.Write(this);
    }
}


// CpiCpiSubscriptionManager

CpiSubscriptionManager::CpiSubscriptionManager()
    : Thread("SBSM")
    , iLock("SBSL")
    , iFree(Stack::InitParams().NumSubscriberThreads())
    , iWaiter("SBSS", 0)
    , iWaiters(0)
    , iShutdownSem("SBMS", 0)
{
    NetworkAdapterList& ifList = Stack::NetworkAdapterList();
    NetworkAdapter* currentInterface = ifList.CurrentAdapter();
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
        currentInterface->RemoveRef();
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

    TBool wait;
    iLock.Wait();
    iActive = false;
    wait = (iMap.size() > 0);
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

    iLock.Wait();
    Kill();
    Join();
    iLock.Signal();

    for (TUint i=0; i<Stack::InitParams().NumSubscriberThreads(); i++) {
        delete iSubscribers[i];
    }
    free(iSubscribers);

    ASSERT(iList.size() == 0);

    Stack::NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListenerId);
    Stack::NetworkAdapterList().RemoveCurrentChangeListener(iInterfaceListListenerId);
    delete iEventServer;

    LOG(kEvent, "< ~CpiSubscriptionManager()\n");
}

CpiSubscription* CpiSubscriptionManager::NewSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType)
{
    return new CpiSubscription(aDevice, aEventProcessor, aServiceType);
}

void CpiSubscriptionManager::NotifyAddPending(CpiSubscription& aSubscription)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    self->iPendingSubscriptions.push_back(&aSubscription);
    self->iLock.Signal();
}

void CpiSubscriptionManager::NotifyAddAborted(CpiSubscription& aSubscription)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    self->RemovePendingAdd(aSubscription);
    self->iLock.Signal();
}

void CpiSubscriptionManager::WaitForPendingAdds()
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    TBool wait;
    self->iLock.Wait();
    wait = (self->iPendingSubscriptions.size() > 0);
    if (wait) {
        self->iWaiters++;
    }
    self->iLock.Signal();
    if (wait) {
        try {
            self->iWaiter.Wait(Stack::InitParams().PendingSubscriptionTimeoutMs());
        }
        catch(Timeout&) {}
    }
}

void CpiSubscriptionManager::Add(CpiSubscription& aSubscription)
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    Brn sid(aSubscription.Sid());
    ASSERT(sid.Bytes() > 0);
    self->iMap.insert(std::pair<Brn,CpiSubscription*>(sid, &aSubscription));
    self->RemovePendingAdd(aSubscription);
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
    TBool shutdownSignal = false;
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
    self->iLock.Wait();
    Brn sid(aSubscription.Sid());
    Map::iterator it = self->iMap.find(sid);
    if (it != self->iMap.end()) {
        it->second = NULL;
        self->iMap.erase(it);
    }
    if (!self->iActive) {
        if (self->iMap.size() == 0) {
            shutdownSignal = true;
        }
    }
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

EventServerUpnp* CpiSubscriptionManager::EventServer()
{
    CpiSubscriptionManager* self = CpiSubscriptionManager::Self();
	return self->iEventServer;
}

CpiSubscriptionManager* CpiSubscriptionManager::Self()
{
    return &CpiStack::SubscriptionManager();
}

void CpiSubscriptionManager::RemovePendingAdd(CpiSubscription& aSubscription)
{
    for (TUint i=0; i<iPendingSubscriptions.size(); i++) {
        if (iPendingSubscriptions[i] == &aSubscription) {
            iPendingSubscriptions.erase(iPendingSubscriptions.begin() + i);
            break;
        }
    }

    if (iPendingSubscriptions.size() == 0) {
        for (TUint i=0; i<iWaiters; i++) {
            iWaiter.Signal();
        }
        iWaiters = 0;
    }
}

void CpiSubscriptionManager::CurrentNetworkAdapterChanged()
{
    HandleInterfaceChange(false);
}

void CpiSubscriptionManager::SubnetListChanged()
{
    HandleInterfaceChange(true);
}

void CpiSubscriptionManager::HandleInterfaceChange(TBool /*aNewSubnet*/)
{
    iLock.Wait();
    NetworkAdapterList& ifList = Stack::NetworkAdapterList();
    NetworkAdapter* currentInterface = ifList.CurrentAdapter();

    // trigger CpiSubscriptionManager::WaitForPendingAdds
    if (iPendingSubscriptions.size() > 0) {
        iWaiter.Signal();
    }

    // recreate the event server on the new interface
    delete iEventServer;
    if (currentInterface == NULL) {
        iEventServer = NULL;
    }
    else {
        iEventServer = new EventServerUpnp(currentInterface->Address());
        currentInterface->RemoveRef();
    }

    // don't worry about updating existing/pending subscriptions
    // instead rely on device list updates prompting proxies to be deleted
    //...which in turn will unsubscribe/delete the existing/pending subscriptions
#if 0
    // take a note of all active and pending subscriptions
    Map activeSubscriptions;
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        Brn sid(it->second->Sid());
        activeSubscriptions.insert(std::pair<Brn,CpiSubscription*>(sid, it->second));
        it++;
    }
    VectorSubscriptions pendingSubscriptions;
    for (TUint i=0; i<iPendingSubscriptions.size(); i++) {
        pendingSubscriptions.push_back(iPendingSubscriptions[i]);
    }
#endif

    iLock.Signal();

#if 0
    if (!aNewSubnet) {
        // resubscribe any pending subscriptions
        for (TUint i=0; i<pendingSubscriptions.size(); i++) {
            pendingSubscriptions[i]->Schedule(CpiSubscription::eSubscribe);
        }

        // resubscribe all formerly active subscriptions
        it = activeSubscriptions.begin();
        while (it != activeSubscriptions.end()) {
            it->second->SetNotificationError();
            it++;
        }
    }
    else {
        /* Its possible that we can't reach the subnet the subscriptions are on.
           Assume that attempts to unsubscribe in this case will fail extremely
           quickly, meaning that its not worth storing the last subnet and using
           that to decide whether unsubscribes have any route to be delivered */
        it = activeSubscriptions.begin();
        while (it != activeSubscriptions.end()) {
            it->second->Unsubscribe();
            it->second->iSubscribeCompleted.Signal();
            it++;
        }
    }
#endif
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
    }
}
