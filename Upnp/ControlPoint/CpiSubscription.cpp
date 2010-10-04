#include <CpiSubscription.h>
#include <Zapp.h>
#include <Stream.h>
#include <Http.h>
#include <Uri.h>
#include <ZappTypes.h>
#include <CpiDevice.h>
#include <Buffer.h>
#include <Timer.h>
#include <Thread.h>
#include <Fifo.h>
#include <Debug.h>
#include <Stack.h>
#include <CpiStack.h>

#include <list>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace Zapp;

// Subscription

const Brx& Subscription::Sid() const
{
    return iSid;
}

void Subscription::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void Subscription::RemoveRef()
{
    TBool dead;
    iLock.Wait();
    ASSERT(iRefCount != 0);
    dead = (--iRefCount == 0);
    iLock.Signal();
    if (dead) {
        delete this;
    }
}

void Subscription::StopUpdates()
{
    iLock.Wait();
    iStopUpdates = true;
    iLock.Signal();
}

TBool Subscription::UpdateSequenceNumber(TUint aSequenceNumber)
{
    if (aSequenceNumber != iNextSequenceNumber) {
        return false;
    }
    iNextSequenceNumber++;
    return true;
}

void Subscription::ProcessNotification(const Brx& aNotification)
{
    AutoMutex a(iLock);
    if (!iStopUpdates) {
        iDevice.ProcessPropertyNotification(aNotification, iProperties);
        if (iUpdatesComplete != NULL) {
            iUpdatesComplete();
        }
    }
}

void Subscription::SetNotificationError()
{
    /* we've missed part or all of update message(s).  The only sure way to recover an
       accurate view on the state of all variables is to unsubscribe then subscribe again
       (relying on subscription generating a notification covering all state variables) */
    Schedule(eResubscribe);
}

void Subscription::Unsubscribe()
{
    AddRef();
    iLock.Wait();
    if (iInterruptHandler != NULL) {
        iInterruptHandler->Interrupt();
    }
    iLock.Signal();
    Schedule(eUnsubscribe);
    RemoveRef();
}

void Subscription::SetInterruptHandler(IInterruptHandler* aHandler)
{
    iLock.Wait();
    iInterruptHandler = aHandler;
    iLock.Signal();
}

void Subscription::SetSid(Brh& aSid)
{
    iLock.Wait();
    aSid.TransferTo(iSid);
    iLock.Signal();
}

const Zapp::ServiceType& Subscription::ServiceType() const
{
    return iServiceType;
}

void Subscription::RunInSubscriber()
{
    iLock.Wait();
    EOperation op = iPendingOperation;
    iLock.Signal();

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
    RemoveRef();
}

Subscription::Subscription(CpiDevice& aDevice, const Zapp::ServiceType& aServiceType,
                           PropertyMap& aProperties, Functor& aUpdatesComplete)
    : iLock("SUBM")
    , iDevice(aDevice)
    , iServiceType(aServiceType)
    , iProperties(aProperties)
    , iUpdatesComplete(aUpdatesComplete)
    , iPendingOperation(eNone)
    , iRefCount(1)
    , iStopUpdates(false)
    , iInterruptHandler(NULL)
{
    iTimer = new Timer(MakeFunctor(*this, &Subscription::Renew));
    iDevice.AddRef();
    Schedule(eSubscribe);
}

Subscription::~Subscription()
{
    iTimer->Cancel();
    iLock.Wait();
    if (iSid.Bytes() > 0) {
        SubscriptionManager::Remove(*this);
    }
    iLock.Signal();
    iDevice.RemoveRef();
    delete iTimer;
}

void Subscription::Schedule(EOperation aOperation)
{
    iLock.Wait();
    iRefCount++;
    iPendingOperation = aOperation;
    iLock.Signal();
    SubscriptionManager::Schedule(*this);
}

