#include "DvUpnpOrgRenderingControl1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgRenderingControl1::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgRenderingControl1::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgRenderingControl1::DvProviderUpnpOrgRenderingControl1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "RenderingControl", 1)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgRenderingControl1::EnableActionListPresets()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ListPresets");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterString("CurrentPresetNameList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoListPresets);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSelectPreset()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSelectPreset);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetBrightness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBrightness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBrightness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetBrightness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetContrast()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetContrast");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredContrast", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetContrast);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetSharpness()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSharpness");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredSharpness", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetSharpness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoGain"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetRedVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoGain"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetRedVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetGreenVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetGreenVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetBlueVideoGain()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoGain");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetBlueVideoGain);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetRedVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRedVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetRedVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetGreenVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetGreenVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetGreenVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetBlueVideoBlackLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBlueVideoBlackLevel");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetBlueVideoBlackLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetColorTemperature()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetColorTemperature");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterUint("DesiredColorTemperature", 0, 0, 1));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetColorTemperature);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetHorizontalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetHorizontalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetHorizontalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetVerticalKeystone()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVerticalKeystone");
    action->AddInputParameter(new ParameterUint("InstanceID"));
    action->AddInputParameter(new ParameterInt("DesiredVerticalKeystone"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetVerticalKeystone);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetMute()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetMute()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetVolume()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetVolume()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetVolumeDB()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetVolumeDB()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetVolumeDB);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetVolumeDBRange()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetVolumeDBRange);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionGetLoudness()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoGetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::EnableActionSetLoudness()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgRenderingControl1::DoSetLoudness);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgRenderingControl1::DoListPresets(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respCurrentPresetNameList(aInvocation, "CurrentPresetNameList");
    ListPresets(resp, aVersion, InstanceID, respCurrentPresetNameList);
}

void DvProviderUpnpOrgRenderingControl1::DoSelectPreset(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz PresetName;
    aInvocation.InvocationReadString("PresetName", PresetName);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SelectPreset(resp, aVersion, InstanceID, PresetName);
}

void DvProviderUpnpOrgRenderingControl1::DoGetBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentBrightness(aInvocation, "CurrentBrightness");
    GetBrightness(resp, aVersion, InstanceID, respCurrentBrightness);
}

void DvProviderUpnpOrgRenderingControl1::DoSetBrightness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBrightness = aInvocation.InvocationReadUint("DesiredBrightness");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetBrightness(resp, aVersion, InstanceID, DesiredBrightness);
}

void DvProviderUpnpOrgRenderingControl1::DoGetContrast(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentContrast(aInvocation, "CurrentContrast");
    GetContrast(resp, aVersion, InstanceID, respCurrentContrast);
}

void DvProviderUpnpOrgRenderingControl1::DoSetContrast(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredContrast = aInvocation.InvocationReadUint("DesiredContrast");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetContrast(resp, aVersion, InstanceID, DesiredContrast);
}

void DvProviderUpnpOrgRenderingControl1::DoGetSharpness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentSharpness(aInvocation, "CurrentSharpness");
    GetSharpness(resp, aVersion, InstanceID, respCurrentSharpness);
}

void DvProviderUpnpOrgRenderingControl1::DoSetSharpness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredSharpness = aInvocation.InvocationReadUint("DesiredSharpness");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetSharpness(resp, aVersion, InstanceID, DesiredSharpness);
}

void DvProviderUpnpOrgRenderingControl1::DoGetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentRedVideoGain(aInvocation, "CurrentRedVideoGain");
    GetRedVideoGain(resp, aVersion, InstanceID, respCurrentRedVideoGain);
}

void DvProviderUpnpOrgRenderingControl1::DoSetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoGain = aInvocation.InvocationReadUint("DesiredRedVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetRedVideoGain(resp, aVersion, InstanceID, DesiredRedVideoGain);
}

void DvProviderUpnpOrgRenderingControl1::DoGetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentGreenVideoGain(aInvocation, "CurrentGreenVideoGain");
    GetGreenVideoGain(resp, aVersion, InstanceID, respCurrentGreenVideoGain);
}

