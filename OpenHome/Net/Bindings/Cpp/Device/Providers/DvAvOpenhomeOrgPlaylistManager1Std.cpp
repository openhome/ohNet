#include "DvAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyMetadata(const std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyMetadata, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyMetadata(std::string& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    const Brx& val = iPropertyMetadata->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyImagesXml(const std::string& aValue)
{
    ASSERT(iPropertyImagesXml != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyImagesXml, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyImagesXml(std::string& aValue)
{
    ASSERT(iPropertyImagesXml != NULL);
    const Brx& val = iPropertyImagesXml->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyIdArray(const std::string& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyIdArray, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyIdArray(std::string& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    const Brx& val = iPropertyIdArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyTokenArray(const std::string& aValue)
{
    ASSERT(iPropertyTokenArray != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyBinary(*iPropertyTokenArray, buf);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyTokenArray(std::string& aValue)
{
    ASSERT(iPropertyTokenArray != NULL);
    const Brx& val = iPropertyTokenArray->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyPlaylistsMax(uint32_t aValue)
{
    ASSERT(iPropertyPlaylistsMax != NULL);
    return SetPropertyUint(*iPropertyPlaylistsMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyPlaylistsMax(uint32_t& aValue)
{
    ASSERT(iPropertyPlaylistsMax != NULL);
    aValue = iPropertyPlaylistsMax->Value();
}

bool DvProviderAvOpenhomeOrgPlaylistManager1Cpp::SetPropertyTracksMax(uint32_t aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::GetPropertyTracksMax(uint32_t& aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    aValue = iPropertyTracksMax->Value();
}

DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DvProviderAvOpenhomeOrgPlaylistManager1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "av.openhome.org", "PlaylistManager", 1)
{
    iPropertyMetadata = NULL;
    iPropertyImagesXml = NULL;
    iPropertyIdArray = NULL;
    iPropertyTokenArray = NULL;
    iPropertyPlaylistsMax = NULL;
    iPropertyTracksMax = NULL;
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnablePropertyImagesXml()
{
    iPropertyImagesXml = new PropertyString(iDvStack.Env(), new ParameterString("ImagesXml"));
    iService->AddProperty(iPropertyImagesXml); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnablePropertyTokenArray()
{
    iPropertyTokenArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("TokenArray"));
    iService->AddProperty(iPropertyTokenArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnablePropertyPlaylistsMax()
{
    iPropertyPlaylistsMax = new PropertyUint(iDvStack.Env(), new ParameterUint("PlaylistsMax"));
    iService->AddProperty(iPropertyPlaylistsMax); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::EnablePropertyTracksMax()
{
    iPropertyTracksMax = new PropertyUint(iDvStack.Env(), new ParameterUint("TracksMax"));
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
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
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

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoMetadata(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respMetadata;
    DvInvocationStd invocation(aInvocation);
    Metadata(invocation, respMetadata);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoImagesXml(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respImagesXml;
    DvInvocationStd invocation(aInvocation);
    ImagesXml(invocation, respImagesXml);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterImagesXml(aInvocation, "ImagesXml");
    Brn buf_ImagesXml((const TByte*)respImagesXml.c_str(), (TUint)respImagesXml.length());
    respWriterImagesXml.Write(buf_ImagesXml);
    aInvocation.InvocationWriteStringEnd("ImagesXml");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistReadArray(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    std::string respArray;
    DvInvocationStd invocation(aInvocation);
    PlaylistReadArray(invocation, Id, respArray);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBinary respWriterArray(aInvocation, "Array");
    Brn buf_Array((const TByte*)respArray.c_str(), (TUint)respArray.length());
    respWriterArray.Write(buf_Array);
    aInvocation.InvocationWriteBinaryEnd("Array");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistReadList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_IdList;
    aInvocation.InvocationReadString("IdList", buf_IdList);
    std::string IdList((const char*)buf_IdList.Ptr(), buf_IdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respPlaylistList;
    DvInvocationStd invocation(aInvocation);
    PlaylistReadList(invocation, IdList, respPlaylistList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterPlaylistList(aInvocation, "PlaylistList");
    Brn buf_PlaylistList((const TByte*)respPlaylistList.c_str(), (TUint)respPlaylistList.length());
    respWriterPlaylistList.Write(buf_PlaylistList);
    aInvocation.InvocationWriteStringEnd("PlaylistList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistRead(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    std::string respName;
    std::string respDescription;
    uint32_t respImageId;
    DvInvocationStd invocation(aInvocation);
    PlaylistRead(invocation, Id, respName, respDescription, respImageId);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterName(aInvocation, "Name");
    Brn buf_Name((const TByte*)respName.c_str(), (TUint)respName.length());
    respWriterName.Write(buf_Name);
    aInvocation.InvocationWriteStringEnd("Name");
    DviInvocationResponseString respWriterDescription(aInvocation, "Description");
    Brn buf_Description((const TByte*)respDescription.c_str(), (TUint)respDescription.length());
    respWriterDescription.Write(buf_Description);
    aInvocation.InvocationWriteStringEnd("Description");
    DviInvocationResponseUint respWriterImageId(aInvocation, "ImageId");
    respWriterImageId.Write(respImageId);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetName(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    Brhz buf_Name;
    aInvocation.InvocationReadString("Name", buf_Name);
    std::string Name((const char*)buf_Name.Ptr(), buf_Name.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    PlaylistSetName(invocation, Id, Name);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetDescription(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    Brhz buf_Description;
    aInvocation.InvocationReadString("Description", buf_Description);
    std::string Description((const char*)buf_Description.Ptr(), buf_Description.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    PlaylistSetDescription(invocation, Id, Description);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistSetImageId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    PlaylistSetImageId(invocation, Id, ImageId);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistInsert(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    PlaylistInsert(invocation, AfterId, Name, Description, ImageId, respNewId);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterNewId(aInvocation, "NewId");
    respWriterNewId.Write(respNewId);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistDeleteId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    PlaylistDeleteId(invocation, Value);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistMove(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t AfterId = aInvocation.InvocationReadUint("AfterId");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    PlaylistMove(invocation, Id, AfterId);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistsMax(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respValue;
    DvInvocationStd invocation(aInvocation);
    PlaylistsMax(invocation, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoTracksMax(IDviInvocation& aInvocation)
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

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistArrays(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respToken;
    std::string respIdArray;
    std::string respTokenArray;
    DvInvocationStd invocation(aInvocation);
    PlaylistArrays(invocation, respToken, respIdArray, respTokenArray);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterToken(aInvocation, "Token");
    respWriterToken.Write(respToken);
    DviInvocationResponseBinary respWriterIdArray(aInvocation, "IdArray");
    Brn buf_IdArray((const TByte*)respIdArray.c_str(), (TUint)respIdArray.length());
    respWriterIdArray.Write(buf_IdArray);
    aInvocation.InvocationWriteBinaryEnd("IdArray");
    DviInvocationResponseBinary respWriterTokenArray(aInvocation, "TokenArray");
    Brn buf_TokenArray((const TByte*)respTokenArray.c_str(), (TUint)respTokenArray.length());
    respWriterTokenArray.Write(buf_TokenArray);
    aInvocation.InvocationWriteBinaryEnd("TokenArray");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoPlaylistArraysChanged(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    bool respValue;
    DvInvocationStd invocation(aInvocation);
    PlaylistArraysChanged(invocation, Token, respValue);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseBool respWriterValue(aInvocation, "Value");
    respWriterValue.Write(respValue);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoRead(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    std::string respMetadata;
    DvInvocationStd invocation(aInvocation);
    Read(invocation, Id, TrackId, respMetadata);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterMetadata(aInvocation, "Metadata");
    Brn buf_Metadata((const TByte*)respMetadata.c_str(), (TUint)respMetadata.length());
    respWriterMetadata.Write(buf_Metadata);
    aInvocation.InvocationWriteStringEnd("Metadata");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoReadList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    Brhz buf_TrackIdList;
    aInvocation.InvocationReadString("TrackIdList", buf_TrackIdList);
    std::string TrackIdList((const char*)buf_TrackIdList.Ptr(), buf_TrackIdList.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respTrackList;
    DvInvocationStd invocation(aInvocation);
    ReadList(invocation, Id, TrackIdList, respTrackList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterTrackList(aInvocation, "TrackList");
    Brn buf_TrackList((const TByte*)respTrackList.c_str(), (TUint)respTrackList.length());
    respWriterTrackList.Write(buf_TrackList);
    aInvocation.InvocationWriteStringEnd("TrackList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoInsert(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t AfterTrackId = aInvocation.InvocationReadUint("AfterTrackId");
    Brhz buf_Metadata;
    aInvocation.InvocationReadString("Metadata", buf_Metadata);
    std::string Metadata((const char*)buf_Metadata.Ptr(), buf_Metadata.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respNewTrackId;
    DvInvocationStd invocation(aInvocation);
    Insert(invocation, Id, AfterTrackId, Metadata, respNewTrackId);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterNewTrackId(aInvocation, "NewTrackId");
    respWriterNewTrackId.Write(respNewTrackId);
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoDeleteId(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    uint32_t TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteId(invocation, Id, TrackId);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DoDeleteAll(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteAll(invocation, Id);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::Metadata(IDvInvocationStd& /*aInvocation*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::ImagesXml(IDvInvocationStd& /*aInvocation*/, std::string& /*aImagesXml*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistReadArray(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, std::string& /*aArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistReadList(IDvInvocationStd& /*aInvocation*/, const std::string& /*aIdList*/, std::string& /*aPlaylistList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistRead(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, std::string& /*aName*/, std::string& /*aDescription*/, uint32_t& /*aImageId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistSetName(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, const std::string& /*aName*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistSetDescription(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, const std::string& /*aDescription*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistSetImageId(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, uint32_t /*aImageId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistInsert(IDvInvocationStd& /*aInvocation*/, uint32_t /*aAfterId*/, const std::string& /*aName*/, const std::string& /*aDescription*/, uint32_t /*aImageId*/, uint32_t& /*aNewId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistDeleteId(IDvInvocationStd& /*aInvocation*/, uint32_t /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistMove(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, uint32_t /*aAfterId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistsMax(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::TracksMax(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistArrays(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aToken*/, std::string& /*aIdArray*/, std::string& /*aTokenArray*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::PlaylistArraysChanged(IDvInvocationStd& /*aInvocation*/, uint32_t /*aToken*/, bool& /*aValue*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::Read(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, uint32_t /*aTrackId*/, std::string& /*aMetadata*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::ReadList(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, const std::string& /*aTrackIdList*/, std::string& /*aTrackList*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::Insert(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, uint32_t /*aAfterTrackId*/, const std::string& /*aMetadata*/, uint32_t& /*aNewTrackId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DeleteId(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/, uint32_t /*aTrackId*/)
{
    ASSERTS();
}

void DvProviderAvOpenhomeOrgPlaylistManager1Cpp::DeleteAll(IDvInvocationStd& /*aInvocation*/, uint32_t /*aId*/)
{
    ASSERTS();
}

