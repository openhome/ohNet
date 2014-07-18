#include "DvUpnpOrgContentDirectory2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgContentDirectory2::SetPropertySystemUpdateID(TUint aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory2::GetPropertySystemUpdateID(TUint& aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory2::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory2::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory2::SetPropertyTransferIDs(const Brx& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory2::GetPropertyTransferIDs(Brhz& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    aValue.Set(iPropertyTransferIDs->Value());
}

DvProviderUpnpOrgContentDirectory2::DvProviderUpnpOrgContentDirectory2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ContentDirectory", 2)
{
    Construct();
}

DvProviderUpnpOrgContentDirectory2::DvProviderUpnpOrgContentDirectory2(DviDevice& aDevice)
    : DvProvider(aDevice, "upnp.org", "ContentDirectory", 2)
{
    Construct();
}

void DvProviderUpnpOrgContentDirectory2::Construct()
{
    iPropertySystemUpdateID = NULL;
    iPropertyContainerUpdateIDs = NULL;
    iPropertyTransferIDs = NULL;
}

void DvProviderUpnpOrgContentDirectory2::EnablePropertySystemUpdateID()
{
    iPropertySystemUpdateID = new PropertyUint(iDvStack.Env(), new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2::EnablePropertyContainerUpdateIDs()
{
    iPropertyContainerUpdateIDs = new PropertyString(iDvStack.Env(), new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2::EnablePropertyTransferIDs()
{
    iPropertyTransferIDs = new PropertyString(iDvStack.Env(), new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2::EnableActionGetSearchCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionGetSortExtensionCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionGetFeatureList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionGetSystemUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionBrowse()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionSearch()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionCreateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionDestroyObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionUpdateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionMoveObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionImportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionExportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionDeleteResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionStopTransferResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionGetTransferProgress()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::EnableActionCreateReference()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2::DoGetSearchCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    GetSearchCapabilities(invocation, respSearchCaps);
}

void DvProviderUpnpOrgContentDirectory2::DoGetSortCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSortCaps(aInvocation, "SortCaps");
    GetSortCapabilities(invocation, respSortCaps);
}

void DvProviderUpnpOrgContentDirectory2::DoGetSortExtensionCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSortExtensionCaps(aInvocation, "SortExtensionCaps");
    GetSortExtensionCapabilities(invocation, respSortExtensionCaps);
}

void DvProviderUpnpOrgContentDirectory2::DoGetFeatureList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respFeatureList(aInvocation, "FeatureList");
    GetFeatureList(invocation, respFeatureList);
}

void DvProviderUpnpOrgContentDirectory2::DoGetSystemUpdateID(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respId(aInvocation, "Id");
    GetSystemUpdateID(invocation, respId);
}

void DvProviderUpnpOrgContentDirectory2::DoBrowse(IDviInvocation& aInvocation)
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    Browse(invocation, ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvProviderUpnpOrgContentDirectory2::DoSearch(IDviInvocation& aInvocation)
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    Search(invocation, ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvProviderUpnpOrgContentDirectory2::DoCreateObject(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respObjectID(aInvocation, "ObjectID");
    DviInvocationResponseString respResult(aInvocation, "Result");
    CreateObject(invocation, ContainerID, Elements, respObjectID, respResult);
}

void DvProviderUpnpOrgContentDirectory2::DoDestroyObject(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DestroyObject(invocation, ObjectID);
}

void DvProviderUpnpOrgContentDirectory2::DoUpdateObject(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz CurrentTagValue;
    aInvocation.InvocationReadString("CurrentTagValue", CurrentTagValue);
    Brhz NewTagValue;
    aInvocation.InvocationReadString("NewTagValue", NewTagValue);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    UpdateObject(invocation, ObjectID, CurrentTagValue, NewTagValue);
}

void DvProviderUpnpOrgContentDirectory2::DoMoveObject(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz NewParentID;
    aInvocation.InvocationReadString("NewParentID", NewParentID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respNewObjectID(aInvocation, "NewObjectID");
    MoveObject(invocation, ObjectID, NewParentID, respNewObjectID);
}

void DvProviderUpnpOrgContentDirectory2::DoImportResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTransferID(aInvocation, "TransferID");
    ImportResource(invocation, SourceURI, DestinationURI, respTransferID);
}

void DvProviderUpnpOrgContentDirectory2::DoExportResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTransferID(aInvocation, "TransferID");
    ExportResource(invocation, SourceURI, DestinationURI, respTransferID);
}

void DvProviderUpnpOrgContentDirectory2::DoDeleteResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteResource(invocation, ResourceURI);
}

void DvProviderUpnpOrgContentDirectory2::DoStopTransferResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    StopTransferResource(invocation, TransferID);
}

void DvProviderUpnpOrgContentDirectory2::DoGetTransferProgress(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respTransferStatus(aInvocation, "TransferStatus");
    DviInvocationResponseString respTransferLength(aInvocation, "TransferLength");
    DviInvocationResponseString respTransferTotal(aInvocation, "TransferTotal");
    GetTransferProgress(invocation, TransferID, respTransferStatus, respTransferLength, respTransferTotal);
}

void DvProviderUpnpOrgContentDirectory2::DoCreateReference(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respNewID(aInvocation, "NewID");
    CreateReference(invocation, ContainerID, ObjectID, respNewID);
}

void DvProviderUpnpOrgContentDirectory2::GetSearchCapabilities(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::GetSortCapabilities(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aSortCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::GetSortExtensionCapabilities(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aSortExtensionCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::GetFeatureList(IDvInvocation& /*aResponse*/, IDvInvocationResponseString& /*aFeatureList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::GetSystemUpdateID(IDvInvocation& /*aResponse*/, IDvInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::Browse(IDvInvocation& /*aResponse*/, const Brx& /*aObjectID*/, const Brx& /*aBrowseFlag*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aNumberReturned*/, IDvInvocationResponseUint& /*aTotalMatches*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::Search(IDvInvocation& /*aResponse*/, const Brx& /*aContainerID*/, const Brx& /*aSearchCriteria*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aNumberReturned*/, IDvInvocationResponseUint& /*aTotalMatches*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::CreateObject(IDvInvocation& /*aResponse*/, const Brx& /*aContainerID*/, const Brx& /*aElements*/, IDvInvocationResponseString& /*aObjectID*/, IDvInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::DestroyObject(IDvInvocation& /*aResponse*/, const Brx& /*aObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::UpdateObject(IDvInvocation& /*aResponse*/, const Brx& /*aObjectID*/, const Brx& /*aCurrentTagValue*/, const Brx& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::MoveObject(IDvInvocation& /*aResponse*/, const Brx& /*aObjectID*/, const Brx& /*aNewParentID*/, IDvInvocationResponseString& /*aNewObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::ImportResource(IDvInvocation& /*aResponse*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IDvInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::ExportResource(IDvInvocation& /*aResponse*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IDvInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::DeleteResource(IDvInvocation& /*aResponse*/, const Brx& /*aResourceURI*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::StopTransferResource(IDvInvocation& /*aResponse*/, TUint /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::GetTransferProgress(IDvInvocation& /*aResponse*/, TUint /*aTransferID*/, IDvInvocationResponseString& /*aTransferStatus*/, IDvInvocationResponseString& /*aTransferLength*/, IDvInvocationResponseString& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2::CreateReference(IDvInvocation& /*aResponse*/, const Brx& /*aContainerID*/, const Brx& /*aObjectID*/, IDvInvocationResponseString& /*aNewID*/)
{
    ASSERTS();
}

