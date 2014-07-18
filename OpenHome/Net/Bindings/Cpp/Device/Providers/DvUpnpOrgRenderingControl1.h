#ifndef HEADER_DVUPNPORGRENDERINGCONTROL1CPP
#define HEADER_DVUPNPORGRENDERINGCONTROL1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

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
 * Provider for the upnp.org:RenderingControl:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgRenderingControl1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgRenderingControl1Cpp() {}
    /**
     * Set the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLastChange(const std::string& aValue);
    /**
     * Get a copy of the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     */
    void GetPropertyLastChange(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgRenderingControl1Cpp(DvDeviceStd& aDevice);
    /**
     * Enable the LastChange property.
     */
    void EnablePropertyLastChange();
    /**
     * Signal that the action ListPresets is supported.
     * The action's availability will be published in the device's service.xml.
     * ListPresets must be overridden if this is called.
     */
    void EnableActionListPresets();
    /**
     * Signal that the action SelectPreset is supported.
     * The action's availability will be published in the device's service.xml.
     * SelectPreset must be overridden if this is called.
     */
    void EnableActionSelectPreset();
    /**
     * Signal that the action GetBrightness is supported.
     * The action's availability will be published in the device's service.xml.
     * GetBrightness must be overridden if this is called.
     */
    void EnableActionGetBrightness();
    /**
     * Signal that the action SetBrightness is supported.
     * The action's availability will be published in the device's service.xml.
     * SetBrightness must be overridden if this is called.
     */
    void EnableActionSetBrightness();
    /**
     * Signal that the action GetContrast is supported.
     * The action's availability will be published in the device's service.xml.
     * GetContrast must be overridden if this is called.
     */
    void EnableActionGetContrast();
    /**
     * Signal that the action SetContrast is supported.
     * The action's availability will be published in the device's service.xml.
     * SetContrast must be overridden if this is called.
     */
    void EnableActionSetContrast();
    /**
     * Signal that the action GetSharpness is supported.
     * The action's availability will be published in the device's service.xml.
     * GetSharpness must be overridden if this is called.
     */
    void EnableActionGetSharpness();
    /**
     * Signal that the action SetSharpness is supported.
     * The action's availability will be published in the device's service.xml.
     * SetSharpness must be overridden if this is called.
     */
    void EnableActionSetSharpness();
    /**
     * Signal that the action GetRedVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRedVideoGain must be overridden if this is called.
     */
    void EnableActionGetRedVideoGain();
    /**
     * Signal that the action SetRedVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * SetRedVideoGain must be overridden if this is called.
     */
    void EnableActionSetRedVideoGain();
    /**
     * Signal that the action GetGreenVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * GetGreenVideoGain must be overridden if this is called.
     */
    void EnableActionGetGreenVideoGain();
    /**
     * Signal that the action SetGreenVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * SetGreenVideoGain must be overridden if this is called.
     */
    void EnableActionSetGreenVideoGain();
    /**
     * Signal that the action GetBlueVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * GetBlueVideoGain must be overridden if this is called.
     */
    void EnableActionGetBlueVideoGain();
    /**
     * Signal that the action SetBlueVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * SetBlueVideoGain must be overridden if this is called.
     */
    void EnableActionSetBlueVideoGain();
    /**
     * Signal that the action GetRedVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * GetRedVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionGetRedVideoBlackLevel();
    /**
     * Signal that the action SetRedVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetRedVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionSetRedVideoBlackLevel();
    /**
     * Signal that the action GetGreenVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * GetGreenVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionGetGreenVideoBlackLevel();
    /**
     * Signal that the action SetGreenVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetGreenVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionSetGreenVideoBlackLevel();
    /**
     * Signal that the action GetBlueVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * GetBlueVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionGetBlueVideoBlackLevel();
    /**
     * Signal that the action SetBlueVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetBlueVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionSetBlueVideoBlackLevel();
    /**
     * Signal that the action GetColorTemperature is supported.
     * The action's availability will be published in the device's service.xml.
     * GetColorTemperature must be overridden if this is called.
     */
    void EnableActionGetColorTemperature();
    /**
     * Signal that the action SetColorTemperature is supported.
     * The action's availability will be published in the device's service.xml.
     * SetColorTemperature must be overridden if this is called.
     */
    void EnableActionSetColorTemperature();
    /**
     * Signal that the action GetHorizontalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * GetHorizontalKeystone must be overridden if this is called.
     */
    void EnableActionGetHorizontalKeystone();
    /**
     * Signal that the action SetHorizontalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * SetHorizontalKeystone must be overridden if this is called.
     */
    void EnableActionSetHorizontalKeystone();
    /**
     * Signal that the action GetVerticalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * GetVerticalKeystone must be overridden if this is called.
     */
    void EnableActionGetVerticalKeystone();
    /**
     * Signal that the action SetVerticalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * SetVerticalKeystone must be overridden if this is called.
     */
    void EnableActionSetVerticalKeystone();
    /**
     * Signal that the action GetMute is supported.
     * The action's availability will be published in the device's service.xml.
     * GetMute must be overridden if this is called.
     */
    void EnableActionGetMute();
    /**
     * Signal that the action SetMute is supported.
     * The action's availability will be published in the device's service.xml.
     * SetMute must be overridden if this is called.
     */
    void EnableActionSetMute();
    /**
     * Signal that the action GetVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * GetVolume must be overridden if this is called.
     */
    void EnableActionGetVolume();
    /**
     * Signal that the action SetVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * SetVolume must be overridden if this is called.
     */
    void EnableActionSetVolume();
    /**
     * Signal that the action GetVolumeDB is supported.
     * The action's availability will be published in the device's service.xml.
     * GetVolumeDB must be overridden if this is called.
     */
    void EnableActionGetVolumeDB();
    /**
     * Signal that the action SetVolumeDB is supported.
     * The action's availability will be published in the device's service.xml.
     * SetVolumeDB must be overridden if this is called.
     */
    void EnableActionSetVolumeDB();
    /**
     * Signal that the action GetVolumeDBRange is supported.
     * The action's availability will be published in the device's service.xml.
     * GetVolumeDBRange must be overridden if this is called.
     */
    void EnableActionGetVolumeDBRange();
    /**
     * Signal that the action GetLoudness is supported.
     * The action's availability will be published in the device's service.xml.
     * GetLoudness must be overridden if this is called.
     */
    void EnableActionGetLoudness();
    /**
     * Signal that the action SetLoudness is supported.
     * The action's availability will be published in the device's service.xml.
     * SetLoudness must be overridden if this is called.
     */
    void EnableActionSetLoudness();
private:
    /**
     * ListPresets action.
     *
     * Will be called when the device stack receives an invocation of the
     * ListPresets action for the owning device.
     * Must be implemented iff EnableActionListPresets was called.
     */
    virtual void ListPresets(IDvInvocationStd& aInvocation, uint32_t aInstanceID, std::string& aCurrentPresetNameList);
    /**
     * SelectPreset action.
     *
     * Will be called when the device stack receives an invocation of the
     * SelectPreset action for the owning device.
     * Must be implemented iff EnableActionSelectPreset was called.
     */
    virtual void SelectPreset(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aPresetName);
    /**
     * GetBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBrightness action for the owning device.
     * Must be implemented iff EnableActionGetBrightness was called.
     */
    virtual void GetBrightness(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentBrightness);
    /**
     * SetBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBrightness action for the owning device.
     * Must be implemented iff EnableActionSetBrightness was called.
     */
    virtual void SetBrightness(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredBrightness);
    /**
     * GetContrast action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetContrast action for the owning device.
     * Must be implemented iff EnableActionGetContrast was called.
     */
    virtual void GetContrast(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentContrast);
    /**
     * SetContrast action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetContrast action for the owning device.
     * Must be implemented iff EnableActionSetContrast was called.
     */
    virtual void SetContrast(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredContrast);
    /**
     * GetSharpness action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSharpness action for the owning device.
     * Must be implemented iff EnableActionGetSharpness was called.
     */
    virtual void GetSharpness(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentSharpness);
    /**
     * SetSharpness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSharpness action for the owning device.
     * Must be implemented iff EnableActionSetSharpness was called.
     */
    virtual void SetSharpness(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredSharpness);
    /**
     * GetRedVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRedVideoGain action for the owning device.
     * Must be implemented iff EnableActionGetRedVideoGain was called.
     */
    virtual void GetRedVideoGain(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentRedVideoGain);
    /**
     * SetRedVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRedVideoGain action for the owning device.
     * Must be implemented iff EnableActionSetRedVideoGain was called.
     */
    virtual void SetRedVideoGain(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
    /**
     * GetGreenVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetGreenVideoGain action for the owning device.
     * Must be implemented iff EnableActionGetGreenVideoGain was called.
     */
    virtual void GetGreenVideoGain(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentGreenVideoGain);
    /**
     * SetGreenVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetGreenVideoGain action for the owning device.
     * Must be implemented iff EnableActionSetGreenVideoGain was called.
     */
    virtual void SetGreenVideoGain(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
    /**
     * GetBlueVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBlueVideoGain action for the owning device.
     * Must be implemented iff EnableActionGetBlueVideoGain was called.
     */
    virtual void GetBlueVideoGain(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentBlueVideoGain);
    /**
     * SetBlueVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBlueVideoGain action for the owning device.
     * Must be implemented iff EnableActionSetBlueVideoGain was called.
     */
    virtual void SetBlueVideoGain(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
    /**
     * GetRedVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRedVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionGetRedVideoBlackLevel was called.
     */
    virtual void GetRedVideoBlackLevel(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentRedVideoBlackLevel);
    /**
     * SetRedVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRedVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionSetRedVideoBlackLevel was called.
     */
    virtual void SetRedVideoBlackLevel(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
    /**
     * GetGreenVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetGreenVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionGetGreenVideoBlackLevel was called.
     */
    virtual void GetGreenVideoBlackLevel(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentGreenVideoBlackLevel);
    /**
     * SetGreenVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetGreenVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionSetGreenVideoBlackLevel was called.
     */
    virtual void SetGreenVideoBlackLevel(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
    /**
     * GetBlueVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBlueVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionGetBlueVideoBlackLevel was called.
     */
    virtual void GetBlueVideoBlackLevel(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentBlueVideoBlackLevel);
    /**
     * SetBlueVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBlueVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionSetBlueVideoBlackLevel was called.
     */
    virtual void SetBlueVideoBlackLevel(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
    /**
     * GetColorTemperature action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColorTemperature action for the owning device.
     * Must be implemented iff EnableActionGetColorTemperature was called.
     */
    virtual void GetColorTemperature(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t& aCurrentColorTemperature);
    /**
     * SetColorTemperature action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColorTemperature action for the owning device.
     * Must be implemented iff EnableActionSetColorTemperature was called.
     */
    virtual void SetColorTemperature(IDvInvocationStd& aInvocation, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
    /**
     * GetHorizontalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetHorizontalKeystone action for the owning device.
     * Must be implemented iff EnableActionGetHorizontalKeystone was called.
     */
    virtual void GetHorizontalKeystone(IDvInvocationStd& aInvocation, uint32_t aInstanceID, int32_t& aCurrentHorizontalKeystone);
    /**
     * SetHorizontalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetHorizontalKeystone action for the owning device.
     * Must be implemented iff EnableActionSetHorizontalKeystone was called.
     */
    virtual void SetHorizontalKeystone(IDvInvocationStd& aInvocation, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
    /**
     * GetVerticalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVerticalKeystone action for the owning device.
     * Must be implemented iff EnableActionGetVerticalKeystone was called.
     */
    virtual void GetVerticalKeystone(IDvInvocationStd& aInvocation, uint32_t aInstanceID, int32_t& aCurrentVerticalKeystone);
    /**
     * SetVerticalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVerticalKeystone action for the owning device.
     * Must be implemented iff EnableActionSetVerticalKeystone was called.
     */
    virtual void SetVerticalKeystone(IDvInvocationStd& aInvocation, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
    /**
     * GetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMute action for the owning device.
     * Must be implemented iff EnableActionGetMute was called.
     */
    virtual void GetMute(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute);
    /**
     * GetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVolume action for the owning device.
     * Must be implemented iff EnableActionGetVolume was called.
     */
    virtual void GetVolume(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume);
    /**
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume);
    /**
     * GetVolumeDB action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVolumeDB action for the owning device.
     * Must be implemented iff EnableActionGetVolumeDB was called.
     */
    virtual void GetVolumeDB(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, int32_t& aCurrentVolume);
    /**
     * SetVolumeDB action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolumeDB action for the owning device.
     * Must be implemented iff EnableActionSetVolumeDB was called.
     */
    virtual void SetVolumeDB(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume);
    /**
     * GetVolumeDBRange action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVolumeDBRange action for the owning device.
     * Must be implemented iff EnableActionGetVolumeDBRange was called.
     */
    virtual void GetVolumeDBRange(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, int32_t& aMinValue, int32_t& aMaxValue);
    /**
     * GetLoudness action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLoudness action for the owning device.
     * Must be implemented iff EnableActionGetLoudness was called.
     */
    virtual void GetLoudness(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentLoudness);
    /**
     * SetLoudness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetLoudness action for the owning device.
     * Must be implemented iff EnableActionSetLoudness was called.
     */
    virtual void SetLoudness(IDvInvocationStd& aInvocation, uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness);
private:
    DvProviderUpnpOrgRenderingControl1Cpp();
    void DoListPresets(IDviInvocation& aInvocation);
    void DoSelectPreset(IDviInvocation& aInvocation);
    void DoGetBrightness(IDviInvocation& aInvocation);
    void DoSetBrightness(IDviInvocation& aInvocation);
    void DoGetContrast(IDviInvocation& aInvocation);
    void DoSetContrast(IDviInvocation& aInvocation);
    void DoGetSharpness(IDviInvocation& aInvocation);
    void DoSetSharpness(IDviInvocation& aInvocation);
    void DoGetRedVideoGain(IDviInvocation& aInvocation);
    void DoSetRedVideoGain(IDviInvocation& aInvocation);
    void DoGetGreenVideoGain(IDviInvocation& aInvocation);
    void DoSetGreenVideoGain(IDviInvocation& aInvocation);
    void DoGetBlueVideoGain(IDviInvocation& aInvocation);
    void DoSetBlueVideoGain(IDviInvocation& aInvocation);
    void DoGetRedVideoBlackLevel(IDviInvocation& aInvocation);
    void DoSetRedVideoBlackLevel(IDviInvocation& aInvocation);
    void DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation);
    void DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation);
    void DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation);
    void DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation);
    void DoGetColorTemperature(IDviInvocation& aInvocation);
    void DoSetColorTemperature(IDviInvocation& aInvocation);
    void DoGetHorizontalKeystone(IDviInvocation& aInvocation);
    void DoSetHorizontalKeystone(IDviInvocation& aInvocation);
    void DoGetVerticalKeystone(IDviInvocation& aInvocation);
    void DoSetVerticalKeystone(IDviInvocation& aInvocation);
    void DoGetMute(IDviInvocation& aInvocation);
    void DoSetMute(IDviInvocation& aInvocation);
    void DoGetVolume(IDviInvocation& aInvocation);
    void DoSetVolume(IDviInvocation& aInvocation);
    void DoGetVolumeDB(IDviInvocation& aInvocation);
    void DoSetVolumeDB(IDviInvocation& aInvocation);
    void DoGetVolumeDBRange(IDviInvocation& aInvocation);
    void DoGetLoudness(IDviInvocation& aInvocation);
    void DoSetLoudness(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGRENDERINGCONTROL1CPP

