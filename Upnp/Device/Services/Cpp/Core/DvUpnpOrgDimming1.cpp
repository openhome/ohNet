#include <Core/DvUpnpOrgDimming1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderUpnpOrgDimming1::SetPropertyLoadLevelStatus(TUint aValue)
{
    return SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvProviderUpnpOrgDimming1::GetPropertyLoadLevelStatus(TUint& aValue)
{
    aValue = iPropertyLoadLevelStatus->Value();
}

TBool DvProviderUpnpOrgDimming1::SetPropertyStepDelta(TUint aValue)
{
    return SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvProviderUpnpOrgDimming1::GetPropertyStepDelta(TUint& aValue)
{
    aValue = iPropertyStepDelta->Value();
}

TBool DvProviderUpnpOrgDimming1::SetPropertyRampRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvProviderUpnpOrgDimming1::GetPropertyRampRate(TUint& aValue)
{
    aValue = iPropertyRampRate->Value();
}

TBool DvProviderUpnpOrgDimming1::SetPropertyIsRamping(TBool aValue)
{
    return SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvProviderUpnpOrgDimming1::GetPropertyIsRamping(TBool& aValue)
{
    aValue = iPropertyIsRamping->Value();
}

TBool DvProviderUpnpOrgDimming1::SetPropertyRampPaused(TBool aValue)
{
    return SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvProviderUpnpOrgDimming1::GetPropertyRampPaused(TBool& aValue)
{
    aValue = iPropertyRampPaused->Value();
}

DvProviderUpnpOrgDimming1::DvProviderUpnpOrgDimming1(DvDevice& aDevice)
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

void DvProviderUpnpOrgDimming1::EnableActionSetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("SetLoadLevelTarget");
    action->AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoSetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetLoadLevelTarget()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelTarget");
    action->AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetLoadLevelStatus()
{
    Zapp::Action* action = new Zapp::Action("GetLoadLevelStatus");
    action->AddOutputParameter(new ParameterRelated("retLoadlevelStatus", *iPropertyLoadLevelStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetLoadLevelStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionSetOnEffectLevel()
{
    Zapp::Action* action = new Zapp::Action("SetOnEffectLevel");
    action->AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoSetOnEffectLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionSetOnEffect()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoSetOnEffect);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetOnEffectParameters()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetOnEffectParameters);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionStepUp()
{
    Zapp::Action* action = new Zapp::Action("StepUp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoStepUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionStepDown()
{
    Zapp::Action* action = new Zapp::Action("StepDown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoStepDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionStartRampUp()
{
    Zapp::Action* action = new Zapp::Action("StartRampUp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoStartRampUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionStartRampDown()
{
    Zapp::Action* action = new Zapp::Action("StartRampDown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoStartRampDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionStopRamp()
{
    Zapp::Action* action = new Zapp::Action("StopRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoStopRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionStartRampToLevel()
{
    Zapp::Action* action = new Zapp::Action("StartRampToLevel");
    action->AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
    action->AddInputParameter(new ParameterUint("newRampTime"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoStartRampToLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionSetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("SetStepDelta");
    action->AddInputParameter(new ParameterRelated("newStepDelta", *iPropertyStepDelta));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoSetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetStepDelta()
{
    Zapp::Action* action = new Zapp::Action("GetStepDelta");
    action->AddOutputParameter(new ParameterRelated("retStepDelta", *iPropertyStepDelta));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionSetRampRate()
{
    Zapp::Action* action = new Zapp::Action("SetRampRate");
    action->AddInputParameter(new ParameterRelated("newRampRate", *iPropertyRampRate));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoSetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetRampRate()
{
    Zapp::Action* action = new Zapp::Action("GetRampRate");
    action->AddOutputParameter(new ParameterRelated("retRampRate", *iPropertyRampRate));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionPauseRamp()
{
    Zapp::Action* action = new Zapp::Action("PauseRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoPauseRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionResumeRamp()
{
    Zapp::Action* action = new Zapp::Action("ResumeRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoResumeRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetIsRamping()
{
    Zapp::Action* action = new Zapp::Action("GetIsRamping");
    action->AddOutputParameter(new ParameterRelated("retIsRamping", *iPropertyIsRamping));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetIsRamping);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetRampPaused()
{
    Zapp::Action* action = new Zapp::Action("GetRampPaused");
    action->AddOutputParameter(new ParameterRelated("retRampPaused", *iPropertyRampPaused));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetRampPaused);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::EnableActionGetRampTime()
{
    Zapp::Action* action = new Zapp::Action("GetRampTime");
    action->AddOutputParameter(new ParameterUint("retRampTime"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1::DoGetRampTime);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1::DoSetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetLoadLevelTarget(resp, aVersion, newLoadlevelTarget);
}

void DvProviderUpnpOrgDimming1::DoGetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    GetLoadLevelTarget(resp, aVersion, respGetLoadlevelTarget);
}

void DvProviderUpnpOrgDimming1::DoGetLoadLevelStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    GetLoadLevelStatus(resp, aVersion, respretLoadlevelStatus);
}

void DvProviderUpnpOrgDimming1::DoSetOnEffectLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetOnEffectLevel(resp, aVersion, newOnEffectLevel);
}

void DvProviderUpnpOrgDimming1::DoSetOnEffect(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz newOnEffect;
    aInvocation.InvocationReadString("newOnEffect", newOnEffect);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetOnEffect(resp, aVersion, newOnEffect);
}

void DvProviderUpnpOrgDimming1::DoGetOnEffectParameters(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respretOnEffect(aInvocation, "retOnEffect");
    InvocationResponseUint respretOnEffectLevel(aInvocation, "retOnEffectLevel");
    GetOnEffectParameters(resp, aVersion, respretOnEffect, respretOnEffectLevel);
}

void DvProviderUpnpOrgDimming1::DoStepUp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StepUp(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoStepDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StepDown(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoStartRampUp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StartRampUp(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoStartRampDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StartRampDown(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoStopRamp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StopRamp(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoStartRampToLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    TUint newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StartRampToLevel(resp, aVersion, newLoadLevelTarget, newRampTime);
}

void DvProviderUpnpOrgDimming1::DoSetStepDelta(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStepDelta(resp, aVersion, newStepDelta);
}

void DvProviderUpnpOrgDimming1::DoGetStepDelta(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretStepDelta(aInvocation, "retStepDelta");
    GetStepDelta(resp, aVersion, respretStepDelta);
}

void DvProviderUpnpOrgDimming1::DoSetRampRate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRampRate(resp, aVersion, newRampRate);
}

void DvProviderUpnpOrgDimming1::DoGetRampRate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretRampRate(aInvocation, "retRampRate");
    GetRampRate(resp, aVersion, respretRampRate);
}

void DvProviderUpnpOrgDimming1::DoPauseRamp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    PauseRamp(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoResumeRamp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ResumeRamp(resp, aVersion);
}

void DvProviderUpnpOrgDimming1::DoGetIsRamping(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respretIsRamping(aInvocation, "retIsRamping");
    GetIsRamping(resp, aVersion, respretIsRamping);
}

void DvProviderUpnpOrgDimming1::DoGetRampPaused(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respretRampPaused(aInvocation, "retRampPaused");
    GetRampPaused(resp, aVersion, respretRampPaused);
}

void DvProviderUpnpOrgDimming1::DoGetRampTime(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respretRampTime(aInvocation, "retRampTime");
    GetRampTime(resp, aVersion, respretRampTime);
}

void DvProviderUpnpOrgDimming1::SetLoadLevelTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewLoadlevelTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetLoadLevelTarget(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aGetLoadlevelTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetLoadLevelStatus(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretLoadlevelStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::SetOnEffectLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewOnEffectLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::SetOnEffect(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*anewOnEffect*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetOnEffectParameters(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aretOnEffect*/, IInvocationResponseUint& /*aretOnEffectLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::StepUp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::StepDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::StartRampUp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::StartRampDown(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::StopRamp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::StartRampToLevel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewLoadLevelTarget*/, TUint /*anewRampTime*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::SetStepDelta(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewStepDelta*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetStepDelta(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretStepDelta*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::SetRampRate(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*anewRampRate*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetRampRate(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretRampRate*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::PauseRamp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::ResumeRamp(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetIsRamping(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aretIsRamping*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetRampPaused(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aretRampPaused*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1::GetRampTime(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aretRampTime*/)
{
    ASSERTS();
}

