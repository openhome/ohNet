#include "DvUpnpOrgContentDirectory2.h"
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
    void EnablePropertySystemUpdateID();
    void EnablePropertyContainerUpdateIDs();
    void EnablePropertyTransferIDs();
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
    void DoGetSearchCapabilities(IDviInvocation& aInvocation);
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetSortExtensionCapabilities(IDviInvocation& aInvocation);
    void DoGetFeatureList(IDviInvocation& aInvocation);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation);
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
    iPropertySystemUpdateID = NULL;
    iPropertyContainerUpdateIDs = NULL;
    iPropertyTransferIDs = NULL;
}

TBool DvProviderUpnpOrgContentDirectory2C::SetPropertySystemUpdateID(TUint aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory2C::GetPropertySystemUpdateID(TUint& aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory2C::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory2C::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory2C::SetPropertyTransferIDs(const Brx& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory2C::GetPropertyTransferIDs(Brhz& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    aValue.Set(iPropertyTransferIDs->Value());
}

void DvProviderUpnpOrgContentDirectory2C::EnablePropertySystemUpdateID()
{
    iPropertySystemUpdateID = new PropertyUint(iDvStack.Env(), new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2C::EnablePropertyContainerUpdateIDs()
{
    iPropertyContainerUpdateIDs = new PropertyString(iDvStack.Env(), new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2C::EnablePropertyTransferIDs()
{
    iPropertyTransferIDs = new PropertyString(iDvStack.Env(), new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
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

void DvProviderUpnpOrgContentDirectory2C::DoGetSearchCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoGetSortCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoGetSortExtensionCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoGetFeatureList(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoGetSystemUpdateID(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoBrowse(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoSearch(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoCreateObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoDestroyObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoUpdateObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoMoveObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoImportResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoExportResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoDeleteResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoStopTransferResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoGetTransferProgress(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory2C::DoCreateReference(IDviInvocation& aInvocation)
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



THandle STDCALL DvProviderUpnpOrgContentDirectory2Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgContentDirectory2C(aDevice);
}

void STDCALL DvProviderUpnpOrgContentDirectory2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSortExtensionCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory2GetFeatureList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetFeatureList(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionBrowse(THandle aProvider, CallbackContentDirectory2Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionSearch(THandle aProvider, CallbackContentDirectory2Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionCreateObject(THandle aProvider, CallbackContentDirectory2CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory2DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory2UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionMoveObject(THandle aProvider, CallbackContentDirectory2MoveObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionMoveObject(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionImportResource(THandle aProvider, CallbackContentDirectory2ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionExportResource(THandle aProvider, CallbackContentDirectory2ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory2DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory2StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnableActionCreateReference(THandle aProvider, CallbackContentDirectory2CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory2SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory2GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory2SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory2GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t STDCALL DvProviderUpnpOrgContentDirectory2SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgContentDirectory2GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnablePropertySystemUpdateID(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnablePropertySystemUpdateID();
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnablePropertyContainerUpdateIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnablePropertyContainerUpdateIDs();
}

void STDCALL DvProviderUpnpOrgContentDirectory2EnablePropertyTransferIDs(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnablePropertyTransferIDs();
}

