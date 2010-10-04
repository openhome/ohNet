#include <Core/CpLinnCoUkPreamp4.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncVolumeIncLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncVolumeIncLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncVolumeIncLinnCoUkPreamp4::SyncVolumeIncLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncVolumeIncLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeInc(aAsync);
}


class SyncVolumeDecLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncVolumeDecLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncVolumeDecLinnCoUkPreamp4::SyncVolumeDecLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncVolumeDecLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeDec(aAsync);
}


class SyncSetVolumeLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncSetVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncSetVolumeLinnCoUkPreamp4::SyncSetVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncSetVolumeLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncVolumeLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TUint& aaVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
    TUint& iaVolume;
};

SyncVolumeLinnCoUkPreamp4::SyncVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TUint& aaVolume)
    : iService(aService)
    , iaVolume(aaVolume)
{
}

void SyncVolumeLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolume(aAsync, iaVolume);
}


class SyncSetMuteLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncSetMuteLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncSetMuteLinnCoUkPreamp4::SyncSetMuteLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncSetMuteLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncMuteLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncMuteLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TBool& aaMute);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
    TBool& iaMute;
};

SyncMuteLinnCoUkPreamp4::SyncMuteLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TBool& aaMute)
    : iService(aService)
    , iaMute(aaMute)
{
}

void SyncMuteLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndMute(aAsync, iaMute);
}


class SyncSetBalanceLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncSetBalanceLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncSetBalanceLinnCoUkPreamp4::SyncSetBalanceLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncSetBalanceLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBalance(aAsync);
}


class SyncBalanceLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncBalanceLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TInt& aaBalance);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
    TInt& iaBalance;
};

SyncBalanceLinnCoUkPreamp4::SyncBalanceLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TInt& aaBalance)
    : iService(aService)
    , iaBalance(aaBalance)
{
}

void SyncBalanceLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalance(aAsync, iaBalance);
}


class SyncSetVolumeLimitLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncSetVolumeLimitLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncSetVolumeLimitLinnCoUkPreamp4::SyncSetVolumeLimitLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncSetVolumeLimitLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeLimit(aAsync);
}


class SyncVolumeLimitLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncVolumeLimitLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TUint& aaVolumeLimit);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
    TUint& iaVolumeLimit;
};

SyncVolumeLimitLinnCoUkPreamp4::SyncVolumeLimitLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TUint& aaVolumeLimit)
    : iService(aService)
    , iaVolumeLimit(aaVolumeLimit)
{
}

void SyncVolumeLimitLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeLimit(aAsync, iaVolumeLimit);
}


class SyncSetStartupVolumeLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncSetStartupVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncSetStartupVolumeLinnCoUkPreamp4::SyncSetStartupVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncSetStartupVolumeLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupVolume(aAsync);
}


class SyncStartupVolumeLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncStartupVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TUint& aaStartupVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
    TUint& iaStartupVolume;
};

SyncStartupVolumeLinnCoUkPreamp4::SyncStartupVolumeLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TUint& aaStartupVolume)
    : iService(aService)
    , iaStartupVolume(aaStartupVolume)
{
}

void SyncStartupVolumeLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupVolume(aAsync, iaStartupVolume);
}


class SyncSetStartupVolumeEnabledLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncSetStartupVolumeEnabledLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
};

SyncSetStartupVolumeEnabledLinnCoUkPreamp4::SyncSetStartupVolumeEnabledLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService)
    : iService(aService)
{
}

void SyncSetStartupVolumeEnabledLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupVolumeEnabled(aAsync);
}


class SyncStartupVolumeEnabledLinnCoUkPreamp4 : public SyncProxyAction
{
public:
    SyncStartupVolumeEnabledLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TBool& aaStartupVolumeEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4& iService;
    TBool& iaStartupVolumeEnabled;
};

