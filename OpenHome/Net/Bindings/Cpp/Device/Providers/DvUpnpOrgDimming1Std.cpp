#include "DvUpnpOrgDimming1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyLoadLevelStatus(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyLoadLevelStatus(uint32_t& aValue)
{
    aValue = iPropertyLoadLevelStatus->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyStepDelta(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyStepDelta(uint32_t& aValue)
{
    aValue = iPropertyStepDelta->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyRampRate(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyRampRate(uint32_t& aValue)
{
    aValue = iPropertyRampRate->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyIsRamping(bool aValue)
{
    return SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyIsRamping(bool& aValue)
{
    aValue = iPropertyIsRamping->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyRampPaused(bool aValue)
{
    return SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyRampPaused(bool& aValue)
{
    aValue = iPropertyRampPaused->Value();
}

DvProviderUpnpOrgDimming1Cpp::DvProviderUpnpOrgDimming1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "Dimming", 1)
{
    
    iPropertyLoadLevelStatus = new PropertyUint(new ParameterUint("LoadLevelStatus", 0, 100));
    iService->AddProperty(iPropertyLoadLevelStatus); // passes ownership
    iPropertyStepDelta = new PropertyUint(new ParameterUint("StepDelta", 1, 100));
    iService->AddProperty(iPropertyStepDelta); // passes ownership
    iPropertyRampRate = new PropertyUint(new ParameterUint("RampRate", 0, 100));
    iService->AddProperty(iPropertyRampRate); // passes ownership
    iPropertyIsRamping = new PropertyBool(new ParameterBool("IsRamping"));
    iService->AddProperty(iPropertyIsRamping); // passes ownership
    iPropertyRampPaused = new PropertyBool(new ParameterBool("RampPaused"));
    iService->AddProperty(iPropertyRampPaused); // passes ownership
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetLoadLevelTarget()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoadLevelTarget");
    action->AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetLoadLevelTarget()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoadLevelTarget");
    action->AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetLoadLevelStatus()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoadLevelStatus");
    action->AddOutputParameter(new ParameterRelated("retLoadlevelStatus", *iPropertyLoadLevelStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetOnEffectLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetOnEffectLevel");
    action->AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetOnEffectLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetOnEffect()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetOnEffect");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    action->AddInputParameter(new ParameterString("newOnEffect", allowedValues, 3));
    delete[] allowedValues;
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetOnEffect);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetOnEffectParameters()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetOnEffectParameters");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    action->AddOutputParameter(new ParameterString("retOnEffect", allowedValues, 3));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterUint("retOnEffectLevel", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetOnEffectParameters);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStepUp()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StepUp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStepUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStepDown()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StepDown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStepDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStartRampUp()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StartRampUp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStartRampUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStartRampDown()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StartRampDown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStartRampDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStopRamp()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStopRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStartRampToLevel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StartRampToLevel");
    action->AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
    action->AddInputParameter(new ParameterUint("newRampTime"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStartRampToLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetStepDelta()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStepDelta");
    action->AddInputParameter(new ParameterRelated("newStepDelta", *iPropertyStepDelta));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetStepDelta()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStepDelta");
    action->AddOutputParameter(new ParameterRelated("retStepDelta", *iPropertyStepDelta));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetRampRate()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRampRate");
    action->AddInputParameter(new ParameterRelated("newRampRate", *iPropertyRampRate));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetRampRate()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRampRate");
    action->AddOutputParameter(new ParameterRelated("retRampRate", *iPropertyRampRate));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionPauseRamp()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PauseRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoPauseRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionResumeRamp()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResumeRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoResumeRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetIsRamping()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetIsRamping");
    action->AddOutputParameter(new ParameterRelated("retIsRamping", *iPropertyIsRamping));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetIsRamping);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetRampPaused()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRampPaused");
    action->AddOutputParameter(new ParameterRelated("retRampPaused", *iPropertyRampPaused));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetRampPaused);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetRampTime()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRampTime");
    action->AddOutputParameter(new ParameterUint("retRampTime"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetRampTime);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::DoSetLoadLevelTarget(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    SetLoadLevelTarget(aVersion, newLoadlevelTarget);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelTarget(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respGetLoadlevelTarget;
    GetLoadLevelTarget(aVersion, respGetLoadlevelTarget);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    respWriterGetLoadlevelTarget.Write(respGetLoadlevelTarget);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelStatus(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretLoadlevelStatus;
    GetLoadLevelStatus(aVersion, respretLoadlevelStatus);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    respWriterretLoadlevelStatus.Write(respretLoadlevelStatus);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetOnEffectLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    SetOnEffectLevel(aVersion, newOnEffectLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetOnEffect(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_newOnEffect;
    aInvocation.InvocationReadString("newOnEffect", buf_newOnEffect);
    std::string newOnEffect((const char*)buf_newOnEffect.Ptr(), buf_newOnEffect.Bytes());
    aInvocation.InvocationReadEnd();
    SetOnEffect(aVersion, newOnEffect);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetOnEffectParameters(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respretOnEffect;
    uint32_t respretOnEffectLevel;
    GetOnEffectParameters(aVersion, respretOnEffect, respretOnEffectLevel);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterretOnEffect(aInvocation, "retOnEffect");
    Brn buf_retOnEffect((const TByte*)respretOnEffect.c_str(), (TUint)respretOnEffect.length());
    respWriterretOnEffect.Write(buf_retOnEffect);
    aInvocation.InvocationWriteStringEnd("retOnEffect");
    DviInvocationResponseUint respWriterretOnEffectLevel(aInvocation, "retOnEffectLevel");
    respWriterretOnEffectLevel.Write(respretOnEffectLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStepUp(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StepUp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStepDown(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StepDown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampUp(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StartRampUp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampDown(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StartRampDown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStopRamp(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StopRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampToLevel(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    uint32_t newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    StartRampToLevel(aVersion, newLoadLevelTarget, newRampTime);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetStepDelta(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    SetStepDelta(aVersion, newStepDelta);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetStepDelta(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretStepDelta;
    GetStepDelta(aVersion, respretStepDelta);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretStepDelta(aInvocation, "retStepDelta");
    respWriterretStepDelta.Write(respretStepDelta);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetRampRate(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    SetRampRate(aVersion, newRampRate);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampRate(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretRampRate;
    GetRampRate(aVersion, respretRampRate);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretRampRate(aInvocation, "retRampRate");
    respWriterretRampRate.Write(respretRampRate);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoPauseRamp(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    PauseRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoResumeRamp(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    ResumeRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetIsRamping(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respretIsRamping;
    GetIsRamping(aVersion, respretIsRamping);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterretIsRamping(aInvocation, "retIsRamping");
    respWriterretIsRamping.Write(respretIsRamping);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampPaused(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respretRampPaused;
    GetRampPaused(aVersion, respretRampPaused);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterretRampPaused(aInvocation, "retRampPaused");
    respWriterretRampPaused.Write(respretRampPaused);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampTime(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretRampTime;
    GetRampTime(aVersion, respretRampTime);
	aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretRampTime(aInvocation, "retRampTime");
    respWriterretRampTime.Write(respretRampTime);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::SetLoadLevelTarget(uint32_t /*aVersion*/, uint32_t /*anewLoadlevelTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetLoadLevelTarget(uint32_t /*aVersion*/, uint32_t& /*aGetLoadlevelTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetLoadLevelStatus(uint32_t /*aVersion*/, uint32_t& /*aretLoadlevelStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetOnEffectLevel(uint32_t /*aVersion*/, uint32_t /*anewOnEffectLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetOnEffect(uint32_t /*aVersion*/, const std::string& /*anewOnEffect*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetOnEffectParameters(uint32_t /*aVersion*/, std::string& /*aretOnEffect*/, uint32_t& /*aretOnEffectLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StepUp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StepDown(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StartRampUp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StartRampDown(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StopRamp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StartRampToLevel(uint32_t /*aVersion*/, uint32_t /*anewLoadLevelTarget*/, uint32_t /*anewRampTime*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetStepDelta(uint32_t /*aVersion*/, uint32_t /*anewStepDelta*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetStepDelta(uint32_t /*aVersion*/, uint32_t& /*aretStepDelta*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetRampRate(uint32_t /*aVersion*/, uint32_t /*anewRampRate*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetRampRate(uint32_t /*aVersion*/, uint32_t& /*aretRampRate*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::PauseRamp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::ResumeRamp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetIsRamping(uint32_t /*aVersion*/, bool& /*aretIsRamping*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetRampPaused(uint32_t /*aVersion*/, bool& /*aretRampPaused*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetRampTime(uint32_t /*aVersion*/, uint32_t& /*aretRampTime*/)
{
    ASSERTS();
}

