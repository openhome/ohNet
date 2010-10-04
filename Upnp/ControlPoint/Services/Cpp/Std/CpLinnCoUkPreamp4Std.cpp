#include <Std/CpLinnCoUkPreamp4.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncVolumeIncLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncVolumeIncLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncVolumeIncLinnCoUkPreamp4Cpp::SyncVolumeIncLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncVolumeIncLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeInc(aAsync);
}


class SyncVolumeDecLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncVolumeDecLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncVolumeDecLinnCoUkPreamp4Cpp::SyncVolumeDecLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncVolumeDecLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeDec(aAsync);
}


class SyncSetVolumeLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncSetVolumeLinnCoUkPreamp4Cpp::SyncSetVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncSetVolumeLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncVolumeLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, uint32_t& aaVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
    uint32_t& iaVolume;
};

SyncVolumeLinnCoUkPreamp4Cpp::SyncVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, uint32_t& aaVolume)
    : iService(aService)
    , iaVolume(aaVolume)
{
}

void SyncVolumeLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolume(aAsync, iaVolume);
}


class SyncSetMuteLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncSetMuteLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncSetMuteLinnCoUkPreamp4Cpp::SyncSetMuteLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncSetMuteLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncMuteLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncMuteLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, bool& aaMute);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
    bool& iaMute;
};

SyncMuteLinnCoUkPreamp4Cpp::SyncMuteLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, bool& aaMute)
    : iService(aService)
    , iaMute(aaMute)
{
}

void SyncMuteLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMute(aAsync, iaMute);
}


class SyncSetBalanceLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncSetBalanceLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncSetBalanceLinnCoUkPreamp4Cpp::SyncSetBalanceLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncSetBalanceLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBalance(aAsync);
}


class SyncBalanceLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncBalanceLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, int32_t& aaBalance);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
    int32_t& iaBalance;
};

SyncBalanceLinnCoUkPreamp4Cpp::SyncBalanceLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, int32_t& aaBalance)
    : iService(aService)
    , iaBalance(aaBalance)
{
}

void SyncBalanceLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalance(aAsync, iaBalance);
}


class SyncSetVolumeLimitLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncSetVolumeLimitLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncSetVolumeLimitLinnCoUkPreamp4Cpp::SyncSetVolumeLimitLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncSetVolumeLimitLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolumeLimit(aAsync);
}


class SyncVolumeLimitLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncVolumeLimitLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, uint32_t& aaVolumeLimit);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
    uint32_t& iaVolumeLimit;
};

SyncVolumeLimitLinnCoUkPreamp4Cpp::SyncVolumeLimitLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, uint32_t& aaVolumeLimit)
    : iService(aService)
    , iaVolumeLimit(aaVolumeLimit)
{
}

void SyncVolumeLimitLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeLimit(aAsync, iaVolumeLimit);
}


class SyncSetStartupVolumeLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncSetStartupVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncSetStartupVolumeLinnCoUkPreamp4Cpp::SyncSetStartupVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncSetStartupVolumeLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupVolume(aAsync);
}


class SyncStartupVolumeLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncStartupVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, uint32_t& aaStartupVolume);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
    uint32_t& iaStartupVolume;
};

SyncStartupVolumeLinnCoUkPreamp4Cpp::SyncStartupVolumeLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, uint32_t& aaStartupVolume)
    : iService(aService)
    , iaStartupVolume(aaStartupVolume)
{
}

void SyncStartupVolumeLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupVolume(aAsync, iaStartupVolume);
}


class SyncSetStartupVolumeEnabledLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncSetStartupVolumeEnabledLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
};

SyncSetStartupVolumeEnabledLinnCoUkPreamp4Cpp::SyncSetStartupVolumeEnabledLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService)
    : iService(aService)
{
}

void SyncSetStartupVolumeEnabledLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupVolumeEnabled(aAsync);
}


class SyncStartupVolumeEnabledLinnCoUkPreamp4Cpp : public SyncProxyAction
{
public:
    SyncStartupVolumeEnabledLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, bool& aaStartupVolumeEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkPreamp4Cpp& iService;
    bool& iaStartupVolumeEnabled;
};

