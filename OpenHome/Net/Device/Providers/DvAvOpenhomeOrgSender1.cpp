#include "DvAvOpenhomeOrgSender1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgSender1::SetPropertyPresentationUrl(const Brx& aValue)
{
    return SetPropertyString(*iPropertyPresentationUrl, aValue);
}

void DvProviderAvOpenhomeOrgSender1::GetPropertyPresentationUrl(Brhz& aValue)
{
    aValue.Set(iPropertyPresentationUrl->Value());
}

TBool DvProviderAvOpenhomeOrgSender1::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgSender1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgSender1::SetPropertyAudio(TBool aValue)
{
    return SetPropertyBool(*iPropertyAudio, aValue);
}

void DvProviderAvOpenhomeOrgSender1::GetPropertyAudio(TBool& aValue)
{
    aValue = iPropertyAudio->Value();
}

TBool DvProviderAvOpenhomeOrgSender1::SetPropertyStatus(const Brx& aValue)
{
    return SetPropertyString(*iPropertyStatus, aValue);
}

void DvProviderAvOpenhomeOrgSender1::GetPropertyStatus(Brhz& aValue)
{
    aValue.Set(iPropertyStatus->Value());
}

TBool DvProviderAvOpenhomeOrgSender1::SetPropertyAttributes(const Brx& aValue)
{
    return SetPropertyString(*iPropertyAttributes, aValue);
}

void DvProviderAvOpenhomeOrgSender1::GetPropertyAttributes(Brhz& aValue)
{
    aValue.Set(iPropertyAttributes->Value());
}

DvProviderAvOpenhomeOrgSender1::DvProviderAvOpenhomeOrgSender1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Sender", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyPresentationUrl = new PropertyString(new ParameterString("PresentationUrl"));
    iService->AddProperty(iPropertyPresentationUrl); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    iPropertyAudio = new PropertyBool(new ParameterBool("Audio"));
    iService->AddProperty(iPropertyAudio); // passes ownership
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"Enabled";
    allowedValues[index++] = (TChar*)"Disabled";
    allowedValues[index++] = (TChar*)"Blocked";
    iPropertyStatus = new PropertyString(new ParameterString("Status", allowedValues, 3));
    delete[] allowedValues;
    iService->AddProperty(iPropertyStatus); // passes ownership
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1::EnableActionPresentationUrl()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PresentationUrl");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyPresentationUrl));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1::DoPresentationUrl);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1::EnableActionMetadata()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1::DoMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1::EnableActionAudio()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Audio");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAudio));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1::DoAudio);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1::EnableActionStatus()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Status");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1::DoStatus);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1::EnableActionAttributes()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1::DoPresentationUrl(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    PresentationUrl(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgSender1::DoMetadata(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Metadata(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgSender1::DoAudio(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Audio(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgSender1::DoStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Status(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgSender1::DoAttributes(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    Attributes(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgSender1::PresentationUrl(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1::Metadata(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1::Audio(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1::Status(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1::Attributes(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

