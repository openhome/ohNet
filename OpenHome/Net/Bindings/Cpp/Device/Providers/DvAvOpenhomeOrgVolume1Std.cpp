#include "DvAvOpenhomeOrgVolume1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolume(uint32_t aValue)
{
    ASSERT(iPropertyVolume != NULL);
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolume(uint32_t& aValue)
{
    ASSERT(iPropertyVolume != NULL);
    aValue = iPropertyVolume->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyMute(bool aValue)
{
    ASSERT(iPropertyMute != NULL);
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyMute(bool& aValue)
{
    ASSERT(iPropertyMute != NULL);
    aValue = iPropertyMute->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyBalance(int32_t aValue)
{
    ASSERT(iPropertyBalance != NULL);
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyBalance(int32_t& aValue)
{
    ASSERT(iPropertyBalance != NULL);
    aValue = iPropertyBalance->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyFade(int32_t aValue)
{
    ASSERT(iPropertyFade != NULL);
    return SetPropertyInt(*iPropertyFade, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyFade(int32_t& aValue)
{
    ASSERT(iPropertyFade != NULL);
    aValue = iPropertyFade->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeLimit(uint32_t aValue)
{
    ASSERT(iPropertyVolumeLimit != NULL);
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeLimit(uint32_t& aValue)
{
    ASSERT(iPropertyVolumeLimit != NULL);
    aValue = iPropertyVolumeLimit->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeMax(uint32_t aValue)
{
    ASSERT(iPropertyVolumeMax != NULL);
    return SetPropertyUint(*iPropertyVolumeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeMax(uint32_t& aValue)
{
    ASSERT(iPropertyVolumeMax != NULL);
    aValue = iPropertyVolumeMax->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeUnity(uint32_t aValue)
{
    ASSERT(iPropertyVolumeUnity != NULL);
    return SetPropertyUint(*iPropertyVolumeUnity, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeUnity(uint32_t& aValue)
{
    ASSERT(iPropertyVolumeUnity != NULL);
    aValue = iPropertyVolumeUnity->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeSteps(uint32_t aValue)
{
    ASSERT(iPropertyVolumeSteps != NULL);
    return SetPropertyUint(*iPropertyVolumeSteps, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeSteps(uint32_t& aValue)
{
    ASSERT(iPropertyVolumeSteps != NULL);
    aValue = iPropertyVolumeSteps->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeMilliDbPerStep(uint32_t aValue)
{
    ASSERT(iPropertyVolumeMilliDbPerStep != NULL);
    return SetPropertyUint(*iPropertyVolumeMilliDbPerStep, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeMilliDbPerStep(uint32_t& aValue)
{
    ASSERT(iPropertyVolumeMilliDbPerStep != NULL);
    aValue = iPropertyVolumeMilliDbPerStep->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyBalanceMax(uint32_t aValue)
{
    ASSERT(iPropertyBalanceMax != NULL);
    return SetPropertyUint(*iPropertyBalanceMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyBalanceMax(uint32_t& aValue)
{
    ASSERT(iPropertyBalanceMax != NULL);
    aValue = iPropertyBalanceMax->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyFadeMax(uint32_t aValue)
{
    ASSERT(iPropertyFadeMax != NULL);
    return SetPropertyUint(*iPropertyFadeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyFadeMax(uint32_t& aValue)
{
    ASSERT(iPropertyFadeMax != NULL);
    aValue = iPropertyFadeMax->Value();
}

DvProviderAvOpenhomeOrgVolume1Cpp::DvProviderAvOpenhomeOrgVolume1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Volume", 1)
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

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyVolume()
{
    iPropertyVolume = new PropertyUint(iDvStack.Env(), new ParameterUint("Volume"));
    iService->AddProperty(iPropertyVolume); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyMute()
{
    iPropertyMute = new PropertyBool(iDvStack.Env(), new ParameterBool("Mute"));
    iService->AddProperty(iPropertyMute); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyBalance()
{
    iPropertyBalance = new PropertyInt(iDvStack.Env(), new ParameterInt("Balance"));
    iService->AddProperty(iPropertyBalance); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyFade()
{
    iPropertyFade = new PropertyInt(iDvStack.Env(), new ParameterInt("Fade"));
    iService->AddProperty(iPropertyFade); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyVolumeLimit()
{
    iPropertyVolumeLimit = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeLimit"));
    iService->AddProperty(iPropertyVolumeLimit); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyVolumeMax()
{
    iPropertyVolumeMax = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeMax"));
    iService->AddProperty(iPropertyVolumeMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyVolumeUnity()
{
    iPropertyVolumeUnity = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeUnity"));
    iService->AddProperty(iPropertyVolumeUnity); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyVolumeSteps()
{
    iPropertyVolumeSteps = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeSteps"));
    iService->AddProperty(iPropertyVolumeSteps); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyVolumeMilliDbPerStep()
{
    iPropertyVolumeMilliDbPerStep = new PropertyUint(iDvStack.Env(), new ParameterUint("VolumeMilliDbPerStep"));
    iService->AddProperty(iPropertyVolumeMilliDbPerStep); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyBalanceMax()
{
    iPropertyBalanceMax = new PropertyUint(iDvStack.Env(), new ParameterUint("BalanceMax"));
    iService->AddProperty(iPropertyBalanceMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnablePropertyFadeMax()
{
    iPropertyFadeMax = new PropertyUint(iDvStack.Env(), new ParameterUint("FadeMax"));
    iService->AddProperty(iPropertyFadeMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionCharacteristics()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Characteristics");
    action->AddOutputParameter(new ParameterRelated("VolumeMax", *iPropertyVolumeMax));
    action->AddOutputParameter(new ParameterRelated("VolumeUnity", *iPropertyVolumeUnity));
    action->AddOutputParameter(new ParameterRelated("VolumeSteps", *iPropertyVolumeSteps));
    action->AddOutputParameter(new ParameterRelated("VolumeMilliDbPerStep", *iPropertyVolumeMilliDbPerStep));
    action->AddOutputParameter(new ParameterRelated("BalanceMax", *iPropertyBalanceMax));
    action->AddOutputParameter(new ParameterRelated("FadeMax", *iPropertyFadeMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoCharacteristics);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionSetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyVolume));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionVolumeInc()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionVolumeDec()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Volume");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyVolume));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoVolume);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionSetBalance()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBalance");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyBalance));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionBalanceInc()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BalanceInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoBalanceInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionBalanceDec()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BalanceDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoBalanceDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionBalance()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Balance");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyBalance));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoBalance);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionSetFade()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetFade");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyFade));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoSetFade);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionFadeInc()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FadeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoFadeInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionFadeDec()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FadeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoFadeDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionFade()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Fade");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyFade));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoFade);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionSetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyMute));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Mute");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMute));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoMute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::EnableActionVolumeLimit()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyVolumeLimit));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoCharacteristics(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respVolumeMax;
    uint32_t respVolumeUnity;
    uint32_t respVolumeSteps;
    uint32_t respVolumeMilliDbPerStep;
    uint32_t respBalanceMax;
    uint32_t respFadeMax;
    DvInvocationStd invocation(aInvocation);
    Characteristics(invocation, respVolumeMax, respVolumeUnity, respVolumeSteps, respVolumeMilliDbPerStep, respBalanceMax, respFadeMax);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterVolumeMax(aInvocation, "VolumeMax");
    respWriterVolumeMax.Write(respVolumeMax);
    DviInvocationResponseUint respWriterVolumeUnity(aInvocation, "VolumeUnity");
    respWriterVolumeUnity.Write(respVolumeUnity);
    DviInvocationResponseUint respWriterVolumeSteps(aInvocation, "VolumeSteps");
    respWriterVolumeSteps.Write(respVolumeSteps);
    DviInvocationResponseUint respWriterVolumeMilliDbPerStep(aInvocation, "VolumeMilliDbPerStep");
    respWriterVolumeMilliDbPerStep.Write(respVolumeMilliDbPerStep);
    DviInvocationResponseUint respWriterBalanceMax(aInvocation, "BalanceMax");
    respWriterBalanceMax.Write(respBalanceMax);
    DviInvocationResponseUint respWriterFadeMax(aInvocation, "FadeMax");
    respWriterFadeMax.Write(respFadeMax);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetVolume(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetVolume(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeInc(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    VolumeInc(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeDec(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    VolumeDec(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolume(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    Volume(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetBalance(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetBalance(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoBalanceInc(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    BalanceInc(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoBalanceDec(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    BalanceDec(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoBalance(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respValue;
    DvInvocationStd invocation(aInvocation);
    Balance(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetFade(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetFade(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoFadeInc(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    FadeInc(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoFadeDec(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    FadeDec(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoFade(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respValue;
    DvInvocationStd invocation(aInvocation);
    Fade(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseInt respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetMute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    bool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetMute(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoMute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValue;
    DvInvocationStd invocation(aInvocation);
    Mute(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeLimit(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    VolumeLimit(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Characteristics(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aVolumeMax*/, uint32_t& /*aVolumeUnity*/, uint32_t& /*aVolumeSteps*/, uint32_t& /*aVolumeMilliDbPerStep*/, uint32_t& /*aBalanceMax*/, uint32_t& /*aFadeMax*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetVolume(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::VolumeInc(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::VolumeDec(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Volume(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetBalance(IDvInvocationStd& /*aInvocation*/, int32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::BalanceInc(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::BalanceDec(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Balance(IDvInvocationStd& /*aInvocation*/, int32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetFade(IDvInvocationStd& /*aInvocation*/, int32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::FadeInc(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::FadeDec(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Fade(IDvInvocationStd& /*aInvocation*/, int32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetMute(IDvInvocationStd& /*aInvocation*/, bool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Mute(IDvInvocationStd& /*aInvocation*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::VolumeLimit(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

