#include "CpLinnCoUkTime1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyLinnCoUkTime1C : public CpProxyC
{
public:
    CpProxyLinnCoUkTime1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkTime1C();
    //CpProxyLinnCoUkTime1* Proxy() { return static_cast<CpProxyLinnCoUkTime1*>(iProxy); }

    void SyncTime(TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds);
    void BeginTime(FunctorAsync& aFunctor);
    void EndTime(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds);

    void SetPropertyTrackCountChanged(Functor& aFunctor);
    void SetPropertyDurationChanged(Functor& aFunctor);
    void SetPropertySecondsChanged(Functor& aFunctor);

    void PropertyTrackCount(TUint& aTrackCount) const;
    void PropertyDuration(TUint& aDuration) const;
    void PropertySeconds(TUint& aSeconds) const;
private:
    void TrackCountPropertyChanged();
    void DurationPropertyChanged();
    void SecondsPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionTime;
    PropertyUint* iTrackCount;
    PropertyUint* iDuration;
    PropertyUint* iSeconds;
    Functor iTrackCountChanged;
    Functor iDurationChanged;
    Functor iSecondsChanged;
};


class SyncTimeLinnCoUkTime1C : public SyncProxyAction
{
public:
    SyncTimeLinnCoUkTime1C(CpProxyLinnCoUkTime1C& aProxy, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkTime1C& iService;
    TUint& iaTrackCount;
    TUint& iaDuration;
    TUint& iaSeconds;
};

SyncTimeLinnCoUkTime1C::SyncTimeLinnCoUkTime1C(CpProxyLinnCoUkTime1C& aProxy, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
    : iService(aProxy)
    , iaTrackCount(aaTrackCount)
    , iaDuration(aaDuration)
    , iaSeconds(aaSeconds)
{
}

void SyncTimeLinnCoUkTime1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iaTrackCount, iaDuration, iaSeconds);
}

CpProxyLinnCoUkTime1C::CpProxyLinnCoUkTime1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Time", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1C::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1C::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkTime1C::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyLinnCoUkTime1C::~CpProxyLinnCoUkTime1C()
{
    delete iActionTime;
}

void CpProxyLinnCoUkTime1C::SyncTime(TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
{
    SyncTimeLinnCoUkTime1C sync(*this, aaTrackCount, aaDuration, aaSeconds);
    BeginTime(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkTime1C::BeginTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkTime1C::EndTime(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
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

void CpProxyLinnCoUkTime1C::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkTime1C::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDurationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkTime1C::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSecondsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkTime1C::PropertyTrackCount(TUint& aTrackCount) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackCount = iTrackCount->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkTime1C::PropertyDuration(TUint& aDuration) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDuration = iDuration->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkTime1C::PropertySeconds(TUint& aSeconds) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aSeconds = iSeconds->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkTime1C::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyLinnCoUkTime1C::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyLinnCoUkTime1C::SecondsPropertyChanged()
{
    ReportEvent(iSecondsChanged);
}


THandle CpProxyLinnCoUkTime1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkTime1C(aDevice);
}

void CpProxyLinnCoUkTime1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkTime1SyncTime(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncTime(*aaTrackCount, *aaDuration, *aaSeconds);
}

void CpProxyLinnCoUkTime1BeginTime(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTime(functor);
}

int32_t CpProxyLinnCoUkTime1EndTime(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds)
{
    int32_t err = 0;
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndTime(*async, *aaTrackCount, *aaDuration, *aaSeconds);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkTime1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void CpProxyLinnCoUkTime1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void CpProxyLinnCoUkTime1SetPropertySecondsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySecondsChanged(functor);
}

void CpProxyLinnCoUkTime1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackCount(*aTrackCount);
}

void CpProxyLinnCoUkTime1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDuration(*aDuration);
}

void CpProxyLinnCoUkTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds)
{
    CpProxyLinnCoUkTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySeconds(*aSeconds);
}

