#include <Std/CpUpnpOrgDimming1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncSetLoadLevelTargetUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetLoadLevelTargetUpnpOrgDimming1Cpp::SyncSetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncSetLoadLevelTargetUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoadLevelTarget(aAsync);
}


class SyncGetLoadLevelTargetUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aGetLoadlevelTarget);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iGetLoadlevelTarget;
};

SyncGetLoadLevelTargetUpnpOrgDimming1Cpp::SyncGetLoadLevelTargetUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aGetLoadlevelTarget)
    : iService(aService)
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
    SyncGetLoadLevelStatusUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretLoadlevelStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretLoadlevelStatus;
};

SyncGetLoadLevelStatusUpnpOrgDimming1Cpp::SyncGetLoadLevelStatusUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretLoadlevelStatus)
    : iService(aService)
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
    SyncSetOnEffectLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetOnEffectLevelUpnpOrgDimming1Cpp::SyncSetOnEffectLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncSetOnEffectLevelUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffectLevel(aAsync);
}


class SyncSetOnEffectUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetOnEffectUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetOnEffectUpnpOrgDimming1Cpp::SyncSetOnEffectUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncSetOnEffectUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffect(aAsync);
}


class SyncGetOnEffectParametersUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetOnEffectParametersUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, std::string& aretOnEffect, uint32_t& aretOnEffectLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    std::string& iretOnEffect;
    uint32_t& iretOnEffectLevel;
};

SyncGetOnEffectParametersUpnpOrgDimming1Cpp::SyncGetOnEffectParametersUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, std::string& aretOnEffect, uint32_t& aretOnEffectLevel)
    : iService(aService)
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
    SyncStepUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStepUpUpnpOrgDimming1Cpp::SyncStepUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncStepUpUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepUp(aAsync);
}


class SyncStepDownUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStepDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStepDownUpnpOrgDimming1Cpp::SyncStepDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncStepDownUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepDown(aAsync);
}


class SyncStartRampUpUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStartRampUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStartRampUpUpnpOrgDimming1Cpp::SyncStartRampUpUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncStartRampUpUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampUp(aAsync);
}


class SyncStartRampDownUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStartRampDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStartRampDownUpnpOrgDimming1Cpp::SyncStartRampDownUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncStartRampDownUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampDown(aAsync);
}


class SyncStopRampUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStopRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStopRampUpnpOrgDimming1Cpp::SyncStopRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncStopRampUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopRamp(aAsync);
}


class SyncStartRampToLevelUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncStartRampToLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncStartRampToLevelUpnpOrgDimming1Cpp::SyncStartRampToLevelUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncStartRampToLevelUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampToLevel(aAsync);
}


class SyncSetStepDeltaUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncSetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetStepDeltaUpnpOrgDimming1Cpp::SyncSetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncSetStepDeltaUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStepDelta(aAsync);
}


class SyncGetStepDeltaUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretStepDelta);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretStepDelta;
};

SyncGetStepDeltaUpnpOrgDimming1Cpp::SyncGetStepDeltaUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretStepDelta)
    : iService(aService)
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
    SyncSetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncSetRampRateUpnpOrgDimming1Cpp::SyncSetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncSetRampRateUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRampRate(aAsync);
}


class SyncGetRampRateUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretRampRate);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretRampRate;
};

SyncGetRampRateUpnpOrgDimming1Cpp::SyncGetRampRateUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretRampRate)
    : iService(aService)
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
    SyncPauseRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncPauseRampUpnpOrgDimming1Cpp::SyncPauseRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncPauseRampUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPauseRamp(aAsync);
}


class SyncResumeRampUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncResumeRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
};

SyncResumeRampUpnpOrgDimming1Cpp::SyncResumeRampUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService)
    : iService(aService)
{
}

void SyncResumeRampUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndResumeRamp(aAsync);
}


class SyncGetIsRampingUpnpOrgDimming1Cpp : public SyncProxyAction
{
public:
    SyncGetIsRampingUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, bool& aretIsRamping);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    bool& iretIsRamping;
};

SyncGetIsRampingUpnpOrgDimming1Cpp::SyncGetIsRampingUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, bool& aretIsRamping)
    : iService(aService)
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
    SyncGetRampPausedUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, bool& aretRampPaused);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    bool& iretRampPaused;
};

SyncGetRampPausedUpnpOrgDimming1Cpp::SyncGetRampPausedUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, bool& aretRampPaused)
    : iService(aService)
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
    SyncGetRampTimeUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretRampTime);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1Cpp& iService;
    uint32_t& iretRampTime;
};

