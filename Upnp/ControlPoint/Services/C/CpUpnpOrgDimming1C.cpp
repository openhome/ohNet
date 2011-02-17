#include "CpUpnpOrgDimming1.h"
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

class CpProxyUpnpOrgDimming1C : public CpProxyC
{
public:
    CpProxyUpnpOrgDimming1C(CpDeviceC aDevice);
    ~CpProxyUpnpOrgDimming1C();
    //CpProxyUpnpOrgDimming1* Proxy() { return static_cast<CpProxyUpnpOrgDimming1*>(iProxy); }

    void SyncSetLoadLevelTarget(TUint anewLoadlevelTarget);
    void BeginSetLoadLevelTarget(TUint anewLoadlevelTarget, FunctorAsync& aFunctor);
    void EndSetLoadLevelTarget(IAsync& aAsync);

    void SyncGetLoadLevelTarget(TUint& aGetLoadlevelTarget);
    void BeginGetLoadLevelTarget(FunctorAsync& aFunctor);
    void EndGetLoadLevelTarget(IAsync& aAsync, TUint& aGetLoadlevelTarget);

    void SyncGetLoadLevelStatus(TUint& aretLoadlevelStatus);
    void BeginGetLoadLevelStatus(FunctorAsync& aFunctor);
    void EndGetLoadLevelStatus(IAsync& aAsync, TUint& aretLoadlevelStatus);

    void SyncSetOnEffectLevel(TUint anewOnEffectLevel);
    void BeginSetOnEffectLevel(TUint anewOnEffectLevel, FunctorAsync& aFunctor);
    void EndSetOnEffectLevel(IAsync& aAsync);

    void SyncSetOnEffect(const Brx& anewOnEffect);
    void BeginSetOnEffect(const Brx& anewOnEffect, FunctorAsync& aFunctor);
    void EndSetOnEffect(IAsync& aAsync);

    void SyncGetOnEffectParameters(Brh& aretOnEffect, TUint& aretOnEffectLevel);
    void BeginGetOnEffectParameters(FunctorAsync& aFunctor);
    void EndGetOnEffectParameters(IAsync& aAsync, Brh& aretOnEffect, TUint& aretOnEffectLevel);

    void SyncStepUp();
    void BeginStepUp(FunctorAsync& aFunctor);
    void EndStepUp(IAsync& aAsync);

    void SyncStepDown();
    void BeginStepDown(FunctorAsync& aFunctor);
    void EndStepDown(IAsync& aAsync);

    void SyncStartRampUp();
    void BeginStartRampUp(FunctorAsync& aFunctor);
    void EndStartRampUp(IAsync& aAsync);

    void SyncStartRampDown();
    void BeginStartRampDown(FunctorAsync& aFunctor);
    void EndStartRampDown(IAsync& aAsync);

    void SyncStopRamp();
    void BeginStopRamp(FunctorAsync& aFunctor);
    void EndStopRamp(IAsync& aAsync);

    void SyncStartRampToLevel(TUint anewLoadLevelTarget, TUint anewRampTime);
    void BeginStartRampToLevel(TUint anewLoadLevelTarget, TUint anewRampTime, FunctorAsync& aFunctor);
    void EndStartRampToLevel(IAsync& aAsync);

    void SyncSetStepDelta(TUint anewStepDelta);
    void BeginSetStepDelta(TUint anewStepDelta, FunctorAsync& aFunctor);
    void EndSetStepDelta(IAsync& aAsync);

    void SyncGetStepDelta(TUint& aretStepDelta);
    void BeginGetStepDelta(FunctorAsync& aFunctor);
    void EndGetStepDelta(IAsync& aAsync, TUint& aretStepDelta);

    void SyncSetRampRate(TUint anewRampRate);
    void BeginSetRampRate(TUint anewRampRate, FunctorAsync& aFunctor);
    void EndSetRampRate(IAsync& aAsync);

    void SyncGetRampRate(TUint& aretRampRate);
    void BeginGetRampRate(FunctorAsync& aFunctor);
    void EndGetRampRate(IAsync& aAsync, TUint& aretRampRate);

    void SyncPauseRamp();
    void BeginPauseRamp(FunctorAsync& aFunctor);
    void EndPauseRamp(IAsync& aAsync);

    void SyncResumeRamp();
    void BeginResumeRamp(FunctorAsync& aFunctor);
    void EndResumeRamp(IAsync& aAsync);

    void SyncGetIsRamping(TBool& aretIsRamping);
    void BeginGetIsRamping(FunctorAsync& aFunctor);
    void EndGetIsRamping(IAsync& aAsync, TBool& aretIsRamping);

