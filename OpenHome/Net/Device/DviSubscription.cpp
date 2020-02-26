#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>

#include <vector>
#include <stdlib.h>
#include <stdint.h>

using namespace OpenHome;
using namespace OpenHome::Net;


TBool SidComparison(const DviSubscription* aSubscription1, const DviSubscription* aSubscription2)
{
    return BufferCmp()(aSubscription1->Sid(), aSubscription2->Sid());
}

// AutoPropertiesLock

class AutoPropertiesLock : INonCopyable
{
public:
    AutoPropertiesLock(DviService& aService);
    ~AutoPropertiesLock();
private:
    DviService& iService;
};

AutoPropertiesLock::AutoPropertiesLock(DviService& aService)
    : iService(aService)
{
    iService.PropertiesLock();
}

AutoPropertiesLock::~AutoPropertiesLock()
{
    iService.PropertiesUnlock();
}


// DviSubscription

DviSubscription::DviSubscription(DvStack& aDvStack, DviDevice& aDevice, IPropertyWriterFactory& aWriterFactory,
                                 IDviSubscriptionUserData* aUserData, Brh& aSid)
    : iDvStack(aDvStack)
    , iLock("DSb1")
    , iRefLock("DSb2")
    , iRefCount(1)
    , iDevice(aDevice)
    , iWriterFactory(aWriterFactory)
    , iUserData(aUserData)
    , iService(NULL)
    , iSequenceNumber(0)
    , iPublisherFailures(0)
    , iPublisherSuccesses(0)
    , iPublisherQueue(NULL)
    , iExpired(false)
{
    iDevice.AddWeakRef();
    aSid.TransferTo(iSid);
    iWriterFactory.NotifySubscriptionCreated(iSid);
    Functor functor = MakeFunctor(*this, &DviSubscription::Expired);
    iTimer = new Timer(iDvStack.Env(), functor, "DviSubscription");
    iDvStack.Env().AddObject(this);
}

void DviSubscription::SetDuration(TUint& aDurationSecs)
{
    DoRenew(aDurationSecs);
}

void DviSubscription::Start(DviService& aService)
{
    iService = &aService;
    iService->AddRef();
    const std::vector<Property*>& properties = iService->Properties();
    for (TUint i=0; i<properties.size(); i++) {
        // store all seq nums as 0 initially to ensure all are published by the first call to WriteChanges()
        iPropertySequenceNumbers.push_back(0);
        if (properties[i]->SequenceNumber() == 0) {
            const Brx& service = iService->ServiceType().Name();
            const Brx& propName = properties[i]->Parameter().Name();
            const Brx& udn = iDevice.Udn();
            Log::Print("ERROR: uninitialised property.  Provider: %.*s, property: %.*s, device: %.*s\n", PBUF(service), PBUF(propName), PBUF(udn));
            ASSERTS();
        }
    }
}

void DviSubscription::Stop()
{
    iTimer->Cancel();
    iLock.Wait();
    if (iService != NULL) {
        iService->RemoveRef();
        iService = NULL;
    }
    iLock.Signal();
    iWriterFactory.NotifySubscriptionExpired(iSid);
}

void DviSubscription::AddRef()
{
    AutoMutex _(iRefLock);
    iRefCount++;
}

TBool DviSubscription::TryAddRef()
{
    TBool added = false;
    iRefLock.Wait();
    if (iRefCount != 0) {
        iRefCount++;
        added = true;
    }
    iRefLock.Signal();
    return added;
}

void DviSubscription::RemoveRef()
{
    iRefLock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    iRefLock.Signal();
    if (dead) {
        delete this;
    }
}

void DviSubscription::Remove()
{
    iLock.Wait();
    DviService* service = iService;
    if (service != NULL) {
        service->AddRef();
    }
    iLock.Signal();
    if (service != NULL) {
        service->RemoveSubscription(iSid);
        service->RemoveRef();
    }
}

void DviSubscription::Renew(TUint& aSeconds)
{
    iLock.Wait();
    TBool expired = (iService == NULL);
    iLock.Signal();
    if (expired) {
        THROW(DvSubscriptionError);
    }
    DoRenew(aSeconds);
}

void DviSubscription::DoRenew(TUint& aSeconds)
{
    const TUint maxDuration = iDvStack.Env().InitParams()->DvMaxUpdateTimeSecs();
    if (aSeconds == 0 || aSeconds > maxDuration) {
        aSeconds = maxDuration;
    }
    iTimer->FireIn(aSeconds * 1000);
}

