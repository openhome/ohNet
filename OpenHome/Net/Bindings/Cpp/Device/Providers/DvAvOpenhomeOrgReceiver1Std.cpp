#include "DvAvOpenhomeOrgReceiver1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyUri(const std::string& aValue)
{
    ASSERT(iPropertyUri != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyUri, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyUri(std::string& aValue)
{
    ASSERT(iPropertyUri != NULL);
    const Brx& val = iPropertyUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyMetadata(std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransportState, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyTransportState(std::string& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyProtocolInfo(const std::string& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProtocolInfo, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyProtocolInfo(std::string& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    const Brx& val = iPropertyProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgReceiver1Cpp::DvProviderAvOpenhomeOrgReceiver1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Receiver", 1)
{
    iPropertyUri = NULL;
    iPropertyMetadata = NULL;
    iPropertyTransportState = NULL;
    iPropertyProtocolInfo = NULL;
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnablePropertyTransportState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Waiting";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(iDvStack.Env(), new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnableActionSetSender()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSender");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1Cpp::DoSetSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnableActionSender()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Sender");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1Cpp::DoSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnableActionProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1Cpp::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::EnableActionTransportState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1Cpp::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Play(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Stop(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoSetSender(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Uri;
    aInvocation.InvocationReadString("Uri", buf_Uri);
    std::string Uri((const char*)buf_Uri.Ptr(), buf_Uri.Bytes());
    Brhz buf_Metadata;
    aInvocation.InvocationReadString("Metadata", buf_Metadata);
    std::string Metadata((const char*)buf_Metadata.Ptr(), buf_Metadata.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetSender(invocation, Uri, Metadata);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoSender(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respUri;
    std::string respMetadata;
    DvInvocationStd invocation(aInvocation);
    Sender(invocation, respUri, respMetadata);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterUri(aInvocation, "Uri");
    Brn buf_Uri((const TByte*)respUri.c_str(), (TUint)respUri.length());
    respWriterUri.Write(buf_Uri);
    aInvocation.InvocationWriteStringEnd("Uri");
    DviInvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoProtocolInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    ProtocolInfo(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoTransportState(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    DvInvocationStd invocation(aInvocation);
    TransportState(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::Play(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::Stop(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::SetSender(IDvInvocationStd& /*aInvocation*/, const std::string& /*aUri*/, const std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::Sender(IDvInvocationStd& /*aInvocation*/, std::string& /*aUri*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::ProtocolInfo(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::TransportState(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

