#ifndef HEADER_DVUPNPORGRENDERINGCONTROL2CPP
#define HEADER_DVUPNPORGRENDERINGCONTROL2CPP

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
 * Provider for the upnp.org:RenderingControl:2 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgRenderingControl2Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgRenderingControl2Cpp() {}
    /**
     * Set the value of the LastChange property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLastChange(const std::string& aValue);
    /**
     * Get a copy of the value of the LastChange property
     */
    void GetPropertyLastChange(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgRenderingControl2Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action ListPresets is supported.
     * The action's availability will be published in the device's service.xml.
     * DoListPresets must be overridden if this is called.
     */
    void EnableActionListPresets();
    /**
     * Signal that the action SelectPreset is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSelectPreset must be overridden if this is called.
     */
    void EnableActionSelectPreset();
    /**
     * Signal that the action GetBrightness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetBrightness must be overridden if this is called.
     */
    void EnableActionGetBrightness();
    /**
     * Signal that the action SetBrightness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetBrightness must be overridden if this is called.
     */
    void EnableActionSetBrightness();
    /**
     * Signal that the action GetContrast is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetContrast must be overridden if this is called.
     */
    void EnableActionGetContrast();
    /**
     * Signal that the action SetContrast is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetContrast must be overridden if this is called.
     */
    void EnableActionSetContrast();
    /**
     * Signal that the action GetSharpness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetSharpness must be overridden if this is called.
     */
    void EnableActionGetSharpness();
    /**
     * Signal that the action SetSharpness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetSharpness must be overridden if this is called.
     */
    void EnableActionSetSharpness();
    /**
     * Signal that the action GetRedVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetRedVideoGain must be overridden if this is called.
     */
    void EnableActionGetRedVideoGain();
    /**
     * Signal that the action SetRedVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetRedVideoGain must be overridden if this is called.
     */
    void EnableActionSetRedVideoGain();
    /**
     * Signal that the action GetGreenVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetGreenVideoGain must be overridden if this is called.
     */
    void EnableActionGetGreenVideoGain();
    /**
     * Signal that the action SetGreenVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetGreenVideoGain must be overridden if this is called.
     */
    void EnableActionSetGreenVideoGain();
    /**
     * Signal that the action GetBlueVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetBlueVideoGain must be overridden if this is called.
     */
    void EnableActionGetBlueVideoGain();
    /**
     * Signal that the action SetBlueVideoGain is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetBlueVideoGain must be overridden if this is called.
     */
    void EnableActionSetBlueVideoGain();
    /**
     * Signal that the action GetRedVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetRedVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionGetRedVideoBlackLevel();
    /**
     * Signal that the action SetRedVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetRedVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionSetRedVideoBlackLevel();
    /**
     * Signal that the action GetGreenVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetGreenVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionGetGreenVideoBlackLevel();
    /**
     * Signal that the action SetGreenVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetGreenVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionSetGreenVideoBlackLevel();
    /**
     * Signal that the action GetBlueVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetBlueVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionGetBlueVideoBlackLevel();
    /**
     * Signal that the action SetBlueVideoBlackLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetBlueVideoBlackLevel must be overridden if this is called.
     */
    void EnableActionSetBlueVideoBlackLevel();
    /**
     * Signal that the action GetColorTemperature is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetColorTemperature must be overridden if this is called.
     */
    void EnableActionGetColorTemperature();
    /**
     * Signal that the action SetColorTemperature is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetColorTemperature must be overridden if this is called.
     */
    void EnableActionSetColorTemperature();
    /**
     * Signal that the action GetHorizontalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetHorizontalKeystone must be overridden if this is called.
     */
    void EnableActionGetHorizontalKeystone();
    /**
     * Signal that the action SetHorizontalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetHorizontalKeystone must be overridden if this is called.
     */
    void EnableActionSetHorizontalKeystone();
    /**
     * Signal that the action GetVerticalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetVerticalKeystone must be overridden if this is called.
     */
    void EnableActionGetVerticalKeystone();
    /**
     * Signal that the action SetVerticalKeystone is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetVerticalKeystone must be overridden if this is called.
     */
    void EnableActionSetVerticalKeystone();
    /**
     * Signal that the action GetMute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetMute must be overridden if this is called.
     */
    void EnableActionGetMute();
    /**
     * Signal that the action SetMute is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetMute must be overridden if this is called.
     */
    void EnableActionSetMute();
    /**
     * Signal that the action GetVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetVolume must be overridden if this is called.
     */
    void EnableActionGetVolume();
    /**
     * Signal that the action SetVolume is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetVolume must be overridden if this is called.
     */
    void EnableActionSetVolume();
    /**
     * Signal that the action GetVolumeDB is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetVolumeDB must be overridden if this is called.
     */
    void EnableActionGetVolumeDB();
    /**
     * Signal that the action SetVolumeDB is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetVolumeDB must be overridden if this is called.
     */
    void EnableActionSetVolumeDB();
    /**
     * Signal that the action GetVolumeDBRange is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetVolumeDBRange must be overridden if this is called.
     */
    void EnableActionGetVolumeDBRange();
    /**
     * Signal that the action GetLoudness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetLoudness must be overridden if this is called.
     */
    void EnableActionGetLoudness();
    /**
     * Signal that the action SetLoudness is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetLoudness must be overridden if this is called.
     */
    void EnableActionSetLoudness();
    /**
     * Signal that the action GetStateVariables is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetStateVariables must be overridden if this is called.
     */
    void EnableActionGetStateVariables();
    /**
     * Signal that the action SetStateVariables is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStateVariables must be overridden if this is called.
     */
    void EnableActionSetStateVariables();
private:
    /**
     * ListPresets action.
     *
     * Will be called when the device stack receives an invocation of the
     * ListPresets action for the owning device.
     * Must be implemented iff EnableActionListPresets was called.
     */
    virtual void ListPresets(uint32_t aVersion, uint32_t aInstanceID, std::string& aCurrentPresetNameList);
    /**
     * SelectPreset action.
     *
     * Will be called when the device stack receives an invocation of the
     * SelectPreset action for the owning device.
     * Must be implemented iff EnableActionSelectPreset was called.
     */
    virtual void SelectPreset(uint32_t aVersion, uint32_t aInstanceID, const std::string& aPresetName);
    /**
     * GetBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBrightness action for the owning device.
     * Must be implemented iff EnableActionGetBrightness was called.
     */
    virtual void GetBrightness(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentBrightness);
    /**
     * SetBrightness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBrightness action for the owning device.
     * Must be implemented iff EnableActionSetBrightness was called.
     */
    virtual void SetBrightness(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
    /**
     * GetContrast action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetContrast action for the owning device.
     * Must be implemented iff EnableActionGetContrast was called.
     */
    virtual void GetContrast(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentContrast);
    /**
     * SetContrast action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetContrast action for the owning device.
     * Must be implemented iff EnableActionSetContrast was called.
     */
    virtual void SetContrast(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
    /**
     * GetSharpness action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSharpness action for the owning device.
     * Must be implemented iff EnableActionGetSharpness was called.
     */
    virtual void GetSharpness(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentSharpness);
    /**
     * SetSharpness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSharpness action for the owning device.
     * Must be implemented iff EnableActionSetSharpness was called.
     */
    virtual void SetSharpness(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
    /**
     * GetRedVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRedVideoGain action for the owning device.
     * Must be implemented iff EnableActionGetRedVideoGain was called.
     */
    virtual void GetRedVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentRedVideoGain);
    /**
     * SetRedVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRedVideoGain action for the owning device.
     * Must be implemented iff EnableActionSetRedVideoGain was called.
     */
    virtual void SetRedVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
    /**
     * GetGreenVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetGreenVideoGain action for the owning device.
     * Must be implemented iff EnableActionGetGreenVideoGain was called.
     */
    virtual void GetGreenVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentGreenVideoGain);
    /**
     * SetGreenVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetGreenVideoGain action for the owning device.
     * Must be implemented iff EnableActionSetGreenVideoGain was called.
     */
    virtual void SetGreenVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
    /**
     * GetBlueVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBlueVideoGain action for the owning device.
     * Must be implemented iff EnableActionGetBlueVideoGain was called.
     */
    virtual void GetBlueVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentBlueVideoGain);
    /**
     * SetBlueVideoGain action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBlueVideoGain action for the owning device.
     * Must be implemented iff EnableActionSetBlueVideoGain was called.
     */
    virtual void SetBlueVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
    /**
     * GetRedVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetRedVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionGetRedVideoBlackLevel was called.
     */
    virtual void GetRedVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentRedVideoBlackLevel);
    /**
     * SetRedVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRedVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionSetRedVideoBlackLevel was called.
     */
    virtual void SetRedVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
    /**
     * GetGreenVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetGreenVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionGetGreenVideoBlackLevel was called.
     */
    virtual void GetGreenVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentGreenVideoBlackLevel);
    /**
     * SetGreenVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetGreenVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionSetGreenVideoBlackLevel was called.
     */
    virtual void SetGreenVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
    /**
     * GetBlueVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetBlueVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionGetBlueVideoBlackLevel was called.
     */
    virtual void GetBlueVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentBlueVideoBlackLevel);
    /**
     * SetBlueVideoBlackLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetBlueVideoBlackLevel action for the owning device.
     * Must be implemented iff EnableActionSetBlueVideoBlackLevel was called.
     */
    virtual void SetBlueVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
    /**
     * GetColorTemperature action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetColorTemperature action for the owning device.
     * Must be implemented iff EnableActionGetColorTemperature was called.
     */
    virtual void GetColorTemperature(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentColorTemperature);
    /**
     * SetColorTemperature action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetColorTemperature action for the owning device.
     * Must be implemented iff EnableActionSetColorTemperature was called.
     */
    virtual void SetColorTemperature(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
    /**
     * GetHorizontalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetHorizontalKeystone action for the owning device.
     * Must be implemented iff EnableActionGetHorizontalKeystone was called.
     */
    virtual void GetHorizontalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t& aCurrentHorizontalKeystone);
    /**
     * SetHorizontalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetHorizontalKeystone action for the owning device.
     * Must be implemented iff EnableActionSetHorizontalKeystone was called.
     */
    virtual void SetHorizontalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
    /**
     * GetVerticalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVerticalKeystone action for the owning device.
     * Must be implemented iff EnableActionGetVerticalKeystone was called.
     */
    virtual void GetVerticalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t& aCurrentVerticalKeystone);
    /**
     * SetVerticalKeystone action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVerticalKeystone action for the owning device.
     * Must be implemented iff EnableActionSetVerticalKeystone was called.
     */
    virtual void SetVerticalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
    /**
     * GetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetMute action for the owning device.
     * Must be implemented iff EnableActionGetMute was called.
     */
    virtual void GetMute(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute);
    /**
     * SetMute action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     * Must be implemented iff EnableActionSetMute was called.
     */
    virtual void SetMute(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute);
    /**
     * GetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVolume action for the owning device.
     * Must be implemented iff EnableActionGetVolume was called.
     */
    virtual void GetVolume(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume);
    /**
     * SetVolume action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     * Must be implemented iff EnableActionSetVolume was called.
     */
    virtual void SetVolume(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume);
    /**
     * GetVolumeDB action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVolumeDB action for the owning device.
     * Must be implemented iff EnableActionGetVolumeDB was called.
     */
    virtual void GetVolumeDB(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, int32_t& aCurrentVolume);
    /**
     * SetVolumeDB action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetVolumeDB action for the owning device.
     * Must be implemented iff EnableActionSetVolumeDB was called.
     */
    virtual void SetVolumeDB(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume);
    /**
     * GetVolumeDBRange action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetVolumeDBRange action for the owning device.
     * Must be implemented iff EnableActionGetVolumeDBRange was called.
     */
    virtual void GetVolumeDBRange(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, int32_t& aMinValue, int32_t& aMaxValue);
    /**
     * GetLoudness action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLoudness action for the owning device.
     * Must be implemented iff EnableActionGetLoudness was called.
     */
    virtual void GetLoudness(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentLoudness);
    /**
     * SetLoudness action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetLoudness action for the owning device.
     * Must be implemented iff EnableActionSetLoudness was called.
     */
    virtual void SetLoudness(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness);
    /**
     * GetStateVariables action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetStateVariables action for the owning device.
     * Must be implemented iff EnableActionGetStateVariables was called.
     */
    virtual void GetStateVariables(uint32_t aVersion, uint32_t aInstanceID, const std::string& aStateVariableList, std::string& aStateVariableValuePairs);
    /**
     * SetStateVariables action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStateVariables action for the owning device.
     * Must be implemented iff EnableActionSetStateVariables was called.
     */
    virtual void SetStateVariables(uint32_t aVersion, uint32_t aInstanceID, const std::string& aRenderingControlUDN, const std::string& aServiceType, const std::string& aServiceId, const std::string& aStateVariableValuePairs, std::string& aStateVariableList);
private:
    DvProviderUpnpOrgRenderingControl2Cpp();
    void DoListPresets(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSelectPreset(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetBrightness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBrightness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetContrast(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetContrast(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetSharpness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSharpness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRedVideoGain(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRedVideoGain(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetGreenVideoGain(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetGreenVideoGain(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetBlueVideoGain(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBlueVideoGain(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColorTemperature(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetColorTemperature(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetHorizontalKeystone(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetHorizontalKeystone(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetVerticalKeystone(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVerticalKeystone(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetMute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetMute(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetVolumeDB(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeDB(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetVolumeDBRange(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetLoudness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetLoudness(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetStateVariables(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStateVariables(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGRENDERINGCONTROL2CPP

