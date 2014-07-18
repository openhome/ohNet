#include "DvUpnpOrgContentDirectory1.h"
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

class DvProviderUpnpOrgContentDirectory1C : public DvProvider
{
public:
    DvProviderUpnpOrgContentDirectory1C(DvDeviceC aDevice);
    TBool SetPropertyTransferIDs(const Brx& aValue);
    void GetPropertyTransferIDs(Brhz& aValue);
    TBool SetPropertySystemUpdateID(TUint aValue);
    void GetPropertySystemUpdateID(TUint& aValue);
    TBool SetPropertyContainerUpdateIDs(const Brx& aValue);
    void GetPropertyContainerUpdateIDs(Brhz& aValue);
    void EnablePropertyTransferIDs();
    void EnablePropertySystemUpdateID();
    void EnablePropertyContainerUpdateIDs();
    void EnableActionGetSearchCapabilities(CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr);
    void EnableActionGetSortCapabilities(CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetSystemUpdateID(CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr);
    void EnableActionBrowse(CallbackContentDirectory1Browse aCallback, void* aPtr);
    void EnableActionSearch(CallbackContentDirectory1Search aCallback, void* aPtr);
    void EnableActionCreateObject(CallbackContentDirectory1CreateObject aCallback, void* aPtr);
    void EnableActionDestroyObject(CallbackContentDirectory1DestroyObject aCallback, void* aPtr);
    void EnableActionUpdateObject(CallbackContentDirectory1UpdateObject aCallback, void* aPtr);
    void EnableActionImportResource(CallbackContentDirectory1ImportResource aCallback, void* aPtr);
    void EnableActionExportResource(CallbackContentDirectory1ExportResource aCallback, void* aPtr);
    void EnableActionStopTransferResource(CallbackContentDirectory1StopTransferResource aCallback, void* aPtr);
    void EnableActionGetTransferProgress(CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr);
    void EnableActionDeleteResource(CallbackContentDirectory1DeleteResource aCallback, void* aPtr);
    void EnableActionCreateReference(CallbackContentDirectory1CreateReference aCallback, void* aPtr);
private:
    void DoGetSearchCapabilities(IDviInvocation& aInvocation);
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation);
    void DoBrowse(IDviInvocation& aInvocation);
    void DoSearch(IDviInvocation& aInvocation);
    void DoCreateObject(IDviInvocation& aInvocation);
    void DoDestroyObject(IDviInvocation& aInvocation);
    void DoUpdateObject(IDviInvocation& aInvocation);
    void DoImportResource(IDviInvocation& aInvocation);
    void DoExportResource(IDviInvocation& aInvocation);
    void DoStopTransferResource(IDviInvocation& aInvocation);
    void DoGetTransferProgress(IDviInvocation& aInvocation);
    void DoDeleteResource(IDviInvocation& aInvocation);
    void DoCreateReference(IDviInvocation& aInvocation);
private:
    CallbackContentDirectory1GetSearchCapabilities iCallbackGetSearchCapabilities;
    void* iPtrGetSearchCapabilities;
    CallbackContentDirectory1GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackContentDirectory1GetSystemUpdateID iCallbackGetSystemUpdateID;
    void* iPtrGetSystemUpdateID;
    CallbackContentDirectory1Browse iCallbackBrowse;
    void* iPtrBrowse;
    CallbackContentDirectory1Search iCallbackSearch;
    void* iPtrSearch;
    CallbackContentDirectory1CreateObject iCallbackCreateObject;
    void* iPtrCreateObject;
    CallbackContentDirectory1DestroyObject iCallbackDestroyObject;
    void* iPtrDestroyObject;
    CallbackContentDirectory1UpdateObject iCallbackUpdateObject;
    void* iPtrUpdateObject;
    CallbackContentDirectory1ImportResource iCallbackImportResource;
    void* iPtrImportResource;
    CallbackContentDirectory1ExportResource iCallbackExportResource;
    void* iPtrExportResource;
    CallbackContentDirectory1StopTransferResource iCallbackStopTransferResource;
    void* iPtrStopTransferResource;
    CallbackContentDirectory1GetTransferProgress iCallbackGetTransferProgress;
    void* iPtrGetTransferProgress;
    CallbackContentDirectory1DeleteResource iCallbackDeleteResource;
    void* iPtrDeleteResource;
    CallbackContentDirectory1CreateReference iCallbackCreateReference;
    void* iPtrCreateReference;
    PropertyString* iPropertyTransferIDs;
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
};

