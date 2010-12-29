#include "DvUpnpOrgContentDirectory1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

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
    void DoGetSearchCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowse(IDviInvocation& aInvocation, TUint aVersion);
    void DoSearch(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoUpdateObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoImportResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoExportResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateReference(IDviInvocation& aInvocation, TUint aVersion);
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
    
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

TBool DvProviderUpnpOrgContentDirectory1C::SetPropertyTransferIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory1C::GetPropertyTransferIDs(Brhz& aValue)
{
    aValue.Set(iPropertyTransferIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory1C::SetPropertySystemUpdateID(TUint aValue)
{
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory1C::GetPropertySystemUpdateID(TUint& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory1C::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory1C::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSearchCapabilities(CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    Zapp::Action* action = new Zapp::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSortCapabilities(CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSystemUpdateID(CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    Zapp::Action* action = new Zapp::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionBrowse(CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    Zapp::Action* action = new Zapp::Action("Browse");
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
    Zapp::Action* action = new Zapp::Action("Search");
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
    Zapp::Action* action = new Zapp::Action("CreateObject");
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
    Zapp::Action* action = new Zapp::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionUpdateObject(CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    Zapp::Action* action = new Zapp::Action("UpdateObject");
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
    Zapp::Action* action = new Zapp::Action("ImportResource");
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
    Zapp::Action* action = new Zapp::Action("ExportResource");
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
    Zapp::Action* action = new Zapp::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetTransferProgress(CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    Zapp::Action* action = new Zapp::Action("GetTransferProgress");
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
    Zapp::Action* action = new Zapp::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionCreateReference(CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    Zapp::Action* action = new Zapp::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1C::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1C::DoGetSearchCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* SearchCaps;
    ASSERT(iCallbackGetSearchCapabilities != NULL);
    if (0 != iCallbackGetSearchCapabilities(iPtrGetSearchCapabilities, aVersion, &SearchCaps)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    resp.Start();
    Brhz bufSearchCaps((const TChar*)SearchCaps);
    ZappFreeExternal(SearchCaps);
    respSearchCaps.Write(bufSearchCaps);
    respSearchCaps.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* SortCaps;
    ASSERT(iCallbackGetSortCapabilities != NULL);
    if (0 != iCallbackGetSortCapabilities(iPtrGetSortCapabilities, aVersion, &SortCaps)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    resp.Start();
    Brhz bufSortCaps((const TChar*)SortCaps);
    ZappFreeExternal(SortCaps);
    respSortCaps.Write(bufSortCaps);
    respSortCaps.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Id;
    ASSERT(iCallbackGetSystemUpdateID != NULL);
    if (0 != iCallbackGetSystemUpdateID(iPtrGetSystemUpdateID, aVersion, &Id)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respId(aInvocation, "Id");
    resp.Start();
    respId.Write(Id);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoBrowse(IDviInvocation& aInvocation, TUint aVersion)
{
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
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowse != NULL);
    if (0 != iCallbackBrowse(iPtrBrowse, aVersion, (const char*)ObjectID.Ptr(), (const char*)BrowseFlag.Ptr(), (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoSearch(IDviInvocation& aInvocation, TUint aVersion)
{
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
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackSearch != NULL);
    if (0 != iCallbackSearch(iPtrSearch, aVersion, (const char*)ContainerID.Ptr(), (const char*)SearchCriteria.Ptr(), (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoCreateObject(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* ObjectID;
    char* Result;
    ASSERT(iCallbackCreateObject != NULL);
    if (0 != iCallbackCreateObject(iPtrCreateObject, aVersion, (const char*)ContainerID.Ptr(), (const char*)Elements.Ptr(), &ObjectID, &Result)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respObjectID(aInvocation, "ObjectID");
    InvocationResponseString respResult(aInvocation, "Result");
    resp.Start();
    Brhz bufObjectID((const TChar*)ObjectID);
    ZappFreeExternal(ObjectID);
    respObjectID.Write(bufObjectID);
    respObjectID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, aVersion, (const char*)ObjectID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoUpdateObject(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz CurrentTagValue;
    aInvocation.InvocationReadString("CurrentTagValue", CurrentTagValue);
    Brhz NewTagValue;
    aInvocation.InvocationReadString("NewTagValue", NewTagValue);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, aVersion, (const char*)ObjectID.Ptr(), (const char*)CurrentTagValue.Ptr(), (const char*)NewTagValue.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoImportResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t TransferID;
    ASSERT(iCallbackImportResource != NULL);
    if (0 != iCallbackImportResource(iPtrImportResource, aVersion, (const char*)SourceURI.Ptr(), (const char*)DestinationURI.Ptr(), &TransferID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respTransferID(aInvocation, "TransferID");
    resp.Start();
    respTransferID.Write(TransferID);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoExportResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t TransferID;
    ASSERT(iCallbackExportResource != NULL);
    if (0 != iCallbackExportResource(iPtrExportResource, aVersion, (const char*)SourceURI.Ptr(), (const char*)DestinationURI.Ptr(), &TransferID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respTransferID(aInvocation, "TransferID");
    resp.Start();
    respTransferID.Write(TransferID);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, aVersion, TransferID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* TransferStatus;
    char* TransferLength;
    char* TransferTotal;
    ASSERT(iCallbackGetTransferProgress != NULL);
    if (0 != iCallbackGetTransferProgress(iPtrGetTransferProgress, aVersion, TransferID, &TransferStatus, &TransferLength, &TransferTotal)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respTransferStatus(aInvocation, "TransferStatus");
    InvocationResponseString respTransferLength(aInvocation, "TransferLength");
    InvocationResponseString respTransferTotal(aInvocation, "TransferTotal");
    resp.Start();
    Brhz bufTransferStatus((const TChar*)TransferStatus);
    ZappFreeExternal(TransferStatus);
    respTransferStatus.Write(bufTransferStatus);
    respTransferStatus.WriteFlush();
    Brhz bufTransferLength((const TChar*)TransferLength);
    ZappFreeExternal(TransferLength);
    respTransferLength.Write(bufTransferLength);
    respTransferLength.WriteFlush();
    Brhz bufTransferTotal((const TChar*)TransferTotal);
    ZappFreeExternal(TransferTotal);
    respTransferTotal.Write(bufTransferTotal);
    respTransferTotal.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, aVersion, (const char*)ResourceURI.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory1C::DoCreateReference(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* NewID;
    ASSERT(iCallbackCreateReference != NULL);
    if (0 != iCallbackCreateReference(iPtrCreateReference, aVersion, (const char*)ContainerID.Ptr(), (const char*)ObjectID.Ptr(), &NewID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respNewID(aInvocation, "NewID");
    resp.Start();
    Brhz bufNewID((const TChar*)NewID);
    ZappFreeExternal(NewID);
    respNewID.Write(bufNewID);
    respNewID.WriteFlush();
    resp.End();
}



THandle DvProviderUpnpOrgContentDirectory1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgContentDirectory1C(aDevice);
}

void DvProviderUpnpOrgContentDirectory1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionBrowse(THandle aProvider, CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionSearch(THandle aProvider, CallbackContentDirectory1Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionCreateObject(THandle aProvider, CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionImportResource(THandle aProvider, CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionExportResource(THandle aProvider, CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionCreateReference(THandle aProvider, CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgContentDirectory1SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory1GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgContentDirectory1SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory1GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgContentDirectory1SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory1GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

