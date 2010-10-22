#include <Core/DvLinnCoUkMultipusSender1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkMultipusSender1::SetPropertyEnabled(TBool aValue)
{
    SetPropertyBool(*iPropertyEnabled, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyEnabled(TBool& aValue)
{
    aValue = iPropertyEnabled->Value();
}

void DvServiceLinnCoUkMultipusSender1::SetPropertyChannel(TUint aValue)
{
    SetPropertyUint(*iPropertyChannel, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyChannel(TUint& aValue)
{
    aValue = iPropertyChannel->Value();
}

void DvServiceLinnCoUkMultipusSender1::SetPropertyMetadata(const Brx& aValue)
{
    SetPropertyString(*iPropertyMetadata, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

void DvServiceLinnCoUkMultipusSender1::SetPropertyAudio(TBool aValue)
{
    SetPropertyBool(*iPropertyAudio, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyAudio(TBool& aValue)
{
    aValue = iPropertyAudio->Value();
}

void DvServiceLinnCoUkMultipusSender1::SetPropertyStatus(const Brx& aValue)
{
    SetPropertyString(*iPropertyStatus, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyStatus(Brhz& aValue)
{
    aValue.Set(iPropertyStatus->Value());
}

void DvServiceLinnCoUkMultipusSender1::SetPropertyInfoAvailable(TBool aValue)
{
    SetPropertyBool(*iPropertyInfoAvailable, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyInfoAvailable(TBool& aValue)
{
    aValue = iPropertyInfoAvailable->Value();
}

void DvServiceLinnCoUkMultipusSender1::SetPropertyTimeAvailable(TBool aValue)
{
    SetPropertyBool(*iPropertyTimeAvailable, aValue);
}

void DvServiceLinnCoUkMultipusSender1::GetPropertyTimeAvailable(TBool& aValue)
{
    aValue = iPropertyTimeAvailable->Value();
}

DvServiceLinnCoUkMultipusSender1::DvServiceLinnCoUkMultipusSender1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "MultipusSender", 1)
{
    Functor empty;
    TChar** allowedValues;
    TUint index;
    iPropertyEnabled = new PropertyBool(new ParameterBool("Enabled"), empty);
    iService->AddProperty(iPropertyEnabled); // passes ownership
    iPropertyChannel = new PropertyUint(new ParameterUint("Channel", 0, 65535, 1), empty);
    iService->AddProperty(iPropertyChannel); // passes ownership
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
    iPropertyInfoAvailable = new PropertyBool(new ParameterBool("InfoAvailable"), empty);
    iService->AddProperty(iPropertyInfoAvailable); // passes ownership
    iPropertyTimeAvailable = new PropertyBool(new ParameterBool("TimeAvailable"), empty);
    iService->AddProperty(iPropertyTimeAvailable); // passes ownership
}

void DvServiceLinnCoUkMultipusSender1::EnableActionEnabled()
{
    Zapp::Action* action = new Zapp::Action("Enabled");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionSetEnabled()
{
    Zapp::Action* action = new Zapp::Action("SetEnabled");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyEnabled));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoSetEnabled);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionChannel()
{
    Zapp::Action* action = new Zapp::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyChannel));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoChannel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionSetChannel()
{
    Zapp::Action* action = new Zapp::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyChannel));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionMetadata()
{
    Zapp::Action* action = new Zapp::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyMetadata));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoMetadata);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionAudio()
{
    Zapp::Action* action = new Zapp::Action("Audio");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyAudio));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoAudio);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionStatus()
{
    Zapp::Action* action = new Zapp::Action("Status");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyStatus));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoStatus);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionInfoAvailable()
{
    Zapp::Action* action = new Zapp::Action("InfoAvailable");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyInfoAvailable));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoInfoAvailable);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::EnableActionTimeAvailable()
{
    Zapp::Action* action = new Zapp::Action("TimeAvailable");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTimeAvailable));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkMultipusSender1::DoTimeAvailable);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkMultipusSender1::DoEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    Enabled(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::DoSetEnabled(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetEnabled(resp, aVersion, Value);
}

void DvServiceLinnCoUkMultipusSender1::DoChannel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respValue(aInvocation, "Value");
    Channel(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::DoSetChannel(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetChannel(resp, aVersion, Value);
}

void DvServiceLinnCoUkMultipusSender1::DoMetadata(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Metadata(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::DoAudio(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    Audio(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::DoStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    Status(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::DoInfoAvailable(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    InfoAvailable(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::DoTimeAvailable(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    TimeAvailable(resp, aVersion, respValue);
}

void DvServiceLinnCoUkMultipusSender1::Enabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::SetEnabled(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::Channel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::SetChannel(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::Metadata(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::Audio(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::Status(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::InfoAvailable(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkMultipusSender1::TimeAvailable(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