DvProviderUpnpOrgContentDirectory1C::DvProviderUpnpOrgContentDirectory1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ContentDirectory", 1)
{
    iPropertyTransferIDs = NULL;
    iPropertySystemUpdateID = NULL;
    iPropertyContainerUpdateIDs = NULL;
}

TBool DvProviderUpnpOrgContentDirectory1C::SetPropertyTransferIDs(const Brx& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory1C::GetPropertyTransferIDs(Brhz& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    aValue.Set(iPropertyTransferIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory1C::SetPropertySystemUpdateID(TUint aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory1C::GetPropertySystemUpdateID(TUint& aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory1C::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory1C::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

void DvProviderUpnpOrgContentDirectory1C::EnablePropertyTransferIDs()
{
    iPropertyTransferIDs = new PropertyString(iDvStack.Env(), new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory1C::EnablePropertySystemUpdateID()
{
    iPropertySystemUpdateID = new PropertyUint(iDvStack.Env(), new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
}

void DvProviderUpnpOrgContentDirectory1C::EnablePropertyContainerUpdateIDs()
{
    iPropertyContainerUpdateIDs = new PropertyString(iDvStack.Env(), new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSearchCapabilities(CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSortCapabilities(CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSystemUpdateID(CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionBrowse(CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Browse");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterString("ObjectID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"BrowseMetadata";
    allowedValues[index++] = (TChar*)"BrowseDirectChildren";
    action->AddInputParameter(new ParameterString("BrowseFlag", allowedValues, 2));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionSearch(CallbackContentDirectory1Search aCallback, void* aPtr)
{
    iCallbackSearch = aCallback;
    iPtrSearch = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Search");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("SearchCriteria"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionCreateObject(CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionDestroyObject(CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionUpdateObject(CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionImportResource(CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionExportResource(CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionStopTransferResource(CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetTransferProgress(CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransferProgress");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("TransferID"));
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"COMPLETED";
    allowedValues[index++] = (TChar*)"ERROR";
    allowedValues[index++] = (TChar*)"IN_PROGRESS";
    allowedValues[index++] = (TChar*)"STOPPED";
    action->AddOutputParameter(new ParameterString("TransferStatus", allowedValues, 4));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("TransferLength"));
    action->AddOutputParameter(new ParameterString("TransferTotal"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionDeleteResource(CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionCreateReference(CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::DoGetSearchCapabilities(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* SearchCaps;
    ASSERT(iCallbackGetSearchCapabilities != NULL);
    if (0 != iCallbackGetSearchCapabilities(iPtrGetSearchCapabilities, invocationC, invocationCPtr, &SearchCaps)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    invocation.StartResponse();
    Brhz bufSearchCaps((const TChar*)SearchCaps);
    OhNetFreeExternal(SearchCaps);
    respSearchCaps.Write(bufSearchCaps);
    respSearchCaps.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoGetSortCapabilities(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* SortCaps;
    ASSERT(iCallbackGetSortCapabilities != NULL);
    if (0 != iCallbackGetSortCapabilities(iPtrGetSortCapabilities, invocationC, invocationCPtr, &SortCaps)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSortCaps(aInvocation, "SortCaps");
    invocation.StartResponse();
    Brhz bufSortCaps((const TChar*)SortCaps);
    OhNetFreeExternal(SortCaps);
    respSortCaps.Write(bufSortCaps);
    respSortCaps.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoGetSystemUpdateID(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Id;
    ASSERT(iCallbackGetSystemUpdateID != NULL);
    if (0 != iCallbackGetSystemUpdateID(iPtrGetSystemUpdateID, invocationC, invocationCPtr, &Id)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respId(aInvocation, "Id");
    invocation.StartResponse();
    respId.Write(Id);
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoBrowse(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz BrowseFlag;
    aInvocation.InvocationReadString("BrowseFlag", BrowseFlag);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    TUint StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    TUint RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", SortCriteria);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowse != NULL);
    if (0 != iCallbackBrowse(iPtrBrowse, invocationC, invocationCPtr, (const char*)ObjectID.Ptr(), (const char*)BrowseFlag.Ptr(), (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoSearch(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz SearchCriteria;
    aInvocation.InvocationReadString("SearchCriteria", SearchCriteria);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    TUint StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    TUint RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", SortCriteria);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackSearch != NULL);
    if (0 != iCallbackSearch(iPtrSearch, invocationC, invocationCPtr, (const char*)ContainerID.Ptr(), (const char*)SearchCriteria.Ptr(), (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoCreateObject(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ObjectID;
    char* Result;
    ASSERT(iCallbackCreateObject != NULL);
    if (0 != iCallbackCreateObject(iPtrCreateObject, invocationC, invocationCPtr, (const char*)ContainerID.Ptr(), (const char*)Elements.Ptr(), &ObjectID, &Result)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respObjectID(aInvocation, "ObjectID");
    DviInvocationResponseString respResult(aInvocation, "Result");
    invocation.StartResponse();
    Brhz bufObjectID((const TChar*)ObjectID);
    OhNetFreeExternal(ObjectID);
    respObjectID.Write(bufObjectID);
    respObjectID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoDestroyObject(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, invocationC, invocationCPtr, (const char*)ObjectID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoUpdateObject(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz CurrentTagValue;
    aInvocation.InvocationReadString("CurrentTagValue", CurrentTagValue);
    Brhz NewTagValue;
    aInvocation.InvocationReadString("NewTagValue", NewTagValue);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, invocationC, invocationCPtr, (const char*)ObjectID.Ptr(), (const char*)CurrentTagValue.Ptr(), (const char*)NewTagValue.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoImportResource(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t TransferID;
    ASSERT(iCallbackImportResource != NULL);
    if (0 != iCallbackImportResource(iPtrImportResource, invocationC, invocationCPtr, (const char*)SourceURI.Ptr(), (const char*)DestinationURI.Ptr(), &TransferID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respTransferID(aInvocation, "TransferID");
    invocation.StartResponse();
    respTransferID.Write(TransferID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoExportResource(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t TransferID;
    ASSERT(iCallbackExportResource != NULL);
    if (0 != iCallbackExportResource(iPtrExportResource, invocationC, invocationCPtr, (const char*)SourceURI.Ptr(), (const char*)DestinationURI.Ptr(), &TransferID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respTransferID(aInvocation, "TransferID");
    invocation.StartResponse();
    respTransferID.Write(TransferID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoStopTransferResource(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, invocationC, invocationCPtr, TransferID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoGetTransferProgress(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* TransferStatus;
    char* TransferLength;
    char* TransferTotal;
    ASSERT(iCallbackGetTransferProgress != NULL);
    if (0 != iCallbackGetTransferProgress(iPtrGetTransferProgress, invocationC, invocationCPtr, TransferID, &TransferStatus, &TransferLength, &TransferTotal)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respTransferStatus(aInvocation, "TransferStatus");
    DviInvocationResponseString respTransferLength(aInvocation, "TransferLength");
    DviInvocationResponseString respTransferTotal(aInvocation, "TransferTotal");
    invocation.StartResponse();
    Brhz bufTransferStatus((const TChar*)TransferStatus);
    OhNetFreeExternal(TransferStatus);
    respTransferStatus.Write(bufTransferStatus);
    respTransferStatus.WriteFlush();
    Brhz bufTransferLength((const TChar*)TransferLength);
    OhNetFreeExternal(TransferLength);
    respTransferLength.Write(bufTransferLength);
    respTransferLength.WriteFlush();
    Brhz bufTransferTotal((const TChar*)TransferTotal);
    OhNetFreeExternal(TransferTotal);
    respTransferTotal.Write(bufTransferTotal);
    respTransferTotal.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoDeleteResource(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, invocationC, invocationCPtr, (const char*)ResourceURI.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory1C::DoCreateReference(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* NewID;
    ASSERT(iCallbackCreateReference != NULL);
    if (0 != iCallbackCreateReference(iPtrCreateReference, invocationC, invocationCPtr, (const char*)ContainerID.Ptr(), (const char*)ObjectID.Ptr(), &NewID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respNewID(aInvocation, "NewID");
    invocation.StartResponse();
    Brhz bufNewID((const TChar*)NewID);
    OhNetFreeExternal(NewID);
    respNewID.Write(bufNewID);
    respNewID.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgContentDirectory1Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgContentDirectory1C(aDevice);
}

void STDCALL DvProviderUpnpOrgContentDirectory1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionBrowse(THandle aProvider, CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionSearch(THandle aProvider, CallbackContentDirectory1Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionCreateObject(THandle aProvider, CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionImportResource(THandle aProvider, CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionExportResource(THandle aProvider, CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnableActionCreateReference(THandle aProvider, CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory1SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory1GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory1SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory1GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory1SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory1GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnablePropertyTransferIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnablePropertyTransferIDs();
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnablePropertySystemUpdateID(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnablePropertySystemUpdateID();
}

void STDCALL DvProviderUpnpOrgContentDirectory1EnablePropertyContainerUpdateIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnablePropertyContainerUpdateIDs();
}

