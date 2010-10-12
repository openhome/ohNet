#include <Std/DvUpnpOrgRenderingControl2.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgRenderingControl2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyLastChange, buf);
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceUpnpOrgRenderingControl2Cpp::DvServiceUpnpOrgRenderingControl2Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "RenderingControl", 2)
{
    Functor empty;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionListPresets()
{
    Zapp::Action* action = new Zapp::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoListPresets);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSelectPreset()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetBrightness()
{
    Zapp::Action* action = new Zapp::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetBrightness()
{
    Zapp::Action* action = new Zapp::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetContrast()
{
    Zapp::Action* action = new Zapp::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetContrast()
{
    Zapp::Action* action = new Zapp::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetSharpness()
{
    Zapp::Action* action = new Zapp::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetSharpness()
{
    Zapp::Action* action = new Zapp::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetRedVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetRedVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetGreenVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetGreenVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetBlueVideoGain()
{
    Zapp::Action* action = new Zapp::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetBlueVideoGain()
{
    Zapp::Action* action = new Zapp::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetRedVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetRedVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetGreenVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetGreenVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetBlueVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetBlueVideoBlackLevel()
{
    Zapp::Action* action = new Zapp::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetColorTemperature()
{
    Zapp::Action* action = new Zapp::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetColorTemperature()
{
    Zapp::Action* action = new Zapp::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetHorizontalKeystone()
{
    Zapp::Action* action = new Zapp::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetHorizontalKeystone()
{
    Zapp::Action* action = new Zapp::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetVerticalKeystone()
{
    Zapp::Action* action = new Zapp::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetVerticalKeystone()
{
    Zapp::Action* action = new Zapp::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetMute()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetMute);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetMute()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetVolume()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetVolume()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetVolumeDB()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetVolumeDB()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetVolumeDBRange()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetLoudness()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetLoudness()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionGetStateVariables()
{
    Zapp::Action* action = new Zapp::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::EnableActionSetStateVariables()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("RenderingControlUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgRenderingControl2Cpp::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoListPresets(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentPresetNameList;
    ListPresets(aVersion, InstanceID, respCurrentPresetNameList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    Brn buf_CurrentPresetNameList((const TByte*)respCurrentPresetNameList.c_str(), respCurrentPresetNameList.length());
    respWriterCurrentPresetNameList.Write(buf_CurrentPresetNameList);
    aInvocation.InvocationWriteStringEnd("CurrentPresetNameList");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSelectPreset(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_PresetName;
    aInvocation.InvocationReadString("PresetName", buf_PresetName);
    std::string PresetName((const char*)buf_PresetName.Ptr(), buf_PresetName.Bytes());
    aInvocation.InvocationReadEnd();
    SelectPreset(aVersion, InstanceID, PresetName);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBrightness;
    GetBrightness(aVersion, InstanceID, respCurrentBrightness);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentBrightness(aInvocation, "CurrentBrightness");
    respWriterCurrentBrightness.Write(respCurrentBrightness);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetBrightness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    SetBrightness(aVersion, InstanceID, DesiredBrightness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetContrast(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentContrast;
    GetContrast(aVersion, InstanceID, respCurrentContrast);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentContrast(aInvocation, "CurrentContrast");
    respWriterCurrentContrast.Write(respCurrentContrast);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetContrast(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    SetContrast(aVersion, InstanceID, DesiredContrast);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetSharpness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentSharpness;
    GetSharpness(aVersion, InstanceID, respCurrentSharpness);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentSharpness(aInvocation, "CurrentSharpness");
    respWriterCurrentSharpness.Write(respCurrentSharpness);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetSharpness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    SetSharpness(aVersion, InstanceID, DesiredSharpness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoGain;
    GetRedVideoGain(aVersion, InstanceID, respCurrentRedVideoGain);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    respWriterCurrentRedVideoGain.Write(respCurrentRedVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetRedVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    SetRedVideoGain(aVersion, InstanceID, DesiredRedVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoGain;
    GetGreenVideoGain(aVersion, InstanceID, respCurrentGreenVideoGain);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    respWriterCurrentGreenVideoGain.Write(respCurrentGreenVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetGreenVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    SetGreenVideoGain(aVersion, InstanceID, DesiredGreenVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoGain;
    GetBlueVideoGain(aVersion, InstanceID, respCurrentBlueVideoGain);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    respWriterCurrentBlueVideoGain.Write(respCurrentBlueVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetBlueVideoGain(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    SetBlueVideoGain(aVersion, InstanceID, DesiredBlueVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoBlackLevel;
    GetRedVideoBlackLevel(aVersion, InstanceID, respCurrentRedVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    respWriterCurrentRedVideoBlackLevel.Write(respCurrentRedVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetRedVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetRedVideoBlackLevel(aVersion, InstanceID, DesiredRedVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoBlackLevel;
    GetGreenVideoBlackLevel(aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    respWriterCurrentGreenVideoBlackLevel.Write(respCurrentGreenVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetGreenVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetGreenVideoBlackLevel(aVersion, InstanceID, DesiredGreenVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoBlackLevel;
    GetBlueVideoBlackLevel(aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    respWriterCurrentBlueVideoBlackLevel.Write(respCurrentBlueVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetBlueVideoBlackLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetBlueVideoBlackLevel(aVersion, InstanceID, DesiredBlueVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetColorTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentColorTemperature;
    GetColorTemperature(aVersion, InstanceID, respCurrentColorTemperature);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    respWriterCurrentColorTemperature.Write(respCurrentColorTemperature);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetColorTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    SetColorTemperature(aVersion, InstanceID, DesiredColorTemperature);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentHorizontalKeystone;
    GetHorizontalKeystone(aVersion, InstanceID, respCurrentHorizontalKeystone);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    respWriterCurrentHorizontalKeystone.Write(respCurrentHorizontalKeystone);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetHorizontalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    SetHorizontalKeystone(aVersion, InstanceID, DesiredHorizontalKeystone);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVerticalKeystone;
    GetVerticalKeystone(aVersion, InstanceID, respCurrentVerticalKeystone);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    respWriterCurrentVerticalKeystone.Write(respCurrentVerticalKeystone);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetVerticalKeystone(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    SetVerticalKeystone(aVersion, InstanceID, DesiredVerticalKeystone);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetMute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    bool respCurrentMute;
    GetMute(aVersion, InstanceID, Channel, respCurrentMute);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterCurrentMute(aInvocation, "CurrentMute");
    respWriterCurrentMute.Write(respCurrentMute);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetMute(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    bool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    SetMute(aVersion, InstanceID, Channel, DesiredMute);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentVolume;
    GetVolume(aVersion, InstanceID, Channel, respCurrentVolume);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetVolume(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    uint32_t DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    SetVolume(aVersion, InstanceID, Channel, DesiredVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetVolumeDB(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVolume;
    GetVolumeDB(aVersion, InstanceID, Channel, respCurrentVolume);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetVolumeDB(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    int32_t DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    SetVolumeDB(aVersion, InstanceID, Channel, DesiredVolume);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetVolumeDBRange(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respMinValue;
    int32_t respMaxValue;
    GetVolumeDBRange(aVersion, InstanceID, Channel, respMinValue, respMaxValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterMinValue(aInvocation, "MinValue");
    respWriterMinValue.Write(respMinValue);
    InvocationResponseInt respWriterMaxValue(aInvocation, "MaxValue");
    respWriterMaxValue.Write(respMaxValue);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetLoudness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    bool respCurrentLoudness;
    GetLoudness(aVersion, InstanceID, Channel, respCurrentLoudness);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterCurrentLoudness(aInvocation, "CurrentLoudness");
    respWriterCurrentLoudness.Write(respCurrentLoudness);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetLoudness(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    bool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    SetLoudness(aVersion, InstanceID, Channel, DesiredLoudness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoGetStateVariables(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", buf_StateVariableList);
    std::string StateVariableList((const char*)buf_StateVariableList.Ptr(), buf_StateVariableList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respStateVariableValuePairs;
    GetStateVariables(aVersion, InstanceID, StateVariableList, respStateVariableValuePairs);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    Brn buf_StateVariableValuePairs((const TByte*)respStateVariableValuePairs.c_str(), respStateVariableValuePairs.length());
    respWriterStateVariableValuePairs.Write(buf_StateVariableValuePairs);
    aInvocation.InvocationWriteStringEnd("StateVariableValuePairs");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::DoSetStateVariables(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_RenderingControlUDN;
    aInvocation.InvocationReadString("RenderingControlUDN", buf_RenderingControlUDN);
    std::string RenderingControlUDN((const char*)buf_RenderingControlUDN.Ptr(), buf_RenderingControlUDN.Bytes());
    Brhz buf_ServiceType;
    aInvocation.InvocationReadString("ServiceType", buf_ServiceType);
    std::string ServiceType((const char*)buf_ServiceType.Ptr(), buf_ServiceType.Bytes());
    Brhz buf_ServiceId;
    aInvocation.InvocationReadString("ServiceId", buf_ServiceId);
    std::string ServiceId((const char*)buf_ServiceId.Ptr(), buf_ServiceId.Bytes());
    Brhz buf_StateVariableValuePairs;
    aInvocation.InvocationReadString("StateVariableValuePairs", buf_StateVariableValuePairs);
    std::string StateVariableValuePairs((const char*)buf_StateVariableValuePairs.Ptr(), buf_StateVariableValuePairs.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respStateVariableList;
    SetStateVariables(aVersion, InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, respStateVariableList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterStateVariableList(aInvocation, "StateVariableList");
    Brn buf_StateVariableList((const TByte*)respStateVariableList.c_str(), respStateVariableList.length());
    respWriterStateVariableList.Write(buf_StateVariableList);
    aInvocation.InvocationWriteStringEnd("StateVariableList");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgRenderingControl2Cpp::ListPresets(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SelectPreset(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aPresetName*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetBrightness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetBrightness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetContrast(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetContrast(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetSharpness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetSharpness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetRedVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetRedVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetGreenVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetGreenVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetBlueVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetBlueVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetRedVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetRedVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetGreenVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetGreenVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetBlueVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetBlueVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetColorTemperature(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetColorTemperature(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetHorizontalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetHorizontalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetVerticalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetVerticalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetMute(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetMute(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetVolume(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetVolume(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetVolumeDB(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetVolumeDB(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetVolumeDBRange(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aMinValue*/, int32_t& /*aMaxValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetLoudness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetLoudness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredLoudness*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::GetStateVariables(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aStateVariableList*/, std::string& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgRenderingControl2Cpp::SetStateVariables(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aRenderingControlUDN*/, const std::string& /*aServiceType*/, const std::string& /*aServiceId*/, const std::string& /*aStateVariableValuePairs*/, std::string& /*aStateVariableList*/)
{
    ASSERTS();
}