void DvProviderUpnpOrgRenderingControl1::DoSetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoGain = aInvocation.InvocationReadUint("DesiredGreenVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetGreenVideoGain(resp, aVersion, InstanceID, DesiredGreenVideoGain);
}

void DvProviderUpnpOrgRenderingControl1::DoGetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentBlueVideoGain(aInvocation, "CurrentBlueVideoGain");
    GetBlueVideoGain(resp, aVersion, InstanceID, respCurrentBlueVideoGain);
}

void DvProviderUpnpOrgRenderingControl1::DoSetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoGain = aInvocation.InvocationReadUint("DesiredBlueVideoGain");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetBlueVideoGain(resp, aVersion, InstanceID, DesiredBlueVideoGain);
}

void DvProviderUpnpOrgRenderingControl1::DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentRedVideoBlackLevel(aInvocation, "CurrentRedVideoBlackLevel");
    GetRedVideoBlackLevel(resp, aVersion, InstanceID, respCurrentRedVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl1::DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredRedVideoBlackLevel = aInvocation.InvocationReadUint("DesiredRedVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetRedVideoBlackLevel(resp, aVersion, InstanceID, DesiredRedVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl1::DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentGreenVideoBlackLevel(aInvocation, "CurrentGreenVideoBlackLevel");
    GetGreenVideoBlackLevel(resp, aVersion, InstanceID, respCurrentGreenVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl1::DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredGreenVideoBlackLevel = aInvocation.InvocationReadUint("DesiredGreenVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetGreenVideoBlackLevel(resp, aVersion, InstanceID, DesiredGreenVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl1::DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentBlueVideoBlackLevel(aInvocation, "CurrentBlueVideoBlackLevel");
    GetBlueVideoBlackLevel(resp, aVersion, InstanceID, respCurrentBlueVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl1::DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredBlueVideoBlackLevel = aInvocation.InvocationReadUint("DesiredBlueVideoBlackLevel");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetBlueVideoBlackLevel(resp, aVersion, InstanceID, DesiredBlueVideoBlackLevel);
}

void DvProviderUpnpOrgRenderingControl1::DoGetColorTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentColorTemperature(aInvocation, "CurrentColorTemperature");
    GetColorTemperature(resp, aVersion, InstanceID, respCurrentColorTemperature);
}

void DvProviderUpnpOrgRenderingControl1::DoSetColorTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TUint DesiredColorTemperature = aInvocation.InvocationReadUint("DesiredColorTemperature");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetColorTemperature(resp, aVersion, InstanceID, DesiredColorTemperature);
}

void DvProviderUpnpOrgRenderingControl1::DoGetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseInt respCurrentHorizontalKeystone(aInvocation, "CurrentHorizontalKeystone");
    GetHorizontalKeystone(resp, aVersion, InstanceID, respCurrentHorizontalKeystone);
}

void DvProviderUpnpOrgRenderingControl1::DoSetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredHorizontalKeystone = aInvocation.InvocationReadInt("DesiredHorizontalKeystone");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetHorizontalKeystone(resp, aVersion, InstanceID, DesiredHorizontalKeystone);
}

void DvProviderUpnpOrgRenderingControl1::DoGetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseInt respCurrentVerticalKeystone(aInvocation, "CurrentVerticalKeystone");
    GetVerticalKeystone(resp, aVersion, InstanceID, respCurrentVerticalKeystone);
}

void DvProviderUpnpOrgRenderingControl1::DoSetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    TInt DesiredVerticalKeystone = aInvocation.InvocationReadInt("DesiredVerticalKeystone");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetVerticalKeystone(resp, aVersion, InstanceID, DesiredVerticalKeystone);
}

void DvProviderUpnpOrgRenderingControl1::DoGetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseBool respCurrentMute(aInvocation, "CurrentMute");
    GetMute(resp, aVersion, InstanceID, Channel, respCurrentMute);
}

