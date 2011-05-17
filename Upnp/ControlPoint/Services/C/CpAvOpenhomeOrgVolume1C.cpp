#include "CpAvOpenhomeOrgVolume1.h"
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

class CpProxyAvOpenhomeOrgVolume1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgVolume1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgVolume1C();
    //CpProxyAvOpenhomeOrgVolume1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgVolume1*>(iProxy); }

    void SyncCharacteristics(TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax);
    void BeginCharacteristics(FunctorAsync& aFunctor);
    void EndCharacteristics(IAsync& aAsync, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax);

    void SyncSetVolume(TUint aValue);
    void BeginSetVolume(TUint aValue, FunctorAsync& aFunctor);
    void EndSetVolume(IAsync& aAsync);

    void SyncVolumeInc();
    void BeginVolumeInc(FunctorAsync& aFunctor);
    void EndVolumeInc(IAsync& aAsync);

    void SyncVolumeDec();
    void BeginVolumeDec(FunctorAsync& aFunctor);
    void EndVolumeDec(IAsync& aAsync);

    void SyncVolume(TUint& aValue);
    void BeginVolume(FunctorAsync& aFunctor);
    void EndVolume(IAsync& aAsync, TUint& aValue);

    void SyncSetBalance(TInt aValue);
    void BeginSetBalance(TInt aValue, FunctorAsync& aFunctor);
    void EndSetBalance(IAsync& aAsync);

    void SyncBalanceInc();
    void BeginBalanceInc(FunctorAsync& aFunctor);
    void EndBalanceInc(IAsync& aAsync);

    void SyncBalanceDec();
    void BeginBalanceDec(FunctorAsync& aFunctor);
    void EndBalanceDec(IAsync& aAsync);

    void SyncBalance(TInt& aValue);
    void BeginBalance(FunctorAsync& aFunctor);
    void EndBalance(IAsync& aAsync, TInt& aValue);

    void SyncSetFade(TInt aValue);
    void BeginSetFade(TInt aValue, FunctorAsync& aFunctor);
    void EndSetFade(IAsync& aAsync);

    void SyncFadeInc();
    void BeginFadeInc(FunctorAsync& aFunctor);
    void EndFadeInc(IAsync& aAsync);

    void SyncFadeDec();
    void BeginFadeDec(FunctorAsync& aFunctor);
    void EndFadeDec(IAsync& aAsync);

    void SyncFade(TInt& aValue);
    void BeginFade(FunctorAsync& aFunctor);
    void EndFade(IAsync& aAsync, TInt& aValue);

    void SyncSetMute(TBool aValue);
    void BeginSetMute(TBool aValue, FunctorAsync& aFunctor);
    void EndSetMute(IAsync& aAsync);

    void SyncMute(TBool& aValue);
    void BeginMute(FunctorAsync& aFunctor);
    void EndMute(IAsync& aAsync, TBool& aValue);

    void SyncVolumeLimit(TUint& aValue);
    void BeginVolumeLimit(FunctorAsync& aFunctor);
    void EndVolumeLimit(IAsync& aAsync, TUint& aValue);

    void SetPropertyVolumeChanged(Functor& aFunctor);
    void SetPropertyMuteChanged(Functor& aFunctor);
    void SetPropertyBalanceChanged(Functor& aFunctor);
    void SetPropertyFadeChanged(Functor& aFunctor);
    void SetPropertyVolumeLimitChanged(Functor& aFunctor);
    void SetPropertyVolumeMaxChanged(Functor& aFunctor);
    void SetPropertyVolumeUnityChanged(Functor& aFunctor);
    void SetPropertyVolumeStepsChanged(Functor& aFunctor);
    void SetPropertyVolumeMilliDbPerStepChanged(Functor& aFunctor);
    void SetPropertyBalanceMaxChanged(Functor& aFunctor);
    void SetPropertyFadeMaxChanged(Functor& aFunctor);

    void PropertyVolume(TUint& aVolume) const;
    void PropertyMute(TBool& aMute) const;
    void PropertyBalance(TInt& aBalance) const;
    void PropertyFade(TInt& aFade) const;
    void PropertyVolumeLimit(TUint& aVolumeLimit) const;
    void PropertyVolumeMax(TUint& aVolumeMax) const;
    void PropertyVolumeUnity(TUint& aVolumeUnity) const;
    void PropertyVolumeSteps(TUint& aVolumeSteps) const;
    void PropertyVolumeMilliDbPerStep(TUint& aVolumeMilliDbPerStep) const;
    void PropertyBalanceMax(TUint& aBalanceMax) const;
    void PropertyFadeMax(TUint& aFadeMax) const;
