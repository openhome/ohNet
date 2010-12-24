#include "CpLinnCoUkComponent1.h"
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

class CpProxyLinnCoUkComponent1C : public CpProxyC
{
public:
    CpProxyLinnCoUkComponent1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkComponent1C();
    //CpProxyLinnCoUkComponent1* Proxy() { return static_cast<CpProxyLinnCoUkComponent1*>(iProxy); }

    void SyncAmplifierEnabled(TBool& aaEnabled);
    void BeginAmplifierEnabled(FunctorAsync& aFunctor);
    void EndAmplifierEnabled(IAsync& aAsync, TBool& aaEnabled);

    void SyncSetAmplifierEnabled(TBool aaEnabled);
    void BeginSetAmplifierEnabled(TBool aaEnabled, FunctorAsync& aFunctor);
    void EndSetAmplifierEnabled(IAsync& aAsync);

    void SyncAmplifierAttenuation(Brh& aaAttenuation);
    void BeginAmplifierAttenuation(FunctorAsync& aFunctor);
    void EndAmplifierAttenuation(IAsync& aAsync, Brh& aaAttenuation);

    void SyncSetAmplifierAttenuation(const Brx& aaAttenuation);
    void BeginSetAmplifierAttenuation(const Brx& aaAttenuation, FunctorAsync& aFunctor);
    void EndSetAmplifierAttenuation(IAsync& aAsync);

    void SyncSetVolumeControlEnabled(TBool aaEnabled);
    void BeginSetVolumeControlEnabled(TBool aaEnabled, FunctorAsync& aFunctor);
    void EndSetVolumeControlEnabled(IAsync& aAsync);

    void SyncVolumeControlEnabled(TBool& aaEnabled);
    void BeginVolumeControlEnabled(FunctorAsync& aFunctor);
    void EndVolumeControlEnabled(IAsync& aAsync, TBool& aaEnabled);

    void SyncSetDigitalAudioOutputRaw(TBool aaRaw);
    void BeginSetDigitalAudioOutputRaw(TBool aaRaw, FunctorAsync& aFunctor);
    void EndSetDigitalAudioOutputRaw(IAsync& aAsync);

    void SyncDigitalAudioOutputRaw(TBool& aaRaw);
    void BeginDigitalAudioOutputRaw(FunctorAsync& aFunctor);
    void EndDigitalAudioOutputRaw(IAsync& aAsync, TBool& aaRaw);

    void SyncAmplifierOverTemperature(TBool& aaOverTemperature);
    void BeginAmplifierOverTemperature(FunctorAsync& aFunctor);
    void EndAmplifierOverTemperature(IAsync& aAsync, TBool& aaOverTemperature);

    void SyncEthernetLinkConnected(TBool& aaLinkConnected);
    void BeginEthernetLinkConnected(FunctorAsync& aFunctor);
    void EndEthernetLinkConnected(IAsync& aAsync, TBool& aaLinkConnected);

    void SyncLocate();
    void BeginLocate(FunctorAsync& aFunctor);
    void EndLocate(IAsync& aAsync);

    void SetPropertyAmplifierEnabledChanged(Functor& aFunctor);
    void SetPropertyAmplifierAttenuationChanged(Functor& aFunctor);
    void SetPropertyVolumeControlEnabledChanged(Functor& aFunctor);
    void SetPropertyDigitalAudioOutputRawChanged(Functor& aFunctor);

