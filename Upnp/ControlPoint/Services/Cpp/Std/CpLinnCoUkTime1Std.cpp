#include <Std/CpLinnCoUkTime1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncTimeLinnCoUkTime1Cpp : public SyncProxyAction
{
public:
    SyncTimeLinnCoUkTime1Cpp(CpProxyLinnCoUkTime1Cpp& aService, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkTime1Cpp& iService;
    uint32_t& iaTrackCount;
    uint32_t& iaDuration;
    uint32_t& iaSeconds;
};

SyncTimeLinnCoUkTime1Cpp::SyncTimeLinnCoUkTime1Cpp(CpProxyLinnCoUkTime1Cpp& aService, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds)
    : iService(aService)
    , iaTrackCount(aaTrackCount)
    , iaDuration(aaDuration)
    , iaSeconds(aaSeconds)
{
}

void SyncTimeLinnCoUkTime1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iaTrackCount, iaDuration, iaSeconds);
}


CpProxyLinnCoUkTime1Cpp::CpProxyLinnCoUkTime1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("linn-co-uk", "Time", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionTime = new Action("Time");
    param = new Zapp::ParameterUint("aTrackCount");
    iActionTime->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aDuration");
    iActionTime->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aSeconds");
    iActionTime->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1Cpp::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    iService->AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1Cpp::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    iService->AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1Cpp::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    iService->AddProperty(iSeconds);
}

CpProxyLinnCoUkTime1Cpp::~CpProxyLinnCoUkTime1Cpp()
{
    delete iService;
    delete iActionTime;
}

void CpProxyLinnCoUkTime1Cpp::SyncTime(uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds)
{
    SyncTimeLinnCoUkTime1Cpp sync(*this, aaTrackCount, aaDuration, aaSeconds);
    BeginTime(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkTime1Cpp::BeginTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkTime1Cpp::EndTime(IAsync& aAsync, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds)
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

void CpProxyLinnCoUkTime1Cpp::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkTime1Cpp::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkTime1Cpp::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSecondsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkTime1Cpp::PropertyTrackCount(uint32_t& aTrackCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
}

void CpProxyLinnCoUkTime1Cpp::PropertyDuration(uint32_t& aDuration) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
}

void CpProxyLinnCoUkTime1Cpp::PropertySeconds(uint32_t& aSeconds) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
}

void CpProxyLinnCoUkTime1Cpp::TrackCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackCountChanged != NULL) {
        iTrackCountChanged();
    }
}

void CpProxyLinnCoUkTime1Cpp::DurationPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDurationChanged != NULL) {
        iDurationChanged();
    }
}

void CpProxyLinnCoUkTime1Cpp::SecondsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSecondsChanged != NULL) {
        iSecondsChanged();
    }
}

