#ifndef HEADER_DVLINNCOUKDELAY1CPP
#define HEADER_DVLINNCOUKDELAY1CPP

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
 * Provider for the linn.co.uk:Delay:1 UPnP service
 */
class DvProviderLinnCoUkDelay1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDelay1Cpp() {}
    /**
     * Set the value of the PresetXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyPresetXml(const std::string& aValue);
    /**
     * Get a copy of the value of the PresetXml property
     */
    void GetPropertyPresetXml(std::string& aValue);
    /**
     * Set the value of the PresetIndex property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyPresetIndex(uint32_t aValue);
    /**
     * Get a copy of the value of the PresetIndex property
     */
    void GetPropertyPresetIndex(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkDelay1Cpp(DvDeviceStd& aDevice);
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
    virtual void PresetXml(uint32_t aVersion, std::string& aaPresetXml);
    /**
     * PresetIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetIndex action for the owning device.
     * Must be implemented iff EnableActionPresetIndex was called.
     */
    virtual void PresetIndex(uint32_t aVersion, uint32_t& aaIndex);
    /**
     * SetPresetIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetIndex action for the owning device.
     * Must be implemented iff EnableActionSetPresetIndex was called.
     */
    virtual void SetPresetIndex(uint32_t aVersion, uint32_t aaIndex);
    /**
     * SetPresetDelay action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetDelay action for the owning device.
     * Must be implemented iff EnableActionSetPresetDelay was called.
     */
    virtual void SetPresetDelay(uint32_t aVersion, uint32_t aaIndex, uint32_t aaDelay);
    /**
     * SetPresetVisible action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetVisible action for the owning device.
     * Must be implemented iff EnableActionSetPresetVisible was called.
     */
    virtual void SetPresetVisible(uint32_t aVersion, uint32_t aaIndex, bool aaVisible);
    /**
     * SetPresetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetPresetName action for the owning device.
     * Must be implemented iff EnableActionSetPresetName was called.
     */
    virtual void SetPresetName(uint32_t aVersion, uint32_t aaIndex, const std::string& aaName);
    /**
     * DelayMinimum action.
     *
     * Will be called when the device stack receives an invocation of the
     * DelayMinimum action for the owning device.
     * Must be implemented iff EnableActionDelayMinimum was called.
     */
    virtual void DelayMinimum(uint32_t aVersion, uint32_t& aaDelay);
    /**
     * DelayMaximum action.
     *
     * Will be called when the device stack receives an invocation of the
     * DelayMaximum action for the owning device.
     * Must be implemented iff EnableActionDelayMaximum was called.
     */
    virtual void DelayMaximum(uint32_t aVersion, uint32_t& aaDelay);
    /**
     * PresetCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * PresetCount action for the owning device.
     * Must be implemented iff EnableActionPresetCount was called.
     */
    virtual void PresetCount(uint32_t aVersion, uint32_t& aaCount);
private:
    DvProviderLinnCoUkDelay1Cpp();
    void DoPresetXml(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPresetIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetDelay(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetVisible(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetPresetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDelayMinimum(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDelayMaximum(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPresetCount(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyPresetXml;
    PropertyUint* iPropertyPresetIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDELAY1CPP

