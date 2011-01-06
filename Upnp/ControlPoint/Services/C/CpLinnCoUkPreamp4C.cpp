#include "CpLinnCoUkPreamp4.h"
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

class CpProxyLinnCoUkPreamp4C : public CpProxyC
{
public:
    CpProxyLinnCoUkPreamp4C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkPreamp4C();
    //CpProxyLinnCoUkPreamp4* Proxy() { return static_cast<CpProxyLinnCoUkPreamp4*>(iProxy); }

    void SyncVolumeInc();
    void BeginVolumeInc(FunctorAsync& aFunctor);
    void EndVolumeInc(IAsync& aAsync);

    void SyncVolumeDec();
    void BeginVolumeDec(FunctorAsync& aFunctor);
    void EndVolumeDec(IAsync& aAsync);

    void SyncSetVolume(TUint aaVolume);
    void BeginSetVolume(TUint aaVolume, FunctorAsync& aFunctor);
    void EndSetVolume(IAsync& aAsync);

    void SyncVolume(TUint& aaVolume);
    void BeginVolume(FunctorAsync& aFunctor);
    void EndVolume(IAsync& aAsync, TUint& aaVolume);

    void SyncSetMute(TBool aaMute);
    void BeginSetMute(TBool aaMute, FunctorAsync& aFunctor);
    void EndSetMute(IAsync& aAsync);

    void SyncMute(TBool& aaMute);
    void BeginMute(FunctorAsync& aFunctor);
    void EndMute(IAsync& aAsync, TBool& aaMute);

    void SyncSetBalance(TInt aaBalance);
    void BeginSetBalance(TInt aaBalance, FunctorAsync& aFunctor);
    void EndSetBalance(IAsync& aAsync);

    void SyncBalance(TInt& aaBalance);
    void BeginBalance(FunctorAsync& aFunctor);
    void EndBalance(IAsync& aAsync, TInt& aaBalance);

    void SyncSetVolumeLimit(TUint aaVolumeLimit);
    void BeginSetVolumeLimit(TUint aaVolumeLimit, FunctorAsync& aFunctor);
    void EndSetVolumeLimit(IAsync& aAsync);

    void SyncVolumeLimit(TUint& aaVolumeLimit);
    void BeginVolumeLimit(FunctorAsync& aFunctor);
    void EndVolumeLimit(IAsync& aAsync, TUint& aaVolumeLimit);

    void SyncSetStartupVolume(TUint aaStartupVolume);
    void BeginSetStartupVolume(TUint aaStartupVolume, FunctorAsync& aFunctor);
    void EndSetStartupVolume(IAsync& aAsync);

    void SyncStartupVolume(TUint& aaStartupVolume);
    void BeginStartupVolume(FunctorAsync& aFunctor);
    void EndStartupVolume(IAsync& aAsync, TUint& aaStartupVolume);

    void SyncSetStartupVolumeEnabled(TBool aaStartupVolumeEnabled);
    void BeginSetStartupVolumeEnabled(TBool aaStartupVolumeEnabled, FunctorAsync& aFunctor);
    void EndSetStartupVolumeEnabled(IAsync& aAsync);

    void SyncStartupVolumeEnabled(TBool& aaStartupVolumeEnabled);
    void BeginStartupVolumeEnabled(FunctorAsync& aFunctor);
    void EndStartupVolumeEnabled(IAsync& aAsync, TBool& aaStartupVolumeEnabled);

    void SetPropertyVolumeChanged(Functor& aFunctor);
    void SetPropertyMuteChanged(Functor& aFunctor);
    void SetPropertyBalanceChanged(Functor& aFunctor);
    void SetPropertyVolumeLimitChanged(Functor& aFunctor);
    void SetPropertyStartupVolumeChanged(Functor& aFunctor);
    void SetPropertyStartupVolumeEnabledChanged(Functor& aFunctor);