    void PropertyAmplifierEnabled(TBool& aAmplifierEnabled) const;
    void PropertyAmplifierAttenuation(Brhz& aAmplifierAttenuation) const;
    void PropertyVolumeControlEnabled(TBool& aVolumeControlEnabled) const;
    void PropertyDigitalAudioOutputRaw(TBool& aDigitalAudioOutputRaw) const;
private:
    void AmplifierEnabledPropertyChanged();
    void AmplifierAttenuationPropertyChanged();
    void VolumeControlEnabledPropertyChanged();
    void DigitalAudioOutputRawPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionAmplifierEnabled;
    Action* iActionSetAmplifierEnabled;
    Action* iActionAmplifierAttenuation;
    Action* iActionSetAmplifierAttenuation;
    Action* iActionSetVolumeControlEnabled;
    Action* iActionVolumeControlEnabled;
    Action* iActionSetDigitalAudioOutputRaw;
    Action* iActionDigitalAudioOutputRaw;
    Action* iActionAmplifierOverTemperature;
    Action* iActionEthernetLinkConnected;
    Action* iActionLocate;
    PropertyBool* iAmplifierEnabled;
    PropertyString* iAmplifierAttenuation;
    PropertyBool* iVolumeControlEnabled;
    PropertyBool* iDigitalAudioOutputRaw;
    Functor iAmplifierEnabledChanged;
    Functor iAmplifierAttenuationChanged;
    Functor iVolumeControlEnabledChanged;
    Functor iDigitalAudioOutputRawChanged;
};


class SyncAmplifierEnabledLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncAmplifierEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
    TBool& iaEnabled;
};

SyncAmplifierEnabledLinnCoUkComponent1C::SyncAmplifierEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaEnabled)
    : iService(aProxy)
    , iaEnabled(aaEnabled)
{
}

void SyncAmplifierEnabledLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierEnabled(aAsync, iaEnabled);
}


class SyncSetAmplifierEnabledLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncSetAmplifierEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
};

SyncSetAmplifierEnabledLinnCoUkComponent1C::SyncSetAmplifierEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetAmplifierEnabledLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAmplifierEnabled(aAsync);
}


class SyncAmplifierAttenuationLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncAmplifierAttenuationLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, Brh& aaAttenuation);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
    Brh& iaAttenuation;
};

SyncAmplifierAttenuationLinnCoUkComponent1C::SyncAmplifierAttenuationLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, Brh& aaAttenuation)
    : iService(aProxy)
    , iaAttenuation(aaAttenuation)
{
}

void SyncAmplifierAttenuationLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierAttenuation(aAsync, iaAttenuation);
}


class SyncSetAmplifierAttenuationLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncSetAmplifierAttenuationLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
};

SyncSetAmplifierAttenuationLinnCoUkComponent1C::SyncSetAmplifierAttenuationLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetAmplifierAttenuationLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetAmplifierAttenuation(aAsync);
}


class SyncSetVolumeControlEnabledLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncSetVolumeControlEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
};

SyncSetVolumeControlEnabledLinnCoUkComponent1C::SyncSetVolumeControlEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeControlEnabledLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeControlEnabled(aAsync);
}


class SyncVolumeControlEnabledLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncVolumeControlEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
    TBool& iaEnabled;
};

SyncVolumeControlEnabledLinnCoUkComponent1C::SyncVolumeControlEnabledLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaEnabled)
    : iService(aProxy)
    , iaEnabled(aaEnabled)
{
}

void SyncVolumeControlEnabledLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeControlEnabled(aAsync, iaEnabled);
}


class SyncSetDigitalAudioOutputRawLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncSetDigitalAudioOutputRawLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
};

SyncSetDigitalAudioOutputRawLinnCoUkComponent1C::SyncSetDigitalAudioOutputRawLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetDigitalAudioOutputRawLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetDigitalAudioOutputRaw(aAsync);
}


class SyncDigitalAudioOutputRawLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncDigitalAudioOutputRawLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaRaw);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
    TBool& iaRaw;
};

SyncDigitalAudioOutputRawLinnCoUkComponent1C::SyncDigitalAudioOutputRawLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaRaw)
    : iService(aProxy)
    , iaRaw(aaRaw)
{
}

void SyncDigitalAudioOutputRawLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDigitalAudioOutputRaw(aAsync, iaRaw);
}


class SyncAmplifierOverTemperatureLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncAmplifierOverTemperatureLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaOverTemperature);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
    TBool& iaOverTemperature;
};

