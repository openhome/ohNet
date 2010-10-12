#include <Std/DvLinnCoUkComponent1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkComponent1Cpp::SetPropertyAmplifierEnabled(bool aValue)
{
    SetPropertyBool(*iPropertyAmplifierEnabled, aValue);
}

void DvServiceLinnCoUkComponent1Cpp::GetPropertyAmplifierEnabled(bool& aValue)
{
    aValue = iPropertyAmplifierEnabled->Value();
}

void DvServiceLinnCoUkComponent1Cpp::SetPropertyAmplifierAttenuation(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyAmplifierAttenuation, buf);
}

void DvServiceLinnCoUkComponent1Cpp::GetPropertyAmplifierAttenuation(std::string& aValue)
{
    const Brx& val = iPropertyAmplifierAttenuation->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkComponent1Cpp::SetPropertyVolumeControlEnabled(bool aValue)
{
    SetPropertyBool(*iPropertyVolumeControlEnabled, aValue);
}

void DvServiceLinnCoUkComponent1Cpp::GetPropertyVolumeControlEnabled(bool& aValue)
{
    aValue = iPropertyVolumeControlEnabled->Value();
}

void DvServiceLinnCoUkComponent1Cpp::SetPropertyDigitalAudioOutputRaw(bool aValue)
{
    SetPropertyBool(*iPropertyDigitalAudioOutputRaw, aValue);
}

void DvServiceLinnCoUkComponent1Cpp::GetPropertyDigitalAudioOutputRaw(bool& aValue)
{
    aValue = iPropertyDigitalAudioOutputRaw->Value();
}

DvServiceLinnCoUkComponent1Cpp::DvServiceLinnCoUkComponent1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Component", 1)
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

void DvServiceLinnCoUkComponent1Cpp::EnableActionAmplifierEnabled()
{
    Zapp::Action* action = new Zapp::Action("AmplifierEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionSetAmplifierEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetAmplifierEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyAmplifierEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoSetAmplifierEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionAmplifierAttenuation()
{
    Zapp::Action* action = new Zapp::Action("AmplifierAttenuation");
    action->AddOutputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionSetAmplifierAttenuation()
{
    Zapp::Action* action = new Zapp::Action("SetAmplifierAttenuation");
    action->AddInputParameter(new ParameterRelated("aAttenuation", *iPropertyAmplifierAttenuation));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoSetAmplifierAttenuation);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionSetVolumeControlEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetVolumeControlEnabled");
    action->AddInputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoSetVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionVolumeControlEnabled()
{
    Zapp::Action* action = new Zapp::Action("VolumeControlEnabled");
    action->AddOutputParameter(new ParameterRelated("aEnabled", *iPropertyVolumeControlEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoVolumeControlEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionSetDigitalAudioOutputRaw()
{
    Zapp::Action* action = new Zapp::Action("SetDigitalAudioOutputRaw");
    action->AddInputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoSetDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionDigitalAudioOutputRaw()
{
    Zapp::Action* action = new Zapp::Action("DigitalAudioOutputRaw");
    action->AddOutputParameter(new ParameterRelated("aRaw", *iPropertyDigitalAudioOutputRaw));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoDigitalAudioOutputRaw);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionAmplifierOverTemperature()
{
    Zapp::Action* action = new Zapp::Action("AmplifierOverTemperature");
    action->AddOutputParameter(new ParameterBool("aOverTemperature"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoAmplifierOverTemperature);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionEthernetLinkConnected()
{
    Zapp::Action* action = new Zapp::Action("EthernetLinkConnected");
    action->AddOutputParameter(new ParameterBool("aLinkConnected"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoEthernetLinkConnected);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::EnableActionLocate()
{
    Zapp::Action* action = new Zapp::Action("Locate");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkComponent1Cpp::DoLocate);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkComponent1Cpp::DoAmplifierEnabled(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkComponent1Cpp::DoSetAmplifierEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetAmplifierEnabled(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkComponent1Cpp::DoAmplifierAttenuation(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaAttenuation;
    AmplifierAttenuation(aVersion, respaAttenuation);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraAttenuation(aInvocation, "aAttenuation");
    Brn buf_aAttenuation((const TByte*)respaAttenuation.c_str(), respaAttenuation.length());
    respWriteraAttenuation.Write(buf_aAttenuation);
    aInvocation.InvocationWriteStringEnd("aAttenuation");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkComponent1Cpp::DoSetAmplifierAttenuation(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkComponent1Cpp::DoSetVolumeControlEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aEnabled = aInvocation.InvocationReadBool("aEnabled");
    aInvocation.InvocationReadEnd();
    SetVolumeControlEnabled(aVersion, aEnabled);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkComponent1Cpp::DoVolumeControlEnabled(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkComponent1Cpp::DoSetDigitalAudioOutputRaw(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    bool aRaw = aInvocation.InvocationReadBool("aRaw");
    aInvocation.InvocationReadEnd();
    SetDigitalAudioOutputRaw(aVersion, aRaw);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkComponent1Cpp::DoDigitalAudioOutputRaw(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkComponent1Cpp::DoAmplifierOverTemperature(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkComponent1Cpp::DoEthernetLinkConnected(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkComponent1Cpp::DoLocate(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Locate(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkComponent1Cpp::AmplifierEnabled(uint32_t /*aVersion*/, bool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::SetAmplifierEnabled(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::AmplifierAttenuation(uint32_t /*aVersion*/, std::string& /*aaAttenuation*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::SetAmplifierAttenuation(uint32_t /*aVersion*/, const std::string& /*aaAttenuation*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::SetVolumeControlEnabled(uint32_t /*aVersion*/, bool /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::VolumeControlEnabled(uint32_t /*aVersion*/, bool& /*aaEnabled*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::SetDigitalAudioOutputRaw(uint32_t /*aVersion*/, bool /*aaRaw*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::DigitalAudioOutputRaw(uint32_t /*aVersion*/, bool& /*aaRaw*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::AmplifierOverTemperature(uint32_t /*aVersion*/, bool& /*aaOverTemperature*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::EthernetLinkConnected(uint32_t /*aVersion*/, bool& /*aaLinkConnected*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkComponent1Cpp::Locate(uint32_t /*aVersion*/)
{
    ASSERTS();
}