private:
    void VolumePropertyChanged();
    void MutePropertyChanged();
    void BalancePropertyChanged();
    void FadePropertyChanged();
    void VolumeLimitPropertyChanged();
    void VolumeMaxPropertyChanged();
    void VolumeUnityPropertyChanged();
    void VolumeStepsPropertyChanged();
    void VolumeMilliDbPerStepPropertyChanged();
    void BalanceMaxPropertyChanged();
    void FadeMaxPropertyChanged();
private:
    Mutex iLock;
    Action* iActionCharacteristics;
    Action* iActionSetVolume;
    Action* iActionVolumeInc;
    Action* iActionVolumeDec;
    Action* iActionVolume;
    Action* iActionSetBalance;
    Action* iActionBalanceInc;
    Action* iActionBalanceDec;
    Action* iActionBalance;
    Action* iActionSetFade;
    Action* iActionFadeInc;
    Action* iActionFadeDec;
    Action* iActionFade;
    Action* iActionSetMute;
    Action* iActionMute;
    Action* iActionVolumeLimit;
    PropertyUint* iVolume;
    PropertyBool* iMute;
    PropertyInt* iBalance;
    PropertyInt* iFade;
    PropertyUint* iVolumeLimit;
    PropertyUint* iVolumeMax;
    PropertyUint* iVolumeUnity;
    PropertyUint* iVolumeSteps;
    PropertyUint* iVolumeMilliDbPerStep;
    PropertyUint* iBalanceMax;
    PropertyUint* iFadeMax;
    Functor iVolumeChanged;
    Functor iMuteChanged;
    Functor iBalanceChanged;
    Functor iFadeChanged;
    Functor iVolumeLimitChanged;
    Functor iVolumeMaxChanged;
    Functor iVolumeUnityChanged;
    Functor iVolumeStepsChanged;
    Functor iVolumeMilliDbPerStepChanged;
    Functor iBalanceMaxChanged;
    Functor iFadeMaxChanged;
};


class SyncCharacteristicsAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncCharacteristicsAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
    TUint& iVolumeMax;
    TUint& iVolumeUnity;
    TUint& iVolumeSteps;
    TUint& iVolumeMilliDbPerStep;
    TUint& iBalanceMax;
    TUint& iFadeMax;
};

SyncCharacteristicsAvOpenhomeOrgVolume1C::SyncCharacteristicsAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax)
    : iService(aProxy)
    , iVolumeMax(aVolumeMax)
    , iVolumeUnity(aVolumeUnity)
    , iVolumeSteps(aVolumeSteps)
    , iVolumeMilliDbPerStep(aVolumeMilliDbPerStep)
    , iBalanceMax(aBalanceMax)
    , iFadeMax(aFadeMax)
{
}

void SyncCharacteristicsAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCharacteristics(aAsync, iVolumeMax, iVolumeUnity, iVolumeSteps, iVolumeMilliDbPerStep, iBalanceMax, iFadeMax);
}


class SyncSetVolumeAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncSetVolumeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncSetVolumeAvOpenhomeOrgVolume1C::SyncSetVolumeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetVolumeAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetVolume(aAsync);
}


class SyncVolumeIncAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncVolumeIncAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncVolumeIncAvOpenhomeOrgVolume1C::SyncVolumeIncAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncVolumeIncAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeInc(aAsync);
}


class SyncVolumeDecAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncVolumeDecAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncVolumeDecAvOpenhomeOrgVolume1C::SyncVolumeDecAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncVolumeDecAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeDec(aAsync);
}


class SyncVolumeAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncVolumeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
    TUint& iValue;
};

SyncVolumeAvOpenhomeOrgVolume1C::SyncVolumeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncVolumeAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolume(aAsync, iValue);
}


class SyncSetBalanceAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncSetBalanceAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncSetBalanceAvOpenhomeOrgVolume1C::SyncSetBalanceAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetBalanceAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetBalance(aAsync);
}


class SyncBalanceIncAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncBalanceIncAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncBalanceIncAvOpenhomeOrgVolume1C::SyncBalanceIncAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncBalanceIncAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalanceInc(aAsync);
}


class SyncBalanceDecAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncBalanceDecAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncBalanceDecAvOpenhomeOrgVolume1C::SyncBalanceDecAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncBalanceDecAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalanceDec(aAsync);
}


class SyncBalanceAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncBalanceAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TInt& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
    TInt& iValue;
};

SyncBalanceAvOpenhomeOrgVolume1C::SyncBalanceAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TInt& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncBalanceAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndBalance(aAsync, iValue);
}


class SyncSetFadeAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncSetFadeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncSetFadeAvOpenhomeOrgVolume1C::SyncSetFadeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetFadeAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetFade(aAsync);
}


class SyncFadeIncAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncFadeIncAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncFadeIncAvOpenhomeOrgVolume1C::SyncFadeIncAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncFadeIncAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndFadeInc(aAsync);
}


class SyncFadeDecAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncFadeDecAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncFadeDecAvOpenhomeOrgVolume1C::SyncFadeDecAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncFadeDecAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndFadeDec(aAsync);
}


class SyncFadeAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncFadeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TInt& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
    TInt& iValue;
};

SyncFadeAvOpenhomeOrgVolume1C::SyncFadeAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TInt& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncFadeAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndFade(aAsync, iValue);
}


class SyncSetMuteAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncSetMuteAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
};

SyncSetMuteAvOpenhomeOrgVolume1C::SyncSetMuteAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetMuteAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetMute(aAsync);
}


class SyncMuteAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncMuteAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
    TBool& iValue;
};

SyncMuteAvOpenhomeOrgVolume1C::SyncMuteAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMuteAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMute(aAsync, iValue);
}


class SyncVolumeLimitAvOpenhomeOrgVolume1C : public SyncProxyAction
{
public:
    SyncVolumeLimitAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgVolume1C& iService;
    TUint& iValue;
};

SyncVolumeLimitAvOpenhomeOrgVolume1C::SyncVolumeLimitAvOpenhomeOrgVolume1C(CpProxyAvOpenhomeOrgVolume1C& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncVolumeLimitAvOpenhomeOrgVolume1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndVolumeLimit(aAsync, iValue);
}

