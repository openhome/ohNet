#include "DvUpnpOrgRenderingControl2.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgRenderingControl2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgRenderingControl2Cpp::DvProviderUpnpOrgRenderingControl2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 2)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionListPresets()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSelectPreset()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetMute()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetMute()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVolume()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetVolume()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVolumeDB()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetVolumeDB()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVolumeDBRange()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetLoudness()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetLoudness()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("StateVariableList"));
    action->AddOutputParameter(new ParameterString("StateVariableValuePairs"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetStateVariables()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStateVariables");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("RenderingControlUDN"));
    action->AddInputParameter(new ParameterString("ServiceType"));
    action->AddInputParameter(new ParameterString("ServiceId"));
    action->AddInputParameter(new ParameterString("StateVariableValuePairs"));
    action->AddOutputParameter(new ParameterString("StateVariableList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetStateVariables);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoListPresets(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentPresetNameList;
    ListPresets(aVersion, InstanceID, respCurrentPresetNameList);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    Brn buf_CurrentPresetNameList((const TByte*)respCurrentPresetNameList.c_str(), (TUint)respCurrentPresetNameList.length());
    respWriterCurrentPresetNameList.Write(buf_CurrentPresetNameList);
    aInvocation.InvocationWriteStringEnd("CurrentPresetNameList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSelectPreset(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetBrightness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBrightness;
    GetBrightness(aVersion, InstanceID, respCurrentBrightness);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentBrightness(aInvocation, "CurrentBrightness");
    respWriterCurrentBrightness.Write(respCurrentBrightness);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetBrightness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    SetBrightness(aVersion, InstanceID, DesiredBrightness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetContrast(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentContrast;
    GetContrast(aVersion, InstanceID, respCurrentContrast);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentContrast(aInvocation, "CurrentContrast");
    respWriterCurrentContrast.Write(respCurrentContrast);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetContrast(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    SetContrast(aVersion, InstanceID, DesiredContrast);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetSharpness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentSharpness;
    GetSharpness(aVersion, InstanceID, respCurrentSharpness);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentSharpness(aInvocation, "CurrentSharpness");
    respWriterCurrentSharpness.Write(respCurrentSharpness);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetSharpness(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    SetSharpness(aVersion, InstanceID, DesiredSharpness);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoGain;
    GetRedVideoGain(aVersion, InstanceID, respCurrentRedVideoGain);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    respWriterCurrentRedVideoGain.Write(respCurrentRedVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    SetRedVideoGain(aVersion, InstanceID, DesiredRedVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoGain;
    GetGreenVideoGain(aVersion, InstanceID, respCurrentGreenVideoGain);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    respWriterCurrentGreenVideoGain.Write(respCurrentGreenVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    SetGreenVideoGain(aVersion, InstanceID, DesiredGreenVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoGain;
    GetBlueVideoGain(aVersion, InstanceID, respCurrentBlueVideoGain);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    respWriterCurrentBlueVideoGain.Write(respCurrentBlueVideoGain);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoGain(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    SetBlueVideoGain(aVersion, InstanceID, DesiredBlueVideoGain);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoBlackLevel;
    GetRedVideoBlackLevel(aVersion, InstanceID, respCurrentRedVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    respWriterCurrentRedVideoBlackLevel.Write(respCurrentRedVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetRedVideoBlackLevel(aVersion, InstanceID, DesiredRedVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoBlackLevel;
    GetGreenVideoBlackLevel(aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    respWriterCurrentGreenVideoBlackLevel.Write(respCurrentGreenVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetGreenVideoBlackLevel(aVersion, InstanceID, DesiredGreenVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoBlackLevel;
    GetBlueVideoBlackLevel(aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    respWriterCurrentBlueVideoBlackLevel.Write(respCurrentBlueVideoBlackLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    SetBlueVideoBlackLevel(aVersion, InstanceID, DesiredBlueVideoBlackLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetColorTemperature(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentColorTemperature;
    GetColorTemperature(aVersion, InstanceID, respCurrentColorTemperature);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    respWriterCurrentColorTemperature.Write(respCurrentColorTemperature);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetColorTemperature(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    SetColorTemperature(aVersion, InstanceID, DesiredColorTemperature);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetHorizontalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentHorizontalKeystone;
    GetHorizontalKeystone(aVersion, InstanceID, respCurrentHorizontalKeystone);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    respWriterCurrentHorizontalKeystone.Write(respCurrentHorizontalKeystone);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetHorizontalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    SetHorizontalKeystone(aVersion, InstanceID, DesiredHorizontalKeystone);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVerticalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVerticalKeystone;
    GetVerticalKeystone(aVersion, InstanceID, respCurrentVerticalKeystone);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    respWriterCurrentVerticalKeystone.Write(respCurrentVerticalKeystone);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetVerticalKeystone(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    SetVerticalKeystone(aVersion, InstanceID, DesiredVerticalKeystone);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetMute(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseBool respWriterCurrentMute(aInvocation, "CurrentMute");
    respWriterCurrentMute.Write(respCurrentMute);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetMute(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolume(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseUint respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolume(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDB(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseInt respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolumeDB(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDBRange(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseInt respWriterMinValue(aInvocation, "MinValue");
    respWriterMinValue.Write(respMinValue);
    DviInvocationResponseInt respWriterMaxValue(aInvocation, "MaxValue");
    respWriterMaxValue.Write(respMaxValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetLoudness(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseBool respWriterCurrentLoudness(aInvocation, "CurrentLoudness");
    respWriterCurrentLoudness.Write(respCurrentLoudness);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetLoudness(IDviInvocation& aInvocation, uint32_t aVersion)
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

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetStateVariables(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseString respWriterStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    Brn buf_StateVariableValuePairs((const TByte*)respStateVariableValuePairs.c_str(), (TUint)respStateVariableValuePairs.length());
    respWriterStateVariableValuePairs.Write(buf_StateVariableValuePairs);
    aInvocation.InvocationWriteStringEnd("StateVariableValuePairs");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetStateVariables(IDviInvocation& aInvocation, uint32_t aVersion)
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
    DviInvocationResponseString respWriterStateVariableList(aInvocation, "StateVariableList");
    Brn buf_StateVariableList((const TByte*)respStateVariableList.c_str(), (TUint)respStateVariableList.length());
    respWriterStateVariableList.Write(buf_StateVariableList);
    aInvocation.InvocationWriteStringEnd("StateVariableList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::ListPresets(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SelectPreset(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetBrightness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetBrightness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetContrast(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetContrast(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetSharpness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetSharpness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetRedVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetRedVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetGreenVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetGreenVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetBlueVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetBlueVideoGain(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetRedVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetRedVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetGreenVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetGreenVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetBlueVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetBlueVideoBlackLevel(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetColorTemperature(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetColorTemperature(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetHorizontalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetHorizontalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVerticalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetVerticalKeystone(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetMute(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetMute(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVolume(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetVolume(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVolumeDB(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetVolumeDB(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVolumeDBRange(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aMinValue*/, int32_t& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetLoudness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetLoudness(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetStateVariables(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aStateVariableList*/, std::string& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetStateVariables(uint32_t /*aVersion*/, uint32_t /*aInstanceID*/, const std::string& /*aRenderingControlUDN*/, const std::string& /*aServiceType*/, const std::string& /*aServiceId*/, const std::string& /*aStateVariableValuePairs*/, std::string& /*aStateVariableList*/)
{
    ASSERTS();
}