SyncAmplifierOverTemperatureLinnCoUkComponent1C::SyncAmplifierOverTemperatureLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaOverTemperature)
    : iService(aProxy)
    , iaOverTemperature(aaOverTemperature)
{
}

void SyncAmplifierOverTemperatureLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndAmplifierOverTemperature(aAsync, iaOverTemperature);
}


class SyncEthernetLinkConnectedLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncEthernetLinkConnectedLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaLinkConnected);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
    TBool& iaLinkConnected;
};

SyncEthernetLinkConnectedLinnCoUkComponent1C::SyncEthernetLinkConnectedLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy, TBool& aaLinkConnected)
    : iService(aProxy)
    , iaLinkConnected(aaLinkConnected)
{
}

void SyncEthernetLinkConnectedLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEthernetLinkConnected(aAsync, iaLinkConnected);
}


class SyncLocateLinnCoUkComponent1C : public SyncProxyAction
{
public:
    SyncLocateLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkComponent1C& iService;
};

SyncLocateLinnCoUkComponent1C::SyncLocateLinnCoUkComponent1C(CpProxyLinnCoUkComponent1C& aProxy)
    : iService(aProxy)
{
}

void SyncLocateLinnCoUkComponent1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndLocate(aAsync);
}

CpProxyLinnCoUkComponent1C::CpProxyLinnCoUkComponent1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Component", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1C::AmplifierEnabledPropertyChanged);
    iAmplifierEnabled = new PropertyBool("AmplifierEnabled", functor);
    AddProperty(iAmplifierEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1C::AmplifierAttenuationPropertyChanged);
    iAmplifierAttenuation = new PropertyString("AmplifierAttenuation", functor);
    AddProperty(iAmplifierAttenuation);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1C::VolumeControlEnabledPropertyChanged);
    iVolumeControlEnabled = new PropertyBool("VolumeControlEnabled", functor);
    AddProperty(iVolumeControlEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkComponent1C::DigitalAudioOutputRawPropertyChanged);
    iDigitalAudioOutputRaw = new PropertyBool("DigitalAudioOutputRaw", functor);
    AddProperty(iDigitalAudioOutputRaw);
}

