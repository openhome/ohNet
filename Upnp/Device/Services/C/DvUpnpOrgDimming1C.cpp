#include "DvUpnpOrgDimming1.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

class DvProviderUpnpOrgDimming1C : public DvProvider
{
public:
    DvProviderUpnpOrgDimming1C(DvDeviceC aDevice);
    TBool SetPropertyLoadLevelStatus(TUint aValue);
    void GetPropertyLoadLevelStatus(TUint& aValue);
    TBool SetPropertyStepDelta(TUint aValue);
    void GetPropertyStepDelta(TUint& aValue);
    TBool SetPropertyRampRate(TUint aValue);
    void GetPropertyRampRate(TUint& aValue);
    TBool SetPropertyIsRamping(TBool aValue);
    void GetPropertyIsRamping(TBool& aValue);
    TBool SetPropertyRampPaused(TBool aValue);
    void GetPropertyRampPaused(TBool& aValue);
    void EnableActionSetLoadLevelTarget(CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr);
    void EnableActionGetLoadLevelTarget(CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr);
    void EnableActionGetLoadLevelStatus(CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr);
    void EnableActionSetOnEffectLevel(CallbackDimming1SetOnEffectLevel aCallback, void* aPtr);
    void EnableActionSetOnEffect(CallbackDimming1SetOnEffect aCallback, void* aPtr);
    void EnableActionGetOnEffectParameters(CallbackDimming1GetOnEffectParameters aCallback, void* aPtr);
    void EnableActionStepUp(CallbackDimming1StepUp aCallback, void* aPtr);
    void EnableActionStepDown(CallbackDimming1StepDown aCallback, void* aPtr);
    void EnableActionStartRampUp(CallbackDimming1StartRampUp aCallback, void* aPtr);
    void EnableActionStartRampDown(CallbackDimming1StartRampDown aCallback, void* aPtr);
    void EnableActionStopRamp(CallbackDimming1StopRamp aCallback, void* aPtr);
    void EnableActionStartRampToLevel(CallbackDimming1StartRampToLevel aCallback, void* aPtr);
    void EnableActionSetStepDelta(CallbackDimming1SetStepDelta aCallback, void* aPtr);
    void EnableActionGetStepDelta(CallbackDimming1GetStepDelta aCallback, void* aPtr);
    void EnableActionSetRampRate(CallbackDimming1SetRampRate aCallback, void* aPtr);
    void EnableActionGetRampRate(CallbackDimming1GetRampRate aCallback, void* aPtr);
    void EnableActionPauseRamp(CallbackDimming1PauseRamp aCallback, void* aPtr);
    void EnableActionResumeRamp(CallbackDimming1ResumeRamp aCallback, void* aPtr);
    void EnableActionGetIsRamping(CallbackDimming1GetIsRamping aCallback, void* aPtr);
    void EnableActionGetRampPaused(CallbackDimming1GetRampPaused aCallback, void* aPtr);
    void EnableActionGetRampTime(CallbackDimming1GetRampTime aCallback, void* aPtr);
private:
    void DoSetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLoadLevelStatus(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetOnEffectLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetOnEffect(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetOnEffectParameters(IDviInvocation& aInvocation, TUint aVersion);
    void DoStepUp(IDviInvocation& aInvocation, TUint aVersion);
    void DoStepDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartRampUp(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartRampDown(IDviInvocation& aInvocation, TUint aVersion);
    void DoStopRamp(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartRampToLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStepDelta(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStepDelta(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRampRate(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRampRate(IDviInvocation& aInvocation, TUint aVersion);
    void DoPauseRamp(IDviInvocation& aInvocation, TUint aVersion);
    void DoResumeRamp(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetIsRamping(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRampPaused(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRampTime(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackDimming1SetLoadLevelTarget iCallbackSetLoadLevelTarget;
    void* iPtrSetLoadLevelTarget;
    CallbackDimming1GetLoadLevelTarget iCallbackGetLoadLevelTarget;
    void* iPtrGetLoadLevelTarget;
    CallbackDimming1GetLoadLevelStatus iCallbackGetLoadLevelStatus;
    void* iPtrGetLoadLevelStatus;
    CallbackDimming1SetOnEffectLevel iCallbackSetOnEffectLevel;
    void* iPtrSetOnEffectLevel;
    CallbackDimming1SetOnEffect iCallbackSetOnEffect;
    void* iPtrSetOnEffect;
    CallbackDimming1GetOnEffectParameters iCallbackGetOnEffectParameters;
    void* iPtrGetOnEffectParameters;
    CallbackDimming1StepUp iCallbackStepUp;
    void* iPtrStepUp;
    CallbackDimming1StepDown iCallbackStepDown;
    void* iPtrStepDown;
    CallbackDimming1StartRampUp iCallbackStartRampUp;
    void* iPtrStartRampUp;
    CallbackDimming1StartRampDown iCallbackStartRampDown;
    void* iPtrStartRampDown;
    CallbackDimming1StopRamp iCallbackStopRamp;
    void* iPtrStopRamp;
    CallbackDimming1StartRampToLevel iCallbackStartRampToLevel;
    void* iPtrStartRampToLevel;
    CallbackDimming1SetStepDelta iCallbackSetStepDelta;
    void* iPtrSetStepDelta;
    CallbackDimming1GetStepDelta iCallbackGetStepDelta;
    void* iPtrGetStepDelta;
    CallbackDimming1SetRampRate iCallbackSetRampRate;
    void* iPtrSetRampRate;
    CallbackDimming1GetRampRate iCallbackGetRampRate;
    void* iPtrGetRampRate;
    CallbackDimming1PauseRamp iCallbackPauseRamp;
    void* iPtrPauseRamp;
    CallbackDimming1ResumeRamp iCallbackResumeRamp;
    void* iPtrResumeRamp;
    CallbackDimming1GetIsRamping iCallbackGetIsRamping;
    void* iPtrGetIsRamping;
    CallbackDimming1GetRampPaused iCallbackGetRampPaused;
    void* iPtrGetRampPaused;
    CallbackDimming1GetRampTime iCallbackGetRampTime;
    void* iPtrGetRampTime;
    PropertyUint* iPropertyLoadLevelStatus;
    PropertyUint* iPropertyStepDelta;
    PropertyUint* iPropertyRampRate;
    PropertyBool* iPropertyIsRamping;
    PropertyBool* iPropertyRampPaused;
};

DvProviderUpnpOrgDimming1C::DvProviderUpnpOrgDimming1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "Dimming", 1)
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

TBool DvProviderUpnpOrgDimming1C::SetPropertyLoadLevelStatus(TUint aValue)
{
    return SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyLoadLevelStatus(TUint& aValue)
{
    aValue = iPropertyLoadLevelStatus->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyStepDelta(TUint aValue)
{
    return SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyStepDelta(TUint& aValue)
{
    aValue = iPropertyStepDelta->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyRampRate(TUint aValue)
{
    return SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyRampRate(TUint& aValue)
{
    aValue = iPropertyRampRate->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyIsRamping(TBool aValue)
{
    return SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyIsRamping(TBool& aValue)
{
    aValue = iPropertyIsRamping->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyRampPaused(TBool aValue)
{
    return SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyRampPaused(TBool& aValue)
{
    aValue = iPropertyRampPaused->Value();
}

void DvProviderUpnpOrgDimming1C::EnableActionSetLoadLevelTarget(CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    iCallbackSetLoadLevelTarget = aCallback;
    iPtrSetLoadLevelTarget = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetLoadLevelTarget");
    action->AddInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoSetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetLoadLevelTarget(CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    iCallbackGetLoadLevelTarget = aCallback;
    iPtrGetLoadLevelTarget = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoadLevelTarget");
    action->AddOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetLoadLevelTarget);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetLoadLevelStatus(CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    iCallbackGetLoadLevelStatus = aCallback;
    iPtrGetLoadLevelStatus = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetLoadLevelStatus");
    action->AddOutputParameter(new ParameterRelated("retLoadlevelStatus", *iPropertyLoadLevelStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetLoadLevelStatus);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionSetOnEffectLevel(CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    iCallbackSetOnEffectLevel = aCallback;
    iPtrSetOnEffectLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetOnEffectLevel");
    action->AddInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoSetOnEffectLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionSetOnEffect(CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    iCallbackSetOnEffect = aCallback;
    iPtrSetOnEffect = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoSetOnEffect);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetOnEffectParameters(CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    iCallbackGetOnEffectParameters = aCallback;
    iPtrGetOnEffectParameters = aPtr;
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetOnEffectParameters);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionStepUp(CallbackDimming1StepUp aCallback, void* aPtr)
{
    iCallbackStepUp = aCallback;
    iPtrStepUp = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StepUp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoStepUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionStepDown(CallbackDimming1StepDown aCallback, void* aPtr)
{
    iCallbackStepDown = aCallback;
    iPtrStepDown = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StepDown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoStepDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionStartRampUp(CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    iCallbackStartRampUp = aCallback;
    iPtrStartRampUp = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StartRampUp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoStartRampUp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionStartRampDown(CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    iCallbackStartRampDown = aCallback;
    iPtrStartRampDown = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StartRampDown");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoStartRampDown);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionStopRamp(CallbackDimming1StopRamp aCallback, void* aPtr)
{
    iCallbackStopRamp = aCallback;
    iPtrStopRamp = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoStopRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionStartRampToLevel(CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    iCallbackStartRampToLevel = aCallback;
    iPtrStartRampToLevel = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StartRampToLevel");
    action->AddInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
    action->AddInputParameter(new ParameterUint("newRampTime"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoStartRampToLevel);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionSetStepDelta(CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    iCallbackSetStepDelta = aCallback;
    iPtrSetStepDelta = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetStepDelta");
    action->AddInputParameter(new ParameterRelated("newStepDelta", *iPropertyStepDelta));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoSetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetStepDelta(CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    iCallbackGetStepDelta = aCallback;
    iPtrGetStepDelta = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStepDelta");
    action->AddOutputParameter(new ParameterRelated("retStepDelta", *iPropertyStepDelta));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetStepDelta);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionSetRampRate(CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    iCallbackSetRampRate = aCallback;
    iPtrSetRampRate = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRampRate");
    action->AddInputParameter(new ParameterRelated("newRampRate", *iPropertyRampRate));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoSetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetRampRate(CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    iCallbackGetRampRate = aCallback;
    iPtrGetRampRate = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRampRate");
    action->AddOutputParameter(new ParameterRelated("retRampRate", *iPropertyRampRate));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetRampRate);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionPauseRamp(CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    iCallbackPauseRamp = aCallback;
    iPtrPauseRamp = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PauseRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoPauseRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionResumeRamp(CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    iCallbackResumeRamp = aCallback;
    iPtrResumeRamp = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResumeRamp");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoResumeRamp);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetIsRamping(CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    iCallbackGetIsRamping = aCallback;
    iPtrGetIsRamping = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetIsRamping");
    action->AddOutputParameter(new ParameterRelated("retIsRamping", *iPropertyIsRamping));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetIsRamping);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetRampPaused(CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    iCallbackGetRampPaused = aCallback;
    iPtrGetRampPaused = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRampPaused");
    action->AddOutputParameter(new ParameterRelated("retRampPaused", *iPropertyRampPaused));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetRampPaused);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::EnableActionGetRampTime(CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    iCallbackGetRampTime = aCallback;
    iPtrGetRampTime = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRampTime");
    action->AddOutputParameter(new ParameterUint("retRampTime"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgDimming1C::DoGetRampTime);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgDimming1C::DoSetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetLoadLevelTarget != NULL);
    if (0 != iCallbackSetLoadLevelTarget(iPtrSetLoadLevelTarget, aVersion, newLoadlevelTarget)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetLoadLevelTarget(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t GetLoadlevelTarget;
    ASSERT(iCallbackGetLoadLevelTarget != NULL);
    if (0 != iCallbackGetLoadLevelTarget(iPtrGetLoadLevelTarget, aVersion, &GetLoadlevelTarget)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    resp.Start();
    respGetLoadlevelTarget.Write(GetLoadlevelTarget);
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetLoadLevelStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t retLoadlevelStatus;
    ASSERT(iCallbackGetLoadLevelStatus != NULL);
    if (0 != iCallbackGetLoadLevelStatus(iPtrGetLoadLevelStatus, aVersion, &retLoadlevelStatus)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    resp.Start();
    respretLoadlevelStatus.Write(retLoadlevelStatus);
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoSetOnEffectLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetOnEffectLevel != NULL);
    if (0 != iCallbackSetOnEffectLevel(iPtrSetOnEffectLevel, aVersion, newOnEffectLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoSetOnEffect(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz newOnEffect;
    aInvocation.InvocationReadString("newOnEffect", newOnEffect);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetOnEffect != NULL);
    if (0 != iCallbackSetOnEffect(iPtrSetOnEffect, aVersion, (const char*)newOnEffect.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetOnEffectParameters(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* retOnEffect;
    uint32_t retOnEffectLevel;
    ASSERT(iCallbackGetOnEffectParameters != NULL);
    if (0 != iCallbackGetOnEffectParameters(iPtrGetOnEffectParameters, aVersion, &retOnEffect, &retOnEffectLevel)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respretOnEffect(aInvocation, "retOnEffect");
    InvocationResponseUint respretOnEffectLevel(aInvocation, "retOnEffectLevel");
    resp.Start();
    Brhz bufretOnEffect((const TChar*)retOnEffect);
    OhNetFreeExternal(retOnEffect);
    respretOnEffect.Write(bufretOnEffect);
    respretOnEffect.WriteFlush();
    respretOnEffectLevel.Write(retOnEffectLevel);
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoStepUp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStepUp != NULL);
    if (0 != iCallbackStepUp(iPtrStepUp, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoStepDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStepDown != NULL);
    if (0 != iCallbackStepDown(iPtrStepDown, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoStartRampUp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStartRampUp != NULL);
    if (0 != iCallbackStartRampUp(iPtrStartRampUp, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoStartRampDown(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStartRampDown != NULL);
    if (0 != iCallbackStartRampDown(iPtrStartRampDown, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoStopRamp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStopRamp != NULL);
    if (0 != iCallbackStopRamp(iPtrStopRamp, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoStartRampToLevel(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    TUint newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStartRampToLevel != NULL);
    if (0 != iCallbackStartRampToLevel(iPtrStartRampToLevel, aVersion, newLoadLevelTarget, newRampTime)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoSetStepDelta(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStepDelta != NULL);
    if (0 != iCallbackSetStepDelta(iPtrSetStepDelta, aVersion, newStepDelta)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetStepDelta(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t retStepDelta;
    ASSERT(iCallbackGetStepDelta != NULL);
    if (0 != iCallbackGetStepDelta(iPtrGetStepDelta, aVersion, &retStepDelta)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respretStepDelta(aInvocation, "retStepDelta");
    resp.Start();
    respretStepDelta.Write(retStepDelta);
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoSetRampRate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetRampRate != NULL);
    if (0 != iCallbackSetRampRate(iPtrSetRampRate, aVersion, newRampRate)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetRampRate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t retRampRate;
    ASSERT(iCallbackGetRampRate != NULL);
    if (0 != iCallbackGetRampRate(iPtrGetRampRate, aVersion, &retRampRate)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respretRampRate(aInvocation, "retRampRate");
    resp.Start();
    respretRampRate.Write(retRampRate);
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoPauseRamp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPauseRamp != NULL);
    if (0 != iCallbackPauseRamp(iPtrPauseRamp, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoResumeRamp(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackResumeRamp != NULL);
    if (0 != iCallbackResumeRamp(iPtrResumeRamp, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetIsRamping(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t retIsRamping;
    ASSERT(iCallbackGetIsRamping != NULL);
    if (0 != iCallbackGetIsRamping(iPtrGetIsRamping, aVersion, &retIsRamping)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respretIsRamping(aInvocation, "retIsRamping");
    resp.Start();
    respretIsRamping.Write((retIsRamping!=0));
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetRampPaused(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t retRampPaused;
    ASSERT(iCallbackGetRampPaused != NULL);
    if (0 != iCallbackGetRampPaused(iPtrGetRampPaused, aVersion, &retRampPaused)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respretRampPaused(aInvocation, "retRampPaused");
    resp.Start();
    respretRampPaused.Write((retRampPaused!=0));
    resp.End();
}

void DvProviderUpnpOrgDimming1C::DoGetRampTime(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t retRampTime;
    ASSERT(iCallbackGetRampTime != NULL);
    if (0 != iCallbackGetRampTime(iPtrGetRampTime, aVersion, &retRampTime)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respretRampTime(aInvocation, "retRampTime");
    resp.Start();
    respretRampTime.Write(retRampTime);
    resp.End();
}



THandle DvProviderUpnpOrgDimming1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgDimming1C(aDevice);
}

void DvProviderUpnpOrgDimming1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider);
}

void DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aProvider, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetLoadLevelTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aProvider, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetLoadLevelTarget(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aProvider, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetLoadLevelStatus(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aProvider, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetOnEffectLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetOnEffect(THandle aProvider, CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetOnEffect(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aProvider, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetOnEffectParameters(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStepUp(THandle aProvider, CallbackDimming1StepUp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStepUp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStepDown(THandle aProvider, CallbackDimming1StepDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStepDown(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStartRampUp(THandle aProvider, CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampUp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStartRampDown(THandle aProvider, CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampDown(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStopRamp(THandle aProvider, CallbackDimming1StopRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStopRamp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(THandle aProvider, CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampToLevel(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetStepDelta(THandle aProvider, CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetStepDelta(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetStepDelta(THandle aProvider, CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetStepDelta(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionSetRampRate(THandle aProvider, CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetRampRate(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetRampRate(THandle aProvider, CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampRate(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionPauseRamp(THandle aProvider, CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionPauseRamp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionResumeRamp(THandle aProvider, CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionResumeRamp(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetIsRamping(THandle aProvider, CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetIsRamping(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetRampPaused(THandle aProvider, CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampPaused(aCallback, aPtr);
}

void DvProviderUpnpOrgDimming1EnableActionGetRampTime(THandle aProvider, CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampTime(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyLoadLevelStatus(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyLoadLevelStatus(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgDimming1SetPropertyStepDelta(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyStepDelta(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyStepDelta(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyStepDelta(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgDimming1SetPropertyRampRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyRampRate(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyRampRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyRampRate(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgDimming1SetPropertyIsRamping(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyIsRamping((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyIsRamping(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyIsRamping(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderUpnpOrgDimming1SetPropertyRampPaused(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyRampPaused((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgDimming1GetPropertyRampPaused(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyRampPaused(val);
    *aValue = (val? 1 : 0);
}