CpProxyAvOpenhomeOrgVolume1C::CpProxyAvOpenhomeOrgVolume1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Volume", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    Zapp::Parameter* param;

    iActionCharacteristics = new Action("Characteristics");
    param = new Zapp::ParameterUint("VolumeMax");
    iActionCharacteristics->AddOutputParameter(param);
    param = new Zapp::ParameterUint("VolumeUnity");
    iActionCharacteristics->AddOutputParameter(param);
    param = new Zapp::ParameterUint("VolumeSteps");
    iActionCharacteristics->AddOutputParameter(param);
    param = new Zapp::ParameterUint("VolumeMilliDbPerStep");
    iActionCharacteristics->AddOutputParameter(param);
    param = new Zapp::ParameterUint("BalanceMax");
    iActionCharacteristics->AddOutputParameter(param);
    param = new Zapp::ParameterUint("FadeMax");
    iActionCharacteristics->AddOutputParameter(param);

    iActionSetVolume = new Action("SetVolume");
    param = new Zapp::ParameterUint("Value");
    iActionSetVolume->AddInputParameter(param);

    iActionVolumeInc = new Action("VolumeInc");

    iActionVolumeDec = new Action("VolumeDec");

    iActionVolume = new Action("Volume");
    param = new Zapp::ParameterUint("Value");
    iActionVolume->AddOutputParameter(param);

    iActionSetBalance = new Action("SetBalance");
    param = new Zapp::ParameterInt("Value");
    iActionSetBalance->AddInputParameter(param);

    iActionBalanceInc = new Action("BalanceInc");

    iActionBalanceDec = new Action("BalanceDec");

    iActionBalance = new Action("Balance");
    param = new Zapp::ParameterInt("Value");
    iActionBalance->AddOutputParameter(param);

    iActionSetFade = new Action("SetFade");
    param = new Zapp::ParameterInt("Value");
    iActionSetFade->AddInputParameter(param);

    iActionFadeInc = new Action("FadeInc");

    iActionFadeDec = new Action("FadeDec");

    iActionFade = new Action("Fade");
    param = new Zapp::ParameterInt("Value");
    iActionFade->AddOutputParameter(param);

    iActionSetMute = new Action("SetMute");
    param = new Zapp::ParameterBool("Value");
    iActionSetMute->AddInputParameter(param);

    iActionMute = new Action("Mute");
    param = new Zapp::ParameterBool("Value");
    iActionMute->AddOutputParameter(param);

    iActionVolumeLimit = new Action("VolumeLimit");
    param = new Zapp::ParameterUint("Value");
    iActionVolumeLimit->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::VolumePropertyChanged);
    iVolume = new PropertyUint("Volume", functor);
    AddProperty(iVolume);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::MutePropertyChanged);
    iMute = new PropertyBool("Mute", functor);
    AddProperty(iMute);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::BalancePropertyChanged);
    iBalance = new PropertyInt("Balance", functor);
    AddProperty(iBalance);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::FadePropertyChanged);
    iFade = new PropertyInt("Fade", functor);
    AddProperty(iFade);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::VolumeLimitPropertyChanged);
    iVolumeLimit = new PropertyUint("VolumeLimit", functor);
    AddProperty(iVolumeLimit);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::VolumeMaxPropertyChanged);
    iVolumeMax = new PropertyUint("VolumeMax", functor);
    AddProperty(iVolumeMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::VolumeUnityPropertyChanged);
    iVolumeUnity = new PropertyUint("VolumeUnity", functor);
    AddProperty(iVolumeUnity);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::VolumeStepsPropertyChanged);
    iVolumeSteps = new PropertyUint("VolumeSteps", functor);
    AddProperty(iVolumeSteps);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::VolumeMilliDbPerStepPropertyChanged);
    iVolumeMilliDbPerStep = new PropertyUint("VolumeMilliDbPerStep", functor);
    AddProperty(iVolumeMilliDbPerStep);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::BalanceMaxPropertyChanged);
    iBalanceMax = new PropertyUint("BalanceMax", functor);
    AddProperty(iBalanceMax);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgVolume1C::FadeMaxPropertyChanged);
    iFadeMax = new PropertyUint("FadeMax", functor);
    AddProperty(iFadeMax);
}

CpProxyAvOpenhomeOrgVolume1C::~CpProxyAvOpenhomeOrgVolume1C()
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

