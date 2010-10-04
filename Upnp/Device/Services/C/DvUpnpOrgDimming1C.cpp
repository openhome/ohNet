#include <C/DvUpnpOrgDimming1.h>
#include <Core/DvUpnpOrgDimming1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgDimming1C : public DvServiceUpnpOrgDimming1
{
public:
    DvServiceUpnpOrgDimming1C(DvDevice& aDevice);
    void EnableActionSetLoadLevelTarget(CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr);
    void EnableActionGetLoadLevelTarget(CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr);
    void EnableActionGetLoadLevelStatus(CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr);
    void EnableActionSetOnEffectLevel(CallbackDimming1SetOnEffectLevel aCallback, void* aPtr);
    void EnableActionSetOnEffect(CallbackDimming1SetOnEffect aCallback, void* aPtr);
    void EnableActionGetOnEffectParameters(CallbackDimming1GetOnEffectParameters aCallback, void* aPtr);
    void EnableActionStepUp(CallbackDimming1StepUp aCallback, void* aPtr);
    void EnableActionStepDown(CallbackDimming1StepDown aCallback, void* aPtr);
    void EnableActionStartRampUp(CallbackDimming1StartRampUp aCallback, void* aPtr);
    void EnableActionStartRampDown(CallbackDimming1StartRampDown aCallback, void* aPtr);
    void EnableActionStopRamp(CallbackDimming1StopRamp aCallback, void* aPtr);
    void EnableActionStartRampToLevel(CallbackDimming1StartRampToLevel aCallback, void* aPtr);
    void EnableActionSetStepDelta(CallbackDimming1SetStepDelta aCallback, void* aPtr);
    void EnableActionGetStepDelta(CallbackDimming1GetStepDelta aCallback, void* aPtr);
    void EnableActionSetRampRate(CallbackDimming1SetRampRate aCallback, void* aPtr);
    void EnableActionGetRampRate(CallbackDimming1GetRampRate aCallback, void* aPtr);
    void EnableActionPauseRamp(CallbackDimming1PauseRamp aCallback, void* aPtr);
    void EnableActionResumeRamp(CallbackDimming1ResumeRamp aCallback, void* aPtr);
    void EnableActionGetIsRamping(CallbackDimming1GetIsRamping aCallback, void* aPtr);
    void EnableActionGetRampPaused(CallbackDimming1GetRampPaused aCallback, void* aPtr);
    void EnableActionGetRampTime(CallbackDimming1GetRampTime aCallback, void* aPtr);
private:
    void SetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadlevelTarget);
    void GetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aGetLoadlevelTarget);
    void GetLoadLevelStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretLoadlevelStatus);
    void SetOnEffectLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewOnEffectLevel);
    void SetOnEffect(IInvocationResponse& aResponse, TUint aVersion, const Brx& anewOnEffect);
    void GetOnEffectParameters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aretOnEffect, IInvocationResponseUint& aretOnEffectLevel);
    void StepUp(IInvocationResponse& aResponse, TUint aVersion);
    void StepDown(IInvocationResponse& aResponse, TUint aVersion);
    void StartRampUp(IInvocationResponse& aResponse, TUint aVersion);
    void StartRampDown(IInvocationResponse& aResponse, TUint aVersion);
    void StopRamp(IInvocationResponse& aResponse, TUint aVersion);
    void StartRampToLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadLevelTarget, TUint anewRampTime);
    void SetStepDelta(IInvocationResponse& aResponse, TUint aVersion, TUint anewStepDelta);
    void GetStepDelta(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretStepDelta);
    void SetRampRate(IInvocationResponse& aResponse, TUint aVersion, TUint anewRampRate);
    void GetRampRate(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampRate);
    void PauseRamp(IInvocationResponse& aResponse, TUint aVersion);
    void ResumeRamp(IInvocationResponse& aResponse, TUint aVersion);
    void GetIsRamping(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretIsRamping);
    void GetRampPaused(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretRampPaused);
    void GetRampTime(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampTime);
