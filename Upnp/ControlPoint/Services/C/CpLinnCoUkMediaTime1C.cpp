#include "CpLinnCoUkMediaTime1.h"
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

class CpProxyLinnCoUkMediaTime1C : public CpProxyC
{
public:
    CpProxyLinnCoUkMediaTime1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkMediaTime1C();
    //CpProxyLinnCoUkMediaTime1* Proxy() { return static_cast<CpProxyLinnCoUkMediaTime1*>(iProxy); }

    void SyncSeconds(TUint& aaSeconds);
    void BeginSeconds(FunctorAsync& aFunctor);
    void EndSeconds(IAsync& aAsync, TUint& aaSeconds);

    void SetPropertySecondsChanged(Functor& aFunctor);

    void PropertySeconds(TUint& aSeconds) const;
private:
    void SecondsPropertyChanged();
private:
    Mutex iLock;
    Action* iActionSeconds;
    PropertyUint* iSeconds;
    Functor iSecondsChanged;
};


class SyncSecondsLinnCoUkMediaTime1C : public SyncProxyAction
{
public:
    SyncSecondsLinnCoUkMediaTime1C(CpProxyLinnCoUkMediaTime1C& aProxy, TUint& aaSeconds);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkMediaTime1C& iService;
    TUint& iaSeconds;
};

SyncSecondsLinnCoUkMediaTime1C::SyncSecondsLinnCoUkMediaTime1C(CpProxyLinnCoUkMediaTime1C& aProxy, TUint& aaSeconds)
    : iService(aProxy)
    , iaSeconds(aaSeconds)
{
}

void SyncSecondsLinnCoUkMediaTime1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeconds(aAsync, iaSeconds);
}

CpProxyLinnCoUkMediaTime1C::CpProxyLinnCoUkMediaTime1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "MediaTime", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    Zapp::Parameter* param;

    iActionSeconds = new Action("Seconds");
    param = new Zapp::ParameterUint("aSeconds");
    iActionSeconds->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkMediaTime1C::SecondsPropertyChanged);
    iSeconds = new PropertyUint("Seconds", functor);
    AddProperty(iSeconds);
}

CpProxyLinnCoUkMediaTime1C::~CpProxyLinnCoUkMediaTime1C()
{
    DestroyService();
    delete iActionSeconds;
}

void CpProxyLinnCoUkMediaTime1C::SyncSeconds(TUint& aaSeconds)
{
    SyncSecondsLinnCoUkMediaTime1C sync(*this, aaSeconds);
    BeginSeconds(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkMediaTime1C::BeginSeconds(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeconds, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSeconds->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkMediaTime1C::EndSeconds(IAsync& aAsync, TUint& aaSeconds)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Seconds"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSeconds = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkMediaTime1C::SetPropertySecondsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSecondsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkMediaTime1C::PropertySeconds(TUint& aSeconds) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aSeconds = iSeconds->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkMediaTime1C::SecondsPropertyChanged()
{
    ReportEvent(iSecondsChanged);
}


THandle CpProxyLinnCoUkMediaTime1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkMediaTime1C(aDevice);
}

void CpProxyLinnCoUkMediaTime1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkMediaTime1SyncSeconds(THandle aHandle, uint32_t* aaSeconds)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeconds(*aaSeconds);
}

void CpProxyLinnCoUkMediaTime1BeginSeconds(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeconds(functor);
}

int32_t CpProxyLinnCoUkMediaTime1EndSeconds(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSeconds)
{
    int32_t err = 0;
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeconds(*async, *aaSeconds);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkMediaTime1SetPropertySecondsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySecondsChanged(functor);
}

void CpProxyLinnCoUkMediaTime1PropertySeconds(THandle aHandle, uint32_t* aSeconds)
{
    CpProxyLinnCoUkMediaTime1C* proxyC = reinterpret_cast<CpProxyLinnCoUkMediaTime1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySeconds(*aSeconds);
}

