#ifndef HEADER_DVUPNPORGDIMMING1
#define HEADER_DVUPNPORGDIMMING1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:Dimming:1
 */
class DvServiceUpnpOrgDimming1 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgDimming1() {}
    void SetPropertyLoadLevelStatus(TUint aValue);
    void GetPropertyLoadLevelStatus(TUint& aValue);
    void SetPropertyStepDelta(TUint aValue);
    void GetPropertyStepDelta(TUint& aValue);
    void SetPropertyRampRate(TUint aValue);
    void GetPropertyRampRate(TUint& aValue);
    void SetPropertyIsRamping(TBool aValue);
    void GetPropertyIsRamping(TBool& aValue);
    void SetPropertyRampPaused(TBool aValue);
    void GetPropertyRampPaused(TBool& aValue);
protected:
    DvServiceUpnpOrgDimming1(DvDevice& aDevice);
    void EnableActionSetLoadLevelTarget();
    void EnableActionGetLoadLevelTarget();
    void EnableActionGetLoadLevelStatus();
    void EnableActionSetOnEffectLevel();
    void EnableActionSetOnEffect();
    void EnableActionGetOnEffectParameters();
    void EnableActionStepUp();
    void EnableActionStepDown();
    void EnableActionStartRampUp();
    void EnableActionStartRampDown();
    void EnableActionStopRamp();
    void EnableActionStartRampToLevel();
    void EnableActionSetStepDelta();
    void EnableActionGetStepDelta();
    void EnableActionSetRampRate();
    void EnableActionGetRampRate();
    void EnableActionPauseRamp();
    void EnableActionResumeRamp();
    void EnableActionGetIsRamping();
    void EnableActionGetRampPaused();
    void EnableActionGetRampTime();
private:
    virtual void SetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadlevelTarget);
    virtual void GetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aGetLoadlevelTarget);
    virtual void GetLoadLevelStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretLoadlevelStatus);
    virtual void SetOnEffectLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewOnEffectLevel);
    virtual void SetOnEffect(IInvocationResponse& aResponse, TUint aVersion, const Brx& anewOnEffect);
    virtual void GetOnEffectParameters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aretOnEffect, IInvocationResponseUint& aretOnEffectLevel);
    virtual void StepUp(IInvocationResponse& aResponse, TUint aVersion);
    virtual void StepDown(IInvocationResponse& aResponse, TUint aVersion);
    virtual void StartRampUp(IInvocationResponse& aResponse, TUint aVersion);
    virtual void StartRampDown(IInvocationResponse& aResponse, TUint aVersion);
    virtual void StopRamp(IInvocationResponse& aResponse, TUint aVersion);
    virtual void StartRampToLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadLevelTarget, TUint anewRampTime);
    virtual void SetStepDelta(IInvocationResponse& aResponse, TUint aVersion, TUint anewStepDelta);
    virtual void GetStepDelta(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretStepDelta);
    virtual void SetRampRate(IInvocationResponse& aResponse, TUint aVersion, TUint anewRampRate);
    virtual void GetRampRate(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampRate);
    virtual void PauseRamp(IInvocationResponse& aResponse, TUint aVersion);
    virtual void ResumeRamp(IInvocationResponse& aResponse, TUint aVersion);
    virtual void GetIsRamping(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretIsRamping);
    virtual void GetRampPaused(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretRampPaused);
    virtual void GetRampTime(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampTime);
private:
    DvServiceUpnpOrgDimming1();
    void DoSetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetLoadLevelStatus(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetOnEffectLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetOnEffect(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetOnEffectParameters(IDvInvocation& aInvocation, TUint aVersion);
    void DoStepUp(IDvInvocation& aInvocation, TUint aVersion);
    void DoStepDown(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartRampUp(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartRampDown(IDvInvocation& aInvocation, TUint aVersion);
    void DoStopRamp(IDvInvocation& aInvocation, TUint aVersion);
    void DoStartRampToLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStepDelta(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetStepDelta(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRampRate(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRampRate(IDvInvocation& aInvocation, TUint aVersion);
    void DoPauseRamp(IDvInvocation& aInvocation, TUint aVersion);
    void DoResumeRamp(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetIsRamping(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRampPaused(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRampTime(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyLoadLevelStatus;
    PropertyUint* iPropertyStepDelta;
    PropertyUint* iPropertyRampRate;
    PropertyBool* iPropertyIsRamping;
    PropertyBool* iPropertyRampPaused;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGDIMMING1

