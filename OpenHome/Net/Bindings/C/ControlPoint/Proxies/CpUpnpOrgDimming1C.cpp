#include "CpUpnpOrgDimming1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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
    virtual ~SyncSetLoadLevelTargetUpnpOrgDimming1C() {};
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
    virtual ~SyncGetLoadLevelTargetUpnpOrgDimming1C() {};
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
    virtual ~SyncGetLoadLevelStatusUpnpOrgDimming1C() {};
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
    virtual ~SyncSetOnEffectLevelUpnpOrgDimming1C() {};
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
    virtual ~SyncSetOnEffectUpnpOrgDimming1C() {};
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
    virtual ~SyncGetOnEffectParametersUpnpOrgDimming1C() {};
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
    virtual ~SyncStepUpUpnpOrgDimming1C() {};
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
    virtual ~SyncStepDownUpnpOrgDimming1C() {};
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
    virtual ~SyncStartRampUpUpnpOrgDimming1C() {};
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
    virtual ~SyncStartRampDownUpnpOrgDimming1C() {};
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
    virtual ~SyncStopRampUpnpOrgDimming1C() {};
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
    virtual ~SyncStartRampToLevelUpnpOrgDimming1C() {};
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
    virtual ~SyncSetStepDeltaUpnpOrgDimming1C() {};
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
    virtual ~SyncGetStepDeltaUpnpOrgDimming1C() {};
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
    virtual ~SyncSetRampRateUpnpOrgDimming1C() {};
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
    virtual ~SyncGetRampRateUpnpOrgDimming1C() {};
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
    virtual ~SyncPauseRampUpnpOrgDimming1C() {};
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
    virtual ~SyncResumeRampUpnpOrgDimming1C() {};
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
    virtual ~SyncGetIsRampingUpnpOrgDimming1C() {};
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
    virtual ~SyncGetRampPausedUpnpOrgDimming1C() {};
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
    virtual ~SyncGetRampTimeUpnpOrgDimming1C() {};
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
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionSetLoadLevelTarget = new Action("SetLoadLevelTarget");
    param = new OpenHome::Net::ParameterUint("newLoadlevelTarget", 0, 100);
    iActionSetLoadLevelTarget->AddInputParameter(param);

    iActionGetLoadLevelTarget = new Action("GetLoadLevelTarget");
    param = new OpenHome::Net::ParameterUint("GetLoadlevelTarget", 0, 100);
    iActionGetLoadLevelTarget->AddOutputParameter(param);

    iActionGetLoadLevelStatus = new Action("GetLoadLevelStatus");
    param = new OpenHome::Net::ParameterUint("retLoadlevelStatus", 0, 100);
    iActionGetLoadLevelStatus->AddOutputParameter(param);

    iActionSetOnEffectLevel = new Action("SetOnEffectLevel");
    param = new OpenHome::Net::ParameterUint("newOnEffectLevel", 0, 100);
    iActionSetOnEffectLevel->AddInputParameter(param);

    iActionSetOnEffect = new Action("SetOnEffect");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    param = new OpenHome::Net::ParameterString("newOnEffect", allowedValues, 3);
    iActionSetOnEffect->AddInputParameter(param);
    delete[] allowedValues;

    iActionGetOnEffectParameters = new Action("GetOnEffectParameters");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    param = new OpenHome::Net::ParameterString("retOnEffect", allowedValues, 3);
    iActionGetOnEffectParameters->AddOutputParameter(param);
    delete[] allowedValues;
    param = new OpenHome::Net::ParameterUint("retOnEffectLevel", 0, 100);
    iActionGetOnEffectParameters->AddOutputParameter(param);

    iActionStepUp = new Action("StepUp");

    iActionStepDown = new Action("StepDown");

    iActionStartRampUp = new Action("StartRampUp");

    iActionStartRampDown = new Action("StartRampDown");

    iActionStopRamp = new Action("StopRamp");

    iActionStartRampToLevel = new Action("StartRampToLevel");
    param = new OpenHome::Net::ParameterUint("newLoadLevelTarget", 0, 100);
    iActionStartRampToLevel->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("newRampTime");
    iActionStartRampToLevel->AddInputParameter(param);

    iActionSetStepDelta = new Action("SetStepDelta");
    param = new OpenHome::Net::ParameterUint("newStepDelta", 1, 100);
    iActionSetStepDelta->AddInputParameter(param);

    iActionGetStepDelta = new Action("GetStepDelta");
    param = new OpenHome::Net::ParameterUint("retStepDelta", 1, 100);
    iActionGetStepDelta->AddOutputParameter(param);

    iActionSetRampRate = new Action("SetRampRate");
    param = new OpenHome::Net::ParameterUint("newRampRate", 0, 100);
    iActionSetRampRate->AddInputParameter(param);

    iActionGetRampRate = new Action("GetRampRate");
    param = new OpenHome::Net::ParameterUint("retRampRate", 0, 100);
    iActionGetRampRate->AddOutputParameter(param);

    iActionPauseRamp = new Action("PauseRamp");

    iActionResumeRamp = new Action("ResumeRamp");

    iActionGetIsRamping = new Action("GetIsRamping");
    param = new OpenHome::Net::ParameterBool("retIsRamping");
    iActionGetIsRamping->AddOutputParameter(param);

    iActionGetRampPaused = new Action("GetRampPaused");
    param = new OpenHome::Net::ParameterBool("retRampPaused");
    iActionGetRampPaused->AddOutputParameter(param);

    iActionGetRampTime = new Action("GetRampTime");
    param = new OpenHome::Net::ParameterUint("retRampTime");
    iActionGetRampTime->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::LoadLevelStatusPropertyChanged);
    iLoadLevelStatus = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "LoadLevelStatus", functor);
    AddProperty(iLoadLevelStatus);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::StepDeltaPropertyChanged);
    iStepDelta = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "StepDelta", functor);
    AddProperty(iStepDelta);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::RampRatePropertyChanged);
    iRampRate = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "RampRate", functor);
    AddProperty(iRampRate);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::IsRampingPropertyChanged);
    iIsRamping = new PropertyBool(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "IsRamping", functor);
    AddProperty(iIsRamping);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1C::RampPausedPropertyChanged);
    iRampPaused = new PropertyBool(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "RampPaused", functor);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLoadLevelStatus = iLoadLevelStatus->Value();
}

