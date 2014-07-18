#ifndef HEADER_DVAVOPENHOMEORGVOLUME1
#define HEADER_DVAVOPENHOMEORGVOLUME1

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
 * Provider for the av.openhome.org:Volume:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgVolume1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgVolume1() {}
    /**
     * Set the value of the Volume property
     *
     * Can only be called if EnablePropertyVolume has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolume(TUint aValue);
    /**
     * Get a copy of the value of the Volume property
     *
     * Can only be called if EnablePropertyVolume has previously been called.
     */
    void GetPropertyVolume(TUint& aValue);
    /**
     * Set the value of the Mute property
     *
     * Can only be called if EnablePropertyMute has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyMute(TBool aValue);
    /**
     * Get a copy of the value of the Mute property
     *
     * Can only be called if EnablePropertyMute has previously been called.
     */
    void GetPropertyMute(TBool& aValue);
    /**
     * Set the value of the Balance property
     *
     * Can only be called if EnablePropertyBalance has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBalance(TInt aValue);
    /**
     * Get a copy of the value of the Balance property
     *
     * Can only be called if EnablePropertyBalance has previously been called.
     */
    void GetPropertyBalance(TInt& aValue);
    /**
     * Set the value of the Fade property
     *
     * Can only be called if EnablePropertyFade has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyFade(TInt aValue);
    /**
     * Get a copy of the value of the Fade property
     *
     * Can only be called if EnablePropertyFade has previously been called.
     */
    void GetPropertyFade(TInt& aValue);
    /**
     * Set the value of the VolumeLimit property
     *
     * Can only be called if EnablePropertyVolumeLimit has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeLimit(TUint aValue);
    /**
     * Get a copy of the value of the VolumeLimit property
     *
     * Can only be called if EnablePropertyVolumeLimit has previously been called.
     */
    void GetPropertyVolumeLimit(TUint& aValue);
    /**
     * Set the value of the VolumeMax property
     *
     * Can only be called if EnablePropertyVolumeMax has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeMax(TUint aValue);
    /**
     * Get a copy of the value of the VolumeMax property
     *
     * Can only be called if EnablePropertyVolumeMax has previously been called.
     */
    void GetPropertyVolumeMax(TUint& aValue);
    /**
     * Set the value of the VolumeUnity property
     *
     * Can only be called if EnablePropertyVolumeUnity has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeUnity(TUint aValue);
    /**
     * Get a copy of the value of the VolumeUnity property
     *
     * Can only be called if EnablePropertyVolumeUnity has previously been called.
     */
    void GetPropertyVolumeUnity(TUint& aValue);
    /**
     * Set the value of the VolumeSteps property
     *
     * Can only be called if EnablePropertyVolumeSteps has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeSteps(TUint aValue);
    /**
     * Get a copy of the value of the VolumeSteps property
     *
     * Can only be called if EnablePropertyVolumeSteps has previously been called.
     */
    void GetPropertyVolumeSteps(TUint& aValue);
    /**
     * Set the value of the VolumeMilliDbPerStep property
     *
     * Can only be called if EnablePropertyVolumeMilliDbPerStep has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeMilliDbPerStep(TUint aValue);
    /**
     * Get a copy of the value of the VolumeMilliDbPerStep property
     *
     * Can only be called if EnablePropertyVolumeMilliDbPerStep has previously been called.
     */
    void GetPropertyVolumeMilliDbPerStep(TUint& aValue);
    /**
     * Set the value of the BalanceMax property
     *
     * Can only be called if EnablePropertyBalanceMax has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBalanceMax(TUint aValue);
    /**
     * Get a copy of the value of the BalanceMax property
     *
     * Can only be called if EnablePropertyBalanceMax has previously been called.
     */
    void GetPropertyBalanceMax(TUint& aValue);
    /**
     * Set the value of the FadeMax property
     *
     * Can only be called if EnablePropertyFadeMax has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyFadeMax(TUint aValue);
    /**
     * Get a copy of the value of the FadeMax property
     *
     * Can only be called if EnablePropertyFadeMax has previously been called.
     */
    void GetPropertyFadeMax(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgVolume1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgVolume1(DviDevice& aDevice);
    /**
     * Enable the Volume property.
     */
    void EnablePropertyVolume();
    /**
     * Enable the Mute property.
     */
    void EnablePropertyMute();
    /**
     * Enable the Balance property.
     */
    void EnablePropertyBalance();
    /**
     * Enable the Fade property.
     */
    void EnablePropertyFade();
    /**
     * Enable the VolumeLimit property.
     */
    void EnablePropertyVolumeLimit();
    /**
     * Enable the VolumeMax property.
     */
    void EnablePropertyVolumeMax();
    /**
     * Enable the VolumeUnity property.
     */
    void EnablePropertyVolumeUnity();
    /**
     * Enable the VolumeSteps property.
     */
    void EnablePropertyVolumeSteps();
    /**
     * Enable the VolumeMilliDbPerStep property.
     */
    void EnablePropertyVolumeMilliDbPerStep();
    /**
     * Enable the BalanceMax property.
     */
    void EnablePropertyBalanceMax();
    /**
     * Enable the FadeMax property.
     */
    void EnablePropertyFadeMax();
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
    virtual void Characteristics(IDvInvocation& aInvocation, IDvInvocationResponseUint& aVolumeMax, IDvInvocationResponseUint& aVolumeUnity, IDvInvocationResponseUint& aVolumeSteps, IDvInvocationResponseUint& aVolumeMilliDbPerStep, IDvInvocationResponseUint& aBalanceMax, IDvInvocationResponseUint& aFadeMax);
    /**
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(IDvInvocation& aInvocation, TUint aValue);
    /**
     * VolumeInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeInc action for the owning device.
     * Must be implemented iff EnableActionVolumeInc was called.
     */
    virtual void VolumeInc(IDvInvocation& aInvocation);
    /**
     * VolumeDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeDec action for the owning device.
     * Must be implemented iff EnableActionVolumeDec was called.
     */
    virtual void VolumeDec(IDvInvocation& aInvocation);
    /**
     * Volume action.
     *
     * Will be called when the device stack receives an invocation of the
     * Volume action for the owning device.
     * Must be implemented iff EnableActionVolume was called.
     */
    virtual void Volume(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * SetBalance action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBalance action for the owning device.
     * Must be implemented iff EnableActionSetBalance was called.
     */
    virtual void SetBalance(IDvInvocation& aInvocation, TInt aValue);
    /**
     * BalanceInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * BalanceInc action for the owning device.
     * Must be implemented iff EnableActionBalanceInc was called.
     */
    virtual void BalanceInc(IDvInvocation& aInvocation);
    /**
     * BalanceDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * BalanceDec action for the owning device.
     * Must be implemented iff EnableActionBalanceDec was called.
     */
    virtual void BalanceDec(IDvInvocation& aInvocation);
    /**
     * Balance action.
     *
     * Will be called when the device stack receives an invocation of the
     * Balance action for the owning device.
     * Must be implemented iff EnableActionBalance was called.
     */
    virtual void Balance(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue);
    /**
     * SetFade action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetFade action for the owning device.
     * Must be implemented iff EnableActionSetFade was called.
     */
    virtual void SetFade(IDvInvocation& aInvocation, TInt aValue);
    /**
     * FadeInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * FadeInc action for the owning device.
     * Must be implemented iff EnableActionFadeInc was called.
     */
    virtual void FadeInc(IDvInvocation& aInvocation);
    /**
     * FadeDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * FadeDec action for the owning device.
     * Must be implemented iff EnableActionFadeDec was called.
     */
    virtual void FadeDec(IDvInvocation& aInvocation);
    /**
     * Fade action.
     *
     * Will be called when the device stack receives an invocation of the
     * Fade action for the owning device.
     * Must be implemented iff EnableActionFade was called.
     */
    virtual void Fade(IDvInvocation& aInvocation, IDvInvocationResponseInt& aValue);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(IDvInvocation& aInvocation, TBool aValue);
    /**
     * Mute action.
     *
     * Will be called when the device stack receives an invocation of the
     * Mute action for the owning device.
     * Must be implemented iff EnableActionMute was called.
     */
    virtual void Mute(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue);
    /**
     * VolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeLimit action for the owning device.
     * Must be implemented iff EnableActionVolumeLimit was called.
     */
    virtual void VolumeLimit(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
private:
    DvProviderAvOpenhomeOrgVolume1();
    void Construct();
    void DoCharacteristics(IDviInvocation& aInvocation);
    void DoSetVolume(IDviInvocation& aInvocation);
    void DoVolumeInc(IDviInvocation& aInvocation);
    void DoVolumeDec(IDviInvocation& aInvocation);
    void DoVolume(IDviInvocation& aInvocation);
    void DoSetBalance(IDviInvocation& aInvocation);
    void DoBalanceInc(IDviInvocation& aInvocation);
    void DoBalanceDec(IDviInvocation& aInvocation);
    void DoBalance(IDviInvocation& aInvocation);
    void DoSetFade(IDviInvocation& aInvocation);
    void DoFadeInc(IDviInvocation& aInvocation);
    void DoFadeDec(IDviInvocation& aInvocation);
    void DoFade(IDviInvocation& aInvocation);
    void DoSetMute(IDviInvocation& aInvocation);
    void DoMute(IDviInvocation& aInvocation);
    void DoVolumeLimit(IDviInvocation& aInvocation);
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

#endif // HEADER_DVAVOPENHOMEORGVOLUME1

