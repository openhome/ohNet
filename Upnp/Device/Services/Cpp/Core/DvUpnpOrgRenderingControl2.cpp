#include <Core/DvUpnpOrgRenderingControl2.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgRenderingControl2::SetPropertyLastChange(const Brx& aValue)
{
    SetPropertyString(*iPropertyLastChange, aValue);
}

void DvServiceUpnpOrgRenderingControl2::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvServiceUpnpOrgRenderingControl2::DvServiceUpnpOrgRenderingControl2(DvDevice& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "RenderingControl", 2)
{
    Functor empty;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvServiceUpnpOrgRenderingControl2::EnableActionListPresets()
{
    Zapp::Action* action = new Zapp::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoListPresets);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSelectPreset()
{
    Zapp::Action* action = new Zapp::Action("SelectPreset");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"FactoryDefaults";
    action->AddInputParameter(new ParameterString("PresetName", allowedValues, 1));
    delete[] allowedValues;
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetBrightness()
{
    Zapp::Action* action = new Zapp::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetContrast()
{
    Zapp::Action* action = new Zapp::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetContrast()
{
    Zapp::Action* action = new Zapp::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetSharpness()
{
    Zapp::Action* action = new Zapp::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetSharpness()
{
    Zapp::Action* action = new Zapp::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetRedVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetRedVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetGreenVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetGreenVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetBlueVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetBlueVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetRedVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetRedVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetGreenVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetGreenVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetBlueVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetBlueVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetColorTemperature()
{
    Zapp::Action* action = new Zapp::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetColorTemperature()
{
    Zapp::Action* action = new Zapp::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetHorizontalKeystone()
{
    Zapp::Action* action = new Zapp::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetHorizontalKeystone()
{
    Zapp::Action* action = new Zapp::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetVerticalKeystone()
{
    Zapp::Action* action = new Zapp::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetVerticalKeystone()
{
    Zapp::Action* action = new Zapp::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetMute()
{
    Zapp::Action* action = new Zapp::Action("GetMute");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetMute);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetMute()
{
    Zapp::Action* action = new Zapp::Action("SetMute");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetMute);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetVolume()
{
    Zapp::Action* action = new Zapp::Action("GetVolume");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetVolume()
{
    Zapp::Action* action = new Zapp::Action("SetVolume");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetVolumeDB()
{
    Zapp::Action* action = new Zapp::Action("GetVolumeDB");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetVolumeDB()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeDB");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetVolumeDBRange()
{
    Zapp::Action* action = new Zapp::Action("GetVolumeDBRange");
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetLoudness()
{
    Zapp::Action* action = new Zapp::Action("GetLoudness");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetLoudness()
{
    Zapp::Action* action = new Zapp::Action("SetLoudness");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("InstanceID"));
    index = 0;
    allowedValues = new TChar*[1];
    allowedValues[index++] = (TChar*)"Master";
    action->AddInputParameter(new ParameterString("Channel", allowedValues, 1));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterBool("DesiredLoudness"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionGetStateVariables()
{
    Zapp::Action* action = new Zapp::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::EnableActionSetStateVariables()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("RenderingControlUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2::DoListPresets(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    ListPresets(resp, aVersion, InstanceID, respCurrentPresetNameList);
}

void DvServiceUpnpOrgRenderingControl2::DoSelectPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SelectPreset(resp, aVersion, InstanceID, PresetName);
}

void DvServiceUpnpOrgRenderingControl2::DoGetBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    GetBrightness(resp, aVersion, InstanceID, respCurrentBrightness);
}

void DvServiceUpnpOrgRenderingControl2::DoSetBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBrightness(resp, aVersion, InstanceID, DesiredBrightness);
}

void DvServiceUpnpOrgRenderingControl2::DoGetContrast(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    GetContrast(resp, aVersion, InstanceID, respCurrentContrast);
}

void DvServiceUpnpOrgRenderingControl2::DoSetContrast(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetContrast(resp, aVersion, InstanceID, DesiredContrast);
}

void DvServiceUpnpOrgRenderingControl2::DoGetSharpness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    GetSharpness(resp, aVersion, InstanceID, respCurrentSharpness);
}

void DvServiceUpnpOrgRenderingControl2::DoSetSharpness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSharpness(resp, aVersion, InstanceID, DesiredSharpness);
}

void DvServiceUpnpOrgRenderingControl2::DoGetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    GetRedVideoGain(resp, aVersion, InstanceID, respCurrentRedVideoGain);
}

void DvServiceUpnpOrgRenderingControl2::DoSetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRedVideoGain(resp, aVersion, InstanceID, DesiredRedVideoGain);
}

void DvServiceUpnpOrgRenderingControl2::DoGetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    GetGreenVideoGain(resp, aVersion, InstanceID, respCurrentGreenVideoGain);
}

void DvServiceUpnpOrgRenderingControl2::DoSetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetGreenVideoGain(resp, aVersion, InstanceID, DesiredGreenVideoGain);
}

void DvServiceUpnpOrgRenderingControl2::DoGetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    GetBlueVideoGain(resp, aVersion, InstanceID, respCurrentBlueVideoGain);
}

void DvServiceUpnpOrgRenderingControl2::DoSetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBlueVideoGain(resp, aVersion, InstanceID, DesiredBlueVideoGain);
}

void DvServiceUpnpOrgRenderingControl2::DoGetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    GetRedVideoBlackLevel(resp, aVersion, InstanceID, respCurrentRedVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl2::DoSetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRedVideoBlackLevel(resp, aVersion, InstanceID, DesiredRedVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl2::DoGetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    GetGreenVideoBlackLevel(resp, aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl2::DoSetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetGreenVideoBlackLevel(resp, aVersion, InstanceID, DesiredGreenVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl2::DoGetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    GetBlueVideoBlackLevel(resp, aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl2::DoSetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBlueVideoBlackLevel(resp, aVersion, InstanceID, DesiredBlueVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl2::DoGetColorTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    GetColorTemperature(resp, aVersion, InstanceID, respCurrentColorTemperature);
}

void DvServiceUpnpOrgRenderingControl2::DoSetColorTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetColorTemperature(resp, aVersion, InstanceID, DesiredColorTemperature);
}

void DvServiceUpnpOrgRenderingControl2::DoGetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    GetHorizontalKeystone(resp, aVersion, InstanceID, respCurrentHorizontalKeystone);
}

void DvServiceUpnpOrgRenderingControl2::DoSetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetHorizontalKeystone(resp, aVersion, InstanceID, DesiredHorizontalKeystone);
}

void DvServiceUpnpOrgRenderingControl2::DoGetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    GetVerticalKeystone(resp, aVersion, InstanceID, respCurrentVerticalKeystone);
}

void DvServiceUpnpOrgRenderingControl2::DoSetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVerticalKeystone(resp, aVersion, InstanceID, DesiredVerticalKeystone);
}

void DvServiceUpnpOrgRenderingControl2::DoGetMute(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoSetMute(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoGetVolume(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoSetVolume(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoGetVolumeDB(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoSetVolumeDB(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoGetVolumeDBRange(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoGetLoudness(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoSetLoudness(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoGetStateVariables(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::DoSetStateVariables(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl2::ListPresets(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SelectPreset(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aPresetName*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetContrast(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetContrast(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetSharpness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetSharpness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetRedVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetRedVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetGreenVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetGreenVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetBlueVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetBlueVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetRedVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetRedVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetGreenVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetGreenVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetBlueVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetBlueVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetColorTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetColorTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetHorizontalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseInt& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetHorizontalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetVerticalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseInt& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetVerticalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseBool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseUint& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TUint /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetVolumeDB(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseInt& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetVolumeDB(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TInt /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetVolumeDBRange(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseInt& /*aMinValue*/, IInvocationResponseInt& /*aMaxValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetLoudness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseBool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetLoudness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredLoudness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::GetStateVariables(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aStateVariableList*/, IInvocationResponseString& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2::SetStateVariables(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aRenderingControlUDN*/, const Brx& /*aServiceType*/, const Brx& /*aServiceId*/, const Brx& /*aStateVariableValuePairs*/, IInvocationResponseString& /*aStateVariableList*/)
{
    ASSERTS();
}

