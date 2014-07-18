#ifndef HEADER_DVUPNPORGDIMMING1
#define HEADER_DVUPNPORGDIMMING1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
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
     * Can only be called if EnablePropertyLoadLevelStatus has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyLoadLevelStatus(TUint aValue);
    /**
     * Get a copy of the value of the LoadLevelStatus property
     *
     * Can only be called if EnablePropertyLoadLevelStatus has previously been called.
     */
    void GetPropertyLoadLevelStatus(TUint& aValue);
    /**
     * Set the value of the StepDelta property
     *
     * Can only be called if EnablePropertyStepDelta has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStepDelta(TUint aValue);
    /**
     * Get a copy of the value of the StepDelta property
     *
     * Can only be called if EnablePropertyStepDelta has previously been called.
     */
    void GetPropertyStepDelta(TUint& aValue);
    /**
     * Set the value of the RampRate property
     *
     * Can only be called if EnablePropertyRampRate has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyRampRate(TUint aValue);
    /**
     * Get a copy of the value of the RampRate property
     *
     * Can only be called if EnablePropertyRampRate has previously been called.
     */
    void GetPropertyRampRate(TUint& aValue);
    /**
     * Set the value of the IsRamping property
     *
     * Can only be called if EnablePropertyIsRamping has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyIsRamping(TBool aValue);
    /**
     * Get a copy of the value of the IsRamping property
     *
     * Can only be called if EnablePropertyIsRamping has previously been called.
     */
    void GetPropertyIsRamping(TBool& aValue);
    /**
     * Set the value of the RampPaused property
     *
     * Can only be called if EnablePropertyRampPaused has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyRampPaused(TBool aValue);
    /**
     * Get a copy of the value of the RampPaused property
     *
     * Can only be called if EnablePropertyRampPaused has previously been called.
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
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgDimming1(DviDevice& aDevice);
    /**
     * Enable the LoadLevelStatus property.
     */
    void EnablePropertyLoadLevelStatus();
    /**
     * Enable the StepDelta property.
     */
    void EnablePropertyStepDelta();
    /**
     * Enable the RampRate property.
     */
    void EnablePropertyRampRate();
    /**
     * Enable the IsRamping property.
     */
    void EnablePropertyIsRamping();
    /**
     * Enable the RampPaused property.
     */
    void EnablePropertyRampPaused();
    /**
     * Signal that the action SetLoadLevelTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * SetLoadLevelTarget must be overridden if this is called.
     */
    void EnableActionSetLoadLevelTarget();
    /**
     * Signal that the action GetLoadLevelTarget is supported.
     * The action's availability will be published in the device's service.xml.
     * GetLoadLevelTarget must be overridden if this is called.
     */
    void EnableActionGetLoadLevelTarget();
    /**
     * Signal that the action GetLoadLevelStatus is supported.
     * The action's availability will be published in the device's service.xml.
     * GetLoadLevelStatus must be overridden if this is called.
     */
    void EnableActionGetLoadLevelStatus();
    /**
     * Signal that the action SetOnEffectLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetOnEffectLevel must be overridden if this is called.
     */
    void EnableActionSetOnEffectLevel();
    /**
     * Signal that the action SetOnEffect is supported.
     * The action's availability will be published in the device's service.xml.
     * SetOnEffect must be overridden if this is called.
     */
    void EnableActionSetOnEffect();
    /**
     * Signal that the action GetOnEffectParameters is supported.
     * The action's availability will be published in the device's service.xml.
     * GetOnEffectParameters must be overridden if this is called.
     */
    void EnableActionGetOnEffectParameters();
    /**
     * Signal that the action StepUp is supported.
     * The action's availability will be published in the device's service.xml.
     * StepUp must be overridden if this is called.
     */
    void EnableActionStepUp();
    /**
     * Signal that the action StepDown is supported.
     * The action's availability will be published in the device's service.xml.
     * StepDown must be overridden if this is called.
     */
    void EnableActionStepDown();
    /**
     * Signal that the action StartRampUp is supported.
     * The action's availability will be published in the device's service.xml.
     * StartRampUp must be overridden if this is called.
     */
    void EnableActionStartRampUp();
    /**
     * Signal that the action StartRampDown is supported.
     * The action's availability will be published in the device's service.xml.
     * StartRampDown must be overridden if this is called.
     */
    void EnableActionStartRampDown();
    /**
     * Signal that the action StopRamp is supported.
     * The action's availability will be published in the device's service.xml.
     * StopRamp must be overridden if this is called.
     */
    void EnableActionStopRamp();
    /**
     * Signal that the action StartRampToLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * StartRampToLevel must be overridden if this is called.
     */
    void EnableActionStartRampToLevel();
    /**
     * Signal that the action SetStepDelta is supported.
     * The action's availability will be published in the device's service.xml.
     * SetStepDelta must be overridden if this is called.
     */
    void EnableActionSetStepDelta();
    /**
     * Signal that the action GetStepDelta is supported.
     * The action's availability will be published in the device's service.xml.
     * GetStepDelta must be overridden if this is called.
     */
    void EnableActionGetStepDelta();
    /**
     * Signal that the action SetRampRate is supported.
     * The action's availability will be published in the device's service.xml.
     * SetRampRate must be overridden if this is called.
     */
    void EnableActionSetRampRate();
    /**
     * Signal that the action GetRampRate is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRampRate must be overridden if this is called.
     */
    void EnableActionGetRampRate();
    /**
     * Signal that the action PauseRamp is supported.
     * The action's availability will be published in the device's service.xml.
     * PauseRamp must be overridden if this is called.
     */
    void EnableActionPauseRamp();
    /**
     * Signal that the action ResumeRamp is supported.
     * The action's availability will be published in the device's service.xml.
     * ResumeRamp must be overridden if this is called.
     */
    void EnableActionResumeRamp();
    /**
     * Signal that the action GetIsRamping is supported.
     * The action's availability will be published in the device's service.xml.
     * GetIsRamping must be overridden if this is called.
     */
    void EnableActionGetIsRamping();
    /**
     * Signal that the action GetRampPaused is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRampPaused must be overridden if this is called.
     */
    void EnableActionGetRampPaused();
    /**
     * Signal that the action GetRampTime is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRampTime must be overridden if this is called.
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
    virtual void SetLoadLevelTarget(IDvInvocation& aInvocation, TUint anewLoadlevelTarget);
    /**
     * GetLoadLevelTarget action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLoadLevelTarget action for the owning device.
     * Must be implemented iff EnableActionGetLoadLevelTarget was called.
     */
    virtual void GetLoadLevelTarget(IDvInvocation& aInvocation, IDvInvocationResponseUint& aGetLoadlevelTarget);
    /**
     * GetLoadLevelStatus action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLoadLevelStatus action for the owning device.
     * Must be implemented iff EnableActionGetLoadLevelStatus was called.
     */
    virtual void GetLoadLevelStatus(IDvInvocation& aInvocation, IDvInvocationResponseUint& aretLoadlevelStatus);
    /**
     * SetOnEffectLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetOnEffectLevel action for the owning device.
     * Must be implemented iff EnableActionSetOnEffectLevel was called.
     */
    virtual void SetOnEffectLevel(IDvInvocation& aInvocation, TUint anewOnEffectLevel);
    /**
     * SetOnEffect action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetOnEffect action for the owning device.
     * Must be implemented iff EnableActionSetOnEffect was called.
     */
    virtual void SetOnEffect(IDvInvocation& aInvocation, const Brx& anewOnEffect);
    /**
     * GetOnEffectParameters action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetOnEffectParameters action for the owning device.
     * Must be implemented iff EnableActionGetOnEffectParameters was called.
     */
    virtual void GetOnEffectParameters(IDvInvocation& aInvocation, IDvInvocationResponseString& aretOnEffect, IDvInvocationResponseUint& aretOnEffectLevel);
    /**
     * StepUp action.
     *
     * Will be called when the device stack receives an invocation of the
     * StepUp action for the owning device.
     * Must be implemented iff EnableActionStepUp was called.
     */
    virtual void StepUp(IDvInvocation& aInvocation);
    /**
     * StepDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * StepDown action for the owning device.
     * Must be implemented iff EnableActionStepDown was called.
     */
    virtual void StepDown(IDvInvocation& aInvocation);
    /**
     * StartRampUp action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartRampUp action for the owning device.
     * Must be implemented iff EnableActionStartRampUp was called.
     */
    virtual void StartRampUp(IDvInvocation& aInvocation);
    /**
     * StartRampDown action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartRampDown action for the owning device.
     * Must be implemented iff EnableActionStartRampDown was called.
     */
    virtual void StartRampDown(IDvInvocation& aInvocation);
    /**
     * StopRamp action.
     *
     * Will be called when the device stack receives an invocation of the
     * StopRamp action for the owning device.
     * Must be implemented iff EnableActionStopRamp was called.
     */
    virtual void StopRamp(IDvInvocation& aInvocation);
    /**
     * StartRampToLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartRampToLevel action for the owning device.
     * Must be implemented iff EnableActionStartRampToLevel was called.
     */
    virtual void StartRampToLevel(IDvInvocation& aInvocation, TUint anewLoadLevelTarget, TUint anewRampTime);
    /**
     * SetStepDelta action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStepDelta action for the owning device.
     * Must be implemented iff EnableActionSetStepDelta was called.
     */
    virtual void SetStepDelta(IDvInvocation& aInvocation, TUint anewStepDelta);
    /**
     * GetStepDelta action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStepDelta action for the owning device.
     * Must be implemented iff EnableActionGetStepDelta was called.
     */
    virtual void GetStepDelta(IDvInvocation& aInvocation, IDvInvocationResponseUint& aretStepDelta);
    /**
     * SetRampRate action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRampRate action for the owning device.
     * Must be implemented iff EnableActionSetRampRate was called.
     */
    virtual void SetRampRate(IDvInvocation& aInvocation, TUint anewRampRate);
    /**
     * GetRampRate action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRampRate action for the owning device.
     * Must be implemented iff EnableActionGetRampRate was called.
     */
    virtual void GetRampRate(IDvInvocation& aInvocation, IDvInvocationResponseUint& aretRampRate);
    /**
     * PauseRamp action.
     *
     * Will be called when the device stack receives an invocation of the
     * PauseRamp action for the owning device.
     * Must be implemented iff EnableActionPauseRamp was called.
     */
    virtual void PauseRamp(IDvInvocation& aInvocation);
    /**
     * ResumeRamp action.
     *
     * Will be called when the device stack receives an invocation of the
     * ResumeRamp action for the owning device.
     * Must be implemented iff EnableActionResumeRamp was called.
     */
    virtual void ResumeRamp(IDvInvocation& aInvocation);
    /**
     * GetIsRamping action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetIsRamping action for the owning device.
     * Must be implemented iff EnableActionGetIsRamping was called.
     */
    virtual void GetIsRamping(IDvInvocation& aInvocation, IDvInvocationResponseBool& aretIsRamping);
    /**
     * GetRampPaused action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRampPaused action for the owning device.
     * Must be implemented iff EnableActionGetRampPaused was called.
     */
    virtual void GetRampPaused(IDvInvocation& aInvocation, IDvInvocationResponseBool& aretRampPaused);
    /**
     * GetRampTime action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRampTime action for the owning device.
     * Must be implemented iff EnableActionGetRampTime was called.
     */
    virtual void GetRampTime(IDvInvocation& aInvocation, IDvInvocationResponseUint& aretRampTime);
