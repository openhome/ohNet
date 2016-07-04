#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Converter.h>

#include <vector>
#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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
    , iLock("MDSB")
    , iRefCount(1)
    , iDevice(aDevice)
    , iWriterFactory(aWriterFactory)
    , iUserData(aUserData)
    , iService(NULL)
    , iSequenceNumber(0)
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
            Log::Print("ERROR: uninitialised property.  Provider: ");
            Log::Print(iService->ServiceType().Name());
            Log::Print(", property: ");
            Log::Print(properties[i]->Parameter().Name());
            Log::Print("\n");
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
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRefCount++;
    lock.Signal();
}

TBool DviSubscription::TryAddRef()
{
    TBool added = false;
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    if (iRefCount != 0) {
        iRefCount++;
        added = true;
    }
    lock.Signal();
    return added;
}

void DviSubscription::RemoveRef()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    lock.Signal();
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
    catch(NetworkTimeout&) {
        // we may block a publisher for a relatively long time failing to connect
        // its reasonable to assume that later attempts are also likely to fail
        // ...so its better if we don't keep blocking and instead remove the subscription
        LOG2(kDvEvent, kError, "Timeout eventing update for %.*s\n", PBUF(iSid));
        Remove();
    }
    catch(NetworkError&) {}
    catch(HttpError&) {}
    catch(WriterError&) {}
    catch(ReaderError&) {}
    if (writer != NULL) {
        writer->Release();
    }
}

IPropertyWriter* DviSubscription::CreateWriter()
{
    LOG(kDvEvent, "WriteChanges for subscription %.*s seq - %u\n", PBUF(iSid), iSequenceNumber);
    if (!iDevice.Enabled()) {
        LOG(kDvEvent, "Device disabled; defer publishing changes\n");
        return NULL;
    }

    if (iService == NULL) {
        LOG(kDvEvent, "Subscription stopped; don't publish changes\n");
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
        LOG(kDvEvent, "Found no changes to publish\n");
        return NULL;
    }
    IPropertyWriter* writer = iWriterFactory.CreateWriter(iUserData, iSid, iSequenceNumber);
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
    iExpired = true;
    // reads/writes of iExpired assumed not to require thread safety
    // ...if this later turns out wrong, DO NOT USE iLock to protect iExpired - it'll deadlock with TimeManager's lock
    
    /* can't call iService->RemoveSubscription from this thread as we'd then take TimerManager/DviSubscription
       locks in the opposite order to Publisher threads.
       Instead, queue an update; this will happen on a Publisher thread where the subscription can safely be removed. */
    iDvStack.SubscriptionManager().QueueUpdate(*this);
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
    aWriter.Write(Brn("<e:property>"));
    aWriter.Write('<');
    aWriter.Write(aName);
    aWriter.Write('>');
    aWriter.Write(aValue);
    aWriter.Write(Brn("</"));
    aWriter.Write(aName);
    aWriter.Write('>');
    aWriter.Write(Brn("</e:property>"));
}

void PropertyWriter::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToXmlEscaped(writer, aValue);
    Brh buf;
    writer.TransferTo(buf);
    WriteVariable(aName, buf);
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
    WriterBwh writer(1024);
    Converter::ToBase64(writer, aValue);
    Brh buf;
    writer.TransferTo(buf);
    WriteVariable(aName, buf);
}

void PropertyWriter::Release()
{
    delete this;
}

void PropertyWriter::WriteVariable(const Brx& aName, const Brx& aValue)
{
    ASSERT(iWriter != NULL);
    WriteVariable(*iWriter, aName, aValue);
}


// Publisher

Publisher::Publisher(const TChar* aName, Fifo<Publisher*>& aFree)
    : Thread(aName)
    , iFree(aFree)
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
    LOG2(kDvEvent, kError, "Error - %s - from SID ", aErr);
    LOG2(kDvEvent, kError, iSubscription->Sid());
    LOG2(kDvEvent, kError, "\n");
}

void Publisher::Run()
{
    for (;;) {
        Wait();
        try {
            iSubscription->WriteChanges();
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

        iSubscription->RemoveRef();
        iFree.Write(this);
    }
}


// DviSubscriptionManager

DviSubscriptionManager::DviSubscriptionManager(DvStack& aDvStack)
    : Thread("DvSubscriptionMgr")
    , iDvStack(aDvStack)
    , iLock("DSBM")
    , iFree(aDvStack.Env().InitParams()->DvNumPublisherThreads())
{
    const TUint numPublisherThreads = iDvStack.Env().InitParams()->DvNumPublisherThreads();
    LOG(kDvEvent, "> DviSubscriptionManager: creating %u publisher threads\n", numPublisherThreads);
    iPublishers = (Publisher**)malloc(sizeof(*iPublishers) * numPublisherThreads);
    for (TUint i=0; i<numPublisherThreads; i++) {
        Bws<Thread::kMaxNameBytes+1> thName;
        thName.AppendPrintf("Publisher %d", i);
        thName.PtrZ();
        iPublishers[i] = new Publisher((const TChar*)thName.Ptr(), iFree);
        iFree.Write(iPublishers[i]);
        iPublishers[i]->Start();
    }
    Start();
}

DviSubscriptionManager::~DviSubscriptionManager()
{
    LOG(kDvEvent, "> ~DviSubscriptionManager\n");

    iLock.Wait();
    Kill();
    Join();
    iLock.Signal();

    const TUint numPublisherThreads = iDvStack.Env().InitParams()->DvNumPublisherThreads();
    for (TUint i=0; i<numPublisherThreads; i++) {
        delete iPublishers[i];
    }
    free(iPublishers);

    for (std::list<DviSubscription*>::iterator it = iList.begin(); it != iList.end(); ++it) {
        (*it)->RemoveRef();
    }

    LOG(kDvEvent, "< ~DviSubscriptionManager\n");
}

void DviSubscriptionManager::AddSubscription(DviSubscription& aSubscription)
{
    iLock.Wait();
    Brn sid(aSubscription.Sid());
    iMap.insert(std::pair<Brn,DviSubscription*>(sid, &aSubscription));
    aSubscription.AddRef();
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
    iList.push_back(&aSubscription);
    Signal();
    iLock.Signal();
}

void DviSubscriptionManager::Run()
{
    for (;;) {
        Wait();
        Publisher* publisher = iFree.Read();
        iLock.Wait();
        DviSubscription* subscription = iList.front();
        iList.pop_front();
        iLock.Signal();
        publisher->Publish(subscription);
    }
}
