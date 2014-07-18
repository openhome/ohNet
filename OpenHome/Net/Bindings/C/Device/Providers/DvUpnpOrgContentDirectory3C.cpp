#include "DvUpnpOrgContentDirectory3.h"
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

class DvProviderUpnpOrgContentDirectory3C : public DvProvider
{
public:
    DvProviderUpnpOrgContentDirectory3C(DvDeviceC aDevice);
    TBool SetPropertySystemUpdateID(TUint aValue);
    void GetPropertySystemUpdateID(TUint& aValue);
    TBool SetPropertyContainerUpdateIDs(const Brx& aValue);
    void GetPropertyContainerUpdateIDs(Brhz& aValue);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    TBool SetPropertyTransferIDs(const Brx& aValue);
    void GetPropertyTransferIDs(Brhz& aValue);
    void EnablePropertySystemUpdateID();
    void EnablePropertyContainerUpdateIDs();
    void EnablePropertyLastChange();
    void EnablePropertyTransferIDs();
    void EnableActionGetSearchCapabilities(CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr);
    void EnableActionGetSortCapabilities(CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetSortExtensionCapabilities(CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr);
    void EnableActionGetFeatureList(CallbackContentDirectory3GetFeatureList aCallback, void* aPtr);
    void EnableActionGetSystemUpdateID(CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr);
    void EnableActionGetServiceResetToken(CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr);
    void EnableActionBrowse(CallbackContentDirectory3Browse aCallback, void* aPtr);
    void EnableActionSearch(CallbackContentDirectory3Search aCallback, void* aPtr);
    void EnableActionCreateObject(CallbackContentDirectory3CreateObject aCallback, void* aPtr);
    void EnableActionDestroyObject(CallbackContentDirectory3DestroyObject aCallback, void* aPtr);
    void EnableActionUpdateObject(CallbackContentDirectory3UpdateObject aCallback, void* aPtr);
    void EnableActionMoveObject(CallbackContentDirectory3MoveObject aCallback, void* aPtr);
    void EnableActionImportResource(CallbackContentDirectory3ImportResource aCallback, void* aPtr);
    void EnableActionExportResource(CallbackContentDirectory3ExportResource aCallback, void* aPtr);
    void EnableActionDeleteResource(CallbackContentDirectory3DeleteResource aCallback, void* aPtr);
    void EnableActionStopTransferResource(CallbackContentDirectory3StopTransferResource aCallback, void* aPtr);
    void EnableActionGetTransferProgress(CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr);
    void EnableActionCreateReference(CallbackContentDirectory3CreateReference aCallback, void* aPtr);
    void EnableActionFreeFormQuery(CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr);
    void EnableActionGetFreeFormQueryCapabilities(CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr);
private:
    void DoGetSearchCapabilities(IDviInvocation& aInvocation);
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetSortExtensionCapabilities(IDviInvocation& aInvocation);
    void DoGetFeatureList(IDviInvocation& aInvocation);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation);
    void DoGetServiceResetToken(IDviInvocation& aInvocation);
    void DoBrowse(IDviInvocation& aInvocation);
    void DoSearch(IDviInvocation& aInvocation);
    void DoCreateObject(IDviInvocation& aInvocation);
    void DoDestroyObject(IDviInvocation& aInvocation);
    void DoUpdateObject(IDviInvocation& aInvocation);
    void DoMoveObject(IDviInvocation& aInvocation);
    void DoImportResource(IDviInvocation& aInvocation);
    void DoExportResource(IDviInvocation& aInvocation);
    void DoDeleteResource(IDviInvocation& aInvocation);
    void DoStopTransferResource(IDviInvocation& aInvocation);
    void DoGetTransferProgress(IDviInvocation& aInvocation);
    void DoCreateReference(IDviInvocation& aInvocation);
    void DoFreeFormQuery(IDviInvocation& aInvocation);
    void DoGetFreeFormQueryCapabilities(IDviInvocation& aInvocation);
private:
    CallbackContentDirectory3GetSearchCapabilities iCallbackGetSearchCapabilities;
    void* iPtrGetSearchCapabilities;
    CallbackContentDirectory3GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackContentDirectory3GetSortExtensionCapabilities iCallbackGetSortExtensionCapabilities;
    void* iPtrGetSortExtensionCapabilities;
    CallbackContentDirectory3GetFeatureList iCallbackGetFeatureList;
    void* iPtrGetFeatureList;
    CallbackContentDirectory3GetSystemUpdateID iCallbackGetSystemUpdateID;
    void* iPtrGetSystemUpdateID;
    CallbackContentDirectory3GetServiceResetToken iCallbackGetServiceResetToken;
    void* iPtrGetServiceResetToken;
    CallbackContentDirectory3Browse iCallbackBrowse;
    void* iPtrBrowse;
    CallbackContentDirectory3Search iCallbackSearch;
    void* iPtrSearch;
    CallbackContentDirectory3CreateObject iCallbackCreateObject;
    void* iPtrCreateObject;
    CallbackContentDirectory3DestroyObject iCallbackDestroyObject;
    void* iPtrDestroyObject;
    CallbackContentDirectory3UpdateObject iCallbackUpdateObject;
    void* iPtrUpdateObject;
    CallbackContentDirectory3MoveObject iCallbackMoveObject;
    void* iPtrMoveObject;
    CallbackContentDirectory3ImportResource iCallbackImportResource;
    void* iPtrImportResource;
    CallbackContentDirectory3ExportResource iCallbackExportResource;
    void* iPtrExportResource;
    CallbackContentDirectory3DeleteResource iCallbackDeleteResource;
    void* iPtrDeleteResource;
    CallbackContentDirectory3StopTransferResource iCallbackStopTransferResource;
    void* iPtrStopTransferResource;
    CallbackContentDirectory3GetTransferProgress iCallbackGetTransferProgress;
    void* iPtrGetTransferProgress;
    CallbackContentDirectory3CreateReference iCallbackCreateReference;
    void* iPtrCreateReference;
    CallbackContentDirectory3FreeFormQuery iCallbackFreeFormQuery;
    void* iPtrFreeFormQuery;
    CallbackContentDirectory3GetFreeFormQueryCapabilities iCallbackGetFreeFormQueryCapabilities;
    void* iPtrGetFreeFormQueryCapabilities;
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
    PropertyString* iPropertyLastChange;
    PropertyString* iPropertyTransferIDs;
};

