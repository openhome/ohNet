#include <Core/DvLinnCoUkConfiguration1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkConfiguration1::SetPropertyConfigurationXml(const Brx& aValue)
{
    SetPropertyString(*iPropertyConfigurationXml, aValue);
}

void DvServiceLinnCoUkConfiguration1::GetPropertyConfigurationXml(Brhz& aValue)
{
    aValue.Set(iPropertyConfigurationXml->Value());
}

void DvServiceLinnCoUkConfiguration1::SetPropertyParameterXml(const Brx& aValue)
{
    SetPropertyString(*iPropertyParameterXml, aValue);
}

void DvServiceLinnCoUkConfiguration1::GetPropertyParameterXml(Brhz& aValue)
{
    aValue.Set(iPropertyParameterXml->Value());
}

DvServiceLinnCoUkConfiguration1::DvServiceLinnCoUkConfiguration1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Configuration", 1)
{
    Functor empty;
    iPropertyConfigurationXml = new PropertyString(new ParameterString("ConfigurationXml"), empty);
    iService->AddProperty(iPropertyConfigurationXml); // passes ownership
    iPropertyParameterXml = new PropertyString(new ParameterString("ParameterXml"), empty);
    iService->AddProperty(iPropertyParameterXml); // passes ownership
}

void DvServiceLinnCoUkConfiguration1::EnableActionConfigurationXml()
{
    Zapp::Action* action = new Zapp::Action("ConfigurationXml");
    action->AddOutputParameter(new ParameterRelated("aConfigurationXml", *iPropertyConfigurationXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkConfiguration1::DoConfigurationXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkConfiguration1::EnableActionParameterXml()
{
    Zapp::Action* action = new Zapp::Action("ParameterXml");
    action->AddOutputParameter(new ParameterRelated("aParameterXml", *iPropertyParameterXml));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkConfiguration1::DoParameterXml);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkConfiguration1::EnableActionSetParameter()
{
    Zapp::Action* action = new Zapp::Action("SetParameter");
    action->AddInputParameter(new ParameterString("aTarget"));
    action->AddInputParameter(new ParameterString("aName"));
    action->AddInputParameter(new ParameterString("aValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkConfiguration1::DoSetParameter);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkConfiguration1::DoConfigurationXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaConfigurationXml(aInvocation, "aConfigurationXml");
    ConfigurationXml(resp, aVersion, respaConfigurationXml);
}

void DvServiceLinnCoUkConfiguration1::DoParameterXml(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaParameterXml(aInvocation, "aParameterXml");
    ParameterXml(resp, aVersion, respaParameterXml);
}

void DvServiceLinnCoUkConfiguration1::DoSetParameter(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aTarget;
    aInvocation.InvocationReadString("aTarget", aTarget);
    Brhz aName;
    aInvocation.InvocationReadString("aName", aName);
    Brhz aValue;
    aInvocation.InvocationReadString("aValue", aValue);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetParameter(resp, aVersion, aTarget, aName, aValue);
}

void DvServiceLinnCoUkConfiguration1::ConfigurationXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaConfigurationXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkConfiguration1::ParameterXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaParameterXml*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkConfiguration1::SetParameter(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaTarget*/, const Brx& /*aaName*/, const Brx& /*aaValue*/)
{
    ASSERTS();
}

