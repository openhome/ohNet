#ifndef HEADER_DVLINNCOUKCOMPONENT1
#define HEADER_DVLINNCOUKCOMPONENT1

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
 * Provider for the linn.co.uk:Component:1 UPnP service
 */
class DvProviderLinnCoUkComponent1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkComponent1() {}
    /**
     * Set the value of the AmplifierEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAmplifierEnabled(TBool aValue);
    /**
     * Get a copy of the value of the AmplifierEnabled property
     */
    void GetPropertyAmplifierEnabled(TBool& aValue);
    /**
     * Set the value of the AmplifierAttenuation property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAmplifierAttenuation(const Brx& aValue);
    /**
     * Get a copy of the value of the AmplifierAttenuation property
     */
    void GetPropertyAmplifierAttenuation(Brhz& aValue);
    /**
     * Set the value of the VolumeControlEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeControlEnabled(TBool aValue);
    /**
     * Get a copy of the value of the VolumeControlEnabled property
     */
    void GetPropertyVolumeControlEnabled(TBool& aValue);
    /**
     * Set the value of the DigitalAudioOutputRaw property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDigitalAudioOutputRaw(TBool aValue);
    /**
     * Get a copy of the value of the DigitalAudioOutputRaw property
     */
    void GetPropertyDigitalAudioOutputRaw(TBool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkComponent1(DvDevice& aDevice);
    /**
     * Signal that the action AmplifierEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoAmplifierEnabled must be overridden if this is called.
     */
    void EnableActionAmplifierEnabled();
    /**
     * Signal that the action SetAmplifierEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetAmplifierEnabled must be overridden if this is called.
     */
    void EnableActionSetAmplifierEnabled();
    /**
     * Signal that the action AmplifierAttenuation is supported.
     * The action's availability will be published in the device's service.xml.
     * DoAmplifierAttenuation must be overridden if this is called.
     */
    void EnableActionAmplifierAttenuation();
    /**
     * Signal that the action SetAmplifierAttenuation is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetAmplifierAttenuation must be overridden if this is called.
     */
    void EnableActionSetAmplifierAttenuation();
    /**
     * Signal that the action SetVolumeControlEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetVolumeControlEnabled must be overridden if this is called.
     */
    void EnableActionSetVolumeControlEnabled();
    /**
     * Signal that the action VolumeControlEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoVolumeControlEnabled must be overridden if this is called.
     */
    void EnableActionVolumeControlEnabled();
    /**
     * Signal that the action SetDigitalAudioOutputRaw is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetDigitalAudioOutputRaw must be overridden if this is called.
     */
    void EnableActionSetDigitalAudioOutputRaw();
    /**
     * Signal that the action DigitalAudioOutputRaw is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDigitalAudioOutputRaw must be overridden if this is called.
     */
    void EnableActionDigitalAudioOutputRaw();
    /**
     * Signal that the action AmplifierOverTemperature is supported.
     * The action's availability will be published in the device's service.xml.
     * DoAmplifierOverTemperature must be overridden if this is called.
     */
    void EnableActionAmplifierOverTemperature();
    /**
     * Signal that the action EthernetLinkConnected is supported.
     * The action's availability will be published in the device's service.xml.
     * DoEthernetLinkConnected must be overridden if this is called.
     */
    void EnableActionEthernetLinkConnected();
    /**
     * Signal that the action Locate is supported.
     * The action's availability will be published in the device's service.xml.
     * DoLocate must be overridden if this is called.
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
    virtual void AmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    /**
     * SetAmplifierEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAmplifierEnabled action for the owning device.
     * Must be implemented iff EnableActionSetAmplifierEnabled was called.
     */
    virtual void SetAmplifierEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    /**
     * AmplifierAttenuation action.
     *
     * Will be called when the device stack receives an invocation of the
     * AmplifierAttenuation action for the owning device.
     * Must be implemented iff EnableActionAmplifierAttenuation was called.
     */
    virtual void AmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaAttenuation);
    /**
     * SetAmplifierAttenuation action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetAmplifierAttenuation action for the owning device.
     * Must be implemented iff EnableActionSetAmplifierAttenuation was called.
     */
    virtual void SetAmplifierAttenuation(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaAttenuation);
    /**
     * SetVolumeControlEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolumeControlEnabled action for the owning device.
     * Must be implemented iff EnableActionSetVolumeControlEnabled was called.
     */
    virtual void SetVolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaEnabled);
    /**
     * VolumeControlEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeControlEnabled action for the owning device.
     * Must be implemented iff EnableActionVolumeControlEnabled was called.
     */
    virtual void VolumeControlEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaEnabled);
    /**
     * SetDigitalAudioOutputRaw action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetDigitalAudioOutputRaw action for the owning device.
     * Must be implemented iff EnableActionSetDigitalAudioOutputRaw was called.
     */
    virtual void SetDigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, TBool aaRaw);
    /**
     * DigitalAudioOutputRaw action.
     *
     * Will be called when the device stack receives an invocation of the
     * DigitalAudioOutputRaw action for the owning device.
     * Must be implemented iff EnableActionDigitalAudioOutputRaw was called.
     */
    virtual void DigitalAudioOutputRaw(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaRaw);
    /**
     * AmplifierOverTemperature action.
     *
     * Will be called when the device stack receives an invocation of the
     * AmplifierOverTemperature action for the owning device.
     * Must be implemented iff EnableActionAmplifierOverTemperature was called.
     */
    virtual void AmplifierOverTemperature(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaOverTemperature);
    /**
     * EthernetLinkConnected action.
     *
     * Will be called when the device stack receives an invocation of the
     * EthernetLinkConnected action for the owning device.
     * Must be implemented iff EnableActionEthernetLinkConnected was called.
     */
    virtual void EthernetLinkConnected(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaLinkConnected);
    /**
     * Locate action.
     *
     * Will be called when the device stack receives an invocation of the
     * Locate action for the owning device.
     * Must be implemented iff EnableActionLocate was called.
     */
    virtual void Locate(IInvocationResponse& aResponse, TUint aVersion);
private:
    DvProviderLinnCoUkComponent1();
    void DoAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion);
    void DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion);
    void DoAmplifierOverTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoEthernetLinkConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoLocate(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKCOMPONENT1

