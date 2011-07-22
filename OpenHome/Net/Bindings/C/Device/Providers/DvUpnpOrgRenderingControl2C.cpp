#include "DvUpnpOrgRenderingControl2.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderUpnpOrgRenderingControl2C : public DvProvider
{
public:
    DvProviderUpnpOrgRenderingControl2C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    void EnableActionListPresets(CallbackRenderingControl2ListPresets aCallback, void* aPtr);
    void EnableActionSelectPreset(CallbackRenderingControl2SelectPreset aCallback, void* aPtr);
    void EnableActionGetBrightness(CallbackRenderingControl2GetBrightness aCallback, void* aPtr);
    void EnableActionSetBrightness(CallbackRenderingControl2SetBrightness aCallback, void* aPtr);
    void EnableActionGetContrast(CallbackRenderingControl2GetContrast aCallback, void* aPtr);
    void EnableActionSetContrast(CallbackRenderingControl2SetContrast aCallback, void* aPtr);
    void EnableActionGetSharpness(CallbackRenderingControl2GetSharpness aCallback, void* aPtr);
    void EnableActionSetSharpness(CallbackRenderingControl2SetSharpness aCallback, void* aPtr);
    void EnableActionGetRedVideoGain(CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr);
    void EnableActionSetRedVideoGain(CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr);
    void EnableActionGetGreenVideoGain(CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr);
    void EnableActionSetGreenVideoGain(CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr);
    void EnableActionGetBlueVideoGain(CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr);
    void EnableActionSetBlueVideoGain(CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr);
    void EnableActionGetRedVideoBlackLevel(CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetRedVideoBlackLevel(CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr);
    void EnableActionGetColorTemperature(CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr);
    void EnableActionSetColorTemperature(CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr);
    void EnableActionGetHorizontalKeystone(CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionSetHorizontalKeystone(CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr);
    void EnableActionGetVerticalKeystone(CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr);
    void EnableActionSetVerticalKeystone(CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr);
    void EnableActionGetMute(CallbackRenderingControl2GetMute aCallback, void* aPtr);
    void EnableActionSetMute(CallbackRenderingControl2SetMute aCallback, void* aPtr);
    void EnableActionGetVolume(CallbackRenderingControl2GetVolume aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackRenderingControl2SetVolume aCallback, void* aPtr);
    void EnableActionGetVolumeDB(CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr);
    void EnableActionSetVolumeDB(CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr);
    void EnableActionGetVolumeDBRange(CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr);
    void EnableActionGetLoudness(CallbackRenderingControl2GetLoudness aCallback, void* aPtr);
    void EnableActionSetLoudness(CallbackRenderingControl2SetLoudness aCallback, void* aPtr);
    void EnableActionGetStateVariables(CallbackRenderingControl2GetStateVariables aCallback, void* aPtr);
    void EnableActionSetStateVariables(CallbackRenderingControl2SetStateVariables aCallback, void* aPtr);
private:
    void DoListPresets(IDviInvocation& aInvocation, TUint aVersion);
    void DoSelectPreset(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetContrast(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetContrast(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSharpness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSharpness(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColorTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetColorTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVolumeDB(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeDB(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVolumeDBRange(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLoudness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetLoudness(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackRenderingControl2ListPresets iCallbackListPresets;
    void* iPtrListPresets;
    CallbackRenderingControl2SelectPreset iCallbackSelectPreset;
    void* iPtrSelectPreset;
    CallbackRenderingControl2GetBrightness iCallbackGetBrightness;
    void* iPtrGetBrightness;
    CallbackRenderingControl2SetBrightness iCallbackSetBrightness;
    void* iPtrSetBrightness;
    CallbackRenderingControl2GetContrast iCallbackGetContrast;
    void* iPtrGetContrast;
    CallbackRenderingControl2SetContrast iCallbackSetContrast;
    void* iPtrSetContrast;
    CallbackRenderingControl2GetSharpness iCallbackGetSharpness;
    void* iPtrGetSharpness;
    CallbackRenderingControl2SetSharpness iCallbackSetSharpness;
    void* iPtrSetSharpness;
    CallbackRenderingControl2GetRedVideoGain iCallbackGetRedVideoGain;
    void* iPtrGetRedVideoGain;
    CallbackRenderingControl2SetRedVideoGain iCallbackSetRedVideoGain;
    void* iPtrSetRedVideoGain;
    CallbackRenderingControl2GetGreenVideoGain iCallbackGetGreenVideoGain;
    void* iPtrGetGreenVideoGain;
    CallbackRenderingControl2SetGreenVideoGain iCallbackSetGreenVideoGain;
    void* iPtrSetGreenVideoGain;
    CallbackRenderingControl2GetBlueVideoGain iCallbackGetBlueVideoGain;
    void* iPtrGetBlueVideoGain;
    CallbackRenderingControl2SetBlueVideoGain iCallbackSetBlueVideoGain;
    void* iPtrSetBlueVideoGain;
    CallbackRenderingControl2GetRedVideoBlackLevel iCallbackGetRedVideoBlackLevel;
    void* iPtrGetRedVideoBlackLevel;
    CallbackRenderingControl2SetRedVideoBlackLevel iCallbackSetRedVideoBlackLevel;
    void* iPtrSetRedVideoBlackLevel;
    CallbackRenderingControl2GetGreenVideoBlackLevel iCallbackGetGreenVideoBlackLevel;
    void* iPtrGetGreenVideoBlackLevel;
    CallbackRenderingControl2SetGreenVideoBlackLevel iCallbackSetGreenVideoBlackLevel;
    void* iPtrSetGreenVideoBlackLevel;
    CallbackRenderingControl2GetBlueVideoBlackLevel iCallbackGetBlueVideoBlackLevel;
    void* iPtrGetBlueVideoBlackLevel;
    CallbackRenderingControl2SetBlueVideoBlackLevel iCallbackSetBlueVideoBlackLevel;
    void* iPtrSetBlueVideoBlackLevel;
    CallbackRenderingControl2GetColorTemperature iCallbackGetColorTemperature;
    void* iPtrGetColorTemperature;
    CallbackRenderingControl2SetColorTemperature iCallbackSetColorTemperature;
    void* iPtrSetColorTemperature;
    CallbackRenderingControl2GetHorizontalKeystone iCallbackGetHorizontalKeystone;
    void* iPtrGetHorizontalKeystone;
    CallbackRenderingControl2SetHorizontalKeystone iCallbackSetHorizontalKeystone;
    void* iPtrSetHorizontalKeystone;
    CallbackRenderingControl2GetVerticalKeystone iCallbackGetVerticalKeystone;
    void* iPtrGetVerticalKeystone;
    CallbackRenderingControl2SetVerticalKeystone iCallbackSetVerticalKeystone;
    void* iPtrSetVerticalKeystone;
    CallbackRenderingControl2GetMute iCallbackGetMute;
    void* iPtrGetMute;
    CallbackRenderingControl2SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackRenderingControl2GetVolume iCallbackGetVolume;
    void* iPtrGetVolume;
    CallbackRenderingControl2SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackRenderingControl2GetVolumeDB iCallbackGetVolumeDB;
    void* iPtrGetVolumeDB;
    CallbackRenderingControl2SetVolumeDB iCallbackSetVolumeDB;
    void* iPtrSetVolumeDB;
    CallbackRenderingControl2GetVolumeDBRange iCallbackGetVolumeDBRange;
    void* iPtrGetVolumeDBRange;
    CallbackRenderingControl2GetLoudness iCallbackGetLoudness;
    void* iPtrGetLoudness;
    CallbackRenderingControl2SetLoudness iCallbackSetLoudness;
    void* iPtrSetLoudness;
    CallbackRenderingControl2GetStateVariables iCallbackGetStateVariables;
    void* iPtrGetStateVariables;
    CallbackRenderingControl2SetStateVariables iCallbackSetStateVariables;
    void* iPtrSetStateVariables;
    PropertyString* iPropertyLastChange;
};

DvProviderUpnpOrgRenderingControl2C::DvProviderUpnpOrgRenderingControl2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "RenderingControl", 2)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

TBool DvProviderUpnpOrgRenderingControl2C::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgRenderingControl2C::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionListPresets(CallbackRenderingControl2ListPresets aCallback, void* aPtr)
{
    iCallbackListPresets = aCallback;
    iPtrListPresets = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSelectPreset(CallbackRenderingControl2SelectPreset aCallback, void* aPtr)
{
    iCallbackSelectPreset = aCallback;
    iPtrSelectPreset = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SelectPreset");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"FactoryDefaults";
    action->AddInputParameter(new ParameterString("PresetName", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetBrightness(CallbackRenderingControl2GetBrightness aCallback, void* aPtr)
{
    iCallbackGetBrightness = aCallback;
    iPtrGetBrightness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetBrightness(CallbackRenderingControl2SetBrightness aCallback, void* aPtr)
{
    iCallbackSetBrightness = aCallback;
    iPtrSetBrightness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetContrast(CallbackRenderingControl2GetContrast aCallback, void* aPtr)
{
    iCallbackGetContrast = aCallback;
    iPtrGetContrast = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetContrast(CallbackRenderingControl2SetContrast aCallback, void* aPtr)
{
    iCallbackSetContrast = aCallback;
    iPtrSetContrast = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetSharpness(CallbackRenderingControl2GetSharpness aCallback, void* aPtr)
{
    iCallbackGetSharpness = aCallback;
    iPtrGetSharpness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetSharpness(CallbackRenderingControl2SetSharpness aCallback, void* aPtr)
{
    iCallbackSetSharpness = aCallback;
    iPtrSetSharpness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetRedVideoGain(CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr)
{
    iCallbackGetRedVideoGain = aCallback;
    iPtrGetRedVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetRedVideoGain(CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr)
{
    iCallbackSetRedVideoGain = aCallback;
    iPtrSetRedVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetGreenVideoGain(CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackGetGreenVideoGain = aCallback;
    iPtrGetGreenVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetGreenVideoGain(CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr)
{
    iCallbackSetGreenVideoGain = aCallback;
    iPtrSetGreenVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetBlueVideoGain(CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackGetBlueVideoGain = aCallback;
    iPtrGetBlueVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetBlueVideoGain(CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr)
{
    iCallbackSetBlueVideoGain = aCallback;
    iPtrSetBlueVideoGain = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetRedVideoBlackLevel(CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetRedVideoBlackLevel = aCallback;
    iPtrGetRedVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetRedVideoBlackLevel(CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetRedVideoBlackLevel = aCallback;
    iPtrSetRedVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetGreenVideoBlackLevel(CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetGreenVideoBlackLevel = aCallback;
    iPtrGetGreenVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetGreenVideoBlackLevel(CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetGreenVideoBlackLevel = aCallback;
    iPtrSetGreenVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetBlueVideoBlackLevel(CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackGetBlueVideoBlackLevel = aCallback;
    iPtrGetBlueVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetBlueVideoBlackLevel(CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    iCallbackSetBlueVideoBlackLevel = aCallback;
    iPtrSetBlueVideoBlackLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetColorTemperature(CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr)
{
    iCallbackGetColorTemperature = aCallback;
    iPtrGetColorTemperature = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetColorTemperature(CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr)
{
    iCallbackSetColorTemperature = aCallback;
    iPtrSetColorTemperature = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetHorizontalKeystone(CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackGetHorizontalKeystone = aCallback;
    iPtrGetHorizontalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetHorizontalKeystone(CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr)
{
    iCallbackSetHorizontalKeystone = aCallback;
    iPtrSetHorizontalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVerticalKeystone(CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackGetVerticalKeystone = aCallback;
    iPtrGetVerticalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetVerticalKeystone(CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr)
{
    iCallbackSetVerticalKeystone = aCallback;
    iPtrSetVerticalKeystone = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetMute(CallbackRenderingControl2GetMute aCallback, void* aPtr)
{
    iCallbackGetMute = aCallback;
    iPtrGetMute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMute");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetMute(CallbackRenderingControl2SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVolume(CallbackRenderingControl2GetVolume aCallback, void* aPtr)
{
    iCallbackGetVolume = aCallback;
    iPtrGetVolume = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolume");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetVolume(CallbackRenderingControl2SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVolumeDB(CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr)
{
    iCallbackGetVolumeDB = aCallback;
    iPtrGetVolumeDB = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDB");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetVolumeDB(CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr)
{
    iCallbackSetVolumeDB = aCallback;
    iPtrSetVolumeDB = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolumeDB");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetVolumeDBRange(CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr)
{
    iCallbackGetVolumeDBRange = aCallback;
    iPtrGetVolumeDBRange = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDBRange");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("MinValue"));
    action->AddOutputParameter(new ParameterInt("MaxValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetLoudness(CallbackRenderingControl2GetLoudness aCallback, void* aPtr)
{
    iCallbackGetLoudness = aCallback;
    iPtrGetLoudness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoudness");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetLoudness(CallbackRenderingControl2SetLoudness aCallback, void* aPtr)
{
    iCallbackSetLoudness = aCallback;
    iPtrSetLoudness = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoudness");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterBool("DesiredLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionGetStateVariables(CallbackRenderingControl2GetStateVariables aCallback, void* aPtr)
{
    iCallbackGetStateVariables = aCallback;
    iPtrGetStateVariables = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::EnableActionSetStateVariables(CallbackRenderingControl2SetStateVariables aCallback, void* aPtr)
{
    iCallbackSetStateVariables = aCallback;
    iPtrSetStateVariables = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("RenderingControlUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2C::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2C::DoListPresets(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* CurrentPresetNameList;
    ASSERT(iCallbackListPresets != NULL);
    if (0 != iCallbackListPresets(iPtrListPresets, aVersion, InstanceID, &CurrentPresetNameList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    resp.Start();
    Brhz bufCurrentPresetNameList((const TChar*)CurrentPresetNameList);
    OhNetFreeExternal(CurrentPresetNameList);
    respCurrentPresetNameList.Write(bufCurrentPresetNameList);
    respCurrentPresetNameList.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSelectPreset(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSelectPreset != NULL);
    if (0 != iCallbackSelectPreset(iPtrSelectPreset, aVersion, InstanceID, (const char*)PresetName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentBrightness;
    ASSERT(iCallbackGetBrightness != NULL);
    if (0 != iCallbackGetBrightness(iPtrGetBrightness, aVersion, InstanceID, &CurrentBrightness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    resp.Start();
    respCurrentBrightness.Write(CurrentBrightness);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBrightness != NULL);
    if (0 != iCallbackSetBrightness(iPtrSetBrightness, aVersion, InstanceID, DesiredBrightness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetContrast(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentContrast;
    ASSERT(iCallbackGetContrast != NULL);
    if (0 != iCallbackGetContrast(iPtrGetContrast, aVersion, InstanceID, &CurrentContrast)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    resp.Start();
    respCurrentContrast.Write(CurrentContrast);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetContrast(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetContrast != NULL);
    if (0 != iCallbackSetContrast(iPtrSetContrast, aVersion, InstanceID, DesiredContrast)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetSharpness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentSharpness;
    ASSERT(iCallbackGetSharpness != NULL);
    if (0 != iCallbackGetSharpness(iPtrGetSharpness, aVersion, InstanceID, &CurrentSharpness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    resp.Start();
    respCurrentSharpness.Write(CurrentSharpness);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetSharpness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetSharpness != NULL);
    if (0 != iCallbackSetSharpness(iPtrSetSharpness, aVersion, InstanceID, DesiredSharpness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentRedVideoGain;
    ASSERT(iCallbackGetRedVideoGain != NULL);
    if (0 != iCallbackGetRedVideoGain(iPtrGetRedVideoGain, aVersion, InstanceID, &CurrentRedVideoGain)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    resp.Start();
    respCurrentRedVideoGain.Write(CurrentRedVideoGain);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetRedVideoGain != NULL);
    if (0 != iCallbackSetRedVideoGain(iPtrSetRedVideoGain, aVersion, InstanceID, DesiredRedVideoGain)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentGreenVideoGain;
    ASSERT(iCallbackGetGreenVideoGain != NULL);
    if (0 != iCallbackGetGreenVideoGain(iPtrGetGreenVideoGain, aVersion, InstanceID, &CurrentGreenVideoGain)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    resp.Start();
    respCurrentGreenVideoGain.Write(CurrentGreenVideoGain);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetGreenVideoGain != NULL);
    if (0 != iCallbackSetGreenVideoGain(iPtrSetGreenVideoGain, aVersion, InstanceID, DesiredGreenVideoGain)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentBlueVideoGain;
    ASSERT(iCallbackGetBlueVideoGain != NULL);
    if (0 != iCallbackGetBlueVideoGain(iPtrGetBlueVideoGain, aVersion, InstanceID, &CurrentBlueVideoGain)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    resp.Start();
    respCurrentBlueVideoGain.Write(CurrentBlueVideoGain);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBlueVideoGain != NULL);
    if (0 != iCallbackSetBlueVideoGain(iPtrSetBlueVideoGain, aVersion, InstanceID, DesiredBlueVideoGain)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentRedVideoBlackLevel;
    ASSERT(iCallbackGetRedVideoBlackLevel != NULL);
    if (0 != iCallbackGetRedVideoBlackLevel(iPtrGetRedVideoBlackLevel, aVersion, InstanceID, &CurrentRedVideoBlackLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    resp.Start();
    respCurrentRedVideoBlackLevel.Write(CurrentRedVideoBlackLevel);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetRedVideoBlackLevel != NULL);
    if (0 != iCallbackSetRedVideoBlackLevel(iPtrSetRedVideoBlackLevel, aVersion, InstanceID, DesiredRedVideoBlackLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentGreenVideoBlackLevel;
    ASSERT(iCallbackGetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackGetGreenVideoBlackLevel(iPtrGetGreenVideoBlackLevel, aVersion, InstanceID, &CurrentGreenVideoBlackLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    resp.Start();
    respCurrentGreenVideoBlackLevel.Write(CurrentGreenVideoBlackLevel);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetGreenVideoBlackLevel != NULL);
    if (0 != iCallbackSetGreenVideoBlackLevel(iPtrSetGreenVideoBlackLevel, aVersion, InstanceID, DesiredGreenVideoBlackLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentBlueVideoBlackLevel;
    ASSERT(iCallbackGetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackGetBlueVideoBlackLevel(iPtrGetBlueVideoBlackLevel, aVersion, InstanceID, &CurrentBlueVideoBlackLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    resp.Start();
    respCurrentBlueVideoBlackLevel.Write(CurrentBlueVideoBlackLevel);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetBlueVideoBlackLevel != NULL);
    if (0 != iCallbackSetBlueVideoBlackLevel(iPtrSetBlueVideoBlackLevel, aVersion, InstanceID, DesiredBlueVideoBlackLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetColorTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentColorTemperature;
    ASSERT(iCallbackGetColorTemperature != NULL);
    if (0 != iCallbackGetColorTemperature(iPtrGetColorTemperature, aVersion, InstanceID, &CurrentColorTemperature)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    resp.Start();
    respCurrentColorTemperature.Write(CurrentColorTemperature);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetColorTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetColorTemperature != NULL);
    if (0 != iCallbackSetColorTemperature(iPtrSetColorTemperature, aVersion, InstanceID, DesiredColorTemperature)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t CurrentHorizontalKeystone;
    ASSERT(iCallbackGetHorizontalKeystone != NULL);
    if (0 != iCallbackGetHorizontalKeystone(iPtrGetHorizontalKeystone, aVersion, InstanceID, &CurrentHorizontalKeystone)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    resp.Start();
    respCurrentHorizontalKeystone.Write(CurrentHorizontalKeystone);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetHorizontalKeystone != NULL);
    if (0 != iCallbackSetHorizontalKeystone(iPtrSetHorizontalKeystone, aVersion, InstanceID, DesiredHorizontalKeystone)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t CurrentVerticalKeystone;
    ASSERT(iCallbackGetVerticalKeystone != NULL);
    if (0 != iCallbackGetVerticalKeystone(iPtrGetVerticalKeystone, aVersion, InstanceID, &CurrentVerticalKeystone)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    resp.Start();
    respCurrentVerticalKeystone.Write(CurrentVerticalKeystone);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetVerticalKeystone != NULL);
    if (0 != iCallbackSetVerticalKeystone(iPtrSetVerticalKeystone, aVersion, InstanceID, DesiredVerticalKeystone)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentMute;
    ASSERT(iCallbackGetMute != NULL);
    if (0 != iCallbackGetMute(iPtrGetMute, aVersion, InstanceID, (const char*)Channel.Ptr(), &CurrentMute)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respCurrentMute(aInvocation, "CurrentMute");
    resp.Start();
    respCurrentMute.Write((CurrentMute!=0));
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, aVersion, InstanceID, (const char*)Channel.Ptr(), DesiredMute)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentVolume;
    ASSERT(iCallbackGetVolume != NULL);
    if (0 != iCallbackGetVolume(iPtrGetVolume, aVersion, InstanceID, (const char*)Channel.Ptr(), &CurrentVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respCurrentVolume(aInvocation, "CurrentVolume");
    resp.Start();
    respCurrentVolume.Write(CurrentVolume);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TUint DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, aVersion, InstanceID, (const char*)Channel.Ptr(), DesiredVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetVolumeDB(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t CurrentVolume;
    ASSERT(iCallbackGetVolumeDB != NULL);
    if (0 != iCallbackGetVolumeDB(iPtrGetVolumeDB, aVersion, InstanceID, (const char*)Channel.Ptr(), &CurrentVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respCurrentVolume(aInvocation, "CurrentVolume");
    resp.Start();
    respCurrentVolume.Write(CurrentVolume);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetVolumeDB(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TInt DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetVolumeDB != NULL);
    if (0 != iCallbackSetVolumeDB(iPtrSetVolumeDB, aVersion, InstanceID, (const char*)Channel.Ptr(), DesiredVolume)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetVolumeDBRange(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    int32_t MinValue;
    int32_t MaxValue;
    ASSERT(iCallbackGetVolumeDBRange != NULL);
    if (0 != iCallbackGetVolumeDBRange(iPtrGetVolumeDBRange, aVersion, InstanceID, (const char*)Channel.Ptr(), &MinValue, &MaxValue)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseInt respMinValue(aInvocation, "MinValue");
    InvocationResponseInt respMaxValue(aInvocation, "MaxValue");
    resp.Start();
    respMinValue.Write(MinValue);
    respMaxValue.Write(MaxValue);
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetLoudness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t CurrentLoudness;
    ASSERT(iCallbackGetLoudness != NULL);
    if (0 != iCallbackGetLoudness(iPtrGetLoudness, aVersion, InstanceID, (const char*)Channel.Ptr(), &CurrentLoudness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respCurrentLoudness(aInvocation, "CurrentLoudness");
    resp.Start();
    respCurrentLoudness.Write((CurrentLoudness!=0));
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetLoudness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetLoudness != NULL);
    if (0 != iCallbackSetLoudness(iPtrSetLoudness, aVersion, InstanceID, (const char*)Channel.Ptr(), DesiredLoudness)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", StateVariableList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* StateVariableValuePairs;
    ASSERT(iCallbackGetStateVariables != NULL);
    if (0 != iCallbackGetStateVariables(iPtrGetStateVariables, aVersion, InstanceID, (const char*)StateVariableList.Ptr(), &StateVariableValuePairs)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    resp.Start();
    Brhz bufStateVariableValuePairs((const TChar*)StateVariableValuePairs);
    OhNetFreeExternal(StateVariableValuePairs);
    respStateVariableValuePairs.Write(bufStateVariableValuePairs);
    respStateVariableValuePairs.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgRenderingControl2C::DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz RenderingControlUDN;
    aInvocation.InvocationReadString("RenderingControlUDN", RenderingControlUDN);
    Brhz ServiceType;
    aInvocation.InvocationReadString("ServiceType", ServiceType);
    Brhz ServiceId;
    aInvocation.InvocationReadString("ServiceId", ServiceId);
    Brhz StateVariableValuePairs;
    aInvocation.InvocationReadString("StateVariableValuePairs", StateVariableValuePairs);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* StateVariableList;
    ASSERT(iCallbackSetStateVariables != NULL);
    if (0 != iCallbackSetStateVariables(iPtrSetStateVariables, aVersion, InstanceID, (const char*)RenderingControlUDN.Ptr(), (const char*)ServiceType.Ptr(), (const char*)ServiceId.Ptr(), (const char*)StateVariableValuePairs.Ptr(), &StateVariableList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respStateVariableList(aInvocation, "StateVariableList");
    resp.Start();
    Brhz bufStateVariableList((const TChar*)StateVariableList);
    OhNetFreeExternal(StateVariableList);
    respStateVariableList.Write(bufStateVariableList);
    respStateVariableList.WriteFlush();
    resp.End();
}



THandle STDCALL DvProviderUpnpOrgRenderingControl2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgRenderingControl2C(aDevice);
}

void STDCALL DvProviderUpnpOrgRenderingControl2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionListPresets(THandle aProvider, CallbackRenderingControl2ListPresets aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionListPresets(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSelectPreset(THandle aProvider, CallbackRenderingControl2SelectPreset aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSelectPreset(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetBrightness(THandle aProvider, CallbackRenderingControl2GetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetBrightness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetBrightness(THandle aProvider, CallbackRenderingControl2SetBrightness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetBrightness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetContrast(THandle aProvider, CallbackRenderingControl2GetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetContrast(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetContrast(THandle aProvider, CallbackRenderingControl2SetContrast aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetContrast(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetSharpness(THandle aProvider, CallbackRenderingControl2GetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetSharpness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetSharpness(THandle aProvider, CallbackRenderingControl2SetSharpness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetSharpness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoGain(THandle aProvider, CallbackRenderingControl2GetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetRedVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoGain(THandle aProvider, CallbackRenderingControl2SetRedVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetRedVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoGain(THandle aProvider, CallbackRenderingControl2GetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetGreenVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoGain(THandle aProvider, CallbackRenderingControl2SetGreenVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetGreenVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoGain(THandle aProvider, CallbackRenderingControl2GetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetBlueVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoGain(THandle aProvider, CallbackRenderingControl2SetBlueVideoGain aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetBlueVideoGain(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetRedVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetRedVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetRedVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetRedVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetGreenVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetGreenVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetGreenVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetGreenVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2GetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetBlueVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetBlueVideoBlackLevel(THandle aProvider, CallbackRenderingControl2SetBlueVideoBlackLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetBlueVideoBlackLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetColorTemperature(THandle aProvider, CallbackRenderingControl2GetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetColorTemperature(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetColorTemperature(THandle aProvider, CallbackRenderingControl2SetColorTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetColorTemperature(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2GetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetHorizontalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetHorizontalKeystone(THandle aProvider, CallbackRenderingControl2SetHorizontalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetHorizontalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVerticalKeystone(THandle aProvider, CallbackRenderingControl2GetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVerticalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetVerticalKeystone(THandle aProvider, CallbackRenderingControl2SetVerticalKeystone aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetVerticalKeystone(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetMute(THandle aProvider, CallbackRenderingControl2GetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetMute(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetMute(THandle aProvider, CallbackRenderingControl2SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetMute(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVolume(THandle aProvider, CallbackRenderingControl2GetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVolume(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetVolume(THandle aProvider, CallbackRenderingControl2SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetVolume(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDB(THandle aProvider, CallbackRenderingControl2GetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVolumeDB(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetVolumeDB(THandle aProvider, CallbackRenderingControl2SetVolumeDB aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetVolumeDB(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetVolumeDBRange(THandle aProvider, CallbackRenderingControl2GetVolumeDBRange aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetVolumeDBRange(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetLoudness(THandle aProvider, CallbackRenderingControl2GetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetLoudness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetLoudness(THandle aProvider, CallbackRenderingControl2SetLoudness aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetLoudness(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionGetStateVariables(THandle aProvider, CallbackRenderingControl2GetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionGetStateVariables(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgRenderingControl2EnableActionSetStateVariables(THandle aProvider, CallbackRenderingControl2SetStateVariables aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->EnableActionSetStateVariables(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgRenderingControl2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgRenderingControl2GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgRenderingControl2C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

