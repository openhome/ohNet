#include "DvUpnpOrgRenderingControl2.h"
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

TBool DvProviderUpnpOrgRenderingControl2::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgRenderingControl2::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgRenderingControl2::DvProviderUpnpOrgRenderingControl2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 2)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
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
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"FactoryDefaults";
    action->AddInputParameter(new ParameterString("PresetName", allowedValues, 1));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
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
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetMute()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVolume()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetVolume()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVolumeDB()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetVolumeDB()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetVolumeDBRange()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionGetLoudness()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2::EnableActionSetLoudness()
{
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

void DvProviderUpnpOrgRenderingControl2::DoListPresets(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    ListPresets(resp, aVersion, InstanceID, respCurrentPresetNameList);
}

void DvProviderUpnpOrgRenderingControl2::DoSelectPreset(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SelectPreset(resp, aVersion, InstanceID, PresetName);
}

void DvProviderUpnpOrgRenderingControl2::DoGetBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    GetBrightness(resp, aVersion, InstanceID, respCurrentBrightness);
}

void DvProviderUpnpOrgRenderingControl2::DoSetBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBrightness(resp, aVersion, InstanceID, DesiredBrightness);
}

void DvProviderUpnpOrgRenderingControl2::DoGetContrast(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    GetContrast(resp, aVersion, InstanceID, respCurrentContrast);
}

void DvProviderUpnpOrgRenderingControl2::DoSetContrast(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetContrast(resp, aVersion, InstanceID, DesiredContrast);
}

void DvProviderUpnpOrgRenderingControl2::DoGetSharpness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    GetSharpness(resp, aVersion, InstanceID, respCurrentSharpness);
}

void DvProviderUpnpOrgRenderingControl2::DoSetSharpness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSharpness(resp, aVersion, InstanceID, DesiredSharpness);
}

void DvProviderUpnpOrgRenderingControl2::DoGetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    GetRedVideoGain(resp, aVersion, InstanceID, respCurrentRedVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoSetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRedVideoGain(resp, aVersion, InstanceID, DesiredRedVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    GetGreenVideoGain(resp, aVersion, InstanceID, respCurrentGreenVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetGreenVideoGain(resp, aVersion, InstanceID, DesiredGreenVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    GetBlueVideoGain(resp, aVersion, InstanceID, respCurrentBlueVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBlueVideoGain(resp, aVersion, InstanceID, DesiredBlueVideoGain);
}

void DvProviderUpnpOrgRenderingControl2::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    GetRedVideoBlackLevel(resp, aVersion, InstanceID, respCurrentRedVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRedVideoBlackLevel(resp, aVersion, InstanceID, DesiredRedVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    GetGreenVideoBlackLevel(resp, aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetGreenVideoBlackLevel(resp, aVersion, InstanceID, DesiredGreenVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    GetBlueVideoBlackLevel(resp, aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBlueVideoBlackLevel(resp, aVersion, InstanceID, DesiredBlueVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl2::DoGetColorTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    GetColorTemperature(resp, aVersion, InstanceID, respCurrentColorTemperature);
}

void DvProviderUpnpOrgRenderingControl2::DoSetColorTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetColorTemperature(resp, aVersion, InstanceID, DesiredColorTemperature);
}

void DvProviderUpnpOrgRenderingControl2::DoGetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    GetHorizontalKeystone(resp, aVersion, InstanceID, respCurrentHorizontalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoSetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetHorizontalKeystone(resp, aVersion, InstanceID, DesiredHorizontalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    GetVerticalKeystone(resp, aVersion, InstanceID, respCurrentVerticalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoSetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVerticalKeystone(resp, aVersion, InstanceID, DesiredVerticalKeystone);
}

void DvProviderUpnpOrgRenderingControl2::DoGetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respCurrentMute(aInvocation, "CurrentMute");
    GetMute(resp, aVersion, InstanceID, Channel, respCurrentMute);
}

void DvProviderUpnpOrgRenderingControl2::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetMute(resp, aVersion, InstanceID, Channel, DesiredMute);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentVolume(aInvocation, "CurrentVolume");
    GetVolume(resp, aVersion, InstanceID, Channel, respCurrentVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TUint DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolume(resp, aVersion, InstanceID, Channel, DesiredVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVolumeDB(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentVolume(aInvocation, "CurrentVolume");
    GetVolumeDB(resp, aVersion, InstanceID, Channel, respCurrentVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoSetVolumeDB(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TInt DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolumeDB(resp, aVersion, InstanceID, Channel, DesiredVolume);
}

void DvProviderUpnpOrgRenderingControl2::DoGetVolumeDBRange(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respMinValue(aInvocation, "MinValue");
    InvocationResponseInt respMaxValue(aInvocation, "MaxValue");
    GetVolumeDBRange(resp, aVersion, InstanceID, Channel, respMinValue, respMaxValue);
}

void DvProviderUpnpOrgRenderingControl2::DoGetLoudness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respCurrentLoudness(aInvocation, "CurrentLoudness");
    GetLoudness(resp, aVersion, InstanceID, Channel, respCurrentLoudness);
}

void DvProviderUpnpOrgRenderingControl2::DoSetLoudness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetLoudness(resp, aVersion, InstanceID, Channel, DesiredLoudness);
}

void DvProviderUpnpOrgRenderingControl2::DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", StateVariableList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    GetStateVariables(resp, aVersion, InstanceID, StateVariableList, respStateVariableValuePairs);
}

void DvProviderUpnpOrgRenderingControl2::DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion)
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
    InvocationResponseString respStateVariableList(aInvocation, "StateVariableList");
    SetStateVariables(resp, aVersion, InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, respStateVariableList);
}

void DvProviderUpnpOrgRenderingControl2::ListPresets(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SelectPreset(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetContrast(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetContrast(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetSharpness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetSharpness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetRedVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetRedVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetGreenVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetGreenVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetBlueVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetBlueVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetRedVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetRedVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetGreenVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetGreenVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetBlueVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetBlueVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetColorTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetColorTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetHorizontalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseInt& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetHorizontalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVerticalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseInt& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetVerticalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseBool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseUint& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TUint /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVolumeDB(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseInt& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetVolumeDB(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TInt /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetVolumeDBRange(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseInt& /*aMinValue*/, IInvocationResponseInt& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetLoudness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseBool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetLoudness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::GetStateVariables(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aStateVariableList*/, IInvocationResponseString& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2::SetStateVariables(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aRenderingControlUDN*/, const Brx& /*aServiceType*/, const Brx& /*aServiceId*/, const Brx& /*aStateVariableValuePairs*/, IInvocationResponseString& /*aStateVariableList*/)
{
    ASSERTS();
}

