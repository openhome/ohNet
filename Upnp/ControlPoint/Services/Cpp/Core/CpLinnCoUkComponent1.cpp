#include <Core/CpLinnCoUkComponent1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncAmplifierEnabledLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncAmplifierEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
    TBool& iaEnabled;
};

SyncAmplifierEnabledLinnCoUkComponent1::SyncAmplifierEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaEnabled)
    : iService(aService)
    , iaEnabled(aaEnabled)
{
}

void SyncAmplifierEnabledLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierEnabled(aAsync, iaEnabled);
}


class SyncSetAmplifierEnabledLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncSetAmplifierEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
};

SyncSetAmplifierEnabledLinnCoUkComponent1::SyncSetAmplifierEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService)
    : iService(aService)
{
}

void SyncSetAmplifierEnabledLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAmplifierEnabled(aAsync);
}


class SyncAmplifierAttenuationLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncAmplifierAttenuationLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, Brh& aaAttenuation);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
    Brh& iaAttenuation;
};

SyncAmplifierAttenuationLinnCoUkComponent1::SyncAmplifierAttenuationLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, Brh& aaAttenuation)
    : iService(aService)
    , iaAttenuation(aaAttenuation)
{
}

void SyncAmplifierAttenuationLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierAttenuation(aAsync, iaAttenuation);
}


class SyncSetAmplifierAttenuationLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncSetAmplifierAttenuationLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
};

SyncSetAmplifierAttenuationLinnCoUkComponent1::SyncSetAmplifierAttenuationLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService)
    : iService(aService)
{
}

void SyncSetAmplifierAttenuationLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAmplifierAttenuation(aAsync);
}


class SyncSetVolumeControlEnabledLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncSetVolumeControlEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
};

SyncSetVolumeControlEnabledLinnCoUkComponent1::SyncSetVolumeControlEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService)
    : iService(aService)
{
}

void SyncSetVolumeControlEnabledLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeControlEnabled(aAsync);
}


class SyncVolumeControlEnabledLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncVolumeControlEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
    TBool& iaEnabled;
};

SyncVolumeControlEnabledLinnCoUkComponent1::SyncVolumeControlEnabledLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaEnabled)
    : iService(aService)
    , iaEnabled(aaEnabled)
{
}

void SyncVolumeControlEnabledLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeControlEnabled(aAsync, iaEnabled);
}


class SyncSetDigitalAudioOutputRawLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncSetDigitalAudioOutputRawLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
};

SyncSetDigitalAudioOutputRawLinnCoUkComponent1::SyncSetDigitalAudioOutputRawLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService)
    : iService(aService)
{
}

void SyncSetDigitalAudioOutputRawLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDigitalAudioOutputRaw(aAsync);
}


class SyncDigitalAudioOutputRawLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncDigitalAudioOutputRawLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaRaw);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
    TBool& iaRaw;
};

SyncDigitalAudioOutputRawLinnCoUkComponent1::SyncDigitalAudioOutputRawLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaRaw)
    : iService(aService)
    , iaRaw(aaRaw)
{
}

void SyncDigitalAudioOutputRawLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDigitalAudioOutputRaw(aAsync, iaRaw);
}


class SyncAmplifierOverTemperatureLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncAmplifierOverTemperatureLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaOverTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
    TBool& iaOverTemperature;
};

SyncAmplifierOverTemperatureLinnCoUkComponent1::SyncAmplifierOverTemperatureLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaOverTemperature)
    : iService(aService)
    , iaOverTemperature(aaOverTemperature)
{
}

void SyncAmplifierOverTemperatureLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierOverTemperature(aAsync, iaOverTemperature);
}


class SyncEthernetLinkConnectedLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncEthernetLinkConnectedLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaLinkConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
    TBool& iaLinkConnected;
};

SyncEthernetLinkConnectedLinnCoUkComponent1::SyncEthernetLinkConnectedLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService, TBool& aaLinkConnected)
    : iService(aService)
    , iaLinkConnected(aaLinkConnected)
{
}

void SyncEthernetLinkConnectedLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndEthernetLinkConnected(aAsync, iaLinkConnected);
}


class SyncLocateLinnCoUkComponent1 : public SyncProxyAction
{
public:
    SyncLocateLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1& iService;
};

SyncLocateLinnCoUkComponent1::SyncLocateLinnCoUkComponent1(CpProxyLinnCoUkComponent1& aService)
    : iService(aService)
{
}

void SyncLocateLinnCoUkComponent1::CompleteRequest(IAsync& aAsync)
{
    iService.EndLocate(aAsync);
}


CpProxyLinnCoUkComponent1::CpProxyLinnCoUkComponent1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1::AmplifierEnabledPropertyChanged);
    iAmplifierEnabled = new PropertyBool("AmplifierEnabled", functor);
    iService->AddProperty(iAmplifierEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1::AmplifierAttenuationPropertyChanged);
    iAmplifierAttenuation = new PropertyString("AmplifierAttenuation", functor);
    iService->AddProperty(iAmplifierAttenuation);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1::VolumeControlEnabledPropertyChanged);
    iVolumeControlEnabled = new PropertyBool("VolumeControlEnabled", functor);
    iService->AddProperty(iVolumeControlEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1::DigitalAudioOutputRawPropertyChanged);
    iDigitalAudioOutputRaw = new PropertyBool("DigitalAudioOutputRaw", functor);
    iService->AddProperty(iDigitalAudioOutputRaw);
}

CpProxyLinnCoUkComponent1::~CpProxyLinnCoUkComponent1()
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

