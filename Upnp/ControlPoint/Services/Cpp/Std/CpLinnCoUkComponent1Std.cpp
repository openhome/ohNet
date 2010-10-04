#include <Std/CpLinnCoUkComponent1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncAmplifierEnabledLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncAmplifierEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
    bool& iaEnabled;
};

SyncAmplifierEnabledLinnCoUkComponent1Cpp::SyncAmplifierEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaEnabled)
    : iService(aService)
    , iaEnabled(aaEnabled)
{
}

void SyncAmplifierEnabledLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierEnabled(aAsync, iaEnabled);
}


class SyncSetAmplifierEnabledLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncSetAmplifierEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
};

SyncSetAmplifierEnabledLinnCoUkComponent1Cpp::SyncSetAmplifierEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService)
    : iService(aService)
{
}

void SyncSetAmplifierEnabledLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAmplifierEnabled(aAsync);
}


class SyncAmplifierAttenuationLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncAmplifierAttenuationLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, std::string& aaAttenuation);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
    std::string& iaAttenuation;
};

SyncAmplifierAttenuationLinnCoUkComponent1Cpp::SyncAmplifierAttenuationLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, std::string& aaAttenuation)
    : iService(aService)
    , iaAttenuation(aaAttenuation)
{
}

void SyncAmplifierAttenuationLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierAttenuation(aAsync, iaAttenuation);
}


class SyncSetAmplifierAttenuationLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncSetAmplifierAttenuationLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
};

SyncSetAmplifierAttenuationLinnCoUkComponent1Cpp::SyncSetAmplifierAttenuationLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService)
    : iService(aService)
{
}

void SyncSetAmplifierAttenuationLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAmplifierAttenuation(aAsync);
}


class SyncSetVolumeControlEnabledLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeControlEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
};

SyncSetVolumeControlEnabledLinnCoUkComponent1Cpp::SyncSetVolumeControlEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService)
    : iService(aService)
{
}

void SyncSetVolumeControlEnabledLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeControlEnabled(aAsync);
}


class SyncVolumeControlEnabledLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncVolumeControlEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
    bool& iaEnabled;
};

SyncVolumeControlEnabledLinnCoUkComponent1Cpp::SyncVolumeControlEnabledLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaEnabled)
    : iService(aService)
    , iaEnabled(aaEnabled)
{
}

void SyncVolumeControlEnabledLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeControlEnabled(aAsync, iaEnabled);
}


class SyncSetDigitalAudioOutputRawLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncSetDigitalAudioOutputRawLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
};

SyncSetDigitalAudioOutputRawLinnCoUkComponent1Cpp::SyncSetDigitalAudioOutputRawLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService)
    : iService(aService)
{
}

void SyncSetDigitalAudioOutputRawLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDigitalAudioOutputRaw(aAsync);
}


class SyncDigitalAudioOutputRawLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncDigitalAudioOutputRawLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaRaw);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
    bool& iaRaw;
};

SyncDigitalAudioOutputRawLinnCoUkComponent1Cpp::SyncDigitalAudioOutputRawLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaRaw)
    : iService(aService)
    , iaRaw(aaRaw)
{
}

void SyncDigitalAudioOutputRawLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDigitalAudioOutputRaw(aAsync, iaRaw);
}


class SyncAmplifierOverTemperatureLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncAmplifierOverTemperatureLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaOverTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
    bool& iaOverTemperature;
};

SyncAmplifierOverTemperatureLinnCoUkComponent1Cpp::SyncAmplifierOverTemperatureLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaOverTemperature)
    : iService(aService)
    , iaOverTemperature(aaOverTemperature)
{
}

void SyncAmplifierOverTemperatureLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierOverTemperature(aAsync, iaOverTemperature);
}


class SyncEthernetLinkConnectedLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncEthernetLinkConnectedLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaLinkConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
    bool& iaLinkConnected;
};

SyncEthernetLinkConnectedLinnCoUkComponent1Cpp::SyncEthernetLinkConnectedLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService, bool& aaLinkConnected)
    : iService(aService)
    , iaLinkConnected(aaLinkConnected)
{
}

void SyncEthernetLinkConnectedLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEthernetLinkConnected(aAsync, iaLinkConnected);
}


class SyncLocateLinnCoUkComponent1Cpp : public SyncProxyAction
{
public:
    SyncLocateLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1Cpp& iService;
};

SyncLocateLinnCoUkComponent1Cpp::SyncLocateLinnCoUkComponent1Cpp(CpProxyLinnCoUkComponent1Cpp& aService)
    : iService(aService)
{
}

void SyncLocateLinnCoUkComponent1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndLocate(aAsync);
}


