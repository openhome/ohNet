#include "DvAvOpenhomeOrgVolume1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyVolume(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyVolume(TUint& aValue)
{
    aValue = iPropertyVolume->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyMute(TBool aValue)
{
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyMute(TBool& aValue)
{
    aValue = iPropertyMute->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyBalance(TInt aValue)
{
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyBalance(TInt& aValue)
{
    aValue = iPropertyBalance->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyFade(TInt aValue)
{
    return SetPropertyInt(*iPropertyFade, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyFade(TInt& aValue)
{
    aValue = iPropertyFade->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyVolumeLimit(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyVolumeLimit(TUint& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyVolumeMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyVolumeMax(TUint& aValue)
{
    aValue = iPropertyVolumeMax->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyVolumeUnity(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeUnity, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyVolumeUnity(TUint& aValue)
{
    aValue = iPropertyVolumeUnity->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyVolumeSteps(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeSteps, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyVolumeSteps(TUint& aValue)
{
    aValue = iPropertyVolumeSteps->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyVolumeMilliDbPerStep(TUint aValue)
{
    return SetPropertyUint(*iPropertyVolumeMilliDbPerStep, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyVolumeMilliDbPerStep(TUint& aValue)
{
    aValue = iPropertyVolumeMilliDbPerStep->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyBalanceMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyBalanceMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyBalanceMax(TUint& aValue)
{
    aValue = iPropertyBalanceMax->Value();
}

TBool DvProviderAvOpenhomeOrgVolume1::SetPropertyFadeMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyFadeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1::GetPropertyFadeMax(TUint& aValue)
{
    aValue = iPropertyFadeMax->Value();
}

DvProviderAvOpenhomeOrgVolume1::DvProviderAvOpenhomeOrgVolume1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Volume", 1)
{
    
    iPropertyVolume = new PropertyUint(new ParameterUint("Volume"));
    iService->AddProperty(iPropertyVolume); // passes ownership
    iPropertyMute = new PropertyBool(new ParameterBool("Mute"));
    iService->AddProperty(iPropertyMute); // passes ownership
    iPropertyBalance = new PropertyInt(new ParameterInt("Balance"));
    iService->AddProperty(iPropertyBalance); // passes ownership
    iPropertyFade = new PropertyInt(new ParameterInt("Fade"));
    iService->AddProperty(iPropertyFade); // passes ownership
    iPropertyVolumeLimit = new PropertyUint(new ParameterUint("VolumeLimit"));
    iService->AddProperty(iPropertyVolumeLimit); // passes ownership
    iPropertyVolumeMax = new PropertyUint(new ParameterUint("VolumeMax"));
    iService->AddProperty(iPropertyVolumeMax); // passes ownership
    iPropertyVolumeUnity = new PropertyUint(new ParameterUint("VolumeUnity"));
    iService->AddProperty(iPropertyVolumeUnity); // passes ownership
    iPropertyVolumeSteps = new PropertyUint(new ParameterUint("VolumeSteps"));
    iService->AddProperty(iPropertyVolumeSteps); // passes ownership
    iPropertyVolumeMilliDbPerStep = new PropertyUint(new ParameterUint("VolumeMilliDbPerStep"));
    iService->AddProperty(iPropertyVolumeMilliDbPerStep); // passes ownership
    iPropertyBalanceMax = new PropertyUint(new ParameterUint("BalanceMax"));
    iService->AddProperty(iPropertyBalanceMax); // passes ownership
    iPropertyFadeMax = new PropertyUint(new ParameterUint("FadeMax"));
    iService->AddProperty(iPropertyFadeMax); // passes ownership
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionCharacteristics()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Characteristics");
    action->AddOutputParameter(new ParameterRelated("VolumeMax", *iPropertyVolumeMax));
    action->AddOutputParameter(new ParameterRelated("VolumeUnity", *iPropertyVolumeUnity));
    action->AddOutputParameter(new ParameterRelated("VolumeSteps", *iPropertyVolumeSteps));
    action->AddOutputParameter(new ParameterRelated("VolumeMilliDbPerStep", *iPropertyVolumeMilliDbPerStep));
    action->AddOutputParameter(new ParameterRelated("BalanceMax", *iPropertyBalanceMax));
    action->AddOutputParameter(new ParameterRelated("FadeMax", *iPropertyFadeMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoCharacteristics);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionSetVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetVolume");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyVolume));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoSetVolume);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionVolumeInc()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoVolumeInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionVolumeDec()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoVolumeDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionVolume()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Volume");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyVolume));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoVolume);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionSetBalance()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetBalance");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyBalance));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoSetBalance);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionBalanceInc()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BalanceInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoBalanceInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionBalanceDec()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BalanceDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoBalanceDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionBalance()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Balance");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyBalance));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoBalance);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionSetFade()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetFade");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyFade));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoSetFade);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionFadeInc()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FadeInc");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoFadeInc);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionFadeDec()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FadeDec");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoFadeDec);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionFade()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Fade");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyFade));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoFade);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionSetMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetMute");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyMute));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoSetMute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionMute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Mute");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMute));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoMute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::EnableActionVolumeLimit()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("VolumeLimit");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyVolumeLimit));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgVolume1::DoVolumeLimit);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgVolume1::DoCharacteristics(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respVolumeMax(aInvocation, "VolumeMax");
    DviInvocationResponseUint respVolumeUnity(aInvocation, "VolumeUnity");
    DviInvocationResponseUint respVolumeSteps(aInvocation, "VolumeSteps");
    DviInvocationResponseUint respVolumeMilliDbPerStep(aInvocation, "VolumeMilliDbPerStep");
    DviInvocationResponseUint respBalanceMax(aInvocation, "BalanceMax");
    DviInvocationResponseUint respFadeMax(aInvocation, "FadeMax");
    Characteristics(invocation, aVersion, respVolumeMax, respVolumeUnity, respVolumeSteps, respVolumeMilliDbPerStep, respBalanceMax, respFadeMax);
}

void DvProviderAvOpenhomeOrgVolume1::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetVolume(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgVolume1::DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    VolumeInc(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgVolume1::DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    VolumeDec(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgVolume1::DoVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    Volume(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgVolume1::DoSetBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetBalance(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgVolume1::DoBalanceInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    BalanceInc(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgVolume1::DoBalanceDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    BalanceDec(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgVolume1::DoBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respValue(aInvocation, "Value");
    Balance(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgVolume1::DoSetFade(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetFade(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgVolume1::DoFadeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    FadeInc(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgVolume1::DoFadeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    FadeDec(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgVolume1::DoFade(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseInt respValue(aInvocation, "Value");
    Fade(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgVolume1::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetMute(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgVolume1::DoMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Mute(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgVolume1::DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    VolumeLimit(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgVolume1::Characteristics(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aVolumeMax*/, IDvInvocationResponseUint& /*aVolumeUnity*/, IDvInvocationResponseUint& /*aVolumeSteps*/, IDvInvocationResponseUint& /*aVolumeMilliDbPerStep*/, IDvInvocationResponseUint& /*aBalanceMax*/, IDvInvocationResponseUint& /*aFadeMax*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::SetVolume(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::VolumeInc(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::VolumeDec(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::Volume(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::SetBalance(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TInt /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::BalanceInc(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::BalanceDec(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::Balance(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseInt& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::SetFade(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TInt /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::FadeInc(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::FadeDec(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::Fade(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseInt& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::SetMute(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::Mute(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1::VolumeLimit(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

