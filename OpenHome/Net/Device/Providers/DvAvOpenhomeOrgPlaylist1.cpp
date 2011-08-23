#include "DvAvOpenhomeOrgPlaylist1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyTransportState(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyTransportState(Brhz& aValue)
{
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyRepeat(TBool aValue)
{
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyRepeat(TBool& aValue)
{
    aValue = iPropertyRepeat->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyShuffle(TBool aValue)
{
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyShuffle(TBool& aValue)
{
    aValue = iPropertyShuffle->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyId(TUint aValue)
{
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyId(TUint& aValue)
{
    aValue = iPropertyId->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyTracksMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyTracksMax(TUint& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyProtocolInfo(const Brx& aValue)
{
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyProtocolInfo(Brhz& aValue)
{
    aValue.Set(iPropertyProtocolInfo->Value());
}

DvProviderAvOpenhomeOrgPlaylist1::DvProviderAvOpenhomeOrgPlaylist1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Playlist", 1)
{
    
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
    iPropertyRepeat = new PropertyBool(new ParameterBool("Repeat"));
    iService->AddProperty(iPropertyRepeat); // passes ownership
    iPropertyShuffle = new PropertyBool(new ParameterBool("Shuffle"));
    iService->AddProperty(iPropertyShuffle); // passes ownership
    iPropertyId = new PropertyUint(new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
    iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionNext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionPrevious()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionSetRepeat()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionRepeat()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoRepeat);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionSetShuffle()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionShuffle()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoShuffle);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionSeekSecondAbsolute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionSeekSecondRelative()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionSeekId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoSeekId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionSeekIndex()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekIndex");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoSeekIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionTransportState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Id");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterRelated("Id", *iPropertyId));
    action->AddOutputParameter(new ParameterString("Uri"));
    action->AddOutputParameter(new ParameterString("Metadata"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("TrackList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionInsert()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Insert");
    action->AddInputParameter(new ParameterRelated("AfterId", *iPropertyId));
    action->AddInputParameter(new ParameterString("Uri"));
    action->AddInputParameter(new ParameterString("Metadata"));
    action->AddOutputParameter(new ParameterRelated("NewId", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionDeleteId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionDeleteAll()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionTracksMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionIdArray()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionIdArrayChanged()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::EnableActionProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPlay(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Play(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Pause(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Stop(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoNext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Next(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPrevious(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Previous(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetRepeat(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Repeat(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetShuffle(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Shuffle(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekSecondAbsolute(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekSecondRelative(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekId(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekIndex(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    TransportState(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    Id(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Read(invocation, aVersion, Id, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respTrackList(aInvocation, "TrackList");
    ReadList(invocation, aVersion, IdList, respTrackList);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz Uri;
    aInvocation.InvocationReadString("Uri", Uri);
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respNewId(aInvocation, "NewId");
    Insert(invocation, aVersion, AfterId, Uri, Metadata, respNewId);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoDeleteId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteId(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteAll(invocation, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    TracksMax(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    IdArray(invocation, aVersion, respToken, respArray);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    IdArrayChanged(invocation, aVersion, Token, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    ProtocolInfo(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::Play(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Pause(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Stop(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Next(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Previous(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SetRepeat(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Repeat(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SetShuffle(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Shuffle(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekSecondAbsolute(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekSecondRelative(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TInt /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekId(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekIndex(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::TransportState(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Id(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Read(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::ReadList(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aIdList*/, IDvInvocationResponseString& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Insert(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aAfterId*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/, IDvInvocationResponseUint& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::DeleteId(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::DeleteAll(IDvInvocation& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::TracksMax(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::IdArray(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aToken*/, IDvInvocationResponseBinary& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::IdArrayChanged(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aToken*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::ProtocolInfo(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

