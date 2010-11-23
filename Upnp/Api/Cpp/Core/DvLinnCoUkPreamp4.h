#ifndef HEADER_DVLINNCOUKPREAMP4
#define HEADER_DVLINNCOUKPREAMP4

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
 * Provider for the linn.co.uk:Preamp:4 UPnP service
 */
class DvProviderLinnCoUkPreamp4 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkPreamp4() {}
    /**
     * Set the value of the Volume property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolume(TUint aValue);
    /**
     * Get a copy of the value of the Volume property
     */
    void GetPropertyVolume(TUint& aValue);
    /**
     * Set the value of the Mute property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMute(TBool aValue);
    /**
     * Get a copy of the value of the Mute property
     */
    void GetPropertyMute(TBool& aValue);
    /**
     * Set the value of the Balance property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBalance(TInt aValue);
    /**
     * Get a copy of the value of the Balance property
     */
    void GetPropertyBalance(TInt& aValue);
    /**
     * Set the value of the VolumeLimit property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeLimit(TUint aValue);
    /**
     * Get a copy of the value of the VolumeLimit property
     */
    void GetPropertyVolumeLimit(TUint& aValue);
    /**
     * Set the value of the StartupVolume property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStartupVolume(TUint aValue);
    /**
     * Get a copy of the value of the StartupVolume property
     */
    void GetPropertyStartupVolume(TUint& aValue);
    /**
     * Set the value of the StartupVolumeEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStartupVolumeEnabled(TBool aValue);
    /**
     * Get a copy of the value of the StartupVolumeEnabled property
     */
    void GetPropertyStartupVolumeEnabled(TBool& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkPreamp4(DvDevice& aDevice);
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
    virtual void VolumeInc(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * VolumeDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeDec action for the owning device.
     * Must be implemented iff EnableActionVolumeDec was called.
     */
    virtual void VolumeDec(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolume);
    /**
     * Volume action.
     *
     * Will be called when the device stack receives an invocation of the
     * Volume action for the owning device.
     * Must be implemented iff EnableActionVolume was called.
     */
    virtual void Volume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolume);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(IInvocationResponse& aResponse, TUint aVersion, TBool aaMute);
    /**
     * Mute action.
     *
     * Will be called when the device stack receives an invocation of the
     * Mute action for the owning device.
     * Must be implemented iff EnableActionMute was called.
     */
    virtual void Mute(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaMute);
    /**
     * SetBalance action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBalance action for the owning device.
     * Must be implemented iff EnableActionSetBalance was called.
     */
    virtual void SetBalance(IInvocationResponse& aResponse, TUint aVersion, TInt aaBalance);
    /**
     * Balance action.
     *
     * Will be called when the device stack receives an invocation of the
     * Balance action for the owning device.
     * Must be implemented iff EnableActionBalance was called.
     */
    virtual void Balance(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aaBalance);
    /**
     * SetVolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolumeLimit action for the owning device.
     * Must be implemented iff EnableActionSetVolumeLimit was called.
     */
    virtual void SetVolumeLimit(IInvocationResponse& aResponse, TUint aVersion, TUint aaVolumeLimit);
    /**
     * VolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeLimit action for the owning device.
     * Must be implemented iff EnableActionVolumeLimit was called.
     */
    virtual void VolumeLimit(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaVolumeLimit);
    /**
     * SetStartupVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupVolume action for the owning device.
     * Must be implemented iff EnableActionSetStartupVolume was called.
     */
    virtual void SetStartupVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aaStartupVolume);
    /**
     * StartupVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupVolume action for the owning device.
     * Must be implemented iff EnableActionStartupVolume was called.
     */
    virtual void StartupVolume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStartupVolume);
    /**
     * SetStartupVolumeEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupVolumeEnabled action for the owning device.
     * Must be implemented iff EnableActionSetStartupVolumeEnabled was called.
     */
    virtual void SetStartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupVolumeEnabled);
    /**
     * StartupVolumeEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupVolumeEnabled action for the owning device.
     * Must be implemented iff EnableActionStartupVolumeEnabled was called.
     */
    virtual void StartupVolumeEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupVolumeEnabled);
private:
    DvProviderLinnCoUkPreamp4();
    void DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupVolumeEnabled(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyStartupVolume;
    PropertyBool* iPropertyStartupVolumeEnabled;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPREAMP4