private:
    CallbackDimming1SetLoadLevelTarget iCallbackSetLoadLevelTarget;
    void* iPtrSetLoadLevelTarget;
    CallbackDimming1GetLoadLevelTarget iCallbackGetLoadLevelTarget;
    void* iPtrGetLoadLevelTarget;
    CallbackDimming1GetLoadLevelStatus iCallbackGetLoadLevelStatus;
    void* iPtrGetLoadLevelStatus;
    CallbackDimming1SetOnEffectLevel iCallbackSetOnEffectLevel;
    void* iPtrSetOnEffectLevel;
    CallbackDimming1SetOnEffect iCallbackSetOnEffect;
    void* iPtrSetOnEffect;
    CallbackDimming1GetOnEffectParameters iCallbackGetOnEffectParameters;
    void* iPtrGetOnEffectParameters;
    CallbackDimming1StepUp iCallbackStepUp;
    void* iPtrStepUp;
    CallbackDimming1StepDown iCallbackStepDown;
    void* iPtrStepDown;
    CallbackDimming1StartRampUp iCallbackStartRampUp;
    void* iPtrStartRampUp;
    CallbackDimming1StartRampDown iCallbackStartRampDown;
    void* iPtrStartRampDown;
    CallbackDimming1StopRamp iCallbackStopRamp;
    void* iPtrStopRamp;
    CallbackDimming1StartRampToLevel iCallbackStartRampToLevel;
    void* iPtrStartRampToLevel;
    CallbackDimming1SetStepDelta iCallbackSetStepDelta;
    void* iPtrSetStepDelta;
    CallbackDimming1GetStepDelta iCallbackGetStepDelta;
    void* iPtrGetStepDelta;
    CallbackDimming1SetRampRate iCallbackSetRampRate;
    void* iPtrSetRampRate;
    CallbackDimming1GetRampRate iCallbackGetRampRate;
    void* iPtrGetRampRate;
    CallbackDimming1PauseRamp iCallbackPauseRamp;
    void* iPtrPauseRamp;
    CallbackDimming1ResumeRamp iCallbackResumeRamp;
    void* iPtrResumeRamp;
    CallbackDimming1GetIsRamping iCallbackGetIsRamping;
    void* iPtrGetIsRamping;
    CallbackDimming1GetRampPaused iCallbackGetRampPaused;
    void* iPtrGetRampPaused;
    CallbackDimming1GetRampTime iCallbackGetRampTime;
    void* iPtrGetRampTime;
};

DvServiceUpnpOrgDimming1C::DvServiceUpnpOrgDimming1C(DvDevice& aDevice)
    : DvServiceUpnpOrgDimming1(aDevice)
{
}

