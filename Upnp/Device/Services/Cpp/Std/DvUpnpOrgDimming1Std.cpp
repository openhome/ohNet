#include <Std/DvUpnpOrgDimming1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

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
    Functor empty;
    iPropertyLoadLevelStatus = new PropertyUint(new ParameterUint("LoadLevelStatus", 0, 100), empty);
    iService->AddProperty(iPropertyLoadLevelStatus); // passes ownership
    iPropertyStepDelta = new PropertyUint(new ParameterUint("StepDelta", 1, 100), empty);
    iService->AddProperty(iPropertyStepDelta); // passes ownership
    iPropertyRampRate = new PropertyUint(new ParameterUint("RampRate", 0, 100), empty);
    iService->AddProperty(iPropertyRampRate); // passes ownership
    iPropertyIsRamping = new PropertyBool(new ParameterBool("IsRamping"), empty);
    iService->AddProperty(iPropertyIsRamping); // passes ownership
    iPropertyRampPaused = new PropertyBool(new ParameterBool("RampPaused"), empty);
    iService->AddProperty(iPropertyRampPaused); // passes ownership
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("SetLoadLevelTarget");
    action->AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelTarget");
    action->AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetLoadLevelStatus()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelStatus");
    action->AddOutputParameter(new ParameterRelated("retLoadlevelStatus", *iPropertyLoadLevelStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetOnEffectLevel()
{
    Zapp::Action* action = new Zapp::Action("SetOnEffectLevel");
    action->AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetOnEffectLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetOnEffect()
{
    Zapp::Action* action = new Zapp::Action("SetOnEffect");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"OnEffectLevel";
    allowedValues[index++] = (TChar*)"LastSetting";
    allowedValues[index++] = (TChar*)"Default";
    action->AddInputParameter(new ParameterString("newOnEffect", allowedValues, 3));
    delete[] allowedValues;
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetOnEffect);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetOnEffectParameters()
{
    Zapp::Action* action = new Zapp::Action("GetOnEffectParameters");
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetOnEffectParameters);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStepUp()
{
    Zapp::Action* action = new Zapp::Action("StepUp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStepUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStepDown()
{
    Zapp::Action* action = new Zapp::Action("StepDown");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStepDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStartRampUp()
{
    Zapp::Action* action = new Zapp::Action("StartRampUp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStartRampUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStartRampDown()
{
    Zapp::Action* action = new Zapp::Action("StartRampDown");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStartRampDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStopRamp()
{
    Zapp::Action* action = new Zapp::Action("StopRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStopRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionStartRampToLevel()
{
    Zapp::Action* action = new Zapp::Action("StartRampToLevel");
    action->AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
    action->AddInputParameter(new ParameterUint("newRampTime"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoStartRampToLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("SetStepDelta");
    action->AddInputParameter(new ParameterRelated("newStepDelta", *iPropertyStepDelta));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("GetStepDelta");
    action->AddOutputParameter(new ParameterRelated("retStepDelta", *iPropertyStepDelta));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionSetRampRate()
{
    Zapp::Action* action = new Zapp::Action("SetRampRate");
    action->AddInputParameter(new ParameterRelated("newRampRate", *iPropertyRampRate));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoSetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetRampRate()
{
    Zapp::Action* action = new Zapp::Action("GetRampRate");
    action->AddOutputParameter(new ParameterRelated("retRampRate", *iPropertyRampRate));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionPauseRamp()
{
    Zapp::Action* action = new Zapp::Action("PauseRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoPauseRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionResumeRamp()
{
    Zapp::Action* action = new Zapp::Action("ResumeRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoResumeRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetIsRamping()
{
    Zapp::Action* action = new Zapp::Action("GetIsRamping");
    action->AddOutputParameter(new ParameterRelated("retIsRamping", *iPropertyIsRamping));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetIsRamping);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetRampPaused()
{
    Zapp::Action* action = new Zapp::Action("GetRampPaused");
    action->AddOutputParameter(new ParameterRelated("retRampPaused", *iPropertyRampPaused));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetRampPaused);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::EnableActionGetRampTime()
{
    Zapp::Action* action = new Zapp::Action("GetRampTime");
    action->AddOutputParameter(new ParameterUint("retRampTime"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderUpnpOrgDimming1Cpp::DoGetRampTime);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1Cpp::DoSetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    SetLoadLevelTarget(aVersion, newLoadlevelTarget);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respGetLoadlevelTarget;
    GetLoadLevelTarget(aVersion, respGetLoadlevelTarget);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    respWriterGetLoadlevelTarget.Write(respGetLoadlevelTarget);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretLoadlevelStatus;
    GetLoadLevelStatus(aVersion, respretLoadlevelStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    respWriterretLoadlevelStatus.Write(respretLoadlevelStatus);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetOnEffectLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    SetOnEffectLevel(aVersion, newOnEffectLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetOnEffect(IDvInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgDimming1Cpp::DoGetOnEffectParameters(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respretOnEffect;
    uint32_t respretOnEffectLevel;
    GetOnEffectParameters(aVersion, respretOnEffect, respretOnEffectLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterretOnEffect(aInvocation, "retOnEffect");
    Brn buf_retOnEffect((const TByte*)respretOnEffect.c_str(), (TUint)respretOnEffect.length());
    respWriterretOnEffect.Write(buf_retOnEffect);
    aInvocation.InvocationWriteStringEnd("retOnEffect");
    InvocationResponseUint respWriterretOnEffectLevel(aInvocation, "retOnEffectLevel");
    respWriterretOnEffectLevel.Write(respretOnEffectLevel);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStepUp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StepUp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStepDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StepDown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampUp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StartRampUp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StartRampDown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStopRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StopRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampToLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    uint32_t newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    StartRampToLevel(aVersion, newLoadLevelTarget, newRampTime);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetStepDelta(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    SetStepDelta(aVersion, newStepDelta);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetStepDelta(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretStepDelta;
    GetStepDelta(aVersion, respretStepDelta);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterretStepDelta(aInvocation, "retStepDelta");
    respWriterretStepDelta.Write(respretStepDelta);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetRampRate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    SetRampRate(aVersion, newRampRate);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampRate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretRampRate;
    GetRampRate(aVersion, respretRampRate);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterretRampRate(aInvocation, "retRampRate");
    respWriterretRampRate.Write(respretRampRate);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoPauseRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    PauseRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoResumeRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    ResumeRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetIsRamping(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respretIsRamping;
    GetIsRamping(aVersion, respretIsRamping);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterretIsRamping(aInvocation, "retIsRamping");
    respWriterretIsRamping.Write(respretIsRamping);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampPaused(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respretRampPaused;
    GetRampPaused(aVersion, respretRampPaused);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterretRampPaused(aInvocation, "retRampPaused");
    respWriterretRampPaused.Write(respretRampPaused);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampTime(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretRampTime;
    GetRampTime(aVersion, respretRampTime);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterretRampTime(aInvocation, "retRampTime");
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

