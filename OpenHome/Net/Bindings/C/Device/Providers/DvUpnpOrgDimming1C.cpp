#include "DvUpnpOrgDimming1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
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
    void EnablePropertyLoadLevelStatus();
    void EnablePropertyStepDelta();
    void EnablePropertyRampRate();
    void EnablePropertyIsRamping();
    void EnablePropertyRampPaused();
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
    void DoSetLoadLevelTarget(IDviInvocation& aInvocation);
    void DoGetLoadLevelTarget(IDviInvocation& aInvocation);
    void DoGetLoadLevelStatus(IDviInvocation& aInvocation);
    void DoSetOnEffectLevel(IDviInvocation& aInvocation);
    void DoSetOnEffect(IDviInvocation& aInvocation);
    void DoGetOnEffectParameters(IDviInvocation& aInvocation);
    void DoStepUp(IDviInvocation& aInvocation);
    void DoStepDown(IDviInvocation& aInvocation);
    void DoStartRampUp(IDviInvocation& aInvocation);
    void DoStartRampDown(IDviInvocation& aInvocation);
    void DoStopRamp(IDviInvocation& aInvocation);
    void DoStartRampToLevel(IDviInvocation& aInvocation);
    void DoSetStepDelta(IDviInvocation& aInvocation);
    void DoGetStepDelta(IDviInvocation& aInvocation);
    void DoSetRampRate(IDviInvocation& aInvocation);
    void DoGetRampRate(IDviInvocation& aInvocation);
    void DoPauseRamp(IDviInvocation& aInvocation);
    void DoResumeRamp(IDviInvocation& aInvocation);
    void DoGetIsRamping(IDviInvocation& aInvocation);
    void DoGetRampPaused(IDviInvocation& aInvocation);
    void DoGetRampTime(IDviInvocation& aInvocation);
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
    iPropertyLoadLevelStatus = NULL;
    iPropertyStepDelta = NULL;
    iPropertyRampRate = NULL;
    iPropertyIsRamping = NULL;
    iPropertyRampPaused = NULL;
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyLoadLevelStatus(TUint aValue)
{
    ASSERT(iPropertyLoadLevelStatus != NULL);
    return SetPropertyUint(*iPropertyLoadLevelStatus, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyLoadLevelStatus(TUint& aValue)
{
    ASSERT(iPropertyLoadLevelStatus != NULL);
    aValue = iPropertyLoadLevelStatus->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyStepDelta(TUint aValue)
{
    ASSERT(iPropertyStepDelta != NULL);
    return SetPropertyUint(*iPropertyStepDelta, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyStepDelta(TUint& aValue)
{
    ASSERT(iPropertyStepDelta != NULL);
    aValue = iPropertyStepDelta->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyRampRate(TUint aValue)
{
    ASSERT(iPropertyRampRate != NULL);
    return SetPropertyUint(*iPropertyRampRate, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyRampRate(TUint& aValue)
{
    ASSERT(iPropertyRampRate != NULL);
    aValue = iPropertyRampRate->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyIsRamping(TBool aValue)
{
    ASSERT(iPropertyIsRamping != NULL);
    return SetPropertyBool(*iPropertyIsRamping, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyIsRamping(TBool& aValue)
{
    ASSERT(iPropertyIsRamping != NULL);
    aValue = iPropertyIsRamping->Value();
}

TBool DvProviderUpnpOrgDimming1C::SetPropertyRampPaused(TBool aValue)
{
    ASSERT(iPropertyRampPaused != NULL);
    return SetPropertyBool(*iPropertyRampPaused, aValue);
}

void DvProviderUpnpOrgDimming1C::GetPropertyRampPaused(TBool& aValue)
{
    ASSERT(iPropertyRampPaused != NULL);
    aValue = iPropertyRampPaused->Value();
}

void DvProviderUpnpOrgDimming1C::EnablePropertyLoadLevelStatus()
{
    iPropertyLoadLevelStatus = new PropertyUint(iDvStack.Env(), new ParameterUint("LoadLevelStatus", 0, 100));
    iService->AddProperty(iPropertyLoadLevelStatus); // passes ownership
}

void DvProviderUpnpOrgDimming1C::EnablePropertyStepDelta()
{
    iPropertyStepDelta = new PropertyUint(iDvStack.Env(), new ParameterUint("StepDelta", 1, 100));
    iService->AddProperty(iPropertyStepDelta); // passes ownership
}

void DvProviderUpnpOrgDimming1C::EnablePropertyRampRate()
{
    iPropertyRampRate = new PropertyUint(iDvStack.Env(), new ParameterUint("RampRate", 0, 100));
    iService->AddProperty(iPropertyRampRate); // passes ownership
}

void DvProviderUpnpOrgDimming1C::EnablePropertyIsRamping()
{
    iPropertyIsRamping = new PropertyBool(iDvStack.Env(), new ParameterBool("IsRamping"));
    iService->AddProperty(iPropertyIsRamping); // passes ownership
}

void DvProviderUpnpOrgDimming1C::EnablePropertyRampPaused()
{
    iPropertyRampPaused = new PropertyBool(iDvStack.Env(), new ParameterBool("RampPaused"));
    iService->AddProperty(iPropertyRampPaused); // passes ownership
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

void DvProviderUpnpOrgDimming1C::DoSetLoadLevelTarget(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint newLoadlevelTarget = aInvocation.InvocationReadUint("newLoadlevelTarget");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetLoadLevelTarget != NULL);
    if (0 != iCallbackSetLoadLevelTarget(iPtrSetLoadLevelTarget, invocationC, invocationCPtr, newLoadlevelTarget)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetLoadLevelTarget(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t GetLoadlevelTarget;
    ASSERT(iCallbackGetLoadLevelTarget != NULL);
    if (0 != iCallbackGetLoadLevelTarget(iPtrGetLoadLevelTarget, invocationC, invocationCPtr, &GetLoadlevelTarget)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respGetLoadlevelTarget(aInvocation, "GetLoadlevelTarget");
    invocation.StartResponse();
    respGetLoadlevelTarget.Write(GetLoadlevelTarget);
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetLoadLevelStatus(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t retLoadlevelStatus;
    ASSERT(iCallbackGetLoadLevelStatus != NULL);
    if (0 != iCallbackGetLoadLevelStatus(iPtrGetLoadLevelStatus, invocationC, invocationCPtr, &retLoadlevelStatus)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respretLoadlevelStatus(aInvocation, "retLoadlevelStatus");
    invocation.StartResponse();
    respretLoadlevelStatus.Write(retLoadlevelStatus);
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoSetOnEffectLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint newOnEffectLevel = aInvocation.InvocationReadUint("newOnEffectLevel");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetOnEffectLevel != NULL);
    if (0 != iCallbackSetOnEffectLevel(iPtrSetOnEffectLevel, invocationC, invocationCPtr, newOnEffectLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoSetOnEffect(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz newOnEffect;
    aInvocation.InvocationReadString("newOnEffect", newOnEffect);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetOnEffect != NULL);
    if (0 != iCallbackSetOnEffect(iPtrSetOnEffect, invocationC, invocationCPtr, (const char*)newOnEffect.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetOnEffectParameters(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* retOnEffect;
    uint32_t retOnEffectLevel;
    ASSERT(iCallbackGetOnEffectParameters != NULL);
    if (0 != iCallbackGetOnEffectParameters(iPtrGetOnEffectParameters, invocationC, invocationCPtr, &retOnEffect, &retOnEffectLevel)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respretOnEffect(aInvocation, "retOnEffect");
    DviInvocationResponseUint respretOnEffectLevel(aInvocation, "retOnEffectLevel");
    invocation.StartResponse();
    Brhz bufretOnEffect((const TChar*)retOnEffect);
    OhNetFreeExternal(retOnEffect);
    respretOnEffect.Write(bufretOnEffect);
    respretOnEffect.WriteFlush();
    respretOnEffectLevel.Write(retOnEffectLevel);
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoStepUp(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStepUp != NULL);
    if (0 != iCallbackStepUp(iPtrStepUp, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoStepDown(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStepDown != NULL);
    if (0 != iCallbackStepDown(iPtrStepDown, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoStartRampUp(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStartRampUp != NULL);
    if (0 != iCallbackStartRampUp(iPtrStartRampUp, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoStartRampDown(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStartRampDown != NULL);
    if (0 != iCallbackStartRampDown(iPtrStartRampDown, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoStopRamp(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStopRamp != NULL);
    if (0 != iCallbackStopRamp(iPtrStopRamp, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoStartRampToLevel(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint newLoadLevelTarget = aInvocation.InvocationReadUint("newLoadLevelTarget");
    TUint newRampTime = aInvocation.InvocationReadUint("newRampTime");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStartRampToLevel != NULL);
    if (0 != iCallbackStartRampToLevel(iPtrStartRampToLevel, invocationC, invocationCPtr, newLoadLevelTarget, newRampTime)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoSetStepDelta(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint newStepDelta = aInvocation.InvocationReadUint("newStepDelta");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetStepDelta != NULL);
    if (0 != iCallbackSetStepDelta(iPtrSetStepDelta, invocationC, invocationCPtr, newStepDelta)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetStepDelta(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t retStepDelta;
    ASSERT(iCallbackGetStepDelta != NULL);
    if (0 != iCallbackGetStepDelta(iPtrGetStepDelta, invocationC, invocationCPtr, &retStepDelta)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respretStepDelta(aInvocation, "retStepDelta");
    invocation.StartResponse();
    respretStepDelta.Write(retStepDelta);
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoSetRampRate(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint newRampRate = aInvocation.InvocationReadUint("newRampRate");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetRampRate != NULL);
    if (0 != iCallbackSetRampRate(iPtrSetRampRate, invocationC, invocationCPtr, newRampRate)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetRampRate(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t retRampRate;
    ASSERT(iCallbackGetRampRate != NULL);
    if (0 != iCallbackGetRampRate(iPtrGetRampRate, invocationC, invocationCPtr, &retRampRate)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respretRampRate(aInvocation, "retRampRate");
    invocation.StartResponse();
    respretRampRate.Write(retRampRate);
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoPauseRamp(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPauseRamp != NULL);
    if (0 != iCallbackPauseRamp(iPtrPauseRamp, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoResumeRamp(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackResumeRamp != NULL);
    if (0 != iCallbackResumeRamp(iPtrResumeRamp, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetIsRamping(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t retIsRamping;
    ASSERT(iCallbackGetIsRamping != NULL);
    if (0 != iCallbackGetIsRamping(iPtrGetIsRamping, invocationC, invocationCPtr, &retIsRamping)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respretIsRamping(aInvocation, "retIsRamping");
    invocation.StartResponse();
    respretIsRamping.Write((retIsRamping!=0));
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetRampPaused(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t retRampPaused;
    ASSERT(iCallbackGetRampPaused != NULL);
    if (0 != iCallbackGetRampPaused(iPtrGetRampPaused, invocationC, invocationCPtr, &retRampPaused)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respretRampPaused(aInvocation, "retRampPaused");
    invocation.StartResponse();
    respretRampPaused.Write((retRampPaused!=0));
    invocation.EndResponse();
}

void DvProviderUpnpOrgDimming1C::DoGetRampTime(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t retRampTime;
    ASSERT(iCallbackGetRampTime != NULL);
    if (0 != iCallbackGetRampTime(iPtrGetRampTime, invocationC, invocationCPtr, &retRampTime)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respretRampTime(aInvocation, "retRampTime");
    invocation.StartResponse();
    respretRampTime.Write(retRampTime);
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgDimming1Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgDimming1C(aDevice);
}

void STDCALL DvProviderUpnpOrgDimming1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionSetLoadLevelTarget(THandle aProvider, CallbackDimming1SetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetLoadLevelTarget(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetLoadLevelTarget(THandle aProvider, CallbackDimming1GetLoadLevelTarget aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetLoadLevelTarget(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetLoadLevelStatus(THandle aProvider, CallbackDimming1GetLoadLevelStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetLoadLevelStatus(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionSetOnEffectLevel(THandle aProvider, CallbackDimming1SetOnEffectLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetOnEffectLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionSetOnEffect(THandle aProvider, CallbackDimming1SetOnEffect aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetOnEffect(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetOnEffectParameters(THandle aProvider, CallbackDimming1GetOnEffectParameters aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetOnEffectParameters(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionStepUp(THandle aProvider, CallbackDimming1StepUp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStepUp(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionStepDown(THandle aProvider, CallbackDimming1StepDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStepDown(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionStartRampUp(THandle aProvider, CallbackDimming1StartRampUp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampUp(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionStartRampDown(THandle aProvider, CallbackDimming1StartRampDown aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampDown(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionStopRamp(THandle aProvider, CallbackDimming1StopRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStopRamp(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionStartRampToLevel(THandle aProvider, CallbackDimming1StartRampToLevel aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionStartRampToLevel(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionSetStepDelta(THandle aProvider, CallbackDimming1SetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetStepDelta(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetStepDelta(THandle aProvider, CallbackDimming1GetStepDelta aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetStepDelta(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionSetRampRate(THandle aProvider, CallbackDimming1SetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionSetRampRate(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetRampRate(THandle aProvider, CallbackDimming1GetRampRate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampRate(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionPauseRamp(THandle aProvider, CallbackDimming1PauseRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionPauseRamp(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionResumeRamp(THandle aProvider, CallbackDimming1ResumeRamp aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionResumeRamp(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetIsRamping(THandle aProvider, CallbackDimming1GetIsRamping aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetIsRamping(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetRampPaused(THandle aProvider, CallbackDimming1GetRampPaused aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampPaused(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgDimming1EnableActionGetRampTime(THandle aProvider, CallbackDimming1GetRampTime aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnableActionGetRampTime(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyLoadLevelStatus(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyLoadLevelStatus(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgDimming1GetPropertyLoadLevelStatus(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyLoadLevelStatus(val);
    *aValue = val;
}

int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyStepDelta(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyStepDelta(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgDimming1GetPropertyStepDelta(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyStepDelta(val);
    *aValue = val;
}

int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyRampRate(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyRampRate(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgDimming1GetPropertyRampRate(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyRampRate(val);
    *aValue = val;
}

int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyIsRamping(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyIsRamping((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgDimming1GetPropertyIsRamping(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyIsRamping(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderUpnpOrgDimming1SetPropertyRampPaused(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->SetPropertyRampPaused((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgDimming1GetPropertyRampPaused(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->GetPropertyRampPaused(val);
    *aValue = (val? 1 : 0);
}

void STDCALL DvProviderUpnpOrgDimming1EnablePropertyLoadLevelStatus(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnablePropertyLoadLevelStatus();
}

void STDCALL DvProviderUpnpOrgDimming1EnablePropertyStepDelta(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnablePropertyStepDelta();
}

void STDCALL DvProviderUpnpOrgDimming1EnablePropertyRampRate(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnablePropertyRampRate();
}

void STDCALL DvProviderUpnpOrgDimming1EnablePropertyIsRamping(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnablePropertyIsRamping();
}

void STDCALL DvProviderUpnpOrgDimming1EnablePropertyRampPaused(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgDimming1C*>(aProvider)->EnablePropertyRampPaused();
}

