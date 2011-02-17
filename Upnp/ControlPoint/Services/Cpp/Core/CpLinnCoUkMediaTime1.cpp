#include "CpLinnCoUkMediaTime1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSecondsLinnCoUkMediaTime1 : public SyncProxyAction
{
public:
    SyncSecondsLinnCoUkMediaTime1(CpProxyLinnCoUkMediaTime1& aProxy, TUint& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkMediaTime1& iService;
    TUint& iaSeconds;
};

SyncSecondsLinnCoUkMediaTime1::SyncSecondsLinnCoUkMediaTime1(CpProxyLinnCoUkMediaTime1& aProxy, TUint& aaSeconds)
    : iService(aProxy)
    , iaSeconds(aaSeconds)
{
}

void SyncSecondsLinnCoUkMediaTime1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeconds(aAsync, iaSeconds);
}


CpProxyLinnCoUkMediaTime1::CpProxyLinnCoUkMediaTime1(CpDevice& aDevice)
    : CpProxy("linn-co-uk", "MediaTime", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionSeconds = new Action("Seconds");
    param = new Zapp::ParameterUint("aSeconds");
    iActionSeconds->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkMediaTime1::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyLinnCoUkMediaTime1::~CpProxyLinnCoUkMediaTime1()
{
    DestroyService();
    delete iActionSeconds;
}

void CpProxyLinnCoUkMediaTime1::SyncSeconds(TUint& aaSeconds)
{
    SyncSecondsLinnCoUkMediaTime1 sync(*this, aaSeconds);
    BeginSeconds(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkMediaTime1::BeginSeconds(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeconds, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSeconds->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkMediaTime1::EndSeconds(IAsync& aAsync, TUint& aaSeconds)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seconds"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSeconds = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkMediaTime1::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSecondsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkMediaTime1::PropertySeconds(TUint& aSeconds) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkMediaTime1::SecondsPropertyChanged()
{
    ReportEvent(iSecondsChanged);
}

