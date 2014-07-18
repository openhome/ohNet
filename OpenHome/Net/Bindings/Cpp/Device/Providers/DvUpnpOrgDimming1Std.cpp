#include "DvUpnpOrgDimming1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyLoadLevelStatus(uint32_t aValue)
{
    ASSERT(iPropertyLoadLevelStatus != NULL);
    return SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyLoadLevelStatus(uint32_t& aValue)
{
    ASSERT(iPropertyLoadLevelStatus != NULL);
    aValue = iPropertyLoadLevelStatus->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyStepDelta(uint32_t aValue)
{
    ASSERT(iPropertyStepDelta != NULL);
    return SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyStepDelta(uint32_t& aValue)
{
    ASSERT(iPropertyStepDelta != NULL);
    aValue = iPropertyStepDelta->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyRampRate(uint32_t aValue)
{
    ASSERT(iPropertyRampRate != NULL);
    return SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyRampRate(uint32_t& aValue)
{
    ASSERT(iPropertyRampRate != NULL);
    aValue = iPropertyRampRate->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyIsRamping(bool aValue)
{
    ASSERT(iPropertyIsRamping != NULL);
    return SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyIsRamping(bool& aValue)
{
    ASSERT(iPropertyIsRamping != NULL);
    aValue = iPropertyIsRamping->Value();
}

bool DvProviderUpnpOrgDimming1Cpp::SetPropertyRampPaused(bool aValue)
{
    ASSERT(iPropertyRampPaused != NULL);
    return SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvProviderUpnpOrgDimming1Cpp::GetPropertyRampPaused(bool& aValue)
{
    ASSERT(iPropertyRampPaused != NULL);
    aValue = iPropertyRampPaused->Value();
}

DvProviderUpnpOrgDimming1Cpp::DvProviderUpnpOrgDimming1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "Dimming", 1)
{
    iPropertyLoadLevelStatus = NULL;
    iPropertyStepDelta = NULL;
    iPropertyRampRate = NULL;
    iPropertyIsRamping = NULL;
    iPropertyRampPaused = NULL;
}

void DvProviderUpnpOrgDimming1Cpp::EnablePropertyLoadLevelStatus()
{
    iPropertyLoadLevelStatus = new PropertyUint(iDvStack.Env(), new ParameterUint("LoadLevelStatus", 0, 100));
    iService->AddProperty(iPropertyLoadLevelStatus); // passes ownership
}

void DvProviderUpnpOrgDimming1Cpp::EnablePropertyStepDelta()
{
    iPropertyStepDelta = new PropertyUint(iDvStack.Env(), new ParameterUint("StepDelta", 1, 100));
    iService->AddProperty(iPropertyStepDelta); // passes ownership
}

void DvProviderUpnpOrgDimming1Cpp::EnablePropertyRampRate()
{
    iPropertyRampRate = new PropertyUint(iDvStack.Env(), new ParameterUint("RampRate", 0, 100));
    iService->AddProperty(iPropertyRampRate); // passes ownership
}

void DvProviderUpnpOrgDimming1Cpp::EnablePropertyIsRamping()
{
    iPropertyIsRamping = new PropertyBool(iDvStack.Env(), new ParameterBool("IsRamping"));
    iService->AddProperty(iPropertyIsRamping); // passes ownership
}

void DvProviderUpnpOrgDimming1Cpp::EnablePropertyRampPaused()
{
    iPropertyRampPaused = new PropertyBool(iDvStack.Env(), new ParameterBool("RampPaused"));
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

void DvProviderUpnpOrgDimming1Cpp::DoSetLoadLevelTarget(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetLoadLevelTarget(invocation, newLoadlevelTarget);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelTarget(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respGetLoadlevelTarget;
    DvInvocationStd invocation(aInvocation);
    GetLoadLevelTarget(invocation, respGetLoadlevelTarget);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    respWriterGetLoadlevelTarget.Write(respGetLoadlevelTarget);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetLoadLevelStatus(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretLoadlevelStatus;
    DvInvocationStd invocation(aInvocation);
    GetLoadLevelStatus(invocation, respretLoadlevelStatus);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    respWriterretLoadlevelStatus.Write(respretLoadlevelStatus);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetOnEffectLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetOnEffectLevel(invocation, newOnEffectLevel);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetOnEffect(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_newOnEffect;
    aInvocation.InvocationReadString("newOnEffect", buf_newOnEffect);
    std::string newOnEffect((const char*)buf_newOnEffect.Ptr(), buf_newOnEffect.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetOnEffect(invocation, newOnEffect);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetOnEffectParameters(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respretOnEffect;
    uint32_t respretOnEffectLevel;
    DvInvocationStd invocation(aInvocation);
    GetOnEffectParameters(invocation, respretOnEffect, respretOnEffectLevel);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterretOnEffect(aInvocation, "retOnEffect");
    Brn buf_retOnEffect((const TByte*)respretOnEffect.c_str(), (TUint)respretOnEffect.length());
    respWriterretOnEffect.Write(buf_retOnEffect);
    aInvocation.InvocationWriteStringEnd("retOnEffect");
    DviInvocationResponseUint respWriterretOnEffectLevel(aInvocation, "retOnEffectLevel");
    respWriterretOnEffectLevel.Write(respretOnEffectLevel);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStepUp(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StepUp(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStepDown(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StepDown(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampUp(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StartRampUp(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampDown(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StartRampDown(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStopRamp(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StopRamp(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoStartRampToLevel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    uint32_t newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StartRampToLevel(invocation, newLoadLevelTarget, newRampTime);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetStepDelta(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetStepDelta(invocation, newStepDelta);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetStepDelta(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretStepDelta;
    DvInvocationStd invocation(aInvocation);
    GetStepDelta(invocation, respretStepDelta);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretStepDelta(aInvocation, "retStepDelta");
    respWriterretStepDelta.Write(respretStepDelta);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoSetRampRate(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetRampRate(invocation, newRampRate);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampRate(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretRampRate;
    DvInvocationStd invocation(aInvocation);
    GetRampRate(invocation, respretRampRate);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretRampRate(aInvocation, "retRampRate");
    respWriterretRampRate.Write(respretRampRate);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoPauseRamp(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    PauseRamp(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoResumeRamp(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    ResumeRamp(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetIsRamping(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respretIsRamping;
    DvInvocationStd invocation(aInvocation);
    GetIsRamping(invocation, respretIsRamping);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterretIsRamping(aInvocation, "retIsRamping");
    respWriterretIsRamping.Write(respretIsRamping);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampPaused(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respretRampPaused;
    DvInvocationStd invocation(aInvocation);
    GetRampPaused(invocation, respretRampPaused);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterretRampPaused(aInvocation, "retRampPaused");
    respWriterretRampPaused.Write(respretRampPaused);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::DoGetRampTime(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respretRampTime;
    DvInvocationStd invocation(aInvocation);
    GetRampTime(invocation, respretRampTime);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterretRampTime(aInvocation, "retRampTime");
    respWriterretRampTime.Write(respretRampTime);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgDimming1Cpp::SetLoadLevelTarget(IDvInvocationStd& /*aInvocation*/, uint32_t /*anewLoadlevelTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetLoadLevelTarget(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aGetLoadlevelTarget*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetLoadLevelStatus(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aretLoadlevelStatus*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetOnEffectLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*anewOnEffectLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetOnEffect(IDvInvocationStd& /*aInvocation*/, const std::string& /*anewOnEffect*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetOnEffectParameters(IDvInvocationStd& /*aInvocation*/, std::string& /*aretOnEffect*/, uint32_t& /*aretOnEffectLevel*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StepUp(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StepDown(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StartRampUp(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StartRampDown(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StopRamp(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::StartRampToLevel(IDvInvocationStd& /*aInvocation*/, uint32_t /*anewLoadLevelTarget*/, uint32_t /*anewRampTime*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetStepDelta(IDvInvocationStd& /*aInvocation*/, uint32_t /*anewStepDelta*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetStepDelta(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aretStepDelta*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::SetRampRate(IDvInvocationStd& /*aInvocation*/, uint32_t /*anewRampRate*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetRampRate(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aretRampRate*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::PauseRamp(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::ResumeRamp(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetIsRamping(IDvInvocationStd& /*aInvocation*/, bool& /*aretIsRamping*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetRampPaused(IDvInvocationStd& /*aInvocation*/, bool& /*aretRampPaused*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgDimming1Cpp::GetRampTime(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aretRampTime*/)
{
    ASSERTS();
}