void CpProxyLinnCoUkComponent1::SyncAmplifierEnabled(TBool& aaEnabled)
{
    SyncAmplifierEnabledLinnCoUkComponent1 sync(*this, aaEnabled);
    BeginAmplifierEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginAmplifierEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAmplifierEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndAmplifierEnabled(IAsync& aAsync, TBool& aaEnabled)
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

void CpProxyLinnCoUkComponent1::SyncSetAmplifierEnabled(TBool aaEnabled)
{
    SyncSetAmplifierEnabledLinnCoUkComponent1 sync(*this);
    BeginSetAmplifierEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginSetAmplifierEnabled(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAmplifierEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAmplifierEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndSetAmplifierEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAmplifierEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1::SyncAmplifierAttenuation(Brh& aaAttenuation)
{
    SyncAmplifierAttenuationLinnCoUkComponent1 sync(*this, aaAttenuation);
    BeginAmplifierAttenuation(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginAmplifierAttenuation(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAmplifierAttenuation, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierAttenuation->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndAmplifierAttenuation(IAsync& aAsync, Brh& aaAttenuation)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("AmplifierAttenuation"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaAttenuation);
}

void CpProxyLinnCoUkComponent1::SyncSetAmplifierAttenuation(const Brx& aaAttenuation)
{
    SyncSetAmplifierAttenuationLinnCoUkComponent1 sync(*this);
    BeginSetAmplifierAttenuation(aaAttenuation, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginSetAmplifierAttenuation(const Brx& aaAttenuation, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetAmplifierAttenuation, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAmplifierAttenuation->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaAttenuation));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndSetAmplifierAttenuation(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAmplifierAttenuation"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1::SyncSetVolumeControlEnabled(TBool aaEnabled)
{
    SyncSetVolumeControlEnabledLinnCoUkComponent1 sync(*this);
    BeginSetVolumeControlEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginSetVolumeControlEnabled(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeControlEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeControlEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndSetVolumeControlEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeControlEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1::SyncVolumeControlEnabled(TBool& aaEnabled)
{
    SyncVolumeControlEnabledLinnCoUkComponent1 sync(*this, aaEnabled);
    BeginVolumeControlEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginVolumeControlEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeControlEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeControlEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndVolumeControlEnabled(IAsync& aAsync, TBool& aaEnabled)
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

void CpProxyLinnCoUkComponent1::SyncSetDigitalAudioOutputRaw(TBool aaRaw)
{
    SyncSetDigitalAudioOutputRawLinnCoUkComponent1 sync(*this);
    BeginSetDigitalAudioOutputRaw(aaRaw, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginSetDigitalAudioOutputRaw(TBool aaRaw, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetDigitalAudioOutputRaw, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDigitalAudioOutputRaw->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaRaw));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndSetDigitalAudioOutputRaw(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDigitalAudioOutputRaw"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1::SyncDigitalAudioOutputRaw(TBool& aaRaw)
{
    SyncDigitalAudioOutputRawLinnCoUkComponent1 sync(*this, aaRaw);
    BeginDigitalAudioOutputRaw(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginDigitalAudioOutputRaw(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDigitalAudioOutputRaw, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDigitalAudioOutputRaw->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndDigitalAudioOutputRaw(IAsync& aAsync, TBool& aaRaw)
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

void CpProxyLinnCoUkComponent1::SyncAmplifierOverTemperature(TBool& aaOverTemperature)
{
    SyncAmplifierOverTemperatureLinnCoUkComponent1 sync(*this, aaOverTemperature);
    BeginAmplifierOverTemperature(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginAmplifierOverTemperature(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAmplifierOverTemperature, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierOverTemperature->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndAmplifierOverTemperature(IAsync& aAsync, TBool& aaOverTemperature)
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

void CpProxyLinnCoUkComponent1::SyncEthernetLinkConnected(TBool& aaLinkConnected)
{
    SyncEthernetLinkConnectedLinnCoUkComponent1 sync(*this, aaLinkConnected);
    BeginEthernetLinkConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginEthernetLinkConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEthernetLinkConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEthernetLinkConnected->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndEthernetLinkConnected(IAsync& aAsync, TBool& aaLinkConnected)
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

void CpProxyLinnCoUkComponent1::SyncLocate()
{
    SyncLocateLinnCoUkComponent1 sync(*this);
    BeginLocate(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1::BeginLocate(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionLocate, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkComponent1::EndLocate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Locate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1::SetPropertyAmplifierEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAmplifierEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1::SetPropertyAmplifierAttenuationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAmplifierAttenuationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1::SetPropertyVolumeControlEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeControlEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1::SetPropertyDigitalAudioOutputRawChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDigitalAudioOutputRawChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkComponent1::PropertyAmplifierEnabled(TBool& aAmplifierEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAmplifierEnabled = iAmplifierEnabled->Value();
}

void CpProxyLinnCoUkComponent1::PropertyAmplifierAttenuation(Brhz& aAmplifierAttenuation) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAmplifierAttenuation.Set(iAmplifierAttenuation->Value());
}

void CpProxyLinnCoUkComponent1::PropertyVolumeControlEnabled(TBool& aVolumeControlEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeControlEnabled = iVolumeControlEnabled->Value();
}

void CpProxyLinnCoUkComponent1::PropertyDigitalAudioOutputRaw(TBool& aDigitalAudioOutputRaw) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDigitalAudioOutputRaw = iDigitalAudioOutputRaw->Value();
}

void CpProxyLinnCoUkComponent1::AmplifierEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iAmplifierEnabledChanged != NULL) {
        iAmplifierEnabledChanged();
    }
}

void CpProxyLinnCoUkComponent1::AmplifierAttenuationPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iAmplifierAttenuationChanged != NULL) {
        iAmplifierAttenuationChanged();
    }
}

void CpProxyLinnCoUkComponent1::VolumeControlEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVolumeControlEnabledChanged != NULL) {
        iVolumeControlEnabledChanged();
    }
}

void CpProxyLinnCoUkComponent1::DigitalAudioOutputRawPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDigitalAudioOutputRawChanged != NULL) {
        iDigitalAudioOutputRawChanged();
    }
}

