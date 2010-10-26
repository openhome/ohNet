#include "DvMusicOpenhomeOrgSender1.h"
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceMusicOpenhomeOrgSender1::SetPropertyMetadata(const Brx& aValue)
{
    SetPropertyString(*iPropertyMetadata, aValue);
}

void DvServiceMusicOpenhomeOrgSender1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

void DvServiceMusicOpenhomeOrgSender1::SetPropertyAudio(TBool aValue)
{
    SetPropertyBool(*iPropertyAudio, aValue);
}

void DvServiceMusicOpenhomeOrgSender1::GetPropertyAudio(TBool& aValue)
{
    aValue = iPropertyAudio->Value();
}

void DvServiceMusicOpenhomeOrgSender1::SetPropertyStatus(const Brx& aValue)
{
    SetPropertyString(*iPropertyStatus, aValue);
}

void DvServiceMusicOpenhomeOrgSender1::GetPropertyStatus(Brhz& aValue)
{
    aValue.Set(iPropertyStatus->Value());
}

void DvServiceMusicOpenhomeOrgSender1::SetPropertyAttributes(const Brx& aValue)
{
    SetPropertyString(*iPropertyAttributes, aValue);
}

void DvServiceMusicOpenhomeOrgSender1::GetPropertyAttributes(Brhz& aValue)
{
    aValue.Set(iPropertyAttributes->Value());
}

DvServiceMusicOpenhomeOrgSender1::DvServiceMusicOpenhomeOrgSender1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "music.openhome.org", "Sender", 1)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"), empty);
    iService->AddProperty(iPropertyMetadata); // passes ownership
    iPropertyAudio = new PropertyBool(new ParameterBool("Audio"), empty);
    iService->AddProperty(iPropertyAudio); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Sending";
    allowedValues[index++] = (TChar*)"Ready";
    allowedValues[index++] = (TChar*)"Blocked";
    allowedValues[index++] = (TChar*)"Inactive";
    iPropertyStatus = new PropertyString(new ParameterString("Status", allowedValues, 4), empty);
    delete[] allowedValues;
    iService->AddProperty(iPropertyStatus); // passes ownership
    iPropertyAttributes = new PropertyString(new ParameterString("Attributes"), empty);
    iService->AddProperty(iPropertyAttributes); // passes ownership
}

void DvServiceMusicOpenhomeOrgSender1::EnableActionMetadata()
{
    Zapp::Action* action = new Zapp::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceMusicOpenhomeOrgSender1::DoMetadata);
    iService->AddAction(action, functor);
}

void DvServiceMusicOpenhomeOrgSender1::EnableActionAudio()
{
    Zapp::Action* action = new Zapp::Action("Audio");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAudio));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceMusicOpenhomeOrgSender1::DoAudio);
    iService->AddAction(action, functor);
}

void DvServiceMusicOpenhomeOrgSender1::EnableActionStatus()
{
    Zapp::Action* action = new Zapp::Action("Status");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceMusicOpenhomeOrgSender1::DoStatus);
    iService->AddAction(action, functor);
}

void DvServiceMusicOpenhomeOrgSender1::EnableActionAttributes()
{
    Zapp::Action* action = new Zapp::Action("Attributes");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAttributes));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceMusicOpenhomeOrgSender1::DoAttributes);
    iService->AddAction(action, functor);
}

void DvServiceMusicOpenhomeOrgSender1::DoMetadata(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Metadata(resp, aVersion, respValue);
}

void DvServiceMusicOpenhomeOrgSender1::DoAudio(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    Audio(resp, aVersion, respValue);
}

void DvServiceMusicOpenhomeOrgSender1::DoStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Status(resp, aVersion, respValue);
}

void DvServiceMusicOpenhomeOrgSender1::DoAttributes(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Attributes(resp, aVersion, respValue);
}

void DvServiceMusicOpenhomeOrgSender1::Metadata(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvServiceMusicOpenhomeOrgSender1::Audio(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvServiceMusicOpenhomeOrgSender1::Status(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvServiceMusicOpenhomeOrgSender1::Attributes(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

