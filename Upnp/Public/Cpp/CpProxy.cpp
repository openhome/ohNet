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

CpProxy::CpProxy()
    : iService(NULL)
    , iLock(NULL)
{
    iCpSubscriptionStatus = eNotSubscribed;
    iLock = new Mutex("PRXY");
}

CpProxy::~CpProxy()
{
    delete iLock;
}

void CpProxy::SetPropertyChanged(Functor& aFunctor)
{
    iService->SetPropertyChanged(aFunctor);
}

TBool CpProxy::ReportEvent()
{
    TBool report;
    iLock->Wait();
    report = (iCpSubscriptionStatus != eNotSubscribed);
    if (iCpSubscriptionStatus == eSubscribing) {
        iCpSubscriptionStatus = eSubscribed;
    }
    iLock->Signal();
    return report;
}
