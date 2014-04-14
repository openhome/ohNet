#include "CpUpnpOrgDimming1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncSetLoadLevelTargetUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetLoadLevelTargetUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetLoadLevelTargetUpnpOrgDimming1Cpp::SyncSetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetLoadLevelTargetUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoadLevelTarget(aAsync);
}


class SyncGetLoadLevelTargetUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aGetLoadlevelTarget);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetLoadLevelTargetUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iGetLoadlevelTarget;
};

SyncGetLoadLevelTargetUpnpOrgDimming1Cpp::SyncGetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aGetLoadlevelTarget)
    : iService(aProxy)
    , iGetLoadlevelTarget(aGetLoadlevelTarget)
{
}

void SyncGetLoadLevelTargetUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoadLevelTarget(aAsync, iGetLoadlevelTarget);
}


class SyncGetLoadLevelStatusUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetLoadLevelStatusUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretLoadlevelStatus);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetLoadLevelStatusUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretLoadlevelStatus;
};

SyncGetLoadLevelStatusUpnpOrgDimming1Cpp::SyncGetLoadLevelStatusUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretLoadlevelStatus)
    : iService(aProxy)
    , iretLoadlevelStatus(aretLoadlevelStatus)
{
}

void SyncGetLoadLevelStatusUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoadLevelStatus(aAsync, iretLoadlevelStatus);
}


class SyncSetOnEffectLevelUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetOnEffectLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetOnEffectLevelUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetOnEffectLevelUpnpOrgDimming1Cpp::SyncSetOnEffectLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetOnEffectLevelUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffectLevel(aAsync);
}


class SyncSetOnEffectUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetOnEffectUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetOnEffectUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetOnEffectUpnpOrgDimming1Cpp::SyncSetOnEffectUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetOnEffectUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffect(aAsync);
}


class SyncGetOnEffectParametersUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetOnEffectParametersUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, std::string& aretOnEffect, uint32_t& aretOnEffectLevel);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetOnEffectParametersUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    std::string& iretOnEffect;
    uint32_t& iretOnEffectLevel;
};

SyncGetOnEffectParametersUpnpOrgDimming1Cpp::SyncGetOnEffectParametersUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, std::string& aretOnEffect, uint32_t& aretOnEffectLevel)
    : iService(aProxy)
    , iretOnEffect(aretOnEffect)
    , iretOnEffectLevel(aretOnEffectLevel)
{
}

void SyncGetOnEffectParametersUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetOnEffectParameters(aAsync, iretOnEffect, iretOnEffectLevel);
}


class SyncStepUpUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStepUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStepUpUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStepUpUpnpOrgDimming1Cpp::SyncStepUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStepUpUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepUp(aAsync);
}


class SyncStepDownUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStepDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStepDownUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStepDownUpnpOrgDimming1Cpp::SyncStepDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStepDownUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepDown(aAsync);
}


class SyncStartRampUpUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStartRampUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStartRampUpUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStartRampUpUpnpOrgDimming1Cpp::SyncStartRampUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStartRampUpUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampUp(aAsync);
}


class SyncStartRampDownUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStartRampDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStartRampDownUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStartRampDownUpnpOrgDimming1Cpp::SyncStartRampDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStartRampDownUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampDown(aAsync);
}


class SyncStopRampUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStopRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStopRampUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStopRampUpnpOrgDimming1Cpp::SyncStopRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStopRampUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopRamp(aAsync);
}


class SyncStartRampToLevelUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStartRampToLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStartRampToLevelUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStartRampToLevelUpnpOrgDimming1Cpp::SyncStartRampToLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncStartRampToLevelUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampToLevel(aAsync);
}


class SyncSetStepDeltaUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStepDeltaUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetStepDeltaUpnpOrgDimming1Cpp::SyncSetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetStepDeltaUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStepDelta(aAsync);
}


class SyncGetStepDeltaUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretStepDelta);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetStepDeltaUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretStepDelta;
};

SyncGetStepDeltaUpnpOrgDimming1Cpp::SyncGetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretStepDelta)
    : iService(aProxy)
    , iretStepDelta(aretStepDelta)
{
}

void SyncGetStepDeltaUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStepDelta(aAsync, iretStepDelta);
}


class SyncSetRampRateUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetRampRateUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetRampRateUpnpOrgDimming1Cpp::SyncSetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetRampRateUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRampRate(aAsync);
}


class SyncGetRampRateUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretRampRate);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRampRateUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretRampRate;
};

SyncGetRampRateUpnpOrgDimming1Cpp::SyncGetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretRampRate)
    : iService(aProxy)
    , iretRampRate(aretRampRate)
{
}

void SyncGetRampRateUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampRate(aAsync, iretRampRate);
}


class SyncPauseRampUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncPauseRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPauseRampUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncPauseRampUpnpOrgDimming1Cpp::SyncPauseRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncPauseRampUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPauseRamp(aAsync);
}


class SyncResumeRampUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncResumeRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncResumeRampUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncResumeRampUpnpOrgDimming1Cpp::SyncResumeRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncResumeRampUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndResumeRamp(aAsync);
}


class SyncGetIsRampingUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetIsRampingUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, bool& aretIsRamping);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetIsRampingUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    bool& iretIsRamping;
};

SyncGetIsRampingUpnpOrgDimming1Cpp::SyncGetIsRampingUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, bool& aretIsRamping)
    : iService(aProxy)
    , iretIsRamping(aretIsRamping)
{
}

void SyncGetIsRampingUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetIsRamping(aAsync, iretIsRamping);
}


class SyncGetRampPausedUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetRampPausedUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, bool& aretRampPaused);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRampPausedUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    bool& iretRampPaused;
};

SyncGetRampPausedUpnpOrgDimming1Cpp::SyncGetRampPausedUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, bool& aretRampPaused)
    : iService(aProxy)
    , iretRampPaused(aretRampPaused)
{
}

void SyncGetRampPausedUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampPaused(aAsync, iretRampPaused);
}


class SyncGetRampTimeUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetRampTimeUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretRampTime);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRampTimeUpnpOrgDimming1Cpp() {}
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretRampTime;
};

SyncGetRampTimeUpnpOrgDimming1Cpp::SyncGetRampTimeUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aProxy, uint32_t& aretRampTime)
    : iService(aProxy)
    , iretRampTime(aretRampTime)
{
}

void SyncGetRampTimeUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampTime(aAsync, iretRampTime);
}


CpProxyUpnpOrgDimming1Cpp::CpProxyUpnpOrgDimming1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("schemas-upnp-org", "Dimming", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::LoadLevelStatusPropertyChanged);
    iLoadLevelStatus = new PropertyUint(aDevice.Device().GetCpStack().Env(), "LoadLevelStatus", functor);
    AddProperty(iLoadLevelStatus);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::StepDeltaPropertyChanged);
    iStepDelta = new PropertyUint(aDevice.Device().GetCpStack().Env(), "StepDelta", functor);
    AddProperty(iStepDelta);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::RampRatePropertyChanged);
    iRampRate = new PropertyUint(aDevice.Device().GetCpStack().Env(), "RampRate", functor);
    AddProperty(iRampRate);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::IsRampingPropertyChanged);
    iIsRamping = new PropertyBool(aDevice.Device().GetCpStack().Env(), "IsRamping", functor);
    AddProperty(iIsRamping);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::RampPausedPropertyChanged);
    iRampPaused = new PropertyBool(aDevice.Device().GetCpStack().Env(), "RampPaused", functor);
    AddProperty(iRampPaused);
}

CpProxyUpnpOrgDimming1Cpp::~CpProxyUpnpOrgDimming1Cpp()
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

