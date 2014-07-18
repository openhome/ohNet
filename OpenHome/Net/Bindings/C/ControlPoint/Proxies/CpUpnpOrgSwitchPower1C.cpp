#include "CpUpnpOrgSwitchPower1.h"
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

class CpProxyUpnpOrgSwitchPower1C : public CpProxyC
{
public:
    CpProxyUpnpOrgSwitchPower1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgSwitchPower1C();
    //CpProxyUpnpOrgSwitchPower1* Proxy() { return static_cast<CpProxyUpnpOrgSwitchPower1*>(iProxy); }

    void SyncSetTarget(TBool anewTargetValue);
    void BeginSetTarget(TBool anewTargetValue, FunctorAsync& aFunctor);
    void EndSetTarget(IAsync& aAsync);

    void SyncGetTarget(TBool& aRetTargetValue);
    void BeginGetTarget(FunctorAsync& aFunctor);
    void EndGetTarget(IAsync& aAsync, TBool& aRetTargetValue);

    void SyncGetStatus(TBool& aResultStatus);
    void BeginGetStatus(FunctorAsync& aFunctor);
    void EndGetStatus(IAsync& aAsync, TBool& aResultStatus);

    void SetPropertyStatusChanged(Functor& aFunctor);

    void PropertyStatus(TBool& aStatus) const;
private:
    void StatusPropertyChanged();
private:
    Mutex iLock;
    Action* iActionSetTarget;
    Action* iActionGetTarget;
    Action* iActionGetStatus;
    PropertyBool* iStatus;
    Functor iStatusChanged;
};


class SyncSetTargetUpnpOrgSwitchPower1C : public SyncProxyAction
{
public:
    SyncSetTargetUpnpOrgSwitchPower1C(CpProxyUpnpOrgSwitchPower1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetTargetUpnpOrgSwitchPower1C() {};
private:
    CpProxyUpnpOrgSwitchPower1C& iService;
};

SyncSetTargetUpnpOrgSwitchPower1C::SyncSetTargetUpnpOrgSwitchPower1C(CpProxyUpnpOrgSwitchPower1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetTargetUpnpOrgSwitchPower1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetTarget(aAsync);
}


class SyncGetTargetUpnpOrgSwitchPower1C : public SyncProxyAction
{
public:
    SyncGetTargetUpnpOrgSwitchPower1C(CpProxyUpnpOrgSwitchPower1C& aProxy, TBool& aRetTargetValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetTargetUpnpOrgSwitchPower1C() {};
private:
    CpProxyUpnpOrgSwitchPower1C& iService;
    TBool& iRetTargetValue;
};

SyncGetTargetUpnpOrgSwitchPower1C::SyncGetTargetUpnpOrgSwitchPower1C(CpProxyUpnpOrgSwitchPower1C& aProxy, TBool& aRetTargetValue)
    : iService(aProxy)
    , iRetTargetValue(aRetTargetValue)
{
}

void SyncGetTargetUpnpOrgSwitchPower1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetTarget(aAsync, iRetTargetValue);
}


class SyncGetStatusUpnpOrgSwitchPower1C : public SyncProxyAction
{
public:
    SyncGetStatusUpnpOrgSwitchPower1C(CpProxyUpnpOrgSwitchPower1C& aProxy, TBool& aResultStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStatusUpnpOrgSwitchPower1C() {};
private:
    CpProxyUpnpOrgSwitchPower1C& iService;
    TBool& iResultStatus;
};

SyncGetStatusUpnpOrgSwitchPower1C::SyncGetStatusUpnpOrgSwitchPower1C(CpProxyUpnpOrgSwitchPower1C& aProxy, TBool& aResultStatus)
    : iService(aProxy)
    , iResultStatus(aResultStatus)
{
}

void SyncGetStatusUpnpOrgSwitchPower1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStatus(aAsync, iResultStatus);
}

CpProxyUpnpOrgSwitchPower1C::CpProxyUpnpOrgSwitchPower1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "SwitchPower", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;

    iActionSetTarget = new Action("SetTarget");
    param = new OpenHome::Net::ParameterBool("newTargetValue");
    iActionSetTarget->AddInputParameter(param);

    iActionGetTarget = new Action("GetTarget");
    param = new OpenHome::Net::ParameterBool("RetTargetValue");
    iActionGetTarget->AddOutputParameter(param);

