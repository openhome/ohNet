#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>

using namespace Zapp;

void CpProxy::Subscribe()
{
    iLock->Wait();
    iCpSubscriptionStatus = eSubscribing;
    iLock->Signal();
    iService->Subscribe();
}

void CpProxy::Unsubscribe()
{
    iLock->Wait();
    iCpSubscriptionStatus = eNotSubscribed;
    iLock->Signal();
    iService->Unsubscribe();
}

CpProxy::CpProxy(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice)
{
    iService = new CpiService(aDomain, aName, aVersion, aDevice);
    Functor functor = MakeFunctor(*this, &CpProxy::PropertyChanged);
    iService->SetPropertyChanged(functor);
    iCpSubscriptionStatus = eNotSubscribed;
    iLock = new Mutex("PRXY");
    iInitialEventDelivered = false;
}

CpProxy::~CpProxy()
{
    delete iLock;
}

void CpProxy::DestroyService()
{
    delete iService;
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

void CpProxy::PropertyChanged()
{
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