    void PropertyVolume(TUint& aVolume) const;
    void PropertyMute(TBool& aMute) const;
    void PropertyBalance(TInt& aBalance) const;
    void PropertyVolumeLimit(TUint& aVolumeLimit) const;
    void PropertyStartupVolume(TUint& aStartupVolume) const;
    void PropertyStartupVolumeEnabled(TBool& aStartupVolumeEnabled) const;
private:
    void VolumePropertyChanged();
    void MutePropertyChanged();
    void BalancePropertyChanged();
    void VolumeLimitPropertyChanged();
    void StartupVolumePropertyChanged();
    void StartupVolumeEnabledPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionVolumeInc;
    Action* iActionVolumeDec;
    Action* iActionSetVolume;
    Action* iActionVolume;
    Action* iActionSetMute;
    Action* iActionMute;
    Action* iActionSetBalance;
    Action* iActionBalance;
    Action* iActionSetVolumeLimit;
    Action* iActionVolumeLimit;
    Action* iActionSetStartupVolume;
    Action* iActionStartupVolume;
    Action* iActionSetStartupVolumeEnabled;
    Action* iActionStartupVolumeEnabled;
    PropertyUint* iVolume;
    PropertyBool* iMute;
    PropertyInt* iBalance;
    PropertyUint* iVolumeLimit;
    PropertyUint* iStartupVolume;
    PropertyBool* iStartupVolumeEnabled;
    Functor iVolumeChanged;
    Functor iMuteChanged;
    Functor iBalanceChanged;
    Functor iVolumeLimitChanged;
    Functor iStartupVolumeChanged;
    Functor iStartupVolumeEnabledChanged;
};


class SyncVolumeIncLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncVolumeIncLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncVolumeIncLinnCoUkPreamp4C::SyncVolumeIncLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncVolumeIncLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeInc(aAsync);
}


class SyncVolumeDecLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncVolumeDecLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncVolumeDecLinnCoUkPreamp4C::SyncVolumeDecLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncVolumeDecLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeDec(aAsync);
}


class SyncSetVolumeLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncSetVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncSetVolumeLinnCoUkPreamp4C::SyncSetVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncVolumeLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TUint& aaVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
    TUint& iaVolume;
};

SyncVolumeLinnCoUkPreamp4C::SyncVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TUint& aaVolume)
    : iService(aProxy)
    , iaVolume(aaVolume)
{
}

void SyncVolumeLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolume(aAsync, iaVolume);
}


class SyncSetMuteLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncSetMuteLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncSetMuteLinnCoUkPreamp4C::SyncSetMuteLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncMuteLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncMuteLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TBool& aaMute);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
    TBool& iaMute;
};

SyncMuteLinnCoUkPreamp4C::SyncMuteLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TBool& aaMute)
    : iService(aProxy)
    , iaMute(aaMute)
{
}

void SyncMuteLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMute(aAsync, iaMute);
}


class SyncSetBalanceLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncSetBalanceLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncSetBalanceLinnCoUkPreamp4C::SyncSetBalanceLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBalanceLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBalance(aAsync);
}


class SyncBalanceLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncBalanceLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TInt& aaBalance);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
    TInt& iaBalance;
};

SyncBalanceLinnCoUkPreamp4C::SyncBalanceLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TInt& aaBalance)
    : iService(aProxy)
    , iaBalance(aaBalance)
{
}

void SyncBalanceLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalance(aAsync, iaBalance);
}


class SyncSetVolumeLimitLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncSetVolumeLimitLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncSetVolumeLimitLinnCoUkPreamp4C::SyncSetVolumeLimitLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeLimitLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeLimit(aAsync);
}


class SyncVolumeLimitLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncVolumeLimitLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TUint& aaVolumeLimit);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
    TUint& iaVolumeLimit;
};

SyncVolumeLimitLinnCoUkPreamp4C::SyncVolumeLimitLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TUint& aaVolumeLimit)
    : iService(aProxy)
    , iaVolumeLimit(aaVolumeLimit)
{
}

void SyncVolumeLimitLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeLimit(aAsync, iaVolumeLimit);
}


class SyncSetStartupVolumeLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncSetStartupVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncSetStartupVolumeLinnCoUkPreamp4C::SyncSetStartupVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStartupVolumeLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupVolume(aAsync);
}


class SyncStartupVolumeLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncStartupVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TUint& aaStartupVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
    TUint& iaStartupVolume;
};

SyncStartupVolumeLinnCoUkPreamp4C::SyncStartupVolumeLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TUint& aaStartupVolume)
    : iService(aProxy)
    , iaStartupVolume(aaStartupVolume)
{
}

void SyncStartupVolumeLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupVolume(aAsync, iaStartupVolume);
}


class SyncSetStartupVolumeEnabledLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncSetStartupVolumeEnabledLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
};

SyncSetStartupVolumeEnabledLinnCoUkPreamp4C::SyncSetStartupVolumeEnabledLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStartupVolumeEnabledLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupVolumeEnabled(aAsync);
}


class SyncStartupVolumeEnabledLinnCoUkPreamp4C : public SyncProxyAction
{
public:
    SyncStartupVolumeEnabledLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TBool& aaStartupVolumeEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4C& iService;
    TBool& iaStartupVolumeEnabled;
};

SyncStartupVolumeEnabledLinnCoUkPreamp4C::SyncStartupVolumeEnabledLinnCoUkPreamp4C(CpProxyLinnCoUkPreamp4C& aProxy, TBool& aaStartupVolumeEnabled)
    : iService(aProxy)
    , iaStartupVolumeEnabled(aaStartupVolumeEnabled)
{
}

void SyncStartupVolumeEnabledLinnCoUkPreamp4C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupVolumeEnabled(aAsync, iaStartupVolumeEnabled);
}

CpProxyLinnCoUkPreamp4C::CpProxyLinnCoUkPreamp4C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Preamp", 4, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionVolumeInc = new Action("VolumeInc");

    iActionVolumeDec = new Action("VolumeDec");

    iActionSetVolume = new Action("SetVolume");
    param = new Zapp::ParameterUint("aVolume");
    iActionSetVolume->AddInputParameter(param);

    iActionVolume = new Action("Volume");
    param = new Zapp::ParameterUint("aVolume");
    iActionVolume->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new Zapp::ParameterBool("aMute");
    iActionSetMute->AddInputParameter(param);

    iActionMute = new Action("Mute");
    param = new Zapp::ParameterBool("aMute");
    iActionMute->AddOutputParameter(param);

    iActionSetBalance = new Action("SetBalance");
    param = new Zapp::ParameterInt("aBalance");
    iActionSetBalance->AddInputParameter(param);

    iActionBalance = new Action("Balance");
    param = new Zapp::ParameterInt("aBalance");
    iActionBalance->AddOutputParameter(param);

    iActionSetVolumeLimit = new Action("SetVolumeLimit");
    param = new Zapp::ParameterUint("aVolumeLimit");
    iActionSetVolumeLimit->AddInputParameter(param);

    iActionVolumeLimit = new Action("VolumeLimit");
    param = new Zapp::ParameterUint("aVolumeLimit");
    iActionVolumeLimit->AddOutputParameter(param);

    iActionSetStartupVolume = new Action("SetStartupVolume");
    param = new Zapp::ParameterUint("aStartupVolume");
    iActionSetStartupVolume->AddInputParameter(param);

    iActionStartupVolume = new Action("StartupVolume");
    param = new Zapp::ParameterUint("aStartupVolume");
    iActionStartupVolume->AddOutputParameter(param);

    iActionSetStartupVolumeEnabled = new Action("SetStartupVolumeEnabled");
    param = new Zapp::ParameterBool("aStartupVolumeEnabled");
    iActionSetStartupVolumeEnabled->AddInputParameter(param);

    iActionStartupVolumeEnabled = new Action("StartupVolumeEnabled");
    param = new Zapp::ParameterBool("aStartupVolumeEnabled");
    iActionStartupVolumeEnabled->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4C::VolumePropertyChanged);
    iVolume = new PropertyUint("Volume", functor);
    AddProperty(iVolume);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4C::MutePropertyChanged);
    iMute = new PropertyBool("Mute", functor);
    AddProperty(iMute);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4C::BalancePropertyChanged);
    iBalance = new PropertyInt("Balance", functor);
    AddProperty(iBalance);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4C::VolumeLimitPropertyChanged);
    iVolumeLimit = new PropertyUint("VolumeLimit", functor);
    AddProperty(iVolumeLimit);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4C::StartupVolumePropertyChanged);
    iStartupVolume = new PropertyUint("StartupVolume", functor);
    AddProperty(iStartupVolume);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4C::StartupVolumeEnabledPropertyChanged);
    iStartupVolumeEnabled = new PropertyBool("StartupVolumeEnabled", functor);
    AddProperty(iStartupVolumeEnabled);
}