private:
    DvProviderUpnpOrgDimming1();
    void Construct();
    void DoSetLoadLevelTarget(IDviInvocation& aInvocation);
    void DoGetLoadLevelTarget(IDviInvocation& aInvocation);
    void DoGetLoadLevelStatus(IDviInvocation& aInvocation);
    void DoSetOnEffectLevel(IDviInvocation& aInvocation);
    void DoSetOnEffect(IDviInvocation& aInvocation);
    void DoGetOnEffectParameters(IDviInvocation& aInvocation);
    void DoStepUp(IDviInvocation& aInvocation);
    void DoStepDown(IDviInvocation& aInvocation);
    void DoStartRampUp(IDviInvocation& aInvocation);
    void DoStartRampDown(IDviInvocation& aInvocation);
    void DoStopRamp(IDviInvocation& aInvocation);
    void DoStartRampToLevel(IDviInvocation& aInvocation);
    void DoSetStepDelta(IDviInvocation& aInvocation);
    void DoGetStepDelta(IDviInvocation& aInvocation);
    void DoSetRampRate(IDviInvocation& aInvocation);
    void DoGetRampRate(IDviInvocation& aInvocation);
    void DoPauseRamp(IDviInvocation& aInvocation);
    void DoResumeRamp(IDviInvocation& aInvocation);
    void DoGetIsRamping(IDviInvocation& aInvocation);
    void DoGetRampPaused(IDviInvocation& aInvocation);
    void DoGetRampTime(IDviInvocation& aInvocation);
private:
    PropertyUint* iPropertyLoadLevelStatus;
    PropertyUint* iPropertyStepDelta;
    PropertyUint* iPropertyRampRate;
    PropertyBool* iPropertyIsRamping;
    PropertyBool* iPropertyRampPaused;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGDIMMING1

