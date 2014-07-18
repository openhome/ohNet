#include "DvAvOpenhomeOrgPlaylist1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyTransportState(const std::string& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransportState, buf);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyTransportState(std::string& aValue)
{
    ASSERT(iPropertyTransportState != NULL);
    const Brx& val = iPropertyTransportState->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyRepeat(bool aValue)
{
    ASSERT(iPropertyRepeat != NULL);
    return SetPropertyBool(*iPropertyRepeat, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyRepeat(bool& aValue)
{
    ASSERT(iPropertyRepeat != NULL);
    aValue = iPropertyRepeat->Value();
}

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyShuffle(bool aValue)
{
    ASSERT(iPropertyShuffle != NULL);
    return SetPropertyBool(*iPropertyShuffle, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyShuffle(bool& aValue)
{
    ASSERT(iPropertyShuffle != NULL);
    aValue = iPropertyShuffle->Value();
}

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyId(uint32_t aValue)
{
    ASSERT(iPropertyId != NULL);
    return SetPropertyUint(*iPropertyId, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyId(uint32_t& aValue)
{
    ASSERT(iPropertyId != NULL);
    aValue = iPropertyId->Value();
}

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyIdArray(std::string& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyTracksMax(uint32_t aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyTracksMax(uint32_t& aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    aValue = iPropertyTracksMax->Value();
}

bool DvProviderAvOpenhomeOrgPlaylist1Cpp::SetPropertyProtocolInfo(const std::string& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyProtocolInfo, buf);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::GetPropertyProtocolInfo(std::string& aValue)
{
    ASSERT(iPropertyProtocolInfo != NULL);
    const Brx& val = iPropertyProtocolInfo->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderAvOpenhomeOrgPlaylist1Cpp::DvProviderAvOpenhomeOrgPlaylist1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "Playlist", 1)
{
    iPropertyTransportState = NULL;
    iPropertyRepeat = NULL;
    iPropertyShuffle = NULL;
    iPropertyId = NULL;
    iPropertyIdArray = NULL;
    iPropertyTracksMax = NULL;
    iPropertyProtocolInfo = NULL;
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyTransportState()
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

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyRepeat()
{
    iPropertyRepeat = new PropertyBool(iDvStack.Env(), new ParameterBool("Repeat"));
    iService->AddProperty(iPropertyRepeat); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyShuffle()
{
    iPropertyShuffle = new PropertyBool(iDvStack.Env(), new ParameterBool("Shuffle"));
    iService->AddProperty(iPropertyShuffle); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyId()
{
    iPropertyId = new PropertyUint(iDvStack.Env(), new ParameterUint("Id"));
    iService->AddProperty(iPropertyId); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyTracksMax()
{
    iPropertyTracksMax = new PropertyUint(iDvStack.Env(), new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnablePropertyProtocolInfo()
{
    iPropertyProtocolInfo = new PropertyString(iDvStack.Env(), new ParameterString("ProtocolInfo"));
    iService->AddProperty(iPropertyProtocolInfo); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionPlay()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Play");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoPlay);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionPause()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Pause");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoPause);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionStop()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Stop");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoStop);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionNext()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Next");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoNext);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionPrevious()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Previous");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoPrevious);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionSetRepeat()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetRepeat");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSetRepeat);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionRepeat()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Repeat");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyRepeat));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoRepeat);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionSetShuffle()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SetShuffle");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSetShuffle);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionShuffle()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Shuffle");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyShuffle));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoShuffle);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionSeekSecondAbsolute()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondAbsolute");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekSecondAbsolute);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionSeekSecondRelative()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekSecondRelative");
    action->AddInputParameter(new ParameterInt("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekSecondRelative);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionSeekId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionSeekIndex()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("SeekIndex");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekIndex);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionTransportState()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TransportState");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTransportState));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoTransportState);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Id");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterRelated("Id", *iPropertyId));
    action->AddOutputParameter(new ParameterString("Uri"));
    action->AddOutputParameter(new ParameterString("Metadata"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("TrackList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionInsert()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Insert");
    action->AddInputParameter(new ParameterRelated("AfterId", *iPropertyId));
    action->AddInputParameter(new ParameterString("Uri"));
    action->AddInputParameter(new ParameterString("Metadata"));
    action->AddOutputParameter(new ParameterRelated("NewId", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionDeleteId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterRelated("Value", *iPropertyId));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionDeleteAll()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionTracksMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionIdArray()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArray");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoIdArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionIdArrayChanged()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("IdArrayChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoIdArrayChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::EnableActionProtocolInfo()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ProtocolInfo");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyProtocolInfo));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylist1Cpp::DoProtocolInfo);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoPlay(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Play(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoPause(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Pause(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoStop(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Stop(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoNext(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Next(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoPrevious(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    Previous(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSetRepeat(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    bool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetRepeat(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoRepeat(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValue;
    DvInvocationStd invocation(aInvocation);
    Repeat(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSetShuffle(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    bool Value = aInvocation.InvocationReadBool("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SetShuffle(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoShuffle(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    bool respValue;
    DvInvocationStd invocation(aInvocation);
    Shuffle(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekSecondAbsolute(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SeekSecondAbsolute(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekSecondRelative(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    int32_t Value = aInvocation.InvocationReadInt("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SeekSecondRelative(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SeekId(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoSeekIndex(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    SeekIndex(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoTransportState(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    Id(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoRead(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    std::string respUri;
    std::string respMetadata;
    DvInvocationStd invocation(aInvocation);
    Read(invocation, Id, respUri, respMetadata);
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

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoReadList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_IdList;
    aInvocation.InvocationReadString("IdList", buf_IdList);
    std::string IdList((const char*)buf_IdList.Ptr(), buf_IdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respTrackList;
    DvInvocationStd invocation(aInvocation);
    ReadList(invocation, IdList, respTrackList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterTrackList(aInvocation, "TrackList");
    Brn buf_TrackList((const TByte*)respTrackList.c_str(), (TUint)respTrackList.length());
    respWriterTrackList.Write(buf_TrackList);
    aInvocation.InvocationWriteStringEnd("TrackList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoInsert(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz buf_Uri;
    aInvocation.InvocationReadString("Uri", buf_Uri);
    std::string Uri((const char*)buf_Uri.Ptr(), buf_Uri.Bytes());
    Brhz buf_Metadata;
    aInvocation.InvocationReadString("Metadata", buf_Metadata);
    std::string Metadata((const char*)buf_Metadata.Ptr(), buf_Metadata.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respNewId;
    DvInvocationStd invocation(aInvocation);
    Insert(invocation, AfterId, Uri, Metadata, respNewId);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterNewId(aInvocation, "NewId");
    respWriterNewId.Write(respNewId);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoDeleteId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteId(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoDeleteAll(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteAll(invocation);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoTracksMax(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    TracksMax(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoIdArray(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respToken;
    std::string respArray;
    DvInvocationStd invocation(aInvocation);
    IdArray(invocation, respToken, respArray);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterToken(aInvocation, "Token");
    respWriterToken.Write(respToken);
    DviInvocationResponseBinary respWriterArray(aInvocation, "Array");
    Brn buf_Array((const TByte*)respArray.c_str(), (TUint)respArray.length());
    respWriterArray.Write(buf_Array);
    aInvocation.InvocationWriteBinaryEnd("Array");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoIdArrayChanged(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    bool respValue;
    DvInvocationStd invocation(aInvocation);
    IdArrayChanged(invocation, Token, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DoProtocolInfo(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Play(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Pause(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Stop(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Next(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Previous(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::SetRepeat(IDvInvocationStd& /*aInvocation*/, bool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Repeat(IDvInvocationStd& /*aInvocation*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::SetShuffle(IDvInvocationStd& /*aInvocation*/, bool /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Shuffle(IDvInvocationStd& /*aInvocation*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::SeekSecondAbsolute(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::SeekSecondRelative(IDvInvocationStd& /*aInvocation*/, int32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::SeekId(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::SeekIndex(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::TransportState(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Id(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Read(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, std::string& /*aUri*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::ReadList(IDvInvocationStd& /*aInvocation*/, const std::string& /*aIdList*/, std::string& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::Insert(IDvInvocationStd& /*aInvocation*/, uint32_t /*aAfterId*/, const std::string& /*aUri*/, const std::string& /*aMetadata*/, uint32_t& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DeleteId(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::DeleteAll(IDvInvocationStd& /*aInvocation*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::TracksMax(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::IdArray(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aToken*/, std::string& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::IdArrayChanged(IDvInvocationStd& /*aInvocation*/, uint32_t /*aToken*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylist1Cpp::ProtocolInfo(IDvInvocationStd& /*aInvocation*/, std::string& /*aValue*/)
{
    ASSERTS();
}

