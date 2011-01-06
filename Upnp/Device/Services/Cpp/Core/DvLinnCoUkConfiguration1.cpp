#include "DvLinnCoUkConfiguration1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkConfiguration1::SetPropertyConfigurationXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyConfigurationXml, aValue);
}

void DvProviderLinnCoUkConfiguration1::GetPropertyConfigurationXml(Brhz& aValue)
{
    aValue.Set(iPropertyConfigurationXml->Value());
}

TBool DvProviderLinnCoUkConfiguration1::SetPropertyParameterXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyParameterXml, aValue);
}

void DvProviderLinnCoUkConfiguration1::GetPropertyParameterXml(Brhz& aValue)
{
    aValue.Set(iPropertyParameterXml->Value());
}

DvProviderLinnCoUkConfiguration1::DvProviderLinnCoUkConfiguration1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Configuration", 1)
{
    
    iPropertyConfigurationXml = new PropertyString(new ParameterString("ConfigurationXml"));
    iService->AddProperty(iPropertyConfigurationXml); // passes ownership
    iPropertyParameterXml = new PropertyString(new ParameterString("ParameterXml"));
    iService->AddProperty(iPropertyParameterXml); // passes ownership
}

void DvProviderLinnCoUkConfiguration1::EnableActionConfigurationXml()
{
    Zapp::Action* action = new Zapp::Action("ConfigurationXml");
    action->AddOutputParameter(new ParameterRelated("aConfigurationXml", *iPropertyConfigurationXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkConfiguration1::DoConfigurationXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkConfiguration1::EnableActionParameterXml()
{
    Zapp::Action* action = new Zapp::Action("ParameterXml");
    action->AddOutputParameter(new ParameterRelated("aParameterXml", *iPropertyParameterXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkConfiguration1::DoParameterXml);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkConfiguration1::EnableActionSetParameter()
{
    Zapp::Action* action = new Zapp::Action("SetParameter");
    action->AddInputParameter(new ParameterString("aTarget"));
    action->AddInputParameter(new ParameterString("aName"));
    action->AddInputParameter(new ParameterString("aValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkConfiguration1::DoSetParameter);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkConfiguration1::DoConfigurationXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaConfigurationXml(aInvocation, "aConfigurationXml");
    ConfigurationXml(resp, aVersion, respaConfigurationXml);
}

void DvProviderLinnCoUkConfiguration1::DoParameterXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaParameterXml(aInvocation, "aParameterXml");
    ParameterXml(resp, aVersion, respaParameterXml);
}

void DvProviderLinnCoUkConfiguration1::DoSetParameter(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderLinnCoUkConfiguration1::ConfigurationXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaConfigurationXml*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkConfiguration1::ParameterXml(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaParameterXml*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkConfiguration1::SetParameter(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaTarget*/, const Brx& /*aaName*/, const Brx& /*aaValue*/)
{
    ASSERTS();
}

