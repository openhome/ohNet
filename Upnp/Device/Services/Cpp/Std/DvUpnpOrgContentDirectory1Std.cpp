#include <Std/DvUpnpOrgContentDirectory1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgContentDirectory1Cpp::SetPropertyTransferIDs(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyTransferIDs, buf);
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetPropertyTransferIDs(std::string& aValue)
{
    const Brx& val = iPropertyTransferIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceUpnpOrgContentDirectory1Cpp::SetPropertySystemUpdateID(uint32_t aValue)
{
    SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetPropertySystemUpdateID(uint32_t& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

void DvServiceUpnpOrgContentDirectory1Cpp::SetPropertyContainerUpdateIDs(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyContainerUpdateIDs, buf);
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetPropertyContainerUpdateIDs(std::string& aValue)
{
    const Brx& val = iPropertyContainerUpdateIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceUpnpOrgContentDirectory1Cpp::DvServiceUpnpOrgContentDirectory1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ContentDirectory", 1)
{
    Functor empty;
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"), empty);
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"), empty);
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"), empty);
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionGetSearchCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionGetSystemUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionBrowse()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoBrowse);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionSearch()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoSearch);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionCreateObject()
{
    Zapp::Action* action = new Zapp::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionDestroyObject()
{
    Zapp::Action* action = new Zapp::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionUpdateObject()
{
    Zapp::Action* action = new Zapp::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionImportResource()
{
    Zapp::Action* action = new Zapp::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoImportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionExportResource()
{
    Zapp::Action* action = new Zapp::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoExportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionStopTransferResource()
{
    Zapp::Action* action = new Zapp::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionGetTransferProgress()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionDeleteResource()
{
    Zapp::Action* action = new Zapp::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::EnableActionCreateReference()
{
    Zapp::Action* action = new Zapp::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory1Cpp::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoGetSearchCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSearchCaps;
    GetSearchCapabilities(aVersion, respSearchCaps);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSearchCaps(aInvocation, "SearchCaps");
    Brn buf_SearchCaps((const TByte*)respSearchCaps.c_str(), respSearchCaps.length());
    respWriterSearchCaps.Write(buf_SearchCaps);
    aInvocation.InvocationWriteStringEnd("SearchCaps");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortCaps;
    GetSortCapabilities(aVersion, respSortCaps);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSortCaps(aInvocation, "SortCaps");
    Brn buf_SortCaps((const TByte*)respSortCaps.c_str(), respSortCaps.length());
    respWriterSortCaps.Write(buf_SortCaps);
    aInvocation.InvocationWriteStringEnd("SortCaps");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoGetSystemUpdateID(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respId;
    GetSystemUpdateID(aVersion, respId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterId(aInvocation, "Id");
    respWriterId.Write(respId);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoBrowse(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    Brhz buf_BrowseFlag;
    aInvocation.InvocationReadString("BrowseFlag", buf_BrowseFlag);
    std::string BrowseFlag((const char*)buf_BrowseFlag.Ptr(), buf_BrowseFlag.Bytes());
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    uint32_t StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    uint32_t RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz buf_SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", buf_SortCriteria);
    std::string SortCriteria((const char*)buf_SortCriteria.Ptr(), buf_SortCriteria.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    uint32_t respNumberReturned;
    uint32_t respTotalMatches;
    uint32_t respUpdateID;
    Browse(aVersion, ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterNumberReturned(aInvocation, "NumberReturned");
    respWriterNumberReturned.Write(respNumberReturned);
    InvocationResponseUint respWriterTotalMatches(aInvocation, "TotalMatches");
    respWriterTotalMatches.Write(respTotalMatches);
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoSearch(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    Brhz buf_SearchCriteria;
    aInvocation.InvocationReadString("SearchCriteria", buf_SearchCriteria);
    std::string SearchCriteria((const char*)buf_SearchCriteria.Ptr(), buf_SearchCriteria.Bytes());
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    uint32_t StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    uint32_t RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz buf_SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", buf_SortCriteria);
    std::string SortCriteria((const char*)buf_SortCriteria.Ptr(), buf_SortCriteria.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    uint32_t respNumberReturned;
    uint32_t respTotalMatches;
    uint32_t respUpdateID;
    Search(aVersion, ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterNumberReturned(aInvocation, "NumberReturned");
    respWriterNumberReturned.Write(respNumberReturned);
    InvocationResponseUint respWriterTotalMatches(aInvocation, "TotalMatches");
    respWriterTotalMatches.Write(respTotalMatches);
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoCreateObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    Brhz buf_Elements;
    aInvocation.InvocationReadString("Elements", buf_Elements);
    std::string Elements((const char*)buf_Elements.Ptr(), buf_Elements.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respObjectID;
    std::string respResult;
    CreateObject(aVersion, ContainerID, Elements, respObjectID, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterObjectID(aInvocation, "ObjectID");
    Brn buf_ObjectID((const TByte*)respObjectID.c_str(), respObjectID.length());
    respWriterObjectID.Write(buf_ObjectID);
    aInvocation.InvocationWriteStringEnd("ObjectID");
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoDestroyObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    aInvocation.InvocationReadEnd();
    DestroyObject(aVersion, ObjectID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoUpdateObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    Brhz buf_CurrentTagValue;
    aInvocation.InvocationReadString("CurrentTagValue", buf_CurrentTagValue);
    std::string CurrentTagValue((const char*)buf_CurrentTagValue.Ptr(), buf_CurrentTagValue.Bytes());
    Brhz buf_NewTagValue;
    aInvocation.InvocationReadString("NewTagValue", buf_NewTagValue);
    std::string NewTagValue((const char*)buf_NewTagValue.Ptr(), buf_NewTagValue.Bytes());
    aInvocation.InvocationReadEnd();
    UpdateObject(aVersion, ObjectID, CurrentTagValue, NewTagValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoImportResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_SourceURI;
    aInvocation.InvocationReadString("SourceURI", buf_SourceURI);
    std::string SourceURI((const char*)buf_SourceURI.Ptr(), buf_SourceURI.Bytes());
    Brhz buf_DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", buf_DestinationURI);
    std::string DestinationURI((const char*)buf_DestinationURI.Ptr(), buf_DestinationURI.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respTransferID;
    ImportResource(aVersion, SourceURI, DestinationURI, respTransferID);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterTransferID(aInvocation, "TransferID");
    respWriterTransferID.Write(respTransferID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoExportResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_SourceURI;
    aInvocation.InvocationReadString("SourceURI", buf_SourceURI);
    std::string SourceURI((const char*)buf_SourceURI.Ptr(), buf_SourceURI.Bytes());
    Brhz buf_DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", buf_DestinationURI);
    std::string DestinationURI((const char*)buf_DestinationURI.Ptr(), buf_DestinationURI.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respTransferID;
    ExportResource(aVersion, SourceURI, DestinationURI, respTransferID);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterTransferID(aInvocation, "TransferID");
    respWriterTransferID.Write(respTransferID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoStopTransferResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    StopTransferResource(aVersion, TransferID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoGetTransferProgress(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    std::string respTransferStatus;
    std::string respTransferLength;
    std::string respTransferTotal;
    GetTransferProgress(aVersion, TransferID, respTransferStatus, respTransferLength, respTransferTotal);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterTransferStatus(aInvocation, "TransferStatus");
    Brn buf_TransferStatus((const TByte*)respTransferStatus.c_str(), respTransferStatus.length());
    respWriterTransferStatus.Write(buf_TransferStatus);
    aInvocation.InvocationWriteStringEnd("TransferStatus");
    InvocationResponseString respWriterTransferLength(aInvocation, "TransferLength");
    Brn buf_TransferLength((const TByte*)respTransferLength.c_str(), respTransferLength.length());
    respWriterTransferLength.Write(buf_TransferLength);
    aInvocation.InvocationWriteStringEnd("TransferLength");
    InvocationResponseString respWriterTransferTotal(aInvocation, "TransferTotal");
    Brn buf_TransferTotal((const TByte*)respTransferTotal.c_str(), respTransferTotal.length());
    respWriterTransferTotal.Write(buf_TransferTotal);
    aInvocation.InvocationWriteStringEnd("TransferTotal");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoDeleteResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", buf_ResourceURI);
    std::string ResourceURI((const char*)buf_ResourceURI.Ptr(), buf_ResourceURI.Bytes());
    aInvocation.InvocationReadEnd();
    DeleteResource(aVersion, ResourceURI);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DoCreateReference(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respNewID;
    CreateReference(aVersion, ContainerID, ObjectID, respNewID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterNewID(aInvocation, "NewID");
    Brn buf_NewID((const TByte*)respNewID.c_str(), respNewID.length());
    respWriterNewID.Write(buf_NewID);
    aInvocation.InvocationWriteStringEnd("NewID");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetSearchCapabilities(uint32_t /*aVersion*/, std::string& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetSortCapabilities(uint32_t /*aVersion*/, std::string& /*aSortCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetSystemUpdateID(uint32_t /*aVersion*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::Browse(uint32_t /*aVersion*/, const std::string& /*aObjectID*/, const std::string& /*aBrowseFlag*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::Search(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, const std::string& /*aSearchCriteria*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::CreateObject(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, const std::string& /*aElements*/, std::string& /*aObjectID*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DestroyObject(uint32_t /*aVersion*/, const std::string& /*aObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::UpdateObject(uint32_t /*aVersion*/, const std::string& /*aObjectID*/, const std::string& /*aCurrentTagValue*/, const std::string& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::ImportResource(uint32_t /*aVersion*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::ExportResource(uint32_t /*aVersion*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::StopTransferResource(uint32_t /*aVersion*/, uint32_t /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::GetTransferProgress(uint32_t /*aVersion*/, uint32_t /*aTransferID*/, std::string& /*aTransferStatus*/, std::string& /*aTransferLength*/, std::string& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::DeleteResource(uint32_t /*aVersion*/, const std::string& /*aResourceURI*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory1Cpp::CreateReference(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, const std::string& /*aObjectID*/, std::string& /*aNewID*/)
{
    ASSERTS();
}