void DvProviderUpnpOrgRenderingControl1::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredMute = aInvocation.InvocationReadBool("DesiredMute");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetMute(resp, aVersion, InstanceID, Channel, DesiredMute);
}

void DvProviderUpnpOrgRenderingControl1::DoGetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respCurrentVolume(aInvocation, "CurrentVolume");
    GetVolume(resp, aVersion, InstanceID, Channel, respCurrentVolume);
}

void DvProviderUpnpOrgRenderingControl1::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TUint DesiredVolume = aInvocation.InvocationReadUint("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetVolume(resp, aVersion, InstanceID, Channel, DesiredVolume);
}

void DvProviderUpnpOrgRenderingControl1::DoGetVolumeDB(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseInt respCurrentVolume(aInvocation, "CurrentVolume");
    GetVolumeDB(resp, aVersion, InstanceID, Channel, respCurrentVolume);
}

void DvProviderUpnpOrgRenderingControl1::DoSetVolumeDB(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TInt DesiredVolume = aInvocation.InvocationReadInt("DesiredVolume");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetVolumeDB(resp, aVersion, InstanceID, Channel, DesiredVolume);
}

void DvProviderUpnpOrgRenderingControl1::DoGetVolumeDBRange(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseInt respMinValue(aInvocation, "MinValue");
    DviInvocationResponseInt respMaxValue(aInvocation, "MaxValue");
    GetVolumeDBRange(resp, aVersion, InstanceID, Channel, respMinValue, respMaxValue);
}

void DvProviderUpnpOrgRenderingControl1::DoGetLoudness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseBool respCurrentLoudness(aInvocation, "CurrentLoudness");
    GetLoudness(resp, aVersion, InstanceID, Channel, respCurrentLoudness);
}

void DvProviderUpnpOrgRenderingControl1::DoSetLoudness(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint InstanceID = aInvocation.InvocationReadUint("InstanceID");
    Brhz Channel;
    aInvocation.InvocationReadString("Channel", Channel);
    TBool DesiredLoudness = aInvocation.InvocationReadBool("DesiredLoudness");
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    SetLoudness(resp, aVersion, InstanceID, Channel, DesiredLoudness);
}

void DvProviderUpnpOrgRenderingControl1::ListPresets(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseString& /*aCurrentPresetNameList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SelectPreset(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aPresetName*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetBrightness(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetBrightness(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBrightness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetContrast(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetContrast(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredContrast*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetSharpness(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetSharpness(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredSharpness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetRedVideoGain(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetRedVideoGain(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetGreenVideoGain(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetGreenVideoGain(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetBlueVideoGain(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetBlueVideoGain(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoGain*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetRedVideoBlackLevel(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetRedVideoBlackLevel(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredRedVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetGreenVideoBlackLevel(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetGreenVideoBlackLevel(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredGreenVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetBlueVideoBlackLevel(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetBlueVideoBlackLevel(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredBlueVideoBlackLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetColorTemperature(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseUint& /*aCurrentColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetColorTemperature(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TUint /*aDesiredColorTemperature*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetHorizontalKeystone(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseInt& /*aCurrentHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetHorizontalKeystone(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredHorizontalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetVerticalKeystone(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, IDvInvocationResponseInt& /*aCurrentVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetVerticalKeystone(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, TInt /*aDesiredVerticalKeystone*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetMute(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseBool& /*aCurrentMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetMute(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredMute*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetVolume(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseUint& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetVolume(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TUint /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetVolumeDB(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseInt& /*aCurrentVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetVolumeDB(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TInt /*aDesiredVolume*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetVolumeDBRange(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseInt& /*aMinValue*/, IDvInvocationResponseInt& /*aMaxValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::GetLoudness(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, IDvInvocationResponseBool& /*aCurrentLoudness*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgRenderingControl1::SetLoudness(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aInstanceID*/, const Brx& /*aChannel*/, TBool /*aDesiredLoudness*/)
{
    ASSERTS();
}