void DvServiceUpnpOrgDimming1C::EnableActionSetLoadLevelTarget(CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    iCallbackSetLoadLevelTarget = aCallback;
    iPtrSetLoadLevelTarget = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionSetLoadLevelTarget();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetLoadLevelTarget(CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    iCallbackGetLoadLevelTarget = aCallback;
    iPtrGetLoadLevelTarget = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetLoadLevelTarget();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetLoadLevelStatus(CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    iCallbackGetLoadLevelStatus = aCallback;
    iPtrGetLoadLevelStatus = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetLoadLevelStatus();
}

void DvServiceUpnpOrgDimming1C::EnableActionSetOnEffectLevel(CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    iCallbackSetOnEffectLevel = aCallback;
    iPtrSetOnEffectLevel = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionSetOnEffectLevel();
}

void DvServiceUpnpOrgDimming1C::EnableActionSetOnEffect(CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    iCallbackSetOnEffect = aCallback;
    iPtrSetOnEffect = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionSetOnEffect();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetOnEffectParameters(CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    iCallbackGetOnEffectParameters = aCallback;
    iPtrGetOnEffectParameters = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetOnEffectParameters();
}

void DvServiceUpnpOrgDimming1C::EnableActionStepUp(CallbackDimming1StepUp aCallback, void* aPtr)
{
    iCallbackStepUp = aCallback;
    iPtrStepUp = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionStepUp();
}

void DvServiceUpnpOrgDimming1C::EnableActionStepDown(CallbackDimming1StepDown aCallback, void* aPtr)
{
    iCallbackStepDown = aCallback;
    iPtrStepDown = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionStepDown();
}

void DvServiceUpnpOrgDimming1C::EnableActionStartRampUp(CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    iCallbackStartRampUp = aCallback;
    iPtrStartRampUp = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionStartRampUp();
}

void DvServiceUpnpOrgDimming1C::EnableActionStartRampDown(CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    iCallbackStartRampDown = aCallback;
    iPtrStartRampDown = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionStartRampDown();
}

void DvServiceUpnpOrgDimming1C::EnableActionStopRamp(CallbackDimming1StopRamp aCallback, void* aPtr)
{
    iCallbackStopRamp = aCallback;
    iPtrStopRamp = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionStopRamp();
}

void DvServiceUpnpOrgDimming1C::EnableActionStartRampToLevel(CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    iCallbackStartRampToLevel = aCallback;
    iPtrStartRampToLevel = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionStartRampToLevel();
}

void DvServiceUpnpOrgDimming1C::EnableActionSetStepDelta(CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    iCallbackSetStepDelta = aCallback;
    iPtrSetStepDelta = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionSetStepDelta();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetStepDelta(CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    iCallbackGetStepDelta = aCallback;
    iPtrGetStepDelta = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetStepDelta();
}

void DvServiceUpnpOrgDimming1C::EnableActionSetRampRate(CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    iCallbackSetRampRate = aCallback;
    iPtrSetRampRate = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionSetRampRate();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetRampRate(CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    iCallbackGetRampRate = aCallback;
    iPtrGetRampRate = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetRampRate();
}

void DvServiceUpnpOrgDimming1C::EnableActionPauseRamp(CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    iCallbackPauseRamp = aCallback;
    iPtrPauseRamp = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionPauseRamp();
}

void DvServiceUpnpOrgDimming1C::EnableActionResumeRamp(CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    iCallbackResumeRamp = aCallback;
    iPtrResumeRamp = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionResumeRamp();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetIsRamping(CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    iCallbackGetIsRamping = aCallback;
    iPtrGetIsRamping = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetIsRamping();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetRampPaused(CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    iCallbackGetRampPaused = aCallback;
    iPtrGetRampPaused = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetRampPaused();
}

void DvServiceUpnpOrgDimming1C::EnableActionGetRampTime(CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    iCallbackGetRampTime = aCallback;
    iPtrGetRampTime = aPtr;
    DvServiceUpnpOrgDimming1::EnableActionGetRampTime();
}

void DvServiceUpnpOrgDimming1C::SetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadlevelTarget)
{
    ASSERT(iCallbackSetLoadLevelTarget != NULL);
    if (0 != iCallbackSetLoadLevelTarget(iPtrSetLoadLevelTarget, aVersion, anewLoadlevelTarget)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aGetLoadlevelTarget)
{
    uint32_t GetLoadlevelTarget;
    ASSERT(iCallbackGetLoadLevelTarget != NULL);
    if (0 != iCallbackGetLoadLevelTarget(iPtrGetLoadLevelTarget, aVersion, &GetLoadlevelTarget)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aGetLoadlevelTarget.Write(GetLoadlevelTarget);
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetLoadLevelStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretLoadlevelStatus)
{
    uint32_t retLoadlevelStatus;
    ASSERT(iCallbackGetLoadLevelStatus != NULL);
    if (0 != iCallbackGetLoadLevelStatus(iPtrGetLoadLevelStatus, aVersion, &retLoadlevelStatus)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aretLoadlevelStatus.Write(retLoadlevelStatus);
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::SetOnEffectLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewOnEffectLevel)
{
    ASSERT(iCallbackSetOnEffectLevel != NULL);
    if (0 != iCallbackSetOnEffectLevel(iPtrSetOnEffectLevel, aVersion, anewOnEffectLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::SetOnEffect(IInvocationResponse& aResponse, TUint aVersion, const Brx& anewOnEffect)
{
    ASSERT(iCallbackSetOnEffect != NULL);
    if (0 != iCallbackSetOnEffect(iPtrSetOnEffect, aVersion, (const char*)anewOnEffect.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetOnEffectParameters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aretOnEffect, IInvocationResponseUint& aretOnEffectLevel)
{
    char* retOnEffect;
    uint32_t retOnEffectLevel;
    ASSERT(iCallbackGetOnEffectParameters != NULL);
    if (0 != iCallbackGetOnEffectParameters(iPtrGetOnEffectParameters, aVersion, &retOnEffect, &retOnEffectLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufretOnEffect((const TChar*)retOnEffect);
    ZappFreeExternal(retOnEffect);
    aretOnEffect.Write(bufretOnEffect);
    aretOnEffect.WriteFlush();
    aretOnEffectLevel.Write(retOnEffectLevel);
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::StepUp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStepUp != NULL);
    if (0 != iCallbackStepUp(iPtrStepUp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::StepDown(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStepDown != NULL);
    if (0 != iCallbackStepDown(iPtrStepDown, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::StartRampUp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStartRampUp != NULL);
    if (0 != iCallbackStartRampUp(iPtrStartRampUp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::StartRampDown(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStartRampDown != NULL);
    if (0 != iCallbackStartRampDown(iPtrStartRampDown, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::StopRamp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStopRamp != NULL);
    if (0 != iCallbackStopRamp(iPtrStopRamp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::StartRampToLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadLevelTarget, TUint anewRampTime)
{
    ASSERT(iCallbackStartRampToLevel != NULL);
    if (0 != iCallbackStartRampToLevel(iPtrStartRampToLevel, aVersion, anewLoadLevelTarget, anewRampTime)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::SetStepDelta(IInvocationResponse& aResponse, TUint aVersion, TUint anewStepDelta)
{
    ASSERT(iCallbackSetStepDelta != NULL);
    if (0 != iCallbackSetStepDelta(iPtrSetStepDelta, aVersion, anewStepDelta)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetStepDelta(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretStepDelta)
{
    uint32_t retStepDelta;
    ASSERT(iCallbackGetStepDelta != NULL);
    if (0 != iCallbackGetStepDelta(iPtrGetStepDelta, aVersion, &retStepDelta)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aretStepDelta.Write(retStepDelta);
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::SetRampRate(IInvocationResponse& aResponse, TUint aVersion, TUint anewRampRate)
{
    ASSERT(iCallbackSetRampRate != NULL);
    if (0 != iCallbackSetRampRate(iPtrSetRampRate, aVersion, anewRampRate)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetRampRate(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampRate)
{
    uint32_t retRampRate;
    ASSERT(iCallbackGetRampRate != NULL);
    if (0 != iCallbackGetRampRate(iPtrGetRampRate, aVersion, &retRampRate)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aretRampRate.Write(retRampRate);
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::PauseRamp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPauseRamp != NULL);
    if (0 != iCallbackPauseRamp(iPtrPauseRamp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::ResumeRamp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackResumeRamp != NULL);
    if (0 != iCallbackResumeRamp(iPtrResumeRamp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetIsRamping(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretIsRamping)
{
    uint32_t retIsRamping;
    ASSERT(iCallbackGetIsRamping != NULL);
    if (0 != iCallbackGetIsRamping(iPtrGetIsRamping, aVersion, &retIsRamping)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aretIsRamping.Write((retIsRamping!=0));
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetRampPaused(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretRampPaused)
{
    uint32_t retRampPaused;
    ASSERT(iCallbackGetRampPaused != NULL);
    if (0 != iCallbackGetRampPaused(iPtrGetRampPaused, aVersion, &retRampPaused)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aretRampPaused.Write((retRampPaused!=0));
    aResponse.End();
}

void DvServiceUpnpOrgDimming1C::GetRampTime(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampTime)
{
    uint32_t retRampTime;
    ASSERT(iCallbackGetRampTime != NULL);
    if (0 != iCallbackGetRampTime(iPtrGetRampTime, aVersion, &retRampTime)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aretRampTime.Write(retRampTime);
    aResponse.End();
}



THandle DvServiceUpnpOrgDimming1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgDimming1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgDimming1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService);
}

void DvServiceUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aService, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionSetLoadLevelTarget(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aService, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetLoadLevelTarget(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aService, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetLoadLevelStatus(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aService, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionSetOnEffectLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionSetOnEffect(THandle aService, CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionSetOnEffect(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aService, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetOnEffectParameters(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionStepUp(THandle aService, CallbackDimming1StepUp aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionStepUp(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionStepDown(THandle aService, CallbackDimming1StepDown aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionStepDown(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionStartRampUp(THandle aService, CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionStartRampUp(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionStartRampDown(THandle aService, CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionStartRampDown(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionStopRamp(THandle aService, CallbackDimming1StopRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionStopRamp(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionStartRampToLevel(THandle aService, CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionStartRampToLevel(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionSetStepDelta(THandle aService, CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionSetStepDelta(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetStepDelta(THandle aService, CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetStepDelta(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionSetRampRate(THandle aService, CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionSetRampRate(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetRampRate(THandle aService, CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetRampRate(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionPauseRamp(THandle aService, CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionPauseRamp(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionResumeRamp(THandle aService, CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionResumeRamp(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetIsRamping(THandle aService, CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetIsRamping(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetRampPaused(THandle aService, CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetRampPaused(aCallback, aPtr);
}

void DvServiceUpnpOrgDimming1EnableActionGetRampTime(THandle aService, CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->EnableActionGetRampTime(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->SetPropertyLoadLevelStatus(aValue);
    return 0;
}

void DvServiceUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->GetPropertyLoadLevelStatus(val);
    *aValue = val;
}

int32_t DvServiceUpnpOrgDimming1SetPropertyStepDelta(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->SetPropertyStepDelta(aValue);
    return 0;
}

void DvServiceUpnpOrgDimming1GetPropertyStepDelta(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->GetPropertyStepDelta(val);
    *aValue = val;
}

int32_t DvServiceUpnpOrgDimming1SetPropertyRampRate(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->SetPropertyRampRate(aValue);
    return 0;
}

void DvServiceUpnpOrgDimming1GetPropertyRampRate(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->GetPropertyRampRate(val);
    *aValue = val;
}

int32_t DvServiceUpnpOrgDimming1SetPropertyIsRamping(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->SetPropertyIsRamping((aValue!=0));
    return 0;
}

void DvServiceUpnpOrgDimming1GetPropertyIsRamping(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->GetPropertyIsRamping(val);
    *aValue = (val? 1 : 0);
}

int32_t DvServiceUpnpOrgDimming1SetPropertyRampPaused(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->SetPropertyRampPaused((aValue!=0));
    return 0;
}

void DvServiceUpnpOrgDimming1GetPropertyRampPaused(THandle aService, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvServiceUpnpOrgDimming1C*>(aService)->GetPropertyRampPaused(val);
    *aValue = (val? 1 : 0);
}

