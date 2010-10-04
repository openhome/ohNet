#ifndef HEADER_DVUPNPORGRENDERINGCONTROL2
#define HEADER_DVUPNPORGRENDERINGCONTROL2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:RenderingControl:2
 */
class DvServiceUpnpOrgRenderingControl2 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgRenderingControl2() {}
    void SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
protected:
    DvServiceUpnpOrgRenderingControl2(DvDevice& aDevice);
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
    void EnableActionGetStateVariables();
    void EnableActionSetStateVariables();
private:
    virtual void ListPresets(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentPresetNameList);
    virtual void SelectPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aPresetName);
    virtual void GetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBrightness);
    virtual void SetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBrightness);
    virtual void GetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentContrast);
    virtual void SetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredContrast);
    virtual void GetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentSharpness);
    virtual void SetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredSharpness);
    virtual void GetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoGain);
    virtual void SetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoGain);
    virtual void GetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoGain);
    virtual void SetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoGain);
    virtual void GetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoGain);
    virtual void SetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoGain);
    virtual void GetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoBlackLevel);
    virtual void SetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoBlackLevel);
    virtual void GetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoBlackLevel);
    virtual void SetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel);
    virtual void GetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoBlackLevel);
    virtual void SetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel);
    virtual void GetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentColorTemperature);
    virtual void SetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredColorTemperature);
    virtual void GetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentHorizontalKeystone);
    virtual void SetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredHorizontalKeystone);
    virtual void GetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentVerticalKeystone);
    virtual void SetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredVerticalKeystone);
    virtual void GetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentMute);
    virtual void SetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute);
    virtual void GetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseUint& aCurrentVolume);
    virtual void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume);
    virtual void GetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aCurrentVolume);
    virtual void SetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume);
    virtual void GetVolumeDBRange(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aMinValue, IInvocationResponseInt& aMaxValue);
    virtual void GetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentLoudness);
    virtual void SetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness);
    virtual void GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs);
    virtual void SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList);
private:
    DvServiceUpnpOrgRenderingControl2();
    void DoListPresets(IDvInvocation& aInvocation, TUint aVersion);
    void DoSelectPreset(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetBrightness(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBrightness(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetContrast(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetContrast(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetSharpness(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetSharpness(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetColorTemperature(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetColorTemperature(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetMute(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetVolume(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetVolumeDB(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeDB(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetVolumeDBRange(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetLoudness(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetLoudness(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetStateVariables(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariables(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGRENDERINGCONTROL2

