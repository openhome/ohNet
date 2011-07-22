#ifndef HEADER_DVAVOPENHOMEORGVOLUME1CPP
#define HEADER_DVAVOPENHOMEORGVOLUME1CPP

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

#include <string>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Volume:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgVolume1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgVolume1Cpp() {}
    /**
     * Set the value of the Volume property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolume(uint32_t aValue);
    /**
     * Get a copy of the value of the Volume property
     */
    void GetPropertyVolume(uint32_t& aValue);
    /**
     * Set the value of the Mute property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyMute(bool aValue);
    /**
     * Get a copy of the value of the Mute property
     */
    void GetPropertyMute(bool& aValue);
    /**
     * Set the value of the Balance property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBalance(int32_t aValue);
    /**
     * Get a copy of the value of the Balance property
     */
    void GetPropertyBalance(int32_t& aValue);
    /**
     * Set the value of the Fade property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyFade(int32_t aValue);
    /**
     * Get a copy of the value of the Fade property
     */
    void GetPropertyFade(int32_t& aValue);
    /**
     * Set the value of the VolumeLimit property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolumeLimit(uint32_t aValue);
    /**
     * Get a copy of the value of the VolumeLimit property
     */
    void GetPropertyVolumeLimit(uint32_t& aValue);
    /**
     * Set the value of the VolumeMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolumeMax(uint32_t aValue);
    /**
     * Get a copy of the value of the VolumeMax property
     */
    void GetPropertyVolumeMax(uint32_t& aValue);
    /**
     * Set the value of the VolumeUnity property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolumeUnity(uint32_t aValue);
    /**
     * Get a copy of the value of the VolumeUnity property
     */
    void GetPropertyVolumeUnity(uint32_t& aValue);
    /**
     * Set the value of the VolumeSteps property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolumeSteps(uint32_t aValue);
    /**
     * Get a copy of the value of the VolumeSteps property
     */
    void GetPropertyVolumeSteps(uint32_t& aValue);
    /**
     * Set the value of the VolumeMilliDbPerStep property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyVolumeMilliDbPerStep(uint32_t aValue);
    /**
     * Get a copy of the value of the VolumeMilliDbPerStep property
     */
    void GetPropertyVolumeMilliDbPerStep(uint32_t& aValue);
    /**
     * Set the value of the BalanceMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBalanceMax(uint32_t aValue);
    /**
     * Get a copy of the value of the BalanceMax property
     */
    void GetPropertyBalanceMax(uint32_t& aValue);
    /**
     * Set the value of the FadeMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyFadeMax(uint32_t aValue);
    /**
     * Get a copy of the value of the FadeMax property
     */
    void GetPropertyFadeMax(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgVolume1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Characteristics is supported.
     * The action's availability will be published in the device's service.xml.
     * Characteristics must be overridden if this is called.
     */
    void EnableActionCharacteristics();
    /**
     * Signal that the action SetVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * SetVolume must be overridden if this is called.
     */
    void EnableActionSetVolume();
    /**
     * Signal that the action VolumeInc is supported.
     * The action's availability will be published in the device's service.xml.
     * VolumeInc must be overridden if this is called.
     */
    void EnableActionVolumeInc();
    /**
     * Signal that the action VolumeDec is supported.
     * The action's availability will be published in the device's service.xml.
     * VolumeDec must be overridden if this is called.
     */
    void EnableActionVolumeDec();
    /**
     * Signal that the action Volume is supported.
     * The action's availability will be published in the device's service.xml.
     * Volume must be overridden if this is called.
     */
    void EnableActionVolume();
    /**
     * Signal that the action SetBalance is supported.
     * The action's availability will be published in the device's service.xml.
     * SetBalance must be overridden if this is called.
     */
    void EnableActionSetBalance();
    /**
     * Signal that the action BalanceInc is supported.
     * The action's availability will be published in the device's service.xml.
     * BalanceInc must be overridden if this is called.
     */
    void EnableActionBalanceInc();
    /**
     * Signal that the action BalanceDec is supported.
     * The action's availability will be published in the device's service.xml.
     * BalanceDec must be overridden if this is called.
     */
    void EnableActionBalanceDec();
    /**
     * Signal that the action Balance is supported.
     * The action's availability will be published in the device's service.xml.
     * Balance must be overridden if this is called.
     */
    void EnableActionBalance();
    /**
     * Signal that the action SetFade is supported.
     * The action's availability will be published in the device's service.xml.
     * SetFade must be overridden if this is called.
     */
    void EnableActionSetFade();
    /**
     * Signal that the action FadeInc is supported.
     * The action's availability will be published in the device's service.xml.
     * FadeInc must be overridden if this is called.
     */
    void EnableActionFadeInc();
    /**
     * Signal that the action FadeDec is supported.
     * The action's availability will be published in the device's service.xml.
     * FadeDec must be overridden if this is called.
     */
    void EnableActionFadeDec();
    /**
     * Signal that the action Fade is supported.
     * The action's availability will be published in the device's service.xml.
     * Fade must be overridden if this is called.
     */
    void EnableActionFade();
    /**
     * Signal that the action SetMute is supported.
     * The action's availability will be published in the device's service.xml.
     * SetMute must be overridden if this is called.
     */
    void EnableActionSetMute();
    /**
     * Signal that the action Mute is supported.
     * The action's availability will be published in the device's service.xml.
     * Mute must be overridden if this is called.
     */
    void EnableActionMute();
    /**
     * Signal that the action VolumeLimit is supported.
     * The action's availability will be published in the device's service.xml.
     * VolumeLimit must be overridden if this is called.
     */
    void EnableActionVolumeLimit();
private:
    /**
     * Characteristics action.
     *
     * Will be called when the device stack receives an invocation of the
     * Characteristics action for the owning device.
     * Must be implemented iff EnableActionCharacteristics was called.
     */
    virtual void Characteristics(uint32_t aVersion, uint32_t& aVolumeMax, uint32_t& aVolumeUnity, uint32_t& aVolumeSteps, uint32_t& aVolumeMilliDbPerStep, uint32_t& aBalanceMax, uint32_t& aFadeMax);
    /**
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(uint32_t aVersion, uint32_t aValue);
    /**
     * VolumeInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeInc action for the owning device.
     * Must be implemented iff EnableActionVolumeInc was called.
     */
    virtual void VolumeInc(uint32_t aVersion);
    /**
     * VolumeDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeDec action for the owning device.
     * Must be implemented iff EnableActionVolumeDec was called.
     */
    virtual void VolumeDec(uint32_t aVersion);
    /**
     * Volume action.
     *
     * Will be called when the device stack receives an invocation of the
     * Volume action for the owning device.
     * Must be implemented iff EnableActionVolume was called.
     */
    virtual void Volume(uint32_t aVersion, uint32_t& aValue);
    /**
     * SetBalance action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBalance action for the owning device.
     * Must be implemented iff EnableActionSetBalance was called.
     */
    virtual void SetBalance(uint32_t aVersion, int32_t aValue);
    /**
     * BalanceInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * BalanceInc action for the owning device.
     * Must be implemented iff EnableActionBalanceInc was called.
     */
    virtual void BalanceInc(uint32_t aVersion);
    /**
     * BalanceDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * BalanceDec action for the owning device.
     * Must be implemented iff EnableActionBalanceDec was called.
     */
    virtual void BalanceDec(uint32_t aVersion);
    /**
     * Balance action.
     *
     * Will be called when the device stack receives an invocation of the
     * Balance action for the owning device.
     * Must be implemented iff EnableActionBalance was called.
     */
    virtual void Balance(uint32_t aVersion, int32_t& aValue);
    /**
     * SetFade action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetFade action for the owning device.
     * Must be implemented iff EnableActionSetFade was called.
     */
    virtual void SetFade(uint32_t aVersion, int32_t aValue);
    /**
     * FadeInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * FadeInc action for the owning device.
     * Must be implemented iff EnableActionFadeInc was called.
     */
    virtual void FadeInc(uint32_t aVersion);
    /**
     * FadeDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * FadeDec action for the owning device.
     * Must be implemented iff EnableActionFadeDec was called.
     */
    virtual void FadeDec(uint32_t aVersion);
    /**
     * Fade action.
     *
     * Will be called when the device stack receives an invocation of the
     * Fade action for the owning device.
     * Must be implemented iff EnableActionFade was called.
     */
    virtual void Fade(uint32_t aVersion, int32_t& aValue);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(uint32_t aVersion, bool aValue);
    /**
     * Mute action.
     *
     * Will be called when the device stack receives an invocation of the
     * Mute action for the owning device.
     * Must be implemented iff EnableActionMute was called.
     */
    virtual void Mute(uint32_t aVersion, bool& aValue);
    /**
     * VolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeLimit action for the owning device.
     * Must be implemented iff EnableActionVolumeLimit was called.
     */
    virtual void VolumeLimit(uint32_t aVersion, uint32_t& aValue);
private:
    DvProviderAvOpenhomeOrgVolume1Cpp();
    void DoCharacteristics(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeInc(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeDec(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBalance(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBalanceInc(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBalanceDec(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBalance(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetFade(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoFadeInc(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoFadeDec(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoFade(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetMute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeLimit(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyInt* iPropertyFade;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyVolumeMax;
    PropertyUint* iPropertyVolumeUnity;
    PropertyUint* iPropertyVolumeSteps;
    PropertyUint* iPropertyVolumeMilliDbPerStep;
    PropertyUint* iPropertyBalanceMax;
    PropertyUint* iPropertyFadeMax;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGVOLUME1CPP

