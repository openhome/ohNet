#include "DvAvOpenhomeOrgReceiver1.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyUri(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyUri, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyUri(std::string& aValue)
{
    const Brx& val = iPropertyUri->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyMetadata(std::string& aValue)
{
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransportState, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyTransportState(std::string& aValue)
{
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgReceiver1Cpp::SetPropertyProtocolInfo(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProtocolInfo, buf);
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::GetPropertyProtocolInfo(std::string& aValue)
{
    const Brx& val = iPropertyProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgReceiver1Cpp::DvProviderAvOpenhomeOrgReceiver1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Receiver", 1)
{
    
    TChar** allowedValues;
    TUint index;
    iPropertyUri = new PropertyString(new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Waiting";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
    iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo"));
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

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoPlay(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Play(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoStop(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    Stop(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoSetSender(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Uri;
    aInvocation.InvocationReadString("Uri", buf_Uri);
    std::string Uri((const char*)buf_Uri.Ptr(), buf_Uri.Bytes());
    Brhz buf_Metadata;
    aInvocation.InvocationReadString("Metadata", buf_Metadata);
    std::string Metadata((const char*)buf_Metadata.Ptr(), buf_Metadata.Bytes());
    aInvocation.InvocationReadEnd();
    SetSender(aVersion, Uri, Metadata);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoSender(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respUri;
    std::string respMetadata;
    Sender(aVersion, respUri, respMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterUri(aInvocation, "Uri");
    Brn buf_Uri((const TByte*)respUri.c_str(), (TUint)respUri.length());
    respWriterUri.Write(buf_Uri);
    aInvocation.InvocationWriteStringEnd("Uri");
    InvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    ProtocolInfo(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::DoTransportState(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respValue;
    TransportState(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterValue(aInvocation, "Value");
    Brn buf_Value((const TByte*)respValue.c_str(), (TUint)respValue.length());
    respWriterValue.Write(buf_Value);
    aInvocation.InvocationWriteStringEnd("Value");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::Play(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::Stop(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::SetSender(uint32_t /*aVersion*/, const std::string& /*aUri*/, const std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::Sender(uint32_t /*aVersion*/, std::string& /*aUri*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::ProtocolInfo(uint32_t /*aVersion*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1Cpp::TransportState(uint32_t /*aVersion*/, std::string& /*aValue*/)
{
    ASSERTS();
}

