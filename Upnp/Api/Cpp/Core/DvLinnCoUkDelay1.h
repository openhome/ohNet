#ifndef HEADER_DVLINNCOUKDELAY1
#define HEADER_DVLINNCOUKDELAY1

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
 * Provider for the linn.co.uk:Delay:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkDelay1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDelay1() {}
    /**
     * Set the value of the PresetXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPresetXml(const Brx& aValue);
    /**
     * Get a copy of the value of the PresetXml property
     */
    void GetPropertyPresetXml(Brhz& aValue);
    /**
     * Set the value of the PresetIndex property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyPresetIndex(TUint aValue);
    /**
     * Get a copy of the value of the PresetIndex property
     */
    void GetPropertyPresetIndex(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDelay1(DvDevice& aDevice);
    /**
     * Signal that the action PresetXml is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPresetXml must be overridden if this is called.
     */
    void EnableActionPresetXml();
    /**
     * Signal that the action PresetIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPresetIndex must be overridden if this is called.
     */
    void EnableActionPresetIndex();
    /**
     * Signal that the action SetPresetIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetPresetIndex must be overridden if this is called.
     */
    void EnableActionSetPresetIndex();
    /**
     * Signal that the action SetPresetDelay is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetPresetDelay must be overridden if this is called.
     */
    void EnableActionSetPresetDelay();
    /**
     * Signal that the action SetPresetVisible is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetPresetVisible must be overridden if this is called.
     */
    void EnableActionSetPresetVisible();
    /**
     * Signal that the action SetPresetName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetPresetName must be overridden if this is called.
     */
    void EnableActionSetPresetName();
    /**
     * Signal that the action DelayMinimum is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDelayMinimum must be overridden if this is called.
     */
    void EnableActionDelayMinimum();
    /**
     * Signal that the action DelayMaximum is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDelayMaximum must be overridden if this is called.
     */
    void EnableActionDelayMaximum();
    /**
     * Signal that the action PresetCount is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPresetCount must be overridden if this is called.
     */
    void EnableActionPresetCount();
private:
    /**
     * PresetXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetXml action for the owning device.
     * Must be implemented iff EnableActionPresetXml was called.
     */
    virtual void PresetXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaPresetXml);
    /**
     * PresetIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetIndex action for the owning device.
     * Must be implemented iff EnableActionPresetIndex was called.
     */
    virtual void PresetIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaIndex);
    /**
     * SetPresetIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetIndex action for the owning device.
     * Must be implemented iff EnableActionSetPresetIndex was called.
     */
    virtual void SetPresetIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex);
    /**
     * SetPresetDelay action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetDelay action for the owning device.
     * Must be implemented iff EnableActionSetPresetDelay was called.
     */
    virtual void SetPresetDelay(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TUint aaDelay);
    /**
     * SetPresetVisible action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetVisible action for the owning device.
     * Must be implemented iff EnableActionSetPresetVisible was called.
     */
    virtual void SetPresetVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, TBool aaVisible);
    /**
     * SetPresetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetName action for the owning device.
     * Must be implemented iff EnableActionSetPresetName was called.
     */
    virtual void SetPresetName(IInvocationResponse& aResponse, TUint aVersion, TUint aaIndex, const Brx& aaName);
    /**
     * DelayMinimum action.
     *
     * Will be called when the device stack receives an invocation of the
     * DelayMinimum action for the owning device.
     * Must be implemented iff EnableActionDelayMinimum was called.
     */
    virtual void DelayMinimum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay);
    /**
     * DelayMaximum action.
     *
     * Will be called when the device stack receives an invocation of the
     * DelayMaximum action for the owning device.
     * Must be implemented iff EnableActionDelayMaximum was called.
     */
    virtual void DelayMaximum(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaDelay);
    /**
     * PresetCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetCount action for the owning device.
     * Must be implemented iff EnableActionPresetCount was called.
     */
    virtual void PresetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaCount);
private:
    DvProviderLinnCoUkDelay1();
    void DoPresetXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetDelay(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetVisible(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelayMinimum(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelayMaximum(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetCount(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyPresetXml;
    PropertyUint* iPropertyPresetIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDELAY1

