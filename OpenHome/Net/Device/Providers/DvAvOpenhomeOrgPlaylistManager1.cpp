#include "DvAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderAvOpenhomeOrgPlaylistManager1::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1::SetPropertyImagesXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyImagesXml, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::GetPropertyImagesXml(Brhz& aValue)
{
    aValue.Set(iPropertyImagesXml->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1::SetPropertyTokenArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyTokenArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::GetPropertyTokenArray(Brh& aValue)
{
    aValue.Set(iPropertyTokenArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1::SetPropertyPlaylistsMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyPlaylistsMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::GetPropertyPlaylistsMax(TUint& aValue)
{
    aValue = iPropertyPlaylistsMax->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1::SetPropertyTracksMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::GetPropertyTracksMax(TUint& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

DvProviderAvOpenhomeOrgPlaylistManager1::DvProviderAvOpenhomeOrgPlaylistManager1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "PlaylistManager", 1)
{
    
    iPropertyMetadata = new PropertyString(new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
    iPropertyImagesXml = new PropertyString(new ParameterString("ImagesXml"));
    iService->AddProperty(iPropertyImagesXml); // passes ownership
    iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
    iPropertyTokenArray = new PropertyBinary(new ParameterBinary("TokenArray"));
    iService->AddProperty(iPropertyTokenArray); // passes ownership
    iPropertyPlaylistsMax = new PropertyUint(new ParameterUint("PlaylistsMax"));
    iService->AddProperty(iPropertyPlaylistsMax); // passes ownership
    iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionMetadata()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionImagesXml()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImagesXml");
    action->AddOutputParameter(new ParameterRelated("ImagesXml", *iPropertyImagesXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoImagesXml);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistReadArray()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadArray");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistReadArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("PlaylistList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistRead");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddOutputParameter(new ParameterString("Name"));
    action->AddOutputParameter(new ParameterString("Description"));
    action->AddOutputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistSetName()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetName");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Name"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistSetName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistSetDescription()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetDescription");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Description"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistSetDescription);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistSetImageId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetImageId");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistSetImageId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistInsert()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistInsert");
    action->AddInputParameter(new ParameterUint("AfterId"));
    action->AddInputParameter(new ParameterString("Name"));
    action->AddInputParameter(new ParameterString("Description"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    action->AddOutputParameter(new ParameterUint("NewId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistDeleteId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistDeleteId");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistMove()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistMove");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("AfterId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistMove);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistsMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistsMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyPlaylistsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistsMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionTracksMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistArrays()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistArrays");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("IdArray", *iPropertyIdArray));
    action->AddOutputParameter(new ParameterRelated("TokenArray", *iPropertyTokenArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistArrays);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionPlaylistArraysChanged()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistArraysChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistArraysChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("TrackId"));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("TrackIdList"));
    action->AddOutputParameter(new ParameterString("TrackList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionInsert()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Insert");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("AfterTrackId"));
    action->AddInputParameter(new ParameterString("Udn"));
    action->AddInputParameter(new ParameterString("MetadataId"));
    action->AddOutputParameter(new ParameterUint("NewTrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionDeleteId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("TrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::EnableActionDeleteAll()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    action->AddInputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoMetadata(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Metadata(invocation, aVersion, respMetadata);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoImagesXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respImagesXml(aInvocation, "ImagesXml");
    ImagesXml(invocation, aVersion, respImagesXml);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistReadArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    PlaylistReadArray(invocation, aVersion, Id, respArray);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respPlaylistList(aInvocation, "PlaylistList");
    PlaylistReadList(invocation, aVersion, IdList, respPlaylistList);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respDescription(aInvocation, "Description");
    DviInvocationResponseUint respImageId(aInvocation, "ImageId");
    PlaylistRead(invocation, aVersion, Id, respName, respDescription, respImageId);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistSetName(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz Name;
    aInvocation.InvocationReadString("Name", Name);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    PlaylistSetName(invocation, aVersion, Id, Name);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistSetDescription(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz Description;
    aInvocation.InvocationReadString("Description", Description);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    PlaylistSetDescription(invocation, aVersion, Id, Description);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistSetImageId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    PlaylistSetImageId(invocation, aVersion, Id, ImageId);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz Name;
    aInvocation.InvocationReadString("Name", Name);
    Brhz Description;
    aInvocation.InvocationReadString("Description", Description);
    TUint ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respNewId(aInvocation, "NewId");
    PlaylistInsert(invocation, aVersion, AfterId, Name, Description, ImageId, respNewId);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistDeleteId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    PlaylistDeleteId(invocation, aVersion, Value);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistMove(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    PlaylistMove(invocation, aVersion, Id, AfterId);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistsMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    PlaylistsMax(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respValue(aInvocation, "Value");
    TracksMax(invocation, aVersion, respValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistArrays(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respIdArray(aInvocation, "IdArray");
    DviInvocationResponseBinary respTokenArray(aInvocation, "TokenArray");
    PlaylistArrays(invocation, aVersion, respToken, respIdArray, respTokenArray);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoPlaylistArraysChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseBool respValue(aInvocation, "Value");
    PlaylistArraysChanged(invocation, aVersion, Token, respValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    Read(invocation, aVersion, Id, TrackId, respMetadata);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz TrackIdList;
    aInvocation.InvocationReadString("TrackIdList", TrackIdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respTrackList(aInvocation, "TrackList");
    ReadList(invocation, aVersion, Id, TrackIdList, respTrackList);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint AfterTrackId = aInvocation.InvocationReadUint("AfterTrackId");
    Brhz Udn;
    aInvocation.InvocationReadString("Udn", Udn);
    Brhz MetadataId;
    aInvocation.InvocationReadString("MetadataId", MetadataId);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respNewTrackId(aInvocation, "NewTrackId");
    Insert(invocation, aVersion, Id, AfterTrackId, Udn, MetadataId, respNewTrackId);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoDeleteId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteId(invocation, aVersion, Id, TrackId);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteAll(invocation, aVersion, Id);
}

void DvProviderAvOpenhomeOrgPlaylistManager1::Metadata(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::ImagesXml(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aImagesXml*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistReadArray(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, IDvInvocationResponseBinary& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistReadList(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aIdList*/, IDvInvocationResponseString& /*aPlaylistList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistRead(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, IDvInvocationResponseString& /*aName*/, IDvInvocationResponseString& /*aDescription*/, IDvInvocationResponseUint& /*aImageId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistSetName(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, const Brx& /*aName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistSetDescription(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, const Brx& /*aDescription*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistSetImageId(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, TUint /*aImageId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistInsert(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aAfterId*/, const Brx& /*aName*/, const Brx& /*aDescription*/, TUint /*aImageId*/, IDvInvocationResponseUint& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistDeleteId(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistMove(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, TUint /*aAfterId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistsMax(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::TracksMax(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistArrays(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aToken*/, IDvInvocationResponseBinary& /*aIdArray*/, IDvInvocationResponseBinary& /*aTokenArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::PlaylistArraysChanged(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aToken*/, IDvInvocationResponseBool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::Read(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, TUint /*aTrackId*/, IDvInvocationResponseString& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::ReadList(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, const Brx& /*aTrackIdList*/, IDvInvocationResponseString& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::Insert(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, TUint /*aAfterTrackId*/, const Brx& /*aUdn*/, const Brx& /*aMetadataId*/, IDvInvocationResponseUint& /*aNewTrackId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DeleteId(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/, TUint /*aTrackId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1::DeleteAll(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aId*/)
{
    ASSERTS();
}

