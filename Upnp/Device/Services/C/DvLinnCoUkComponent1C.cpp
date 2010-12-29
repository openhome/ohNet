#include "DvLinnCoUkComponent1.h"
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

class DvProviderLinnCoUkComponent1C : public DvProvider
{
public:
    DvProviderLinnCoUkComponent1C(DvDeviceC aDevice);
    TBool SetPropertyAmplifierEnabled(TBool aValue);
    void GetPropertyAmplifierEnabled(TBool& aValue);
    TBool SetPropertyAmplifierAttenuation(const Brx& aValue);
    void GetPropertyAmplifierAttenuation(Brhz& aValue);
    TBool SetPropertyVolumeControlEnabled(TBool aValue);
    void GetPropertyVolumeControlEnabled(TBool& aValue);
    TBool SetPropertyDigitalAudioOutputRaw(TBool aValue);
    void GetPropertyDigitalAudioOutputRaw(TBool& aValue);
    void EnableActionAmplifierEnabled(CallbackComponent1AmplifierEnabled aCallback, void* aPtr);
    void EnableActionSetAmplifierEnabled(CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr);
    void EnableActionAmplifierAttenuation(CallbackComponent1AmplifierAttenuation aCallback, void* aPtr);
    void EnableActionSetAmplifierAttenuation(CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr);
    void EnableActionSetVolumeControlEnabled(CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr);
    void EnableActionVolumeControlEnabled(CallbackComponent1VolumeControlEnabled aCallback, void* aPtr);
    void EnableActionSetDigitalAudioOutputRaw(CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr);
    void EnableActionDigitalAudioOutputRaw(CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr);
    void EnableActionAmplifierOverTemperature(CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr);
    void EnableActionEthernetLinkConnected(CallbackComponent1EthernetLinkConnected aCallback, void* aPtr);
    void EnableActionLocate(CallbackComponent1Locate aCallback, void* aPtr);
private:
    void DoAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion);
    void DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion);
    void DoAmplifierOverTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoEthernetLinkConnected(IDviInvocation& aInvocation, TUint aVersion);
    void DoLocate(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackComponent1AmplifierEnabled iCallbackAmplifierEnabled;
    void* iPtrAmplifierEnabled;
    CallbackComponent1SetAmplifierEnabled iCallbackSetAmplifierEnabled;
    void* iPtrSetAmplifierEnabled;
    CallbackComponent1AmplifierAttenuation iCallbackAmplifierAttenuation;
    void* iPtrAmplifierAttenuation;
    CallbackComponent1SetAmplifierAttenuation iCallbackSetAmplifierAttenuation;
    void* iPtrSetAmplifierAttenuation;
    CallbackComponent1SetVolumeControlEnabled iCallbackSetVolumeControlEnabled;
    void* iPtrSetVolumeControlEnabled;
    CallbackComponent1VolumeControlEnabled iCallbackVolumeControlEnabled;
    void* iPtrVolumeControlEnabled;
    CallbackComponent1SetDigitalAudioOutputRaw iCallbackSetDigitalAudioOutputRaw;
    void* iPtrSetDigitalAudioOutputRaw;
    CallbackComponent1DigitalAudioOutputRaw iCallbackDigitalAudioOutputRaw;
    void* iPtrDigitalAudioOutputRaw;
    CallbackComponent1AmplifierOverTemperature iCallbackAmplifierOverTemperature;
    void* iPtrAmplifierOverTemperature;
    CallbackComponent1EthernetLinkConnected iCallbackEthernetLinkConnected;
    void* iPtrEthernetLinkConnected;
    CallbackComponent1Locate iCallbackLocate;
    void* iPtrLocate;
    PropertyBool* iPropertyAmplifierEnabled;
    PropertyString* iPropertyAmplifierAttenuation;
    PropertyBool* iPropertyVolumeControlEnabled;
    PropertyBool* iPropertyDigitalAudioOutputRaw;
};

DvProviderLinnCoUkComponent1C::DvProviderLinnCoUkComponent1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Component", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyAmplifierEnabled = new PropertyBool(new ParameterBool("AmplifierEnabled"));
    iService->AddProperty(iPropertyAmplifierEnabled); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"-12dB";
    allowedValues[index++] = (TChar*)"-9dB";
    allowedValues[index++] = (TChar*)"-6dB";
    allowedValues[index++] = (TChar*)"0dB";
    iPropertyAmplifierAttenuation = new PropertyString(new ParameterString("AmplifierAttenuation", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyAmplifierAttenuation); // passes ownership
    iPropertyVolumeControlEnabled = new PropertyBool(new ParameterBool("VolumeControlEnabled"));
    iService->AddProperty(iPropertyVolumeControlEnabled); // passes ownership
    iPropertyDigitalAudioOutputRaw = new PropertyBool(new ParameterBool("DigitalAudioOutputRaw"));
    iService->AddProperty(iPropertyDigitalAudioOutputRaw); // passes ownership
}

TBool DvProviderLinnCoUkComponent1C::SetPropertyAmplifierEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyAmplifierEnabled, aValue);
}