void CpProxyAvOpenhomeOrgVolume1C::SyncCharacteristics(TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax)
{
    SyncCharacteristicsAvOpenhomeOrgVolume1C sync(*this, aVolumeMax, aVolumeUnity, aVolumeSteps, aVolumeMilliDbPerStep, aBalanceMax, aFadeMax);
    BeginCharacteristics(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginCharacteristics(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCharacteristics, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCharacteristics->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndCharacteristics(IAsync& aAsync, TUint& aVolumeMax, TUint& aVolumeUnity, TUint& aVolumeSteps, TUint& aVolumeMilliDbPerStep, TUint& aBalanceMax, TUint& aFadeMax)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Characteristics"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aVolumeMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aVolumeUnity = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aVolumeSteps = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aVolumeMilliDbPerStep = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBalanceMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aFadeMax = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1C::SyncSetVolume(TUint aValue)
{
    SyncSetVolumeAvOpenhomeOrgVolume1C sync(*this);
    BeginSetVolume(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginSetVolume(TUint aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetVolume, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetVolume->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndSetVolume(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetVolume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncVolumeInc()
{
    SyncVolumeIncAvOpenhomeOrgVolume1C sync(*this);
    BeginVolumeInc(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginVolumeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeInc, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndVolumeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeInc"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncVolumeDec()
{
    SyncVolumeDecAvOpenhomeOrgVolume1C sync(*this);
    BeginVolumeDec(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginVolumeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeDec, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndVolumeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeDec"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncVolume(TUint& aValue)
{
    SyncVolumeAvOpenhomeOrgVolume1C sync(*this, aValue);
    BeginVolume(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginVolume(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolume, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolume->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndVolume(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Volume"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1C::SyncSetBalance(TInt aValue)
{
    SyncSetBalanceAvOpenhomeOrgVolume1C sync(*this);
    BeginSetBalance(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginSetBalance(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetBalance, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetBalance->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndSetBalance(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetBalance"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncBalanceInc()
{
    SyncBalanceIncAvOpenhomeOrgVolume1C sync(*this);
    BeginBalanceInc(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginBalanceInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBalanceInc, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndBalanceInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BalanceInc"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncBalanceDec()
{
    SyncBalanceDecAvOpenhomeOrgVolume1C sync(*this);
    BeginBalanceDec(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginBalanceDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBalanceDec, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndBalanceDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BalanceDec"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncBalance(TInt& aValue)
{
    SyncBalanceAvOpenhomeOrgVolume1C sync(*this, aValue);
    BeginBalance(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginBalance(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionBalance, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBalance->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndBalance(IAsync& aAsync, TInt& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Balance"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1C::SyncSetFade(TInt aValue)
{
    SyncSetFadeAvOpenhomeOrgVolume1C sync(*this);
    BeginSetFade(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginSetFade(TInt aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetFade, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetFade->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndSetFade(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetFade"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncFadeInc()
{
    SyncFadeIncAvOpenhomeOrgVolume1C sync(*this);
    BeginFadeInc(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginFadeInc(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionFadeInc, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndFadeInc(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("FadeInc"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncFadeDec()
{
    SyncFadeDecAvOpenhomeOrgVolume1C sync(*this);
    BeginFadeDec(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginFadeDec(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionFadeDec, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndFadeDec(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("FadeDec"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncFade(TInt& aValue)
{
    SyncFadeAvOpenhomeOrgVolume1C sync(*this, aValue);
    BeginFade(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginFade(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionFade, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionFade->OutputParameters();
    invocation->AddOutput(new ArgumentInt(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndFade(IAsync& aAsync, TInt& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Fade"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentInt*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1C::SyncSetMute(TBool aValue)
{
    SyncSetMuteAvOpenhomeOrgVolume1C sync(*this);
    BeginSetMute(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginSetMute(TBool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetMute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetMute->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndSetMute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetMute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgVolume1C::SyncMute(TBool& aValue)
{
    SyncMuteAvOpenhomeOrgVolume1C sync(*this, aValue);
    BeginMute(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginMute(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMute, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMute->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndMute(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Mute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1C::SyncVolumeLimit(TUint& aValue)
{
    SyncVolumeLimitAvOpenhomeOrgVolume1C sync(*this, aValue);
    BeginVolumeLimit(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgVolume1C::BeginVolumeLimit(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionVolumeLimit, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionVolumeLimit->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgVolume1C::EndVolumeLimit(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("VolumeLimit"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyVolumeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyMuteChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMuteChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyBalanceChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBalanceChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyFadeChanged(Functor& aFunctor)
{
    iLock.Wait();
    iFadeChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyVolumeLimitChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeLimitChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyVolumeMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyVolumeUnityChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeUnityChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyVolumeStepsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeStepsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyVolumeMilliDbPerStepChanged(Functor& aFunctor)
{
    iLock.Wait();
    iVolumeMilliDbPerStepChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyBalanceMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBalanceMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::SetPropertyFadeMaxChanged(Functor& aFunctor)
{
    iLock.Wait();
    iFadeMaxChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyVolume(TUint& aVolume) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVolume = iVolume->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyMute(TBool& aMute) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMute = iMute->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyBalance(TInt& aBalance) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aBalance = iBalance->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyFade(TInt& aFade) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aFade = iFade->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyVolumeLimit(TUint& aVolumeLimit) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVolumeLimit = iVolumeLimit->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyVolumeMax(TUint& aVolumeMax) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVolumeMax = iVolumeMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyVolumeUnity(TUint& aVolumeUnity) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVolumeUnity = iVolumeUnity->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyVolumeSteps(TUint& aVolumeSteps) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVolumeSteps = iVolumeSteps->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyVolumeMilliDbPerStep(TUint& aVolumeMilliDbPerStep) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aVolumeMilliDbPerStep = iVolumeMilliDbPerStep->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyBalanceMax(TUint& aBalanceMax) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aBalanceMax = iBalanceMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::PropertyFadeMax(TUint& aFadeMax) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aFadeMax = iFadeMax->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgVolume1C::VolumePropertyChanged()
{
    ReportEvent(iVolumeChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::MutePropertyChanged()
{
    ReportEvent(iMuteChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::BalancePropertyChanged()
{
    ReportEvent(iBalanceChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::FadePropertyChanged()
{
    ReportEvent(iFadeChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::VolumeLimitPropertyChanged()
{
    ReportEvent(iVolumeLimitChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::VolumeMaxPropertyChanged()
{
    ReportEvent(iVolumeMaxChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::VolumeUnityPropertyChanged()
{
    ReportEvent(iVolumeUnityChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::VolumeStepsPropertyChanged()
{
    ReportEvent(iVolumeStepsChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::VolumeMilliDbPerStepPropertyChanged()
{
    ReportEvent(iVolumeMilliDbPerStepChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::BalanceMaxPropertyChanged()
{
    ReportEvent(iBalanceMaxChanged);
}

void CpProxyAvOpenhomeOrgVolume1C::FadeMaxPropertyChanged()
{
    ReportEvent(iFadeMaxChanged);
}


THandle CpProxyAvOpenhomeOrgVolume1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgVolume1C(aDevice);
}

void CpProxyAvOpenhomeOrgVolume1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    delete proxyC;
}

void CpProxyAvOpenhomeOrgVolume1SyncCharacteristics(THandle aHandle, uint32_t* aVolumeMax, uint32_t* aVolumeUnity, uint32_t* aVolumeSteps, uint32_t* aVolumeMilliDbPerStep, uint32_t* aBalanceMax, uint32_t* aFadeMax)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncCharacteristics(*aVolumeMax, *aVolumeUnity, *aVolumeSteps, *aVolumeMilliDbPerStep, *aBalanceMax, *aFadeMax);
}

void CpProxyAvOpenhomeOrgVolume1BeginCharacteristics(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCharacteristics(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndCharacteristics(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aVolumeMax, uint32_t* aVolumeUnity, uint32_t* aVolumeSteps, uint32_t* aVolumeMilliDbPerStep, uint32_t* aBalanceMax, uint32_t* aFadeMax)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCharacteristics(*async, *aVolumeMax, *aVolumeUnity, *aVolumeSteps, *aVolumeMilliDbPerStep, *aBalanceMax, *aFadeMax);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncSetVolume(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetVolume(aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginSetVolume(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetVolume(aValue, functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndSetVolume(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
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

void CpProxyAvOpenhomeOrgVolume1SyncVolumeInc(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolumeInc();
}

void CpProxyAvOpenhomeOrgVolume1BeginVolumeInc(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeInc(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndVolumeInc(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
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

void CpProxyAvOpenhomeOrgVolume1SyncVolumeDec(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolumeDec();
}

void CpProxyAvOpenhomeOrgVolume1BeginVolumeDec(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeDec(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndVolumeDec(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
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

void CpProxyAvOpenhomeOrgVolume1SyncVolume(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolume(*aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginVolume(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolume(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndVolume(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndVolume(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncSetBalance(THandle aHandle, int32_t aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetBalance(aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginSetBalance(THandle aHandle, int32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetBalance(aValue, functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndSetBalance(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
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

void CpProxyAvOpenhomeOrgVolume1SyncBalanceInc(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncBalanceInc();
}

void CpProxyAvOpenhomeOrgVolume1BeginBalanceInc(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBalanceInc(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndBalanceInc(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndBalanceInc(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncBalanceDec(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncBalanceDec();
}

void CpProxyAvOpenhomeOrgVolume1BeginBalanceDec(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBalanceDec(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndBalanceDec(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndBalanceDec(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncBalance(THandle aHandle, int32_t* aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncBalance(*aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginBalance(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginBalance(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndBalance(THandle aHandle, ZappHandleAsync aAsync, int32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndBalance(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncSetFade(THandle aHandle, int32_t aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetFade(aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginSetFade(THandle aHandle, int32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetFade(aValue, functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndSetFade(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetFade(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncFadeInc(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncFadeInc();
}

void CpProxyAvOpenhomeOrgVolume1BeginFadeInc(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginFadeInc(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndFadeInc(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndFadeInc(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncFadeDec(THandle aHandle)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncFadeDec();
}

void CpProxyAvOpenhomeOrgVolume1BeginFadeDec(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginFadeDec(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndFadeDec(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndFadeDec(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncFade(THandle aHandle, int32_t* aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncFade(*aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginFade(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginFade(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndFade(THandle aHandle, ZappHandleAsync aAsync, int32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndFade(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncSetMute(THandle aHandle, uint32_t aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetMute((aValue==0? false : true));
}

void CpProxyAvOpenhomeOrgVolume1BeginSetMute(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetMute((aValue==0? false : true), functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndSetMute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
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

void CpProxyAvOpenhomeOrgVolume1SyncMute(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aValue = 0;
    proxyC->SyncMute(*(TBool*)aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginMute(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginMute(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndMute(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aValue = 0;
    try {
        proxyC->EndMute(*async, *(TBool*)aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SyncVolumeLimit(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncVolumeLimit(*aValue);
}

void CpProxyAvOpenhomeOrgVolume1BeginVolumeLimit(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginVolumeLimit(functor);
}

int32_t CpProxyAvOpenhomeOrgVolume1EndVolumeLimit(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndVolumeLimit(*async, *aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyMuteChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMuteChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyBalanceChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBalanceChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyFadeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyFadeChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeLimitChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeLimitChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeMaxChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeUnityChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeUnityChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeStepsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeStepsChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyVolumeMilliDbPerStepChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyVolumeMilliDbPerStepChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyBalanceMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBalanceMaxChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1SetPropertyFadeMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyFadeMaxChanged(functor);
}

void CpProxyAvOpenhomeOrgVolume1PropertyVolume(THandle aHandle, uint32_t* aVolume)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolume(*aVolume);
}

void CpProxyAvOpenhomeOrgVolume1PropertyMute(THandle aHandle, uint32_t* aMute)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aMute = false;
    proxyC->PropertyMute(*(TBool*)aMute);
}

void CpProxyAvOpenhomeOrgVolume1PropertyBalance(THandle aHandle, int32_t* aBalance)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBalance(*aBalance);
}

void CpProxyAvOpenhomeOrgVolume1PropertyFade(THandle aHandle, int32_t* aFade)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyFade(*aFade);
}

void CpProxyAvOpenhomeOrgVolume1PropertyVolumeLimit(THandle aHandle, uint32_t* aVolumeLimit)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolumeLimit(*aVolumeLimit);
}

void CpProxyAvOpenhomeOrgVolume1PropertyVolumeMax(THandle aHandle, uint32_t* aVolumeMax)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolumeMax(*aVolumeMax);
}

void CpProxyAvOpenhomeOrgVolume1PropertyVolumeUnity(THandle aHandle, uint32_t* aVolumeUnity)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolumeUnity(*aVolumeUnity);
}

void CpProxyAvOpenhomeOrgVolume1PropertyVolumeSteps(THandle aHandle, uint32_t* aVolumeSteps)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolumeSteps(*aVolumeSteps);
}

void CpProxyAvOpenhomeOrgVolume1PropertyVolumeMilliDbPerStep(THandle aHandle, uint32_t* aVolumeMilliDbPerStep)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyVolumeMilliDbPerStep(*aVolumeMilliDbPerStep);
}

void CpProxyAvOpenhomeOrgVolume1PropertyBalanceMax(THandle aHandle, uint32_t* aBalanceMax)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBalanceMax(*aBalanceMax);
}

void CpProxyAvOpenhomeOrgVolume1PropertyFadeMax(THandle aHandle, uint32_t* aFadeMax)
{
    CpProxyAvOpenhomeOrgVolume1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgVolume1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyFadeMax(*aFadeMax);
}