SyncStartupVolumeEnabledLinnCoUkPreamp4::SyncStartupVolumeEnabledLinnCoUkPreamp4(CpProxyLinnCoUkPreamp4& aService, TBool& aaStartupVolumeEnabled)
    : iService(aService)
    , iaStartupVolumeEnabled(aaStartupVolumeEnabled)
{
}

void SyncStartupVolumeEnabledLinnCoUkPreamp4::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupVolumeEnabled(aAsync, iaStartupVolumeEnabled);
}


CpProxyLinnCoUkPreamp4::CpProxyLinnCoUkPreamp4(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Preamp", 4, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4::VolumePropertyChanged);
    iVolume = new PropertyUint("Volume", functor);
    iService->AddProperty(iVolume);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4::MutePropertyChanged);
    iMute = new PropertyBool("Mute", functor);
    iService->AddProperty(iMute);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4::BalancePropertyChanged);
    iBalance = new PropertyInt("Balance", functor);
    iService->AddProperty(iBalance);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4::VolumeLimitPropertyChanged);
    iVolumeLimit = new PropertyUint("VolumeLimit", functor);
    iService->AddProperty(iVolumeLimit);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4::StartupVolumePropertyChanged);
    iStartupVolume = new PropertyUint("StartupVolume", functor);
    iService->AddProperty(iStartupVolume);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4::StartupVolumeEnabledPropertyChanged);
    iStartupVolumeEnabled = new PropertyBool("StartupVolumeEnabled", functor);
    iService->AddProperty(iStartupVolumeEnabled);
}

