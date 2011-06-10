#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void CpProxy::Subscribe()
{
    if (iInitialEventLock == NULL) {
        iInitialEventLock = new OpenHome::Mutex("PRX4");
    }
    iLock->Wait();
    iCpSubscriptionStatus = eSubscribing;
    iLock->Signal();
    iService->Subscribe(*this);
}

void CpProxy::Unsubscribe()
{
    iLock->Wait();
    iCpSubscriptionStatus = eNotSubscribed;
    iLock->Signal();
    iService->Unsubscribe();
    iLock->Wait();
    iInitialEventDelivered = false;
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

void CpProxy::PropertyReadLock() const
{
    iPropertyReadLock->Wait();
}

void CpProxy::PropertyReadUnlock() const
{
    iPropertyReadLock->Signal();
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
    PropertyReadLock();
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
    PropertyReadUnlock();
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
