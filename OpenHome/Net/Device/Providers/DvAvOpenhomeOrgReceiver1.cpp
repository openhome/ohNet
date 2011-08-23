#include "DvAvOpenhomeOrgReceiver1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgReceiver1::SetPropertyUri(const Brx& aValue)
{
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1::GetPropertyUri(Brhz& aValue)
{
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgReceiver1::SetPropertyProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgReceiver1::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

DvProviderAvOpenhomeOrgReceiver1::DvProviderAvOpenhomeOrgReceiver1(DvDevice& aDevice)
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

void DvProviderAvOpenhomeOrgReceiver1::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1::EnableActionSetSender()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetSender");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1::DoSetSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1::EnableActionSender()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Sender");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1::DoSender);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1::EnableActionProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1::EnableActionTransportState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgReceiver1::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgReceiver1::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Play(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgReceiver1::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Stop(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgReceiver1::DoSetSender(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetSender(invocation, aVersion, Uri, Metadata);
}

void DvProviderAvOpenhomeOrgReceiver1::DoSender(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Sender(invocation, aVersion, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgReceiver1::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    ProtocolInfo(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgReceiver1::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    TransportState(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgReceiver1::Play(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1::Stop(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1::SetSender(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1::Sender(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1::ProtocolInfo(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgReceiver1::TransportState(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

