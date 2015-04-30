#include "DvAvOpenhomeOrgSender1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgSender1Cpp::SetPropertyPresentationUrl(const std::string& aValue)
{
    ASSERT(iPropertyPresentationUrl != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyPresentationUrl, buf);
}

void DvProviderAvOpenhomeOrgSender1Cpp::GetPropertyPresentationUrl(std::string& aValue)
{
    ASSERT(iPropertyPresentationUrl != NULL);
    const Brx& val = iPropertyPresentationUrl->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgSender1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgSender1Cpp::GetPropertyMetadata(std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgSender1Cpp::SetPropertyAudio(bool aValue)
{
    ASSERT(iPropertyAudio != NULL);
    return SetPropertyBool(*iPropertyAudio, aValue);
}

void DvProviderAvOpenhomeOrgSender1Cpp::GetPropertyAudio(bool& aValue)
{
    ASSERT(iPropertyAudio != NULL);
    aValue = iPropertyAudio->Value();
}

bool DvProviderAvOpenhomeOrgSender1Cpp::SetPropertyStatus(const std::string& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyStatus, buf);
}

void DvProviderAvOpenhomeOrgSender1Cpp::GetPropertyStatus(std::string& aValue)
{
    ASSERT(iPropertyStatus != NULL);
    const Brx& val = iPropertyStatus->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgSender1Cpp::SetPropertyAttributes(const std::string& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyAttributes, buf);
}

void DvProviderAvOpenhomeOrgSender1Cpp::GetPropertyAttributes(std::string& aValue)
{
    ASSERT(iPropertyAttributes != NULL);
    const Brx& val = iPropertyAttributes->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgSender1Cpp::DvProviderAvOpenhomeOrgSender1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Sender", 1)
{
    iPropertyPresentationUrl = NULL;
    iPropertyMetadata = NULL;
    iPropertyAudio = NULL;
    iPropertyStatus = NULL;
    iPropertyAttributes = NULL;
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnablePropertyPresentationUrl()
{
    iPropertyPresentationUrl = new PropertyString(new ParameterString("PresentationUrl"));
    iService->AddProperty(iPropertyPresentationUrl); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnablePropertyAudio()
{
    iPropertyAudio = new PropertyBool(new ParameterBool("Audio"));
    iService->AddProperty(iPropertyAudio); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnablePropertyStatus()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"Enabled";
    allowedValues[index++] = (TChar*)"Disabled";
    allowedValues[index++] = (TChar*)"Blocked";
    iPropertyStatus = new PropertyString(new ParameterString("Status", allowedValues, 3));
    delete[] allowedValues;
    iService->AddProperty(iPropertyStatus); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnablePropertyAttributes()
{
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"));
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnableActionPresentationUrl()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PresentationUrl");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyPresentationUrl));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1Cpp::DoPresentationUrl);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnableActionMetadata()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1Cpp::DoMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnableActionAudio()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Audio");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAudio));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1Cpp::DoAudio);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnableActionStatus()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Status");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStatus));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1Cpp::DoStatus);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1Cpp::EnableActionAttributes()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgSender1Cpp::DoAttributes);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgSender1Cpp::DoPresentationUrl(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    PresentationUrl(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgSender1Cpp::DoMetadata(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    Metadata(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgSender1Cpp::DoAudio(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValue;
    DvInvocationStd invocation(aInvocation);
    Audio(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgSender1Cpp::DoStatus(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    Status(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgSender1Cpp::DoAttributes(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    Attributes(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgSender1Cpp::PresentationUrl(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1Cpp::Metadata(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1Cpp::Audio(IDvInvocationStd& /*aInvocation*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1Cpp::Status(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgSender1Cpp::Attributes(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

