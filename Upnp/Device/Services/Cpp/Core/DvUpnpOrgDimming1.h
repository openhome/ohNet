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
 * Provider for the upnp.org:Dimming:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgDimming1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgDimming1() {}
    /**
     * Set the value of the LoadLevelStatus property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLoadLevelStatus(TUint aValue);
    /**
     * Get a copy of the value of the LoadLevelStatus property
     */
    void GetPropertyLoadLevelStatus(TUint& aValue);
    /**
     * Set the value of the StepDelta property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStepDelta(TUint aValue);
    /**
     * Get a copy of the value of the StepDelta property
     */
    void GetPropertyStepDelta(TUint& aValue);
    /**
     * Set the value of the RampRate property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyRampRate(TUint aValue);
    /**
     * Get a copy of the value of the RampRate property
     */
    void GetPropertyRampRate(TUint& aValue);
    /**
     * Set the value of the IsRamping property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyIsRamping(TBool aValue);
    /**
     * Get a copy of the value of the IsRamping property
     */
    void GetPropertyIsRamping(TBool& aValue);
    /**
     * Set the value of the RampPaused property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyRampPaused(TBool aValue);
    /**
     * Get a copy of the value of the RampPaused property
     */
    void GetPropertyRampPaused(TBool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgDimming1(DvDevice& aDevice);
    /**
     * Signal that the action SetLoadLevelTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetLoadLevelTarget must be overridden if this is called.
     */
    void EnableActionSetLoadLevelTarget();
    /**
     * Signal that the action GetLoadLevelTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetLoadLevelTarget must be overridden if this is called.
     */
    void EnableActionGetLoadLevelTarget();
    /**
     * Signal that the action GetLoadLevelStatus is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetLoadLevelStatus must be overridden if this is called.
     */
    void EnableActionGetLoadLevelStatus();
    /**
     * Signal that the action SetOnEffectLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetOnEffectLevel must be overridden if this is called.
     */
    void EnableActionSetOnEffectLevel();
    /**
     * Signal that the action SetOnEffect is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetOnEffect must be overridden if this is called.
     */
    void EnableActionSetOnEffect();
    /**
     * Signal that the action GetOnEffectParameters is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetOnEffectParameters must be overridden if this is called.
     */
    void EnableActionGetOnEffectParameters();
    /**
     * Signal that the action StepUp is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStepUp must be overridden if this is called.
     */
    void EnableActionStepUp();
    /**
     * Signal that the action StepDown is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStepDown must be overridden if this is called.
     */
    void EnableActionStepDown();
    /**
     * Signal that the action StartRampUp is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartRampUp must be overridden if this is called.
     */
    void EnableActionStartRampUp();
    /**
     * Signal that the action StartRampDown is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartRampDown must be overridden if this is called.
     */
    void EnableActionStartRampDown();
    /**
     * Signal that the action StopRamp is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStopRamp must be overridden if this is called.
     */
    void EnableActionStopRamp();
    /**
     * Signal that the action StartRampToLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartRampToLevel must be overridden if this is called.
     */
    void EnableActionStartRampToLevel();
    /**
     * Signal that the action SetStepDelta is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStepDelta must be overridden if this is called.
     */
    void EnableActionSetStepDelta();
    /**
     * Signal that the action GetStepDelta is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetStepDelta must be overridden if this is called.
     */
    void EnableActionGetStepDelta();
    /**
     * Signal that the action SetRampRate is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetRampRate must be overridden if this is called.
     */
    void EnableActionSetRampRate();
    /**
     * Signal that the action GetRampRate is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetRampRate must be overridden if this is called.
     */
    void EnableActionGetRampRate();
    /**
     * Signal that the action PauseRamp is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPauseRamp must be overridden if this is called.
     */
    void EnableActionPauseRamp();
    /**
     * Signal that the action ResumeRamp is supported.
     * The action's availability will be published in the device's service.xml.
     * DoResumeRamp must be overridden if this is called.
     */
    void EnableActionResumeRamp();
    /**
     * Signal that the action GetIsRamping is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetIsRamping must be overridden if this is called.
     */
    void EnableActionGetIsRamping();
    /**
     * Signal that the action GetRampPaused is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetRampPaused must be overridden if this is called.
     */
    void EnableActionGetRampPaused();
    /**
     * Signal that the action GetRampTime is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetRampTime must be overridden if this is called.
     */
    void EnableActionGetRampTime();
private:
    /**
     * SetLoadLevelTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetLoadLevelTarget action for the owning device.
     * Must be implemented iff EnableActionSetLoadLevelTarget was called.
     */
    virtual void SetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadlevelTarget);
    /**
     * GetLoadLevelTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLoadLevelTarget action for the owning device.
     * Must be implemented iff EnableActionGetLoadLevelTarget was called.
     */
    virtual void GetLoadLevelTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aGetLoadlevelTarget);
    /**
     * GetLoadLevelStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLoadLevelStatus action for the owning device.
     * Must be implemented iff EnableActionGetLoadLevelStatus was called.
     */
    virtual void GetLoadLevelStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretLoadlevelStatus);
    /**
     * SetOnEffectLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetOnEffectLevel action for the owning device.
     * Must be implemented iff EnableActionSetOnEffectLevel was called.
     */
    virtual void SetOnEffectLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewOnEffectLevel);
    /**
     * SetOnEffect action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetOnEffect action for the owning device.
     * Must be implemented iff EnableActionSetOnEffect was called.
     */
    virtual void SetOnEffect(IInvocationResponse& aResponse, TUint aVersion, const Brx& anewOnEffect);
    /**
     * GetOnEffectParameters action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetOnEffectParameters action for the owning device.
     * Must be implemented iff EnableActionGetOnEffectParameters was called.
     */
    virtual void GetOnEffectParameters(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aretOnEffect, IInvocationResponseUint& aretOnEffectLevel);
    /**
     * StepUp action.
     *
     * Will be called when the device stack receives an invocation of the
     * StepUp action for the owning device.
     * Must be implemented iff EnableActionStepUp was called.
     */
    virtual void StepUp(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * StepDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * StepDown action for the owning device.
     * Must be implemented iff EnableActionStepDown was called.
     */
    virtual void StepDown(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * StartRampUp action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartRampUp action for the owning device.
     * Must be implemented iff EnableActionStartRampUp was called.
     */
    virtual void StartRampUp(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * StartRampDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartRampDown action for the owning device.
     * Must be implemented iff EnableActionStartRampDown was called.
     */
    virtual void StartRampDown(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * StopRamp action.
     *
     * Will be called when the device stack receives an invocation of the
     * StopRamp action for the owning device.
     * Must be implemented iff EnableActionStopRamp was called.
     */
    virtual void StopRamp(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * StartRampToLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartRampToLevel action for the owning device.
     * Must be implemented iff EnableActionStartRampToLevel was called.
     */
    virtual void StartRampToLevel(IInvocationResponse& aResponse, TUint aVersion, TUint anewLoadLevelTarget, TUint anewRampTime);
    /**
     * SetStepDelta action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStepDelta action for the owning device.
     * Must be implemented iff EnableActionSetStepDelta was called.
     */
    virtual void SetStepDelta(IInvocationResponse& aResponse, TUint aVersion, TUint anewStepDelta);
    /**
     * GetStepDelta action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStepDelta action for the owning device.
     * Must be implemented iff EnableActionGetStepDelta was called.
     */
    virtual void GetStepDelta(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretStepDelta);
    /**
     * SetRampRate action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRampRate action for the owning device.
     * Must be implemented iff EnableActionSetRampRate was called.
     */
    virtual void SetRampRate(IInvocationResponse& aResponse, TUint aVersion, TUint anewRampRate);
    /**
     * GetRampRate action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRampRate action for the owning device.
     * Must be implemented iff EnableActionGetRampRate was called.
     */
    virtual void GetRampRate(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aretRampRate);
    /**
     * PauseRamp action.
     *
     * Will be called when the device stack receives an invocation of the
     * PauseRamp action for the owning device.
     * Must be implemented iff EnableActionPauseRamp was called.
     */
    virtual void PauseRamp(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * ResumeRamp action.
     *
     * Will be called when the device stack receives an invocation of the
     * ResumeRamp action for the owning device.
     * Must be implemented iff EnableActionResumeRamp was called.
     */
    virtual void ResumeRamp(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * GetIsRamping action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetIsRamping action for the owning device.
     * Must be implemented iff EnableActionGetIsRamping was called.
     */
    virtual void GetIsRamping(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretIsRamping);
    /**
     * GetRampPaused action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRampPaused action for the owning device.
     * Must be implemented iff EnableActionGetRampPaused was called.
     */
    virtual void GetRampPaused(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aretRampPaused);
    /**
     * GetRampTime action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRampTime action for the owning device.
     * Must be implemented iff EnableActionGetRampTime was called.
     */
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

