#include <Core/CpLinnCoUkConfiguration1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncConfigurationXmlLinnCoUkConfiguration1 : public SyncProxyAction
{
public:
    SyncConfigurationXmlLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1& aService, Brh& aaConfigurationXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1& iService;
    Brh& iaConfigurationXml;
};

SyncConfigurationXmlLinnCoUkConfiguration1::SyncConfigurationXmlLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1& aService, Brh& aaConfigurationXml)
    : iService(aService)
    , iaConfigurationXml(aaConfigurationXml)
{
}

void SyncConfigurationXmlLinnCoUkConfiguration1::CompleteRequest(IAsync& aAsync)
{
    iService.EndConfigurationXml(aAsync, iaConfigurationXml);
}


class SyncParameterXmlLinnCoUkConfiguration1 : public SyncProxyAction
{
public:
    SyncParameterXmlLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1& aService, Brh& aaParameterXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1& iService;
    Brh& iaParameterXml;
};

SyncParameterXmlLinnCoUkConfiguration1::SyncParameterXmlLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1& aService, Brh& aaParameterXml)
    : iService(aService)
    , iaParameterXml(aaParameterXml)
{
}

void SyncParameterXmlLinnCoUkConfiguration1::CompleteRequest(IAsync& aAsync)
{
    iService.EndParameterXml(aAsync, iaParameterXml);
}


class SyncSetParameterLinnCoUkConfiguration1 : public SyncProxyAction
{
public:
    SyncSetParameterLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1& iService;
};

SyncSetParameterLinnCoUkConfiguration1::SyncSetParameterLinnCoUkConfiguration1(CpProxyLinnCoUkConfiguration1& aService)
    : iService(aService)
{
}

void SyncSetParameterLinnCoUkConfiguration1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetParameter(aAsync);
}


CpProxyLinnCoUkConfiguration1::CpProxyLinnCoUkConfiguration1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Configuration", 1, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkConfiguration1::ConfigurationXmlPropertyChanged);
    iConfigurationXml = new PropertyString("ConfigurationXml", functor);
    iService->AddProperty(iConfigurationXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkConfiguration1::ParameterXmlPropertyChanged);
    iParameterXml = new PropertyString("ParameterXml", functor);
    iService->AddProperty(iParameterXml);
}

CpProxyLinnCoUkConfiguration1::~CpProxyLinnCoUkConfiguration1()
{
    delete iService;
    delete iActionConfigurationXml;
    delete iActionParameterXml;
    delete iActionSetParameter;
}

void CpProxyLinnCoUkConfiguration1::SyncConfigurationXml(Brh& aaConfigurationXml)
{
    SyncConfigurationXmlLinnCoUkConfiguration1 sync(*this, aaConfigurationXml);
    BeginConfigurationXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1::BeginConfigurationXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionConfigurationXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionConfigurationXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkConfiguration1::EndConfigurationXml(IAsync& aAsync, Brh& aaConfigurationXml)
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

void CpProxyLinnCoUkConfiguration1::SyncParameterXml(Brh& aaParameterXml)
{
    SyncParameterXmlLinnCoUkConfiguration1 sync(*this, aaParameterXml);
    BeginParameterXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1::BeginParameterXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionParameterXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionParameterXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkConfiguration1::EndParameterXml(IAsync& aAsync, Brh& aaParameterXml)
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

void CpProxyLinnCoUkConfiguration1::SyncSetParameter(const Brx& aaTarget, const Brx& aaName, const Brx& aaValue)
{
    SyncSetParameterLinnCoUkConfiguration1 sync(*this);
    BeginSetParameter(aaTarget, aaName, aaValue, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1::BeginSetParameter(const Brx& aaTarget, const Brx& aaName, const Brx& aaValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetParameter, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetParameter->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaTarget));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaValue));
    invocation->Invoke();
}

void CpProxyLinnCoUkConfiguration1::EndSetParameter(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetParameter"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkConfiguration1::SetPropertyConfigurationXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iConfigurationXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkConfiguration1::SetPropertyParameterXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iParameterXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkConfiguration1::PropertyConfigurationXml(Brhz& aConfigurationXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aConfigurationXml.Set(iConfigurationXml->Value());
}

void CpProxyLinnCoUkConfiguration1::PropertyParameterXml(Brhz& aParameterXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aParameterXml.Set(iParameterXml->Value());
}

void CpProxyLinnCoUkConfiguration1::ConfigurationXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iConfigurationXmlChanged != NULL) {
        iConfigurationXmlChanged();
    }
}

void CpProxyLinnCoUkConfiguration1::ParameterXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iParameterXmlChanged != NULL) {
        iParameterXmlChanged();
    }
}

