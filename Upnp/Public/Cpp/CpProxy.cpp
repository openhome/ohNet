#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>

using namespace Zapp;

void CpProxy::Subscribe()
{
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
}

CpProxy::CpProxy(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice)
    : iInvocable(aDevice)
{
    iService = new CpiService(aDomain, aName, aVersion, aDevice);
    iCpSubscriptionStatus = eNotSubscribed;
    iLock = new Mutex("PRX1");
    iPropertyLock = new Mutex("PRX2");
    iInitialEventDelivered = false;
}

CpProxy::~CpProxy()
{
    delete iService;
    delete iLock;
    delete iPropertyLock;
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

void CpProxy::ReportEvent(Functor aFunctor)
{
    iLock->Wait();
    if (iCpSubscriptionStatus == eSubscribing) {
        iCpSubscriptionStatus = eSubscribed;
    }
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && aFunctor != NULL) {
        aFunctor();
    }
    iLock->Signal();
}

void CpProxy::EventUpdateStart()
{
    iPropertyLock->Wait();
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
    iPropertyLock->Signal();
    TBool changed = false;
    PropertyMap::iterator it = iProperties.begin();
    while (it != iProperties.end()) {
        changed = changed | it->second->ReportChanged();
		it++;
    }
    if (changed) {
        iLock->Wait();
        if (iPropertyChanged) {
            iPropertyChanged();
        }
        if (!iInitialEventDelivered) {
            iInitialEventDelivered = true;
            if (iInitialEvent) {
                iInitialEvent();
            }
        }
        iLock->Signal();
    }
}