void DvProviderLinnCoUkComponent1C::GetPropertyAmplifierEnabled(TBool& aValue)
{
    aValue = iPropertyAmplifierEnabled->Value();
}

TBool DvProviderLinnCoUkComponent1C::SetPropertyAmplifierAttenuation(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAmplifierAttenuation, aValue);
}

void DvProviderLinnCoUkComponent1C::GetPropertyAmplifierAttenuation(Brhz& aValue)
{
    aValue.Set(iPropertyAmplifierAttenuation->Value());
}

TBool DvProviderLinnCoUkComponent1C::SetPropertyVolumeControlEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyVolumeControlEnabled, aValue);
}

void DvProviderLinnCoUkComponent1C::GetPropertyVolumeControlEnabled(TBool& aValue)
{
    aValue = iPropertyVolumeControlEnabled->Value();
}

TBool DvProviderLinnCoUkComponent1C::SetPropertyDigitalAudioOutputRaw(TBool aValue)
{
    return SetPropertyBool(*iPropertyDigitalAudioOutputRaw, aValue);
}

void DvProviderLinnCoUkComponent1C::GetPropertyDigitalAudioOutputRaw(TBool& aValue)
{
    aValue = iPropertyDigitalAudioOutputRaw->Value();
}

void DvProviderLinnCoUkComponent1C::EnableActionAmplifierEnabled(CallbackComponent1AmplifierEnabled aCallback, void* aPtr)
{
    iCallbackAmplifierEnabled = aCallback;
    iPtrAmplifierEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("AmplifierEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionSetAmplifierEnabled(CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr)
{
    iCallbackSetAmplifierEnabled = aCallback;
    iPtrSetAmplifierEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("SetAmplifierEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoSetAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionAmplifierAttenuation(CallbackComponent1AmplifierAttenuation aCallback, void* aPtr)
{
    iCallbackAmplifierAttenuation = aCallback;
    iPtrAmplifierAttenuation = aPtr;
    Zapp::Action* action = new Zapp::Action("AmplifierAttenuation");
    action->AddOutputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionSetAmplifierAttenuation(CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr)
{
    iCallbackSetAmplifierAttenuation = aCallback;
    iPtrSetAmplifierAttenuation = aPtr;
    Zapp::Action* action = new Zapp::Action("SetAmplifierAttenuation");
    action->AddInputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoSetAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionSetVolumeControlEnabled(CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr)
{
    iCallbackSetVolumeControlEnabled = aCallback;
    iPtrSetVolumeControlEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("SetVolumeControlEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoSetVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionVolumeControlEnabled(CallbackComponent1VolumeControlEnabled aCallback, void* aPtr)
{
    iCallbackVolumeControlEnabled = aCallback;
    iPtrVolumeControlEnabled = aPtr;
    Zapp::Action* action = new Zapp::Action("VolumeControlEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionSetDigitalAudioOutputRaw(CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr)
{
    iCallbackSetDigitalAudioOutputRaw = aCallback;
    iPtrSetDigitalAudioOutputRaw = aPtr;
    Zapp::Action* action = new Zapp::Action("SetDigitalAudioOutputRaw");
    action->AddInputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoSetDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionDigitalAudioOutputRaw(CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr)
{
    iCallbackDigitalAudioOutputRaw = aCallback;
    iPtrDigitalAudioOutputRaw = aPtr;
    Zapp::Action* action = new Zapp::Action("DigitalAudioOutputRaw");
    action->AddOutputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionAmplifierOverTemperature(CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr)
{
    iCallbackAmplifierOverTemperature = aCallback;
    iPtrAmplifierOverTemperature = aPtr;
    Zapp::Action* action = new Zapp::Action("AmplifierOverTemperature");
    action->AddOutputParameter(new ParameterBool("aOverTemperature"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoAmplifierOverTemperature);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionEthernetLinkConnected(CallbackComponent1EthernetLinkConnected aCallback, void* aPtr)
{
    iCallbackEthernetLinkConnected = aCallback;
    iPtrEthernetLinkConnected = aPtr;
    Zapp::Action* action = new Zapp::Action("EthernetLinkConnected");
    action->AddOutputParameter(new ParameterBool("aLinkConnected"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoEthernetLinkConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::EnableActionLocate(CallbackComponent1Locate aCallback, void* aPtr)
{
    iCallbackLocate = aCallback;
    iPtrLocate = aPtr;
    Zapp::Action* action = new Zapp::Action("Locate");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1C::DoLocate);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1C::DoAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aEnabled;
    ASSERT(iCallbackAmplifierEnabled != NULL);
    if (0 != iCallbackAmplifierEnabled(iPtrAmplifierEnabled, aVersion, &aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    resp.Start();
    respaEnabled.Write((aEnabled!=0));
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoSetAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetAmplifierEnabled != NULL);
    if (0 != iCallbackSetAmplifierEnabled(iPtrSetAmplifierEnabled, aVersion, aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aAttenuation;
    ASSERT(iCallbackAmplifierAttenuation != NULL);
    if (0 != iCallbackAmplifierAttenuation(iPtrAmplifierAttenuation, aVersion, &aAttenuation)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaAttenuation(aInvocation, "aAttenuation");
    resp.Start();
    Brhz bufaAttenuation((const TChar*)aAttenuation);
    ZappFreeExternal(aAttenuation);
    respaAttenuation.Write(bufaAttenuation);
    respaAttenuation.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoSetAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aAttenuation;
    aInvocation.InvocationReadString("aAttenuation", aAttenuation);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetAmplifierAttenuation != NULL);
    if (0 != iCallbackSetAmplifierAttenuation(iPtrSetAmplifierAttenuation, aVersion, (const char*)aAttenuation.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoSetVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetVolumeControlEnabled != NULL);
    if (0 != iCallbackSetVolumeControlEnabled(iPtrSetVolumeControlEnabled, aVersion, aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aEnabled;
    ASSERT(iCallbackVolumeControlEnabled != NULL);
    if (0 != iCallbackVolumeControlEnabled(iPtrVolumeControlEnabled, aVersion, &aEnabled)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    resp.Start();
    respaEnabled.Write((aEnabled!=0));
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aRaw = aInvocation.InvocationReadBool("aRaw");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetDigitalAudioOutputRaw != NULL);
    if (0 != iCallbackSetDigitalAudioOutputRaw(iPtrSetDigitalAudioOutputRaw, aVersion, aRaw)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aRaw;
    ASSERT(iCallbackDigitalAudioOutputRaw != NULL);
    if (0 != iCallbackDigitalAudioOutputRaw(iPtrDigitalAudioOutputRaw, aVersion, &aRaw)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaRaw(aInvocation, "aRaw");
    resp.Start();
    respaRaw.Write((aRaw!=0));
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoAmplifierOverTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aOverTemperature;
    ASSERT(iCallbackAmplifierOverTemperature != NULL);
    if (0 != iCallbackAmplifierOverTemperature(iPtrAmplifierOverTemperature, aVersion, &aOverTemperature)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaOverTemperature(aInvocation, "aOverTemperature");
    resp.Start();
    respaOverTemperature.Write((aOverTemperature!=0));
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoEthernetLinkConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aLinkConnected;
    ASSERT(iCallbackEthernetLinkConnected != NULL);
    if (0 != iCallbackEthernetLinkConnected(iPtrEthernetLinkConnected, aVersion, &aLinkConnected)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respaLinkConnected(aInvocation, "aLinkConnected");
    resp.Start();
    respaLinkConnected.Write((aLinkConnected!=0));
    resp.End();
}

void DvProviderLinnCoUkComponent1C::DoLocate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackLocate != NULL);
    if (0 != iCallbackLocate(iPtrLocate, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkComponent1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkComponent1C(aDevice);
}

void DvProviderLinnCoUkComponent1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider);
}

void DvProviderLinnCoUkComponent1EnableActionAmplifierEnabled(THandle aProvider, CallbackComponent1AmplifierEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionAmplifierEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetAmplifierEnabled(THandle aProvider, CallbackComponent1SetAmplifierEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetAmplifierEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionAmplifierAttenuation(THandle aProvider, CallbackComponent1AmplifierAttenuation aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionAmplifierAttenuation(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetAmplifierAttenuation(THandle aProvider, CallbackComponent1SetAmplifierAttenuation aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetAmplifierAttenuation(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetVolumeControlEnabled(THandle aProvider, CallbackComponent1SetVolumeControlEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetVolumeControlEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionVolumeControlEnabled(THandle aProvider, CallbackComponent1VolumeControlEnabled aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionVolumeControlEnabled(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1SetDigitalAudioOutputRaw aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionSetDigitalAudioOutputRaw(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(THandle aProvider, CallbackComponent1DigitalAudioOutputRaw aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionDigitalAudioOutputRaw(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionAmplifierOverTemperature(THandle aProvider, CallbackComponent1AmplifierOverTemperature aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionAmplifierOverTemperature(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionEthernetLinkConnected(THandle aProvider, CallbackComponent1EthernetLinkConnected aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionEthernetLinkConnected(aCallback, aPtr);
}

void DvProviderLinnCoUkComponent1EnableActionLocate(THandle aProvider, CallbackComponent1Locate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->EnableActionLocate(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyAmplifierEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyAmplifierEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyAmplifierEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkComponent1SetPropertyAmplifierAttenuation(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyAmplifierAttenuation(buf)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyAmplifierAttenuation(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyAmplifierAttenuation(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderLinnCoUkComponent1SetPropertyVolumeControlEnabled(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyVolumeControlEnabled((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyVolumeControlEnabled(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyVolumeControlEnabled(val);
    *aValue = (val? 1 : 0);
}

int32_t DvProviderLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->SetPropertyDigitalAudioOutputRaw((aValue!=0))? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderLinnCoUkComponent1C*>(aProvider)->GetPropertyDigitalAudioOutputRaw(val);
    *aValue = (val? 1 : 0);
}