    void SyncGetRampPaused(TBool& aretRampPaused);
    void BeginGetRampPaused(FunctorAsync& aFunctor);
    void EndGetRampPaused(IAsync& aAsync, TBool& aretRampPaused);

    void SyncGetRampTime(TUint& aretRampTime);
    void BeginGetRampTime(FunctorAsync& aFunctor);
    void EndGetRampTime(IAsync& aAsync, TUint& aretRampTime);

    void SetPropertyLoadLevelStatusChanged(Functor& aFunctor);
    void SetPropertyStepDeltaChanged(Functor& aFunctor);
    void SetPropertyRampRateChanged(Functor& aFunctor);
    void SetPropertyIsRampingChanged(Functor& aFunctor);
    void SetPropertyRampPausedChanged(Functor& aFunctor);

    void PropertyLoadLevelStatus(TUint& aLoadLevelStatus) const;
    void PropertyStepDelta(TUint& aStepDelta) const;
    void PropertyRampRate(TUint& aRampRate) const;
    void PropertyIsRamping(TBool& aIsRamping) const;
    void PropertyRampPaused(TBool& aRampPaused) const;
private:
    void LoadLevelStatusPropertyChanged();
    void StepDeltaPropertyChanged();
    void RampRatePropertyChanged();
    void IsRampingPropertyChanged();
    void RampPausedPropertyChanged();
private:
    Mutex iLock;
    Action* iActionSetLoadLevelTarget;
    Action* iActionGetLoadLevelTarget;
    Action* iActionGetLoadLevelStatus;
    Action* iActionSetOnEffectLevel;
    Action* iActionSetOnEffect;
    Action* iActionGetOnEffectParameters;
    Action* iActionStepUp;
    Action* iActionStepDown;
    Action* iActionStartRampUp;
    Action* iActionStartRampDown;
    Action* iActionStopRamp;
    Action* iActionStartRampToLevel;
    Action* iActionSetStepDelta;
    Action* iActionGetStepDelta;
    Action* iActionSetRampRate;
    Action* iActionGetRampRate;
    Action* iActionPauseRamp;
    Action* iActionResumeRamp;
    Action* iActionGetIsRamping;
    Action* iActionGetRampPaused;
    Action* iActionGetRampTime;
    PropertyUint* iLoadLevelStatus;
    PropertyUint* iStepDelta;
    PropertyUint* iRampRate;
    PropertyBool* iIsRamping;
    PropertyBool* iRampPaused;
    Functor iLoadLevelStatusChanged;
    Functor iStepDeltaChanged;
    Functor iRampRateChanged;
    Functor iIsRampingChanged;
    Functor iRampPausedChanged;
};


class SyncSetLoadLevelTargetUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncSetLoadLevelTargetUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncSetLoadLevelTargetUpnpOrgDimming1C::SyncSetLoadLevelTargetUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoadLevelTargetUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoadLevelTarget(aAsync);
}


class SyncGetLoadLevelTargetUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetLoadLevelTargetUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aGetLoadlevelTarget);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TUint& iGetLoadlevelTarget;
};

SyncGetLoadLevelTargetUpnpOrgDimming1C::SyncGetLoadLevelTargetUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aGetLoadlevelTarget)
    : iService(aProxy)
    , iGetLoadlevelTarget(aGetLoadlevelTarget)
{
}

void SyncGetLoadLevelTargetUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoadLevelTarget(aAsync, iGetLoadlevelTarget);
}


class SyncGetLoadLevelStatusUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetLoadLevelStatusUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretLoadlevelStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TUint& iretLoadlevelStatus;
};

SyncGetLoadLevelStatusUpnpOrgDimming1C::SyncGetLoadLevelStatusUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretLoadlevelStatus)
    : iService(aProxy)
    , iretLoadlevelStatus(aretLoadlevelStatus)
{
}

void SyncGetLoadLevelStatusUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoadLevelStatus(aAsync, iretLoadlevelStatus);
}


class SyncSetOnEffectLevelUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncSetOnEffectLevelUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncSetOnEffectLevelUpnpOrgDimming1C::SyncSetOnEffectLevelUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetOnEffectLevelUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffectLevel(aAsync);
}


class SyncSetOnEffectUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncSetOnEffectUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncSetOnEffectUpnpOrgDimming1C::SyncSetOnEffectUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetOnEffectUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffect(aAsync);
}


class SyncGetOnEffectParametersUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetOnEffectParametersUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, Brh& aretOnEffect, TUint& aretOnEffectLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    Brh& iretOnEffect;
    TUint& iretOnEffectLevel;
};

SyncGetOnEffectParametersUpnpOrgDimming1C::SyncGetOnEffectParametersUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, Brh& aretOnEffect, TUint& aretOnEffectLevel)
    : iService(aProxy)
    , iretOnEffect(aretOnEffect)
    , iretOnEffectLevel(aretOnEffectLevel)
{
}

void SyncGetOnEffectParametersUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetOnEffectParameters(aAsync, iretOnEffect, iretOnEffectLevel);
}


class SyncStepUpUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncStepUpUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncStepUpUpnpOrgDimming1C::SyncStepUpUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncStepUpUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepUp(aAsync);
}


class SyncStepDownUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncStepDownUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncStepDownUpnpOrgDimming1C::SyncStepDownUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncStepDownUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepDown(aAsync);
}


class SyncStartRampUpUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncStartRampUpUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncStartRampUpUpnpOrgDimming1C::SyncStartRampUpUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncStartRampUpUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampUp(aAsync);
}


class SyncStartRampDownUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncStartRampDownUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncStartRampDownUpnpOrgDimming1C::SyncStartRampDownUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncStartRampDownUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampDown(aAsync);
}


class SyncStopRampUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncStopRampUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncStopRampUpnpOrgDimming1C::SyncStopRampUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopRampUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopRamp(aAsync);
}


class SyncStartRampToLevelUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncStartRampToLevelUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncStartRampToLevelUpnpOrgDimming1C::SyncStartRampToLevelUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncStartRampToLevelUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampToLevel(aAsync);
}


class SyncSetStepDeltaUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncSetStepDeltaUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncSetStepDeltaUpnpOrgDimming1C::SyncSetStepDeltaUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStepDeltaUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStepDelta(aAsync);
}


class SyncGetStepDeltaUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetStepDeltaUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretStepDelta);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TUint& iretStepDelta;
};

SyncGetStepDeltaUpnpOrgDimming1C::SyncGetStepDeltaUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretStepDelta)
    : iService(aProxy)
    , iretStepDelta(aretStepDelta)
{
}

void SyncGetStepDeltaUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStepDelta(aAsync, iretStepDelta);
}


class SyncSetRampRateUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncSetRampRateUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncSetRampRateUpnpOrgDimming1C::SyncSetRampRateUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRampRateUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRampRate(aAsync);
}


class SyncGetRampRateUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetRampRateUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretRampRate);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TUint& iretRampRate;
};

SyncGetRampRateUpnpOrgDimming1C::SyncGetRampRateUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretRampRate)
    : iService(aProxy)
    , iretRampRate(aretRampRate)
{
}

void SyncGetRampRateUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampRate(aAsync, iretRampRate);
}


class SyncPauseRampUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncPauseRampUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncPauseRampUpnpOrgDimming1C::SyncPauseRampUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseRampUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPauseRamp(aAsync);
}


class SyncResumeRampUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncResumeRampUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
};

SyncResumeRampUpnpOrgDimming1C::SyncResumeRampUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy)
    : iService(aProxy)
{
}

void SyncResumeRampUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndResumeRamp(aAsync);
}


class SyncGetIsRampingUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetIsRampingUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TBool& aretIsRamping);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TBool& iretIsRamping;
};

SyncGetIsRampingUpnpOrgDimming1C::SyncGetIsRampingUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TBool& aretIsRamping)
    : iService(aProxy)
    , iretIsRamping(aretIsRamping)
{
}

void SyncGetIsRampingUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetIsRamping(aAsync, iretIsRamping);
}


class SyncGetRampPausedUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetRampPausedUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TBool& aretRampPaused);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TBool& iretRampPaused;
};

SyncGetRampPausedUpnpOrgDimming1C::SyncGetRampPausedUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TBool& aretRampPaused)
    : iService(aProxy)
    , iretRampPaused(aretRampPaused)
{
}

void SyncGetRampPausedUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampPaused(aAsync, iretRampPaused);
}


class SyncGetRampTimeUpnpOrgDimming1C : public SyncProxyAction
{
public:
    SyncGetRampTimeUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretRampTime);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1C& iService;
    TUint& iretRampTime;
};

SyncGetRampTimeUpnpOrgDimming1C::SyncGetRampTimeUpnpOrgDimming1C(CpProxyUpnpOrgDimming1C& aProxy, TUint& aretRampTime)
    : iService(aProxy)
    , iretRampTime(aretRampTime)
{
}