void CpProxyUpnpOrgDimming1Cpp::SyncSetLoadLevelTarget(uint32_t anewLoadlevelTarget)
{
    SyncSetLoadLevelTargetUpnpOrgDimming1Cpp sync(*this);
    BeginSetLoadLevelTarget(anewLoadlevelTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginSetLoadLevelTarget(uint32_t anewLoadlevelTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLoadLevelTarget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoadLevelTarget->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewLoadlevelTarget));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndSetLoadLevelTarget(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetLoadLevelTarget(uint32_t& aGetLoadlevelTarget)
{
    SyncGetLoadLevelTargetUpnpOrgDimming1Cpp sync(*this, aGetLoadlevelTarget);
    BeginGetLoadLevelTarget(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetLoadLevelTarget(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoadLevelTarget, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoadLevelTarget->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetLoadLevelTarget(IAsync& aAsync, uint32_t& aGetLoadlevelTarget)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetLoadLevelStatus(uint32_t& aretLoadlevelStatus)
{
    SyncGetLoadLevelStatusUpnpOrgDimming1Cpp sync(*this, aretLoadlevelStatus);
    BeginGetLoadLevelStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetLoadLevelStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoadLevelStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoadLevelStatus->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetLoadLevelStatus(IAsync& aAsync, uint32_t& aretLoadlevelStatus)
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

void CpProxyUpnpOrgDimming1Cpp::SyncSetOnEffectLevel(uint32_t anewOnEffectLevel)
{
    SyncSetOnEffectLevelUpnpOrgDimming1Cpp sync(*this);
    BeginSetOnEffectLevel(anewOnEffectLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginSetOnEffectLevel(uint32_t anewOnEffectLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetOnEffectLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetOnEffectLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewOnEffectLevel));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndSetOnEffectLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncSetOnEffect(const std::string& anewOnEffect)
{
    SyncSetOnEffectUpnpOrgDimming1Cpp sync(*this);
    BeginSetOnEffect(anewOnEffect, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginSetOnEffect(const std::string& anewOnEffect, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetOnEffect, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetOnEffect->InputParameters();
    {
        Brn buf((const TByte*)anewOnEffect.c_str(), (TUint)anewOnEffect.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndSetOnEffect(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetOnEffectParameters(std::string& aretOnEffect, uint32_t& aretOnEffectLevel)
{
    SyncGetOnEffectParametersUpnpOrgDimming1Cpp sync(*this, aretOnEffect, aretOnEffectLevel);
    BeginGetOnEffectParameters(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetOnEffectParameters(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetOnEffectParameters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetOnEffectParameters->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetOnEffectParameters(IAsync& aAsync, std::string& aretOnEffect, uint32_t& aretOnEffectLevel)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aretOnEffect.assign((const char*)val.Ptr(), val.Bytes());
    }
    aretOnEffectLevel = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyUpnpOrgDimming1Cpp::SyncStepUp()
{
    SyncStepUpUpnpOrgDimming1Cpp sync(*this);
    BeginStepUp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginStepUp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStepUp, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndStepUp(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncStepDown()
{
    SyncStepDownUpnpOrgDimming1Cpp sync(*this);
    BeginStepDown(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginStepDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStepDown, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndStepDown(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncStartRampUp()
{
    SyncStartRampUpUpnpOrgDimming1Cpp sync(*this);
    BeginStartRampUp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginStartRampUp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartRampUp, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndStartRampUp(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncStartRampDown()
{
    SyncStartRampDownUpnpOrgDimming1Cpp sync(*this);
    BeginStartRampDown(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginStartRampDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartRampDown, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndStartRampDown(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncStopRamp()
{
    SyncStopRampUpnpOrgDimming1Cpp sync(*this);
    BeginStopRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginStopRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStopRamp, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndStopRamp(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncStartRampToLevel(uint32_t anewLoadLevelTarget, uint32_t anewRampTime)
{
    SyncStartRampToLevelUpnpOrgDimming1Cpp sync(*this);
    BeginStartRampToLevel(anewLoadLevelTarget, anewRampTime, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginStartRampToLevel(uint32_t anewLoadLevelTarget, uint32_t anewRampTime, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartRampToLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStartRampToLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewLoadLevelTarget));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewRampTime));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndStartRampToLevel(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncSetStepDelta(uint32_t anewStepDelta)
{
    SyncSetStepDeltaUpnpOrgDimming1Cpp sync(*this);
    BeginSetStepDelta(anewStepDelta, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginSetStepDelta(uint32_t anewStepDelta, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStepDelta, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStepDelta->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewStepDelta));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndSetStepDelta(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetStepDelta(uint32_t& aretStepDelta)
{
    SyncGetStepDeltaUpnpOrgDimming1Cpp sync(*this, aretStepDelta);
    BeginGetStepDelta(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetStepDelta(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStepDelta, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStepDelta->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetStepDelta(IAsync& aAsync, uint32_t& aretStepDelta)
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

void CpProxyUpnpOrgDimming1Cpp::SyncSetRampRate(uint32_t anewRampRate)
{
    SyncSetRampRateUpnpOrgDimming1Cpp sync(*this);
    BeginSetRampRate(anewRampRate, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginSetRampRate(uint32_t anewRampRate, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRampRate, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRampRate->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewRampRate));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndSetRampRate(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetRampRate(uint32_t& aretRampRate)
{
    SyncGetRampRateUpnpOrgDimming1Cpp sync(*this, aretRampRate);
    BeginGetRampRate(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetRampRate(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRampRate, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampRate->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetRampRate(IAsync& aAsync, uint32_t& aretRampRate)
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

void CpProxyUpnpOrgDimming1Cpp::SyncPauseRamp()
{
    SyncPauseRampUpnpOrgDimming1Cpp sync(*this);
    BeginPauseRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginPauseRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPauseRamp, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndPauseRamp(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncResumeRamp()
{
    SyncResumeRampUpnpOrgDimming1Cpp sync(*this);
    BeginResumeRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginResumeRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionResumeRamp, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndResumeRamp(IAsync& aAsync)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetIsRamping(bool& aretIsRamping)
{
    SyncGetIsRampingUpnpOrgDimming1Cpp sync(*this, aretIsRamping);
    BeginGetIsRamping(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetIsRamping(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetIsRamping, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetIsRamping->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetIsRamping(IAsync& aAsync, bool& aretIsRamping)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetRampPaused(bool& aretRampPaused)
{
    SyncGetRampPausedUpnpOrgDimming1Cpp sync(*this, aretRampPaused);
    BeginGetRampPaused(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetRampPaused(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRampPaused, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampPaused->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetRampPaused(IAsync& aAsync, bool& aretRampPaused)
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

void CpProxyUpnpOrgDimming1Cpp::SyncGetRampTime(uint32_t& aretRampTime)
{
    SyncGetRampTimeUpnpOrgDimming1Cpp sync(*this, aretRampTime);
    BeginGetRampTime(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginGetRampTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRampTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyUpnpOrgDimming1Cpp::EndGetRampTime(IAsync& aAsync, uint32_t& aretRampTime)
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

void CpProxyUpnpOrgDimming1Cpp::SetPropertyLoadLevelStatusChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLoadLevelStatusChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1Cpp::SetPropertyStepDeltaChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStepDeltaChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1Cpp::SetPropertyRampRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRampRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1Cpp::SetPropertyIsRampingChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIsRampingChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1Cpp::SetPropertyRampPausedChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRampPausedChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyLoadLevelStatus(uint32_t& aLoadLevelStatus) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLoadLevelStatus = iLoadLevelStatus->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyStepDelta(uint32_t& aStepDelta) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStepDelta = iStepDelta->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyRampRate(uint32_t& aRampRate) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRampRate = iRampRate->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyIsRamping(bool& aIsRamping) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIsRamping = iIsRamping->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyRampPaused(bool& aRampPaused) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRampPaused = iRampPaused->Value();
}

void CpProxyUpnpOrgDimming1Cpp::LoadLevelStatusPropertyChanged()
{
    ReportEvent(iLoadLevelStatusChanged);
}

void CpProxyUpnpOrgDimming1Cpp::StepDeltaPropertyChanged()
{
    ReportEvent(iStepDeltaChanged);
}

void CpProxyUpnpOrgDimming1Cpp::RampRatePropertyChanged()
{
    ReportEvent(iRampRateChanged);
}

void CpProxyUpnpOrgDimming1Cpp::IsRampingPropertyChanged()
{
    ReportEvent(iIsRampingChanged);
}

void CpProxyUpnpOrgDimming1Cpp::RampPausedPropertyChanged()
{
    ReportEvent(iRampPausedChanged);
}

