#include <Std/DvLinnCoUkComponent1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkComponent1Cpp::SetPropertyAmplifierEnabled(bool aValue)
{
    return SetPropertyBool(*iPropertyAmplifierEnabled, aValue);
}

void DvProviderLinnCoUkComponent1Cpp::GetPropertyAmplifierEnabled(bool& aValue)
{
    aValue = iPropertyAmplifierEnabled->Value();
}

bool DvProviderLinnCoUkComponent1Cpp::SetPropertyAmplifierAttenuation(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyAmplifierAttenuation, buf);
}

void DvProviderLinnCoUkComponent1Cpp::GetPropertyAmplifierAttenuation(std::string& aValue)
{
    const Brx& val = iPropertyAmplifierAttenuation->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderLinnCoUkComponent1Cpp::SetPropertyVolumeControlEnabled(bool aValue)
{
    return SetPropertyBool(*iPropertyVolumeControlEnabled, aValue);
}

void DvProviderLinnCoUkComponent1Cpp::GetPropertyVolumeControlEnabled(bool& aValue)
{
    aValue = iPropertyVolumeControlEnabled->Value();
}

bool DvProviderLinnCoUkComponent1Cpp::SetPropertyDigitalAudioOutputRaw(bool aValue)
{
    return SetPropertyBool(*iPropertyDigitalAudioOutputRaw, aValue);
}

void DvProviderLinnCoUkComponent1Cpp::GetPropertyDigitalAudioOutputRaw(bool& aValue)
{
    aValue = iPropertyDigitalAudioOutputRaw->Value();
}

DvProviderLinnCoUkComponent1Cpp::DvProviderLinnCoUkComponent1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Component", 1)
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

void DvProviderLinnCoUkComponent1Cpp::EnableActionAmplifierEnabled()
{
    Zapp::Action* action = new Zapp::Action("AmplifierEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionSetAmplifierEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetAmplifierEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoSetAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionAmplifierAttenuation()
{
    Zapp::Action* action = new Zapp::Action("AmplifierAttenuation");
    action->AddOutputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionSetAmplifierAttenuation()
{
    Zapp::Action* action = new Zapp::Action("SetAmplifierAttenuation");
    action->AddInputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoSetAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionSetVolumeControlEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeControlEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoSetVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionVolumeControlEnabled()
{
    Zapp::Action* action = new Zapp::Action("VolumeControlEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionSetDigitalAudioOutputRaw()
{
    Zapp::Action* action = new Zapp::Action("SetDigitalAudioOutputRaw");
    action->AddInputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoSetDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionDigitalAudioOutputRaw()
{
    Zapp::Action* action = new Zapp::Action("DigitalAudioOutputRaw");
    action->AddOutputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionAmplifierOverTemperature()
{
    Zapp::Action* action = new Zapp::Action("AmplifierOverTemperature");
    action->AddOutputParameter(new ParameterBool("aOverTemperature"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoAmplifierOverTemperature);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionEthernetLinkConnected()
{
    Zapp::Action* action = new Zapp::Action("EthernetLinkConnected");
    action->AddOutputParameter(new ParameterBool("aLinkConnected"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoEthernetLinkConnected);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::EnableActionLocate()
{
    Zapp::Action* action = new Zapp::Action("Locate");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkComponent1Cpp::DoLocate);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkComponent1Cpp::DoAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaEnabled;
    AmplifierEnabled(aVersion, respaEnabled);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraEnabled(aInvocation, "aEnabled");
    respWriteraEnabled.Write(respaEnabled);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoSetAmplifierEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetAmplifierEnabled(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaAttenuation;
    AmplifierAttenuation(aVersion, respaAttenuation);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraAttenuation(aInvocation, "aAttenuation");
    Brn buf_aAttenuation((const TByte*)respaAttenuation.c_str(), (TUint)respaAttenuation.length());
    respWriteraAttenuation.Write(buf_aAttenuation);
    aInvocation.InvocationWriteStringEnd("aAttenuation");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoSetAmplifierAttenuation(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aAttenuation;
    aInvocation.InvocationReadString("aAttenuation", buf_aAttenuation);
    std::string aAttenuation((const char*)buf_aAttenuation.Ptr(), buf_aAttenuation.Bytes());
    aInvocation.InvocationReadEnd();
    SetAmplifierAttenuation(aVersion, aAttenuation);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoSetVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetVolumeControlEnabled(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoVolumeControlEnabled(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaEnabled;
    VolumeControlEnabled(aVersion, respaEnabled);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraEnabled(aInvocation, "aEnabled");
    respWriteraEnabled.Write(respaEnabled);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoSetDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aRaw = aInvocation.InvocationReadBool("aRaw");
    aInvocation.InvocationReadEnd();
    SetDigitalAudioOutputRaw(aVersion, aRaw);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoDigitalAudioOutputRaw(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaRaw;
    DigitalAudioOutputRaw(aVersion, respaRaw);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraRaw(aInvocation, "aRaw");
    respWriteraRaw.Write(respaRaw);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoAmplifierOverTemperature(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaOverTemperature;
    AmplifierOverTemperature(aVersion, respaOverTemperature);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraOverTemperature(aInvocation, "aOverTemperature");
    respWriteraOverTemperature.Write(respaOverTemperature);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoEthernetLinkConnected(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respaLinkConnected;
    EthernetLinkConnected(aVersion, respaLinkConnected);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriteraLinkConnected(aInvocation, "aLinkConnected");
    respWriteraLinkConnected.Write(respaLinkConnected);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::DoLocate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Locate(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkComponent1Cpp::AmplifierEnabled(uint32_t /*aVersion*/, bool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::SetAmplifierEnabled(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::AmplifierAttenuation(uint32_t /*aVersion*/, std::string& /*aaAttenuation*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::SetAmplifierAttenuation(uint32_t /*aVersion*/, const std::string& /*aaAttenuation*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::SetVolumeControlEnabled(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::VolumeControlEnabled(uint32_t /*aVersion*/, bool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::SetDigitalAudioOutputRaw(uint32_t /*aVersion*/, bool /*aaRaw*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::DigitalAudioOutputRaw(uint32_t /*aVersion*/, bool& /*aaRaw*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::AmplifierOverTemperature(uint32_t /*aVersion*/, bool& /*aaOverTemperature*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::EthernetLinkConnected(uint32_t /*aVersion*/, bool& /*aaLinkConnected*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkComponent1Cpp::Locate(uint32_t /*aVersion*/)
{
    ASSERTS();
}