SyncGetRampTimeUpnpOrgDimming1Cpp::SyncGetRampTimeUpnpOrgDimming1Cpp(CpProxyUpnpOrgDimming1Cpp& aService, uint32_t& aretRampTime)
    : iService(aService)
    , iretRampTime(aretRampTime)
{
}

void SyncGetRampTimeUpnpOrgDimming1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampTime(aAsync, iretRampTime);
}


CpProxyUpnpOrgDimming1Cpp::CpProxyUpnpOrgDimming1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("schemas-upnp-org", "Dimming", 1, aDevice.Device());
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
    param = new Zapp::ParameterUint("newRampTime", 0, 4294967295);
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
    param = new Zapp::ParameterUint("retRampTime", 0, 4294967295);
    iActionGetRampTime->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::LoadLevelStatusPropertyChanged);
    iLoadLevelStatus = new PropertyUint("LoadLevelStatus", functor);
    iService->AddProperty(iLoadLevelStatus);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::StepDeltaPropertyChanged);
    iStepDelta = new PropertyUint("StepDelta", functor);
    iService->AddProperty(iStepDelta);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::RampRatePropertyChanged);
    iRampRate = new PropertyUint("RampRate", functor);
    iService->AddProperty(iRampRate);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::IsRampingPropertyChanged);
    iIsRamping = new PropertyBool("IsRamping", functor);
    iService->AddProperty(iIsRamping);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1Cpp::RampPausedPropertyChanged);
    iRampPaused = new PropertyBool("RampPaused", functor);
    iService->AddProperty(iRampPaused);
}

CpProxyUpnpOrgDimming1Cpp::~CpProxyUpnpOrgDimming1Cpp()
{
    delete iService;
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndSetLoadLevelTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLoadLevelTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetLoadLevelTarget(IAsync& aAsync, uint32_t& aGetLoadlevelTarget)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetLoadLevelStatus(IAsync& aAsync, uint32_t& aretLoadlevelStatus)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndSetOnEffectLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetOnEffectLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
        Brn buf((const TByte*)anewOnEffect.c_str(), anewOnEffect.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndSetOnEffect(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetOnEffect"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetOnEffectParameters(IAsync& aAsync, std::string& aretOnEffect, uint32_t& aretOnEffectLevel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetOnEffectParameters"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndStepUp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StepUp"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndStepDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StepDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndStartRampUp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampUp"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndStartRampDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndStopRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StopRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndStartRampToLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampToLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndSetStepDelta(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStepDelta"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetStepDelta(IAsync& aAsync, uint32_t& aretStepDelta)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndSetRampRate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRampRate"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetRampRate(IAsync& aAsync, uint32_t& aretRampRate)
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

void CpProxyUpnpOrgDimming1Cpp::SyncPauseRamp()
{
    SyncPauseRampUpnpOrgDimming1Cpp sync(*this);
    BeginPauseRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1Cpp::BeginPauseRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPauseRamp, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndPauseRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PauseRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndResumeRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResumeRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetIsRamping(IAsync& aAsync, bool& aretIsRamping)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetRampPaused(IAsync& aAsync, bool& aretRampPaused)
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
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1Cpp::EndGetRampTime(IAsync& aAsync, uint32_t& aretRampTime)
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
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLoadLevelStatus = iLoadLevelStatus->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyStepDelta(uint32_t& aStepDelta) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStepDelta = iStepDelta->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyRampRate(uint32_t& aRampRate) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRampRate = iRampRate->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyIsRamping(bool& aIsRamping) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIsRamping = iIsRamping->Value();
}

void CpProxyUpnpOrgDimming1Cpp::PropertyRampPaused(bool& aRampPaused) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRampPaused = iRampPaused->Value();
}

void CpProxyUpnpOrgDimming1Cpp::LoadLevelStatusPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLoadLevelStatusChanged != NULL) {
        iLoadLevelStatusChanged();
    }
}

void CpProxyUpnpOrgDimming1Cpp::StepDeltaPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStepDeltaChanged != NULL) {
        iStepDeltaChanged();
    }
}

void CpProxyUpnpOrgDimming1Cpp::RampRatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRampRateChanged != NULL) {
        iRampRateChanged();
    }
}

void CpProxyUpnpOrgDimming1Cpp::IsRampingPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIsRampingChanged != NULL) {
        iIsRampingChanged();
    }
}

void CpProxyUpnpOrgDimming1Cpp::RampPausedPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRampPausedChanged != NULL) {
        iRampPausedChanged();
    }
}

