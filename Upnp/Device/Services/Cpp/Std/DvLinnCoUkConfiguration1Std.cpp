#include <Std/DvLinnCoUkConfiguration1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkConfiguration1Cpp::SetPropertyConfigurationXml(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyConfigurationXml, buf);
}

void DvServiceLinnCoUkConfiguration1Cpp::GetPropertyConfigurationXml(std::string& aValue)
{
    const Brx& val = iPropertyConfigurationXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceLinnCoUkConfiguration1Cpp::SetPropertyParameterXml(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyParameterXml, buf);
}

void DvServiceLinnCoUkConfiguration1Cpp::GetPropertyParameterXml(std::string& aValue)
{
    const Brx& val = iPropertyParameterXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceLinnCoUkConfiguration1Cpp::DvServiceLinnCoUkConfiguration1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Configuration", 1)
{
    Functor empty;
    iPropertyConfigurationXml = new PropertyString(new ParameterString("ConfigurationXml"), empty);
    iService->AddProperty(iPropertyConfigurationXml); // passes ownership
    iPropertyParameterXml = new PropertyString(new ParameterString("ParameterXml"), empty);
    iService->AddProperty(iPropertyParameterXml); // passes ownership
}

void DvServiceLinnCoUkConfiguration1Cpp::EnableActionConfigurationXml()
{
    Zapp::Action* action = new Zapp::Action("ConfigurationXml");
    action->AddOutputParameter(new ParameterRelated("aConfigurationXml", *iPropertyConfigurationXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkConfiguration1Cpp::DoConfigurationXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkConfiguration1Cpp::EnableActionParameterXml()
{
    Zapp::Action* action = new Zapp::Action("ParameterXml");
    action->AddOutputParameter(new ParameterRelated("aParameterXml", *iPropertyParameterXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkConfiguration1Cpp::DoParameterXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkConfiguration1Cpp::EnableActionSetParameter()
{
    Zapp::Action* action = new Zapp::Action("SetParameter");
    action->AddInputParameter(new ParameterString("aTarget"));
    action->AddInputParameter(new ParameterString("aName"));
    action->AddInputParameter(new ParameterString("aValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkConfiguration1Cpp::DoSetParameter);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkConfiguration1Cpp::DoConfigurationXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaConfigurationXml;
    ConfigurationXml(aVersion, respaConfigurationXml);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraConfigurationXml(aInvocation, "aConfigurationXml");
    Brn buf_aConfigurationXml((const TByte*)respaConfigurationXml.c_str(), respaConfigurationXml.length());
    respWriteraConfigurationXml.Write(buf_aConfigurationXml);
    aInvocation.InvocationWriteStringEnd("aConfigurationXml");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkConfiguration1Cpp::DoParameterXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaParameterXml;
    ParameterXml(aVersion, respaParameterXml);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraParameterXml(aInvocation, "aParameterXml");
    Brn buf_aParameterXml((const TByte*)respaParameterXml.c_str(), respaParameterXml.length());
    respWriteraParameterXml.Write(buf_aParameterXml);
    aInvocation.InvocationWriteStringEnd("aParameterXml");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkConfiguration1Cpp::DoSetParameter(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aTarget;
    aInvocation.InvocationReadString("aTarget", buf_aTarget);
    std::string aTarget((const char*)buf_aTarget.Ptr(), buf_aTarget.Bytes());
    Brhz buf_aName;
    aInvocation.InvocationReadString("aName", buf_aName);
    std::string aName((const char*)buf_aName.Ptr(), buf_aName.Bytes());
    Brhz buf_aValue;
    aInvocation.InvocationReadString("aValue", buf_aValue);
    std::string aValue((const char*)buf_aValue.Ptr(), buf_aValue.Bytes());
    aInvocation.InvocationReadEnd();
    SetParameter(aVersion, aTarget, aName, aValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkConfiguration1Cpp::ConfigurationXml(uint32_t /*aVersion*/, std::string& /*aaConfigurationXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkConfiguration1Cpp::ParameterXml(uint32_t /*aVersion*/, std::string& /*aaParameterXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkConfiguration1Cpp::SetParameter(uint32_t /*aVersion*/, const std::string& /*aaTarget*/, const std::string& /*aaName*/, const std::string& /*aaValue*/)
{
    ASSERTS();
}