CpProxyLinnCoUkComponent1Cpp::CpProxyLinnCoUkComponent1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("linn-co-uk", "Component", 1, aDevice.Device());
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionAmplifierEnabled = new Action("AmplifierEnabled");
    param = new Zapp::ParameterBool("aEnabled");
    iActionAmplifierEnabled->AddOutputParameter(param);

    iActionSetAmplifierEnabled = new Action("SetAmplifierEnabled");
    param = new Zapp::ParameterBool("aEnabled");
    iActionSetAmplifierEnabled->AddInputParameter(param);

    iActionAmplifierAttenuation = new Action("AmplifierAttenuation");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"-12dB";
    allowedValues[index++] = (TChar*)"-9dB";
    allowedValues[index++] = (TChar*)"-6dB";
    allowedValues[index++] = (TChar*)"0dB";
    param = new Zapp::ParameterString("aAttenuation", allowedValues, 4);
    iActionAmplifierAttenuation->AddOutputParameter(param);
    delete[] allowedValues;

    iActionSetAmplifierAttenuation = new Action("SetAmplifierAttenuation");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"-12dB";
    allowedValues[index++] = (TChar*)"-9dB";
    allowedValues[index++] = (TChar*)"-6dB";
    allowedValues[index++] = (TChar*)"0dB";
    param = new Zapp::ParameterString("aAttenuation", allowedValues, 4);
    iActionSetAmplifierAttenuation->AddInputParameter(param);
    delete[] allowedValues;

    iActionSetVolumeControlEnabled = new Action("SetVolumeControlEnabled");
    param = new Zapp::ParameterBool("aEnabled");
    iActionSetVolumeControlEnabled->AddInputParameter(param);

    iActionVolumeControlEnabled = new Action("VolumeControlEnabled");
    param = new Zapp::ParameterBool("aEnabled");
    iActionVolumeControlEnabled->AddOutputParameter(param);

    iActionSetDigitalAudioOutputRaw = new Action("SetDigitalAudioOutputRaw");
    param = new Zapp::ParameterBool("aRaw");
    iActionSetDigitalAudioOutputRaw->AddInputParameter(param);

    iActionDigitalAudioOutputRaw = new Action("DigitalAudioOutputRaw");
    param = new Zapp::ParameterBool("aRaw");
    iActionDigitalAudioOutputRaw->AddOutputParameter(param);

    iActionAmplifierOverTemperature = new Action("AmplifierOverTemperature");
    param = new Zapp::ParameterBool("aOverTemperature");
    iActionAmplifierOverTemperature->AddOutputParameter(param);

    iActionEthernetLinkConnected = new Action("EthernetLinkConnected");
    param = new Zapp::ParameterBool("aLinkConnected");
    iActionEthernetLinkConnected->AddOutputParameter(param);

    iActionLocate = new Action("Locate");

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1Cpp::AmplifierEnabledPropertyChanged);
    iAmplifierEnabled = new PropertyBool("AmplifierEnabled", functor);
    iService->AddProperty(iAmplifierEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1Cpp::AmplifierAttenuationPropertyChanged);
    iAmplifierAttenuation = new PropertyString("AmplifierAttenuation", functor);
    iService->AddProperty(iAmplifierAttenuation);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1Cpp::VolumeControlEnabledPropertyChanged);
    iVolumeControlEnabled = new PropertyBool("VolumeControlEnabled", functor);
    iService->AddProperty(iVolumeControlEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1Cpp::DigitalAudioOutputRawPropertyChanged);
    iDigitalAudioOutputRaw = new PropertyBool("DigitalAudioOutputRaw", functor);
    iService->AddProperty(iDigitalAudioOutputRaw);
}

CpProxyLinnCoUkComponent1Cpp::~CpProxyLinnCoUkComponent1Cpp()
{
    delete iService;
    delete iActionAmplifierEnabled;
    delete iActionSetAmplifierEnabled;
    delete iActionAmplifierAttenuation;
    delete iActionSetAmplifierAttenuation;
    delete iActionSetVolumeControlEnabled;
    delete iActionVolumeControlEnabled;
    delete iActionSetDigitalAudioOutputRaw;
    delete iActionDigitalAudioOutputRaw;
    delete iActionAmplifierOverTemperature;
    delete iActionEthernetLinkConnected;
    delete iActionLocate;
}

