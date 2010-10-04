#include <Std/DvUpnpOrgDimming1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgDimming1Cpp::SetPropertyLoadLevelStatus(uint32_t aValue)
{
    SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvServiceUpnpOrgDimming1Cpp::GetPropertyLoadLevelStatus(uint32_t& aValue)
{
    aValue = iPropertyLoadLevelStatus->Value();
}

void DvServiceUpnpOrgDimming1Cpp::SetPropertyStepDelta(uint32_t aValue)
{
    SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvServiceUpnpOrgDimming1Cpp::GetPropertyStepDelta(uint32_t& aValue)
{
    aValue = iPropertyStepDelta->Value();
}

void DvServiceUpnpOrgDimming1Cpp::SetPropertyRampRate(uint32_t aValue)
{
    SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvServiceUpnpOrgDimming1Cpp::GetPropertyRampRate(uint32_t& aValue)
{
    aValue = iPropertyRampRate->Value();
}

void DvServiceUpnpOrgDimming1Cpp::SetPropertyIsRamping(bool aValue)
{
    SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvServiceUpnpOrgDimming1Cpp::GetPropertyIsRamping(bool& aValue)
{
    aValue = iPropertyIsRamping->Value();
}

void DvServiceUpnpOrgDimming1Cpp::SetPropertyRampPaused(bool aValue)
{
    SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvServiceUpnpOrgDimming1Cpp::GetPropertyRampPaused(bool& aValue)
{
    aValue = iPropertyRampPaused->Value();
}

DvServiceUpnpOrgDimming1Cpp::DvServiceUpnpOrgDimming1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "Dimming", 1)
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

void DvServiceUpnpOrgDimming1Cpp::EnableActionSetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("SetLoadLevelTarget");
    action->AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoSetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelTarget");
    action->AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetLoadLevelStatus()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelStatus");
    action->AddOutputParameter(new ParameterRelated("retLoadlevelStatus", *iPropertyLoadLevelStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetLoadLevelStatus);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionSetOnEffectLevel()
{
    Zapp::Action* action = new Zapp::Action("SetOnEffectLevel");
    action->AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoSetOnEffectLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionSetOnEffect()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoSetOnEffect);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetOnEffectParameters()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetOnEffectParameters);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionStepUp()
{
    Zapp::Action* action = new Zapp::Action("StepUp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoStepUp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionStepDown()
{
    Zapp::Action* action = new Zapp::Action("StepDown");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoStepDown);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionStartRampUp()
{
    Zapp::Action* action = new Zapp::Action("StartRampUp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoStartRampUp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionStartRampDown()
{
    Zapp::Action* action = new Zapp::Action("StartRampDown");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoStartRampDown);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionStopRamp()
{
    Zapp::Action* action = new Zapp::Action("StopRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoStopRamp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionStartRampToLevel()
{
    Zapp::Action* action = new Zapp::Action("StartRampToLevel");
    action->AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
    action->AddInputParameter(new ParameterUint("newRampTime", 0, 4294967295));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoStartRampToLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionSetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("SetStepDelta");
    action->AddInputParameter(new ParameterRelated("newStepDelta", *iPropertyStepDelta));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoSetStepDelta);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("GetStepDelta");
    action->AddOutputParameter(new ParameterRelated("retStepDelta", *iPropertyStepDelta));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetStepDelta);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionSetRampRate()
{
    Zapp::Action* action = new Zapp::Action("SetRampRate");
    action->AddInputParameter(new ParameterRelated("newRampRate", *iPropertyRampRate));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoSetRampRate);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetRampRate()
{
    Zapp::Action* action = new Zapp::Action("GetRampRate");
    action->AddOutputParameter(new ParameterRelated("retRampRate", *iPropertyRampRate));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetRampRate);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionPauseRamp()
{
    Zapp::Action* action = new Zapp::Action("PauseRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoPauseRamp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionResumeRamp()
{
    Zapp::Action* action = new Zapp::Action("ResumeRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoResumeRamp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetIsRamping()
{
    Zapp::Action* action = new Zapp::Action("GetIsRamping");
    action->AddOutputParameter(new ParameterRelated("retIsRamping", *iPropertyIsRamping));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetIsRamping);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetRampPaused()
{
    Zapp::Action* action = new Zapp::Action("GetRampPaused");
    action->AddOutputParameter(new ParameterRelated("retRampPaused", *iPropertyRampPaused));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetRampPaused);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::EnableActionGetRampTime()
{
    Zapp::Action* action = new Zapp::Action("GetRampTime");
    action->AddOutputParameter(new ParameterUint("retRampTime", 0, 4294967295));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1Cpp::DoGetRampTime);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1Cpp::DoSetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    SetLoadLevelTarget(aVersion, newLoadlevelTarget);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoGetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoGetLoadLevelStatus(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoSetOnEffectLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    SetOnEffectLevel(aVersion, newOnEffectLevel);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoSetOnEffect(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoGetOnEffectParameters(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respretOnEffect;
    uint32_t respretOnEffectLevel;
    GetOnEffectParameters(aVersion, respretOnEffect, respretOnEffectLevel);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterretOnEffect(aInvocation, "retOnEffect");
    Brn buf_retOnEffect((const TByte*)respretOnEffect.c_str(), respretOnEffect.length());
    respWriterretOnEffect.Write(buf_retOnEffect);
    aInvocation.InvocationWriteStringEnd("retOnEffect");
    InvocationResponseUint respWriterretOnEffectLevel(aInvocation, "retOnEffectLevel");
    respWriterretOnEffectLevel.Write(respretOnEffectLevel);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoStepUp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StepUp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoStepDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StepDown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoStartRampUp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StartRampUp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoStartRampDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StartRampDown(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoStopRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    StopRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoStartRampToLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    uint32_t newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    StartRampToLevel(aVersion, newLoadLevelTarget, newRampTime);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoSetStepDelta(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    SetStepDelta(aVersion, newStepDelta);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoGetStepDelta(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoSetRampRate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    SetRampRate(aVersion, newRampRate);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoGetRampRate(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoPauseRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    PauseRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoResumeRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    ResumeRamp(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgDimming1Cpp::DoGetIsRamping(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoGetRampPaused(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::DoGetRampTime(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgDimming1Cpp::SetLoadLevelTarget(uint32_t /*aVersion*/, uint32_t /*anewLoadlevelTarget*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetLoadLevelTarget(uint32_t /*aVersion*/, uint32_t& /*aGetLoadlevelTarget*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetLoadLevelStatus(uint32_t /*aVersion*/, uint32_t& /*aretLoadlevelStatus*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::SetOnEffectLevel(uint32_t /*aVersion*/, uint32_t /*anewOnEffectLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::SetOnEffect(uint32_t /*aVersion*/, const std::string& /*anewOnEffect*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetOnEffectParameters(uint32_t /*aVersion*/, std::string& /*aretOnEffect*/, uint32_t& /*aretOnEffectLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::StepUp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::StepDown(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::StartRampUp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::StartRampDown(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::StopRamp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::StartRampToLevel(uint32_t /*aVersion*/, uint32_t /*anewLoadLevelTarget*/, uint32_t /*anewRampTime*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::SetStepDelta(uint32_t /*aVersion*/, uint32_t /*anewStepDelta*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetStepDelta(uint32_t /*aVersion*/, uint32_t& /*aretStepDelta*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::SetRampRate(uint32_t /*aVersion*/, uint32_t /*anewRampRate*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetRampRate(uint32_t /*aVersion*/, uint32_t& /*aretRampRate*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::PauseRamp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::ResumeRamp(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetIsRamping(uint32_t /*aVersion*/, bool& /*aretIsRamping*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetRampPaused(uint32_t /*aVersion*/, bool& /*aretRampPaused*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1Cpp::GetRampTime(uint32_t /*aVersion*/, uint32_t& /*aretRampTime*/)
{
    ASSERTS();
}

