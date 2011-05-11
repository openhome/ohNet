#include "CpAvOpenhomeOrgTime1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncTimeAvOpenhomeOrgTime1 : public SyncProxyAction
{
public:
    SyncTimeAvOpenhomeOrgTime1(CpProxyAvOpenhomeOrgTime1& aProxy, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgTime1& iService;
    TUint& iaTrackCount;
    TUint& iaDuration;
    TUint& iaSeconds;
};

SyncTimeAvOpenhomeOrgTime1::SyncTimeAvOpenhomeOrgTime1(CpProxyAvOpenhomeOrgTime1& aProxy, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
    : iService(aProxy)
    , iaTrackCount(aaTrackCount)
    , iaDuration(aaDuration)
    , iaSeconds(aaSeconds)
{
}

void SyncTimeAvOpenhomeOrgTime1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iaTrackCount, iaDuration, iaSeconds);
}


CpProxyAvOpenhomeOrgTime1::CpProxyAvOpenhomeOrgTime1(CpDevice& aDevice)
    : CpProxy("av-openhome-org", "Time", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionTime = new Action("Time");
    param = new Zapp::ParameterUint("aTrackCount");
    iActionTime->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aDuration");
    iActionTime->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aSeconds");
    iActionTime->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyAvOpenhomeOrgTime1::~CpProxyAvOpenhomeOrgTime1()
{
    DestroyService();
    delete iActionTime;
}

void CpProxyAvOpenhomeOrgTime1::SyncTime(TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
{
    SyncTimeAvOpenhomeOrgTime1 sync(*this, aaTrackCount, aaDuration, aaSeconds);
    BeginTime(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgTime1::BeginTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgTime1::EndTime(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Time"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaTrackCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaSeconds = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgTime1::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgTime1::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgTime1::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSecondsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgTime1::PropertyTrackCount(TUint& aTrackCount) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1::PropertyDuration(TUint& aDuration) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1::PropertySeconds(TUint& aSeconds) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyAvOpenhomeOrgTime1::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyAvOpenhomeOrgTime1::SecondsPropertyChanged()
{
    ReportEvent(iSecondsChanged);
}

