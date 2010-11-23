#ifndef HEADER_DVLINNCOUKPREAMP4CPP
#define HEADER_DVLINNCOUKPREAMP4CPP

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
 * Provider for the linn.co.uk:Preamp:4 UPnP service
 */
class DvProviderLinnCoUkPreamp4Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPreamp4Cpp() {}
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
     * Set the value of the StartupVolume property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyStartupVolume(uint32_t aValue);
    /**
     * Get a copy of the value of the StartupVolume property
     */
    void GetPropertyStartupVolume(uint32_t& aValue);
    /**
     * Set the value of the StartupVolumeEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyStartupVolumeEnabled(bool aValue);
    /**
     * Get a copy of the value of the StartupVolumeEnabled property
     */
    void GetPropertyStartupVolumeEnabled(bool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkPreamp4Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action VolumeInc is supported.
     * The action's availability will be published in the device's service.xml.
     * DoVolumeInc must be overridden if this is called.
     */
    void EnableActionVolumeInc();
    /**
     * Signal that the action VolumeDec is supported.
     * The action's availability will be published in the device's service.xml.
     * DoVolumeDec must be overridden if this is called.
     */
    void EnableActionVolumeDec();
    /**
     * Signal that the action SetVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetVolume must be overridden if this is called.
     */
    void EnableActionSetVolume();
    /**
     * Signal that the action Volume is supported.
     * The action's availability will be published in the device's service.xml.
     * DoVolume must be overridden if this is called.
     */
    void EnableActionVolume();
    /**
     * Signal that the action SetMute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetMute must be overridden if this is called.
     */
    void EnableActionSetMute();
    /**
     * Signal that the action Mute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMute must be overridden if this is called.
     */
    void EnableActionMute();
    /**
     * Signal that the action SetBalance is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetBalance must be overridden if this is called.
     */
    void EnableActionSetBalance();
    /**
     * Signal that the action Balance is supported.
     * The action's availability will be published in the device's service.xml.
     * DoBalance must be overridden if this is called.
     */
    void EnableActionBalance();
    /**
     * Signal that the action SetVolumeLimit is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetVolumeLimit must be overridden if this is called.
     */
    void EnableActionSetVolumeLimit();
    /**
     * Signal that the action VolumeLimit is supported.
     * The action's availability will be published in the device's service.xml.
     * DoVolumeLimit must be overridden if this is called.
     */
    void EnableActionVolumeLimit();
    /**
     * Signal that the action SetStartupVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStartupVolume must be overridden if this is called.
     */
    void EnableActionSetStartupVolume();
    /**
     * Signal that the action StartupVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartupVolume must be overridden if this is called.
     */
    void EnableActionStartupVolume();
    /**
     * Signal that the action SetStartupVolumeEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStartupVolumeEnabled must be overridden if this is called.
     */
    void EnableActionSetStartupVolumeEnabled();
    /**
     * Signal that the action StartupVolumeEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartupVolumeEnabled must be overridden if this is called.
     */
    void EnableActionStartupVolumeEnabled();
private:
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
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(uint32_t aVersion, uint32_t aaVolume);
    /**
     * Volume action.
     *
     * Will be called when the device stack receives an invocation of the
     * Volume action for the owning device.
     * Must be implemented iff EnableActionVolume was called.
     */
    virtual void Volume(uint32_t aVersion, uint32_t& aaVolume);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(uint32_t aVersion, bool aaMute);
    /**
     * Mute action.
     *
     * Will be called when the device stack receives an invocation of the
     * Mute action for the owning device.
     * Must be implemented iff EnableActionMute was called.
     */
    virtual void Mute(uint32_t aVersion, bool& aaMute);
    /**
     * SetBalance action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBalance action for the owning device.
     * Must be implemented iff EnableActionSetBalance was called.
     */
    virtual void SetBalance(uint32_t aVersion, int32_t aaBalance);
    /**
     * Balance action.
     *
     * Will be called when the device stack receives an invocation of the
     * Balance action for the owning device.
     * Must be implemented iff EnableActionBalance was called.
     */
    virtual void Balance(uint32_t aVersion, int32_t& aaBalance);
    /**
     * SetVolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolumeLimit action for the owning device.
     * Must be implemented iff EnableActionSetVolumeLimit was called.
     */
    virtual void SetVolumeLimit(uint32_t aVersion, uint32_t aaVolumeLimit);
    /**
     * VolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeLimit action for the owning device.
     * Must be implemented iff EnableActionVolumeLimit was called.
     */
    virtual void VolumeLimit(uint32_t aVersion, uint32_t& aaVolumeLimit);
    /**
     * SetStartupVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupVolume action for the owning device.
     * Must be implemented iff EnableActionSetStartupVolume was called.
     */
    virtual void SetStartupVolume(uint32_t aVersion, uint32_t aaStartupVolume);
    /**
     * StartupVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupVolume action for the owning device.
     * Must be implemented iff EnableActionStartupVolume was called.
     */
    virtual void StartupVolume(uint32_t aVersion, uint32_t& aaStartupVolume);
    /**
     * SetStartupVolumeEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupVolumeEnabled action for the owning device.
     * Must be implemented iff EnableActionSetStartupVolumeEnabled was called.
     */
    virtual void SetStartupVolumeEnabled(uint32_t aVersion, bool aaStartupVolumeEnabled);
    /**
     * StartupVolumeEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupVolumeEnabled action for the owning device.
     * Must be implemented iff EnableActionStartupVolumeEnabled was called.
     */
    virtual void StartupVolumeEnabled(uint32_t aVersion, bool& aaStartupVolumeEnabled);
private:
    DvProviderLinnCoUkPreamp4Cpp();
    void DoVolumeInc(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeDec(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetMute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBalance(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBalance(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeLimit(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoVolumeLimit(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartupVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartupVolumeEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyStartupVolume;
    PropertyBool* iPropertyStartupVolumeEnabled;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPREAMP4CPP

