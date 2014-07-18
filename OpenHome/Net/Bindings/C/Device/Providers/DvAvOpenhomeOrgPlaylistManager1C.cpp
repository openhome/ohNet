#include "DvAvOpenhomeOrgPlaylistManager1.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

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
    void EnablePropertyMetadata();
    void EnablePropertyImagesXml();
    void EnablePropertyIdArray();
    void EnablePropertyTokenArray();
    void EnablePropertyPlaylistsMax();
    void EnablePropertyTracksMax();
    void EnableActionMetadata(CallbackPlaylistManager1Metadata aCallback, void* aPtr);
    void EnableActionImagesXml(CallbackPlaylistManager1ImagesXml aCallback, void* aPtr);
    void EnableActionPlaylistReadArray(CallbackPlaylistManager1PlaylistReadArray aCallback, void* aPtr);
    void EnableActionPlaylistReadList(CallbackPlaylistManager1PlaylistReadList aCallback, void* aPtr);
    void EnableActionPlaylistRead(CallbackPlaylistManager1PlaylistRead aCallback, void* aPtr);
    void EnableActionPlaylistSetName(CallbackPlaylistManager1PlaylistSetName aCallback, void* aPtr);
    void EnableActionPlaylistSetDescription(CallbackPlaylistManager1PlaylistSetDescription aCallback, void* aPtr);
    void EnableActionPlaylistSetImageId(CallbackPlaylistManager1PlaylistSetImageId aCallback, void* aPtr);
    void EnableActionPlaylistInsert(CallbackPlaylistManager1PlaylistInsert aCallback, void* aPtr);
    void EnableActionPlaylistDeleteId(CallbackPlaylistManager1PlaylistDeleteId aCallback, void* aPtr);
    void EnableActionPlaylistMove(CallbackPlaylistManager1PlaylistMove aCallback, void* aPtr);
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
    void DoMetadata(IDviInvocation& aInvocation);
    void DoImagesXml(IDviInvocation& aInvocation);
    void DoPlaylistReadArray(IDviInvocation& aInvocation);
    void DoPlaylistReadList(IDviInvocation& aInvocation);
    void DoPlaylistRead(IDviInvocation& aInvocation);
    void DoPlaylistSetName(IDviInvocation& aInvocation);
    void DoPlaylistSetDescription(IDviInvocation& aInvocation);
    void DoPlaylistSetImageId(IDviInvocation& aInvocation);
    void DoPlaylistInsert(IDviInvocation& aInvocation);
    void DoPlaylistDeleteId(IDviInvocation& aInvocation);
    void DoPlaylistMove(IDviInvocation& aInvocation);
    void DoPlaylistsMax(IDviInvocation& aInvocation);
    void DoTracksMax(IDviInvocation& aInvocation);
    void DoPlaylistArrays(IDviInvocation& aInvocation);
    void DoPlaylistArraysChanged(IDviInvocation& aInvocation);
    void DoRead(IDviInvocation& aInvocation);
    void DoReadList(IDviInvocation& aInvocation);
    void DoInsert(IDviInvocation& aInvocation);
    void DoDeleteId(IDviInvocation& aInvocation);
    void DoDeleteAll(IDviInvocation& aInvocation);
