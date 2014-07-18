#include "DvUpnpOrgRenderingControl1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgRenderingControl1Cpp::SetPropertyLastChange(const std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetPropertyLastChange(std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgRenderingControl1Cpp::DvProviderUpnpOrgRenderingControl1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 1)
{
    iPropertyLastChange = NULL;
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionListPresets()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSelectPreset()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SelectPreset");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("PresetName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredMute"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterUint("CurrentVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterUint("DesiredVolume", 0, 2147483647, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("CurrentVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetVolumeDB()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolumeDB");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterInt("DesiredVolume"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetVolumeDBRange()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVolumeDBRange");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterInt("MinValue"));
    action->AddOutputParameter(new ParameterInt("MaxValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionGetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddOutputParameter(new ParameterBool("CurrentLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::EnableActionSetLoudness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoudness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterString("Channel"));
    action->AddInputParameter(new ParameterBool("DesiredLoudness"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1Cpp::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1Cpp::DoListPresets(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSelectPreset(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetBrightness(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetBrightness(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetContrast(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetContrast(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetSharpness(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetSharpness(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoGain(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoGain(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoGain(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoGain(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoGain(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoGain(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetColorTemperature(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetColorTemperature(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetHorizontalKeystone(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetHorizontalKeystone(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVerticalKeystone(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetVerticalKeystone(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetMute(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetMute(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolume(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolume(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDB(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetVolumeDB(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetVolumeDBRange(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoGetLoudness(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::DoSetLoudness(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgRenderingControl1Cpp::ListPresets(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, std::string& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SelectPreset(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetBrightness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetBrightness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetContrast(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetContrast(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetSharpness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetSharpness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetRedVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetRedVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetGreenVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetGreenVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetBlueVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetBlueVideoGain(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetRedVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetRedVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetGreenVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetGreenVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetBlueVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetBlueVideoBlackLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetColorTemperature(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetColorTemperature(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, uint32_t /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetHorizontalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetHorizontalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVerticalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetVerticalKeystone(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, int32_t /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetMute(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetMute(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVolume(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetVolume(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, uint32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVolumeDB(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetVolumeDB(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetVolumeDBRange(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, int32_t& /*aMinValue*/, int32_t& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::GetLoudness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1Cpp::SetLoudness(IDvInvocationStd& /*aInvocation*/, uint32_t /*aInstanceID*/, const std::string& /*aChannel*/, bool /*aDesiredLoudness*/)
{
    ASSERTS();
}

