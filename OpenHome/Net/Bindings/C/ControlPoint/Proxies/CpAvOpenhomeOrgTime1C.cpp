#include "CpAvOpenhomeOrgTime1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
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
    virtual ~SyncTimeAvOpenhomeOrgTime1C() {};
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
    iTrackCount = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1C::DurationPropertyChanged);
    iDuration = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgTime1C::SecondsPropertyChanged);
    iSeconds = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Seconds", functor);
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
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTrackCount = iTrackCount->Value();
}

void CpProxyAvOpenhomeOrgTime1C::PropertyDuration(TUint& aDuration) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aDuration = iDuration->Value();
}

void CpProxyAvOpenhomeOrgTime1C::PropertySeconds(TUint& aSeconds) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSeconds = iSeconds->Value();
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


THandle STDCALL CpProxyAvOpenhomeOrgTime1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgTime1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgTime1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgTime1SyncTime(THandle aHandle, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncTime(*aTrackCount, *aDuration, *aSeconds);
    }
    catch (ProxyError& ) {
        err = -1;
        *aTrackCount = 0;
        *aDuration = 0;
        *aSeconds = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgTime1BeginTime(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTime(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgTime1EndTime(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrackCount, uint32_t* aDuration, uint32_t* aSeconds)
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

void STDCALL CpProxyAvOpenhomeOrgTime1SetPropertyTrackCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgTime1SetPropertyDurationChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgTime1SetPropertySecondsChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySecondsChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgTime1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackCount(*aTrackCount);
}

void STDCALL CpProxyAvOpenhomeOrgTime1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDuration(*aDuration);
}

void STDCALL CpProxyAvOpenhomeOrgTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds)
{
    CpProxyAvOpenhomeOrgTime1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySeconds(*aSeconds);
}