CpProxyLinnCoUkPreamp4::~CpProxyLinnCoUkPreamp4()
{
    delete iService;
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

void CpProxyLinnCoUkPreamp4::SyncVolumeInc()
{
    SyncVolumeIncLinnCoUkPreamp4 sync(*this);
    BeginVolumeInc(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginVolumeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeInc, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndVolumeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeInc"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncVolumeDec()
{
    SyncVolumeDecLinnCoUkPreamp4 sync(*this);
    BeginVolumeDec(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginVolumeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeDec, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndVolumeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeDec"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncSetVolume(TUint aaVolume)
{
    SyncSetVolumeLinnCoUkPreamp4 sync(*this);
    BeginSetVolume(aaVolume, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginSetVolume(TUint aaVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaVolume));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncVolume(TUint& aaVolume)
{
    SyncVolumeLinnCoUkPreamp4 sync(*this, aaVolume);
    BeginVolume(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndVolume(IAsync& aAsync, TUint& aaVolume)
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

void CpProxyLinnCoUkPreamp4::SyncSetMute(TBool aaMute)
{
    SyncSetMuteLinnCoUkPreamp4 sync(*this);
    BeginSetMute(aaMute, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginSetMute(TBool aaMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaMute));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncMute(TBool& aaMute)
{
    SyncMuteLinnCoUkPreamp4 sync(*this, aaMute);
    BeginMute(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginMute(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMute, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndMute(IAsync& aAsync, TBool& aaMute)
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

void CpProxyLinnCoUkPreamp4::SyncSetBalance(TInt aaBalance)
{
    SyncSetBalanceLinnCoUkPreamp4 sync(*this);
    BeginSetBalance(aaBalance, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginSetBalance(TInt aaBalance, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBalance, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBalance->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaBalance));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndSetBalance(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBalance"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncBalance(TInt& aaBalance)
{
    SyncBalanceLinnCoUkPreamp4 sync(*this, aaBalance);
    BeginBalance(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginBalance(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBalance, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBalance->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndBalance(IAsync& aAsync, TInt& aaBalance)
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

void CpProxyLinnCoUkPreamp4::SyncSetVolumeLimit(TUint aaVolumeLimit)
{
    SyncSetVolumeLimitLinnCoUkPreamp4 sync(*this);
    BeginSetVolumeLimit(aaVolumeLimit, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginSetVolumeLimit(TUint aaVolumeLimit, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeLimit, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeLimit->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaVolumeLimit));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndSetVolumeLimit(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeLimit"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncVolumeLimit(TUint& aaVolumeLimit)
{
    SyncVolumeLimitLinnCoUkPreamp4 sync(*this, aaVolumeLimit);
    BeginVolumeLimit(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginVolumeLimit(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeLimit, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeLimit->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndVolumeLimit(IAsync& aAsync, TUint& aaVolumeLimit)
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

void CpProxyLinnCoUkPreamp4::SyncSetStartupVolume(TUint aaStartupVolume)
{
    SyncSetStartupVolumeLinnCoUkPreamp4 sync(*this);
    BeginSetStartupVolume(aaStartupVolume, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginSetStartupVolume(TUint aaStartupVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaStartupVolume));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndSetStartupVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncStartupVolume(TUint& aaStartupVolume)
{
    SyncStartupVolumeLinnCoUkPreamp4 sync(*this, aaStartupVolume);
    BeginStartupVolume(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginStartupVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndStartupVolume(IAsync& aAsync, TUint& aaStartupVolume)
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

void CpProxyLinnCoUkPreamp4::SyncSetStartupVolumeEnabled(TBool aaStartupVolumeEnabled)
{
    SyncSetStartupVolumeEnabledLinnCoUkPreamp4 sync(*this);
    BeginSetStartupVolumeEnabled(aaStartupVolumeEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginSetStartupVolumeEnabled(TBool aaStartupVolumeEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupVolumeEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupVolumeEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStartupVolumeEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndSetStartupVolumeEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupVolumeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4::SyncStartupVolumeEnabled(TBool& aaStartupVolumeEnabled)
{
    SyncStartupVolumeEnabledLinnCoUkPreamp4 sync(*this, aaStartupVolumeEnabled);
    BeginStartupVolumeEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4::BeginStartupVolumeEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupVolumeEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupVolumeEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4::EndStartupVolumeEnabled(IAsync& aAsync, TBool& aaStartupVolumeEnabled)
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

void CpProxyLinnCoUkPreamp4::SetPropertyVolumeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4::SetPropertyMuteChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMuteChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4::SetPropertyBalanceChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBalanceChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4::SetPropertyVolumeLimitChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeLimitChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4::SetPropertyStartupVolumeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupVolumeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4::SetPropertyStartupVolumeEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupVolumeEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4::PropertyVolume(TUint& aVolume) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolume = iVolume->Value();
}

void CpProxyLinnCoUkPreamp4::PropertyMute(TBool& aMute) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMute = iMute->Value();
}

void CpProxyLinnCoUkPreamp4::PropertyBalance(TInt& aBalance) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBalance = iBalance->Value();
}

void CpProxyLinnCoUkPreamp4::PropertyVolumeLimit(TUint& aVolumeLimit) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeLimit = iVolumeLimit->Value();
}

void CpProxyLinnCoUkPreamp4::PropertyStartupVolume(TUint& aStartupVolume) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupVolume = iStartupVolume->Value();
}

void CpProxyLinnCoUkPreamp4::PropertyStartupVolumeEnabled(TBool& aStartupVolumeEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupVolumeEnabled = iStartupVolumeEnabled->Value();
}

void CpProxyLinnCoUkPreamp4::VolumePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVolumeChanged != NULL) {
        iVolumeChanged();
    }
}

void CpProxyLinnCoUkPreamp4::MutePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iMuteChanged != NULL) {
        iMuteChanged();
    }
}

void CpProxyLinnCoUkPreamp4::BalancePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iBalanceChanged != NULL) {
        iBalanceChanged();
    }
}

void CpProxyLinnCoUkPreamp4::VolumeLimitPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVolumeLimitChanged != NULL) {
        iVolumeLimitChanged();
    }
}

void CpProxyLinnCoUkPreamp4::StartupVolumePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupVolumeChanged != NULL) {
        iStartupVolumeChanged();
    }
}

void CpProxyLinnCoUkPreamp4::StartupVolumeEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupVolumeEnabledChanged != NULL) {
        iStartupVolumeEnabledChanged();
    }
}

