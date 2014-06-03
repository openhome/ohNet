#include "CpAvOpenhomeOrgTime1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncTimeAvOpenhomeOrgTime1Cpp : public SyncProxyAction
{
public:
    SyncTimeAvOpenhomeOrgTime1Cpp(CpProxyAvOpenhomeOrgTime1Cpp& aProxy, uint32_t& aTrackCount, uint32_t& aDuration, uint32_t& aSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTimeAvOpenhomeOrgTime1Cpp() {}
private:
    CpProxyAvOpenhomeOrgTime1Cpp& iService;
    uint32_t& iTrackCount;
    uint32_t& iDuration;
    uint32_t& iSeconds;
};

SyncTimeAvOpenhomeOrgTime1Cpp::SyncTimeAvOpenhomeOrgTime1Cpp(CpProxyAvOpenhomeOrgTime1Cpp& aProxy, uint32_t& aTrackCount, uint32_t& aDuration, uint32_t& aSeconds)
    : iService(aProxy)
    , iTrackCount(aTrackCount)
    , iDuration(aDuration)
    , iSeconds(aSeconds)
{
}

void SyncTimeAvOpenhomeOrgTime1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iTrackCount, iDuration, iSeconds);
}


CpProxyAvOpenhomeOrgTime1Cpp::CpProxyAvOpenhomeOrgTime1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1Cpp::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint(aDevice.Device().GetCpStack().Env(), "TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1Cpp::DurationPropertyChanged);
    iDuration = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1Cpp::SecondsPropertyChanged);
    iSeconds = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyAvOpenhomeOrgTime1Cpp::~CpProxyAvOpenhomeOrgTime1Cpp()
{
    DestroyService();
    delete iActionTime;
}

void CpProxyAvOpenhomeOrgTime1Cpp::SyncTime(uint32_t& aTrackCount, uint32_t& aDuration, uint32_t& aSeconds)
{
    SyncTimeAvOpenhomeOrgTime1Cpp sync(*this, aTrackCount, aDuration, aSeconds);
    BeginTime(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgTime1Cpp::BeginTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgTime1Cpp::EndTime(IAsync& aAsync, uint32_t& aTrackCount, uint32_t& aDuration, uint32_t& aSeconds)
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

void CpProxyAvOpenhomeOrgTime1Cpp::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgTime1Cpp::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgTime1Cpp::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSecondsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgTime1Cpp::PropertyTrackCount(uint32_t& aTrackCount) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
}

void CpProxyAvOpenhomeOrgTime1Cpp::PropertyDuration(uint32_t& aDuration) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
}

void CpProxyAvOpenhomeOrgTime1Cpp::PropertySeconds(uint32_t& aSeconds) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
}

void CpProxyAvOpenhomeOrgTime1Cpp::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyAvOpenhomeOrgTime1Cpp::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyAvOpenhomeOrgTime1Cpp::SecondsPropertyChanged()
{
    ReportEvent(iSecondsChanged);
}

