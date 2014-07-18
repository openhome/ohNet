#include "DvAvOpenhomeOrgRadio1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyUri(const Brx& aValue)
{
    ASSERT(iPropertyUri != NULL);
    return SetPropertyString(*iPropertyUri, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyUri(Brhz& aValue)
{
    ASSERT(iPropertyUri != NULL);
    aValue.Set(iPropertyUri->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyTransportState(const Brx& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyTransportState(Brhz& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyId(TUint aValue)
{
    ASSERT(iPropertyId != NULL);
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyId(TUint& aValue)
{
    ASSERT(iPropertyId != NULL);
    aValue = iPropertyId->Value();
}

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyIdArray(const Brx& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyIdArray(Brh& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyChannelsMax(TUint aValue)
{
    ASSERT(iPropertyChannelsMax != NULL);
    return SetPropertyUint(*iPropertyChannelsMax, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyChannelsMax(TUint& aValue)
{
    ASSERT(iPropertyChannelsMax != NULL);
    aValue = iPropertyChannelsMax->Value();
}

TBool DvProviderAvOpenhomeOrgRadio1::SetPropertyProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgRadio1::GetPropertyProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    aValue.Set(iPropertyProtocolInfo->Value());
}

DvProviderAvOpenhomeOrgRadio1::DvProviderAvOpenhomeOrgRadio1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Radio", 1)
{
    Construct();
}

DvProviderAvOpenhomeOrgRadio1::DvProviderAvOpenhomeOrgRadio1(DviDevice& aDevice)
    : DvProvider(aDevice, "av.openhome.org", "Radio", 1)
{
    Construct();
}

void DvProviderAvOpenhomeOrgRadio1::Construct()
{
    iPropertyUri = NULL;
    iPropertyMetadata = NULL;
    iPropertyTransportState = NULL;
    iPropertyId = NULL;
    iPropertyIdArray = NULL;
    iPropertyChannelsMax = NULL;
    iPropertyProtocolInfo = NULL;
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyUri()
{
    iPropertyUri = new PropertyString(iDvStack.Env(), new ParameterString("Uri"));
    iService->AddProperty(iPropertyUri); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyTransportState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(iDvStack.Env(), new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyId()
{
    iPropertyId = new PropertyUint(iDvStack.Env(), new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyChannelsMax()
{
    iPropertyChannelsMax = new PropertyUint(iDvStack.Env(), new ParameterUint("ChannelsMax"));
    iService->AddProperty(iPropertyChannelsMax); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionSeekSecondAbsolute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionSeekSecondRelative()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionChannel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Channel");
    action->AddOutputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoChannel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionSetChannel()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetChannel");
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoSetChannel);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionTransportState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Id");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionSetId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    action->AddInputParameter(new ParameterRelated("Uri", *iPropertyUri));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoSetId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterRelated("Id", *iPropertyId));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("ChannelList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionIdArray()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionIdArrayChanged()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionChannelsMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ChannelsMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyChannelsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoChannelsMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::EnableActionProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgRadio1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgRadio1::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Play(invocation);
}

void DvProviderAvOpenhomeOrgRadio1::DoPause(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Pause(invocation);
}

void DvProviderAvOpenhomeOrgRadio1::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Stop(invocation);
}

void DvProviderAvOpenhomeOrgRadio1::DoSeekSecondAbsolute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekSecondAbsolute(invocation, Value);
}

void DvProviderAvOpenhomeOrgRadio1::DoSeekSecondRelative(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekSecondRelative(invocation, Value);
}

void DvProviderAvOpenhomeOrgRadio1::DoChannel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Channel(invocation, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgRadio1::DoSetChannel(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetChannel(invocation, Uri, Metadata);
}

void DvProviderAvOpenhomeOrgRadio1::DoTransportState(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    TransportState(invocation, respValue);
}

void DvProviderAvOpenhomeOrgRadio1::DoId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    Id(invocation, respValue);
}

void DvProviderAvOpenhomeOrgRadio1::DoSetId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetId(invocation, Value, Uri);
}

void DvProviderAvOpenhomeOrgRadio1::DoRead(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Read(invocation, Id, respMetadata);
}

void DvProviderAvOpenhomeOrgRadio1::DoReadList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respChannelList(aInvocation, "ChannelList");
    ReadList(invocation, IdList, respChannelList);
}

void DvProviderAvOpenhomeOrgRadio1::DoIdArray(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    IdArray(invocation, respToken, respArray);
}

void DvProviderAvOpenhomeOrgRadio1::DoIdArrayChanged(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    IdArrayChanged(invocation, Token, respValue);
}

void DvProviderAvOpenhomeOrgRadio1::DoChannelsMax(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    ChannelsMax(invocation, respValue);
}

void DvProviderAvOpenhomeOrgRadio1::DoProtocolInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    ProtocolInfo(invocation, respValue);
}

void DvProviderAvOpenhomeOrgRadio1::Play(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::Pause(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::Stop(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::SeekSecondAbsolute(IDvInvocation& /*aResponse*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::SeekSecondRelative(IDvInvocation& /*aResponse*/, TInt /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::Channel(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::SetChannel(IDvInvocation& /*aResponse*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::TransportState(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::Id(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::SetId(IDvInvocation& /*aResponse*/, TUint /*aValue*/, const Brx& /*aUri*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::Read(IDvInvocation& /*aResponse*/, TUint /*aId*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::ReadList(IDvInvocation& /*aResponse*/, const Brx& /*aIdList*/, IDvInvocationResponseString& /*aChannelList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::IdArray(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aToken*/, IDvInvocationResponseBinary& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::IdArrayChanged(IDvInvocation& /*aResponse*/, TUint /*aToken*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::ChannelsMax(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgRadio1::ProtocolInfo(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