void SyncGetRampTimeUpnpOrgDimming1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampTime(aAsync, iretRampTime);
}

CpProxyUpnpOrgDimming1C::CpProxyUpnpOrgDimming1C(CpDeviceC aDevice)
    : CpProxyC("schemas-upnp-org", "Dimming", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionSetLoadLevelTarget = new Action("SetLoadLevelTarget");
    param = new Zapp::ParameterUint("newLoadlevelTarget", 0, 100);
    iActionSetLoadLevelTarget->AddInputParameter(param);

    iActionGetLoadLevelTarget = new Action("GetLoadLevelTarget");
    param = new Zapp::ParameterUint("GetLoadlevelTarget", 0, 100);
    iActionGetLoadLevelTarget->AddOutputParameter(param);

    iActionGetLoadLevelStatus = new Action("GetLoadLevelStatus");
    param = new Zapp::ParameterUint("retLoadlevelStatus", 0, 100);
    iActionGetLoadLevelStatus->AddOutputParameter(param);

    iActionSetOnEffectLevel = new Action("SetOnEffectLevel");
    param = new Zapp::ParameterUint("newOnEffectLevel", 0, 100);
    iActionSetOnEffectLevel->AddInputParameter(param);

    iActionSetOnEffect = new Action("SetOnEffect");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    param = new Zapp::ParameterString("newOnEffect", allowedValues, 3);
    iActionSetOnEffect->AddInputParameter(param);
    delete[] allowedValues;

    iActionGetOnEffectParameters = new Action("GetOnEffectParameters");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    param = new Zapp::ParameterString("retOnEffect", allowedValues, 3);
    iActionGetOnEffectParameters->AddOutputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterUint("retOnEffectLevel", 0, 100);
    iActionGetOnEffectParameters->AddOutputParameter(param);

    iActionStepUp = new Action("StepUp");

    iActionStepDown = new Action("StepDown");

    iActionStartRampUp = new Action("StartRampUp");

    iActionStartRampDown = new Action("StartRampDown");

    iActionStopRamp = new Action("StopRamp");

    iActionStartRampToLevel = new Action("StartRampToLevel");
    param = new Zapp::ParameterUint("newLoadLevelTarget", 0, 100);
    iActionStartRampToLevel->AddInputParameter(param);
    param = new Zapp::ParameterUint("newRampTime");
    iActionStartRampToLevel->AddInputParameter(param);

    iActionSetStepDelta = new Action("SetStepDelta");
    param = new Zapp::ParameterUint("newStepDelta", 1, 100);
    iActionSetStepDelta->AddInputParameter(param);

    iActionGetStepDelta = new Action("GetStepDelta");
    param = new Zapp::ParameterUint("retStepDelta", 1, 100);
    iActionGetStepDelta->AddOutputParameter(param);

    iActionSetRampRate = new Action("SetRampRate");
    param = new Zapp::ParameterUint("newRampRate", 0, 100);
    iActionSetRampRate->AddInputParameter(param);

    iActionGetRampRate = new Action("GetRampRate");
    param = new Zapp::ParameterUint("retRampRate", 0, 100);
    iActionGetRampRate->AddOutputParameter(param);

    iActionPauseRamp = new Action("PauseRamp");

    iActionResumeRamp = new Action("ResumeRamp");

    iActionGetIsRamping = new Action("GetIsRamping");
    param = new Zapp::ParameterBool("retIsRamping");
    iActionGetIsRamping->AddOutputParameter(param);

    iActionGetRampPaused = new Action("GetRampPaused");
    param = new Zapp::ParameterBool("retRampPaused");
    iActionGetRampPaused->AddOutputParameter(param);

    iActionGetRampTime = new Action("GetRampTime");
    param = new Zapp::ParameterUint("retRampTime");
    iActionGetRampTime->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::LoadLevelStatusPropertyChanged);
    iLoadLevelStatus = new PropertyUint("LoadLevelStatus", functor);
    AddProperty(iLoadLevelStatus);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::StepDeltaPropertyChanged);
    iStepDelta = new PropertyUint("StepDelta", functor);
    AddProperty(iStepDelta);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::RampRatePropertyChanged);
    iRampRate = new PropertyUint("RampRate", functor);
    AddProperty(iRampRate);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::IsRampingPropertyChanged);
    iIsRamping = new PropertyBool("IsRamping", functor);
    AddProperty(iIsRamping);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::RampPausedPropertyChanged);
    iRampPaused = new PropertyBool("RampPaused", functor);
    AddProperty(iRampPaused);
}

