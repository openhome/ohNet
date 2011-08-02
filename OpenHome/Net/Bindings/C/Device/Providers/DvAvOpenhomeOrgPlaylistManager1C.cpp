#include "DvAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderAvOpenhomeOrgPlaylistManager1C : public DvProvider
{
public:
    DvProviderAvOpenhomeOrgPlaylistManager1C(DvDeviceC aDevice);
    TBool SetPropertyMetadata(const Brx& aValue);
    void GetPropertyMetadata(Brhz& aValue);
    TBool SetPropertyImagesXml(const Brx& aValue);
    void GetPropertyImagesXml(Brhz& aValue);
    TBool SetPropertyIdArray(const Brx& aValue);
    void GetPropertyIdArray(Brh& aValue);
    TBool SetPropertyTokenArray(const Brx& aValue);
    void GetPropertyTokenArray(Brh& aValue);
    TBool SetPropertyPlaylistsMax(TUint aValue);
    void GetPropertyPlaylistsMax(TUint& aValue);
    TBool SetPropertyTracksMax(TUint aValue);
    void GetPropertyTracksMax(TUint& aValue);
    void EnableActionMetadata(CallbackPlaylistManager1Metadata aCallback, void* aPtr);
    void EnableActionImagesXml(CallbackPlaylistManager1ImagesXml aCallback, void* aPtr);
    void EnableActionPlaylistReadArray(CallbackPlaylistManager1PlaylistReadArray aCallback, void* aPtr);
    void EnableActionPlaylistReadMetadata(CallbackPlaylistManager1PlaylistReadMetadata aCallback, void* aPtr);
    void EnableActionPlaylistRead(CallbackPlaylistManager1PlaylistRead aCallback, void* aPtr);
    void EnableActionPlaylistUpdate(CallbackPlaylistManager1PlaylistUpdate aCallback, void* aPtr);
    void EnableActionPlaylistInsert(CallbackPlaylistManager1PlaylistInsert aCallback, void* aPtr);
    void EnableActionPlaylistDeleteId(CallbackPlaylistManager1PlaylistDeleteId aCallback, void* aPtr);
    void EnableActionPlaylistsMax(CallbackPlaylistManager1PlaylistsMax aCallback, void* aPtr);
    void EnableActionTracksMax(CallbackPlaylistManager1TracksMax aCallback, void* aPtr);
    void EnableActionPlaylistArrays(CallbackPlaylistManager1PlaylistArrays aCallback, void* aPtr);
    void EnableActionPlaylistArraysChanged(CallbackPlaylistManager1PlaylistArraysChanged aCallback, void* aPtr);
    void EnableActionRead(CallbackPlaylistManager1Read aCallback, void* aPtr);
    void EnableActionReadList(CallbackPlaylistManager1ReadList aCallback, void* aPtr);
    void EnableActionInsert(CallbackPlaylistManager1Insert aCallback, void* aPtr);
    void EnableActionDeleteId(CallbackPlaylistManager1DeleteId aCallback, void* aPtr);
    void EnableActionDeleteAll(CallbackPlaylistManager1DeleteAll aCallback, void* aPtr);
private:
    void DoMetadata(IDviInvocation& aInvocation, TUint aVersion);
    void DoImagesXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistReadArray(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistReadMetadata(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistUpdate(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistInsert(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistDeleteId(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistsMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoTracksMax(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistArrays(IDviInvocation& aInvocation, TUint aVersion);
    void DoPlaylistArraysChanged(IDviInvocation& aInvocation, TUint aVersion);
    void DoRead(IDviInvocation& aInvocation, TUint aVersion);
    void DoReadList(IDviInvocation& aInvocation, TUint aVersion);
    void DoInsert(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteId(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackPlaylistManager1Metadata iCallbackMetadata;
    void* iPtrMetadata;
    CallbackPlaylistManager1ImagesXml iCallbackImagesXml;
    void* iPtrImagesXml;
    CallbackPlaylistManager1PlaylistReadArray iCallbackPlaylistReadArray;
    void* iPtrPlaylistReadArray;
    CallbackPlaylistManager1PlaylistReadMetadata iCallbackPlaylistReadMetadata;
    void* iPtrPlaylistReadMetadata;
    CallbackPlaylistManager1PlaylistRead iCallbackPlaylistRead;
    void* iPtrPlaylistRead;
    CallbackPlaylistManager1PlaylistUpdate iCallbackPlaylistUpdate;
    void* iPtrPlaylistUpdate;
    CallbackPlaylistManager1PlaylistInsert iCallbackPlaylistInsert;
    void* iPtrPlaylistInsert;
    CallbackPlaylistManager1PlaylistDeleteId iCallbackPlaylistDeleteId;
    void* iPtrPlaylistDeleteId;
    CallbackPlaylistManager1PlaylistsMax iCallbackPlaylistsMax;
    void* iPtrPlaylistsMax;
    CallbackPlaylistManager1TracksMax iCallbackTracksMax;
    void* iPtrTracksMax;
    CallbackPlaylistManager1PlaylistArrays iCallbackPlaylistArrays;
    void* iPtrPlaylistArrays;
    CallbackPlaylistManager1PlaylistArraysChanged iCallbackPlaylistArraysChanged;
    void* iPtrPlaylistArraysChanged;
    CallbackPlaylistManager1Read iCallbackRead;
    void* iPtrRead;
    CallbackPlaylistManager1ReadList iCallbackReadList;
    void* iPtrReadList;
    CallbackPlaylistManager1Insert iCallbackInsert;
    void* iPtrInsert;
    CallbackPlaylistManager1DeleteId iCallbackDeleteId;
    void* iPtrDeleteId;
    CallbackPlaylistManager1DeleteAll iCallbackDeleteAll;
    void* iPtrDeleteAll;
    PropertyString* iPropertyMetadata;
    PropertyString* iPropertyImagesXml;
    PropertyBinary* iPropertyIdArray;
    PropertyBinary* iPropertyTokenArray;
    PropertyUint* iPropertyPlaylistsMax;
    PropertyUint* iPropertyTracksMax;
};

DvProviderAvOpenhomeOrgPlaylistManager1C::DvProviderAvOpenhomeOrgPlaylistManager1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "av.openhome.org", "PlaylistManager", 1)
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

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyMetadata(const Brx& aValue)
{
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyMetadata(Brhz& aValue)
{
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyImagesXml(const Brx& aValue)
{
    return SetPropertyString(*iPropertyImagesXml, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyImagesXml(Brhz& aValue)
{
    aValue.Set(iPropertyImagesXml->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyIdArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyIdArray(Brh& aValue)
{
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyTokenArray(const Brx& aValue)
{
    return SetPropertyBinary(*iPropertyTokenArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyTokenArray(Brh& aValue)
{
    aValue.Set(iPropertyTokenArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyPlaylistsMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyPlaylistsMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyPlaylistsMax(TUint& aValue)
{
    aValue = iPropertyPlaylistsMax->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyTracksMax(TUint aValue)
{
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyTracksMax(TUint& aValue)
{
    aValue = iPropertyTracksMax->Value();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionMetadata(CallbackPlaylistManager1Metadata aCallback, void* aPtr)
{
    iCallbackMetadata = aCallback;
    iPtrMetadata = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Metadata");
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionImagesXml(CallbackPlaylistManager1ImagesXml aCallback, void* aPtr)
{
    iCallbackImagesXml = aCallback;
    iPtrImagesXml = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImagesXml");
    action->AddOutputParameter(new ParameterRelated("ImagesXml", *iPropertyImagesXml));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoImagesXml);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistReadArray(CallbackPlaylistManager1PlaylistReadArray aCallback, void* aPtr)
{
    iCallbackPlaylistReadArray = aCallback;
    iPtrPlaylistReadArray = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadArray");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddOutputParameter(new ParameterRelated("Array", *iPropertyIdArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadArray);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistReadMetadata(CallbackPlaylistManager1PlaylistReadMetadata aCallback, void* aPtr)
{
    iCallbackPlaylistReadMetadata = aCallback;
    iPtrPlaylistReadMetadata = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadMetadata");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadMetadata);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistRead(CallbackPlaylistManager1PlaylistRead aCallback, void* aPtr)
{
    iCallbackPlaylistRead = aCallback;
    iPtrPlaylistRead = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistRead");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddOutputParameter(new ParameterString("Name"));
    action->AddOutputParameter(new ParameterString("Description"));
    action->AddOutputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistUpdate(CallbackPlaylistManager1PlaylistUpdate aCallback, void* aPtr)
{
    iCallbackPlaylistUpdate = aCallback;
    iPtrPlaylistUpdate = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistUpdate");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Name"));
    action->AddInputParameter(new ParameterString("Description"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistUpdate);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistInsert(CallbackPlaylistManager1PlaylistInsert aCallback, void* aPtr)
{
    iCallbackPlaylistInsert = aCallback;
    iPtrPlaylistInsert = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistInsert");
    action->AddInputParameter(new ParameterUint("AfterId"));
    action->AddInputParameter(new ParameterString("Name"));
    action->AddInputParameter(new ParameterString("Description"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    action->AddOutputParameter(new ParameterUint("NewId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistDeleteId(CallbackPlaylistManager1PlaylistDeleteId aCallback, void* aPtr)
{
    iCallbackPlaylistDeleteId = aCallback;
    iPtrPlaylistDeleteId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistDeleteId");
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistsMax(CallbackPlaylistManager1PlaylistsMax aCallback, void* aPtr)
{
    iCallbackPlaylistsMax = aCallback;
    iPtrPlaylistsMax = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistsMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyPlaylistsMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistsMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionTracksMax(CallbackPlaylistManager1TracksMax aCallback, void* aPtr)
{
    iCallbackTracksMax = aCallback;
    iPtrTracksMax = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("TracksMax");
    action->AddOutputParameter(new ParameterRelated("Value", *iPropertyTracksMax));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoTracksMax);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistArrays(CallbackPlaylistManager1PlaylistArrays aCallback, void* aPtr)
{
    iCallbackPlaylistArrays = aCallback;
    iPtrPlaylistArrays = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistArrays");
    action->AddOutputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterRelated("IdArray", *iPropertyIdArray));
    action->AddOutputParameter(new ParameterRelated("TokenArray", *iPropertyTokenArray));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistArrays);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistArraysChanged(CallbackPlaylistManager1PlaylistArraysChanged aCallback, void* aPtr)
{
    iCallbackPlaylistArraysChanged = aCallback;
    iPtrPlaylistArraysChanged = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistArraysChanged");
    action->AddInputParameter(new ParameterUint("Token"));
    action->AddOutputParameter(new ParameterBool("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistArraysChanged);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionRead(CallbackPlaylistManager1Read aCallback, void* aPtr)
{
    iCallbackRead = aCallback;
    iPtrRead = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Read");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("TrackId"));
    action->AddOutputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoRead);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionReadList(CallbackPlaylistManager1ReadList aCallback, void* aPtr)
{
    iCallbackReadList = aCallback;
    iPtrReadList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ReadList");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("TrackIdList"));
    action->AddOutputParameter(new ParameterString("TrackList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoReadList);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionInsert(CallbackPlaylistManager1Insert aCallback, void* aPtr)
{
    iCallbackInsert = aCallback;
    iPtrInsert = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Insert");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("AfterTrackId"));
    action->AddInputParameter(new ParameterString("Udn"));
    action->AddInputParameter(new ParameterString("MetadataId"));
    action->AddOutputParameter(new ParameterUint("NewTrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionDeleteId(CallbackPlaylistManager1DeleteId aCallback, void* aPtr)
{
    iCallbackDeleteId = aCallback;
    iPtrDeleteId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterUint("TrackId"));
    action->AddInputParameter(new ParameterUint("Value"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionDeleteAll(CallbackPlaylistManager1DeleteAll aCallback, void* aPtr)
{
    iCallbackDeleteAll = aCallback;
    iPtrDeleteAll = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    action->AddInputParameter(new ParameterUint("TrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoMetadata(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Metadata;
    ASSERT(iCallbackMetadata != NULL);
    if (0 != iCallbackMetadata(iPtrMetadata, aVersion, &Metadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    resp.Start();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoImagesXml(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ImagesXml;
    ASSERT(iCallbackImagesXml != NULL);
    if (0 != iCallbackImagesXml(iPtrImagesXml, aVersion, &ImagesXml)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respImagesXml(aInvocation, "ImagesXml");
    resp.Start();
    Brhz bufImagesXml((const TChar*)ImagesXml);
    OhNetFreeExternal(ImagesXml);
    respImagesXml.Write(bufImagesXml);
    respImagesXml.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadArray(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Array;
    uint32_t ArrayLen;
    ASSERT(iCallbackPlaylistReadArray != NULL);
    if (0 != iCallbackPlaylistReadArray(iPtrPlaylistReadArray, aVersion, Id, &Array, &ArrayLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBinary respArray(aInvocation, "Array");
    resp.Start();
    Brh bufArray;
    bufArray.Set((const TByte*)Array, ArrayLen);
    OhNetFreeExternal(Array);
    respArray.Write(bufArray);
    respArray.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadMetadata(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Metadata;
    ASSERT(iCallbackPlaylistReadMetadata != NULL);
    if (0 != iCallbackPlaylistReadMetadata(iPtrPlaylistReadMetadata, aVersion, (const char*)IdList.Ptr(), &Metadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    resp.Start();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Name;
    char* Description;
    uint32_t ImageId;
    ASSERT(iCallbackPlaylistRead != NULL);
    if (0 != iCallbackPlaylistRead(iPtrPlaylistRead, aVersion, Id, &Name, &Description, &ImageId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respName(aInvocation, "Name");
    InvocationResponseString respDescription(aInvocation, "Description");
    InvocationResponseUint respImageId(aInvocation, "ImageId");
    resp.Start();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    Brhz bufDescription((const TChar*)Description);
    OhNetFreeExternal(Description);
    respDescription.Write(bufDescription);
    respDescription.WriteFlush();
    respImageId.Write(ImageId);
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistUpdate(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz Name;
    aInvocation.InvocationReadString("Name", Name);
    Brhz Description;
    aInvocation.InvocationReadString("Description", Description);
    TUint ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPlaylistUpdate != NULL);
    if (0 != iCallbackPlaylistUpdate(iPtrPlaylistUpdate, aVersion, Id, (const char*)Name.Ptr(), (const char*)Description.Ptr(), ImageId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz Name;
    aInvocation.InvocationReadString("Name", Name);
    Brhz Description;
    aInvocation.InvocationReadString("Description", Description);
    TUint ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t NewId;
    ASSERT(iCallbackPlaylistInsert != NULL);
    if (0 != iCallbackPlaylistInsert(iPtrPlaylistInsert, aVersion, AfterId, (const char*)Name.Ptr(), (const char*)Description.Ptr(), ImageId, &NewId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respNewId(aInvocation, "NewId");
    resp.Start();
    respNewId.Write(NewId);
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistDeleteId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackPlaylistDeleteId != NULL);
    if (0 != iCallbackPlaylistDeleteId(iPtrPlaylistDeleteId, aVersion, Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistsMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackPlaylistsMax != NULL);
    if (0 != iCallbackPlaylistsMax(iPtrPlaylistsMax, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respValue(aInvocation, "Value");
    resp.Start();
    respValue.Write(Value);
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoTracksMax(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackTracksMax != NULL);
    if (0 != iCallbackTracksMax(iPtrTracksMax, aVersion, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respValue(aInvocation, "Value");
    resp.Start();
    respValue.Write(Value);
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistArrays(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Token;
    char* IdArray;
    uint32_t IdArrayLen;
    char* TokenArray;
    uint32_t TokenArrayLen;
    ASSERT(iCallbackPlaylistArrays != NULL);
    if (0 != iCallbackPlaylistArrays(iPtrPlaylistArrays, aVersion, &Token, &IdArray, &IdArrayLen, &TokenArray, &TokenArrayLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respToken(aInvocation, "Token");
    InvocationResponseBinary respIdArray(aInvocation, "IdArray");
    InvocationResponseBinary respTokenArray(aInvocation, "TokenArray");
    resp.Start();
    respToken.Write(Token);
    Brh bufIdArray;
    bufIdArray.Set((const TByte*)IdArray, IdArrayLen);
    OhNetFreeExternal(IdArray);
    respIdArray.Write(bufIdArray);
    respIdArray.WriteFlush();
    Brh bufTokenArray;
    bufTokenArray.Set((const TByte*)TokenArray, TokenArrayLen);
    OhNetFreeExternal(TokenArray);
    respTokenArray.Write(bufTokenArray);
    respTokenArray.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistArraysChanged(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackPlaylistArraysChanged != NULL);
    if (0 != iCallbackPlaylistArraysChanged(iPtrPlaylistArraysChanged, aVersion, Token, &Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBool respValue(aInvocation, "Value");
    resp.Start();
    respValue.Write((Value!=0));
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoRead(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Metadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, aVersion, Id, TrackId, &Metadata)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respMetadata(aInvocation, "Metadata");
    resp.Start();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoReadList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz TrackIdList;
    aInvocation.InvocationReadString("TrackIdList", TrackIdList);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* TrackList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, aVersion, Id, (const char*)TrackIdList.Ptr(), &TrackList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respTrackList(aInvocation, "TrackList");
    resp.Start();
    Brhz bufTrackList((const TChar*)TrackList);
    OhNetFreeExternal(TrackList);
    respTrackList.Write(bufTrackList);
    respTrackList.WriteFlush();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoInsert(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint AfterTrackId = aInvocation.InvocationReadUint("AfterTrackId");
    Brhz Udn;
    aInvocation.InvocationReadString("Udn", Udn);
    Brhz MetadataId;
    aInvocation.InvocationReadString("MetadataId", MetadataId);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t NewTrackId;
    ASSERT(iCallbackInsert != NULL);
    if (0 != iCallbackInsert(iPtrInsert, aVersion, Id, AfterTrackId, (const char*)Udn.Ptr(), (const char*)MetadataId.Ptr(), &NewTrackId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respNewTrackId(aInvocation, "NewTrackId");
    resp.Start();
    respNewTrackId.Write(NewTrackId);
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteId(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDeleteId != NULL);
    if (0 != iCallbackDeleteId(iPtrDeleteId, aVersion, TrackId, Value)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteAll(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDeleteAll != NULL);
    if (0 != iCallbackDeleteAll(iPtrDeleteAll, aVersion, TrackId)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle STDCALL DvProviderAvOpenhomeOrgPlaylistManager1Create(DvDeviceC aDevice)
{
	return new DvProviderAvOpenhomeOrgPlaylistManager1C(aDevice);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionMetadata(THandle aProvider, CallbackPlaylistManager1Metadata aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionMetadata(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionImagesXml(THandle aProvider, CallbackPlaylistManager1ImagesXml aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionImagesXml(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadArray(THandle aProvider, CallbackPlaylistManager1PlaylistReadArray aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistReadArray(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadMetadata(THandle aProvider, CallbackPlaylistManager1PlaylistReadMetadata aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistReadMetadata(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistRead(THandle aProvider, CallbackPlaylistManager1PlaylistRead aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistRead(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistUpdate(THandle aProvider, CallbackPlaylistManager1PlaylistUpdate aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistUpdate(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistInsert(THandle aProvider, CallbackPlaylistManager1PlaylistInsert aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistInsert(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistDeleteId(THandle aProvider, CallbackPlaylistManager1PlaylistDeleteId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistDeleteId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistsMax(THandle aProvider, CallbackPlaylistManager1PlaylistsMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistsMax(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionTracksMax(THandle aProvider, CallbackPlaylistManager1TracksMax aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionTracksMax(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistArrays(THandle aProvider, CallbackPlaylistManager1PlaylistArrays aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistArrays(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistArraysChanged(THandle aProvider, CallbackPlaylistManager1PlaylistArraysChanged aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistArraysChanged(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionRead(THandle aProvider, CallbackPlaylistManager1Read aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionRead(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionReadList(THandle aProvider, CallbackPlaylistManager1ReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionReadList(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionInsert(THandle aProvider, CallbackPlaylistManager1Insert aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionInsert(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionDeleteId(THandle aProvider, CallbackPlaylistManager1DeleteId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionDeleteId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionDeleteAll(THandle aProvider, CallbackPlaylistManager1DeleteAll aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionDeleteAll(aCallback, aPtr);
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyMetadata(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->SetPropertyMetadata(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyMetadata(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->GetPropertyMetadata(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyImagesXml(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->SetPropertyImagesXml(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyImagesXml(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->GetPropertyImagesXml(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyIdArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->SetPropertyIdArray(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyIdArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->GetPropertyIdArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyTokenArray(THandle aProvider, const char* aValue, uint32_t aValueLen, uint32_t* aChanged)
{
    Brh buf;
    buf.Set((const TByte*)aValue, aValueLen);
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->SetPropertyTokenArray(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyTokenArray(THandle aProvider, char** aValue, uint32_t* aValueLen)
{
    Brh buf;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->GetPropertyTokenArray(buf);
    *aValueLen = buf.Bytes();
    *aValue = (char*)buf.Extract();
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyPlaylistsMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->SetPropertyPlaylistsMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyPlaylistsMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->GetPropertyPlaylistsMax(val);
    *aValue = val;
}

int32_t STDCALL DvProviderAvOpenhomeOrgPlaylistManager1SetPropertyTracksMax(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->SetPropertyTracksMax(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1GetPropertyTracksMax(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->GetPropertyTracksMax(val);
    *aValue = val;
}