void CpProxyLinnCoUkComponent1Cpp::SyncAmplifierEnabled(bool& aaEnabled)
{
    SyncAmplifierEnabledLinnCoUkComponent1Cpp sync(*this, aaEnabled);
    BeginAmplifierEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginAmplifierEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAmplifierEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndAmplifierEnabled(IAsync& aAsync, bool& aaEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AmplifierEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkComponent1Cpp::SyncSetAmplifierEnabled(bool aaEnabled)
{
    SyncSetAmplifierEnabledLinnCoUkComponent1Cpp sync(*this);
    BeginSetAmplifierEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginSetAmplifierEnabled(bool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAmplifierEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAmplifierEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndSetAmplifierEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAmplifierEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1Cpp::SyncAmplifierAttenuation(std::string& aaAttenuation)
{
    SyncAmplifierAttenuationLinnCoUkComponent1Cpp sync(*this, aaAttenuation);
    BeginAmplifierAttenuation(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginAmplifierAttenuation(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAmplifierAttenuation, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierAttenuation->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndAmplifierAttenuation(IAsync& aAsync, std::string& aaAttenuation)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AmplifierAttenuation"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaAttenuation.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkComponent1Cpp::SyncSetAmplifierAttenuation(const std::string& aaAttenuation)
{
    SyncSetAmplifierAttenuationLinnCoUkComponent1Cpp sync(*this);
    BeginSetAmplifierAttenuation(aaAttenuation, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginSetAmplifierAttenuation(const std::string& aaAttenuation, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAmplifierAttenuation, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAmplifierAttenuation->InputParameters();
    {
        Brn buf((const TByte*)aaAttenuation.c_str(), aaAttenuation.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndSetAmplifierAttenuation(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAmplifierAttenuation"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1Cpp::SyncSetVolumeControlEnabled(bool aaEnabled)
{
    SyncSetVolumeControlEnabledLinnCoUkComponent1Cpp sync(*this);
    BeginSetVolumeControlEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginSetVolumeControlEnabled(bool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeControlEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeControlEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndSetVolumeControlEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeControlEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1Cpp::SyncVolumeControlEnabled(bool& aaEnabled)
{
    SyncVolumeControlEnabledLinnCoUkComponent1Cpp sync(*this, aaEnabled);
    BeginVolumeControlEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginVolumeControlEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeControlEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeControlEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndVolumeControlEnabled(IAsync& aAsync, bool& aaEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeControlEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkComponent1Cpp::SyncSetDigitalAudioOutputRaw(bool aaRaw)
{
    SyncSetDigitalAudioOutputRawLinnCoUkComponent1Cpp sync(*this);
    BeginSetDigitalAudioOutputRaw(aaRaw, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginSetDigitalAudioOutputRaw(bool aaRaw, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDigitalAudioOutputRaw, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDigitalAudioOutputRaw->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaRaw));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndSetDigitalAudioOutputRaw(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDigitalAudioOutputRaw"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1Cpp::SyncDigitalAudioOutputRaw(bool& aaRaw)
{
    SyncDigitalAudioOutputRawLinnCoUkComponent1Cpp sync(*this, aaRaw);
    BeginDigitalAudioOutputRaw(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginDigitalAudioOutputRaw(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDigitalAudioOutputRaw, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDigitalAudioOutputRaw->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndDigitalAudioOutputRaw(IAsync& aAsync, bool& aaRaw)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("DigitalAudioOutputRaw"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaRaw = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkComponent1Cpp::SyncAmplifierOverTemperature(bool& aaOverTemperature)
{
    SyncAmplifierOverTemperatureLinnCoUkComponent1Cpp sync(*this, aaOverTemperature);
    BeginAmplifierOverTemperature(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginAmplifierOverTemperature(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAmplifierOverTemperature, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierOverTemperature->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndAmplifierOverTemperature(IAsync& aAsync, bool& aaOverTemperature)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AmplifierOverTemperature"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaOverTemperature = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkComponent1Cpp::SyncEthernetLinkConnected(bool& aaLinkConnected)
{
    SyncEthernetLinkConnectedLinnCoUkComponent1Cpp sync(*this, aaLinkConnected);
    BeginEthernetLinkConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginEthernetLinkConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEthernetLinkConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEthernetLinkConnected->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndEthernetLinkConnected(IAsync& aAsync, bool& aaLinkConnected)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("EthernetLinkConnected"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaLinkConnected = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkComponent1Cpp::SyncLocate()
{
    SyncLocateLinnCoUkComponent1Cpp sync(*this);
    BeginLocate(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1Cpp::BeginLocate(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLocate, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1Cpp::EndLocate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Locate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1Cpp::SetPropertyAmplifierEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAmplifierEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1Cpp::SetPropertyAmplifierAttenuationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAmplifierAttenuationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1Cpp::SetPropertyVolumeControlEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeControlEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1Cpp::SetPropertyDigitalAudioOutputRawChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDigitalAudioOutputRawChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1Cpp::PropertyAmplifierEnabled(bool& aAmplifierEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAmplifierEnabled = iAmplifierEnabled->Value();
}

void CpProxyLinnCoUkComponent1Cpp::PropertyAmplifierAttenuation(std::string& aAmplifierAttenuation) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iAmplifierAttenuation->Value();
    aAmplifierAttenuation.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkComponent1Cpp::PropertyVolumeControlEnabled(bool& aVolumeControlEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeControlEnabled = iVolumeControlEnabled->Value();
}

void CpProxyLinnCoUkComponent1Cpp::PropertyDigitalAudioOutputRaw(bool& aDigitalAudioOutputRaw) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDigitalAudioOutputRaw = iDigitalAudioOutputRaw->Value();
}

void CpProxyLinnCoUkComponent1Cpp::AmplifierEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iAmplifierEnabledChanged != NULL) {
        iAmplifierEnabledChanged();
    }
}

void CpProxyLinnCoUkComponent1Cpp::AmplifierAttenuationPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iAmplifierAttenuationChanged != NULL) {
        iAmplifierAttenuationChanged();
    }
}

void CpProxyLinnCoUkComponent1Cpp::VolumeControlEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVolumeControlEnabledChanged != NULL) {
        iVolumeControlEnabledChanged();
    }
}

void CpProxyLinnCoUkComponent1Cpp::DigitalAudioOutputRawPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDigitalAudioOutputRawChanged != NULL) {
        iDigitalAudioOutputRawChanged();
    }
}

