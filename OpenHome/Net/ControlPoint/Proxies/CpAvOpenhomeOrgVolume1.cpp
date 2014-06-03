#include "CpAvOpenhomeOrgVolume1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncCharacteristicsAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncCharacteristicsAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCharacteristicsAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
    TUint& iVolumeMax;
    TUint& iVolumeUnity;
    TUint& iVolumeSteps;
    TUint& iVolumeMilliDbPerStep;
    TUint& iBalanceMax;
    TUint& iFadeMax;
};

SyncCharacteristicsAvOpenhomeOrgVolume1::SyncCharacteristicsAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax)
    : iService(aProxy)
    , iVolumeMax(aVolumeMax)
    , iVolumeUnity(aVolumeUnity)
    , iVolumeSteps(aVolumeSteps)
    , iVolumeMilliDbPerStep(aVolumeMilliDbPerStep)
    , iBalanceMax(aBalanceMax)
    , iFadeMax(aFadeMax)
{
}

void SyncCharacteristicsAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCharacteristics(aAsync, iVolumeMax, iVolumeUnity, iVolumeSteps, iVolumeMilliDbPerStep, iBalanceMax, iFadeMax);
}


class SyncSetVolumeAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncSetVolumeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetVolumeAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncSetVolumeAvOpenhomeOrgVolume1::SyncSetVolumeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncVolumeIncAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncVolumeIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncVolumeIncAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncVolumeIncAvOpenhomeOrgVolume1::SyncVolumeIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncVolumeIncAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeInc(aAsync);
}


class SyncVolumeDecAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncVolumeDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncVolumeDecAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncVolumeDecAvOpenhomeOrgVolume1::SyncVolumeDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncVolumeDecAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeDec(aAsync);
}


class SyncVolumeAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncVolumeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncVolumeAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
    TUint& iValue;
};

SyncVolumeAvOpenhomeOrgVolume1::SyncVolumeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncVolumeAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolume(aAsync, iValue);
}


class SyncSetBalanceAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncSetBalanceAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetBalanceAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncSetBalanceAvOpenhomeOrgVolume1::SyncSetBalanceAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncSetBalanceAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBalance(aAsync);
}


class SyncBalanceIncAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncBalanceIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBalanceIncAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncBalanceIncAvOpenhomeOrgVolume1::SyncBalanceIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncBalanceIncAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalanceInc(aAsync);
}


class SyncBalanceDecAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncBalanceDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBalanceDecAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncBalanceDecAvOpenhomeOrgVolume1::SyncBalanceDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncBalanceDecAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalanceDec(aAsync);
}


class SyncBalanceAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncBalanceAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TInt& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBalanceAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
    TInt& iValue;
};

SyncBalanceAvOpenhomeOrgVolume1::SyncBalanceAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TInt& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncBalanceAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalance(aAsync, iValue);
}


class SyncSetFadeAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncSetFadeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetFadeAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncSetFadeAvOpenhomeOrgVolume1::SyncSetFadeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncSetFadeAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetFade(aAsync);
}


class SyncFadeIncAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncFadeIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncFadeIncAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncFadeIncAvOpenhomeOrgVolume1::SyncFadeIncAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncFadeIncAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndFadeInc(aAsync);
}


class SyncFadeDecAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncFadeDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncFadeDecAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncFadeDecAvOpenhomeOrgVolume1::SyncFadeDecAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncFadeDecAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndFadeDec(aAsync);
}


class SyncFadeAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncFadeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TInt& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncFadeAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
    TInt& iValue;
};

SyncFadeAvOpenhomeOrgVolume1::SyncFadeAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TInt& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncFadeAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndFade(aAsync, iValue);
}


class SyncSetMuteAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncSetMuteAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetMuteAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
};

SyncSetMuteAvOpenhomeOrgVolume1::SyncSetMuteAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncMuteAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncMuteAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMuteAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
    TBool& iValue;
};

SyncMuteAvOpenhomeOrgVolume1::SyncMuteAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMuteAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndMute(aAsync, iValue);
}


