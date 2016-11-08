#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// ProxyError

ProxyError::ProxyError()
    : Exception("")
    , iLevel(0)
    , iCode(0)
{
}

ProxyError::ProxyError(const TChar* aFile, TUint aLine, uint32_t aLevel, uint32_t aCode)
    : Exception("", aFile, aLine)
    , iLevel(aLevel)
    , iCode(aCode)
{
}

TUint ProxyError::Level() const
{
    return iLevel;
}

uint32_t ProxyError::Code() const
{
    return iCode;
}

ProxyError::ProxyError(const ProxyError& aProxyError)
    : Exception(aProxyError)
{
    iLevel = aProxyError.Level();
    iCode = aProxyError.Code();
}

ProxyError& ProxyError::operator=(const ProxyError& aProxyError)
{
    if (this != &aProxyError) {
        Exception::operator=(aProxyError);
        iLevel = aProxyError.Level();
        iCode = aProxyError.Code();
    }
    return *this;
}


// CpProxy

void CpProxy::Subscribe()
{
    if (iProperties.size() == 0) {
        THROW(SubscriptionErrorUnrecoverable);
    }
    if (iInitialEventLock == NULL) {
        iInitialEventLock = new OpenHome::Mutex("PRX4");
    }
    iLock->Wait();
    iCpSubscriptionStatus = eSubscribing;
    if (!iService->Subscribe(*this)) {
        iCpSubscriptionStatus = eNotSubscribed;
    }
    iLock->Signal();
}

void CpProxy::Unsubscribe()
{
    iLock->Wait();
    iCpSubscriptionStatus = eNotSubscribed;
    iLock->Signal();
    iService->Unsubscribe();
    iLock->Wait();
    iInitialEventDelivered = false;
    PropertyMap::iterator it = iProperties.begin();
    while (it != iProperties.end()) {
        it->second->ResetSequenceNumber();
        it++;
    }
    iLock->Signal();
}

CpProxy::CpProxy(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice)
    : iInvocable(aDevice)
{
    iService = new CpiService(aDomain, aName, aVersion, aDevice);
    iCpSubscriptionStatus = eNotSubscribed;
    iLock = new OpenHome::Mutex("PRX1");
    iPropertyReadLock = new OpenHome::Mutex("PRX2");
    iPropertyWriteLock = new OpenHome::Mutex("PRX3");
    iInitialEventDelivered = false;
    iInitialEventLock = NULL;
}

CpProxy::~CpProxy()
{
    delete iService;
    delete iLock;
    delete iPropertyReadLock;
    delete iPropertyWriteLock;
    delete iInitialEventLock;
    PropertyMap::iterator it = iProperties.begin();
    while (it != iProperties.end()) {
        delete it->second;
        it++;
    }
}

void CpProxy::AddProperty(Property* aProperty)
{
    ASSERT(aProperty != NULL);
    Brn name(aProperty->Parameter().Name());
    iProperties.insert(std::pair<Brn,Property*>(name, aProperty));
}

void CpProxy::DestroyService()
{
    delete iService;
    iService = NULL;
}

void CpProxy::SetPropertyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPropertyChanged = aFunctor;
    iLock->Signal();
}

void CpProxy::SetPropertyInitialEvent(Functor& aFunctor)
{
    iLock->Wait();
    iInitialEvent = aFunctor;
    if (iInitialEventDelivered && iInitialEvent) {
        iInitialEvent();
    }
    iLock->Signal();
}

TUint CpProxy::Version() const
{
    return iService->Version();
}

Mutex& CpProxy::PropertyReadLock() const
{
    return *iPropertyReadLock;
}

void CpProxy::ReportEvent(Functor aFunctor)
{
    iLock->Wait();
    if (iCpSubscriptionStatus == eSubscribing) {
        iCpSubscriptionStatus = eSubscribed;
    }
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && aFunctor != 0) {
        aFunctor();
    }
    iLock->Signal();
}

void CpProxy::EventUpdateStart()
{
    iPropertyWriteLock->Wait();
    iPropertyReadLock->Wait();
}

void CpProxy::EventUpdate(const Brx& aName, const Brx& aValue, IOutputProcessor& aProcessor)
{
    if (iCpSubscriptionStatus != eNotSubscribed) {
        Brn name(aName);
        PropertyMap::iterator it = iProperties.find(name);
        if (it != iProperties.end()) {
            it->second->Process(aProcessor, aValue);
        }
    }
}

void CpProxy::EventUpdateEnd()
{
    iPropertyReadLock->Signal();
    TBool changed = false;
    PropertyMap::iterator it = iProperties.begin();
    while (it != iProperties.end()) {
        changed = changed | it->second->ReportChanged();
        it++;
    }
    if (changed || !iInitialEventDelivered) {
        iLock->Wait();
        if (iPropertyChanged) {
            iPropertyChanged();
        }
        iLock->Signal();
        if (!iInitialEventDelivered) {
            iInitialEventDelivered = true;
            iInitialEventLock->Wait();
            if (iInitialEvent) {
                iInitialEvent();
            }
            iInitialEventLock->Signal();
            delete iInitialEventLock;
            iInitialEventLock = NULL;
        }
    }
    iPropertyWriteLock->Signal();
}

void CpProxy::EventUpdateError()
{
    iPropertyReadLock->Signal();
    iPropertyWriteLock->Signal();
}

void CpProxy::EventUpdatePrepareForDelete()
{
    iPropertyWriteLock->Wait();
    iPropertyWriteLock->Signal();
}

CpiService& CpProxy::GetService() const
{
    return *iService;
}

IInvocable& CpProxy::GetInvocable() const
{
    return iInvocable;
}

Mutex& CpProxy::GetLock() const
{
    return *iLock;
}

CpProxy::SubscriptionStatus CpProxy::GetSubscriptionStatus() const
{
    return iCpSubscriptionStatus;
}