CpProxyUpnpOrgDimming1C::~CpProxyUpnpOrgDimming1C()
{
    DestroyService();
    delete iActionSetLoadLevelTarget;
    delete iActionGetLoadLevelTarget;
    delete iActionGetLoadLevelStatus;
    delete iActionSetOnEffectLevel;
    delete iActionSetOnEffect;
    delete iActionGetOnEffectParameters;
    delete iActionStepUp;
    delete iActionStepDown;
    delete iActionStartRampUp;
    delete iActionStartRampDown;
    delete iActionStopRamp;
    delete iActionStartRampToLevel;
    delete iActionSetStepDelta;
    delete iActionGetStepDelta;
    delete iActionSetRampRate;
    delete iActionGetRampRate;
    delete iActionPauseRamp;
    delete iActionResumeRamp;
    delete iActionGetIsRamping;
    delete iActionGetRampPaused;
    delete iActionGetRampTime;
}

void CpProxyUpnpOrgDimming1C::SyncSetLoadLevelTarget(TUint anewLoadlevelTarget)
{
    SyncSetLoadLevelTargetUpnpOrgDimming1C sync(*this);
    BeginSetLoadLevelTarget(anewLoadlevelTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginSetLoadLevelTarget(TUint anewLoadlevelTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetLoadLevelTarget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoadLevelTarget->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewLoadlevelTarget));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndSetLoadLevelTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLoadLevelTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncGetLoadLevelTarget(TUint& aGetLoadlevelTarget)
{
    SyncGetLoadLevelTargetUpnpOrgDimming1C sync(*this, aGetLoadlevelTarget);
    BeginGetLoadLevelTarget(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetLoadLevelTarget(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetLoadLevelTarget, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoadLevelTarget->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetLoadLevelTarget(IAsync& aAsync, TUint& aGetLoadlevelTarget)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetLoadLevelTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aGetLoadlevelTarget = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncGetLoadLevelStatus(TUint& aretLoadlevelStatus)
{
    SyncGetLoadLevelStatusUpnpOrgDimming1C sync(*this, aretLoadlevelStatus);
    BeginGetLoadLevelStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetLoadLevelStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetLoadLevelStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoadLevelStatus->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetLoadLevelStatus(IAsync& aAsync, TUint& aretLoadlevelStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetLoadLevelStatus"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aretLoadlevelStatus = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncSetOnEffectLevel(TUint anewOnEffectLevel)
{
    SyncSetOnEffectLevelUpnpOrgDimming1C sync(*this);
    BeginSetOnEffectLevel(anewOnEffectLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginSetOnEffectLevel(TUint anewOnEffectLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetOnEffectLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetOnEffectLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewOnEffectLevel));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndSetOnEffectLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetOnEffectLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncSetOnEffect(const Brx& anewOnEffect)
{
    SyncSetOnEffectUpnpOrgDimming1C sync(*this);
    BeginSetOnEffect(anewOnEffect, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginSetOnEffect(const Brx& anewOnEffect, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetOnEffect, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetOnEffect->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], anewOnEffect));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndSetOnEffect(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetOnEffect"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncGetOnEffectParameters(Brh& aretOnEffect, TUint& aretOnEffectLevel)
{
    SyncGetOnEffectParametersUpnpOrgDimming1C sync(*this, aretOnEffect, aretOnEffectLevel);
    BeginGetOnEffectParameters(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetOnEffectParameters(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetOnEffectParameters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetOnEffectParameters->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetOnEffectParameters(IAsync& aAsync, Brh& aretOnEffect, TUint& aretOnEffectLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetOnEffectParameters"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aretOnEffect);
    aretOnEffectLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncStepUp()
{
    SyncStepUpUpnpOrgDimming1C sync(*this);
    BeginStepUp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginStepUp(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStepUp, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndStepUp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StepUp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncStepDown()
{
    SyncStepDownUpnpOrgDimming1C sync(*this);
    BeginStepDown(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginStepDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStepDown, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndStepDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StepDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncStartRampUp()
{
    SyncStartRampUpUpnpOrgDimming1C sync(*this);
    BeginStartRampUp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginStartRampUp(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartRampUp, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndStartRampUp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampUp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncStartRampDown()
{
    SyncStartRampDownUpnpOrgDimming1C sync(*this);
    BeginStartRampDown(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginStartRampDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartRampDown, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndStartRampDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncStopRamp()
{
    SyncStopRampUpnpOrgDimming1C sync(*this);
    BeginStopRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginStopRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStopRamp, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndStopRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StopRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncStartRampToLevel(TUint anewLoadLevelTarget, TUint anewRampTime)
{
    SyncStartRampToLevelUpnpOrgDimming1C sync(*this);
    BeginStartRampToLevel(anewLoadLevelTarget, anewRampTime, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginStartRampToLevel(TUint anewLoadLevelTarget, TUint anewRampTime, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStartRampToLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStartRampToLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewLoadLevelTarget));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewRampTime));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndStartRampToLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampToLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncSetStepDelta(TUint anewStepDelta)
{
    SyncSetStepDeltaUpnpOrgDimming1C sync(*this);
    BeginSetStepDelta(anewStepDelta, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginSetStepDelta(TUint anewStepDelta, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStepDelta, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStepDelta->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewStepDelta));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndSetStepDelta(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStepDelta"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncGetStepDelta(TUint& aretStepDelta)
{
    SyncGetStepDeltaUpnpOrgDimming1C sync(*this, aretStepDelta);
    BeginGetStepDelta(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetStepDelta(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetStepDelta, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStepDelta->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetStepDelta(IAsync& aAsync, TUint& aretStepDelta)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetStepDelta"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aretStepDelta = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncSetRampRate(TUint anewRampRate)
{
    SyncSetRampRateUpnpOrgDimming1C sync(*this);
    BeginSetRampRate(anewRampRate, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginSetRampRate(TUint anewRampRate, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRampRate, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRampRate->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewRampRate));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndSetRampRate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRampRate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncGetRampRate(TUint& aretRampRate)
{
    SyncGetRampRateUpnpOrgDimming1C sync(*this, aretRampRate);
    BeginGetRampRate(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetRampRate(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRampRate, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampRate->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetRampRate(IAsync& aAsync, TUint& aretRampRate)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRampRate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aretRampRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncPauseRamp()
{
    SyncPauseRampUpnpOrgDimming1C sync(*this);
    BeginPauseRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginPauseRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPauseRamp, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndPauseRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PauseRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncResumeRamp()
{
    SyncResumeRampUpnpOrgDimming1C sync(*this);
    BeginResumeRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginResumeRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionResumeRamp, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndResumeRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResumeRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1C::SyncGetIsRamping(TBool& aretIsRamping)
{
    SyncGetIsRampingUpnpOrgDimming1C sync(*this, aretIsRamping);
    BeginGetIsRamping(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetIsRamping(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetIsRamping, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetIsRamping->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetIsRamping(IAsync& aAsync, TBool& aretIsRamping)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetIsRamping"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aretIsRamping = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncGetRampPaused(TBool& aretRampPaused)
{
    SyncGetRampPausedUpnpOrgDimming1C sync(*this, aretRampPaused);
    BeginGetRampPaused(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetRampPaused(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRampPaused, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampPaused->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetRampPaused(IAsync& aAsync, TBool& aretRampPaused)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRampPaused"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aretRampPaused = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SyncGetRampTime(TUint& aretRampTime)
{
    SyncGetRampTimeUpnpOrgDimming1C sync(*this, aretRampTime);
    BeginGetRampTime(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1C::BeginGetRampTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRampTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1C::EndGetRampTime(IAsync& aAsync, TUint& aretRampTime)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRampTime"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aretRampTime = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1C::SetPropertyLoadLevelStatusChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLoadLevelStatusChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgDimming1C::SetPropertyStepDeltaChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStepDeltaChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgDimming1C::SetPropertyRampRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iRampRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgDimming1C::SetPropertyIsRampingChanged(Functor& aFunctor)
{
    iLock.Wait();
    iIsRampingChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgDimming1C::SetPropertyRampPausedChanged(Functor& aFunctor)
{
    iLock.Wait();
    iRampPausedChanged = aFunctor;
    iLock.Signal();
}

void CpProxyUpnpOrgDimming1C::PropertyLoadLevelStatus(TUint& aLoadLevelStatus) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aLoadLevelStatus = iLoadLevelStatus->Value();
    PropertyReadUnlock();
}

void CpProxyUpnpOrgDimming1C::PropertyStepDelta(TUint& aStepDelta) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aStepDelta = iStepDelta->Value();
    PropertyReadUnlock();
}

void CpProxyUpnpOrgDimming1C::PropertyRampRate(TUint& aRampRate) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aRampRate = iRampRate->Value();
    PropertyReadUnlock();
}

void CpProxyUpnpOrgDimming1C::PropertyIsRamping(TBool& aIsRamping) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aIsRamping = iIsRamping->Value();
    PropertyReadUnlock();
}

void CpProxyUpnpOrgDimming1C::PropertyRampPaused(TBool& aRampPaused) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aRampPaused = iRampPaused->Value();
    PropertyReadUnlock();
}

void CpProxyUpnpOrgDimming1C::LoadLevelStatusPropertyChanged()
{
    ReportEvent(iLoadLevelStatusChanged);
}

void CpProxyUpnpOrgDimming1C::StepDeltaPropertyChanged()
{
    ReportEvent(iStepDeltaChanged);
}

void CpProxyUpnpOrgDimming1C::RampRatePropertyChanged()
{
    ReportEvent(iRampRateChanged);
}

void CpProxyUpnpOrgDimming1C::IsRampingPropertyChanged()
{
    ReportEvent(iIsRampingChanged);
}

void CpProxyUpnpOrgDimming1C::RampPausedPropertyChanged()
{
    ReportEvent(iRampPausedChanged);
}


THandle CpProxyUpnpOrgDimming1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgDimming1C(aDevice);
}

void CpProxyUpnpOrgDimming1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(THandle aHandle, uint32_t anewLoadlevelTarget)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetLoadLevelTarget(anewLoadlevelTarget);
}

void CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(THandle aHandle, uint32_t anewLoadlevelTarget, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetLoadLevelTarget(anewLoadlevelTarget, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetLoadLevelTarget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(THandle aHandle, uint32_t* aGetLoadlevelTarget)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetLoadLevelTarget(*aGetLoadlevelTarget);
}

void CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetLoadLevelTarget(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetLoadLevelTarget(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aGetLoadlevelTarget)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetLoadLevelTarget(*async, *aGetLoadlevelTarget);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(THandle aHandle, uint32_t* aretLoadlevelStatus)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetLoadLevelStatus(*aretLoadlevelStatus);
}

void CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetLoadLevelStatus(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetLoadLevelStatus(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretLoadlevelStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetLoadLevelStatus(*async, *aretLoadlevelStatus);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(THandle aHandle, uint32_t anewOnEffectLevel)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetOnEffectLevel(anewOnEffectLevel);
}

void CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(THandle aHandle, uint32_t anewOnEffectLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetOnEffectLevel(anewOnEffectLevel, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetOnEffectLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetOnEffectLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetOnEffect(THandle aHandle, const char* anewOnEffect)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_anewOnEffect(anewOnEffect);
    proxyC->SyncSetOnEffect(buf_anewOnEffect);
}

void CpProxyUpnpOrgDimming1BeginSetOnEffect(THandle aHandle, const char* anewOnEffect, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_anewOnEffect(anewOnEffect);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetOnEffect(buf_anewOnEffect, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetOnEffect(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetOnEffect(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetOnEffectParameters(THandle aHandle, char** aretOnEffect, uint32_t* aretOnEffectLevel)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aretOnEffect;
    proxyC->SyncGetOnEffectParameters(buf_aretOnEffect, *aretOnEffectLevel);
    *aretOnEffect = buf_aretOnEffect.Extract();
}

void CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetOnEffectParameters(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetOnEffectParameters(THandle aHandle, ZappHandleAsync aAsync, char** aretOnEffect, uint32_t* aretOnEffectLevel)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aretOnEffect;
    *aretOnEffect = NULL;
    try {
        proxyC->EndGetOnEffectParameters(*async, buf_aretOnEffect, *aretOnEffectLevel);
        *aretOnEffect = buf_aretOnEffect.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStepUp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStepUp();
}

void CpProxyUpnpOrgDimming1BeginStepUp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStepUp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStepUp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStepUp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStepDown(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStepDown();
}

void CpProxyUpnpOrgDimming1BeginStepDown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStepDown(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStepDown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStepDown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStartRampUp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStartRampUp();
}

void CpProxyUpnpOrgDimming1BeginStartRampUp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartRampUp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStartRampUp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStartRampUp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStartRampDown(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStartRampDown();
}

void CpProxyUpnpOrgDimming1BeginStartRampDown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartRampDown(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStartRampDown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStartRampDown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStopRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStopRamp();
}

void CpProxyUpnpOrgDimming1BeginStopRamp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStopRamp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndStopRamp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStopRamp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncStartRampToLevel(THandle aHandle, uint32_t anewLoadLevelTarget, uint32_t anewRampTime)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStartRampToLevel(anewLoadLevelTarget, anewRampTime);
}

void CpProxyUpnpOrgDimming1BeginStartRampToLevel(THandle aHandle, uint32_t anewLoadLevelTarget, uint32_t anewRampTime, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStartRampToLevel(anewLoadLevelTarget, anewRampTime, functor);
}

int32_t CpProxyUpnpOrgDimming1EndStartRampToLevel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStartRampToLevel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetStepDelta(THandle aHandle, uint32_t anewStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStepDelta(anewStepDelta);
}

void CpProxyUpnpOrgDimming1BeginSetStepDelta(THandle aHandle, uint32_t anewStepDelta, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStepDelta(anewStepDelta, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetStepDelta(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStepDelta(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetStepDelta(THandle aHandle, uint32_t* aretStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetStepDelta(*aretStepDelta);
}

void CpProxyUpnpOrgDimming1BeginGetStepDelta(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetStepDelta(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetStepDelta(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretStepDelta)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetStepDelta(*async, *aretStepDelta);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncSetRampRate(THandle aHandle, uint32_t anewRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetRampRate(anewRampRate);
}

void CpProxyUpnpOrgDimming1BeginSetRampRate(THandle aHandle, uint32_t anewRampRate, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetRampRate(anewRampRate, functor);
}

int32_t CpProxyUpnpOrgDimming1EndSetRampRate(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRampRate(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetRampRate(THandle aHandle, uint32_t* aretRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetRampRate(*aretRampRate);
}

void CpProxyUpnpOrgDimming1BeginGetRampRate(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetRampRate(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetRampRate(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretRampRate)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetRampRate(*async, *aretRampRate);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncPauseRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPauseRamp();
}

void CpProxyUpnpOrgDimming1BeginPauseRamp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPauseRamp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndPauseRamp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPauseRamp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncResumeRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncResumeRamp();
}

void CpProxyUpnpOrgDimming1BeginResumeRamp(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginResumeRamp(functor);
}

int32_t CpProxyUpnpOrgDimming1EndResumeRamp(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndResumeRamp(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetIsRamping(THandle aHandle, uint32_t* aretIsRamping)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aretIsRamping = 0;
    proxyC->SyncGetIsRamping(*(TBool*)aretIsRamping);
}

void CpProxyUpnpOrgDimming1BeginGetIsRamping(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetIsRamping(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetIsRamping(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretIsRamping)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aretIsRamping = 0;
    try {
        proxyC->EndGetIsRamping(*async, *(TBool*)aretIsRamping);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetRampPaused(THandle aHandle, uint32_t* aretRampPaused)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aretRampPaused = 0;
    proxyC->SyncGetRampPaused(*(TBool*)aretRampPaused);
}

void CpProxyUpnpOrgDimming1BeginGetRampPaused(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetRampPaused(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetRampPaused(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretRampPaused)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aretRampPaused = 0;
    try {
        proxyC->EndGetRampPaused(*async, *(TBool*)aretRampPaused);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SyncGetRampTime(THandle aHandle, uint32_t* aretRampTime)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetRampTime(*aretRampTime);
}

void CpProxyUpnpOrgDimming1BeginGetRampTime(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetRampTime(functor);
}

int32_t CpProxyUpnpOrgDimming1EndGetRampTime(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aretRampTime)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetRampTime(*async, *aretRampTime);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgDimming1SetPropertyLoadLevelStatusChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLoadLevelStatusChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyStepDeltaChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStepDeltaChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyRampRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRampRateChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyIsRampingChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIsRampingChanged(functor);
}

void CpProxyUpnpOrgDimming1SetPropertyRampPausedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRampPausedChanged(functor);
}

void CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(THandle aHandle, uint32_t* aLoadLevelStatus)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyLoadLevelStatus(*aLoadLevelStatus);
}

void CpProxyUpnpOrgDimming1PropertyStepDelta(THandle aHandle, uint32_t* aStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyStepDelta(*aStepDelta);
}

void CpProxyUpnpOrgDimming1PropertyRampRate(THandle aHandle, uint32_t* aRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyRampRate(*aRampRate);
}

void CpProxyUpnpOrgDimming1PropertyIsRamping(THandle aHandle, uint32_t* aIsRamping)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aIsRamping = false;
    proxyC->PropertyIsRamping(*(TBool*)aIsRamping);
}

void CpProxyUpnpOrgDimming1PropertyRampPaused(THandle aHandle, uint32_t* aRampPaused)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aRampPaused = false;
    proxyC->PropertyRampPaused(*(TBool*)aRampPaused);
}

