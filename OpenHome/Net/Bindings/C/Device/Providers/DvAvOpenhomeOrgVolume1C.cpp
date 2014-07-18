#include "DvAvOpenhomeOrgVolume1.h"
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

class DvProviderAvOpenhomeOrgVolume1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgVolume1C(DvDeviceC aDevice);
    TBool SetPropertyVolume(TUint aValue);
    void GetPropertyVolume(TUint& aValue);
    TBool SetPropertyMute(TBool aValue);
    void GetPropertyMute(TBool& aValue);
    TBool SetPropertyBalance(TInt aValue);
    void GetPropertyBalance(TInt& aValue);
    TBool SetPropertyFade(TInt aValue);
    void GetPropertyFade(TInt& aValue);
    TBool SetPropertyVolumeLimit(TUint aValue);
    void GetPropertyVolumeLimit(TUint& aValue);
    TBool SetPropertyVolumeMax(TUint aValue);
    void GetPropertyVolumeMax(TUint& aValue);
    TBool SetPropertyVolumeUnity(TUint aValue);
    void GetPropertyVolumeUnity(TUint& aValue);
    TBool SetPropertyVolumeSteps(TUint aValue);
    void GetPropertyVolumeSteps(TUint& aValue);
    TBool SetPropertyVolumeMilliDbPerStep(TUint aValue);
    void GetPropertyVolumeMilliDbPerStep(TUint& aValue);
    TBool SetPropertyBalanceMax(TUint aValue);
    void GetPropertyBalanceMax(TUint& aValue);
    TBool SetPropertyFadeMax(TUint aValue);
    void GetPropertyFadeMax(TUint& aValue);
    void EnablePropertyVolume();
    void EnablePropertyMute();
    void EnablePropertyBalance();
    void EnablePropertyFade();
    void EnablePropertyVolumeLimit();
    void EnablePropertyVolumeMax();
    void EnablePropertyVolumeUnity();
    void EnablePropertyVolumeSteps();
    void EnablePropertyVolumeMilliDbPerStep();
    void EnablePropertyBalanceMax();
    void EnablePropertyFadeMax();
    void EnableActionCharacteristics(CallbackVolume1Characteristics aCallback, void* aPtr);
    void EnableActionSetVolume(CallbackVolume1SetVolume aCallback, void* aPtr);
    void EnableActionVolumeInc(CallbackVolume1VolumeInc aCallback, void* aPtr);
    void EnableActionVolumeDec(CallbackVolume1VolumeDec aCallback, void* aPtr);
    void EnableActionVolume(CallbackVolume1Volume aCallback, void* aPtr);
    void EnableActionSetBalance(CallbackVolume1SetBalance aCallback, void* aPtr);
    void EnableActionBalanceInc(CallbackVolume1BalanceInc aCallback, void* aPtr);
    void EnableActionBalanceDec(CallbackVolume1BalanceDec aCallback, void* aPtr);
    void EnableActionBalance(CallbackVolume1Balance aCallback, void* aPtr);
    void EnableActionSetFade(CallbackVolume1SetFade aCallback, void* aPtr);
    void EnableActionFadeInc(CallbackVolume1FadeInc aCallback, void* aPtr);
    void EnableActionFadeDec(CallbackVolume1FadeDec aCallback, void* aPtr);
    void EnableActionFade(CallbackVolume1Fade aCallback, void* aPtr);
    void EnableActionSetMute(CallbackVolume1SetMute aCallback, void* aPtr);
    void EnableActionMute(CallbackVolume1Mute aCallback, void* aPtr);
    void EnableActionVolumeLimit(CallbackVolume1VolumeLimit aCallback, void* aPtr);
private:
    void DoCharacteristics(IDviInvocation& aInvocation);
    void DoSetVolume(IDviInvocation& aInvocation);
    void DoVolumeInc(IDviInvocation& aInvocation);
    void DoVolumeDec(IDviInvocation& aInvocation);
    void DoVolume(IDviInvocation& aInvocation);
    void DoSetBalance(IDviInvocation& aInvocation);
    void DoBalanceInc(IDviInvocation& aInvocation);
    void DoBalanceDec(IDviInvocation& aInvocation);
    void DoBalance(IDviInvocation& aInvocation);
    void DoSetFade(IDviInvocation& aInvocation);
    void DoFadeInc(IDviInvocation& aInvocation);
    void DoFadeDec(IDviInvocation& aInvocation);
    void DoFade(IDviInvocation& aInvocation);
    void DoSetMute(IDviInvocation& aInvocation);
    void DoMute(IDviInvocation& aInvocation);
    void DoVolumeLimit(IDviInvocation& aInvocation);