CpProxyLinnCoUkPreamp4C::~CpProxyLinnCoUkPreamp4C()
{
    DestroyService();
    delete iActionVolumeInc;
    delete iActionVolumeDec;
    delete iActionSetVolume;
    delete iActionVolume;
    delete iActionSetMute;
    delete iActionMute;
    delete iActionSetBalance;
    delete iActionBalance;
    delete iActionSetVolumeLimit;
    delete iActionVolumeLimit;
    delete iActionSetStartupVolume;
    delete iActionStartupVolume;
    delete iActionSetStartupVolumeEnabled;
    delete iActionStartupVolumeEnabled;
}

void CpProxyLinnCoUkPreamp4C::SyncVolumeInc()
{
    SyncVolumeIncLinnCoUkPreamp4C sync(*this);
    BeginVolumeInc(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginVolumeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeInc, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndVolumeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeInc"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncVolumeDec()
{
    SyncVolumeDecLinnCoUkPreamp4C sync(*this);
    BeginVolumeDec(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginVolumeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeDec, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndVolumeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeDec"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncSetVolume(TUint aaVolume)
{
    SyncSetVolumeLinnCoUkPreamp4C sync(*this);
    BeginSetVolume(aaVolume, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginSetVolume(TUint aaVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaVolume));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncVolume(TUint& aaVolume)
{
    SyncVolumeLinnCoUkPreamp4C sync(*this, aaVolume);
    BeginVolume(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndVolume(IAsync& aAsync, TUint& aaVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Volume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaVolume = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPreamp4C::SyncSetMute(TBool aaMute)
{
    SyncSetMuteLinnCoUkPreamp4C sync(*this);
    BeginSetMute(aaMute, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginSetMute(TBool aaMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaMute));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncMute(TBool& aaMute)
{
    SyncMuteLinnCoUkPreamp4C sync(*this, aaMute);
    BeginMute(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginMute(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMute, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndMute(IAsync& aAsync, TBool& aaMute)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Mute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaMute = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPreamp4C::SyncSetBalance(TInt aaBalance)
{
    SyncSetBalanceLinnCoUkPreamp4C sync(*this);
    BeginSetBalance(aaBalance, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginSetBalance(TInt aaBalance, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBalance, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBalance->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaBalance));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndSetBalance(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBalance"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncBalance(TInt& aaBalance)
{
    SyncBalanceLinnCoUkPreamp4C sync(*this, aaBalance);
    BeginBalance(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginBalance(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBalance, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBalance->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndBalance(IAsync& aAsync, TInt& aaBalance)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Balance"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaBalance = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPreamp4C::SyncSetVolumeLimit(TUint aaVolumeLimit)
{
    SyncSetVolumeLimitLinnCoUkPreamp4C sync(*this);
    BeginSetVolumeLimit(aaVolumeLimit, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginSetVolumeLimit(TUint aaVolumeLimit, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolumeLimit, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeLimit->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaVolumeLimit));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndSetVolumeLimit(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeLimit"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncVolumeLimit(TUint& aaVolumeLimit)
{
    SyncVolumeLimitLinnCoUkPreamp4C sync(*this, aaVolumeLimit);
    BeginVolumeLimit(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginVolumeLimit(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeLimit, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeLimit->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndVolumeLimit(IAsync& aAsync, TUint& aaVolumeLimit)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeLimit"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaVolumeLimit = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPreamp4C::SyncSetStartupVolume(TUint aaStartupVolume)
{
    SyncSetStartupVolumeLinnCoUkPreamp4C sync(*this);
    BeginSetStartupVolume(aaStartupVolume, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginSetStartupVolume(TUint aaStartupVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStartupVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaStartupVolume));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndSetStartupVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncStartupVolume(TUint& aaStartupVolume)
{
    SyncStartupVolumeLinnCoUkPreamp4C sync(*this, aaStartupVolume);
    BeginStartupVolume(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginStartupVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartupVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndStartupVolume(IAsync& aAsync, TUint& aaStartupVolume)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartupVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStartupVolume = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPreamp4C::SyncSetStartupVolumeEnabled(TBool aaStartupVolumeEnabled)
{
    SyncSetStartupVolumeEnabledLinnCoUkPreamp4C sync(*this);
    BeginSetStartupVolumeEnabled(aaStartupVolumeEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginSetStartupVolumeEnabled(TBool aaStartupVolumeEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStartupVolumeEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupVolumeEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStartupVolumeEnabled));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndSetStartupVolumeEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupVolumeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4C::SyncStartupVolumeEnabled(TBool& aaStartupVolumeEnabled)
{
    SyncStartupVolumeEnabledLinnCoUkPreamp4C sync(*this, aaStartupVolumeEnabled);
    BeginStartupVolumeEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4C::BeginStartupVolumeEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartupVolumeEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupVolumeEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkPreamp4C::EndStartupVolumeEnabled(IAsync& aAsync, TBool& aaStartupVolumeEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartupVolumeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStartupVolumeEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkPreamp4C::SetPropertyVolumeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::SetPropertyMuteChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMuteChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::SetPropertyBalanceChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBalanceChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::SetPropertyVolumeLimitChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeLimitChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::SetPropertyStartupVolumeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStartupVolumeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::SetPropertyStartupVolumeEnabledChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStartupVolumeEnabledChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::PropertyVolume(TUint& aVolume) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aVolume = iVolume->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::PropertyMute(TBool& aMute) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aMute = iMute->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::PropertyBalance(TInt& aBalance) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aBalance = iBalance->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::PropertyVolumeLimit(TUint& aVolumeLimit) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aVolumeLimit = iVolumeLimit->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::PropertyStartupVolume(TUint& aStartupVolume) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aStartupVolume = iStartupVolume->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::PropertyStartupVolumeEnabled(TBool& aStartupVolumeEnabled) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aStartupVolumeEnabled = iStartupVolumeEnabled->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkPreamp4C::VolumePropertyChanged()
{
    ReportEvent(iVolumeChanged);
}

void CpProxyLinnCoUkPreamp4C::MutePropertyChanged()
{
    ReportEvent(iMuteChanged);
}

void CpProxyLinnCoUkPreamp4C::BalancePropertyChanged()
{
    ReportEvent(iBalanceChanged);
}

void CpProxyLinnCoUkPreamp4C::VolumeLimitPropertyChanged()
{
    ReportEvent(iVolumeLimitChanged);
}

void CpProxyLinnCoUkPreamp4C::StartupVolumePropertyChanged()
{
    ReportEvent(iStartupVolumeChanged);
}

void CpProxyLinnCoUkPreamp4C::StartupVolumeEnabledPropertyChanged()
{
    ReportEvent(iStartupVolumeEnabledChanged);
}


THandle CpProxyLinnCoUkPreamp4Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkPreamp4C(aDevice);
}

void CpProxyLinnCoUkPreamp4Destroy(THandle aHandle)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkPreamp4SyncVolumeInc(THandle aHandle)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolumeInc();
}

void CpProxyLinnCoUkPreamp4BeginVolumeInc(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeInc(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolumeInc(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndVolumeInc(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncVolumeDec(THandle aHandle)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolumeDec();
}

void CpProxyLinnCoUkPreamp4BeginVolumeDec(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeDec(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolumeDec(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndVolumeDec(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetVolume(THandle aHandle, uint32_t aaVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetVolume(aaVolume);
}

void CpProxyLinnCoUkPreamp4BeginSetVolume(THandle aHandle, uint32_t aaVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetVolume(aaVolume, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetVolume(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncVolume(THandle aHandle, uint32_t* aaVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolume(*aaVolume);
}

void CpProxyLinnCoUkPreamp4BeginVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolume(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaVolume)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndVolume(*async, *aaVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetMute(THandle aHandle, uint32_t aaMute)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetMute((aaMute==0? false : true));
}

void CpProxyLinnCoUkPreamp4BeginSetMute(THandle aHandle, uint32_t aaMute, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetMute((aaMute==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetMute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetMute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncMute(THandle aHandle, uint32_t* aaMute)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaMute = 0;
    proxyC->SyncMute(*(TBool*)aaMute);
}

void CpProxyLinnCoUkPreamp4BeginMute(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginMute(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaMute)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaMute = 0;
    try {
        proxyC->EndMute(*async, *(TBool*)aaMute);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetBalance(THandle aHandle, int32_t aaBalance)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBalance(aaBalance);
}

void CpProxyLinnCoUkPreamp4BeginSetBalance(THandle aHandle, int32_t aaBalance, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetBalance(aaBalance, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetBalance(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetBalance(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncBalance(THandle aHandle, int32_t* aaBalance)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncBalance(*aaBalance);
}

void CpProxyLinnCoUkPreamp4BeginBalance(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBalance(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndBalance(THandle aHandle, ZappHandleAsync aAsync, int32_t* aaBalance)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndBalance(*async, *aaBalance);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetVolumeLimit(THandle aHandle, uint32_t aaVolumeLimit)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetVolumeLimit(aaVolumeLimit);
}

void CpProxyLinnCoUkPreamp4BeginSetVolumeLimit(THandle aHandle, uint32_t aaVolumeLimit, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetVolumeLimit(aaVolumeLimit, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetVolumeLimit(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetVolumeLimit(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncVolumeLimit(THandle aHandle, uint32_t* aaVolumeLimit)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolumeLimit(*aaVolumeLimit);
}

void CpProxyLinnCoUkPreamp4BeginVolumeLimit(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeLimit(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndVolumeLimit(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaVolumeLimit)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndVolumeLimit(*async, *aaVolumeLimit);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetStartupVolume(THandle aHandle, uint32_t aaStartupVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStartupVolume(aaStartupVolume);
}

void CpProxyLinnCoUkPreamp4BeginSetStartupVolume(THandle aHandle, uint32_t aaStartupVolume, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStartupVolume(aaStartupVolume, functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetStartupVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStartupVolume(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncStartupVolume(THandle aHandle, uint32_t* aaStartupVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStartupVolume(*aaStartupVolume);
}

void CpProxyLinnCoUkPreamp4BeginStartupVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartupVolume(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndStartupVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupVolume)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStartupVolume(*async, *aaStartupVolume);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncSetStartupVolumeEnabled(THandle aHandle, uint32_t aaStartupVolumeEnabled)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStartupVolumeEnabled((aaStartupVolumeEnabled==0? false : true));
}

void CpProxyLinnCoUkPreamp4BeginSetStartupVolumeEnabled(THandle aHandle, uint32_t aaStartupVolumeEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStartupVolumeEnabled((aaStartupVolumeEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPreamp4EndSetStartupVolumeEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStartupVolumeEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SyncStartupVolumeEnabled(THandle aHandle, uint32_t* aaStartupVolumeEnabled)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStartupVolumeEnabled = 0;
    proxyC->SyncStartupVolumeEnabled(*(TBool*)aaStartupVolumeEnabled);
}

void CpProxyLinnCoUkPreamp4BeginStartupVolumeEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartupVolumeEnabled(functor);
}

int32_t CpProxyLinnCoUkPreamp4EndStartupVolumeEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupVolumeEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStartupVolumeEnabled = 0;
    try {
        proxyC->EndStartupVolumeEnabled(*async, *(TBool*)aaStartupVolumeEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPreamp4SetPropertyVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyMuteChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMuteChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyBalanceChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBalanceChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyVolumeLimitChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeLimitChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStartupVolumeChanged(functor);
}

void CpProxyLinnCoUkPreamp4SetPropertyStartupVolumeEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStartupVolumeEnabledChanged(functor);
}

void CpProxyLinnCoUkPreamp4PropertyVolume(THandle aHandle, uint32_t* aVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolume(*aVolume);
}

void CpProxyLinnCoUkPreamp4PropertyMute(THandle aHandle, uint32_t* aMute)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aMute = false;
    proxyC->PropertyMute(*(TBool*)aMute);
}

void CpProxyLinnCoUkPreamp4PropertyBalance(THandle aHandle, int32_t* aBalance)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBalance(*aBalance);
}

void CpProxyLinnCoUkPreamp4PropertyVolumeLimit(THandle aHandle, uint32_t* aVolumeLimit)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolumeLimit(*aVolumeLimit);
}

void CpProxyLinnCoUkPreamp4PropertyStartupVolume(THandle aHandle, uint32_t* aStartupVolume)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyStartupVolume(*aStartupVolume);
}

void CpProxyLinnCoUkPreamp4PropertyStartupVolumeEnabled(THandle aHandle, uint32_t* aStartupVolumeEnabled)
{
    CpProxyLinnCoUkPreamp4C* proxyC = reinterpret_cast<CpProxyLinnCoUkPreamp4C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStartupVolumeEnabled = false;
    proxyC->PropertyStartupVolumeEnabled(*(TBool*)aStartupVolumeEnabled);
}

