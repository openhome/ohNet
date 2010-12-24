#include "CpLinnCoUkConfiguration1.h"
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

class CpProxyLinnCoUkConfiguration1C : public CpProxyC
{
public:
    CpProxyLinnCoUkConfiguration1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkConfiguration1C();
    //CpProxyLinnCoUkConfiguration1* Proxy() { return static_cast<CpProxyLinnCoUkConfiguration1*>(iProxy); }

    void SyncConfigurationXml(Brh& aaConfigurationXml);
    void BeginConfigurationXml(FunctorAsync& aFunctor);
    void EndConfigurationXml(IAsync& aAsync, Brh& aaConfigurationXml);

    void SyncParameterXml(Brh& aaParameterXml);
    void BeginParameterXml(FunctorAsync& aFunctor);
    void EndParameterXml(IAsync& aAsync, Brh& aaParameterXml);

    void SyncSetParameter(const Brx& aaTarget, const Brx& aaName, const Brx& aaValue);
    void BeginSetParameter(const Brx& aaTarget, const Brx& aaName, const Brx& aaValue, FunctorAsync& aFunctor);
    void EndSetParameter(IAsync& aAsync);

    void SetPropertyConfigurationXmlChanged(Functor& aFunctor);
    void SetPropertyParameterXmlChanged(Functor& aFunctor);

    void PropertyConfigurationXml(Brhz& aConfigurationXml) const;
    void PropertyParameterXml(Brhz& aParameterXml) const;
private:
    void ConfigurationXmlPropertyChanged();
    void ParameterXmlPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionConfigurationXml;
    Action* iActionParameterXml;
    Action* iActionSetParameter;
    PropertyString* iConfigurationXml;
    PropertyString* iParameterXml;
    Functor iConfigurationXmlChanged;
    Functor iParameterXmlChanged;
};


class SyncConfigurationXmlLinnCoUkConfiguration1C : public SyncProxyAction
{
public:
    SyncConfigurationXmlLinnCoUkConfiguration1C(CpProxyLinnCoUkConfiguration1C& aProxy, Brh& aaConfigurationXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1C& iService;
    Brh& iaConfigurationXml;
};

SyncConfigurationXmlLinnCoUkConfiguration1C::SyncConfigurationXmlLinnCoUkConfiguration1C(CpProxyLinnCoUkConfiguration1C& aProxy, Brh& aaConfigurationXml)
    : iService(aProxy)
    , iaConfigurationXml(aaConfigurationXml)
{
}

void SyncConfigurationXmlLinnCoUkConfiguration1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndConfigurationXml(aAsync, iaConfigurationXml);
}


class SyncParameterXmlLinnCoUkConfiguration1C : public SyncProxyAction
{
public:
    SyncParameterXmlLinnCoUkConfiguration1C(CpProxyLinnCoUkConfiguration1C& aProxy, Brh& aaParameterXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1C& iService;
    Brh& iaParameterXml;
};

SyncParameterXmlLinnCoUkConfiguration1C::SyncParameterXmlLinnCoUkConfiguration1C(CpProxyLinnCoUkConfiguration1C& aProxy, Brh& aaParameterXml)
    : iService(aProxy)
    , iaParameterXml(aaParameterXml)
{
}

void SyncParameterXmlLinnCoUkConfiguration1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndParameterXml(aAsync, iaParameterXml);
}


class SyncSetParameterLinnCoUkConfiguration1C : public SyncProxyAction
{
public:
    SyncSetParameterLinnCoUkConfiguration1C(CpProxyLinnCoUkConfiguration1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1C& iService;
};

SyncSetParameterLinnCoUkConfiguration1C::SyncSetParameterLinnCoUkConfiguration1C(CpProxyLinnCoUkConfiguration1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetParameterLinnCoUkConfiguration1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetParameter(aAsync);
}

CpProxyLinnCoUkConfiguration1C::CpProxyLinnCoUkConfiguration1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Configuration", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionConfigurationXml = new Action("ConfigurationXml");
    param = new Zapp::ParameterString("aConfigurationXml");
    iActionConfigurationXml->AddOutputParameter(param);

    iActionParameterXml = new Action("ParameterXml");
    param = new Zapp::ParameterString("aParameterXml");
    iActionParameterXml->AddOutputParameter(param);

    iActionSetParameter = new Action("SetParameter");
    param = new Zapp::ParameterString("aTarget");
    iActionSetParameter->AddInputParameter(param);
    param = new Zapp::ParameterString("aName");
    iActionSetParameter->AddInputParameter(param);
    param = new Zapp::ParameterString("aValue");
    iActionSetParameter->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkConfiguration1C::ConfigurationXmlPropertyChanged);
    iConfigurationXml = new PropertyString("ConfigurationXml", functor);
    AddProperty(iConfigurationXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkConfiguration1C::ParameterXmlPropertyChanged);
    iParameterXml = new PropertyString("ParameterXml", functor);
    AddProperty(iParameterXml);
}

CpProxyLinnCoUkConfiguration1C::~CpProxyLinnCoUkConfiguration1C()
{
    delete iActionConfigurationXml;
    delete iActionParameterXml;
    delete iActionSetParameter;
}

