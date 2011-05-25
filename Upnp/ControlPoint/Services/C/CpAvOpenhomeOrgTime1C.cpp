#include "CpAvOpenhomeOrgTime1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <OhNetTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace OpenHome::Net;

class CpProxyAvOpenhomeOrgTime1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgTime1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgTime1C();
    //CpProxyAvOpenhomeOrgTime1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgTime1*>(iProxy); }

    void SyncTime(TUint& aTrackCount, TUint& aDuration, TUint& aSeconds);
    void BeginTime(FunctorAsync& aFunctor);
    void EndTime(IAsync& aAsync, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds);

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
    SyncTimeAvOpenhomeOrgTime1C(CpProxyAvOpenhomeOrgTime1C& aProxy, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgTime1C& iService;
    TUint& iTrackCount;
    TUint& iDuration;
    TUint& iSeconds;
};

SyncTimeAvOpenhomeOrgTime1C::SyncTimeAvOpenhomeOrgTime1C(CpProxyAvOpenhomeOrgTime1C& aProxy, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds)
    : iService(aProxy)
    , iTrackCount(aTrackCount)
    , iDuration(aDuration)
    , iSeconds(aSeconds)
{
}

void SyncTimeAvOpenhomeOrgTime1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTime(aAsync, iTrackCount, iDuration, iSeconds);
}

CpProxyAvOpenhomeOrgTime1C::CpProxyAvOpenhomeOrgTime1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Time", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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

void CpProxyAvOpenhomeOrgTime1C::SyncTime(TUint& aTrackCount, TUint& aDuration, TUint& aSeconds)
{
    SyncTimeAvOpenhomeOrgTime1C sync(*this, aTrackCount, aDuration, aSeconds);
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

void CpProxyAvOpenhomeOrgTime1C::EndTime(IAsync& aAsync, TUint& aTrackCount, TUint& aDuration, TUint& aSeconds)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Time"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aTrackCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aSeconds = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
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

void CpProxyAvOpenhomeOrgTime1SyncTime(THandle aHandle, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncTime(*aTrackCount, *aDuration, *aSeconds);
}

void CpProxyAvOpenhomeOrgTime1BeginTime(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTime(functor);
}

int32_t CpProxyAvOpenhomeOrgTime1EndTime(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndTime(*async, *aTrackCount, *aDuration, *aSeconds);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgTime1SetPropertyTrackCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void CpProxyAvOpenhomeOrgTime1SetPropertyDurationChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void CpProxyAvOpenhomeOrgTime1SetPropertySecondsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
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

