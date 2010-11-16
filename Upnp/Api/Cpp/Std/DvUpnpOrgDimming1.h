#ifndef HEADER_DVUPNPORGDIMMING1CPP
#define HEADER_DVUPNPORGDIMMING1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

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
class DvProviderUpnpOrgDimming1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgDimming1Cpp() {}
    bool SetPropertyLoadLevelStatus(uint32_t aValue);
    void GetPropertyLoadLevelStatus(uint32_t& aValue);
    bool SetPropertyStepDelta(uint32_t aValue);
    void GetPropertyStepDelta(uint32_t& aValue);
    bool SetPropertyRampRate(uint32_t aValue);
    void GetPropertyRampRate(uint32_t& aValue);
    bool SetPropertyIsRamping(bool aValue);
    void GetPropertyIsRamping(bool& aValue);
    bool SetPropertyRampPaused(bool aValue);
    void GetPropertyRampPaused(bool& aValue);
protected:
    DvProviderUpnpOrgDimming1Cpp(DvDeviceStd& aDevice);
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
    DvProviderUpnpOrgDimming1Cpp();
    void DoSetLoadLevelTarget(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetLoadLevelTarget(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetLoadLevelStatus(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetOnEffectLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetOnEffect(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetOnEffectParameters(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStepUp(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStepDown(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartRampUp(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartRampDown(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStopRamp(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartRampToLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStepDelta(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetStepDelta(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRampRate(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRampRate(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPauseRamp(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoResumeRamp(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetIsRamping(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRampPaused(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRampTime(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyLoadLevelStatus;
    PropertyUint* iPropertyStepDelta;
    PropertyUint* iPropertyRampRate;
    PropertyBool* iPropertyIsRamping;
    PropertyBool* iPropertyRampPaused;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGDIMMING1CPP

