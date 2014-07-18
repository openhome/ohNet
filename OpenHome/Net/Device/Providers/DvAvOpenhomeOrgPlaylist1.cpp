#include "DvAvOpenhomeOrgPlaylist1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyTransportState(const Brx& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    return SetPropertyString(*iPropertyTransportState, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyTransportState(Brhz& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    aValue.Set(iPropertyTransportState->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyRepeat(TBool aValue)
{
    ASSERT(iPropertyRepeat != NULL);
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyRepeat(TBool& aValue)
{
    ASSERT(iPropertyRepeat != NULL);
    aValue = iPropertyRepeat->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyShuffle(TBool aValue)
{
    ASSERT(iPropertyShuffle != NULL);
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyShuffle(TBool& aValue)
{
    ASSERT(iPropertyShuffle != NULL);
    aValue = iPropertyShuffle->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyId(TUint aValue)
{
    ASSERT(iPropertyId != NULL);
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyId(TUint& aValue)
{
    ASSERT(iPropertyId != NULL);
    aValue = iPropertyId->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyIdArray(const Brx& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyIdArray(Brh& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyTracksMax(TUint aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyTracksMax(TUint& aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    aValue = iPropertyTracksMax->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylist1::SetPropertyProtocolInfo(const Brx& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    return SetPropertyString(*iPropertyProtocolInfo, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::GetPropertyProtocolInfo(Brhz& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    aValue.Set(iPropertyProtocolInfo->Value());
}

DvProviderAvOpenhomeOrgPlaylist1::DvProviderAvOpenhomeOrgPlaylist1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Playlist", 1)
{
    Construct();
}

DvProviderAvOpenhomeOrgPlaylist1::DvProviderAvOpenhomeOrgPlaylist1(DviDevice& aDevice)
    : DvProvider(aDevice, "av.openhome.org", "Playlist", 1)
{
    Construct();
}

void DvProviderAvOpenhomeOrgPlaylist1::Construct()
{
    iPropertyTransportState = NULL;
    iPropertyRepeat = NULL;
    iPropertyShuffle = NULL;
    iPropertyId = NULL;
    iPropertyIdArray = NULL;
    iPropertyTracksMax = NULL;
    iPropertyProtocolInfo = NULL;
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyTransportState()
{
    TChar** allowedValues;
    TUint index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    iPropertyTransportState = new PropertyString(iDvStack.Env(), new ParameterString("TransportState", allowedValues, 4));
    delete[] allowedValues;
    iService->AddProperty(iPropertyTransportState); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyRepeat()
{
    iPropertyRepeat = new PropertyBool(iDvStack.Env(), new ParameterBool("Repeat"));
    iService->AddProperty(iPropertyRepeat); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyShuffle()
{
    iPropertyShuffle = new PropertyBool(iDvStack.Env(), new ParameterBool("Shuffle"));
    iService->AddProperty(iPropertyShuffle); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyId()
{
    iPropertyId = new PropertyUint(iDvStack.Env(), new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyTracksMax()
{
    iPropertyTracksMax = new PropertyUint(iDvStack.Env(), new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
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

void DvProviderAvOpenhomeOrgPlaylist1::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Play(invocation);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPause(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Pause(invocation);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Stop(invocation);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoNext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Next(invocation);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPrevious(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    Previous(invocation);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSetRepeat(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetRepeat(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoRepeat(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Repeat(invocation, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSetShuffle(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SetShuffle(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoShuffle(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    Shuffle(invocation, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondAbsolute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekSecondAbsolute(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondRelative(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekSecondRelative(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekId(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekIndex(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    SeekIndex(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoTransportState(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    TransportState(invocation, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    Id(invocation, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoRead(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respUri(aInvocation, "Uri");
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Read(invocation, Id, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoReadList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respTrackList(aInvocation, "TrackList");
    ReadList(invocation, IdList, respTrackList);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoInsert(IDviInvocation& aInvocation)
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
    Insert(invocation, AfterId, Uri, Metadata, respNewId);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoDeleteId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteId(invocation, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoDeleteAll(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteAll(invocation);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoTracksMax(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    TracksMax(invocation, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoIdArray(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    IdArray(invocation, respToken, respArray);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoIdArrayChanged(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    IdArrayChanged(invocation, Token, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoProtocolInfo(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respValue(aInvocation, "Value");
    ProtocolInfo(invocation, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::Play(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Pause(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Stop(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Next(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Previous(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SetRepeat(IDvInvocation& /*aResponse*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Repeat(IDvInvocation& /*aResponse*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SetShuffle(IDvInvocation& /*aResponse*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Shuffle(IDvInvocation& /*aResponse*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekSecondAbsolute(IDvInvocation& /*aResponse*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekSecondRelative(IDvInvocation& /*aResponse*/, TInt /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekId(IDvInvocation& /*aResponse*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekIndex(IDvInvocation& /*aResponse*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::TransportState(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Id(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Read(IDvInvocation& /*aResponse*/, TUint /*aId*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::ReadList(IDvInvocation& /*aResponse*/, const Brx& /*aIdList*/, IDvInvocationResponseString& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Insert(IDvInvocation& /*aResponse*/, TUint /*aAfterId*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/, IDvInvocationResponseUint& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::DeleteId(IDvInvocation& /*aResponse*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::DeleteAll(IDvInvocation& /*aResponse*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::TracksMax(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::IdArray(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aToken*/, IDvInvocationResponseBinary& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::IdArrayChanged(IDvInvocation& /*aResponse*/, TUint /*aToken*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::ProtocolInfo(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

