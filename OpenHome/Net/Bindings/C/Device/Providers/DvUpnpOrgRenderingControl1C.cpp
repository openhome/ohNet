#include "DvUpnpOrgRenderingControl1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderUpnpOrgRenderingControl1C : public DvProvider
{
public:
    DvProviderUpnpOrgRenderingControl1C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    void EnablePropertyLastChange();
    void EnableActionListPresets(CallbackRenderingControl1ListPresets aCallback, void* aPtr);
    void EnableActionSelectPreset(CallbackRenderingControl1SelectPreset aCallback, void* aPtr);
    void EnableActionGetBrightness(CallbackRenderingControl1GetBrightness aCallback, void* aPtr);
    void EnableActionSetBrightness(CallbackRenderingControl1SetBrightness aCallback, void* aPtr);
    void EnableActionGetContrast(CallbackRenderingControl1GetContrast aCallback, void* aPtr);
    void EnableActionSetContrast(CallbackRenderingControl1SetContrast aCallback, void* aPtr);
    void EnableActionGetSharpness(CallbackRenderingControl1GetSharpness aCallback, void* aPtr);
    void EnableActionSetSharpness(CallbackRenderingControl1SetSharpness aCallback, void* aPtr);
    void EnableActionGetRedVideoGain(CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr);
    void EnableActionSetRedVideoGain(CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr);
    void EnableActionGetGreenVideoGain(CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr);
    void EnableActionSetGreenVideoGain(CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr);
    void EnableActionGetBlueVideoGain(CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr);
    void EnableActionSetBlueVideoGain(CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr);
    void EnableActionGetRedVideoBlackLevel(CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetRedVideoBlackLevel(CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetColorTemperature(CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr);
    void EnableActionSetColorTemperature(CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr);
    void EnableActionGetHorizontalKeystone(CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionSetHorizontalKeystone(CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionGetVerticalKeystone(CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr);
    void EnableActionSetVerticalKeystone(CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr);
    void EnableActionGetMute(CallbackRenderingControl1GetMute aCallback, void* aPtr);
    void EnableActionSetMute(CallbackRenderingControl1SetMute aCallback, void* aPtr);
    void EnableActionGetVolume(CallbackRenderingControl1GetVolume aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackRenderingControl1SetVolume aCallback, void* aPtr);
    void EnableActionGetVolumeDB(CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr);
    void EnableActionSetVolumeDB(CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr);
    void EnableActionGetVolumeDBRange(CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr);
    void EnableActionGetLoudness(CallbackRenderingControl1GetLoudness aCallback, void* aPtr);
    void EnableActionSetLoudness(CallbackRenderingControl1SetLoudness aCallback, void* aPtr);
private:
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
    CallbackRenderingControl1ListPresets iCallbackListPresets;
    void* iPtrListPresets;
    CallbackRenderingControl1SelectPreset iCallbackSelectPreset;
    void* iPtrSelectPreset;
    CallbackRenderingControl1GetBrightness iCallbackGetBrightness;
    void* iPtrGetBrightness;
    CallbackRenderingControl1SetBrightness iCallbackSetBrightness;
    void* iPtrSetBrightness;
    CallbackRenderingControl1GetContrast iCallbackGetContrast;
    void* iPtrGetContrast;
    CallbackRenderingControl1SetContrast iCallbackSetContrast;
    void* iPtrSetContrast;
    CallbackRenderingControl1GetSharpness iCallbackGetSharpness;
    void* iPtrGetSharpness;
    CallbackRenderingControl1SetSharpness iCallbackSetSharpness;
    void* iPtrSetSharpness;
    CallbackRenderingControl1GetRedVideoGain iCallbackGetRedVideoGain;
    void* iPtrGetRedVideoGain;
    CallbackRenderingControl1SetRedVideoGain iCallbackSetRedVideoGain;
    void* iPtrSetRedVideoGain;
    CallbackRenderingControl1GetGreenVideoGain iCallbackGetGreenVideoGain;
    void* iPtrGetGreenVideoGain;
    CallbackRenderingControl1SetGreenVideoGain iCallbackSetGreenVideoGain;
    void* iPtrSetGreenVideoGain;
    CallbackRenderingControl1GetBlueVideoGain iCallbackGetBlueVideoGain;
    void* iPtrGetBlueVideoGain;
    CallbackRenderingControl1SetBlueVideoGain iCallbackSetBlueVideoGain;
    void* iPtrSetBlueVideoGain;
    CallbackRenderingControl1GetRedVideoBlackLevel iCallbackGetRedVideoBlackLevel;
    void* iPtrGetRedVideoBlackLevel;
    CallbackRenderingControl1SetRedVideoBlackLevel iCallbackSetRedVideoBlackLevel;
    void* iPtrSetRedVideoBlackLevel;
    CallbackRenderingControl1GetGreenVideoBlackLevel iCallbackGetGreenVideoBlackLevel;
    void* iPtrGetGreenVideoBlackLevel;
    CallbackRenderingControl1SetGreenVideoBlackLevel iCallbackSetGreenVideoBlackLevel;
    void* iPtrSetGreenVideoBlackLevel;
    CallbackRenderingControl1GetBlueVideoBlackLevel iCallbackGetBlueVideoBlackLevel;
    void* iPtrGetBlueVideoBlackLevel;
    CallbackRenderingControl1SetBlueVideoBlackLevel iCallbackSetBlueVideoBlackLevel;
    void* iPtrSetBlueVideoBlackLevel;
    CallbackRenderingControl1GetColorTemperature iCallbackGetColorTemperature;
    void* iPtrGetColorTemperature;
    CallbackRenderingControl1SetColorTemperature iCallbackSetColorTemperature;
    void* iPtrSetColorTemperature;
    CallbackRenderingControl1GetHorizontalKeystone iCallbackGetHorizontalKeystone;
    void* iPtrGetHorizontalKeystone;
    CallbackRenderingControl1SetHorizontalKeystone iCallbackSetHorizontalKeystone;
    void* iPtrSetHorizontalKeystone;
    CallbackRenderingControl1GetVerticalKeystone iCallbackGetVerticalKeystone;
    void* iPtrGetVerticalKeystone;
    CallbackRenderingControl1SetVerticalKeystone iCallbackSetVerticalKeystone;
    void* iPtrSetVerticalKeystone;
    CallbackRenderingControl1GetMute iCallbackGetMute;
    void* iPtrGetMute;
    CallbackRenderingControl1SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackRenderingControl1GetVolume iCallbackGetVolume;
    void* iPtrGetVolume;
    CallbackRenderingControl1SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackRenderingControl1GetVolumeDB iCallbackGetVolumeDB;
    void* iPtrGetVolumeDB;
    CallbackRenderingControl1SetVolumeDB iCallbackSetVolumeDB;
    void* iPtrSetVolumeDB;
    CallbackRenderingControl1GetVolumeDBRange iCallbackGetVolumeDBRange;
    void* iPtrGetVolumeDBRange;
    CallbackRenderingControl1GetLoudness iCallbackGetLoudness;
    void* iPtrGetLoudness;
    CallbackRenderingControl1SetLoudness iCallbackSetLoudness;
    void* iPtrSetLoudness;
    PropertyString* iPropertyLastChange;
};

DvProviderUpnpOrgRenderingControl1C::DvProviderUpnpOrgRenderingControl1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "RenderingControl", 1)
{
    iPropertyLastChange = NULL;
}

TBool DvProviderUpnpOrgRenderingControl1C::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgRenderingControl1C::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgRenderingControl1C::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionListPresets(CallbackRenderingControl1ListPresets aCallback, void* aPtr)
{
    iCallbackListPresets = aCallback;
    iPtrListPresets = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSelectPreset(CallbackRenderingControl1SelectPreset aCallback, void* aPtr)
{
    iCallbackSelectPreset = aCallback;
    iPtrSelectPreset = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SelectPreset");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("PresetName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetBrightness(CallbackRenderingControl1GetBrightness aCallback, void* aPtr)
{
    iCallbackGetBrightness = aCallback;
    iPtrGetBrightness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetBrightness(CallbackRenderingControl1SetBrightness aCallback, void* aPtr)
{
    iCallbackSetBrightness = aCallback;
    iPtrSetBrightness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetContrast(CallbackRenderingControl1GetContrast aCallback, void* aPtr)
{
    iCallbackGetContrast = aCallback;
    iPtrGetContrast = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetContrast(CallbackRenderingControl1SetContrast aCallback, void* aPtr)
{
    iCallbackSetContrast = aCallback;
    iPtrSetContrast = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetSharpness(CallbackRenderingControl1GetSharpness aCallback, void* aPtr)
{
    iCallbackGetSharpness = aCallback;
    iPtrGetSharpness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetSharpness(CallbackRenderingControl1SetSharpness aCallback, void* aPtr)
{
    iCallbackSetSharpness = aCallback;
    iPtrSetSharpness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetRedVideoGain(CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr)
{
    iCallbackGetRedVideoGain = aCallback;
    iPtrGetRedVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetRedVideoGain(CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr)
{
    iCallbackSetRedVideoGain = aCallback;
    iPtrSetRedVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetGreenVideoGain(CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackGetGreenVideoGain = aCallback;
    iPtrGetGreenVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetGreenVideoGain(CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackSetGreenVideoGain = aCallback;
    iPtrSetGreenVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetBlueVideoGain(CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackGetBlueVideoGain = aCallback;
    iPtrGetBlueVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetBlueVideoGain(CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackSetBlueVideoGain = aCallback;
    iPtrSetBlueVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetRedVideoBlackLevel(CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetRedVideoBlackLevel = aCallback;
    iPtrGetRedVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetRedVideoBlackLevel(CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetRedVideoBlackLevel = aCallback;
    iPtrSetRedVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetGreenVideoBlackLevel = aCallback;
    iPtrGetGreenVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetGreenVideoBlackLevel = aCallback;
    iPtrSetGreenVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetBlueVideoBlackLevel = aCallback;
    iPtrGetBlueVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetBlueVideoBlackLevel = aCallback;
    iPtrSetBlueVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetColorTemperature(CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr)
{
    iCallbackGetColorTemperature = aCallback;
    iPtrGetColorTemperature = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetColorTemperature(CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr)
{
    iCallbackSetColorTemperature = aCallback;
    iPtrSetColorTemperature = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetHorizontalKeystone(CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackGetHorizontalKeystone = aCallback;
    iPtrGetHorizontalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetHorizontalKeystone(CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackSetHorizontalKeystone = aCallback;
    iPtrSetHorizontalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetVerticalKeystone(CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackGetVerticalKeystone = aCallback;
    iPtrGetVerticalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetVerticalKeystone(CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackSetVerticalKeystone = aCallback;
    iPtrSetVerticalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetMute(CallbackRenderingControl1GetMute aCallback, void* aPtr)
{
    iCallbackGetMute = aCallback;
    iPtrGetMute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetMute(CallbackRenderingControl1SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetVolume(CallbackRenderingControl1GetVolume aCallback, void* aPtr)
{
    iCallbackGetVolume = aCallback;
    iPtrGetVolume = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetVolume(CallbackRenderingControl1SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetVolumeDB(CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr)
{
    iCallbackGetVolumeDB = aCallback;
    iPtrGetVolumeDB = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetVolumeDB(CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr)
{
    iCallbackSetVolumeDB = aCallback;
    iPtrSetVolumeDB = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetVolumeDBRange(CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr)
{
    iCallbackGetVolumeDBRange = aCallback;
    iPtrGetVolumeDBRange = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDBRange");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("MinValue"));
    action->AddOutputParameter(new ParameterInt("MaxValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionGetLoudness(CallbackRenderingControl1GetLoudness aCallback, void* aPtr)
{
    iCallbackGetLoudness = aCallback;
    iPtrGetLoudness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::EnableActionSetLoudness(CallbackRenderingControl1SetLoudness aCallback, void* aPtr)
{
    iCallbackSetLoudness = aCallback;
    iPtrSetLoudness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1C::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1C::DoListPresets(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* CurrentPresetNameList;
    ASSERT(iCallbackListPresets != NULL);
    if (0 != iCallbackListPresets(iPtrListPresets, invocationC, invocationCPtr, InstanceID, &CurrentPresetNameList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    invocation.StartResponse();
    Brhz bufCurrentPresetNameList((const TChar*)CurrentPresetNameList);
    OhNetFreeExternal(CurrentPresetNameList);
    respCurrentPresetNameList.Write(bufCurrentPresetNameList);
    respCurrentPresetNameList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSelectPreset(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSelectPreset != NULL);
    if (0 != iCallbackSelectPreset(iPtrSelectPreset, invocationC, invocationCPtr, InstanceID, (const char*)PresetName.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetBrightness(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentBrightness;
    ASSERT(iCallbackGetBrightness != NULL);
    if (0 != iCallbackGetBrightness(iPtrGetBrightness, invocationC, invocationCPtr, InstanceID, &CurrentBrightness)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    invocation.StartResponse();
    respCurrentBrightness.Write(CurrentBrightness);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetBrightness(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetBrightness != NULL);
    if (0 != iCallbackSetBrightness(iPtrSetBrightness, invocationC, invocationCPtr, InstanceID, DesiredBrightness)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetContrast(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentContrast;
    ASSERT(iCallbackGetContrast != NULL);
    if (0 != iCallbackGetContrast(iPtrGetContrast, invocationC, invocationCPtr, InstanceID, &CurrentContrast)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    invocation.StartResponse();
    respCurrentContrast.Write(CurrentContrast);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetContrast(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetContrast != NULL);
    if (0 != iCallbackSetContrast(iPtrSetContrast, invocationC, invocationCPtr, InstanceID, DesiredContrast)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetSharpness(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentSharpness;
    ASSERT(iCallbackGetSharpness != NULL);
    if (0 != iCallbackGetSharpness(iPtrGetSharpness, invocationC, invocationCPtr, InstanceID, &CurrentSharpness)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    invocation.StartResponse();
    respCurrentSharpness.Write(CurrentSharpness);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetSharpness(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetSharpness != NULL);
    if (0 != iCallbackSetSharpness(iPtrSetSharpness, invocationC, invocationCPtr, InstanceID, DesiredSharpness)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetRedVideoGain(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentRedVideoGain;
    ASSERT(iCallbackGetRedVideoGain != NULL);
    if (0 != iCallbackGetRedVideoGain(iPtrGetRedVideoGain, invocationC, invocationCPtr, InstanceID, &CurrentRedVideoGain)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    invocation.StartResponse();
    respCurrentRedVideoGain.Write(CurrentRedVideoGain);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetRedVideoGain(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetRedVideoGain != NULL);
    if (0 != iCallbackSetRedVideoGain(iPtrSetRedVideoGain, invocationC, invocationCPtr, InstanceID, DesiredRedVideoGain)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetGreenVideoGain(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentGreenVideoGain;
    ASSERT(iCallbackGetGreenVideoGain != NULL);
    if (0 != iCallbackGetGreenVideoGain(iPtrGetGreenVideoGain, invocationC, invocationCPtr, InstanceID, &CurrentGreenVideoGain)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    invocation.StartResponse();
    respCurrentGreenVideoGain.Write(CurrentGreenVideoGain);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetGreenVideoGain(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetGreenVideoGain != NULL);
    if (0 != iCallbackSetGreenVideoGain(iPtrSetGreenVideoGain, invocationC, invocationCPtr, InstanceID, DesiredGreenVideoGain)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetBlueVideoGain(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentBlueVideoGain;
    ASSERT(iCallbackGetBlueVideoGain != NULL);
    if (0 != iCallbackGetBlueVideoGain(iPtrGetBlueVideoGain, invocationC, invocationCPtr, InstanceID, &CurrentBlueVideoGain)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    invocation.StartResponse();
    respCurrentBlueVideoGain.Write(CurrentBlueVideoGain);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetBlueVideoGain(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetBlueVideoGain != NULL);
    if (0 != iCallbackSetBlueVideoGain(iPtrSetBlueVideoGain, invocationC, invocationCPtr, InstanceID, DesiredBlueVideoGain)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentRedVideoBlackLevel;
    ASSERT(iCallbackGetRedVideoBlackLevel != NULL);
    if (0 != iCallbackGetRedVideoBlackLevel(iPtrGetRedVideoBlackLevel, invocationC, invocationCPtr, InstanceID, &CurrentRedVideoBlackLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    invocation.StartResponse();
    respCurrentRedVideoBlackLevel.Write(CurrentRedVideoBlackLevel);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetRedVideoBlackLevel != NULL);
    if (0 != iCallbackSetRedVideoBlackLevel(iPtrSetRedVideoBlackLevel, invocationC, invocationCPtr, InstanceID, DesiredRedVideoBlackLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentGreenVideoBlackLevel;
    ASSERT(iCallbackGetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackGetGreenVideoBlackLevel(iPtrGetGreenVideoBlackLevel, invocationC, invocationCPtr, InstanceID, &CurrentGreenVideoBlackLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    invocation.StartResponse();
    respCurrentGreenVideoBlackLevel.Write(CurrentGreenVideoBlackLevel);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackSetGreenVideoBlackLevel(iPtrSetGreenVideoBlackLevel, invocationC, invocationCPtr, InstanceID, DesiredGreenVideoBlackLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentBlueVideoBlackLevel;
    ASSERT(iCallbackGetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackGetBlueVideoBlackLevel(iPtrGetBlueVideoBlackLevel, invocationC, invocationCPtr, InstanceID, &CurrentBlueVideoBlackLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    invocation.StartResponse();
    respCurrentBlueVideoBlackLevel.Write(CurrentBlueVideoBlackLevel);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackSetBlueVideoBlackLevel(iPtrSetBlueVideoBlackLevel, invocationC, invocationCPtr, InstanceID, DesiredBlueVideoBlackLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetColorTemperature(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentColorTemperature;
    ASSERT(iCallbackGetColorTemperature != NULL);
    if (0 != iCallbackGetColorTemperature(iPtrGetColorTemperature, invocationC, invocationCPtr, InstanceID, &CurrentColorTemperature)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    invocation.StartResponse();
    respCurrentColorTemperature.Write(CurrentColorTemperature);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetColorTemperature(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetColorTemperature != NULL);
    if (0 != iCallbackSetColorTemperature(iPtrSetColorTemperature, invocationC, invocationCPtr, InstanceID, DesiredColorTemperature)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetHorizontalKeystone(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t CurrentHorizontalKeystone;
    ASSERT(iCallbackGetHorizontalKeystone != NULL);
    if (0 != iCallbackGetHorizontalKeystone(iPtrGetHorizontalKeystone, invocationC, invocationCPtr, InstanceID, &CurrentHorizontalKeystone)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    invocation.StartResponse();
    respCurrentHorizontalKeystone.Write(CurrentHorizontalKeystone);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetHorizontalKeystone(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetHorizontalKeystone != NULL);
    if (0 != iCallbackSetHorizontalKeystone(iPtrSetHorizontalKeystone, invocationC, invocationCPtr, InstanceID, DesiredHorizontalKeystone)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetVerticalKeystone(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t CurrentVerticalKeystone;
    ASSERT(iCallbackGetVerticalKeystone != NULL);
    if (0 != iCallbackGetVerticalKeystone(iPtrGetVerticalKeystone, invocationC, invocationCPtr, InstanceID, &CurrentVerticalKeystone)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    invocation.StartResponse();
    respCurrentVerticalKeystone.Write(CurrentVerticalKeystone);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetVerticalKeystone(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetVerticalKeystone != NULL);
    if (0 != iCallbackSetVerticalKeystone(iPtrSetVerticalKeystone, invocationC, invocationCPtr, InstanceID, DesiredVerticalKeystone)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetMute(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentMute;
    ASSERT(iCallbackGetMute != NULL);
    if (0 != iCallbackGetMute(iPtrGetMute, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), &CurrentMute)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respCurrentMute(aInvocation, "CurrentMute");
    invocation.StartResponse();
    respCurrentMute.Write((CurrentMute!=0));
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetMute(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), DesiredMute)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetVolume(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentVolume;
    ASSERT(iCallbackGetVolume != NULL);
    if (0 != iCallbackGetVolume(iPtrGetVolume, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), &CurrentVolume)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respCurrentVolume(aInvocation, "CurrentVolume");
    invocation.StartResponse();
    respCurrentVolume.Write(CurrentVolume);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetVolume(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TUint DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), DesiredVolume)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetVolumeDB(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t CurrentVolume;
    ASSERT(iCallbackGetVolumeDB != NULL);
    if (0 != iCallbackGetVolumeDB(iPtrGetVolumeDB, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), &CurrentVolume)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respCurrentVolume(aInvocation, "CurrentVolume");
    invocation.StartResponse();
    respCurrentVolume.Write(CurrentVolume);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetVolumeDB(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TInt DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetVolumeDB != NULL);
    if (0 != iCallbackSetVolumeDB(iPtrSetVolumeDB, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), DesiredVolume)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetVolumeDBRange(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t MinValue;
    int32_t MaxValue;
    ASSERT(iCallbackGetVolumeDBRange != NULL);
    if (0 != iCallbackGetVolumeDBRange(iPtrGetVolumeDBRange, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), &MinValue, &MaxValue)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respMinValue(aInvocation, "MinValue");
    DviInvocationResponseInt respMaxValue(aInvocation, "MaxValue");
    invocation.StartResponse();
    respMinValue.Write(MinValue);
    respMaxValue.Write(MaxValue);
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoGetLoudness(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t CurrentLoudness;
    ASSERT(iCallbackGetLoudness != NULL);
    if (0 != iCallbackGetLoudness(iPtrGetLoudness, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), &CurrentLoudness)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respCurrentLoudness(aInvocation, "CurrentLoudness");
    invocation.StartResponse();
    respCurrentLoudness.Write((CurrentLoudness!=0));
    invocation.EndResponse();
}

void DvProviderUpnpOrgRenderingControl1C::DoSetLoudness(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetLoudness != NULL);
    if (0 != iCallbackSetLoudness(iPtrSetLoudness, invocationC, invocationCPtr, InstanceID, (const char*)Channel.Ptr(), DesiredLoudness)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgRenderingControl1Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgRenderingControl1C(aDevice);
}

void STDCALL DvProviderUpnpOrgRenderingControl1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionListPresets(THandle aProvider, CallbackRenderingControl1ListPresets aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionListPresets(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl1SelectPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSelectPreset(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl1GetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetBrightness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl1SetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetBrightness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetContrast(THandle aProvider, CallbackRenderingControl1GetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetContrast(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetContrast(THandle aProvider, CallbackRenderingControl1SetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetContrast(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl1GetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetSharpness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl1SetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetSharpness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl1GetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetRedVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl1SetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetRedVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl1GetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetGreenVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl1SetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetGreenVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl1GetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetBlueVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl1SetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetBlueVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetRedVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetRedVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetGreenVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetGreenVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl1GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetBlueVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl1SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetBlueVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl1GetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetColorTemperature(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl1SetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetColorTemperature(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl1GetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetHorizontalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl1SetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetHorizontalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl1GetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetVerticalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl1SetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetVerticalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetMute(THandle aProvider, CallbackRenderingControl1GetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetMute(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetMute(THandle aProvider, CallbackRenderingControl1SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetMute(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetVolume(THandle aProvider, CallbackRenderingControl1GetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetVolume(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetVolume(THandle aProvider, CallbackRenderingControl1SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetVolume(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl1GetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetVolumeDB(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl1SetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetVolumeDB(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl1GetVolumeDBRange aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetVolumeDBRange(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl1GetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionGetLoudness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl1SetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnableActionSetLoudness(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgRenderingControl1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgRenderingControl1GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgRenderingControl1EnablePropertyLastChange(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl1C*>(aProvider)->EnablePropertyLastChange();
}

