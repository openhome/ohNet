#include "DvAvOpenhomeOrgVolume1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolume(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolume, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolume(uint32_t& aValue)
{
    aValue = iPropertyVolume->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyMute(bool aValue)
{
    return SetPropertyBool(*iPropertyMute, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyMute(bool& aValue)
{
    aValue = iPropertyMute->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyBalance(int32_t aValue)
{
    return SetPropertyInt(*iPropertyBalance, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyBalance(int32_t& aValue)
{
    aValue = iPropertyBalance->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyFade(int32_t aValue)
{
    return SetPropertyInt(*iPropertyFade, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyFade(int32_t& aValue)
{
    aValue = iPropertyFade->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeLimit(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolumeLimit, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeLimit(uint32_t& aValue)
{
    aValue = iPropertyVolumeLimit->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolumeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeMax(uint32_t& aValue)
{
    aValue = iPropertyVolumeMax->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeUnity(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolumeUnity, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeUnity(uint32_t& aValue)
{
    aValue = iPropertyVolumeUnity->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeSteps(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolumeSteps, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeSteps(uint32_t& aValue)
{
    aValue = iPropertyVolumeSteps->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyVolumeMilliDbPerStep(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyVolumeMilliDbPerStep, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyVolumeMilliDbPerStep(uint32_t& aValue)
{
    aValue = iPropertyVolumeMilliDbPerStep->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyBalanceMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyBalanceMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyBalanceMax(uint32_t& aValue)
{
    aValue = iPropertyBalanceMax->Value();
}

bool DvProviderAvOpenhomeOrgVolume1Cpp::SetPropertyFadeMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyFadeMax, aValue);
}

void DvProviderAvOpenhomeOrgVolume1Cpp::GetPropertyFadeMax(uint32_t& aValue)
{
    aValue = iPropertyFadeMax->Value();
}

DvProviderAvOpenhomeOrgVolume1Cpp::DvProviderAvOpenhomeOrgVolume1Cpp(DvDeviceStd& aDevice)
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

void DvProviderAvOpenhomeOrgVolume1Cpp::DoCharacteristics(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respVolumeMax;
    uint32_t respVolumeUnity;
    uint32_t respVolumeSteps;
    uint32_t respVolumeMilliDbPerStep;
    uint32_t respBalanceMax;
    uint32_t respFadeMax;
    Characteristics(aVersion, respVolumeMax, respVolumeUnity, respVolumeSteps, respVolumeMilliDbPerStep, respBalanceMax, respFadeMax);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterVolumeMax(aInvocation, "VolumeMax");
    respWriterVolumeMax.Write(respVolumeMax);
    InvocationResponseUint respWriterVolumeUnity(aInvocation, "VolumeUnity");
    respWriterVolumeUnity.Write(respVolumeUnity);
    InvocationResponseUint respWriterVolumeSteps(aInvocation, "VolumeSteps");
    respWriterVolumeSteps.Write(respVolumeSteps);
    InvocationResponseUint respWriterVolumeMilliDbPerStep(aInvocation, "VolumeMilliDbPerStep");
    respWriterVolumeMilliDbPerStep.Write(respVolumeMilliDbPerStep);
    InvocationResponseUint respWriterBalanceMax(aInvocation, "BalanceMax");
    respWriterBalanceMax.Write(respBalanceMax);
    InvocationResponseUint respWriterFadeMax(aInvocation, "FadeMax");
    respWriterFadeMax.Write(respFadeMax);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    SetVolume(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    VolumeInc(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    VolumeDec(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolume(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    Volume(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    SetBalance(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoBalanceInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    BalanceInc(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoBalanceDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    BalanceDec(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoBalance(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respValue;
    Balance(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetFade(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    SetFade(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoFadeInc(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    FadeInc(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoFadeDec(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    FadeDec(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoFade(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    int32_t respValue;
    Fade(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseInt respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoSetMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    SetMute(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoMute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValue;
    Mute(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::DoVolumeLimit(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    VolumeLimit(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Characteristics(uint32_t /*aVersion*/, uint32_t& /*aVolumeMax*/, uint32_t& /*aVolumeUnity*/, uint32_t& /*aVolumeSteps*/, uint32_t& /*aVolumeMilliDbPerStep*/, uint32_t& /*aBalanceMax*/, uint32_t& /*aFadeMax*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetVolume(uint32_t /*aVersion*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::VolumeInc(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::VolumeDec(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Volume(uint32_t /*aVersion*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetBalance(uint32_t /*aVersion*/, int32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::BalanceInc(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::BalanceDec(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Balance(uint32_t /*aVersion*/, int32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetFade(uint32_t /*aVersion*/, int32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::FadeInc(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::FadeDec(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Fade(uint32_t /*aVersion*/, int32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::SetMute(uint32_t /*aVersion*/, bool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::Mute(uint32_t /*aVersion*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgVolume1Cpp::VolumeLimit(uint32_t /*aVersion*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

