#include "DvUpnpOrgContentDirectory1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

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
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetSystemUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionBrowse()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionSearch()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionCreateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionDestroyObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionUpdateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionImportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionExportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionStopTransferResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionGetTransferProgress()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionDeleteResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory1::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory1::EnableActionCreateReference()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSearchCaps(aInvocation, "SearchCaps");
    GetSearchCapabilities(invocation, aVersion, respSearchCaps);
}

void DvProviderUpnpOrgContentDirectory1::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respSortCaps(aInvocation, "SortCaps");
    GetSortCapabilities(invocation, aVersion, respSortCaps);
}

void DvProviderUpnpOrgContentDirectory1::DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respId(aInvocation, "Id");
    GetSystemUpdateID(invocation, aVersion, respId);
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    Browse(invocation, aVersion, ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
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
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    Search(invocation, aVersion, ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvProviderUpnpOrgContentDirectory1::DoCreateObject(IDviInvocation& aInvocation, TUint aVersion)
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
    CreateObject(invocation, aVersion, ContainerID, Elements, respObjectID, respResult);
}

void DvProviderUpnpOrgContentDirectory1::DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DestroyObject(invocation, aVersion, ObjectID);
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
    DviInvocation invocation(aInvocation);
    UpdateObject(invocation, aVersion, ObjectID, CurrentTagValue, NewTagValue);
}

void DvProviderUpnpOrgContentDirectory1::DoImportResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTransferID(aInvocation, "TransferID");
    ImportResource(invocation, aVersion, SourceURI, DestinationURI, respTransferID);
}

void DvProviderUpnpOrgContentDirectory1::DoExportResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz SourceURI;
    aInvocation.InvocationReadString("SourceURI", SourceURI);
    Brhz DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", DestinationURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseUint respTransferID(aInvocation, "TransferID");
    ExportResource(invocation, aVersion, SourceURI, DestinationURI, respTransferID);
}

void DvProviderUpnpOrgContentDirectory1::DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    StopTransferResource(invocation, aVersion, TransferID);
}

void DvProviderUpnpOrgContentDirectory1::DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respTransferStatus(aInvocation, "TransferStatus");
    DviInvocationResponseString respTransferLength(aInvocation, "TransferLength");
    DviInvocationResponseString respTransferTotal(aInvocation, "TransferTotal");
    GetTransferProgress(invocation, aVersion, TransferID, respTransferStatus, respTransferLength, respTransferTotal);
}

void DvProviderUpnpOrgContentDirectory1::DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", ResourceURI);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DeleteResource(invocation, aVersion, ResourceURI);
}

void DvProviderUpnpOrgContentDirectory1::DoCreateReference(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz ContainerID;
    aInvocation.InvocationReadString("ContainerID", ContainerID);
    Brhz ObjectID;
    aInvocation.InvocationReadString("ObjectID", ObjectID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    DviInvocationResponseString respNewID(aInvocation, "NewID");
    CreateReference(invocation, aVersion, ContainerID, ObjectID, respNewID);
}

void DvProviderUpnpOrgContentDirectory1::GetSearchCapabilities(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::GetSortCapabilities(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aSortCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::GetSystemUpdateID(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::Browse(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aBrowseFlag*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aNumberReturned*/, IDvInvocationResponseUint& /*aTotalMatches*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::Search(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aSearchCriteria*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aNumberReturned*/, IDvInvocationResponseUint& /*aTotalMatches*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::CreateObject(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aElements*/, IDvInvocationResponseString& /*aObjectID*/, IDvInvocationResponseString& /*aResult*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::DestroyObject(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::UpdateObject(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aObjectID*/, const Brx& /*aCurrentTagValue*/, const Brx& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::ImportResource(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IDvInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::ExportResource(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aSourceURI*/, const Brx& /*aDestinationURI*/, IDvInvocationResponseUint& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::StopTransferResource(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::GetTransferProgress(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, TUint /*aTransferID*/, IDvInvocationResponseString& /*aTransferStatus*/, IDvInvocationResponseString& /*aTransferLength*/, IDvInvocationResponseString& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::DeleteResource(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aResourceURI*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory1::CreateReference(IDvInvocation& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aContainerID*/, const Brx& /*aObjectID*/, IDvInvocationResponseString& /*aNewID*/)
{
    ASSERTS();
}