private:
    CallbackVolume1Characteristics iCallbackCharacteristics;
    void* iPtrCharacteristics;
    CallbackVolume1SetVolume iCallbackSetVolume;
    void* iPtrSetVolume;
    CallbackVolume1VolumeInc iCallbackVolumeInc;
    void* iPtrVolumeInc;
    CallbackVolume1VolumeDec iCallbackVolumeDec;
    void* iPtrVolumeDec;
    CallbackVolume1Volume iCallbackVolume;
    void* iPtrVolume;
    CallbackVolume1SetBalance iCallbackSetBalance;
    void* iPtrSetBalance;
    CallbackVolume1BalanceInc iCallbackBalanceInc;
    void* iPtrBalanceInc;
    CallbackVolume1BalanceDec iCallbackBalanceDec;
    void* iPtrBalanceDec;
    CallbackVolume1Balance iCallbackBalance;
    void* iPtrBalance;
    CallbackVolume1SetFade iCallbackSetFade;
    void* iPtrSetFade;
    CallbackVolume1FadeInc iCallbackFadeInc;
    void* iPtrFadeInc;
    CallbackVolume1FadeDec iCallbackFadeDec;
    void* iPtrFadeDec;
    CallbackVolume1Fade iCallbackFade;
    void* iPtrFade;
    CallbackVolume1SetMute iCallbackSetMute;
    void* iPtrSetMute;
    CallbackVolume1Mute iCallbackMute;
    void* iPtrMute;
    CallbackVolume1VolumeLimit iCallbackVolumeLimit;
    void* iPtrVolumeLimit;
    PropertyUint* iPropertyVolume;
    PropertyBool* iPropertyMute;
    PropertyInt* iPropertyBalance;
    PropertyInt* iPropertyFade;
    PropertyUint* iPropertyVolumeLimit;
    PropertyUint* iPropertyVolumeMax;
    PropertyUint* iPropertyVolumeUnity;
    PropertyUint* iPropertyVolumeSteps;
    PropertyUint* iPropertyVolumeMilliDbPerStep;
    PropertyUint* iPropertyBalanceMax;
    PropertyUint* iPropertyFadeMax;
};

