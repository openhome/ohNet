#include "DvUpnpOrgContentDirectory2.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

class DvProviderUpnpOrgContentDirectory2C : public DvProvider
{
public:
    DvProviderUpnpOrgContentDirectory2C(DvDeviceC aDevice);
    TBool SetPropertySystemUpdateID(TUint aValue);
    void GetPropertySystemUpdateID(TUint& aValue);
    TBool SetPropertyContainerUpdateIDs(const Brx& aValue);
    void GetPropertyContainerUpdateIDs(Brhz& aValue);
    TBool SetPropertyTransferIDs(const Brx& aValue);
    void GetPropertyTransferIDs(Brhz& aValue);
    void EnableActionGetSearchCapabilities(CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr);
    void EnableActionGetSortCapabilities(CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetSortExtensionCapabilities(CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr);
    void EnableActionGetFeatureList(CallbackContentDirectory2GetFeatureList aCallback, void* aPtr);
    void EnableActionGetSystemUpdateID(CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr);
    void EnableActionBrowse(CallbackContentDirectory2Browse aCallback, void* aPtr);
    void EnableActionSearch(CallbackContentDirectory2Search aCallback, void* aPtr);
    void EnableActionCreateObject(CallbackContentDirectory2CreateObject aCallback, void* aPtr);
    void EnableActionDestroyObject(CallbackContentDirectory2DestroyObject aCallback, void* aPtr);
    void EnableActionUpdateObject(CallbackContentDirectory2UpdateObject aCallback, void* aPtr);
    void EnableActionMoveObject(CallbackContentDirectory2MoveObject aCallback, void* aPtr);
    void EnableActionImportResource(CallbackContentDirectory2ImportResource aCallback, void* aPtr);
    void EnableActionExportResource(CallbackContentDirectory2ExportResource aCallback, void* aPtr);
    void EnableActionDeleteResource(CallbackContentDirectory2DeleteResource aCallback, void* aPtr);
    void EnableActionStopTransferResource(CallbackContentDirectory2StopTransferResource aCallback, void* aPtr);
    void EnableActionGetTransferProgress(CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr);
    void EnableActionCreateReference(CallbackContentDirectory2CreateReference aCallback, void* aPtr);
private:
    void DoGetSearchCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSortExtensionCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetFeatureList(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowse(IDviInvocation& aInvocation, TUint aVersion);
    void DoSearch(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoUpdateObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoMoveObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoImportResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoExportResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateReference(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackContentDirectory2GetSearchCapabilities iCallbackGetSearchCapabilities;
    void* iPtrGetSearchCapabilities;
    CallbackContentDirectory2GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackContentDirectory2GetSortExtensionCapabilities iCallbackGetSortExtensionCapabilities;
    void* iPtrGetSortExtensionCapabilities;
    CallbackContentDirectory2GetFeatureList iCallbackGetFeatureList;
    void* iPtrGetFeatureList;
    CallbackContentDirectory2GetSystemUpdateID iCallbackGetSystemUpdateID;
    void* iPtrGetSystemUpdateID;
    CallbackContentDirectory2Browse iCallbackBrowse;
    void* iPtrBrowse;
    CallbackContentDirectory2Search iCallbackSearch;
    void* iPtrSearch;
    CallbackContentDirectory2CreateObject iCallbackCreateObject;
    void* iPtrCreateObject;
    CallbackContentDirectory2DestroyObject iCallbackDestroyObject;
    void* iPtrDestroyObject;
    CallbackContentDirectory2UpdateObject iCallbackUpdateObject;
    void* iPtrUpdateObject;
    CallbackContentDirectory2MoveObject iCallbackMoveObject;
    void* iPtrMoveObject;
    CallbackContentDirectory2ImportResource iCallbackImportResource;
    void* iPtrImportResource;
    CallbackContentDirectory2ExportResource iCallbackExportResource;
    void* iPtrExportResource;
    CallbackContentDirectory2DeleteResource iCallbackDeleteResource;
    void* iPtrDeleteResource;
    CallbackContentDirectory2StopTransferResource iCallbackStopTransferResource;
    void* iPtrStopTransferResource;
    CallbackContentDirectory2GetTransferProgress iCallbackGetTransferProgress;
    void* iPtrGetTransferProgress;
    CallbackContentDirectory2CreateReference iCallbackCreateReference;
    void* iPtrCreateReference;
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
    PropertyString* iPropertyTransferIDs;
};

DvProviderUpnpOrgContentDirectory2C::DvProviderUpnpOrgContentDirectory2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ContentDirectory", 2)
{
    
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

TBool DvProviderUpnpOrgContentDirectory2C::SetPropertySystemUpdateID(TUint aValue)
{
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory2C::GetPropertySystemUpdateID(TUint& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory2C::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory2C::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory2C::SetPropertyTransferIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory2C::GetPropertyTransferIDs(Brhz& aValue)
{
    aValue.Set(iPropertyTransferIDs->Value());
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSearchCapabilities(CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSortCapabilities(CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSortExtensionCapabilities(CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortExtensionCapabilities = aCallback;
    iPtrGetSortExtensionCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetFeatureList(CallbackContentDirectory2GetFeatureList aCallback, void* aPtr)
{
    iCallbackGetFeatureList = aCallback;
    iPtrGetFeatureList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSystemUpdateID(CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionBrowse(CallbackContentDirectory2Browse aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionSearch(CallbackContentDirectory2Search aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionCreateObject(CallbackContentDirectory2CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionDestroyObject(CallbackContentDirectory2DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionUpdateObject(CallbackContentDirectory2UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionMoveObject(CallbackContentDirectory2MoveObject aCallback, void* aPtr)
{
    iCallbackMoveObject = aCallback;
    iPtrMoveObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionImportResource(CallbackContentDirectory2ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionExportResource(CallbackContentDirectory2ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionDeleteResource(CallbackContentDirectory2DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionStopTransferResource(CallbackContentDirectory2StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetTransferProgress(CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionCreateReference(CallbackContentDirectory2CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2C::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2C::DoGetSearchCapabilities(IDviInvocation& aInvocation, TUint aVersion)
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
    OhNetFreeExternal(SearchCaps);
    respSearchCaps.Write(bufSearchCaps);
    respSearchCaps.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
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
    OhNetFreeExternal(SortCaps);
    respSortCaps.Write(bufSortCaps);
    respSortCaps.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoGetSortExtensionCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* SortExtensionCaps;
    ASSERT(iCallbackGetSortExtensionCapabilities != NULL);
    if (0 != iCallbackGetSortExtensionCapabilities(iPtrGetSortExtensionCapabilities, aVersion, &SortExtensionCaps)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respSortExtensionCaps(aInvocation, "SortExtensionCaps");
    resp.Start();
    Brhz bufSortExtensionCaps((const TChar*)SortExtensionCaps);
    OhNetFreeExternal(SortExtensionCaps);
    respSortExtensionCaps.Write(bufSortExtensionCaps);
    respSortExtensionCaps.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoGetFeatureList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* FeatureList;
    ASSERT(iCallbackGetFeatureList != NULL);
    if (0 != iCallbackGetFeatureList(iPtrGetFeatureList, aVersion, &FeatureList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respFeatureList(aInvocation, "FeatureList");
    resp.Start();
    Brhz bufFeatureList((const TChar*)FeatureList);
    OhNetFreeExternal(FeatureList);
    respFeatureList.Write(bufFeatureList);
    respFeatureList.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoBrowse(IDviInvocation& aInvocation, TUint aVersion)
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
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoSearch(IDviInvocation& aInvocation, TUint aVersion)
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
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoCreateObject(IDviInvocation& aInvocation, TUint aVersion)
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
    OhNetFreeExternal(ObjectID);
    respObjectID.Write(bufObjectID);
    respObjectID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoUpdateObject(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoMoveObject(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz NewParentID;
    aInvocation.InvocationReadString("NewParentID", NewParentID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* NewObjectID;
    ASSERT(iCallbackMoveObject != NULL);
    if (0 != iCallbackMoveObject(iPtrMoveObject, aVersion, (const char*)ObjectID.Ptr(), (const char*)NewParentID.Ptr(), &NewObjectID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respNewObjectID(aInvocation, "NewObjectID");
    resp.Start();
    Brhz bufNewObjectID((const TChar*)NewObjectID);
    OhNetFreeExternal(NewObjectID);
    respNewObjectID.Write(bufNewObjectID);
    respNewObjectID.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoImportResource(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoExportResource(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory2C::DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion)
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
    resp.End();
}

void DvProviderUpnpOrgContentDirectory2C::DoCreateReference(IDviInvocation& aInvocation, TUint aVersion)
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
    OhNetFreeExternal(NewID);
    respNewID.Write(bufNewID);
    respNewID.WriteFlush();
    resp.End();
}



THandle DvProviderUpnpOrgContentDirectory2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgContentDirectory2C(aDevice);
}

void DvProviderUpnpOrgContentDirectory2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSortExtensionCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory2GetFeatureList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetFeatureList(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionBrowse(THandle aProvider, CallbackContentDirectory2Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionSearch(THandle aProvider, CallbackContentDirectory2Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionCreateObject(THandle aProvider, CallbackContentDirectory2CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory2DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory2UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionMoveObject(THandle aProvider, CallbackContentDirectory2MoveObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionMoveObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionImportResource(THandle aProvider, CallbackContentDirectory2ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionExportResource(THandle aProvider, CallbackContentDirectory2ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory2DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory2StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionCreateReference(THandle aProvider, CallbackContentDirectory2CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgContentDirectory2SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory2GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgContentDirectory2SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory2GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgContentDirectory2SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory2GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

