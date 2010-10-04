#include <Core/CpUpnpOrgDimming1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncSetLoadLevelTargetUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncSetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncSetLoadLevelTargetUpnpOrgDimming1::SyncSetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncSetLoadLevelTargetUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetLoadLevelTarget(aAsync);
}


class SyncGetLoadLevelTargetUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aGetLoadlevelTarget);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TUint& iGetLoadlevelTarget;
};

SyncGetLoadLevelTargetUpnpOrgDimming1::SyncGetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aGetLoadlevelTarget)
    : iService(aService)
    , iGetLoadlevelTarget(aGetLoadlevelTarget)
{
}

void SyncGetLoadLevelTargetUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoadLevelTarget(aAsync, iGetLoadlevelTarget);
}


class SyncGetLoadLevelStatusUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetLoadLevelStatusUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretLoadlevelStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TUint& iretLoadlevelStatus;
};

SyncGetLoadLevelStatusUpnpOrgDimming1::SyncGetLoadLevelStatusUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretLoadlevelStatus)
    : iService(aService)
    , iretLoadlevelStatus(aretLoadlevelStatus)
{
}

void SyncGetLoadLevelStatusUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetLoadLevelStatus(aAsync, iretLoadlevelStatus);
}


class SyncSetOnEffectLevelUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncSetOnEffectLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncSetOnEffectLevelUpnpOrgDimming1::SyncSetOnEffectLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncSetOnEffectLevelUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffectLevel(aAsync);
}


class SyncSetOnEffectUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncSetOnEffectUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncSetOnEffectUpnpOrgDimming1::SyncSetOnEffectUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncSetOnEffectUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetOnEffect(aAsync);
}


class SyncGetOnEffectParametersUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetOnEffectParametersUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, Brh& aretOnEffect, TUint& aretOnEffectLevel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    Brh& iretOnEffect;
    TUint& iretOnEffectLevel;
};

SyncGetOnEffectParametersUpnpOrgDimming1::SyncGetOnEffectParametersUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, Brh& aretOnEffect, TUint& aretOnEffectLevel)
    : iService(aService)
    , iretOnEffect(aretOnEffect)
    , iretOnEffectLevel(aretOnEffectLevel)
{
}

void SyncGetOnEffectParametersUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetOnEffectParameters(aAsync, iretOnEffect, iretOnEffectLevel);
}


class SyncStepUpUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncStepUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncStepUpUpnpOrgDimming1::SyncStepUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncStepUpUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepUp(aAsync);
}


class SyncStepDownUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncStepDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncStepDownUpnpOrgDimming1::SyncStepDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncStepDownUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStepDown(aAsync);
}


class SyncStartRampUpUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncStartRampUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncStartRampUpUpnpOrgDimming1::SyncStartRampUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncStartRampUpUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampUp(aAsync);
}


class SyncStartRampDownUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncStartRampDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncStartRampDownUpnpOrgDimming1::SyncStartRampDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncStartRampDownUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampDown(aAsync);
}


class SyncStopRampUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncStopRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncStopRampUpnpOrgDimming1::SyncStopRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncStopRampUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStopRamp(aAsync);
}


class SyncStartRampToLevelUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncStartRampToLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncStartRampToLevelUpnpOrgDimming1::SyncStartRampToLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncStartRampToLevelUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartRampToLevel(aAsync);
}


class SyncSetStepDeltaUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncSetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncSetStepDeltaUpnpOrgDimming1::SyncSetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncSetStepDeltaUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStepDelta(aAsync);
}


class SyncGetStepDeltaUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretStepDelta);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TUint& iretStepDelta;
};

SyncGetStepDeltaUpnpOrgDimming1::SyncGetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretStepDelta)
    : iService(aService)
    , iretStepDelta(aretStepDelta)
{
}

void SyncGetStepDeltaUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetStepDelta(aAsync, iretStepDelta);
}


class SyncSetRampRateUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncSetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncSetRampRateUpnpOrgDimming1::SyncSetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncSetRampRateUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRampRate(aAsync);
}


class SyncGetRampRateUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretRampRate);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TUint& iretRampRate;
};

SyncGetRampRateUpnpOrgDimming1::SyncGetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretRampRate)
    : iService(aService)
    , iretRampRate(aretRampRate)
{
}

void SyncGetRampRateUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampRate(aAsync, iretRampRate);
}


class SyncPauseRampUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncPauseRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncPauseRampUpnpOrgDimming1::SyncPauseRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncPauseRampUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPauseRamp(aAsync);
}


class SyncResumeRampUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncResumeRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
};

SyncResumeRampUpnpOrgDimming1::SyncResumeRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService)
    : iService(aService)
{
}

void SyncResumeRampUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndResumeRamp(aAsync);
}


class SyncGetIsRampingUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetIsRampingUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TBool& aretIsRamping);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TBool& iretIsRamping;
};

SyncGetIsRampingUpnpOrgDimming1::SyncGetIsRampingUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TBool& aretIsRamping)
    : iService(aService)
    , iretIsRamping(aretIsRamping)
{
}

void SyncGetIsRampingUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetIsRamping(aAsync, iretIsRamping);
}


class SyncGetRampPausedUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetRampPausedUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TBool& aretRampPaused);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TBool& iretRampPaused;
};

SyncGetRampPausedUpnpOrgDimming1::SyncGetRampPausedUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TBool& aretRampPaused)
    : iService(aService)
    , iretRampPaused(aretRampPaused)
{
}

void SyncGetRampPausedUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampPaused(aAsync, iretRampPaused);
}


class SyncGetRampTimeUpnpOrgDimming1 : public SyncProxyAction
{
public:
    SyncGetRampTimeUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretRampTime);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyUpnpOrgDimming1& iService;
    TUint& iretRampTime;
};

SyncGetRampTimeUpnpOrgDimming1::SyncGetRampTimeUpnpOrgDimming1(CpProxyUpnpOrgDimming1& aService, TUint& aretRampTime)
    : iService(aService)
    , iretRampTime(aretRampTime)
{
}

void SyncGetRampTimeUpnpOrgDimming1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRampTime(aAsync, iretRampTime);
}


CpProxyUpnpOrgDimming1::CpProxyUpnpOrgDimming1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1::LoadLevelStatusPropertyChanged);
    iLoadLevelStatus = new PropertyUint("LoadLevelStatus", functor);
    iService->AddProperty(iLoadLevelStatus);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1::StepDeltaPropertyChanged);
    iStepDelta = new PropertyUint("StepDelta", functor);
    iService->AddProperty(iStepDelta);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1::RampRatePropertyChanged);
    iRampRate = new PropertyUint("RampRate", functor);
    iService->AddProperty(iRampRate);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1::IsRampingPropertyChanged);
    iIsRamping = new PropertyBool("IsRamping", functor);
    iService->AddProperty(iIsRamping);
    functor = MakeFunctor(*this, &CpProxyUpnpOrgDimming1::RampPausedPropertyChanged);
    iRampPaused = new PropertyBool("RampPaused", functor);
    iService->AddProperty(iRampPaused);
}

CpProxyUpnpOrgDimming1::~CpProxyUpnpOrgDimming1()
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