SyncStartupVolumeEnabledLinnCoUkPreamp4Cpp::SyncStartupVolumeEnabledLinnCoUkPreamp4Cpp(CpProxyLinnCoUkPreamp4Cpp& aService, bool& aaStartupVolumeEnabled)
    : iService(aService)
    , iaStartupVolumeEnabled(aaStartupVolumeEnabled)
{
}

void SyncStartupVolumeEnabledLinnCoUkPreamp4Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupVolumeEnabled(aAsync, iaStartupVolumeEnabled);
}


CpProxyLinnCoUkPreamp4Cpp::CpProxyLinnCoUkPreamp4Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4Cpp::VolumePropertyChanged);
    iVolume = new PropertyUint("Volume", functor);
    iService->AddProperty(iVolume);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4Cpp::MutePropertyChanged);
    iMute = new PropertyBool("Mute", functor);
    iService->AddProperty(iMute);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4Cpp::BalancePropertyChanged);
    iBalance = new PropertyInt("Balance", functor);
    iService->AddProperty(iBalance);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4Cpp::VolumeLimitPropertyChanged);
    iVolumeLimit = new PropertyUint("VolumeLimit", functor);
    iService->AddProperty(iVolumeLimit);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4Cpp::StartupVolumePropertyChanged);
    iStartupVolume = new PropertyUint("StartupVolume", functor);
    iService->AddProperty(iStartupVolume);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkPreamp4Cpp::StartupVolumeEnabledPropertyChanged);
    iStartupVolumeEnabled = new PropertyBool("StartupVolumeEnabled", functor);
    iService->AddProperty(iStartupVolumeEnabled);
}

CpProxyLinnCoUkPreamp4Cpp::~CpProxyLinnCoUkPreamp4Cpp()
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

