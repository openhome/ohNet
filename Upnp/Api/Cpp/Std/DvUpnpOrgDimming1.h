#ifndef HEADER_DVUPNPORGDIMMING1CPP
#define HEADER_DVUPNPORGDIMMING1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:Dimming:1
 */
class DvServiceUpnpOrgDimming1Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgDimming1Cpp() {}
    void SetPropertyLoadLevelStatus(uint32_t aValue);
    void GetPropertyLoadLevelStatus(uint32_t& aValue);
    void SetPropertyStepDelta(uint32_t aValue);
    void GetPropertyStepDelta(uint32_t& aValue);
    void SetPropertyRampRate(uint32_t aValue);
    void GetPropertyRampRate(uint32_t& aValue);
    void SetPropertyIsRamping(bool aValue);
    void GetPropertyIsRamping(bool& aValue);
    void SetPropertyRampPaused(bool aValue);
    void GetPropertyRampPaused(bool& aValue);
protected:
    DvServiceUpnpOrgDimming1Cpp(DvDeviceStd& aDevice);
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
    virtual void SetLoadLevelTarget(uint32_t aVersion, uint32_t anewLoadlevelTarget);
    virtual void GetLoadLevelTarget(uint32_t aVersion, uint32_t& aGetLoadlevelTarget);
    virtual void GetLoadLevelStatus(uint32_t aVersion, uint32_t& aretLoadlevelStatus);
    virtual void SetOnEffectLevel(uint32_t aVersion, uint32_t anewOnEffectLevel);
    virtual void SetOnEffect(uint32_t aVersion, const std::string& anewOnEffect);
    virtual void GetOnEffectParameters(uint32_t aVersion, std::string& aretOnEffect, uint32_t& aretOnEffectLevel);
    virtual void StepUp(uint32_t aVersion);
    virtual void StepDown(uint32_t aVersion);
    virtual void StartRampUp(uint32_t aVersion);
    virtual void StartRampDown(uint32_t aVersion);
    virtual void StopRamp(uint32_t aVersion);
    virtual void StartRampToLevel(uint32_t aVersion, uint32_t anewLoadLevelTarget, uint32_t anewRampTime);
    virtual void SetStepDelta(uint32_t aVersion, uint32_t anewStepDelta);
    virtual void GetStepDelta(uint32_t aVersion, uint32_t& aretStepDelta);
    virtual void SetRampRate(uint32_t aVersion, uint32_t anewRampRate);
    virtual void GetRampRate(uint32_t aVersion, uint32_t& aretRampRate);
    virtual void PauseRamp(uint32_t aVersion);
    virtual void ResumeRamp(uint32_t aVersion);
    virtual void GetIsRamping(uint32_t aVersion, bool& aretIsRamping);
    virtual void GetRampPaused(uint32_t aVersion, bool& aretRampPaused);
    virtual void GetRampTime(uint32_t aVersion, uint32_t& aretRampTime);
private:
    DvServiceUpnpOrgDimming1Cpp();
    void DoSetLoadLevelTarget(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetLoadLevelTarget(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetLoadLevelStatus(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetOnEffectLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetOnEffect(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetOnEffectParameters(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStepUp(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStepDown(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartRampUp(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartRampDown(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStopRamp(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartRampToLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStepDelta(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetStepDelta(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRampRate(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRampRate(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPauseRamp(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoResumeRamp(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetIsRamping(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRampPaused(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRampTime(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyLoadLevelStatus;
    PropertyUint* iPropertyStepDelta;
    PropertyUint* iPropertyRampRate;
    PropertyBool* iPropertyIsRamping;
    PropertyBool* iPropertyRampPaused;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGDIMMING1CPP

