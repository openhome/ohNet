#include <Core/DvUpnpOrgContentDirectory1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderUpnpOrgContentDirectory1::SetPropertyTransferIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyTransferIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory1::GetPropertyTransferIDs(Brhz& aValue)
{
    aValue.Set(iPropertyTransferIDs->Value());
}

TBool DvProviderUpnpOrgContentDirectory1::SetPropertySystemUpdateID(TUint aValue)
{
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory1::GetPropertySystemUpdateID(TUint& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

TBool DvProviderUpnpOrgContentDirectory1::SetPropertyContainerUpdateIDs(const Brx& aValue)
{
    return SetPropertyString(*iPropertyContainerUpdateIDs, aValue);
}

void DvProviderUpnpOrgContentDirectory1::GetPropertyContainerUpdateIDs(Brhz& aValue)
{
    aValue.Set(iPropertyContainerUpdateIDs->Value());
}

DvProviderUpnpOrgContentDirectory1::DvProviderUpnpOrgContentDirectory1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ContentDirectory", 1)
{
    
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetSearchCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetSystemUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionBrowse()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionSearch()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionCreateObject()
{
    Zapp::Action* action = new Zapp::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionDestroyObject()
{
    Zapp::Action* action = new Zapp::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionUpdateObject()
{
    Zapp::Action* action = new Zapp::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionImportResource()
{
    Zapp::Action* action = new Zapp::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionExportResource()
{
    Zapp::Action* action = new Zapp::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionStopTransferResource()
{
    Zapp::Action* action = new Zapp::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetTransferProgress()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionDeleteResource()
{
    Zapp::Action* action = new Zapp::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionCreateReference()
{
    Zapp::Action* action = new Zapp::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::DoGetSearchCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    GetSearchCapabilities(resp, aVersion, respSearchCaps);
}

void DvProviderUpnpOrgContentDirectory1::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    GetSortCapabilities(resp, aVersion, respSortCaps);
}

void DvProviderUpnpOrgContentDirectory1::DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respId(aInvocation, "Id");
    GetSystemUpdateID(resp, aVersion, respId);
}

void DvProviderUpnpOrgContentDirectory1::DoBrowse(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoSearch(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoCreateObject(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DestroyObject(resp, aVersion, ObjectID);
}

void DvProviderUpnpOrgContentDirectory1::DoUpdateObject(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoImportResource(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoExportResource(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    StopTransferResource(resp, aVersion, TransferID);
}

void DvProviderUpnpOrgContentDirectory1::DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteResource(resp, aVersion, ResourceURI);
}

void DvProviderUpnpOrgContentDirectory1::DoCreateReference(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgContentDirectory1::GetSearchCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::GetSortCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::GetSystemUpdateID(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::Browse(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aBrowseFlag*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::Search(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aSearchCriteria*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::CreateObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aElements*/, IInvocationResponseString& /*aObjectID*/, IInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::DestroyObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::UpdateObject(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aCurrentTagValue*/, const Brx& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::ImportResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::ExportResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::StopTransferResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::GetTransferProgress(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/, IInvocationResponseString& /*aTransferStatus*/, IInvocationResponseString& /*aTransferLength*/, IInvocationResponseString& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::DeleteResource(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aResourceURI*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::CreateReference(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aObjectID*/, IInvocationResponseString& /*aNewID*/)
{
    ASSERTS();
}

