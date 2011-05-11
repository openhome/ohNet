#include "CpAvOpenhomeOrgTime1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncTimeAvOpenhomeOrgTime1Cpp : public SyncProxyAction
{
public:
    SyncTimeAvOpenhomeOrgTime1Cpp(CpProxyAvOpenhomeOrgTime1Cpp& aProxy, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgTime1Cpp& iService;
    uint32_t& iaTrackCount;
    uint32_t& iaDuration;
    uint32_t& iaSeconds;
};

SyncTimeAvOpenhomeOrgTime1Cpp::SyncTimeAvOpenhomeOrgTime1Cpp(CpProxyAvOpenhomeOrgTime1Cpp& aProxy, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds)
    : iService(aProxy)
    , iaTrackCount(aaTrackCount)
    , iaDuration(aaDuration)
    , iaSeconds(aaSeconds)
{
}

void SyncTimeAvOpenhomeOrgTime1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iaTrackCount, iaDuration, iaSeconds);
}


CpProxyAvOpenhomeOrgTime1Cpp::CpProxyAvOpenhomeOrgTime1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1Cpp::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1Cpp::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1Cpp::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyAvOpenhomeOrgTime1Cpp::~CpProxyAvOpenhomeOrgTime1Cpp()
{
    DestroyService();
    delete iActionTime;
}

void CpProxyAvOpenhomeOrgTime1Cpp::SyncTime(uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds)
{
    SyncTimeAvOpenhomeOrgTime1Cpp sync(*this, aaTrackCount, aaDuration, aaSeconds);
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

void CpProxyAvOpenhomeOrgTime1Cpp::EndTime(IAsync& aAsync, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds)
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
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1Cpp::PropertyDuration(uint32_t& aDuration) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1Cpp::PropertySeconds(uint32_t& aSeconds) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
    PropertyReadUnlock();
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

