#include "DvLinnCoUkDelay1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkDelay1C : public DvProvider
{
public:
    DvProviderLinnCoUkDelay1C(DvDeviceC aDevice);
    TBool SetPropertyPresetXml(const Brx& aValue);
    void GetPropertyPresetXml(Brhz& aValue);
    TBool SetPropertyPresetIndex(TUint aValue);
    void GetPropertyPresetIndex(TUint& aValue);
    void EnableActionPresetXml(CallbackDelay1PresetXml aCallback, void* aPtr);
    void EnableActionPresetIndex(CallbackDelay1PresetIndex aCallback, void* aPtr);
    void EnableActionSetPresetIndex(CallbackDelay1SetPresetIndex aCallback, void* aPtr);
    void EnableActionSetPresetDelay(CallbackDelay1SetPresetDelay aCallback, void* aPtr);
    void EnableActionSetPresetVisible(CallbackDelay1SetPresetVisible aCallback, void* aPtr);
    void EnableActionSetPresetName(CallbackDelay1SetPresetName aCallback, void* aPtr);
    void EnableActionDelayMinimum(CallbackDelay1DelayMinimum aCallback, void* aPtr);
    void EnableActionDelayMaximum(CallbackDelay1DelayMaximum aCallback, void* aPtr);
    void EnableActionPresetCount(CallbackDelay1PresetCount aCallback, void* aPtr);
private:
    void DoPresetXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetDelay(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetVisible(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetPresetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelayMinimum(IDviInvocation& aInvocation, TUint aVersion);
    void DoDelayMaximum(IDviInvocation& aInvocation, TUint aVersion);
    void DoPresetCount(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackDelay1PresetXml iCallbackPresetXml;
    void* iPtrPresetXml;
    CallbackDelay1PresetIndex iCallbackPresetIndex;
    void* iPtrPresetIndex;
    CallbackDelay1SetPresetIndex iCallbackSetPresetIndex;
    void* iPtrSetPresetIndex;
    CallbackDelay1SetPresetDelay iCallbackSetPresetDelay;
    void* iPtrSetPresetDelay;
    CallbackDelay1SetPresetVisible iCallbackSetPresetVisible;
    void* iPtrSetPresetVisible;
    CallbackDelay1SetPresetName iCallbackSetPresetName;
    void* iPtrSetPresetName;
    CallbackDelay1DelayMinimum iCallbackDelayMinimum;
    void* iPtrDelayMinimum;
    CallbackDelay1DelayMaximum iCallbackDelayMaximum;
    void* iPtrDelayMaximum;
    CallbackDelay1PresetCount iCallbackPresetCount;
    void* iPtrPresetCount;
    PropertyString* iPropertyPresetXml;
    PropertyUint* iPropertyPresetIndex;
};

DvProviderLinnCoUkDelay1C::DvProviderLinnCoUkDelay1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Delay", 1)
{
    
    iPropertyPresetXml = new PropertyString(new ParameterString("PresetXml"));
    iService->AddProperty(iPropertyPresetXml); // passes ownership
    iPropertyPresetIndex = new PropertyUint(new ParameterUint("PresetIndex"));
    iService->AddProperty(iPropertyPresetIndex); // passes ownership
}

TBool DvProviderLinnCoUkDelay1C::SetPropertyPresetXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyPresetXml, aValue);
}

void DvProviderLinnCoUkDelay1C::GetPropertyPresetXml(Brhz& aValue)
{
    aValue.Set(iPropertyPresetXml->Value());
}

TBool DvProviderLinnCoUkDelay1C::SetPropertyPresetIndex(TUint aValue)
{
    return SetPropertyUint(*iPropertyPresetIndex, aValue);
}

void DvProviderLinnCoUkDelay1C::GetPropertyPresetIndex(TUint& aValue)
{
    aValue = iPropertyPresetIndex->Value();
}

void DvProviderLinnCoUkDelay1C::EnableActionPresetXml(CallbackDelay1PresetXml aCallback, void* aPtr)
{
    iCallbackPresetXml = aCallback;
    iPtrPresetXml = aPtr;
    Zapp::Action* action = new Zapp::Action("PresetXml");
    action->AddOutputParameter(new ParameterRelated("aPresetXml", *iPropertyPresetXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoPresetXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionPresetIndex(CallbackDelay1PresetIndex aCallback, void* aPtr)
{
    iCallbackPresetIndex = aCallback;
    iPtrPresetIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("PresetIndex");
    action->AddOutputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoPresetIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionSetPresetIndex(CallbackDelay1SetPresetIndex aCallback, void* aPtr)
{
    iCallbackSetPresetIndex = aCallback;
    iPtrSetPresetIndex = aPtr;
    Zapp::Action* action = new Zapp::Action("SetPresetIndex");
    action->AddInputParameter(new ParameterRelated("aIndex", *iPropertyPresetIndex));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoSetPresetIndex);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionSetPresetDelay(CallbackDelay1SetPresetDelay aCallback, void* aPtr)
{
    iCallbackSetPresetDelay = aCallback;
    iPtrSetPresetDelay = aPtr;
    Zapp::Action* action = new Zapp::Action("SetPresetDelay");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoSetPresetDelay);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionSetPresetVisible(CallbackDelay1SetPresetVisible aCallback, void* aPtr)
{
    iCallbackSetPresetVisible = aCallback;
    iPtrSetPresetVisible = aPtr;
    Zapp::Action* action = new Zapp::Action("SetPresetVisible");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterBool("aVisible"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoSetPresetVisible);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionSetPresetName(CallbackDelay1SetPresetName aCallback, void* aPtr)
{
    iCallbackSetPresetName = aCallback;
    iPtrSetPresetName = aPtr;
    Zapp::Action* action = new Zapp::Action("SetPresetName");
    action->AddInputParameter(new ParameterUint("aIndex"));
    action->AddInputParameter(new ParameterString("aName"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoSetPresetName);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionDelayMinimum(CallbackDelay1DelayMinimum aCallback, void* aPtr)
{
    iCallbackDelayMinimum = aCallback;
    iPtrDelayMinimum = aPtr;
    Zapp::Action* action = new Zapp::Action("DelayMinimum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoDelayMinimum);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionDelayMaximum(CallbackDelay1DelayMaximum aCallback, void* aPtr)
{
    iCallbackDelayMaximum = aCallback;
    iPtrDelayMaximum = aPtr;
    Zapp::Action* action = new Zapp::Action("DelayMaximum");
    action->AddOutputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoDelayMaximum);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::EnableActionPresetCount(CallbackDelay1PresetCount aCallback, void* aPtr)
{
    iCallbackPresetCount = aCallback;
    iPtrPresetCount = aPtr;
    Zapp::Action* action = new Zapp::Action("PresetCount");
    action->AddOutputParameter(new ParameterUint("aCount"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDelay1C::DoPresetCount);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDelay1C::DoPresetXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aPresetXml;
    ASSERT(iCallbackPresetXml != NULL);
    if (0 != iCallbackPresetXml(iPtrPresetXml, aVersion, &aPresetXml)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaPresetXml(aInvocation, "aPresetXml");
    resp.Start();
    Brhz bufaPresetXml((const TChar*)aPresetXml);
    ZappFreeExternal(aPresetXml);
    respaPresetXml.Write(bufaPresetXml);
    respaPresetXml.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoPresetIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aIndex;
    ASSERT(iCallbackPresetIndex != NULL);
    if (0 != iCallbackPresetIndex(iPtrPresetIndex, aVersion, &aIndex)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaIndex(aInvocation, "aIndex");
    resp.Start();
    respaIndex.Write(aIndex);
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoSetPresetIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetPresetIndex != NULL);
    if (0 != iCallbackSetPresetIndex(iPtrSetPresetIndex, aVersion, aIndex)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoSetPresetDelay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    TUint aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetPresetDelay != NULL);
    if (0 != iCallbackSetPresetDelay(iPtrSetPresetDelay, aVersion, aIndex, aDelay)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoSetPresetVisible(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    TBool aVisible = aInvocation.InvocationReadBool("aVisible");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetPresetVisible != NULL);
    if (0 != iCallbackSetPresetVisible(iPtrSetPresetVisible, aVersion, aIndex, aVisible)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoSetPresetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aIndex = aInvocation.InvocationReadUint("aIndex");
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetPresetName != NULL);
    if (0 != iCallbackSetPresetName(iPtrSetPresetName, aVersion, aIndex, (const char*)aName.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoDelayMinimum(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aDelay;
    ASSERT(iCallbackDelayMinimum != NULL);
    if (0 != iCallbackDelayMinimum(iPtrDelayMinimum, aVersion, &aDelay)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaDelay(aInvocation, "aDelay");
    resp.Start();
    respaDelay.Write(aDelay);
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoDelayMaximum(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aDelay;
    ASSERT(iCallbackDelayMaximum != NULL);
    if (0 != iCallbackDelayMaximum(iPtrDelayMaximum, aVersion, &aDelay)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaDelay(aInvocation, "aDelay");
    resp.Start();
    respaDelay.Write(aDelay);
    resp.End();
}

void DvProviderLinnCoUkDelay1C::DoPresetCount(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aCount;
    ASSERT(iCallbackPresetCount != NULL);
    if (0 != iCallbackPresetCount(iPtrPresetCount, aVersion, &aCount)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaCount(aInvocation, "aCount");
    resp.Start();
    respaCount.Write(aCount);
    resp.End();
}



THandle DvProviderLinnCoUkDelay1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDelay1C(aDevice);
}

void DvProviderLinnCoUkDelay1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider);
}

void DvProviderLinnCoUkDelay1EnableActionPresetXml(THandle aProvider, CallbackDelay1PresetXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionPresetXml(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionPresetIndex(THandle aProvider, CallbackDelay1PresetIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionPresetIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionSetPresetIndex(THandle aProvider, CallbackDelay1SetPresetIndex aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionSetPresetIndex(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionSetPresetDelay(THandle aProvider, CallbackDelay1SetPresetDelay aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionSetPresetDelay(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionSetPresetVisible(THandle aProvider, CallbackDelay1SetPresetVisible aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionSetPresetVisible(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionSetPresetName(THandle aProvider, CallbackDelay1SetPresetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionSetPresetName(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionDelayMinimum(THandle aProvider, CallbackDelay1DelayMinimum aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionDelayMinimum(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionDelayMaximum(THandle aProvider, CallbackDelay1DelayMaximum aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionDelayMaximum(aCallback, aPtr);
}

void DvProviderLinnCoUkDelay1EnableActionPresetCount(THandle aProvider, CallbackDelay1PresetCount aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->EnableActionPresetCount(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkDelay1SetPropertyPresetXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->SetPropertyPresetXml(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDelay1GetPropertyPresetXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->GetPropertyPresetXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkDelay1SetPropertyPresetIndex(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->SetPropertyPresetIndex(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDelay1GetPropertyPresetIndex(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDelay1C*>(aProvider)->GetPropertyPresetIndex(val);
    *aValue = val;
}

