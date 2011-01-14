#ifndef HEADER_DVLINNCOUKCOMPONENT1CPP
#define HEADER_DVLINNCOUKCOMPONENT1CPP

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
 * Provider for the linn.co.uk:Component:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkComponent1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkComponent1Cpp() {}
    /**
     * Set the value of the AmplifierEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyAmplifierEnabled(bool aValue);
    /**
     * Get a copy of the value of the AmplifierEnabled property
     */
    void GetPropertyAmplifierEnabled(bool& aValue);
    /**
     * Set the value of the AmplifierAttenuation property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyAmplifierAttenuation(const std::string& aValue);
    /**
     * Get a copy of the value of the AmplifierAttenuation property
     */
    void GetPropertyAmplifierAttenuation(std::string& aValue);
    /**
     * Set the value of the VolumeControlEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolumeControlEnabled(bool aValue);
    /**
     * Get a copy of the value of the VolumeControlEnabled property
     */
    void GetPropertyVolumeControlEnabled(bool& aValue);
    /**
     * Set the value of the DigitalAudioOutputRaw property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDigitalAudioOutputRaw(bool aValue);
    /**
     * Get a copy of the value of the DigitalAudioOutputRaw property
     */
    void GetPropertyDigitalAudioOutputRaw(bool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkComponent1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action AmplifierEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * AmplifierEnabled must be overridden if this is called.
     */
    void EnableActionAmplifierEnabled();
    /**
     * Signal that the action SetAmplifierEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * SetAmplifierEnabled must be overridden if this is called.
     */
    void EnableActionSetAmplifierEnabled();
    /**
     * Signal that the action AmplifierAttenuation is supported.
     * The action's availability will be published in the device's service.xml.
     * AmplifierAttenuation must be overridden if this is called.
     */
    void EnableActionAmplifierAttenuation();
    /**
     * Signal that the action SetAmplifierAttenuation is supported.
     * The action's availability will be published in the device's service.xml.
     * SetAmplifierAttenuation must be overridden if this is called.
     */
    void EnableActionSetAmplifierAttenuation();
    /**
     * Signal that the action SetVolumeControlEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * SetVolumeControlEnabled must be overridden if this is called.
     */
    void EnableActionSetVolumeControlEnabled();
    /**
     * Signal that the action VolumeControlEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * VolumeControlEnabled must be overridden if this is called.
     */
    void EnableActionVolumeControlEnabled();
    /**
     * Signal that the action SetDigitalAudioOutputRaw is supported.
     * The action's availability will be published in the device's service.xml.
     * SetDigitalAudioOutputRaw must be overridden if this is called.
     */
    void EnableActionSetDigitalAudioOutputRaw();
    /**
     * Signal that the action DigitalAudioOutputRaw is supported.
     * The action's availability will be published in the device's service.xml.
     * DigitalAudioOutputRaw must be overridden if this is called.
     */
    void EnableActionDigitalAudioOutputRaw();
    /**
     * Signal that the action AmplifierOverTemperature is supported.
     * The action's availability will be published in the device's service.xml.
     * AmplifierOverTemperature must be overridden if this is called.
     */
    void EnableActionAmplifierOverTemperature();
    /**
     * Signal that the action EthernetLinkConnected is supported.
     * The action's availability will be published in the device's service.xml.
     * EthernetLinkConnected must be overridden if this is called.
     */
    void EnableActionEthernetLinkConnected();
    /**
     * Signal that the action Locate is supported.
     * The action's availability will be published in the device's service.xml.
     * Locate must be overridden if this is called.
     */
    void EnableActionLocate();
private:
    /**
     * AmplifierEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * AmplifierEnabled action for the owning device.
     * Must be implemented iff EnableActionAmplifierEnabled was called.
     */
    virtual void AmplifierEnabled(uint32_t aVersion, bool& aaEnabled);
    /**
     * SetAmplifierEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAmplifierEnabled action for the owning device.
     * Must be implemented iff EnableActionSetAmplifierEnabled was called.
     */
    virtual void SetAmplifierEnabled(uint32_t aVersion, bool aaEnabled);
    /**
     * AmplifierAttenuation action.
     *
     * Will be called when the device stack receives an invocation of the
     * AmplifierAttenuation action for the owning device.
     * Must be implemented iff EnableActionAmplifierAttenuation was called.
     */
    virtual void AmplifierAttenuation(uint32_t aVersion, std::string& aaAttenuation);
    /**
     * SetAmplifierAttenuation action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAmplifierAttenuation action for the owning device.
     * Must be implemented iff EnableActionSetAmplifierAttenuation was called.
     */
    virtual void SetAmplifierAttenuation(uint32_t aVersion, const std::string& aaAttenuation);
    /**
     * SetVolumeControlEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolumeControlEnabled action for the owning device.
     * Must be implemented iff EnableActionSetVolumeControlEnabled was called.
     */
    virtual void SetVolumeControlEnabled(uint32_t aVersion, bool aaEnabled);
    /**
     * VolumeControlEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeControlEnabled action for the owning device.
     * Must be implemented iff EnableActionVolumeControlEnabled was called.
     */
    virtual void VolumeControlEnabled(uint32_t aVersion, bool& aaEnabled);
    /**
     * SetDigitalAudioOutputRaw action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDigitalAudioOutputRaw action for the owning device.
     * Must be implemented iff EnableActionSetDigitalAudioOutputRaw was called.
     */
    virtual void SetDigitalAudioOutputRaw(uint32_t aVersion, bool aaRaw);
    /**
     * DigitalAudioOutputRaw action.
     *
     * Will be called when the device stack receives an invocation of the
     * DigitalAudioOutputRaw action for the owning device.
     * Must be implemented iff EnableActionDigitalAudioOutputRaw was called.
     */
    virtual void DigitalAudioOutputRaw(uint32_t aVersion, bool& aaRaw);
    /**
     * AmplifierOverTemperature action.
     *
     * Will be called when the device stack receives an invocation of the
     * AmplifierOverTemperature action for the owning device.
     * Must be implemented iff EnableActionAmplifierOverTemperature was called.
     */
    virtual void AmplifierOverTemperature(uint32_t aVersion, bool& aaOverTemperature);
    /**
     * EthernetLinkConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * EthernetLinkConnected action for the owning device.
     * Must be implemented iff EnableActionEthernetLinkConnected was called.
     */
    virtual void EthernetLinkConnected(uint32_t aVersion, bool& aaLinkConnected);
    /**
     * Locate action.
     *
     * Will be called when the device stack receives an invocation of the
     * Locate action for the owning device.
     * Must be implemented iff EnableActionLocate was called.
     */
    virtual void Locate(uint32_t aVersion);
private:
    DvProviderLinnCoUkComponent1Cpp();
    void DoAmplifierEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetAmplifierEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoAmplifierAttenuation(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetAmplifierAttenuation(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeControlEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeControlEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoAmplifierOverTemperature(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoEthernetLinkConnected(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoLocate(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCOMPONENT1CPP

