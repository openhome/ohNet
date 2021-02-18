#include <OpenHome/Net/Private/CpiSubscription.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>
#include <OpenHome/Net/Private/XmlParser.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Private/Globals.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/DviSubscription.h> // for DvSubscriptionError
#include <OpenHome/Private/TIpAddressUtils.h>

#include <list>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// Subscription

const Brx& CpiSubscription::Sid() const
{
    AutoMutex a(iSidLock);
    return iSid;
}

TUint CpiSubscription::Id() const
{
    return iId;
}

void CpiSubscription::AddRef()
{
    AutoMutex _(iLockInternal);
    iRefCount++;
}

void CpiSubscription::RemoveRef()
{
    TBool dead;
    {
        AutoMutex _(iLockInternal);
        ASSERT(iRefCount != 0);
        dead = (--iRefCount == 0);
    }
    if (dead) {
        delete this;
    }
}

TBool CpiSubscription::UpdateSequenceNumber(TUint aSequenceNumber)
{
    iLock.Wait();
    if (aSequenceNumber != iNextSequenceNumber) {
        iLock.Signal();
        return false;
    }
    iNextSequenceNumber++;
    return true;
}

TBool CpiSubscription::UpdateSequenceNumber()
{
    return UpdateSequenceNumber(iNextSequenceNumber);
}

void CpiSubscription::Unlock()
{
    iLock.Signal();
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
    {
        AutoMutex a(iLock);
        if (iEventProcessor != NULL) {
            iEventProcessor->EventUpdatePrepareForDelete();
            iEventProcessor = NULL;
        }
        if (iInterruptHandler != NULL) {
            iInterruptHandler->Interrupt();
        }
    }
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
    iSidLock.Wait();
    aSid.TransferTo(iSid);
    iSidLock.Signal();
}

const OpenHome::Net::ServiceType& CpiSubscription::ServiceType() const
{
    return iServiceType;
}

