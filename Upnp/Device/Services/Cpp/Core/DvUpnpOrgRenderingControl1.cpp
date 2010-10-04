#include <Core/DvUpnpOrgRenderingControl1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgRenderingControl1::SetPropertyLastChange(const Brx& aValue)
{
    SetPropertyString(*iPropertyLastChange, aValue);
}

void DvServiceUpnpOrgRenderingControl1::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvServiceUpnpOrgRenderingControl1::DvServiceUpnpOrgRenderingControl1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "RenderingControl", 1)
{
    Functor empty;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvServiceUpnpOrgRenderingControl1::EnableActionListPresets()
{
    Zapp::Action* action = new Zapp::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoListPresets);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSelectPreset()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetBrightness()
{
    Zapp::Action* action = new Zapp::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetContrast()
{
    Zapp::Action* action = new Zapp::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetContrast()
{
    Zapp::Action* action = new Zapp::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetSharpness()
{
    Zapp::Action* action = new Zapp::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetSharpness()
{
    Zapp::Action* action = new Zapp::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetRedVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetRedVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetGreenVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetGreenVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetBlueVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetBlueVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetRedVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetRedVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetGreenVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetGreenVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetBlueVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetBlueVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetColorTemperature()
{
    Zapp::Action* action = new Zapp::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetColorTemperature()
{
    Zapp::Action* action = new Zapp::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetHorizontalKeystone()
{
    Zapp::Action* action = new Zapp::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetHorizontalKeystone()
{
    Zapp::Action* action = new Zapp::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetVerticalKeystone()
{
    Zapp::Action* action = new Zapp::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetVerticalKeystone()
{
    Zapp::Action* action = new Zapp::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetMute()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetMute);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetMute()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetMute);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetVolume()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetVolume()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetVolumeDB()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetVolumeDB()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetVolumeDBRange()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionGetLoudness()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::EnableActionSetLoudness()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl1::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl1::DoListPresets(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    ListPresets(resp, aVersion, InstanceID, respCurrentPresetNameList);
}

void DvServiceUpnpOrgRenderingControl1::DoSelectPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SelectPreset(resp, aVersion, InstanceID, PresetName);
}

void DvServiceUpnpOrgRenderingControl1::DoGetBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    GetBrightness(resp, aVersion, InstanceID, respCurrentBrightness);
}

void DvServiceUpnpOrgRenderingControl1::DoSetBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBrightness(resp, aVersion, InstanceID, DesiredBrightness);
}

void DvServiceUpnpOrgRenderingControl1::DoGetContrast(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    GetContrast(resp, aVersion, InstanceID, respCurrentContrast);
}

void DvServiceUpnpOrgRenderingControl1::DoSetContrast(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetContrast(resp, aVersion, InstanceID, DesiredContrast);
}

void DvServiceUpnpOrgRenderingControl1::DoGetSharpness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    GetSharpness(resp, aVersion, InstanceID, respCurrentSharpness);
}

void DvServiceUpnpOrgRenderingControl1::DoSetSharpness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetSharpness(resp, aVersion, InstanceID, DesiredSharpness);
}

void DvServiceUpnpOrgRenderingControl1::DoGetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    GetRedVideoGain(resp, aVersion, InstanceID, respCurrentRedVideoGain);
}

void DvServiceUpnpOrgRenderingControl1::DoSetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRedVideoGain(resp, aVersion, InstanceID, DesiredRedVideoGain);
}

void DvServiceUpnpOrgRenderingControl1::DoGetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    GetGreenVideoGain(resp, aVersion, InstanceID, respCurrentGreenVideoGain);
}

void DvServiceUpnpOrgRenderingControl1::DoSetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetGreenVideoGain(resp, aVersion, InstanceID, DesiredGreenVideoGain);
}

void DvServiceUpnpOrgRenderingControl1::DoGetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    GetBlueVideoGain(resp, aVersion, InstanceID, respCurrentBlueVideoGain);
}

void DvServiceUpnpOrgRenderingControl1::DoSetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBlueVideoGain(resp, aVersion, InstanceID, DesiredBlueVideoGain);
}

void DvServiceUpnpOrgRenderingControl1::DoGetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    GetRedVideoBlackLevel(resp, aVersion, InstanceID, respCurrentRedVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl1::DoSetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRedVideoBlackLevel(resp, aVersion, InstanceID, DesiredRedVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl1::DoGetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    GetGreenVideoBlackLevel(resp, aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl1::DoSetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetGreenVideoBlackLevel(resp, aVersion, InstanceID, DesiredGreenVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl1::DoGetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    GetBlueVideoBlackLevel(resp, aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl1::DoSetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetBlueVideoBlackLevel(resp, aVersion, InstanceID, DesiredBlueVideoBlackLevel);
}

void DvServiceUpnpOrgRenderingControl1::DoGetColorTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    GetColorTemperature(resp, aVersion, InstanceID, respCurrentColorTemperature);
}

void DvServiceUpnpOrgRenderingControl1::DoSetColorTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetColorTemperature(resp, aVersion, InstanceID, DesiredColorTemperature);
}

void DvServiceUpnpOrgRenderingControl1::DoGetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    GetHorizontalKeystone(resp, aVersion, InstanceID, respCurrentHorizontalKeystone);
}

void DvServiceUpnpOrgRenderingControl1::DoSetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetHorizontalKeystone(resp, aVersion, InstanceID, DesiredHorizontalKeystone);
}

void DvServiceUpnpOrgRenderingControl1::DoGetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    GetVerticalKeystone(resp, aVersion, InstanceID, respCurrentVerticalKeystone);
}

void DvServiceUpnpOrgRenderingControl1::DoSetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVerticalKeystone(resp, aVersion, InstanceID, DesiredVerticalKeystone);
}

void DvServiceUpnpOrgRenderingControl1::DoGetMute(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoSetMute(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoGetVolume(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoSetVolume(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoGetVolumeDB(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoSetVolumeDB(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoGetVolumeDBRange(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoGetLoudness(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::DoSetLoudness(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgRenderingControl1::ListPresets(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseString& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SelectPreset(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aPresetName*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetBrightness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetContrast(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetContrast(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetSharpness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetSharpness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetRedVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetRedVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetGreenVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetGreenVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetBlueVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetBlueVideoGain(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetRedVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetRedVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetGreenVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetGreenVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetBlueVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetBlueVideoBlackLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetColorTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseUint& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetColorTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetHorizontalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseInt& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetHorizontalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetVerticalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IInvocationResponseInt& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetVerticalKeystone(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseBool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetMute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseUint& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetVolume(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TUint /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetVolumeDB(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseInt& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetVolumeDB(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TInt /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetVolumeDBRange(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseInt& /*aMinValue*/, IInvocationResponseInt& /*aMaxValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::GetLoudness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IInvocationResponseBool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl1::SetLoudness(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredLoudness*/)
{
    ASSERTS();
}

