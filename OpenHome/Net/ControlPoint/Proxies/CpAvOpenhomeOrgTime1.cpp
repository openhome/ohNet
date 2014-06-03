#include "CpAvOpenhomeOrgTime1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncTimeAvOpenhomeOrgTime1 : public SyncProxyAction
{
public:
    SyncTimeAvOpenhomeOrgTime1(CpProxyAvOpenhomeOrgTime1& aProxy, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTimeAvOpenhomeOrgTime1() {}
private:
    CpProxyAvOpenhomeOrgTime1& iService;
    TUint& iTrackCount;
    TUint& iDuration;
    TUint& iSeconds;
};

SyncTimeAvOpenhomeOrgTime1::SyncTimeAvOpenhomeOrgTime1(CpProxyAvOpenhomeOrgTime1& aProxy, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds)
    : iService(aProxy)
    , iTrackCount(aTrackCount)
    , iDuration(aDuration)
    , iSeconds(aSeconds)
{
}

void SyncTimeAvOpenhomeOrgTime1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iTrackCount, iDuration, iSeconds);
}


CpProxyAvOpenhomeOrgTime1::CpProxyAvOpenhomeOrgTime1(CpDevice& aDevice)
    : CpProxy("av-openhome-org", "Time", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionTime = new Action("Time");
    param = new OpenHome::Net::ParameterUint("TrackCount");
    iActionTime->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionTime->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Seconds");
    iActionTime->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint(aDevice.Device().GetCpStack().Env(), "TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1::DurationPropertyChanged);
    iDuration = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1::SecondsPropertyChanged);
    iSeconds = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyAvOpenhomeOrgTime1::~CpProxyAvOpenhomeOrgTime1()
{
    DestroyService();
    delete iActionTime;
}

void CpProxyAvOpenhomeOrgTime1::SyncTime(TUint& aTrackCount, TUint& aDuration, TUint& aSeconds)
{
    SyncTimeAvOpenhomeOrgTime1 sync(*this, aTrackCount, aDuration, aSeconds);
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

void CpProxyAvOpenhomeOrgTime1::EndTime(IAsync& aAsync, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Time"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aTrackCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aSeconds = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
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
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
}

void CpProxyAvOpenhomeOrgTime1::PropertyDuration(TUint& aDuration) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
}

void CpProxyAvOpenhomeOrgTime1::PropertySeconds(TUint& aSeconds) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
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