void CpProxyUpnpOrgDimming1::SyncSetLoadLevelTarget(TUint anewLoadlevelTarget)
{
    SyncSetLoadLevelTargetUpnpOrgDimming1 sync(*this);
    BeginSetLoadLevelTarget(anewLoadlevelTarget, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginSetLoadLevelTarget(TUint anewLoadlevelTarget, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetLoadLevelTarget, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetLoadLevelTarget->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewLoadlevelTarget));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndSetLoadLevelTarget(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetLoadLevelTarget"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncGetLoadLevelTarget(TUint& aGetLoadlevelTarget)
{
    SyncGetLoadLevelTargetUpnpOrgDimming1 sync(*this, aGetLoadlevelTarget);
    BeginGetLoadLevelTarget(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetLoadLevelTarget(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoadLevelTarget, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoadLevelTarget->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetLoadLevelTarget(IAsync& aAsync, TUint& aGetLoadlevelTarget)
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

void CpProxyUpnpOrgDimming1::SyncGetLoadLevelStatus(TUint& aretLoadlevelStatus)
{
    SyncGetLoadLevelStatusUpnpOrgDimming1 sync(*this, aretLoadlevelStatus);
    BeginGetLoadLevelStatus(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetLoadLevelStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetLoadLevelStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetLoadLevelStatus->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetLoadLevelStatus(IAsync& aAsync, TUint& aretLoadlevelStatus)
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

void CpProxyUpnpOrgDimming1::SyncSetOnEffectLevel(TUint anewOnEffectLevel)
{
    SyncSetOnEffectLevelUpnpOrgDimming1 sync(*this);
    BeginSetOnEffectLevel(anewOnEffectLevel, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginSetOnEffectLevel(TUint anewOnEffectLevel, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetOnEffectLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetOnEffectLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewOnEffectLevel));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndSetOnEffectLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetOnEffectLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncSetOnEffect(const Brx& anewOnEffect)
{
    SyncSetOnEffectUpnpOrgDimming1 sync(*this);
    BeginSetOnEffect(anewOnEffect, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginSetOnEffect(const Brx& anewOnEffect, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetOnEffect, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetOnEffect->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], anewOnEffect));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndSetOnEffect(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetOnEffect"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncGetOnEffectParameters(Brh& aretOnEffect, TUint& aretOnEffectLevel)
{
    SyncGetOnEffectParametersUpnpOrgDimming1 sync(*this, aretOnEffect, aretOnEffectLevel);
    BeginGetOnEffectParameters(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetOnEffectParameters(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetOnEffectParameters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetOnEffectParameters->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetOnEffectParameters(IAsync& aAsync, Brh& aretOnEffect, TUint& aretOnEffectLevel)
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

void CpProxyUpnpOrgDimming1::SyncStepUp()
{
    SyncStepUpUpnpOrgDimming1 sync(*this);
    BeginStepUp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginStepUp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStepUp, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndStepUp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StepUp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncStepDown()
{
    SyncStepDownUpnpOrgDimming1 sync(*this);
    BeginStepDown(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginStepDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStepDown, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndStepDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StepDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncStartRampUp()
{
    SyncStartRampUpUpnpOrgDimming1 sync(*this);
    BeginStartRampUp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginStartRampUp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartRampUp, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndStartRampUp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampUp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncStartRampDown()
{
    SyncStartRampDownUpnpOrgDimming1 sync(*this);
    BeginStartRampDown(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginStartRampDown(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartRampDown, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndStartRampDown(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampDown"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncStopRamp()
{
    SyncStopRampUpnpOrgDimming1 sync(*this);
    BeginStopRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginStopRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStopRamp, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndStopRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StopRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncStartRampToLevel(TUint anewLoadLevelTarget, TUint anewRampTime)
{
    SyncStartRampToLevelUpnpOrgDimming1 sync(*this);
    BeginStartRampToLevel(anewLoadLevelTarget, anewRampTime, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginStartRampToLevel(TUint anewLoadLevelTarget, TUint anewRampTime, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartRampToLevel, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionStartRampToLevel->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewLoadLevelTarget));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewRampTime));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndStartRampToLevel(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartRampToLevel"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncSetStepDelta(TUint anewStepDelta)
{
    SyncSetStepDeltaUpnpOrgDimming1 sync(*this);
    BeginSetStepDelta(anewStepDelta, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginSetStepDelta(TUint anewStepDelta, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStepDelta, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStepDelta->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewStepDelta));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndSetStepDelta(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStepDelta"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncGetStepDelta(TUint& aretStepDelta)
{
    SyncGetStepDeltaUpnpOrgDimming1 sync(*this, aretStepDelta);
    BeginGetStepDelta(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetStepDelta(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetStepDelta, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetStepDelta->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetStepDelta(IAsync& aAsync, TUint& aretStepDelta)
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

void CpProxyUpnpOrgDimming1::SyncSetRampRate(TUint anewRampRate)
{
    SyncSetRampRateUpnpOrgDimming1 sync(*this);
    BeginSetRampRate(anewRampRate, sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginSetRampRate(TUint anewRampRate, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRampRate, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRampRate->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], anewRampRate));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndSetRampRate(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRampRate"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncGetRampRate(TUint& aretRampRate)
{
    SyncGetRampRateUpnpOrgDimming1 sync(*this, aretRampRate);
    BeginGetRampRate(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetRampRate(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRampRate, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampRate->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetRampRate(IAsync& aAsync, TUint& aretRampRate)
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

void CpProxyUpnpOrgDimming1::SyncPauseRamp()
{
    SyncPauseRampUpnpOrgDimming1 sync(*this);
    BeginPauseRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginPauseRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPauseRamp, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndPauseRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PauseRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncResumeRamp()
{
    SyncResumeRampUpnpOrgDimming1 sync(*this);
    BeginResumeRamp(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginResumeRamp(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionResumeRamp, aFunctor);
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndResumeRamp(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ResumeRamp"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyUpnpOrgDimming1::SyncGetIsRamping(TBool& aretIsRamping)
{
    SyncGetIsRampingUpnpOrgDimming1 sync(*this, aretIsRamping);
    BeginGetIsRamping(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetIsRamping(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetIsRamping, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetIsRamping->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetIsRamping(IAsync& aAsync, TBool& aretIsRamping)
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

void CpProxyUpnpOrgDimming1::SyncGetRampPaused(TBool& aretRampPaused)
{
    SyncGetRampPausedUpnpOrgDimming1 sync(*this, aretRampPaused);
    BeginGetRampPaused(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetRampPaused(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRampPaused, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampPaused->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetRampPaused(IAsync& aAsync, TBool& aretRampPaused)
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

void CpProxyUpnpOrgDimming1::SyncGetRampTime(TUint& aretRampTime)
{
    SyncGetRampTimeUpnpOrgDimming1 sync(*this, aretRampTime);
    BeginGetRampTime(sync.Functor());
    sync.Wait();
}

void CpProxyUpnpOrgDimming1::BeginGetRampTime(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRampTime, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRampTime->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyUpnpOrgDimming1::EndGetRampTime(IAsync& aAsync, TUint& aretRampTime)
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

void CpProxyUpnpOrgDimming1::SetPropertyLoadLevelStatusChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLoadLevelStatusChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1::SetPropertyStepDeltaChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStepDeltaChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1::SetPropertyRampRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRampRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1::SetPropertyIsRampingChanged(Functor& aFunctor)
{
    iLock->Wait();
    iIsRampingChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1::SetPropertyRampPausedChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRampPausedChanged = aFunctor;
    iLock->Signal();
}

void CpProxyUpnpOrgDimming1::PropertyLoadLevelStatus(TUint& aLoadLevelStatus) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLoadLevelStatus = iLoadLevelStatus->Value();
}

void CpProxyUpnpOrgDimming1::PropertyStepDelta(TUint& aStepDelta) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStepDelta = iStepDelta->Value();
}

void CpProxyUpnpOrgDimming1::PropertyRampRate(TUint& aRampRate) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRampRate = iRampRate->Value();
}

void CpProxyUpnpOrgDimming1::PropertyIsRamping(TBool& aIsRamping) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aIsRamping = iIsRamping->Value();
}

void CpProxyUpnpOrgDimming1::PropertyRampPaused(TBool& aRampPaused) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRampPaused = iRampPaused->Value();
}

void CpProxyUpnpOrgDimming1::LoadLevelStatusPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLoadLevelStatusChanged != NULL) {
        iLoadLevelStatusChanged();
    }
}

void CpProxyUpnpOrgDimming1::StepDeltaPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStepDeltaChanged != NULL) {
        iStepDeltaChanged();
    }
}

void CpProxyUpnpOrgDimming1::RampRatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRampRateChanged != NULL) {
        iRampRateChanged();
    }
}

void CpProxyUpnpOrgDimming1::IsRampingPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iIsRampingChanged != NULL) {
        iIsRampingChanged();
    }
}

void CpProxyUpnpOrgDimming1::RampPausedPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRampPausedChanged != NULL) {
        iRampPausedChanged();
    }
}

