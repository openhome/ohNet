#include "DvUpnpOrgRenderingControl2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgRenderingControl2::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgRenderingControl2::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgRenderingControl2::DvProviderUpnpOrgRenderingControl2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 2)
{
    Construct();
}

DvProviderUpnpOrgRenderingControl2::DvProviderUpnpOrgRenderingControl2(DviDevice& aDevice)
    : DvProvider(aDevice, "upnp.org", "RenderingControl", 2)
{
    Construct();
}

void DvProviderUpnpOrgRenderingControl2::Construct()
{
    iPropertyLastChange = NULL;
}

void DvProviderUpnpOrgRenderingControl2::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgRenderingControl2::EnableActionListPresets()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSelectPreset()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SelectPreset");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("PresetName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVolumeDBRange()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDBRange");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("MinValue"));
    action->AddOutputParameter(new ParameterInt("MaxValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("RenderingControlUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::DoListPresets(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    ListPresets(invocation, InstanceID, respCurrentPresetNameList);
}

void DvProviderUpnpOrgRenderingControl2::DoSelectPreset(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SelectPreset(invocation, InstanceID, PresetName);
}

void DvProviderUpnpOrgRenderingControl2::DoGetBrightness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    GetBrightness(invocation, InstanceID, respCurrentBrightness);
}

void DvProviderUpnpOrgRenderingControl2::DoSetBrightness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetBrightness(invocation, InstanceID, DesiredBrightness);
}

void DvProviderUpnpOrgRenderingControl2::DoGetContrast(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    GetContrast(invocation, InstanceID, respCurrentContrast);
}

void DvProviderUpnpOrgRenderingControl2::DoSetContrast(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetContrast(invocation, InstanceID, DesiredContrast);
}

void DvProviderUpnpOrgRenderingControl2::DoGetSharpness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    GetSharpness(invocation, InstanceID, respCurrentSharpness);
}

void DvProviderUpnpOrgRenderingControl2::DoSetSharpness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetSharpness(invocation, InstanceID, DesiredSharpness);
}

void DvProviderUpnpOrgRenderingControl2::DoGetRedVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    GetRedVideoGain(invocation, InstanceID, respCurrentRedVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoSetRedVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetRedVideoGain(invocation, InstanceID, DesiredRedVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    GetGreenVideoGain(invocation, InstanceID, respCurrentGreenVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetGreenVideoGain(invocation, InstanceID, DesiredGreenVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    GetBlueVideoGain(invocation, InstanceID, respCurrentBlueVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetBlueVideoGain(invocation, InstanceID, DesiredBlueVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    GetRedVideoBlackLevel(invocation, InstanceID, respCurrentRedVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetRedVideoBlackLevel(invocation, InstanceID, DesiredRedVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    GetGreenVideoBlackLevel(invocation, InstanceID, respCurrentGreenVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetGreenVideoBlackLevel(invocation, InstanceID, DesiredGreenVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    GetBlueVideoBlackLevel(invocation, InstanceID, respCurrentBlueVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetBlueVideoBlackLevel(invocation, InstanceID, DesiredBlueVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoGetColorTemperature(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    GetColorTemperature(invocation, InstanceID, respCurrentColorTemperature);
}

void DvProviderUpnpOrgRenderingControl2::DoSetColorTemperature(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetColorTemperature(invocation, InstanceID, DesiredColorTemperature);
}

void DvProviderUpnpOrgRenderingControl2::DoGetHorizontalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    GetHorizontalKeystone(invocation, InstanceID, respCurrentHorizontalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoSetHorizontalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetHorizontalKeystone(invocation, InstanceID, DesiredHorizontalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVerticalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    GetVerticalKeystone(invocation, InstanceID, respCurrentVerticalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoSetVerticalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetVerticalKeystone(invocation, InstanceID, DesiredVerticalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoGetMute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respCurrentMute(aInvocation, "CurrentMute");
    GetMute(invocation, InstanceID, Channel, respCurrentMute);
}

void DvProviderUpnpOrgRenderingControl2::DoSetMute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetMute(invocation, InstanceID, Channel, DesiredMute);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVolume(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respCurrentVolume(aInvocation, "CurrentVolume");
    GetVolume(invocation, InstanceID, Channel, respCurrentVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoSetVolume(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TUint DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetVolume(invocation, InstanceID, Channel, DesiredVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVolumeDB(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respCurrentVolume(aInvocation, "CurrentVolume");
    GetVolumeDB(invocation, InstanceID, Channel, respCurrentVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoSetVolumeDB(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TInt DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetVolumeDB(invocation, InstanceID, Channel, DesiredVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVolumeDBRange(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respMinValue(aInvocation, "MinValue");
    DviInvocationResponseInt respMaxValue(aInvocation, "MaxValue");
    GetVolumeDBRange(invocation, InstanceID, Channel, respMinValue, respMaxValue);
}

void DvProviderUpnpOrgRenderingControl2::DoGetLoudness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respCurrentLoudness(aInvocation, "CurrentLoudness");
    GetLoudness(invocation, InstanceID, Channel, respCurrentLoudness);
}

void DvProviderUpnpOrgRenderingControl2::DoSetLoudness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetLoudness(invocation, InstanceID, Channel, DesiredLoudness);
}

void DvProviderUpnpOrgRenderingControl2::DoGetStateVariables(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", StateVariableList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    GetStateVariables(invocation, InstanceID, StateVariableList, respStateVariableValuePairs);
}

void DvProviderUpnpOrgRenderingControl2::DoSetStateVariables(IDviInvocation& aInvocation)
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respStateVariableList(aInvocation, "StateVariableList");
    SetStateVariables(invocation, InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, respStateVariableList);
}

void DvProviderUpnpOrgRenderingControl2::ListPresets(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SelectPreset(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetBrightness(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetBrightness(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetContrast(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetContrast(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetSharpness(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetSharpness(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetRedVideoGain(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetRedVideoGain(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetGreenVideoGain(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetGreenVideoGain(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetBlueVideoGain(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetBlueVideoGain(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetRedVideoBlackLevel(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetRedVideoBlackLevel(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetGreenVideoBlackLevel(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetGreenVideoBlackLevel(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetBlueVideoBlackLevel(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetBlueVideoBlackLevel(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetColorTemperature(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetColorTemperature(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TUint /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetHorizontalKeystone(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseInt& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetHorizontalKeystone(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TInt /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVerticalKeystone(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, IDvInvocationResponseInt& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetVerticalKeystone(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, TInt /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetMute(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseBool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetMute(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVolume(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseUint& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetVolume(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TUint /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVolumeDB(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseInt& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetVolumeDB(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TInt /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVolumeDBRange(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseInt& /*aMinValue*/, IDvInvocationResponseInt& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetLoudness(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseBool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetLoudness(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetStateVariables(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aStateVariableList*/, IDvInvocationResponseString& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetStateVariables(IDvInvocation& /*aResponse*/, TUint /*aInstanceID*/, const Brx& /*aRenderingControlUDN*/, const Brx& /*aServiceType*/, const Brx& /*aServiceId*/, const Brx& /*aStateVariableValuePairs*/, IDvInvocationResponseString& /*aStateVariableList*/)
{
    ASSERTS();
}

