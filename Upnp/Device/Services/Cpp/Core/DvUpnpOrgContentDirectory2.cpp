#include <Core/DvUpnpOrgContentDirectory2.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgContentDirectory2::SetPropertySystemUpdateID(TUint aValue)
{
    SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvServiceUpnpOrgContentDirectory2::GetPropertySystemUpdateID(TUint& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

void DvServiceUpnpOrgContentDirectory2::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvServiceUpnpOrgContentDirectory2::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

void DvServiceUpnpOrgContentDirectory2::SetPropertyTransferIDs(const Brx& aValue)
{
    SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvServiceUpnpOrgContentDirectory2::GetPropertyTransferIDs(Brhz& aValue)
{
    aValue.Set(iPropertyTransferIDs->Value());
}

DvServiceUpnpOrgContentDirectory2::DvServiceUpnpOrgContentDirectory2(DvDevice& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ContentDirectory", 2)
{
    Functor empty;
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"), empty);
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"), empty);
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"), empty);
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvServiceUpnpOrgContentDirectory2::EnableActionGetSearchCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionGetSortExtensionCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionGetFeatureList()
{
    Zapp::Action* action = new Zapp::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionGetSystemUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionBrowse()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoBrowse);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionSearch()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoSearch);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionCreateObject()
{
    Zapp::Action* action = new Zapp::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionDestroyObject()
{
    Zapp::Action* action = new Zapp::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionUpdateObject()
{
    Zapp::Action* action = new Zapp::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionMoveObject()
{
    Zapp::Action* action = new Zapp::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionImportResource()
{
    Zapp::Action* action = new Zapp::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoImportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionExportResource()
{
    Zapp::Action* action = new Zapp::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoExportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionDeleteResource()
{
    Zapp::Action* action = new Zapp::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionStopTransferResource()
{
    Zapp::Action* action = new Zapp::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionGetTransferProgress()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::EnableActionCreateReference()
{
    Zapp::Action* action = new Zapp::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory2::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory2::DoGetSearchCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    GetSearchCapabilities(resp, aVersion, respSearchCaps);
}

void DvServiceUpnpOrgContentDirectory2::DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    GetSortCapabilities(resp, aVersion, respSortCaps);
}

void DvServiceUpnpOrgContentDirectory2::DoGetSortExtensionCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortExtensionCaps(aInvocation, "SortExtensionCaps");
    GetSortExtensionCapabilities(resp, aVersion, respSortExtensionCaps);
}

void DvServiceUpnpOrgContentDirectory2::DoGetFeatureList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respFeatureList(aInvocation, "FeatureList");
    GetFeatureList(resp, aVersion, respFeatureList);
}

void DvServiceUpnpOrgContentDirectory2::DoGetSystemUpdateID(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respId(aInvocation, "Id");
    GetSystemUpdateID(resp, aVersion, respId);
}

void DvServiceUpnpOrgContentDirectory2::DoBrowse(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoSearch(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoCreateObject(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoDestroyObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DestroyObject(resp, aVersion, ObjectID);
}

void DvServiceUpnpOrgContentDirectory2::DoUpdateObject(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoMoveObject(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoImportResource(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoExportResource(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoDeleteResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteResource(resp, aVersion, ResourceURI);
}

void DvServiceUpnpOrgContentDirectory2::DoStopTransferResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StopTransferResource(resp, aVersion, TransferID);
}

void DvServiceUpnpOrgContentDirectory2::DoGetTransferProgress(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::DoCreateReference(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgContentDirectory2::GetSearchCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::GetSortCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::GetSortExtensionCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortExtensionCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::GetFeatureList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aFeatureList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::GetSystemUpdateID(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::Browse(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aBrowseFlag*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::Search(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aSearchCriteria*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::CreateObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aElements*/, IInvocationResponseString& /*aObjectID*/, IInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::DestroyObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::UpdateObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aCurrentTagValue*/, const Brx& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::MoveObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aNewParentID*/, IInvocationResponseString& /*aNewObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::ImportResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::ExportResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::DeleteResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aResourceURI*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::StopTransferResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::GetTransferProgress(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/, IInvocationResponseString& /*aTransferStatus*/, IInvocationResponseString& /*aTransferLength*/, IInvocationResponseString& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory2::CreateReference(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aObjectID*/, IInvocationResponseString& /*aNewID*/)
{
    ASSERTS();
}