class SyncVolumeLimitAvOpenhomeOrgVolume1 : public SyncProxyAction
{
public:
    SyncVolumeLimitAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncVolumeLimitAvOpenhomeOrgVolume1() {}
private:
    CpProxyAvOpenhomeOrgVolume1& iService;
    TUint& iValue;
};

SyncVolumeLimitAvOpenhomeOrgVolume1::SyncVolumeLimitAvOpenhomeOrgVolume1(CpProxyAvOpenhomeOrgVolume1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncVolumeLimitAvOpenhomeOrgVolume1::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeLimit(aAsync, iValue);
}


CpProxyAvOpenhomeOrgVolume1::CpProxyAvOpenhomeOrgVolume1(CpDevice& aDevice)
    : CpProxy("av-openhome-org", "Volume", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionCharacteristics = new Action("Characteristics");
    param = new OpenHome::Net::ParameterUint("VolumeMax");
    iActionCharacteristics->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("VolumeUnity");
    iActionCharacteristics->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("VolumeSteps");
    iActionCharacteristics->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("VolumeMilliDbPerStep");
    iActionCharacteristics->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("BalanceMax");
    iActionCharacteristics->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("FadeMax");
    iActionCharacteristics->AddOutputParameter(param);

    iActionSetVolume = new Action("SetVolume");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSetVolume->AddInputParameter(param);

    iActionVolumeInc = new Action("VolumeInc");

    iActionVolumeDec = new Action("VolumeDec");

    iActionVolume = new Action("Volume");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionVolume->AddOutputParameter(param);

    iActionSetBalance = new Action("SetBalance");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionSetBalance->AddInputParameter(param);

    iActionBalanceInc = new Action("BalanceInc");

    iActionBalanceDec = new Action("BalanceDec");

    iActionBalance = new Action("Balance");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionBalance->AddOutputParameter(param);

    iActionSetFade = new Action("SetFade");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionSetFade->AddInputParameter(param);

    iActionFadeInc = new Action("FadeInc");

    iActionFadeDec = new Action("FadeDec");

    iActionFade = new Action("Fade");
    param = new OpenHome::Net::ParameterInt("Value");
    iActionFade->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionSetMute->AddInputParameter(param);

    iActionMute = new Action("Mute");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionMute->AddOutputParameter(param);

    iActionVolumeLimit = new Action("VolumeLimit");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionVolumeLimit->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::VolumePropertyChanged);
    iVolume = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Volume", functor);
    AddProperty(iVolume);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::MutePropertyChanged);
    iMute = new PropertyBool(aDevice.Device().GetCpStack().Env(), "Mute", functor);
    AddProperty(iMute);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::BalancePropertyChanged);
    iBalance = new PropertyInt(aDevice.Device().GetCpStack().Env(), "Balance", functor);
    AddProperty(iBalance);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::FadePropertyChanged);
    iFade = new PropertyInt(aDevice.Device().GetCpStack().Env(), "Fade", functor);
    AddProperty(iFade);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::VolumeLimitPropertyChanged);
    iVolumeLimit = new PropertyUint(aDevice.Device().GetCpStack().Env(), "VolumeLimit", functor);
    AddProperty(iVolumeLimit);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::VolumeMaxPropertyChanged);
    iVolumeMax = new PropertyUint(aDevice.Device().GetCpStack().Env(), "VolumeMax", functor);
    AddProperty(iVolumeMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::VolumeUnityPropertyChanged);
    iVolumeUnity = new PropertyUint(aDevice.Device().GetCpStack().Env(), "VolumeUnity", functor);
    AddProperty(iVolumeUnity);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::VolumeStepsPropertyChanged);
    iVolumeSteps = new PropertyUint(aDevice.Device().GetCpStack().Env(), "VolumeSteps", functor);
    AddProperty(iVolumeSteps);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::VolumeMilliDbPerStepPropertyChanged);
    iVolumeMilliDbPerStep = new PropertyUint(aDevice.Device().GetCpStack().Env(), "VolumeMilliDbPerStep", functor);
    AddProperty(iVolumeMilliDbPerStep);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::BalanceMaxPropertyChanged);
    iBalanceMax = new PropertyUint(aDevice.Device().GetCpStack().Env(), "BalanceMax", functor);
    AddProperty(iBalanceMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1::FadeMaxPropertyChanged);
    iFadeMax = new PropertyUint(aDevice.Device().GetCpStack().Env(), "FadeMax", functor);
    AddProperty(iFadeMax);
}