void CpProxyLinnCoUkPreamp4Cpp::SyncVolumeInc()
{
    SyncVolumeIncLinnCoUkPreamp4Cpp sync(*this);
    BeginVolumeInc(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginVolumeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeInc, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndVolumeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeInc"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncVolumeDec()
{
    SyncVolumeDecLinnCoUkPreamp4Cpp sync(*this);
    BeginVolumeDec(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginVolumeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeDec, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndVolumeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeDec"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncSetVolume(uint32_t aaVolume)
{
    SyncSetVolumeLinnCoUkPreamp4Cpp sync(*this);
    BeginSetVolume(aaVolume, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginSetVolume(uint32_t aaVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaVolume));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncVolume(uint32_t& aaVolume)
{
    SyncVolumeLinnCoUkPreamp4Cpp sync(*this, aaVolume);
    BeginVolume(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndVolume(IAsync& aAsync, uint32_t& aaVolume)
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

void CpProxyLinnCoUkPreamp4Cpp::SyncSetMute(bool aaMute)
{
    SyncSetMuteLinnCoUkPreamp4Cpp sync(*this);
    BeginSetMute(aaMute, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginSetMute(bool aaMute, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaMute));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncMute(bool& aaMute)
{
    SyncMuteLinnCoUkPreamp4Cpp sync(*this, aaMute);
    BeginMute(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginMute(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMute, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndMute(IAsync& aAsync, bool& aaMute)
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

void CpProxyLinnCoUkPreamp4Cpp::SyncSetBalance(int32_t aaBalance)
{
    SyncSetBalanceLinnCoUkPreamp4Cpp sync(*this);
    BeginSetBalance(aaBalance, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginSetBalance(int32_t aaBalance, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBalance, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBalance->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaBalance));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndSetBalance(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBalance"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncBalance(int32_t& aaBalance)
{
    SyncBalanceLinnCoUkPreamp4Cpp sync(*this, aaBalance);
    BeginBalance(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginBalance(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBalance, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBalance->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndBalance(IAsync& aAsync, int32_t& aaBalance)
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

void CpProxyLinnCoUkPreamp4Cpp::SyncSetVolumeLimit(uint32_t aaVolumeLimit)
{
    SyncSetVolumeLimitLinnCoUkPreamp4Cpp sync(*this);
    BeginSetVolumeLimit(aaVolumeLimit, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginSetVolumeLimit(uint32_t aaVolumeLimit, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolumeLimit, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolumeLimit->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaVolumeLimit));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndSetVolumeLimit(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolumeLimit"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncVolumeLimit(uint32_t& aaVolumeLimit)
{
    SyncVolumeLimitLinnCoUkPreamp4Cpp sync(*this, aaVolumeLimit);
    BeginVolumeLimit(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginVolumeLimit(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeLimit, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeLimit->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndVolumeLimit(IAsync& aAsync, uint32_t& aaVolumeLimit)
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

void CpProxyLinnCoUkPreamp4Cpp::SyncSetStartupVolume(uint32_t aaStartupVolume)
{
    SyncSetStartupVolumeLinnCoUkPreamp4Cpp sync(*this);
    BeginSetStartupVolume(aaStartupVolume, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginSetStartupVolume(uint32_t aaStartupVolume, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaStartupVolume));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndSetStartupVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncStartupVolume(uint32_t& aaStartupVolume)
{
    SyncStartupVolumeLinnCoUkPreamp4Cpp sync(*this, aaStartupVolume);
    BeginStartupVolume(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginStartupVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndStartupVolume(IAsync& aAsync, uint32_t& aaStartupVolume)
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

void CpProxyLinnCoUkPreamp4Cpp::SyncSetStartupVolumeEnabled(bool aaStartupVolumeEnabled)
{
    SyncSetStartupVolumeEnabledLinnCoUkPreamp4Cpp sync(*this);
    BeginSetStartupVolumeEnabled(aaStartupVolumeEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginSetStartupVolumeEnabled(bool aaStartupVolumeEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupVolumeEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupVolumeEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStartupVolumeEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndSetStartupVolumeEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupVolumeEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkPreamp4Cpp::SyncStartupVolumeEnabled(bool& aaStartupVolumeEnabled)
{
    SyncStartupVolumeEnabledLinnCoUkPreamp4Cpp sync(*this, aaStartupVolumeEnabled);
    BeginStartupVolumeEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkPreamp4Cpp::BeginStartupVolumeEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupVolumeEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupVolumeEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkPreamp4Cpp::EndStartupVolumeEnabled(IAsync& aAsync, bool& aaStartupVolumeEnabled)
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

void CpProxyLinnCoUkPreamp4Cpp::SetPropertyVolumeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4Cpp::SetPropertyMuteChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMuteChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4Cpp::SetPropertyBalanceChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBalanceChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4Cpp::SetPropertyVolumeLimitChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeLimitChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4Cpp::SetPropertyStartupVolumeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupVolumeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4Cpp::SetPropertyStartupVolumeEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupVolumeEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkPreamp4Cpp::PropertyVolume(uint32_t& aVolume) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolume = iVolume->Value();
}

void CpProxyLinnCoUkPreamp4Cpp::PropertyMute(bool& aMute) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMute = iMute->Value();
}

void CpProxyLinnCoUkPreamp4Cpp::PropertyBalance(int32_t& aBalance) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBalance = iBalance->Value();
}

void CpProxyLinnCoUkPreamp4Cpp::PropertyVolumeLimit(uint32_t& aVolumeLimit) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeLimit = iVolumeLimit->Value();
}

void CpProxyLinnCoUkPreamp4Cpp::PropertyStartupVolume(uint32_t& aStartupVolume) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupVolume = iStartupVolume->Value();
}

void CpProxyLinnCoUkPreamp4Cpp::PropertyStartupVolumeEnabled(bool& aStartupVolumeEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupVolumeEnabled = iStartupVolumeEnabled->Value();
}

void CpProxyLinnCoUkPreamp4Cpp::VolumePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVolumeChanged != NULL) {
        iVolumeChanged();
    }
}

void CpProxyLinnCoUkPreamp4Cpp::MutePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iMuteChanged != NULL) {
        iMuteChanged();
    }
}

void CpProxyLinnCoUkPreamp4Cpp::BalancePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iBalanceChanged != NULL) {
        iBalanceChanged();
    }
}

void CpProxyLinnCoUkPreamp4Cpp::VolumeLimitPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iVolumeLimitChanged != NULL) {
        iVolumeLimitChanged();
    }
}

void CpProxyLinnCoUkPreamp4Cpp::StartupVolumePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupVolumeChanged != NULL) {
        iStartupVolumeChanged();
    }
}

void CpProxyLinnCoUkPreamp4Cpp::StartupVolumeEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupVolumeEnabledChanged != NULL) {
        iStartupVolumeEnabledChanged();
    }
}