DvProviderAvOpenhomeOrgVolume1C::DvProviderAvOpenhomeOrgVolume1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "Volume", 1)
{
    iPropertyVolume = NULL;
    iPropertyMute = NULL;
    iPropertyBalance = NULL;
    iPropertyFade = NULL;
    iPropertyVolumeLimit = NULL;
    iPropertyVolumeMax = NULL;
    iPropertyVolumeUnity = NULL;
    iPropertyVolumeSteps = NULL;
    iPropertyVolumeMilliDbPerStep = NULL;
    iPropertyBalanceMax = NULL;
    iPropertyFadeMax = NULL;
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyVolume(TUint aValue)
{
    ASSERT(iPropertyVolume != NULL);
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyVolume(TUint& aValue)
{
    ASSERT(iPropertyVolume != NULL);
    aValue = iPropertyVolume->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyMute(TBool aValue)
{
    ASSERT(iPropertyMute != NULL);
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyMute(TBool& aValue)
{
    ASSERT(iPropertyMute != NULL);
    aValue = iPropertyMute->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyBalance(TInt aValue)
{
    ASSERT(iPropertyBalance != NULL);
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyBalance(TInt& aValue)
{
    ASSERT(iPropertyBalance != NULL);
    aValue = iPropertyBalance->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyFade(TInt aValue)
{
    ASSERT(iPropertyFade != NULL);
    return SetPropertyInt(*iPropertyFade, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyFade(TInt& aValue)
{
    ASSERT(iPropertyFade != NULL);
    aValue = iPropertyFade->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyVolumeLimit(TUint aValue)
{
    ASSERT(iPropertyVolumeLimit != NULL);
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyVolumeLimit(TUint& aValue)
{
    ASSERT(iPropertyVolumeLimit != NULL);
    aValue = iPropertyVolumeLimit->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyVolumeMax(TUint aValue)
{
    ASSERT(iPropertyVolumeMax != NULL);
    return SetPropertyUint(*iPropertyVolumeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyVolumeMax(TUint& aValue)
{
    ASSERT(iPropertyVolumeMax != NULL);
    aValue = iPropertyVolumeMax->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyVolumeUnity(TUint aValue)
{
    ASSERT(iPropertyVolumeUnity != NULL);
    return SetPropertyUint(*iPropertyVolumeUnity, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyVolumeUnity(TUint& aValue)
{
    ASSERT(iPropertyVolumeUnity != NULL);
    aValue = iPropertyVolumeUnity->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyVolumeSteps(TUint aValue)
{
    ASSERT(iPropertyVolumeSteps != NULL);
    return SetPropertyUint(*iPropertyVolumeSteps, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyVolumeSteps(TUint& aValue)
{
    ASSERT(iPropertyVolumeSteps != NULL);
    aValue = iPropertyVolumeSteps->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyVolumeMilliDbPerStep(TUint aValue)
{
    ASSERT(iPropertyVolumeMilliDbPerStep != NULL);
    return SetPropertyUint(*iPropertyVolumeMilliDbPerStep, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyVolumeMilliDbPerStep(TUint& aValue)
{
    ASSERT(iPropertyVolumeMilliDbPerStep != NULL);
    aValue = iPropertyVolumeMilliDbPerStep->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyBalanceMax(TUint aValue)
{
    ASSERT(iPropertyBalanceMax != NULL);
    return SetPropertyUint(*iPropertyBalanceMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyBalanceMax(TUint& aValue)
{
    ASSERT(iPropertyBalanceMax != NULL);
    aValue = iPropertyBalanceMax->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1C::SetPropertyFadeMax(TUint aValue)
{
    ASSERT(iPropertyFadeMax != NULL);
    return SetPropertyUint(*iPropertyFadeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1C::GetPropertyFadeMax(TUint& aValue)
{
    ASSERT(iPropertyFadeMax != NULL);
    aValue = iPropertyFadeMax->Value();
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyVolume()
{
    iPropertyVolume = new PropertyUint(iDvStack.Env(), new ParameterUint("Volume"));
    iService->AddProperty(iPropertyVolume); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyMute()
{
    iPropertyMute = new PropertyBool(iDvStack.Env(), new ParameterBool("Mute"));
    iService->AddProperty(iPropertyMute); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyBalance()
{
    iPropertyBalance = new PropertyInt(iDvStack.Env(), new ParameterInt("Balance"));
    iService->AddProperty(iPropertyBalance); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyFade()
{
    iPropertyFade = new PropertyInt(iDvStack.Env(), new ParameterInt("Fade"));
    iService->AddProperty(iPropertyFade); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyVolumeLimit()
{
    iPropertyVolumeLimit = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeLimit"));
    iService->AddProperty(iPropertyVolumeLimit); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyVolumeMax()
{
    iPropertyVolumeMax = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeMax"));
    iService->AddProperty(iPropertyVolumeMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyVolumeUnity()
{
    iPropertyVolumeUnity = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeUnity"));
    iService->AddProperty(iPropertyVolumeUnity); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyVolumeSteps()
{
    iPropertyVolumeSteps = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeSteps"));
    iService->AddProperty(iPropertyVolumeSteps); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyVolumeMilliDbPerStep()
{
    iPropertyVolumeMilliDbPerStep = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeMilliDbPerStep"));
    iService->AddProperty(iPropertyVolumeMilliDbPerStep); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyBalanceMax()
{
    iPropertyBalanceMax = new PropertyUint(iDvStack.Env(), new ParameterUint("BalanceMax"));
    iService->AddProperty(iPropertyBalanceMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnablePropertyFadeMax()
{
    iPropertyFadeMax = new PropertyUint(iDvStack.Env(), new ParameterUint("FadeMax"));
    iService->AddProperty(iPropertyFadeMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionCharacteristics(CallbackVolume1Characteristics aCallback, void* aPtr)
{
    iCallbackCharacteristics = aCallback;
    iPtrCharacteristics = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Characteristics");
    action->AddOutputParameter(new ParameterRelated("VolumeMax", *iPropertyVolumeMax));
    action->AddOutputParameter(new ParameterRelated("VolumeUnity", *iPropertyVolumeUnity));
    action->AddOutputParameter(new ParameterRelated("VolumeSteps", *iPropertyVolumeSteps));
    action->AddOutputParameter(new ParameterRelated("VolumeMilliDbPerStep", *iPropertyVolumeMilliDbPerStep));
    action->AddOutputParameter(new ParameterRelated("BalanceMax", *iPropertyBalanceMax));
    action->AddOutputParameter(new ParameterRelated("FadeMax", *iPropertyFadeMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoCharacteristics);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionSetVolume(CallbackVolume1SetVolume aCallback, void* aPtr)
{
    iCallbackSetVolume = aCallback;
    iPtrSetVolume = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyVolume));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionVolumeInc(CallbackVolume1VolumeInc aCallback, void* aPtr)
{
    iCallbackVolumeInc = aCallback;
    iPtrVolumeInc = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionVolumeDec(CallbackVolume1VolumeDec aCallback, void* aPtr)
{
    iCallbackVolumeDec = aCallback;
    iPtrVolumeDec = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionVolume(CallbackVolume1Volume aCallback, void* aPtr)
{
    iCallbackVolume = aCallback;
    iPtrVolume = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Volume");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyVolume));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoVolume);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionSetBalance(CallbackVolume1SetBalance aCallback, void* aPtr)
{
    iCallbackSetBalance = aCallback;
    iPtrSetBalance = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBalance");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyBalance));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionBalanceInc(CallbackVolume1BalanceInc aCallback, void* aPtr)
{
    iCallbackBalanceInc = aCallback;
    iPtrBalanceInc = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BalanceInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoBalanceInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionBalanceDec(CallbackVolume1BalanceDec aCallback, void* aPtr)
{
    iCallbackBalanceDec = aCallback;
    iPtrBalanceDec = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BalanceDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoBalanceDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionBalance(CallbackVolume1Balance aCallback, void* aPtr)
{
    iCallbackBalance = aCallback;
    iPtrBalance = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Balance");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyBalance));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoBalance);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionSetFade(CallbackVolume1SetFade aCallback, void* aPtr)
{
    iCallbackSetFade = aCallback;
    iPtrSetFade = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetFade");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyFade));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoSetFade);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionFadeInc(CallbackVolume1FadeInc aCallback, void* aPtr)
{
    iCallbackFadeInc = aCallback;
    iPtrFadeInc = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FadeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoFadeInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionFadeDec(CallbackVolume1FadeDec aCallback, void* aPtr)
{
    iCallbackFadeDec = aCallback;
    iPtrFadeDec = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FadeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoFadeDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionFade(CallbackVolume1Fade aCallback, void* aPtr)
{
    iCallbackFade = aCallback;
    iPtrFade = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Fade");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyFade));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoFade);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionSetMute(CallbackVolume1SetMute aCallback, void* aPtr)
{
    iCallbackSetMute = aCallback;
    iPtrSetMute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyMute));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionMute(CallbackVolume1Mute aCallback, void* aPtr)
{
    iCallbackMute = aCallback;
    iPtrMute = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Mute");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMute));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoMute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::EnableActionVolumeLimit(CallbackVolume1VolumeLimit aCallback, void* aPtr)
{
    iCallbackVolumeLimit = aCallback;
    iPtrVolumeLimit = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyVolumeLimit));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1C::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1C::DoCharacteristics(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t VolumeMax;
    uint32_t VolumeUnity;
    uint32_t VolumeSteps;
    uint32_t VolumeMilliDbPerStep;
    uint32_t BalanceMax;
    uint32_t FadeMax;
    ASSERT(iCallbackCharacteristics != NULL);
    if (0 != iCallbackCharacteristics(iPtrCharacteristics, invocationC, invocationCPtr, &VolumeMax, &VolumeUnity, &VolumeSteps, &VolumeMilliDbPerStep, &BalanceMax, &FadeMax)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respVolumeMax(aInvocation, "VolumeMax");
    DviInvocationResponseUint respVolumeUnity(aInvocation, "VolumeUnity");
    DviInvocationResponseUint respVolumeSteps(aInvocation, "VolumeSteps");
    DviInvocationResponseUint respVolumeMilliDbPerStep(aInvocation, "VolumeMilliDbPerStep");
    DviInvocationResponseUint respBalanceMax(aInvocation, "BalanceMax");
    DviInvocationResponseUint respFadeMax(aInvocation, "FadeMax");
    invocation.StartResponse();
    respVolumeMax.Write(VolumeMax);
    respVolumeUnity.Write(VolumeUnity);
    respVolumeSteps.Write(VolumeSteps);
    respVolumeMilliDbPerStep.Write(VolumeMilliDbPerStep);
    respBalanceMax.Write(BalanceMax);
    respFadeMax.Write(FadeMax);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoSetVolume(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetVolume != NULL);
    if (0 != iCallbackSetVolume(iPtrSetVolume, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoVolumeInc(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackVolumeInc != NULL);
    if (0 != iCallbackVolumeInc(iPtrVolumeInc, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoVolumeDec(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackVolumeDec != NULL);
    if (0 != iCallbackVolumeDec(iPtrVolumeDec, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoVolume(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackVolume != NULL);
    if (0 != iCallbackVolume(iPtrVolume, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoSetBalance(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetBalance != NULL);
    if (0 != iCallbackSetBalance(iPtrSetBalance, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoBalanceInc(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackBalanceInc != NULL);
    if (0 != iCallbackBalanceInc(iPtrBalanceInc, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoBalanceDec(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackBalanceDec != NULL);
    if (0 != iCallbackBalanceDec(iPtrBalanceDec, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoBalance(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t Value;
    ASSERT(iCallbackBalance != NULL);
    if (0 != iCallbackBalance(iPtrBalance, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoSetFade(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetFade != NULL);
    if (0 != iCallbackSetFade(iPtrSetFade, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoFadeInc(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackFadeInc != NULL);
    if (0 != iCallbackFadeInc(iPtrFadeInc, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoFadeDec(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackFadeDec != NULL);
    if (0 != iCallbackFadeDec(iPtrFadeDec, invocationC, invocationCPtr)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoFade(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    int32_t Value;
    ASSERT(iCallbackFade != NULL);
    if (0 != iCallbackFade(iPtrFade, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseInt respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoSetMute(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackSetMute != NULL);
    if (0 != iCallbackSetMute(iPtrSetMute, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoMute(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackMute != NULL);
    if (0 != iCallbackMute(iPtrMute, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgVolume1C::DoVolumeLimit(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackVolumeLimit != NULL);
    if (0 != iCallbackVolumeLimit(iPtrVolumeLimit, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}



THandle STDCALL DvProviderAvOpenhomeOrgVolume1Create(DvDeviceC aDevice)
{
    return new DvProviderAvOpenhomeOrgVolume1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionCharacteristics(THandle aProvider, CallbackVolume1Characteristics aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionCharacteristics(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionSetVolume(THandle aProvider, CallbackVolume1SetVolume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionSetVolume(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionVolumeInc(THandle aProvider, CallbackVolume1VolumeInc aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionVolumeInc(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionVolumeDec(THandle aProvider, CallbackVolume1VolumeDec aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionVolumeDec(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionVolume(THandle aProvider, CallbackVolume1Volume aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionVolume(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionSetBalance(THandle aProvider, CallbackVolume1SetBalance aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionSetBalance(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionBalanceInc(THandle aProvider, CallbackVolume1BalanceInc aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionBalanceInc(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionBalanceDec(THandle aProvider, CallbackVolume1BalanceDec aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionBalanceDec(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionBalance(THandle aProvider, CallbackVolume1Balance aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionBalance(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionSetFade(THandle aProvider, CallbackVolume1SetFade aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionSetFade(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionFadeInc(THandle aProvider, CallbackVolume1FadeInc aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionFadeInc(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionFadeDec(THandle aProvider, CallbackVolume1FadeDec aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionFadeDec(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionFade(THandle aProvider, CallbackVolume1Fade aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionFade(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionSetMute(THandle aProvider, CallbackVolume1SetMute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionSetMute(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionMute(THandle aProvider, CallbackVolume1Mute aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionMute(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnableActionVolumeLimit(THandle aProvider, CallbackVolume1VolumeLimit aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnableActionVolumeLimit(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyVolume(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyVolume(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyVolume(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyVolume(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyMute(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyMute((aValue!=0))? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyMute(THandle aProvider, uint32_t* aValue)
{
    TBool val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyMute(val);
    *aValue = (val? 1 : 0);
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyBalance(THandle aProvider, int32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyBalance(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyBalance(THandle aProvider, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyBalance(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyFade(THandle aProvider, int32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyFade(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyFade(THandle aProvider, int32_t* aValue)
{
    int32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyFade(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeLimit(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyVolumeLimit(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeLimit(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyVolumeLimit(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyVolumeMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyVolumeMax(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeUnity(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyVolumeUnity(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeUnity(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyVolumeUnity(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeSteps(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyVolumeSteps(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeSteps(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyVolumeSteps(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyVolumeMilliDbPerStep(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyVolumeMilliDbPerStep(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyVolumeMilliDbPerStep(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyVolumeMilliDbPerStep(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyBalanceMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyBalanceMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyBalanceMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyBalanceMax(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgVolume1SetPropertyFadeMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->SetPropertyFadeMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1GetPropertyFadeMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->GetPropertyFadeMax(val);
    *aValue = val;
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyVolume(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyVolume();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyMute(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyMute();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyBalance(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyBalance();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyFade(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyFade();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyVolumeLimit(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyVolumeLimit();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyVolumeMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyVolumeMax();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyVolumeUnity(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyVolumeUnity();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyVolumeSteps(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyVolumeSteps();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyVolumeMilliDbPerStep(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyVolumeMilliDbPerStep();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyBalanceMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyBalanceMax();
}

void STDCALL DvProviderAvOpenhomeOrgVolume1EnablePropertyFadeMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgVolume1C*>(aProvider)->EnablePropertyFadeMax();
}