void CpiSubscription::RunInSubscriber()
{
    AutoMutex a(iSubscriberLock);
    iLockInternal.Wait();
    EOperation op = iPendingOperation;
    iPendingOperation = eNone;
    iLockInternal.Signal();
    switch (op)
    {
    case eNone:
        break;
    case eSubscribe:
        try {
            DoSubscribe();
        }
        catch (AssertionFailed&) {
            throw;
        }
        catch(...) {
            const Brx& udn = iDevice.Udn();
            LOG_ERROR(kEvent, "Subscribe (%p) for device %.*s failed\n", this, PBUF(udn));
            throw;
        }
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

CpiSubscription::CpiSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType, TUint aId)
    : iLock("SUBM")
    , iSubscriberLock("SBM2")
    , iLockInternal("SBM3")
    , iSidLock("SBM4")
    , iDevice(aDevice)
    , iCpStack(aDevice.GetCpStack())
    , iEnv(iCpStack.Env())
    , iEventProcessor(&aEventProcessor)
    , iServiceType(aServiceType)
    , iId(aId)
    , iPendingOperation(eNone)
    , iRefCount(1)
    , iSubscribeErrorCount(0)
    , iInterruptHandler(NULL)
    , iSuspended(false)
{
    iTimer = new Timer(iEnv, MakeFunctor(*this, &CpiSubscription::Renew), "CpiSubscription");
    iTimerSubscribeRetry = new Timer(iEnv, MakeFunctor(*this, &CpiSubscription::SubscribeRetry), "CpiSubscription2");
    iDevice.AddRef();
    iRejectFutureOperations = false;
    iEnv.AddObject(this);
}

CpiSubscription::~CpiSubscription()
{
    iTimer->Cancel();
    iTimerSubscribeRetry->Cancel();
    ASSERT(iSid.Bytes() == 0);
    iCpStack.SubscriptionManager().Remove(*this); // in case we never subscribed, so never need to unsubscribe
    iDevice.RemoveRef();
    delete iTimerSubscribeRetry;
    delete iTimer;
    iEnv.RemoveObject(this);
}

void CpiSubscription::Schedule(EOperation aOperation, TBool aRejectFutureOperations)
{
    if (StartSchedule(aOperation, aRejectFutureOperations)) {
        iDevice.GetCpStack().SubscriptionManager().Schedule(*this);
    }
}

TBool CpiSubscription::StartSchedule(EOperation aOperation, TBool aRejectFutureOperations)
{
    AutoMutex _(iLockInternal);
    if (iRejectFutureOperations) {
        return false;
    }
    if (aRejectFutureOperations) {
        iRejectFutureOperations = true;
    }
    iRefCount++;
    iPendingOperation = aOperation;
    return true;
}

void CpiSubscription::DoSubscribe()
{
    Bws<Uri::kMaxUriBytes> uri;
    uri.Append(Http::kSchemeHttp);
    NetworkAdapter* nif = iEnv.NetworkAdapterList().CurrentAdapter("CpiSubscription::DoSubscribe").Ptr();
    TIpAddress nifAddr = kTIpAddressEmpty;
    if (nif != NULL) {
        nifAddr = nif->Address();
        nif->RemoveRef("CpiSubscription::DoSubscribe");
    }
    Endpoint endpt(iCpStack.SubscriptionManager().EventServerPort(), nifAddr);
    Endpoint::EndpointBuf buf;
    endpt.AppendEndpoint(buf);
    uri.Append(buf);
    uri.Append('/');
    Ascii::AppendDec(uri, iId);
    uri.Append('/');
    Uri subscriber(uri);

    const Brx& serviceFullName = iServiceType.FullName();
    const Brx& subscriberUri = subscriber.AbsoluteUri();
    LOG(kEvent, "Subscribing - device = %.*s\n    service = %.*s\n    subscription = %p\n    subscriber = %.*s\n",
                PBUF(iDevice.Udn()), PBUF(serviceFullName), this, PBUF(subscriberUri));

    iNextSequenceNumber = 0;
    TUint renewSecs;
    try {
        renewSecs = iDevice.Subscribe(*this, subscriber);
    }
    // retry subscription request
    catch (NetworkTimeout& ex) {
        ScheduleSubscribeRetry(ex.Message());
        throw;
    }
    catch (NetworkError& ex) {
        ScheduleSubscribeRetry(ex.Message());
        throw;
    }
    catch (WriterError& ex) {
        ScheduleSubscribeRetry(ex.Message());
        throw;
    }
    // subscription may have succeeded, try renewing it later
    catch (XmlError&) {
        // we don't expect to ever get here.  Its worth capturing some debug info if we do.
        Brh deviceXml;
        if (!iDevice.GetAttribute("Upnp.DeviceXml", deviceXml)) {
            deviceXml.Set("[missing]");
        }
        const Brx& udn = iDevice.Udn();
        Log::Print("XmlError attempting to subscribe to %.*s service on device %.*s, with xml\n\n%.*s\n\n",
                   PBUF(serviceFullName), PBUF(udn), PBUF(deviceXml));

        SetRenewTimerDefault();
        throw;
    }
    catch (Exception&) {
        SetRenewTimerDefault();
        throw;
    }

    LOG(kEvent, "Subscription (%p) for %.*s, %.*s completed\n    Sid is %.*s\n    Renew in %u secs\n",
                this, PBUF(iDevice.Udn()), PBUF(serviceFullName), PBUF(iSid), renewSecs);

    iSubscribeErrorCount = 0;
    SetRenewTimer(renewSecs);
}

void CpiSubscription::Renew()
{
    Schedule(eRenew);
}

void CpiSubscription::DoRenew()
{
    LOG(kEvent, "Renewing (%p) sid %.*s\n", this, PBUF(iSid));

    TUint renewSecs = 0;
    try {
        renewSecs = iDevice.Renew(*this);
        LOG(kEvent, "Renewed (%p) %.*s.  Renew again in %u secs\n",
                    this, PBUF(iSid), renewSecs);
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
    catch (DvSubscriptionError&) {
        Log::Print("WARNING: CpiSubscription::DoRenew() caught DvSubscriptionError (has some other CP removed a subscription used by a CpDeviceDv?)\n");
        Schedule(eResubscribe);
    }
    catch (AssertionFailed&) {
        throw;
    }
    catch (Exception& e) {
        Log::Print("ERROR - unexpected exception renewing subscription: %s from %s:%u\n", e.Message(), e.File(), e.Line());
        ASSERTS();
    }
}

void CpiSubscription::DoUnsubscribe()
{
    LOG(kEvent, "Unsubscribing (%p) sid %.*s\n", this, PBUF(iSid));

    const TUint startTime = Os::TimeInMs(iEnv.OsCtx());
    iTimer->Cancel();
    if (iSid.Bytes() == 0) {
        LOG(kEvent, "Skipped unsubscribing since sid is empty (we're not subscribed)\n");
        return;
    }
    Brh sid;
    iLockInternal.Wait();
    iSid.TransferTo(sid);
    iLockInternal.Signal();
    try {
        iDevice.Unsubscribe(*this, sid);
    }
    catch (NetworkTimeout&) {
    }
    catch (NetworkError&) {
    }
    catch (HttpError&) {
    }
    catch (WriterError&) {
    }
    catch (ReaderError&) {
    }
    const TUint diffTime = Os::TimeInMs(iEnv.OsCtx()) - startTime; // ignore possibility of time wrapping
    LOG(kEvent, "Unsubscribed (%p) sid %.*s in %ums\n", this, PBUF(sid), diffTime);
}

void CpiSubscription::ScheduleSubscribeRetry(const TChar* aMsg)
{
    static const TUint kMaxSubscribeRetrys = 10;
    static const TUint kRetryDelayGranularity = 250;

    ++iSubscribeErrorCount;
    const Brx& serviceFullName = iServiceType.FullName();
    LOG(kEvent, "Subscription (%p) for %.*s, %.*s failed (%s) - failure count is %u\n",
        this, PBUF(iDevice.Udn()), PBUF(serviceFullName), aMsg, iSubscribeErrorCount);
    if (iSubscribeErrorCount > kMaxSubscribeRetrys) {
        // if we can't subscribe after the first 20 attempts, we're unlikely to ever succeed
        return;
    }
    const TUint retryMs = iSubscribeErrorCount * kRetryDelayGranularity;
    iTimerSubscribeRetry->FireIn(retryMs);
}

void CpiSubscription::SubscribeRetry()
{
    Schedule(eSubscribe);
}

void CpiSubscription::SetRenewTimer(TUint aMaxSeconds)
{
    if (aMaxSeconds == 0) {
        LOG_ERROR(kEvent, "ERROR: subscription (%p) sid %.*s has 0s renew time\n", this, PBUF(iSid));
        return;
    }
    TUint64 maxSeconds = aMaxSeconds;
    const TUint randMin = (TUint)((maxSeconds*1000*3)/4);
    const TUint randMax = (TUint)((maxSeconds*1000)/2);
    TUint renewMs = iEnv.Random(randMin, randMax);
    iTimer->FireIn(renewMs);
}

void CpiSubscription::SetRenewTimerDefault()
{
    const TUint defaultDurationSecs = iEnv.InitParams()->SubscriptionDurationSecs();
    SetRenewTimer(defaultDurationSecs);
}

void CpiSubscription::Resubscribe()
{
    EOperation op = iSuspended? eSubscribe : eResubscribe;
    if (StartSchedule(op, false)) {
        iDevice.GetCpStack().SubscriptionManager().ScheduleLocked(*this);
    }
}

void CpiSubscription::NotifySubnetChanged()
{
    /* We're on a new network so all existing subscriptions are pretty much useless.
       We expect all subscriptions to be unsubscribed very shortly when a device
       list signals that its devices have been removed.  At that point, each
       unsubscribe attempt might block for InitParams::TcpConnectTimeoutMs() failing
       to (tcp) connect to its device.  To avoid this, refuse any further operations
       as soon as we know about a subnet change */
    AutoMutex _(iLockInternal);
    iRejectFutureOperations = true;
    Brh tmp;
    iSid.TransferTo(tmp);
}

void CpiSubscription::Suspend()
{
    iTimer->Cancel();
    iSuspended = true;
    if (StartSchedule(eUnsubscribe, false)) {
        iDevice.GetCpStack().SubscriptionManager().ScheduleLocked(*this);
    }
}

TBool CpiSubscription::RemoveOnSubnetChange() const
{
    return iDevice.OrphanSubscriptionsOnSubnetChange();
}

void CpiSubscription::EventUpdateStart()
{
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
}

void CpiSubscription::EventUpdateError()
{
    LOG_ERROR(kEvent, "ERROR: subscription (%p) sid %.*s failure processing update\n", this, PBUF(iSid));
    SetNotificationError();
    if (iEventProcessor != NULL) {
        iEventProcessor->EventUpdateError();
    }
}

void CpiSubscription::EventUpdatePrepareForDelete()
{
    if (iEventProcessor != NULL) {
        iEventProcessor->EventUpdatePrepareForDelete();
    }
}

void CpiSubscription::ListObjectDetails() const
{
    const Brx& udn = iDevice.Udn();
    Log::Print("  CpiSubscription: addr=%p, device=%.*s, refCount=%u, sid=%.*s\n",
               this, PBUF(udn), iRefCount, PBUF(iSid));
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
    LOG_ERROR(kEvent, "Error - %s - from (%p) SID ", aErr, iSubscription);
    if (iSubscription->Sid().Bytes() > 0) {
        LOG_ERROR(kEvent, iSubscription->Sid());
    }
    else {
        LOG_ERROR(kEvent, "(null)");
    }
    LOG_ERROR(kEvent, "\n");
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
        catch (UriError&) {
            Error("Uri");
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

CpiSubscriptionManager::CpiSubscriptionManager(CpStack& aCpStack)
    : Thread("CpSubscriptionMgr")
    , iCpStack(aCpStack)
    , iLock("SBSL")
    , iFree(aCpStack.Env().InitParams()->NumSubscriberThreads())
    , iWaiter("SBSS", 0)
    , iShutdownSem("SBMS", 0)
    , iInterface(kTIpAddressEmpty)
    , iNextSubscriptionId(1)
{
    NetworkAdapterList& ifList = iCpStack.Env().NetworkAdapterList();
    AutoNetworkAdapterRef ref(aCpStack.Env(), "CpiSubscriptionManager ctor");
    const NetworkAdapter* currentInterface = ref.Adapter();
    Functor functor = MakeFunctor(*this, &CpiSubscriptionManager::CurrentNetworkAdapterChanged);
    iInterfaceListListenerId = ifList.AddCurrentChangeListener(functor, "CpiSubscriptionManager-current");
    functor = MakeFunctor(*this, &CpiSubscriptionManager::SubnetListChanged);
    iSubnetListenerId = ifList.AddSubnetListChangeListener(functor, "CpiSubscriptionManager-subnet");
    iCpStack.Env().AddSuspendObserver(*this);
    iCpStack.Env().AddResumeObserver(*this);
    if (currentInterface == NULL) {
        iEventServer = NULL;
    }
    else {
        iLock.Wait();
        iInterface = currentInterface->Address();
        iEventServer = new EventServerUpnp(iCpStack, iInterface);
        iLock.Signal();
    }

    const TUint numThreads = iCpStack.Env().InitParams()->NumSubscriberThreads();
    iSubscribers = (Subscriber**)malloc(sizeof(*iSubscribers) * numThreads);
    for (TUint i=0; i<numThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("Subscriber %d", i);
        thName.PtrZ();
        iSubscribers[i] = new Subscriber((const TChar*)thName.Ptr(), iFree);
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
    iCpStack.Env().RemoveSuspendObserver(*this);
    iCpStack.Env().RemoveResumeObserver(*this);
    TBool wait = !ReadyForShutdown();
    iShutdownSem.Clear();
    iLock.Signal();
    if (wait) {
        // wait 1 minute then proceed
        // we'll have leaked some subscriptions but this'll be logged later during shutdown
        iCleanShutdown = true;
        Timer timer(iCpStack.Env(), MakeFunctor(*this, &CpiSubscriptionManager::ShutdownHasHung), "SubscriptionManagerShutdown");
        timer.FireIn(60*1000);
        iShutdownSem.Wait();
        if (iCleanShutdown) {
            timer.Cancel();
        }
        else {
            Log::Print("WARNING: Subscription manager failed to shutdown cleanly\n");
            iCpStack.Env().ListObjects();
        }
    }

    Kill();
    Join();

    for (TUint i=0; i<iCpStack.Env().InitParams()->NumSubscriberThreads(); i++) {
        delete iSubscribers[i];
    }
    free(iSubscribers);

    iCpStack.Env().NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListenerId);
    iCpStack.Env().NetworkAdapterList().RemoveCurrentChangeListener(iInterfaceListListenerId);
    delete iEventServer;

    LOG(kEvent, "< ~CpiSubscriptionManager()\n");
}

CpiSubscription* CpiSubscriptionManager::NewSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType)
{
    iLock.Wait();
    const TUint id = iNextSubscriptionId++;
    CpiSubscription* subscription = new CpiSubscription(aDevice, aEventProcessor, aServiceType, id);
    iMap.insert(std::pair<TUint,CpiSubscription*>(id, subscription));
    iLock.Signal();
    subscription->Schedule(CpiSubscription::eSubscribe);
    return subscription;
}

CpiSubscription* CpiSubscriptionManager::FindSubscription(TUint aId)
{
    AutoMutex a(iLock);
    std::map<TUint,CpiSubscription*>::iterator it = iMap.find(aId);
    if (it == iMap.end()) {
        return NULL;
    }
    CpiSubscription* subscription = it->second;
    subscription->AddRef();
    return subscription;
}

CpiSubscription* CpiSubscriptionManager::FindSubscription(const Brx& aSid)
{
    AutoMutex a(iLock);
    CpiSubscription* subscription = NULL;
    for (std::map<TUint,CpiSubscription*>::iterator it=iMap.begin(); it!=iMap.end(); ++it) {
        if (it->second->Sid() == aSid) {
            subscription = it->second;
            subscription->AddRef();
            break;
        }
    }
    return subscription;
}

void CpiSubscriptionManager::Remove(CpiSubscription& aSubscription)
{
    iLock.Wait();
    RemoveLocked(aSubscription);
    TBool shutdownSignal = ReadyForShutdown();
    iLock.Signal();
    if (shutdownSignal) {
        iShutdownSem.Signal();
    }
}

void CpiSubscriptionManager::RemoveLocked(CpiSubscription& aSubscription)
{
    std::map<TUint,CpiSubscription*>::iterator it = iMap.find(aSubscription.Id());
    if (it != iMap.end()) {
        it->second = NULL;
        iMap.erase(it);
    }
}

void CpiSubscriptionManager::Schedule(CpiSubscription& aSubscription)
{
    iLock.Wait();
    ScheduleLocked(aSubscription);
    iLock.Signal();
}

void CpiSubscriptionManager::ScheduleLocked(CpiSubscription& aSubscription)
{
    ASSERT(iActive);
    iList.push_back(&aSubscription);
    Signal();
}

TUint CpiSubscriptionManager::EventServerPort()
{
    AutoMutex a(iLock);
    EventServerUpnp* server = iEventServer;
    if (server == NULL) {
        THROW(ReaderError);
    }
    return server->Port();
}

void CpiSubscriptionManager::RenewAll()
{
    AutoMutex a(iLock);
    std::map<TUint,CpiSubscription*>::iterator it = iMap.begin();
    while (it != iMap.end()) {
        it->second->Resubscribe();
        it++;
    }
}

void CpiSubscriptionManager::NotifySuspended()
{
    AutoMutex a(iLock);
    std::map<TUint,CpiSubscription*>::iterator it = iMap.begin();
    while (it != iMap.end()) {
        it->second->Suspend();
        it++;
    }
}

void CpiSubscriptionManager::NotifyResumed()
{
    /* sockets are unusable on iOS when we resume so we need to perform as same actions
       as when we change address within the current subnet */
    HandleInterfaceChange(false);

    AutoMutex a(iLock);
    std::map<TUint,CpiSubscription*>::iterator it = iMap.begin();
    while (it != iMap.end()) {
        it->second->iSuspended = false;
        it++;
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

void CpiSubscriptionManager::HandleInterfaceChange(TBool aNewSubnet)
{
    LOG(kEvent, "> CpiSubscriptionManager::HandleInterfaceChange(%d)\n", aNewSubnet);
    iLock.Wait();
    AutoNetworkAdapterRef ref(iCpStack.Env(), "CpiSubscriptionManager::HandleInterfaceChange");
    const NetworkAdapter* currentInterface = ref.Adapter();
    if (aNewSubnet) {
        if (currentInterface != NULL && TIpAddressUtils::Equal(currentInterface->Address(), iInterface)) {
            iLock.Signal();
            return;
        }
        size_t count = iMap.size();
        while (count-- > 0) {
            CpiSubscription* subscription = iMap.begin()->second;
            if (subscription->RemoveOnSubnetChange()) {
                RemoveLocked(*subscription);
                subscription->NotifySubnetChanged();
            }
        }
    }
    /* Don't try to migrate subscriptions here if !aNewSubnet - this causes a race between
       recreating the event server below and the resubscribes being scheduled in another thread */
    EventServerUpnp* server = iEventServer;
    iEventServer = NULL;
    iLock.Signal();

    // recreate the event server on the new interface
    delete server;
    if (currentInterface == NULL) {
        iInterface = kTIpAddressEmpty;
    }
    else {
        iInterface = currentInterface->Address();
        iEventServer = new EventServerUpnp(iCpStack, iInterface);
    }
    if (!aNewSubnet) {
        /* device lists may not signal that devices have been removed
           ...so we need to try to migrate existing subscriptions */
        RenewAll();
    }
    LOG(kEvent, "< CpiSubscriptionManager::HandleInterfaceChange(%d)\n", aNewSubnet);
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

void CpiSubscriptionManager::ShutdownHasHung()
{
    iCleanShutdown = false;
    iShutdownSem.Signal();
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