void DviSubscription::WriteChanges()
{
    if (iExpired) {
        // reads/writes of iExpired assumed not to require thread safety
        // ...if this later turns out wrong, DO NOT USE iLock to protect iExpired - it'll deadlock with TimeManager's lock
        LOG_DEBUG(kDvEvent, "Subscription %.*s has expired. Don't publish changes\n", PBUF(iSid));
        Remove();
        return;
    }
    IPropertyWriter* writer = NULL;
    try {
        AutoMutex a(iLock); // claim lock here to fully serialise updates to a single subscriber
        writer = CreateWriter();
        if (writer != NULL) {
            writer->PropertyWriteEnd();
        }
    }
    catch (AssertionFailed&) {
        throw;
    }
    catch (NetworkTimeout&) {
        iWriterFactory.ReleaseWriter(writer);
        throw;
    }
    catch (Exception& ex) {
        LOG_ERROR(kDvEvent, "Exception - %s - eventing update for %.*s\n", ex.Message(), PBUF(iSid));
        /* For cases when NetworkTimeout is not the cause of a failure, its reasonable
         * to assume that later attempts are also likely to fail, so its better if we
         * don't keep blocking and instead remove the subscription */
        iExpired = true;
        Remove();
    }
    if (writer != NULL) {
        iWriterFactory.ReleaseWriter(writer);
    }
}

IPropertyWriter* DviSubscription::CreateWriter()
{
    LOG_DEBUG(kDvEvent, "WriteChanges for subscription %.*s seq - %u\n", PBUF(iSid), iSequenceNumber);

    if (iService == NULL) {
        LOG_DEBUG(kDvEvent, "Subscription stopped; don't publish changes\n");
        return NULL;
    }

    const std::vector<Property*>& properties = iService->Properties();
    ASSERT(properties.size() == iPropertySequenceNumbers.size()); // services can't change definition after first advertisement
    TBool changed = false;
    {
        AutoPropertiesLock b(*iService);
        for (TUint i=0; i<properties.size(); i++) {
            Property* prop = properties[i];
            const TUint seq = prop->SequenceNumber();
            ASSERT(seq != 0); // => implementor hasn't initialised the property
            if (seq != iPropertySequenceNumbers[i]) {
                changed = true;
                break;
            }
        }

    }
    if (!changed) {
        LOG_DEBUG(kDvEvent, "Found no changes to publish for %.*s\n", PBUF(iSid));
        return NULL;
    }
    IPropertyWriter* writer = iWriterFactory.ClaimWriter(iUserData, iSid, iSequenceNumber);
    if (writer == NULL) {
        THROW(WriterError);
    }
    if (iSequenceNumber == UINT32_MAX) {
        iSequenceNumber = 1;
    }
    else {
        iSequenceNumber++;
    }

    AutoPropertiesLock b(*iService);
    for (TUint i=0; i<properties.size(); i++) {
        Property* prop = properties[i];
        const TUint seq = prop->SequenceNumber();
        if (seq != iPropertySequenceNumbers[i]) {
            prop->Write(*writer);
            iPropertySequenceNumbers[i] = seq;
        }
    }
    return writer;
}

const Brx& DviSubscription::Sid() const
{
    return iSid;
}

DviService* DviSubscription::Service()
{
    AutoMutex _(iLock);
    return ServiceLocked();
}

DviService* DviSubscription::ServiceLocked()
{
    if (iService != NULL) {
        iService->AddRef();
    }
    return iService;
}

void DviSubscription::Log(IWriter& aWriter)
{
    AutoMutex _(iLock);

    aWriter.Write(Brn("sid: "));
    aWriter.Write(iSid);

    aWriter.Write(Brn(", service: "));
    if (iService == NULL) {
        aWriter.Write(Brn(""));
    }
    else {
        aWriter.Write(iService->ServiceType().Name());
    }

    aWriter.Write(Brn(", seq: "));
    Bws<Ascii::kMaxUintStringBytes> seqBuf;
    (void)Ascii::AppendDec(seqBuf, iSequenceNumber);
    aWriter.Write(seqBuf);

    aWriter.Write(Brn(", publisher failures: "));
    Bws<Ascii::kMaxUintStringBytes> publishBuf;
    (void)Ascii::AppendDec(publishBuf, iPublisherFailures);
    aWriter.Write(publishBuf);
    static const Brn kQuick(" - quick queue");
    static const Brn kSlow(" - slow queue");
    aWriter.Write(iPublisherFailures ? kSlow : kQuick);

    aWriter.Write(Brn(", expired: "));
    static const Brn kTrue("true");
    static const Brn kFalse("false");
    aWriter.Write(iExpired? kTrue : kFalse);

    iWriterFactory.LogUserData(aWriter, *iUserData);
}

