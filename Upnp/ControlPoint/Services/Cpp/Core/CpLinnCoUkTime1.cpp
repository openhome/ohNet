#include <Core/CpLinnCoUkTime1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncTimeLinnCoUkTime1 : public SyncProxyAction
{
public:
    SyncTimeLinnCoUkTime1(CpProxyLinnCoUkTime1& aService, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkTime1& iService;
    TUint& iaTrackCount;
    TUint& iaDuration;
    TUint& iaSeconds;
};

SyncTimeLinnCoUkTime1::SyncTimeLinnCoUkTime1(CpProxyLinnCoUkTime1& aService, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
    : iService(aService)
    , iaTrackCount(aaTrackCount)
    , iaDuration(aaDuration)
    , iaSeconds(aaSeconds)
{
}

void SyncTimeLinnCoUkTime1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iaTrackCount, iaDuration, iaSeconds);
}


CpProxyLinnCoUkTime1::CpProxyLinnCoUkTime1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    iService->AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    iService->AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    iService->AddProperty(iSeconds);
}

CpProxyLinnCoUkTime1::~CpProxyLinnCoUkTime1()
{
    delete iService;
    delete iActionTime;
}

void CpProxyLinnCoUkTime1::SyncTime(TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
{
    SyncTimeLinnCoUkTime1 sync(*this, aaTrackCount, aaDuration, aaSeconds);
    BeginTime(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkTime1::BeginTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkTime1::EndTime(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
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

void CpProxyLinnCoUkTime1::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkTime1::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkTime1::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSecondsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkTime1::PropertyTrackCount(TUint& aTrackCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
}

void CpProxyLinnCoUkTime1::PropertyDuration(TUint& aDuration) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
}

void CpProxyLinnCoUkTime1::PropertySeconds(TUint& aSeconds) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSeconds = iSeconds->Value();
}

void CpProxyLinnCoUkTime1::TrackCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackCountChanged != NULL) {
        iTrackCountChanged();
    }
}

void CpProxyLinnCoUkTime1::DurationPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDurationChanged != NULL) {
        iDurationChanged();
    }
}

void CpProxyLinnCoUkTime1::SecondsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSecondsChanged != NULL) {
        iSecondsChanged();
    }
}

