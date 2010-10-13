#include <Std/CpLinnCoUkConfiguration1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncConfigurationXmlLinnCoUkConfiguration1Cpp : public SyncProxyAction
{
public:
    SyncConfigurationXmlLinnCoUkConfiguration1Cpp(CpProxyLinnCoUkConfiguration1Cpp& aService, std::string& aaConfigurationXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1Cpp& iService;
    std::string& iaConfigurationXml;
};

SyncConfigurationXmlLinnCoUkConfiguration1Cpp::SyncConfigurationXmlLinnCoUkConfiguration1Cpp(CpProxyLinnCoUkConfiguration1Cpp& aService, std::string& aaConfigurationXml)
    : iService(aService)
    , iaConfigurationXml(aaConfigurationXml)
{
}

void SyncConfigurationXmlLinnCoUkConfiguration1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndConfigurationXml(aAsync, iaConfigurationXml);
}


class SyncParameterXmlLinnCoUkConfiguration1Cpp : public SyncProxyAction
{
public:
    SyncParameterXmlLinnCoUkConfiguration1Cpp(CpProxyLinnCoUkConfiguration1Cpp& aService, std::string& aaParameterXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1Cpp& iService;
    std::string& iaParameterXml;
};

SyncParameterXmlLinnCoUkConfiguration1Cpp::SyncParameterXmlLinnCoUkConfiguration1Cpp(CpProxyLinnCoUkConfiguration1Cpp& aService, std::string& aaParameterXml)
    : iService(aService)
    , iaParameterXml(aaParameterXml)
{
}

void SyncParameterXmlLinnCoUkConfiguration1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndParameterXml(aAsync, iaParameterXml);
}


class SyncSetParameterLinnCoUkConfiguration1Cpp : public SyncProxyAction
{
public:
    SyncSetParameterLinnCoUkConfiguration1Cpp(CpProxyLinnCoUkConfiguration1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkConfiguration1Cpp& iService;
};

SyncSetParameterLinnCoUkConfiguration1Cpp::SyncSetParameterLinnCoUkConfiguration1Cpp(CpProxyLinnCoUkConfiguration1Cpp& aService)
    : iService(aService)
{
}

void SyncSetParameterLinnCoUkConfiguration1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetParameter(aAsync);
}


CpProxyLinnCoUkConfiguration1Cpp::CpProxyLinnCoUkConfiguration1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkConfiguration1Cpp::ConfigurationXmlPropertyChanged);
    iConfigurationXml = new PropertyString("ConfigurationXml", functor);
    iService->AddProperty(iConfigurationXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkConfiguration1Cpp::ParameterXmlPropertyChanged);
    iParameterXml = new PropertyString("ParameterXml", functor);
    iService->AddProperty(iParameterXml);
}

CpProxyLinnCoUkConfiguration1Cpp::~CpProxyLinnCoUkConfiguration1Cpp()
{
    delete iService;
    delete iActionConfigurationXml;
    delete iActionParameterXml;
    delete iActionSetParameter;
}

void CpProxyLinnCoUkConfiguration1Cpp::SyncConfigurationXml(std::string& aaConfigurationXml)
{
    SyncConfigurationXmlLinnCoUkConfiguration1Cpp sync(*this, aaConfigurationXml);
    BeginConfigurationXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1Cpp::BeginConfigurationXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionConfigurationXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionConfigurationXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkConfiguration1Cpp::EndConfigurationXml(IAsync& aAsync, std::string& aaConfigurationXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ConfigurationXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaConfigurationXml.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkConfiguration1Cpp::SyncParameterXml(std::string& aaParameterXml)
{
    SyncParameterXmlLinnCoUkConfiguration1Cpp sync(*this, aaParameterXml);
    BeginParameterXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1Cpp::BeginParameterXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionParameterXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionParameterXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkConfiguration1Cpp::EndParameterXml(IAsync& aAsync, std::string& aaParameterXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ParameterXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaParameterXml.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkConfiguration1Cpp::SyncSetParameter(const std::string& aaTarget, const std::string& aaName, const std::string& aaValue)
{
    SyncSetParameterLinnCoUkConfiguration1Cpp sync(*this);
    BeginSetParameter(aaTarget, aaName, aaValue, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkConfiguration1Cpp::BeginSetParameter(const std::string& aaTarget, const std::string& aaName, const std::string& aaValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetParameter, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetParameter->InputParameters();
    {
        Brn buf((const TByte*)aaTarget.c_str(), aaTarget.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aaName.c_str(), aaName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    {
        Brn buf((const TByte*)aaValue.c_str(), aaValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkConfiguration1Cpp::EndSetParameter(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetParameter"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkConfiguration1Cpp::SetPropertyConfigurationXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iConfigurationXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkConfiguration1Cpp::SetPropertyParameterXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iParameterXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkConfiguration1Cpp::PropertyConfigurationXml(std::string& aConfigurationXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iConfigurationXml->Value();
    aConfigurationXml.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkConfiguration1Cpp::PropertyParameterXml(std::string& aParameterXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iParameterXml->Value();
    aParameterXml.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkConfiguration1Cpp::ConfigurationXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iConfigurationXmlChanged != NULL) {
        iConfigurationXmlChanged();
    }
}

void CpProxyLinnCoUkConfiguration1Cpp::ParameterXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iParameterXmlChanged != NULL) {
        iParameterXmlChanged();
    }
}