void DviSubscription::ListObjectDetails() const
{
    Log::Print("  DviSubscription: addr=%p, serviceType=", this);
    if (iService != NULL) {
        Log::Print(iService->ServiceType().FullName());
    }
    else {
        Log::Print("%s", "NULL");
    }
    Log::Print(", sid=");
    Log::Print(iSid);
    Log::Print(", refCount=%u, seqNum=%u\n", iRefCount, iSequenceNumber);
}

DviSubscription::~DviSubscription()
{
    iLock.Wait();
    if (iService != NULL) {
        iService->RemoveRef();
    }
    iLock.Signal();
    iWriterFactory.NotifySubscriptionDeleted(iSid);
    iDevice.RemoveWeakRef();
    delete iTimer;
    if (iUserData != NULL) {
        iUserData->Release();
    }
    iDvStack.Env().RemoveObject(this);
}

void DviSubscription::Expired()
{
    LOG(kDvEvent, "Subscription %.*s expired\n", PBUF(iSid));
    iExpired = true;
    // reads/writes of iExpired assumed not to require thread safety
    // ...if this later turns out wrong, DO NOT USE iLock to protect iExpired - it'll deadlock with TimeManager's lock

    /* can't call iService->RemoveSubscription from this thread as we'd then take TimerManager/DviSubscription
       locks in the opposite order to Publisher threads.
       Instead, queue an update; this will happen on a Publisher thread where the subscription can safely be removed. */
    iDvStack.SubscriptionManager().QueueUpdate(*this);
}


// AutoSubscriptionRef

AutoSubscriptionRef::AutoSubscriptionRef(DviSubscription& aSubscription)
    : iSubscription(aSubscription)
{
}

AutoSubscriptionRef::~AutoSubscriptionRef()
{
    iSubscription.RemoveRef();
}


// PropertyWriter

PropertyWriter::PropertyWriter()
    : iWriter(NULL)
{
}

void PropertyWriter::SetWriter(IWriter& aWriter)
{
    iWriter = &aWriter;
}

void PropertyWriter::WriteVariable(IWriter& aWriter, const Brx& aName, const Brx& aValue)
{ // static
    WriteVariableStart(aWriter, aName);
    aWriter.Write(aValue);
    WriteVariableEnd(aWriter, aName);
}

void PropertyWriter::WriteVariableStart(IWriter& aWriter, const Brx& aName)
{ // static
    static const Brn kPropertyStart("<e:property><");
    aWriter.Write(kPropertyStart);
    aWriter.Write(aName);
    aWriter.Write('>');
}

void PropertyWriter::WriteVariableEnd(IWriter& aWriter, const Brx& aName)
{ // static
    static const Brn kPropertyEnd("></e:property>");
    aWriter.Write(Brn("</"));
    aWriter.Write(aName);
    aWriter.Write(kPropertyEnd);
}

inline void PropertyWriter::WriteVariable(const Brx& aName, const Brx& aValue)
{
    ASSERT(iWriter != NULL);
    WriteVariable(*iWriter, aName, aValue);
}

inline void PropertyWriter::WriteVariableStart(const Brx& aName)
{
    ASSERT(iWriter != NULL);
    WriteVariableStart(*iWriter, aName);
}

inline void PropertyWriter::WriteVariableEnd(const Brx& aName)
{
    WriteVariableEnd(*iWriter, aName);
}

void PropertyWriter::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    WriteVariableStart(aName);
    Converter::ToXmlEscaped(*iWriter, aValue);
    WriteVariableEnd(aName);
}

void PropertyWriter::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    PropertyWriteUint(aName, (aValue? 1 : 0));
}

void PropertyWriter::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    WriteVariableStart(aName);
    Converter::ToBase64(*iWriter, aValue);
    WriteVariableEnd(aName);
}


// Publisher

Publisher::Publisher(const TChar* aName, TUint aPriority, IPublisherObserver& aObserver, Fifo<Publisher*>& aFree, TUint aModerationMs)
    : Thread(aName, aPriority)
    , iObserver(aObserver)
    , iFree(aFree)
    , iModerationMs(aModerationMs)
    , iModerator("PBMS", 0)
{
}

Publisher::~Publisher()
{
    Kill();
    Join();
}

