#include "CpAvOpenhomeOrgTime1.h"
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

class CpProxyAvOpenhomeOrgTime1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgTime1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgTime1C();
    //CpProxyAvOpenhomeOrgTime1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgTime1*>(iProxy); }

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
    Action* iActionTime;
    PropertyUint* iTrackCount;
    PropertyUint* iDuration;
    PropertyUint* iSeconds;
    Functor iTrackCountChanged;
    Functor iDurationChanged;
    Functor iSecondsChanged;
};


class SyncTimeAvOpenhomeOrgTime1C : public SyncProxyAction
{
public:
    SyncTimeAvOpenhomeOrgTime1C(CpProxyAvOpenhomeOrgTime1C& aProxy, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgTime1C& iService;
    TUint& iaTrackCount;
    TUint& iaDuration;
    TUint& iaSeconds;
};

SyncTimeAvOpenhomeOrgTime1C::SyncTimeAvOpenhomeOrgTime1C(CpProxyAvOpenhomeOrgTime1C& aProxy, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
    : iService(aProxy)
    , iaTrackCount(aaTrackCount)
    , iaDuration(aaDuration)
    , iaSeconds(aaSeconds)
{
}

void SyncTimeAvOpenhomeOrgTime1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iaTrackCount, iaDuration, iaSeconds);
}

CpProxyAvOpenhomeOrgTime1C::CpProxyAvOpenhomeOrgTime1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Time", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1C::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1C::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1C::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyAvOpenhomeOrgTime1C::~CpProxyAvOpenhomeOrgTime1C()
{
    DestroyService();
    delete iActionTime;
}

void CpProxyAvOpenhomeOrgTime1C::SyncTime(TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
{
    SyncTimeAvOpenhomeOrgTime1C sync(*this, aaTrackCount, aaDuration, aaSeconds);
    BeginTime(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgTime1C::BeginTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgTime1C::EndTime(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDuration, TUint& aaSeconds)
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

void CpProxyAvOpenhomeOrgTime1C::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgTime1C::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDurationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgTime1C::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSecondsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgTime1C::PropertyTrackCount(TUint& aTrackCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aTrackCount = iTrackCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1C::PropertyDuration(TUint& aDuration) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDuration = iDuration->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1C::PropertySeconds(TUint& aSeconds) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aSeconds = iSeconds->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgTime1C::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyAvOpenhomeOrgTime1C::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyAvOpenhomeOrgTime1C::SecondsPropertyChanged()
{
    ReportEvent(iSecondsChanged);
}


THandle CpProxyAvOpenhomeOrgTime1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgTime1C(aDevice);
}

void CpProxyAvOpenhomeOrgTime1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    delete proxyC;
}

void CpProxyAvOpenhomeOrgTime1SyncTime(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncTime(*aaTrackCount, *aaDuration, *aaSeconds);
}

void CpProxyAvOpenhomeOrgTime1BeginTime(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTime(functor);
}

int32_t CpProxyAvOpenhomeOrgTime1EndTime(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDuration, uint32_t* aaSeconds)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
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

void CpProxyAvOpenhomeOrgTime1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void CpProxyAvOpenhomeOrgTime1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void CpProxyAvOpenhomeOrgTime1SetPropertySecondsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySecondsChanged(functor);
}

void CpProxyAvOpenhomeOrgTime1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackCount(*aTrackCount);
}

void CpProxyAvOpenhomeOrgTime1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDuration(*aDuration);
}

void CpProxyAvOpenhomeOrgTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySeconds(*aSeconds);
}

