#include <Core/DvLinnCoUkComponent1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkComponent1::SetPropertyAmplifierEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyAmplifierEnabled, aValue);
}

void DvProviderLinnCoUkComponent1::GetPropertyAmplifierEnabled(TBool& aValue)
{
    aValue = iPropertyAmplifierEnabled->Value();
}

TBool DvProviderLinnCoUkComponent1::SetPropertyAmplifierAttenuation(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAmplifierAttenuation, aValue);
}

void DvProviderLinnCoUkComponent1::GetPropertyAmplifierAttenuation(Brhz& aValue)
{
    aValue.Set(iPropertyAmplifierAttenuation->Value());
}

TBool DvProviderLinnCoUkComponent1::SetPropertyVolumeControlEnabled(TBool aValue)
{
    return SetPropertyBool(*iPropertyVolumeControlEnabled, aValue);
}

void DvProviderLinnCoUkComponent1::GetPropertyVolumeControlEnabled(TBool& aValue)
{
    aValue = iPropertyVolumeControlEnabled->Value();
}

TBool DvProviderLinnCoUkComponent1::SetPropertyDigitalAudioOutputRaw(TBool aValue)
{
    return SetPropertyBool(*iPropertyDigitalAudioOutputRaw, aValue);
}

void DvProviderLinnCoUkComponent1::GetPropertyDigitalAudioOutputRaw(TBool& aValue)
{
    aValue = iPropertyDigitalAudioOutputRaw->Value();
}

DvProviderLinnCoUkComponent1::DvProviderLinnCoUkComponent1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Component", 1)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    iPropertyAmplifierEnabled = new PropertyBool(new ParameterBool("AmplifierEnabled"), empty);
    iService->AddProperty(iPropertyAmplifierEnabled); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"-12dB";
    allowedValues[index++] = (TChar*)"-9dB";
    allowedValues[index++] = (TChar*)"-6dB";
    allowedValues[index++] = (TChar*)"0dB";
    iPropertyAmplifierAttenuation = new PropertyString(new ParameterString("AmplifierAttenuation", allowedValues, 4), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyAmplifierAttenuation); // passes ownership
    iPropertyVolumeControlEnabled = new PropertyBool(new ParameterBool("VolumeControlEnabled"), empty);
    iService->AddProperty(iPropertyVolumeControlEnabled); // passes ownership
    iPropertyDigitalAudioOutputRaw = new PropertyBool(new ParameterBool("DigitalAudioOutputRaw"), empty);
    iService->AddProperty(iPropertyDigitalAudioOutputRaw); // passes ownership
}

void DvProviderLinnCoUkComponent1::EnableActionAmplifierEnabled()
{
    Zapp::Action* action = new Zapp::Action("AmplifierEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionSetAmplifierEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetAmplifierEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoSetAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionAmplifierAttenuation()
{
    Zapp::Action* action = new Zapp::Action("AmplifierAttenuation");
    action->AddOutputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionSetAmplifierAttenuation()
{
    Zapp::Action* action = new Zapp::Action("SetAmplifierAttenuation");
    action->AddInputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoSetAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionSetVolumeControlEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeControlEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoSetVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionVolumeControlEnabled()
{
    Zapp::Action* action = new Zapp::Action("VolumeControlEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionSetDigitalAudioOutputRaw()
{
    Zapp::Action* action = new Zapp::Action("SetDigitalAudioOutputRaw");
    action->AddInputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoSetDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionDigitalAudioOutputRaw()
{
    Zapp::Action* action = new Zapp::Action("DigitalAudioOutputRaw");
    action->AddOutputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionAmplifierOverTemperature()
{
    Zapp::Action* action = new Zapp::Action("AmplifierOverTemperature");
    action->AddOutputParameter(new ParameterBool("aOverTemperature"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoAmplifierOverTemperature);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionEthernetLinkConnected()
{
    Zapp::Action* action = new Zapp::Action("EthernetLinkConnected");
    action->AddOutputParameter(new ParameterBool("aLinkConnected"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoEthernetLinkConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::EnableActionLocate()
{
    Zapp::Action* action = new Zapp::Action("Locate");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvProviderLinnCoUkComponent1::DoLocate);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1::DoAmplifierEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    AmplifierEnabled(resp, aVersion, respaEnabled);
}

void DvProviderLinnCoUkComponent1::DoSetAmplifierEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetAmplifierEnabled(resp, aVersion, aEnabled);
}

void DvProviderLinnCoUkComponent1::DoAmplifierAttenuation(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaAttenuation(aInvocation, "aAttenuation");
    AmplifierAttenuation(resp, aVersion, respaAttenuation);
}

void DvProviderLinnCoUkComponent1::DoSetAmplifierAttenuation(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aAttenuation;
    aInvocation.InvocationReadString("aAttenuation", aAttenuation);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetAmplifierAttenuation(resp, aVersion, aAttenuation);
}

void DvProviderLinnCoUkComponent1::DoSetVolumeControlEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetVolumeControlEnabled(resp, aVersion, aEnabled);
}

void DvProviderLinnCoUkComponent1::DoVolumeControlEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaEnabled(aInvocation, "aEnabled");
    VolumeControlEnabled(resp, aVersion, respaEnabled);
}

void DvProviderLinnCoUkComponent1::DoSetDigitalAudioOutputRaw(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool aRaw = aInvocation.InvocationReadBool("aRaw");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetDigitalAudioOutputRaw(resp, aVersion, aRaw);
}

void DvProviderLinnCoUkComponent1::DoDigitalAudioOutputRaw(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaRaw(aInvocation, "aRaw");
    DigitalAudioOutputRaw(resp, aVersion, respaRaw);
}

void DvProviderLinnCoUkComponent1::DoAmplifierOverTemperature(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaOverTemperature(aInvocation, "aOverTemperature");
    AmplifierOverTemperature(resp, aVersion, respaOverTemperature);
}

void DvProviderLinnCoUkComponent1::DoEthernetLinkConnected(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respaLinkConnected(aInvocation, "aLinkConnected");
    EthernetLinkConnected(resp, aVersion, respaLinkConnected);
}

void DvProviderLinnCoUkComponent1::DoLocate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Locate(resp, aVersion);
}

void DvProviderLinnCoUkComponent1::AmplifierEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::SetAmplifierEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::AmplifierAttenuation(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaAttenuation*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::SetAmplifierAttenuation(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaAttenuation*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::SetVolumeControlEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::VolumeControlEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::SetDigitalAudioOutputRaw(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aaRaw*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::DigitalAudioOutputRaw(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaRaw*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::AmplifierOverTemperature(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaOverTemperature*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::EthernetLinkConnected(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aaLinkConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1::Locate(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