void Publisher::Publish(DviSubscription* aSubscription)
{
    iSubscription = aSubscription;
    Signal();
}

#ifdef DEFINE_TRACE
void Publisher::Error(const TChar* aErr)
#else
void Publisher::Error(const TChar* /*aErr*/)
#endif
{
    LOG_ERROR(kDvEvent, "Error - %s - from SID ", aErr);
    LOG_ERROR(kDvEvent, iSubscription->Sid());
    LOG_ERROR(kDvEvent, "\n");
}

void Publisher::Run()
{
    for (;;) {
        Wait();
        TBool timeout = false;
        try {
            iSubscription->WriteChanges();
        }
        catch (NetworkTimeout& ex) {
            Error(ex.Message());
            iObserver.NotifyPublishError(*iSubscription);
            timeout = true;
        }
        catch (Exception& ex) {
            Error(ex.Message());
        }

        if (!timeout) {
            iObserver.NotifyPublishSuccess(*iSubscription);
        }
        iSubscription->RemoveRef();
        if (iModerationMs > 0) {
            try {
                iModerator.Wait(iModerationMs);
            }
            catch (Timeout&) {}
        }
        iFree.Write(this);
    }
}

// PublisherPool

PublisherPool::PublisherPool(const TChar* aName, TUint aPriority, IPublisherObserver& aObserver,
                             TUint aNumPublisherThreads, TUint aPoolNumber, TUint aModerationMs)
    : Thread(aName, aPriority)
    , iNumPublishers(aNumPublisherThreads)
    , iFree(aNumPublisherThreads)
    , iLock("DVPP")
{
    LOG_DEBUG(kDvEvent, "> PublisherPool %u: creating %u publisher threads\n", aPoolNumber, iNumPublishers);
    iPublishers = (Publisher**)malloc(sizeof(*iPublishers) * iNumPublishers);

    for (TUint i=0; i<iNumPublishers; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("Publisher %d:%d\n", aPoolNumber, i);
        thName.PtrZ();
        iPublishers[i] = new Publisher((const TChar*)thName.Ptr(), aPriority, aObserver, iFree, aModerationMs);
        iFree.Write(iPublishers[i]);
        iPublishers[i]->Start();
    }
    Start();
}

std::list<DviSubscription*> PublisherPool::GetUpdates()
{
    AutoMutex amx(iLock);
    return iPendingUpdates;
}

void PublisherPool::QueueUpdate(DviSubscription& aSubscription)
{
    iLock.Wait();
    iPendingUpdates.push_back(&aSubscription);
    Signal();
    iLock.Signal();
}

void PublisherPool::Run()
{
    for (;;) {
        Wait();
        Publisher* publisher = iFree.Read();
        iLock.Wait();
        DviSubscription* subscription = iPendingUpdates.front();
        iPendingUpdates.pop_front();
        iLock.Signal();
        publisher->Publish(subscription);
    }
}

PublisherPool::~PublisherPool()
{
    iLock.Wait();
    Kill();
    Join();
    iLock.Signal();
    for (TUint i=0; i<iNumPublishers; i++) {
        delete iPublishers[i];
    }
    free(iPublishers);
    for (std::list<DviSubscription*>::iterator it = iPendingUpdates.begin(); it != iPendingUpdates.end(); ++it) {
        (*it)->RemoveRef();
    }
}


// DviSubscriptionManager

const Brn DviSubscriptionManager::kQuerySubscriptions("subscriptions");

DviSubscriptionManager::DviSubscriptionManager(DvStack& aDvStack, TUint aPriority)
    : iDvStack(aDvStack)
    , iLock("DSBM")
    , iCount(0)
{
    IInfoAggregator* infoAggregator = iDvStack.Env().InfoAggregator();
    if (infoAggregator != NULL) {
        std::vector<Brn> queries;
        queries.push_back(kQuerySubscriptions);
        infoAggregator->Register(*this, queries);
    }
    InitialisationParams* initParams = iDvStack.Env().InitParams();
    const TUint numPublisherThreads = initParams->DvNumPublisherThreads();
    const TUint moderationMs = initParams->DvPublisherModerationTimeMs();
    Brn quickPoolThName("DviPublisherPool1");
    Brn slowPoolThName("DviPublisherPool2");
    iPublishersQuick = new PublisherPool((const TChar*)quickPoolThName.Ptr(), aPriority, *this, numPublisherThreads, 1, moderationMs);
    iPublishersSlow = new PublisherPool((const TChar*)slowPoolThName.Ptr(), aPriority, *this, numPublisherThreads, 2, moderationMs);
}