void CpProxyUpnpOrgDimming1C::PropertyStepDelta(TUint& aStepDelta) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aStepDelta = iStepDelta->Value();
}

void CpProxyUpnpOrgDimming1C::PropertyRampRate(TUint& aRampRate) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aRampRate = iRampRate->Value();
}

void CpProxyUpnpOrgDimming1C::PropertyIsRamping(TBool& aIsRamping) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aIsRamping = iIsRamping->Value();
}

void CpProxyUpnpOrgDimming1C::PropertyRampPaused(TBool& aRampPaused) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aRampPaused = iRampPaused->Value();
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


THandle STDCALL CpProxyUpnpOrgDimming1Create(CpDeviceC aDevice)
{
    return new CpProxyUpnpOrgDimming1C(aDevice);
}

void STDCALL CpProxyUpnpOrgDimming1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyUpnpOrgDimming1SyncSetLoadLevelTarget(THandle aHandle, uint32_t anewLoadlevelTarget)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetLoadLevelTarget(anewLoadlevelTarget);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginSetLoadLevelTarget(THandle aHandle, uint32_t anewLoadlevelTarget, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetLoadLevelTarget(anewLoadlevelTarget, functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndSetLoadLevelTarget(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetLoadLevelTarget(THandle aHandle, uint32_t* aGetLoadlevelTarget)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetLoadLevelTarget(*aGetLoadlevelTarget);
    }
    catch (ProxyError& ) {
        err = -1;
        *aGetLoadlevelTarget = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetLoadLevelTarget(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetLoadLevelTarget(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetLoadLevelTarget(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aGetLoadlevelTarget)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetLoadLevelStatus(THandle aHandle, uint32_t* aretLoadlevelStatus)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetLoadLevelStatus(*aretLoadlevelStatus);
    }
    catch (ProxyError& ) {
        err = -1;
        *aretLoadlevelStatus = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetLoadLevelStatus(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetLoadLevelStatus(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetLoadLevelStatus(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aretLoadlevelStatus)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncSetOnEffectLevel(THandle aHandle, uint32_t anewOnEffectLevel)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetOnEffectLevel(anewOnEffectLevel);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginSetOnEffectLevel(THandle aHandle, uint32_t anewOnEffectLevel, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetOnEffectLevel(anewOnEffectLevel, functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndSetOnEffectLevel(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncSetOnEffect(THandle aHandle, const char* anewOnEffect)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_anewOnEffect(anewOnEffect);
    int32_t err = 0;
    try {
        proxyC->SyncSetOnEffect(buf_anewOnEffect);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginSetOnEffect(THandle aHandle, const char* anewOnEffect, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_anewOnEffect(anewOnEffect);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetOnEffect(buf_anewOnEffect, functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndSetOnEffect(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetOnEffectParameters(THandle aHandle, char** aretOnEffect, uint32_t* aretOnEffectLevel)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aretOnEffect;
    int32_t err = 0;
    try {
        proxyC->SyncGetOnEffectParameters(buf_aretOnEffect, *aretOnEffectLevel);
        *aretOnEffect = buf_aretOnEffect.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aretOnEffect = NULL;
        *aretOnEffectLevel = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetOnEffectParameters(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetOnEffectParameters(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetOnEffectParameters(THandle aHandle, OhNetHandleAsync aAsync, char** aretOnEffect, uint32_t* aretOnEffectLevel)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncStepUp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStepUp();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginStepUp(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStepUp(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndStepUp(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncStepDown(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStepDown();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginStepDown(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStepDown(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndStepDown(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncStartRampUp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStartRampUp();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginStartRampUp(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStartRampUp(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndStartRampUp(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncStartRampDown(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStartRampDown();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginStartRampDown(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStartRampDown(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndStartRampDown(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncStopRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStopRamp();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginStopRamp(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStopRamp(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndStopRamp(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncStartRampToLevel(THandle aHandle, uint32_t anewLoadLevelTarget, uint32_t anewRampTime)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncStartRampToLevel(anewLoadLevelTarget, anewRampTime);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginStartRampToLevel(THandle aHandle, uint32_t anewLoadLevelTarget, uint32_t anewRampTime, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStartRampToLevel(anewLoadLevelTarget, anewRampTime, functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndStartRampToLevel(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncSetStepDelta(THandle aHandle, uint32_t anewStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetStepDelta(anewStepDelta);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginSetStepDelta(THandle aHandle, uint32_t anewStepDelta, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetStepDelta(anewStepDelta, functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndSetStepDelta(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetStepDelta(THandle aHandle, uint32_t* aretStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetStepDelta(*aretStepDelta);
    }
    catch (ProxyError& ) {
        err = -1;
        *aretStepDelta = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetStepDelta(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetStepDelta(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetStepDelta(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aretStepDelta)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncSetRampRate(THandle aHandle, uint32_t anewRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetRampRate(anewRampRate);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginSetRampRate(THandle aHandle, uint32_t anewRampRate, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetRampRate(anewRampRate, functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndSetRampRate(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetRampRate(THandle aHandle, uint32_t* aretRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetRampRate(*aretRampRate);
    }
    catch (ProxyError& ) {
        err = -1;
        *aretRampRate = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetRampRate(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRampRate(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetRampRate(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aretRampRate)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncPauseRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncPauseRamp();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginPauseRamp(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPauseRamp(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndPauseRamp(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncResumeRamp(THandle aHandle)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncResumeRamp();
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginResumeRamp(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginResumeRamp(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndResumeRamp(THandle aHandle, OhNetHandleAsync aAsync)
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

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetIsRamping(THandle aHandle, uint32_t* aretIsRamping)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool retIsRamping;
    int32_t err = 0;
    try {
        proxyC->SyncGetIsRamping(retIsRamping);
        *aretIsRamping = retIsRamping? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aretIsRamping = false;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetIsRamping(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetIsRamping(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetIsRamping(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aretIsRamping)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool retIsRamping;
    try {
        proxyC->EndGetIsRamping(*async, retIsRamping);
        *aretIsRamping = retIsRamping? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetRampPaused(THandle aHandle, uint32_t* aretRampPaused)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool retRampPaused;
    int32_t err = 0;
    try {
        proxyC->SyncGetRampPaused(retRampPaused);
        *aretRampPaused = retRampPaused? 1 : 0;
    }
    catch (ProxyError& ) {
        err = -1;
        *aretRampPaused = false;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetRampPaused(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRampPaused(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetRampPaused(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aretRampPaused)
{
    int32_t err = 0;
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool retRampPaused;
    try {
        proxyC->EndGetRampPaused(*async, retRampPaused);
        *aretRampPaused = retRampPaused? 1 : 0;
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyUpnpOrgDimming1SyncGetRampTime(THandle aHandle, uint32_t* aretRampTime)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetRampTime(*aretRampTime);
    }
    catch (ProxyError& ) {
        err = -1;
        *aretRampTime = 0;
    }
    return err;
}

void STDCALL CpProxyUpnpOrgDimming1BeginGetRampTime(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRampTime(functor);
}

int32_t STDCALL CpProxyUpnpOrgDimming1EndGetRampTime(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aretRampTime)
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

void STDCALL CpProxyUpnpOrgDimming1SetPropertyLoadLevelStatusChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLoadLevelStatusChanged(functor);
}

void STDCALL CpProxyUpnpOrgDimming1SetPropertyStepDeltaChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStepDeltaChanged(functor);
}

void STDCALL CpProxyUpnpOrgDimming1SetPropertyRampRateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRampRateChanged(functor);
}

void STDCALL CpProxyUpnpOrgDimming1SetPropertyIsRampingChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyIsRampingChanged(functor);
}

void STDCALL CpProxyUpnpOrgDimming1SetPropertyRampPausedChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRampPausedChanged(functor);
}

void STDCALL CpProxyUpnpOrgDimming1PropertyLoadLevelStatus(THandle aHandle, uint32_t* aLoadLevelStatus)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyLoadLevelStatus(*aLoadLevelStatus);
}

void STDCALL CpProxyUpnpOrgDimming1PropertyStepDelta(THandle aHandle, uint32_t* aStepDelta)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyStepDelta(*aStepDelta);
}

void STDCALL CpProxyUpnpOrgDimming1PropertyRampRate(THandle aHandle, uint32_t* aRampRate)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyRampRate(*aRampRate);
}

void STDCALL CpProxyUpnpOrgDimming1PropertyIsRamping(THandle aHandle, uint32_t* aIsRamping)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool IsRamping;
    proxyC->PropertyIsRamping(IsRamping);
    *aIsRamping = IsRamping? 1 : 0;
}

void STDCALL CpProxyUpnpOrgDimming1PropertyRampPaused(THandle aHandle, uint32_t* aRampPaused)
{
    CpProxyUpnpOrgDimming1C* proxyC = reinterpret_cast<CpProxyUpnpOrgDimming1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool RampPaused;
    proxyC->PropertyRampPaused(RampPaused);
    *aRampPaused = RampPaused? 1 : 0;
}