void Subscription::DoSubscribe()
{
    Bws<Uri::kMaxUriBytes> uri;
    uri.Append(Http::kUriPrefix);
    NetworkInterface* nif = Stack::NetworkInterfaceList().CurrentInterface();
    if (nif == NULL) {
        THROW(NetworkError);
    }
    TIpAddress addr = nif->Address();
    delete nif;
    (void)Ascii::AppendDec(uri, addr&0xff);
    uri.Append('.');
    (void)Ascii::AppendDec(uri, (addr>>8)&0xff);
    uri.Append('.');
    (void)Ascii::AppendDec(uri, (addr>>16)&0xff);
    uri.Append('.');
    (void)Ascii::AppendDec(uri, (addr>>24)&0xff);
    uri.Append(':');
    (void)Ascii::AppendDec(uri, SubscriptionManager::EventServer()->Port());
    uri.Append('/');
    Uri subscriber(uri);

    LOG(kEvent, "Subscribing - service = ");
    LOG(kEvent, iServiceType.FullName());
    LOG(kEvent, "\n    subscriber = ");
    LOG(kEvent, subscriber.AbsoluteUri());
    LOG(kEvent, "\n");

    iNextSequenceNumber = 0;
    SubscriptionManager::NotifyAddPending(*this);
    TUint renewSecs;
    try {
        renewSecs = iDevice.Subscribe(*this, subscriber);
    }
    catch (HttpError&) {
        SubscriptionManager::NotifyAddAborted(*this);
        THROW(HttpError);
    }
    catch (NetworkError&) {
        SubscriptionManager::NotifyAddAborted(*this);
        THROW(NetworkError);
    }
    catch (NetworkTimeout&) {
        SubscriptionManager::NotifyAddAborted(*this);
        THROW(NetworkTimeout);
    }
    catch (WriterError&) {
        SubscriptionManager::NotifyAddAborted(*this);
        THROW(WriterError);
    }
    catch (ReaderError&) {
        SubscriptionManager::NotifyAddAborted(*this);
        THROW(ReaderError);
    }

    SubscriptionManager::Add(*this);

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

void Subscription::Renew()
{
    Schedule(eRenew);
}

void Subscription::DoRenew()
{
    LOG(kEvent, "Renewing sid ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n");

    TUint renewSecs = iDevice.Renew(*this);

    LOG(kEvent, "Renewed ");
    LOG(kEvent, iSid);
    LOG(kEvent, ".  Renew again in %u secs\n", renewSecs);

    if (renewSecs > 0) {
        TUint renewMs = (renewSecs*1000)/2;
        iTimer->FireIn(renewMs);
    }
}

void Subscription::DoUnsubscribe()
{
    LOG(kEvent, "Unsubscribing sid ");
    LOG(kEvent, iSid);
    LOG(kEvent, "\n");

    iTimer->Cancel();
    SubscriptionManager::Remove(*this);
    Brh sid;
    iLock.Wait();
    iSid.TransferTo(sid);
    iLock.Signal();
    iDevice.Unsubscribe(*this, sid);

    LOG(kEvent, "Unsubscribed sid ");
    LOG(kEvent, sid);
    LOG(kEvent, "\n");
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

void Subscriber::Subscribe(Subscription* aSubscription)
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


// SubscriptionManager

SubscriptionManager::SubscriptionManager()
    : Thread("SBSM")
    , iLock("SBSL")
    , iFree(Stack::InitParams().NumSubscriberThreads())
    , iWaiter("SBSS", 0)
    , iWaiters(0)
    , iShutdownSem("SBMS", 0)
{
    NetworkInterfaceList& ifList = Stack::NetworkInterfaceList();
    NetworkInterface* currentInterface = ifList.CurrentInterface();
    Functor functor = MakeFunctor(*this, &SubscriptionManager::CurrentNetworkInterfaceChanged);
    iInterfaceListListenerId = ifList.AddCurrentChangeListener(functor);
    functor = MakeFunctor(*this, &SubscriptionManager::SubnetChanged);
    iSubnetListenerId = ifList.AddSubnetChangeListener(functor);
    if (currentInterface == NULL) {
        iEventServer = NULL;
    }
    else {
        iLock.Wait();
        iEventServer = new EventServerUpnp(currentInterface->Address());
        iLock.Signal();
        delete currentInterface;
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

SubscriptionManager::~SubscriptionManager()
{
    LOG(kEvent, "> ~SubscriptionManager()\n");

    TBool wait;
    iLock.Wait();
    iActive = false;
    wait = (iMap.size() > 0);
    iShutdownSem.Clear();
    iLock.Signal();
    if (wait) {
        iShutdownSem.Wait();
    }
    ASSERT(iMap.size() == 0);

    iLock.Wait();
    Kill();
    Join();
    iLock.Signal();

    for (TUint i=0; i<Stack::InitParams().NumSubscriberThreads(); i++) {
        delete iSubscribers[i];
    }
    free(iSubscribers);

    ASSERT(iList.size() == 0);

    Stack::NetworkInterfaceList().RemoveSubnetChangeListener(iSubnetListenerId);
    Stack::NetworkInterfaceList().RemoveCurrentChangeListener(iInterfaceListListenerId);
    delete iEventServer;

    LOG(kEvent, "< ~SubscriptionManager()\n");
}

Subscription* SubscriptionManager::NewSubscription(CpiDevice& aDevice, const ServiceType& aServiceType,
                                                   PropertyMap& aProperties, Functor& aUpdatesComplete)
{
    return new Subscription(aDevice, aServiceType, aProperties, aUpdatesComplete);
}

void SubscriptionManager::NotifyAddPending(Subscription& aSubscription)
{
    SubscriptionManager* self = SubscriptionManager::Self();
    self->iLock.Wait();
    self->iPendingSubscriptions.push_back(&aSubscription);
    self->iLock.Signal();
}

void SubscriptionManager::NotifyAddAborted(Subscription& aSubscription)
{
    SubscriptionManager* self = SubscriptionManager::Self();
    self->iLock.Wait();
    self->RemovePendingAdd(aSubscription);
    self->iLock.Signal();
}

void SubscriptionManager::WaitForPendingAdds()
{
    SubscriptionManager* self = SubscriptionManager::Self();
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

void SubscriptionManager::Add(Subscription& aSubscription)
{
    SubscriptionManager* self = SubscriptionManager::Self();
    self->iLock.Wait();
    Brn sid(aSubscription.Sid());
    ASSERT(sid.Bytes() > 0);
    self->iMap.insert(std::pair<Brn,Subscription*>(sid, &aSubscription));
    self->RemovePendingAdd(aSubscription);
    self->iLock.Signal();
}

Subscription* SubscriptionManager::FindSubscription(const Brx& aSid)
{
    SubscriptionManager* self = SubscriptionManager::Self();
    AutoMutex a(self->iLock);
    Brn sid(aSid);
    Map::iterator it = self->iMap.find(sid);
    if (it == self->iMap.end()) {
        return NULL;
    }
    Subscription* subscription = it->second;
    subscription->AddRef();
    return subscription;
}

void SubscriptionManager::Remove(Subscription& aSubscription)
{
    TBool shutdownSignal = false;
    SubscriptionManager* self = SubscriptionManager::Self();
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

void SubscriptionManager::Schedule(Subscription& aSubscription)
{
    SubscriptionManager* self = SubscriptionManager::Self();
    self->iLock.Wait();
    ASSERT(self->iActive);
    self->iList.push_back(&aSubscription);
    self->Signal();
    self->iLock.Signal();
}

EventServerUpnp* SubscriptionManager::EventServer()
{
    SubscriptionManager* self = SubscriptionManager::Self();
	return self->iEventServer;
}

SubscriptionManager* SubscriptionManager::Self()
{
    return &CpiStack::SubscriptionManager();
}

void SubscriptionManager::RemovePendingAdd(Subscription& aSubscription)
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

void SubscriptionManager::CurrentNetworkInterfaceChanged()
{
    HandleInterfaceChange(false);
}

void SubscriptionManager::SubnetChanged()
{
    HandleInterfaceChange(true);
}

void SubscriptionManager::HandleInterfaceChange(TBool aNewSubnet)
{
    iLock.Wait();
    NetworkInterfaceList& ifList = Stack::NetworkInterfaceList();
    NetworkInterface* currentInterface = ifList.CurrentInterface();

    // trigger SubscriptionManager::WaitForPendingAdds
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
    }

    // take a note of all active and pending subscriptions
    Map activeSubscriptions;
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        Brn sid(it->second->Sid());
        activeSubscriptions.insert(std::pair<Brn,Subscription*>(sid, it->second));
        it++;
    }
    VectorSubscriptions pendingSubscriptions;
    for (TUint i=0; i<iPendingSubscriptions.size(); i++) {
        pendingSubscriptions.push_back(iPendingSubscriptions[i]);
    }

    iLock.Signal();

    if (!aNewSubnet) {
        // resubscribe any pending subscriptions
        for (TUint i=0; i<pendingSubscriptions.size(); i++) {
            pendingSubscriptions[i]->Schedule(Subscription::eSubscribe);
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
            it++;
        }
    }
}

void SubscriptionManager::Run()
{
    for (;;) {
        Wait();
        Subscriber* subscriber = iFree.Read();
        iLock.Wait();
        Subscription* subscription = iList.front();
        iList.front() = NULL;
        iList.pop_front();
        iLock.Signal();
        subscriber->Subscribe(subscription);
    }
}