DvProviderUpnpOrgContentDirectory3C::DvProviderUpnpOrgContentDirectory3C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ContentDirectory", 3)
{
    iPropertySystemUpdateID = NULL;
    iPropertyContainerUpdateIDs = NULL;
    iPropertyLastChange = NULL;
    iPropertyTransferIDs = NULL;
}

TBool DvProviderUpnpOrgContentDirectory3C::SetPropertySystemUpdateID(TUint aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory3C::GetPropertySystemUpdateID(TUint& aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory3C::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory3C::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory3C::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgContentDirectory3C::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

TBool DvProviderUpnpOrgContentDirectory3C::SetPropertyTransferIDs(const Brx& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory3C::GetPropertyTransferIDs(Brhz& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    aValue.Set(iPropertyTransferIDs->Value());
}

void DvProviderUpnpOrgContentDirectory3C::EnablePropertySystemUpdateID()
{
    iPropertySystemUpdateID = new PropertyUint(iDvStack.Env(), new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3C::EnablePropertyContainerUpdateIDs()
{
    iPropertyContainerUpdateIDs = new PropertyString(iDvStack.Env(), new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3C::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3C::EnablePropertyTransferIDs()
{
    iPropertyTransferIDs = new PropertyString(iDvStack.Env(), new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSearchCapabilities(CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSortCapabilities(CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSortExtensionCapabilities(CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortExtensionCapabilities = aCallback;
    iPtrGetSortExtensionCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetFeatureList(CallbackContentDirectory3GetFeatureList aCallback, void* aPtr)
{
    iCallbackGetFeatureList = aCallback;
    iPtrGetFeatureList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSystemUpdateID(CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetServiceResetToken(CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr)
{
    iCallbackGetServiceResetToken = aCallback;
    iPtrGetServiceResetToken = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetServiceResetToken");
    action->AddOutputParameter(new ParameterString("ResetToken"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetServiceResetToken);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionBrowse(CallbackContentDirectory3Browse aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionSearch(CallbackContentDirectory3Search aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionCreateObject(CallbackContentDirectory3CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionDestroyObject(CallbackContentDirectory3DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionUpdateObject(CallbackContentDirectory3UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionMoveObject(CallbackContentDirectory3MoveObject aCallback, void* aPtr)
{
    iCallbackMoveObject = aCallback;
    iPtrMoveObject = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionImportResource(CallbackContentDirectory3ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionExportResource(CallbackContentDirectory3ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionDeleteResource(CallbackContentDirectory3DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionStopTransferResource(CallbackContentDirectory3StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetTransferProgress(CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionCreateReference(CallbackContentDirectory3CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionFreeFormQuery(CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr)
{
    iCallbackFreeFormQuery = aCallback;
    iPtrFreeFormQuery = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FreeFormQuery");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterUint("CDSView"));
    action->AddInputParameter(new ParameterString("QueryRequest"));
    action->AddOutputParameter(new ParameterString("QueryResult"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoFreeFormQuery);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetFreeFormQueryCapabilities(CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr)
{
    iCallbackGetFreeFormQueryCapabilities = aCallback;
    iPtrGetFreeFormQueryCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFreeFormQueryCapabilities");
    action->AddOutputParameter(new ParameterString("FFQCapabilities"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3C::DoGetFreeFormQueryCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3C::DoGetSearchCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoGetSortCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoGetSortExtensionCapabilities(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* SortExtensionCaps;
    ASSERT(iCallbackGetSortExtensionCapabilities != NULL);
    if (0 != iCallbackGetSortExtensionCapabilities(iPtrGetSortExtensionCapabilities, invocationC, invocationCPtr, &SortExtensionCaps)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSortExtensionCaps(aInvocation, "SortExtensionCaps");
    invocation.StartResponse();
    Brhz bufSortExtensionCaps((const TChar*)SortExtensionCaps);
    OhNetFreeExternal(SortExtensionCaps);
    respSortExtensionCaps.Write(bufSortExtensionCaps);
    respSortExtensionCaps.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory3C::DoGetFeatureList(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* FeatureList;
    ASSERT(iCallbackGetFeatureList != NULL);
    if (0 != iCallbackGetFeatureList(iPtrGetFeatureList, invocationC, invocationCPtr, &FeatureList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respFeatureList(aInvocation, "FeatureList");
    invocation.StartResponse();
    Brhz bufFeatureList((const TChar*)FeatureList);
    OhNetFreeExternal(FeatureList);
    respFeatureList.Write(bufFeatureList);
    respFeatureList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory3C::DoGetSystemUpdateID(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoGetServiceResetToken(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* ResetToken;
    ASSERT(iCallbackGetServiceResetToken != NULL);
    if (0 != iCallbackGetServiceResetToken(iPtrGetServiceResetToken, invocationC, invocationCPtr, &ResetToken)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResetToken(aInvocation, "ResetToken");
    invocation.StartResponse();
    Brhz bufResetToken((const TChar*)ResetToken);
    OhNetFreeExternal(ResetToken);
    respResetToken.Write(bufResetToken);
    respResetToken.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory3C::DoBrowse(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoSearch(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoCreateObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoDestroyObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoUpdateObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoMoveObject(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz NewParentID;
    aInvocation.InvocationReadString("NewParentID", NewParentID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* NewObjectID;
    ASSERT(iCallbackMoveObject != NULL);
    if (0 != iCallbackMoveObject(iPtrMoveObject, invocationC, invocationCPtr, (const char*)ObjectID.Ptr(), (const char*)NewParentID.Ptr(), &NewObjectID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respNewObjectID(aInvocation, "NewObjectID");
    invocation.StartResponse();
    Brhz bufNewObjectID((const TChar*)NewObjectID);
    OhNetFreeExternal(NewObjectID);
    respNewObjectID.Write(bufNewObjectID);
    respNewObjectID.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory3C::DoImportResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoExportResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoDeleteResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoStopTransferResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoGetTransferProgress(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoCreateReference(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3C::DoFreeFormQuery(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    TUint CDSView = aInvocation.InvocationReadUint("CDSView");
    Brhz QueryRequest;
    aInvocation.InvocationReadString("QueryRequest", QueryRequest);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* QueryResult;
    uint32_t UpdateID;
    ASSERT(iCallbackFreeFormQuery != NULL);
    if (0 != iCallbackFreeFormQuery(iPtrFreeFormQuery, invocationC, invocationCPtr, (const char*)ContainerID.Ptr(), CDSView, (const char*)QueryRequest.Ptr(), &QueryResult, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respQueryResult(aInvocation, "QueryResult");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufQueryResult((const TChar*)QueryResult);
    OhNetFreeExternal(QueryResult);
    respQueryResult.Write(bufQueryResult);
    respQueryResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgContentDirectory3C::DoGetFreeFormQueryCapabilities(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* FFQCapabilities;
    ASSERT(iCallbackGetFreeFormQueryCapabilities != NULL);
    if (0 != iCallbackGetFreeFormQueryCapabilities(iPtrGetFreeFormQueryCapabilities, invocationC, invocationCPtr, &FFQCapabilities)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respFFQCapabilities(aInvocation, "FFQCapabilities");
    invocation.StartResponse();
    Brhz bufFFQCapabilities((const TChar*)FFQCapabilities);
    OhNetFreeExternal(FFQCapabilities);
    respFFQCapabilities.Write(bufFFQCapabilities);
    respFFQCapabilities.WriteFlush();
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgContentDirectory3Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgContentDirectory3C(aDevice);
}

void STDCALL DvProviderUpnpOrgContentDirectory3Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSortExtensionCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory3GetFeatureList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetFeatureList(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetServiceResetToken(THandle aProvider, CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetServiceResetToken(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionBrowse(THandle aProvider, CallbackContentDirectory3Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionSearch(THandle aProvider, CallbackContentDirectory3Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionCreateObject(THandle aProvider, CallbackContentDirectory3CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory3DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory3UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionMoveObject(THandle aProvider, CallbackContentDirectory3MoveObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionMoveObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionImportResource(THandle aProvider, CallbackContentDirectory3ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionExportResource(THandle aProvider, CallbackContentDirectory3ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory3DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory3StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionCreateReference(THandle aProvider, CallbackContentDirectory3CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionFreeFormQuery(THandle aProvider, CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionFreeFormQuery(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(THandle aProvider, CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetFreeFormQueryCapabilities(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory3SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory3GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertySystemUpdateID(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnablePropertySystemUpdateID();
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertyContainerUpdateIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnablePropertyContainerUpdateIDs();
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertyLastChange(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnablePropertyLastChange();
}

void STDCALL DvProviderUpnpOrgContentDirectory3EnablePropertyTransferIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnablePropertyTransferIDs();
}