    iActionGetStatus = new Action("GetStatus");
    param = new OpenHome::Net::ParameterBool("ResultStatus");
    iActionGetStatus->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgSwitchPower1C::StatusPropertyChanged);
    iStatus = new PropertyBool(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Status", functor);
    AddProperty(iStatus);
}

CpProxyUpnpOrgSwitchPower1C::~CpProxyUpnpOrgSwitchPower1C()
{
    DestroyService();
    delete iActionSetTarget;
    delete iActionGetTarget;
    delete iActionGetStatus;
}

void CpProxyUpnpOrgSwitchPower1C::SyncSetTarget(TBool anewTargetValue)
{
    SyncSetTargetUpnpOrgSwitchPower1C sync(*this);
    BeginSetTarget(anewTargetValue, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1C::BeginSetTarget(TBool anewTargetValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetTarget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetTarget->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], anewTargetValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1C::EndSetTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetTarget"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyUpnpOrgSwitchPower1C::SyncGetTarget(TBool& aRetTargetValue)
{
    SyncGetTargetUpnpOrgSwitchPower1C sync(*this, aRetTargetValue);
    BeginGetTarget(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1C::BeginGetTarget(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetTarget, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetTarget->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1C::EndGetTarget(IAsync& aAsync, TBool& aRetTargetValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetTarget"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aRetTargetValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgSwitchPower1C::SyncGetStatus(TBool& aResultStatus)
{
    SyncGetStatusUpnpOrgSwitchPower1C sync(*this, aResultStatus);
    BeginGetStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgSwitchPower1C::BeginGetStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStatus->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgSwitchPower1C::EndGetStatus(IAsync& aAsync, TBool& aResultStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStatus"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aResultStatus = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgSwitchPower1C::SetPropertyStatusChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStatusChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgSwitchPower1C::PropertyStatus(TBool& aStatus) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aStatus = iStatus->Value();
}

void CpProxyUpnpOrgSwitchPower1C::StatusPropertyChanged()
{
    ReportEvent(iStatusChanged);
}


THandle STDCALL CpProxyUpnpOrgSwitchPower1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgSwitchPower1C(aDevice);
}

void STDCALL CpProxyUpnpOrgSwitchPower1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgSwitchPower1SyncSetTarget(THandle aHandle, uint32_t anewTargetValue)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetTarget((anewTargetValue==0? false : true));
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgSwitchPower1BeginSetTarget(THandle aHandle, uint32_t anewTargetValue, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetTarget((anewTargetValue==0? false : true), functor);
}

int32_t STDCALL CpProxyUpnpOrgSwitchPower1EndSetTarget(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetTarget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgSwitchPower1SyncGetTarget(THandle aHandle, uint32_t* aRetTargetValue)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool RetTargetValue;
    int32_t err = 0;
    try {
        proxyC->SyncGetTarget(RetTargetValue);
        *aRetTargetValue = RetTargetValue? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aRetTargetValue = false;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgSwitchPower1BeginGetTarget(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetTarget(functor);
}

int32_t STDCALL CpProxyUpnpOrgSwitchPower1EndGetTarget(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aRetTargetValue)
{
    int32_t err = 0;
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool RetTargetValue;
    try {
        proxyC->EndGetTarget(*async, RetTargetValue);
        *aRetTargetValue = RetTargetValue? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgSwitchPower1SyncGetStatus(THandle aHandle, uint32_t* aResultStatus)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool ResultStatus;
    int32_t err = 0;
    try {
        proxyC->SyncGetStatus(ResultStatus);
        *aResultStatus = ResultStatus? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aResultStatus = false;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgSwitchPower1BeginGetStatus(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetStatus(functor);
}

int32_t STDCALL CpProxyUpnpOrgSwitchPower1EndGetStatus(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aResultStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool ResultStatus;
    try {
        proxyC->EndGetStatus(*async, ResultStatus);
        *aResultStatus = ResultStatus? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgSwitchPower1SetPropertyStatusChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStatusChanged(functor);
}

void STDCALL CpProxyUpnpOrgSwitchPower1PropertyStatus(THandle aHandle, uint32_t* aStatus)
{
    CpProxyUpnpOrgSwitchPower1C* proxyC = reinterpret_cast<CpProxyUpnpOrgSwitchPower1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Status;
    proxyC->PropertyStatus(Status);
    *aStatus = Status? 1 : 0;
}

