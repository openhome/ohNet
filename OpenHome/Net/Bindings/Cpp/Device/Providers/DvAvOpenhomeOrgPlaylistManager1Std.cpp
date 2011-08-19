#include "DvAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyMetadata(std::string& aValue)
{
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyImagesXml(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyImagesXml, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyImagesXml(std::string& aValue)
{
    const Brx& val = iPropertyImagesXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyIdArray(std::string& aValue)
{
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyTokenArray(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyTokenArray, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyTokenArray(std::string& aValue)
{
    const Brx& val = iPropertyTokenArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyPlaylistsMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyPlaylistsMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyPlaylistsMax(uint32_t& aValue)
{
    aValue = iPropertyPlaylistsMax->Value();
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyTracksMax(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyTracksMax(uint32_t& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DvProviderAvOpenhomeOrgPlaylistManager1Cpp(DvDeviceStd& aDevice)
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

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionMetadata()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionImagesXml()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImagesXml");
    action->AddOutputParameter(new ParameterRelated("ImagesXml", *iPropertyImagesXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoImagesXml);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistReadArray()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadArray");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistReadArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("PlaylistList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistRead");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddOutputParameter(new ParameterString("Name"));
    action->AddOutputParameter(new ParameterString("Description"));
    action->AddOutputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistSetName()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetName");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Name"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistSetDescription()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetDescription");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Description"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetDescription);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistSetImageId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetImageId");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetImageId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistInsert()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistInsert");
    action->AddInputParameter(new ParameterUint("AfterId"));
    action->AddInputParameter(new ParameterString("Name"));
    action->AddInputParameter(new ParameterString("Description"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    action->AddOutputParameter(new ParameterUint("NewId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistDeleteId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistDeleteId");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistMove()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistMove");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("AfterId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistMove);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistsMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistsMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyPlaylistsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistsMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionTracksMax()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistArrays()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistArrays");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("IdArray", *iPropertyIdArray));
    action->AddOutputParameter(new ParameterRelated("TokenArray", *iPropertyTokenArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistArrays);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionPlaylistArraysChanged()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistArraysChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistArraysChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionRead()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("TrackId"));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionReadList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("TrackIdList"));
    action->AddOutputParameter(new ParameterString("TrackList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionInsert()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Insert");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("AfterTrackId"));
    action->AddInputParameter(new ParameterString("Udn"));
    action->AddInputParameter(new ParameterString("MetadataId"));
    action->AddOutputParameter(new ParameterUint("NewTrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionDeleteId()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("TrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnableActionDeleteAll()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    action->AddInputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoMetadata(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respMetadata;
    Metadata(aVersion, respMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoImagesXml(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respImagesXml;
    ImagesXml(aVersion, respImagesXml);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterImagesXml(aInvocation, "ImagesXml");
    Brn buf_ImagesXml((const TByte*)respImagesXml.c_str(), (TUint)respImagesXml.length());
    respWriterImagesXml.Write(buf_ImagesXml);
    aInvocation.InvocationWriteStringEnd("ImagesXml");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistReadArray(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    std::string respArray;
    PlaylistReadArray(aVersion, Id, respArray);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriterArray(aInvocation, "Array");
    Brn buf_Array((const TByte*)respArray.c_str(), (TUint)respArray.length());
    respWriterArray.Write(buf_Array);
    aInvocation.InvocationWriteBinaryEnd("Array");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistReadList(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_IdList;
    aInvocation.InvocationReadString("IdList", buf_IdList);
    std::string IdList((const char*)buf_IdList.Ptr(), buf_IdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respPlaylistList;
    PlaylistReadList(aVersion, IdList, respPlaylistList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterPlaylistList(aInvocation, "PlaylistList");
    Brn buf_PlaylistList((const TByte*)respPlaylistList.c_str(), (TUint)respPlaylistList.length());
    respWriterPlaylistList.Write(buf_PlaylistList);
    aInvocation.InvocationWriteStringEnd("PlaylistList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistRead(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    std::string respName;
    std::string respDescription;
    uint32_t respImageId;
    PlaylistRead(aVersion, Id, respName, respDescription, respImageId);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterName(aInvocation, "Name");
    Brn buf_Name((const TByte*)respName.c_str(), (TUint)respName.length());
    respWriterName.Write(buf_Name);
    aInvocation.InvocationWriteStringEnd("Name");
    InvocationResponseString respWriterDescription(aInvocation, "Description");
    Brn buf_Description((const TByte*)respDescription.c_str(), (TUint)respDescription.length());
    respWriterDescription.Write(buf_Description);
    aInvocation.InvocationWriteStringEnd("Description");
    InvocationResponseUint respWriterImageId(aInvocation, "ImageId");
    respWriterImageId.Write(respImageId);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetName(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    Brhz buf_Name;
    aInvocation.InvocationReadString("Name", buf_Name);
    std::string Name((const char*)buf_Name.Ptr(), buf_Name.Bytes());
    aInvocation.InvocationReadEnd();
    PlaylistSetName(aVersion, Id, Name);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetDescription(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    Brhz buf_Description;
    aInvocation.InvocationReadString("Description", buf_Description);
    std::string Description((const char*)buf_Description.Ptr(), buf_Description.Bytes());
    aInvocation.InvocationReadEnd();
    PlaylistSetDescription(aVersion, Id, Description);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetImageId(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    PlaylistSetImageId(aVersion, Id, ImageId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistInsert(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz buf_Name;
    aInvocation.InvocationReadString("Name", buf_Name);
    std::string Name((const char*)buf_Name.Ptr(), buf_Name.Bytes());
    Brhz buf_Description;
    aInvocation.InvocationReadString("Description", buf_Description);
    std::string Description((const char*)buf_Description.Ptr(), buf_Description.Bytes());
    uint32_t ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    uint32_t respNewId;
    PlaylistInsert(aVersion, AfterId, Name, Description, ImageId, respNewId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterNewId(aInvocation, "NewId");
    respWriterNewId.Write(respNewId);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistDeleteId(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    PlaylistDeleteId(aVersion, Value);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistMove(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t AfterId = aInvocation.InvocationReadUint("AfterId");
    aInvocation.InvocationReadEnd();
    PlaylistMove(aVersion, Id, AfterId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistsMax(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    PlaylistsMax(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoTracksMax(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    TracksMax(aVersion, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistArrays(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respToken;
    std::string respIdArray;
    std::string respTokenArray;
    PlaylistArrays(aVersion, respToken, respIdArray, respTokenArray);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterToken(aInvocation, "Token");
    respWriterToken.Write(respToken);
    InvocationResponseBinary respWriterIdArray(aInvocation, "IdArray");
    Brn buf_IdArray((const TByte*)respIdArray.c_str(), (TUint)respIdArray.length());
    respWriterIdArray.Write(buf_IdArray);
    aInvocation.InvocationWriteBinaryEnd("IdArray");
    InvocationResponseBinary respWriterTokenArray(aInvocation, "TokenArray");
    Brn buf_TokenArray((const TByte*)respTokenArray.c_str(), (TUint)respTokenArray.length());
    respWriterTokenArray.Write(buf_TokenArray);
    aInvocation.InvocationWriteBinaryEnd("TokenArray");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistArraysChanged(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    bool respValue;
    PlaylistArraysChanged(aVersion, Token, respValue);
	aInvocation.InvocationWriteStart();
    InvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoRead(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    std::string respMetadata;
    Read(aVersion, Id, TrackId, respMetadata);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoReadList(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    Brhz buf_TrackIdList;
    aInvocation.InvocationReadString("TrackIdList", buf_TrackIdList);
    std::string TrackIdList((const char*)buf_TrackIdList.Ptr(), buf_TrackIdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respTrackList;
    ReadList(aVersion, Id, TrackIdList, respTrackList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterTrackList(aInvocation, "TrackList");
    Brn buf_TrackList((const TByte*)respTrackList.c_str(), (TUint)respTrackList.length());
    respWriterTrackList.Write(buf_TrackList);
    aInvocation.InvocationWriteStringEnd("TrackList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoInsert(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t AfterTrackId = aInvocation.InvocationReadUint("AfterTrackId");
    Brhz buf_Udn;
    aInvocation.InvocationReadString("Udn", buf_Udn);
    std::string Udn((const char*)buf_Udn.Ptr(), buf_Udn.Bytes());
    Brhz buf_MetadataId;
    aInvocation.InvocationReadString("MetadataId", buf_MetadataId);
    std::string MetadataId((const char*)buf_MetadataId.Ptr(), buf_MetadataId.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respNewTrackId;
    Insert(aVersion, Id, AfterTrackId, Udn, MetadataId, respNewTrackId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterNewTrackId(aInvocation, "NewTrackId");
    respWriterNewTrackId.Write(respNewTrackId);
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoDeleteId(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    DeleteId(aVersion, Id, TrackId);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoDeleteAll(IDviInvocation& aInvocation, uint32_t aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DeleteAll(aVersion, Id);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::Metadata(uint32_t /*aVersion*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::ImagesXml(uint32_t /*aVersion*/, std::string& /*aImagesXml*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistReadArray(uint32_t /*aVersion*/, uint32_t /*aId*/, std::string& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistReadList(uint32_t /*aVersion*/, const std::string& /*aIdList*/, std::string& /*aPlaylistList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistRead(uint32_t /*aVersion*/, uint32_t /*aId*/, std::string& /*aName*/, std::string& /*aDescription*/, uint32_t& /*aImageId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistSetName(uint32_t /*aVersion*/, uint32_t /*aId*/, const std::string& /*aName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistSetDescription(uint32_t /*aVersion*/, uint32_t /*aId*/, const std::string& /*aDescription*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistSetImageId(uint32_t /*aVersion*/, uint32_t /*aId*/, uint32_t /*aImageId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistInsert(uint32_t /*aVersion*/, uint32_t /*aAfterId*/, const std::string& /*aName*/, const std::string& /*aDescription*/, uint32_t /*aImageId*/, uint32_t& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistDeleteId(uint32_t /*aVersion*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistMove(uint32_t /*aVersion*/, uint32_t /*aId*/, uint32_t /*aAfterId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistsMax(uint32_t /*aVersion*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::TracksMax(uint32_t /*aVersion*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistArrays(uint32_t /*aVersion*/, uint32_t& /*aToken*/, std::string& /*aIdArray*/, std::string& /*aTokenArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistArraysChanged(uint32_t /*aVersion*/, uint32_t /*aToken*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::Read(uint32_t /*aVersion*/, uint32_t /*aId*/, uint32_t /*aTrackId*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::ReadList(uint32_t /*aVersion*/, uint32_t /*aId*/, const std::string& /*aTrackIdList*/, std::string& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::Insert(uint32_t /*aVersion*/, uint32_t /*aId*/, uint32_t /*aAfterTrackId*/, const std::string& /*aUdn*/, const std::string& /*aMetadataId*/, uint32_t& /*aNewTrackId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DeleteId(uint32_t /*aVersion*/, uint32_t /*aId*/, uint32_t /*aTrackId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DeleteAll(uint32_t /*aVersion*/, uint32_t /*aId*/)
{
    ASSERTS();
}

