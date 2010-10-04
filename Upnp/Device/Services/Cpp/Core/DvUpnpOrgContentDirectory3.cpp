#include <Core/DvUpnpOrgContentDirectory3.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgContentDirectory3::SetPropertySystemUpdateID(TUint aValue)
{
    SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvServiceUpnpOrgContentDirectory3::GetPropertySystemUpdateID(TUint& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

void DvServiceUpnpOrgContentDirectory3::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvServiceUpnpOrgContentDirectory3::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

void DvServiceUpnpOrgContentDirectory3::SetPropertyLastChange(const Brx& aValue)
{
    SetPropertyString(*iPropertyLastChange, aValue);
}

void DvServiceUpnpOrgContentDirectory3::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

void DvServiceUpnpOrgContentDirectory3::SetPropertyTransferIDs(const Brx& aValue)
{
    SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvServiceUpnpOrgContentDirectory3::GetPropertyTransferIDs(Brhz& aValue)
{
    aValue.Set(iPropertyTransferIDs->Value());
}

DvServiceUpnpOrgContentDirectory3::DvServiceUpnpOrgContentDirectory3(DvDevice& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ContentDirectory", 3)
{
    Functor empty;
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"), empty);
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"), empty);
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"), empty);
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetSearchCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetSortExtensionCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetFeatureList()
{
    Zapp::Action* action = new Zapp::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetSystemUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetServiceResetToken()
{
    Zapp::Action* action = new Zapp::Action("GetServiceResetToken");
    action->AddOutputParameter(new ParameterString("ResetToken"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetServiceResetToken);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionBrowse()
{
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoBrowse);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionSearch()
{
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoSearch);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionCreateObject()
{
    Zapp::Action* action = new Zapp::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionDestroyObject()
{
    Zapp::Action* action = new Zapp::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionUpdateObject()
{
    Zapp::Action* action = new Zapp::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionMoveObject()
{
    Zapp::Action* action = new Zapp::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionImportResource()
{
    Zapp::Action* action = new Zapp::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoImportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionExportResource()
{
    Zapp::Action* action = new Zapp::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoExportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionDeleteResource()
{
    Zapp::Action* action = new Zapp::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionStopTransferResource()
{
    Zapp::Action* action = new Zapp::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetTransferProgress()
{
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionCreateReference()
{
    Zapp::Action* action = new Zapp::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionFreeFormQuery()
{
    Zapp::Action* action = new Zapp::Action("FreeFormQuery");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterUint("CDSView"));
    action->AddInputParameter(new ParameterString("QueryRequest"));
    action->AddOutputParameter(new ParameterString("QueryResult"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoFreeFormQuery);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::EnableActionGetFreeFormQueryCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetFreeFormQueryCapabilities");
    action->AddOutputParameter(new ParameterString("FFQCapabilities"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3::DoGetFreeFormQueryCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3::DoGetSearchCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    GetSearchCapabilities(resp, aVersion, respSearchCaps);
}

void DvServiceUpnpOrgContentDirectory3::DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    GetSortCapabilities(resp, aVersion, respSortCaps);
}

void DvServiceUpnpOrgContentDirectory3::DoGetSortExtensionCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortExtensionCaps(aInvocation, "SortExtensionCaps");
    GetSortExtensionCapabilities(resp, aVersion, respSortExtensionCaps);
}

void DvServiceUpnpOrgContentDirectory3::DoGetFeatureList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respFeatureList(aInvocation, "FeatureList");
    GetFeatureList(resp, aVersion, respFeatureList);
}

void DvServiceUpnpOrgContentDirectory3::DoGetSystemUpdateID(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respId(aInvocation, "Id");
    GetSystemUpdateID(resp, aVersion, respId);
}

void DvServiceUpnpOrgContentDirectory3::DoGetServiceResetToken(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respResetToken(aInvocation, "ResetToken");
    GetServiceResetToken(resp, aVersion, respResetToken);
}

void DvServiceUpnpOrgContentDirectory3::DoBrowse(IDvInvocation& aInvocation, TUint aVersion)
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
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    Browse(resp, aVersion, ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvServiceUpnpOrgContentDirectory3::DoSearch(IDvInvocation& aInvocation, TUint aVersion)
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
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    Search(resp, aVersion, ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvServiceUpnpOrgContentDirectory3::DoCreateObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respObjectID(aInvocation, "ObjectID");
    InvocationResponseString respResult(aInvocation, "Result");
    CreateObject(resp, aVersion, ContainerID, Elements, respObjectID, respResult);
}

void DvServiceUpnpOrgContentDirectory3::DoDestroyObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DestroyObject(resp, aVersion, ObjectID);
}

void DvServiceUpnpOrgContentDirectory3::DoUpdateObject(IDvInvocation& aInvocation, TUint aVersion)
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
    UpdateObject(resp, aVersion, ObjectID, CurrentTagValue, NewTagValue);
}

void DvServiceUpnpOrgContentDirectory3::DoMoveObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    Brhz NewParentID;
    aInvocation.InvocationReadString("NewParentID", NewParentID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respNewObjectID(aInvocation, "NewObjectID");
    MoveObject(resp, aVersion, ObjectID, NewParentID, respNewObjectID);
}

void DvServiceUpnpOrgContentDirectory3::DoImportResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respTransferID(aInvocation, "TransferID");
    ImportResource(resp, aVersion, SourceURI, DestinationURI, respTransferID);
}

void DvServiceUpnpOrgContentDirectory3::DoExportResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respTransferID(aInvocation, "TransferID");
    ExportResource(resp, aVersion, SourceURI, DestinationURI, respTransferID);
}

void DvServiceUpnpOrgContentDirectory3::DoDeleteResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteResource(resp, aVersion, ResourceURI);
}

void DvServiceUpnpOrgContentDirectory3::DoStopTransferResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StopTransferResource(resp, aVersion, TransferID);
}

void DvServiceUpnpOrgContentDirectory3::DoGetTransferProgress(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respTransferStatus(aInvocation, "TransferStatus");
    InvocationResponseString respTransferLength(aInvocation, "TransferLength");
    InvocationResponseString respTransferTotal(aInvocation, "TransferTotal");
    GetTransferProgress(resp, aVersion, TransferID, respTransferStatus, respTransferLength, respTransferTotal);
}

void DvServiceUpnpOrgContentDirectory3::DoCreateReference(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respNewID(aInvocation, "NewID");
    CreateReference(resp, aVersion, ContainerID, ObjectID, respNewID);
}

void DvServiceUpnpOrgContentDirectory3::DoFreeFormQuery(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    TUint CDSView = aInvocation.InvocationReadUint("CDSView");
    Brhz QueryRequest;
    aInvocation.InvocationReadString("QueryRequest", QueryRequest);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respQueryResult(aInvocation, "QueryResult");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    FreeFormQuery(resp, aVersion, ContainerID, CDSView, QueryRequest, respQueryResult, respUpdateID);
}

void DvServiceUpnpOrgContentDirectory3::DoGetFreeFormQueryCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respFFQCapabilities(aInvocation, "FFQCapabilities");
    GetFreeFormQueryCapabilities(resp, aVersion, respFFQCapabilities);
}

void DvServiceUpnpOrgContentDirectory3::GetSearchCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetSortCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetSortExtensionCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortExtensionCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetFeatureList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aFeatureList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetSystemUpdateID(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetServiceResetToken(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aResetToken*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::Browse(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aBrowseFlag*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::Search(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aSearchCriteria*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::CreateObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aElements*/, IInvocationResponseString& /*aObjectID*/, IInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::DestroyObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::UpdateObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aCurrentTagValue*/, const Brx& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::MoveObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aNewParentID*/, IInvocationResponseString& /*aNewObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::ImportResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::ExportResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::DeleteResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aResourceURI*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::StopTransferResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetTransferProgress(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/, IInvocationResponseString& /*aTransferStatus*/, IInvocationResponseString& /*aTransferLength*/, IInvocationResponseString& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::CreateReference(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aObjectID*/, IInvocationResponseString& /*aNewID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::FreeFormQuery(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, TUint /*aCDSView*/, const Brx& /*aQueryRequest*/, IInvocationResponseString& /*aQueryResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3::GetFreeFormQueryCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aFFQCapabilities*/)
{
    ASSERTS();
}

