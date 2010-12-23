#include "DvUpnpOrgDimming1C.h"
#include "DvUpnpOrgDimming1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgDimming1C : public DvProviderUpnpOrgDimming1
{
public:
    DvProviderUpnpOrgDimming1C(DvDevice& aDevice);
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

DvProviderUpnpOrgDimming1C::DvProviderUpnpOrgDimming1C(DvDevice& aDevice)
    : DvProviderUpnpOrgDimming1(aDevice)
{
}

void DvProviderUpnpOrgDimming1C::EnableActionSetLoadLevelTarget(CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    iCallbackSetLoadLevelTarget = aCallback;
    iPtrSetLoadLevelTarget = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionSetLoadLevelTarget();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetLoadLevelTarget(CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    iCallbackGetLoadLevelTarget = aCallback;
    iPtrGetLoadLevelTarget = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetLoadLevelTarget();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetLoadLevelStatus(CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    iCallbackGetLoadLevelStatus = aCallback;
    iPtrGetLoadLevelStatus = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetLoadLevelStatus();
}

void DvProviderUpnpOrgDimming1C::EnableActionSetOnEffectLevel(CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    iCallbackSetOnEffectLevel = aCallback;
    iPtrSetOnEffectLevel = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionSetOnEffectLevel();
}

void DvProviderUpnpOrgDimming1C::EnableActionSetOnEffect(CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    iCallbackSetOnEffect = aCallback;
    iPtrSetOnEffect = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionSetOnEffect();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetOnEffectParameters(CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    iCallbackGetOnEffectParameters = aCallback;
    iPtrGetOnEffectParameters = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetOnEffectParameters();
}

void DvProviderUpnpOrgDimming1C::EnableActionStepUp(CallbackDimming1StepUp aCallback, void* aPtr)
{
    iCallbackStepUp = aCallback;
    iPtrStepUp = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionStepUp();
}

void DvProviderUpnpOrgDimming1C::EnableActionStepDown(CallbackDimming1StepDown aCallback, void* aPtr)
{
    iCallbackStepDown = aCallback;
    iPtrStepDown = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionStepDown();
}

void DvProviderUpnpOrgDimming1C::EnableActionStartRampUp(CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    iCallbackStartRampUp = aCallback;
    iPtrStartRampUp = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionStartRampUp();
}

void DvProviderUpnpOrgDimming1C::EnableActionStartRampDown(CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    iCallbackStartRampDown = aCallback;
    iPtrStartRampDown = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionStartRampDown();
}

void DvProviderUpnpOrgDimming1C::EnableActionStopRamp(CallbackDimming1StopRamp aCallback, void* aPtr)
{
    iCallbackStopRamp = aCallback;
    iPtrStopRamp = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionStopRamp();
}

void DvProviderUpnpOrgDimming1C::EnableActionStartRampToLevel(CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    iCallbackStartRampToLevel = aCallback;
    iPtrStartRampToLevel = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionStartRampToLevel();
}

void DvProviderUpnpOrgDimming1C::EnableActionSetStepDelta(CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    iCallbackSetStepDelta = aCallback;
    iPtrSetStepDelta = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionSetStepDelta();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetStepDelta(CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    iCallbackGetStepDelta = aCallback;
    iPtrGetStepDelta = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetStepDelta();
}

void DvProviderUpnpOrgDimming1C::EnableActionSetRampRate(CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    iCallbackSetRampRate = aCallback;
    iPtrSetRampRate = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionSetRampRate();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetRampRate(CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    iCallbackGetRampRate = aCallback;
    iPtrGetRampRate = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetRampRate();
}

void DvProviderUpnpOrgDimming1C::EnableActionPauseRamp(CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    iCallbackPauseRamp = aCallback;
    iPtrPauseRamp = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionPauseRamp();
}

void DvProviderUpnpOrgDimming1C::EnableActionResumeRamp(CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    iCallbackResumeRamp = aCallback;
    iPtrResumeRamp = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionResumeRamp();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetIsRamping(CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    iCallbackGetIsRamping = aCallback;
    iPtrGetIsRamping = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetIsRamping();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetRampPaused(CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    iCallbackGetRampPaused = aCallback;
    iPtrGetRampPaused = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetRampPaused();
}

void DvProviderUpnpOrgDimming1C::EnableActionGetRampTime(CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    iCallbackGetRampTime = aCallback;
    iPtrGetRampTime = aPtr;
    DvProviderUpnpOrgDimming1::EnableActionGetRampTime();
}

void DvProviderUpnpOrgDimming1C::SetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadlevelTarget)
{
    ASSERT(iCallbackSetLoadLevelTarget != NULL);
    if (0 != iCallbackSetLoadLevelTarget(iPtrSetLoadLevelTarget, aVersion, anewLoadlevelTarget)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::GetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aGetLoadlevelTarget)
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

void DvProviderUpnpOrgDimming1C::GetLoadLevelStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretLoadlevelStatus)
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

void DvProviderUpnpOrgDimming1C::SetOnEffectLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewOnEffectLevel)
{
    ASSERT(iCallbackSetOnEffectLevel != NULL);
    if (0 != iCallbackSetOnEffectLevel(iPtrSetOnEffectLevel, aVersion, anewOnEffectLevel)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::SetOnEffect(IInvocationResponse& aResponse, TUint aVersion, const Brx& anewOnEffect)
{
    ASSERT(iCallbackSetOnEffect != NULL);
    if (0 != iCallbackSetOnEffect(iPtrSetOnEffect, aVersion, (const char*)anewOnEffect.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::GetOnEffectParameters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aretOnEffect, IInvocationResponseUint& aretOnEffectLevel)
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

void DvProviderUpnpOrgDimming1C::StepUp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStepUp != NULL);
    if (0 != iCallbackStepUp(iPtrStepUp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::StepDown(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStepDown != NULL);
    if (0 != iCallbackStepDown(iPtrStepDown, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::StartRampUp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStartRampUp != NULL);
    if (0 != iCallbackStartRampUp(iPtrStartRampUp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::StartRampDown(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStartRampDown != NULL);
    if (0 != iCallbackStartRampDown(iPtrStartRampDown, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::StopRamp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackStopRamp != NULL);
    if (0 != iCallbackStopRamp(iPtrStopRamp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::StartRampToLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadLevelTarget, TUint anewRampTime)
{
    ASSERT(iCallbackStartRampToLevel != NULL);
    if (0 != iCallbackStartRampToLevel(iPtrStartRampToLevel, aVersion, anewLoadLevelTarget, anewRampTime)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::SetStepDelta(IInvocationResponse& aResponse, TUint aVersion, TUint anewStepDelta)
{
    ASSERT(iCallbackSetStepDelta != NULL);
    if (0 != iCallbackSetStepDelta(iPtrSetStepDelta, aVersion, anewStepDelta)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::GetStepDelta(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretStepDelta)
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

void DvProviderUpnpOrgDimming1C::SetRampRate(IInvocationResponse& aResponse, TUint aVersion, TUint anewRampRate)
{
    ASSERT(iCallbackSetRampRate != NULL);
    if (0 != iCallbackSetRampRate(iPtrSetRampRate, aVersion, anewRampRate)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::GetRampRate(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampRate)
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

void DvProviderUpnpOrgDimming1C::PauseRamp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackPauseRamp != NULL);
    if (0 != iCallbackPauseRamp(iPtrPauseRamp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::ResumeRamp(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackResumeRamp != NULL);
    if (0 != iCallbackResumeRamp(iPtrResumeRamp, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgDimming1C::GetIsRamping(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretIsRamping)
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

void DvProviderUpnpOrgDimming1C::GetRampPaused(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretRampPaused)
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

void DvProviderUpnpOrgDimming1C::GetRampTime(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampTime)
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



THandle DvProviderUpnpOrgDimming1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgDimming1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgDimming1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider);
}

void DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aProvider, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetLoadLevelTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aProvider, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetLoadLevelTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aProvider, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetLoadLevelStatus(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aProvider, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetOnEffectLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetOnEffect(THandle aProvider, CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetOnEffect(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aProvider, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetOnEffectParameters(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStepUp(THandle aProvider, CallbackDimming1StepUp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStepUp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStepDown(THandle aProvider, CallbackDimming1StepDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStepDown(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStartRampUp(THandle aProvider, CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampUp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStartRampDown(THandle aProvider, CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampDown(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStopRamp(THandle aProvider, CallbackDimming1StopRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStopRamp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(THandle aProvider, CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampToLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetStepDelta(THandle aProvider, CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetStepDelta(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetStepDelta(THandle aProvider, CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetStepDelta(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetRampRate(THandle aProvider, CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetRampRate(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetRampRate(THandle aProvider, CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampRate(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionPauseRamp(THandle aProvider, CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionPauseRamp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionResumeRamp(THandle aProvider, CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionResumeRamp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetIsRamping(THandle aProvider, CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetIsRamping(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetRampPaused(THandle aProvider, CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampPaused(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetRampTime(THandle aProvider, CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampTime(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyLoadLevelStatus(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyLoadLevelStatus(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgDimming1SetPropertyStepDelta(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyStepDelta(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyStepDelta(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyStepDelta(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgDimming1SetPropertyRampRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyRampRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyRampRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyRampRate(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgDimming1SetPropertyIsRamping(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyIsRamping((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyIsRamping(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyIsRamping(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderUpnpOrgDimming1SetPropertyRampPaused(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyRampPaused((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyRampPaused(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyRampPaused(val);
    *aValue = (val? 1 : 0);
}