CpProxyLinnCoUkComponent1C::~CpProxyLinnCoUkComponent1C()
{
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

void CpProxyLinnCoUkComponent1C::SyncAmplifierEnabled(TBool& aaEnabled)
{
    SyncAmplifierEnabledLinnCoUkComponent1C sync(*this, aaEnabled);
    BeginAmplifierEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginAmplifierEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionAmplifierEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndAmplifierEnabled(IAsync& aAsync, TBool& aaEnabled)
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

void CpProxyLinnCoUkComponent1C::SyncSetAmplifierEnabled(TBool aaEnabled)
{
    SyncSetAmplifierEnabledLinnCoUkComponent1C sync(*this);
    BeginSetAmplifierEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginSetAmplifierEnabled(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetAmplifierEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAmplifierEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndSetAmplifierEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAmplifierEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1C::SyncAmplifierAttenuation(Brh& aaAttenuation)
{
    SyncAmplifierAttenuationLinnCoUkComponent1C sync(*this, aaAttenuation);
    BeginAmplifierAttenuation(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginAmplifierAttenuation(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionAmplifierAttenuation, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierAttenuation->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndAmplifierAttenuation(IAsync& aAsync, Brh& aaAttenuation)
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

void CpProxyLinnCoUkComponent1C::SyncSetAmplifierAttenuation(const Brx& aaAttenuation)
{
    SyncSetAmplifierAttenuationLinnCoUkComponent1C sync(*this);
    BeginSetAmplifierAttenuation(aaAttenuation, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginSetAmplifierAttenuation(const Brx& aaAttenuation, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetAmplifierAttenuation, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetAmplifierAttenuation->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaAttenuation));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndSetAmplifierAttenuation(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetAmplifierAttenuation"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1C::SyncSetVolumeControlEnabled(TBool aaEnabled)
{
    SyncSetVolumeControlEnabledLinnCoUkComponent1C sync(*this);
    BeginSetVolumeControlEnabled(aaEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginSetVolumeControlEnabled(TBool aaEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolumeControlEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeControlEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaEnabled));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndSetVolumeControlEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeControlEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1C::SyncVolumeControlEnabled(TBool& aaEnabled)
{
    SyncVolumeControlEnabledLinnCoUkComponent1C sync(*this, aaEnabled);
    BeginVolumeControlEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginVolumeControlEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeControlEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeControlEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndVolumeControlEnabled(IAsync& aAsync, TBool& aaEnabled)
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

void CpProxyLinnCoUkComponent1C::SyncSetDigitalAudioOutputRaw(TBool aaRaw)
{
    SyncSetDigitalAudioOutputRawLinnCoUkComponent1C sync(*this);
    BeginSetDigitalAudioOutputRaw(aaRaw, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginSetDigitalAudioOutputRaw(TBool aaRaw, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetDigitalAudioOutputRaw, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetDigitalAudioOutputRaw->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaRaw));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndSetDigitalAudioOutputRaw(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetDigitalAudioOutputRaw"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1C::SyncDigitalAudioOutputRaw(TBool& aaRaw)
{
    SyncDigitalAudioOutputRawLinnCoUkComponent1C sync(*this, aaRaw);
    BeginDigitalAudioOutputRaw(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginDigitalAudioOutputRaw(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDigitalAudioOutputRaw, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDigitalAudioOutputRaw->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndDigitalAudioOutputRaw(IAsync& aAsync, TBool& aaRaw)
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

void CpProxyLinnCoUkComponent1C::SyncAmplifierOverTemperature(TBool& aaOverTemperature)
{
    SyncAmplifierOverTemperatureLinnCoUkComponent1C sync(*this, aaOverTemperature);
    BeginAmplifierOverTemperature(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginAmplifierOverTemperature(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionAmplifierOverTemperature, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAmplifierOverTemperature->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndAmplifierOverTemperature(IAsync& aAsync, TBool& aaOverTemperature)
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

void CpProxyLinnCoUkComponent1C::SyncEthernetLinkConnected(TBool& aaLinkConnected)
{
    SyncEthernetLinkConnectedLinnCoUkComponent1C sync(*this, aaLinkConnected);
    BeginEthernetLinkConnected(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginEthernetLinkConnected(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEthernetLinkConnected, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEthernetLinkConnected->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndEthernetLinkConnected(IAsync& aAsync, TBool& aaLinkConnected)
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

void CpProxyLinnCoUkComponent1C::SyncLocate()
{
    SyncLocateLinnCoUkComponent1C sync(*this);
    BeginLocate(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkComponent1C::BeginLocate(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionLocate, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkComponent1C::EndLocate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Locate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkComponent1C::SetPropertyAmplifierEnabledChanged(Functor& aFunctor)
{
    iLock.Wait();
    iAmplifierEnabledChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkComponent1C::SetPropertyAmplifierAttenuationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iAmplifierAttenuationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkComponent1C::SetPropertyVolumeControlEnabledChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeControlEnabledChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkComponent1C::SetPropertyDigitalAudioOutputRawChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDigitalAudioOutputRawChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkComponent1C::PropertyAmplifierEnabled(TBool& aAmplifierEnabled) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aAmplifierEnabled = iAmplifierEnabled->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkComponent1C::PropertyAmplifierAttenuation(Brhz& aAmplifierAttenuation) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aAmplifierAttenuation.Set(iAmplifierAttenuation->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkComponent1C::PropertyVolumeControlEnabled(TBool& aVolumeControlEnabled) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aVolumeControlEnabled = iVolumeControlEnabled->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkComponent1C::PropertyDigitalAudioOutputRaw(TBool& aDigitalAudioOutputRaw) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aDigitalAudioOutputRaw = iDigitalAudioOutputRaw->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkComponent1C::AmplifierEnabledPropertyChanged()
{
    ReportEvent(iAmplifierEnabledChanged);
}

void CpProxyLinnCoUkComponent1C::AmplifierAttenuationPropertyChanged()
{
    ReportEvent(iAmplifierAttenuationChanged);
}

void CpProxyLinnCoUkComponent1C::VolumeControlEnabledPropertyChanged()
{
    ReportEvent(iVolumeControlEnabledChanged);
}

void CpProxyLinnCoUkComponent1C::DigitalAudioOutputRawPropertyChanged()
{
    ReportEvent(iDigitalAudioOutputRawChanged);
}


THandle CpProxyLinnCoUkComponent1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkComponent1C(aDevice);
}

void CpProxyLinnCoUkComponent1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkComponent1SyncAmplifierEnabled(THandle aHandle, uint32_t* aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaEnabled = 0;
    proxyC->SyncAmplifierEnabled(*(TBool*)aaEnabled);
}

void CpProxyLinnCoUkComponent1BeginAmplifierEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginAmplifierEnabled(functor);
}

int32_t CpProxyLinnCoUkComponent1EndAmplifierEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaEnabled = 0;
    try {
        proxyC->EndAmplifierEnabled(*async, *(TBool*)aaEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetAmplifierEnabled(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetAmplifierEnabled((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkComponent1BeginSetAmplifierEnabled(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetAmplifierEnabled((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetAmplifierEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetAmplifierEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncAmplifierAttenuation(THandle aHandle, char** aaAttenuation)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaAttenuation;
    proxyC->SyncAmplifierAttenuation(buf_aaAttenuation);
    *aaAttenuation = buf_aaAttenuation.Extract();
}

void CpProxyLinnCoUkComponent1BeginAmplifierAttenuation(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginAmplifierAttenuation(functor);
}

int32_t CpProxyLinnCoUkComponent1EndAmplifierAttenuation(THandle aHandle, ZappHandleAsync aAsync, char** aaAttenuation)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaAttenuation;
    *aaAttenuation = NULL;
    try {
        proxyC->EndAmplifierAttenuation(*async, buf_aaAttenuation);
        *aaAttenuation = buf_aaAttenuation.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetAmplifierAttenuation(THandle aHandle, const char* aaAttenuation)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaAttenuation(aaAttenuation);
    proxyC->SyncSetAmplifierAttenuation(buf_aaAttenuation);
}

void CpProxyLinnCoUkComponent1BeginSetAmplifierAttenuation(THandle aHandle, const char* aaAttenuation, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaAttenuation(aaAttenuation);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetAmplifierAttenuation(buf_aaAttenuation, functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetAmplifierAttenuation(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetAmplifierAttenuation(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetVolumeControlEnabled(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetVolumeControlEnabled((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkComponent1BeginSetVolumeControlEnabled(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetVolumeControlEnabled((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetVolumeControlEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetVolumeControlEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncVolumeControlEnabled(THandle aHandle, uint32_t* aaEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaEnabled = 0;
    proxyC->SyncVolumeControlEnabled(*(TBool*)aaEnabled);
}

void CpProxyLinnCoUkComponent1BeginVolumeControlEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeControlEnabled(functor);
}

int32_t CpProxyLinnCoUkComponent1EndVolumeControlEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaEnabled = 0;
    try {
        proxyC->EndVolumeControlEnabled(*async, *(TBool*)aaEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncSetDigitalAudioOutputRaw(THandle aHandle, uint32_t aaRaw)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetDigitalAudioOutputRaw((aaRaw==0? false : true));
}

void CpProxyLinnCoUkComponent1BeginSetDigitalAudioOutputRaw(THandle aHandle, uint32_t aaRaw, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetDigitalAudioOutputRaw((aaRaw==0? false : true), functor);
}

int32_t CpProxyLinnCoUkComponent1EndSetDigitalAudioOutputRaw(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetDigitalAudioOutputRaw(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncDigitalAudioOutputRaw(THandle aHandle, uint32_t* aaRaw)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaRaw = 0;
    proxyC->SyncDigitalAudioOutputRaw(*(TBool*)aaRaw);
}

void CpProxyLinnCoUkComponent1BeginDigitalAudioOutputRaw(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDigitalAudioOutputRaw(functor);
}

int32_t CpProxyLinnCoUkComponent1EndDigitalAudioOutputRaw(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaRaw)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaRaw = 0;
    try {
        proxyC->EndDigitalAudioOutputRaw(*async, *(TBool*)aaRaw);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncAmplifierOverTemperature(THandle aHandle, uint32_t* aaOverTemperature)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaOverTemperature = 0;
    proxyC->SyncAmplifierOverTemperature(*(TBool*)aaOverTemperature);
}

void CpProxyLinnCoUkComponent1BeginAmplifierOverTemperature(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginAmplifierOverTemperature(functor);
}

int32_t CpProxyLinnCoUkComponent1EndAmplifierOverTemperature(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaOverTemperature)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaOverTemperature = 0;
    try {
        proxyC->EndAmplifierOverTemperature(*async, *(TBool*)aaOverTemperature);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncEthernetLinkConnected(THandle aHandle, uint32_t* aaLinkConnected)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaLinkConnected = 0;
    proxyC->SyncEthernetLinkConnected(*(TBool*)aaLinkConnected);
}

void CpProxyLinnCoUkComponent1BeginEthernetLinkConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginEthernetLinkConnected(functor);
}

int32_t CpProxyLinnCoUkComponent1EndEthernetLinkConnected(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaLinkConnected)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaLinkConnected = 0;
    try {
        proxyC->EndEthernetLinkConnected(*async, *(TBool*)aaLinkConnected);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SyncLocate(THandle aHandle)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncLocate();
}

void CpProxyLinnCoUkComponent1BeginLocate(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginLocate(functor);
}

int32_t CpProxyLinnCoUkComponent1EndLocate(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndLocate(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkComponent1SetPropertyAmplifierEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyAmplifierEnabledChanged(functor);
}

void CpProxyLinnCoUkComponent1SetPropertyAmplifierAttenuationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyAmplifierAttenuationChanged(functor);
}

void CpProxyLinnCoUkComponent1SetPropertyVolumeControlEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeControlEnabledChanged(functor);
}

void CpProxyLinnCoUkComponent1SetPropertyDigitalAudioOutputRawChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDigitalAudioOutputRawChanged(functor);
}

void CpProxyLinnCoUkComponent1PropertyAmplifierEnabled(THandle aHandle, uint32_t* aAmplifierEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aAmplifierEnabled = false;
    proxyC->PropertyAmplifierEnabled(*(TBool*)aAmplifierEnabled);
}

void CpProxyLinnCoUkComponent1PropertyAmplifierAttenuation(THandle aHandle, char** aAmplifierAttenuation)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aAmplifierAttenuation;
    proxyC->PropertyAmplifierAttenuation(buf_aAmplifierAttenuation);
    *aAmplifierAttenuation = buf_aAmplifierAttenuation.Transfer();
}

void CpProxyLinnCoUkComponent1PropertyVolumeControlEnabled(THandle aHandle, uint32_t* aVolumeControlEnabled)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aVolumeControlEnabled = false;
    proxyC->PropertyVolumeControlEnabled(*(TBool*)aVolumeControlEnabled);
}

void CpProxyLinnCoUkComponent1PropertyDigitalAudioOutputRaw(THandle aHandle, uint32_t* aDigitalAudioOutputRaw)
{
    CpProxyLinnCoUkComponent1C* proxyC = reinterpret_cast<CpProxyLinnCoUkComponent1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDigitalAudioOutputRaw = false;
    proxyC->PropertyDigitalAudioOutputRaw(*(TBool*)aDigitalAudioOutputRaw);
}