void CpProxyLinnCoUkConfiguration1C::SyncConfigurationXml(Brh& aaConfigurationXml)
{
    SyncConfigurationXmlLinnCoUkConfiguration1C sync(*this, aaConfigurationXml);
    BeginConfigurationXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1C::BeginConfigurationXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionConfigurationXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionConfigurationXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkConfiguration1C::EndConfigurationXml(IAsync& aAsync, Brh& aaConfigurationXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ConfigurationXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaConfigurationXml);
}

void CpProxyLinnCoUkConfiguration1C::SyncParameterXml(Brh& aaParameterXml)
{
    SyncParameterXmlLinnCoUkConfiguration1C sync(*this, aaParameterXml);
    BeginParameterXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1C::BeginParameterXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionParameterXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionParameterXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkConfiguration1C::EndParameterXml(IAsync& aAsync, Brh& aaParameterXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ParameterXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaParameterXml);
}

void CpProxyLinnCoUkConfiguration1C::SyncSetParameter(const Brx& aaTarget, const Brx& aaName, const Brx& aaValue)
{
    SyncSetParameterLinnCoUkConfiguration1C sync(*this);
    BeginSetParameter(aaTarget, aaName, aaValue, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1C::BeginSetParameter(const Brx& aaTarget, const Brx& aaName, const Brx& aaValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetParameter, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetParameter->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaTarget));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkConfiguration1C::EndSetParameter(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetParameter"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkConfiguration1C::SetPropertyConfigurationXmlChanged(Functor& aFunctor)
{
    iLock.Wait();
    iConfigurationXmlChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkConfiguration1C::SetPropertyParameterXmlChanged(Functor& aFunctor)
{
    iLock.Wait();
    iParameterXmlChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkConfiguration1C::PropertyConfigurationXml(Brhz& aConfigurationXml) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aConfigurationXml.Set(iConfigurationXml->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkConfiguration1C::PropertyParameterXml(Brhz& aParameterXml) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aParameterXml.Set(iParameterXml->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkConfiguration1C::ConfigurationXmlPropertyChanged()
{
    ReportEvent(iConfigurationXmlChanged);
}

void CpProxyLinnCoUkConfiguration1C::ParameterXmlPropertyChanged()
{
    ReportEvent(iParameterXmlChanged);
}


THandle CpProxyLinnCoUkConfiguration1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkConfiguration1C(aDevice);
}

void CpProxyLinnCoUkConfiguration1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkConfiguration1SyncConfigurationXml(THandle aHandle, char** aaConfigurationXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConfigurationXml;
    proxyC->SyncConfigurationXml(buf_aaConfigurationXml);
    *aaConfigurationXml = buf_aaConfigurationXml.Extract();
}

void CpProxyLinnCoUkConfiguration1BeginConfigurationXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginConfigurationXml(functor);
}

int32_t CpProxyLinnCoUkConfiguration1EndConfigurationXml(THandle aHandle, ZappHandleAsync aAsync, char** aaConfigurationXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaConfigurationXml;
    *aaConfigurationXml = NULL;
    try {
        proxyC->EndConfigurationXml(*async, buf_aaConfigurationXml);
        *aaConfigurationXml = buf_aaConfigurationXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkConfiguration1SyncParameterXml(THandle aHandle, char** aaParameterXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaParameterXml;
    proxyC->SyncParameterXml(buf_aaParameterXml);
    *aaParameterXml = buf_aaParameterXml.Extract();
}

void CpProxyLinnCoUkConfiguration1BeginParameterXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginParameterXml(functor);
}

int32_t CpProxyLinnCoUkConfiguration1EndParameterXml(THandle aHandle, ZappHandleAsync aAsync, char** aaParameterXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaParameterXml;
    *aaParameterXml = NULL;
    try {
        proxyC->EndParameterXml(*async, buf_aaParameterXml);
        *aaParameterXml = buf_aaParameterXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkConfiguration1SyncSetParameter(THandle aHandle, const char* aaTarget, const char* aaName, const char* aaValue)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaTarget(aaTarget);
    Brh buf_aaName(aaName);
    Brh buf_aaValue(aaValue);
    proxyC->SyncSetParameter(buf_aaTarget, buf_aaName, buf_aaValue);
}

void CpProxyLinnCoUkConfiguration1BeginSetParameter(THandle aHandle, const char* aaTarget, const char* aaName, const char* aaValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaTarget(aaTarget);
    Brh buf_aaName(aaName);
    Brh buf_aaValue(aaValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetParameter(buf_aaTarget, buf_aaName, buf_aaValue, functor);
}

int32_t CpProxyLinnCoUkConfiguration1EndSetParameter(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetParameter(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyConfigurationXmlChanged(functor);
}

void CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyParameterXmlChanged(functor);
}

void CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(THandle aHandle, char** aConfigurationXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aConfigurationXml;
    proxyC->PropertyConfigurationXml(buf_aConfigurationXml);
    *aConfigurationXml = buf_aConfigurationXml.Transfer();
}

void CpProxyLinnCoUkConfiguration1PropertyParameterXml(THandle aHandle, char** aParameterXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aParameterXml;
    proxyC->PropertyParameterXml(buf_aParameterXml);
    *aParameterXml = buf_aParameterXml.Transfer();
}

