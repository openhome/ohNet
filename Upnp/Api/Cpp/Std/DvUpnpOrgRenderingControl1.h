#ifndef HEADER_DVUPNPORGRENDERINGCONTROL1CPP
#define HEADER_DVUPNPORGRENDERINGCONTROL1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:RenderingControl:1
 */
class DvServiceUpnpOrgRenderingControl1Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgRenderingControl1Cpp() {}
    void SetPropertyLastChange(const std::string& aValue);
    void GetPropertyLastChange(std::string& aValue);
protected:
    DvServiceUpnpOrgRenderingControl1Cpp(DvDeviceStd& aDevice);
    void EnableActionListPresets();
    void EnableActionSelectPreset();
    void EnableActionGetBrightness();
    void EnableActionSetBrightness();
    void EnableActionGetContrast();
    void EnableActionSetContrast();
    void EnableActionGetSharpness();
    void EnableActionSetSharpness();
    void EnableActionGetRedVideoGain();
    void EnableActionSetRedVideoGain();
    void EnableActionGetGreenVideoGain();
    void EnableActionSetGreenVideoGain();
    void EnableActionGetBlueVideoGain();
    void EnableActionSetBlueVideoGain();
    void EnableActionGetRedVideoBlackLevel();
    void EnableActionSetRedVideoBlackLevel();
    void EnableActionGetGreenVideoBlackLevel();
    void EnableActionSetGreenVideoBlackLevel();
    void EnableActionGetBlueVideoBlackLevel();
    void EnableActionSetBlueVideoBlackLevel();
    void EnableActionGetColorTemperature();
    void EnableActionSetColorTemperature();
    void EnableActionGetHorizontalKeystone();
    void EnableActionSetHorizontalKeystone();
    void EnableActionGetVerticalKeystone();
    void EnableActionSetVerticalKeystone();
    void EnableActionGetMute();
    void EnableActionSetMute();
    void EnableActionGetVolume();
    void EnableActionSetVolume();
    void EnableActionGetVolumeDB();
    void EnableActionSetVolumeDB();
    void EnableActionGetVolumeDBRange();
    void EnableActionGetLoudness();
    void EnableActionSetLoudness();
private:
    virtual void ListPresets(uint32_t aVersion, uint32_t aInstanceID, std::string& aCurrentPresetNameList);
    virtual void SelectPreset(uint32_t aVersion, uint32_t aInstanceID, const std::string& aPresetName);
    virtual void GetBrightness(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentBrightness);
    virtual void SetBrightness(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBrightness);
    virtual void GetContrast(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentContrast);
    virtual void SetContrast(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredContrast);
    virtual void GetSharpness(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentSharpness);
    virtual void SetSharpness(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredSharpness);
    virtual void GetRedVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentRedVideoGain);
    virtual void SetRedVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
    virtual void GetGreenVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentGreenVideoGain);
    virtual void SetGreenVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
    virtual void GetBlueVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentBlueVideoGain);
    virtual void SetBlueVideoGain(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
    virtual void GetRedVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentRedVideoBlackLevel);
    virtual void SetRedVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
    virtual void GetGreenVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentGreenVideoBlackLevel);
    virtual void SetGreenVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
    virtual void GetBlueVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentBlueVideoBlackLevel);
    virtual void SetBlueVideoBlackLevel(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
    virtual void GetColorTemperature(uint32_t aVersion, uint32_t aInstanceID, uint32_t& aCurrentColorTemperature);
    virtual void SetColorTemperature(uint32_t aVersion, uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
    virtual void GetHorizontalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t& aCurrentHorizontalKeystone);
    virtual void SetHorizontalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
    virtual void GetVerticalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t& aCurrentVerticalKeystone);
    virtual void SetVerticalKeystone(uint32_t aVersion, uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
    virtual void GetMute(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute);
    virtual void SetMute(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute);
    virtual void GetVolume(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume);
    virtual void SetVolume(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume);
    virtual void GetVolumeDB(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, int32_t& aCurrentVolume);
    virtual void SetVolumeDB(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume);
    virtual void GetVolumeDBRange(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, int32_t& aMinValue, int32_t& aMaxValue);
    virtual void GetLoudness(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentLoudness);
    virtual void SetLoudness(uint32_t aVersion, uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness);
private:
    DvServiceUpnpOrgRenderingControl1Cpp();
    void DoListPresets(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSelectPreset(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetBrightness(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBrightness(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetContrast(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetContrast(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetSharpness(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetSharpness(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRedVideoGain(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRedVideoGain(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetGreenVideoGain(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetGreenVideoGain(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetBlueVideoGain(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBlueVideoGain(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRedVideoBlackLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRedVideoBlackLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetGreenVideoBlackLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetGreenVideoBlackLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetBlueVideoBlackLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetBlueVideoBlackLevel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetColorTemperature(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetColorTemperature(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetHorizontalKeystone(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetHorizontalKeystone(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetVerticalKeystone(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetVerticalKeystone(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetMute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetMute(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetVolume(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolume(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetVolumeDB(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetVolumeDB(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetVolumeDBRange(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetLoudness(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetLoudness(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGRENDERINGCONTROL1CPP

