#include "DvAvOpenhomeOrgPlaylist1.h"
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

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
    InvocationResponse resp(aInvocation);
    Play(resp, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPause(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Pause(resp, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoStop(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Stop(resp, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoNext(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Next(resp, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoPrevious(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Previous(resp, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSetRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetRepeat(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoRepeat(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    Repeat(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSetShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TBool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetShuffle(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoShuffle(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    Shuffle(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondAbsolute(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondAbsolute(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekSecondRelative(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TInt Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekSecondRelative(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekId(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoSeekIndex(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SeekIndex(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoTransportState(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    TransportState(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respValue(aInvocation, "Value");
    Id(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respUri(aInvocation, "Uri");
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    Read(resp, aVersion, Id, respUri, respMetadata);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respTrackList(aInvocation, "TrackList");
    ReadList(resp, aVersion, IdList, respTrackList);
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
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respNewId(aInvocation, "NewId");
    Insert(resp, aVersion, AfterId, Uri, Metadata, respNewId);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoDeleteId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteId(resp, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteAll(resp, aVersion);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respValue(aInvocation, "Value");
    TracksMax(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoIdArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respToken(aInvocation, "Token");
    InvocationResponseBinary respArray(aInvocation, "Array");
    IdArray(resp, aVersion, respToken, respArray);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoIdArrayChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBool respValue(aInvocation, "Value");
    IdArrayChanged(resp, aVersion, Token, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::DoProtocolInfo(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respValue(aInvocation, "Value");
    ProtocolInfo(resp, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylist1::Play(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Pause(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Stop(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Next(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Previous(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SetRepeat(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Repeat(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SetShuffle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TBool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Shuffle(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekSecondAbsolute(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekSecondRelative(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TInt /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::SeekIndex(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::TransportState(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Id(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Read(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, IInvocationResponseString& /*aUri*/, IInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::ReadList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aIdList*/, IInvocationResponseString& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::Insert(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aAfterId*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/, IInvocationResponseUint& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::DeleteId(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::DeleteAll(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::TracksMax(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::IdArray(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aToken*/, IInvocationResponseBinary& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::IdArrayChanged(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aToken*/, IInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1::ProtocolInfo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aValue*/)
{
    ASSERTS();
}

