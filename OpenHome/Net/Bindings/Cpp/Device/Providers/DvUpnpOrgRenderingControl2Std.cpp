#include "DvUpnpOrgRenderingControl2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgRenderingControl2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetPropertyLastChange(std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgRenderingControl2Cpp::DvProviderUpnpOrgRenderingControl2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 2)
{
    iPropertyLastChange = NULL;
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
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
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("PresetName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1));
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
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetVolumeDBRange()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDBRange");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("MinValue"));
    action->AddOutputParameter(new ParameterInt("MaxValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionGetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl2Cpp::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl2Cpp::EnableActionSetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
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

void DvProviderUpnpOrgRenderingControl2Cpp::DoListPresets(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    std::string respCurrentPresetNameList;
    DvInvocationStd invocation(aInvocation);
    ListPresets(invocation, InstanceID, respCurrentPresetNameList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    Brn buf_CurrentPresetNameList((const TByte*)respCurrentPresetNameList.c_str(), (TUint)respCurrentPresetNameList.length());
    respWriterCurrentPresetNameList.Write(buf_CurrentPresetNameList);
    aInvocation.InvocationWriteStringEnd("CurrentPresetNameList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSelectPreset(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_PresetName;
    aInvocation.InvocationReadString("PresetName", buf_PresetName);
    std::string PresetName((const char*)buf_PresetName.Ptr(), buf_PresetName.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SelectPreset(invocation, InstanceID, PresetName);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetBrightness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBrightness;
    DvInvocationStd invocation(aInvocation);
    GetBrightness(invocation, InstanceID, respCurrentBrightness);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentBrightness(aInvocation, "CurrentBrightness");
    respWriterCurrentBrightness.Write(respCurrentBrightness);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetBrightness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetBrightness(invocation, InstanceID, DesiredBrightness);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetContrast(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentContrast;
    DvInvocationStd invocation(aInvocation);
    GetContrast(invocation, InstanceID, respCurrentContrast);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentContrast(aInvocation, "CurrentContrast");
    respWriterCurrentContrast.Write(respCurrentContrast);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetContrast(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetContrast(invocation, InstanceID, DesiredContrast);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetSharpness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentSharpness;
    DvInvocationStd invocation(aInvocation);
    GetSharpness(invocation, InstanceID, respCurrentSharpness);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentSharpness(aInvocation, "CurrentSharpness");
    respWriterCurrentSharpness.Write(respCurrentSharpness);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetSharpness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetSharpness(invocation, InstanceID, DesiredSharpness);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoGain;
    DvInvocationStd invocation(aInvocation);
    GetRedVideoGain(invocation, InstanceID, respCurrentRedVideoGain);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    respWriterCurrentRedVideoGain.Write(respCurrentRedVideoGain);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetRedVideoGain(invocation, InstanceID, DesiredRedVideoGain);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoGain;
    DvInvocationStd invocation(aInvocation);
    GetGreenVideoGain(invocation, InstanceID, respCurrentGreenVideoGain);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    respWriterCurrentGreenVideoGain.Write(respCurrentGreenVideoGain);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetGreenVideoGain(invocation, InstanceID, DesiredGreenVideoGain);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoGain;
    DvInvocationStd invocation(aInvocation);
    GetBlueVideoGain(invocation, InstanceID, respCurrentBlueVideoGain);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    respWriterCurrentBlueVideoGain.Write(respCurrentBlueVideoGain);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoGain(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetBlueVideoGain(invocation, InstanceID, DesiredBlueVideoGain);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentRedVideoBlackLevel;
    DvInvocationStd invocation(aInvocation);
    GetRedVideoBlackLevel(invocation, InstanceID, respCurrentRedVideoBlackLevel);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    respWriterCurrentRedVideoBlackLevel.Write(respCurrentRedVideoBlackLevel);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetRedVideoBlackLevel(invocation, InstanceID, DesiredRedVideoBlackLevel);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentGreenVideoBlackLevel;
    DvInvocationStd invocation(aInvocation);
    GetGreenVideoBlackLevel(invocation, InstanceID, respCurrentGreenVideoBlackLevel);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    respWriterCurrentGreenVideoBlackLevel.Write(respCurrentGreenVideoBlackLevel);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetGreenVideoBlackLevel(invocation, InstanceID, DesiredGreenVideoBlackLevel);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentBlueVideoBlackLevel;
    DvInvocationStd invocation(aInvocation);
    GetBlueVideoBlackLevel(invocation, InstanceID, respCurrentBlueVideoBlackLevel);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    respWriterCurrentBlueVideoBlackLevel.Write(respCurrentBlueVideoBlackLevel);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetBlueVideoBlackLevel(invocation, InstanceID, DesiredBlueVideoBlackLevel);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetColorTemperature(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentColorTemperature;
    DvInvocationStd invocation(aInvocation);
    GetColorTemperature(invocation, InstanceID, respCurrentColorTemperature);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    respWriterCurrentColorTemperature.Write(respCurrentColorTemperature);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetColorTemperature(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    uint32_t DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetColorTemperature(invocation, InstanceID, DesiredColorTemperature);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetHorizontalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentHorizontalKeystone;
    DvInvocationStd invocation(aInvocation);
    GetHorizontalKeystone(invocation, InstanceID, respCurrentHorizontalKeystone);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    respWriterCurrentHorizontalKeystone.Write(respCurrentHorizontalKeystone);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetHorizontalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetHorizontalKeystone(invocation, InstanceID, DesiredHorizontalKeystone);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVerticalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVerticalKeystone;
    DvInvocationStd invocation(aInvocation);
    GetVerticalKeystone(invocation, InstanceID, respCurrentVerticalKeystone);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    respWriterCurrentVerticalKeystone.Write(respCurrentVerticalKeystone);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetVerticalKeystone(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    int32_t DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetVerticalKeystone(invocation, InstanceID, DesiredVerticalKeystone);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetMute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    bool respCurrentMute;
    DvInvocationStd invocation(aInvocation);
    GetMute(invocation, InstanceID, Channel, respCurrentMute);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterCurrentMute(aInvocation, "CurrentMute");
    respWriterCurrentMute.Write(respCurrentMute);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetMute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    bool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetMute(invocation, InstanceID, Channel, DesiredMute);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolume(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respCurrentVolume;
    DvInvocationStd invocation(aInvocation);
    GetVolume(invocation, InstanceID, Channel, respCurrentVolume);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolume(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    uint32_t DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetVolume(invocation, InstanceID, Channel, DesiredVolume);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDB(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respCurrentVolume;
    DvInvocationStd invocation(aInvocation);
    GetVolumeDB(invocation, InstanceID, Channel, respCurrentVolume);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterCurrentVolume(aInvocation, "CurrentVolume");
    respWriterCurrentVolume.Write(respCurrentVolume);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetVolumeDB(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    int32_t DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetVolumeDB(invocation, InstanceID, Channel, DesiredVolume);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetVolumeDBRange(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    int32_t respMinValue;
    int32_t respMaxValue;
    DvInvocationStd invocation(aInvocation);
    GetVolumeDBRange(invocation, InstanceID, Channel, respMinValue, respMaxValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterMinValue(aInvocation, "MinValue");
    respWriterMinValue.Write(respMinValue);
    DviInvocationResponseInt respWriterMaxValue(aInvocation, "MaxValue");
    respWriterMaxValue.Write(respMaxValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetLoudness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    aInvocation.InvocationReadEnd();
    bool respCurrentLoudness;
    DvInvocationStd invocation(aInvocation);
    GetLoudness(invocation, InstanceID, Channel, respCurrentLoudness);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterCurrentLoudness(aInvocation, "CurrentLoudness");
    respWriterCurrentLoudness.Write(respCurrentLoudness);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetLoudness(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_Channel;
    aInvocation.InvocationReadString("Channel", buf_Channel);
    std::string Channel((const char*)buf_Channel.Ptr(), buf_Channel.Bytes());
    bool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetLoudness(invocation, InstanceID, Channel, DesiredLoudness);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoGetStateVariables(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz buf_StateVariableList;
    aInvocation.InvocationReadString("StateVariableList", buf_StateVariableList);
    std::string StateVariableList((const char*)buf_StateVariableList.Ptr(), buf_StateVariableList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respStateVariableValuePairs;
    DvInvocationStd invocation(aInvocation);
    GetStateVariables(invocation, InstanceID, StateVariableList, respStateVariableValuePairs);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterStateVariableValuePairs(aInvocation, "StateVariableValuePairs");
    Brn buf_StateVariableValuePairs((const TByte*)respStateVariableValuePairs.c_str(), (TUint)respStateVariableValuePairs.length());
    respWriterStateVariableValuePairs.Write(buf_StateVariableValuePairs);
    aInvocation.InvocationWriteStringEnd("StateVariableValuePairs");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::DoSetStateVariables(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    SetStateVariables(invocation, InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, respStateVariableList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterStateVariableList(aInvocation, "StateVariableList");
    Brn buf_StateVariableList((const TByte*)respStateVariableList.c_str(), (TUint)respStateVariableList.length());
    respWriterStateVariableList.Write(buf_StateVariableList);
    aInvocation.InvocationWriteStringEnd("StateVariableList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgRenderingControl2Cpp::ListPresets(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SelectPreset(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetBrightness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetBrightness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetContrast(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetContrast(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetSharpness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetSharpness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetRedVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetRedVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetGreenVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetGreenVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetBlueVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetBlueVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetRedVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetRedVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetGreenVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetGreenVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetBlueVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetBlueVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetColorTemperature(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetColorTemperature(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetHorizontalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetHorizontalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVerticalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetVerticalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetMute(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetMute(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVolume(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetVolume(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVolumeDB(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetVolumeDB(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetVolumeDBRange(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aMinValue*/, int32_t& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetLoudness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetLoudness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::GetStateVariables(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aStateVariableList*/, std::string& /*aStateVariableValuePairs*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl2Cpp::SetStateVariables(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aRenderingControlUDN*/, const std::string& /*aServiceType*/, const std::string& /*aServiceId*/, const std::string& /*aStateVariableValuePairs*/, std::string& /*aStateVariableList*/)
{
    ASSERTS();
}

