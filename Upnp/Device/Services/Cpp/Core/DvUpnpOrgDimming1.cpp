#include <Core/DvUpnpOrgDimming1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgDimming1::SetPropertyLoadLevelStatus(TUint aValue)
{
    SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvServiceUpnpOrgDimming1::GetPropertyLoadLevelStatus(TUint& aValue)
{
    aValue = iPropertyLoadLevelStatus->Value();
}

void DvServiceUpnpOrgDimming1::SetPropertyStepDelta(TUint aValue)
{
    SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvServiceUpnpOrgDimming1::GetPropertyStepDelta(TUint& aValue)
{
    aValue = iPropertyStepDelta->Value();
}

void DvServiceUpnpOrgDimming1::SetPropertyRampRate(TUint aValue)
{
    SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvServiceUpnpOrgDimming1::GetPropertyRampRate(TUint& aValue)
{
    aValue = iPropertyRampRate->Value();
}

void DvServiceUpnpOrgDimming1::SetPropertyIsRamping(TBool aValue)
{
    SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvServiceUpnpOrgDimming1::GetPropertyIsRamping(TBool& aValue)
{
    aValue = iPropertyIsRamping->Value();
}

void DvServiceUpnpOrgDimming1::SetPropertyRampPaused(TBool aValue)
{
    SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvServiceUpnpOrgDimming1::GetPropertyRampPaused(TBool& aValue)
{
    aValue = iPropertyRampPaused->Value();
}

DvServiceUpnpOrgDimming1::DvServiceUpnpOrgDimming1(DvDevice& aDevice)
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

void DvServiceUpnpOrgDimming1::EnableActionSetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("SetLoadLevelTarget");
    action->AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoSetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelTarget");
    action->AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetLoadLevelStatus()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelStatus");
    action->AddOutputParameter(new ParameterRelated("retLoadlevelStatus", *iPropertyLoadLevelStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetLoadLevelStatus);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionSetOnEffectLevel()
{
    Zapp::Action* action = new Zapp::Action("SetOnEffectLevel");
    action->AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoSetOnEffectLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionSetOnEffect()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoSetOnEffect);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetOnEffectParameters()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetOnEffectParameters);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionStepUp()
{
    Zapp::Action* action = new Zapp::Action("StepUp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoStepUp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionStepDown()
{
    Zapp::Action* action = new Zapp::Action("StepDown");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoStepDown);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionStartRampUp()
{
    Zapp::Action* action = new Zapp::Action("StartRampUp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoStartRampUp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionStartRampDown()
{
    Zapp::Action* action = new Zapp::Action("StartRampDown");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoStartRampDown);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionStopRamp()
{
    Zapp::Action* action = new Zapp::Action("StopRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoStopRamp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionStartRampToLevel()
{
    Zapp::Action* action = new Zapp::Action("StartRampToLevel");
    action->AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
    action->AddInputParameter(new ParameterUint("newRampTime", 0, 4294967295));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoStartRampToLevel);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionSetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("SetStepDelta");
    action->AddInputParameter(new ParameterRelated("newStepDelta", *iPropertyStepDelta));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoSetStepDelta);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("GetStepDelta");
    action->AddOutputParameter(new ParameterRelated("retStepDelta", *iPropertyStepDelta));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetStepDelta);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionSetRampRate()
{
    Zapp::Action* action = new Zapp::Action("SetRampRate");
    action->AddInputParameter(new ParameterRelated("newRampRate", *iPropertyRampRate));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoSetRampRate);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetRampRate()
{
    Zapp::Action* action = new Zapp::Action("GetRampRate");
    action->AddOutputParameter(new ParameterRelated("retRampRate", *iPropertyRampRate));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetRampRate);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionPauseRamp()
{
    Zapp::Action* action = new Zapp::Action("PauseRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoPauseRamp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionResumeRamp()
{
    Zapp::Action* action = new Zapp::Action("ResumeRamp");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoResumeRamp);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetIsRamping()
{
    Zapp::Action* action = new Zapp::Action("GetIsRamping");
    action->AddOutputParameter(new ParameterRelated("retIsRamping", *iPropertyIsRamping));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetIsRamping);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetRampPaused()
{
    Zapp::Action* action = new Zapp::Action("GetRampPaused");
    action->AddOutputParameter(new ParameterRelated("retRampPaused", *iPropertyRampPaused));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetRampPaused);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::EnableActionGetRampTime()
{
    Zapp::Action* action = new Zapp::Action("GetRampTime");
    action->AddOutputParameter(new ParameterUint("retRampTime", 0, 4294967295));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgDimming1::DoGetRampTime);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgDimming1::DoSetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetLoadLevelTarget(resp, aVersion, newLoadlevelTarget);
}

void DvServiceUpnpOrgDimming1::DoGetLoadLevelTarget(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    GetLoadLevelTarget(resp, aVersion, respGetLoadlevelTarget);
}

void DvServiceUpnpOrgDimming1::DoGetLoadLevelStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    GetLoadLevelStatus(resp, aVersion, respretLoadlevelStatus);
}

void DvServiceUpnpOrgDimming1::DoSetOnEffectLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetOnEffectLevel(resp, aVersion, newOnEffectLevel);
}

void DvServiceUpnpOrgDimming1::DoSetOnEffect(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz newOnEffect;
    aInvocation.InvocationReadString("newOnEffect", newOnEffect);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetOnEffect(resp, aVersion, newOnEffect);
}

void DvServiceUpnpOrgDimming1::DoGetOnEffectParameters(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respretOnEffect(aInvocation, "retOnEffect");
    InvocationResponseUint respretOnEffectLevel(aInvocation, "retOnEffectLevel");
    GetOnEffectParameters(resp, aVersion, respretOnEffect, respretOnEffectLevel);
}

void DvServiceUpnpOrgDimming1::DoStepUp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StepUp(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoStepDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StepDown(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoStartRampUp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StartRampUp(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoStartRampDown(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StartRampDown(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoStopRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StopRamp(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoStartRampToLevel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    TUint newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StartRampToLevel(resp, aVersion, newLoadLevelTarget, newRampTime);
}

void DvServiceUpnpOrgDimming1::DoSetStepDelta(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStepDelta(resp, aVersion, newStepDelta);
}

void DvServiceUpnpOrgDimming1::DoGetStepDelta(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretStepDelta(aInvocation, "retStepDelta");
    GetStepDelta(resp, aVersion, respretStepDelta);
}

void DvServiceUpnpOrgDimming1::DoSetRampRate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRampRate(resp, aVersion, newRampRate);
}

void DvServiceUpnpOrgDimming1::DoGetRampRate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretRampRate(aInvocation, "retRampRate");
    GetRampRate(resp, aVersion, respretRampRate);
}

void DvServiceUpnpOrgDimming1::DoPauseRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    PauseRamp(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoResumeRamp(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ResumeRamp(resp, aVersion);
}

void DvServiceUpnpOrgDimming1::DoGetIsRamping(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respretIsRamping(aInvocation, "retIsRamping");
    GetIsRamping(resp, aVersion, respretIsRamping);
}

void DvServiceUpnpOrgDimming1::DoGetRampPaused(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respretRampPaused(aInvocation, "retRampPaused");
    GetRampPaused(resp, aVersion, respretRampPaused);
}

void DvServiceUpnpOrgDimming1::DoGetRampTime(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretRampTime(aInvocation, "retRampTime");
    GetRampTime(resp, aVersion, respretRampTime);
}

void DvServiceUpnpOrgDimming1::SetLoadLevelTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewLoadlevelTarget*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetLoadLevelTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aGetLoadlevelTarget*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetLoadLevelStatus(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretLoadlevelStatus*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::SetOnEffectLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewOnEffectLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::SetOnEffect(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*anewOnEffect*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetOnEffectParameters(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aretOnEffect*/, IInvocationResponseUint& /*aretOnEffectLevel*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::StepUp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::StepDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::StartRampUp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::StartRampDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::StopRamp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::StartRampToLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewLoadLevelTarget*/, TUint /*anewRampTime*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::SetStepDelta(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewStepDelta*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetStepDelta(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretStepDelta*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::SetRampRate(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewRampRate*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetRampRate(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretRampRate*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::PauseRamp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::ResumeRamp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetIsRamping(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aretIsRamping*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetRampPaused(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aretRampPaused*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgDimming1::GetRampTime(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretRampTime*/)
{
    ASSERTS();
}

