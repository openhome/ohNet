#ifndef HEADER_DVUPNPORGDIMMING1
#define HEADER_DVUPNPORGDIMMING1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:Dimming:1
 */
class DvProviderUpnpOrgDimming1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgDimming1() {}
    TBool SetPropertyLoadLevelStatus(TUint aValue);
    void GetPropertyLoadLevelStatus(TUint& aValue);
    TBool SetPropertyStepDelta(TUint aValue);
    void GetPropertyStepDelta(TUint& aValue);
    TBool SetPropertyRampRate(TUint aValue);
    void GetPropertyRampRate(TUint& aValue);
    TBool SetPropertyIsRamping(TBool aValue);
    void GetPropertyIsRamping(TBool& aValue);
    TBool SetPropertyRampPaused(TBool aValue);
    void GetPropertyRampPaused(TBool& aValue);
protected:
    DvProviderUpnpOrgDimming1(DvDevice& aDevice);
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
    DvProviderUpnpOrgDimming1();
    void DoSetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLoadLevelStatus(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetOnEffectLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetOnEffect(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetOnEffectParameters(IDviInvocation& aInvocation, TUint aVersion);
    void DoStepUp(IDviInvocation& aInvocation, TUint aVersion);
    void DoStepDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartRampUp(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartRampDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoStopRamp(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartRampToLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStepDelta(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStepDelta(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRampRate(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRampRate(IDviInvocation& aInvocation, TUint aVersion);
    void DoPauseRamp(IDviInvocation& aInvocation, TUint aVersion);
    void DoResumeRamp(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetIsRamping(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRampPaused(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRampTime(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyLoadLevelStatus;
    PropertyUint* iPropertyStepDelta;
    PropertyUint* iPropertyRampRate;
    PropertyBool* iPropertyIsRamping;
    PropertyBool* iPropertyRampPaused;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGDIMMING1