private:
    CallbackPlaylistManager1Metadata iCallbackMetadata;
    void* iPtrMetadata;
    CallbackPlaylistManager1ImagesXml iCallbackImagesXml;
    void* iPtrImagesXml;
    CallbackPlaylistManager1PlaylistReadArray iCallbackPlaylistReadArray;
    void* iPtrPlaylistReadArray;
    CallbackPlaylistManager1PlaylistReadList iCallbackPlaylistReadList;
    void* iPtrPlaylistReadList;
    CallbackPlaylistManager1PlaylistRead iCallbackPlaylistRead;
    void* iPtrPlaylistRead;
    CallbackPlaylistManager1PlaylistSetName iCallbackPlaylistSetName;
    void* iPtrPlaylistSetName;
    CallbackPlaylistManager1PlaylistSetDescription iCallbackPlaylistSetDescription;
    void* iPtrPlaylistSetDescription;
    CallbackPlaylistManager1PlaylistSetImageId iCallbackPlaylistSetImageId;
    void* iPtrPlaylistSetImageId;
    CallbackPlaylistManager1PlaylistInsert iCallbackPlaylistInsert;
    void* iPtrPlaylistInsert;
    CallbackPlaylistManager1PlaylistDeleteId iCallbackPlaylistDeleteId;
    void* iPtrPlaylistDeleteId;
    CallbackPlaylistManager1PlaylistMove iCallbackPlaylistMove;
    void* iPtrPlaylistMove;
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
    iPropertyMetadata = NULL;
    iPropertyImagesXml = NULL;
    iPropertyIdArray = NULL;
    iPropertyTokenArray = NULL;
    iPropertyPlaylistsMax = NULL;
    iPropertyTracksMax = NULL;
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyMetadata(const Brx& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    return SetPropertyString(*iPropertyMetadata, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyMetadata(Brhz& aValue)
{
    ASSERT(iPropertyMetadata != NULL);
    aValue.Set(iPropertyMetadata->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyImagesXml(const Brx& aValue)
{
    ASSERT(iPropertyImagesXml != NULL);
    return SetPropertyString(*iPropertyImagesXml, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyImagesXml(Brhz& aValue)
{
    ASSERT(iPropertyImagesXml != NULL);
    aValue.Set(iPropertyImagesXml->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyIdArray(const Brx& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    return SetPropertyBinary(*iPropertyIdArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyIdArray(Brh& aValue)
{
    ASSERT(iPropertyIdArray != NULL);
    aValue.Set(iPropertyIdArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyTokenArray(const Brx& aValue)
{
    ASSERT(iPropertyTokenArray != NULL);
    return SetPropertyBinary(*iPropertyTokenArray, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyTokenArray(Brh& aValue)
{
    ASSERT(iPropertyTokenArray != NULL);
    aValue.Set(iPropertyTokenArray->Value());
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyPlaylistsMax(TUint aValue)
{
    ASSERT(iPropertyPlaylistsMax != NULL);
    return SetPropertyUint(*iPropertyPlaylistsMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyPlaylistsMax(TUint& aValue)
{
    ASSERT(iPropertyPlaylistsMax != NULL);
    aValue = iPropertyPlaylistsMax->Value();
}

TBool DvProviderAvOpenhomeOrgPlaylistManager1C::SetPropertyTracksMax(TUint aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    return SetPropertyUint(*iPropertyTracksMax, aValue);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::GetPropertyTracksMax(TUint& aValue)
{
    ASSERT(iPropertyTracksMax != NULL);
    aValue = iPropertyTracksMax->Value();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnablePropertyMetadata()
{
    iPropertyMetadata = new PropertyString(iDvStack.Env(), new ParameterString("Metadata"));
    iService->AddProperty(iPropertyMetadata); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnablePropertyImagesXml()
{
    iPropertyImagesXml = new PropertyString(iDvStack.Env(), new ParameterString("ImagesXml"));
    iService->AddProperty(iPropertyImagesXml); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnablePropertyIdArray()
{
    iPropertyIdArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("IdArray"));
    iService->AddProperty(iPropertyIdArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnablePropertyTokenArray()
{
    iPropertyTokenArray = new PropertyBinary(iDvStack.Env(), new ParameterBinary("TokenArray"));
    iService->AddProperty(iPropertyTokenArray); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnablePropertyPlaylistsMax()
{
    iPropertyPlaylistsMax = new PropertyUint(iDvStack.Env(), new ParameterUint("PlaylistsMax"));
    iService->AddProperty(iPropertyPlaylistsMax); // passes ownership
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnablePropertyTracksMax()
{
    iPropertyTracksMax = new PropertyUint(iDvStack.Env(), new ParameterUint("TracksMax"));
    iService->AddProperty(iPropertyTracksMax); // passes ownership
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

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistReadList(CallbackPlaylistManager1PlaylistReadList aCallback, void* aPtr)
{
    iCallbackPlaylistReadList = aCallback;
    iPtrPlaylistReadList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistReadList");
    action->AddInputParameter(new ParameterString("IdList"));
    action->AddOutputParameter(new ParameterString("PlaylistList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadList);
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

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistSetName(CallbackPlaylistManager1PlaylistSetName aCallback, void* aPtr)
{
    iCallbackPlaylistSetName = aCallback;
    iPtrPlaylistSetName = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetName");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Name"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistSetName);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistSetDescription(CallbackPlaylistManager1PlaylistSetDescription aCallback, void* aPtr)
{
    iCallbackPlaylistSetDescription = aCallback;
    iPtrPlaylistSetDescription = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetDescription");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterString("Description"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistSetDescription);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistSetImageId(CallbackPlaylistManager1PlaylistSetImageId aCallback, void* aPtr)
{
    iCallbackPlaylistSetImageId = aCallback;
    iPtrPlaylistSetImageId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistSetImageId");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("ImageId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistSetImageId);
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

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionPlaylistMove(CallbackPlaylistManager1PlaylistMove aCallback, void* aPtr)
{
    iCallbackPlaylistMove = aCallback;
    iPtrPlaylistMove = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("PlaylistMove");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("AfterId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistMove);
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
    action->AddInputParameter(new ParameterRelated("Metadata", *iPropertyMetadata));
    action->AddOutputParameter(new ParameterUint("NewTrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoInsert);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionDeleteId(CallbackPlaylistManager1DeleteId aCallback, void* aPtr)
{
    iCallbackDeleteId = aCallback;
    iPtrDeleteId = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteId");
    action->AddInputParameter(new ParameterUint("Id"));
    action->AddInputParameter(new ParameterUint("TrackId"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteId);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::EnableActionDeleteAll(CallbackPlaylistManager1DeleteAll aCallback, void* aPtr)
{
    iCallbackDeleteAll = aCallback;
    iPtrDeleteAll = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteAll");
    action->AddInputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteAll);
    iService->AddAction(action, functor);
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoMetadata(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Metadata;
    ASSERT(iCallbackMetadata != NULL);
    if (0 != iCallbackMetadata(iPtrMetadata, invocationC, invocationCPtr, &Metadata)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    invocation.StartResponse();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoImagesXml(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ImagesXml;
    ASSERT(iCallbackImagesXml != NULL);
    if (0 != iCallbackImagesXml(iPtrImagesXml, invocationC, invocationCPtr, &ImagesXml)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respImagesXml(aInvocation, "ImagesXml");
    invocation.StartResponse();
    Brhz bufImagesXml((const TChar*)ImagesXml);
    OhNetFreeExternal(ImagesXml);
    respImagesXml.Write(bufImagesXml);
    respImagesXml.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadArray(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Array;
    uint32_t ArrayLen;
    ASSERT(iCallbackPlaylistReadArray != NULL);
    if (0 != iCallbackPlaylistReadArray(iPtrPlaylistReadArray, invocationC, invocationCPtr, Id, &Array, &ArrayLen)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBinary respArray(aInvocation, "Array");
    invocation.StartResponse();
    Brh bufArray;
    bufArray.Set((const TByte*)Array, ArrayLen);
    OhNetFreeExternal(Array);
    respArray.Write(bufArray);
    respArray.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistReadList(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz IdList;
    aInvocation.InvocationReadString("IdList", IdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* PlaylistList;
    ASSERT(iCallbackPlaylistReadList != NULL);
    if (0 != iCallbackPlaylistReadList(iPtrPlaylistReadList, invocationC, invocationCPtr, (const char*)IdList.Ptr(), &PlaylistList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respPlaylistList(aInvocation, "PlaylistList");
    invocation.StartResponse();
    Brhz bufPlaylistList((const TChar*)PlaylistList);
    OhNetFreeExternal(PlaylistList);
    respPlaylistList.Write(bufPlaylistList);
    respPlaylistList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistRead(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Name;
    char* Description;
    uint32_t ImageId;
    ASSERT(iCallbackPlaylistRead != NULL);
    if (0 != iCallbackPlaylistRead(iPtrPlaylistRead, invocationC, invocationCPtr, Id, &Name, &Description, &ImageId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respName(aInvocation, "Name");
    DviInvocationResponseString respDescription(aInvocation, "Description");
    DviInvocationResponseUint respImageId(aInvocation, "ImageId");
    invocation.StartResponse();
    Brhz bufName((const TChar*)Name);
    OhNetFreeExternal(Name);
    respName.Write(bufName);
    respName.WriteFlush();
    Brhz bufDescription((const TChar*)Description);
    OhNetFreeExternal(Description);
    respDescription.Write(bufDescription);
    respDescription.WriteFlush();
    respImageId.Write(ImageId);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistSetName(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz Name;
    aInvocation.InvocationReadString("Name", Name);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlaylistSetName != NULL);
    if (0 != iCallbackPlaylistSetName(iPtrPlaylistSetName, invocationC, invocationCPtr, Id, (const char*)Name.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistSetDescription(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz Description;
    aInvocation.InvocationReadString("Description", Description);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlaylistSetDescription != NULL);
    if (0 != iCallbackPlaylistSetDescription(iPtrPlaylistSetDescription, invocationC, invocationCPtr, Id, (const char*)Description.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistSetImageId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlaylistSetImageId != NULL);
    if (0 != iCallbackPlaylistSetImageId(iPtrPlaylistSetImageId, invocationC, invocationCPtr, Id, ImageId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistInsert(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    Brhz Name;
    aInvocation.InvocationReadString("Name", Name);
    Brhz Description;
    aInvocation.InvocationReadString("Description", Description);
    TUint ImageId = aInvocation.InvocationReadUint("ImageId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t NewId;
    ASSERT(iCallbackPlaylistInsert != NULL);
    if (0 != iCallbackPlaylistInsert(iPtrPlaylistInsert, invocationC, invocationCPtr, AfterId, (const char*)Name.Ptr(), (const char*)Description.Ptr(), ImageId, &NewId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respNewId(aInvocation, "NewId");
    invocation.StartResponse();
    respNewId.Write(NewId);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistDeleteId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Value = aInvocation.InvocationReadUint("Value");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlaylistDeleteId != NULL);
    if (0 != iCallbackPlaylistDeleteId(iPtrPlaylistDeleteId, invocationC, invocationCPtr, Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistMove(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint AfterId = aInvocation.InvocationReadUint("AfterId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackPlaylistMove != NULL);
    if (0 != iCallbackPlaylistMove(iPtrPlaylistMove, invocationC, invocationCPtr, Id, AfterId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistsMax(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackPlaylistsMax != NULL);
    if (0 != iCallbackPlaylistsMax(iPtrPlaylistsMax, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoTracksMax(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackTracksMax != NULL);
    if (0 != iCallbackTracksMax(iPtrTracksMax, invocationC, invocationCPtr, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write(Value);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistArrays(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Token;
    char* IdArray;
    uint32_t IdArrayLen;
    char* TokenArray;
    uint32_t TokenArrayLen;
    ASSERT(iCallbackPlaylistArrays != NULL);
    if (0 != iCallbackPlaylistArrays(iPtrPlaylistArrays, invocationC, invocationCPtr, &Token, &IdArray, &IdArrayLen, &TokenArray, &TokenArrayLen)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respToken(aInvocation, "Token");
    DviInvocationResponseBinary respIdArray(aInvocation, "IdArray");
    DviInvocationResponseBinary respTokenArray(aInvocation, "TokenArray");
    invocation.StartResponse();
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
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoPlaylistArraysChanged(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Token = aInvocation.InvocationReadUint("Token");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Value;
    ASSERT(iCallbackPlaylistArraysChanged != NULL);
    if (0 != iCallbackPlaylistArraysChanged(iPtrPlaylistArraysChanged, invocationC, invocationCPtr, Token, &Value)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseBool respValue(aInvocation, "Value");
    invocation.StartResponse();
    respValue.Write((Value!=0));
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoRead(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Metadata;
    ASSERT(iCallbackRead != NULL);
    if (0 != iCallbackRead(iPtrRead, invocationC, invocationCPtr, Id, TrackId, &Metadata)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respMetadata(aInvocation, "Metadata");
    invocation.StartResponse();
    Brhz bufMetadata((const TChar*)Metadata);
    OhNetFreeExternal(Metadata);
    respMetadata.Write(bufMetadata);
    respMetadata.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoReadList(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    Brhz TrackIdList;
    aInvocation.InvocationReadString("TrackIdList", TrackIdList);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* TrackList;
    ASSERT(iCallbackReadList != NULL);
    if (0 != iCallbackReadList(iPtrReadList, invocationC, invocationCPtr, Id, (const char*)TrackIdList.Ptr(), &TrackList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respTrackList(aInvocation, "TrackList");
    invocation.StartResponse();
    Brhz bufTrackList((const TChar*)TrackList);
    OhNetFreeExternal(TrackList);
    respTrackList.Write(bufTrackList);
    respTrackList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoInsert(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint AfterTrackId = aInvocation.InvocationReadUint("AfterTrackId");
    Brhz Metadata;
    aInvocation.InvocationReadString("Metadata", Metadata);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t NewTrackId;
    ASSERT(iCallbackInsert != NULL);
    if (0 != iCallbackInsert(iPtrInsert, invocationC, invocationCPtr, Id, AfterTrackId, (const char*)Metadata.Ptr(), &NewTrackId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respNewTrackId(aInvocation, "NewTrackId");
    invocation.StartResponse();
    respNewTrackId.Write(NewTrackId);
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteId(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    TUint TrackId = aInvocation.InvocationReadUint("TrackId");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteId != NULL);
    if (0 != iCallbackDeleteId(iPtrDeleteId, invocationC, invocationCPtr, Id, TrackId)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderAvOpenhomeOrgPlaylistManager1C::DoDeleteAll(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint Id = aInvocation.InvocationReadUint("Id");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteAll != NULL);
    if (0 != iCallbackDeleteAll(iPtrDeleteAll, invocationC, invocationCPtr, Id)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
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

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistReadList(THandle aProvider, CallbackPlaylistManager1PlaylistReadList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistReadList(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistRead(THandle aProvider, CallbackPlaylistManager1PlaylistRead aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistRead(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetName(THandle aProvider, CallbackPlaylistManager1PlaylistSetName aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistSetName(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetDescription(THandle aProvider, CallbackPlaylistManager1PlaylistSetDescription aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistSetDescription(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistSetImageId(THandle aProvider, CallbackPlaylistManager1PlaylistSetImageId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistSetImageId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistInsert(THandle aProvider, CallbackPlaylistManager1PlaylistInsert aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistInsert(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistDeleteId(THandle aProvider, CallbackPlaylistManager1PlaylistDeleteId aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistDeleteId(aCallback, aPtr);
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnableActionPlaylistMove(THandle aProvider, CallbackPlaylistManager1PlaylistMove aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnableActionPlaylistMove(aCallback, aPtr);
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

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyMetadata(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnablePropertyMetadata();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyImagesXml(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnablePropertyImagesXml();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyIdArray(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnablePropertyIdArray();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTokenArray(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnablePropertyTokenArray();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyPlaylistsMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnablePropertyPlaylistsMax();
}

void STDCALL DvProviderAvOpenhomeOrgPlaylistManager1EnablePropertyTracksMax(THandle aProvider)
{
    reinterpret_cast<DvProviderAvOpenhomeOrgPlaylistManager1C*>(aProvider)->EnablePropertyTracksMax();
}