CpProxyAvOpenhomeOrgVolume1::~CpProxyAvOpenhomeOrgVolume1()
{
    DestroyService();
    delete iActionCharacteristics;
    delete iActionSetVolume;
    delete iActionVolumeInc;
    delete iActionVolumeDec;
    delete iActionVolume;
    delete iActionSetBalance;
    delete iActionBalanceInc;
    delete iActionBalanceDec;
    delete iActionBalance;
    delete iActionSetFade;
    delete iActionFadeInc;
    delete iActionFadeDec;
    delete iActionFade;
    delete iActionSetMute;
    delete iActionMute;
    delete iActionVolumeLimit;
}

void CpProxyAvOpenhomeOrgVolume1::SyncCharacteristics(TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax)
{
    SyncCharacteristicsAvOpenhomeOrgVolume1 sync(*this, aVolumeMax, aVolumeUnity, aVolumeSteps, aVolumeMilliDbPerStep, aBalanceMax, aFadeMax);
    BeginCharacteristics(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginCharacteristics(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCharacteristics, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCharacteristics->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndCharacteristics(IAsync& aAsync, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Characteristics"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aVolumeMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aVolumeUnity = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aVolumeSteps = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aVolumeMilliDbPerStep = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBalanceMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aFadeMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1::SyncSetVolume(TUint aValue)
{
    SyncSetVolumeAvOpenhomeOrgVolume1 sync(*this);
    BeginSetVolume(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginSetVolume(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncVolumeInc()
{
    SyncVolumeIncAvOpenhomeOrgVolume1 sync(*this);
    BeginVolumeInc(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginVolumeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeInc, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndVolumeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeInc"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncVolumeDec()
{
    SyncVolumeDecAvOpenhomeOrgVolume1 sync(*this);
    BeginVolumeDec(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginVolumeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeDec, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndVolumeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeDec"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncVolume(TUint& aValue)
{
    SyncVolumeAvOpenhomeOrgVolume1 sync(*this, aValue);
    BeginVolume(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndVolume(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Volume"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1::SyncSetBalance(TInt aValue)
{
    SyncSetBalanceAvOpenhomeOrgVolume1 sync(*this);
    BeginSetBalance(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginSetBalance(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetBalance, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBalance->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndSetBalance(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBalance"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncBalanceInc()
{
    SyncBalanceIncAvOpenhomeOrgVolume1 sync(*this);
    BeginBalanceInc(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginBalanceInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBalanceInc, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndBalanceInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BalanceInc"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncBalanceDec()
{
    SyncBalanceDecAvOpenhomeOrgVolume1 sync(*this);
    BeginBalanceDec(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginBalanceDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBalanceDec, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndBalanceDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BalanceDec"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncBalance(TInt& aValue)
{
    SyncBalanceAvOpenhomeOrgVolume1 sync(*this, aValue);
    BeginBalance(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginBalance(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBalance, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBalance->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndBalance(IAsync& aAsync, TInt& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Balance"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1::SyncSetFade(TInt aValue)
{
    SyncSetFadeAvOpenhomeOrgVolume1 sync(*this);
    BeginSetFade(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginSetFade(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetFade, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetFade->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndSetFade(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetFade"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncFadeInc()
{
    SyncFadeIncAvOpenhomeOrgVolume1 sync(*this);
    BeginFadeInc(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginFadeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionFadeInc, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndFadeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("FadeInc"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncFadeDec()
{
    SyncFadeDecAvOpenhomeOrgVolume1 sync(*this);
    BeginFadeDec(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginFadeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionFadeDec, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndFadeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("FadeDec"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncFade(TInt& aValue)
{
    SyncFadeAvOpenhomeOrgVolume1 sync(*this, aValue);
    BeginFade(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginFade(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionFade, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionFade->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndFade(IAsync& aAsync, TInt& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Fade"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1::SyncSetMute(TBool aValue)
{
    SyncSetMuteAvOpenhomeOrgVolume1 sync(*this);
    BeginSetMute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginSetMute(TBool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyAvOpenhomeOrgVolume1::SyncMute(TBool& aValue)
{
    SyncMuteAvOpenhomeOrgVolume1 sync(*this, aValue);
    BeginMute(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginMute(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMute, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndMute(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Mute"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1::SyncVolumeLimit(TUint& aValue)
{
    SyncVolumeLimitAvOpenhomeOrgVolume1 sync(*this, aValue);
    BeginVolumeLimit(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1::BeginVolumeLimit(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionVolumeLimit, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeLimit->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1::EndVolumeLimit(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeLimit"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyVolumeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyMuteChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMuteChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyBalanceChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBalanceChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyFadeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iFadeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyVolumeLimitChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeLimitChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyVolumeMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyVolumeUnityChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeUnityChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyVolumeStepsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeStepsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyVolumeMilliDbPerStepChanged(Functor& aFunctor)
{
    iLock->Wait();
    iVolumeMilliDbPerStepChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyBalanceMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBalanceMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::SetPropertyFadeMaxChanged(Functor& aFunctor)
{
    iLock->Wait();
    iFadeMaxChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyVolume(TUint& aVolume) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolume = iVolume->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyMute(TBool& aMute) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMute = iMute->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyBalance(TInt& aBalance) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBalance = iBalance->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyFade(TInt& aFade) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aFade = iFade->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyVolumeLimit(TUint& aVolumeLimit) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeLimit = iVolumeLimit->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyVolumeMax(TUint& aVolumeMax) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeMax = iVolumeMax->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyVolumeUnity(TUint& aVolumeUnity) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeUnity = iVolumeUnity->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyVolumeSteps(TUint& aVolumeSteps) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeSteps = iVolumeSteps->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyVolumeMilliDbPerStep(TUint& aVolumeMilliDbPerStep) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aVolumeMilliDbPerStep = iVolumeMilliDbPerStep->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyBalanceMax(TUint& aBalanceMax) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBalanceMax = iBalanceMax->Value();
}

void CpProxyAvOpenhomeOrgVolume1::PropertyFadeMax(TUint& aFadeMax) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aFadeMax = iFadeMax->Value();
}

void CpProxyAvOpenhomeOrgVolume1::VolumePropertyChanged()
{
    ReportEvent(iVolumeChanged);
}

void CpProxyAvOpenhomeOrgVolume1::MutePropertyChanged()
{
    ReportEvent(iMuteChanged);
}

void CpProxyAvOpenhomeOrgVolume1::BalancePropertyChanged()
{
    ReportEvent(iBalanceChanged);
}

void CpProxyAvOpenhomeOrgVolume1::FadePropertyChanged()
{
    ReportEvent(iFadeChanged);
}

void CpProxyAvOpenhomeOrgVolume1::VolumeLimitPropertyChanged()
{
    ReportEvent(iVolumeLimitChanged);
}

void CpProxyAvOpenhomeOrgVolume1::VolumeMaxPropertyChanged()
{
    ReportEvent(iVolumeMaxChanged);
}

void CpProxyAvOpenhomeOrgVolume1::VolumeUnityPropertyChanged()
{
    ReportEvent(iVolumeUnityChanged);
}

void CpProxyAvOpenhomeOrgVolume1::VolumeStepsPropertyChanged()
{
    ReportEvent(iVolumeStepsChanged);
}

void CpProxyAvOpenhomeOrgVolume1::VolumeMilliDbPerStepPropertyChanged()
{
    ReportEvent(iVolumeMilliDbPerStepChanged);
}

void CpProxyAvOpenhomeOrgVolume1::BalanceMaxPropertyChanged()
{
    ReportEvent(iBalanceMaxChanged);
}

void CpProxyAvOpenhomeOrgVolume1::FadeMaxPropertyChanged()
{
    ReportEvent(iFadeMaxChanged);
}