DviSubscriptionManager::~DviSubscriptionManager()
{
    LOG_DEBUG(kDvEvent, "> ~DviSubscriptionManager\n");
    delete iPublishersQuick;
    delete iPublishersSlow;
    LOG_DEBUG(kDvEvent, "< ~DviSubscriptionManager\n");
}

void DviSubscriptionManager::AddSubscription(DviSubscription& aSubscription)
{
    iLock.Wait();
    Brn sid(aSubscription.Sid());
    iMap.insert(std::pair<Brn,DviSubscription*>(sid, &aSubscription));
    aSubscription.iPublisherQueue = iPublishersQuick;
    aSubscription.AddRef();
    iCount++;
    iLock.Signal();
}

void DviSubscriptionManager::RemoveSubscription(DviSubscription& aSubscription)
{
    iLock.Wait();
    Brn sid(aSubscription.Sid());
    Map::iterator it = iMap.find(sid);
    if (it != iMap.end()) {
        it->second->RemoveRef();
        iMap.erase(it);
    }
    iLock.Signal();
}

DviSubscription* DviSubscriptionManager::Find(const Brx& aSid)
{
    DviSubscription* subs = NULL;
    iLock.Wait();
    Brn sid(aSid);
    Map::iterator it = iMap.find(sid);
    if (it != iMap.end()) {
        subs = it->second;
        subs->AddRef();
    }
    iLock.Signal();
    return subs;
}

void DviSubscriptionManager::QueueUpdate(DviSubscription& aSubscription)
{
    aSubscription.AddRef();
    iLock.Wait();
    aSubscription.iPublisherQueue->QueueUpdate(aSubscription);
    iLock.Signal();
}

void DviSubscriptionManager::NotifyPublishSuccess(DviSubscription& aSubscription)
{
    aSubscription.iPublisherFailures = 0;
    if (++aSubscription.iPublisherSuccesses == kPublisherSuccessThreshold && aSubscription.iPublisherQueue == iPublishersSlow) {
        LOG_INFO(kDvEvent, "DviSubscriptionManager - %u successful publishes, moving to quick queue. SID is %.*s\n"
                    , kPublisherSuccessThreshold, PBUF(aSubscription.Sid()));
        aSubscription.iPublisherQueue = iPublishersQuick;
    }
}

void DviSubscriptionManager::NotifyPublishError(DviSubscription& aSubscription)
{
    aSubscription.iPublisherSuccesses = 0;
    aSubscription.iPublisherFailures++;
    LOG_INFO(kDvEvent, "DviSubscriptionManager - Publishing Failure %u of %u. SID is %.*s\n",
              aSubscription.iPublisherFailures, kMaxFailures, PBUF(aSubscription.Sid()));
    if (aSubscription.iPublisherFailures == 1) {
        aSubscription.iPublisherQueue = iPublishersSlow;
    }
    else if (aSubscription.iPublisherFailures == kMaxFailures) {
        LOG_ERROR(kDvEvent, "DviSubscriptionManager - Publisher Max Failures: Removing SID %.*s\n", PBUF(aSubscription.Sid()));
        aSubscription.iExpired = true;
    }
}

void DviSubscriptionManager::QueryInfo(const Brx& aQuery, IWriter& aWriter)
{
    if (aQuery != kQuerySubscriptions) {
        return;
    }
    AutoMutex _(iLock);
    Map::iterator it;
    Bws<80> summary;
    summary.AppendPrintf("Subscriptions: %u current, %u since startup\n", iMap.size(), iCount);
    aWriter.Write(summary);
    aWriter.Write(Brn("Current:"));
    for (it=iMap.begin(); it!=iMap.end(); ++it) {
        aWriter.Write(Brn("\n\t"));
        it->second->Log(aWriter);
    }
    aWriter.Write(Brn("\n\nPending updates:"));
    std::list<DviSubscription*>::iterator it2;
    iAllPendingUpdates = iPublishersQuick->GetUpdates();
    std::list<DviSubscription*> slowUpdates = iPublishersSlow->GetUpdates();
    iAllPendingUpdates.merge(slowUpdates, SidComparison);
    for (it2=iAllPendingUpdates.begin(); it2!=iAllPendingUpdates.end(); ++it2) {
        aWriter.Write(Brn("\n\t"));
        it->second->Log(aWriter);
    }
    aWriter.Write(Brn("\n"));
}
