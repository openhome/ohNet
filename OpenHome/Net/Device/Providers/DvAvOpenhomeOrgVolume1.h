#ifndef HEADER_DVAVOPENHOMEORGVOLUME1
#define HEADER_DVAVOPENHOMEORGVOLUME1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

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
class DvProviderAvOpenhomeOrgVolume1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgVolume1() {}
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
     * Set the value of the Fade property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyFade(TInt aValue);
    /**
     * Get a copy of the value of the Fade property
     */
    void GetPropertyFade(TInt& aValue);
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
     * Set the value of the VolumeMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeMax(TUint aValue);
    /**
     * Get a copy of the value of the VolumeMax property
     */
    void GetPropertyVolumeMax(TUint& aValue);
    /**
     * Set the value of the VolumeUnity property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeUnity(TUint aValue);
    /**
     * Get a copy of the value of the VolumeUnity property
     */
    void GetPropertyVolumeUnity(TUint& aValue);
    /**
     * Set the value of the VolumeSteps property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeSteps(TUint aValue);
    /**
     * Get a copy of the value of the VolumeSteps property
     */
    void GetPropertyVolumeSteps(TUint& aValue);
    /**
     * Set the value of the VolumeMilliDbPerStep property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyVolumeMilliDbPerStep(TUint aValue);
    /**
     * Get a copy of the value of the VolumeMilliDbPerStep property
     */
    void GetPropertyVolumeMilliDbPerStep(TUint& aValue);
    /**
     * Set the value of the BalanceMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBalanceMax(TUint aValue);
    /**
     * Get a copy of the value of the BalanceMax property
     */
    void GetPropertyBalanceMax(TUint& aValue);
    /**
     * Set the value of the FadeMax property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyFadeMax(TUint aValue);
    /**
     * Get a copy of the value of the FadeMax property
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
    virtual void Characteristics(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aVolumeMax, IInvocationResponseUint& aVolumeUnity, IInvocationResponseUint& aVolumeSteps, IInvocationResponseUint& aVolumeMilliDbPerStep, IInvocationResponseUint& aBalanceMax, IInvocationResponseUint& aFadeMax);
    /**
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aValue);
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
     * Volume action.
     *
     * Will be called when the device stack receives an invocation of the
     * Volume action for the owning device.
     * Must be implemented iff EnableActionVolume was called.
     */
    virtual void Volume(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
    /**
     * SetBalance action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBalance action for the owning device.
     * Must be implemented iff EnableActionSetBalance was called.
     */
    virtual void SetBalance(IInvocationResponse& aResponse, TUint aVersion, TInt aValue);
    /**
     * BalanceInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * BalanceInc action for the owning device.
     * Must be implemented iff EnableActionBalanceInc was called.
     */
    virtual void BalanceInc(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * BalanceDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * BalanceDec action for the owning device.
     * Must be implemented iff EnableActionBalanceDec was called.
     */
    virtual void BalanceDec(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Balance action.
     *
     * Will be called when the device stack receives an invocation of the
     * Balance action for the owning device.
     * Must be implemented iff EnableActionBalance was called.
     */
    virtual void Balance(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValue);
    /**
     * SetFade action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetFade action for the owning device.
     * Must be implemented iff EnableActionSetFade was called.
     */
    virtual void SetFade(IInvocationResponse& aResponse, TUint aVersion, TInt aValue);
    /**
     * FadeInc action.
     *
     * Will be called when the device stack receives an invocation of the
     * FadeInc action for the owning device.
     * Must be implemented iff EnableActionFadeInc was called.
     */
    virtual void FadeInc(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * FadeDec action.
     *
     * Will be called when the device stack receives an invocation of the
     * FadeDec action for the owning device.
     * Must be implemented iff EnableActionFadeDec was called.
     */
    virtual void FadeDec(IInvocationResponse& aResponse, TUint aVersion);
    /**
     * Fade action.
     *
     * Will be called when the device stack receives an invocation of the
     * Fade action for the owning device.
     * Must be implemented iff EnableActionFade was called.
     */
    virtual void Fade(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseInt& aValue);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(IInvocationResponse& aResponse, TUint aVersion, TBool aValue);
    /**
     * Mute action.
     *
     * Will be called when the device stack receives an invocation of the
     * Mute action for the owning device.
     * Must be implemented iff EnableActionMute was called.
     */
    virtual void Mute(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
    /**
     * VolumeLimit action.
     *
     * Will be called when the device stack receives an invocation of the
     * VolumeLimit action for the owning device.
     * Must be implemented iff EnableActionVolumeLimit was called.
     */
    virtual void VolumeLimit(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue);
private:
    DvProviderAvOpenhomeOrgVolume1();
    void DoCharacteristics(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoBalanceInc(IDviInvocation& aInvocation, TUint aVersion);
    void DoBalanceDec(IDviInvocation& aInvocation, TUint aVersion);
    void DoBalance(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetFade(IDviInvocation& aInvocation, TUint aVersion);
    void DoFadeInc(IDviInvocation& aInvocation, TUint aVersion);
    void DoFadeDec(IDviInvocation& aInvocation, TUint aVersion);
    void DoFade(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion);
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

